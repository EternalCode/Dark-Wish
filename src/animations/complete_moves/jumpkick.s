.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ footParticle, 0x9006
.equ impactParticle, 0x9007

.global JumpKickAnimation
JumpKickAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull stompSprite stompPalette stompOam
    copyvar footParticle LASTRESULT
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    spritepriority attacker 0
    OPENCMD
    spritetobg target 8 8
    spriteblend 8 8
    BLOCKCMD
    sideof attacker
    compare LASTRESULT PLAYERSIDE
    if2 0x1 call translateforplayer
    if2 0x0 call translateforOpponent
    waittask TaskTranslateSpriteHorizontalArc
    waittask TaskTranslateSpriteHorizontalArcCos
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    quakebg 1 2 0 2 2 false
    rendersprite impactParticle targetx targety nullrsf
    deletesprite footParticle
    pauseframes 5
    deletesprite impactParticle
    spritepriority attacker 3
    waitthread 1
    end

translateforOpponent:
    addvar attackery 16
    subvar attackerx 8
    rendersprite footParticle attackerx attackery nullrsf
    OPENCMD
    movesprite footParticle 2 0xFFFC 4 false
    movesprite attacker 0xFFFE 0 4 true
    horizontalArcTranslate 0 130 footParticle target 20 PLAYERSIDE
    runtask TaskTranslateSpriteHorizontalArc footParticle 0 0 0
    wait
    movesprite attacker 2 0 4 false
    return

translateforplayer:
    addvar attackery 16
    addvar attackerx 8
    rendersprite footParticle attackerx attackery nullrsf
    OPENCMD
    movesprite footParticle 0xFFFE 0xFFFC 4 false
    movesprite attacker 2 0 4 true
    horizontalArcTranslate 0 130 footParticle target 20 OPPONENTSIDE
    runtask TaskTranslateSpriteHorizontalArcCos footParticle 0 0 0
    wait
    movesprite attacker 0xFFFE 0 4 false
    return

.pool
