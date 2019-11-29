#include <pokeagb/pokeagb.h>

#define DIR_LEFT 0x03
#define DIR_RIGHT 0x04
#define DIR_DOWN_AND_LEFT 0x05
#define DIR_DOWN_AND_RIGHT 0x06
#define DIR_UP_AND_LEFT 0x07
#define DIR_UP_AND_RIGHT 0x08

#define STAIRS_LEFT_ASCENDING 0xB0
#define STAIRS_RIGHT_ASCENDING 0xB1
#define STAIRS_LEFT_ASCENDING_WALL 0xB2
#define STAIRS_RIGHT_ASCENDING_WALL 0xB3


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

void FuturePlayerTile(u8 dir, struct MapPosition* playerPos)
{
    playerPos->x = gEventObjects[gPlayerAvatar.spriteId].currentCoords.x;
    playerPos->y = gEventObjects[gPlayerAvatar.spriteId].currentCoords.y;
    MoveCoords(dir, &playerPos->x, &playerPos->y);
}

void PlayerWalkDirection(u8 dir)
{
    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = GetWalkNormalMovementAction(dir);
    dprintf("default movement %d\n", movement);
    if (dir >= 3 && dir <= 4) {
        struct MapPosition playerPos;
        GetPlayerPosition(&playerPos);
        u8 fdir = gEventObjects[gPlayerAvatar.spriteId].facingDirection & 0x7;
        if (fdir != dir) {
            dprintf("The direction facing and direction moving don't match. %d %d\n", dir, fdir);
            FuturePlayerTile(dir, &playerPos);
        } else {
            GetInFrontOfPlayerPosition(&playerPos);
        }

        u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
        // if staircase is left acending
        // you should climb if the next stair is B0 going left
        if (((behaviourFront == STAIRS_LEFT_ASCENDING) || (behaviourFront == STAIRS_LEFT_ASCENDING_WALL)) &&
            (dir == DIR_LEFT || dir == DIR_NORTHWEST)) {
            dprintf("front %x, current %x\n", behaviourFront, behaviour);
            if (behaviourFront == STAIRS_LEFT_ASCENDING_WALL && (behaviour != STAIRS_LEFT_ASCENDING_WALL || behaviour != STAIRS_LEFT_ASCENDING)) {
                movement = movement;
                PlayerNotOnBikeCollide(dir);
                return;
            }
            else
                movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 0);
        // going left the top stair should not ascend
        } else if (((behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_LEFT_ASCENDING_WALL) &&
         (behaviourFront != STAIRS_LEFT_ASCENDING && behaviourFront != STAIRS_LEFT_ASCENDING_WALL)) &&
         (dir == DIR_LEFT || dir == DIR_NORTHWEST)) {
            movement = GetWalkNormalMovementAction(dir);
        // if staircase is right ascending
        // you should climb if the next stair is B1 going right
        } else if (behaviourFront == STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 0);
        // going right the top stair should not ascend
        } else if (behaviour == STAIRS_RIGHT_ASCENDING && behaviourFront != STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetWalkNormalMovementAction(dir);
        } else if (behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_RIGHT_ASCENDING || behaviour == STAIRS_LEFT_ASCENDING_WALL) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviour, 0);
        }
    }
    dprintf("final movement %d\n", movement);
    PlayerSetAnimId(movement, 2);
}


void PlayerRunDirection(u8 dir)
{
    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = GetPlayerRunMovementAction(dir);
    if (dir >= 3 && dir <= 4) {
        struct MapPosition playerPos;
        GetPlayerPosition(&playerPos);
        GetInFrontOfPlayerPosition(&playerPos);
        u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
        // if staircase is left acending
        // you should climb if the next stair is B0 going left
        if (behaviourFront == STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 1);
        // going left the top stair should not ascend
        } else if (behaviour == STAIRS_LEFT_ASCENDING && behaviourFront != STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            movement = GetPlayerRunMovementAction(dir);
        // if staircase is right ascending
        // you should climb if the next stair is B1 going right
        } else if (behaviourFront == STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 1);
            // going right the top stair should not ascend
        } else if (behaviour == STAIRS_RIGHT_ASCENDING && behaviourFront != STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetPlayerRunMovementAction(dir);
        } else if (behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_RIGHT_ASCENDING) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviour, 1);
        }
    }
    PlayerSetAnimId(movement, 2);
}


void PlayerBikeDirection(u8 dir)
{

    struct EventObject* playerObject = &gEventObjects[gPlayerAvatar.spriteId];
    u32 behaviour = MapGridGetMetatileBehaviorAt(playerObject->currentCoords.x, playerObject->currentCoords.y);
    u8 movement = GetPlayerBikeMovementAction(dir);
    if (dir >= 3 && dir <= 4) {
        struct MapPosition playerPos;
        GetPlayerPosition(&playerPos);
        GetInFrontOfPlayerPosition(&playerPos);
        u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
        // if staircase is left acending
        // you should climb if the next stair is B0 going left
        if (behaviourFront == STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 2);
        // going left the top stair should not ascend
        } else if (behaviour == STAIRS_LEFT_ASCENDING && behaviourFront != STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            movement = GetPlayerBikeMovementAction(dir);
        // if staircase is right ascending
        // you should climb if the next stair is B1 going right
        } else if (behaviourFront == STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviourFront, 2);
            // going right the top stair should not ascend
        } else if (behaviour == STAIRS_RIGHT_ASCENDING && behaviourFront != STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            movement = GetPlayerBikeMovementAction(dir);
        } else if (behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_RIGHT_ASCENDING) {
            movement = GetPlayerSidewaysstairsAction(dir, behaviour, 2);
        }
    }
    PlayerSetAnimId(movement, 2);
}


u8 GetPlayerSidewaysstairsAction(u8 dir, u8 behaviour, u8 type)
{
    u8 direction = dir > 4 ? 0 : dir;
    switch(type) {
        case 0:
            //walk table
            if (behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_LEFT_ASCENDING_WALL) {
                // left ascending stair
                if (direction == DIR_LEFT) {
                    // move diagonally left up
                    return 0xB6;
                } else {
                    // move diagonally right up
                    return 0xB7;
                }
            } else {
                if (direction == DIR_LEFT) {
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
            if (behaviour == STAIRS_LEFT_ASCENDING) {
                // left ascending stair
                if (direction == DIR_LEFT) {
                    // move diagonally left up
                    return 0xBA;
                } else {
                    // move diagonally right up
                    return 0xBB;
                }
            } else {
                if (direction == DIR_LEFT) {
                    // move diagonally left down
                    return 0xBC;
                } else {
                    // move diagonally right down
                    return 0xBD;
                }
            }
            //return run_table[behaviour - STAIRS_LEFT_ASCENDING][direction];
            break;
        case 2:
            // bike table
            if (behaviour == STAIRS_LEFT_ASCENDING) {
                // left ascending stair
                if (direction == DIR_LEFT) {
                    // move diagonally left up
                    return 0xBE;
                } else {
                    // move diagonally right up
                    return 0xBF;
                }
            } else {
                if (direction == DIR_LEFT) {
                    // move diagonally left down
                    return 0xC0;
                } else {
                    // move diagonally right down
                    return 0xC1;
                }
            }
            //return bike_table[behaviour - STAIRS_LEFT_ASCENDING][direction];
            break;
    };
    return 0;
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
    struct EventObject *playerEventObj = &gEventObjects[gPlayerAvatar.eventObjectId];
    struct MapPosition playerPos;
    GetPlayerPosition(&playerPos);
    s16 x = playerPos.x;
    s16 y = playerPos.y;
    GetInFrontOfPlayerPosition(&playerPos);
    u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
    u8 behaviour = MapGridGetMetatileBehaviorAt(x, y);
    // if staircase is left acending
    // you should climb if the next stair is B0 going left
    if (behaviourFront == STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
        dir = DIR_NORTHWEST;
        // going left the top stair should not ascend
    } else if (behaviour == STAIRS_LEFT_ASCENDING && behaviourFront != STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
        dir = dir;
        // if staircase is right ascending
        // you should climb if the next stair is B1 going right
    } else if (behaviour == STAIRS_LEFT_ASCENDING && dir == DIR_RIGHT) {
        dir = DIR_SOUTHEAST;
    } else if (behaviourFront == STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
        dir = DIR_NORTHEAST;
        // going right the top stair should not ascend
    } else if (behaviour == STAIRS_RIGHT_ASCENDING && behaviourFront != STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
        dir = dir;
    } else if (behaviour == STAIRS_RIGHT_ASCENDING && dir == DIR_LEFT) {
        dir = DIR_SOUTHWEST;
    }
    MoveCoords(dir, &x, &y);
    return Bike_CheckCollisionTryAdvanceCollisionCount(playerEventObj, x, y, dir, MapGridGetMetatileBehaviorAt(x, y));
}

u8 CheckForPlayerAvatarCollision(u8 direction)
{
    u8 dir = direction;
    struct EventObject *playerEventObj = &gEventObjects[gPlayerAvatar.eventObjectId];
    struct MapPosition playerPos;
    GetPlayerPosition(&playerPos);
    s16 x = playerPos.x;
    s16 y = playerPos.y;
    GetInFrontOfPlayerPosition(&playerPos);
    u8 behaviourFront = MapGridGetMetatileBehaviorAt(playerPos.x, playerPos.y);
    u8 behaviour = MapGridGetMetatileBehaviorAt(x, y);

    if (IsStaircase(behaviour, dir)) {
        return 8; // ?
    } else {
        // if staircase is left acending
        // you should climb if the next stair is B0 going left
        if (behaviourFront == STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            dir = DIR_NORTHWEST;
            // going left the top stair should not ascend
        } else if (behaviour == STAIRS_LEFT_ASCENDING && behaviourFront != STAIRS_LEFT_ASCENDING && dir == DIR_LEFT) {
            dir = dir;
            // going right on a left acending stair case, you should decend
        } else if ((behaviour == STAIRS_LEFT_ASCENDING || behaviour == STAIRS_LEFT_ASCENDING_WALL) && dir == DIR_RIGHT) {
            dir = DIR_SOUTHEAST;
            dprintf("here %d\n", DIR_SOUTHEAST);
        } else if (behaviourFront == STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            dir = DIR_NORTHEAST;
            // going right the top stair should not ascend
        } else if (behaviour == STAIRS_RIGHT_ASCENDING && behaviourFront != STAIRS_RIGHT_ASCENDING && dir == DIR_RIGHT) {
            dir = dir;
        } else if (behaviour == STAIRS_RIGHT_ASCENDING && dir == DIR_LEFT) {
            dir = DIR_SOUTHWEST;
        }
        MoveCoords(dir, &x, &y);
        return CheckForEventObjectCollision(playerEventObj, x, y, dir, MapGridGetMetatileBehaviorAt(x, y));
    }
}
