#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

#include <pokeagb/pokeagb.h>
#include "saveblock_expansion/save.h"

/* Colors */
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

/* CPUset */
#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))
extern void CpuFastSet(void* src, void* dst, u32 mode);

/* Debugging */
extern void dprintf(const char * str, ...);

#endif /* GLOBAL_DEFS_H_ */
