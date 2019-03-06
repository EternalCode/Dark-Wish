#include <pokeagb/pokeagb.h>
#include "brm.h"


// func called from selecting HM in BRM
void ValidateAndLaunchFieldmove(u8 taskId) {
	u8 fieldIndex = gPtrBrmData->brmSequence[gMenuChoices.choiceCurrent] - 0x12;
	PlaySE(SOUND_GENERIC_CLINK);
	ClearAndPrepareTextbox(&gPtrBrmData->optsBoxId);
	ClearAndPrepareTextbox(&gPtrBrmData->actionBoxId);
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
}

// function to perform warping (dig, teleport, dive)
void AskAndDoBRMWarp( u8 bank, u8 map, u8 taskId, u8 fieldIndex, u32* StrPtr ) {
	u8* LastHealingMapStruct = (u8*) mapheaderByMapnumbers( bank, map );
	u8 mapNameID = *(LastHealingMapStruct + 0x14);
	u8 mapName = GetMapName(gFcodeBuffer2, mapNameID);
	pchar* askTeleportStr = fdecoder( gStringBuffer, StrPtr );
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

void BRMLaunchDive(u8 fieldIndex, u8 taskId) {
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

bool BRMPrepareDive() {
	return false;
}
