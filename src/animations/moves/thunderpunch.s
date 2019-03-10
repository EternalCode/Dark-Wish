.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ lightningParticle, 0x9006
.equ counter, 0x9007
.equ angle, 0x9008
.equ fistParticle, 0x9009
.equ paralyzeParticle, 0x900A

.global ThunderpunchAnimation
ThunderpunchAnimation:
    // this block is so the delay for the setup doesnt take time
    BLOCKCMD
    fastsetbattlers
    loadspritefull lightningboltSprite lightningboltPalette lightningboltOam
    copyvar lightningParticle LASTRESULT
    loadspritefull yellowfistSprite yellowfistPalette yellowfistOam
    copyvar fistParticle LASTRESULT
    loadspritefull paralyzeSprite paralyzePalette paralyzeOam
    copyvar paralyzeParticle LASTRESULT
    setvar counter 0
    setvar angle 0
    addfadeplatformbg
    OPENCMD
    hidehpbars
    rendersprite paralyzeParticle targetx targety nullrsf
    setframessprite 0 paralyzeParticle paralyzeLoopPtr
    beginfade 3 0 FADETO false 10
    animatesprite fistParticle bigfistShrinkSlowlyAffinePtr 0
    spritecallback fistParticle SCB_SpriteDeleteWhenAffineEnds
    BLOCKCMD
    rendersprite fistParticle targetx targety bigfistShrinkSlowlyAffinePtr
    quakesprite fistParticle 4 2 4 2 false
    quakesprite target 4 4 4 2 false
    OPENCMD
    spriteblend2 target 8 0x579F
    BLOCKCMD

splashingLightning:
    compare counter 10
    if1 0x1 goto splashLightningRandom
    loadsprite lightningboltSprite lightningboltPalette lightningboltOam
    spritesetposition LASTRESULT targetx targety
    setframessprite 0 LASTRESULT lightningboltFramesPtr
    spritecallbackargs LASTRESULT 0 angle 0 0 SpriteTravelRandDirFlash
    addvar counter 1
    addvar angle 25
    goto splashingLightning

splashLightningRandom:
    OPENCMD
    pauseframes 30
    spriteblend2 target 0 0x579F
    deletesprite paralyzeParticle
    deletesprite lightningParticle
    beginfade 3 0 FADEFROM true 10
    showhpbars
    end

.pool
