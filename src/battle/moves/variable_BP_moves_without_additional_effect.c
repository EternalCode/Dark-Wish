#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"

extern void dprintf(const char * str, ...);
extern bool QueueMessage(u16 move, u8 user, enum battle_string_ids id, u16 effect);
extern u8 GetMoveIndexBank(u16 moveId, u8 bank);
void set_status(u8 bank, enum StatusAilments status, u8 inflictor);
extern u16 RandRange(u16 min, u16 max);


void acrobatics_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_ITEM(user) == 0)
        B_MOVE_POWER(user) *= 2;
}


void crush_grip_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 power = ((B_CURRENT_HP(user) * 100) / TOTAL_HP(user));
    power = PERCENT(120, power);
    B_MOVE_POWER(user) = MAX(1, power);
}


void avalanche_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (gPkmnBank[user]->battleData.last_attacked_by == TARGET_OF(user)) {
        B_MOVE_POWER(user) *= 2;
    }
}


void assurance_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (gPkmnBank[TARGET_OF(user)]->battleData.last_damage != 0) {
        B_MOVE_POWER(user) *= 2;
    }
}


void payback_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (gPkmnBank[TARGET_OF(user)]->battleData.will_move == false) {
        B_MOVE_POWER(user) *= 2;
    }
}


void hex_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 defender = TARGET_OF(user);
    if (B_STATUS(defender))
        B_MOVE_POWER(user) *= 2;
}


void facade_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_STATUS(user))
        B_MOVE_POWER(user) *= 2;
}


void brine_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 defender = TARGET_OF(user);
    if ((B_CURRENT_HP(defender) * 2) <= TOTAL_HP(defender))
        B_MOVE_POWER(user) *= 2;
}


void reversal_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 current_hp = B_CURRENT_HP(user);
    u16 total_hp = TOTAL_HP(user);
    if((current_hp * 48) >= (total_hp * 33))
        B_MOVE_POWER(user) = 20;
    else if((current_hp * 48) >= (total_hp * 17))
        B_MOVE_POWER(user) = 40;
    else if((current_hp * 48) >= (total_hp * 10))
        B_MOVE_POWER(user) = 80;
    else if((current_hp * 48) >= (total_hp * 5))
        B_MOVE_POWER(user) = 100;
    else if((current_hp * 48) >= (total_hp * 2))
        B_MOVE_POWER(user) = 150;
    else
        B_MOVE_POWER(user) = 200;
}


void heavy_slam_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 user_weight = B_WEIGHT(user);
    u16 defender_weight = B_WEIGHT(TARGET_OF(user));
    if((defender_weight * 2) >= user_weight)
        B_MOVE_POWER(user) = 40;
    else if((defender_weight * 3) >= user_weight)
        B_MOVE_POWER(user) = 60;
    else if((defender_weight * 4) >= user_weight)
        B_MOVE_POWER(user) = 80;
    else if((defender_weight * 5) >= user_weight)
        B_MOVE_POWER(user) = 100;
    else
        B_MOVE_POWER(user) = 120;

}


void low_kick_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if(user != src) return;
    u16 defender_weight = B_WEIGHT(TARGET_OF(user));
    if(defender_weight >= 200)
        B_MOVE_POWER(user) = 120;
    else if(defender_weight >= 100)
        B_MOVE_POWER(user) = 100;
    else if(defender_weight >= 50)
        B_MOVE_POWER(user) = 80;
    else if(defender_weight >= 25)
        B_MOVE_POWER(user) = 60;
    else if(defender_weight >= 10)
        B_MOVE_POWER(user) = 40;
    else
        B_MOVE_POWER(user) = 20;
};


void stomping_tantrum_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (B_LAST_MOVE_FAILED(user)) {
        B_MOVE_POWER(user) *= 2;
    }
}


void venoshock_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 status = B_STATUS(TARGET_OF(user));
    if ((status == AILMENT_BAD_POISON) || (status == AILMENT_POISON)) {
        B_MOVE_POWER(user) *= 2;
    }
}


/* Echoed voice */
void echoed_voice_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // don't make a duplicate for echoed voice's counter
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (CURRENT_MOVE(i) == MOVE_ECHOEDVOICE) {
            acb->duration += 1;
            acb->data_ptr += 1;
            acb->data_ptr = MIN(acb->data_ptr, 5); // clamp at 5
            return true;
        }
    }
    return true;
}


void echoed_voice_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (!callback_exists((u32)echoed_voice_after_move)) {
        u8 id = AddCallback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)echoed_voice_after_move);
        CB_MASTER[id].data_ptr = 1;
    }
    u8 counter = CB_MASTER[id_by_func((u32)echoed_voice_after_move)].data_ptr;
    B_MOVE_POWER(user) = 40 * counter;
}

/* Fury Cutter */
void fury_cutter_after_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    // don't make a duplicate for echoed voice's counter
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (CURRENT_MOVE(i) == MOVE_FURYCUTTER) {
            acb->duration += 1;
            acb->data_ptr += 1;
            acb->data_ptr = MIN(acb->data_ptr, 5); // clamp at 5
            return true;
        }
    }
    return true;
}


void fury_cutter_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (!callback_exists((u32)fury_cutter_after_move)) {
        u8 id = AddCallback(CB_ON_AFTER_MOVE, 0, 0, user, (u32)fury_cutter_after_move);
        CB_MASTER[id].data_ptr = 1;
    }
    u8 counter = CB_MASTER[id_by_func((u32)fury_cutter_after_move)].data_ptr;
    B_MOVE_POWER(user) = 40 * counter;
}


/* Electro Ball */
void electro_ball_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 user_spe = B_SPEED_STAT(user);
    u16 target_spe = B_SPEED_STAT(TARGET_OF(user));
    u8 power = 40;
    if (user_spe >= target_spe) {
        power = 60;
    }
    if (user_spe >= (2 * target_spe)) {
        power = 80;
    }
    if (user_spe >= (3 * target_spe)) {
        power = 120;
    }
    if (user_spe >= (4 * target_spe)) {
        power = 150;
    }
    B_MOVE_POWER(user) = MAX(power, 40);
}


void trump_card_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u8 slot = GetMoveIndexBank(CURRENT_MOVE(user), user);
    u8 power;
    switch (B_GET_MOVE_PP(user, slot)) {
		case 0:
			power = 200;
			break;
		case 1:
			power = 80;
			break;
		case 2:
			power = 60;
			break;
		case 3:
			power = 50;
			break;
		default:
			power = 40;
			break;
		};
    B_MOVE_POWER(user) = power;
}


void water_spout_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    B_MOVE_POWER(user) = (B_CURRENT_HP(user) * 150) / TOTAL_HP(user);
}


void gyro_ball_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 user_spe = B_SPEED_STAT(user);
    u16 target_spe = B_SPEED_STAT(TARGET_OF(user));
    u16 power = MAX(25, ((25 * target_spe) / user_spe));
    B_MOVE_POWER(user) = MIN(150, power); // clamp 150 power
}


/* Wake up slap*/
u8 wake_up_slap_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_SLEEP))
        set_status(TARGET_OF(user), AILMENT_CURE, user);
    return true;
}

void wake_up_slap_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_SLEEP) || (BANK_ABILITY(TARGET_OF(user)) == ABILITY_COMATOSE))
        B_MOVE_POWER(user) *= 2;
}


/* Smelling Salts */
u8 smelling_salts_on_effect(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_PARALYZE))
        set_status(TARGET_OF(user), AILMENT_CURE, user);
    return true;
}

void smelling_salts_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if ((B_STATUS(TARGET_OF(user)) == AILMENT_PARALYZE))
            B_MOVE_POWER(user) *= 2;
}


/* Whirl pool and surf */
u8 whirlpool_on_tryhit_invul(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_DIVE)) {
        B_MOVE_ACCURACY(user) = 101;
        return false;
    }
    return true;
}

void whirlpool_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_DIVE))
        B_MOVE_POWER(user) *= 2;
}


/* Magnitude & Earthquake */
u8 magnitude_on_tryhit_invul(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_DIG)) {
        B_MOVE_ACCURACY(user) = 101;
        return false;
    }
    return true;
}

void magnitude_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    u8 i = RandRange(0, 101);
    u8 magnitude = 0;
    u8 power = 0;
	if (i < 5) {
		magnitude = 4;
		power = 10;
	} else if (i < 15) {
		magnitude = 5;
		power = 30;
	} else if (i < 35) {
		magnitude = 6;
		power = 50;
	} else if (i < 65) {
		magnitude = 7;
		power = 70;
	} else if (i < 85) {
		magnitude = 8;
		power = 90;
	} else if (i < 95) {
		magnitude = 9;
		power = 110;
	} else {
		magnitude = 10;
		power = 150;
	}
    B_MOVE_POWER(user) = power;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_DIG))
        B_MOVE_POWER(user) *= 2;
    QueueMessage(NULL, NULL, STRING_MAGNITUDE_AMOUNT, magnitude);
}


void earthquake_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_DIG))
        B_MOVE_POWER(user) *= 2;
}


void flail_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    u16 ratio = ((48 * B_CURRENT_HP(user)) / TOTAL_HP(user));
    u8 power;
    if (ratio < 2) {
        power = 200;
    } else if (ratio < 5) {
        power = 150;
    } else if (ratio < 10) {
        power = 100;
    } else if (ratio < 17) {
        power = 80;
    } else if (ratio < 33) {
        power = 40;
    } else {
        power = 20;
    }
    B_MOVE_POWER(user) = power;
}


// twister damage. Invulnerbility hitting is shared with skyuppercut
void twister_on_damage(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return true;
    if (HAS_VOLATILE(TARGET_OF(user), VOLATILE_SKYDROP) || HAS_VOLATILE(TARGET_OF(user), VOLATILE_FLYING) ||
        HAS_VOLATILE(TARGET_OF(user), VOLATILE_BOUNCE)) {
            B_MOVE_DMG(user) *= 2;
    }
}


// Triple kick
void triple_kick_on_base_power(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;
    B_MOVE_POWER(user) = (10 * gBattleMaster->b_moves[(user)].hit_counter);
    //dprintf("current power is %d\n", B_MOVE_POWER(user));
}


void stored_power_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    u8 boost_factor = 0;
    boost_factor += MAX(B_ATTACK_BUFF(user), 0);
    boost_factor += MAX(B_DEFENSE_BUFF(user), 0);
    boost_factor += MAX(B_SPEED_BUFF(user), 0);
    boost_factor += MAX(B_SPATTACK_BUFF(user), 0);
    boost_factor += MAX(B_SPDEFENSE_BUFF(user), 0);
    boost_factor += MAX(B_ACCURACY_BUFF(user), 0);
    boost_factor += MAX(B_EVASION_BUFF(user), 0);

    B_MOVE_POWER(user) = 20 + 20*(boost_factor);
}

void punishment_on_base_power_move(u8 user, u8 src, u16 move, struct anonymous_callback* acb)
{
    if (user != src) return;

    u8 defender = TARGET_OF(user);
    u8 boost_factor = 0;
    boost_factor += MAX(B_ATTACK_BUFF(defender), 0);
    boost_factor += MAX(B_DEFENSE_BUFF(defender), 0);
    boost_factor += MAX(B_SPEED_BUFF(defender), 0);
    boost_factor += MAX(B_SPATTACK_BUFF(defender), 0);
    boost_factor += MAX(B_SPDEFENSE_BUFF(defender), 0);
    boost_factor += MAX(B_ACCURACY_BUFF(defender), 0);
    boost_factor += MAX(B_EVASION_BUFF(defender), 0);

    B_MOVE_POWER(user) = 60 + 20*(boost_factor);
}
