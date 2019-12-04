.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ bubbleParticle, 0x9006
.equ counter, 0x9007
.equ TempSprite, 0x9008

.global BubbleBeamAnimation
BubbleBeamAnimation:
    fastsetbattlers
    loadspritefull bubblebeamSprite bubblebeamPalette bubblebeamOam
    copyvar bubbleParticle LASTRESULT
    spritetobg target 8 8
    hidehpbars
    startscript bubblebeamSway true

loopBubbles:
    compare counter 8
    if1 0x1 goto finishAnim
    BLOCKCMD
    loadsprite bubblebeamSprite bubblebeamPalette bubblebeamOam
    copyvar TempSprite LASTRESULT
    animatesprite TempSprite bubblebeamAffine 0
    OPENCMD
    rendersprite TempSprite attackerx attackery bubblebeamAffine
    copyvar 0x8000 targetx
    copyvar 0x8001 targety
    runtask TaskRunPoisonTaskAfterFrames TempSprite 60 0 0
    movewave TempSprite target 1 4 60
    addvar counter 1
    goto loopBubbles


finishAnim:
    pauseframes 60
    waitthread 1
    waittask TaskMovePoisonBubble
    showsprite target
    hidebg 1
    spritebgclear target
    showhpbars
    deletesprite bubbleParticle
    end


bubblebeamSway:
    pauseframes 40
    movebg 1 2 0 4 LEFT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 LEFT true
    wait
    movebg 1 2 0 4 LEFT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 LEFT true
    wait
    movebg 1 2 0 4 LEFT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 RIGHT true
    wait
    movebg 1 2 0 4 LEFT true
    wait
    end

.pool
