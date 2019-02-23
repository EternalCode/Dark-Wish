#include <pokeagb\pokeagb.h>
#include "../../generated/images/battle_animations/impact1.h"
#include "../../generated/images/battle_animations/burn.h"
#include "../../generated/images/battle_animations/poison.h"
#include "../../generated/images/battle_animations/paralyze.h"
#include "../../generated/images/battle_animations/freeze.h"
#include "../../generated/images/battle_animations/confused.h"

extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];


// the impact sprite from tackle
const struct CompressedSpriteSheet impact1Sprite = {(void*)&impact1Tiles, 32 * 4 * 4, 400};
const struct SpritePalette impact1Palette = {&impact1Pal, 400};

const struct OamData impact1Oam = {
    .size = 2,
    .priority = 3,
};

// the burn animation sprite
const struct CompressedSpriteSheet burnSprite = {(void*)&burnTiles, 32 * 2 * 4, 401};
const struct SpritePalette burnPalette = {&burnPal, 401};

// burn sprite to shrink
const struct RotscaleFrame burnAffineTable[] = {
    {-20, -20, 0, 10, 0},
    {0x7FFF, 0, 0, 0, 0}
};

const struct OamData burnOam = {
    .affine_mode = 1,
    .shape = 2,
    .size = 2,
    .priority = 1,
};
const u32 burnAffinePtr = (u32)&burnAffineTable;


// poison ailment sprite
const struct CompressedSpriteSheet poisonSprite = {(void*)&poisonTiles, 32 * 2 * 2, 402};
const struct SpritePalette poisonPalette = {&poisonPal, 402};

const struct OamData poisonOam = {
    .size = 1,
    .priority = 1,
};

// paralyze ailment sprite
const struct CompressedSpriteSheet paralyzeSprite = {(void*)&paralyzeTiles, 32 * 4 * 4 * 3, 403};
const struct SpritePalette paralyzePalette = {&paralyzePal, 403};

const struct OamData paralyzeOam = {
    .size = 2,
    .priority = 1,
};

const struct Frame paralyzeLoop[] = {
    {0, 0x200},
    {8, 5},
    {16, 5},
    {20, 5},
    {24, 5},
    {32, 5},
    {0xFFFE, 0},
};
const struct Frame* paralyzeLoopPtr[] = {paralyzeLoop};

// freeze ailment sprite
const struct CompressedSpriteSheet freezeSprite = {(void*)&freezeTiles, 32 * 4 * 4, 404};
const struct SpritePalette freezePalette = {&freezePal, 404};

// freeze sprite to shrink
const struct RotscaleFrame freezeAffineTable[] = {
    {-200, -200, 0, 1, 0},
    {10, 10, 0, 15, 0},
    {0, 0, 0, 10, 0},
    {0x7FFF, 0, 0, 0, 0}
};

const struct OamData freezeOam = {
    .affine_mode = 1,
    .size = 2,
    .priority = 3,
};
const u32 freezeAffinePtr = (u32)&freezeAffineTable;


// confused sprite
const struct CompressedSpriteSheet confusedSprite = {(void*)&confusedTiles, 32 * 2 * 2 * 3, 405};
const struct SpritePalette confusedPalette = {&confusedPal, 405};

const struct OamData confusedOam = {
    .size = 1,
    .priority = 1,
};

const struct Frame confusedLoop[] = {
    {0, 20},
    {4, 20},
    {8, 20},
    {0xFFFE, 0},
};
const struct Frame* confusedLoopPtr[] = {confusedLoop};
