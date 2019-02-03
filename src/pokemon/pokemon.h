#ifndef POKEMON_H_
#define POKEMON_H_

#include <pokeagb/pokeagb.h>
#include "pokemon_base_stats.h"
#include "pokebacks.h"
#include "pokefronts.h"

extern const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1];
extern const u16 *const gLevelUpLearnsets[SPECIES_MAX];

#endif /* POKEMON_H_ */
