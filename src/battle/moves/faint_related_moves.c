#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_events/battle_events.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern u8 GetMoveIndexBank(u16 moveId, u8 bank);


/* Perish song */
u8 perish_song_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (HAS_VOLATILE(i, VOLATILE_PERISH_SONG)) {
            QueueMessage(0, i, STRING_COUNT_FELL, 3 - gPkmnBank[i]->battleData.perish_song_counter);
            gPkmnBank[i]->battleData.perish_song_counter += 1;
            if (gPkmnBank[i]->battleData.perish_song_counter > 3) {
                B_FAINTED(i) = true;
                do_damage(i, B_CURRENT_HP(i));
            }
        }
    }
    return true;
}

u8 perish_song_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    return true;
}

u8 perish_song_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    /* Perish song marks each target it hits with a volatile, and sets the perish song counter to 0.
    Already affected targets aren't reapplied perish song. */
    u8 target = TARGET_OF(user);
    if (HAS_VOLATILE(target, VOLATILE_PERISH_SONG)) return true;

    u8 id = get_callback_src((u32)perish_song_before_move, src);
    CB_MASTER[id].data_ptr = true;
    ADD_VOLATILE(target, VOLATILE_PERISH_SONG);
    gPkmnBank[target]->battleData.perish_song_counter = 0;
    return true;
}

void perish_song_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 id = get_callback_src((u32)perish_song_before_move, src);
    if (CB_MASTER[id].data_ptr == true) {
        QueueMessage(0, user, STRING_PERISH_START, 0);
        add_callback(CB_ON_RESIDUAL, 0, 3, user, (u32)perish_song_on_residual);
    } else {
        QueueMessage(0, user, STRING_FAILED, 0);
    }
}


/* Destiny Bond */
void destiny_bond_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    do_damage(acb->data_ptr, B_CURRENT_HP(acb->data_ptr));
    QueueMessage(0, src, STRING_TOOK_WITH_HIM, 0);
}

void destiny_bond_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (HAS_VOLATILE(src, VOLATILE_DESTINY_BOND)) {
        u16 dmg = B_MOVE_DMG(user);
        if (dmg > B_CURRENT_HP(src)) {
            u8 id = add_callback(CB_ON_FAINT_CHECK, 0, 0, src, (u32)destiny_bond_on_faint);
            CB_MASTER[id].data_ptr = user;
            B_FAINTED(user) = true;
        }
    }
}

u8 destiny_bond_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    CLEAR_VOLATILE(user, VOLATILE_DESTINY_BOND);
    return true;
}

u8 destiny_bond_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)destiny_bond_before_move, user)) return false;
    ADD_VOLATILE(user, VOLATILE_DESTINY_BOND);
    QueueMessage(0, user, STRING_TRYING_TO_TAKE, 0);
    add_callback(CB_ON_DAMAGE_MOVE, 0, 1, user, (u32)destiny_bond_on_damage);
    add_callback(CB_ON_BEFORE_MOVE, 0, 1, user, (u32)destiny_bond_before_move);
    return true;
}


/* Grudge */
void grudge_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    QueueMessage(CURRENT_MOVE(acb->data_ptr), acb->data_ptr, STRING_GRUDGE_END, 0);
    u8 id = GetMoveIndexBank(CURRENT_MOVE(acb->data_ptr), acb->data_ptr);
    B_GET_MOVE_PP(acb->data_ptr, id) = 0;
}

void grudge_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (HAS_VOLATILE(src, VOLATILE_GRUDGE)) {
        u16 dmg = B_MOVE_DMG(user);
        if (dmg > B_CURRENT_HP(src)) {
            u8 id = add_callback(CB_ON_FAINT_CHECK, 0, 0, src, (u32)grudge_on_faint);
            CB_MASTER[id].data_ptr = user;
        }
    }
}

u8 grudge_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    CLEAR_VOLATILE(user, VOLATILE_GRUDGE);
    return true;
}

u8 grudge_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)grudge_before_move, user)) return false;
    ADD_VOLATILE(user, VOLATILE_GRUDGE);
    QueueMessage(0, user, STRING_GRUDGE_START, 0);
    add_callback(CB_ON_DAMAGE_MOVE, 0, 1, user, (u32)grudge_on_damage);
    add_callback(CB_ON_BEFORE_MOVE, 0, 1, user, (u32)grudge_before_move);
    return true;
}


/* Final Gambit */
void final_gambit_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    do_damage(user, B_CURRENT_HP(user));
}

void final_gambit_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    B_MOVE_DMG(user) = B_CURRENT_HP(user);
    B_FAINTED(user) = true;
}

/* Self Destruct, Explosion */
// These moves fail with Damp on the field. Damp should handle this effect.
enum TryHitMoveStatus self_destruct_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    do_damage(user, B_CURRENT_HP(user));
    return TRYHIT_USE_MOVE_NORMAL;
}
