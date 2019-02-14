#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"
#include "battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern void dprintf(const char * str, ...);
extern void battle_loop(void);
extern void pick_battle_message(u16 moveId, u8 user_bank, enum BattleTypes battle_type, enum battle_string_ids id, u16 move_effect_id);


struct action* QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect)
{
    struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionText, EventPeekMessage);
    a->action_bank = bank;
    a->move = move;
    a->priv[0] = id;
    a->priv[1] = effect;
    return a;
}


void event_peek_message(struct action* current_action)
{
    extern void play_bmessage(void);
    gMain.savedCallback = gMain.callback1;
    gMain.callback1 = play_bmessage;
    gBattleMaster->execution_index = gMain.state;
    gMain.state = 0;
}


void play_bmessage()
{
    switch(gMain.state) {
        case 0:
        {
            struct action* a = CURRENT_ACTION;
            pick_battle_message(a->move, a->action_bank, battle_type_flag, a->priv[0], a->priv[1]);
            ShowBattleMessage((u8*)string_buffer, 0x18);
            gMain.state++;
        }
            break;
        case 1:
            if (!dialogid_was_acknowledged(0x18)) {
                gMain.state++;
            }
            break;
        case 25:
        {
            end_action(CURRENT_ACTION);
            gMain.callback1 = gMain.savedCallback;
            gMain.state = gBattleMaster->execution_index;
            gBattleMaster->execution_index = 0;
            break;
        }
        default:
            gMain.state++;
            break;
    };
}
