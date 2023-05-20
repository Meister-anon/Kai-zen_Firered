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


Palachu — Today at 4:06 AM
Fun fact: the new character limit for Pokemon as of Gen. 6 is actually 12 (Crabominable and since Gen. 9 also Squawkabilly)

Stat calc Iv allocation note

Meister_anon — Yesterday at 10:29 PM
ok so apparently trainer mon have ivs and are used the same way, but unlike wild mon, they aren't set randomly,  it uses fix values to generate the same ivs for each stat?
but most have 0?
GriffinR — Yesterday at 10:33 PM
That's correct
Meister_anon — Yesterday at 10:52 PM
awesome glad I understand that now



Meister_anon — Yesterday at 11:33 PM
I don't understand bit wise so I'm just gonna have to ask this.
since trainer mon personality is also fixed and based on trainer name and mon species name.

does that mean rematching the rival, or other enemies you face multiple times, with different teams,

is it possible their mon could have completely different abilities when they evolve?
As personality determines the ability slot.

GriffinR — Yesterday at 11:36 PM
No, because the way they're generated will never set the first bit of the personality. NPC trainer pokemon will never use the alternate ability
Other things like their natures would change, though
Meister_anon — Today at 12:15 AM
hmm I see, so if I want them to be able to, I need to make it use non fixed personality, or set it up to be able to set the ability from trainer party

GriffinR — Today at 12:26 AM
This is where the first byte of each pokemon's personality is set (none of these values have the first bit set).
You could calculate this byte any way you like, including setting the first bit

if (gTrainers[trainerNum].doubleBattle == TRUE)
                personalityValue = 0x80;
            else if (gTrainers[trainerNum].encounterMusic_gender & F_TRAINER_FEMALE)
                personalityValue = 0x78; // Use personality more likely to result in a female Pokémon
            else
                personalityValue = 0x88; // Use personality more likely to result in a male Pokémon

                apparently ecounter music field uses/has a gender value

[I don't udnerstanad what he meant about the bit/bytes but I can add an abilit num field to party data
and make it select the abiliity that way  il.e abilitynum 1 = ability slot x and so and so
also consider better way of assigning personality and adding nature selection to custom fields as well.
They used 2, relatively static fields here to attempt uniformity for rematches.

as it stands personality would change if mon evolves, which would change nature, but not ability,
but because of the attempt at tying mon gender to player gender, trainer mon would never naturally
have anything besides their default ability.

I can add an extra check to get around the personality shift. I think.
pretty much use the name hash to chcek for multiple instances of that trainer occuring.

from their loop through their partry find the personality value as normal,
for other appearances check each party slot for a mon of that evo line, if its in the evo line,
but the species value isn't the same,  compare personality values and have the personality value 
set at the first encounter overwrite the current value.

slightly complex but would ensure consistent nature and abiility

plan:
set direction selection for ability num & nature for custom trainer data

but for default making this change so fighting the same trainer again when they have stronger/evolved mon
would result in the same nature and abilty as first time encountering them, (would require setting it so ability can be different)

checked trainername (which is used for personalityvalue  /namehash, never changes,
so can ues that reliably, 

incase names are reused filter for trainer class as well.
only time trainerclass is every changed is for rival.
and can easily filter for him only with "isrivalbattle" function.   
(thankfully rival name "Terry" is not reused its only for rival
so check is rival battle, make loop just trainername ignore class)

logic is to loop gTrainers until you find the first instance of a trainer name(and class) that matches
the current gTrainer trainer num  trainer name
once you find that loop through that party for a mon in the evo line as the mon in the current trainer party
if you don't find a like evo line species  move to next mon in party and break out back to continue main loop
at next instance of matching trainer name.

If you do find a matching evo line speices, check if the actual species name matches the current trainer species name,
if it does match  break and continue checking the rest of party if all match do nothing, as there is no cause for a different personality value

if the evo line matches, but the species names don't match, we found our criteria, overwrite namehash of current species with that of original instance
that way even when the mon is evolved it will keep identical personality i.e identical nature

use u32 values for i, to make move faster/more efficiently
also attempt to do all this with new function rather than in createnpctrainerparty function
as this is a massive implementation and I'd rather not make the function look any uglier

would call personalityvaluechecksum or sometihng

//function value set & value comparison logic

Meister_anon — Today at 10:10 AM
Does a function have to return a  value, for it to be used as a value comparison?
like does it only make sense to use logic x == function

if that function is built to return a value?
Kurausukun — Today at 10:20 AM
I don't see how else it would work
Otherwise you're comparing with whatever garbage is in the register



Meister_anon — Today at 2:09 PM
what does it mean when this value is used?   " \ "
I see that in the repo in some places,  its not the division one

I'm assuming it does something similar to commenting?
GriffinR — Today at 2:44 PM
No, this wouldn't be a comment. It's a backslash, its meaning depends on the context. For example in a string n is just the character n, but \n is a newline
In general it's used as an indicator to treat what follows in a different way

Kurausukun — Today at 5:00 PM
It's called an escape sequence
If you Google it you will find more info

Meister_anon — Today at 5:24 PM
ok looked into it, but the way its used wasn't mentioned in the resource i found.
the escape was used at the end of a line, where a constant was being defined.

I'm guessing using the escape that way lets you extend the values for a define for
further than a single line?
GriffinR — Today at 5:35 PM
Yes, that'd be to carry the definition onto the next line


Meister_anon — Today at 12:18 PM
Can someone give me a heads up on why this text causes issue in pokedex entries?

"will-o’-the-wisp"

from what I can tell all the characters individually are used in other dex entries.

GriffinR — Today at 12:21 PM
’ is not the same as '
Meister_anon — Today at 12:21 PM
ok got it,
alright easy fix to make then
you can prob tell yes, I copy pasted from online
GriffinR — Today at 12:23 PM
You can also add it to the charmap by putting a '’' = B4 in charmap.txt. It was added to pokeemerald's, it just hasn't been added to pokefirered's yet.
This would treat it the same way as '
Meister_anon — Today at 12:24 PM
good to know,  
oh wait,
you're saying it would default to the same character oh ok cool.
ok I prob will do that then.

*/

//Single extra note, for battle script,  I think when I use a call, it has to end in a return
//but I can't use a return when jumping I instead have to use a goto

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
* comb pokedex_text_fr.h  remove unused dex entries save a little more space, also look over dex entries
* that are boring see if entries can be improved from parts of pokemondb entries
* 
* adjust charmap based on emerald update, for other style apostrophe - DONE thanks to griffinR
* 
* Changed OHKO moves, so they have a chance to land when below level. -DONE
* (since its luck, set it to work when attacker up to 7 levels below the target
* if (Random() % 100 + 1 < chance && gBattleMons[gBattlerAttacker].level >= (gBattleMons[gBattlerTarget].level - 7))
* 
* go over summary screen again, on mon skills page to give ability description more room.
* go back and see if I can't raise the ability name box, (not the Ability LABEL)  and possibly exp bar too.
* then recapitalize all type names in ability descriptions like "Ups GRASS moves" rather than  "Ups Grass moves"
* it just looks nice, and fits the fire red style more
* 
* test hidden ability selection odds again, when able to build
* 
* changing trainer ivs to be random, as most are just set to 0, -DONE
* (change works I actually lost starter fight after this,for now will leave monitemcustommove as fixed, as I think those use max value
* and making random would actually make things easier) 
* 
* forgot, set rival to devault moves, as custom move works weird where when you remove move argument
* from mon, instead of defaulting to normal move learn it defaults to no moves and mon can only struggle.
* need to redo custom move logic so if no move arguemnt use normal setinitial mon learnset function?
* GiveMonInitialMoveset
* 
* had to do that because I setup randomized starter, either I make a look up table that,
* can check starter actual species and then make custom moveset for EACH starter option
* or set it to use initial mon moveset if exlcuding move argument (prefer the latter but the former would be useful too) - DONE!!!
* 
* (tweaked setup, now rather than just replacing fixediv with randomiv constant in createmon function,
* it'll default to that itself if fixediv less than 30, and a value of 30 and above is only used for elite four)
* 
* the struggle is ENDED! now if a mon in custom moves template doesn't have a move argument listed it'll default to normal learnset  
* just need to set rival trainer matches back to customs and remove comments - DONE
* 
* need to comb over custom moves compared to learnset in some(possibly many) cases it seems custom moves
* actually are just to make things easier -
* 
* as note above says  trainer ivs are set the same for all stats, and require a value of 255 to equate to 31 max ivs
* going to setup so random trainers noitem default move, use random ivs, will actually make things more difficult/interesting/balanced
* then can set it up so gyms/custom move trainers use actual iv distributions
* 
* or could keep all ivs random,(as that also matches matsuda intentions)  and instead
* setup custom fields to set nature, and evs. and perhaps abilitynum

* -will treat ivs as hidden stat for player side as matsuda wanted, ivs won't be adjustable with an item.-
* -you can change nature, change ability, but ivs will be hard locked to the individual mon.-
* -with my ev change you'll be able to overcome bad ivs anyway, and ivs are stronger to make more of a difference as well.-
* 
* think I will treat rival starter same as roamer, where the iv data is intentionally saved
* 
* mon personality is also fixed for trainers, but I think I would like to keep that constant,
* so for rematches trainers would atleast have the same ability,
* the personality value is derived from a combination of the trainer name, and mon species name.
* 
* realized logic for damage on air targets was incomplete 
* correcting setup - DONE
* 
* Forgot to replace all instances of Levitate in basestats -
* 
* need replace gBattleMons[gActiveBattler].ability with GetBattlerAbility(gActiveBattler)  for ability check, so suppresants work
* compare to emerald for which valus should change
* 
* increase quick claw success odds - DONE doubled to 40%
* 
* idea meister fight similar to fights but with all my favorite mon  i.e mon with favorite changes
* think team will have sudowoodo shiinotic heatran etc.  
* will be full custom move and ability fight, but think won't use items
* will appear randomly on mirage island, same as legendaries can appear
* will setup like oaks lab, where soon as you walk up to a certain point, I'll come down from the stairs
* same as oak shtick, will have black version of rival sprite,  and use some of character I'm impersonating lines,
* play rival music this should be after the oak impersonation where I tell the player about new game plus
* like rival fight, should the player lose it shouldn't trigger whiteout, instead I'll heal their pokemon
* (since its already hard enough to get to mirage island dont want it to just be gone) 
* and give em the " better luck next time, smell ya later" and walk away actually no make it the teleport animation lol so I just spin away
* me appearing is not mutually exclusive to a legendary appearing so if I show up there can still be a legendary.
* 
* change iv formula, to give ivs more expression  will increase by 2.4 
* since iv allocation is random, I think I can leave ev cap where it is.
* decided won't actually make item to increase ivs,
* based on matsuda perspective, of it just being natural potentiall
* and that my increased ev cap was meant to fill in the gap left in customization. anyway - TESTED | DONE,
* 
* 
* more efficient player pc actions, be able to close pc while holding mon,
* make it put mon back where you had it then press again to close pc
* logic when picking up mon to move have it save current position before moving,  for both cursor and the mon
* when pressing B while holding mon, set cursor to original position, do put down animation and return mon to original position.
* 
* When using the move pokemon dialogue allow for depositing all your mon, as you can still withdraw mon before returning to overworld.
* instead of bringing up last mon text make "you have no mon left" if you hit cancel before putting mon back in team.
* pretty much jsut a safety to make sure you don't accidentally go out with no mon, which I think would break the game.
* 
* Add Hold A option for the orange cursor, to withdraw and deposit mon menus plan is let you deposit/withdraw multiple mon at once.
* right now when using selection cursor(orange one) it goes straight to box selection with a multi select option.
* you'd still need to order your mon properlu before you used new drag/drop option but that woudl stil be far better.
* 
* want it to auto detect free spots within the box you want to deposit mon into and just slot them into those positions
* automatically based on order of first mon selected and first free space encounterd top to bottom.
* 
* make new text for functioality, if not enough slots for selected mon in box,  bring up yes no dialogue
* "Not enough space in box, deposit anyway?"
* If you sselect yes, it'll do the loop depositing mon into the box until its full, it'll then
* loop through the next boxes until it finds free slots and deposit the remainder there.
* 
* And if the box is full, don't bring up a dialogue just say "Box is full"  and make you select a different one.
* 
* Use that new logic for when on the move pokemomn menu and you have mon selected and are trying to place them as well.
* Rather than the stupid thing of it holding them in a straight line and you only able to place them in a space of a flat line.
* 
* So if you have a group of mon selected, but there are filled slots preventing you from putting them down in a line.
* Use that same looping logic for placing htem within the box, just make it look for n number of free slots
* and auto place them, with the cursor going to the position of the last placed mon, so you know where they are.
*/
goto DEPOSIT_TO_PCLOGIC //in pokemon.c covers box position, and how it reads space in the box
/* 
* setup pokenav, show potential area encounters but want mon to be greyed out until you've seen them.
* so just see a silloette-
* 
* bad onion b.o trainer repellent figure logic think it would temporarily set trainer view of every trainer on
* current map/map section to 0, so its talk to fight,  like repel long as timer isn't 0-
* 
* tweak field moves, since adding item use selection to summary menu.
* will keep cut and fly as field moves, and softboiled review list and think to remove others.
* as they work with metatile anyway.  and change sweet scent to an keyitem.
* that way can set to select and do quick encounters. -
* 
* make game run smoother, i.e faster base text, move animations, battle text
* movement speed as well, want to move twice as far, without needing to 
* change the actual walking animation. and make running slightly faster
* pretty much optimizing things so speed up isnt so necessary,
* but not so fast the game loses the chill vibe -
* 
* redo disobedience mechanics to work on player mon, just for the sake of new game plus, as the point is to  make the game like new again
* and allow you to go through the trials with a different team.
* since I don't want to ruin player choice/fun, I will only make this apply in new game plus mode
* so use newgame+ flag to check if mon should be disobediant 
* 
* [keep track of  flags not to be reset by newgame+
* 
* find plans for new game + mode I think plan was you'd be sent back with all your items money, etc.
* but mon in your party would be reset to lvl 1. (keeping evs ivs moves friendship etc
* think change encounter data to lvl 1 met fateful encounter text)
* also reevaluate benefit of new game + as original idea as makign the game new again and having a way to get other starters...
* 
* played OPAL effing amazing, incorporate the great qol stuff frome there, flame charge buff to raise speed, (oh it already does that lol)
* try to get meowth forms, setup exp share with icon on summary screen. [would make Cefireon ghost flying in my game]
* 
* -ALL THE ASSETS ARE INCLUDED WITH THE GAME ALL ICONS AND SPRITES SFAFWJAGRGARAGNSNIODNVNVDHFB
* 
* -checked can't use backgrounds as they're too large,  about 100x the size of typical gen 3 backgrounds/terrains
* -also their mon pics use 160 x 160 where base game uses 64 x 64, so would need to resize
* -64 is thankfully a flat percentage of 160, so percent based resize will make it fit perfectly. (hard part would prob be pallete conversion)
* 64 is 40% of 160.  so 160 reduce to 40% of full size and it'll fit perfectly
* 
* -base game terrain png is 64 x 88   opal terrain uses 512 x 288, hmm ok if I can resize potentially useful
* but I think I'll just take and resize mon pics only
* 
* Ok another thing to add from opal, ae capsules, items that boost IV's, rather than other stat items that boost evs- =SCRAPPED
* 
* -ok found mon data for opal I can put in learnsets  variant forms data etc in but for things like meowth
* where it has multiple variants only one data set is listed, so I hope/ assume stats are all the same but I don't have a learnset
* will assume identical moveset and just substitute in the type based move where you get it
* 
* [want to include opal forms/mon as an official region, far as my game is conscerned that is gen 9 its better than anything]
* [I'm treating that as its official] - like red is in the game anyway and it mentions kanto and oak and the pokedex
* -its only right to tie it all back in even if the story of opal takes place many decades after gen1, can consider 
* professor ebon/ebono to be a genenration or 2 younger than red, maybe can say something like he took 
* a pilgrimage in his youth as a young professor to kanto and worked with professor oak
* then again black don't crack, and he calls himself grandfatherly, so could possibly have him be around the same age
* maybe make a cameo as someone touring to learn to be a professor and furthr his knowledge of pokemon rather than a league champion]
* 
* plus item use text on summary rather than just give/take, to goto bag menu/medicine  bag select how many to use from there
* make stat boosting faster, also copy some of their item cost changes.
* copy logic from tossing items, calls same box.
* just change to "use how many?"
* make item use work with a loop, (keep in mind item use graphic need to make sure that only triggers once, per "use"
* change item use logic to use a loop,  value for "used" and quantity is "quantity selected"
* "used = 0, increment long as used is less than quantity selected"
* then need to filter use items that can be used in multi use
* i.e only healing and stat boosting items and pp ups.  not status cure items
*/ 
 goto ITEM_USE
/* 
* low cost of ev boost items.  1k or 2k per rebalance other things I like that cost economy balance
* get incubator so can hatch eggs easily while on the go, would greatly speed up breeding as well
* include flame body/fire ability in party boosts speed of all  
* rename mon and relearn moves from a npc/attendant in every pokemon center
* plan to put 2nd nurse attendant in front of counter by left corner (but not directly infront of flower)
*  to serve this purpose -
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
* test rotom, gave custom dex entry based on legends dex -
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
* - think I may bring trap escape hp drop back, will just need to fix my implementation of  new trap effects
* 
* buff in a pinch abilities, activate soon as hp hits yellow i.e 50% - DONE
* 
* General repo update compare to griff red modern fire red search #ifdef BUGFIX
* and replace bad code with bugfixes don't know if it'll make a differnce or not though - DONE ?  yeah done
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
* give gumshoos move first impressions and facade as evo moves, leaning into trump pokemon idea
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
* made one hit kos a bit more usable/workable works when up to 7 levels below target- DONE
* 
* 
* fix typhlosion line learnset curve, bring in line with charizard - DONE
* 
* NEED double check trap logic, may not need to make them status 1, to keep from being reset when mon switches
* occured to me its not a status1 thing becuse confusion persists if mon switches, so its prob just somehting in trap logic?
* either way, reset status stuff so status1 doesn't move-
* 
* for wormadam line, buff anticipation ability with disguise effects,
* it warns of a super effective or ohko move, and gets a chance once a battle to dodge one super effective move
* allows for a chance to stay in rather than having to switch because you know a move is coming.
* is part of switch in effects i'm trying to make reactive, so if you don't take a super-effective hit and beat enemy, move should check again-
* 
* do similar for ability forwarn, since it checks the enemy for a move, set it so if they are targetted with said move
* it will miss, something like their psychic powers let them avoid damage, 
* think of it like them predicting an attack specifically from that move -
* ( can use telepathy logic  for these effects, its essentially telepathy but single use)
* can attempt include type component to check which move woulda actually do most damage to me, more than just power based
* 
* think it may be too powerful for these abilities to reactivate when new enemy switches in
* idk maybe not psychic type is usually pretty frail so this gives them slightly safer switch in, 
* and more longevity
* - or could just make it on use for the invul, but next turn it will still inform of the most damaging move
* just do a check similar to intimidate where it changes a variables value when the effect triggers
* 
* 
* gDisableStructs[battler].isFirstTurn == 2  is logic for mon switchig in, can use for switchin reactivation condition
* 
* fix delibird learnset oh already done
* Give crabominable a better front sprite, its just ugly 
* -progress
* takng inspiration from wendigo lore mixed with abominable snowman - lore actually works too 
* since its a selfish mon that desires to conquer and be the best, so put it like its desires went ary.
* 
* Fix Pyroar F sprite front & back , guys in pret won't do it, so I'll have to. its potentially worse than crabominable I can't even look at it.
* 
* remake SPECIES_GOTHITELLE line sprites, to something more in line with gothic lolita, not ugly may take inspiration from Ori for final evo,
* black/white bob/bangs instead of the weird spike spider hair
* 
* make cursola signature ability PERISH_BODY only activate for enemy mon
* watching JPR Poketrainer showed me how niche/bad it is, especially whene mon already has such low def stat
* even without perish song on it if it gets hit by a physical move its not sticking around long
* 
* Also give cursola better, more cursed sprite, based on image found
* 
* GIVE Turtonator more stab moves? or more early moves
* 
* fix sneasal-line give better moves to learnset
* it hass great stats, but is usually only encuotnered late game,
* and is hard to evolve.
* but the biggest issue is prob, that it doesn't seem to get any moves above like 50 power.
* 
* added more buffs to paras line with ideas from youtubeer Zen Mode also leans
* into what I want of giving a good reason to use mon indivdually from their evolution
* if they change greatly between evos.
* so parasect gets ghost type, bring up sp def for eviolite on paras
* give parasect ghost moves  evolving to ghost will make FAR more defensive, but
* get less use out of effect spore with normal fighting immunity
* give parasct nightmare in learnset  potentially added ultra sun dex entry
* Also give it pain split  & shadow punch  and dream eater and destiny bond
* 
* make pressure & hi pressure work like paralysis chance to prevent  atk- DONE need test
* 
* made custom paralysis effect, electric types can be paralyzed, but only by non electric paralysis moves - DONE
* 
* buff for suction cups, give it built in grip claw, using a trap move with suction cups will extend its duration
* in addition to normal force switch prevention effects
* 
* make revisions to add grass moves to sudowoodo line lvl up and tm learnsets   thinkin ingrain & bullet seed
* think want to also add beatup if it doesn't have already
* 
* GIVE shiinotic creepier more cursed front sprite -
* and change type to grass ghost but give ability nymph spirit to give it triple stab, boosts fairy type moves think 
* will roll in illuminate effect aswell  as replacement, nymphs usually draw in forest creatures so it would work. -This part is done
* Ability name toadstool nymp
* 
* Need add more ghost moves to its learnset  also dryads curse
* will be its signature move, unsure of what stat to drop.  ok think I've decided to drop atk stat 1 stage,
* sudowoodo would also get the ability but since shiinotic is a sp atker w low physical atk, it'd be able to take best advantage of the move.
* 
* Finish setup for move Dryads Curse effect need do stat drop & animation -  think Stat drop done
* animation idea, ingrain roots and wrap/bind constrict anim but with a black or darker color?
* or ingrain with mon shake but without the orbs  -DONE, need test combined, ingrain and ghost curse
* 
* Setting up flash freeze to just use sheer cold animation for now- will prbo keep DONE
* 
* For different forms, i.e hisuan alolan galarain cefirian, setup icon similar to pokerus in summary screen
* that will show a pokemon has the relevant flag set, and will evolve into its alternate form
* perhaps can demonstrate to player, with one of the in-game trades?
* just want to put a little letter in the bottom right of summarys screen box where mon pic is
* A C G H hopefully of different color for each  thinking seafoam/light green for ceferia  orange or red for alola
* purple for Hisuian? maybe dark gold for galar idk
* 
* abra buff, gave comatose, slightly buffed health to help give a chance of staying as abra to keep status immunity
* buffing to give comatose end turn healing 1/8th max health  as it takes double damgae from hex etc.
* and guarantees sleep based damage without having to get hit by low accuracy sleep move.
* Also keep in mind plan to allow being damaged by multiple status 1s at once, which would mean removing
* volatile status immunity from comatose, so consider this balancing for a future nerf  - DONE consider give substitute to comatose mon if needed
* (prob just for abra, as it learns sub byb tm gen 1
* 
* STATUS NOTES-
* could put in exceptions for statuses but it wouldn't be for every ability as for others unchanged
* itd be a nerf, and it might not make sense to do for some and not every in the category, even if it makes sense.
* hmm ok I think I can make it work actually, it'd be the ones that don't require setting up weather or some other effect to work.
* i.e rain dish wouldn't need it. but again each thing is balanced with an intended draw back so prob best to just not do that for these.
* just for intimidate trace and the draw in attack abilities should be fine
* 
* ...many moves were tms in gen 1 were replaced with move tutors or just lost from learnsets, of those
* abra was indeed able to learn substitute in original red blue yellow... o.o
* 
* will reinstate gen 1 & 2 tms that were removed from tms  full list below -
Body Slam	 Normal   TM08
Counter	    Fighting  TM18
Double-Edge	 Normal   TM10
Dream Eater	 Psychic  TM42
Psywave      Psychic  TM46
Explosion	 Normal   TM47
Mega Kick	 Normal	  TM05
Mega Punch	 Normal	  TM01
Metronome	 Normal   TM35
Mimic	     Normal   TM31
Egg Bomb     Normal   TM37
Rock Slide	 Rock     TM48
Seismic Toss Fighting TM19
Softboiled	 Normal   TM41
Substitute	 Normal   TM50
Swords Dance Normal   TM03
Thunder Wave Electric TM45
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
* maybe offer de-evolution option? since I'm buffing some pre evos to be alternate ways to use a mon
* as it may be better at times to use the pre evo, based on what you want.
* if I do, i think will setup on cinibar island in the fosil restoration lab,
* something like "in the course of our research on fossil revitilization we discovered a method for reversing
* pokemon evolution, a "de-evolution" process if you will" -
* 
* update level up learnsets from emerald gen 8 files, and then adjust learnsets as I chose 
* based on my learnset expansion, since I can fit more moves now
* 
* Make copy ability of tinted lens, for non bugs, call it protag powere or subversion of great expectations  tiger cub? -   DONE ubt need test
* litleo  other vrsino  tigr mom o.0 will lower target defense on switch specific for female variant evo -  setup need test
* text for tiger mom,  "blank cowed the enemy\ into submission"
*cowed - to cause (someone) to submit to one's wishes by intimidation.
* need update constants/battle.h status 3 defines tweak setup or move some things to status 4 and change fieldsports embargo heal block to work as side status-s
* 
* BUFFED pickpockeet to have slight contact based damage reduction
* 
* buffed illuminate added compound eyes accuracy boost
* 
* *note*  Nidoqueen line intentionally can't be breed, something to do with comprison to real life rhinos not being breedable in captivity.
* so just make sure nidoqueen are available to catch in places, put them in safari zone I guess...well no that'd be even worse.
* make them wild somewhere in mid game/late game  put in desert area I guess.
* 
* adjusted multihit bs messages, check fury cutter see if is satisfactory - 
* 
* go over move chart, adjusting for low accuracy moves, bring up everything below 75
* meta is revolves around 1 shot or 2 shot, so low accuracy moves would never be worth the risk and just never get used
* especially if it doesn't have some other effect besides damage - DONE
* 
* made changes to psychic fangs, need test -
* 
* last thing I could do before break, is adjust the summary info box for ability description
* actually simpler than I thought, all I need to do is move up the text and fill the bottom of the window, with the```
* description pixels - may not be able to move window?
* 
* buffed arceus, gave global stab, and changed to mystery type
* 
* check moves that rely on enemy using a move first, make sure they use last used move, so they don't 
* just fail if they are faster than the target - think mostly done, need check mirror move and setup sketch monotype changes
* 
* fix focus punch move will NEVER work as is, instead make into a one turn move with recharge effect will also add high flinch chance - DONE
* another thing that will need ai adjustment later
* 
* add rock throw to more fighting types (or make tm), only for muscled bulky arch types
* 
* anyway for mon that can setup  multiple type power/dmg buffs i.e terrain & weather or to be used with a terrain on on team.
* 
* made grass buffs, make grass version of u-turn aka up root can be taken advantage of by chlorophyl mons - DONE
* make up-root remove ingrain status to ensure you can get out if you want to/really need to -
* 
* make sure mon types have their own niche where needed, i.e bugs imune to confusion because of hive mind
* grass immune to powder, ease of access to status moves to take advantage of multi status and higher than average vitatliy as part of nature
* fire can't be burned, poison can't be poisoned etc. 
* 
* need buff poison i think
* for poison think can just give sp def boosts, as poison specialists poison themselves to build up immunity to poison
* giving them a stronger than normal internal constitution. - DONE
* 
* also added uturn variant for flyig types - DONE  need test animations later
* 
* changed hail ice buff,  most ice types have higher sp def than def, and main weaknesses are 
* typically physical made 50% defense and 1/3rd sp def incrase
* make sure to test later  tweaked as realized not much raeson to pick sandstorm for rock ice types
* 
* reworking poison type add normal type to pure poison that is poison as a function of animal attributes
* leave the more amorphous mon as pure poison - DONE
* 
* 
* Remember setup ability Dark Deal companion ability to nuisance
* Also need to add other abilties listed in base stats comments/port over comments/notes
* 
* Dark deal effect
* companion ability to nuisance, most effect is on partner, 
* give user devils luck i.e increased crit rate or double effect chance random % 2 if move power greater than 1
* usr gets increased secondary effct chance OR crit, the partner gets both, but in exchange all moves above base power 70 get their power cut in half
* 
* sounds like a nerf but is meant to work together with nuisance which increass priority of moves if they are weak,
* essentially expanding the move pool that the ability can pick from.
* think can do effect with edits to set effect chance bs command/function and a flag set to add high crit flag to move?
* potentially do like focus energy where it raises crit ratio instead, so its more easiy controlled, i.e can better control the crit
* can use critcalc  function for partner boost, use + 2 * partner ability dark deal
* then do other part in seteffectchance function
* for mon with dark deal, get either or crit boost or seconaryr effect boost each turn, flip with random % 2.  between 0 or 1  choose crit booost, vs effect boost
* changed mind,   since it doesn't have negative effect just gave both effects at lower values than the partner.
* still need to write ability description but effects are complete -
* 
* Also buffed/adjusted crit stag ratios, a mix of late gen higher crit odds, with lower ones.
* approx 10% crit increase per stage up to stage 4 which is guaranteed crit
* 
* think will give this ability to murkrow line, since they're mob boss potentially obstigoon as well.
* 
* //then finish new grass move nettel something
* got set deciding to setup move descriptions in.c file remember can just add file, as remember I added updates from  pret
* to simplify adding files.
* 
* updated move descriptions and trainer tower fils to C files,  following pret commit history, double check later if there were any issues
* all that's left is setup animation for Nettle Whip/vine   - for now fill with generic vine whip animation
* 
* I think use vine whip animation, smack target 3 times, and then do astonish effect on target, where thy get the exclamation point thing. -
* 
* late gens restricted toxic, so only poison mon can learn it, that's too restrictive imo, I'll limit it to grass bug, poison and dark. -
* 
* think fixed setup for heal block as side status,  should work for blocking all items as well,  made new heal block switch in anti heal ability
* plan to give to guzzlord, try find other mon as well. -
* 
* because of embargo and heal block changes, need to setup new bs command jumpifsidestatus to replace use of jumpifstatus3 for them
* 
* also setting up embargo as side status ability, will give to theif mon, liepard  theival etc. also give them pickup if they don't have it. - DONE
* 
* nother idea true anti heal, gbattlemovedamage *-1  if attempts to heal re-reverses damage formula, so it causes you to take damage instead.
* giratina origin  etc.  imagine uses rest and just dies off rip 0.o
* can give to darkrai too, since you die in sleep when you're trying to rest use same move effect list as IsHealBlockPreventingMove
*ABILITY_DESPAIR  and look at itembattleeffects etc. setup like healblock has 5 turn timer or no timer, if permanent do if ability on opposing side
*
* Also comb over stats again, to attempt to address power creep?
* not sure if it would matter, higher is still higher even if I bring things closer
* on the offensive side i.e atk sp atk speed  and my ev cap increase is technically already made to address this
* 
*
* Look at changes to early gen mon, consider bringing back stats from gen 1 & 2
* where special atk & sp def were all one stat  see how it changes mon
* and if it makes sense for balance - DONE this was only for gen 1, it was changed in gen 2 and most gen1 mon were balanced with that in mind already
* 
* with buffs and planned addition of more mon early on, consider tweak to leveling function that will weight stat growth to later
* so you can have stronger mon in early areas without them being super op at low levels ( may not need ot its possible current function already balances that)
* if early levels aren't greatly different stat wise would make easier to balance mon for late game. -tested, not needed
* 
* Also consider tweaking how terrain switch works, make it stay as long as the ability surge mon is on the field
* want to work like  weather switch which I think works off last in?  may work off speed?
* make conditional where its supposed to decrement if they're on field timer equals "permanet" i.e timer = 5, if not on field decrement timer
* that way even if they get one shot its still valuable to put out as a setup.-
* 
* Do I want to make all terrain last until removed?
* then make ocean permanent terrain that can't be changed, is set by environment
* 
* Remove drizzle & drought from mon, and replace with new ability's instead of just giving everyone groudon and kyogre's abilities
* Thinking Squal in place of drizzle  and I guess High Noon in place of drought - DONE  test
* 
* setup weather moves, to increase duration of weather effect if used again
* if you count you don't need that, now question is, with being able to do that does that balance the low pp use?
* I think so, ok all weather moves will have pp 5, but be extendable if used again.
* 
* that way kyogre and groudon can stay special.
* plan is other weather abilities will be temporary 5 turns like sunny day but better
* as it resets the timer at turn end as long as the mon is still on the field.
* think will need to make a new struct member for it, simialr to  wrapped by
* where it'll track the battler who set the weather condition
* check will be if current weather isn't permament/primal, and matches the weather that would be set by the ability 
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

/* adjust enemy battler placement for double battles, seems doubles aren't well optimized in fire red...for some reason
*  health boxes cover the enemy, need to move them higher, and move field they stand on by same amount
*
* moving sprite placement is a combination of gEnemyMonElevation  which is additionnal floating position for mon that fly/levitate and
* gMonFrontPicCoords  which is the coordinate for every mon, and can go into negative values to raise higher
* for non floating mon believe a tentative value of yoffset - 8 should put them where I need/want them.
* flying mon will be harder,   but will need to specifically filter the change for doubles only,
* which can do with IsDoubleBattle  function  this is from battle_anim_mons.c may actually be able to do all changes from there?
* while gmonfrontpick coords is the source it seems to be mainly accessed through GetBattlerYDelta,  and can make changes there and have
* it populate everything else rather than messing with src data, for extra protection
*
* need find differene betwen GetBattlerSpriteCoord & GetBattlerSpriteCoord2   they both go to GetBattlerYDelta
* but the first doesn't immediately go there, and allso handles some X values not just y
* also it uses this  "sBattlerCoords" before the other function does.
* not yet sure how to read it, but it seesms to prove/show that singles and doubles use separate values.
* also it SEEMS like position x y is determind by taking an average of the values in sBattlerCoords ?
* 
* near done, needed to move trainer pic as well also adjusted default battler position height for doubles
* battler right sat higher for some reason made more even, so height boost won't be uneven.
* still need to move terrain, updated defins but requires 4 pixel graphic edit to raise.
*/
goto SPRITE_COORDINATE_AND_ELEVATION_LOGIC
goto FRONT_PIC_TABLE    //table for front pic use rules to standardize mon brought in from expansion
goto MON_ELEVATION_TABLE    //SAME BUT for elevation

goto TERRAIN_DEFINES
goto FIELD_ENDTURN  //battle_util.c  includes weather & terrain decrement
goto BATTLE_TERRAIN //Battle Terrain, NOT TERRAIN effect, is the entire battle field, including part battler sits on, can use to make terrain effect
goto BATTLE_SETUP_TERRAIN   //sets battle terrain from metatile/environment
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
//plan setup misty with ocean terrain in gym as introduction to effect
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
* 
* the circle is attached to the backgrond presently so setting up different terrain would require every battle terrain have 5 or so variations
* just so I can change the circle. on top of needing 2 different sets for each because of needing to move the circle for single and doubles etc.
* 
* rather than that I'd prefer separating the circle graphic from the normal background base (look at opal grpahics think it does that)\
* if possible I'd like to use it as an object, similar to health box etc. is handled where I can just load it onto the background
* only question is if the pokemon would still sit correctly on that, or would they be under it, as an object would have a highr
* "priority"  if I can separate it, that would solve everything,  it would stil build from the tileset,
* but I can move the object dynamically with code, /a window rather than needing to make multiple variations
* 
* yeah opal has the battle background and then the png for the base to sit on separately
* base pokemon has it all tied up together  hopefully can separat without coming up on some gba limit
* 
* terrain would need to load in and slide in, like trainer sprites
* incidentally strainer sprite proves its possible to separate the sprite and have it sit on the background
* as the trainer sprite is also a png and does exactly that.
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
* believe I've sstup rtc need to see if it works, further ssetup day night graphics (the good ones with proper night lighting)
* daily weekly monthly & seasonal events to make the world feel real.
* and time and season based encounter data
* would also need tile changes for areas that would get snow in winter
* deserts and tundras would remain unhanges year round
* 
* Emerald expansion dropped new  mon icons for legends arceus need update and add 
* - added stat data, need setup pokedex data and acual sprites/graphics and cry data, think will just use base mon cry rathr than new ones for space -
* 
* 
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
* -removed famechecker for space, have rival give dexnav in cerulean instead of famechecker
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
* 
* 
* species based  ai?? like archtyps for the type of battllere based on species data  i.e tricksters, more patient mon, harsh attackers, healers etc.
* had an old idea based around nature based learnsets, so wild mon would perform differently when you encounter them
* based on their nature
* 
* but learnset array like all arrays are static, (least in c) so I can't just filter the array
* but instead think can do by changing wild mon move learn, would potentially apply to wild mon and trainers without custom movesets
* can possibly apply filter for trainer struct  like  TrainerMonNoItemDefaultMoves
* 
* GiveBoxMonInitialMoveset is the function that deals with wild learnsets..I think, also includes function i think is for deleting 
* the first move it learned when learning a new move  tpye of FiFO process.
* so if add a lot more moves to base learnset, and the using functions to filter the array for what it decides to learn,
* or skip, to essentially make the mon move learning look more like the player decision making
* and once you catch it, what it has wouldn't matter as we have move relearners in the poke centers.
* 
* Learn more about learnset limit, and how to increase?
* Being able to add much more moves would be greatly impactful/helpful.
* would get rid of the long gap of not learning anything, and need to attempt to space things out
* the same way its done in base game.
* 
* move relearner
* max level iup moves
* 
* we're learning all the time, and can say mon learn faster, so argument its more natural.
* more options would allow for better/easier customization of style of play. - DONE
* -raised to 35, appears to work without issue, also had to raise move relearner/move tutor as it seems to use same thing
* 
* next goal setup better move relearner logic, so mon like stone evos don't just have no moves if you evolve early.
* make it so when you select a mon for move relearn you have the choice to choose from that mon's moveset
* or any of the pre evos move set, up to the level you're currently at.
* that way its more balanced and you don't just evolve and get all the moves, like the cases where pre-evos are 
* just all the same moves but ata lower level. 
* 
* So instead of looping pre evo moveset to lelarnset end just go up to current level.
* put move relearned in pokemon center, select mon, like normal, but then it opens a dialogue
* which moveset do you want to choose from?
* "Ninetales's Moveset"
* "Vulpix's Moveset"
* start with current species, and going down the evo line
* when you select here then it would open the moveset w moves learned by that mon up to your current level
* for some mon this would be unncessrary as learnset is the same, but for stone evos etc would be a major upgrade.
* 
* can setup list by reading evo logic in reverse
* use  GetEvolutionTargetSpecies(struct Pokemon *mon, u8 type, u16 evolutionItem)
* targetSpecies = gEvolutionTable[species][i].targetSpecies;
* 
* 
* that way you can return the pre evo
* start list as first value if can evolve returs 0, just return mon i.e species. -doesn't work either, would break for mid evos
* 
* and have it append to list.
* given that logic and the exaample given,...that wouldn't work, ok if I did it that way it'd
* only find the evo given the pre evo which is the oppoite of what I'm trying to do.
* 
* So instead return species of mon first, append that to list.
* and then read evo table in reverse from there.and include level compnonent
* that way ninetales would be added to lsit firt then it would look for pre evo and find vulpix
* and add it to list next, would then just need to break if can't find another pre evo
* 
* ok not technically possible to read in reverse, as it works by reading a given species value,
* than loops through evo methods reads parameteres and finds a target evo species from that.
* 
* without the x value you cant get to y, you can't read backwards.
* 
* 
* Instead load current species to separate target species value. Loop entire species list rather than using a given species
* stop when you find a species whos target species equals saved species value
* and return that species value as the pre evo and add to list
* 
* do repeat until you reach species list end (NUM_SPECIES or FORMS_START), that way you know you've found all the pre evos
* and no existing mon evolves into the one in question
* 
* want to exclude evolution method mega evolution
* 
* will need to make a function from this to find pre evo -
* 
* -will also use for de-evolution logic, will make functionality for others, but not use myself as there isn't a need in normal pokemon
* 
* thanks to emiyasora have a starting point for reference, forgot that breeding/daycare logic essentialy reads back through evolution.
* that may be what i need.
* GetEggSpecies     yup that works perfetctly,  it loops through species until it finds no mon that can evolve into that mon.
* 
* List apend logic can be taken from fieldmove append list
* 
* 
* idea for ev boosting gym do with safron city fighting gym  could give ev boost items there -
* 
* think will remove need for badges to use overworld hms, makes more logical sense.
* instead balance progression by availability of mon with those abilities.
* 
* only need mon that can learn the move to do hms.
* for fly/surf set it upp that you need a mon of a certain size.
* can do by comparing pokedex value, pokemon scale with trainer scale
* long as trainer scale is greater than pokemon scale, mon is bigger than player
* to give some wiggle room, will do if ((pokemoonscale - 30) is < trainerscale)
* 
* may do away with, if it ain't broke dont fix it type of situation,  doing this would create a forced list of mon
* you'd need to keep in your party, while its realistic, this is still a game, and the average player won't want to deal with that.
* 
* while technically I could do this without a problem, as I'm planning to  add the legends arceus holder that lets
* you carry extra pokemon outside of the party, and let you swap their place  on commmand.
*  that would essentially bring up a similar issue to hm slaves, but it just wouldn't be inconvenint, or as inconvenient.
* 
* Reconider later, still haven't even attempted adding the carry case.
* would be 6 (or less) extra slots of mon that would be held in a pc type thing
* simplest thing would be making 1 extra pc box, with fixed title only accessible via this item.
* no need for new logic, or graphic
* 
* //shifting 8 is the same as using 100, left shift << is multiplying,,  >> right shift is dividing
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
//notes for gameplayloop below
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
* 
* game loop improvements, game is old, people are used to games being faster now,
* I want to fix that, on top of addressing the issue, of not having reason to grind.
* it needs better time/reward investment
* with my changes you'll spend more time catching the same mon, (or some people will)
* so I want to add arceus style improvements where you receive items for releasing mon.
* chose from multiple fields to add, at their own odds ev items, the items the mon gives/has a chance to hold (make sure every mon has some held item item1 & item2)
* and other random odds ends to sell,  but keep in mind also plan to eventually setup timed events with nuggets other item give aways for economy management.
* as well as plan to make all trainers rematchable which would make it easy to get more money from grinding battles.
* plan to do via time or a stepp counter, when condition is met, reset trainer flags of all npc on map.
* this would also give rise to need to use b.o  trainer repellet from pewter, further setting the realistic world economy, etc.
* 
* potential idea need recharge gems with element stones instead of removing item, after gem is used up in battle,
* add item to bag, that is a grey gem,  spent gem something,   late game wont need evo stones so this will be new use for them,
* Add Lore Gems captured power of the elements, from crystalizing/forming in environments near evo stones
* which is why they are able to boost the elements,  will make require two evo stones,  so elements
* that don't have a specific stone evo, can use combinations  i.e dusk/water for poison maybe
* fire gem  2 fire stones  stuff like that.     Gem collector that does this also place to buy gems at highish cost
* to make this sytem worth while   
* able to farm gems and fossils from underground  or just inside different caves, prob inside caves,
* save map space, simpler and gives reason to back track
* 
* other thing adjust play speed without needing speed up, so music doesn't get changed.
* make options menu flag for increasing movement speed. can reset to default from options menu like text.
* best case can move further without changing animation so it still has that laid back feel.
* have to ensure you still move actually occupy the space/x position or would cause object clipping.
* 
*  Also adjust move animation speed.  could potentially shift animation by a multipple so they all change equally?
* file battle_anim_scripts.s  look at commands for battle anims as well
* change move speed, text speed, and animation speed,
* make new faster but not instant text speed, already have how to, in screenshots
* 
* 
* plan to be able to catch every legendary one way or another, initial idea was they'd randomly show up in cerulean cave after mewtwo
* but that would be boring to always just go back through the same cave so instead.
* 
* have multiple different options for finding legendaries, cerulean cave, another hidden cave, 
* port mirage island but with better mechanics, i.e will appear once a month at midnight for one hour with an npc telling you if its available
* or when its coming each with their own set of legends to spawn. the rarest would go to mirage island the mystics i guess
* things like guzzlord could go to cerulean cave the dark or bad ones
* -could also put mirage island alerrt in space time upgrade for dexnav from time events
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
* found just enough room, to fit move names with type icons, but need to adjust bin file for graphics.
* as needed to raise pp values with new move name placement for moves 1 & 3.
* was able to confirm I need to raise those spaces up 3 pixels to fit pp values.
* after that will need to make the space from the bottom smaller to make move name not floating.
* appears to be double the space for pp value? will balance out since moving in opposite direction so won't look too off.
* will add 3 pixels of white space to top of window, then will start with removing 6 pixels of white space from bottom of window
* tested its 3 & 3 perfect equal add 3 whitespace to top, and remove 3 from bottom.
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
* [enemy gets stronger...prob best to have it reset and not be permamnent...unless I want to make a fuck you hard mode] lol make hardmode flag XD
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
* ABILITY IDEAS -
* 
* want to setup mega marowak themed after ancholysauras
* thick armor plating stronger bones
* new ability idea, is um damage reduction  I think 20%?
* 2nd ability turns every special move into a physical contact move as marowak learns moves like flamethrower but has trash sp atk 
* also good for machamp, inspired by Mashle believe will call elemental muscle - DONE
* hmm may actually be able to do a special animation for it,  like fire punch, can add the fist animation to the end of moves if ability is e.m ?
* would need to setup new macro?
* think can do same thing I did for truant and make new bs that will play an animation I want.
* think can do punch/foot animation and have it play the punch animation during or after the normal move animtion
* would need to setup like I did for multihit, do ability check and then play animation
* idk if I can gete timing perfect, but hopefully would work
* 
* ability liquid metal, for regi-steel effects of light metal, but also reduces damage from contact moves, like fluffy does
* not sure if will do full 50% reduction or do a 33% reduction instead. prob the latter
* could make it a metal absorb ability?  idk if I'll do this, would be interesting as it doesn't exist
* but not necissarly good as steel is so good as a defensive option not an offensive one.
* instead decide to mix in clear body effect - DONE
* 
* //Glacial Ice for regi-ice negates fire damage also combine with ice-body effect to heal during hail and add low chance to freeze on contact
    //make sure stacks with hail effect freeze chance boost 
    //think may also combine with volt absorb so ice attacks heal it, so its immune to fire & ice, but ice heals it - DONE
* 
* Rock Collctor (name pending) for regi rock //rock version of volt absorb, that also absorbs stealh rocks
* think will have it also heal if absorb stealth rocks
* Anthroyd came up with name "Erosion"  will use that.  wearing down rocks to use for healing minerals- DONE
* 
* purifying aura, Suicune Ability similar effect to healer, also mon removes all status effects on itself & allies at the end of turn
* in doubles heals status of ally on switchin as well. -DONE need test
* 
* BUFF for Golisopod Emergency Exit, rather than it being the same as wimp out,
* keep main effect but tweak it to be more offensive instead of force switch on hp threshold.
* make it so you do a hit and run attack on your next turn.
* Upon reaching switch threshold, your next move gets boosted priority  (possibly make new status for it? like focus energy?)
* to guarantee goes first, similar to pursuit but lower, and then you switch out after attacking.
* 
* This gives multiple new avenus of use, can better plan your switch, have a chance to knock out the enemy,
* giving you a free switch, and just overall allows you to actually get some value out of the ability
* 
* Concept is hurt and decide to run, but you full force steal off on the enemy to get the last lick in.
* Think, may raise attack one stage as well? can do like strength should work fine.
* 
* consider make leech seed work like anime, where it wraps up the target
* meaning it would be a trap, preventing the enemy from switching, and a good buff to grass types
* as only they learn it, and only theye are immune to it. -
* 
*/


/* new megas won't have +100bst but instead will take a stat average value that is strong
* like say 615 or 630/635.  and will either reallocate or add to existing stats to get there.
* 
* most legendaries have base 600, and then others go up to 680  psuedo legends are also 600
* 
* mega marowak should have higher defenses (sp def too  since its armor can take most things) atk & bulk
* 
* rework existing megas stats by this standard -
* 
* also remember plan for new version of megas, instead of a temp buff, it'll be a special difficult to acvhive but permanent evolution
* you can have more than one mega on your team but it'll just be much harder to get them to mega evolve,
* and also you'll only be able to have a single mon of that species to mega evolve,  thing of it like ash greninja
* a mon you have a very deep bond with you go through trials with to be able to evolve stronger.
* 
* So you have to decide which mon you will go through the mega trials with, even breeding specifically for that in mind
* if you want the best possible outcome.
* 
* Don't forget plans to revamp breeding mechanics, using as a menes to get alternate forms
* people don't often use it anyway so may potentially get rid of egg groups, if skitty wailord works it can't make too much logic.
* will make breeding easier and remove some of the need to use ditto exclusively
* 
* other idea, be able to access pc from breeder desk selection, to remove need to go to pc and put
* mon in your party JUST to put them in the daycare. major time saver and convience feature
*  
* Consider increasing day care from 2 mons to 6, i.e 3 pairs of mon can be put in at a time.
* do some menu work and logic work so there are 3 plots/sections of the day care
* each plot/slot is treated separately and can house 2 mon that would be a breeding pair.
* 
* that way you can generate 3 eggs at a time. 
* and with inclusion of the opal egg incubator,  egg management would be FAR more efficient
* 
*/
goto TRAINER_MEMO_SUMMARY	//pokemon_summary_screen.c, scroll down for trainer memo functions
goto SUMMARY_GRAPHICS //graphics.c all graphic files, but this spot is for summary screen

goto MOVEICON_ABILITYDESC	//function for displaying move icons & ability info in summ screen
/* 
* Upgrade UI menu for new mechanics. Expanded move description & ability description & move name fields
* Adjusted summary screen menu for trainer memo, &\ move summary/info page.
* Need to find a fix for move icons misalignment in moves pags 
* rquires direct editing the tilemap to fit the icons/tiles - DONE
* 
* also move learn slot is not wide enough long moves in move learn slot get cut off - DONE
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
* new effect calling it, jack of all trades  and gives reason to want normal as secondary type  25% non normal type damage buff
*/ 


goto PICKUP_LOGIC   //out of battle buffs done, moving to in battle buffs - need fix sets item but isn't random currently only setting stick?
goto SPECIAL_TRAP_EFFECTCHANCE
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
* fix moves mirror move, copycat etc. sketch monotype to use lasthitby  value, rather than enemy or last used move for target, so it doesnt fail
* if used first. -_-
* gBattleResults.lastUsedMoveOpponent       gLastMoves[gBattlerTarget] instead 
* adjusted copycat, sketch seems to already work optimally, mirror move is very complex for some reason will need to take time to study
* also note monotype will take sketch place,   sketch will essentially be mirror move +
* 
* smeargle changes new moves -
* stat boosts, and change sketch to temporary move copy
* similar to ditto's transform, move is replaced for duration of battle, and pp is updated after
* moved copycat original effect to new move monotype
* change sketch to raise all stats 2 levels or all but speed stat?
* this way it can overcome the disadvantage of using another mons move with worse stats, and without type advanage.
* that way smeargle is turned from a failed artist, into a type of sevant that can improve on the original.
* increased priority of sketch, so I'll not increase speed stat
* 
* //since I'm changing sketches effect to be temporary
    //and the current move has outside battle uses.
    //I think what I'll do is copy the current effect
    //and move it to another move I'll call
    //"hard copy" or something.

    //that move can be relearnabe to pick a moveset
    //and keep the 1pp thing.

    //ok I've decided I'll call it "Monotype" from the one-time art
    //print process 
* 
* buff to make magma armor unique, rather than just naother flame body (specially since I gave flame body freeze immunity
* first idea is give it incinerate effect, where it destroys enemy held item on contact
* othre idea is sp def damage reduction from being surrounded in magma shield
* based on bulbapdia reading make function for if item can be removed/stolen
* 
* buff pidgey line, according to Zen Mode YT changes, give u-turn and my move dive bomb
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
//so guess I'll edit that       -look over and reconsider this

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