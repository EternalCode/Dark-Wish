.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012

// You must set the target to the BG before calling this
// Additionally, set the CoefficientA, CoefficientB and speed to starting values

.global FadeToBGAnimation
FadeToBGAnimation:
    blendsemitransparent coA coB

fadeLoop:
    compare coB 16
    BLOCKCMD
    if1 0x1 goto finish
    addvar coB speed
    subvar coA speed
    blendsemitransparent coA coB
    OPENCMD
    goto fadeLoop

finish:
    OPENCMD
    end

.pool
