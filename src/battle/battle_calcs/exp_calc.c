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
    u8 trainer_mon = (battle_type_flag != BATTLE_MODE_WILD) ? 150 : 100;
    // base species recieve incase of species index change
    u16 species = pokemon_getattr(gPkmnBank[fainted]->this_pkmn, REQUEST_SPECIES, NULL);
    u16 base_yield = gBaseStats[species].expYield;
    u8 fainted_lvl = gPkmnBank[fainted]->battleData.level;
    u8 reciever_lvl = gPkmnBank[reciever]->battleData.level;

    u32 traded = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_TID, NULL);
    u32* temp = (u32*)&gSaveBlock2Ptr->playerTrainerId;
    traded = (traded == *temp) ? 100 : 150;

    u32 exp_part1 = fainted_lvl * base_yield;
    exp_part1 = PERCENT(exp_part1, trainer_mon);
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

/* TODO exp share item - probably as a callback here */
/* TODO Lucky egg item - probably as a callback here */
/* TODO Passpower/O-power - probably not implementing this */
void give_exp(u8 fainted, u8 reciever)
{
    u32 exp = calc_exp(fainted, reciever);
    QueueMessage(0, reciever, STRING_EXP_GAIN, exp);
    /* TODO add task that grants exp*/
    exp += pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_EXP_POINTS, NULL);
    pokemon_setattr(gPkmnBank[reciever]->this_pkmn, REQUEST_EXP_POINTS, &exp);
    u16 total_hp = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_TOTAL_HP, NULL);
    recalculate_stats(gPkmnBank[reciever]->this_pkmn);
    u8 new_lvl = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_LEVEL, NULL);
    if (new_lvl > gPkmnBank[reciever]->battleData.level) {
        QueueMessage(0, reciever, STRING_LEVEL_UP, 0);
        u16 total_hp_new = pokemon_getattr(gPkmnBank[reciever]->this_pkmn, REQUEST_TOTAL_HP, NULL);
        B_CURRENT_HP(reciever) += (total_hp_new - total_hp);
    }
    return;
}
