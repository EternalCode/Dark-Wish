#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);
extern void give_exp(u8 fainted, u8 reciever);
extern void jump_switch_menu(enum switch_reason reason);
extern void SyncBankToParty(u8 bank);
extern u8 SideCountUsablePkmn(u8 side);

void wild_battle_status_update(struct action* current_action)
{
    // if the player side has fainted and there are no switch-ins, end the battle (port PC)
    if (B_IS_FAINTED(PLAYER_SINGLES_BANK)) {
        u8 count = SideCountUsablePkmn(SIDE_OF(PLAYER_SINGLES_BANK));
        if (count > 0) {
            CURRENT_ACTION->event_state = EventPreSwitch;
            CURRENT_ACTION->active_override = true;
            CURRENT_ACTION->action_bank = PLAYER_SINGLES_BANK;
            gBattleMaster->option_selecting_bank = PLAYER_SINGLES_BANK;
            jump_switch_menu(PokemonFainted);
            return;
        } else {
            // pokemon not found to switch
            CURRENT_ACTION->event_state = EventEndBattle;
            SyncBankToParty(PLAYER_SINGLES_BANK);
            return;
        }
    }

    // if foe side has fainted end the battle
    if (B_IS_FAINTED(OPPONENT_SINGLES_BANK)) {
        CURRENT_ACTION->event_state = EventEndBattle;
    } else {
        end_action(CURRENT_ACTION);
    }
}
