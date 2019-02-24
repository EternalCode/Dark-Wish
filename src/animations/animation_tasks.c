#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"
#include "../battle/battle_actions/actions.h"
#include "../battle/battle_data/battle_state.h"
#include "../battle/battle_data/pkmn_bank_stats.h"

#define id t->priv[0]
#define deltaX t->priv[1]
#define deltaY t->priv[2]
#define framesCount t->priv[3]
#define thread t->priv[4]
#define framesPast t->priv[5]
void TaskMoveSprite(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* spr = &gSprites[id];

    if (framesPast < framesCount) {
        spr->pos1.x += deltaX;
        spr->pos1.y += deltaY;
        framesPast++;
    } else {
        gAnimationCore->wait[thread] = false;
        DestroyTask(taskId);
    }
}
#undef id
#undef deltaX
#undef deltaY
#undef framesCount
#undef thread
#undef framesPast

// wait X frames before deleting task and undoing wait state
void TaskWaitFrames(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    if (t->priv[0] > t->priv[2]) {
        t->priv[2]++;
    } else {
        gAnimationCore->wait[t->priv[1]] = false;
        DestroyTask(taskId);
    }
}

// Undo thread waiting after palfade has finished
void TaskWaitFade(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    if (!gPaletteFade.active) {
        gAnimationCore->wait[t->priv[0]] = false;
        DestroyTask(taskId);
    }
}

// wait for a specified task to finish
void TaskWaitForTask(u16 taskId)
{
    struct Task* t = &tasks[taskId];
    u32* func = (u32*)&t->priv[0];
    if (task_is_running((TaskCallback)*func))
        return;
    if (task_is_running((TaskCallback)(*func - 1)))
        return;
    gAnimationCore->wait[t->priv[3]] = false;
    DestroyTask(taskId);
}

#define spriteId t->priv[0]
#define flashDuration t->priv[1]
#define timesToFlash t->priv[2]
#define thread (t->priv[3])
#define towait (t->priv[4])
#define color (t->priv[5])
#define state t->priv[7]
#define counter t->priv[8]
#define timesFlashed t->priv[9]

void TaskFlashSprite(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    u16 palSlot = (gSprites[spriteId].final_oam.palette_num) * 16;
    switch (state) {
        case 0:
            state = 1;
            counter = 0;
            break;
        case 1:
            counter++;
            if (counter <= flashDuration) {
                memset(&gPlttBufferObjFaded[palSlot], color, 32);
            } else {
                counter = 0;
                state = 2;
            }
            break;
        case 2:
            counter++;
            if (counter <= flashDuration) {
                memcpy(&gPlttBufferObjFaded[palSlot], &gPlttBufferObjUnFaded[palSlot], 32);
            } else {
                counter = 0;
                state = 3;
                timesFlashed++;
            }
            break;
        case 3:
            if (timesToFlash > timesFlashed) {
                state = 1;
                counter = 0;
            } else {
                if (towait == true) {
                    gAnimationCore->wait[thread] = false;
                }
                DestroyTask(taskId);
            }
            break;
    };
}

#undef spriteId
#undef flashDuration
#undef timesToFlash
#undef thread
#undef towait
#undef state
#undef counter
#undef timesFlashed

#define bgid t->priv[0]
#define spriteId t->priv[0]
#define xquake t->priv[1]
#define yquake t->priv[2]
#define times t->priv[3]
#define speed t->priv[4]
#define dirX t->priv[5]
#define dirY t->priv[6]
#define quakeCount t->priv[9]
#define towait t->priv[10]
#define thread t->priv[11]
#define waitcounter t->priv[12]
#define dirRight 0
#define dirUp 1
void TaskQuakeBg(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    // check anim finished
    if ((quakeCount >> 2) == times) {
        DestroyTask(taskId);
        if (towait) {
            gAnimationCore->wait[thread] = false;
        }
        return;
    }
    // wait for delay
    if (waitcounter < speed) {
        waitcounter++;
        return;
    }
    waitcounter = 0;
    // quake X

    if (dirX == dirRight) {
        ChangeBgX(bgid, xquake << 8, 1);
        dirX = !dirRight;
        quakeCount++;
    } else {
        ChangeBgX(bgid, xquake << 8, 2);
        dirX = dirRight;
        quakeCount++;
    }
    // quake Y
    if (dirY == dirUp) {
        ChangeBgY(bgid, yquake << 8, 1);
        dirY = !dirUp;
        quakeCount++;
    } else {
        ChangeBgY(bgid, yquake << 8, 2);
        dirY = dirUp;
        quakeCount++;
    }
}

void TaskQuakeSprite(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    // check anim finished
    if ((quakeCount >> 2) == times) {
        DestroyTask(taskId);
        if (towait) {
            gAnimationCore->wait[thread] = false;
        }
        return;
    }
    // wait for delay
    if (waitcounter < speed) {
        waitcounter++;
        return;
    }
    waitcounter = 0;
    // quake X

    if (dirX == dirRight) {
        gSprites[spriteId].pos1.x += xquake;
        dirX = !dirRight;
        quakeCount++;
    } else {
        gSprites[spriteId].pos1.x -= xquake;
        dirX = dirRight;
        quakeCount++;
    }
    // quake Y
    if (dirY == dirUp) {
        gSprites[spriteId].pos1.y -= yquake;
        dirY = !dirUp;
        quakeCount++;
    } else {
        gSprites[spriteId].pos1.y -= yquake;
        dirY = dirUp;
        quakeCount++;
    }
}
#undef bgid
#undef spriteId
#undef xquake
#undef yquake
#undef times
#undef speed
#undef dirX
#undef dirY
#undef quakeCount
#undef towait
#undef thread
#undef waitcounter
#undef dirRight
#undef dirUp

void TaskHPBoxBobFast(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    if (t->priv[3] == 20) {
        DestroyTask(taskId);
        return;
    }

    // calculate bank and delta
    u8 bank = t->priv[0];
    s8 amount = (t->priv[1]) ? -2 : 2;
    t->priv[3]++;
    // apply delta
    gSprites[gPkmnBank[bank]->objid_hpbox[0]].pos1.y += amount;
    gSprites[gPkmnBank[bank]->objid_hpbox[1]].pos1.y += amount;
    gSprites[gPkmnBank[bank]->objid_hpbox[2]].pos1.y += amount;
    gSprites[gPkmnBank[bank]->objid_hpbox[3]].pos1.y += amount;
    // adjust direction of delta next time
    t->priv[1] = !(t->priv[1]);
}

#define state t->priv[0]
#define spriteId t->priv[1]
void TaskBurnEffect(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    s16 randFactor = 0;
    switch (state) {
        case 0:
            // pick sprite's position
            randFactor = (rand() % 2) ? -(rand_range(0, 20)) : rand_range(0, 20);
            gSprites[spriteId].pos1.x = VarGet(0x8006) + randFactor;
            gSprites[spriteId].pos1.y = VarGet(0x8007) + 16;
            gSprites[spriteId].invisible = false;
            t->priv[5] = gSprites[spriteId].pos1.y;
            state++;
            break;
        case 1:
            // move the sprite up
            gSprites[spriteId].pos1.y -=2;
            if (gSprites[spriteId].pos1.y + 30 < t->priv[5]) {
                state++;
            }
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

void TaskFreezeEffect(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    s16 randFactorX, randFactorY = 0;
    switch (state) {
        case 0:
            // pick sprite's position
            randFactorX = (rand() % 2) ? -(rand_range(0, 20)) : rand_range(0, 20);
            randFactorY = (rand() % 2) ? -(rand_range(0, 20)) : rand_range(5, 10);
            gSprites[spriteId].pos1.x = VarGet(0x8006) + randFactorX;
            gSprites[spriteId].pos1.y = VarGet(0x8007) + randFactorY;
            gSprites[spriteId].invisible = false;
            t->priv[5] = 0;
            state++;
            break;
        case 1:
            // move the sprite up
            if (gSprites[spriteId].affineAnimEnded) {
                state++;
            }
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

#define amplitude t->priv[2]
#define frequency t->priv[3]
void TaskMovePoisonBubble(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    s16 randFactor = 0;
    switch (state) {
        case 0:
            // pick sprite's position
            randFactor = (rand() % 2) ? -(rand_range(0, 20)) : rand_range(0, 20);
            gSprites[spriteId].pos1.x = VarGet(0x8006) + randFactor;
            gSprites[spriteId].pos1.y = VarGet(0x8007) + 16;
            gSprites[spriteId].invisible = false;
            t->priv[5] = gSprites[spriteId].pos1.y;
            t->priv[6] = 0;
            state++;
            break;
        case 1:
            // move the sprite up
            gSprites[spriteId].pos1.y -=2;
            if (gSprites[spriteId].pos1.y + t->priv[4] < t->priv[5]) {
                state++;
            }
            // move X influenced by sin wave
            gSprites[spriteId].pos1.x += Sin(t->priv[6], amplitude);
            // update wave frequency
            t->priv[6] = (t->priv[6] + frequency) & 0xFF;
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

void TaskMoveSleepZ(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    switch (state) {
        case 0:
            // pick sprite's position
            gSprites[spriteId].pos1.x = VarGet(0x8006);
            gSprites[spriteId].pos1.y = VarGet(0x8007);
            gSprites[spriteId].invisible = false;
            t->priv[5] = gSprites[spriteId].pos1.y;
            t->priv[6] = 0;
            state++;
            break;
        case 1:
            // delay
            if (t->priv[7] < 1) {
                t->priv[7]++;
                return;
            }
            t->priv[7] = 0;
            // move the sprite up
            gSprites[spriteId].pos1.y -=1;
            if (gSprites[spriteId].pos1.y + t->priv[4] < t->priv[5]) {
                state++;
            }
            // move X influenced by sin wave
            gSprites[spriteId].pos1.x += Sin(t->priv[6], amplitude);
            // update wave frequency
            t->priv[6] = (t->priv[6] + frequency) & 0xFF;
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

#define delay t->priv[2]
void TaskMoveSinLeftAndRight(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    u32 dist = 0;
    switch (state) {
        case 0:
            // pick sprite's position
            for (u8 i = 0; i < 180; i+= (180 / frequency))
                dist += Sin2(t->priv[5]);
            dist = dist >> 1;
            gSprites[spriteId].pos1.x = VarGet(0x8006) - dist;
            gSprites[spriteId].pos1.y = VarGet(0x8007);
            gSprites[spriteId].invisible = false;
            state++;
            break;
        case 1:
            // check if done
            if (t->priv[4] < t->priv[6]) {
                state++;
                return;
            }
            // check if delay
            if (delay > t->priv[7]) {
                t->priv[7]++;
                return;
            }
            t->priv[7] = 0;
            // move X influenced by sin wave
            gSprites[spriteId].pos1.x += (Sin2(t->priv[5]) / 256);
            // update wave frequency
            t->priv[5] = (t->priv[5] + frequency);
            if (t->priv[5] > 360) {
                t->priv[6]++;
                t->priv[5] = frequency;
            }
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}
#undef state
#undef spriteId
#undef amplitude
#undef frequency
#undef delay


#define spriteId t->priv[1] // var arg
#define arg1bits t->priv[2] // arg 1byte gravity
#define currentx t->priv[3] // arg 2
#define currenty t->priv[4] // arg 3
#define vX t->priv[5]
#define vY t->priv[6]
#define ystart t->priv[7]
#define accX t->priv[8]
#define accY t->priv[9]
#define state t->priv[10]
#define delay t->priv[11]
#define delaytimer t->priv[12]
extern const struct CompressedSpriteSheet glowballSprite;
extern const struct SpritePalette glowballPalette;
extern const struct OamData glowballOam;
extern const struct RotscaleFrame glowballAffineTable[];
extern const u32 glowballAffinePtr;
extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];
void TaskCreateSmallFireworkImpact(u8 taskId)
{
    struct Task* t = &tasks[taskId];

    switch (state) {
        case 0:
        {
            u8 blend = arg1bits & 1;
            u8 left = arg1bits & 2;
            currentx = VarGet(currentx);
            currentx += left ? rand_range(0, 10) - 10 : rand_range(0, 10);
            currenty = VarGet(currenty);
            currenty += rand_range(0, 20) - 10;
            ystart = currenty;

            struct CompressedSpriteSheet* gfx = (struct CompressedSpriteSheet*)&glowballSprite;
            struct SpritePalette* pal = (struct SpritePalette*)&glowballPalette;
            struct OamData* oam = (struct OamData*)&glowballOam;
            struct Template spriteTemp = {gfx->tag, pal->tag, oam, nullframe, gfx, nullrsf, (SpriteCallback)oac_nullsub};
            spriteId = template_instanciate_forward_search(&spriteTemp, currentx, currenty, 0);
            struct RotscaleFrame (**rotscale_table)[] = (void*)&glowballAffinePtr;
            gSprites[spriteId].rotscale_table = rotscale_table;
            gSprites[spriteId].final_oam.affine_mode = 1;
            gSprites[spriteId].final_oam.priority = 3;
            if (!blend) {
                gSprites[spriteId].final_oam.obj_mode = 1;
                gSprites[spriteId].final_oam.priority = 1;
            }

            // acceleration. Y must be always negative
            accX = 1;
            accY = 2;
            // initial velocities
            vX = left ? -rand_range(1, 3) : rand_range(1, 3);
            vY = -(rand_range(1, 4));
            state++;
            break;
        }
        case 1:
            // if affine transformation done end
            if (gSprites[spriteId].affineAnimEnded) {
                state++;
                return;
            }
            // update vectors
            vX += (accX / 32);
            vY += (accY / 32);
            currentx += vX;
            currenty += vY;
            gSprites[spriteId].pos1.x = currentx;
            gSprites[spriteId].pos1.y = currenty;
            accX += 1;
            accY = MAX(accY + 2, 10);
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };

}
