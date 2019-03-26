// from berry pouch selection in battle
.org 0x08030AF8
    .word ReturnToBattleFromBag|1
.pool

// items
.org 0x083DB028 + (0x2C * 4) + 0x24
    .word PokeballTask|1;
.pool


// opponent trainer party test hook
.org 0x080112E0
    ldr r0, =(TestBattleDataInit|1)
    bx r0
.pool
