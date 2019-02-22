#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void do_damage(u8 bank_index, u16 dmg);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);

void event_move_recoil(struct action* current_action) {
    u8 bank = current_action->action_bank;
    u16 move = CURRENT_MOVE(bank);
    if (B_FAINTED(bank)) {
        CURRENT_ACTION->event_state++;
        return;
    }
    // check for recoil
    if (gBattleMoves[move].recoil_struggle) {
        // struggle recoil is based off max health
        do_damage(bank, PERCENT(TOTAL_HP(bank), gBattleMoves[move].recoil));
        QueueMessage(move, bank, STRING_RECOIL, 0);
    } else if (B_MOVE_DMG(bank) != 0 && gBattleMoves[move].recoil > 0) {
        // normal recoil based on move damage
        if(do_damage_residual(bank, 1, A_FLAG_RECOIL_DMG_PREVENT)) {
            do_damage(bank, MAX(PERCENT(B_MOVE_DMG(bank), gBattleMoves[move].recoil), 1));
            QueueMessage(move, bank, STRING_RECOIL, 0);
        }
    }
    CURRENT_ACTION->event_state++;
}
