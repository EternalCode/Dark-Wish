#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "battle_data/battle_state.h"
#include "../pokemon/pokemon.h"

// Switch
const bool USE_TESTS = true; // Change to false to not execute the test environment

/* Player data */
const static u16 playerSpecies = SPECIES_ABOMASNOW;
const static u16 playerMove1 = MOVE_POISONPOWDER;
const static u16 playerMove2 = MOVE_THUNDERPUNCH;
const static u16 playerMove3 = MOVE_WATERGUN;
const static u16 playerMove4 = MOVE_SHADOWPUNCH;
const static u8 playerLevel = 25;
const static u16 playerItem = ITEM_ORANBERRY;
const u8 gPlayerAbility = ABILITY_TORRENT;

/* Opponent data */
const static u16 opponentSpecies = SPECIES_SEADRA;
const static u16 opponentMove1 = MOVE_SOLARBEAM;
const static u16 opponentMove2 = MOVE_SOLARBEAM;
const static u16 opponentMove3 = MOVE_SOLARBEAM;
const static u16 opponentMove4 = MOVE_SOLARBEAM;
const static u8 opponentLevel = 16;
const static u16 opponentItem = ITEM_SITRUSBERRY;
const u8 gOpponentAbility = ABILITY_BLAZE;



void SideSetBattleComponents(u8 side)
{
	struct Pokemon* p = (side) ? (&party_player[0]) : (&party_opponent[0]);
	u16 species = (side) ? (playerSpecies) : (opponentSpecies);
	u16 move1 = (side) ? (playerMove1) : (opponentMove1);
	u16 move2 = (side) ? (playerMove2) : (opponentMove2);
	u16 move3 = (side) ? (playerMove3) : (opponentMove3);
	u16 move4 = (side) ? (playerMove4) : (opponentMove4);
	u8 level = (side) ? (playerLevel) : (opponentLevel);
	u16 item = (side) ? (playerItem) : (opponentItem);

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
	pokemon_setattr(p, REQUEST_HELD_ITEM, &item);
}

void TestBattleDataInit()
{
	if (USE_TESTS) {
		SideSetBattleComponents(0);
		SideSetBattleComponents(1);
	}
}
