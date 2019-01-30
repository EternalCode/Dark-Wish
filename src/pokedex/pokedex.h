#ifndef POKEDEX_H_
#define POKEDEX_H_

#include <pokeagb/pokeagb.h>

struct PokedexEntry {
    pchar categoryName[15];
    u16 height;
    u16 weight;
    pchar** desc;
};

struct DexMon {
    u16 species;
};

struct PokedexData {
    struct DexMon shownPokemon[6 * 3];
    u8 selectedSlot;
    void* dexBackBuffer;
};

extern const struct PokedexEntry gPokedexEntries[];

#endif /* POKEDEX_H_ */
