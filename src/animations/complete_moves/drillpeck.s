.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ sandParticle, 0x9007
.equ counter, 0x9008
.equ tempImpactParticle, 0x9009
.equ tempSandParticle, 0x900A


.global DrillPeckAnimation
DrillPeckAnimation:
    fastsetbattlers
    // impact
    BLOCKCMD
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

    spritetobg target 8 8
    showbg 1
    OPENCMD
    hidehpbars
    blendsemitransparent 12 8

    // attacker should duck
    sideof attacker
    if2 0x0 goto playerDuck
    if2 0x1 goto opponentDuck
    startscript quakeDrillpeck true

    // circle around sprite effects
    addvar targetx 0
    addvar targety 0xFFE8
    call drawImpacts
    fastsetbattlers
    addvar targetx 24
    addvar targety 0xFFF4
    call drawImpacts
    fastsetbattlers
    addvar targetx 24
    addvar targety 12
    call drawImpacts
    fastsetbattlers
    addvar targetx 0
    addvar targety 24
    call drawImpacts
    fastsetbattlers
    addvar targetx 0xFFE8
    addvar targety 12
    call drawImpacts
    fastsetbattlers
    addvar targetx 0xFFE8
    addvar targety 0xFFF4
    call drawImpacts
    sideof attacker
    if2 0x0 goto restorePlayerDuck
    if2 0x1 goto restoreOpponentDuck
    pauseframes 10
    deletesprite sandParticle
    deletesprite impactParticle
    waitthread 1
    showsprite target
    spritebgclear target
    clearblending
    showhpbars
    end

drawImpacts:
    BLOCKCMD
    loadsprite impact4Sprite impact4Palette peckOam
    copyvar tempImpactParticle LASTRESULT
    rendersprite tempImpactParticle targetx targety nullrsf
    spritecallback tempImpactParticle SCB_SpriteDeleteAfter10Frames
    spritepriority tempImpactParticle 1
    OPENCMD
    loadsprite sandattackSprite sandattackPalette sandattackOam
    BLOCKCMD
    copyvar tempSandParticle LASTRESULT
    setframessprite 0 tempSandParticle drillpeckFrames
    rendersprite tempSandParticle targetx targety nullrsf
    spritecallback tempSandParticle SCB_SpriteDeleteWhenAnimEnds
    spritepriority tempSandParticle 1
    OPENCMD
    return

playerDuck:
    movesprite attacker 0xFFFC 0 4 true
    wait
    movesprite attacker 0 7 2 false
    animatesprite attacker drillpeckPlayerAffine 0
    waitaffineanimation attacker
    movesprite attacker 4 0 4 false
    return

restorePlayerDuck:
    movesprite attacker 0 0xFFF9 2 false
    animatesprite attacker drillpeckRestorePlayerAffine 0
    return

opponentDuck:
    movesprite attacker 4 0 4 true
    wait
    movesprite attacker 0 4 2 false
    animatesprite attacker drillpeckOpponentAffine 0
    waitaffineanimation attacker
    movesprite attacker 0xFFFC 0 4 false
    return

restoreOpponentDuck:
    movesprite attacker 0 0xFFFC 2 false
    animatesprite attacker drillpeckRestoreOpponentAffine 0
    return


quakeDrillpeck:
    pauseframes 10
    quakebg 1 3 0 6 2 true
    end

.pool
