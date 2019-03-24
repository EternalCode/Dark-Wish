.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013

// You must set the target to the BG before calling this
// Additionally, set the CoefficientA, CoefficientB and speed to starting values

.global FadeToBGAnimation
FadeToBGAnimation:
    BLOCKCMD
    blendsemitransparent coA coB
    setvar amount 16
    OPENCMD

fadeLoop:
    comparevars coB amount
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



.global FadeToBGAmountAnimation
FadeToBGAmountAnimation:
    blendsemitransparent coA coB
    goto fadeLoop

.global FadeFromBgAmountAnimation
FadeFromBgAmountAnimation:
    blendsemitransparent coA coB

fadeLoopBackwards:
    comparevars coB amount
    BLOCKCMD
    if1 0x1 goto finish
    subvar coB speed
    addvar coA speed
    blendsemitransparent coA coB
    OPENCMD
    goto fadeLoopBackwards

.pool
