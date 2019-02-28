.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ attacker, 0x8004
.equ target, 0x8005
.equ targetx, 0x8006
.equ targety, 0x8007
.equ attackerx, 0x8008
.equ attackery, 0x8009
.equ LASTRESULT, 0x800D
.equ glowballParticle, 0x800A

.global FireworkAnimation
FireworkAnimation:
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar glowballParticle LASTRESULT
    fastsetbattlers
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
