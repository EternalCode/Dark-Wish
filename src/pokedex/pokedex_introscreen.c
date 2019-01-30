#include <pokeagb/pokeagb.h>
#include "pokedex.h"
#include "../global.h"
#include "../saveblock_expansion/save.h"
#include "../dexnav/GUI/dexnav_gui.h"
#include "../../generated/images/pokedex_selection_screen.h"

static struct PokedexData** gPokedexData = (struct PokedexData**)(POKEDEX_START);
extern void VblankSPQ(void);
extern void C2DexnavGui(void);
extern void Setup(void);

/* GUI Rboxes */
const u16 dexTextPal[] = {rgb5(255, 0, 255),   rgb5(248, 248, 248), rgb5(112, 112, 112), rgb5(96, 96, 96),
                                rgb5(208, 208, 208), rgb5(76, 154, 38),   rgb5(102, 194, 66),  rgb5(168, 75, 76),
                                rgb5(224, 114, 75),  rgb5(180, 124, 41),  rgb5(241, 188, 60),  rgb5(255, 0, 255),
                                rgb5(255, 0, 255),   rgb5(255, 0, 255),   rgb5(255, 133, 200),   rgb5(64, 200, 248)};
struct TextColor dexTextBlack = {0, 3, 4};
struct TextColor dexTextWhite = {0, 1, 2};
struct TextColor dexTextRed = {0, 7, 8};
struct TextColor dexTextGreen = {0, 5, 6};


struct TextboxTemplate dexTextBoxes[] = {
    {
        /* Number */
        .bg_id = 0,
        .x = 1,
        .y = 0,
        .width = 4,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        /* Flavor text */
        .bg_id = 0,
        .x = 6,
        .y = 0,
        .width = 15,
        .height = 2,
        .pal_id = 15,
        .charbase = 31,
    },
    {
        /*Species Name */
        .bg_id = 0,
        .x = 23,
        .y = 0,
        .width = 3,
        .height = 3,
        .pal_id = 15,
        .charbase = 76,
    },
    {
        /* Seen */
        .bg_id = 0,
        .x = 19,
        .y = 18,
        .width = 12,
        .height = 3,
        .pal_id = 15,
        .charbase = 96,
    },
    {
        /* Owned */
        .bg_id = 0,
        .x = 27,
        .y = 18,
        .width = 22,
        .height = 3,
        .pal_id = 15,
        .charbase = 121,
    },
    {
        .bg_id = 0xFF, /* marks the end of the tb array */
    },

};



const pchar dexNoinfo[] = _("--------");
const pchar noNum[] = _("---");
const pchar numberString[] = _("No.");
const pchar nZero[] = _("0");
const pchar strPKMN[] = _("Pokémon");
const pchar strSpace[] = _(" ");
void dexUpdateText()
{
    u16 species = (*gPokedexData)->shownPokemon[(*gPokedexData)->selectedSlot].species;
    // clean boxes
    for (u32 i = 0; i < 5; ++i) {
        rboxid_clear_pixels(i, 0);
    }

    // number string
    pstrcpy(string_buffer, numberString);
    if (species) {
        if (species < 10) {
            // pad 2 zeros
            pstrcat(string_buffer, nZero);
            pstrcat(string_buffer, nZero);
        } else if (species < 100) {
            // pad 1 zero
            pstrcat(string_buffer, nZero);
        }
        pchar tempStr[4];
        fmt_int_10(&tempStr[0], species, 0, 4);
        pstrcat(string_buffer, &tempStr[0]);
    } else {
        pstrcat(string_buffer, noNum);
    }
    rboxid_print(0, 0, 0, 0, &dexTextWhite, 0, string_buffer);

    // flavor text
    pstrcpy(string_buffer, gPokedexEntries[species].categoryName);
    pstrcat(string_buffer, strSpace);
    pstrcat(string_buffer, strPKMN);
    rboxid_print(1, 0, 0, 0, &dexTextWhite, 0, &string_buffer[0]);

    // species name
    if (species) {
        rboxid_print(2, 1, 0, 0, &dexTextWhite, 0, pokemon_names[species]);
    } else {
        rboxid_print(2, 1, 0, 0, &dexTextWhite, 0, &dexNoinfo[0]);
    }

    // rbox commit seen
    fmt_int_10(string_buffer, 13, 0, 4);
    rboxid_print(3, 0, 4, 2, &dexTextWhite, 0, &string_buffer[0]);

    // rbox commit owned
    fmt_int_10(string_buffer, 28, 0, 4);
    rboxid_print(4, 0, 5, 2, &dexTextWhite, 0, &string_buffer[0]);


    // display committed gfx
    for (u8 i = 0; i < 5; i++) {
        rboxid_update(i, 3);
        rboxid_tilemap_update(i);
    }
}

//extern u16 rand_range(u16 min, u16 max);

// initialize shown pokemon
void shownPokemonInitialize(u16 speciesStart)
{
    for (u8 i = 0 + speciesStart; i < 3 + speciesStart; i++) {
        for (u8 j = 0; j < 6; j++) {
            u16 species = (i * 6) + j + 1;
            (*gPokedexData)->shownPokemon[species - 1].species = species;
            // load OAM for species
        }
    }
}


u8 ExecPokedex()
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
    void PokedexIntroScreenSetup(void);
    SetMainCallback(PokedexIntroScreenSetup);
    gMain.state = 0;
    return true;
}

// Setup pokedex intro screen gfx
void PokedexIntroScreenSetup()
{
    switch(gMain.state) {
        case 0:
        {
            if (!gPaletteFade.active) {
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
                gpu_sync_bg_hide(3);
                gpu_sync_bg_hide(2);
                gpu_sync_bg_hide(1);
                gpu_sync_bg_hide(0);
                SetMainCallback2(C2DexnavGui);
                SetVBlankCallback(VblankSPQ);
                *gPokedexData = (struct PokedexData*)malloc_and_clear(sizeof(struct PokedexData));
                SetMainCallback(PokedexIntroScreenSetup);
                // enable Hblank interrupt
                // interrupts_enable(2);
                // SetHBlankCallback((MainCallback)pokepad_hblank_handler);
                gMain.state++;
            }
            break;
        }
        case 1:
        {
            // load BG assets
            void *dexBackBuffer = malloc(0x800);
            (*gPokedexData)->dexBackBuffer = dexBackBuffer;
            gpu_pal_apply((void *)(&dexTextPal), 15 * 16, 32);
            gpu_pal_apply_compressed((void *)pokedex_selection_screenPal, 0, 32);
            LZ77UnCompWram((void *)pokedex_selection_screenMap, (void *)dexBackBuffer);
            lz77UnCompVram((void *)pokedex_selection_screenTiles, (void *)0x06000000);
            bgid_set_tilemap(1, dexBackBuffer);
            bgid_mark_for_sync(1);
            bgid_mark_for_sync(0);
            gMain.state++;
            break;
        }
        case 2:
            rbox_init_from_templates(dexTextBoxes);
            dexUpdateText();
            gMain.state++;
            break;
        case 3:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            gpu_sync_bg_show(0);
            gpu_sync_bg_show(1);
            gMain.state++;
            break;
        default:
            break;
    };

}
