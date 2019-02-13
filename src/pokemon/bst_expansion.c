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
