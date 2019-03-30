.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ leerParticle, 0x9006
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global LeerAnimation
LeerAnimation:
    fastsetbattlers
    spritetobg attacker 8 8
    addfadeplatformbg
    loadspritefull leerSprite leerPalette leerOam
    copyvar leerParticle LASTRESULT
    semitransparent leerParticle
    blendsemitransparent 16 0
    hidehpbars
    beginfade 4 0 FADETO true 10
    BLOCKCMD
    sideof attacker
    if2 0x0 call rightOfAttacker
    if2 0x1 call leftOfAttacker
    setframessprite 0 leerParticle leerFrames
    OPENCMD
    rendersprite leerParticle attackerx attackery nullrsf
    pauseframes 9
    quakesprite target 2 0 2 2 false
    BLOCKCMD
    setvar coA 16
    setvar coB 0
    setvar speed 2
    setvar amount 16
    startscript FadeToBGAnimation true
    OPENCMD
    waitthread 1
    deletesprite leerParticle
    beginfade 4 0 FADEFROM true 10
    clearblending
    showsprite attacker
    hidebg 1
    spritebgclear attacker
    showhpbars
    end

leftOfAttacker:
    subvar attackerx 12
    return

rightOfAttacker:
    addvar attackerx 12
    addvar attackery 16
    return

.pool
