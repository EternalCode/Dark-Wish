.macro showsprite x y graphics palette
.byte 0
.byte 0
.byte 0
.byte 0
.word \graphics
.word \palette
.endm

.macro deletesprite tag
.byte 1
.byte 0
.hword \tag
.endm
