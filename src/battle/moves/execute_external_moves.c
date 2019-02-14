#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_events/battle_events.h"


extern u16 RandRange(u16 min, u16 max);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void dprintf(const char * str, ...);
extern u8 BankCountUsableMoves(u8 bank);
extern u8 BankMoveCount(u8 bank);
extern void set_attack_bm_inplace(u16 move, u8 new_bank);

/* Metronome */

const static u16 metronome_disallow[] = {
	MOVE_AFTERYOU, MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW,
	 MOVE_COPYCAT, MOVE_COUNTER,
	MOVE_COVET, MOVE_DESTINYBOND, MOVE_DETECT,
	MOVE_ENDURE, MOVE_FEINT,
	MOVE_FOCUSPUNCH, MOVE_FOLLOWME,
	MOVE_HELPINGHAND, MOVE_KINGSSHIELD,
	MOVE_MEFIRST, MOVE_METRONOME,
	MOVE_MIMIC, MOVE_MIRRORCOAT, MOVE_MIRRORMOVE, MOVE_NATUREPOWER,
	MOVE_PROTECT, MOVE_QUASH,
	MOVE_QUICKGUARD, MOVE_RAGEPOWDER,
	MOVE_SKETCH, MOVE_SLEEPTALK, MOVE_SNATCH,
	MOVE_SNORE, MOVE_SPIKYSHIELD, MOVE_STRUGGLE,
	MOVE_SWITCHEROO, MOVE_THIEF, MOVE_TRANSFORM, MOVE_TRICK,
	MOVE_WIDEGUARD, MOVE_MAX,
};

u16 pick_rand_metronome_move()
{
	bool unusable_move = true;
    u16 selected_move = MOVE_NONE;
	while (unusable_move) {
		selected_move = RandRange(1, MOVE_MAX);
		for (u8 i = 0; i < (sizeof(metronome_disallow) / sizeof(u16)); i++) {
			if (metronome_disallow[i] == selected_move) {
				unusable_move = false;
				break;
			}
		}
		unusable_move = (unusable_move) ? false : true;
	}
	return selected_move;
}

u8 metronome_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    CURRENT_MOVE(user) = pick_rand_metronome_move();
	set_attack_bm_inplace(CURRENT_MOVE(user), user);
	LAST_MOVE(user) = MOVE_METRONOME;
    QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
    return true;
}

/* Mirror Move */
u8 mirror_move_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    // fails if target hasn't made a move or target's move isn't mirrorable
	u8 target = TARGET_OF(user);
    if ((LAST_MOVE(target) != MOVE_NONE) && (IS_MIRRORABLE(LAST_MOVE(target)))) {
        CURRENT_MOVE(user) = LAST_MOVE(target);
        set_attack_bm_inplace(CURRENT_MOVE(user), user);
		LAST_MOVE(user) = MOVE_MIRRORMOVE;
        QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
        return true;
    }
    return false;
}

/* Sleep Talk */
const static u16 sleep_talk_disallow[] = {
    MOVE_ASSIST, MOVE_BELCH,
    MOVE_BIDE, MOVE_COPYCAT,
    MOVE_FOCUSPUNCH, MOVE_MEFIRST, MOVE_METRONOME,
    MOVE_MIMIC, MOVE_MIRRORMOVE, MOVE_NATUREPOWER,
    MOVE_SHELLTRAP, MOVE_SKETCH, MOVE_SLEEPTALK, MOVE_UPROAR,

};

bool is_allowed_sleep_talk(u16 move)
{
    for (u8 i = 0; i < (sizeof(sleep_talk_disallow) / sizeof(u16)); i++) {
        if (move == sleep_talk_disallow[i])
            return false;
    }
    return true;
}

u8 sleep_talk_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    if ((B_STATUS(user) == AILMENT_SLEEP) || (BANK_ABILITY(user) == ABILITY_COMATOSE)) {
        CLEAR_VOLATILE(user, VOLATILE_SLEEP_TURN);
        QueueMessage(0, user, STRING_FAST_ASLEEP, 0);
    }
	// don't fail here, fail after posting "Used move" string
	return true;

}

u8 sleep_talk_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    if ((B_STATUS(user) == AILMENT_SLEEP) || (BANK_ABILITY(user) == ABILITY_COMATOSE)) {
        // fail if no moves learnt
        u16 move_set[4] = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE};
        u8 array_slot = 0;
        for (u8 i = 0; i < 4; i++) {
            u16 this_move = B_GET_MOVE(user, i);
            if ((this_move != MOVE_NONE) && (is_allowed_sleep_talk(this_move)) && (!(IS_CHARGE(this_move)))) {
                move_set[array_slot] = this_move;
                array_slot++;
            }
        }
        if (array_slot) {
            CURRENT_MOVE(user) = move_set[RandRange(0, array_slot)];
            set_attack_bm_inplace(CURRENT_MOVE(user), user);
			CURRENT_ACTION->move = CURRENT_MOVE(user);
			LAST_MOVE(user) = MOVE_SLEEPTALK;
            QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


/* Assist */
const static u16 assist_disallow[] = {
    MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW,
    MOVE_BOUNCE, MOVE_CIRCLETHROW,
    MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET,
    MOVE_DESTINYBOND, MOVE_DETECT, MOVE_DIG,
    MOVE_DIVE, MOVE_DRAGONTAIL, MOVE_ENDURE,
    MOVE_FEINT, MOVE_FLY, MOVE_FOCUSPUNCH,
    MOVE_FOLLOWME, MOVE_HELPINGHAND, MOVE_KINGSSHIELD,
    MOVE_MEFIRST, MOVE_METRONOME,
    MOVE_MIMIC, MOVE_MIRRORCOAT, MOVE_MIRRORMOVE,
    MOVE_NATUREPOWER, MOVE_PHANTOMFORCE, MOVE_PROTECT,
    MOVE_RAGEPOWDER, MOVE_ROAR,
    MOVE_SKETCH, MOVE_SKYDROP, MOVE_SLEEPTALK,
    MOVE_SNATCH, MOVE_SPIKYSHIELD, MOVE_STRUGGLE,
    MOVE_SWITCHEROO, MOVE_THIEF, MOVE_TRANSFORM,
    MOVE_TRICK, MOVE_WHIRLWIND, MOVE_MAX, MOVE_NONE,
};

bool is_allowed_assist(u16 move)
{
    for (u8 i = 0; i < ((sizeof(assist_disallow)) / sizeof(u16)); i++) {
        if (assist_disallow[i] == move)
            return false;
    }
    return true;
}

u8 assist_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    u16 move_set[24] = {MOVE_NONE};
    u8 array_slot = 0;
    u8 poke_count = count_pokemon();
    struct Pokemon* bank_party = (SIDE_OF(user)) ? (&party_opponent[0]) : (&party_player[0]);
    for (u8 i = 0; i < poke_count; i++) {
        if ((u32)&bank_party[i] == (u32)gPkmnBank[user]->this_pkmn)
            continue;
        for (u8 j = 0; j < 4; j++) {
            u16 this_move = pokemon_getattr(&bank_party[i], REQUEST_MOVE1 + j, NULL);
            if (is_allowed_assist(this_move)) {
                move_set[array_slot] = this_move;
                array_slot++;
            }
        }
    }

    if (array_slot) {
        CURRENT_MOVE(user) = move_set[RandRange(0, array_slot)];
		CURRENT_ACTION->move = CURRENT_MOVE(user);
        set_attack_bm_inplace(CURRENT_MOVE(user), user);
        QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
		LAST_MOVE(user) = MOVE_ASSIST;
        return true;
    } else {
        return false;
    }
}


/* Copycat */
const static u16 copycat_disallow[] = {
    MOVE_ASSIST, MOVE_BESTOW,
    MOVE_CIRCLETHROW, MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET,
    MOVE_DESTINYBOND, MOVE_DETECT, MOVE_DRAGONTAIL, MOVE_ENDURE,
    MOVE_FEINT, MOVE_FOCUSPUNCH, MOVE_FOLLOWME, MOVE_HELPINGHAND,
    MOVE_MEFIRST, MOVE_METRONOME, MOVE_MIMIC, MOVE_MIRRORCOAT,
    MOVE_MIRRORMOVE, MOVE_NATUREPOWER, MOVE_PROTECT,
    MOVE_RAGEPOWDER, MOVE_ROAR, MOVE_SKETCH, MOVE_SLEEPTALK,
    MOVE_SNATCH, MOVE_STRUGGLE, MOVE_SWITCHEROO, MOVE_THIEF,
    MOVE_TRANSFORM, MOVE_TRICK, MOVE_WHIRLWIND, MOVE_NONE, MOVE_MAX
};

bool is_allowed_copycat(u16 move)
{
    for (u8 i = 0; i < ((sizeof(copycat_disallow)) / sizeof(u16)); i++) {
        if (copycat_disallow[i] == move)
            return false;
    }
    return true;
}

u8 copycat_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    u16 last_move = gBattleMaster->field_state.last_used_move;
    if (is_allowed_copycat(last_move)) {
        CURRENT_MOVE(user) = last_move;
        set_attack_bm_inplace(CURRENT_MOVE(user), user);
        QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
		LAST_MOVE(user) = MOVE_COPYCAT;
        return true;
    } else {
        return false;
    }
}

/* Magic coat */
u16 magic_coat_tryhit_anon(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if ((user == source) || ACTION_BOUNCED || (!IS_REFLECTABLE(move)))
		return TRYHIT_USE_MOVE_NORMAL;
	struct action* a = next_action(user, user, ActionMove, EventMoveTryHit);
	a->move = CURRENT_MOVE(user);
	a->target = user;
	a->has_bounced = true;
	a->reset_move_config = true;
	QueueMessage(CURRENT_MOVE(user), source, STRING_BOUNCED_BACK, 0);
	B_MOVE_FAILED(user) = true;
	acb->in_use = false;
	return TRYHIT_FAIL_SILENTLY; // fail silently
}

enum TryHitMoveStatus magic_coat_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return TRYHIT_USE_MOVE_NORMAL;
	QueueMessage(CURRENT_MOVE(user), user, STRING_SHROUDED_MAGICCOAT, 0);
	add_callback(CB_ON_TRYHIT_MOVE, 2, 0, user, (u32)(magic_coat_tryhit_anon));
	return TRYHIT_USE_MOVE_NORMAL;
}


/* Me first */
const static u16 me_first_disallow[] = {
	MOVE_COUNTER, MOVE_COVET, MOVE_FOCUSPUNCH,
	MOVE_MEFIRST, MOVE_METALBURST, MOVE_MIRRORCOAT,
	MOVE_STRUGGLE, MOVE_THIEF, MOVE_MAX, MOVE_NONE
};

u8 me_first_on_base_power_anon(u8 attacker, u8 src, u16 move, struct anonymous_callback* acb)
{
	u16 base_power = B_MOVE_POWER(attacker);
	if (attacker == src) {
		acb->in_use = false;
		B_MOVE_POWER(attacker) = PERCENT(base_power, 150);
	}
	return true;
}

enum TryHitMoveStatus me_first_on_tryhit(u8 user, u8 src, u16 move_user, struct anonymous_callback* acb)
{
	if (user != src) return TRYHIT_USE_MOVE_NORMAL;
	// fail if user hasn't moved before target
	if (user != 0)
		return TRYHIT_CANT_USE_MOVE;
	u8 defender = TARGET_OF(user);
	u16 move = CURRENT_MOVE(defender);
	if (IS_MOVE_STATUS(move))
		return TRYHIT_CANT_USE_MOVE;
	for (u8 i = 0; i < (sizeof(me_first_disallow) / sizeof(u16)); i++) {
		if (me_first_disallow[i] == move)
			return TRYHIT_CANT_USE_MOVE;
	}

	// move is valid to be copied
	CURRENT_MOVE(user) = move;
	set_attack_bm_inplace(CURRENT_MOVE(user), user);
	LAST_MOVE(user) = MOVE_MEFIRST;
	QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
	add_callback(CB_ON_BASE_POWER_MOVE, 4, 0, user, (u32)me_first_on_base_power_anon);
	acb->in_use = false;
	return TRYHIT_USE_MOVE_NORMAL;
}

/* Snatch */
u16 statch_tryhit_anon(u8 user, u8 source, u16 move, struct anonymous_callback* acb)
{
	if ((user == source) || (!IS_SNATCHABLE(move))) {
		return true;
	}
	struct action* a = next_action(source, source, ActionMove, EventMoveTryHit);
	a->target = source,
	a->has_bounced = true;
	a->reset_move_config = true;
	a->move = CURRENT_MOVE(user);
	QueueMessage(0, source, STRING_SNATCHED_MOVE, 0);
	acb->in_use = false;
	return 3;
}

u8 snatch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	QueueMessage(CURRENT_MOVE(user), user, STRING_SNATCH_WAITING, 0);
	add_callback(CB_ON_TRYHIT_MOVE, 0, 0, user, (u32)(statch_tryhit_anon));
	acb->in_use = false;
	return true;
}


// After you
u8 after_you_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// fail if target has moved already
	if (!gPkmnBank[TARGET_OF(user)]->battleData.will_move) return false;
	// fail if target moves next anyways
	if (CURRENT_ACTION->next_action->action_bank == TARGET_OF(user)) return false;
	struct action* a = find_action(TARGET_OF(user), ActionMove);
	if (a == NULL) return false;
	u8 target_backup = a->target;
	u16 move_backup = a->move;
	u8 event_state_backup = a->event_state;
	end_action(a);
	a = next_action(TARGET_OF(user), target_backup, ActionMove, event_state_backup);
	a->move = move_backup;
	return true;
}


// Quash
enum TryHitMoveStatus quash_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return TRYHIT_USE_MOVE_NORMAL;
	// fail if target has moved already
	if (!gPkmnBank[TARGET_OF(user)]->battleData.will_move) return TRYHIT_CANT_USE_MOVE;

	// find and terminate target's turn
	struct action* a = find_action(TARGET_OF(user), ActionMove);
	if (a == NULL) return TRYHIT_CANT_USE_MOVE;
	u8 target_backup = a->target;
	u16 move_backup = a->move;
	u8 event_state_backup = a->event_state;
	end_action(a);

	// find last action before turns end, and put opponent action before it
	a = find_action(0xFF, ActionHighPriority); // residual effects
	struct action* backup_current = CURRENT_ACTION;
	CURRENT_ACTION = a;
	a = prepend_action(TARGET_OF(user), NULL, ActionMove, event_state_backup);
	CURRENT_ACTION = backup_current;
	a->move = move_backup;
	a->target = target_backup;
	a->event_state = event_state_backup;
	return TRYHIT_USE_MOVE_NORMAL;
}
