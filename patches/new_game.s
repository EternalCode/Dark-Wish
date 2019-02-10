.org 0x08110F14
    push {lr}
    ldr r0, =(ContinueGame|1)
    bl linkrzero
    pop{pc}

linkrzero:
    bx r0

.pool
