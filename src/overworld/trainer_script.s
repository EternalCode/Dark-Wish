.text
.thumb
.align 2

.include "src/xse_commands.s"

.global scrPlayerFaceTrainer
scrPlayerFaceTrainer:
    compare 0x8001 0x0
    if1 0x1 look_up
    compare 0x8001 0x1
    if1 0x1 look_down
    compare 0x8001 0x2
    if1 0x1 look_right
    compare 0x8001 0x3
    if1 0x1 look_left
    goto 0x2021D18

look_down:
    applymovement 0xFF mdown
    waitmovement 0xFF
    goto 0x2021D18

look_up:
    applymovement 0xFF mup
    waitmovement 0xFF
    goto 0x2021D18

look_left:
    applymovement 0xFF mleft
    waitmovement 0xFF
    goto 0x2021D18

look_right:
    applymovement 0xFF mright
    waitmovement 0xFF
    goto 0x2021D18

mdown:
    .byte 0x0
    .byte 0xFE

mup:
    .byte 0x1
    .byte 0xFE

mleft:
    .byte 0x2
    .byte 0xFE

mright:
    .byte 0x3
    .byte 0xFE

.pool
