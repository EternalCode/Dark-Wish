.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global PoundAnimation
PoundAnimation:
	fastsetbattlers
	loadspritefull impact1Sprite impact1Palette impactSmallOam
	copyvar impactParticle LASTRESULT
	animatesprite impactParticle impactSmallAffine 0
	spritetobg target 8 8
	spriteblend 4 12
	BLOCKCMD
	rendersprite impactParticle targetx targety impactSmallAffine
	quakebg 1 2 0 2 2 false
	setvar gLASTRESULT 0x57FF
	startscript FireworkAnimation true
	OPENCMD
	pauseframes 10
	deletesprite impactParticle
	waitthread 1
    end

.pool
