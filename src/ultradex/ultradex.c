#include <pokeagb/pokeagb.h>
#include "../global.h"
#include "ultradex.h"

static struct UltraDexState** UltraDexPtr = (struct UltraDexState**)(ULTRADEX_START);
#define gUltraDex (*UltraDexPtr)

/* Entry point into the Ultradex */
u8 LaunchUltraDex()
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
    void C1UltraDex(void);
    SetMainCallback(C1UltraDex);
    gMain.state = 0;
    return true;
}


const struct BgConfig BGConfigUDex[4] = {
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 0,
        .palette = 0,
        .size = 0,
        .map_base = 31,
        .character_base = 0,
        .bgid = 0,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 1,
        .palette = 0,
        .size = 0,
        .map_base = 30,
        .character_base = 1,
        .bgid = 1,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 2,
        .palette = 0,
        .size = 0,
        .map_base = 29,
        .character_base = 2,
        .bgid = 2,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 3,
        .palette = 0,
        .size = 0,
        .map_base = 28,
        .character_base = 3,
        .bgid = 3,
    },
};

void UltraDexSetup() {
    extern void Setup(void);
    extern void C2DexnavGui(void);
    extern void VblankSPQ(void);
    Setup();
    rboxes_free();
    bg_vram_setup(0, (struct BgConfig *)&BGConfigUDex, 4);
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
    gpu_sync_bg_hide(3);
    gpu_sync_bg_hide(2);
    gpu_sync_bg_hide(1);
    gpu_sync_bg_hide(0);
    SetMainCallback2(C2DexnavGui);
    SetVBlankCallback(VblankSPQ);
}

void C1UltraDex()
{
    switch(gMain.state) {
        case 0:
            if (!gPaletteFade.active) {
                m4aMPlayVolumeControl(&mplay_BGM, 0xFFFF, 128);
                UltraDexSetup();
                SetMainCallback(C1UltraDex); // setup resets all CBs
                // allocate ultradex
                gUltraDex = (struct UltraDexState*)malloc_and_clear(sizeof(struct UltraDexState));
                gMain.state++;
            }
            break;
        case 1:
            break;
    };
}
