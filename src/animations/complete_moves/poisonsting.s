.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ angleBuffer, 0x9006
.equ poisonstingParticle, 0x9007
.equ poisonParticle, 0x9008
.equ tempSprite, 0x9009

.global PoisonStingAnimation
PoisonStingAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull poisonSprite poisonPalette poisonOam
    copyvar poisonParticle LASTRESULT
    loadspritefull poisonstingSprite poisonstingPalette poisonstingOam
    copyvar poisonstingParticle LASTRESULT
    spritepriority poisonstingParticle 3
    spritepriority attacker 2
    OPENCMD
    spritetobg target 8 8
    BLOCKCMD
    spritesetposition poisonstingParticle attackerx attackery
    getangle attackerx attackery targetx targety angleBuffer
    applycustomaffine poisonstingParticle 256 256 angleBuffer
    showsprite poisonstingParticle
    OPENCMD
    spritemovedst 16 poisonstingParticle target
    pauseframes 7
    spriteblend2 poisonstingParticle 10 0x6A1A
    spritepriority attacker 3
    spritepriority poisonstingParticle 1
    pauseframes 6
    addpalbuffer target false
    fadespritebg 2 0x6C50 FADETO false 10
    BLOCKCMD
    blendsemitransparent 12 4
    quakebg 1 2 0 2 2 false
    OPENCMD
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    pauseframes 8
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    pauseframes 8
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    fadespritebg 2 0x6C50 FADEFROM false 10
    pauseframes 8
    call createPoisonBubble
    spritecallback tempSprite SCB_SpriteDeleteAfter20Frames
    pauseframes 20
    clearblending
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite poisonParticle
    end


createPoisonBubble:
    BLOCKCMD
    fastsetbattlers
    addvar targety 8
    loadsprite poisonSprite poisonPalette poisonOam
    copyvar tempSprite LASTRESULT
    semitransparent tempSprite
    pickrandompos targetx targety 24 24
    rendersprite tempSprite targetx targety nullrsf
    movesprite tempSprite 0 0xFFFF 20 false
    OPENCMD
    return

.pool
