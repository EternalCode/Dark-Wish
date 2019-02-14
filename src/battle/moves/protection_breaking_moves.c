#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern bool break_protection(u8 bank);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 feint_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (break_protection(TARGET_OF(src))) {
        QueueMessage(MOVE_FEINT, src, STRING_BROKE_PROTECT, 0);
    }
    return true;
}
