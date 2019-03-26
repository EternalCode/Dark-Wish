.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ chopParticle, 0x9007

.global KaratechopAnimation
KaratechopAnimation:
    // Always load assets and data before starting an animation
    // this will not burn frames on fetching data during the animation
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    loadspritefull chopSprite chopPalette chopOam
    copyvar chopParticle LASTRESULT
    fastsetbattlers

blendingPrep:
    spriteblend 8 8
    spritetobg target 8 8
    subvar targety 40
    setframessprite 0 chopParticle chopLeftFrames
    rendersprite chopParticle targetx targety nullrsf
    movesprite chopParticle 0 6 9 true
    wait
    BLOCKCMD
    addvar targety 40
    spriteblend2 impactParticle 10 0x019D
    rendersprite impactParticle targetx targety nullrsf
    setvar gLASTRESULT 0x019D
    startscript FireworkAnimationSmaller true
    quakebg 1 2 0 2 2 false
    movesprite chopParticle 0 0xFFFE 5 true
    OPENCMD
    wait
    deletesprite chopParticle
    deletesprite impactParticle
    pauseframes 30
    end

.pool
