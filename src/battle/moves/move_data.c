#include <pokeagb/pokeagb.h>
#include "moves.h"
#include "move_data.h"
#include "../items/items.h"


pchar Pound_desc[] = _("No additional effect.");
pchar Karate_Chop_desc[] = _("High critical hit ratio.");
pchar Double_Slap_desc[] = _("Hits 2-5 times in one turn.");
pchar Comet_Punch_desc[] = _("Hits 2-5 times in one turn.");
pchar Mega_Punch_desc[] = _("No additional effect.");
pchar Pay_Day_desc[] = _("Scatters coins.");
pchar Fire_Punch_desc[] = _("10% chance to burn the target.");
pchar Ice_Punch_desc[] = _("10% chance to freeze the target.");
pchar Thunder_Punch_desc[] = _("10% chance to paralyze the target.");
pchar Scratch_desc[] = _("No additional effect.");
pchar Vice_Grip_desc[] = _("No additional effect.");
pchar Guillotine_desc[] = _("OHKOs the target. Fails if user is a lower level.");
pchar Razor_Wind_desc[] = _("Charges then hits foe(s) turn 2. High crit ratio.");
pchar Swords_Dance_desc[] = _("Raises the user‘s Attack by 2.");
pchar Cut_desc[] = _("No additional effect.");
pchar Gust_desc[] = _("Power doubles during Fly Bounce and Sky Drop.");
pchar Wing_Attack_desc[] = _("No additional effect.");
pchar Whirlwind_desc[] = _("Forces the target to switch to a random ally.");
pchar Fly_desc[] = _("Flies up on first turn then strikes the next turn.");
pchar Bind_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Slam_desc[] = _("No additional effect.");
pchar Vine_Whip_desc[] = _("No additional effect.");
pchar Stomp_desc[] = _("30% chance to flinch the target.");
pchar Double_Kick_desc[] = _("Hits 2 times in one turn.");
pchar Mega_Kick_desc[] = _("No additional effect.");
pchar Jump_Kick_desc[] = _("User is hurt by 50% of its max HP if it misses.");
pchar Rolling_Kick_desc[] = _("30% chance to flinch the target.");
pchar Sand_Attack_desc[] = _("Lowers the target‘s accuracy by 1.");
pchar Headbutt_desc[] = _("30% chance to flinch the target.");
pchar Horn_Attack_desc[] = _("No additional effect.");
pchar Fury_Attack_desc[] = _("Hits 2-5 times in one turn.");
pchar Horn_Drill_desc[] = _("OHKOs the target. Fails if user is a lower level.");
pchar Tackle_desc[] = _("No additional effect.");
pchar Body_Slam_desc[] = _("30% chance to paralyze the target.");
pchar Wrap_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Take_Down_desc[] = _("Has 1/4 recoil.");
pchar Thrash_desc[] = _("Lasts 2-3 turns. Confuses the user afterwards.");
pchar Double_Edge_desc[] = _("Has 33% recoil.");
pchar Tail_Whip_desc[] = _("Lowers the foe(s) Defense by 1.");
pchar Poison_Sting_desc[] = _("30% chance to poison the target.");
pchar Twineedle_desc[] = _("Hits 2 times. Each hit has 20% chance to poison.");
pchar Pin_Missile_desc[] = _("Hits 2-5 times in one turn.");
pchar Leer_desc[] = _("Lowers the foe(s) Defense by 1.");
pchar Bite_desc[] = _("30% chance to flinch the target.");
pchar Growl_desc[] = _("Lowers the foe(s) Attack by 1.");
pchar Roar_desc[] = _("Forces the target to switch to a random ally.");
pchar Sing_desc[] = _("Puts the target to sleep.");
pchar Supersonic_desc[] = _("Confuses the target.");
pchar Sonic_Boom_desc[] = _("Always does 20 HP of damage.");
pchar Disable_desc[] = _("For 4 turns disables the target‘s last move used.");
pchar Acid_desc[] = _("10% chance to lower the foe(s) Sp. Def by 1.");
pchar Ember_desc[] = _("10% chance to burn the target.");
pchar Flamethrower_desc[] = _("10% chance to burn the target.");
pchar Mist_desc[] = _("For 5 turns protects user‘s party from stat drops.");
pchar Water_Gun_desc[] = _("No additional effect.");
pchar Hydro_Pump_desc[] = _("No additional effect.");
pchar Surf_desc[] = _("Hits adjacent Pokemon. Power doubles on Dive.");
pchar Ice_Beam_desc[] = _("10% chance to freeze the target.");
pchar Blizzard_desc[] = _("10% chance to freeze the foe(s).");
pchar Psybeam_desc[] = _("10% chance to confuse the target.");
pchar Bubble_Beam_desc[] = _("10% chance to lower the target‘s Speed by 1.");
pchar Aurora_Beam_desc[] = _("10% chance to lower the foe‘s Attack by 1.");
pchar Hyper_Beam_desc[] = _("User cannot move next turn.");
pchar Peck_desc[] = _("No additional effect.");
pchar Drill_Peck_desc[] = _("No additional effect.");
pchar Submission_desc[] = _("Has 1/4 recoil.");
pchar Low_Kick_desc[] = _("More power the heavier the target.");
pchar Counter_desc[] = _("If hit by physical attack returns double damage.");
pchar Seismic_Toss_desc[] = _("Does damage equal to the user‘s level.");
pchar Strength_desc[] = _("No additional effect.");
pchar Absorb_desc[] = _("User recovers 50% of the damage dealt.");
pchar Mega_Drain_desc[] = _("User recovers 50% of the damage dealt.");
pchar Leech_Seed_desc[] = _("1/8 of target‘s HP is restored to user every turn.");
pchar Growth_desc[] = _("Raises user‘s Attack and SpAtk by 1, or 2 in Sun.");
pchar Razor_Leaf_desc[] = _("High critical hit ratio. Hits adjacent foes.");
pchar Solar_Beam_desc[] = _("Charges turn 1. Hits turn 2. No charge in sunlight.");
pchar Poison_Powder_desc[] = _("Poisons the target.");
pchar Stun_Spore_desc[] = _("Paralyzes the target.");
pchar Sleep_Powder_desc[] = _("Puts the target to sleep.");
pchar Petal_Dance_desc[] = _("Lasts 2-3 turns. Confuses the user afterwards.");
pchar String_Shot_desc[] = _("Lowers the foe(s) Speed by 2.");
pchar Dragon_Rage_desc[] = _("Always does 40 HP of damage.");
pchar Fire_Spin_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Thunder_Shock_desc[] = _("10% chance to paralyze the target.");
pchar Thunderbolt_desc[] = _("10% chance to paralyze the target.");
pchar Thunder_Wave_desc[] = _("Paralyzes the target.");
pchar Thunder_desc[] = _("30% chance to paralyze target. Can‘t miss in rain.");
pchar Rock_Throw_desc[] = _("No additional effect.");
pchar Earthquake_desc[] = _("Hits adjacent Pokemon. Power doubles on Dig.");
pchar Fissure_desc[] = _("OHKOs the target. Fails if user is a lower level.");
pchar Dig_desc[] = _("Digs underground turn 1 strikes turn 2.");
pchar Toxic_desc[] = _("Badly poisons the target.");
pchar Confusion_desc[] = _("10% chance to confuse the target.");
pchar Psychic_desc[] = _("10% chance to lower the target‘s Sp. Def by 1.");
pchar Hypnosis_desc[] = _("Puts the target to sleep.");
pchar Meditate_desc[] = _("Raises the user‘s Attack by 1.");
pchar Agility_desc[] = _("Raises the user‘s Speed by 2.");
pchar Quick_Attack_desc[] = _("Usually goes first.");
pchar Rage_desc[] = _("Raises the user‘s Attack by 1 if hit during use.");
pchar Teleport_desc[] = _("Flee from wild Pokemon battles.");
pchar Night_Shade_desc[] = _("Does damage equal to the user‘s level.");
pchar Mimic_desc[] = _("The last move the target used replaces this one.");
pchar Screech_desc[] = _("Lowers the target‘s Defense by 2.");
pchar Double_Team_desc[] = _("Raises the user‘s evasiveness by 1.");
pchar Recover_desc[] = _("Heals the user by 50% of its max HP.");
pchar Harden_desc[] = _("Raises the user‘s Defense by 1.");
pchar Minimize_desc[] = _("Raises the user‘s evasiveness by 2.");
pchar Smokescreen_desc[] = _("Lowers the target‘s accuracy by 1.");
pchar Confuse_Ray_desc[] = _("Confuses the target.");
pchar Withdraw_desc[] = _("Raises the user‘s Defense by 1.");
pchar Defense_Curl_desc[] = _("Raises the user‘s Defense by 1.");
pchar Barrier_desc[] = _("Raises the user‘s Defense by 2.");
pchar Light_Screen_desc[] = _("For 5 turns special damage to allies is halved.");
pchar Haze_desc[] = _("Eliminates all stat changes.");
pchar Reflect_desc[] = _("For 5 turns physical damage to allies is halved.");
pchar Focus_Energy_desc[] = _("Raises the user‘s critical hit ratio by 2.");
pchar Bide_desc[] = _("Waits 2 turns- deals double the damage taken.");
pchar Metronome_desc[] = _("Picks a random move.");
pchar Mirror_Move_desc[] = _("User uses the target‘s last used move against it.");
pchar Self_Destruct_desc[] = _("Hits adjacent Pokemon. The user faints.");
pchar Egg_Bomb_desc[] = _("No additional effect.");
pchar Lick_desc[] = _("30% chance to paralyze the target.");
pchar Smog_desc[] = _("40% chance to poison the target.");
pchar Sludge_desc[] = _("30% chance to poison the target.");
pchar Bone_Club_desc[] = _("10% chance to flinch the target.");
pchar Fire_Blast_desc[] = _("10% chance to burn the target.");
pchar Waterfall_desc[] = _("20% chance to flinch the target.");
pchar Clamp_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Swift_desc[] = _("This move does not check accuracy. Hits foes.");
pchar Skull_Bash_desc[] = _("Raises user‘s Defense by 1 on turn 1. Hits turn 2.");
pchar Spike_Cannon_desc[] = _("Hits 2-5 times in one turn.");
pchar Constrict_desc[] = _("10% chance to lower the target‘s Speed by 1.");
pchar Amnesia_desc[] = _("Raises the user‘s Sp. Def by 2.");
pchar Kinesis_desc[] = _("Lowers the target‘s accuracy by 1.");
pchar Soft_Boiled_desc[] = _("Heals the user by 50% of its max HP.");
pchar High_Jump_Kick_desc[] = _("User is hurt by 50% of its max HP if it misses.");
pchar Glare_desc[] = _("Paralyzes the target.");
pchar Dream_Eater_desc[] = _("User gains 1/2 HP inflicted. Sleeping target only.");
pchar Poison_Gas_desc[] = _("Poisons the foe(s).");
pchar Barrage_desc[] = _("Hits 2-5 times in one turn.");
pchar Leech_Life_desc[] = _("User recovers 50% of the damage dealt.");
pchar Lovely_Kiss_desc[] = _("Puts the target to sleep.");
pchar Sky_Attack_desc[] = _("Charges then hits turn 2. 30% flinch. High crit.");
pchar Transform_desc[] = _("Copies target‘s stats moves types and Ability.");
pchar Bubble_desc[] = _("10% chance to lower the foe(s) Speed by 1.");
pchar Dizzy_Punch_desc[] = _("20% chance to confuse the target.");
pchar Spore_desc[] = _("Puts the target to sleep.");
pchar Flash_desc[] = _("Lowers the target‘s accuracy by 1.");
pchar Psywave_desc[] = _("Random damage equal to 0.5x-1.5x user‘s level.");
pchar Splash_desc[] = _("Does nothing (but we still love it).");
pchar Acid_Armor_desc[] = _("Raises the user‘s Defense by 2.");
pchar Crabhammer_desc[] = _("High critical hit ratio.");
pchar Explosion_desc[] = _("Hits adjacent Pokemon. The user faints.");
pchar Fury_Swipes_desc[] = _("Hits 2-5 times in one turn.");
pchar Bonemerang_desc[] = _("Hits 2 times in one turn.");
pchar Rest_desc[] = _("User sleeps 2 turns and restores HP and status.");
pchar Rock_Slide_desc[] = _("30% chance to flinch the foe(s).");
pchar Hyper_Fang_desc[] = _("10% chance to flinch the target.");
pchar Sharpen_desc[] = _("Raises the user‘s Attack by 1.");
pchar Conversion_desc[] = _("Changes user‘s type to match its first move.");
pchar Tri_Attack_desc[] = _("20% chance to paralyze or burn or freeze target.");
pchar Super_Fang_desc[] = _("Does damage equal to 1/2 target‘s current HP.");
pchar Slash_desc[] = _("High critical hit ratio.");
pchar Substitute_desc[] = _("User takes 1/4 its max HP to put in a Substitute.");
pchar Struggle_desc[] = _("User loses 25% of its max HP as recoil.");
pchar Sketch_desc[] = _("Permanently copies the last move target used.");
pchar Triple_Kick_desc[] = _("Hits 3 times. Each hit can miss but power rises.");
pchar Thief_desc[] = _("If the user has no item it steals the target‘s.");
pchar Spider_Web_desc[] = _("The target cannot switch out.");
pchar Mind_Reader_desc[] = _("User‘s next move will not miss the target.");
pchar Nightmare_desc[] = _("A sleeping target is hurt by 1/4 max HP per turn.");
pchar Flame_Wheel_desc[] = _("10% chance to burn the target. Thaws user.");
pchar Snore_desc[] = _("User must be asleep. 30% chance to flinch target.");
pchar Curse_desc[] = _("Curses if Ghost else +1 Atk +1 Def -1 Spe.");
pchar Flail_desc[] = _("More power the less HP the user has left.");
pchar Conversion_2_desc[] = _("Changes user‘s type to resist target‘s last move.");
pchar Aeroblast_desc[] = _("High critical hit ratio.");
pchar Cotton_Spore_desc[] = _("Lowers the target‘s Speed by 2.");
pchar Reversal_desc[] = _("More power the less HP the user has left.");
pchar Spite_desc[] = _("Lowers the PP of the target‘s last move by 4.");
pchar Powder_Snow_desc[] = _("10% chance to freeze the foe(s).");
pchar Protect_desc[] = _("Prevents moves from affecting the user this turn.");
pchar Mach_Punch_desc[] = _("Usually goes first.");
pchar Scary_Face_desc[] = _("Lowers the target‘s Speed by 2.");
pchar Feint_Attack_desc[] = _("This move does not check accuracy.");
pchar Sweet_Kiss_desc[] = _("Confuses the target.");
pchar Belly_Drum_desc[] = _("User loses 50% max HP. Maximizes Attack.");
pchar Sludge_Bomb_desc[] = _("30% chance to poison the target.");
pchar Mud_Slap_desc[] = _("100% chance to lower the target‘s accuracy by 1.");
pchar Octazooka_desc[] = _("50% chance to lower the target‘s accuracy by 1.");
pchar Spikes_desc[] = _("Hurts grounded foes on switch-in. Max 3 layers.");
pchar Zap_Cannon_desc[] = _("100% chance to paralyze the target.");
pchar Foresight_desc[] = _("Fighting Normal hit Ghost. Evasiveness ignored.");
pchar Destiny_Bond_desc[] = _("If an opponent knocks out the user it also faints.");
pchar Perish_Song_desc[] = _("All active Pokemon will faint in 3 turns.");
pchar Icy_Wind_desc[] = _("100% chance to lower the foe(s) Speed by 1.");
pchar Detect_desc[] = _("Prevents moves from affecting the user this turn.");
pchar Bone_Rush_desc[] = _("Hits 2-5 times in one turn.");
pchar Lock_On_desc[] = _("User‘s next move will not miss the target.");
pchar Outrage_desc[] = _("Lasts 2-3 turns. Confuses the user afterwards.");
pchar Sandstorm_desc[] = _("For 5 turns a sandstorm rages.");
pchar Giga_Drain_desc[] = _("User recovers 50% of the damage dealt.");
pchar Endure_desc[] = _("The user survives the next hit with at least 1 HP.");
pchar Charm_desc[] = _("Lowers the target‘s Attack by 2.");
pchar Rollout_desc[] = _("Power doubles with each hit. Repeats for 5 turns.");
pchar False_Swipe_desc[] = _("Always leaves the target with at least 1 HP.");
pchar Swagger_desc[] = _("Raises the target‘s Attack by 2 and confuses it.");
pchar Milk_Drink_desc[] = _("Heals the user by 50% of its max HP.");
pchar Spark_desc[] = _("30% chance to paralyze the target.");
pchar Fury_Cutter_desc[] = _("Power doubles with each hit up to 160.");
pchar Steel_Wing_desc[] = _("10% chance to raise the user‘s Defense by 1.");
pchar Mean_Look_desc[] = _("The target cannot switch out.");
pchar Attract_desc[] = _("A target of the opposite gender gets infatuated.");
pchar Sleep_Talk_desc[] = _("User must be asleep. Uses another known move.");
pchar Heal_Bell_desc[] = _("Cures the user‘s party of all status conditions.");
pchar Return_desc[] = _("Max 102 power at maximum Happiness.");
pchar Present_desc[] = _("40 80 120 power or heals target by 1/4 max HP.");
pchar Frustration_desc[] = _("Max 102 power at minimum Happiness.");
pchar Safeguard_desc[] = _("For 5 turns protects user‘s party from status.");
pchar Pain_Split_desc[] = _("Shares HP of user and target equally.");
pchar Sacred_Fire_desc[] = _("50% chance to burn the target. Thaws user.");
pchar Magnitude_desc[] = _("Hits adjacent Pokemon. Power varies- 2x on Dig.");
pchar Dynamic_Punch_desc[] = _("100% chance to confuse the target.");
pchar Megahorn_desc[] = _("No additional effect.");
pchar Dragon_Breath_desc[] = _("30% chance to paralyze the target.");
pchar Baton_Pass_desc[] = _("User switches passing stat changes and more.");
pchar Encore_desc[] = _("The target repeats its last move for 3 turns.");
pchar Pursuit_desc[] = _("Power doubles if a foe is switching out.");
pchar Rapid_Spin_desc[] = _("Frees user from hazards/partial trap/Leech Seed.");
pchar Sweet_Scent_desc[] = _("Lowers the foe(s) evasion by 2.");
pchar Iron_Tail_desc[] = _("30% chance to lower the target‘s Defense by 1.");
pchar Metal_Claw_desc[] = _("10% chance to raise the user‘s Attack by 1.");
pchar Vital_Throw_desc[] = _("This move does not check accuracy. Goes last.");
pchar Morning_Sun_desc[] = _("Heals the user by a weather-dependent amount.");
pchar Synthesis_desc[] = _("Heals the user by a weather-dependent amount.");
pchar Moonlight_desc[] = _("Heals the user by a weather-dependent amount.");
pchar Hidden_Power_desc[] = _("Varies in type based on the user‘s IVs.");
pchar Cross_Chop_desc[] = _("High critical hit ratio.");
pchar Twister_desc[] = _("20% chance to flinch the foe(s).");
pchar Rain_Dance_desc[] = _("For 5 turns heavy rain powers Water moves.");
pchar Sunny_Day_desc[] = _("For 5 turns intense sunlight powers Fire moves.");
pchar Crunch_desc[] = _("20% chance to lower the target‘s Defense by 1.");
pchar Mirror_Coat_desc[] = _("If hit by special attack returns double damage.");
pchar Psych_Up_desc[] = _("Copies the target‘s current stat stages.");
pchar Extreme_Speed_desc[] = _("Nearly always goes first.");
pchar Ancient_Power_desc[] = _("10% chance to raise all stats by 1 (not acc/eva).");
pchar Shadow_Ball_desc[] = _("20% chance to lower the target‘s Sp. Def by 1.");
pchar Future_Sight_desc[] = _("Hits two turns after being used.");
pchar Rock_Smash_desc[] = _("50% chance to lower the target‘s Defense by 1.");
pchar Whirlpool_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Beat_Up_desc[] = _("All healthy allies aid in damaging the target.");
pchar Fake_Out_desc[] = _("Hits first. First turn out only. 100% flinch chance.");
pchar Uproar_desc[] = _("Lasts 3 turns. Active Pokemon cannot fall asleep.");
pchar Stockpile_desc[] = _("Raises user‘s Defense Sp. Def by 1. Max 3 uses.");
pchar Spit_Up_desc[] = _("More power with more uses of Stockpile.");
pchar Swallow_desc[] = _("Heals the user based on uses of Stockpile.");
pchar Heat_Wave_desc[] = _("10% chance to burn the foe(s).");
pchar Hail_desc[] = _("For 5 turns hail crashes down.");
pchar Torment_desc[] = _("Target can‘t select the same move twice in a row.");
pchar Flatter_desc[] = _("Raises the target‘s Sp. Atk by 1 and confuses it.");
pchar Will_O_Wisp_desc[] = _("Burns the target.");
pchar Memento_desc[] = _("Lowers target‘s Attack Sp. Atk by 2. User faints.");
pchar Facade_desc[] = _("Power doubles if user is burn/poison/paralyzed.");
pchar Focus_Punch_desc[] = _("Fails if the user takes damage before it hits.");
pchar Smelling_Salts_desc[] = _("Power doubles if target is paralyzed and cures it.");
pchar Follow_Me_desc[] = _("The foes‘ moves target the user on the turn used.");
pchar Nature_Power_desc[] = _("Attack depends on terrain (default Tri Attack).");
pchar Charge_desc[] = _("Boosts next Electric move and user‘s Sp. Def by 1.");
pchar Taunt_desc[] = _("For 3 turns the target can‘t use status moves.");
pchar Helping_Hand_desc[] = _("One adjacent ally‘s move power is 1.5x this turn.");
pchar Trick_desc[] = _("User switches its held item with the target‘s.");
pchar Role_Play_desc[] = _("User replaces its Ability with the target‘s.");
pchar Wish_desc[] = _("Next turn 50% of the user‘s max HP is restored.");
pchar Assist_desc[] = _("Uses a random move known by a team member.");
pchar Ingrain_desc[] = _("User recovers 1/16 max HP per turn. Traps user.");
pchar Superpower_desc[] = _("Lowers the user‘s Attack and Defense by 1.");
pchar Magic_Coat_desc[] = _("Bounces back certain non-damaging moves.");
pchar Recycle_desc[] = _("Restores the item the user last used.");
pchar Revenge_desc[] = _("Power doubles if user is damaged by the target.");
pchar Brick_Break_desc[] = _("Destroys screens unless the target is immune.");
pchar Yawn_desc[] = _("Puts the target to sleep after 1 turn.");
pchar Knock_Off_desc[] = _("1.5x damage if foe holds an item. Removes item.");
pchar Endeavor_desc[] = _("Lowers the target‘s HP to the user‘s HP.");
pchar Eruption_desc[] = _("Less power as user‘s HP decreases. Hits foe(s).");
pchar Skill_Swap_desc[] = _("The user and the target trade Abilities.");
pchar Imprison_desc[] = _("No foe can use any move known by the user.");
pchar Refresh_desc[] = _("User cures its burn poison or paralysis.");
pchar Grudge_desc[] = _("If the user faints the attack used loses all its PP.");
pchar Snatch_desc[] = _("User steals certain support moves to use itself.");
pchar Secret_Power_desc[] = _("Effect varies with terrain, 30% paralysis chance");
pchar Dive_desc[] = _("Dives underwater turn 1 strikes turn 2.");
pchar Arm_Thrust_desc[] = _("Hits 2-5 times in one turn.");
pchar Camouflage_desc[] = _("Changes user‘s type by terrain (default Normal).");
pchar Tail_Glow_desc[] = _("Raises the user‘s Sp. Atk by 3.");
pchar Luster_Purge_desc[] = _("50% chance to lower the target‘s Sp. Def by 1.");
pchar Mist_Ball_desc[] = _("50% chance to lower the target‘s Sp. Atk by 1.");
pchar Feather_Dance_desc[] = _("Lowers the target‘s Attack by 2.");
pchar Teeter_Dance_desc[] = _("Confuses adjacent Pokemon.");
pchar Blaze_Kick_desc[] = _("High critical hit ratio. 10% chance to burn.");
pchar Mud_Sport_desc[] = _("For 5 turns Electric-type attacks have 1/3 power.");
pchar Ice_Ball_desc[] = _("Power doubles with each hit. Repeats for 5 turns.");
pchar Needle_Arm_desc[] = _("30% chance to flinch the target.");
pchar Slack_Off_desc[] = _("Heals the user by 50% of its max HP.");
pchar Hyper_Voice_desc[] = _("No additional effect. Hits adjacent foes.");
pchar Poison_Fang_desc[] = _("50% chance to badly poison the target.");
pchar Crush_Claw_desc[] = _("50% chance to lower the target‘s Defense by 1.");
pchar Blast_Burn_desc[] = _("User cannot move next turn.");
pchar Hydro_Cannon_desc[] = _("User cannot move next turn.");
pchar Meteor_Mash_desc[] = _("20% chance to raise the user‘s Attack by 1.");
pchar Astonish_desc[] = _("30% chance to flinch the target.");
pchar Weather_Ball_desc[] = _("Power doubles and type varies in each weather.");
pchar Aromatherapy_desc[] = _("Cures the user‘s party of all status conditions.");
pchar Fake_Tears_desc[] = _("Lowers the target‘s Sp. Def by 2.");
pchar Air_Cutter_desc[] = _("High critical hit ratio. Hits adjacent foes.");
pchar Overheat_desc[] = _("Lowers the user‘s Sp. Atk by 2.");
pchar Odor_Sleuth_desc[] = _("Fighting Normal hit Ghost. Evasiveness ignored.");
pchar Rock_Tomb_desc[] = _("100% chance to lower the target‘s Speed by 1.");
pchar Silver_Wind_desc[] = _("10% chance to raise all stats by 1 (not acc/eva).");
pchar Metal_Sound_desc[] = _("Lowers the target‘s Sp. Def by 2.");
pchar Grass_Whistle_desc[] = _("Puts the target to sleep.");
pchar Tickle_desc[] = _("Lowers the target‘s Attack and Defense by 1.");
pchar Cosmic_Power_desc[] = _("Raises the user‘s Defense and Sp. Def by 1.");
pchar Water_Spout_desc[] = _("Less power as user‘s HP decreases. Hits foe(s).");
pchar Signal_Beam_desc[] = _("10% chance to confuse the target.");
pchar Shadow_Punch_desc[] = _("This move does not check accuracy.");
pchar Extrasensory_desc[] = _("10% chance to flinch the target.");
pchar Sky_Uppercut_desc[] = _("Can hit Pokemon using Bounce Fly or Sky Drop.");
pchar Sand_Tomb_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Sheer_Cold_desc[] = _("OHKOs non-Ice targets. Fails if user‘s lower level.");
pchar Muddy_Water_desc[] = _("30% chance to lower the foe(s) accuracy by 1.");
pchar Bullet_Seed_desc[] = _("Hits 2-5 times in one turn.");
pchar Aerial_Ace_desc[] = _("This move does not check accuracy.");
pchar Icicle_Spear_desc[] = _("Hits 2-5 times in one turn.");
pchar Iron_Defense_desc[] = _("Raises the user‘s Defense by 2.");
pchar Block_desc[] = _("The target cannot switch out.");
pchar Howl_desc[] = _("Raises the user‘s Attack by 1.");
pchar Dragon_Claw_desc[] = _("No additional effect.");
pchar Frenzy_Plant_desc[] = _("User cannot move next turn.");
pchar Bulk_Up_desc[] = _("Raises the user‘s Attack and Defense by 1.");
pchar Bounce_desc[] = _("Bounces turn 1. Hits turn 2. 30% paralyze.");
pchar Mud_Shot_desc[] = _("100% chance to lower the target‘s Speed by 1.");
pchar Poison_Tail_desc[] = _("High critical hit ratio. 10% chance to poison.");
pchar Covet_desc[] = _("If the user has no item it steals the target‘s.");
pchar Volt_Tackle_desc[] = _("Has 33% recoil. 10% chance to paralyze target.");
pchar Magical_Leaf_desc[] = _("This move does not check accuracy.");
pchar Water_Sport_desc[] = _("For 5 turns Fire-type attacks have 1/3 power.");
pchar Calm_Mind_desc[] = _("Raises the user‘s Sp. Atk and Sp. Def by 1.");
pchar Leaf_Blade_desc[] = _("High critical hit ratio.");
pchar Dragon_Dance_desc[] = _("Raises the user‘s Attack and Speed by 1.");
pchar Rock_Blast_desc[] = _("Hits 2-5 times in one turn.");
pchar Shock_Wave_desc[] = _("This move does not check accuracy.");
pchar Water_Pulse_desc[] = _("20% chance to confuse the target.");
pchar Doom_Desire_desc[] = _("Hits two turns after being used.");
pchar Psycho_Boost_desc[] = _("Lowers the user‘s Sp. Atk by 2.");


pchar Roost_desc[] = _("Heals 50% HP. Flying-type removed ‘til turn ends.");
pchar Gravity_desc[] = _("For 5 turns negates all Ground immunities.");
pchar Miracle_Eye_desc[] = _("Psychic hits Dark. Evasiveness ignored.");
pchar Wake_Up_Slap_desc[] = _("Power doubles if target is asleep and wakes it.");
pchar Hammer_Arm_desc[] = _("Lowers the user‘s Speed by 1.");
pchar Gyro_Ball_desc[] = _("More power the slower the user than the target.");
pchar Healing_Wish_desc[] = _("User faints. Replacement is fully healed.");
pchar Brine_desc[] = _("Power doubles if the target‘s HP is 50% or less.");
pchar Natural_Gift_desc[] = _("Power and type depends on the user‘s Berry.");
pchar Feint_desc[] = _("Nullifies Detect Protect and Quick/Wide Guard.");
pchar Pluck_desc[] = _("User steals and eats the target‘s Berry.");
pchar Tailwind_desc[] = _("For 4 turns allies‘ Speed is doubled.");
pchar Acupressure_desc[] = _("Raises a random stat of the user or an ally by 2.");
pchar Metal_Burst_desc[] = _("If hit by an attack returns 1.5x damage.");
pchar U_turn_desc[] = _("User switches out after damaging the target.");
pchar Close_Combat_desc[] = _("Lowers the user‘s Defense and Sp. Def by 1.");
pchar Payback_desc[] = _("Power doubles if the user moves after the target.");
pchar Assurance_desc[] = _("Power doubles if target was damaged this turn.");
pchar Embargo_desc[] = _("For 5 turns the target can‘t use any items.");
pchar Fling_desc[] = _("Flings the user‘s item at the target. Power varies.");
pchar Psycho_Shift_desc[] = _("Transfers the user‘s status ailment to the target.");
pchar Trump_Card_desc[] = _("More power the fewer PP this move has left.");
pchar Heal_Block_desc[] = _("For 5 turns the foe(s) is prevented from healing.");
pchar Wring_Out_desc[] = _("More power the more HP the target has left.");
pchar Power_Trick_desc[] = _("Switches user‘s Attack and Defense stats.");
pchar Gastro_Acid_desc[] = _("Nullifies the target‘s Ability.");
pchar Lucky_Chant_desc[] = _("For 5 turns shields user‘s party from critical hits.");
pchar Me_First_desc[] = _("Copies a foe at 1.5x power. User must be faster.");
pchar Copycat_desc[] = _("Uses the last move used in the battle.");
pchar Power_Swap_desc[] = _("Swaps Attack and Sp. Atk stat stages with target.");
pchar Guard_Swap_desc[] = _("Swaps Defense and Sp. Def changes with target.");
pchar Punishment_desc[] = _("60 power +20 for each of the target‘s stat boosts.");
pchar Last_Resort_desc[] = _("Fails unless each known move has been used.");
pchar Worry_Seed_desc[] = _("The target‘s Ability becomes Insomnia.");
pchar Sucker_Punch_desc[] = _("Usually goes first. Fails if target is not attacking.");
pchar Toxic_Spikes_desc[] = _("Poisons grounded foes on switch-in. Max 2 layers.");
pchar Aqua_Ring_desc[] = _("User recovers 1/16 max HP per turn.");
pchar Magnet_Rise_desc[] = _("For 5 turns the user is immune to Ground moves.");
pchar Flare_Blitz_desc[] = _("Has 33% recoil. 10% chance to burn. Thaws user.");
pchar Force_Palm_desc[] = _("30% chance to paralyze the target.");
pchar Aura_Sphere_desc[] = _("This move does not check accuracy.");
pchar Rock_Polish_desc[] = _("Raises the user‘s Speed by 2.");
pchar Poison_Jab_desc[] = _("30% chance to poison the target.");
pchar Dark_Pulse_desc[] = _("20% chance to flinch the target.");
pchar Night_Slash_desc[] = _("High critical hit ratio.");
pchar Aqua_Tail_desc[] = _("No additional effect.");
pchar Seed_Bomb_desc[] = _("No additional effect.");
pchar Air_Slash_desc[] = _("30% chance to flinch the target.");
pchar X_Scissor_desc[] = _("No additional effect.");
pchar Bug_Buzz_desc[] = _("10% chance to lower the target‘s Sp. Def. by 1.");
pchar Dragon_Pulse_desc[] = _("No additional effect.");
pchar Dragon_Rush_desc[] = _("20% chance to flinch the target.");
pchar Power_Gem_desc[] = _("No additional effect.");
pchar Drain_Punch_desc[] = _("User recovers 50% of the damage dealt.");
pchar Vacuum_Wave_desc[] = _("Usually goes first.");
pchar Focus_Blast_desc[] = _("10% chance to lower the target‘s Sp. Def by 1.");
pchar Energy_Ball_desc[] = _("10% chance to lower the target‘s Sp. Def. by 1.");
pchar Brave_Bird_desc[] = _("Has 33% recoil.");
pchar Earth_Power_desc[] = _("10% chance to lower the target‘s Sp. Def. by 1.");
pchar Switcheroo_desc[] = _("User switches its held item with the target‘s.");
pchar Giga_Impact_desc[] = _("User cannot move next turn.");
pchar Nasty_Plot_desc[] = _("Raises the user‘s Sp. Atk by 2.");
pchar Bullet_Punch_desc[] = _("Usually goes first.");
pchar Avalanche_desc[] = _("Power doubles if user is damaged by the target.");
pchar Ice_Shard_desc[] = _("Usually goes first.");
pchar Shadow_Claw_desc[] = _("High critical hit ratio.");
pchar Thunder_Fang_desc[] = _("10% chance to paralyze. 10% chance to flinch.");
pchar Ice_Fang_desc[] = _("10% chance to freeze. 10% chance to flinch.");
pchar Fire_Fang_desc[] = _("10% chance to burn. 10% chance to flinch.");
pchar Shadow_Sneak_desc[] = _("Usually goes first.");
pchar Mud_Bomb_desc[] = _("30% chance to lower the target‘s accuracy by 1.");
pchar Psycho_Cut_desc[] = _("High critical hit ratio.");
pchar Zen_Headbutt_desc[] = _("20% chance to flinch the target.");
pchar Mirror_Shot_desc[] = _("30% chance to lower the target‘s accuracy by 1.");
pchar Flash_Cannon_desc[] = _("10% chance to lower the target‘s Sp. Def by 1.");
pchar Rock_Climb_desc[] = _("20% chance to confuse the target.");
pchar Defog_desc[] = _("-1 evasion- clears user and target side‘s hazards.");
pchar Trick_Room_desc[] = _("For 5 turns slower Pokemon move first.");
pchar Draco_Meteor_desc[] = _("Lowers the user‘s Sp. Atk by 2.");
pchar Discharge_desc[] = _("30% chance to paralyze adjacent Pokemon.");
pchar Lava_Plume_desc[] = _("30% chance to burn adjacent Pokemon.");
pchar Leaf_Storm_desc[] = _("Lowers the user‘s Sp. Atk by 2.");
pchar Power_Whip_desc[] = _("No additional effect.");
pchar Rock_Wrecker_desc[] = _("User cannot move next turn.");
pchar Cross_Poison_desc[] = _("High critical hit ratio. 10% chance to poison.");
pchar Gunk_Shot_desc[] = _("30% chance to poison the target.");
pchar Iron_Head_desc[] = _("30% chance to flinch the target.");
pchar Magnet_Bomb_desc[] = _("This move does not check accuracy.");
pchar Stone_Edge_desc[] = _("High critical hit ratio.");
pchar Captivate_desc[] = _("Lowers the foe(s) Sp. Atk by 2 if opposite gender.");
pchar Stealth_Rock_desc[] = _("Hurts foes on switch-in. Factors Rock weakness.");
pchar Grass_Knot_desc[] = _("More power the heavier the target.");
pchar Bug_Bite_desc[] = _("User steals and eats the target‘s Berry.");
pchar Charge_Beam_desc[] = _("70% chance to raise the user‘s Sp. Atk by 1.");
pchar Wood_Hammer_desc[] = _("Has 33% recoil.");
pchar Aqua_Jet_desc[] = _("Usually goes first.");
pchar Attack_Order_desc[] = _("High critical hit ratio.");
pchar Defend_Order_desc[] = _("Raises the user‘s Defense and Sp. Def by 1.");
pchar Heal_Order_desc[] = _("Heals the user by 50% of its max HP.");
pchar Head_Smash_desc[] = _("Has 1/2 recoil.");
pchar Double_Hit_desc[] = _("Hits 2 times in one turn.");
pchar Magma_Storm_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Dark_Void_desc[] = _("Puts the foe(s) to sleep.");
pchar Ominous_Wind_desc[] = _("10% chance to raise all stats by 1 (not acc/eva).");
pchar Hone_Claws_desc[] = _("Raises the user‘s Attack and accuracy by 1.");
pchar Wide_Guard_desc[] = _("Protects allies from multi-target moves this turn.");
pchar Guard_Split_desc[] = _("Averages Defense and Sp. Def stats with target.");
pchar Power_Split_desc[] = _("Averages Attack and Sp. Atk stats with target.");
pchar Psyshock_desc[] = _("Damages target based on Defense not Sp. Def.");
pchar Venoshock_desc[] = _("Power doubles if the target is poisoned.");
pchar Autotomize_desc[] = _("Raises the user‘s Speed by 2- user loses 100 kg.");
pchar Rage_Powder_desc[] = _("The foes‘ moves target the user on the turn used.");
pchar Telekinesis_desc[] = _("For 3 turns target floats but moves can‘t miss it.");
pchar Magic_Room_desc[] = _("For 5 turns all held items have no effect.");
pchar Smack_Down_desc[] = _("Removes the target‘s Ground immunity.");
pchar Storm_Throw_desc[] = _("Always results in a critical hit.");
pchar Flame_Burst_desc[] = _("Damages Pokemon next to the target as well.");
pchar Sludge_Wave_desc[] = _("10% chance to poison adjacent Pokemon.");
pchar Quiver_Dance_desc[] = _("Raises the user‘s Sp. Atk Sp. Def Speed by 1.");
pchar Heavy_Slam_desc[] = _("More power the heavier the user than the target.");
pchar Synchronoise_desc[] = _("Hits adjacent Pokemon sharing the user‘s type.");
pchar Electro_Ball_desc[] = _("More power the faster the user is than the target.");
pchar Soak_desc[] = _("Changes the target‘s type to Water.");
pchar Flame_Charge_desc[] = _("100% chance to raise the user‘s Speed by 1.");
pchar Coil_desc[] = _("Raises user‘s Attack Defense and accuracy by 1.");
pchar Low_Sweep_desc[] = _("100% chance to lower the target‘s Speed by 1.");
pchar Acid_Spray_desc[] = _("100% chance to lower the target‘s Sp. Def by 2.");
pchar Foul_Play_desc[] = _("Uses target‘s Attack stat in damage calculation.");
pchar Simple_Beam_desc[] = _("The target‘s Ability becomes Simple.");
pchar Entrainment_desc[] = _("The target‘s Ability changes to match the user‘s.");
pchar After_You_desc[] = _("The target makes its move right after the user.");
pchar Round_desc[] = _("Power doubles if others used Round this turn.");
pchar Echoed_Voice_desc[] = _("Power increases when used on consecutive turns.");
pchar Chip_Away_desc[] = _("Ignores the target‘s stat stage changes.");
pchar Clear_Smog_desc[] = _("Eliminates the target‘s stat changes.");
pchar Stored_Power_desc[] = _(" + 20 power for each of the user‘s stat boosts.");
pchar Quick_Guard_desc[] = _("Protects allies from priority attacks this turn.");
pchar Scald_desc[] = _("30% chance to burn the target. Thaws target.");
pchar Shell_Smash_desc[] = _("Lowers Def SpD by 1- raises Atk SpA Spe by 2.");
pchar Heal_Pulse_desc[] = _("Heals the target by 50% of its max HP.");
pchar Hex_desc[] = _("Power doubles if the target has a status ailment.");
pchar Sky_Drop_desc[] = _("User and foe fly up turn 1. Damages on turn 2.");
pchar Circle_Throw_desc[] = _("Forces the target to switch to a random ally.");
pchar Incinerate_desc[] = _("Destroys the foe(s) Berry/Gem.");
pchar Quash_desc[] = _("Forces the target to move last this turn.");
pchar Acrobatics_desc[] = _("Power doubles if the user has no held item.");
pchar Reflect_Type_desc[] = _("User becomes the same type as the target.");
pchar Retaliate_desc[] = _("Power doubles if an ally fainted last turn.");
pchar Final_Gambit_desc[] = _("Does damage equal to the user‘s HP. User faints.");
pchar Bestow_desc[] = _("User passes its held item to the target.");
pchar Inferno_desc[] = _("100% chance to burn the target.");
pchar Volt_Switch_desc[] = _("User switches out after damaging the target.");
pchar Struggle_Bug_desc[] = _("100% chance to lower the foe(s) Sp. Atk by 1.");
pchar Bulldoze_desc[] = _("100% chance to lower adjacent Pkmn Speed by 1.");
pchar Frost_Breath_desc[] = _("Always results in a critical hit.");
pchar Dragon_Tail_desc[] = _("Forces the target to switch to a random ally.");
pchar Work_Up_desc[] = _("Raises the user‘s Attack and Sp. Atk by 1.");
pchar Electroweb_desc[] = _("100% chance to lower the foe(s) Speed by 1.");
pchar Wild_Charge_desc[] = _("Has 1/4 recoil.");
pchar Drill_Run_desc[] = _("High critical hit ratio.");
pchar Dual_Chop_desc[] = _("Hits 2 times in one turn.");
pchar Horn_Leech_desc[] = _("User recovers 50% of the damage dealt.");
pchar Sacred_Sword_desc[] = _("Ignores the target‘s stat stage changes.");
pchar Razor_Shell_desc[] = _("50% chance to lower the target‘s Defense by 1.");
pchar Leaf_Tornado_desc[] = _("50% chance to lower the target‘s accuracy by 1.");
pchar Steamroller_desc[] = _("30% chance to flinch the target.");
pchar Cotton_Guard_desc[] = _("Raises the user‘s Defense by 3.");
pchar Night_Daze_desc[] = _("40% chance to lower the target‘s accuracy by 1.");
pchar Psystrike_desc[] = _("Damages target based on Defense not Sp. Def.");
pchar Tail_Slap_desc[] = _("Hits 2-5 times in one turn.");
pchar Hurricane_desc[] = _("30% chance to confuse target. Can‘t miss in rain.");
pchar Head_Charge_desc[] = _("Has 1/4 recoil.");
pchar Fiery_Dance_desc[] = _("50% chance to raise the user‘s Sp. Atk by 1.");
pchar Icicle_Crash_desc[] = _("30% chance to flinch the target.");
pchar Flying_Press_desc[] = _("Combines Flying in its type effectiveness.");
pchar Belch_desc[] = _("Cannot be selected until the user eats a Berry.");
pchar Rototiller_desc[] = _("Raises Atk Sp. Atk of grounded Grass types by 1.");
pchar Sticky_Web_desc[] = _("Lowers Speed of grounded foes by 1 on switch-in.");
pchar Fell_Stinger_desc[] = _("Raises user‘s Attack by 3 if this KOes the target.");
pchar Phantom_Force_desc[] = _("Disappears turn 1. Hits turn 2. Breaks protection.");
pchar Noble_Roar_desc[] = _("Lowers the target‘s Attack and Sp. Atk by 1.");
pchar Ion_Deluge_desc[] = _("Normal moves become Electric type this turn.");
pchar Petal_Blizzard_desc[] = _("No additional effect. Hits adjacent Pokemon.");
pchar Freeze_Dry_desc[] = _("10% chance to freeze. Super effective on Water.");
pchar Disarming_Voice_desc[] = _("This move does not check accuracy. Hits foes.");
pchar Parting_Shot_desc[] = _("Lowers target‘s Atk Sp. Atk by 1. User switches.");
pchar Topsy_Turvy_desc[] = _("Inverts the target‘s stat stages.");
pchar Draining_Kiss_desc[] = _("User recovers 75% of the damage dealt.");
pchar Grassy_Terrain_desc[] = _("5 turns. Grounded: +Grass power+1/16 max HP.");
pchar Misty_Terrain_desc[] = _("5 turns. Can‘t status-Dragon power vs grounded.");
pchar Play_Rough_desc[] = _("10% chance to lower the target‘s Attack by 1.");
pchar Fairy_Wind_desc[] = _("No additional effect.");
pchar Moonblast_desc[] = _("30% chance to lower the target‘s Sp. Atk by 1.");
pchar Boomburst_desc[] = _("No additional effect. Hits adjacent Pokemon.");
pchar Fairy_Lock_desc[] = _("Prevents all Pokemon from switching next turn.");
pchar Kings_Shield_desc[] = _("Protects from attacks. Contact: lowers Atk by 2.");
pchar Play_Nice_desc[] = _("Lowers the target‘s Attack by 1.");
pchar Spiky_Shield_desc[] = _("Protects from moves. Contact: loses 1/8 max HP.");
pchar Aromatic_Mist_desc[] = _("Raises an ally‘s Sp. Def by 1.");
pchar Eerie_Impulse_desc[] = _("Lowers the target‘s Sp. Atk by 2.");
pchar Venom_Drench_desc[] = _("Lowers Atk Sp. Atk Speed of poisoned foes by 1.");
pchar Powder_desc[] = _("If using a Fire move target loses 1/4 max HP.");
pchar Magnetic_Flux_desc[] = _("Raises Def Sp. Def of allies with Plus/Minus by 1.");
pchar Electric_Terrain_desc[] = _("5 turns. Grounded: +Electric power can‘t sleep.");
pchar Dazzling_Gleam_desc[] = _("No additional effect. Hits adjacent foes.");
pchar Baby_Doll_Eyes_desc[] = _("Lowers the target‘s Attack by 1.");
pchar Nuzzle_desc[] = _("100% chance to paralyze the target.");
pchar Hold_Back_desc[] = _("Always leaves the target with at least 1 HP.");
pchar Infestation_desc[] = _("Traps and damages the target for 4-5 turns.");
pchar Power_Up_Punch_desc[] = _("100% chance to raise the user‘s Attack by 1.");
pchar Shore_Up_desc[] = _("Heals the user by a weather-dependent amount.");
pchar High_Horsepower_desc[] = _("No additional effect.");
pchar Strength_Sap_desc[] = _("User heals HP=target‘s Atk stat. Lowers Atk by 1.");
pchar Spotlight_desc[] = _("Spotlights the target, forcing it to be attacked.");
pchar Toxic_Thread_desc[] = _("Lowers the target‘s Speed by 1 and poisons it.");
pchar Laser_Focus_desc[] = _("Focuses turn 1, crits turn 2.");
pchar Throat_Chop_desc[] = _("For 2 turns the target cannot use sound moves.");
pchar Anchor_Shot_desc[] = _("Prevents the target from switching out.");
pchar Psychic_Terrain_desc[] = _("5 turns. Grounded: +Psychic power priority-safe.");
pchar Lunge_desc[] = _("100% chance to lower the target‘s Attack by 1.");
pchar Power_Trip_desc[] = _(" + 20 power for each of the user‘s stat boosts.");
pchar Burn_Up_desc[] = _("User‘s Fire-type is removed until it switches out.");
pchar Trop_Kick_desc[] = _("100% chance to lower the target‘s Attack by 1.");
pchar Dragon_Hammer_desc[] = _("No additional effect.");
pchar Brutal_Swing_desc[] = _("No additional effect. Hits adjacent Pokemon.");
pchar Shell_Trap_desc[] = _("User must take physical damage before moving.");
pchar Psychic_Fangs_desc[] = _("Destroys screens unless the target is immune.");
pchar Stomping_Tantrum_desc[] = _("Power doubles if the user‘s last move failed.");
pchar Accelerock_desc[] = _("Usually goes first.");
pchar Liquidation_desc[] = _("20% chance to lower the target‘s Defense by 1.");
pchar Tearful_Look_desc[] = _("Lowers the target‘s Attack and Sp. Atk by 1.");
pchar Zing_Zap_desc[] = _("30% chance to flinch the target.");

extern struct move_procs basic_proc;

struct move_data gBattleMoves[] = {
    {
    /* Move NULL */
    .name = _("-"),
    .description = (pchar*)Pound_desc,
    .pp = 0,
    .type = TYPE_NONE,
    .procs = &basic_proc,
    },

    {
    /* Pound */
    .name = _("Pound"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Pound_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PoundAnimation,
    },

    {
    /*Karate Chop*/
    .name = _("Karate Chop"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Karate_Chop_desc,
    .pp = 25,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&KaratechopAnimation,
    },

    {
    /*Double Slap*/
    .name = _("Double Slap"),
    .accuracy = 85,
    .base_power = 15,
    .description = (pchar*)Double_Slap_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DoubleSlapAnimation,
    },

    {
    /*Comet Punch*/
    .name = _("Comet Punch"),
    .accuracy = 85,
    .base_power = 18,
    .description = (pchar*)Comet_Punch_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_PUNCH,
    .procs = &basic_proc,
    .animation = (u8*)&CometpunchAnimation,
    },

    {
    /*Mega Punch*/
    .name = _("Mega Punch"),
    .accuracy = 85,
    .base_power = 80,
    .description = (pchar*)Mega_Punch_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_PUNCH,
    .procs = &basic_proc,
    .animation = (u8*)&MegapunchAnimation,
    },

    {
    /*Pay Day*/
    .name = _("Pay Day"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Pay_Day_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = payday_ondmg,
    },

    {
    /*Fire Punch*/
    .name = _("Fire Punch"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Fire_Punch_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_PUNCH,
    .procs = &burn_10_procs,
    .animation = (u8*)&FirepunchAnimation,
    },

    {
    /*Ice Punch*/
    .name = _("Ice Punch"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Ice_Punch_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_PUNCH,
    .procs = &freeze_10_procs,
    .animation = (u8*)&IcepunchAnimation,
    },

    {
    /*Thunder Punch*/
    .name = _("Thunder Punch"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Thunder_Punch_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_PUNCH,
    .procs = &paralyze_10_procs,
    .animation = (u8*)&ThunderpunchAnimation,
    },

    {
    /*Scratch*/
    .name = _("Scratch"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Scratch_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    },

    {
    /*Vice Grip*/
    .name = _("Vice Grip"),
    .accuracy = 100,
    .base_power = 55,
    .description = (pchar*)Vice_Grip_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&VicegripAnimation,
    },

    {
    /*Guillotine*/
    .name = _("Guillotine"),
    .accuracy = 30,
    .description = (pchar*)Guillotine_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_OHKO,
    .procs = &basic_proc,
    .on_tryhit_move = ohko_tryhit_move,
    .animation = (u8*)&GuillotineAnimation,
    },

    {
    /*Razor Wind*/
    .name = _("Razor Wind"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Razor_Wind_desc,
    .pp = 10,
    .crit_ratio = 1,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &basic_proc,
    .before_move = razor_wind_before_move,
    .animation = (u8*)&RazorwindAnimation,
    },

    {
    /*Swords Dance*/
    .name = _("Swords Dance"),
    .accuracy = 101,
    .description = (pchar*)Swords_Dance_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_DANCE | FLAG_ONSELF,
    .procs = &user_raise_atk_2,
    .animation = (u8*)&SwordsDanceAnimation,
    },

    {
    /*Cut*/
    .name = _("Cut"),
    .accuracy = 95,
    .base_power = 50,
    .description = (pchar*)Cut_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&CutAnimation,
    },

    {
    /*Gust*/
    .name = _("Gust"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Gust_desc,
    .pp = 35,
    .category = MOVE_SPECIAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_inv_tryhit_move = gust_on_invul_hit,
    .animation = (u8*)&GustAnimation,
    },

    {
    /*Wing Attack*/
    .name = _("Wing Attack"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Wing_Attack_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&WingAttackAnimation,
    },

    {
    /*Whirlwind*/
    .name = _("Whirlwind"),
    .accuracy = 101,
    .description = (pchar*)Whirlwind_desc,
    .pp = 20,
    .priority = -6,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_REFLECTABLE | FLAG_TARGET | FLAG_AUTHENTIC,
    .procs = &basic_proc,
    .on_effect_cb = dragon_tail_on_effect,
    .animation = (u8*)&WhirlwindAnimation,
    },

    {
    /*Fly*/
    .name = _("Fly"),
    .accuracy = 95,
    .base_power = 90,
    .description = (pchar*)Fly_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_CHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_GRAVITY,
    .procs = &basic_proc,
    .before_move = fly_before_move,
    .animation = (u8*)&FlyAnimation,
    },

    {
    /*Bind*/
    .name = _("Bind"),
    .accuracy = 85,
    .base_power = 15,
    .description = (pchar*)Bind_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&BindAnimation,
    },

    {
    /*Slam*/
    .name = _("Slam"),
    .accuracy = 75,
    .base_power = 80,
    .description = (pchar*)Slam_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.animation = (u8*)&SlamAnimation,
    },

    {
    /*Vine Whip*/
    .name = _("Vine Whip"),
    .accuracy = 100,
    .base_power = 45,
    .description = (pchar*)Vine_Whip_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&VineWhipAnimation,
    },

    {
    /*Stomp*/
    .name = _("Stomp"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Stomp_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .on_modify_move = stomp_on_modify_move,
    .animation = (u8*)&StompAnimation,
    },

    {
    /*Double Kick*/
    .name = _("Double Kick"),
    .accuracy = 100,
    .base_power = 30,
    .description = (pchar*)Double_Kick_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .multi_hit = {2, 2},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DoubleKickAnimation,
    },

    {
    /*Mega Kick*/
    .name = _("Mega Kick"),
    .accuracy = 75,
    .base_power = 120,
    .description = (pchar*)Mega_Kick_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MegaKickAnimation,
    },

    {
    /*Jump Kick*/
    .name = _("Jump Kick"),
    .accuracy = 95,
    .base_power = 100,
    .description = (pchar*)Jump_Kick_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_GRAVITY | FLAG_TARGET,
    .procs = &basic_proc,
    .on_move_fail = jump_kick_on_move_fail,
    .animation = (u8*)&JumpKickAnimation,
    },

    {
    /*Rolling Kick*/
    .name = _("Rolling Kick"),
    .accuracy = 85,
    .base_power = 60,
    .description = (pchar*)Rolling_Kick_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&RollingKickAnimation,
    },

    {
    /*Sand Attack*/
    .name = _("Sand Attack"),
    .accuracy = 100,
    .description = (pchar*)Sand_Attack_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GROUND,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1,
    .animation = (u8*)&SandAttackAnimation,
    },

    {
    /*Headbutt*/
    .name = _("Headbutt"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Headbutt_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&HeadbuttAnimation,
    },

    {
    /*Horn Attack*/
    .name = _("Horn Attack"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Horn_Attack_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HornAttackAnimation,
    },

    {
    /*Fury Attack*/
    .name = _("Fury Attack"),
    .accuracy = 85,
    .base_power = 15,
    .description = (pchar*)Fury_Attack_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FuryAttackAnimation,
    },

    {
    /*Horn Drill*/
    .name = _("Horn Drill"),
    .accuracy = 30,
    .description = (pchar*)Horn_Drill_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_OHKO,
    .procs = &basic_proc,
    .on_tryhit_move = ohko_tryhit_move,
    .animation = (u8*)&HornDrillAnimation,
    },

    {
    /*Tackle*/
    .name = _("Tackle"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Tackle_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&TackleAnimation,
    },

    {
    /*Body Slam*/
    .name = _("Body Slam"),
    .accuracy = 100,
    .base_power = 85,
    .description = (pchar*)Body_Slam_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .on_modify_move = stomp_on_modify_move,
    .animation = (u8*)&BodySlamAnimation,
    },

    {
    /*Wrap*/
    .name = _("Wrap"),
    .accuracy = 90,
    .base_power = 15,
    .description = (pchar*)Wrap_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = wrap_partially_trapped_effect_cb,
    .animation = (u8*)&WrapAnimation,
    },

    {
    /*Take Down*/
    .name = _("Take Down"),
    .accuracy = 85,
    .base_power = 90,
    .description = (pchar*)Take_Down_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .recoil = 25,
    .animation = (u8*)&TakedownAnimation,
    },

    {
    /*Thrash*/
    .name = _("Thrash"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Thrash_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = thrash_on_tryhit_move,
    .on_move_fail = thrash_on_move_fail,
    .on_after_move = thrash_on_after_move,
    .animation = (u8*)&ThrashAnimation,
    },

    /* Double edge*/
    {
    .name = _("Double-Edge"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Double_Edge_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .recoil = 25,
    .animation = (u8*)&DoubleEdgeAnimation,
    },

    {
    /*Tail Whip*/
    .name = _("Tail Whip"),
    .accuracy = 100,
    .description = (pchar*)Tail_Whip_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &target_lower_def_1,
    .animation = (u8*)&TailWhipAnimation,
    },

    {
    /*Poison Sting*/
    .name = _("Poison Sting"),
    .accuracy = 100,
    .base_power = 15,
    .description = (pchar*)Poison_Sting_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_30_procs,
    .animation = (u8*)&PoisonStingAnimation,
    },

    {
    /*Twineedle*/
    .name = _("Twineedle"),
    .accuracy = 100,
    .base_power = 25,
    .description = (pchar*)Twineedle_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .multi_hit = {2, 2},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_20_procs,
    .animation = (u8*)&TwineedleAnimation,
    },

    {
    /*Pin Missile*/
    .name = _("Pin Missile"),
    .accuracy = 95,
    .base_power = 25,
    .description = (pchar*)Pin_Missile_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .multi_hit = {2, 5},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PinMissileAnimation,
    },

    {
    /*Leer*/
    .name = _("Leer"),
    .accuracy = 100,
    .description = (pchar*)Leer_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_1,
    .animation = (u8*)&LeerAnimation,
    },

    {
    /*Bite*/
    .name = _("Bite"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Bite_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&BiteAnimation,
    },

    {
    /*Growl*/
    .name = _("Growl"),
    .accuracy = 100,
    .description = (pchar*)Growl_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_SOUND | FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &target_lower_atk_1,
    .animation = (u8*)&GrowlAnimation,
    },

    {
    /*Roar*/
    .name = _("Roar"),
    .accuracy = 101,
    .description = (pchar*)Roar_desc,
    .pp = 20,
    .priority = -6,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = dragon_tail_on_effect,
    .animation = (u8*)&RoarAnimation,
    },

    {
    /*Sing*/
    .name = _("Sing"),
    .accuracy = 55,
    .description = (pchar*)Sing_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_SOUND | FLAG_AUTHENTIC | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&SingAnimation,
    },

    {
    /*Supersonic*/
    .name = _("Supersonic"),
    .accuracy = 55,
    .description = (pchar*)Supersonic_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &supersonic_procs,
    .animation = (u8*)&SupersonicAnimation,
    },

    {
    /*Sonic Boom*/
    .name = _("Sonic Boom"),
    .accuracy = 90,
    .description = (pchar*)Sonic_Boom_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = sonic_boom_on_dmg,
    .animation = (u8*)&SonicBoomAnimation,
    },

    {
    /*Disable*/
    .name = _("Disable"),
    .accuracy = 100,
    .description = (pchar*)Disable_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = disable_on_before_move,
    .on_effect_cb = disable_on_effect_cb,
    .animation = (u8*)&DisableAnimation,
    },

    {
    /*Acid*/
    .name = _("Acid"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Acid_desc,
    .pp = 30,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_1,
    .animation = (u8*)&AcidAnimation,
    },

    {
    /*Ember*/
    .name = _("Ember"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Ember_desc,
    .pp = 25,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&EmberAnimation,
    },

    {
    /*Flamethrower*/
    .name = _("Flamethrower"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Flamethrower_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&FlamethrowerAnimation,
	},

	{
	/*Mist*/
	.name = _("Mist"),
	.accuracy = 101,
    .description = (pchar*)Mist_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_ICE,
    .m_flags = FLAG_SNATCH | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mist_on_effect,
    .animation = (u8*)&MistAnimation,
    },

    {
    /*Water Gun*/
    .name = _("Water Gun"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Water_Gun_desc,
    .pp = 25,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&WatergunAnimation,
    },

    {
    /*Hydro Pump*/
    .name = _("Hydro Pump"),
    .accuracy = 80,
    .base_power = 110,
    .description = (pchar*)Hydro_Pump_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HydroPumpAnimation,
    },

    {
    /*Surf*/
    .name = _("Surf"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Surf_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &basic_proc,
    .on_base_power_move = whirlpool_on_base_power,
    .on_inv_tryhit_move = whirlpool_on_tryhit_invul,
    .animation = (u8*)&SurfAnimation,
    },

    {
    /*Ice Beam*/
    .name = _("Ice Beam"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Ice_Beam_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &freeze_10_procs,
    .animation = (u8*)&IceBeamAnimation,
    },

    {
    /*Blizzard*/
    .name = _("Blizzard"),
    .accuracy = 70,
    .base_power = 110,
    .description = (pchar*)Blizzard_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &freeze_10_procs,
    .on_modify_move = blizzard_on_modify_move,
    .animation = (u8*)&BlizzardAnimation,
    },

    {
    /*Psybeam*/
    .name = _("Psybeam"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Psybeam_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_10_procs,
    .animation = (u8*)&PsybeamAnimation,
    },

    {
    /*Bubble Beam*/
    .name = _("Bubble Beam"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Bubble_Beam_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &bubble_beam_procs,
    .animation = (u8*)&BubbleBeamAnimation,
    },

    {
    /*Aurora Beam*/
    .name = _("Aurora Beam"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Aurora_Beam_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &aurora_beam_procs,
    .animation = (u8*)&AuroraBeamAnimation,
    },

    {
    /*Hyper Beam*/
    .name = _("Hyper Beam"),
    .accuracy = 90,
    .base_power = 150,
    .description = (pchar*)Hyper_Beam_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_RECHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HyperBeamAnimation,
    },

    {
    /*Peck*/
    .name = _("Peck"),
    .accuracy = 100,
    .base_power = 35,
    .description = (pchar*)Peck_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PeckAnimation,
    },

    {
    /*Drill Peck*/
    .name = _("Drill Peck"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Drill_Peck_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DrillPeckAnimation,
    },

    {
    /*Submission*/
    .name = _("Submission"),
    .accuracy = 80,
    .base_power = 80,
    .description = (pchar*)Submission_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.recoil = 25,
    .animation = (u8*)&SubmissionAnimation,
    },

    {
    /*Low Kick*/
    .name = _("Low Kick"),
    .accuracy = 100,
    .description = (pchar*)Low_Kick_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = low_kick_on_base_power_move,
    .animation = (u8*)&LowKickAnimation,
    },

    {
    /*Counter*/
    .name = _("Counter"),
    .accuracy = 100,
    .description = (pchar*)Counter_desc,
    .pp = 20,
    .priority = -5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = counter_before_turn,
    .on_tryhit_move = counter_on_tryhit,
    .animation = (u8*)&CounterAnimation,
    },

    {
    /*Seismic Toss*/
    .name = _("Seismic Toss"),
    .accuracy = 100,
    .description = (pchar*)Seismic_Toss_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.on_damage_move = seismic_toss_on_damage_move,
    .animation = (u8*)&SeismicTossAnimation,
    },

    {
    /*Strength*/
    .name = _("Strength"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Strength_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&StrengthAnimation,
    },

    {
    /*Absorb*/
    .name = _("Absorb"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Absorb_desc,
    .pp = 25,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_HEAL | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .drain = 50,
    .procs = &basic_proc,
    .animation = (u8*)&AbsorbAnimation,
    },

    {
    /*Mega drain*/
    .name = _("Mega drain"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Mega_Drain_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_HEAL | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .drain = 50,
    .procs = &basic_proc,
    .animation = (u8*)&MegaDrainAnimation,
    },

    {
    /*Leech Seed*/
    .name = _("Leech Seed"),
    .accuracy = 90,
    .description = (pchar*)Leech_Seed_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .drain = 100, // leech seed should drain 100% of dmg dealt
    .on_tryhit_move = leech_seed_on_tryhit,
    .animation = (u8*)&LeechSeedAnimation,
    },

    {
    /*Growth*/
    .name = _("Growth"),
    .accuracy = 101,
    .description = (pchar*)Growth_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = growth_on_effect,
    .animation = (u8*)&GrowthAnimation,
    },

    {
    /*Razor Leaf*/
    .name = _("Razor Leaf"),
    .accuracy = 95,
    .base_power = 55,
    .description = (pchar*)Razor_Leaf_desc,
    .pp = 25,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RazorLeafAnimation,
    },

    {
    /*Solar Beam*/
    .name = _("Solar Beam"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Solar_Beam_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = solarbeam_before_move,
    .animation = (u8*)&SolarBeamAnimation,
    },

    {
    /*Poison Powder*/
    .name = _("Poison Powder"),
    .accuracy = 75,
    .description = (pchar*)Poison_Powder_desc,
    .pp = 35,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_100_procs,
    .animation = (u8*)&PoisonPowderAnimation,
    },

    {
    /*Stun Spore*/
    .name = _("Stun Spore"),
    .accuracy = 75,
    .description = (pchar*)Stun_Spore_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_100_procs,
    .animation = (u8*)&StunSporeAnimation,
    },

    {
    /*Sleep Powder*/
    .name = _("Sleep Powder"),
    .accuracy = 75,
    .description = (pchar*)Sleep_Powder_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&SleepPowderAnimation,
    },

    {
    /*Petal Dance*/
    .name = _("Petal Dance"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Petal_Dance_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_DANCE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = thrash_on_tryhit_move,
    .on_move_fail = thrash_on_move_fail,
    .on_after_move = thrash_on_after_move,
    .animation = (u8*)&PetalDanceAnimation,
    },

    {
    /*String Shot*/
    .name = _("String Shot"),
    .accuracy = 95,
    .description = (pchar*)String_Shot_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &target_lower_spd_2,
    .animation = (u8*)&StringShotAnimation,
    },

    {
    /*Dragon Rage*/
    .name = _("Dragon Rage"),
    .accuracy = 100,
    .description = (pchar*)Dragon_Rage_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = dragon_rage_on_dmg,
    .animation = (u8*)&DragonRageAnimation,
    },

    {
    /*Fire Spin*/
    .name = _("Fire Spin"),
    .accuracy = 85,
    .base_power = 35,
    .description = (pchar*)Fire_Spin_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&FireSpinAnimation,
    },

    {
    /*Thunder Shock*/
    .name = _("Thunder Shock"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Thunder_Shock_desc,
    .pp = 30,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_10_procs,
    .animation = (u8*)&ThunderShockAnimation,
    },

    {
    /*Thunderbolt*/
    .name = _("Thunderbolt"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Thunderbolt_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_10_procs,
    .animation = (u8*)&ThunderboltAnimation,
    },

    {
    /*Thunder Wave*/
    .name = _("Thunder Wave"),
    .accuracy = 90,
    .description = (pchar*)Thunder_Wave_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_100_procs,
    .animation = (u8*)&ThunderWaveAnimation,
    },

    {
    /*Thunder*/
    .name = _("Thunder"),
    .accuracy = 70,
    .base_power = 110,
    .description = (pchar*)Thunder_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .on_modify_move = hurricane_on_modify_move,
    .on_inv_tryhit_move = hurricane_on_tryhit_inv,
    .animation = (u8*)&ThunderAnimation,
    },

    {
    /*Rock Throw*/
    .name = _("Rock Throw"),
    .accuracy = 90,
    .base_power = 50,
    .description = (pchar*)Rock_Throw_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RockThrowAnimation,
    },

    {
    /*Earthquake*/
    .name = _("Earthquake"),
    .accuracy = 100,
    .base_power = 100,
    .description = (pchar*)Earthquake_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_base_power_move = earthquake_on_base_power,
    .on_inv_tryhit_move = magnitude_on_tryhit_invul,
    .animation = (u8*)&EarthquakeAnimation,
    },

    {
    /*Fissure*/
    .name = _("Fissure"),
    .accuracy = 30,
    .description = (pchar*)Fissure_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_OHKO | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = ohko_tryhit_move,
    .animation = (u8*)&FissureAnimation,
    },

    {
    /*Dig*/
    .name = _("Dig"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Dig_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_CONTACT | FLAG_CHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = dig_before_move,
    .on_inv_tryhit_move = magnitude_on_tryhit_invul,
    .animation = (u8*)&DigAnimation,
	},

    {
    /*Toxic*/
    .name = _("Toxic"),
    .accuracy = 90,
    .description = (pchar*)Toxic_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &toxic_procs,
    .animation = (u8*)&ToxicAnimation,
	},

    {
    /*Confusion*/
    .name = _("Confusion"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Confusion_desc,
    .pp = 25,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_10_procs,
    .animation = (u8*)&ConfusionAnimation,
	},

    {
    /*Psychic*/
    .name = _("Psychic"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Psychic_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &psychic_procs,
    .animation = (u8*)&PsychicAnimation,
	},

    {
    /*Hypnosis*/
    .name = _("Hypnosis"),
    .accuracy = 60,
    .description = (pchar*)Hypnosis_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_PROTECT | FLAG_MIRROR | FLAG_REFLECTABLE | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&HypnosisAnimation,
	},

    {
    /*Meditate*/
    .name = _("Meditate"),
    .accuracy = 101,
    .description = (pchar*)Meditate_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_atk_1,
    .animation = (u8*)&MeditateAnimation,
	},

    {
    /*Agility*/
    .name = _("Agility"),
    .accuracy = 101,
    .description = (pchar*)Agility_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_spd_2,
    .animation = (u8*)&AgilityAnimation,
	},

    {
    /*Quick Attack*/
    .name = _("Quick Attack"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Quick_Attack_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&QuickAttackAnimation,
	},

    {
    /*Rage*/
    .name = _("Rage"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Rage_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = rage_on_effect,
    .animation = (u8*)&RageAnimation,
	},

    {
    /*Teleport*/
    .name = _("Teleport"),
    .accuracy = 101,
    .description = (pchar*)Teleport_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = dragon_tail_on_effect,
    .animation = (u8*)&TeleportAnimation,
	},

    {
    /*Night Shade*/
    .name = _("Night Shade"),
    .accuracy = 100,
    .description = (pchar*)Night_Shade_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = seismic_toss_on_damage_move,
    .animation = (u8*)&NightShadeAnimation,
	},

    {
    /*Mimic*/
    .name = _("Mimic"),
    .accuracy = 101,
    .description = (pchar*)Mimic_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mimic_on_effect,
    .animation = (u8*)&MimicAnimation,
	},

    {
    /*Screech*/
    .name = _("Screech"),
    .accuracy = 85,
    .description = (pchar*)Screech_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_2,
    .animation = (u8*)&ScreechAnimation,
	},

    {
    /*Double Team*/
    .name = _("Double Team"),
    .accuracy = 101,
    .description = (pchar*)Double_Team_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_evn_1,
    .animation = (u8*)&DoubleTeamAnimation,
	},

    {
    /*Recover*/
    .name = _("Recover"),
    .accuracy = 101,
    .description = (pchar*)Recover_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
	.heal = 50,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .animation = (u8*)&RecoverAnimation,
	},

    {
    /*Harden*/
    .name = _("Harden"),
    .accuracy = 101,
    .description = (pchar*)Harden_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_def_1,
    .animation = (u8*)&HardenAnimation,
	},

    {
    /*Minimize*/
    .name = _("Minimize"),
    .accuracy = 101,
    .description = (pchar*)Minimize_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_evn_1,
    .on_effect_cb = minimize_on_effect_cb,
    .animation = (u8*)&MinimizeAnimation,
	},

    {
    /*Smokescreen*/
    .name = _("Smokescreen"),
    .accuracy = 100,
    .description = (pchar*)Smokescreen_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1,
    .animation = (u8*)&SmokescreenAnimation,
	},

    {
    /*Confuse Ray*/
    .name = _("Confuse Ray"),
    .accuracy = 100,
    .description = (pchar*)Confuse_Ray_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_100_procs,
    .animation = (u8*)&ConfuseRayAnimation,
	},

    {
    /*Withdraw*/
    .name = _("Withdraw"),
    .accuracy = 101,
    .description = (pchar*)Withdraw_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_WATER,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_def_1,
    .animation = (u8*)&WithdrawAnimation,
	},

    {
    /*Defense Curl*/
    .name = _("Defense Curl"),
    .accuracy = 101,
    .description = (pchar*)Defense_Curl_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_def_1,
    .animation = (u8*)&DefenseCurlAnimation,
	},

    {
    /*Barrier*/
    .name = _("Barrier"),
    .accuracy = 101,
    .description = (pchar*)Barrier_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_def_2,
    .animation = (u8*)&BarrierAnimation,
	},

    {
    /*Light Screen*/
    .name = _("Light Screen"),
    .accuracy = 101,
    .description = (pchar*)Light_Screen_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = light_screen_on_effect,
    .animation = (u8*)&LightScreenAnimation,
	},

    {
    /*Haze*/
    .name = _("Haze"),
    .accuracy = 101,
    .description = (pchar*)Haze_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_ICE,
    .m_flags = FLAG_AUTHENTIC | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = haze_effect,
    .animation = (u8*)&HazeAnimation,
	},

    {
    /*Reflect*/
    .name = _("Reflect"),
    .accuracy = 101,
    .description = (pchar*)Reflect_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = reflect_on_effect,
    .animation = (u8*)&ReflectAnimation,
	},

    {
    /*Focus Energy*/
    .name = _("Focus Energy"),
    .accuracy = 101,
    .description = (pchar*)Focus_Energy_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &focus_energy_proc,
    .on_tryhit_move = focus_energy_on_tryhit,
    .animation = (u8*)&FocusEnergyAnimation,
	},

    {
    /*Bide*/
    .name = _("Bide"),
    .accuracy = 101,
    .description = (pchar*)Bide_desc,
    .pp = 10,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = bide_on_effect,
    .animation = (u8*)&BideAnimation,
	},

    {
    /*Metronome*/
    .name = _("Metronome"),
    .accuracy = 101,
    .description = (pchar*)Metronome_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = metronome_on_modify_move,
    .animation = (u8*)&MetronomeAnimation,
	},

    {
    /*Mirror Move*/
    .name = _("Mirror Move"),
    .accuracy = 101,
    .description = (pchar*)Mirror_Move_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = mirror_move_on_modify_move,
    .animation = (u8*)&MirrorMoveAnimation,
	},

    /*Self-Destruct*/
    {
    .name = _("Self-Destruct"),
    .accuracy = 100,
    .base_power = 200,
    .description = (pchar*)Self_Destruct_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_tryhit_move = self_destruct_on_tryhit,
    .animation = (u8*)&SelfDestructAnimation,
	},

    {
    /*Egg Bomb*/
    .name = _("Egg Bomb"),
    .accuracy = 75,
    .base_power = 100,
    .description = (pchar*)Egg_Bomb_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&EggBombAnimation,
	},

    {
    /*Lick*/
    .name = _("Lick"),
    .accuracy = 100,
    .base_power = 30,
    .description = (pchar*)Lick_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .animation = (u8*)&LickAnimation,
	},

    {
    /*Smog*/
    .name = _("Smog"),
    .accuracy = 70,
    .base_power = 30,
    .description = (pchar*)Smog_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_40_procs,
    .animation = (u8*)&SmogAnimation,
	},

    {
    /*Sludge*/
    .name = _("Sludge"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Sludge_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_30_procs,
    .animation = (u8*)&SludgeAnimation,
	},

    {
    /*Bone Club*/
    .name = _("Bone Club"),
    .accuracy = 85,
    .base_power = 65,
    .description = (pchar*)Bone_Club_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 10,
    .animation = (u8*)&BoneClubAnimation,
	},

    {
    /*Fire Blast*/
    .name = _("Fire Blast"),
    .accuracy = 85,
    .base_power = 110,
    .description = (pchar*)Fire_Blast_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&FireBlastAnimation,
	},

    {
    /*Waterfall*/
    .name = _("Waterfall"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Waterfall_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 20,
    .animation = (u8*)&WaterfallAnimation,
	},

    {
    /*Clamp*/
    .name = _("Clamp"),
    .accuracy = 85,
    .base_power = 35,
    .description = (pchar*)Clamp_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&ClampAnimation,
	},

    {
    /*Swift*/
    .name = _("Swift"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Swift_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SwiftAnimation,
	},

    {
    /*Skull Bash*/
    .name = _("Skull Bash"),
    .accuracy = 100,
    .base_power = 130,
    .description = (pchar*)Skull_Bash_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_CHARGE | FLAG_PROTECT | FLAG_TARGET | FLAG_MIRROR,
    .procs = &basic_proc,
    .before_move = skull_bash_before_move,
    .animation = (u8*)&SkullBashAnimation,
	},

    {
    /*Spike Cannon*/
    .name = _("Spike Cannon"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Spike_Cannon_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SpikeCannonAnimation,
	},

    {
    /*Constrict*/
    .name = _("Constrict"),
    .accuracy = 100,
    .base_power = 10,
    .description = (pchar*)Constrict_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spe_1_10,
    .animation = (u8*)&ConstrictAnimation,
	},

    {
    /*Amnesia*/
    .name = _("Amnesia"),
    .accuracy = 101,
    .description = (pchar*)Amnesia_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_spDef_2,
    .animation = (u8*)&AmnesiaAnimation,
	},

    {
    /*Kinesis*/
    .name = _("Kinesis"),
    .accuracy = 80,
    .description = (pchar*)Kinesis_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1,
    .animation = (u8*)&KinesisAnimation,
	},

    /*Soft-Boiled*/
    {
    .name = _("Soft-Boiled"),
    .accuracy = 101,
    .description = (pchar*)Soft_Boiled_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_HEAL,
	.heal = 50,
    .procs = &basic_proc,
    .animation = (u8*)&SoftBoiledAnimation,
	},

    {
    /*High Jump Kick*/
    .name = _("High Jump Kick"),
    .accuracy = 90,
    .base_power = 130,
    .description = (pchar*)High_Jump_Kick_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_GRAVITY | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_move_fail = jump_kick_on_move_fail,
    .animation = (u8*)&HighJumpKickAnimation,
	},

    {
    /*Glare*/
    .name = _("Glare"),
    .accuracy = 100,
    .description = (pchar*)Glare_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_100_procs,
    .animation = (u8*)&GlareAnimation,
	},

    {
    /*Dream Eater*/
    .name = _("Dream Eater"),
    .accuracy = 100,
    .base_power = 100,
    .description = (pchar*)Dream_Eater_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_HEAL | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .drain = 50,
    .on_tryhit_move = dream_eater_on_tryhit,
    .animation = (u8*)&DreamEaterAnimation,
	},

    {
    /*Poison Gas*/
    .name = _("Poison Gas"),
    .accuracy = 90,
    .description = (pchar*)Poison_Gas_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_100_procs,
    .animation = (u8*)&PoisonGasAnimation,
	},

    {
    /*Barrage*/
    .name = _("Barrage"),
    .accuracy = 85,
    .base_power = 15,
    .description = (pchar*)Barrage_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BarrageAnimation,
	},

    {
    /*Leech Life*/
    .name = _("Leech Life"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Leech_Life_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_HEAL | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .drain = 50,
    .procs = &basic_proc,
    .animation = (u8*)&LeechLifeAnimation,
	},

    {
    /*Lovely Kiss*/
    .name = _("Lovely Kiss"),
    .accuracy = 75,
    .description = (pchar*)Lovely_Kiss_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&LovelyKissAnimation,
	},

    {
    /*Sky Attack*/
    .name = _("Sky Attack"),
    .accuracy = 90,
    .base_power = 140,
    .description = (pchar*)Sky_Attack_desc,
    .pp = 5,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CHARGE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = sky_attack_before_move,
    .flinch_chance = 30,
    .animation = (u8*)&SkyAttackAnimation,
	},

    {
    /*Transform*/
    .name = _("Transform"),
    .accuracy = 101,
    .description = (pchar*)Transform_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&TransformAnimation,
	},

    {
    /*Bubble*/
    .name = _("Bubble"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Bubble_desc,
    .pp = 30,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &bubble_beam_procs,
    .animation = (u8*)&BubbleAnimation,
	},

    {
    /*Dizzy Punch*/
    .name = _("Dizzy Punch"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Dizzy_Punch_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_20_procs,
    .animation = (u8*)&DizzyPunchAnimation,
	},

    {
    /*Spore*/
    .name = _("Spore"),
    .accuracy = 100,
    .description = (pchar*)Spore_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&SporeAnimation,
	},

    {
    /*Flash*/
    .name = _("Flash"),
    .accuracy = 100,
    .description = (pchar*)Flash_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1,
    .animation = (u8*)&FlashAnimation,
	},

    {
    /*Psywave*/
    .name = _("Psywave"),
    .accuracy = 100,
    .description = (pchar*)Psywave_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.on_damage_move = psywave_on_damage_move,
    .animation = (u8*)&PsywaveAnimation,
	},

    {
    /*Splash*/
    .name = _("Splash"),
    .accuracy = 101,
    .description = (pchar*)Splash_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SplashAnimation,
	},

    {
    /*Acid Armor*/
    .name = _("Acid Armor"),
    .accuracy = 101,
    .description = (pchar*)Acid_Armor_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_def_2,
    .animation = (u8*)&AcidArmorAnimation,
	},

    {
    /*Crabhammer*/
    .name = _("Crabhammer"),
    .accuracy = 90,
    .base_power = 100,
    .description = (pchar*)Crabhammer_desc,
    .pp = 10,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&CrabhammerAnimation,
	},

    {
    /*Explosion*/
    .name = _("Explosion"),
    .accuracy = 100,
    .base_power = 250,
    .description = (pchar*)Explosion_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_tryhit_move = self_destruct_on_tryhit,
    .animation = (u8*)&ExplosionAnimation,
	},

    {
    /*Fury Swipes*/
    .name = _("Fury Swipes"),
    .accuracy = 80,
    .base_power = 18,
    .description = (pchar*)Fury_Swipes_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FurySwipesAnimation,
	},

    {
    /*Bonemerang*/
    .name = _("Bonemerang"),
    .accuracy = 90,
    .base_power = 50,
    .description = (pchar*)Bonemerang_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .multi_hit = {2, 2},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BonemerangAnimation,
	},

    {
    /*Rest*/
    .name = _("Rest"),
    .accuracy = 101,
    .description = (pchar*)Rest_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = rest_on_tryhit_move,
    .animation = (u8*)&RestAnimation,
	},

    {
    /*Rock Slide*/
    .name = _("Rock Slide"),
    .accuracy = 90,
    .base_power = 75,
    .description = (pchar*)Rock_Slide_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&RockSlideAnimation,
	},

    {
    /*Hyper Fang*/
    .name = _("Hyper Fang"),
    .accuracy = 90,
    .base_power = 80,
    .description = (pchar*)Hyper_Fang_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 10,
    .animation = (u8*)&HyperFangAnimation,
	},

    {
    /*Sharpen*/
    .name = _("Sharpen"),
    .accuracy = 101,
    .description = (pchar*)Sharpen_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_atk_1,
    .animation = (u8*)&SharpenAnimation,
	},

    {
    /*Conversion*/
    .name = _("Conversion"),
    .accuracy = 101,
    .description = (pchar*)Conversion_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = conversion_on_effect,
    .animation = (u8*)&ConversionAnimation,
	},

    {
    /*Tri Attack*/
    .name = _("Tri Attack"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Tri_Attack_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = tri_attack_on_effect,
    .animation = (u8*)&TriAttackAnimation,
	},

    {
    /*Super Fang*/
    .name = _("Super Fang"),
    .accuracy = 90,
    .description = (pchar*)Super_Fang_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = natures_madness_on_modify_move,
    .animation = (u8*)&SuperFangAnimation,
	},

    {
    /*Slash*/
    .name = _("Slash"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Slash_desc,
    .pp = 20,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SlashAnimation,
	},

    {
    /*Substitute*/
    .name = _("Substitute"),
    .accuracy = 101,
    .description = (pchar*)Substitute_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH,
    .procs = &basic_proc,
    .animation = (u8*)&SubstituteAnimation,
	},

    {
    /*Struggle*/
    .name = _("Struggle"),
    .accuracy = 101,
    .base_power = 50,
    .description = (pchar*)Struggle_desc,
    .pp = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .recoil = 25,
    .recoil_struggle = true,
    .animation = (u8*)&StruggleAnimation,
	},

    {
    /*Sketch*/
    .name = _("Sketch"),
    .accuracy = 101,
    .description = (pchar*)Sketch_desc,
    .pp = 1,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mimic_on_effect,
    .animation = (u8*)&SketchAnimation,
	},

    {
    /*Triple Kick*/
    .name = _("Triple Kick"),
    .accuracy = 90,
    .base_power = 10,
    .description = (pchar*)Triple_Kick_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .multi_hit = {3, 3},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = triple_kick_on_base_power,
    .animation = (u8*)&TripleKickAnimation,
	},

    {
    /*Thief*/
    .name = _("Thief"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Thief_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ThiefAnimation,
	},

    {
    /*Spider Web*/
    .name = _("Spider Web"),
    .accuracy = 101,
    .description = (pchar*)Spider_Web_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SpiderWebAnimation,
	},

    {
    /*Mind Reader*/
    .name = _("Mind Reader"),
    .accuracy = 101,
    .description = (pchar*)Mind_Reader_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mind_reader_on_effect,
    .animation = (u8*)&MindReaderAnimation,
	},

    {
    /*Nightmare*/
    .name = _("Nightmare"),
    .accuracy = 100,
    .description = (pchar*)Nightmare_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = nightmare_on_tryhit,
    .animation = (u8*)&NightmareAnimation,
	},

    {
    /*Flame Wheel*/
    .name = _("Flame Wheel"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Flame_Wheel_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_DEFROST | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&FlameWheelAnimation,
	},

    {
    /*Snore*/
    .name = _("Snore"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Snore_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .on_tryhit_move = snore_on_tryhit,
    .animation = (u8*)&SnoreAnimation,
	},

    {
    /*Curse*/
    .name = _("Curse"),
    .accuracy = 101,
    .description = (pchar*)Curse_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = curse_on_tryhit,
    .animation = (u8*)&CurseAnimation,
	},

    {
    /*Flail*/
    .name = _("Flail"),
    .accuracy = 100,
    .description = (pchar*)Flail_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = flail_on_base_power,
    .animation = (u8*)&FlailAnimation,
	},

    {
    /* Conversion 2 */
    .name = _("Conversion 2"),
    .accuracy = 101,
    .description = (pchar*)Conversion_2_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = conversion_two_on_effect,
    .animation = (u8*)&Conversion2Animation,
	},

    {
    /*Aeroblast*/
    .name = _("Aeroblast"),
    .accuracy = 95,
    .base_power = 100,
    .description = (pchar*)Aeroblast_desc,
    .pp = 5,
    .crit_ratio = 1,
    .category = MOVE_SPECIAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AeroblastAnimation,
	},

    {
    /*Cotton Spore*/
    .name = _("Cotton Spore"),
    .accuracy = 100,
    .description = (pchar*)Cotton_Spore_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_2,
    .on_effect_cb = cotton_spore_on_tryhit_move,
    .animation = (u8*)&CottonSporeAnimation,
	},

    {
    /*Reversal*/
    .name = _("Reversal"),
    .accuracy = 100,
    .description = (pchar*)Reversal_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ReversalAnimation,
	},

    {
    /*Spite*/
    .name = _("Spite"),
    .accuracy = 100,
    .description = (pchar*)Spite_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = spite_on_effect,
    .animation = (u8*)&SpiteAnimation,
	},

    {
    /*Powder Snow*/
    .name = _("Powder Snow"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Powder_Snow_desc,
    .pp = 25,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &freeze_10_procs,
    .animation = (u8*)&PowderSnowAnimation,
	},

    {
    /*Protect*/
    .name = _("Protect"),
    .accuracy = 101,
    .description = (pchar*)Protect_desc,
    .pp = 10,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = protect_on_effect,
    .animation = (u8*)&ProtectAnimation,
	},

    {
    /*Mach Punch*/
    .name = _("Mach Punch"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Mach_Punch_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MachPunchAnimation,
	},

    {
    /*Scary Face*/
    .name = _("Scary Face"),
    .accuracy = 100,
    .description = (pchar*)Scary_Face_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_2,
    .animation = (u8*)&ScaryFaceAnimation,
	},

    {
    /*Feint Attack*/
    .name = _("Feint Attack"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Feint_Attack_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FeintAttackAnimation,
	},

    {
    /*Sweet Kiss*/
    .name = _("Sweet Kiss"),
    .accuracy = 75,
    .description = (pchar*)Sweet_Kiss_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_100_procs,
    .animation = (u8*)&SweetKissAnimation,
	},

    {
    /*Belly Drum*/
    .name = _("Belly Drum"),
    .accuracy = 101,
    .description = (pchar*)Belly_Drum_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = belly_drum_effect,
    .animation = (u8*)&BellyDrumAnimation,
	},

    {
    /*Sludge Bomb*/
    .name = _("Sludge Bomb"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Sludge_Bomb_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_30_procs,
    .animation = (u8*)&SludgeBombAnimation,
	},

    {
    /* Mud-Slap*/
    .name = _("Mud-Slap"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Mud_Slap_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1,
    .animation = (u8*)&MudSlapAnimation,
	},

    {
    /*Octazooka*/
    .name = _("Octazooka"),
    .accuracy = 85,
    .base_power = 65,
    .description = (pchar*)Octazooka_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1_chance_50,
    .animation = (u8*)&OctazookaAnimation,
	},

    {
    /*Spikes*/
    .name = _("Spikes"),
    .accuracy = 101,
    .description = (pchar*)Spikes_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_GROUND,
    .m_flags = FLAG_REFLECTABLE,
    .procs = &basic_proc,
    .animation = (u8*)&SpikesAnimation,
	},

    {
    /*Zap Cannon*/
    .name = _("Zap Cannon"),
    .accuracy = 50,
    .base_power = 120,
    .description = (pchar*)Zap_Cannon_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_100_procs,
    .animation = (u8*)&ZapCannonAnimation,
	},

    {
    /*Foresight*/
    .name = _("Foresight"),
    .accuracy = 101,
    .description = (pchar*)Foresight_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = foresight_effect,
    .animation = (u8*)&ForesightAnimation,
	},

    {
    /*Destiny Bond*/
    .name = _("Destiny Bond"),
    .accuracy = 101,
    .description = (pchar*)Destiny_Bond_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_AUTHENTIC | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = destiny_bond_on_effect,
    .animation = (u8*)&DestinyBondAnimation,
	},

    {
    /*Perish Song*/
    .name = _("Perish Song"),
    .accuracy = 101,
    .description = (pchar*)Perish_Song_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_HITS_ALL,
    .procs = &basic_proc,
    .before_move = perish_song_before_move,
    .on_effect_cb = perish_song_on_effect,
    .on_after_move = perish_song_on_after_move,
    .animation = (u8*)&PerishSongAnimation,
	},

    {
    /*Icy Wind*/
    .name = _("Icy Wind"),
    .accuracy = 95,
    .base_power = 55,
    .description = (pchar*)Icy_Wind_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_1,
    .animation = (u8*)&IcyWindAnimation,
	},

    {
    /*Detect*/
    .name = _("Detect"),
    .accuracy = 101,
    .description = (pchar*)Detect_desc,
    .pp = 5,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = protect_on_effect,
    .animation = (u8*)&DetectAnimation,
	},

    {
    /*Bone Rush*/
    .name = _("Bone Rush"),
    .accuracy = 90,
    .base_power = 25,
    .description = (pchar*)Bone_Rush_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .multi_hit = {2, 5},
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BoneRushAnimation,
	},

    {
    /* Lock-on */
    .name = _("Lock-On"),
    .accuracy = 101,
    .description = (pchar*)Lock_On_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mind_reader_on_effect,
    .animation = (u8*)&LockOnAnimation,
	},

    {
    /*Outrage*/
    .name = _("Outrage"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Outrage_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = thrash_on_tryhit_move,
    .on_move_fail = thrash_on_move_fail,
    .on_after_move = thrash_on_after_move,
    .animation = (u8*)&OutrageAnimation,
	},

    {
    /*Sandstorm*/
    .name = _("Sandstorm"),
    .accuracy = 101,
    .description = (pchar*)Sandstorm_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_ROCK,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = sandstorm_on_effect,
    .animation = (u8*)&SandstormAnimation,
	},

    {
    /*Giga drain*/
    .name = _("Giga drain"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Giga_Drain_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
	.drain = 50,
    .m_flags = FLAG_HEAL | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&GigaDrainAnimation,
	},

    {
    /*Endure*/
    .name = _("Endure"),
    .accuracy = 101,
    .description = (pchar*)Endure_desc,
    .pp = 10,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = endure_on_effect,
    .animation = (u8*)&EndureAnimation,
	},

    {
    /*Charm*/
    .name = _("Charm"),
    .accuracy = 100,
    .description = (pchar*)Charm_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_atk_2,
    .animation = (u8*)&CharmAnimation,
	},

    {
    /*Rollout*/
    .name = _("Rollout"),
    .accuracy = 90,
    .base_power = 30,
    .description = (pchar*)Rollout_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = rollout_on_before_move,
    .on_move_fail = rollout_on_move_fail,
    .on_base_power_move = rollout_on_base_power_move,
    .animation = (u8*)&RolloutAnimation,
	},

    {
    /*False Swipe*/
    .name = _("False Swipe"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)False_Swipe_desc,
    .pp = 40,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = false_swipe_on_damage,
    .animation = (u8*)&FalseSwipeAnimation,
	},

    {
    /*Swagger*/
    .name = _("Swagger"),
    .accuracy = 85,
    .description = (pchar*)Swagger_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_raise_atk_2_confuse,
    .animation = (u8*)&SwaggerAnimation,
	},

    {
    /*Milk Drink*/
    .name = _("Milk Drink"),
    .accuracy = 101,
    .description = (pchar*)Milk_Drink_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
	.heal = 50,
    .m_flags = FLAG_SNATCH | FLAG_HEAL,
    .procs = &basic_proc,
    .animation = (u8*)&MilkDrinkAnimation,
	},

    {
    /*Spark*/
    .name = _("Spark"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Spark_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .animation = (u8*)&SparkAnimation,
	},

    {
    /*Fury Cutter*/
    .name = _("Fury Cutter"),
    .accuracy = 95,
    .base_power = 40,
    .description = (pchar*)Fury_Cutter_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = fury_cutter_on_base_power_move,
    .animation = (u8*)&FuryCutterAnimation,
	},

    {
    /*Steel Wing*/
    .name = _("Steel Wing"),
    .accuracy = 90,
    .base_power = 70,
    .description = (pchar*)Steel_Wing_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_raise_def_1_10,
    .animation = (u8*)&SteelWingAnimation,
	},

    {
    /*Mean Look*/
    .name = _("Mean Look"),
    .accuracy = 101,
    .description = (pchar*)Mean_Look_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = mean_look_on_effect,
    .animation = (u8*)&MeanLookAnimation,
	},

    {
    /*Attract*/
    .name = _("Attract"),
    .accuracy = 100,
    .description = (pchar*)Attract_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = attract_on_effect,
    .animation = (u8*)&AttractAnimation,
	},

    {
    /*Sleep Talk*/
    .name = _("Sleep Talk"),
    .accuracy = 101,
    .description = (pchar*)Sleep_Talk_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = sleep_talk_before_move,
    .on_modify_move = sleep_talk_on_modify_move,
    .animation = (u8*)&SleepTalkAnimation,
	},

    {
    /*Heal Bell*/
    .name = _("Heal Bell"),
    .accuracy = 101,
    .description = (pchar*)Heal_Bell_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_AUTHENTIC | FLAG_SOUND | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = heal_bell_on_effect,
    .animation = (u8*)&HealBellAnimation,
	},

    {
    /*Return*/
    .name = _("Return"),
    .accuracy = 100,
    .description = (pchar*)Return_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = frustration_on_damage,
    .animation = (u8*)&ReturnAnimation,
	},

    {
    /*Present*/
    .name = _("Present"),
    .accuracy = 90,
    .description = (pchar*)Present_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.on_modify_move = present_on_modify_move,
    .animation = (u8*)&PresentAnimation,
	},

    {
    /*Frustration*/
    .name = _("Frustration"),
    .accuracy = 100,
    .description = (pchar*)Frustration_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = return_on_damage,
    .animation = (u8*)&FrustrationAnimation,
	},

    {
    /*Safeguard*/
    .name = _("Safeguard"),
    .accuracy = 101,
    .description = (pchar*)Safeguard_desc,
    .pp = 25,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = safe_guard_on_effect,
    .animation = (u8*)&SafeguardAnimation,
	},

    {
    /*Pain Split*/
    .name = _("Pain Split"),
    .accuracy = 101,
    .description = (pchar*)Pain_Split_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = pain_split_on_effect,
    .animation = (u8*)&PainSplitAnimation,
	},

    {
    /*Sacred Fire*/
    .name = _("Sacred Fire"),
    .accuracy = 95,
    .base_power = 100,
    .description = (pchar*)Sacred_Fire_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_DEFROST | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_burn_50,
    .animation = (u8*)&SacredFireAnimation,
	},

    {
    /*Magnitude*/
    .name = _("Magnitude"),
    .accuracy = 100,
    .description = (pchar*)Magnitude_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_base_power_move = magnitude_on_base_power,
    .animation = (u8*)&MagnitudeAnimation,
	},

    {
    /*Dynamic Punch*/
    .name = _("Dynamic Punch"),
    .accuracy = 50,
    .base_power = 100,
    .description = (pchar*)Dynamic_Punch_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_100_procs,
    .animation = (u8*)&DynamicPunchAnimation,
	},

    {
    /*Megahorn*/
    .name = _("Megahorn"),
    .accuracy = 85,
    .base_power = 120,
    .description = (pchar*)Megahorn_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MegahornAnimation,
	},

    {
    /*Dragon Breath*/
    .name = _("Dragon Breath"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Dragon_Breath_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .animation = (u8*)&DragonBreathAnimation,
	},

    {
    /*Baton Pass*/
    .name = _("Baton Pass"),
    .accuracy = 101,
    .description = (pchar*)Baton_Pass_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BatonPassAnimation,
	},

    {
    /*Encore*/
    .name = _("Encore"),
    .accuracy = 100,
    .description = (pchar*)Encore_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = encore_on_tryhit,
    .on_effect_cb = encore_on_effect,
    .animation = (u8*)&EncoreAnimation,
	},

    {
    /*Pursuit*/
    .name = _("Pursuit"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Pursuit_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = pursuit_on_before_turn,
    .on_base_power_move = pursuit_on_basepower,
    .animation = (u8*)&PursuitAnimation,
	},

    {
    /*Rapid Spin*/
    .name = _("Rapid Spin"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Rapid_Spin_desc,
    .pp = 40,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RapidSpinAnimation,
	},

    {
    /*Sweet Scent*/
    .name = _("Sweet Scent"),
    .accuracy = 100,
    .description = (pchar*)Sweet_Scent_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_evn_2,
    .animation = (u8*)&SweetScentAnimation,
	},

    {
    /*Iron Tail*/
    .name = _("Iron Tail"),
    .accuracy = 75,
    .base_power = 100,
    .description = (pchar*)Iron_Tail_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_1_30,
    .animation = (u8*)&IronTailAnimation,
	},

    {
    /*Metal Claw*/
    .name = _("Metal Claw"),
    .accuracy = 95,
    .base_power = 50,
    .description = (pchar*)Metal_Claw_desc,
    .pp = 35,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_raise_atk_1_10,
    .animation = (u8*)&MetalClawAnimation,
	},

    {
    /*Vital Throw*/
    .name = _("Vital Throw"),
    .accuracy = 101,
    .base_power = 70,
    .description = (pchar*)Vital_Throw_desc,
	.pp = 10,
	.priority = -1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&VitalThrowAnimation,
	},

    {
    /*Morning Sun*/
    .name = _("Morning Sun"),
    .accuracy = 101,
    .description = (pchar*)Morning_Sun_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .heal = 50,
    .before_move = synthesis_before_move,
    .animation = (u8*)&MorningSunAnimation,
	},

    {
    /*Synthesis*/
    .name = _("Synthesis"),
    .accuracy = 101,
    .description = (pchar*)Synthesis_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .heal = 50,
    .before_move = synthesis_before_move,
    .animation = (u8*)&SynthesisAnimation,
	},

    {
    /*Moonlight*/
    .name = _("Moonlight"),
    .accuracy = 101,
    .description = (pchar*)Moonlight_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .before_move = synthesis_before_move,
    .animation = (u8*)&MoonlightAnimation,
	},

    {
    /*Hidden Power*/
    .name = _("Hidden Power"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Hidden_Power_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = hidden_power_on_modify_move,
    .animation = (u8*)&HiddenPowerAnimation,
	},

    {
    /*Cross Chop*/
    .name = _("Cross Chop"),
    .accuracy = 80,
    .base_power = 100,
    .description = (pchar*)Cross_Chop_desc,
    .pp = 5,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_TARGET | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT,
    .procs = &basic_proc,
    .animation = (u8*)&CrossChopAnimation,
	},

    {
    /*Twister*/
    .name = _("Twister"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Twister_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &basic_proc,
    .on_damage_move = twister_on_damage,
    .on_inv_tryhit_move = sky_uppercut_on_invulnerable_move,
    .animation = (u8*)&TwisterAnimation,
	},

    {
    /*Rain Dance*/
    .name = _("Rain Dance"),
    .accuracy = 101,
    .description = (pchar*)Rain_Dance_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_WATER,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = rain_dance_on_effect,
    .animation = (u8*)&RainDanceAnimation,
	},

    {
    /*Sunny Day*/
    .name = _("Sunny Day"),
    .accuracy = 101,
    .description = (pchar*)Sunny_Day_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_FIRE,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = sunny_day_on_effect,
    .animation = (u8*)&SunnyDayAnimation,
	},

    {
    /*Crunch*/
    .name = _("Crunch"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Crunch_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_20_procs,
    .animation = (u8*)&CrunchAnimation,
	},

    {
    /*Mirror Coat*/
    .name = _("Mirror Coat"),
    .accuracy = 100,
    .description = (pchar*)Mirror_Coat_desc,
    .pp = 20,
    .priority = -4,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = mirror_coat_before_turn,
    .on_tryhit_move = mirror_coat_on_tryhit,

    .animation = (u8*)&MirrorCoatAnimation,
	},

    {
    /*Psych Up*/
    .name = _("Psych Up"),
    .accuracy = 101,
    .description = (pchar*)Psych_Up_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = psych_up_on_effect,
    .animation = (u8*)&PsychUpAnimation,
	},

    {
    /*Extreme Speed*/
    .name = _("Extreme Speed"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Extreme_Speed_desc,
    .pp = 5,
    .priority = 2,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.priority = 1,
    .animation = (u8*)&ExtremeSpeedAnimation,
	},

    {
    /*Ancient Power*/
    .name = _("Ancient Power"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Ancient_Power_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = ancient_power_on_modify_move,
    .animation = (u8*)&AncientPowerAnimation,
	},

    {
    /*Shadow Ball*/
    .name = _("Shadow Ball"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Shadow_Ball_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &shadow_ball_procs,
    .animation = (u8*)&ShadowBallAnimation,
	},

    {
    /*Future Sight*/
    .name = _("Future Sight"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Future_Sight_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = future_sight_on_tryhit,
    .animation = (u8*)&FutureSightAnimation,
	},

    {
    /*Rock Smash*/
    .name = _("Rock Smash"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Rock_Smash_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_50_procs,
    .animation = (u8*)&RockSmashAnimation,
	},

    {
    /*Whirlpool*/
    .name = _("Whirlpool"),
    .accuracy = 85,
    .base_power = 35,
    .description = (pchar*)Whirlpool_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .on_base_power_move = whirlpool_on_base_power,
    .on_inv_tryhit_move = whirlpool_on_tryhit_invul,
    .animation = (u8*)&WhirlpoolAnimation,
	},

    {
    /*Beat Up*/
    .name = _("Beat Up"),
    .accuracy = 100,
    .description = (pchar*)Beat_Up_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = beatup_before_turn,
    .animation = (u8*)&BeatUpAnimation,
	},

    {
    /*Fake Out*/
    .name = _("Fake Out"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Fake_Out_desc,
    .pp = 10,
    .priority = 3,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = fakeout_on_tryhit,
    .flinch_chance = 100,
    .animation = (u8*)&FakeOutAnimation,
	},

    {
    /*Uproar*/
    .name = _("Uproar"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Uproar_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&UpRoarAnimation,
	},

    {
    /*Stockpile*/
    .name = _("Stockpile"),
    .accuracy = 101,
    .description = (pchar*)Stockpile_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_Def_SpD,
    .on_tryhit_move = stockpile_on_tryhit_move,
    .before_move = stockpile_before_move,
    .on_after_move = stockpile_on_after_move,
    .animation = (u8*)&StockpileAnimation,
	},

    {
    /*Spit Up*/
    .name = _("Spit Up"),
    .accuracy = 100,
    .description = (pchar*)Spit_Up_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = spit_up_on_tryhit_move,
    .on_base_power_move = spit_up_on_base_power_move,
    .animation = (u8*)&SpitUpAnimation,
	},

    {
    /*Swallow*/
    .name = _("Swallow"),
    .accuracy = 101,
    .description = (pchar*)Swallow_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = swallow_on_tryhit_move,
    .animation = (u8*)&SwallowAnimation,
	},

    {
    /*Heat Wave*/
    .name = _("Heat Wave"),
    .accuracy = 90,
    .base_power = 95,
    .description = (pchar*)Heat_Wave_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&HeatWaveAnimation,
	},

    {
    /*Hail*/
    .name = _("Hail"),
    .accuracy = 101,
    .description = (pchar*)Hail_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_ICE,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = hail_on_effect,
    .animation = (u8*)&HailAnimation,
	},

    {
    /*Torment*/
    .name = _("Torment"),
    .accuracy = 100,
    .description = (pchar*)Torment_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = torment_on_effect,
    .animation = (u8*)&TormentAnimation,
	},

    {
    /*Flatter*/
    .name = _("Flatter"),
    .accuracy = 100,
    .description = (pchar*)Flatter_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &flatter_procs,
    .animation = (u8*)&FlatterAnimation,
	},

    {
    /* Will-O-Wisp */
    .name = _("Will-O-Wisp"),
    .accuracy = 85,
    .description = (pchar*)Will_O_Wisp_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_FIRE,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_100_procs,
    .animation = (u8*)&WillOWispAnimation,
	},

    {
    /*Memento*/
    .name = _("Memento"),
    .accuracy = 100,
    .description = (pchar*)Memento_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags =  FLAG_MIRROR | FLAG_PROTECT | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = memento_on_effect,
    .animation = (u8*)&MementoAnimation,
	},

    {
    /*Facade*/
    .name = _("Facade"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Facade_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = facade_on_base_power_move,
    .animation = (u8*)&FacadeAnimation,
	},

    {
    /*Focus Punch*/
    .name = _("Focus Punch"),
    .accuracy = 100,
    .base_power = 150,
    .description = (pchar*)Focus_Punch_desc,
    .pp = 20,
    .priority = -3,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = focus_punch_before_turn,
    .animation = (u8*)&FocusPunchAnimation,
	},

    {
    /*Smelling Salts*/
    .name = _("Smelling Salts"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Smelling_Salts_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = smelling_salts_on_effect,
    .on_base_power_move = smelling_salts_on_base_power,
    .animation = (u8*)&SmellingSaltsAnimation,
	},

    {
    /*Follow Me*/
    .name = _("Follow Me"),
    .accuracy = 101,
    .description = (pchar*)Follow_Me_desc,
    .pp = 20,
    .priority = 2,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = rage_powder_on_effect,
    .animation = (u8*)&FollowMeAnimation,
	},

    {
    /*Nature Power*/
    .name = _("Nature Power"),
    .accuracy = 101,
    .description = (pchar*)Nature_Power_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = nature_power_on_tryhit,
    .animation = (u8*)&NaturePowerAnimation,
	},

    {
    /*Charge*/
    .name = _("Charge"),
    .accuracy = 101,
    .description = (pchar*)Charge_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_spDef_1,
    .on_effect_cb = charge_on_effect,
    .animation = (u8*)&ChargeAnimation,
	},

    {
    /*Taunt*/
    .name = _("Taunt"),
    .accuracy = 100,
    .description = (pchar*)Taunt_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = taunt_on_effect,
    .before_move = taunt_on_before_move,
    .animation = (u8*)&TauntAnimation,
	},

    {
    /*Helping Hand*/
    .name = _("Helping Hand"),
    .accuracy = 101,
    .description = (pchar*)Helping_Hand_desc,
    .pp = 20,
    .priority = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_HITS_ALLY,
    .procs = &basic_proc,
    .animation = (u8*)&HelpingHandAnimation,
	},

    {
    /*Trick*/
    .name = _("Trick"),
    .accuracy = 100,
    .description = (pchar*)Trick_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&TrickAnimation,
	},

    {
    /*Role Play*/
    .name = _("Role Play"),
    .accuracy = 101,
    .description = (pchar*)Role_Play_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = role_play_on_effect,
    .animation = (u8*)&RolePlayAnimation,
	},

    {
    /*Wish*/
    .name = _("Wish"),
    .accuracy = 101,
    .description = (pchar*)Wish_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH,
    .procs = &basic_proc,
    .on_effect_cb = wish_on_effect,
    .animation = (u8*)&WishAnimation,
	},

    {
    /*Assist*/
    .name = _("Assist"),
    .accuracy = 101,
    .description = (pchar*)Assist_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = assist_on_modify_move,
    .animation = (u8*)&AssistAnimation,
	},

    {
    /*Ingrain*/
    .name = _("Ingrain"),
    .accuracy = 101,
    .description = (pchar*)Ingrain_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = ingrain_on_effect,
    .animation = (u8*)&IngrainAnimation,
	},

    {
    /*Superpower*/
    .name = _("Superpower"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Superpower_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &dec_user_atk_def_procs,
    .animation = (u8*)&SuperpowerAnimation,
	},

    {
    /*Magic Coat*/
    .name = _("Magic Coat"),
    .accuracy = 101,
    .description = (pchar*)Magic_Coat_desc,
    .pp = 15,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = magic_coat_on_tryhit,
    .animation = (u8*)&MagicCoatAnimation,
	},

    {
    /*Recycle*/
    .name = _("Recycle"),
    .accuracy = 101,
    .description = (pchar*)Recycle_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH,
    .procs = &basic_proc,
    .animation = (u8*)&RecycleAnimation,
	},

    {
    /*Revenge*/
    .name = _("Revenge"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Revenge_desc,
    .pp = 10,
    .priority = -4,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = avalanche_on_base_power,
    .animation = (u8*)&RevengeAnimation,
	},

    {
    /*Brick Break*/
    .name = _("Brick Break"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Brick_Break_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = brickbreak_on_tryhit,
    .animation = (u8*)&BrickBreakAnimation,
	},

    {
    /*Yawn*/
    .name = _("Yawn"),
    .accuracy = 101,
    .description = (pchar*)Yawn_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = yawn_on_tryhit,
    .on_effect_cb = yawn_on_effect,
    .animation = (u8*)&YawnAnimation,
	},

    {
    /*Knock Off*/
    .name = _("Knock Off"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Knock_Off_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&KnockOffAnimation,
	},

    {
    /*Endeavor*/
    .name = _("Endeavor"),
    .accuracy = 100,
    .description = (pchar*)Endeavor_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = endeavor_on_tryhit,
    .on_damage_move = endeavor_on_dmg,
    .animation = (u8*)&EndeavorAnimation,
	},

    {
    /*Eruption*/
    .name = _("Eruption"),
    .accuracy = 100,
    .base_power = 150,
    .description = (pchar*)Eruption_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_base_power_move = water_spout_on_base_power_move,
    .animation = (u8*)&EruptionAnimation,
	},

    {
    /*Skill Swap*/
    .name = _("Skill Swap"),
    .accuracy = 101,
    .description = (pchar*)Skill_Swap_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = skill_swap_on_effect,
    .animation = (u8*)&SkillSwapAnimation,
	},

    {
    /*Imprison*/
    .name = _("Imprison"),
    .accuracy = 101,
    .description = (pchar*)Imprison_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH |  FLAG_AUTHENTIC | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = imprison_on_effect,
    .animation = (u8*)&ImprisonAnimation,
	},

    {
    /*Refresh*/
    .name = _("Refresh"),
    .accuracy = 101,
    .description = (pchar*)Refresh_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = refresh_on_effect,
    .animation = (u8*)&RefreshAnimation,
	},

    {
    /*Grudge*/
    .name = _("Grudge"),
    .accuracy = 101,
    .description = (pchar*)Grudge_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_GHOST,
    .m_flags = FLAG_AUTHENTIC | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = grudge_on_effect,
    .animation = (u8*)&GrudgeAnimation,
	},

    {
    /*Snatch*/
    .name = _("Snatch"),
    .accuracy = 101,
    .description = (pchar*)Snatch_desc,
    .pp = 10,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = snatch_on_effect,
    .animation = (u8*)&SnatchAnimation,
	},

    {
    /*Secret Power*/
    .name = _("Secret Power"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Secret_Power_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = secret_power_on_modify,
    .animation = (u8*)&SecretPowerAnimation,
	},

    {
    /*Dive*/
    .name = _("Dive"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Dive_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CHARGE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = dive_before_move,
    .animation = (u8*)&DiveAnimation,
	},

    {
    /*Arm Thrust*/
    .name = _("Arm Thrust"),
    .accuracy = 100,
    .base_power = 15,
    .description = (pchar*)Arm_Thrust_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ArmThrustAnimation,
	},

    {
    /*Camouflage*/
    .name = _("Camouflage"),
    .accuracy = 101,
    .description = (pchar*)Camouflage_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH |  FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = camouflage_on_effect,
    .animation = (u8*)&CamouflageAnimation,
	},

    {
    /*Tail Glow*/
    .name = _("Tail Glow"),
    .accuracy = 101,
    .description = (pchar*)Tail_Glow_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &inc_user_spa_3_procs,
    .animation = (u8*)&TailGlowAnimation,
	},

    {
    /*Luster Purge*/
    .name = _("Luster Purge"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Luster_Purge_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &dec_SpD_50_procs,
    .animation = (u8*)&LusterPurgeAnimation,
	},

    {
    /*Mist Ball*/
    .name = _("Mist Ball"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Mist_Ball_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &dec_SpA_50_procs,
    .animation = (u8*)&MistBallAnimation,
	},

    {
    /*Feather Dance*/
    .name = _("Feather Dance"),
    .accuracy = 100,
    .description = (pchar*)Feather_Dance_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_FLYING,
    .m_flags = FLAG_DANCE | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_atk_2,
    .animation = (u8*)&FeatherDanceAnimation,
	},

    {
    /*Teeter Dance*/
    .name = _("Teeter Dance"),
    .accuracy = 100,
    .description = (pchar*)Teeter_Dance_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_DANCE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_100_procs,
    .animation = (u8*)&TeeterDanceAnimation,
	},

    {
    /*Blaze Kick*/
    .name = _("Blaze Kick"),
    .accuracy = 90,
    .base_power = 85,
    .description = (pchar*)Blaze_Kick_desc,
    .pp = 10,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .animation = (u8*)&BlazeKickAnimation,
	},

    {
    /*Mud Sport*/
    .name = _("Mud Sport"),
    .accuracy = 101,
    .description = (pchar*)Mud_Sport_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GROUND,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = mud_sport_on_effect,
    .animation = (u8*)&MudSportAnimation,
	},

    {
    /*Ice Ball*/
    .name = _("Ice Ball"),
    .accuracy = 90,
    .base_power = 30,
    .description = (pchar*)Ice_Ball_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_BULLET | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = rollout_on_before_move,
    .on_move_fail = rollout_on_move_fail,
    .on_base_power_move = rollout_on_base_power_move,
    .animation = (u8*)&IceBallAnimation,
	},

    {
    /*Needle Arm*/
    .name = _("Needle Arm"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Needle_Arm_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&NeedleArmAnimation,
	},

    {
    /*Slack Off*/
    .name = _("Slack Off"),
    .accuracy = 101,
    .description = (pchar*)Slack_Off_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
	.heal = 50,
    .procs = &basic_proc,

    .animation = (u8*)&SlackOffAnimation,
	},

    {
    /*Hyper Voice*/
    .name = _("Hyper Voice"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Hyper_Voice_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HyperVoiceAnimation,
	},

    {
    /*Poison Fang*/
    .name = _("Poison Fang"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Poison_Fang_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &bad_poison_50_procs,
    .animation = (u8*)&PoisonFangAnimation,
	},

    {
    /*Crush Claw*/
    .name = _("Crush Claw"),
    .accuracy = 95,
    .base_power = 75,
    .description = (pchar*)Crush_Claw_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_50_procs,
    .animation = (u8*)&CrushClawAnimation,
	},

    {
    /*Blast Burn*/
    .name = _("Blast Burn"),
    .accuracy = 90,
    .base_power = 150,
    .description = (pchar*)Blast_Burn_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_RECHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BlastBurnAnimation,
	},

    {
    /*Hydro Cannon*/
    .name = _("Hydro Cannon"),
    .accuracy = 100,
    .base_power = 150,
    .description = (pchar*)Hydro_Cannon_desc,
    .priority = 1,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_RECHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HydroCannonAnimation,
	},

    {
    /*Meteor Mash*/
    .name = _("Meteor Mash"),
    .accuracy = 90,
    .base_power = 90,
    .description = (pchar*)Meteor_Mash_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &raise_user_atk_20,
    .animation = (u8*)&MeteorMashAnimation,
	},

    {
    /*Astonish*/
    .name = _("Astonish"),
    .accuracy = 100,
    .base_power = 30,
    .description = (pchar*)Astonish_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&AstonishAnimation,
	},

    {
    /*Weather Ball*/
    .name = _("Weather Ball"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Weather_Ball_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = weather_ball_on_modify_move,
    .animation = (u8*)&WeatherBallAnimation,
	},

    {
    /*Aromatherapy*/
    .name = _("Aromatherapy"),
    .accuracy = 101,
    .description = (pchar*)Aromatherapy_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = aromatherapy_on_effect,
    .animation = (u8*)&AromatherapyAnimation,
	},

    {
    /*Fake Tears*/
    .name = _("Fake Tears"),
    .accuracy = 100,
    .description = (pchar*)Fake_Tears_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_2,
    .animation = (u8*)&FakeTearsAnimation,
	},

    {
    /*Air Cutter*/
    .name = _("Air Cutter"),
    .accuracy = 95,
    .base_power = 60,
    .description = (pchar*)Air_Cutter_desc,
    .pp = 25,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AirCutterAnimation,
	},

    {
    /*Overheat*/
    .name = _("Overheat"),
    .accuracy = 90,
    .base_power = 130,
    .description = (pchar*)Overheat_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_spAtk_2,
    .animation = (u8*)&OverheatAnimation,
	},

    {
    /*Odor Sleuth*/
    .name = _("Odor Sleuth"),
    .accuracy = 101,
    .description = (pchar*)Odor_Sleuth_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = odor_sleuth_effect,
    .animation = (u8*)&OdorSleuthAnimation,
	},

    {
    /*Rock Tomb*/
    .name = _("Rock Tomb"),
    .accuracy = 95,
    .base_power = 60,
    .description = (pchar*)Rock_Tomb_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = & target_lower_spd_1,
    .animation = (u8*)&RockTombAnimation,
	},

    {
    /*Silver Wind*/
    .name = _("Silver Wind"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Silver_Wind_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &ancient_power_procs,
    .animation = (u8*)&SilverWindAnimation,
	},

    {
    /*Metal Sound*/
    .name = _("Metal Sound"),
    .accuracy = 85,
    .description = (pchar*)Metal_Sound_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_STEEL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_2,
    .animation = (u8*)&MetalSoundAnimation,
	},

    {
    /*Grass Whistle*/
    .name = _("Grass Whistle"),
    .accuracy = 55,
    .description = (pchar*)Grass_Whistle_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&GrassWhistleAnimation,
	},

    {
    /*Tickle*/
    .name = _("Tickle"),
    .accuracy = 100,
    .description = (pchar*)Tickle_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_targ_atk_def,
    .animation = (u8*)&TickleAnimation,
	},

    {
    /*Cosmic Power*/
    .name = _("Cosmic Power"),
    .accuracy = 101,
    .description = (pchar*)Cosmic_Power_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_Def_SpD,
    .animation = (u8*)&CosmicPowerAnimation,
	},

    {
    /*Water Spout*/
    .name = _("Water Spout"),
    .accuracy = 100,
    .base_power = 150,
    .description = (pchar*)Water_Spout_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_base_power_move = water_spout_on_base_power_move,
    .animation = (u8*)&WaterSpoutAnimation,
	},

    {
    /*Signal Beam*/
    .name = _("Signal Beam"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Signal_Beam_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_10_procs,
    .animation = (u8*)&SignalBeamAnimation,
	},

    {
    /*Shadow Punch*/
    .name = _("Shadow Punch"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Shadow_Punch_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ShadowpunchAnimation,
	},

    {
    /*Extrasensory*/
    .name = _("Extrasensory"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Extrasensory_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags =  FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 10,
    .animation = (u8*)&ExtrasensoryAnimation,
	},

    {
    /*Sky Uppercut*/
    .name = _("Sky Uppercut"),
    .accuracy = 90,
    .base_power = 85,
    .description = (pchar*)Sky_Uppercut_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_inv_tryhit_move = sky_uppercut_on_invulnerable_move,
    .animation = (u8*)&SkyUppercutAnimation,
	},

    {
    /*Sand Tomb*/
    .name = _("Sand Tomb"),
    .accuracy = 85,
    .base_power = 35,
    .description = (pchar*)Sand_Tomb_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&SandTombAnimation,
	},

    {
    /*Sheer Cold*/
    .name = _("Sheer Cold"),
    .accuracy = 30,
    .description = (pchar*)Sheer_Cold_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_OHKO,
    .procs = &basic_proc,
    .on_tryhit_move = ohko_tryhit_move,
    .animation = (u8*)&SheerColdAnimation,
	},

    {
    /*Muddy Water*/
    .name = _("Muddy Water"),
    .accuracy = 85,
    .base_power = 90,
    .description = (pchar*)Muddy_Water_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_Acc,
    .animation = (u8*)&MuddyWaterAnimation,
	},

    {
    /*Bullet Seed*/
    .name = _("Bullet Seed"),
    .accuracy = 100,
    .base_power = 25,
    .description = (pchar*)Bullet_Seed_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .multi_hit = {2, 5},
    .m_flags = FLAG_BULLET | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BulletSeedAnimation,
	},

    {
    /*Aerial Ace*/
    .name = _("Aerial Ace"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Aerial_Ace_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AerialAceAnimation,
	},

    {
    /*Icicle Spear*/
    .name = _("Icicle Spear"),
    .accuracy = 100,
    .base_power = 25,
    .description = (pchar*)Icicle_Spear_desc,
    .pp = 30,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .multi_hit = {2, 5},
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&IcicleSpearAnimation,
	},

   {
    /*Iron Defense*/
    .name = _("Iron Defense"),
    .accuracy = 101,
    .description = (pchar*)Iron_Defense_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_STEEL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_def_2,
    .animation = (u8*)&IronDefenseAnimation,
	},

    {
    /*Block*/
    .name = _("Block"),
    .accuracy = 101,
    .description = (pchar*)Block_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = block_on_effect,
    .animation = (u8*)&BlockAnimation,
	},

    {
    /*Howl*/
    .name = _("Howl"),
    .accuracy = 101,
    .description = (pchar*)Howl_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_atk_1,
    .animation = (u8*)&HowlAnimation,
	},

    {
    /*Dragon Claw*/
    .name = _("Dragon Claw"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Dragon_Claw_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DragonClawAnimation,
	},

    {
    /*Frenzy Plant*/
    .name = _("Frenzy Plant"),
    .accuracy = 90,
    .base_power = 150,
    .description = (pchar*)Frenzy_Plant_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_RECHARGE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FrenzyPlantAnimation,
	},

    {
    /*Bulk Up*/
    .name = _("Bulk Up"),
    .accuracy = 101,
    .description = (pchar*)Bulk_Up_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_SNATCH,
    .procs = &bulk_up_procs,
    .animation = (u8*)&BulkUpAnimation,
	},

    {
    /*Bounce*/
    .name = _("Bounce"),
    .accuracy = 85,
    .base_power = 85,
    .description = (pchar*)Bounce_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CHARGE | FLAG_GRAVITY | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = bounce_before_move,
    .animation = (u8*)&BounceAnimation,
	},

    {
    /*Mud Shot*/
    .name = _("Mud Shot"),
    .accuracy = 95,
    .base_power = 55,
    .description = (pchar*)Mud_Shot_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_1,
    .animation = (u8*)&MudShotAnimation,
	},

    {
    /*Poison Tail*/
    .name = _("Poison Tail"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Poison_Tail_desc,
    .pp = 25,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_10_procs,
    .animation = (u8*)&PoisonTailAnimation,
	},

    {
    /*Covet*/
    .name = _("Covet"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Covet_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&CovetAnimation,
	},

    {
    /*Volt Tackle*/
    .name = _("Volt Tackle"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Volt_Tackle_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_10_procs,
	.recoil = 33,
    .animation = (u8*)&VoltTackleAnimation,
	},

    {
    /*Magical Leaf*/
    .name = _("Magical Leaf"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Magical_Leaf_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MagicalLeafAnimation,
	},

    {
    /*Water Sport*/
    .name = _("Water Sport"),
    .accuracy = 101,
    .description = (pchar*)Water_Sport_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_WATER,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = water_sport_on_effect,
    .animation = (u8*)&WaterSportAnimation,
	},

    {
    /*Calm Mind*/
    .name = _("Calm Mind"),
    .accuracy = 101,
    .description = (pchar*)Calm_Mind_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_spAtk_spDef_1,
    .animation = (u8*)&CalmMindAnimation,
	},

    {
    /*Leaf Blade*/
    .name = _("Leaf Blade"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Leaf_Blade_desc,
    .pp = 15,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&LeafBladeAnimation,
	},

    {
    /*Dragon Dance*/
    .name = _("Dragon Dance"),
    .accuracy = 101,
    .description = (pchar*)Dragon_Dance_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_ONSELF | FLAG_SNATCH,
	.procs = &dragon_dance_procs,
	.animation = (u8*)&DragonDanceAnimation,
	},

    {
    /*Rock Blast*/
    .name = _("Rock Blast"),
    .accuracy = 90,
    .base_power = 25,
    .description = (pchar*)Rock_Blast_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .multi_hit = {2, 5},
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RockBlastAnimation,
	},

    {
    /*Shock Wave*/
    .name = _("Shock Wave"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Shock_Wave_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ShockWaveAnimation,
	},

    {
    /*Water Pulse*/
    .name = _("Water Pulse"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Water_Pulse_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_PULSE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_20_procs,
    .animation = (u8*)&WaterPulseAnimation,
	},

    {
    /*Doom Desire*/
    .name = _("Doom Desire"),
    .accuracy = 100,
    .base_power = 140,
    .description = (pchar*)Doom_Desire_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = doom_desire_on_tryhit,
    .animation = (u8*)&DoomDesireAnimation,
	},

    {
    /*Psycho Boost*/
    .name = _("Psycho Boost"),
    .accuracy = 90,
    .base_power = 140,
    .description = (pchar*)Psycho_Boost_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_spAtk_2,
    .animation = (u8*)&PsychoBoostAnimation,
	},

    {
    /*Roost*/
    .name = _("Roost"),
    .accuracy = 101,
    .description = (pchar*)Roost_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_FLYING,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .heal = 50,
    .on_effect_cb = roost_on_effect,
    .animation = (u8*)&RoostAnimation,
	},

    {
    /*Gravity*/
    .name = _("Gravity"),
    .accuracy = 101,
    .description = (pchar*)Gravity_desc,
    .pp = 5,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = gravity_on_effect,
    .animation = (u8*)&GravityAnimation,
	},

    {
    /*Miracle Eye*/
    .name = _("Miracle Eye"),
    .accuracy = 101,
    .description = (pchar*)Miracle_Eye_desc,
    .pp = 40,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = miracle_eye_effect,
    .animation = (u8*)&MiracleEyeAnimation,
	},

    {
    /*Wake-up Slap */
    .name = _("Wake-Up Slap"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Wake_Up_Slap_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = wake_up_slap_on_effect,
    .on_base_power_move = wake_up_slap_on_base_power,
    .animation = (u8*)&WakeUpSlapAnimation,
	},

    {
    /*Hammer Arm*/
    .name = _("Hammer Arm"),
    .accuracy = 90,
    .base_power = 100,
    .description = (pchar*)Hammer_Arm_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_spd_1,
    .animation = (u8*)&HammerArmAnimation,
	},

    {
    /*Gyro Ball*/
    .name = _("Gyro Ball"),
    .accuracy = 100,
    .description = (pchar*)Gyro_Ball_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_BULLET | FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = gyro_ball_on_base_power,
    .animation = (u8*)&GyroBallAnimation,
	},

    {
    /*Healing Wish*/
    .name = _("Healing Wish"),
    .accuracy = 101,
    .description = (pchar*)Healing_Wish_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = lunar_dance_on_effect,
    .animation = (u8*)&HealingWishAnimation,
	},

    {
    /*Brine*/
    .name = _("Brine"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Brine_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = brine_on_base_power_move,
    .animation = (u8*)&BrineAnimation,
	},

    {
    /*Natural Gift*/
    .name = _("Natural Gift"),
    .accuracy = 100,
    .description = (pchar*)Natural_Gift_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&NaturalGiftAnimation,
	},

    {
    /*Feint*/
    .name = _("Feint"),
    .accuracy = 100,
    .base_power = 30,
    .description = (pchar*)Feint_desc,
    .pp = 10,
    .priority = 2,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = feint_on_before_move,
    .animation = (u8*)&FeintAnimation,
	},

    {
    /*Pluck*/
    .name = _("Pluck"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Pluck_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PluckAnimation,
	},

    {
    /*Tailwind*/
    .name = _("Tailwind"),
    .accuracy = 101,
    .description = (pchar*)Tailwind_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_FLYING,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = tailwind_on_effect,
    .animation = (u8*)&TailwindAnimation,
	},

    {
    /*Acupressure*/
    .name = _("Acupressure"),
    .accuracy = 101,
    .description = (pchar*)Acupressure_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_HITS_ALLY_OR_SELF,
    .procs = &basic_proc,
    .on_effect_cb = accupressure_on_effect,
    .animation = (u8*)&AcupressureAnimation,
	},

    {
    /*Metal Burst*/
    .name = _("Metal Burst"),
    .accuracy = 100,
    .description = (pchar*)Metal_Burst_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = metal_burst_before_turn,
    .on_tryhit_move = metal_burst_on_tryhit,
    .animation = (u8*)&MetalBurstAnimation,
	},

    {
    /* U-turn*/
    .name = _("U-turn"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)U_turn_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = volt_switch_on_effect,
    .animation = (u8*)&UturnAnimation,
	},

    {
    /*Close Combat*/
    .name = _("Close Combat"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Close_Combat_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_def_spDef_1,
    .animation = (u8*)&CloseCombatAnimation,
	},

    {
    /*Payback*/
    .name = _("Payback"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Payback_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = payback_on_base_power,
    .animation = (u8*)&PaybackAnimation,
	},

    {
    /*Assurance*/
    .name = _("Assurance"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Assurance_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = assurance_on_base_power,
    .animation = (u8*)&AssuranceAnimation,
	},

    {
    /*Embargo*/
    .name = _("Embargo"),
    .accuracy = 100,
    .description = (pchar*)Embargo_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&EmbargoAnimation,
	},

    {
    /*Fling*/
    .name = _("Fling"),
    .accuracy = 100,
    .description = (pchar*)Fling_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FlingAnimation,
	},

    {
    /*Psycho Shift*/
    .name = _("Psycho Shift"),
    .accuracy = 101,
    .description = (pchar*)Psycho_Shift_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = psycho_shift_effect,
    .animation = (u8*)&PsychoShiftAnimation,
	},

    {
    /*Trump Card*/
    .name = _("Trump Card"),
    .accuracy = 101,
    .description = (pchar*)Trump_Card_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = trump_card_on_base_power,
    .animation = (u8*)&TrumpCardAnimation,
	},

    {
    /*Heal Block*/
    .name = _("Heal Block"),
    .accuracy = 100,
    .description = (pchar*)Heal_Block_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_REFLECTABLE | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = heal_block_on_effect,
    .animation = (u8*)&HealBlockAnimation,
	},

    {
    /*Wring Out*/
    .name = _("Wring Out"),
    .accuracy = 100,
    .description = (pchar*)Wring_Out_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = crush_grip_on_base_power_move,
    .animation = (u8*)&WringOutAnimation,
	},

    {
    /*Power Trick*/
    .name = _("Power Trick"),
    .accuracy = 101,
    .description = (pchar*)Power_Trick_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_SNATCH,
    .procs = &basic_proc,
    .animation = (u8*)&PowerTrickAnimation,
	},

    {
    /*Gastro Acid*/
    .name = _("Gastro Acid"),
    .accuracy = 100,
    .description = (pchar*)Gastro_Acid_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = gastro_acid_effect,
    .animation = (u8*)&GastroAcidAnimation,
	},

    {
    /*Lucky Chant*/
    .name = _("Lucky Chant"),
    .accuracy = 101,
    .description = (pchar*)Lucky_Chant_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = lucky_chant_on_effect,
    .animation = (u8*)&LuckyChantAnimation,
	},

    {
    /*Me First*/
    .name = _("Me First"),
    .accuracy = 101,
    .description = (pchar*)Me_First_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = me_first_on_tryhit,
    .animation = (u8*)&MeFirstAnimation,
	},

    {
    /*Copycat*/
    .name = _("Copycat"),
    .accuracy = 101,
    .description = (pchar*)Copycat_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = copycat_on_modify_move,
    .animation = (u8*)&CopycatAnimation,
	},

    {
    /*Power Swap*/
    .name = _("Power Swap"),
    .accuracy = 101,
    .description = (pchar*)Power_Swap_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PowerSwapAnimation,
	},

    {
    /*Guard Swap*/
    .name = _("Guard Swap"),
    .accuracy = 101,
    .description = (pchar*)Guard_Swap_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&GuardSwapAnimation,
	},

    {
    /*Punishment*/
    .name = _("Punishment"),
    .accuracy = 100,
    .description = (pchar*)Punishment_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = punishment_on_base_power_move,
    .animation = (u8*)&PunishmentAnimation,
	},

    {
    /*Last Resort*/
    .name = _("Last Resort"),
    .accuracy = 100,
    .base_power = 140,
    .description = (pchar*)Last_Resort_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = last_resort_tryhit,
    .animation = (u8*)&LastResortAnimation,
	},

    {
    /*Worry Seed*/
    .name = _("Worry Seed"),
    .accuracy = 100,
    .description = (pchar*)Worry_Seed_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = worry_seed_effect,
    .animation = (u8*)&WorrySeedAnimation,
	},

    {
    /*Sucker Punch*/
    .name = _("Sucker Punch"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Sucker_Punch_desc,
    .pp = 5,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SuckerPunchAnimation,
	},

    {
    /*Toxic Spikes*/
    .name = _("Toxic Spikes"),
    .accuracy = 101,
    .description = (pchar*)Toxic_Spikes_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE,
    .procs = &basic_proc,
    .animation = (u8*)&ToxicSpikesAnimation,
	},

    {
    /*Aqua Ring*/
    .name = _("Aqua Ring"),
    .accuracy = 101,
    .description = (pchar*)Aqua_Ring_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_WATER,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = aqua_ring_effect_cb,
    .animation = (u8*)&AquaRingAnimation,
	},

    {
    /*Magnet Rise*/
    .name = _("Magnet Rise"),
    .accuracy = 101,
    .description = (pchar*)Magnet_Rise_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_SNATCH | FLAG_GRAVITY | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = magnet_rise_on_effect,
    .animation = (u8*)&MagnetRiseAnimation,
	},

    {
    /*Flare Blitz*/
    .name = _("Flare Blitz"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Flare_Blitz_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_DEFROST | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
	.recoil = 30,
    .animation = (u8*)&FlareBlitzAnimation,
	},

    {
    /*Force Palm*/
    .name = _("Force Palm"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Force_Palm_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .animation = (u8*)&ForcePalmAnimation,
	},

    {
    /*Aura Sphere*/
    .name = _("Aura Sphere"),
    .accuracy = 101,
    .base_power = 80,
    .description = (pchar*)Aura_Sphere_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PULSE | FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AuraSphereAnimation,
	},

    {
    /*Rock Polish*/
    .name = _("Rock Polish"),
    .accuracy = 101,
    .description = (pchar*)Rock_Polish_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_ROCK,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_spd_2,
    .animation = (u8*)&RockPolishAnimation,
	},

    {
    /*Poison Jab*/
    .name = _("Poison Jab"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Poison_Jab_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PoisonJabAnimation,
	},

    {
    /*Dark Pulse*/
    .name = _("Dark Pulse"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Dark_Pulse_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_PULSE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 20,
    .animation = (u8*)&DarkPulseAnimation,
	},

    {
    /*Night Slash*/
    .name = _("Night Slash"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Night_Slash_desc,
    .pp = 15,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&NightShadeAnimation,
	},

    {
    /*Aqua Tail*/
    .name = _("Aqua Tail"),
    .accuracy = 90,
    .base_power = 90,
    .description = (pchar*)Aqua_Tail_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AquaTailAnimation,
	},

    {
    /*Seed Bomb*/
    .name = _("Seed Bomb"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Seed_Bomb_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SeedBombAnimation,
	},

    {
    /*Air Slash*/
    .name = _("Air Slash"),
    .accuracy = 95,
    .base_power = 75,
    .description = (pchar*)Air_Slash_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
	.priority =1,
    .animation = (u8*)&AirSlashAnimation,
	},

    {
    /*X-Scissor */
    .name = _("X-Scissor"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)X_Scissor_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&XScissorAnimation,
	},

    {
    /*Bug Buzz*/
    .name = _("Bug Buzz"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Bug_Buzz_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &bug_buzz_procs,
    .animation = (u8*)&BugBuzzAnimation,
	},

    {
    /*Dragon Pulse*/
    .name = _("Dragon Pulse"),
    .accuracy = 100,
    .base_power = 85,
    .description = (pchar*)Dragon_Pulse_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_PULSE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DragonPulseAnimation,
	},

    {
    /*Dragon Rush*/
    .name = _("Dragon Rush"),
    .accuracy = 75,
    .base_power = 100,
    .description = (pchar*)Dragon_Rush_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 20,
    .on_modify_move = stomp_on_modify_move,
    .animation = (u8*)&DragonRushAnimation,
	},

    {
    /*Power Gem*/
    .name = _("Power Gem"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Power_Gem_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PowerGemAnimation,
	},

    {
    /* Drain Punch*/
    .name = _("Drain Punch"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*) Drain_Punch_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_HEAL | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .drain = 50,
    .animation = (u8*)&DrainPunchAnimation,
	},

    {
    /*Vacuum Wave*/
    .name = _("Vacuum Wave"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Vacuum_Wave_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&VacuumWaveAnimation,
	},

    {
    /*Focus Blast*/
    .name = _("Focus Blast"),
    .accuracy = 70,
    .base_power = 120,
    .description = (pchar*)Focus_Blast_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_1_10,
    .animation = (u8*)&FocusBlastAnimation,
	},

    {
    /*Energy Ball*/
    .name = _("Energy Ball"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Energy_Ball_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_1_10,
    .animation = (u8*)&EnergyBallAnimation,
	},

    {
    /*Brave Bird*/
    .name = _("Brave Bird"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Brave_Bird_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BraveBirdAnimation,
	},

    {
    /*Earth Power*/
    .name = _("Earth Power"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Earth_Power_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_1_10,
    .animation = (u8*)&EarthPowerAnimation,
	},

    {
    /*Switcheroo*/
    .name = _("Switcheroo"),
    .accuracy = 100,
    .description = (pchar*)Switcheroo_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SwitcherooAnimation,
	},

    {
    /*Giga Impact*/
    .name = _("Giga Impact"),
    .accuracy = 90,
    .base_power = 150,
    .description = (pchar*)Giga_Impact_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_RECHARGE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&GigaImpactAnimation,
	},

    {
    /*Nasty Plot*/
    .name = _("Nasty Plot"),
    .accuracy = 101,
    .description = (pchar*)Nasty_Plot_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &user_raise_spAtk_2,
    .animation = (u8*)&NastyPlotAnimation,
	},

    {
    /*Bullet Punch*/
    .name = _("Bullet Punch"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Bullet_Punch_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BulletPunchAnimation,
	},

    {
    /*Avalanche*/
    .name = _("Avalanche"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Avalanche_desc,
    .pp = 10,
    .priority = -4,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = avalanche_on_base_power,
    .animation = (u8*)&AvalancheAnimation,
	},

    {
    /*Ice Shard*/
    .name = _("Ice Shard"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Ice_Shard_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_SPECIAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&IceShardAnimation,
	},

    {
    /*Shadow Claw*/
    .name = _("Shadow Claw"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Shadow_Claw_desc,
    .pp = 15,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&ShadowClawAnimation,
	},

    {
    /*Thunder Fang*/
    .name = _("Thunder Fang"),
    .accuracy = 95,
    .base_power = 65,
    .description = (pchar*)Thunder_Fang_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_10_procs,
    .flinch_chance = 10,
    .animation = (u8*)&ThunderFangAnimation,
	},

    {
    /*Ice Fang*/
    .name = _("Ice Fang"),
    .accuracy = 95,
    .base_power = 65,
    .description = (pchar*)Ice_Fang_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &freeze_10_procs,
    .flinch_chance = 10,
    .animation = (u8*)&IceFangAnimation,
	},

    {
    /*Fire Fang*/
    .name = _("Fire Fang"),
    .accuracy = 95,
    .base_power = 65,
    .description = (pchar*)Fire_Fang_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_10_procs,
    .flinch_chance = 10,
    .animation = (u8*)&FireFangAnimation,
	},

    {
    /*Shadow Sneak*/
    .name = _("Shadow Sneak"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Shadow_Sneak_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.priority =1,
    .animation = (u8*)&ShadowSneakAnimation,
	},

    {
    /*Mud Bomb*/
    .name = _("Mud Bomb"),
    .accuracy = 85,
    .base_power = 65,
    .description = (pchar*)Mud_Bomb_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_acc_30,
    .animation = (u8*)&MudBombAnimation,
	},

    {
    /*Psycho Cut*/
    .name = _("Psycho Cut"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Psycho_Cut_desc,
    .pp = 20,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PsychoCutAnimation,
	},

    {
    /*Zen Headbutt*/
    .name = _("Zen Headbutt"),
    .accuracy = 90,
    .base_power = 80,
    .description = (pchar*)Zen_Headbutt_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 20,
    .animation = (u8*)&ZenHeadbuttAnimation,
	},

    {
    /*Mirror Shot*/
    .name = _("Mirror Shot"),
    .accuracy = 85,
    .base_power = 65,
    .description = (pchar*)Mirror_Shot_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_acc_30,
    .animation = (u8*)&MirrorShotAnimation,
	},

    {
    /*Flash Cannon*/
    .name = _("Flash Cannon"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Flash_Cannon_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spDef_1_10,
    .animation = (u8*)&FlashCannonAnimation,
	},

    {
    /*Rock Climb*/
    .name = _("Rock Climb"),
    .accuracy = 85,
    .base_power = 90,
    .description = (pchar*)Rock_Climb_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &confuse_30_procs,
    .animation = (u8*)&RockClimbAnimation,
	},

    {
    /*Defog*/
    .name = _("Defog"),
    .accuracy = 101,
    .description = (pchar*)Defog_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_FLYING,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_evn_1,
    .animation = (u8*)&DefogAnimation,
	},

    {
    /*Trick Room*/
    .name = _("Trick Room"),
    .accuracy = 101,
    .description = (pchar*)Trick_Room_desc,
    .pp = 5,
    .priority = -7,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = trick_room_on_effect,
    .animation = (u8*)&TrickRoomAnimation,
	},

    {
    /*Draco Meteor*/
    .name = _("Draco Meteor"),
    .accuracy = 90,
    .base_power = 130,
    .description = (pchar*)Draco_Meteor_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_spAtk_2,
    .animation = (u8*)&DracoMeteorAnimation,
	},

    {
    /*Discharge*/
    .name = _("Discharge"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Discharge_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_30_procs,
    .animation = (u8*)&DischargeAnimation,
	},

    {
    /*Lava Plume*/
    .name = _("Lava Plume"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Lava_Plume_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_30_procs,
    .animation = (u8*)&LavaPlumeAnimation,
	},

    {
    /*Leaf Storm*/
    .name = _("Leaf Storm"),
    .accuracy = 90,
    .base_power = 130,
    .description = (pchar*)Leaf_Storm_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_lower_spAtk_2,
    .animation = (u8*)&LeafStormAnimation,
	},

    {
    /*Power Whip*/
    .name = _("Power Whip"),
    .accuracy = 85,
    .base_power = 120,
    .description = (pchar*)Power_Whip_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PowerWhipAnimation,
	},

    {
    /*Rock Wrecker*/
    .name = _("Rock Wrecker"),
    .accuracy = 90,
    .base_power = 150,
    .description = (pchar*)Rock_Wrecker_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_RECHARGE | FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RockWreckerAnimation,
	},

    {
    /*Cross Poison*/
    .name = _("Cross Poison"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Cross_Poison_desc,
    .pp = 20,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_CONTACT | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_10_procs,
    .animation = (u8*)&CrossPoisonAnimation,
	},

    {
    /*Gunk Shot*/
    .name = _("Gunk Shot"),
    .accuracy = 80,
    .base_power = 120,
    .description = (pchar*)Gunk_Shot_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_30_procs,
    .animation = (u8*)&GunkShotAnimation,
	},

    {
    /*Iron Head*/
    .name = _("Iron Head"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Iron_Head_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&IronHeadAnimation,
	},

    {
    /*Magnet Bomb*/
    .name = _("Magnet Bomb"),
    .accuracy = 101,
    .base_power = 60,
    .description = (pchar*)Magnet_Bomb_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MagnetBombAnimation,
	},

    {
    /*Stone Edge*/
    .name = _("Stone Edge"),
    .accuracy = 80,
    .base_power = 100,
    .description = (pchar*)Stone_Edge_desc,
    .pp = 5,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&StoneEdgeAnimation,
	},

    {
    /*Captivate*/
    .name = _("Captivate"),
    .accuracy = 100,
    .description = (pchar*)Captivate_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_FOE_SIDE,
    .procs = &target_lower_spAtk_2,
    .on_tryhit_move = captivate_on_tryhit,
    .animation = (u8*)&CaptivateAnimation,
	},

    {
    /*Stealth Rock*/
    .name = _("Stealth Rock"),
    .accuracy = 101,
    .description = (pchar*)Stealth_Rock_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_ROCK,
    .m_flags = FLAG_REFLECTABLE,
    .procs = &basic_proc,
    .animation = (u8*)&StealthRockAnimation,
	},

    {
    /*Grass Knot*/
    .name = _("Grass Knot"),
    .accuracy = 100,
    .description = (pchar*)Grass_Knot_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = low_kick_on_base_power_move,
    .animation = (u8*)&GrassKnotAnimation,
	},

    {
    /*Bug Bite*/
    .name = _("Bug Bite"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Bug_Bite_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BugBiteAnimation,
	},

    {
    /*Charge Beam*/
    .name = _("Charge Beam"),
    .accuracy = 90,
    .base_power = 50,
    .description = (pchar*)Charge_Beam_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &charge_beam_procs,
    .animation = (u8*)&ChargeBeamAnimation,
	},

    {
    /*Wood Hammer*/
    .name = _("Wood Hammer"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Wood_Hammer_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.recoil = 25,
    .animation = (u8*)&WoodHammerAnimation,
	},

    {
    /*Aqua Jet*/
    .name = _("Aqua Jet"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Aqua_Jet_desc,
    .pp = 20,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AquaJetAnimation,
	},

    {
    /*Attack Order*/
    .name = _("Attack Order"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Attack_Order_desc,
    .pp = 15,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AttackOrderAnimation,
	},

    {
    /*Defend Order*/
    .name = _("Defend Order"),
    .accuracy = 101,
    .description = (pchar*)Defend_Order_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_Def_SpD,
    .animation = (u8*)&DefendOrderAnimation,
	},

    {
    /*Heal Order*/
    .name = _("Heal Order"),
    .accuracy = 101,
    .description = (pchar*)Heal_Order_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
	.heal = 50,
    .animation = (u8*)&HealOrderAnimation,
	},

    {
    /*Head Smash*/
    .name = _("Head Smash"),
    .accuracy = 80,
    .base_power = 150,
    .description = (pchar*)Head_Smash_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.recoil = 50,
    .animation = (u8*)&HeadSmashAnimation,
	},

    {
    /*Double Hit*/
    .name = _("Double Hit"),
    .accuracy = 90,
    .base_power = 35,
    .description = (pchar*)Double_Hit_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 2},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DoubleHitAnimation,
	},

    {
    /*Magma Storm*/
    .name = _("Magma Storm"),
    .accuracy = 75,
    .base_power = 100,
    .description = (pchar*)Magma_Storm_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&MagmaStormAnimation,
	},

    {
    /*Dark Void*/
    .name = _("Dark Void"),
    .accuracy = 50,
    .description = (pchar*)Dark_Void_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &sing_procs,
    .animation = (u8*)&DarkVoidAnimation,
	},

    {
    /*Ominous Wind*/
    .name = _("Ominous Wind"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Ominous_Wind_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &ancient_power_procs,
    .animation = (u8*)&OminousWindAnimation,
	},

    {
    /*Hone Claws*/
    .name = _("Hone Claws"),
    .accuracy = 101,
    .description = (pchar*)Hone_Claws_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_Atk_Acc,
    .animation = (u8*)&HoneClawsAnimation,
	},

    {
    /*Wide Guard*/
    .name = _("Wide Guard"),
    .accuracy = 101,
    .description = (pchar*)Wide_Guard_desc,
    .pp = 10,
    .priority = 3,
    .category = MOVE_STATUS,
    .type = TYPE_ROCK,
    .m_flags = FLAG_ONSELF | FLAG_SNATCH,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = wide_guard_on_effect,
    .animation = (u8*)&WideGuardAnimation,
	},

    {
    /*Guard Split*/
    .name = _("Guard Split"),
    .accuracy = 101,
    .description = (pchar*)Guard_Split_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = guard_split_on_effect,
    .animation = (u8*)&GuardSplitAnimation,
	},

    {
    /*Power Split*/
    .name = _("Power Split"),
    .accuracy = 101,
    .description = (pchar*)Power_Split_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = power_split_on_effect,
    .animation = (u8*)&PowerSplitAnimation,
	},

    {
    /*Psyshock*/
    .name = _("Psyshock"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Psyshock_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CATEGORY_OVERRIDE | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PsyshockAnimation,
	},

    {
    /*Venoshock*/
    .name = _("Venoshock"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Venoshock_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = venoshock_on_base_power_move,
    .animation = (u8*)&VenoShockAnimation,
	},

    {
    /*Autotomize*/
    .name = _("Autotomize"),
    .accuracy = 101,
    .description = (pchar*)Autotomize_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_STEEL,
    .m_flags = FLAG_SNATCH,
    .procs = &user_raise_spd_2,
    .on_effect_cb = autotomize_on_effect,
    .animation = (u8*)&AutomizeAnimation,
	},

    {
    /*Rage Powder*/
    .name = _("Rage Powder"),
    .accuracy = 101,
    .description = (pchar*)Rage_Powder_desc,
    .pp = 20,
    .priority = 2,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_POWDER | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = rage_powder_on_effect,
    .animation = (u8*)&RagePowderAnimation,
	},

    {
    /*Telekinesis*/
    .name = _("Telekinesis"),
    .accuracy = 101,
    .description = (pchar*)Telekinesis_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_GRAVITY | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = telekinesis_on_effect,
    .animation = (u8*)&TelekinesisAnimation,
	},

    {
    /*Magic Room*/
    .name = _("Magic Room"),
    .accuracy = 101,
    .description = (pchar*)Magic_Room_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&MagicRoomAnimation,
	},

    {
    /*Smack Down*/
    .name = _("Smack Down"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Smack_Down_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = smackdown_on_effect,
    .on_inv_tryhit_move = smackdown_on_invul_tryhit,
    .animation = (u8*)&SmackDownAnimation,
	},

    {
    /*Storm Throw*/
    .name = _("Storm Throw"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Storm_Throw_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = storm_throw_on_modify_move,
    .animation = (u8*)&StormThrowAnimation,
	},

    {
    /*Flame Burst*/
    .name = _("Flame Burst"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Flame_Burst_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FlameBurstAnimation,
	},

    {
    /*Sludge Wave*/
    .name = _("Sludge Wave"),
    .accuracy = 100,
    .base_power = 95,
    .description = (pchar*)Sludge_Wave_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &poison_10_procs,
    .animation = (u8*)&SludgeWaveAnimation,
	},

    {
    /*Quiver Dance*/
    .name = _("Quiver Dance"),
    .accuracy = 101,
    .description = (pchar*)Quiver_Dance_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_SNATCH | FLAG_DANCE  | FLAG_ONSELF,
    .procs = &raise_user_SpD_SpA_Spd,
    .animation = (u8*)&QuiverDnaceAnimation,
	},

    {
    /*Heavy Slam*/
    .name = _("Heavy Slam"),
    .accuracy = 100,
    .description = (pchar*)Heavy_Slam_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = heavy_slam_on_base_power_move,
    .animation = (u8*)&HeavySlamAnimation,
	},

    {
    /*Synchronoise*/
    .name = _("Synchronoise"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Synchronoise_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .on_tryhit_move = synchonoise_on_tryhit,
    .animation = (u8*)&SynchronoiseAnimation,
	},

    {
    /*Electro Ball*/
    .name = _("Electro Ball"),
    .accuracy = 100,
    .description = (pchar*)Electro_Ball_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_BULLET | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = electro_ball_on_base_power,
    .animation = (u8*)&ElectroBallAnimation,
	},

    {
    /*Soak*/
    .name = _("Soak"),
    .accuracy = 100,
    .description = (pchar*)Soak_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_WATER,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = soak_on_effect,
    .animation = (u8*)&SoakAnimation,
	},

    {
    /*Flame Charge*/
    .name = _("Flame Charge"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Flame_Charge_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_raise_spd_1,
    .animation = (u8*)&FlameChargeAnimation,
	},

    {
    /*Coil*/
    .name = _("Coil"),
    .accuracy = 101,
    .description = (pchar*)Coil_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_Atk_Def_Acc,
    .animation = (u8*)&FlameChargeCoilAnimation,
	},

    {
    /*Low Sweep*/
    .name = _("Low Sweep"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Low_Sweep_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_1,
    .animation = (u8*)&LowSweepAnimation,
	},

    {
    /*Acid Spray*/
    .name = _("Acid Spray"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Acid_Spray_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_BULLET,
    .procs = &target_lower_spDef_2,
    .animation = (u8*)&AcidSprayAnimation,
	},

    {
    /*Foul Play*/
    .name = _("Foul Play"),
    .accuracy = 100,
    .base_power = 95,
    .description = (pchar*)Foul_Play_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_STEAL_OFFENSIVE,
    .procs = &basic_proc,
    .animation = (u8*)&FoulPlayAnimation,
	},

    {
    /*Simple Beam*/
    .name = _("Simple Beam"),
    .accuracy = 100,
    .description = (pchar*)Simple_Beam_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&SimpleBeamAnimation,
	},

    {
    /*Entrainment*/
    .name = _("Entrainment"),
    .accuracy = 100,
    .description = (pchar*)Entrainment_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&EntrainmentAnimation,
	},

    {
    /*After You*/
    .name = _("After You"),
    .accuracy = 101,
    .description = (pchar*)After_You_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = after_you_tryhit,
    .animation = (u8*)&AfterYouAnimation,
	},

    {
    /*Round*/
    .name = _("Round"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Round_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RoundAnimation,
	},

    {
    /*Echoed Voice*/
    .name = _("Echoed Voice"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Echoed_Voice_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = echoed_voice_on_base_power_move,
    .animation = (u8*)&EchoedVoiceAnimation,
	},

    {
    /*Chip Away*/
    .name = _("Chip Away"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Chip_Away_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = chip_away_on_before_move,
    .animation = (u8*)&ChipAwayAnimation,
	},

    {
    /*Clear Smog*/
    .name = _("Clear Smog"),
    .accuracy = 101,
    .base_power = 50,
    .description = (pchar*)Clear_Smog_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = clear_smog_effect,
    .animation = (u8*)&ClearSmogAnimation,
	},

    {
    /*Stored Power*/
    .name = _("Stored Power"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Stored_Power_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = stored_power_on_base_power_move,
    .animation = (u8*)&StoredPowerAnimation,
	},

    {
    /*Quick Guard*/
    .name = _("Quick Guard"),
    .accuracy = 101,
    .description = (pchar*)Quick_Guard_desc,
    .pp = 15,
    .priority = 3,
    .category = MOVE_STATUS,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = quick_guard_on_effect,
    .animation = (u8*)&QuickGuardAnimation,
	},

    {
    /*Scald*/
    .name = _("Scald"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Scald_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_DEFROST | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_30_procs,
    .animation = (u8*)&ScaldAnimation,
	},

    {
    /*Shell Smash*/
    .name = _("Shell Smash"),
    .accuracy = 101,
    .description = (pchar*)Shell_Smash_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &shell_smash_procs,
    .animation = (u8*)&ShellSmashAnimation,
	},

    {
    /*Heal Pulse*/
    .name = _("Heal Pulse"),
    .accuracy = 101,
    .description = (pchar*)Heal_Pulse_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_PULSE | FLAG_HEAL | FLAG_PROTECT | FLAG_REFLECTABLE | FLAG_TARGET,
    .procs = &basic_proc,
	.heal = 50,
    .on_tryhit_move = heal_pulse_on_tryhit_move,
    .animation = (u8*)&HealPulseAnimation,
	},

    {
    /*Hex*/
    .name = _("Hex"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Hex_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = hex_on_base_power_move,
    .animation = (u8*)&HexAnimation,
	},

    {
    /*Sky Drop*/
    .name = _("Sky Drop"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Sky_Drop_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_GRAVITY | FLAG_CHARGE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = skydrop_before_move,
    .on_damage_move = skydrop_on_damage,
    .animation = (u8*)&SkyDropAnimation,
	},

    {
    /*Circle Throw*/
    .name = _("Circle Throw"),
    .accuracy = 90,
    .base_power = 60,
    .description = (pchar*)Circle_Throw_desc,
    .pp = 10,
    .priority = -6,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = dragon_tail_on_effect,
    .animation = (u8*)&CircleThrowAnimation,
	},

    {
    /*Incinerate*/
    .name = _("Incinerate"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Incinerate_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&IncinerateAnimation,
	},

    {
    /*Quash*/
    .name = _("Quash"),
    .accuracy = 100,
    .description = (pchar*)Quash_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = quash_on_tryhit,
    .animation = (u8*)&QuashAnimation,
	},

    {
    /*Acrobatics*/
    .name = _("Acrobatics"),
    .accuracy = 100,
    .base_power = 55,
    .description = (pchar*)Acrobatics_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = acrobatics_on_base_power_move,
    .animation = (u8*)&AcrobaticsAnimation,
	},

    {
    /*Reflect Type*/
    .name = _("Reflect Type"),
    .accuracy = 101,
    .description = (pchar*)Reflect_Type_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = reflect_type_on_effect,
    .animation = (u8*)&ReflectTypeAnimation,
	},

    {
    /*Retaliate*/
    .name = _("Retaliate"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Retaliate_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&RetaliateAnimation,
	},

    {
    /*Final Gambit*/
    .name = _("Final Gambit"),
    .accuracy = 100,
    .description = (pchar*)Final_Gambit_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = final_gambit_on_damage,
    .on_after_move = final_gambit_on_after_move,
    .animation = (u8*)&FinalGambitAnimation,
	},

    {
    /*Bestow*/
    .name = _("Bestow"),
    .accuracy = 101,
    .description = (pchar*)Bestow_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR,
    .procs = &basic_proc,
    .animation = (u8*)&BestowAnimation,
	},

    {
    /*Inferno*/
    .name = _("Inferno"),
    .accuracy = 50,
    .base_power = 100,
    .description = (pchar*)Inferno_desc,
    .pp = 5,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &burn_100_procs,
    .animation = (u8*)&InfernoAnimation,
	},

    {
    /*Volt Switch*/
    .name = _("Volt Switch"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Volt_Switch_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = volt_switch_on_effect,
    .animation = (u8*)&VoltSwitchAnimation,
	},

    {
    /*Struggle Bug*/
    .name = _("Struggle Bug"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Struggle_Bug_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = & target_lower_spAtk_1,
    .animation = (u8*)&StruggleBugAnimation,
	},

    {
    /*Frost Breath*/
    .name = _("Frost Breath"),
    .accuracy = 90,
    .base_power = 60,
    .description = (pchar*)Frost_Breath_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.crit_ratio = 1,
    .animation = (u8*)&FrostBeathAnimation,
	},

    {
    /*Dragon Tail*/
    .name = _("Dragon Tail"),
    .accuracy = 90,
    .base_power = 60,
    .description = (pchar*)Dragon_Tail_desc,
    .pp = 10,
    .priority = -6,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.on_effect_cb = dragon_tail_on_effect,
    .animation = (u8*)&DragonTailAnimation,
	},

    {
    /*Work Up*/
    .name = _("Work Up"),
    .accuracy = 101,
    .description = (pchar*)Work_Up_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &raise_user_SpA_Atk,
    .animation = (u8*)&WorkUpAnimation,
	},

    {
    /*Electroweb*/
    .name = _("Electroweb"),
    .accuracy = 95,
    .base_power = 55,
    .description = (pchar*)Electroweb_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spd_1,
    .animation = (u8*)&ElectrowebAnimation,
	},

    {
    /*Wild Charge*/
    .name = _("Wild Charge"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Wild_Charge_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.recoil = 25,
    .animation = (u8*)&WildChargeAnimation,
	},

    {
    /*Drill Run*/
    .name = _("Drill Run"),
    .accuracy = 95,
    .base_power = 80,
    .description = (pchar*)Drill_Run_desc,
    .pp = 10,
    .crit_ratio = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DrillRunAnimation,
	},

    {
    /*Dual Chop*/
    .name = _("Dual Chop"),
    .accuracy = 90,
    .base_power = 40,
    .description = (pchar*)Dual_Chop_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .multi_hit = {2, 2},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.crit_ratio = 1,
    .animation = (u8*)&DualChopAnimation,
	},

    {
    /*Horn Leech*/
    .name = _("Horn Leech"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Horn_Leech_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_HEAL | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.drain = 25,
    .animation = (u8*)&HornLeechAnimation,
	},

    {
    /*Sacred Sword*/
    .name = _("Sacred Sword"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Sacred_Sword_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = chip_away_on_before_move,
    .animation = (u8*)&SacredSwordAnimation,
	},

    {
    /*Razor Shell*/
    .name = _("Razor Shell"),
    .accuracy = 95,
    .base_power = 75,
    .description = (pchar*)Razor_Shell_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_50_procs,
    .animation = (u8*)&RazorShellAnimation,
	},

    {
    /*Leaf Tornado*/
    .name = _("Leaf Tornado"),
    .accuracy = 90,
    .base_power = 65,
    .description = (pchar*)Leaf_Tornado_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_acc_1_chance_50,
    .animation = (u8*)&LeafTornadoAnimation,
	},

    {
    /*Steamroller*/
    .name = _("Steamroller"),
    .accuracy = 100,
    .base_power = 65,
    .description = (pchar*)Steamroller_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .on_modify_move = stomp_on_modify_move,
    .animation = (u8*)&SteamrollerAnimation,
	},

    {
    /*Cotton Guard*/
    .name = _("Cotton Guard"),
    .accuracy = 101,
    .description = (pchar*)Cotton_Guard_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_SNATCH,
    .procs = &basic_proc,
    .animation = (u8*)&CottonGuardAnimation,
	},

    {
    /*Night Daze*/
    .name = _("Night Daze"),
    .accuracy = 95,
    .base_power = 85,
    .description = (pchar*)Night_Daze_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_acc_40,
    .animation = (u8*)&NightDazeAnimation,
	},

    {
    /*Psystrike*/
    .name = _("Psystrike"),
    .accuracy = 100,
    .base_power = 100,
    .description = (pchar*)Psystrike_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET  | FLAG_CATEGORY_OVERRIDE,
    .procs = &basic_proc,
    .animation = (u8*)&PsystrikeAnimation,
	},

    {
    /*Tail Slap*/
    .name = _("Tail Slap"),
    .accuracy = 85,
    .base_power = 25,
    .description = (pchar*)Tail_Slap_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .multi_hit = {2, 5},
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&TailSlapAnimation,
	},

    {
    /*Hurricane*/
    .name = _("Hurricane"),
    .accuracy = 70,
    .base_power = 110,
    .description = (pchar*)Hurricane_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_FLYING,
    .m_flags = FLAG_PROTECT | FLAG_TARGET | FLAG_MIRROR,
    .procs = &confuse_30_procs,
    .on_modify_move = hurricane_on_modify_move,
    .on_inv_tryhit_move = hurricane_on_tryhit_inv,
    .animation = (u8*)&HurricaneAnimation,
	},

    {
    /*Head Charge*/
    .name = _("Head Charge"),
    .accuracy = 100,
    .base_power = 120,
    .description = (pchar*)Head_Charge_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.recoil = 25,
    .animation = (u8*)&HeadChargeAnimation,
	},

    {
    /*Fiery Dance*/
    .name = _("Fiery Dance"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Fiery_Dance_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_DANCE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &raise_user_SpA_50,
    .animation = (u8*)&FieryDanceAnimation,
	},

    {
    /*Icicle Crash*/
    .name = _("Icicle Crash"),
    .accuracy = 90,
    .base_power = 85,
    .description = (pchar*)Icicle_Crash_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&IcicleCrashAnimation,
	},

    {
    /*Flying Press*/
    .name = _("Flying Press"),
    .accuracy = 95,
    .base_power = 100,
    .description = (pchar*)Flying_Press_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_GRAVITY | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_modify_move = flying_press_on_modify_move,
    .on_base_power_move = flying_press_on_base_power,
    .animation = (u8*)&FlyingPressAnimation,
	},

    {
    /*Belch*/
    .name = _("Belch"),
    .accuracy = 90,
    .base_power = 120,
    .description = (pchar*)Belch_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_POISON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&BlechAnimation,
	},

    {
    /*Rototiller*/
    .name = _("Rototiller"),
    .accuracy = 101,
    .description = (pchar*)Rototiller_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GROUND,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = rototiller_on_effect,
    .animation = (u8*)&RototillerAnimation,
	},

    {
    /*Sticky Web*/
    .name = _("Sticky Web"),
    .accuracy = 101,
    .description = (pchar*)Sticky_Web_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_REFLECTABLE,
    .procs = &basic_proc,
    .animation = (u8*)&StickyWebAnimation,
	},

    {
    /*Fell Stinger*/
    .name = _("Fell Stinger"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*)Fell_Stinger_desc,
    .pp = 25,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_after_move = fell_stinger_after_move,
    .animation = (u8*)&FellStingerAnimation,
	},

    {
    /*Phantom Force*/
    .name = _("Phantom Hit"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Phantom_Force_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GHOST,
    .m_flags = FLAG_CHARGE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = phantom_force_on_before_move,
    .animation = (u8*)&PhantomHitAnimation,
	},

    {
    /*Noble Roar*/
    .name = _("Noble Roar"),
    .accuracy = 100,
    .description = (pchar*)Noble_Roar_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_target_atk_SpA,
    .animation = (u8*)&NobleRoarAnimation,
	},

    {
    /*Ion Deluge*/
    .name = _("Ion Deluge"),
    .accuracy = 101,
    .description = (pchar*)Ion_Deluge_desc,
    .pp = 25,
    .priority = 1,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = ion_deluge_on_effect,
    .animation = (u8*)&IonDelugeAnimation,
	},

    {
    /*Petal Blizzard*/
    .name = _("Petal Storm"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Petal_Blizzard_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PetalBlizzardAnimation,
	},

    {
    /* Freeze Dry */
    .name = _("Freeze-Dry"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Freeze_Dry_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ICE,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FreezeDryAnimation,
	},

    {
    /*Disarming Voice*/
    .name = _("Calming Note"),
    .accuracy = 101,
    .base_power = 40,
    .description = (pchar*)Disarming_Voice_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DisarmingVoiceAnimation,
	},

    {
    /*Parting Shot*/
    .name = _("Parting Shot"),
    .accuracy = 100,
    .description = (pchar*)Parting_Shot_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_SOUND | FLAG_AUTHENTIC | FLAG_REFLECTABLE |FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = parting_shot_on_effect,
    .animation = (u8*)&PartingShotAnimation,
	},

    {
    /* Topsy-Turvy*/
    .name = _("Topsy-Turvy"),
    .accuracy = 101,
    .description = (pchar*)Topsy_Turvy_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_DARK,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = topsy_turvy_on_effect,
    .animation = (u8*)&TopsyTurvyAnimation,
	},

    {
    /* Draining Kiss*/
    .name = _("Draining Kiss"),
    .accuracy = 100,
    .base_power = 50,
    .description = (pchar*) Draining_Kiss_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_HEAL | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
	.drain = 50,
    .animation = (u8*)&DrainingKissAnimation,
	},

    {
    /*Grassy Terrain*/
    .name = _("Floral Earth"),
    .accuracy = 101,
    .description = (pchar*)Grassy_Terrain_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = grassy_terrain_on_effect,
    .animation = (u8*)&GrassyTerrainAnimation,
	},

    {
    /*Misty Terrain*/
    .name = _("Misty Air"),
    .accuracy = 101,
    .description = (pchar*)Misty_Terrain_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = misty_terrain_on_effect,
    .animation = (u8*)&MistyTerrainAnimation,
	},

    {
    /*Play Rough*/
    .name = _("Play Rough"),
    .accuracy = 90,
    .base_power = 90,
    .description = (pchar*)Play_Rough_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_target_atk_10,
    .animation = (u8*)&PlayRoughAnimation,
	},

    {
    /*Fairy Wind*/
    .name = _("Fairy Wind"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Fairy_Wind_desc,
    .pp = 30,
    .category = MOVE_SPECIAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&FairyWindAnimation,
	},

    {
    /*Moonblast*/
    .name = _("Moonblast"),
    .accuracy = 100,
    .base_power = 95,
    .description = (pchar*)Moonblast_desc,
    .pp = 15,
    .category = MOVE_SPECIAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &low_tar_spAtk_30,
    .animation = (u8*)&MoonblastAnimation,
	},

    {
    /*Boomburst*/
    .name = _("Boomburst"),
    .accuracy = 100,
    .base_power = 140,
    .description = (pchar*)Boomburst_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SOUND | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ADJACENT,
    .procs = &basic_proc,
    .animation = (u8*)&BoomburstAnimation,
	},

    {
    /*Fairy Lock*/
    .name = _("Fairy Lock"),
    .accuracy = 101,
    .description = (pchar*)Fairy_Lock_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_HITS_ALL,
    .procs = &basic_proc,
    .on_effect_cb = fairy_lock_on_effect,
    .animation = (u8*)&FairyLockAnimation,
	},

    {
    /* King's sheild */
    .name = _("King‘s Shield"),
    .accuracy = 101,
    .description = (pchar*)Kings_Shield_desc,
    .pp = 10,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_STEEL,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = protect_on_effect,
    .animation = (u8*)&KingsShieldAnimation,
	},

    {
    /*Play Nice*/
    .name = _("Play Nice"),
    .accuracy = 101,
    .description = (pchar*)Play_Nice_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_AUTHENTIC | FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_TARGET,
    .procs = &target_lower_atk_1,
    .animation = (u8*)&PlayNiceAnimation,
	},

    {
    /*Spiky Shield*/
    .name = _("Spiky Shield"),
    .accuracy = 101,
    .description = (pchar*)Spiky_Shield_desc,
    .pp = 10,
    .priority = 4,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_tryhit_move = protection_on_tryhit,
    .on_effect_cb = protect_on_effect,
    .animation = (u8*)&SpikyShieldAnimation,
	},

    {
    /*Aromatic Mist*/
    .name = _("Aromic Mist"),
    .accuracy = 101,
    .description = (pchar*)Aromatic_Mist_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_AUTHENTIC | FLAG_HITS_ALLY,
    .procs = &target_raise_spDef_1,
    .animation = (u8*)&AromaticMistAnimation,
	},

    {
    /*Eerie Impulse*/
    .name = _("Eerie Sense"),
    .accuracy = 100,
    .description = (pchar*)Eerie_Impulse_desc,
    .pp = 15,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_spAtk_2,
    .animation = (u8*)&EerieImpulseAnimation,
	},

    {
    /*Venom Drench*/
    .name = _("Venom Drench"),
    .accuracy = 100,
    .description = (pchar*)Venom_Drench_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &venom_drench,
    .animation = (u8*)&VenomDrenchAnimation,
	},

    {
    /*Powder*/
    .name = _("Powder"),
    .accuracy = 100,
    .description = (pchar*)Powder_desc,
    .pp = 20,
    .priority = 1,
    .category = MOVE_STATUS,
    .type = TYPE_BUG,
    .m_flags = FLAG_POWDER | FLAG_REFLECTABLE | FLAG_AUTHENTIC | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = powder_on_tryhit_move,
    .animation = (u8*)&PowderAnimation,
	},

    {
    /*Magnetic Flux*/
    .name = _("Magna Flux"),
    .accuracy = 101,
    .description = (pchar*)Magnetic_Flux_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_SNATCH | FLAG_AUTHENTIC | FLAG_HITS_MY_SIDE,
    .procs = &raise_user_Def_SpD,
    .on_modify_move = gear_up_on_modify_move,
    .animation = (u8*)&MagneticFluxAnimation,
	},

    {
    /*Electric Terrain*/
    .name = _("Ele Terrain"),
    .accuracy = 101,
    .description = (pchar*)Electric_Terrain_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_ELECTRIC,
    .m_flags =FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = electric_terrain_on_effect,
    .animation = (u8*)&ElectricTerrainAnimation,
	},

    {
    /*Dazzling Gleam*/
    .name = _("Dazzle Gleam"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Dazzling_Gleam_desc,
    .pp = 10,
    .category = MOVE_SPECIAL,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DazzlingGleamAnimation,
	},

    {
    /* Baby-Doll-Eyes */
    .name = _("Puppy Eyes"),
    .accuracy = 100,
    .description = (pchar*)Baby_Doll_Eyes_desc,
    .pp = 30,
    .priority = 1,
    .category = MOVE_STATUS,
    .type = TYPE_FAIRY,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_atk_1,
    .animation = (u8*)&BabyDollEyesAnimation,
	},

    {
    /*Nuzzle*/
    .name = _("Nuzzle"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Nuzzle_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &paralyze_100_procs,
    .animation = (u8*)&NuzzleAnimation,
	},

    {
    /*Hold Back*/
    .name = _("Hold Back"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Hold_Back_desc,
    .pp = 40,
    .category = MOVE_PHYSICAL,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_damage_move = false_swipe_on_damage,
    .animation = (u8*)&HoldBackAnimation,
	},

    {
    /*Infestation*/
    .name = _("Infestation"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Infestation_desc,
    .pp = 20,
    .category = MOVE_SPECIAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = partially_trapped_effect_cb,
    .animation = (u8*)&InfestationAnimation,
	},

    {
    /*Power-up Punch */
    .name = _("Power-Up hit"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Power_Up_Punch_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIGHTING,
    .m_flags = FLAG_PUNCH | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &user_raise_atk_1,
    .animation = (u8*)&PowerUpPunchAnimation,
	},

    {
    /*Shore Up*/
    .name = _("Shore Up"),
    .accuracy = 101,
    .description = (pchar*)Shore_Up_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GROUND,
    .m_flags = FLAG_SNATCH | FLAG_HEAL | FLAG_ONSELF,
    .procs = &basic_proc,
    .heal = 50,
    .on_modify_move = shore_up_on_modify_move,
    .animation = (u8*)&ShoreUpAnimation,
	},

    {
    /*High Horsepower*/
    .name = _("High Horsepower"),
    .accuracy = 95,
    .base_power = 95,
    .description = (pchar*)High_Horsepower_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&HighHorsePowerAnimation,
	},

    {
    /*Strength Sap*/
    .name = _("Strength Sap"),
    .accuracy = 100,
    .description = (pchar*)Strength_Sap_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_GRASS,
    .m_flags = FLAG_HEAL | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET | FLAG_REFLECTABLE,
    .procs = &target_lower_atk_1,
    .on_effect_cb = strength_sap_on_effect,
    .animation = (u8*)&StrengthSapAnimation,
	},

    {
    /*Spotlight*/
    .name = _("Spotlight"),
    .accuracy = 101,
    .description = (pchar*)Spotlight_desc,
    .pp = 15,
    .priority = 3,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = rage_powder_on_effect,
    .animation = (u8*)&SpotlightAnimation,
	},

    {
    /*Toxic Thread*/
    .name = _("Toxic Thread"),
    .accuracy = 100,
    .description = (pchar*)Toxic_Thread_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_POISON,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &toxic_thread,
    .animation = (u8*)&ToxicThreadAnimation,
	},

    {
    /*Laser Focus*/
    .name = _("Laser Focus"),
    .accuracy = 101,
    .description = (pchar*)Laser_Focus_desc,
    .pp = 30,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_SNATCH | FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = laser_focus_on_effect,
    .animation = (u8*)&LaserFocusAnimation,
	},

    {
    /*Throat Chop*/
    .name = _("Throat Chop"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Throat_Chop_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_move = throat_chop_on_before_move,
    .on_effect_cb = throat_chop_on_effect_cb,
    .animation = (u8*)&ThroatChopAnimation,
	},

    {
    /*Anchor Shot*/
    .name = _("Anchor Shot"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Anchor_Shot_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_STEEL,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_effect_cb = block_on_effect,
    .animation = (u8*)&AnchorShotAnimation,
	},

    {
    /*Psychic Terrain*/
    .name = _("Psy Terrain"),
    .accuracy = 101,
    .description = (pchar*)Psychic_Terrain_desc,
    .pp = 10,
    .category = MOVE_STATUS,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_ONSELF,
    .procs = &basic_proc,
    .on_effect_cb = psychic_terrain_on_effect,
    .animation = (u8*)&PsychicTerrainAnimation,
	},

    {
    /*Lunge*/
    .name = _("Lunge"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Lunge_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_BUG,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_atk_1,
    .animation = (u8*)&LungeAnimation,
	},

    {
    /*Power Trip*/
    .name = _("Power Trip"),
    .accuracy = 100,
    .base_power = 20,
    .description = (pchar*)Power_Trip_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = stored_power_on_base_power_move,
    .animation = (u8*)&PowerTripAnimation,
	},

    {
    /*Burn Up*/
    .name = _("Burn Up"),
    .accuracy = 100,
    .base_power = 130,
    .description = (pchar*)Burn_Up_desc,
    .pp = 5,
    .category = MOVE_SPECIAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_DEFROST | FLAG_PROTECT | FLAG_MIRROR | FLAG_TARGET,
    .procs = &basic_proc,
    .on_tryhit_move = burn_up_on_tryhit,
    .on_effect_cb = burn_up_on_effect,

    .animation = (u8*)&BurnUpAnimation,
	},

    {
    /*Trop Kick*/
    .name = _("Trop Kick"),
    .accuracy = 100,
    .base_power = 70,
    .description = (pchar*)Trop_Kick_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GRASS,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_atk_1,
    .animation = (u8*)&TropKickAnimation,
	},

    {
    /*Dragon Hammer*/
    .name = _("Draco Hammer"),
    .accuracy = 100,
    .base_power = 90,
    .description = (pchar*)Dragon_Hammer_desc,
    .pp = 15,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DRAGON,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&DragonHammerAnimation,
	},

    {
    /*Brutal Swing*/
    .name = _("Brutal Swing"),
    .accuracy = 100,
    .base_power = 60,
    .description = (pchar*)Brutal_Swing_desc,
    .pp = 20,
    .category = MOVE_PHYSICAL,
    .type = TYPE_DARK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_HITS_ALL,
    .procs = &basic_proc,
    .animation = (u8*)&BrutalSwingAnimation,
	},

    {
    /*Shell Trap*/
    .name = _("Shell Trap"),
    .accuracy = 100,
    .base_power = 150,
    .description = (pchar*)Shell_Trap_desc,
    .pp = 5,
    .priority = -3,
    .category = MOVE_PHYSICAL,
    .type = TYPE_FIRE,
    .m_flags = FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .before_turn = shell_trap_before_turn,
    .animation = (u8*)&ShellTrapAnimation,
	},

    {
    /*Psychic Fangs*/
    .name = _("Psychic Fang"),
    .accuracy = 100,
    .base_power = 85,
    .description = (pchar*)Psychic_Fangs_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_PSYCHIC,
    .m_flags = FLAG_BITE | FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&PsychicFangsAnimation,
	},

    {
    /*Stomping Tantrum*/
    .name = _("Tantrum Rage"),
    .accuracy = 100,
    .base_power = 75,
    .description = (pchar*)Stomping_Tantrum_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_GROUND,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .on_base_power_move = stomping_tantrum_on_base_power_move,
    .animation = (u8*)&StompingTantrumAnimation,
	},

    {
    /*Accelerock*/
    .name = _("Accelerock"),
    .accuracy = 100,
    .base_power = 40,
    .description = (pchar*)Accelerock_desc,
    .pp = 20,
    .priority = 1,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ROCK,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .animation = (u8*)&AccelerockAnimation,
	},

    {
    /*Liquidation*/
    .name = _("Liquidation"),
    .accuracy = 100,
    .base_power = 85,
    .description = (pchar*)Liquidation_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_WATER,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &target_lower_def_20_procs,
    .animation = (u8*)&LiquidationAnimation,
	},

    {
    /*Tearful Look*/
    .name = _("Tearful Look"),
    .accuracy = 101,
    .description = (pchar*)Tearful_Look_desc,
    .pp = 20,
    .category = MOVE_STATUS,
    .type = TYPE_NORMAL,
    .m_flags = FLAG_REFLECTABLE | FLAG_MIRROR | FLAG_TARGET,
    .procs = &low_target_atk_SpA,
    .animation = (u8*)&TearfulLookAnimation,
	},

    {
    /*Zing Zap*/
    .name = _("Zing Zap"),
    .accuracy = 100,
    .base_power = 80,
    .description = (pchar*)Zing_Zap_desc,
    .pp = 10,
    .category = MOVE_PHYSICAL,
    .type = TYPE_ELECTRIC,
    .m_flags = FLAG_CONTACT | FLAG_MIRROR | FLAG_PROTECT | FLAG_TARGET,
    .procs = &basic_proc,
    .flinch_chance = 30,
    .animation = (u8*)&ZingZapAnimation,
	},
};
