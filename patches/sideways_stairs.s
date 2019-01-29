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
    .word (an_table)
.pool

.org 0x08064584
    .word (an_table)
.pool

.org 0x080645B4
    .word (an_table)
.pool

// hook
.org 0x0805BB5C
    ldr r0, =(change_movement|1)
    bx r0
.pool
