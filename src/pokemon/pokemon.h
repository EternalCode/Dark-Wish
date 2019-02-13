#ifndef POKEMON_H_
#define POKEMON_H_

#include <pokeagb/pokeagb.h>
#include "pokemon_base_stats.h"
#include "evolution/evolution_table.h"
#include "species.h"

#define POKE_COUNT SPECIES_MAX
#define EVOS_PER_MON 5


struct BattleMove
{
    u8 argument;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 secondaryEffectChance;
    u8 target;
    s8 priority;
    u32 flags;
    u8 split;
    u16 effect;
};


#define START_ADDR_FRONT_T (const u8*)0x08740000
#define START_ADDR_BACK_T (const u8*)0x8740000 + 0x50000
#define START_ADDR_PAL_T (const u8*)0x8740000 + 0x100000

extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];
extern const struct LearnMove* const gLevelUpLearnsets[POKE_COUNT];
extern const u8 gMoveNames[MOVE_MAX][POKEAGB_MOVE_NAME_LENGTH];
extern const void* FrontSpriteGfxTable;
extern const void* BackSpriteGfxTable;
extern const void* PKMNSpritePalTable;
extern const struct BattleMove gBattleMoves[];

struct MonCoords
{
    u8 width : 4;
    u8 height : 4;
    u8 y_offset;
};

struct LearnMove {
	u16 move;
	u8 level;
	u8 padding;
};



#endif /* POKEMON_H_ */
