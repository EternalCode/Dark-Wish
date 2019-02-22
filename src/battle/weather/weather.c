#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../abilities/battle_abilities.h"

extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern void clear_other_weather(void);
extern void dprintf(const char * str, ...);
extern bool BankMonHasType(u8 bank, enum PokemonType type);
extern bool do_damage_residual(u8 bank_index, u16 dmg, u32 ability_flags);
extern bool BankMonIsMonoType(u8 bank, enum PokemonType type);
extern void do_damage(u8 bank_index, u16 dmg);

/* Rain */
u16 rain_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (IS_WEATHER_STANDARD_RAIN && (B_MOVE_HAS_TYPE(user, TYPE_WATER))) {
        return 150;
    } else if (IS_WEATHER_STANDARD_RAIN && B_MOVE_HAS_TYPE(user, TYPE_FIRE)) {
        return 50;
    } else {
        return 100;
    }
}

u16 rain_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->data_ptr) {
        acb->data_ptr = 0;
    } else {
        acb->data_ptr = 1;
        return true;
    }
    if (acb->duration == 0) {
        QueueMessage(NULL, NULL, STRING_RAIN_STOPPED, MOVE_RAINDANCE);
        gBattleMaster->field_state.is_raining = false;
    } else {
        QueueMessage(NULL, NULL, STRING_RAIN_FALLING, MOVE_RAINDANCE);
    }
    return true;
}

void rain_init_effect()
{
    gBattleMaster->field_state.is_raining = true;
    AddCallback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)rain_on_residual);
    AddCallback(CB_ON_WEATHER_DMG, 0, 5, 0, (u32)rain_dmg_mod);
    QueueMessage(0, 0, STRING_RAINING, MOVE_RAINDANCE);
    return true;
}

void clear_rain()
{
    gBattleMaster->field_state.is_raining = false;
    delete_callback((u32)rain_dmg_mod);
    delete_callback((u32)rain_on_residual);
}


/* Sun */
u16 sun_dmg_mod(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (IS_WEATHER_STANDARD_SUN && B_MOVE_HAS_TYPE(user, TYPE_FIRE)) {
        return 150;
    } else if (IS_WEATHER_STANDARD_SUN && B_MOVE_HAS_TYPE(user, TYPE_WATER)) {
        return 50;
    } else {
        return 100;
    }
}

u16 sun_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->data_ptr) {
        acb->data_ptr = 0;
    } else {
        acb->data_ptr = 1;
        return true;
    }
    if (acb->duration == 0) {
        QueueMessage(NULL, NULL, STRING_SUNLIGHT_FADE, NULL);
        gBattleMaster->field_state.is_sunny = false;
    } else {
        QueueMessage(NULL, NULL, STRING_SUNLIGHT_STRONG, NULL);
    }
    return true;
}

void sun_init_effect()
{
    gBattleMaster->field_state.is_sunny = true;
    AddCallback(CB_ON_WEATHER_DMG, 1, 5, NULL, (u32)sun_dmg_mod);
    AddCallback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)sun_on_residual);
    QueueMessage(0, 0, STRING_SUNLIGHT_HARSH, 0);
}

void clear_sun()
{
    gBattleMaster->field_state.is_sunny = false;
    delete_callback((u32)sun_dmg_mod);
    delete_callback((u32)sun_on_residual);
}


/* Sandstorm */
u16 sandstorm_stat_mod(u8 user, u8 src, u16 stat_id, struct anonymous_callback* acb)
{
    if (stat_id != SPDEFENSE_MOD) return (u32)acb->data_ptr;
    if (IS_WEATHER_SANDSTORM && BankMonHasType(user, TYPE_ROCK)) {
        return PERCENT((u32)acb->data_ptr, 150);
    } else {
        return (u32)acb->data_ptr;
    }
}


u16 sandstorm_on_residual_buffet(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->data_ptr) {
        acb->data_ptr = 0;
    } else {
        acb->data_ptr = 1;
    }
    if (acb->duration == 0) {
        if (acb->data_ptr) {
            QueueMessage(NULL, NULL, STRING_SANDSTORM_END, NULL);
            gBattleMaster->field_state.is_sandstorm = false;
        }
    } else {
        if (acb->data_ptr)
            QueueMessage(NULL, NULL, STRING_SANDSTORM_RAGE, NULL);
        if (!IS_WEATHER_SANDSTORM || BankMonHasType(user, TYPE_ROCK) || BankMonHasType(user, TYPE_STEEL) || BankMonHasType(user, TYPE_GROUND))
            return true;
        if (HAS_VOLATILE(user, VOLATILE_DIVE) || HAS_VOLATILE(user, VOLATILE_DIG))
            return true;
        if (do_damage_residual(user, 1, A_FLAG_SANDSTORM_DMG_PREVENT)) {
            do_damage(user, MAX(1, (TOTAL_HP(user) / 16)));
            QueueMessage(NULL, user, STRING_SANDSTORM_BUFFET, MOVE_SANDSTORM);
        }
    }
    return true;
}

void sandstorm_init_effect()
{
    gBattleMaster->field_state.is_sandstorm = true;
    AddCallback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)sandstorm_on_residual_buffet);
    AddCallback(CB_ON_STAT_MOD, 10, 5, NULL, (u32)sandstorm_stat_mod);
    QueueMessage(NULL, NULL, STRING_SANDSTORM_KICKED, NULL);
}

void clear_sandstorm()
{
    gBattleMaster->field_state.is_sandstorm = false;
    delete_callback((u32)sandstorm_on_residual_buffet);
    delete_callback((u32)sandstorm_stat_mod);
}


/* hail */
u16 hail_on_residual_buffet(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->data_ptr) {
        acb->data_ptr = 0;
    } else {
        acb->data_ptr = 1;
    }
    if (acb->duration == 0) {
        if (acb->data_ptr) {
            QueueMessage(NULL, NULL, STRING_RAIN_STOPPED, MOVE_HAIL);
            gBattleMaster->field_state.is_hail = false;
        }
    } else {
        if (acb->data_ptr)
            QueueMessage(NULL, NULL, STRING_RAIN_FALLING, MOVE_HAIL);
        if (!IS_WEATHER_HAIL || BankMonHasType(user, TYPE_ICE))
            return true;
        if (HAS_VOLATILE(user, VOLATILE_DIVE) || HAS_VOLATILE(user, VOLATILE_DIG))
            return true;
        if(do_damage_residual(user, MAX(1, (TOTAL_HP(user) / 16)), A_FLAG_HAIL_DMG_PREVENT))
            QueueMessage(NULL, user, STRING_SANDSTORM_BUFFET, MOVE_HAIL);

    }
    return true;
}

void hail_init_effect()
{
    gBattleMaster->field_state.is_hail = true;
    AddCallback(CB_ON_RESIDUAL, 1, 5, NULL, (u32)hail_on_residual_buffet);
    QueueMessage(0, 0, STRING_RAINING, MOVE_HAIL);
}

void clear_hail()
{
    gBattleMaster->field_state.is_hail = false;
    delete_callback((u32)hail_on_residual_buffet);
}



void clear_other_weather()
{
    // todo
    gBattleMaster->field_state.is_raining = false;
    gBattleMaster->field_state.is_sunny = false;
    gBattleMaster->field_state.is_sandstorm = false;
    gBattleMaster->field_state.is_hail = false;
    gBattleMaster->field_state.suppress_weather = false;
    clear_rain();
    clear_sun();
    clear_sandstorm();
    clear_hail();
}

bool set_weather(enum WeatherTypes weather)
{
    clear_other_weather();
    switch (weather) {
        case WEATHER_RAIN:
            rain_init_effect();
            break;
        case WEATHER_SUN:
            sun_init_effect();
            break;
        case WEATHER_SANDSTORM:
            sandstorm_init_effect();
            break;
        case WEATHER_HAIL:
            hail_init_effect();
            break;
        default:
            return false;
    };
    return true;
}


enum WeatherTypes get_weather()
{
    if (gBattleMaster->field_state.suppress_weather) return WEATHER_CLEAR;
    if (gBattleMaster->field_state.is_raining) return WEATHER_RAIN;
    if (gBattleMaster->field_state.is_sunny) return WEATHER_SUN;
    if (gBattleMaster->field_state.is_sandstorm) return WEATHER_SANDSTORM;
    if (gBattleMaster->field_state.is_hail) return WEATHER_HAIL;
    return WEATHER_CLEAR;
}
