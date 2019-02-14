#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);

u8 belly_drum_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((B_CURRENT_HP(user) << 1) < TOTAL_HP(user))
        return false;
    do_damage(user, TOTAL_HP(user) / 2);
    B_ATTACK_BUFF(user) = 6;
    QueueMessage(NULL, user, STRING_BELLY_DRUM, NULL);
    return true;
}
