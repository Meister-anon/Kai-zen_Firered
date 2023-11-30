#ifndef GUARD_BATTLE_MAIN_H
#define GUARD_BATTLE_MAIN_H

#include "constants/abilities.h"

struct TrainerMoney
{
    u8 classId;
    u8 value;
};

// for Natural Gift and Fling
struct TypePower
{
    u8 type;
    u8 power;
    u16 effect;
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

//#define TYPE_NAME_LENGTH 6
//#define ABILITY_NAME_LENGTH 14

// defines for the u8 array gTypeEffectiveness
#define TYPE_EFFECT_ATK_TYPE(i)((gTypeEffectiveness[i + 0]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
#define TYPE_EFFECT_DEF_TYPE(i)((gTypeEffectiveness[i + 1]))    //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns
#define TYPE_EFFECT_MULTIPLIER(i)((gTypeEffectiveness[i + 2]))  //chart is broken into 3 fields per row, i reads the row, + value shifts the column, size of array is total number of fields, i.e num rows x columns

// defines for the gTypeEffectiveness multipliers
#define TYPE_MUL_NO_EFFECT          0
#define TYPE_MUL_NOT_EFFECTIVE      5
#define TYPE_MUL_NORMAL             10
#define TYPE_MUL_SUPER_EFFECTIVE    (155 / 10)//16  //changed from 20 to 15 to 16 for 1.6x dmg  change 1.55x seems works? messed up  forgot these get divided by 10 after heh

// special type table Ids
#define TYPE_FORESIGHT  0xFE
#define TYPE_ENDTABLE   0xFF

// defines for the 'DoBounceEffect' function
#define BOUNCE_MON          0x0
#define BOUNCE_HEALTHBOX    0x1

#define CAN_ABILITY_ABSORB(battler) (gBattleMons[battler].status1 == 0 && !(gBattleMons[battler].status2 & STATUS2_CONFUSION))

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
extern const u16 gTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES]; //type table port
extern const u8 gTypeEffectiveness[420]; //normal type array
extern const struct TrainerMoney gTrainerMoneyTable[];
extern const struct TypePower gNaturalGiftTable[];
//extern const u8 *const gAbilityDescriptionPointers[ABILITIES_COUNT];
//extern const u8 gAbilityNames[ABILITIES_COUNT][ABILITY_NAME_LENGTH + 1];

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
void SortBattlersBySpeed(u8 *battlers, bool8 slowToFast);
u32 GetBattlerTotalSpeedStat(u8 battlerId);
void RunBattleScriptCommands_PopCallbacksStack(void);
void RunBattleScriptCommands(void);
bool8 TryRunFromBattle(u8 battler);
s8 GetMovePriority(u8 battlerId, u16 move);
s8 GetChosenMovePriority(u8 battlerId);
bool8 IsRivalBattle(u16 trainerNum);
bool32 IsWildMonSmart(void);
void SetTypeBeforeUsingMove(u16 move, u8 battlerAtk);
u8 ReturnMoveType(u16 move, u8 battlerAtk); //atempt copy of settype function but using return value of move type so can display stuff in sum screen

#endif // GUARD_BATTLE_MAIN_H
