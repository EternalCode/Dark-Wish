#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern u16 RandRange(u16, u16);
extern void do_heal(u8 bank_index, u16 heal);

u8 present_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)

{
	if (user != src) return 1;
	u16 rand_num = RandRange(0, 100);
	if (rand_num < 20) {
		if (B_CURRENT_HP(TARGET_OF(user)) == TOTAL_HP(TARGET_OF(user)))
			return 0;
		else B_HEAL(user) = 25;
		}
	else if (rand_num < 60) {
		B_MOVE_POWER(user) = 40;
	}
	else if (rand_num < 90) {
		B_MOVE_POWER(user) = 80;
	}
	else if (rand_num >= 90) {
		B_MOVE_POWER(user) = 120;
	}
	return 1;
}
