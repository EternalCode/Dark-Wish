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
        spr->pos1.x += deltaX > 0 ? 1 : -1;
    if (totalFramesPast % yerror == 0)
        spr->pos1.y += deltaY > 0 ? 1 : -1;
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
        }
        sprite->callback = (oac_nullsub);
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


void AttemptNonConstRotscale(struct Sprite* sprite)
{
    switch (sprite->data[0]) {
        case 0:
        {
            struct RotscaleFrame* affineTable = (void*)malloc_and_clear(sizeof(struct RotscaleFrame) * 2);
            affineTable[1].scale_delta_x = 0x7FFF;
            affineTable[0].scale_delta_x = 6;
            affineTable[0].scale_delta_y = 6;
            affineTable[0].rot_delta = -7;
            affineTable[0].duration = 24;
            affineTable[0].field_6 = 0;
            u32* ptr = (u32*)malloc_and_clear(4);
            *ptr = (u32)affineTable;
            sprite->rotscale_table = (void*)ptr;
            StartSpriteAffineAnim(sprite, 0);
            sprite->data[0]++;
        }
        default:
            break;
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
