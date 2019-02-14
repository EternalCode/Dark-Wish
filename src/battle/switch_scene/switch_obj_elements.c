#include <pokeagb/pokeagb.h>

// icon_oam see src/ultradex/dexnav/gui/gui_gfx_templates.c

// the difference is that the slider doesn't have affine mode turned on
const struct OamData slider_oam = {
    .y = 0,
    .affine_mode = 0,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrix_num = 0,
    .size = 2, // 32x32 square
    .tile_num = 0,
    .priority = 2, /*above the rest*/
    .palette_num = 0,
    .affine_param = 0,
};

const struct OamData confirm_box_oam = {
    .y = 0,
    .affine_mode = 0,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrix_num = 0,
    .size = 3, // 64x64 square
    .tile_num = 0,
    .priority = 1, /*above the rest*/
    .palette_num = 0,
    .affine_param = 0,
};

const struct OamData cursor_confirm_oam = {
    .y = 0,
    .affine_mode = 0,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrix_num = 0,
    .size = 1, // 16x16 square
    .tile_num = 0,
    .priority = 0, /*above the rest*/
    .palette_num = 0,
    .affine_param = 0,
};

const struct RotscaleFrame switch_scale_down[] = {
    {-0xA0, 0xA0, 0, 0, 0},
    {0x7FFE, 0, 0, 0, 0},
};

const struct RotscaleFrame switch_scale_full[] = {
    {-0x100, 0x100, 0, 0, 0},
    {0x7FFE, 0, 0, 0, 0},
};


const struct RotscaleFrame *switch_scale_table[] = {
    switch_scale_down,
};

const struct RotscaleFrame *switch_scale_table_full[] = {
    switch_scale_full,
};
