#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"


void ScriptCmd_loadsprite(void);
void ScriptCmd_deletesprite(void);
void ScriptCmd_rendersprite(void);
void ScriptCmd_copyvar(void);
void ScriptCmd_setvar(void);
void ScriptCmd_addvar(void);
void ScriptCmd_subvar(void);
void ScriptCmd_mulvar(void);
void ScriptCmd_divvar(void);
void ScriptCmd_goto(void);
void ScriptCmd_movesprite(void);
void ScriptCmd_waitthread(void);
void ScriptCmd_RunAnimAvailableThread(void);
void ScriptCmd_waitframes(void);
void ScriptCmd_animatesprite(void);
void ScriptCmd_spriteshow(void);
void ScriptCmd_spritehide(void);
void ScriptCmd_setspritepal(void);
void ScriptCmd_spritetobg(void);
void ScriptCmd_spritesblend(void);
void ScriptCmd_spritebgclear(void);
void ScriptCmd_spriteblend(void);
void ScriptCmd_excludeblend(void);

extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];
extern void TaskMoveSprite(u8 taskId);
extern void TaskWaitFrames(u8 taskId);


const AnimScriptFunc gAnimTable[] = {
    ScriptCmd_loadsprite, // 0
    ScriptCmd_deletesprite, // 1
    ScriptCmd_rendersprite, // 2
    ScriptCmd_copyvar, // 3
    ScriptCmd_setvar, // 4
    ScriptCmd_addvar, // 5
    ScriptCmd_subvar, // 6
    ScriptCmd_mulvar, // 7
    ScriptCmd_divvar, // 8
    ScriptCmd_goto, // 9
    ScriptCmd_movesprite, // 10
    ScriptCmd_waitthread, // 11
    ScriptCmd_RunAnimAvailableThread, //12
    ScriptCmd_waitframes, //13
    ScriptCmd_animatesprite, //14
    ScriptCmd_spriteshow, // 15
    ScriptCmd_spritehide, // 16
    ScriptCmd_setspritepal, // 17
    ScriptCmd_spritetobg, // 18
    ScriptCmd_spritebgclear, // 19
    ScriptCmd_spritesblend, // 20
    ScriptCmd_excludeblend, // 21
};


void InitializeAnimationCore(u8* scr1, u8* scr2, u8* scr3, u8* scr4)
{
    // Allocate and assign script pointers to each thread
    gAnimationCore = (struct AnimationCore*)malloc_and_clear(sizeof(struct AnimationCore));
    gAnimationCore->animScriptPtr[0] = scr1;
    gAnimationCore->animScriptPtr[1] = scr2;
    gAnimationCore->animScriptPtr[2] = scr3;
    gAnimationCore->animScriptPtr[3] = scr4;
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
    struct OamData* oam = (struct OamData*)ANIMSCR_READ_WORD;
    struct Template spriteTemp = {gfx->tag, pal->tag, oam, nullframe, gfx, nullrsf, (SpriteCallback)oac_nullsub};
    LoadCompressedSpriteSheetUsingHeap(gfx);
    LoadCompressedSpritePaletteUsingHeap(pal);
    u8 spriteId = template_instanciate_forward_search(&spriteTemp, 0, 0, 0);
    gSprites[spriteId].invisible = true;
    var_800D = spriteId;
    ANIMSCR_CMD_NEXT;
}

/* Deletes a sprite from the gfx tag */
void ScriptCmd_deletesprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    // read tag
    u16 var = ANIMSCR_READ_HWORD;
    obj_free(&gSprites[VarGet(var)]);
    ANIMSCR_CMD_NEXT;
}

/* show a loaded sprite using it's tag */
void ScriptCmd_rendersprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    // read tag
    u16 var = ANIMSCR_READ_HWORD;
    var = VarGet(var);
    // read positional arguements
    s8 x = (s8)ANIMSCR_READ_HWORD;
    s8 y = (s8)ANIMSCR_READ_HWORD;
    // read animation data
    struct RotscaleFrame (**rotscale_table)[] = (void*)ANIMSCR_READ_WORD;
    struct Sprite* s = &gSprites[var];
    s->pos1.x = x;
    s->pos1.y = y;
    s->rotscale_table = rotscale_table;
    s->invisible = false;
    ANIMSCR_CMD_NEXT;
}

/* Var related script commands */
void ScriptCmd_copyvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 dst = ANIMSCR_READ_HWORD;
    u16 src = ANIMSCR_READ_HWORD;
    VarSet(dst, VarGet(src));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_setvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, value);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_addvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) + value);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_subvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) - value);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_mulvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) * value);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_divvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) / value);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_goto()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u32 scriptPtr = ANIMSCR_READ_WORD;
    ANIMSCR_SCRIPT = (void*)scriptPtr;
    ANIMSCR_CMD_NEXT;
}


/* Moves a sprite to a position by an amount per frame */
void ScriptCmd_movesprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u8 taskId = CreateTask(TaskMoveSprite, 0);
    struct Task* t = &tasks[taskId];

    // set passed args to task
    u16 spriteId = ANIMSCR_READ_HWORD;
    t->priv[0] = VarGet(spriteId);
    t->priv[1] = ANIMSCR_READ_HWORD; // Delta X
    t->priv[2] = ANIMSCR_READ_HWORD; // Delta Y
    t->priv[3] = ANIMSCR_READ_HWORD; // Amount of frames to do animation for
    t->priv[4] = ANIMSCR_THREAD; // execution thread
    // to wait for finish, make sure to put use a waitanim command as the next command.
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

/* sets the thread to a waiting state */
void ScriptCmd_waitthread()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    ANIMSCR_WAITING = true;
    ANIMSCR_CMD_NEXT;
}

/* start a script on an available thread */
void ScriptCmd_RunAnimAvailableThread()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u8* scriptPtr = (u8*)ANIMSCR_READ_WORD;
    // find an unused script pointer and assign animation script to it
    for (u8 i = 0; i < ANIM_SCR_COUNT; i++) {
        if (gAnimationCore->animScriptPtr[i] == NULL) {
            gAnimationCore->animScriptPtr[i] = scriptPtr;
            break;
        }
    }
    dprintf("no thread available for script insertion\n");
    ANIMSCR_CMD_NEXT;
}

/* sets a thread on a waiting state for X amount of frames */
void ScriptCmd_waitframes()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 waitTime = ANIMSCR_READ_HWORD;
    u8 taskId = CreateTask(TaskWaitFrames, 0);
    tasks[taskId].priv[0] = waitTime;
    tasks[taskId].priv[1] = ANIMSCR_THREAD;
    ANIMSCR_CMD_NEXT;
}

/* writes an animation struct to a sprite and starts the animation */
void ScriptCmd_animatesprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct RotscaleFrame (**rotscale_table)[] = (void*)ANIMSCR_READ_WORD;
    gSprites[spriteId].rotscale_table = rotscale_table;
    gSprites[spriteId].final_oam.affine_mode = 1;
    ANIMSCR_CMD_NEXT;
}

/* Sprite show and hide commands */
void ScriptCmd_spriteshow()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    gSprites[spriteId].invisible = false;
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_spritehide()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    gSprites[spriteId].invisible = true;
    ANIMSCR_CMD_NEXT;
}

/* Given a sprite ID, change it's palette */
void ScriptCmd_setspritepal()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    void* palette = (void*)ANIMSCR_READ_WORD;
    // figure out palette number and apply new palette to it
    u8 palSlot = gSprites[spriteId].final_oam.palette_num;
    LoadPalette(palette, 16 * (16 + palSlot), 32);
    ANIMSCR_CMD_NEXT;
}

void DrawSpriteToBG1(u8 spriteId, u8 palslotBG, u8 width, u8 height)
{
    // turn on BG 1 display
    REG_DISPCNT |= DISPCNT_BG1;

    // zerofill tilemap and tileset for BG1
    void* charBase = (void *)0x6008000;
    u16* mapBase = (void*)0x600F000;
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)charBase, CPUModeFS(4096, CPUFSSET));
    CpuFastSet((void*)&set, (void*)mapBase, CPUModeFS(2048, CPUFSSET));

    // copy into BG1 tileset, tiles from the OAM. Note the first tile on the tileset is left empty
    // this is so that the 0filled tiles don't display as the first tile of the image
    u32 tileOffset = gSprites[spriteId].final_oam.tile_num * 32;
    CpuFastSet((void*)(0x6010000 + tileOffset), charBase + 32, CPUModeFS(32 * width * height, CPUFSCPY));

    // create tilemap
    u8 offset = 1; // this is 1 because the first tile in the tileset is 0 filled
    for (u8 xTile = 0; xTile < width; xTile++) {
        for (u8 yTile = 0; yTile < height; yTile++) {
            mapBase[xTile * 32 + yTile] = offset | (palslotBG << 12);
            offset++;
        }
    }

    // write sprite palette to BG
    u8 spritePalSlot = gSprites[spriteId].final_oam.palette_num;
    void* spritepal = (void*)(ADDR_OAMPALRAM + (spritePalSlot * 32));
    void* bgpal = (void*)(ADDR_PALRAM + (32 * palslotBG));
    CpuFastSet(spritepal, bgpal, CPUModeFS(32, CPUFSCPY));
    LoadPalette(spritepal, 16 * palslotBG, 32);

    // BG position to sprite position
    REG_BG1HOFS = -gSprites[spriteId].pos1.x + (4 * width);
    REG_BG1VOFS = -gSprites[spriteId].pos1.y + (4 * height);
    gSprites[spriteId].invisible = true;
}


/* Copy Sprite to BG layer (typically done for blending) */
void ScriptCmd_spritetobg()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u16 tilewidth = ANIMSCR_READ_HWORD;
    u16 tileheight = ANIMSCR_READ_HWORD;
    DrawSpriteToBG1(spriteId, 4, tilewidth, tileheight);
    ANIMSCR_CMD_NEXT;
}

/* Clears bg1, the bg which sprites are mirrored to */
void ScriptCmd_spritebgclear()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    void* charBase = (void *)0x6008000;
    u16* mapBase = (void*)0x600F000;
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)charBase, CPUModeFS(4096, CPUFSSET));
    CpuFastSet((void*)&set, (void*)mapBase, CPUModeFS(2048, CPUFSSET));
    gSprites[spriteId].invisible = false;
    ANIMSCR_CMD_NEXT;
}

/* Given a coefficient for the amount of blending for the sprites and BG 0. Apply blending */
void ScriptCmd_spritesblend()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u8 coefficientA = ANIMSCR_READ_BYTE;
    u8 coefficientB = ANIMSCR_READ_BYTE;
    REG_BLDCNT = (BLDCNT_BG1_SRC |  BLDCNT_SPRITES_DST | BLDCNT_ALPHA_BLEND);
    REG_BLDALPHA = BLDALPHA_BUILD(coefficientA, coefficientB);

    // set blending move for the sprite
    ANIMSCR_CMD_NEXT;
}

/* Exclude a sprite from blending */
void ScriptCmd_excludeblend()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    gSprites[spriteId].final_oam.obj_mode = 1; // semi-transparent
    ANIMSCR_CMD_NEXT;
}


void AnimationMain()
{
    if (gAnimationCore->waitAll)
        return;

    for (u8 i = 0; i < ANIM_SCR_COUNT; i++) {
        if (ANIMSCR_WAITING || !ANIMSCR_SCRIPT) {
            ANIMSCR_CMD_NEXT;
        } else {
            RunCurrentCommand();
        }
}


void TestAnimation()
{
    extern u8 scrAnimTesting;
    dprintf("running tests on script %x\n", (u32)&scrAnimTesting);
    InitializeAnimationCore(&scrAnimTesting, NULL, NULL, NULL);
    SetMainCallback(AnimationMain);
}
