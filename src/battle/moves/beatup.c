#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

/*
 * Beat up's implementation is weird. Basically it takes advantage of the multihit system during
 * the before_turn callback to set the correct amount of multihits. The general purpose data_ptr
 * attached to a callback is used as a bitfield for which slots can attack. The party is looped in
 * order during the base power callback and set bits cooresponding to the slot will attack. The user
 * of the move will always attack first, and won't be apart of this bitfield.
 */

void beatup_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    struct Pokemon *p = SIDE_OF(user) ? (&party_opponent[0]) : (&party_player[0]);
    u8 slot = acb->data_ptr >> 24;
    if (slot < 6) {
        B_MOVE_POWER(user) = (5 + PERCENT(pokemon_getattr(&p[slot], REQUEST_ATK, NULL), 10));
        acb->data_ptr |= (6 << 24);
    } else {
        for (u8 i = 0; i < 6; i++) {
            if ((1 << i) & (acb->data_ptr)) {
                // clear bit
                acb->data_ptr &= ~((1) << i);
                // apply damage from current index 'mon
                B_MOVE_POWER(user) = (5 + PERCENT(pokemon_getattr(&p[i], REQUEST_ATK, NULL), 10));
                slot = i;
                break;
            }
        }
    }
    QueueMessage(move, user, STRING_SLOT_ATTACK, slot);
}

void beatup_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    // figure out how many hits to do
    struct Pokemon *p = SIDE_OF(user) ? (&party_opponent[0]) : (&party_player[0]);
    u8 user_slot;
    u8 cb_id = AddCallback(CB_ON_BASE_POWER_MOVE, 0, 0, user, (u32)beatup_on_base_power);
    if (SIDE_OF(user)) {
        user_slot = ((u32)(gPkmnBank[user]->this_pkmn) - (u32)(&party_opponent[0])) / 100;
    } else {
        user_slot = ((u32)(gPkmnBank[user]->this_pkmn) - (u32)(&party_player[0])) / 100;
    }
    CB_MASTER[cb_id].data_ptr = (user_slot << 24);
    u8 hitters = 1;
    for (u8 i = 0; i < 6; i++) {
        if (i == user_slot) continue;
        if (pokemon_getattr(&p[i], REQUEST_SPECIES, NULL) == 0) break;
        u8 status = pokemon_getattr(&p[i], REQUEST_STATUS_AILMENT, NULL);
        u8 hp = pokemon_getattr(&p[i], REQUEST_CURRENT_HP, NULL);
        if ((status != 0) || (hp < 1 )) continue;
        hitters++;
        CB_MASTER[cb_id].data_ptr |= (1 << i);
    }
    gBattleMaster->b_moves[(user)].hit_times = hitters -1;
    gBattleMaster->b_moves[(user)].hit_counter = 1;
}
