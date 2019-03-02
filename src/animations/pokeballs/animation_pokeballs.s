.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ ballSprite, 0x9006
.equ shakes, 0x9007
.equ shakedir, 0x9008
.equ captureStatus, 0x9009

.global AnimCapturePokeball
AnimCapturePokeball:
    fastsetbattlers
    loadspritefull pokeballSprite pokeballPalette pokeballOam
    copyvar ballSprite LASTRESULT
    rendersprite ballSprite 32 80 nullrsf

    // throw ball curve
    horizontalArcTranslate 0 160 ballSprite target 34
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
    copyactionpriv shakes
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
    if1 0x1 goto finish
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

finish:
    end

.pool
