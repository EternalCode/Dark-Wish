#include <pokeagb/pokeagb.h>
#include "../pokemon.h"

struct CompressedSpriteSheet gMonStillFrontPicTable[246] = {
	// question
	{START_ADDR_FRONT_T + 0, 0x800, 0},
	// horsea
	{START_ADDR_FRONT_T + 384, 0x800, 1},
	// seadra
	{START_ADDR_FRONT_T + 952, 0x800, 2},
	// kingdra
	{START_ADDR_FRONT_T + 1912, 0x800, 3},
	// trapinch
	{START_ADDR_FRONT_T + 2968, 0x800, 4},
	// vibrava
	{START_ADDR_FRONT_T + 3508, 0x800, 5},
	// flygon
	{START_ADDR_FRONT_T + 4388, 0x800, 6},
	// togepi
	{START_ADDR_FRONT_T + 5652, 0x800, 7},
	// togetic
	{START_ADDR_FRONT_T + 6120, 0x800, 8},
	// togekiss
	{START_ADDR_FRONT_T + 6748, 0x800, 9},
	// yungoos
	{START_ADDR_FRONT_T + 7528, 0x800, 10},
	// gumshoos
	{START_ADDR_FRONT_T + 8188, 0x800, 11},
	// bunnelby
	{START_ADDR_FRONT_T + 8936, 0x800, 12},
	// diggersby
	{START_ADDR_FRONT_T + 9680, 0x800, 13},
	// bounsweet
	{START_ADDR_FRONT_T + 10708, 0x800, 14},
	// steenee
	{START_ADDR_FRONT_T + 11236, 0x800, 15},
	// tsareena
	{START_ADDR_FRONT_T + 11980, 0x800, 16},
	// mareep
	{START_ADDR_FRONT_T + 12992, 0x800, 17},
	// flaaffy
	{START_ADDR_FRONT_T + 13684, 0x800, 18},
	// ampharos
	{START_ADDR_FRONT_T + 14452, 0x800, 19},
	// combee
	{START_ADDR_FRONT_T + 15312, 0x800, 20},
	// vespiquen
	{START_ADDR_FRONT_T + 15960, 0x800, 21},
	// spinarak
	{START_ADDR_FRONT_T + 16968, 0x800, 22},
	// ariados
	{START_ADDR_FRONT_T + 17596, 0x800, 23},
	// joltik
	{START_ADDR_FRONT_T + 18556, 0x800, 24},
	// galvantula
	{START_ADDR_FRONT_T + 19092, 0x800, 25},
	// dewpider
	{START_ADDR_FRONT_T + 20024, 0x800, 26},
	// araquanid
	{START_ADDR_FRONT_T + 20704, 0x800, 27},
	// zubat
	{START_ADDR_FRONT_T + 21836, 0x800, 28},
	// golbat
	{START_ADDR_FRONT_T + 22564, 0x800, 29},
	// crobat
	{START_ADDR_FRONT_T + 23488, 0x800, 30},
	// yanma
	{START_ADDR_FRONT_T + 24432, 0x800, 31},
	// yanmega
	{START_ADDR_FRONT_T + 25332, 0x800, 32},
	// morelull
	{START_ADDR_FRONT_T + 26268, 0x800, 33},
	// shiinotic
	{START_ADDR_FRONT_T + 26836, 0x800, 34},
	// vulpix
	{START_ADDR_FRONT_T + 27764, 0x800, 35},
	// ninetales
	{START_ADDR_FRONT_T + 28592, 0x800, 36},
	// growlithe
	{START_ADDR_FRONT_T + 29676, 0x800, 37},
	// arcanine
	{START_ADDR_FRONT_T + 30532, 0x800, 38},
	// pineco
	{START_ADDR_FRONT_T + 31864, 0x800, 39},
	// forretress
	{START_ADDR_FRONT_T + 32696, 0x800, 40},
	// nincada
	{START_ADDR_FRONT_T + 33748, 0x800, 41},
	// ninjask
	{START_ADDR_FRONT_T + 34420, 0x800, 42},
	// shedinja
	{START_ADDR_FRONT_T + 35300, 0x800, 43},
	// feebas
	{START_ADDR_FRONT_T + 36100, 0x800, 44},
	// milotic
	{START_ADDR_FRONT_T + 36752, 0x800, 45},
	// shellder
	{START_ADDR_FRONT_T + 37920, 0x800, 46},
	// cloyster
	{START_ADDR_FRONT_T + 38536, 0x800, 47},
	// slowpoke
	{START_ADDR_FRONT_T + 39616, 0x800, 48},
	// slowbro
	{START_ADDR_FRONT_T + 40396, 0x800, 49},
	// slowking
	{START_ADDR_FRONT_T + 41612, 0x800, 50},
	// abra
	{START_ADDR_FRONT_T + 42560, 0x800, 51},
	// kadabra
	{START_ADDR_FRONT_T + 43300, 0x800, 52},
	// alakazam
	{START_ADDR_FRONT_T + 44424, 0x800, 53},
	// espurr
	{START_ADDR_FRONT_T + 45444, 0x800, 54},
	// meowstic
	{START_ADDR_FRONT_T + 46076, 0x800, 55},
	// cottonee
	{START_ADDR_FRONT_T + 46984, 0x800, 56},
	// whimsicott
	{START_ADDR_FRONT_T + 47584, 0x800, 57},
	// petilil
	{START_ADDR_FRONT_T + 48500, 0x800, 58},
	// lilligant
	{START_ADDR_FRONT_T + 49116, 0x800, 59},
	// shroomish
	{START_ADDR_FRONT_T + 50180, 0x800, 60},
	// breloom
	{START_ADDR_FRONT_T + 50796, 0x800, 61},
	// swablu
	{START_ADDR_FRONT_T + 51796, 0x800, 62},
	// altaria
	{START_ADDR_FRONT_T + 52512, 0x800, 63},
	// murkrow
	{START_ADDR_FRONT_T + 53500, 0x800, 64},
	// honchkrow
	{START_ADDR_FRONT_T + 54236, 0x800, 65},
	// cleffa
	{START_ADDR_FRONT_T + 55208, 0x800, 66},
	// clefairy
	{START_ADDR_FRONT_T + 55688, 0x800, 67},
	// clefable
	{START_ADDR_FRONT_T + 56336, 0x800, 68},
	// riolu
	{START_ADDR_FRONT_T + 57164, 0x800, 69},
	// lucario
	{START_ADDR_FRONT_T + 57840, 0x800, 70},
	// machop
	{START_ADDR_FRONT_T + 58720, 0x800, 71},
	// machoke
	{START_ADDR_FRONT_T + 59396, 0x800, 72},
	// machamp
	{START_ADDR_FRONT_T + 60340, 0x800, 73},
	// shinx
	{START_ADDR_FRONT_T + 61700, 0x800, 74},
	// luxio
	{START_ADDR_FRONT_T + 62380, 0x800, 75},
	// luxray
	{START_ADDR_FRONT_T + 63224, 0x800, 76},
	// litleo
	{START_ADDR_FRONT_T + 64236, 0x800, 77},
	// pyroar
	{START_ADDR_FRONT_T + 64908, 0x800, 78},
	// houndour
	{START_ADDR_FRONT_T + 66168, 0x800, 79},
	// houndoom
	{START_ADDR_FRONT_T + 66864, 0x800, 80},
	// wingull
	{START_ADDR_FRONT_T + 67888, 0x800, 81},
	// pelipper
	{START_ADDR_FRONT_T + 68460, 0x800, 82},
	// tentacool
	{START_ADDR_FRONT_T + 69380, 0x800, 83},
	// tentacruel
	{START_ADDR_FRONT_T + 70052, 0x800, 84},
	// remoraid
	{START_ADDR_FRONT_T + 71232, 0x800, 85},
	// octillery
	{START_ADDR_FRONT_T + 71848, 0x800, 86},
	// inkay
	{START_ADDR_FRONT_T + 72668, 0x800, 87},
	// malamar
	{START_ADDR_FRONT_T + 73352, 0x800, 88},
	// dwebble
	{START_ADDR_FRONT_T + 74492, 0x800, 89},
	// crustle
	{START_ADDR_FRONT_T + 75180, 0x800, 90},
	// skrelp
	{START_ADDR_FRONT_T + 76188, 0x800, 91},
	// dragalge
	{START_ADDR_FRONT_T + 76840, 0x800, 92},
	// trubbish
	{START_ADDR_FRONT_T + 77828, 0x800, 93},
	// garbodor
	{START_ADDR_FRONT_T + 78412, 0x800, 94},
	// croagunk
	{START_ADDR_FRONT_T + 79696, 0x800, 95},
	// toxicroak
	{START_ADDR_FRONT_T + 80428, 0x800, 96},
	// skorupi
	{START_ADDR_FRONT_T + 81408, 0x800, 97},
	// drapion
	{START_ADDR_FRONT_T + 82216, 0x800, 98},
	// carnivine
	{START_ADDR_FRONT_T + 83496, 0x800, 99},
	// goomy
	{START_ADDR_FRONT_T + 84424, 0x800, 100},
	// sliggoo
	{START_ADDR_FRONT_T + 84968, 0x800, 101},
	// goodra
	{START_ADDR_FRONT_T + 85684, 0x800, 102},
	// mudbray
	{START_ADDR_FRONT_T + 86668, 0x800, 103},
	// mudsdale
	{START_ADDR_FRONT_T + 87488, 0x800, 104},
	// gastly
	{START_ADDR_FRONT_T + 88712, 0x800, 105},
	// haunter
	{START_ADDR_FRONT_T + 89664, 0x800, 106},
	// gengar
	{START_ADDR_FRONT_T + 90688, 0x800, 107},
	// duskull
	{START_ADDR_FRONT_T + 91612, 0x800, 108},
	// dusclops
	{START_ADDR_FRONT_T + 92364, 0x800, 109},
	// dusknoir
	{START_ADDR_FRONT_T + 93292, 0x800, 110},
	// noibat
	{START_ADDR_FRONT_T + 94504, 0x800, 111},
	// noivern
	{START_ADDR_FRONT_T + 95364, 0x800, 112},
	// dunsparce
	{START_ADDR_FRONT_T + 96524, 0x800, 113},
	// mienfoo
	{START_ADDR_FRONT_T + 97308, 0x800, 114},
	// mienshao
	{START_ADDR_FRONT_T + 97980, 0x800, 115},
	// blitzle
	{START_ADDR_FRONT_T + 98896, 0x800, 116},
	// zebstrika
	{START_ADDR_FRONT_T + 99612, 0x800, 117},
	// ponyta
	{START_ADDR_FRONT_T + 100680, 0x800, 118},
	// rapidash
	{START_ADDR_FRONT_T + 101616, 0x800, 119},
	// heracross
	{START_ADDR_FRONT_T + 102848, 0x800, 120},
	// scyther
	{START_ADDR_FRONT_T + 103856, 0x800, 121},
	// scizor
	{START_ADDR_FRONT_T + 105052, 0x800, 122},
	// eevee
	{START_ADDR_FRONT_T + 106308, 0x800, 123},
	// vaporeon
	{START_ADDR_FRONT_T + 106984, 0x800, 124},
	// jolteon
	{START_ADDR_FRONT_T + 107900, 0x800, 125},
	// flareon
	{START_ADDR_FRONT_T + 108828, 0x800, 126},
	// espeon
	{START_ADDR_FRONT_T + 109720, 0x800, 127},
	// umbreon
	{START_ADDR_FRONT_T + 110552, 0x800, 128},
	// leafeon
	{START_ADDR_FRONT_T + 111340, 0x800, 129},
	// glaceon
	{START_ADDR_FRONT_T + 112192, 0x800, 130},
	// sylveon
	{START_ADDR_FRONT_T + 112988, 0x800, 131},
	// rockruff
	{START_ADDR_FRONT_T + 113948, 0x800, 132},
	// lycanroc
	{START_ADDR_FRONT_T + 114704, 0x800, 133},
	// geodude
	{START_ADDR_FRONT_T + 115796, 0x800, 134},
	// graveler
	{START_ADDR_FRONT_T + 116416, 0x800, 135},
	// golem
	{START_ADDR_FRONT_T + 117432, 0x800, 136},
	// anorith
	{START_ADDR_FRONT_T + 118580, 0x800, 137},
	// armaldo
	{START_ADDR_FRONT_T + 119384, 0x800, 138},
	// lileep
	{START_ADDR_FRONT_T + 120792, 0x800, 139},
	// cradily
	{START_ADDR_FRONT_T + 121644, 0x800, 140},
	// chinchou
	{START_ADDR_FRONT_T + 122688, 0x800, 141},
	// lanturn
	{START_ADDR_FRONT_T + 123416, 0x800, 142},
	// staryu
	{START_ADDR_FRONT_T + 124296, 0x800, 143},
	// starmie
	{START_ADDR_FRONT_T + 125036, 0x800, 144},
	// spheal
	{START_ADDR_FRONT_T + 126100, 0x800, 145},
	// sealeo
	{START_ADDR_FRONT_T + 126728, 0x800, 146},
	// walrein
	{START_ADDR_FRONT_T + 127624, 0x800, 147},
	// pawniard
	{START_ADDR_FRONT_T + 128792, 0x800, 148},
	// bisharp
	{START_ADDR_FRONT_T + 129476, 0x800, 149},
	// scraggy
	{START_ADDR_FRONT_T + 130500, 0x800, 150},
	// scrafty
	{START_ADDR_FRONT_T + 131084, 0x800, 151},
	// gligar
	{START_ADDR_FRONT_T + 131936, 0x800, 152},
	// gliscor
	{START_ADDR_FRONT_T + 133000, 0x800, 153},
	// skiddo
	{START_ADDR_FRONT_T + 134180, 0x800, 154},
	// gogoat
	{START_ADDR_FRONT_T + 135012, 0x800, 155},
	// drampa
	{START_ADDR_FRONT_T + 136168, 0x800, 156},
	// larvitar
	{START_ADDR_FRONT_T + 137392, 0x800, 157},
	// pupitar
	{START_ADDR_FRONT_T + 137996, 0x800, 158},
	// tyranitar
	{START_ADDR_FRONT_T + 138748, 0x800, 159},
	// salandit
	{START_ADDR_FRONT_T + 140088, 0x800, 160},
	// salazzle
	{START_ADDR_FRONT_T + 140836, 0x800, 161},
	// sandile
	{START_ADDR_FRONT_T + 141844, 0x800, 162},
	// krokorok
	{START_ADDR_FRONT_T + 142468, 0x800, 163},
	// krookodile
	{START_ADDR_FRONT_T + 143392, 0x800, 164},
	// sigilyph
	{START_ADDR_FRONT_T + 144780, 0x800, 165},
	// maractus
	{START_ADDR_FRONT_T + 145960, 0x800, 166},
	// cacnea
	{START_ADDR_FRONT_T + 147024, 0x800, 167},
	// cacturne
	{START_ADDR_FRONT_T + 147808, 0x800, 168},
	// shuckle
	{START_ADDR_FRONT_T + 148888, 0x800, 169},
	// slugma
	{START_ADDR_FRONT_T + 149600, 0x800, 170},
	// magcargo
	{START_ADDR_FRONT_T + 150228, 0x800, 171},
	// torkoal
	{START_ADDR_FRONT_T + 151068, 0x800, 172},
	// turtonator
	{START_ADDR_FRONT_T + 152264, 0x800, 173},
	// larvesta
	{START_ADDR_FRONT_T + 153624, 0x800, 174},
	// volcarona
	{START_ADDR_FRONT_T + 154288, 0x800, 175},
	// swirlix
	{START_ADDR_FRONT_T + 155396, 0x800, 176},
	// slurpuff
	{START_ADDR_FRONT_T + 156012, 0x800, 177},
	// snubbull
	{START_ADDR_FRONT_T + 156896, 0x800, 178},
	// granbull
	{START_ADDR_FRONT_T + 157616, 0x800, 179},
	// tynamo
	{START_ADDR_FRONT_T + 158524, 0x800, 180},
	// eelektrik
	{START_ADDR_FRONT_T + 159004, 0x800, 181},
	// eelektross
	{START_ADDR_FRONT_T + 159856, 0x800, 182},
	// magnemite
	{START_ADDR_FRONT_T + 161020, 0x800, 183},
	// magneton
	{START_ADDR_FRONT_T + 161492, 0x800, 184},
	// magnezone
	{START_ADDR_FRONT_T + 162516, 0x800, 185},
	// togedemaru
	{START_ADDR_FRONT_T + 163536, 0x800, 186},
	// rotom
	{START_ADDR_FRONT_T + 164168, 0x800, 187},
	// sandygast
	{START_ADDR_FRONT_T + 164748, 0x800, 188},
	// palossand
	{START_ADDR_FRONT_T + 165388, 0x800, 189},
	// litwick
	{START_ADDR_FRONT_T + 166428, 0x800, 190},
	// lampent
	{START_ADDR_FRONT_T + 166960, 0x800, 191},
	// chandelure
	{START_ADDR_FRONT_T + 167608, 0x800, 192},
	// dhelmise
	{START_ADDR_FRONT_T + 168416, 0x800, 193},
	// honedge
	{START_ADDR_FRONT_T + 169436, 0x800, 194},
	// doublade
	{START_ADDR_FRONT_T + 170232, 0x800, 195},
	// aegislash
	{START_ADDR_FRONT_T + 171340, 0x800, 196},
	// spiritomb
	{START_ADDR_FRONT_T + 172344, 0x800, 197},
	// mawile
	{START_ADDR_FRONT_T + 173272, 0x800, 198},
	// girafarig
	{START_ADDR_FRONT_T + 174172, 0x800, 199},
	// munchlax
	{START_ADDR_FRONT_T + 175112, 0x800, 200},
	// snorlax
	{START_ADDR_FRONT_T + 175760, 0x800, 201},
	// pancham
	{START_ADDR_FRONT_T + 176852, 0x800, 202},
	// pangoro
	{START_ADDR_FRONT_T + 177484, 0x800, 203},
	// passimian
	{START_ADDR_FRONT_T + 178584, 0x800, 204},
	// stufful
	{START_ADDR_FRONT_T + 179664, 0x800, 205},
	// bewear
	{START_ADDR_FRONT_T + 180328, 0x800, 206},
	// bouffalant
	{START_ADDR_FRONT_T + 181160, 0x800, 207},
	// kangaskhan
	{START_ADDR_FRONT_T + 182156, 0x800, 208},
	// hawlucha
	{START_ADDR_FRONT_T + 183368, 0x800, 209},
	// tropius
	{START_ADDR_FRONT_T + 184288, 0x800, 210},
	// lapras
	{START_ADDR_FRONT_T + 185688, 0x800, 211},
	// skarmory
	{START_ADDR_FRONT_T + 186648, 0x800, 212},
	// sneasel
	{START_ADDR_FRONT_T + 187896, 0x800, 213},
	// weavile
	{START_ADDR_FRONT_T + 188732, 0x800, 214},
	// snover
	{START_ADDR_FRONT_T + 189700, 0x800, 215},
	// abomasnow
	{START_ADDR_FRONT_T + 190592, 0x800, 216},
	// snorunt
	{START_ADDR_FRONT_T + 191848, 0x800, 217},
	// glalie
	{START_ADDR_FRONT_T + 192556, 0x800, 218},
	// froslass
	{START_ADDR_FRONT_T + 193524, 0x800, 219},
	// bergmite
	{START_ADDR_FRONT_T + 194320, 0x800, 220},
	// avalugg
	{START_ADDR_FRONT_T + 194952, 0x800, 221},
	// cryogonal
	{START_ADDR_FRONT_T + 196072, 0x800, 222},
	// porygon
	{START_ADDR_FRONT_T + 197408, 0x800, 223},
	// porygon2
	{START_ADDR_FRONT_T + 198108, 0x800, 224},
	// porygonz
	{START_ADDR_FRONT_T + 198756, 0x800, 225},
	// druddigon
	{START_ADDR_FRONT_T + 199428, 0x800, 226},
	// golett
	{START_ADDR_FRONT_T + 200568, 0x800, 227},
	// golurk
	{START_ADDR_FRONT_T + 201520, 0x800, 228},
	// drilbur
	{START_ADDR_FRONT_T + 202956, 0x800, 229},
	// excadrill
	{START_ADDR_FRONT_T + 203820, 0x800, 230},
	// beldum
	{START_ADDR_FRONT_T + 204912, 0x800, 231},
	// metang
	{START_ADDR_FRONT_T + 205536, 0x800, 232},
	// metagross
	{START_ADDR_FRONT_T + 206652, 0x800, 233},
	// gible
	{START_ADDR_FRONT_T + 207776, 0x800, 234},
	// gabite
	{START_ADDR_FRONT_T + 208520, 0x800, 235},
	// garchomp
	{START_ADDR_FRONT_T + 209532, 0x800, 236},
	// dratini
	{START_ADDR_FRONT_T + 210776, 0x800, 237},
	// dragonair
	{START_ADDR_FRONT_T + 211472, 0x800, 238},
	// dragonite
	{START_ADDR_FRONT_T + 212336, 0x800, 239},
	// latias
	{START_ADDR_FRONT_T + 213728, 0x800, 240},
	// latios
	{START_ADDR_FRONT_T + 214788, 0x800, 241},
	// heatran
	{START_ADDR_FRONT_T + 215896, 0x800, 242},
	// deoxys
	{START_ADDR_FRONT_T + 216988, 0x800, 243},
	// jirachi
	{START_ADDR_FRONT_T + 217976, 0x800, 244},
	// darkrai
	{START_ADDR_FRONT_T + 218756, 0x800, 245},
	
};
