#include <pokeagb/pokeagb.h>
#include "battle_data/battle_state.h"
#include "battle_text/battle_textbox_gfx.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_slide_in_data/battle_obj_sliding.h"
extern void CpuFastSet(void*, void*, u32);

/* This vblank overlaps the tilemap from show_message with the battle box */
void VblankMergeTextBox()
{
    gpu_sprites_upload();
    copy_queue_process();
    gpu_pal_upload();
    u8 **bg0_map = (u8**)0x030008EC;
    u8 *dst = (u8 *)(*bg0_map);
    u8 *src = (u8 *)battle_textboxMap;
    for (u32 i = 0; i < 2048; i++) {
    // only merge if there is no text on this tile
        if (!*(dst + i))
            *(dst + i) = *(src + i);
	}
}

void VblankMergeStatTextBox()
{
    gpu_sprites_upload();
    copy_queue_process();
    gpu_pal_upload();
    u8 **bg0_map = (u8**)0x030008EC;
    u8 *dst = (u8 *)(*bg0_map);
    u8 *src = (u8 *)battle_textbox_statMap;
    for (u32 i = 0; i < 2048; i++) {
    // only merge if there is no text on this tile
        if (!*(dst + i))
            *(dst + i) = *(src + i);
	}
}

/* This vblank overlaps the tilemap from show_message with the battle box */


void VblankMergeTextBoxSliding()
{
    gpu_sprites_upload();
    copy_queue_process();
    gpu_pal_upload();
    if (gMain.state == 7) {
        BattleEntryWindows->bot_side -= 3;
        BattleEntryWindows->top_side += 3;
        BattleEntryWindows->wintop -= 1;
        BattleEntryWindows->winbot += 1;
    }
}

/* This vblank overlaps the tilemap from move selection with the battle box */
void VblankMergeMoveSelect()
{
    gpu_sprites_upload();
    copy_queue_process();
    gpu_pal_upload();

}

//
// void C2SyncAll()
// {
//     BuildOAMBuffer();
//     AnimateSprites();
//     process_palfade();
//     RunTasks();
//     // merge textbox and text tile maps
//     RunTextPrinters();
// }
//
// void C2SyncAll()
// {
//     BuildOAMBuffer();
//     AnimateSprites();
//     process_palfade();
//     RunTasks();
//     tilemaps_sync();
//     // merge textbox and text tile maps
//     RunTextPrinters();
// }
