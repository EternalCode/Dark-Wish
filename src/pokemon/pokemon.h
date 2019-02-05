#ifndef POKEMON_H_
#define POKEMON_H_

#include <pokeagb/pokeagb.h>
#include "pokemon_base_stats.h"

#define POKE_COUNT 248 + 1

#define START_ADDR_FRONT_T (const u8*)0x08740000
#define START_ADDR_BACK_T (const u8*)0x8740000 + 0x4000
#define START_ADDR_PAL_T (const u8*)0x8740000 + 0x8000

extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];
extern const u16 *const gLevelUpLearnsets[SPECIES_MAX];
extern const void* FrontSpriteGfxTable;
extern const void* BackSpriteGfxTable;
extern const void* PKMNSpritePalTable;


struct MonCoords
{
    u8 width : 4;
    u8 height : 4;
    u8 y_offset;
};


#endif /* POKEMON_H_ */
