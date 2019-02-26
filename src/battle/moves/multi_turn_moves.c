#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void run_decision(void);
extern u16 RandRange(u16 min, u16 max);
extern void set_status(u8 bank, enum StatusAilments status, u8 inflictor);

/* Thrash, Outrage, Petal Dance */
u8 thrash_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((gPkmnBank[user]->battleData.skip_move_select) && (gPkmnBank[user]->battleData.move_lock_counter < 1)) {
        gPkmnBank[user]->battleData.skip_move_select = false;
        gPkmnBank[user]->battleData.move_lock_counter = 0;
        CLEAR_VOLATILE(user, VOLATILE_MULTI_TURN);
    } else if (gPkmnBank[user]->battleData.skip_move_select) {
        gPkmnBank[user]->battleData.move_lock_counter--;
    } else {
        gPkmnBank[user]->battleData.move_lock_counter = RandRange(1, 2);
        gPkmnBank[user]->battleData.skip_move_select = true;
        ADD_VOLATILE(user, VOLATILE_MULTI_TURN);
    }
    return 1;
}

u8 thrash_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    gPkmnBank[user]->battleData.skip_move_select = false;
    gPkmnBank[user]->battleData.move_lock_counter = 0;
    return 1;
}

void thrash_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (gPkmnBank[user]->battleData.skip_move_select == false) {
        if (!(HAS_VOLATILE(user, VOLATILE_CONFUSION))) {
            set_status(user, AILMENT_CONFUSION, user);
        }
    }
    return;
}


/* shared callbacks with Ice ball */
u8 rollout_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
	if ((gPkmnBank[user]->battleData.skip_move_select) && (gPkmnBank[user]->battleData.move_lock_counter < 1)) {
		gPkmnBank[user]->battleData.skip_move_select = false;
        gPkmnBank[user]->battleData.move_lock_counter = 0;
        CLEAR_VOLATILE(user, VOLATILE_MULTI_TURN);
	} else if (gPkmnBank[user]->battleData.skip_move_select) {
		gPkmnBank[user]->battleData.move_lock_counter--;
	} else {
		 gPkmnBank[user]->battleData.move_lock_counter = 5;
        gPkmnBank[user]->battleData.skip_move_select = true;
        ADD_VOLATILE(user, VOLATILE_MULTI_TURN);
	}
	return 1;
}

u8 rollout_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    gPkmnBank[user]->battleData.skip_move_select = false;
    gPkmnBank[user]->battleData.move_lock_counter = 0;
    return 1;
}

void rollout_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
	if (HAS_VOLATILE(user, VOLATILE_DEFENSE_CURL)) {
		B_MOVE_POWER(user) *= 2;
	}
	B_MOVE_POWER(user) = (B_MOVE_POWER(user) << (5 - gPkmnBank[user]->battleData.move_lock_counter));
}
