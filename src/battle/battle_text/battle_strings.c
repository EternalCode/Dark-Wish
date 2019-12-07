#include <pokeagb/pokeagb.h>
#include "battle_pick_message.h"

const static pchar empty_text[] = _("");
const static pchar encounter_wild_text[] = _("A wild {DEFENDING_MON} appeared!\pGo! {ATTACKING_MON}!");
const static pchar str_used_item[] = _("{PLAYER} used\n{ITEM_NAME}!");

const pchar str_stat_mod_severely_fell_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nseverely fell!");
const pchar str_stat_mod_severely_fell_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nseverely fell!");
const pchar str_stat_mod_rose_drastically_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nrose drastically!");
const pchar str_stat_mod_rose_drastically_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nrose drastically!");
const pchar str_stat_mod_cant_go_lower_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any lower!");
const pchar str_stat_mod_cant_go_lower_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any lower!");
const pchar str_stat_mod_cant_go_higher_p[] = _("{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any higher!");
const pchar str_stat_mod_cant_go_higher_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nwon’t go any higher!");

const pchar str_broke_free[] = _("Oh no! the Pokémon broke free!");
const pchar str_appeared_caught[] = _("Aww! it appeared to be caught!");
const pchar str_almost_had_it[] = _("Aargh! Almost had it!");
const pchar str_so_close_too[] = _("Gah! It was so close, too!");
const pchar str_gotcha_caught[] = _("Gotcha! {DEFENDING_MON} was caught!\p");

const pchar str_forgot_selected_move[] = _("{ATTACKING_MON} forgot {ATTACK_NAME}\nand learned {MOVE_NAME_TWO}!\p");
const pchar str_confirm_forget[] = _("Forget {ATTACK_NAME} to\nlearn {MOVE_NAME_TWO}?");
const pchar str_stop_learning_move[] = _("Stop learning\n{MOVE_NAME_TWO}?");
const pchar str_wants_to_learn_move[] = _("{PSLOT_MON} wants to learn the\nmove {MOVE_NAME_TWO}\lbut {PSLOT_MON} can’t learn\lmore than 4 moves.\pMake it forget another move?");
const pchar str_what_move_to_forget[] = _("Which move should\nbe forgotten?");
const pchar str_atk_used_o[] = _("{FOE}{ATTACKING_MON} used\n{ATTACK_NAME}!");
const pchar str_infatuated_o[] = _("{FOE}{ATTACKING_MON}\nis immobolized by love!");
const pchar str_inlove[] = _("{FOE}{ATTACKING_MON} is in love.");
const pchar str_bide_o[] = _("{FOE}{ATTACKING_MON} is\nstoring energy!");
const pchar str_focus_lost_o[] = _("{FOE}{ATTACKING_MON} lost its\nfocus and couldn’t move!");
const pchar str_cant_use_o[] = _("{ATTACKING_MON} can’t use\n{ATTACK_NAME} because of {AILMENT_NAME}!");
const pchar str_disabled_o[] = _("{FOE}{ATTACKING_MON}’s {ATTACK_NAME}\nwas disabled!");
const pchar str_failed_o[] = _("But it failed!");
const pchar str_curse_dmg_o[] = _("{FOE}{ATTACKING_MON} is afflicted\nby {ATTACK_NAME}");
const pchar str_magnitude_amount_o[] = _("MAGNITUDE {STR_VAR_1}!");
const pchar str_no_target_o[] = _("But there was no target!");
const pchar str_failed_alone[] = _("But it failed!");
const pchar str_immunity_p[] = _("{FOE}{ATTACKING_MON}’s {ABILITY}\nmade it immune!");
const pchar str_ability_changed[] = _("{FOE}{ATTACKING_MON}’s {ABILITY_ARBITRARY}\nturned into {ABILITY}!");
const pchar str_charging_up_razorwind_o[] = _("{FOE}{ATTACKING_MON} whipped\nup a whirlwind!");
const pchar str_solarbeam_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
const pchar str_freeze_shock_o[] = _("{FOE}{ATTACKING_MON} became cloaked\nin a freezing light!");
const pchar str_ice_burn_o[] = _("{FOE}{ATTACKING_MON} is radiating\na blazing aura!");
const pchar str_geomancy_o[] = _("{FOE}{ATTACKING_MON} is absorbing\npower!");
const pchar str_skull_bash_o[] = _("{FOE}{ATTACKING_MON} lowered\nits head!");
const pchar str_started_rain[] = _("It started to {WEATHER}!");
const pchar str_sturdy_immune_o[] = _("{FOE}{DEFENDING_MON}’s sturdy makes\nit immune to {ATTACK_NAME}!");
const pchar str_damp_o[] = _("{FOE}{ATTACKING_MON} couldn’t use\n{ATTACK_NAME} because of {DEFENDING_MON}’s DAMP!");
const pchar str_cure_status_o[] = _("{FOE}{ATTACKING_MON}’s cured\nits status!");
const pchar str_effect_ended_o[] = _("{FOE}{ATTACKING_MON}’s\n{ATTACK_NAME} ended.");
const pchar str_weather_gone[] = _("The effects of the weather\ndisappeared.");
const pchar str_gained_type_o[] = _("{FOE}{ATTACKING_MON} gained {TYPE}\nfrom {ABILITY}!");
const pchar str_confusion_end_o[] = _("{FOE}{ATTACKING_MON} is\nno longer confused!");
const pchar str_dragout_failed_o[] = _("{FOE}{ATTACKING_MON} couldn’t be\ndragged out of battle!");
const pchar str_stat_mod_harsh_drop_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\ndropped harshly!");
const pchar str_stat_mod_drop_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\ndropped!");
const pchar str_stat_mod_harsh_rise_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nsharply rose!");
const pchar str_stat_mod_rise_o[] = _("{FOE}{ATTACKING_MON}’s {STAT_NAME}\nrose!");
const pchar str_ailment_applied_o[] = _("{FOE}{ATTACKING_MON} was {STATUS_NAME}!");
const pchar str_ailment_immune_o[] = _("{FOE}{ATTACKING_MON} was immune\nto being {STATUS_NAME}!");
const pchar str_ailment_cured_o[] = _("{FOE}{ATTACKING_MON} was cured\nof all status ailments!");
const pchar str_delta_stream[] = _("A mysterious air current\nis protecting Flying-type Pokémon!");
const pchar str_desolate_land[] = _("The sunlight turned\nextremely harsh!");
const pchar str_primordial_sea[] = _("A heavy rain began to fall!");
const pchar str_protean_o[] = _("{FOE}{ATTACKING_MON}’s Protean changed\nit’s type!");
const pchar str_atk_missed[] = _("The attack missed!");
const pchar str_atk_avoided[] = _("{DEFENDING_MON} avoided the attack!");
const pchar str_fled_p[] = _("Got away safely.\p");
const pchar str_fled_o[] = _("{ATTACKING_MON} fled\p");
const pchar str_flee_failed[] = _("Could not flee!\p"); /* TODO: proper text and reasoning */
const pchar str_move_crit[] = _("A critical hit!");
const pchar str_move_immune_p[] = _("{FOE}{DEFENDING_MON} was immune!");
const pchar str_move_immune_o[] = _("{DEFENDING_MON} was immune!");
const pchar str_move_nve[] = _("It wasn’t very effective");
const pchar str_move_se[] = _("It was super effective!");
const pchar str_recoil[] =_("{ATTACKING_MON} was hurt by recoil!");
const pchar str_drain[] = _("{DEFENDING_MON}’s energy was drained!");
const pchar str_fainted_o[] = _("{FOE}{ATTACKING_MON}\nfainted!\p");
const pchar str_give_exp[] = _("{PSLOT_MON} gained {STR_VAR_1} exp!\p");
const pchar str_level_up[] = _("{PSLOT_MON} leveled up!\p{PSLOT_MON} grew to\nlevel {STR_VAR_1}!\p");
const pchar str_healed_o[] = _("{FOE}{ATTACKING_MON} restored some HP!");
const pchar str_flinched_o[] = _("{FOE}{ATTACKING_MON} flinched\nand couldn’t move!");
const pchar str_multi_hit[] = _("Hit {STR_VAR_1} time(s)!");
const pchar str_OHKO[] = _("It’s a one-hit KO!");
const pchar str_charge_solarbeam_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
const pchar str_charge_sky_attack_o[] = _("{FOE}{ATTACKING_MON} became\ncloaked in a harsh light!");
const pchar str_charge_dig_o[] = _("{FOE}{ATTACKING_MON} burrowed\nits way underground");
const pchar str_charge_dive_o[] = _("{FOE}{ATTACKING_MON} hid underwater!");
const pchar str_fly_o[] = _("{FOE}{ATTACKING_MON} flew up high!");
const pchar str_phantom_force_o[] = _("{FOE}{ATTACKING_MON} vanished instantly!");
const pchar str_shadow_force_o[] = _("{FOE}{ATTACKING_MON} vanished instantly!");
const pchar str_bounce_o[] = _("{FOE}{ATTACKING_MON} sprang up!");
const pchar str_sky_drop_o[] = _("{FOE}{ATTACKING_MON} took\n{DEFENDING_MON} into the sky!");
const pchar str_charge_solarblade_o[] = _("{FOE}{ATTACKING_MON} absorbed\nlight!");
const pchar str_invulnerable_o[] = _("{DEFENDING_MON} was invulnerable\nto the attack!");
const pchar str_residual_dmg[] = _("{ATTACKING_MON} took some damage from\n{ATTACK_NAME}!");
const pchar str_residual_status_dmg[] = _("{ATTACKING_MON} took some damage from\nbeing {STATUS_NAME}!");
const pchar str_fast_asleep_o[] = _("{FOE}{ATTACKING_MON}\nis fast asleep.");
const pchar str_awoke_o[] = _("{FOE}{ATTACKING_MON}\nwoke up!");
const pchar str_snapped_out_o[] = _("{FOE}{ATTACKING_MON}\nsnapped out of confusion!");
const pchar str_hurt_itself_o[] = _("{FOE}{ATTACKING_MON}\nhurt itself in confusion");
const pchar str_is_confused_o[] = _("{FOE}{ATTACKING_MON} is confused");
const pchar str_no_pp[] = _("There is no PP left for\nthis move!");
const pchar str_disabled_pick[] = _("This move is disabled!");
const pchar str_frozen_solid_o[] = _("{FOE}{ATTACKING_MON} is\nfrozen solid!");
const pchar str_thawed_out_o[] = _("{FOE}{ATTACKING_MON}\nthawed out!");
const pchar str_fully_paralyzed_o[] = _("{FOE}{ATTACKING_MON} is paralyzed!\nIt can’t move!");
const pchar str_clear_smog_o[] = _("{FOE}{DEFENDING_MON}’s stat changes\nwere removed!");
const pchar str_bounced_back_p[] = _("Foe {DEFENDING_MON}’s {ATTACK_NAME}\nwas bounced back by Magic Coat!");
const pchar str_bounced_back_o[] = _("{DEFENDING_MON}’s {ATTACK_NAME} was\nbounced back by Magic Coat!");
const pchar str_shrouded_magiccoat_o[] = _("{FOE}{ATTACKING_MON} shrouded\nitself with Magic Coat!");
const pchar str_snatch_waiting_o[] = _("{FOE}{ATTACKING_MON} waits for a target\nto make a move!");
const pchar str_snatched_o[] = _("{FOE}{ATTACKING_MON} snatched\n{DEFENDING_MON}’s move!");
const pchar str_must_recharge_o[] = _("{FOE}{ATTACKING_MON} must recharge!");
const pchar str_conversion_gain_type_o[] = _("{FOE}{ATTACKING_MON} transformed\ninto the {PKMN_TYPE}-type!");
const pchar str_reflect_type_match_o[] = _("{FOE}{ATTACKING_MON}’s type changed\nto match {THE_FOE}{DEFENDING_MON}’s!");
const pchar str_type_added_o[] = _("The {PKMN_TYPE}-type was added\nto {THE_FOE}{DEFENDING_MON}!");
const pchar str_ion_deluge_field[] = _("A deluge of ions showers\nthe battlefield!");
const pchar str_electrified_p[] = _("{FOE}{DEFENDING_MON}’s moves\nhave been electrified!");
const pchar str_electrified_o[] = _("{DEFENDING_MON}’s moves\nhave been electrified!");
const pchar str_burnt_out_o[] = _("{FOE}{ATTACKING_MON} burnt\nitself out!");
const pchar str_protected_itself_o[] = _("{FOE}{ATTACKING_MON} protected\nitself!");
const pchar str_endured_hit_o[] = _("{FOE}{ATTACKING_MON} endured\nthe hit!");
const pchar str_braced_self_o[] = _("{FOE}{ATTACKING_MON} braced\nitself!");
const pchar str_kicked_mat[] = _("It was blocked by\nthe kicked-up mat!");
const pchar str_protected_side[] = _("{ATTACK_NAME} protected\nthe team!");
const pchar str_protected_mon[] = _("{ATTACK_NAME} protected {ATTACKING_MON}!");
const pchar str_broke_protect[] = _("{ATTACK_NAME} broke the\nprotection!");
const pchar str_rain_continue[] = _("The {WEATHER} continues to fall.");
const pchar str_rain_stop[] = _("The {WEATHER} stopped.");
const pchar str_heavy_rain_atk[] = _("The Fire-type attack fizzled out\nin the heavy rain!");
const pchar str_heavy_rain_lift[] = _("The heavy rain has lifted!");
const pchar str_sun_start[] = _("The sunlight turned harsh!");
const pchar str_sun_strong[] = _("The sunlight is strong.");
const pchar str_sun_finish[] = _("The sunlight faded.");
const pchar str_harsh_sun_evaporates[] = _("The Water-type attack evaporated\nin the harsh sunlight!");
const pchar str_harsh_sun_over[] = _("The harsh sunlight faded.");
const pchar str_sandstorm_start[] = _("A sandstorm kicked up!");
const pchar str_sandstorm_continue[] = _("The sandstorm rages.");
const pchar str_sandstorm_o[] = _("{FOE}{ATTACKING_MON} is buffeted\nby the {WEATHER}!");
const pchar str_sandstorm_finish[] = _("The sandstorm subsided.");
const pchar str_delta_stream_effectiveness[] = _("The mysterious strong winds\nweakened the attack!");
const pchar str_delta_stream_fin[] = _("The mysterious strong winds\nweakened the attack!");
const pchar str_delta_stream_imm[] = _("The mysterious strong winds\nblow on regardless!");
const pchar str_harsh_sun_imm[] = _("The extremely harsh sunlight\nwas not lessened at all!");
const pchar str_harsh_rain_imm[] = _("There is no relief\nfrom this heavy rain!");
const pchar str_a_veil_o[] = _("Aurora Veil made {THE_FOE}team stronger\nagainst physical and special moves!");
const pchar str_reflect_o[] = _("Reflect raised {THE_FOE}team’s\nDefense!");
const pchar str_lightscreen_o[] = _("Light Screen raised {THE_FOE}team’s\nSpecial Defense!");
const pchar str_shattered_barr[] = _("It shattered the barrier!");
const pchar str_foresaw_atk_o[] = _("{FOE}{ATTACKING_MON} foresaw\nan attack!");
const pchar str_took_attack_o[] = _("{FOE}{ATTACKING_MON} took\nthe {ATTACK_NAME}!");
const pchar str_chose_doom_o[] = _("{FOE}{ATTACKING_MON}\nchose Doom Desire as its destiny!");
const pchar str_wish_true_o[] = _("{FOE}{ATTACKING_MON}’s wish\ncame true!");
const pchar str_grew_drowsy_o[] = _("{DEFENDING_MON} grew drowsy!");
const pchar str_began_charging_o[] = _("{FOE}{ATTACKING_MON} began\ncharging power!");
const pchar str_move_end[] = _("The {ATTACK_NAME} ended.");
const pchar str_elec_terrain[] = _("An Electric current runs\nacross the battlefield!");
const pchar str_psyc_terrain[] = _("The battlefield got weird!");
const pchar str_grass_terrain[] = _("Grass grew to\ncover the battlefield!");
const pchar str_misty_terrain[] = _("Mist swirled about\nthe battlefield!");
const pchar str_learnt_move[] = _("{FOE}{ATTACKING_MON} learned\n{ATTACK_NAME}!");
const pchar str_whos_attack[] = _("{SLOT_MON}’s attack!");
const pchar str_tailwind_behind[] = _("The tailwind blew from\nbehind {THE_FOE}team!");
const pchar str_tailwind_peter[] = _("{FOE}Tailwind petered out!");
const pchar str_twisted_dim[] = _("{FOE}{ATTACKING_MON} twisted\nthe dimensions!");
const pchar str_twisted_dim_n[] = _("The twisted dimensions\nreturned to normal!");
const pchar str_wonder_area[] = _("It created a bizzare area in which\nthe Defense and Sp. Def stats\lare swapped!");
const pchar str_safe_guard_v[] = _("{FOE}{ATTACKING_MON}’s team became\ncloaked in a mystical veil!");
const pchar str_shield_team_crit[] = _("The {ATTACK_NAME} shielded {THE_FOE}\nteam from critical hits!");
const pchar str_grav_instense[] = _("Gravity intensified!");
const pchar str_exec_failed[] = _("{FOE}{ATTACKING_MON}’s move\n{ATTACK_NAME} failed due to {AILMENT_NAME}!");
const pchar str_was_identified[] = _("{FOE}{ATTACKING_MON} was identified!");
const pchar str_weaken_type[] = _("{PKMN_TYPE}’s power was weakened!");
const pchar str_lev_mag[] = _("{FOE}{ATTACKING_MON} levitated\nwith electromagnetism!");
const pchar str_teleken_hurled[] = _("{FOE}{ATTACKING_MON} was hurled\ninto the air!");
const pchar str_heal_b[] = _("{FOE}{ATTACKING_MON} was prevented\nfrom healing!");
const pchar str_guard_s[] = _("{FOE}{ATTACKING_MON} shared its\nguard with the target!");
const pchar str_power_s[] = _("{FOE}{ATTACKING_MON} shared its\npower with the target!");
const pchar str_swap_spe[] = _("{FOE}{ATTACKING_MON} swapped its\nspeed stat with the target!");
const pchar str_enc_rec[] = _("{FOE}{ATTACKING_MON} recieved\nan encore!");
const pchar str_sub_torment[] = _("{FOE}{ATTACKING_MON} was subjected\nto torment!");
const pchar str_fell_taunt[] = _("{FOE}{ATTACKING_MON} fell\nfor the taunt!");
const pchar string_reason_cant[] = _("Can’t use {ATTACK_NAME}\nwhile {AILMENT_NAME} is active!");
const pchar string_roots_plant[] = _("{FOE}{ATTACKING_MON} planted\nits roots!");
const pchar str_fell_down[] = _("{FOE}{ATTACKING_MON}\nfell right down!");
const pchar str_shell_trap_set[] = _("{FOE}{ATTACKING_MON} set\na shell trap!");
const pchar str_perish_start[] = _("All Pokémon hearing the song\nwill faint in three turns!");
const pchar str_count_fell[] = _("{ATTACKING_MON}’s perish count fell to {STR_VAR_1}!");
const pchar str_destiny_bond_end[] = _("{FOE}{ATTACKING_MON} took\nits foe with it!");
const pchar str_destiny_bond_start[] = _("{FOE}{ATTACKING_MON} is trying to\ntake its foe down with it!");
const pchar str_grudge[] = _("{FOE}{ATTACKING_MON} wants its\ntarget to hold a grudge!");
const pchar str_grudge_end[] = _("{FOE}{ATTACKING_MON}’s {ATTACK_NAME}\nlost all its PP from the Grudge!");
const pchar str_skydrop_start_p[] = _("{FOE}{ATTACKING_MON} took\n{FOE}{DEFENDING_MON} to the sky!");
const pchar str_skydrop_start_o[] = _("{FOE}{ATTACKING_MON} took\n{DEFENDING_MON} to the sky!");
const pchar str_skydrop_air[] = _("{FOE}{ATTACKING_MON} is\nimmobolized mid-air!");
const pchar str_skydrop_free[] = _("{FOE}{ATTACKING_MON} was freed\nfrom the {ATTACK_NAME}!");
const pchar str_attract[] = _("{FOE}{ATTACKING_MON} fell in love!");
const pchar str_unleashed_p[] = _("{FOE}{ATTACKING_MON} unleashed\nenergy!");
const pchar str_rdy_to_help[] = _("{FOE}{ATTACKING_MON} is ready\nto help {DEFENDING_MON}!");
const pchar str_infestation[] = _("{FOE}{ATTACKING_MON} has been\nafflicted with an infestation!");
const pchar str_topsy_turvy[] = _("{FOE}{ATTACKING_MON}’s stats changes\nwere inverted!");
const pchar str_center_attention[] = _("{FOE}{ATTACKING_MON} became\nthe center of attention!");
const pchar str_stockpile_set[] = _("{FOE}{ATTACKING_MON} stockpiled {STR_VAR_1}!");
const pchar str_aromatherapy[] = _("A soothing aroma wafted\nthrough the air!");
const pchar str_copied_stats[] = _("{FOE}{ATTACKING_MON} copied\n{DEFENDING_MON}’s stat changes!");
const pchar str_pain_split[] = _("The battlers shared\ntheir pain!");
const pchar str_heal_bell[] = _("A bell chimed!");
const pchar str_belly_drum[] = _("{FOE}{ATTACKING_MON} maximized\nits Attack!");
const pchar str_curse[] = _("{ATTACKING_MON} cut its HP own HP\nand laid a curse on the foe!");
const pchar str_stat_changes_clear[] = _("All stat changes\nwere eliminated!");
const pchar str_seeded[] = _("{FOE}{ATTACKING_MON} was seeded.");
const pchar str_sapped[] = _("{FOE}{ATTACKING_MON}’s health was\nsapped by Leech seed.");
const pchar str_focus_tight[] = _("{FOE}{ATTACKING_MON} is tightening\nits focus!");
const pchar str_beak_blast[] = _("{FOE}{ATTACKING_MON} started heating\nup its beak!");
const pchar str_heart_swap[] = _("{FOE}{ATTACKING_MON} switched stat\nchanges with the target!");
const pchar str_come_back[] = _("{ATTACKING_MON}, come back!");
const pchar str_send_out[] = _("Go! {ATTACKING_MON}!");
const pchar str_trapped[] = _("{FOE}{ATTACKING_MON} is trapped\nand cannot switch!");
const pchar str_trapped_run[] = _("{FOE}{ATTACKING_MON} is trapped\nand cannot run!");
const pchar str_anger_point[] = _("{FOE}{ATTACKING_MON} maxed its Attack!");
const pchar str_flash_fire[] = _("{FOE}{ATTACKING_MON} raised\n its Fire power!");
const pchar str_ability_trace[] = _("{FOE}{ATTACKING_MON} traced {ABILITY_ARBITRARY}!");
const pchar str_run_away[] = _("{ATTACKING_MON} fled using\n{ABILITY_ARBITRARY}!\p");
const pchar str_anticipation[] = _("{FOE}{ATTACKING_MON}’s {ABILITY_ARBITRARY} made\nit shudder!");
const pchar str_frisk[] = _("{FOE}{ATTACKING_MON} frisked {BANK_NAME}\nand found it’s {BANK_ITEM}");
const pchar str_learn_move[] = _("{PSLOT_MON} learnt {MOVE_NAME_TWO}!\p");
const pchar str_disabled_use[] = _("{FOE}{ATTACKING_MON}’s {ATTACK_NAME}\nis disabled!");
const pchar str_absorbed_energy_p[] = _("Foe {DEFENDING_MON} had its\nenergy drained!");
const pchar str_absorbed_energy_o[] = _("{DEFENDING_MON} had its\nenergy drained!");

// stat names
const pchar str_stat_atk[] = _("attack");
const pchar str_stat_def[] = _("defense");
const pchar str_stat_spd[] = _("speed");
const pchar str_stat_spatk[] = _("special attack");
const pchar str_stat_spdef[] = _("special defense");
const pchar str_stat_acc[] = _("accuracy");
const pchar str_stat_evn[] = _("evasion");
const pchar str_stat_crit[] = _("critical chance");

// status names
const pchar str_status_paralyze[] = _("paralyzed");
const pchar str_status_burn[] = _("burned");
const pchar str_status_poison[] = _("poisoned");
const pchar str_status_sleep[] = _("put to sleep");
const pchar str_status_frozen[] = _("frozen");
const pchar str_status_bpoison[] = _("badly poisoned");
const pchar str_status_confuse[] = _("confused");
const pchar str_status_infactuation[] = _("infactuated");

// weather names
const pchar str_hail_w[] = _("hail");
const pchar str_sandstorm_w[] = _("sandstorm");
const pchar str_rain_w[] = _("rain");


const pchar str_thefoe[] = _("the foe ");
const pchar str_thefoe_p[] = _("your ");
const pchar str_nfoe[] = _("Foe ");


const pchar* battle_strings[STRINGS_TABLE_MAX] = {
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
   (pchar*)&empty_text, // 204
   (pchar*)&str_learn_move, // 205
   (pchar*)&str_used_item, // 206
   (pchar*)&str_inlove, // 207
   (pchar*)&str_broke_free, // 208
   (pchar*)&str_appeared_caught, // 209
   (pchar*)&str_almost_had_it, // 210
   (pchar*)&str_so_close_too, // 211
   (pchar*)&str_gotcha_caught, // 212
   (pchar*)&str_wants_to_learn_move, // 213
   (pchar*)&str_what_move_to_forget, // 214
   (pchar*)&str_stop_learning_move, // 215
   (pchar*)&str_confirm_forget, // 216
   (pchar*)&str_forgot_selected_move, // 217
   (pchar*)&str_disabled_use, // 218
   (pchar*)&str_absorbed_energy_p, (pchar*)&str_absorbed_energy_o, // 219, 220
};
