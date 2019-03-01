.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ burnParticle, 0x9006
.equ counter, 0x9007
.equ initialSprite, 0x9008

.global animBurnEffect
animBurnEffect:
    fastsetbattlers
    setvar counter 0x0
    copyvar 0x8000 targetx
    copyvar 0x8001 targety

redset:
    addpalbuffer target 0
    beginfade 3 0x1CF8 FADETO 0 10
    loadspritefull burnSprite burnPalette burnOam
    copyvar initialSprite LASTRESULT

burnLoop:
    compare counter 5
    if1 0x1 goto finishburn
    loadsprite burnSprite burnPalette burnOam
    copyvar burnParticle LASTRESULT
    animatesprite burnParticle burnAffinePtr
    runtask TaskBurnEffect burnParticle 0 0 0
    addvar counter 1
    goto burnLoop

finishburn:
    beginfade 3 0x1CF8 FADEFROM 1 10
    waittask TaskBurnEffect
    deletesprite initialSprite
    end
.pool


.thumb
.align 2
.equ poisonParticle, 0x9006

.global animPoisonEffect
animPoisonEffect:
    fastsetbattlers
    setvar counter 0x0
    copyvar 0x8000 targetx
    copyvar 0x8001 targety

purpleset:
    addpalbuffer target 0
    beginfade 3 0x6C50 FADETO 0 10
    loadspritefull poisonSprite poisonPalette poisonOam
    copyvar initialSprite LASTRESULT

poisonLoop:
    compare counter 4
    if1 0x1 goto finishpoison
    loadsprite poisonSprite poisonPalette poisonOam
    copyvar poisonParticle LASTRESULT
    runtask TaskMovePoisonBubble poisonParticle 2 12 30
    pauseframes 5
    addvar counter 1
    goto poisonLoop

finishpoison:
    beginfade 3 0x6C50 FADEFROM 1 10
    waittask TaskMovePoisonBubble
    deletesprite initialSprite
    end
.pool


.global animBadlyPoisoned
animBadlyPoisoned:
    startscript animPoisonEffect false
    fastsetbattlers
    pauseframes 15
    quakesprite target 6 0 2 5 true
    end
.pool

.equ paralyzeParticle, 0x9006
.global animParalyzed
animParalyzed:
    fastsetbattlers
    addpalbuffer target 0
    loadspritefull paralyzeSprite paralyzePalette paralyzeOam
    copyvar paralyzeParticle LASTRESULT
    rendersprite paralyzeParticle targetx targety nullrsf
    setframessprite 0 paralyzeParticle paralyzeLoopPtr
    quakesprite target 4 0 2 5 0
    beginfade 3 0 FADETO 1 10
    beginfade 3 0 FADEFROM 1 10
    deletesprite paralyzeParticle
    end
.pool

.equ freezeParticle, 0x9006
.global animFreeze
animFreeze:
    fastsetbattlers
    copyvar 0x8000 targetx
    copyvar 0x8001 targety
    loadspritefull freezeSprite freezePalette freezeOam
    copyvar initialSprite LASTRESULT
    spritetobg target 8 8
    fadespritebg 3 0x6546 FADETO 0 10
    spriteblend 8 8
    setvar counter 0x0

freezeLoop:
    compare counter 8
    if1 0x1 goto finishfreeze
    loadsprite freezeSprite freezePalette freezeOam
    copyvar freezeParticle LASTRESULT
    animatesprite freezeParticle freezeAffinePtr
    runtask TaskFreezeEffect freezeParticle 0 0 0
    pauseframes 2
    addvar counter 1
    goto freezeLoop

finishfreeze:
    fadespritebg 3 0x6546 FADEFROM true 10
    waittask TaskFreezeEffect
    showsprite target
    spritebgclear target
    deletesprite initialSprite
    end
.pool


.equ confusedParticle1, 0x9006
.equ confusedParticle2, 0x9009
.equ confusedParticle3, 0x900A
.global animConfused
animConfused:
    fastsetbattlers
    loadspritefull confusedSprite confusedPalette confusedOam
    copyvar initialSprite LASTRESULT
    subvar targety 16
    setvar counter 0
    // load particles for ducks
    loadsprite confusedSprite confusedPalette confusedOam
    copyvar confusedParticle1 LASTRESULT
    loadsprite confusedSprite confusedPalette confusedOam
    copyvar confusedParticle2 LASTRESULT
    loadsprite confusedSprite confusedPalette confusedOam
    copyvar confusedParticle3 LASTRESULT
    // set ducks animframe
    setframessprite 0 confusedParticle1 confusedLoopPtr
    setframessprite 0 confusedParticle2 confusedLoopPtr
    setframessprite 0 confusedParticle3 confusedLoopPtr
    // set ducks orbit cb
    orbit confusedParticle1 target 60 30 8 0 9 false true 85
    orbit confusedParticle2 target 60 30 8 0 9 false true 170
    orbit confusedParticle3 target 60 30 8 0 9 false true 255
    // render ducks
    rendersprite confusedParticle1 targetx targety nullrsf
    rendersprite confusedParticle2 targetx targety nullrsf
    rendersprite confusedParticle3 targetx targety nullrsf


finishConfused:
    waittask TaskMoveSinLeftAndRight
    pauseframes 10
    deletesprite initialSprite
    end
.pool


.equ infatuationParticle, 0x9006
.equ infatuationX, 0x9009
.equ infatuationY, 0x900A
.global animInfatuation
animInfatuation:
    fastsetbattlers
    loadspritefull infatuationSprite infatuationPalette infatuationOam
    copyvar initialSprite LASTRESULT
    setvar counter 0
    copyvar 0x8000 targetx
    copyvar 0x8001 targety

infatuationLoop:
    compare counter 4
    if1 0x1 goto finishInfatuation
    random 0 1
    compare LASTRESULT 0x1
    random 10 30
    copyvar infatuationX LASTRESULT
    random 20 30
    copyvar infatuationY LASTRESULT
    subvars targety infatuationY
    copyvar LASTRESULT targety
    addvars targety infatuationY
    copyvar infatuationY LASTRESULT
    if1 0x1 goto infatuationLeft

infatuationRight:
    copyvar LASTRESULT targetx
    addvars infatuationX LASTRESULT
    goto infatuationHeartShow

infatuationLeft:
    copyvar LASTRESULT targetx
    subvars LASTRESULT infatuationX
    copyvar infatuationX LASTRESULT

infatuationHeartShow:
    loadsprite infatuationSprite infatuationPalette infatuationOam
    copyvar infatuationParticle LASTRESULT
    runtask TaskMovePoisonBubble infatuationParticle 3 12 50
    addvar counter 1
    goto infatuationLoop


finishInfatuation:
    waittask TaskMovePoisonBubble
    deletesprite initialSprite
    end

.pool


.equ sleepParticle, 0x9006
.global animSleep
animSleep:
    fastsetbattlers
    copyvar 0x8000 targetx
    copyvar 0x8001 targety
    loadspritefull sleepSprite sleepPalette sleepOam
    subvar targety 16
    copyvar initialSprite LASTRESULT
    setvar counter 0x0


sleepLoop:
    compare counter 3
    if1 0x1 goto finishsleep
    loadsprite sleepSprite sleepPalette sleepOam
    copyvar sleepParticle LASTRESULT
    animatesprite sleepParticle sleepAffinePtr
    runtask TaskMoveSleepZ sleepParticle 1 12 30
    pauseframes 20
    addvar counter 1
    goto sleepLoop

finishsleep:
    waittask TaskMoveSleepZ
    deletesprite initialSprite
    end
.pool
