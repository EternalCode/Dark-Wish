.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ buffCircle, 0x9006
.equ counter, 0x9007


.global CircleBuffAttacker
CircleBuffAttacker:
    BLOCKCMD
    fastsetbattlers
    sideof attacker
    if2 0x0 call playersidey
    loadspritefull buffcircleSprite buffcirclePalette buffcircleOam
    copyvar buffCircle LASTRESULT
    spriteblend2 buffCircle 12 gLASTRESULT
    semitransparent buffCircle
    setvar counter 512
    spritesetposition buffCircle attackerx attackery
    showsprite buffCircle
    superscale buffCircle counter counter 256
    OPENCMD

growSprite:
    BLOCKCMD
    compare counter 128
    if1 0x1 goto finishGrow
    superscale buffCircle counter counter 256
    subvar counter 32
    OPENCMD
    goto growSprite

playersidey:
    addvar attackery 32
    return

finishGrow:
    superscale buffCircle 128 128 256
    OPENCMD
    deletesprite buffCircle
    end

.pool
