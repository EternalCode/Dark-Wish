// nop old Base stats table
.org 0x08254784
    .fill 11536, 0xFF

// repoint Base stat table
.org 0x080001BC
	.word gBaseStats
	.pool

.org 0x08012754
	.word gBaseStats
	.pool

.org 0x08012FA8
	.word gBaseStats
	.pool

.org 0x08013230
	.word gBaseStats
	.pool

.org 0x08016A60
	.word gBaseStats
	.pool

.org 0x0801F008
	.word gBaseStats
	.pool

.org 0x08021C28
	.word gBaseStats
	.pool

.org 0x080240B4
	.word gBaseStats
	.pool

.org 0x0802BABC
	.word gBaseStats
	.pool

.org 0x0802CE90
	.word gBaseStats
	.pool

.org 0x0802D53C
	.word gBaseStats
	.pool

.org 0x0802FFBC
	.word gBaseStats
	.pool

.org 0x080300E8
	.word gBaseStats
	.pool

.org 0x080301F8
	.word gBaseStats
	.pool

.org 0x08039558
	.word gBaseStats
	.pool

.org 0x080399BC
	.word gBaseStats
	.pool

.org 0x08039A68
	.word gBaseStats
	.pool

.org 0x08039FE8
	.word gBaseStats
	.pool

.org 0x0803DCC4
	.word gBaseStats
	.pool

.org 0x0803DD94
	.word gBaseStats
	.pool

.org 0x0803E734
	.word gBaseStats
	.pool

.org 0x0803E82C
	.word gBaseStats
	.pool

.org 0x0803E898
	.word gBaseStats
	.pool

.org 0x0803F780
	.word gBaseStats
	.pool

.org 0x0803F7C8
	.word gBaseStats
	.pool

.org 0x08040D58
	.word gBaseStats
	.pool

.org 0x08040D78
	.word gBaseStats
	.pool

.org 0x080413B8
	.word gBaseStats
	.pool

.org 0x080419A0
	.word gBaseStats
	.pool

.org 0x08043914
	.word gBaseStats
	.pool

.org 0x08043928
	.word gBaseStats
	.pool

.org 0x0804393C
	.word gBaseStats
	.pool

.org 0x08043950
	.word gBaseStats
	.pool

.org 0x08043964
	.word gBaseStats
	.pool

.org 0x080439A4
	.word gBaseStats
	.pool

.org 0x08043B8C
	.word gBaseStats
	.pool

.org 0x08043C10
	.word gBaseStats
	.pool

.org 0x08044208
	.word gBaseStats
	.pool

.org 0x08044458
	.word gBaseStats
	.pool

.org 0x08046600
	.word gBaseStats
	.pool

.org 0x08049F4C
	.word gBaseStats
	.pool

.org 0x0804FC88
	.word gBaseStats
	.pool

.org 0x080C84E0
	.word gBaseStats
	.pool

.org 0x080CA850
	.word gBaseStats
	.pool

.org 0x080E7F14
	.word gBaseStats
	.pool

.org 0x080E8040
	.word gBaseStats
	.pool

.org 0x080E8150
	.word gBaseStats
	.pool

.org 0x08103AC4
	.word gBaseStats
	.pool

.org 0x081066B4
	.word gBaseStats
	.pool

.org 0x0811AE48
	.word gBaseStats
	.pool

.org 0x081361F8
	.word gBaseStats
	.pool

.org 0x08136794
	.word gBaseStats
	.pool

.org 0x0813AAE0
	.word gBaseStats
	.pool

.org 0x081569EC
	.word gBaseStats
	.pool

.org 0x08156B18
	.word gBaseStats
	.pool

.org 0x08156C28
    .word gBaseStats
    .pool


// Pokemon names table nop
.org 0x08245EE0
    .fill 0x11B4, 0xFF

// Pokemon names table repointing
.org 0x08000144
    .word gSpeciesNames
    .pool

.org 0x08011450
    .word gSpeciesNames
    .pool

.org 0x0801150C
    .word gSpeciesNames
    .pool

.org 0x080115A4
    .word gSpeciesNames
    .pool

.org 0x080116BC
    .word gSpeciesNames
    .pool

.org 0x08034D80
    .word gSpeciesNames
    .pool

.org 0x08040FEC
    .word gSpeciesNames
    .pool

.org 0x080435DC
    .word gSpeciesNames
    .pool

.org 0x08049768
    .word gSpeciesNames
    .pool

.org 0x08053ADC
    .word gSpeciesNames
    .pool

.org 0x08053B44
    .word gSpeciesNames
    .pool

.org 0x0806BCC4
    .word gSpeciesNames
    .pool

.org 0x0806BD10
    .word gSpeciesNames
    .pool

.org 0x08093E8C
    .word gSpeciesNames
    .pool

.org 0x0809F560
    .word gSpeciesNames
    .pool

.org 0x080A0900
    .word gSpeciesNames
    .pool

.org 0x080BD820
    .word gSpeciesNames
    .pool

.org 0x080CB120
    .word gSpeciesNames
    .pool

.org 0x080CBEAC
    .word gSpeciesNames
    .pool

.org 0x080CE0B4
    .word gSpeciesNames
    .pool

.org 0x080CE6B8
    .word gSpeciesNames
    .pool

.org 0x080CE8D0
    .word gSpeciesNames
    .pool

.org 0x080E651C
    .word gSpeciesNames
    .pool

.org 0x080F3324
    .word gSpeciesNames
    .pool

.org 0x081035C0
    .word gSpeciesNames
    .pool

.org 0x08103698
    .word gSpeciesNames
    .pool

.org 0x08103738
    .word gSpeciesNames
    .pool

.org 0x081037D0
    .word gSpeciesNames
    .pool

.org 0x0810386C
    .word gSpeciesNames
    .pool

.org 0x081038CC
    .word gSpeciesNames
    .pool

.org 0x08104E70
    .word gSpeciesNames
    .pool

.org 0x08105FE0
    .word gSpeciesNames
    .pool

.org 0x081066B0
    .word gSpeciesNames
    .pool

.org 0x08113EFC
    .word gSpeciesNames
    .pool

.org 0x08119458
    .word gSpeciesNames
    .pool

.org 0x0811ACA0
    .word gSpeciesNames
    .pool

.org 0x0811AFF4
    .word gSpeciesNames
    .pool

.org 0x0811B048
    .word gSpeciesNames
    .pool

.org 0x0812190C
    .word gSpeciesNames
    .pool

.org 0x08136318
    .word gSpeciesNames
    .pool


// Egg hatch cycles repoint gBaseStats[0].eggCycles
.org 0x08046204
    .word gBaseStats + 0x11
    .pool

.org 0x080462A8
    .word gBaseStats + 0x11
    .pool



// Pokemon names table nop
.org 0x0825D7B4
    .fill 0x670, 0xFF

.org 0x08040FD0
    ldr r2, =(GetSpeciesName|1)
    bx r2
    .pool


// Pokemon level up learn moves repointing
.org 0x0803EA7C
    .word gLevelUpLearnsets
    .pool

.org 0x0803EB10
    .word gLevelUpLearnsets
    .pool

.org 0x0803EB84
    .word gLevelUpLearnsets
    .pool

.org 0x08043DC8
    .word gLevelUpLearnsets
    .pool

.org 0x08043E20
    .word gLevelUpLearnsets
    .pool

.org 0x08043F84
    .word gLevelUpLearnsets
    .pool

// generated bin tables insert
.org 0x08740000
    .incbin "src/pokemon/front_sprite_data.bin"
.pool

.org 0x8740000 + 0x4000
    .incbin "src/pokemon/back_sprite_data.bin"
.pool

.org 0x8740000 + 0x8000
    .incbin "src/pokemon/shared_pal_data.bin"
.pool


// Pokemon front sprites
.org 0x082350AC
    .fill 0xDC0, 0xFF
    .pool

.org 0x08000128
    .word gMonStillFrontPicTable
    .pool

.org 0x0800ECA8
    .word gMonStillFrontPicTable
    .pool

.org 0x0800ECEC
    .word gMonStillFrontPicTable
    .pool

.org 0x0800ED68
    .word gMonStillFrontPicTable
    .pool

.org 0x0800ED80
    .word gMonStillFrontPicTable
    .pool

.org 0x0800F0F8
    .word gMonStillFrontPicTable
    .pool

.org 0x0800F130
    .word gMonStillFrontPicTable
    .pool

.org 0x0800F1AC
    .word gMonStillFrontPicTable
    .pool

.org 0x0800F1C4
    .word gMonStillFrontPicTable
    .pool

.org 0x080343C4
    .word gMonStillFrontPicTable
    .pool

.org 0x08034D60
    .word gMonStillFrontPicTable
    .pool

.org 0x0803507C
    .word gMonStillFrontPicTable
    .pool

.org 0x08046F64
    .word gMonStillFrontPicTable
    .pool

.org 0x08050074
    .word gMonStillFrontPicTable
    .pool

.org 0x080500BC
    .word gMonStillFrontPicTable
    .pool

.org 0x08052068
    .word gMonStillFrontPicTable
    .pool

.org 0x080534C4
    .word gMonStillFrontPicTable
    .pool

.org 0x080769C0
    .word gMonStillFrontPicTable
    .pool

.org 0x080769E4
    .word gMonStillFrontPicTable
    .pool

.org 0x0808F470
    .word gMonStillFrontPicTable
    .pool

.org 0x080CE0B8
    .word gMonStillFrontPicTable
    .pool

.org 0x080CE2B8
    .word gMonStillFrontPicTable
    .pool

.org 0x080CE454
    .word gMonStillFrontPicTable
    .pool

.org 0x080CE6C4
    .word gMonStillFrontPicTable
    .pool

.org 0x0810BBE4
    .word gMonStillFrontPicTable
    .pool

.org 0x0810BBF0
    .word gMonStillFrontPicTable
    .pool

.org 0x0811D900
    .word gMonStillFrontPicTable
    .pool

.org 0x0814AED8
    .word gMonStillFrontPicTable
    .pool

// repoint back sprites
.org 0x0823654C
    .fill 0xDC0, 0xFF
    .pool

.org 0x0800012C
    .word gMonBackPicTable
    .pool

.org 0x0800ED58
    .word gMonBackPicTable
    .pool

.org 0x0800F19C
    .word gMonBackPicTable
    .pool

.org 0x08034540
    .word gMonBackPicTable
    .pool

.org 0x08034584
    .word gMonBackPicTable
    .pool

.org 0x08034F04
    .word gMonBackPicTable
    .pool

.org 0x08076A58
    .word gMonBackPicTable
    .pool

.org 0x08076AC8
    .word gMonBackPicTable
    .pool

.org 0x0810BC0C
    .word gMonBackPicTable
    .pool

.org 0x0810BC24
    .word gMonBackPicTable
    .pool


// repoint palette tables
.org 0x823730C
    .fill 0xDC0, 0xFF

.org 0x08000130
    .word gMonSpritePalTable
    .pool

.org 0x08000130
    .word gMonSpritePalTable
    .pool

.org 0x0804410C
    .word gMonSpritePalTable
    .pool

.org 0x08044130
    .word gMonSpritePalTable
    .pool

.org 0x080441A4
    .word gMonSpritePalTable
    .pool

.org 0x080839C0
    .word gMonSpritePalTable
    .pool

.org 0x080440F4
    ldr r3, =(GetMonSpritePalStructFromOtIdPersonality|1)
    bx r3
.pool


// Black sprite height
.org 0x8235E6C
    .fill 0x6E0, 0xFF

.org 0x08074634
    .word gMonBackPicCoords
    .pool

.org 0x08074664
    .word gMonBackPicCoords
    .pool

.org 0x08074670
    .word gMonBackPicCoords
    .pool

.org 0x08076564
    .word gMonBackPicCoords
    .pool

.org 0x08076B1C
    .word gMonBackPicCoords
    .pool

.org 0x08076BE8
    .word gMonBackPicCoords
    .pool

.org 0x08076BF8
    .word gMonBackPicCoords
    .pool

.org 0x08076C04
    .word gMonBackPicCoords
    .pool


// Front sprite Y table
.org 0x2349CC
    .fill 0x6E0, 0xFF

.org 0x08011F4C
    .word gMonFrontPicCoords
    .pool

.org 0x08011F80
    .word gMonFrontPicCoords
    .pool

.org 0x08011FAC
    .word gMonFrontPicCoords
    .pool

.org 0x080477E0
    .word gMonFrontPicCoords
    .pool

.org 0x08051410
    .word gMonFrontPicCoords
    .pool

.org 0x08052120
    .word gMonFrontPicCoords
    .pool

.org 0x08052800
    .word gMonFrontPicCoords
    .pool

.org 0x0805357C
    .word gMonFrontPicCoords
    .pool

.org 0x08074700
    .word gMonFrontPicCoords
    .pool

.org 0x08074734
    .word gMonFrontPicCoords
    .pool

.org 0x08074748
    .word gMonFrontPicCoords
    .pool

.org 0x080765A8
    .word gMonFrontPicCoords
    .pool

.org 0x08076AD8
    .word gMonFrontPicCoords
    .pool

.org 0x08076CD4
    .word gMonFrontPicCoords
    .pool

.org 0x08076CF0
    .word gMonFrontPicCoords
    .pool

.org 0x0814A938
    .word gMonFrontPicCoords
    .pool


// altitude table
.org 0x080356F8
    .word gEnemyMonElevation
    .pool

.org 0x0803575C
    .word gEnemyMonElevation
    .pool

.org 0x08074794
    .word gEnemyMonElevation
    .pool

.org 0x080747A8
    .word gEnemyMonElevation
    .pool

// height table limiters
.org 0x0807472E
    .byte 0x03
    .byte 0xE0

.org 0x0807465E
    .byte 0x03
    .byte 0xE0

.org 0x08074788
    .byte 0x06
    .byte 0xE0
