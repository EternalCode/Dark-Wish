#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);

u8 stockpile_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if(user != src) return true;
    if(gPkmnBank[user]->battleData.stockpile_uses == 3)
        return false;
    gPkmnBank[user]->battleData.stockpile_uses++;
    QueueMessage(NULL, user, STRING_SETUP_STOCKPILE, gPkmnBank[user]->battleData.stockpile_uses);
    return true;
}

u8 stockpile_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    acb->data_ptr = ((B_DEFENSE_BUFF(user) << 3) | B_SPDEFENSE_BUFF(user));
    return true;
}

void stockpile_on_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 id = get_callback_src((u32)stockpile_before_move, user);
    u32 logged_data = CB_MASTER[id].data_ptr;
    u8 amount_def = B_DEFENSE_BUFF(user) - (logged_data >> 3);
    u8 amount_spdef = B_SPDEFENSE_BUFF(user) - (logged_data & 0x7);
    gPkmnBank[user]->battleData.stockpile_def_boost += amount_def;
    gPkmnBank[user]->battleData.stockpile_spdef_boost += amount_spdef;
}

u8 stockpile_drop_on_before_stat_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (user != src) return true;
    gPkmnBank[user]->battleData.stockpile_uses = 0;
    if (gPkmnBank[user]->battleData.stockpile_def_boost) {
        B_USER_STAT_MOD_CHANCE(user, STAT_DEFENSE - 1) = 100;
        B_USER_STAT_MOD_AMOUNT(user, STAT_DEFENSE - 1) = -gPkmnBank[user]->battleData.stockpile_def_boost;
        gPkmnBank[user]->battleData.stockpile_def_boost = 0;
    }
    if (gPkmnBank[user]->battleData.stockpile_spdef_boost) {
        B_USER_STAT_MOD_CHANCE(user, STAT_SPECIAL_DEFENSE - 1) = 100;
        B_USER_STAT_MOD_AMOUNT(user, STAT_SPECIAL_DEFENSE - 1) = -gPkmnBank[user]->battleData.stockpile_spdef_boost;
        gPkmnBank[user]->battleData.stockpile_spdef_boost = 0;
    }
    return true;
}

void spit_up_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if(user != src) return true;
    B_MOVE_POWER(user) = gPkmnBank[user]->battleData.stockpile_uses * 100;
}

u8 spit_up_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (gPkmnBank[user]->battleData.stockpile_uses == 0)
        return false;
    AddCallback(CB_ON_BEFORE_STAT_MOD, -1, 0, user, (u32)stockpile_drop_on_before_stat_mod);
    return true;
}

u8 swallow_on_tryhit_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (gPkmnBank[user]->battleData.stockpile_uses == 0 || (B_CURRENT_HP(user) == TOTAL_HP(user)))
        return false;
    switch (gPkmnBank[user]->battleData.stockpile_uses) {
        case 1:
            B_HEAL(user) = 25;
            break;
        case 2:
            B_HEAL(user) = 50;
            break;
        case 3:
            B_HEAL(user) = 100;
            break;
    }
    AddCallback(CB_ON_BEFORE_STAT_MOD, -1, 0, user, (u32)stockpile_drop_on_before_stat_mod);
    return true;
}






