.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ poisonParticle, 0x9007
.equ poisonParticle2, 0x9008
.equ poisonParticle3, 0x9009
.equ tempSprite, 0x900A

.global AcidAnimation
AcidAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull poisonSprite poisonPalette poisonOam
    copyvar poisonParticle LASTRESULT
    spritepriority poisonParticle 1
    semitransparent poisonParticle
    loadsprite poisonSprite poisonPalette poisonOam
    copyvar poisonParticle2 LASTRESULT
    semitransparent poisonParticle2
    spritepriority poisonParticle2 1
    loadsprite poisonSprite poisonPalette poisonOam
    copyvar poisonParticle3 LASTRESULT
    semitransparent poisonParticle3
    spritepriority poisonParticle3 1
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    spritepriority impactParticle 1
    semitransparent impactParticle
    spriteblend2 impactParticle 10 0x6DF8
    spritetobg target 8 8
    blendsemitransparent 10 4
    OPENCMD
    BLOCKCMD
    spritesetposition poisonParticle attackerx attackery
    spritesetposition poisonParticle2 attackerx attackery
    spritesetposition poisonParticle3 attackerx attackery
    sideof attacker
    OPENCMD
    if2 0x0 call playerSideArcConfig
    if2 0x1 call opponentSideArcConfig
    copyvar tempSprite poisonParticle
    call moveParticleArc
    addfadebg1
    beginfade 1 0x50F3 FADETO false 10
    copyvar tempSprite poisonParticle2
    call moveParticleArc
    copyvar tempSprite poisonParticle3
    call moveParticleArc
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 false
    waittask TaskTranslateSpriteHorizontalArc
    waittask TaskTranslateSpriteHorizontalArcCos
    BLOCKCMD
    beginfade 1 0x50F3 FADEFROM true 10
    deletesprite impactParticle
    deletesprite poisonParticle
    deletesprite poisonParticle2
    deletesprite poisonParticle3
    deletesprite impactParticle
    clearblending
    showsprite target
    OPENCMD
    hidebg 1
    spritebgclear target
    end

playerSideArcConfig:
    BLOCKCMD
    horizontalArcTranslate 0 150 poisonParticle target 20 PLAYERSIDE
    horizontalArcTranslate 0 150 poisonParticle2 target 20 PLAYERSIDE
    horizontalArcTranslate 0 150 poisonParticle3 target 20 PLAYERSIDE
    OPENCMD
    return

opponentSideArcConfig:
    BLOCKCMD
    horizontalArcTranslate 0 90 poisonParticle target 20 OPPONENTSIDE
    horizontalArcTranslate 0 90 poisonParticle2 target 20 OPPONENTSIDE
    horizontalArcTranslate 0 90 poisonParticle3 target 20 OPPONENTSIDE
    OPENCMD
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
    rendersprite tempSprite attackerx attackery nullrsf
    OPENCMD
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    return

.pool
