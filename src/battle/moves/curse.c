#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern void do_damage(u8 bank_index, u16 dmg);


u8 curse_on_effect_ghost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    do_damage(user, TOTAL_HP(user) >> 1);
    QueueMessage(NULL, user, STRING_CURSE, NULL);
    return true;
}

u8 curse_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    QueueMessage(MOVE_CURSE, user, STRING_CURSE_RESIDUAL, MOVE_CURSE);
    do_damage(user, MAX(1, (TOTAL_HP(user) / 4)));
    return true;
}

enum TryHitMoveStatus curse_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (BankMonHasType(user, TYPE_GHOST)) {
        AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, TARGET_OF(user), (u32)curse_on_residual);
        AddCallback(CB_ON_EFFECT, 0, 0, user, (u32)curse_on_effect_ghost);
    } else {
        // set the stat boosts
        B_USER_STAT_MOD_CHANCE(user, ATTACK_MOD) = 100;
        B_USER_STAT_MOD_CHANCE(user, DEFENSE_MOD) = 100;
        B_USER_STAT_MOD_CHANCE(user, SPEED_MOD) = 100;
        B_USER_STAT_MOD_AMOUNT(user, ATTACK_MOD) = 1;
        B_USER_STAT_MOD_AMOUNT(user, DEFENSE_MOD) = 1;
        B_USER_STAT_MOD_AMOUNT(user, SPEED_MOD) = -1;
    }
    return TRYHIT_USE_MOVE_NORMAL;
}
