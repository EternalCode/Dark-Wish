#include <pokeagb\pokeagb.h>
#include "../../generated/images/battle_animations/impact1.h"

const struct CompressedSpriteSheet impact1Sprite = {(void*)&impact1Tiles, 32 * 4 * 4, 400};
const struct SpritePalette impact1Palette = {&impact1Pal, 400};

const struct OamData impact1Oam = {
    .size = 2,
    .priority = 3,
};
