#ifndef MOVE_TEMPLATES_H_
#define MOVE_TEMPLATES_H_

#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../abilities/ability_override.h"
#include "../anonymous_callbacks/anonymous_callbacks.h"
#include "../../pokemon/types/pkmn_types.h"

/* Ailment names and order:

    AILMENT_NONE
    AILMENT_SLEEP
    AILMENT_POISON
    AILMENT_BURN
    AILMENT_FREEZE
    AILMENT_PARALYZE
    AILMENT_BAD_POISON
    AILMENT_CONFUSION
    AILMENT_CURE
*/

/*  Order of stat boosts:

    Attack - 0
    Defense - 1
    Speed - 2
    Special Attack - 3
    Special Defense - 4
    Accuracy - 5
    Evasion - 6
    Critical chance - 7
*/

struct move_procs {
    u8 chance_user[8];
    s8 user_amounts[8];

    u8 chance_target[8];
    s8 target_amounts[8];

    enum StatusAilments ailment_user;
    enum StatusAilments ailment_target;
    u8 ailment_user_chance;      //
    u8 ailment_target_chance;    // Chance the ailment affects the user
};

#define MOVE_AILMENT_PROCS_CHANCE_USER(move) gBattleMoves[move].ailment_user_chance
#define MOVE_AILMENT_PROCS_CHANCE_TARGET(move) gBattleMoves[move].ailment_target_chance
#define MOVE_AILMENT_PROCS_STATUS_USER(move) gBattleMoves[move].ailment_user
#define MOVE_AILMENT_PROCS_STATUS_TARGET(move) gBattleMoves[move].ailment_target


#include "../battle_data/battle_state.h"

/* Move flags list */
#define FLAG_CHARGE (1 << 1)
#define FLAG_RECHARGE (1 << 2)
#define FLAG_CONTACT (1 << 3)
#define FLAG_DEFROST (1 << 4)
#define FLAG_GRAVITY (1 << 5)
#define FLAG_HEAL (1 << 6)
#define FLAG_MIRROR (1 << 7)
#define FLAG_POWDER (1 << 8)
#define FLAG_PROTECT (1 << 9)
#define FLAG_AUTHENTIC (1 << 10)
#define FLAG_PUNCH (1 << 11)
#define FLAG_REFLECTABLE (1 << 12)
#define FLAG_SNATCH (1 << 13)
#define FLAG_SOUND (1 << 14)
#define FLAG_BITE (1 << 15) // strongjaw
#define FLAG_BULLET (1 << 16)
#define FLAG_ONSELF (1 << 17)
#define FLAG_TARGET (1 << 18)
#define FLAG_HITS_ALL (1 << 19)
#define FLAG_HITS_MY_SIDE (1 << 20)
#define FLAG_HITS_FOE_SIDE (1 << 21)
#define FLAG_HITS_ALLY (1 << 22)
#define FLAG_HITS_ADJACENT (1 << 23)
#define FLAG_HITS_ALLY_OR_SELF (1 << 24)
#define FLAG_TRIAGE (1 << 25)
#define FLAG_DANCE (1 << 26)
#define FLAG_PULSE (1 << 27)
#define FLAG_OHKO (1 << 28)
#define FLAG_CATEGORY_OVERRIDE (1 << 29)
#define FLAG_STEAL_OFFENSIVE (1 << 30)
#define FLAG_STEAL_BOOSTS (1 << 31)
#define FLAGS_UNUSED (1 << 32)

/*
 * Field data fetch macros
 */
#define MOVE_PRIORITY(move) (gBattleMoves[move].priority)
#define MOVE_POWER(move) (gBattleMoves[move].base_power)
#define MOVE_CATEGORY(move) (gBattleMoves[move].category)
#define MOVE_ACCURACY(move) (gBattleMoves[move].accuracy)
#define MOVE_CRIT(move) (gBattleMoves[move].crit_ratio)
#define MOVE_RECOIL(move) (gBattleMoves[move].recoil)
#define M_FLINCH(move) (gBattleMoves[move].flinch_chance)
#define MOVE_TYPE(move) (gBattleMoves[move].type)
#define IS_MOVE_STATUS(move) (gBattleMoves[move].category == MOVE_STATUS)
#define IS_MOVE_PHYSICAL(move) (gBattleMoves[move].category == MOVE_PHYSICAL)
#define IS_MOVE_SPECIAL(move) (gBattleMoves[move].category == MOVE_SPECIAL)
#define IS_CHARGE(move) ((gBattleMoves[move].m_flags) & FLAG_CHARGE)
#define IS_CONTACT(move) ((gBattleMoves[move].m_flags) & FLAG_CONTACT)
#define IS_PUNCH(move) ((gBattleMoves[move].m_flags) & FLAG_PUNCH)
#define IS_BITE(move) ((gBattleMoves[move].m_flags) & FLAG_BITE)
#define IS_RECHARGE(move) ((gBattleMoves[move].m_flags) & FLAG_RECHARGE)
#define IS_DEFROST(move) ((gBattleMoves[move].m_flags) & FLAG_DEFROST)
#define IS_GRAVITY(move) ((gBattleMoves[move].m_flags) & FLAG_GRAVITY)
#define IS_HEAL(move) ((gBattleMoves[move].m_flags) & FLAG_HEAL)
#define IS_POWDER(move) ((gBattleMoves[move].m_flags) & FLAG_POWDER)
#define IS_MIRRORABLE(move) ((gBattleMoves[move].m_flags) & FLAG_MIRROR)
#define IS_PROTECTABLE(move) ((gBattleMoves[move].m_flags) & FLAG_PROTECT)
#define IS_REFLECTABLE(move) ((gBattleMoves[move].m_flags) & FLAG_REFLECTABLE)
#define IS_SNATCHABLE(move) ((gBattleMoves[move].m_flags) & FLAG_SNATCH)
#define IS_DANCE(move) ((gBattleMoves[move].m_flags) & FLAG_DANCE)
#define IS_TRIAGE(move) ((gBattleMoves[move].m_flags) & FLAG_TRIAGE)
#define IS_SOUND_BASE(move) ((gBattleMoves[move].m_flags) & FLAG_SOUND)
#define IS_PULSE(move) ((gBattleMoves[move].m_flags) & FLAG_PULSE)
#define IS_BULLET(move) ((gBattleMoves[move].m_flags) & FLAG_BULLET)
#define IS_SEMI_INVUL(move) ((gBattleMoves[move].m_flags) & FLAG_SEMI_INVUL)
#define IS_OHKO(move) ((gBattleMoves[move].m_flags) & FLAG_OHKO)
#define CAT_OVERRIDE(move) ((gBattleMoves[move].m_flags) & FLAG_CATEGORY_OVERRIDE)
#define STEAL_OFFENSIVE(move) ((gBattleMoves[move].m_flags) & FLAG_STEAL_OFFENSIVE)
#define STEAL_BOOSTS(move) ((gBattleMoves[move].m_flags) & FLAG_STEAL_BOOSTS)

#define M_HITS_FOE_SIDE(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_FOE_SIDE)
#define M_HITS_MY_SIDE(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_MY_SIDE)
#define M_HITS_TARGET(move) ((gBattleMoves[move].m_flags) & FLAG_TARGET)
#define M_HITS_SELF(move) ((gBattleMoves[move].m_flags) & FLAG_ONSELF)
#define M_HITS_ALLY(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_ALLY)
#define M_HITS_ALL(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_ALL)
#define M_HITS_ADJ(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_ADJACENT)
#define M_HITS_ALLY_OR_SELF(move) ((gBattleMoves[move].m_flags) & FLAG_HITS_ALLY_OR_SELF)

#define MAKES_CONTACT(move, bank) (IS_CONTACT(move) && (!gBattleMaster->b_moves[bank].makes_contact))
#define DEF_CATEGORY(move) ((CAT_OVERRIDE(move)) ? ((IS_MOVE_PHYSICAL(move) ? MOVE_SPECIAL : MOVE_PHYSICAL)) : MOVE_CATEGORY(move))
#define MOVE_SECONDARY_STATUS_CHANCE(move, bank) gBattleMoves[move].procs->secondary_status_chance[SIDE_OF(bank)]
#define MOVE_SECONDARY_STATUS(move, bank) gBattleMoves[move].procs->secondary_status[SIDE_OF(bank)]


enum MoveCategory {
    MOVE_PHYSICAL,
    MOVE_SPECIAL,
    MOVE_STATUS,
};

enum PokemonStat {
    STAT_ATTACK = 0,
    STAT_DEFENSE = 1,
    STAT_SPEED = 2,
    STAT_SPECIAL_ATTACK = 3,
    STAT_SPECIAL_DEFENSE = 4,
    STAT_ACCURACY = 5,
    STAT_EVASION = 6,
    STAT_CRIT = 7,
};

/*

List of flags and their descriptions:

authentic: Ignores a target's substitute.
bite: Power is multiplied by 1.5 when used by a Pokemon with the Ability Strong Jaw.
bullet: Has no effect on Pokemon with the Ability Bulletproof.
charge: The user is unable to make a move between turns.
contact: Makes contact.
defrost: Thaws the user if executed successfully while the user is frozen.
gravity: Prevented from being executed or selected during Gravity's effect.
heal: Prevented from being executed or selected during Heal Block's effect.
mirror: Can be copied by Mirror Move.
powder: Has no effect on Grass-type Pokemon, Pokemon with the Ability Overcoat, and Pokemon holding Safety Goggles.
protect: Blocked by Detect, Protect, Spiky Shield, and if not a Status move, King's Shield.
pulse: Power is multiplied by 1.5 when used by a Pokemon with the Ability Mega Launcher.
punch: Power is multiplied by 1.2 when used by a Pokemon with the Ability Iron Fist.
recharge: If this move is successful, the user must recharge on the following turn and cannot make a move.
reflectable: Bounced back to the original user by Magic Coat or the Ability Magic Bounce.
snatch: Can be stolen from the original user and instead used by another Pokemon using Snatch.
sound: Has no effect on Pokemon with the Ability Soundproof.

*/



typedef void (*MoveBeforeTurnCallback)(u8 user, u8 src, u16 move, struct anonymous_callback* acb);
typedef void (*MoveBeforeSwitchOutCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnStartCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveBeforeMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnFailCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnModifyMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnTryHitMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnInvulnerableTryHitMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnBasePowerCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnDamageCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef u8 (*MoveOnEffectCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);
typedef void (*MoveOnAfterMoveCallback)(u8 user, u8 source, u16 move, struct anonymous_callback* acb);

struct move_data {
    pchar name[22];
    u8 accuracy;
    u8 base_power;
    pchar* description;
    u8 pp;
    s8 priority;
    u8 crit_ratio;
    enum MoveCategory category;
    enum PokemonType type;
    u32 m_flags;
    u8 drain;
    u8 recoil;
    u8 heal;
    u8 multi_hit[2];
    u8 recoil_struggle : 1;
    u8 flinch_chance : 7;
    u8* animation; // animation script pointer
    struct move_procs* procs;

    MoveBeforeTurnCallback before_turn;
    MoveBeforeSwitchOutCallback before_switch;
    MoveOnStartCallback on_start;
    MoveBeforeMoveCallback before_move;
    MoveOnFailCallback on_move_fail;
    MoveOnModifyMoveCallback on_modify_move;
    MoveOnTryHitMoveCallback on_tryhit_move;
    MoveOnInvulnerableTryHitMoveCallback on_inv_tryhit_move;
    MoveOnBasePowerCallback on_base_power_move;
    MoveOnDamageCallback on_damage_move;
    MoveOnEffectCallback on_effect_cb;
    MoveOnAfterMoveCallback on_after_move;
};

extern struct move_data gBattleMoves[];


#endif /* MOVE_TEMPLATES_H_ */
