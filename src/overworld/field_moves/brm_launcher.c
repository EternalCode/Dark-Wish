#include <pokeagb/pokeagb.h>
#include "brm.h"

struct TextboxTemplate hmBoxTemplate = {
	.bg_id = 2,
	.x = 0,
	.y = 13,
	.width = 18,
	.height = 3,
	.pal_id = 12,
	.charbase = 883,
};

struct TextColor hmBoxTextColors = {0, 1, 2};


void hmDescriptionBox(u8 brmIndex) {
	u8 hmBoxId = gPtrBrmData->fieldMoveHelpboxId;
	u8 bgId = 2;
	if (brmIndex >= flashIndex) {
		if (hmBoxId == (0xFF)) {
			hmBoxId = rboxid_init(&hmBoxTemplate);
			gPtrBrmData->fieldMoveHelpboxId = hmBoxId;
		}
		CreateBannerBox(hmBoxId);
		u8 fboxId = 2;
		u8 fboxField = FBoxIdGetField(fboxId, 2);
		rboxid_add_812E5A4(hmBoxId, fboxId, 3, 6, fboxField, 0, &hmBoxTextColors, 0, (pchar*)gHmHelper[brmIndex]);
		rboxid_tilemap_update(hmBoxId);
		bgid_mark_for_sync(bgId);
		return;
	}
	else {
		// clear description box if it exists
		if ( hmBoxId != (0xFF)) {
			CreateBannerBox(hmBoxId);
			rboxid_free(hmBoxId);
			gPtrBrmData->fieldMoveHelpboxId = (0xFF);
			bgid_mark_for_sync(bgId);
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
	CreateBannerBox(hmBoxId);
	u8 fboxId = 2;
	u8 fboxField = FBoxIdGetField( fboxId, 2 );
	rboxid_add_812E5A4(hmBoxId, fboxId, 3, 6, fboxField, 0, &hmBoxTextColors, 0, gHmHelper[brmIndex]);
	u8 null = rboxid_tilemap_update(hmBoxId);
	bgid_mark_for_sync(bgId);
	*/
	return;
};


// hook at 08122C5C via r1
void brmLauncher(u8 taskId) {
	if (gPaletteFade.active)
		return;

	// check brm size
	u8 keypadChoice;
	if ( gPtrBrmData->numBrmOpts > 3 ) {
		keypadChoice = KeypadRepeatChoiceUpdate();
	}
	else {
		keypadChoice = KeypadRepeatChoiceUpdateSilent();
	}

	u8 brmIndex = tasks[taskId].priv[0];
	u8 choiceCurr = GetChoiceCurr();
	if ( brmIndex != choiceCurr ) {
		hmDescriptionBox(gPtrBrmData->BRMSequence[choiceCurr]);
	}
	tasks[taskId].priv[0] = choiceCurr;

	u8 keyPress = gMain.newKeys;
	if ( keyPress == KEY_A ) {
		ClearAndPrepareTextbox(&gPtrBrmData->fieldMoveHelpboxId);
		gBrmLauncher[gPtrBrmData->BRMSequence[keypadChoice]].LaunchBRMTask(taskId);
	}
	else if (keyPress == KEY_B ) {
		PlaySE(SOUND_GENERIC_CLINK);
		ClearAndPrepareTextbox(&gPtrBrmData->fieldMoveHelpboxId);
		gBrmLauncher[gPtrBrmData->BRMSequence[(gPtrBrmData->numBrmOpts)-1]].LaunchBRMTask(taskId);
	}
	return;
};
