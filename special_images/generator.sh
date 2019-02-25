grit battle_textbox.png battle_textbox_action_select.png battle_textbox_move_select.png battle_textbox_stat.png -fh -ftc -g -gS -gzl -gB4 -gu8 -m -mp5 -mu8 -p -pe16 -pS -pu8 -ah256 -aw256 -O bbox
cp *.h ../src/battle/battle_text
cp *.c ../src/battle/battle_text
cp battle_textbox_gfx.h btg.d
rm -rf *.h
rm -rf *.c
mv btg.d battle_textbox_gfx.h 