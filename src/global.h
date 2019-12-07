#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

#include <pokeagb/pokeagb.h>
#include "core/saveblock_expansion/save.h"
#include "pokemon/pokemon_base_stats.h"

/* Util general */
extern u16 rand_range(u16 min, u16 max);
s32 GreatestCommonFactor(s32 dividend, s32 divisor);


/* Pokemon sprite tables */
extern struct CompressedSpriteSheet gMonStillFrontPicTable[246];
extern struct SpritePalette gMonSpritePalTable[246];
extern struct CompressedSpriteSheet gMonBackPicTable[246];

/* Pokemon data fetching */
#define TYPES_OF_SPECIES(species) (gBaseStats[species].type1 | (gBaseStats[species].type2 << 8))
extern u8 SpeciesGetIndexAbility(u16 species, u8 ability_index);
extern bool PartyHasAbility(u8 ability);
extern u8 GetPokemonAbility(struct Pokemon* p);
extern u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
extern u16* GetEggMoves(u16 species);
extern u8 CountEggMoves(u16 species);
extern bool SpaceAvailableInPC(void);
extern bool SpaceAvailableInPartyPlayer(void);
extern bool SpaceAvailableForPKMN(void);
extern void AddOpponentPokemonToPlayer(void);
extern u8 PokemonCountUsableMoves(struct Pokemon* p);

/* EventObjects and sprite fetching */
#define EVENTID_DIR(i) (gEventObjects[i].facingDirection & 0xF)
#define EVENTOBJ_DIR(n) (n->facingDirection & 0xF)
struct Sprite* GetSpriteFromGfxTag(u16 tag);
extern void ClearSpriteData(struct Sprite* s);


/* var access funcs */
extern u8 *GetFlagPointer(u16 id);
extern u16 *GetVarPointer(u16 id);

/* Colors */
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))
extern void BlendPalette(u16 palOffset, u16 numEntries, u8 coeff, u16 blendColor);

/* Textbox stuff */
extern const u16 GenericTextPal[];
extern struct TextColor textBlack;
extern struct TextColor textWhite;
extern struct TextColor textRed;
extern struct TextColor textGreen;

/* Software interrupts */
#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))
extern void CpuFastSet(void* src, void* dst, u32 mode);
extern s32	Div(s32 num, s32 divisor);
extern s32	DivMod(s32 num, s32 divisor);
extern u32	Sqrt(u32 num);
extern u16 ArcTan2(s16 x, s16 y);
extern void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, s32 count, s32 offset);

/* Game clock */
// we'll say 60 minutes is 1 day. So 1140 mins is 1 day,
#define TIME_SCALE 19
#define MINUTES_IN_A_DAY 1140
extern void GetClockTime(u8* hour, u8* min);

/* Debugging */
extern void dprintf(const char * str, ...);

#endif /* GLOBAL_DEFS_H_ */
