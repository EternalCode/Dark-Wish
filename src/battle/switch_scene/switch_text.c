#include <pokeagb/pokeagb.h>
#include "../battle_data/battle_state.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "switch_scene.h"

// no item string
const pchar str_no_item[] = _("None");
const pchar str_invalid_num[] = _("---");

// color for text
u16 switch_text_pal[] = {rgb5(255, 0, 255),   rgb5(248, 248, 248), rgb5(112, 112, 112), rgb5(96, 96, 96),
                                rgb5(208, 208, 208), rgb5(76, 154, 38),   rgb5(102, 194, 66),  rgb5(168, 75, 76),
                                rgb5(224, 114, 75),  rgb5(180, 124, 41),  rgb5(241, 188, 60),  rgb5(255, 0, 255),
                                rgb5(255, 0, 255),   rgb5(255, 0, 255),   rgb5(255, 133, 200),   rgb5(64, 200, 248)};

// Text color for nature highlighting
struct TextColor switch_color = {0, 3, 4};
struct TextColor switch_color_bg = {0, 1, 2};
struct TextColor switch_color_red = {0, 7, 8};
struct TextColor switch_color_green = {0, 5, 6};

// Texbox table for defined text on switch screen
struct TextboxTemplate switch_boxes[] = {
    {
        /*ability*/
        .bg_id = 0,
        .x = 8,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        /*item*/
        .bg_id = 0,
        .x = 20,
        .y = 4,
        .width = 9,
        .height = 2,
        .pal_id = 15,
        .charbase = 19,
    },
    {
        /*atk*/
        .bg_id = 0,
        .x = 6,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 37,
    },
    {
        /*def*/
        .bg_id = 0,
        .x = 11,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 46,
    },
    {
        /*spa*/
        .bg_id = 0,
        .x = 16,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 55,
    },
    {
        /*spd*/
        .bg_id = 0,
        .x = 21,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 64,
    },
    {
        /*spe*/
        .bg_id = 0,
        .x = 26,
        .y = 5,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 73,
    },
    {
        /*moves*/
        .bg_id = 0,
        .x = 9,
        .y = 9,
        .width = 10,
        .height = 8,
        .pal_id = 15,
        .charbase = 82,
    },
    {
        /*power*/
        .bg_id = 0,
        .x = 20,
        .y = 9,
        .width = 2,
        .height = 8,
        .pal_id = 15,
        .charbase = 162,
    },
    {
        /*accuracy*/
        .bg_id = 0,
        .x = 22,
        .y = 9,
        .width = 3,
        .height = 8,
        .pal_id = 15,
        .charbase = 178,
    },
    {
        /*pp*/
        .bg_id = 0,
        .x = 25,
        .y = 9,
        .width = 2,
        .height = 8,
        .pal_id = 15,
        .charbase = 202,
    },
    {
        /*pkmn name*/
        .bg_id = 0,
        .x = 5,
        .y = 0,
        .width = 11,
        .height = 2,
        .pal_id = 15,
        .charbase = 218,
    },
    {
        /*lvl name*/
        .bg_id = 0,
        .x = 19,
        .y = 0,
        .width = 3,
        .height = 2,
        .pal_id = 15,
        .charbase = 240,
    },
    {
        /*hp ratio*/
        .bg_id = 0,
        .x = 22,
        .y = 0,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 246,
    },
    {
        .bg_id = 0xFF, /* marks the end of the tb array */
    },

};
