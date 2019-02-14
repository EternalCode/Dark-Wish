#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../status_effects/status.h"

extern void dprintf(const char * str, ...);
extern void ShowStatusAilmentGraphic(u8 bank, enum Effect status);


u8 rest_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)

{
    if (user != src) return true;
    if (B_CURRENT_HP(user) == TOTAL_HP(user))
        return false;
    if (B_STATUS(user) == AILMENT_SLEEP)
        return false;
    statuses[AILMENT_SLEEP].on_inflict(user);
    ShowStatusAilmentGraphic(user, AILMENT_SLEEP);
    if ((B_STATUS(user) != AILMENT_SLEEP))
        return false;
    B_HEAL(user) = 100;
    return true;
}
