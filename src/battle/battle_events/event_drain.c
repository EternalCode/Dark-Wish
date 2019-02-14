#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void flat_heal(u8 bank, u16 heal);
extern void do_damage(u8 bank_index, u16 dmg);

void event_drain(struct action* current_action)
{
    u8 bank = current_action->action_bank;
    u16 move = CURRENT_MOVE(bank);
    B_DRAIN(bank) = 0;
    if (B_FAINTED(bank)) {
        end_action(CURRENT_ACTION);
        return;
    }

    // add drain related callbacks
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_drain) && (ACTIVE_BANK(i)))
            add_callback(CB_ON_DRAIN, 0, 0, i, (u32)abilities[ability].on_drain);
    }

    B_DRAIN(bank) = PERCENT(B_MOVE_DMG(bank), moves[move].drain);
    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    bool execution_status = gBattleMaster->executing;

    // run callbacks
    build_execution_order(CB_ON_DRAIN);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        pop_callback(bank, move);
    }
    // restore callbacks
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    gBattleMaster->executing = execution_status;

    // do drain
    if (B_DRAIN(bank) > 0) {
        flat_heal(bank, B_DRAIN(bank));
    } else if (B_DRAIN(bank) < 0) {
        do_damage(bank, -B_DRAIN(bank));
    }
    end_action(CURRENT_ACTION);
}


void event_move_drain(struct action* current_action)
{
    // apply drain
    u8 bank = CURRENT_ACTION->action_bank;
    CURRENT_ACTION->event_state++;
    prepend_action(bank, TARGET_OF(bank), ActionHeal, EventDrain);
}
