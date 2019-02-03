        .gba
        .thumb
        .open "roms/BPRE0.gba","build/dw.gba", 0x08000000

        .include "patches/save.s"
        .include "patches/sideways_stairs.s"
        .include "patches/triple_layer_block.s"
        .include "patches/overworld_cave_effect.s"
        .include "patches/start_menu.s"
        .include "patches/select_button.s"
        .include "patches/hidden_abilities.s"
        .include "patches/pokemon_bst.s"

		.org 0x08FFFFFF
			.fill 0xFFFFFF, 0xFF

        .org 0x09000000
        .importobj "build/linked.o"
        .close
