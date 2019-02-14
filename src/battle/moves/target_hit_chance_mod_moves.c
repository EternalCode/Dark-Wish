#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../../pokemon/pokemon.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);

bool unliftable(u8 bank)
{
    return (HAS_VOLATILE(bank, VOLATILE_INGRAIN) || HAS_VOLATILE(bank, VOLATILE_SMACK_DOWN));
}


/* Magnet rise */
u8 magnet_rise_on_effectiveness(u8 target_type, u8 src, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    if (user == src) return effectiveness;
    if ((move_type == TYPE_GROUND)) {
        return 0; // straight immune to ground moves
    } else {
        return (u16)acb->data_ptr;
    }
}

u8 magnet_rise_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_MAGNETRISE, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_MAGNET_RISE);
    }
    return true;
}

u8 magnet_rise_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(user, VOLATILE_MAGNET_RISE)) return false;
    if (unliftable(user)) return false;
    ADD_VOLATILE(user, VOLATILE_MAGNET_RISE);
    AddCallback(CB_ON_EFFECTIVENESS, 0, 5, user, (u32)magnet_rise_on_effectiveness);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, user, (u32)magnet_rise_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    QueueMessage(NULL, user, STRING_MAGNETISM_LEV, NULL);
    return true;
}


/* Telekinesis */

const u16 telekinesis_ban_list[] = {
    SPECIES_SANDYGAST, SPECIES_PALOSSAND, //SPECIES_MEGA_GENGAR
};

u8 telekinesis_on_effectiveness(u8 target_type, u8 src, u16 move_type, struct anonymous_callback* acb)
{
    u8 user = (u8)(acb->data_ptr >> 16);
    u16 effectiveness = ((acb->data_ptr << 16) >> 16);
    dprintf("src is bank %d and user is bank %d\n", src, user);
    if (TARGET_OF(user) != src) return effectiveness;
    if ((move_type == TYPE_GROUND)) {
        return 0; // straight immune to ground moves
    } else {
        return (u16)acb->data_ptr;
    }
}

u8 telekinesis_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_TELEKINESIS, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_TELEKINESIS);
    }
    return true;
}

u8 telekinesis_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(user, VOLATILE_TELEKINESIS)) return false;
    if (unliftable(user)) return false;
    for (u8 i = 0; i < (sizeof(telekinesis_ban_list) / sizeof(u16)); i++) {
        if (telekinesis_ban_list[i] == gPkmnBank[user]->battleData.species)
            return false;
    }
    ADD_VOLATILE(user, VOLATILE_TELEKINESIS);
    AddCallback(CB_ON_EFFECTIVENESS, 0, 3, TARGET_OF(user), (u32)telekinesis_on_effectiveness);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, user, (u32)telekinesis_on_residual);
    CB_MASTER[id].delay_before_effect = 3;
    QueueMessage(NULL, user, STRING_HURLED_AIR, NULL);
    return true;
}


/* Heal block */
bool heal_block_on_disabled_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user == src) return true;
    return (!IS_HEAL(move));
}

u8 heal_block_on_residual(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (acb->in_use) {
        acb->in_use = false;
        QueueMessage(MOVE_HEALBLOCK, user, STRING_MOVE_ENDED, NULL);
        CLEAR_VOLATILE(src, VOLATILE_HEAL_BLOCK);
    }
    return true;
}

u8 heal_block_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_HEAL_BLOCK)) return false;
    AddCallback(CB_ON_DISABLE_MOVE, 0, 5, user, (u32)heal_block_on_disabled_move);
    u8 id = AddCallback(CB_ON_RESIDUAL, 0, 0, TARGET_OF(user), (u32)heal_block_on_residual);
    CB_MASTER[id].delay_before_effect = 5;
    QueueMessage(MOVE_HEALBLOCK, TARGET_OF(user), STRING_HEAL_PREVENT, NULL);
    ADD_VOLATILE(TARGET_OF(user), VOLATILE_HEAL_BLOCK);
    return true;
}
