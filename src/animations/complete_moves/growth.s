.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ counter, 0x9006
.equ amount, 0x9007

.global GrowthAnimation
GrowthAnimation:
    fastsetbattlers
    addpalbuffer attacker false
    call GrowAnimEffect
    call GrowAnimEffect
    clearpalbuffer
    end


GrowAnimEffect:
    setvar counter 256
    setvar amount 16
    startscript GrowSprite true
    beginfade 1 0xFFFF FADETO true 10
    waitthread 1
    setvar counter 224
    setvar amount 16
    startscript ShrinkSprite true
    beginfade 1 0xFFFF FADEFROM true 10
    waitthread 1
    return

GrowSprite:
    superscale attacker counter counter 256
    subvar counter amount
    compare counter 224
    if1 0x0 goto GrowSprite
    superscale attacker 224 224 256
    end

ShrinkSprite:
    superscale attacker counter counter 256
    addvar counter amount
    compare counter 256
    if1 0x0 goto ShrinkSprite
    superscale attacker 256 256 256
    end

.pool
