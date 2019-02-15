#ifndef BATTLE_ABILITIES_TABLE_H_
#define BATTLE_ABILITIES_TABLE_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"
#include "../moves/moves.h"
#include "ability_override.h"

typedef void (*AbilityBeforeTurn)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*AbilityOnStart)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityBeforeSwitchOutCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityBeforeMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnFailCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnModifyMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef enum TryHitMoveStatus (*AbilityOnTryhitCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*AbilityOnBasePowerCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*AbilityOnDamageCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnEffectCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*AbilityOnAfterMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*AbilityOnStatusCallback)(u8 user, u8 source, u16 ailment, struct anonymous_callback* acb);
typedef bool (*AbilityOnStatBoostModCallback)(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
typedef u16 (*AbilityOnStatCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*AbilityAfterStatBoostModCallback)(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
typedef u8 (*AbilityOnResidualCallback)(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
typedef void (*AbilityOnDrainCallback)(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
typedef u16 (*AbilityOnEffectiveness)(u8 target_type, u8 src, u16 move_type, struct anonymous_callback* acb); // acb->data == ((attacker << 16) | move_effectiveness);
typedef void(*AbilityOnFaintCallback)(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
typedef void(*AbilityOnFlinchCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef bool(*AbilityOnTrapCallback)(u8 user, u8 source, u8 trapType);
typedef bool(*AbilityOnOverrideTrapCallback)(u8 user, u8 source, u8 trapType);

struct ability_data {
    AbilityBeforeTurn before_turn;
    AbilityOnStart on_start;
    AbilityBeforeSwitchOutCallback before_switch;
    AbilityBeforeMoveCallback before_move;
    AbilityOnFailCallback on_fail;
    AbilityOnModifyMoveCallback on_modify_move;
    AbilityOnTryhitCallback on_tryhit;
    AbilityOnEffectiveness on_effectiveness;
    AbilityOnBasePowerCallback on_base_power;
    AbilityOnDamageCallback on_damage;
    AbilityOnEffectCallback on_effect;
    AbilityOnDrainCallback on_drain;
    AbilityOnAfterMoveCallback on_after_move;
    AbilityOnStatusCallback on_status;
    AbilityOnStatCallback on_stat; // when a base stat is read. acb->data_ptr = stat total. move = stat_id
    AbilityOnStatBoostModCallback on_stat_boost_mod;
    AbilityAfterStatBoostModCallback after_stat_boost_mod;
    AbilityOnResidualCallback on_residual;
    AbilityOnFaintCallback on_faint;
    AbilityOnFlinchCallback on_flinch;
    AbilityOnTrapCallback on_trap;
    AbilityOnOverrideTrapCallback on_trap_override;
    u32 a_flags;
};

extern struct ability_data abilities[];
extern const pchar ability_names[][17];

/* Ability Flags */
#define A_FLAG_RECOIL_DMG_PREVENT (1 << 1)
#define A_FLAG_SANDSTORM_DMG_PREVENT (1 << 2)
#define A_FLAG_HAIL_DMG_PREVENT (1 << 3)
#define A_FLAG_POWDER_EFX_PREVENT (1 << 4)
#define A_FLAG_AFTERMATH_DMG_PREVENT (1 << 5)
#define A_FLAG_INDIRECT_DMG_PREVENT (1 << 6)
#define A_FLAG_SECONDARIES_PREVENT (1 << 7)
#define A_FLAG_OPP_SECONDARIES_PREVENT (1 << 8)
#define A_FLAG_FORCED_SWITCHING_PREVENT (1 << 9)
#define HAS_ABILITY_FLAG(ability, flag) (abilities[ability].a_flags & flag)

/* Callback externs */
extern u8 ability_none_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void stench_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 limber_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern u8 insomnia_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern u8 immunity_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern u8 waterveil_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern u8 magmaarmor_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern u8 vitalspirit_on_status(u8 user, u8 source, u16 ailment , struct anonymous_callback* acb);
extern void technician_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern bool contrary_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
extern bool simple_on_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
extern void defiant_after_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
extern void competitive_after_stat_boost_mod(u8 user, u8 source, u16 stat_id, struct anonymous_callback* acb);
extern void steelworker_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void colorchange_on_after_move(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void heatproof_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void drizzle_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void sandstream_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void snowwarning_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void drought_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 speedboost_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void ironfist_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void reckless_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void strongjaw_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void megalauncher_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void adaptability_on_base_power(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void tintedlens_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void filter_variations_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 flamebody_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 poisonpoint_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u8 static_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void liquid_ooze_on_drain(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 cursed_body_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 weak_armor_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 justified_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rattled_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 stamina_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 water_compaction_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 effect_spore_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rough_skin_variations_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 flamebody_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 cute_charm_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 aftermath_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 poison_touch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 mummy_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 gooey_variations_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void pick_pocket_on_secondary(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus oblivious_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 oblivious_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern u8 own_tempo_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern u8 poison_heal_on_effect(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern u8 sweet_veil_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern void prankster_before_turn(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern void gale_wings_before_turn(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern bool clear_body_variations_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool keen_eye_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool hyper_cutter_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool white_smoke_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool big_pecks_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool flower_veil_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u16 keen_eye_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 flower_veil_on_status(u8 user, u8 src, u16 ailment, struct anonymous_callback* acb);
extern u16 scrappy_on_effectiveness(u8 target_type, u8 src, u16 move_type, struct anonymous_callback* acb);
extern u8 infiltrator_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 battle_armor_variations_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void moxie_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void beast_boost_on_damage(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void soul_heart_on_faint(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void receiver_variations_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void normalize_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void refrigerate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void pixilate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void aerilate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void galvanize_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 liquid_voice_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 serenegrace_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void neuro_force_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void shadow_shield_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 skill_link_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u16 super_luck_on_stat(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 merciless_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 long_reach_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void sturdy_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 truant_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 moody_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void slow_start_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 angerpoint_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void tough_claws_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void analytic_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void flare_boost_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void toxic_boost_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void battery_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void rivalry_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void sand_force_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u16 victory_star_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 huge_power_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 compound_eyes_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 hustle_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 fur_coat_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 overgrow_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 blaze_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 torrent_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 swarm_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 grass_pelt_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 defeatist_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 thick_fat_before_move(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern void fluffy_on_damage(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 water_bubble_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 water_bubble_on_status(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern void friend_guard_on_damage(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 shed_skin_on_residual(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 guts_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 marvel_scale_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 early_bird_on_residual(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 synchronize_on_status(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 tangled_feet_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 quick_feet_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 plus_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 minus_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 comatose_on_status(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 pressure_on_effect(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern u16 slush_rush_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 sand_rush_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 swift_swim_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 chlorophyll_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 sand_veil_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u16 snow_cloak_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 inner_focus_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void steadfast_on_flinch(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void download_on_start(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern enum TryHitMoveStatus motor_drive_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus sap_sipper_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus lightning_rod_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus storm_drain_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus bulletproof_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus soundproof_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus overcoat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus dazzling_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus volt_absorb_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus water_absorb_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus flash_fire_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback *acb);
extern enum TryHitMoveStatus noguard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 bad_dreams_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 healer_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 wimp_out_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 berserk_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u16 surge_surfer_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern void sniper_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus damp_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus wonder_guard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus telepathy_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus magic_bounce_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus aroma_veil_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void sheer_force_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void fairy_aura_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void dark_aura_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 rain_dish_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void cloud_nine_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern enum TryHitMoveStatus dry_skin_try_hit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void dry_skin_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 dry_skin_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 hydration_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u16 solar_power_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb);
extern u8 solar_power_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 leaf_guard_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb);
extern enum TryHitMoveStatus leaf_guard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 ice_body_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern void intimidate_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 natural_cure_before_switch(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
extern void trace_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern bool magnetpull_on_trap(u8 user, u8 affectedMon, u8 trapType);
extern bool arena_trap_on_trap(u8 user, u8 affectedMon, u8 trapType);
extern bool run_away_on_override_trap(u8 affectedMon, u8 user, u8 trapType);
extern void anticipation_on_start(u8 user, u8 src, u16 atk, struct anonymous_callback* acb);
extern u8 unaware_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);


#endif /* BATTLE_ABILITIES_TABLE_H_ */
