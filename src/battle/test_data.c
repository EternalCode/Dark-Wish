#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"
#include "../pokemon/pokemon.h"

// Switch
const static bool USE_TESTS = true; // Change to false to not execute the test environment

/* Player data */
const static u16 playerSpecies = SPECIES_DARKRAI;
const static u16 playerMove1 = MOVE_HYPERBEAM;
const static u16 playerMove2 = MOVE_RECOVER;
const static u16 playerMove3 = MOVE_ACID;
const static u16 playerMove4 = MOVE_DRILLPECK;
const static u8 playerLevel = 15;
const u8 gPlayerAbility = ABILITY_COMATOSE;

/* Opponent data */
const static u16 opponentSpecies = SPECIES_DRAGONAIR;
const static u16 opponentMove1 = MOVE_PURSUIT;
const static u16 opponentMove2 = MOVE_PURSUIT;
const static u16 opponentMove3 = MOVE_PURSUIT;
const static u16 opponentMove4 = MOVE_PURSUIT;
const static u8 opponentLevel = 15;
const u8 gOpponentAbility = ABILITY_COMATOSE;



void SideSetBattleComponents(u8 side)
{
	struct Pokemon* p = (side) ? (&party_player[0]) : (&party_opponent[0]);
	u16 species = (side) ? (playerSpecies) : (opponentSpecies);
	u16 move1 = (side) ? (playerMove1) : (opponentMove1);
	u16 move2 = (side) ? (playerMove2) : (opponentMove2);
	u16 move3 = (side) ? (playerMove3) : (opponentMove3);
	u16 move4 = (side) ? (playerMove4) : (opponentMove4);
	u8 level = (side) ? (playerLevel) : (opponentLevel);

	pokemon_setattr(p, REQUEST_SPECIES, &species);
	pokemon_setattr(p, REQUEST_NICK, (void*)&gSpeciesNames[species]);
	u32 speciesExpIndex = (gBaseStats[species].growthRate * 0x194);
	u32 *expNeeded = (u32*) (0x8253AE4 + (speciesExpIndex + (level * 4)));
	pokemon_setattr(p, REQUEST_EXP_POINTS, expNeeded);
	recalculate_stats(p);
	pokemon_setattr(p, REQUEST_MOVE1, &move1);
	pokemon_setattr(p, REQUEST_MOVE2, &move2);
	pokemon_setattr(p, REQUEST_MOVE3, &move3);
	pokemon_setattr(p, REQUEST_MOVE4, &move4);
	pokemon_setattr(p, REQUEST_PP1, &gBattleMoves[move1].pp);
	pokemon_setattr(p, REQUEST_PP2, &gBattleMoves[move2].pp);
	pokemon_setattr(p, REQUEST_PP3, &gBattleMoves[move3].pp);
	pokemon_setattr(p, REQUEST_PP4, &gBattleMoves[move4].pp);
}

void TestBattleDataInit()
{
	if (USE_TESTS) {
		SideSetBattleComponents(0);
		SideSetBattleComponents(1);
	}
}