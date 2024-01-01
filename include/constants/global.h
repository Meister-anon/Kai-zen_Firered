#ifndef GUARD_CONSTANTS_GLOBAL_H
#define GUARD_CONSTANTS_GLOBAL_H


#define ITEM_NAME_LENGTH 18
#define POKEMON_NAME_LENGTH 11 //remember set back to 12 //will break save data
#define OT_NAME_LENGTH 7    //player name length
#define MOVE_NAME_LENGTH 16 //longest move name is 16 

#define TYPE_NAME_LENGTH 6 //forgot change back as I undid type name expansion
#define ABILITY_NAME_LENGTH 16 //is 16 in emerald may look into raising - DONE
#define ABILITY_DESCRIPTION_LENGTH 82   //two lines 41 chars per line
#define MOVE_DESCRIPTION_LENGTH 114  //approx 19 per line, over 6 lines

#define VERSION_SAPPHIRE    1
#define VERSION_RUBY        2
#define VERSION_EMERALD     3
#define VERSION_FIRE_RED    4
#define VERSION_LEAF_GREEN  5

#define LANGUAGE_JAPANESE   1
#define LANGUAGE_ENGLISH    2
#define LANGUAGE_FRENCH     3
#define LANGUAGE_ITALIAN    4
#define LANGUAGE_GERMAN     5
    // 6 goes unused but the theory is it was meant to be Korean
#define LANGUAGE_SPANISH    7

#ifdef ENGLISH
#define GAME_LANGUAGE (LANGUAGE_ENGLISH)
#endif

#define PC_ITEMS_COUNT      30
#define BAG_ITEMS_COUNT     52
#define BAG_KEYITEMS_COUNT  50
#define BAG_POKEBALLS_COUNT 13  //double check how many poke ball types i have
#define BAG_TMHM_COUNT      128 //brocks gym battle crashes, when giving tm & badge, maybe not having an accurate count was the problem. nope that isn't a problem, 
#define BAG_BERRIES_COUNT   23 //that didn't solve it , but I think it did improve it.
#define OBJECT_EVENT_TEMPLATES_COUNT 64

#define QUEST_LOG_SCENE_COUNT 2 //think this is flashbacks, cut from 4 to 2, to hopefully save space. plus everyone doesn't like the feature like I do.

#define NUM_TOWER_CHALLENGE_TYPES 4

#define MALE   0
#define FEMALE 1
#define GENDER_COUNT 2

#define BARD_SONG_LENGTH       6
#define NUM_STORYTELLER_TALES  4
#define NUM_TRADER_ITEMS       4

#define OPTIONS_BUTTON_MODE_HELP         0 //may make only L call help, & use select, R, & start for ev iv screen. may use for alt ev/iv screen,the one from modexe
#define OPTIONS_BUTTON_MODE_LR           1 //new default for change, for iv ev status, actually may change that.
#define OPTIONS_BUTTON_MODE_L_EQUALS_A   2// i think modexe ev/iv thing is actually just adding menu and printing evs onto pokemon diploma image
// since I realize print will display text on whatever baground image you chose, the modexe thing is probably asm that tells the 
//rom where to print, and what values to print, onto what image.

#define OPTIONS_TEXT_SPEED_SLOW  0
#define OPTIONS_TEXT_SPEED_MID   1
#define OPTIONS_TEXT_SPEED_FAST  2 //new default
//new idea replace slow no one uses that. speeds will be mid/fast/faster
//according to luckytypholosion from pret instant text speed would be too fast and cause people to too easily skip text
//he believes a text speed that is 2-3 characters per frame would be best,  the basic speed of fast is 1 char per frame.
//I will attempt to make this new text speed and also include an instant option,
//as I want to optimze game progression/movement so emulator speed up isn't necessary.
//this includes a look at test speed, move speed, and animation speed, to bring the game up to a more modern standard.
//while still giving people a comfortable experience, because pokemon is a comfort game it doesn't need to be light speed constantly.

#define OPTIONS_SOUND_MONO    0
#define OPTIONS_SOUND_STEREO  1

#define OPTIONS_BATTLE_STYLE_SHIFT  0 //need to remove opponent pokemon alert from shift.  DONE!
#define OPTIONS_BATTLE_STYLE_SET    1

#define POCKET_ITEMS        1
#define POCKET_KEY_ITEMS    2
#define POCKET_POKE_BALLS   3
#define POCKET_TM_CASE      4
#define POCKET_BERRY_POUCH  5

#define ITEMS_POCKET       0
#define BALLS_POCKET       1
#define TMHM_POCKET        2
#define BERRIES_POCKET     3
#define KEYITEMS_POCKET    4
#define NUM_BAG_POCKETS 5   //plan add medicine pouch/field item pouch for things like repel revives potions etc. so items doesn't get as cluttered

#define MAX_MON_MOVES 4
#define NUM_EV_STATS 6

#define TRAINER_ID_LENGTH 4
#define PARTY_SIZE 6
#define MULTI_PARTY_SIZE (PARTY_SIZE / 2)

#define DIR_NONE        0
#define DIR_SOUTH       1
#define DIR_NORTH       2
#define DIR_WEST        3
#define DIR_EAST        4
#define DIR_SOUTHWEST   5
#define DIR_SOUTHEAST   6
#define DIR_NORTHWEST   7
#define DIR_NORTHEAST   8

#endif //GUARD_CONSTANTS_GLOBAL_H
