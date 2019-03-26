.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006
.equ glowcolor, 0x9007
.equ mainSprite, 0x9006
.equ coA, 0x9010
.equ coB, 0x9011
.equ speed, 0x9012
.equ amount, 0x9013


.global HeadbuttAnimation
HeadbuttAnimation:
    fastsetbattlers
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    // attacker jump animation
    sideof attacker
    if2 0x0 call playerisattacker
    if2 0x1 call opponentisattacker
    startscript StarsFirework true
    BLOCKCMD
    spritepriority impactParticle 1
    semitransparent impactParticle
    rendersprite impactParticle targetx targety nullrsf
    OPENCMD
    quakebg 1 2 0 2 2 true
    wait
    deletesprite impactParticle
    waitthread 1
    end

playerisattacker:
    movesprite attacker 0xFFFE 1 10 true
    wait
    pauseframes 5
    quakesprite attacker 2 0 4 1 true
    wait
    movesprite attacker 4 0xFFFE 5 true
    wait
    return

opponentisattacker:
    movesprite attacker 2 0xFFFF 10 true
    wait
    pauseframes 5
    quakesprite attacker 2 0 4 1 true
    wait
    movesprite attacker 0xFFFC 2 5 true
    wait
    return

StarsFirework:
    BLOCKCMD
    spriteblend 8 8
    hidebg 1
    spritetobg target 8 8
    showbg 1
    loadspritefull starSprite starPalette starOam
    copyvar mainSprite LASTRESULT
    setvar coA 16
    setvar coB 0
    setvar speed 1
    setvar amount 16
    startscript FadeToBGAnimation true
    OPENCMD

    BLOCKCMD
    applyfirework starSprite starPalette starOam starAffine 3 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 3 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 2 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 2 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 1 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 1 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 0 targetx targety
    semitransparent LASTRESULT
    applyfirework starSprite starPalette starOam starAffine 0 targetx targety
    semitransparent LASTRESULT
    OPENCMD

    waittask TaskCreateSmallFireworkGeneric
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite mainSprite
    end
