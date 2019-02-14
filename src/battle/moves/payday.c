#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

void payday_ondmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    gBattleMaster->field_state.payday_coins = B_LEVEL(user);
}
