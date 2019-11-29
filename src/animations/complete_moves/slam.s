.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impactParticle, 0x9006

.global SlamAnimation
SlamAnimation:
	fastsetbattlers
	setvar gLASTRESULT 0x57FF
	startscript FireworkAnimation true
	loadspritefull impact6Sprite impact6Palette impact6SlamOam
	copyvar impactParticle LASTRESULT
	spriteblend 4 12
	hidehpbars
	BLOCKCMD
	sideof attacker
	if2 0x0 call SlamMovementPlayerSide
	if2 0x1 call SlamMovementOpponentSide
	animatesprite impactParticle impact6SlamAffine 0
	subvar targety 24
	OPENCMD
	BLOCKCMD
	rendersprite impactParticle targetx targety impact6SlamAffine
	movesprite impactParticle 0 4 6 true
	OPENCMD
	wait
	BLOCKCMD
	deletesprite impactParticle
	sideof attacker
	if2 0x0 call SlamPlayerReturnMovement
	if2 0x1 call SlamOpponentReturnMovement
	OPENCMD
	wait
	waitthread 1
	showsprite target
	hidebg 1
	spritebgclear target
	clearblending
	showhpbars
	end

SlamMovementPlayerSide:
	movesprite attacker 5 3 2 false
	movebg 1 5 3 2 RIGHT false
	return

SlamMovementOpponentSide:
	movesprite attacker 0xFFFB 3 2 false
	movebg 1 5 0xFFFD 2 LEFT false
	return

SlamPlayerReturnMovement:
	movesprite attacker 0xFFFB 0xFFFD 2 true
	movebg 1 5 3 2 LEFT false
	return

SlamOpponentReturnMovement:
	movesprite attacker 5 0xFFFD 2 true
	movebg 1 5 0xFFFD 2 RIGHT false
	return


.pool
