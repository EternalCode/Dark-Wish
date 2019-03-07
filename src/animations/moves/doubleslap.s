.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ slapParticle, 0x9007

.global DoubleSlapAnimation
DoubleSlapAnimation:
    // Always load assets and data before starting an animation
    // this will not burn frames on fetching data during the animation
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    loadspritefull slapSprite slapPalette slapOam
    copyvar slapParticle LASTRESULT
    fastsetbattlers

blendingPrep:
    spriteblend 8 8
    spritetobg target 8 8

slapLeft:
    subvar targetx 40
    setframessprite 0 slapParticle slapFramesPtr
    rendersprite slapParticle targetx targety nullrsf
    movesprite slapParticle 4 0 10 true
    wait
    BLOCKCMD
    addvar targetx 40
    spriteblend2 impactParticle 10 0x57FF
    rendersprite impactParticle targetx targety nullrsf
    setvar gLASTRESULT 0x57FF
    startscript scrQuakeSprite true
    movesprite slapParticle 4 0 10 true
    OPENCMD
    wait

slapRight:
    movesprite slapParticle 0xFFFC 0 10 true
    wait
    BLOCKCMD
    spritetobg target 8 8
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spriteblend2 impactParticle 10 0x57FF
    rendersprite impactParticle targetx targety nullrsf
    setvar gLASTRESULT 0x57FF
    startscript scrQuakeSprite true
    movesprite slapParticle 0xFFFC 0 10 true
    OPENCMD
    wait
    deletesprite slapParticle
    showsprite target
    hidebg 1
    clearblending
    spritebgclear target
    end

.pool
