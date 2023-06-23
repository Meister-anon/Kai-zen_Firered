#ifndef GUARD_BATTLE_SCRIPT_COMMANDS_H
#define GUARD_BATTLE_SCRIPT_COMMANDS_H

#include "global.h"


#define STAT_CHANGE_WORKED      0
#define STAT_CHANGE_DIDNT_WORK  1

#define WINDOW_CLEAR            0x1
#define WINDOW_x80              0x80

void SetMoveEffect(bool32 primary, u32 certain);
bool8 UproarWakeUpCheck(u8 battlerId);
u8 AI_TypeCalc(u16 move, u16 targetSpecies, u16 targetAbility);	//return value is u8 so function can stay u8, even if all elements aren't
u8 TypeCalc(u16 move, u8 attacker, u8 defender);
s32 AI_CalcDmgFormula(u8 attacker, u8 defender);
bool32 IsMonGettingExpSentOut(void);
void BattleCreateYesNoCursorAt(void);
void BattleDestroyYesNoCursorAt(void);
bool32 CanBattlerSwitch(u32 battlerId);
void HandleBattleWindow(u8 xStart, u8 yStart, u8 xEnd, u8 yEnd, u8 flags);
u8 GetBattlerTurnOrderNum(u8 battlerId);
void BufferMoveToLearnIntoBattleTextBuff2(void);
bool32 DoesSubstituteBlockMove(u8 battlerAtk, u8 battlerDef, u32 move);
bool32 DoesDisguiseBlockMove(u8 battlerAtk, u8 battlerDef, u32 move);
bool32 NoAliveMonsForEitherParty(void);
bool32 CanUseLastResort(u8 battlerId);
u32 IsFlowerVeilProtected(u32 battler);
u32 IsLeafGuardProtected(u32 battler);
bool32 IsShieldsDownProtected(u32 battler);
u32 IsAbilityStatusProtected(u32 battler);
bool32 TryResetBattlerStatChanges(u8 battler);
bool32 CanCamouflage(u8 battlerId);
void StealTargetItem(u8 battlerStealer, u8 battlerItem);
bool32 CanStealItem(u8 battlerStealing, u8 battlerItem, u16 item);
u32 GetHighestStatId(u32 battlerId);
s32 AICalcCritChance(u8 battlerAtk, u8 battlerDef, u32 move, bool32 recordAbility);
u16 GetNaturePowerMove(void);
s8 GetInverseCritChance(u8 battlerAtk, u8 battlerDef, u32 move);

s32 CalculateMoveDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, s32 fixedBasePower, bool32 isCrit, bool32 randomFactor, bool32 updateFlags);

const u16 gCriticalHitChance[] = { 16, 6, 4, 3, 1 };	//made global, so can run in ai file

extern void (* const gBattleScriptingCommandsTable[])(void);

#endif // GUARD_BATTLE_SCRIPT_COMMANDS_H
