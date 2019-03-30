.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ angleBuffer, 0x9006
.equ hornParticle, 0x9007
.equ hornParticle2, 0x9008
.equ hornParticle3, 0x9009
.equ tempSprite, 0x900A
.equ impactParticle, 0x900B

.global PinMissileAnimation
PinMissileAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull pinmissileSprite pinmissilePalette pinmissileOam
    copyvar hornParticle LASTRESULT
    loadspritefull pinmissileSprite pinmissilePalette pinmissileOam
    copyvar hornParticle2 LASTRESULT
    loadspritefull pinmissileSprite pinmissilePalette pinmissileOam
    copyvar hornParticle3 LASTRESULT
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 8 8

    spritesetposition hornParticle attackerx attackery
    spritesetposition hornParticle2 attackerx attackery
    spritesetposition hornParticle3 attackerx attackery

    sideof attacker
    if2 0x0 call playerSideArcConfig
    if2 0x1 call opponentSideArcConfig


    OPENCMD

    copyvar tempSprite hornParticle
    call moveParticleArc
    pauseframes 8
    copyvar tempSprite hornParticle2
    call moveParticleArc
    pauseframes 8
    copyvar tempSprite hornParticle3
    call moveParticleArc

    waitthread 1
    waitthread 2
    waitthread 3
    BLOCKCMD
    deletesprite impactParticle
    clearblending
    showsprite target
    hidebg 1
    OPENCMD
    spritebgclear target
    end

playerSideArcConfig:
    horizontalArcTranslate 0 150 hornParticle target 20 PLAYERSIDE
    horizontalArcTranslate 0 150 hornParticle2 target 20 PLAYERSIDE
    horizontalArcTranslate 0 150 hornParticle3 target 20 PLAYERSIDE
    return

opponentSideArcConfig:
    horizontalArcTranslate 0 85 hornParticle target 20 OPPONENTSIDE
    horizontalArcTranslate 0 85 hornParticle2 target 20 OPPONENTSIDE
    horizontalArcTranslate 0 85 hornParticle3 target 20 OPPONENTSIDE
    return

SinWaveTranslate:
    runtask TaskTranslateSpriteHorizontalArc tempSprite 0 0 0
    return

CosWaveTranslate:
    runtask TaskTranslateSpriteHorizontalArcCos tempSprite 0 0 0
    return

moveParticleArc:
    BLOCKCMD
    sideof attacker
    if2 0x0 call SinWaveTranslate
    if2 0x1 call CosWaveTranslate
    runtask TaskSpriteFaceSprite tempSprite 0 target 0
    startscript RenderImpactParticle true
    OPENCMD
    pauseframes 1
    showsprite tempSprite
    return


RenderImpactParticle:
    pauseframes 17
    BLOCKCMD
    spritebufferposition tempSprite targetx targety
    deletesprite tempSprite
    OPENCMD
    loadsprite impact1Sprite impact1Palette impact1Oam
    BLOCKCMD
    rendersprite LASTRESULT targetx targety nullrsf
    quakebg 1 2 0 2 2 true
    OPENCMD
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    wait
    end


.pool
