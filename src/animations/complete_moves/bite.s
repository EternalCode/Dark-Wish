.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticleleft, 0x9006
.equ biteTop, 0x9007
.equ biteBot, 0x9008
.equ impactParticleright, 0x9009

.global BiteAnimation
BiteAnimation:
	fastsetbattlers
	loadspritefull biteSprite bitePalette biteOam
	copyvar biteTop LASTRESULT
	loadsprite biteSprite bitePalette biteflippedOam
	copyvar biteBot LASTRESULT
	loadspritefull impact1Sprite impact1Palette impactSmallOam
	copyvar impactParticleleft LASTRESULT
	animatesprite impactParticleleft impactSmallAffine 0
	loadsprite impact1Sprite impact1Palette impactSmallOam
	copyvar impactParticleright LASTRESULT
	animatesprite impactParticleright impactSmallAffine 0
	spritetobg target 8 8
	spriteblend 4 12
	BLOCKCMD
	subvar targety 24
	rendersprite biteTop targetx targety nullrsf
	addvar targety 48
	rendersprite biteBot targetx targety nullrsf
	fastsetbattlers
	OPENCMD
	movesprite biteTop 0 2 10 false
	movesprite biteBot 0 0xFFFE 10 true
	wait
	BLOCKCMD
	subvar targetx 24
	rendersprite impactParticleleft targetx targety impactSmallAffine
	addvar targetx 48
	rendersprite impactParticleright targetx targety impactSmallAffine
	OPENCMD
	pauseframes 2
	quakebg 1 1 3 2 2 false
	BLOCKCMD
	movesprite biteBot 0 2 10 false
	movesprite biteTop 0 0xFFFE 10 true
	OPENCMD
	wait
	deletesprite biteBot
	deletesprite biteTop
	pauseframes 10
	BLOCKCMD
	deletesprite impactParticleleft
	deletesprite impactParticleright
	spritebgclear target
	OPENCMD
    end

.pool
