#include <pokeagb/pokeagb.h>
#include "global.h"

void CpuFastSet(void* src, void* dst, u32 mode)
{
    __asm__("swi 0xC");
}

u16 rand_range(u16 min, u16 max)
{
    if (min == max) return min;
    return (rand() % (max - min)) + min;
}


void GetClockTime(u8* hour, u8* min)
{
    dprintf("Saveblock ptr is %x\n", gSaveBlock2Ptr);
    dprintf("Saveblock time addr is %x\n", &gSaveBlock2Ptr->playTimeMinutes);
    u32 totalMinutes = gSaveBlock2Ptr->playTimeMinutes + (gSaveBlock2Ptr->playTimeHours * 60);
    dprintf("Total minutes is %d from %d min and %d hours\n", totalMinutes, gSaveBlock2Ptr->playTimeMinutes, gSaveBlock2Ptr->playTimeHours);
    totalMinutes = (totalMinutes * TIME_SCALE) % MINUTES_IN_A_DAY;
    *min = totalMinutes % 60;
    totalMinutes -= *min;
    *hour = totalMinutes / 60;
}
