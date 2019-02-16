#include <pokeagb/pokeagb.h>
#include "battle_obj_sliding.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"

extern void C2SyncAll(void);
extern void spawn_hpboxes_wild(void);
extern void VblankMergeTextBox(void);
extern void VblankMergeTextBoxSliding(void);
extern void StartBattle(void);
extern const struct BgConfig bg_config_data[4];
extern void pick_and_load_battle_bgs(void);
extern void battle_scene_intialize_sprites(void);
extern void battlers_move_into_scene(void);
extern void task_lightup_objs(u8);

void hblank_battle_bgsslide_win_open(void)
{
    // screen opening from middle, outwards
    if ((REG_VCOUNT > BattleEntryWindows->winbot) || (REG_VCOUNT < BattleEntryWindows->wintop)) {
        // turn off display
        REG_DISPCNT = 0x0;
    } else {
        // enable win0 and win 1
        REG_DISPCNT = 0x7B60;
    }

    // bg movement
    if (REG_VCOUNT > 79) {
        // move BG3 left
        REG_BG3HOFS = BattleEntryWindows->top_side;
    } else {
        // move BG3 right
        REG_BG3HOFS = BattleEntryWindows->bot_side;
    }

}

void hblank_battle_bgslide(void)
{
    // bg movement
    if (REG_VCOUNT > 79) {
        // move BG3 left
        REG_BG3HOFS = BattleEntryWindows->top_side;
    } else {
        // move BG3 right
        REG_BG3HOFS = BattleEntryWindows->bot_side;
    }
}


void TransitionWildBattle()
{
    switch (gMain.state) {
        case 0:
            dprintf("CASE 0\n");
            // set callbacks and vblank interrupt
            SetVBlankCallback((MainCallback)VblankMergeTextBoxSliding);
            SetMainCallback2((MainCallback)C2SyncAll);
            // put everything in the window

            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,
            WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);
            gMain.state++;
            break;
        case 1:
            dprintf("CASE 1\n");
            bg_vram_setup(0, (struct BgConfig *)&bg_config_data, 4);
            // init textbox
            rbox_init_from_templates((struct TextboxTemplate*)0x8248330);
            gMain.state++;
            break;
        case 2:
            dprintf("CASE 2\n");
            pick_and_load_battle_bgs();
            gMain.state++;
            break;
        case 3:
            /*
            darken sprites only
            This is a trick in which by putting BG3 in the destination, sprites which have semi-transparent
            mode activated will not be effected by the darken, since the lowest BG layer is lower in
            priority, thus the transparency will take place instead.
            */
            dprintf("CASE 3\n");
            dprintf("callback is %x\n", gMain.callback1);
            REG_BLDCNT = (BLDCNT_SPRITES_SRC |  BLDCNT_BG3_DST | BLDCNT_DARKEN);
            // darken factor of 7
            REG_BLDY = 0x7;
            battle_scene_intialize_sprites();
            dprintf("does it come back?\n");
            gMain.state++;
            dprintf("the state handler is %d\n", gMain.state);
            dprintf("callback is %x\n", gMain.callback1);
            break;
        case 4:
            // show bgs for background and entry image
            dprintf("CASE 4\n");
            ShowBg(3);
            ShowBg(1);
            ShowBg(0);
            dprintf("CASE 4 show bgs\n");
            // enable wraparound for BG3 and BG1 (platform and entry image)
            REG_BG3CNT |= 0x2000;
            REG_BG1CNT |= 0x2000;

            // activate hblank interrupt
            interrupts_enable(2);
            SetHBlankCallback((MainCallback)hblank_battle_bgsslide_win_open);
            gMain.state++;
            break;
        case 5:
            // set initial position for BG bottom and top half
            BattleEntryWindows->top_side = -260;
            BattleEntryWindows->bot_side = -254;

            // set initial position for center of open effect (160 / 2 = 80 = center)
            BattleEntryWindows->wintop = 80;
            BattleEntryWindows->winbot = 80;
            gMain.state++;
            break;
        case 6:
            // there is a window in which the entry image and BG are moving
            bgid_mod_x_offset(1, 3 << 8, 1);
            BattleEntryWindows->wintop -= 1;
            BattleEntryWindows->winbot += 1;
            if (BattleEntryWindows->wintop < 20)
                gMain.state++;
            break;
        case 7:
        {
            bgid_mod_x_offset(1, 4 << 8, 1);
            bgid_mod_y_offset(1, 1 << 7, 2);

            // slide in battlers for each side
            battlers_move_into_scene();
            // the Hblank is lightened since the window effect is unneeded at this point
            if (BattleEntryWindows->wintop <= 0) {
                SetHBlankCallback((MainCallback)hblank_battle_bgslide);
                REG_DISPCNT = 0x7B60;
            }
            // once the sliding is done, continue next state
            if (BattleEntryWindows->top_side > -3)
                gMain.state++;
            break;
        }
        case 8:
        {
            interrupts_disable(2);
            SetHBlankCallback(NULL);
            SetVBlankCallback((MainCallback)VblankMergeTextBox);
            // light up opponents gradually and disable entry image
            u8 taskId = task_add(task_lightup_objs, 0x1);
            tasks[taskId].priv[0] = 0x7;
            HideBg(1);

            // spawn HP boxes
            spawn_hpboxes_wild();
            gMain.state = 0;
            SetMainCallback((MainCallback)StartBattle);
        }
        case 10:
        default:
            break;
    };
}


void task_lightup_objs(u8 taskId)
{
    if (tasks[taskId].priv[0]) {
        // every other frame drop the darken value
        if (tasks[taskId].priv[1] % 2)
            tasks[taskId].priv[0]--;
        tasks[taskId].priv[1]++;
        REG_BLDY = tasks[taskId].priv[0];
    } else {
        // opponent side light up original palette
        REG_BLDCNT = 0;

        // player side remove blending
        gSprites[BattleEntryWindows->player_trainer_objid].final_oam.obj_mode = 0;
        gSprites[BattleEntryWindows->partner_trainer_objid].final_oam.obj_mode = 0;
        DestroyTask(taskId);
    }
}
