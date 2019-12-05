.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ dustParticle, 0x9006
.equ counter, 0x9007
.equ waveOffset, 0x9008
.equ waveOffsetDelta, 0x9009
.equ tempParticle, 0x900A
.equ impactParticle, 0x900B
.equ ogX, 0x900C
.equ ogY, 0x900E
.equ tempX, 0x9008
.equ tempY, 0x9009

.global SubmissionAnimation
SubmissionAnimation:
    fastsetbattlers
    // dust tornade assets
    loadspritefull smokeballSprite smokeballPalette smokeballOam
    copyvar dustParticle LASTRESULT
    loadspritefull impact4Sprite impact4Palette impact4Oam
    copyvar impactParticle LASTRESULT
    hidehpbars
    spritetobg target 8 8
    showbg 1
    blendsemitransparent 10 6
    sideof attacker
    if2 0x0 goto normalAnim
    if2 0x1 goto backspriteModded

backspriteModded:
    BLOCKCMD
    copyvar ogX attackerx
    copyvar ogY attackery
    addvar attackery 8
    subvar attackerx 8
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 128 24 8 RIGHT 16 false false 0
    subvar attackery 10
    depthlessorbitbg 128 24 8 LEFT 16 128
    goto continued


normalAnim:
    BLOCKCMD
    copyvar ogX attackerx
    copyvar ogY attackery
    addvar attackery 8
    subvar attackerx 8
    spritesetposition attacker attackerx attackery
    depthlessorbit attacker attacker 128 24 8 LEFT 16 false false 0
    subvar attackery 10
    depthlessorbitbg 128 24 8 RIGHT 16 0

continued:
    addvar targety 16
    setvar counter 0
    setvar waveOffsetDelta 255
    divvar waveOffsetDelta 8
    startscript impactTornado true

dustAnimationLoop:
    compare counter 8
    if1 0x1 goto finishAnim
    loadsprite smokeballSprite smokeballPalette smokeballOam
    copyvar waveOffset waveOffsetDelta
    mulvar waveOffset counter
    orbit LASTRESULT target 128 40 6 0 4 false true waveOffset
    animatesprite LASTRESULT smokeballAffine 0
    runspritefunc LASTRESULT BeginAffineAnim
    rendersprite LASTRESULT targetx targety smokeballAffine
    spriteblend2 LASTRESULT 12 0x4B17
    copyvar tempParticle LASTRESULT
    random 0 100
    compare LASTRESULT 40
    if2 0 call makeTransparent
    addvar counter 1
    goto dustAnimationLoop

finishAnim:
    OPENCMD
    waitthread 1
    waittask TaskAnimOrbitFastStepNoPriority
    spritesetposition attacker ogX ogY
    deletesprite dustParticle
    showsprite target
    hidebg 1
    clearblending
    setbgpos 1 0 0
    showhpbars
    end


makeTransparent:
    semitransparent tempParticle
    return

impactTornado:
    compare counter 19
    if1 0x1 goto endTornado
    BLOCKCMD
    fastsetbattlers
    copyvar tempX targetx
    subvar tempX 32
    random 0 64
    addvar tempX LASTRESULT
    copyvar tempY targety
    subvar tempY 32
    random 0 64
    addvar tempY LASTRESULT
    loadsprite impact4Sprite impact4Palette impact4Oam
    copyvar tempParticle LASTRESULT
    random 0 100
    compare LASTRESULT 40
    if2 0 call makeTransparent
    semitransparent tempParticle
    spriteblend2 tempParticle 14 0x47FF
    spritepriority tempParticle 1
    addvar counter 1
    OPENCMD
    rendersprite tempParticle tempX tempY nullrsf
    spritecallback tempParticle SCB_SpriteDeleteAfter10Frames
    goto impactTornado

endTornado:
    pauseframes 10
    deletesprite impactParticle
    end

.pool
