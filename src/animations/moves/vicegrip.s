.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ gripTop, 0x9006
.equ gripBot, 0x9007
.equ impactParticle, 0x9008

.global VicegripAnimation
VicegripAnimation:
    fastsetbattlers
    loadspritefull vicegripSprite vicegripPalette vicegripOam
    copyvar gripTop LASTRESULT
    loadspritefull impact1Sprite impact1Palette impact1Oam
    copyvar impactParticle LASTRESULT
    loadsprite vicegripSprite vicegripPalette vicegripFlipOam
    copyvar gripBot LASTRESULT
    spritetobg target 8 8
    spriteblend 4 12
    BLOCKCMD
    setframessprite 0 gripTop vicegripFrame
    setframessprite 0 gripBot vicegripFlipFrame
    addvar targetx 24
    subvar targety 24
    rendersprite gripTop targetx targety nullrsf
    subvar targetx 48
    addvar targety 48
    rendersprite gripBot targetx targety nullrsf
    fastsetbattlers
    OPENCMD
    movesprite gripTop 0xFFFF 1 8 false
    movesprite gripBot 1 0xFFFF 8 true
    wait
    BLOCKCMD
    rendersprite impactParticle targetx targety nullrsf
    quakebg 1 2 0 2 2 false
    setvar gLASTRESULT 0x57FF
    startscript FireworkAnimation true
    OPENCMD
    pauseframes 10
    deletesprite impactParticle
    pauseframes 5
    deletesprite gripTop
    deletesprite gripBot
    end

.pool
