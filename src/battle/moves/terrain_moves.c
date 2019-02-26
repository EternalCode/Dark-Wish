#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern bool is_grounded(u8 bank);
extern void do_heal(u8 bank_index, u8 percent_heal);
extern void clear_terrain(void);

// Electric Terrain
void electric_terrain_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (is_grounded(user) && B_MOVE_HAS_TYPE(user, TYPE_ELECTRIC))
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
}

bool electric_terrain_on_status(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if ((status_id == AILMENT_SLEEP) && is_grounded(user)) {
        QueueMessage(MOVE_ELECTRICTERRAIN, user, STRING_AILMENT_IMMUNE, status_id);
        return false;
    }
    return true;
}

u16 electric_terrain_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        gBattleMaster->field_state.is_electric_terrain = false;
        QueueMessage(MOVE_ELECTRICTERRAIN, user, STRING_MOVE_ENDED, NULL);
    }
    acb->in_use = false;
    return true;
}

u8 electric_terrain_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)electric_terrain_on_status)) return false;
    clear_terrain();
    AddCallback(CB_ON_STATUS, 0, 5, src, (u32)electric_terrain_on_status);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, src, (u32)electric_terrain_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    gBattleMaster->field_state.is_electric_terrain = true;
    QueueMessage(NULL, NULL, STRING_ELECTRIC_TERRAIN_START, NULL);
    return true;
}


// Grass Terrain
const static u16 grassy_terrain_weakened[] = {
    MOVE_EARTHQUAKE,
    MOVE_BULLDOZE,
    MOVE_MAGNITUDE,
};

void grassy_terrain_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    for (u8 i = 0; i < (sizeof(grassy_terrain_weakened) / sizeof(u16)); i++) {
        if (move == grassy_terrain_weakened[i]) {
            B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 50);
            return;
        }
    }
    if (is_grounded(user) && B_MOVE_HAS_TYPE(user, TYPE_GRASS)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
}

u16 grassy_terrain_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (acb->duration != 0) {
        if (is_grounded(user) && (B_CURRENT_HP(user) != TOTAL_HP(user))) {
            do_heal(user, 6);
            QueueMessage(NULL, user, STRING_HEAL, 0);
        }
    } else {
        if (acb->in_use) {
            QueueMessage(MOVE_GRASSYTERRAIN, user, STRING_MOVE_ENDED, NULL);
            gBattleMaster->field_state.is_grassy_terrain = false;
            acb->in_use = false;
        }
    }
    return true;
}

u8 grassy_terrain_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)grassy_terrain_on_base_power)) return false;
    clear_terrain();
    AddCallback(CB_ON_BASE_POWER_MOVE, 0, 5, src, (u32)grassy_terrain_on_base_power);
    AddCallback(CB_ON_RESIDUAL, 0, 5, src, (u32)grassy_terrain_on_residual);
    gBattleMaster->field_state.is_grassy_terrain = true;
    QueueMessage(NULL, NULL, STRING_GRASSY_TERRAIN_START, NULL);
    return true;
}

// Misty Terrain
bool misty_terrain_on_status(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (is_grounded(user) && ((status_id != AILMENT_CURE) && (status_id != AILMENT_NONE))) {
        QueueMessage(MOVE_MISTYTERRAIN, user, STRING_AILMENT_IMMUNE, status_id);
        return false;
    }
    return true;
}

void misty_terrain_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (is_grounded(user) && B_MOVE_HAS_TYPE(user, TYPE_DRAGON)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 50);
    }
}

u16 misty_terrain_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        QueueMessage(MOVE_MISTYTERRAIN, user, STRING_MOVE_ENDED, NULL);
        gBattleMaster->field_state.is_misty_terrain = false;
        acb->in_use = false;
    }
    return true;
}

u8 misty_terrain_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)misty_terrain_on_base_power)) return false;
    clear_terrain();
    AddCallback(CB_ON_BASE_POWER_MOVE, 0, 5, src, (u32)misty_terrain_on_base_power);
    AddCallback(CB_ON_STATUS, 0, 5, src, (u32)misty_terrain_on_status);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, src, (u32)misty_terrain_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    gBattleMaster->field_state.is_misty_terrain = true;
    QueueMessage(NULL, NULL, STRING_MISTY_TERRAIN_START, NULL);
    return true;
}


// Psychic Terrain
u8 psychic_terrain_tryhit(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (!is_grounded(user)) return true;
    if ((B_MOVE_PRIORITY(user) > 0) && (TARGET_OF(user) != user))
        return false;
    return true;
}

void psychic_terrain_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (is_grounded(user) && B_MOVE_HAS_TYPE(user, TYPE_PSYCHIC)) {
        B_MOVE_POWER(user) = PERCENT(B_MOVE_POWER(user), 150);
    }
}

u16 psychic_terrain_on_residual(u8 user, u8 src, u16 status_id, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        QueueMessage(MOVE_PSYCHICTERRAIN, user, STRING_MOVE_ENDED, NULL);
        gBattleMaster->field_state.is_psychic_terrain = false;
        acb->in_use = false;
    }
    return true;
}

u8 psychic_terrain_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (callback_exists((u32)psychic_terrain_on_base_power)) return false;
    clear_terrain();
    AddCallback(CB_ON_BASE_POWER_MOVE, 0, 5, src, (u32)psychic_terrain_on_base_power);
    AddCallback(CB_ON_TRYHIT_MOVE, 4, 5, src, (u32)psychic_terrain_tryhit);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, src, (u32)psychic_terrain_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    gBattleMaster->field_state.is_psychic_terrain = true;
    QueueMessage(NULL, NULL, STRING_PSYCHIC_TERRAIN_START, NULL);
    return true;
}


// clear terrain
void clear_terrain()
{
    gBattleMaster->field_state.is_electric_terrain = false;
    gBattleMaster->field_state.is_grassy_terrain = false;
    gBattleMaster->field_state.is_misty_terrain = false;
    gBattleMaster->field_state.is_psychic_terrain = false;

    delete_callback((u32)psychic_terrain_on_base_power);
    delete_callback((u32)psychic_terrain_tryhit);
    delete_callback((u32)psychic_terrain_on_residual);
    delete_callback((u32)misty_terrain_on_base_power);
    delete_callback((u32)misty_terrain_on_status);
    delete_callback((u32)misty_terrain_on_residual);
    delete_callback((u32)grassy_terrain_on_base_power);
    delete_callback((u32)grassy_terrain_on_residual);
    delete_callback((u32)electric_terrain_on_status);
    delete_callback((u32)electric_terrain_on_residual);
}
