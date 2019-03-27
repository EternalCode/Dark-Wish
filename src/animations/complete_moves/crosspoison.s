.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ crossLeft, 0x9006
.equ crossRight, 0x9007

.global CrossPoisonAnimation
CrossPoisonAnimation:
	fastsetbattlers
	loadspritefull crosspoisonSprite crosspoisonPalette crosspoisonOam
	copyvar crossLeft LASTRESULT
	loadsprite crosspoisonSprite crosspoisonPalette crosspoisonFlipOam
	copyvar crossRight LASTRESULT
	spritetobg target 8 8
	spriteblend 4 12
	BLOCKCMD
	subvar targetx 12
	addvar targety 12
	rendersprite crossLeft targetx targety nullrsf
	addvar targetx 24
	rendersprite crossRight targetx targety nullrsf
	fastsetbattlers
	OPENCMD
	startscript animPoisonEffect false
	quakebg 1 6 0 2 5 true
	BLOCKCMD
	movesprite crossLeft 4 0xFFFC 15 false
	movesprite crossRight 0xFFFC 0xFFFC 15 false
	OPENCMD
	pauseframes 15
	deletesprite crossLeft
	deletesprite crossRight
	spritebgclear target
    end

.pool
