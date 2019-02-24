#ifndef BATTLE_STATE_H_
#define BATTLE_STATE_H_

#include "pkmn_bank.h"
#include "../moves/moves.h"
#include "../anonymous_callbacks/anonymous_callbacks.h"
#include "../battle_actions/actions.h"
#include <pokeagb/pokeagb.h>

enum BattleTypes {
    BATTLE_MODE_WILD,
    BATTLE_MODE_WILD_DOUBLE,
    BATTLE_MODE_TRAINER,
    BATTLE_MODE_TRAINER_DOUBLE,
    BATTLE_MODE_PARTNER,
};
extern enum BattleTypes battle_type_flag;

enum Effect {
    EFFECT_NONE,
    EFFECT_SLEEP,
    EFFECT_POISON,
    EFFECT_BURN,
    EFFECT_FREEZE,
    EFFECT_PARALYZE,
    EFFECT_BAD_POISON,
    EFFECT_CONFUSION,
    EFFECT_CURE,
    EFFECT_INFACTUATION,
};

enum WeatherTypes {
    WEATHER_CLEAR,
    WEATHER_RAIN,
    WEATHER_SUN,
    WEATHER_SANDSTORM,
    WEATHER_HAIL,
    WEATHER_HARSH_SUN,
    WEATHER_HARSH_RAIN,
    WEATHER_MYSTERIOUS_AIR_CURRENT,
};


enum TypeEffectiveness {
    TE_IMMUNE,
    TE_NOT_VERY_EFFECTIVE,
    TE_EFFECTIVE,
    TE_SUPER_EFFECTIVE,
    TE_OHKO,
};

enum TryHitMoveStatus {
    TRYHIT_CANT_USE_MOVE = 0,
    TRYHIT_USE_MOVE_NORMAL,
    TRYHIT_TARGET_MOVE_IMMUNITY,
    TRYHIT_FAIL_SILENTLY,
    TRYHIT_PASS,
};

struct battle_selection_cursor {
    u8 objid;
    u8 objid_mv_crsr[2];
    u8 cursor_pos; // 0-3
    u8 cursor_x[6];
    u8 cursor_y[6];
};

struct global_message {
    u16 moveId;
    u8 bank : 7;
    u8 in_use : 1;
    u8 string_id;
    u16 effect;
};

struct battle_field_state {
    u8 payday_coins;
    u32 is_raining : 1;
    u32 is_sunny : 1;
    u32 is_sandstorm : 1;
    u32 is_hail : 1;
    u32 suppress_weather : 1;
    u32 is_electric_terrain : 1;
    u32 is_grassy_terrain : 1;
    u32 is_misty_terrain : 1;
    u32 is_psychic_terrain : 1;
    u32 speed_inverse : 1;
    u8 weather_turns;
    u16 last_used_move;
};

struct move_used {
    u8 user_bank;
    u16 moveId;
    s8 priority;
    u8 stab;
    u16 power; //prevent clamp up for moves over effectively 255 bp
    u8 category;
    u8 type[2];
    u8 flinch;
    u8 accuracy; // over 100 = never miss

    u16 makes_contact : 1;
    u16 ignore_abilities : 1;
    u16 infiltrates : 1;
    u16 will_crit : 1;
    u16 can_crit : 1;
    u16 ignore_target_atk : 1;
    u16 ignore_target_def : 1;
    u16 ignore_target_evasion : 1;

    struct move_procs b_procs;

    u8 hit_times;
    u8 hit_counter;
    u16 dmg;
    s16 drain;
    enum TypeEffectiveness effectiveness;
    u16 heal;
    u16 after_dmg;
};

typedef u16 (*StatModifierCallback)(u16 stat, u8 id, u8 bank);

enum switch_reason {
    PokemonFainted,
    ViewPokemon,
    ForcedSwitch,
    NormalSwitch,
};

struct switch_pokemon_data {
    u32 PID;
    u16 species;
    pchar health[9];
    u8 ability;
    u16 item;
    u16 stats[5];
    struct TextColor* nature_boosted[5];
    u16 move[4];
    u16 pp[4];
    pchar nickname[20];
    pchar level[6];
    u8 ailment_effect;
};

struct switch_data {
    u8 list_count;
    struct switch_pokemon_data s_pkmn_data[6];
    u8 hpbar_id;
};

struct switch_menu {
    u8 type_objid[10];
    u8 slider_objid[3];
    u8 icon_objid[6];
    u8 switch_confirm_box_id;
    u8 switch_confirm_cursor_id;
    u8 position;
    enum switch_reason reason;
    u8 unswitchable_bank; // used if a pkmn is forced out
    void* back_buffer;
    struct switch_data* sd;
};

struct battle_main {
    struct battle_field_state field_state;

    /* Battle actions */
    struct action* action_head;
    struct action* this_action;

    /* Main Battle callbacks */
    struct anonymous_callback anon_cb_master[ANON_CB_MAX];
    u8 cb_execution_order[ANON_CB_MAX];
    u8 current_cb_index : 7;
    u8 executing : 1;
    u8 bank_state;

    /* Object ids and positions for fight menu */
    struct battle_selection_cursor battle_cursor;
    u8 selected_option;
    u8 type_objid[4];
    u8 move_name_objid[4];
    u8 move_pss_objid[4];
    u8 move_pp_objid[4];
    u8 fight_menu_content_spawned;
    u8 option_selecting_bank;

    /* Battle turn order variables */
    u8 execution_index;
    u8 bank_hit_list[BANK_MAX];
    u8 bankOrder[BANK_MAX];
    struct move_used b_moves[BANK_MAX];
    u32 participatingIDs[6]; // PIDs of pokemon who entered the battle.
    u8 c1_prestate;
    struct switch_menu switch_main;

};

enum fight_menu { OPTION_FIGHT, OPTION_POKEMON, OPTION_BAG, OPTION_RUN };

extern struct battle_main* gBattleMaster;
extern u8 gBattleAnimationStatus;
extern void play_bmessage(void);
extern void dprintf(const char* str, ...);
extern bool peek_message(void);

//weather macros
#define IS_WEATHER_SUPPRESSED (gBattleMaster->field_state.suppress_weather)
#define IS_WEATHER_RAINING (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_raining)
#define IS_WEATHER_SUNNY (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_sunny)
#define IS_WEATHER_STANDARD_RAIN (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_raining)
#define IS_WEATHER_STANDARD_SUN (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_sunny)
#define IS_WEATHER_HAIL (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_hail)
#define IS_WEATHER_SANDSTORM (!IS_WEATHER_SUPPRESSED && gBattleMaster->field_state.is_sandstorm)

#endif /* BATTLE_STATE_H_ */
