#include <pokeagb/pokeagb.h>
#include "../pokemon.h"
#include "../../global.h"

#define LAST_MOVE(arr, x) arr[0] = arr[1];\
                          arr[1] = arr[2];\
                          arr[2] = arr[3];\
                          arr[3] = x;

bool FillPokemonMoves(struct Pokemon* p)
{
    u16 species = pokemon_getattr(p, REQUEST_SPECIES, NULL);
    u8 level = GetPokemonLevel(p);
    struct LearnMove* learnableMove = (struct LearnMove*)malloc_and_clear(sizeof(struct LearnMove)* 4);
    u8 j = 0;
    while (true) {
        // if move is valid and level is appropriate, add the move
        u16 learnmove = gLevelUpLearnsets[species][j].move;
        u8 learnlevel = gLevelUpLearnsets[species][j].level;
        if (learnmove != MOVE_NONE && learnmove != MOVE_NONE && level >= learnlevel) {
            if (learnableMove[3].move != MOVE_NONE) {
                LAST_MOVE(learnableMove, gLevelUpLearnsets[species][j]);
            } else {
                for (u8 i = 0; i < 4; i++) {
                    if (learnableMove[i].move == MOVE_NONE){
                        learnableMove[i].move = learnmove;
                        learnableMove[i].level = learnlevel;
                        break;
                    }
                }
            }
        } else {
            break;
        }
        j++;
    }
    for (u8 i = 0; i < 4; i++) {
        u16 move = learnableMove[i].move;
        pokemon_setattr(p, REQUEST_MOVE1 + i, &move);
        u8 PP = 5;//gBattleMoves[move].pp;
        pokemon_setattr(p, REQUEST_PP1 + i, &PP);
    }
    free(learnableMove);
    return 0;
}
