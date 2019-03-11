.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ punchParticle, 0x9007
.equ tempx, 0x9008
.equ tempy, 0x9009
.equ counter, 0x900A
.equ impactOrg, 0x900B
.equ punchOrg, 0x900C


.global CometpunchAnimation
CometpunchAnimation:
    // Always load assets and data before starting an animation
    // this will not burn frames on fetching data during the animation
    BLOCKCMD
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactOrg LASTRESULT
    loadspritefull fistSprite fistPalette fist2Oam
    copyvar punchOrg LASTRESULT
    fastsetbattlers
    spriteblend 8 8
    spritetobg target 8 8
    OPENCMD
    setvar counter 0

Punchloop:
    // pick a position for the punch & impact
    compare counter 7
    if1 0x1 goto finishAnimation
    BLOCKCMD
    copyvar tempx targetx
    copyvar tempy targety
    subvar tempx 32
    subvar tempy 32
    random 0 64
    addvars tempx LASTRESULT
    random 0 48
    addvars tempy LASTRESULT
    loadsprite fistSprite fistPalette fist2Oam
    copyvar punchParticle LASTRESULT
    loadsprite bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spriteblend2 impactParticle 10 0x03DE
    rendersprite impactParticle tempx tempy nullrsf
    rendersprite punchParticle tempx tempy nullrsf
    animatesprite punchParticle fistAffinePtr2 0
    spritecallback punchParticle SCB_SpriteDeleteWhenAffineEnds
    spritecallback impactParticle SCB_SpriteDeleteAfter10Frames
    OPENCMD
    quakebg 1 2 0 2 1 false
    addvar counter 1
    goto Punchloop

finishAnimation:
    showsprite target
    hidebg 1
    clearblending
    spritebgclear target
    deletesprite impactOrg
    deletesprite punchOrg
    end

.pool
