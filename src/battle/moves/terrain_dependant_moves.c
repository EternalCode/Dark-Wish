#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool BankMonSetType(u8 bank, enum PokemonType type);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern void set_attack_bm_inplace(u8 bank, u8 index, s8 priority);


// Secret power
u8 secret_power_on_modify(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_AILMENT_PROCS_CHANCE_TARGET(user) = 30;
    if (gBattleMaster->field_state.is_electric_terrain) {
        B_AILMENT_PROCS_TARGET(user) = AILMENT_PARALYZE;
    } else if (gBattleMaster->field_state.is_grassy_terrain) {
        B_AILMENT_PROCS_TARGET(user) = AILMENT_SLEEP;
    } else if (gBattleMaster->field_state.is_misty_terrain) {
        B_AILMENT_PROCS_CHANCE_TARGET(user) = 0;
        B_TARGET_STAT_MOD_CHANCE(user, 3) = 30;
        B_TARGET_STAT_MOD_AMOUNT(user, 3) = -1;
    } else if (gBattleMaster->field_state.is_psychic_terrain) {
        B_AILMENT_PROCS_CHANCE_TARGET(user) = 0;
        B_TARGET_STAT_MOD_CHANCE(user, 2) = 30;
        B_TARGET_STAT_MOD_AMOUNT(user, 2) = -1;
    } else {
        B_AILMENT_PROCS_TARGET(user) = AILMENT_PARALYZE;
    }
    return true;
}

// Camouflage
u8 camouflage_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 type = MTYPE_EGG;
    if (gBattleMaster->field_state.is_electric_terrain) {
        type = MTYPE_ELECTRIC;
    } else if (gBattleMaster->field_state.is_grassy_terrain) {
        type = MTYPE_GRASS;
    } else if (gBattleMaster->field_state.is_misty_terrain) {
        type = MTYPE_FAIRY;
    } else if (gBattleMaster->field_state.is_psychic_terrain) {
        type = MTYPE_PSYCHIC;
    } else {
        type = TYPE_NORMAL;
    }
    if (BankMonHasType(user, type))
        return false;
    if (BankMonSetType(user, type)) {
        QueueMessage(MOVE_CAMOUFLAGE, user, STRING_CONVERSION_TYPE, B_PKMN_TYPE(user, 0));
        return true;
    }
    return false;
}

// Nature power
enum TryHitMoveStatus nature_power_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    if (gBattleMaster->field_state.is_electric_terrain) {
        CURRENT_MOVE(user) = MOVE_THUNDERBOLT;
    } else if (gBattleMaster->field_state.is_grassy_terrain) {
        CURRENT_MOVE(user) = MOVE_ENERGYBALL;
    } else if (gBattleMaster->field_state.is_misty_terrain) {
        CURRENT_MOVE(user) = MOVE_MOONBLAST;
    } else if (gBattleMaster->field_state.is_psychic_terrain) {
        CURRENT_MOVE(user) = MOVE_PSYCHIC;
    } else {
        CURRENT_MOVE(user) = MOVE_TRIATTACK;
    }
    set_attack_bm_inplace(user, (user), MOVE_PRIORITY(CURRENT_MOVE(user)));
    LAST_MOVE(user) = MOVE_NATUREPOWER;
    QueueMessage(CURRENT_MOVE(user), user, STRING_ATTACK_USED, 0);
    return TRYHIT_USE_MOVE_NORMAL;
}
