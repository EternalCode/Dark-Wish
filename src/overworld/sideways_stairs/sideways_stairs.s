@ --- Change these:
.equ behaviour_0,   0xB0     @ First of six contiguous, free behaviour bytes
@ ---

.equ behaviour_1,   (behaviour_0 + 1)
.equ behaviour_2,   (behaviour_1 + 1)
.equ behaviour_3,   (behaviour_2 + 1)
.equ behaviour_4,   (behaviour_3 + 1)
.equ behaviour_5,   (behaviour_4 + 1)

@CheckForPlayerAvatarCollision
.equ change_movement_return,                  0x0805BB66+ 1

@PlayerWalkDirection
.equ walk_return,                               0x0805C10E+ 1

@sub_805C14C
.equ run_return,                                0x0805C156+ 1

.equ npc_set_direction,                         0x0805FBDC+ 1
.equ sub_8064008,                               0x08064008+ 1
.equ npc_apply_direction_return,                0x080646AC+ 1
.equ an_run_any_return,                         0x08064728+ 1
.equ npc_obj_ministep_stop_on_arrival_return,   0x08064794+ 1
.equ sub_80649C8_return,                        0x080649D0+ 1
.equ npc_08064C04_and_modify_priv1_return,      0x08064C10+ 1
.equ an_pulse_dn_2_return,                      0x08064D64+ 1
.equ sub_8065EF0_return,                        0x08065F18+ 1
.equ sub_8065F60_return,                        0x08065F6E+ 1
.equ sub_8065F8C_return,                        0x08065F98+ 1
.equ sub_8065FE4_return,                        0x08065FEE+ 1
.equ an_stop,                                   0x08067934+ 1
.equ little_step,                               0x08068A8C+ 1
.equ obj_npc_ministep_return,                   0x08068B8C+ 1
.equ sub_8068C18_return_0,                      0x08068C30+ 1
.equ sub_8068C18_return_1,                      0x08068C3E+ 1
.equ sub_8068CB4_return_0,                      0x08068CDE+ 1
.equ sub_8068CB4_return_1,                      0x08068CE8+ 1
.equ off_83A6884,                               0x083A6884
.equ stepspeeds,                                0x083A719C
.equ stepspeed_seq_length,                      0x083A71B0

.equ npc_tile_to,       0x1E
.equ walkrun_npcid,     0x05


.thumb
.align 2
.global change_movement
change_movement:
    mov r0, r6
    mov r1, r5
    bl SidewaysStairsUpdateToCoords
    add r1, sp, #4
    mov r2, r4
    ldr r3, =(MoveCoords)
    bl call_via_r3
    ldr r3, =(change_movement_return)

call_via_r3:
    bx r3

.pool

.align 4
.global an_table
an_table:
.word 0x083A6864, 0x083A686C, 0x083A6874, 0x083A687C, 0x083A6A30, 0x083A6A38, 0x083A6A40, 0x083A6A48, 0x083A68C8, 0x083A68D4, 0x083A68E0, 0x083A68EC, 0x083A6904, 0x083A68F8, 0x083A6910, 0x083A691C, 0x083A6928, 0x083A6934, 0x083A6940, 0x083A694C, 0x083A6964, 0x083A6970, 0x083A697C, 0x083A6988, 0x083A6994, 0x083A69A0, 0x083A69AC, 0x083A69B8, 0x083A69C4, 0x083A69D0, 0x083A69DC, 0x083A69E8, 0x083A69F4, 0x083A6A50, 0x083A6A5C, 0x083A6A68, 0x083A6A74, 0x083A6A80, 0x083A6A8C, 0x083A6A98, 0x083A6AA4, 0x083A6AB0, 0x083A6ABC, 0x083A6AC8, 0x083A6AD4, 0x083A6AE0, 0x083A6AEC, 0x083A6AF8, 0x083A6B04, 0x083A6B10, 0x083A6B1C, 0x083A6B28, 0x083A6B34, 0x083A6B40, 0x083A6B4C, 0x083A6B58, 0x083A6B64, 0x083A6B70, 0x083A6B7C, 0x083A6B88, 0x083A6B94, 0x083A6BA0, 0x083A6BAC, 0x083A6BB8, 0x083A6BC4, 0x083A6BD0, 0x083A6BDC, 0x083A6BE8, 0x083A6BF4, 0x083A6C00, 0x083A6C0C, 0x083A6C18, 0x083A6C24, 0x083A6C30, 0x083A6C6C, 0x083A6C74, 0x083A6C7C, 0x083A6C84, 0x083A6C8C, 0x083A6C98, 0x083A6CA4, 0x083A6CB0, 0x083A6CBC, 0x083A6CC8, 0x083A6CD4, 0x083A6CE0, 0x083A6CEC, 0x083A6CF8, 0x083A6D04, 0x083A6D10, 0x083A6D1C, 0x083A6D24, 0x083A6D30, 0x083A6D38, 0x083A6D40, 0x083A6D48, 0x083A6D50, 0x083A6D58, 0x083A6D60, 0x083A6D68, 0x083A6D70, 0x083A6D78, 0x083A6D80, 0x083A6D88, 0x083A6D94, 0x083A6DA4, 0x083A6DB4, 0x083A6DBC, 0x083A6DC4, 0x083A6DCC, 0x083A6DD4, 0x083A6DE0, 0x083A6DEC, 0x083A6DF4, 0x083A6DFC, 0x083A6E04, 0x083A6E0C, 0x083A6E18, 0x083A6E24, 0x083A6E30, 0x083A6E3C, 0x083A6E48, 0x083A6E54, 0x083A6E60, 0x083A6E9C, 0x083A6EA8, 0x083A6EB4, 0x083A6EC0, 0x083A6ECC, 0x083A6ED8, 0x083A6EE4, 0x083A6EF0, 0x083A6EFC, 0x083A6F08, 0x083A6F14, 0x083A6F20, 0x083A6F2C, 0x083A6F38, 0x083A6F44, 0x083A6F50, 0x083A6F5C, 0x083A6F68, 0x083A6F74, 0x083A6F80, 0x083A6F8C, 0x083A6F98, 0x083A6FA4, 0x083A6FB0, 0x083A6FBC, 0x083A6FC8, 0x083A6FD4, 0x083A6FE0, 0x083A6FEC, 0x083A6FF4, 0x083A6FFC, 0x083A6898, 0x083A68A4, 0x083A68B0, 0x083A68BC, 0x083A7004, 0x083A6A00, 0x083A6A0C, 0x083A6A18, 0x083A6A24, 0x083A700C, 0x083A7018, 0x083A6C3C, 0x083A6C48, 0x083A6C54, 0x083A6C60, (entry_0), (entry_1), (entry_2), (entry_3), (entry_4), (entry_5), (entry_6), (entry_7), (entry_8), (entry_9), (entry_10), (entry_11)

.global entry_0
    entry_0:  .word (routine_0 + 1), (routine_1 + 1), an_stop

.global entry_1
    entry_1:  .word (routine_2 + 1), (routine_1 + 1), an_stop
.global entry_2
    entry_2:  .word (routine_3 + 1), (routine_4 + 1), an_stop
.global entry_3
    entry_3:  .word (routine_5 + 1), (routine_4 + 1), an_stop
.global entry_4
    entry_4:  .word (routine_6 + 1), (routine_7 + 1), an_stop
.global entry_5
    entry_5:  .word (routine_8 + 1), (routine_7 + 1), an_stop
.global entry_6
    entry_6:  .word (routine_9 + 1), (routine_10 + 1), an_stop
.global entry_7
    entry_7:  .word (routine_11 + 1), (routine_10 + 1), an_stop
.global entry_8
    entry_8:  .word (routine_12 + 1), (routine_13 + 1), an_stop
.global entry_9
    entry_9:  .word (routine_14 + 1), (routine_13 + 1), an_stop
.global entry_10
    entry_10: .word (routine_15 + 1), (routine_16 + 1), an_stop
.global entry_11
    entry_11: .word (routine_17 + 1), (routine_16 + 1), an_stop

.align 2
routine_0:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #0
    bl subroutine_0
    mov r0, r4
    mov r1, r5
    bl routine_1
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_2:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #0
    bl subroutine_0
    mov r0, r4
    mov r1, r5
    bl routine_1
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
subroutine_0:
    push {r4-r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x14
    mov r5, r0
    mov r8, r1
    mov r4, r3
    lsl r2, r2, #24
    lsr r2, r2, #24
    lsl r4, r4, #24
    lsr r4, r4, #24
    mov r1, sp
    ldr r0, =(off_83A6884)
    ldmia r0!, {r3, r6, r7}
    stmia r1!, {r3, r6, r7}
    ldmia r0!, {r3, r6}
    stmia r1!, {r3, r6}
    mov r0, r5
    mov r1, r8
    mov r3, r4
    bl subroutine_1
    ldr r7, =(an_run_any_return)
    bx r7

.align 2
subroutine_1:
    push {r4-r6, lr}
    mov r6, r9
    mov r5, r8
    push {r5, r6}
    sub sp, #4
    mov r8, r0
    mov r9, r1
    mov r4, r2
    mov r6, r3
    lsl r4, r4, #24
    lsr r4, r4, #24
    lsl r6, r6, #24
    lsr r6, r6, #24
    ldrh r1, [r0, #0x10]
    mov r0, sp
    strh r1, [r0]
    mov r1, r8
    ldrh r0, [r1, #0x12]
    mov r5, sp
    add r5, #2
    strh r0, [r5]
    mov r0, r8
    mov r1, r4
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    sub r2, r4, #1
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(npc_apply_direction_return)
    bx r1

.align 2
routine_1:
    push {r4, lr}
    mov r4, r1
    bl subroutine_2
    ldr r1, =(sub_80649C8_return)
    bx r1

.align 2
subroutine_2:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_3
    ldr r1, =(npc_08064C04_and_modify_priv1_return)
    bx r1

.align 2
subroutine_3:
    push {r4, lr}
    mov r4, r0
    ldrh r0, [r4, #0x36]
    add r0, #1
    strh r0, [r4, #0x36]
    lsl r0, r0, #16
    asr r0, r0, #16
    cmp r0, #2
    bgt subroutine_3_r0_gt_2
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    sub r1, #1
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r0, =(sub_8068C18_return_0)
    bx r0

.align 2
subroutine_3_r0_gt_2:
    ldr r1, =(sub_8068C18_return_1)
    bx r1

.align 2
.pool

.align 2
routine_3:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #0
    bl subroutine_4
    mov r0, r4
    mov r1, r5
    bl routine_4
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_5:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #0
    bl subroutine_4
    mov r0, r4
    mov r1, r5
    bl routine_4
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
subroutine_4:
    push {r4-r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x14
    mov r5, r0
    mov r8, r1
    mov r4, r3
    lsl r2, r2, #24
    lsr r2, r2, #24
    lsl r4, r4, #24
    lsr r4, r4, #24
    mov r1, sp
    ldr r0, =(off_83A6884)
    ldmia r0!, {r3, r6, r7}
    stmia r1!, {r3, r6, r7}
    ldmia r0!, {r3, r6}
    stmia r1!, {r3, r6}
    mov r0, r5
    mov r1, r8
    mov r3, r4
    bl subroutine_5
    ldr r7, =(an_run_any_return)
    bx r7

.align 2
subroutine_5:
    push {r4-r6, lr}
    mov r6, r9
    mov r5, r8
    push {r5, r6}
    sub sp, #4
    mov r8, r0
    mov r9, r1
    mov r4, r2
    mov r6, r3
    lsl r4, r4, #24
    lsr r4, r4, #24
    lsl r6, r6, #24
    lsr r6, r6, #24
    ldrh r1, [r0, #0x10]
    mov r0, sp
    strh r1, [r0]
    mov r1, r8
    ldrh r0, [r1, #0x12]
    mov r5, sp
    add r5, #2
    strh r0, [r5]
    mov r0, r8
    mov r1, r4
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    add r2, r4, #3
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(npc_apply_direction_return)
    bx r1

.align 2
routine_4:
    push {r4, lr}
    mov r4, r1
    bl subroutine_6
    ldr r1, =(sub_80649C8_return)
    bx r1

.align 2
subroutine_6:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_7
    ldr r1, =(npc_08064C04_and_modify_priv1_return)
    bx r1

.align 2
subroutine_7:
    push {r4, lr}
    mov r4, r0
    ldrh r0, [r4, #0x36]
    add r0, #1
    strh r0, [r4, #0x36]
    lsl r0, r0, #16
    asr r0, r0, #16
    cmp r0, #2
    bgt subroutine_7_r0_gt_2
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    add r1, #3
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r0, =(sub_8068C18_return_0)
    bx r0

.align 2
subroutine_7_r0_gt_2:
    ldr r1, =(sub_8068C18_return_1)
    bx r1

.align 2
.pool

.align 2
routine_6:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #0
    bl subroutine_23
    mov r0, r4
    mov r1, r5
    bl routine_7
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_8:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #0
    bl subroutine_23
    mov r0, r4
    mov r1, r5
    bl routine_7
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
subroutine_23:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    lsl r2, r2, #24
    lsr r2, r2, #24
    bl subroutine_8
    ldr r1, =(sub_8065F60_return)
    bx r1

.align 2
subroutine_8:
    push {r4-r6, lr}
    mov r6, r8
    push {r6}
    sub sp, #4
    mov r6, r0
    mov r8, r1
    lsl r5, r2, #24
    lsr r5, r5, #24
    ldrh r1, [r6, #0x10]
    mov r0, sp
    strh r1, [r0]
    ldrh r0, [r6, #0x12]
    mov r4, sp
    add r4, #2
    strh r0, [r4]
    mov r0, r6
    mov r1, r5
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    sub r2, r5, #1
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(sub_8065EF0_return)
    bx r1

.align 2
routine_7:
    push {r4, lr}
    mov r4, r1
    bl subroutine_9
    ldr r1, =(sub_8065FE4_return)
    bx r1

.align 2
subroutine_9:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_10
    ldr r1, =(sub_8065F8C_return)
    bx r1

.align 2
subroutine_10:
    push {r4, lr}
    mov r4, r0
    ldrh r0, [r4, #0x36]
    add r0, #1
    strh r0, [r4, #0x36]
    mov r1, #1
    and r0, r1
    cmp r0, #0
    beq subroutine_10_r0_eq_0
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    sub r1, #1
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    mov r0, r4
    ldr r3, =(little_step)
    bl call_via_r3
    ldrh r0, [r4, #0x38]
    add r0, #1
    ldr r3, =(sub_8068CB4_return_1)
    bx r3

.align 2
subroutine_10_r0_eq_0:
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #0x18
    lsr r1, r1, #0x18
    ldr r0, =(byte_list)
    sub r1, #1
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r3, =(sub_8068CB4_return_0)
    bx r3

.align 2
.pool

.align 2
routine_9:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #0
    bl subroutine_11
    mov r0, r4
    mov r1, r5
    bl routine_10
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_11:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #0
    bl subroutine_11
    mov r0, r4
    mov r1, r5
    bl routine_10
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_10:
    push {r4, lr}
    mov r4, r1
    bl subroutine_13
    ldr r1, =(sub_8065FE4_return)
    bx r1

.align 2
subroutine_11:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    lsl r2, r2, #24
    lsr r2, r2, #24
    bl subroutine_12
    ldr r1, =(sub_8065F60_return)
    bx r1

.align 2
subroutine_12:
    push {r4-r6, lr}
    mov r6, r8
    push {r6}
    sub sp, #4
    mov r6, r0
    mov r8, r1
    lsl r5, r2, #24
    lsr r5, r5, #24
    ldrh r1, [r6, #0x10]
    mov r0, sp
    strh r1, [r0]
    ldrh r0, [r6, #0x12]
    mov r4, sp
    add r4, #2
    strh r0, [r4]
    mov r0, r6
    mov r1, r5
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    add r2, r5, #3
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(sub_8065EF0_return)
    bx r1

.align 2
subroutine_13:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_14
    ldr r1, =(sub_8065F8C_return)
    bx r1

.align 2
subroutine_14:
    push {r4, lr}
    mov r4, r0
    ldrh r0, [r4, #0x36]
    add r0, #1
    strh r0, [r4, #0x36]
    mov r1, #1
    and r0, r1
    cmp r0, #0
    beq subroutine_14_r0_eq_0
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    add r1, #3
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    mov r0, r4
    ldr r3, =(little_step)
    bl call_via_r3
    ldrh r0, [r4, #0x38]
    add r0, #1
    ldr r3, =(sub_8068CB4_return_1)
    bx r3

.align 2
subroutine_14_r0_eq_0:
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #0x18
    lsr r1, r1, #0x18
    ldr r0, =(byte_list)
    add r1, #3
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r3, =(sub_8068CB4_return_0)
    bx r3

.align 2
.pool

.align 2
routine_12:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #1
    bl subroutine_15
    mov r0, r4
    mov r1, r5
    bl routine_13
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_14:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #1
    bl subroutine_15
    mov r0, r4
    mov r1, r5
    bl routine_13
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
subroutine_15:
    push {r4-r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x14
    mov r5, r0
    mov r8, r1
    mov r4, r3
    lsl r2, r2, #24
    lsr r2, r2, #24
    lsl r4, r4, #24
    lsr r4, r4, #24
    mov r1, sp
    ldr r0, =(off_83A6884)
    ldmia r0!, {r3, r6, r7}
    stmia r1!, {r3, r6, r7}
    ldmia r0!, {r3, r6}
    stmia r1!, {r3, r6}
    mov r0, r5
    mov r1, r8
    mov r3, r4
    bl subroutine_16
    ldr r7, =(an_run_any_return)
    bx r7

.align 2
subroutine_16:
    push {r4-r6, lr}
    mov r6, r8
    mov r5, r9
    push {r5, r6}
    sub sp, #4
    mov r8, r0
    mov r9, r1
    mov r4, r2
    mov r6, r3
    lsl r4, r4, #24
    lsr r4, r4, #24
    lsl r6, r6, #24
    lsr r6, r6, #24
    ldrh r1, [r0, #0x10]
    mov r0, sp
    strh r1, [r0]
    mov r1, r8
    ldrh r0, [r1, #0x12]
    mov r5, sp
    add r5, #2
    strh r0, [r5]
    mov r0, r8
    mov r1, r4
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    sub r2, r4, #1
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(npc_apply_direction_return)
    bx r1

.align 2
routine_13:
    push {r4, lr}
    mov r4, r1
    bl subroutine_17
    ldr r1, =(an_pulse_dn_2_return)
    bx r1

.align 2
subroutine_17:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_18
    ldr r1, =(npc_obj_ministep_stop_on_arrival_return)
    bx r1

.align 2
subroutine_18:
    push {r4, r5, lr}
    mov r4, r0
    ldr r5, =(stepspeed_seq_length)
    ldrh r2, [r4, #0x36]
    lsl r0, r2, #1
    add r0, r0, r5
    ldrh r1, [r4, #0x38]
    ldrh r0, [r0]
    cmp r1, r0
    bge subroutine_18_r1_ge_r0
    ldr r1, =(stepspeeds)
    lsl r0, r2, #2
    add r0, r0, r1
    ldrh r2, [r4, #0x38]
    ldr r0, [r0]
    lsl r2, r2, #2
    add r2, r2, r0
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    sub r1, #1
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r3, [r2]
    mov r0, r4
    bl call_via_r3
    ldr r0, =(obj_npc_ministep_return)
    bx r0

.align 2
subroutine_18_r1_ge_r0:
    mov r0, #0
    pop {r4, r5, pc}
.pool

.align 2
routine_15:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #3
    mov r3, #1
    bl subroutine_19
    mov r0, r4
    mov r1, r5
    bl routine_16
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_17:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r2, #4
    mov r3, #1
    bl subroutine_19
    mov r0, r4
    mov r1, r5
    bl routine_16
    lsl r0, r0, #24
    lsr r0, r0, #24
    pop {r4, r5, pc}

.align 2
routine_16:
    push {r4, lr}
    mov r4, r1
    bl subroutine_20
    ldr r1, =(an_pulse_dn_2_return)
    bx r1

.align 2
subroutine_20:
    push {r4, r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, r5
    bl subroutine_21
    ldr r1, =(npc_obj_ministep_stop_on_arrival_return)
    bx r1

.align 2
subroutine_21:
    push {r4, r5, lr}
    mov r4, r0
    ldr r5, =(stepspeed_seq_length)
    ldrh r2, [r4, #0x36]
    lsl r0, r2, #1
    add r0, r0, r5
    ldrh r1, [r4, #0x38]
    ldrh r0, [r0]
    cmp r1, r0
    bge subroutine_21_r1_ge_r0
    ldr r1, =(stepspeeds)
    lsl r0, r2, #2
    add r0, r0, r1
    ldrh r2, [r4, #0x38]
    ldr r0, [r0]
    lsl r2, r2, #2
    add r2, r2, r0
    ldrh r1, [r4, #0x34]
    lsl r1, r1, #24
    lsr r1, r1, #24
    ldr r0, =(byte_list)
    add r1, #3
    lsl r1, r1, #1
    ldsh r1, [r0, r1]
    ldr r3, [r2]
    mov r0, r4
    bl call_via_r3
    ldr r0, =(obj_npc_ministep_return)
    bx r0

.align 2
subroutine_21_r1_ge_r0:
    mov r0, #0
    pop {r4, r5, pc}

.align 2
subroutine_19:
    push {r4-r7, lr}
    mov r7, r8
    push {r7}
    sub sp, #0x14
    mov r5, r0
    mov r8, r1
    mov r4, r3
    lsl r2, r2, #24
    lsr r2, r2, #24
    lsl r4, r4, #24
    lsr r4, r4, #24
    mov r1, sp
    ldr r0, =(off_83A6884)
    ldmia r0!, {r3, r6, r7}
    stmia r1!, {r3, r6, r7}
    ldmia r0!, {r3, r6}
    stmia r1!, {r3, r6}
    mov r0, r5
    mov r1, r8
    mov r3, r4
    bl subroutine_22
    ldr r7, =(an_run_any_return)
    bx r7

.align 2
subroutine_22:
    push {r4-r6, lr}
    mov r6, r8
    mov r5, r9
    push {r5, r6}
    sub sp, #4
    mov r8, r0
    mov r9, r1
    mov r4, r2
    mov r6, r3
    lsl r4, r4, #24
    lsr r4, r4, #24
    lsl r6, r6, #24
    lsr r6, r6, #24
    ldrh r1, [r0, #0x10]
    mov r0, sp
    strh r1, [r0]
    mov r1, r8
    ldrh r0, [r1, #0x12]
    mov r5, sp
    add r5, #2
    strh r0, [r5]
    mov r0, r8
    mov r1, r4
    ldr r3, =(npc_set_direction)
    bl call_via_r3
    ldr r1, =(byte_list)
    add r2, r4, #3
    lsl r2, r2, #1
    ldsh r0, [r1, r2]
    ldr r1, =(npc_apply_direction_return)
    bx r1

.align 2
byte_list:
    .short 5, 7, 5, 6, 6, 8, 7, 8

.pool
