#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern u16 RandRange(u16 min, u16 max);
extern void dprintf(const char * str, ...);
extern u8 BankCountUsableMoves(u8 bank);
extern u8 BankMoveCount(u8 bank);
extern bool BankCanUseMove(u8 bank, u16 move);
extern u8 CountBankMovePP(u16 moveId, u8 bank);
extern u8 GetMoveIndexBank(u16 moveId, u8 bank);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern s8 GetMovePriority(u8 bank);

/* These following 3 functions are used to determine which order that Pokemon actions
 * are queued into the actions list
 */
u8 compare_bank_speeds(u8 a, u8 b)
{
    u16 a_speed = B_SPEED_STAT(a);
    u16 b_speed = B_SPEED_STAT(b);
    if (a_speed == b_speed) {
        return (RandRange(0, 1)) ? a : b;
    } else if (a_speed < b_speed) {
        return b;
    } else {
        return a;
    }
}


u8 compare_bank_priority(u8 a, u8 b)
{
    extern s8 GetMovePriority(u8 bank);
    s8 a_priority = GetMovePriority(a);
    s8 b_priority = GetMovePriority(b);
    if (a_priority == b_priority) {
        return (compare_bank_speeds(a, b));
    } else if (a_priority < b_priority) {
        return b;
    } else {
        return a;
    }
}

void SortBanksBySpeed(u8* active_banks, u8 index)
{
    // sort active banks
    for (u8 i = 0; i < index; i++) {
        if (active_banks[i] == 0x3F)
            break;
        u8 fastest = i;
        for (u8 j = i + 1; j < index; j++) {
            if (active_banks[j] == 0x3F)
                break;
            u8 result = compare_bank_priority(active_banks[fastest], active_banks[j]);
            if (result != active_banks[fastest]) {
                fastest = j;
            }
        }
        u8 temp = active_banks[i];
        active_banks[i] = active_banks[fastest];
        active_banks[fastest] = temp;
    }
}

void CreateActionsForActiveBanks()
{
    u8 active_banks[4] = {0x3F, 0x3F, 0x3F, 0x3F};
    u8 index = 0;
    for (u8 i = 0 ; i < BANK_MAX; i++) {
        if (gPkmnBank[i]->battleData.is_active_bank) {
            active_banks[index] = i;
            index++;
        }
    }
    SortBanksBySpeed(&active_banks[0], index);
    /* Before turn callbacks */
    for (u8 i = 0; i < 4; i++) {
        gBattleMaster->bankOrder[i] = active_banks[i];
        if (active_banks[i] == 0x3F) continue;
        // add ability specific cbs
        u8 ability = gPkmnBank[active_banks[i]]->battleData.ability;
        if (abilities[ability].before_turn)
            add_callback(CB_ON_BEFORE_TURN, 0, 0, active_banks[i], (u32)abilities[ability].before_turn);

        u16 move = CURRENT_MOVE(active_banks[i]);
        if (moves[move].before_turn)
            add_callback(CB_ON_BEFORE_TURN, 0, 0, active_banks[i], (u32)moves[move].before_turn);
    }
    build_execution_order(CB_ON_BEFORE_TURN);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        u8 attacker = CB_MASTER[CB_EXEC_ORDER[CB_EXEC_INDEX]].source_bank;
        u16 move = CURRENT_MOVE(CB_MASTER[CB_EXEC_ORDER[CB_EXEC_INDEX]].source_bank);
        pop_callback(attacker, move);
    }
    // before turn could've changed the priorities
    SortBanksBySpeed(&active_banks[0], index);
    for (u8 i = 0; i < index; i++) {
        if (gPkmnBank[active_banks[i]]->battleData.isRunning) {
            add_action(active_banks[i], active_banks[i], ActionRun, EventFlee);
        } else if (gPkmnBank[active_banks[i]]->battleData.isSwitching) {
            add_action(active_banks[i], active_banks[i], ActionSwitch, EventPreSwitch);
        } else {
            // action's target is developed later
            struct action *a = add_action(active_banks[i], NULL, ActionMove, EventBeforeMove);
            a->move = CURRENT_MOVE(active_banks[i]);
        }
        gPkmnBank[active_banks[i]]->battleData.will_move = true;
        B_FLINCH(active_banks[i]) = 0;
    }
    /* Add turn end effects as actions */
    struct action* r = add_action(0xFF, 0xFF, ActionResidual, EventResidualEffects);
    r->active_override = true;
    struct action* bo = add_action(0xFF, 0xFF, ActionHighPriority, EventWildBattleOver);
    bo->active_override = true;
}


u16 BankInterpretSelectedMove(u8 bank)
{
    if (gPkmnBank[bank]->battleData.isRunning)
        return MOVE_NONE;
    if (gPkmnBank[bank]->battleData.isSwitching)
        return MOVE_NONE;
    if (gPkmnBank[bank]->battleData.skip_move_select)
        return LAST_MOVE(bank);
    u16 move_slot = gBattleMaster->battle_cursor.cursor_pos;
    if (move_slot == 1) {
        move_slot += 1;
    } else if (move_slot == 2) {
        move_slot -= 1;
    }
    gPkmnBank[bank]->battleData.pp_index = move_slot;
    return (B_GET_MOVE(bank, move_slot));
}

bool external_move_disable_callbacks(u8 bank, u16 move)
{
    // callbacks for external move disables
    build_execution_order(CB_ON_DISABLE_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        // if a move is successfully disabled, the child should return false to halt
        if (!pop_callback(bank, move)) {
            // this is to stoping moves in multi turn is left to the child callback.
            // some moves like disable stop them, but moves like torment do not
            gBattleMaster->executing = false;
            return false;
        }
    }
    return true;
}

// Return True = Continue; False = Reset
bool ValidateBankMove(u8 bank)
{
    // get and set currently selected move
    u16 move_player = CURRENT_MOVE(bank);

    // if player is fleeing, don't use a move
    if (gPkmnBank[bank]->battleData.isRunning || gPkmnBank[bank]->battleData.isSwitching) {
        CURRENT_MOVE(bank) = MOVE_NONE;
        gPkmnBank[bank]->battleData.pp_index = 0xFF;
        return true;
    }

    // if player doesn't have an available move, struggle instead
    u8 index = 0;
    for (u8 i = 0; i < 4; i++) {
        // if move is usable insert to array
        u16 selected_move = B_GET_MOVE(bank, i);
        if (BankCanUseMove(bank, selected_move)) {
            if (external_move_disable_callbacks(bank, selected_move)) {
                index++;
            }
        }
    }
    // delete actions
    clear_actions();
    ACTION_HEAD = NULL;

    if (index < 1) {
        // all moves disabled or unpickable
        CURRENT_MOVE(bank) = MOVE_STRUGGLE;
        B_MOVE_CAN_CRIT(bank) = false;
        gPkmnBank[bank]->battleData.pp_index = 0xFF;
        return true;
    }

    // ensure player has PP for move being used
    if (CountBankMovePP(move_player, bank) < 1) {
        QueueMessage(0, 0, STRING_NO_PP, 0);
        return false;
    }
    B_MOVE_CAN_CRIT(bank) = true;
    return external_move_disable_callbacks(bank, move_player);
}

void WildBattleAIPickMove(u8 bank)
{
    // If bank is attempting to flee, don't queue a move
    if (gPkmnBank[bank]->battleData.isRunning) {
        CURRENT_MOVE(bank) = MOVE_NONE;
        gPkmnBank[bank]->battleData.pp_index = 0xFF;
        return;
    }

    // if AI is locked into current move, use that move instead
    if (gPkmnBank[bank]->battleData.skip_move_select) {
        CURRENT_MOVE(bank) = LAST_MOVE(bank);
        return;
    }

    // if AI is charging or recharging, don't use a move
    if (HAS_VOLATILE(bank, VOLATILE_CHARGING) || HAS_VOLATILE(bank, VOLATILE_RECHARGING)) {
        // use move was using last time.
        return;
    }

    // pick a valid move for the AI
    u16 to_pick[4] = {0};
    u8 index = 0;
    for (u8 i = 0; i < 4; i++) {
        // if move is usable insert to array
        u16 selected_move = B_GET_MOVE(bank, i);
        if (BankCanUseMove(bank, selected_move)) {
            if (external_move_disable_callbacks(bank, selected_move)) {
                to_pick[index] = selected_move;
                index++;
            }
        }
    }
    if (index < 1) {
        // all moves disabled or unpickable
        CURRENT_MOVE(bank) = MOVE_STRUGGLE;
        B_MOVE_CAN_CRIT(bank) = false;
        gPkmnBank[bank]->battleData.pp_index = 0xFF;
        return;
    }

    u16 rand_index = RandRange(0, index);
    CURRENT_MOVE(bank) = to_pick[rand_index];
    gPkmnBank[bank]->battleData.pp_index = GetMoveIndexBank(to_pick[rand_index], bank);
    B_MOVE_CAN_CRIT(bank) = true;
    return;
}

void ResetBankTurnBits(u8 bank)
{
    gPkmnBank[bank]->battleData.isRunning = false;
    gPkmnBank[bank]->battleData.isSwitching = false;
    gPkmnBank[bank]->battleData.first_turn = false;
    memset((void*)(&gBattleMaster->b_moves[(bank)]), 0x0, sizeof(struct move_used));
    gPkmnBank[bank]->battleData.last_damage = 0;
    B_LAST_MOVE_FAILED(bank) = B_MOVE_FAILED(bank);
    B_MOVE_FAILED(bank) = false;
	CLEAR_VOLATILE(bank, VOLATILE_PRANKSTERED);

}

void set_attack_bm_inplace(u16 moveId, u8 bank)
{
    gBattleMaster->b_moves[bank].user_bank = bank;
    gBattleMaster->b_moves[bank].moveId = moveId;
    gBattleMaster->b_moves[bank].priority = B_MOVE_PRIORITY(bank);
    gBattleMaster->b_moves[bank].stab = 150; // move stab bonus
    gBattleMaster->b_moves[bank].power = MOVE_POWER(moveId);
    gBattleMaster->b_moves[bank].category = MOVE_CATEGORY(moveId);
    gBattleMaster->b_moves[bank].type[0] = MOVE_TYPE(moveId);
    gBattleMaster->b_moves[bank].type[1] = MTYPE_EGG;
    gBattleMaster->b_moves[bank].flinch = M_FLINCH(moveId);
    gBattleMaster->b_moves[bank].accuracy = MOVE_ACCURACY(moveId);
    gBattleMaster->b_moves[bank].makes_contact = (IS_CONTACT(moveId) != 0);
    gBattleMaster->b_moves[bank].ignore_abilities = false;
    gBattleMaster->b_moves[bank].heal = moves[moveId].heal;
    gBattleMaster->b_moves[bank].infiltrates = false;
    if (moves[moveId].multi_hit[0]) {
        u8 hit_times = 0;
        if ((moves[moveId].multi_hit[0] == 2) && (moves[moveId].multi_hit[1] == 5)) {
            switch(RandRange(0, 3)) {
                case 0:
                    hit_times = 2;
                    break;
                case 1:
                    hit_times = 3;
                    break;
                case 2:
                    hit_times = RandRange(4, 6);
                    break;
            };
        } else {
            if (moves[moveId].multi_hit[0] == moves[moveId].multi_hit[1]) {
                hit_times = moves[moveId].multi_hit[1];
            } else {
                hit_times = RandRange(moves[moveId].multi_hit[0], moves[moveId].multi_hit[1]);
                hit_times |= 1;
            }
        }
        gBattleMaster->b_moves[bank].hit_times = hit_times - 1;
        gBattleMaster->b_moves[bank].hit_counter = 1;
    }
    B_MOVE_CAN_CRIT(bank) = true;
    B_MOVE_WILL_CRIT(bank) = false;
    B_MOVE_DMG(bank) = 0;
    B_MOVE_EFFECTIVENESS(bank) = 0;
    if (!HAS_ABILITY_FLAG(BANK_ABILITY(bank), A_FLAG_SECONDARIES_PREVENT)) {
        gBattleMaster->b_moves[bank].b_procs = *(moves[moveId].procs);
    } else {
        gBattleMaster->b_moves[bank].flinch = 0;

    }
}
