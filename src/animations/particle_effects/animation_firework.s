.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ glowballParticle, 0x9006
.equ glowcolor, 0x9007

.global FireworkAnimation
FireworkAnimation:
    copyvar glowcolor gLASTRESULT
    compare targetx 0
    if1 1 goto FireworkPosInherited
    fastsetbattlers

FireworkPosInherited:
    BLOCKCMD
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar glowballParticle LASTRESULT
    spriteblend 8 8
    hidebg 1
    spritetobg target 8 8
    showbg 1
    OPENCMD

FireworkLoop:
    BLOCKCMD
    runtask TaskCreateSmallFireworkImpact glowcolor 3 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 3 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 2 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 2 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 1 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 1 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 0 targetx targety
    runtask TaskCreateSmallFireworkImpact glowcolor 0 targetx targety
    OPENCMD

FireworkFinish:
    waittask TaskCreateSmallFireworkImpact
    spritebgclear target
    deletesprite glowballParticle
    end

.pool
