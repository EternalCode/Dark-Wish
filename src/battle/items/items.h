#ifndef ITEM_IDS_H
#define ITEM_IDS_H

#include <pokeagb/pokeagb.h>

typedef void (*ItemCallback)(u8);

#define POKEBALL_CATCH_RATE 10

struct ItemBattleEffects {
    u16 itemId;
    ItemCallback initAction;
};

// struct BallCaptureRate {
//     u16 itemId;
//     u8 captureMultiplier;
//     u8 guarenteeCapture;
// };
//
// const struct BallCaptureRate BallRates[] = {
//     {ITEM_POKEBALL, 10, false},
//     {ITEM_GREATBALL, 15, false},
//     {ITEM_ULTRABALL, 20, false},
//     {ITEM_MASTERBALL, 0, true},
// };

/*
enum Items {
    ITEM_NONE,
	ITEM_MASTER_BALL,
	ITEM_ULTRA_BALL,
	ITEM_GREAT_BALL,
	ITEM_POKE_BALL,
	ITEM_SAFARI_BALL,
	ITEM_NET_BALL,
	ITEM_DIVE_BALL,
	ITEM_NEST_BALL,
	ITEM_REPEAT_BALL,
	ITEM_TIMER_BALL,
	ITEM_LUXURY_BALL,
	ITEM_PREMIER_BALL,
	ITEM_DUSK_BALL,
	ITEM_HEAL_BALL,
	ITEM_QUICK_BALL,
	ITEM_CHERISH_BALL,
	ITEM_POTION,
	ITEM_ANTIDOTE,
	ITEM_BURN_HEAL,
	ITEM_ICE_HEAL,
	ITEM_AWAKENING,
	ITEM_PARALYZE_HEAL,
	ITEM_FULL_RESTORE,
	ITEM_MAX_POTION,
	ITEM_HYPER_POTION,
	ITEM_SUPER_POTION,
	ITEM_FULL_HEAL,
	ITEM_REVIVE,
	ITEM_MAX_REVIVE,
	ITEM_FRESH_WATER,
	ITEM_SODA_POP,
	ITEM_LEMONADE,
	ITEM_MOOMOO_MILK,
	ITEM_ENERGY_POWDER,
	ITEM_ENERGY_ROOT,
	ITEM_HEAL_POWDER,
	ITEM_REVIVAL_HERB,
	ITEM_ETHER,
	ITEM_MAX_ETHER,
	ITEM_ELIXIR,
	ITEM_MAX_ELIXIR,
	ITEM_LAVA_COOKIE,
	ITEM_BERRY_JUICE,
	ITEM_SACRED_ASH,
	ITEM_HP_UP,
	ITEM_PROTEIN,
	ITEM_IRON,
	ITEM_CARBOS,
	ITEM_CALCIUM,
	ITEM_RARE_CANDY,
	ITEM_PP_UP,
	ITEM_ZINC,
	ITEM_PP_MAX,
	ITEM_OLD_GATEAU,
	ITEM_GUARD_SPEC,
	ITEM_DIRE_HIT,
	ITEM_X_ATTACK,
	ITEM_X_DEFENSE,
	ITEM_X_SPEED,
	ITEM_X_ACCURACY,
	ITEM_X_SP_ATK,
	ITEM_X_SP_DEF,
	ITEM_POKE_DOLL,
	ITEM_FLUFFY_TAIL,
	ITEM_BLUE_FLUTE,
	ITEM_YELLOW_FLUTE,
	ITEM_RED_FLUTE,
	ITEM_BLACK_FLUTE,
	ITEM_WHITE_FLUTE,
	ITEM_SHOAL_SALT,
	ITEM_SHOAL_SHELL,
	ITEM_RED_SHARD,
	ITEM_BLUE_SHARD,
	ITEM_YELLOW_SHARD,
	ITEM_GREEN_SHARD,
	ITEM_SUPER_REPEL,
	ITEM_MAX_REPEL,
	ITEM_ESCAPE_ROPE,
	ITEM_REPEL,
	ITEM_SUN_STONE,
	ITEM_MOON_STONE,
	ITEM_FIRE_STONE,
	ITEM_THUNDER_STONE,
	ITEM_WATER_STONE,
	ITEM_LEAF_STONE,
	ITEM_TINY_MUSHROOM,
	ITEM_BIG_MUSHROOM,
	ITEM_PEARL,
	ITEM_BIG_PEARL,
	ITEM_STARDUST,
	ITEM_STAR_PIECE,
	ITEM_NUGGET,
	ITEM_HEART_SCALE,
	ITEM_HONEY,
	ITEM_GROWTH_MULCH,
	ITEM_DAMP_MULCH,
	ITEM_STABLE_MULCH,
	ITEM_GOOEY_MULCH,
	ITEM_ROOT_FOSSIL,
	ITEM_CLAW_FOSSIL,
	ITEM_HELIX_FOSSIL,
	ITEM_DOME_FOSSIL,
	ITEM_OLD_AMBER,
	ITEM_ARMOR_FOSSIL,
	ITEM_SKULL_FOSSIL,
	ITEM_RARE_BONE,
	ITEM_SHINY_STONE,
	ITEM_DUSK_STONE,
	ITEM_DAWN_STONE,
	ITEM_OVAL_STONE,
	ITEM_ODD_KEYSTONE,
	ITEM_GRISEOUS_ORB,
	ITEM_DOUSE_DRIVE,
	ITEM_SHOCK_DRIVE,
	ITEM_BURN_DRIVE,
	ITEM_CHILL_DRIVE,
	ITEM_SWEET_HEART,
	ITEM_ADAMANT_ORB,
	ITEM_LUSTROUS_ORB,
	ITEM_GREET_MAIL,
	ITEM_FAVORED_MAIL,
	ITEM_RSVP_MAIL,
	ITEM_THANKS_MAIL,
	ITEM_INQUIRY_MAIL,
	ITEM_LIKE_MAIL,
	ITEM_REPLY_MAIL,
	ITEM_BRIDGEMAIL_S,
	ITEM_BRIDGEMAIL_D,
	ITEM_BRIDGEMAIL_T,
	ITEM_BRIDGEMAIL_V,
	ITEM_BRIDGEMAIL_M,
	ITEM_CHERI_BERRY,
	ITEM_CHESTO_BERRY,
	ITEM_PECHA_BERRY,
	ITEM_RAWST_BERRY,
	ITEM_ASPEAR_BERRY,
	ITEM_LEPPA_BERRY,
	ITEM_ORAN_BERRY,
	ITEM_PERSIM_BERRY,
	ITEM_LUM_BERRY,
	ITEM_SITRUS_BERRY,
	ITEM_FIGY_BERRY,
	ITEM_WIKI_BERRY,
	ITEM_MAGO_BERRY,
	ITEM_AGUAV_BERRY,
	ITEM_IAPAPA_BERRY,
	ITEM_RAZZ_BERRY,
	ITEM_BLUK_BERRY,
	ITEM_NANAB_BERRY,
	ITEM_WEPEAR_BERRY,
	ITEM_PINAP_BERRY,
	ITEM_POMEG_BERRY,
	ITEM_KELPSY_BERRY,
	ITEM_QUALOT_BERRY,
	ITEM_HONDEW_BERRY,
	ITEM_GREPA_BERRY,
	ITEM_TAMATO_BERRY,
	ITEM_CORNN_BERRY,
	ITEM_MAGOST_BERRY,
	ITEM_RABUTA_BERRY,
	ITEM_NOMEL_BERRY,
	ITEM_SPELON_BERRY,
	ITEM_PAMTRE_BERRY,
	ITEM_WATMEL_BERRY,
	ITEM_DURIN_BERRY,
	ITEM_BELUE_BERRY,
	ITEM_OCCA_BERRY,
	ITEM_PASSHO_BERRY,
	ITEM_WACAN_BERRY,
	ITEM_RINDO_BERRY,
	ITEM_YACHE_BERRY,
	ITEM_CHOPLE_BERRY,
	ITEM_KEBIA_BERRY,
	ITEM_SHUCA_BERRY,
	ITEM_COBA_BERRY,
	ITEM_PAYAPA_BERRY,
	ITEM_TANGA_BERRY,
	ITEM_CHARTI_BERRY,
	ITEM_KASIB_BERRY,
	ITEM_HABAN_BERRY,
	ITEM_COLBUR_BERRY,
	ITEM_BABIRI_BERRY,
	ITEM_CHILAN_BERRY,
	ITEM_LIECHI_BERRY,
	ITEM_GANLON_BERRY,
	ITEM_SALAC_BERRY,
	ITEM_PETAYA_BERRY,
	ITEM_APICOT_BERRY,
	ITEM_LANSAT_BERRY,
	ITEM_STARF_BERRY,
	ITEM_ENIGMA_BERRY,
	ITEM_MICLE_BERRY,
	ITEM_CUSTAP_BERRY,
	ITEM_JABOCA_BERRY,
	ITEM_ROWAP_BERRY,
	ITEM_BRIGHT_POWDER,
	ITEM_WHITE_HERB,
	ITEM_MACHO_BRACE,
	ITEM_EXP_SHARE,
	ITEM_QUICK_CLAW,
	ITEM_SOOTHE_BELL,
	ITEM_MENTAL_HERB,
	ITEM_CHOICE_BAND,
	ITEM_KINGS_ROCK,
	ITEM_SILVER_POWDER,
	ITEM_AMULET_COIN,
	ITEM_CLEANSE_TAG,
	ITEM_SOUL_DEW,
	ITEM_DEEP_SEA_TOOTH,
	ITEM_DEEP_SEA_SCALE,
	ITEM_SMOKE_BALL,
	ITEM_EVERSTONE,
	ITEM_FOCUS_BAND,
	ITEM_LUCKY_EGG,
	ITEM_SCOPE_LENS,
	ITEM_METAL_COAT,
	ITEM_LEFTOVERS,
	ITEM_DRAGON_SCALE,
	ITEM_LIGHT_BALL,
	ITEM_SOFT_SAND,
	ITEM_HARD_STONE,
	ITEM_MIRACLE_SEED,
	ITEM_BLACK_GLASSES,
	ITEM_BLACK_BELT,
	ITEM_MAGNET,
	ITEM_MYSTIC_WATER,
	ITEM_SHARP_BEAK,
	ITEM_POISON_BARB,
	ITEM_NEVER_MELT_ICE,
	ITEM_SPELL_TAG,
	ITEM_TWISTED_SPOON,
	ITEM_CHARCOAL,
	ITEM_DRAGON_FANG,
	ITEM_SILK_SCARF,
	ITEM_UP_GRADE,
	ITEM_SHELL_BELL,
	ITEM_SEA_INCENSE,
	ITEM_LAX_INCENSE,
	ITEM_LUCKY_PUNCH,
	ITEM_METAL_POWDER,
	ITEM_THICK_CLUB,
	ITEM_STICK,
	ITEM_RED_SCARF,
	ITEM_BLUE_SCARF,
	ITEM_PINK_SCARF,
	ITEM_GREEN_SCARF,
	ITEM_YELLOW_SCARF,
	ITEM_WIDE_LENS,
	ITEM_MUSCLE_BAND,
	ITEM_WISE_GLASSES,
	ITEM_EXPERT_BELT,
	ITEM_LIGHT_CLAY,
	ITEM_LIFE_ORB,
	ITEM_POWER_HERB,
	ITEM_TOXIC_ORB,
	ITEM_FLAME_ORB,
	ITEM_QUICK_POWDER,
	ITEM_FOCUS_SASH,
	ITEM_ZOOM_LENS,
	ITEM_METRONOME_item,
	ITEM_IRON_BALL,
	ITEM_LAGGING_TAIL,
	ITEM_DESTINY_KNOT,
	ITEM_BLACK_SLUDGE,
	ITEM_ICY_ROCK,
	ITEM_SMOOTH_ROCK,
	ITEM_HEAT_ROCK,
	ITEM_DAMP_ROCK,
	ITEM_GRIP_CLAW,
	ITEM_CHOICE_SCARF,
	ITEM_STICKY_BARB,
	ITEM_POWER_BRACER,
	ITEM_POWER_BELT,
	ITEM_POWER_LENS,
	ITEM_POWER_BAND,
	ITEM_POWER_ANKLET,
	ITEM_POWER_WEIGHT,
	ITEM_SHED_SHELL,
	ITEM_BIG_ROOT,
	ITEM_CHOICE_SPECS,
	ITEM_FLAME_PLATE,
	ITEM_SPLASH_PLATE,
	ITEM_ZAP_PLATE,
	ITEM_MEADOW_PLATE,
	ITEM_ICICLE_PLATE,
	ITEM_FIST_PLATE,
	ITEM_TOXIC_PLATE,
	ITEM_EARTH_PLATE,
	ITEM_SKY_PLATE,
	ITEM_MIND_PLATE,
	ITEM_INSECT_PLATE,
	ITEM_STONE_PLATE,
	ITEM_SPOOKY_PLATE,
	ITEM_DRACO_PLATE,
	ITEM_DREAD_PLATE,
	ITEM_IRON_PLATE,
	ITEM_ODD_INCENSE,
	ITEM_ROCK_INCENSE,
	ITEM_FULL_INCENSE,
	ITEM_WAVE_INCENSE,
	ITEM_ROSE_INCENSE,
	ITEM_LUCK_INCENSE,
	ITEM_PURE_INCENSE,
	ITEM_PROTECTOR,
	ITEM_ELECTIRIZER,
	ITEM_MAGMARIZER,
	ITEM_DUBIOUS_DISC,
	ITEM_REAPER_CLOTH,
	ITEM_RAZOR_CLAW,
	ITEM_RAZOR_FANG,
	ITEM_TM01,
	ITEM_TM02,
	ITEM_TM03,
	ITEM_TM04,
	ITEM_TM05,
	ITEM_TM06,
	ITEM_TM07,
	ITEM_TM08,
	ITEM_TM09,
	ITEM_TM10,
	ITEM_TM11,
	ITEM_TM12,
	ITEM_TM13,
	ITEM_TM14,
	ITEM_TM15,
	ITEM_TM16,
	ITEM_TM17,
	ITEM_TM18,
	ITEM_TM19,
	ITEM_TM20,
	ITEM_TM21,
	ITEM_TM22,
	ITEM_TM23,
	ITEM_TM24,
	ITEM_TM25,
	ITEM_TM26,
	ITEM_TM27,
	ITEM_TM28,
	ITEM_TM29,
	ITEM_TM30,
	ITEM_TM31,
	ITEM_TM32,
	ITEM_TM33,
	ITEM_TM34,
	ITEM_TM35,
	ITEM_TM36,
	ITEM_TM37,
	ITEM_TM38,
	ITEM_TM39,
	ITEM_TM40,
	ITEM_TM41,
	ITEM_TM42,
	ITEM_TM43,
	ITEM_TM44,
	ITEM_TM45,
	ITEM_TM46,
	ITEM_TM47,
	ITEM_TM48,
	ITEM_TM49,
	ITEM_TM50,
	ITEM_TM51,
	ITEM_TM52,
	ITEM_TM53,
	ITEM_TM54,
	ITEM_TM55,
	ITEM_TM56,
	ITEM_TM57,
	ITEM_TM58,
	ITEM_TM59,
	ITEM_TM60,
	ITEM_TM61,
	ITEM_TM62,
	ITEM_TM63,
	ITEM_TM64,
	ITEM_TM65,
	ITEM_TM66,
	ITEM_TM67,
	ITEM_TM68,
	ITEM_TM69,
	ITEM_TM70,
	ITEM_TM71,
	ITEM_TM72,
	ITEM_TM73,
	ITEM_TM74,
	ITEM_TM75,
	ITEM_TM76,
	ITEM_TM77,
	ITEM_TM78,
	ITEM_TM79,
	ITEM_TM80,
	ITEM_TM81,
	ITEM_TM82,
	ITEM_TM83,
	ITEM_TM84,
	ITEM_TM85,
	ITEM_TM86,
	ITEM_TM87,
	ITEM_TM88,
	ITEM_TM89,
	ITEM_TM90,
	ITEM_TM91,
	ITEM_TM92,
	ITEM_HM_NORMAL,
	ITEM_HM_FLYING,
	ITEM_HM_WATER,
	ITEM_HM_NORMAL,
	ITEM_HM_WATER,
	ITEM_MASTER_BALL,
	ITEM_EXPLORER_KIT,
	ITEM_LOOT_SACK,
	ITEM_RULE_BOOK,
	ITEM_POKE_RADAR,
	ITEM_POINT_CARD,
	ITEM_JOURNAL,
	ITEM_SEAL_CASE,
	ITEM_FASHION_CASE,
	ITEM_SEAL_BAG,
	ITEM_PAL_PAD,
	ITEM_WORKS_KEY,
	ITEM_OLD_CHARM,
	ITEM_GALACTIC_KEY,
	ITEM_RED_CHAIN,
	ITEM_TOWN_MAP,
	ITEM_VS_SEEKER,
	ITEM_COIN_CASE,
	ITEM_OLD_ROD,
	ITEM_GOOD_ROD,
	ITEM_SUPER_ROD,
	ITEM_SPRAYDUCK,
	ITEM_POFFIN_CASE,
	ITEM_BICYCLE_GREEN,
	ITEM_BICYCLE_GREEN,
	ITEM_SUITE_KEY,
	ITEM_OAKS_LETTER,
	ITEM_LUNAR_WING,
	ITEM_MEMBER_CARD,
	ITEM_AZURE_FLUTE,
	ITEM_SS_TICKET,
	ITEM_CONTEST_PASS,
	ITEM_MAGMA_STONE,
	ITEM_PARCEL,
	ITEM_COUPON_1,
	ITEM_COUPON_2,
	ITEM_COUPON_3,
	ITEM_STORAGE_KEY,
	ITEM_SECRETPOTION,
	ITEM_VS_RECORDER,
	ITEM_GRACIDEA,
	ITEM_SECRET_KEY,
	ITEM_APRICORN_BOX,
	ITEM_UNOWN_REPORT,
	ITEM_BERRY_POTS,
	ITEM_DOWSING_MACHINE_XY,
	ITEM_DOWSING_MACHINE_ORAS,
	ITEM_BLUE_CARD,
	ITEM_SLOWPOKETAIL,
	ITEM_CLEAR_BELL,
	ITEM_CARD_KEY,
	ITEM_BASEMENT_KEY,
	ITEM_SQUIRTBOTTLE,
	ITEM_RED_SCALE,
	ITEM_LOST_ITEM,
	ITEM_PASS,
	ITEM_MACHINE_PART,
	ITEM_SILVER_WING,
	ITEM_RAINBOW_WING,
	ITEM_MYSTERY_EGG,
	ITEM_RED_APRICORN,
	ITEM_YLW_APRICORN,
	ITEM_BLU_APRICORN,
	ITEM_GRN_APRICORN,
	ITEM_PNK_APRICORN,
	ITEM_WHT_APRICORN,
	ITEM_BLK_APRICORN,
	ITEM_FAST_BALL,
	ITEM_LEVEL_BALL,
	ITEM_LURE_BALL,
	ITEM_HEAVY_BALL,
	ITEM_LOVE_BALL,
	ITEM_FRIEND_BALL,
	ITEM_MOON_BALL,
	ITEM_SPORT_BALL,
	ITEM_PARK_BALL,
	ITEM_PHOTO_ALBUM,
	ITEM_GB_SOUNDS,
	ITEM_TIDAL_BELL,
	ITEM_RAGE_CANDY_BAR,
	ITEM_DATA_CARD,
	ITEM_DATA_CARD1,
	ITEM_DATA_CARD2,
	ITEM_DATA_CARD3,
	ITEM_DATA_CARD4,
	ITEM_DATA_CARD5,
	ITEM_DATA_CARD6,
	ITEM_DATA_CARD7,
	ITEM_DATA_CARD8,
	ITEM_DATA_CARD9,
	ITEM_DATA_CARDA,
	ITEM_DATA_CARDB,
	ITEM_DATA_CARDC,
	ITEM_DATA_CARDD,
	ITEM_DATA_CARDE,
	ITEM_DATA_CARDF,
	ITEM_DATA_CARD10,
	ITEM_DATA_CARD11,
	ITEM_DATA_CARD12,
	ITEM_DATA_CARD13,
	ITEM_DATA_CARD14,
	ITEM_DATA_CARD15,
	ITEM_DATA_CARD16,
	ITEM_DATA_CARD17,
	ITEM_DATA_CARD18,
	ITEM_DATA_CARD19,
	ITEM_DATA_CARD1A,
	ITEM_JADE_ORB,
	ITEM_LOCK_CAPSULE,
	ITEM_RED_ORB,
	ITEM_BLUE_ORB,
	ITEM_ENIGMA_STONE,
	ITEM_PRISM_SCALE,
	ITEM_EVIOLITE,
	ITEM_FLOAT_STONE,
	ITEM_ROCKY_HELMET,
	ITEM_AIR_BALLOON,
	ITEM_RED_CARD,
	ITEM_RING_TARGET,
	ITEM_BINDING_BAND,
	ITEM_ABSORB_BULB,
	ITEM_CELL_BATTERY,
	ITEM_EJECT_BUTTON,
	ITEM_FIRE_GEM,
	ITEM_WATER_GEM,
	ITEM_ELECTRIC_GEM,
	ITEM_GRASS_GEM,
	ITEM_ICE_GEM,
	ITEM_FIGHTING_GEM,
	ITEM_POISON_GEM,
	ITEM_GROUND_GEM,
	ITEM_FLYING_GEM,
	ITEM_PSYCHIC_GEM,
	ITEM_BUG_GEM,
	ITEM_ROCK_GEM,
	ITEM_GHOST_GEM,
	ITEM_DRAGON_GEM,
	ITEM_DARK_GEM,
	ITEM_STEEL_GEM,
	ITEM_NORMAL_GEM,
	ITEM_HEALTH_WING,
	ITEM_MUSCLE_WING,
	ITEM_RESIST_WING,
	ITEM_GENIUS_WING,
	ITEM_CLEVER_WING,
	ITEM_SWIFT_WING,
	ITEM_PRETTY_WING,
	ITEM_COVER_FOSSIL,
	ITEM_PLUME_FOSSIL,
	ITEM_LIBERTY_PASS,
	ITEM_PASS_ORB,
	ITEM_DREAM_BALL,
	ITEM_POKE_TOY,
	ITEM_PROP_CASE,
	ITEM_DRAGON_SKULL,
	ITEM_BALM_MUSHROOM,
	ITEM_BIG_NUGGET,
	ITEM_PEARL_STRING,
	ITEM_COMET_SHARD,
	ITEM_RELIC_COPPER,
	ITEM_RELIC_SILVER,
	ITEM_RELIC_GOLD,
	ITEM_RELIC_VASE,
	ITEM_RELIC_BAND,
	ITEM_RELIC_STATUE,
	ITEM_RELIC_CROWN,
	ITEM_CASTELIACONE,
	ITEM_DIRE_HIT_2,
	ITEM_X_SPEED_2,
	ITEM_X_SPECIAL_2,
	ITEM_X_SP_DEF_2,
	ITEM_X_DEFEND_2,
	ITEM_X_ATTACK_2,
	ITEM_X_ACCURACY_2,
	ITEM_X_SPEED_3,
	ITEM_X_SPECIAL_3,
	ITEM_X_SP_DEF_3,
	ITEM_X_DEFEND_3,
	ITEM_X_ATTACK_3,
	ITEM_X_ACCURACY_3,
	ITEM_X_SPEED_6,
	ITEM_X_SPECIAL_6,
	ITEM_X_SP_DEF_6,
	ITEM_X_DEFEND_6,
	ITEM_X_ATTACK_6,
	ITEM_X_ACCURACY_6,
	ITEM_ABILITY_URGE,
	ITEM_ITEM_DROP,
	ITEM_ITEM_URGE,
	ITEM_RESET_URGE,
	ITEM_DIRE_HIT_3,
	ITEM_LIGHT_STONE,
	ITEM_DARK_STONE,
	ITEM_TM93,
	ITEM_TM94,
	ITEM_TM94,
	ITEM_TM95,
	ITEM_B2W2_XTRANSCEIVER_M,
	ITEM_GOD_STONE,
	ITEM_B2W2_XTRANSCEIVER_F,
	ITEM_MEDAL_BOX,
	ITEM_DNA_SPLICERS,
	ITEM_DNA_SPLICERS2,
	ITEM_PERMIT,
	ITEM_OVAL_CHARM,
	ITEM_SHINY_CHARM,
	ITEM_PLASMA_CARD,
	ITEM_GRUBBY_HANKY,
	ITEM_COLRESS_MCHN,
	ITEM_DROPPED_ITEM_M,
	ITEM_DROPPED_ITEM_F,
	ITEM_REVEAL_GLASS,
	ITEM_WEAKNESS_POLICY,
	ITEM_ASSAULT_VEST,
	ITEM_HOLO_CASTER_GREEN,
	ITEM_PROFS_LETTER,
	ITEM_ROLLER_SKATES,
	ITEM_PIXIE_PLATE,
	ITEM_ABILITY_CAPSULE,
	ITEM_WHIPPED_DREAM,
	ITEM_SACHET,
	ITEM_LUMINOUS_MOSS,
	ITEM_SNOWBALL,
	ITEM_SAFETY_GOGGLES,
	ITEM_POKE_FLUTE,
	ITEM_RICH_MULCH,
	ITEM_SURPRISE_MULCH,
	ITEM_BOOST_MULCH,
	ITEM_AMAZE_MULCH,
	ITEM_GENGARITE,
	ITEM_GARDEVOIRITE,
	ITEM_AMPHAROSITE,
	ITEM_VENUSAURITE,
	ITEM_CHARIZARDITE_X,
	ITEM_BLASTOISINITE,
	ITEM_MEWTWONITE_X,
	ITEM_MEWTWONITE_Y,
	ITEM_BLAZIKENITE,
	ITEM_MEDICHAMITE,
	ITEM_HOUNDOOMINITE,
	ITEM_AGGRONITE,
	ITEM_BANETTITE,
	ITEM_TYRANITARITE,
	ITEM_SCIZORITE,
	ITEM_PINSIRITE,
	ITEM_AERODACTYLITE,
	ITEM_LUCARIONITE,
	ITEM_ABOMASITE,
	ITEM_KANGASKHANITE,
	ITEM_GYARADOSITE,
	ITEM_ABSOLITE,
	ITEM_CHARIZARDITE_Y,
	ITEM_ALAKAZITE,
	ITEM_HERACRONITE,
	ITEM_MAWILITE,
	ITEM_MANECTITE,
	ITEM_GARCHOMPITE,
	ITEM_LATIASITE,
	ITEM_LATIOSITE,
	ITEM_ROSELI_BERRY,
	ITEM_KEE_BERRY,
	ITEM_MARANGA_BERRY,
	ITEM_SPRINKLOTAD,
	ITEM_TM96,
	ITEM_TM97,
	ITEM_TM98,
	ITEM_TM100,
	ITEM_POWER_PLANT_PASS,
	ITEM_MEGA_RING,
	ITEM_INTRIGUING_STONE,
	ITEM_COMMON_STONE,
	ITEM_DISCOUNT_COUPON,
	ITEM_ELEVATOR_KEY,
	ITEM_TMV_PASS,
	ITEM_HONOR_OF_KALOS,
	ITEM_ADVENTURE_RULES,
	ITEM_STRANGE_SOUVENIR,
	ITEM_LENS_CASE,
	ITEM_TRAVEL_TRUNK_SILVER,
	ITEM_TRAVEL_TRUNK_GOLD,
	ITEM_LUMIOSE_GALETTE,
	ITEM_SHALOUR_SABLE,
	ITEM_JAW_FOSSIL,
	ITEM_SAIL_FOSSIL,
	ITEM_LOOKER_TICKET,
	ITEM_BICYCLE_YELLOW,
	ITEM_BICYCLE_YELLOW,
	ITEM_HOLO_CASTER_RED,
	ITEM_FAIRY_GEM,
	ITEM_MEGA_CHARM,
	ITEM_MACH_BIKE,
	ITEM_ACRO_BIKE,
	ITEM_WAILMER_PAIL,
	ITEM_DEVON_GOODS,
	ITEM_SOOT_SACK,
	ITEM_BASEMENT_KEY_III,
	ITEM_POKEBLOCK_KIT,
	ITEM_LETTER,
	ITEM_EON_TICKET,
	ITEM_SCANNER,
	ITEM_GO_GOGGLES,
	ITEM_METEORITE,
	ITEM_RM_1_KEY,
	ITEM_RM_2_KEY,
	ITEM_RM_4_KEY,
	ITEM_RM_6_KEY,
	ITEM_STORAGE_KEY2,
	ITEM_DEVON_SCOPE,
	ITEM_SS_TICKET2,
	ITEM_DEVON_SCUBA_GEAR,
	ITEM_CONTEST_COSTUME_M,
	ITEM_CONTEST_COSTUME_F,
	ITEM_MAGMA_SUIT,
	ITEM_AQUA_SUIT,
	ITEM_PAIR_OF_TICKETS,
	ITEM_MEGA_BRACELET,
	ITEM_MEGA_PENDANT,
	ITEM_MEGA_GLASSES,
	ITEM_MEGA_ANCHOR,
	ITEM_MEGA_STICKPIN,
	ITEM_MEGA_TIARA,
	ITEM_MEGA_ANKLET,
	ITEM_METEORITE_2,
	ITEM_SWAMPERTITE,
	ITEM_SCEPTILITE,
	ITEM_SABLENITE,
	ITEM_ALTARIANITE,
	ITEM_GALLADITE,
	ITEM_AUDINITE,
	ITEM_METAGROSSITE,
	ITEM_SHARPEDONITE,
	ITEM_SLOWBRONITE,
	ITEM_STEELIXITE,
	ITEM_PIDGEOTITE,
	ITEM_GLALITITE,
	ITEM_DIANCITE,
	ITEM_PRISON_BOTTLE,
	ITEM_MEGA_CUFF,
	ITEM_CAMERUPTITE,
	ITEM_LOPUNNITE,
	ITEM_SALAMENCITE,
	ITEM_BEEDRILLITE,
	ITEM_METEORITE_3,
	ITEM_METEORITE_4,
	ITEM_KEY_STONE,
	ITEM_METEORITE_SHARD,
	ITEM_EON_FLUTE,
};*/


#endif /* ITEM_IDS_H */
