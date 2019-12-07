.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ orbParticle, 0x9006
.equ innerOrbParticle, 0x900E
.equ healParticle, 0x9007
.equ counter, 0x9008
.equ amplitude, 0x9009
.equ tempParticle, 0x900B
.equ tempParticle2, 0x900C
.equ tempParticle3, 0x900F
.equ oX, 0x9009
.equ oY, 0x900A

.global AbsorbAnimation
AbsorbAnimation:
    fastsetbattlers
    loadspritefull circularSprite circularPalette absorbOrbOam
    copyvar orbParticle LASTRESULT
    loadspritefull confuseraySprite confuserayPalette absorbOrbShadowOam
    copyvar innerOrbParticle LASTRESULT
    copyvar oX attackerx
    copyvar oY attackery
    spritetobg attacker 8 8
    addfadeplatformbg
    hidehpbars
    beginfade 2 0 FADETO true 14
    blendsemitransparent 10 6


loopOrbsLeech:
    BLOCKCMD
    loadsprite circularSprite circularPalette absorbOrbOam
    copyvar tempParticle LASTRESULT
    loadsprite confuseraySprite confuserayPalette absorbOrbShadowOam
    copyvar tempParticle2 LASTRESULT
    // determine orb amplitude
    random 1 5
    copyvar amplitude LASTRESULT
    // determine if orb travels from top or bottom
    animatesprite tempParticle2 absorbOrbShadowAffine 0
    OPENCMD
    spriteblend2 tempParticle2 12 0x273E
    spriteblend2 tempParticle 12 0x273E
    BLOCKCMD
    rendersprite tempParticle targetx targety nullrsf
    rendersprite tempParticle2 targetx targety absorbOrbShadowAffine
    random 0 100
    compare LASTRESULT 50
    if2 0x0 goto orbTop
    if2 0x2 goto orbBot
    addvar counter 1
    spritecallback tempParticle SCB_SpriteDeleteAfter30Frames
    spritecallback tempParticle2 SCB_SpriteDeleteAfter30Frames
    OPENCMD
    compare counter 20
    if1 0x0 goto loopOrbsLeech
    waittask TaskTranslateSpriteHorizontal
    setvar counter 0
    pauseframes 15
    deletesprite orbParticle
    deletesprite innerOrbParticle
    loadspritefull absorbSprite absorbPalette absorbOam
    copyvar healParticle LASTRESULT

loopHealBulb:
    // heal bulb effect
    loadsprite absorbSprite absorbPalette absorbOam
    copyvar tempParticle LASTRESULT
    animatesprite tempParticle absorbAffine 0
    fastsetbattlers
    subvar attackerx 24
    random 0 48
    addvar attackerx LASTRESULT
    addvar attackery 24
    random 0 48
    subvar attackery LASTRESULT

    BLOCKCMD
    movesprite tempParticle 0 0xFFFF 24 false
    rendersprite tempParticle attackerx attackery absorbAffine
    spritecallback tempParticle SCB_SpriteDeleteWhenAffineEnds
    OPENCMD
    addvar counter 1
    compare counter 4
    if1 0x0 goto loopHealBulb
    clearblending
    showsprite attacker
    beginfade 2 0 FADEFROM true 14
    spritebgclear attacker
    deletesprite healParticle
    showhpbars
    end


orbTop:
    arctranslate tempParticle attacker 90 270 amplitude 30
    arctranslate tempParticle2 attacker 90 270 amplitude 30
    return

orbBot:
    arctranslate tempParticle attacker 270 90 amplitude 30
    arctranslate tempParticle2 attacker 270 90 amplitude 30
    return

.pool
