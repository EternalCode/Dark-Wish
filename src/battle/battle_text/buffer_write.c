#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../moves/moves.h"
#include "battle_pick_message.h"
#include "../abilities/battle_abilities.h"

extern void dprintf(const char * str, ...);

void buffer_write_bank_item(pchar* buffer, u8 bank)
{
    dprintf("getting item for bank %d\n", bank);
    memcpy(buffer, items[B_ITEM(bank)].name, POKEAGB_ITEM_NAME_LENGTH);
    buffer[POKEAGB_ITEM_NAME_LENGTH] = 0xFF;
}

void buffer_write_pkmn_nick(pchar* buffer, u8 bank)
{
    memcpy(buffer, gPkmnBank[bank]->battleData.name, sizeof(gPkmnBank[bank]->battleData.name));
}

void buffer_pkmn_nick_arbitrary(pchar* buffer, u8 bank, u8 slot)
{
    if (SIDE_OF(bank)) {
        memcpy(buffer, party_opponent[slot].box.nick, sizeof(party_opponent[slot].box.nick));
        buffer[sizeof(party_opponent[slot].box.nick)] = 0xFF;
    } else {
        memcpy(buffer, party_player[slot].box.nick, sizeof(party_player[slot].box.nick));
        buffer[sizeof(party_player[slot].box.nick)] = 0xFF;
    }
}

void buffer_player_pkmn_nick_arbitrary(pchar* buffer, u8 slot)
{
    memcpy(buffer, party_player[slot].box.nick, sizeof(party_player[slot].box.nick));
    buffer[sizeof(party_player[slot].box.nick)] = 0xFF;
}

void buffer_write_player_name(pchar* buffer)
{
    pstrcpy(buffer, gSaveBlock2Ptr->playerName);
}

void buffer_write_move_name(pchar* buffer, u16 moveId)
{
    pstrcpy(buffer, gBattleMoves[moveId].name);
}

void buffer_write_ability_name(pchar* buffer, u8 ability)
{
    pstrcpy(buffer, &ability_names[ability][0]);
}

void buffer_write_move_type(pchar* buffer, u16 move)
{
    pstrcpy(buffer, PkmnTypeNames[MOVE_TYPE(move)]);
}

void buffer_write_stat_mod(pchar* buffer, u8 stat_id)
{
    switch (stat_id) {
        case REQUEST_ATK:
            pstrcpy(buffer, (pchar*)&str_stat_atk);
            break;
        case REQUEST_DEF:
            pstrcpy(buffer, (pchar*)&str_stat_def);
            break;
        case REQUEST_SPD:
            pstrcpy(buffer, (pchar*)&str_stat_spd);
            break;
        case REQUEST_SPATK:
            pstrcpy(buffer, (pchar*)&str_stat_spatk);
            break;
        case REQUEST_SPDEF:
            pstrcpy(buffer, (pchar*)&str_stat_spdef);
            break;
        case (REQUEST_SPDEF + 1): // accuracy
            pstrcpy(buffer, (pchar*)&str_stat_acc);
            break;
        case (REQUEST_SPDEF + 2): // evasion
            pstrcpy(buffer, (pchar*)&str_stat_evn);
            break;
        case (REQUEST_SPDEF + 3): // crit
            pstrcpy(buffer, (pchar*)&str_stat_crit);
            break;
    };
}

void buffer_write_status_name(pchar* buffer, u8 status_id)
{
    switch (status_id) {
        case AILMENT_PARALYZE:
            pstrcpy(buffer, (pchar*)&str_status_paralyze);
            break;
        case AILMENT_BURN:
            pstrcpy(buffer, (pchar*)&str_status_burn);
            break;
        case AILMENT_POISON:
            pstrcpy(buffer, (pchar*)&str_status_poison);
            break;
        case AILMENT_SLEEP:
            pstrcpy(buffer, (pchar*)&str_status_sleep);
            break;
        case AILMENT_FREEZE:
            pstrcpy(buffer, (pchar*)&str_status_frozen);
            break;
        case AILMENT_BAD_POISON:
            pstrcpy(buffer, (pchar*)&str_status_bpoison);
            break;
        case AILMENT_CONFUSION:
            pstrcpy(buffer, (pchar*)&str_status_confuse);
            break;
        case AILMENT_INFACTUATION:
            pstrcpy(buffer, (pchar*)&str_status_infactuation);
            break;
    };
}


void fdecoder_battle(pchar* buffer, u8 bank, u16 moveId, u16 move_effect_id)
{
    u16 len = pstrlen(buffer);
    pchar* result = (pchar*)malloc((len < 50) ? 100 : len * 2);
    u16 i, result_index;
    for (i = 0, result_index = 0; ((i < len) || (buffer[i] > 0xFE)); i++) {
        if (buffer[i] == 0xFD) {
            i++;
            switch (buffer[i]) {
                case 0xE:
                    // buffer Attacking Pokemon name
                    buffer_write_pkmn_nick(&(result[result_index]), bank);
                    result_index = pstrlen(result);
                    break;
                case 0xF:
                    // buffer move name
                    buffer_write_move_name(&(result[result_index]), moveId);
                    result_index = pstrlen(result);
                    break;
                case 0x10:
                    // buffer move effect name
                    buffer_write_move_name(&(result[result_index]), move_effect_id);
                    result_index = pstrlen(result);
                    break;
                case 0x11:
                    // buffer Defending Pokemon name
                    buffer_write_pkmn_nick(&(result[result_index]), gPkmnBank[bank]->battleData.my_target);
                    result_index = pstrlen(result);
                    break;
                case 0x12:
                    // ability buff
                    buffer_write_ability_name(&result[result_index], BANK_ABILITY(bank));
                    result_index = pstrlen(result);
                    break;
                case 0x13:
                    // ability arbitrary
                    {
                        buffer_write_ability_name(&result[result_index], move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x14:
                    // type of current move
                    {
                        buffer_write_move_type(&result[result_index], moveId);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x15:
                    // stat name
                    {
                        buffer_write_stat_mod(&result[result_index], move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x16:
                    // status ailment name
                    {
                        buffer_write_status_name(&result[result_index], move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x17:
                    {
                    // Buffer the name of a general type
                        pstrcpy(&result[result_index], (const pchar*)PkmnTypeNames[move_effect_id]);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x18:
                    {
                    // buffer name of a weather
                        if (move_effect_id == MOVE_HAIL) {
                            pstrcpy(&result[result_index], (const pchar*)str_hail_w);
                        } else if (move_effect_id == MOVE_RAINDANCE) {
                            pstrcpy(&result[result_index], (const pchar*)str_rain_w);
                        } else {
                            pstrcpy(&result[result_index], (const pchar*)str_sandstorm_w);
                        }
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x19:
                    {
                        // the foe prefix
                        if (SIDE_OF(bank) == 0) {
                            pstrcpy(&result[result_index], (const pchar*)str_thefoe_p);
                        } else {
                            pstrcpy(&result[result_index], (const pchar*)str_thefoe);
                        }
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x1A:
                    {
                        // foe prefix
                        if (SIDE_OF(bank) == 0) break;
                        pstrcpy(&result[result_index], (const pchar*)str_nfoe);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x1B:
                    {
                        buffer_pkmn_nick_arbitrary(&result[result_index], bank, move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x1C:
                    {
                        buffer_write_bank_item(&(result[result_index]), move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x1D:
                    {
                        buffer_write_pkmn_nick(&(result[result_index]), move_effect_id);
                        result_index = pstrlen(result);
                        break;
                    }
                case 0x1E:
                    buffer_player_pkmn_nick_arbitrary(&result[result_index], moveId);
                    result_index = pstrlen(result);
                    break;
                case 0x1F:
                buffer_write_move_name(&(result[result_index]), move_effect_id);
                result_index = pstrlen(result);
                    break;
                default:
                    {

                    result[result_index] = buffer[i - 1];
                    result[result_index + 1] = buffer[i];
                    result_index += 2;
                    }
                    break;
            };
        } else {
            result[result_index] = buffer[i];
            result_index++;
        }
    }

    fdecoder(string_buffer, result);
    free(result);
}
