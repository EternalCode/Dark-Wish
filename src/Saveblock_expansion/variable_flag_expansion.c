#include <pokeagb/pokeagb.h>

extern void dprintf(const char * str, ...);
u8 *GetFlagPointer(u16 id)
{
    u32 tempFlagsAddr = 0x020370E0;
    if (id == 0) {
        return NULL;
    } else if (id >= 0x900 && id <= 0x18FF) {
        // Added flags
        u16 tempFlag = id - 0x900;
        return (u8*)gSaveBlockParasite + (tempFlag >> 3);
    } else if (id < 0x3FFF) {
        // vanilla vars
        return &gSaveBlock1Ptr->flags[id >> 3];
    } else {
        // temporary flags in non Save RAM
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
        u16 flagSpace = (ADDED_FLAGS >> 3) % 2 ? 1 + (ADDED_FLAGS >> 3) : (ADDED_FLAGS >> 3);
        return  (u16*)(gSaveBlockParasite + flagSpace) + trueVarId;
    } else if (id >= 0x8000 && id <= 0x8016) {
        // temp vars, doesn't rely on table now...
        return (u16*)(0x20370B8 + ((id - 0x8000) >> 1));
    } else {
        return NULL;
    }
}
