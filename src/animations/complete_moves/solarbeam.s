.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ innerOrbParticle, 0x9007
.equ beamParticle, 0x9007
.equ tempSprite, 0x9008
.equ beamTailParticle, 0x9008
.equ ogX, 0x9009
.equ ogY, 0x900A
.equ counter, 0x900B

.global SolarBeamChargeAnimation
SolarBeamChargeAnimation:
    fastsetbattlers
    blendsemitransparent 12 4
    loadspritefull glowballSprite glowballPalette shadowpunchGlowBallOam
    copyvar innerOrbParticle LASTRESULT
    copyvar ogX attackerx
    copyvar ogY attackery
    spritetobg attacker 8 8
    addfadeplatformbg
    hidehpbars
    beginfade 2 0 FADETO true 14
    startscript ConvergenceGlow true
    startscript ParticleConvergence true
    waitthread 1
    waitthread 2
    beginfade 2 0 FADEFROM true 14
    showhpbars
    showsprite attacker
    spritebgclear attacker
    clearblending
    deletesprite innerOrbParticle
    end

ParticleConvergence:
    compare counter 24
    if1 0x1 goto ConvergenceWaitingRoom
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    copyvar tempSprite LASTRESULT
    copyvar attackerx ogX
    copyvar attackery ogY
    pickrandompos attackerx attackery 100 100
    addvar counter 1
    spriteblend2 tempSprite 16 0x4B7B
    animatesprite tempSprite solarbeamBulbsAffine 0
    OPENCMD
    rendersprite tempSprite attackerx attackery solarbeamBulbsAffine
    spritemovedstdelay 8 tempSprite attacker 4
    goto ParticleConvergence

ConvergenceWaitingRoom:
    end

ConvergenceGlow:
    fadespritebg 1 0x477B FADETO true 7
    pauseframes 5
    fadespritebg 1 0x477B FADETO true 7
    pauseframes 5
    fadespritebg 1 0x477B FADEFROM true 7
    pauseframes 5
    fadespritebg 1 0x477B FADETO true 7
    pauseframes 5
    fadespritebg 1 0x477B FADEFROM true 7
    pauseframes 5
    fadespritebg 1 0x477B FADETO true 7
    pauseframes 5
    fadespritebg 1 0x477B FADEFROM true 7
    pauseframes 5
    end

.global SolarBeamAnimation
SolarBeamAnimation:
    fastsetbattlers
    BLOCKCMD
    addfadeplatformbg
    spritetobg target 8 8
    blendsemitransparent 13 3
    loadspritefull solarbeamSprite solarbeamPalette solarbeamOam
    copyvar beamParticle LASTRESULT
    loadspritefull solarbeamTailSprite solarbeamTailPalette solarbeamOam
    copyvar beamTailParticle LASTRESULT
    OPENCMD
    hidehpbars
    beginfade 2 0 FADETO true 14
    spriteblend2 attacker 10 0x477B
    pauseframes 5
    beginfade 1 0x477B FADETO true 16
    BLOCKCMD
    addvar targety 16
    loadsprite solarbeamTailSprite solarbeamPalette solarbeamOam
    rendersprite LASTRESULT targetx targety solarbeamAffine
    spritecallback LASTRESULT SCB_SpriteDeleteAfter30Frames
    subvar targety 32
    loadsprite solarbeamSprite solarbeamPalette solarbeamOam
    rendersprite LASTRESULT targetx targety solarbeamAffine
    spritecallback LASTRESULT SCB_SpriteDeleteAfter30Frames
    subvar targety 32
    loadsprite solarbeamSprite solarbeamPalette solarbeamOam
    rendersprite LASTRESULT targetx targety solarbeamAffine
    spritecallback LASTRESULT SCB_SpriteDeleteAfter30Frames
    subvar targety 32
    loadsprite solarbeamSprite solarbeamPalette solarbeamOam
    rendersprite LASTRESULT targetx targety solarbeamAffine
    spritecallback LASTRESULT SCB_SpriteDeleteAfter30Frames
    OPENCMD
    quakebg 1 2 0 4 2 false
    beginfade 1 0xFFFF FADEFROM false 16
    spriteblend2 attacker 9 0x477B
    spriteblend2 attacker 8 0x477B
    spriteblend2 attacker 7 0x477B
    spriteblend2 attacker 6 0x477B
    spriteblend2 attacker 5 0x477B
    spriteblend2 attacker 4 0x477B
    spriteblend2 attacker 3 0x477B
    spriteblend2 attacker 2 0x477B
    spriteblend2 attacker 1 0x477B
    spriteblend2 attacker 0 0x477B
    pauseframes 15
    clearblending
    deletesprite beamParticle
    deletesprite beamTailParticle
    showsprite target
    spritebgclear target
    showhpbars
    end

.pool
