#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern void battle_loop(void);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);

struct action *stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank)
{
    struct action *a = prepend_action(inflicting_bank, bank, ActionStatBoost, EventStatBoost);
    a->priv[0] = stat_id;
    a->priv[1] = amount;
    return a;
}

void event_stat_boost(struct action* current_action)
{
    s8 *new_amount = (s8 *)(&(current_action->priv[1]));
    if  (*new_amount == 0) {
        end_action(CURRENT_ACTION);
        return;
    }
    u8 bank = current_action->target; // bank to be boosted is the target
    u8 stat_id = current_action->priv[0];
    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    bool executor_backup = gBattleMaster->executing;
    for(u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_stat_boost_mod) && (ACTIVE_BANK(i))) {
            AddCallback(CB_ON_STAT_BOOST_MOD, 0, 0, i, (u32)abilities[ability].on_stat_boost_mod);
        }
    }

    // execute cbs
    BuildCallbackExecutionBuffer(CB_ON_STAT_BOOST_MOD);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        if (!PopCallback(bank, stat_id)) {
            QueueMessage(CURRENT_MOVE(bank), bank, STRING_FAILED_ALONE, NULL);
            gBattleMaster->executing = executor_backup;
            restore_callbacks(old_execution_array);
            CB_EXEC_INDEX = old_index;
            end_action(CURRENT_ACTION);
            return;
        };
    }

    gBattleMaster->executing = executor_backup;
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;

    s8* stat_stored;
    switch (stat_id) {
        case STAT_ATTACK:
            stat_stored = &(gPkmnBank[bank]->battleData.attack);
            break;
        case STAT_DEFENSE:
            stat_stored = &(gPkmnBank[bank]->battleData.defense);
            break;
        case STAT_SPEED:
            stat_stored = &(gPkmnBank[bank]->battleData.speed);
            break;
        case STAT_SPECIAL_ATTACK:
            stat_stored = &(gPkmnBank[bank]->battleData.sp_atk);
            break;
        case STAT_SPECIAL_DEFENSE:
            stat_stored = &(gPkmnBank[bank]->battleData.sp_def);
            break;
        case STAT_EVASION: // evasion
            stat_stored = &(gPkmnBank[bank]->battleData.evasion);
            break;
        case STAT_ACCURACY: // accuracy
            stat_stored = &(gPkmnBank[bank]->battleData.accuracy);
            break;
        case STAT_CRIT: // crit
            stat_stored = &(gPkmnBank[bank]->battleData.crit_mod);
            break;
        default:
            end_action(CURRENT_ACTION);
            return;
    };

    s8 stat_total = *stat_stored + *new_amount;
    stat_total = MIN(6, stat_total);
    stat_total = MAX(-6, stat_total);
    u8 delta = (ABS(stat_total - (*stat_stored)));
    switch (delta) {
        case 0:
           // stat didn't change - string can't go up/down anymore
            if (*new_amount > 0) {
                QueueMessage(0, bank, STRING_STAT_MOD_CANT_GO_HIGHER, stat_id + REQUEST_ATK);
            } else {
                QueueMessage(0, bank, STRING_STAT_MOD_CANT_GO_LOWER, stat_id + REQUEST_ATK);
            }
            break;
        case 1:
            // stat changed by 1 stage
            *stat_stored += (*new_amount > 0) ? delta : -delta;
            if (*new_amount > 0) {
                dprintf("\ntrying to queue the stat went up string...\n\n");
                QueueMessage(0, bank, STRING_STAT_MOD_RISE, stat_id + REQUEST_ATK);
            } else {
                QueueMessage(0, bank, STRING_STAT_MOD_DROP, stat_id + REQUEST_ATK);
            }
            break;
        case 2:
            // stat changed by 2 stages
            *stat_stored += (*new_amount > 0) ? delta : -delta;
            if (*new_amount > 0) {
                QueueMessage(0, bank, STRING_STAT_MOD_HARSH_RISE, stat_id + REQUEST_ATK);
            } else {
                QueueMessage(0, bank, STRING_STAT_MOD_HARSH_DROP, stat_id + REQUEST_ATK);
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            // stat changed by >=3 stages
            *stat_stored += (*new_amount > 0) ? delta : -delta;
            if (*new_amount > 0) {
                QueueMessage(0, bank, STRING_STAT_MOD_ROSE_DRASTICALLY, stat_id + REQUEST_ATK);
            } else {
                QueueMessage(0, bank, STRING_STAT_MOD_SEVERELY_FELL, stat_id + REQUEST_ATK);
            }
            break;
        default:
            break;

    };


    old_execution_array = push_callbacks();
    for(u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].after_stat_boost_mod) && (ACTIVE_BANK(i))) {
            AddCallback(CB_AFTER_STAT_BOOST_MOD, 0, 0, i, (u32)abilities[ability].after_stat_boost_mod);
        }
    }

    BuildCallbackExecutionBuffer(CB_AFTER_STAT_BOOST_MOD);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        PopCallback(bank, stat_id);
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    gBattleMaster->executing = executor_backup;
    end_action(CURRENT_ACTION);
}
