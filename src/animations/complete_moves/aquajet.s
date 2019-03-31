.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ aquaJet, 0x9006
.equ waterSplash, 0x9007

.global AquaJetAnimation
AquaJetAnimation:
	hidehpbars
	fastsetbattlers
	loadspritefull aquajetSprite aquajetPalette aquajetOam
	copyvar aquaJet LASTRESULT
	loadspritefull watersplashSprite watersplashPalette watersplashOam
	copyvar waterSplash LASTRESULT
	spritetobg target 8 8
	spriteblend 4 12
	hidesprite attacker
	rendersprite aquaJet attackerx attackery nullrsf
	setframessprite 0 aquaJet aquajetFrames
    spritemovedst 30 aquaJet target
	pauseframes 30
    BLOCKCMD
	rendersprite waterSplash targetx targety nullrsf
	setframessprite 0 waterSplash watersplashFrames
	deletesprite aquaJet
	quakebg 1 8 0 2 5 true
	OPENCMD
	pauseframes 10
	deletesprite waterSplash
	spritebgclear target
	showsprite attacker
	showhpbars
    end
	


.pool
