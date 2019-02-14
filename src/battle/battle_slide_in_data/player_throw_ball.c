#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "battle_obj_sliding.h"

extern void make_spinning_pokeball(s16 x, s16 y, u8 bank);


void PlayerThrowBallAndMoveScene(struct Sprite* spr)
{
    switch (spr->data[0]) {
        case 0:
            if (spr->pos1.x == -494) {
                spr->pos1.x = -480;
                spr->data[0]++;
            } else {
                spr->pos1.x -= 2;
            }
            break;
        case 1:
            // spawn ball
            if (spr->pos1.x == -492) {
                spr->data[0]++;
                make_spinning_pokeball(53, 64, spr->data[2]);
            }
            spr->pos1.x -= 2;
            break;
        case 2:
            if (spr->pos1.x < -530) {
                obj_free(spr);
            } else {
                spr->pos1.x -= 2;
            }
            break;
    };
}
