.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ furyParticle, 0x9007

.global FuryAttackAnimation
FuryAttackAnimation:
    fastsetbattlers
    BLOCKCMD
    spritetobg target 8 8
    spriteblend 8 8
    loadspritefull bimpact1Sprite bimpact1Palette bimpact1Oam
    copyvar impactParticle LASTRESULT
    spriteblend2 impactParticle 10 0x025E
    OPENCMD
    sideof attacker
    compare LASTRESULT PLAYERSIDE
    BLOCKCMD
    if2 0x0 call playerisattacker
    if2 0x1 call opponentisattacker
    rendersprite furyParticle targetx targety nullrsf
    OPENCMD
    pauseframes 3
    setvar gLASTRESULT 0x025E
    startscript FireworkAnimationSmaller true
    BLOCKCMD
    fastsetbattlers
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 true
    OPENCMD
    wait
    deletesprite furyParticle
    deletesprite impactParticle
    waitthread 1
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    end

playerisattacker:
    loadspritefull furyattackSprite furyattackPalette furyattackOam
    copyvar furyParticle LASTRESULT
    subvar targetx 32
    addvar targety 32
    movesprite furyParticle 4 0xFFFC 8 false
    return

opponentisattacker:
    loadspritefull furyattackSprite furyattackPalette furyattackFlippedOam
    copyvar furyParticle LASTRESULT
    addvar targetx 32
    subvar targety 32
    movesprite furyParticle 0xFFFC 4 8 false
    return

    end

.pool
