#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"

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
    if (t->priv[0] < t->priv[2]) {
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
#undef wait
#undef state
#undef counter
#undef timesFlashed
