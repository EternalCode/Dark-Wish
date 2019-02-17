.text
.thumb
.align 4

.include "src/animation_cmds.s"

.global scrAnimTesting
scrAnimTesting:
    loadsprite top_gfx scroll_pal slider_oam
    rendersprite 0x800D 100 100 nullrsf
    deletesprite 0x800D
    copyvar 0x8000 0x800D
    setvar 0x8001 0x1919
    copyvar 0x8003 0x8001
    subvar 0x8003 0x18
    .byte 0xFF
    .byte 0xFF
.pool
