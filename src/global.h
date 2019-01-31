#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

#include <pokeagb/pokeagb.h>
#include "saveblock_expansion/save.h"

/* Colors */
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

/* Textbox stuff */
extern const u16 GenericTextPal[];
extern struct TextColor textBlack;
extern struct TextColor textWhite;
extern struct TextColor textRed;
extern struct TextColor textGreen;

/* CPUset */
#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))
extern void CpuFastSet(void* src, void* dst, u32 mode);

/* Game clock */
// we'll say 60 minutes is 1 day. So 1140 mins is 1 day,
#define TIME_SCALE 19
#define MINUTES_IN_A_DAY 1140
extern void GetClockTime(u8* hour, u8* min);

/* Debugging */
extern void dprintf(const char * str, ...);

#endif /* GLOBAL_DEFS_H_ */
