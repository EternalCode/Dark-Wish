.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ attacker, 0x8004
.equ target, 0x8005
.equ targetx, 0x8006
.equ targety, 0x8007
.equ attackerx, 0x8008
.equ attackery, 0x8009
.equ LASTRESULT, 0x800D
.equ impactParticle, 0x8003

.global TackleAnimation
TackleAnimation:
    // Always load assets and data before starting an animation
    // this will not burn frames on fetching data during the animation
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle 0x800D
    fastsetbattlers

blendingPrep:
    spriteblend 8 8
    spritetobg target 8 8
    sideof attacker
    if1 0x1 goto animationOpponent

animationPlayer:
    movesprite attacker 8 0 5
    wait
    rendersprite impactParticle targetx targety nullrsf
    startscript FireworkAnimation
    startscript scrQuakeSprite
    movesprite attacker 0xFFFC 0 10 // -4 xoffset
    wait
    pauseframes 30
    end

animationOpponent:
    movesprite attacker 0xFFF8 0 5
    wait
    rendersprite impactParticle targetx targety nullrsf
    startscript FireworkAnimation
    startscript scrQuakeSprite
    movesprite attacker 4 0 10
    wait
    pauseframes 30
    end

.pool


.align 2
.global scrQuakeSprite
scrQuakeSprite:
    quakebg 1 2 0 2 2 true
    wait
    deletesprite impactParticle
    showsprite target
    spritebgclear target
    end
.pool
