.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ flamesParticle, 0x9006
.equ angleBuffer, 0x9007
.equ tempSprite, 0x9008
.equ counter, 0x9009

.global FlamethrowerAnimation
FlamethrowerAnimation:
    fastsetbattlers
    spritetobg target 8 8
    spriteblend 2 14
    addfadeplatformbg
    loadspritefull flamethrowerSprite flamethrowerPalette flamethrowerOam
    copyvar flamesParticle LASTRESULT
    hidehpbars
    beginfade 2 0x0056 FADETO true 10
    startscript BlendSpriteBgRed true

flamesLoop:
    BLOCKCMD
    compare counter 20
    if1 0x1 goto finishMove
    loadsprite flamethrowerSprite flamethrowerPalette flamethrowerOam
    copyvar tempSprite LASTRESULT
    animatesprite tempSprite flamethrowerAffine 0
    setframessprite 0 tempSprite flamethrowerFrames
    OPENCMD
    BLOCKCMD
    rendersprite tempSprite attackerx attackery flamethrowerAffine
    spritemovedst 40 tempSprite target
    addvar counter 1
    quakesprite attacker 0 1 1 1 false
    OPENCMD
    goto flamesLoop

finishMove:
    pauseframes 20
    clearpalbuffer
    addfadebg1
    addvar targety 8
    beginfade 1 0xFFFF FADETO false 3
    quakebg 1 2 0 7 2 false
    OPENCMD
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    call flamesEmerge
    pauseframes 28
    waitthread 1
    waitthread 2
    beginfade 1 0xFFFF FADEFROM true 3
    clearpalbuffer
    addfadeplatformbg
    beginfade 2 0x0056 FADEFROM true 10
    clearblending
    showhpbars
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite flamesParticle
    end

flamesEmerge:
    BLOCKCMD
    loadsprite flamethrowerSprite flamethrowerPalette flamethrowerOam
    copyvar tempSprite LASTRESULT
    pickrandompos targetx targety 8 16
    animatesprite tempSprite flamethrowerAffine 0
    movesprite tempSprite 0 0xFFFF 30 false
    setframessprite 0 tempSprite flamethrowerFrames
    spritecallback tempSprite SCB_SpriteDeleteWhenAnimEnds
    OPENCMD
    rendersprite tempSprite targetx targety flamethrowerAffine
    return

BlendSpriteBgRed:
    pauseframes 26
    clearpalbuffer
    addfadebg1
    beginfade 1 0x0056 FADETO true 4
    end

.pool
