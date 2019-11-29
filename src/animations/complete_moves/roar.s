.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ growlParticle, 0x9006
.equ counter, 0x9007

.global RoarAnimation
RoarAnimation:
    fastsetbattlers
    spritetobg attacker 8 8
    spriteblend 8 8
    loadspritefull growlSprite growlPalette growlOam
    copyvar growlParticle LASTRESULT
    quakebg 1 2 0 10 2 false
    quakesprite target 2 0 8 2 false
    call RoarParticles
    pauseframes 8
    call RoarParticles
    pauseframes 8
    call RoarParticles
    pauseframes 8
    deletesprite growlParticle
    sideof target
    if1 0 goto moveplayer
    movesprite target 4 0 25 true
    wait
    pauseframes 10
    end

moveplayer:
    movesprite target 0xFFFC 0 25 true
    wait
    pauseframes 10
    end

RoarParticles:
    BLOCKCMD
    setvar counter 0
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    addvar counter 27
    call roarDirection
    OPENCMD
    return

roarDirection:
    loadsprite growlSprite growlPalette growlOam
    spritesetposition LASTRESULT attackerx attackery
    spritecallbackargs LASTRESULT 0 counter 40 4 SpriteTravelDir
    return

opponentSideRoar:
    return


.pool
