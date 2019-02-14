#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);

u8 sky_uppercut_on_invulnerable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_SKYDROP) || HAS_VOLATILE(TARGET_OF(user), VOLATILE_FLYING) ||
        HAS_VOLATILE(TARGET_OF(user), VOLATILE_BOUNCE)) {
            return false;
    }
    return true;
}
