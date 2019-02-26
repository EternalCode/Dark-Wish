.text
.thumb
.align 2
.include "src/animation_cmds.s"

.global AnimSummaryLoad
AnimSummaryLoad:
	runtask TaskStatScreen 0x8000 0 0 0
	waittask TaskStatScreen
    end
.pool


AnimLearnMove:
	runtask TaskLearnMove 0x8000 0 0 0
	waittask TaskLearnMove
	end
.pool
