#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_events/battle_events.h"
#include "../abilities/battle_abilities.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern u8 SideCountUsablePkmn(u8 side);
extern void forced_switch(u8 bank, u8 switch_method);
extern void stat_boost(u8 bank, u8 stat_id, s8 amount, u8 inflicting_bank);
extern void do_heal(u8 bank_index, u8 heal);
extern void set_status(u8 bank, enum StatusAilments status, u8 inflictor);
extern void do_damage(u8 bank_index, u16 dmg);

// Pursuit
void pursuit_on_basepower(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (gPkmnBank[TARGET_OF(user)]->battleData.isSwitching) {
        B_MOVE_POWER(user) *= 2; // double base power on switch
    }
}

void pursuit_on_before_turn(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    for (u8 i = 0; i < 4; i++) {
        if ((SIDE_OF(i) != SIDE_OF(user)) && ((gPkmnBank[i]->battleData.isSwitching))) {
            B_MOVE_PRIORITY(user) = 7;
            TARGET_OF(user) = i;
            return;
        }
    }
}


bool forced_switch_effect_move(u8 target, u8 user)
{
    // fail if trapped
    if (HAS_VOLATILE(target, VOLATILE_TRAPPED) || HAS_VOLATILE(target, VOLATILE_INGRAIN) || B_IS_TRAPPED(target))
        return false;
    // continue faint event if this pokemon fainted, don't do switch logic.
    if (B_IS_FAINTED(target)) return false;
    // ability prevents switching
    if (HAS_ABILITY_FLAG(BANK_ABILITY(target), A_FLAG_FORCED_SWITCHING_PREVENT)) return false;
    // end the battle in wild battles if used against wild mon
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
            // player
            if (SIDE_OF(target) == PLAYER_SIDE) {
                // if user's level is less than target's level, don't switch
                if (B_LEVEL(user) < B_LEVEL(target)) return true;
                // exit battle if selected mon is only one for player
                if (SideCountUsablePkmn(PLAYER_SIDE) < 2) {
                    prepend_action(target, target, ActionHighPriority, EventEndBattle);
                    end_action(CURRENT_ACTION);
                } else {
                    struct action* a = next_action(target, target, ActionSwitch, EventForcedSwitch);
                    a->priv[0] = 0;
                }
            } else {
                // opponent wild, end battle
                prepend_action(target, target, ActionHighPriority, EventEndBattle);
                end_action(CURRENT_ACTION);
            }
            break;
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            dprintf("FAILED to select a valid battle mode.\n");
            break;
    };
    return true;
}


// Dragon Tail, Circle throw, Whirlwind
u8 dragon_tail_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target = TARGET_OF(user);
    return forced_switch_effect_move(target, user);
}


// Volt switch, U-turn
u8 volt_switch_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // player
    if (user == PLAYER_SIDE) {
        // no switch effect if cannot switch into something
        if (SideCountUsablePkmn(PLAYER_SIDE) < 2) return true;
        struct action* a = next_action(user, user, ActionSwitch, EventForcedSwitch);
        a->priv[0] = 1;
    } else {
        if (SideCountUsablePkmn(OPPONENT_SIDE) < 2) return true;
        // TODO: Opponent switching(?)
    }
    return true;
}


// Parting shot
u8 parting_shot_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // stat drop on foe
    stat_boost(TARGET_OF(user), ATTACK_MOD, -1, user);
    stat_boost(TARGET_OF(user), SPATTACK_MOD, -1, user);
    // player
    if (user == PLAYER_SIDE) {
        // no switch effect if cannot switch into something
        struct action* a = next_action(user, user, ActionSwitch, EventForcedSwitch);
        a->priv[0] = 1;
    } else {
        if (SideCountUsablePkmn(OPPONENT_SIDE) < 2) return true;
        // TODO: Opponent switching(?)
    }
    return true;
}


// Momento
u8 memento_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // stat drop on foe
    for (u8 i = 0; i < BANK_MAX; i++) {
        if ((i == user) && (ACTIVE_BANK(i))) continue;
        stat_boost(i, ATTACK_MOD, -2, user);
        stat_boost(i, SPATTACK_MOD, -2, user);
    }
    do_damage(user, B_CURRENT_HP(user));
    struct action* a = prepend_action(user, user, ActionSwitch, EventForcedSwitch);
    a->priv[0] = 1;
    return true;
}


// Lunar Dance, Healing Wish
void lunar_dance_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    do_heal(user, 100); // heal to 100%
    if (B_STATUS(user) != AILMENT_NONE)
        set_status(user, AILMENT_CURE, user);
    return true;
}

u8 lunar_dance_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    do_damage(user, B_CURRENT_HP(user));
    if (SideCountUsablePkmn(SIDE_OF(user)) > 2) {
        struct action* a = prepend_action(user, user, ActionSwitch, EventForcedSwitch);
        a->priv[0] = 1;
    }
    AddCallback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)lunar_dance_on_after_move);
    return true;
}

// Thousand waves, Spirit Shackle, Anchor Shot, Block
u8 block_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_TRAPPED);
    return true;
}


// Fairy lock
u8 fairy_lock_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    CLEAR_VOLATILE(TARGET_OF(user), VOLATILE_FAIRY_BLOCK);
    CLEAR_VOLATILE(user, VOLATILE_TRAPPED);
    return true;
}

u8 fairy_lock_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_FAIRY_BLOCK);
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_TRAPPED);
    AddCallback(CB_ON_RESIDUAL, 0, 0, user, (u32)fairy_lock_on_residual);
    return true;
}
