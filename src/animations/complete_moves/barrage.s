.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ barrage, 0x9006

.global BarrageAnimation
BarrageAnimation:
	fastsetbattlers
	loadspritefull barrageSprite barragePalette barrageOam
	copyvar barrage LASTRESULT
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
    quakebg 1 0 4 5 2 true
	quakebg 3 0 4 5 2 true
	OPENCMD
	pauseframes 10
	deletesprite barrage
	spritebgclear target
    end

BarrageOpp:
	horizontalArcTranslate 0 130 barrage target 35 OPPONENTSIDE
    runtask TaskTranslateSpriteHorizontalArcCos barrage 0 0 0
	OPENCMD
	goto Finish

.pool
