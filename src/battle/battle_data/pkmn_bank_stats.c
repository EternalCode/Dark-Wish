#include <pokeagb/pokeagb.h>
#include "pkmn_bank.h"
#include "battle_state.h"
#include "pkmn_bank_stats.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "../status_effects/status.h"

extern void dprintf(const char * str, ...);
typedef u16 (*StatCallback)(u8, u16);


/*
 * Returns the stat after stage modifications have been done. Id represents which stat has been modified
 * 0 - atk; 1 - def; 2 - speed; 3 - spatk; 4 - spdef; 5 - accuracy; 6 - evasion; 7 - Crit chance
 */
const static u16 stat_mod[13] = {25, 29, 33, 40, 50, 67, 100, 150, 200, 250, 300, 350, 400};
const static u16 acc_mod[13] = {33, 38, 43, 50, 60, 75, 100, 133, 167, 200, 233, 266, 300};
const static u8 crit_mod[4] = {6, 13, 50, 100};

u16 stage_modify_stat(u16 stat, s8 mod, u8 id, u8 bank)
{
    u16 stat_total;

    /* atk, def, spd, spa, spdef */
    if (id < 5) {
        stat_total = PERCENT(stat, stat_mod[mod + 6]);
    } else if (id < 7) {
        /* Accuracy and Evasion */
        stat_total = acc_mod[mod + 6];
    } else {
        /* crit chance */
        stat_total = (mod > sizeof(crit_mod)) ? crit_mod[sizeof(crit_mod) - 1]: crit_mod[mod];
    }

    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i)) {
            u8 ability = gPkmnBank[i]->battleData.ability;
            if (abilities[ability].on_stat)
                add_callback(CB_ON_STAT_MOD, 0, 0, i, (u32)abilities[ability].on_stat);
        }
    }

    // back up cbs
    u32* old_execution_array = push_callbacks();
    u8 old_index = CB_EXEC_INDEX;
    bool execution_status = gBattleMaster->executing;
    // Stat modifying callbacks
    build_execution_order(CB_ON_STAT_MOD);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        set_data_next_acb(stat_total);
        u16 new_total = pop_callback(bank, id);
        if (new_total != 1) {
            stat_total = new_total;
        }
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    gBattleMaster->executing = execution_status;
    return stat_total;
}


bool has_volatile(u8 bank, enum Volatiles v)
{
    u32* byte_index = &(gPkmnBank[bank]->battleData.v_status);
    u8 shift_amount = (u8)v;
    if (shift_amount > 31) {
        byte_index++;
        shift_amount -= 32;
    }
    return (1 & ((*byte_index) >> shift_amount));
}

void clear_volatile(u8 bank, enum Volatiles v)
{
    u32* byte_index = &(gPkmnBank[bank]->battleData.v_status);
    u8 shift_amount = (u8)v;
    if (shift_amount > 31) {
        byte_index++;
        shift_amount -= 32;
    }
    *byte_index &= ~(1 << shift_amount);
}

void add_volatile(u8 bank, enum Volatiles v)
{
    u32* byte_index = &(gPkmnBank[bank]->battleData.v_status);
    u8 shift_amount = (u8)v;
    if (shift_amount > 31) {
        byte_index++;
        shift_amount -= 32;
    }
    *byte_index |= (1 << shift_amount);
}
