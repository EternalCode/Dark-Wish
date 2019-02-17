.text
.thumb
.align 4

.include "src/animation_cmds.s"

.global scrAnimTesting
scrAnimTesting:
    showsprite 100 100 top_gfx1 scroll_pal1
@    deletesprite 0xD740
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
	.byte 0xFF
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF
.pool
