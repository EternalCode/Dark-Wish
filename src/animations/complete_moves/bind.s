.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ bindParticle1, 0x9006
.equ bindParticle2, 0x9007

.global BindAnimation
BindAnimation:
    fastsetbattlers
    loadspritefull bindSprite bindPalette bindOam
    copyvar bindParticle1 LASTRESULT
    rendersprite bindParticle1 targetx targety nullrsf
    pauseframes 5
    BLOCKCMD
    animatesprite bindParticle1 bindAffine 0
    animatesprite target bindAffine 0
    OPENCMD
    waitaffineanimation target
    pauseframes 5
    deletesprite bindParticle1
    pauseframes 1
    end

.pool
