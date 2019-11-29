.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ disableParticle, 0x9006
.equ counter, 0x9007
.equ amount, 0x9008

.global DisableAnimation
DisableAnimation:
    fastsetbattlers
    loadspritefull leerSprite leerPalette disableOam
    copyvar disableParticle LASTRESULT
    spriteblend2 disableParticle 10 0x7620
    spritetobg target 8 8
    showsprite target
    semitransparent target
    spritepriority target 1
    blendsemitransparent 10 6
    hidehpbars
    sideof attacker
    if2 0 call playerSideParticle
    if2 1 call opponentSideParticle
    subvar attackery 8
    animatesprite disableParticle disableAffine 0
    BLOCKCMD
    rendersprite disableParticle attackerx attackery disableAffine
    spritecallback disableParticle SCB_SpriteDeleteWhenAffineEnds
    runvoidfunc GrayScaleBg3
    OPENCMD
    pauseframes 10
    setvar counter 256
    setvar amount 16
    addpalbuffer target false
    addfadebg1
    beginfade 1 0 FADETO false 6
    startscript GrowSprite true
    waitthread 1
    pauseframes 8
    setvar counter 192
    setvar amount 16
    startscript ShrinkSprite true
    waitthread 1
    beginfade 1 0 FADEFROM true 6
    runvoidfunc UnfadeBg3
    clearblending
    hidebg 1
    spritebgclear target
    nontransparent target
    spritepriority target 3
    showhpbars
    end

playerSideParticle:
    addvar attackerx 16
    return

opponentSideParticle:
    subvar attackerx 16
    return

GrowSprite:
    BLOCKCMD
    compare counter 192
    if1 0x1 goto finishGrow
    superscale target counter counter 256
    subvar counter amount
    OPENCMD
    goto GrowSprite

finishGrow:
    superscale target 192 192 256
    OPENCMD
    end

ShrinkSprite:
    BLOCKCMD
    compare counter 256
    if1 0x1 goto finishShrink
    superscale target counter counter 256
    addvar counter amount
    OPENCMD
    goto ShrinkSprite

finishShrink:
    superscale target 256 256 256
    OPENCMD
    end

.pool
