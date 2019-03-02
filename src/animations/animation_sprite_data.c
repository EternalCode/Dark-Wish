#include <pokeagb\pokeagb.h>
#include "../../generated/images/battle_animations/impact1.h"
#include "../../generated/images/battle_animations/burn.h"
#include "../../generated/images/battle_animations/poison.h"
#include "../../generated/images/battle_animations/paralyze.h"
#include "../../generated/images/battle_animations/freeze.h"
#include "../../generated/images/battle_animations/confused.h"
#include "../../generated/images/battle_animations/infatuation.h"
#include "../../generated/images/battle_animations/sleep.h"
#include "../../generated/images/battle_animations/smoke.h"
#include "../../generated/images/battle_animations/glowball.h"
#include "../../generated/images/battle_animations/pokeball.h"
#include "../../generated/images/battle_animations/impact2.h"
#include "../../generated/images/battle_animations/impact2.h"
#include "../../generated/images/battle_animations/pokeball_particles.h"


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

// freeze sprite to grow
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


// infactuation sprite
const struct CompressedSpriteSheet infatuationSprite = {(void*)&infatuationTiles, 32 * 2 * 2, 406};
const struct SpritePalette infatuationPalette = {&infatuationPal, 406};

const struct OamData infatuationOam = {
    .size = 1,
    .priority = 1,
};


// Sleep sprite
const struct CompressedSpriteSheet sleepSprite = {(void*)&sleepTiles, 32 * 4 * 4, 407};
const struct SpritePalette sleepPalette = {&sleepPal, 407};

const struct RotscaleFrame sleepAffineTable[] = {
    {-150, -150, -30, 1, 0},
    {2, 2, 2, 5, 0},
    {0, 0, 0, 8, 0},
    {2, 2, 2, 5, 0},
    {0, 0, 0, 8, 0},
    {2, 2, 2, 5, 0},
    {0, 0, 0, 8, 0},
    {0x7FFF, 0, 0, 0, 0}
};
const u32 sleepAffinePtr = (u32)&sleepAffineTable;

const struct OamData sleepOam = {
    .affine_mode = 1,
    .size = 2,
    .priority = 1,
};

// Smoke sprite
const struct CompressedSpriteSheet smokeSprite = {(void*)&smokeTiles, 32 * 4 * 4 * 3, 407};
const struct SpritePalette smokePalette = {&smokePal, 407};

const struct OamData smokeOam = {
    .size = 2,
    .priority = 1,
};

const struct Frame smokeLoop[] = {
    {0, 5},
    {16, 5},
    {32, 5},
    {0xFFFF, 0},
};
const struct Frame* smokeLoopPtr[] = {smokeLoop};

// glowball sprite
const struct CompressedSpriteSheet glowballSprite = {(void*)&glowballTiles, 32 * 2 * 2, 408};
const struct SpritePalette glowballPalette = {&glowballPal, 408};

const struct OamData glowballOam = {
    .affine_mode = 1,
    .size = 1,
    .priority = 1,
};

const struct RotscaleFrame glowballAffineTable[] = {
    {0, 0, 0, 1, 0},
    {-10, -10, 0, 30, 0},
    {0x7FFF, 0, 0, 0, 0}
};
const u32 glowballAffinePtr = (u32)&glowballAffineTable;

// pokeball sprite
const struct CompressedSpriteSheet pokeballSprite = {(void*)&pokeballTiles, 32 * 2 * 2 * 3, 409};
const struct SpritePalette pokeballPalette = {&pokeballPal, 409};

const struct OamData pokeballOam = {
    .affine_mode = 1,
    .size = 1,
    .priority = 1,
};

const struct Frame pokeballOpen[] = {
    {0, 5},
    {4, 5},
    {0xFFFF, 0},
};

const struct Frame pokeballClose[] = {
    {4, 5},
    {0, 5},
    {0xFFFF, 0},
};

const struct Frame* pokeballFrames[] = {
    pokeballOpen,
    pokeballClose,
};


const struct RotscaleFrame pokeballLeftTiltAffineTable[] = {
    {0, 0, 0, 1, 0},
    {0, 0, -3, 10, 0},
    {0, 0, 0, 10, 0},
    {0, 0, 3, 10, 0},
    {0x7FFF, 0, 0, 0, 0}
};

const struct RotscaleFrame pokeballRightTiltAffineTable[] = {
    {0, 0, 0, 1, 0},
    {0, 0, 3, 10, 0},
    {0, 0, 0, 10, 0},
    {0, 0, -3, 10, 0},
    {0x7FFF, 0, 0, 0, 0}
};

const struct Frame* pokeballOpenPtr[] = {pokeballOpen};
const u32 pokeballLeftTiltAffineTablePtr = (u32)&pokeballLeftTiltAffineTable;
const u32 pokeballRightTiltAffineTablePtr = (u32)&pokeballRightTiltAffineTable;

// impact2 sprite
const struct CompressedSpriteSheet impact2Sprite = {(void*)&impact2Tiles, 32 * 4 * 4, 410};
const struct SpritePalette impact2Palette = {&impact2Pal, 410};

const struct OamData impact2Oam = {
    .size = 2,
    .priority = 3,
};

// Pokeball particles when opened or closed
const struct CompressedSpriteSheet pokeballParticleSprite = {(void*)&pokeball_particlesTiles, 32 * 1 * 1 * 3, 411};
const struct SpritePalette pokeballParticlePalette = {&pokeball_particlesPal, 411};

const struct OamData pokeballParticleOam = {
    .size = 0,
    .priority = 1,
};

const struct Frame pokeballParticleLoop[] = {
    {0, 5},
    {1, 5},
    {2, 5},
    {0xFFFE, 0},
};
const struct Frame* pokeballParticleLoopPtr[] = {pokeballParticleLoop};


/*
	OAM DATA:

	priority: 0-3; 0=Highest

	affine_mode: 0=Normal, 1=Affine
	h_flip 1=flip horizontally
    v_flip 1=flip vertically

	shape: 0=Square,1=Horizontal,2=Vertical
	size:
     * Size  Square   Horizontal  Vertical
     * 0     8x8      16x8        8x16
     * 1     16x16    32x8        8x32
     * 2     32x32    32x16       16x32
     * 3     64x64    64x32       32x64
*/
