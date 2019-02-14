#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount);


u8 gear_up_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 ability = BANK_ABILITY(TARGET_OF(user));
    if ((ability == ABILITY_PLUS) || (ability == ABILITY_MINUS))
        return true;
    return false;
}
