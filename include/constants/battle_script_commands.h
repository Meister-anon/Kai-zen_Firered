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
#define sMULTIHIT_EFFECT gBattleScripting + 0x16		//u16 multihitMoveEffect; 2 byte 0x16 0x17	 //multihitMoveEffect
#define sSAVED_MOVE_EFFECT gBattleScripting + 0x18		//u16 savedMoveEffect; 2 byte 0x18 0x19         // savedMoveEffect
#define sMOVE_EFFECT gBattleScripting + 0x1A			//u16 moveEffect; 2 byte 0x1a 0x1b          // moveEffect
#define sBATTLER gBattleScripting + 0x1C				//u8 battler; 1 byte 0x1c
#define sB_ANIM_TURN gBattleScripting + 0x1D			//u8 animTurn; 1 byte 0x1d
#define sB_ANIM_TARGETS_HIT gBattleScripting + 0x1E		//u8 animTargetsHit; 1 byte 0x1e
#define sSTATCHANGER gBattleScripting + 0x1F			//u8 statChanger; 1 byte 0x1f
#define sSTAT_ANIM_PLAYED gBattleScripting + 0x20		//bool8 statAnimPlayed; 1 byte 0x20
#define sGIVEEXP_STATE gBattleScripting + 0x21			//u8 atk23_getexpState; 1 byte 0x21
#define sBATTLE_STYLE gBattleScripting + 0x22			//u8 battleStyle; 1 byte 0x22
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
#define sSPECIAL_TRAINER_BATTLE_TYPE gBattleScripting + 0x34

#define cEFFECT_CHOOSER gBattleCommunication + 3
#define cMULTISTRING_CHOOSER gBattleCommunication + 5

// Battle Script defines for getting the wanted battler
#define BS_TARGET                   0
#define BS_ATTACKER                 1
#define BS_EFFECT_BATTLER           2
#define BS_FAINTED                  3
#define BS_ATTACKER_WITH_PARTNER    4 // for atk98_updatestatusicon
#define BS_UNKNOWN_5                5 // for openpartyscreen
#define BS_UNKNOWN_6                6 // for openpartyscreen
#define BS_BATTLER_0                7
#define BS_ATTACKER_SIDE            8 // for atk1E_jumpifability
#define BS_NOT_ATTACKER_SIDE        9 // for atk1E_jumpifability
#define BS_SCRIPTING                10
#define BS_PLAYER1                  11
#define BS_OPPONENT1                12
#define BS_PLAYER2                  13 // for atk98_updatestatusicon
#define BS_OPPONENT2                14

// used for openpartyscreen
#define OPEN_PARTY_ALLOW_CANCEL     0x80

// atk 01, accuracy calc
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

// TODO: documentation
// atk76, various
#define VARIOUS_CANCEL_MULTI_TURN_MOVES         0
#define VARIOUS_SET_MAGIC_COAT_TARGET           1
#define VARIOUS_IS_RUNNING_IMPOSSIBLE           2
#define VARIOUS_GET_MOVE_TARGET                 3
#define VARIOUS_CASE_4                          4
#define VARIOUS_RESET_INTIMIDATE_TRACE_BITS     5
#define VARIOUS_UPDATE_CHOICE_MOVE_ON_LVL_UP    6
#define VARIOUS_RESET_PLAYER_FAINTED_FLAG                          7
#define VARIOUS_CASE_8                          8
#define VARIOUS_RETURN_OPPONENT_MON1            9
#define VARIOUS_RETURN_OPPONENT_MON2            10
#define VARIOUS_CHECK_POKEFLUTE                 11
#define VARIOUS_WAIT_FANFARE                    12

// atk80, dmg manipulation
#define ATK80_DMG_CHANGE_SIGN                               0
#define ATK80_DMG_HALF_BY_TWO_NOT_MORE_THAN_HALF_MAX_HP     1
#define ATK80_DMG_DOUBLED                                   2

// atk4F, a flag used for the jumpifcantswitch command
#define ATK4F_DONT_CHECK_STATUSES   0x80

// statchange defines
#define STAT_CHANGE_BS_PTR                  0x1
#define STAT_CHANGE_NOT_PROTECT_AFFECTED    0x20

// atk48
#define ATK48_STAT_NEGATIVE         0x1
#define ATK48_STAT_BY_TWO           0x2
#define ATK48_ONLY_MULTIPLE         0x4
#define ATK48_DONT_CHECK_LOWER      0x8

// atk49, moveend cases
#define ATK49_RAGE                              0
#define ATK49_DEFROST                           1
#define ATK49_SYNCHRONIZE_TARGET                2
#define ATK49_MOVE_END_ABILITIES                3
#define ATK49_STATUS_IMMUNITY_ABILITIES         4
#define ATK49_SYNCHRONIZE_ATTACKER              5
#define ATK49_CHOICE_MOVE                       6
#define ATK49_CHANGED_ITEMS                     7
#define ATK49_ATTACKER_INVISIBLE                8
#define ATK49_ATTACKER_VISIBLE                  9
#define ATK49_TARGET_VISIBLE                    10
#define ATK49_ITEM_EFFECTS_ALL                  11
#define ATK49_KINGSROCK_SHELLBELL               12
#define ATK49_SUBSTITUTE                        13
#define ATK49_UPDATE_LAST_MOVES                 14
#define ATK49_MIRROR_MOVE                       15
#define ATK49_NEXT_TARGET                       16
#define ATK49_COUNT                             17

#define BIT_HP                      0x1
#define BIT_ATK                     0x2
#define BIT_DEF                     0x4
#define BIT_SPEED                   0x8
#define BIT_SPATK                   0x10
#define BIT_SPDEF                   0x20
#define BIT_ACC                     0x40
#define BIT_EVASION                 0x80

#endif // GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
