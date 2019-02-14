#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

// Counter
void counter_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return;
    if ((TARGET_OF(user) == src) && B_MOVE_IS_PHYSICAL(user))
        B_MOVE_DMG(src) = B_MOVE_DMG(user) << 1;
}

enum TryHitMoveStatus counter_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (B_MOVE_DMG(src) < 1)
        return TRYHIT_CANT_USE_MOVE;
    return TRYHIT_USE_MOVE_NORMAL;
}

void counter_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_DAMAGE_MOVE, -101, 0, user, (u32)counter_on_damage);
}

// Mirror Coat
void mirror_coat_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return;
    if ((TARGET_OF(user) == src) && B_MOVE_IS_SPECIAL(user))
        B_MOVE_DMG(src) = B_MOVE_DMG(user) << 1;
}

enum TryHitMoveStatus mirror_coat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (B_MOVE_DMG(src) < 1)
        return TRYHIT_CANT_USE_MOVE;
    return TRYHIT_USE_MOVE_NORMAL;
}

void mirror_coat_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_DAMAGE_MOVE, -101, 0, user, (u32)mirror_coat_on_damage);
}

// Metal Burst
void metal_burst_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return;
    if (TARGET_OF(user) == src)
        B_MOVE_DMG(src) = PERCENT(B_MOVE_DMG(user), 150);

}

enum TryHitMoveStatus metal_burst_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (B_MOVE_DMG(src) < 1)
        return TRYHIT_CANT_USE_MOVE;
    return TRYHIT_USE_MOVE_NORMAL;
}

void metal_burst_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_DAMAGE_MOVE, -101, 0, user, (u32)metal_burst_damage);
}
