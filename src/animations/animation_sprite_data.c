#include <pokeagb\pokeagb.h>
#include "../../generated/images/battle_animations/impact1.h"
#include "../../generated/images/battle_animations/burn.h"
#include "../../generated/images/battle_animations/poison.h"
#include "../../generated/images/battle_animations/paralyze.h"
#include "../../generated/images/battle_animations/freeze.h"
#include "../../generated/images/battle_animations/confused.h"
#include "../../generated/images/battle_animations/infactuation.h"
#include "../../generated/images/battle_animations/sleep.h"
#include "../../generated/images/battle_animations/smoke.h"
#include "../../generated/images/battle_animations/glowball.h"
#include "../../generated/images/battle_animations/pokeball.h"
#include "../../generated/images/battle_animations/impact2.h"
#include "../../generated/images/battle_animations/impact2.h"
#include "../../generated/images/battle_animations/pokeballParticle.h"
#include "../../generated/images/battle_animations/starParticle.h"
#include "../../generated/images/battle_animations/yesno.h"
#include "../../generated/images/battle_animations/yesnoCursor.h"
#include "../../generated/images/battle_animations/fist.h"
#include "../../generated/images/battle_animations/circular.h"
#include "../../generated/images/battle_animations/bimpact1.h"
#include "../../generated/images/battle_animations/watersplash.h"
#include "../../generated/images/battle_animations/chop.h"
#include "../../generated/images/battle_animations/slap.h"
#include "../../generated/images/battle_animations/bigfist.h"
#include "../../generated/images/battle_animations/smallfire.h"
#include "../../generated/images/battle_animations/bigbluefist.h"
#include "../../generated/images/battle_animations/lightningbolt.h"
#include "../../generated/images/battle_animations/yellowfist.h"
#include "../../generated/images/battle_animations/vicegrip.h"


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


/* the impact sprite from tackle */
ASSETS(impact1, 4 * 4, 400);

MAKE_OAM(impact1)
    OAM_PRIORITY(3)
    OAM_SIZE(2)
END_OAM()


/* the burn animation sprite */
ASSETS(burn, 2 * 4, 401);

MAKE_OAM(burn)
    OAM_AFFINE()
    OAM_SHAPE(TALL)
    OAM_SIZE(2)
    OAM_PRIORITY(1)
END_OAM()

// burn sprite to shrink
BEGIN_AFFINE_ANIM(burn)
    PLAY_AFFINE(-20, -20, 0, 10)
END_AFFINE()


/* poison ailment sprite */
ASSETS(poison, 2 * 2, 402);

MAKE_OAM(poison)
    OAM_SIZE(1)
    OAM_PRIORITY(1)
END_OAM()


/* paralyze ailment sprite */
ASSETS(paralyze, 4 * 4 * 3, 403);

MAKE_OAM(paralyze)
    OAM_SIZE(2)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(paralyzeFrames)
    SHOW_FRAME(0, 8, 5)
    SHOW_FRAME(1, 8, 5)
    SHOW_FRAME(4, 4, 5)
    SHOW_FRAME(5, 4, 5)
    SHOW_FRAME(6, 4, 5)
    SHOW_FRAME(8, 4, 5)
    JUMP_FRAME(0)
END_ANIM()


/* freeze ailment sprite */
ASSETS(freeze, 4 * 4, 404);

MAKE_OAM(freeze)
    OAM_PRIORITY(3)
    OAM_SIZE(2)
    OAM_AFFINE()
END_OAM()

// freeze sprite to grow
BEGIN_AFFINE_ANIM(freeze)
    PLAY_AFFINE(-200, -200, 0, 1)
    PLAY_AFFINE(10, 10, 0, 15)
    PLAY_AFFINE(0, 0, 0, 10)
END_AFFINE()

// freeze sprite grow slow and rotate slow
BEGIN_AFFINE_ANIM(freeze2)
    PLAY_AFFINE(-200, -200, 0, 1)
    PLAY_AFFINE(5, 5, 5, 20)
END_AFFINE()


/* confused sprite */
ASSETS(confused, 2 * 2 * 3, 405);

MAKE_OAM(confused)
    OAM_PRIORITY(1)
    OAM_SIZE(1)
END_OAM()

BEGIN_FRAME_ANIM(confusedFrames)
    SHOW_FRAME(0, 4, 20)
    SHOW_FRAME(1, 4, 20)
    SHOW_FRAME(2, 4, 20)
    JUMP_FRAME(0)
END_ANIM()


/* infactuation sprite */
ASSETS(infactuation, 2 * 2, 406);

MAKE_OAM(infactuation)
    OAM_SIZE(1)
    OAM_PRIORITY(1)
END_OAM()


/* Sleep sprite */
ASSETS(sleep, 4 * 4, 407);

MAKE_OAM(sleep)
    OAM_AFFINE()
    OAM_SIZE(2)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_AFFINE_ANIM(sleep)
    PLAY_AFFINE(-150, -150, -30, 1)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 8, 0)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 8, 0)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 8, 0)
END_AFFINE()


/* Smoke sprite */
ASSETS(smoke, 4 * 4 * 3, 408);

MAKE_OAM(smoke)
    OAM_SIZE(2)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(smokeFrames)
    SHOW_FRAME(0, 16, 5)
    SHOW_FRAME(1, 16, 5)
    SHOW_FRAME(2, 16, 5)
END_ANIM()


/* glowball sprite */
ASSETS(glowball, 2 * 2, 409);

MAKE_OAM(glowball)
    OAM_AFFINE()
    OAM_SIZE(1)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_AFFINE_ANIM(glowball)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(-10, -10, 0, 30)
END_AFFINE()

BEGIN_AFFINE_ANIM(glowballSmaller)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(-10, -10, 0, 20)
END_AFFINE()

BEGIN_AFFINE_ANIM(glowballRev)
    PLAY_AFFINE(-300, -300, 0, 1)
    PLAY_AFFINE(10, 10, 0, 30)
END_AFFINE()


/* pokeball sprite */
ASSETS(pokeball, 2 * 2 * 3, 410);

MAKE_OAM(pokeball)
    OAM_AFFINE()
    OAM_SIZE(1)
    OAM_PRIORITY(1)
END_OAM()

const struct Frame pokeballOpen[] = {
    SHOW_FRAME(0, 4, 5)
    SHOW_FRAME(1, 4, 5)
    STOP_ANIM()
};

const struct Frame pokeballClose[] = {
    SHOW_FRAME(1, 4, 5)
    SHOW_FRAME(0, 4, 5)
    STOP_ANIM()
};

const struct Frame* pokeballFrames[] = {
    pokeballOpen,
    pokeballClose,
};
const struct Frame* pokeballOpenPtr[] = {pokeballOpen};

BEGIN_AFFINE_ANIM(pokeballLeftTilt)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(0, 0, -6, 5)
    PLAY_AFFINE(0, 0, 0, 5)
    PLAY_AFFINE(0, 0, 6, 5)
    PLAY_AFFINE(0, 0, 6, 3)
    PLAY_AFFINE(0, 0, 0, 3)
    PLAY_AFFINE(0, 0, -6, 3)
END_AFFINE()

BEGIN_AFFINE_ANIM(pokeballRightTilt)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(0, 0, 6, 5)
    PLAY_AFFINE(0, 0, 0, 5)
    PLAY_AFFINE(0, 0, -6, 5)
    PLAY_AFFINE(0, 0, -6, 3)
    PLAY_AFFINE(0, 0, 0, 3)
    PLAY_AFFINE(0, 0, 6, 3)
END_AFFINE()


/* impact2 sprite */
ASSETS(impact2, 4 * 4, 411);

MAKE_OAM(impact2)
    OAM_SIZE(2)
    OAM_PRIORITY(3)
END_OAM()


/* Pokeball particles when opened or closed */
ASSETS(pokeballParticle, 1 * 1 * 3, 412);

MAKE_OAM(pokeballParticle)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(pokeballParticleFrames)
    SHOW_FRAME(0, 1, 5)
    SHOW_FRAME(1, 1, 5)
    SHOW_FRAME(2, 1, 5)
    JUMP_FRAME(0)
END_ANIM()


/* Pokeball capture sucess stars particle */
ASSETS(starParticle, 1 * 1, 413);

MAKE_OAM(starParticle)
END_OAM()


/* Yes no choice box for..whatever choices */
ASSETS(yesno, 8 * 8, 414);

MAKE_OAM(yesno)
    OAM_SIZE(3)
    OAM_PRIORITY(1)
END_OAM()


/* a cursor meant for the yesno box */
ASSETS(yesnoCursor, 8 * 8, 415);

MAKE_OAM(yesnoCursor)
    OAM_SIZE(1)
    OAM_PRIORITY(0)
END_OAM()


/* fist sprite */
ASSETS(fist, 4 * 4, 416);

MAKE_OAM(fist)
    OAM_PRIORITY(3)
    OAM_AFFINE()
    OAM_SIZE(2)
END_OAM()

MAKE_OAM(fist2)
    OAM_PRIORITY(1)
    OAM_AFFINE()
    OAM_SIZE(2)
END_OAM ()

BEGIN_AFFINE_ANIM(fist)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(20, 20, 0, 8)
END_AFFINE()

BEGIN_AFFINE_ANIM(fist2)
    PLAY_AFFINE(0, 0, 3, 5)
END_AFFINE()

BEGIN_AFFINE_ANIM(fist3)
    PLAY_AFFINE(-450, -450, 0, 1)
    PLAY_AFFINE(6, 6, -7, 24)
END_AFFINE()


/* circular sprite */
ASSETS(circular, 2 * 2, 417);

MAKE_OAM(circular)
    OAM_AFFINE()
    OAM_PRIORITY(3)
    OAM_SIZE(1)
END_OAM()

BEGIN_AFFINE_ANIM(circular)
    PLAY_AFFINE(8, 8, 0, 32)
END_AFFINE()


/* the impact sprite from tackle - but white for blendability */
ASSETS(bimpact1, 4 * 4, 418);

MAKE_OAM(bimpact1)
    OAM_SIZE(2)
    OAM_PRIORITY(3)
END_OAM()


/* a splash of dispersing water */
ASSETS(watersplash, 8 * 8 * 4, 419);

MAKE_OAM(watersplash)
    OAM_SIZE(3)
    OAM_PRIORITY(2)
END_OAM()

BEGIN_FRAME_ANIM(watersplashFrames)
    SHOW_FRAME(0, 64, 5)
    SHOW_FRAME(1, 64, 5)
    SHOW_FRAME(2, 64, 5)
    SHOW_FRAME(3, 64, 5)
    JUMP_FRAME(0)
END_ANIM()


/* Chop hand from Karate chop */
ASSETS(chop, 4 * 4 * 2, 420);

MAKE_OAM(chop)
    OAM_SIZE(2)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(chopLeftFrames)
    SHOW_FRAME(1, 16, 1)
END_ANIM()


/* Slap hand from double slap */
ASSETS(slap, 4 * 4 * 3, 421);

MAKE_OAM(slap)
    OAM_SIZE(2)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(slapFrames)
    SHOW_FRAME(0, 16, 12)
    SHOW_FRAME(1, 16, 4)
    SHOW_FRAME(2, 16, 12)
    SHOW_FRAME(2, 16, 12)
    SHOW_FRAME(1, 16, 4)
    SHOW_FRAME(0, 16, 12)
END_ANIM()


/* Big red fist from mega punch, and blue fist from ice punch */
ASSETS(bigfist, 8 * 8, 422);
ASSETS(bigbluefist, 8 * 8, 424);

MAKE_OAM(bigfist)
    OAM_AFFINE()
    OAM_SIZE(3)
    OAM_PRIORITY(2)
END_OAM()

BEGIN_AFFINE_ANIM(bigfistShrink)
    PLAY_AFFINE(-140, -140, 0, 1)
END_AFFINE()


/* The small fire from fire punch */
ASSETS(smallfire, 2 * 4 * 4, 423);

MAKE_OAM(smallfire)
    OAM_SHAPE(TALL)
    OAM_SIZE(2)
    OAM_PRIORITY(2)
END_OAM()

MAKE_OAM(smallfireAff)
    OAM_AFFINE()
    OAM_SHAPE(TALL)
    OAM_SIZE(2)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(smallfireFrames)
    SHOW_FRAME(0, 8, 5)
    SHOW_FRAME(1, 8, 5)
    SHOW_FRAME(2, 8, 5)
    SHOW_FRAME(3, 8, 5)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_AFFINE_ANIM(smallfire)
    PLAY_AFFINE(-6, -6, 0, 20)
END_AFFINE()


/* Lightning bolt */
ASSETS(lightningbolt, 4 * 4 * 2, 425);

MAKE_OAM(lightningbolt)
    OAM_AFFINE()
    OAM_SIZE(2)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(lightningboltFrames)
    SHOW_FRAME(0, 16, 2)
    SHOW_FRAME(1, 16, 2)
    JUMP_FRAME(0)
END_ANIM()


/* Yellow fist sprite from thunder punch */
ASSETS(yellowfist, 8 * 8, 426);

MAKE_OAM(yellowfist)
    OAM_AFFINE()
    OAM_SIZE(3)
END_OAM()

BEGIN_AFFINE_ANIM(bigfistShrinkSlowly)
    PLAY_AFFINE(0, 0, 0, 8)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(0, 0, 0, 28)
END_AFFINE()


/* Vicegrip graphic */
ASSETS(vicegrip, 4 * 4, 427);

MAKE_OAM(vicegrip)
    OAM_PRIORITY(1)
    OAM_SIZE(2)
END_OAM()



/*
	OAM DATA:

    // priority 3 = all battlers
    // priority 2 = hp boxes
    // priority 1 free
    // priortiy 0 free
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
