gritargs="-gB4 -gzl -pzl -pe16 -gu8 -pu8 -ftc -fh -pS -S "
gritargsshiny="-g! -pzl -pe16 -pu8 -ftc -fh -pS -S "
frontgfx = '#include <pokeagb/pokeagb.h>\n#include '
backgfx = "#include <pokeagb/pokeagb.h>"
frontgfx = "#include <pokeagb/pokeagb.h>"
normalPals = "#include <pokeagb/pokeagb.h>"
shinyPals = "#include <pokeagb/pokeagb.h>"
ending="PAL"
ending2="SPAL"
for file in *frontNormal.png; do 
    if [ -f "$file" ]; then
		this_file=$(echo "$file" | cut -f 1 -d '.' | sed 's\-frontNormal\\g')
		echo output is $this_file$ending
		grit $this_file-frontNormal.png $this_file-backNormal.png $gritargs $this_file$ending
		grit $this_file-frontShiny.png $this_file-backShiny.png $gritargsshiny $this_file$ending2
		echo this file is $this_file.png
    fi
done

rm -f *backShiny.h
rm -f *backShiny.c
rm -f *frontShiny.c
rm -f *frontShiny.h

mkdir -p ../src/pokemon/gfx
for file in *.c; do 
    if [ -f "$file" ]; then
		this_file=$(echo "$file" | cut -f 1 -d '.')
		mv $this_file.h "../src/pokemon/gfx/"$this_file.h
		mv $this_file.c "../src/pokemon/gfx/"$this_file.c
		echo transferred $file.h and $file.c
    fi
done
