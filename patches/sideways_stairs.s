
.org 0x0806343C
    .word gFaceDirectionAnimNums
.pool

.org 0x0806344C
    .word gMoveDirectionAnimNums
.pool

.org 0x08063668
    .word gTrainerFacingDirectionMovementTypes
.pool

.org 0x08063EB8
    ldr r1, =(GetFaceDirectionMovementAction|1)
    bx r1
.pool

// redirections
.org 0x0805C104
    ldr r1, =(PlayerWalkDirection|1)
    bx r1
.pool

.org 0x0805C14C
    ldr r1, =(PlayerBikeDirection|1)
    bx r1
.pool

.org 0x0805C17C
    ldr r1, =(PlayerRunDirection|1)
    bx r1
.pool

.org 0x080BD3A0
    ldr r1, =(GetBikeCollisionType|1)
    bx r1
.pool

// repoint animation table
.org 0x08064540
    .word (gMovementActionFuncs)
.pool

.org 0x08064584
    .word (gMovementActionFuncs)
.pool

.org 0x080645B4
    .word (gMovementActionFuncs)
.pool

// hook
.org 0x0805BB5C
    ldr r0, =(change_movement|1)
    bx r0
.pool
