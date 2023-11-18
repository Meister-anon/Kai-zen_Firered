#ifndef GUARD_FIELD_SPECIALS_H
#define GUARD_FIELD_SPECIALS_H

#include "global.h"

enum HiddenItemAttr
{
    HIDDEN_ITEM_ID = 0,
    HIDDEN_ITEM_FLAG,
    HIDDEN_ITEM_QUANTITY,
    HIDDEN_ITEM_UNDERFOOT
};

u8 GetLeadMonIndex(void);
//extern const u8 gTypeNames[][TYPE_NAME_LENGTH + 1];
extern const u16 sTypeExceptions[18]; //update this value when adding to the array
s32 CountDigits(s32 number);
void TV_PrintIntToStringVar(u8 varidx, s32 number);
u16 GetStarterSpecies(void);
u16 RivalEeveelutionForPlayerStarter(void);
void StopPokemonLeagueLightingEffectTask(void);
void nullsub_60(void);
void nullsub_61(void);
u8 ContextNpcGetTextColor(void);
void SetPCBoxToSendMon(u8);
u16 GetPCBoxToSendMon(void);
bool8 IsDestinationBoxFull(void);
bool8 ShouldShowBoxWasFullMessage(void);
u16 GetHiddenItemAttr(u32 hiddenItem, u8 attr);
u8 GetUnlockedSeviiAreas(void);
u32 GetPlayerTrainerId(void);
bool8 CutMoveRuinValleyCheck(void);
void CutMoveOpenDottedHoleDoor(void);
void RunMassageCooldownStepCounter(void);
void IncrementResortGorgeousStepCounter(void);
void IncrementBirthIslandRockStepCount(void);
void ResetCyclingRoadChallengeData(void);
void ResetFieldTasksArgs(void);  //not in .c? is used its in a differnt file
bool8 UsedPokemonCenterWarp(void);
void sub_80CC534(void);
void sub_80CC59C(void);
/*void SetPlayerBulbasaurBall(void); //pray this works, and its not in the wrong place
void SetPlayerSquirtleBall(void);
void SetPlayerCharmanderBall(void);
void SetRivalBulbasaurBall(void);
void SetRivalSquirtleBall(void);
void SetRivalCharmanderBall(void);*/
void SetPlayerRandomStarterSpecies(void);
void SetRivalRandomStarterSpecies(void);
void RivalStarterConditionCheck(void); //loop for rival starter reset
u8 ShouldResetRivalStarter(void); //check type relation with player and return true false, plan use loop to reset
u16 GetFinalEvo(u16 species); //very basic, does not take into account branching evos, it only uses the first method
u8 CheckSuperEffective(u16 Atk_Species, u16 Target_Species); //check given species and measures super effectiveness given base stat types


#endif // GUARD_FIELD_SPECIALS_H
