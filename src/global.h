#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

#include <pokeagb/pokeagb.h>
#include "core/saveblock_expansion/save.h"
#include "pokemon/pokemon_base_stats.h"

/* Util general */
extern u16 rand_range(u16 min, u16 max);

/* Pokemon data fetching */
#define TYPES_OF_SPECIES(species) (gBaseStats[species].type1 | (gBaseStats[species].type2 << 8))
extern u8 get_ability(u16 species, u8 ability_index);
extern bool PartyHasAbility(u8 ability);
extern u8 GetPokemonAbility(struct Pokemon* p);
extern u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);


/* EventObjects fetch macros */
#define EVENTID_DIR(i) (gEventObjects[i].direction & 0xF)
#define EVENTOBJ_DIR(n) (n->direction & 0xF)

/* var access funcs */
extern u8 *GetFlagPointer(u16 id);
extern u16 *GetVarPointer(u16 id);

/* Colors */
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

/* Textbox stuff */
extern const u16 GenericTextPal[];
extern struct TextColor textBlack;
extern struct TextColor textWhite;
extern struct TextColor textRed;
extern struct TextColor textGreen;

/* CPUset */
#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))
extern void CpuFastSet(void* src, void* dst, u32 mode);

/* Game clock */
// we'll say 60 minutes is 1 day. So 1140 mins is 1 day,
#define TIME_SCALE 19
#define MINUTES_IN_A_DAY 1140
extern void GetClockTime(u8* hour, u8* min);

/* Debugging */
extern void dprintf(const char * str, ...);

#endif /* GLOBAL_DEFS_H_ */
