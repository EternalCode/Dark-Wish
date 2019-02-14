#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern void do_damage(u8 bank_index, u16 dmg);
extern void flat_heal(u8 bank, u16 heal);
extern u16 RandRange(u16 min, u16 max);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);

void seismic_toss_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_MOVE_DMG(user) = B_LEVEL(user);
}

void sonic_boom_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	B_MOVE_DMG(user) = 20;
}

void dragon_rage_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	B_MOVE_DMG(user) = 40;
}

u8 natures_madness_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	B_MOVE_DMG(user) = MAX((B_CURRENT_HP(TARGET_OF(user)) >> 1) , 1);
	return true;
}

enum TryHitMoveStatus endeavor_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return TRYHIT_USE_MOVE_NORMAL;
	if (B_CURRENT_HP(user) >= B_CURRENT_HP(TARGET_OF(user)))
		return TRYHIT_TARGET_MOVE_IMMUNITY; // immune
	return TRYHIT_USE_MOVE_NORMAL;
}

void endeavor_on_dmg(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return;
	s16 dmg = B_CURRENT_HP(TARGET_OF(user)) - B_CURRENT_HP(user);
	B_MOVE_DMG(user) = MAX(0, dmg);
}

void psywave_on_damage_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	u8 level = B_LEVEL(user);
    u16 damage = PERCENT(level, RandRange(50, 151));
    damage = MAX(1, damage);
    B_MOVE_DMG(user) = damage;
}

void pain_split_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	u16 user_hp = B_CURRENT_HP(user);
	u16 target_hp = B_CURRENT_HP(TARGET_OF(user));
	u16 average_hp = ((user_hp + target_hp) / 2);
	if (user_hp < average_hp) {
		flat_heal(user, average_hp - user_hp);
	} else {
		do_damage(user, user_hp - average_hp);
	}
	if (target_hp < average_hp) {
		flat_heal(TARGET_OF(user), average_hp - target_hp);
	} else {
		do_damage(TARGET_OF(user), target_hp - average_hp);
	}
	QueueMessage(NULL, NULL, STRING_PAIN_SPLIT, NULL);
	return true;
}


void frustration_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	u8 happiness = pokemon_getattr(gPkmnBank[user]->this_pkmn, REQUEST_HAPPINESS, NULL);
	u8 power = PERCENT((255 - happiness), 40);
	B_MOVE_DMG(user) = MAX(1, power);

}


void return_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	u8 happiness = pokemon_getattr(gPkmnBank[user]->this_pkmn, REQUEST_HAPPINESS, NULL);
	u8 power = ((happiness * 10) / 25);
	B_MOVE_DMG(user) = MAX(1, power);
}
