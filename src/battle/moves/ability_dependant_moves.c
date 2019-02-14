#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../abilities/battle_abilities.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

const static u8 target_roleplay_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE, ABILITY_FLOWERGIFT,
    ABILITY_FORECAST, ABILITY_ILLUSION, ABILITY_IMPOSTER, ABILITY_MULTITYPE,
    ABILITY_POWERCONSTRUCT, ABILITY_POWEROFALCHEMY, ABILITY_RECEIVER,
    ABILITY_RKSSYSTEM, ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN,
    ABILITY_STANCECHANGE, ABILITY_TRACE, ABILITY_WONDERGUARD,
    ABILITY_ZENMODE, ABILITY_NONE, ABILITY_MAX,
 };

const static u8 src_roleplay_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE,
    ABILITY_MULTITYPE, ABILITY_POWERCONSTRUCT, ABILITY_RKSSYSTEM,
    ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN, ABILITY_STANCECHANGE,
    ABILITY_NONE, ABILITY_MAX,
};

u8 role_play_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 user_ability = BANK_ABILITY(user);
    u8 target_ability = BANK_ABILITY(TARGET_OF(user));
    // fail if ability is shared
    if (user_ability == target_ability) return false;
    // fail if user has a user-banned ability
    for (u8 i = 0; i < sizeof(src_roleplay_banlist); i++) {
        if (src_roleplay_banlist[i] == user_ability)
            return false;
    }
    // fail if target has a banned ability
    for (u8 i = 0; i < sizeof(target_roleplay_banlist); i++) {
        if (target_roleplay_banlist[i] == target_ability)
            return false;
    }
    // copy target ability
    BANK_ABILITY(user) = target_ability;
    return true;
}


const static u8 skill_swap_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE,
    ABILITY_ILLUSION, ABILITY_MULTITYPE, ABILITY_POWERCONSTRUCT,
    ABILITY_RKSSYSTEM, ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN,
    ABILITY_STANCECHANGE, ABILITY_WONDERGUARD, ABILITY_NONE, ABILITY_MAX
};

u8 skill_swap_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 user_ability = BANK_ABILITY(user);
    u8 target_ability = BANK_ABILITY(TARGET_OF(user));
    // fail if ability is shared
    if (user_ability == target_ability) return false;
    // fail if either pokemon's abilities are banlisted
    for (u8 i = 0; i < sizeof(skill_swap_banlist); i++) {
        if ((skill_swap_banlist[i] == target_ability) || (skill_swap_banlist[i] == user_ability))
            return false;
    }
    // copy target ability
    BANK_ABILITY(user) = target_ability;
    return true;
}


const static u8 gastro_acid_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE,
    ABILITY_MULTITYPE, ABILITY_POWERCONSTRUCT, ABILITY_RKSSYSTEM,
    ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN, ABILITY_STANCECHANGE,
    ABILITY_NONE, ABILITY_MAX
};

u8 gastro_acid_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target_ability = BANK_ABILITY(TARGET_OF(user));
    // fail if target's ability cannot be suppressed
    for (u8 i = 0; i < sizeof(gastro_acid_banlist); i++) {
        if (gastro_acid_banlist[i] == target_ability)
            return false;
    }
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_GASTRO_ACID)) return false;
    // Nullify ability
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_GASTRO_ACID);
    BANK_ABILITY(TARGET_OF(user)) = ABILITY_NONE;
    return true;
}


const static u8 worry_seed_banlist[] = {
    ABILITY_BATTLEBOND, ABILITY_COMATOSE, ABILITY_DISGUISE,
    ABILITY_INSOMNIA, ABILITY_MULTITYPE, ABILITY_POWERCONSTRUCT,
    ABILITY_RKSSYSTEM, ABILITY_SCHOOLING, ABILITY_SHIELDSDOWN,
    ABILITY_STANCECHANGE, ABILITY_TRUANT, ABILITY_MAX,
};

u8 worry_seed_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 target_ability = BANK_ABILITY(TARGET_OF(user));
    // fail if target's ability cannot be suppressed
    for (u8 i = 0; i < sizeof(worry_seed_banlist); i++) {
        if (worry_seed_banlist[i] == target_ability)
            return false;
    }
    // Nullify ability
    BANK_ABILITY(TARGET_OF(user)) = ABILITY_INSOMNIA;
    return true;
}
