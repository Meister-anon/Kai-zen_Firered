#ifndef GUARD_BATTLE_UTIL_H
#define GUARD_BATTLE_UTIL_H

#include "global.h"

#define MOVE_LIMITATION_ZEROMOVE                (1 << 0)
#define MOVE_LIMITATION_PP                      (1 << 1)
#define MOVE_LIMITATION_DISABLED                (1 << 2)
#define MOVE_LIMITATION_TORMENTED               (1 << 3)
#define MOVE_LIMITATION_TAUNT                   (1 << 4)
#define MOVE_LIMITATION_IMPRISON                (1 << 5)
#define MOVE_LIMITATIONS_ALL                    0xFF

#define ABILITYEFFECT_ON_SWITCHIN                0x0
#define ABILITYEFFECT_ENDTURN                    0x1
#define ABILITYEFFECT_MOVES_BLOCK                0x2
#define ABILITYEFFECT_ABSORBING                  0x3
#define ABILITYEFFECT_MOVE_END_ATTACKER          0x4
#define ABILITYEFFECT_MOVE_END                   0x5
#define ABILITYEFFECT_IMMUNITY                   0x6
#define ABILITYEFFECT_FORECAST                   0x7
#define ABILITYEFFECT_SYNCHRONIZE                0x8
#define ABILITYEFFECT_ATK_SYNCHRONIZE            0x9
#define ABILITYEFFECT_INTIMIDATE1                0xA
#define ABILITYEFFECT_INTIMIDATE2                0xB
#define ABILITYEFFECT_TRACE                      0xC
#define ABILITYEFFECT_CHECK_OTHER_SIDE           0xD
#define ABILITYEFFECT_CHECK_BATTLER_SIDE         0xE
#define ABILITYEFFECT_FIELD_SPORT                0xF
#define ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER 0x10 // TODO: Is it correct? 
#define ABILITYEFFECT_COUNT_OTHER_SIDE           0x11
#define ABILITYEFFECT_COUNT_BATTLER_SIDE         0x12
#define ABILITYEFFECT_COUNT_ON_FIELD             0x13
#define ABILITYEFFECT_CHECK_ON_FIELD             0x14
#define ABILITYEFFECT_NEUTRALIZINGGAS			 0x15  //swapped what was a nuisance ability test
#define ABILITYEFFECT_MOVE_END_OTHER			 0x16
#define ABILITYEFFECT_SWITCH_IN_ABILITIES		 0x17   //realized ability battle effects function doesn't really separate blocks well, so added more for better organization
#define ABILITYEFFECT_SWITCH_IN_TERRAIN_ABILITY	 0x18   //nvm can't do more as new block would require new switch...and would break switch in effects i beleive
//#define ABILITYEFFECT_CUPIDSARROW				 0x15  //1st attempted implementation realized goes in switchin don't need new effect
#define ABILITYEFFECT_MUD_SPORT                  0xFC	//actually potentially does as trace and intimidate have them? look over implementation again
#define ABILITYEFFECT_WATER_SPORT                0xFD
//figure out what this does, adn check any limitations
//I want to redo tererain graphic for something more subtle
//instead of everything glowing display graphic template that's fitting
//over/inside the mon circle, so will only be noticeable from enemy side
//i.e sparks tags for electric terrain etc.
#define ABILITYEFFECT_SWITCH_IN_TERRAIN          0xFF
#define ABILITYEFFECT_SWITCH_IN_WEATHER          0xFE   //sets battle weather from map conditions, nothing to do with ability

#define ABILITY_ON_OPPOSING_FIELD(battlerId, abilityId)(AbilityBattleEffects(ABILITYEFFECT_CHECK_OTHER_SIDE, battlerId, abilityId, 0, 0))
#define ABILITY_ON_FIELD(abilityId)(AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, abilityId, 0, 0))
#define ABILITY_ON_FIELD2(abilityId)(AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, abilityId, 0, 0))

#define IS_WHOLE_SIDE_ALIVE(battler)((IsBattlerAlive(battler) && IsBattlerAlive(BATTLE_PARTNER(battler))))


#define ITEMEFFECT_ON_SWITCH_IN                 0x0
#define ITEMEFFECT_NORMAL                       0x1
#define ITEMEFFECT_MOVE_END                     0x3
#define ITEMEFFECT_KINGSROCK          0x4		//removed shell bell from this effect and renamed to just kingsrock
#define ITEMEFFECT_TARGET                       0x5
#define ITEMEFFECT_ORBS                         0x6
#define ITEMEFFECT_LIFEORB_SHELLBELL            0x7		
#define ITEMEFFECT_BATTLER_MOVE_END             0x8 // move end effects for just the battler, not whole field

#define WEATHER_HAS_EFFECT ((!AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_AIR_LOCK, 0, 0)))
#define WEATHER_HAS_EFFECT2 ((!AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_AIR_LOCK, 0, 0)))

#define BS_GET_TARGET                   0
#define BS_GET_ATTACKER                 1
#define BS_GET_EFFECT_BANK              2
#define BS_GET_SCRIPTING_BANK           10
#define BS_GET_PLAYER1                  11
#define BS_GET_OPPONENT1                12
#define BS_GET_PLAYER2                  13
#define BS_GET_OPPONENT2                14

u8 GetBattlerForBattleScript(u8 caseId);

void PressurePPLose(u8 target, u8 attacker, u16 move);
void PressurePPLoseOnUsingImprison(u8 attacker);
void PressurePPLoseOnUsingPerishSong(u8 attacker);
void MarkAllBattlersForControllerExec(void);
void MarkBattlerForControllerExec(u8 battlerId);
void sub_8017298(u8 arg0);
void CancelMultiTurnMoves(u8 battler);
bool8 WasUnableToUseMove(u8 battler);
u16 HeldItemSearch(void);
void PrepareStringBattle(u16 stringId, u8 battler);
void ResetSentPokesToOpponentValue(void);
void sub_8017434(u8 battler);
void UpdateSentPokesToOpponentValue(u8 battler);
void BattleScriptPush(const u8 *bsPtr);
void BattleScriptPushCursor(void);
void BattleScriptPop(void);
u8 TrySetCantSelectMoveBattleScript(void);
u8 CheckMoveLimitations(u8 battlerId, u8 unusableMoves, u8 check);
bool8 AreAllMovesUnusable(void);
u8 GetImprisonedMovesCount(u8 battlerId, u16 move);
u8 DoFieldEndTurnEffects(void);
s32 GetDrainedBigRootHp(u32 battler, s32 hp);
u8 DoBattlerEndTurnEffects(void);
bool8 HandleWishPerishSongOnTurnEnd(void);
bool8 HandleFaintedMonActions(void);
void TryClearRageStatuses(void);
u8 AtkCanceller_UnableToUseMove(void);
u8 AtkCanceller_UnableToUseMove2(void);
bool8 IsFloatingSpecies(u8 battlerId);
bool8 IsBattlerGrounded(u8 battlerId);
bool8 HasNoMonsToSwitch(u8 battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2);
bool32 TryChangeBattleWeather(u8 battler, u32 weatherEnumId, bool32 viaAbility);
static bool32 TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer);
static bool32 ShouldChangeFormHpBased(u32 battler);
static u8 ForewarnChooseMove(u32 battler);
u8 CastformDataTypeChange(u8 battler);
u8 AbilityBattleEffects(u8 caseID, u8 battler, u16 ability, u8 special, u16 moveArg);
void BattleScriptExecute(const u8 *BS_ptr);
void BattleScriptPushCursorAndCallback(const u8 *BS_ptr);
u8 ItemBattleEffects(u8 caseID, u8 battlerId, bool8 moveTurn);
void ClearFuryCutterDestinyBondGrudge(u8 battlerId);
void HandleAction_RunBattleScript(void);
u8 GetMoveTarget(u16 move, u8 setTarget);
u8 IsMonDisobedient(void);
bool32 SetIllusionMon(struct Pokemon *mon, u32 battlerId);
u32 GetBattleMoveSplit(u32 moveId);
bool8 IsBattlerAlive(u8 battlerId);
u32 GetBattlerAbility(u8 battlerId);
u32 GetBattlerWeight(u8 battlerId);
u16 GetMegaEvolutionSpecies(u16 preEvoSpecies, u16 heldItemId);
u16 GetWishMegaEvolutionSpecies(u16 preEvoSpecies, u16 moveId1, u16 moveId2, u16 moveId3, u16 moveId4);
bool32 CanMegaEvolve(u8 battlerId);
void UndoMegaEvolution(u32 monId);
void UndoFormChange(u32 monId, u32 side);
bool32 DoBattlersShareType(u32 battler1, u32 battler2);
bool32 CanBattlerEscape(u32 battlerId);
u32 IsAbilityPreventingEscape(u32 battlerId);
u32 IsAbilityOnFieldExcept(u32 battlerId, u32 ability);
u32 IsAbilityOnField(u32 ability);
u32 GetBattlerHoldEffect(u8 battlerId, bool32 checkNegating);
u32 GetBattlerHoldEffectParam(u8 battlerId);
bool8 IsMoveMakingContact(u16 move, u8 battlerAtk); //made bool8 since its just a true false return
bool8 CanBattlerGetOrLoseItem(u8 battlerId, u16 itemId); //same as above
struct Pokemon *GetIllusionMonPtr(u32 battlerId);
void ClearIllusionMon(u32 battlerId);
bool32 SetIllusionMon(struct Pokemon *mon, u32 battlerId);
u32 IsAbilityOnSide(u32 battlerId, u32 ability);
u32 IsAbilityOnOpposingSide(u32 battlerId, u32 ability);
u32 DoesSideHaveAbility(u32 battlerId, u32 ability); // //adapted abilityonside function that doesn't use getbattlerability
bool32 CanFling(u8 battlerId);
bool32 IsRolePlayBannedAbilityAtk(u16 ability);  //looping array kept 32
bool32 IsRolePlayBannedAbility(u16 ability);
bool32 IsSkillSwapBannedAbility(u16 ability);
bool32 IsWorrySeedBannedAbility(u16 ability);
bool32 IsGastroAcidBannedAbility(u16 ability);
bool32 IsEntrainmentBannedAbilityAttacker(u16 ability);
bool32 IsEntrainmentTargetOrSimpleBeamBannedAbility(u16 ability);
bool32 IsBattlerTerrainAffected(u8 battlerId, u32 terrainFlag);
bool32 CanSleep(u8 battlerId);
bool32 CanPoisonType(u8 battlerAttacker, u8 battlerTarget);
bool32 CanBePoisoned(u8 battlerAttacker, u8 battlerTarget); //actually needs to be different
bool32 CanBeBurned(u8 battlerId);
bool32 CanBeParalyzed(u8 battlerId);
bool32 CanBeFrozen(u8 battlerId);
bool32 CanBeConfused(u8 battlerId);
bool32 HasEnoughHpToEatBerry(u8 battlerId, u32 hpFraction, u16 itemId);
bool32 BlocksPrankster(u16 move, u8 battlerPrankster, u8 battlerDef, bool32 checkTarget);
bool32 CompareStat(u8 battlerId, u8 statId, u8 cmpTo, u8 cmpKind);
bool32 IsBattlerWeatherAffected(u8 battlerId, u32 weatherFlags);
bool32 TryRoomService(u8 battlerId);
bool32 TestSheerForceFlag(u8 battler, u16 move);
u8 TryHandleSeed(u8 battler, u32 terrainFlag, u8 statId, u16 itemId, bool32 execute);
void TryToRevertMimicry(void);
void TryToApplyMimicry(u8 battlerId, bool8 various);
void RestoreBattlerOriginalTypes(u8 battlerId);
void ResetFuryCutterCounter(u8 battlerId);
void MulModifier(u16 *modifier, u16 val);
u32 ApplyModifier(u16 modifier, u32 val);
bool32 UnnerveOn(u32 battlerId, u32 itemId);
void TrySaveExchangedItem(u8 battlerId, u16 stolenItem);
u32 GetBattlerMoveTargetType(u8 battlerId, u16 move); //need port these two fully
bool32 CanTargetBattler(u8 battlerAtk, u8 battlerDef, u16 move);
//learned defined need be on one line, this should be logic for thawing i.e remove frozen status
#define THAW_CONDITION ((gCurrentMove == MOVE_SCALD) || ((gBattleMoves[gCurrentMove].type == TYPE_FIRE) && (gBattleMoves[gCurrentMove].power >= 60 || gDynamicBasePower >= 60) && gCurrentMove != MOVE_FIRE_FANG))

// percent in UQ_4_12 format
const u16 sPercentToModifier[] =
{
    UQ_4_12(0.00), // 0
    UQ_4_12(0.01), // 1
    UQ_4_12(0.02), // 2
    UQ_4_12(0.03), // 3
    UQ_4_12(0.04), // 4
    UQ_4_12(0.05), // 5
    UQ_4_12(0.06), // 6
    UQ_4_12(0.07), // 7
    UQ_4_12(0.08), // 8
    UQ_4_12(0.09), // 9
    UQ_4_12(0.10), // 10
    UQ_4_12(0.11), // 11
    UQ_4_12(0.12), // 12
    UQ_4_12(0.13), // 13
    UQ_4_12(0.14), // 14
    UQ_4_12(0.15), // 15
    UQ_4_12(0.16), // 16
    UQ_4_12(0.17), // 17
    UQ_4_12(0.18), // 18
    UQ_4_12(0.19), // 19
    UQ_4_12(0.20), // 20
    UQ_4_12(0.21), // 21
    UQ_4_12(0.22), // 22
    UQ_4_12(0.23), // 23
    UQ_4_12(0.24), // 24
    UQ_4_12(0.25), // 25
    UQ_4_12(0.26), // 26
    UQ_4_12(0.27), // 27
    UQ_4_12(0.28), // 28
    UQ_4_12(0.29), // 29
    UQ_4_12(0.30), // 30
    UQ_4_12(0.31), // 31
    UQ_4_12(0.32), // 32
    UQ_4_12(0.33), // 33
    UQ_4_12(0.34), // 34
    UQ_4_12(0.35), // 35
    UQ_4_12(0.36), // 36
    UQ_4_12(0.37), // 37
    UQ_4_12(0.38), // 38
    UQ_4_12(0.39), // 39
    UQ_4_12(0.40), // 40
    UQ_4_12(0.41), // 41
    UQ_4_12(0.42), // 42
    UQ_4_12(0.43), // 43
    UQ_4_12(0.44), // 44
    UQ_4_12(0.45), // 45
    UQ_4_12(0.46), // 46
    UQ_4_12(0.47), // 47
    UQ_4_12(0.48), // 48
    UQ_4_12(0.49), // 49
    UQ_4_12(0.50), // 50
    UQ_4_12(0.51), // 51
    UQ_4_12(0.52), // 52
    UQ_4_12(0.53), // 53
    UQ_4_12(0.54), // 54
    UQ_4_12(0.55), // 55
    UQ_4_12(0.56), // 56
    UQ_4_12(0.57), // 57
    UQ_4_12(0.58), // 58
    UQ_4_12(0.59), // 59
    UQ_4_12(0.60), // 60
    UQ_4_12(0.61), // 61
    UQ_4_12(0.62), // 62
    UQ_4_12(0.63), // 63
    UQ_4_12(0.64), // 64
    UQ_4_12(0.65), // 65
    UQ_4_12(0.66), // 66
    UQ_4_12(0.67), // 67
    UQ_4_12(0.68), // 68
    UQ_4_12(0.69), // 69
    UQ_4_12(0.70), // 70
    UQ_4_12(0.71), // 71
    UQ_4_12(0.72), // 72
    UQ_4_12(0.73), // 73
    UQ_4_12(0.74), // 74
    UQ_4_12(0.75), // 75
    UQ_4_12(0.76), // 76
    UQ_4_12(0.77), // 77
    UQ_4_12(0.78), // 78
    UQ_4_12(0.79), // 79
    UQ_4_12(0.80), // 80
    UQ_4_12(0.81), // 81
    UQ_4_12(0.82), // 82
    UQ_4_12(0.83), // 83
    UQ_4_12(0.84), // 84
    UQ_4_12(0.85), // 85
    UQ_4_12(0.86), // 86
    UQ_4_12(0.87), // 87
    UQ_4_12(0.88), // 88
    UQ_4_12(0.89), // 89
    UQ_4_12(0.90), // 90
    UQ_4_12(0.91), // 91
    UQ_4_12(0.92), // 92
    UQ_4_12(0.93), // 93
    UQ_4_12(0.94), // 94
    UQ_4_12(0.95), // 95
    UQ_4_12(0.96), // 96
    UQ_4_12(0.97), // 97
    UQ_4_12(0.98), // 98
    UQ_4_12(0.99), // 99
    UQ_4_12(1.00), // 100
};

#endif // GUARD_BATTLE_UTIL_H
