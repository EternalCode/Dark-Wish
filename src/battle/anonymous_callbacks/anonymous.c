#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void sort_priority_cbs(void);
extern bool has_callback_src(u32 func, u8 src);

// insert a new anonymous callback
u8 AddCallback(u8 CB_id, s8 priority, u8 dur, u8 src, u32 func)
{
    if (has_callback_src(func, src)) {
        dprintf("WARNING: DUPLICATE FUNCTION %x WAS NOT ADDED TO BANK %d\n", func, src);
        return ANON_CB_MAX;
    }
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if (!(CB_MASTER[i].in_use)) {
            // initialize new callback here
            CB_MASTER[i].priority = priority;
            CB_MASTER[i].delay_before_effect = 0;
            CB_MASTER[i].in_use = true;
            CB_MASTER[i].duration = dur;
            CB_MASTER[i].source_bank = src;
            CB_MASTER[i].cb_id = CB_id;
            CB_MASTER[i].data_ptr = 0;
            CB_MASTER[i].func = func;
            return i;
        }
    }
    dprintf("WARNING, CALLBACKS ARRAY FULL ADDING CALLBACK %x!\n", func);
    return ANON_CB_MAX;
}

// execution order building before executing a specific type of CB
void BuildCallbackExecutionBuffer(u8 CB_id) {
    CB_EXEC_INDEX = 0;
    sort_priority_cbs();
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].cb_id != CB_id) || (!CB_MASTER[i].in_use) || (CB_MASTER[i].delay_before_effect)) {
            continue;
        } else {
            CB_EXEC_ORDER[CB_EXEC_INDEX] = i;
            CB_EXEC_INDEX++;
        }
    }
    CB_EXEC_ORDER[CB_EXEC_INDEX] = ANON_CB_MAX;
    CB_EXEC_INDEX = 0;
}

// Run the next callback in the built list
u16 PopCallback(u8 attacker, u16 move) {
    u8 i = CB_EXEC_ORDER[CB_EXEC_INDEX];
    if (i != ANON_CB_MAX) {
        i = CB_EXEC_ORDER[CB_EXEC_INDEX];
        CB_EXEC_INDEX++;
        // catch case where other callback deleted/delayed this one
        if ((CB_MASTER[i].in_use == false) || (CB_MASTER[i].delay_before_effect > 0)) return true;
        AnonymousCallback func = (AnonymousCallback)CB_MASTER[i].func;
        gBattleMaster->executing = true;
        dprintf("executing a function at %x\n", CB_MASTER[i].func -1);
        return func(attacker, CB_MASTER[i].source_bank, move, &CB_MASTER[i]);

    }
    // callbacks are done executing here
    gBattleMaster->executing = false;
    CB_EXEC_INDEX = 0;
    return true;
}

// run current callback
u16 run_callback(u8 attacker, u16 move) {
    u8 i = CB_EXEC_ORDER[CB_EXEC_INDEX];
    if (i != ANON_CB_MAX) {
        i = CB_EXEC_ORDER[CB_EXEC_INDEX];
        // catch case where other callback deleted this one
        if ((CB_MASTER[i].in_use == false) || (CB_MASTER[i].delay_before_effect > 0)) return true;
        AnonymousCallback func = (AnonymousCallback)CB_MASTER[i].func;
        gBattleMaster->executing = true;
        dprintf("executing a function at %x\n", CB_MASTER[i].func -1);
        return func(attacker, CB_MASTER[i].source_bank, move, &CB_MASTER[i]);
    }
    gBattleMaster->executing = false;
    CB_EXEC_INDEX = 0;
    return true;
}

// list built callbacks
void list_cbs()
{
    dprintf("Runnable functions include: \n");
    for (u8 i = 0; ((i < ANON_CB_MAX) && (CB_EXEC_ORDER[i] < 40)); i++) {
        dprintf("func: %x\n", CB_MASTER[CB_EXEC_ORDER[i]].func);
        dprintf("func index: %x\n", CB_EXEC_ORDER[i]);
    }
}

// turn end, drop counters of array elements
void update_callbacks() {
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        // Count down turn delay
        if (!CB_MASTER[i].in_use) continue;
        if (CB_MASTER[i].delay_before_effect) {
            CB_MASTER[i].delay_before_effect--;
        } else {
            // Count down duration if delay done
            if (CB_MASTER[i].duration > 0) {
                if (CB_MASTER[i].duration < 0xFF)
                    CB_MASTER[i].duration--;
            } else {
                CB_MASTER[i].in_use = false;
            }
        }
    }
    sort_priority_cbs();
}


/* Array sorting by struct element Priority */
void callbacks_swap(u8 i, u8 j)
{
    struct anonymous_callback temp = CB_MASTER[i];
    CB_MASTER[i] = CB_MASTER[j];
    CB_MASTER[j] = temp;
    return;
}

void sort_priority_cbs()
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        for (u8 j = i + 1; j < ANON_CB_MAX; j++) {
            if (ELE_NULL(i) && ELE_USED(j)) {
                callbacks_swap(i, j);
            } else if (ELE_USED(i) && ELE_USED(j)) {
                if (ANON_PRIORITY(i) < ANON_PRIORITY(j)) {
                    callbacks_swap(i, j);
                }
            }
        }
    }
}


u8 id_by_func(u32 func)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true))
            return i;
    }
    return 255;
}

void delete_callback(u32 func)
{
    u8 id = id_by_func(func);
    if (id != 255)
        CB_MASTER[id].in_use = false;
}


void delete_callback_src(u32 func, u8 src)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true) &&
         (CB_MASTER[i].source_bank == src)) {
            CB_MASTER[i].in_use = false;
        }
    }
}

void delete_callback_side(u32 func, u8 side)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true) &&
         (SIDE_OF(CB_MASTER[i].source_bank) == side)) {
            CB_MASTER[i].in_use = false;
        }
    }
}

bool has_callback_src(u32 func, u8 src)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true) &&
         (CB_MASTER[i].source_bank == src)) {
            return true;
        }
    }
    return false;
}

u8 get_callback_src(u32 func, u8 src)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true) &&
         (CB_MASTER[i].source_bank == src)) {
            return i;
        }
    }
    return ANON_CB_MAX;
}

void set_data_next_acb(u32 data) {
    u8 i = CB_EXEC_ORDER[CB_EXEC_INDEX];
    if (i != ANON_CB_MAX) {
        CB_MASTER[i].data_ptr = data;
    }
}

bool callback_exists(u32 func)
{
    return (id_by_func(func) < 255);
}


u8 callback_exists_side(u32 func, u8 side)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((CB_MASTER[i].func == func) && (CB_MASTER[i].in_use == true) &&
         (SIDE_OF(CB_MASTER[i].source_bank) == side)) {
            return true;
        }
    }
    return false;
}

u32* push_callbacks()
{
    u32* data_ptr = (u32*)malloc_and_clear(ANON_CB_MAX);
    memcpy(data_ptr, &CB_EXEC_ORDER[0], ANON_CB_MAX);
    return data_ptr;
}

void restore_callbacks(u32* data_ptr)
{
    memcpy(&CB_EXEC_ORDER[0], data_ptr, ANON_CB_MAX);
    free(data_ptr);
}


u8 id_by_acb(struct anonymous_callback* acb)
{
    for (u8 i = 0; i < ANON_CB_MAX; i++) {
        if ((u32)acb == ((u32)&CB_MASTER[i]))
            return i;
    }
    return ANON_CB_MAX;
}
