#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);

u8 jump_kick_on_move_fail(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    do_damage_residual(user, MIN(B_CURRENT_HP(user), (TOTAL_HP(user) >> 1)), NULL);
    return true;
}
