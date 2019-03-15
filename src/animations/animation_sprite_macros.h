#ifndef ANIMATION_SPRITE_MACROS_H_
#define ANIMATION_SPRITE_MACROS_H_

#include <pokeagb/pokeagb.h>

/* Size and shape related */
#define SQUARE 0
#define WIDE 1
#define TALL 2

#define o8x8 0
#define s8x8 1

#define o16x8 0
#define s16x8 2

#define o8x16 0
#define s8x16 2

#define o16x16 1
#define s16x16 4

#define o32x8 1
#define s32x8 4

#define o8x32 1
#define s8x32 4

#define o32x32 2
#define s32x32 16

#define o32x16 2
#define s32x16 8

#define o16x32 2
#define s16x32 8

#define o64x64 3
#define s64x64 64

#define o64x32 3
#define s64x32 32

#define o32x64 3
#define s32x64 32

/* Frame */
#define BEGIN_FRAME_ANIM(name) const struct Frame name ## A_N_I_M_F_R_A_M_E[];\
                               const struct Frame* name[] = {name ## A_N_I_M_F_R_A_M_E}; \
                               const struct Frame name ## A_N_I_M_F_R_A_M_E[] = {
#define HFLIP 1 << 7
#define VFLIP 1 << 6
#define HVFLIP 3 << 6
#define VHFLIP 3 << 6
#define NOFLIP 0
#define SHOW_FRAME(x, size, flips, duration) {x * size, flips | duration},
#define JUMP_FRAME(x) {0xFFFE, x},
#define LOOP_FRAME(times) {0xFFFD, times},
#define STOP_ANIM() {0xFFFF, 0},
#define END_ANIM() {0xFFFF, 0},};

/* Sprite and Palette */
#define ASSETS(name, size, tag) const struct CompressedSpriteSheet name ##Sprite = {(void*)&name ## Tiles, size * 32, tag}; \
                                const struct SpritePalette name ## Palette = {&name ## Pal, tag}

#define ASSET_ALIAS(name, size, tag, prefname) const struct CompressedSpriteSheet prefname ##Sprite = {(void*)&name ## Tiles, size * 32, tag}; \
                                const struct SpritePalette prefname ## Palette = {&name ## Pal, tag}


/* OAM */
#define MAKE_OAM(name) const struct OamData name ## Oam = {
#define OAM_PRIORITY(p) .priority = p,
#define OAM_SIZE(s) .size = s,
#define OAM_AFFINE() .affine_mode = 1,
#define OAM_HFLIP() .h_flip = 1,
#define OAM_VFLIP() .v_flip = 1,
#define OAM_SHAPE(shp) .shape = shp,
#define END_OAM() };

/* Affine */
#define BEGIN_AFFINE_ANIM(name) const struct RotscaleFrame name ## AffineTable[];\
                                const u32 name ## Affine = (u32)&name ## AffineTable; \
                                const struct RotscaleFrame name ## AffineTable[] = {
#define PLAY_AFFINE(x, y, rot, dur) {x, y, rot, dur, 0},
#define LOOP_AFFINE(x) {0x7FFD, x, 0, 0, 0},
#define JUMP_AFFINE(x) {0x7FFE, x, 0, 0, 0},
#define END_AFFINE() {0x7FFF, 0, 0, 0, 0},};

#endif /* ANIMATION_SPRITE_MACROS_H_ */
