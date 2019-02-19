.text
.thumb
.align 2

.include "src/animation_cmds.s"

.global scrAnimTesting

scrAnimTesting:
    loadsprite top_gfx scroll_pal slider_oam
    rendersprite 0x800D 100 60 nullrsf
    movesprite 0x800D 1 0xFFFF 20
    wait
    copyvar 0x8000 0x800D
    setvar 0x800D 0x0
    spritetobg 0x800D 8 8
    spriteblend 8 8
    movesprite 0x8000 1 0 50
    wait
    lighten 0xA INBG0|INBG3
    goto scrTestVars
    .byte 0xFF

scrTestVars:
    copyvar 0x8000 0x800D
    setvar 0x8001 0x1919
    copyvar 0x8003 0x8001
    subvar 0x8003 0x18
    .byte 0xFF
.pool
