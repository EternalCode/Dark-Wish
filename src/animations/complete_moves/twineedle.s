.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ needleParticle1, 0x9007
.equ needleParticle2, 0x9008
.equ angleBuffer, 0x9009

.global TwineedleAnimation
TwineedleAnimation:
    fastsetbattlers
    BLOCKCMD
    spritepriority attacker 2
    spritetobg target 8 8
    setprioritybg 1 3
    addfadebg1
    // impact particle
    loadspritefull impact1Sprite impact1Palette impactSmallOam
	copyvar impactParticle LASTRESULT
    animatesprite impactParticle impactSmallAffine 0
    addpalbuffer impactParticle false

    loadspritefull poisonstingSprite poisonstingPalette poisonstingOam
    copyvar needleParticle1 LASTRESULT
    loadspritefull poisonstingSprite poisonstingPalette poisonstingOam
    copyvar needleParticle2 LASTRESULT
    spritepriority needleParticle1 3
    spritepriority needleParticle2 3
    spritesetposition needleParticle1 attackerx attackery
    spritesetposition needleParticle2 attackerx attackery
    getangle attackerx attackery targetx targety angleBuffer
    applycustomaffine needleParticle1 256 256 angleBuffer
    applycustomaffine needleParticle2 256 256 angleBuffer
    OPENCMD
    showsprite needleParticle1
    showsprite needleParticle2

    spritemovedst 16 needleParticle1 target
    pauseframes 7
    startscript blendSpriteBg true
    spriteblend2 needleParticle1 10 0x6A1A
    spritemovedst 16 needleParticle2 target
    pauseframes 8
    spriteblend2 needleParticle2 10 0x6A1A
    pauseframes 6
    rendersprite impactParticle targetx targety impactSmallAffine
    quakebg 1 2 0 2 2 false
    spritecallback impactParticle SCB_SpriteDeleteAfter10Frames
    waitthread 1
    BLOCKCMD
    clearblending
    showsprite target
    hidebg 1
    OPENCMD
    spritebgclear target
    BLOCKCMD
    setprioritybg 1 1
    spritepriority attacker 3
    OPENCMD
    end

blendSpriteBg:
    beginfade 2 0x6C50 FADETO true 10
    beginfade 2 0x6C50 FADEFROM true 10
    end

.pool
