.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ sandParticle, 0x9007

.global PeckAnimation
PeckAnimation:
    fastsetbattlers
    // impact
    loadspritefull impact4Sprite impact4Palette peckOam
    copyvar impactParticle LASTRESULT
    semitransparent impactParticle
    spriteblend2 impactParticle 12 0x47FF
    spritepriority impactParticle 1

    // sand
    loadspritefull sandattackSprite sandattackPalette sandattackOam
    copyvar sandParticle LASTRESULT
    semitransparent sandParticle
    spriteblend2 sandParticle 12 0x47FF
    spritepriority sandParticle 1

    // diagonal movement on impact
    movesprite target 0 4 2 false
    BLOCKCMD
    sideof attacker
    if2 0x0 goto duckRight
    if2 0x1 goto duckLeft
    OPENCMD
    pauseframes 13
    movesprite target 0 0xFFFC 2 true
    wait
    BLOCKCMD
    spritetobg target 8 8
    showbg 1
    addvar targety 10
    blendsemitransparent 12 4
    OPENCMD
    rendersprite impactParticle targetx targety nullrsf
    setframessprite 0 sandParticle sandattackFrames
    rendersprite sandParticle targetx targety nullrsf
    spritecallback sandParticle SCB_SpriteDeleteWhenAnimEnds
    pauseframes 4
    deletesprite impactParticle
    showsprite target
    spritebgclear target
    clearblending
    pauseframes 5
    end

duckLeft:
    animatesprite target playerPeckAffine 0
    return

duckRight:
    animatesprite target opponentPeckAffine 0
    return

.pool
