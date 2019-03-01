#include <pokeagb/pokeagb.h>
#include "save.h"
#include "../../animations/animation_core.h"

extern void dprintf(const char * str, ...);
u8 *GetFlagPointer(u16 id)
{
    if (id == 0) {
        return NULL;
    } else if (id >= EXPANDED_START_FLAG && id <= EXPANDED_END_FLAG) {
        // Added flags
        u16 tempFlag = id - EXPANDED_START_FLAG;
        return (u8*)gSaveBlockParasite + (tempFlag >> 3);
    } else if (id < 0x3FFF) {
        // vanilla vars
        return &gSaveBlock1Ptr->flags[id >> 3];
    } else {
        // temporary flags in non Save RAM
        u32 tempFlagsAddr = 0x020370E0;
        s16 tempFlag = id - 0x4000;
        if (tempFlag < 0) {
            tempFlag -= 0x3FF9;
        }
        tempFlag = tempFlag >> 3;
        return (u8*)(tempFlag + tempFlagsAddr);
    }
}


u16 *GetVarPointer(u16 id)
{
    if (id >= 0x4000 && id <= 0x40FF) {
        // vanilla vars
        return &gSaveBlock1Ptr->vars[id - 0x4000];
    } else if (id >= 0x5000 && id <= 0x51FF) {
        // added vars
        u16 trueVarId = (id - 0x5000) << 1;
        return  (u16*)(EXPANDED_VARS_START + trueVarId);
    } else if (id >= ANIMVARS) {
        // animation script vars -- available only during animation. Unsaved
        return &gAnimationCore->corevars[ANIMSCR_THREAD][id - ANIMVARS];
    } else if (id >= 0x8000 && id <= 0x8016) {
        id -= 0x8000;
        return (u16*)var_80xx[id];
    } else {
        return NULL;
    }
}
