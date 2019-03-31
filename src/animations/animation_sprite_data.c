#include <pokeagb/pokeagb.h>
#include "animation_sprite_macros.h"
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
#include "../../generated/images/battle_animations/guillotine.h"
#include "../../generated/images/battle_animations/guillotineLeft.h"
#include "../../generated/images/battle_animations/tornadopiece.h"
#include "../../generated/images/battle_animations/impact3.h"
#include "../../generated/images/battle_animations/blueglowball.h"
#include "../../generated/images/battle_animations/sword.h"
#include "../../generated/images/battle_animations/smokeball.h"
#include "../../generated/images/battle_animations/smallrockcircle.h"
#include "../../generated/images/battle_animations/feather.h"
#include "../../generated/images/battle_animations/impact4.h"
#include "../../generated/images/battle_animations/flybg.h"
#include "../../generated/images/battle_animations/fly.h"
#include "../../generated/images/battle_animations/bind.h"
#include "../../generated/images/battle_animations/vinewhip.h"
#include "../../generated/images/battle_animations/leafblades.h"
#include "../../generated/images/battle_animations/stomp.h"
#include "../../generated/images/battle_animations/impact5.h"
#include "../../generated/images/battle_animations/megakickbg.h"
#include "../../generated/images/battle_animations/megakickplayerbg.h"
#include "../../generated/images/battle_animations/sandattack.h"
#include "../../generated/images/battle_animations/star.h"
#include "../../generated/images/battle_animations/horn.h"
#include "../../generated/images/battle_animations/furyattack.h"
#include "../../generated/images/battle_animations/impact6.h"
#include "../../generated/images/battle_animations/impact7.h"
#include "../../generated/images/battle_animations/wrap.h"
#include "../../generated/images/battle_animations/crosspoison.h"
#include "../../generated/images/battle_animations/confuseray.h"
#include "../../generated/images/battle_animations/innerray.h"
#include "../../generated/images/battle_animations/nightshade.h"
#include "../../generated/images/battle_animations/squarefist.h"
#include "../../generated/images/battle_animations/doubleedgebg_opponent.h"
#include "../../generated/images/battle_animations/doubleedgebg_player.h"
#include "../../generated/images/battle_animations/poisonsting.h"
#include "../../generated/images/battle_animations/pinmissile.h"
#include "../../generated/images/battle_animations/leer.h"
#include "../../generated/images/battle_animations/growl.h"
#include "../../generated/images/battle_animations/buffcircle.h"
#include "../../generated/images/battle_animations/notes.h"
#include "../../generated/images/battle_animations/supersonic.h"
#include "../../generated/images/battle_animations/aquajet.h"
#include "../../generated/images/battle_animations/sonicboom.h"


/* the impact sprite from tackle */
ASSETS(impact1, s32x32, 400);

MAKE_OAM(impact1)
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
END_OAM()


/* the burn animation sprite */
ASSETS(burn, s16x32, 401);

MAKE_OAM(burn)
    OAM_AFFINE()
    OAM_SHAPE(TALL)
    OAM_SIZE(o16x32)
    OAM_PRIORITY(1)
END_OAM()

// burn sprite to shrink
BEGIN_AFFINE_ANIM(burn)
    PLAY_AFFINE(-20, -20, 0, 10)
END_AFFINE()


/* poison ailment sprite */
ASSETS(poison, s16x16, 402);

MAKE_OAM(poison)
    OAM_SIZE(o16x16)
    OAM_PRIORITY(1)
END_OAM()


/* paralyze ailment sprite */
ASSETS(paralyze, s32x32 * 3, 403);

MAKE_OAM(paralyze)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(paralyzeFrames)
    SHOW_FRAME(0, s32x16, NOFLIP, 5)
    SHOW_FRAME(1, s32x16, NOFLIP, 5)
    SHOW_FRAME(4, s32x8, NOFLIP, 5)
    SHOW_FRAME(5, s32x8, NOFLIP, 5)
    SHOW_FRAME(6, s32x8, NOFLIP, 5)
    SHOW_FRAME(8, s32x8, NOFLIP, 5)
    JUMP_FRAME(0)
END_ANIM()


/* freeze ailment sprite */
ASSETS(freeze, s32x32, 404);

MAKE_OAM(freeze)
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
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
ASSETS(confused, s16x16 * 3, 405);

MAKE_OAM(confused)
    OAM_PRIORITY(1)
    OAM_SIZE(o16x16)
END_OAM()

BEGIN_FRAME_ANIM(confusedFrames)
    SHOW_FRAME(0, s16x16, NOFLIP, 20)
    SHOW_FRAME(1, s16x16, NOFLIP, 20)
    SHOW_FRAME(2, s16x16, NOFLIP, 20)
    JUMP_FRAME(0)
END_ANIM()


/* infactuation sprite */
ASSETS(infactuation, s16x16, 406);

MAKE_OAM(infactuation)
    OAM_SIZE(o16x16)
    OAM_PRIORITY(1)
END_OAM()


/* Sleep sprite */
ASSETS(sleep, s32x32, 407);

MAKE_OAM(sleep)
    OAM_AFFINE()
    OAM_SIZE(o32x32)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_AFFINE_ANIM(sleep)
    PLAY_AFFINE(-150, -150, -30, 1)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 0, 8)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 0, 8)
    PLAY_AFFINE(2, 2, 2, 5)
    PLAY_AFFINE(0, 0, 0, 8)
END_AFFINE()


/* Smoke sprite */
ASSETS(smoke, s32x32 * 3, 408);

MAKE_OAM(smoke)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(smokeFrames)
    SHOW_FRAME(0, s32x32, NOFLIP, 5)
    SHOW_FRAME(1, s32x32, NOFLIP, 5)
    SHOW_FRAME(2, s32x32, NOFLIP, 5)
END_ANIM()


/* glowball sprite */
ASSETS(glowball, s16x16, 409);

MAKE_OAM(glowball)
    OAM_AFFINE()
    OAM_SIZE(o16x16)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_AFFINE_ANIM(glowball)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(-10, -10, 0, 30)
END_AFFINE()

BEGIN_AFFINE_ANIM(glowball2)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(-10, -10, 0, 20)
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
ASSETS(pokeball, s16x16 * 3, 410);

MAKE_OAM(pokeball)
    OAM_AFFINE()
    OAM_SIZE(o16x16)
    OAM_PRIORITY(1)
END_OAM()

const struct Frame pokeballOpen[] = {
    SHOW_FRAME(0, s16x16, NOFLIP, 5)
    SHOW_FRAME(1, s16x16, NOFLIP, 5)
    STOP_ANIM()
};

const struct Frame pokeballClose[] = {
    SHOW_FRAME(1, s16x16, NOFLIP, 5)
    SHOW_FRAME(0, s16x16, NOFLIP, 5)
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
ASSETS(impact2, s32x32, 411);

MAKE_OAM(impact2)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(3)
END_OAM()


/* Pokeball particles when opened or closed */
ASSETS(pokeballParticle, s8x8 * 3, 412);

MAKE_OAM(pokeballParticle)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(pokeballParticleFrames)
    SHOW_FRAME(0, s8x8, NOFLIP, 5)
    SHOW_FRAME(1, s8x8, NOFLIP, 5)
    SHOW_FRAME(2, s8x8, NOFLIP, 5)
    JUMP_FRAME(0)
END_ANIM()


/* Pokeball capture sucess stars particle */
ASSETS(starParticle, s8x8, 413);

MAKE_OAM(starParticle)
END_OAM()


/* Yes no choice box for..whatever choices */
ASSETS(yesno, s64x64, 414);

MAKE_OAM(yesno)
    OAM_SIZE(o64x64)
    OAM_PRIORITY(1)
END_OAM()


/* a cursor meant for the yesno box */
ASSETS(yesnoCursor, s16x16, 415);

MAKE_OAM(yesnoCursor)
    OAM_SIZE(o16x16)
    OAM_PRIORITY(0)
END_OAM()


/* fist sprite */
ASSETS(fist, s32x32, 416);

MAKE_OAM(fist)
    OAM_PRIORITY(3)
    OAM_AFFINE()
    OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(fist2)
    OAM_PRIORITY(1)
    OAM_AFFINE()
    OAM_SIZE(o32x32)
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
ASSETS(circular, s16x16, 417);

MAKE_OAM(circular)
    OAM_AFFINE()
    OAM_PRIORITY(3)
    OAM_SIZE(o16x16)
END_OAM()

BEGIN_AFFINE_ANIM(circular)
    PLAY_AFFINE(8, 8, 0, 32)
END_AFFINE()


/* the impact sprite from tackle - but white for blendability */
ASSETS(bimpact1, s32x32, 418);

MAKE_OAM(bimpact1)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(3)
END_OAM()


/* a splash of dispersing water */
ASSETS(watersplash, s64x64 * 4, 419);

MAKE_OAM(watersplash)
    OAM_SIZE(o64x64)
    OAM_PRIORITY(2)
END_OAM()

BEGIN_FRAME_ANIM(watersplashFrames)
    SHOW_FRAME(0, s64x64, NOFLIP, 5)
    SHOW_FRAME(1, s64x64, NOFLIP, 5)
    SHOW_FRAME(2, s64x64, NOFLIP, 5)
    SHOW_FRAME(3, s64x64, NOFLIP, 5)
    JUMP_FRAME(0)
END_ANIM()


/* Chop hand from Karate chop */
ASSETS(chop, s32x32 * 2, 420);

MAKE_OAM(chop)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(1)
END_OAM()

BEGIN_FRAME_ANIM(chopLeftFrames)
    SHOW_FRAME(1, 16, NOFLIP, 1)
END_ANIM()


/* Slap hand from double slap */
ASSETS(slap, s32x32 * 3, 421);

MAKE_OAM(slap)
    OAM_SIZE(o32x32)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(slapFrames)
    SHOW_FRAME(0, s32x32, NOFLIP, 12)
    SHOW_FRAME(1, s32x32, NOFLIP, 4)
    SHOW_FRAME(2, s32x32, NOFLIP, 12)
    SHOW_FRAME(2, s32x32, NOFLIP, 12)
    SHOW_FRAME(1, s32x32, NOFLIP, 4)
    SHOW_FRAME(0, s32x32, NOFLIP, 12)
END_ANIM()


/* Big red fist from mega punch, and blue fist from ice punch */
ASSETS(bigfist, s64x64, 422);
ASSETS(bigbluefist, s64x64, 424);

MAKE_OAM(bigfist)
    OAM_AFFINE()
    OAM_SIZE(o64x64)
    OAM_PRIORITY(2)
END_OAM()

BEGIN_AFFINE_ANIM(bigfistShrink)
    PLAY_AFFINE(-140, -140, 0, 1)
END_AFFINE()


/* The small fire from fire punch */
ASSETS(smallfire, s16x32 * 4, 423);

MAKE_OAM(smallfire)
    OAM_SHAPE(TALL)
    OAM_SIZE(o16x32)
    OAM_PRIORITY(2)
END_OAM()

MAKE_OAM(smallfireAff)
    OAM_AFFINE()
    OAM_SHAPE(TALL)
    OAM_SIZE(o16x32)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(smallfireFrames)
    SHOW_FRAME(0, s16x32, NOFLIP, 5)
    SHOW_FRAME(1, s16x32, NOFLIP, 5)
    SHOW_FRAME(2, s16x32, NOFLIP, 5)
    SHOW_FRAME(3, s16x32, NOFLIP, 5)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_AFFINE_ANIM(smallfire)
    PLAY_AFFINE(-6, -6, 0, 20)
END_AFFINE()


/* Lightning bolt */
ASSETS(lightningbolt, s32x32 * 2, 425);

MAKE_OAM(lightningbolt)
    OAM_AFFINE()
    OAM_SIZE(o32x32)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_FRAME_ANIM(lightningboltFrames)
    SHOW_FRAME(0, s32x32, NOFLIP, 2)
    SHOW_FRAME(1, s32x32, NOFLIP, 2)
    JUMP_FRAME(0)
END_ANIM()


/* Yellow fist sprite from thunder punch */
ASSETS(yellowfist, s64x64, 426);

MAKE_OAM(yellowfist)
    OAM_AFFINE()
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(bigfistShrinkSlowly)
    PLAY_AFFINE(0, 0, 0, 8)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(0, 0, 0, 28)
END_AFFINE()


/* Vicegrip graphic */
ASSETS(vicegrip, s32x32 * 4, 427);

MAKE_OAM(vicegrip)
    OAM_PRIORITY(2)
    OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(vicegripFlip)
    OAM_PRIORITY(2)
    OAM_HFLIP()
    OAM_VFLIP()
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_FRAME_ANIM(vicegripFrame)
    SHOW_FRAME(0, s32x32, NOFLIP, 2)
    SHOW_FRAME(1, s32x32, NOFLIP, 2)
    SHOW_FRAME(2, s32x32, NOFLIP, 2)
END_ANIM()

BEGIN_FRAME_ANIM(vicegripFlipFrame)
    SHOW_FRAME(0, s32x32, HVFLIP, 2)
    SHOW_FRAME(1, s32x32, HVFLIP, 2)
    SHOW_FRAME(2, s32x32, HVFLIP, 2)
END_ANIM()


/* Cut (borrows vicegrip graphic frames 1-3, skipping 0) */
MAKE_OAM(cut)
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_FRAME_ANIM(cutFrame)
    SHOW_FRAME(0, s32x32, NOFLIP, 4)
    SHOW_FRAME(1, s32x32, NOFLIP, 5)
    SHOW_FRAME(2, s32x32, NOFLIP, 6)
    SHOW_FRAME(3, s32x32, NOFLIP, 8)
END_ANIM()


/* Guillotine */
ASSETS(guillotine, s64x64, 428);
ASSETS(guillotineLeft, s64x64, 429);

MAKE_OAM(guillotine)
    OAM_AFFINE()
    OAM_PRIORITY(3)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(guillotineGrow)
    PLAY_AFFINE(-100, -140, 0, 1)
    PLAY_AFFINE(5, 7, 0, 20)
END_AFFINE()

BEGIN_AFFINE_ANIM(guillotineTiltLeft)
    PLAY_AFFINE(0, 0, 1, 40)
END_AFFINE()

BEGIN_AFFINE_ANIM(guillotineTiltRight)
    PLAY_AFFINE(0, 0, -1, 40)
END_AFFINE()


/* Razor wind whip up + whirlwind */
ASSETS(tornadopiece, s64x64 * 4, 430);

MAKE_OAM(tornadopiece)
    OAM_AFFINE()
    OAM_PRIORITY(2)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(tornadopieceTransparent)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SEMI_TRANSPARENT()
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(tornadopieceTransparentAttack)
    OAM_PRIORITY(1)
    OAM_SEMI_TRANSPARENT()
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(tornadopieceAttack)
    OAM_PRIORITY(2)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_FRAME_ANIM(tornadopieceFrame)
    SHOW_FRAME(0, s64x64, NOFLIP, 3)
    SHOW_FRAME(1, s64x64, NOFLIP, 3)
    SHOW_FRAME(2, s64x64, NOFLIP, 3)
    SHOW_FRAME(3, s64x64, NOFLIP, 3)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(tornadopieceSlowerFrame)
    SHOW_FRAME(0, s64x64, NOFLIP, 4)
    SHOW_FRAME(1, s64x64, NOFLIP, 4)
    SHOW_FRAME(2, s64x64, NOFLIP, 4)
    SHOW_FRAME(3, s64x64, NOFLIP, 4)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(tornadopieceSlowestFrame)
    SHOW_FRAME(0, s64x64, NOFLIP, 5)
    SHOW_FRAME(1, s64x64, NOFLIP, 5)
    SHOW_FRAME(2, s64x64, NOFLIP, 5)
    SHOW_FRAME(3, s64x64, NOFLIP, 5)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_AFFINE_ANIM(tornadopiece)
    PLAY_AFFINE(180, 180, 0, 1)
    PLAY_AFFINE(-12, -12, 0, 30)
    PLAY_AFFINE(0, 0, 0, 4)
    PLAY_AFFINE(12, 12, 0, 30)
END_AFFINE()

BEGIN_AFFINE_ANIM(tornadoInner)
    PLAY_AFFINE(-100, -100, 0, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(tornadoSmall)
    PLAY_AFFINE(-50, -50, 0, 1)
END_AFFINE()


/* Impact3 particle (small 16x16) */
ASSETS(impact3, s16x16, 431);

MAKE_OAM(impact3)
    OAM_PRIORITY(2)
    OAM_SIZE(o16x16)
END_OAM()


/* Glowball particle from swords dance */
ASSETS(blueglowball, s16x16, 432);

MAKE_OAM(blueglowball)
    OAM_PRIORITY(3)
    OAM_SIZE(o16x16)
END_OAM()


/* Swords dance sword */
ASSETS(sword, s32x64, 433);

MAKE_OAM(sword)
    OAM_AFFINE()
    OAM_PRIORITY(2)
    OAM_SHAPE(TALL)
    OAM_SIZE(o32x64)
END_OAM()

BEGIN_AFFINE_ANIM(sword)
    PLAY_AFFINE(-200, -200, 0, 1)
    PLAY_AFFINE(10, 10, 0, 20)
END_AFFINE()


/* Smokeball from gust */
ASSETS(smokeball, s32x32, 434);

MAKE_OAM(smokeball)
    OAM_AFFINE()
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_AFFINE_ANIM(smokeball)
    PLAY_AFFINE(-80, -80, 0, 1)
    PLAY_AFFINE(3, 3, 4, 8)
    PLAY_AFFINE(-3, -3, -4, 8)
    JUMP_AFFINE(1)
END_AFFINE()


/* Small rock debris */
ASSETS(smallrockcircle, s8x8, 435);

MAKE_OAM(smallrockcircle)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o8x8)
END_OAM()

BEGIN_AFFINE_ANIM(smallrockcircle)
    PLAY_AFFINE(-8, -8, 0, 20)
END_AFFINE()


/* Feather particle from Wing Attack */
ASSETS(feather, s32x16 * 5, 436);

MAKE_OAM(feather)
    OAM_PRIORITY(1)
    OAM_SIZE(o32x16)
    OAM_SHAPE(WIDE)
END_OAM()

BEGIN_FRAME_ANIM(featherFrame)
    SHOW_FRAME(0, s32x16, NOFLIP, 16)
    SHOW_FRAME(1, s32x16, NOFLIP, 16)
    SHOW_FRAME(2, s32x16, NOFLIP, 16)
    SHOW_FRAME(3, s32x16, NOFLIP, 16)
    SHOW_FRAME(4, s32x16, NOFLIP, 16)
    SHOW_FRAME(0, s32x16, NOFLIP, 16)
    SHOW_FRAME(1, s32x16, NOFLIP, 8)
    SHOW_FRAME(4, s32x16, NOFLIP, 4)
END_ANIM()


/* Impact sprite medium sized */
ASSETS(impact4, s32x32, 437);
ASSET_ALIAS(impact4, s32x32, 438, impact4_2);
ASSET_ALIAS(impact4, s32x32, 439, impact4_3);

MAKE_OAM(impact4)
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
END_OAM()


/* Fly sprite */
ASSETS(fly, s64x64, 440);

MAKE_OAM(fly)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(fly)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(10, 10, 0, 10)
    PLAY_AFFINE(-10, -10, 0, 10)
END_AFFINE()

BEGIN_AFFINE_ANIM(flySquish)
    PLAY_AFFINE(-100, -100, 0, 1)
    PLAY_AFFINE(0, 3, 0, 40)
END_AFFINE()

BEGIN_AFFINE_ANIM(flySmall)
    PLAY_AFFINE(-80, -80, 0, 1)
END_AFFINE()


/* Bind wrap sprite */
ASSETS(bind, s64x64, 441);

MAKE_OAM(bind)
    OAM_AFFINE()
    OAM_PRIORITY(2)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(bind)
    PLAY_AFFINE(-8, 0, 0, 10)
    PLAY_AFFINE(20, 0, 0, 4)
    LOOP_AFFINE(1)
END_AFFINE()


/* Vine whip sprite */
ASSETS(vinewhip, s64x64 * 4, 442);

MAKE_OAM(vinewhip)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_FRAME_ANIM(vinewhipFrames)
    SHOW_FRAME(0, s64x64, NOFLIP, 4)
    SHOW_FRAME(1, s64x64, NOFLIP, 4)
    SHOW_FRAME(2, s64x64, NOFLIP, 3)
    SHOW_FRAME(3, s64x64, NOFLIP, 2)
END_ANIM()

BEGIN_AFFINE_ANIM(vinewhip)
    PLAY_AFFINE(10, 10, 0, 13)
END_AFFINE()


/* Leaf blades sprite */
ASSETS(leafblades, s32x32 * 6, 443);

MAKE_OAM(leafblades)
    OAM_PRIORITY(2)
    OAM_SIZE(o32x32)
END_OAM()


/* Stomp foot sprite, also used in double kick, megakick, thrash */
ASSETS(stomp, s64x64 * 2, 444);

MAKE_OAM(stomp)
    OAM_PRIORITY(2)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(doublekick)
    OAM_AFFINE()
    OAM_PRIORITY(2)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(thrashfoot)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(stompSquish) // affine is applied to the target
    PLAY_AFFINE(0, -60, 0, 1)
    PLAY_AFFINE(0, 0, 0, 19)
    PLAY_AFFINE(0, 60, 0, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(doublekickBig) // affine on outter foot
    PLAY_AFFINE(200, 200, 0, 1)
    PLAY_AFFINE(-60, -60, 0, 4)
END_AFFINE()

BEGIN_FRAME_ANIM(doublekickFrames)
    SHOW_FRAME(1, s64x64, NOFLIP, 1)
END_ANIM()

BEGIN_AFFINE_ANIM(megakickGrow) // affine on outter foot
    PLAY_AFFINE(10, 10, 0, 20)
END_AFFINE()


/* Impact5 sprite, big red impact */
ASSETS(impact5, s64x64, 445);

MAKE_OAM(impact5)
    OAM_PRIORITY(3)
    OAM_SIZE(o64x64)
END_OAM()


/* Sand attack dust sprite */
ASSETS(sandattack, s32x32 * 5, 446);

MAKE_OAM(sandattack)
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_FRAME_ANIM(sandattackFrames)
    SHOW_FRAME(0, s32x32, NOFLIP, 5)
    SHOW_FRAME(1, s32x32, NOFLIP, 5)
    SHOW_FRAME(2, s32x32, NOFLIP, 4)
    SHOW_FRAME(3, s32x32, NOFLIP, 3)
    SHOW_FRAME(4, s32x32, NOFLIP, 2)
END_ANIM()


/* Headbutt star sprite */
ASSETS(star, s16x16, 447);

MAKE_OAM(star)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o16x16)
END_OAM()

BEGIN_AFFINE_ANIM(star)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(-8, -8, 0, 16)
END_AFFINE()


/* Horn attack horn sprite */
ASSETS(horn, s32x32, 448);

MAKE_OAM(horn)
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(hornFlipped)
    OAM_VFLIP()
    OAM_HFLIP()
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()


/* Fury attack orange spike sprite */
ASSETS(furyattack, s32x32, 449);

MAKE_OAM(furyattack)
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(furyattackFlipped)
    OAM_PRIORITY(1)
    OAM_HFLIP()
    OAM_VFLIP()
    OAM_SIZE(o32x32)
END_OAM()


/* Impact6 and impact7 sprite used in horndrill and slam */
ASSETS(impact6, s64x64, 450);
ASSETS(impact7, s64x64, 451);

MAKE_OAM(impact6)
    OAM_AFFINE()
    OAM_PRIORITY(0)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(impact7)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(impact6Original)
    OAM_PRIORITY(0)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(impact7Original)
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(impact6)
    PLAY_AFFINE(0, 0, 3, 30)
    PLAY_AFFINE(0, 0, 3, 30)
END_AFFINE()

BEGIN_AFFINE_ANIM(impact7)
    PLAY_AFFINE(0, 0, 5, 30)
    PLAY_AFFINE(0, 0, 5, 30)
END_AFFINE()

BEGIN_AFFINE_ANIM(impact7Thrash)
    PLAY_AFFINE(0, 0, 0, 1)
    PLAY_AFFINE(60, 60, 0, 3)
END_AFFINE()

MAKE_OAM(impact6Slam)
    OAM_AFFINE()
    OAM_SIZE(o64x64)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_AFFINE_ANIM(impact6Slam)
    PLAY_AFFINE(20, -80, 0, 1)
    PLAY_AFFINE(-10, -10, 0, 10)
END_AFFINE()




/* Wrap effect */
ASSETS(wrap, s64x64 * 4, 452);

MAKE_OAM(wrap)
    OAM_PRIORITY(0)
    OAM_SIZE(o64x64)
END_OAM()

MAKE_OAM(wrapFlipped)
    OAM_VFLIP()
    OAM_PRIORITY(0)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_FRAME_ANIM(wrapFrames)
    SHOW_FRAME(0, s64x64, NOFLIP, 3)
    SHOW_FRAME(1, s64x64, NOFLIP, 4)
    SHOW_FRAME(2, s64x64, NOFLIP, 4)
    SHOW_FRAME(3, s64x64, NOFLIP, 5)
END_ANIM()

BEGIN_FRAME_ANIM(wrapFlippedFrames)
    SHOW_FRAME(0, s64x64, VFLIP, 3)
    SHOW_FRAME(1, s64x64, VFLIP, 4)
    SHOW_FRAME(2, s64x64, VFLIP, 4)
    SHOW_FRAME(3, s64x64, VFLIP, 5)
END_ANIM()

BEGIN_AFFINE_ANIM(wrap) // applied to wrap target
    PLAY_AFFINE(-10, 0, 0, 3)
    PLAY_AFFINE(0, 0, 0, 3)
    PLAY_AFFINE(10, 0, 0, 3)
    PLAY_AFFINE(0, 0, 0, 3)

    PLAY_AFFINE(-10, 0, 0, 3)
    PLAY_AFFINE(0, 0, 0, 3)
    PLAY_AFFINE(10, 0, 0, 3)
    PLAY_AFFINE(0, 0, 0, 3)
END_AFFINE()


/* bimpact1 sprite transformed for pound */
MAKE_OAM(impactSmall)
    OAM_AFFINE()
    OAM_PRIORITY(3)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_AFFINE_ANIM(impactSmall)
    PLAY_AFFINE(-100, -100, 0, 1)
END_AFFINE()


/* Cross Poison */
ASSETS(crosspoison, s32x32, 453);

MAKE_OAM(crosspoison)
	OAM_PRIORITY(3)
	OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(crosspoisonFlip)
	OAM_PRIORITY(3)
	OAM_HFLIP()
	OAM_SIZE(o32x32)
END_OAM()

/* confuse ray sprite */
ASSETS(confuseray, s32x32, 453);
ASSETS(innerray, s16x16, 454);

MAKE_OAM(confuseray)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

MAKE_OAM(innerray)
    OAM_AFFINE()
    OAM_PRIORITY(0)
    OAM_SIZE(o16x16)
END_OAM()

BEGIN_AFFINE_ANIM(confuseray)
    PLAY_AFFINE(-5, -5, 0, 16)
    PLAY_AFFINE(0, 0, 0, 4)
    PLAY_AFFINE(5, 5, 0, 16)
    PLAY_AFFINE(0, 0, 0, 4)
    JUMP_AFFINE(0)
END_AFFINE()


/* Square fist sprite */
ASSETS(squarefist, s64x64, 455);

MAKE_OAM(squarefist)
    .affine_mode = 3,
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()

BEGIN_AFFINE_ANIM(squarefist)
    PLAY_AFFINE(0, 0, 20, 1)
END_AFFINE()


/* Poisonsting barb */
ASSETS(poisonsting, s16x16, 456);

MAKE_OAM(poisonsting)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o16x16)
END_OAM()


/* Pinmissile barb */
ASSETS(pinmissile, s16x16, 457);

MAKE_OAM(pinmissile)
    OAM_AFFINE()
    OAM_PRIORITY(0)
    OAM_SIZE(o16x16)
END_OAM()


/* Leer glisten sprite */
ASSETS(leer, s32x32 * 5, 458);

MAKE_OAM(leer)
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_FRAME_ANIM(leerFrames)
    SHOW_FRAME(0, s32x32, NOFLIP, 4)
    SHOW_FRAME(1, s32x32, NOFLIP, 4)
    SHOW_FRAME(2, s32x32, NOFLIP, 8)
    SHOW_FRAME(3, s32x32, NOFLIP, 6)
    SHOW_FRAME(4, s32x32, NOFLIP, 3)
END_ANIM()


/* Growl roar particle */
ASSETS(growl, s32x32, 459);

MAKE_OAM(growl)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_AFFINE_ANIM(growlTop) // straight up
    PLAY_AFFINE(0, 0, 128, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlLeft) // 45 degrees left
    PLAY_AFFINE(0, 0, 160, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlRight) // 315 degrees right (45 degrees right)
    PLAY_AFFINE(0, 0, 96, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlHorizontal) // 90 degrees
    PLAY_AFFINE(0, 0, 64, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlDownRight) // 135 degrees
    PLAY_AFFINE(0, 0, 32, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlDiagonalRight)
    PLAY_AFFINE(0, 0, 96, 1)
END_AFFINE()

BEGIN_AFFINE_ANIM(growlDiagonalRightUp)
    PLAY_AFFINE(0, 0, 48, 1)
END_AFFINE()


/* Buff circle sprite that grows */
ASSETS(buffcircle, s64x64, 460);

MAKE_OAM(buffcircle)
    OAM_AFFINE()
    OAM_PRIORITY(1)
    OAM_SIZE(o64x64)
END_OAM()


/* Sing music notes */
ASSETS(notes, s16x16 * 6, 461);
ASSET_ALIAS(notes, s16x16 * 6, 462, notes2);
ASSET_ALIAS(notes, s16x16 * 6, 463, notes3);

MAKE_OAM(notes)
    OAM_PRIORITY(1)
    OAM_SEMI_TRANSPARENT()
    OAM_SIZE(o16x16)
END_OAM()

BEGIN_FRAME_ANIM(note1Frame)
    SHOW_FRAME(0, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(note2Frame)
    SHOW_FRAME(1, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(note3Frame)
    SHOW_FRAME(2, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(note4Frame)
    SHOW_FRAME(3, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(note5Frame)
    SHOW_FRAME(4, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_FRAME_ANIM(note6Frame)
    SHOW_FRAME(5, s16x16, NOFLIP, 30)
    JUMP_FRAME(0)
END_ANIM()


/* Supersonic circle sprite */
ASSETS(supersonic, s16x32, 464);

MAKE_OAM(supersonic)
    OAM_AFFINE()
    OAM_SHAPE(TALL)
    OAM_SIZE(o16x32)
    OAM_PRIORITY(3)
END_OAM()

BEGIN_AFFINE_ANIM(supersonic)
    PLAY_AFFINE(-150, -150, 0, 1)
    PLAY_AFFINE(5, 5, 0, 30)
END_AFFINE()


/* Aqua Jet */
ASSETS(aquajet, s64x64 * 4, 465);

MAKE_OAM(aquajet)
	OAM_PRIORITY(3)
	OAM_SIZE(o64x64)
END_OAM()

BEGIN_FRAME_ANIM(aquajetFrames)
    SHOW_FRAME(0, s64x64, NOFLIP, 3)
    SHOW_FRAME(1, s64x64, NOFLIP, 3)
    SHOW_FRAME(2, s64x64, NOFLIP, 3)
    SHOW_FRAME(3, s64x64, NOFLIP, 3)
	JUMP_FRAME(0)
END_ANIM()


/* Sonicboom sprite */
ASSETS(sonicboom, s32x32 * 2, 466);

MAKE_OAM(sonicboom)
    OAM_AFFINE()
    OAM_PRIORITY(2)
    OAM_SIZE(o32x32)
END_OAM()

BEGIN_FRAME_ANIM(sonicboomOpponent)
    SHOW_FRAME(1, s32x32, NOFLIP, 50)
    JUMP_FRAME(0)
END_ANIM()

BEGIN_AFFINE_ANIM(sonicboom)
    PLAY_AFFINE(-160, -160, 0, 1)
    PLAY_AFFINE(8, 8, 0, 20)
END_AFFINE()
