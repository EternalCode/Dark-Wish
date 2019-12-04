.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ psybeamParticle, 0x9006
.equ counter, 0x9007
.equ TempSprite, 0x9008

.global PsybeamAnimation
PsybeamAnimation:
    fastsetbattlers
    loadspritefull psybeamSprite psybeamPalette psybeamOam
    copyvar psybeamParticle LASTRESULT
    spritetobg target 8 8
    startscript PsybeamSway true

loopParticles:
    BLOCKCMD
    compare counter 20
    if1 0x1 goto finishAnim
    loadsprite psybeamSprite psybeamPalette psybeamOam
    copyvar TempSprite LASTRESULT
    setframessprite 0 TempSprite psybeamFrames
    rendersprite TempSprite attackerx attackery nullrsf
    spritemovedst 30 TempSprite target
    addvar counter 1
    OPENCMD
    goto loopParticles


finishAnim:
    OPENCMD
    waitthread 1
    deletesprite psybeamParticle
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite psybeamParticle
    end


PsybeamSway:
    pauseframes 10
    fadespritebg 2 0x763D FADETO 0 12
    movebg 1 2 0 5 LEFT true
    wait
    movebg 1 2 0 5 RIGHT true
    wait
    movebg 1 2 0 5 RIGHT true
    wait
    movebg 1 2 0 5 LEFT true
    wait
    movebg 1 2 0 5 LEFT true
    wait
    movebg 1 2 0 5 RIGHT true
    wait
    movebg 1 2 0 5 RIGHT true
    wait
    movebg 1 2 0 5 LEFT true
    wait
    fadespritebg 2 0x763D FADEFROM 0 12
    end

.pool
