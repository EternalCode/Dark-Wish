#include <pokeagb/pokeagb.h>
#include "../../global.h"

u16 TryPickTypedSpecies(u8 env, u8 index, u8 type, u8* min, u8* max)
{
    u8 wildCount;
    if (env == 1) {
        wildCount = 12;
    } else {
        wildCount = 5;
    }
    struct wild_pokemon speciesList[wildCount];
    u8 matchedSpecies = 0;
    u16 breed;
    u8 minLevel;
    u8 maxLevel;
    for (u8 i = 0; i < wildCount; i++) {
        if (env == 1) {
            breed = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[i].species;
            minLevel = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[i].min_level;
            maxLevel = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[i].max_level;
        } else {
            breed = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[i].species;
            minLevel = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[i].min_level;
            maxLevel = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[i].max_level;
        }
        u16 types = TYPES_OF_SPECIES(breed);
        if (((types & 0xFF) == type) || ((types >> 8) == type)) {
            speciesList[matchedSpecies] = (struct wild_pokemon){minLevel, maxLevel, breed};
            matchedSpecies++;
        }
    }
    if (matchedSpecies) {
        u16 num = rand_range(0, matchedSpecies);
        *min = speciesList[num].min_level;
        *max = speciesList[num].max_level;
        return speciesList[num].species;
    } else {
        return 0;
    }
}


bool GenerateWildPokemon(u8 environment, u8 index)
{
    u16 wildIndexRoll = rand_range(0, 100);
    u16 species = 0;
    u8 minLevel = 0;
    u8 maxLevel = 0;
    u8 wildIndex = 0;
    if (environment == 1) { // grass
        if (wildIndexRoll <= 20) {
            // index 1
            wildIndex = 0;
        } else if (wildIndexRoll <= 40) {
            // index 2
            wildIndex = 1;
        } else if (wildIndexRoll <= 50) {
            // index 3
            wildIndex = 2;
        } else if (wildIndexRoll <= 60) {
            // index 4
            wildIndex = 3;
        } else if (wildIndexRoll <= 70) {
            // index 5
            wildIndex = 4;
        } else if (wildIndexRoll <= 80) {
            // index 6
            wildIndex = 5;
        } else if (wildIndexRoll <= 85) {
            // index 7
            wildIndex = 6;
        } else if (wildIndexRoll <= 90) {
            // index 8
            wildIndex = 7;
        } else if (wildIndexRoll <= 94) {
            // index 9
            wildIndex = 8;
        } else if (wildIndexRoll <= 98) {
            // index 10
            wildIndex = 9;
        } else if (wildIndexRoll <= 1) {
            // index 11
            wildIndex = 10;
        } else {
            // index 12
            wildIndex = 11;
        }
        dprintf("wild index was %d\n", wildIndex);
        species = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[wildIndex].species;
        minLevel = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[wildIndex].min_level;
        maxLevel = gWildMonHeaders[index].grass_encounter->wild_encounters->wild_grass[wildIndex].max_level;
    } else { // water
        if (wildIndexRoll <= 60) {
            // index 1
            wildIndex = 0;
        } else if (wildIndexRoll <= 90) {
            // index 2
            wildIndex = 1;
        } else if (wildIndexRoll <= 95) {
            // index 3
            wildIndex = 2;
        } else if (wildIndexRoll <= 99) {
            // index 4
            wildIndex = 3;
        } else {
            // index 5
            wildIndex = 4;
        }
        dprintf("wild index was %d\n", wildIndex);
        species = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[wildIndex].species;
        minLevel = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[wildIndex].min_level;
        maxLevel = gWildMonHeaders[index].water_encounter->wild_encounters->wild_water[wildIndex].max_level;
    }

    // abilities that change species
    u8 ability = GetPokemonAbility(party_player);
    u16 speciesMatch = 0;
    switch (ability) {
        case ABILITY_STATIC:
            speciesMatch = TryPickTypedSpecies(environment, index, TYPE_ELECTRIC, &minLevel, &maxLevel);
            if (speciesMatch) {
                species = speciesMatch;
            }
            break;
        case ABILITY_MAGNET_PULL:
            speciesMatch = TryPickTypedSpecies(environment, index, TYPE_STEEL, &minLevel, &maxLevel);
            if (speciesMatch) {
                species = speciesMatch;
            }
            break;
        default:
            break;
    };
    // calculate wild pokemon's level - some abilities affect this
    u8 level = 0;
    switch (ability) {
        case ABILITY_HUSTLE:
        case ABILITY_VITAL_SPIRIT:
        case ABILITY_PRESSURE:
            if (rand() % 2)
                level = maxLevel;
            break;
    };
    if (!level)
        level = rand_range(minLevel, maxLevel);

    // check repel vs level
    if ((level < party_player[0].level) && (VarGet(0x4020) > 0))
        return false;

    // abilities which reduce the encounter chance
    switch (ability) {
        case ABILITY_INTIMIDATE:
        case ABILITY_KEEN_EYE:
            if (party_player[0].level >= level + 5) {
                if (rand() % 2) {
                    return false;
                }
            }
            break;
        case ABILITY_SNOW_CLOAK:
            if (currentmap_header.weather == 0xA) {
                if (rand() % 2) {
                    return false;
                }
            }
            break;
    };
    dprintf("level was picked to be %d\n", level);
    // generate a PID for cute charm
    u32 PID = 0;
    if (ability == ABILITY_CUTE_CHARM) {
        dprintf("cutecharm manipulation..\n");
        // get gender of current pokemon
        u8 gender = pokemon_get_gender(party_player);
        u8 targetGender = 0;
        if (gender == PKMN_GENDER_BOY) {
            targetGender = PKMN_GENDER_GIRL;
        } else {
            targetGender = PKMN_GENDER_BOY;
        }

        // check if species can be target gender
        if (gBaseStats[species].genderRatio > 0 && gBaseStats[species].genderRatio < 254) {
            PID = ((rand() << 16) | rand());
            while (GetGenderFromSpeciesAndPersonality(species, PID) != targetGender) {
                PID = ((rand() << 16) | rand());
                dprintf("trying a new PID...\n");
            }
        }
    }
    // create pokemon
    if (PID) {
        pokemon_make_full(party_opponent, species, level, 0xFF, true, PID, false, 0);
    } else {
        pokemon_make_full(party_opponent, species, level, 0xFF, false, 0, false, 0);
    }
    return true;
}


bool DoWildEncounterRateDiceRoll(u16 encounterRate)
{
    return (rand() % 2880 < encounterRate);
}

bool DoWildEncounters(struct MapPosition* playerPos)
{
    u32 metatile = cur_mapdata_block_get_field_at(playerPos->x, playerPos->y, 0xFF); // get entire metatile
    u32 environment = blockinfo_get_field(metatile, 0x4); // background byte
    u16 metatileBehavior = MapGridGetMetatileBehaviorAt(playerPos->x, playerPos->y);
    u8 index = get_wild_data_index_for_map();
    u32 baseEncounterRate = 0;

    // don't encounter on first step into a new type of tile
    if (gPreviousPlayerMetatileBehaviour != metatileBehavior){
        gPreviousPlayerMetatileBehaviour = metatileBehavior;
        return false;
    }
    gPreviousPlayerMetatileBehaviour = metatileBehavior;
    // don't encounter if currently immune to wild battles
    if (environment != 1 && environment != 2) {
        return false;
    } else if (gWildEncounterImmunitySteps < 4) {
        gWildEncounterImmunitySteps = gWildEncounterImmunitySteps + 1;\
        return false;
    }
    // calculate base encounter rate
    if (environment == 1) {
        // grass
        if (gWildMonHeaders[index].grass_encounter) {
            baseEncounterRate = gWildMonHeaders[index].grass_encounter->encounter_chance;
        } else {
            return false;
        }
    } else if (environment == 2) {
        // water
        if (gWildMonHeaders[index].water_encounter) {
            baseEncounterRate = gWildMonHeaders[index].water_encounter->encounter_chance;
        } else {
            return false;
        }
    }
    // modify base encounter rate
    baseEncounterRate = baseEncounterRate << 5;
    if (gPlayerAvatar.flags & 0x6) // biking probably
        baseEncounterRate = (baseEncounterRate * 80) / 100;
    gStepUpdatedFirstPokemonItemPlayer = pokemon_getattr(party_player, REQUEST_HELD_ITEM, NULL);
    if (gStepUpdatedFirstPokemonItemPlayer == ITEM_CLEANSETAG)
        baseEncounterRate = baseEncounterRate / 3;

    if (!pokemon_getattr(party_player, REQUEST_SANITY_X6, NULL)) {
        u16 species = pokemon_getattr(party_player, REQUEST_SPECIES, NULL);
        u8 monAbility = get_ability(species, pokemon_getattr(party_player, REQUEST_ABILITY_BIT, NULL));
        switch (monAbility) {
            case ABILITY_STENCH:
            case ABILITY_WHITE_SMOKE:
            case ABILITY_SAND_VEIL:
            case ABILITY_QUICK_FEET:
                baseEncounterRate /= 2;
                break;
            case ABILITY_ILLUMINATE:
            case ABILITY_ARENA_TRAP:
            case ABILITY_NO_GUARD:
                baseEncounterRate *= 2;
                break;
        };
    }
    dprintf("base encounter rate is %d\n", baseEncounterRate);
    if (baseEncounterRate > 2880)
        baseEncounterRate = 2880;
    if (DoWildEncounterRateDiceRoll(baseEncounterRate)) {
        if (GenerateWildPokemon(environment, index)) {
            // setup the battle
            StartWildBattleNormal();
            return true;
        }
    }
    return false;
}
