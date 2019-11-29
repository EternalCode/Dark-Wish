.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ mistParticle1, 0x9006
.equ mistParticle2, 0x9007
.equ mistParticle3, 0x9008
.equ mistParticle4, 0x9009
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global MistAnimation
MistAnimation:
    fastsetbattlers
    spritetobg attacker 8 8
    blendsemitransparent 2 14
    addfadeplatformbg
    //addfadebg1
    loadspritefull mistSprite mistPalette mistOam
    copyvar mistParticle1 LASTRESULT
    spriteblend2 LASTRESULT 16 0xFFFF
    semitransparent LASTRESULT

    loadsprite mistSprite mistPalette mistOam
    copyvar mistParticle2 LASTRESULT
    spriteblend2 LASTRESULT 16 0xFFFF
    semitransparent LASTRESULT

    loadsprite mistSprite mistPalette mistOam
    copyvar mistParticle3 LASTRESULT
    spriteblend2 LASTRESULT 16 0xFFFF
    semitransparent LASTRESULT

    loadsprite mistSprite mistPalette mistOam
    copyvar mistParticle4 LASTRESULT
    spriteblend2 LASTRESULT 16 0xFFFF
    semitransparent LASTRESULT
    hidehpbars

    BLOCKCMD
    subvar attackery 8
    subvar attackerx 28
    rendersprite mistParticle1 attackerx attackery nullrsf
    beginfade 4 0xFFFF FADETO false 12
    fastsetbattlers
    addvar attackerx 28
    rendersprite mistParticle2 attackerx attackery nullrsf
    fastsetbattlers
    addvar attackery 8
    subvar attackerx 28
    rendersprite mistParticle3 attackerx attackery nullrsf
    fastsetbattlers
    addvar attackery 16
    addvar attackerx 28
    rendersprite mistParticle4 attackerx attackery nullrsf
    OPENCMD
    BLOCKCMD
    setvar coA 2
    setvar coB 14
    setvar amount 0
    setvar speed 2
    startscript FadeFromBgAmountAnimation true
    movesprite mistParticle1 1 0 28 false
    movesprite mistParticle2 0xFFFF 0 28 false
    movesprite mistParticle3 1 0 28 false
    movesprite mistParticle4 0xFFFF 0 28 false
    OPENCMD
    waitthread 1
    BLOCKCMD
    setvar coA 16
    setvar coB 0
    setvar amount 16
    setvar speed 1
    startscript FadeToBGAnimation true
    movesprite mistParticle1 1 0 28 false
    movesprite mistParticle2 0xFFFF 0 28 false
    movesprite mistParticle3 1 0 28 false
    movesprite mistParticle4 0xFFFF 0 28 true
    OPENCMD
    wait
    BLOCKCMD
    deletesprite mistParticle1
    deletesprite mistParticle2
    deletesprite mistParticle3
    deletesprite mistParticle4
    beginfade 4 0xFFFF FADEFROM true 12
    OPENCMD
    waitthread 1
    clearblending
    showsprite attacker
    hidebg 1
    spritebgclear attacker
    showhpbars
    end

.pool
