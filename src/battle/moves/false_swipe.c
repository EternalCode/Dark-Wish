#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void false_swipe_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 target = TARGET_OF(user);
    u16 dmg = B_MOVE_DMG(user);
    if (dmg > B_CURRENT_HP(target)) {
        B_MOVE_DMG(user) = B_CURRENT_HP(target) - 1;
    }
}
