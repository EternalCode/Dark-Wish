.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ stompParticle, 0x9006

.global StompAnimation
StompAnimation:
    fastsetbattlers
    loadspritefull stompSprite stompPalette stompOam
    copyvar stompParticle LASTRESULT
    subvar targety 32
    rendersprite stompParticle targetx targety nullrsf
    movesprite stompParticle 0 4 16 false
    pauseframes 4
    BLOCKCMD
    addvar targety 32
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimationNoBlend true
    OPENCMD
    movesprite target 0 7 1 false
    animatesprite target stompSquishAffine 0
    pauseframes 3
    quakebg 1 2 0 2 2 true
    deletesprite stompParticle
    waitthread 1
    waitaffineanimation target
    movesprite target 0 0xFF9 1 false
    end

.pool
