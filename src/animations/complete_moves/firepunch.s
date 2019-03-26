.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ fireParticle, 0x9006
.equ fistParticle, 0x9007
.equ counter, 0x9008
.equ multiplyBuffer, 0x9009
.equ randX, 0x900A
.equ randY, 0x900B
.equ tempSprite, 0x900C

.global FirepunchAnimation
FirepunchAnimation:
    loadspritefull smallfireSprite smallfirePalette smallfireOam
    copyvar fireParticle LASTRESULT
    loadspritefull bigfistSprite bigfistPalette bigfistOam
    copyvar fistParticle LASTRESULT
    animatesprite fistParticle bigfistShrinkAffine 0
    fastsetbattlers
    setvar counter 0
    addpalbuffer target false
    addfadeplatformbg
    beginfade 3 0x1CF8 FADETO false 10
    hidehpbars
    BLOCKCMD

firepunchFireOrbiting:
    compare counter 0x6
    if1 0x1 goto showFist
    loadsprite smallfireSprite smallfirePalette smallfireOam
    setframessprite 0 LASTRESULT smallfireFrames
    copyvar multiplyBuffer counter
    mulvar multiplyBuffer 43
    rendersprite LASTRESULT targetx targety nullrsf
    hidesprite LASTRESULT
    shrinkingorbit LASTRESULT target 42 24 24 0 6 false true multiplyBuffer
    showsprite LASTRESULT
    addvar counter 1
    goto firepunchFireOrbiting

showFist:
    OPENCMD
    pauseframes 40
    rendersprite fistParticle targetx targety bigfistShrinkAffine
    quakesprite fistParticle 3 3 6 1 false
    quakesprite target 2 0 6 1 false
    setvar counter 0

disperseFlames:
    BLOCKCMD
    compare counter 14
    if1 0x1 goto finishAnimation
    // disperse flames six directions
    call spawnFlameRandomDir
    addvar counter 1
    OPENCMD
    goto disperseFlames

finishAnimation:
    OPENCMD
    deletesprite fistParticle
    waittask TaskMoveSprite
    deletesprite fireParticle
    beginfade 3 0x1CF8 FADEFROM true 10
    showhpbars
    end

spawnFlameRandomDir:
    loadsprite smallfireSprite smallfirePalette smallfireAffOam
    copyvar tempSprite LASTRESULT
    setframessprite 0 tempSprite smallfireFrames
    rendersprite tempSprite targetx targety smallfireAffine
    // pick random xOff
    random 0 5
    subvar LASTRESULT 2
    copyvar randX LASTRESULT
    // pick random yOff
    random 0 5
    subvar LASTRESULT 2
    copyvar randY LASTRESULT
    movesprite tempSprite randX randY 20 false
    spritecallback tempSprite SCB_SpriteDeleteWhenAffineEnds
    return

.pool
