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
.equ burnParticle, 0x8003

.global animBurnEffect
animBurnEffect:
    fastsetbattlers
    setvar 0x8002 0x0

redset:
    addpalbuffer target 0
    beginfade 3 0x1CF8 FADETO 0 10
    loadspritefull burnSprite burnPalette burnOam
    copyvar 0x800A LASTRESULT

burnLoop:
    compare 0x8002 5
    if1 0x1 goto finishburn
    loadsprite burnSprite burnPalette burnOam
    copyvar burnParticle LASTRESULT
    animatesprite burnParticle burnAffinePtr
    runtask TaskBurnEffect burnParticle 0 0 0
    pauseframes 10
    addvar 0x8002 1
    goto burnLoop

finishburn:
    beginfade 3 0x1CF8 FADEFROM 1 10
    pauseframes 10
    deletesprite 0x800A
    end
.pool


.thumb
.align 2
.equ poisonParticle, 0x8003

.global animPoisonEffect
animPoisonEffect:
    fastsetbattlers
    setvar 0x8002 0x0

purpleset:
    addpalbuffer target 0
    beginfade 3 0x6C50 FADETO 0 10
    loadspritefull poisonSprite poisonPalette poisonOam
    copyvar 0x800A LASTRESULT

poisonLoop:
    compare 0x8002 4
    if1 0x1 goto finishpoison
    loadsprite poisonSprite poisonPalette poisonOam
    copyvar poisonParticle LASTRESULT
    runtask TaskMoveSinLeftAndRight poisonParticle 2 12 0
    pauseframes 10
    addvar 0x8002 1
    goto poisonLoop

finishpoison:
    beginfade 3 0x6C50 FADEFROM 1 10
    pauseframes 10
    deletesprite 0x800A
    end
.pool


.global animBadlyPoisoned
animBadlyPoisoned:
    startscript animPoisonEffect
    pauseframes 15
    quakesprite target 6 0 2 5 true
    end
.pool

.equ paralyzeParticle, 0x8003
.global animParalyzed
animParalyzed:
    fastsetbattlers
    addpalbuffer target 0
    loadspritefull paralyzeSprite paralyzePalette paralyzeOam
    copyvar paralyzeParticle LASTRESULT
    rendersprite paralyzeParticle targetx targety nullrsf
    setframessprite 0 paralyzeParticle paralyzeLoopPtr
    quakesprite target 4 0 2 5 0
    beginfade 3 0 FADETO 1 10
    pauseframes 50
    beginfade 3 0 FADEFROM 1 10
    deletesprite paralyzeParticle
    end
.pool

.equ freezeParticle, 0x8003
.global animFreeze
animFreeze:
    fastsetbattlers
    loadspritefull freezeSprite freezePalette freezeOam
    copyvar 0x800A LASTRESULT
    spritetobg target 8 8
    fadespritebg 3 0x6546 FADETO 0 10
    spriteblend 8 8
    setvar 0x8002 0x0

freezeLoop:
    compare 0x8002 8
    if1 0x1 goto finishfreeze
    loadsprite freezeSprite freezePalette freezeOam
    copyvar freezeParticle LASTRESULT
    animatesprite freezeParticle freezeAffinePtr
    runtask TaskfreezeEffect freezeParticle 0 0 0
    pauseframes 10
    addvar 0x8002 1
    goto freezeLoop

finishfreeze:
    fadespritebg 3 0x6546 FADEFROM true 10
    showsprite target
    spritebgclear target
    deletesprite 0x800A
    end
.pool
