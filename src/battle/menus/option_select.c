#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../abilities/battle_abilities.h"
#include "../battle_events/battle_events.h"
#include "../battle_text/battle_textbox_gfx.h"

extern void validate_player_selected_move(void);
extern void battle_loop(void);
extern void VblankSPQ(void);
extern void VblankMergeMoveSelect(void);
extern void VblankMergeTextBox(void);
extern void load_icons_moves(u8 bank);
extern void update_cursor_move_select(u8 task_id);
extern void show_move_data(void);
extern void init_selection_cursor(u8 mode, u8 bank);
extern void dprintf(const char * str, ...);
extern void BankSelectOption2(void);
extern void switch_scene_main(void);
extern void free_unused_objs(void);
extern void free_battler_oams(void);
extern void event_peek_message(struct action* current_action);
extern void CpuFastSet(void* src, void* dst, u32 mode);
extern void SyncBankToParty(u8 bank);
extern void TaskBackspriteBob(u8 task_id);
extern void return_to_battle_bag(void);
extern bool bank_trapped(u8 bank);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

void (*sub_8107ECC)(u8, u8, MainCallback) = 0x8107DB5;


/* Fight menu and move menu selection. Preperation to go into battle loop*/

#define SELECTING_BANK gBattleMaster->option_selecting_bank

enum BattleMenuSelectionOptions {
    BaseMenuInitialize = 0,
    BaseMenuInputInterpret,
    FightOptionSelected_FirstTime,
    FightOptionSelected_FastLoad,
    SwitchOptionSelected,
    BagOptionSelected,
    RunOptionSelected,
    MenuWaitState,
    MoveSelectedExit,
};

/* Fight menu and move menu selection. Preperation to go into battle loop*/
void BankSelectOption(u8 bank)
{
    gBattleMaster->option_selecting_bank = bank;
    // check bank is skipping selection via move
    if ((HAS_VOLATILE(bank, VOLATILE_CHARGING)) ||
        (gPkmnBank[bank]->battleData.skip_move_select) ||
        (HAS_VOLATILE(bank, VOLATILE_RECHARGING))) {
        // jump straight to move validation
        SetMainCallback(validate_player_selected_move);
        return;
    }
    SetMainCallback(BankSelectOption2);
    gMain.state = BaseMenuInitialize;
}

void jump_switch_menu(enum switch_reason reason)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
    DestroyTask(task_find_id_by_functpr(TaskBackspriteBob));
    free_unused_objs();
    gBattleMaster->switch_main.position = 0;
    gBattleMaster->fight_menu_content_spawned  = 0;
    gBattleMaster->switch_main.reason = reason;
    gMain.state = 0;
    SyncBankToParty(gBattleMaster->option_selecting_bank);
    SetMainCallback(switch_scene_main);
}

void bag_prep()
{
    if (!gPaletteFade.active) {
        SetMainCallback(NULL);
        sub_8107ECC(5, 3, return_to_battle_bag);
        gpu_tile_bg_drop_all_sets(0);
        rboxes_free();
        free_battler_oams();
    }
}

void BankSelectOption2()
{
    // the new peek message
    if (ACTION_HEAD != NULL) {
        CURRENT_ACTION = ACTION_HEAD;
        event_peek_message(ACTION_HEAD);
        return;
    }
    switch (gMain.state) {
        case BaseMenuInitialize:
        {
            // initialize fight menu selection
            SetVBlankCallback(VblankSPQ);
            void* map_base = (void *)0x600F800;
            //memcpy(map_base, battle_textbox_action_selectMap, sizeof(battle_textbox_action_selectMap));
            CpuFastSet((void*)&battle_textbox_action_selectMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
            init_selection_cursor(1, 0);
            if (!task_is_running(TaskBackspriteBob)) {
                u8 taskId = CreateTask(TaskBackspriteBob, 1);
                tasks[taskId].priv[0] = PLAYER_SINGLES_BANK;
            }
            gBattleAnimationStatus = 1;
            gMain.state = BaseMenuInputInterpret;
            break;
        }
        case BaseMenuInputInterpret:
            // wait for input selection from fight menu
            if (gBattleAnimationStatus)
                return;
            // interpret selection
            switch (gBattleMaster->selected_option) {
                case OPTION_FIGHT:
                    if (gBattleMaster->fight_menu_content_spawned) {
                        gMain.state = FightOptionSelected_FastLoad;
                    } else {
                        gMain.state = FightOptionSelected_FirstTime;
                    }
                    break;
                case OPTION_POKEMON:
                    gMain.state = SwitchOptionSelected;
                    break;
                case OPTION_BAG:
                    gMain.state = BagOptionSelected;
                    break;
                case OPTION_RUN:
                    gMain.state = RunOptionSelected;
                    break;

            };
            break;
        case FightOptionSelected_FirstTime:
            /* FIGHT selected from fight menu */
            dprintf("opening fight menu for the first time for bank %d\n", SELECTING_BANK);
            // update tilemap
            SetVBlankCallback(VblankMergeMoveSelect);
            void* map_base = (void *)0x600F800;
            //memcpy(map_base, battle_textbox_move_selectMap, sizeof(battle_textbox_move_selectMap));
            CpuFastSet((void*)&battle_textbox_move_selectMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
            // init cursor
            init_selection_cursor(0, 0);

            // init move types
            load_icons_moves(SELECTING_BANK);
            // set into pause state
            gBattleAnimationStatus = 1;
            gMain.state = MenuWaitState;
            break;
        case FightOptionSelected_FastLoad:
            {
                SetVBlankCallback(VblankMergeMoveSelect);
                dprintf("opening fight menu fast load\n");
                void* map_base = (void *)0x600F800;
                //memcpy(map_base, battle_textbox_move_selectMap, sizeof(battle_textbox_action_selectMap));
                CpuFastSet((void*)&battle_textbox_move_selectMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
                show_move_data();
                tasks[CreateTask(update_cursor_move_select, 1)].priv[0] = 0;
                gBattleAnimationStatus = 1;
                gMain.state = MenuWaitState;
                break;
            }
        case SwitchOptionSelected:
            // POKEMON selection from fight menu
            jump_switch_menu(ViewPokemon);
            break;
        case BagOptionSelected:
        {
            // BAG selected from fight menu
            for (u8 i = 0; i < BANK_MAX; i++) {
                if (ACTIVE_BANK(i)) {
                    SyncBankToParty(i);
                }
            }
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
            DestroyTask(task_find_id_by_functpr(TaskBackspriteBob));
            free_unused_objs();
            gBattleMaster->fight_menu_content_spawned  = 0;
            gMain.state = 0;
            SetMainCallback(bag_prep);
            break;
        }
        case RunOptionSelected:
        {
            // RUN selected from fight menu
            // Check if Pokemon is trapped
            if (!bank_trapped(SELECTING_BANK)) {
                gPkmnBank[SELECTING_BANK]->battleData.isRunning = true;
                gMain.state = MoveSelectedExit;
            } else {
                ACTION_HEAD = add_action(0xFF, 0xFF, ActionHighPriority, EventEndAction);
                CURRENT_ACTION = ACTION_HEAD;
                // run trap override for running bank
                if (abilities[BANK_ABILITY(SELECTING_BANK)].on_trap_override) {
                    if (abilities[BANK_ABILITY(SELECTING_BANK)].on_trap_override(SELECTING_BANK, SELECTING_BANK, AttemptFlee)) {
                        // run silently, on trap override needs to create it's own message
                        free_unused_objs();
                        SetVBlankCallback((MainCallback)VblankMergeTextBox);
                        SetMainCallback(battle_loop);
                        gBattleMaster->fight_menu_content_spawned  = 0;
                        gMain.state = 0;
                        return;
                    }
                }
                free_unused_objs();
                QueueMessage(MOVE_NONE, SELECTING_BANK, STRING_TRAPPED_RUN, 0);
                SetVBlankCallback((MainCallback)VblankMergeTextBox);
                SetMainCallback(battle_loop);
                gBattleMaster->fight_menu_content_spawned  = 0;
                gMain.state = 0;
            }
            break;
        }
        case MenuWaitState:
            break;
        case MoveSelectedExit:
        {
            void* map_base = (void *)0x600F800;
            CpuFastSet((void*)&battle_textboxMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
            free_unused_objs();
            SetMainCallback(validate_player_selected_move);
            SetVBlankCallback((MainCallback)VblankMergeTextBox);
            gBattleMaster->fight_menu_content_spawned  = 0;
            gMain.state = 0;
            break;
        }
        case 9:
            // pick move validator function based on battle type
            return;
    };
}
