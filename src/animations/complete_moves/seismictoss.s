.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ rockParticle, 0x9006
.equ impactParticle, 0x9007

.global SeismicTossAnimation
SeismicTossAnimation:
    fastsetbattlers
    loadbg2 32 seismictossbgTiles seismictossbgMap seismictossbgPal
    addfadeplatformbg
    addfadebg2
    spritetobg target 8 8
    showbg 1
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    blendsemitransparent 8 8
    hidehpbars
    beginfade 2 0 FADETO true 16
    showbg 2
    beginfade 2 0 FADEFROM false 16
    runtask TaskMoveBGSeismicToss 0 0 0 0
    startscript seismictossbgCleanUp true
    pauseframes 164
    addvar targety 24
    startscript seismictossRocks true
    waitthread 2
    startscript seismictossRocks true
    waitthread 2
    startscript seismictossRocks true
    waitthread 2
    startscript seismictossRocks true
    waitthread 2
    startscript seismictossRocks true
    waitthread 2
    waitthread 1
    deletesprite impactParticle
    showsprite target
    hidebg 1
    spritebgclear target
    clearblending
    showhpbars
    end

seismictossRocks:
    BLOCKCMD
    loadspritefull rockSprite rockPalette rockOam
    copyvar rockParticle LASTRESULT
    applyfirework rockSprite rockPalette rockOam rockAffine 3 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 3 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 3 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 3 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 1 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 1 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 1 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 1 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 2 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 2 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 0 targetx targety
    applyfirework rockSprite rockPalette rockOam rockAffine 0 targetx targety
    loadsprite impact1Sprite impact1Palette impact1Oam
    semitransparent LASTRESULT
    spritepriority LASTRESULT 1
    subvar targety 12
    rendersprite LASTRESULT targetx targety nullrsf
    spritecallback LASTRESULT SCB_SpriteDeleteAfter10Frames
    OPENCMD
    addvar targety 12
    waittask TaskCreateSmallFireworkGeneric
    end


seismictossbgCleanUp:
    pauseframes 220
    beginfade 2 0 FADETO true 16
    hidebg 2
    beginfade 2 0 FADEFROM true 16
    waittask TaskMoveBGSeismicToss
    setbgpos 2 0 0
    end

.pool
