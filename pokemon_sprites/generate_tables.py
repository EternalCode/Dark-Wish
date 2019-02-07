#!/usr/bin/env python

from glob import glob
import os
import itertools
import hashlib
import subprocess
import sys
import math

# destination dir
dest_dir = "../src/pokemon/gfx_tables/"

order = ["question","horsea","seadra","kingdra","trapinch","vibrava","flygon","togepi","togetic",
        "togekiss","yungoos","gumshoos","bunnelby","diggersby","bounsweet","steenee","tsareena",
        "mareep","flaaffy","ampharos","combee","vespiquen","spinarak","ariados","joltik",
        "galvantula","dewpider","araquanid","zubat","golbat","crobat","yanma","yanmega","morelull",
        "shiinotic","vulpix","ninetales","growlithe","arcanine","pineco","forretress","nincada",
        "ninjask","shedinja","feebas","milotic","shellder","cloyster","slowpoke","slowbro",
        "slowking","abra","kadabra","alakazam","espurr","meowstic","cottonee","whimsicott",
        "petilil","lilligant","shroomish","breloom","swablu","altaria","murkrow","honchkrow",
        "cleffa","clefairy","clefable","riolu","lucario","machop","machoke","machamp","shinx",
        "luxio","luxray","litleo","pyroar","houndour","houndoom","wingull","pelipper","tentacool",
        "tentacruel","remoraid","octillery","inkay","malamar","dwebble","crustle","skrelp",
        "dragalge","trubbish","garbodor","croagunk","toxicroak","skorupi","drapion","carnivine",
        "goomy","sliggoo","goodra","mudbray","mudsdale","gastly","haunter","gengar","duskull",
        "dusclops","dusknoir","noibat","noivern","dunsparce","mienfoo","mienshao","blitzle",
        "zebstrika","ponyta","rapidash","heracross","scyther","scizor","eevee","vaporeon","jolteon",
        "flareon","espeon","umbreon","leafeon","glaceon","sylveon","rockruff","lycanroc","geodude",
        "graveler","golem","anorith","armaldo","lileep","cradily","chinchou","lanturn","staryu",
        "starmie","spheal","sealeo","walrein","pawniard","bisharp","scraggy","scrafty","gligar",
        "gliscor","skiddo","gogoat","drampa","larvitar","pupitar","tyranitar","salandit","salazzle",
        "sandile","krokorok","krookodile","sigilyph","maractus","cacnea","cacturne","slugma",
        "magcargo","torkoal","turtonator","larvesta","volcarona","swirlix","slurpuff","comfey",
        "klefki","tynamo","eelektrik","eelektross","magnemite","magneton","magnezone","dedenne",
        "togedemaru","mimikyu","rotom","sandygast","palossand","litwick","lampent","chandelure",
        "dhelmise","honedge","doublade","aegislash","spiritomb","mawile","shuckle","girafarig",
        "munchlax","snorlax","pancham","pangoro","passimian","stufful","bewear","bouffalant",
        "kangaskhan","hawlucha","tropius","lapras","skarmory","sneasel","weavile","snover",
        "abomasnow","snorunt","glalie","froslass","bergmite","avalugg","cryogonal","porygon",
        "porygon2","porygonz","druddigon","golett","golurk","drilbur","excadrill","beldum","metang",
        "metagross","gible","gabite","garchomp","dratini","dragonair","dragonite","latias","latios",
        "heatran","deoxys","jirachi","darkrai"]

#-gB4 -gzl -pe16 -gu8 -pu8 -pzl -ftb -fh! -pS -S $base2"Pal" >$base$ext2
GRIT_FLAGS = ['-gB4', '-gzl', '-pe16', '-gu8', '-pu8', '-pzl', '-ftb', '-fh!', '-pS', '-S']
MKDIR_BUILD =["mkdir", "-p", "../src/pokemon"]
MOVE_DATA_TABLES =["mv", "*_data.bin", "../src/pokemon/gfx_tables"]

def run_command(cmd):
    try:
        subprocess.check_output(cmd)
    except subprocess.CalledProcessError as e:
        print(e.output.decode(), file=sys.stderr)
        sys.exit(1)

def main():
    # offset tracking vars
    front_sprite_table = "\t"
    back_sprite_table = "\t"
    palette_table = "\t"
    offset = 0

    # create bin files for pal, front and back sprites
    for file in order:
        print("grit processing for " + file)
        cmd = ["grit", file+"_back_pic.PNG", file+".png"] + GRIT_FLAGS + [file+"PAL"]
        run_command(cmd)

    # create the front sprite binary
    open("front_sprite_data.bin", 'a').close()
    counter = 0
    for mon in order:
        # append front sprite binary to frontsprite table at offset
        with open("front_sprite_data.bin", "r+b") as dest, open(mon+".img.bin", "rb") as src:
            print("front sprite processing for " + mon)
            dest.seek(offset)
            dest.write(src.read())
            # format table entry text for logging
            front_sprite_table = front_sprite_table + "{START_ADDR_FRONT_T + " + str(offset) + ", 0x800, " + str(counter) + "},\n\t"
            offset = offset + os.path.getsize(".//" + mon+".img.bin")
            # requires word alignment for read with LDR
            x = offset % 4
            if (x > 0):
                dest.write("0" * 4 - x)
            counter+=1

    # create the back sprite binary
    open("back_sprite_data.bin", 'a').close()
    counter = 0
    offset = 0
    for mon in order:
        # append back sprite binary to backsprite table at offset
        with open("back_sprite_data.bin", "r+b") as dest, open(mon+"_back_pic.img.bin", "rb") as src:
            print("back sprite processing for " + mon)
            dest.seek(offset)
            dest.write(src.read())
            # formate table entry for text logging
            back_sprite_table = back_sprite_table + "{START_ADDR_BACK_T + " + str(offset) + ", 0x800, " + str(counter) + "},\n\t"
            offset = offset + os.path.getsize(".//" + mon+"_back_pic.img.bin")
            # requires word alignment for read with LDR
            x = offset % 4
            if (x > 0):
                dest.write("0" * 4 - x)
            counter+=1

    # create the shared palette binary
    open("shared_pal_data.bin", 'a').close()
    counter = 0
    offset = 0
    for mon in order:
        # append back sprite binary to backsprite table at offset
        with open("shared_pal_data.bin", "r+b") as dest, open(mon+"PAL.pal.bin", "rb") as src:
            print("Palette processing for " + mon)
            dest.seek(offset)
            dest.write(src.read())
            # formate table entry for text logging
            palette_table = palette_table + "{START_ADDR_PAL_T + " + str(offset) + ", " + str(counter) + "},\n\t"
            offset = offset + os.path.getsize(".//" + mon+"PAL.pal.bin")
            # requires word alignment for read with LDR
            x = offset % 4
            if (x > 0):
                dest.write("0" * 4 - x)
            counter+=1

    # create front sprite table file
    run_command(MKDIR_BUILD)
    open(dest_dir + "pkmn_front_sprites.c", 'a').close()
    with open(dest_dir + "pkmn_front_sprites.c", "w+") as f:
        # includes
        f.write('#include <pokeagb/pokeagb.h>\n')
        f.write('#include "../pokemon.h"\n\n')
        #content
        f.write("struct CompressedSpriteSheet gMonStillFrontPicTable[" + str(len(order)) + "] = {\n")
        f.write(front_sprite_table)
        f.write("\n};\n")

    # create back sprite table file
    open(dest_dir + "pkmn_back_sprites.c", 'a').close()
    with open(dest_dir +"pkmn_back_sprites.c", "w+") as f:
        # includes
        f.write('#include <pokeagb/pokeagb.h>\n')
        f.write('#include "../pokemon.h"\n\n')
        # content
        f.write("struct CompressedSpriteSheet gMonBackPicTable[" + str(len(order)) + "] = {\n")
        f.write(back_sprite_table)
        f.write("\n};\n")

    # create palette sprite table file
    open(dest_dir + "pkmn_sprite_pals.c", 'a').close()
    with open(dest_dir + "pkmn_sprite_pals.c", "w+") as f:
        # includes
        f.write('#include <pokeagb/pokeagb.h>\n')
        f.write('#include "../pokemon.h"\n\n')
        f.write("struct SpritePalette gMonSpritePalTable[" + str(len(order)) + "] = {\n")
        #content
        f.write(palette_table)
        f.write("\n};\n")

    # moving files
    run_command(MOVE_DATA_TABLES)

    #clean cwd
    run_command(["rm", "-f", "*.bin"])


if __name__ == '__main__':
    main()
