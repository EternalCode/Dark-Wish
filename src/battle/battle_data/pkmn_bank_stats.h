#ifndef PKMN_BANK_STAT_H_
#define PKMN_BANK_STAT_H_

#include <pokeagb/pokeagb.h>
#include "pkmn_bank.h"
#include "battle_state.h"
#include "../moves/moves.h"
#include "../battle_actions/actions.h"
#include "../battle_text/battle_pick_message.h"

extern bool has_volatile(u8 bank, enum Volatiles v);
extern void clear_volatile(u8 bank, enum Volatiles v);
extern void add_volatile(u8 bank, enum Volatiles v);
extern u16 stage_modify_stat(u16 stat, s8 mod, u8 id, u8 bank);

// this one is unrelated but I want to have it here
#define CPUFSCPY 0
#define CPUFSSET 1
#define CPUModeFS(size, mode) ((size >> 2) | (mode << 24))
#define OBJID_HIDE(objid) gSprites[objid].final_oam.affine_mode = 2
#define OBJID_SHOW(objid) gSprites[objid].final_oam.affine_mode = 0
#define OBJID_SHOW_AFFINE(objid) gSprites[objid].final_oam.affine_mode = 1

/*
 * Names of stats as IDs in stage_modify_stat
 */
#define ATTACK_MOD 0
#define DEFENSE_MOD 1
#define SPEED_MOD 2
#define SPATTACK_MOD 3
#define SPDEFENSE_MOD 4
#define ACCURACY_MOD 5
#define EVASION_MOD 6
#define CRIT_CHANCE_MOD 7

/*
 * Get Pokemon's current battle stats based on stage changes to stat
 *
 */
#define B_ATTACK_STAT(bank) stage_modify_stat(gPkmnBank[bank]->battleData.attack_raw, gPkmnBank[bank]->battleData.attack, 0, bank)
#define B_DEFENSE_STAT(bank) stage_modify_stat(gPkmnBank[bank]->battleData.defense_raw, gPkmnBank[bank]->battleData.defense, 1, bank)
#define B_SPEED_STAT(bank) stage_modify_stat(gPkmnBank[bank]->battleData.speed_raw, gPkmnBank[bank]->battleData.speed, 2, bank)
#define B_SPATTACK_STAT(bank) stage_modify_stat(gPkmnBank[bank]->battleData.sp_atk_raw, gPkmnBank[bank]->battleData.sp_atk, 3, bank)
#define B_SPDEFENSE_STAT(bank) stage_modify_stat(gPkmnBank[bank]->battleData.sp_def_raw, gPkmnBank[bank]->battleData.sp_def, 4, bank)
#define B_ACCURACY_STAT(bank) stage_modify_stat(0, gPkmnBank[bank]->battleData.accuracy, 5, bank)
#define B_EVASION_STAT(bank) stage_modify_stat(0, gPkmnBank[bank]->battleData.evasion, 6, bank)
#define B_CRITCHANCE_STAT(bank) stage_modify_stat(0, gPkmnBank[bank]->battleData.crit_mod, 7, bank)

#define B_ATTACKING_STAT(attacker) (B_MOVE_CATEGORY(attacker) == MOVE_PHYSICAL) ? B_ATTACK_STAT(attacker) : B_SPATTACK_STAT(attacker)
#define B_DEFENDING_STAT(defender, category) (category == MOVE_PHYSICAL) ? B_DEFENSE_STAT(defender) : B_SPDEFENSE_STAT(defender)

#define B_ATTACK_BUFF(bank) (gPkmnBank[bank]->battleData.attack)
#define B_DEFENSE_BUFF(bank) (gPkmnBank[bank]->battleData.defense)
#define B_SPEED_BUFF(bank) (gPkmnBank[bank]->battleData.speed)
#define B_SPATTACK_BUFF(bank) (gPkmnBank[bank]->battleData.sp_atk)
#define B_SPDEFENSE_BUFF(bank) (gPkmnBank[bank]->battleData.sp_def)
#define B_ACCURACY_BUFF(bank)  (gPkmnBank[bank]->battleData.accuracy)
#define B_EVASION_BUFF(bank) (gPkmnBank[bank]->battleData.evasion)
#define B_CRIT_BUFF(bank) (gPkmnBank[bank]->battleData.crit_mod)

#define B_WEIGHT(bank) (gPkmnBank[bank]->battleData.weight)

/*
 * Umodified battle sats
 */
#define B_ATTACK_STAT_UMOD(bank) (gPkmnBank[bank]->battleData.attack_raw)
#define B_DEFENSE_STAT_UMOD(bank) (gPkmnBank[bank]->battleData.defense_raw)
#define B_SPEED_STAT_UMOD(bank) (gPkmnBank[bank]->battleData.speed_raw)
#define B_SPATTACK_STAT_UMOD(bank) (gPkmnBank[bank]->battleData.sp_atk_raw)
#define B_SPDEFENSE_STAT_UMOD(bank) (gPkmnBank[bank]->battleData.sp_def_raw)

#define PERCENT(number, percent) ((number * percent) / 100)

/*
 * P_bank battleData volatile macros
 */
#define ADD_VOLATILE(bank, v) (add_volatile(bank, v))
// clear the bit, even when not set.
#define CLEAR_VOLATILE(bank, v) (clear_volatile(bank, v))
#define HAS_VOLATILE(bank, v) (has_volatile(bank, v))

/*
 * P_bank battleData set and fetch macros
 *
 */
#define B_SPECIES(bank) (gPkmnBank[bank]->battleData.species)
#define CURRENT_MOVE(bank) (gPkmnBank[bank]->battleData.current_move)
#define LAST_MOVE(bank) (gPkmnBank[bank]->battleData.last_move)
#define BANK_ABILITY(bank) (gPkmnBank[bank]->battleData.ability)
#define B_PKMN(bank) (gPkmnBank[bank]->this_pkmn)
#define B_FLINCH(bank) (gPkmnBank[bank]->battleData.flinch)
#define B_MOVE_FLINCH(bank) (gBattleMaster->b_moves[bank].flinch)
#define B_MOVE_TYPE(bank, i) (gBattleMaster->b_moves[bank].type[i])
#define B_MOVE_POWER(bank) (gBattleMaster->b_moves[bank].power)
#define B_MOVE_STAB(bank) (gBattleMaster->b_moves[bank].stab)
#define B_MOVE_ACCURACY(bank) (gBattleMaster->b_moves[bank].accuracy)
#define B_MOVE_PRIORITY(bank) (gBattleMaster->b_moves[bank].priority)
#define B_MOVE_CONTACT(bank) (gBattleMaster->b_moves[bank].makes_contact)
#define B_MOVE_IGNORING_ABILITIES(bank) (gBattleMaster->b_moves[bank].ignore_abilities)
#define B_MOVE_HAS_TYPE(bank, type) ((B_MOVE_TYPE(bank, 0) == type) || (B_MOVE_TYPE(bank, 1) == type))
#define B_MOVE_IS_STATUS(bank) (gBattleMaster->b_moves[bank].category == MOVE_STATUS)
#define B_MOVE_IS_SPECIAL(bank) (gBattleMaster->b_moves[bank].category == MOVE_SPECIAL)
#define B_MOVE_IS_PHYSICAL(bank) (gBattleMaster->b_moves[bank].category == MOVE_PHYSICAL)
#define B_MOVE_CATEGORY(bank) (gBattleMaster->b_moves[bank].category)
#define B_MOVE_WILL_CRIT(bank) (gBattleMaster->b_moves[bank].will_crit)
#define B_MOVE_CAN_CRIT(bank) (gBattleMaster->b_moves[bank].can_crit)
#define B_MOVE_DMG(bank) (gBattleMaster->b_moves[bank].dmg)
#define B_DRAIN(bank) (gBattleMaster->b_moves[bank].drain)
#define B_MOVE_EFFECTIVENESS(bank) (gBattleMaster->b_moves[bank].effectiveness)
#define B_MOVE_IGNORE_ATK(bank) (gBattleMaster->b_moves[bank].ignore_target_atk)
#define B_MOVE_IGNORE_DEF(bank) (gBattleMaster->b_moves[bank].ignore_target_def)
#define B_MOVE_IGNORE_EVASION(bank) (gBattleMaster->b_moves[bank].ignore_target_evasion)
#define B_MOVE_MULTI(bank) ((gBattleMaster->b_moves[bank].hit_times > 1) || (gBattleMaster->b_moves[bank].hit_counter > 1))
#define PROTECTION_TURNS(bank) (gPkmnBank[bank]->battleData.protect_used_turns)
#define B_GENDER(bank) (gPkmnBank[bank]->battleData.gender)
#define B_REDUCE_PP(bank) (gPkmnBank[bank]->battleData.reduce_pp)
#define B_IS_TRAPPED(bank) (gPkmnBank[bank]->battleData.is_trapped)
#define B_PKMN_TYPE(bank, index) (gPkmnBank[bank]->battleData.type[index])
#define B_CURRENT_HP(bank) (gPkmnBank[bank]->battleData.current_hp)
#define B_LEVEL(bank) (gPkmnBank[bank]->battleData.level)
#define TOTAL_HP(bank) (gPkmnBank[bank]->battleData.total_hp)
#define B_STATUS(bank) (gPkmnBank[bank]->battleData.status)
#define B_PSTATUS(bank) (gPkmnBank[bank]->battleData.pseudo_ailment)
#define TARGET_OF(bank) (gPkmnBank[bank]->battleData.my_target)
#define SET_CONFUSION_TURNS(bank, v) (gPkmnBank[bank]->battleData.confusion_turns = v)
#define B_IS_GROUNDED(bank) (gPkmnBank[bank]->battleData.is_grounded)
#define B_INFILTRATES(bank) (gBattleMaster->b_moves[bank].infiltrates)
#define B_HEAL(bank) (gBattleMaster->b_moves[bank].heal)
#define B_ITEM(bank) (gPkmnBank[bank]->battleData.item)
#define B_MOVE_FAILED(bank) (gPkmnBank[bank]->battleData.move_failed)
#define B_LAST_MOVE_FAILED(bank) (gPkmnBank[bank]->battleData.last_move_failed)
#define B_IS_FAINTED(bank) ((gPkmnBank[bank]->battleData.fainted) || (B_CURRENT_HP(bank) < 1))
#define B_FAINTED(bank) (gPkmnBank[bank]->battleData.fainted)
#define B_GET_MOVE(bank, id) (gPkmnBank[bank]->battleData.moves[id])
#define B_GET_MOVE_PP(bank, id) (gPkmnBank[bank]->battleData.move_pp[id])
#define B_LAST_DMG(bank) (gPkmnBank[bank]->battleData.last_damage)
#define ALLY_OF(bank) (bank ^ 1)
#define B_DID_CRIT(bank) (gPkmnBank[bank]->battleData.did_crit)

/*
 *
 * Secondary status macros from battle state
 */
#define B_USER_STAT_MOD_CHANCE(bank, stat) (gBattleMaster->b_moves[bank].b_procs.chance_user[stat])
#define B_USER_STAT_MOD_AMOUNT(bank, stat) (gBattleMaster->b_moves[bank].b_procs.user_amounts[stat])

#define B_TARGET_STAT_MOD_CHANCE(bank, stat) (gBattleMaster->b_moves[bank].b_procs.chance_target[stat])
#define B_TARGET_STAT_MOD_AMOUNT(bank, stat) (gBattleMaster->b_moves[bank].b_procs.target_amounts[stat])

#define B_AILMENT_PROCS_CHANCE_USER(bank) (gBattleMaster->b_moves[bank].b_procs.ailment_user_chance)
#define B_AILMENT_PROCS_CHANCE_TARGET(bank) (gBattleMaster->b_moves[bank].b_procs.ailment_target_chance)
#define B_AILMENT_PROCS_USER(bank) (gBattleMaster->b_moves[bank].b_procs.ailment_user)
#define B_AILMENT_PROCS_TARGET(bank) (gBattleMaster->b_moves[bank].b_procs.ailment_target)


/*
 * General Pbank macros
 */
#define PLAYER_SIDE 0
#define OPPONENT_SIDE 1

#define SIDE_OF(bank) ((bank > 1) ? 1 : 0)
#define ACTIVE_BANK(bank) (gPkmnBank[bank]->battleData.is_active_bank)

#define ACTION_PRANKSTER (CURRENT_ACTION->prankstered)
#define ACTION_BOUNCED (CURRENT_ACTION->has_bounced)

#define MOVE_EFFECTIVENESS(target_type, dmg_type) (effectiveness_chart[((target_type * 19) + (dmg_type))])


#endif /* PKMN_BANK_STAT_H_ */
