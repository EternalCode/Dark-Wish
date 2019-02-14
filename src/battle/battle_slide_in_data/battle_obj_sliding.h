#ifndef BATTLE_ENTRY_OBJ_H_
#define BATTLE_ENTRY_OBJ_H_

#include <pokeagb/pokeagb.h>
#include "../hpboxes/hpbox_positional_data.h"


/* Battle screen elements positions structure */
struct bs_elements_positions {
    s16 bot_side;
    s16 top_side;
    s16 wintop;
    s16 winbot;
    u8 player_trainer_objid;
    u8 partner_trainer_objid;
};

extern struct bs_elements_positions* BattleEntryWindows;

#endif /* BATTLE_ENTRY_OBJ_H_ */
