#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"

static struct UltraDexState** UltraDexPtr = (struct UltraDexState**)(ULTRADEX_START);
#define gUltraDex (*UltraDexPtr)

struct PlttData
{
    u16 r:5; // red
    u16 g:5; // green
    u16 b:5; // blue
    u16 unused_15:1;
};

u16 BlendColor(u16 color, u8 coeff, u16 blendColor)
{
    struct PlttData *data1 = (struct PlttData *) &color;
    s8 r = data1->r;
    s8 g = data1->g;
    s8 b = data1->b;
    struct PlttData *data2 = (struct PlttData *) &blendColor;
    return ((r + (((data2->r - r) * coeff) >> 4)) << 0)
        | ((g + (((data2->g - g) * coeff) >> 4)) << 5)
        | ((b + (((data2->b - b) * coeff) >> 4)) << 10);
}

void BuildGradient(u16 startColor, u16 stopColor)
{
    struct ColorComponents* start = (struct ColorComponents*) &startColor;
    struct ColorComponents* stop = (struct ColorComponents*) &stopColor;
    u16 lines = sizeof(gUltraDex->sharedGfx->gradient) / sizeof(u16);
    u16 startLine = 2;

    /* RGB 8 bit components */
    u16 mr = ((stop->r << 3) - (start->r << 3)) / (lines - startLine);
    u16 mg = ((stop->g << 3) - (start->g << 3)) / (lines - startLine);
    u16 mb = ((stop->b << 3) - (start->b << 3)) / (lines - startLine);
    u16 r = start->r << 3;
    u16 g = start->g << 3;
    u16 b = start->b << 3;

    union Color color = {};
    for (u8 i = 0; i < lines; i++) {
        if (i < startLine) {
            gUltraDex->sharedGfx->gradient[i] = 0;
        } else {
            color.components.r = r >> 3;
            color.components.g = g >> 3;
            color.components.b = b >> 3;

            gUltraDex->sharedGfx->gradient[i] = color.packed;

            r += mr;
            g += mg;
            b += mb;
        }
    }
}

void BuildGradientPalette(void)
{
    u16* buffer = (u16*) gUltraDex->sharedGfx->gradient_palette;
    for (u8 i = 0; i < sizeof(gUltraDex->sharedGfx->gradient) / sizeof(u16); i++) {
        u16 color = gUltraDex->sharedGfx->gradient[i];

        for (u8 j = 0; j < 16; j++) {
            u8 r = color & 0x1f;
            u8 g = (color >> 5) & 0x1f;
            u8 b = (color >> 10) & 0x1f;

#define SUB_OR_ZERO(a, b) (a) >= (b) ? (a) - (b) : 0
            r = SUB_OR_ZERO(r, (j >> 2) + 2);
            g = SUB_OR_ZERO(g, (j >> 2) + 2);
            b = SUB_OR_ZERO(b, (j >> 2) + 2);
#undef SUB_OR_ZERO

            u16 final_color = r | (g << 5) | (b << 10);
            *buffer++ = BlendColor(final_color, gPaletteFade.y, gPaletteFade.blend_color);
        }
    }
}

void BuildMosaic(void* charbase, void* mapbase)
{
    /* Tile tileset, one tile for each palette */
    u8 tiles[16][32];

    for (u8 i = 0; i < 16; i++) {
        u8 tile = i | (i << 4);
        memset(tiles[i], tile, 32);
    }

    memcpy(charbase, tiles, sizeof(tiles));

    /* Build tilemap */
    u16 tilemap[20][32];

    for (u8 y = 0; y < 20; y++) {
        for (u8 x = 0; x < 32; x++) {
            u8 tile = rand() & 0xF;
            tilemap[y][x] = tile;
        }
    }
    memcpy(mapbase, tilemap, sizeof(tilemap));
}

void HBlankCBUltraDex(void)
{
    /* HBlank saves memory compared to the DMA implementation as the
     * gradient only changes colour every 8 scanlines. */
    u16* buffer = (u16*) gUltraDex->sharedGfx->gradient_palette;
    if (REG_VCOUNT < 160) {
        u16 index = (REG_VCOUNT + 1) / 8;
        memcpy((void*) 0x05000000, &buffer[index * 16], 32);
        if (REG_VCOUNT > 120) {
            //WRITE_REG_WININ(0x3F3F);
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,  WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);

            //WRITE_REG_BLDCNT(0x0FFE);
            REG_BLDCNT = (BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC | BLDCNT_BACKDROP_SRC | BLDCNT_BG0_DST | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST | BLDCNT_DARKEN);
            REG_BLDY = 0x8;
        } else {
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ, WIN_BG0 |
                            WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ);
            //WRITE_REG_BLDCNT(0x401E);
            REG_BLDCNT = BLDALPHA_BUILD(BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC, 0);
        }
    }
}

void HBlankCBUltraDexFadeOut(void)
{
    /* HBlank saves memory compared to the DMA implementation as the
     * gradient only changes colour every 8 scanlines. */
    REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ, WIN_BG0 |
                 WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ);
    //WRITE_REG_BLDCNT(0x401E);
    REG_BLDCNT = BLDALPHA_BUILD(BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC, 0);
    u16* buffer = (u16*) gUltraDex->sharedGfx->gradient_palette;
    if (REG_VCOUNT < 160) {
        u16 index = (REG_VCOUNT + 1) / 8;
        CpuFastSet((void*)&buffer[index * 16], (void*) 0x05000000, CPUModeFS(32, CPUFSCPY));
        if (REG_VCOUNT < gUltraDex->screenTransitionOffsetTop * 8) {
            //WRITE_REG_WININ(0x3F3F);
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,  WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);

            //WRITE_REG_BLDCNT(0x0FFE);
            REG_BLDCNT = (BLDCNT_BG0_SRC | BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC | BLDCNT_BACKDROP_SRC | BLDCNT_BG0_DST | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST | BLDCNT_DARKEN);
            REG_BLDY = gUltraDex->screenTransitionOffsetTop;
        }
        if (REG_VCOUNT > 120) {
            //WRITE_REG_WININ(0x3F3F);
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,  WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);

            //WRITE_REG_BLDCNT(0x0FFE);
            REG_BLDCNT = (BLDCNT_BG0_SRC | BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_SRC | BLDCNT_BACKDROP_SRC | BLDCNT_BG0_DST | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST | BLDCNT_DARKEN);
            REG_BLDY = 0x8 + gUltraDex->screenTransitionOffsetTop;
       }
    }

}
