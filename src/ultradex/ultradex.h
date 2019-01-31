#ifndef ULTRA_DEX_H_
#define ULTRA_DEX_H_

#include <pokeagb/pokeagb.h>

typedef void (*UDCallback)(void);
#define gUltraDex (*UltraDexPtr)

#define APPS_PER_PAGE 4
#define ULTRADEX_NAME_BAR 2
#define APPS_COUNT 9

/* tags */
#define ULTRADEX_PAGE_ICON_TAG 0x8281
#define ULTRADEX_CURSOR_TAG 0x8282
#define ULTRADEX_APP_ICON_TAG 0x8283

struct DexApplication {
    const pchar* appName;
    const pchar* appDescription;
    UDCallback appCB;
    u8 xNameShift;
};

struct UltraDexSharedGraphics {
    u8 textboxes[4];
    u16 gradient[20];
    u16 gradient_palette[20][16] __attribute__((aligned(4))); /* 20 lines of 16 colours */
};

struct UltraDexState {
    struct UltraDexSharedGraphics* sharedGfx;
    u8 page;
    s8 selectedAppIndex;
    u8 currentOpenApp;
    u8 cursorObjId;
    u8 pageObjId;
    u8 iconObjIds[APPS_COUNT];
};

extern struct DexApplication DexApps[];

#endif /* ULTRA_DEX_H_ */
