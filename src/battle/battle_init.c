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


const u8 WildBattleTransitionIds[] = {
    8, // indoors maybe, player level > opp level
    9, // indoors maybe, player level < opp level

    5, // outdoors on path maybe. player level > opp level
    10, // outdoors on path maybe, player level > opp level

    0, // Flash used on map, player higher level
    10, // flash used on map, opponent higher level

    7, // Grass transition Player is higher level
    6, // Grass transition Player is lower level
};


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


void Task_WildBattleStart(u8 taskId)
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
        // check if map is indoors
        t->priv[3] = true;
        BattleTransition_StartOnField(tasks->priv[1]);
    }
}


void StartWildBattleTransition(u8 environment)
{
    // get opponent's level
    u8 oppLevel = pokemon_getattr(party_opponent, REQUEST_LEVEL, NULL);
    u8 playerLevel = 0;
    u8 battleTransitionId = 0xFF;
    // get player leading mon level
    for (u8 i = 0; i < 6; i++) {
        if (pokemon_getattr(&party_player[i], REQUEST_SPECIES2, NULL)) {
            if (pokemon_getattr(&party_player[i], REQUEST_CURRENT_HP, NULL)) {
                playerLevel = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);
                break;
            }
        }
    }
    if (gSaveBlock1Ptr->flashLevel) {
        // flash used on map
        battleTransitionId = WildBattleTransitionIds[4 + (oppLevel > playerLevel)];
    } else if (environment != 1) {
        if (currentmap_header.light == 4) {
            // outside path maybe?
            battleTransitionId = WildBattleTransitionIds[2 + (oppLevel > playerLevel)];
        }
        if (currentmap_header.light != 5) {
            // inside probably
            battleTransitionId = WildBattleTransitionIds[0 + (oppLevel > playerLevel)];
        }
    }
    if (battleTransitionId == 0xFF) {
        // grass
        battleTransitionId = WildBattleTransitionIds[6 + (oppLevel > playerLevel)];
    }
    battle_type_flag = BATTLE_MODE_WILD_DOUBLE;
    u8 taskId = task_add(Task_WildBattleStart, 0);
    tasks[taskId].priv[1] = battleTransitionId;
    PlayMapChosenOrBattleBGM(0);
}
