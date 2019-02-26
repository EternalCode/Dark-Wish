#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_events/battle_events.h"
#include "../battle_slide_in_data/battle_obj_sliding.h"
#include "../../pokemon/pokemon.h"
#include "../hpboxes/hpbox_positional_data.h"

extern void UpdatePKMNBank(u8 bank, struct SwitchingFlagsToPass* flags);
extern void buffer_write_pkmn_nick(pchar* buff, u8 bank);
extern void make_spinning_pokeball(s16 x, s16 y, u8 bank);
extern void TaskBackspriteBob(u8 tid);
extern void TaskPlayerHPBoxSlideIn(u8 taskId);
extern u8 spawn_hpbox_player(u16 tag, s16 x, s16 y, u8 bank);
extern void battle_loop(void);
extern void run_after_switch(u8 bank);
extern void jump_switch_menu(enum switch_reason reason);
extern void ShowBattleMessage2(pchar* str, u8 rboxid);

static const struct RotscaleFrame shrink[] = {
    {-10, -10, 0, 10, 0},
    {-20, -20, 0, 5, 0},
    {0x7FFF, 0, 0, 0, 0},
};

static const struct RotscaleFrame* shrink_ptr[] = {shrink};


void reset_hpbars_and_sprite_player(struct Sprite* spr)
{
    // Free HP box and bars
    u8 bank = CURRENT_ACTION->action_bank;
    for (u8 j = 0; j < 4; j++) {
        if (gPkmnBank[bank]->objid_hpbox[j] < 0x3F) {
            gBattleMaster->switch_main.type_objid[j] = gPkmnBank[bank]->objid_hpbox[j];
            OBJID_HIDE(gPkmnBank[bank]->objid_hpbox[j]);
        } else {
            gBattleMaster->switch_main.type_objid[j] = 0x3F;
        }
        gPkmnBank[bank]->objid_hpbox[j] = 0x3F;
    }

    // Free player pkmn
    gPkmnBank[bank]->objid = 0x3F;
    obj_free(spr);
}


void pkmn_recall_cb(struct Sprite* spr)
{
    if (spr->data[0] < 25) {
        spr->pos1.y += 2;
    } else {
        reset_hpbars_and_sprite_player(spr);
    }
    spr->data[0]++;
}


void pkmn_player_normal_switch()
{
    switch (gMain.state) {
        case 0:
            {
                u8 bank = CURRENT_ACTION->action_bank;
                u8 objid = gPkmnBank[bank]->objid;
                gSprites[objid].rotscale_table = shrink_ptr;
                gSprites[objid].data[0] = 0;
                gSprites[objid].callback = pkmn_recall_cb;
                OBJID_SHOW_AFFINE(objid);
                obj_rotscale_play(&gSprites[objid], 0);
                // fade only this OAM's palette to pink
                u8 pal_slot = gSprites[objid].final_oam.palette_num;
                u32 pal_fade = ((1 << (pal_slot + 16)));
                BeginNormalPaletteFade(pal_fade , 2, 0x10, 0x0, 0x7ADF);
                gMain.state++;
                break;
            }
        case 1:
            {
                DestroyTask(task_find_id_by_functpr(TaskBackspriteBob));
                u8 objid = gPkmnBank[CURRENT_ACTION->action_bank]->objid;
                u8 species_y = gMonBackPicCoords[B_SPECIES(CURRENT_ACTION->action_bank)].y_offset;
                gSprites[objid].pos1.y = 80 + species_y;
                objid = gPkmnBank[CURRENT_ACTION->action_bank]->objid_hpbox[0];
                gSprites[objid].pos1.y = HPBOX_PLAYER_SINGLE_Y;
                objid = gPkmnBank[CURRENT_ACTION->action_bank]->objid_hpbox[1];
                gSprites[objid].pos1.y = HPBOX_PLAYER_SINGLE_Y;
                objid = gPkmnBank[CURRENT_ACTION->action_bank]->objid_hpbox[2];
                gSprites[objid].pos1.y = HPBAR_PS_Y;
                objid = gPkmnBank[CURRENT_ACTION->action_bank]->objid_hpbox[3];
                gSprites[objid].pos1.y = HPBOX_STATUS_PLAYER_SINGLE_Y;
                gMain.state++;
                break;
            }
        case 2:
            {
                if (gPkmnBank[CURRENT_ACTION->action_bank]->objid < 0x3F) return;
                pchar text[] = _("Go! {STR_VAR_2}!");
                memcpy(fcode_buffer3, gPkmnBank[CURRENT_ACTION->action_bank]->this_pkmn->box.nick, sizeof(party_player[0].box.nick));
                fcode_buffer3[sizeof(party_player[0].box.nick)] = 0xFF;
                fdecoder(string_buffer, text);
                remo_reset_acknowledgement_flags();
                ShowBattleMessage2((u8*)string_buffer, 0x1);
                gMain.state++;
                break;
            }
       case 3:
            if (!dialogid_was_acknowledged(0x1)) {
                u8 bank = CURRENT_ACTION->action_bank;
                make_spinning_pokeball(53, 64, bank);
                gBattleAnimationStatus = 1;
                for (u8 i = 0; i < 4; i++) {
                    u8 objid = gBattleMaster->switch_main.type_objid[i];
                    if (objid < 0x3F)
                        obj_free(&gSprites[objid]);
                    gBattleMaster->switch_main.type_objid[i] = 0x3F;
                }

                // spawn new HP bar
                spawn_hpbox_player(HPBOX_TAG_PLAYER_SINGLE, HPBOX_PLAYER_SINGLE_X, HPBOX_PLAYER_SINGLE_Y, bank);
                gSprites[gPkmnBank[bank]->objid_hpbox[0]].pos1.x += 128;
                gSprites[gPkmnBank[bank]->objid_hpbox[1]].pos1.x += 128;
                gSprites[gPkmnBank[bank]->objid_hpbox[2]].pos1.x += 128;
                gSprites[gPkmnBank[bank]->objid_hpbox[3]].pos1.x += 128;
                gMain.state++;
            }
            break;
        case 4:
            if ((gPaletteFade.active) || (gBattleAnimationStatus)) return;
            CreateTask(TaskPlayerHPBoxSlideIn, 1);
            gBattleAnimationStatus = 1;
            gMain.state++;
            break;
        case 5:
            if (gBattleAnimationStatus) return;
            struct SwitchingFlagsToPass* flags = (struct SwitchingFlagsToPass*)malloc_and_clear(sizeof(struct SwitchingFlagsToPass));
            flags->pass_status = false;
            flags->pass_stats = false;
            flags->pass_atk_history = false;
            flags->pass_disables = false;
            UpdatePKMNBank(CURRENT_ACTION->action_bank, flags);
            free(flags);
            gMain.state++;
            break;
        case 6:
            if (!gPaletteFade.active) {
                gPkmnBank[CURRENT_ACTION->action_bank]->battleData.isSwitching = false;
                struct action* a = next_action(ACTION_BANK, NULL, ActionSwitch, EventPostSwitch);
                a->priv[0] = ACTION_BANK;
                end_action(CURRENT_ACTION);
                gMain.state = 0;
                SetMainCallback(battle_loop);
            }
            break;
    };
}


void pkmn_recall_animation()
{
    switch (gBattleMaster->switch_main.reason) {
        case ViewPokemon:
            dprintf("Reason ViewPokemon given for switch into battle. Executing normal switch.");
        case NormalSwitch:
            gMain.state = 0;
            SetMainCallback(pkmn_player_normal_switch);
            return;
        case ForcedSwitch:
            gMain.state = 2;
            SetMainCallback(pkmn_player_normal_switch);
            break;
        case PokemonFainted:
            gMain.state = 2;
            SetMainCallback(pkmn_player_normal_switch);
            return;
    };
}
