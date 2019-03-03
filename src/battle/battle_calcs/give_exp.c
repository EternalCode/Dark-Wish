#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_actions/actions.h"
#include "../battle_events/battle_events.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../battle_text/stat_window.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../../pokemon/pokemon.h"
#include "../../global.h"

extern const u8 AnimSummaryLoad;
extern const u8 AnimLearnMove;
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);
extern u32 PokemonExpNeededToLevel(u8 slot);
extern void ShowStatBoostText(struct StatWindow* stats);
extern void ShowStatBoostTextComplete(struct StatWindow* stats);
extern void VblankMergeStatTextBox(void);
extern void VblankMergeTextBox(void);
extern u8 PokemonLearnsMoveLevel(u16 species, u8 level, u16* moveBuffer);

u32 calc_exp(u8 fainted, u8 reciever, u8 defeaterLevel)
{
    // check if reciever participated in battle
    u32 recieverId = pokemon_getattr(&party_player[reciever], REQUEST_PID, NULL);
    bool participated = false;
    for (u8 i = 0; i < 6; i++) {
        if (gBattleMaster->participatingIDs[i] == recieverId) {
            participated = true;
            break;
        }
    }

    // trainer gives 50% move exp
    u8 trainer_mon = (battle_type_flag != BATTLE_MODE_WILD) ? 150 : 100; // a

    // traded pokemon give 50% more exp
    u32 traded = pokemon_getattr(&party_player[reciever], REQUEST_TID, NULL) & 0xFFFF;
    u32 temp = gSaveBlock2Ptr->playerTrainerId[1] << 8 | gSaveBlock2Ptr->playerTrainerId[0];
    traded = (traded == temp) ? 100 : 150; // t
    // species base exp yield
    u16 species = pokemon_getattr(gPkmnBank[fainted]->this_pkmn, REQUEST_SPECIES, NULL);
    u16 base_yield =  gBaseStats[species].expYield; // b
    // E = 50% more exp if the winning Pokémon is holding a lucky egg -- omitted

    u8 fainted_lvl = gPkmnBank[fainted]->battleData.level; // L

    u32 exp_part1 = fainted_lvl * base_yield;
    exp_part1 = PERCENT(exp_part1, trainer_mon);
    if (participated)
        exp_part1 = exp_part1 / 5;
    else
        exp_part1 = MAX((exp_part1 / 50), 1);
    u32 exp_part2 = ((2 *fainted_lvl) + 10);
    exp_part2 *= (exp_part2 * PERCENT(exp_part2, 50));
    u32 exp_part3 = (fainted_lvl + defeaterLevel + 10);
    exp_part3 *= (exp_part3 * PERCENT(exp_part3, 50));
    exp_part2 /= exp_part3;
    exp_part2 = MAX(exp_part2, 1);
    exp_part1 = (exp_part1 * exp_part2) + 1;
    return PERCENT(exp_part1, traded);
}


void give_exp(u8 fainted, u8 defeater)
{
    u32 experience;
    u8 pkmnLevel = pokemon_getattr(gPkmnBank[defeater]->this_pkmn, REQUEST_LEVEL, NULL); // Lp
    for (u8 i = 0; i < 6; i++) {
        struct Pokemon* pkmn = &party_player[i];
        u16 species = pokemon_getattr(pkmn, REQUEST_SPECIES, NULL);
        bool is_egg = pokemon_getattr(pkmn, REQUEST_IS_EGG, NULL);
        u16 currentHP = pokemon_getattr(pkmn, REQUEST_CURRENT_HP, NULL);
        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!is_egg) && (currentHP > 0)) {
             // calc exp to grant for level
            experience = calc_exp(fainted, i, pkmnLevel);
            QueueMessage(i, defeater, STRING_EXP_GAIN, experience);
            u32 currentExp = pokemon_getattr(pkmn, REQUEST_EXP_POINTS, NULL);
            u8 levelOld = pokemon_getattr(pkmn, REQUEST_LEVEL, NULL);
            u8 newLevel = levelOld;

            // while the exp needed for slot to level < exp, grant exp needed to level
            u32 neededExp = PokemonExpNeededToLevel(i);
            while (neededExp < experience) {
                // log old stats
                struct StatWindow* stats = (struct StatWindow*)malloc_and_clear(sizeof(struct StatWindow));
                stats->slot = i;
                stats->level = pokemon_getattr(pkmn, REQUEST_LEVEL, NULL);
                stats->totalHP = pokemon_getattr(pkmn, REQUEST_TOTAL_HP, NULL);
                stats->attack = pokemon_getattr(pkmn, REQUEST_ATK, NULL);
                stats->defense = pokemon_getattr(pkmn, REQUEST_DEF, NULL);
                stats->speed = pokemon_getattr(pkmn, REQUEST_SPD, NULL);
                stats->spattack = pokemon_getattr(pkmn, REQUEST_SPATK, NULL);
                stats->spdefense = pokemon_getattr(pkmn, REQUEST_SPDEF, NULL);
                // grant needed exp and recalc stats
                experience -=neededExp;
                neededExp += currentExp;
                pokemon_setattr(pkmn, REQUEST_EXP_POINTS, &neededExp);
                // TODO Play exp gain animation
                recalculate_stats(pkmn);
                currentExp = pokemon_getattr(pkmn, REQUEST_EXP_POINTS, NULL);
                newLevel += 1;
                // log new stats for level
                stats->levelNew = pokemon_getattr(pkmn, REQUEST_LEVEL, NULL);
                stats->totalHPNew = pokemon_getattr(pkmn, REQUEST_TOTAL_HP, NULL);
                stats->attackNew = pokemon_getattr(pkmn, REQUEST_ATK, NULL);
                stats->defenseNew = pokemon_getattr(pkmn, REQUEST_DEF, NULL);
                stats->speedNew = pokemon_getattr(pkmn, REQUEST_SPD, NULL);
                stats->spattackNew = pokemon_getattr(pkmn, REQUEST_SPATK, NULL);
                stats->spdefenseNew = pokemon_getattr(pkmn, REQUEST_SPDEF, NULL);
                QueueMessage(i, defeater, STRING_LEVEL_UP, newLevel);
                // show updated stats
                struct action* a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
                a->action_bank = defeater;
                a->script = (u32)&AnimSummaryLoad;
                a->priv32 = (u32)stats;
                // check if pokemon learns a move at this level
                u16 moveBuffer[4] = {0, 0, 0, 0};
                u8 learnableMoves = PokemonLearnsMoveLevel(species, newLevel, &moveBuffer[0]);
                u8 buffIndex = 0;
                while (learnableMoves > buffIndex) {
                    u8 moveCount = PokemonCountUsableMoves(pkmn);
                    if ((moveCount < 4) && (learnableMoves > 0)) {
                        // teach move to pokemon in an open slot
                        pokemon_setattr(pkmn, REQUEST_MOVE1 + moveCount, &moveBuffer[buffIndex]);
                        pokemon_setattr(pkmn, REQUEST_PP1 + moveCount, &gBattleMoves[moveBuffer[buffIndex]].pp);
                        // pp needs to be synced if the slot is currently battling
                        if (B_PKMN(defeater) == pkmn)
                            B_GET_MOVE_PP(defeater, moveCount) = gBattleMoves[moveBuffer[buffIndex]].pp;
                        QueueMessage(i, defeater, STRING_LEARN_MOVE, moveBuffer[buffIndex]);
                    } else {
                        // <slot> wants to learn the\nmove <move>
                        // but <slot> can't learn\nmore than 4 moves
                        // Make it forget another move?
                        QueueMessage(i, defeater, STRING_TRYING_TO_LEARN_MOVE, moveBuffer[buffIndex]);
                        // Yes/No
                        // Yes-> which move should be forgotten?
                        a = prepend_action(ACTION_BANK, ACTION_BANK, ActionHighPriority, EventPlayAnimation);
                        a->action_bank = defeater;
                        a->script = (u32)&AnimLearnMove;
                        a->priv[0] = moveBuffer[buffIndex];
                        a->priv[1] = i;
                    }
                     buffIndex++;
                }
                // TODO check if pokemon evolves
                neededExp = PokemonExpNeededToLevel(i);
            }
            // grant remaining exp
            experience += currentExp;
            // TODO Play exp gain animation
            pokemon_setattr(pkmn, REQUEST_EXP_POINTS, &experience);
            recalculate_stats(pkmn);

        }
    }
    return;
}


#define state CURRENT_ACTION->priv[0]
void TaskStatScreen(u8 taskId)
{
    struct StatWindow* stats = (struct StatWindow*)CURRENT_ACTION->priv32;
    switch(state) {
        case 0:
            {
            // copy textbox image
            void* char_base = (void *)0x600C000;
            void* map_base = (void *)0x600F800;
            lz77UnCompVram((void *)bboxTiles, char_base);
            CpuFastSet((void*)battle_textbox_statMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
            u8 **bg0_map = (u8**)0x030008EC;
            u8 *dst = (u8 *)(*bg0_map);
            CpuFastSet((void*)battle_textbox_statMap, (void*)dst, CPUModeFS(0x800, CPUFSCPY));
            // write palettes
            SetVBlankCallback(VblankMergeStatTextBox);
            state++;
            break;
            }
        case 1:
            ShowStatBoostText(stats);
            state++;
            break;
        case 2:
            if (gMain.newKeys & (KEY_A | KEY_B)) {
                PlaySE(SOUND_GENERIC_CLINK);
                ShowStatBoostTextComplete(stats);
                state++;
            }
            break;
        case 3:
            if (gMain.newKeys & (KEY_A | KEY_B)) {
                PlaySE(SOUND_GENERIC_CLINK);
                // get rid of the summary screen gfx by writing default textbox gfx
                void* char_base = (void *)0x600C000;
                void* map_base = (void *)0x600F800;
                lz77UnCompVram((void *)bboxTiles, char_base);
                CpuFastSet((void*)battle_textboxMap, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));
                u8 **bg0_map = (u8**)0x030008EC;
                u8 *dst = (u8 *)(*bg0_map);
                CpuFastSet((void*)battle_textboxMap, (void*)dst, CPUModeFS(0x800, CPUFSCPY));
                SetVBlankCallback(VblankMergeTextBox);
                obj_free(&gSprites[stats->iconId]);
                free(stats);
                DestroyTask(taskId);
                state++;
            }
            break;
        case 4:
            break;
    };
}
#undef state

extern void ReturnToBattleFromMoveMenu(void);
extern void AnimationMain(void);
void TaskLearnMove(u8 taskId)
{
    switch (tasks[taskId].priv[0]) {
        case 0:
            gMain.callback1 = NULL;
            ShowSelectMovePokemonSummaryScreen(party_player, CURRENT_ACTION->priv[1], count_pokemon(), ReturnToBattleFromMoveMenu, MOVE_EMBER);
            gSummarySelectedMove = 0xFF;
            tasks[taskId].priv[0]++;
            break;
        case 1:
        {
            if (gMain.callback1 == AnimationMain && gSummarySelectedMove != 0xFF && !gPaletteFade.active) {
                u8 partySlot = CURRENT_ACTION->priv[1];
                VarSet(0x8000, pokemon_getattr(&party_player[partySlot], REQUEST_MOVE1 + gSummarySelectedMove, NULL));
                DestroyTask(taskId);
            }
            break;
        }
    };
}
