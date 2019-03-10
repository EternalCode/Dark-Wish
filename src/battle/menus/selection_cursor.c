#include <pokeagb/pokeagb.h>
#include "options.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"
#include "../../../generated/images/selection_cursor.h"
#include "../../../generated/images/move_selection_cursor.h"


extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];

const struct OamData cursor_oam = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 0, //8x8
                                .tile_num = 0,
                                .priority = 0, // above BG layers
                                .palette_num = 0,
                                .affine_param = 0
};

const struct OamData move_cursor_oam = {
                                .y = 0,
                                .affine_mode = 0,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 1,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 3, //64x32
                                .tile_num = 0,
                                .priority = 0, // above BG layers
                                .palette_num = 0,
                                .affine_param = 0
};


void update_cursor_action_select(u8 taskId)
{
    switch (gMain.newKeys & (KEY_DPAD | KEY_A)) {
        case KEY_LEFT:
            PlaySE(SOUND_GENERIC_CLINK);
            gBattleMaster->battle_cursor.cursor_pos += (!gBattleMaster->battle_cursor.cursor_pos) ? 3 : -1;
            break;
        case KEY_RIGHT:
            PlaySE(SOUND_GENERIC_CLINK);
            gBattleMaster->battle_cursor.cursor_pos += (gBattleMaster->battle_cursor.cursor_pos > 2) ? -3 : 1;
            break;
        case KEY_A:
            // pick selected move
            PlaySE(SOUND_GENERIC_CLINK);
            DestroyTask(taskId);
            gBattleMaster->selected_option = gBattleMaster->battle_cursor.cursor_pos;
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid]);
            gBattleAnimationStatus = 0;
            break;
        default:
            // up and down do nothing
            break;
    };
    gSprites[gBattleMaster->battle_cursor.objid].pos1.x = gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos];
    gSprites[gBattleMaster->battle_cursor.objid].pos1.y = gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos];
}

u8 move_count()
{
    u8 count = 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        if (gBattleMaster->type_objid[i] != 0x3F)
            count++;
    }
    return count;
}

void update_cursor_move_select(u8 taskId)
{
    u8 cursor_old =  gBattleMaster->battle_cursor.cursor_pos;
    switch (gMain.newKeys & (KEY_DPAD | KEY_A | KEY_B)) {
        case KEY_B:
        {
            // return to previous fight menu
            PlaySE(SOUND_GENERIC_CLINK);
            DestroyTask(taskId);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]]);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]]);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid]);
            gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 2;
            for (u8 i = 0; i < 4; i++) {
                if (gBattleMaster->type_objid[i] != 0x3F) {
                    gSprites[gBattleMaster->type_objid[i]].final_oam.affine_mode = 2;
                    gSprites[gBattleMaster->move_pss_objid[i]].final_oam.affine_mode = 2;
                    gSprites[gBattleMaster->move_pp_objid[i]].final_oam.affine_mode = 2;
                }
                gSprites[gBattleMaster->move_name_objid[i]].final_oam.affine_mode = 2;
            }
            gBattleAnimationStatus = 0;
            gMain.state = 0;
            return;
            break;
        }
        case KEY_A:
            // battle loop enter time
            // TODO Avoid moving left or right onto the mega symbol unless item pair and mega is valid
            PlaySE(SOUND_GENERIC_CLINK);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]]);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]]);
            obj_free(&gSprites[gBattleMaster->battle_cursor.objid]);
            for (u8 i = 0; i < 4; i++) {
                if (gBattleMaster->type_objid[i] != 0x3F) {
                    obj_free(&gSprites[gBattleMaster->type_objid[i]]);
                    obj_free(&gSprites[gBattleMaster->move_pss_objid[i]]);
                    obj_free(&gSprites[gBattleMaster->move_pp_objid[i]]);
                }
                obj_free(&gSprites[gBattleMaster->move_name_objid[i]]);
            }
            gBattleAnimationStatus = 0;
            DestroyTask(taskId);
            gMain.state = MoveSelectedExit;
            break;
        case KEY_LEFT:
            PlaySE(SOUND_GENERIC_CLINK);
            if (!gBattleMaster->battle_cursor.cursor_pos) {
                gBattleMaster->battle_cursor.cursor_pos = 4;
            } else if (gBattleMaster->battle_cursor.cursor_pos == 1) {
                gBattleMaster->battle_cursor.cursor_pos = 5;
            } else {
                gBattleMaster->battle_cursor.cursor_pos -= 2;
            }
            break;
        case KEY_RIGHT:
            PlaySE(SOUND_GENERIC_CLINK);
            if (gBattleMaster->battle_cursor.cursor_pos == 4) {
                gBattleMaster->battle_cursor.cursor_pos = 0;
            } else if (gBattleMaster->battle_cursor.cursor_pos == 5) {
                gBattleMaster->battle_cursor.cursor_pos = 1;
            } else {
                gBattleMaster->battle_cursor.cursor_pos += 2;
            }
            break;
        case KEY_DOWN:
        case KEY_UP:
            // avoid moving up and down on mega symbol
            PlaySE(SOUND_GENERIC_CLINK);
            if (gBattleMaster->battle_cursor.cursor_pos > 3)
                break;
            gBattleMaster->battle_cursor.cursor_pos += (gBattleMaster->battle_cursor.cursor_pos % 2) ? -1 : 1;
            break;
        default:
            break;
    };
    u8 available_moves = move_count();
    switch (available_moves) {
        case 1:
            if ((gBattleMaster->battle_cursor.cursor_pos) && (gBattleMaster->battle_cursor.cursor_pos < 4)) {
                gBattleMaster->battle_cursor.cursor_pos = cursor_old;
            }
            break;
        case 2:
            if ((gBattleMaster->battle_cursor.cursor_pos % 2) && (gBattleMaster->battle_cursor.cursor_pos < 4)) {
                gBattleMaster->battle_cursor.cursor_pos = cursor_old;
            }
            break;
        case 3:
            if (gBattleMaster->battle_cursor.cursor_pos == 3)
                gBattleMaster->battle_cursor.cursor_pos = cursor_old;
            break;
        default:
            break;
    };

    u8 i;
    for (i = 0; i < 4; i++) {
        u8 adjust = (gBattleMaster->battle_cursor.cursor_pos == 1) ? 2 : gBattleMaster->battle_cursor.cursor_pos;
        adjust = (gBattleMaster->battle_cursor.cursor_pos == 2) ? 1 : adjust;
        if (i == adjust) {
            gSprites[gBattleMaster->type_objid[i]].final_oam.affine_mode = 2;
            gSprites[gBattleMaster->move_pss_objid[i]].final_oam.affine_mode = 0;
            gSprites[gBattleMaster->move_pp_objid[i]].final_oam.affine_mode = 0;
        } else {
            gSprites[gBattleMaster->type_objid[i]].final_oam.affine_mode = 0;
            gSprites[gBattleMaster->move_pss_objid[i]].final_oam.affine_mode = 2;
            gSprites[gBattleMaster->move_pp_objid[i]].final_oam.affine_mode = 2;
        }
    }
    if (gBattleMaster->battle_cursor.cursor_pos > 3) {
        gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 0;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]].final_oam.affine_mode = 2;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]].final_oam.affine_mode = 2;
    } else {
        gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 2;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]].final_oam.affine_mode = 0;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]].final_oam.affine_mode = 0;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]].pos1.x = gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos];
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]].pos1.y = gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos];
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]].pos1.x = gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos] + 64;
        gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]].pos1.y = gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos];
    }

}

void spawn_pointer_arrow(u8 tag)
{
    struct CompressedSpriteSheet cursor_gfx = {(void*)selection_cursorTiles, 32, SELECTION_CURSOR_TAG + tag};
    struct SpritePalette cursor_pal = {(void*)selection_cursorPal, SELECTION_CURSOR_TAG + tag};
    struct Template cursor_temp = {SELECTION_CURSOR_TAG + tag, SELECTION_CURSOR_TAG + tag, &cursor_oam,
                                    nullframe, &cursor_gfx, nullrsf, (SpriteCallback)oac_nullsub};

    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&cursor_gfx);
    gpu_pal_obj_alloc_tag_and_apply(&cursor_pal);
    gBattleMaster->battle_cursor.objid = CreateSprite(
                                        &cursor_temp,
                                        gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos],
                                        gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos], 0
                                        );
}

void spawn_square_pointer(u8 tag)
{
    struct CompressedSpriteSheet move_cursor_gfx = {(void*)move_selection_cursorTiles, 2048, SELECTION_CURSOR_TAG + tag};
    struct SpritePalette move_cursor_pal = {(void*)move_selection_cursorPal, SELECTION_CURSOR_TAG + tag};
    struct Template move_cursor_temp = {SELECTION_CURSOR_TAG + tag, SELECTION_CURSOR_TAG + tag, &move_cursor_oam,
                                    nullframe, &move_cursor_gfx, nullrsf, (SpriteCallback)oac_nullsub};

    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&move_cursor_gfx);
    gpu_pal_obj_alloc_tag_and_apply(&move_cursor_pal);

    gBattleMaster->battle_cursor.objid_mv_crsr[0] = CreateSprite(
                                        &move_cursor_temp,
                                        gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos],
                                        gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos], 0
                                        );
    gBattleMaster->battle_cursor.objid_mv_crsr[1] = CreateSprite(
                                                &move_cursor_temp,
                                                gBattleMaster->battle_cursor.cursor_x[gBattleMaster->battle_cursor.cursor_pos] + 64,
                                                gBattleMaster->battle_cursor.cursor_y[gBattleMaster->battle_cursor.cursor_pos], 0
                                                );
    gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]].final_oam.tile_num += 32;
}

void show_move_data(void)
{

    gBattleMaster->battle_cursor.cursor_x[0] = 39;
    gBattleMaster->battle_cursor.cursor_x[1] = 39;
    gBattleMaster->battle_cursor.cursor_x[2] = 141;
    gBattleMaster->battle_cursor.cursor_x[3] = 141;
    gBattleMaster->battle_cursor.cursor_x[4] = 216;
    gBattleMaster->battle_cursor.cursor_x[5] = 216;

    gBattleMaster->battle_cursor.cursor_y[0] = 132;
    gBattleMaster->battle_cursor.cursor_y[1] = 151;
    gBattleMaster->battle_cursor.cursor_y[2] = 132;
    gBattleMaster->battle_cursor.cursor_y[3] = 151;
    gBattleMaster->battle_cursor.cursor_y[4] = 136;
    gBattleMaster->battle_cursor.cursor_y[5] = 136;
    gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 0;

    u8 i;
    for (i = 0; i < 4; i++) {
        if (gBattleMaster->type_objid[i] != 0x3F)
            gSprites[gBattleMaster->type_objid[i]].final_oam.affine_mode = 0;
        gSprites[gBattleMaster->move_name_objid[i]].final_oam.affine_mode = 0;
    }

    spawn_square_pointer(5);
    spawn_pointer_arrow(10);
    gSprites[gBattleMaster->battle_cursor.objid].pos1.x = gBattleMaster->battle_cursor.cursor_x[4];
    gSprites[gBattleMaster->battle_cursor.objid].pos1.y = gBattleMaster->battle_cursor.cursor_y[4];
    gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 2; // hide
}

void init_selection_cursor(u8 mode, u8 bank)
{
    gBattleMaster->battle_cursor.cursor_pos = 0;
    if (mode) {
        // mode is action selection
        gBattleMaster->battle_cursor.cursor_x[0] = 15;
        gBattleMaster->battle_cursor.cursor_x[1] = 75;
        gBattleMaster->battle_cursor.cursor_x[2] = 148;
        gBattleMaster->battle_cursor.cursor_x[3] = 198;

        gBattleMaster->battle_cursor.cursor_y[0] = 136;
        gBattleMaster->battle_cursor.cursor_y[1] = 136;
        gBattleMaster->battle_cursor.cursor_y[2] = 136;
        gBattleMaster->battle_cursor.cursor_y[3] = 136;
        CreateTask(update_cursor_action_select, 1);
        spawn_pointer_arrow(0);

    } else {
        // mode is move selection
        gBattleMaster->battle_cursor.cursor_x[0] = 39;
        gBattleMaster->battle_cursor.cursor_x[1] = 39;
        gBattleMaster->battle_cursor.cursor_x[2] = 141;
        gBattleMaster->battle_cursor.cursor_x[3] = 141;
        gBattleMaster->battle_cursor.cursor_x[4] = 216;
        gBattleMaster->battle_cursor.cursor_x[5] = 216;

        gBattleMaster->battle_cursor.cursor_y[0] = 132;
        gBattleMaster->battle_cursor.cursor_y[1] = 151;
        gBattleMaster->battle_cursor.cursor_y[2] = 132;
        gBattleMaster->battle_cursor.cursor_y[3] = 151;
        gBattleMaster->battle_cursor.cursor_y[4] = 136;
        gBattleMaster->battle_cursor.cursor_y[5] = 136;
        u8 taskId = CreateTask(update_cursor_move_select, 1);
        tasks[taskId].priv[0] = bank;

        spawn_square_pointer(5);
        spawn_pointer_arrow(10);
        gSprites[gBattleMaster->battle_cursor.objid].pos1.x = gBattleMaster->battle_cursor.cursor_x[4];
        gSprites[gBattleMaster->battle_cursor.objid].pos1.y = gBattleMaster->battle_cursor.cursor_y[4];
        gSprites[gBattleMaster->battle_cursor.objid].final_oam.affine_mode = 2; // hide
        gBattleMaster->fight_menu_content_spawned = 1;
    }
    return;
}


void free_unused_objs()
{
    if (gBattleMaster->battle_cursor.objid_mv_crsr[0] != 0x3F) {
        obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[0]]);
        obj_free(&gSprites[gBattleMaster->battle_cursor.objid_mv_crsr[1]]);
        gBattleMaster->battle_cursor.objid_mv_crsr[0] = 0x3F;
        gBattleMaster->battle_cursor.objid_mv_crsr[1] = 0x3F;
    }
    for (u8 i = 0; i < 4; i++) {
        if (gBattleMaster->type_objid[i] != 0x3F) {
            obj_free(&gSprites[gBattleMaster->type_objid[i]]);
            obj_free(&gSprites[gBattleMaster->move_pss_objid[i]]);
            obj_free(&gSprites[gBattleMaster->move_pp_objid[i]]);
            gBattleMaster->type_objid[i] = 0x3F;
            gBattleMaster->move_pss_objid[i] = 0x3F;
            gBattleMaster->move_pp_objid[i] = 0x3F;
        }
        if (gBattleMaster->move_name_objid[i] != 0x3F) {
            obj_free(&gSprites[gBattleMaster->move_name_objid[i]]);
            gBattleMaster->move_name_objid[i] = 0x3F;
        }
    }
}
