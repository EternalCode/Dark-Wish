#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
void set_status(u8 bank, enum StatusAilments status, u8 inflictor);

u8 psycho_shift_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_STATUS(user) != AILMENT_NONE) {
        set_status(TARGET_OF(user), B_STATUS(user), user);
        set_status(user, AILMENT_CURE, user);
        return true;
    }
    return false;
}
