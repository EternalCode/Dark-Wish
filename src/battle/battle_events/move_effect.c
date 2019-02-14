#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);


void event_move_effect(struct action* current_action)
{
    /* execute move effect */
    u8 attacker = current_action->action_bank;
    u16 move = CURRENT_MOVE(attacker);

    if (B_FAINTED(attacker)) {
        CURRENT_ACTION->event_state++;
        return;
    }
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_effect) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_EFFECT, 0, 0, i, (u32)abilities[ability].on_effect);
    }
    // add callbacks specific to field
    if (gBattleMoves[move].on_effect_cb) {
        AddCallback(CB_ON_EFFECT, 0, 0, attacker, (u32)gBattleMoves[move].on_effect_cb);
    }
    // run callbacks
    BuildCallbackExecutionBuffer(CB_ON_EFFECT);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        if (!(PopCallback(attacker, move))) {
            QueueMessage(move, attacker, STRING_FAILED, 0);
            CURRENT_ACTION->event_state = EventMoveFailed;
            return;
        }
    }
    CURRENT_ACTION->event_state++;
}
