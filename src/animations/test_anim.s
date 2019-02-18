.text
.thumb
.align 2

.include "src/animation_cmds.s"

.global scrAnimTesting

scrAnimTesting:
    loadsprite top_gfx scroll_pal slider_oam
    rendersprite 0x800D 100 100 nullrsf
    movesprite 0x800D 50 0xFF42 2
    wait
    deletesprite 0x800D
    goto scrTestVars
    .byte 0xFF
    .byte 0xFF
    .byte 0xFF

scrTestVars:
    copyvar 0x8000 0x800D
    setvar 0x8001 0x1919
    copyvar 0x8003 0x8001
    subvar 0x8003 0x18
    .byte 0xFF
    .byte 0xFF
.pool
