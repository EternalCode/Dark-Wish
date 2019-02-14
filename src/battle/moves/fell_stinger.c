#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);

void fell_stinger_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_CURRENT_HP(TARGET_OF(user)) == 0) {
        stat_boost(user, ATTACK_MOD, 3, user);
    }
}
