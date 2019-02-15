#include <pokeagb/pokeagb.h>
#include "battle_events.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../abilities/battle_abilities.h"
#include "../battle_actions/actions.h"
#include "../status_effects/status.h"

extern u16 RandRange(u16, u16);
extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern struct move_procs basic_proc;

extern void ShowStatusAilmentGraphic(u8 bank, enum Effect status);
extern bool BankMonHasType(u8 bank, enum PokemonType type);

void set_status(u8 bank, enum Effect status, u8 inflictor)
{
    struct action* a =  prepend_action(inflictor, bank, ActionStatus, EventSetStatus);
    a->priv[0] = status;
}

void event_set_status(struct action* current_move)
{
    u8 bank = CURRENT_ACTION->target;
    u8 attacker = CURRENT_ACTION->action_bank;
    enum Effect status = CURRENT_ACTION->priv[0];
    bool status_applied = false;
    // lowest priority for override are types and current status
    switch (status) {
        case EFFECT_PARALYZE:
            // electric types are immune. Already status'd is immune
            if ((BankMonHasType(bank, TYPE_ELECTRIC)) || (gPkmnBank[bank]->battleData.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_BURN:
            // fire types are immune.  Already status'd is immune
            if ((BankMonHasType(bank, TYPE_FIRE)) || (gPkmnBank[bank]->battleData.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_POISON:
        case EFFECT_BAD_POISON:
            if (gPkmnBank[bank]->battleData.status != AILMENT_NONE) {
                status_applied = false;
                break;
            }
            // corrosion ability on attacker makes ability always succeed
            if (BANK_ABILITY(attacker) == ABILITY_CORROSION) {
                status_applied = true;
                break;
            }
            // poison and steel types are immune. Already status'd is immune
            if ((BankMonHasType(bank, TYPE_POISON)) || (BankMonHasType(bank, TYPE_STEEL))) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_SLEEP:
            // sleep isn't affected by type
            if ((gPkmnBank[bank]->battleData.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
            break;
        case EFFECT_FREEZE:
            // fire types cannot be frozen
            if ((BankMonHasType(bank, TYPE_FIRE)) || (gPkmnBank[bank]->battleData.status != AILMENT_NONE)) {
                status_applied = false;
            } else {
                status_applied = true;
            }
			break;
        case EFFECT_CONFUSION:
            // Confusion isn't affected by type
            if (gPkmnBank[bank]->battleData.pseudo_ailment != AILMENT_CONFUSION)
                status_applied = true;
			break;
        case EFFECT_CURE:
            // cure status
			status_applied = true;
            break;
        case EFFECT_INFACTUATION:
            if (gPkmnBank[bank]->battleData.pseudo_ailment != AILMENT_INFACTUATE)
                status_applied = true;
            break;
        case EFFECT_NONE:
        default:
            end_action(CURRENT_ACTION);
            return;
    };

    // back up cbs
    u8 old_index = CB_EXEC_INDEX;
    u32* old_execution_array = push_callbacks();
    bool executor = gBattleMaster->executing;
    for (u8 i = 0; i < BANK_MAX; i++) {
        u8 ability = gPkmnBank[i]->battleData.ability;
        if ((abilities[ability].on_status) && (ACTIVE_BANK(i)))
            AddCallback(CB_ON_STATUS, 0, 0, i, (u32)abilities[ability].on_status);
    }

    // execute cbs
    BuildCallbackExecutionBuffer(CB_ON_STATUS);
    gBattleMaster->executing = true;
    while (gBattleMaster->executing) {
        if (!PopCallback(bank, status)) {
            restore_callbacks(old_execution_array);
            CB_EXEC_INDEX = old_index;
            gBattleMaster->executing = executor;
            QueueMessage(0, bank, STRING_AILMENT_IMMUNE, status);
            end_action(CURRENT_ACTION);
            return;
        }
    }
    restore_callbacks(old_execution_array);
    CB_EXEC_INDEX = old_index;
    gBattleMaster->executing = executor;

    if (status_applied) {
        if (statuses[status].on_inflict) {
            statuses[status].on_inflict(bank);
            ShowStatusAilmentGraphic(bank, status);
        }
    } else {
        QueueMessage(0, bank, STRING_AILMENT_IMMUNE, status);
    }
    end_action(CURRENT_ACTION);
}
