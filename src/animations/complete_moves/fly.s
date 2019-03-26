.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ flyParticle, 0x9006
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

.global FlyAnimation
FlyAnimation:
    hidehpbars
    fastsetbattlers
    BLOCKCMD
    addfadeplatformbg
    addfadebg2
    loadbg2 32 flybgTiles flybgMap flybgPal
    loadspritefull flySprite flyPalette flyOam
    copyvar flyParticle LASTRESULT
    spriteblend2 flyParticle 11 0xFFFF
    OPENCMD

    // glow platform & Bg2 white
    beginfade 4 0xFFFF FADETO true 16
    movebg 2 0 8 150 DOWN false
    showbg 2
    beginfade 4 0xFFFF FADEFROM true 16

    // show fly circle, grow & fade
    BLOCKCMD
    subvar targetx 32
    subvar targety 64
    animatesprite flyParticle flySmallAffine 0
    OPENCMD
    rendersprite flyParticle targetx targety flySmallAffine
    movesprite flyParticle 2 4 16 true
    waitthread 1
    wait
    BLOCKCMD
    fastsetbattlers
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    deletesprite flyParticle
    OPENCMD
    pauseframes 1
    BLOCKCMD
    quakebg 1 2 0 2 2 false
    quakesprite target 2 0 2 2 false
    OPENCMD
    showsprite attacker
    // glow platform & bg2 white
    beginfade 4 0xFFFF FADETO true 16
    hidebg 2
    beginfade 4 0xFFFF FADEFROM true 16
    waitthread 1
    showhpbars
    end


.global FlyWindUpAnimation
FlyWindUpAnimation:
    hidehpbars
    fastsetbattlers
    BLOCKCMD
    addfadeplatformbg
    addfadebg2
    showbg 1
    spritetobg attacker 8 8
    loadbg2 32 flybgTiles flybgMap flybgPal
    loadspritefull flySprite flyPalette flyOam
    copyvar flyParticle LASTRESULT
    semitransparent flyParticle
    setvar coA 16
    setvar coB 0
    setvar speed 1
    setvar amount 10
    OPENCMD

    // glow platform & Bg2 white
    beginfade 4 0xFFFF FADETO true 16
    movebg 2 0 8 200 UP false
    showbg 2
    beginfade 4 0xFFFF FADEFROM true 16

    // show fly circle, grow & fade
    startscript FadeToBGAmountAnimation true
    animatesprite flyParticle flyAffine 0
    waitthread 1
    BLOCKCMD
    sideof attacker
    compare LASTRESULT PLAYERSIDE
    if2 0x1 call repositionFlySprite
    OPENCMD
    rendersprite flyParticle attackerx attackery flyAffine
    waitaffineanimation flyParticle
    hidesprite attacker
    hidebg 1

    // fly circle squish & go up off screen
    BLOCKCMD
    animatesprite flyParticle flySquishAffine 0
    movesprite flyParticle 0 0xFFFC 40 true
    setvar amount 0
    startscript FadeFromBgAmountAnimation true
    OPENCMD
    wait
    waitthread 1

    // glow platform & bg2 white
    beginfade 4 0xFFFF FADETO true 16
    BLOCKCMD
    hidebg 2
    hidebg 1
    spritebgclear target
    hidesprite attacker
    OPENCMD
    beginfade 4 0xFFFF FADEFROM true 16
    deletesprite flyParticle
    showhpbars
    end

repositionFlySprite:
    addvar attackery 16
    return

.pool
