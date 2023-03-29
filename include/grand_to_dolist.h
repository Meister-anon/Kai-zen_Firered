#ifndef GUARD_GRAND_TO_DOLIST_H
#define GUARD_GRAND_TO_DOLIST_H

/*this file is to be an itemized list of things I plan to do/my progress.
with the intention of cleaning up my files, so I dont have comments everywhere
and to help ensure I don't lose track of things

Procedure--
include a file I am working in with line stamps		*as you can use includes to navigate to said file*
and a brief description of what my goal is there
each thing should be checked off when done
//OK REALIZED I can use goto's with variabls as a shortcut parts of to .c files

*/

//TODO:
/*Add logic for when flying types are grounded they take neutral damage from fighting types
* Look at how emerald handeled smack down and roost logic for ground type dmg -
* 
* Setup moves with flag 2x dmg on air to remove on air status and ground target when they hit flying target
* -done
* 
* realized logic for damage on air targets was incomplete 
* correcting setup -
* 
* need double check trap effects, make sure effect_trap setup
* works correctly for thunder_cage since I didn't even know
* that was part of the effect- 
* 
* Finish Ability_Defeatist setup need to finish setting up
* the cleanse effect, actually can just do what runnaway does
* then that would just leave trap effects to remove then do hp drop
* realize I can bypass that by using emergency exit effect, as that gaurantees switch/does force switch
* for simplicity sake will skip the hp drop I was planning to do if statused with traps or escape prevention
* -escape prevention done need to setup guaranteed switch ALLOWANCE DONE and need add to switch in effects 
* -Setup Done need test but DONE for now
* 
* General repo update compare to griff red modern fire red search #ifdef BUGFIX
* and replace bad code with bugfixes don't know if it'll make a differnce or not though
* 
* Re-capitalize ability names, decapitalization doesn't look good in fire red menus - DONE
*/ 
goto CATCHING_LOGIC
/*
* Need to adjust ball multiplier logic for catch.
* Add more pokeballs, add more status effect multipliers to augment catch odds.
* and NEED to change the current status augment odds so they'r additive instead of multiplicative.
* Current effect would be FAR too strong. 
* I'm using IFs so they would all be inclusive
* just need to chanege from *= to an +=  I believe odds = (odds * 15) / 10;
* would become odds += ((odds * 15) / 10);
* As the way it works is takes whatever value is on the right,  and applies
* the operator to value on the left...actuallyy nvm that would actually be larger than if it was multiplicative
* my mental math was wrong, leave the function as it is, just add more status 2 & trap effects
* 
* Set wild double battles, and allow catching both mon
* cleanest way is to store both mons data for the pokedex beforehand
* and clear whoever dies.
* Then at end of battle do pokedex entries for both, make it loop
* just like other functions do, so have create function buffer mon
* to value or var used for speciees data zero out value if mon dies
* then have pokedex loop through functions baseed on var/value if they aren't 0
* -Progress-
*/

goto EVOLUTION_LOGIC
/*  want battle evolution for player and opponenet for enemy need to work out how to give them exp.
* after they have exp need set function to make it feel real that they would level up i.e they aren't starting from 0.
* for that make random function that would get their needed exp to level and then random divide that by either 2, 3, or 4 to increase their chance of lvl in battle.
* player can use this and the above function to evolve, but enemy needs a specific one, that won't take out of battle, make it so if they can evolve they will. 
* use CFRU mega evolve animation for opponent. -
* 
* Check if time works, add clocks to fire red setup hourly
* daily, weekly, Monthly time based events.
* Periodic overworld Weather conditions
* map based terrain and seasons as well
* Treat entire map like a globe, with different climates so differeent areas experience different weather baseed on season
* Then have different encounters based on season, mon migration if a climate shifts cold they move to a hotter area vice versa
* -Progress-
* 
*/
goto TRAINER_MEMO_SUMMARY	//pokemon_summary_screen.c, scroll down for trainer memo functions

goto MOVEICON_ABILITYDESC	//function for displaying move icons & ability info in summ screen
/* 
* Upgrade UI menu for new mechanics. Expanded move description & ability description & move name fields
* Adjusted summary screen menu for trainer memo, &\ move summary/info page.
* Need to find a fix for move icons misalignment in moves pags
* 
* Also add new string/logic for trainer memo box, for nuzlocke idea
* Where pokemon would die and be replaced by ashes when taken to pokemon center
* Which can be placed at pokemon tower in lavender town after plot point 
* for a chance to resurect your pokemon based on friendship -needs open slot to work
* Otherwise it'll serve as a record of your lost mon.
* if viewing dead mon in tower bring up the summary screen for them
* Pokemon ashes should store all mon data, as if it was the mon itself.
* with 3rd line of trainer memo, displaying where they died,
* i.e "Lost in *location* at *lvl* to *cause of death-either mon to kill it, or status that killed it.
* to severe burns, hypothermia, poison  burn poison & freezee/frostbite are status1s that do dot and can kill
* if left uncured/healed for a number of steps after mon dies to or with them.
*/

/* 
* 
* 
*/


goto STAT_AND_DAMAGE_ABILITIES_ETC // pokemon.c function for ability and item effects that affect damage calc


goto PRIORITY_EFFECTS	//battle_main.c all effects regarding priority changes go here.
//working on setting up an effect for rock toss and the other effects that do double damage to on air targets
//increased priority is done, still need to set atk canceler portion in battle_script_commands.c
//to cancel fly
//and set  grounded / smack down status if hit while in the air status.
//hmm ok just found there's a bs for that, various gravity on in air targets from emerald
//so guess I'll edit that

//ok checkd bs_scripts.inc the various command translates to bringdownairbornebattler
//the command doesn't have any logic secific to gravity instead its associated because
//its only placed  in the gravity battle script  so for effect I want  think
//I just need to make a new various bs command with the specific logic I want and place it in 
//the effect_hit command after damage calc to ensure the thing didn't miss.

goto VARIOUS_BS_COMMANDS	//long function for easily setting up new bs commands. and not need a new function
//macro is made in battle_script.inc

goto GROUNDED_GHOSTMON //battle_util.c grounded logic, also right below floating mon list
/*
* Relevant Notes:
* Raised Pokémon are not affected by Ground type moves, Spikes, Toxic Spikes nor Arena Trap.
* Pokémon no longer stay raised (and cannot become raised) if Gravity or Ingrain is in effect, 
* the move Smack Down is used against them, or Iron Ball is held.
* 
* Its a status 3 so smackdown would be removed on switch 
* I think I want to also make it removed by fly and possibly several other flying moves
* as well as using telekinesis again.
*/

goto RUN_LOGIC_PT1 //battle_main.c 1st area that deals with running logic

goto RUN_LOGIC_PT2 //last part for setting up run based effects battle_main.c

goto TURN_ACTIONS_SWITCH_ETC // battle_main.c  HandleTurnActionSelectionState function deaels with logic  for turn actions i.e switching catching using moves etc.

goto EXP_FUNCTION //battle_script_commands.c has exp & level up logic, can be used as example for mid battle evo 
				//	and needed pokedex logic for double wilds check case 5
#endif //GUARD_GRAND_TO_DOLIST_H