#ifndef DEXNAV_GUI_H_
#define DEXNAV_GUI_H_

/* GUI Text related */
extern struct TextboxTemplate dexnavBoxes[];

/* GUI BG template */
extern const struct BgConfig bg_config_dexnav_gui[4];

/* cursor and pokeicon oam */
extern const struct OamData icon_oam;
extern const struct OamData DnavCursorOAM;
// cursor positions for water
extern const u16 cursor_positions2[];
// positions for grass
extern const u16 cursor_positions1[];

#endif /* DEXNAV_GUI_H_ */
