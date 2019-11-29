.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ boomParticle, 0x9007
.equ counter, 0x9008
.equ tempSprite, 0x9009

.global SonicBoomAnimation
SonicBoomAnimation:
    fastsetbattlers
    spritetobg target 8 8
    spriteblend 4 12
    loadspritefull sonicboomSprite sonicboomPalette sonicboomOam
    copyvar boomParticle LASTRESULT
    startscript BoomImpact true

boomLoop:
    BLOCKCMD
    compare counter 6
    if1 0x1 goto finishAnim
    loadsprite sonicboomSprite sonicboomPalette sonicboomOam
    copyvar tempSprite LASTRESULT
    sideof attacker
    if2 0x1 call opponentBoom
    animatesprite tempSprite sonicboomAffine 0
    OPENCMD
    BLOCKCMD
    rendersprite tempSprite attackerx attackery sonicboomAffine
    spritemovedst 20 tempSprite target
    addvar counter 1
    OPENCMD
    goto boomLoop

finishAnim:
    OPENCMD
    pauseframes 20
    waitthread 1
    clearblending
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite boomParticle
    end

opponentBoom:
    setframessprite 0 tempSprite sonicboomOpponent
    return


BoomImpact:
    pauseframes 18
    BLOCKCMD
    loadspritefull impact1Sprite impact1Palette impact1Oam
	copyvar impactParticle LASTRESULT
    spriteblend2 impactParticle 10 0xFFFF
    OPENCMD
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 4 2 true
    wait
    deletesprite impactParticle
    end

.pool
