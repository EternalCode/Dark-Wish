#include <pokeagb/pokeagb.h>
#include "animation_core.h"
#include "../global.h"
#include "../battle/battle_actions/actions.h"
#include "../battle/battle_data/battle_state.h"
#include "../battle/battle_data/pkmn_bank_stats.h"


void ScriptCmd_loadspritefull(void);
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
void ScriptCmd_excludeblend(void);
void ScriptCmd_includeblend(void);
void SpriteCmd_darkensprites(void);
void SpriteCmd_lightensprites(void);
void ScripCmd_clearpalbuff(void);
void ScriptCmd_palbufferspriteandbgs(void);
void ScriptCmd_palfade(void);
void SpriteCmd_movewave(void);
void ScriptCmd_uploadbg(void);
void ScriptCmd_showbg(void);
void ScriptCmd_hidebg(void);
void ScriptCmd_flashsprite(void);
void ScriptCmd_getattacker(void);
void ScriptCmd_getdefender(void);
void ScriptCmd_getattackercoords(void);
void ScriptCmd_getdefendercoords(void);
void ScriptCmd_quakebg(void);
void ScriptCmd_call(void);
void ScriptCmd_return(void);
void ScriptCmd_if(void);
void ScriptCmd_compare(void);
void ScriptCmd_comparevars(void);
void ScriptCmd_sideofsprite(void);
void ScriptCmd_fastsetbattlers(void);
void ScriptCmd_shakehpbox(void);
void ScriptCmd_randrange(void);
void ScriptCmd_addvars(void);
void ScriptCmd_subvars(void);
void ScriptCmd_runtask(void);
void ScriptCmd_quakesprite(void);
void ScriptCmd_setframessprite(void);
void ScriptCmd_loadsprite(void);
void ScriptCmd_fadespritebg(void);
void ScriptCmd_waittask(void);
void ScriptCmd_confighorizontalarctranslate(void);
void ScriptCmd_waitanimation(void);
void ScriptCmd_waitaffineanimation(void);
void ScriptCmd_spritecallback(void);
void ScriptCmd_hidehpbars(void);
void ScriptCmd_showhpbars(void);
void ScriptCmd_orbit(void);
void ScriptCmd_movebg(void);
void ScriptCmd_copyactionpriv(void);
void ScriptCmd_spriteblend2(void);
void ScriptCmd_spritebufferposition(void);
void ScriptCmd_playmessage(void);
void ScriptCmd_spriteafterimage(void);
void ScriptCmd_movespritedst(void);
void ScriptCmd_setpriority(void);
void ScriptCmd_setprioritybg(void);
void ScriptCmd_clearblending(void);
void ScriptCmd_spritesblendall(void);
void ScriptCmd_fireworkeffect(void);
void ScriptCmd_random(void);
void ScriptCmd_fadeplatformbg(void);
void ScriptCmd_depthlessorbit(void);
void ScriptCmd_shrinkingorbit(void);
void ScriptCmd_spritesetposition(void);
void ScriptCmd_spritecallbackargs(void);
void ScriptCmd_runspritefunc(void);
void ScriptCmd_blendsemitransparent(void);
void ScriptCmd_runvoidfunc(void);
void ScriptCmd_spritefeatherfall(void);
void ScriptCmd_pickrandompos(void);


extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];
extern void TaskMoveSprite(u8 taskId);
extern void SCBMoveSpriteErrorCorrection(struct Sprite* spr);
extern void TaskWaitFrames(u8 taskId);
extern void TaskWaitFade(u8 taskId);
extern void TaskFlashSprite(u8 taskId);
extern void TaskQuakeBg(u8 taskId);
extern void TaskQuakeSprite(u8 taskId);
extern void TaskHPBoxBobFast(u8 taskId);
extern void TaskWaitForTask(u8 taskId);
extern void TaskWaitAnimation(u8 taskId);
extern void TaskWaitAffineAnimation(u8 taskId);
extern void TaskMoveBG(u8 taskId);
extern void TaskWaitAnimMessage(u8 taskId);
extern void TaskCreateSmallFireworkGeneric(u8 taskId);
extern void battle_loop(void);
extern void InitAnimLinearTranslation(struct Sprite *sprite);
extern void pick_battle_message(u16 moveId, u8 user_bank, enum BattleTypes battle_type, enum battle_string_ids id, u16 move_effect_id);
extern void ShowBattleMessage2(pchar* str, u8 rboxid);
extern void AnimOrbitFastStep(struct Sprite *sprite);
extern void AnimOrbitFastStepNoPriority(struct Sprite *sprite);
extern void AnimOrbitShrinkNoPriority(struct Sprite *sprite);
extern void SCB_SpriteFeatherFall(struct Sprite *sprite);

const AnimScriptFunc gAnimTable[] = {
    ScriptCmd_loadspritefull, // 0
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
    SpriteCmd_darkensprites, // 22
    SpriteCmd_lightensprites, // 23
    ScripCmd_clearpalbuff, // 24
    ScriptCmd_palbufferspriteandbgs, // 25
    ScriptCmd_palfade, // 26
    SpriteCmd_movewave, // 27
    ScriptCmd_uploadbg, // 28
    ScriptCmd_showbg, // 29
    ScriptCmd_hidebg, // 30
    ScriptCmd_includeblend, // 31
    ScriptCmd_flashsprite, // 32
    ScriptCmd_getattacker, // 33
    ScriptCmd_getdefender, // 34
    ScriptCmd_getattackercoords, // 35
    ScriptCmd_getdefendercoords, // 36
    ScriptCmd_quakebg, // 37
    ScriptCmd_call, // 38
    ScriptCmd_return, // 39
    ScriptCmd_if, // 40
    ScriptCmd_compare, // 41
    ScriptCmd_comparevars, // 42
    ScriptCmd_sideofsprite, // 43
    ScriptCmd_fastsetbattlers, // 44
    ScriptCmd_shakehpbox, // 45
    ScriptCmd_randrange, // 46
    ScriptCmd_addvars, // 47
    ScriptCmd_subvars, // 48
    ScriptCmd_runtask, // 49
    ScriptCmd_quakesprite, // 50
    ScriptCmd_setframessprite, // 51
    ScriptCmd_loadsprite, // 52
    ScriptCmd_fadespritebg, // 53
    ScriptCmd_waittask, // 54
    ScriptCmd_confighorizontalarctranslate, // 55
    ScriptCmd_waitanimation, // 56
    ScriptCmd_waitaffineanimation, // 57
    ScriptCmd_spritecallback, // 58
	ScriptCmd_hidehpbars, // 59
    ScriptCmd_showhpbars, // 60
    ScriptCmd_orbit, // 61
    ScriptCmd_movebg, // 62
    ScriptCmd_copyactionpriv, // 63
    ScriptCmd_spriteblend2, // 64
    ScriptCmd_spritebufferposition, // 65
    ScriptCmd_playmessage, // 66
    ScriptCmd_spriteafterimage, // 67
    ScriptCmd_movespritedst, // 68
    ScriptCmd_setpriority, // 69
    ScriptCmd_setprioritybg, // 70
    ScriptCmd_clearblending, // 71
    ScriptCmd_spritesblendall, // 72
    ScriptCmd_fireworkeffect, // 73
    ScriptCmd_random, // 74
    ScriptCmd_fadeplatformbg, // 75
    ScriptCmd_depthlessorbit, // 76
    ScriptCmd_shrinkingorbit, // 77
    ScriptCmd_spritesetposition, // 78
    ScriptCmd_spritecallbackargs, // 79
    ScriptCmd_runspritefunc, // 80
    ScriptCmd_blendsemitransparent, // 81
    ScriptCmd_runvoidfunc, // 82
    ScriptCmd_spritefeatherfall, // 83
    ScriptCmd_pickrandompos, // 84
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

#define ENDCMD 0xFF
#define BLOCKCMD 0xFE
#define OPENCMD 0xFD
void RunCurrentCommand()
{
    u8 cmd = ANIMSCR_READ_BYTE;
    dprintf("running command id %d for script %x in thread %d\n", cmd, (u32)ANIMSCR_SCRIPT, ANIMSCR_THREAD);
    if (cmd == ENDCMD) {
        ANIMSCR_SCRIPT = NULL;
        ANIMSCR_CMD_NEXT;
        return;
    } else if (cmd == BLOCKCMD) {
        // keep running commands until command is unblock
        cmd = ANIMSCR_READ_BYTE;
        while (cmd != OPENCMD) {
            dprintf("running blocking command id %d for script %x in thread %d\n", cmd, (u32)ANIMSCR_SCRIPT, ANIMSCR_THREAD);
            gAnimTable[cmd]();
            ANIMSCR_THREAD = (ANIMSCR_THREAD == 0) ? 3 : ANIMSCR_THREAD - 1;
            cmd = ANIMSCR_READ_BYTE;
        }
        ANIMSCR_CMD_NEXT;
    } else {
        gAnimTable[cmd]();
    }
}
#undef ENDCMD
#undef BLOCKCMD
#undef OPENCMD


/* this will only load the graphics themselves. Later must be initialized as objects */
void ScriptCmd_loadspritefull()
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
    u8 spriteId = CreateSprite(&spriteTemp, 0, 0, 0);
    gSprites[spriteId].final_oam.affine_mode = false;
    gSprites[spriteId].invisible = true;
    VarSet(0x900D, spriteId);
    ANIMSCR_CMD_NEXT;
}

/* load copy of a previously loaded sprite */
void ScriptCmd_loadsprite()
{
    // alignment for read
	ANIMSCR_MOVE(3);
    struct CompressedSpriteSheet* gfx = (struct CompressedSpriteSheet*)ANIMSCR_READ_WORD;
    struct SpritePalette* pal = (struct SpritePalette*)ANIMSCR_READ_WORD;
    struct OamData* oam = (struct OamData*)ANIMSCR_READ_WORD;
    struct Template spriteTemp = {gfx->tag, pal->tag, oam, nullframe, gfx, nullrsf, (SpriteCallback)oac_nullsub};
    u8 spriteId = CreateSprite(&spriteTemp, 0, 0, 0);
    gSprites[spriteId].invisible = true;
    VarSet(0x900D, spriteId);
    ANIMSCR_CMD_NEXT;
}

/* Deletes a sprite from the spriteId */
void ScriptCmd_deletesprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    // read tag
    u16 var = ANIMSCR_READ_HWORD;
    var = VarGet(var);
    FreeSpriteOamMatrix(&gSprites[var]);
    obj_free(&gSprites[var]);
    ANIMSCR_CMD_NEXT;
}

/* show a loaded sprite using it's spriteId */
void ScriptCmd_rendersprite()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    // read tag
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    // read positional arguements
    u16 xcontainer = ANIMSCR_READ_HWORD;
    s16 x = VarGet(xcontainer);
    u16 ycontainer = ANIMSCR_READ_HWORD;
    s16 y = VarGet(ycontainer);
    // read animation data
    struct RotscaleFrame (**rotscale_table)[] = (void*)ANIMSCR_READ_WORD;
    struct Sprite* s = &gSprites[spriteId];
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
    u16 varA = ANIMSCR_READ_HWORD;
    u16 varB = ANIMSCR_READ_HWORD;
    VarSet(varA, VarGet(varA) + VarGet(varB));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_addvars()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 varA = ANIMSCR_READ_HWORD;
    u16 varB = ANIMSCR_READ_HWORD;
    VarSet(varA, VarGet(varA) + VarGet(varB));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_subvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 varA = ANIMSCR_READ_HWORD;
    u16 varB = ANIMSCR_READ_HWORD;
    VarSet(varA, VarGet(varA) - VarGet(varB));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_subvars()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 varA = ANIMSCR_READ_HWORD;
    u16 varB = ANIMSCR_READ_HWORD;
    VarSet(varA, VarGet(varA) - VarGet(varB));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_mulvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) * VarGet(value));
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_divvar()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    VarSet(var, VarGet(var) / VarGet(value));
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
    t->priv[1] = VarGet(t->priv[1]);
    t->priv[2] = ANIMSCR_READ_HWORD; // Delta Y
    t->priv[2] = VarGet(t->priv[2]);
    t->priv[3] = ANIMSCR_READ_HWORD; // Amount of frames to do animation for
    t->priv[4] = ANIMSCR_READ_BYTE; // anim wait
    t->priv[5] = ANIMSCR_THREAD; // execution thread
    // to wait for finish, make sure to put use a waitanim command as the next command.
    ANIMSCR_MOVE(1);
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
    ANIMSCR_MOVE(2);
    bool copyvars = ANIMSCR_READ_BYTE;
    u8* scriptPtr = (u8*)ANIMSCR_READ_WORD;
    // find an unused script pointer and assign animation script to it
    for (u8 i = 0; i < ANIM_SCR_COUNT; i++) {
        if (gAnimationCore->animScriptPtr[i] == NULL) {
            gAnimationCore->animScriptPtr[i] = scriptPtr;
            if (copyvars) {
                for (u8 varId = 0; varId < ANIM_VAR_COUNT; varId++) {
                    gAnimationCore->corevars[i][varId] = gAnimationCore->corevars[ANIMSCR_THREAD][varId];
                }
            } else {
                for (u8 varId = 0; varId < ANIM_VAR_COUNT; varId++) {
                    gAnimationCore->corevars[i][varId] = 0;
                }
            }
            break;
        }
    }
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
    ANIMSCR_WAITING = true;
    ANIMSCR_CMD_NEXT;
}

/* writes an animation struct to a sprite and starts the animation */
void ScriptCmd_animatesprite()
{
    // alignment for read
    u8 index = ANIMSCR_READ_BYTE;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct RotscaleFrame (**rotscale_table)[] = (void*)ANIMSCR_READ_WORD;
    gSprites[spriteId].rotscale_table = rotscale_table;
    gSprites[spriteId].final_oam.affine_mode = 1;
    StartSpriteAffineAnim(&gSprites[spriteId], index);
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
    // temporarily boost up the priority of the copying sprite to appear ABOVE the BG layer until copying is done
    // this keeps ugly tiles from vision because this cmd is not vsynced
    u8 priority = gSprites[spriteId].final_oam.priority;
    gSprites[spriteId].final_oam.priority = 0;
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
    // turn on BG 1 display
    REG_DISPCNT |= DISPCNT_BG1;
    ChangeBgX(1, (-gSprites[spriteId].pos1.x + (4 * width)) * 256, 0);
    ChangeBgY(1, (-gSprites[spriteId].pos1.y + (4 * height)) * 256, 0);
    REG_BG1CNT = BGCNT_PRIORITY1 | BGCNT_TILESTART2 | BGCNT_MAPSTART(30) | BGCNT_TILEMAPSIZE0;
    gSprites[spriteId].final_oam.priority = priority;
    gSprites[spriteId].invisible = true;
}

void CopySpriteToBG1(u8 spriteId, u8 palslotBG, u8 width, u8 height)
{
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
            mapBase[xTile * 32 + yTile] |= offset | (palslotBG << 12);
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
    // turn on BG 1 display
    REG_DISPCNT |= DISPCNT_BG1;
    ChangeBgX(1, (-gSprites[spriteId].pos1.x + (4 * width)) * 256, 0);
    ChangeBgY(1, (-gSprites[spriteId].pos1.y + (4 * height)) * 256, 0);
    REG_BG1CNT = BGCNT_PRIORITY1 | BGCNT_TILESTART2 | BGCNT_MAPSTART(30) | BGCNT_TILEMAPSIZE0;
    gSprites[spriteId].invisible = false;
}


void ScriptCmd_spriteafterimage()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u16 tilewidth = ANIMSCR_READ_HWORD;
    u16 tileheight = ANIMSCR_READ_HWORD;
    CopySpriteToBG1(spriteId, 4, tilewidth, tileheight);
    ANIMSCR_CMD_NEXT;
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
    gSprites[spriteId].invisible = false;
    HideBg(1);
    void* charBase = (void *)0x6008000;
    u16* mapBase = (void*)0x600F000;
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)charBase, CPUModeFS(4096, CPUFSSET));
    CpuFastSet((void*)&set, (void*)mapBase, CPUModeFS(2048, CPUFSSET));
    ANIMSCR_CMD_NEXT;
}

/* Blend sprite bg. This will work if other sprites aren't in the process of blending */
void ScriptCmd_fadespritebg()
{
    // time between color transitions
    u8 delay = ANIMSCR_READ_BYTE;
    // dst color
    u16 blendColor = ANIMSCR_READ_HWORD;
    // fade direction
    u8 dir = ANIMSCR_READ_BYTE;
    // apply delay task or not
    u8 wait = ANIMSCR_READ_BYTE;
    // amount of fade
    u8 amount = ANIMSCR_READ_BYTE;
    if (dir == 0) {
        BeginNormalPaletteFade((1 << 4) , delay, 0x0, amount, blendColor);
    } else {
        BeginNormalPaletteFade((1 << 4) , delay, amount, 0x0, blendColor);
    }
    if (wait != 0) {
        ANIMSCR_WAITING = true;
        u8 taskId = CreateTask(TaskWaitFade, 0);
        tasks[taskId].priv[0] = ANIMSCR_THREAD;
    }
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

/* Given a coefficient for the amount of blending for the sprites and BG 0. Apply blending */
void ScriptCmd_spritesblend()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 coefficientA = ANIMSCR_READ_HWORD;
    coefficientA = VarGet(coefficientA);
    u16 coefficientB = ANIMSCR_READ_HWORD;
    coefficientB = VarGet(coefficientB);
    REG_BLDCNT = (BLDCNT_SPRITES_DST | BLDCNT_BG1_SRC | BLDCNT_ALPHA_BLEND);
    REG_BLDALPHA = BLDALPHA_BUILD(coefficientA, coefficientB);
    ANIMSCR_MOVE(2);
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

/* Include a sprite to blend
   typically only used after a sprite has been excluded
*/
void ScriptCmd_includeblend()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    gSprites[spriteId].final_oam.obj_mode = 0; // semi-transparent
    ANIMSCR_CMD_NEXT;
}

/* Sprite Darken */
void SpriteCmd_darkensprites()
{
    u8 factor = ANIMSCR_READ_BYTE;
    u8 incBgs = ANIMSCR_READ_BYTE;
    u16 blendTargets = (BLDCNT_DARKEN | BLDCNT_SPRITES_SRC);
    if (incBgs & 1)
        blendTargets |= (BLDCNT_BG0_SRC);
    if (incBgs & 2)
        blendTargets |= (BLDCNT_BG1_SRC);
    if (incBgs & 4)
        blendTargets |= (BLDCNT_BG2_SRC);
    if (incBgs & 8)
        blendTargets |= (BLDCNT_BG3_SRC);
    if (incBgs == 0)
        blendTargets |= (BLDCNT_BACKDROP_SRC);

    REG_BLDCNT = blendTargets;
    // darken factor
    REG_BLDY = factor;
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

/* Sprite Lighten */
void SpriteCmd_lightensprites()
{
    u8 factor = ANIMSCR_READ_BYTE;
    u8 incBgs = ANIMSCR_READ_BYTE;
    u16 blendTargets = (BLDCNT_SPRITES_SRC | BLDCNT_LIGHTEN);
    if (incBgs & 1)
        blendTargets |= (BLDCNT_BG0_SRC);
    if (incBgs & 2)
        blendTargets |= (BLDCNT_BG1_SRC);
    if (incBgs & 4)
        blendTargets |= (BLDCNT_BG2_SRC);
    if (incBgs & 8)
        blendTargets |= (BLDCNT_BG3_SRC);
    if (incBgs & 16)
        blendTargets |= (BLDCNT_BACKDROP_SRC);
    REG_BLDCNT = blendTargets;
    // lighten factor
    REG_BLDY = factor;
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

/* clears the current thread's palette buffer */
void ScripCmd_clearpalbuff()
{
    ANIMSCR_MOVE(3);
    ANIMSCR_PALBUFF = 0;
    ANIMSCR_CMD_NEXT;
}

/* add a sprite to the current thread's palette buffer. */
void ScriptCmd_palbufferspriteandbgs()
{
    u8 incBgs = ANIMSCR_READ_BYTE;
    u32 palbuff = ANIMSCR_PALBUFF;
    if (incBgs != 0)
        palbuff |= 0xFFFF;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u8 palSlot = gSprites[spriteId].final_oam.palette_num;
    ANIMSCR_PALBUFF |= ((1 << (palSlot + 16)));
    ANIMSCR_CMD_NEXT;
}

/* Pal fading on buffered sprites and BGs */
void ScriptCmd_palfade()
{
    // time between color transitions
    u8 delay = ANIMSCR_READ_BYTE;
    // dst color
    u16 blendColor = ANIMSCR_READ_HWORD;
    // fade direction
    u8 dir = ANIMSCR_READ_BYTE;
    // apply delay task or not
    u8 wait = ANIMSCR_READ_BYTE;
    // amount of fade
    u8 amount = ANIMSCR_READ_BYTE;
    if (dir == 0) {
        BeginNormalPaletteFade(ANIMSCR_PALBUFF , delay, 0x0, amount, blendColor);
    } else {
        BeginNormalPaletteFade(ANIMSCR_PALBUFF , delay, amount, 0x0, blendColor);
    }
    if (wait != 0) {
        ANIMSCR_WAITING = true;
        u8 taskId = CreateTask(TaskWaitFade, 0);
        tasks[taskId].priv[0] = ANIMSCR_THREAD;
    }
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

/* move sprite in a wave with amplitude and slope */
#define bounces sprite->data[0]
#define bouncesPast sprite->data[3]
#define xDelta sprite->data[1]
#define yDelta sprite->data[2]
#define X sprite->data[4]
#define amplitude sprite->data[5]
#define deltaError sprite->data[6]
#define frequency sprite->data[7]
void SCBWaveMovement(struct Sprite* sprite)
{
    sprite->pos1.x +=xDelta;
    sprite->pos1.y += yDelta;
    bouncesPast += 1;
    u8 xerror = deltaError >> 8;
    u8 yerror = deltaError & 0xFF;
    if (bouncesPast % xerror == 0)
        sprite->pos1.x += xDelta > 0 ? 1 : -1;
    if (bouncesPast % yerror == 0)
        sprite->pos1.y += yDelta > 0 ? 1 : -1;
    if (bouncesPast > bounces)
        sprite->callback = oac_nullsub;
    // apply sin curve to Y position
    if (yDelta < 0)
        sprite->pos1.y -= Sin(X, amplitude);
    else
        sprite->pos1.y += Sin(X, amplitude);
    // update wave frequency
    X = (X + frequency) & 0xFF;
}

void SpriteCmd_movewave()
{
    // steps needed to reach DST
    u8 steps = ANIMSCR_READ_BYTE;
    // get sprites
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u16 destSpriteId = ANIMSCR_READ_HWORD;
    destSpriteId = VarGet(destSpriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    struct Sprite* s2 = &gSprites[destSpriteId];
    X = 0; // starts sin(x) on X = 0. Can phase shift forward, not backwards
    bounces = steps;
    amplitude = (s8)ANIMSCR_READ_BYTE;
    frequency = ANIMSCR_READ_BYTE;
    frequency = (256 / steps) * frequency;
    // calculate delta distances per bounce
    s32 x = s2->pos1.x - sprite->pos1.x;
    s32 y = s2->pos1.y - sprite->pos1.y;
    xDelta = Div(x, bounces);
    yDelta = Div(y, bounces);
    u16 xerr = ABS((bounces / (x - (xDelta * bounces)))); // error minimization increment intervals
    u16 yerr = ABS((bounces / (y - (yDelta * bounces)))); // error minimization increment intervals
    deltaError = ((xerr << 8) | (yerr & 0xFF));
    // Animate sprite bounce given parameters
    sprite->callback = SCBWaveMovement;
    ANIMSCR_CMD_NEXT;
}

#undef bounces
#undef bouncesPast
#undef xDelta
#undef yDelta
#undef X
#undef amplitude
#undef waveOrBounce
#undef frequency

/* Upload a BG to BG2.. */
void ScriptCmd_uploadbg()
{
    // alignment purposes
    ANIMSCR_MOVE(1);
    HideBg(2);
    void* charBase = (void*)0x6004000;
    void* mapBase = (void*)0x600E800;
    // load graphical assets tileset
    u16 palSize = ANIMSCR_READ_HWORD;
    void* tileset = (void*)ANIMSCR_READ_WORD;
    void* tilemap = (void*)ANIMSCR_READ_WORD;
    u16* palette = (void*)ANIMSCR_READ_WORD;
    // commit assets to BG
    lz77UnCompVram(tileset, charBase);
    lz77UnCompVram(tilemap, mapBase);
    LoadPalette_compressed(palette, 16 * 9, palSize);
    ANIMSCR_CMD_NEXT;
}

/* Show and hide BGs */
void ScriptCmd_showbg()
{
    u8 bgid = ANIMSCR_READ_BYTE;
    ShowBg(bgid);
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

void ScriptCmd_hidebg()
{
    u8 bgid = ANIMSCR_READ_BYTE;
    HideBg(bgid);
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

/* Flash BG */

/* Flash sprite */
void ScriptCmd_flashsprite()
{
    ANIMSCR_MOVE(1);
    u8 flashDuration = ANIMSCR_READ_BYTE;
    u8 timesToFlash = ANIMSCR_READ_BYTE;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u8 taskId = CreateTask(TaskFlashSprite, 0);
    tasks[taskId].priv[0] = spriteId;
    tasks[taskId].priv[1] = flashDuration;
    tasks[taskId].priv[2] = timesToFlash;
    tasks[taskId].priv[3] = ANIMSCR_THREAD;
    tasks[taskId].priv[4] = ANIMSCR_READ_BYTE;
    tasks[taskId].priv[5] = ANIMSCR_READ_HWORD;
    ANIMSCR_MOVE(3);
    ANIMSCR_CMD_NEXT;
}

/* Set attacker to var */
void ScriptCmd_getattacker()
{
    ANIMSCR_MOVE(3);
    VarSet(0x9000, gPkmnBank[ACTION_BANK]->objid);
    ANIMSCR_CMD_NEXT;
}

/* Set defender to var */
void ScriptCmd_getdefender()
{
    ANIMSCR_MOVE(3);
    VarSet(0x9001, gPkmnBank[ACTION_TARGET]->objid);
    ANIMSCR_CMD_NEXT;
}

/* Set attacker coords */
void ScriptCmd_getattackercoords()
{
    ANIMSCR_MOVE(3);
    struct Sprite* sprite = &gSprites[gPkmnBank[ACTION_BANK]->objid];
    VarSet(0x9002, sprite->pos1.x);
    VarSet(0x9004, sprite->pos1.y);
    ANIMSCR_CMD_NEXT;
}

/* Set defender coords */
void ScriptCmd_getdefendercoords()
{
    ANIMSCR_MOVE(3);
    struct Sprite* sprite = &gSprites[gPkmnBank[ACTION_TARGET]->objid];
    VarSet(0x9003, sprite->pos1.x);
    VarSet(0x9005, sprite->pos1.y);
    ANIMSCR_CMD_NEXT;
}

/* Side of a mon given it's sprite Id */
void ScriptCmd_sideofsprite()
{
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId) & 0xFF;
    if (gPkmnBank[ACTION_BANK]->objid == spriteId) {
        ANIMSCR_CONDITION = SIDE_OF(ACTION_BANK);
    } else {
        ANIMSCR_CONDITION = SIDE_OF(ACTION_TARGET);
    }
    ANIMSCR_CMD_NEXT;
}

/* Quake BG */
void ScriptCmd_quakebg()
{
    u8 taskId = CreateTask(TaskQuakeBg, 0);
    tasks[taskId].priv[0] = ANIMSCR_READ_BYTE; // bgid
    tasks[taskId].priv[1] = ANIMSCR_READ_BYTE; // xquake
    tasks[taskId].priv[2] = ANIMSCR_READ_BYTE; // yquake
    tasks[taskId].priv[3] = ANIMSCR_READ_BYTE; // times
    tasks[taskId].priv[4] = ANIMSCR_READ_BYTE; // delay
    tasks[taskId].priv[10] = ANIMSCR_READ_BYTE; // wait bool
    tasks[taskId].priv[11] = ANIMSCR_THREAD; // thread
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

/* Quake Sprite */
void ScriptCmd_quakesprite()
{
    ANIMSCR_MOVE(1);
    u8 taskId = CreateTask(TaskQuakeSprite, 0);
    u16 var = ANIMSCR_READ_HWORD;
    var = VarGet(var);
    tasks[taskId].priv[0] = var; // spriteid
    tasks[taskId].priv[1] = ANIMSCR_READ_BYTE; // xquake
    tasks[taskId].priv[2] = ANIMSCR_READ_BYTE; // yquake
    tasks[taskId].priv[3] = ANIMSCR_READ_BYTE; // times
    tasks[taskId].priv[4] = ANIMSCR_READ_BYTE; // delay
    tasks[taskId].priv[10] = ANIMSCR_READ_BYTE; // wait bool
    tasks[taskId].priv[11] = ANIMSCR_THREAD; // thread
    ANIMSCR_MOVE(3);
    ANIMSCR_CMD_NEXT;
}

/* Call */
void ScriptCmd_call()
{
    ANIMSCR_MOVE(3);
    u8* callLocation = (u8*)ANIMSCR_READ_WORD;
    gAnimationCore->callStack[ANIMSCR_THREAD][ANIMSCR_STACKDEPTH] = ANIMSCR_SCRIPT;
    ANIMSCR_STACKDEPTH++;
    ANIMSCR_SCRIPT = callLocation;
    ANIMSCR_CMD_NEXT;
}

/* Return */
void ScriptCmd_return()
{
    ANIMSCR_SCRIPT = gAnimationCore->callStack[ANIMSCR_THREAD][ANIMSCR_STACKDEPTH - 1];
    ANIMSCR_STACKDEPTH--;
    ANIMSCR_CMD_NEXT;
}

/* if */
void ScriptCmd_if()
{
    bool condition = ANIMSCR_READ_BYTE;
    ANIMSCR_MOVE(2);
    if (ANIMSCR_CONDITION != condition) {
        // skip the condition true clause. This is 1 command and a script arg - 8 bytes including the padding
        ANIMSCR_MOVE(8);
    }
    ANIMSCR_CMD_NEXT;
}

/* compare var to value */
void ScriptCmd_compare()
{
    ANIMSCR_MOVE(1);
    u16 var = ANIMSCR_READ_HWORD;
    u16 value = ANIMSCR_READ_HWORD;
    ANIMSCR_MOVE(2);
    var = VarGet(var);
    if (var < value) {
        ANIMSCR_CONDITION = 0;
    } else if (var == value) {
        ANIMSCR_CONDITION = 1;
    } else if (var > value) {
        ANIMSCR_CONDITION = 2;
    } else if (var <= value) {
        ANIMSCR_CONDITION = 3;
    } else if (var >= value) {
        ANIMSCR_CONDITION = 4;
    }
    ANIMSCR_CMD_NEXT;
}

/* compare var to var */
void ScriptCmd_comparevars()
{
    ANIMSCR_MOVE(1);
    u16 varA = ANIMSCR_READ_HWORD;
    u16 varB = ANIMSCR_READ_HWORD;
    ANIMSCR_MOVE(2);
    varA = VarGet(varA);
    varB = VarGet(varB);
    if (varA < varB) {
        ANIMSCR_CONDITION = 0;
    } else if (varA == varB) {
        ANIMSCR_CONDITION = 1;
    } else if (varA > varB) {
        ANIMSCR_CONDITION = 2;
    } else if (varA <= varB) {
        ANIMSCR_CONDITION = 3;
    } else if (varA >= varB) {
        ANIMSCR_CONDITION = 4;
    }
    ANIMSCR_CMD_NEXT;
}

/* fast get all battlers into predetermined vars */
#define attacker 0x9000
#define defender 0x9001
#define attackerx 0x9002
#define targetx 0x9003
#define attackery 0x9004
#define targety 0x9005
void ScriptCmd_fastsetbattlers()
{
    ANIMSCR_MOVE(3);
    u8 sprattacker = gPkmnBank[ACTION_BANK]->objid;
    u8 sprtarget = gPkmnBank[ACTION_TARGET]->objid;
    VarSet(attacker, sprattacker);
    VarSet(defender, sprtarget);
    VarSet(targetx, gSprites[sprtarget].pos1.x);
    VarSet(targety, gSprites[sprtarget].pos1.y);
    VarSet(attackerx, gSprites[sprattacker].pos1.x);
    VarSet(attackery, gSprites[sprattacker].pos1.y);
    ANIMSCR_CMD_NEXT;
}
#undef attacker
#undef defender
#undef targetx
#undef targety
#undef attacker
#undef attackery

/* Shake HP box of a sprite */
void ScriptCmd_shakehpbox()
{
    ANIMSCR_MOVE(1);
    u16 shakehpof = ANIMSCR_READ_HWORD;
    shakehpof = VarGet(shakehpof);
    u8 bank;
    if (gPkmnBank[ACTION_BANK]->objid == shakehpof) {
        bank = ACTION_BANK;
    } else {
        bank = ACTION_TARGET;
    }
    u8 taskId = CreateTask(TaskHPBoxBobFast, 0);
    tasks[taskId].priv[0] = bank;
    ANIMSCR_CMD_NEXT;
}

/* random range */
void ScriptCmd_randrange()
{
    ANIMSCR_MOVE(1);
    u16 min = ANIMSCR_READ_HWORD;
    u16 max = ANIMSCR_READ_HWORD;
    var_800D = rand_range(min, max);
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

/* Run task */
void ScriptCmd_runtask()
{
    s8 arg = ANIMSCR_READ_BYTE;
    u16 arg2 = ANIMSCR_READ_HWORD;
    u16 arg3 = ANIMSCR_READ_HWORD;
    u16 vararg = ANIMSCR_READ_HWORD;
    TaskCallback t = (TaskCallback)ANIMSCR_READ_WORD;
    u8 taskId = CreateTask(t, 0);
    tasks[taskId].priv[1] = VarGet(vararg);
    tasks[taskId].priv[2] = VarGet(arg);
    tasks[taskId].priv[3] = VarGet(arg2);
    tasks[taskId].priv[4] = VarGet(arg3);
    ANIMSCR_CMD_NEXT;
}

/* wait for a running task to finish */
void ScriptCmd_waittask()
{
    ANIMSCR_MOVE(3);
    u8 taskId = CreateTask(TaskWaitForTask, 0);
    u32* arg = (u32*)&tasks[taskId].priv[0];
    *arg = ANIMSCR_READ_WORD;
    tasks[taskId].priv[3] = ANIMSCR_THREAD;
    ANIMSCR_WAITING = true;
    ANIMSCR_CMD_NEXT;
}

/* Set frames */
void ScriptCmd_setframessprite()
{
    u8 frame = ANIMSCR_READ_BYTE;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    void* frames = (void*)ANIMSCR_READ_WORD;
    gSprites[spriteId].animation_table = (void*)frames;
    gSprites[spriteId].animNum = frame;
    gSprites[spriteId].animBeginning = true;
    gSprites[spriteId].animEnded = false;
    ANIMSCR_CMD_NEXT;
}

/* Set up a sprite's private variables for horizontal arc movement */
// Meant to be called in conjunction with TaskTranslateSpriteHorizontalArc
// used with the pokeball. For general use, use the one below this function
void ScriptCmd_confighorizontalarctranslate()
{
    u8 speed = ANIMSCR_READ_BYTE;
    s16 startAngle = ANIMSCR_READ_HWORD;
    s16 endAngle = ANIMSCR_READ_HWORD;
    u16 spriteId = ANIMSCR_READ_HWORD;
    u16 spriteIdDst = ANIMSCR_READ_HWORD;
    u8 mode = ANIMSCR_READ_BYTE;
    // get sprites
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    spriteIdDst = VarGet(spriteIdDst);
    struct Sprite* spriteDst = &gSprites[spriteIdDst];
    // get total distances for x and y
    s32 x = (spriteDst->pos1.x - sprite->pos1.x);
    s32 y;
    switch (mode) {
        case 0:
            y = -((spriteDst->pos1.y - sprite->pos1.y) + sprite->pos1.y + 40); // peak is 40px over
            break;
        case 1:
            y = -((spriteDst->pos1.y - sprite->pos1.y) + sprite->pos1.y); // normal player side
            break;
        default:
            y = -sprite->pos1.y; // normal opponent's side
            break;
    };
    sprite->data[0] = speed; // intervals to travel distance
    sprite->data[1] = endAngle;
    sprite->data[2] = Div((x * 256), speed);
    sprite->data[3] = sprite->pos1.y;
    sprite->data[4] = speed / (x - ((sprite->data[2] / 256) * speed)); // error minimization increment intervals
    sprite->data[5] = y;
    // calc frequency required
    sprite->data[6] = ABS(endAngle - startAngle) /  speed; // frequency step
    sprite->data[7] = startAngle; // frequency start
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

// Make spriteA orbit spriteB with given customizations
void ScriptCmd_orbit()
{
    bool wait = ANIMSCR_READ_BYTE;
    // spriteA
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // spriteB
    spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* toOrbit = &gSprites[spriteId];

    toOrbit->final_oam.priority = 2;
    sprite->data[0] = ANIMSCR_READ_HWORD; // duration
    sprite->data[0] = MAX(1, sprite->data[0]);
    sprite->data[2] = ANIMSCR_READ_BYTE; // width
    sprite->data[3] = ANIMSCR_READ_BYTE; // height
    u8 direction = ANIMSCR_READ_BYTE; // direction
    if (direction) {
        // left
        sprite->data[2] = -sprite->data[2];
        sprite->data[3] = -sprite->data[3];
    }
    sprite->data[4] = ANIMSCR_READ_BYTE; // speed
    // animation should pause script thread or not
    if (wait) {
        sprite->data[6] = ANIMSCR_THREAD;
        sprite->data[6] += 1;
        ANIMSCR_WAITING = true;
    } else {
        sprite->data[6] = 0;
    }
    sprite->data[5] = ANIMSCR_READ_BYTE; // bool to delete
    sprite->data[1] = ANIMSCR_READ_HWORD; // wave offset (0 - 255)
    sprite->data[1] = VarGet(sprite->data[1]);
    sprite->data[7] = toOrbit->final_oam.priority;
    sprite->callback = AnimOrbitFastStep;
    sprite->callback(sprite);
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}


// wait for frame animation of sprite to finish
void ScriptCmd_waitanimation()
{
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    if (!gSprites[spriteId].animEnded) {
        ANIMSCR_WAITING = true;
        u8 taskId = CreateTask(TaskWaitAnimation, 0);
        tasks[taskId].priv[0] = spriteId;
    }
    ANIMSCR_CMD_NEXT;
}

// wait for affine animation on a sprite to complete
void ScriptCmd_waitaffineanimation()
{
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    if (!gSprites[spriteId].affineAnimEnded) {
        ANIMSCR_WAITING = true;
        u8 taskId = CreateTask(TaskWaitAffineAnimation, 0);
        tasks[taskId].priv[0] = spriteId;
        tasks[taskId].priv[1] = ANIMSCR_THREAD;
    }
    ANIMSCR_CMD_NEXT;
}

// set sprite callback
void ScriptCmd_spritecallback()
{
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    ClearSpriteData(&gSprites[spriteId]);
    gSprites[spriteId].callback = (SpriteCallback)ANIMSCR_READ_WORD;
    ANIMSCR_CMD_NEXT;
}

// hide the hp bars of a given pokemon sprite
void ScriptCmd_hidehpbars()
{
	ANIMSCR_MOVE(3);
	for (u8 i = 0; i < BANK_MAX; i++) {
		if (!ACTIVE_BANK(i)) continue;
		// hide HP bars of this sprite
		gSprites[gPkmnBank[i]->objid_hpbox[0]].invisible = true;
		gSprites[gPkmnBank[i]->objid_hpbox[1]].invisible = true;
		gSprites[gPkmnBank[i]->objid_hpbox[2]].invisible = true;
		gSprites[gPkmnBank[i]->objid_hpbox[3]].invisible = true;
	}
	ANIMSCR_CMD_NEXT;
}

// show the hp bars of a given pokemon sprite
void ScriptCmd_showhpbars()
{
	ANIMSCR_MOVE(3);
	for (u8 i = 0; i < BANK_MAX; i++) {
		if (!ACTIVE_BANK(i)) continue;
		// hide HP bars of this sprite
		gSprites[gPkmnBank[i]->objid_hpbox[0]].invisible = false;
		gSprites[gPkmnBank[i]->objid_hpbox[1]].invisible = false;
		gSprites[gPkmnBank[i]->objid_hpbox[2]].invisible = false;
		gSprites[gPkmnBank[i]->objid_hpbox[3]].invisible = false;
	}
	ANIMSCR_CMD_NEXT;
}

// move a bg
void ScriptCmd_movebg()
{
    struct Task* t = &tasks[CreateTask(TaskMoveBG, 0)];
    t->priv[0] = ANIMSCR_READ_BYTE; // bg id
    t->priv[1] = ANIMSCR_READ_HWORD; // Delta X
    t->priv[2] = ANIMSCR_READ_HWORD; // Delta Y
    t->priv[3] = ANIMSCR_READ_BYTE; // Amount of frames to do animation for
    t->priv[4] = ANIMSCR_READ_BYTE; // if we need to wait
    t->priv[5] = ANIMSCR_THREAD;  // thread
    t->priv[7] = ANIMSCR_READ_BYTE;  // direction
    ANIMSCR_MOVE(3);
    ANIMSCR_CMD_NEXT;
}

// copy an action variable from the current action to a script variable
void ScriptCmd_copyactionpriv()
{
    u8 privId = ANIMSCR_READ_BYTE;
    u16 var = ANIMSCR_READ_HWORD;
    VarSet(var, CURRENT_ACTION->priv[privId]);
    ANIMSCR_CMD_NEXT;
}

// blend a sprite without using the fade structure
void ScriptCmd_spriteblend2()
{
    ANIMSCR_MOVE(1);
    u8 coefficient = ANIMSCR_READ_HWORD;
    coefficient = VarGet(coefficient);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u16 color = ANIMSCR_READ_HWORD;
    color = VarGet(color);
    u8 pal_slot = gSprites[spriteId].final_oam.palette_num;
    BlendPalette((pal_slot * 16) + (16 * 16), 16, coefficient, color);
    ANIMSCR_CMD_NEXT;
}

// buffer a sprite's position into passed vars
void ScriptCmd_spritebufferposition()
{
    ANIMSCR_MOVE(1);
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    u16 buffx = ANIMSCR_READ_HWORD;
    u16 buffy = ANIMSCR_READ_HWORD;
    VarSet(buffx, gSprites[spriteId].pos1.x);
    VarSet(buffy, gSprites[spriteId].pos1.y);
    ANIMSCR_CMD_NEXT;
}

// play a message
void ScriptCmd_playmessage()
{
    ANIMSCR_MOVE(3);
    u16 bank = ANIMSCR_READ_HWORD;
    bank = VarGet(bank);
    u16 move = ANIMSCR_READ_HWORD;
    move = VarGet(move);
    enum battle_string_ids id = ANIMSCR_READ_HWORD;
    u16 effect = ANIMSCR_READ_HWORD;
    effect = VarGet(effect);
    pick_battle_message(move, bank, battle_type_flag, id, effect);
    ShowBattleMessage2((u8*)string_buffer, 0x1);
    CreateTask(TaskWaitAnimMessage, 0);
    // to wait for the cmd to finish, you must use waittask on TaskWaitAnimMessage
    ANIMSCR_CMD_NEXT;
}

// move sprite to another sprite linearly
void ScriptCmd_movespritedst()
{
    u8 steps = ANIMSCR_READ_BYTE;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    u16 spriteId2 = ANIMSCR_READ_HWORD;
    spriteId2 = VarGet(spriteId2);
    struct Sprite* s2 = &gSprites[spriteId2];

    // calculate delta distances per movement
    s32 x = s2->pos1.x - sprite->pos1.x;
    s32 y = s2->pos1.y - sprite->pos1.y;
    s16 xDelta = Div(x, steps);
    s16 yDelta = Div(y, steps);

    sprite->callback = SCBMoveSpriteErrorCorrection;
    sprite->data[0] = steps;
    sprite->data[1] = xDelta;
    sprite->data[2] = yDelta;
    sprite->data[3] = steps / (x - (xDelta * steps)); // error minimization increment intervals
    sprite->data[4] = steps / (y - (yDelta * steps)); // error minimization increment intervals

    // to wait for finish, make sure to put use a waitanim command as the next command.
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

// blend sprites, on all layers including BG 3
/* Given a coefficient for the amount of blending for the sprites and BG 0. Apply blending */
void ScriptCmd_spritesblendall()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 coefficientA = ANIMSCR_READ_HWORD;
    coefficientA = VarGet(coefficientA);
    u16 coefficientB = ANIMSCR_READ_HWORD;
    coefficientB = VarGet(coefficientB);
    REG_BLDCNT = (BLDCNT_BG1_SRC | BLDCNT_BG3_SRC | BLDCNT_SPRITES_DST | BLDCNT_ALPHA_BLEND);
    REG_BLDALPHA = BLDALPHA_BUILD(coefficientA, coefficientB);
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

// sets the priority of a sprite
void ScriptCmd_setpriority()
{
    // alignment for read
    u8 priority = ANIMSCR_READ_BYTE;
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    gSprites[spriteId].final_oam.priority = priority;
    ANIMSCR_CMD_NEXT;
}

// sets the priority of a BG
void ScriptCmd_setprioritybg()
{
    // alignment for read
    u8 priority = ANIMSCR_READ_BYTE;
    u8 bgid = ANIMSCR_READ_BYTE;
    switch (bgid) {
        case 1:
            REG_BG1CNT &= ~3;
            REG_BG1CNT |= priority;
            break;
        case 2:
            REG_BG2CNT &= ~3;
            REG_BG2CNT |= priority;
            break;
        case 3:
            REG_BG3CNT &= ~3;
            REG_BG3CNT |= priority;
            break;
    }
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

// Clears REGBLD
void ScriptCmd_clearblending()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    REG_BLDCNT = 0;
    REG_BLDALPHA = 0;
    ANIMSCR_CMD_NEXT;
}

// Run the firework effect with a generic sprite
void ScriptCmd_fireworkeffect()
{
    ANIMSCR_MOVE(2);
    u8 argbits = ANIMSCR_READ_BYTE;
    u32 pgfx = ANIMSCR_READ_WORD;
    u32 ppal = ANIMSCR_READ_WORD;
    u32 poam = ANIMSCR_READ_WORD;
    u32 affine = ANIMSCR_READ_WORD;
    s16 currentx = ANIMSCR_READ_HWORD;
    s16 currenty = ANIMSCR_READ_HWORD;

    u8 blend = argbits & 1;
    u8 left = argbits & 1;
    currentx = VarGet(currentx);
    currentx += left ? rand_range(0, 10) - 10 : rand_range(0, 10);
    currenty = VarGet(currenty);
    currenty += rand_range(0, 20) - 10;
    struct CompressedSpriteSheet* gfx = (struct CompressedSpriteSheet*)pgfx;
    struct SpritePalette* pal = (struct SpritePalette*)ppal;
    struct OamData* oam = (struct OamData*)poam;
    struct Template spriteTemp = {gfx->tag, pal->tag, oam, nullframe, gfx, (void*)affine, (SpriteCallback)oac_nullsub};
    u8 spriteId = CreateSprite(&spriteTemp, currentx, currenty, 0);
    struct RotscaleFrame (**rotscale_table)[] = (void*)affine;
    gSprites[spriteId].rotscale_table = rotscale_table;
    gSprites[spriteId].final_oam.affine_mode = 1;
    gSprites[spriteId].final_oam.priority = 3;
    if (!blend) {
        gSprites[spriteId].final_oam.obj_mode = 1;
        gSprites[spriteId].final_oam.priority = 1;
    }
    struct Task* t = &tasks[CreateTask(TaskCreateSmallFireworkGeneric, 0)];
    t->priv[1] = spriteId;
    t->priv[3] = currentx;
    t->priv[4] = currenty;
    // acceleration. Y must be always negative
    t->priv[8] = 1;
    t->priv[9] = 2;
    // initial velocities
    t->priv[5] = left ? -rand_range(1, 3) : rand_range(1, 3);
    t->priv[6] = -(rand_range(1, 4));
    ANIMSCR_CMD_NEXT;
}

// puts a random number between two given numbers in var 0x900D, lastresult
void ScriptCmd_random()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    u16 min = ANIMSCR_READ_HWORD;
    u16 max = ANIMSCR_READ_HWORD;
    VarSet(0x900D, rand_range(min, max));
    ANIMSCR_CMD_NEXT;
}

/* Blend platform bg. This will work if other sprites aren't in the process of blending */
void ScriptCmd_fadeplatformbg()
{
    ANIMSCR_MOVE(3);
    ANIMSCR_PALBUFF |= (1 << 0);
    ANIMSCR_CMD_NEXT;
}


// Make spriteA orbit spriteB with given customizations
void ScriptCmd_depthlessorbit()
{
    bool wait = ANIMSCR_READ_BYTE;
    // spriteA
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // spriteB
    spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* toOrbit = &gSprites[spriteId];

    toOrbit->final_oam.priority = 2;
    sprite->data[0] = ANIMSCR_READ_HWORD; // duration
    sprite->data[0] = MAX(1, sprite->data[0]);
    sprite->data[2] = ANIMSCR_READ_BYTE; // width
    sprite->data[3] = ANIMSCR_READ_BYTE; // height
    u8 direction = ANIMSCR_READ_BYTE; // direction
    if (direction) {
        // left
        sprite->data[2] = -sprite->data[2];
        sprite->data[3] = -sprite->data[3];
    }
    sprite->data[4] = ANIMSCR_READ_BYTE; // speed
    // animation should pause script thread or not
    if (wait) {
        sprite->data[6] = ANIMSCR_THREAD;
        sprite->data[6] += 1;
        ANIMSCR_WAITING = true;
    } else {
        sprite->data[6] = 0;
    }
    sprite->data[5] = ANIMSCR_READ_BYTE; // bool to delete
    sprite->data[1] = ANIMSCR_READ_HWORD; // wave offset (0 - 255) var
    sprite->data[1] = VarGet(sprite->data[1]);
    sprite->data[7] = toOrbit->final_oam.priority;
    sprite->callback = AnimOrbitFastStepNoPriority;
    sprite->callback(sprite);
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

// Make spriteA orbit spriteB with given customizations
void ScriptCmd_shrinkingorbit()
{
    bool wait = ANIMSCR_READ_BYTE;
    // spriteA
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // spriteB
    spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* toOrbit = &gSprites[spriteId];

    toOrbit->final_oam.priority = 2;
    sprite->data[0] = ANIMSCR_READ_HWORD; // duration
    sprite->data[0] = MAX(1, sprite->data[0]);
    sprite->data[2] = ANIMSCR_READ_BYTE; // width
    sprite->data[3] = ANIMSCR_READ_BYTE; // height
    u8 direction = ANIMSCR_READ_BYTE; // direction
    if (direction) {
        // left
        sprite->data[2] = -sprite->data[2];
        sprite->data[3] = -sprite->data[3];
    }
    sprite->data[4] = ANIMSCR_READ_BYTE; // speed
    // animation should pause script thread or not
    if (wait) {
        sprite->data[6] = ANIMSCR_THREAD;
        sprite->data[6] += 1;
        ANIMSCR_WAITING = true;
    } else {
        sprite->data[6] = 0;
    }
    sprite->data[5] = ANIMSCR_READ_BYTE; // bool to delete
    sprite->data[1] = ANIMSCR_READ_HWORD; // wave offset (0 - 255)
    sprite->data[1] = VarGet(sprite->data[1]);
    sprite->data[7] = toOrbit->final_oam.priority;
    sprite->callback = AnimOrbitShrinkNoPriority;
    sprite->callback(sprite);
    ANIMSCR_MOVE(1);
    ANIMSCR_CMD_NEXT;
}

// set a sprite's position to the given position
void ScriptCmd_spritesetposition()
{
    ANIMSCR_MOVE(1);
    // sprite
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // positions
    s16 posx = ANIMSCR_READ_HWORD;
    s16 posy = ANIMSCR_READ_HWORD;
    posx = VarGet(posx);
    posy = VarGet(posy);
    sprite->pos1.x = posx;
    sprite->pos1.y = posy;
    ANIMSCR_CMD_NEXT;
}

// assign a sprite callback with args
void ScriptCmd_spritecallbackargs()
{
    ANIMSCR_MOVE(1);
    // sprite
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // clear sprite args
    ClearSpriteData(sprite);
    // read args
    sprite->data[0] = ANIMSCR_READ_HWORD;
    sprite->data[0] = VarGet(sprite->data[0]);
    sprite->data[1] = ANIMSCR_READ_HWORD;
    sprite->data[1] = VarGet(sprite->data[1]);
    sprite->data[2] = ANIMSCR_READ_HWORD;
    sprite->data[2] = VarGet(sprite->data[2]);
    sprite->data[3] = ANIMSCR_READ_HWORD;
    sprite->data[3] = VarGet(sprite->data[3]);
    // read and assign callback
    sprite->callback = (void*)ANIMSCR_READ_WORD;
    ANIMSCR_CMD_NEXT;
}

// run a spritecallback once
void ScriptCmd_runspritefunc()
{
    ANIMSCR_MOVE(1);
    // sprite
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    struct Sprite* sprite = &gSprites[spriteId];
    // func
    SpriteCallback sprcb = (SpriteCallback)ANIMSCR_READ_WORD;
    sprcb(sprite);
    ANIMSCR_CMD_NEXT;
}

// Blend semi transparent sprites only
void ScriptCmd_blendsemitransparent()
{
    // alignment for read
    ANIMSCR_MOVE(1);
    u16 coefficientA = ANIMSCR_READ_HWORD;
    coefficientA = VarGet(coefficientA);
    u16 coefficientB = ANIMSCR_READ_HWORD;
    coefficientB = VarGet(coefficientB);
    REG_BLDCNT = (BLDCNT_BG0_DST | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST | BLDCNT_SPRITES_DST |
        BLDCNT_BACKDROP_DST | BLDCNT_ALPHA_BLEND);
    REG_BLDALPHA = BLDALPHA_BUILD(coefficientA, coefficientB);
    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}

// run a void function
void ScriptCmd_runvoidfunc()
{
    // alignment for read
    ANIMSCR_MOVE(3);
    MainCallback func = (MainCallback)ANIMSCR_READ_WORD;
    func();
    ANIMSCR_CMD_NEXT;
}


// A slow fall like a feather
void ScriptCmd_spritefeatherfall()
{
    bool toDelete = ANIMSCR_READ_BYTE;
    // sprite
    u16 spriteId = ANIMSCR_READ_HWORD;
    spriteId = VarGet(spriteId);
    // Amplitude
    s16 amplitude = ANIMSCR_READ_HWORD;
    amplitude = VarGet(amplitude);
    // frequency
    u16 frequency = ANIMSCR_READ_HWORD;
    frequency = VarGet(frequency);
    // duration
    u16 duration = ANIMSCR_READ_HWORD;
    duration = VarGet(duration);

    struct Sprite* spr = &gSprites[spriteId];
    ClearSpriteData(spr);
    spr->data[0] = ANIMSCR_READ_BYTE; // delay
    spr->data[1] = ANIMSCR_READ_BYTE; // speed y
    spr->data[2] = amplitude;
    spr->data[3] = frequency;
    spr->data[4] = duration;
    spr->data[5] = toDelete;
    spr->callback = (SpriteCallback)SCB_SpriteFeatherFall;
    ANIMSCR_CMD_NEXT;
}

// command picks a random position of a centered sprite
void ScriptCmd_pickrandompos()
{
    ANIMSCR_MOVE(1);
    u16 targetX = ANIMSCR_READ_HWORD;
    u16 targetY = ANIMSCR_READ_HWORD;
    s16 x = VarGet(targetX);
    s16 y = VarGet(targetY);
    // xRange
    u16 xRange = ANIMSCR_READ_HWORD;
    xRange = VarGet(xRange);
    // yRange
    u16 yRange = ANIMSCR_READ_HWORD;
    yRange = VarGet(yRange);

    x -= xRange / 2;
    y -= yRange / 2;
    VarSet(targetX, rand_range(0, xRange) + x);
    VarSet(targetY, rand_range(0, yRange) + y);

    ANIMSCR_MOVE(2);
    ANIMSCR_CMD_NEXT;
}


void AnimationMain()
{
    u8 counter = 0;
    for (u8 i = 0; i < ANIM_SCR_COUNT; i++) {
        if (gAnimationCore->waitAll)
            return;
        if (gAnimationCore->wait[i] || (gAnimationCore->animScriptPtr[i] == 0)) {
            ANIMSCR_CMD_NEXT;
            if ((gAnimationCore->animScriptPtr[i] == 0))
                counter++;
        } else {
            RunCurrentCommand();
        }
    }
    if (counter == ANIM_SCR_COUNT) {
        // all threads complete. Return
        free(gAnimationCore);
        end_action(CURRENT_ACTION);
        SetMainCallback(battle_loop);
    }
}


void event_play_animation(struct action* current_action)
{
    InitializeAnimationCore((u8*)current_action->script, NULL, NULL, NULL);
    SetMainCallback(AnimationMain);
}
