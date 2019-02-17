#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"

#include "../battle/switch_scene/switch_scene.h"
// images
#include "../../generated/images/switch/slider_bot.h"
#include "../../generated/images/switch/slider_mid.h"
#include "../../generated/images/switch/slider_top.h"
#include "../../generated/images/PSS_icons1.h"
#include "../../generated/images/battle_terrains/grass/grass_bg.h"
#include "../../generated/images/switch/switch_bg.h"
#include "../../generated/images/type_icons.h"
#include "../../generated/images/hpbox/hpbar_pieces_switch.h"
#include "../../generated/images/switch/shift_menu.h"
#include "../../generated/images/switch/shift_cursor.h"

void ScriptCmd_loadsprite(void);
void ScriptCmd_freespritetag(void);

extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];

const AnimScriptFunc gAnimTable[] = {
    ScriptCmd_loadsprite,
    ScriptCmd_freespritetag,
};


void InitializeAnimationCore(u8* scr1, u8* scr2, u8* scr3, u8* scr4)
{
    // Allocate and assign script pointers to each thread
    gAnimationCore = (struct AnimationCore*)malloc_and_clear(sizeof(struct AnimationCore));
	dprintf("allocated %d space at %x\n", sizeof(struct AnimationCore), gAnimationCore);
    gAnimationCore->animScriptPtr[0] = scr1;
	dprintf("scr1 is %d\n", scr1);
    gAnimationCore->animScriptPtr[1] = scr2;
    gAnimationCore->animScriptPtr[2] = scr3;
    gAnimationCore->animScriptPtr[3] = scr4;
}

void RunAnimAvailableThread(u8* src)
{
    // find an unused script pointer and assign animation script to it
    for (u8 i = 0; i < ANIM_SCR_COUNT; i++) {
        if (gAnimationCore->animScriptPtr[i] == NULL) {
            gAnimationCore->animScriptPtr[i] = src;
            return;
        }
    }
}

void RunCurrentCommand()
{
    u8 cmd = ANIMSCR_READ_BYTE;
    dprintf("running command id %d for script %x\n", cmd, (u32)ANIMSCR_SCRIPT);
    if (cmd == 0xFF) {
        gAnimationCore->waitAll = true;
        return;
    }
    gAnimTable[cmd]();
}


/* this will only load the graphics themselves. Later must be initialized as objects */
void ScriptCmd_loadsprite()
{
    // alignment for read
	ANIMSCR_MOVE(3);
    // read pal and gfx from script pointer
    struct CompressedSpriteSheet* gfx = (struct CompressedSpriteSheet*)ANIMSCR_READ_WORD;
    struct SpritePalette* pal = (struct SpritePalette*)ANIMSCR_READ_WORD;
    LoadCompressedSpriteSheetUsingHeap(gfx);
    LoadCompressedSpritePaletteUsingHeap(pal);
    ANIMSCR_CMD_NEXT;
}

/* Deletes a sprite from the gfx tag */
void ScriptCmd_freespritetag()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    // read tag
    u16 tag = ANIMSCR_READ_HWORD;
    for (u8 i = 0; i < 64; i++) {
        if (tag == gSprites[i].gfx_table->tag)
            obj_free(&gSprites[i]);
    }
    ANIMSCR_CMD_NEXT;
}

/* Draw a loaded sprite using it's tag */
void ScriptCmd_initspritetag()
{

}


/* Move a sprite with a tag by a certain delta X in F frames */



const struct SpritePalette scroll_pal1 = {(void *)slider_topPal, SLIDER_PAL_TAG};
const struct CompressedSpriteSheet top_gfx1 = {(void *)slider_topTiles, 512, SLIDER_GFX_TAG};
void AnimationMain()
{
    if (gAnimationCore->waitAll) {
        dprintf("wait all\n");
        return;
    }

    if (ANIMSCR_WAITING) {
        dprintf("current command is waiting, move on\n");
        ANIMSCR_CMD_NEXT;
		return;
    }
    if (!ANIMSCR_SCRIPT) {
        ANIMSCR_CMD_NEXT;
		return;
	}
	dprintf("running animation for thread %d because it was %x\n", ANIMSCR_THREAD, ANIMSCR_SCRIPT);
    RunCurrentCommand();
}


void TestAnimation()
{
	extern u8 scrAnimTesting;
    dprintf("running tests on script %x\n", (u32)&scrAnimTesting);
	InitializeAnimationCore(&scrAnimTesting, NULL, NULL, NULL);
	SetMainCallback(AnimationMain);
}
