#ifndef BATTLE_HPBOX_POS_H_
#define BATTLE_HPBOX_POS_H_

#include <pokeagb/pokeagb.h>

// single wild battle opponent HPbox tag and position for object
#define HPBOX_TAG_OPP_SW 0x400
#define HPBOX_OPP_SW_X 32
#define HPBOX_OPP_SW_Y 38

// single battle player HPbox tag and position for object
#define HPBOX_TAG_PLAYER_SINGLE 0x500
#define HPBOX_PLAYER_SINGLE_X 144
#define HPBOX_PLAYER_SINGLE_Y 88

// single battle HPbox status tag and position for object
#define HPBOX_STATUS_TAG_PLAYER_SINGLE 0x510
#define HPBOX_STATUS_TAG_OPP_SINGLE 0x514

#define HPBOX_STATUS_PLAYER_SINGLE_X 160
#define HPBOX_STATUS_PLAYER_SINGLE_Y 98
#define HPBOX_STATUS_OPP_SINGLE_X 16
#define HPBOX_STATUS_OPP_SINGLE_Y 28

// HP bar (green health bar) positions and tags
#define HPBAR_PS_TAG 0x600
#define HPBAR_PS_X 200
#define HPBAR_PS_Y 103
#define HPBAR_OS_TAG 0x700
#define HPBAR_OS_X 56
#define HPBAR_OS_Y 37

// tile offsets for hpbox elements
// (PS) = player single, (0S) = opponent single
#define NAME_PS_OFFSET1 21
#define NAME_PS_OFFSET2 59
#define LVL_PS_OFFSET 84
#define HPNUM_PS_OFFSET 98
#define NAME_OS_OFFSET1 1
#define NAME_OS_OFFSET2 0
#define LVL_OS_OFFSET 64

/* Used for distinguishing how big HP boxes are and how much writing room there is */
enum HPFontMode {
    HPFONT_PLAYER_SINGLE,
    HPFONT_OPP_SINGLE,
};


#endif /* BATTLE_HPBOX_POS_H_ */