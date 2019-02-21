.text
.thumb
.align 2

.include "src/animation_cmds.s"
.equ target, 0x8000
.equ attacker, 0x8001

.global scrAnimTesting

scrAnimTesting:
    loadsprite top_gfx scroll_pal slider_oam
    rendersprite 0x800D 50 100 nullrsf
    copyvar 0x8002 0x800D
    loadbg2 32 switch_bgTiles switch_bgMap switch_bgPal
    showbg 2
    beginfade 0 0x1CF8 FADETO true
    beginfade 0 0x1CF8 FADEFROM true
    getdefender
    movewave target 0x8002 2 32 SINWAVE
    flashsprite 0x8002 5 20 true 0
    wait
    .byte 0xFF

scrTestVars:
    copyvar 0x8000 0x800D
    setvar 0x8001 0x1919
    copyvar 0x8003 0x8001
    subvar 0x8003 0x18
    .byte 0xFF
.pool
