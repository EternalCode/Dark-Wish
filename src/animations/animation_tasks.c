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
