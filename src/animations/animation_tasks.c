#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"
#include "../battle/battle_actions/actions.h"
#include "../battle/battle_data/battle_state.h"
#include "../battle/battle_data/pkmn_bank_stats.h"

#define gtargetx 0x8000
#define gtargety 0x8001



void TaskWaitAnimMessage(u8 taskId)
{
    if (!dialogid_was_acknowledged(0x1))
        DestroyTask(taskId);
}

#define id t->priv[0]
#define deltaX t->priv[1]
#define deltaY t->priv[2]
#define framesCount t->priv[3]
#define animwait t->priv[4]
#define thread t->priv[5]
#define framesPast t->priv[6]
#define direction t->priv[7]
#define xerror t->priv[8]
#define totalFramesPast t->priv[9]
#define yerror t->priv[10]

void TaskMoveSprite(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* spr = &gSprites[id];

    if (framesPast < framesCount) {
        spr->pos1.x += deltaX;
        spr->pos1.y += deltaY;
        framesPast++;
    } else {
        if (animwait)
            gAnimationCore->wait[thread] = false;
        DestroyTask(taskId);
    }
}

void TaskMoveBG(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    if (framesPast < framesCount) {
        ChangeBgX(id, deltaX << 8, direction); // 2
        ChangeBgY(id, deltaY << 8, direction);
        framesPast++;
    } else {
        if (animwait)
            gAnimationCore->wait[thread] = false;
        DestroyTask(taskId);
    }
}


#undef id
#undef deltaX
#undef deltaY
#undef framesCount
#undef animwait
#undef thread
#undef framesPast
#undef xerror
#undef yerror
#undef totalFramesPast


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
void TaskWaitForTask(u8 taskId)
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

void TaskWaitAnimation(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* sprite = &gSprites[t->priv[0]];
    if (sprite->animEnded) {
        gAnimationCore->wait[t->priv[1]] = false;
        DestroyTask(taskId);
    }
}

void TaskWaitAffineAnimation(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* sprite = &gSprites[t->priv[0]];
    if (sprite->affineAnimEnded) {
        gAnimationCore->wait[t->priv[1]] = false;
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
#undef towait
#undef state
#undef counter
#undef timesFlashed
#undef color

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
        gSprites[spriteId].pos1.y += yquake;
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
            gSprites[spriteId].pos1.x = VarGet(gtargetx) + randFactor;
            gSprites[spriteId].pos1.y = VarGet(gtargety) + 16;
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
            gSprites[spriteId].pos1.x = VarGet(gtargetx) + randFactorX;
            gSprites[spriteId].pos1.y = VarGet(gtargety) + randFactorY;
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
            gSprites[spriteId].pos1.x = VarGet(gtargetx) + randFactor;
            gSprites[spriteId].pos1.y = VarGet(gtargety) + 16;
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
            gSprites[spriteId].pos1.x = VarGet(gtargetx);
            gSprites[spriteId].pos1.y = VarGet(gtargety);
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
            gSprites[spriteId].pos1.x = VarGet(gtargetx) - dist;
            gSprites[spriteId].pos1.y = VarGet(gtargety);
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
#define gfxpriv t->priv[13]
#define palpriv t->priv[14]
#define oampriv t->priv[15]
extern const struct CompressedSpriteSheet glowballSprite;
extern const struct SpritePalette glowballPalette;
extern const struct OamData glowballOam;
extern const u32 glowballSmallerAffinePtr;
extern const u32 glowballAffinePtr;
extern const u32 glowballRevAffinePtr;
extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];
void TaskCreateSmallFireworkGeneric(u8 taskId)
{
    struct Task* t = &tasks[taskId];

    switch (state) {
        case 0:
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
        case 1:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

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
            u16 color = t->priv[1];
            spriteId = template_instanciate_forward_search(&spriteTemp, currentx, currenty, 0);
            u8 pal_slot = gSprites[spriteId].final_oam.palette_num;
            BlendPalette((pal_slot * 16) + (16 * 16), 16, 12, color);
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

void TaskCreateSmallerFireworkImpact(u8 taskId)
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
            u16 color = t->priv[1];
            spriteId = template_instanciate_forward_search(&spriteTemp, currentx, currenty, 0);
            u8 pal_slot = gSprites[spriteId].final_oam.palette_num;
            BlendPalette((pal_slot * 16) + (16 * 16), 16, 12, color);
            struct RotscaleFrame (**rotscale_table)[] = (void*)&glowballSmallerAffinePtr;
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

void TaskCreateSmallLinearFireworkImpact(u8 taskId)
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
            u16 color = t->priv[1];
            spriteId = template_instanciate_forward_search(&spriteTemp, currentx, currenty, 0);
            u8 pal_slot = gSprites[spriteId].final_oam.palette_num;
            BlendPalette((pal_slot * 16) + (16 * 16), 16, 12, color);
            struct RotscaleFrame (**rotscale_table)[] = (void*)&glowballAffinePtr;
            gSprites[spriteId].rotscale_table = rotscale_table;
            gSprites[spriteId].final_oam.affine_mode = 1;
            gSprites[spriteId].final_oam.priority = 3;
            if (!blend) {
                gSprites[spriteId].final_oam.obj_mode = 1;
                gSprites[spriteId].final_oam.priority = 1;
            }

            // initial velocities
            vX = left ? -rand_range(1, 3) : rand_range(1, 3);
            vY = rand() % 2 ? -rand_range(1, 4) : rand_range(1, 4);
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
            currentx += vX;
            currenty += vY;
            gSprites[spriteId].pos1.x = currentx;
            gSprites[spriteId].pos1.y = currenty;
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}

void TaskCreateSmallLinearFireworkImpactRev(u8 taskId)
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
            u16 color = t->priv[1];
            spriteId = template_instanciate_forward_search(&spriteTemp, currentx, currenty, 0);
            u8 pal_slot = gSprites[spriteId].final_oam.palette_num;
            BlendPalette((pal_slot * 16) + (16 * 16), 16, 12, color);
            struct RotscaleFrame (**rotscale_table)[] = (void*)&glowballRevAffinePtr;
            gSprites[spriteId].rotscale_table = rotscale_table;
            gSprites[spriteId].final_oam.affine_mode = 1;
            gSprites[spriteId].final_oam.priority = 3;
            if (!blend) {
                gSprites[spriteId].final_oam.obj_mode = 1;
                gSprites[spriteId].final_oam.priority = 1;
            }

            // initial velocities
            vX = left ? -rand_range(1, 3) : rand_range(1, 3);
            vY = rand() % 2 ? -rand_range(1, 4) : rand_range(1, 4);
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
            currentx += vX;
            currenty += vY;
            gSprites[spriteId].pos1.x = currentx;
            gSprites[spriteId].pos1.y = currenty;
            break;
        case 2:
            // delete sprite
            FreeSpriteOamMatrix(&gSprites[spriteId]);
            DestroySprite(&gSprites[spriteId]);
            DestroyTask(taskId);
            break;
    };
}
#undef spriteId
#undef arg1bits
#undef currentx
#undef currenty
#undef vX
#undef vY
#undef ystart
#undef accX
#undef accY
#undef state
#undef delay
#undef delaytimer


#define startX sprite->data[1]
#define deltaX sprite->data[1]
#define dstX sprite->data[2]
#define startY sprite->data[3]
#define deltaY sprite->data[3]
#define dstY sprite->data[4]
#define speed sprite->data[0]
void InitAnimLinearTranslation(struct Sprite *sprite)
{
    s32 x = dstX - startX;
    s32 y = dstY- startY;
    deltaX = Div((x * 256), speed);
    deltaY = Div((y * 256), speed);
}


u8 AnimTranslateLinear(struct Sprite* sprite)
{
    // destination reached
    if (!speed)
        return true;
    sprite->pos1.x += deltaX / 256;
    sprite->pos1.y += deltaY / 256;
    speed--;
    return false;
}

// meant to be used in conjunction with ScriptCmd_confighorizontalarctranslate
void TaskTranslateSpriteHorizontalArc(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* sprite = &gSprites[t->priv[1]];
    if (!sprite->data[0] || !sprite->inUse) {
        DestroyTask(taskId);
        return;
    }
    sprite->data[7] += sprite->data[6]; // frequency step
    // amplitude must be a percentage from total amplitude * current sin(x) / sin(pi/2)
    u32 percent = (Sin2(sprite->data[7]) * 100) / Sin2(90);
    sprite->pos1.y = PERCENT(sprite->data[5], percent) + sprite->data[3];
    sprite->pos1.x += (sprite->data[2] / 256);
    // add 1px to the X as an error correction, if conditions align
    if (sprite->data[4] != 0) {
        if ((sprite->data[0] % sprite->data[4]) == 0) {
            sprite->pos1.x += 1;
        }
    }
    sprite->data[0]--;
}

// meant to be used in conjunction with ScriptCmd_confighorizontalarctranslate
void TaskTranslateSpriteHorizontalArcCos(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* sprite = &gSprites[t->priv[1]];
    if (!sprite->data[0] || !sprite->inUse) {
        DestroyTask(taskId);
        return;
    }
    sprite->data[7] += sprite->data[6]; // frequency step
    // amplitude must be a percentage from total amplitude * current sin(x) / sin(pi/2)
    u32 percent = (Cos2(sprite->data[7]) * 100) / Cos2(0);
    sprite->pos1.y = PERCENT(sprite->data[5], percent) + (sprite->data[3] * 2);
    sprite->pos1.x += (sprite->data[2] / 256);
    // add 1px to the X as an error correction, if conditions align
    if (sprite->data[4] != 0) {
        if ((sprite->data[0] % sprite->data[4]) == 0) {
            sprite->pos1.x -= 1;
        }
    }
    sprite->data[0]--;
}

#undef startX
#undef deltaX
#undef dstX
#undef startY
#undef deltaY
#undef dstY
#undef speed

extern const struct CompressedSpriteSheet pokeballParticleSprite;
extern const struct SpritePalette pokeballParticlePalette;
extern const struct OamData pokeballParticleOam;
extern const struct Frame* pokeballParticleLoopPtr[];

#define basemovement 1
#define spritedur 40
#define randfactor 16
void SCBMoveSpriteLinear(struct Sprite* s)
{
    s->pos1.x += s->data[0];
    s->pos1.y += s->data[1];
    s->data[2]++;
    if (s->data[2] > spritedur) {
        FreeSpriteOamMatrix(s);
        obj_free(s);
    }
}


void TaskDrawPokeballGlitter(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* sprite = &gSprites[t->priv[1]]; // ballsprite

    switch (t->priv[0]) {
        case 0:
        {
            // make the sprites
            struct CompressedSpriteSheet gfx = (struct CompressedSpriteSheet)pokeballParticleSprite;
            struct SpritePalette pal = (struct SpritePalette)pokeballParticlePalette;
            struct Template spriteTemp = {gfx.tag, pal.tag, &pokeballParticleOam, (void*)pokeballParticleLoopPtr, &gfx, nullrsf, (SpriteCallback)SCBMoveSpriteLinear};
            LoadCompressedSpriteSheetUsingHeap(&gfx);
            LoadCompressedSpritePaletteUsingHeap(&pal);
            u8 spriteId = template_instanciate_forward_search(&spriteTemp, sprite->pos1.x, sprite->pos1.y, 0);
            switch (t->priv[10]) {
                case 0:
                    // axis y = 0, for all positive X
                    gSprites[spriteId].data[0] = basemovement;
                    gSprites[spriteId].data[1] = 0;
                    // randomize start position
                    gSprites[spriteId].pos1.x += rand() % randfactor;
                    break;
                case 1:
                    // axis y = 0, for all negative x
                    gSprites[spriteId].data[0] = -basemovement;
                    gSprites[spriteId].data[1] = 0;
                    // randomize start position
                    gSprites[spriteId].pos1.x -= rand() % randfactor;
                    break;
                case 2:
                    // axis x = 0, for all positive y
                    gSprites[spriteId].data[0] = 0;
                    gSprites[spriteId].data[1] = basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.y += rand() % randfactor;
                    break;
                case 3:
                    // axis x = 0, for all negative y
                    gSprites[spriteId].data[0] = 0;
                    gSprites[spriteId].data[1] = -basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.y -= rand() % randfactor;
                    break;
                case 4:
                    // y = x, for all positive x
                    gSprites[spriteId].data[0] = basemovement;
                    gSprites[spriteId].data[1] = basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.x += rand() % randfactor;
                    gSprites[spriteId].pos1.y += rand() % randfactor;
                    break;
                case 5:
                    // y = x, for all negative x
                    gSprites[spriteId].data[0] = -basemovement;
                    gSprites[spriteId].data[1] = basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.x -= rand() % randfactor;
                    gSprites[spriteId].pos1.y += rand() % randfactor;
                    break;
                case 6:
                    // y = -x, for all positive x
                    gSprites[spriteId].data[0] = basemovement;
                    gSprites[spriteId].data[1] = -basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.x += rand() % randfactor;
                    gSprites[spriteId].pos1.y -= rand() % randfactor;
                    break;
                case 7:
                    // y = -x, for all negative x
                    gSprites[spriteId].data[0] = -basemovement;
                    gSprites[spriteId].data[1] = -basemovement;
                    // randomize start position
                    gSprites[spriteId].pos1.x -= rand() % randfactor;
                    gSprites[spriteId].pos1.y -= rand() % randfactor;
                    break;
            };
            t->priv[10]++;
            if (t->priv[10] == 8)
                t->priv[0]++;
            break;
        }
        case 1:
            DestroyTask(taskId);
            break;
    };

}


void TaskAnimYesNo(u8 taskId)
{
    struct Task* t = &tasks[taskId];
    struct Sprite* cursor = &gSprites[t->priv[1]];
    bool currentPos = t->priv[2];
    // draw cursor on current position
    if (currentPos) {
        // NO
        cursor->pos1.x = 186;
        cursor->pos1.y = 97;
    } else {
        // YES
        cursor->pos1.x = 186;
        cursor->pos1.y = 83;
    }
    // update cursorPos on input
    switch (gMain.newKeys & (KEY_A | KEY_B | KEY_DOWN | KEY_UP)) {
        case KEY_A:
            // an option is selected (lets buffer the option into a local var?)
            PlaySE(SOUND_GENERIC_CLINK);
            VarSet(0x8000, currentPos);
            dprintf("selected option is %d\n", currentPos);
            DestroyTask(taskId);
            break;
        case KEY_B:
            // same as pressing no
            VarSet(0x8000, 1);
            dprintf("selected option is No\n");
            PlaySE(SOUND_GENERIC_CLINK);
            DestroyTask(taskId);
            break;
        case KEY_DOWN:
        case KEY_UP:
            PlaySE(SOUND_GENERIC_CLINK);
            t->priv[2] = !currentPos;
            break;
        default:
            break;
    };
}



#undef gtargetx
#undef gtargety
