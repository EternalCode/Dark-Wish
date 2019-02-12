#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"


/* Ultra Dex application */
const pchar appUDexName[] = _("UltraDex");
const pchar appUDexDesc[] = _("Select an Application.");
const pchar appUDexError[] = _("Application failed to load.");

void UDexAppCB()
{
    return;
}

bool UDexIsValid()
{
    return false;
}


/* Pokelog Application */
const pchar appPokeLogName[] = _("Pokélog");
const pchar appPokeLogDesc[] = _("A logging app to keep track of your\nPokémon capturing progress.");
const pchar appPokeLogError[] = _("Error: 0x0910C9B0\nPlease reinstall the application.");

void PokelogAppCB()
{
    return;
}

bool PokeLogIsValid()
{
    return false;
}

/* Dexnav Application */
const pchar appDexnavName[] = _("Dexnav");
const pchar appDexnavDesc[] = _("Train and use this app to search for\nPokémon in the area.");
const pchar appDexnavError[] = _("Application not up to date.\nCannot connect to Pokénet server.");

void DexnavAppCB()
{
    extern void DexnavGuiHandler(void);
    SetMainCallback(DexnavGuiHandler);
    gMain.state = 0;
}

bool DexnavIsValid()
{
    return true;
}

/* Pokepedia Application */
const pchar appPokepediaName[] = _("Poképedia");
const pchar appPokepediaDesc[] = _("The Pokémon encyclopedia.\nLearn about discovered Pokémon.");
const pchar appPokepediaError[] = _("Error: No result.\n“SELECT MissingNo FROM POKéMON”");

void PokepediaAppCB()
{
    return;
}

bool PokepediaIsValid()
{
    return false;
}

/* PokeMaps Application */
const pchar appWorldMapName[] = _("PokéMaps");
const pchar appWorldMapDesc[] = _("A GPS application containing\nthe Region map.");
const pchar appWorldMapError[] = _("No Signal.\nSatellite communication unestablished.");

void WorldMapAppCB()
{
    return;
}

bool WorldMapIsValid()
{
    return false;
}

/* Pokecall Application */
const pchar appPokecallName[] = _("PokéCall");
const pchar appPokecallDesc[] = _("Speak with your friends through\nthe PokéNetwork.");
const pchar appPokecallError[] = _("Error: No SIM\nPlease insert a SIM card.");

void PokecallAppCB()
{
    return;
}

bool PokecallIsValid()
{
    return false;
}

/* Clock App */
const pchar appClockName[] = _("Clock");
const pchar appClockDesc[] = _("Check the current time in KANTO+1");
const pchar appClockError[] = _("Error: Time is relative.");

void ClockAppCB()
{
    return;
}

bool ClockIsValid()
{
    return false;
}

const pchar appSettingsName[] = _("Settings");
const pchar appSettingsDesc[] = _("Adjust your Ultradex settings.");
const pchar appSettingsError[] = _("Error: Winrar is expired.");

void SettingsAppCB()
{
    return;
}

bool SettingsIsValid()
{
    return false;
}

/* Web-Mart Application */
const pchar appMartName[] = _("Web-Mart");
const pchar appMartDesc[] = _("An online Mart Shopping tool.\nSpeedy delivery by Dragonite!");
const pchar appMartError[] = _("You must register a Pokécard\nto use this application.");

void MartAppCB()
{
    return;
}

bool MartIsValid()
{
    return false;
}

/* Weather Application */
const pchar appWeatherName[] = _("Weather Net");
const pchar appWeatherDesc[] = _("Get early weather warnings and\nnotifications of Pokémon Hazards");
const pchar appWeatherError[] = _("Validation of authentication\ntoken in API request failed.");

void WeatherAppCB()
{
    return;
}

bool WeatherIsValid()
{
    return false;
}


struct DexApplication DexApps[] = {
    {
        .appName = appUDexName,
        .appDescription = appUDexDesc,
        .errorText = appUDexError,
        .appCB = UDexAppCB,
        .appValidityCB = UDexIsValid,
        .xNameShift = 0,
    },
    {
        .appName = appPokeLogName,
        .appDescription = appPokeLogDesc,
        .errorText = appPokeLogError,
        .appCB = PokelogAppCB,
        .appValidityCB = PokeLogIsValid,
        .xNameShift = 10,
    },
    {
        .appName = appDexnavName,
        .appDescription = appDexnavDesc,
        .errorText = appDexnavError,
        .appCB = DexnavAppCB,
        .appValidityCB = DexnavIsValid,
        .xNameShift = 12,
    },
    {
        .appName = appPokepediaName,
        .appDescription = appPokepediaDesc,
        .errorText = appPokepediaError,
        .appCB = PokepediaAppCB,
        .appValidityCB = PokepediaIsValid,
        .xNameShift = 2,
    },
    {
        .appName = appWorldMapName,
        .appDescription = appWorldMapDesc,
        .errorText = appWorldMapError,
        .appCB = WorldMapAppCB,
        .appValidityCB = WorldMapIsValid,
        .xNameShift = 5,
    },
    {
        .appName = appPokecallName,
        .appDescription = appPokecallDesc,
        .errorText = appPokecallError,
        .appCB = PokecallAppCB,
        .appValidityCB = PokecallIsValid,
        .xNameShift = 5,
    },
    {
        .appName = appSettingsName,
        .appDescription = appSettingsDesc,
        .errorText = appSettingsError,
        .appCB = SettingsAppCB,
        .appValidityCB = SettingsIsValid,
        .xNameShift = 8,
    },
    {
        .appName = appMartName,
        .appDescription = appMartDesc,
        .errorText = appMartError,
        .appCB = MartAppCB,
        .appValidityCB = MartIsValid,
        .xNameShift = 8,
    },
    {
        .appName = appWeatherName,
        .appDescription = appWeatherDesc,
        .errorText = appWeatherError,
        .appCB = WeatherAppCB,
        .appValidityCB = WeatherIsValid,
        .xNameShift = 0,
    },

};
