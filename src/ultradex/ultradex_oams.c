#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"
#include "../../generated/images/ultradex/menu/arrow.h"
#include "../../generated/images/ultradex/menu/page_indicator.h"
#include "../../generated/images/ultradex/icons/pokelog.h"
#include "../../generated/images/ultradex/icons/dexnav.h"
#include "../../generated/images/ultradex/icons/pokepedia.h"
#include "../../generated/images/ultradex/icons/map.h"
#include "../../generated/images/ultradex/icons/phone.h"
#include "../../generated/images/ultradex/icons/clock.h"
#include "../../generated/images/ultradex/icons/webmart.h"
#include "../../generated/images/ultradex/icons/weather.h"

static struct UltraDexState** UltraDexPtr = (struct UltraDexState**)(ULTRADEX_START);
extern void C1UltraDexInteractionHandler(void);

/* CURSOR */
const struct OamData ultraDexCursorOam = {
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


void CursorBob(struct Sprite* s)
{
#define CURSOR_ORIGINAL_Y (s->data[0])
#define CURSOR_BOT_Y (CURSOR_ORIGINAL_Y + 3)
#define CURSOR_TOP_Y (CURSOR_ORIGINAL_Y - 3)
#define CURSOR_DIRECTION (s->data[1])
#define CURSOR_COUNTER (s->data[2])
    CURSOR_COUNTER++;
    if (CURSOR_COUNTER % 3)
        return;
    if (!CURSOR_ORIGINAL_Y)
        CURSOR_ORIGINAL_Y = s->pos1.y;

    if (CURSOR_DIRECTION) {
        // move down until goal
        if (s->pos1.y >= CURSOR_BOT_Y) {
            CURSOR_DIRECTION = 0;
        } else {
            s->pos1.y++;
        }
    } else {
        // move up until goal
        if (s->pos1.y <= CURSOR_TOP_Y) {
            CURSOR_DIRECTION = 1;
        } else {
            s->pos1.y--;
        }
    }
#undef CURSOR_ORIGINAL_Y
#undef CURSOR_BOT_Y
#undef CURSOR_TOP_Y
#undef CURSOR_DIRECTION
#undef CURSOR_COUNTER
}


void UpdateUltraDexCursor()
{
    u8 cursorX;
    if (!gUltraDex->selectedAppIndex && !gUltraDex->currentOpenApp) {
        cursorX = 36;
    }
    if (gUltraDex->page) {
        cursorX = 36 + ((gUltraDex->selectedAppIndex - (APPS_COUNT >> 1)) * 56);
    } else {
        cursorX = 36 + (gUltraDex->selectedAppIndex * 56);
    }
    gSprites[gUltraDex->cursorObjId].pos1.x = cursorX;
}


void SpawnUltraDexCursor()
{
    struct SpriteTiles cursorGfx = {(void*)arrowTiles, 32 * 1, ULTRADEX_CURSOR_TAG};
    struct SpritePalette cursorPal = {(void*)arrowPal, ULTRADEX_CURSOR_TAG};
    struct Template cursorTemp = {ULTRADEX_CURSOR_TAG, ULTRADEX_CURSOR_TAG, &ultraDexCursorOam,
                                    (const struct Frame (**)[])0x8231CF0, &cursorGfx,
                                    (const struct RotscaleFrame (**)[])0x8231CFC, (SpriteCallback)CursorBob};
    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&cursorGfx);
    gpu_pal_obj_alloc_tag_and_apply(&cursorPal);
    gUltraDex->cursorObjId = template_instanciate_forward_search(&cursorTemp, 36, 24, 0);
    gSprites[gUltraDex->cursorObjId].invisible = true;
}


/* Page Indicator */
const struct OamData ultraDexPageOam = {
    .y = 0,
    .affine_mode = 0,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1, // horizontal
    .x = 0,
    .matrix_num = 0,
    .size = 0, //16x8
    .tile_num = 0,
    .priority = 0, // above BG layers
    .palette_num = 0,
    .affine_param = 0
};


void SpawnUltraDexPageTracker()
{
    struct SpriteTiles pageGfx = {(void*)page_indicatorTiles, 32 * 2, ULTRADEX_PAGE_ICON_TAG};
    struct SpritePalette pagePal = {(void*)page_indicatorPal, ULTRADEX_PAGE_ICON_TAG};
    struct Template pageTemp = {ULTRADEX_PAGE_ICON_TAG, ULTRADEX_PAGE_ICON_TAG, &ultraDexPageOam,
                                    (const struct Frame (**)[])0x8231CF0, &pageGfx,
                                    (const struct RotscaleFrame (**)[])0x8231CFC, (SpriteCallback)oac_nullsub};
    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&pageGfx);
    gpu_pal_obj_alloc_tag_and_apply(&pagePal);
    gUltraDex->pageObjId = template_instanciate_forward_search(&pageTemp, 120, 104, 0);
    gSprites[gUltraDex->pageObjId].invisible = true;
}


/* ICONS */
const struct OamData ultraDexAppIconOam = {
    .y = 0,
    .affine_mode = 0,
    .obj_mode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrix_num = 0,
    .size = 3, //64x64
    .tile_num = 0,
    .priority = 0, // above BG layers
    .palette_num = 0,
    .affine_param = 0
};


void SpawnUltraDexIcon(u8 i, void* tiles, void* pal)
{
    /* Pokelog */
    struct SpriteTiles iconGfx = {(void*)tiles, 32 * 64, ULTRADEX_APP_ICON_TAG + i};
    struct SpritePalette iconPal = {(void*)pal, ULTRADEX_APP_ICON_TAG + i};
    struct Template iconTemp = {ULTRADEX_APP_ICON_TAG + i, ULTRADEX_APP_ICON_TAG + i, &ultraDexAppIconOam,
                                    (const struct Frame (**)[])0x8231CF0, &iconGfx,
                                    (const struct RotscaleFrame (**)[])0x8231CFC, (SpriteCallback)oac_nullsub};
    // uncompressed
    gpu_tile_obj_alloc_tag_and_upload(&iconGfx);
    gpu_pal_obj_alloc_tag_and_apply(&iconPal);
    u16 x = i >= (APPS_COUNT >> 1) ? 240 + 36 + ((i - (APPS_COUNT >> 1)) * 56) : 36 + (i * 56);
    dprintf("x pos is %d\n", x);
    dprintf("i is %d\n", i);
    gUltraDex->iconObjIds[i] = template_instanciate_forward_search(&iconTemp, x, 56, 0);
    gSprites[gUltraDex->iconObjIds[i]].invisible = true;
}


void SpawnPageOneIcons()
{
    SpawnUltraDexIcon(0, (void*)pokelogTiles, (void*)pokelogPal);
    SpawnUltraDexIcon(1, (void*)dexnavTiles, (void*)dexnavPal);
    SpawnUltraDexIcon(2, (void*)pokepediaTiles, (void*)pokepediaPal);
    SpawnUltraDexIcon(3, (void*)mapTiles, (void*)mapPal);
}


void SpawnPageTwoIcons()
{
    SpawnUltraDexIcon(4, (void*)phoneTiles, (void*)phonePal);
    SpawnUltraDexIcon(5, (void*)clockTiles, (void*)clockPal);
    SpawnUltraDexIcon(6, (void*)webmartTiles, (void*)webmartPal);
    SpawnUltraDexIcon(7, (void*)weatherTiles, (void*)weatherPal);
}


void HideUltraDexObjects(u8 page)
{
    u8 i = page ? APPS_PER_PAGE - 1 : 0;
    u8 max = page ? APPS_COUNT : APPS_COUNT >> 1;
    for (; i < max; i++) {
        gSprites[gUltraDex->iconObjIds[i]].invisible = true;
    }
}


void ShowUltraDexObjects(u8 page)
{
    gSprites[gUltraDex->cursorObjId].invisible = false;
    gSprites[gUltraDex->pageObjId].invisible = false;
    u8 i = page ? APPS_PER_PAGE - 1 : 0;
    u8 max = page ? APPS_COUNT : APPS_COUNT >> 1;
    for (; i < max; i++) {
        gSprites[gUltraDex->iconObjIds[i]].invisible = false;
    }
}


void SlideObjLeft240(struct Sprite* s)
{
#define INITIAL_POSITION (s->data[0])
#define GOAL_POSITION (INITIAL_POSITION - 240)
    if (!INITIAL_POSITION)
        INITIAL_POSITION = s->pos1.x;
    if (s->pos1.x == GOAL_POSITION) {
        INITIAL_POSITION = 0;
        s->callback = oac_nullsub;
        SetMainCallback(C1UltraDexInteractionHandler);
        gSprites[gUltraDex->cursorObjId].invisible = false;
    } else {
        s->pos1.x -= 16;
    }
#undef INITIAL_POSITION
#undef GOAL_POSITION
}

void SlideObjRight240(struct Sprite* s)
{
#define INITIAL_POSITION (s->data[0])
#define GOAL_POSITION (INITIAL_POSITION + 240)
    if (!INITIAL_POSITION)
        INITIAL_POSITION = s->pos1.x;
    if (s->pos1.x == GOAL_POSITION) {
        INITIAL_POSITION = 0;
        s->callback = oac_nullsub;
        SetMainCallback(C1UltraDexInteractionHandler);
        gSprites[gUltraDex->cursorObjId].invisible = false;
    } else {
        s->pos1.x += 16;
    }
#undef INITIAL_POSITION
#undef GOAL_POSITION
}

void TransitionPage2()
{
    for (u8 i = 0; i < (APPS_COUNT - 1); i++) {
        gSprites[gUltraDex->iconObjIds[i]].callback = SlideObjLeft240;
    }
}

void TransitionPage1()
{
    for (u8 i = 0; i < (APPS_COUNT - 1); i++) {
        gSprites[gUltraDex->iconObjIds[i]].callback = SlideObjRight240;
    }
}
