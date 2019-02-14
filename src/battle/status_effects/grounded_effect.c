#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"

extern u8 magnet_rise_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 telekinesis_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool BankMonHasType(u8 bank, enum PokemonType type);

/* Must revist as these effects are implemented. */
bool is_grounded(u8 bank) {
    // gravity in effect, true
    if (HAS_VOLATILE(bank, VOLATILE_GRAVITY)) return true;
    // ingrain in effect true
    if (HAS_VOLATILE(bank, VOLATILE_INGRAIN)) return true;
    // smackdown in effect on bank true
    if (HAS_VOLATILE(bank, VOLATILE_SMACK_DOWN)) return true;
    // ironball active true
    // levitate active here false
    if (BANK_ABILITY(bank) == ABILITY_LEVITATE) return false;
    // Magnet rise here false
    if (has_callback_src((u32)magnet_rise_on_residual, bank)) return false;
    // telekinesis here false
    if (has_callback_src((u32)telekinesis_on_residual, bank)) return false;
    // if air balloon true
    // false
    if (BankMonHasType(bank, TYPE_FLYING)) {
        B_IS_GROUNDED(bank) = false;
        return false;
    }
    return true;
}
