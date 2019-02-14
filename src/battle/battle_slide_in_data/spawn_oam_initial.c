#include <pokeagb/pokeagb.h>
#include "battle_obj_sliding.h"
#include "../battle_data/pkmn_bank.h"
#include "../../global.h"

// back sprites
#include "../../../generated/images/backsprites/female_player.h"
#include "../../../generated/images/backsprites/male_player.h"
#include "../../../generated/images/backsprites/may.h"
#include "../../../generated/images/backsprites/oldman.h"
#include "../../../generated/images/backsprites/brendon.h"
#include "../../../generated/images/backsprites/poke_dude.h"

// unique battle tags
#define OPP1_BTAG 0x100
#define PLAYER_BTAG 0x300

// initial positions before starting to apply sliding
#define PLAYER_X_POS_SLIDE -176
#define OPP1_X_POS_SLIDE -80

extern const struct Frame (**nullframe)[];
extern const struct RotscaleFrame (**nullrsf)[];

const struct OamData opp_oam = {
                                .y = 0,
                                .affine_mode = 1,
                                .obj_mode = 0,
                                .mosaic = 0,
                                .bpp = 0,
                                .shape = 0,
                                .x = 0,
                                .matrix_num = 0,
                                .size = 3, //64x64
                                .tile_num = 0,
                                .priority = 3, // above BG background, below entry layer
                                .palette_num = 0,
                                .affine_param = 0
};

bool is_shiny(struct Pokemon* p)
{
    u32 tid = pokemon_getattr(p, REQUEST_TID, NULL);
    u32 pid = pokemon_getattr(p, REQUEST_PID, NULL);

    /* the weird shiny formula */
    return ((tid >> 16) ^ tid ^ (pid >> 16) ^ pid) <= 7;
}

void* get_pal_pkmn(struct Pokemon* p, u16 species)
{
    if(!is_shiny(p))
        return (void*)gMonSpritePalTable[species].data;
    else
        return (void*)pokemon_palette_shiny[species].data;
}

u8 spawn_pkmn_obj_slot(u8 bank, u16 tag)
{
    struct Pokemon* pkmn = gPkmnBank[bank]->this_pkmn;
    u16 species = pokemon_getattr(pkmn, REQUEST_SPECIES, NULL);
    void* pkmn_pal = get_pal_pkmn(pkmn, species);
    void* pkmn_gfx = (void*)gMonStillFrontPicTable[species].data;

    struct SpritePalette pkmn_sprite_pal = {pkmn_pal, tag};
    struct CompressedSpriteSheet pkmn_sprite_gfx = {pkmn_gfx, 2048, tag};
    struct Template pkmn_temp = {tag, tag, &opp_oam, nullframe, &pkmn_sprite_gfx, nullrsf, (SpriteCallback)oac_nullsub};

    gpu_tile_obj_decompress_alloc_tag_and_upload(&pkmn_sprite_gfx);
    gpu_pal_decompress_alloc_tag_and_upload(&pkmn_sprite_pal);
    return template_instanciate_forward_search(&pkmn_temp, OPP1_X_POS_SLIDE, 54, 0);
}

u8 spawn_pkmn_backsprite_obj_slot(u8 bank, u16 tag)
{
    struct Pokemon* pkmn = gPkmnBank[bank]->this_pkmn;

    u16 species = pokemon_getattr(pkmn, REQUEST_SPECIES, NULL);
    void* pkmn_pal = get_pal_pkmn(pkmn, species);
    void* pkmn_gfx = (void*)gMonBackPicTable[species].data;

    struct SpritePalette pkmn_sprite_pal = {pkmn_pal, tag};
    struct CompressedSpriteSheet pkmn_sprite_gfx = {pkmn_gfx, 2048, tag};
    struct Template pkmn_temp = {tag, tag, &opp_oam, nullframe, &pkmn_sprite_gfx, nullrsf, (SpriteCallback)oac_nullsub};

    gpu_tile_obj_decompress_alloc_tag_and_upload(&pkmn_sprite_gfx);
    gpu_pal_decompress_alloc_tag_and_upload(&pkmn_sprite_pal);
    u8 species_y = pokemon_player_xy_table[species] >> 8;
    return template_instanciate_forward_search(&pkmn_temp, 64, 80 + species_y, 0);
}

static struct Frame trainer_slide_in[] = {
    {0,0},
    {0xFFFF, 0},
};

static struct Frame trainer_throw_out_frames[] = {
    {0, 0},
    {64, 23},
    {128, 7},
    {192, 6},
    {256, 6},
    {0xFFFF, 0},
};
static struct Frame* trainer_frame_table [2] = {
    trainer_slide_in,
    trainer_throw_out_frames,
};


u8 spawn_backsprite_npc(u8 sprite_id, u16 tag)
{
    void* player_pal;
    void* player_gfx;

    // use graphic based on sprite id override, otherwise use gender
    if (sprite_id < 0xFF) {
        switch (sprite_id) {
            case 0:
                player_pal = (void*)female_playerPal;
                player_gfx = (void*)female_playerTiles;
                break;
            case 1:
                player_pal = (void*)male_playerPal;
                player_gfx = (void*)male_playerTiles;
                break;
            case 2:
                player_pal = (void*)mayPal;
                player_gfx = (void*)mayTiles;
                break;
            case 3:
                player_pal = (void*)brendonPal;
                player_gfx = (void*)brendonTiles;
                break;
            case 4:
                player_pal = (void*)oldmanPal;
                player_gfx = (void*)oldmanTiles;
                break;
            default:
                player_pal = (void*)poke_dudePal;
                player_gfx = (void*)poke_dudeTiles;
                break;
        };
    } else {
        // gender based player character
        if (gPlayerAvatar.gender) {
            player_pal = (void*)female_playerPal;
            player_gfx = (void*)female_playerTiles;
        } else {
            player_pal = (void*)male_playerPal;
            player_gfx = (void*)male_playerTiles;
        }
    }

    struct SpritePalette player_sprite_pal = {player_pal, tag};
    struct CompressedSpriteSheet player_sprite_gfx = {player_gfx, 2048 * 5, tag};
    struct Template player_temp = {tag, tag, &opp_oam, trainer_frame_table, &player_sprite_gfx, nullrsf, (SpriteCallback)oac_nullsub};

    gpu_tile_obj_decompress_alloc_tag_and_upload(&player_sprite_gfx);
    gpu_pal_decompress_alloc_tag_and_upload(&player_sprite_pal);
    u8 objid = template_instanciate_forward_search(&player_temp, PLAYER_X_POS_SLIDE, 81, 0);
    gSprites[objid].final_oam.obj_mode = 1;
    return objid;
}

// this creates the opponent battler & player backsprite
void create_sprites_wild_battlers()
{
    // wild mon first
    u8 objid = spawn_pkmn_obj_slot(OPPONENT_SINGLES_BANK, OPP1_BTAG);
    gPkmnBank[OPPONENT_SINGLES_BANK]->objid = objid;

    // gender based player character
        if (gPlayerAvatar.gender) {
            objid = spawn_backsprite_npc(0, PLAYER_BTAG);
        } else {
            objid = spawn_backsprite_npc(1, PLAYER_BTAG);
        }
    if (BattleEntryWindows != NULL)
        BattleEntryWindows->player_trainer_objid = objid;
}


void create_sprites_battle_mons_wild()
{
    gPkmnBank[OPPONENT_SINGLES_BANK]->objid = spawn_pkmn_obj_slot(OPPONENT_SINGLES_BANK, OPP1_BTAG);
    gPkmnBank[PLAYER_SINGLES_BANK]->objid = spawn_pkmn_backsprite_obj_slot(PLAYER_SINGLES_BANK, PLAYER_BTAG);
}


void free_battler_oams()
{
    for (u8 i = 0; i < BANK_MAX; i++) {
        if (gPkmnBank[i]->objid < 0x3F) {
            obj_free(&gSprites[gPkmnBank[i]->objid]);
            gPkmnBank[i]->objid = 0x3F;
        }
        for (u8 j = 0; j < 4; j++) {
            if (gPkmnBank[i]->objid_hpbox[j] < 0x3F) {
                obj_free(&gSprites[gPkmnBank[i]->objid_hpbox[j]]);
                gPkmnBank[i]->objid_hpbox[j] = 0x3F;
            }
        }
    }
}
