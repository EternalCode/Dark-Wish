#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void run_flee(void);
extern bool BankMonHasType(u8 bank, u8 type);
extern u16 RandRange(u16 min, u16 max);
extern void pkmn_recall_animation(void);
extern void SyncBankToParty(u8 bank);

bool bank_trapped(u8 bank)
{
    if (BankMonHasType(bank, TYPE_GHOST))
        return false;
    if (HAS_VOLATILE(bank, VOLATILE_TRAPPED) || HAS_VOLATILE(bank, VOLATILE_INGRAIN)) {
        return true;
    }
    return false;
}


/* Event switch related */
void move_on_switch_cb(u8 attacker)
{
    // add ability specific cbs
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].before_switch) && (ACTIVE_BANK(i)))
            add_callback(CB_ON_BEFORE_SWITCH, 0, 0, i, (u32)abilities[ability].before_switch);
    }
    u16 move = CURRENT_MOVE(attacker);
    // add callbacks specific to field
    if (moves[move].before_switch) {
        add_callback(CB_ON_BEFORE_SWITCH, 0, 0, attacker, (u32)moves[move].before_switch);
    }
    // run callbacks
    build_execution_order(CB_ON_BEFORE_SWITCH);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        pop_callback(attacker, move);
    }
}

void run_after_switch(u8 attacker)
{
    // update the bank data structure with the new Pokemon's stats

    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i)) {
            u8 ability = gPkmnBank[i]->battleData.ability;
            if (abilities[ability].on_start)
                add_callback(CB_ON_START, 0, 0, i, (u32)abilities[ability].on_start);
            u16 move = CURRENT_MOVE(i);
            if (moves[move].on_start)
                add_callback(CB_ON_START, 0, 0, i, (u32)moves[move].on_start);
        }
    }
    // run on start callbacks
    build_execution_order(CB_ON_START);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing)
        pop_callback(0xFF, NULL);
}


void event_on_start(struct action* current_action)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i)) {
            u8 ability = gPkmnBank[i]->battleData.ability;
            if (abilities[ability].on_start)
                add_callback(CB_ON_START, 0, 0, i, (u32)abilities[ability].on_start);
            u16 move = CURRENT_MOVE(i);
            if (moves[move].on_start)
                add_callback(CB_ON_START, 0, 0, i, (u32)moves[move].on_start);
        }
    }
    // run on start callbacks
    build_execution_order(CB_ON_START);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing)
        pop_callback(0xFF, NULL);
    end_action(CURRENT_ACTION);
}

void event_switch(struct action* current_action)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i)) {
            SyncBankToParty(i);
        }
    }
    gMain.state = 0;
    // the recall animation is in the switch scene folder; onlyplayer supported as of now
    SetMainCallback(pkmn_recall_animation);
}


void event_switch_mid_battle(struct action* current_action)
{
    move_on_switch_cb(ACTION_BANK);
    QueueMessage(MOVE_NONE, ACTION_BANK, STRING_RETREAT_MON, 0);
    prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventForcedSwitch);
}

void event_pre_switch(struct action* current_action)
{
    if (bank_trapped(ACTION_BANK)) {
        QueueMessage(MOVE_NONE, ACTION_BANK, STRING_TRAPPED, 0);
        end_action(CURRENT_ACTION);
        return;
    } else {
        move_on_switch_cb(ACTION_BANK);
        QueueMessage(MOVE_NONE, ACTION_BANK, STRING_RETREAT_MON, 0);
        CURRENT_ACTION->event_state++;
    }
}


/* Event flee related */
bool can_flee_by_random(u8 bank)
{
    // TODO: How does the flee formula change in doubles?
    gPkmnBank[bank]->battleData.flee_count++;

    u16 reference = B_SPEED_STAT_UMOD(bank) * 128;
    reference /= B_SPEED_STAT_UMOD((bank ? 0 : 2));
    reference += (30 * gPkmnBank[bank]->battleData.flee_count);
    reference = reference & 0xFF;

    u16 random = RandRange(0,255);
    return random < reference;
}


void event_run_flee(struct action* current_action)
{
    if (!can_flee_by_random(ACTION_BANK)) {
        // we cannot flee because we failed the dice roll
        dprintf("failed to run\n");
        QueueMessage(MOVE_NONE, ACTION_BANK, STRING_FLEE_FAILED, 0);
        end_action(current_action);
    } else {
        // flee the battle
        dprintf("successful run\n");
        QueueMessage(MOVE_NONE, ACTION_BANK, STRING_FLEE, 0);
        prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventEndBattle);
        end_action(current_action);
    }
}
