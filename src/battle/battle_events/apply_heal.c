#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void hp_anim_change(u8 bank, s16 delta);
extern void battle_loop(void);
extern void hpbar_apply_dmg(u8 task_id);
extern void hp_anim_change(u8 bank, s16 delta);


void apply_heal()
{
    switch (gMain.state) {
        case 0:
        {
            u8 bank = CURRENT_ACTION->priv[0];
            u16 heal = PERCENT(TOTAL_HP(bank), CURRENT_ACTION->priv[1]);
            if (TOTAL_HP(bank) < (heal + B_CURRENT_HP(bank))) {
                heal = TOTAL_HP(bank) - B_CURRENT_HP(bank);
            }
            if (heal > 0) {
                hp_anim_change(bank, heal + B_CURRENT_HP(bank));
            }
            gMain.state = 2;
            break;
        }
        case 1:
        {
            u8 bank = CURRENT_ACTION->priv[0];
            u16 max_heal = TOTAL_HP(bank) - B_CURRENT_HP(bank);
            if (CURRENT_ACTION->priv[1] > 0) {
                hp_anim_change(bank, B_CURRENT_HP(bank) + MIN(CURRENT_ACTION->priv[1], max_heal));
            }
            gMain.state++;
            break;
        }
        case 2:
            if (task_is_running(hpbar_apply_dmg))
                return;
            gMain.state++;
            break;
        default:
            end_action(CURRENT_ACTION);
            SetMainCallback(battle_loop);
            break;
        };
}

void init_heal(struct action* a)
{
    gMain.state = a->priv[2];
    SetMainCallback(apply_heal);
    return;
}

void flat_heal(u8 bank, u16 heal)
{
    struct action* a = prepend_action(bank, NULL, ActionHeal, EventHealAnim);
    a->priv[0] = bank;
    a->priv[1] = heal;
    a->priv[2] = 1;
}

void do_heal(u8 bank_index, u16 heal)
{
    struct action* a = prepend_action(bank_index, NULL, ActionHeal, EventHealAnim);
    a->priv[0] = bank_index;
    a->priv[1] = heal;
    a->priv[2] = 0;
}

void event_move_heal(struct action* current_action) {
    u8 bank = current_action->action_bank;
    if (B_FAINTED(bank)) {
        CURRENT_ACTION->event_state++;
        return;
    }
    if (B_HEAL(bank)) {
        do_heal(TARGET_OF(bank), B_HEAL(bank));
        QueueMessage(CURRENT_MOVE(bank), TARGET_OF(bank), STRING_HEAL, 0);
    }
    CURRENT_ACTION->event_state++;
}
