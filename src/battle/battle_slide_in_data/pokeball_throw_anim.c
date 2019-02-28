#include <pokeagb/pokeagb.h>
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"


extern u8 spawn_pkmn_backsprite_obj_slot(u8 bank, u16 tag);
extern void dprintf(const char * str, ...);


static const struct RotscaleFrame shrink_grow[] = {
    {-200, -200, 0, 1, 0},
    {20, 20, 0, 10, 0},
    {0x7FFF, 0, 0, 0, 0}
};

static const struct RotscaleFrame* shrink_grow_ptr[] = {shrink_grow};

void PokemonCaptureIntoPokeballSCB(struct Sprite* spr)
{
    // handle sprite upwards movement TODO
    switch (spr->data[1]) {
        case 0:
            {
                u8 pal_slot = spr->final_oam.palette_num;
                u32 pal_fade = ((1 << (pal_slot + 16)));
                BeginNormalPaletteFade(pal_fade, 10, 0x10, 0, 0x7ADF);
                REG_BLDCNT = (BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_LIGHTEN | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST);
                spr->data[0] = 0;
                spr->data[1]++;
                break;
            }
        case 1:
            // TODO Move up
            spr->data[2]++;
            if (spr->data[2] % 3)
                return;
            if (spr->data[0] >= 10) {
                REG_BLDCNT = 0;
                spr->callback = oac_nullsub;
                spr->invisible = true;
                return;
            }
            REG_BLDY = spr->data[0];
            spr->data[0]++;
            break;
    };
}

void pkmn_sendingout_objc(struct Sprite* spr)
{
    /* Send out gSprites grow from bottom up */
    if (spr->data[5] < spr->pos1.y) {
        if ((spr->pos1.y - 6) < spr->data[5]) {
            spr->pos1.y = spr->data[5];
        } else {
            spr->pos1.y -= 6;
        }
    }
   spr->data[2]++;
    if (spr->data[2] % spr->data[1])
        return;
    if (!spr->data[0]) {
        REG_BLDCNT = 0;
        spr->callback = oac_nullsub;
        spr->final_oam.affine_mode = 1;
        gBattleAnimationStatus = 0;
        return;
    }
    REG_BLDY = spr->data[0];
    spr->data[0]--;
}

u8 send_out_backsprite(u8 bank)
{
    // send out pokemon's backsprite based on bank
    affine_reset_all();
    u8 objid = spawn_pkmn_backsprite_obj_slot(bank, 0x810);
    gSprites[objid].rotscale_table = shrink_grow_ptr;
    gSprites[objid].final_oam.affine_mode = 1;
    gSprites[objid].callback = pkmn_sendingout_objc;
    gSprites[objid].data[0] = 10;
    gSprites[objid].data[1] = 3; // delay
    gSprites[objid].data[5] = gSprites[objid].pos1.y;
    gSprites[objid].pos1.y += 64;
    gPkmnBank[bank]->objid = objid;
    u8 pal_slot = gSprites[objid].final_oam.palette_num;
    u32 pal_fade = ((1 << (pal_slot + 16)));

    // flash white for 4 frames
    BeginNormalPaletteFade(pal_fade , 10, 0x10, 0x0, 0x7ADF);
    REG_BLDCNT = (BLDCNT_BG1_SRC | BLDCNT_BG2_SRC | BLDCNT_BG3_SRC | BLDCNT_LIGHTEN | BLDCNT_BG1_DST | BLDCNT_BG2_DST | BLDCNT_BG3_DST);
    return objid;
}

static const struct RotscaleFrame spin[] = {
    {0, 0, 0x00, 8, 0x0}, // 8 frame wait
    {0, 0, 10, 3, 0x0}, // 10, 3 frames
    {0, 0, 20, 4, 0x0}, // 20, 4 frames
    {0, 0, 30, 255, 0x0}, // 30, 255 frame
    {0x7FFF, 0x0, 0x0, 0x0, 0x0} // end
};
static const struct RotscaleFrame (*spin_ptr)[] = (const struct RotscaleFrame(*)[])&spin;
void pokeball_player_throw_arc(struct Sprite* spr)
{
    if (spr->data[6] < 170) {
        if (spr->data[6] < 80) {
            spr->data[6] += 2;
            if (spr->data[6] % 3)
                spr->pos1.x += 1;
            spr->pos1.y = (Sin(spr->data[6], -30)) + 100;
        } else if (spr->data[6] < 130) {
            spr->data[6] += 3;
            if (spr->data[6] % 2)
                spr->pos1.x += 1;
            spr->pos1.y = (Sin(spr->data[6], -30)) + 100;
        } else {
            if (spr->data[6] % 2)
                spr->pos1.x += 1;
            spr->data[6] += 5;
            spr->pos1.y = (Sin(spr->data[6], -30)) + 100;

        }

    } else {
        spr->final_oam.affine_mode = 0;
        send_out_backsprite(spr->data[0]);
        obj_free(spr);
    }

}


void make_spinning_pokeball(s16 x, s16 y, u8 bank)
{
    // get pokeball index in table
    struct Pokemon* p = gPkmnBank[bank]->this_pkmn;
    u16 ball_id = pokemon_getattr(p, REQUEST_POKEBALL, NULL);
    ball_id = ball_number_to_ball_processing_index(ball_id);
    LoadCompressedSpriteSheetUsingHeap(&ball_tiles[ball_id]);
    LoadCompressedSpritePaletteUsingHeap(&ball_palettes[ball_id]);
    u8 objid = template_instanciate_forward_search((struct Template*)0x82606F4, x, y, 0);
    gSprites[objid].callback = pokeball_player_throw_arc;
    gSprites[objid].data[0] = bank;

    gSprites[objid].data[6] = 0x25; // Delay timer
    gSprites[objid].rotscale_table = (const struct RotscaleFrame(**)[])&spin_ptr;
    gSprites[objid].final_oam.affine_mode = 1;
}
