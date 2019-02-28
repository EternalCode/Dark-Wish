.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ attacker, 0x8004
.equ target, 0x8005
.equ targetx, 0x8006
.equ targety, 0x8007
.equ attackerx, 0x8008
.equ attackery, 0x8009
.equ LASTRESULT, 0x800D
.equ ballSprite, 0x8003
.equ ballParticle, 0x800A

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
    spritecallback target PokemonCaptureIntoPokeballSCB
    waitanimation ballSprite
    // play orbiting particles
    
    // pokemon to ball

    // close ball
    setframessprite 1 ballSprite pokeballFrames
    waitanimation ballSprite
    wait
    end

.pool

//;
//;
//; PokeBallParticles:
//;     loadspriteFull pokeballParticleSprite pokeballParticlePalette pokeballParticleOAM
//;     copyvar ballParticle LASTRESULT
