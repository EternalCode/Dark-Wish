#ifndef ANONYMOUS_CALLBACKS_H_
#define ANONYMOUS_CALLBACKS_H_

#include <pokeagb/pokeagb.h>


#define ANON_CB_MAX 40
#define ELE_NULL(i) (gBattleMaster->anon_cb_master[i].in_use == false)
#define ELE_USED(i) (gBattleMaster->anon_cb_master[i].in_use == true)
#define ANON_PRIORITY(i) gBattleMaster->anon_cb_master[i].priority
#define CB_MASTER gBattleMaster->anon_cb_master
#define CB_EXEC_ORDER gBattleMaster->cb_execution_order
#define CB_EXEC_INDEX gBattleMaster->current_cb_index
#define CB_PERMA 126

#define CB_ON_BEFORE_TURN 1
#define CB_ON_BEFORE_SWITCH 2
#define CB_ON_BEFORE_MOVE 3
#define CB_ON_START 4
#define CB_ON_MOVE_FAIL 5
#define CB_ON_MODIFY_MOVE 6
#define CB_ON_TRYHIT_MOVE 7
#define CB_ON_BASE_POWER_MOVE 8
#define CB_ON_DAMAGE_MOVE 9
#define CB_ON_EFFECT 10
#define CB_ON_AFTER_MOVE 11
#define CB_ON_TRYHIT_INV_MOVE 12
#define CB_ON_RESIDUAL 13
#define CB_ON_STAT_MOD 14 // (user, src, stat_id, acb = current stat return)
#define CB_ON_WEATHER_DMG 15
#define CB_ON_EFFECTIVENESS 16 //(target_type, src, move_type, acb = current effectiveness)
#define CB_ON_STATUS 17
#define CB_ON_BEFORE_STAT_MOD 18
#define CB_ON_DISABLE_MOVE 19 // run before  before turn. Resets banks and prompts move selection on fail
#define CB_ON_FAINT_CHECK 20
#define CB_ON_STAT_BOOST_MOD 21
#define CB_AFTER_STAT_BOOST_MOD 22
#define CB_ON_DRAIN 23
#define CB_ON_FLINCH 24


struct anonymous_callback {
	s8 priority;
	u8 delay_before_effect : 6;
	u8 in_use : 1;
	u8 remove_on_faint_or_switch : 1;
	u8 duration;
	u8 source_bank; // source bank using the effect
	u8 cb_id; // execution timing, callback id
	u32 data_ptr;
	u32 func;
};

typedef u16 (*AnonymousCallback)(u8 user, u8 src, u16 move, struct anonymous_callback* acb);

// Generic callback functions
extern u8 AddCallback(u8 CB_id, s8 priority, u8 dur, u8 src, u32 func);
extern bool callback_exists(u32 func);
extern void delete_callback(u32 func);
extern void DeleteGhostCallbacks(u8 user);

// Building and running callbacks
extern void BuildCallbackExecutionBuffer(u8 CB_id);
extern u16 PopCallback(u8 attacker, u16 move);
extern u16 run_callback(u8 attacker, u16 move);

// Fetch callbacks and generic
extern u8 id_by_func(u32 func);
extern u8 id_by_acb(struct anonymous_callback* acb);
extern void set_data_next_acb(u32 data);

// Callback operations on source + func level
extern void delete_callback_src(u32 func, u8 src);
extern bool has_callback_src(u32 func, u8 src);
extern u8 get_callback_src(u32 func, u8 src);

// callback operations on side + func level
extern void delete_callback_side(u32 func, u8 side);
extern u8 callback_exists_side(u32 func, u8 bank);

// callback stack restore and backup related
extern void restore_callbacks(u32* data_ptr);
extern u32* push_callbacks();

// Update Callback counters - Mark expired callbacks
extern void update_callbacks(void);


#endif /* ANONYMOUS_CALLBACKS_H_ */
