#include <pokeagb/pokeagb.h>
#include "switch_scene.h"
#include "../battle_data/battle_state.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../abilities/battle_abilities.h"
#include "../../pokemon/pokemon.h"

// images
#include "../../../generated/images/switch/slider_bot.h"
#include "../../../generated/images/switch/slider_mid.h"
#include "../../../generated/images/switch/slider_top.h"
#include "../../../generated/images/PSS_icons1.h"
#include "../../../generated/images/battle_terrains/grass/grass_bg.h"
#include "../../../generated/images/switch/switch_bg.h"
#include "../../../generated/images/type_icons.h"
#include "../../../generated/images/hpbox/hpbar_pieces_switch.h"
#include "../../../generated/images/switch/shift_menu.h"
#include "../../../generated/images/switch/shift_cursor.h"

extern u8 PokemonGetAbility(struct Pokemon *p);
extern const struct BgConfig bg_config_data[4];
extern void CpuFastSet(void* src, void* dst, u32 mode);
extern void return_to_battle(void);
extern void ResetTextBoxes(void);
extern void refresh_hp(struct Pokemon* pkmn, u8 objid, u8 mode, u8 bank, u8* tiles);
extern u8 hpbar_build_transparent(struct Pokemon* pkmn, s16 x, s16 y, u16 tag);
extern void status_switch_menu(u8 objid, u8 ailment);
extern bool bank_trapped(u8 bank);

extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];


const struct BgConfig bg_config_switch_data[4] = {
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 2,
        .palette = 0,
        .size = 0,
        .map_base = 29,
        .character_base = 1,
        .bgid = 0,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 3,
        .palette = 0,
        .size = 0,
        .map_base = 28,
        .character_base = 0,
        .bgid = 1,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 3,
        .palette = 0,
        .size = 0,
        .map_base = 30,
        .character_base = 2,
        .bgid = 2,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 3,
        .palette = 0,
        .size = 1,
        .map_base = 31,
        .character_base = 3,
        .bgid = 3,
    },
};

void str_int_padding(u8 number, u8 digits)
{
    /* 3 digit max support */
    u8 space = digits;
    u8 prefix[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    fmt_int_10(string_buffer, number, 0, 4);

    // faster than div or log...
    if (number < 10) {
        space -= 1;
    } else if (number < 100) {
        space -= 2;
    } else if (number >= 100) {
        space -= 3;
    }
    for (u32 i = 0; i < space; i++) {
        prefix[i] = 0;
    }
    pstrcat((pchar*)prefix, string_buffer);
    pstrcpy(string_buffer, prefix);
}

void switch_fetch_all_data()
{
    /* Log data into struct for every Pokemon in player's party */
    struct switch_data* sd = (struct switch_data*)malloc_and_clear(sizeof(struct switch_data));
    SWM_LOG = sd;
    sd->list_count = count_pokemon();
    u8 id = hpbar_build_transparent(&party_player[0], 184, 32, 0x58A8);
    OBJID_HIDE(id);
    SWM_LOG->hpbar_id = id;

    for (u32 i = 0; i < sd->list_count; i++) {
        // log current HP and misc data
        sd->s_pkmn_data[i].ability = PokemonGetAbility(&party_player[i]);
        sd->s_pkmn_data[i].item = pokemon_getattr(&party_player[i], REQUEST_HELD_ITEM, NULL);
        sd->s_pkmn_data[i].species = pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL);
        sd->s_pkmn_data[i].PID = pokemon_getattr(&party_player[i], REQUEST_PID, NULL);

        /* Get effect from raw status ailment */
        u32 status = pokemon_getattr(&party_player[i], REQUEST_STATUS_AILMENT, NULL);
        u8 ailment = 0;
        if ((status & 7) > 0) {
            ailment = EFFECT_SLEEP;
        } else if (status & (1 << 3))
            ailment = EFFECT_POISON;
        else if (status & (1 << 4))
            ailment = EFFECT_BURN;
        else if (status & (1 << 5))
            ailment = EFFECT_FREEZE;
        else if (status & (1 << 6))
            ailment = EFFECT_PARALYZE;
        else if (status & (1 << 7))
            ailment = EFFECT_BAD_POISON;
        else
            ailment = EFFECT_NONE;
        sd->s_pkmn_data[i].ailment_effect = ailment;
        pokemon_getattr(&party_player[i], REQUEST_NICK, (pchar*)&sd->s_pkmn_data[i].nickname[0]);
        pchar gender_m[] = _("{COLOR 15}{SHADOW 2}♂");
        pchar gender_f[] = _("{COLOR 14}{SHADOW 2}♀");
        pchar level[] = _("{LV}");
        pchar slash[] = _("/");
        /* Append gender symbol to string */
        switch (pokemon_get_gender(&party_player[i])) {
            case 0:
                // male
                pstrcat((pchar*)&sd->s_pkmn_data[i].nickname[0], gender_m);
                break;
            case 0xFE:
                // female
                pstrcat((pchar*)&sd->s_pkmn_data[i].nickname[0], gender_f);
                break;
            case 0xFF:
                // none
                break;
        };
        str_int_padding(pokemon_getattr(&party_player[i], REQUEST_CURRENT_HP, NULL), 3);
        pstrcat(string_buffer, slash);
        pstrcpy((pchar*)&sd->s_pkmn_data[i].health[0], string_buffer);


        str_int_padding(pokemon_getattr(&party_player[i], REQUEST_TOTAL_HP, NULL), 3);
        pstrcat((pchar*)&sd->s_pkmn_data[i].health[0], string_buffer);

        fmt_int_10((pchar*)&sd->s_pkmn_data[i].level[0], pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL), 0, 4);
        pstrcpy(string_buffer, level);
        pstrcat(string_buffer, (pchar*)&sd->s_pkmn_data[i].level[0]);
        pstrcpy((pchar*)&sd->s_pkmn_data[i].level[0], string_buffer);

        for (u32 j = 0; j < 5; j++) {
            // in get_attr, speed comes after Def. Here we want it as the last member
            if (j == 2) {
                sd->s_pkmn_data[i].stats[4] = pokemon_getattr(&party_player[i], REQUEST_ATK + j, NULL);
                sd->s_pkmn_data[i].nature_boosted[4] = STAT_COLOR(j, &party_player[i]);
            } else if (j == 4) {
                sd->s_pkmn_data[i].stats[2] = pokemon_getattr(&party_player[i], REQUEST_ATK + j, NULL);
                sd->s_pkmn_data[i].nature_boosted[2] = STAT_COLOR(j, &party_player[i]);
            } else {
                sd->s_pkmn_data[i].stats[j] = pokemon_getattr(&party_player[i], REQUEST_ATK + j, NULL);
                sd->s_pkmn_data[i].nature_boosted[j] = STAT_COLOR(j, &party_player[i]);
            }
        }
        // log moves and remaining PP counts
        for (u32 j = 0; j < 4; j++) {
            sd->s_pkmn_data[i].move[j] = pokemon_getattr(&party_player[i], REQUEST_MOVE1 + j, NULL);
            sd->s_pkmn_data[i].pp[j] = pokemon_getattr(&party_player[i], REQUEST_PP1 + j, NULL);
        }
    }
}


void switch_setup()
{
    SetVBlankCallback(VblankSPQ);
    SetMainCallback2(C2SyncAll);

    bgid_mod_x_offset(0, 0, 0);
    bgid_mod_y_offset(0, 0, 0);
    bgid_mod_x_offset(1, 0, 0);
    bgid_mod_y_offset(1, 0, 0);
    gpu_tile_bg_drop_all_sets(0);
    bg_vram_setup(0, (struct BgConfig *)&bg_config_switch_data, 4);
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));

    /* Hide all the gSprites on screen */
    for (u8 i = 0; i < BANK_MAX; i++) {
        //  pokemon OAMs
        if (gPkmnBank[i]->objid < 0x3F)
            OBJID_HIDE(gPkmnBank[i]->objid);
        // hide HP box OAMs
        for (u8 j = 0; j < 4; j++) {
            if (gPkmnBank[i]->objid_hpbox[j] < 0x3F)
                OBJID_HIDE(gPkmnBank[i]->objid_hpbox[j]);
        }
    }
    HideBg(1);
    HideBg(0);
}

void switch_load_background()
{
    /* load menu */
    void *sw_bgbackbuffer = malloc(0x800);
    gBattleMaster->switch_main.back_buffer = sw_bgbackbuffer;
    gpu_pal_apply_compressed((void *)switch_bgPal, 0, 32);
    gpu_pal_apply((void *)(&switch_text_pal), 15 * 16, 32);
    LZ77UnCompWram((void *)switch_bgMap, (void *)sw_bgbackbuffer);
    lz77UnCompVram((void *)switch_bgTiles, (void *)0x06000000);
    bgid_set_tilemap(1, sw_bgbackbuffer);
    bgid_mark_for_sync(1);
    bgid_mark_for_sync(0);
}

void switch_type_update_icon(u8 objid, enum PokemonType type)
{
    void *vram = (void *)((0x06010000) + gSprites[objid].final_oam.tile_num * 32);
    dprintf("loading icon for type %d\n", type);
    CpuFastSet((void*)((type * 256) + type_iconsTiles), vram, CPUModeFS(256, CPUFSCPY));
}

void switch_category_update_icon(u8 objid, u8 category)
{
    void *vram = (void *)((0x06010000) + gSprites[objid].final_oam.tile_num * 32);
    CpuFastSet((void*)((category * 128) + PSS_icons1Tiles), vram, CPUModeFS(128, CPUFSCPY));
}

void switch_type_icon_load(u8 type, s16 x, s16 y, u8 id)
{
    if (gBattleMaster->switch_main.type_objid[id] != 0x3F) {
        switch_type_update_icon(gBattleMaster->switch_main.type_objid[id], type);
    } else {
        gBattleMaster->switch_main.type_objid[id] = load_dmg_type_icon(type, x, y, id + 4);
    }
    OBJID_SHOW(gBattleMaster->switch_main.type_objid[id]);
}

void switch_cat_icon_load(u8 category, s16 x, s16 y, u8 id)
{
    u8 array_idx = id + 6;
    if (gBattleMaster->switch_main.type_objid[array_idx] != 0x3F) {
        switch_category_update_icon(gBattleMaster->switch_main.type_objid[array_idx], category);
    } else {
        gBattleMaster->switch_main.type_objid[array_idx] = load_small_dmg_category_icon(category, x, y, id + 4);
        gSprites[gBattleMaster->switch_main.type_objid[array_idx]].final_oam.priority = 2;
    }
    OBJID_SHOW(gBattleMaster->switch_main.type_objid[array_idx]);
}

void icon_frame_change(struct Sprite* spr)
{
    if (spr->data[0] == 20) {
        spr->final_oam.tile_num += 16;
        spr->data[0]++;
    } else if (spr->data[0] == 40) {
        spr->final_oam.tile_num -= 16;
        spr->data[0] = 0;
    }
    spr->data[0]++;
}


void switch_load_pokemon_icons() {
    /* allocate all pallettes */
    for (u32 i = 0; i < 3; i++) {
        struct SpritePalette pal = {&pokeicon_pals[i], ICON_PAL_TAG + i};
        gpu_pal_obj_alloc_tag_and_apply(&pal);
    }

    for (u32 i = 0; i < SWM_LOG->list_count; i++) {
        u16 species = SWM_LOG->s_pkmn_data[i].species;
        u32 pid = SWM_LOG->s_pkmn_data[i].PID;
        if (species > 0) {
            void *icon_gfx = load_party_icon_tiles_with_form(species, pid, false);
            u16 gfx_tag = ICON_GFX_TAG + i;
            u16 pal_tag = ICON_PAL_TAG + pokeicon_pal_indices[species];
            struct CompressedSpriteSheet icon_tiles = {icon_gfx, 4 * 8 * 32, gfx_tag};
            gpu_tile_obj_alloc_tag_and_upload(&icon_tiles);
            struct Template icon_template = {
                                            .tiles_tag = gfx_tag,
                                            .pal_tag = pal_tag,
                                            .oam = &icon_oam,
                                            .animation = nullframe,
                                            .graphics = &icon_tiles,
                                            .rotscale = ((i != 0) ? switch_scale_table : switch_scale_table_full),
                                            .callback = ((i != 0) ? oac_nullsub : icon_frame_change),
                                            };
            if (i == 0) {
                gBattleMaster->switch_main.icon_objid[i] = template_instanciate_forward_search(&icon_template, 16, 10, 0);
            } else if (i == 5) {
                gBattleMaster->switch_main.icon_objid[i] = template_instanciate_forward_search(&icon_template, 16, 10 + 23 * i, 0);
            } else {
                gBattleMaster->switch_main.icon_objid[i] = template_instanciate_forward_search(&icon_template, 16, 10 + 24 * i, 0);
            }
        }
    }
}


void switch_load_scroll_box()
{
    struct SpritePalette scroll_pal = {(void *)slider_topPal, SLIDER_PAL_TAG};
    struct CompressedSpriteSheet top_gfx = {(void *)slider_topTiles, 512, SLIDER_GFX_TAG};
    struct CompressedSpriteSheet mid_gfx = {(void *)slider_midTiles, 512, SLIDER_GFX_TAG + 1};
    struct CompressedSpriteSheet bot_gfx = {(void *)slider_botTiles, 512, SLIDER_GFX_TAG + 2};

    struct Template top_template = {SLIDER_GFX_TAG, SLIDER_PAL_TAG, &slider_oam, nullframe, &top_gfx, nullrsf, oac_nullsub};
    struct Template mid_template = {SLIDER_GFX_TAG + 1, SLIDER_PAL_TAG, &slider_oam, nullframe, &mid_gfx, nullrsf, oac_nullsub};
    struct Template bot_template = {SLIDER_GFX_TAG + 2, SLIDER_PAL_TAG, &slider_oam, nullframe, &bot_gfx, nullrsf, oac_nullsub};
    gpu_pal_decompress_alloc_tag_and_upload(&scroll_pal);
    gpu_tile_obj_decompress_alloc_tag_and_upload(&top_gfx);
    gpu_tile_obj_decompress_alloc_tag_and_upload(&mid_gfx);
    gpu_tile_obj_decompress_alloc_tag_and_upload(&bot_gfx);
    gBattleMaster->switch_main.slider_objid[0] = template_instanciate_forward_search(&top_template, 17, 17, 1);
    gBattleMaster->switch_main.slider_objid[1] = template_instanciate_forward_search(&mid_template, 17, 40, 1);
    gBattleMaster->switch_main.slider_objid[2] = template_instanciate_forward_search(&bot_template, 17, 128, 1);
    gSprites[gBattleMaster->switch_main.slider_objid[0]].final_oam.affine_mode = 0;
    gSprites[gBattleMaster->switch_main.slider_objid[1]].final_oam.affine_mode = 0;
    gSprites[gBattleMaster->switch_main.slider_objid[2]].final_oam.affine_mode = 0;
    OBJID_HIDE(gBattleMaster->switch_main.slider_objid[1]);
    OBJID_HIDE(gBattleMaster->switch_main.slider_objid[2]);
}


void switch_load_pokemon_data(u8 index)
{
    REG_DISPCNT = 0x7260;
    for (u32 i = SWB_ABILITY; i <= SWB_MAX; ++i) {
        rboxid_clear_pixels(i, 0);
    }

    rboxid_print(SWB_NAME, 0, 0, 4, &switch_color_bg, 0, &SWM_LOG->s_pkmn_data[index].nickname[0]);
    rboxid_print(SWB_LVL, 0, 1, 4, &switch_color_bg, 0, &SWM_LOG->s_pkmn_data[index].level[0]);
    rboxid_print(SWB_HP, 0, 1, 4, &switch_color_bg, 0, &SWM_LOG->s_pkmn_data[index].health[0]);

    /* print the stats */
    str_int_padding(SWM_LOG->s_pkmn_data[index].stats[0], 3);
    rboxid_print(SWB_ATK, 0, 1, 7, SWM_LOG->s_pkmn_data[index].nature_boosted[0], 0, &string_buffer[0]);

    str_int_padding(SWM_LOG->s_pkmn_data[index].stats[1], 3);
    rboxid_print(SWB_DEF, 0, 2, 7, SWM_LOG->s_pkmn_data[index].nature_boosted[1], 0, &string_buffer[0]);

    str_int_padding(SWM_LOG->s_pkmn_data[index].stats[2], 3);
    rboxid_print(SWB_SPA, 0, 3, 7, SWM_LOG->s_pkmn_data[index].nature_boosted[2], 0, &string_buffer[0]);

    str_int_padding(SWM_LOG->s_pkmn_data[index].stats[3], 3);
    rboxid_print(SWB_SPD, 0, 4, 7, SWM_LOG->s_pkmn_data[index].nature_boosted[3], 0, &string_buffer[0]);

    str_int_padding(SWM_LOG->s_pkmn_data[index].stats[4], 3);
    rboxid_print(SWB_SPE, 0, 5, 7, SWM_LOG->s_pkmn_data[index].nature_boosted[4], 0, &string_buffer[0]);

    /* print the ability */

    rboxid_print(SWB_ABILITY, 0, 3, 1, &switch_color, 0, &ability_names[SWM_LOG->s_pkmn_data[index].ability][0]);

    /* print the item */
//    u8 item = SWM_LOG->s_pkmn_data[index].item;
    //if (item == 0) {
        rboxid_print(SWB_ITEM, 0, 1, 1, &switch_color, 0, &str_no_item[0]);
//    } else {
        /* TODO Use item table */
        //rboxid_print(SWB_ITEM, 0, 1, 1, &switch_color, 0, &items[item].name[0]);
//    }

    for (u32 i = 0; i < 4; ++i) {
        u16 move = SWM_LOG->s_pkmn_data[index].move[i];
        if (move == 0) {
            if (gBattleMaster->switch_main.type_objid[i + 2] != 0x3F) {
                OBJID_HIDE(gBattleMaster->switch_main.type_objid[i + 2]);
            }
            if (gBattleMaster->switch_main.type_objid[i + 6] != 0x3F) {
                OBJID_HIDE(gBattleMaster->switch_main.type_objid[i + 6]);
            }
            continue;
        }
        rboxid_print(SWB_MOVES, 0, 0, (4 + 14 * i), &switch_color, 0, &gBattleMoves[move].name[0]);

        if (gBattleMoves[move].base_power)
            str_int_padding(gBattleMoves[move].base_power, 3);
        else
            memcpy(string_buffer, str_invalid_num, 4);
        rboxid_print(SWB_POW, 0, 1, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);

        if (gBattleMoves[move].accuracy > 100)
            memcpy(string_buffer, str_invalid_num, 4);
        else
            str_int_padding(gBattleMoves[move].accuracy, 3);
        rboxid_print(SWB_ACC, 0, 5, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);

        str_int_padding(SWM_LOG->s_pkmn_data[index].pp[i], 2);
        rboxid_print(SWB_PP, 0, 2, (4 + 14 * i), &switch_color, 0, &string_buffer[0]);


        /*the move type icon*/
        switch_type_icon_load(gBattleMoves[move].type, 49, 84 + (14 * i), i + 2);
        switch_cat_icon_load(gBattleMoves[move].category, 226, 84 + (14 * i), i);
    }

    for (u32 i = SWB_ATK; i <= SWB_MAX; ++i) {
        rboxid_update(i, 3);
        rboxid_tilemap_update(i);
    }
    /* write those again, to overwrite empty space from stats */
    rboxid_update(SWB_ABILITY, 3);
    rboxid_tilemap_update(SWB_ABILITY);
    rboxid_update(SWB_ITEM, 3);
    rboxid_tilemap_update(SWB_ITEM);
    REG_DISPCNT = 0x7360;

    /* load the type icons */
    u16 species = SWM_LOG->s_pkmn_data[index].species;
    if ((enum PokemonType)(gBaseStats[species].type1) != TYPE_NONE) {
        switch_type_icon_load(gBaseStats[species].type1, 47, 25, 0);
    }
    if (((enum PokemonType)(gBaseStats[species].type2) != TYPE_NONE) &&
        (gBaseStats[species].type1 != gBaseStats[species].type2)) {
        switch_type_icon_load(gBaseStats[species].type2, 83, 25, 1);
    } else if (gBattleMaster->switch_main.type_objid[1] != 0x3F) {
        OBJID_HIDE(gBattleMaster->switch_main.type_objid[1]);
    }

    /* reload HP bar */
    status_switch_menu(SWM_LOG->hpbar_id, SWM_LOG->s_pkmn_data[index].ailment_effect);
    refresh_hp(&party_player[index], SWM_LOG->hpbar_id, 0, 0, (u8*)hpbar_pieces_switchTiles);

}

void switch_obj_hide_all()
{
    for (u8 i = 0; i < 10; i++) {
        if (gBattleMaster->switch_main.type_objid[i] != 0x3F)
            OBJID_HIDE(gBattleMaster->switch_main.type_objid[i]);
        if (i < SWM_LOG->list_count)
            OBJID_HIDE(gBattleMaster->switch_main.icon_objid[i]);
        if (i < 1)
            OBJID_HIDE(gBattleMaster->switch_main.slider_objid[0]);
    }
    OBJID_HIDE(SWM_LOG->hpbar_id);
}

void switch_obj_show_all()
{
    for (u8 i = 0; i < 10; i++) {
        if (gBattleMaster->switch_main.type_objid[i] != 0x3F)
            OBJID_SHOW(gBattleMaster->switch_main.type_objid[i]);
        if (i < SWM_LOG->list_count) {
            OBJID_SHOW(gBattleMaster->switch_main.icon_objid[i]);
            gSprites[gBattleMaster->switch_main.icon_objid[i]].final_oam.affine_mode = 1;
        }
        if (i < 1)
            OBJID_SHOW(gBattleMaster->switch_main.slider_objid[0]);
    }
    OBJID_SHOW(SWM_LOG->hpbar_id);
}


void switch_update_graphical(u8 cursor_position)
{
    // update size of icons based on cursor position
    for (u8 i = 0; i < SWM_LOG->list_count; i++) {
        if (i != cursor_position) {
            gSprites[gBattleMaster->switch_main.icon_objid[i]].rotscale_table = switch_scale_table;
            gSprites[gBattleMaster->switch_main.icon_objid[i]].callback = oac_nullsub;
            obj_rotscale_play(&gSprites[gBattleMaster->switch_main.icon_objid[i]], 0);
        } else {
            gSprites[gBattleMaster->switch_main.icon_objid[i]].rotscale_table = switch_scale_table_full;
            gSprites[gBattleMaster->switch_main.icon_objid[i]].callback = icon_frame_change;
            obj_rotscale_play(&gSprites[gBattleMaster->switch_main.icon_objid[i]], 0);
        }
    }

    // hide unused cursor icon baed on cursor position
    switch (cursor_position) {
        case 0:
            OBJID_HIDE(gBattleMaster->switch_main.slider_objid[2]);
            OBJID_HIDE(gBattleMaster->switch_main.slider_objid[1]);
            OBJID_SHOW(gBattleMaster->switch_main.slider_objid[0]);
            break;
        case 1:
            gSprites[gBattleMaster->switch_main.slider_objid[1]].pos1.y = Y_POS_MID_ONE;
            break;
        case 2:
            gSprites[gBattleMaster->switch_main.slider_objid[1]].pos1.y = Y_POS_MID_TWO;
            break;
        case 3:
            gSprites[gBattleMaster->switch_main.slider_objid[1]].pos1.y = Y_POS_MID_THREE;
            break;
        case 4:
            gSprites[gBattleMaster->switch_main.slider_objid[1]].pos1.y = Y_POS_MID_FOUR;
            break;
        case 5:
            OBJID_HIDE(gBattleMaster->switch_main.slider_objid[0]);
            OBJID_HIDE(gBattleMaster->switch_main.slider_objid[1]);
            OBJID_SHOW(gBattleMaster->switch_main.slider_objid[2]);
            break;
    };
    if ((cursor_position < 5) && (cursor_position > 0)) {
        OBJID_HIDE(gBattleMaster->switch_main.slider_objid[0]);
        OBJID_SHOW(gBattleMaster->switch_main.slider_objid[1]);
        OBJID_HIDE(gBattleMaster->switch_main.slider_objid[2]);
    }
    // display information of cursor index pokemon
    switch_load_pokemon_data(cursor_position);
}

void switch_scene_main()
{
    void spawn_confirm_box(void);
    void confirm_box(void);
    u8 prev;
    switch (gMain.state) {
    case 0:
        if (!gPaletteFade.active) {
            /* VRAM Setup */
            rboxes_free();
            switch_setup();
            switch_fetch_all_data();
            rotscale_reset();
            gMain.state++;
        }
        break;
    case 1:
        switch_load_background();
        rbox_init_from_templates(switch_boxes);
        switch_load_pokemon_data(0);
        switch_load_pokemon_icons();
        switch_load_scroll_box();
        switch_obj_hide_all();
        gMain.state++;
        break;
    case 2:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
        ShowBg(1);
        ShowBg(0);
        switch_obj_show_all();
        gMain.state++;
        break;
    case 3:
        prev = gBattleMaster->switch_main.position;
        if (!gPaletteFade.active) {
            switch (gMain.newKeys & (KEY_A | KEY_B | KEY_DOWN | KEY_UP)) {
            case KEY_A:
                /* Choose
                 * You only ever get to the switch menu and press A when you need to select a Pokemon.
                 * Need to display the confirmation text. Skipped for now TODO
                 */

                 spawn_confirm_box();
                 SetMainCallback(confirm_box);
                 // BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
                 // if (gBattleMaster->switch_main.reason == ViewPokemon)
                 //    gBattleMaster->switch_main.reason = NormalSwitch;
                 // gMain.state = 5;
                break;
            case KEY_B:
                /* Exit the switch menu, unless you are forced to make a switch option */
                BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
                gBattleMaster->switch_main.reason = ViewPokemon;
                gMain.state = 5;
                break;
            case KEY_DOWN:
                if (gBattleMaster->switch_main.position < (SWM_LOG->list_count-1))
                    gBattleMaster->switch_main.position++;
                else
                    gBattleMaster->switch_main.position = 0;
                if (prev == gBattleMaster->switch_main.position) return;
                switch_update_graphical(gBattleMaster->switch_main.position);
                break;
            case KEY_UP:
                if (gBattleMaster->switch_main.position > 0)
                    gBattleMaster->switch_main.position--;
                else
                    gBattleMaster->switch_main.position = SWM_LOG->list_count - 1;
                if (prev == gBattleMaster->switch_main.position) return;
                switch_update_graphical(gBattleMaster->switch_main.position);
                break;
            default:
                break;
            }
        }
        break;
    case 4:
        // unused...
        break;
    case 5:
        if (!gPaletteFade.active) {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
        }
        gMain.state++;
        break;
    case 6:
        // free everything
        ResetTextBoxes();
        free(gBattleMaster->switch_main.sd);
        free(gBattleMaster->switch_main.back_buffer);
        for (u8 i = 0; i < 10; ++i) {
            if (gBattleMaster->switch_main.type_objid[i] != 0x3F) {
                obj_free(&gSprites[(gBattleMaster->switch_main.type_objid[i])]);
                gBattleMaster->switch_main.type_objid[i] = 0x3F;
            }
            if ((i < SWM_LOG->list_count) && (gBattleMaster->switch_main.icon_objid[i] < 0x3F)) {
                obj_free(&gSprites[(gBattleMaster->switch_main.icon_objid[i])]);
                gBattleMaster->switch_main.icon_objid[i] = 0x3F;
            }
            if ((i < 3) && (gBattleMaster->switch_main.slider_objid[i] < 0x3F)) {
                obj_free(&gSprites[(gBattleMaster->switch_main.slider_objid[i])]);
                gBattleMaster->switch_main.slider_objid[i] = 0x3F;
            }
        }
        obj_free(&gSprites[SWM_LOG->hpbar_id]);
        gMain.state++;
        break;
    case 7:
        // return to battle
        gpu_tile_bg_drop_all_sets(0);
        SetMainCallback(return_to_battle);
        gMain.state = 0;
        return;
    };
}


void spawn_confirm_box()
{
    /* Box Object */
    u16 gfx_tag = CONFIRM_BOX_TAG;
    u16 pal_tag = CONFIRM_BOX_TAG;
    struct CompressedSpriteSheet menu_tiles = {shift_menuTiles, 8 * 8 * 32, gfx_tag};
    struct SpritePalette menu_pal = {(void *)shift_menuPal, pal_tag};
    gpu_tile_obj_decompress_alloc_tag_and_upload(&menu_tiles);
    gpu_pal_decompress_alloc_tag_and_upload(&menu_pal);
    struct Template confirm_template = {
                                    .tiles_tag = gfx_tag,
                                    .pal_tag = pal_tag,
                                    .oam = &confirm_box_oam,
                                    .animation = nullframe,
                                    .graphics = &menu_tiles,
                                    .rotscale = nullrsf,
                                    .callback = oac_nullsub,
                                    };
    gBattleMaster->switch_main.switch_confirm_box_id = template_instanciate_forward_search(&confirm_template, 208, 120, 0);

    /* Box cursor */
    gfx_tag = CONFIRM_BOX_TAG + 1;
    struct CompressedSpriteSheet cursor_tiles = {shift_cursorTiles, 2 * 2 * 32, gfx_tag};
    gpu_tile_obj_alloc_tag_and_upload(&cursor_tiles);
    struct Template cursor_template = {
                                    .tiles_tag = gfx_tag,
                                    .pal_tag = pal_tag,
                                    .oam = &cursor_confirm_oam,
                                    .animation = nullframe,
                                    .graphics = &cursor_tiles,
                                    .rotscale = nullrsf,
                                    .callback = oac_nullsub,
                                    };
    gBattleMaster->switch_main.switch_confirm_cursor_id = template_instanciate_forward_search(&cursor_template, 188, CURSOR_SHIFT_POS , 0);
}


void free_confirmation_box()
{
    obj_free(&gSprites[gBattleMaster->switch_main.switch_confirm_cursor_id]);
    obj_free(&gSprites[gBattleMaster->switch_main.switch_confirm_box_id]);
}

bool slot_is_fainted(u8 slot)
{
    return (pokemon_getattr(&party_player[slot], REQUEST_CURRENT_HP, NULL) < 1);
}

bool slot_in_battle(u8 slot)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (SIDE_OF(i)) continue; // skip opponent banks
        if ((gPkmnBank[i]->battleData.slot == slot) && (ACTIVE_BANK(i))) {
            return true;
        }
    }
    return false;
}

bool slot_is_trapped(u8 slot)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (SIDE_OF(i)) continue; // skip opponent banks
        if ((gPkmnBank[i]->battleData.slot == slot) && ACTIVE_BANK(i))
            return bank_trapped(i);
    }
    return false;
}

void confirm_box()
{
    u8 objid, slot;
    switch (gMain.newKeys & (KEY_A | KEY_B | KEY_DOWN | KEY_UP)) {
        case KEY_A:
            // if cursor on cancel button, free confirm box and go back to main switch
            slot = gBattleMaster->switch_main.position;
            objid = gBattleMaster->switch_main.switch_confirm_cursor_id;
            if ((gSprites[objid].pos1.y == CURSOR_CANCEL_POS) || (slot_is_fainted(slot)) || (slot_is_trapped(slot)) || (slot_in_battle(slot))) {
                gMain.state = 3;
                SetMainCallback(switch_scene_main);
                free_confirmation_box();
                return;
            }
            // validate chosen pokemon validitity TODO
            // exit to battle
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
            if (gBattleMaster->switch_main.reason == ViewPokemon)
               gBattleMaster->switch_main.reason = NormalSwitch;
            gMain.state = 5;
            SetMainCallback(switch_scene_main);
            free_confirmation_box();
            break;
        case KEY_B:
            free_confirmation_box();
            gMain.state = 3;
            SetMainCallback(switch_scene_main);
            break;
        case KEY_UP:
        case KEY_DOWN:
            objid = gBattleMaster->switch_main.switch_confirm_cursor_id;
            if (gSprites[objid].pos1.y == CURSOR_SHIFT_POS)
                gSprites[objid].pos1.y = CURSOR_CANCEL_POS;
            else
                gSprites[objid].pos1.y = CURSOR_SHIFT_POS;
            break;
    };
}
