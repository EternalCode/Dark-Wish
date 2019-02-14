#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern bool BankMonSetType(u8 bank, enum PokemonType type);
extern bool BankAddType(u8 bank, enum PokemonType type);
extern u16 RandRange(u16, u16);

/* Conversion */
u8 conversion_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // get type of move in first slot
    u8 type = gBattleMoves[(B_GET_MOVE(user, 0))].type;
    if (BankMonHasType(user, type)) {
        return false;
    }

    // X transformed\ninto the Y type!
    QueueMessage(move, user, STRING_CONVERSION_TYPE, type);
    return BankMonSetType(user, type);
}


/* Conversion 2 */
u8 conversion_two_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 last_type = MOVE_TYPE(LAST_MOVE((user ? 0 : 2)));
    u8 possible_types[TYPE_NONE];
    memset(&possible_types, TYPE_NONE, TYPE_NONE);
    if (last_type == TYPE_NONE)
        return false;
    u8 array_index = 0;
    for (u8 i = 0; i < TYPE_MAX; i++) {
        if (BankMonHasType(user, i))
            continue;
        u16 effectiveness = MOVE_EFFECTIVENESS(i, last_type);
        if (effectiveness < 100) {
            possible_types[array_index] = i;
            array_index++;
        }
    }
    u8 type = possible_types[RandRange(0, array_index)];
    QueueMessage(move, user, STRING_CONVERSION_TYPE, type);
    return BankMonSetType(user, type);
}


/* Reflect type */
u8 reflect_type_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 defender = TARGET_OF(user);
    u8 types[3];
    types[0] = B_PKMN_TYPE(defender, 0);
    types[1] = B_PKMN_TYPE(defender, 1);
    types[2] = B_PKMN_TYPE(defender, 2);
    // fail if target lost it's types
    if ((types[0] == TYPE_NONE) && (types[1] == TYPE_NONE) && (types[2] == TYPE_NONE)) {
        return false;
    }

    if ((types[0] == TYPE_NONE) && (types[1] == TYPE_NONE) && (types[2] != TYPE_NONE)) {
        B_PKMN_TYPE(user, 0) = TYPE_NORMAL;
        B_PKMN_TYPE(user, 1) = TYPE_NONE;
        B_PKMN_TYPE(user, 2) = types[2];
    } else {
        B_PKMN_TYPE(user, 0) = types[0];
        B_PKMN_TYPE(user, 1) = types[1];
        B_PKMN_TYPE(user, 2) = types[2];
    }

    //X's type\nchanged to match the Foe Y's!
    QueueMessage(0, user, STRING_REFLECT_TYPE_MATCHED, 0);
    return true;
}


/* Soak */
u8 soak_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (BankMonSetType(TARGET_OF(src), TYPE_WATER))
        QueueMessage(move, TARGET_OF(src), STRING_CONVERSION_TYPE, TYPE_WATER);
    else
        return false;
    return true;
}


/* Flying Press */
u8 flying_press_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    B_MOVE_TYPE(user, 1) = TYPE_FLYING;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MINIMIZE)) {
        B_MOVE_ACCURACY(user) = 101;
    }
    return true;
}

void flying_press_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u16 base_power = B_MOVE_POWER(user);
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_MINIMIZE)) {
        if ((base_power << 1) < base_power) {
            B_MOVE_POWER(user) = 255;
        } else {
            B_MOVE_POWER(user) *= 2;
        }
    }
    B_MOVE_POWER(user) = base_power;
}


/* Ion Deluge */
u8 ion_deluge_on_modify_move_anon(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (B_MOVE_TYPE(user, 0) == TYPE_NORMAL) {
        B_MOVE_TYPE(user, 0) = TYPE_ELECTRIC;
    } else if (B_MOVE_TYPE(user, 1) == TYPE_NORMAL) {
        B_MOVE_TYPE(user, 0) = TYPE_ELECTRIC;
    }
    return true;
}

u8 ion_deluge_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // a deluge of ions showers the battlefield!
    QueueMessage(move, user, STRING_ION_DELUGE, 0);
    AddCallback(CB_ON_TRYHIT_MOVE, -2, 0, user, (u32)(ion_deluge_on_modify_move_anon));
    return true;
}


/* Burn up */
enum TryHitMoveStatus burn_up_on_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return TRYHIT_USE_MOVE_NORMAL;
    return BankMonHasType(user, TYPE_FIRE);
}

u8 burn_up_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    for (u8 i = 0; i < sizeof(gPkmnBank[user]->battleData.type); i++) {
        if (B_PKMN_TYPE(user, i) == TYPE_FIRE) {
            B_PKMN_TYPE(user, i) = TYPE_NONE;
        }
    }
    QueueMessage(move, user, STRING_BURNT_OUT, 0);
    return true;
}


/* Hidden Power*/
u8 hidden_power_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 correlated_sum = 0;
    correlated_sum  += gPkmnBank[user]->battleData.hp_iv;
    correlated_sum  += gPkmnBank[user]->battleData.attack_iv << 1;
    correlated_sum  += gPkmnBank[user]->battleData.defense_iv << 2;
    correlated_sum  += gPkmnBank[user]->battleData.speed_iv << 3;
    correlated_sum  += gPkmnBank[user]->battleData.sp_atk_iv << 4;
    correlated_sum  += gPkmnBank[user]->battleData.sp_def_iv << 5;
    B_MOVE_TYPE(user, 0) = (correlated_sum *15)/63;
    return true;
}


/* Rooost */
extern bool BankMonUntyped(u8 bank);
extern void BankMonReplaceType(u8 bank, enum PokemonType type, enum PokemonType typeReplace);

u8 roost_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        if (acb->data_ptr) {
            BankAddType(src, TYPE_FLYING);
        } else {
            BankMonReplaceType(src, TYPE_NORMAL, TYPE_FLYING);
        }
        acb->in_use = false;
    }
    return true;
}

u8 roost_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (BankMonHasType(user, TYPE_FLYING)) {
        BankMonReplaceType(user, TYPE_FLYING, TYPE_NONE);
        bool add = true;
        if (BankMonUntyped(user)) {
            BankAddType(user, TYPE_NORMAL);
            add = false;
        }
        u8 id = AddCallback(CB_ON_RESIDUAL, -10, 0, user, (u32)roost_on_residual);
        CB_MASTER[id].data_ptr = add;
    }
    return true;
}
