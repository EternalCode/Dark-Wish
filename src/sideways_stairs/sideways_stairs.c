#include <pokeagb/pokeagb.h>

#define DIR_LEFT 0x03
#define DIR_RIGHT 0x04
#define DIR_DOWN_AND_LEFT 0x05
#define DIR_DOWN_AND_RIGHT 0x06
#define DIR_UP_AND_LEFT 0x07
#define DIR_UP_AND_RIGHT 0x08

extern void dprintf(const char * str, ...);
u8 GetPlayerSidewaysstairsAction(u8 dir, u8 behaviour, u8 type);

/* Sideways stairs movement state IDs */
const u8 walk_entry_0[5] = {0x10, 0x10, 0x11, 0xAC, 0xAB};
const u8 walk_entry_1[5] = {0x10, 0x10, 0x11, 0xAC, 0x13};
const u8 walk_entry_2[5] = {0x10, 0x10, 0x11, 0x12, 0xAB};
const u8 walk_entry_3[5] = {0x10, 0x10, 0x11, 0xAA, 0xAD};
const u8 walk_entry_4[5] = {0x10, 0x10, 0x11, 0x12, 0xAD};
const u8 walk_entry_5[5] = {0x10, 0x10, 0x11, 0xAA, 0x13};

const u8 bike_entry_0[5] = {0x31, 0x31, 0x32, 0xB4, 0xB3};
const u8 bike_entry_1[5] = {0x31, 0x31, 0x32, 0xB4, 0x34};
const u8 bike_entry_2[5] = {0x31, 0x31, 0x32, 0x33, 0xB3};
const u8 bike_entry_3[5] = {0x31, 0x31, 0x32, 0xB2, 0xB5};
const u8 bike_entry_4[5] = {0x31, 0x31, 0x32, 0x33, 0xB5};
const u8 bike_entry_5[5] = {0x31, 0x31, 0x32, 0xB2, 0x34};

const u8 run_entry_0[5] = {0x3D, 0x3D, 0x3E, 0xB1, 0xAF};
const u8 run_entry_1[5] = {0x3D, 0x3D, 0x3E, 0xB1, 0x40};
const u8 run_entry_2[5] = {0x3D, 0x3D, 0x3E, 0x3F, 0xAF};
const u8 run_entry_3[5] = {0x3D, 0x3D, 0x3E, 0xAE, 0xB0};
const u8 run_entry_4[5] = {0x3D, 0x3D, 0x3E, 0x3F, 0xB0};
const u8 run_entry_5[5] = {0x3D, 0x3D, 0x3E, 0xAE, 0x40};

const u8* walk_table[6] = {(u8*)(walk_entry_0), (u8*)(walk_entry_1), (u8*)(walk_entry_2), (u8*)(walk_entry_3), (u8*)(walk_entry_4), (u8*)(walk_entry_5)};
const u8* bike_table[6] = {(u8*)(bike_entry_0), (u8*)(bike_entry_1), (u8*)(bike_entry_2), (u8*)(bike_entry_3), (u8*)(bike_entry_4), (u8*)(bike_entry_5)};
const u8* run_table[6] = {(u8*)(run_entry_0), (u8*)(run_entry_1), (u8*)(run_entry_2), (u8*)(run_entry_3), (u8*)(run_entry_4), (u8*)(run_entry_5)};

void PlayerSetAnimId(u8 movementActionId, u8 copyableMovement)
{
    if (!PlayerIsAnimActive()) {
        PlayerSetCopyableMovement(copyableMovement);
        EventObjectSetHeldMovement(&mapObjects[gPlayerAvatar.mapObjectId], movementActionId);
    }
}

void PlayerWalkDirection(u8 dir)
{

    struct MapObject* playerObject = &mapObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = 0;
    if (behaviour < 0xB0 || behaviour > 0xB5) {
        movement = GetWalkNormalMovementAction(dir);
    } else {
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 0);
    }
    PlayerSetAnimId(movement, 2);
}


void PlayerRunDirection(u8 dir)
{
    struct MapObject* playerObject = &mapObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = 0;
    if (behaviour < 0xB0 || behaviour > 0xB5) {
        movement = GetPlayerRunMovementAction(dir);
    } else {
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 1);
    }
    PlayerSetAnimId(movement, 2);
}


void PlayerBikeDirection(u8 dir)
{
    struct MapObject* playerObject = &mapObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = 0;
    if (behaviour < 0xB0 || behaviour > 0xB5) {
        movement = GetPlayerBikeMovementAction(dir);
    } else {
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 2);
    }
    PlayerSetAnimId(movement, 2);
}


u8 GetPlayerSidewaysstairsAction(u8 dir, u8 behaviour, u8 type)
{
    u8 direction = dir > 4 ? 0 : dir;
    switch(type) {
        case 0:
            //walk table
            return walk_table[behaviour - 0xB0][direction];
            break;
        case 1:
            // run table
            return run_table[behaviour - 0xB0][direction];
            break;
        case 2:
            // bike table
            return bike_table[behaviour - 0xB0][direction];
            break;
    };
    return 0;
}


u8 SidewaysStairsUpdateToCoords(u8 dir, struct MapObject* eventObject)
{
    u8 behaviour = MapGridGetMetatileBehaviorAt(eventObject->currentCoords.x, eventObject->currentCoords.y);
    switch (behaviour - 0xB0) {
        case 0:
            if (dir == DIR_LEFT) {
                return DIR_UP_AND_LEFT;
            } else if (dir == DIR_RIGHT) {
                return DIR_DOWN_AND_RIGHT;
            }
            break;
        case 1:
            if (dir == DIR_LEFT)
                return DIR_UP_AND_LEFT;
            break;
        case 2:
            if (dir == DIR_RIGHT)
                return DIR_DOWN_AND_RIGHT;
            break;
        case 3:
            if (dir == DIR_LEFT) {
                return DIR_DOWN_AND_LEFT;
            } else if (dir == DIR_RIGHT) {
                return DIR_UP_AND_RIGHT;
            }
            break;
        case 4:
            if (dir == DIR_RIGHT)
                return DIR_UP_AND_RIGHT;
            break;
        case 5:
            if (dir == DIR_LEFT)
                return DIR_DOWN_AND_LEFT;
            break;
        default:
            // normal
            break;
    };
    return dir;
}
