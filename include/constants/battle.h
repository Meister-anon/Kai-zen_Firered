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

#define B_POSITION_PLAYER_LEFT        0
#define B_POSITION_OPPONENT_LEFT      1
#define B_POSITION_PLAYER_RIGHT       2
#define B_POSITION_OPPONENT_RIGHT     3

// These macros can be used with either battler ID or positions to get the partner or the opposite mon
#define BATTLE_OPPOSITE(id) ((id) ^ 1)
#define BATTLE_PARTNER(id) ((id) ^ 2)

#define B_SIDE_PLAYER     0
#define B_SIDE_OPPONENT   1

#define B_FLANK_LEFT 0
#define B_FLANK_RIGHT 1

#define BIT_SIDE        1
#define BIT_FLANK       2

// Battle Type Flags
#define BATTLE_TYPE_DOUBLE           0x0001
#define BATTLE_TYPE_LINK             0x0002
#define BATTLE_TYPE_IS_MASTER        0x0004 // In not-link battles, it's always set.
#define BATTLE_TYPE_TRAINER          0x0008
#define BATTLE_TYPE_FIRST_BATTLE     0x0010
#define BATTLE_TYPE_20               0x0020
#define BATTLE_TYPE_MULTI            0x0040
#define BATTLE_TYPE_SAFARI           0x0080
#define BATTLE_TYPE_BATTLE_TOWER     0x0100
#define BATTLE_TYPE_OLD_MAN_TUTORIAL 0x0200
#define BATTLE_TYPE_ROAMER           0x0400
#define BATTLE_TYPE_EREADER_TRAINER  0x0800	//remove this, so I can replace it.
#define BATTLE_TYPE_KYOGRE_GROUDON   0x1000
#define BATTLE_TYPE_LEGENDARY        0x2000
#define BATTLE_TYPE_GHOST_UNVEILED   0x2000 // Re-use of BATTLE_TYPE_LEGENDARY, when combined with BATTLE_TYPE_GHOST
#define BATTLE_TYPE_REGI             0x4000
#define BATTLE_TYPE_GHOST            0x8000
#define BATTLE_TYPE_POKEDUDE         0x10000
#define BATTLE_TYPE_WILD_SCRIPTED    0x20000
#define BATTLE_TYPE_LEGENDARY_FRLG   0x40000
#define BATTLE_TYPE_TRAINER_TOWER    0x80000
#define BATTLE_TYPE_x100000          0x100000
#define BATTLE_TYPE_x200000          0x200000
#define BATTLE_TYPE_INGAME_PARTNER   0x400000
#define BATTLE_TYPE_TWO_OPPONENTS    0x800000	//carry over from emerald, not used here but is reason for gTrainerBattleOpponent_B  when 2 trainers approach player
#define BATTLE_TYPE_RECORDED         0x1000000
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
//#define BATTLE_TWO_VS_ONE_OPPONENT ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && gTrainerBattleOpponent_B == 0xFFFF))


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
#define STATUS1_SPIRIT_LOCK      (1 << 7)	//test if toxic still works fine
#define STATUS1_SNAP_TRAP		 (1 << 8)	//check status 1 effect for permanent status clear	pretty sure defaults to <= 6
#define STATUS1_FIRE_SPIN		 (1 << 9)
#define STATUS1_CLAMP			 (1 << 10)
#define STATUS1_WHIRLPOOL		 (1 << 11)
#define STATUS1_SAND_TOMB		 (1 << 12)
#define STATUS1_MAGMA_STORM		 (1 << 14)
#define STATUS1_INFESTATION		 (1 << 14)
#define STATUS1_WRAPPED			 (1 << 15)
#define STATUS1_TOXIC_POISON     (1 << 16)
#define STATUS1_TOXIC_COUNTER    (1 << 17 | 1 << 18 | 1 << 19 | 1 << 20)
#define STATUS1_TOXIC_TURN(num)  ((num) << 17)
#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON)

#define STATUS1_ENVIRONMENT_TRAP (STATUS1_FIRE_SPIN || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM)

#define ITS_A_TRAP_STATUS1 (STATUS1_SNAP_TRAP || STATUS1_FIRE_SPIN || STATUS1_CLAMP || STATUS1_WHIRLPOOL || STATUS1_SAND_TOMB || STATUS1_MAGMA_STORM || STATUS1_INFESTATION || STATUS1_WRAPPED)

// Volatile status ailments
// These are removed after exiting the battle or switching out
#define STATUS2_CONFUSION             (1 << 0 | 1 << 1 | 1 << 2)
#define STATUS2_CONFUSION_TURN(num)   ((num) << 0)
#define STATUS2_FLINCHED              (1 << 3)
#define STATUS2_UPROAR                (1 << 4 | 1 << 5 | 1 << 6)
#define STATUS2_UPROAR_TURN(num)      ((num) << 4)
#define STATUS2_UNUSED                (1 << 7)
#define STATUS2_BIDE                  (1 << 8 | 1 << 9)
#define STATUS2_BIDE_TURN(num)        (((num) << 8) & STATUS2_BIDE)
#define STATUS2_LOCK_CONFUSE          (1 << 10 | 1 << 11) // e.g. Thrash
#define STATUS2_LOCK_CONFUSE_TURN(num)((num) << 10)
#define STATUS2_MULTIPLETURNS         (1 << 12) 
#define STATUS2_WRAPPED               (1 << 13)	//make individual wrapped for each, but all use same wrap turn counter
//#define STATUS2_WRAPPED_TURN(num)     ((num) << 13)	//left shift value is starting point of status wrapped
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
//but realized its u32 so possibly may need to upgrade to u64? if even possible to hvae more status 2
//haev 2 extra spaces now

// Seems like per-battler statuses. Not quite sure how to categorize these
#define STATUS3_SKY_DROPPED             0x1 // Target of Sky Drop
#define STATUS3_LEECHSEED_BATTLER       0x3
#define STATUS3_LEECHSEED               0x4
#define STATUS3_ALWAYS_HITS             0x18    // two bits
#define STATUS3_PERISH_SONG             0x20
#define STATUS3_ON_AIR                  0x40
#define STATUS3_UNDERGROUND             0x80
#define STATUS3_MINIMIZED               0x100
#define STATUS3_ROOTED                  0x400
#define STATUS3_CHARGED_UP              0x200
#define STATUS3_YAWN                    0x1800  // two bits
#define STATUS3_IMPRISONED_OTHERS       0x2000
#define STATUS3_GRUDGE                  0x4000
#define STATUS3_CANT_SCORE_A_CRIT       0x8000
#define STATUS3_MUDSPORT                0x10000
#define STATUS3_WATERSPORT              0x20000
#define STATUS3_UNDERWATER              0x40000
#define STATUS3_INTIMIDATE_POKES        0x80000
#define STATUS3_TRACE                   0x100000
#define STATUS3_ROOTED_SHIFT (21)
#define STATUS3_ROOTED_COUNTER (0xF << STATUS3_ROOTED_SHIFT)
#define STATUS3_ROOTED_TURN(num) ((num) << STATUS3_ROOTED_SHIFT)
#define STATUS3_SEMI_INVULNERABLE       (STATUS3_UNDERGROUND | STATUS3_ON_AIR | STATUS3_UNDERWATER)

#define STATUS3_GASTRO_ACID             (1 << 16)
#define STATUS3_EMBARGO                 (1 << 17)
#define STATUS3_SMACKED_DOWN            (1 << 21)
#define STATUS3_ME_FIRST                (1 << 22)
#define STATUS3_TELEKINESIS             (1 << 23)
#define STATUS3_PHANTOM_FORCE           (1 << 24)
#define STATUS3_MIRACLE_EYED            (1 << 25)
#define STATUS3_MAGNET_RISE             (1 << 26)
#define STATUS3_HEAL_BLOCK              (1 << 27)
#define STATUS3_AQUA_RING               (1 << 28)
#define STATUS3_LASER_FOCUS             (1 << 29)
#define STATUS3_ELECTRIFIED             (1 << 30)
#define STATUS3_POWER_TRICK             (1 << 31)

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
#define ITS_A_TRAP_STATUS_2 (STATUS2_WRAPPED | STATUS4_FIRE_SPIN | STATUS4_CLAMP | STATUS4_WHIRLPOOL | STATUS4_SAND_TOMB | STATUS4_INFESTATION)

//temp just the status4 stuff		//OK so status4 not currently used in battle? its not in BattlePokemon struct need add and investigate
#define ITS_A_TRAP_STATUS4 (STATUS4_FIRE_SPIN || STATUS4_CLAMP || STATUS4_WHIRLPOOL || STATUS4_SAND_TOMB || STATUS4_MAGMA_STORM || STATUS4_INFESTATION)

//effects for traps together //move data used in battle_moves_effects.h  each needs own battlescript
#define ITS_A_TRAP (EFFECT_TRAP || EFFECT_FIRE_SPIN || EFFECT_CLAMP || EFFECT_WHIRLPOOL || EFFECT_SAND_TOMB || EFFECT_MAGMA_STORM || EFFECT_INFESTATION || EFFECT_SNAP_TRAP)

#define GROUND_TRAPS (EFFECT_TRAP || EFFECT_FIRE_SPIN || EFFECT_CLAMP || EFFECT_WHIRLPOOL || EFFECT_SAND_TOMB || EFFECT_INFESTATION || EFFECT_SNAP_TRAP)

// Not really sure what a "hitmarker" is.
#define HITMARKER_WAKE_UP_CLEAR         0x00000010	//// Cleared when waking up. Never set or checked.
#define HITMARKER_SKIP_DMG_TRACK        0x00000020
#define HITMARKER_DESTINYBOND           0x00000040
#define HITMARKER_NO_ANIMATIONS         0x00000080
#define HITMARKER_IGNORE_SUBSTITUTE     0x00000100
#define HITMARKER_NO_ATTACKSTRING       0x00000200
#define HITMARKER_ATTACKSTRING_PRINTED  0x00000400
#define HITMARKER_NO_PPDEDUCT           0x00000800
#define HITMARKER_SWAP_ATTACKER_TARGET  0x00001000
#define HITMARKER_IGNORE_SAFEGUARD      0x00002000
#define HITMARKER_SYNCHRONISE_EFFECT    0x00004000
#define HITMARKER_RUN                   0x00008000
/*#define HITMARKER_IGNORE_ON_AIR         0x00010000
#define HITMARKER_IGNORE_UNDERGROUND    0x00020000
#define HITMARKER_IGNORE_UNDERWATER     0x00040000*/
#define HITMARKER_UNABLE_TO_USE_MOVE    0x00010000
#define HITMARKER_PASSIVE_DAMAGE        0x00020000
#define HITMARKER_DISOBEDIENT_MOVE      0x00040000
#define HITMARKER_PLAYER_FAINTED        0x00080000
#define HITMARKER_ALLOW_NO_PP           0x00100000
#define HITMARKER_GRUDGE                0x00200000
#define HITMARKER_OBEYS                 0x00400000
#define HITMARKER_NEVER_SET             0x00800000	// Cleared as part of a large group. Never set or checked
#define HITMARKER_CHARGING              0x01000000
#define HITMARKER_IGNORE_DISGUISE       0x02000000
#define HITMARKER_FAINTED(battler)      (gBitTable[battler] << 0x1C)
#define HITMARKER_FAINTED2(battler)     (0x10000000 << battler)	//removed hitmarker semi invul underground etc. can't go up to fainted2 value

// Per-side statuses that affect an entire party
#define SIDE_STATUS_REFLECT					(1 << 0)
#define SIDE_STATUS_LIGHTSCREEN				(1 << 1)
#define SIDE_STATUS_STICKY_WEB				(1 << 2)
#define SIDE_STATUS_SPIKES					(1 << 4)
#define SIDE_STATUS_SAFEGUARD				(1 << 5)
#define SIDE_STATUS_FUTUREATTACK			(1 << 6)
#define SIDE_STATUS_MIST					(1 << 8)
#define SIDE_STATUS_SPIKES_DAMAGED			(1 << 9)
#define SIDE_STATUS_TAILWIND                (1 << 10)
#define SIDE_STATUS_AURORA_VEIL             (1 << 11)
#define SIDE_STATUS_LUCKY_CHANT             (1 << 12)
#define SIDE_STATUS_TOXIC_SPIKES            (1 << 13)
#define SIDE_STATUS_STEALTH_ROCK            (1 << 14)
#define SIDE_STATUS_STEALTH_ROCK_DAMAGED    (1 << 15)
#define SIDE_STATUS_TOXIC_SPIKES_DAMAGED    (1 << 16)
#define SIDE_STATUS_STICKY_WEB_DAMAGED      (1 << 17)
#define SIDE_STATUS_QUICK_GUARD             (1 << 18)
#define SIDE_STATUS_WIDE_GUARD              (1 << 19)
#define SIDE_STATUS_CRAFTY_SHIELD           (1 << 20)
#define SIDE_STATUS_MAT_BLOCK               (1 << 21)

// Field affecting statuses.
#define STATUS_FIELD_MAGIC_ROOM         0x1
#define STATUS_FIELD_TRICK_ROOM         0x2
#define STATUS_FIELD_WONDER_ROOM        0x4
//#define STATUS_FIELD_MUDSPORT           0x8  will try to keep these 2 in status3 because they didn't use a timer
//#define STATUS_FIELD_WATERSPORT         0x10
#define STATUS_FIELD_GRAVITY            0x20
#define STATUS_FIELD_GRASSY_TERRAIN     0x40
#define STATUS_FIELD_MISTY_TERRAIN      0x80
#define STATUS_FIELD_ELECTRIC_TERRAIN   0x100
#define STATUS_FIELD_PSYCHIC_TERRAIN    0x200
#define STATUS_FIELD_ION_DELUGE         0x400
#define STATUS_FIELD_FAIRY_LOCK         0x800

#define STATUS_TERRAIN_ANY              (STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN)

// Flags describing move's result
#define MOVE_RESULT_MISSED             (1 << 0)
#define MOVE_RESULT_SUPER_EFFECTIVE    (1 << 1)
#define MOVE_RESULT_NOT_VERY_EFFECTIVE (1 << 2)
#define MOVE_RESULT_DOESNT_AFFECT_FOE  (1 << 3)
#define MOVE_RESULT_ONE_HIT_KO         (1 << 4)
#define MOVE_RESULT_FAILED             (1 << 5)
#define MOVE_RESULT_FOE_ENDURED        (1 << 6)
#define MOVE_RESULT_FOE_HUNG_ON        (1 << 7)
#define MOVE_RESULT_NO_EFFECT          (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_FAILED)

// Battle Weather as enum
#define ENUM_WEATHER_NONE           0
#define ENUM_WEATHER_RAIN           1
#define ENUM_WEATHER_SUN            2
#define ENUM_WEATHER_SANDSTORM      3
#define ENUM_WEATHER_HAIL           4
#define REPEAT_SWITCH_IN            5 // Value added
//hopefully to make macro for list of abilities
//to repeat on opponent switch in/send out

// Battle Weather flags
#define WEATHER_RAIN_TEMPORARY			(1 << 0)
#define WEATHER_RAIN_DOWNPOUR			(1 << 1)  // unused
#define WEATHER_RAIN_PERMANENT			(1 << 2)
#define B_WEATHER_RAIN_PRIMAL			(1 << 11)
#define WEATHER_RAIN_ANY				(WEATHER_RAIN_TEMPORARY | WEATHER_RAIN_DOWNPOUR | WEATHER_RAIN_PERMANENT | B_WEATHER_RAIN_PRIMAL)
#define WEATHER_SANDSTORM_TEMPORARY		(1 << 3)
#define WEATHER_SANDSTORM_PERMANENT		(1 << 4)
#define WEATHER_SANDSTORM_ANY			(WEATHER_SANDSTORM_TEMPORARY | WEATHER_SANDSTORM_PERMANENT)
#define WEATHER_SUN_TEMPORARY			(1 << 5)
#define WEATHER_SUN_PERMANENT			(1 << 6)
#define B_WEATHER_SUN_PRIMAL			(1 << 9)
#define WEATHER_SUN_ANY					(WEATHER_SUN_TEMPORARY | WEATHER_SUN_PERMANENT | B_WEATHER_SUN_PRIMAL)
#define WEATHER_HAIL					(1 << 7)
#define WEATHER_HAIL_PERMANENT			(1 << 8)
#define B_WEATHER_STRONG_WINDS			(1 << 10)
#define WEATHER_HAIL_ANY				(WEATHER_HAIL | WEATHER_HAIL_PERMANENT)
#define WEATHER_ANY						(WEATHER_RAIN_ANY | WEATHER_SANDSTORM_ANY | WEATHER_SUN_ANY | WEATHER_HAIL_ANY | B_WEATHER_STRONG_WINDS)
#define B_WEATHER_PRIMAL_ANY			(B_WEATHER_RAIN_PRIMAL | B_WEATHER_SUN_PRIMAL | B_WEATHER_STRONG_WINDS)

// Move Effects
#define MOVE_EFFECT_NOTHING_0           0x0
#define MOVE_EFFECT_SLEEP               0x1
#define MOVE_EFFECT_POISON              0x2
#define MOVE_EFFECT_BURN                0x3
#define MOVE_EFFECT_FREEZE              0x4
#define MOVE_EFFECT_PARALYSIS           0x5
#define MOVE_EFFECT_TOXIC               0x6
#define PRIMARY_STATUS_MOVE_EFFECT      MOVE_EFFECT_TOXIC // All above move effects apply primary status
//#define MOVE_EFFECT_SPIRIT_LOCK       0x6  //increase everything til v create by 1 use incrementer from discord for that
#define MOVE_EFFECT_CONFUSION           0x7 //have to do it by hand since incrementer tool cant handle hexadecimal
#define MOVE_EFFECT_FLINCH              0x8
#define MOVE_EFFECT_TRI_ATTACK          0x9
#define MOVE_EFFECT_UPROAR              0xA
#define MOVE_EFFECT_PAYDAY              0xB
#define MOVE_EFFECT_CHARGING            0xC
#define MOVE_EFFECT_WRAP                0xD
#define MOVE_EFFECT_RECOIL_25           0xE
#define MOVE_EFFECT_ATK_PLUS_1          0xF
#define MOVE_EFFECT_DEF_PLUS_1          0x10
#define MOVE_EFFECT_SPD_PLUS_1          0x11
#define MOVE_EFFECT_SP_ATK_PLUS_1       0x12
#define MOVE_EFFECT_SP_DEF_PLUS_1       0x13
#define MOVE_EFFECT_ACC_PLUS_1          0x14
#define MOVE_EFFECT_EVS_PLUS_1          0x15
#define MOVE_EFFECT_ATK_MINUS_1         0x16
#define MOVE_EFFECT_DEF_MINUS_1         0x17
#define MOVE_EFFECT_SPD_MINUS_1         0x18
#define MOVE_EFFECT_SP_ATK_MINUS_1      0x19
#define MOVE_EFFECT_SP_DEF_MINUS_1      0x1A
#define MOVE_EFFECT_ACC_MINUS_1         0x1B
#define MOVE_EFFECT_EVS_MINUS_1         0x1C
#define MOVE_EFFECT_RECHARGE            0x1D
#define MOVE_EFFECT_RAGE                0x1E
#define MOVE_EFFECT_STEAL_ITEM          0x1F
#define MOVE_EFFECT_PREVENT_ESCAPE      0x20
#define MOVE_EFFECT_NIGHTMARE           0x21
#define MOVE_EFFECT_ALL_STATS_UP        0x22
#define MOVE_EFFECT_RAPIDSPIN           0x23
#define MOVE_EFFECT_REMOVE_PARALYSIS    0x24
#define MOVE_EFFECT_ATK_DEF_DOWN        0x25
#define MOVE_EFFECT_RECOIL_33           0x26
#define MOVE_EFFECT_ATK_PLUS_2          0x27
#define MOVE_EFFECT_DEF_PLUS_2          0x28
#define MOVE_EFFECT_SPD_PLUS_2          0x29
#define MOVE_EFFECT_SP_ATK_PLUS_2       0x2A
#define MOVE_EFFECT_SP_DEF_PLUS_2       0x2B
#define MOVE_EFFECT_ACC_PLUS_2          0x2C
#define MOVE_EFFECT_EVS_PLUS_2          0x2D
#define MOVE_EFFECT_ATK_MINUS_2         0x2E
#define MOVE_EFFECT_DEF_MINUS_2         0x2F
#define MOVE_EFFECT_SPD_MINUS_2         0x30
#define MOVE_EFFECT_SP_ATK_MINUS_2      0x31
#define MOVE_EFFECT_SP_DEF_MINUS_2      0x32
#define MOVE_EFFECT_ACC_MINUS_2         0x33
#define MOVE_EFFECT_EVS_MINUS_2         0x34
#define MOVE_EFFECT_THRASH              0x35
#define MOVE_EFFECT_KNOCK_OFF           0x36
#define MOVE_EFFECT_CLEAR_SMOG          0x37
#define MOVE_EFFECT_SMACK_DOWN          0x38
#define MOVE_EFFECT_FLAME_BURST         0x39
#define MOVE_EFFECT_DEF_SPDEF_DOWN      0x3A
#define MOVE_EFFECT_SP_ATK_TWO_DOWN     0x3B
#define MOVE_EFFECT_FEINT				0x3C
#define MOVE_EFFECT_SPECTRAL_THIEF      0x3D
#define MOVE_EFFECT_ATTRACT				0x3E	//just need to set this to the effect attract?
#define MOVE_EFFECT_SPIRIT_LOCK			0x3F  
#define MOVE_EFFECT_HAPPY_HOUR          0x40
#define MOVE_EFFECT_CORE_ENFORCER       0x41
#define MOVE_EFFECT_THROAT_CHOP         0x42
#define MOVE_EFFECT_INCINERATE          0x43
#define MOVE_EFFECT_BUG_BITE	        0x44
#define MOVE_EFFECT_RECOIL_50	        0x45
#define MOVE_EFFECT_RECOIL_33_STATUS	0x46
#define MOVE_EFFECT_V_CREATE			0x47
#define MOVE_EFFECT_RELIC_SONG          0x48
#define MOVE_EFFECT_TRAP_BOTH           0x49
#define MOVE_EFFECT_SKY_DROP            0x4A	//add move_effects for other wrap moves
#define MOVE_EFFECT_FIRE_SPIN			0x4B
#define MOVE_EFFECT_CLAMP				0x4C
#define MOVE_EFFECT_WHIRLPOOL			0x4D
#define MOVE_EFFECT_SAND_TOMB			0x4E
#define MOVE_EFFECT_MAGMA_STORM			0x4F
#define MOVE_EFFECT_INFESTATION			0x50
#define MOVE_EFFECT_SNAP_TRAP			0x51

#define NUM_MOVE_EFFECTS                82
#define MOVE_EFFECT_AFFECTS_USER        0x60
#define MOVE_EFFECT_CERTAIN             0x90	//OK THIS SEEMS FINE its just a define doesn't need to be a specific value

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
#define B_WIN_ACTION_MENU         2 // "Fight/Pokémon/Bag/Run" menu
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

#endif // GUARD_CONSTANTS_BATTLE_H
