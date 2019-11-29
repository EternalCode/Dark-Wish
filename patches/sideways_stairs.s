// redirections

.org 0x0806343C
    .word gFaceDirectionAnimNums
.pool

.org 0x0806344C
    .word gMoveDirectionAnimNums
.pool

.org 0x0806345C
    .word gMoveDirectionFastAnimNums
.pool

.org 0x0806352C
    .word gRunningDirectionAnimNums
.pool

.org 0x08063668
    .word gTrainerFacingDirectionMovementTypes
.pool

.org 0x080638F8
    .word gDirectionBlockedMetatileFuncs
.pool

.org 0x080638F4
    .word gOppositeDirectionBlockedMetatileFuncs
.pool

.org 0x0805BB1C
    ldr r1, =(CheckForPlayerAvatarCollision|1)
    bx r1
.pool

.org 0x08063EB8
    ldr r1, =(GetFaceDirectionMovementAction|1)
    bx r1
.pool

.org 0x0805C104
    ldr r1, =(PlayerWalkDirection|1)
    bx r1
.pool

.org 0x0805C17C
    ldr r1, =(PlayerRunDirection|1)
    bx r1
.pool

.org 0x0805C14C
    ldr r1, =(PlayerBikeDirection|1)
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

.pool
