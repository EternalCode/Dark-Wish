#include <pokeagb/pokeagb.h>
#include "../pokemon.h"

u8 SpeciesGetIndexAbility(u16 species, u8 abilityIndex) {
    u8 ability = 0;
    //struct PokemonBaseStatNew* bst = (struct PokemonBaseStatNew*)&;
    switch (abilityIndex) {
        case 0:
            {
            // first
            ability = gBaseStats[species].ability1;
            break;
            }
        case 1:
            {
            // second
            ability = gBaseStats[species].ability2;
            break;
            }
        default:
            {
            // hidden
            ability = gBaseStats[species].hidden_ability;
            break;
            }
    };
    return ability;
}
