#include <pokeagb/pokeagb.h>
#include "pokemon/pokemon_base_stats.h"
#include "pokemon/pokemon.h"

#define TIME_SCALE 19
#define MINUTES_IN_A_DAY 1140
extern u8 SpeciesGetIndexAbility(u16 species, u8 abilityIndicator);
extern void dprintf(const char * str, ...);

const struct Frame (**nullframe)[] = (const struct Frame (**)[])0x8231CF0;
const struct RotscaleFrame (**nullrsf)[] = (const struct RotscaleFrame (**)[])0x8231CFC;

void CpuFastSet(void* src, void* dst, u32 mode)
{
    __asm__("swi 0xC");
}

s32	Div(s32 num, s32 divisor)
{
    __asm__("swi 0x6");
    __asm__("bx lr");
    return 0;
}

u32	Sqrt(u32 num)
{
    __asm__("swi 0x8");
    __asm__("bx lr");
    return 0;
}

u16 ArcTan2(u16 angle)
{
    __asm__("swi 0xA");
    __asm__("bx lr");
    return 0;
}


void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, s32 count, s32 offset)
{
    __asm__("swi 0xF");
    __asm__("bx lr");
}

u16 rand_range(u16 min, u16 max)
{
    if (min == max) return min;
    return (rand() % (max - min)) + min;
}


void GetClockTime(u8* hour, u8* min)
{
    u32 totalMinutes = gSaveBlock2Ptr->playTimeMinutes + (gSaveBlock2Ptr->playTimeHours * 60);
    totalMinutes = (totalMinutes * TIME_SCALE) % MINUTES_IN_A_DAY;
    // add in seconds too
    totalMinutes += (gSaveBlock2Ptr->playTimeSeconds * TIME_SCALE) / 60;
    *min = totalMinutes % 60;
    totalMinutes -= *min;
    *hour = totalMinutes / 60;
}


bool PartyHasAbility(u8 ability)
{
    for (u8 i = 0; i < gPartyCount; i++) {
        if (pokemon_getattr(&party_player[i], REQUEST_SANITY_X6, NULL)) continue; // egg
        u16 species = pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL);
        u8 monAbility = SpeciesGetIndexAbility(species, pokemon_getattr(&party_player[i], REQUEST_ABILITY_BIT, NULL));
        if (monAbility == ability) {
            return true;
        }
    }
    return false;
}


u8 GetPokemonAbility(struct Pokemon* p)
{
    if (!pokemon_getattr(p, REQUEST_SANITY_X6, NULL)) {
        u16 species = pokemon_getattr(p, REQUEST_SPECIES, NULL);
        u8 monAbility = SpeciesGetIndexAbility(species, pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL));
        return monAbility;
    }
    return ABILITY_NONE;
}


u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality)
{
    switch (gBaseStats[species].genderRatio) {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        return gBaseStats[species].genderRatio;
    };
    if (gBaseStats[species].genderRatio > (personality & 0xFF))
        return MON_FEMALE;
    else
        return MON_MALE;
}

extern u16* GetEggMoves(u16 species);
u8 CountEggMoves(u16 species)
{
    u16* eggMoves = GetEggMoves(species);
    u8 i = 0;
    while (eggMoves[i] != MOVE_NONE)
        i++;
    return i;
}

#define PCBOX_COUNT 13
#define PCBOX_COMPACITY 30
bool SpaceAvailableInPC()
{
    for (u8 box = 0; box < PCBOX_COUNT; box++) {
        for (u8 i = 0; i < PCBOX_COMPACITY; i++) {
            if (!pokemon_getattr(&saveblock3->bills_pc[(box * PCBOX_COMPACITY) + i], REQUEST_SPECIES, NULL))
                return true;
        }
    }
    return false;
}

bool SpaceAvailableInPartyPlayer()
{
    for (u8 i = 0; i < 6; i++) {
        if (!pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL))
            return true;
    }
    return false;
}

bool SpaceAvailableForPKMN()
{
    return (SpaceAvailableInPC() || SpaceAvailableInPartyPlayer());
}

void AddOpponentPokemonToPlayer()
{
    // party
    for (u8 i = 0; i < 6; i++) {
        if (!pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL)) {
            // drop pokemon in this slot
            memcpy(&party_player[i], &party_opponent[0], sizeof(struct Pokemon));
            return true;
        }
    }
    // bank
    for (u8 box = 0; box < PCBOX_COUNT; box++) {
        for (u8 i = 0; i < PCBOX_COMPACITY; i++) {
            if (!pokemon_getattr(&saveblock3->bills_pc[(box * PCBOX_COMPACITY) + i], REQUEST_SPECIES, NULL)) {
                // drop pokemon in this slot
                memcpy(&party_player[i], &party_opponent[0], sizeof(struct BoxPokemon));
                return true;
            }
        }
    }
}

#undef PCBOX_COUNT
#undef PCBOX_COMPACITY


u32 PokemonExpNeededToLevel(u8 slot)
{
    // get current level
    u8 level = pokemon_getattr(&party_player[slot], REQUEST_LEVEL, NULL);
    // get current exp
    u32 currentExp = pokemon_getattr(&party_player[slot], REQUEST_EXP_POINTS, NULL);
    // calc exp for next level
    u16 species = pokemon_getattr(&party_player[slot], REQUEST_SPECIES, NULL);
    u32 speciesExpIndex = (gBaseStats[species].growthRate * 0x194);
	u32 *expNeeded = (u32*) (0x8253AE4 + (speciesExpIndex + ((level + 1) * 4)));
    dprintf("exp needed is logged as %d to reach level %d\n", *expNeeded - currentExp, level + 1);
    // substract current exp from needed exp
    return *expNeeded - currentExp;
}


struct Sprite* GetSpriteFromGfxTag(u16 tag)
{
    /* This doesn't see reliable at all... Currently objid is the best way to get a sprite */
    return NULL;
}


const struct OamData icon_oam2 = {
    .y = 0,
    .affine_mode = 1,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrix_num = 0,
    .size = 2, // 32x32 square
    .tile_num = 0,
    .priority = 0, /*above the rest*/
    .palette_num = 0,
    .affine_param = 0,
};

u8 SpawnPokemonObj(u16 species, u32 pid, s16 x, s16 y, u16 tag)
{
    if (species > 0) {
        void *icon_gfx = load_party_icon_tiles_with_form(species, pid, false);
        struct SpritePalette pal = {&pokeicon_pals[pokeicon_pal_indices[species]], tag};
        struct CompressedSpriteSheet icon_tiles = {icon_gfx, 4 * 8 * 32, tag};
        gpu_tile_obj_alloc_tag_and_upload(&icon_tiles);
        gpu_pal_obj_alloc_tag_and_apply(&pal);
        struct Template icon_template = {
                                        .tiles_tag = tag,
                                        .pal_tag = tag,
                                        .oam = &icon_oam2,
                                        .animation = nullframe,
                                        .graphics = &icon_tiles,
                                        .rotscale = nullrsf,
                                        .callback = oac_nullsub,
                                        };
        return CreateSprite(&icon_template, x, y, 0);
    }
    return 0x3F;
}

extern const struct LearnMove* const gLevelUpLearnsets[];
u8 PokemonLearnsMoveLevel(u16 species, u8 level, u16* moveBuffer)
{
    struct LearnMove* learnmove = (struct LearnMove*)gLevelUpLearnsets[species];
    u8 setIndex = 0;
    u8 bufferIndex = 0;
    while (true) {
        if (learnmove[setIndex].level == level) {
            moveBuffer[bufferIndex] = learnmove[setIndex].move;
            bufferIndex++;
        } else if (learnmove[setIndex].level > level) {
            break;
        }
        setIndex++;
    }
    return bufferIndex;
}


u8 PokemonCountUsableMoves(struct Pokemon *p)
{
    for (u8 i = 0; i < 4; i++) {
        if (!pokemon_getattr(p, REQUEST_MOVE1 + i, NULL))
            return i;
    }
    return 4;
}


void BlendPalette(u16 palOffset, u16 numEntries, u8 coeff, u16 blendColor)
{
    u16 i;
    for (i = 0; i < numEntries; i++)
    {
        u16 index = i + palOffset;
        struct ColorComponents *data1 = (struct ColorComponents *)&gPlttBufferUnfaded[index];
        s8 r = data1->r;
        s8 g = data1->g;
        s8 b = data1->b;
        struct ColorComponents *data2 = (struct ColorComponents *)&blendColor;
        gPlttBufferFaded[index] = ((r + (((data2->r - r) * coeff) >> 4)) << 0)
                                | ((g + (((data2->g - g) * coeff) >> 4)) << 5)
                                | ((b + (((data2->b - b) * coeff) >> 4)) << 10);
    }
}

void ClearSpriteData(struct Sprite* s)
{
    for (u8 i = 0; i < 8; i++)
        s->data[i] = 0;
}
