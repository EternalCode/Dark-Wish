.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ tornado1, 0x9006
.equ tornado2, 0x9007
.equ tornado3, 0x9008
.equ tornado4, 0x9009
.equ tornado5, 0x900A
.equ tornado6, 0x900B
.equ coa, 0x9010
.equ cob, 0x9011
.equ speed, 0x9012
.equ displacementDistRight, 40

.global WhirlwindAnimation
WhirlwindAnimation:
    fastsetbattlers
    //hidesprite target
    subvar targety 24
    spritetobg target 8 8
    blendsemitransparent 12 4
    BLOCKCMD
    loadspritefull tornadopieceSprite tornadopiecePalette tornadopieceTransparentAttackOam
    copyvar tornado1 LASTRESULT

    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceTransparentOam
    copyvar tornado2 LASTRESULT

    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceTransparentOam
    copyvar tornado3 LASTRESULT

    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceTransparentOam
    copyvar tornado4 LASTRESULT

    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceTransparentOam
    copyvar tornado5 LASTRESULT

    loadsprite tornadopieceSprite tornadopiecePalette tornadopieceTransparentAttackOam
    copyvar tornado6 LASTRESULT

    setframessprite 0 tornado1 tornadopieceSlowestFrame
    setframessprite 0 tornado2 tornadopieceSlowerFrame
    setframessprite 0 tornado3 tornadopieceFrame
    setframessprite 0 tornado4 tornadopieceFrame
    setframessprite 0 tornado5 tornadopieceSlowerFrame
    setframessprite 0 tornado6 tornadopieceSlowestFrame

    animatesprite tornado2 tornadoSmallAffine 0
    animatesprite tornado3 tornadoInnerAffine 0
    animatesprite tornado4 tornadoInnerAffine 0
    animatesprite tornado5 tornadoSmallAffine 0


    addvar targety 8
    rendersprite tornado1 targetx targety tornadopieceAffine
    addvar targety 6
    rendersprite tornado2 targetx targety tornadoSmallAffine
    addvar targety 4
    rendersprite tornado3 targetx targety tornadoInnerAffine
    addvar targety 4
    rendersprite tornado4 targetx targety tornadoInnerAffine
    addvar targety 6
    rendersprite tornado5 targetx targety tornadoSmallAffine
    addvar targety 8
    rendersprite tornado6 targetx targety tornadopieceAffine
    OPENCMD
    quakebg 1 3 0 3 2 true
    setvar coa 16
    setvar cob 0
    setvar speed 2
    startscript FadeToBGAnimation true
    wait
    BLOCKCMD
    deletesprite tornado1
    deletesprite tornado2
    deletesprite tornado3
    deletesprite tornado4
    deletesprite tornado5
    deletesprite tornado6
    OPENCMD
    showsprite target
    BLOCKCMD
    spritebgclear target
    sideof target
    compare LASTRESULT 0
    if1 0x1 goto moveplayer
    movesprite target 4 0 25 true
    OPENCMD
    wait
    end

moveplayer:
    movesprite target 0xFFFC 0 25 true
    OPENCMD
    wait
    end

.pool
