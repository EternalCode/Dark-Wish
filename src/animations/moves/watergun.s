.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ watergunParticle, 0x9006
.equ counter, 0x9007

.global WatergunAnimation
WatergunAnimation:
    fastsetbattlers
    loadspritefull circularSprite circularPalette circularOam
    copyvar watergunParticle LASTRESULT
    hidehpbars
    spriteblend 5 11
    setvar counter 0
    spritetobg target 8 8
    spriteblend2 watergunParticle 10 0x7354
    //rendersprite watergunParticle attackerx attackery circularAffinePtr
    //spritemovedst 30 watergunParticle target


WatergunLoop:
    BLOCKCMD
    compare counter 3
    if1 0x1 goto WatergunFinish
    loadsprite circularSprite circularPalette circularOam
    spriteblend2 LASTRESULT 10 0x7354
    animatesprite LASTRESULT circularAffinePtr 0
    rendersprite LASTRESULT attackerx attackery circularAffinePtr
    sideof attacker
    if1 0x1 goto WatergunOpponent
    movewave LASTRESULT target 2 1 30
    addvar counter 1
    OPENCMD
    goto WatergunLoop

WatergunOpponent:
    movewave LASTRESULT target 0xFE 1 30
    addvar counter 1
    OPENCMD
    goto WatergunLoop




WatergunFinish:
    OPENCMD
    pauseframes 28
    deletesprite watergunParticle
    clearblending
    showhpbars
    end
