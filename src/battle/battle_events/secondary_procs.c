#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../abilities/battle_abilities.h"


extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void set_status(u8 bank, enum Effect status, u8 inflictor);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 RandRange(u16 min, u16 max);

/* Boost event */
void event_move_boosts(struct action* current_action)
{
    u8 bank = current_action->action_bank;
    u16 t_ability = BANK_ABILITY(TARGET_OF(bank));
    if (abilities[t_ability].a_flags | A_FLAG_OPP_SECONDARIES_PREVENT) {
        CURRENT_ACTION->event_state++;
        return;
    }
    if (B_FAINTED(bank)) {
        CURRENT_ACTION->event_state++;
        return;
    }
    // back up cbs
    u32* old_execution_array = push_callbacks();
    u8 old_index = CB_EXEC_INDEX;
    // Stat modifying callbacks
    build_execution_order(CB_ON_BEFORE_STAT_MOD);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        pop_callback(bank, NULL);
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;

	/* first step is to apply user boosts */
	for (u8 i = 0; i < 8; i++) {
		if (B_USER_STAT_MOD_CHANCE(bank, i) >= RandRange(0, 100)) {
			stat_boost(bank, i, B_USER_STAT_MOD_AMOUNT(bank, i), bank);
			B_USER_STAT_MOD_CHANCE(bank, i) = 0;
            return;
		}
	}

	/* second step is to apply target boosts */
	for (u8 i = 0; i < 8; i++) {
		if (B_TARGET_STAT_MOD_CHANCE(bank, i) >= RandRange(0, 100)) {
			stat_boost(TARGET_OF(bank), i, B_TARGET_STAT_MOD_AMOUNT(bank, i), bank);
			B_TARGET_STAT_MOD_CHANCE(bank, i) = 0;
            return;
		}
	}
    CURRENT_ACTION->event_state++;
}


/* Ailment events */
void event_move_ailments(struct action* current_action)
{
    u8 bank = current_action->action_bank;
    u16 t_ability = BANK_ABILITY(TARGET_OF(bank));
    if (abilities[t_ability].a_flags | A_FLAG_OPP_SECONDARIES_PREVENT) {
        CURRENT_ACTION->event_state++;
        return;
    }
    if (B_FAINTED(bank)) {
        CURRENT_ACTION->event_state++;
        return;
    }
	if (B_AILMENT_PROCS_CHANCE_USER(bank) >= RandRange(1, 100)) {
		// apply status user
		B_AILMENT_PROCS_CHANCE_USER(bank) = 0;
		set_status(bank, B_AILMENT_PROCS_USER(bank), bank);
		return;
	}

	if (B_AILMENT_PROCS_CHANCE_TARGET(bank) >= RandRange(1, 100)) {
		// apply status target
		B_AILMENT_PROCS_CHANCE_TARGET(bank) = 0;
		set_status(TARGET_OF(bank), B_AILMENT_PROCS_TARGET(bank), bank);
		return;
	}
    CURRENT_ACTION->event_state++;
}
