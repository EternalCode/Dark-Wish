.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ wrapLeft, 0x9006
.equ wrapRight, 0x9007

.global WrapAnimation
WrapAnimation:
    BLOCKCMD
    fastsetbattlers
    loadspritefull wrapSprite wrapPalette wrapOam
    copyvar wrapLeft LASTRESULT
    loadspritefull wrapSprite wrapPalette wrapFlippedOam
    copyvar wrapRight LASTRESULT
    OPENCMD
    startscript targetOrbit true
    animatesprite target wrapAffine 0
    quakesprite target 1 0 2 1 false
    rendersprite wrapLeft targetx targety nullrsf
    setframessprite 0 wrapLeft wrapFrames
    pauseframes 8
    subvar targety 8
    setframessprite 0 wrapRight wrapFlippedFrames
    rendersprite wrapRight targetx targety nullrsf
    pauseframes 16
    waitaffineanimation attacker
    deletesprite wrapLeft
    deletesprite wrapRight
    end

targetOrbit:
    BLOCKCMD
    addvar attackery 10
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 17 10 10 1 16 true false 0
    OPENCMD
    subvar attackery 10
    spritesetposition attacker attackerx attackery
    end

.global WrapResidualAnimation
WrapResidualAnimation:
    BLOCKCMD
    fastsetbattlers
    loadspritefull wrapSprite wrapPalette wrapOam
    copyvar wrapLeft LASTRESULT
    loadspritefull wrapSprite wrapPalette wrapFlippedOam
    copyvar wrapRight LASTRESULT
    animatesprite target wrapAffine 0
    quakesprite target 1 0 2 1 false
    OPENCMD
    rendersprite wrapLeft targetx targety nullrsf
    setframessprite 0 wrapLeft wrapFrames
    pauseframes 8
    subvar targety 8
    setframessprite 0 wrapRight wrapFlippedFrames
    rendersprite wrapRight targetx targety nullrsf
    pauseframes 16
    waitaffineanimation attacker
    BLOCKCMD
    deletesprite wrapLeft
    deletesprite wrapRight
    OPENCMD
    end


.pool
