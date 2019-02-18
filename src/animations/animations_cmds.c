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
extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];
extern void TaskMoveSprite(u8 taskId);

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
    u8 taskId = task_add(TaskMoveSprite, 0);
    struct Task* t = &tasks[taskId];

    // set passed args to task
    u16 spriteId = ANIMSCR_READ_HWORD;
    t->priv[0] = VarGet(spriteId);
    t->priv[1] = ANIMSCR_READ_HWORD; // xOff
    t->priv[2] = ANIMSCR_READ_HWORD; // yOff
    t->priv[3] = ANIMSCR_READ_HWORD; // speed
    t->priv[4] = ANIMSCR_THREAD; // execution thread
    t->priv[5] = gSprites[t->priv[0]].pos1.x; // original x
    t->priv[6] = gSprites[t->priv[0]].pos1.y; // original y
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

/* Move a sprite with a tag by a certain delta X in F frames */
void AnimationMain()
{
    if (gAnimationCore->waitAll) {
        return;
    }

    if (ANIMSCR_WAITING) {
        ANIMSCR_CMD_NEXT;
		return;
    }
    if (!ANIMSCR_SCRIPT) {
        ANIMSCR_CMD_NEXT;
		return;
	}
    RunCurrentCommand();
}


void TestAnimation()
{
	extern u8 scrAnimTesting;
    dprintf("running tests on script %x\n", (u32)&scrAnimTesting);
	InitializeAnimationCore(&scrAnimTesting, NULL, NULL, NULL);
	SetMainCallback(AnimationMain);
}
