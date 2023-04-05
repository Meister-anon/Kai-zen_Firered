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

/*
* note from CompuMax in pret   fire red debug system not removed actually takese up ewram so going through removal process saves space.
* 
* Make the following change to include/config.h To get some space in the EWRAM and IWRAM
// #define NDEBUG
To
#define NDEBUG

And in common_syms/main.txt remove the following lines:
sVcountAfterSound
sVcountAtIntr
sVcountBeforeSound
 
Meister_anon — Today at 6:22 PM
thank you very much,  what does the com_sym stuff do? so I know what I'm doing.
CompuMax — Today at 6:24 PM
The first change is defining that it does not include the DEBUG used during the development and testing of the game. Since they forgot to remove it before publishing the ROM. 
And the second change removes the references in IWRAM from references used in the DEBUG
Meister_anon — Today at 6:25 PM
ok so its all part of the same removal?  for taking out the debug stuff?
CompuMax — Today at 6:26 PM
Exactly
* 
* [tested in pret and works so adapting for main repo, worked for expanding species name]
* Explanation for why it works
* 
* 
* did you inspect how much space you needed in iwram before moving stuff to ewram?
CompuMax — 06/03/2021 10:23 AM
No, but now that you mention it, it could be the IWRAM that is generating the problem for me.
I am still installing the mixer in pokeemerald to rule out that the tutorial has overlooked something
PikalaxALT — 06/03/2021 10:24 AM,<<<
one thing you can do is set config.h to define NDEBUG
that'd give you back 0xB4 bytes in IWRAM
CompuMax — 06/03/2021 10:33 AM
Oh! Thanks! I will do it
Although I imagine that I am exceeding the IWRAM when compiling, it should show an error, right?
PikalaxALT — 06/03/2021 10:35 AM<<<<
it'll also give you back something like 0x754 bytes in EWRAM, which is huge



Notes on health box
I'm wondering why its using TextIntoHealthboxObject twice
CompuMax — Today at 8:33 PM
@Meister_anon Because the Healthboxes are too big, they are divided into 2 OBJs of 64x64
What the first TextIntoHealthBox does is copy the first 6 tiles that make up the nickname to the first OBJ
Then depending if you are in a double battle or not, determine where to copy the remaining 7 tiles into the next OBJ


Meister_anon — Today at 12:46 PM
ok I see it now, I luckily came close to the right solution,  32 x 4bpp is the same thing as I had before 0x400 etc.
and is still half of the playersidee values so the relation is the same.

but since the player first textintoHealth function ended in 6
the 2nd function needs the value 6 * TILE_SIZE_4BPP

and since the enemy side ends in 7  that's why I need 7 * TILE_SIZE_4BPP
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
* 
* anthroyd advice need to start keeping list of things I plan to use for the thread and what I plan
* to introduce explicitly in-game I want my new type chart to mostly be discoveredd in game,
* but just have them aware that things are diffeerent and some things will be a new experiencee
* 
* need double check trap effects, make sure effect_trap setup
* works correctly for thunder_cage since I didn't even know
* that was part of the effect -
* progress -checked since it uses effect_trap battle script is already setting wrap effect
* still checking statu1 to see if need it for allowing traps to persist after switch
* it seems ugly, think just need to make a grip glaw exclusion -
*/
goto CLEARDATA_ON_FAINT //if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
goto CLEARDATA_ON_SWITCH    //search, for status2_wrapped & wrappedby  implement new trap checks where it makes 
goto OTHER_SWITCH_EFFECTS_1 //goes to jumpifcantswitch bs command, need to update with trap effects
/*
* all traps used statuswrap before and wrapped by, need to make new struct value trappedby
* and have it set for other trap statuses or make wrapped by set with other statuses too
* each one has its own timer, so it doesn't matter if I dont check  each individual status set/applied at the time
just need make wrapppedby work with new trap statuses adn then set that if holding grip claw staus doesn't get cleared on switch
as well as the effect of increasing trap duration
*/


/* 
* Finish Ability_Defeatist setup need to finish setting up
* the cleanse effect, actually can just do what runnaway does
* then that would just leave trap effects to remove then do hp drop
* realize I can bypass that by using emergency exit effect, as that gaurantees switch/does force switch
* for simplicity sake will skip the hp drop I was planning to do if statused with traps or escape prevention
* -escape prevention done need to setup guaranteed switch ALLOWANCE DONE and need add to switch in effects 
* -Setup Done need test but DONE for now
* 
* buff in a pinch abilities, activate soon as hp hits yellow i.e 50% - DONE
* 
* General repo update compare to griff red modern fire red search #ifdef BUGFIX
* and replace bad code with bugfixes don't know if it'll make a differnce or not though - DONE ?
* 
* Update pokedex_screen.c and other pokedex files with new function renames -
* 
* Re-capitalize ability names, decapitalization doesn't look good in fire red menus - DONE
* 
* Buffed static & flame body to apply on hit and when attacking. DONE
* 
* Need setup mon with static w new in a pinch ability overcharge -
* 
* Further buff cupid arrow for luvdisc make it ignore gender check, as its the love pokemon and something further to make it more unique. DONE
* 
* BUFFED unown, learnset and new ability
* 
* nother wave of buffs, delcatty buff, will need change its pokedex entry to fit, made part ghost, cats have 9 lives
* may say delcatty is cat that died and came back intending to live its life to the fullest of its desire.
* 
* may consider buff plus/minus ability with same affect as overcharge, but only when the partner is in a pinch -
* can lead to an interesting plan where players ev build them for bulk
* 
* NEED double check trap logic, may not need to make them status 1, to keep from being reset when mon switches
* occured to me its not a status1 thing becuse confusion persists if mon switches, so its prob just somehting in trap logic?-
* 
* for wormadam line, buff anticipation ability with disguise effects,
* it warns of a super effective or ohko move, and gets a chance once a battle to dodge one super effective move
* allows for a chance to stay in rather than having to switch because you know a move is coming.
* is part of switch in effects i'm trying to make reactive, so if you don't take a super-effective hit and beat enemy, move should check again
* 
* gDisableStructs[battler].isFirstTurn == 2  is logic for mon switchig in, can use for switchin reactivation condition
* 
* fix delibird learnset oh already done
* Give crabominable a better front sprite, its just ugly -
* 
* make cursola signature ability PERISH_BODY only activate for enemy mon
* watching JPR Poketrainer showed me how niche/bad it is, especially whene mon already has such low def stat
* even without perish song on it if it gets hit by a physical move its not sticking around long
* 
* GIVE Turtonator more stab moves? or more early moves
* 
* make revisions to add grass moves to sudowoodo line lvl up and tm learnsets   thinkin ingrain & bullet seed
* think want to also add beatup if it doesn't have already
* 
* GIVE shiinotic creepier more cursed front sprite -
* and change type to grass ghost but give ability nymph spirit to give it triple stab, boosts fairy type moves think 
* will roll in illuminate effect as replacement, nymphs usually draw in forest creatures so it would work. -This part is done
* 
* Need add more ghost moves to its learnset  also dryads curse
* 
* Finish setup for move Dryads Curse  
* animation idea, ingrain roots and wrap/bind constrict anim but with a black or darker color?
* 
* Setting up flash freeze to just use sheer cold animation for now- will prbo keep DONE
* 
* Further adjust freeze status effect, plan setup current gen frotstbite for after target defrosts
* double check that I've already made freeze consistent and work like confusion/traps to last 2-5 turns
* long as target defrosts normally i.e not via thaw or ice cure/status cure effect target will remain with status1_frostbite
* would need to make sure it keeps the status1 freeze icon, so will need to change defrosting
* to not just remove frozen but set frostbite, OR just not remove freeeze so you keep the turn damage & icon
* 
* check freeze implementation, if used a timer can set it so it plays defrost text turn timer hits 0,
* [woudl need to check last used move and last hit by move, to check if timer reached zero as a result of
* the thaw effect or not.]
* and then display a different string for end turn if defrosted rather than thawed, would be hurt by frostbite
* only remove status icon  if thawed, or ice cured or status cured w items
* 
* check shed skin ability, after changing define values to fit new straps, the bitwise may go wonky?
* another reason to remove new status 1 traps for grip claw & implement with conditional logic instead
* 
* 
* Make copy ability of tinted lens, for non bugs, call it protag powere or subversion or great expectations  tiger cub?
* anyway for mon that can setup  multiple type power/dmg buffs i.e terrain & weather or to be used with a terrain on on team.
* 
* Remember setup ability Dark Deal companion ability to nuisance
*
*
* Also comb over stats again, to attempt to address power creep?
* not sure if it would matter, higher is still higher even if I bring things closer
* on the offensive side i.e atk sp atk speed  and my ev cap increase is technically already made to address this
* 
*
* Look at changes to early gen mon, consider bringing back stats from gen 1 & 2
* where special atk & sp def were all one stat  see how it changes mon
* and if it makes sense for balance
* 
* Also consider tweaking how terrain switch works, make it stay as long as the ability surge mon is on the field
* want to work like  weather switch which I think works off last in?  may work off speed?
* make conditional where its supposed to decrement if they're on field timer equals "permanet" i.e timer = 5, if not on field decrement timer
* that way even if they get one shot its still valuable to put out as a setup.-
* 
* Go over field control effects again, i.e traps status terrain weather  drain abilities make sure everything remains in balance
* I don't want to turn things into a gimmick where the only thing ppl do is status or terrain I want them to be relatively equal options
* -
* 
*  add and change for regi effects, instead of player needing to know brail, setup archologist npc, maybe in pewter town museum.
* that will "translate" the text for you to read.   so when you initially find read it, a special flag will be set.
* in the museum npc he'll chech for those flags from lowest to highest, and read the first he finds each time you talk to him.
* have him be shocked excited then say let me translate  ... fades to black and returns
* Ah I see, the text means (maybe highlight translation) "blah blah blah" clears the first set flag and then sets another
* that'll change what happens when you click the wall, now that you know what it says, a box will come up asking if yuo want to do the thing
* i.e "use cut on wall?" yes/no  then check party for a mon that can and do it if possible, or return no one is able to use cut.
* 
* 
* Emerald expansion dropped new icons for legends arceus need update and add
* planning space time events for palkia dialga, so for post game
* can use that as setup for hisuian mon appearing on the map.
* scientist is studying  time distortion then space distorition with his tech/device
* after both events are complete as thanks he'll give you a new version of his
* device hes working on.
* 
* Can have it as a filter add on to the pokenav/dexnav
* it'll be a filter to select, search for warped time/space
* a bush will shake and it'll spawn from the hisuian mon table
* that can spawn on that map.
* Believe will require converting encounter table from a json 
* to .c & .h file to use functions and arrays
* to decide what table to pull from.
* 
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
goto PARTYMENU_GRAPHICS
/* Found species names were being slightly truncated in some cases, comb through added mon ppost gen 3
* all names fit current POKEMON_NAME_LENGTH  limit of 10 + 1, but some are shrunken to fit, 
* so edited party graphics box & was able to add 1 additional space no more.  need to increase name length by 1 to match
* 
* still has issue finding in battle values to adjust, need to move over gender icon
* found it ,its all in UpdateNickInHealthbox  -increased name length need to expand window width and adjust other parameters that 
* take mon name  i.e summary screen, & naming screen - playere health box works enemy can't figure out yet  
* - progress - fixed enemy health bar neeed to setup for the other places and test rest of party slots-
* 
* 
* also my need to re-capitalize species namees as well. it prob looks fine in emerald but for fire red looks a bit off
* espcially on some of the wider characters like M  -DONE  (unless I decide to go in and redo the font to look better myself that's it)
* 
*/ 


goto HEALTHBOX_LOGIC	//health box for battle, enemy values at bottom of function, need add exp bar/values to that section.
goto EVOLUTION_LOGIC
/*  want battle evolution for player and opponenet for enemy need to work out how to give them exp.
* after they have exp need set function to make it feel real that they would level up i.e they aren't starting from 0.
* for that make random function that would get their needed exp to level and then random divide that by either 2, 3, or 4 to increase their chance of lvl in battle.
* player can use this and the above function to evolve, but enemy needs a specific one, that won't take out of battle, make it so if they can evolve they will. 
* use CFRU mega evolve animation for opponent. -
* 
* For getting mon to level up at least visually use healthbox function.  to make random level up
* decided use variation of exp function but insteead of using exp basd on their actual level generate a lower level.
* so thy need far less exp than a full level to make it seem like they're almost leveled up.
* (prob need to make exp bar linked to value returned by level function)
* to make a false level I'll make a function that'll return a random value between 5 and I think half their actual level.
* Random () % ((mon level/2) +5)    witha min exp for level 5, defeating practically anything in the game would be enough to level up.
* [thought normaly this effect would go away could attempt to find someway to store and make permanent? do the whole reverse rogue light thing?
* [enemy gets stronger...prob best to have it reset and not be permamnent...unless I want to make a fuck you hard mode]
*
* level = GetMonData(mon, MON_DATA_LEVEL);
            exp = GetMonData(mon, MON_DATA_EXP);
            currLevelExp = gExperienceTables[gBaseStats[species].growthRate][level];
            currExpBarValue = exp - currLevelExp;
            maxExpBarValue = gExperienceTables[gBaseStats[species].growthRate][level + 1] - currLevelExp;
* 
* 
* Check if time works, add clocks to fire red setup hourly
* daily, weekly, Monthly time based events.
* Periodic overworld Weather conditions
* map based terrain and seasons as well
* Treat entire map like a globe, with different climates so differeent areas experience different weather baseed on season
* Then have different encounters based on season, mon migration if a climate shifts cold they move to a hotter area vice versa
* -Progress-
* 
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

goto ABILITYBATTLE_FUNCTION	//	battle_util.c function other more complex ability activation logic
/*
* Setting up new effeets for absorb abilities
* make all work like lightnight rod and change targetting to draw in moves
* counter balance is only does that if ability mon isn't statused 
* 
* New signature ability for suicune
* purifying aura, similar effect to healer, also mon removes all status1 effects on itself & allies at the end of turn
* shed skin but not random  in doubles heals status of ally on switchin as well.   replace pressure think can use plus minus ability effect
* nvm plus/minus use field sport effect which is both sides of field I just want that prat to effect your side so partner on switch in
* plan to make on all status exlcuuding traps, to make it a great team mon for abrorbing mon or intimidate mon who's abilities get canceled
* with status 
* 
* tweak idea, to make bit less overpowered, will just do status1, leaving confusion and infatuation as viable options
* rather than not having an out/counter - DONE  *need test though
* 
*/

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
//	                and needed pokedex logic for double wilds check case 5

goto ENCOUNTER_COUNT_DATA
//data for encounter count i.e number of spaces for land/surf mon defines etc.


#endif //GUARD_GRAND_TO_DOLIST_H