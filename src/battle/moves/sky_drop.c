#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool BankMonHasType(u8 bank, enum PokemonType type);


u8 skydrop_opponent_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(user, VOLATILE_SKYDROP)) {
        QueueMessage(CURRENT_MOVE(user), user, STRING_SKY_DROP_AIR, MOVE_SKYDROP);
        return 3;
    }
    return true;
}

u8 skydrop_on_effectiveness(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 attacker = acb->data_ptr >> 16;
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (attacker != src) return effectiveness;
    if (BankMonHasType(TARGET_OF(attacker), MTYPE_FLYING))
        return 0;
    return effectiveness;
}

u8 skydrop_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // can't sky drop under gravity
    if (HAS_VOLATILE(user, VOLATILE_GRAVITY)) {
        CLEAR_VOLATILE(user, VOLATILE_SKYDROP);
        CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        QueueMessage(MOVE_SKYDROP, user, STRING_CANT_REASON, NULL);
        return false;
    }
    // if charging move skip turn
    if (HAS_VOLATILE(user, VOLATILE_CHARGING)) {
        CLEAR_VOLATILE(user, VOLATILE_CHARGING);
        CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        CLEAR_VOLATILE(user, VOLATILE_SKYDROP);
    } else {
        QueueMessage(0, user, STRING_SKY_DROP_START, 0);
        ADD_VOLATILE(user, VOLATILE_CHARGING);
        ADD_VOLATILE(user, VOLATILE_SKYDROP);
        ADD_VOLATILE(TARGET_OF(user), VOLATILE_SKYDROP);
        ADD_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        add_callback(CB_ON_BEFORE_MOVE, 3, 1, TARGET_OF(user), (u32)skydrop_opponent_before_move);
        add_callback(CB_ON_EFFECTIVENESS, 0, 1, user, (u32)skydrop_on_effectiveness);
    }
    return true;
}

void skydrop_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    CLEAR_VOLATILE(TARGET_OF(user), VOLATILE_SKYDROP);
    QueueMessage(MOVE_SKYDROP, TARGET_OF(user), STRING_SKY_DROP_FREE, NULL);
}

//attacker took defender to the sky!
//foe was freed from the Sky Drop!
