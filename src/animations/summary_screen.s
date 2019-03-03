.text
.thumb
.align 2
.include "src/animation_cmds.s"

.equ boxSprite, 0x9006
.equ boxCursorSprite, 0x9007
.equ cursorPos, 0x9008
.equ selectedMove, 0x9009
.equ POS_YES, 0
.equ POS_NO, 1
.equ STRING_FORGET_WHICH_MOVE, 214
.equ STRING_STOP_LEARNING_MOVE, 215
.equ STRING_CONFIRM_FORGET, 216
.equ STRING_FORGOT_SELECTED_MOVE, 217

.global AnimSummaryLoad
AnimSummaryLoad:
	runtask TaskStatScreen 0x8000 0 0 0
	waittask TaskStatScreen
    end
.pool

.global AnimLearnMove
AnimLearnMove:
	// Make it forget another move ?
	setvar cursorPos POS_YES
	call loadYesNoBoxes
	BLOCKCMD
	hidesprite boxSprite
	hidesprite boxCursorSprite
	compare 0x8000 POS_NO
	OPENCMD
	if1 0x1 goto stopLearningMoveConfirm

forgetMoveInterface:
	// Forget which move?
	playmessage 0 0 STRING_FORGET_WHICH_MOVE 0
	waittask TaskWaitAnimMessage
	pauseframes 20

	// Summary screen for move selection
	runtask TaskLearnMove 0 0 0 0
	waittask TaskLearnMove
	copyvar selectedMove 0x8000

	// Forget SelectedMove to learn Move
	copyactionpriv LASTRESULT 0
	playmessage 0 selectedMove STRING_CONFIRM_FORGET LASTRESULT

	setvar cursorPos POS_NO
	call loadYesNoBoxes
	BLOCKCMD
	hidesprite boxSprite
	hidesprite boxCursorSprite
	compare 0x8000 POS_NO
	OPENCMD
	if1 0x1 goto stopLearningMoveConfirm
	// Mon forgot SelectedMove, & learned Move
	copyactionpriv LASTRESULT 0
	copyactionpriv 0x8000 1
	playmessage 0x8000 selectedMove STRING_FORGOT_SELECTED_MOVE LASTRESULT
	runtask TaskSetSlotMove selectedMove 0 0 0
	waittask TaskWaitAnimMessage
	waittask TaskSetSlotMove
	end

stopLearningMoveConfirm:
	// stop learning Movename?
	copyactionpriv LASTRESULT 0
	playmessage 0 0 STRING_STOP_LEARNING_MOVE LASTRESULT
	waittask TaskWaitAnimMessage
	runtask TaskAnimYesNo boxCursorSprite POS_NO 0 0
	BLOCKCMD
	showsprite boxSprite
	showsprite boxCursorSprite
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
	BLOCKCMD
	loadspritefull yesnoBoxSprite yesnoBoxPalette yesnoBoxOam
	copyvar boxSprite LASTRESULT
	loadspritefull yesnoCursorSprite yesnoCursorPalette yesnoCursorOam
	copyvar boxCursorSprite LASTRESULT
	rendersprite boxSprite 209 90 nullrsf
	compare cursorPos POS_NO
	if1 0x1 goto cursorNoPosition
	rendersprite boxCursorSprite 186 83 nullrsf
	runtask TaskAnimYesNo boxCursorSprite POS_YES 0 0
	waittask TaskAnimYesNo
	OPENCMD
	return


cursorNoPosition:
	rendersprite boxCursorSprite 186 97 nullrsf
	runtask TaskAnimYesNo boxCursorSprite POS_NO 0 0
	waittask TaskAnimYesNo
	OPENCMD
	return

.pool
