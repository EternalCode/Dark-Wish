#include <pokeagb/pokeagb.h>

typedef bool(*HMPrepareFunc)(void);
typedef void(*LaunchFunc)(u8 fieldIndex, u8 taskId);

const pchar fieldMoveErrorMsg[] = _("Can’t use this move right now!\p");

const pchar FlashErrorMsg[] = _("Flash can’t be used here!\p");
const pchar CutErrorMsg[] = _("There is no grass within range!\p");
const pchar FlyErrorMsg[] = _("You can’t fly from\nthis location!\p");
const pchar StrengthErrorMsg[] = _("There are no boulders to\npush here!\p");
const pchar SurfErrorMsg[] = _("Unable to Surf here!\p");
//		differentiate between trying on land vs. fast current?
const pchar RockSmashErrorMsg[] = _("There are no rocks to\nsmash here!\p");
const pchar WaterfallErrorMsg[] = _("There is no waterfall\nto climb!\p");
const pchar TeleportErrorMsg[] = _("Can’t Teleport from here!\p");
const pchar DigErrorMsg[] = _("Can’t Dig from this location!\p");
const pchar MilkDrinkErrorMsg[] = _("There are no Pokémon to heal\nwith Milk Drink!\p");
const pchar SoftboiledErrorMsg[] = _("There are no Pokémon to heal\nwith Softboiled!\p");
const pchar SweetScentErrorMsg[] = _("Can’t use Sweet Scent at this location!\p");

const pchar AskTeleport[] = _("Teleport back to\n{STR_VAR_1}?");
const pchar AskDig[] = _("Dig through to return\nto {STR_VAR_1}?");

// function to perform warping (dig, teleport, dive)
void AskAndDoBRMWarp( u8 bank, u8 map, u8 taskId, u8 fieldIndex, u32* StrPtr ) {
	u8* LastHealingMapStruct = (u8*) mapheaderByMapnumbers( bank, map );
	u8 mapNameID = *(LastHealingMapStruct + 0x14);
	u8 mapName = GetMapName(fcodeBuffer2, mapNameID);
	pchar* askTeleportStr = fdecoder( stringBuffer, StrPtr );
	BRMStringBufferTask(taskId);
	u16* fieldStoreLoc = (u16*) (gPtrBrmData + 0x218);
	*fieldStoreLoc = fieldIndex;
	return;
}

void BRMLaunchFly(u8 fieldIndex, u8 taskId) {
	gAddrBRM = PerformBRMFly;	// store task in brm
	TaskBRMPalFade(taskId);	
	return;
}

void BRMLaunchTeleport(u8 fieldIndex, u8 taskId) {
	u8 teleportMap = gSaveBlock1Ptr->lastHealLocation.map;
	u8 teleportBank = gSaveBlock1Ptr->lastHealLocation.bank;
	AskAndDoBRMWarp( teleportBank, teleportMap, taskId, fieldIndex, AskTeleport );
	return;
}

void BRMLaunchDig(u8 fieldIndex, u8 taskId) {
	u8 digMap = gSaveBlock1Ptr->warp4.map;
	u8 digBank = gSaveBlock1Ptr->warp4.bank;
	AskAndDoBRMWarp( digBank, digMap, taskId, fieldIndex, AskDig );
	return;
}

void BRMLaunchSoftboiledAndMilkDrink(u8 fieldIndex, u8 taskId) {
	TaskSelectBRMPokeForHeal(taskId);
	return;
}

void BRMLaunchExitOverworld(u8 fieldIndex, u8 taskId) {
	gAddrBRM = exitToOverworldSwitch2;
	u8 brmSlot = brmGetPokemonSelection();
	BRMPrepareOverworldExit( &party_player[brmSlot], fieldIndex );
	TaskBRMPalFade(taskId);
	return;
}

struct MachineFieldMoves {
    HMPrepareFunc BRMPrepareFunc;	// func to validate HM can be used / set up some stuff
    LaunchFunc LaunchFieldTask;	// do HM
	pchar *errorMsg;		// cannot do HM string pointer
};

struct MachineFieldMoves gFieldMoves[] = {
    {BRMPrepareFlash, BRMLaunchExitOverworld, FlashErrorMsg},
    {BRMPrepareCut, BRMLaunchExitOverworld, CutErrorMsg},
	{BRMPrepareFly, BRMLaunchFly, FlyErrorMsg},
	{BRMPrepareStrength, BRMLaunchExitOverworld, StrengthErrorMsg},
	{BRMPrepareSurf, BRMLaunchExitOverworld, SurfErrorMsg},
	{BRMPrepareRockSmash, BRMLaunchExitOverworld, RockSmashErrorMsg},
	{BRMPrepareWaterfall, BRMLaunchExitOverworld, WaterfallErrorMsg},
	{BRMPrepareTeleport, BRMLaunchTeleport, TeleportErrorMsg},
	{BRMPrepareDig, BRMLaunchDig, DigErrorMsg},
	{BRMPrepareSoftboiledAndMilkDrink, BRMLaunchSoftboiledAndMilkDrink, MilkDrinkErrorMsg},
	{BRMPrepareSoftboiledAndMilkDrink, BRMLaunchSoftboiledAndMilkDrink, MilkDrinkErrorMsg},
	{BRMPrepareSweetScent, BRMLaunchExitOverworld, SweetScentErrorMsg},
};


// func called from selecting HM in BRM
void ValidateAndLaunchFieldmove(u8 taskId) {		
	// get relevant brm data
	u8 choiceCurr = gMenuChoices.choiceCurrent;	// BRM menu selection index from 0x0203ade6
	
	// need to define the struct!
	u8* brm0 = (u8*) gPtrBrmData;			// [0203b09c]
	u8 fieldIndex = *(brm0 + 0xF + choiceCurr);	// byte from [0203b09c] + 0xf
	fieldIndex -= 0x12;		// start of HM indices
	PlaySE(SOUND_GENERIC_CLINK);		// 'select' sound
	
	// update some textboxes
	ClearAndPrepareTextbox( (u32*) (brm0 + 0xc) );		// pass in address [0203b09c]+0xc
	ClearAndPrepareTextbox( (u32*) (brm0 + 0xd) );		// pass in address [0203b09c]+0xd  
	
	bool usable = gFieldMoves[fieldIndex].BRMPrepareFunc();
	if (usable == false) {
		u8 priority = 1;
		BRMDisplayMessageTask(gFieldMoves[fieldIndex].errorMsg, priority);
		tasks[taskId].function = TaskResetBRM;
		return;	
	}
	else {
		gFieldMoves[fieldIndex].LaunchFieldTask(fieldIndex, taskId);	//field moves, not flash/surf
		return;
    }
	return;
}	// end FieldMoveSelection

