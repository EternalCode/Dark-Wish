.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ seedParticle, 0x9006
.equ plantParticle, 0x9007

.global LeechSeedAnimation
LeechSeedAnimation:
    fastsetbattlers
    loadspritefull leechseedSprite leechseedPalette leechseedOam
    copyvar seedParticle LASTRESULT
    loadspritefull leechseed_plantSprite leechseed_plantPalette leechseed_plantOam
    copyvar plantParticle LASTRESULT
    spritetobg target 8 8
    hidehpbars
    call SeedToDst
    call SeedToDst
    call SeedToDst
    waittask TaskTranslateSpriteHorizontal
    pauseframes 10
    deletesprite seedParticle
    blendsemitransparent 8 8
    addvar targety 24
    addvar targetx 24
    call SpawnPlants
    subvar targetx 24
    call SpawnPlants
    subvar targetx 24
    call SpawnPlants
    addvar targetx 24
    subvar targety 24
    spritesetposition target targetx targety
    pauseframes 70
    showsprite target
    spritebgclear target
    clearblending
    showhpbars
    deletesprite plantParticle
    end


SpawnPlants:
    BLOCKCMD
    loadsprite leechseed_plantSprite leechseed_plantPalette leechseed_plantOam
    animatesprite LASTRESULT leechseed_plantAffine 0
    rendersprite LASTRESULT targetx targety leechseed_plantAffine
    setframessprite 0 LASTRESULT leechseed_plantFrames
    spritecallback LASTRESULT SCB_SpriteDeleteWhenAffineEnds
    spritesetposition target targetx targety
    setvar gLASTRESULT 0xFFFF
    OPENCMD
    startscript SeedFirework true
    return

SeedToDst:
    loadsprite leechseedSprite leechseedPalette leechseedOam
    animatesprite LASTRESULT leechseedAffine 0
    rendersprite LASTRESULT attackerx attackery leechseedAffine
    arctranslate LASTRESULT target 270 90 6 30
    spritecallback LASTRESULT SCB_SpriteDeleteAfter30Frames
    return

.equ glowballParticle, 0x9006
.equ glowcolor, 0x900C
.equ speed, 2
.equ speedDir, 3
.equ negSpeed, 0xFFFE
.equ negSpeedDir, 0xFFFD

SeedFirework:
    pauseframes 20
    BLOCKCMD
    copyvar glowcolor gLASTRESULT
    loadspritefull glowballSprite glowballPalette shadowpunchGlowBallOam
    copyvar glowballParticle LASTRESULT
    OPENCMD

    // up
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT 0 negSpeedDir 10 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // up right
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    spriteblend2 LASTRESULT 10 glowcolor
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    movesprite LASTRESULT speed negSpeed 10 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // down right
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    spriteblend2 LASTRESULT 10 glowcolor
    movesprite LASTRESULT speed speed 10 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // down left
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    spriteblend2 LASTRESULT 10 glowcolor
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    movesprite LASTRESULT negSpeed speed 10 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    // up left
    BLOCKCMD
    loadsprite glowballSprite glowballPalette shadowpunchGlowBallOam
    spritecallback LASTRESULT SCB_SpriteDeleteAfter20Frames
    spriteblend2 LASTRESULT 10 glowcolor
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    movesprite LASTRESULT negSpeed negSpeed 10 false
    animatesprite LASTRESULT glowballRev2Affine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety glowballRev2Affine
    OPENCMD
    pauseframes 20
    deletesprite glowballParticle
    end

.pool
