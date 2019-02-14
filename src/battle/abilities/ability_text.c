#include <pokeagb/pokeagb.h>

//Abilities Name

const pchar ability_names[][17] = {
    _("-------"),
    _("Stench"),
    _("Drizzle"),
    _("Speed Boost"),
    _("Battle Armor"),
    _("Sturdy"),
    _("Damp"),
    _("Limber"),
    _("Sand Veil"),
    _("Static"),
    _("Volt Absorb"),
    _("Water Absorb"),
    _("Oblivious"),
    _("Cloud Nine"),
    _("Compound Eyes"),
    _("Insomnia"),
    _("Color Change"),
    _("Immunity"),
    _("Flash Fire"),
    _("Shield Dust"),
    _("Own Tempo"),
    _("Suction Cups"),
    _("Intimidate"),
    _("Shadow Tag"),
    _("Rough Skin"),
    _("Wonder Guard"),
    _("Levitate"),
    _("Effect Spore"),
    _("Synchronize"),
    _("Clear Body"),
    _("Natural Cure"),
    _("Lightning Rod"),
    _("Serene Grace"),
    _("Swift Swim"),
    _("Chlorophyll"),
    _("Illuminate"),
    _("Trace"),
    _("Huge Power"),
    _("Poison Point"),
    _("Inner Focus"),
    _("Magma Armor"),
    _("Water Veil"),
    _("Magnet Pull"),
    _("Soundproof"),
    _("Rain Dish"),
    _("Sand Stream"),
    _("Pressure"),
    _("Thick Fat"),
    _("Early Bird"),
    _("Flame Body"),
    _("Run Away"),
    _("Keen Eye"),
    _("Hyper Cutter"),
    _("Pickup"),
    _("Truant"),
    _("Hustle"),
    _("Cute Charm"),
    _("Plus"),
    _("Minus"),
    _("Forecast"),
    _("Sticky Hold"),
    _("Shed Skin"),
    _("Guts"),
    _("Marvel Scale"),
    _("Liquid Ooze"),
    _("Overgrow"),
    _("Blaze"),
    _("Torrent"),
    _("Swarm"),
    _("Rock Head"),
    _("Drought"),
    _("Arena Trap"),
    _("Vital Spirit"),
    _("White Smoke"),
    _("Pure Power"),
    _("Shell Armor"),
    _("Air Lock"),
    _("Tangled Feet"),
    _("Motor Drive"),
    _("Rivalry"),
    _("Steadfast"),
    _("Snow Cloak"),
    _("Gluttony"),
    _("Anger Point"),
    _("Unburden"),
    _("Heatproof"),
    _("Simple"),
    _("Dry Skin"),
    _("Download"),
    _("Iron Fist"),
    _("Poison Heal"),
    _("Adaptability"),
    _("Skill Link"),
    _("Hydration"),
    _("Solar Power"),
    _("Quick Feet"),
    _("Normalize"),
    _("Sniper"),
    _("Magic Guard"),
    _("No Guard"),
    _("Stall"),
    _("Technician"),
    _("Leaf Guard"),
    _("Klutz"),
    _("Mold Breaker"),
    _("Super Luck"),
    _("Aftermath"),
    _("Anticipation"),
    _("Forewarn"),
    _("Unaware"),
    _("Tinted Lens"),
    _("Filter"),
    _("Slow Start"),
    _("Scrappy"),
    _("Storm Drain"),
    _("Ice Body"),
    _("Solid Rock"),
    _("Snow Warning"),
    _("Honey Gather"),
    _("Frisk"),
    _("Reckless"),
    _("Multitype"),
    _("Flower Gift"),
    _("Bad Dreams"),
    _("Pickpocket"),
    _("Sheer Force"),
    _("Contrary"),
    _("Unnerve"),
    _("Defiant"),
    _("Defeatist"),
    _("Cursed Body"),
    _("Healer"),
    _("Friend Guard"),
    _("Weak Armor"),
    _("Heavy Metal"),
    _("Light Metal"),
    _("Multiscale"),
    _("Toxic Boost"),
    _("Flare Boost"),
    _("Harvest"),
    _("Telepathy"),
    _("Moody"),
    _("Overcoat"),
    _("Poison Touch"),
    _("Regenerator"),
    _("Big Pecks"),
    _("Sand Rush"),
    _("Wonder Skin"),
    _("Analytic"),
    _("Illusion"),
    _("Imposter"),
    _("Infiltrator"),
    _("Mummy"),
    _("Moxie"),
    _("Justified"),
    _("Rattled"),
    _("Magic Bounce"),
    _("Sap Sipper"),
    _("Prankster"),
    _("Sand Force"),
    _("Iron Barbs"),
    _("Zen Mode"),
    _("Victory Star"),
    _("Turboblaze"),
    _("Teravolt"),
    _("Aroma Veil"),
    _("Flower Veil"),
    _("Cheek Pouch"),
    _("Protean"),
    _("Fur Coat"),
    _("Magician"),
    _("Bulletproof"),
    _("Competitive"),
    _("Strong Jaw"),
    _("Refrigerate"),
    _("Sweet Veil"),
    _("Stance Change"),
    _("Gale Wings"),
    _("Mega Launcher"),
    _("Grass Pelt"),
    _("Symbiosis"),
    _("Tough Claws"),
    _("Pixilate"),
    _("Gooey"),
    _("Aerilate"),
    _("Parental Bond"),
    _("Dark Aura"),
    _("Fairy Aura"),
    _("Aura Break"),
    _("Primordial Sea"),
    _("Desolate Land"),
    _("Delta Stream"),
    _("Stamina"),
    _("Wimp Out"),
    _("Emergency Exit"),
    _("Water Compacton"),
    _("Merciless"),
    _("Shields Down"),
    _("Stakeout"),
    _("Water Bubble"),
    _("Steelworker"),
    _("Berserk"),
    _("Slush Rush"),
    _("Long Reach"),
    _("Liquid Voice"),
    _("Triage"),
    _("Galvanize"),
    _("Surge Surfer"),
    _("Schooling"),
    _("Disguise"),
    _("Battle Bond"),
    _("Power Construct"),
    _("Corrosion"),
    _("Comatose"),
    _("Queenly Majesty"),
    _("Innards Out"),
    _("Dancer"),
    _("Battery"),
    _("Fluffy"),
    _("Dazzling"),
    _("Soul-Heart"),
    _("Tanglng Hair"),
    _("Receiver"),
    _("Power of Alchemy"),
    _("Beast Boost"),
    _("RKS System"),
    _("Electric Surge"),
    _("Psychic Surge"),
    _("Misty Surge"),
    _("Grassy Surge"),
    _("Full Metal Body"),
    _("Shadow Shield"),
    _("Prism Armor"),
    _("Neuroforce")
};


// ABILITIES DESCRIPTION

pchar des_no_ability[] = _("No special ability.");
pchar des_Stench[] = _("Helps repel wild POKéMON.");
pchar des_Drizzle[] = _("Summons rain in battle.");
pchar des_Speed_Boost[] = _("Gradually boosts SPEED.");
pchar des_Battle_Armor[] = _("Blocks critical hits.");
pchar des_Sturdy[] = _("Negates 1-hit KO attacks.");
pchar des_Damp[] = _("Prevents self-destruction.");
pchar des_Limber[] = _("Prevents paralysis.");
pchar des_Sand_Veil[] = _("Ups evasion in a sandstorm.");
pchar des_Static[] = _("Paralyzes on contact.");
pchar des_Volt_Absorb[] = _("Turns electricity into HP.");
pchar des_Water_Absorb[] = _("Changes water into HP.");
pchar des_Oblivious[] = _("Prevents attraction.");
pchar des_Cloud_Nine[] = _("Negates weather effects.");
pchar des_Compoundeyes[] = _("Raises accuracy.");
pchar des_Insomnia[] = _("Prevents sleep.");
pchar des_Color_Change[] = _("Changes type to foe‘s move.");
pchar des_Immunity[] = _("Prevents poisoning.");
pchar des_Flash_Fire[] = _("Powers up if hit by fire.");
pchar des_Shield_Dust[] = _("Prevents added effects.");
pchar des_Own_Tempo[] = _("Prevents confusion.");
pchar des_Suction_Cups[] = _("Firmly anchors the body.");
pchar des_Intimidate[] = _("Lowers the foe‘s ATTACK.");
pchar des_Shadow_Tag[] = _("Prevents the foe‘s escape.");
pchar des_Rough_Skin[] = _("Hurts to touch.");
pchar des_Wonder_Guard[] = _("”Super effective“ hits.");
pchar des_Levitate[] = _("Not hit by GROUND attacks.");
pchar des_Effect_Spore[] = _("Leaves spores on contact.");
pchar des_Synchronize[] = _("Passes on status problems.");
pchar des_Clear_Body[] = _("Prevents ability reduction.");
pchar des_Natural_Cure[] = _("Heals upon switching out.");
pchar des_Lightningrod[] = _("Draws electrical moves.");
pchar des_Serene_Grace[] = _("Promotes added effects.");
pchar des_Swift_Swim[] = _("Raises SPEED in rain.");
pchar des_Chlorophyll[] = _("Raises SPEED in sunshine.");
pchar des_Illuminate[] = _("Encounter rate increases.");
pchar des_Trace[] = _("Copies special ability.");
pchar des_Huge_Power[] = _("Raises ATTACK.");
pchar des_Poison_Point[] = _("Poisons foe on contact.");
pchar des_Inner_Focus[] = _("Prevents flinching.");
pchar des_Magma_Armor[] = _("Prevents freezing.");
pchar des_Water_Veil[] = _("Prevents burns.");
pchar des_Magnet_Pull[] = _("Traps STEEL-type POKéMON.");
pchar des_Soundproof[] = _("Avoids sound-based moves.");
pchar des_Rain_Dish[] = _("Slight HP recovery in rain.");
pchar des_Sand_Stream[] = _("Summons a sandstorm.");
pchar des_Pressure[] = _("Raises foe‘s PP usage.");
pchar des_Thick_Fat[] = _("Heat-and-cold protection.");
pchar des_Early_Bird[] = _("Awakens quickly from sleep.");
pchar des_Flame_Body[] = _("Burns the foe on contact.");
pchar des_Run_Away[] = _("Makes escaping easier.");
pchar des_Keen_Eye[] = _("Prevents loss of accuracy.");
pchar des_Hyper_Cutter[] = _("Prevents ATTACK reduction.");
pchar des_Pickup[] = _("May pick up items.");
pchar des_Truant[] = _("Moves only every two turns.");
pchar des_Hustle[] = _("Trades accuracy for power.");
pchar des_Cute_Charm[] = _("Infatuates on contact.");
pchar des_Plus[] = _("Powers up with MINUS.");
pchar des_Minus[] = _("Powers up with PLUS.");
pchar des_Forecast[] = _("Changes with the weather.");
pchar des_Sticky_Hold[] = _("Prevents item theft.");
pchar des_Shed_Skin[] = _("Heals the body by shedding.");
pchar des_Guts[] = _("Ups ATTACK if suffering.");
pchar des_Marvel_Scale[] = _("Ups DEFENSE if suffering.");
pchar des_Liquid_Ooze[] = _("Draining causes injury.");
pchar des_Overgrow[] = _("Ups GRASS moves in a pinch.");
pchar des_Blaze[] = _("Ups FIRE moves in a pinch.");
pchar des_Torrent[] = _("Ups WATER moves in a pinch.");
pchar des_Swarm[] = _("Ups BUG moves in a pinch.");
pchar des_Rock_Head[] = _("Prevents recoil damage.");
pchar des_Drought[] = _("Summons sunlight in battle.");
pchar des_Arena_Trap[] = _("Prevents fleeing.");
pchar des_Vital_Spirit[] = _("Prevents sleep.");
pchar des_White_Smoke[] = _("Prevents ability reduction.");
pchar des_Pure_Power[] = _("Raises ATTACK.");
pchar des_Shell_Armor[] = _("Blocks critical hits.");
pchar des_Air_Lock[] = _("Negates weather effects.");
pchar des_tangled_feet[] = _("Ups evasion if confused.");
pchar des_motor_drive[] = _("Electricity boosts Speed.");
pchar des_rivalry[] = _("Powers up against rivals.");
pchar des_steadfast[] = _("Flinching boosts Speed.");
pchar des_snow_cloak[] = _("Ups evasion in hail.");
pchar des_gluttony[] = _("Eats Berries early.");
pchar des_anger_point[] = _("Critical hits boost Attack.");
pchar des_unburden[] = _("Using a hold item ups Speed.");
pchar des_hearproof[] = _("Heat and burn protection.");
pchar des_simple[] = _("Prone to wild stat changes.");
pchar des_dry_skin[] = _("Prefers moisture to hear.");
pchar des_download[] = _("Adjusts power favorably.");
pchar des_iron_fist[] = _("Boosts punching moves.");
pchar des_poison_heal[] = _("Restores HP if poisoned.");
pchar des_adaptability[] = _("Boosts same type attacks.");
pchar des_skill_link[] = _("Multi hit moves hit 5 times.");
pchar des_hydration[] = _("Cures status in rain.");
pchar des_solar_power[] = _("Powers up in sunshine.");
pchar des_quick_feet[] = _("Ups Speed if suffering.");
pchar des_normalize[] = _("Moves become Normal type.");
pchar des_sniper[] = _("Boosts critical hits.");
pchar des_magic_guard[] = _("Only damaged by attacks.");
pchar des_no_guard[] = _("Ensures that all moves hit.");
pchar des_stall[] = _("Always moves last.");
pchar des_technician[] = _("Boosts weaker moves.");
pchar des_leaf_guard[] = _("Blocks status in sunshine.");
pchar des_klutz[] = _("Can‘t use hold items.");
pchar des_mold_breaker[] = _("Moves hit through abilities.");
pchar des_super_luck[] = _("Critical hits land often.");
pchar des_aftermath[] = _("Fainting damages the foe.");
pchar des_anticipation[] = _("Senses dangerous moves.");
pchar des_forewarn[] = _("Determines a foe‘s move.");
pchar des_unaware[] = _("Ignores stat changes.");
pchar des_tinted_lens[] = _("Ups ”not very effective“.");
pchar des_filter[] = _("Weakens ”Super effective“.");
pchar des_slow_Start[] = _("Takes a while to get going.");
pchar des_scrappy[] = _("Hits ghosts type pokémon.");
pchar des_storm_drain[] = _("Draws in Water moves.");
pchar des_solid_rock[] = _("Weakens ”Super effective“.");
pchar des_ice_body[] = _("Slight HP recovery in hail.");
pchar des_snow_warning[] = _("Summons a hailstorm.");
pchar des_honey_gather[] = _("May gather Honey.");
pchar des_frisk[] = _("Checks a foe‘s held item.");
pchar des_reckless[] = _("Boosts moves with recoil.");
pchar des_multitype[] = _("Changes type to its plate.");
pchar des_flower_gift[] = _("Transforms in sunshine.");
pchar des_bad_dreams[] = _("Damages sleeping Pokémon.");
pchar des_pickpocket[] = _("Steals the foe‘s hold item.");
pchar des_sheer_force[] = _("Trades effects for power.");
pchar des_contrary[] = _("Inverts stat changes.");
pchar des_unnerve[] = _("Foes can‘t eat Berries.");
pchar des_defiant[] = _("Lowered stats up Attack.");
pchar des_defeatist[] = _("Gives up at half HP.");
pchar des_cursed_body[] = _("Disables move on contact.");
pchar des_healer[] = _("Heals partner Pokémon.");
pchar des_friend_guard[] = _("Lowers damage to partners.");
pchar des_weak_armor[] = _("Its stats change when hit.");
pchar des_heavy_metal[] = _("Doubles weight.");
pchar des_light_metal[] = _("Halves weight.");
pchar des_multiscale[] = _("Halves damage at full HP.");
pchar des_toxic_boost[] = _("Ups Attack if poisoned.");
pchar des_flare_boost[] = _("Ups Sp.Atk if burned.");
pchar des_harvest[] = _("May recycle a used Berry.");
pchar des_Telepathy[] = _("Can‘t be damaged by an ally.");
pchar des_moody[] = _("Stats change gradually.");
pchar des_overcoat[] = _("Blocks weather and powder.");
pchar des_poison_touch[] = _("Poison target on contact.");
pchar des_regenerator[] = _("Restores HP with withdrawn.");
pchar des_big_pecks[] = _("Prevents Degense loss.");
pchar des_sand_rush[] = _("Ups Speed in a sandstorm.");
pchar des_wonder_skin[] = _("May avoid status problems.");
pchar des_analytic[] = _("Moving last boosts power.");
pchar des_illusion[] = _("Appears as a partner.");
pchar des_imposter[] = _("Transforms into the foe.");
pchar des_infiltrator[] = _("Passes through barriers.");
pchar des_mummy[] = _("Spreads with contact.");
pchar des_moxie[] = _("KOs raise Attack.");
pchar des_justified[] = _("Dark hits up Attack.");
pchar des_rattled[] = _("Raises Speed when scared.");
pchar des_magic_bounce[] = _("Reflects status moves.");
pchar des_sap_sipper[] = _("Turns grass into Attack,");
pchar des_prankster[] = _("Status moves fo first.");
pchar des_sand_force[] = _("Powers up in a sandstorm.");
pchar des_iron_barbs[] = _("Hit Attacker on contact.");
pchar des_zen_mode[] = _("Transforms at half HP.");
pchar des_victory_star[] = _("Boost accuracy of team.");
pchar des_turboblaze[] = _("Moves hit through abilities.");
pchar des_teravolt[] = _("Moves hit through abilities.");
pchar des_aroma_veil[] = _("Prevents limiting of moves.");
pchar des_flower_veil[] = _("Protects Grass types.");
pchar des_cheek_pouch[] = _("Eating Berries restores HP.");
pchar des_protean[] = _("Changes type to used move.");
pchar des_fur_coat[] = _("Raises Defense");
pchar des_magician[] = _("Steals the foe‘s hold item.");
pchar des_bulletproof[] = _("Avoids some projectiles.");
pchar des_competative[] = _("Lowered stats up Sp.Atk");
pchar des_strong_jaw[] = _("Boosts biting moves.");
pchar des_refrigerate[] = _("Normal moves become Ice.");
pchar des_sweet_veil[] = _("Prevent team from sleeping.");
pchar des_stance_change[] = _("Transforms as it battles.");
pchar des_gale_wings[] = _("Flying moves go first.");
pchar des_mega_launcher[] = _("Boosts pulse moves.");
pchar des_grass_pelt[] = _("Ups Defense in Grass.");
pchar des_symbiosis[] = _("Passes its item to an ally.");
pchar des_touch_claws[] = _("Boosts contact moves.");
pchar des_pixilate[] = _("Normal moves become Fairy.");
pchar des_gooey[] = _("Lowers Speed on contact.");
pchar des_aerilate[] = _("Normal moves become Flying.");
pchar des_parental_bond[] = _("Moves hit twice.");
pchar des_dark_aura[] = _("Boosts Dark moves.");
pchar des_fairy_aura[]= _("Boosts Fairy moves.");
pchar des_aura_break[] = _("Reverses aura abilities.");
pchar des_stamina[] = _("Boosts defense when hit.");
pchar des_wimp_out[] = _("Flees at half HP.");
pchar des_water_compaction[] = _("Water boosts defense.");
pchar des_merciless[] = _("Criticals poisoned foes.");
pchar des_shields_down[] = _("Shell breaks at half HP.");
pchar des_stakeout[] = _("Stronger as foes switch in.");
pchar des_water_bubble[] = _("Guards from fire and burn.");
pchar des_steelworker[] = _("Powers up stell move.");
pchar des_berserk[] = _("Boosts Sp.Atk at low HP");
pchar des_slush_rush[] = _("Raises Speed in hail.");
pchar des_long_reach[] = _("Never makes contact.");
pchar des_liquid_voice[] = _("Makes sound moves water.");
pchar des_triage[] = _("Healing moves go first.");
pchar des_galvanize[] = _("Normal moves turn electric");
pchar des_surge_super[] = _("Faster on electricity.");
pchar des_schooling[] = _("Forms a school when strong");
pchar des_disguise[] = _("Decoy protects it once.");
pchar des_battle_bond[] = _("Changes form after a KO.");
pchar des_power_construct[] = _("Cells aid it when weakened.");
pchar des_corrosion[] = _("Poisons any type.");
pchar des_comatose[] = _("Always drowsing");
pchar des_queenly_majesty[] = _("Protects from priority");
pchar des_innards_out[] = _("Hurts foe when defeated");
pchar des_dancer[] = _("Dances along with others.");
pchar des_battery[] = _("Boosts ally‘s SP.Atk");
pchar des_fluffy[] = _("Tougher but Flammable.");
pchar des_soul_heart[] = _("SP.Atk up after a KO.");
pchar des_receiver[] = _("Copies ally‘s ability.");
pchar des_beast_boost[] = _("KOs boost best stats.");
pchar des_RKS_system[] = _("Memories change it type.");
pchar des_electric_surge[] = _("Field become electric.");
pchar des_psychic_surge[] = _("Field become weird.");
pchar des_misty_surge[] = _("Field become misty.");
pchar des_grass_surge[] = _("Field become grassy.");
pchar des_full_metal_body[] = _("Stats aren‘t reduced.");
pchar des_neuroforce[] = _("Supereffective moves power increased");


// THE DESCRIPTION POINTER TABLE
void* ability_descriptions[] =
{
    &des_no_ability,
    &des_Stench,
    &des_Drizzle,
    &des_Speed_Boost,
    &des_Battle_Armor,
    &des_Sturdy,
    &des_Damp,
    &des_Limber,
    &des_Sand_Veil,
    &des_Static,
    &des_Volt_Absorb,
    &des_Water_Absorb,
    &des_Oblivious,
    &des_Cloud_Nine,
    &des_Compoundeyes,
    &des_Insomnia,
    &des_Color_Change,
    &des_Immunity,
    &des_Flash_Fire,
    &des_Shield_Dust,
    &des_Own_Tempo,
    &des_Suction_Cups,
    &des_Intimidate,
    &des_Shadow_Tag,
    &des_Rough_Skin,
    &des_Wonder_Guard,
    &des_Levitate,
    &des_Effect_Spore,
    &des_Synchronize,
    &des_Clear_Body,
    &des_Natural_Cure,
    &des_Lightningrod,
    &des_Serene_Grace,
    &des_Swift_Swim,
    &des_Chlorophyll,
    &des_Illuminate,
    &des_Trace,
    &des_Huge_Power,
    &des_Poison_Point,
    &des_Inner_Focus,
    &des_Magma_Armor,
    &des_Water_Veil,
    &des_Magnet_Pull,
    &des_Soundproof,
    &des_Rain_Dish,
    &des_Sand_Stream,
    &des_Pressure,
    &des_Thick_Fat,
    &des_Early_Bird,
    &des_Flame_Body,
    &des_Run_Away,
    &des_Keen_Eye,
    &des_Hyper_Cutter,
    &des_Pickup,
    &des_Truant,
    &des_Hustle,
    &des_Cute_Charm,
    &des_Plus,
    &des_Minus,
    &des_Forecast,
    &des_Sticky_Hold,
    &des_Shed_Skin,
    &des_Guts,
    &des_Marvel_Scale,
    &des_Liquid_Ooze,
    &des_Overgrow,
    &des_Blaze,
    &des_Torrent,
    &des_Swarm,
    &des_Rock_Head,
    &des_Drought,
    &des_Arena_Trap,
    &des_Vital_Spirit,
    &des_White_Smoke,
    &des_Pure_Power,
    &des_Shell_Armor,
    &des_Air_Lock,
    &des_tangled_feet,
    &des_motor_drive,
    &des_rivalry,
    &des_steadfast,
    &des_snow_cloak,
    &des_gluttony,
    &des_anger_point,
    &des_unburden,
    &des_hearproof,
    &des_simple,
    &des_dry_skin,
    &des_download,
    &des_iron_fist,
    &des_poison_heal,
    &des_adaptability,
    &des_skill_link,
    &des_hydration,
    &des_solar_power,
    &des_quick_feet,
    &des_normalize,
    &des_sniper,
    &des_magic_guard,
    &des_no_guard,
    &des_stall,
    &des_technician,
    &des_leaf_guard,
    &des_klutz,
    &des_mold_breaker,
    &des_super_luck,
    &des_aftermath,
    &des_anticipation,
    &des_forewarn,
    &des_unaware,
    &des_tinted_lens,
    &des_filter,
    &des_slow_Start,
    &des_scrappy,
    &des_storm_drain,
    &des_solid_rock,
    &des_ice_body,
    &des_snow_warning,
    &des_honey_gather,
    &des_frisk,
    &des_reckless,
    &des_multitype,
    &des_flower_gift,
    &des_bad_dreams,
    &des_pickpocket,
    &des_sheer_force,
    &des_contrary,
    &des_unnerve,
    &des_defiant,
    &des_defeatist,
    &des_cursed_body,
    &des_healer,
    &des_friend_guard,
    &des_weak_armor,
    &des_heavy_metal,
    &des_light_metal,
    &des_multiscale,
    &des_toxic_boost,
    &des_flare_boost,
    &des_harvest,
    &des_Telepathy,
    &des_moody,
    &des_overcoat,
    &des_poison_touch,
    &des_regenerator,
    &des_big_pecks,
    &des_sand_rush,
    &des_wonder_skin,
    &des_analytic,
    &des_illusion,
    &des_imposter,
    &des_infiltrator,
    &des_mummy,
    &des_moxie,
    &des_justified,
    &des_rattled,
    &des_magic_bounce,
    &des_sap_sipper,
    &des_prankster,
    &des_sand_force,
    &des_iron_barbs,
    &des_zen_mode,
    &des_victory_star,
    &des_turboblaze,
    &des_teravolt,
    &des_aroma_veil,
    &des_flower_veil,
    &des_cheek_pouch,
    &des_protean,
    &des_fur_coat,
    &des_magician,
    &des_bulletproof,
    &des_competative,
    &des_strong_jaw,
    &des_refrigerate,
    &des_sweet_veil,
    &des_stance_change,
    &des_gale_wings,
    &des_mega_launcher,
    &des_grass_pelt,
    &des_symbiosis,
    &des_touch_claws,
    &des_pixilate,
    &des_gooey,
    &des_aerilate,
    &des_parental_bond,
    &des_dark_aura,
    &des_fairy_aura,
    &des_aura_break,
    &des_stamina,
    &des_wimp_out,
    &des_water_compaction,
    &des_merciless,
    &des_shields_down,
    &des_stakeout,
    &des_water_bubble,
    &des_steelworker,
    &des_berserk,
    &des_slush_rush,
    &des_long_reach,
    &des_liquid_voice,
    &des_triage,
    &des_galvanize,
    &des_surge_super,
    &des_schooling,
    &des_disguise,
    &des_battle_bond,
    &des_power_construct,
    &des_corrosion,
    &des_comatose,
    &des_queenly_majesty,
    &des_innards_out,
    &des_dancer,
    &des_battery,
    &des_fluffy,
    &des_soul_heart,
    &des_receiver,
    &des_beast_boost,
    &des_RKS_system,
    &des_electric_surge,
    &des_psychic_surge,
    &des_misty_surge,
    &des_grass_surge,
    &des_full_metal_body,
    &des_neuroforce
};
