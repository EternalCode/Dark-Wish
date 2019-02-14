// Hook for hidden ability read position in pokemon_getattr
.org 0x0803FD58
   ldr r5, =(get_attr_ability_hook|1);
   bx r5
.pool

// Hook the battle malloc
.org 0x08040938
   ldrb r0, [r4]
   lsl r0, r0, #0x6
   mov r1, r7
   orr r0, r1
   strb r0, [r7, #0x1D]
   mov r8, r8
   mov r8, r8

// b_copy_species_ability hook
.org 0x08040D38
   ldr r2,=(b_copy_species_ability_new_hook|1)
   bx r2
.pool

// Pick up , atkE5_pickupitemcalculation
.org 0x0802CE7E
   ldr r1, =(atkE5_pickupitemcalculation_hook|1)
   bx r1
.pool

// ai_switch_blocking_ability hook
.org 0x08039548
   ldr r1, =(ai_switch_blocking_ability_hook|1)
   bx r1
.pool

// BC read battle data bit shift undo
.org 0x08013152
   mov r8, r8

// abilities name
	.org 0x80001C0
	.word ability_names

	.org 0x80D8004
	.word ability_names

	.org 0x80D8624
	.word ability_names

	.org 0x81367A0
	.word ability_names

// abilities description
	.org 0x80001C4
	.word ability_descriptions

	.org 0x81367A8
	.word ability_descriptions
