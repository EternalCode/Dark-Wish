.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ beamParticle, 0x9006
.equ counter, 0x9007
.equ TempSprite, 0x9008

.global AuroraBeamAnimation
AuroraBeamAnimation:
    fastsetbattlers
    loadspritefull psybeamSprite psybeamPalette aurorabeamOam
    copyvar beamParticle LASTRESULT
    spritetobg target 8 8
    showbg 1
    hidehpbars
    addfadeplatformbg
    addfadebg2
    loadbg2 32 aurorabeambgTiles aurorabeambgMap aurorabeambgPal
    beginfade 2 0 FADETO true 16
    showbg 2
    movebg 2 1 0 120 LEFT false
    beginfade 2 0 FADEFROM true 16
    startscript quakeSpriteBg true

loopParticles:
    BLOCKCMD
    compare counter 28
    if1 0x1 goto finishAnim
    loadsprite psybeamSprite psybeamPalette aurorabeamOam
    copyvar TempSprite LASTRESULT
    animatesprite TempSprite aurorabeamOddAffine 0
    rendersprite TempSprite attackerx attackery aurorabeamOddAffine
    setframessprite 0 TempSprite psybeamFrames
    spritemovedst 30 TempSprite target

    loadsprite psybeamSprite psybeamPalette aurorabeamOam
    copyvar TempSprite LASTRESULT
    animatesprite TempSprite aurorabeamEvenAffine 0
    rendersprite TempSprite attackerx attackery aurorabeamEvenAffine
    setframessprite 0 TempSprite psybeamFrames
    spritemovedst 16 TempSprite target

    addvar counter 1
    OPENCMD
    goto loopParticles


finishAnim:
    OPENCMD
    beginfade 2 0 FADETO true 16
    hidebg 2
    beginfade 2 0 FADEFROM true 16
    waitthread 1
    setbgpos 2 0 0
    showhpbars
    end

quakeSpriteBg:
    pauseframes 12
    quakebg 1 2 0 16 2 true
    wait
    showsprite target
    spritebgclear target
    end

.pool
