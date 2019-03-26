.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ footParticle, 0x9006
.equ impactParticle, 0x9007

.global RollingKickAnimation
RollingKickAnimation:
    fastsetbattlers
    loadspritefull stompSprite stompPalette stompOam
    copyvar footParticle LASTRESULT
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    BLOCKCMD
    addvar attackery 10
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 17 10 10 1 16 true false 0
    depthlessorbit footParticle target 33 20 20 1 8 false true 64
    rendersprite footParticle targetx targety nullrsf
    OPENCMD
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    spritetobg target 8 8
    spriteblend 8 8
    rendersprite impactParticle targetx targety nullrsf
    pauseframes 10
    deletesprite impactParticle
    waitthread 1
    showsprite target
    spritebgclear target
    clearblending
    spritesetposition attacker attackerx attackery
    end

.pool
