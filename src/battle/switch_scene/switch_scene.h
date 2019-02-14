#ifndef SWITCH_SCENE_H_
#define SWITCH_SCENE_H_

// tags
#define SLIDER_PAL_TAG 0xD740
#define SLIDER_GFX_TAG 0xD740
#define ICON_PAL_TAG 0xDAC0
#define ICON_GFX_TAG 0xD75A
#define CONFIRM_BOX_TAG 0x519

// positions
#define Y_POS_MID_ONE 38
#define Y_POS_MID_TWO 62
#define Y_POS_MID_THREE 87
#define Y_POS_MID_FOUR 110
#define CURSOR_SHIFT_POS 111
#define CURSOR_CANCEL_POS 125

// text palette related
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))
extern bool IsStatNatureNerved(u8 stat, struct Pokemon *pokemon);
extern bool IsStatNatureBoosted(u8 stat, struct Pokemon *pokemon);
#define STAT_COLOR(stat, pkmn) \
    (IsStatNatureBoosted(stat, pkmn) ? &switch_color_green : (IsStatNatureNerved(stat, pkmn) ? &switch_color_red : &switch_color))

// Text table indexes for strings
#define SWB_ABILITY 0
#define SWB_ITEM 1
#define SWB_ATK 2
#define SWB_DEF 3
#define SWB_SPA 4
#define SWB_SPD 5
#define SWB_SPE 6
#define SWB_MOVES 7
#define SWB_POW 8
#define SWB_ACC 9
#define SWB_PP 10
#define SWB_NAME 11
#define SWB_LVL 12
#define SWB_HP 13
#define SWB_MAX 13
#define SWM_LOG (gBattleMaster->switch_main.sd)


// text related declarations, see switch_text.c
extern const pchar str_no_item[];
extern const pchar str_invalid_num[];
extern u16 switch_text_pal[];
extern struct TextColor switch_color;
extern struct TextColor switch_color_bg;
extern struct TextColor switch_color_red;
extern struct TextColor switch_color_green;
extern struct TextboxTemplate switch_boxes[];


extern u8 load_dmg_type_icon(u8 type, s16 x, s16 y, u8 tag);
extern u8 load_small_dmg_category_icon(u8 category, s16 x, s16 y, u8 tag);
extern void VblankSPQ(void);
extern void C2SyncAll(void);
extern void oac_nullsub(struct Sprite* spr);
extern const struct OamData icon_oam;
extern const struct OamData slider_oam;
extern const struct OamData confirm_box_oam;
extern const struct OamData cursor_confirm_oam;
extern struct RotscaleFrame *switch_scale_table[];
extern struct RotscaleFrame *switch_scale_table_full[];

#endif /* SWITCH_SCENE_H_ */
