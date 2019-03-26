.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ featherParticle, 0x9007
.equ impact2Particle, 0x9008
.equ impact3Particle, 0x9009
.equ featherX, 0x900A
.equ featherY, 0x900B
.equ tempY, 0x900C
.equ counter, 0x900E
.equ tempX, 0x900F
.equ coa, 0x9010
.equ cob, 0x9011
.equ speed, 0x9012

.global WingAttackAnimation
WingAttackAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull impact4Sprite impact4Palette impact4Oam
    copyvar impactParticle LASTRESULT
    loadspritefull impact4_2Sprite impact4_2Palette impact4Oam
    copyvar impact2Particle LASTRESULT

    loadspritefull impact4_3Sprite impact4_3Palette impact4Oam
    copyvar impact3Particle LASTRESULT
    OPENCMD
    spritetobg target 8 8
    spriteblend 4 12
    startscript FeathersFall true
    BLOCKCMD
    hidehpbars
    addvar targety 16
    spriteblend2 impactParticle 10 0xFFFF
    rendersprite impactParticle targetx targety nullrsf
    spritecallback impactParticle SCB_SpriteDeleteAfter10Frames
    OPENCMD
    BLOCKCMD
    subvar targety 12
    spriteblend2 impact2Particle 10 0x3F9F
    rendersprite impact2Particle targetx targety nullrsf
    spritecallback impact2Particle SCB_SpriteDeleteAfter10Frames
    quakebg 1 2 0 3 2 false
    OPENCMD
    BLOCKCMD
    subvar targety 12
    spriteblend2 impact3Particle 10 0x1F5F
    rendersprite impact3Particle targetx targety nullrsf
    spritecallback impact3Particle SCB_SpriteDeleteAfter10Frames
    OPENCMD
    pauseframes 10
    showsprite target
    BLOCKCMD
    hidebg 1
    clearblending
    spritebgclear target
    OPENCMD
    end

.global FeathersFall
FeathersFall:
    loadspritefull featherSprite featherPalette featherOam
    BLOCKCMD
    copyvar featherParticle LASTRESULT
    fastsetbattlers
    subvar targety 16
    copyvar tempY targety
    copyvar tempX targetx
    OPENCMD
    BLOCKCMD
    call createFeather
    call createFeather
    OPENCMD
    BLOCKCMD
    call createFeather
    call createFeather
    OPENCMD
    BLOCKCMD
    call createFeather
    call createFeather
    OPENCMD
    BLOCKCMD
    call createFeather
    call createFeather
    OPENCMD
    goto finishFeathers

createFeather:
    loadsprite featherSprite featherPalette featherOam
    copyvar tempY targety
    copyvar tempX targetx
    pickrandompos tempX tempY 64 56
    setframessprite 0 LASTRESULT featherFrame
    spriteblend2 LASTRESULT 8 0x337B
    rendersprite LASTRESULT tempX tempY nullrsf
    spritefeatherfall LASTRESULT 2 8 20 1 2 true
    semitransparent LASTRESULT
    return

finishFeathers:
    // slow fade to bg
    waitthread 0
    BLOCKCMD
    spritetobg target 8 8
    setvar coa 16
    setvar cob 0
    setvar speed 1
    startscript FadeToBGAnimation true
    OPENCMD
    waitthread 0
    showsprite target
    BLOCKCMD
    hidebg 1
    clearblending
    spritebgclear target
    OPENCMD
    showhpbars
    end

.pool
