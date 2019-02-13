#include <pokeagb/pokeagb.h>
#include "../pokemon.h"

struct CompressedSpriteSheet gMonStillFrontPicTable[247] = {
	// question
	{START_ADDR_FRONT_T + 0, 0x800, 0},
	// horsea
	{START_ADDR_FRONT_T + 384, 0x800, 1},
	// seadra
	{START_ADDR_FRONT_T + 1016, 0x800, 2},
	// kingdra
	{START_ADDR_FRONT_T + 1976, 0x800, 3},
	// trapinch
	{START_ADDR_FRONT_T + 3032, 0x800, 4},
	// vibrava
	{START_ADDR_FRONT_T + 3572, 0x800, 5},
	// flygon
	{START_ADDR_FRONT_T + 4452, 0x800, 6},
	// togepi
	{START_ADDR_FRONT_T + 5716, 0x800, 7},
	// togetic
	{START_ADDR_FRONT_T + 6184, 0x800, 8},
	// togekiss
	{START_ADDR_FRONT_T + 6812, 0x800, 9},
	// yungoos
	{START_ADDR_FRONT_T + 7592, 0x800, 10},
	// gumshoos
	{START_ADDR_FRONT_T + 8252, 0x800, 11},
	// bunnelby
	{START_ADDR_FRONT_T + 9000, 0x800, 12},
	// diggersby
	{START_ADDR_FRONT_T + 9744, 0x800, 13},
	// bounsweet
	{START_ADDR_FRONT_T + 10772, 0x800, 14},
	// steenee
	{START_ADDR_FRONT_T + 11300, 0x800, 15},
	// tsareena
	{START_ADDR_FRONT_T + 12044, 0x800, 16},
	// mareep
	{START_ADDR_FRONT_T + 13056, 0x800, 17},
	// flaaffy
	{START_ADDR_FRONT_T + 13748, 0x800, 18},
	// ampharos
	{START_ADDR_FRONT_T + 14516, 0x800, 19},
	// combee
	{START_ADDR_FRONT_T + 15376, 0x800, 20},
	// vespiquen
	{START_ADDR_FRONT_T + 16024, 0x800, 21},
	// spinarak
	{START_ADDR_FRONT_T + 17032, 0x800, 22},
	// ariados
	{START_ADDR_FRONT_T + 17660, 0x800, 23},
	// joltik
	{START_ADDR_FRONT_T + 18620, 0x800, 24},
	// galvantula
	{START_ADDR_FRONT_T + 19156, 0x800, 25},
	// dewpider
	{START_ADDR_FRONT_T + 20088, 0x800, 26},
	// araquanid
	{START_ADDR_FRONT_T + 20768, 0x800, 27},
	// zubat
	{START_ADDR_FRONT_T + 21900, 0x800, 28},
	// golbat
	{START_ADDR_FRONT_T + 22628, 0x800, 29},
	// crobat
	{START_ADDR_FRONT_T + 23552, 0x800, 30},
	// yanma
	{START_ADDR_FRONT_T + 24496, 0x800, 31},
	// yanmega
	{START_ADDR_FRONT_T + 25396, 0x800, 32},
	// morelull
	{START_ADDR_FRONT_T + 26332, 0x800, 33},
	// shiinotic
	{START_ADDR_FRONT_T + 26900, 0x800, 34},
	// vulpix
	{START_ADDR_FRONT_T + 27828, 0x800, 35},
	// ninetales
	{START_ADDR_FRONT_T + 28656, 0x800, 36},
	// growlithe
	{START_ADDR_FRONT_T + 29740, 0x800, 37},
	// arcanine
	{START_ADDR_FRONT_T + 30596, 0x800, 38},
	// pineco
	{START_ADDR_FRONT_T + 31928, 0x800, 39},
	// forretress
	{START_ADDR_FRONT_T + 32760, 0x800, 40},
	// nincada
	{START_ADDR_FRONT_T + 33812, 0x800, 41},
	// ninjask
	{START_ADDR_FRONT_T + 34484, 0x800, 42},
	// shedinja
	{START_ADDR_FRONT_T + 35364, 0x800, 43},
	// feebas
	{START_ADDR_FRONT_T + 36164, 0x800, 44},
	// milotic
	{START_ADDR_FRONT_T + 36816, 0x800, 45},
	// shellder
	{START_ADDR_FRONT_T + 37984, 0x800, 46},
	// cloyster
	{START_ADDR_FRONT_T + 38600, 0x800, 47},
	// slowpoke
	{START_ADDR_FRONT_T + 39680, 0x800, 48},
	// slowbro
	{START_ADDR_FRONT_T + 40460, 0x800, 49},
	// slowking
	{START_ADDR_FRONT_T + 41676, 0x800, 50},
	// abra
	{START_ADDR_FRONT_T + 42624, 0x800, 51},
	// kadabra
	{START_ADDR_FRONT_T + 43364, 0x800, 52},
	// alakazam
	{START_ADDR_FRONT_T + 44488, 0x800, 53},
	// espurr
	{START_ADDR_FRONT_T + 45508, 0x800, 54},
	// meowstic
	{START_ADDR_FRONT_T + 46140, 0x800, 55},
	// cottonee
	{START_ADDR_FRONT_T + 47048, 0x800, 56},
	// whimsicott
	{START_ADDR_FRONT_T + 47648, 0x800, 57},
	// petilil
	{START_ADDR_FRONT_T + 48564, 0x800, 58},
	// lilligant
	{START_ADDR_FRONT_T + 49180, 0x800, 59},
	// shroomish
	{START_ADDR_FRONT_T + 50244, 0x800, 60},
	// breloom
	{START_ADDR_FRONT_T + 50860, 0x800, 61},
	// swablu
	{START_ADDR_FRONT_T + 51860, 0x800, 62},
	// altaria
	{START_ADDR_FRONT_T + 52576, 0x800, 63},
	// murkrow
	{START_ADDR_FRONT_T + 53564, 0x800, 64},
	// honchkrow
	{START_ADDR_FRONT_T + 54300, 0x800, 65},
	// cleffa
	{START_ADDR_FRONT_T + 55272, 0x800, 66},
	// clefairy
	{START_ADDR_FRONT_T + 55752, 0x800, 67},
	// clefable
	{START_ADDR_FRONT_T + 56400, 0x800, 68},
	// riolu
	{START_ADDR_FRONT_T + 57228, 0x800, 69},
	// lucario
	{START_ADDR_FRONT_T + 57904, 0x800, 70},
	// machop
	{START_ADDR_FRONT_T + 58784, 0x800, 71},
	// machoke
	{START_ADDR_FRONT_T + 59460, 0x800, 72},
	// machamp
	{START_ADDR_FRONT_T + 60404, 0x800, 73},
	// shinx
	{START_ADDR_FRONT_T + 61764, 0x800, 74},
	// luxio
	{START_ADDR_FRONT_T + 62444, 0x800, 75},
	// luxray
	{START_ADDR_FRONT_T + 63288, 0x800, 76},
	// litleo
	{START_ADDR_FRONT_T + 64300, 0x800, 77},
	// pyroar
	{START_ADDR_FRONT_T + 64972, 0x800, 78},
	// houndour
	{START_ADDR_FRONT_T + 66232, 0x800, 79},
	// houndoom
	{START_ADDR_FRONT_T + 66928, 0x800, 80},
	// wingull
	{START_ADDR_FRONT_T + 67952, 0x800, 81},
	// pelipper
	{START_ADDR_FRONT_T + 68524, 0x800, 82},
	// tentacool
	{START_ADDR_FRONT_T + 69444, 0x800, 83},
	// tentacruel
	{START_ADDR_FRONT_T + 70116, 0x800, 84},
	// remoraid
	{START_ADDR_FRONT_T + 71296, 0x800, 85},
	// octillery
	{START_ADDR_FRONT_T + 71912, 0x800, 86},
	// inkay
	{START_ADDR_FRONT_T + 72732, 0x800, 87},
	// malamar
	{START_ADDR_FRONT_T + 73416, 0x800, 88},
	// dwebble
	{START_ADDR_FRONT_T + 74556, 0x800, 89},
	// crustle
	{START_ADDR_FRONT_T + 75244, 0x800, 90},
	// skrelp
	{START_ADDR_FRONT_T + 76252, 0x800, 91},
	// dragalge
	{START_ADDR_FRONT_T + 76904, 0x800, 92},
	// trubbish
	{START_ADDR_FRONT_T + 77892, 0x800, 93},
	// garbodor
	{START_ADDR_FRONT_T + 78476, 0x800, 94},
	// croagunk
	{START_ADDR_FRONT_T + 79760, 0x800, 95},
	// toxicroak
	{START_ADDR_FRONT_T + 80492, 0x800, 96},
	// skorupi
	{START_ADDR_FRONT_T + 81472, 0x800, 97},
	// drapion
	{START_ADDR_FRONT_T + 82280, 0x800, 98},
	// carnivine
	{START_ADDR_FRONT_T + 83560, 0x800, 99},
	// goomy
	{START_ADDR_FRONT_T + 84488, 0x800, 100},
	// sliggoo
	{START_ADDR_FRONT_T + 85032, 0x800, 101},
	// goodra
	{START_ADDR_FRONT_T + 85748, 0x800, 102},
	// mudbray
	{START_ADDR_FRONT_T + 86732, 0x800, 103},
	// mudsdale
	{START_ADDR_FRONT_T + 87552, 0x800, 104},
	// gastly
	{START_ADDR_FRONT_T + 88776, 0x800, 105},
	// haunter
	{START_ADDR_FRONT_T + 89728, 0x800, 106},
	// gengar
	{START_ADDR_FRONT_T + 90752, 0x800, 107},
	// duskull
	{START_ADDR_FRONT_T + 91676, 0x800, 108},
	// dusclops
	{START_ADDR_FRONT_T + 92428, 0x800, 109},
	// dusknoir
	{START_ADDR_FRONT_T + 93356, 0x800, 110},
	// noibat
	{START_ADDR_FRONT_T + 94568, 0x800, 111},
	// noivern
	{START_ADDR_FRONT_T + 95428, 0x800, 112},
	// dunsparce
	{START_ADDR_FRONT_T + 96588, 0x800, 113},
	// mienfoo
	{START_ADDR_FRONT_T + 97372, 0x800, 114},
	// mienshao
	{START_ADDR_FRONT_T + 98044, 0x800, 115},
	// blitzle
	{START_ADDR_FRONT_T + 98960, 0x800, 116},
	// zebstrika
	{START_ADDR_FRONT_T + 99676, 0x800, 117},
	// ponyta
	{START_ADDR_FRONT_T + 100744, 0x800, 118},
	// rapidash
	{START_ADDR_FRONT_T + 101680, 0x800, 119},
	// heracross
	{START_ADDR_FRONT_T + 102912, 0x800, 120},
	// scyther
	{START_ADDR_FRONT_T + 103920, 0x800, 121},
	// scizor
	{START_ADDR_FRONT_T + 105116, 0x800, 122},
	// eevee
	{START_ADDR_FRONT_T + 106372, 0x800, 123},
	// vaporeon
	{START_ADDR_FRONT_T + 107048, 0x800, 124},
	// jolteon
	{START_ADDR_FRONT_T + 107964, 0x800, 125},
	// flareon
	{START_ADDR_FRONT_T + 108892, 0x800, 126},
	// espeon
	{START_ADDR_FRONT_T + 109784, 0x800, 127},
	// umbreon
	{START_ADDR_FRONT_T + 110616, 0x800, 128},
	// leafeon
	{START_ADDR_FRONT_T + 111404, 0x800, 129},
	// glaceon
	{START_ADDR_FRONT_T + 112256, 0x800, 130},
	// sylveon
	{START_ADDR_FRONT_T + 113052, 0x800, 131},
	// rockruff
	{START_ADDR_FRONT_T + 114012, 0x800, 132},
	// lycanroc
	{START_ADDR_FRONT_T + 114768, 0x800, 133},
	// geodude
	{START_ADDR_FRONT_T + 115860, 0x800, 134},
	// graveler
	{START_ADDR_FRONT_T + 116480, 0x800, 135},
	// golem
	{START_ADDR_FRONT_T + 117496, 0x800, 136},
	// anorith
	{START_ADDR_FRONT_T + 118644, 0x800, 137},
	// armaldo
	{START_ADDR_FRONT_T + 119448, 0x800, 138},
	// lileep
	{START_ADDR_FRONT_T + 120856, 0x800, 139},
	// cradily
	{START_ADDR_FRONT_T + 121708, 0x800, 140},
	// chinchou
	{START_ADDR_FRONT_T + 122752, 0x800, 141},
	// lanturn
	{START_ADDR_FRONT_T + 123480, 0x800, 142},
	// staryu
	{START_ADDR_FRONT_T + 124360, 0x800, 143},
	// starmie
	{START_ADDR_FRONT_T + 125100, 0x800, 144},
	// spheal
	{START_ADDR_FRONT_T + 126164, 0x800, 145},
	// sealeo
	{START_ADDR_FRONT_T + 126792, 0x800, 146},
	// walrein
	{START_ADDR_FRONT_T + 127688, 0x800, 147},
	// pawniard
	{START_ADDR_FRONT_T + 128856, 0x800, 148},
	// bisharp
	{START_ADDR_FRONT_T + 129540, 0x800, 149},
	// scraggy
	{START_ADDR_FRONT_T + 130564, 0x800, 150},
	// scrafty
	{START_ADDR_FRONT_T + 131148, 0x800, 151},
	// gligar
	{START_ADDR_FRONT_T + 132000, 0x800, 152},
	// gliscor
	{START_ADDR_FRONT_T + 133064, 0x800, 153},
	// skiddo
	{START_ADDR_FRONT_T + 134244, 0x800, 154},
	// gogoat
	{START_ADDR_FRONT_T + 135076, 0x800, 155},
	// drampa
	{START_ADDR_FRONT_T + 136232, 0x800, 156},
	// larvitar
	{START_ADDR_FRONT_T + 137456, 0x800, 157},
	// pupitar
	{START_ADDR_FRONT_T + 138060, 0x800, 158},
	// tyranitar
	{START_ADDR_FRONT_T + 138812, 0x800, 159},
	// salandit
	{START_ADDR_FRONT_T + 140152, 0x800, 160},
	// salazzle
	{START_ADDR_FRONT_T + 140900, 0x800, 161},
	// sandile
	{START_ADDR_FRONT_T + 141908, 0x800, 162},
	// krokorok
	{START_ADDR_FRONT_T + 142532, 0x800, 163},
	// krookodile
	{START_ADDR_FRONT_T + 143456, 0x800, 164},
	// sigilyph
	{START_ADDR_FRONT_T + 144844, 0x800, 165},
	// maractus
	{START_ADDR_FRONT_T + 146024, 0x800, 166},
	// cacnea
	{START_ADDR_FRONT_T + 147088, 0x800, 167},
	// cacturne
	{START_ADDR_FRONT_T + 147872, 0x800, 168},
	// shuckle
	{START_ADDR_FRONT_T + 148952, 0x800, 169},
	// slugma
	{START_ADDR_FRONT_T + 149664, 0x800, 170},
	// magcargo
	{START_ADDR_FRONT_T + 150292, 0x800, 171},
	// torkoal
	{START_ADDR_FRONT_T + 151132, 0x800, 172},
	// turtonator
	{START_ADDR_FRONT_T + 152328, 0x800, 173},
	// larvesta
	{START_ADDR_FRONT_T + 153688, 0x800, 174},
	// volcarona
	{START_ADDR_FRONT_T + 154352, 0x800, 175},
	// swirlix
	{START_ADDR_FRONT_T + 155460, 0x800, 176},
	// slurpuff
	{START_ADDR_FRONT_T + 156076, 0x800, 177},
	// snubbull
	{START_ADDR_FRONT_T + 156960, 0x800, 178},
	// granbull
	{START_ADDR_FRONT_T + 157680, 0x800, 179},
	// tynamo
	{START_ADDR_FRONT_T + 158588, 0x800, 180},
	// eelektrik
	{START_ADDR_FRONT_T + 159068, 0x800, 181},
	// eelektross
	{START_ADDR_FRONT_T + 159920, 0x800, 182},
	// magnemite
	{START_ADDR_FRONT_T + 161084, 0x800, 183},
	// magneton
	{START_ADDR_FRONT_T + 161556, 0x800, 184},
	// magnezone
	{START_ADDR_FRONT_T + 162580, 0x800, 185},
	// togedemaru
	{START_ADDR_FRONT_T + 163600, 0x800, 186},
	// rotom
	{START_ADDR_FRONT_T + 164232, 0x800, 187},
	// sandygast
	{START_ADDR_FRONT_T + 164812, 0x800, 188},
	// palossand
	{START_ADDR_FRONT_T + 165452, 0x800, 189},
	// litwick
	{START_ADDR_FRONT_T + 166492, 0x800, 190},
	// lampent
	{START_ADDR_FRONT_T + 167024, 0x800, 191},
	// chandelure
	{START_ADDR_FRONT_T + 167672, 0x800, 192},
	// dhelmise
	{START_ADDR_FRONT_T + 168480, 0x800, 193},
	// honedge
	{START_ADDR_FRONT_T + 169500, 0x800, 194},
	// doublade
	{START_ADDR_FRONT_T + 170296, 0x800, 195},
	// aegislash
	{START_ADDR_FRONT_T + 171404, 0x800, 196},
	// spiritomb
	{START_ADDR_FRONT_T + 172408, 0x800, 197},
	// mawile
	{START_ADDR_FRONT_T + 173336, 0x800, 198},
	// shuckle
	{START_ADDR_FRONT_T + 174236, 0x800, 199},
	// girafarig
	{START_ADDR_FRONT_T + 174948, 0x800, 200},
	// munchlax
	{START_ADDR_FRONT_T + 175888, 0x800, 201},
	// snorlax
	{START_ADDR_FRONT_T + 176536, 0x800, 202},
	// pancham
	{START_ADDR_FRONT_T + 177628, 0x800, 203},
	// pangoro
	{START_ADDR_FRONT_T + 178260, 0x800, 204},
	// passimian
	{START_ADDR_FRONT_T + 179360, 0x800, 205},
	// stufful
	{START_ADDR_FRONT_T + 180440, 0x800, 206},
	// bewear
	{START_ADDR_FRONT_T + 181104, 0x800, 207},
	// bouffalant
	{START_ADDR_FRONT_T + 181936, 0x800, 208},
	// kangaskhan
	{START_ADDR_FRONT_T + 182932, 0x800, 209},
	// hawlucha
	{START_ADDR_FRONT_T + 184144, 0x800, 210},
	// tropius
	{START_ADDR_FRONT_T + 185064, 0x800, 211},
	// lapras
	{START_ADDR_FRONT_T + 186464, 0x800, 212},
	// skarmory
	{START_ADDR_FRONT_T + 187424, 0x800, 213},
	// sneasel
	{START_ADDR_FRONT_T + 188672, 0x800, 214},
	// weavile
	{START_ADDR_FRONT_T + 189508, 0x800, 215},
	// snover
	{START_ADDR_FRONT_T + 190476, 0x800, 216},
	// abomasnow
	{START_ADDR_FRONT_T + 191368, 0x800, 217},
	// snorunt
	{START_ADDR_FRONT_T + 192624, 0x800, 218},
	// glalie
	{START_ADDR_FRONT_T + 193332, 0x800, 219},
	// froslass
	{START_ADDR_FRONT_T + 194300, 0x800, 220},
	// bergmite
	{START_ADDR_FRONT_T + 195096, 0x800, 221},
	// avalugg
	{START_ADDR_FRONT_T + 195728, 0x800, 222},
	// cryogonal
	{START_ADDR_FRONT_T + 196848, 0x800, 223},
	// porygon
	{START_ADDR_FRONT_T + 198184, 0x800, 224},
	// porygon2
	{START_ADDR_FRONT_T + 198884, 0x800, 225},
	// porygonz
	{START_ADDR_FRONT_T + 199532, 0x800, 226},
	// druddigon
	{START_ADDR_FRONT_T + 200204, 0x800, 227},
	// golett
	{START_ADDR_FRONT_T + 201344, 0x800, 228},
	// golurk
	{START_ADDR_FRONT_T + 202296, 0x800, 229},
	// drilbur
	{START_ADDR_FRONT_T + 203732, 0x800, 230},
	// excadrill
	{START_ADDR_FRONT_T + 204596, 0x800, 231},
	// beldum
	{START_ADDR_FRONT_T + 205688, 0x800, 232},
	// metang
	{START_ADDR_FRONT_T + 206312, 0x800, 233},
	// metagross
	{START_ADDR_FRONT_T + 207428, 0x800, 234},
	// gible
	{START_ADDR_FRONT_T + 208552, 0x800, 235},
	// gabite
	{START_ADDR_FRONT_T + 209296, 0x800, 236},
	// garchomp
	{START_ADDR_FRONT_T + 210308, 0x800, 237},
	// dratini
	{START_ADDR_FRONT_T + 211552, 0x800, 238},
	// dragonair
	{START_ADDR_FRONT_T + 212248, 0x800, 239},
	// dragonite
	{START_ADDR_FRONT_T + 213112, 0x800, 240},
	// latias
	{START_ADDR_FRONT_T + 214504, 0x800, 241},
	// latios
	{START_ADDR_FRONT_T + 215564, 0x800, 242},
	// heatran
	{START_ADDR_FRONT_T + 216672, 0x800, 243},
	// deoxys
	{START_ADDR_FRONT_T + 217764, 0x800, 244},
	// jirachi
	{START_ADDR_FRONT_T + 218752, 0x800, 245},
	// darkrai
	{START_ADDR_FRONT_T + 219532, 0x800, 246},
	
};
