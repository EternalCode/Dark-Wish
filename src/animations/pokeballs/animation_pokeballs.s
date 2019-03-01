.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ ballSprite, 0x9006
.equ ballParticle, 0x9007

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
    // run target transformations
    //spritecallback target PokemonCaptureIntoPokeballSCB
    waitanimation ballSprite
    // play scattering particles
    orbit ballSprite target 800 28 20 1 6 true
    // pokemon to ball

    // close ball
    setframessprite 1 ballSprite pokeballFrames
    waitanimation ballSprite
    wait
    end

.pool

//PokeBallParticles:
//     loadspriteFull pokeballParticleSprite pokeballParticlePalette pokeballParticleOam
//     copyvar ballParticle LASTRESULT
//     loadsprite pokeballParticleSprite pokeballParticlePalette pokeballParticleOam
