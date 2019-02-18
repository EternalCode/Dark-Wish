#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"

#define id t->priv[0]
#define xOff t->priv[1]
#define yOff t->priv[2]
#define speed t->priv[3]
#define thread t->priv[4]
#define originalX t->priv[5]
#define originalY t->priv[6]
void TaskMoveSprite(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* spr = &gSprites[id];
    s16 finalX = (originalX + xOff);
    s16 finalY = (originalY + yOff);
    // check if movement is done
    if ((spr->pos1.x == finalX) && (spr->pos1.y == finalY)) {
        // undo wait command, if it's on
        gAnimationCore->wait[thread] = false;
        DestroyTask(taskId);
        return;
    }
    // Modify X position if it needs modification
    s16 deltaX = (xOff < 0) ? MIN(Div(xOff, speed), -1) : MAX(Div(xOff, speed), 1);
    if (xOff < 0) {
        if (spr->pos1.x > finalX) {
            // x position needs to be modified for sprite going left
            if ((spr->pos1.x + deltaX) < finalX) {
                spr->pos1.x = finalX;
            } else {
                spr->pos1.x += deltaX;
            }
        }
    } else {
        if (spr->pos1.x < finalX) {
            // x position needs to be modified for sprite going right
            if ((spr->pos1.x + deltaX) > finalX) {
                spr->pos1.x = finalX;
            } else {
                spr->pos1.x += deltaX;
            }
        }
    }
    // Modify Y position if it needs modification
    s16 deltaY = (yOff < 0) ? MIN(Div(yOff, speed), -1) : MAX(Div(yOff, speed), 1);
    if (yOff < 0) {
        if (spr->pos1.y > finalY) {
            // y position needs to be modified for sprite going up
            if ((spr->pos1.y + deltaY) < finalY) {
                spr->pos1.y = finalY;
            } else {
                spr->pos1.y += deltaY;
            }
        }
    } else {
        if (spr->pos1.y < finalY) {
            // y position needs to be modified for sprite going down
            if ((spr->pos1.y + deltaY) > finalY) {
                spr->pos1.y = finalY;
            } else {
                spr->pos1.y += deltaY;
            }
        }
    }
}
#undef id
#undef xOff
#undef yOff
#undef speed
#undef thread
#undef originalX
#undef originalY

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
