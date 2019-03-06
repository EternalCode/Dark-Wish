#include <pokeagb/pokeagb.h>
#include "../../global.h"

#define EventScript_EggHatch 0x081BF546
#define EventScript_RepelFinished 0x081BFB65

extern u8 CheckRegisteredDexnavMon(void);
extern bool DoWildEncounters(struct MapPosition* p);
extern bool CheckTrainerBattle(struct MapPosition* p);

void GetPlayerPosition(struct MapPosition* p)
{
    p->x = gEventObjects[gPlayerAvatar.spriteId].currentCoords.x;
    p->y = gEventObjects[gPlayerAvatar.spriteId].currentCoords.y;
    p->height = gEventObjects[gPlayerAvatar.spriteId].elevation;
}

void HappinessPerStep()
{
    // increment happiness pedometer
    u16* happinessPedometer = GetVarPointer(0x4021);
    *happinessPedometer += 1;
    if (*happinessPedometer >= 128) {
        *happinessPedometer = 0;
        // 50% chance to give happiness to party
        if (rand() % 2) {
            for (u8 i = 0; i < gPartyCount; i++) {
                if (pokemon_getattr(&party_player[i], REQUEST_SANITY_X6, NULL)) continue;
                u32 happiness = pokemon_getattr(&party_player[i], REQUEST_HAPPINESS, NULL);
                if (happiness < 99) {
                    happiness += 2;
                } else if (happiness < 255) {
                    happiness += 1;
                }
                pokemon_setattr(&party_player[i], REQUEST_HAPPINESS, &happiness);
            }
        }
    }
}

bool AttemptEggHatching()
{
    for (u8 i = 0; i < gPartyCount; i++) {
        struct Pokemon *p = &party_player[i];
        if (!pokemon_getattr(p, REQUEST_IS_EGG, NULL)) continue;
        if (pokemon_getattr(p, REQUEST_SANITY_X4, NULL)) continue;
        u16 happiness = pokemon_getattr(p, REQUEST_HAPPINESS, NULL);
        u8 amount = 0;
        // check party for flamebody or magma armor
        if (PartyHasAbility(ABILITY_FLAME_BODY) || PartyHasAbility(ABILITY_MAGMA_ARMOR)) {
            amount = 2;
        } else {
            amount = 1;
        }
        happiness = (amount > happiness) ? happiness : happiness - amount;
        pokemon_setattr(p, REQUEST_HAPPINESS, &happiness);
        if (happiness == 0) {
            // hatch egg script
            var_8004 = i;
            ScriptContext1_SetupScript((void*)EventScript_EggHatch);
            return 1;
        }
    }
    return 0;
}


bool TryStartMiscWalkingScripts(u16 metatileBehavior)
{
    // every 127 steps boost happiness
    HappinessPerStep();
    // attempt to hatch an egg in your party
    AttemptEggHatching();
    // repel
    u16 repelSteps = VarGet(0x4020);
    if (repelSteps == 1) {
        VarSet(0x4020, 0);
        ScriptContext1_SetupScript((void*)EventScript_RepelFinished);
        return true;
    } else {
        VarSet(0x4020, repelSteps - 1);
    }
    return false;
}


bool TryStartStepBasedScript(struct MapPosition* playerPos, u16 metatileBehavior)
{
    if (TryStartCoordEventScript(playerPos) == true)
        return true;
    if (TryStartWarpEventScript(playerPos, metatileBehavior) == true)
        return true;
    if (TryStartMiscWalkingScripts(metatileBehavior) == true)
        return true;
    return false;
}


bool ProcessPlayerFieldInput(struct FieldInput *input)
{
    struct MapPosition playerPos;
    u8 playerDirection = gEventObjects[gPlayerAvatar.spriteId].direction & 0xF;
    GetPlayerPosition(&playerPos);
    u16 metatileBehavior = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);

    if (CheckTrainerBattle(&playerPos) || mapheader_run_first_tag2_script_list_match()) {
        dprintf("trainer is wanting to battle\n");
        return true;
    }

    if (input->tookStep) {
        if (TryStartStepBasedScript(&playerPos, metatileBehavior) == true)
            return true;
    }

    if (input->checkStandardWildEncounter && DoWildEncounters(&playerPos) == true) {
        return true;
    }

    if (input->heldDirection && input->dpadDirection == playerDirection) {
        if (TryArrowWarp(&playerPos, metatileBehavior, playerDirection) == true)
            return true;
    }

    GetInFrontOfPlayerPosition(&playerPos);
    metatileBehavior = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
    if (input->pressedAButton && TryStartInteractionScript(&playerPos, metatileBehavior, playerDirection) == true)
        return true;

    GetPlayerPosition(&playerPos);
    metatileBehavior = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
    if (input->heldDirection2 && input->dpadDirection == playerDirection) {
        if (TryDoorWarp(&playerPos, metatileBehavior, playerDirection) == true)
            return true;
    }
    if (input->pressedStartButton) {
        PlaySE(SE_WIN_OPEN);
        ShowStartMenu();
        return true;
    }
    if (input->pressedSelectButton) {
        if (UseRegisteredKeyItemOnField())
            return true;
        if (CheckRegisteredDexnavMon())
            return true;

    }
    return false;
}
