#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_actions/actions.h"
#include "../battle_events/battle_events.h"
#include "../moves/moves.h"
#include "status.h"

extern u16 RandRange(u16, u16);
extern void ShowStatusAilmentGraphic(u8 bank, enum StatusAilments status);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);
extern void do_damage(u8 bank_index, u16 dmg);
extern u16 get_damage(u8 attacker, u8 defender, u16 move);
extern void dprintf(const char * str, ...);
extern void hpbar_apply_dmg(u8 task_id);
extern void PKMNAilmentToBank(u8 bank, u8 ailment);

/* Sleep Related */
u8 sleep_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
u8 sleep_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (gPkmnBank[user]->battleData.status == AILMENT_SLEEP) {
		if (gPkmnBank[user]->battleData.status_turns) {
			ADD_VOLATILE(user, VOLATILE_SLEEP_TURN);
		} else {
			gPkmnBank[user]->battleData.status = AILMENT_NONE;
			QueueMessage(0, user, STRING_WOKE_UP, 0);
			ShowStatusAilmentGraphic(user, AILMENT_NONE);
			CLEAR_VOLATILE(user, VOLATILE_SLEEP_TURN);
			delete_callback_src((u32)sleep_on_before_move, user);
			delete_callback_src((u32)sleep_on_residual, user);
		}
	}
	return true;
}

u8 sleep_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (gPkmnBank[user]->battleData.status_turns) {
		gPkmnBank[user]->battleData.status_turns--;
	} else {
		gPkmnBank[user]->battleData.status_turns = 0;
		acb->in_use = false;
	}
	return true;
}

void sleep_on_inflict(u8 bank)
{
	if ((BANK_ABILITY(bank) != ABILITY_COMATOSE) || (BANK_ABILITY(bank) != ABILITY_INSOMNIA) ||
	(BANK_ABILITY(bank) != ABILITY_VITALSPIRIT) || (BANK_ABILITY(bank) != ABILITY_SWEETVEIL)) {
		u8 ailment = RandRange(1, 4);
		gPkmnBank[bank]->battleData.status_turns = ailment;
		gPkmnBank[bank]->battleData.status = AILMENT_SLEEP;
		pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
		QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_SLEEP);
		AddCallback(CB_ON_RESIDUAL, 3, ailment, bank, (u32)sleep_on_residual);
		AddCallback(CB_ON_BEFORE_MOVE, 3, ailment, bank, (u32)sleep_on_before_move);
	}
}


/* Poison Related */
u8 poison_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
    u16 dmg = TOTAL_HP(user) / 8;
    if (do_damage_residual(user, MAX(1, dmg), NULL)) {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animPoisonEffect;
		do_damage(user, MAX(1, dmg));
        QueueMessage(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
	}
    gPkmnBank[user]->battleData.status_turns++;
	return true;
}

void poison_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_POISON;
	B_STATUS(bank) = AILMENT_POISON;
    gPkmnBank[bank]->battleData.status_turns = 0;
	pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_POISON);
	AddCallback(CB_ON_RESIDUAL, 0, 0xFF, bank, (u32)poison_on_residual);
}


/* Burn Related */
u8 burn_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
	// heatproof:
	u16 dmg;
	if (BANK_ABILITY(user) == ABILITY_HEATPROOF)
		dmg = MAX(1, TOTAL_HP(user) / 16);
	else
		dmg = MAX(1, TOTAL_HP(user) >> 3);
    if (do_damage_residual(user, dmg, NULL)) {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animBurnEffect;
		do_damage(user, dmg);
        QueueMessage(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_BURN);
	}
    gPkmnBank[user]->battleData.status_turns++;
	return true;
}

void burn_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_BURN;
    gPkmnBank[bank]->battleData.status = AILMENT_BURN;
    gPkmnBank[bank]->battleData.status_turns = 0;
	pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_BURN);
	AddCallback(CB_ON_RESIDUAL, 0, 0xFF, bank, (u32)burn_on_residual);

}


/* Freeze Related */
u8 freeze_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    // 20% change to break out
    if ((RandRange(0, 100) < 20) || (IS_DEFROST(CURRENT_MOVE(user))))  {
        gPkmnBank[user]->battleData.status = AILMENT_NONE;
		QueueMessage(0, user, STRING_FREEZE_THAWED, 0);
		ShowStatusAilmentGraphic(user, AILMENT_NONE);
		delete_callback_src((u32)freeze_on_before_move, user);
    } else {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animFreeze;
        ADD_VOLATILE(user, VOLATILE_ATK_SKIP_TURN);
        QueueMessage(0, user, STRING_FROZEN_SOLID, 0);
    }
	return true;
}

void freeze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_FREEZE;
    gPkmnBank[bank]->battleData.status = AILMENT_FREEZE;
    gPkmnBank[bank]->battleData.status_turns = 0;
	pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_FREEZE);
	AddCallback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)freeze_on_before_move);
}


/* Paralyze Related */
u8 paralyze_on_before_move(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
	if (user != src) return true;
    if (RandRange(0, 100) < 25) {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animParalyzed;
        ADD_VOLATILE(user, VOLATILE_ATK_SKIP_TURN);
        QueueMessage(0, user, STRING_FULL_PARA, 0);
		return 3; // silent_fail
    }
	return true;
}

u16 paralyze_on_mod_stat(u8 bank, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
	if (B_STATUS(bank) != AILMENT_NONE) {
		if (stat_id != SPEED_MOD) return (u32)acb->data_ptr;
	    if (!(BANK_ABILITY(bank) == ABILITY_QUICK_FEET))
	        return PERCENT((u32)acb->data_ptr, 50);
	} else {
		acb->in_use = false;
	}
	return (u32)acb->data_ptr;
}

void paralyze_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_PARALYZE;
    B_STATUS(bank) = AILMENT_PARALYZE;
    gPkmnBank[bank]->battleData.status_turns = 0;
	pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_PARALYZE);
	AddCallback(CB_ON_STAT_MOD, 0, CB_PERMA, NULL, (u32)paralyze_on_mod_stat);
	AddCallback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)paralyze_on_before_move);
}


/* Toxic Related */
u8 toxic_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	// do dmg
    if (gPkmnBank[user]->battleData.status_turns < 15) {
        gPkmnBank[user]->battleData.status_turns++;
    }
    u16 dmg = ((MAX(1, (TOTAL_HP(user) / 16))) * gPkmnBank[user]->battleData.status_turns);
    if (do_damage_residual(user, 1, NULL)) {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
        a->script = (u32)&animBadlyPoisoned;
		do_damage(user, MAX(1, dmg));
        QueueMessage(0, user, STRING_RESIDUAL_STATUS_DMG, AILMENT_POISON);
	}
	return true;
}

void toxic_on_inflict(u8 bank)
{
	u8 ailment = AILMENTBITS_TOXIC;
	B_STATUS(bank) = AILMENT_BAD_POISON;
    gPkmnBank[bank]->battleData.status_turns = 0;
	pokemon_setattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, &ailment);
    QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_BAD_POISON);
	AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)toxic_on_residual);
}

/* Infactuation related */
// 50% chance to fail to hit the target infactuated with
u8 infactuated_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
	a->script = (u32)&animInfatuation;
	QueueMessage(0, user, STRING_IN_LOVE, 0);
	if (RandRange(0, 100) < 50) {
		return true;
	} else {
		QueueMessage(0, user, STRING_INFATUATED, 0);
		return 3;
	}
}

void infactuate_on_inflict(u8 bank)
{
	if (HAS_VOLATILE(bank, VOLATILE_INFACTUATION))
		return;
	ADD_VOLATILE(bank, VOLATILE_INFACTUATION);
	QueueMessage(0, bank, STRING_ATTRACT, AILMENT_INFACTUATION);
	AddCallback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)infactuated_before_move);
}


/* Confusion Related */
u8 confusion_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	ADD_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	if (gPkmnBank[user]->battleData.confusion_turns) {
		struct action* a = prepend_action(user, user, ActionAnimation, EventPlayAnimation);
		a->script = (u32)&animConfused;
		QueueMessage(0, user, STRING_IS_CONFUSED, 0);
		if (RandRange(0, 100) <= 33) {
			// hurt itself in confusion
			QueueMessage(0, user, STRING_CONFUSION_HURT, 0);
			B_MOVE_TYPE(user, 0) = TYPE_NONE;
			B_MOVE_POWER(user) = 40;
			B_MOVE_ACCURACY(user) = 101;
			B_MOVE_IGNORING_ABILITIES(user) = true;
			B_MOVE_CATEGORY(user) = MOVE_PHYSICAL;
			B_MOVE_CAN_CRIT(user) = false;
			B_MOVE_WILL_CRIT(user) = false;
			gBattleMaster->b_moves[(user)].hit_times = 0;
			u16 dmg = get_damage(user, user, CURRENT_MOVE(user));
			do_damage(user, MAX(1, dmg));
		} else {
			CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN); // don't skip turn
		}
	} else {
		gPkmnBank[user]->battleData.pseudo_ailment = AILMENT_NONE;
		QueueMessage(0, user, STRING_SNAPPED_OUT, 0);
		CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	}
	return true;
}

u8 confusion_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
	if (gPkmnBank[user]->battleData.confusion_turns) {
		gPkmnBank[user]->battleData.confusion_turns--;
	}
	CLEAR_VOLATILE(user, VOLATILE_CONFUSE_TURN);
	return true;
}

void confusion_on_inflict(u8 bank)
{
	gPkmnBank[bank]->battleData.pseudo_ailment = AILMENT_CONFUSION;
	gPkmnBank[bank]->battleData.confusion_turns = RandRange(1, 5);
	QueueMessage(0, bank, STRING_AILMENT_APPLIED, AILMENT_CONFUSION);
	AddCallback(CB_ON_RESIDUAL, 0, gPkmnBank[bank]->battleData.confusion_turns, bank, (u32)confusion_on_residual);
	AddCallback(CB_ON_BEFORE_MOVE, 3, gPkmnBank[bank]->battleData.confusion_turns, bank, (u32)confusion_on_before_move);
}


/* Misc Ailment related effects */
void silent_cure_major(u8 bank) {
	gPkmnBank[bank]->battleData.status = AILMENT_NONE;
	gPkmnBank[bank]->battleData.status_turns = 0;
	CLEAR_VOLATILE(bank, VOLATILE_SLEEP_TURN);
	delete_callback_src((u32)toxic_on_residual, bank);
	delete_callback_src((u32)paralyze_on_before_move, bank);
	delete_callback_src((u32)paralyze_on_mod_stat, bank);
	delete_callback_src((u32)freeze_on_before_move, bank);
	delete_callback_src((u32)burn_on_residual, bank);
	delete_callback_src((u32)poison_on_residual, bank);
	delete_callback_src((u32)sleep_on_before_move, bank);
	delete_callback_src((u32)sleep_on_residual, bank);
	ShowStatusAilmentGraphic(bank, AILMENT_NONE);
}

void clear_ailments_silent(u8 bank) {
	gPkmnBank[bank]->battleData.status = AILMENT_NONE;
	gPkmnBank[bank]->battleData.pseudo_ailment = AILMENT_NONE;
	gPkmnBank[bank]->battleData.status_turns = 0;
	gPkmnBank[bank]->battleData.confusion_turns = 0;
	CLEAR_VOLATILE(bank, VOLATILE_SLEEP_TURN);
	delete_callback_src((u32)confusion_on_residual, bank);
	delete_callback_src((u32)confusion_on_before_move, bank);
	delete_callback_src((u32)toxic_on_residual, bank);
	delete_callback_src((u32)paralyze_on_before_move, bank);
	delete_callback_src((u32)paralyze_on_mod_stat, bank);
	delete_callback_src((u32)freeze_on_before_move, bank);
	delete_callback_src((u32)burn_on_residual, bank);
	delete_callback_src((u32)poison_on_residual, bank);
	delete_callback_src((u32)sleep_on_before_move, bank);
	delete_callback_src((u32)sleep_on_residual, bank);
    ShowStatusAilmentGraphic(bank, AILMENT_NONE);
}

void effect_cure_on_inflict(u8 bank)
{
	clear_ailments_silent(bank);
	QueueMessage(0, bank, STRING_AILMENT_CURED, 0);
}

u8 BankAilmentToPKMN(u8 bank)
{
    switch(gPkmnBank[bank]->battleData.status)
    {
        case AILMENT_SLEEP:
            return gPkmnBank[bank]->battleData.status_turns;
        case AILMENT_POISON:
            return 1<<3;
        case AILMENT_BURN:
            return 1<<4;
        case AILMENT_FREEZE:
            return 1<<5;
        case AILMENT_PARALYZE:
            return 1<<6;
        case AILMENT_BAD_POISON:
            return 1<<7;
        default:
            return 0;
    }
}

void PKMNAilmentToBank(u8 bank, u8 ailment)
{
    if ((ailment & 7) > 0) {
        gPkmnBank[bank]->battleData.status = AILMENT_SLEEP;
        gPkmnBank[bank]->battleData.status_turns = ailment & 7;
		AddCallback(CB_ON_RESIDUAL, 3, 3, bank, (u32)sleep_on_residual);
		AddCallback(CB_ON_BEFORE_MOVE, 3, 3, bank, (u32)sleep_on_before_move);
    } else if (ailment & (1<<3)) {
        gPkmnBank[bank]->battleData.status = AILMENT_POISON;
		AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)poison_on_residual);
    } else if (ailment & (1<<4)) {
        gPkmnBank[bank]->battleData.status = AILMENT_BURN;
		AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)burn_on_residual);
    } else if (ailment & (1<<5)) {
        gPkmnBank[bank]->battleData.status = AILMENT_FREEZE;
		AddCallback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)freeze_on_before_move);
    } else if (ailment & (1<<6)) {
        gPkmnBank[bank]->battleData.status = AILMENT_PARALYZE;
		AddCallback(CB_ON_STAT_MOD, 0, CB_PERMA, NULL, (u32)paralyze_on_mod_stat);
		AddCallback(CB_ON_BEFORE_MOVE, 3, CB_PERMA, bank, (u32)paralyze_on_before_move);
    } else if (ailment & (1<<7)) {
        gPkmnBank[bank]->battleData.status = AILMENT_BAD_POISON;
		AddCallback(CB_ON_RESIDUAL, 0, CB_PERMA, bank, (u32)toxic_on_residual);
	}
}




struct status_ailments statuses[] =
{
    // Ailment none
    {
    },
    // Ailment sleep
    {
        .on_inflict = sleep_on_inflict,
    },

    // Ailment poison
    {
        .on_inflict = poison_on_inflict,
    },

    // Ailment burn
    {
        .on_inflict = burn_on_inflict,
    },

    // Ailment freeze
    {
        .on_inflict = freeze_on_inflict,
    },

    // Ailment paralyze
    {
        .on_inflict = paralyze_on_inflict,
    },

    // Ailment toxic
    {
        .on_inflict = toxic_on_inflict,
    },

    // Ailment confusion
    {
        .on_inflict = confusion_on_inflict,
    },

    // Ailment cure
    {
        .on_inflict = effect_cure_on_inflict,
    },

	// Ailment infactuation
	{
		.on_inflict = infactuate_on_inflict,
	}
};
