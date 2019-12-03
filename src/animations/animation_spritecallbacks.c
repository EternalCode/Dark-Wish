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
#define delay spr->data[7]

void SCBMoveSpriteErrorCorrection(struct Sprite* spr)
{
    if ((delay > 0) && (framesPast % delay)) {
        framesPast++;
        framesCount++;
        return;
    }
    if (framesPast <= framesCount) {
        spr->pos1.x += deltaX;
        spr->pos1.y += deltaY;
        framesPast++;
    } else {
        FreeSpriteOamMatrix(spr);
        obj_free(spr);
        return;
    }
    totalFramesPast++;
    u16 absXerr = ABS(xerror);
    u16 absYerr = ABS(yerror);
    if (absXerr > 0) {
        if (totalFramesPast % absXerr == 0)
            spr->pos1.x += xerror > 0 ? 1 : -1;
    }
    if (absYerr > 0) {
        if (totalFramesPast % absYerr == 0)
            spr->pos1.y += yerror > 0 ? 1 : -1;
    }
}
#undef framesCount
#undef deltaX
#undef deltaY
#undef xerror
#undef yerror
#undef totalFramesPast
#undef framesPast
#undef delay

void SCB_SpriteDeleteWhenAffineEnds(struct Sprite* sprite)
{
    if (sprite->affineAnimEnded) {
        FreeSpriteOamMatrix(sprite);
        obj_free(sprite);
        DestroySprite(sprite);
    }
}

void SCB_SpriteDeleteWhenAnimEnds(struct Sprite* sprite)
{
    if (sprite->animEnded) {
        FreeSpriteOamMatrix(sprite);
        obj_free(sprite);
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

void SCB_SpriteDeleteAfter20Frames(struct Sprite* sprite)
{
    sprite->data[0]++;
    if (sprite->data[0] == 20) {
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}

void SCB_SpriteDeleteAfter60Frames(struct Sprite* sprite)
{
    sprite->data[0]++;
    if (sprite->data[0] == 60) {
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

/*
data[0] = untransparent distance
data[1] = angle
data[2] = 30 - dist to travel
data[3] = 8  - speed
*/
void SpriteTravelDir(struct Sprite* sprite)
{
    switch (sprite->data[5]) {
        case 0:
        {
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
            sprite->data[5]++;
        }
        default:
        {
            sprite->data[4] += sprite->data[3];
            sprite->pos2.x = Sin(sprite->data[1], sprite->data[4]);
            sprite->pos2.y = Cos(sprite->data[1], sprite->data[4]);
            sprite->invisible = false;
            if (sprite->data[4] > sprite->data[0] && sprite->data[4] < sprite->data[0] + 64) {
                sprite->final_oam.obj_mode = 0;
            } else {
                sprite->final_oam.obj_mode = 1;
            }
            if (sprite->data[4] > sprite->data[2]) {
                // sprite has traveled 80 pixels from origin
                sprite->callback = oac_nullsub;
                u32** ptr = (u32**)sprite->rotscale_table;
                free(*ptr);
                free(ptr);
                FreeSpriteOamMatrix(sprite);
                obj_free(sprite);
            }
            break;
        }
    };
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
