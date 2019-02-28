.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ attacker, 0x8004
.equ target, 0x8005
.equ targetx, 0x8006
.equ targety, 0x8007
.equ attackerx, 0x8008
.equ attackery, 0x8009
.equ LASTRESULT, 0x800D
.equ impact2Particle, 0x800B

.global SlamAnimation
SlamAnimation:
	fastsetbattlers
	loadspritefull impact2Sprite impact2Palette impact2Oam
	copyvar impact2Particle LASTRESULT
	hidehpbars
	movesprite attacker 5 3 8
	startscript FireworkAnimation
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


