#include <pokeagb/pokeagb.h>
#include "../../global.h"

#define TOOL_COUNT 2
extern u8 exec_dexnav(void);
extern u8 ExecPokedex(void);
extern u8 LaunchUltraDex(void);

const pchar menu_text[] = _("Pokédex\nDexnav");
const pchar sm_poketools_text[] = _("TOOLS");
struct TextColor menu_text_black = {0, 2, 3};
struct Textbox tbox = {0, 2, 2, 10, TOOL_COUNT << 1, 0xF, 0x130};

void CloseStartmenu() {
	safari_stepscount_close();
	sm_close_description();
	sm_close_menu();
}

void ToolSelection(u8 task_id) {
    #define priv0 tasks[task_id].priv[0]
    switch (priv0) {
        case 0:
            if (script_env_2_is_enabled())
                return;
            priv0++;
        break;
		case 1:
			script_env_enable();
			DestroyTask(task_id);
			LaunchUltraDex();
			break;
    /*    case 1:
            script_env_enable();
            u8 boxid = rboxid_init(&tbox);
            rboxid_clear_pixels(boxid, 0x11);
            outline_box(boxid, 1, 0x214, 0xE);
            rboxid_print(boxid, 1, 8, 2, &menu_text_black, 0, menu_text);
            choice_setup_simple(boxid, 2, 0, 1, 16, TOOL_COUNT, 0);
            rboxid_update(boxid, 3);
            rboxid_tilemap_update(boxid);
            tasks[task_id].priv[1] = boxid;
            priv0++;
            break;
        case 2:
        {
            s8 choice = rbox_choice_update();
            if (choice == 0) {
                //pokedex
				ExecPokedex();
                // sm_pokedex();
                // DestroyTask(task_id);
				// BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0x0000);
            } else if (choice == 1) {
                // dexnav
                exec_dexnav();
                DestroyTask(task_id);
            } else if (choice == -1) {
                // b pressed, exit
                rboxid_clean(tasks[task_id].priv[1], 1);
                rboxid_free(tasks[task_id].priv[1]);
                script_env_disable();
                DestroyTask(task_id);
            }
            return;
        }*/
    };

}


u8 sm_poketools() {
    CloseStartmenu();
    CreateTask(ToolSelection, 0);
    return 1;
}
