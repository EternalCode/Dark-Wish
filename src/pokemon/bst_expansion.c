#include <pokeagb/pokeagb.h>
#include "pokemon.h"

extern struct CompressedSpriteSheet gMonStillFrontPicTable[POKE_COUNT];
extern struct CompressedSpriteSheet gMonBackPicTable[POKE_COUNT];
extern struct SpritePalette gMonSpritePalTable[POKE_COUNT];

void* GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality) {
    /* TODO: Shiny sprite palettes */
    return (void*)gMonSpritePalTable[species].data;
}
