#ifndef GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_CONSTANTS_BATTLE_SCRIPT_COMMANDS_H

// Battle Scripting and BattleCommunication addresses
#define sPAINSPLIT_HP gBattleScripting
#define sBIDE_DMG gBattleScripting + 4
#define sMULTIHIT_STRING gBattleScripting + 8
#define sDMG_MULTIPLIER gBattleScripting + 0xE
#define sTWOTURN_STRINGID gBattleScripting + 0xF
#define sB_ANIM_ARG1 gBattleScripting + 0x10
#define sB_ANIM_ARG2 gBattleScripting + 0x11
#define sTRIPLE_KICK_POWER gBattleScripting + 0x12
#define sMOVEEND_STATE gBattleScripting + 0x14
#define sBATTLER_WITH_ABILITY gBattleScripting + 0x15
#define sMULTIHIT_EFFECT gBattleScripting + 0x16
#define sBATTLER gBattleScripting + 0x17
#define sB_ANIM_TURN gBattleScripting + 0x18
#define sB_ANIM_TARGETS_HIT gBattleScripting + 0x19
#define sSTATCHANGER gBattleScripting + 0x1A
#define sSTAT_ANIM_PLAYED gBattleScripting + 0x1B
#define sGIVEEXP_STATE gBattleScripting + 0x1C
#define sBATTLE_STYLE gBattleScripting + 0x1D
#define sLVLBOX_STATE gBattleScripting + 0x1E
#define sLEARNMOVE_STATE gBattleScripting + 0x1F
#define sFIELD_20 gBattleScripting + 0x20
#define sRESHOW_MAIN_STATE gBattleScripting + 0x21
#define sRESHOW_HELPER_STATE gBattleScripting + 0x22
#define sFIELD_23 gBattleScripting + 0x23
#define sWINDOWS_TYPE gBattleScripting + 0x24
#define sMULTIPLAYER_ID gBattleScripting + 0x25
#define sSPECIAL_TRAINER_BATTLE_TYPE gBattleScripting + 0x26

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

// TODO: documentation	//need to set bs.inc various to the order of this file
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
//emerald ported luckily doesn't have to be in sequence so I'll just leave
//here in case they're needed
#define VARIOUS_SET_TELEPORT_OUTCOME            25
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
