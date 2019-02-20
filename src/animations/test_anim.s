.text
.thumb
.align 2

.include "src/animation_cmds.s"

.global scrAnimTesting

scrAnimTesting:
    loadsprite top_gfx scroll_pal slider_oam
    rendersprite 0x800D 50 100 nullrsf
    //movesprite 0x800D 1 0xFFFF 20
    //wait
    copyvar 0x8000 0x800D
    setvar 0x800D 0x0
    spritetobg 0x800D 8 8
    showbg 1
    spriteblend 8 8
    //movesprite 0x8000 1 0 50
    //wait
    addpalbuffer 0x8000 0
    addpalbuffer 0x800D 0
    loadbg2 32 switch_bgTiles switch_bgMap switch_bgPal
    showbg 2
    beginfade 0 0x1CF8 FADETO true
    beginfade 0 0x1CF8 FADEFROM true
    movewave 0x8000 0x800D 2 32 SINWAVE
    .byte 0xFF

scrTestVars:
    copyvar 0x8000 0x800D
    setvar 0x8001 0x1919
    copyvar 0x8003 0x8001
    subvar 0x8003 0x18
    .byte 0xFF
.pool
