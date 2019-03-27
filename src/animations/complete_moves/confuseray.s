.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ confuseParticle, 0x9006
.equ innerParticle, 0x9007
.equ counter, 0x9008

.global ConfuseRayAnimation
ConfuseRayAnimation:
    fastsetbattlers

loadConfuseRaySprites:
    BLOCKCMD
    loadspritefull confuseraySprite confuserayPalette confuserayOam
    copyvar confuseParticle LASTRESULT
    loadspritefull innerraySprite innerrayPalette innerrayOam
    copyvar innerParticle LASTRESULT
    semitransparent confuseParticle
    animatesprite confuseParticle confuserayAffine 0
    animatesprite innerParticle confuserayAffine 0
    OPENCMD

blendAndFadePrep:
    blendsemitransparent 8 8
    addfadeplatformbg
    spritetobg target 8 8

startingAnimation:
    hidehpbars
    beginfade 4 0x0000 FADETO true 14

    // rendering sprites
    rendersprite confuseParticle attackerx attackery confuserayAffine
    rendersprite innerParticle attackerx attackery confuserayAffine

    // color change for confuse ray particles
    setvar counter 0
    startscript ColorChange true

    // sync sprite wave movements
    BLOCKCMD
    movewave confuseParticle target 3 2 54
    movewave innerParticle target 3 2 54
    OPENCMD

    // hide sprites once they reach target
    pauseframes 54
    BLOCKCMD
    hidesprite confuseParticle
    hidesprite innerParticle
    OPENCMD
    pauseframes 5
    subvar targety 16
    spritesetposition confuseParticle targetx targety
    spritesetposition innerParticle targetx targety
    // showsprites orbiting the target
    BLOCKCMD
    showsprite confuseParticle
    showsprite innerParticle
    depthlessorbit confuseParticle target 100 25 2 0 8 false true 0
    depthlessorbit innerParticle target 100 25 2 0 8 false true 0
    setvar counter 0
    OPENCMD

loopDownwardMovement:
    compare counter 8
    if1 0x1 goto finishLoop
    BLOCKCMD
    movesprite confuseParticle 0 1 3 false
    movesprite innerParticle 0 1 3 true
    OPENCMD
    wait
    pauseframes 4
    addvar counter 1
    goto loopDownwardMovement

finishLoop:
    beginfade 4 0x0000 FADEFROM true 14
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    showhpbars
    end


// Color Change script
ColorChange:
    compare counter 7
    if1 0x1 goto finishColorChange

    // yellow
    blendsemitransparent 8 8
    BLOCKCMD
    spriteblend2 confuseParticle 14 0x2278
    spriteblend2 innerParticle 14 0x2278
    OPENCMD
    pauseframes 8

    // green
    blendsemitransparent 4 12
    BLOCKCMD
    spriteblend2 confuseParticle 14 0x2F13
    spriteblend2 innerParticle 14 0x2F13
    OPENCMD
    pauseframes 4

    // loopcounter increment
    addvar counter 1
    goto ColorChange

finishColorChange:
    end

.pool
