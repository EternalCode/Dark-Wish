#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 guard_split_on_effect(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u16 target_def = B_DEFENSE_STAT_UMOD(TARGET_OF(user));
    u16 user_def = B_DEFENSE_STAT_UMOD(user);
    u16 new_def = (target_def + user_def) >> 1;

    target_def = B_SPDEFENSE_STAT_UMOD(TARGET_OF(user));
    user_def = B_SPDEFENSE_STAT_UMOD(user);
    u16 new_sdef = (target_def + user_def) >> 1;

    B_DEFENSE_STAT_UMOD(user) = new_def;
    B_DEFENSE_STAT_UMOD(TARGET_OF(user)) = new_def;
    B_SPDEFENSE_STAT_UMOD(user) = new_sdef;
    B_SPDEFENSE_STAT_UMOD(TARGET_OF(user)) = new_sdef;
    QueueMessage(NULL, user, STRING_GUARD_S, NULL);
    return true;
}

u8 power_split_on_effect(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u16 target_atk = B_ATTACK_STAT_UMOD(TARGET_OF(user));
    u16 user_atk = B_ATTACK_STAT_UMOD(user);
    u16 new_atk = (target_atk + user_atk) >> 1;

    target_atk = B_SPATTACK_STAT_UMOD(TARGET_OF(user));
    user_atk = B_SPATTACK_STAT_UMOD(user);
    u16 new_satk = (target_atk + user_atk) >> 1;

    B_ATTACK_STAT_UMOD(user) = new_atk;
    B_ATTACK_STAT_UMOD(TARGET_OF(user)) = new_atk;
    B_SPATTACK_STAT_UMOD(user) = new_satk;
    B_SPATTACK_STAT_UMOD(TARGET_OF(user)) = new_satk;
    QueueMessage(NULL, user, STRING_POWER_S, NULL);
    return true;
}
