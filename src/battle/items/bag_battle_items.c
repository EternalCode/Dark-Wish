#include <pokeagb/pokeagb.h>

extern void return_to_battle_bag(void);

struct TextboxTemplate BagErrMsgText = {
    .bg_id = 0,
    .x = 2,
    .y = 0xF,
    .width = 0x1A,
    .height = 4,
    .pal_id = 0xF,
    .charbase = 0x2A2,
};

const pchar Pokeball_error[] = _("Error text checking\ncan go new line?");

// write some text to the main bag error message box
void WriteTextBag(u8 taskId, pchar* toPrint, bool keepOpen)
{
    if (keepOpen)
        PrintErrorMsgBag(taskId, 2, toPrint, bag_print_and_click_sound);
    else
        PrintErrorMsgBag(taskId, 2, toPrint, bag_print);
}

// return to battle scene
void ReturnToBattleScene(u8 taskId)
{
    // setup callback
    *gBagCallback2OnExit = (u32)return_to_battle_bag|1;
    *gBagCallback2OnExit_backup = (u32)return_to_battle_bag|1;
    BagClosingAnimation();
    TaskExitBag(taskId);
}


// go to switch menu to select a pokemon for something
// TODO


void PokeballTask(u8 taskId)
{
    ReturnToBattleScene(taskId);
    //WriteTextBag(taskId, Pokeball_error, true);
}
