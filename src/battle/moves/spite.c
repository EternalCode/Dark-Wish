#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 GetMoveIndexBank(u16 moveId, u8 bank);

u8 spite_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (LAST_MOVE(TARGET_OF(user)) == MOVE_NONE) return false;
    u8 id = GetMoveIndexBank(LAST_MOVE(TARGET_OF(user)), TARGET_OF(user));
    if (id < 3) {
        s8 amount = B_GET_MOVE_PP(TARGET_OF(user), id);
        B_GET_MOVE_PP(TARGET_OF(user), id) = MAX(0, amount - 5);
        return true;
    } else {
        return false;
    }
}
