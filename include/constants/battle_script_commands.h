#ifndef GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H

//ok this needs to match the Battlescripting struct in include/battle.h
// + 1 if u8,   +2 if u16,   +4 if u32,  if bracket multiply value in bracket by type
//ex  u8 multihitString[6];    6 x  +1  = +6
//go up from previous value, not inclusive, so not counting that last value based on your found number and that's next values starting point
//ex last value 24  it is u16 so you go Up 2 from 24, - 25, 26, your next value is 26
//emerald also goes over 32, so that dosen't seem to be a hard limit this is fine

// Battle Scripting and BattleCommunication addresses
#define sPAINSPLIT_HP gBattleScripting					// s32 painSplitHp;	4 byte 0 1 2 3
#define sBIDE_DMG gBattleScripting + 4					//s32 bideDmg;	4 byte 4 5 6 7
#define sMULTIHIT_STRING gBattleScripting + 8			//u8 multihitString[6]; 6 1byte  8 9 a b c d

// think don't use sdmg_multiplier anymore since put dmg shift into flag least for semi invul, still have some to adjust facade & pursit, thencan remove
#define sDMG_MULTIPLIER gBattleScripting + 0xE			//u8 dmgMultiplier; 1 byte e
#define sTWOTURN_STRINGID gBattleScripting + 0xF		//u8 twoTurnsMoveStringId; 1 byte f
#define sB_ANIM_ARG1 gBattleScripting + 0x10			//u8 animArg1; 1 byte 0x10
#define sB_ANIM_ARG2 gBattleScripting + 0x11			//u8 animArg2; 1 byte 0x11
//I also moved triple kick power to functions so could remove?
#define sTRIPLE_KICK_POWER gBattleScripting + 0x12		//tripleKickPower; 2 byte 0x12 0x13
#define sMOVEEND_STATE gBattleScripting + 0x14			//u8 atk49_state; 1 byte 0x14
#define sBATTLER_WITH_ABILITY gBattleScripting + 0x15	//u8 battlerWithAbility; 1 byte 0x15
#define sMULTIHIT_EFFECT gBattleScripting + 0x16		//u16 multihitMoveEffect; 2 byte 0x16 0x17	 //stores move effect for multihit moves, like twineedle uses it to store poison
#define sSAVED_MOVE_EFFECT gBattleScripting + 0x18		//u16 savedMoveEffect; 2 byte 0x18 0x19         // savedMoveEffect
#define sMOVE_EFFECT gBattleScripting + 0x1A			//u16 moveEffect; 2 byte 0x1a 0x1b          // moveEffect   //these really are move effect
#define sBATTLER gBattleScripting + 0x1C				//u8 battler; 1 byte 0x1c
#define sB_ANIM_TURN gBattleScripting + 0x1D			//u8 animTurn; 1 byte 0x1d
#define sB_ANIM_TARGETS_HIT gBattleScripting + 0x1E		//u8 animTargetsHit; 1 byte 0x1e
#define sSTATCHANGER gBattleScripting + 0x1F			//u8 statChanger; 1 byte 0x1f
#define sSTAT_ANIM_PLAYED gBattleScripting + 0x20		//bool8 statAnimPlayed; 1 byte 0x20
#define sGIVEEXP_STATE gBattleScripting + 0x21			//u8 atk23_getexpState; 1 byte 0x21
#define sBATTLE_STYLE gBattleScripting + 0x22			//u8 battleStyle; 1 byte 0x22   //switch or set
#define sLVLBOX_STATE gBattleScripting + 0x23			//u8 atk6C_drawlvlupboxState; 1 byte 0x23
#define sLEARNMOVE_STATE gBattleScripting + 0x24		//u8 learnMoveState; 1 byte 0x24
#define sPURSUIT_DOUBLE_DAMAGE gBattleScripting + 0x25	//u8 field_25_pursuitDoublesAttacker; 1 byte 0x25    //unsure of use  maybe i changed but does'nt seem used
#define sRESHOW_MAIN_STATE gBattleScripting + 0x26		//u8 reshowMainState; 1 byte 0x26
#define sRESHOW_HELPER_STATE gBattleScripting + 0x27	//u8 reshowHelperState; 1 byte 0x27
#define sSAVED_STAT_CHANGER gBattleScripting + 0x28		//u8 savedStatChanger; 1 byte 0x28	for moody

#define sSAVED_BATTLER (gBattleScripting + 0x29)		//u8 savedBattler; 1 byte 0x29
//#define sILLUSION_NICK_HACK gBattleScripting + 0x25	//need add this eventually
//
//#define sFIXED_ABILITY_POPUP         (gBattleScripting + 0x26) // fixedPopup
//#define sABILITY_OVERWRITE           (gBattleScripting + 0x27) // abilityPopupOverwrite


#define sSWITCH_CASE (gBattleScripting + 0x2A)			//u8 switchCase; 1 byte 0x2a    // switchCase  used for red card special swith condition	//FORCED SWITCH?
#define sBERRY_OVERRIDE	(gBattleScripting + 0x2B)		//u8 overrideBerryRequirements; 1 byte 0x2b  // overrideBerryRequirements
#define sSTICKY_WEB_STAT_DROP (gBattleScripting + 0x2C) //u8 stickyWebStatDrop; 1 byte 0x2c  // overrideBerryRequirements
#define sSAVED_DMG gBattleScripting + 0x2D				//s32 savedDmg; 4 byte 0x2d 0x2e 0x2f 0x30
//#define sMON_CAUGHT     (gBattleScripting + 0x33) // monCaught NOT NEEDED, only used in emerald for succesful captures to incremennt game stat capture
#define sFIELD_23 gBattleScripting + 0x31				//u8 field_23;	1 byte 0x31		//nothing in struct below this think all used values must go above here
#define sWINDOWS_TYPE gBattleScripting + 0x32
#define sMULTIPLAYER_ID gBattleScripting + 0x33
#define sSPECIAL_TRAINER_BATTLE_TYPE gBattleScripting + 0x34    //wait aren't these limited to 32?


#define cEFFECT_CHOOSER gBattleCommunication + 3        //figure what gBattleCommunication is and how works. vsonic
#define cMULTISTRING_CHOOSER gBattleCommunication + 5

// Battle Script defines for getting the wanted battler
#define BS_TARGET                   0
#define BS_ATTACKER                 1
#define BS_EFFECT_BATTLER           2
#define BS_FAINTED                  3
#define BS_ATTACKER_WITH_PARTNER    4 // for atk98_updatestatusicon
#define BS_FAINTED_LINK_MULTIPLE_1  5 // for openpartyscreen
#define BS_FAINTED_LINK_MULTIPLE_2  6 // for openpartyscreen
#define BS_BATTLER_0                7
#define BS_ATTACKER_SIDE            8 // for atk1E_jumpifability
#define BS_TARGET_SIDE				9 // for atk1E_jumpifability
#define BS_SCRIPTING                10
#define BS_PLAYER1                  11
#define BS_OPPONENT1                12
#define BS_PLAYER2                  13 // for atk98_updatestatusicon  /?? i don't remember tis
#define BS_OPPONENT2                14
#define BS_ABILITY_BATTLER          15	//port from emerald
#define BS_ATTACKER_PARTNER         16

// used for openpartyscreen
#define OPEN_PARTY_ALLOW_CANCEL     0x80

// atk01_accuracycheck
#define NO_ACC_CALC 0xFFFE
#define NO_ACC_CALC_CHECK_LOCK_ON 0xFFFF
#define ACC_CURR_MOVE 0

// compare operands
#define CMP_EQUAL               0x0
#define CMP_NOT_EQUAL           0x1
#define CMP_GREATER_THAN        0x2
#define CMP_LESS_THAN           0x3
#define CMP_COMMON_BITS         0x4
#define CMP_NO_COMMON_BITS      0x5

// TODO: documentation	//need to set bs.inc various to the order of this file      doesn't need to match order at all
// atk76, various
#define VARIOUS_CANCEL_MULTI_TURN_MOVES         0
#define VARIOUS_SET_MAGIC_COAT_TARGET           1
#define VARIOUS_IS_RUNNING_IMPOSSIBLE           2
#define VARIOUS_GET_MOVE_TARGET                 3
#define VARIOUS_GET_BATTLER_FAINTED                          4
#define VARIOUS_RESET_INTIMIDATE_TRACE_BITS     5
#define VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP    6
#define VARIOUS_RESET_PLAYER_FAINTED			7
#define VARIOUS_CASE_8                          8
#define VARIOUS_RETURN_OPPONENT_MON1            9
#define VARIOUS_RETURN_OPPONENT_MON2            10
#define VARIOUS_CHECK_POKEFLUTE                 11
#define VARIOUS_WAIT_FANFARE                    12
//emerald ported luckily doesn't have to be in sequence so I'll just leave
//here in case they're needed
#define VARIOUS_SET_TELEPORT_OUTCOME            25
#define VARIOUS_SWITCHIN_ABILITIES				28
#define VARIOUS_SAVE_TARGET                     29
#define VARIOUS_RESTORE_TARGET                  30
#define VARIOUS_INSTANT_HP_DROP                 31
#define VARIOUS_CLEAR_STATUS                    32
#define VARIOUS_RESTORE_PP                      33
#define VARIOUS_TRY_ACTIVATE_MOXIE              34
#define VARIOUS_TRY_ACTIVATE_FELL_STINGER       35
#define VARIOUS_PLAY_MOVE_ANIMATION             36
#define VARIOUS_SET_LUCKY_CHANT                 37
#define VARIOUS_SUCKER_PUNCH_CHECK              38
#define VARIOUS_SET_SIMPLE_BEAM                 39
#define VARIOUS_TRY_ENTRAINMENT                 40
#define VARIOUS_SET_LAST_USED_ABILITY           41
#define VARIOUS_TRY_HEAL_PULSE                  42
#define VARIOUS_TRY_QUASH                       43
#define VARIOUS_INVERT_STAT_STAGES              44
#define VARIOUS_SET_TERRAIN                     45
#define VARIOUS_TRY_ME_FIRST                    46
#define VARIOUS_JUMP_IF_BATTLE_END              47
#define VARIOUS_TRY_ELECTRIFY                   48
#define VARIOUS_TRY_REFLECT_TYPE                49
#define VARIOUS_TRY_SOAK                        50
#define VARIOUS_HANDLE_MEGA_EVO                 51
#define VARIOUS_TRY_LAST_RESORT                 52
#define VARIOUS_ARGUMENT_STATUS_EFFECT          53
#define VARIOUS_TRY_HIT_SWITCH_TARGET           54
#define VARIOUS_TRY_AUTOTOMIZE                  55
#define VARIOUS_TRY_COPYCAT                     56
#define VARIOUS_ABILITY_POPUP                   57
#define VARIOUS_DEFOG                           58
#define VARIOUS_JUMP_IF_TARGET_ALLY             59
#define VARIOUS_TRY_SYNCHRONOISE                60
#define VARIOUS_PSYCHO_SHIFT                    61
#define VARIOUS_CURE_STATUS                     62
#define VARIOUS_POWER_TRICK                     63
#define VARIOUS_AFTER_YOU                       64
#define VARIOUS_BESTOW                          65
#define VARIOUS_ARGUMENT_TO_MOVE_EFFECT         66
#define VARIOUS_JUMP_IF_NOT_GROUNDED            67
#define VARIOUS_HANDLE_TRAINER_SLIDE_MSG        68
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_FIRST_OFF 69
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_LAST_ON   70
#define VARIOUS_SET_AURORA_VEIL                 71
#define VARIOUS_TRY_THIRD_TYPE                  72
#define VARIOUS_ACUPRESSURE                     73
#define VARIOUS_SET_POWDER                      74
#define VARIOUS_SPECTRAL_THIEF                  75
#define VARIOUS_GRAVITY_ON_AIRBORNE_MONS        76
#define VARIOUS_CHECK_IF_GRASSY_TERRAIN_HEALS   77
#define VARIOUS_JUMP_IF_ROAR_FAILS              78
#define VARIOUS_TRY_INSTRUCT                    79
#define VARIOUS_JUMP_IF_NOT_BERRY               80
#define VARIOUS_TRACE_ABILITY                   81
#define VARIOUS_UPDATE_NICK                     82
#define VARIOUS_TRY_ILLUSION_OFF                83
#define VARIOUS_SET_SPRITEIGNORE0HP             84
#define VARIOUS_HANDLE_FORM_CHANGE              85
#define VARIOUS_GET_STAT_VALUE                  86
#define VARIOUS_JUMP_IF_FULL_HP                 87
#define VARIOUS_LOSE_TYPE                       88
#define VARIOUS_TRY_ACTIVATE_SOULHEART          89
#define VARIOUS_TRY_ACTIVATE_RECEIVER           90
#define VARIOUS_TRY_ACTIVATE_BEAST_BOOST        91
#define VARIOUS_TRY_FRISK                       92
#define VARIOUS_JUMP_IF_SHIELDS_DOWN_PROTECTED  93
#define VARIOUS_TRY_FAIRY_LOCK                  94
#define VARIOUS_JUMP_IF_NO_ALLY                 95
#define VARIOUS_POISON_TYPE_IMMUNITY            96
#define VARIOUS_JUMP_IF_NO_HOLD_EFFECT          97
#define VARIOUS_INFATUATE_WITH_BATTLER          98
#define VARIOUS_SET_LAST_USED_ITEM              99
#define VARIOUS_PARALYZE_TYPE_IMMUNITY          100
#define VARIOUS_JUMP_IF_ABSENT                  101
#define VARIOUS_DESTROY_ABILITY_POPUP           102
#define VARIOUS_TOTEM_BOOST                     103
#define VARIOUS_TRY_ACTIVATE_GRIM_NEIGH         104
#define VARIOUS_MOVEEND_ITEM_EFFECTS            105
//think will introduce character that will give seeds for berries
#define VARIOUS_TERRAIN_SEED                        106
#define VARIOUS_MAKE_INVISIBLE                      107
#define VARIOUS_ROOM_SERVICE                        108
#define VARIOUS_JUMP_IF_TERRAIN_AFFECTED            109
#define VARIOUS_EERIE_SPELL_PP_REDUCE               110
#define VARIOUS_JUMP_IF_TEAM_HEALTHY                111
#define VARIOUS_TRY_HEAL_QUARTER_HP                 112
#define VARIOUS_REMOVE_TERRAIN                      113
#define VARIOUS_JUMP_IF_PRANKSTER_BLOCKED           114
#define VARIOUS_TRY_TO_CLEAR_PRIMAL_WEATHER         115
#define VARIOUS_GET_ROTOTILLER_TARGETS              116
#define VARIOUS_JUMP_IF_NOT_ROTOTILLER_AFFECTED     117
#define VARIOUS_TRY_ACTIVATE_BATTLE_BOND            118
#define VARIOUS_CONSUME_BERRY                       119
#define VARIOUS_JUMP_IF_CANT_REVERT_TO_PRIMAL       120
#define VARIOUS_HANDLE_PRIMAL_REVERSION             121
#define VARIOUS_APPLY_PLASMA_FISTS                  122
#define VARIOUS_JUMP_IF_SPECIES                     123
#define VARIOUS_UPDATE_ABILITY_POPUP                124
#define VARIOUS_JUMP_IF_WEATHER_AFFECTED            125
#define VARIOUS_JUMP_IF_LEAF_GUARD_PROTECTED        126
#define VARIOUS_SET_ATTACKER_STICKY_WEB_USER        127
#define VARIOUS_TRY_TO_APPLY_MIMICRY                128
#define VARIOUS_PHOTON_GEYSER_CHECK                 129
#define VARIOUS_SHELL_SIDE_ARM_CHECK                130
#define VARIOUS_TRY_NO_RETREAT                      131
#define VARIOUS_TRY_TAR_SHOT                        132
#define VARIOUS_CAN_TAR_SHOT_WORK                   133
#define VARIOUS_CHECK_POLTERGEIST                   134
#define VARIOUS_SET_OCTOLOCK                        135
#define VARIOUS_CUT_1_3_HP_RAISE_STATS              136
#define VARIOUS_TRY_END_NEUTRALIZING_GAS            137
#define VARIOUS_JUMP_IF_UNDER_200                   138
#define VARIOUS_SET_SKY_DROP                        139
#define VARIOUS_CLEAR_SKY_DROP                      140
#define VARIOUS_SKY_DROP_YAWN                       141
#define VARIOUS_JUMP_IF_CANT_FLING                  142
#define VARIOUS_JUMP_IF_HOLD_EFFECT                 143
#define VARIOUS_CURE_CERTAIN_STATUSES               144
#define VARIOUS_TRY_RESET_NEGATIVE_STAT_STAGES      145
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_BERRY        146
#define VARIOUS_JUMP_IF_LAST_USED_ITEM_HOLD_EFFECT  147
#define VARIOUS_SAVE_BATTLER_ITEM                   148
#define VARIOUS_RESTORE_BATTLER_ITEM                149
#define VARIOUS_BATTLER_ITEM_TO_LAST_USED_ITEM      150
#define VARIOUS_GROUND_FLYING_TARGET_2XDMGFLAG      151	//new bs command  to ground flying targets if hit by my w flag 2xdmg on air
#define VARIOUS_JUMP_IF_NOT_FULL_HP					152	
#define VARIOUS_TRY_END_STENCH						153	
//#define VARIOUS_RESET_FOREWARN_ANTICIPATION_BITS	154		pretty sure don't need doing different way.
#define VARIOUS_JUMP_IF_EMERGENCY_EXITED			154		//default implement, plan to just use for wimp out
#define VARIOUS_CHECK_PARENTAL_BOND_COUNTER			155 //not in updated emerlad expansion?

#define VARIOUS_SET_BEAK_BLAST                       156
#define VARIOUS_SWAP_SIDE_STATUSES                   157
#define VARIOUS_SWAP_STATS                           158
#define VARIOUS_JUMP_IF_ROD                          159
#define VARIOUS_JUMP_IF_ABSORB                       160
#define VARIOUS_JUMP_IF_MOTOR                        161
#define VARIOUS_TEATIME_INVUL                        162
#define VARIOUS_TEATIME_TARGETS                      163
#define VARIOUS_TRY_WIND_RIDER_POWER                 164
#define VARIOUS_ACTIVATE_WEATHER_CHANGE_ABILITIES    165
#define VARIOUS_ACTIVATE_TERRAIN_CHANGE_ABILITIES    166
#define VARIOUS_STORE_HEALING_WISH                   167
#define VARIOUS_HIT_SWITCH_TARGET_FAILED             168
#define VARIOUS_JUMP_IF_SHELL_TRAP                   169
#define VARIOUS_TRY_REVIVAL_BLESSING                 170
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_Z_MOVE         171
#define VARIOUS_TRY_TRAINER_SLIDE_MSG_MEGA_EVOLUTION 172


// atk80, dmg manipulation
#define NEGATIVE_DMG					0
#define RECOIL_MISS_DMG					1	//udated this should do miss & immunity
#define DOUBLE_DMG						2
#define DMG_1_8_TARGET_HP				3
#define DMG_FULL_ATTACKER_HP			4
#define DMG_CURR_ATTACKER_HP			5
#define DMG_BIG_ROOT					6
#define DMG_1_2_ATTACKER_HP				7
#define DMG_RECOIL_FROM_IMMUNE		    8 // Used to calculate recoil for the Gen 4 version of Jump Kick, will tweak and instead consolidate in case 1

// Cmd_jumpifcantswitch
#define SWITCH_IGNORE_ESCAPE_PREVENTION   (1 << 7)

// atk4F, a flag used for the jumpifcantswitch command
#define ATK4F_DONT_CHECK_STATUSES   0x80

//equivalent of STAT_BUFF_ALLOW_PTR  just has different name
//& STAT_BUFF_NOT_PROTECT_AFFECTED

// statchange defines
#define STAT_CHANGE_BS_PTR                  (1 << 0) // If set, allow use of jumpptr. Set in every use of statbuffchange		//equivalent stat_change_allow_ptr
#define STAT_CHANGE_MIRROR_ARMOR			(1 << 1)	// Stat change redirection caused by Mirror Armor ability.
#define STAT_CHANGE_NOT_PROTECT_AFFECTED    (1 << 5)
#define STAT_CHANGE_UPDATE_MOVE_EFFECT		(1 << 6)	//still don't know what does

// atk48
#define STAT_CHANGE_STAT_NEGATIVE         0x1
#define STAT_CHANGE_STAT_BY_TWO           0x2
#define STAT_CHANGE_ONLY_MULTIPLE         0x4
#define STAT_CHANGE_DONT_CHECK_LOWER      0x8	//think equivalent of stat_change_cant_prevent

// atk49, moveend cases
#define MOVE_END_PROTECT_LIKE_EFFECT			   0
#define MOVE_END_RAGE                              1
#define MOVE_END_DEFROST                           2
#define MOVE_END_SYNCHRONIZE_TARGET                3
#define MOVE_END_MOVE_END_ABILITIES                4
#define MOVE_END_ABILITIES_ATTACKER				   5 //increment above 1
#define MOVE_END_STATUS_IMMUNITY_ABILITIES         6
#define MOVE_END_SYNCHRONIZE_ATTACKER              7
#define MOVE_END_CHOICE_MOVE                       8
#define MOVE_END_CHANGED_ITEMS                     9
#define MOVE_END_ATTACKER_INVISIBLE                10
#define MOVE_END_ATTACKER_VISIBLE                  11
#define MOVE_END_TARGET_VISIBLE                    12
#define MOVE_END_ITEM_EFFECTS_TARGET			   13
#define MOVE_END_MOVE_EFFECTS2					   14      
#define MOVE_END_ITEM_EFFECTS_ALL                  15
#define MOVE_END_KINGSROCK						   16  //item effect need to be bfore kingsrock for things like rocky helm I guess
#define MOVE_END_SUBSTITUTE                        17
#define MOVE_END_GROUND_TARGET                     18 //put here so cancel sky drop stuff
#define MOVE_END_SKY_DROP_CONFUSE				   19
#define MOVE_END_UPDATE_LAST_MOVES                 20
#define MOVE_END_MIRROR_MOVE                       21

#define MOVE_END_MULTIHIT_MOVE					   22   //added don't need, except for dragon darts but coudl potentially setup in bs maybe rename for parental bond instead?
#define MOVE_END_MAGICIAN                          23    // Occurs after final multi-hit strike, and after other items/abilities would activate
#define MOVE_END_EJECT_BUTTON                      24
#define MOVE_END_RED_CARD                          25
#define MOVE_END_EJECT_PACK                        26
#define MOVE_END_LIFEORB_SHELLBELL                 27    // Includes shell bell, throat spray, etc
#define MOVE_END_PICKPOCKET                        28
#define MOVE_END_DANCER							   29
#define MOVE_END_EMERGENCY_EXIT					   30
#define MOVE_END_SYMBIOSIS						   31
#define MOVE_END_NEXT_TARGET                       32 //was last value before count, in base firered
#define MOVE_END_CLEAR_BITS						   33
#define MOVE_END_COUNT							   34

// switch cases - PORTED right now not used, adding red card only for now
#define B_SWITCH_NORMAL     0
#define B_SWITCH_HIT        1   // dragon tail, circle throw
#define B_SWITCH_RED_CARD   2

#define BIT_HP                      0x1
#define BIT_ATK                     0x2
#define BIT_DEF                     0x4
#define BIT_SPEED                   0x8
#define BIT_SPATK                   0x10
#define BIT_SPDEF                   0x20
#define BIT_ACC                     0x40
#define BIT_EVASION                 0x80

//battle communication stuff
#define MISS_TYPE               6

#endif // GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
