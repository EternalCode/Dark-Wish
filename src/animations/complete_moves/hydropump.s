.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ hydroParticle, 0x9006

.global HydroPumpAnimation
HydroPumpAnimation:
    fastsetbattlers
    loadspritefull hydropumpSprite hydropumpPalette hydropumpOam
    copyvar hydroParticle LASTRESULT
    end

.pool
