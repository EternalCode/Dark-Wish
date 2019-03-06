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
