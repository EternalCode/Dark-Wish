#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"
#include "../status_effects/status.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

enum BeforeMoveStatus {
    CANT_USE_MOVE = 0,
    USE_MOVE_NORMAL,
    TARGET_MOVE_IMMUNITY,
    SILENT_FAIL,
    SILENT_CONTINUE,
};


enum BeforeMoveStatus RunBeforeMoveCallbacks(u8 attacker)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].before_move) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_BEFORE_MOVE, 0, 0, i, (u32)abilities[ability].before_move);
    }
    u16 move = CURRENT_MOVE(attacker);
    // add callbacks specific to field
    if (gBattleMoves[move].before_move) {
        AddCallback(CB_ON_BEFORE_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].before_move);
    }
    // run callbacks
    BuildCallbackExecutionBuffer(CB_ON_BEFORE_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        enum BeforeMoveStatus status = PopCallback(attacker, move);
        if (status != USE_MOVE_NORMAL)
            return status;
    }
    return USE_MOVE_NORMAL;
}

void event_before_move(struct action* current_action)
{
    dprintf("running before move event\n");
    /* If bank is recharging, then recharge and end action. */
    if (HAS_VOLATILE(ACTION_BANK, VOLATILE_RECHARGING)) {
        CLEAR_VOLATILE(ACTION_BANK, VOLATILE_RECHARGING);
        QueueMessage(0, ACTION_BANK, STRING_MUST_RECHARGE, 0);
        end_action(current_action);
        return;
    }
    CURRENT_MOVE(ACTION_BANK) = CURRENT_ACTION->move;
    /* Resolve before move callbacks */
    u8 result = RunBeforeMoveCallbacks(ACTION_BANK);
    switch (result) {
        case CANT_USE_MOVE:
        case TARGET_MOVE_IMMUNITY:
            QueueMessage(0, ACTION_BANK, STRING_FAILED, 0);
        case SILENT_FAIL:
            end_action(current_action);
            return;
        case USE_MOVE_NORMAL:
            break;
    };

    /* Before Move effects which cause turn ending */
    if (HAS_VOLATILE(ACTION_BANK, VOLATILE_SLEEP_TURN)) {
        QueueMessage(0, ACTION_BANK, STRING_FAST_ASLEEP, 0);
        struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animSleep;
        QueueMessage(0, ACTION_BANK, STRING_FAST_ASLEEP, 0);
        B_MOVE_FAILED(ACTION_BANK) = true;
    } else if (HAS_VOLATILE(ACTION_BANK, VOLATILE_CONFUSE_TURN) || HAS_VOLATILE(ACTION_BANK, VOLATILE_CHARGING)) {
        B_MOVE_FAILED(ACTION_BANK) = true;
    } else if (HAS_VOLATILE(ACTION_BANK, VOLATILE_ATK_SKIP_TURN)) {
        B_MOVE_FAILED(ACTION_BANK) = true;
        CLEAR_VOLATILE(ACTION_BANK, VOLATILE_ATK_SKIP_TURN);
    } else {
        B_MOVE_FAILED(ACTION_BANK) = false;
    }
    if (B_MOVE_FAILED(ACTION_BANK)) {
        CURRENT_ACTION->event_state = EventMoveFailed;
        return;
    }
    // display "Pokemon used move!"
    QueueMessage(CURRENT_MOVE(ACTION_BANK), ACTION_BANK, STRING_ATTACK_USED, 0);
    current_action->event_state++;
}
