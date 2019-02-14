#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

/* Fakeout + First impression */
enum TryHitMoveStatus fakeout_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (gPkmnBank[user]->battleData.first_turn) {
        return TRYHIT_USE_MOVE_NORMAL;
    } else {
        return TRYHIT_CANT_USE_MOVE;
    }
}
