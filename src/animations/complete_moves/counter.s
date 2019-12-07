.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ fistParticle, 0x9007
.equ ox, 0x9008
.equ oy, 0x9009

.global CounterAnimation
CounterAnimation:
    fastsetbattlers
    loadspritefull squarefistSprite squarefistPalette yellowfistOam
    copyvar fistParticle LASTRESULT
    spriteblend2 fistParticle 12 0x107D
    spritetobg target 8 8
    blendsemitransparent 8 8
    copyvar ox attackerx
    copyvar oy attackery
    addvar attackery 8
    subvar attackerx 8
    spritesetposition attacker attackerx attackery
    hidehpbars
    depthlessorbit attacker attacker 16 24 8 LEFT 16 true false 0
    sideof attacker
    if2 0x0 goto playerMove
    if2 0x1 goto oppMove
    animatesprite fistParticle bigfistShrinkSlowly2Affine 0
    spritecallback fistParticle SCB_SpriteDeleteWhenAffineEnds
    rendersprite fistParticle targetx targety bigfistShrinkSlowly2Affine
    quakesprite fistParticle 4 2 4 2 false
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimationNoClearBg true
    startscript scrQuakeCounter true
    waitthread 1
    waitthread 2
    clearblending
    sideof attacker
    if2 0x0 goto playerRestore
    if2 0x1 goto oppRestore
    showsprite target
    hidebg 1
    spritebgclear target
    showhpbars
    spritesetposition attacker ox oy
    end

playerMove:
    movesprite attacker 4 0 4 true
    wait
    return

oppMove:
    movesprite attacker 0xFFFC 0 4 true
    wait
    return

playerRestore:
    movesprite attacker 0xFFFC 0 4 true
    wait
    return

oppRestore:
    movesprite attacker 4 0 4 true
    wait
    return

scrQuakeCounter:
    quakebg 1 2 0 2 2 true
    wait
    end

.pool
