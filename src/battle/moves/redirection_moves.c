#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 rage_powder_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    TARGET_OF(user) = acb->data_ptr;
    return true;
}

u8 rage_powder_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    bool applied = false;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (SIDE_OF(i) == SIDE_OF(TARGET_OF(user)))
            continue;
        if (M_HITS_TARGET(CURRENT_MOVE(i))) {
            u8 id = AddCallback(CB_ON_MODIFY_MOVE, 0, 0, i, (u32)rage_powder_on_modify_move);
            CB_MASTER[id].data_ptr = TARGET_OF(user);
            applied = true;
        }
    }
    if (applied)
        QueueMessage(0, user, STRING_CENTER_ATTENTION, 0);
    return applied;
}
