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

.global ReceiveDamage
ReceiveDamage:
    fastsetbattlers
    shakehpbox target
    hidesprite target
    pauseframes 3
    showsprite target
    pauseframes 3
    hidesprite target
    pauseframes 3
    showsprite target
    pauseframes 3
    hidesprite target
    pauseframes 3
    showsprite target
    pauseframes 3
    hidesprite target
    pauseframes 3
    showsprite target
    end
.pool
