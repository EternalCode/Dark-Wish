#ifndef BATTLE_PICK_MESSAGES_H_
#define BATTLE_PICK_MESSAGES_H_

#include <pokeagb/pokeagb.h>

enum battle_string_ids {
    STRING_ATTACK_USED = 0,
    STRING_INFATUATED,
    STRING_BIDE_CHARGE,
    STRING_LOST_FOCUS,
    STRING_CANT_USE,
    STRING_DISABLED,
    STRING_FAILED,
    STRING_CURSE_RESIDUAL,
    STRING_MAGNITUDE_AMOUNT,
    STRING_NO_TARGET,
    STRING_FAILED_ALONE,
    STRING_IMMUNE_ABILITY,
    STRING_RAZORWIND = 13,
    STRING_SOLARBEAM,
    STRING_FREEZE_SHOCK,
    STRING_ICE_BURN,
    STRING_GOEMANCY,
    STRING_SKULL_BASH,
    STRING_RAINING,
    STRING_STURDY_IMMUNE,
    STRING_DAMP_BLOCKED,
    STRING_STATUS_CURED,
    STRING_EFFECT_ENDED,
    STRING_WEATHER_GONE,
    STRING_GAINED_TYPE,
    STRING_CONFUSION_ENDED,
    STRING_DRAGGED_OUT_FAILED,
    STRING_STAT_MOD_HARSH_DROP,
    STRING_STAT_MOD_DROP,
    STRING_STAT_MOD_HARSH_RISE,
    STRING_STAT_MOD_RISE,
    STRING_AILMENT_APPLIED,
    STRING_AILMENT_IMMUNE,
    STRING_AILMENT_CURED,
    STRING_DELTA_STREAM,
    STRING_DESOLATE_LAND,
    STRING_PRIMORDIAL_SEA,
    STRING_PROTEAN,
    STRING_ATTACK_MISSED,
    STRING_ATTACK_AVOIDED,
    STRING_FLEE,
    STRING_FLEE_FAILED = 43,
    STRING_MOVE_CRIT,
    STRING_MOVE_IMMUNE,
    STRING_MOVE_NVE = 47,
    STRING_MOVE_SE,
    STRING_RECOIL,
    STRING_DRAIN,
    STRING_FAINTED,
    STRING_EXP_GAIN,
    STRING_LEVEL_UP,
    STRING_HEAL,
    STRING_FLINCHED,
    STRING_MULTI_HIT,
    STRING_OHKO,
    STRING_CHARGE_SKY_ATTACK,
    STRING_CHARGE_DIG,
    STRING_CHARGE_DIVE,
    STRING_CHARGE_FLY,
    STRING_CHARGE_PHANTOM_FORCE,
    STRING_CHARGE_SHADOW_FORCE,
    STRING_CHARGE_BOUNCE,
    STRING_CHARGE_SKY_DROP,
    STRING_CHARGE_SOLAR_BLADE,
    STRING_INVULNERABLE,
    STRING_RESIDUAL_DMG,
    STRING_STAT_MOD_CANT_GO_LOWER,
    STRING_STAT_MOD_CANT_GO_HIGHER,
    STRING_STAT_MOD_SEVERELY_FELL,
    STRING_STAT_MOD_ROSE_DRASTICALLY,
    STRING_RESIDUAL_STATUS_DMG,
    STRING_FAST_ASLEEP,
    STRING_WOKE_UP,
    STRING_SNAPPED_OUT,
    STRING_CONFUSION_HURT,
    STRING_IS_CONFUSED,
    STRING_NO_PP,
    STRING_DISABLED_PICKED,
    STRING_FROZEN_SOLID,
    STRING_FREEZE_THAWED,
    STRING_FULL_PARA,
    STRING_CLEAR_SMOG,
    STRING_BOUNCED_BACK,
    STRING_SHROUDED_MAGICCOAT = 87,
    STRING_SNATCH_WAITING,
    STRING_SNATCHED_MOVE,
    STRING_MUST_RECHARGE,
    STRING_CONVERSION_TYPE,
    STRING_REFLECT_TYPE_MATCHED,
    STRING_TYPE_ADDED,
    STRING_ION_DELUGE,
    STRING_ELECTRIFIED,
    STRING_BURNT_OUT = 97,
    STRING_PROTECTED_SELF,
    STRING_ENDURED,
    STRING_BRACED_ITSELF,
    STRING_KICKED_UP_MAT,
    STRING_PROTECTED_TEAM,
    STRING_PROTECTED_MON,
    STRING_BROKE_PROTECT,
    STRING_RAIN_FALLING,
    STRING_RAIN_STOPPED,
    STRING_HEAVY_RAIN_FIZZLE,
    STRING_HEAVY_RAIN_LIFTED,
    STRING_SUNLIGHT_HARSH,
    STRING_SUNLIGHT_STRONG,
    STRING_SUNLIGHT_FADE,
    STRING_HARSH_SUN_WATER,
    STRING_HARSH_SUN_END,
    STRING_SANDSTORM_KICKED,
    STRING_SANDSTORM_RAGE,
    STRING_SANDSTORM_BUFFET,
    STRING_SANDSTORM_END,
    STRING_DELTA_STREAM_EFFECT,
    STRING_DELTA_STREAM_END,
    STRING_DELTA_STREAM_IMM,
    STRING_PRIMORDIAL_SEA_IMM,
    STRING_DESOLATE_LAND_IMM,
    STRING_AURORA_VEIL,
    STRING_REFLECT,
    STRING_LIGHTSCREEN,
    STRING_SHATTER_BARRIER,
    STRING_FUTURE_FORESAW,
    STRING_TOOK_ATTACK,
    STRING_DOOM_DESIRE,
    STRING_WISH_TRUE,
    STRING_GREW_DROWSY,
    STRING_MOVE_ENDED,
    STRING_ELECTRIC_TERRAIN_START,
    STRING_PSYCHIC_TERRAIN_START,
    STRING_GRASSY_TERRAIN_START,
    STRING_MISTY_TERRAIN_START,
    STRING_LEARNED_MOVE,
    STRING_SLOT_ATTACK,
    STRING_TAILWIND_BLEW,
    STRING_TAILWIND_PETER,
    STRING_TWISTED_DIM,
    STRING_TWISTED_DIM_NORM,
    STRING_WONDER_AREA,
    STRING_SAFE_GUARD_VEIL,
    STRING_SHIELDED_CRITS,
    STRING_GRAVITY_INTENSE,
    STRING_FAILED_EXECUTION,
    STRING_IDENTIFIED,
    STRING_TYPE_WEAKEN,
    STRING_MAGNETISM_LEV,
    STRING_HURLED_AIR,
    STRING_HEAL_PREVENT,
    STRING_GUARD_S,
    STRING_POWER_S,
    STRING_SPE_SWAP,
    STRING_RECIEVED_ENCORE,
    STRING_SUBJECTED_TORM,
    STRING_FELL_FOR_TAUNT,
    STRING_CANT_REASON,
    STRING_ROOTS_PLANTED,
    STRING_FELL_DOWN,
    STRING_SETUP_SHELL_TRP,
    STRING_PERISH_START,
    STRING_COUNT_FELL,
    STRING_TOOK_WITH_HIM,
    STRING_TRYING_TO_TAKE,
    STRING_GRUDGE_START,
    STRING_GRUDGE_END,
    STRING_SKY_DROP_START,
    STRING_SKY_DROP_AIR = 171,
    STRING_SKY_DROP_FREE,
    STRING_ATTRACT,
    STRING_UNLEASHED_ENERGY,
    STRING_READY_TO_HELP,
    STRING_INFESTATION,
    STRING_TOPSY_TURVY,
    STRING_CENTER_ATTENTION,
    STRING_SETUP_STOCKPILE,
    STRING_SOOTHING_AROMA,
    STRING_COPIED_STATS,
    STRING_PAIN_SPLIT,
    STRING_BELL_CHIMED,
    STRING_BELLY_DRUM,
    STRING_CURSE,
    STRING_STAT_ELIMINATED,
    STRING_SEEDED,
    STRING_SAPPED,
    STRING_TIGHTEN_FOCUS,
    STRING_BEAK_BLAST,
    STRING_ENCOUNTER_WILD,
    STRING_HEART_SWAP,
    STRING_RETREAT_MON,
    STRING_SEND_OUT,
    STRING_TRAPPED,
    STRING_ABILITY_CHANGED,
    STRING_ANGER_POINT,
    STRING_FLASH_FIRE,
    STRING_TRACE_ABILITY,
    STRING_TRAPPED_RUN,
    STRING_RUN_AWAY,
    STRING_ANTICIPATION,
    STRING_FRISK,
    STRINGS_TABLE_MAX = 700,
};
const static pchar encounter_wild_text[] = _("A wild {DEFENDING_MON} appeared!\pGo! {ATTACKING_MON}!");

static const pchar str_stat_mod_severely_fell_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nseverely fell!");
static const pchar str_stat_mod_severely_fell_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nseverely fell!");
static const pchar str_stat_mod_rose_drastically_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nrose drastically!");
static const pchar str_stat_mod_rose_drastically_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nrose drastically!");
static const pchar str_stat_mod_cant_go_lower_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any lower!");
static const pchar str_stat_mod_cant_go_lower_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any lower!");
static const pchar str_stat_mod_cant_go_higher_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any higher!");
static const pchar str_stat_mod_cant_go_higher_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any higher!");


static const pchar str_atk_used_o[] = _("{FOE}{ATTACKING_MON} used\n{ATTACK_NAME}!");
static const pchar str_infatuated_o[] = _("{FOE}{ATTACKING_MON} is in love\nwith {DEFENDING_MON}\p{FOE}{ATTACKING_MON}\nis immobolized by love!");
static const pchar str_bide_o[] = _("{FOE}{ATTACKING_MON} is\nstoring energy!");
static const pchar str_focus_lost_o[] = _("{FOE}{ATTACKING_MON} lost its\nfocus and couldn’t move!");
static const pchar str_cant_use_o[] = _("{ATTACKING_MON} can’t use\n{ATTACK_NAME} because of {EFFECT_NAME}!");
static const pchar str_disabled_o[] = _("{FOE}{ATTACKING_MON}’s {ATTACK_NAME}\nwas disabled!");
static const pchar str_failed_o[] = _("But it failed!");
static const pchar str_curse_dmg_o[] = _("{FOE}{ATTACKING_MON} is afflicted\nby {ATTACK_NAME}");
static const pchar str_magnitude_amount_o[] = _("MAGNITUDE {STR_VAR_1}!");
static const pchar str_no_target_o[] = _("But there was no target!");
static const pchar str_failed_alone[] = _("But it failed!");
static const pchar str_immunity_p[] = _("{FOE}{ATTACKING_MON}’s {ABILITY}\nmade it immune!");
static const pchar str_ability_changed[] = _("{FOE}{ATTACKING_MON}’s {ABILITY_ARBITRARY}\nturned into {ABILITY}!");
static const pchar str_charging_up_razorwind_o[] = _("{FOE}{ATTACKING_MON} whipped\nup a whirlwind!");
static const pchar str_solarbeam_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
static const pchar str_freeze_shock_o[] = _("{FOE}{ATTACKING_MON} became cloaked\nin a freezing light!");
static const pchar str_ice_burn_o[] = _("{FOE}{ATTACKING_MON} is radiating\na blazing aura!");
static const pchar str_geomancy_o[] = _("{FOE}{ATTACKING_MON} is absorbing\npower!");
static const pchar str_skull_bash_o[] = _("{FOE}{ATTACKING_MON} lowered\nits head!");
static const pchar str_started_rain[] = _("It started to {WEATHER}!");
static const pchar str_sturdy_immune_o[] = _("{FOE}{DEFENDING_MON}’s sturdy makes\nit immune to {ATTACK_NAME}!");
static const pchar str_damp_o[] = _("{FOE}{ATTACKING_MON} couldn’t use\n{ATTACK_NAME} because of {DEFENDING_MON}’s DAMP!");
static const pchar str_cure_status_o[] = _("{FOE}{ATTACKING_MON}’s cured\nits status!");
static const pchar str_effect_ended_o[] = _("{FOE}{ATTACKING_MON}’s\n{ATTACK_NAME} ended.");
static const pchar str_weather_gone[] = _("The effects of the weather\ndisappeared.");
static const pchar str_gained_type_o[] = _("{FOE}{ATTACKING_MON} gained {TYPE}\nfrom {ABILITY}!");
static const pchar str_confusion_end_o[] = _("{FOE}{ATTACKING_MON} is\nno longer confused!");
static const pchar str_dragout_failed_o[] = _("{FOE}{ATTACKING_MON} couldn’t be\ndragged out of battle!");
static const pchar str_stat_mod_harsh_drop_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\ndropped harshly!");
static const pchar str_stat_mod_drop_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\ndropped!");
static const pchar str_stat_mod_harsh_rise_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nsharply rose!");
static const pchar str_stat_mod_rise_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nrose!");
static const pchar str_ailment_applied_o[] = _("{FOE}{ATTACKING_MON} was {STATUS_NAME}!");
static const pchar str_ailment_immune_o[] = _("{FOE}{ATTACKING_MON} was immune\nto being {STATUS_NAME}!");
static const pchar str_ailment_cured_o[] = _("{FOE}{ATTACKING_MON} was cured\nof all status ailments!");
static const pchar str_delta_stream[] = _("A mysterious air current\nis protecting Flying-type Pokémon!");
static const pchar str_desolate_land[] = _("The sunlight turned\nextremely harsh!");
static const pchar str_primordial_sea[] = _("A heavy rain began to fall!");
static const pchar str_protean_o[] = _("{FOE}{ATTACKING_MON}’s Protean changed\nit’s type!");
static const pchar str_atk_missed[] = _("The attack missed!");
static const pchar str_atk_avoided[] = _("{DEFENDING_MON} avoided the attack!");
static const pchar str_fled_p[] = _("Got away safely.\p");
static const pchar str_fled_o[] = _("{ATTACKING_MON} fled\p");
static const pchar str_flee_failed[] = _("Could not flee!\p"); /* TODO: proper text and reasoning */
static const pchar str_move_crit[] = _("A critical hit!");
static const pchar str_move_immune_p[] = _("{FOE}{DEFENDING_MON} was immune!");
static const pchar str_move_immune_o[] = _("{DEFENDING_MON} was immune!");
static const pchar str_move_nve[] = _("It wasn’t very effective");
static const pchar str_move_se[] = _("It was super effective!");
static const pchar str_recoil[] =_("{ATTACKING_MON} was hurt by recoil!");
static const pchar str_drain[] = _("{DEFENDING_MON}’s energy was drained!");
static const pchar str_fainted_o[] = _("{FOE}{ATTACKING_MON}\nfainted!\p");
static const pchar str_give_exp[] = _("{ATTACKING_MON} gained {STR_VAR_1} exp!\p");
static const pchar str_level_up[] = _("{ATTACKING_MON} leveled up!\p");
static const pchar str_healed_o[] = _("{FOE}{ATTACKING_MON} restored some HP!");
static const pchar str_flinched_o[] = _("{FOE}{ATTACKING_MON} flinched\nand couldn’t move!");
static const pchar str_multi_hit[] = _("Hit {STR_VAR_1} time(s)!");
static const pchar str_OHKO[] = _("It’s a one-hit KO!");
static const pchar str_charge_solarbeam_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
static const pchar str_charge_sky_attack_o[] = _("{FOE}{ATTACKING_MON} became\ncloaked in a harsh light!");
static const pchar str_charge_dig_o[] = _("{FOE}{ATTACKING_MON} burrowed\nits way underground");
static const pchar str_charge_dive_o[] = _("{FOE}{ATTACKING_MON} hid underwater!");
static const pchar str_fly_o[] = _("{FOE}{ATTACKING_MON} flew up high!");
static const pchar str_phantom_force_o[] = _("{FOE}{ATTACKING_MON} vanished instantly!");
static const pchar str_shadow_force_o[] = _("{FOE}{ATTACKING_MON} vanished instantly!");
static const pchar str_bounce_o[] = _("{FOE}{ATTACKING_MON} sprang up!");
static const pchar str_sky_drop_o[] = _("{FOE}{ATTACKING_MON} took\n{DEFENDING_MON} into the sky!");
static const pchar str_charge_solarblade_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
static const pchar str_invulnerable_o[] = _("{DEFENDING_MON} was invulnerable\nto the attack!");
static const pchar str_residual_dmg[] = _("{ATTACKING_MON} took some damage from\n{ATTACK_NAME}!");
static const pchar str_residual_status_dmg[] = _("{ATTACKING_MON} took some damage from\nbeing {STATUS_NAME}!");
static const pchar str_fast_asleep_o[] = _("{FOE}{ATTACKING_MON}\nis fast asleep.");
static const pchar str_awoke_o[] = _("{FOE}{ATTACKING_MON}\nwoke up!");
static const pchar str_snapped_out_o[] = _("{FOE}{ATTACKING_MON}\nsnapped out of confusion!");
static const pchar str_hurt_itself_o[] = _("{FOE}{ATTACKING_MON}\nhurt itself in confusion");
static const pchar str_is_confused_o[] = _("{FOE}{ATTACKING_MON} is confused");
static const pchar str_no_pp[] = _("There is no PP left for\nthis move!");
static const pchar str_disabled_pick[] = _("This move is disabled!");
static const pchar str_frozen_solid_o[] = _("{FOE}{ATTACKING_MON} is\nfrozen solid!");
static const pchar str_thawed_out_o[] = _("{FOE}{ATTACKING_MON}\nthawed out!");
static const pchar str_fully_paralyzed_o[] = _("{FOE}{ATTACKING_MON} is paralyzed!\nIt can’t move!");
static const pchar str_clear_smog_o[] = _("{FOE}{DEFENDING_MON}’s stat changes\nwere removed!");
static const pchar str_bounced_back_p[] = _("Foe {DEFENDING_MON}’s {ATTACK_NAME}\nwas bounced back by Magic Coat!");
static const pchar str_bounced_back_o[] = _("{DEFENDING_MON}’s {ATTACK_NAME} was\nbounced back by Magic Coat!");
static const pchar str_shrouded_magiccoat_o[] = _("{FOE}{ATTACKING_MON} shrouded\nitself with Magic Coat!");
static const pchar str_snatch_waiting_o[] = _("{FOE}{ATTACKING_MON} waits for a target\nto make a move!");
static const pchar str_snatched_o[] = _("{FOE}{ATTACKING_MON} snatched\n{DEFENDING_MON}’s move!");
static const pchar str_must_recharge_o[] = _("{FOE}{ATTACKING_MON} must recharge!");
static const pchar str_conversion_gain_type_o[] = _("{FOE}{ATTACKING_MON} transformed\ninto the {PKMN_TYPE}-type!");
static const pchar str_reflect_type_match_o[] = _("{FOE}{ATTACKING_MON}’s type changed\nto match {THE_FOE}{DEFENDING_MON}’s!");
static const pchar str_type_added_o[] = _("The {PKMN_TYPE}-type was added\nto {THE_FOE}{DEFENDING_MON}!");
static const pchar str_ion_deluge_field[] = _("A deluge of ions showers\nthe battlefield!");
static const pchar str_electrified_p[] = _("{FOE}{DEFENDING_MON}’s moves\nhave been electrified!");
static const pchar str_electrified_o[] = _("{DEFENDING_MON}’s moves\nhave been electrified!");
static const pchar str_burnt_out_o[] = _("{FOE}{ATTACKING_MON} burnt\nitself out!");
static const pchar str_protected_itself_o[] = _("{FOE}{ATTACKING_MON} protected\nitself!");
static const pchar str_endured_hit_o[] = _("{FOE}{ATTACKING_MON} endured\nthe hit!");
static const pchar str_braced_self_o[] = _("{FOE}{ATTACKING_MON} braced\nitself!");
static const pchar str_kicked_mat[] = _("It was blocked by\nthe kicked-up mat!");
static const pchar str_protected_side[] = _("{ATTACK_NAME} protected\nthe team!");
static const pchar str_protected_mon[] = _("{ATTACK_NAME} protected {ATTACKING_MON}!");
static const pchar str_broke_protect[] = _("{ATTACK_NAME} broke the\nprotection!");
static const pchar str_rain_continue[] = _("The {WEATHER} continues to fall.");
static const pchar str_rain_stop[] = _("The {WEATHER} stopped.");
static const pchar str_heavy_rain_atk[] = _("The Fire-type attack fizzled out\nin the heavy rain!");
static const pchar str_heavy_rain_lift[] = _("The heavy rain has lifted!");
static const pchar str_sun_start[] = _("The sunlight turned harsh!");
static const pchar str_sun_strong[] = _("The sunlight is strong.");
static const pchar str_sun_finish[] = _("The sunlight faded.");
static const pchar str_harsh_sun_evaporates[] = _("The Water-type attack evaporated\nin the harsh sunlight!");
static const pchar str_harsh_sun_over[] = _("The harsh sunlight faded.");
static const pchar str_sandstorm_start[] = _("A sandstorm kicked up!");
static const pchar str_sandstorm_continue[] = _("The sandstorm rages.");
static const pchar str_sandstorm_o[] = _("{FOE}{ATTACKING_MON} is buffeted\nby the {WEATHER}!");
static const pchar str_sandstorm_finish[] = _("The sandstorm subsided.");
static const pchar str_delta_stream_effectiveness[] = _("The mysterious strong winds\nweakened the attack!");
static const pchar str_delta_stream_fin[] = _("The mysterious strong winds\nweakened the attack!");
static const pchar str_delta_stream_imm[] = _("The mysterious strong winds\nblow on regardless!");
static const pchar str_harsh_sun_imm[] = _("The extremely harsh sunlight\nwas not lessened at all!");
static const pchar str_harsh_rain_imm[] = _("There is no relief\nfrom this heavy rain!");
static const pchar str_a_veil_o[] = _("Aurora Veil made {THE_FOE}team stronger\nagainst physical and special moves!");
static const pchar str_reflect_o[] = _("Reflect raised {THE_FOE}team’s\nDefense!");
static const pchar str_lightscreen_o[] = _("Light Screen raised {THE_FOE}team’s\nSpecial Defense!");
static const pchar str_shattered_barr[] = _("It shattered the barrier!");
static const pchar str_foresaw_atk_o[] = _("{FOE}{ATTACKING_MON} foresaw\nan attack!");
static const pchar str_took_attack_o[] = _("{FOE}{ATTACKING_MON} took\nthe {ATTACK_NAME}!");
static const pchar str_chose_doom_o[] = _("{FOE}{ATTACKING_MON}\nchose Doom Desire as its destiny!");
static const pchar str_wish_true_o[] = _("{FOE}{ATTACKING_MON}’s wish\ncame true!");
static const pchar str_grew_drowsy_o[] = _("{DEFENDING_MON} grew drowsy!");
static const pchar str_began_charging_o[] = _("{FOE}{ATTACKING_MON} began\ncharging power!");
static const pchar str_move_end[] = _("The {ATTACK_NAME} ended.");
static const pchar str_elec_terrain[] = _("An Electric current runs\nacross the battlefield!");
static const pchar str_psyc_terrain[] = _("The battlefield got weird!");
static const pchar str_grass_terrain[] = _("Grass grew to\ncover the battlefield!");
static const pchar str_misty_terrain[] = _("Mist swirled about\nthe battlefield!");
static const pchar str_learnt_move[] = _("{FOE}{ATTACKING_MON} learned\n{ATTACK_NAME}!");
static const pchar str_whos_attack[] = _("{SLOT_MON}’s attack!");
static const pchar str_tailwind_behind[] = _("The tailwind blew from\nbehind {THE_FOE}team!");
static const pchar str_tailwind_peter[] = _("{FOE}Tailwind petered out!");
static const pchar str_twisted_dim[] = _("{FOE}{ATTACKING_MON} twisted\nthe dimensions!");
static const pchar str_twisted_dim_n[] = _("The twisted dimensions\nreturned to normal!");
static const pchar str_wonder_area[] = _("It created a bizzare area in which\nthe Defense and Sp. Def stats\lare swapped!");
static const pchar str_safe_guard_v[] = _("{FOE}{ATTACKING_MON}’s team became\ncloaked in a mystical veil!");
static const pchar str_shield_team_crit[] = _("The {ATTACK_NAME} shielded {THE_FOE}\nteam from critical hits!");
static const pchar str_grav_instense[] = _("Gravity intensified!");
static const pchar str_exec_failed[] = _("{FOE}{ATTACKING_MON}’s move\n{ATTACK_NAME} failed due to {EFFECT_NAME}!");
static const pchar str_was_identified[] = _("{FOE}{ATTACKING_MON} was identified!");
static const pchar str_weaken_type[] = _("{PKMN_TYPE}’s power was weakened!");
static const pchar str_lev_mag[] = _("{FOE}{ATTACKING_MON} levitated\nwith electromagnetism!");
static const pchar str_teleken_hurled[] = _("{FOE}{ATTACKING_MON} was hurled\ninto the air!");
static const pchar str_heal_b[] = _("{FOE}{ATTACKING_MON} was prevented\nfrom healing!");
static const pchar str_guard_s[] = _("{FOE}{ATTACKING_MON} shared its\nguard with the target!");
static const pchar str_power_s[] = _("{FOE}{ATTACKING_MON} shared its\npower with the target!");
static const pchar str_swap_spe[] = _("{FOE}{ATTACKING_MON} swapped its\nspeed stat with the target!");
static const pchar str_enc_rec[] = _("{FOE}{ATTACKING_MON} recieved\nan encore!");
static const pchar str_sub_torment[] = _("{FOE}{ATTACKING_MON} was subjected\nto torment!");
static const pchar str_fell_taunt[] = _("{FOE}{ATTACKING_MON} fell\nfor the taunt!");
static const pchar string_reason_cant[] = _("Can’t use {ATTACK_NAME}\nwhile {EFFECT_NAME} is active!");
static const pchar string_roots_plant[] = _("{FOE}{ATTACKING_MON} planted\nits roots!");
static const pchar str_fell_down[] = _("{FOE}{ATTACKING_MON}\nfell right down!");
static const pchar str_shell_trap_set[] = _("{FOE}{ATTACKING_MON} set\na shell trap!");
static const pchar str_perish_start[] = _("All Pokémon hearing the song\nwill faint in three turns!");
static const pchar str_count_fell[] = _("{ATTACKING_MON}’s perish count fell to {STR_VAR_1}!");
static const pchar str_destiny_bond_end[] = _("{FOE}{ATTACKING_MON} took\nits foe with it!");
static const pchar str_destiny_bond_start[] = _("{FOE}{ATTACKING_MON} is trying to\ntake its foe down with it!");
static const pchar str_grudge[] = _("{FOE}{ATTACKING_MON} wants its\ntarget to hold a grudge!");
static const pchar str_grudge_end[] = _("{FOE}{ATTACKING_MON}’s {ATTACK_NAME}\nlost all its PP from the Grudge!");
static const pchar str_skydrop_start_p[] = _("{FOE}{ATTACKING_MON} took\n{FOE}{DEFENDING_MON} to the sky!");
static const pchar str_skydrop_start_o[] = _("{FOE}{ATTACKING_MON} took\n{DEFENDING_MON} to the sky!");
static const pchar str_skydrop_air[] = _("{FOE}{ATTACKING_MON} is\nimmobolized mid-air!");
static const pchar str_skydrop_free[] = _("{FOE}{ATTACKING_MON} was freed\nfrom the {ATTACK_NAME}!");
static const pchar str_attract[] = _("{FOE}{ATTACKING_MON} fell in love!");
static const pchar str_unleashed_p[] = _("{FOE}{ATTACKING_MON} unleashed\nenergy!");
static const pchar str_rdy_to_help[] = _("{FOE}{ATTACKING_MON} is ready\nto help {DEFENDING_MON}!");
static const pchar str_infestation[] = _("{FOE}{ATTACKING_MON} has been\nafflicted with an infestation!");
static const pchar str_topsy_turvy[] = _("{FOE}{ATTACKING_MON}’s stats changes\nwere inverted!");
static const pchar str_center_attention[] = _("{FOE}{ATTACKING_MON} became\nthe center of attention!");
static const pchar str_stockpile_set[] = _("{FOE}{ATTACKING_MON} stockpiled {STR_VAR_1}!");
static const pchar str_aromatherapy[] = _("A soothing aroma wafted\nthrough the air!");
static const pchar str_copied_stats[] = _("{FOE}{ATTACKING_MON} copied\n{DEFENDING_MON}’s stat changes!");
static const pchar str_pain_split[] = _("The battlers shared\ntheir pain!");
static const pchar str_heal_bell[] = _("A bell chimed!");
static const pchar str_belly_drum[] = _("{FOE}{ATTACKING_MON} maximized\nits Attack!");
static const pchar str_curse[] = _("{ATTACKING_MON} cut its HP own HP\nand laid a curse on the foe!");
static const pchar str_stat_changes_clear[] = _("All stat changes\nwere eliminated!");
static const pchar str_seeded[] = _("{FOE}{ATTACKING_MON} was seeded.");
static const pchar str_sapped[] = _("{FOE}{ATTACKING_MON}’s health was\nsapped by Leech seed.");
static const pchar str_focus_tight[] = _("{FOE}{ATTACKING_MON} is tightening\nits focus!");
static const pchar str_beak_blast[] = _("{FOE}{ATTACKING_MON} started heating\nup its beak!");
static const pchar str_heart_swap[] = _("{FOE}{ATTACKING_MON} switched stat\nchanges with the target!");
static const pchar str_come_back[] = _("{ATTACKING_MON}, come back!");
static const pchar str_send_out[] = _("Go! {ATTACKING_MON}!");
static const pchar str_trapped[] = _("{FOE}{ATTACKING_MON} is trapped\nand cannot switch!");
static const pchar str_trapped_run[] = _("{FOE}{ATTACKING_MON} is trapped\nand cannot run!");
static const pchar str_anger_point[] = _("{FOE}{ATTACKING_MON} maxed its Attack!");
static const pchar str_flash_fire[] = _("{FOE}{ATTACKING_MON} raised\n its Fire power!");
static const pchar str_ability_trace[] = _("{FOE}{ATTACKING_MON} traced {ABILITY_ARBITRARY}!");
static const pchar str_run_away[] = _("{ATTACKING_MON} fled using\n{ABILITY_ARBITRARY}!\p");
static const pchar str_anticipation[] = _("{FOE}{ATTACKING_MON}’s {ABILITY_ARBITRARY} made\nit shudder!");
static const pchar str_frisk[] = _("{FOE}{ATTACKING_MON} frisked {BANK_NAME}\nand found it’s {BANK_ITEM}");


// stat names
static const pchar str_stat_atk[] = _("attack");
static const pchar str_stat_def[] = _("defense");
static const pchar str_stat_spd[] = _("speed");
static const pchar str_stat_spatk[] = _("special attack");
static const pchar str_stat_spdef[] = _("special defense");
static const pchar str_stat_acc[] = _("accuracy");
static const pchar str_stat_evn[] = _("evasion");
static const pchar str_stat_crit[] = _("critical chance");

// status names
static const pchar str_status_paralyze[] = _("paralyzed");
static const pchar str_status_burn[] = _("burned");
static const pchar str_status_poison[] = _("poisoned");
static const pchar str_status_sleep[] = _("put to sleep");
static const pchar str_status_frozen[] = _("frozen");
static const pchar str_status_bpoison[] = _("badly poisoned");
static const pchar str_status_confuse[] = _("confused");
static const pchar str_status_infactuation[] = _("infactuated");

// weather names
static const pchar str_hail_w[] = _("hail");
static const pchar str_sandstorm_w[] = _("sandstorm");
static const pchar str_rain_w[] = _("rain");


static const pchar str_thefoe[] = _("the foe ");
static const pchar str_thefoe_p[] = _("your ");
static const pchar str_nfoe[] = _("Foe ");


static const pchar* battle_strings[STRINGS_TABLE_MAX] = {
   (pchar*)&str_atk_used_o, //0
   (pchar*)&str_infatuated_o, //1
   (pchar*)&str_bide_o, // 2
   (pchar*)&str_focus_lost_o, // 3
   (pchar*)&str_cant_use_o, // 4
   (pchar*)&str_disabled_o, // 5
   (pchar*)&str_failed_o, // 6
   (pchar*)&str_curse_dmg_o, // 7
   (pchar*)str_magnitude_amount_o, // 8
   (pchar*)&str_no_target_o, // 9
   (pchar*)&str_failed_alone, // 10
   (pchar*)&str_immunity_p,
   (pchar*)&str_immunity_p,
   (pchar*)&str_charging_up_razorwind_o, // 13
   (pchar*)&str_solarbeam_o, // 14
   (pchar*)&str_freeze_shock_o, // 15
   (pchar*)&str_ice_burn_o, // 16
   (pchar*)&str_geomancy_o, // 17
   (pchar*)&str_skull_bash_o, // 18
   (pchar*)str_started_rain, // 19
   (pchar*)&str_sturdy_immune_o, // 20
   (pchar*)&str_damp_o, // 21
   (pchar*)&str_cure_status_o, // 22
   (pchar*)&str_effect_ended_o, // 23
   (pchar*)&str_weather_gone, // 24
   (pchar*)&str_gained_type_o, // 25
   (pchar*)&str_confusion_end_o, // 26
   (pchar*)&str_dragout_failed_o, // 27
   (pchar*)&str_stat_mod_harsh_drop_o, // 28
   (pchar*)&str_stat_mod_drop_o, // 29
   (pchar*)&str_stat_mod_harsh_rise_o, // 30
   (pchar*)&str_stat_mod_rise_o, // 31
   (pchar*)&str_ailment_applied_o, // 32
   (pchar*)&str_ailment_immune_o, // 33
   (pchar*)&str_ailment_cured_o, // 34
   (pchar*)&str_delta_stream, // 35
   (pchar*)&str_desolate_land, // 36
   (pchar*)&str_primordial_sea, // 37
   (pchar*)&str_protean_o, // 38
   (pchar*)&str_atk_missed, // 39
   (pchar*)&str_atk_avoided, // 40
   (pchar*)&str_fled_p, (pchar*)&str_fled_o, // 41, 42
   (pchar*)&str_flee_failed, // 43
   (pchar*)&str_move_crit, // 44
   (pchar*)&str_move_immune_p, (pchar*)&str_move_immune_o, // 45, 46
   (pchar*)&str_move_nve, // 47
   (pchar*)&str_move_se, // 48
   (pchar*)&str_recoil, // 49
   (pchar*)&str_drain, // 50
   (pchar*)&str_fainted_o, // 51
   (pchar*)&str_give_exp, // 52
   (pchar*)&str_level_up, // 53
   (pchar*)&str_healed_o, // 54
   (pchar*)&str_flinched_o, // 55
   (pchar*)&str_multi_hit, // 56
   (pchar*)&str_OHKO, // 57
   (pchar*)&str_charge_sky_attack_o, // 58
   (pchar*)&str_charge_dig_o, // 59
   (pchar*)&str_charge_dive_o, // 60
   (pchar*)&str_fly_o, // 61
   (pchar*)&str_phantom_force_o, // 62
   (pchar*)&str_shadow_force_o, // 63
   (pchar*)&str_bounce_o, // 64
   (pchar*)&str_sky_drop_o, // 65
   (pchar*)&str_charge_solarblade_o, // 66
   (pchar*)&str_invulnerable_o, // 67
   (pchar*)&str_residual_dmg, // 68
   (pchar*)&str_stat_mod_cant_go_lower_o, // 69
   (pchar*)&str_stat_mod_cant_go_higher_o, // 70
   (pchar*)&str_stat_mod_severely_fell_p, // 71
   (pchar*)&str_stat_mod_rose_drastically_p, // 72
   (pchar*)&str_residual_status_dmg, // 73
   (pchar*)&str_fast_asleep_o, // 74
   (pchar*)&str_awoke_o, // 75
   (pchar*)&str_snapped_out_o, // 76
   (pchar*)&str_hurt_itself_o, // 77
   (pchar*)&str_is_confused_o, // 78
   (pchar*)&str_no_pp, // 79
   (pchar*)&str_disabled_pick, // 80
   (pchar*)&str_frozen_solid_o, // 81
   (pchar*)&str_thawed_out_o, // 82
   (pchar*)&str_fully_paralyzed_o, // 83
   (pchar*)&str_clear_smog_o, // 84
   (pchar*)&str_bounced_back_p, (pchar*)&str_bounced_back_o, // 85, 86
   (pchar*)&str_shrouded_magiccoat_o, // 87
   (pchar*)&str_snatch_waiting_o, // 88
   (pchar*)&str_snatched_o, // 89
   (pchar*)&str_must_recharge_o, // 90
   (pchar*)&str_conversion_gain_type_o, // 91
   (pchar*)&str_reflect_type_match_o, // 92
   (pchar*)&str_type_added_o, // 93
   (pchar*)&str_ion_deluge_field, // 94
   (pchar*)&str_electrified_p, (pchar*)&str_electrified_o, // 95, 96
   (pchar*)&str_burnt_out_o, // 97
   (pchar*)&str_protected_itself_o, // 98
   (pchar*)&str_endured_hit_o, // 99
   (pchar*)&str_braced_self_o, // 100
   (pchar*)&str_kicked_mat, // 101
   (pchar*)&str_protected_side, // 102
   (pchar*)&str_protected_mon, // 103
   (pchar*)&str_broke_protect, // 104
   (pchar*)&str_rain_continue, // 105
   (pchar*)&str_rain_stop, // 106
   (pchar*)&str_heavy_rain_atk, // 107
   (pchar*)&str_heavy_rain_lift, // 108
   (pchar*)&str_sun_start, // 109
   (pchar*)&str_sun_strong, // 110
   (pchar*)&str_sun_finish, // 111
   (pchar*)&str_harsh_sun_evaporates, // 112
   (pchar*)&str_harsh_sun_over, // 113
   (pchar*)&str_sandstorm_start, // 114
   (pchar*)&str_sandstorm_continue, // 115
   (pchar*)&str_sandstorm_o, // 116
   (pchar*)&str_sandstorm_finish, // 117
   (pchar*)&str_delta_stream_effectiveness, // 118
   (pchar*)&str_delta_stream_fin, // 119
   (pchar*)&str_delta_stream_imm, // 120
   (pchar*)&str_harsh_sun_imm, // 121
   (pchar*)&str_harsh_rain_imm, // 122
   (pchar*)&str_a_veil_o, // 123
   (pchar*)&str_reflect_o, // 124
   (pchar*)&str_lightscreen_o, // 125
   (pchar*)&str_shattered_barr, // 126
   (pchar*)&str_foresaw_atk_o, // 127
   (pchar*)&str_took_attack_o, // 128
   (pchar*)&str_chose_doom_o, // 129
   (pchar*)&str_wish_true_o, // 130
   (pchar*)&str_grew_drowsy_o, // 131
   (pchar*)&str_move_end, // 132
   (pchar*)&str_elec_terrain, // 133
   (pchar*)&str_psyc_terrain, // 134
   (pchar*)&str_grass_terrain, // 135
   (pchar*)&str_misty_terrain, // 136
   (pchar*)&str_learnt_move, // 137
   (pchar*)&str_whos_attack, // 138
   (pchar*)&str_tailwind_behind, // 139
   (pchar*)&str_tailwind_peter, // 140
   (pchar*)&str_twisted_dim, // 141
   (pchar*)&str_twisted_dim_n, // 142
   (pchar*)&str_wonder_area, // 143
   (pchar*)&str_safe_guard_v, // 144
   (pchar*)&str_shield_team_crit, // 145
   (pchar*)&str_grav_instense, // 146
   (pchar*)&str_exec_failed, // 147
   (pchar*)&str_was_identified, // 148
   (pchar*)&str_weaken_type, // 149
   (pchar*)&str_lev_mag, // 150
   (pchar*)&str_teleken_hurled, // 151
   (pchar*)&str_heal_b, // 152
   (pchar*)&str_guard_s, // 153
   (pchar*)&str_power_s, // 154
   (pchar*)&str_swap_spe, // 155
   (pchar*)&str_enc_rec, // 156
   (pchar*)&str_sub_torment, // 157
   (pchar*)&str_fell_taunt, // 158
   (pchar*)&string_reason_cant, // 159
   (pchar*)&string_roots_plant, // 160
   (pchar*)&str_fell_down, // 161
   (pchar*)&str_shell_trap_set, // 162
   (pchar*)&str_perish_start, // 163
   (pchar*)&str_count_fell, // 164
   (pchar*)&str_destiny_bond_end, // 165
   (pchar*)&str_destiny_bond_start, // 166
   (pchar*)&str_grudge, // 167
   (pchar*)&str_grudge_end, // 168
   (pchar*)&str_skydrop_start_p, (pchar*)&str_skydrop_start_o,// 169, 170
   (pchar*)&str_skydrop_air, // 171
   (pchar*)&str_skydrop_free, // 172
   (pchar*)&str_attract, // 173
   (pchar*)&str_unleashed_p, // 174
   (pchar*)&str_rdy_to_help, // 175
   (pchar*)&str_infestation, // 176
   (pchar*)&str_topsy_turvy, // 177
   (pchar*)&str_center_attention, // 178
   (pchar*)&str_stockpile_set, // 179
   (pchar*)&str_aromatherapy, // 180
   (pchar*)&str_copied_stats, // 181
   (pchar*)&str_pain_split, // 182
   (pchar*)&str_heal_bell, // 183
   (pchar*)&str_belly_drum, // 184
   (pchar*)&str_curse, // 185
   (pchar*)&str_stat_changes_clear, // 186
   (pchar*)&str_seeded, // 187
   (pchar*)&str_sapped, // 188
   (pchar*)&str_focus_tight, // 189
   (pchar*)&str_beak_blast, // 190
   (pchar*)&encounter_wild_text, // 191
   (pchar*)&str_heart_swap, // 192
   (pchar*)&str_come_back, // 193
   (pchar*)&str_send_out, // 194
   (pchar*)&str_trapped, // 195
   (pchar*)&str_ability_changed, // 196
   (pchar*)&str_anger_point, // 197
   (pchar*)&str_flash_fire, //198
   (pchar*)&str_ability_trace, //199
   (pchar*)&str_trapped_run, //200
   (pchar*)&str_run_away, // 201
   (pchar*)&str_anticipation, // 202
   (pchar*)&str_frisk, // 203

};


#endif /* BATTLE_PICK_MESSAGES_H_ */
