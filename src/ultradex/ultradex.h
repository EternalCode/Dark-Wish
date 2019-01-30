#ifndef ULTRA_DEX_H_
#define ULTRA_DEX_H_

#include <pokeagb/pokeagb.h>

typedef void (*UDCallback)(void);
#define gUltraDex (*UltraDexPtr)

struct DexApplication {
    const pchar* appName;
    const pchar* appDescription;
    UDCallback appCB;
};

struct UltraDexState {
        u8 page;
        u8 selectedApp;

};

#endif /* ULTRA_DEX_H_ */
