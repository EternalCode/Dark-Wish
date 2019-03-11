#include <pokeagb/pokeagb.h>
#include "stat_window.h"
#include "../../pokemon/pokemon.h"

extern void dprintf(const char * str, ...);

const struct TextboxTemplate BattleTextBoxes[] = {
    // unused
    {
        .bg_id = 0,
        .x = 0,
        .y = 0,
        .width = 0,
        .height = 0,
        .pal_id = 0,
        .charbase = 0,
    },
    // Main battle dialog textbox. <0, 0x13, 2, 8, 2, 0, 0xB0>
    {
        .bg_id = 0,
        .x = 2,
        .y = 15,
        .width = 26,
        .height = 4,
        .pal_id = 7,
        .charbase = 90,
    },
    // Species name
    {
        .bg_id = 0,
        .x = 22,
        .y = 8,
        .width = 7,
        .height = 2,
        .pal_id = 5,
        .charbase = 196,
    },
    // Level
    {
        .bg_id = 0,
        .x = 22,
        .y = 10,
        .width = 6,
        .height = 2,
        .pal_id = 5,
        .charbase = 320,
    },
    // HP
    {
        .bg_id = 0,
        .x = 7,
        .y = 13,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 332,
    },
    // Attack
    {
        .bg_id = 0,
        .x = 7,
        .y = 15,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 340,
    },
    // Defense
    {
        .bg_id = 0,
        .x = 7,
        .y = 17,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 348,
    },
    // Special Attack
    {
        .bg_id = 0,
        .x = 22,
        .y = 13,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 356,
    },
    // Special Defense
    {
        .bg_id = 0,
        .x = 22,
        .y = 15,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 364,
    },
    // Speed
    {
        .bg_id = 0,
        .x = 22,
        .y = 17,
        .width = 4,
        .height = 2,
        .pal_id = 5,
        .charbase = 372,
    },
    {
        // end
        .bg_id = 0xFF,
    },
};

//rboxid_print(SWB_NAME, 0, 0, 4, &switch_color_bg, 0, &SWM_LOG->s_pkmn_data[index].nickname[0]);



void ShowBattleMessage2(pchar* str, u8 rboxid)
{
    rboxid_clear_pixels(rboxid, 0x11);
    AddTextPrinterParameterized(rboxid, 1, str, 1, 2, sav2_get_text_speed(), NULL);
    rboxid_update(rboxid, 3);
    rboxid_tilemap_update(rboxid);
}

extern void GetSpeciesName(u8 *name, u16 species);
extern u8 SpawnPokemonObj(u16 species, u32 pid, s16 x, s16 y, u16 tag);
extern void str_int_padding(u8 number, u8 digits);
extern u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
void ShowStatBoostText(struct StatWindow* stats)
{
    // prefix and suffixes
    pchar level[] = _("{LV}. ");
    pchar plusSign[] = _("+");
    pchar genderM[] = _("{COLOR 15}{SHADOW 2}♂");
    pchar genderF[] = _("{COLOR 14}{SHADOW 2}♀");
    // colors
    struct TextColor nameColor = {3, 10, 2};
    struct TextColor levelColor = {9, 10, 2};
    struct TextColor StatColor = {10, 3, 11};
    // data needed
    u16 species = pokemon_getattr(&party_player[stats->slot], REQUEST_SPECIES, NULL);
    u32 pid = pokemon_getattr(&party_player[stats->slot], REQUEST_PID, NULL);
    pchar numberBuffer[6];
    // clear pixels
    rboxid_clear_pixels(2, 0x33);
    rboxid_clear_pixels(3, 0x99);
    for (u8 i = 4; i < 10; i++)
        rboxid_clear_pixels(i, 0xAA);
    // name
    pokemon_getattr(&party_player[stats->slot], REQUEST_NICK, string_buffer);
    u8 gender = GetGenderFromSpeciesAndPersonality(species, pid);
    switch (gender) {
        case MON_MALE:
            pstrcat(string_buffer, genderM);
            break;
        case MON_FEMALE:
            pstrcat(string_buffer, genderF);
            break;
        default:
            break;
    }
    rboxid_print(2, 0, 6, 0, &nameColor, 0, string_buffer);
    // level
    pstrcpy(string_buffer, level);
    fmt_int_10(&numberBuffer[0], stats->levelNew, 0, 4);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(3, 0, 6, 0, &levelColor, 0, string_buffer);
    // pokemon icon
    stats->iconId = SpawnPokemonObj(species, pid, 160, 76, 0x393);
    // Total HP
    str_int_padding(stats->totalHPNew - stats->totalHP, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(4, 1, 6, 2, &StatColor, 0, string_buffer);
    // Attack
    str_int_padding(stats->attackNew - stats->attack, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(5, 1, 6, 1, &StatColor, 0, string_buffer);
    // Defense
    str_int_padding(stats->defenseNew - stats->defense, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(6, 1, 6, 1, &StatColor, 0, string_buffer);
    // Special Attack
    str_int_padding(stats->spattackNew - stats->spattack, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(7, 1, 6, 2, &StatColor, 0, string_buffer);
    // Special Defense
    str_int_padding(stats->spdefenseNew - stats->spdefense, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(8, 1, 6, 1, &StatColor, 0, string_buffer);
    // Speed
    str_int_padding(stats->speedNew - stats->speed, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(9, 1, 6, 1, &StatColor, 0, string_buffer);
    // update
    for (u8 i = 2; i < 10; i++) {
        rboxid_update_tilemap_and_tileset(i);
    }
}

void ShowStatBoostTextComplete(struct StatWindow* stats)
{
    pchar plusSign[] = _(" ");
    // colors
    struct TextColor StatColor = {10, 3, 11};
    // data needed
    // u16 species = pokemon_getattr(&party_player[stats->slot], REQUEST_SPECIES, NULL);
    // u32 pid = pokemon_getattr(&party_player[stats->slot], REQUEST_PID, NULL);
    pchar numberBuffer[6];
    // clear pixels
    for (u8 i = 4; i < 10; i++)
        rboxid_clear_pixels(i, 0xAA);
    // Total HP
    str_int_padding(stats->totalHPNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(4, 1, 6, 2, &StatColor, 0, string_buffer);
    // Attack
    str_int_padding(stats->attackNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(5, 1, 6, 1, &StatColor, 0, string_buffer);
    // Defense
    str_int_padding(stats->defenseNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(6, 1, 6, 1, &StatColor, 0, string_buffer);
    // Special Attack
    str_int_padding(stats->spattackNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(7, 1, 6, 2, &StatColor, 0, string_buffer);
    // Special Defense
    str_int_padding(stats->spdefenseNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(8, 1, 6, 1, &StatColor, 0, string_buffer);
    // Speed
    str_int_padding(stats->speedNew, 3);
    pstrcpy(numberBuffer, string_buffer);
    pstrcpy(string_buffer, plusSign);
    pstrcat(string_buffer, numberBuffer);
    rboxid_print(9, 1, 6, 1, &StatColor, 0, string_buffer);
    // update
    for (u8 i = 4; i < 10; i++) {
        rboxid_update_tilemap_and_tileset(i);
    }
}
