.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ vinewhipParticle, 0x9006
.equ impactParticle, 0x9007

.global VineWhipAnimation
VineWhipAnimation:
    fastsetbattlers
    loadspritefull vinewhipSprite vinewhipPalette vinewhipOam
    copyvar vinewhipParticle LASTRESULT
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 4 12
    subvar targetx 36
    subvar targety 36
    rendersprite vinewhipParticle targetx targety nullrsf
    setframessprite 0 vinewhipParticle vinewhipFrames
    animatesprite vinewhipParticle vinewhipAffine 0
    movesprite vinewhipParticle 3 3 12 false
    fastsetbattlers
    spriteblend2 impactParticle 10 0x12CB
    pauseframes 4
    BLOCKCMD
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 false
    setvar gLASTRESULT 0x12CB
    startscript FireworkAnimation true
    OPENCMD
    pauseframes 12
    deletesprite vinewhipParticle
    deletesprite impactParticle
    waitthread 1

createLeafBlades:
    showsprite target
    hidebg 1
    spritebgclear 1
    clearblending
    end

.pool
