#ifndef GAME_ACTIONS_H_
#define GAME_ACTIONS_H_

#include <pokeagb/pokeagb.h>

/* The timings only serve as identifiers. Nothing more */
enum ActionTiming {
    ActionMove = 0, // Make a move
    ActionSwitch, // Make a switch
    ActionRun, // Attempt Flee
    ActionFaint, // Faint a bank
    ActionText, // Display game text
    ActionDamage, // Do damage
    ActionHeal, // Do heal
    ActionStatus,
    ActionResidual,
    ActionHighPriority,
    ActionStatBoost,
    ActionAnimation,
};

struct action {
    u8 action_bank;
    u8 target;
    enum ActionTiming type;
    u8 event_state; // which game loop function is under execution right now
    u16 move;
    u8 copied : 1;
    u8 prankstered : 1;
    u8 has_bounced : 1;
    u8 reset_move_config : 1;
    u8 active_override : 1;
    s16 priv[5];
    u32 script;
    u32 priv32;
    struct action* prev_action;
    struct action* next_action;
};

typedef void (*EventCallback)(struct action* a);

/* Macros */
#define ACTION_HEAD gBattleMaster->action_head
#define ACTION_TARGET ACTION_HEAD->target
#define ACTION_BANK ACTION_HEAD->action_bank
#define ACTION_TYPE ACTION_HEAD->type
#define EVENT_STATE ACTION_HEAD->event_state
#define CURRENT_ACTION gBattleMaster->this_action


extern struct action* add_action(u8 bank, u8 target, u8 type, u8 event_state);
extern void end_action(struct action* a);
extern struct action* prepend_action(u8 bank, u8 target, u8 type, u8 event_state);
extern struct action* next_action(u8 bank, u8 target, u8 type, u8 event_state);
extern void clear_actions(void);
extern struct action* find_action(u8 bank, u8 type);

#endif /* GAME_ACTIONS_H_ */
