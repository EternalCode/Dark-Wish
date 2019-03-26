.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9003

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
