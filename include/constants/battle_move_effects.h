#ifndef GUARD_CONSTANTS_BATTLE_MOVE_EFFECTS_H
#define GUARD_CONSTANTS_BATTLE_MOVE_EFFECTS_H

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
#define MOVE_EFFECT_REMOVE_STATUS		0x24
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
#define MOVE_EFFECT_DEF_SPDEF_DOWN      0x38
#define MOVE_EFFECT_SP_ATK_TWO_DOWN     0x39
#define MOVE_EFFECT_RECOIL_50	        0x3A
#define MOVE_EFFECT_RECOIL_33_STATUS	0x3B
#define MOVE_EFFECT_SMACK_DOWN          0x3C	//reordered move effects for shield dust logic
#define MOVE_EFFECT_FLAME_BURST         0x3D
#define MOVE_EFFECT_FEINT				0x3E
#define MOVE_EFFECT_SPECTRAL_THIEF      0x3F
#define MOVE_EFFECT_ATTRACT				0x40	//just need to set this to the effect attract?	//setstatus in bscommands, this infatuates w target should work for effect spore
#define MOVE_EFFECT_SPIRIT_LOCK			0x41  //but if
#define MOVE_EFFECT_INFESTATION         0x42
#define MOVE_EFFECT_HAPPY_HOUR          0x43
#define MOVE_EFFECT_CORE_ENFORCER       0x44
#define MOVE_EFFECT_THROAT_CHOP         0x45
#define MOVE_EFFECT_INCINERATE          0x46
#define MOVE_EFFECT_BUG_BITE	        0x47

#define MOVE_EFFECT_V_CREATE			0x48
#define MOVE_EFFECT_RELIC_SONG          0x49
#define MOVE_EFFECT_TRAP_BOTH           0x4A
#define MOVE_EFFECT_SKY_DROP            0x4B	//add move_effects for other wrap moves
#define MOVE_EFFECT_SCALE_SHOT			0x4C
#define MOVE_EFFECT_LOSE_TYPE			0x4D
#define MOVE_EFFECT_ROUND				0x4E

#define NUM_MOVE_EFFECTS                79	//ok think i got this right, battlescript are assigned based on battle_move_effects.h file
#define MOVE_EFFECT_AFFECTS_USER        0x4000//that has to line up with battle_scripts_1.s but don't need move effect unlesss new status made or other new effect
#define MOVE_EFFECT_CERTAIN             0x8000	//OK THIS SEEMS FINE its just a define doesn't need to be a specific value


#endif  // GUARD_CONSTANTS_BATTLE_MOVE_EFFECTS_H
