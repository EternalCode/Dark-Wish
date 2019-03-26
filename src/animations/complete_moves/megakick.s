.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ footParticle, 0x9006
.equ footGrowParticle, 0x9007
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013


.global MegaKickAnimation
MegaKickAnimation:
    fastsetbattlers
    addfadeplatformbg
    addfadebg2
    hidebg 2
    sideof attacker
    if2 0x0 call loadOpponentsideBg
    if2 0x1 call loadPlayersideBg
    BLOCKCMD
    loadspritefull stompSprite stompPalette stompOam
    copyvar footParticle LASTRESULT
    spritepriority footParticle 0
    loadsprite stompSprite stompPalette doublekickOam
    copyvar footGrowParticle LASTRESULT
    spritepriority footGrowParticle 1
    semitransparent footGrowParticle
    spriteblend2 footParticle 10 0x0012
    spriteblend2 footGrowParticle 10 0x0012
    spritetobg target 8 8
    showbg 1
    OPENCMD
    hidehpbars

FadeBgsToBlack:
    // fade black
    beginfade 1 0 FADETO true 16
    setvar gLASTRESULT 0x00FA
    startscript FireworkAnimationNoBlend true
    pauseframes 3

ShowFootAndGrowingAfterImage:
    BLOCKCMD
    setvar coA 16
    setvar coB 0
    setvar speed 1
    setvar amount 16
    startscript FadeToBGAnimation true
    rendersprite footParticle targetx targety nullrsf
    rendersprite footGrowParticle targetx targety megakickGrowAffine
    depthlessorbit footParticle target 200 1 1 0 12 false false 0
    animatesprite footGrowParticle megakickGrowAffine 0
    showbg 2
    quakebg 2 5 0xFE 8 2 false
    OPENCMD
    // unfade
    beginfade 1 0 FADEFROM true 16
    waitthread 2
    deletesprite footParticle
    deletesprite footGrowParticle

Restore:
    beginfade 1 0 FADETO true 16
    hidebg 2
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    beginfade 1 0 FADEFROM true 16
    showhpbars
    end

loadPlayersideBg:
    loadbg2 32 megakickplayerbgTiles megakickplayerbgMap megakickplayerbgPal
    return

loadOpponentsideBg:
    loadbg2 32 megakickbgTiles megakickbgMap megakickbgPal
    return




.pool
