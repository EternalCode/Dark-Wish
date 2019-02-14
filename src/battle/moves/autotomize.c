#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);

u8 autotomize_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    if (B_WEIGHT(user) <= 1000) {
        B_WEIGHT(user) = 1;
    }
    else {
        B_WEIGHT(user) = B_WEIGHT(user) - 1000;
    }
    return true;
}
