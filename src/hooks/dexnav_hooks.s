@--------------------------------------------
@ The vanilla startmenu enters a fadescreen on certain options
@ This hook adds an exception to that fade for Poketools
.thumb
.align 2
.global add_exception_poketools

add_exception_poketools:
    cmp r1, r0
    beq end
    ldr r0, =(sm_poketools)
    cmp r1, r0
    beq end
    ldr r0, =(0x080CCB68|1)
    bl linker
    ldr r0, =(0x0806F3B0|1)

linker:
    bx r0

end:
    pop {pc}
