#include <pokeagb/pokeagb.h>
#include "items.h"
#include "../battle_actions/actions.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../../global.h"
#include "../../pokemon/pokemon.h"

extern void ReturnToBattleFromBag(void);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 AnimCapturePokeball;

struct TextboxTemplate BagErrMsgText = {
    .bg_id = 0,
    .x = 2,
    .y = 0xF,
    .width = 0x1A,
    .height = 4,
    .pal_id = 0xF,
    .charbase = 0x2A2,
};


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
    *gBagCallback2OnExit = (u32)ReturnToBattleFromBag|1;
    *gBagCallback2OnExit_backup = (u32)ReturnToBattleFromBag|1;
    BagClosingAnimation();
    TaskExitBag(taskId);
}


// go to switch menu to select a pokemon for something
// TODO

u32 CalculateCatchRate(u8 ballBonus)
{
    // get bank
    u8 bank;
    if (ACTIVE_BANK(OPPONENT_SINGLES_BANK)) {
        bank = OPPONENT_SINGLES_BANK;
    } else {
        bank = OPPONENT_DOUBLES_BANK;
    }
    // get HP modifier
    u32 hpMax3 = 3 * TOTAL_HP(bank);
    u32 hpModifier = (hpMax3 - (B_CURRENT_HP(bank) << 1));
    // get pokemon catch rate
    u8 catchRate = gBaseStats[B_SPECIES(bank)].catchRate;
    // get ball bonus
    // ballBonus = ballBonus;
    // get bonus status
    u8 status;
    switch (B_STATUS(bank)) {
        case AILMENT_PARALYZE:
        case AILMENT_BURN:
        case AILMENT_BAD_POISON:
            status = 150;
            break;
        case AILMENT_SLEEP:
        case AILMENT_FREEZE:
            status = 250;
            break;
        default:
            status = 100;
            break;
    };
    // a
    return (hpModifier * catchRate * ballBonus * status) / hpMax3;
}

bool ShakeBall(u8 modifiedCatchRate)
{
    u32 sqrta = 16711680 / modifiedCatchRate;
    sqrta = Sqrt(sqrta);
    sqrta = Sqrt(sqrta);
    sqrta = 1048560 / sqrta;
    return rand() < sqrta;
}



const pchar Pokeball_error[] = _("Error text checking\ncan go new line?");
void PokeballTask(u8 taskId)
{
    // TODO: Check if it's a singles battle
    if (SpaceAvailableForPKMN()) {
        var_800E = ITEM_POKEBALL;
        BagRemoveItem(ITEM_POKEBALL, 1);
        ReturnToBattleScene(taskId);
    } else {
        WriteTextBag(taskId, (pchar*)Pokeball_error, true);
    }
}

void PokeballStartAction(u8 bank)
{
    // item used message
    QueueMessage(ITEM_POKEBALL, bank, STRING_USED_ITEM, 0);
    // calculate shakes and put it in lastresult
    u32 rate = CalculateCatchRate(POKEBALL_CATCH_RATE);
    u8 shakes;
    for (shakes = 0; shakes < 4; shakes++) {
        if (!ShakeBall(rate))
            break;
    }
    // call animation script
    struct action* a;

    if (ACTIVE_BANK(OPPONENT_SINGLES_BANK)) {
        TARGET_OF(bank) = OPPONENT_SINGLES_BANK;
        a = prepend_action(bank, OPPONENT_SINGLES_BANK, ActionHighPriority, EventPlayAnimation);
    } else {
        TARGET_OF(bank) = OPPONENT_DOUBLES_BANK;
        a = prepend_action(bank, OPPONENT_DOUBLES_BANK, ActionHighPriority, EventPlayAnimation);
    }
    a->script = (u32)&AnimCapturePokeball;
    a->priv[0] = shakes;
    switch (shakes) {
        case 0:
            QueueMessage(0, bank, STRING_BROKE_FREE, 0);
            break;
        case 1:
            QueueMessage(0, bank, STRING_APPEARED_CAUGHT, 0);
            break;
        case 2:
            QueueMessage(0, bank, STRING_ALMOST_HAD_IT, 0);
            break;
        case 3:
            QueueMessage(0, bank, STRING_SO_CLOSE_TOO, 0);
            break;
        case 4:
            {
                // if pokemon is captured, add it to party/box
                QueueMessage(0, bank, STRING_GOTCHA_CAUGHT, 0);
                AddOpponentPokemonToPlayer();
                struct action* bo = prepend_action(0xFF, 0xFF, ActionHighPriority, EventEndBattle);
                bo->active_override = true;
            }

    };
}







const struct ItemBattleEffects gBattleItemEffects[] = {
    {
        .itemId = ITEM_NONE,
        .initAction = NULL,
    },
    {
        .itemId = ITEM_MASTERBALL,
        .initAction = NULL,
    },
    {
        .itemId = ITEM_ULTRABALL,
        .initAction = NULL,
    },
    {
        .itemId = ITEM_GREATBALL,
        .initAction = NULL,
    },
    {
        .itemId = ITEM_POKEBALL,
        .initAction = PokeballStartAction,
    },
};
