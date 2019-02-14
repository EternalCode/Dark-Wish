#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

u8 clear_smog_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    u8 defender = TARGET_OF(user);
    gPkmnBank[defender]->battleData.attack = 0;
    gPkmnBank[defender]->battleData.defense = 0;
    gPkmnBank[defender]->battleData.speed = 0;
    gPkmnBank[defender]->battleData.sp_atk = 0;
    gPkmnBank[defender]->battleData.sp_def = 0;
    gPkmnBank[defender]->battleData.accuracy = 0;
    gPkmnBank[defender]->battleData.evasion = 0;
    gPkmnBank[defender]->battleData.crit_mod = 0;
    QueueMessage(move, user, STRING_CLEAR_SMOG, 0);
    return true;
}

u8 psych_up_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target = TARGET_OF(user);
    B_ATTACK_BUFF(user) = B_ATTACK_BUFF(target);
    B_DEFENSE_BUFF(user) = B_DEFENSE_BUFF(target);
    B_SPEED_BUFF(user) = B_SPEED_BUFF(target);
    B_SPATTACK_BUFF(user) = B_SPATTACK_BUFF(target);
    B_SPDEFENSE_BUFF(user) = B_SPDEFENSE_BUFF(target);
    B_ACCURACY_BUFF(user) = B_ACCURACY_BUFF(target);
    B_EVASION_BUFF(user) = B_EVASION_BUFF(target);
    B_CRIT_BUFF(user) = B_CRIT_BUFF(target);
    QueueMessage(move, user, STRING_COPIED_STATS, 0);
    return true;
}

u8 haze_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    for (u8 i = 0; i < BANK_MAX; i++) {
        gPkmnBank[i]->battleData.attack = 0;
        gPkmnBank[i]->battleData.defense = 0;
        gPkmnBank[i]->battleData.speed = 0;
        gPkmnBank[i]->battleData.sp_atk = 0;
        gPkmnBank[i]->battleData.sp_def = 0;
        gPkmnBank[i]->battleData.accuracy = 0;
        gPkmnBank[i]->battleData.evasion = 0;
        gPkmnBank[i]->battleData.crit_mod = 0;
    }
    QueueMessage(move, user, STRING_STAT_ELIMINATED, 0);
    return true;
}
