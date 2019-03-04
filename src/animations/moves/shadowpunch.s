.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ fistParticle, 0x9006
.equ impactParticle, 0x9008

.global ShadowpunchAnimation
ShadowpunchAnimation:
    fastsetbattlers
    loadspritefull fistSprite fistPalette fistOam
    copyvar fistParticle LASTRESULT
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    hidehpbars
    spriteblend 8 8

    // fade attacker dark
    addpalbuffer attacker false
    beginfade 2 0 FADETO true 12

    // attacker move forward
    BLOCKCMD
    spriteafterimage attacker 8 8 0
    movesprite attacker 5 0 6 true
    startscript ShadowpunchAfterImage true
    OPENCMD
    wait

    // attacker move backward
    movesprite attacker 0xFFFB 0 6 true
    wait
    beginfade 2 0 FADEFROM true 12
    end
.pool


ShadowpunchAfterImage:
    movebg 1 2 0 15 RIGHT true
    wait
    movebg 1 2 0 15 LEFT true
    wait
    spritebgclear attacker

    // defender to Bg for blending with fist and impact particle
    spritetobg target 8 8
    // render first sprite and a blinking copy of it
    animatesprite fistParticle fistAffinePtr 0
    BLOCKCMD
    subvar targetx 35
    rendersprite fistParticle targetx targety fistAffinePtr
    movesprite fistParticle 6 0 15 false
    fadespritebg 10 0 FADETO false 5
    OPENCMD
    addvar targetx 35
    setvar gLASTRESULT 0
    startscript FireworkAnimation true
    BLOCKCMD
    spriteblend2 impactParticle 12 0
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 false
    OPENCMD
    pauseframes 10
    deletesprite fistParticle
    deletesprite impactParticle
    BLOCKCMD
    showsprite target
    hidebg 1
    OPENCMD
    waittask TaskCreateSmallFireworkImpact
    spritebgclear target
    showhpbars
    end
