#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_data/pkmn_bank_stats.h"
#include "abilities/battle_abilities.h"
#include "battle_data/pkmn_bank.h"
#include "battle_data/battle_state.h"

#define SPECIES_MAX 900

extern bool enqueue_message(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);

void CpuFastSet(void* src, void* dst, u32 mode)
{
    __asm__("swi 0xC");
}

bool nature_stat_boosted(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature / 5);
}

bool nature_stat_nerved(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature % 5);
}

s8 get_move_priority(u8 bank)
{
    u16 move = CURRENT_MOVE(bank);

    /* update selected move's innate priority */
    if (B_MOVE_PRIORITY(bank))
        return B_MOVE_PRIORITY(bank);
    s8 priority = 0;
    priority += MOVE_PRIORITY(move);
    B_MOVE_PRIORITY(bank) = priority;

    /* on flee & switch the actor has a priority high enough to outspeed everything except pursuit */
    if ((p_bank[bank]->b_data.is_running) || (p_bank[bank]->b_data.is_switching))
        priority = 6;
    return priority;
}

u16 rand_range(u16 min, u16 max)
{
    if (min == max) return min;
    return (rand() % (max - min)) + min;
}

bool knows_move(u16 move_id, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == move_id)
            return true;
    }
    return false;
}

u8 get_move_index(u16 move_id, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == move_id)
            return i;
    }
    return 255;
}

u8 move_pp_count(u16 move_id, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == move_id) {
            return B_GET_MOVE_PP(bank, i);
        }
    }
	// move not found
    return 0;
}

u8 get_ability(struct Pokemon* p)
{
    u8 ability_bit = pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL);
    return pokemon_base_stats[pokemon_getattr(p, REQUEST_SPECIES, NULL)].ability[ability_bit];
}

bool ignoring_item(struct Pokemon* p)
{
    return (get_ability(p) == ABILITY_KLUTZ);
}

bool b_pkmn_has_type(u8 bank, enum PokemonType type)
{
    for (u8 i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if (p_bank[bank]->b_data.type[i] == type) {
            return true;
        }
    }
    return false;
}

bool b_pkmn_pure_type(u8 bank, enum PokemonType type)
{
    for (u8 i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if ((p_bank[bank]->b_data.type[i] != type) && (p_bank[bank]->b_data.type[i] != MTYPE_EGG))
            return false;
    }
    return true;
}

bool b_pkmn_add_type(u8 bank, enum PokemonType type)
{
    // cap at first two types. 3rd would be added types only
    for (u8 i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if (p_bank[bank]->b_data.type[i] == MTYPE_EGG) {
            p_bank[bank]->b_data.type[i] = type;
            return true;
        }
    }
    return false;
}

bool b_pkmn_set_type(u8 bank, enum PokemonType type)
{
    // Arceus and Silvally cannot have their types changed
    u16 species = p_bank[bank]->b_data.species;
    if ((species == SPECIES_ARCEUS) || (species == SPECIES_SILVALLY)) {
        return false;
    }
    p_bank[bank]->b_data.type[0] = type;
    p_bank[bank]->b_data.type[1] = MTYPE_EGG;
    p_bank[bank]->b_data.type[2] = MTYPE_EGG;
    return true;
}

void b_pkmn_replace_type(u8 bank, enum PokemonType type, enum PokemonType type_replace)
{
    for (u8 i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if (p_bank[bank]->b_data.type[i] == type) {
            p_bank[bank]->b_data.type[i] = type_replace;
        }
    }
}

bool b_pkmn_is_untyped(u8 bank)
{
    for (u8 i = 0; i < sizeof(p_bank[bank]->b_data.type); i++) {
        if (p_bank[bank]->b_data.type[i] != MTYPE_EGG) {
            return false;
        }
    }
    return true;
}



bool on_ground(u8 bank)
{
    if (b_pkmn_has_type(bank, TYPE_FLYING) ||
       (p_bank[bank]->b_data.ability == ABILITY_LEVITATE)) {
        if(p_bank[bank]->b_data.is_grounded)
            return true;
        return false;
    }
    return true;
}



//TODO: IMPLEMENT
void set_ability(u8 bank, u8 source, u8 new_ability)
{

}

bool move_is_usable(u8 bank, u16 move)
{
    // unusable under gravity
    if (HAS_VOLATILE(bank, VOLATILE_GRAVITY) && IS_GRAVITY(move)) {
        return false;
    }

    // unusable under healblock
    if (HAS_VOLATILE(bank, VOLATILE_HEAL_BLOCK) && IS_HEAL(move)) {
        return false;
    }

    // unusable because lack of PP or move Null
    u8 index = get_move_index(move, bank);
    if ((move == 0) || (B_GET_MOVE_PP(bank, index) == 0)) {
        return false;
    }
    return true;

}

u8 count_usable_moves(u8 bank)
{
    u8 usable_moves = 0;
    for (u8 i = 0; i < 4; i++) {
        if (move_is_usable(bank, B_GET_MOVE(bank, i))) {
            usable_moves++;
        }
    }
    return usable_moves;
}

u8 count_total_moves(u8 bank)
{
    u8 move_total = 0;
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i)) {
            move_total++;
        } else {
            break;
        }
    }
    return move_total;
}


bool moves_last(u8 bank)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (battle_master->bank_order[i] == bank) {
            if ((i == (BANK_MAX - 1))) {
                return true;
            }
            if (i < (BANK_MAX - 1)) {
                return (battle_master->bank_order[i + 1] == 0x3F);
            }
            return false;
        }
    }
    return false;
}


u8 count_usable_pokemon(u8 side)
{
    struct Pokemon* p = side ? &party_opponent[0] : &party_player[0];
    u8 count = 0;
    for (u8 i = 0; i < 6; i++) {
        u16 species = pokemon_getattr(&p[i], REQUEST_SPECIES, NULL);
        bool is_egg = pokemon_getattr(&p[i], REQUEST_IS_EGG, NULL);
        u16 current_hp = pokemon_getattr(&p[i], REQUEST_CURRENT_HP, NULL);

        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!is_egg) && (current_hp > 0)) {
            count++;
        }
    }
    return count;
}
