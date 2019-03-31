.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global TailWhipAnimation
TailWhipAnimation:
    fastsetbattlers
    call OrbitOnce
    pauseframes 2
    call OrbitOnce
    end

OrbitOnce:
    addvar attackery 10
    BLOCKCMD
    spritesetposition attacker attackerx attackery
    subvar attackery 10
    depthlessorbit attacker attacker 33 10 10 1 8 true false 0
    OPENCMD
    spritesetposition attacker attackerx attackery
    return


.pool
