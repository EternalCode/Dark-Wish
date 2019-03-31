.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ fistParticle, 0x9006
.equ footParticle, 0x9007
.equ rotation, 0x9008
.equ scaleDelta, 0x9009
.equ counter, 0x900A
.equ tempSprite, 0x900B
.equ impactParticle, 0x900C
.equ posxBuff, 0x900D
.equ posyBuff, 0x900E
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global ThrashAnimation
ThrashAnimation:
    fastsetbattlers
    loadspritefull squarefistSprite squarefistPalette squarefistOam
    copyvar fistParticle LASTRESULT
    loadspritefull stompSprite stompPalette thrashfootOam
    copyvar footParticle LASTRESULT
    loadspritefull impact7Sprite impact7Palette impact7Oam
    copyvar impactParticle LASTRESULT
    spritetobg target 8 8
    semitransparent fistParticle
    semitransparent footParticle
    spriteblend2 fistParticle 10 0
    spriteblend2 footParticle 10 0
    hidehpbars

    // first thrash set
    copyvar tempSprite fistParticle
    random 0 256
    copyvar rotation LASTRESULT
    startscript AttackerMovementThrash false
    call ThrashEffectParticle
    BLOCKCMD
    loadspritefull impact7Sprite impact7Palette impact7Oam
    copyvar impactParticle LASTRESULT
    copyvar tempSprite footParticle
    hidesprite fistParticle
    random 0 256
    copyvar rotation LASTRESULT
    OPENCMD
    call ThrashEffectParticle
    hidesprite footParticle

    waitthread 1

    // second thrash set
    loadspritefull impact7Sprite impact7Palette impact7Oam
    copyvar impactParticle LASTRESULT
    copyvar tempSprite fistParticle
    random 0 256
    copyvar rotation LASTRESULT
    startscript AttackerMovementThrash false
    call ThrashEffectParticle
    BLOCKCMD
    loadspritefull impact7Sprite impact7Palette impact7Oam
    copyvar impactParticle LASTRESULT
    copyvar tempSprite footParticle
    hidesprite fistParticle
    random 0 256
    copyvar rotation LASTRESULT
    OPENCMD
    call ThrashEffectParticle
    hidesprite footParticle
    showsprite target
    spritebgclear target
    hidebg 1
    showhpbars
    deletesprite fistParticle
    deletesprite footParticle
    end

ThrashEffectParticle:
    BLOCKCMD
    setvar coA 0
    setvar coB 16
    setvar speed 4
    setvar amount 0
    setvar counter 128
    setvar scaleDelta 64
    startscript FadeFromBgAmountAnimation true
    startscript ShrinkSprite true
    pickrandompos targetx targety 24 24
    spritesetposition tempSprite targetx targety
    fastsetbattlers
    superscale tempSprite counter counter rotation
    OPENCMD
    showsprite tempSprite
    waitthread 2
    waitthread 3
    return

ShrinkSprite:
    BLOCKCMD
    compare counter 384
    if1 0x1 goto finishShrink
    superscale tempSprite counter counter rotation
    addvar counter scaleDelta
    OPENCMD
    goto ShrinkSprite

finishShrink:
    superscale tempSprite 384 384 rotation
    spriteblend2 tempSprite 0 0
    call ThrashImpactParticle
    OPENCMD
    end

ThrashImpactParticle:
    animatesprite impactParticle impact7ThrashAffine 0
    spritepriority tempSprite 0
    spritebufferposition tempSprite posxBuff posyBuff
    rendersprite impactParticle posxBuff posyBuff impact7ThrashAffine
    spritecallback impactParticle SCB_SpriteDeleteWhenAffineEnds
    quakebg 1 2 0 2 2 false
    return

AttackerMovementThrash:
    BLOCKCMD
    fastsetbattlers
    addvar attackery 10
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 33 10 10 1 8 true false 0
    OPENCMD
    subvar attackery 10
    spritesetposition attacker attackerx attackery
    end



.pool
