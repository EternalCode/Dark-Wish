#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u16 RandRange(u16 min, u16 max);
extern void set_attack_bm_inplace(u16 moveId, u8 bank);
extern void ResetBankTurnBits(u8 bank);
extern u8 ShowAttackerAnimation;

enum TryHitMoveStatus move_tryhit(u8 attacker, u8 defender, u16 move)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_tryhit) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_TRYHIT_MOVE, 0, 0, i, (u32)abilities[ability].on_tryhit);
    }
    // add callbacks specific to field
    if (gBattleMoves[move].on_tryhit_move) {
        AddCallback(CB_ON_TRYHIT_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].on_tryhit_move);
    }
    // run callbacks
    BuildCallbackExecutionBuffer(CB_ON_TRYHIT_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        enum TryHitMoveStatus status = PopCallback(attacker, move);
        if (status != TRYHIT_USE_MOVE_NORMAL)
            return status;
    }
    return TRYHIT_USE_MOVE_NORMAL;
}


bool tryhit_semi_invulnerble(u8 attacker, u8 defender, u16 move)
{
    if (HAS_VOLATILE(defender, VOLATILE_SEMI_INVULNERABLE)) {
        // add callbacks specific to field
        u16 move = CURRENT_MOVE(attacker);
        if (gBattleMoves[move].on_inv_tryhit_move) {
            AddCallback(CB_ON_TRYHIT_INV_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].on_inv_tryhit_move);
        }
        // run callbacks
        u8 old_index = CB_EXEC_INDEX;
        u32* old_execution_array = push_callbacks();
        BuildCallbackExecutionBuffer(CB_ON_TRYHIT_INV_MOVE);
        gBattleMaster->executing = true;
        bool is_inv = true;
        while (gBattleMaster->executing) {
            if (!PopCallback(attacker, move)) {
                is_inv = false;
                break;
            }
        }
        restore_callbacks(old_execution_array);
        CB_EXEC_INDEX = old_index;
        if (is_inv) {
            // if user's move doesn't hit invulnerable target
            QueueMessage(0, attacker, STRING_INVULNERABLE, 0);
            // clear users volatiles if user used a 2 turn move and failed
            CLEAR_VOLATILE(attacker, VOLATILE_FLYING);
            CLEAR_VOLATILE(attacker, VOLATILE_BOUNCE);
            CLEAR_VOLATILE(attacker, VOLATILE_DIVE);
            CLEAR_VOLATILE(attacker, VOLATILE_DIG);
            CLEAR_VOLATILE(attacker, VOLATILE_SEMI_INVULNERABLE);
            struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
            a->action_bank = attacker;
            a->script = (u32)&ShowAttackerAnimation;
            return false;
        }
    }
    return true;
}


bool try_hit(u8 attacker)
{
    u16 move = CURRENT_MOVE(attacker);
    u8 defender = TARGET_OF(attacker);
    // if move fails under gravity, fail
    if (HAS_VOLATILE(attacker, VOLATILE_GRAVITY) && IS_GRAVITY(move)) {
        QueueMessage(move, attacker, STRING_FAILED, 0);
        return false;
    }

    // if move fails under heal block, fail
    if (HAS_VOLATILE(attacker, VOLATILE_HEAL_BLOCK) && IS_HEAL(move)) {
        QueueMessage(move, attacker, STRING_FAILED, 0);
        return false;
    }

    // if target is in semi invulnerability do checks
    if (!tryhit_semi_invulnerble(attacker, defender, move))
        return false;


    // if moves never misses, exit early
    u8 move_accuracy = B_MOVE_ACCURACY(attacker);
    if (move_accuracy > 100) {
        return true;
    }
    // OHKO moves have their own accuracy checks
    if (IS_OHKO(move))
        return true;
    // standard accuracy formula check
    u16 target_evasion;
    if (B_MOVE_IGNORE_EVASION(attacker))
        target_evasion = 100;
    else
        target_evasion = B_EVASION_STAT(defender);
    u16 user_accuracy = B_ACCURACY_STAT(attacker);

    u16 result = PERCENT(((user_accuracy * 100) / target_evasion),  move_accuracy);
    if (RandRange(0, 100) <= result || (gBattleMoves[move].multi_hit && gBattleMaster->b_moves[attacker].hit_counter < 3))
        return true;
    if (target_evasion > 100) {
        if (gBattleMoves[move].multi_hit && gBattleMaster->b_moves[attacker].hit_counter > 1)
            QueueMessage(0, 0, STRING_MULTI_HIT, gBattleMaster->b_moves[attacker].hit_counter - 1);
        else
            QueueMessage(0, defender, STRING_ATTACK_AVOIDED, 0);
    } else {
        if (gBattleMoves[move].multi_hit && gBattleMaster->b_moves[attacker].hit_counter > 1)
            QueueMessage(0, 0, STRING_MULTI_HIT, gBattleMaster->b_moves[attacker].hit_counter - 1);
        else
            QueueMessage(0, attacker, STRING_ATTACK_MISSED, 0);
    }
    // clear users volatiles if user used a 2 turn move and failed
    CLEAR_VOLATILE(attacker, VOLATILE_FLYING);
    CLEAR_VOLATILE(attacker, VOLATILE_BOUNCE);
    CLEAR_VOLATILE(attacker, VOLATILE_DIVE);
    CLEAR_VOLATILE(attacker, VOLATILE_DIG);
    CLEAR_VOLATILE(attacker, VOLATILE_SEMI_INVULNERABLE);
    struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
    a->action_bank = attacker;
    a->script = (u32)&ShowAttackerAnimation;
    return false;
}

void event_move_tryhit_external(struct action* current_action)
{
    u8 bank_index = current_action->action_bank;
    u16 move = current_action->move;
    CURRENT_MOVE(bank_index) = move;
    TARGET_OF(bank_index) = current_action->target;
    if (current_action->reset_move_config) {
        ResetBankTurnBits(bank_index);
        set_attack_bm_inplace(move, bank_index);
        current_action->reset_move_config = false;
    }
    /* Flinch interrupts move */
    if (RandRange(0, 100) < B_FLINCH(bank_index)) {
        QueueMessage(0, bank_index, STRING_FLINCHED, 0);
        //B_FLINCH(bank_index) = 0;
        CURRENT_ACTION->event_state = EventMoveFailed;
        for (u8 i = 0; i < BANK_MAX; i++) {
            u8 ability = gPkmnBank[i]->battleData.ability;
            if ((abilities[ability].on_flinch) && (ACTIVE_BANK(i)))
                AddCallback(CB_ON_FLINCH, 0, 0, i, (u32)abilities[ability].on_flinch);
        }
        // run callbacks
        BuildCallbackExecutionBuffer(CB_ON_FLINCH);
        bool temp_status = gBattleMaster->executing;
        gBattleMaster->executing = true;
        while (gBattleMaster->executing) {
            PopCallback(bank_index, move);
        }
        gBattleMaster->executing = temp_status;
        return;
    }

    // display "Pokemon used move!"
    if (!B_MOVE_MULTI(ACTION_BANK) || gBattleMaster->b_moves[ACTION_BANK].hit_counter == 1)
        QueueMessage(CURRENT_MOVE(ACTION_BANK), ACTION_BANK, STRING_ATTACK_USED, 0);

    /* Move tryhit callbacks */
    switch (move_tryhit(bank_index, TARGET_OF(bank_index), move)) {
        case TRYHIT_CANT_USE_MOVE:
            B_MOVE_FAILED(bank_index) = true;
            QueueMessage(move, bank_index, STRING_FAILED, move);
            break;
        case TRYHIT_TARGET_MOVE_IMMUNITY:
            B_MOVE_FAILED(bank_index) = true;
            QueueMessage(0, bank_index, STRING_MOVE_IMMUNE, 0);
            break;
        case TRYHIT_FAIL_SILENTLY:
            B_MOVE_FAILED(bank_index) = true;
            break;
        case TRYHIT_PASS:
            current_action->event_state++;
            return;
        default:
            break;
    };
    if (B_MOVE_FAILED(bank_index)) {
        CURRENT_ACTION->event_state = EventMoveFailed;
        return;
    }

    /* General tryhit move */
    if (try_hit(bank_index)) {
        current_action->event_state++;
    } else {
        CURRENT_ACTION->event_state = EventMoveFailed;
    }

}
