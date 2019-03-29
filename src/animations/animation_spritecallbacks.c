#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"
#include "../battle/battle_actions/actions.h"
#include "../battle/battle_data/battle_state.h"
#include "../battle/battle_data/pkmn_bank_stats.h"


void SCB_SpriteBlink(struct Sprite* sprite)
{
    sprite->invisible = !sprite->invisible;
}


#define framesCount spr->data[0]
#define deltaX spr->data[1]
#define deltaY spr->data[2]
#define xerror spr->data[3]
#define yerror spr->data[4]
#define totalFramesPast spr->data[5]
#define framesPast spr->data[6]

void SCBMoveSpriteErrorCorrection(struct Sprite* spr)
{
    totalFramesPast++;
    if (totalFramesPast % xerror == 0)
        spr->pos1.x += deltaX >= 0 ? 1 : -1;
    if (totalFramesPast % yerror == 0)
        spr->pos1.y += deltaY >= 0 ? 1 : -1;
    if (framesPast < framesCount) {
        spr->pos1.x += deltaX;
        spr->pos1.y += deltaY;
        framesPast++;
    } else {
        FreeSpriteOamMatrix(spr);
        obj_free(spr);
    }
}
#undef framesCount
#undef deltaX
#undef deltaY
#undef xerror
#undef yerror
#undef totalFramesPast
#undef framesPast

void SCB_SpriteDeleteWhenAffineEnds(struct Sprite* sprite)
{
    if (sprite->affineAnimEnded) {
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}

void SCB_SpriteDeleteAfter10Frames(struct Sprite* sprite)
{
    sprite->data[0]++;
    if (sprite->data[0] == 10) {
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}

void AnimOrbitFastStep(struct Sprite *sprite)
{
    if ((u16)(sprite->data[1] - 64) < 128)
        sprite->final_oam.priority = MAX(0, sprite->data[7] + 1);
    else
        sprite->final_oam.priority = MIN(3, sprite->data[7] - 1);

    sprite->pos2.x = Sin(sprite->data[1], sprite->data[2]);
    sprite->pos2.y = Cos(sprite->data[1], sprite->data[3]);
    sprite->data[1] = (sprite->data[1] + sprite->data[4]) & 0xFF;
    sprite->data[0]--;
    if (sprite->data[0] == 0) {
        if (sprite->data[6]) {
            gAnimationCore->wait[sprite->data[6] - 1] = false;
        }
        if (sprite->data[5]) {
            FreeSpriteOamMatrix(sprite);
            obj_free(sprite);
            sprite->final_oam.priority = 3;
        }
        sprite->callback = (oac_nullsub);
    }
}

void AnimOrbitFastStepNoPriority(struct Sprite *sprite)
{
    sprite->pos2.x = Sin(sprite->data[1], sprite->data[2]);
    sprite->pos2.y = Cos(sprite->data[1], sprite->data[3]);
    sprite->data[1] = (sprite->data[1] + sprite->data[4]) & 0xFF;
    sprite->data[0]--;
    if (sprite->data[0] == 0) {
        if (sprite->data[6]) {
            gAnimationCore->wait[sprite->data[6] - 1] = false;
        }
        if (sprite->data[5]) {
            FreeSpriteOamMatrix(sprite);
            obj_free(sprite);
            return;
        }
        sprite->callback = (oac_nullsub);
    }
    // calcuate the center
    if (sprite->final_oam.affine_mode) {
        dprintf("runniadfasdfasdfasdfng this\n");
        CalcCenterToCornerVec(sprite, sprite->final_oam.shape, sprite->final_oam.size, sprite->final_oam.affine_mode);
    }
}

void AnimOrbitShrinkNoPriority(struct Sprite *sprite)
{
    sprite->pos2.x = Sin(sprite->data[1], sprite->data[2]);
    sprite->pos2.y = Cos(sprite->data[1], sprite->data[3]);
    sprite->data[1] = (sprite->data[1] + sprite->data[4]) & 0xFF;
    sprite->data[0]--;
    if (sprite->data[0] % 2) {
        sprite->data[3] = MAX(0, sprite->data[3] - 1);
        sprite->data[2] = MAX(0, sprite->data[2] - 1);
    }
    if (sprite->data[0] == 0) {
        if (sprite->data[6]) {
            gAnimationCore->wait[sprite->data[6] - 1] = false;
        }
        if (sprite->data[5]) {
            FreeSpriteOamMatrix(sprite);
            obj_free(sprite);
        }
        sprite->callback = (oac_nullsub);
    }
}


void SpriteTravelRandDirFlash(struct Sprite* sprite)
{
    switch (sprite->data[0]) {
        case 0:
        {
            sprite->data[3] = rand_range(2, 5);
            sprite->final_oam.affine_mode = 1;
            struct RotscaleFrame* affineTable = (void*)malloc_and_clear(sizeof(struct RotscaleFrame) * 2);
            affineTable[0].scale_delta_x = 6;
            affineTable[0].scale_delta_y = 6;
            affineTable[0].rot_delta = sprite->data[1];
            affineTable[0].duration = 1;
            affineTable[0].field_6 = 0;
            affineTable[1].scale_delta_x = 0x7FFF;
            u32* ptr = (u32*)malloc_and_clear(4);
            *ptr = (u32)affineTable;
            sprite->rotscale_table = (void*)ptr;
            StartSpriteAffineAnim(sprite, 0);
            sprite->data[0]++;
            sprite->final_oam.priority = rand_range(2, 4);
        }
        default:
        {
            sprite->data[2] += sprite->data[3];
            sprite->pos2.x = Sin(sprite->data[1], sprite->data[2]);
            sprite->pos2.y = Cos(sprite->data[1], sprite->data[2]);
            sprite->invisible = false;
            u8 pal_slot = sprite->final_oam.palette_num;
            sprite->data[4]++;
            if (sprite->data[2] > 80) {
                // sprite has traveled 80 pixels from origin
                sprite->callback = oac_nullsub;
                u32** ptr = (u32**)sprite->rotscale_table;
                free(*ptr);
                free(ptr);
                FreeSpriteOamMatrix(sprite);
                obj_free(sprite);
            } else if (!(sprite->data[4] % 3)) {
                BlendPalette((pal_slot * 16) + (16 * 16), 16, 16, 0xFFFF);
            } else {
                BlendPalette((pal_slot * 16) + (16 * 16), 16, 0, 0xFFFF);
            }
            break;
        }
    };
}

void ManualRotationAttempt(struct Sprite* sprite)
{
    sprite->final_oam.affine_mode = 1;
    sprite->affineAnimPaused = true;
    u8 matrixNum = sprite->final_oam.matrix_num;
    struct ObjAffineSrcData src;
    src.xScale = 1 * 256;
    src.yScale = 1 * 256;
    src.rotation = (sprite->data[0]) << 8;
    ObjAffineSet(&src, (void *)&gOamMatrices[matrixNum], 1, 2);
    sprite->pos2.x = Sin(sprite->data[0], 20) - 32;
    sprite->pos2.y = Cos(sprite->data[0], 20) - 52;
    sprite->centerToCornerVecX = 0;
    sprite->centerToCornerVecY = 0;
    //CalcCenterToCornerVec(sprite, 0, 3, 1);
    sprite->data[0] = (sprite->data[0] + 1) & 0xFF;
    if (sprite->data[1])
        sprite->callback = oac_nullsub;

    if (sprite->data[0] == 0)
        sprite->data[1] = 1;
    else
        sprite->data[1] = 0;
}


void SCB_SpriteMove64UpAndDeleteWhenAffineEnds(struct Sprite* sprite)
{
    sprite->data[0]++;
    if (sprite->data[0] <= 64)
        sprite->pos1.y--;
    if (sprite->affineAnimEnded) {
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}


void SCB_SpriteFeatherFall(struct Sprite* sprite)
{
    if (sprite->data[4] == 0) {
        sprite->callback = oac_nullsub;
        if (sprite->data[5]) {
            FreeSpriteOamMatrix(sprite);
            DestroySprite(sprite);
        }
        return;
    }
    if (sprite->data[7] < sprite->data[0]) {
        sprite->data[7]++;
        return;
    }
    sprite->data[7] = 0;
    sprite->data[4]--;
    // update X in sin X by frequency
    sprite->data[6] = (sprite->data[6] + sprite->data[3]) & 0xFF;
    // move X influenced by sin wave
    sprite->pos1.x += Sin(sprite->data[6], sprite->data[2]);
    // move Y
    sprite->pos1.y += sprite->data[1];
}
