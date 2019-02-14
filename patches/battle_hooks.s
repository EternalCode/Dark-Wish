// bag inbattle to return hook
.org 0x08030AF8
    .word return_to_battle_bag|1
.pool


.org 0x0807F6C4
    .word Task_BattleStart|1
.pool
