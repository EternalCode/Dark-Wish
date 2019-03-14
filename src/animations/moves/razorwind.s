.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ tornadopieceParticle, 0x9006
.equ counter, 0x9007
.equ tempTornado, 0x9008
.equ tempx, 0x9009
.equ tempy, 0x900A
.equ impactParticle, 0x900B

.global RazorwindWhipUpAnimation
RazorwindWhipUpAnimation:
    fastsetbattlers
    loadspritefull tornadopieceSprite tornadopiecePalette tornadopieceOam
    copyvar tornadopieceParticle LASTRESULT
    addvar attackery 24
    setvar counter 0
    setvar tempTornado 0
    spritetobg attacker 8 8
    spriteblend 8 8
    hidehpbars
    quakebg 1 2 1 16 2 false

razorwindTornadoLoop:
    compare counter 8
    BLOCKCMD
    if1 0x1 goto razorwindWhipUpFinish
    addvar counter 1
    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceOam
    copyvar tempTornado LASTRESULT
    animatesprite tempTornado tornadopieceAffine 0
    setframessprite 0 tempTornado tornadopieceFrame
    spritecallback tempTornado SCB_SpriteMove64UpAndDeleteWhenAffineEnds
    OPENCMD
    rendersprite tempTornado attackerx attackery tornadopieceAffine
    goto razorwindTornadoLoop

razorwindWhipUpFinish:
    OPENCMD
    pauseframes 40
    clearblending
    showsprite attacker
    hidebg 1
    spritebgclear attacker
    pauseframes 18
    showhpbars
    deletesprite tornadopieceParticle
    end

.global RazorwindAnimation
RazorwindAnimation:
    fastsetbattlers
    loadspritefull tornadopieceSprite tornadopiecePalette tornadopieceAttackOam
    copyvar tornadopieceParticle LASTRESULT
    loadspritefull impact3Sprite impact3Palette impact3Oam
    copyvar impactParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 8 8
    hidehpbars
    addvar targety 24
    setvar counter 0
    setvar tempTornado 0
    quakebg 1 2 1 16 2 false

razorwindAttackTornadoLoop:
    compare counter 8
    BLOCKCMD
    if1 0x1 goto razorwindFinish
    addvar counter 1
    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceAttackOam
    copyvar tempTornado LASTRESULT
    setframessprite 0 tempTornado tornadopieceFrame
    random 0 32
    subvar LASTRESULT 16
    addvars LASTRESULT targetx
    copyvar tempx LASTRESULT
    random 0 32
    subvar LASTRESULT 16
    addvars LASTRESULT targety
    subvar LASTRESULT 24
    copyvar tempy LASTRESULT
    loadsprite impact3Sprite impact3Palette impact3Oam
    spriteblend2 LASTRESULT 10 0x75DE
    rendersprite LASTRESULT tempx tempy nullrsf
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    depthlessorbit tempTornado target 64 10 4 0 6 false true 0
    movesprite tempTornado 0 0xFFFF 64 false
    OPENCMD
    rendersprite tempTornado targetx targety nullrsf
    goto razorwindAttackTornadoLoop

razorwindFinish:
    OPENCMD
    pauseframes 40
    showsprite target
    hidebg 1
    spritebgclear target
    pauseframes 18
    showhpbars
    deletesprite tornadopieceParticle
    deletesprite impactParticle
    end

.pool
