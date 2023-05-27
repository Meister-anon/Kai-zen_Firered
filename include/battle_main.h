#ifndef GUARD_BATTLE_MAIN_H
#define GUARD_BATTLE_MAIN_H

#include "constants/abilities.h"

struct TrainerMoney
{
    u8 classId;
    u8 value;
};

struct MultiBattlePokemonTx
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 heldItem;
    /*0x04*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x0F*/ u8 level;
    /*0x10*/ u16 hp;
    /*0x12*/ u16 maxhp;
    /*0x14*/ u32 status;
    /*0x18*/ u32 personality;
    /*0x1C*/ u8 gender;
    /*0x1D*/ u8 language;
};

#define TYPE_NAME_LENGTH 8
#define ABILITY_NAME_LENGTH 16 //is 16 in emerald may look into raising - DONE
#define ABILITY_DESCRIPTION_LENGTH 82

//I feel so stupid I literally never knew this was here... vsonic IMPORTANT
//ok so each line in the table is broken up into 3 parts
// i  should be line start, so i + 1, is the 2nd argument in the line i.e def type
// and i + 2, I believe would be 3rd argument in the line

//curious about hwo to use these defines to pull effectiveness,
//and where rest of logic i.e how it knows to make things not in table neutral effectiveness??

//mostly know how it works now, interesting thing to note, its actually simpler to alter and work with the firered type implementation
//than the emerald version,  they have a all the data visible in a table,but changing it requires,
//making a new table, in fire red I can just tweak the function logic.

// defines for the u8 array gTypeEffectiveness
#define TYPE_EFFECT_ATK_TYPE(i)((gTypeEffectiveness[i + 0]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
#define TYPE_EFFECT_DEF_TYPE(i)((gTypeEffectiveness[i + 1]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
#define TYPE_EFFECT_MULTIPLIER(i)((gTypeEffectiveness[i + 2]))  //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns

// defines for the gTypeEffectiveness multipliers
#define TYPE_MUL_NO_EFFECT          0
#define TYPE_MUL_NOT_EFFECTIVE      5
#define TYPE_MUL_NORMAL             10
#define TYPE_MUL_SUPER_EFFECTIVE    20

// special type table Ids
#define TYPE_FORESIGHT  0xFE
#define TYPE_ENDTABLE   0xFF

// defines for the 'DoBounceEffect' function
#define BOUNCE_MON          0x0
#define BOUNCE_HEALTHBOX    0x1


// for Natural Gift and Fling
struct TypePower
{
    u8 type;
    u8 power;
    u16 effect;
};

extern const struct SpriteTemplate gUnknownDebugSprite;
extern const struct OamData gOamData_BattlerOpponent;
extern const struct OamData gOamData_BattlerPlayer;
extern const u8 gTypeNames[][TYPE_NAME_LENGTH + 1];
extern const u8 gStatusConditionString_PoisonJpn[8];
extern const u8 gStatusConditionString_SleepJpn[8];
extern const u8 gStatusConditionString_ParalysisJpn[8];
extern const u8 gStatusConditionString_BurnJpn[8];
extern const u8 gStatusConditionString_IceJpn[8];
extern const u8 gStatusConditionString_ConfusionJpn[8];
extern const u8 gStatusConditionString_LoveJpn[8];
extern const u8 *const gStatusConditionStringsTable[7][2];
extern const u8 gTypeEffectiveness[423]; //fairy addition
extern const struct TrainerMoney gTrainerMoneyTable[];
extern const u8 *const gAbilityDescriptionPointers[ABILITIES_COUNT];
extern const u8 gAbilityNames[ABILITIES_COUNT][ABILITY_NAME_LENGTH + 1];
extern const struct TypePower gNaturalGiftTable[];

void CB2_InitBattle(void);
void BattleMainCB2(void);
void FreeRestoreBattleData(void);
void VBlankCB_Battle(void);
void SpriteCB_VsLetterDummy(struct Sprite *sprite);
void SpriteCB_VsLetterInit(struct Sprite *sprite);
//void CB2_InitEndLinkBattle(void);
u32 GetBattleBgAttribute(u8 arrayId, u8 caseId);
void SpriteCB_EnemyMon(struct Sprite *sprite);
void SpriteCallbackDummy2(struct Sprite *sprite);
void SpriteCB_FaintOpponentMon(struct Sprite *sprite);
void SpriteCb_ShowAsMoveTarget(struct Sprite *sprite);
void SpriteCb_HideAsMoveTarget(struct Sprite *sprite);
void SpriteCB_AllyMon(struct Sprite *sprite);
void SpriteCB_SetToDummy3(struct Sprite *sprite);
void SpriteCB_FaintSlideAnim(struct Sprite *sprite);
void DoBounceEffect(u8 battler, u8 which, s8 delta, s8 amplitude);
void EndBounceEffect(u8 battler, u8 which);
void SpriteCB_PlayerThrowInit(struct Sprite *sprite);
void UpdatePlayerPosInThrowAnim(struct Sprite *sprite);
void BattleDummy(void);
void BeginBattleIntro(void);
void SwitchInClearSetData(void);
void FaintClearSetData(void);
void BattleTurnPassed(void);
u8 IsRunningFromBattleImpossible(void);
void UpdatePartyOwnerOnSwitch_NonMulti(u8 battler);
void SwapTurnOrder(u8 id1, u8 id2);
u8 GetWhoStrikesFirst(u8 battler1, u8 battler2, bool8 ignoreChosenMoves);
void RunBattleScriptCommands_PopCallbacksStack(void);
void RunBattleScriptCommands(void);
bool8 TryRunFromBattle(u8 battler);
s8 GetMovePriority(u8 battlerId, u16 move);
s8 GetChosenMovePriority(u8 battlerId);
bool8 IsRivalBattle(u16 trainerNum);

#endif // GUARD_BATTLE_MAIN_H
