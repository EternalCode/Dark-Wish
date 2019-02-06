#ifndef POKEMON_EVOLUTION_H_
#define POKEMON_EVOLUTION_H_

#include <pokeagb/pokeagb.h>

#define EVOS_PER_MON 5
#define EVO_REQ_FEMALE 1
#define EVO_REQ_MALE 0

#define EVO_FRIENDSHIP       0x0001 // Pokémon levels up with friendship ≥ 220
#define EVO_FRIENDSHIP_DAY   0x0002 // Pokémon levels up during the day with friendship ≥ 220
#define EVO_FRIENDSHIP_NIGHT 0x0003 // Pokémon levels up at night with friendship ≥ 220
#define EVO_LEVEL            0x0004 // Pokémon reaches the specified level
#define EVO_TRADE            0x0005 // Pokémon is traded
#define EVO_TRADE_ITEM       0x0006 // Pokémon is traded while it's holding the specified item
#define EVO_ITEM             0x0007 // specified item is used on Pokémon
#define EVO_LEVEL_ATK_GT_DEF 0x0008 // Pokémon reaches the specified level with attack > defense
#define EVO_LEVEL_ATK_EQ_DEF 0x0009 // Pokémon reaches the specified level with attack = defense
#define EVO_LEVEL_ATK_LT_DEF 0x000A // Pokémon reaches the specified level with attack < defense
#define EVO_LEVEL_SILCOON    0x000B // Pokémon reaches the specified level with a Silcoon personality value
#define EVO_LEVEL_CASCOON    0x000C // Pokémon reaches the specified level with a Cascoon personality value
#define EVO_LEVEL_NINJASK    0x000D // Pokémon reaches the specified level (special value for Ninjask)
#define EVO_LEVEL_SHEDINJA   0x000E // Pokémon reaches the specified level (special value for Shedinja)
#define EVO_BEAUTY           0x000F // Pokémon levels up with beauty ≥ specified value
#define EVO_LEVEL_DAY        0x0010 // Pokemon Levels up during the night
#define EVO_LEVEL_NIGHT      0x0011 // Pokemon Levels up during the night
#define EVO_LEVEL_DUSK       0x0012 // Pokemon Levels up during the night
#define EVO_LEVEL_KNOW_MOVE  0x0013 // Pokemon Levels up while knowing a move param_2
#define EVO_LEVEL_GENDER     0x0014 // Pokemon needs to be a specified gender to evolve
#define EVO_LEVEL_WEATHER    0x0015 // Pokemon Levels during OW weather condition (param2)
#define EVO_NEAR_MOSS        0x0016 // Pokemon Levels on map near location
#define EVO_NEAR_ICE         0x0017 // Pokemon Levels on map near location
#define EVO_LEVEL_MOVE_TYPE  0x0018 // Pokemon Levels up while knowing a TYPE of move param_2
#define EVO_LEVEL_ITEM       0x0019 // Pokemon Levels up while knowing holding an item param_2
#define EVO_LEVEL_ITEM_NIGHT 0x001A // Pokemon Levels up while knowing holding an item param_2 at night
#define EVO_LEVEL_ELEC_FIELD 0x001B // Pokemon Levels up while in electric field
#define EVO_LEVEL_WITH_TYPE  0x001C // Pokemon Levels up while in electric field
#define EVO_LEVEL_EEVEE      0x001D // Eevee's non-stone evolution stuff



struct Evolution
{
    u16 method;
    u16 param;
    u16 targetSpecies;
    u16 param_2;
};

extern const struct Evolution gEvolutionTable[248][EVOS_PER_MON];

#endif /* POKEMON_EVOLUTION_H_ */
