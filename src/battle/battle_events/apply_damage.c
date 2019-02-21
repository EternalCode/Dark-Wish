#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern bool damage_result_msg(u8 bank_index);
extern void hpbar_apply_dmg(u8 task_id);
extern void hp_anim_change(u8 bank, s16 delta);
extern void battle_loop(void);

void apply_damage()
{
    switch (gMain.state) {
        case 0:
        {
            s16 delta = B_CURRENT_HP(CURRENT_ACTION->priv[0]) - CURRENT_ACTION->priv[1];
            delta = MAX(delta, 0);
            // HP bar damage animation
            hp_anim_change(CURRENT_ACTION->priv[0], delta);
            gMain.state++;
            break;
        }
        case 1:
            if (task_is_running(hpbar_apply_dmg))
                return;
            gMain.state++;
            break;
        default:
            if (B_CURRENT_HP(CURRENT_ACTION->priv[0]) < 1) {
                B_FAINTED(CURRENT_ACTION->priv[0]) = true;
            }
            end_action(CURRENT_ACTION);
            SetMainCallback(battle_loop);
            break;
        };
}

void init_damage(struct action* a)
{
    gMain.state = 0;
    SetMainCallback(apply_damage);
    return;
}

void do_damage(u8 bank_index, u16 dmg)
{
    struct action* a = prepend_action(bank_index, NULL, ActionDamage, EventDamageAnim);
    a->priv[0] = bank_index;
    a->priv[1] = dmg;
}

bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags)
{
    u8 ability = BANK_ABILITY(bank_index);
    if (dmg && !HAS_ABILITY_FLAG(ability, (A_FLAG_INDIRECT_DMG_PREVENT | ability_flags))) {
        do_damage(bank_index, dmg);
        return true;
    }
    return false;
}

void event_move_damage(struct action* current_action)
{
    u8 bank_index = current_action->action_bank;
    // get dmg
    u16 dmg = get_damage(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index));
    if (dmg < 1) {
        CURRENT_ACTION->event_state++;
        return;
    }
    if (B_MOVE_EFFECTIVENESS(bank_index) == TE_IMMUNE) {
        // Todo: run move failed and delete current event
        damage_result_msg(bank_index);
        CURRENT_ACTION->event_state = EventMoveFailed;
        return;
    }

    // Log damage stats in structs
    B_MOVE_DMG(bank_index) = dmg;
    gPkmnBank[TARGET_OF(bank_index)]->battleData.last_damage = dmg;
    gPkmnBank[TARGET_OF(bank_index)]->battleData.last_attacked_by = bank_index;

    // play move animation
    if (gBattleMoves[CURRENT_MOVE(bank_index)].animation) {
        struct action* a = prepend_action(bank_index, TARGET_OF(bank_index), ActionAnimation, EventPlayAnimation);
        a->move = CURRENT_MOVE(bank_index);
        a->script = gBattleMoves[CURRENT_MOVE(bank_index)].animation;
    }

    // HP bar damage
    do_damage(TARGET_OF(bank_index), dmg);
    damage_result_msg(bank_index);
    CURRENT_ACTION->event_state++;
}
