#include <pokeagb/pokeagb.h>
#include "../moves/moves.h"
#include "battle_abilities.h"


struct ability_data abilities[] = {
	{
		// None - Example
		.before_turn = NULL,
		.before_switch = NULL,
		.before_move = NULL,
		.on_fail = NULL,
		.on_modify_move = NULL,
		.on_tryhit = NULL,
		.on_base_power = NULL,
		.on_damage = NULL,
		.on_effect = ability_none_on_effect,
		.on_after_move = NULL,
		.on_status = NULL,
	},
	{
		// Stench
		.on_damage = stench_on_damage,
	},
	{
		// Drizzle
		.on_start = drizzle_on_start,
	},
	{
		// Speed Boost
		.on_residual = speedboost_on_residual,
	},
	{
		// Battle Armor
		.on_modify_move = battle_armor_variations_on_modify_move,
	},
	{
		// Sturdy
		.on_damage = sturdy_on_dmg,
	},
	{
		// Damp
		.on_tryhit = damp_on_tryhit,
		.a_flags = A_FLAG_AFTERMATH_DMG_PREVENT,
	},
	{
		// Limber
		.on_status = limber_on_status,
	},
	{
		// Sand Veil
		.on_stat = sand_veil_on_stat,
		.a_flags = A_FLAG_SANDSTORM_DMG_PREVENT,
	},
	{
		// Static
		.on_effect = static_on_effect,
	},
	{
		// Volt Absorb
		.on_tryhit = volt_absorb_on_tryhit,
	},
	{
		// Water Absorb
		.on_tryhit = water_absorb_on_tryhit,
	},
	{
		// Oblivious
		.on_tryhit = oblivious_on_tryhit,
		.on_status = oblivious_on_status,
	},
	{
		// Cloud nine
		.on_start = cloud_nine_on_start,
	},
	{
		// Compound Eyes
		.on_stat = compound_eyes_on_stat,
	},
	{
		// Insomnia
		.on_status = insomnia_on_status,
	},
	{
		// Color Change
		.on_after_move = colorchange_on_after_move,
	},
	{
		// Immunity
		.on_status = immunity_on_status,
	},
	{
		// Flash Fire
		.on_tryhit = flash_fire_on_tryhit,
	},
	{
		// Shield dust
		.a_flags = A_FLAG_OPP_SECONDARIES_PREVENT,
	},
	{
		// Own Tempo
		.on_status = own_tempo_on_status,
	},
	{
		// Suction cups
		.a_flags = A_FLAG_FORCED_SWITCHING_PREVENT,
	},
	{
		// Intimidate
		.on_start = intimidate_on_start,
	},
	{
		// SHADOWTAG
	},
	{
		// Rough Skin
		.on_effect = rough_skin_variations_on_effect,
	},
	{
		// Wonder Guard
		.on_tryhit = wonder_guard_on_tryhit,
	},
	{
		// Levitate
		/* Ability effect is added in as a clause to the is_grounded function. See grounded_effect.c */
	},
	{
		// Effect Spore
		.on_effect = effect_spore_effect,
	},
	{
		// SYNCHRONIZE
		.on_status = synchronize_on_status,
	},
	{
		// Clear Body
		.on_stat_boost_mod = clear_body_variations_on_stat_boost,
	},
	{
		// Natural cure
		.before_switch = natural_cure_before_switch,
	},
	{
		// Lightning Rod
		.on_tryhit = lightning_rod_on_tryhit,
	},
	{
		// Serene Grace
		.on_modify_move = serenegrace_on_modify_move,
	},
	{
		// Swift Swim
		.on_stat = swift_swim_on_stat,
	},
	{
		// Chlorophyll
		.on_stat = chlorophyll_on_stat,
	},
	{
		// Illuminate
		/* Note: This Ability doesn't have an in battle effect */
	},
	{
		// Trace
		.on_start = trace_on_start,
	},
	{
		// Huge Power
		.on_stat = huge_power_on_stat,
	},
	{
		// Poison Point
		.on_effect = poisonpoint_on_effect,
	},
	{
		// Inner Focus
		.on_modify_move = inner_focus_on_modify_move,
	},
	{
		// Magma Armor
		.on_status = magmaarmor_on_status,
	},
	{
		// Water Veil
		.on_status = waterveil_on_status,
	},
	{
		// Magnetpull
		.on_trap = magnetpull_on_trap,
	},
	{
		// Soundproof
		.on_tryhit = soundproof_on_tryhit,
	},
	{
		// Rain Dish
		.on_residual = rain_dish_on_residual,
	},
	{
		// Sand Stream
		.on_start = sandstream_on_start,
	},
	{
		// Pressure
		.on_effect = pressure_on_effect,
	},
	{
		// Thick fat
		.before_move = thick_fat_before_move,
	},
	{
		// Early bird
		.on_residual = early_bird_on_residual,
	},
	{
		// Flame Body
		.on_effect = flamebody_on_effect,
	},
	{
		// Run away
		.on_trap_override = run_away_on_override_trap,
	},
	{
		// Keen Eye
		.on_stat_boost_mod = keen_eye_on_stat_boost,
		.on_stat = keen_eye_on_stat,
	},
	{
		// Hyper Cutter
		.on_stat_boost_mod = hyper_cutter_on_stat_boost,
	},
	{
		// PICKUP TODO
	},
	{
		// TRUANT
		.before_move = truant_on_before_move,
	},
	{
		// Hustle
		.on_stat = hustle_on_stat,
	},
	{
		// Cute Charm
		.on_effect = cute_charm_on_effect,
	},
	{
		// PLUS
		.on_stat = plus_on_stat,
	},
	{
		// MINUS
		.on_stat = minus_on_stat,
	},
	{
		// FORECAST
	},
	{
		// STICKYHOLD TODO
	},
	{
		// Shed Skin
		.on_residual = shed_skin_on_residual,
	},
	{
		// Guts
		.on_stat = guts_on_stat,
	},
	{
		// Marvel Scale
		.on_stat = marvel_scale_on_stat,
	},
	{
		// Liquid Ooze
		.on_drain = liquid_ooze_on_drain,
	},
	{
		// Overgrow
		.on_stat = overgrow_on_stat,
	},
	{
		// Blaze
		.on_stat = blaze_on_stat,
	},
	{
		// Torrent
		.on_stat = torrent_on_stat,
	},
	{
		// Swarm
		.on_stat = swarm_on_stat,
	},
	{
		// ROCKHEAD
		.a_flags = A_FLAG_RECOIL_DMG_PREVENT,
	},
	{
		// Drought
		.on_start = drought_on_start,
	},
	{
		// Arena trap
		.on_trap = arena_trap_on_trap,
	},
	{
		// Vital Spirit
		.on_status = vitalspirit_on_status,
	},
	{
		// White Smoke
		.on_stat_boost_mod = white_smoke_on_stat_boost,
	},
	{
		// Pure Power
		.on_stat = huge_power_on_stat,
	},
	{
		// Shell Armor
		.on_modify_move = battle_armor_variations_on_modify_move,
	},
	{
		// Air lock
		/* Clone effect of cloud nine */
		.on_start = cloud_nine_on_start,
	},
	{
		// Tangled Feet
		.on_stat = tangled_feet_on_stat,
	},
	{
		// Motor Drive
		.on_tryhit = motor_drive_on_tryhit,
	},
	{
		// Rivalry
		.on_base_power = rivalry_on_base_power,
	},
	{
		// STEADFAST
		.on_flinch = steadfast_on_flinch,
	},
	{
		// Snow Cloak
		.on_stat = snow_cloak_on_stat,
		.a_flags = A_FLAG_HAIL_DMG_PREVENT,
	},
	{
		// GLUTTONY TODO
	},
	{
		// Anger Point
		.on_effect = angerpoint_on_effect,
	},
	{
		// UNBURDEN TODO
	},
	{
		// Heatproof
        .on_base_power = heatproof_on_base_power,
	},
    {
		// Simple
		.on_stat_boost_mod = simple_on_stat_boost_mod,
	},
	{
		// Dry Skin
		.on_tryhit = dry_skin_try_hit,
		.on_base_power = dry_skin_on_base_power,
		.on_residual = dry_skin_on_residual,
	},
	{
		// Download
		.on_start = download_on_start,
	},
	{
		// Iron Fist
		.on_base_power = ironfist_on_base_power,
	},
	{
		// Poison Heal
		.on_effect = poison_heal_on_effect,
	},
	{
		// Adaptability
		.on_base_power = adaptability_on_base_power,
	},
	{
		// Skill Link
		.on_modify_move = skill_link_on_modify_move,
	},
	{
		// Hydration
		.on_residual = hydration_on_residual,
	},
	{
		// Solar Power
		.on_residual = solar_power_on_residual,
		.on_stat = solar_power_on_stat,
	},
	{
		// Quick Feet
		.on_stat = quick_feet_on_stat,
	},
	{
		// Normalize
		.before_turn = normalize_before_turn,
	},
	{
		// SNIPER
		.on_damage = sniper_on_damage,
	},
	{
		// Magic Guard
		.a_flags = A_FLAG_INDIRECT_DMG_PREVENT,
	},
	{
		// NOGUARD
		.on_tryhit = noguard_on_tryhit,
	},
	{
		// STALL
	},
	{
		// Technician
		.on_base_power = technician_on_base_power,
	},
	{
		// Leaf Guard
		.on_tryhit = leaf_guard_on_tryhit,
		.on_status = leaf_guard_on_status,

	},
	{
		// KLUTZ TODO
	},
	{
		// MOLDBREAKER TODO
	},
	{
		// SUPERLUCK
		.on_stat = super_luck_on_stat,
	},
	{
		// Aftermath
		.on_effect = aftermath_on_effect,
	},
	{
		// Anticipation
		.on_start = anticipation_on_start,
	},
	{
		// FOREWARN
	},
	{
		// Unaware
		.on_modify_move = unaware_on_modify_move,
	},
	{
		// Tinted Lens
		.on_damage = tintedlens_on_damage,
	},
	{
		// Filter
		.on_damage = filter_variations_on_damage,
	},
	{
		// SLOWSTART
		.on_start = slow_start_on_start,
	},
	{
		// Scrappy
		.on_effectiveness = scrappy_on_effectiveness,
	},
	{
		// Storm Drain
		.on_tryhit = storm_drain_on_tryhit,
	},
	{
		// Ice Body
		.a_flags = A_FLAG_HAIL_DMG_PREVENT,
		.on_residual = ice_body_on_residual,
	},
	{
		// Solid Rock
		.on_damage = filter_variations_on_damage,
	},
	{
		// Snow Warning
		.on_start = snowwarning_on_start,
	},
	{
		// Honey Gather
		/* Note: This Ability doesn't have an in battle effect */
	},
	{
		// Frisk
		.on_start = frisk_on_start,
	},
	{
		// Reckless
		.on_base_power = reckless_on_base_power,
	},
	{
		// MULTITYPE
	},
	{
		// FLOWERGIFT
	},
	{
		// Bad dreams
		.on_residual = bad_dreams_on_residual,
	},
	{
		// Pickpocket
		.after_stat_boost_mod = pick_pocket_on_secondary,
	},
	{
		// Sheer Force
		.on_base_power = sheer_force_on_base_power,
		.a_flags = A_FLAG_SECONDARIES_PREVENT,
	},
	{
		// Contrary
		.on_stat_boost_mod = contrary_on_stat_boost_mod,
	},
	{
		// UNNERVE TODO
	},
	{
		// Defiant
		.after_stat_boost_mod = defiant_after_stat_boost_mod,
	},
	{
		// Defeatist
		.on_stat = defeatist_on_stat,
	},
	{
		// Cursed Body
		.on_effect = cursed_body_on_effect,
	},
	{
		// healer
		.on_residual = healer_on_residual,
	},
	{
		// FRIENDGUARD
		.on_damage = friend_guard_on_damage,
	},
	{
		// Weak Armor
		.on_effect = weak_armor_on_effect,
	},
	{
		// HEAVYMETAL
	},
	{
		// LIGHTMETAL TODO
	},
	{
		// Multi-scale
		.on_damage = shadow_shield_on_damage,
	},
	{
		// Toxic Boost
		.on_base_power = toxic_boost_on_base_power,
	},
	{
		// Flare Boost
		.on_base_power = flare_boost_on_base_power,
	},
	{
		// HARVEST TODO
	},
	{
		// telepathy
		.on_tryhit = telepathy_on_tryhit,
	},
	{
		// Moody
		.on_residual = moody_on_residual,
	},
	{
		// Overcoat
		.on_tryhit = overcoat_on_tryhit,
		.a_flags = (A_FLAG_SANDSTORM_DMG_PREVENT | A_FLAG_HAIL_DMG_PREVENT | A_FLAG_POWDER_EFX_PREVENT),
	},
	{
		// Poison Touch
		.on_effect = poison_touch_on_effect,
	},
	{
		// REGENERATOR TODO
	},
	{
		// Big Pecks
		.on_stat_boost_mod = big_pecks_on_stat_boost,
	},
	{
		// Sand Rush
		.on_stat = sand_rush_on_stat,
		.a_flags = A_FLAG_SANDSTORM_DMG_PREVENT,
	},
	{
		// WONDERSKIN TODO
	},
	{
		// Analytic
		.on_base_power = analytic_on_base_power,
	},
	{
		// ILLUSION
	},
	{
		// IMPOSTER
	},
	{
		// Infiltrator
		.on_modify_move = infiltrator_modify_move,
	},
	{
		// Mummy
		.on_effect = mummy_on_effect,
	},
	{
		// Moxie
		.on_damage = moxie_on_damage,
	},
	{
		// Justified
		.on_effect = justified_on_effect,
	},
	{
		// Rattled
		.on_effect = rattled_on_effect,
	},
	{
		// MAGICBOUNCE
		.on_tryhit = magic_bounce_on_tryhit,
	},
	{
		// Sap Sipper
		.on_tryhit =sap_sipper_on_tryhit,
	},
	{
		// Prankster
		.before_turn = prankster_before_turn,
	},
	{
		// Sand Force
		.on_base_power = sand_force_on_base_power,
		.a_flags = A_FLAG_SANDSTORM_DMG_PREVENT,
	},
	{
		// Iron Barbs
		.on_effect = rough_skin_variations_on_effect,
	},
	{
		// ZENMODE
	},
	{
		// Victory Star
		.on_stat = victory_star_on_stat,
	},
	{
		// TURBOBLAZE
	},
	{
		// TERAVOLT
	},
	{
		// Aroma Veil
		.on_tryhit = aroma_veil_on_tryhit,
	},
	{
		// Flower Veil
		.on_stat_boost_mod = flower_veil_on_stat_boost,
		.on_status = flower_veil_on_status,
	},
	{
		// CHEEKPOUCH TODO
	},
	{
		// PROTEAN
	},
	{
		// Fur Coat
		.on_stat = fur_coat_on_stat,
	},
	{
		// MAGICIAN
	},
	{
		// Bullet Proof
		.on_tryhit = bulletproof_on_tryhit,
	},
	{
		// Competitive
		.after_stat_boost_mod = competitive_after_stat_boost_mod,
	},
	{
		// Strong Jaw
		.on_base_power = strongjaw_on_base_power,
	},
	{
		// Refrigerate
		.before_turn = refrigerate_before_turn,
	},
	{
		// Sweet Veil
		.on_status = sweet_veil_on_status,
	},
	{
		// STANCE CHANGE TODO
	},
	{
		// Gale Wings
		.before_turn = gale_wings_before_turn,
	},
	{
		// Mega Launcher
		.on_base_power = megalauncher_on_base_power,
	},
	{
		// Grass Pelt
		.on_stat = grass_pelt_on_stat,
	},
	{
		// SYMBIOSIS
	},
	{
		// Tough Claws
		.on_base_power = tough_claws_on_base_power,
	},
	{
		// Pixilate
		.before_turn = pixilate_before_turn,
	},
	{
		// Gooey
		.on_effect = gooey_variations_on_effect,
	},
	{
		// Aerilate
		.before_turn = aerilate_before_turn,
	},
	{
		// PARENTALBOND
	},
	{
		// Dark Aura
		.on_base_power = dark_aura_on_base_power,
	},
	{
		// Fairy Aura
		.on_base_power = fairy_aura_on_base_power,
	},
	{
		// Aura Break
		/* Handled within Dark aura and Fairy aura abilities */
	},
	{
		// Stamina
		.on_effect = stamina_on_effect,
	},
	{
		// Wimp out
		.on_effect = wimp_out_on_effect,
	},
	{
		// Emergency Exit
		.on_effect = wimp_out_on_effect,
	},
	{
		// Water Compaction
		.on_effect = water_compaction_on_effect,
	},
	{
		// Merciless
		.on_modify_move = merciless_on_modify_move,
	},
	{
		// SHIELDSDOWN
	},
	{
		// STAKEOUT TODO
	},
	{
		// water bubble
		.on_stat = water_bubble_on_stat,
		.on_status = water_bubble_on_status,
	},
	{
		// Steel Worker
		.on_base_power = steelworker_on_base_power,
	},
	{
		// Berserk
		.on_effect = berserk_on_effect,
	},
	{
		// Slush Rush
		.on_stat = slush_rush_on_stat,
		.a_flags = A_FLAG_HAIL_DMG_PREVENT,
	},
	{
		// long reach
		.on_modify_move = long_reach_on_modify_move,
	},
	{
		// Liquid Voice
		.on_modify_move = liquid_voice_on_modify_move,
	},
	{
		// TRIAGE
	},
	{
		// Galvanize
		.before_turn = galvanize_before_turn,
	},
	{
		// surge surfer
		.on_stat = surge_surfer_on_stat,
	},
	{
		// SCHOOLING
	},
	{
		// DISGUISE
	},
	{
		// BATTLEBOND
	},
	{
		// POWERCONSTRUCT
	},
	{
		// Corrosion
		/* Implemented in on_status.c*/
	},
	{
		// Comatose
		.on_status = comatose_on_status,
	},
	{
		// Queenly Majesty
		.on_tryhit = dazzling_on_tryhit,
	},
	{
		// INNARDSOUT
	},
	{
		// DANCER
	},
	{
		// Battery
		.on_base_power = battery_on_base_power,
	},
	{
		// Fluffy
		.on_damage = fluffy_on_damage,
	},
	{
		// Dazzling
		.on_tryhit = dazzling_on_tryhit,
	},
	{
		// Soul Heart
		.on_faint = soul_heart_on_faint,
	},
	{
		// Tangling Hair
		.on_effect = gooey_variations_on_effect,
	},
	{
		// Receiver
		.on_faint = receiver_variations_on_faint,
	},
	{
		// Power of Alchemy
		.on_faint = receiver_variations_on_faint,
	},
	{
		// Beast Boost
		.on_damage = beast_boost_on_damage,
	},
	{
		// RKSSYSTEM
	},
	{
		// ELECTRICSURGE
	},
	{
		// PSYCHICSURGE
	},
	{
		// MISTYSURGE
	},
	{
		// GRASSYSURGE
	},
	{
		// Full Metal Body
		.on_stat_boost_mod = clear_body_variations_on_stat_boost,
	},
	{
		// Shadow Shield
		.on_damage = shadow_shield_on_damage,
	},
	{
		// Prism Armor
		.on_damage = filter_variations_on_damage,
	},
	{
		// Neuroforce
		.on_damage = neuro_force_on_damage,
	},
};
