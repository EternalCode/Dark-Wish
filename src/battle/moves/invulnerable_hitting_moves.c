#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);

u8 gust_on_invul_hit(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != src) return true;
    u8 defender = TARGET_OF(user);
    if ((CURRENT_MOVE(defender) == MOVE_BOUNCE) || (CURRENT_MOVE(defender) == MOVE_FLY)) {
        if (HAS_VOLATILE(defender, VOLATILE_SEMI_INVULNERABLE)) {
            B_MOVE_POWER(user) *= 2;
        }
        return false;
    }
    return true;
}
