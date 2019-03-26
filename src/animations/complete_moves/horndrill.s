.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ outterimpact, 0x9006
.equ innerimpact, 0x9007
.equ hornParticle, 0x9008
.equ mainSprite, 0x9009
.equ posx, 0x900A
.equ posy, 0x900B

.global HornDrillAnimation
HornDrillAnimation:
    fastsetbattlers
    loadspritefull glowballSprite glowballPalette glowballOam
    copyvar mainSprite LASTRESULT
    loadspritefull impact6Sprite impact6Palette impact6Oam
    copyvar outterimpact LASTRESULT
    loadspritefull impact7Sprite impact7Palette impact7Oam
    copyvar innerimpact LASTRESULT
    loadspritefull hornSprite hornPalette hornOam
    copyvar hornParticle LASTRESULT
    spriteblend2 hornParticle 10 0x0C43
    spriteblend2 outterimpact 6 0x051C
    spriteblend2 innerimpact 6 0x127C
    spritetobg target 8 8
    blendsemitransparent 12 4

    subvar targetx 32
    addvar targety 16
    rendersprite hornParticle targetx targety nullrsf
    depthlessorbit hornParticle target 80 5 5 0 16 false true 0
    pauseframes 18
    BLOCKCMD
    fastsetbattlers
    rendersprite innerimpact targetx targety impact7Affine
    subvar targetx 5
    subvar targety 5
    rendersprite outterimpact targetx targety impact6Affine
    animatesprite innerimpact impact7Affine 0
    animatesprite outterimpact impact6Affine 0
    spritecallback innerimpact SCB_SpriteDeleteWhenAffineEnds
    spritecallback outterimpact SCB_SpriteDeleteWhenAffineEnds
    quakebg 1 3 2 10 2 false
    OPENCMD
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    fastsetbattlers
    call LeftFirework
    waittask TaskCreateSmallFireworkGeneric
    deletesprite mainSprite
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    end

LeftFirework:
    BLOCKCMD
    pickrandompos targetx targety 16 32
    applyfirework glowballSprite glowballPalette glowballOam glowball2Affine 3 targetx targety
    spriteblend2 LASTRESULT 14 0x00FA
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    applyfirework glowballSprite glowballPalette glowballOam glowball2Affine 1 targetx targety
    spriteblend2 LASTRESULT 14 0x00FA
    OPENCMD
    return

.pool
