#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../abilities/battle_abilities.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);

/* Miracle eye */
u16 miracle_eye_on_effectiveness(u8 target_type, u8 defender, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (user == defender) return effectiveness;
    if ((target_type == MTYPE_DARK) && (move_type == MTYPE_PSYCHIC)) {
        return 100;
    } else {
        return effectiveness;
    }
}

u16 miracle_eye_on_evasion(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if ((user != src) || (stat_id != EVASION_MOD)) return (u16)acb->data_ptr;
    return 100;
}

u8 miracle_eye_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_MIRACLEEYE, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_MIRACLE_EYE);
    }
    return true;
}

u8 miracle_eye_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MIRACLE_EYE)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_MIRACLE_EYE);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)miracle_eye_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    QueueMessage(MOVE_MIRACLEEYE, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}


/* Odor Sleuth */
u16 odor_sleuth_on_effectiveness(u8 target_type, u8 defender, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (user == defender) return effectiveness;
    if ((target_type == MTYPE_GHOST) && ((move_type == MTYPE_NORMAL) || (move_type == MTYPE_FIGHTING))) {
        return 100;
    } else {
        return effectiveness;
    }
}


u8 odor_sleuth_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_ODORSLEUTH, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_ODOR_SLEUTH);
    }
    return true;
}

u8 odor_sleuth_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_ODOR_SLEUTH)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_ODOR_SLEUTH);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)odor_sleuth_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)odor_sleuth_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    QueueMessage(MOVE_ODORSLEUTH, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}


/* Foresight */
u8 foresight_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_FORESIGHT, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_FORESIGHT);
    }
    return true;
}

u8 foresight_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_FORESIGHT)) return false;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_FORESIGHT);
    add_callback(CB_ON_STAT_MOD, 0, 5, TARGET_OF(user), (u32)miracle_eye_on_evasion);
    add_callback(CB_ON_EFFECTIVENESS, 0, 5, TARGET_OF(user), (u32)odor_sleuth_on_effectiveness);
    u8 id = add_callback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)foresight_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    QueueMessage(MOVE_FORESIGHT, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}

/* Mind Reader */
u8 mind_reader_on_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (TARGET_OF(src) != user) return true;
    B_MOVE_ACCURACY(src) = 101;
    B_MOVE_IGNORE_EVASION(src) = true;
    return true;
}

u8 mind_reader_on_semi_invulnerable(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    return false;
}

u8 mind_reader_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (LAST_MOVE(user) == MOVE_MINDREADER) return false;
    add_callback(CB_ON_BEFORE_MOVE, 0, 1, user, (u32)mind_reader_on_before_move);
    add_callback(CB_ON_TRYHIT_INV_MOVE, 0, 1, user, (u32)mind_reader_on_semi_invulnerable);
    QueueMessage(MOVE_FORESIGHT, TARGET_OF(user), STRING_IDENTIFIED, NULL);
    return true;
}


/* Laser Focus */
// Laser focus is just similar to Mind reader, so I put it here
u8 laser_focus_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (B_MOVE_CAN_CRIT(user)) {
        B_MOVE_WILL_CRIT(user) = true;
    }
    return true;
}

u8 laser_focus_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    add_callback(CB_ON_MODIFY_MOVE, 0, 1, user, (u32)laser_focus_on_modify_move);
    return true;
}


/* Chip Away */
/* Sacred Sword */
/* Darkest Lariat */
// They all share this callback.
u8 chip_away_on_before_move(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_MOVE_IGNORE_DEF(user) = true;
    B_MOVE_IGNORE_EVASION(user) = true;
    return true;
}
