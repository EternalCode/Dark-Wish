#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void set_status(u8 bank, enum Effect status, u8 inflictor);

u8 attract_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_INFACTUATION)) return false;
    u8 target_gender = B_GENDER(TARGET_OF(user));
    u8 user_gender = B_GENDER(user);
    if ((user_gender == target_gender) || (user_gender > 0xFE) || (target_gender > 0xFE))
        return false;
    set_status(TARGET_OF(user), AILMENT_INFACTUATE, user);
    return true;
}

enum TryHitMoveStatus captivate_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 target_gender = B_GENDER(TARGET_OF(user));
    u8 user_gender = B_GENDER(user);
    if ((user_gender == target_gender) || (user_gender > 0xFE) || (target_gender > 0xFE))
        return TRYHIT_CANT_USE_MOVE;
    return TRYHIT_USE_MOVE_NORMAL;
}

