#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);


void helping_hand_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), acb->data_ptr);
}

u8 helping_hand_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // helping hand is stackable
    u8 id = get_callback_src((u32)helping_hand_on_base_power, TARGET_OF(user));
    if (id < ANON_CB_MAX) {
        CB_MASTER[id].data_ptr += 50;
    } else {
        id = add_callback(CB_ON_BASE_POWER_MOVE, 3, 1, TARGET_OF(user), (u32)helping_hand_on_base_power);
        CB_MASTER[id].data_ptr = 150;
    }
    QueueMessage(NULL, user, STRING_READY_TO_HELP, NULL);
    return true;
}
