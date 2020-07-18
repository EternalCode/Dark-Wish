.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ leafParticle, 0x9007
.equ counter, 0x9008
.equ tempSprite, 0x9009
.equ ogX, 0x900A
.equ ogY, 0x900B
.equ waitingInterval, 0x900C
.equ coefficientA, 0x900D
.equ coefficientB, 0x900E

.global RazorLeafAnimation
RazorLeafAnimation:
    fastsetbattlers
    copyvar ogX attackerx
    copyvar ogY attackery
    loadspritefull razorleafSprite razorleafPalette razorleafOam
    copyvar leafParticle LASTRESULT
    hidehpbars
    BLOCKCMD
    sideof attacker
    if1 0x0 goto RazorLeafsFloatingPlayer
    goto RazorLeafsFloatingOpp

RazorLeafsFloatingPlayer:
    compare counter 8
    if1 true goto RazorLeafPreProjectileSpawn
    loadsprite razorleafSprite razorleafPalette razorleafOam
    copyvar tempSprite LASTRESULT
    copyvar attackerx ogX
    copyvar attackery ogY
    addvar attackery 32
    pickrandompos attackerx attackery 64 64
    rendersprite tempSprite attackerx attackery razorleafAffine
    animatesprite tempSprite razorleafAffine 0
    spritecallback tempSprite SCB_SpriteRiseFastFallSlow
    runspritefunc tempSprite SCB_SpriteRiseFastFallSlow
    addvar counter 1
    goto RazorLeafsFloatingPlayer

RazorLeafsFloatingOpp:
    compare counter 8
    if1 true goto RazorLeafPreProjectileSpawn
    loadsprite razorleafSprite razorleafPalette razorleafOam
    copyvar tempSprite LASTRESULT
    copyvar attackerx ogX
    copyvar attackery ogY
    addvar attackery 16
    pickrandompos attackerx attackery 64 48
    rendersprite tempSprite attackerx attackery razorleafAffine
    animatesprite tempSprite razorleafAffine 0
    spritecallback tempSprite SCB_SpriteRiseFastFallSlow
    runspritefunc tempSprite SCB_SpriteRiseFastFallSlow
    addvar counter 1
    goto RazorLeafsFloatingOpp

RazorLeafPreProjectileSpawn:
    OPENCMD
    pauseframes 110
    quakebg 1 2 0 2 2 false
    showhpbars
    deletesprite leafParticle
    showsprite target
    spritebgclear target
    end


.pool
