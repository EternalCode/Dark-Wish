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


.global LinearFireworkAnimation
LinearFireworkAnimation:
    copyvar glowcolor gLASTRESULT
    compare targetx 0
    if1 1 goto LinearFireworkPosInherited
    fastsetbattlers

LinearFireworkPosInherited:
    BLOCKCMD
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar glowballParticle LASTRESULT
    spriteblend 8 8
    hidebg 1
    spritetobg target 8 8
    showbg 1
    OPENCMD

LinearFireworkLoop:
    BLOCKCMD
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 3 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 3 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 2 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 2 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 1 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 1 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 0 targetx targety
    runtask TaskCreateSmallLinearFireworkImpact glowcolor 0 targetx targety
    OPENCMD

LinearFireworkFinish:
    waittask TaskCreateSmallLinearFireworkImpact
    spritebgclear target
    deletesprite glowballParticle
    end


.global LinearFireworkAnimationRev
LinearFireworkAnimationRev:
    copyvar glowcolor gLASTRESULT
    compare targetx 0
    if1 1 goto LinearFireworkPosInheritedrev
    fastsetbattlers

LinearFireworkPosInheritedrev:
    BLOCKCMD
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar glowballParticle LASTRESULT
    spriteblend 8 8
    hidebg 1
    spritetobg target 8 8
    showbg 1
    OPENCMD

LinearFireworkLooprev:
    BLOCKCMD
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 3 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 3 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 2 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 2 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 1 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 1 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 0 targetx targety
    runtask TaskCreateSmallLinearFireworkImpactRev glowcolor 0 targetx targety
    OPENCMD

LinearFireworkFinishrev:
    waittask TaskCreateSmallLinearFireworkImpactRev
    spritebgclear target
    deletesprite glowballParticle
    end
