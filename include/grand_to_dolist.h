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
 
Meister_anon � Today at 6:22 PM
thank you very much,  what does the com_sym stuff do? so I know what I'm doing.
CompuMax � Today at 6:24 PM
The first change is defining that it does not include the DEBUG used during the development and testing of the game. Since they forgot to remove it before publishing the ROM. 
And the second change removes the references in IWRAM from references used in the DEBUG
Meister_anon � Today at 6:25 PM
ok so its all part of the same removal?  for taking out the debug stuff?
CompuMax � Today at 6:26 PM
Exactly
* 
* [tested in pret and works so adapting for main repo, worked for expanding species name]
* Explanation for why it works
* 
* 
* did you inspect how much space you needed in iwram before moving stuff to ewram?
CompuMax � 06/03/2021 10:23 AM
No, but now that you mention it, it could be the IWRAM that is generating the problem for me.
I am still installing the mixer in pokeemerald to rule out that the tutorial has overlooked something
PikalaxALT � 06/03/2021 10:24 AM,<<<
one thing you can do is set config.h to define NDEBUG
that'd give you back 0xB4 bytes in IWRAM
CompuMax � 06/03/2021 10:33 AM
Oh! Thanks! I will do it
Although I imagine that I am exceeding the IWRAM when compiling, it should show an error, right?
PikalaxALT � 06/03/2021 10:35 AM<<<<
it'll also give you back something like 0x754 bytes in EWRAM, which is huge



Notes on health box
I'm wondering why its using TextIntoHealthboxObject twice
CompuMax � Today at 8:33 PM
@Meister_anon Because the Healthboxes are too big, they are divided into 2 OBJs of 64x64
What the first TextIntoHealthBox does is copy the first 6 tiles that make up the nickname to the first OBJ
Then depending if you are in a double battle or not, determine where to copy the remaining 7 tiles into the next OBJ


Meister_anon � Today at 12:46 PM
ok I see it now, I luckily came close to the right solution,  32 x 4bpp is the same thing as I had before 0x400 etc.
and is still half of the playersidee values so the relation is the same.

but since the player first textintoHealth function ended in 6
the 2nd function needs the value 6 * TILE_SIZE_4BPP

and since the enemy side ends in 7  that's why I need 7 * TILE_SIZE_4BPP


Palachu � Today at 4:06 AM
Fun fact: the new character limit for Pokemon as of Gen. 6 is actually 12 (Crabominable and since Gen. 9 also Squawkabilly)

*/

//I've decided I'm not making 2 things rather than a rom base at emerald expansion standard, and my own game with all the features I like
//I'm making one project Kai-zen Red  will be everything I want, my vision for what pokemon should be.
//It will have everything, and be THE rom base for fire red projects going forward!! -4/18/2023  11:12am  MEISTER!!


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
* played OPAL effing amazing, incorporate the great qol stuff frome there, flame charge buff to raise speed,
* try to get meowth forms, setup exp share with icon on summary screen.
* plus item use text on summary, to take to bag menu/medicine  bag select how many to use from there
* make stat boosting faster, also copy some of their item cost changes.
* low cost of ev boost items.  1k or 2k per rebalance other things I like that cost economy balance
* get incubator so can hatch eggs easily while on the go, would greatly speed up breeding as well
* include flame body/fire ability in party boosts speed of all  
* rename mon and relearn moves from a npc/attendant in every pokemon center -
* 
* ok remembered I also wanted to setup move learn better, a lot of time you see a move 
* and it looks cool but you don't remember your mons stats, so you can't make a full informed decision
* so change the move learn screen where you can move left and right to slide out
* and it'll slide you to the main summary page that shows your mon info/ i.e stats & ability data etc.
* (believe need to add this in normal summary screen and evolution file?
* same as how had setup movelearn confirmation text)
* 
* ok for starter fight, add oak text in menu for when you level up and learn your first move,
* telling the player about the menu change.
* 
* hmm could possibly do with a flag check? first move learn flag, 
* on summary screen state of move learn if flag isn't already set,
* run the oak script just like when in battle for first time
* "OAK:What's this?!\n  {pokemon name} is learning a new move?\pSpectacular! Now if at any time during move selection\n
* "you want some help making with your decision. \pPress Left on the d-pad to see your stat info/data.\nAnd simple press Right to return here."
* and then set the flag
* 
* done that way it'll always get seen, regardless of if you win the rival fight or for some reason don't level your starter first
* check battle_controller_oak for text
* 
* or can just have a scripp to run, similar to how oak works in overworld
* so soon as your starter is leveling up and learning a move for the first time.
* oak text would pop up to inform you of the menu/dialogue changes
* 
* 
* need to update name length to 12 base, so will need to move health bar
* 
* make early event script to set all mon as caught seen
* loop through species and set all flags, and unlock national dex
* may also give a few mon with script, this is to check pokedex entries fit
* 
*  THOUGHT attempt change item use, allow for using multiple of the same item at once.
* from outside of battle. i.e use 5 oran berries,  to equal 1 super potion.
* the item use image would play 1 time, but it would apply the effects of the item 
* all at once. check how it works, if it shows exact hp recorvered or just displays text for hp recovered.
* would only be for hp recovery level up, stat items, and pp ups.
* 
* pick item, add quanity argument do it like in mart buying an item,
* hopefully can shift total quantity as you move amount you plan to use. may not need to/have any benefit in doing it that way
* other than preference.
* after confirm to use that quantity, only then go to party menu.
* think just loop through portion that actually uses item n number of times, where n is quantity - 1
* i.e if you use 3 rare candies will use item and then loop 2 times
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
* Update pokedex_screen.c and other pokedex files with new function renames - DONE
* 
* NEED upgrade pokedex entry graphic so can fit emerald style longer dex entries. - DONE
* 
* Re-capitalize ability names, decapitalization doesn't look good in fire red menus - DONE
* 
* Buffed static & flame body to apply on hit and when attacking. DONE
* 
* Need setup mon with static w new in a pinch ability overcharge -
* 
* Further buff cupid arrow for luvdisc make it ignore gender check, as its the love pokemon and something further to make it more unique. DONE
* 
* BUFFED unown, learnset and new ability - DONE
* 
* nother wave of buffs, delcatty buff, will need change its pokedex entry to fit, made part ghost, cats have 9 lives
* may say delcatty is cat that died and came back intending to live its life to the fullest of its desire. - DONE
* 
* may consider buff plus/minus ability with same affect as overcharge, but only when the partner is in a pinch -
* can lead to an interesting plan where players ev build them for bulk
* yeah that works as the ability activates when a mon with plus/minus is on the field, but 
* if I make that action only be for if using the opposite ability as your partner its a different synergy
* 
* companion ability to nuisance, cuts dynamicbasepower of partner moves in half,
* in exchange for serene grace style heightned effect chance INCLUDING heighteeend crit chance/odds.
* possibly done by dirrectly moding critchance, or by setting high crit flag to moves if possible
* the point of high crit is, it'd give a chance to overcome the negative, crit would double damage
* so you do normal move damage. plan to use in doubles with nuisance, lets them use stronger moves
* kind of a opposite to serene grace, think can do like this  
* if (!(gBattleMoves[move].flags & FLAG_HIGH_CRIT))
* gBattleMoves[move].flags |= FLAG_HIGH_CRIT
* 
* 
* made one hit kos a bit more usable/workable
* 
* 
* fix typhlosion line learnset curve, bring in line with charizard - DONE
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
* fix sneasal-line give better moves to learnset
* it hass great stats, but is usually only encuotnered late game,
* and is hard to evolve.
* but the biggest issue is prob, that it doesn't seem to get any moves above like 50 power.
* 
* make pressure & hi pressure work like paralysis chance to prevent  atk- DONE need test
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
* check shed skin ability, after changing define values to fit new traps, the bitwise may go wonky?
* another reason to remove new status 1 traps for grip claw & implement with conditional logic instead
* so can set values back to normal
* 
* note* potentially  remove badge stat boosts? since I will have higher ev cap stuff idk.
* 
* 
* Make copy ability of tinted lens, for non bugs, call it protag powere or subversion or great expectations  tiger cub? -
* 
* anyway for mon that can setup  multiple type power/dmg buffs i.e terrain & weather or to be used with a terrain on on team.
* 
* made grass buffs, make grass version of u-turn aka up root can be taken advantage of by chlorophyl mons - DONE
* make up root remove ingrain status to ensure you can get out if you want to/really need to
* 
* also added uturn variant for flyig types  need test animations later-
* 
* changed hail ice buff,  most ice types have higher sp def than def, and main weaknesses are 
* typically physical made 50% defense and 1/3rd sp def incrase
* make sure to test later  tweaked as realized not much raeson to pick sandstorm for rock ice types
* 
* Remember setup ability Dark Deal companion ability to nuisance
* Also need to add other abilties listed in base stats comments/port over comments/notes
*
*
* Also comb over stats again, to attempt to address power creep?
* not sure if it would matter, higher is still higher even if I bring things closer
* on the offensive side i.e atk sp atk speed  and my ev cap increase is technically already made to address this
* 
*
* Look at changes to early gen mon, consider bringing back stats from gen 1 & 2
* where special atk & sp def were all one stat  see how it changes mon
* and if it makes sense for balance - DONE this was only for gen 1, it was changed in gen 2 and most gen1 mon were balanced with that in mind
* 
* with buffs and planned addition of more mon early on, consider tweak to leveling function that will weight stat growth to later
* so you can have stronger mon in early areas without them being super op at low levels ( may not need ot its possible current function already balances that)
* if early levels aren't greatly different stat wise would make easier to balance mon for late game.
* 
* Also consider tweaking how terrain switch works, make it stay as long as the ability surge mon is on the field
* want to work like  weather switch which I think works off last in?  may work off speed?
* make conditional where its supposed to decrement if they're on field timer equals "permanet" i.e timer = 5, if not on field decrement timer
* that way even if they get one shot its still valuable to put out as a setup.-
* 
* Do I want to make all terrain last until removed?
* then make ocean permanent terrain that can't be changed set by environment
* 
* Remove drizzle & drought from mon, and replace with new ability's instead of just giving everyone groudon and kyogre's abilities
* Thinking Squal in place of drizzle  and I guess High Noon in place of drought - DONE
* 
* that way kyogre and groudon can stay special.
* plan is other weather abilities will be temporary 5 turns like sunny day but better
* as it resets the timer as long as the mon is still on the field.
* think will need to make a new struct member for it, simialr to  wrapped by
* where it'll track the battler who set the weather condition
* check will be if current weather isn't permament, and matches the weather that would be set by the ability 
* (as proof it wasn't overwritten by another weather ability) timer gets reset to 5 at end turn
* if said battler is still on the field. 
* make meber struct weathersetby  
* just need to set when ability actiavates like so gBattleStruct->wrappedBy[gEffectBattler] = gBattlerAttacker;
* do in ability battle effects just sub effectbattler for battler as ability function already uses battler as aits swithin fun stuff..
* 
* - think done, don't need weather wrapped by,  permanent weather doesn't use timer. so dont need special stuct
* just need to use plusle minum ability on field check, linked with the weather condition its supposed to set,
* if weather is current just keep timer from going down - DONE
* 
* TryChangeBattleWeather  need replace  LOGIC for all weather abilities with that function - DONE
* 
* primal weather also sets terrain,  for kyogre & groudon, mega rayquaza would only remove their weather condition
* where otherwise primal weather can't be changed.  so strengths them a bit as they keep the terrain
* 
* change mudsport and watersport to be terrain clears, will still do 
* normal move effects but they will also clear terrain *idea from Sigel - 
* 
* change terrain function elements TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer)
* to work like changeweather function replace timer pointer with true false for viaAbility - NULL doesn't need doing just adjust end turn terrain for abilities
* 
* so I can setup logic for terrain surge abilities  potentially make certain side wide type moves terrain clears as well
* i.e earthquake surf etc. -  NULL changed mind, makes terrain too accessible and thus overbearing.
* well that was dumb, was tired and literally crossed my wires,  I had an idea of them setting terrain as well,
* so they can clear terrain but not set and thats fine
* 
* don't know if need snow terrain, since I have weather condition,
* and places where I'd set hail there's no need for snow terrain effect
* unless I make it exclusive to seasons/places where it only is snowy on the season, and hail for just places where its 
* winter/icy year round.? could work i guess
*/

goto WEATHER_AND_TERRAIN_EFFECTS
/* 
* 
* new ability idea from anercomp,  high roller (name pending)  comeback king  (?)
* ability that doubles in power whenever the mon misses (or move fails), a bit of move forgivenesss
* will essentially let them make up for lost damage from the miss.
* next attack becomes sure hit.   use same surehit logic  I did for traps
* what can do is make a value/member in battlsruct set to zero,
* and hvae it increment whenever the battler with the ability misses a move or fails to land an attack (put in accuracy calc/atk canceler))
* and thn in damagecalc multiply that value by gbattlemovedamage like the critmultiplier
* but use +1 since the value starts at 0.     if ability  gbattlemovedamage *=  (value + 1)
* 
* Go over field control effects again, i.e traps status terrain weather  drain abilities make sure everything remains in balance
* I don't want to turn things into a gimmick where the only thing ppl do is status or terrain I want them to be relatively equal options
* -
*/
goto TERRAIN_DEFINES
goto FIELD_ENDTURN  //battle_util.c  includes weather & terrain decrement
/*
* New terrain notes
* 
* Overworld thunderstorm generates electric terrain //do more with this & nature power
* changing terrain can change nature power move? 
* 
//may do something with counters and advantage where certain overworld terrains can't be overwritten by certain terrain effects
//i.e scorched can't overrwrite ocean teerrain but can cancle flooded since its the opposit they cancel out, will need a seecon dus to make terrain
//also can't setup grass on desert or ocean terrain, but will work on flooded terrain  also will cancel scorched and need second use to work
//think have flood & ocean terrain have same effects but ocean is just harder to remove/permanent and only when surfing
//strengthen water as if in rain, and activate rain based abilities? 100% activating swift swim in ocean terrain 
//checked includes swift swim & hydration, exclude rain dish  but include dry skin
//think can make scorched activate abilities involving being burned or involving heat
//includes thermal exchange, guts, steam engine, well baked body, flare boost
//negative side activates dry skin
//may cut back on this so terrain isn't too overbearing/important  just check balance 
//should be fine just don't add flash fire
* 
* further plans setup snowy terrain for mountains, and winter season.
* in addition to same effect as weather buffs, hail in this case for ice types.
* Since terrain is the mon being in their natural element, I will check and activate certain abilities 
* central to the element that make sense for each terrain.
*  snowy terrain would set snow cloak etc.
* 
* //look into how fild is generated i.e grass vs water when surfacing
//specifically the circle mon stand on, want put terrain effects on that
//simlest solution depending, may just be to edit the graphic for each,
//and have it white out, and reload the circle during fade
* 
*/


/* 
* NOTES PT 2.
*  add and change for regi effects, instead of player needing to know brail, setup archologist npc, maybe in pewter town museum.
* that will "translate" the text for you to read.   so when you initially find read it, a special flag will be set.
* in the museum npc he'll chech for those flags from lowest to highest, and read the first he finds each time you talk to him.
* have him be shocked excited then say let me translate  ... fades to black and returns
* Ah I see, the text means (maybe highlight translation) "blah blah blah" clears the first set flag and then sets another
* that'll change what happens when you click the wall, now that you know what it says, a box will come up asking if yuo want to do the thing
* i.e "use cut on wall?" yes/no  then check party for a mon that can and do it if possible, or return no one is able to use cut.
* 
* 
* Emerald expansion dropped new  mon icons for legends arceus need update and add
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
* also plan to add more encounters to each area on top of changing how tiles work, so grass not on the road, and rock not on sand can spawn encounters
* but hopefully can set separate encounter rate for said tiles so its a bit lower.
* 
* good way to add more encounters to maps without needing a lot of graphic work, 
* if I can do that, then patches of grass can be used as "tall grass" and have separate encounters and 
* higher chance for double wild encounters.   
* 
* Will need to fix and add double wild encounters, as its in the game but not fixed/properly coded
* 
* also setup special event for new game, where there is a random chance for the game to set a extra flag
* that would trigger a traveling fishermin event script at the south side of pallet by the lake.
* rather than a battle he will give you the old rod, after a speel about teaching the youth/next generation the joy of fishing.
* 
* add more than magikarp to old rod, things like lotad feebass etc.
* 
* add on to normal old rod event script if the flag for the traveling fisherman is set (actually just make it the same fisherman)
* he'll remark its good to see you again, ask if you've been using the rod.
* 
* and then give you a water pokemon around lvl 10 with a relatively low stat total.
* i.e need make function that will check type and then total all the stat fields.
* 
* could also use that for new game plus, were you would alrady have all the rods.
* 
* so instad each fisherman gives you a progressively better water pokemon instead of a better fishing rod
* 
*/
goto FIELDMOVE_LISTMENU
goto CURSORSELECTION_FIELDMOVES
goto ABILITY_CAPSULE_DATA
/*
* change how ability capsule works, let it change current ability to any other abilities it has 
* make opena dialgoue displaying species abilities in order of slots and print to a box if not equal current ability
* so should print every possible ability excluding the one it currently has, populate selected ability to str_var_2
* 
* as it works now, it takes current ability to hidden ability 1 and fails to work if current ability is hidden ability
* my version will work no matter what your ability is and allow you to select any ability it can have.
* 
* similar logic to field moves loop options add to list if not ability none, and don't match the previous
* added abilities
* 
* make sure to exclude from new use logic I plan to make
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
* cleanest way is to store both mons data for the pokedex beforehand  (based on battlerId)
* and clear whoever dies.
* Then at end of battle do pokedex entries for both, make it loop
* just like other functions do, so have create function buffer mon
* to value or var used for speciees data zero out value if mon dies
* then have pokedex loop through functions baseed on var/value if they aren't 0
* -Progress-
*/

goto POKEDEX_PAGE_FUNCTIONS
goto CREATE_POKEDEX_PAGE // all values for creating pokedex page  DexScreen_PrintMonFlavorText  is function for dexx entires
goto PARTYMENU_GRAPHICS
/* Found species names were being slightly truncated in some cases, comb through added mon ppost gen 3
* all names fit current POKEMON_NAME_LENGTH  limit of 10 + 1, but some are shrunken to fit, 
* so edited party graphics box & was able to add 1 additional space no more.  need to increase name length by 1 to match
* 
* still has issue finding in battle values to adjust, need to move over gender icon
* found it ,its all in UpdateNickInHealthbox  -increased name length need to expand window width and adjust other parameters that 
* take mon name  i.e summary screen, & naming screen - playere health box works enemy can't figure out yet  
* - progress - fixed enemy health bar neeed to setup for the other places and test rest of party slots- DONE
* 
* found curreent gen name limit is 12, so need add ANOTHER space and will need to figure out how to move health bar to work smh
* plan to increase width of healthbox in battle to make names fit, potentiallly do same as category pokedex
* and have it generate different size box based on pokemon name length, just so it fits/doesn't look too big
* 
* name limit 12 is cutoff in pc, and I can't make the graphic bigger as
* there is no more space so instead I need to make the font smaller.
* 
* also my need to re-capitalize species namees as well. it prob looks fine in emerald but for fire red looks a bit off
* espcially on some of the wider characters like M  -DONE  (unless I decide to go in and redo the font to look better myself that's it)
* 
* need search repo for values [10] & [11]  and replace with POKEMON_NAME_LENGTH & POKEMON_NAME_LENGTH + 1
* as for some reason gamefreak used fixed values for a lot of the game rather than the constant  - DONE
* need fix POKEMON_NAME_LENGTH expansion issue first, as it could just spread issue throughout even more areas 
* found new issue, pokemon names are using full buffer space even when name is shorter (or I made window too big?)
* need test later to fix forgot how window value works, I thought name & lvl were in same window
* so a shorter name should move lvl values over but maybe not,  consider change to append, so it'll add on to whateveer
* the name string is instead... -
* 
* 
* redoing species name expansion
* need adjust naming screen, parrty menu & pokedex fields again
* new change add all 3 category page images I made, and make
* each their own define and have game use species name length
* to decide which to use, name length 11 use mid, name length 12 uses large
* everything below 11 can use the original have different window dimmenssions for each
* 
* found similar issue potentially with healthbox and naming screen.
* adjusted naming screen for name length but now player is off.
* need to make it swap bgs somehow for player vs mon naming screen some kind of callback or something
* 
* same thing forhealth box, want to make it adjust based on use,  so size of name length use different width healthbox
* 
* for party menu move left column mon pic up and left,
* move name over 1 character,  same for right column 
* 
* considre swap placemnt of type icon and pp in summary.
* did still has issue, only solution I see is put type icons on separate windows
* buffer all of them to each window, and just use if conditional
* to tell which window window to display  or just buffer the same thing to all windows
* to all windows and then just in the funciton that puts the window up
* I just swap the window for each instead of using move window 5.
* 
* what I'll have to do is put pp value in the middle and
* alternate the type icon from left to right for each move.
* then edit the bin to move up the window for the 3rd move data
* 
* it'll look a little off, but it'll work practically
* make a mockup compare with current and throw up on peer review
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
* rquires direct editing the tilemap to fit the icons/tiles
* 
* also move learn slot is not wide enough long moves in move learn slot get cut off
* 
* Also plan to add new string/logic for trainer memo box, for nuzlocke idea
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

goto TYPE_AND_STAB_CHECK //battle_script_commands.c  type calc also where s.t.a.b is handled
/*
* plan buff normal types, their gimmick, is being highly adaptable for their lack of weaknessand resisted damage
* but power creep(and new move restrictions) has made them lose their place, make sure pure normal always has very diverse move pool to chose from
* also as they lack stab, instead of trying to give them all insane stats to counter will instead make new jack - of - all - trades gimmick / effect
* for normal types   rather than the specialing of same - type - attack - bonus by being a normal type you have adaptability to do everything,
* so will come up with a smaller power bonus exclusively for normal types that applies to whatever type of moving they are using (excluding normal moves)
* that would stack with stab should they be a dual type - DONE
* inspiration from wolfeyvgc
* new effect calling it, jack of all trades  and gives reason to want normal as secondary type
*/ 



goto STAT_AND_DAMAGE_ABILITIES_ETC // pokemon.c function for ability and item effects that affect damage calc

goto ABILITYBATTLE_FUNCTION	//	battle_util.c function other more complex ability activation logic.  STIL need to update
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
* for setting up rattled to activate on intimidate add check for gSpecialStatuses[battler].intimidatedMon = 1;  if true i.e == 1 
* activate rattled
* note- also found all I needd to reactivate switch in ability is to call the battlescript again
* 
* smeargle changes new moves -
* 
* fix ditto make imposter its only ability (or just but  speed stat so it can transform easier)
* change imposter to be more than just a free transform on switch.
* instead make it transform into a random pokemon that resists the typeing of the target.
* will be pretty complex, need to use emerald way to read type effectiveness 
* loop through mon of type that resists, potentially need to put in list, but don't want to.
* 
* comtinue adding notes...
* array won't end well if size doesn't match random value, so do just like, starter selection random % nelems 
* but I'm making the list with the function logic,   so I cant do array nelms
* so read target's type set that as attack type then loop through entire species and if they would result
* in a not effective or no effect result.  I could add the species to list?  and then nelms the list and loop'
* over that to decide what it transforms into?
* need check if its possible to build an array from a function
* EDIT--
* try explaining agian, check target type, if target 2 matches target 1,
*  make one list and set that as atk type, and loop through all the species that
* have a defending type that  are not effective or no effect result.
* 
* Then randomly pick a species wihtin that list to transform into
* 
* If the type 2 doesn't match type 1, make two lists of the above guuidelines
* select a random species, and then compare the species for each list,
* if the species are identical transform into that species.
* 
* if the species returned is different, random % 2 to pick one of the two species to transform into
* 
* I may need to do all the logic within one function rather than being able to make an array from the function
* as it looks like arrays have to be defined in size at build
* 
* So I think I need to create the list loop the list, and passive the species value to transform into
* to a variable, all within the same function...
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
* Raised Pok�mon are not affected by Ground type moves, Spikes, Toxic Spikes nor Arena Trap.
* Pok�mon no longer stay raised (and cannot become raised) if Gravity or Ingrain is in effect, 
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