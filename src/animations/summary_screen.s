.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ boxSprite, 0x9006
.equ boxCursorSprite, 0x9007
.equ cursorPos, 0x9008
.equ POS_YES, 0
.equ POS_NO, 1
.equ STRING_FORGET_WHICH_MOVE, 214
.equ STRING_STOP_LEARNING_MOVE, 215
.equ STRING_CONFIRM_FORGET, 216

.global AnimSummaryLoad
AnimSummaryLoad:
	runtask TaskStatScreen 0x8000 0 0 0
	waittask TaskStatScreen
    end
.pool

.global AnimLearnMove
AnimLearnMove:
	call loadYesNoBoxes
	// load task for box input
	runtask TaskAnimYesNo boxCursorSprite POS_YES 0 0
	waittask TaskAnimYesNo
	BLOCKCMD
	hidesprite boxSprite
	hidesprite boxCursorSprite
	// process selected option
	compare 0x8000 POS_NO
	OPENCMD
	if1 0x1 goto areYouSureText

forgetMoveInterface:
	// run a task to begin forget a move sequence
	playmessage 0 0 STRING_FORGET_WHICH_MOVE 0
	waittask TaskWaitAnimMessage
	pauseframes 20
	// run task for actually entering the move forgetting
	runtask TaskLearnMove 0 0 0 0
	waittask TaskLearnMove
	copyactionpriv LASTRESULT 0
	playmessage 0 0x8000 STRING_CONFIRM_FORGET LASTRESULT
	call loadYesNoBoxes
	// load task for box input
	runtask TaskAnimYesNo boxCursorSprite POS_NO 0 0
	waittask TaskAnimYesNo
	BLOCKCMD
	hidesprite boxSprite
	hidesprite boxCursorSprite
	// process selected option
	compare 0x8000 POS_NO
	OPENCMD
	end

areYouSureText:
	// ask the player to confirm skipping learning the move
	// stop learning Movename?
	copyactionpriv LASTRESULT 0
	playmessage 0 0 STRING_STOP_LEARNING_MOVE LASTRESULT
	waittask TaskWaitAnimMessage
	BLOCKCMD
	showsprite boxSprite
	showsprite boxCursorSprite
	runtask TaskAnimYesNo boxCursorSprite POS_NO 0 0
	OPENCMD
	waittask TaskAnimYesNo
	BLOCKCMD
	hidesprite boxSprite
	hidesprite boxCursorSprite
	OPENCMD
	compare 0x8000 POS_NO
	if1 0x1 goto forgetMoveInterface
	// player doesnt want to learn move
	deletesprite boxSprite
	deletesprite boxCursorSprite
	end

loadYesNoBoxes:
	// load options box
	setvar cursorPos POS_YES
	loadspritefull yesnoBoxSprite yesnoBoxPalette yesnoBoxOam
	copyvar boxSprite LASTRESULT
	loadspritefull yesnoCursorSprite yesnoCursorPalette yesnoCursorOam
	copyvar boxCursorSprite LASTRESULT
	rendersprite boxSprite 209 90 nullrsf
	rendersprite boxCursorSprite 186 83 nullrsf
	return

.pool
