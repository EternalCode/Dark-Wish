.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ hornParticle, 0x9006
.equ impactParticle, 0x9007
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global HornAttackAnimation
HornAttackAnimation:
    fastsetbattlers
    loadspritefull impact5Sprite impact5Palette impact5Oam
    copyvar impactParticle LASTRESULT
    sideof attacker
    if2 0x0 call attackerisplayer
    if2 0x1 call attackerisopponent
    waitthread 1
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    spriteblend2 impactParticle 10 0x57FF
    semitransparent impactParticle
    quakebg 1 2 0 2 2 true
    rendersprite impactParticle targetx targety nullrsf
    wait
    deletesprite impactParticle
    waitthread 1
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    end

attackerisplayer:
    loadspritefull hornSprite hornPalette hornOam
    copyvar hornParticle LASTRESULT
    movesprite attacker 2 0 8 true
    wait
    movesprite attacker 0xFFFF 0 16 true
    fastsetbattlers
    call fadeHornIn
    BLOCKCMD
    semitransparent hornParticle
    rendersprite hornParticle attackerx attackery nullrsf
    OPENCMD
    spritemovedst 22 hornParticle target
    wait
    return

attackerisopponent:
    loadspritefull hornSprite hornPalette hornFlippedOam
    copyvar hornParticle LASTRESULT
    movesprite attacker 0xFFFE 0 8 true
    wait
    movesprite attacker 1 0 16 true
    fastsetbattlers
    call fadeHornIn
    BLOCKCMD
    semitransparent hornParticle
    rendersprite hornParticle attackerx attackery nullrsf
    OPENCMD
    spritemovedst 22 hornParticle target
    return

fadeHornIn:
    BLOCKCMD
    setvar coA 8
    setvar coB 8
    setvar amount 0
    setvar speed 2
    startscript FadeFromBgAmountAnimation true
    OPENCMD
    return

.pool
