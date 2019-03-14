.text
.thumb
.align 2
.include "src/animation_cmds.s"

// used for swords are 9006, 9007, 9008, 9009, 900A
.equ impactParticle, 0x900C
.equ coeffB, 0x900E
.equ coeffA, 0x900F
.equ swordParticle, 0x9010
.equ glowballParticle, 0x9011
.equ counter, 0x9012


.global SwordsDanceAnimation
SwordsDanceAnimation:
    fastsetbattlers
    loadspritefull blueglowballSprite blueglowballPalette blueglowballOam
    copyvar glowballParticle LASTRESULT
    loadspritefull swordSprite swordPalette swordOam
    copyvar swordParticle LASTRESULT
    setvar counter 0
    subvar attackery 16
    spritepriority attacker 1
    spritepriority attacker 1
    BLOCKCMD

// unrolling the loop
    loadsprite swordSprite swordPalette swordOam
    copyvar 0x9006 LASTRESULT
    loadsprite swordSprite swordPalette swordOam
    copyvar 0x9007 LASTRESULT
    loadsprite swordSprite swordPalette swordOam
    copyvar 0x9008 LASTRESULT
    loadsprite swordSprite swordPalette swordOam
    copyvar 0x9009 LASTRESULT
    loadsprite swordSprite swordPalette swordOam
    copyvar 0x900A LASTRESULT

    orbit 0x9006 attacker 110 32 4 0 4 false false 0
    orbit 0x9007 attacker 110 32 4 0 4 false false 51
    orbit 0x9008 attacker 110 32 4 0 4 false false 102
    orbit 0x9009 attacker 110 32 4 0 4 false false 153
    orbit 0x900A attacker 110 32 4 0 4 false false 205

    animatesprite 0x9006 swordAffine 0
    animatesprite 0x9007 swordAffine 0
    animatesprite 0x9008 swordAffine 0
    animatesprite 0x9009 swordAffine 0
    animatesprite 0x900A swordAffine 0

    runspritefunc 0x9006 BeginAffineAnim
    runspritefunc 0x9007 BeginAffineAnim
    runspritefunc 0x9008 BeginAffineAnim
    runspritefunc 0x9009 BeginAffineAnim
    runspritefunc 0x900A BeginAffineAnim

    rendersprite 0x9006 attackerx attackery swordAffine
    rendersprite 0x9007 attackerx attackery swordAffine
    rendersprite 0x9008 attackerx attackery swordAffine
    rendersprite 0x9009 attackerx attackery swordAffine
    rendersprite 0x900A attackerx attackery swordAffine

    semitransparent 0x9006
    semitransparent 0x9007
    semitransparent 0x9008
    semitransparent 0x9009
    semitransparent 0x900A
    OPENCMD
    setvar counter 0
    waitaffineanimation 0x900A
    addvar attackery 16
    BLOCKCMD
spawnShinies:
    compare counter 256
    if1 0x1 goto swordsDanceFade
    loadsprite blueglowballSprite blueglowballPalette blueglowballOam
    orbit LASTRESULT attacker 60 28 4 1 3 false true counter
    rendersprite LASTRESULT attackerx attackery nullrsf
    movesprite LASTRESULT 0 0xFFFF 10 false
    addvar counter 64
    goto spawnShinies

swordsDanceFade:
    OPENCMD
    pauseframes 50
    spritetobg attacker 8 8
    setvar coeffA 16
    setvar coeffB 0
    blendsemitransparent coeffA coeffB

fadeLoop:
    compare coeffB 16
    BLOCKCMD
    if1 0x1 goto finish
    addvar coeffB 2
    subvar coeffA 2
    blendsemitransparent coeffA coeffB

    spriteblend2 0x9006 coeffB 0
    spriteblend2 0x9007 coeffB 0
    spriteblend2 0x9008 coeffB 0
    spriteblend2 0x9009 coeffB 0
    spriteblend2 0x900A coeffB 0

continueFadeLoop:
    setvar counter 0
    OPENCMD
    goto fadeLoop

finish:
    OPENCMD
    deletesprite 0x9006
    deletesprite 0x9007
    deletesprite 0x9008
    deletesprite 0x9009
    deletesprite 0x900A
    deletesprite glowballParticle
    deletesprite swordParticle
    clearblending
    showsprite attacker
    hidebg 1
    spritebgclear attacker
    spritepriority attacker 3
    end

.pool
