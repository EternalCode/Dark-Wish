#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_slide_in_data/battle_obj_sliding.h"
#include "battle_data/battle_state.h"
#include "battle_text/battle_textbox_gfx.h"
#include "battle_actions/actions.h"

extern void Setup(void);
extern void TestBattleDataInit(void);
extern void AllocateBattleStructs(void);
extern void TransitionWildBattle(void);


/* Battle Entry point */
void BattleEngineStartup()
{
    SetMainCallback(NULL);
    // reset game screen and callbacks
    Setup();
    HideBg(0);
    HideBg(1);
    HideBg(2);
    HideBg(3);
    AllocateBattleStructs();
    // battle testing presets initialize
    TestBattleDataInit();
    battle_type_flag = BATTLE_MODE_WILD;
    SetMainCallback(TransitionWildBattle);
    gMain.state = 0;
}


void NullBattleSpriteTracker()
{
    // set objids to 0x3f, symbolizing no valid objid set.
    for (u8 i = 0; i < 10; ++i) {
        gBattleMaster->switch_main.type_objid[i] = 0x3F;
        if (i < 6)
            gBattleMaster->switch_main.icon_objid[i] = 0x3F;
        if (i < 3)
            gBattleMaster->switch_main.slider_objid[i] = 0x3F;
    }

    gBattleMaster->battle_cursor.objid_mv_crsr[0] = 0x3F;
    gBattleMaster->battle_cursor.objid_mv_crsr[1] = 0x3F;

    for (u8 i = 0; i < 4; i++) {
        gBattleMaster->type_objid[i] = 0x3F;
        gBattleMaster->move_pss_objid[i] = 0x3F;
        gBattleMaster->move_pp_objid[i] = 0x3F;
        gBattleMaster->move_name_objid[i] = 0x3F;
    }
}


void AllocateBattleStructs()
{
    // All 4 banks
    void* p_bank_data = malloc_and_clear(sizeof(struct pkmn_bank) * 4);
    for(u8 i = 0; i < BANK_MAX; i++) {
        gPkmnBank[i] = (struct pkmn_bank*)(p_bank_data + (sizeof(struct pkmn_bank) * i));
        for(u8 j = 0; j < 4; j++) {
            gPkmnBank[i]->objid_hpbox[j] = 0x3F;
        }
        gPkmnBank[i]->objid = 0x3F;
    }
    // Battle entrance tracker
    BattleEntryWindows = (struct bs_elements_positions*)malloc_and_clear(sizeof(struct bs_elements_positions));
    // Battle state master initialize
    gBattleMaster = (struct battle_main*)malloc_and_clear(sizeof(struct battle_main));

    // actions linked list head nullify
    gBattleMaster->action_head = NULL;
    NullBattleSpriteTracker();
}


void Task_BattleStart(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    if (t->priv[3]) {
        // wait transition to finish
        if (IsBattleTransitionDone()) {
            gWildEncounterImmunitySteps = 0;
            task_del(taskId);
            BattleEngineStartup();
        }
    } else {
        t->priv[3] = true;
        BattleTransition_StartOnField(tasks->priv[1]);
    }
}
