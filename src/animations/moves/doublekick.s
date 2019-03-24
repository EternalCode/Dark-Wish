.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ doublekickParticle, 0x9006
.equ doublekickInnerParticle, 0x9007
.equ tempSprite, 0x9008
.equ impactParticle, 0x9009
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global DoubleKickAnimation
DoubleKickAnimation:
    fastsetbattlers
    loadspritefull impact5Sprite impact5Palette impact5Oam
    copyvar impactParticle LASTRESULT
    loadspritefull stompSprite stompPalette doublekickOam
    copyvar doublekickParticle LASTRESULT
    loadsprite stompSprite stompPalette doublekickOam
    copyvar doublekickInnerParticle LASTRESULT
    setframessprite 0 doublekickParticle doublekickFrames
    spritetobg target 8 8
    copyvar tempSprite doublekickParticle
    call DoubleKickSpawnFootGrowFaded
    copyvar tempSprite doublekickInnerParticle
    call DoubleKickSpawnFootGrowFaded
    BLOCKCMD
    deletesprite impactParticle
    showsprite target
    OPENCMD
    hidebg 1
    clearblending
    spritebgclear target
    end

DoubleKickSpawnFootGrowFaded:
    BLOCKCMD
    animatesprite tempSprite doublekickBigAffine 0
    setvar gLASTRESULT 0x00FA
    startscript FireworkAnimationSmaller true
    OPENCMD
    BLOCKCMD
    semitransparent tempSprite
    spritepriority tempSprite 1
    setvar coA 8
    setvar coB 8
    setvar speed 2
    setvar amount 0
    startscript FadeFromBgAmountAnimation true
    rendersprite tempSprite targetx targety doublekickBigAffine
    OPENCMD
    waitthread 2
    BLOCKCMD
    quakebg 1 2 0 2 2 false
    spriteblend2 tempSprite 10 0x0012
    nontransparent tempSprite
    spriteblend 8 8
    rendersprite impactParticle targetx targety nullrsf
    OPENCMD
    pauseframes 5
    spriteblend2 tempSprite 0 0x0012
    BLOCKCMD
    deletesprite tempSprite
    hidesprite impactParticle
    OPENCMD
    waitthread 1
    showsprite target
    spritetobg target 8 8
    return

.pool
