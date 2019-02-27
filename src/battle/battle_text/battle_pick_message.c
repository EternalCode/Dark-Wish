#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "battle_pick_message.h"

extern void dprintf(const char * str, ...);
extern void buffer_write_pkmn_nick(pchar* buff, u8 bank);
extern void buffer_write_move_name(pchar* buff, u16 moveId);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void PickBattleTypeEncounterMsg(enum BattleTypes battle_type_flag)
{
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
        {
            pchar text[] = _("A wild {STR_VAR_1} appeared!\pGo! {STR_VAR_2}!");
            buffer_write_pkmn_nick(fcode_buffer3, PLAYER_SINGLES_BANK);
            buffer_write_pkmn_nick(fcode_buffer2, OPPONENT_SINGLES_BANK);
            fdecoder(string_buffer, text);
            break;
        }
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            break;
    };

}


extern void fdecoder_battle(const pchar* buffer, u8 bank, u16 moveId, u16 move_effect_id);
void pick_battle_message(u16 moveId, u8 user_bank, enum BattleTypes battle_type, enum battle_string_ids id, u16 move_effect_id)
{
    u8 side = SIDE_OF(user_bank);
    remo_reset_acknowledgement_flags();
    if (battle_type_flag == BATTLE_MODE_WILD) {
        switch (id) {
            case STRING_LEVEL_UP:
            case STRING_EXP_GAIN:
            case STRING_MULTI_HIT:
            case STRING_COUNT_FELL:
            case STRING_SETUP_STOCKPILE:
            case STRING_MAGNITUDE_AMOUNT:
                fmt_int_10(fcode_buffer2, move_effect_id, 0, 8);
                fdecoder_battle(battle_strings[id], user_bank, moveId, move_effect_id);
                break;
            case STRING_TRAPPED:
            case STRING_INFATUATED:
            case STRING_BIDE_CHARGE:
            case STRING_LOST_FOCUS:
            case STRING_CANT_USE:
            case STRING_DISABLED:
            case STRING_FAILED:
            case STRING_CURSE_RESIDUAL:
            case STRING_NO_TARGET:
            case STRING_RAZORWIND:
            case STRING_SOLARBEAM:
            case STRING_FREEZE_SHOCK:
            case STRING_ICE_BURN:
            case STRING_GOEMANCY:
            case STRING_SKULL_BASH:
            case STRING_RAINING:
            case STRING_STATUS_CURED:
            case STRING_AILMENT_ENDED:
            case STRING_GAINED_TYPE:
            case STRING_CONFUSION_ENDED:
            case STRING_DRAGGED_OUT_FAILED:
            case STRING_STAT_MOD_HARSH_DROP:
            case STRING_STAT_MOD_DROP:
            case STRING_STAT_MOD_HARSH_RISE:
            case STRING_STAT_MOD_RISE:
            case STRING_AILMENT_APPLIED:
            case STRING_AILMENT_IMMUNE:
            case STRING_AILMENT_CURED:
            case STRING_PROTEAN:
            case STRING_FAINTED:
            case STRING_HEAL:
            case STRING_FLINCHED:
            case STRING_CHARGE_SKY_ATTACK:
            case STRING_CHARGE_FLY:
            case STRING_CHARGE_PHANTOM_FORCE:
            case STRING_CHARGE_SHADOW_FORCE:
            case STRING_CHARGE_BOUNCE:
            case STRING_CHARGE_SKY_DROP:
            case STRING_CHARGE_SOLAR_BLADE:
            case STRING_INVULNERABLE:
            case STRING_RESIDUAL_DMG:
            case STRING_STAT_MOD_CANT_GO_LOWER:
            case STRING_STAT_MOD_CANT_GO_HIGHER:
            case STRING_STAT_MOD_SEVERELY_FELL:
            case STRING_STAT_MOD_ROSE_DRASTICALLY:
  			case STRING_FAST_ASLEEP:
  			case STRING_WOKE_UP:
  			case STRING_SNAPPED_OUT:
  			case STRING_CONFUSION_HURT:
  			case STRING_IS_CONFUSED:
  			case STRING_FROZEN_SOLID:
  			case STRING_FREEZE_THAWED:
  			case STRING_FULL_PARA:
            case STRING_CLEAR_SMOG:
            case STRING_SHROUDED_MAGICCOAT:
            case STRING_SNATCH_WAITING:
            case STRING_SNATCHED_MOVE:
            case STRING_MUST_RECHARGE:
            case STRING_CONVERSION_TYPE:
            case STRING_REFLECT_TYPE_MATCHED:
            case STRING_TYPE_ADDED:
            case STRING_BURNT_OUT:
            case STRING_PROTECTED_SELF:
            case STRING_ENDURED:
            case STRING_BRACED_ITSELF:
            case STRING_SANDSTORM_BUFFET:
            case STRING_AURORA_VEIL:
            case STRING_REFLECT:
            case STRING_LIGHTSCREEN:
            case STRING_FUTURE_FORESAW:
            case STRING_TOOK_ATTACK:
            case STRING_DOOM_DESIRE:
            case STRING_WISH_TRUE:
            case STRING_GREW_DROWSY:
            case STRING_RECOIL:
            case STRING_DRAIN:
            case STRING_FAILED_ALONE:
            case STRING_DELTA_STREAM:
            case STRING_DESOLATE_LAND:
            case STRING_PRIMORDIAL_SEA:
            case STRING_ATTACK_AVOIDED:
            case STRING_ATTACK_MISSED:
            case STRING_FLEE_FAILED:
            case STRING_MOVE_CRIT:
            case STRING_MOVE_NVE:
            case STRING_MOVE_SE:
            case STRING_WEATHER_GONE:
            case STRING_OHKO:
            case STRING_ATTACK_USED:
            case STRING_RESIDUAL_STATUS_DMG:
  			case STRING_NO_PP:
  			case STRING_DISABLED_PICKED:
  			case STRING_ION_DELUGE:
  			case STRING_PROTECTED_MON:
            case STRING_KICKED_UP_MAT:
            case STRING_PROTECTED_TEAM:
            case STRING_BROKE_PROTECT:
            case STRING_RAIN_FALLING:
            case STRING_RAIN_STOPPED:
            case STRING_HEAVY_RAIN_FIZZLE:
            case STRING_HEAVY_RAIN_LIFTED:
            case STRING_SUNLIGHT_HARSH:
            case STRING_SUNLIGHT_STRONG:
            case STRING_SUNLIGHT_FADE:
            case STRING_HARSH_SUN_WATER:
            case STRING_HARSH_SUN_END:
            case STRING_SANDSTORM_KICKED:
            case STRING_SANDSTORM_RAGE:
            case STRING_SANDSTORM_END:
            case STRING_DELTA_STREAM_EFFECT:
            case STRING_DELTA_STREAM_END:
            case STRING_DELTA_STREAM_IMM:
            case STRING_PRIMORDIAL_SEA_IMM:
            case STRING_DESOLATE_LAND_IMM:
            case STRING_SHATTER_BARRIER:
            case STRING_MOVE_ENDED:
            case STRING_ELECTRIC_TERRAIN_START:
            case STRING_PSYCHIC_TERRAIN_START:
            case STRING_GRASSY_TERRAIN_START:
            case STRING_MISTY_TERRAIN_START:
            case STRING_LEARNED_MOVE:
            case STRING_SLOT_ATTACK:
            case STRING_TAILWIND_BLEW:
            case STRING_TAILWIND_PETER:
            case STRING_TWISTED_DIM:
            case STRING_TWISTED_DIM_NORM:
            case STRING_WONDER_AREA:
            case STRING_SAFE_GUARD_VEIL:
            case STRING_SHIELDED_CRITS:
            case STRING_GRAVITY_INTENSE:
            case STRING_FAILED_EXECUTION:
            case STRING_IDENTIFIED:
            case STRING_TYPE_WEAKEN:
            case STRING_MAGNETISM_LEV:
            case STRING_HURLED_AIR:
            case STRING_HEAL_PREVENT:
            case STRING_GUARD_S:
            case STRING_POWER_S:
            case STRING_SPE_SWAP:
            case STRING_RECIEVED_ENCORE:
            case STRING_SUBJECTED_TORM:
            case STRING_FELL_FOR_TAUNT:
            case STRING_CANT_REASON:
            case STRING_ROOTS_PLANTED:
            case STRING_FELL_DOWN:
            case STRING_SETUP_SHELL_TRP:
            case STRING_PERISH_START:
            case STRING_TOOK_WITH_HIM:
            case STRING_TRYING_TO_TAKE:
            case STRING_GRUDGE_START:
            case STRING_GRUDGE_END:
            case STRING_SKY_DROP_AIR:
            case STRING_SKY_DROP_FREE:
            case STRING_ATTRACT:
            case STRING_UNLEASHED_ENERGY:
            case STRING_READY_TO_HELP:
            case STRING_INFESTATION:
            case STRING_TOPSY_TURVY:
            case STRING_CENTER_ATTENTION:
            case STRING_SOOTHING_AROMA:
            case STRING_CHARGE_DIVE:
            case STRING_CHARGE_DIG:
            case STRING_COPIED_STATS:
            case STRING_PAIN_SPLIT:
            case STRING_BELL_CHIMED:
            case STRING_BELLY_DRUM:
            case STRING_CURSE:
            case STRING_STAT_ELIMINATED:
            case STRING_SEEDED:
            case STRING_SAPPED:
            case STRING_TIGHTEN_FOCUS:
            case STRING_BEAK_BLAST:
            case STRING_HEART_SWAP:
            case STRING_RETREAT_MON:
            case STRING_SEND_OUT:
            case STRING_ANGER_POINT:
            case STRING_FLASH_FIRE:
            case STRING_ABILITY_CHANGED:
            case STRING_TRACE_ABILITY:
            case STRING_TRAPPED_RUN:
            case STRING_RUN_AWAY:
            case STRING_ANTICIPATION:
            case STRING_FRISK:
            case STRING_EMPTY:
            case STRING_LEARN_MOVE:
            case STRING_USED_ITEM:
                fdecoder_battle(battle_strings[id], user_bank, moveId, move_effect_id);
                break;
            case STRING_IMMUNE_ABILITY:
            case STRING_FLEE:
            case STRING_MOVE_IMMUNE:
            case STRING_BOUNCED_BACK:
            case STRING_ELECTRIFIED:
            case STRING_SKY_DROP_START:
                fdecoder_battle(battle_strings[id + side], user_bank, moveId, move_effect_id);
                break;
            case STRINGS_TABLE_MAX:
            default:
                break;
        };
    }
}

/* Pick and queue effectiveness string. 0 = fail should fail/immune. */
bool damage_result_msg(u8 bank_index)
{
    // effectiveness msgs
    bool effective = true;
    switch (B_MOVE_EFFECTIVENESS(bank_index)) {
        case TE_IMMUNE:
            if (!B_MOVE_MULTI(bank_index))
                QueueMessage(0, bank_index, STRING_MOVE_IMMUNE, 0);
            effective = false;
            break;
        case TE_NOT_VERY_EFFECTIVE:
            if (!B_MOVE_MULTI(bank_index))
                QueueMessage(0, 0, STRING_MOVE_NVE, 0);
            break;
        case TE_SUPER_EFFECTIVE:
            if (!B_MOVE_MULTI(bank_index))
                QueueMessage(0, 0, STRING_MOVE_SE, 0);
            break;
        case TE_OHKO:
            if (!B_MOVE_MULTI(bank_index))
                QueueMessage(0, 0, STRING_OHKO, 0);
            break;
        default:
            break;
    };

    if (effective) {
        // crit msg if crit
        if (B_MOVE_WILL_CRIT(bank_index)) {
            QueueMessage(0, bank_index, STRING_MOVE_CRIT, 0);
        }
    }
    return effective;
}
