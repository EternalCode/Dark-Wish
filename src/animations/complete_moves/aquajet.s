.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ aquaJet, 0x9006

.global AquaJetAnimation
AquaJetAnimation:
	hidehpbars
	fastsetbattlers
	loadspritefull aquajetSprite aquajetPalette aquajetOam
	copyvar aquaJet LASTRESULT
	spritetobg target 8 8
	spriteblend 4 12
	hidesprite attacker
	rendersprite aquaJet attackerx attackery nullrsf
	setframessprite 0 aquaJet aquajetFrames
    spritemovedst 30 aquaJet target
	pauseframes 30
    BLOCKCMD
	deletesprite aquaJet
	quakebg 1 8 0 2 5 true
	OPENCMD
	pauseframes 10
	spritebgclear target
	showsprite attacker
	showhpbars
    end
	


.pool
