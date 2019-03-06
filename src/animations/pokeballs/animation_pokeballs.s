.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ ballSprite, 0x9006
.equ shakes, 0x9007
.equ shakedir, 0x9008
.equ captureStatus, 0x9009
.equ starSprite1, 0x900A
.equ starSprite2, 0x900B
.equ starSprite3, 0x900C
.equ ballx, 0x900E
.equ bally, 0x900F

.global AnimCapturePokeball
AnimCapturePokeball:
    fastsetbattlers
    loadspritefull pokeballSprite pokeballPalette pokeballOam
    copyvar ballSprite LASTRESULT
    rendersprite ballSprite 32 80 nullrsf

    // throw ball curve
    horizontalArcTranslate 0 160 ballSprite target 34 POKEBALL
    runtask TaskTranslateSpriteHorizontalArc ballSprite 0 0 0
    waittask TaskTranslateSpriteHorizontalArc

    // open ball
    setframessprite 0 ballSprite pokeballFrames
    pauseframes 5
    spritecallback target PokemonCaptureIntoPokeballSCB
    // play scattering particles
    runtask TaskDrawPokeballGlitter ballSprite 0 0 0
    pauseframes 10
    runtask TaskDrawPokeballGlitter ballSprite 0 0 0
    // pokemon to ball

waitloop:
    compare 0x8000 0x0
    if1 0x1 goto waitloop
    waittask TaskDrawPokeballGlitter
    pauseframes 10
    // close ball
    setframessprite 1 ballSprite pokeballFrames
    waitanimation ballSprite
    pauseframes 8
    // ball perform bounces
    spritecallback ballSprite PokeballBounceInitSCB
    setvar 0x8000 0x0

waitloop2:
    compare 0x8000 0x0
    if1 0x1 goto waitloop2
    pauseframes 10
    // shaking should happen now
    copyactionpriv shakes 0
    setvar shakedir 0
    copyvar captureStatus shakes

shakeLoop:
    compare shakes 1
    if1 0x1 goto checkCapture
    compare shakes 0
    if1 0x1 goto checkCapture
    compare shakedir 1
    if1 0x1 goto shakeRight

shakeLeft:
    animatesprite ballSprite pokeballLeftTiltAffineTablePtr 0
    subvar shakes 1
    setvar shakedir 1
    waitaffineanimation ballSprite
    pauseframes 20
    goto shakeLoop

shakeRight:
    animatesprite ballSprite pokeballRightTiltAffineTablePtr 0
    setvar shakedir 0
    subvar shakes 1
    waitaffineanimation ballSprite
    pauseframes 20
    goto shakeLoop

checkCapture:
    compare captureStatus 4
    if1 0x1 goto caught
    // pokemon needs to be released from ball
    setframessprite 0 ballSprite pokeballFrames
    copyvar 0x8000 ballSprite
    spritecallback target PokemonReleaseFromPokeballSCB
    pauseframes 5
    // play scattering particles
    runtask TaskDrawPokeballGlitter ballSprite 0 0 0
    pauseframes 10
    runtask TaskDrawPokeballGlitter ballSprite 0 0 0
    pauseframes 15
    deletesprite ballSprite
    end

caught:
    // stars appear going downward for a few frames
    startscript AnimStarsMove true
    // fade black
    spriteblend2 ballSprite 10 0
    pauseframes 20
    spriteblend2 ballSprite 5 0
    pauseframes 2
    spriteblend2 ballSprite 0 0
    pauseframes 2
    end

.pool


AnimStarsMove:
    spritebufferposition ballSprite ballx bally
    loadspritefull starParticleSprite starParticlePalette StarParticleOam
    copyvar starSprite1 LASTRESULT
    loadsprite starParticleSprite starParticlePalette StarParticleOam
    copyvar starSprite2 LASTRESULT
    loadsprite starParticleSprite starParticlePalette StarParticleOam
    copyvar starSprite3 LASTRESULT
    subvar bally 4
    BLOCKCMD
    spritecallback starSprite1 SCB_SpriteBlink
    spritecallback starSprite2 SCB_SpriteBlink
    spritecallback starSprite3 SCB_SpriteBlink
    rendersprite starSprite1 ballx bally nullrsf
    rendersprite starSprite2 ballx bally nullrsf
    rendersprite starSprite3 ballx bally nullrsf
    movesprite starSprite1 0 1 8 false
    movesprite starSprite2 0xFFFF 1 8 false
    movesprite starSprite3 1 1 8 true
    OPENCMD
    wait
    BLOCKCMD
    deletesprite starSprite1
    deletesprite starSprite2
    deletesprite starSprite3
    OPENCMD
    end
