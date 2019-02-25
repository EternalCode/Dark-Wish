#include <pokeagb/pokeagb.h>
#include "pokemon/pokemon_base_stats.h"

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
