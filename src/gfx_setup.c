#include <pokeagb/pokeagb.h>
#include "global.h"

void VblankSPQ()
{
	gpu_sprites_upload();
	copy_queue_process();
	gpu_pal_upload();
}


void C2SyncAll()
{
    BuildOAMBuffer();
    AnimateSprites();
    process_palfade();
    RunTasks();
    tilemaps_sync();
    // merge textbox and text tile maps
    RunTextPrinters();
}


void HandlersClear()
{
	SetVBlankCallback(NULL);
	SetHBlankCallback(NULL);
	SetMainCallback(NULL);
	SetMainCallback2(NULL);
}


void ResetPals()
{
	pal_fade_control_and_dead_struct_reset();
	palette_bg_faded_fill_black();
	gpu_pal_allocator_reset();
	*gpu_pal_tag_search_lower_boundary = 0;
}


void ResetBgs()
{
	overworld_free_bgmaps();
	gpu_tile_bg_drop_all_sets(0);
	bgid_mod_x_offset(0, 0, 0);
    bgid_mod_y_offset(0, 0, 0);
	bgid_mod_x_offset(1, 0, 0);
    bgid_mod_y_offset(1, 0, 0);
	bgid_mod_x_offset(2, 0, 0);
    bgid_mod_y_offset(2, 0, 0);
	bgid_mod_x_offset(3, 0, 0);
    bgid_mod_y_offset(3, 0, 0);
}


void ResetTextBoxes()
{
	remo_reset_acknowledgement_flags();
	rboxes_free();
}


void Setup()
{
    // callbacks
    HandlersClear();
    // BGs
    ResetBgs();
    // pals
    ResetPals();
    // objs
    ResetSpriteData();
    gpu_tile_obj_tags_reset();
    // VRAM clear
    u32 set = 0;
    CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
    // tasks
    malloc_init((void*)0x2000000, 0x1C000);
    ResetTasks();
}
