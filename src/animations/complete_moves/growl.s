.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ growlParticle, 0x9006
.equ growlParticle2, 0x9007
.equ growlParticle3, 0x9008
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global GrowlAnimation
GrowlAnimation:
    fastsetbattlers
    spritetobg attacker 8 8
    hidehpbars
    startscript growlOnce false
    waitthread 1
    startscript growlOnce false
    waitthread 1
    clearblending
    showsprite attacker
    hidebg 1
    spritebgclear attacker
    showhpbars
    end

growlOnce:
    BLOCKCMD
    fastsetbattlers
    loadspritefull growlSprite growlPalette growlOam
    copyvar growlParticle LASTRESULT
    semitransparent growlParticle
    loadsprite growlSprite growlPalette growlOam
    copyvar growlParticle2 LASTRESULT
    semitransparent growlParticle2
    loadsprite growlSprite growlPalette growlOam
    copyvar growlParticle3 LASTRESULT
    semitransparent growlParticle3
    blendsemitransparent 13 3

    // three growl sprites angle and head out from source
    sideof attacker
    if2 0x0 call playerGrowlMovement
    OPENCMD
    BLOCKCMD
    animatesprite growlParticle growlTopAffine 0
    animatesprite growlParticle2 growlLeftAffine 0
    animatesprite growlParticle3 growlRightAffine 0
    OPENCMD
    BLOCKCMD
    rendersprite growlParticle attackerx attackery growlTopAffine
    rendersprite growlParticle2 attackerx attackery growlLeftAffine
    rendersprite growlParticle3 attackerx attackery growlRightAffine

    movesprite growlParticle 0 0xFFFD 21 false
    movesprite growlParticle2 0xFFFE 0xFFFE 21 false
    movesprite growlParticle3 2 0xFFFE 21 false
    setvar gLASTRESULT 0x0850
    startscript CircleBuffAttacker false
    OPENCMD
    pauseframes 15
    BLOCKCMD
    setvar coA 12
    setvar coB 4
    setvar amount 16
    setvar speed 4
    startscript FadeToBGAnimation true
    OPENCMD
    waitthread 2
    BLOCKCMD
    deletesprite growlParticle
    deletesprite growlParticle2
    deletesprite growlParticle3
    OPENCMD
    end

playerGrowlMovement:
    addvar attackery 32
    return



.pool
