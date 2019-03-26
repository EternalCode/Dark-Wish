.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ punchParticle, 0x9006
.equ coefficientA, 0x9007
.equ coefficientB, 0x9008

.global MegapunchAnimation
MegapunchAnimation:
    loadspritefull bigfistSprite bigfistPalette bigfistOam
    copyvar punchParticle LASTRESULT
    fastsetbattlers
    hidehpbars
    spritetobg target 8 8
    setvar coefficientA 0
    setvar coefficientB 16
    spriteblend coefficientA coefficientB
    excludeblend punchParticle
    addfadeplatformbg
    beginfade 5 0 FADETO true 10
    rendersprite punchParticle targetx targety nullrsf
    setvar gLASTRESULT 0x00FA
    quakebg 1 5 0 8 3 false
    quakesprite punchParticle 3 3 4 1 false
    quakebg 1 1 0 2 1 false
    pauseframes 5
    animatesprite punchParticle fist2Affine 0
    startscript FireworkAnimation true

Punchloop:
    // gradually fadeout
    compare coefficientB 8
    if1 0x1 goto finishAnimation
    spriteblend coefficientA coefficientB
    subvar coefficientB 1
    addvar coefficientA 1
    goto Punchloop


finishAnimation:
    waitaffineanimation punchParticle
    deletesprite punchParticle
    beginfade 5 0 FADEFROM true 10
    showhpbars
    showsprite target
    hidebg 1
    clearblending
    spritebgclear target
    end

.pool
