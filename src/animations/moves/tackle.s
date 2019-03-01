.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global TackleAnimation
TackleAnimation:
    // Always load assets and data before starting an animation
    // this will not burn frames on fetching data during the animation
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    fastsetbattlers

blendingPrep:
    spriteblend 8 8
    spritetobg target 8 8
    sideof attacker
    if1 0x1 goto animationOpponent

animationPlayer:
    movesprite attacker 8 0 5 true
    wait
    rendersprite impactParticle targetx targety nullrsf
    startscript FireworkAnimation true
    startscript scrQuakeSprite true
    movesprite attacker 0xFFFC 0 10 true
    wait
    pauseframes 30
    end

animationOpponent:
    movesprite attacker 0xFFF8 0 5
    wait
    rendersprite impactParticle targetx targety nullrsf
    startscript FireworkAnimation true
    startscript scrQuakeSprite true
    movesprite attacker 4 0 10 true
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
