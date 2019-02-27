#ifndef OPTIONS_MENU_H_
#define OPTIONS_MENU_H_

#include <pokeagb/pokeagb.h>

#define SELECTION_CURSOR_TAG 0x200
#define SELECTING_BANK gBattleMaster->option_selecting_bank

enum BattleMenuSelectionOptions {
    BaseMenuInitialize = 0,
    BaseMenuInputInterpret,
    FightOptionSelected_FirstTime,
    FightOptionSelected_FastLoad,
    SwitchOptionSelected,
    BagOptionSelected,
    RunOptionSelected,
    MenuWaitState,
    MoveSelectedExit,
};



#endif /* OPTIONS_MENU_H_ */
