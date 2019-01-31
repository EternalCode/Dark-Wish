#ifndef ULTRA_DEX_H_
#define ULTRA_DEX_H_

#include <pokeagb/pokeagb.h>

typedef void (*UDCallback)(void);
#define gUltraDex (*UltraDexPtr)

#define APP_DESC_BAR 0
#define APP_TIME_BAR 1
#define APPS_PER_PAGE 4
#define ULTRADEX_NAME_BAR 2

/* tags */
#define ULTRADEX_CURSOR_TAG 0x8282

struct DexApplication {
    const pchar* appName;
    const pchar* appDescription;
    UDCallback appCB;
};

struct UltraDexSharedGraphics {
    u8 textboxes[4];
    u16 gradient[20];
    u16 gradient_palette[20][16] __attribute__((aligned(4))); /* 20 lines of 16 colours */
};

struct UltraDexState {
        u8 page;
        u8 selectedAppIndex;
        u8 currentOpenApp;
        u8 ultraDexCursorObjId;
        struct UltraDexSharedGraphics* sharedGfx;
};

extern struct DexApplication DexApps[];

#endif /* ULTRA_DEX_H_ */
