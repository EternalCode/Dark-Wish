#include <pokeagb/pokeagb.h>
#include "../global.h"

#define c2_overworld (0x080565B4|1)

MainCallback call_203AE8C = (MainCallback)0x0811092;
extern bool ProcessPlayerFieldInput(struct FieldInput *input);


void FieldClearPlayerInput(struct FieldInput *input)
{
    input->pressedAButton = false;
    input->checkStandardWildEncounter = false;
    input->pressedStartButton = false;
    input->pressedSelectButton = false;
    input->heldDirection = false;
    input->heldDirection2 = false;
    input->tookStep = false;
    input->pressedBButton = false;
    input->input_field_1_0 = false;
    input->input_field_1_1 = false;
    input->input_field_1_2 = false;
    input->input_field_1_3 = false;
    input->dpadDirection = 0;
}


void FieldGetPlayerInput(struct FieldInput *input, u16 newKeys, u16 heldKeys)
{
    u8 tileTransitionState = gPlayerAvatar.tileTransitionState;
    u8 runningState = gPlayerAvatar.runningState;
    u8 forcedMove = MetatileBehavior_IsForcedMovementTile(GetPlayerCurMetatileBehavior(runningState));
    if ((tileTransitionState == T_TILE_CENTER && forcedMove == false) || tileTransitionState == T_NOT_MOVING)
    {
        if (GetPlayerSpeed() != 4)
        {
            if (newKeys & KEY_START)
                input->pressedStartButton = true;
            if (newKeys & KEY_SELECT)
                input->pressedSelectButton = true;
            if (newKeys & KEY_A)
                input->pressedAButton = true;
            if (newKeys & KEY_B)
                input->pressedBButton = true;
        }

        if (heldKeys & (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))
        {
            input->heldDirection = true;
            input->heldDirection2 = true;
        }
    }

    if (forcedMove == false)
    {
        if (tileTransitionState == T_TILE_CENTER && runningState == MOVING)
            input->tookStep = true;
        if (forcedMove == false && tileTransitionState == T_TILE_CENTER)
            input->checkStandardWildEncounter = true;
    }

    if (heldKeys & KEY_UP)
        input->dpadDirection = DIR_NORTH;
    else if (heldKeys & KEY_DOWN)
        input->dpadDirection = DIR_SOUTH;
    else if (heldKeys & KEY_LEFT)
        input->dpadDirection = DIR_WEST;
    else if (heldKeys & KEY_RIGHT)
        input->dpadDirection = DIR_EAST;
}


void C1Overworld()
{
    if ((gMain.callback2 != (MainCallback)c2_overworld)) return;
    enum Keypad newKeys = gMain.newKeys;
    enum Keypad heldKeys = gMain.heldKeys;
    struct FieldInput inputStruct;
    sub_805BEB8(); // something to do with player animation
    memset(&inputStruct, 0, sizeof(struct FieldInput));
    FieldGetPlayerInput(&inputStruct, newKeys, heldKeys);
    if ((script_env_2.enabled)) return;
    if (ProcessPlayerFieldInput(&inputStruct) == 1) {
        script_env_2.enabled = 1;
        HideMapPopUpWindow();
    } else {
        player_step(inputStruct.dpadDirection, newKeys, heldKeys);
    }
}


#undef c2_overworld
