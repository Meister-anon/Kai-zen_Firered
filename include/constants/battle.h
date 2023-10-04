#ifndef GUARD_CONSTANTS_BATTLE_H
#define GUARD_CONSTANTS_BATTLE_H

#include "battle_move_effects.h"

/*
 * A battler may be in one of four positions on the field. The first bit determines
 * what side the battler is on, either the player's side or the opponent's side.
 * The second bit determines what flank the battler is on, either the left or right.
 * Note that the opponent's flanks are drawn corresponding to their perspective, so
 * their right mon appears on the left, and their left mon appears on the right.
 * The battler ID is usually the same as the position, except in the case of link battles.
 *
 *   + ------------------------- +
 *   |           Opponent's side |
 *   |            Right    Left  |
 *   |              3       1    |
 *   |                           |
 *   | Player's side             |
 *   |  Left   Right             |
 *   |   0       2               |
 *   ----------------------------+
 *   |                           |
 *   |                           |
 *   +---------------------------+
 */

#define MAX_BATTLERS_COUNT  4

 //battler positions for gbattlerpostions
#define B_POSITION_PLAYER_LEFT        0
#define B_POSITION_OPPONENT_LEFT      1	//read from back of enemy, oponent left is right from player view
#define B_POSITION_PLAYER_RIGHT       2
#define B_POSITION_OPPONENT_RIGHT     3	//read from back of enemy, oponent right is left from player view

// These macros can be used with either battler ID or positions to get the partner or the opposite mon
#define BATTLE_OPPOSITE(id) ((id) ^ 1)
#define BATTLE_PARTNER(id) ((id) ^ 2)

#define B_SIDE_PLAYER     0
#define B_SIDE_OPPONENT   1
#define NUM_BATTLE_SIDES  2

#define B_FLANK_LEFT 0
#define B_FLANK_RIGHT 1

#define BIT_SIDE        1
#define BIT_FLANK       2

// Battle Type Flags
#define BATTLE_TYPE_DOUBLE           0x0001 //relized this was used as 1 for double value in trainers.h because it lined up with this for gbattletypeflags, its the actual value, 0 is no flags so just default single I guess
#define BATTLE_TYPE_LINK             0x0002
#define BATTLE_TYPE_IS_MASTER        0x0004 // In not-link battles, it's always set.
#define BATTLE_TYPE_TRAINER          0x0008
#define BATTLE_TYPE_FIRST_BATTLE     0x0010
#define BATTLE_TYPE_ROTATION         0x0020     
#define BATTLE_TYPE_TRIPLE           0x0040     
#define BATTLE_TWO_VS_ONE_PLAYER     0x0080 //planned but yet to do
#define BATTLE_TYPE_BATTLE_TOWER     0x0100 //last value for u8 size, so if want use this for trainer set in trainers, would need all relevant battle types below this...
#define BATTLE_TYPE_OLD_MAN_TUTORIAL 0x0200 //checked and can move all others, without issue, trainer battle type is only one that uses u8 value all else is u32
#define BATTLE_TYPE_ROAMER           0x0400
#define BATTLE_TYPE_EREADER_TRAINER  0x0800	//remove this, so I can replace it.
#define BATTLE_TYPE_KYOGRE_GROUDON   0x1000
#define BATTLE_TYPE_LEGENDARY        0x2000
#define BATTLE_TYPE_GHOST_UNVEILED   0x2000 // Re-use of BATTLE_TYPE_LEGENDARY, when combined with BATTLE_TYPE_GHOST
#define BATTLE_TYPE_SAFARI           0x4000 //no using regi can replace this
#define BATTLE_TYPE_GHOST            0x8000
#define BATTLE_TYPE_POKEDUDE         0x10000
#define BATTLE_TYPE_WILD_SCRIPTED    0x20000
#define BATTLE_TYPE_LEGENDARY_FRLG   0x40000
#define BATTLE_TYPE_TRAINER_TOWER    0x80000
#define BATTLE_TYPE_20               0x100000   //this appears to be for link battle?   /renmae to link at some point will eventually remove these 2
#define BATTLE_TYPE_MULTI            0x200000   //multi link battle?  swapped these 2 placement, so could use incldues for trainers.h battle type setting
#define BATTLE_TYPE_INGAME_PARTNER   0x400000
#define BATTLE_TYPE_TWO_OPPONENTS    0x800000	//carry over from emerald, not used here but is reason for gTrainerBattleOpponent_B  when 2 trainers approach player
#define BATTLE_TYPE_RECORDED         0x1000000  //also not used, or wont be
#define BATTLE_TYPE_x2000000         0x2000000
#define BATTLE_TYPE_x4000000         0x4000000
#define BATTLE_TYPE_SECRET_BASE      0x8000000
#define BATTLE_TYPE_GROUDON          0x10000000
#define BATTLE_TYPE_KYOGRE           0x20000000
#define BATTLE_TYPE_RAYQUAZA         0x40000000
#define BATTLE_TYPE_x80000000        0x80000000

#define IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && !((flags) & BATTLE_TYPE_GHOST_UNVEILED))
#define IS_BATTLE_TYPE_GHOST_WITH_SCOPE(flags) ((flags) & BATTLE_TYPE_GHOST && (flags) & BATTLE_TYPE_GHOST_UNVEILED)

#define RIVAL_BATTLE_HEAL_AFTER  1
#define RIVAL_BATTLE_TUTORIAL    3

#define WILD_DOUBLE_BATTLE ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER))))
#define BATTLE_TWO_VS_ONE_OPPONENT ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && gTrainerBattleOpponent_B == 0xFFFF))
#define BATTLE_TYPE_HAS_AI          (BATTLE_TYPE_TRAINER | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_SAFARI | BATTLE_TYPE_ROAMER | BATTLE_TYPE_INGAME_PARTNER)


// Battle Outcome defines
#define B_OUTCOME_WON                  0x1
#define B_OUTCOME_LOST                 0x2
#define B_OUTCOME_DREW                 0x3
#define B_OUTCOME_RAN                  0x4
#define B_OUTCOME_PLAYER_TELEPORTED    0x5
#define B_OUTCOME_MON_FLED             0x6
#define B_OUTCOME_CAUGHT               0x7
#define B_OUTCOME_NO_SAFARI_BALLS      0x8
#define B_OUTCOME_FORFEITED            0x9
#define B_OUTCOME_MON_TELEPORTED       0xA
#define B_OUTCOME_LINK_BATTLE_RAN      0x80

// Non-volatile status conditions
// These persist remain outside of battle and after switching out
/*#define STATUS1_NONE             0x0
#define STATUS1_SLEEP            0x7
#define STATUS1_POISON           0x8
#define STATUS1_BURN             0x10
#define STATUS1_FREEZE           0x20
#define STATUS1_PARALYSIS        0x40
#define STATUS1_SPIRIT_LOCK      0x60
#define STATUS1_TOXIC_POISON     0x80		//remembered need change toxic, so it still toxic on switch out
#define STATUS1_TOXIC_COUNTER    0xF00		//idea change pokemon summary box from red to black to show dead ... play the runescape death music   XD
#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_SPIRIT_LOCK | STATUS1_TOXIC_POISON)

// Volatile status ailments
// These are removed after exiting the battle or switching out
#define STATUS2_CONFUSION             0x00000007
#define STATUS2_CONFUSION_TURN(num)   ((num) << 0)	//ported, just used to label confusion function, always followed by ((Random()) % 4) + 2)
#define STATUS2_FLINCHED              0x00000008
#define STATUS2_UPROAR                0x00000070
#define STATUS2_BIDE                  0x00000300  // two bits 0x100, 0x200
#define STATUS2_LOCK_CONFUSE          0x00000C00
#define STATUS2_MULTIPLETURNS         0x00001000
#define STATUS2_WRAPPED               0x0000E000
#define STATUS2_POWDER                (1 << 14)
#define STATUS2_INFATUATION           0x000F0000  // 4 bits, one for every battler
#define STATUS2_INFATUATED_WITH(battler) (gBitTable[battler] << 16)
#define STATUS2_FOCUS_ENERGY          0x00100000
#define STATUS2_TRANSFORMED           0x00200000
#define STATUS2_RECHARGE              0x00400000
#define STATUS2_RAGE                  0x00800000
#define STATUS2_SUBSTITUTE            0x01000000
#define STATUS2_DESTINY_BOND          0x02000000
#define STATUS2_ESCAPE_PREVENTION     0x04000000
#define STATUS2_NIGHTMARE             0x08000000
#define STATUS2_CURSED                0x10000000
#define STATUS2_FORESIGHT             0x20000000
#define STATUS2_DEFENSE_CURL          0x40000000
#define STATUS2_TORMENT               0x80000000*/

// Non-volatile status conditions
// These persist remain outside of battle and after switching out
#define STATUS1_NONE             0
#define STATUS1_SLEEP            (1 << 0 | 1 << 1 | 1 << 2) // First 3 bits (Number of turns to sleep)
#define STATUS1_SLEEP_TURN(num)  ((num) << 0) // Just for readability (or if rearranging statuses)
#define STATUS1_POISON           (1 << 3)
#define STATUS1_BURN             (1 << 4)
#define STATUS1_FREEZE           (1 << 5)
#define STATUS1_PARALYSIS        (1 << 6)
#define STATUS1_TOXIC_POISON     (1 << 7)
#define STATUS1_TOXIC_COUNTER    (1 << 8 | 1 << 9 | 1 << 10 | 1 << 11)
#define STATUS1_TOXIC_TURN(num)  ((num) << 8)
#define STATUS1_SPIRIT_LOCK      (1 << 12)	//redid toxic, put at original value, moved others
#define STATUS1_SNAP_TRAP		 (1 << 13)	//check status 1 effect for permanent status clear	pretty sure defaults to <= 6
#define STATUS1_FIRE_SPIN		 (1 << 14)
#define STATUS1_CLAMP			 (1 << 15)
#define STATUS1_WHIRLPOOL		 (1 << 16)
#define STATUS1_SAND_TOMB		 (1 << 17)
#define STATUS1_MAGMA_STORM		 (1 << 18)
#define STATUS1_INFESTATION		 (1 << 19)
#define STATUS1_WRAPPED			 (1 << 20)

#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
//will need to go through and review all use of this variable since I've expanded status1
//laso cean up status definex

//status1_any seeems tobe used to check all status1 but exclude toxic counter values & sleep counter
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON)

#define STATUS1_ENVIRONMENT_TRAP (STATUS1_FIRE_SPIN || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM)

#define ITS_A_TRAP_STATUS1 (STATUS1_SNAP_TRAP || STATUS1_FIRE_SPIN || STATUS1_CLAMP || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM || STATUS1_INFESTATION || STATUS1_WRAPPED)

// Volatile status ailments
// These are removed after exiting the battle or switching out
//from what I see game is only set up to display status animations for status 1 & status2 staus...but then leech seed works and its status3?
#define STATUS2_CONFUSION             (1 << 0 | 1 << 1 | 1 << 2)
#define STATUS2_CONFUSION_TURN(num)   ((num) << 0)
#define STATUS2_FLINCHED              (1 << 3)
#define STATUS2_UPROAR                (1 << 4 | 1 << 5 | 1 << 6)
#define STATUS2_UPROAR_TURN(num)      ((num) << 4)
#define STATUS2_EMERGENCY_EXIT         (1 << 7)	//use for emergency exit
#define STATUS2_BIDE                  (1 << 8 | 1 << 9)
#define STATUS2_BIDE_TURN(num)        (((num) << 8) & STATUS2_BIDE)
#define STATUS2_LOCK_CONFUSE          (1 << 10 | 1 << 11) // e.g. Thrash
#define STATUS2_LOCK_CONFUSE_TURN(num)((num) << 10)
#define STATUS2_MULTIPLETURNS         (1 << 12) //wrapped is wrap & bide
#define STATUS2_WRAPPED               (1 << 13)	//make individual wrapped for each, but all use same wrap turn counter
//#define STATUS2_WRAPPED_TURN(num)     ((num) << 13)	//left shift value is starting point of status wrapped
#define STATUS2_POWDER                (1 << 14)
#define STATUS2_INFATUATION           (1 << 16 | 1 << 17 | 1 << 18 | 1 << 19)  // 4 bits, one for every battler
#define STATUS2_INFATUATED_WITH(battler) (gBitTable[battler] << 16)
#define STATUS2_FOCUS_ENERGY          (1 << 20)
#define STATUS2_TRANSFORMED           (1 << 21)
#define STATUS2_RECHARGE              (1 << 22)
#define STATUS2_RAGE                  (1 << 23)
#define STATUS2_SUBSTITUTE            (1 << 24)
#define STATUS2_DESTINY_BOND          (1 << 25)
#define STATUS2_ESCAPE_PREVENTION     (1 << 26)
#define STATUS2_NIGHTMARE             (1 << 27)
#define STATUS2_CURSED                (1 << 28)
#define STATUS2_FORESIGHT             (1 << 29)
#define STATUS2_DEFENSE_CURL          (1 << 30)
#define STATUS2_TORMENT               (1 << 31)	//ok updated from current firered thought would let me have more status
//but realized its u32  cant go higher than 31, either make new status type or replace existing
//haev 2 extra spaces now

// Seems like per-battler statuses. Not quite sure how to categorize these
//#define STATUS3_SKY_DROPPED             0x1 // Target of Sky Drop
#define STATUS3_LEECHSEED_BATTLER       (1 << 0 | 1 << 1) // The battler to receive HP from Leech Seed
#define STATUS3_LEECHSEED                (1 << 2)
#define STATUS3_ALWAYS_HITS             (1 << 3 | 1 << 4)    // two bits
#define STATUS3_ALWAYS_HITS_TURN(num)   (((num) << 3) & STATUS3_ALWAYS_HITS) // "Always Hits" is set as a 2 turn timer, i.e. next turn is the last turn when it's active
#define STATUS3_PERISH_SONG             (1 << 5)
#define STATUS3_ON_AIR                  (1 << 6)
#define STATUS3_UNDERGROUND             (1 << 7)
#define STATUS3_MINIMIZED               (1 << 8)
#define STATUS3_CHARGED_UP              (1 << 9)
#define STATUS3_ROOTED                  (1 << 10) //if I understand correctly, change gives extra statur 3 space 12 would be unused
#define STATUS3_YAWN                    (1 << 11) // Number of turns to sleep
//#define STATUS3_YAWN_TURN(num)          (((num) << 11) & STATUS3_YAWN)  changing set status yawn, then at end turn check for it, if there remove and put to sleep
#define STATUS3_IMPRISONED_OTHERS       (1 << 13)
#define STATUS3_GRUDGE                  (1 << 14)
#define STATUS3_CANT_SCORE_A_CRIT       (1 << 15)
//#define STATUS3_MUDSPORT                (1 << 16)	//can move these 2 to side status?
//#define STATUS3_WATERSPORT              0x20000	//(1 << 17) //remove sports later
#define STATUS3_UNDERWATER              (1 << 18)
#define STATUS3_INTIMIDATE_POKES        (1 << 19)
#define STATUS3_TRACE                   (1 << 20)
#define STATUS3_ROOTED_SHIFT (21)
#define STATUS3_ROOTED_COUNTER (0xF << STATUS3_ROOTED_SHIFT)
#define STATUS3_ROOTED_TURN(num) ((num) << STATUS3_ROOTED_SHIFT)


#define STATUS3_GASTRO_ACID             (1 << 16)	//is there any reaso this needs to be status3 rather than a status 2?
//#define STATUS3_EMBARGO                 (1 << 17)	//move to side status to make room
#define STATUS3_SMACKED_DOWN            (1 << 17)
#define STATUS3_ME_FIRST                (1 << 22)//check make sure this doesn't cause issues with ingrain
#define STATUS3_TELEKINESIS             (1 << 23)
#define STATUS3_PHANTOM_FORCE           (1 << 24)
#define STATUS3_MIRACLE_EYED            (1 << 25)
#define STATUS3_MAGNET_RISE             (1 << 26)
#define STATUS3_AQUA_RING               (1 << 27)
#define STATUS3_LASER_FOCUS             (1 << 28)
#define STATUS3_TIGER_MOM_ATTACKS       (1 << 29)
#define STATUS3_POWER_TRICK             (1 << 30)
#define STATUS3_SKY_DROPPED				(1 << 31) //will be side affecting, this just for first turn effects,  change move to target both to match intentions
//#define STATUS3_HEAL_BLOCK				(1 << 31) //will be side affecting, this just for first turn effects,  change move to target both to match intentions

#define STATUS3_SEMI_INVULNERABLE       (STATUS3_UNDERGROUND | STATUS3_ON_AIR | STATUS3_UNDERWATER | STATUS3_PHANTOM_FORCE)

//signature of heliolisk, for move electrify
//similar to plasma fist effect but for target
#define STATUS4_ELECTRIFIED             (1 << 0)	//need to check how status4 is setup to make sure it runs on same conditions as status2
#define STATUS4_PLASMA_FISTS            (1 << 1)	//if it works I can move wrap status and wrap counter up here so it all uses status4
#define STATUS4_FIRE_SPIN				(1 << 2)
#define STATUS4_CLAMP					(1 << 3)
#define STATUS4_WHIRLPOOL				(1 << 4)
#define STATUS4_SAND_TOMB				(1 << 5)
#define STATUS4_MAGMA_STORM				(1 << 6)
#define STATUS4_INFESTATION				(1 << 7)

//was able to save great amount of space with emerald upgrades
//but now dont have separate counter for each status
//I could make one without issue by adding to disable struct
//but further thought it doesnt make sense for most of the status
//to interact since they are environment based.
//only ones that make sense are clamp, infestation & snaptrap

//hmm keep that in mind for later,
//2 types of traps environment vs physical, where physical has separate wrap timer & can stack

//statuses for traps together forgot can't do this  since not all  .status2
//#define ITS_A_TRAP_STATUS (STATUS2_WRAPPED | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_MAGMA_STORM | STATUS4_INFESTATION)

#define STATUS4_ENVIRONMENT_TRAP (STATUS4_FIRE_SPIN || STATUS4_WHIRLPOOL || STATUS4_SAND_TOMB || STATUS4_MAGMA_STORM)

#define STATUS4_PHYSICAL_TRAP (STATUS4_CLAMP || STATUS4_INFESTATION) //summary you get 1 environment trap and as many physical traps as you want

//trap statuses not immune to floating enemies
//#define ITS_A_TRAP_STATUS_2 (STATUS2_WRAPPED | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_INFESTATION)

//temp just the status4 stuff		//OK so status4 not currently used in battle? its not in BattlePokemon struct need add and investigate
#define ITS_A_TRAP_STATUS4 (STATUS4_FIRE_SPIN || STATUS4_CLAMP || STATUS4_WHIRLPOOL || STATUS4_SAND_TOMB || STATUS4_MAGMA_STORM || STATUS4_INFESTATION)

//effects for traps together //move data used in battle_moves_effects.h  each needs own battlescript
#define ITS_A_TRAP (EFFECT_TRAP || EFFECT_FIRE_SPIN || EFFECT_CLAMP || EFFECT_WHIRLPOOL || EFFECT_SAND_TOMB || EFFECT_MAGMA_STORM || EFFECT_SNAP_TRAP)

#define GROUND_TRAPS (EFFECT_TRAP || EFFECT_FIRE_SPIN || EFFECT_CLAMP || EFFECT_WHIRLPOOL || EFFECT_SAND_TOMB || EFFECT_SWARM || EFFECT_SNAP_TRAP)

// Not really sure what a "hitmarker" is.
#define HITMARKER_WAKE_UP_CLEAR         (1 << 4)	//// Cleared when waking up. Never set or checked.
#define HITMARKER_SKIP_DMG_TRACK        (1 << 5)
#define HITMARKER_DESTINYBOND           (1 << 6)
#define HITMARKER_NO_ANIMATIONS         (1 << 7)
#define HITMARKER_IGNORE_SUBSTITUTE     (1 << 8)
#define HITMARKER_NO_ATTACKSTRING       (1 << 9)
#define HITMARKER_ATTACKSTRING_PRINTED  (1 << 10)
#define HITMARKER_NO_PPDEDUCT           (1 << 11)
#define HITMARKER_SWAP_ATTACKER_TARGET  (1 << 12)
#define HITMARKER_IGNORE_SAFEGUARD      (1 << 13)
#define HITMARKER_SYNCHRONIZE_EFFECT    (1 << 14)
#define HITMARKER_RUN                   (1 << 15)
#define HITMARKER_IGNORE_DISGUISE       (1 << 16)
//#define HITMARKER_IGNORE_ON_AIR         0x00010000 //remove later
//#define HITMARKER_IGNORE_UNDERGROUND    0x00020000 //remove later
//#define HITMARKER_IGNORE_UNDERWATER     0x00040000 //remove later
// 3 free spots because of change in handling of UNDERGROUND/UNDERWATER/ON AIR
#define HITMARKER_UNABLE_TO_USE_MOVE    (1 << 19)
#define HITMARKER_PASSIVE_DAMAGE        (1 << 20)
#define HITMARKER_DISOBEDIENT_MOVE      (1 << 21)
#define HITMARKER_PLAYER_FAINTED        (1 << 22)
#define HITMARKER_ALLOW_NO_PP           (1 << 23)
#define HITMARKER_GRUDGE                (1 << 24)
#define HITMARKER_OBEYS                 (1 << 25)
#define HITMARKER_NEVER_SET             (1 << 26) // Cleared as part of a large group. Never set or checked
#define HITMARKER_CHARGING              (1 << 27)
#define HITMARKER_FAINTED(battler)      (gBitTable[battler] << 28)
#define HITMARKER_FAINTED2(battler)     ((1 << 28) << battler)	//removed hitmarker semi invul underground etc. can't go up to fainted2 value
#define HITMARKER_STRING_PRINTED        (1 << 29) //extra from emerald in case need

// Per-side statuses that affect an entire party
#define SIDE_STATUS_REFLECT					(1 << 0)
#define SIDE_STATUS_LIGHTSCREEN				(1 << 1)
#define SIDE_STATUS_STICKY_WEB				(1 << 2)
#define SIDE_STATUS_SPIKES					(1 << 4)
#define SIDE_STATUS_SAFEGUARD				(1 << 5)
#define SIDE_STATUS_FUTUREATTACK			(1 << 6)	//block fog shuold prevnt same as block burn/etc. dmg
#define SIDE_STATUS_MIST					(1 << 8)	//blocked by black fog
#define SIDE_STATUS_SPIKES_DAMAGED			(1 << 9)
#define SIDE_STATUS_TAILWIND                (1 << 10)	//unsure could have tail wind use do defog affect, remove mist & black fog
#define SIDE_STATUS_AURORA_VEIL             (1 << 11)
#define SIDE_STATUS_LUCKY_CHANT             (1 << 12)
#define SIDE_STATUS_TOXIC_SPIKES            (1 << 13)
#define SIDE_STATUS_STEALTH_ROCK            (1 << 14) //also prevented from dmg when black fog up
#define SIDE_STATUS_STEALTH_ROCK_DAMAGED    (1 << 15)
#define SIDE_STATUS_TOXIC_SPIKES_DAMAGED    (1 << 16)
#define SIDE_STATUS_STICKY_WEB_DAMAGED      (1 << 17)
#define SIDE_STATUS_QUICK_GUARD             (1 << 18)
#define SIDE_STATUS_WIDE_GUARD              (1 << 19)
#define SIDE_STATUS_CRAFTY_SHIELD           (1 << 20)
#define SIDE_STATUS_MAT_BLOCK               (1 << 21)
#define SIDE_STATUS_HEAL_BLOCK              (1 << 22)//need setup this & embargo  heal block side status is already setup I jusut forgot...
#define SIDE_STATUS_EMBARGO					(1 << 23)
#define SIDE_STATUS_MUDSPORT				(1 << 24)
#define SIDE_STATUS_WATERSPORT				(1 << 25)
#define SIDE_STATUS_MAGIC_COAT				(1 << 26)	//for magic coat buff make 3 turn, similar in effect to a screen, but 3 instead of 5 turns as it nullifies

#define SIDE_STATUS_HAZARDS_ANY    (SIDE_STATUS_SPIKES | SIDE_STATUS_STICKY_WEB | SIDE_STATUS_TOXIC_SPIKES | SIDE_STATUS_STEALTH_ROCK)
#define SIDE_STATUS_SCREEN_ANY     (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)

// Field affecting statuses.
#define STATUS_FIELD_MAGIC_ROOM         (1 << 0)
#define STATUS_FIELD_TRICK_ROOM        (1 << 1)
#define STATUS_FIELD_WONDER_ROOM        (1 << 2)
#define STATUS_FIELD_GRAVITY            (1 << 3)
//#define STATUS_FIELD_MUDSPORT           0x8  will try to keep these 2 in status3 because they didn't use a timer I can put them here and have them not use a timer as well.
//#define STATUS_FIELD_WATERSPORT         0x10
#define STATUS_FIELD_SCORCHED_TERRAIN   (1 << 4)	//make red version or new tile with scorched cracked earth appearane
#define STATUS_FIELD_FLOODED_TERRAIN    (1 << 5)	//can use surf tile/ or edit a blue puddle into normal graphic
#define STATUS_FIELD_OCEAN_TERRAIN      (1 << 6)	//for when surfing on ocean/deeper water /grass terrain & scorched terrain wouldn't work
#define STATUS_FIELD_GRASSY_TERRAIN     (1 << 7)	//longer grass
#define STATUS_FIELD_MISTY_TERRAIN      (1 << 8)	//mist/haze/defog -?? ooh this was to use the animation from those for field effect
#define STATUS_FIELD_ELECTRIC_TERRAIN   (1 << 9)	//sparks tag
#define STATUS_FIELD_PSYCHIC_TERRAIN    (1 << 10)	//could surround field w hidden power orbs?
#define STATUS_FIELD_SNOWY_TERRAIN		(1 << 11)	//for snow area
#define STATUS_FIELD_TERRAIN_PERMANENT  (1 << 12)		//last terrain effect so putting here //(1 << 12)   
#define STATUS_FIELD_ION_DELUGE         (1 << 13)
#define STATUS_FIELD_FAIRY_LOCK         (1 << 14)
#define STATUS_FIELD_BLACK_FOG          (1 << 15)	//HAZE -3 full turns so timer is 4
//#define STATUS_FIELD_MUDSPORT			(1 << 15) gonna put these in side status instead
//#define STATUS_FIELD_WATERSPORT         (1 << 16)

#define TERRAIN_DEFINES

#define STATUS_FIELD_TERRAIN_ANY              (STATUS_FIELD_SCORCHED_TERRAIN | STATUS_FIELD_FLOODED_TERRAIN | STATUS_FIELD_OCEAN_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN)

// Flags describing move's result
#define MOVE_RESULT_MISSED             (1 << 0)
#define MOVE_RESULT_SUPER_EFFECTIVE    (1 << 1)
#define MOVE_RESULT_NOT_VERY_EFFECTIVE (1 << 2)
#define MOVE_RESULT_DOESNT_AFFECT_FOE  (1 << 3)
#define MOVE_RESULT_ONE_HIT_KO         (1 << 4)
#define MOVE_RESULT_FAILED             (1 << 5)
#define MOVE_RESULT_FOE_ENDURED        (1 << 6)
#define MOVE_RESULT_FOE_HUNG_ON        (1 << 7)
#define MOVE_RESULT_STURDIED		   (1 << 8)
#define MOVE_RESULT_NO_EFFECT          (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_FAILED)

// Battle Weather as enum
#define ENUM_WEATHER_NONE			      0
#define ENUM_WEATHER_RAIN		          1
#define ENUM_WEATHER_SUN	              2
#define ENUM_WEATHER_SANDSTORM			  3
#define ENUM_WEATHER_HAIL				  4
#define ENUM_WEATHER_SUN_PRIMAL           5
#define ENUM_WEATHER_RAIN_PRIMAL          6
#define ENUM_WEATHER_STRONG_WINDS         7
//vsonic since added special status switchin done prob don't need now?
//think can just use that
#define REPEAT_SWITCH_IN            8
//hopefully to make macro for list of abilities
//to repeat on opponent switch in/send out


// Battle Weather flags
#define WEATHER_RAIN_TEMPORARY			(1 << 0)
#define WEATHER_RAIN_DOWNPOUR			(1 << 1)  // unused
#define WEATHER_RAIN_PERMANENT			(1 << 2)
#define WEATHER_RAIN_PRIMAL				(1 << 11)
#define WEATHER_RAIN_NON_TEMP			(WEATHER_RAIN_DOWNPOUR | WEATHER_RAIN_PERMANENT | WEATHER_RAIN_PRIMAL)	//excludes tmporary rain effects
#define WEATHER_RAIN_ANY				(WEATHER_RAIN_TEMPORARY | WEATHER_RAIN_DOWNPOUR | WEATHER_RAIN_PERMANENT | WEATHER_RAIN_PRIMAL)
#define WEATHER_SANDSTORM_TEMPORARY		(1 << 3)
#define WEATHER_SANDSTORM_PERMANENT		(1 << 4)
#define WEATHER_SANDSTORM_NON_TEMP		(WEATHER_SANDSTORM_PERMANENT)	//irrelevant unless add more sandstorm types
#define WEATHER_SANDSTORM_ANY			(WEATHER_SANDSTORM_TEMPORARY | WEATHER_SANDSTORM_PERMANENT)
#define WEATHER_SUN_TEMPORARY			(1 << 5)
#define WEATHER_SUN_PERMANENT			(1 << 6)
#define WEATHER_SUN_PRIMAL				(1 << 9)
#define WEATHER_SUN_NON_TEMP			(WEATHER_SUN_PERMANENT | WEATHER_SUN_PRIMAL)	//excludes temporary sun effects
#define WEATHER_SUN_ANY					(WEATHER_SUN_TEMPORARY | WEATHER_SUN_PERMANENT | WEATHER_SUN_PRIMAL)
#define WEATHER_HAIL					(1 << 7)
#define WEATHER_HAIL_PERMANENT			(1 << 8)
#define WEATHER_STRONG_WINDS			(1 << 10)
#define WEATHER_HAIL_NON_TEMP			(WEATHER_HAIL_PERMANENT)	//only relevant if add more hail types
#define WEATHER_HAIL_ANY				(WEATHER_HAIL | WEATHER_HAIL_PERMANENT)
#define WEATHER_ANY						(WEATHER_RAIN_ANY | WEATHER_SANDSTORM_ANY | WEATHER_SUN_ANY | WEATHER_HAIL_ANY)
#define WEATHER_PRIMAL_ANY				(WEATHER_RAIN_PRIMAL | WEATHER_SUN_PRIMAL | WEATHER_STRONG_WINDS)


// Battle terrain defines for gBattleTerrain.
#define BATTLE_TERRAIN_GRASS        0
#define BATTLE_TERRAIN_LONG_GRASS   1
#define BATTLE_TERRAIN_SAND         2
#define BATTLE_TERRAIN_UNDERWATER   3
#define BATTLE_TERRAIN_WATER        4
#define BATTLE_TERRAIN_POND         5
#define BATTLE_TERRAIN_MOUNTAIN     6
#define BATTLE_TERRAIN_CAVE         7
#define BATTLE_TERRAIN_BUILDING     8
#define BATTLE_TERRAIN_PLAIN        9
#define BATTLE_TERRAIN_LINK        10
#define BATTLE_TERRAIN_GYM         11
#define BATTLE_TERRAIN_LEADER      12
#define BATTLE_TERRAIN_INDOOR_2    13
#define BATTLE_TERRAIN_INDOOR_1    14
#define BATTLE_TERRAIN_LORELEI     15
#define BATTLE_TERRAIN_BRUNO       16
#define BATTLE_TERRAIN_AGATHA      17
#define BATTLE_TERRAIN_LANCE       18
#define BATTLE_TERRAIN_CHAMPION    19

// Return value for IsRunningFromBattleImpossible. 
#define BATTLE_RUN_SUCCESS        0
#define BATTLE_RUN_FORBIDDEN      1
#define BATTLE_RUN_FAILURE        2

//sub for wait time for battlescript
#define B_WAIT_TIME_LONG     0x40
#define B_WAIT_TIME_MED      0x30
#define B_WAIT_TIME_SHORT    0x20
#define B_WAIT_TIME_SHORTEST 0x10

// Window Ids for sTextOnWindowsInfo_Normal
#define B_WIN_MSG                 0
#define B_WIN_ACTION_PROMPT       1 // "What will {x} do?"
#define B_WIN_ACTION_MENU         2 // "Fight/Pok�mon/Bag/Run" menu
#define B_WIN_MOVE_NAME_1         3 // Top left
#define B_WIN_MOVE_NAME_2         4 // Top right
#define B_WIN_MOVE_NAME_3         5 // Bottom left
#define B_WIN_MOVE_NAME_4         6 // Bottom right
#define B_WIN_PP				  9	// pp symbol	B_WIN_PP_REMAINING
#define B_WIN_MOVE_TYPE           8 // name of selected move type
#define B_WIN_PP_REMAINING        7 // current & max pp values	B_WIN_PP
#define B_WIN_DUMMY              10
#define B_WIN_SWITCH_PROMPT      11 // "Switch which?"
#define B_WIN_LEVEL_UP_BOX       12
#define B_WIN_LEVEL_UP_BANNER    13
#define B_WIN_YESNO              14
#define B_WIN_VS_PLAYER          15
#define B_WIN_VS_OPPONENT        16
#define B_WIN_VS_MULTI_PLAYER_1  17
#define B_WIN_VS_MULTI_PLAYER_2  18
#define B_WIN_VS_MULTI_PLAYER_3  19
#define B_WIN_VS_MULTI_PLAYER_4  20
#define B_WIN_VS_OUTCOME_DRAW    21
#define B_WIN_VS_OUTCOME_LEFT    22
#define B_WIN_VS_OUTCOME_RIGHT   23
#define B_WIN_OAK_OLD_MAN        24

#define B_TEXT_FLAG_NPC_CONTEXT_FONT    (1 << 6)
#define B_TEXT_FLAG_WINDOW_CLEAR        (1 << 7)

// Constants for Parental Bond
#define PARENTAL_BOND_1ST_HIT 2
#define PARENTAL_BOND_2ND_HIT 1
#define PARENTAL_BOND_OFF     0

#endif // GUARD_CONSTANTS_BATTLE_H
