#include <pokeagb/pokeagb.h>
#include "../ultradex.h"
#include "../../global.h"
#include "../../../generated/images/ultradex/settings_imgs/scroller.h"
//#include "../../../generated/images/ultradex/settings_imgs/bg.h"

extern void VblankSPQ(void);
extern void C2SyncAll(void);
extern void UltraDexSetup(void);
extern const struct BgConfig BGConfigUDex[4];
extern struct TextboxTemplate UDexSettingsTextTemplate[];
extern void UpdateAppHeaderText(void);
extern void BuildGradient(u16 startColor, u16 stopColor);
extern void BuildGradientPalette(void);
extern void BuildMosaic(void* charbase, void* mapbase);
extern void HBlankCBUltraDex(void);

static struct UltraDexState** UltraDexPtr = (struct UltraDexState**)(ULTRADEX_START);

struct TextboxTemplate UDexSettingsTextTemplate[] = {
    {
        /* Current open application in Top Left */
        .bg_id = 0,
        .x = 1,
        .y = 0,
        .width = 9,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        /* Time */
        .bg_id = 0,
        .x = 26,
        .y = 0,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 31,
    },
    {
        /* R1 */
        .bg_id = 0,
        .x = 5,
        .y = 6,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 62,
    },
    {
        /* G1 */
        .bg_id = 0,
        .x = 5,
        .y = 8,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 94,
    },
    {
        /* B1 */
        .bg_id = 0,
        .x = 5,
        .y = 10,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 126,
    },
    {
        /* start color */
        .bg_id = 0,
        .x = 5,
        .y = 4,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 158,
    },
    {
        /* R2 */
        .bg_id = 0,
        .x = 19,
        .y = 6,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 190,
    },
    {
        /* G2 */
        .bg_id = 0,
        .x = 19,
        .y = 8,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 222,
    },
    {
        /* B2 */
        .bg_id = 0,
        .x = 19,
        .y = 10,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 254,
    },
    {
        /* start color */
        .bg_id = 0,
        .x = 19,
        .y = 4,
        .width = 6,
        .height = 2,
        .pal_id = 15,
        .charbase = 286,
    },
    {
        /* Application desc text */
        .bg_id = 0,
        .x = 1,
        .y = 16,
        .width = 32,
        .height = 6,
        .pal_id = 15,
        .charbase = 318,
    },
    {
        .bg_id = 0xFF, /* marks the end of the tb array */
    },
};


void UpdateSettingsAppText()
{
    pchar helpText[] = _("Change the background colors. Use the\nA and B buttons to adjust color values");
    rboxid_clear_pixels(10, 0);
    rboxid_print(10, 1, 3, 0, &textWhite, 0, helpText);
    rboxid_update(10, 3);
    rboxid_tilemap_update(10);
}

void UpdateRBGScaleText()
{
    pchar redText[] = _("{COLOR 4}{SHADOW 3}R: 203");
    pchar greenText[] = _("{COLOR 6}{SHADOW 3}G: 202");
    pchar blueText[] = _("{COLOR 8}{SHADOW 3}B: 204");
    pchar red2Text[] = _("{COLOR 4}{SHADOW 3}R: 103");
    pchar green2Text[] = _("{COLOR 6}{SHADOW 3}G: 102");
    pchar blue2Text[] = _("{COLOR 8}{SHADOW 3}B: 104");
    pchar startText[] = _("Color 1");
    pchar start2Text[] = _("Color 2");
    rboxid_clear_pixels(2, 0x11);
    rboxid_clear_pixels(3, 0x11);
    rboxid_clear_pixels(4, 0x11);
    rboxid_clear_pixels(5, 0xBB);
    rboxid_clear_pixels(6, 0x11);
    rboxid_clear_pixels(7, 0x11);
    rboxid_clear_pixels(8, 0x11);
    rboxid_clear_pixels(9, 0xBB);
    rboxid_print(2, 1, 3, 0, &textWhite, 0, redText);
    rboxid_print(3, 1, 3, 0, &textWhite, 0, greenText);
    rboxid_print(4, 1, 3, 0, &textWhite, 0, blueText);
    rboxid_print(5, 1, 3, 0, &textWhite, 0, startText);
    rboxid_print(6, 1, 3, 0, &textWhite, 0, red2Text);
    rboxid_print(7, 1, 3, 0, &textWhite, 0, green2Text);
    rboxid_print(8, 1, 3, 0, &textWhite, 0, blue2Text);
    rboxid_print(9, 1, 3, 0, &textWhite, 0, start2Text);
    for (u32 i = 2; i < 10; i++) {
        rboxid_update(i, 3);
        rboxid_tilemap_update(i);
    }
}

void SetBackgroundColors()
{
    u16* c1 = (u16*)ULTRADEX_COLOR1;
    u16* c2 = (u16*)ULTRADEX_COLOR2;
    BuildGradient(*c1, *c2);
    BuildGradientPalette();
    LoadPalette(gUltraDex->sharedGfx->gradient_palette, 0, 32);
    memset(gUltraDex->sharedGfx->gradient_palette, 0, 32 * 20);
}




void SettingsGuiHandler() {
    switch(gMain.state) {
        case 0:
            if (!gPaletteFade.active) {
                m4aMPlayVolumeControl(&mplay_BGM, 0xFFFF, 128);
                UltraDexSetup();
                SetMainCallback(SettingsGuiHandler); // setup resets all CBs
                gUltraDex->sharedGfx = (struct UltraDexSharedGraphics*)malloc_and_clear(sizeof(struct UltraDexSharedGraphics));
                gMain.state++;
            }
            break;
        case 1:
        {
            // build bg graphics
            void *char_base = (void*) 0x6000000 + (0x4000 * 2);
            void *map_base = (void*) 0x6000000 + (0xF800 - (0x800 * 2));
            BuildMosaic(char_base + 0x4000, map_base - 0x800);
            gMain.state++;
            break;
        }
        case 2:
        {
            // update text
            rbox_init_from_templates(UDexSettingsTextTemplate);
            UpdateAppHeaderText();
            UpdateSettingsAppText();
            UpdateRBGScaleText();
            gMain.state++;
            break;
        }
        case 3:
            gMain.state++;
            break;
        case 4:
        {
            SetBackgroundColors();
            SetHBlankCallback(HBlankCBUltraDex);
            interrupts_enable(INTERRUPT_VBLANK | INTERRUPT_HBLANK);

            // void *sw_bgbackbuffer = malloc(0x800);
            // gBattleMaster->switch_main.back_buffer = sw_bgbackbuffer;
            // LoadPalette_compressed((void *)bgPal, 0, 32);
            // LZ77UnCompWram((void *)bgMap, (void *)sw_bgbackbuffer);
            // lz77UnCompVram((void *)bgTiles, (void *)0x06000000);
            // bgid_set_tilemap(2, sw_bgbackbuffer);

            gMain.state++;
            break;
        }
        case 5:
            bgid_mark_for_sync(0);
            bgid_mark_for_sync(1);
            bgid_mark_for_sync(2);
            bgid_mark_for_sync(3);
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            gMain.state++;
            break;
        case 6:
            if (!gPaletteFade.active) {
                gMain.state++;
            } else {
                BuildGradientPalette();
            }
            break;
        case 7:
            // handle input
            {
                // void C1UltraDexInteractionHandler(void);
                // SetMainCallback(C1UltraDexInteractionHandler);
                // gMain.state = 0;
                break;
            }
        default:
            break;
        };
}
