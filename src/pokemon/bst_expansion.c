#include <pokeagb/pokeagb.h>
#include "pokemon.h"
#include "../global.h"

extern struct CompressedSpriteSheet gMonStillFrontPicTable[POKE_COUNT];
extern struct CompressedSpriteSheet gMonBackPicTable[POKE_COUNT];
extern struct SpritePalette gMonSpritePalTable[POKE_COUNT];

void* GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality) {
    /* TODO: Shiny sprite palettes */
    dprintf("attempting to get pal for species %x\n", species);
    return (void*)gMonSpritePalTable[species].data;
}
//
// pokemon_make_full(struct Pokemon* dst,
//                                       u16 species,
//                                       u8 level,
//                                       u8 iv,
//                                       bool use_pid,
//                                       u32 pid,
//                                       u8 use_tid,
//                                       u32 tid);

void make_pkmn()
{
    var_8000++;
    pokemon_make_full((struct Pokemon*)0x202402C, var_8000, 10, 0, 0, 0, 1, 1921);
}
