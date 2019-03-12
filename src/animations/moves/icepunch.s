.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ freezeParticle, 0x9006
.equ fistParticle, 0x9007
.equ counter, 0x9008
.equ multiplyBuffer, 0x9009
.equ randX, 0x900A
.equ randY, 0x900B
.equ tempSprite, 0x900C

.global IcepunchAnimation
IcepunchAnimation:
    loadspritefull freezeSprite freezePalette freezeOam
    copyvar freezeParticle LASTRESULT
    loadspritefull bigbluefistSprite bigbluefistPalette bigfistOam
    copyvar fistParticle LASTRESULT
    animatesprite fistParticle bigfistShrinkAffine 0
    fastsetbattlers
    setvar counter 0
    addfadeplatformbg
    beginfade 3 0x7B99 FADETO false 10
    hidehpbars

showFist:
    pauseframes 40
    rendersprite fistParticle targetx targety bigfistShrinkAffine
    quakesprite fistParticle 3 3 6 1 false
    quakesprite target 2 0 6 1 false
    setvar counter 0

disperseFlames:
    deletesprite fistParticle
    waittask TaskMoveSprite
    beginfade 3 0x7B99 FADEFROM true 10
    deletesprite freezeParticle
    startscript animFreeze true
    pauseframes 20
    showhpbars
    end

.pool
