.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ impact2Particle, 0x9006

.global SlamAnimation
SlamAnimation:
	fastsetbattlers
	loadspritefull impact2Sprite impact2Palette impact2Oam
	copyvar impact2Particle LASTRESULT
	hidehpbars
	movesprite attacker 5 3 8
	startscript FireworkAnimation true
	rendersprite impact2Particle targetx targety nullrsf
	movesprite target 5 3 8
	movesprite impact2Particle 5 3 8
	wait
	movesprite attacker 0xFFFB 0xFFFD 8
	movesprite target 0xFFFB 0xFFFD 8
	wait
	deletesprite impact2Particle
	waittask TaskCreateSmallFireworkImpact
	showhpbars
	end

.pool
