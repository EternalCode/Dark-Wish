#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"

const pchar appUDexName[] = _("UltraDex");
const pchar appUDexDesc[] = _("Select an Application.");

const pchar appPokeLogName[] = _("Pokélog");
const pchar appPokeLogDesc[] = _("A logging app to keep track of your\nPokémon capturing feats.");

const pchar appDexnavName[] = _("Dexnav");
const pchar appDexnavDesc[] = _("Train and use this app to search for\nPokémon in the area.");

const pchar appWorldMapName[] = _("PokeMaps");
const pchar appWorldMapDesc[] = _("A GPS application containing a Region map.");

const pchar appPokepediaName[] = _("Poképedia");
const pchar appPokepediaDesc[] = _("The Pokémon encyclopedia.\nLearn about things Pokémon like stats and moves.");


struct DexApplication DexApps[] = {
    {
        .appName = appUDexName,
        .appDescription = appUDexDesc,
        .appCB = NULL,
    },
    {
        .appName = appPokeLogName,
        .appDescription = appPokeLogDesc,
        .appCB = NULL,
    },
    {
        .appName = appDexnavName,
        .appDescription = appDexnavDesc,
        .appCB = NULL,
    },
    {
        .appName = appPokepediaName,
        .appDescription = appPokepediaDesc,
        .appCB = NULL,
    },
    {
        .appName = appWorldMapName,
        .appDescription = appWorldMapDesc,
        .appCB = NULL,
    },

};
