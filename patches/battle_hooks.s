// from berry pouch selection in battle
.org 0x08030AF8
    .word return_to_battle_bag|1
.pool

.org 0x083DB028 + (0x2C * 4) + 0x24
    .word PokeballTask|1;
.pool
