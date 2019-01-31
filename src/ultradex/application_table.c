#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"

const pchar appUDexName[] = _("UltraDex");
const pchar appUDexDesc[] = _("Select an Application.");

const pchar appPokeLogName[] = _("Pokélog");
const pchar appPokeLogDesc[] = _("A logging app to keep track of your\nPokémon capturing progress.");

const pchar appDexnavName[] = _("Dexnav");
const pchar appDexnavDesc[] = _("Train and use this app to search for\nPokémon in the area.");

const pchar appWorldMapName[] = _("PokeMaps");
const pchar appWorldMapDesc[] = _("A GPS application containing\nthe Region map.");

const pchar appPokepediaName[] = _("Poképedia");
const pchar appPokepediaDesc[] = _("The Pokémon encyclopedia.\nLearn about discovered Pokémon.");

const pchar appPokecallName[] = _("PokéCall");
const pchar appPokecallDesc[] = _("Speak with your friends through\nthe PokéNetwork.");

const pchar appClockName[] = _("Clock");
const pchar appClockDesc[] = _("Check the current time in KANTO+1");

const pchar appMartName[] = _("Web-Mart");
const pchar appMartDesc[] = _("An online Mart Shopping tool.\nSpeedy delivery by Dragonite!");

const pchar appWeatherName[] = _("Weather Net");
const pchar appWeatherDesc[] = _("Get early weather warnings and\nnotifications of Pokémon Hazards");


struct DexApplication DexApps[] = {
    {
        .appName = appUDexName,
        .appDescription = appUDexDesc,
        .appCB = NULL,
        .xNameShift = 0,
    },
    {
        .appName = appPokeLogName,
        .appDescription = appPokeLogDesc,
        .appCB = NULL,
        .xNameShift = 10,
    },
    {
        .appName = appDexnavName,
        .appDescription = appDexnavDesc,
        .appCB = NULL,
        .xNameShift = 12,
    },
    {
        .appName = appPokepediaName,
        .appDescription = appPokepediaDesc,
        .appCB = NULL,
        .xNameShift = 2,
    },
    {
        .appName = appWorldMapName,
        .appDescription = appWorldMapDesc,
        .appCB = NULL,
        .xNameShift = 5,
    },
    {
        .appName = appPokecallName,
        .appDescription = appPokecallDesc,
        .appCB = NULL,
        .xNameShift = 5,
    },
    {
        .appName = appClockName,
        .appDescription = appClockDesc,
        .appCB = NULL,
        .xNameShift = 16,
    },
    {
        .appName = appMartName,
        .appDescription = appMartDesc,
        .appCB = NULL,
        .xNameShift = 8,
    },
    {
        .appName = appWeatherName,
        .appDescription = appWeatherDesc,
        .appCB = NULL,
        .xNameShift = 0,
    },

};
