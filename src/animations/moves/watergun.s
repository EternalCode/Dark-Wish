.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ watergunParticle, 0x9006
.equ watersplashParticle, 0x9008
.equ impactParticle, 0x9009
.equ counter, 0x9007

.global WatergunAnimation
WatergunAnimation:
    fastsetbattlers
    loadspritefull circularSprite circularPalette circularOam
    copyvar watergunParticle LASTRESULT
    loadspritefull watersplashSprite watersplashPalette watersplashOam
    copyvar watersplashParticle LASTRESULT
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    hidehpbars
    setvar counter 0
    spritetobg target 8 8
    spritepriority attacker 1
    setprioritybg 3 2
    spritesblendall 2 14


WatergunLoop:
    BLOCKCMD
    compare counter 8
    if1 0x1 goto WatergunFinish
    loadsprite circularSprite circularPalette circularOam
    spriteblend2 LASTRESULT 10 0x7354
    animatesprite LASTRESULT circularAffinePtr 0
    rendersprite LASTRESULT attackerx attackery circularAffinePtr
    excludeblend LASTRESULT
    spritecallback LASTRESULT SCB_SpriteDeleteWhenAffineEnds
    sideof attacker
    if1 0x1 goto WatergunOpponent
    horizontalArcTranslate 0 130 LASTRESULT target 35 PLAYERSIDE
    runtask TaskTranslateSpriteHorizontalArc LASTRESULT 0 0 0
    addvar counter 1
    OPENCMD
    goto WatergunLoop

WatergunOpponent:
    horizontalArcTranslate 0 130 LASTRESULT target 35 OPPONENTSIDE
    runtask TaskTranslateSpriteHorizontalArcCos LASTRESULT 0 0 0
    addvar counter 1
    OPENCMD
    goto WatergunLoop

WatergunFinish:
    OPENCMD
    pauseframes 8
    BLOCKCMD
    spritesblendall 8 8
    spriteblend2 watersplashParticle 10 0x7354
    rendersprite watersplashParticle targetx targety nullrsf
    spriteblend2 impactParticle 10 0x7354
    rendersprite impactParticle targetx targety nullrsf
    spritepriority impactParticle 2
    setframessprite 0 watersplashParticle watersplashFrames
    excludeblend watersplashParticle
    quakebg 1 2 0 2 2 false
    OPENCMD
    waittask TaskTranslateSpriteHorizontalArcCos
    waittask TaskTranslateSpriteHorizontalArc
    deletesprite impactParticle
    deletesprite watergunParticle
    deletesprite watersplashParticle
    showsprite target
    hidebg 1
    setprioritybg 3 3
    clearblending
    spritebgclear target
    showhpbars
    end
