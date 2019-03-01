#include <pokeagb/pokeagb.h>

#define ANIM_STACK_DEPTH 20
#define ANIM_VAR_COUNT 20
#define ANIM_SCR_COUNT 4

typedef void(*AnimScriptFunc)(void);


struct AnimationStack {
    u8* script;
    u8 scriptIndex;
};

struct AnimationCore {
    /* Animation script pointers */
    u8* animScriptPtr[ANIM_SCR_COUNT];

    /*
    * GBA is single threaded. We have to take turns running animations in reality.
    * Running them in C1 and then Vsyncing them will sync it visually
    */
    u8 currentAnimationScript; // 0, 1, 2, or 3

    /* wait state for each animation script */
    u8 wait[ANIM_SCR_COUNT];
    u8 waitAll;

    /* Call stack */
    u8* callStack[ANIM_SCR_COUNT][ANIM_STACK_DEPTH];
    u8 stacks[ANIM_SCR_COUNT];

    /* global vars for all commands split into each script */
    u32 palbuffer[ANIM_SCR_COUNT];
    u8 conditionResult[ANIM_SCR_COUNT];
    u16 corevars[ANIM_SCR_COUNT][ANIM_VAR_COUNT];
};


struct AnimationCore* gAnimationCore;

#define ANIMSCR_THREAD gAnimationCore->currentAnimationScript
#define ANIMSCR_SCRIPT gAnimationCore->animScriptPtr[ANIMSCR_THREAD]
#define ANIMSCR_SPRITES gAnimationCore->animationSprites[ANIMSCR_THREAD]
#define ANIMSCR_WAITING gAnimationCore->wait[ANIMSCR_THREAD]
#define ANIMSCR_ARGS gAnimationCore->retArg[ANIMSCR_THREAD]
#define ANIMSCR_PALBUFF gAnimationCore->palbuffer[ANIMSCR_THREAD]
#define ANIMSCR_STACKDEPTH gAnimationCore->stacks[ANIMSCR_THREAD]
#define ANIMSCR_CONDITION gAnimationCore->conditionResult[ANIMSCR_THREAD]
#define ANIMSCR_CMD_NEXT ANIMSCR_THREAD = (ANIMSCR_THREAD == (ANIM_SCR_COUNT - 1)) ? \
                                            0 : ANIMSCR_THREAD + 1

#define ANIMSCR_MOVE(x) (ANIMSCR_SCRIPT += x)

#define ANIMSCR_READ_BYTE (ANIMSCR_SCRIPT[0] << 0); ANIMSCR_MOVE(1)

#define ANIMSCR_READ_HWORD  ((ANIMSCR_SCRIPT[0] << 0) | \
                            (ANIMSCR_SCRIPT[1] << 8)); ANIMSCR_MOVE(2)

#define ANIMSCR_READ_WORD ((ANIMSCR_SCRIPT[0] << 0) | \
						   (ANIMSCR_SCRIPT[1] << 8) | \
						   (ANIMSCR_SCRIPT[2] << 16) | \
						   (ANIMSCR_SCRIPT[3] << 24)); ANIMSCR_MOVE(4)
