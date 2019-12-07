.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ randx, 0x9007
.equ randy, 0x9008
.equ counter, 0x9009


.global StrengthAnimation
StrengthAnimation:
    fastsetbattlers
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    blendsemitransparent 8 8
    hidehpbars
    animatesprite attacker strengthShrinkAffine 0
    movesprite attacker 2 2 1 false
    pauseframes 1
    movesprite attacker 0xFFFE 2 1 false
    pauseframes 1
    movesprite attacker 2 2 1 false
    pauseframes 1
    movesprite attacker 0xFFFE 2 1 false
    pauseframes 20
    // flash red and back 3 times
    addpalbuffer attacker false
    beginfade 1 0x107D FADETO true 12
    beginfade 1 0x107D FADEFROM true 12

    beginfade 1 0x107D FADETO true 12
    beginfade 1 0x107D FADEFROM true 12

    beginfade 1 0x107D FADETO true 12
    beginfade 1 0x107D FADEFROM true 12
    movesprite attacker 0 0xFFFE 4 true
    wait
    spritetobg target 8 8
    waitaffineanimation attacker
    depthlessorbitbg 64 32 8 LEFT 12 128
    startscript spawnImpactsRandom true
    waittask TaskAnimOrbitFastStepNoPriority
    waitthread 1
    showsprite target
    spritebgclear target
    clearblending
    deletesprite impactParticle
    showhpbars
    end


spawnImpactsRandom:
    BLOCKCMD
    copyvar randx targetx
    copyvar randy targety
    subvar randx 32
    subvar randy 24
    random 0 64
    addvar randx LASTRESULT
    random 0 40
    addvar randy LASTRESULT
    loadsprite impact1Sprite impact1Palette impact1Oam
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    rendersprite LASTRESULT randx randy nullrsf
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    addvar counter 1
    OPENCMD
    compare counter 12
    if1 0 goto spawnImpactsRandom
    end

.pool
