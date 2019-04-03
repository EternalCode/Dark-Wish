#include <pokeagb/pokeagb.h>

#define DIR_LEFT 0x03
#define DIR_RIGHT 0x04
#define DIR_DOWN_AND_LEFT 0x05
#define DIR_DOWN_AND_RIGHT 0x06
#define DIR_UP_AND_LEFT 0x07
#define DIR_UP_AND_RIGHT 0x08

extern void dprintf(const char * str, ...);
extern void GetPlayerPosition(struct MapPosition* p);
u8 GetPlayerSidewaysstairsAction(u8 dir, u8 behaviour, u8 type);

void PlayerSetAnimId(u8 movementActionId, u8 copyableMovement)
{
    if (!PlayerIsAnimActive()) {
        PlayerSetCopyableMovement(copyableMovement);
        EventObjectSetHeldMovement(&gEventObjects[gPlayerAvatar.eventObjectId], movementActionId);
    }
}

void PlayerWalkDirection(u8 dir)
{
    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = GetWalkNormalMovementAction(dir);
    dprintf("behaviour is %x, DIR is %d\n", behaviour, dir);
    if (dir >= 3 && dir <= 4) {
        struct MapPosition playerPos;
        GetPlayerPosition(&playerPos);
        GetInFrontOfPlayerPosition(&playerPos);
        u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
        // right stairs you should climb if next tile is 0xB1
        if (behaviourFront == 0xB1 && dir == 4) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 0);
        } else if (behaviourFront == 0xB0 && dir == 3) {
            // left stairs you should climb if next tile is B0
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 0);
        } else if (behaviour == 0xB0 || behaviour == 0xB1) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviour, 0);
        }
    }
    PlayerSetAnimId(movement, 2);
}


void PlayerRunDirection(u8 dir)
{
    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = 0;
    if (behaviour == 0xB0 && (dir >= 3 && dir <= 4)) {
        // left ascending stairs
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 1);
    } else if (behaviour == 0xB1 && (dir >= 3 && dir <= 4)) {
        // right ascending stairs
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 1);
    } else {
        movement = GetPlayerRunMovementAction(dir);
    }
    PlayerSetAnimId(movement, 2);
}


void PlayerBikeDirection(u8 dir)
{
    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = 0;
    if (behaviour == 0xB0 && (dir >= 3 && dir <= 4)) {
        // left ascending stairs
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 2);
    } else if (behaviour == 0xB1 && (dir >= 3 && dir <= 4)) {
        // right ascending stairs
        movement = GetPlayerSidewaysstairsAction(dir, behaviour, 2);
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
            if (behaviour == 0xB0) {
                // left ascending stair
                if (direction == 3) {
                    // move diagonally left up
                    return 0xB6;
                } else {
                    // move diagonally right up
                    return 0xB7;
                }
            } else {
                if (direction == 3) {
                    // move diagonally left down
                    return 0xB8;
                } else {
                    // move diagonally right down
                    return 0xB9;
                }
            }
            break;
        case 1:
            // run table
            return 0xB6;
            //return run_table[behaviour - 0xB0][direction];
            break;
        case 2:
            // bike table
            return 0xB6;
            //return bike_table[behaviour - 0xB0][direction];
            break;
    };
    return 0;
}


u8 SidewaysStairsUpdateToCoords(u8 dir, struct EventObject* EventObject)
{
    u8 behaviour = MapGridGetMetatileBehaviorAt(EventObject->currentCoords.x, EventObject->currentCoords.y);
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


u8 Bike_CheckCollisionTryAdvanceCollisionCount(struct EventObject *EventObject, s16 x, s16 y, u8 direction, u8 metatitleBehavior)
{
    u8 collision = CheckForEventObjectCollision(EventObject, x, y, direction, metatitleBehavior);
    if (collision == 0 && metatitleBehavior == 0xA)
        return 2;
    return collision;
}


u8 GetBikeCollisionType(u8 direction)
{
    u8 dir = direction;
    struct EventObject *playerMapObj = &gEventObjects[gPlayerAvatar.eventObjectId];
    s16 x = playerMapObj->currentCoords.x;
    s16 y = playerMapObj->currentCoords.y;
    u8 metatitleBehavior = MapGridGetMetatileBehaviorAt(x, y);
    MoveCoords(SidewaysStairsUpdateToCoords(dir, playerMapObj), &x, &y);
    return Bike_CheckCollisionTryAdvanceCollisionCount(playerMapObj, x, y, direction, metatitleBehavior);
}
