#include <pokeagb/pokeagb.h>
#include "dexnav_gui.h"
#include "../../ultradex.h"
#include "../HUD/dexnav_hud.h"
#include "../../../pokemon/pokemon.h"
#include "../../../battle/abilities/battle_abilities.h"
#include "../../../../generated/images/dexnav/dexnav_gui/dexnav_gui.h"
#include "../../../../generated/images/dexnav/dexnav_hud/dexnav_selection_cursor.h"


#define ICON_PAL_TAG 0xDAC0
#define ICON_GFX_TAG 0xD75A
#define dexnav_selection_cursor_TAG 0x200

static struct UltraDexState** UltraDexPtr = (struct UltraDexState**)(ULTRADEX_START);
static struct DexnavHudData** DNavState = (struct DexnavHudData**)(DEXNAV_START);
static u8* SearchLevels = (u8*)SEARCH_LEVEL_START;
extern void VblankSPQ(void);
extern void C2SyncAll(void);
extern void Setup(void);
extern u16 rand_range(u16 min, u16 max);

/* Entry point into dexnav + dexnav gui */
u8 exec_dexnav() {
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
    void DexnavGuiHandler(void);
    SetMainCallback(DexnavGuiHandler);
    gMain.state = 0;
    return true;
}

// gfx clean
void dexnav_gui_setup() {
    Setup();
    rboxes_free();
    bgid_mod_x_offset(0, 0, 0);
    bgid_mod_y_offset(0, 0, 0);
    bgid_mod_x_offset(1, 0, 0);
    bgid_mod_y_offset(1, 0, 0);
    gpu_tile_bg_drop_all_sets(0);
    bg_vram_setup(0, (struct BgConfig *)&bg_config_dexnav_gui, 4);
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
    HideBg(1);
    HideBg(0);
    SetMainCallback2(C2SyncAll);
    SetVBlankCallback(VblankSPQ);
}

void dexnav_load_pokemon_icons() {
    /* allocate all pallettes */
    for (u32 i = 0; i < 3; i++) {
        struct SpritePalette pal = {&pokeicon_pals[i], ICON_PAL_TAG + i};
        gpu_pal_obj_alloc_tag_and_apply(&pal);
    }

    for (u8 i = 0; i < 12; i++) {
        u16 species = (*DNavState)->grass_species[i];
        u32 pid = 0xFFFFFFFF;
        //if (species > 0) {
            void *icon_gfx = load_party_icon_tiles_with_form(species, pid, false);
            u16 gfx_tag = ICON_GFX_TAG + i;
            u16 pal_tag = ICON_PAL_TAG + pokeicon_pal_indices[species];
            struct CompressedSpriteSheet icon_tiles = {icon_gfx, 4 * 8 * 32, gfx_tag};
            gpu_tile_obj_alloc_tag_and_upload(&icon_tiles);
            struct Template icon_template = {
                                            .tiles_tag = gfx_tag,
                                            .pal_tag = pal_tag,
                                            .oam = &icon_oam,
                                            .animation = (const struct Frame (**)[])0x8231CF0,
                                            .graphics = &icon_tiles,
                                            .rotscale = (const struct RotscaleFrame (**)[])0x8231CFC,
                                            .callback = oac_nullsub,
                                            };
                                                                // x and y pos of sprite
            (*DNavState)->objids[i] = template_instanciate_forward_search(&icon_template, 20 + (24 * (i % 6)), 92 + (i > 5 ? 28 : 0), 0);
        //}
    }
    for (u8 i = 0; i < 5; i++) {
        u16 species = (*DNavState)->water_species[i];
        u32 pid = 0xFFFFFFFF;
        //if (species > 0) {
            void *icon_gfx = load_party_icon_tiles_with_form(species, pid, false);
            u16 gfx_tag = ICON_GFX_TAG + i + 12;
            u16 pal_tag = ICON_PAL_TAG + pokeicon_pal_indices[species];
            struct CompressedSpriteSheet icon_tiles = {icon_gfx, 4 * 8 * 32, gfx_tag};
            gpu_tile_obj_alloc_tag_and_upload(&icon_tiles);
            struct Template icon_template = {
                                            .tiles_tag = gfx_tag,
                                            .pal_tag = pal_tag,
                                            .oam = &icon_oam,
                                            .animation = (const struct Frame (**)[])0x8231CF0,
                                            .graphics = &icon_tiles,
                                            .rotscale = (const struct RotscaleFrame (**)[])0x8231CFC,
                                            .callback = oac_nullsub,
                                            };
                                                                // x and y pos of sprite
            (*DNavState)->objids[12 + i] = template_instanciate_forward_search(&icon_template, 30 + 24 * i, 48, 0);
        //}
    }
}



void update_cursor_position() {
    // update cursor position
    if ((*DNavState)->selected_arr) {
        // water
        gSprites[(*DNavState)->cursor_id].pos1.x = cursor_positions2[(*DNavState)->selected_index];
        gSprites[(*DNavState)->cursor_id].pos1.y = cursor_positions2[(*DNavState)->selected_index + 1];
    } else {
        // grass
        gSprites[(*DNavState)->cursor_id].pos1.x = cursor_positions1[(*DNavState)->selected_index];
        gSprites[(*DNavState)->cursor_id].pos1.y = cursor_positions1[(*DNavState)->selected_index + 1];
    }
}
void DnavSpawnPointerArrow() {
    struct CompressedSpriteSheet cursor_gfx = {(void*)dexnav_selection_cursorTiles, 32 * 32, dexnav_selection_cursor_TAG};
    struct SpritePalette cursor_pal = {(void*)dexnav_selection_cursorPal, dexnav_selection_cursor_TAG};
    struct Template cursor_temp = {dexnav_selection_cursor_TAG, dexnav_selection_cursor_TAG, &DnavCursorOAM,
                                    (const struct Frame (**)[])0x8231CF0, &cursor_gfx,
                                    (const struct RotscaleFrame (**)[])0x8231CFC, (SpriteCallback)oac_nullsub};

    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&cursor_gfx);
    gpu_pal_obj_alloc_tag_and_apply(&cursor_pal);
    (*DNavState)->cursor_id = template_instanciate_forward_search(&cursor_temp, 30, 48, 0);
    update_cursor_position();
}



const pchar no_info[] = _("--------");
const pchar resting_text[] = _("Choose a Pokémon");
const pchar invalid_pick_text[] = _("That Pokémon can’t be searched!");
const pchar select_locked_text[] = _("Pokémon searchable via Select!");
void dexnav_load_pnames(u8 status) {
    // clean boxes
    for (u32 i = 0; i < 5; ++i) {
        rboxid_clear_pixels(i, 0);
    }

    // rbox commit species name
    u16 species = (*DNavState)->selected_arr ? (*DNavState)->water_species[(*DNavState)->selected_index >> 1] : (*DNavState)->grass_species[(*DNavState)->selected_index>>1];
    if (species) {
        rboxid_print(0, 0, 0, 4, &textBlack, 0, gSpeciesNames[species]);
    } else {
        rboxid_print(0, 0, 0, 4, &textBlack, 0, &no_info[0]);
    }

    // rbox commit search level
    fmt_int_10(string_buffer, SearchLevels[species], 0, 4);
    rboxid_print(1, 0, 0, 4, &textBlack, 0, &string_buffer[0]);

    // rbox commit level bonus
    u8 search_level_bonus = 0;
    if ((SearchLevels[species] >> 2) > 20) {
        search_level_bonus = 20;
    } else {
        search_level_bonus = (SearchLevels[species] >> 2);
    }
    fmt_int_10(string_buffer, search_level_bonus, 0, 4);
    rboxid_print(2, 0, 0, 4, &textBlack, 0, &string_buffer[0]);

    // rbox commit hidden ability name
    if (gBaseStats[species].hidden_ability) {
        rboxid_print(3, 0, 0, 4, &textBlack, 0, ability_names[gBaseStats[species].hidden_ability]);
    } else {
        rboxid_print(3, 0, 0, 4, &textBlack, 0, &no_info[0]);
    }

    // rbox commit status message bar
    switch(status) {
        case 0:
            rboxid_print(4, 1, 0, 8, &textWhite, 0, &invalid_pick_text[0]);
            break;
        case 1:
            rboxid_print(4, 1, 0, 8, &textWhite, 0, &resting_text[0]);
            break;
        case 2:
            rboxid_print(4, 1, 0, 8, &textWhite, 0, &select_locked_text[0]);
    }
    // display committed gfx
    for (u8 i = 0; i < 5; i++) {
        rboxid_update(i, 3);
        rboxid_tilemap_update(i);
    }
}

void c1_dexnavOW() {
    extern void exec_dexnav_hud(void);
    exec_dexnav_hud();
}

void dexnav_gui_exit_search() {
    switch (gMain.state) {
        case 0:
            BeginNormalPaletteFade(~0, 0, 0x0, 0x10, 0);
            PlaySE(SOUND_PC_OPEN);
            gMain.state++;
            break;
        case 1:
            if (!gPaletteFade.active) {
                free((*DNavState)->backbuffer);
                gMain.state++;
            }
            break;
        case 2:
            m4aMPlayVolumeControl(&mplay_BGM, 0xFFFF, 256);
            SetMainCallback(c1_dexnavOW);
            SetMainCallback2(c2_return_overworld_music_scripts_cont);
            break;
        }
}

void dexnav_gui_exit_nosearch() {

    extern void C1UltraDexBoot(void);
    switch (gMain.state) {
        case 0:
            BeginNormalPaletteFade(~0, 0, 0x0, 0x10, 0);
            gMain.state++;
            break;
        case 1:
            if (!gPaletteFade.active) {
                rboxes_free();
                obj_free(&gSprites[(*DNavState)->cursor_id]);
                for (u8 i = 0; i < 17; i++) {
                    dprintf("freeing sprites with objid %d\n", (*DNavState)->objids[i]);
                    obj_free(&gSprites[(*DNavState)->objids[i]]);
                }
                free((*DNavState)->backbuffer);
                free((void*)*DNavState);
                gMain.state++;
            }
            break;
        case 2:
            VarSet(0x5000, 0x2);
            gUltraDex->currentOpenApp = 0;
            SetMainCallback(C1UltraDexBoot);
            gMain.state = 0;
            break;
        }
}


extern void dexnav_populate_encounter_list();

void DexnavGuiHandler() {
    switch(gMain.state) {
        case 0:
            if (!gPaletteFade.active) {
                dexnav_gui_setup();
                SetMainCallback(DexnavGuiHandler);
                // allocate dexnav struct
                *DNavState = (struct DexnavHudData*)malloc_and_clear(sizeof(struct DexnavHudData));
                gMain.state++;
            }
            break;
        case 1:
        {
                // load BG assets
                void *dexnav_gbackbuffer = malloc(0x800);
                (*DNavState)->backbuffer = dexnav_gbackbuffer;
                LoadPalette((void *)(&GenericTextPal), 15 * 16, 32);
                LoadPalette_compressed((void *)dexnav_guiPal, 0, 32);
                LZ77UnCompWram((void *)dexnav_guiMap, (void *)dexnav_gbackbuffer);
                lz77UnCompVram((void *)dexnav_guiTiles, (void *)0x06000000);
                bgid_set_tilemap(1, dexnav_gbackbuffer);
                bgid_mark_for_sync(1);
                bgid_mark_for_sync(0);
                gMain.state++;
        }
            break;
        case 2:
            rbox_init_from_templates(dexnavBoxes);
            dexnav_populate_encounter_list();
            dexnav_load_pnames(1);
            gMain.state++;
            break;
        case 3:
            REG_DISPCNT = 0x7F60;
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ, WIN_BG0 |
                            WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ);
            //WRITE_REG_BLDCNT(0x401E);
            REG_BLDCNT = BLDALPHA_BUILD(BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC, 0);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            ShowBg(0);
            ShowBg(1);
            dexnav_load_pokemon_icons();
            DnavSpawnPointerArrow();
            (*DNavState)->selected_arr = 0;
            (*DNavState)->selected_index = 0;
            gMain.state++;
            break;
        case 4:
            if (!gPaletteFade.active) {
                switch (gMain.newKeys & (KEY_A | KEY_B | KEY_DOWN | KEY_UP | KEY_LEFT | KEY_RIGHT | KEY_SELECT)) {
                    case KEY_A:
                        {
                        // check selection is valid. Play sound if invalid
                        u16 species = (*DNavState)->selected_arr ? (*DNavState)->water_species[(*DNavState)->selected_index >> 1] : (*DNavState)->grass_species[(*DNavState)->selected_index>>1];
                        // if species is MISSINGNO then error
                        if (species) {
                            // species was valid, save and enter OW HUD mode
                            var_8000 = species;
                            var_8001 = (*DNavState)->selected_arr;
                            SetMainCallback(dexnav_gui_exit_search);
                            gMain.state = 0;
                            return;
                        } else {
                            // beep and update
                            dexnav_load_pnames(0);
                            PlaySE(SOUND_RSE_BERRY_MIX_CLICK);
                        }
                        break;
                        }
                    case KEY_B:
                        // exit to start menu
                        SetMainCallback(dexnav_gui_exit_nosearch);
                        gMain.state = 0;
                        return;
                    case KEY_DOWN:
                    case KEY_UP:
                        (*DNavState)->selected_arr = !(*DNavState)->selected_arr;
                        (*DNavState)->selected_index = 0;
                        dexnav_load_pnames(1);
                        break;
                    case KEY_LEFT:
                        // wrap cursor around
                        if ((*DNavState)->selected_arr) {
                            (*DNavState)->selected_index = (*DNavState)->selected_index == 0 ? 4 * 2 : (*DNavState)->selected_index - 2;
                        } else {
                            (*DNavState)->selected_index = (*DNavState)->selected_index == 0 ? 11 * 2 : (*DNavState)->selected_index - 2;
                        }
                        dexnav_load_pnames(1);
                        break;
                    case KEY_RIGHT:
                        if ((*DNavState)->selected_arr) {
                            // don't go past index 4 in water
                            (*DNavState)->selected_index = (*DNavState)->selected_index == 4 * 2 ? 0 : (*DNavState)->selected_index + 2;
                        } else {
                            // don't go past index 11 in grass
                            (*DNavState)->selected_index = (*DNavState)->selected_index == 11 * 2 ? 0 : (*DNavState)->selected_index + 2;
                        }
                        dexnav_load_pnames(1);
                        break;
                    case KEY_SELECT:
                    {
                        // check selection is valid. Play sound if invalid
                        u16 species = (*DNavState)->selected_arr ? (*DNavState)->water_species[(*DNavState)->selected_index >> 1] : (*DNavState)->grass_species[(*DNavState)->selected_index>>1];
                        // if species is MISSINGNO then error
                        if (species) {
                            // species was valid
                            dexnav_load_pnames(2);
                            PlaySE(SOUND_PC_OPEN);
                            // create value to store in a var
                            u16 var_store = ((*DNavState)->selected_arr << 15) | species;
                            VarSet(DEXNAV_VAR, var_store);
                        } else {
                            // beep and update
                            dexnav_load_pnames(0);
                            PlaySE(SOUND_RSE_BERRY_MIX_CLICK);
                        }
                        break;
                    }
                    default:
                        return;
                };
                update_cursor_position();
                PlaySE(SOUND_GENERIC_CLINK);
            }
            break;
        default:
            break;
    };
}
