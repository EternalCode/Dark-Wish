#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_slide_in_data/battle_obj_sliding.h"
#include "battle_data/battle_state.h"
#include "battle_events/battle_events.h"
#include "battle_text/battle_textbox_gfx.h"
#include "abilities/battle_abilities.h"

extern void battle_loop(void);
extern void UpdatePKMNBank(u8 bank, struct SwitchingFlagsToPass* flags);
extern void PlayerThrowBallAndMoveScene(struct Sprite*);
extern void TaskPlayerHPBoxSlideIn(u8 taskId);
extern void TaskBackspriteBob(u8 task_id);
extern void BankSelectOption(u8 bank);
extern void PickBattleTypeEncounterMsg(enum BattleTypes);
extern void SortBanksBySpeed(u8* activeBanks, u8 index);


void StartWildBattle()
{
    switch (gMain.state) {
        case 0:
            LoadPalette((void*)stdpal_get(0), 16*rboxes[0x18 & 0x3F].pal_id, 32);
            PickBattleTypeEncounterMsg(battle_type_flag);
            ShowBattleMessage((u8*)string_buffer, 0x18);
            gMain.state++;
            break;
        case 1:
            if (!dialogid_was_acknowledged(0x18 & 0x3F)) {
                gSprites[BattleEntryWindows->player_trainer_objid].animNum++;
                gSprites[BattleEntryWindows->player_trainer_objid].callback = PlayerThrowBallAndMoveScene;
                gSprites[BattleEntryWindows->player_trainer_objid].data[2] = PLAYER_SINGLES_BANK;
                gBattleAnimationStatus = 1;
                gMain.state++;
            }
            break;
        case 2:
            if (gBattleAnimationStatus)
                return;
            // create and slide into place HPbox
            CreateTask(TaskPlayerHPBoxSlideIn, 1);
            gBattleAnimationStatus = 1;
            gMain.state++;
            break;
        case 3:
        {
            // wait for hp sliding animations to finish
            if (gBattleAnimationStatus)
                return;

            // up and down movement of the active moving Pokemon
            u8 taskId = CreateTask(TaskBackspriteBob, 1);
            tasks[taskId].priv[0] = PLAYER_SINGLES_BANK;

            // build gPkmnBank data once animation is finished
            struct SwitchingFlagsToPass* flags = (struct SwitchingFlagsToPass*)malloc_and_clear(sizeof(struct SwitchingFlagsToPass));
            flags->pass_status = true;
            flags->pass_stats = false;
            flags->pass_atk_history = false;
            flags->pass_disables = false;
            UpdatePKMNBank(PLAYER_SINGLES_BANK, flags);
            UpdatePKMNBank(OPPONENT_SINGLES_BANK, flags);
            free(flags);
            free(BattleEntryWindows);
            gMain.state++;
        }
        case 4:
        {
            u8 activeBanks[4] = {0x3F, 0x3F, 0x3F, 0x3F};
            u8 index = 0;
            for (u8 i = 0 ; i < BANK_MAX; i++) {
                if (gPkmnBank[i]->battleData.is_active_bank) {
                    activeBanks[index] = i;
                    index++;
                }
            }
            SortBanksBySpeed(&activeBanks[0], index);
            ACTION_HEAD = add_action(0xFF, 0xFF, ActionHighPriority, EventEndAction);
            CURRENT_ACTION = ACTION_HEAD;
            for (u8 i = 0; i < index; i++) {
                if (ACTIVE_BANK(activeBanks[i])) {
                    u8 ability = gPkmnBank[activeBanks[i]]->battleData.ability;
                    if (abilities[ability].on_start) {
                        abilities[ability].on_start(activeBanks[i], activeBanks[i], NULL, NULL);
                    }
                }
            }
            SetMainCallback(battle_loop);
			extern void TestAnimation(void);
			TestAnimation();
            gMain.state = 0;
            //BankSelectOption(PLAYER_SINGLES_BANK);
            break;
        }
        default:
            break;
    };
}


/* Called right after sliding in effects have finished executing. */
void StartBattle()
{
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
            SetMainCallback(StartWildBattle);
            break;
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            dprintf("FAILED to select a valid battle mode.\n");
            break;
    };
    gMain.state = 0;
}
