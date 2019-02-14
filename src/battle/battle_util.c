#include <pokeagb/pokeagb.h>
#include "moves/moves.h"
#include "battle_data/pkmn_bank_stats.h"
#include "abilities/battle_abilities.h"
#include "battle_data/pkmn_bank.h"
#include "battle_data/battle_state.h"
#include "../pokemon/pokemon.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 SpeciesGetIndexAbility(u16 species, u8 abilityIndex);


bool IsStatNatureBoosted(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature / 5);
}

bool IsStatNatureNerved(u8 stat, struct Pokemon *pokemon) {
    u8 nature = get_nature(pokemon_getattr(pokemon, REQUEST_PID, NULL));
    if ((nature / 5) == (nature % 5))
        return false;
    return stat == (nature % 5);
}

s8 GetMovePriority(u8 bank)
{
    u16 move = CURRENT_MOVE(bank);

    /* update selected move's innate priority */
    if (B_MOVE_PRIORITY(bank))
        return B_MOVE_PRIORITY(bank);
    s8 priority = 0;
    priority += MOVE_PRIORITY(move);
    B_MOVE_PRIORITY(bank) = priority;

    /* on flee & switch the actor has a priority high enough to outspeed everything except pursuit */
    if ((gPkmnBank[bank]->battleData.isRunning) || (gPkmnBank[bank]->battleData.isSwitching))
        priority = 6;
    return priority;
}

u16 RandRange(u16 min, u16 max)
{
    if (min == max) return min;
    return (rand() % (max - min)) + min;
}

bool BankKnowsMove(u16 moveId, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == moveId)
            return true;
    }
    return false;
}

u8 GetMoveIndexBank(u16 moveId, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == moveId)
            return i;
    }
    return 255;
}

u8 CountBankMovePP(u16 moveId, u8 bank)
{
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i) == moveId) {
            return B_GET_MOVE_PP(bank, i);
        }
    }
	// move not found
    return 0;
}

u8 PokemonGetAbility(struct Pokemon* p)
{
    u8 abilityIndex = pokemon_getattr(p, REQUEST_ABILITY_BIT, NULL);
    u16 species = pokemon_getattr(p, REQUEST_SPECIES, NULL);
    return SpeciesGetIndexAbility(species, abilityIndex);
}

bool IsPokemonIgnoringItem(struct Pokemon* p)
{
    return (PokemonGetAbility(p) == ABILITY_KLUTZ);
}

bool BankMonHasType(u8 bank, enum PokemonType type)
{
    for (u8 i = 0; i < sizeof(gPkmnBank[bank]->battleData.type); i++) {
        if (gPkmnBank[bank]->battleData.type[i] == type) {
            return true;
        }
    }
    return false;
}

bool BankMonIsMonoType(u8 bank, enum PokemonType type)
{
    for (u8 i = 0; i < sizeof(gPkmnBank[bank]->battleData.type); i++) {
        if ((gPkmnBank[bank]->battleData.type[i] != type) && (gPkmnBank[bank]->battleData.type[i] != TYPE_NONE))
            return false;
    }
    return true;
}

bool BankAddType(u8 bank, enum PokemonType type)
{
    // cap at first two types. 3rd would be added types only
    for (u8 i = 0; i < sizeof(gPkmnBank[bank]->battleData.type); i++) {
        if (gPkmnBank[bank]->battleData.type[i] == TYPE_NONE) {
            gPkmnBank[bank]->battleData.type[i] = type;
            return true;
        }
    }
    return false;
}

bool BankMonSetType(u8 bank, enum PokemonType type)
{
    gPkmnBank[bank]->battleData.type[0] = type;
    gPkmnBank[bank]->battleData.type[1] = TYPE_NONE;
    gPkmnBank[bank]->battleData.type[2] = TYPE_NONE;
    return true;
}

void BankMonReplaceType(u8 bank, enum PokemonType type, enum PokemonType typeReplace)
{
    for (u8 i = 0; i < sizeof(gPkmnBank[bank]->battleData.type); i++) {
        if (gPkmnBank[bank]->battleData.type[i] == type) {
            gPkmnBank[bank]->battleData.type[i] = typeReplace;
        }
    }
}

bool BankMonUntyped(u8 bank)
{
    for (u8 i = 0; i < sizeof(gPkmnBank[bank]->battleData.type); i++) {
        if (gPkmnBank[bank]->battleData.type[i] != TYPE_NONE) {
            return false;
        }
    }
    return true;
}



bool BankOnGround(u8 bank)
{
    if (BankMonHasType(bank, TYPE_FLYING) ||
       (gPkmnBank[bank]->battleData.ability == ABILITY_LEVITATE)) {
        if(gPkmnBank[bank]->battleData.is_grounded)
            return true;
        return false;
    }
    return true;
}



//TODO: IMPLEMENT
void BankSetAbility(u8 bank, u8 source, u8 newAbility)
{

}

bool BankCanUseMove(u8 bank, u16 move)
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
    u8 index = GetMoveIndexBank(move, bank);
    if ((move == 0) || (B_GET_MOVE_PP(bank, index) == 0)) {
        return false;
    }
    return true;

}

u8 BankCountUsableMoves(u8 bank)
{
    u8 usableMoves = 0;
    for (u8 i = 0; i < 4; i++) {
        if (BankCanUseMove(bank, B_GET_MOVE(bank, i))) {
            usableMoves++;
        }
    }
    return usableMoves;
}

u8 BankMoveCount(u8 bank)
{
    u8 moveTotal = 0;
    for (u8 i = 0; i < 4; i++) {
        if (B_GET_MOVE(bank, i)) {
            moveTotal++;
        } else {
            break;
        }
    }
    return moveTotal;
}


bool BankMovesLast(u8 bank)
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (gBattleMaster->bankOrder[i] == bank) {
            if ((i == (BANK_MAX - 1))) {
                return true;
            }
            if (i < (BANK_MAX - 1)) {
                return (gBattleMaster->bankOrder[i + 1] == 0x3F);
            }
            return false;
        }
    }
    return false;
}


u8 SideCountUsablePkmn(u8 side)
{
    struct Pokemon* p = side ? &party_opponent[0] : &party_player[0];
    u8 count = 0;
    for (u8 i = 0; i < 6; i++) {
        u16 species = pokemon_getattr(&p[i], REQUEST_SPECIES, NULL);
        bool isEgg = pokemon_getattr(&p[i], REQUEST_IS_EGG, NULL);
        u16 currentHP = pokemon_getattr(&p[i], REQUEST_CURRENT_HP, NULL);

        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!isEgg) && (currentHP > 0)) {
            count++;
        }
    }
    return count;
}
