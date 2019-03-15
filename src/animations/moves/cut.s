.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ cutParticle, 0x9006

.global CutAnimation
CutAnimation:
    fastsetbattlers
    loadspritefull vicegripSprite vicegripPalette cutOam
    copyvar cutParticle LASTRESULT
    spritetobg target 8 8
    spriteblend 4 12
    setframessprite 0 cutParticle cutFrame
    BLOCKCMD
    addvar targetx 24
    subvar targety 24
    rendersprite cutParticle targetx targety nullrsf
    movesprite cutParticle 0xFFFD 3 16 true
    OPENCMD
    pauseframes 6
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    quakebg 1 2 0 2 2 false
    wait
    pauseframes 3
    deletesprite cutParticle
    waittask TaskCreateSmallFireworkImpact
    showsprite target
    hidebg 1
    spritebgclear target
    deletesprite cutParticle
    end

.pool
