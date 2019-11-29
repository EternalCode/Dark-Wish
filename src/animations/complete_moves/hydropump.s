.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ hydroParticle, 0x9006
.equ counter, 0x9007
.equ waterSplash, 0x9008

.global HydroPumpAnimation
HydroPumpAnimation:
    fastsetbattlers
    loadspritefull hydropumpSprite hydropumpPalette hydropumpOam
    copyvar hydroParticle LASTRESULT
    loadbg2 32 hydropumpbgTiles hydropumpbgMap hydropumpbgPal
    BLOCKCMD
    addfadeplatformbg
    addfadebg2
    spritetobg target 8 8
    showbg 1
    blendsemitransparent 12 4
    hidehpbars
    OPENCMD
    beginfade 2 0 FADETO true 16
    BLOCKCMD
    sideof attacker
    if2 0x0 goto playerbgmove
    if2 0x1 goto opponentbgmove
    showbg 2
    OPENCMD
    beginfade 1 0 FADEFROM true 16
    startscript HydroPumpAffectTarget true

hydropumpLoop:
    BLOCKCMD
    compare counter 40
    if1 0x1 goto finishAnim
    loadsprite hydropumpSprite hydropumpPalette hydropumpOam
    setframessprite 0 LASTRESULT hydropumpFrames
    animatesprite LASTRESULT hydropumpAffine 0
    OPENCMD
    BLOCKCMD
    rendersprite LASTRESULT attackerx attackery hydropumpAffine
    spritemovedstdelay 30 LASTRESULT target 1
    addvar counter 1
    OPENCMD
    goto hydropumpLoop

finishAnim:
    OPENCMD
    beginfade 2 0 FADETO true 16
    hidebg 2
    beginfade 1 0 FADEFROM true 16
    pauseframes 10
    deletesprite hydroParticle
    waitthread 1
    showsprite target
    hidebg 1
    spritebgclear target
    showhpbars
    end

playerbgmove:
    movebg 2 6 0 190 RIGHT false
    subvar attackery 8
    addvar attackerx 8
    return

opponentbgmove:
    movebg 2 6 0 190 LEFT false
    subvar attackerx 8
    addvar attackery 8
    return

HydroPumpAffectTarget:
    pauseframes 24
    loadspritefull watersplashSprite watersplashPalette watersplashOam
	copyvar waterSplash LASTRESULT
    spritepriority waterSplash 1
    semitransparent waterSplash
    setframessprite 0 waterSplash watersplashFrames
    rendersprite waterSplash targetx targety nullrsf
    quakebg 1 2 0 20 2 true
    wait
    deletesprite waterSplash
    end

.pool
