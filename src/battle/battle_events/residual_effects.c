#include <pokeagb/pokeagb.h>
#include "battle_events.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);


void event_residual_effects(struct action* current_action)
{
	switch (current_action->priv[0]) {
        case 0:
			for (u8 i = 0; i < BANK_MAX; i++) {
				u8 ability = gPkmnBank[i]->battleData.ability;
				if ((abilities[ability].on_residual) && (ACTIVE_BANK(i))) {
					AddCallback(CB_ON_RESIDUAL, 0, 0, i, (u32)abilities[ability].on_residual);
				}
			}
            BuildCallbackExecutionBuffer(CB_ON_RESIDUAL);
            gBattleMaster->executing = true;
            s8 last_index = -1;
            for (u8 i = 0; i < 4; i++) {
                if (ACTIVE_BANK(gBattleMaster->bankOrder[i]) && (!B_FAINTED(gBattleMaster->bankOrder[i])))
                    last_index++;
            }
            if (last_index < 0) {
                end_action(CURRENT_ACTION);
                return;
            }
            gBattleMaster->c1_prestate = last_index;
            current_action->priv[0]++;
            gBattleMaster->bank_state = 0;
            break;
        case 1:
			{
			u8 bank = gBattleMaster->bankOrder[gBattleMaster->bank_state];
			prepend_action(bank, NULL, ActionHighPriority, EventDoFaints);
            if (gBattleMaster->executing) {
                if (gBattleMaster->bank_state == gBattleMaster->c1_prestate) {
                    if (B_FAINTED(bank) == false) {
                        PopCallback(bank , CURRENT_MOVE(bank));
                    } else {
                        CB_EXEC_INDEX++;
                        if ((CB_EXEC_ORDER[CB_EXEC_INDEX] == ANON_CB_MAX) || (CB_EXEC_ORDER[CB_EXEC_INDEX - 1] == ANON_CB_MAX))
                            end_action(CURRENT_ACTION);
                    }
                    gBattleMaster->bank_state = 0;
                } else {
                    if (B_FAINTED(bank) == false)
                        run_callback(bank, CURRENT_MOVE(bank));
                    gBattleMaster->bank_state++;
                }
            } else {
                end_action(CURRENT_ACTION);
                return;
            }
            break;
			}
        };
}
