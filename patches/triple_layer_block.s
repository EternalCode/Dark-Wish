// function redirection, tfw all 3 params are used
.org 0x0805A9B4
    push {r4, lr}
    ldr r4, =(DrawMetatile|1)
    bl linker4
    pop {r4, pc}

linker4:
    bx r4
.pool

// byte writes
.org 0x08352F0B
.byte 0x70

.org 0x08352F16
.byte 0x1C

.org 0x0809B868
.byte 0x2

.org 0x809B86E
.byte 0x2F
.byte 0xD0
