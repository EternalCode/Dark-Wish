#include <pokeagb/pokeagb.h>
#include "moves.h"

/* Basic proc format for moves like tackle */
struct move_procs basic_proc = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's attack 1 stage
struct move_procs target_lower_atk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's attack 2 stages
struct move_procs target_lower_atk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-2, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's defense 1 stage
struct move_procs target_lower_def_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's defense 2 stages
struct move_procs target_lower_def_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -2, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's sp. attack 1 stage
struct move_procs target_lower_spAtk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's sp. attack 2 stages
struct move_procs target_lower_spAtk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -2, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's sp. defense 1 stage
struct move_procs target_lower_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's sp. defense 2 stages
struct move_procs target_lower_spDef_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -2, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's speed 1 stage
struct move_procs target_lower_spd_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's speed 2 stages
struct move_procs target_lower_spd_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -2, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's ACCURACY 1 stage
struct move_procs target_lower_acc_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's ACCURACY 1 stage, 50%
struct move_procs target_lower_acc_1_chance_50 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 50, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's ACCURACY 2 stages
struct move_procs target_lower_acc_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -2, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

struct move_procs target_lower_evn_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 100, 0},
    {0, 0, 0, 0, 0, 0, -2, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's attack 1 stage
struct move_procs user_lower_atk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's attack 2 stages
struct move_procs user_lower_atk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 0, 0, 0, 0, 0},
    {-2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's defense 1 stage
struct move_procs user_lower_def_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

struct move_procs target_lower_def_1_30 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 30, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's defense 2 stages
struct move_procs user_lower_def_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, -2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's sp. attack 1 stage
struct move_procs user_lower_spAtk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's sp. attack 2 stages
struct move_procs user_lower_spAtk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's sp. defense 1 stage
struct move_procs user_lower_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's sp. defense 2 stages
struct move_procs user_lower_spDef_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, -2, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's speed 1 stage
struct move_procs user_lower_spd_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's speed 2 stages
struct move_procs user_lower_spd_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, -2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's ACCURACY 1 stage
struct move_procs user_lower_acc_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's ACCURACY 2 stages
struct move_procs user_lower_acc_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, -2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's attack 1 stage
struct move_procs target_raise_atk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's attack 2 stages
struct move_procs target_raise_atk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's Defense 1 stage
struct move_procs target_raise_def_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's defense 2 stages
struct move_procs target_raise_def_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's sp. attack 1 stage
struct move_procs target_raise_spAtk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's sp. attack 2 stages
struct move_procs target_raise_spAtk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's sp. defense 1 stage
struct move_procs target_raise_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's sp. defense 2 stages
struct move_procs target_raise_spDef_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's speed 1 stage
struct move_procs target_raise_spd_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's speed 2 stages
struct move_procs target_raise_spd_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's ACCURACY 1 stage
struct move_procs target_raise_acc_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's ACCURACY 2 stages
struct move_procs target_raise_acc_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's attack 1 stage
struct move_procs user_raise_atk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

struct move_procs user_raise_atk_1_10 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {10, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's attack 2 stages
struct move_procs user_raise_atk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's defense 1 stage
struct move_procs user_raise_def_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's defense 2 stages
struct move_procs user_raise_def_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's sp. attack 1 stage
struct move_procs user_raise_spAtk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's sp. attack 2 stages
struct move_procs user_raise_spAtk_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's sp. defense 1 stage
struct move_procs user_raise_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's sp. defense 2 stages
struct move_procs user_raise_spDef_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 100, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's speed 1 stage
struct move_procs user_raise_spd_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's speed 2 stages
struct move_procs user_raise_spd_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 0, 0, 0, 0, 0},
    {0, 0, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's ACCURACY 1 stage
struct move_procs user_raise_acc_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's ACCURACY 2 stages
struct move_procs user_raise_acc_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 100, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's evasiveness 1 stage
struct move_procs user_raise_evn_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 100, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//poison sting, sludge (30%)
struct move_procs poison_30_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_POISON,
    0,
    30,
};

//smog (40%)
struct move_procs poison_40_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_POISON,
    0,
    40,
};

// posion 20
struct move_procs poison_20_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_POISON,
    0,
    20,
};

// Sing
struct move_procs sing_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_SLEEP,
    0,
    100,
};

// Supersonic
struct move_procs supersonic_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    100,
};

// 10% Burn on target.
struct move_procs burn_10_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BURN,
    0,
    10,
};

// 30% Burn on target.
struct move_procs burn_30_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BURN,
    0,
    30,
};

// 10% Freeze: Ice Beam
struct move_procs freeze_10_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_FREEZE,
    0,
    10,
};

// 10% Confuse: Psybeam
struct move_procs confuse_10_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    10,
};

// 100% Confuse
struct move_procs confuse_100_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    100,
};

// Shell Smash
struct move_procs shell_smash_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 100, 100, 100, 100, 0, 0, 0},
    {2, -1, 2, 2, -1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Dragon Ascent
struct move_procs dragon_ascent_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 100, 0, 0, 0},
    {0, -1, 0, 0, -1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Shift Gear
struct move_procs shift_gear_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 100, 0, 0, 0, 0, 0},
    {1, 0, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Paralyze 100%
struct move_procs paralyze_100_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_PARALYZE,
    0,
    100,
};


// Bubble Beam
struct move_procs bubble_beam_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 10, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

// Aurora Beam
struct move_procs aurora_beam_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
	{10, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
	AILMENT_NONE,
	AILMENT_NONE,
	0,
	0,
};

// Shadow ball
struct move_procs shadow_ball_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 20, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//100% poison
struct move_procs poison_100_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_POISON,
    0,
    100,
};

//10% Paralyze
struct move_procs paralyze_10_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_PARALYZE,
    0,
    10,
};

//30% Paralyze
struct move_procs paralyze_30_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_PARALYZE,
    0,
    30,
};

//Toxic
struct move_procs toxic_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BAD_POISON,
    0,
    100,
};

//Psychic spD drop
struct move_procs psychic_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 10, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// 20% Confuse
struct move_procs confuse_20_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    20,
};

// 30% Confuse
struct move_procs confuse_30_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    20,
};

// user sleep
struct move_procs rest_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_SLEEP,
    AILMENT_NONE,
    100,
    0,
};

struct move_procs target_raise_atk_2_confuse = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
    100,
};

struct move_procs user_raise_def_1_10 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 10, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

struct move_procs target_burn_50 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BURN,
    0,
    50,
};

struct move_procs poison_10_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_POISON,
    0,
    10,
};

// Lowers Defense 50% by 1 stage
struct move_procs target_lower_def_50_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 50, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

struct move_procs target_lower_def_20_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 20, 0, 0, 0, 0, 0, 0},
    {0, -1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Ancient Power
struct move_procs ancient_power_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {10, 10, 10, 10, 10, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Burns 100%
struct move_procs burn_100_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BURN,
    0,
   100,
};

// Flatter; SPA -1 and confuse
struct move_procs flatter_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_CONFUSION,
    0,
   100,
};

// Decreases User's Attack and Defense
struct move_procs dec_user_atk_def_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 100, 0, 0, 0, 0, 0, 0},
    {-1, -1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Raises User's Attack and Speed by 1 Stage - Dragon Dance
struct move_procs dragon_dance_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 100, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Raises User's Attack and Defense by 1 Stage - Bulk Up
struct move_procs bulk_up_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 100, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Increases User's SpA by 3 stages
struct move_procs inc_user_spa_3_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 0, 0, 0, 0},
    {0, 0, 0, 3, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Decreases  50% SpD
struct move_procs dec_SpD_50_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 50, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Decreases  50% SpA
struct move_procs dec_SpA_50_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 50, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Bad Poison 50%
struct move_procs bad_poison_50_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BAD_POISON,
    0,
    50,
};

// Raises User's Attack by 20% in 1 Stage
struct move_procs raise_user_atk_20 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {20, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Lowers Target's Attack and Defense by 1 Stage
struct move_procs low_targ_atk_def = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 100, 0, 0, 0, 0, 0, 0},
    {-1, -1, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Raises User's Special Defense and Defense by 1 Stage
struct move_procs raise_user_Def_SpD = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 100, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Lowers Target's Accuracy by 1 Stage
struct move_procs low_tar_Acc = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 30, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's sp. defense 1 stage
struct move_procs target_lower_spDef_1_10 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 10, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises user's sp. attack and Sp. defense 1 stage
struct move_procs user_raise_spAtk_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 100, 100, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises target's sp. attack and attack 1 stage
struct move_procs target_raise_Atk_spAtk_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 100, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers user's defense and special defense 1 stage
struct move_procs user_lower_def_spDef_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 0, 0, 100, 0, 0, 0},
    {0, -1, 0, 0, -1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Geomancy +2 SPA, SPD, SPE to user
struct move_procs geomancy_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 100, 100, 0, 0, 0},
    {0, 0, 2, 2, 2, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Venom drench -1 SPA, ATK, SPE target
struct move_procs venom_drench = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 100, 100, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's accuracy 30% by 1 Stage
struct move_procs low_tar_acc_30 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 30, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//30% chance to lower target's spAtk by 1 stage
struct move_procs low_tar_spAtk_30 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 30, 0, 0, 0, 0},
    {0, 0, 0, -1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers target's evasion by 1 Stage
struct move_procs low_tar_evn_1 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 100, 0},
    {0, 0, 0, 0, 0, 0, -1, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// 10% chance to lower Target's Sp. Def by 1 Stage - Bug Buzz
struct move_procs bug_buzz_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 10, 0, 0, 0},
    {0, 0, 0, 0, -1, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};


// 10% chance to lower Target's Speed by 1 Stage - constrict
struct move_procs target_lower_spe_1_10 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 10, 0, 0, 0, 0, 0},
    {0, 0, -1, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//70% chance to raise user's Sp. Atk by 1 stage - Charge Beam
struct move_procs charge_beam_procs = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 70, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//+2 user crit chance - focus energy
struct move_procs focus_energy_proc = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 100},
    {0, 0, 0, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers Target's SpD 30% by 2 Stages
struct move_procs low_tar_SpD_30_2 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 30, 0, 0, 0},
    {0, 0, 0, 0, -2, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises User's Attack and Accuracy
struct move_procs raise_user_Atk_Acc = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 0, 0, 100, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises User's Attack, Defense and Accuracy
struct move_procs raise_user_Atk_Def_Acc = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 100, 0, 0, 0, 100, 0, 0},
    {1, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises User's SpD, SpA and Speed
struct move_procs raise_user_SpD_SpA_Spd = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 100, 100, 100, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Raises User's SpA and Atk
struct move_procs raise_user_SpA_Atk = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {100, 0, 0, 100, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

//Lowers Target's Accuracy 1 Stage 40%
struct move_procs low_tar_acc_40 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 40, 0, 0},
    {0, 0, 0, 0, 0, -1, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Raises User's SpA 50% by 1 stage
struct move_procs raise_user_SpA_50 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 50, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// V-Create
struct move_procs v_create = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 100, 100, 0, 100, 0, 0, 0},
    {0, -1, -1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Lowers Target's Atk and SpA
struct move_procs low_target_atk_SpA = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {100, 0, 0, 100, 0, 0, 0, 0},
    {-1, 0, 0, -1, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Lowers Target's Atk 10%
struct move_procs low_target_atk_10 = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {10, 0, 0, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_NONE,
    0,
    0,
};

// Toxic Thread
struct move_procs toxic_thread = {
    // Atk, Def, Spd, SpA, SpD, Acc, Evn, Crt
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0,100,0, 0, 0, 0, 0},
    {0, 0,-1, 0, 0, 0, 0, 0},
    AILMENT_NONE,
    AILMENT_BAD_POISON,
    0,
    100,
};
