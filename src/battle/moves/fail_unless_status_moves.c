#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern u8 GetMoveIndexBank(u16 moveId, u8 bank);
extern u16 RandRange(u16 min, u16 max);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);
extern void do_damage(u8 bank_index, u16 dmg);


enum TryHitMoveStatus snore_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_SLEEP) || (BANK_ABILITY(TARGET_OF(user)) == ABILITY_COMATOSE))
        return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_CANT_USE_MOVE;
}


/* Nightmare */
// Nightmare effect is removed is the sleep status is removed
extern u8 nightmare_on_status(u8 user, u8 src, u16 status, struct anonymous_callback* acb);
extern u8 nightmare_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
u8 nightmare_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_SLEEP) || (BANK_ABILITY(TARGET_OF(user)) == ABILITY_COMATOSE))
        return true;

    // remove the residual
    delete_callback_src((u32)nightmare_on_residual, user);
    delete_callback_src((u32)nightmare_on_status, user);
    acb->in_use = false;
    return true;
}

u8 nightmare_on_status(u8 user, u8 src, u16 status, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((status == AILMENT_CURE) || (status == AILMENT_NONE)) {
        delete_callback_src((u32)nightmare_on_residual, user);
        delete_callback_src((u32)nightmare_on_modify_move, user);
        acb->in_use = false;
    }
    return true;
}

u8 nightmare_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 status = B_STATUS(user);
    if ((status == AILMENT_SLEEP) || (BANK_ABILITY(TARGET_OF(user)) == ABILITY_COMATOSE)) {
        if (do_damage_residual(user, 1, NULL)) {
            do_damage(user, MAX(1, (TOTAL_HP(user) / 4)));
            QueueMessage(MOVE_NIGHTMARE, user, STRING_CURSE_RESIDUAL, MOVE_NIGHTMARE);
        }
    } else {
        delete_callback_src((u32)nightmare_on_status, user);
        delete_callback_src((u32)nightmare_on_modify_move, user);
    }
    return true;
}

enum TryHitMoveStatus nightmare_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    u8 status = B_STATUS(TARGET_OF(user));

    if ((status == AILMENT_SLEEP) || (BANK_ABILITY(TARGET_OF(user)) == ABILITY_COMATOSE)) {
        AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, TARGET_OF(user), (u32)nightmare_on_residual);
        AddCallback(CB_ON_STATUS, 0, CB_PERMA, TARGET_OF(user), (u32)nightmare_on_status);
        AddCallback(CB_ON_MODIFY_MOVE, 0, CB_PERMA, TARGET_OF(user), (u32)nightmare_on_modify_move);
        return TRYHIT_USE_MOVE_NORMAL;
    } else {
        return TRYHIT_CANT_USE_MOVE;
    }
}
