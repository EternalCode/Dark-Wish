#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern void set_status(u8 bank, enum Effect status, u8 inflictor);
extern u16 RandRange(u16 min, u16 max);

u8 tri_attack_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (RandRange(0, 100) < 20) {
        u8 random = RandRange(0, 3);
        if (random == 0) {
            set_status(TARGET_OF(user), AILMENT_BURN, user);
        } else if (random == 1) {
            set_status(TARGET_OF(user), AILMENT_PARALYZE, user);
        } else {
            set_status(TARGET_OF(user), AILMENT_FREEZE, user);
        }
    }
    return true;
}
