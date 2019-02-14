#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 CountBankMovePP(u16 moveId, u8 bank);
extern void set_attack_bm_inplace(u8 bank, u8 index, s8 priority);
extern bool BankKnowsMove(u16 moveId, u8 bank);

const static u16 encore_disallow[] = {
    MOVE_ASSIST, MOVE_COPYCAT, MOVE_ENCORE, MOVE_MEFIRST,
    MOVE_METRONOME, MOVE_MIMIC, MOVE_MIRRORMOVE,
    MOVE_NATUREPOWER, MOVE_SKETCH, MOVE_SLEEPTALK,
    MOVE_STRUGGLE, MOVE_TRANSFORM, MOVE_NONE,
};

/* Encore */
enum TryHitMoveStatus encore_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (CountBankMovePP(LAST_MOVE(TARGET_OF(user)), TARGET_OF(user)) < 1) return TRYHIT_CANT_USE_MOVE;
    for (u8 i = 0; i < (sizeof(encore_disallow) / sizeof(u16)); i++) {
        if (LAST_MOVE(TARGET_OF(user)) == encore_disallow[i])
            return TRYHIT_CANT_USE_MOVE;
    }
    return TRYHIT_USE_MOVE_NORMAL;
}

u8 encore_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CountBankMovePP(LAST_MOVE(user), user) < 1) {
        acb->in_use = false;
        return true;
    }
    if (move != LAST_MOVE(user)) {
        // we want to display a message when player picks an invalid move.
        // Obviously not display the message to the AI.
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_ENCORE);
        return false;
    }
    return true;
}

u8 encore_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (CountBankMovePP(CURRENT_MOVE(user), user) < 1) {
        acb->in_use = false;
        gPkmnBank[user]->battleData.skip_move_select = false;
    }
    return true;
}

u8 encore_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target = TARGET_OF(user);
    // fail if first turn/no move selected last turn
    if (LAST_MOVE(target) == 0) return false;
    // fail if target's move has no PP left
    if (CountBankMovePP(LAST_MOVE(target), target) < 1) return false;
    // fail if encore active on target already
    if (has_callback_src((u32)encore_on_disable, target)) return false;
    CURRENT_MOVE(target) = LAST_MOVE(target);
    set_attack_bm_inplace(target, (target), 0);
    add_callback(CB_ON_RESIDUAL, 0, 3, target, (u32)encore_on_residual);
    add_callback(CB_ON_DISABLE_MOVE, 0, 3, target, (u32)encore_on_disable);
    QueueMessage(NULL, target, STRING_RECIEVED_ENCORE, NULL);
    return true;
}


/* Torment */
u8 torment_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (move == LAST_MOVE(user)) {
        // we want to display a message when player picks an invalid move.
        // Obviously not display the message to the AI.
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_TORMENT);
        return false;
    }
    return true;
}

u8 torment_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)torment_on_disable, TARGET_OF(user))) return false;
    add_callback(CB_ON_DISABLE_MOVE, 0, 0xFF, TARGET_OF(user), (u32)torment_on_disable);
    QueueMessage(NULL, TARGET_OF(user), STRING_SUBJECTED_TORM, NULL);
    return true;
}


/* Taunt */
u8 taunt_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != TARGET_OF(src)) return true;
    QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
    return (!B_MOVE_IS_STATUS(user));
}

u8 taunt_on_disable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_MOVE_STATUS(move)) {
        // we want to display a message when player picks an invalid move.
        // Obviously not display the message to the AI.
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_TORMENT);
        return false;
    }
    return true;
}

u8 taunt_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (has_callback_src((u32)taunt_on_disable, TARGET_OF(user))) return false;
    add_callback(CB_ON_DISABLE_MOVE, 0, 0x5, TARGET_OF(user), (u32)taunt_on_disable);
    QueueMessage(NULL, TARGET_OF(user), STRING_FELL_FOR_TAUNT, NULL);
    return true;
}


/* Disable */
bool disable_on_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (acb->duration == 0)
        CLEAR_VOLATILE(user, VOLATILE_DISABLE);
    if (move == acb->data_ptr) {
        // we want to display a message when player picks an invalid move.
        // Obviously not display the message to the AI.
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_DISABLE);
        return false;
    }
    return true;
}

u8 disable_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != TARGET_OF(src)) return true;
    if (has_callback_src((u32)disable_on_disable_move, user) || HAS_VOLATILE(user, VOLATILE_DISABLE)) {
        QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
        return false;
    }
    return true;
}

u8 disable_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    u8 target = TARGET_OF(user);
    // fail if first turn/no move selected last turn
    if (LAST_MOVE(target) == 0) return false;
    // fail if target's move has no PP left
    if (CountBankMovePP(LAST_MOVE(target), target) < 1) return false;
    // fail if effect already active on target
    if (has_callback_src((u32)disable_on_disable_move, target) || HAS_VOLATILE(user, VOLATILE_DISABLE)) return false;
    u8 id = add_callback(CB_ON_DISABLE_MOVE, 0, 4, target, (u32)disable_on_disable_move);
    ADD_VOLATILE(target, VOLATILE_DISABLE);
    CB_MASTER[id].data_ptr = LAST_MOVE(target);
    QueueMessage(LAST_MOVE(target), target, STRING_DISABLED, 0);
	return true;
}


/* Throat Chop */
u8 throat_chop_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != TARGET_OF(src)) return true;
    if (IS_SOUND_BASE(CURRENT_MOVE(user))) {
        QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
        return false;
    } else {
        return true;
    }
}

bool throat_chop_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_SOUND_BASE(move)) {
        // we want to display a message when player picks an invalid move.
        // Obviously not display the message to the AI.
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_THROATCHOP);
        return false;
    }
    return true;
}

u8 throat_chop_on_effect_cb(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    u8 target = TARGET_OF(user);
    // don't reapply effect if effect is active
    if (has_callback_src((u32)throat_chop_disable_move, target)) return true;
    add_callback(CB_ON_DISABLE_MOVE, 0, 2, target, (u32)throat_chop_disable_move);
	return true;
}

/* Imprison */
bool imprison_disable_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    if (BankKnowsMove(move, src)){
        if (!SIDE_OF(user))
            QueueMessage(move, user, STRING_CANT_REASON, MOVE_IMPRISON);
        return false;
    }
    return true;
}

u8 imprison_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
	if (user != src) return true;
    // don't reapply effect if effect is active, fail move
    if (has_callback_src((u32)imprison_disable_move, user)) return false;
    add_callback(CB_ON_DISABLE_MOVE, 0, CB_PERMA, user, (u32)imprison_disable_move);
	return true;
}
