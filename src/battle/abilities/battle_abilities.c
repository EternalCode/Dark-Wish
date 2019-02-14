#include <pokeagb/pokeagb.h>
#include "battle_abilities.h"
#include "../moves/moves.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/battle_state.h"
#include "../battle_actions/actions.h"
#include "../battle_events/battle_events.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool set_weather(enum WeatherTypes weather);
extern bool BankMonSetType(u8 bank, enum PokemonType type);
extern struct action *stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern u16 RandRange(u16, u16);
extern bool disable_on_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 CountBankMovePP(u16 moveId, u8 bank);
extern void set_status(u8 bank, enum Effect status, u8 inflictor);
extern void do_damage(u8 bank_index, u16 dmg);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);
extern void flat_heal(u8 bank, u16 heal);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern void do_heal(u8 bank_index, u8 percent_heal);
extern bool bank_trapped(u8 bank);
extern void event_switch_mid_battle(struct action* current_action);
extern void clear_other_weather(void);

/* Note: Illuminate and Honey Gather have no In-Battle effect so they are not present here*/


// None
u8 ability_none_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // This is just an example
    return true;
}

// Stench
void stench_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_MOVE_DMG(user) > 0) {
        B_MOVE_FLINCH(user) = 10;
    }
}

// Drizzle
void drizzle_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_DRIZZLE, src)) return;
    ADD_VOLATILE(VOLATILE_DRIZZLE, src);
    if (gBattleMaster->field_state.is_raining) return;
    set_weather(WEATHER_RAIN);
}

// Speed Boost
u8 speedboost_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	stat_boost(user, SPEED_MOD, 1, user);
	return true;
}

// Battle Armor and Shell Armor
u8 battle_armor_variations_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    B_MOVE_WILL_CRIT(user) = false;
    return true;
}

// Sturdy
void sturdy_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_CURRENT_HP(src) == TOTAL_HP(src)) {
        if (B_MOVE_DMG(user) >= B_CURRENT_HP(user))
            B_MOVE_DMG(user) = B_CURRENT_HP(src) - 1;
    }
}

// Damp
/* Aftermath immunity is done through ability flag. See ability_table.c */
enum TryHitMoveStatus damp_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((move == MOVE_SELFDESTRUCT) || (move == MOVE_EXPLOSION))
        return TRYHIT_CANT_USE_MOVE;
    return TRYHIT_USE_MOVE_NORMAL;
}


// Limber
u8 limber_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_PARALYZE) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
       	return false;
    }
    return true;
}

// Sand Veil
u16 sand_veil_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_SANDSTORM && stat_id == STAT_EVASION) {
        return PERCENT(acb->data_ptr, 120);
    }
    return acb->data_ptr;
}

// Static
u8 static_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
	if (RandRange(1, 100) <= 30) {
	    set_status(user, EFFECT_PARALYZE, src);
	}
	return true;
}

// Volt Absorb
enum TryHitMoveStatus volt_absorb_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_ELECTRIC)) return TRYHIT_USE_MOVE_NORMAL;
    if (TOTAL_HP(src) != B_CURRENT_HP(src)) {
        do_heal(src, (TOTAL_HP(src) >> 2));
        QueueMessage(NULL, src, STRING_HEAL, 0);
        return TRYHIT_FAIL_SILENTLY;
    }
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Water Absorb
enum TryHitMoveStatus water_absorb_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_WATER)) return TRYHIT_USE_MOVE_NORMAL;
    if (TOTAL_HP(src) != B_CURRENT_HP(src)) {
        do_heal(src, (TOTAL_HP(src) >> 2));
        QueueMessage(NULL, src, STRING_HEAL, 0);
        return TRYHIT_FAIL_SILENTLY;
    }
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Oblivious
u16 oblivious_disallow[] = {
    MOVE_TAUNT, MOVE_NONE, MOVE_MAX, MOVE_CAPTIVATE, MOVE_ATTRACT,
};

enum TryHitMoveStatus oblivious_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    for (u8 i = 0; i < (sizeof(oblivious_disallow)/sizeof(u16)); i++) {
         if (move == oblivious_disallow[i]) return TRYHIT_CANT_USE_MOVE;
    }
    return TRYHIT_USE_MOVE_NORMAL;
}

u8 oblivious_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == EFFECT_INFACTUATION) {
    	return false;
    }
    return true;
}


// Cloud nine
void cloud_nine_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    clear_other_weather();
}


// Compound Eyes
u16 compound_eyes_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if ((stat_id == ACCURACY_MOD)) {
        return PERCENT(acb->data_ptr, 130);
    }
    return acb->data_ptr;
}

// Insomnia
u8 insomnia_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_SLEEP) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Color Change
void colorchange_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if ((B_MOVE_DMG(user) > 0) && (!B_MOVE_HAS_TYPE(user, MTYPE_NONE))) {
    	 u8 type = B_MOVE_TYPE(TARGET_OF(user), 0);
    	 BankMonSetType(TARGET_OF(user), type);
    	 QueueMessage(NULL, user, STRING_CONVERSION_TYPE, type);
    }
}

// Immunity
u8 immunity_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_POISON) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Flash Fire
u16 flash_fire_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (B_MOVE_HAS_TYPE(user, TYPE_FIRE)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

enum TryHitMoveStatus flash_fire_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_FIRE)) return TRYHIT_USE_MOVE_NORMAL;
    if (!HAS_VOLATILE(VOLATILE_FLASH_FIRE, src)) {
        ADD_VOLATILE(VOLATILE_FLASH_FIRE, src);
        QueueMessage(NULL, src, STRING_FLASH_FIRE, NULL);
        add_callback(CB_ON_STAT_MOD, 0, 0xFF, src, (u32)flash_fire_on_stat);
        return TRYHIT_FAIL_SILENTLY;
    }
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// SHIELDDUST

// Own Tempo
u8 own_tempo_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == EFFECT_CONFUSION) {
    	return false;
    }
    return true;
}

// SUCTIONCUPS

// Intimidate
void intimidate_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return;
    stat_boost(user, ATTACK_MOD, -1, src);
}

// SHADOWTAG

// Rough Skin and Iron Barbs
u8 rough_skin_variations_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
	do_damage_residual(user, TOTAL_HP(user) >> 3, NULL);
	return true;
}

// Wonder Guard
enum TryHitMoveStatus wonder_guard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((user == src) || (B_MOVE_IS_STATUS(user) || CURRENT_MOVE(user) == MOVE_STRUGGLE))
        return TRYHIT_USE_MOVE_NORMAL;
    if (B_MOVE_EFFECTIVENESS(user) != TE_SUPER_EFFECTIVE)
        return TRYHIT_TARGET_MOVE_IMMUNITY;
    else
        return TRYHIT_USE_MOVE_NORMAL;
}

// Levitate
/* Ability effect is added in as a clause to the is_grounded function. See grounded_effect.c */


// Effect Spore
u8 effect_spore_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    // Immunity in the case of overcoat
    if (HAS_ABILITY_FLAG(BANK_ABILITY(user), A_FLAG_POWDER_EFX_PREVENT)) return true;
    if (!B_MOVE_CONTACT(user)) return true;
    u16 rand_num = RandRange(0, 100);
    if (rand_num < 10) {
        set_status(user, EFFECT_SLEEP, src);
    } else if (rand_num < 20) {
        set_status(user, EFFECT_PARALYZE, src);
    } else if (rand_num < 30) {
        set_status(user, EFFECT_POISON, src);
    }
    return true;
}

// SYNCHRONIZE

u8 synchronize_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (CURRENT_ACTION->action_bank != src) {
        struct action* a =  add_action(src, CURRENT_ACTION->action_bank, ActionStatus, EventSetStatus);
        a->priv[0] = ailment;
    }
    return true;
}

// Clear Body and Full Metal Body
bool clear_body_variations_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // boost on self which isnt by the user
    return ((CURRENT_ACTION->action_bank == user) || (CURRENT_ACTION->priv[1] > 0));
}

// NATURALCURE

// Lightning Rod
enum TryHitMoveStatus lightning_rod_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_ELECTRIC)) return TRYHIT_USE_MOVE_NORMAL;
    stat_boost(src, STAT_SPECIAL_ATTACK, 1, src);
    return TRYHIT_FAIL_SILENTLY;
}

// Serene Grace
u8 serenegrace_on_modify_move_opp(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_FLINCH(user) *= 2;
    delete_callback_src((u32)serenegrace_on_modify_move_opp, src);
    return true;
}

u8 serenegrace_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    for (u8 i = 0; i < 8; i++) {
         B_USER_STAT_MOD_CHANCE(user, i) *= 2;
         B_TARGET_STAT_MOD_CHANCE(user, i) *= 2;
    }
    add_callback(CB_ON_MODIFY_MOVE, 0, 0, TARGET_OF(user), (u32)serenegrace_on_modify_move_opp);
    return true;
}

// Swift Swim
u16 swift_swim_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_RAINING && stat_id == STAT_SPEED) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// Chlorophyll
u16 chlorophyll_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_SUNNY && stat_id == STAT_SPEED) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}


// TRACE

// Huge Power, Pure Power
u16 huge_power_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (stat_id == ATTACK_MOD) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// Poison Point
u8 poisonpoint_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
        if (RandRange(0, 100) <= 30)
	    set_status(user, EFFECT_POISON, src);
	return true;
}

// INNERFOCUS
u8 inner_focus_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return true;
    B_MOVE_FLINCH(user) = 0;
    return true;
}


// Magma Armor
u8 magmaarmor_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_FREEZE) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// Water Veil
u8 waterveil_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_BURN) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// MAGNETPULL

// Soundproof
enum TryHitMoveStatus soundproof_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src) || !(IS_SOUND_BASE(move))) return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Rain Dish
u8 rain_dish_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    if (IS_WEATHER_RAINING) {
        flat_heal(user, MAX(1, TOTAL_HP(user) >> 4));
    }
    return true;
}


// Sand Stream
void sandstream_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_SANDSTREAM, src)) return;
    ADD_VOLATILE(VOLATILE_SANDSTREAM, src);
    if (gBattleMaster->field_state.is_sandstorm) return;
    set_weather(WEATHER_SANDSTORM);
}

// Pressure
u8 pressure_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((SIDE_OF(user) == SIDE_OF(src)) || (TARGET_OF(user) != src)) return true;
    // reduce PP
    if ((!HAS_VOLATILE(user, VOLATILE_MULTI_TURN)) && (!B_REDUCE_PP(user))) {
        u8 pp_index = gPkmnBank[user]->battleData.pp_index;
        if (pp_index < 4) {
            gPkmnBank[user]->battleData.move_pp[pp_index]--;
        }
    }
    return true;
}

// Thick Fat
u16 thick_fat_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (CURRENT_ACTION->action_bank != user)) return acb->data_ptr;

    // check current move is fire or ice
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE) || B_MOVE_HAS_TYPE(user, MTYPE_ICE)) {
        // halve atk and spa stats
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return acb->data_ptr >> 1;
    }
    return acb->data_ptr;
}

u8 thick_fat_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    add_callback(CB_ON_STAT_MOD, 5, 0, src, (u32)thick_fat_on_stat);
    return true;
}

// EARLYBIRD
u8 early_bird_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_STATUS(user) != AILMENT_SLEEP) return true;
    /*
    Sleep on_residual will drop the sleep counter by 1. Early bird will drop it by another one
    resulting in a half-time sleep.
    */
    if (BANK_ABILITY(user) == ABILITY_EARLYBIRD) {
        if (gPkmnBank[user]->battleData.status_turns > 1)
            gPkmnBank[user]->battleData.status_turns--;
    }
    return true;
}


// Flame Body
u8 flamebody_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
        if (RandRange(0, 100) <= 30)
	    set_status(user, EFFECT_BURN, src);
	return true;
}

// RUNAWAY

// Keen Eye
bool keen_eye_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 attacker = CURRENT_ACTION->action_bank; // inflictor
    if (attacker == src) return true;
    return (!(CURRENT_ACTION->priv[0] == ACCURACY_MOD));
}

u16 keen_eye_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    // if pokemon getting stat accessed isnt the target of keeneye user or
    // if keeneye user is not the one attacking or
    // if keen eye bank is accessing its evasion stat by itself
    if ((TARGET_OF(src) != user) || (CURRENT_ACTION->action_bank != src) || (user == src)) return acb->data_ptr;
    if (stat_id == EVASION_MOD)
        return 100;
    return acb->data_ptr;
}

// Hyper Cutter
bool hyper_cutter_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return (!CURRENT_ACTION->priv[0] == ATTACK_MOD);
}

// PICKUP

// TRUANT
u8 truant_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    /* Truant needs it's own string when it fails */
    if (user != src) return true;
    if (HAS_VOLATILE(user, VOLATILE_TRUANT)) {
        CLEAR_VOLATILE(user, VOLATILE_TRUANT);
        return false;
    } else {
        ADD_VOLATILE(user, VOLATILE_TRUANT);
        return true;
    }
}

// Hustle
u16 hustle_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if ((stat_id == ATTACK_MOD)) {
        return PERCENT(acb->data_ptr, 150);
    }
    if ((stat_id == ACCURACY_MOD) && B_MOVE_IS_PHYSICAL(user)) {
        return PERCENT(acb->data_ptr, 80);
    }
    return acb->data_ptr;
}

// Cute Charm
u8 cute_charm_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
        if (B_GENDER(user) == B_GENDER(src)) return true;
        if (RandRange(0, 100) <= 30)
	    set_status(user, EFFECT_INFACTUATION, src);
	return true;
}

// PLUS
u16 plus_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i) && ((SIDE_OF(i) == SIDE_OF(user)) && (i != user))) {
            if ((BANK_ABILITY(i) == ABILITY_MINUS) && (stat_id == SPATTACK_MOD))
                return PERCENT(acb->data_ptr, 150);
        }
    }
    return acb->data_ptr;
}

// MINUS
u16 minus_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (ACTIVE_BANK(i) && ((SIDE_OF(i) == SIDE_OF(user)) && (i != user))) {
            if ((BANK_ABILITY(i) == ABILITY_PLUS) && (stat_id == SPATTACK_MOD))
                return PERCENT(acb->data_ptr, 150);
        }
    }
    return acb->data_ptr;
}

// FORECAST

// STICKYHOLD

// SHEDSKIN
u8 shed_skin_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_STATUS(user) != AILMENT_NONE) {
        if (RandRange(0, 100) <= 33)
            set_status(user, EFFECT_CURE, user);
    }
    return true;
}

// Guts
/* Burn 1/2 damage effect handled in battle_calcs/damage_calc.c */
u16 guts_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    // double attack if status'd
    if (B_STATUS(user) != AILMENT_NONE) {
        if (stat_id == ATTACK_MOD)
            return acb->data_ptr << 1;
    }
    return acb->data_ptr;
}


// MARVELSCALE
u16 marvel_scale_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    // double attack if status'd
    if (B_STATUS(user) != AILMENT_NONE) {
        if (stat_id == DEFENSE_MOD)
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// Liquid Ooze
void liquid_ooze_on_drain(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) !=  src) return;
    if (B_DRAIN(user))
        B_DRAIN(user) = -B_DRAIN(user);
}

// Overgrow
u16 overgrow_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;

    if (B_MOVE_HAS_TYPE(user, TYPE_GRASS) && B_CURRENT_HP(user) <= (TOTAL_HP(user) / 3)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// Blaze
u16 blaze_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;

    if (B_MOVE_HAS_TYPE(user, TYPE_FIRE) && B_CURRENT_HP(user) <= (TOTAL_HP(user) / 3)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// Torrent
u16 torrent_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;

    if (B_MOVE_HAS_TYPE(user, TYPE_WATER) && B_CURRENT_HP(user) <= (TOTAL_HP(user) / 3)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// Swarm
u16 swarm_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;

    if (B_MOVE_HAS_TYPE(user, TYPE_BUG) && B_CURRENT_HP(user) <= (TOTAL_HP(user) / 3)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// Rock Head
/* A_FLAG_RECOIL_DMG_PREVENT flag in the ability table is used for this effect. */

// Drought
void drought_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_DROUGHT, src)) return;
    ADD_VOLATILE(VOLATILE_DROUGHT, src);
    if (gBattleMaster->field_state.is_sunny) return;
    set_weather(WEATHER_SUN);
}

// ARENATRAP

// Vital Spirit
u8 vitalspirit_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_SLEEP) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
    	return false;
    }
    return true;
}

// White Smoke
bool white_smoke_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return false;
}

// Air lock
/* Cloud nine clone ability */

// Tangled Feet
u16 tangled_feet_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (B_PSTATUS(user) != AILMENT_CONFUSION) {
        if ((stat_id == EVASION_MOD))
            return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// Motor Drive
enum TryHitMoveStatus motor_drive_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_ELECTRIC)) return TRYHIT_USE_MOVE_NORMAL;
    stat_boost(src, STAT_SPEED, 1, src);
    return TRYHIT_FAIL_SILENTLY;
}

// Rivalry
void rivalry_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_GENDER(user) == 0xFF || B_GENDER(src) == 0xFF) return;
    if (B_GENDER(user) == B_GENDER(src))
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 125);
    else
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 75);
}

// STEADFAST
void steadfast_on_flinch(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    stat_boost(user, STAT_SPEED, 1, user);
    return;
}

// Snow Cloak
u16 snow_cloak_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_HAIL && stat_id == STAT_EVASION) {
        return PERCENT(acb->data_ptr, 120);
    }
    return acb->data_ptr;
}


// GLUTTONY

// Anger Point
u8 angerpoint_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_WILL_CRIT(user)) {
        B_ATTACK_BUFF(src) = 6;
        QueueMessage(NULL, src, STRING_ANGER_POINT, NULL);
    }
    return true;
}

// UNBURDEN

// HEATPROOF
/* Burn damage being halved is done in status_effects/status.c */
void heatproof_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_HAS_TYPE (user, MTYPE_FIRE)) {
        B_MOVE_POWER(user) = B_MOVE_POWER(user) >> 1;
    }
}

// Simple
bool simple_on_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return true;
    CURRENT_ACTION->priv[1] = ((CURRENT_ACTION->priv[1]) << 1);
    return true;
}

// Dry skin
enum TryHitMoveStatus dry_skin_try_hit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_WATER)) return TRYHIT_USE_MOVE_NORMAL;
    if (TOTAL_HP(src) != B_CURRENT_HP(src)) {
        flat_heal(src, (TOTAL_HP(src) >> 2));
        QueueMessage(NULL, src, STRING_HEAL, 0);
        return TRYHIT_FAIL_SILENTLY;
    }
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

void dry_skin_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return;
	if (B_MOVE_HAS_TYPE(user, TYPE_FIRE))
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 125);
}

u8 dry_skin_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_RAINING) {
        flat_heal(user, MAX(1, TOTAL_HP(user) >> 3));
    } else if (IS_WEATHER_SUNNY) {
        flat_heal(user, MAX(1, TOTAL_HP(user) >> 3));
    }
    return true;
}


// Download
void download_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u32 def_total = 0;
    u32 sdef_total = 0;

    for (u8 i = 0; i < BANK_MAX; i++) {
        if (!ACTIVE_BANK(i) || SIDE_OF(i) == SIDE_OF(src)) {
            continue;
        } else {
            def_total += B_DEFENSE_STAT_UMOD(i);
            sdef_total += B_SPDEFENSE_STAT_UMOD(i);
        }
    }
    if (def_total > sdef_total) {
        stat_boost(user, STAT_SPECIAL_ATTACK, 1, user);
    } else {
        stat_boost(user, STAT_ATTACK, 1, user);
    }
}


// Iron Fist
void ironfist_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_PUNCH(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    }
}

// Poison Heal
extern u8 toxic_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
extern u8 poison_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);

u8 poison_heal_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != src) return true;
    // the ability can change at some point. Since this is anonymous, the case must be handled
    if (BANK_ABILITY(src) != ABILITY_POISON_HEAL) return true;
    if ((B_STATUS(user) == AILMENT_POISON) || (B_STATUS(user) == AILMENT_BAD_POISON)) {
        u8 id = get_callback_src((u32)toxic_on_residual, user);
        CB_MASTER[id].delay_before_effect = 1;
        id = get_callback_src((u32)poison_on_residual, user);
        CB_MASTER[id].delay_before_effect = 1;
        flat_heal(user, MAX(1, (TOTAL_HP(user) >> 3)));
        gPkmnBank[user]->battleData.status_turns++;
    } else {
        acb->in_use = false;
    }
    return true;
}

u8 poison_heal_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    add_callback(CB_ON_RESIDUAL, 2, 0, src, (u32)poison_heal_on_residual);
    return true;
}

// Adaptability
void adaptability_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_STAB(user)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 133);
    }
}


// SKILLLINK
u8 skill_link_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // if move is a multi hit move, then hit 5 times
    if (moves[move].multi_hit[0] > 0) {
        if (gBattleMaster->b_moves[user].hit_times != (moves[move].multi_hit[1] - 1)) {
            gBattleMaster->b_moves[user].hit_times = moves[move].multi_hit[1] - 1;
            gBattleMaster->b_moves[user].hit_counter = 1;
        }
    }
    return true;
}

// Hydration
u8 hydration_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_RAINING) {
        if (B_STATUS(user) != AILMENT_NONE)
                set_status(user, EFFECT_CURE, user);
    }
    return true;
}


// Solar Power
u8 solar_power_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_SUNNY) {
        do_damage(user, MAX(1, TOTAL_HP(user) >> 3));
    }
    return true;
}

u16 solar_power_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if ((stat_id == SPATTACK_MOD) && IS_WEATHER_SUNNY) {
        return (PERCENT(acb->data_ptr, 150));
    }
    return acb->data_ptr;
}

// Quick Feet
u16 quick_feet_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if ((B_STATUS(user) != AILMENT_NONE) && (stat_id == SPEED_MOD)) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// Normalize
u16 normalize_banlist[] = {
    MOVE_HIDDENPOWER,
    MOVE_NATURALGIFT, MOVE_STRUGGLE, MOVE_WEATHERBALL, MOVE_NONE
};

u8 normalize_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_MOVE_IS_STATUS(user)) return true;
    for (u8 i = 0; i < (sizeof(normalize_banlist) / sizeof(u16)); i++) {
         if (normalize_banlist[i] == move) return true;
    }
    B_MOVE_TYPE(user, 0) = MTYPE_NORMAL;
    B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    return true;
}

void normalize_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_MODIFY_MOVE, 1, 0, user, (u32)normalize_on_modify_move);
}


// SNIPER
void sniper_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_DID_CRIT(user))
	    B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 200);
}

// Magic Guard
/* Implemented with an ability flag. See ability_table.c */

// NOGUARD
enum TryHitMoveStatus noguard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_PASS;
}

// STALL

// Technician
void technician_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_POWER(user) <= 60) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
}

// Leaf Guard
u8 leaf_guard_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (TARGET_OF(user) == src) return true;
    return false;
}

enum TryHitMoveStatus leaf_guard_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (move == MOVE_YAWN) return TRYHIT_FAIL_SILENTLY;
    return TRYHIT_USE_MOVE_NORMAL;
}

// KLUTZ

// MOLDBREAKER

// Super Luck
u16 super_luck_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    // if pokemon getting stat accessed isnt the target of keeneye user or
    // if keeneye user is not the one attacking or
    // if keen eye bank is accessing its evasion stat by itself
    if ((user != src) || (stat_id != CRIT_CHANCE_MOD)) return true;
    u8 crit_mod[4] = {6, 13, 50, 100};
    if (acb->data_ptr == 100)
        return 100;
    for (u8 i = 0; i < 3; i++) {
        if (crit_mod[i] > acb->data_ptr)
            return crit_mod[i];
    }
    return acb->data_ptr;
}

// Aftermath
u8 aftermath_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
	if (!B_MOVE_CONTACT(user)) return true;
        if (B_CURRENT_HP(src) < 1)
            do_damage_residual(user, TOTAL_HP(user) >> 2, A_FLAG_AFTERMATH_DMG_PREVENT);
	return true;
}

// ANTICIPATION

// FOREWARN

// UNAWARE

// Tinted Lens
void tintedlens_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_EFFECTIVENESS(user) == TE_NOT_VERY_EFFECTIVE) {
	    B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 200);
    }
}

// Filter, Solid Rock and Prism Armor
void filter_variations_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
    if (B_MOVE_EFFECTIVENESS(user) == TE_SUPER_EFFECTIVE) {
        B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 75);
    }
}

// Slow Start
u16 slow_start_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (BANK_ABILITY(src) != ABILITY_SLOWSTART) {
        acb->in_use = false;
        return acb->data_ptr;
    }
    // halve atk and spe stats
    if ((stat_id == ATTACK_MOD) || (stat_id == SPEED_MOD)) {
        return acb->data_ptr >> 1;
    }
    return acb->data_ptr;
}

void slow_start_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    add_callback(CB_ON_STAT_MOD, 5, 5, src, (u32)slow_start_on_stat);
}

// Scrappy
u16 scrappy_on_effectiveness(u8 target_type, u8 src, u16 move_type, struct anonymous_callback* acb) {
    // acb->data == ((attacker << 16) | move_effectiveness);
    u16 attacker = acb->data_ptr >> 16;
    if ((attacker != src) || (target_type != MTYPE_GHOST)) return true; // use current effectiveness
    if ((move_type == MTYPE_NORMAL) || (move_type == MTYPE_FIGHTING))
        return 100; // normal attacks against ghost types have 100% effectiveness
    return true;
}

// Storm Drain
enum TryHitMoveStatus storm_drain_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_WATER)) return TRYHIT_USE_MOVE_NORMAL;
    stat_boost(src, STAT_SPECIAL_ATTACK, 1, src);
    return TRYHIT_FAIL_SILENTLY;
}

// Ice Body
u8 ice_body_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    if (gBattleMaster->field_state.is_hail) {
        flat_heal(user, MAX(1, TOTAL_HP(user) >> 4));
    }
    return true;
}

// Snow Warning
void snowwarning_on_start(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (HAS_VOLATILE(VOLATILE_SNOWWARNING, src)) return;
    ADD_VOLATILE(VOLATILE_SNOWWARNING, src);
    if (gBattleMaster->field_state.is_hail) return;
    set_weather(WEATHER_HAIL);
}

// FRISK

// Reckless
void reckless_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (MOVE_RECOIL(move)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    }
}

// MULTITYPE

// FLOWERGIFT

// Bad Dreams
u8 bad_dreams_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user == src) return true;
    if ((B_STATUS(user) ==  AILMENT_SLEEP) || (BANK_ABILITY(user) == ABILITY_COMATOSE))
        do_damage(user, MAX(1, TOTAL_HP(user) >> 3));
    return true;
}

// PICKPOCKET [Message is to be added]
void pick_pocket_on_secondary(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((B_ITEM(src) != ITEM_NONE) || (B_ITEM(user) == ITEM_NONE)) return;
    if (!B_MOVE_CONTACT(user)) return;
    if ((user == src) || (TARGET_OF(user) == src)) {
        B_ITEM(src) = B_ITEM(TARGET_OF(src));
        B_ITEM(TARGET_OF(src)) = ITEM_NONE;
        // TODO: message
    }
}

// Sheer Force
void sheer_force_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if ((moves[move].procs) != NULL || M_FLINCH(move)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 130);
    }
}


// Contary
bool contrary_on_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return true;
    CURRENT_ACTION->priv[1] = -CURRENT_ACTION->priv[1];
    return true;
}

// UNNERVE

// Defiant
void defiant_after_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return;
    if (SIDE_OF((CURRENT_ACTION)->action_bank) != SIDE_OF(user) && ((CURRENT_ACTION)->priv[1] < 0))
        stat_boost(user, STAT_ATTACK - 1, 2, user);
}

// Defeatist
u16 defeatist_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;

    if (B_CURRENT_HP(user) <= (TOTAL_HP(user) >> 1)) {
        if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD))
            return acb->data_ptr >> 1;
    }
    return acb->data_ptr;
}

// Cursed Body
u8 cursed_body_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    // no effect on self or if not targetted
    if ((TARGET_OF(user) != src) || (user == src)) return true;

    // 30% chance to disable move, if it did dmg
    if ((B_MOVE_DMG(user) != 0) && (RandRange(0, 100) <= 100)) {
        // fail if attackers move has no PP left
        if (CountBankMovePP(move, user) < 1) return true;
        // fail if effect already active on target
        if (HAS_VOLATILE(user, VOLATILE_DISABLE)) return true;
        u8 id = add_callback(CB_ON_DISABLE_MOVE, 0, 4, user, (u32)disable_on_disable_move);
        ADD_VOLATILE(user, VOLATILE_DISABLE);
        CB_MASTER[id].data_ptr = move;
        QueueMessage(move, user, STRING_DISABLED, 0);
    }
    return true;
}

// Healer
u8 healer_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((user == src) || (SIDE_OF(user) != SIDE_OF(src))) return true;
    if (B_STATUS(user) != AILMENT_NONE)
            set_status(user, EFFECT_CURE, user);
    return true;
}

// Friend Guard
void friend_guard_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 target = TARGET_OF(user);
    if ((SIDE_OF(target) != SIDE_OF(src)) || (target == src) || (B_MOVE_DMG(user) < 1)) return;
    B_MOVE_DMG(user) = MAX(1, PERCENT(B_MOVE_DMG(user), 75));
}

// Weak Armor
u8 weak_armor_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_IS_PHYSICAL(user)) {
        stat_boost(src, DEFENSE_MOD, -1, user);
        stat_boost(src, SPEED_MOD, 2, user);
    }
    return true;
}

// HEAVYMETAL

// LIGHTMETAL

// Toxic Boost
void toxic_boost_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_IS_PHYSICAL(user) && ((B_STATUS(user) == AILMENT_POISON) || (B_STATUS(user) == AILMENT_BAD_POISON))) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
}

// Flare Boost
void flare_boost_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_IS_SPECIAL(user) && B_STATUS(user) == AILMENT_BURN) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
}

// HARVEST

// Telepathy
enum TryHitMoveStatus telepathy_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) == src) && (src == ALLY_OF(user)))
        return TRYHIT_FAIL_SILENTLY;
    return TRYHIT_USE_MOVE_NORMAL;
}

// MOODY
u8 moody_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != src) return true;
    u8 up_stats[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF};
    u8 down_stats[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    u8 up_index = 0;
    u8 down_index = 0;

    // populate boostable stats array
    s8* stat = &(gPkmnBank[user]->battleData.attack);
    for (u8 i = 0; i < 6; i++) {
        if (*stat < 6) {
            up_stats[up_index] = i;
            up_index++;
        }
        if (*stat > -6) {
            down_stats[down_index] = i;
            down_index++;
        }
    }

    // pick stat to boost
    if (up_index >  0) {
        stat_boost(user, up_stats[RandRange(0, up_index)], 2, src);
    }
    // pick stat to drop
    if (down_index > 0) {
        stat_boost(user, down_stats[RandRange(0, down_index)], -1, src);
    }
    return true;
}

// Overcoat
enum TryHitMoveStatus overcoat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src) || !(IS_POWDER(move))) return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Poison Touch
u8 poison_touch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (!B_MOVE_CONTACT(user)) return true;
        if (RandRange(0, 100) <= 30)
	    set_status(TARGET_OF(user), EFFECT_POISON, src);
	return true;
}

// REGENERATOR

// Big Pecks
bool big_pecks_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CURRENT_ACTION->action_bank == src) return true;
    return (!(CURRENT_ACTION->priv[0] == DEFENSE_MOD));
}

// Sand Rush
u16 sand_rush_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_SANDSTORM && stat_id == STAT_SPEED) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// WONDERSKIN

// Analytic
extern u8 doom_desire_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
void analytic_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if ((gPkmnBank[TARGET_OF(user)]->battleData.will_move == false) && (moves[move].on_tryhit_move != doom_desire_on_tryhit)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 130);
	}
}

// ILLUSION

// IMPOSTER

// Infiltrator
u8 infiltrator_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    B_INFILTRATES(src) = true;
    return true;
}

// Mummy
u16 mummy_immune_abilities[] = {
    ABILITY_MUMMY, ABILITY_MULTITYPE, ABILITY_STANCE_CHANGE
};

u8 mummy_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (!B_MOVE_CONTACT(user)) return true;
    for (u8 i = 0; i < (sizeof(mummy_immune_abilities) / sizeof(u16)); i++) {
         if (mummy_immune_abilities[i] == BANK_ABILITY(user)) return true;
    }

    QueueMessage(move, user, STRING_ABILITY_CHANGED, BANK_ABILITY(user));
    // remove users old ability callbacks
    delete_callback_src((u32)abilities[BANK_ABILITY(user)].on_effect, user);
    BANK_ABILITY(user) = ABILITY_MUMMY;
    if (abilities[BANK_ABILITY(user)].on_effect) {
        add_callback(CB_ON_EFFECT, 0, 0, user, (u32)abilities[BANK_ABILITY(user)].on_effect);
    }
    return true;
}

// Moxie
void moxie_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (gPkmnBank[user]->battleData.last_attacked_by == src)
        stat_boost(src, ATTACK_MOD, 1, src);
}

void moxie_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 target = TARGET_OF(user);
    if ((B_CURRENT_HP(target) > 0) && ((B_CURRENT_HP(target) - B_MOVE_DMG(user)) <= 0))
        add_callback(CB_ON_FAINT_CHECK, 0, 0, src, (u32)moxie_on_faint);
}


// Justified
u8 justified_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_HAS_TYPE(user, MTYPE_DARK))
        stat_boost(src, ATTACK_MOD, 1, user);
    return true;
}

// Rattled
u8 rattled_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_HAS_TYPE(user, MTYPE_DARK) || B_MOVE_HAS_TYPE(user, MTYPE_GHOST) || B_MOVE_HAS_TYPE(user, MTYPE_BUG))
        stat_boost(src, ATTACK_MOD, 1, src);
    return true;
}

// MAGICBOUNCE

enum TryHitMoveStatus magic_bounce_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) == src) && (!ACTION_BOUNCED) && (IS_REFLECTABLE(move))) {
        struct action* a = next_action(user, user, ActionMove, EventMoveTryHit);
        a->move = CURRENT_MOVE(user);
        a->target = user;
        a->has_bounced = true;
        a->reset_move_config = true;
        QueueMessage(CURRENT_MOVE(user), src, STRING_BOUNCED_BACK, 0);
        B_MOVE_FAILED(user) = true;
        acb->in_use = false;
        return TRYHIT_FAIL_SILENTLY;
    } else {
        return TRYHIT_USE_MOVE_NORMAL;
    }
}

// Sap Sipper
enum TryHitMoveStatus sap_sipper_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return TRYHIT_USE_MOVE_NORMAL;
    if (!B_MOVE_HAS_TYPE(user, TYPE_GRASS)) return TRYHIT_USE_MOVE_NORMAL;
    stat_boost(src, STAT_DEFENSE, 1, src);
    return TRYHIT_FAIL_SILENTLY;
}

// Prankster
enum TryHitMoveStatus prankster_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((user != src) || (TARGET_OF(user) == src)) return TRYHIT_USE_MOVE_NORMAL;
    // priority boosted moves fail against those who are dark type
    return !(BankMonHasType(TARGET_OF(user), MTYPE_DARK) && HAS_VOLATILE(user, VOLATILE_PRANKSTERED));
}

void prankster_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (IS_MOVE_STATUS(move)) {
        B_MOVE_PRIORITY(user) += 1;
        ADD_VOLATILE(user, VOLATILE_PRANKSTERED);
        add_callback(CB_ON_TRYHIT_MOVE, 1, 0, user, (u32)prankster_on_tryhit);
    }
}

// Sand Force
void sand_force_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (IS_WEATHER_SANDSTORM && (B_MOVE_HAS_TYPE(user, TYPE_ROCK) || B_MOVE_HAS_TYPE(user, TYPE_GROUND) || B_MOVE_HAS_TYPE(user, TYPE_STEEL)))
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 130);
}

// ZENMODE

// Victory Star
u16 victory_star_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (SIDE_OF(user) != SIDE_OF(src)) return acb->data_ptr;
    if ((stat_id == ACCURACY_MOD)) {
        return PERCENT(acb->data_ptr, 110);
    }
    return acb->data_ptr;
}

// TURBOBLAZE

// TERAVOLT

// Aroma Veil
u16 aroma_veil_banned[] = {MOVE_ATTRACT, MOVE_DISABLE, MOVE_ENCORE, MOVE_HEALBLOCK, MOVE_TAUNT, MOVE_TORMENT};
enum TryHitMoveStatus aroma_veil_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (SIDE_OF(TARGET_OF(user)) == SIDE_OF(src)) {
        for (u8 i = 0; i < (sizeof(aroma_veil_banned)/ sizeof(u16)); i++) {
            if (move == aroma_veil_banned[i])
                return TRYHIT_TARGET_MOVE_IMMUNITY;
        }
    }
    return TRYHIT_USE_MOVE_NORMAL;
}

// Flower Veil
bool flower_veil_on_stat_boost(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    u8 defender = CURRENT_ACTION->target;
    return (!((SIDE_OF(defender) == SIDE_OF(src)) && (BankMonHasType(defender, MTYPE_GRASS))));
}

u8 flower_veil_on_status(u8 user, u8 src, u16 ailment, struct anonymous_callback* acb)
{
    switch (ailment) {
        case AILMENT_CURE:
        case AILMENT_CONFUSION:
        case AILMENT_NONE:
        case AILMENT_INFACTUATE:
            return true;
        default:
            if (!BankMonHasType(user, MTYPE_GRASS)) return true;
            return (!(SIDE_OF(user) == SIDE_OF(src)));
    }
}


// CHEEKPOUCH

// PROTEAN

// Fur Coat
u16 fur_coat_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (stat_id == DEFENSE_MOD) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// MAGICIAN

// Bulletproof
enum TryHitMoveStatus bulletproof_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src) || !(IS_BULLET(move))) return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Competitive
void competitive_after_stat_boost_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    acb->in_use = false;
    if (user != src) return;
    if (SIDE_OF((CURRENT_ACTION)->action_bank) != SIDE_OF(user) && ((CURRENT_ACTION)->priv[1] < 0))
        stat_boost(user, STAT_SPECIAL_ATTACK - 1, 2, user);
}

// Strong Jaw
void strongjaw_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_BITE(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
}

// Refrigerate
u16 refrigerate_banlist[] = {
    MOVE_HIDDENPOWER,
    MOVE_NATURALGIFT, MOVE_STRUGGLE, MOVE_WEATHERBALL, MOVE_NONE
};

u8 refrigerate_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // status moves excempt
    if (B_MOVE_IS_STATUS(user) || (!B_MOVE_HAS_TYPE(user, MTYPE_NORMAL))) return true;
    for (u8 i = 0; i < (sizeof(refrigerate_banlist) / sizeof(u16)); i++) {
         if (refrigerate_banlist[i] == move) return true;
    }
    B_MOVE_TYPE(user, 0) = MTYPE_ICE;
    B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    return true;
}

void refrigerate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_MODIFY_MOVE, -1, 0, user, (u32)refrigerate_on_modify_move);
}

// Sweet Veil
u8 sweet_veil_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (SIDE_OF(user) != SIDE_OF(src)) return true;
    if (ailment == AILMENT_SLEEP) {
    	QueueMessage(NULL, user, STRING_AILMENT_IMMUNE, AILMENT_SLEEP);
    	return false;
    }
    return true;
}

// STANCECHANGE

// Gale Wings
void gale_wings_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (((B_CURRENT_HP(user) << 1) >= TOTAL_HP(user)) && (MOVE_TYPE(move) == MTYPE_FLYING))
        B_MOVE_PRIORITY(user) += 1;
}

// Mega Launcher
void megalauncher_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (IS_PULSE(move)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
}

// Grass Pelt
u16 grass_pelt_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (gBattleMaster->field_state.is_grassy_terrain && stat_id == DEFENSE_MOD) {
        return PERCENT(acb->data_ptr, 150);
    }
    return acb->data_ptr;
}

// SYMBIOSIS

// Tough Claws
void tough_claws_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_CONTACT(user)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 130);
	}
}

// Pixilate
u16 pixilate_banlist[] = {
    MOVE_HIDDENPOWER,
    MOVE_NATURALGIFT, MOVE_STRUGGLE,
    MOVE_WEATHERBALL, MOVE_NONE
};

u8 pixilate_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // status moves excempt
    if (B_MOVE_IS_STATUS(user) || (!B_MOVE_HAS_TYPE(user, MTYPE_NORMAL))) return true;
    for (u8 i = 0; i < (sizeof(pixilate_banlist) / sizeof(u16)); i++) {
         if (pixilate_banlist[i] == move) return true;
    }
    B_MOVE_TYPE(user, 0) = MTYPE_FAIRY;
    B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    return true;
}

void pixilate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_MODIFY_MOVE, -1, 0, user, (u32)pixilate_on_modify_move);
}

// Gooey and Tangling Hair
u8 gooey_variations_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (!B_MOVE_CONTACT(user)) return true;
    stat_boost(user, SPEED_MOD, -1, user);
    return true;
}

// Aerilate
u16 aerilate_banlist[] = {
    MOVE_HIDDENPOWER,
    MOVE_NATURALGIFT, MOVE_STRUGGLE,
    MOVE_WEATHERBALL, MOVE_NONE
};

u8 aerilate_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // status moves excempt
    if (B_MOVE_IS_STATUS(user) || (!B_MOVE_HAS_TYPE(user, MTYPE_NORMAL))) return true;
    for (u8 i = 0; i < (sizeof(aerilate_banlist) / sizeof(u16)); i++) {
         if (aerilate_banlist[i] == move) return true;
    }
    B_MOVE_TYPE(user, 0) = MTYPE_FLYING;
    B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    return true;
}

void aerilate_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_MODIFY_MOVE, -1, 0, user, (u32)aerilate_on_modify_move);
}

// PARENTALBOND

// Dark Aura
void dark_aura_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    bool reverse = false;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (BANK_ABILITY(i) == ABILITY_AURA_BREAK) {
            reverse = true;
            break;
        }
    }
	if (B_MOVE_HAS_TYPE(user, MTYPE_DARK)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), ((reverse) ? 75 : 130));
	}
	return;
}

// Fairy Aura
void fairy_aura_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    bool reverse = false;
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (BANK_ABILITY(i) == ABILITY_AURA_BREAK) {
            reverse = true;
            break;
        }
    }

	if (B_MOVE_HAS_TYPE(user, MTYPE_FAIRY)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), ((reverse) ? 75 : 130));
	}
	return;
}

// Aura break - handled within Dark Aura and Fairy Aura


// Stamina
u8 stamina_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_DMG(user) > 0)
        stat_boost(src, DEFENSE_MOD, 1, user);
    return true;
}

// wimp out
// Emergency exit - same as wimp out
u8 wimp_out_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (bank_trapped(src)) return true;
    if ((B_LAST_DMG(src) > 0) && ((B_CURRENT_HP(src) << 1) < TOTAL_HP(src))) {
        // swap here
        prepend_action(src, src, ActionHighPriority, EventEndAction);
        event_switch_mid_battle(CURRENT_ACTION->prev_action);
    }
    return true;
}


// Water Compaction
u8 water_compaction_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src)) return true;
    if (B_MOVE_HAS_TYPE(user, MTYPE_WATER))
        stat_boost(src, DEFENSE_MOD, 2, user);
    return true;
}

// MERCILESS
u8 merciless_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_STATUS(TARGET_OF(user)) == AILMENT_POISON)
        B_MOVE_WILL_CRIT(user) = true;
    return true;
}

// SHIELDSDOWN

// STAKEOUT

// Water Bubble
u16 water_bubble_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    // boost water attacks
    if (user == src) {
        if (CURRENT_ACTION->action_bank != user) return acb->data_ptr;
        if (B_MOVE_HAS_TYPE(user, MTYPE_WATER)) {
            // halve atk and spa stats
            if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD)) {
                return acb->data_ptr << 1;
            }
        }
    } else {
    // deboost fire type attacks against src
        if ((TARGET_OF(user) != src) || (CURRENT_ACTION->action_bank != user)) return acb->data_ptr;
        if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE)) {
            // halve atk and spa stats
            if ((stat_id == ATTACK_MOD) || (stat_id == SPATTACK_MOD)) {
                return acb->data_ptr >> 1;
            }
        }
    }
    return acb->data_ptr;
}

u8 water_bubble_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (ailment == AILMENT_BURN) {
    	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
       	return false;
    }
    return true;
}


// Steel Worker
void steelworker_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
	if (B_MOVE_HAS_TYPE(user, MTYPE_STEEL)) {
	    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
	}
	return;
}

// BERSERK
u8 berserk_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
if ((B_LAST_DMG(src) > 0) && ((B_CURRENT_HP(src) << 1) < TOTAL_HP(src)) && (!HAS_VOLATILE(src, VOLATILE_BERSERK))) {
        add_volatile(src, VOLATILE_BERSERK);
        stat_boost(src, ATTACK_MOD, 1, user);
    }
    return true;
}

// Slush Rush
u16 slush_rush_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (IS_WEATHER_HAIL && stat_id == STAT_SPEED) {
        return (acb->data_ptr << 1);
    }
    return acb->data_ptr;
}

// Long Reach
u8 long_reach_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_MOVE_CONTACT(user) = false;
    return true;
}

// Liquid Voice
u8 liquid_voice_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_SOUND_BASE(move)) {
        B_MOVE_TYPE(user, 0) = MTYPE_WATER;
        B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    }
    return true;
}

// Triage
void triage_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (IS_HEAL(move))
        B_MOVE_PRIORITY(user) += 1;
}

// Galvanize
u16 galvanize_banlist[] = {
    MOVE_HIDDENPOWER,
    MOVE_NATURALGIFT, MOVE_STRUGGLE,
    MOVE_WEATHERBALL, MOVE_NONE
};

u8 galvanize_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // status moves excempt
    if (B_MOVE_IS_STATUS(user) || (!B_MOVE_HAS_TYPE(user, MTYPE_NORMAL))) return true;
    for (u8 i = 0; i < (sizeof(galvanize_banlist) / sizeof(u16)); i++) {
         if (galvanize_banlist[i] == move) return true;
    }
    B_MOVE_TYPE(user, 0) = MTYPE_ELECTRIC;
    B_MOVE_TYPE(user, 1) = MTYPE_NONE;
    B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 120);
    return true;
}

void galvanize_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    add_callback(CB_ON_MODIFY_MOVE, -1, 0, user, (u32)galvanize_on_modify_move);
}

// SURGESURFER
u16 surge_surfer_on_stat(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return acb->data_ptr;
    if (gBattleMaster->field_state.is_electric_terrain && stat_id == SPEED_MOD) {
        return PERCENT(acb->data_ptr, 200);
    }
    return acb->data_ptr;
}
// SCHOOLING

// DISGUISE

// BATTLEBOND

// POWERCONSTRUCT

// Corrosion
/* Implemented directly in event_on_status */

// Comatose
u8 comatose_on_status(u8 user, u8 src, u16 ailment , struct anonymous_callback* acb)
{
    if (user != src) return true;
	QueueMessage(NULL, user, STRING_IMMUNE_ABILITY, NULL);
   	return false;
}

// QUEENLYMAJESTY

// INNARDSOUT

// DANCER

// Battery
void battery_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != ALLY_OF(src))
        return;
    if(IS_MOVE_SPECIAL(move)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 130);
    }
}

// Fluffy
void fluffy_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (B_MOVE_DMG(user) < 1)) return;
    if (B_MOVE_HAS_TYPE(user, MTYPE_FIRE))
        B_MOVE_DMG(user) = B_MOVE_DMG(user) << 1;
    if (B_MOVE_CONTACT(user)) {
        B_MOVE_DMG(user) = B_MOVE_DMG(user) >> 1;
    }
    // atleast 1 dmg
    B_MOVE_DMG(user) = MAX(1, B_MOVE_DMG(user));
}
// Dazzling and Queenly Majesty
enum TryHitMoveStatus dazzling_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((TARGET_OF(user) != src) || (user == src) || (MOVE_PRIORITY(user) < 1)) return TRYHIT_USE_MOVE_NORMAL;
    return TRYHIT_TARGET_MOVE_IMMUNITY;
}

// Soul Heart
void soul_heart_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb) {
    if (user != src)
        stat_boost(src, SPATTACK_MOD, 1, src);
}

// Receiver and Power of Alchemy
u16 receiver_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE,
    ABILITY_FLOWERGIFT, ABILITY_FORECAST, ABILITY_ILLUSION,
    ABILITY_IMPOSTER, ABILITY_MULTITYPE, ABILITY_POWERCONSTRUCT,
    ABILITY_POWEROFALCHEMY, ABILITY_RECEIVER, ABILITY_RKSSYSTEM,
    ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN, ABILITY_STANCECHANGE,
    ABILITY_TRACE, ABILITY_WONDERGUARD, ABILITY_ZENMODE,
};

void receiver_variations_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if ((SIDE_OF(user) != SIDE_OF(src)) || (user == src)) return;
    u8 user_ability = BANK_ABILITY(user);
    for (u8 i = 0; i < (sizeof(receiver_banlist)/sizeof(u16)); i++) {
         if (user_ability == receiver_banlist[i])
	     return;
    }
    BANK_ABILITY(src) = BANK_ABILITY(user);
}

// Beast Boost
void beast_boost_on_faint(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (gPkmnBank[user]->battleData.last_attacked_by != src) return;
    u16 highest = 0;
    u8 mod = ATTACK_MOD;
    if (B_ATTACK_STAT_UMOD(src) > highest) {
        highest = B_ATTACK_STAT_UMOD(src);
        mod = ATTACK_MOD;
    }
    if (B_DEFENSE_STAT_UMOD(src) > highest) {
        highest = B_DEFENSE_STAT_UMOD(src);
        mod = DEFENSE_MOD;
    }
    if (B_SPEED_STAT_RAW(src) > highest) {
        highest = B_SPEED_STAT_RAW(src);
        mod = SPEED_MOD;
    }
    if (B_SPATTACK_STAT_UMOD(src) > highest) {
        highest = B_SPATTACK_STAT_UMOD(src);
        mod = SPATTACK_MOD;
    }
    if (B_SPDEFENSE_STAT_UMOD(src) > highest) {
        highest = B_SPDEFENSE_STAT_UMOD(src);
        mod = SPDEFENSE_MOD;
    }
    stat_boost(src, mod, 1, src);
}

void beast_boost_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 target = TARGET_OF(user);
    if ((B_CURRENT_HP(target) > 0) && ((B_CURRENT_HP(target) - B_MOVE_DMG(user)) <= 0))
        add_callback(CB_ON_FAINT_CHECK, 0, 0, src, (u32)beast_boost_on_faint);
}

// RKSSYSTEM

// ELECTRICSURGE

// PSYCHICSURGE

// MISTYSURGE

// GRASSYSURGE

// Multi-scale & Shadow Shield
void shadow_shield_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(user) != src) return;
	if (TOTAL_HP(user) == B_CURRENT_HP(user)) {
	    B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 50);
    }
    return;
}

// Neuro-force
void neuro_force_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_MOVE_EFFECTIVENESS(user) == TE_SUPER_EFFECTIVE) {
        B_MOVE_DMG(user) = PERCENT(B_MOVE_DMG(user), 120);
    }
    return;
}
