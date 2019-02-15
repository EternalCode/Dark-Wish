#include <pokeagb/pokeagb.h>
#include "battle_data/pkmn_bank.h"
#include "battle_data/pkmn_bank_stats.h"
#include "../pokemon/pokemon.h"

extern void PKMNAilmentToBank(u8 bank, u8 ailment);
extern u8 BankAilmentToPKMN(u8 bank);
extern u8 PokemonGetAbility(struct Pokemon* p);
extern void ShowStatusAilmentGraphic(u8 bank, enum Effect status);
extern const u8 gPlayerAbility;
extern const u8 gOpponentAbility;
extern const bool USE_TESTS;

void UpdatePKMNBank(u8 bank, struct SwitchingFlagsToPass* flags)
{
    // base stats
    u16 species = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPECIES, NULL);
    memcpy(gPkmnBank[bank]->battleData.name, gPkmnBank[bank]->this_pkmn->box.nick, sizeof(party_player[0].box.nick));
    gPkmnBank[bank]->battleData.name[11] = 0xFF;
    gPkmnBank[bank]->battleData.is_active_bank = true;

    gPkmnBank[bank]->battleData.weight = gPokemonWeight[species] / 10;
    gPkmnBank[bank]->battleData.species = species;
    gPkmnBank[bank]->battleData.gender = pokemon_get_gender(gPkmnBank[bank]->this_pkmn);
    gPkmnBank[bank]->battleData.current_hp = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_CURRENT_HP, NULL);;
    gPkmnBank[bank]->battleData.total_hp = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_TOTAL_HP, NULL);;

    if (USE_TESTS) {
        if (SIDE_OF(bank)) {
            gPkmnBank[bank]->battleData.ability = gOpponentAbility;
        } else {
            gPkmnBank[bank]->battleData.ability = gPlayerAbility;
        }
    } else {
        PokemonGetAbility(gPkmnBank[bank]->this_pkmn);
    }

    gPkmnBank[bank]->battleData.item = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_HELD_ITEM, NULL);
    gPkmnBank[bank]->battleData.level = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_LEVEL, NULL);
    gPkmnBank[bank]->battleData.poke_ball = 0;
    gPkmnBank[bank]->battleData.type[0] = gBaseStats[species].type1;
    gPkmnBank[bank]->battleData.type[1] = gBaseStats[species].type2;
    // if the pkmn's typing is the same af the first, the second type should be none
    if (gPkmnBank[bank]->battleData.type[1] == gPkmnBank[bank]->battleData.type[0])
            gPkmnBank[bank]->battleData.type[1] = TYPE_NONE;
    gPkmnBank[bank]->battleData.type[2] = TYPE_NONE;

    // pp and moves
    for (u8 i = 0; i < 4; i++) {
        gPkmnBank[bank]->battleData.bmoves[i] = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_MOVE1 + i, NULL);
        if (gPkmnBank[bank]->battleData.bmoves[i])
            gPkmnBank[bank]->battleData.move_pp[i] = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_PP1 + i, NULL);
        else
            gPkmnBank[bank]->battleData.move_pp[i] = 0;
    }

    // raw base stats
    gPkmnBank[bank]->battleData.attack_raw = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_ATK, NULL);
    gPkmnBank[bank]->battleData.defense_raw = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_DEF, NULL);
    gPkmnBank[bank]->battleData.speed_raw = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPD, NULL);
    gPkmnBank[bank]->battleData.sp_atk_raw = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPATK, NULL);
    gPkmnBank[bank]->battleData.sp_def_raw = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPDEF, NULL);

    // pokemon IVs
    gPkmnBank[bank]->battleData.hp_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_HP_IV, NULL);
    gPkmnBank[bank]->battleData.attack_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_ATK_IV, NULL);
    gPkmnBank[bank]->battleData.defense_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_DEF_IV, NULL);
    gPkmnBank[bank]->battleData.speed_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPD_IV, NULL);
    gPkmnBank[bank]->battleData.sp_atk_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPATK_IV, NULL);
    gPkmnBank[bank]->battleData.sp_def_iv = pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_SPDEF_IV, NULL);
    gPkmnBank[bank]->battleData.will_move = true;

    // stat boosts clear
    if (!flags->pass_stats) {
        gPkmnBank[bank]->battleData.attack = 0;
        gPkmnBank[bank]->battleData.defense = 0;
        gPkmnBank[bank]->battleData.speed = 0;
        gPkmnBank[bank]->battleData.sp_atk = 0;
        gPkmnBank[bank]->battleData.sp_def = 0;
        gPkmnBank[bank]->battleData.accuracy = 0;
        gPkmnBank[bank]->battleData.evasion = 0;
        gPkmnBank[bank]->battleData.crit_mod = 0;
    }

    // user actions should always be cleared
    gPkmnBank[bank]->battleData.isRunning = 0;
    gPkmnBank[bank]->battleData.using_item = 0;
    gPkmnBank[bank]->battleData.isSwitching = 0;
    gPkmnBank[bank]->battleData.skip_move_select = 0;
    gPkmnBank[bank]->battleData.first_turn = 1;

    // attack history clear
    if (!flags->pass_atk_history) {
        gPkmnBank[bank]->battleData.my_target = 0xFF;
        gPkmnBank[bank]->battleData.last_move = 0;
        gPkmnBank[bank]->battleData.current_move = 0;
        gPkmnBank[bank]->battleData.last_damage = 0;
        gPkmnBank[bank]->battleData.last_attacked_by = 0xFF;
        gPkmnBank[bank]->battleData.last_used_item = 0;
        gPkmnBank[bank]->battleData.ate_berry = 0;
    }

    // volatile status clear
    if (!flags->pass_status) {
        gPkmnBank[bank]->battleData.status = 0;
        gPkmnBank[bank]->battleData.confusion_turns = 0;
        gPkmnBank[bank]->battleData.status_turns = 0;
        gPkmnBank[bank]->battleData.substitute_health = 0;
        gPkmnBank[bank]->battleData.v_status = 0;
        gPkmnBank[bank]->battleData.v_status2 = 0;
        gPkmnBank[bank]->battleData.is_grounded = 0;
    }
    
    if (!flags->pass_disables) {

    }

    PKMNAilmentToBank(bank, pokemon_getattr(gPkmnBank[bank]->this_pkmn, REQUEST_STATUS_AILMENT, NULL));
    ShowStatusAilmentGraphic(bank, gPkmnBank[bank]->battleData.status);
    gPkmnBank[bank]->battleData.illusion = 0;
    gPkmnBank[bank]->battleData.fainted = 0;

    gPkmnBank[bank]->battleData.stockpile_uses = 0;
    gPkmnBank[bank]->battleData.stockpile_def_boost = 0;
    gPkmnBank[bank]->battleData.stockpile_spdef_boost = 0;

    gPkmnBank[bank]->battleData.slot = GET_SLOT_FROM_PTR((SIDE_OF(bank) ? (u32)&party_opponent[0] : (u32)&party_player[0]), (u32)gPkmnBank[bank]->this_pkmn, sizeof(struct Pokemon));
}


void SyncBankToParty(u8 bank)
{
    struct Pokemon* p = SIDE_OF(bank) ? &party_opponent[gPkmnBank[bank]->battleData.slot] : &party_player[gPkmnBank[bank]->battleData.slot];
    u16 c_hp = gPkmnBank[bank]->battleData.current_hp;
    u32 ailment = BankAilmentToPKMN(bank);
    pokemon_setattr(p, REQUEST_CURRENT_HP, &c_hp);
    pokemon_setattr(p, REQUEST_STATUS_AILMENT, &ailment);
    for (u8 i = 0; i < 4; i++) {
        u8 pp = B_GET_MOVE_PP(bank, i);
        pokemon_setattr(p, REQUEST_PP1 + i, &pp);
    }
}


bool UpdateBankHitList(u8 bank_index)
{
    u16 move = CURRENT_MOVE(bank_index);
    u8 list[4] = {BANK_MAX, BANK_MAX, BANK_MAX, BANK_MAX};

    if (M_HITS_SELF(move)) {
        // Target is user
        list[0] = bank_index;
    } else if (M_HITS_ALLY_OR_SELF(move)) {
        // todo. The choice between ally and self.
        list[0] = bank_index;
    } else if (M_HITS_TARGET(move)) {
        // Target is selected Target
        list[0] = (bank_index ? 0 : 2);
    } else if (M_HITS_ALLY(move)) {
        // hits ally
        if (SIDE_OF(bank_index) == PLAYER_SIDE) {
            list[0] = bank_index ? 0 : 1;
        } else {
            list[0] = (bank_index < 2) ? 2 : 1;
        }
        // in singles hitting your ally does nothing.
        return false;
    } else if (M_HITS_ADJ(move)) {
        for (u8 i = 0; i < 4; i++) {
            list[i] = (i != bank_index) ? i : BANK_MAX;
        }
    } else if (M_HITS_FOE_SIDE(move)) {
        // Target is the foe side
        if (SIDE_OF(bank_index) == PLAYER_SIDE) {
            list[0] = 2;
            list[1] = 3;
        } else {
            list[0] = 0;
            list[1] = 1;
        }
    } else if (M_HITS_MY_SIDE(move)) {
        // Target is the user side
        if (SIDE_OF(bank_index) == PLAYER_SIDE) {
            list[0] = 0;
            list[1] = 1;
        } else {
            list[0] = 2;
            list[1] = 3;
        }
    } else if (M_HITS_ALL(move)) {
        // Target is everything
        for (u8 i = 0; i < 4; i++) {
            list[i] = i;
        }
    } else {
        // no target
        return false;
    }
    for (u8 i = 0; i < 4; i++) {
        gBattleMaster->bank_hit_list[i] = list[i];
    }

    return true;
}
