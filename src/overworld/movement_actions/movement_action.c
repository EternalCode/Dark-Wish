#include <pokeagb/pokeagb.h>
#include "../../global.h"

// struct Coords16 sDirectionToVectors[] = {
//     {0, 0}, // no movement 0
//     {0, 1}, // move down 1
//     {0, -1}, // move up 2
//     {-1, 0}, // move left 3
//     {1, 0}, // move right 4
//     {-1, 1}, // move left down 5
//     {1, 1}, // move right down 6
//     {-1, -1}, // move left up
//     {1, -1}, // move right up
// };


const u8 gFaceDirectionAnimNums[] = {
    0, // DIR_NONE
    0, // FACE DOWN
    1, // FACE UP
    2, // FACE LEFT
    3, // FACE RIGHT
    2, // FACE DOWN LEFT
    3, // FACE DOWN RIGHT
    2, // FACE UP LEFT
    3, // FACE UP RIGHT
};

const u8 gMoveDirectionAnimNums[] = {
    4, // None
    4, // FACE DOWN
    5, // FACE UP
    6, // FACE LEFT
    7, // FACE RIGHT
    6, // FACE DOWN LEFT
    7, // FACE DOWN RIGHT
    6, // FACE UP LEFT
    7, // FACE UP RIGHT
};

const u8 gMoveDirectionFastAnimNums[] = {
    8, // None
    8, // FACE DOWN
    9, // FACE UP
    10, // FACE LEFT
    11, // FACE RIGHT
    10, // FACE DOWN LEFT
    11, // FACE DOWN RIGHT
    10, // FACE UP LEFT
    11, // FACE UP RIGHT
};

const u8 gTrainerFacingDirectionMovementTypes[] = {
    8, //MOVEMENT_TYPE_FACE_DOWN,
    8, //MOVEMENT_TYPE_FACE_DOWN,
    7, //MOVEMENT_TYPE_FACE_UP,
    9, //MOVEMENT_TYPE_FACE_LEFT,
    10, //MOVEMENT_TYPE_FACE_RIGHT,
    9, //MOVEMENT_TYPE_FACE_DOWN,
    10, //MOVEMENT_TYPE_FACE_DOWN,
    9, //MOVEMENT_TYPE_FACE_UP,
    10, //MOVEMENT_TYPE_FACE_UP,
};

const u8 gFaceDirectionMovementActions[] = {
    0,// MOVEMENT_ACTION_FACE_DOWN,
    0,// MOVEMENT_ACTION_FACE_DOWN,
    1,// MOVEMENT_ACTION_FACE_UP,
    2,// MOVEMENT_ACTION_FACE_LEFT,
    3,// MOVEMENT_ACTION_FACE_RIGHT,
    2,
    3,
    2,
    3,
};


const u8 gRunningDirectionAnimNums[] = {
    20, // movement no dir
    20, // DIR_SOUTH
    21, // DIR_NORTH
    22, // DIR_WEST
    23, // DIR_EAST
    22, // DIR_SOUTHWEST
    23, // DIR_SOUTHEAST
    22, // DIR_NORTHWEST
    23, // DIR_NORTHEAST
};

u8 (*const gOppositeDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked,
};

u8 (*const gDirectionBlockedMetatileFuncs[])(u8) = {
    MetatileBehavior_IsNorthBlocked,
    MetatileBehavior_IsSouthBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked,
    MetatileBehavior_IsEastBlocked,
    MetatileBehavior_IsWestBlocked,
};


u8 GetFaceDirectionMovementAction(u32 direction)
{
    return gFaceDirectionMovementActions[direction];
}

u8 MovementAction_PauseSpriteAnim(struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->animPaused = true;
    return true;
}

u8 MovementAction_step1(struct EventObject *eventObject, struct Sprite *sprite)
{
    if (npc_obj_ministep_stop_on_arrival(eventObject, sprite)) {
        sprite->data[2] = 2;
        return true;
    }
    return false;
}

// Bike diagonal
u8 MovementAction_BikeNormalDiagonalUpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_NORTHWEST, 2);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_BikeNormalDiagonalDownRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_SOUTHEAST, 2);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_BikeNormalDiagonalDownLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_SOUTHWEST, 2);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_BikeNormalDiagonalUpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_NORTHEAST, 2);
    return MovementAction_step1(eventObject, sprite);
}

u8 (*const gMovementActionFuncs_BikeNormalDiagonalUpLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_BikeNormalDiagonalUpLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_BikeNormalDiagonalDownRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_BikeNormalDiagonalDownRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_BikeNormalDiagonalDownLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_BikeNormalDiagonalDownLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_BikeNormalDiagonalUpRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_BikeNormalDiagonalUpRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};


// Run diagonal
u8 MovementAction_RunUpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_NORTHWEST);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_RunDownRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_SOUTHEAST);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_RunDownLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_SOUTHWEST);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_RunUpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    StartRunningAnim(eventObject, sprite, DIR_NORTHEAST);
    return MovementAction_step1(eventObject, sprite);
}

u8 (*const gMovementActionFuncs_RunDiagonalUpLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_RunUpLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_RunDiagonalDownRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_RunDownRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_RunDiagonalDownLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_RunDownLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_RunDiagonalUpRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_RunUpRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};


// Walk Diagonal
u8 MovementAction_WalkNormalDiagonalUpLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_NORTHWEST, 0);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_WalkNormalDiagonalDownRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_SOUTHEAST, 0);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_WalkNormalDiagonalDownLeft_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_SOUTHWEST, 0);
    return MovementAction_step1(eventObject, sprite);
}

u8 MovementAction_WalkNormalDiagonalUpRight_Step0(struct EventObject *eventObject, struct Sprite *sprite)
{
    an_run_any(eventObject, sprite, DIR_NORTHEAST, 0);
    return MovementAction_step1(eventObject, sprite);
}

u8 (*const gMovementActionFuncs_WalkNormalDiagonalUpLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_WalkNormalDiagonalUpLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_WalkNormalDiagonalDownRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_WalkNormalDiagonalDownRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_WalkNormalDiagonalDownLeft[])(struct EventObject *, struct Sprite *) = {
    MovementAction_WalkNormalDiagonalDownLeft_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (*const gMovementActionFuncs_WalkNormalDiagonalUpRight[])(struct EventObject *, struct Sprite *) = {
    MovementAction_WalkNormalDiagonalUpRight_Step0,
    MovementAction_step1,
    MovementAction_PauseSpriteAnim,
};

u8 (** gMovementActionFuncs[])(struct EventObject *, struct Sprite *) = {
    (void*)0x083A6864, (void*)0x083A686C, (void*)0x083A6874, (void*)0x083A687C, // FaceDir 0x0 - 0x3
    (void*)0x083A6A30, (void*)0x083A6A38, (void*)0x083A6A40, (void*)0x083A6A48, // WalkSlowDir 0x4 - 0x7
    (void*)0x083A68C8, (void*)0x083A68D4, (void*)0x083A68E0, (void*)0x083A68EC, // WalkNormalDir 0x8 - 0xB
    (void*)0x083A6904, (void*)0x083A68F8, (void*)0x083A6910, (void*)0x083A691C, // Jump2Dir 0xC - 0xF
    (void*)0x083A6928, (void*)0x083A6934, (void*)0x083A6940, (void*)0x083A694C, (void*)0x083A6964, // Delay1-16 0x10-0x14
    (void*)0x083A6970, (void*)0x083A697C, (void*)0x083A6988, (void*)0x083A6994, // WalkFastDir 0x15 - 0x18
    (void*)0x083A69A0, (void*)0x083A69AC, (void*)0x083A69B8, (void*)0x083A69C4, // WalkInPlaceSlowDir 0x19 - 0x1C
    (void*)0x083A69D0, (void*)0x083A69DC, (void*)0x083A69E8, (void*)0x083A69F4, // WalkInPaceNormalDir 0x1D - 0x20
    (void*)0x083A6A50, (void*)0x083A6A5C, (void*)0x083A6A68, (void*)0x083A6A74, // WalkInPlaceFastDir 0x21 - 0x24
    (void*)0x083A6A80, (void*)0x083A6A8C, (void*)0x083A6A98, (void*)0x083A6AA4, // WalkInPlaceFastest 0x25 - 0x28
    (void*)0x083A6AB0, (void*)0x083A6ABC, (void*)0x083A6AC8, (void*)0x083A6AD4, // RideWaterCurrent 0x29 - 0x2C
    (void*)0x083A6AE0, (void*)0x083A6AEC, (void*)0x083A6AF8, (void*)0x083A6B04, // WalkFastestDir 0x2D - 0x30
    (void*)0x083A6B10, (void*)0x083A6B1C, (void*)0x083A6B28, (void*)0x083A6B34, // SlideDir 0x31 - 0x34
    (void*)0x083A6B40, (void*)0x083A6B4C, (void*)0x083A6B58, (void*)0x083A6B64, // Bike speed? 0x35 - 0x38
    (void*)0x083A6B70, // StartAnimInDirection 0x39
    (void*)0x083A6B7C, (void*)0x083A6B88, (void*)0x083A6B94, (void*)0x083A6BA0, // JumpSpecialDir 0x3A - 0x3D
    (void*)0x083A6BAC, // FacePlayer 0x3E
    (void*)0x083A6BB8, // FaceAwayPlayer 0x3F
    (void*)0x083A6BC4, (void*)0x083A6BD0, // Lock/UnlockFacingDirection 0x40 - 0x41
    (void*)0x083A6BDC, (void*)0x083A6BE8, (void*)0x083A6BF4, (void*)0x083A6C00, // JumpDir 0x42 - 0x45
    (void*)0x083A6C0C, (void*)0x083A6C18, (void*)0x083A6C24, (void*)0x083A6C30, // JumpInPlaceDir 0x46 - 0x49
    (void*)0x083A6C6C, (void*)0x083A6C74, (void*)0x083A6C7C, (void*)0x083A6C84, // 0x4A - 0x4D JumpInPlace DownUp, UpDown, LeftRight, RightLeft
    (void*)0x083A6C8C, // FaceOriginalDirection 0x4E
    (void*)0x083A6C98, // NursejoyBow 0x4F
    (void*)0x083A6CA4, (void*)0x083A6CB0, // Enable/Disable JumpLandingGroundEffect 0x50 - 0x51
    (void*)0x083A6CBC, (void*)0x083A6CC8, // Disable/RestoreAnimation 0x52 - 0x53
    (void*)0x083A6CD4, (void*)0x083A6CE0, // SetInvisible/Visible 0x54 - 0x55
    (void*)0x083A6CEC, // EmoteExclaimationMark 0x56
    (void*)0x083A6CF8, // EmoteQuestionMark 0x57
    (void*)0x083A6D04, // EmoteHeart 0x58
    (void*)0x083A6D10, // RevealTrainer 0x59
    (void*)0x083A6D1C, (void*)0x083A6D24, // RocksmashBreak CutTree 0x5A-0x5B
    (void*)0x083A6D30, (void*)0x083A6D38, // Set/clear FixedPriority 0x5C-0x5D
    (void*)0x083A6D40, (void*)0x083A6D48, // Init/clearAffineAnimation 0x5E - 0x5F
    (void*)0x083A6D50, (void*)0x083A6D58, // WalkDownStartAffine, WalkDownAffine 0x60-0x61
    /* Unknown */
    (void*)0x083A6D60, (void*)0x083A6D68, (void*)0x083A6D70, (void*)0x083A6D78, // 0x62 - 0x65
    (void*)0x083A6D80, (void*)0x083A6D88, (void*)0x083A6D94, (void*)0x083A6DA4, // 0x66 - 0x69
    (void*)0x083A6DB4, (void*)0x083A6DBC, (void*)0x083A6DC4, (void*)0x083A6DCC, // 0x6A - 0x6D
    (void*)0x083A6DD4, (void*)0x083A6DE0, (void*)0x083A6DEC, (void*)0x083A6DF4, // 0x6E - 0x71
    (void*)0x083A6DFC, (void*)0x083A6E04, (void*)0x083A6E0C, (void*)0x083A6E18, // 0x72 - 0x75
    (void*)0x083A6E24, (void*)0x083A6E30, (void*)0x083A6E3C, (void*)0x083A6E48, // 0x76 - 0x79
    (void*)0x083A6E54, (void*)0x083A6E60, (void*)0x083A6E9C, (void*)0x083A6EA8, // 0x7A - 0x7D
    (void*)0x083A6EB4, (void*)0x083A6EC0, (void*)0x083A6ECC, (void*)0x083A6ED8, // 0x7E - 0x81
    (void*)0x083A6EE4, (void*)0x083A6EF0, (void*)0x083A6EFC, (void*)0x083A6F08, // 0x82 - 0x85
    (void*)0x083A6F14, (void*)0x083A6F20, (void*)0x083A6F2C, (void*)0x083A6F38, // 0x86 - 0x89
    (void*)0x083A6F44, (void*)0x083A6F50, (void*)0x083A6F5C, (void*)0x083A6F68, // 0x8A - 0x8D
    (void*)0x083A6F74, (void*)0x083A6F80, (void*)0x083A6F8C, (void*)0x083A6F98, // 0x8E - 0x91
    (void*)0x083A6FA4, (void*)0x083A6FB0, (void*)0x083A6FBC, (void*)0x083A6FC8, // 0x92 - 0x95
    (void*)0x083A6FD4, (void*)0x083A6FE0, (void*)0x083A6FEC, (void*)0x083A6FF4, // 0x96 - 0x99
    (void*)0x083A6FFC, (void*)0x083A6898, (void*)0x083A68A4, (void*)0x083A68B0, // 0x9A = 0x9D
    (void*)0x083A68BC, (void*)0x083A7004, (void*)0x083A6A00, (void*)0x083A6A0C, // 0x9E - 0xA1
    (void*)0x083A6A18, (void*)0x083A6A24, (void*)0x083A700C, (void*)0x083A7018, // 0xA2 - 0xA5
    (void*)0x083A6C3C, (void*)0x083A6C48, (void*)0x083A6C54, (void*)0x083A6C60, // 0xA6 - 0xA9
    /* Diagonal walk */

    NULL, NULL, NULL, NULL, // 0xAA - 0xAD
    NULL, NULL, NULL, NULL, // 0xAE - 0xB1
    NULL, NULL, NULL, NULL, // 0xB2 - 0xB5

    // 0xB6 - 0xB9 walk stairs
    gMovementActionFuncs_WalkNormalDiagonalUpLeft, // Move up left - B0 behaviour left movement
    gMovementActionFuncs_WalkNormalDiagonalDownRight, // Move down right - B0 behaviour right movement
    gMovementActionFuncs_WalkNormalDiagonalDownLeft, // Move down left  - B1 behaviour left movement
    gMovementActionFuncs_WalkNormalDiagonalUpRight, // Move up right - B1 behaviour right movement

    // 0xBA - 0xBD run stairs
    gMovementActionFuncs_RunDiagonalUpLeft, // Move up left - B0 behaviour left movement
    gMovementActionFuncs_RunDiagonalDownRight, // Move down right - B0 behaviour right movement
    gMovementActionFuncs_RunDiagonalDownLeft, // Move down left  - B1 behaviour left movement
    gMovementActionFuncs_RunDiagonalUpRight, // Move up right - B1 behaviour right movement

    // 0xBE - 0xC1 Bike stairs
    gMovementActionFuncs_BikeNormalDiagonalUpLeft, // Move up left - B0 behaviour left movement
    gMovementActionFuncs_BikeNormalDiagonalDownRight, // Move down right - B0 behaviour right movement
    gMovementActionFuncs_BikeNormalDiagonalDownLeft, // Move down left  - B1 behaviour left movement
    gMovementActionFuncs_BikeNormalDiagonalUpRight, // Move up right - B1 behaviour right movement

};
