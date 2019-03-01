.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impact2Particle, 0x900B

.global SlamAnimation
SlamAnimation:
	startscript FireworkAnimation false
	fastsetbattlers
	loadspritefull impact2Sprite impact2Palette impact2Oam
	copyvar impact2Particle LASTRESULT
	hidehpbars
	movesprite attacker 5 3 2 false
	rendersprite impact2Particle targetx targety nullrsf
	movebg 1 5 3 2 false
	movesprite impact2Particle 1 3 3 true
	wait
	deletesprite impact2Particle
	movesprite attacker 0xFFFB 0xFFFD 2 true
	movebg 1 0xFFFB 0xFFFD 2 false
	wait
	waittask TaskCreateSmallFireworkImpact
	showhpbars
	end

.pool
