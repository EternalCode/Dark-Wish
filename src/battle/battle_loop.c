#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"
#include "moves/moves.h"
#include "battle_text/battle_pick_message.h"
#include "battle_events/battle_events.h"
#include "../pokemon/pokemon.h"
#include "hpboxes/hpbox_positional_data.h"

extern void dprintf(const char * str, ...);
extern void ResetBankTurnBits(u8 bank);
extern void BankSelectOption(u8 bank);
extern void SyncBankToParty(u8 bank);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void WildBattleAIPickMove(u8 bank);
extern bool ValidateBankMove(u8 bank);
extern void CreateActionsForActiveBanks(void);
extern void TaskBackspriteBob(u8 taskid);
extern u16 BankInterpretSelectedMove(u16);


EventCallback gWildBattleEvents[] = {
    event_on_start, // pre turn effects
    /* Pre-move */
    event_run_flee,
    event_pre_switch,
    event_switch,
    event_after_switch,

    /* Run Move */
    event_before_move,
    event_config_move_hitlist,
    event_pre_move_hit, // loop through hit list and pick next target. If no target, go to aftermove
    event_move_tryhit_external, // multi hits subsequent hits start here
    event_move_damage,
    event_move_heal,
    event_move_effect,
    event_move_recoil,
    event_move_drain,
    event_move_boosts,
    event_move_ailments,
    event_multi_hit, // multi hits loop back to EventMoveHit or EventPreMoveHit
    event_after_move,
    event_fainted,


    /* Misc Events */
    event_move_failed,
    event_peek_message,
    init_damage,
    init_heal,
    event_stat_boost,
    event_drain,
    event_set_status,
    event_faint,
    end_action,
    event_set_inactive,
    event_residual_effects,
    wild_battle_status_update,
    event_play_animation,
    event_forced_switch,
    end_battle,
};


void battle_loop()
{
    CURRENT_ACTION = ACTION_HEAD;
    if (ACTION_HEAD != NULL) {
        //dprintf("action: %x\n", ACTION_HEAD);
        // Don't run actions for fainted banks
        if (!(ACTIVE_BANK(ACTION_HEAD->action_bank) || ACTION_HEAD->active_override)) {
            end_action(ACTION_HEAD);
            return;
        }
        // the event is responsible for adjusting the action state of the top level action
        gWildBattleEvents[EVENT_STATE](ACTION_HEAD);
    } else {
        // all actions complete...
        dprintf("completed actions\n");
        for (u8 i = 0; i < BANK_MAX; i++) {
            if (!ACTIVE_BANK(i)) continue;
            gPkmnBank[i]->battleData.first_turn = false;
            gPkmnBank[i]->battleData.justSwitched = false;
            ResetBankTurnBits(i);
        }
        update_callbacks();
        BankSelectOption(PLAYER_SINGLES_BANK);
        gMain.state = 0;
    }
}


void validate_player_selected_move()
{
    // get and set currently selected move
    CURRENT_ACTION = ACTION_HEAD;
    u16 move_player = BankInterpretSelectedMove(PLAYER_SINGLES_BANK);
    CURRENT_MOVE(PLAYER_SINGLES_BANK) = move_player;
    if (!ValidateBankMove(PLAYER_SINGLES_BANK)) {
        BankSelectOption(PLAYER_SINGLES_BANK);
        return;
    }
    WildBattleAIPickMove(OPPONENT_SINGLES_BANK);
    DestroyTask(task_find_id_by_functpr(TaskBackspriteBob));
    u8 objid = gPkmnBank[PLAYER_SINGLES_BANK]->objid;
    u8 species_y = gMonBackPicCoords[B_SPECIES(PLAYER_SINGLES_BANK)].y_offset;
    gSprites[objid].pos1.y = 80 + species_y;
    objid = gPkmnBank[PLAYER_SINGLES_BANK]->objid_hpbox[0];
    gSprites[objid].pos1.y = HPBOX_PLAYER_SINGLE_Y;
    objid = gPkmnBank[PLAYER_SINGLES_BANK]->objid_hpbox[1];
    gSprites[objid].pos1.y = HPBOX_PLAYER_SINGLE_Y;
    objid = gPkmnBank[PLAYER_SINGLES_BANK]->objid_hpbox[2];
    gSprites[objid].pos1.y = HPBAR_PS_Y;
    objid = gPkmnBank[PLAYER_SINGLES_BANK]->objid_hpbox[3];
    gSprites[objid].pos1.y = HPBOX_STATUS_PLAYER_SINGLE_X;
    CreateActionsForActiveBanks();
    SetMainCallback(battle_loop);
}

void end_battle(struct action* a)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i))
            SyncBankToParty(i);
    }
    clear_actions();
    free(gBattleMaster);
    free(gPkmnBank[0]);
    exit_to_overworld_2_switch();
    SetMainCallback(c1_overworld);
}
