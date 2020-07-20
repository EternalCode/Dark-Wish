.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ tempSprite, 0x9006
.equ powderSprite, 0x9007
.equ counter, 0x9008

.global PoisonPowderAnimation
PoisonPowderAnimation:
    fastsetbattlers
    loadspritefull poisonpowderSprite poisonpowderPalette poisonpowderOam
    copyvar powderSprite LASTRESULT
    setvar counter 0

PowderLoop:
    compare counter 12
    if1 0x1 goto FinishPowder
    loadsprite poisonpowderSprite poisonpowderPalette poisonpowderOam
    copyvar tempSprite LASTRESULT
    spritesetposition tempSprite targetx targety
    setframessprite 0 tempSprite poisonpowderFrames
    random 0 0xFF
    spritecallbackargs tempSprite 30 12 1 LASTRESULT SCB_MovePowder
    addvar counter 1
    pauseframes 3
    goto PowderLoop

FinishPowder:
    pauseframes 60
    deletesprite powderSprite
    end

.pool
