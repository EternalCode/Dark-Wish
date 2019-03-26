.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ Impound, 0x9006

.global PoundAnimation
PoundAnimation:
	fastsetbattlers
	loadspritefull impact1Sprite impact1Palette impactSmallOam
	copyvar Impound LASTRESULT
	animatesprite Impound impactSmallAffine 0
	spritetobg target 8 8
	spriteblend 4 12
	BLOCKCMD
	rendersprite Impound targetx targety impactSmallAffine
	quakebg 1 2 0 2 2 false
	setvar gLASTRESULT 0x57FF
	startscript FireworkAnimation true
	OPENCMD
	pauseframes 10
	deletesprite Impound
	waitthread 1
	
    end

.pool
