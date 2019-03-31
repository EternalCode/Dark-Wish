.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ fistParticle, 0x9006
.equ fistParticle2, 0x9007
.equ fistParticle3, 0x9008
.equ impactParticle, 0x9009
.equ xOff, 0x900A
.equ xOffRestore, 0x900B
.equ attacker2, 0x900C
.equ attacker3, 0x900F
.equ tag, 900
.equ tag2, 901

.global ShadowpunchAnimation
ShadowpunchAnimation:
    BLOCKCMD
    fastsetbattlers
    loadspritefull fistSprite fistPalette fistOam
    copyvar fistParticle LASTRESULT
    semitransparent fistParticle
    spritepriority fistParticle 0
    loadsprite fistSprite fistPalette fistOam
    copyvar fistParticle2 LASTRESULT
    spritepriority fistParticle2 0
    semitransparent fistParticle2
    loadsprite fistSprite fistPalette fistOam
    copyvar fistParticle3 LASTRESULT
    spritepriority fistParticle3 0
    semitransparent fistParticle3
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spritepriority impactParticle 1
    semitransparent impactParticle
    clonebattler attacker attackerx attackery tag
    copyvar attacker2 LASTRESULT
    semitransparent attacker2
    clonebattler attacker attackerx attackery tag2
    copyvar attacker3 LASTRESULT
    semitransparent attacker3
    OPENCMD
    spritetobg target 8 8
    showbg 1
    blendsemitransparent 12 4
    hidehpbars

    // fade attacker dark
    addpalbuffer attacker false
    addpalbuffer attacker2 false
    addpalbuffer attacker3 false
    beginfade 2 0 FADETO true 12

    // attacker move forward
    sideof attacker
    if2 0 call playermove
    if2 1 call oppmove
    showbg 2
    setprioritybg 2 0
    movebg 2 6 0 30 RIGHT false
    runvoidfunc AddBg2Blend
    movesprite attacker xOff 0 6 false
    pauseframes 1
    movesprite attacker2 xOff 0 6 false
    pauseframes 1
    movesprite attacker3 xOff 0 6 true
    wait
    startscript PunchAnimation true
    // attacker move backward
    movesprite attacker xOffRestore 0 6 true
    pauseframes 1
    movesprite attacker2 xOffRestore 0 6 true
    pauseframes 1
    movesprite attacker3 xOffRestore 0 6 true
    wait
    waitthread 1
    hidebg 2
    movebg 2 0 0 1 0 false
    deletesprite fistParticle
    deletesprite fistParticle2
    deletesprite fistParticle3
    beginfade 2 0 FADEFROM true 12
    deletesprite attacker2
    deletesprite attacker3
    clearblending
    showsprite target
    hidebg 1
    spritebgclear target
    setprioritybg 2 2
    showhpbars
    end

playermove:
    loadbg2 32 playerwindTiles playerwindMap playerwindPal
    setvar xOff 5
    setvar xOffRestore 0xFFFB
    return

oppmove:
    loadbg2 32 playerwindTiles playerwindMap playerwindPal
    movebg 2 0 48 1 UP false
    setvar xOff 0xFFFB
    setvar xOffRestore 5
    return

PunchAnimation:
    BLOCKCMD
    sideof attacker
    if2 0 call punchPlayer
    if2 1 call punchOpponent
    animatesprite fistParticle fistAffine 0
    // TODO Firework effect here
    setvar gLASTRESULT 0
    startscript ShadowPunchFirework false
    OPENCMD
    BLOCKCMD
    rendersprite fistParticle targetx targety fistAffine
    movesprite fistParticle xOff 0 16 false
    OPENCMD
    animatesprite fistParticle2 fistAffine 0
    BLOCKCMD
    rendersprite fistParticle2 targetx targety fistAffine
    movesprite fistParticle2 xOff 0 16 false
    OPENCMD
    animatesprite fistParticle3 fistAffine 0
    BLOCKCMD
    rendersprite fistParticle3 targetx targety fistAffine
    movesprite fistParticle3 xOff 0 16 false
    OPENCMD
    BLOCKCMD
    fastsetbattlers
    spriteblend2 impactParticle 12 0
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 false
    OPENCMD
    pauseframes 5
    nontransparent fistParticle
    pauseframes 4
    deletesprite impactParticle
    end

punchPlayer:
    subvar targetx 32
    setvar xOff 6
    return

punchOpponent:
    addvar targetx 32
    setvar xOff 0xFFFA
    return

.equ glowballParticle, 0x9006
.equ glowcolor, 0x900C
.equ speed, 2
.equ speedDir, 3
.equ negSpeed, 0xFFFE
.equ negSpeedDir, 0xFFFD

ShadowPunchFirework:
    BLOCKCMD
    copyvar glowcolor gLASTRESULT
    fastsetbattlers
    loadspritefull glowballSprite glowballPalette shadowpunchGlowBallOam
    copyvar glowballParticle LASTRESULT
    OPENCMD

    // up
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT 0 negSpeedDir 20 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // up right
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT speed negSpeed 20 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // down right
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT speed speed 20 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // down left
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT negSpeed speed 20 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // up left
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT negSpeed negSpeed 20 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    pauseframes 20
    deletesprite glowballParticle
    end

.pool
