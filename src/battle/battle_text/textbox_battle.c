#include <pokeagb/pokeagb.h>
#include "stat_window.h"

extern void dprintf(const char * str, ...);

const struct TextboxTemplate BattleTextBoxes[] = {
    //TextboxTemplate <0, 2, 0xF, 0x1A, 4, 7, 0x90>
    {
        .bg_id = 0,
        .x = 0,
        .y = 0,
        .width = 0,
        .height = 0,
        .pal_id = 0,
        .charbase = 0,
    },
    //TextboxTemplate <0, 0x13, 2, 8, 2, 0, 0xB0>
    {
        .bg_id = 0,
        .x = 2,
        .y = 15,
        .width = 26,
        .height = 4,
        .pal_id = 7,
        .charbase = 90,
    },
    {
        // end
        .bg_id = 0xFF,
    },
};


void ShowBattleMessage2(pchar* str, u8 rboxid)
{
    rboxid_clear_pixels(rboxid, 0x11);
    AddTextPrinterParameterized(rboxid, 1, str, 1, 2, sav2_get_text_speed(), NULL);
    rboxid_update(rboxid, 3);
    rboxid_tilemap_update(rboxid);
}

void ShowStatBoostText(struct StatWindow* stats)
{

}
// {
//     /*item*/
//     .bg_id = 0,
//     .x = 20,
//     .y = 4,
//     .width = 9,
//     .height = 2,
//     .pal_id = 15,
//     .charbase = 31,
// },
// {
//     /*atk*/
//     .bg_id = 0,
//     .x = 6,
//     .y = 5,
//     .width = 3,
//     .height = 3,
//     .pal_id = 15,
//     .charbase = 61,
// },
// {
//     /*def*/
//     .bg_id = 0,
//     .x = 11,
//     .y = 5,
//     .width = 3,
//     .height = 3,
//     .pal_id = 15,
//     .charbase = 76,
// },
// {
//     /*spa*/
//     .bg_id = 0,
//     .x = 16,
//     .y = 5,
//     .width = 3,
//     .height = 3,
//     .pal_id = 15,
//     .charbase = 96,
// },
// {
//     /*spd*/
//     .bg_id = 0,
//     .x = 21,
//     .y = 5,
//     .width = 3,
//     .height = 3,
//     .pal_id = 15,
//     .charbase = 106,
// },
// {
//     /*spe*/
//     .bg_id = 0,
//     .x = 26,
//     .y = 5,
//     .width = 3,
//     .height = 3,
//     .pal_id = 15,
//     .charbase = 121,
// },
// {
//     /*moves*/
//     .bg_id = 0,
//     .x = 9,
//     .y = 9,
//     .width = 10,
//     .height = 8,
//     .pal_id = 15,
//     .charbase = 136,
// },
// {
//     /*power*/
//     .bg_id = 0,
//     .x = 20,
//     .y = 9,
//     .width = 2,
//     .height = 8,
//     .pal_id = 15,
//     .charbase = 220,
// },
// {
//     /*accuracy*/
//     .bg_id = 0,
//     .x = 22,
//     .y = 9,
//     .width = 3,
//     .height = 8,
//     .pal_id = 15,
//     .charbase = 265,
// },
// {
//     /*pp*/
//     .bg_id = 0,
//     .x = 25,
//     .y = 9,
//     .width = 2,
//     .height = 8,
//     .pal_id = 15,
//     .charbase = 310,
// },
// {
//     /*pkmn name*/
//     .bg_id = 0,
//     .x = 5,
//     .y = 0,
//     .width = 11,
//     .height = 2,
//     .pal_id = 15,
//     .charbase = 355,
// },
// {
//     /*lvl name*/
//     .bg_id = 0,
//     .x = 19,
//     .y = 0,
//     .width = 3,
//     .height = 2,
//     .pal_id = 15,
//     .charbase = 465,
// },
// {
//     /*hp ratio*/
//     .bg_id = 0,
//     .x = 22,
//     .y = 0,
//     .width = 6,
//     .height = 2,
//     .pal_id = 15,
//     .charbase = 496,
// },
