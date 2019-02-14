#include <pokeagb/pokeagb.h>
#include "battle_obj_sliding.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../../../generated/images/battle_terrains/grass/grass_bg.h"
#include "../../../generated/images/battle_terrains/grass/grass_entry.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../../pokemon/pokemon.h"

extern void CpuFastSet(void*, void*, u32);
/* Standard BG configuration for battle start */
const struct BgConfig bg_config_data[4] = {
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 0,
        .palette = 0,
        .size = 0,
        .map_base = 31,
        .character_base = 3,
        .bgid = 0,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 1,
        .palette = 0,
        .size = 0,
        .map_base = 30,
        .character_base = 2,
        .bgid = 1,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 2,
        .palette = 0,
        .size = 0,
        .map_base = 29,
        .character_base = 1,
        .bgid = 2,
    },
    {
        .padding = 0,
        .b_padding = 0,
        .priority = 3,
        .palette = 0,
        .size = 1,
        .map_base = 28,
        .character_base = 0,
        .bgid = 3,
    },
};


void pick_and_load_battle_bgs()
{
    /* TODO Make this change based on where you are. */
    // copy image BG background
    void* char_base = (void *)0x6000000;
    void* map_base = (void *)0x600E000;
    lz77UnCompVram((void *)grass_bgTiles, char_base);
    lz77UnCompVram((void *)grass_bgMap, map_base);

    // copy image BG entry image
    char_base = (void *)0x6008000;
    map_base = (void *)0x600F000;
    lz77UnCompVram((void *)grass_entryTiles, char_base);
    lz77UnCompVram((void *)grass_entryMap, map_base);

    // copy textbox image
    char_base = (void *)0x600C000;
    map_base = (void *)0x600F800;
    lz77UnCompVram((void *)bboxTiles, char_base);

    DMA3COPY(battle_textboxMap, map_base, sizeof(battle_textboxMap));

    // write palettes
    gpu_pal_apply_compressed((void *)grass_bgPal, 0, 64);
    gpu_pal_apply((void*)grass_entryPal, 16 * 4, 32);
    gpu_pal_apply((void*)bboxPal, 16 * 5, 32);
}

void pick_and_load_battle_bgs_no_entry(const void* textbox_map)
{
    /* TODO Make this change based on where you are. */
    // copy image BG background
    void* char_base = (void *)0x6000000;
    void* map_base = (void *)0x600E000;
    lz77UnCompVram((void *)grass_bgTiles, char_base);
    lz77UnCompVram((void *)grass_bgMap, map_base);

    // copy textbox image
    char_base = (void *)0x600C000;
    map_base = (void *)0x600F800;
    lz77UnCompVram((void *)bboxTiles, char_base);
    CpuFastSet((void*)textbox_map, (void*)map_base, CPUModeFS(0x800, CPUFSCPY));

    // write palettes
    gpu_pal_apply_compressed((void *)grass_bgPal, 0, 64);
    gpu_pal_apply((void*)bboxPal, 16 * 5, 32);
}

struct Pokemon* pick_first_usable_pokemon(struct Pokemon* p, u8 party_size)
{
    for (u8 i = 0; i < party_size; i++) {
        u16 species = pokemon_getattr(&p[i], REQUEST_SPECIES, NULL);
        bool is_egg = pokemon_getattr(&p[i], REQUEST_IS_EGG, NULL);
        u16 current_hp = pokemon_getattr(&p[i], REQUEST_CURRENT_HP, NULL);
        dprintf("SELECTING SPECIES. SPECIES ID IS %d\n", species);
        dprintf("SELECTING SPECIES. SPECIES IS EGG? %d\n", is_egg);
        dprintf("SELECTING SPECIES. CURRENTHP? %d\n", current_hp);
        // valid if it's a valid species, isn't an egg, and is alive.
        if ((species < SPECIES_MAX) && (species > 0) &&
         (!is_egg) && (current_hp > 0)) {
            return (&p[i]);
        }
    }
    return NULL; // failed to find an active battler. Maybe the battle should whiteout here.
}

/* Spawn battler gSprites. Set active banks based on battle type */
extern void create_sprites_wild_battlers(void);
void battle_scene_intialize_sprites()
{
    BattleEntryWindows->player_trainer_objid = 0x3F;
    BattleEntryWindows->partner_trainer_objid = 0x3F;
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
            // initialize gPkmnBank pkmn name and pointer for player
            gPkmnBank[PLAYER_SINGLES_BANK]->this_pkmn = pick_first_usable_pokemon(&party_player[0], 6);
            memcpy(gPkmnBank[PLAYER_SINGLES_BANK]->battleData.name, gPkmnBank[PLAYER_SINGLES_BANK]->this_pkmn->box.nick, sizeof(party_player[0].box.nick));
            gPkmnBank[PLAYER_SINGLES_BANK]->battleData.name[11] = 0xFF;
            gPkmnBank[PLAYER_SINGLES_BANK]->battleData.is_active_bank = true;

            // same for opponent
            gPkmnBank[OPPONENT_SINGLES_BANK]->this_pkmn = pick_first_usable_pokemon(&party_opponent[0], 6);
            memcpy(gPkmnBank[OPPONENT_SINGLES_BANK]->battleData.name, gPkmnBank[OPPONENT_SINGLES_BANK]->this_pkmn->box.nick, sizeof(party_player[0].box.nick));
            gPkmnBank[OPPONENT_SINGLES_BANK]->battleData.name[11] = 0xFF;
            gPkmnBank[OPPONENT_SINGLES_BANK]->battleData.is_active_bank = true;
            dprintf("battle scene initialize sprites right before creating sprites wild battlers\n");
            create_sprites_wild_battlers();
            dprintf("battle scene initialize after\n");
            break;
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            dprintf("FAILED to select a valid battle mode.\n");
            break;
    };

}


void battlers_move_into_scene()
{
    switch (battle_type_flag) {
        case BATTLE_MODE_WILD:
            // player
            if (BattleEntryWindows->player_trainer_objid != 0x3F)
                gSprites[BattleEntryWindows->player_trainer_objid].pos1.x -= 3;
            // wild mon
             if (gPkmnBank[OPPONENT_SINGLES_BANK]->objid != 0x3F)
                 gSprites[gPkmnBank[OPPONENT_SINGLES_BANK]->objid].pos1.x += 3;
            break;
        case BATTLE_MODE_WILD_DOUBLE:
        case BATTLE_MODE_TRAINER:
        case BATTLE_MODE_TRAINER_DOUBLE:
        case BATTLE_MODE_PARTNER:
        default:
            dprintf("FAILED to select a valid battle mode.\n");
            break;
    };
}


extern void PlayerThrowBallAndMoveScene(struct Sprite*);
void player_sendout_animation_singles()
{
    gSprites[BattleEntryWindows->player_trainer_objid].animNum++;
    gSprites[BattleEntryWindows->player_trainer_objid].callback = PlayerThrowBallAndMoveScene;
    gSprites[BattleEntryWindows->player_trainer_objid].data[2] = PLAYER_SINGLES_BANK;
    gBattleAnimationStatus = 1;
}
