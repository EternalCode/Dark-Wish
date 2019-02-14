.thumb
.align 2

.global battle_hook
battle_hook:
    mov r0, #0x0
    ldr r3, =current_map_music_set__default_for_battle
    bl linker
    mov r0, #0x7
    ldr r3, =(0x8054E90|1)
    bl linker
    mov r0, #0x8
    ldr r3, =(0x8054E90|1)
    bl linker
    ldr r3, =BattleEngineStartup
    bl linker
    pop {pc}
    
linker:
    bx r3
    
.pool
