.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global BodySlamAnimation
BodySlamAnimation:
    fastsetbattlers
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 8 8
    movesprite attacker 0 2 8 true
    wait
    pauseframes 2
    movesprite attacker 0 0xFFFE 8 true
    sideof attacker
    if2 0 call moveright
    if2 1 call moveleft
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    if2 0 call targetmoverightfast
    if2 1 call targetmoveleftfast
    rendersprite impactParticle targetx targety nullrsf
    wait
    pauseframes 2
    deletesprite impactParticle
    quakebg 1 2 0 2 1 true
    wait
    if2 0 call targetmoveleft
    if2 1 call targetmoveright
    wait
    waitthread 1
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    end

moveright:
    movesprite attacker 2 0 8 true
    wait
    movesprite attacker 0xFFFF 0 16 true
    wait
    return

moveleft:
    movesprite attacker 0xFFFE 0 8 true
    wait
    movesprite attacker 1 0 16 true
    wait
    return

targetmoverightfast:
    movebg 1 4 0 6 RIGHT true
    return

targetmoveleftfast:
    movebg 1 4 0 6 LEFT true
    return

targetmoveright:
    movebg 1 3 0 8 RIGHT true
    return

targetmoveleft:
    movebg 1 3 0 8 LEFT true
    return


.pool
