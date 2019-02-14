#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "actions.h"

extern void dprintf(const char * str, ...);
extern u16 RandRange(u16 min, u16 max);

void clear_actions()
{
    struct action* head = ACTION_HEAD;
    while(true) {
        if (head == NULL) return;
        struct action* next = head->next_action;
        free(head);
        head = next;
    }
}

void debug_print_action_banks()
{
    struct action* a = ACTION_HEAD;
    if (a == NULL) {
        dprintf("Action Head - NULL!\n");
        return;
    }
    dprintf("head: %d\n", a->action_bank);
    while(a != NULL) {
        dprintf("action bank is %d\n", a->action_bank);
        a = a->next_action;
    }
}

struct action* add_action(u8 bank, u8 target, u8 type, u8 event_state)
{
    /* initialize action to insert */
    struct action* new_action = (struct action*)malloc_and_clear(sizeof(struct action));
    new_action->action_bank = bank;
    new_action->target = target;
    new_action->type = type;
    new_action->event_state = event_state;
    new_action->next_action = NULL;
    new_action->prev_action = NULL;
    /* insert into next available location on linked list */
    struct action** this_action = &(ACTION_HEAD);
    if (*(this_action) == NULL) {
        (*this_action) = new_action;
    } else {
        while (true) {
            if ((*this_action)->next_action == NULL) {
                (*this_action)->next_action = new_action;
                new_action->prev_action = (*this_action);
                break;
            } else {
                this_action = &(*this_action)->next_action;
            }
        }
    }
    return new_action;
}

/* Prepend is done at the current event's current action */
struct action* prepend_action(u8 bank, u8 target, u8 type, u8 event_state)
{
    /* initialize action to insert */
    struct action* new_action = (struct action*)malloc_and_clear(sizeof(struct action));
    new_action->action_bank = bank;
    new_action->target = target;
    new_action->type = type;
    new_action->event_state = event_state;
    /* insert into slot before head */
    new_action->next_action = CURRENT_ACTION;
    new_action->prev_action = CURRENT_ACTION->prev_action;
    CURRENT_ACTION->prev_action = new_action;
    new_action->prev_action->next_action = new_action;
    if (CURRENT_ACTION == ACTION_HEAD)
        ACTION_HEAD = new_action;
    return new_action;
}

struct action* next_action(u8 bank, u8 target, u8 type, u8 event_state)
{
    /* initialize action to insert */
    struct action* new_action = (struct action*)malloc_and_clear(sizeof(struct action));
    new_action->action_bank = bank;
    new_action->target = target;
    new_action->type = type;
    new_action->event_state = event_state;
    /* insert into slot after current action */
    if (CURRENT_ACTION == NULL) {
        ACTION_HEAD = new_action;
    } else {
        new_action->next_action = CURRENT_ACTION->next_action;
        new_action->prev_action = CURRENT_ACTION;
        CURRENT_ACTION->next_action = new_action;
        new_action->next_action->prev_action = new_action;
    }
    return new_action;
}


void end_action(struct action* to_delete)
{
    if (to_delete == NULL)
        return;
    struct action* prev = to_delete->prev_action;
    struct action* next = to_delete->next_action;
    if (prev != NULL) {
        prev->next_action = next;
    }

    if (next != NULL) {
        next->prev_action = prev;
    }

    if (to_delete == ACTION_HEAD)
        ACTION_HEAD = next;
    free(to_delete);
}


struct action* find_action(u8 bank, enum ActionTiming type)
{
    struct action* a = ACTION_HEAD;
    if (a == NULL) {
        dprintf("Action Head - NULL!\n");
        return NULL;
    }
    while(a != NULL) {
        if ((a->action_bank == bank) && (a->type == type)) {
            return a;
        }
        a = a->next_action;
    }
    return NULL;
}
