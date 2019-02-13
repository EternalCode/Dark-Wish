// Recognize new moves on pkmn creation
.org 0x0803E9E0
    ldr r1, =(FillPokemonMoves|1)
    bx r1
.pool

.org 0x0803EA88
    ldr r1, =(FillPokemonMoves|1)
    bx r1
.pool

// repoint move names table
.org 0x08000148
    .word gMoveNames
.pool

.org 0x080308A4
    .word gMoveNames
.pool

.org 0x0804EF84
    .word gMoveNames
.pool

.org 0x0806BE8C
    .word gMoveNames
.pool

.org 0x0809B524
    .word gMoveNames
.pool

.org 0x080BD830
    .word gMoveNames
.pool

.org 0x080BFAA4
    .word gMoveNames
.pool

.org 0x080CC914
    .word gMoveNames
.pool

.org 0x080D764C
    .word gMoveNames
.pool

.org 0x080D7EE0
    .word gMoveNames
.pool

.org 0x080D8500
    .word gMoveNames
.pool

.org 0x080E4E58
    .word gMoveNames
.pool

.org 0x080E51F0
    .word gMoveNames
.pool

.org 0x0810D9C0
    .word gMoveNames
.pool

.org 0x081140F0
    .word gMoveNames
.pool

.org 0x0811C5A8
    .word gMoveNames
.pool

.org 0x0811C6E4
    .word gMoveNames
.pool

.org 0x081256BC
    .word gMoveNames
.pool

.org 0x08125948
    .word gMoveNames
.pool

.org 0x08125A2C
    .word gMoveNames
.pool

.org 0x08125BE4
    .word gMoveNames
.pool

.org 0x08125CE0
    .word gMoveNames
.pool

.org 0x08125FF8
    .word gMoveNames
.pool

.org 0x08125CE0
    .word gMoveNames
.pool

.org 0x0812606C
    .word gMoveNames
.pool

.org 0x08126128
    .word gMoveNames
.pool

.org 0x081261FC
    .word gMoveNames
.pool

.org 0x0812627C
    .word gMoveNames
.pool

.org 0x081267F0
    .word gMoveNames
.pool

.org 0x08126880
    .word gMoveNames
.pool

.org 0x08126E64
    .word gMoveNames
.pool

.org 0x08131E14
    .word gMoveNames
.pool

.org 0x0813695C
    .word gMoveNames
.pool
