.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ barrage, 0x9006
.equ smoke, 0x9007
.equ smoke2, 0x9008

.global BarrageAnimation
BarrageAnimation:
	fastsetbattlers
	loadspritefull barrageSprite barragePalette barrageOam
	copyvar barrage LASTRESULT
	loadspritefull barragesmokeSprite barragesmokePalette barragesmokeOam
	copyvar smoke LASTRESULT
	loadspritefull barragesmoke2Sprite barragesmoke2Palette barragesmokeOam
	copyvar smoke2 LASTRESULT
	spritetobg target 8 8
	spriteblend 4 12
	BLOCKCMD
	rendersprite barrage attackerx attackery nullrsf
	sideof attacker
	if1 0x1 goto BarrageOpp
	horizontalArcTranslate 0 160 barrage target 35 PLAYERSIDE
    runtask TaskTranslateSpriteHorizontalArc barrage 0 0 0
	OPENCMD
Finish:
	waittask TaskTranslateSpriteHorizontalArcCos
    waittask TaskTranslateSpriteHorizontalArc
	BLOCKCMD
	addvar targety 15
	semitransparent smoke
	rendersprite smoke targetx targety nullrsf
	setframessprite 0 smoke barragesmokeFrames
	semitransparent smoke2
	rendersprite smoke2 targetx targety nullrsf
	setframessprite 0 smoke2 barragesmoke2Frames
	movesprite smoke 5 0 30 true
	movesprite smoke2 0xFFFB 0 30 true
    quakebg 1 0 4 5 2 true
	quakebg 3 0 4 5 2 true
	OPENCMD
	pauseframes 10
	deletesprite smoke
	deletesprite smoke2
	deletesprite barrage
	spritebgclear target
    end

BarrageOpp:
	horizontalArcTranslate 0 130 barrage target 35 OPPONENTSIDE
    runtask TaskTranslateSpriteHorizontalArcCos barrage 0 0 0
	OPENCMD
	goto Finish

.pool
