#ifndef GUARD_BATTLE_SCRIPTS_H
#define GUARD_BATTLE_SCRIPTS_H

#include "global.h"

extern const u8 BattleScript_HitFromCritCalc[]; //only defined because its refered to in function
extern const u8 BattleScript_EffectWithChance[]; //putting more emerald ports below this
extern const u8 BattleScript_SideStatusWoreOff[];
extern const u8 BattleScript_NeutralizingGasExits[];
extern const u8 BattleScript_StenchExits[];
extern const u8 BattleScript_ToxicSpikesFree[];
extern const u8 BattleScript_StickyWebFree[];
extern const u8 BattleScript_StealthRockFree[];
extern const u8 BattleScript_MegaEvolution[];
extern const u8 BattleScript_WishMegaEvolution[];
extern const u8 BattleScript_AttackerAbilityStatRaise[];
extern const u8 BattleScript_AttackerAbilityStatRaiseEnd3[];
extern const u8 BattleScript_TargetAbilityStatRaiseRet[];
extern const u8 BattleScript_RaiseStatOnFaintingTarget[];
extern const u8 BattleScript_ScriptingAbilityStatRaise[];
extern const u8 BattleScript_PrimalReversion[];
extern const u8 BattleScript_TotemVar[];
extern const u8 BattleScript_TotemFlaredToLife[];
extern const u8 BattleScript_BerryStatRaiseRet[];
extern const u8 BattleScript_MicleBerryActivateEnd2[];
extern const u8 BattleScript_MicleBerryActivateRet[];
extern const u8 BattleScript_JabocaRowapBerryActivates[];
extern const u8 BattleScript_BattleBondActivatesOnMoveEndAttacker[];
extern const u8 BattleScript_BrickBreakWithScreens[];
extern const u8 BattleScript_BrickBreakNoScreens[];
extern const u8 BattleScript_MoveEnd[];
extern const u8 BattleScript_MakeMoveMissed[];
extern const u8 BattleScript_PrintMoveMissed[];
extern const u8 BattleScript_MoveMissedPause[];
extern const u8 BattleScript_MoveMissed[];
extern const u8 BattleScript_ButItFailed[];
extern const u8 BattleScript_StatUp[];
extern const u8 BattleScript_StatDown[];
extern const u8 BattleScript_AlreadyAtFullHp[];
extern const u8 BattleScript_PresentHealTarget[];
extern const u8 BattleScript_ReturnAlreadyAtFullHp[];  //for present
extern const u8 BattleScript_MoveUsedMustRecharge[];
extern const u8 BattleScript_SkyAttackTurn2[];
extern const u8 BattleScript_FaintAttacker[];
extern const u8 BattleScript_FaintTarget[];
extern const u8 BattleScript_GiveExp[];
extern const u8 BattleScript_HandleFaintedMon[];
extern const u8 BattleScript_LocalTrainerBattleWon[];
extern const u8 BattleScript_LocalTwoTrainersDefeated[];
extern const u8 BattleScript_LocalBattleWonLoseTexts[];
extern const u8 BattleScript_LocalBattleWonReward[];
extern const u8 BattleScript_PayDayMoneyAndPickUpItems[];
extern const u8 BattleScript_LocalBattleLost[];
extern const u8 BattleScript_LocalBattleLostPrintWhiteOut[];
extern const u8 BattleScript_LocalBattleLostEnd[];
extern const u8 BattleScript_CheckDomeDrew[];
//extern const u8 BattleScript_LinkBattleWonOrLost[];
extern const u8 BattleScript_BattleTowerTrainerBattleWon[];
extern const u8 BattleScript_SmokeBallEscape[];
extern const u8 BattleScript_RanAwayUsingMonAbility[];
extern const u8 BattleScript_GotAwaySafely[];
extern const u8 BattleScript_WildMonFled[];
extern const u8 BattleScript_PrintCantRunFromTrainer[];
extern const u8 BattleScript_PrintFailedToRunString[];
extern const u8 BattleScript_PrintCantEscapeFromBattle[];
extern const u8 BattleScript_PrintFullBox[];
extern const u8 BattleScript_ActionSwitch[];
extern const u8 BattleScript_Pausex20[];
extern const u8 BattleScript_Pausex40[];
extern const u8 BattleScript_LevelUp[];
extern const u8 BattleScript_RainContinuesOrEnds[];
extern const u8 BattleScript_DamagingWeatherContinues[];
extern const u8 BattleScript_SandStormHailEnds[];
extern const u8 BattleScript_SunlightContinues[];
extern const u8 BattleScript_SunlightFaded[];
extern const u8 BattleScript_OverworldWeatherStarts[];
extern const u8 BattleScript_OverworldTerrain[];
extern const u8 BattleScript_SideStatusWoreOff[];
extern const u8 BattleScript_SideStatusWoreOffReturn[];
extern const u8 BattleScript_SafeguardProtected[];
extern const u8 BattleScript_SafeguardEnds[];
extern const u8 BattleScript_LeechSeedTurnDrain[];
extern const u8 BattleScript_BideStoringEnergy[];
extern const u8 BattleScript_BideAttack[];
extern const u8 BattleScript_BideNoEnergyToAttack[];
extern const u8 BattleScript_ButItFailedAtkStringPpReduce[];
extern const u8 BattleScript_SuccessForceOut[];
extern const u8 BattleScript_WeaknessPolicy[];
extern const u8 BattleScript_TargetItemStatRaise[];
extern const u8 BattleScript_AttackerItemStatRaise[];
extern const u8 BattleScript_MistProtected[];
extern const u8 BattleScript_RageIsBuilding[];
extern const u8 BattleScript_AttackerRageBuilding[];
extern const u8 BattleScript_RageEnds[];
extern const u8 BattleScript_MoveUsedIsDisabled[];
extern const u8 BattleScript_MoveUsedIsInthralled[];
extern const u8 BattleScript_SelectingDisabledMove[];
extern const u8 BattleScript_SelectingInthralledMove[];
extern const u8 BattleScript_DisabledNoMore[];
extern const u8 BattleScript_InthralledNoMore[];
extern const u8 BattleScript_SelectingDisabledMoveInPalace[];
extern const u8 BattleScript_SelectingUnusableMoveInPalace[];
extern const u8 BattleScript_EncoredNoMore[];
extern const u8 BattleScript_WaterSportEnds[];
extern const u8 BattleScript_MudSportEnds[];
extern const u8 BattleScript_DestinyBondTakesLife[];
extern const u8 BattleScript_SpikesOnAttacker[];
extern const u8 BattleScript_SpikesOnTarget[];
extern const u8 BattleScript_SpikesOngBank1[];
extern const u8 BattleScript_DmgHazardsOnTarget[];
extern const u8 BattleScript_DmgHazardsOnAttacker[];
extern const u8 BattleScript_DmgHazardsOnFaintedBattler[];
extern const u8 BattleScript_PerishSongTakesLife[];
extern const u8 BattleScript_PerishSongCountGoesDown[];
extern const u8 BattleScript_AllStatsUp[];
extern const u8 BattleScript_StatDownCantGoLower[];
extern const u8 BattleScript_StatUpCantGoHigher[];
extern const u8 BattleScript_RapidSpinAway[];
extern const u8 BattleScript_RapidSpinTrapHazardClear[];
extern const u8 BattleScript_LeechSeedFree[];
extern const u8 BattleScript_SpikesFree[];
extern const u8 BattleScript_MonTookFutureAttack[];
extern const u8 BattleScript_NoMovesLeft[];
extern const u8 BattleScript_SelectingMoveWithNoPP[];
extern const u8 BattleScript_NoPPForMove[];
extern const u8 BattleScript_SelectingTormentedMove[];
extern const u8 BattleScript_MoveUsedIsTormented[];
extern const u8 BattleScript_SelectingTormentedMoveInPalace[];
extern const u8 BattleScript_SelectingNotAllowedMoveTaunt[];
extern const u8 BattleScript_SelectingNotAllowedMoveThroatChop[];
extern const u8 BattleScript_MoveUsedIsTaunted[];
extern const u8 BattleScript_SelectingNotAllowedMoveTauntInPalace[];
extern const u8 BattleScript_WishComesTrue[];
extern const u8 BattleScript_IngrainTurnHeal[];
extern const u8 BattleScript_AtkDefDown[];
extern const u8 BattleScript_KnockedOff[];
extern const u8 BattleScript_MoveUsedIsImprisoned[];
extern const u8 BattleScript_SelectingImprisonedMove[];
extern const u8 BattleScript_SelectingImprisonedMoveInPalace[];
extern const u8 BattleScript_GrudgeTakesPp[];
extern const u8 BattleScript_SelectingNotAllowedMoveGravity[];
extern const u8 BattleScript_SelectingNotAllowedMoveHealBlock[];
extern const u8 BattleScript_SelectingNotAllowedBelch[];
extern const u8 BattleScript_SelectingNotAllowedStuffCheeks[];
extern const u8 BattleScript_MagicCoatBounce[];
extern const u8 BattleScript_SnatchedMove[];
extern const u8 BattleScript_EnduredMsg[];
extern const u8 BattleScript_OneHitKOMsg[];
extern const u8 BattleScript_SturdiedMsg[];
extern const u8 BattleScript_AttackerSturdiedMsg[];
extern const u8 BattleScript_SAtkDown2[];
extern const u8 BattleScript_FocusPunchSetUp[];
extern const u8 BattleScript_MoveUsedIsAsleep[];
extern const u8 BattleScript_MoveUsedWokeUp[];
extern const u8 BattleScript_MonWokeUpInUproar[];
extern const u8 BattleScript_StatusInfested[];  //script for playing infest animation
extern const u8 BattleScript_PoisonWorsened[];
extern const u8 BattleScript_PoisonTurnDmg[];
extern const u8 BattleScript_BurnTurnDmg[];
extern const u8 BattleScript_FreezeTurnDmg[];
extern const u8 BattleScript_FrostbiteTurnDmg[];
extern const u8 BattleScript_DefrostBattler_KeepStatus[];
extern const u8 BattleScript_MoveUsedIsFrozen[];
extern const u8 BattleScript_MoveUsedUnfroze[];
extern const u8 BattleScript_DefrostedViaFireMove[];
extern const u8 BattleScript_MoveUsedIsParalyzed[];
extern const u8 BattleScript_MovePressureCanceler[];
extern const u8 BattleScript_AbilityEffectIronWill[];
extern const u8 BattleScript_MoveUsedFlinched[];
extern const u8 BattleScript_PrintUproarOverTurns[];
extern const u8 BattleScript_ThrashConfuses[];
extern const u8 BattleScript_MoveUsedIsConfused[];
extern const u8 BattleScript_MoveUsedIsConfusedNoMore[];
extern const u8 BattleScript_PrintPayDayMoneyString[];
extern const u8 BattleScript_WrapTurnDmg[];
extern const u8 BattleScript_WrapEnds[];
extern const u8 BattleScript_MoveUsedIsInLove[];
extern const u8 BattleScript_MoveUsedIsInLoveCantAttack[];
extern const u8 BattleScript_MoveUsedIsParalyzedCantAttack[];
extern const u8 BattleScript_NightmareTurnDmg[];
extern const u8 BattleScript_CurseTurnDmg[];
extern const u8 BattleScript_TargetPRLZHeal[];
extern const u8 BattleScript_TargetWokeUp[];
extern const u8 BattleScript_TargetBurnHeal[];
extern const u8 BattleScript_MoveEffectSleep[];
extern const u8 BattleScript_MoveEffectAttract[]; //don't know  if work right
extern const u8 BattleScript_YawnMakesAsleep[];
extern const u8 BattleScript_SleepHealing[];
extern const u8 BattleScript_MoveEffectPoison[];
extern const u8 BattleScript_MoveEffectBurn[];
extern const u8 BattleScript_MoveEffectFreeze[];
extern const u8 BattleScript_MoveEffectParalysis[];
extern const u8 BattleScript_MoveEffectUproar[];
extern const u8 BattleScript_MoveEffectToxic[];
extern const u8 BattleScript_MoveEffectPayDay[];
extern const u8 BattleScript_MoveEffectWrap[];
extern const u8 BattleScript_MoveEffectFireSpin[];
extern const u8 BattleScript_MoveEffectClamp[];
extern const u8 BattleScript_MoveEffectWhirlpool[];
extern const u8 BattleScript_MoveEffectSandTomb[];
extern const u8 BattleScript_MoveEffectMagmaStorm[];
extern const u8 BattleScript_MoveEffectInfestation[];
extern const u8 BattleScript_MoveEffectSnapTrap[];
extern const u8 BattleScript_MoveEffectConfusion[];
extern const u8 BattleScript_MoveEffectRecoil[];
extern const u8 BattleScript_DoRecoil[];
extern const u8 BattleScript_RecoilEnd[];
extern const u8 BattleScript_EffectRecoil33WithStatus[];
extern const u8 BattleScript_EffectRecoil50[];
extern const u8 BattleScript_ItemSteal[];
extern const u8 BattleScript_InBattlePickup[];	//new in battle effect for ability pickup, 1 in 3 chance pickup held item and end of turn
extern const u8 BattleScript_DrizzleActivates[];
extern const u8 BattleScript_SpeedBoostActivates[];
extern const u8 BattleScript_DefeatistActivates[];
extern const u8 BattleScript_TraceActivates[];
extern const u8 BattleScript_RainDishActivates[];
extern const u8 BattleScript_HealWithoutMessage[];
extern const u8 BattleScript_SandstreamActivates[];
extern const u8 BattleScript_ShedSkinActivates[];
extern const u8 BattleScript_PurifyingAuraActivates[];
extern const u8 BattleScript_PurifyingAuraActivatesForPartner[];
extern const u8 BattleScript_AuraofLightActivatesForPartner[];
extern const u8 BattleScript_WeatherFormChanges[];
extern const u8 BattleScript_WeatherFormChangesLoop[];
extern const u8 BattleScript_CastformChange[];
extern const u8 BattleScript_DroughtActivates[];
extern const u8 BattleScript_DesolateLandActivates[];
extern const u8 BattleScript_PrimordialSeaActivates[];
extern const u8 BattleScript_DeltaStreamActivates[];
extern const u8 BattleScript_TookAttack[];
extern const u8 BattleScript_SturdyPreventsOHKO[];
extern const u8 BattleScript_DampStopsExplosion[];
extern const u8 BattleScript_DampPreventsAftermath[];
extern const u8 BattleScript_MoveHPDrain_PPLoss[];
extern const u8 BattleScript_MoveHPDrain[];
extern const u8 BattleScript_MoveStatDrain_PPLoss[];
extern const u8 BattleScript_MoveStatDrain[];
extern const u8 BattleScript_MonMadeMoveUseless_PPLoss[];
extern const u8 BattleScript_MonMadeMoveUseless[];
extern const u8 BattleScript_FlashFireBoost_PPLoss[];
extern const u8 BattleScript_FlashFireBoost[];
extern const u8 BattleScript_AbilityNoStatLoss[];
extern const u8 BattleScript_NotAffected[]; //added for status type efect changes
extern const u8 BattleScript_BRNPrevention[];
extern const u8 BattleScript_PRLZPrevention[];
extern const u8 BattleScript_PSNPrevention[];
extern const u8 BattleScript_AbilityPreventsMoodShift[];
extern const u8 BattleScript_AbilityFemmeFatale[];
extern const u8 BattleScript_FlinchPrevention[];
extern const u8 BattleScript_OwnTempoPrevents[];
extern const u8 BattleScript_SoundproofProtected[];
extern const u8 BattleScript_AbilityNoSpecificStatLoss[];
extern const u8 BattleScript_MirrorArmorAttackAnimation[];
extern const u8 BattleScript_MirrorArmorReflect[];
extern const u8 BattleScript_EmpathAttackAnimation[];
extern const u8 BattleScript_EmpathActivates[];
extern const u8 BattleScript_EmpathicCurseActivates[];
extern const u8 BattleScript_RisingPhoenixActivates[];
extern const u8 BattleScript_StickyHoldActivates[];
extern const u8 BattleScript_StickyHoldKnockoff[];
extern const u8 BattleScript_ColorChangeActivates[];
extern const u8 BattleScript_RoughSkinActivates[];
extern const u8 BattleScript_HurtAttacker[];
extern const u8 BattleScript_AttackerRemoveType[];
extern const u8 BattleScript_CuteCharmActivates[];
extern const u8 BattleScript_CupidsArrowActivates[];
extern const u8 BattleScript_ApplySecondaryEffect[];
extern const u8 BattleScript_DefSpDefDownRet[];
extern const u8 BattleScript_DefSpDefDownTrySpDef[];
extern const u8 BattleScript_DefSpDefDown[];
extern const u8 BattleScript_DefDownSpeedUp[];
extern const u8 BattleScript_BufferEndTurn[];
extern const u8 BattleScript_SynchronizeActivates[];
extern const u8 BattleScript_NoItemSteal[];
extern const u8 BattleScript_AbilityCuredStatus[];
extern const u8 BattleScript_IgnoresAndUsesRandomMove[];    
extern const u8 BattleScript_PanickedAndUsesRandomMove[];
extern const u8 BattleScript_BindDoCalledMove[];
extern const u8 BattleScript_BindMoveRanoutofPP[];
extern const u8 BattleScript_IllusionOff[];
extern const u8 BattleScript_TwoTurnMovesSecondTurn[];
extern const u8 BattleScript_EffectTwoTurnsAttackFreezeShock[];
extern const u8 BattleScript_EffectTwoTurnsAttackIceBurn[];
extern const u8 BattleScript_EffectTwoTurnsAttackContinue[];
extern const u8 BattleScript_EffectTwoTurnsAttack[];
extern const u8 BattleScript_CottonDownReturn[];
extern const u8 BattleScript_CottonDownLoopIncrement[];
extern const u8 BattleScript_CottonDownTargetSpeedCantGoLower[];
extern const u8 BattleScript_CottonDownLoop[];
extern const u8 BattleScript_CottonDownActivates[];
extern const u8 BattleScript_MoveUsedLoafingAround[];
extern const u8 BattleScript_MoveUsedGravityPrevents[];
extern const u8 BattleScript_MoveUsedHealBlockPrevents[];
extern const u8 BattleScript_SlowStartEnds[];
extern const u8 BattleScript_AquaRingHeal[];
extern const u8 BattleScript_TurnHeal[];
extern const u8 BattleScript_AnticipationActivates[];
extern const u8 BattleScript_AftermathDmg[];
extern const u8 BattleScript_AftermathOnSwitch[];
extern const u8 BattleScript_MoveEffectClearSmog[];
extern const u8 BattleScript_ToxicOrb[];
extern const u8 BattleScript_FlameOrb[];
extern const u8 BattleScript_DancerActivates[];
extern const u8 BattleScript_RockyHelmetActivates[];
extern const u8 BattleScript_RockyHelmetActivatesDmg[];
extern const u8 BattleScript_BallFetch[];
extern const u8 BattleScript_CudChewActivates[];    //is gen 9 but added for tauros plan addition
extern const u8 BattleScript_AttackWeakenedByStrongWinds[];
extern const u8 BattleScript_BlockedByPrimalWeatherRet[];
extern const u8 BattleScript_BlockedByPrimalWeatherEnd3[];
extern const u8 BattleScript_SandSpitActivates[];
extern const u8 BattleScript_PerishBodyActivates[];
extern const u8 BattleScript_GulpMissileGulping[];
extern const u8 BattleScript_GulpMissileGorging[];
extern const u8 BattleScript_MoveEffectSmackDown[];
extern const u8 BattleScript_MoveEffectFlameBurst[];
extern const u8 BattleScript_MoveUsedPsychicTerrainPrevents[];
extern const u8 BattleScript_MoveUsedPowder[];
extern const u8 BattleScript_PowderMoveNoEffect[];
extern const u8 BattleScript_GrassyTerrainHeals[];
extern const u8 BattleScript_SpikyShieldEffect[];
extern const u8 BattleScript_KingsShieldEffect[];
extern const u8 BattleScript_BanefulBunkerEffect[];
extern const u8 BattleScript_ForceRandomSwitch[];
extern const u8 BattleScript_PoisonHealActivates[];
extern const u8 BattleScript_SwitchInAbilityMsg[];
extern const u8 BattleScript_SwitchInAbilityMsgRet[];
extern const u8 BattleScript_ToxicSpikesPoisoned[];
extern const u8 BattleScript_ToxicSpikesAbsorbed[];
extern const u8 BattleScript_StickyWebOnSwitchIn[];
extern const u8 BattleScript_AbilityRaisesDefenderStat[];
extern const u8 BattleScript_AbilityPopUp[];
extern const u8 BattleScript_MoodyActivates[];
extern const u8 BattleScript_MoodyLower[];
extern const u8 BattleScript_MoodyEnd[];
extern const u8 BattleScript_EmergencyExit[];
extern const u8 BattleScript_EmergencyExitNoPopUp[];
extern const u8 BattleScript_EmergencyExitRet[];
extern const u8 BattleScript_EmergencyExitWild[];
extern const u8 BattleScript_EmergencyExitWildNoPopUp[];
extern const u8 BattleScript_ReceiverActivates[];
extern const u8 BattleScript_AbilityHpHeal[];
extern const u8 BattleScript_EndTurnAbilityHpHeal[];
extern const u8 BattleScript_CheekPouchActivates[];
extern const u8 BattleScript_HarvestActivates[];
extern const u8 BattleScript_SolarPowerActivates[];
extern const u8 BattleScript_HealerActivates[];
extern const u8 BattleScript_TryAdrenalineOrbRet[];
extern const u8 BattleScript_SnowWarningActivates[];
extern const u8 BattleScript_ElectricSurgeActivates[];
extern const u8 BattleScript_MistySurgeActivates[];
extern const u8 BattleScript_GrassySurgeActivates[];
extern const u8 BattleScript_PsychicSurgeActivates[];
extern const u8 BattleScript_LavaDistortionActivates[];
extern const u8 BattleScript_BadDreamsActivates[];
extern const u8 BattleScript_BadDreamsLoop[];
extern const u8 BattleScript_BadDreamsIncrement[];
extern const u8 BattleScript_BadDreamsEnd[];
extern const u8 BattleScript_DazzlingProtected[];
extern const u8 BattleScript_IceFaceNullsDamage[];
extern const u8 BattleScript_DarkTypePreventsPrankster[];
extern const u8 BattleScript_MoveUsedPsychicTerrainPrevents[];
extern const u8 BattleScript_GrassyTerrainHeals[];
extern const u8 BattleScript_GrassyTerrainLoop[];
extern const u8 BattleScript_GrassyTerrainHpChange[];
extern const u8 BattleScript_GrassyTerrainLoopIncrement[];
extern const u8 BattleScript_GrassyTerrainLoopEnd[];
extern const u8 BattleScript_ProteanActivates[];
extern const u8 BattleScript_CursedBodyActivates[];
extern const u8 BattleScript_MummyActivates[];
extern const u8 BattleScript_WanderingSpiritActivates[];
extern const u8 BattleScript_GooeyActivates[];
extern const u8 BattleScript_TargetsStatWasMaxedOut[];
extern const u8 BattleScript_BattlerAbilityStatRaiseOnSwitchIn[];
extern const u8 BattleScript_TargetAbilityStatRaiseOnMoveEnd[];
extern const u8 BattleScript_WeakArmorActivates[];
extern const u8 BattleScript_WeakArmorDefAnim[];
extern const u8 BattleScript_WeakArmorActivatesSpeed[];
extern const u8 BattleScript_WeakArmorSpeedAnim[];
extern const u8 BattleScript_WeakArmorActivatesEnd[];
extern const u8 BattleScript_FellStingerRaisesStat[];
extern const u8 BattleScript_FellStingerRaisesAtkEnd[];
extern const u8 BattleScript_FriskMsgWithPopup[];
extern const u8 BattleScript_FriskMsg[];
extern const u8 BattleScript_FriskActivates[];
extern const u8 BattleScript_ForgotAndLearnedNewMove[];
extern const u8 BattleScript_ImposterActivates[];
extern const u8 BattleScript_LeafGuardProtects[];
extern const u8 BattleScript_LeafGuardProtectsRet[];
extern const u8 BattleScript_AromaVeilProtects[];
extern const u8 BattleScript_AromaVeilProtectsRet[];
extern const u8 BattleScript_SweetVeilProtects[];
extern const u8 BattleScript_SweetVeilProtectsRet[];
extern const u8 BattleScript_FlowerVeilProtects[];
extern const u8 BattleScript_FlowerVeilProtectsRet[];
extern const u8 BattleScript_EffectPlaceholder[];
extern const u8 BattleScript_ShieldBash[];
extern const u8 BattleScript_SetSpikesfromSpikyShield[];
extern const u8 BattleScript_EjectButtonActivates[];
extern const u8 BattleScript_EjectPackActivate_Ret[];
extern const u8 BattleScript_EjectPackActivate_End2[];
extern const u8 BattleScript_EjectPackActivates[];
extern const u8 BattleScript_HitEscapeEnd[];
extern const u8 BattleScript_EffectHitEscape[];
extern const u8 BattleScript_EffectThroatChop[];
extern const u8 BattleScript_ThroatChopEndTurn[];
extern const u8 BattleScript_MoveUsedIsThroatChopPrevented[];
extern const u8 BattleScript_EffectHealBlock[];
extern const u8 BattleScript_CaptivateCheckAcc[];
extern const u8 BattleScript_EffectCaptivate[];
extern const u8 BattleScript_EffectRoost[];
extern const u8 BattleScript_Roosting[];
extern const u8 BattleScript_GravityLoopEnd[];
extern const u8 BattleScript_GravityLoopDrop[];
extern const u8 BattleScript_GravityLoop[];
extern const u8 BattleScript_EffectGravity[];
extern const u8 BattleScript_GravityEnds[];
extern const u8 BattleScript_GroundFlyingEnemywithoutGravity[]; //2x dmg in air flag
extern const u8 BattleScript_EffectMircleEye[];
extern const u8 BattleScript_EffectTailwind[];
extern const u8 BattleScript_TailwindEnds[];
extern const u8 BattleScript_EffectEmbargo[];
extern const u8 BattleScript_EmbargoEndTurn[];
extern const u8 BattleScript_EffectAquaRing[];
extern const u8 BattleScript_EffectMagicRoom[];
extern const u8 BattleScript_MagicRoomEnds[];
extern const u8 BattleScript_EffectWonderRoom[];
extern const u8 BattleScript_WonderRoomEnds[];
extern const u8 BattleScript_EffectTrickRoom[];
extern const u8 BattleScript_TrickRoomEnds[];
extern const u8 BattleScript_EffectMagnetRise[];
extern const u8 BattleScript_EffectToxicSpikes[];
extern const u8 BattleScript_EffectGastroAcid[];
extern const u8 BattleScript_EffectStickyWeb[];
extern const u8 BattleScript_EffectStealthRock[];
extern const u8 BattleScript_StealthRockAbsorb[];
extern const u8 BattleScript_EffectTelekinesis[];
extern const u8 BattleScript_TelekinesisEndTurn[];
extern const u8 BattleScript_GroundFlyingEnemywithoutGravity[];
extern const u8 BattleScript_EffectSpeedSwap[];
extern const u8 BattleScript_EffectGuardSwap[];
extern const u8 BattleScript_EffectPowerSwap[];
extern const u8 BattleScript_EffectHeartSwap[];
extern const u8 BattleScript_EffectGuardSplit[];
extern const u8 BattleScript_EffectPowerSplit[];
extern const u8 BattleScript_EffectWorrySeed[];
extern const u8 BattleScript_EffectHealingWishEnd[];
extern const u8 BattleScript_EffectHealingWishNewMon[];
extern const u8 BattleScript_EffectHealingWish[];
extern const u8 BattleScript_EffectMetalBurst[];
extern const u8 BattleScript_EffectLuckyChant[];
extern const u8 BattleScript_LuckyChantEnds[];
extern const u8 BattleScript_EffectSuckerPunch[];
extern const u8 BattleScript_EffectSimpleBeam[];
extern const u8 BattleScript_EffectEntrainment[];
extern const u8 BattleScript_EffectHealPulse[];
extern const u8 BattleScript_EffectQuash[];
extern const u8 BattleScript_EffectIonDeluge[];
extern const u8 BattleScript_EffectTopsyTurvyWorks[];
extern const u8 BattleScript_EffectTopsyTurvy[];
extern const u8 BattleScript_EffectPsychicTerrain[];
extern const u8 BattleScript_EffectElectricTerrain[];
extern const u8 BattleScript_EffectGrassyTerrain[];
extern const u8 BattleScript_EffectMistyTerrain[];
extern const u8 BattleScript_ElectricTerrainEnds[];
extern const u8 BattleScript_MistyTerrainEnds[];
extern const u8 BattleScript_GrassyTerrainEnds[];
extern const u8 BattleScript_PsychicTerrainEnds[];
extern const u8 BattleScript_AttackAccUpEnd[];
extern const u8 BattleScript_AttackAccUpTrySpDef[];
extern const u8 BattleScript_AttackAccUpDoMoveAnim[];
extern const u8 BattleScript_EffectAttackAccUp[];
extern const u8 BattleScript_AttackSpAttackUpEnd[];
extern const u8 BattleScript_AttackSpAttackUpTrySpAtk[];
extern const u8 BattleScript_AttackSpAttackUpDoMoveAnim[];
extern const u8 BattleScript_EffectAttackSpAttackUp[];
extern const u8 BattleScript_EffectMeFirst[];
extern const u8 BattleScript_EffectSpeedUpHit[];
extern const u8 BattleScript_QuiverDanceEnd[];
extern const u8 BattleScript_QuiverDanceTrySpeed[];
extern const u8 BattleScript_QuiverDanceTrySpDef[];
extern const u8 BattleScript_QuiverDanceDoMoveAnim[];
extern const u8 BattleScript_EffectQuiverDance[];
extern const u8 BattlesScript_RoostEnds[];
extern const u8 BattleScript_EndturnRoost[];
extern const u8 BattleScript_CoilEnd[];
extern const u8 BattleScript_CoilTryAcc[];
extern const u8 BattleScript_CoilTryDef[];
extern const u8 BattleScript_CoilDoMoveAnim[];
extern const u8 BattleScript_EffectCoil[];
extern const u8 BattleScript_ShiftGearEnd[];
extern const u8 BattleScript_ShiftGearTryAtk[];
extern const u8 BattleScript_ShiftGearDoSpeed[];
extern const u8 BattleScript_ShiftGearSpeedBy1[];
extern const u8 BattleScript_ShiftGearDoMoveAnim[];
extern const u8 BattleScript_EffectShiftGear[];
extern const u8 BattleScript_AttackerFormChangeMoveEffect[];
extern const u8 BattleScript_AttackerFormChangeEnd3NoPopup[];
extern const u8 BattleScript_AttackerFormChangeEnd3[];
extern const u8 BattleScript_AttackerFormChange[]; 
extern const u8 BattleScript_TargetFormChange[];
extern const u8 BattleScript_MagicianActivates[];
extern const u8 BattleScript_MagicianSwap[];
extern const u8 BattleScript_SymbiosisActivates[];
extern const u8 BattleScript_MagicCoatBouncePrankster[];
extern const u8 BattleScript_MagicCoatBounce[];
extern const u8 BattleScript_PrintBerryReduceString[];
extern const u8 BattleScript_BerryReduceDmg[];
extern const u8 BattleScript_GemActivates[];
extern const u8 BattleScript_RedCardActivates[];
extern const u8 BattleScript_StickyBarbTransfer[];
extern const u8 BattleScript_BothCanNoLongerEscape[];
extern const u8 BattleScript_PickpocketPrevented[];
extern const u8 BattleScript_Pickpocket[];
extern const u8 BattleScript_GrowthEnd[];
extern const u8 BattleScript_GrowthSpAtk[];
extern const u8 BattleScript_GrowthSpAtk2[];
extern const u8 BattleScript_GrowthTrySpAtk[];
extern const u8 BattleScript_GrowthAtk[];
extern const u8 BattleScript_GrowthAtk2[];
extern const u8 BattleScript_GrowthDoMoveAnim[];
extern const u8 BattleScript_EffectGrowth[];
extern const u8 BattleScript_EffectElectrify[];
extern const u8 BattleScript_EffectReflectType[];
extern const u8 BattleScript_EffectSoak[];
extern const u8 BattleScript_EffectLastResort[];
extern const u8 BattleScript_ShellSmashEnd[];
extern const u8 BattleScript_ShellSmashTrySpeed[];
extern const u8 BattleScript_ShellSmashTrySpAtk[];
extern const u8 BattleScript_ShellSmashTryAttack[];
extern const u8 BattleScript_ShellSmashTrySpDef[];
extern const u8 BattleScript_ShellSmashTryDef[];
extern const u8 BattleScript_EffectShellSmash[];
extern const u8 BattleScript_NobleRoarEnd[];
extern const u8 BattleScript_NobleRoarTryLowerSpAtk[];
extern const u8 BattleScript_NobleRoarDoMoveAnim[];
extern const u8 BattleScript_EffectNobleRoar[];
extern const u8 BattleScript_VenomDrenchEnd[];
extern const u8 BattleScript_VenomDrenchTryLowerSpeed[];
extern const u8 BattleScript_VenomDrenchTryLowerSpAtk[];
extern const u8 BattleScript_VenomDrenchDoMoveAnim[];
extern const u8 BattleScript_EffectVenomDrenchCanBeUsed[];
extern const u8 BattleScript_EffectVenomDrench[];
extern const u8 BattleScript_ToxicThreadTryPsn[];
extern const u8 BattleScript_ToxicThreadPrintString[];
extern const u8 BattleScript_ToxicThreadDoAnim[];
extern const u8 BattleScript_ToxicThreadWorks[];
extern const u8 BattleScript_EffectToxicThread[];
extern const u8 BattleScript_EffectHitSwitchTargetMoveEnd[];
extern const u8 BattleScript_EffectHitSwitchTarget[];
extern const u8 BattleScript_EffectFinalGambit[];
extern const u8 BattleScript_AutotomizeWeightLoss[];
extern const u8 BattleScript_AutotomizePrintString[];
extern const u8 BattleScript_AutotomizeDoAnim[];
extern const u8 BattleScript_AutotomizeAttackAnim[];
extern const u8 BattleScript_EffectAutotomize[];
extern const u8 BattleScript_EffectInstruct[];
extern const u8 BattleScript_CopycatFail[];
extern const u8 BattleScript_EffectCopycat[];
extern const u8 BattleScript_DefogTryHazardsWithAnim[];
extern const u8 BattleScript_DefogTryHazards[];
extern const u8 BattleScript_DefogPrintString[];
extern const u8 BattleScript_DefogDoAnim[];
extern const u8 BattleScript_DefogWorks[];
extern const u8 BattleScript_DefogIfCanClearHazards[];
extern const u8 BattleScript_EffectDefog[];
extern const u8 BattleScript_EffectHitEnemyHealAlly[];
extern const u8 BattleScript_MoveEffectSmackDown[];
extern const u8 BattleScript_EffectSmackDown[];
extern const u8 BattleScript_SynchronoiseNoEffect[];
extern const u8 BattleScript_SynchronoiseMissed[];
extern const u8 BattleScript_SynchronoiseMoveTargetEnd[];
extern const u8 BattleScript_SynchronoiseLoop[];
extern const u8 BattleScript_EffectSynchronoise[];
extern const u8 BattleScript_EffectPsychoShiftCanWork[];
extern const u8 BattleScript_EffectPsychoShift[];
extern const u8 BattleScript_EffectPowerTrick[];
extern const u8 BattleScript_MoveEffectFlameBurst[];
extern const u8 BattleScript_EffectFlameBurst[];
extern const u8 BattleScript_EffectAfterYou[];
extern const u8 BattleScript_EffectBestow[];
extern const u8 BattleScript_RototillerCantRaiseMultipleStats[];
extern const u8 BattleScript_RototillerMoveTargetEnd[];
extern const u8 BattleScript_RototillerTrySpAtk[];
extern const u8 BattleScript_RototillerDoMoveAnim[];
extern const u8 BattleScript_RototillerLoop2[];
extern const u8 BattleScript_RototillerNoEffect[];
extern const u8 BattleScript_RototillerLoop[];
extern const u8 BattleScript_EffectRototiller[];
extern const u8 BattleScript_FlowerShieldMoveTargetEnd[];
extern const u8 BattleScript_FlowerShieldString[];
extern const u8 BattleScript_FlowerShieldDoAnim[];
extern const u8 BattleScript_FlowerShieldLoop2[];
extern const u8 BattleScript_FlowerShieldLoop[];
extern const u8 BattleScript_FlowerShieldLoopStart[];
extern const u8 BattleScript_FlowerShieldIsAnyGrass[];
extern const u8 BattleScript_EffectFlowerShield[];
extern const u8 BattleScript_EffectDefenseUp2Hit[];
extern const u8 BattleScript_EffectThirdType[];
extern const u8 BattleScript_MimicryActivatesEnd3[];
extern const u8 BattleScript_ApplyMimicry[];
extern const u8 BattleScript_EffectFeint[];
extern const u8 BattleScript_MoveEffectFeint[];
extern const u8 BattleScript_HyperspaceFuryRemoveProtect[];
extern const u8 BattleScript_EffectAcupressureTry[];
extern const u8 BattleScript_EffectAcupressure[];
extern const u8 BattleScript_EffectGearUpEnd[];
extern const u8 BattleScript_EffectGearUpLoop[];
extern const u8 BattleScript_EffectGearUpTrySpAtk[];
extern const u8 BattleScript_EffectGearUpSkipAnim[];
extern const u8 BattleScript_EffectGearUpTryAtk[];
extern const u8 BattleScript_EffectGearUpCheckStats[];
extern const u8 BattleScript_EffectGearUpStart[];
extern const u8 BattleScript_EffectGearUp[];
extern const u8 BattleScript_EffectMagneticFluxEnd[];
extern const u8 BattleScript_EffectMagneticFluxLoop[];
extern const u8 BattleScript_EffectMagneticFluxTrySpDef[];
extern const u8 BattleScript_EffectMagneticFluxSkipAnim[];
extern const u8 BattleScript_EffectMagneticFluxTryDef[];
extern const u8 BattleScript_EffectMagneticFluxCheckStats[];
extern const u8 BattleScript_EffectMagneticFluxStart[];
extern const u8 BattleScript_EffectMagneticFlux[];
extern const u8 BattleScript_EffectAromaticMistEnd[];
extern const u8 BattleScript_AromaticMistAnim[];
extern const u8 BattleScript_EffectAromaticMistWorks[];
extern const u8 BattleScript_EffectAromaticMist[];
extern const u8 BattleScript_EffectPowder[];
extern const u8 BattleScript_EffectSpAtkUpHit[];
extern const u8 BattleScript_PartingShotEnd[];
extern const u8 BattleScript_EffectPartingShotSwitch[];
extern const u8 BattleScript_EffectPartingShotTrySpAtk[];
extern const u8 BattleScript_EffectPartingShotTryAtk[];
extern const u8 BattleScript_EffectPartingShot[];
extern const u8 BattleScript_EffectSpectralThief[];
extern const u8 BattleScript_SpectralThiefSteal[];
extern const u8 BattleScript_StatUpMsg[];
extern const u8 BattleScript_StatUp[];
extern const u8 BattleScript_VCreateStatLossRet[];
extern const u8 BattleScript_VCreateTrySpeed[];
extern const u8 BattleScript_VCreateTrySpDef[];
extern const u8 BattleScript_VCreateStatAnim[];
extern const u8 BattleScript_VCreateStatLoss[];
extern const u8 BattleScript_EffectVCreate[];
extern const u8 BattleScript_EffectLaserFocus[];
extern const u8 BattleScript_CoreEnforcerRet[];
extern const u8 BattleScript_MoveEffectCoreEnforcer[];
extern const u8 BattleScript_EffectCoreEnforcer[];
extern const u8 BattleScript_MoveEffectBugBite[];
extern const u8 BattleScript_MoveEffectIncinerate[];
extern const u8 BattleScript_EffectIncinerate[];
extern const u8 BattleScript_EffectBugBite[];
extern const u8 BattleScript_StrengthSapMustLower[];
extern const u8 BattleScript_StrengthSapHp[];
extern const u8 BattleScript_StrengthSapTryHp[];
extern const u8 BattleScript_StrengthSapLower[];
extern const u8 BattleScript_StrengthSapTryLower[];
extern const u8 BattleScript_EffectStrengthSap[];
extern const u8 BattleScript_EffectStrengthUpHit[];
extern const u8 BattleScript_OctolockEndTurn[];
extern const u8 BattleScript_PurifyWorks[];
extern const u8 BattleScript_EffectPurify[];
extern const u8 BattleScript_BurnUpWorks[];
extern const u8 BattleScript_EffectBurnUp[];
extern const u8 BattleScript_EffectFairyLock[];
extern const u8 BattleScript_EffectAllySwitch[];
extern const u8 BattleScript_EffectSleepHit[];
extern const u8 BattleScript_IgnoresAndFallsAsleep[];
extern const u8 BattleScript_SubstituteFade[];
extern const u8 BattleScript_BerryCurePrlzEnd2[];
extern const u8 BattleScript_BerryCureParRet[];
extern const u8 BattleScript_BerryCurePsnEnd2[];
extern const u8 BattleScript_BerryCurePsnRet[];
extern const u8 BattleScript_BerryCureBrnEnd2[];
extern const u8 BattleScript_BerryCureBrnRet[];
extern const u8 BattleScript_BerryCureFrzEnd2[];
extern const u8 BattleScript_BerryCureFrzRet[];
extern const u8 BattleScript_BerryCureSlpEnd2[];
extern const u8 BattleScript_BerryCureSlpRet[];
extern const u8 BattleScript_BerryCureConfusionEnd2[];
extern const u8 BattleScript_BerryCureConfusionRet[];
extern const u8 BattleScript_BerryCureChosenStatusEnd2[];
extern const u8 BattleScript_BerryCureChosenStatusRet[];
extern const u8 BattleScript_MentalHerbCureEnd2[];
extern const u8 BattleScript_MentalHerbCureRet[];
extern const u8 BattleScript_WhiteHerbEnd2[];
extern const u8 BattleScript_WhiteHerbRet[];
extern const u8 BattleScript_ItemHealHP_RemoveItem[];
extern const u8 BattleScript_ItemHealHP_RemoveItemRet[];
extern const u8 BattleScript_BerryPPHealEnd2[];
extern const u8 BattleScript_ItemHealHP_End2[];
extern const u8 BattleScript_ItemHealHP_Ret[];
extern const u8 BattleScript_ItemHurtEnd2[];
extern const u8 BattleScript_ItemHurtRet[];
extern const u8 BattleScript_SelectingNotAllowedMoveChoiceItem[];
extern const u8 BattleScript_SelectingNotAllowedMoveAssaultVest[];
extern const u8 BattleScript_SelectingNotAllowedMoveGorillaTactics[];
extern const u8 BattleScript_HangedOnMsg[];
extern const u8 BattleScript_BerryConfuseHealEnd2[];
extern const u8 BattleScript_BerryConfuseHealRet[];
extern const u8 BattleScript_BerryStatRaiseEnd2[];
extern const u8 BattleScript_BerryFocusEnergyEnd2[];
extern const u8 BattleScript_AirBaloonMsgIn[];
extern const u8 BattleScript_AirBaloonMsgPop[];
extern const u8 BattleScript_ActionSelectionItemsCantBeUsed[];
extern const u8 BattleScript_AskIfWantsToForfeitMatch[];
extern const u8 BattleScript_PrintPlayerForfeited[];
//extern const u8 BattleScript_PrintPlayerForfeitedLinkBattle[];
extern const u8 BattleScript_BallThrow[];
extern const u8 BattleScript_BallThrowByWally[];
extern const u8 BattleScript_SafariBallThrow[];
extern const u8 BattleScript_SuccessBallThrow[];
extern const u8 BattleScript_WallyBallThrow[];
extern const u8 BattleScript_ShakeBallThrow[];
extern const u8 BattleScript_TrainerBallBlock[];
extern const u8 BattleScript_TakeItemfromCaughtMon[];
extern const u8 BattleScript_RunByUsingItem[];
extern const u8 BattleScript_ActionWatchesCarefully[];
extern const u8 BattleScript_ActionGetNear[];
extern const u8 BattleScript_ActionThrowPokeblock[];
extern const u8 BattleScript_GhostGetOutGetOut[];
extern const u8 BattleScript_TooScaredToMove[];
extern const u8 BattleScript_IntimidateActivates[];
extern const u8 BattleScript_IntimidateActivatesEnd3[];
extern const u8 BattleScript_ReactivateIntimidate[];
extern const u8 BattleScript_HailActivates[]; //wondering if it matters where I put battlescript ehre, poisonworsened was only one put at end, adn thats when problem started.
extern const u8 BattleScript_IgnoresWhileAsleep[]; //need remember to add effect to change poison to toxic poison
extern const u8 BattleScript_IgnoresAndHitsItself[];// and set toxic timer to 3 so it does more damage than normal poison
//extern const u8 BattleScript_MoveEffectRecoil[];
extern const u8 BattleScript_MultiHitPrintStrings[];
extern const u8 BattleScript_FlushMessageBox[];//i think the issue was because I put it in the wrong place in battle_scripts_1.s
extern const u8 BattleScript_SpikesOnFaintedBattler[]; //order here shouldn't matter
extern const u8 BattleScript_WildMonBallBlock[];
extern const u8 BattleScript_NonGhost_BallDodge[];
extern const u8 BattleScript_SkipTurn[];
extern const u8 BattleScript_ExpOnCatch[];
extern const u8 BattleScript_GhostBallDodge[];
extern const u8 BattleScript_OldMan_Pokedude_CaughtMessage[];
extern const u8 BattleScript_SilphScopeUnveiled[];
extern const u8 BattleScript_BattleTowerTrainerBattleWon[];

extern const u8 *const gBattleScriptsForBattleEffects[]; //down here because these are pointers
extern const u8 *const gBattlescriptsForBallThrow[];
extern const u8 *const gBattlescriptsForRunningByItem[];
extern const u8 *const gBattlescriptsForUsingItem[];
extern const u8 *const gBattlescriptsForSafariActions[];

#endif // GUARD_BATTLE_SCRIPTS_H
