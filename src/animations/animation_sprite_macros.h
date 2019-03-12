#ifndef ANIMATION_SPRITE_MACROS_H_
#define ANIMATION_SPRITE_MACROS_H_

#include <pokeagb/pokeagb.h>


#define BEGIN_FRAME_ANIM(name) const struct Frame name ## A_N_I_M_F_R_A_M_E[];\
                               const struct Frame* name[] = {name ## A_N_I_M_F_R_A_M_E}; \
                               const struct Frame name ## A_N_I_M_F_R_A_M_E[] = {
#define SHOW_FRAME(x, size, duration) {x * size, duration},
#define JUMP_FRAME(x) {0xFFFE, x},
#define LOOP_FRAME(times) {0xFFFD, times},
#define STOP_ANIM() {0xFFFF, 0},
#define END_ANIM() {0xFFFF, 0},};

#define ASSETS(name, size, tag) const struct CompressedSpriteSheet name ##Sprite = {(void*)&name ## Tiles, size * 32, tag}; \
                                const struct SpritePalette name ## Palette = {&name ## Pal, tag}

#define MAKE_OAM(name) const struct OamData name ## Oam = {
#define OAM_PRIORITY(p) .priority = p,
#define OAM_SIZE(s) .size = s,
#define OAM_AFFINE() .affine_mode = 1,
#define OAM_HFLIP() .h_flip = 1,
#define OAM_VFLIP() .v_flip = 1,
#define OAM_SHAPE(shp) .shape = shp,
#define END_OAM() };
#define SQUARE 0
#define WIDE 1
#define TALL 2

#define BEGIN_AFFINE_ANIM(name) const struct RotscaleFrame name ## AffineTable[];\
                                const u32 name ## Affine = (u32)&name ## AffineTable; \
                                const struct RotscaleFrame name ## AffineTable[] = {
#define PLAY_AFFINE(x, y, rot, dur) {x, y, rot, dur, 0},
#define LOOP_AFFINE(x) {0x7FFD, x, 0, 0, 0},
#define JUMP_AFFINE(x) {0x7FFE, x, 0, 0, 0},
#define END_AFFINE() {0x7FFF, 0, 0, 0, 0},};

#endif /* ANIMATION_SPRITE_MACROS_H_ */
