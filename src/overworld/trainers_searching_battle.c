#include <pokeagb/pokeagb.h>
#include "../global.h"

// Baseline script
/*
lock
applymovement 0xMapID @movements
waitmovement 0x0
goto @trainer_script

#org @movements
-dynamic movements-
*/
#define sMOVE_DOWN 0x10
#define sMOVE_UP 0x11
#define sMOVE_LEFT 0x12
#define sMOVE_RIGHT 0x13
#define sMOVE_EXCLAIMATION 0x62
#define sEND_MOVEMENTS 0xFE

u8 sTrainerMoveToPlayer[] = {
    0x00, // 0 nop
    0x4F, // 1 applymovement
    0x11, // 2 NPC ID
    0x00, // 3 nop
    0x00, // 4 movements ptr
    0x00, // 5
    0x00, // 6
    0x00, // 7
    0x51, // 8 waitmovement
    0x00, // 9 who to wait on
    0x00, // 10 nop
    0x05, // 11 goto
    0x00, // 12 trainer's script pointer
    0x00, // 13
    0x00, // 14
    0x00, // 15
};

#define COLLISIONMASK (~1)
bool CheckPathwayValid(struct EventObject* trainerObj, u8 dir, u8 dist, u8* movements)
{
    u8 i = 0;
    s16 x = trainerObj->currentCoords.x;
    s16 y = trainerObj->currentCoords.y;
    switch(dir){
        case DIR_SOUTH:
            for (i = 1; i < dist; i++) {
                // check tile valid
                if (GetCollisionAtCoords(trainerObj, x, y + i, dir) & COLLISIONMASK)
                    return false;
                movements[i] = sMOVE_DOWN;
            }
            break;
        case DIR_NORTH:
            for (i = 1; i < dist; i++) {
                // check tile valid
                if (GetCollisionAtCoords(trainerObj, x, y - i, dir) & COLLISIONMASK)
                    return false;
                movements[i] = sMOVE_UP;
            }
            break;
        case DIR_EAST:
            for (i = 1; i < dist; i++) {
                // check tile valid
                if (GetCollisionAtCoords(trainerObj, x + i, y, dir) & COLLISIONMASK)
                    return false;
                movements[i] = sMOVE_RIGHT;
            }
            break;
        case DIR_WEST:
            for (i = 1; i < dist; i++) {
                // check tile valid
                if (GetCollisionAtCoords(trainerObj, x - i, y, dir) & COLLISIONMASK)
                    return false;
                movements[i] = sMOVE_LEFT;
            }
            break;
        default:
            return false;
    };
    movements[dist] = sEND_MOVEMENTS;
    return true;
}



bool CheckTrainerBattle(struct MapPosition* playerPos)
{
    for (u8 i = 0; i < NPC_STATE_ID_MAX; i++) {
        u16 dist = 0;
        struct EventObject *npc = &gEventObjects[i];
        if (!npc->active)
            continue;
        if (npc->trainerType != 1 && npc->trainerType != 3)
            continue;
        if (npc->elevation != gEventObjects[gPlayerAvatar.eventObjectId].elevation)
            continue;

        // check if the trainer is defeated
        u16* trainerScrPtr = (u16*)GetEventObjectScriptPointerByEventObjectId(i);
        if (FlagGet(trainerScrPtr[1] + 0x500))
            continue;

        u8 trainerDir = EVENTOBJ_DIR(npc);
        // undefeated trainer, check path to player & get distance
        if (playerPos->x == npc->currentCoords.x) {
            // check direction NPC is facing is up or down
            if (trainerDir != DIR_SOUTH && trainerDir != DIR_NORTH) {
                // valid trainer in vertical direction, but not looking up or down
                continue;
            } else if (trainerDir == DIR_SOUTH && playerPos->y < npc->currentCoords.y) {
                // valid trainer, but looking down and player is above
                continue;
            } else if (trainerDir == DIR_NORTH && playerPos->y > npc->currentCoords.y) {
                // valid trainer, but looking up and player is below
                continue;
            } else if (trainerDir == DIR_SOUTH) {
                // NPC needs to walk down to meet the player
                dist = playerPos->y - npc->currentCoords.y;
            } else {
                // NPC needs to walk up to meet the player
                dist = npc->currentCoords.y - playerPos->y;
            }
        } else if (playerPos->y == npc->currentCoords.y) {
            // horizontal delta only
            u8 trainerDir = EVENTOBJ_DIR(npc);
            if (trainerDir != DIR_EAST && trainerDir != DIR_WEST) {
                //valid trainer in hdir, but not looking left or right
                continue;
            } else if (trainerDir == DIR_EAST && playerPos->x < npc->currentCoords.x) {
                // valid trainer in hdir, but looking right and player is on the left
                continue;
            } else if (trainerDir == DIR_WEST && playerPos->x > npc->currentCoords.x) {
                // valid trainer in hdir, but looking left and player is on the right
                continue;
            } else if (trainerDir == DIR_EAST) {
                // needs to move right to see player
                dist = playerPos->x - npc->currentCoords.x;
            } else {
                // needs to move left to meet player
                dist = npc->currentCoords.x - playerPos->x;
            }
        } else {
            // player and trainer NPC aren't in line of sight
            continue;
        }

        // check if the trainer's view distance is less than the travel distance required
        if (npc->sight_distance < dist - 1) {
            return false;
        } else {
            u8 movements[dist + 1];
            movements[0] = sMOVE_EXCLAIMATION;
            if (CheckPathwayValid(npc, trainerDir, dist, movements)) {
                // copy the base script
                u16 scriptOffset = 0;
                memset(string_buffer, 0xFF, STRING_BUFFER_SIZE);
                VarSet(0x8001, trainerDir - 1);
                memcpy(&string_buffer[scriptOffset], sTrainerMoveToPlayer, sizeof(sTrainerMoveToPlayer));
                scriptOffset += sizeof(sTrainerMoveToPlayer);
                // modify base script NPC id
                string_buffer[2] = npc->localId;
                // modify the movements pointer
                memcpy(&(string_buffer[scriptOffset]), movements, sizeof(movements));
                u32 *movementsPointer = (u32*)&(string_buffer[4]);
                *movementsPointer = (u32)&(string_buffer[scriptOffset]);
                scriptOffset += sizeof(movements);
                // modify the goto pointer
                u32* t = (u32*)&(string_buffer[12]);
                *t = (u32)trainerScrPtr;
                extern void* scrPlayerFaceTrainer;
                ScriptContext1_SetupScript(&scrPlayerFaceTrainer);
                return true;
            }
        }

    }
    return false;
}
