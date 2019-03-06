#include <pokeagb/pokeagb.h>
#include "brm.h"

struct TextboxTemplate hmBoxTemplate[] = {
	(0x2),
	(0x0),
	(0xD),
	(0x12),
	(0x3),
	(0xC),
	(0x0373),
};

u8 hmBoxTextColors[] = {(0x0),(0x1),(0x2)};
	

void hmDescriptionBox(u8 brmIndex) {
	u8 hmBoxId = gPtrBrmData->fieldMoveHelpboxId;
	u8 bgId = 2;
	if ( brmIndex >= flashIndex ) {
		if ( hmBoxId == (0xFF) ) {
			hmBoxId = rboxIdInit(&hmBoxTemplate);
			gPtrBrmData->fieldMoveHelpboxId = hmBoxId;
		}
		createBannerBox(hmBoxId);
		u8 fboxId = 2;
		u8 fboxField = fBoxIdGetField( fboxId, 2 );
		rboxid_add_812E5A4(hmBoxId, fboxId, 3, 6, fboxField, 0, &hmBoxTextColors, 0, gHmHelper[brmIndex]);
		u8 null = rboxIdTilemapUpdate(hmBoxId);
		bgIdMarkForSync(bgId);
		return;
	}
	else {
		// clear description box if it exists
		if ( hmBoxId != (0xFF) ) {
			clearWindowTilemap(hmBoxId);
			rboxIdFree(hmBoxId);
			gPtrBrmData->fieldMoveHelpboxId = (0xFF);
			bgIdMarkForSync(bgId);
		}
		return;
	}
	/*
	sub menus messing up graphically
		081236A0 brm_item (need to clear third box too)
		08123CF4 brm_mail
	
	if ( hmBoxId == (0xFF) ) {
		hmBoxId = rboxIdInit(&hmBoxTemplate);
		gPtrBrmData->fieldMoveHelpboxId = hmBoxId;
	}
	createBannerBox(hmBoxId);
	u8 fboxId = 2;
	u8 fboxField = fBoxIdGetField( fboxId, 2 );
	rboxid_add_812E5A4(hmBoxId, fboxId, 3, 6, fboxField, 0, &hmBoxTextColors, 0, gHmHelper[brmIndex]);
	u8 null = rboxIdTilemapUpdate(hmBoxId);
	bgIdMarkForSync(bgId);
	*/
	return;
};


// hook at 08122C5C via r1
void brmLauncher(u8 taskId) {	
	u8* addr = (u8*) (0x02037AB8);
	u8 byte = *(addr + 0x7);
	
	if ( (byte >> 7) >= 1) {
		return;
	}
		
	/*
	if ( !gPaletteFade.active ) {
		return;
	}
	
	*/
	
	
	
	// check brm size
	u8 keypadChoice;
	if ( gPtrBrmData->numBrmOpts > 3 ) {
		keypadChoice = keypadRepeatChoiceUpdate();
	}
	else {
		keypadChoice = keypadRepeatChoiceUpdateSilent();
	}
	
	u8 brmIndex = tasks[taskId].priv[0];
	u8 choiceCurr = getChoiceCurr();
	if ( brmIndex != choiceCurr ) {
		hmDescriptionBox(gPtrBrmData->brmSequence[choiceCurr]);
	}
	tasks[taskId].priv[0] = choiceCurr;
	
	u8 keyPress = gMain.newKeys;
	if ( keyPress == KEY_A ) {
		ClearAndPrepareTextbox(&gPtrBrmData->fieldMoveHelpboxId);
		gBrmLauncher[gPtrBrmData->brmSequence[keypadChoice]].LaunchBRMTask(taskId);
	}
	else if (keyPress == KEY_B ) {
		PlaySE(SOUND_GENERIC_CLINK);
		ClearAndPrepareTextbox(&gPtrBrmData->fieldMoveHelpboxId);
		gBrmLauncher[gPtrBrmData->brmSequence[(gPtrBrmData->numBrmOpts)-1]].LaunchBRMTask(taskId);
	}
	return;
};

