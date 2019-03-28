.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ counter, 0x9006
.equ amount, 0x9007

.global NightShadeAnimation
NightShadeAnimation:
    fastsetbattlers
    loadbg2 32 nightshadeTiles nightshadeMap nightshadePal
    semitransparent attacker
    showbg 1
    spritetobg attacker 8 8
    showsprite attacker
    setprioritybg 1 3
    blendsemitransparent 12 4
    addfadeplatformbg
    addfadebg2
    beginfade 2 0x0000 FADETO true 16
    showbg 2
    beginfade 2 0x0000 FADEFROM true 16

    // supersize the attacker sprite
    setvar counter 256
    setvar amount 32
    startscript GrowSprite true
    waitthread 1

    // quake and turn black target
    spriteblend2 target 10 0x0000
    quakesprite target 4 0 4 2 true
    wait
    spriteblend2 target 10 0x0000
    spriteblend2 target 8 0x0000
    spriteblend2 target 6 0x0000
    spriteblend2 target 4 0x0000
    spriteblend2 target 2 0x0000
    spriteblend2 target 0 0x0000

    setvar counter 128
    setvar amount 32
    startscript ShrinkSprite true
    waitthread 1

    beginfade 2 0x0000 FADETO true 16
    hidebg 2
    beginfade 2 0x0000 FADEFROM true 16
    setprioritybg 1 1
    clearblending
    spritebgclear attacker
    nontransparent attacker
    end

GrowSprite:
    compare counter 128
    if1 0x1 goto finishGrow
    superscale attacker counter counter
    subvar counter amount
    goto GrowSprite

finishGrow:
    superscale attacker 128 128
    end

ShrinkSprite:
    compare counter 256
    if1 0x1 goto finishShrink
    superscale attacker counter counter
    addvar counter amount
    goto ShrinkSprite

finishShrink:
    superscale attacker 256 256
    end

.pool
