/* Battle master */
gBattleMaster = 0x03004F80;

/* Pointer to the pokemon bank pointers. It's an array of size 4
 * So all 4 of these addresses are reserved.
 */
gPkmnBank = 0x03004F84;
gPkmnBank1 = 0x03004F88;
gPkmnBank2 = 0x03004F8C;
gPkmnBank3 = 0x03004F90;

/* During slide in, holds pointer to positional data */
BattleEntryWindows = 0x03004F94;

/* The type of the current battle. Currently only wild is supported */
battle_type_flag = 0x02022B4C;

/* Animation status for the battle UI */
gBattleAnimationStatus = 0x03004FA3;

/* Animation script core struct pointer */
gAnimationCore = 0x03004FA4;
