#include <pokeagb/pokeagb.h>
#include "brm.h"

// hook at 081229fc via r2
void buildBrmMenu(u32* addr, u8 slot) {
	u8* sequenceCounter = (u8*) &gPtrBrmData->numBrmOpts;
	u8* sequence = (u8*) &gPtrBrmData->brmSequence[0];
	*sequenceCounter = 0;	// init
	
	// add summary
	appendElement(sequence, sequenceCounter, summaryIndex);
	
	// init loop(s)
	u8 tableCounter = 0;
	u16 tableMoveID = fieldMoveIdTable[tableCounter];
	
	u32 pokeAddr = &party_player[slot];
	// loop through move ID table, check to see if this poke can learn 
	while ( tableMoveID != moveIdTerminator ) {
		
		// check if can learn move
		u8 i;
		for (i = 0 ; i < 4; i++ ) {
			u16 learnsetMove = pokemon_getattr( pokeAddr, (REQUEST_MOVE1 + i), 0 );
			if ( learnsetMove == tableMoveID ) {
				appendElement( sequence, sequenceCounter, (tableCounter+0x12) );	// add field move
				break;
			}
		}
		// could not learn the move, next move ID from table	
		tableCounter++;
		tableMoveID = fieldMoveIdTable[tableCounter];
		if ( tableMoveID == moveIdTerminator ) {
			break;
		}
	}
	
	// add switch
	u16 species = pokemon_getattr( pokeAddr, REQUEST_SPECIES, 0 );
	if ( species != 0 ) {
		appendElement(sequence, sequenceCounter, switchIndex);	// add switch
	}
	
	// check mail
	u16 holdItem = pokemon_getattr( pokeAddr, REQUEST_HELD_ITEM, 0 );
	bool isMail = itemIdIsMail(holdItem);
	if ( isMail == true ) {
		appendElement(sequence, sequenceCounter, mailIndex);	// add mail
	}
	else {
		appendElement(sequence, sequenceCounter, itemIndex);	// add item
	}
	
	// add cancel
	appendElement(sequence, sequenceCounter, cancelIndex);
	
	return;
};

