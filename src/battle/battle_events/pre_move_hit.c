#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern void ResetBankTurnBits(u8 bank);
extern void set_attack_bm_inplace(u16 moveId, u8 bank);
extern bool UpdateBankHitList(u8 bank_index);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

bool on_modify_move(u8 attacker, u8 defender, u16 move)
{
    // add ability specific cbs
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_modify_move) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_MODIFY_MOVE, 0, 0, i, (u32)abilities[ability].on_modify_move);
    }
    // add callbacks specific to field
    if (gBattleMoves[move].on_modify_move) {
        AddCallback(CB_ON_MODIFY_MOVE, 0, 0, attacker, (u32)gBattleMoves[move].on_modify_move);
    }
    // run callbacks
    BuildCallbackExecutionBuffer(CB_ON_MODIFY_MOVE);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        if (!(PopCallback(attacker, move)))
            return false;
    }
    return true;
}


void event_config_move_hitlist(struct action* current_action)
{
    dprintf("running event config move hitlist\n");
    if (!UpdateBankHitList(ACTION_BANK)) {
        // Move didn't specify a target
        QueueMessage(0, ACTION_BANK, STRING_FAILED, 0);
        CURRENT_ACTION->event_state = EventMoveFailed;
        return;
    }
    // reduce PP
    if ((!HAS_VOLATILE(ACTION_BANK, VOLATILE_MULTI_TURN)) && (!B_REDUCE_PP(ACTION_BANK))) {
        u8 pp_index = gPkmnBank[ACTION_BANK]->battleData.pp_index;
        if (pp_index < 4) {
            gPkmnBank[ACTION_BANK]->battleData.move_pp[pp_index]--;
        }
    }
    current_action->event_state++;
}


void event_pre_move_hit(struct action* current_action)
{
    dprintf("running event pre move hit\n");
    bool will_move = false;
    u8 bank_index = current_action->action_bank;
    // check if hit list has a bank to hit. Mark said bank as hit and continue
    for (u8 i = 0; i < sizeof(gBattleMaster->bank_hit_list); i++) {
        if (gBattleMaster->bank_hit_list[i] < BANK_MAX) {
            if (ACTIVE_BANK(gBattleMaster->bank_hit_list[i])) {
                TARGET_OF(bank_index) = gBattleMaster->bank_hit_list[i];
                CURRENT_ACTION->target = gBattleMaster->bank_hit_list[i];
                gBattleMaster->bank_hit_list[i] = BANK_MAX;
                will_move = true;
                break;
            } else {
                if (battle_type_flag == BATTLE_MODE_WILD) {
                    if (B_FAINTED(gBattleMaster->bank_hit_list[i])) {
                        QueueMessage(0, bank_index, STRING_NO_TARGET, 0);
                        CURRENT_ACTION->event_state = EventMoveFailed;
                    }
                }
                gBattleMaster->bank_hit_list[i] = BANK_MAX;
            }
        }
    }

    // if there was a bank to hit, prepare data structures
    if (will_move) {
        // reset battle master move structure for this move
        CURRENT_MOVE(ACTION_BANK) = CURRENT_ACTION->move;
        if (current_action->reset_move_config) {
            ResetBankTurnBits(bank_index);
            current_action->reset_move_config = false;
        }
        set_attack_bm_inplace(CURRENT_MOVE(bank_index), bank_index);
        if (!on_modify_move(bank_index, TARGET_OF(bank_index), CURRENT_MOVE(bank_index))) {
            B_MOVE_FAILED(bank_index) = true;
            QueueMessage(0, bank_index, STRING_FAILED, 0);
            CURRENT_ACTION->event_state = EventMoveFailed;
            return;
        }
        CURRENT_ACTION->event_state++;
    } else {
        CURRENT_ACTION->event_state = EventMoveAfterMove;
    }
}
