.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ sonicParticle, 0x9006
.equ tempSprite, 0x9007
.equ counter, 0x9008

.global SupersonicAnimation
SupersonicAnimation:
    fastsetbattlers
    spritetobg target 8 8
    spriteblend 8 8
    loadspritefull supersonicSprite supersonicPalette supersonicOam
    copyvar sonicParticle LASTRESULT
    startscript SonicQuakeBg true

supersonicLoop:
    compare counter 8
    if1 0x1 goto finishMove
    BLOCKCMD
    loadspritefull supersonicSprite supersonicPalette supersonicOam
    copyvar tempSprite LASTRESULT
    animatesprite tempSprite supersonicAffine 0
    OPENCMD
    BLOCKCMD
    rendersprite tempSprite attackerx attackery supersonicAffine
    spritemovedst 30 tempSprite target
    addvar counter 1
    OPENCMD
    goto supersonicLoop

finishMove:
    pauseframes 30
    waitthread 1
    deletesprite sonicParticle
    clearblending
    showsprite target
    hidebg 1
    spritebgclear target
    end

SonicQuakeBg:
    pauseframes 30
    quakebg 1 2 0 8 2 true
    wait
    end

.pool
