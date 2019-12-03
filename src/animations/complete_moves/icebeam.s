.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ icebeamParticle, 0x9007
.equ angle, 0x9008
.equ counter, 0x9009

.global IceBeamAnimation
IceBeamAnimation:
    fastsetbattlers
    loadspritefull icebeamSprite icebeamPalette icebeamOam
    spritetobg target 8 8
    copyvar icebeamParticle LASTRESULT
    sideof attacker
    if2 0x0 goto playerPositionChange
    if2 0x1 goto opponentPositionChange
    blendsemitransparent 9 7
    hidehpbars
    addfadeplatformbg
    beginfade 3 0x3DAB FADETO true 10
    BLOCKCMD
    getangle attackerx attackery targetx targety angle
    startscript animFreeze true
    quakebg 1 2 0 6 2 false

spawnBeamParticle:
    OPENCMD
    BLOCKCMD
    compare counter 16
    if1 0x1 goto finishIceBeam
    loadsprite icebeamSprite icebeamPalette icebeamOam
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 70 angle 240 8 SpriteTravelDir
    semitransparent LASTRESULT
    addvar counter 1
    OPENCMD
    BLOCKCMD
    goto spawnBeamParticle

finishIceBeam:
    OPENCMD
    waitthread 1
    beginfade 3 0x3DAB FADEFROM true 10
    deletesprite icebeamParticle
    showhpbars
    end

playerPositionChange:
    addvar attackerx 24
    return

opponentPositionChange:
    subvar attackerx 24
    return

iceimpact:



.pool
