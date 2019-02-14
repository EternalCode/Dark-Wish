#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_actions/actions.h"
#include "../battle_events/battle_events.h"

extern void dprintf(const char * str, ...);
extern u16 RandRange(u16 min, u16 max);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_heal(u8 bank_index, u8 heal);
extern bool BankMonHasType(u8 bank, enum PokemonType type);

u8 partial_dmg_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    if (acb->duration == 0) {
        CLEAR_VOLATILE(user, VOLATILE_BIND);
        CLEAR_VOLATILE(user, VOLATILE_TRAPPED);
        return true;
    }
    if(do_damage_residual(user, MAX(1, (TOTAL_HP(user) / 8)), NULL))
        QueueMessage(acb->data_ptr, user, STRING_RESIDUAL_DMG, 0);
    return true;
}

u8 partially_trapped_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 defender = TARGET_OF(user);
    // the bind effect timer does not reset upon using bind again
    if (has_callback_src((u32)partial_dmg_on_residual, defender))
        return true;
    ADD_VOLATILE(defender, VOLATILE_BIND);
    ADD_VOLATILE(defender, VOLATILE_TRAPPED);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, RandRange(4, 6), src, (u32)partial_dmg_on_residual);
    CB_MASTER[id].data_ptr = move;
    return true;
}


/* Auqa ring */
u8 aqua_ring_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    QueueMessage(acb->data_ptr, user, STRING_HEAL, 0);
    do_heal(user, 6);
    return true;
}

u8 aqua_ring_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)aqua_ring_on_residual, user))
        return true;
    u8 id = add_callback(CB_ON_RESIDUAL, 6, CB_PERMA, user, (u32)aqua_ring_on_residual);
    CB_MASTER[id].data_ptr = move;
    return true;
}


/* Mean look steal strapping effect */
u8 mean_look_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_TRAPPED);
    return true;
}


// leech seed
u8 leech_seed_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 dmg = MAX(1, (TOTAL_HP(user) / 8));
    if (do_damage_residual(user, dmg, NULL)) {
        CURRENT_MOVE(acb->data_ptr) = MOVE_LEECHSEED;
        B_MOVE_DMG(acb->data_ptr) = dmg;
        TARGET_OF(acb->data_ptr) = user;
        prepend_action(acb->data_ptr, user, ActionHeal, EventDrain);
        QueueMessage(NULL, user, STRING_SAPPED, 0);
    }
    return true;
}

enum TryHitMoveStatus leech_seed_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (BankMonHasType(TARGET_OF(user), MTYPE_GRASS)) return TRYHIT_TARGET_MOVE_IMMUNITY; // immune
    u8 id = add_callback(CB_ON_RESIDUAL, 8, CB_PERMA, TARGET_OF(user), (u32)leech_seed_on_residual);
    CB_MASTER[id].data_ptr = user;
    QueueMessage(NULL, TARGET_OF(user), STRING_SEEDED, 0);
    return TRYHIT_USE_MOVE_NORMAL;
}
