#include <pokeagb/pokeagb.h>
#include "brm.h"

// hook at 081229fc via r2
void buildBrmMenu(u32* addr, u8 slot) {
	u8* sequenceCounter = (u8*)&gPtrBrmData->numBrmOpts;
	u8* sequence = (u8*)&gPtrBrmData->BRMSequence[0];
	*sequenceCounter = 0;	// init

	// add summary
	AppendElement(sequence, sequenceCounter, summaryIndex);

	// init loop(s)
	u8 tableCounter = 0;
	u16 tableMoveID = fieldMoveIdTable[tableCounter];

	struct Pokemon* pkmn = &party_player[slot];
	// loop through move ID table, check to see if this poke can learn
	while ( tableMoveID != 0xFFFF ) {

		// check if can learn move
		u8 i;
		for (i = 0 ; i < 4; i++ ) {
			u16 learnsetMove = pokemon_getattr(pkmn, (REQUEST_MOVE1 + i), NULL);
			if ( learnsetMove == tableMoveID ) {
				AppendElement(sequence, sequenceCounter, (tableCounter + 0x12));	// add field move
				break;
			}
		}
		// could not learn the move, next move ID from table
		tableCounter++;
		tableMoveID = fieldMoveIdTable[tableCounter];
		if (tableMoveID == 0xFFFF) {
			break;
		}
	}

	// add switch
	u16 species = pokemon_getattr(pkmn, REQUEST_SPECIES, NULL);
	if (species != 0) {
		AppendElement(sequence, sequenceCounter, switchIndex);	// add switch
	}

	// check mail
	u16 holdItem = pokemon_getattr(pkmn, REQUEST_HELD_ITEM, NULL);
	bool isMail = ItemIdIsMail(holdItem);
	if (isMail == true) {
		AppendElement(sequence, sequenceCounter, mailIndex);	// add mail
	}
	else {
		AppendElement(sequence, sequenceCounter, itemIndex);	// add item
	}

	// add cancel
	AppendElement(sequence, sequenceCounter, cancelIndex);
};
