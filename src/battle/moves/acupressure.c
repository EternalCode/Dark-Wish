#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 RandRange(u16 min, u16 max);

u8 accupressure_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 stats[6] = {ACCURACY_MOD, ACCURACY_MOD, ACCURACY_MOD, ACCURACY_MOD, ACCURACY_MOD};
    u8 index = 0;
    if (B_ATTACK_BUFF(user) < 6){
        stats[index] = ATTACK_MOD;
        index++;
    }
    if (B_DEFENSE_BUFF(user) < 6){
        stats[index] = DEFENSE_MOD;
        index++;
    }
    if (B_SPEED_BUFF(user) < 6){
        stats[index] = SPEED_MOD;
        index++;
    }
    if (B_SPATTACK_BUFF(user) < 6){
        stats[index] = SPATTACK_MOD;
        index++;
    }
    if (B_SPDEFENSE_BUFF(user) < 6){
        stats[index] = SPDEFENSE_MOD;
        index++;
    }

    if (index < 1) {
        // nothing to boost
        return false;
    }
    stat_boost(TARGET_OF(user), stats[RandRange(0, index)], 2, user);
    return true;
}
