.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ outterimpact, 0x9006
.equ innerimpact, 0x9007

.global DoubleEdgeAnimation
DoubleEdgeAnimation:
    fastsetbattlers
    BLOCKCMD
    loadspritefull impact6Sprite impact6Palette impact6OriginalOam
    copyvar outterimpact LASTRESULT
    loadspritefull impact7Sprite impact7Palette impact7OriginalOam
    copyvar innerimpact LASTRESULT
    semitransparent outterimpact
    semitransparent innerimpact
    blendsemitransparent 10 6
    spritetobg target 8 8
    addfadeplatformbg
    addfadebg2
    OPENCMD
    showbg 1
    hidehpbars
    addvar attackery 10
    BLOCKCMD
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 33 10 10 1 16 true false 0
    subvar attackery 10
    setvar gLASTRESULT 0x00FA
    OPENCMD
    beginfade 0 0 FADETO false 16
    runtask TaskWaitFade 0 0 0 0
    sideof attacker
    if2 0x0 call movePlayer
    if2 0x1 call moveOpponent
    startscript FireworkAnimationNoBlend true
    wait
    waittask TaskWaitFade
    BLOCKCMD
    sideof attacker
    if2 0x0 call loadPlayersideBg
    if2 0x1 call loadOpponentsideBg
    showbg 2
    beginfade 0 0 FADEFROM true 16
    quakebg 2 2 2 6 1 true
    quakebg 1 3 1 4 2 false
    rendersprite outterimpact targetx targety nullrsf
    rendersprite innerimpact targetx targety nullrsf
    OPENCMD
    wait
    BLOCKCMD
    deletesprite outterimpact
    deletesprite innerimpact
    sideof attacker
    if2 0x0 call movePlayerOriginalLocation
    if2 0x1 call moveOpponentOriginalLocation
    OPENCMD
    beginfade 3 0 FADETO true 16
    wait
    hidebg 2
    beginfade 2 0 FADEFROM true 16
    waitthread 1
    showsprite target
    hidebg 1
    spritebgclear target
    showhpbars
    clearblending
    end

movePlayer:
    spritesetposition attacker attackerx attackery
    movesprite attacker 0xFFFD 2 8 false
    pauseframes 5
    movesprite attacker 8 0xFFFC 4 true
    return

moveOpponent:
    spritesetposition attacker attackerx attackery
    movesprite attacker 3 0xFFFE 8 false
    pauseframes 5
    movesprite attacker 0xFFF8 4 4 true
    return

movePlayerOriginalLocation:
    movesprite attacker 0xFFFE 0 4 true
    return

moveOpponentOriginalLocation:
    movesprite attacker 2 0 4 true
    return

loadPlayersideBg:
    loadbg2 32 doubleedgebg_playerTiles doubleedgebg_playerMap doubleedgebg_playerPal
    return

loadOpponentsideBg:
    loadbg2 32 doubleedgebg_opponentTiles doubleedgebg_opponentMap doubleedgebg_opponentPal
    return



.pool
