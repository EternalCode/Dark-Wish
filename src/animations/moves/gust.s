.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ dustParticle, 0x9006
.equ counter, 0x9007
.equ waveOffset, 0x9008
.equ waveOffsetDelta, 0x9009
.equ tempParticle, 0x900A
.equ rockParticle, 0x900B

.global GustAnimation
GustAnimation:
    fastsetbattlers
    loadspritefull smokeballSprite smokeballPalette smokeballOam
    copyvar dustParticle LASTRESULT
    loadspritefull smallrockcircleSprite smallrockcirclePalette smallrockcircleOam
    copyvar rockParticle LASTRESULT
    spritepriority target 1
    spritetobg target 8 8
    blendsemitransparent 10 6
    hidehpbars
    BLOCKCMD
    addvar targety 16
    setvar counter 0
    setvar waveOffsetDelta 255
    divvar waveOffsetDelta 8


GustAnimationLoop:
    compare counter 8
    if1 0x1 goto waitingGust
    loadsprite smokeballSprite smokeballPalette smokeballOam
    copyvar waveOffset waveOffsetDelta
    mulvar waveOffset counter
    orbit LASTRESULT target 70 40 6 0 4 false true waveOffset
    animatesprite LASTRESULT smokeballAffine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety smokeballAffine
    spriteblend2 LASTRESULT 12 0x4B17
    copyvar tempParticle LASTRESULT
    random 0 100
    compare LASTRESULT 40
    if2 0 call makeTransparent
    addvar counter 1
    goto GustAnimationLoop

waitingGust:
    OPENCMD
    BLOCKCMD
    setvar counter 0
    quakebg 1 3 1 11 2 true
    OPENCMD

flyingRocks:
    compare counter 7
    if1 0x1 goto finishGust
    BLOCKCMD
    loadsprite smallrockcircleSprite smallrockcirclePalette smallrockcircleOam
    copyvar tempParticle LASTRESULT
    movesprite tempParticle 0 0xFFFF 38 false
    random 0 255
    orbit tempParticle target 40 24 8 1 10 false true LASTRESULT
    animatesprite tempParticle smallrockcircleAffine 0
    rendersprite tempParticle targetx targety smallrockcircleAffine
    addvar counter 1
    OPENCMD
    goto flyingRocks

finishGust:
    wait
    spritepriority target 3
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite dustParticle
    deletesprite rockParticle
    showhpbars
    end

makeTransparent:
    semitransparent tempParticle
    return


.pool
