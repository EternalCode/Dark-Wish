#ifndef BATTLE_PKMN_BANK_H_
#define BATTLE_PKMN_BANK_H_

#include <pokeagb/pokeagb.h>
#include "../../pokemon/types/pkmn_types.h"

#define PLAYER_SINGLES_BANK 0
#define PLAYER_DOUBLES_BANK 1
#define OPPONENT_SINGLES_BANK 2
#define OPPONENT_DOUBLES_BANK 3

#define PARTICIPANTS_AMOUNT_WILD 2

#define BANK_MAX 4


enum StatusAilments {
    AILMENT_NONE = 0,
    AILMENT_SLEEP,
    AILMENT_POISON,
    AILMENT_BURN,
    AILMENT_FREEZE,
    AILMENT_PARALYZE,
    AILMENT_BAD_POISON,
    AILMENT_CONFUSION,
    AILMENT_CURE,
    AILMENT_INFACTUATION,
};


enum TypeBits {
    TYPE_BITS_NORMAL = (1 << 0),
    TYPE_BITS_FIGHTING = (1 << 1),
    TYPE_BITS_FLYING = (1 << 2),
    TYPE_BITS_POISON = (1 << 3),
    TYPE_BITS_GROUND = (1 << 4),
    TYPE_BITS_ROCK = (1 << 5),
    TYPE_BITS_BUG = (1 << 6),
    TYPE_BITS_GHOST = (1 << 7),
    TYPE_BITS_STEEL = (1 << 8),
    TYPE_BITS_FIRE = (1 << 9),
    TYPE_BITS_WATER = (1 << 10),
    TYPE_BITS_GRASS = (1 << 11),
    TYPE_BITS_ELECTRIC = (1 << 12),
    TYPE_BITS_PSYCHIC = (1 << 13),
    TYPE_BITS_ICE = (1 << 14),
    TYPE_BITS_DRAGON = (1 << 15),
    TYPE_BITS_DARK = (1 << 16),
};


/* Volatile definitions for Bitmasks -- enum is unsuitable */
enum Volatiles {
    VOLATILE_FLASH_FIRE,
    VOLATILE_CONFUSION,
    VOLATILE_SUBSTITUTE,
    VOLATILE_STAT_REDUC_IMMUNE,
    VOLATILE_TRAPPED,
    VOLATILE_AROMA_VEIL,
    VOLATILE_MOLDBREAKER,
    VOLATILE_PRANKSTERED,
    VOLATILE_SEMI_INVULNERABLE,
    VOLATILE_CHARGING,
    VOLATILE_INGRAIN,
    VOLATILE_BIND,
    VOLATILE_FLYING,
    VOLATILE_MINIMIZE,
    VOLATILE_MULTI_TURN,// disables PP reduction
    VOLATILE_SLEEP_TURN,
    VOLATILE_CONFUSE_TURN,
    VOLATILE_ATK_SKIP_TURN,
    VOLATILE_DEFENSE_CURL,
    VOLATILE_RECHARGING,
    VOLATILE_GRAVITY,
    VOLATILE_BOUNCE,
    VOLATILE_SKYDROP,
    VOLATILE_MIRACLE_EYE,
    VOLATILE_MAGNET_RISE,
    VOLATILE_SMACK_DOWN,
    VOLATILE_TELEKINESIS,
    VOLATILE_HEAL_BLOCK,
    VOLATILE_ODOR_SLEUTH,
    VOLATILE_FORESIGHT,
    VOLATILE_ENCORE,
    VOLATILE_PERISH_SONG,
    VOLATILE_DESTINY_BOND,
    VOLATILE_INSTRUCT,
    VOLATILE_GRUDGE,
    VOLATILE_INFACTUATION,
    VOLATILE_BIDE,
    VOLATILE_DIVE,
    VOLATILE_DIG,
    VOLATILE_FOCUS_ENERGY,
    VOLATILE_GASTRO_ACID,
    VOLATILE_FAIRY_BLOCK,
    VOLATILE_DRIZZLE,
    VOLATILE_DROUGHT,
    VOLATILE_SANDSTREAM,
    VOLATILE_SNOWWARNING,
    VOLATILE_DISABLE,
    VOLATILE_TRUANT,
    VOLATILE_BERSERK,
    VOLATILE_SHEER_FORCE,
};


struct local_battler_data {
    // Base stats in battle
    pchar name[12];
    u16 species;
    u16 current_hp;
    u16 total_hp;
    u8 slot;
    u8 gender;
    u8 ability;
    u16 item;
    u8 level;
    u8 poke_ball;
    u8 type[3];
    u16 weight;

    // moves
    u16 bmoves[4];
    u8 move_pp[4];

    // raw base stats
    u16 attack_raw;
    u16 defense_raw;
    u16 speed_raw;
    u16 sp_atk_raw;
    u16 sp_def_raw;

    // IVs
    u32 hp_iv : 5;
    u32 attack_iv : 5;
    u32 defense_iv : 5;
    u32 speed_iv : 5;
    u32 sp_atk_iv : 5;
    u32 sp_def_iv : 5;
    u32 reduce_pp : 1;
    u32 will_move : 1;

    // Delta applied to base stat. ex: -1 atk
    s8 attack;
    s8 defense;
    s8 speed;
    s8 sp_atk;
    s8 sp_def;
    s8 accuracy;
    s8 evasion;
    s8 crit_mod;

    // This Pokemon's action this turn
    u8 isRunning : 1;
    u8 using_item : 1;
    u8 isSwitching : 1;
    u8 skip_move_select : 1;
    u8 first_turn : 1;
    u8 move_failed : 1;
    u8 last_move_failed : 1;
    u8 is_active_bank : 1;

    u8 flinch;
    u8 my_target;
    u8 pp_index;
    u16 last_move;
    u16 current_move;
    u16 last_damage;
    u16 moves_used[4];
    u16 last_used_item;
    u8 last_attacked_by;
    u8 move_lock_counter;

    // local user specific bitfield
    u8 illusion : 1;
    u8 is_transformed : 1;
    u8 fainted : 1;
    u8 ate_berry : 1;
    u8 is_trapped : 1;
    u8 is_grounded : 1;
    u8 did_crit : 1;
    u8 justSwitched : 1;

	// stockpile
    u8 stockpile_uses : 2;
    u8 stockpile_def_boost : 3;
    u8 stockpile_spdef_boost : 3;

    enum StatusAilments status;
    u8 pseudo_ailment;
    u8 confusion_turns;
    u8 status_turns;
    u16 substitute_health;
    u8 protect_used_turns;
    u32 v_status; // enum volatile status
    u32 v_status2; // continue of above
    // counters
    u8 EscapeAttempts;
    u8 perish_song_counter;
    u8 fury_cutter_counter;
};

struct SwitchingFlagsToPass {
    u8 pass_status : 1;
    u8 pass_stats : 1;
    u8 pass_atk_history : 1;
    u8 pass_disables : 1;

};

struct pkmn_bank {
    struct Pokemon* this_pkmn;
    u8 objid;
    u8 objid_hpbox[4]; // Main box, tag on part and
    u8 pp_pal;
    u8 move_pal;
    struct local_battler_data battleData;
};

extern struct pkmn_bank* gPkmnBank[BANK_MAX];

#endif /* BATTLE_PKMN_BANK_H_ */
