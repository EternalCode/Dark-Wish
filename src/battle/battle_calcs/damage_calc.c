#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../abilities/battle_abilities.h"

extern u16 RandRange(u16, u16);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern void dprintf(const char * str, ...);
extern bool is_grounded(u8 bank);

u16 type_effectiveness_mod(u8 attacker, u8 defender, u16 move)
{
    u16 percent = 100;
    // for each type of the attacker's move
    for (u8 i = 0; i < sizeof(gBattleMaster->b_moves[(attacker)].type); i++) {
        // get the type effectiveness for each type of the defender
        for (u8 j = 0; j < sizeof(gPkmnBank[defender]->battleData.type); j++) {
            if ((B_MOVE_TYPE(attacker, i) != TYPE_NONE) && (B_PKMN_TYPE(defender, j) != TYPE_NONE)) {
                u8 target_type = B_PKMN_TYPE(defender, j);
                u8 move_type = B_MOVE_TYPE(attacker, i);
				if (move_type == TYPE_NONE)
					return percent;
                u16 move_effectiveness = MOVE_EFFECTIVENESS(target_type, move_type);
                if (is_grounded(defender) && (move_type == TYPE_GROUND) && (target_type == TYPE_FLYING)) {
                    move_effectiveness = 100;
                } else if (!is_grounded(defender) && (move_type == TYPE_GROUND)) {
                    move_effectiveness = 0;
                }

                // add ability immunity callbacks
                for (u8 z = 0; z < BANK_MAX; z++) {
                    u8 ability = gPkmnBank[z]->battleData.ability;
                    if ((abilities[ability].on_effectiveness) && (ACTIVE_BANK(z)))
                        AddCallback(CB_ON_EFFECTIVENESS, 0, 0, z, (u32)abilities[ability].on_effectiveness);
                }

                // back up cbs
                u8 old_index = CB_EXEC_INDEX;
                u32* old_execution_array = push_callbacks();
                // callbacks for effectiveness of moves
                BuildCallbackExecutionBuffer(CB_ON_EFFECTIVENESS);
                gBattleMaster->executing = true;
                while (gBattleMaster->executing) {
                    u32 data = ((attacker << 16) | move_effectiveness);
                    set_data_next_acb(data);
                    u16 effectiveness_temp = PopCallback(target_type, move_type);
                    if (effectiveness_temp != 1) {
                        move_effectiveness = effectiveness_temp;
                    }
                }
                // restore callbacks
                restore_callbacks(old_execution_array);
                CB_EXEC_INDEX = old_index;
                if (move_effectiveness > 0) {
                    percent = PERCENT(percent, move_effectiveness);
                } else {
                    // target has an immunity, return 0
                    return 0;
                }
            }
        }
    }
    return percent;
}


u16 weather_dmg_mod(u16 damage, u8 attacker)
{
    u16 modifier = 100;
    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    BuildCallbackExecutionBuffer(CB_ON_WEATHER_DMG);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        u16 test_modifier = PopCallback(attacker, CURRENT_MOVE(attacker));
        if (test_modifier != 1) {
            modifier = test_modifier;
        }
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    return PERCENT(damage, modifier);
}


u16 get_base_damage(u8 attacker, u8 defender, u16 move)
{
    if (B_MOVE_IS_STATUS(attacker))
        return 0;

    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_base_power) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_BASE_POWER_MOVE, 0, 0, i, (u32)abilities[ability].on_base_power);
    }
    // add base power callbacks specific to field
    if (gBattleMoves[move].on_base_power_move) {
        AddCallback(CB_ON_BASE_POWER_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].on_base_power_move);
    }
    // run base power callbacks
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    BuildCallbackExecutionBuffer(CB_ON_BASE_POWER_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        PopCallback(attacker, move);
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    u16 base_power = B_MOVE_POWER(attacker);

    // get defending and attacking stats
    enum MoveCategory atk_category = B_MOVE_CATEGORY(attacker);
    enum MoveCategory def_category;
    if (CAT_OVERRIDE(move)) {
        def_category = B_MOVE_IS_PHYSICAL(attacker) ? MOVE_SPECIAL : MOVE_PHYSICAL;
    } else {
        def_category = B_MOVE_CATEGORY(attacker);
    }

    s8 atk_mod[2] = {0, 0};
    s8 def_mod[2] = {0, 0};
    u16 atk_stat, def_stat;

    // temporarily remove effects of boosts
    if (B_MOVE_IGNORE_ATK(attacker)) {
        atk_mod[0] = gPkmnBank[attacker]->battleData.attack;
        atk_mod[1] = gPkmnBank[attacker]->battleData.sp_atk;
        gPkmnBank[attacker]->battleData.attack = 0;
        gPkmnBank[attacker]->battleData.sp_atk = 0;
    }
    if (B_MOVE_IGNORE_DEF(attacker)) {
        def_mod[0] = gPkmnBank[defender]->battleData.defense;
        def_mod[1] = gPkmnBank[defender]->battleData.sp_def;
        gPkmnBank[defender]->battleData.defense = 0;
        gPkmnBank[defender]->battleData.sp_def = 0;
    }

    // foul play sets this flag
    if (STEAL_OFFENSIVE(move)) {
        atk_stat = (atk_category == MOVE_PHYSICAL) ? B_ATTACK_STAT(defender) : B_SPATTACK_STAT(defender);
    } else {
        atk_stat = (atk_category == MOVE_PHYSICAL) ? B_ATTACK_STAT(attacker) : B_SPATTACK_STAT(attacker);
    }
    def_stat = (def_category == MOVE_PHYSICAL)? B_DEFENSE_STAT(defender) : B_SPDEFENSE_STAT(defender);

    // restore boosts if they were removed
    if (B_MOVE_IGNORE_ATK(attacker)) {
        gPkmnBank[attacker]->battleData.attack = atk_mod[0];
        gPkmnBank[attacker]->battleData.sp_atk = atk_mod[1];
    }

    if (B_MOVE_IGNORE_DEF(attacker)) {
        gPkmnBank[defender]->battleData.defense = def_mod[0];
        gPkmnBank[defender]->battleData.sp_def = def_mod[1];
    }

    // Calc base damage - broken up for readability
    u16 dmg = ((B_LEVEL(attacker) * 2) / 5) + 2;
    dmg *= base_power;
    dmg = PERCENT(dmg, ((atk_stat * 100) / def_stat));
    dmg = (dmg/ 50) + 2;
    return dmg;
}

u16 modify_damage(u16 base_damage, u8 attacker, u8 defender, u16 move)
{
    u16 modded_base = base_damage;

    // Targets mod
    u8 targets_mod;
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
            /* TODO : Check if other targets are alive & move is spread */
            targets_mod = 75;
            break;
        default:
            targets_mod = 100;
    };
    modded_base = PERCENT(modded_base, targets_mod);

    // Weather Mod
    modded_base = weather_dmg_mod(modded_base, attacker);

    // critical Mod
    if (B_MOVE_WILL_CRIT(attacker)) {
        modded_base = PERCENT(modded_base, 150);
    } else if (B_MOVE_CAN_CRIT(attacker)) {
        gPkmnBank[attacker]->battleData.crit_mod += MOVE_CRIT(move);
        if ((RandRange(0, 100)) <= B_CRITCHANCE_STAT(attacker)) {
            B_MOVE_WILL_CRIT(attacker) = true;
            modded_base = PERCENT(modded_base, 150);
            B_DID_CRIT(attacker) = true;
        }
        gPkmnBank[attacker]->battleData.crit_mod -= MOVE_CRIT(move);
    }

    // random factor
    modded_base = PERCENT(modded_base, RandRange(85, 100));

    // stab calc
    u8 i;
    for (i = 0; i < 2; i++) {
        if ((B_MOVE_TYPE(attacker, i) != TYPE_NONE) && (BankMonHasType(attacker, B_MOVE_TYPE(attacker, i)))) {
            modded_base = PERCENT(modded_base, B_MOVE_STAB(attacker));
            break;
        }
    }

    // type modifications
    u16 type_effect_percent = type_effectiveness_mod(attacker, defender, move);
    if (type_effect_percent > 100) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_SUPER_EFFECTIVE;
    } else if (type_effect_percent == 100) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_EFFECTIVE;
    } else if (type_effect_percent > 0) {
        B_MOVE_EFFECTIVENESS(attacker) = TE_NOT_VERY_EFFECTIVE;
    } else {
        dprintf("The target was immune via dmg calc.\n");
        B_MOVE_EFFECTIVENESS(attacker) = TE_IMMUNE;
    }
    modded_base = PERCENT(modded_base, type_effect_percent);

    // burn ailment attack reduction
    if ((B_STATUS(attacker) == AILMENT_BURN) &&
        (B_MOVE_CATEGORY(attacker) == MOVE_PHYSICAL) &&
        (BANK_ABILITY(attacker) != ABILITY_GUTS) &&
        (move != MOVE_FACADE) && (!B_MOVE_WILL_CRIT(attacker))) {
        modded_base = PERCENT(modded_base, 50);
    }
    return modded_base;
}

s16 get_damage(u8 attacker, u8 defender, u16 move)
{
    u16 dmg = 0;
    bool return_now = false;
	if (B_MOVE_DMG(attacker)) {
        u16 percent = type_effectiveness_mod(attacker, defender, move);
        if (percent) {
            B_MOVE_EFFECTIVENESS(attacker) = TE_EFFECTIVE;
            dmg = B_MOVE_DMG(attacker);
            return_now = true;
        } else {
            B_MOVE_EFFECTIVENESS(attacker) = TE_IMMUNE;
            dmg = 0;
            return_now = true;
        }
    }

    if (!return_now) {
        if (IS_OHKO(move)) {
            gBattleMaster->b_moves[(attacker)].effectiveness = TE_OHKO;
            dmg = (TOTAL_HP(defender));
            return_now = true;
        }

        if (!return_now) {
            // get base damage
            u16 base_dmg = get_base_damage(attacker, defender, move);
            if (base_dmg == 0) {
                dmg = 0;
            } else {
                u16 result = modify_damage(base_dmg, attacker, defender, move);
                dmg = MAX(result, 1);
            }
            if (B_MOVE_POWER(attacker) == 0)
                dmg = 0;
        }
    }
    B_MOVE_DMG(attacker) = dmg;
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_damage) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_DAMAGE_MOVE, 0, 0, i, (u32)abilities[ability].on_damage);
    }
    // add base power callbacks specific to field
    if (gBattleMoves[move].on_damage_move) {
        AddCallback(CB_ON_DAMAGE_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].on_damage_move);
    }

    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    // run base power callbacks
    BuildCallbackExecutionBuffer(CB_ON_DAMAGE_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        PopCallback(attacker, move);
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    return B_MOVE_DMG(attacker);
}
