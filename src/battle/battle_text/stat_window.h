#ifndef STAT_WINDOW_H_
#define STAT_WINDOW_H_

#include <pokeagb/pokeagb.h>

struct StatWindow {
    u16 species;
    u8 level;
    u16 totalHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spattack;
    u16 spdefense;

    u8 levelNew;
    u16 totalHPNew;
    u16 attackNew;
    u16 defenseNew;
    u16 speedNew;
    u16 spattackNew;
    u16 spdefenseNew;
    u8 textboxes[10];
};


#endif /* STAT_WINDOW_H_ */
