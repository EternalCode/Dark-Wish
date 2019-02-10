#include <pokeagb/pokeagb.h>
#include "../HUD/dexnav_hud.h"

extern void init_dexnav_hud(u16 species, u8 environment);

u8 CheckRegisteredDexnavMon()
{
    u16 var_val = VarGet(DEXNAV_VAR);
    if (var_val) {
        if (task_is_running(dexnav_hud_manage)) {
            // don't redo the search...
            return false;
        }
        init_dexnav_hud(var_val & 0x7FFF, var_val >> 15);
        return true;
    }
    return false;
}
