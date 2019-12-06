.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ stompParticle, 0x9006
.equ impactParticle, 0x9007
.equ xOff, 0x9008
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013


.global LowKickAnimation
LowKickAnimation:
    fastsetbattlers
    loadspritefull stompSprite stompPalette stompOam
    copyvar stompParticle LASTRESULT
    semitransparent stompParticle
    spritepriority stompParticle 1
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    semitransparent impactParticle
    spritetobg target 8 8
    sideof attacker
    if2 0 call kickPlayer
    if2 1 call kickOpp
    setvar coA 12
    setvar coB 4
    setvar amount 16
    setvar speed 4
    rendersprite stompParticle targetx targety nullrsf
    movesprite stompParticle xOff 0 15 false
    pauseframes 12
    startscript FadeToBGAnimation true
    startscript scrQuakeSprite true
    movesprite stompParticle xOff 0 5 true
    wait
    deletesprite stompParticle
    waitthread 1
    BLOCKCMD
    fastsetbattlers
    spriteblend 8 8
    setvar gLASTRESULT 0x57FF
    OPENCMD
    startscript FireworkAnimation true
    rendersprite impactParticle targetx targety nullrsf
    spritecallback impactParticle SCB_SpriteDeleteAfter10Frames
    pauseframes 20
    waitthread 1
    waitthread 2
    waitthread 3
    end


kickOpp:
    addvar targetx 60
    addvar targety 8
    setvar xOff 0xFFFA
    return

kickPlayer:
    subvar targetx 60
    addvar targety 8
    setvar xOff 6
    return

    end

.pool
