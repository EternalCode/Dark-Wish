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
.equ smokeParticle, 0x800B
.equ impactParticle, 0x800C
.equ smokeParticle2, 0x8003
.equ smokeParticle3, 0x8002
.equ smokeParticle4, 0x8001
.equ LASTRESULT, 0x800D

.global TakedownAnimation
TakedownAnimation:
    // Always load things before the animation,
    // so to not waste frames during the animation itself
    fastsetbattlers
    loadspritefull smokeSprite smokePalette smokeOam
    copyvar smokeParticle LASTRESULT
    loadsprite smokeSprite smokePalette smokeOam
    copyvar smokeParticle2 LASTRESULT
    loadsprite smokeSprite smokePalette smokeOam
    copyvar smokeParticle3 LASTRESULT
    loadsprite smokeSprite smokePalette smokeOam
    copyvar smokeParticle4 LASTRESULT
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    sideof attacker
    if1 0x1 goto TakedownSpriteMoveOpponent

TakedownSpriteMovePlayer:
    movesprite attacker 0xFFFD 1 1
    wait
    movesprite attacker 0xFFFD 1 1
    wait
    movesprite attacker 0xFFFD 1 1
    wait
    movesprite attacker 0xFFFD 1 1
    wait
    movesprite attacker 0xFFFD 1 1
    wait
    movesprite attacker 0xFFFD 1 1
    wait
    pauseframes 8
    movesprite attacker 6 0xFFFD 3
    wait
    goto TakedownTargetSideEffects

TakedownSpriteMoveOpponent:
    movesprite attacker 3 0xFFFF 1
    wait
    movesprite attacker 3 0xFFFF 1
    wait
    movesprite attacker 3 0xFFFF 1
    wait
    movesprite attacker 3 0xFFFF 1
    wait
    movesprite attacker 3 0xFFFF 1
    wait
    movesprite attacker 3 0xFFFF 1
    wait
    pauseframes 8
    movesprite attacker 0xFFFA 2 3
    wait

TakedownTargetSideEffects:
    quakesprite target 6 0 2 2 false
    rendersprite impactParticle targetx targety nullrsf
    subvar targetx 10
    rendersprite smokeParticle targetx targety nullrsf
    subvar targety 10
    rendersprite smokeParticle2 targetx targety nullrsf
    addvar targetx 20
    addvar targety 10
    rendersprite smokeParticle3 targetx targety nullrsf
    addvar targety 10
    rendersprite smokeParticle4 targetx targety nullrsf
    setframessprite 0 smokeParticle smokeLoopPtr
    setframessprite 0 smokeParticle2 smokeLoopPtr
    setframessprite 0 smokeParticle3 smokeLoopPtr
    setframessprite 0 smokeParticle4 smokeLoopPtr
    pauseframes 10
    deletesprite impactParticle
    deletesprite smokeParticle2
    deletesprite smokeParticle3
    deletesprite smokeParticle4
    deletesprite smokeParticle
    end
.pool
