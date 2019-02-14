#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern bool break_protection(u8 bank);
extern u8 before_move_charge_frame(u8 user, u8 string_id);


u8 shadow_force_phantom_force_effect(u8 user, u8 src, u8 string_id) {
    before_move_charge_frame(user, string_id);
    if (HAS_VOLATILE(user, VOLATILE_CHARGING)) {
        ADD_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
        return true;
    }
    CLEAR_VOLATILE(user, VOLATILE_SEMI_INVULNERABLE);
    // on after charge complete, break protection effect
    if (break_protection(TARGET_OF(src))) {
        QueueMessage(MOVE_PHANTOMFORCE, src, STRING_BROKE_PROTECT, 0);
    }

    // accuracy umissable and double power when hitting a minimizer
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MINIMIZE)) {
        B_MOVE_ACCURACY(user) = 101;
        B_MOVE_POWER(user) *= 2;
    }
    return true;
}

u8 phantom_force_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // shadow force two-turn effect
    return shadow_force_phantom_force_effect(user, src, STRING_CHARGE_PHANTOM_FORCE);
}
