#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);

u8 topsy_turvy_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (src != user) return true;
    B_ATTACK_BUFF(TARGET_OF(user)) = -(B_ATTACK_BUFF(TARGET_OF(user)));
    B_DEFENSE_BUFF(TARGET_OF(user)) = -(B_DEFENSE_BUFF(TARGET_OF(user)));
    B_SPEED_BUFF(TARGET_OF(user)) = -(B_SPEED_BUFF(TARGET_OF(user)));
    B_SPATTACK_BUFF(TARGET_OF(user)) = -(B_SPATTACK_BUFF(TARGET_OF(user)));
    B_SPDEFENSE_BUFF(TARGET_OF(user)) = -(B_SPDEFENSE_BUFF(TARGET_OF(user)));
    B_ACCURACY_BUFF(TARGET_OF(user))  = -(B_ACCURACY_BUFF(TARGET_OF(user)));
    B_EVASION_BUFF(TARGET_OF(user)) = -(B_EVASION_BUFF(TARGET_OF(user)));
    QueueMessage(NULL, TARGET_OF(user), STRING_TOPSY_TURVY, NULL);
    return true;
}
