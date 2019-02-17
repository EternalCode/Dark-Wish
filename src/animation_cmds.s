@Loads the sprite Id into var_800D
.macro loadsprite graphics palette oam
.byte 0
.byte 0
.byte 0
.byte 0
.word \graphics
.word \palette
.word \oam
.endm

@pass var which holds your sprite Id
.macro deletesprite var
.byte 1
.byte 0
.hword \var
.endm

.macro rendersprite var x y anim
.byte 2
.byte 0
.hword \var
.hword \x
.hword \y
.byte 0
.byte 0
.word \anim
.endm

.macro copyvar dst src
.byte 3
.byte 0
.byte 0
.byte 0
.hword \dst
.hword \src
.endm

.macro setvar var value
.byte 4
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro addvar var value
.byte 5
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro subvar var value
.byte 6
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro mulvar var value
.byte 7
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro divvar var value
.byte 8
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm

.macro gotovar var value
.byte 9
.byte 0
.byte 0
.byte 0
.hword \var
.hword \value
.endm
