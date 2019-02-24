#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "../battle_text/battle_pick_message.h"
#include "../../pokemon/pokemon.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);

u32 calc_exp(u8 fainted, u8 reciever)
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
    u32 traded = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_TID, NULL);
    u32* temp = (u32*)&gSaveBlock2Ptr->playerTrainerId;
    traded = (traded == *temp) ? 100 : 150; // t

    // species base exp yield
    u16 species = pokemon_getattr(gPkmnBank[fainted]->this_pkmn, REQUEST_SPECIES, NULL);
    u16 base_yield = gBaseStats[species].expYield; // b
    // E = 50% more exp if the winning Pokémon is holding a lucky egg -- omitted

    u8 fainted_lvl = gPkmnBank[fainted]->battleData.level; // L
    u8 reciever_lvl = gPkmnBank[reciever]->battleData.level; // Lp

    u32 exp_part1 = fainted_lvl * base_yield;
    exp_part1 = PERCENT(exp_part1, trainer_mon);
    if (participated)
        exp_part1 = MAX((exp_part1 / 50), 1);
    else
        exp_part1 = exp_part1 / 5;

    u32 exp_part2 = ((2 *fainted_lvl) + 10);
    exp_part2 *= (exp_part2 * PERCENT(exp_part2, 50));
    u32 exp_part3 = (fainted_lvl + reciever_lvl + 10);
    exp_part3 *= (exp_part3 * PERCENT(exp_part3, 50));
    exp_part2 /= exp_part3;
    exp_part2 = MAX(exp_part2, 1);
    exp_part1 = (exp_part1 * exp_part2) + 1;
    return PERCENT(exp_part1, traded);
}


void give_exp(u8 fainted)
{
    u32 experience;
    for (u8 i = 0; i < 6; i++) {
        u16 species = pokemon_getattr(&party_player[i], REQUEST_SPECIES, NULL);
        bool is_egg = pokemon_getattr(&party_player[i], REQUEST_IS_EGG, NULL);
        u16 current_hp = pokemon_getattr(&party_player[i], REQUEST_CURRENT_HP, NULL);
        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!is_egg) && (current_hp > 0)) {
             // calc exp to grant for level
            experience = calc_exp(fainted, i);
            QueueMessage(0, i, STRING_EXP_GAIN, experience);
            // grant exp and see if level changed
            u8 level = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);
            experience += pokemon_getattr(&party_player[i], REQUEST_EXP_POINTS, NULL);
            pokemon_setattr(&party_player[i], REQUEST_EXP_POINTS, &experience);
            recalculate_stats(&party_player[i]);
            u8 newlevel = pokemon_getattr(&party_player[i], REQUEST_LEVEL, NULL);

            // if leveled up, print level up string
            if (newlevel > level) {
                // QueueMessage(0, reciever, STRING_LEVEL_UP, 0);
                // if (i ==)
                // u16 total_hp_new = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_TOTAL_HP, NULL);
                // B_CURRENT_HP(reciever) += (total_hp_new - total_hp);
            }
        }
    }
    return;
}
