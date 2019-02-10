#include <pokeagb/pokeagb.h>

#define TIME_SCALE 19
#define MINUTES_IN_A_DAY 1140
extern u8 get_ability(u16 species, u8 abilityIndicator);

void CpuFastSet(void* src, void* dst, u32 mode)
{
    __asm__("swi 0xC");
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
        u8 monAbility = get_ability(species, pokemon_getattr(&party_player[i], REQUEST_ABILITY_BIT, NULL));
        if (monAbility == ability) {
            return true;
        }
    }
    return false;
}
