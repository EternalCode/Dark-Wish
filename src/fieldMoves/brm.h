#ifndef BRM_TABLE_DEFS_H_
#define BRM_TABLE_DEFS_H_

#include <pokeagb/pokeagb.h>

typedef void(*BRMFunc)(u8 taskId);

extern void ValidateAndLaunchFieldmove(u8 taskId);

static const u16 moveIdTerminator = 0xFFFF;

extern const pchar summaryDescription[];
extern const pchar switchDescription[];
extern const pchar cancelDescription[];
extern const pchar itemDescription[];
extern const pchar giveItemDescription[];
extern const pchar takeItemDescription[];
extern const pchar mailDescription[];
extern const pchar takeMailDescription[];
extern const pchar readMailDescription[];
extern const pchar cancelSubMenuDescription[];
extern const pchar shiftDescription[];
extern const pchar sendOutDescription[];
extern const pchar enterDescription[];
extern const pchar noEntryDescription[];
extern const pchar storeDescription[];
extern const pchar registerDescription[];
extern const pchar tradeDescription[];
extern const pchar nullDescription[];
extern const pchar flashDescription[];
extern const pchar cutDescription[];
extern const pchar flyDescription[];
extern const pchar strengthDescription[];
extern const pchar surfDescription[];
extern const pchar rockSmashDescription[];
extern const pchar waterfallDescription[];
extern const pchar teleportDescription[];
extern const pchar digDescription[];
extern const pchar milkDrinkDescription[];
extern const pchar softboiledDescription[];
extern const pchar sweetScentDescription[];
extern const pchar diveDescription[];

extern const pchar summaryString[];
extern const pchar switchString[];
extern const pchar cancelString[];
extern const pchar itemString[];
extern const pchar giveString[];
extern const pchar takeString[];
extern const pchar mailString[];
extern const pchar readString[];
extern const pchar shiftString[];
extern const pchar sendOutString[];
extern const pchar enterString[];
extern const pchar noEntryString[];
extern const pchar storeString[];
extern const pchar registerString[];
extern const pchar tradeString[];
extern const pchar flashString[];
extern const pchar cutString[];
extern const pchar flyString[];
extern const pchar strengthString[];
extern const pchar surfString[];
extern const pchar rockSmashString[];
extern const pchar waterfallString[];
extern const pchar teleportString[];
extern const pchar digString[];
extern const pchar milkDrinkString[];
extern const pchar softboiledString[];
extern const pchar sweetScentString[];
extern const pchar diveString[];

extern const pchar fieldMoveErrorMsg[];
extern const pchar FlashErrorMsg[];
extern const pchar CutErrorMsg[];
extern const pchar FlyErrorMsg[];
extern const pchar StrengthErrorMsg[];
extern const pchar SurfErrorMsg[];
extern const pchar RockSmashErrorMsg[];
extern const pchar WaterfallErrorMsg[];
extern const pchar TeleportErrorMsg[];
extern const pchar DigErrorMsg[];
extern const pchar MilkDrinkErrorMsg[];
extern const pchar SoftboiledErrorMsg[];
extern const pchar SweetScentErrorMsg[];
extern const pchar DiveErrorMsg[];

extern const pchar AskTeleport[];
extern const pchar AskDig[];
extern const pchar AskDive[];


static struct MachineBRM {
	pchar *brmString;
	BRMFunc LaunchBRMTask;
};

typedef bool(*HMPrepareFunc)(void);
typedef void(*LaunchFunc)(u8 fieldIndex, u8 taskId);
struct MachineFieldMoves {
    HMPrepareFunc BRMPrepareFunc;	// func to validate HM can be used / set up some stuff
    LaunchFunc LaunchFieldTask;	// do HM
	pchar *errorMsg;		// cannot do HM string pointer
};

static enum brmIndices { 
	summaryIndex = 0,
	switchIndex,
	cancelIndex,
	itemIndex,
	giveItemIndex,
	takeItemIndex,
	mailIndex,
	takeMailIndex,
	readMailIndex,
	cancelMenuIndex,
	shiftIndex,
	sendOutIndex,
	enterIndex,
	noEntryIndex,
	storeIndex,
	registerIndex,
	tradeIndex,
	nullIndex,
	flashIndex,
	cutIndex,
	flyIndex,
	strengthIndex,
	surfIndex,
	rockSmashIndex,
	waterfallIndex,
	teleportIndex,
	digIndex,
	milkDrinkIndex,
	softboiledIndex,
	sweetScentIndex,
	diveIndex,	
};



extern void AskAndDoBRMWarp( u8 bank, u8 map, u8 taskId, u8 fieldIndex, u32* StrPtr );
extern void BRMLaunchFly(u8 fieldIndex, u8 taskId);
extern void BRMLaunchTeleport(u8 fieldIndex, u8 taskId);
extern void BRMLaunchDig(u8 fieldIndex, u8 taskId);
extern void BRMLaunchSoftboiledAndMilkDrink(u8 fieldIndex, u8 taskId);
extern void BRMLaunchExitOverworld(u8 fieldIndex, u8 taskId);

extern bool BRMPrepareDive();

extern struct MachineBRM gBrmLauncher[];
extern struct MachineFieldMoves gFieldMoves[];

extern u32 gHmHelper[];
extern u16 fieldMoveIdTable[];


#endif /* BRM_TABLE_DEFS_H_ */