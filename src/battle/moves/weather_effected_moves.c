#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern enum WeatherTypes get_weather(void);

// hurricane
// Thunder
u8 hurricane_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_RAINING) {
        B_MOVE_ACCURACY(user) = 101;
    } else if (IS_WEATHER_SUNNY) {
        B_MOVE_ACCURACY(user) = 50;
    }
    return true;
}

u8 hurricane_on_tryhit_inv(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    u8 defender = TARGET_OF(user);
    if ((CURRENT_MOVE(defender) == MOVE_BOUNCE) || (CURRENT_MOVE(defender) == MOVE_FLY) ||
         (CURRENT_MOVE(defender) == MOVE_SKYDROP)) {
         return true;
     }
     return false;
}


// blizzard
u8 blizzard_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_HAIL)
        B_MOVE_ACCURACY(user) = 101;
    return true;
}

// Morning Sun
// Synthesis
// Moonlight
u8 synthesis_before_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    switch(get_weather()) {
        case WEATHER_RAIN:
        case WEATHER_SANDSTORM:
        case WEATHER_HAIL:
        case WEATHER_HARSH_RAIN:
            B_HEAL(user) = 33;
            break;
        case WEATHER_SUN:
        case WEATHER_HARSH_SUN:
            B_HEAL(user) = 67;
            break;
        default:
            B_HEAL(user) = 50;
    };
    return true;
}


// Growth
u8 growth_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (IS_WEATHER_SUNNY) {
        B_USER_STAT_MOD_CHANCE(user, ATTACK_MOD) = 100;
        B_USER_STAT_MOD_CHANCE(user, SPATTACK_MOD) = 100;
        B_USER_STAT_MOD_AMOUNT(user, ATTACK_MOD) = 2;
        B_USER_STAT_MOD_AMOUNT(user, SPATTACK_MOD) = 2;
    } else {
        B_USER_STAT_MOD_CHANCE(user, ATTACK_MOD) = 100;
        B_USER_STAT_MOD_CHANCE(user, SPATTACK_MOD) = 100;
        B_USER_STAT_MOD_AMOUNT(user, ATTACK_MOD) = 1;
        B_USER_STAT_MOD_AMOUNT(user, SPATTACK_MOD) = 1;
    }
    return true;
}


// Weather ball
u8 weather_ball_on_modify_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    switch(get_weather()) {
        case WEATHER_RAIN:
        case WEATHER_HARSH_RAIN:
            B_MOVE_TYPE(user, 0) = MTYPE_WATER;
            B_MOVE_POWER(user) *= 2;
            break;
        case WEATHER_SUN:
        case WEATHER_HARSH_SUN:
            B_MOVE_TYPE(user, 0) = MTYPE_FIRE;
            B_MOVE_POWER(user) *= 2;
            break;
        case WEATHER_SANDSTORM:
            B_MOVE_TYPE(user, 0) = MTYPE_ROCK;
            B_MOVE_POWER(user) *= 2;
            break;
        case WEATHER_HAIL:
            B_MOVE_TYPE(user, 0) = MTYPE_ICE;
            B_MOVE_POWER(user) *= 2;
            break;
        case WEATHER_MYSTERIOUS_AIR_CURRENT:
            B_MOVE_POWER(user) *= 2;
            break;
        default:
            break;
    };
    return true;
}
