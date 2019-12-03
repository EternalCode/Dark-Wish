.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ dustParticle, 0x9006
.equ counter, 0x9007
.equ buffx, 0x9008
.equ buffy, 0x9009
.equ tempsprite, 0x900A

.global BlizzardAnimation
BlizzardAnimation:
    fastsetbattlers
    loadbg2 32 blizzardbgTiles blizzardbgMap blizzardbgPal
    loadspritefull smokeballSprite smokeballPalette smokeball_noaffineOam
    copyvar dustParticle LASTRESULT
    addfadeplatformbg
    addfadebg2
    spritetobg target 8 8
    showbg 1
    hidehpbars
    beginfade 2 0 FADETO true 16
    BLOCKCMD
    sideof attacker
    if2 0x0 goto playerbgmove
    if2 0x1 goto opponentbgmove
    showbg 2
    OPENCMD
    beginfade 1 0 FADEFROM true 16
    BLOCKCMD
    blendsemitransparent 4 12
    setvar counter 0
    startscript animFreezeNoPalFade true
    quakebg 1 2 0 8 2 false

loopSmoke:
    OPENCMD
    BLOCKCMD
    compare counter 8
    if1 0x1 goto finishAnimation
    loadsprite smokeballSprite smokeballPalette smokeball_noaffineOam
    copyvar tempsprite LASTRESULT
    spritepriority tempsprite 1
    semitransparent tempsprite
    spriteblend2 tempsprite 14 0x735C
    setvar buffx 0xFFE0
    setvar buffy 60
    pickrandompos buffx buffy 0 100
    rendersprite tempsprite buffx buffy nullrsf
    sideof attacker
    if2 0x0 goto playersmokemove
    if2 0x1 goto opponentsmokemove
    OPENCMD
    spritecallback tempsprite SCB_SpriteDeleteAfter60Frames
    addvar counter 1
    BLOCKCMD
    goto loopSmoke


finishAnimation:
    OPENCMD
    waitthread 1
    beginfade 2 0 FADETO true 16
    BLOCKCMD
    hidebg 2
    setbgpos 2 0 0
    OPENCMD
    beginfade 1 0 FADEFROM true 16
    BLOCKCMD
    spritepriority attacker 3
    showsprite target
    hidebg 1
    spritebgclear target
    hidebg 2
    clearblending
    OPENCMD
    showhpbars
    end

playerbgmove:
    movebg 2 8 0 255 RIGHT false
    return

opponentbgmove:
    movebg 2 8 0 255 LEFT false
    return

playersmokemove:
    movesprite tempsprite 10 0 40 false
    return

opponentsmokemove:
    movesprite tempsprite 0xFFF6 0 60 false
    return

.pool
