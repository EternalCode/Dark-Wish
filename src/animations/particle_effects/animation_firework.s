.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ glowballParticle, 0x9006

.global FireworkAnimation
FireworkAnimation:
    compare targetx 0
    if1 1 goto FireworkPosInherited
    fastsetbattlers

FireworkPosInherited:
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar glowballParticle LASTRESULT
    spriteblend 8 8
    spritetobg target 8 8

FireworkLoop:
    runtask TaskCreateSmallFireworkImpact 0 3 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 3 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 2 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 2 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 1 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 1 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 0 targetx targety
    runtask TaskCreateSmallFireworkImpact 0 0 targetx targety

FireworkFinish:
    waittask TaskCreateSmallFireworkImpact
    spritebgclear target
    deletesprite glowballParticle
    end

.pool
