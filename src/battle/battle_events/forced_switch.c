#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"

extern void jump_switch_menu(enum switch_reason reason);


void fly_out_player_mon(struct Sprite* spr)
{
    spr->pos1.x -= 8;
    if (spr->pos1.x < -64) {
        spr->callback = NULL;
        // Free HP box and bars
        u8 bank = spr->data[0];
        for (u8 j = 0; j < 4; j++) {
            if (gPkmnBank[bank]->objid_hpbox[j] < 0x3F)
                obj_free(&gSprites[gPkmnBank[bank]->objid_hpbox[j]]);
            gPkmnBank[bank]->objid_hpbox[j] = 0x3F;
        }

        // Free player pkmn
        gPkmnBank[bank]->objid = 0x3F;
        obj_free(spr);
        jump_switch_menu(ForcedSwitch);
    }
}

void simple_delete_player_mon(struct Sprite* spr)
{
    spr->callback = NULL;
    // Free HP box and bars
    u8 bank = spr->data[0];
    for (u8 j = 0; j < 4; j++) {
        if (gPkmnBank[bank]->objid_hpbox[j] < 0x3F)
            obj_free(&gSprites[gPkmnBank[bank]->objid_hpbox[j]]);
        gPkmnBank[bank]->objid_hpbox[j] = 0x3F;
    }

    // Free player pkmn
    gPkmnBank[bank]->objid = 0x3F;
    obj_free(spr);
    jump_switch_menu(ForcedSwitch);
}

void forced_switch(u8 bank, u8 switch_method)
{
    gBattleMaster->switch_main.reason = ForcedSwitch;
    if (switch_method == 1) {
        gSprites[gPkmnBank[bank]->objid].callback = simple_delete_player_mon;
        gSprites[gPkmnBank[bank]->objid].data[0] = bank;
    } else {
        gSprites[gPkmnBank[bank]->objid].callback = fly_out_player_mon;
        gSprites[gPkmnBank[bank]->objid].data[0] = bank;
    }
    prepend_action(bank, bank, ActionHighPriority, EventSwitch);
    end_action(CURRENT_ACTION);
    SetMainCallback(NULL);
}

void event_forced_switch(struct action* current_action)
{
    forced_switch(CURRENT_ACTION->action_bank, CURRENT_ACTION->priv[0]);
}
