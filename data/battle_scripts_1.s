#include "constants/moves.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"	@put here as move effects were previously in batttle.h
#include "constants/battle_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_anim.h"
#include "constants/items.h"
#include "constants/hold_effects.h"
#include "constants/abilities.h"
#include "constants/species.h"
#include "constants/pokemon.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/game_stat.h"
#include "battle_string_ids.h"
	.include "asm/macros/battle_script.inc"
@ Define these here since misc_constants.inc conflicts with the C headers
	.set NULL, 0
	.set FALSE, 0
	.set TRUE, 1
	.section script_data, "aw", %progbits
	.align 2

gBattleScriptsForBattleEffects::	@must match order of battle_effects.h file
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectSleep
	.4byte BattleScript_EffectPoisonHit
	.4byte BattleScript_EffectAbsorb
	.4byte BattleScript_EffectBurnHit
	.4byte BattleScript_EffectFreezeHit
	.4byte BattleScript_EffectParalyzeHit
	.4byte BattleScript_EffectExplosion
	.4byte BattleScript_EffectDreamEater
	.4byte BattleScript_EffectMirrorMove
	.4byte BattleScript_EffectAttackUp
	.4byte BattleScript_EffectDefenseUp
	.4byte BattleScript_EffectSpeedUp
	.4byte BattleScript_EffectSpecialAttackUp
	.4byte BattleScript_EffectSpecialDefenseUp
	.4byte BattleScript_EffectAccuracyUp
	.4byte BattleScript_EffectEvasionUp
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectAttackDown
	.4byte BattleScript_EffectDefenseDown
	.4byte BattleScript_EffectSpeedDown
	.4byte BattleScript_EffectSpecialAttackDown
	.4byte BattleScript_EffectSpecialDefenseDown
	.4byte BattleScript_EffectAccuracyDown
	.4byte BattleScript_EffectEvasionDown
	.4byte BattleScript_EffectHaze
	.4byte BattleScript_EffectBide
	.4byte BattleScript_EffectRampage
	.4byte BattleScript_EffectRoar
	.4byte BattleScript_EffectMultiHit
	.4byte BattleScript_EffectConversion
	.4byte BattleScript_EffectFlinchHit
	.4byte BattleScript_EffectRestoreHp
	.4byte BattleScript_EffectToxic
	.4byte BattleScript_EffectPayDay
	.4byte BattleScript_EffectLightScreen
	.4byte BattleScript_EffectTriAttack
	.4byte BattleScript_EffectRest
	.4byte BattleScript_EffectOHKO
	.4byte BattleScript_EffectRazorWind		@not used changed using two type effect
	.4byte BattleScript_EffectSuperFang
	.4byte BattleScript_EffectDragonRage
	.4byte BattleScript_EffectTrap
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectDoubleHit
	.4byte BattleScript_EffectRecoilIfMiss
	.4byte BattleScript_EffectMist
	.4byte BattleScript_EffectFocusEnergy
	.4byte BattleScript_EffectRecoil
	.4byte BattleScript_EffectConfuse
	.4byte BattleScript_EffectAttackUp2
	.4byte BattleScript_EffectDefenseUp2
	.4byte BattleScript_EffectSpeedUp2
	.4byte BattleScript_EffectSpecialAttackUp2
	.4byte BattleScript_EffectSpecialDefenseUp2
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectTransform
	.4byte BattleScript_EffectAttackDown2
	.4byte BattleScript_EffectDefenseDown2
	.4byte BattleScript_EffectSpeedDown2
	.4byte BattleScript_EffectSpecialAttackDown2
	.4byte BattleScript_EffectSpecialDefenseDown2
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectReflect
	.4byte BattleScript_EffectPoison
	.4byte BattleScript_EffectParalyze
	.4byte BattleScript_EffectAttackDownHit
	.4byte BattleScript_EffectDefenseDownHit
	.4byte BattleScript_EffectSpeedDownHit
	.4byte BattleScript_EffectSpecialAttackDownHit
	.4byte BattleScript_EffectSpecialDefenseDownHit
	.4byte BattleScript_EffectAccuracyDownHit
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectSkyAttack
	.4byte BattleScript_EffectConfuseHit
	.4byte BattleScript_EffectTwineedle
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectSubstitute
	.4byte BattleScript_EffectRecharge
	.4byte BattleScript_EffectRage
	.4byte BattleScript_EffectMimic
	.4byte BattleScript_EffectMetronome
	.4byte BattleScript_EffectLeechSeed
	.4byte BattleScript_EffectSplash
	.4byte BattleScript_EffectDisable
	.4byte BattleScript_EffectLevelDamage
	.4byte BattleScript_EffectPsywave
	.4byte BattleScript_EffectCounter
	.4byte BattleScript_EffectEncore
	.4byte BattleScript_EffectPainSplit
	.4byte BattleScript_EffectSnore
	.4byte BattleScript_EffectConversion2
	.4byte BattleScript_EffectLockOn
	.4byte BattleScript_EffectSketch
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectSleepTalk
	.4byte BattleScript_EffectDestinyBond
	.4byte BattleScript_EffectFlail
	.4byte BattleScript_EffectSpite
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectHealBell
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectTripleKick
	.4byte BattleScript_EffectThief
	.4byte BattleScript_EffectMeanLook
	.4byte BattleScript_EffectNightmare
	.4byte BattleScript_EffectMinimize
	.4byte BattleScript_EffectCurse
	.4byte BattleScript_EffectHealingWish
	.4byte BattleScript_EffectProtect
	.4byte BattleScript_EffectSpikes
	.4byte BattleScript_EffectForesight
	.4byte BattleScript_EffectPerishSong
	.4byte BattleScript_EffectSandstorm
	.4byte BattleScript_EffectProtect
	.4byte BattleScript_EffectRollout
	.4byte BattleScript_EffectSwagger
	.4byte BattleScript_EffectFuryCutter
	.4byte BattleScript_EffectAttract
	.4byte BattleScript_EffectReturn
	.4byte BattleScript_EffectPresent
	.4byte BattleScript_EffectReturn
	.4byte BattleScript_EffectSafeguard
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectMagnitude
	.4byte BattleScript_EffectBatonPass
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectRapidSpin
	.4byte BattleScript_EffectSonicscreech
	.4byte BattleScript_EffectTwoTurnsAttack
	.4byte BattleScript_EffectMorningSun
	.4byte BattleScript_EffectMorningSun
	.4byte BattleScript_EffectMorningSun
	.4byte BattleScript_EffectHiddenPower
	.4byte BattleScript_EffectRainDance
	.4byte BattleScript_EffectSunnyDay
	.4byte BattleScript_EffectDefenseUpHit
	.4byte BattleScript_EffectAttackUpHit
	.4byte BattleScript_EffectAllStatsUpHit
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectBellyDrum
	.4byte BattleScript_EffectPsychUp
	.4byte BattleScript_EffectMirrorCoat
	.4byte BattleScript_EffectSkullBash
	.4byte BattleScript_EffectTwister
	.4byte BattleScript_EffectEarthquake
	.4byte BattleScript_EffectFutureSight
	.4byte BattleScript_EffectGust
	.4byte BattleScript_EffectFlinchMinimizeHit
	.4byte BattleScript_EffectSolarbeam
	.4byte BattleScript_EffectThunder
	.4byte BattleScript_EffectTeleport
	.4byte BattleScript_EffectBeatUp
	.4byte BattleScript_EffectSemiInvulnerable
	.4byte BattleScript_EffectDefenseCurl
	.4byte BattleScript_EffectSoftboiled
	.4byte BattleScript_EffectFakeOut
	.4byte BattleScript_EffectUproar
	.4byte BattleScript_EffectStockpile
	.4byte BattleScript_EffectSpitUp
	.4byte BattleScript_EffectSwallow
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectHail
	.4byte BattleScript_EffectTorment
	.4byte BattleScript_EffectFlatter
	.4byte BattleScript_EffectWillOWisp
	.4byte BattleScript_EffectMemento
	.4byte BattleScript_EffectFacade
	.4byte BattleScript_EffectFocusPunch
	.4byte BattleScript_EffectSmellingsalt
	.4byte BattleScript_EffectFollowMe
	.4byte BattleScript_EffectNaturePower
	.4byte BattleScript_EffectCharge
	.4byte BattleScript_EffectTaunt
	.4byte BattleScript_EffectHelpingHand
	.4byte BattleScript_EffectTrick
	.4byte BattleScript_EffectRolePlay
	.4byte BattleScript_EffectWish
	.4byte BattleScript_EffectAssist
	.4byte BattleScript_EffectIngrain
	.4byte BattleScript_EffectSuperpower
	.4byte BattleScript_EffectMagicCoat
	.4byte BattleScript_EffectRecycle
	.4byte BattleScript_EffectRevenge
	.4byte BattleScript_EffectBrickBreak
	.4byte BattleScript_EffectYawn
	.4byte BattleScript_EffectKnockOff
	.4byte BattleScript_EffectEndeavor
	.4byte BattleScript_EffectEruption
	.4byte BattleScript_EffectSkillSwap
	.4byte BattleScript_EffectImprison
	.4byte BattleScript_EffectRefresh
	.4byte BattleScript_EffectGrudge
	.4byte BattleScript_EffectSnatch
	.4byte BattleScript_EffectLowKick
	.4byte BattleScript_EffectSecretPower
	.4byte BattleScript_EffectDoubleEdge
	.4byte BattleScript_EffectTeeterDance
	.4byte BattleScript_EffectBurnHit
	.4byte BattleScript_EffectMudSport
	.4byte BattleScript_EffectPoisonFang
	.4byte BattleScript_EffectWeatherBall
	.4byte BattleScript_EffectOverheat
	.4byte BattleScript_EffectTickle
	.4byte BattleScript_EffectCosmicPower
	.4byte BattleScript_EffectSkyUppercut
	.4byte BattleScript_EffectBulkUp
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectMudSport
	.4byte BattleScript_EffectCalmMind
	.4byte BattleScript_EffectDragonDance
	.4byte BattleScript_EffectCamouflage
	@ new effects  @@@@@@@@@@
	.4byte BattleScript_EffectHit                     @ EFFECT_PLEDGE
	.4byte BattleScript_EffectFling                   @ EFFECT_FLING
	.4byte BattleScript_EffectNaturalGift             @ EFFECT_NATURAL_GIFT
	.4byte BattleScript_EffectWakeUpSlap              @ EFFECT_WAKE_UP_SLAP
	.4byte BattleScript_EffectHit                     @ EFFECT_WRING_OUT
	.4byte BattleScript_EffectHit                     @ EFFECT_HEX
	.4byte BattleScript_EffectHit                     @ EFFECT_ASSURANCE
	.4byte BattleScript_EffectHit                     @ EFFECT_TRUMP_CARD
	.4byte BattleScript_EffectHit                     @ EFFECT_ACROBATICS
	.4byte BattleScript_EffectHit                     @ EFFECT_HEAT_CRASH
	.4byte BattleScript_EffectHit                     @ EFFECT_PUNISHMENT
	.4byte BattleScript_EffectHit                     @ EFFECT_STORED_POWER
	.4byte BattleScript_EffectHit                     @ EFFECT_ELECTRO_BALL
	.4byte BattleScript_EffectHit                     @ EFFECT_GYRO_BALL
	.4byte BattleScript_EffectHit                     @ EFFECT_ECHOED_VOICE
	.4byte BattleScript_EffectHit                     @ EFFECT_PAYBACK
	.4byte BattleScript_EffectHit                     @ EFFECT_ROUND
	.4byte BattleScript_EffectHit                     @ EFFECT_BRINE
	.4byte BattleScript_EffectHit                     @ EFFECT_VENOSHOCK
	.4byte BattleScript_EffectHit                     @ EFFECT_RETALIATE
	.4byte BattleScript_EffectBulldoze                @ EFFECT_BULLDOZE
	.4byte BattleScript_EffectHit                     @ EFFECT_FOUL_PLAY
	.4byte BattleScript_EffectHit                     @ EFFECT_PSYSHOCK
	.4byte BattleScript_EffectRoost                   @ EFFECT_ROOST
	.4byte BattleScript_EffectGravity                 @ EFFECT_GRAVITY
	.4byte BattleScript_EffectMircleEye               @ EFFECT_MIRACLE_EYE
	.4byte BattleScript_EffectTailwind                @ EFFECT_TAILWIND
	.4byte BattleScript_EffectEmbargo                 @ EFFECT_EMBARGO
	.4byte BattleScript_EffectAquaRing                @ EFFECT_AQUA_RING
	.4byte BattleScript_EffectTrickRoom               @ EFFECT_TRICK_ROOM
	.4byte BattleScript_EffectWonderRoom              @ EFFECT_WONDER_ROOM
	.4byte BattleScript_EffectMagicRoom               @ EFFECT_MAGIC_ROOM
	.4byte BattleScript_EffectMagnetRise              @ EFFECT_MAGNET_RISE
	.4byte BattleScript_EffectToxicSpikes             @ EFFECT_TOXIC_SPIKES
	.4byte BattleScript_EffectGastroAcid              @ EFFECT_GASTRO_ACID
	.4byte BattleScript_EffectStealthRock             @ EFFECT_STEALTH_ROCK
	.4byte BattleScript_EffectTelekinesis             @ EFFECT_TELEKINESIS
	.4byte BattleScript_EffectPowerSwap               @ EFFECT_POWER_SWAP
	.4byte BattleScript_EffectGuardSwap               @ EFFECT_GUARD_SWAP
	.4byte BattleScript_EffectHeartSwap               @ EFFECT_HEART_SWAP
	.4byte BattleScript_EffectPowerSplit              @ EFFECT_POWER_SPLIT
	.4byte BattleScript_EffectGuardSplit              @ EFFECT_GUARD_SPLIT
	.4byte BattleScript_EffectStickyWeb               @ EFFECT_STICKY_WEB
	.4byte BattleScript_EffectMetalBurst              @ EFFECT_METAL_BURST
	.4byte BattleScript_EffectLuckyChant              @ EFFECT_LUCKY_CHANT
	.4byte BattleScript_EffectSuckerPunch             @ EFFECT_SUCKER_PUNCH
	.4byte BattleScript_EffectSpecialDefenseDownHit2  @ EFFECT_SPECIAL_DEFENSE_DOWN_HIT_2
	.4byte BattleScript_EffectSimpleBeam              @ EFFECT_SIMPLE_BEAM
	.4byte BattleScript_EffectEntrainment             @ EFFECT_ENTRAINMENT
	.4byte BattleScript_EffectHealPulse               @ EFFECT_HEAL_PULSE
	.4byte BattleScript_EffectQuash                   @ EFFECT_QUASH
	.4byte BattleScript_EffectIonDeluge               @ EFFECT_ION_DELUGE
	.4byte BattleScript_EffectFreezeHit               @ EFFECT_FREEZE_DRY
	.4byte BattleScript_EffectTopsyTurvy              @ EFFECT_TOPSY_TURVY
	.4byte BattleScript_EffectMistyTerrain            @ EFFECT_MISTY_TERRAIN
	.4byte BattleScript_EffectGrassyTerrain           @ EFFECT_GRASSY_TERRAIN
	.4byte BattleScript_EffectElectricTerrain         @ EFFECT_ELECTRIC_TERRAIN
	.4byte BattleScript_EffectPsychicTerrain          @ EFFECT_PSYCHIC_TERRAIN
	.4byte BattleScript_EffectAttackAccUp             @ EFFECT_ATTACK_ACCURACY_UP
	.4byte BattleScript_EffectAttackSpAttackUp        @ EFFECT_ATTACK_SPATK_UP
	.4byte BattleScript_EffectHurricane               @ EFFECT_HURRICANE
	.4byte BattleScript_EffectHit                     @ EFFECT_TWO_TYPED_MOVE
	.4byte BattleScript_EffectMeFirst                 @ EFFECT_ME_FIRST
	.4byte BattleScript_EffectSpeedUpHit              @ EFFECT_SPEED_UP_HIT
	.4byte BattleScript_EffectQuiverDance             @ EFFECT_QUIVER_DANCE
	.4byte BattleScript_EffectCoil                    @ EFFECT_COIL
	.4byte BattleScript_EffectElectrify               @ EFFECT_ELECTRIFY
	.4byte BattleScript_EffectBurnHit                 @ EFFECT_SCALD
	.4byte BattleScript_EffectReflectType             @ EFFECT_REFLECT_TYPE
	.4byte BattleScript_EffectSoak                    @ EFFECT_SOAK
	.4byte BattleScript_EffectGrowth                  @ EFFECT_GROWTH
	.4byte BattleScript_EffectCloseCombat             @ EFFECT_CLOSE_COMBAT
	.4byte BattleScript_EffectLastResort              @ EFFECT_LAST_RESORT
	.4byte BattleScript_EffectRecoil33WithStatus      @ EFFECT_RECOIL_33_STATUS
	.4byte BattleScript_EffectFlinchStatus			  @ EFFECT_FLINCH_STATUS
	.4byte BattleScript_EffectRecoil50                @ EFFECT_RECOIL_50
	.4byte BattleScript_EffectShellSmash              @ EFFECT_SHELL_SMASH
	.4byte BattleScript_EffectShiftGear               @ EFFECT_SHIFT_GEAR
	.4byte BattleScript_EffectDefenseUp3              @ EFFECT_DEFENSE_UP_3
	.4byte BattleScript_EffectNobleRoar               @ EFFECT_NOBLE_ROAR
	.4byte BattleScript_EffectVenomDrench             @ EFFECT_VENOM_DRENCH
	.4byte BattleScript_EffectToxicThread             @ EFFECT_TOXIC_THREAD
	.4byte BattleScript_EffectClearSmog               @ EFFECT_CLEAR_SMOG
	.4byte BattleScript_EffectHitSwitchTarget         @ EFFECT_HIT_SWITCH_TARGET
	.4byte BattleScript_EffectFinalGambit             @ EFFECT_FINAL_GAMBIT
	.4byte BattleScript_EffectHit                     @ EFFECT_CHANGE_TYPE_ON_ITEM
	.4byte BattleScript_EffectAutotomize              @ EFFECT_AUTOTOMIZE
	.4byte BattleScript_EffectCopycat                 @ EFFECT_COPYCAT
	.4byte BattleScript_EffectDefog                   @ EFFECT_DEFOG
	.4byte BattleScript_EffectHitEnemyHealAlly        @ EFFECT_HIT_ENEMY_HEAL_ALLY
	.4byte BattleScript_EffectSmackDown               @ EFFECT_SMACK_DOWN
	.4byte BattleScript_EffectSynchronoise            @ EFFECT_SYNCHRONOISE
	.4byte BattleScript_EffectPsychoShift             @ EFFECT_PSYCHO_SHIFT
	.4byte BattleScript_EffectPowerTrick              @ EFFECT_POWER_TRICK
	.4byte BattleScript_EffectFlameBurst              @ EFFECT_FLAME_BURST
	.4byte BattleScript_EffectAfterYou                @ EFFECT_AFTER_YOU
	.4byte BattleScript_EffectBestow                  @ EFFECT_BESTOW
	.4byte BattleScript_EffectRototiller              @ EFFECT_ROTOTILLER
	.4byte BattleScript_EffectFlowerShield            @ EFFECT_FLOWER_SHIELD
	.4byte BattleScript_EffectHitPreventEscape        @ EFFECT_HIT_PREVENT_ESCAPE
	.4byte BattleScript_EffectSpeedSwap               @ EFFECT_SPEED_SWAP
	.4byte BattleScript_EffectDefenseUp2Hit           @ EFFECT_DEFENSE_UP2_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_REVELATION_DANCE
	.4byte BattleScript_EffectAuroraVeil              @ EFFECT_AURORA_VEIL
	.4byte BattleScript_EffectThirdType               @ EFFECT_THIRD_TYPE
	.4byte BattleScript_EffectFeint                   @ EFFECT_FEINT
	.4byte BattleScript_EffectSparklingAria           @ EFFECT_SPARKLING_ARIA
	.4byte BattleScript_EffectAcupressure             @ EFFECT_ACUPRESSURE
	.4byte BattleScript_EffectAromaticMist            @ EFFECT_AROMATIC_MIST
	.4byte BattleScript_EffectPowder                  @ EFFECT_POWDER
	.4byte BattleScript_EffectSpAtkUpHit              @ EFFECT_SP_ATTACK_UP_HIT
	.4byte BattleScript_EffectHit                     @ EFFECT_BELCH
	.4byte BattleScript_EffectPartingShot             @ EFFECT_PARTING_SHOT
	.4byte BattleScript_EffectSpectralThief           @ EFFECT_SPECTRAL_THIEF
	.4byte BattleScript_EffectVCreate                 @ EFFECT_V_CREATE
	.4byte BattleScript_EffectMatBlock                @ EFFECT_MAT_BLOCK
	.4byte BattleScript_EffectHit                     @ EFFECT_STOMPING_TANTRUM
	.4byte BattleScript_EffectCoreEnforcer            @ EFFECT_CORE_ENFORCER
	.4byte BattleScript_EffectInstruct                @ EFFECT_INSTRUCT
	.4byte BattleScript_EffectThroatChop              @ EFFECT_THROAT_CHOP
	.4byte BattleScript_EffectLaserFocus              @ EFFECT_LASER_FOCUS
	.4byte BattleScript_EffectMagneticFlux            @ EFFECT_MAGNETIC_FLUX
	.4byte BattleScript_EffectGearUp                  @ EFFECT_GEAR_UP
	.4byte BattleScript_EffectIncinerate              @ EFFECT_INCINERATE
	.4byte BattleScript_EffectBugBite                 @ EFFECT_BUG_BITE
	.4byte BattleScript_EffectStrengthSap             @ EFFECT_STRENGTH_SAP
	.4byte BattleScript_EffectMindBlown               @ EFFECT_MIND_BLOWN
	.4byte BattleScript_EffectPurify                  @ EFFECT_PURIFY
	.4byte BattleScript_EffectLoseTypeHit             @ EFFECT_LOSETYPE_HIT - previously EFFECT_BURN_UP
	.4byte BattleScript_EffectShoreUp                 @ EFFECT_SHORE_UP
	.4byte BattleScript_EffectGeomancy                @ EFFECT_GEOMANCY
	.4byte BattleScript_EffectFairyLock               @ EFFECT_FAIRY_LOCK
	.4byte BattleScript_EffectAllySwitch              @ EFFECT_ALLY_SWITCH
	.4byte BattleScript_EffectRelicSong               @ EFFECT_RELIC_SONG
	.4byte BattleScript_EffectHitEscape
	.4byte BattleScript_EffectWorrySeed
	.4byte BattleScript_EffectFellStinger
	.4byte BattleScript_EffectCaptivate
	.4byte BattleScript_EffectHit
	.4byte BattleScript_EffectHammerArm
	.4byte BattleScript_EffectFusionCombo
	.4byte BattleScript_EffectHealBlock
	.4byte BattleScript_EffectSpecialAttackUp3
	.4byte BattleScript_EffectStrengthUpHit
	.4byte BattleScript_EffectBodyPress
	.4byte BattleScript_EffectEerieSpell              @ EFFECT_EERIE_SPELL
	.4byte BattleScript_EffectJungleHealing           @ EFFECT_JUNGLE_HEALING
	.4byte BattleScript_EffectCoaching                @ EFFECT_COACHING
	.4byte BattleScript_EffectHit                     @ EFFECT_LASH_OUT
	.4byte BattleScript_EffectHit                     @ EFFECT_GRASSY_GLIDE
	.4byte BattleScript_EffectRemoveTerrain           @ EFFECT_REMOVE_TERRAIN
	.4byte BattleScript_EffectHit                     @ EFFECT_DYNAMAX_DOUBLE_DMG
	.4byte BattleScript_EffectDecorate                @ EFFECT_DECORATE
	.4byte BattleScript_EffectHit                     @ EFFECT_SNIPE_SHOT
	.4byte BattleScript_EffectStuffCheeks             @ EFFECT_STUFF_CHEEKS
	.4byte BattleScript_EffectDefenseDownHit          @ EFFECT_GRAV_APPLE
	.4byte BattleScript_EffectEvasionUpHit            @ EFFECT_EVASION_UP_HIT
	.4byte BattleScript_EffectDoubleIronBash          @ EFFECT_DOUBLE_IRON_BASH
	.4byte BattleScript_EffectGlitzyGlow              @ EFFECT_GLITZY_GLOW
	.4byte BattleScript_EffectBaddyBad                @ EFFECT_BADDY_BAD
	.4byte BattleScript_EffectSappySeed               @ EFFECT_SAPPY_SEED
	.4byte BattleScript_EffectFreezyFrost             @ EFFECT_FREEZY_FROST
	.4byte BattleScript_EffectSparklySwirl            @ EFFECT_SPARKLY_SWIRL
	.4byte BattleScript_EffectPlasmaFists             @ EFFECT_PLASMA_FISTS
	.4byte BattleScript_EffectHyperspaceFury          @ EFFECT_HYPERSPACE_FURY
	.4byte BattleScript_EffectAuraWheel               @ EFFECT_AURA_WHEEL
	.4byte BattleScript_EffectPhotonGeyser            @ EFFECT_PHOTON_GEYSER
	.4byte BattleScript_EffectShellSideArm            @ EFFECT_SHELL_SIDE_ARM
	.4byte BattleScript_EffectHit                     @ EFFECT_TERRAIN_PULSE
	.4byte BattleScript_EffectJawLock                 @ EFFECT_JAW_LOCK
	.4byte BattleScript_EffectNoRetreat               @ EFFECT_NO_RETREAT
	.4byte BattleScript_EffectTarShot                 @ EFFECT_TAR_SHOT
	.4byte BattleScript_EffectPoltergeist             @ EFFECT_POLTERGEIST
	.4byte BattleScript_EffectOctolock                @ EFFECT_OCTOLOCK
	.4byte BattleScript_EffectClangorousSoul          @ EFFECT_CLANGOROUS_SOUL
	.4byte BattleScript_EffectHit                     @ EFFECT_BOLT_BEAK
	.4byte BattleScript_EffectSkyDrop                 @ EFFECT_SKY_DROP

	
	.4byte BattleScript_EffectAttackerDefenseDownHit

	@ custom effects  @@@@@@@@@@
	.4byte BattleScript_EffectMonotype
	.4byte BattleScript_EffectSketchStatUp
	.4byte BattleScript_EffectFlash
	.4byte BattleScript_EffectCocoon
	.4byte BattleScript_EffectFlashFreeze	@ice will o wisp
	.4byte BattleScript_EffectDryadsCurse
	.4byte BattleScript_EffectProtect	@shield bash
	.4byte BattleScript_EffectAttractHit	@use move_effect_attract	dont thnk work/setup yet think reserve for sallazle
	.4byte BattleScript_EffectHit		@Expanding Force fill effect  is gen 9, just putting here to fill space, is not setup
	.4byte BattleScript_EffectTripleArrows @ EFFECT_TRIPLE_ARROWS
	.4byte BattleScript_EffectSpecialAttackUpHit	@EFFECT_SPECIAL_ATTACK_UP_HIT
	.4byte BattleScript_EffectVictoryDance            @ EFFECT_VICTORY_DANCE
	.4byte BattleScript_EffectTeatime                 @ EFFECT_TEATIME
	.4byte BattleScript_EffectAttackUpUserAlly        @ EFFECT_ATTACK_UP_USER_ALLY
	.4byte BattleScript_EffectTargetTypeBasedDmg	  @ EFFECT_TARGET_TYPE_DAMAGE  @ bug status / dont need effect for can use moveeffect  instaed w arg to move effect
	.4byte BattleScript_EffectTrenchrun				  @ EFFECT_TRENCH_RUN

BattleScript_EffectAlwaysCrit:
BattleScript_EffectFellStinger:
BattleScript_EffectFusionCombo:
BattleScript_EffectTwoTypedMove:
BattleScript_EffectBelch:
BattleScript_EffectBodyPress:
BattleScript_EffectChangeTypeOnItem:
BattleScript_EffectRevelationDance:
BattleScript_EffectStompingTantrum:

@BattleScript_EffectSleepHit:
@	setmoveeffect MOVE_EFFECT_SLEEP
@	goto BattleScript_EffectHit

@check this make sure it works I dont see a command here	
BattleScript_EffectAllySwitch:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_ALLYSWITCHPOSITION
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectHammerArm::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit
	
BattleScript_EffectFairyLock:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetfairylock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_NOONEWILLBEABLETORUNAWAY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_BurnUpFireTypeCheck:
	jumpiftype BS_ATTACKER, TYPE_FIRE, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed

BattleScript_BurnUpPsychicTypeCheck:
	jumpiftype BS_ATTACKER, TYPE_PSYCHIC, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed

BattleScript_BurnUpFightingTypeCheck:
	jumpiftype BS_ATTACKER, TYPE_FIGHTING, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed

BattleScript_BurnUpFlyingTypeCheck:
	jumpiftype BS_ATTACKER, TYPE_FLYING, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed

BattleScript_BurnUpElectricTypeCheck:
	jumpiftype BS_ATTACKER, TYPE_ELECTRIC, BattleScript_BurnUpWorks
	goto BattleScript_ButItFailed
	
@can make its own move category, just need to add a jump for move name check that would go to the type check & buffer type name in losetype command
@and after result/wait message make another jump for movename to do type loss and print loss message, then a goto, to come back for fainting
@have idea for psychic version inspired by mob psycho, 110% power
@done will add more types later, also plan to make lose type for entire battle.
BattleScript_EffectLoseTypeHit: 
	attackcanceler
	attackstring
	ppreduce
	jumpifmove MOVE_BURN_OUT, BattleScript_BurnUpFireTypeCheck
	jumpifmove MOVE_OVER_MAX_POWER, BattleScript_BurnUpPsychicTypeCheck
	jumpifmove MOVE_SHIMON, BattleScript_BurnUpFightingTypeCheck
	jumpifmove MOVE_FINAL_FLIGHT, BattleScript_BurnUpFlyingTypeCheck
	jumpifmove MOVE_PLASMA_RAILGUN, BattleScript_BurnUpElectricTypeCheck
	jumpifmove MOVE_DOUBLE_SHOCK, BattleScript_BurnUpElectricTypeCheck
BattleScript_BurnUpWorks:
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	losetype BS_ATTACKER
	printstring STRINGID_ATTACKERLOSTTYPE
	waitmessage 0x40
BattleScript_BurnUpEnd:			@leaving for now, in case I make losetype bs_targt
	tryfaintmon BS_TARGET, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_AttackerRemoveType::	@apparently just for parental bond
	losetype BS_ATTACKER
	printstring STRINGID_ATTACKERLOSTTYPE
	waitmessage 0x40
	return

	
BattleScript_EffectPurify:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_PurifyWorks
	goto BattleScript_ButItFailed
BattleScript_PurifyWorks:
	attackanimation
	waitanimation
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_ATTACKERCUREDTARGETSTATUS
	waitmessage 0x40
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_ATTACKER
	goto BattleScript_RestoreHp
	
BattleScript_EffectStrengthSap:
	setstatchanger STAT_ATK, 1, TRUE	@set stat to affect and if being lowered
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_ATK, 0, BattleScript_ButItFailed	@if can lower stat move continues otherwise fail
	pause 0x20	@don't know if necessary but will keep
BattleScript_StrengthSapTryLower:	@start of main logic
	getstatvalue BS_TARGET, STAT_ATK	@get atk statvalue for later heal
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_StrengthSapHp	@think go to heal if cant lower stat
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_StrengthSapHp	@dont know what does assumed similar to above so keeping
BattleScript_StrengthSapLower:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40	@finish stat drop effect go to heal
BattleScript_StrengthSapHp:
	jumpiffullhp BS_ATTACKER, BattleScript_MoveEnd	@goto moev end if cant heal
	jumpifhealblock BS_ATTACKER, BattleScript_MoveEnd
	manipulatedamage DMG_BIG_ROOT @this is a physical drain unlike dream eater so think can use liquid ooze 
	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_AbsorbLiquidOoze	@should always be below DMG_BIG_ROOT
	healthbarupdate BS_ATTACKER	@& ghost drain here think will put ghost drain effect into big root for ease of use
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNENERGYDRAINED
	waitmessage 0x40
	goto BattleScript_MoveEnd

@need test move will succeed
BattleScript_EffectSkyDrop:
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SkyDropTurn2
	attackcanceler
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifsubstituteblocks BattleScript_ButItFailed
	jumpiftargetally BattleScript_ButItFailed
	jumpifunder200 BS_TARGET, BattleScript_SkyDropWork
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_TARGETTOOHEAVY
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_SkyDropWork:
	setskydrop
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKY_DROP
	setsemiinvulnerablebit
	call BattleScriptFirstChargingTurn
	goto BattleScript_MoveEnd
BattleScript_SkyDropTurn2:
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 0x1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	clearsemiinvulnerablebit
	attackstring
	clearskydrop BattleScript_SkyDropChangedTarget
	jumpiftype BS_TARGET, TYPE_FLYING, BattleScript_SkyDropFlyingType
	goto BattleScript_SkyDropHitFromAtkString
BattleScript_SkyDropFlyingType:
	makevisible BS_TARGET
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	makevisible BS_ATTACKER
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_SkyDropFlyingAlreadyConfused
	jumpifstatus2 BS_TARGET, STATUS2_LOCK_CONFUSE, BattleScript_SkyDropFlyingConfuseLock
	goto BattleScript_MoveEnd
BattleScript_SkyDropChangedTarget:
	pause B_WAIT_TIME_SHORT
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	makevisible BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_SkyDropFlyingConfuseLock:
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
BattleScript_SkyDropFlyingAlreadyConfused:
	setmoveeffect MOVE_EFFECT_THRASH
	clearstatusfromeffect BS_TARGET
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_MoveEnd
	setbyte BS_ATTACKER, BS_TARGET
	goto BattleScript_ThrashConfuses

BattleScript_EffectFling:
	jumpifcantfling BS_ATTACKER, BattleScript_ButItFailedAtkStringPpReduce
	jumpifembargo BattleScript_ButItFailedAtkStringPpReduce
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_MAGIC_ROOM, BattleScript_ButItFailedAtkStringPpReduce
	setlastuseditem BS_ATTACKER
	removeitem BS_ATTACKER
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_PKMNFLUNG
	waitmessage B_WAIT_TIME_SHORT
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_MED
	resultmessage
	waitmessage B_WAIT_TIME_MED
	jumpiflastuseditemberry BattleScript_EffectFlingConsumeBerry
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_FLAME_ORB, BattleScript_FlingFlameOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_FLINCH, BattleScript_FlingFlinch
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_LIGHT_BALL, BattleScript_FlingLightBall
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_MENTAL_HERB, BattleScript_FlingMentalHerb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_POISON_POWER, BattleScript_FlingPoisonBarb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_TOXIC_ORB, BattleScript_FlingToxicOrb
	jumpiflastuseditemholdeffect BS_ATTACKER, HOLD_EFFECT_RESTORE_STATS, BattleScript_FlingWhiteHerb
BattleScript_EffectFlingConsumeBerry:
	savebattleritem BS_TARGET
	battleritemtolastuseditem BS_TARGET
	setbyte sBERRY_OVERRIDE, TRUE @ override the requirements for eating berries
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_TARGET
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, FALSE
	restorebattleritem BS_TARGET
BattleScript_FlingEnd:
	tryfaintmon BS_TARGET FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_FlingFlameOrb:
	setmoveeffect MOVE_EFFECT_BURN
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingFlinch:
	setmoveeffect MOVE_EFFECT_FLINCH
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingLightBall:
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingMentalHerb:
	curecertainstatuses BS_TARGET
	savetarget
	copybyte gBattlerAttacker, gBattlerTarget
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_ATTACKER
	restoretarget
	goto BattleScript_FlingEnd
BattleScript_FlingPoisonBarb:
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingToxicOrb:
	setmoveeffect MOVE_EFFECT_TOXIC
	seteffectprimary
	goto BattleScript_FlingEnd
BattleScript_FlingWhiteHerb:
	tryresetnegativestatstages BS_TARGET
	swapattackerwithtarget
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_MED
	swapattackerwithtarget
	goto BattleScript_FlingEnd

BattleScript_EffectBugBite:
	setmoveeffect MOVE_EFFECT_BUG_BITE | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectIncinerate:
	setmoveeffect MOVE_EFFECT_INCINERATE | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_MoveEffectIncinerate::
	printstring STRINGID_INCINERATEBURN
	waitmessage 0x40
	return
	
BattleScript_StickyHoldKnockoff::
	printstring STRINGID_STICKYHOLDABSORBEDITEM
	waitmessage 0x40
	return

BattleScript_MoveEffectBugBite::
	printstring STRINGID_BUGBITE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, TRUE   @ override the requirements for eating berries
	consumeberry BS_ATTACKER, TRUE  @ consume the berry, then restore the item from changedItems
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, FALSE
	return

BattleScript_EffectCoreEnforcer:
	setmoveeffect MOVE_EFFECT_CORE_ENFORCER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_MoveEffectCoreEnforcer::
	setgastroacid BattleScript_CoreEnforcerRet
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage 0x40
BattleScript_CoreEnforcerRet:
	return

BattleScript_EffectLaserFocus:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_LASER_FOCUS, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_LASERFOCUS
	waitmessage 0x40
	goto BattleScript_MoveEnd

 @not complete need setup evasion boost (2 stage boost) and make sure its removed if status on air i.e flying/skydrop donethat part
 @also need to put back logic that grounded flying types dont take super from electricity etc. 
BattleScript_EffectTrenchrun::
	setuserstatus4 STATUS4_GROUNDED, BattleScript_ButItFailed
	attackcanceler	@cancel logic should be in attack canceler so not stacked
	setmoveeffect MOVE_EFFECT_EVS_PLUS_2 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	setmoveeffectwithchance
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_LASERFOCUS @give its own string/message
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectVCreate:
	setmoveeffect MOVE_EFFECT_V_CREATE | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_VCreateStatLoss::
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, 0x0, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPDEF, 0x0, BattleScript_VCreateStatAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, 0x0, BattleScript_VCreateStatLossRet
BattleScript_VCreateStatAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF | BIT_SPEED, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VCreateTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_VCreateTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VCreateTrySpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_VCreateTrySpeed:
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, BattleScript_VCreateStatLossRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VCreateStatLossRet
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_VCreateStatLossRet:
	return

BattleScript_SpectralThiefSteal::
	printstring STRINGID_SPECTRALTHIEFSTEAL
	waitmessage 0x40
	setbyte sB_ANIM_ARG2, 0
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	spectralthiefprintstats
	return

BattleScript_EffectSpectralThief:
	setmoveeffect MOVE_EFFECT_SPECTRAL_THIEF
	goto BattleScript_EffectHit

BattleScript_EffectPartingShot::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, 0x0, BattleScript_EffectPartingShotTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, 0x0, BattleScript_CantLowerMultipleStats
BattleScript_EffectPartingShotTryAtk:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE	
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectPartingShotTrySpAtk
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_EffectPartingShotTrySpAtk:
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectPartingShotSwitch
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_EffectPartingShotSwitch:	
	moveendall
	@ jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_PartingShotEnd
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_PartingShotEnd
	openpartyscreen 0x1, BattleScript_PartingShotEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 0x2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
BattleScript_PartingShotEnd:
	end

BattleScript_EffectSpAtkUpHit:
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectPowder:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_POWDER, BattleScript_ButItFailed
	setpowder BS_TARGET
	attackanimation
	waitanimation
	printstring STRINGID_COVEREDINPOWDER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectAromaticMist:
	attackcanceler
	attackstring
	ppreduce
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_ButItFailed
	jumpiftargetally BattleScript_EffectAromaticMistWorks
	goto BattleScript_ButItFailed
BattleScript_EffectAromaticMistWorks:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectAromaticMistEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AromaticMistAnim
	pause 0x10
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage 0x40
	goto BattleScript_EffectAromaticMistEnd
BattleScript_AromaticMistAnim:
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_EffectAromaticMistEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectMagneticFlux::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0x0
BattleScript_EffectMagneticFluxStart:
	jumpiftype BS_TARGET, TYPE_ELECTRIC, BattleScript_EffectMagneticFluxCheckStats
	goto BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_DEF, 0xC, BattleScript_EffectMagneticFluxTryDef
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPDEF, 0xC, BattleScript_EffectMagneticFluxLoop
BattleScript_EffectMagneticFluxTryDef:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_EffectMagneticFluxSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectMagneticFluxSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_DEF | BIT_SPDEF, 0x0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectMagneticFluxTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_EffectMagneticFluxTrySpDef
	addbyte gBattleCommunication, 0x1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_EffectMagneticFluxTrySpDef:
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectMagneticFluxLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_EffectMagneticFluxLoop
	addbyte gBattleCommunication, 0x1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_EffectMagneticFluxLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectMagneticFluxEnd
	setallytonexttarget BattleScript_EffectMagneticFluxStart
BattleScript_EffectMagneticFluxEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectGearUp::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattleCommunication, 0x0
BattleScript_EffectGearUpStart:
	jumpiftype BS_TARGET, TYPE_ELECTRIC, BattleScript_EffectGearUpCheckStats
	goto BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpCheckStats:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_EffectGearUpTryAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, 0xC, BattleScript_EffectGearUpLoop
BattleScript_EffectGearUpTryAtk:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_EffectGearUpSkipAnim
	attackanimation
	waitanimation
BattleScript_EffectGearUpSkipAnim:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectGearUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_EffectGearUpTrySpAtk
	addbyte gBattleCommunication, 0x1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_EffectGearUpTrySpAtk:
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectGearUpLoop
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_EffectGearUpLoop
	addbyte gBattleCommunication, 0x1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_EffectGearUpLoop:
	jumpifbytenotequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectGearUpEnd
	setallytonexttarget BattleScript_EffectGearUpStart
BattleScript_EffectGearUpEnd:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	goto BattleScript_ButItFailed

BattleScript_EffectAcupressure:
	attackcanceler
	jumpifbyteequal gBattlerTarget, gBattlerAttacker, BattleScript_EffectAcupressureTry
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_PrintMoveMissed
BattleScript_EffectAcupressureTry:
	attackstring
	ppreduce
	tryaccupressure BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	statbuffchange MOVE_EFFECT_CERTAIN, BattleScript_MoveEnd
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_MoveEffectFeint::
	printstring STRINGID_FELLFORFEINT
	waitmessage 0x40
	return

BattleScript_EffectFeint:
	setmoveeffect MOVE_EFFECT_FEINT
	goto BattleScript_EffectHit

BattleScript_EffectThirdType:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetthirdtype BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_THIRDTYPEADDED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectDefenseUp2Hit:
	setmoveeffect MOVE_EFFECT_DEF_PLUS_2 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectFlowerShield:
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
BattleScript_FlowerShieldIsAnyGrass:
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_FlowerShieldLoopStart
	jumpifnexttargetvalid BattleScript_FlowerShieldIsAnyGrass
	goto BattleScript_ButItFailed
BattleScript_FlowerShieldLoopStart:
	selectfirstvalidtarget
BattleScript_FlowerShieldLoop:
	movevaluescleanup
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_FlowerShieldLoop2
	goto BattleScript_FlowerShieldMoveTargetEnd
BattleScript_FlowerShieldLoop2:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_FlowerShieldMoveTargetEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 0x2, BattleScript_FlowerShieldDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_FlowerShieldMoveTargetEnd
	pause 0x15
	goto BattleScript_FlowerShieldString
BattleScript_FlowerShieldDoAnim:
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_FlowerShieldString:
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_FlowerShieldMoveTargetEnd:
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_FlowerShieldLoop
	end

BattleScript_EffectRototiller:
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
BattleScript_RototillerLoop:
	movevaluescleanup
	jumpifnotgrounded BS_TARGET, BattleScript_RototillerNoEffect
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_RototillerLoop2
BattleScript_RototillerNoEffect:
	pause 0x20
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage 0x40
	goto BattleScript_RototillerMoveTargetEnd
BattleScript_RototillerLoop2:
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_RototillerDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, 0xC, BattleScript_RototillerCantRaiseMultipleStats
BattleScript_RototillerDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_RototillerTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_RototillerTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_RototillerTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_RototillerMoveTargetEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_RototillerMoveTargetEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_RototillerMoveTargetEnd:
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_RototillerLoop
	end
BattleScript_RototillerCantRaiseMultipleStats:
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage 0x40
	goto BattleScript_RototillerMoveTargetEnd

BattleScript_EffectBestow:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	jumpifsubstituteblocks BattleScript_ButItFailed
	trybestow BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_BESTOWITEMGIVING
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_MoveUsedHealBlockPrevents::
	printstring STRINGID_HEALBLOCKPREVENTSUSAGE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_MoveUsedGravityPrevents::
	printstring STRINGID_GRAVITYPREVENTSUSAGE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SlowStartEnds::
	pause 0x5
	@ copybyte gBattlerAbility, gBattlerAttacker
	printstring STRINGID_SLOWSTARTEND
	waitmessage 0x40
	end2

BattleScript_MoveUsedIsThroatChopPrevented::
	printstring STRINGID_PKMNCANTUSEMOVETHROATCHOP
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_ThroatChopEndTurn::
	printstring STRINGID_THROATCHOPENDS
	waitmessage 0x40
	end2

BattleScript_EffectAfterYou:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryafteryou BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_KINDOFFER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFlameBurst:
	setmoveeffect MOVE_EFFECT_FLAME_BURST | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_MoveEffectFlameBurst::
	tryfaintmon BS_TARGET, FALSE, NULL
	printstring STRINGID_BURSTINGFLAMESHIT
	waitmessage 0x40
	savetarget
	copybyte gBattlerTarget, sBATTLER
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	tryfaintmon BS_TARGET, FALSE, NULL	@idk if I need two fo these? oh its not using this at all?
	restoretarget
	goto BattleScript_MoveEnd

BattleScript_EffectPowerTrick:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	powertrick BS_ATTACKER
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDATKANDDEF
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPsychoShift:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstatus BS_ATTACKER, STATUS1_ANY, BattleScript_EffectPsychoShiftCanWork
	goto BattleScript_ButItFailed
BattleScript_EffectPsychoShiftCanWork:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	jumpifsafeguard BattleScript_SafeguardProtected
	trypsychoshift BattleScript_MoveEnd
	attackanimation
	waitanimation
	copybyte gEffectBattler, gBattlerTarget
	printfromtable gStatusConditionsStringIds
	waitmessage 0x40
	statusanimation BS_TARGET
	updatestatusicon BS_TARGET
	curestatus BS_ATTACKER
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectAttackUpUserAlly:
	jumpifnoally BS_ATTACKER, BattleScript_EffectAttackUp
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_EffectAttackUpUserAlly_Works
	jumpifstat BS_ATTACKER_PARTNER, CMP_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_ButItFailed
BattleScript_EffectAttackUpUserAlly_Works:
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_EffectAttackUpUserAlly_TryAlly
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAttackUpUserAllyUser_PrintString
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_EffectAttackUpUserAllyUser_PrintString:
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectAttackUpUserAlly_TryAlly:
	setallytonexttarget BattleScript_EffectAttackUpUserAlly_TryAlly_
BattleScript_EffectAttackUpUserAlly_End:
	goto BattleScript_MoveEnd
BattleScript_EffectAttackUpUserAlly_TryAlly_:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_EffectAttackUpUserAlly_End
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectAttackUpUserAlly_AllyAnim
	pause B_WAIT_TIME_SHORTEST
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectAttackUpUserAlly_End
BattleScript_EffectAttackUpUserAlly_AllyAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_EffectAttackUpUserAlly_End

BattleScript_EffectTeatime::
	attackcanceler
	attackstring
	ppreduce
	@jumpifteanoberry BattleScript_ButItFailed  neeed to add commands vsonic
@ at least one battler is affected 
	attackanimation
	waitanimation
BattleScript_TeatimeLoop:
	@jumpifteainvulnerable BS_TARGET, BattleScript_Teatimevul
	@jumpifrodaffected BS_TARGET, BattleScript_Teatimerod
	@jumpifabsorbaffected BS_TARGET, BattleScript_Teatimesorb
	@jumpifmotoraffected BS_TARGET, BattleScript_Teatimemotor
	orword gHitMarker, HITMARKER_NO_ANIMATIONS | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	setbyte sBERRY_OVERRIDE, TRUE   @ override the requirements for eating berries
	consumeberry BS_TARGET, TRUE  @ consume the berry, then restore the item from changedItems
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_IGNORE_DISGUISE
	setbyte sBERRY_OVERRIDE, FALSE
	removeitem BS_TARGET
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimevul:
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimesorb:
	@ call BattleScript_AbilityPopUpTarget
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimerod:
	@ call BattleScript_AbilityPopUpTarget
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TeatimeBuffer
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_TeatimeBuffer
	printfromtable gStatUpStringIds
	waitmessage 0x40
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_Teatimemotor:
	@ call BattleScript_AbilityPopUpTarget
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TeatimeBuffer
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_TeatimeBuffer
	printfromtable gStatUpStringIds
	waitmessage 0x40
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd
BattleScript_TeatimeBuffer:
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_TeatimeLoop
	moveendcase MOVE_END_CLEAR_BITS
	goto BattleScript_MoveEnd

BattleScript_EffectVictoryDance:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, MAX_STAT_STAGE, BattleScript_VictoryDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_VictoryDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_VictoryDanceTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceTryDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTryDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_VictoryDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_VictoryDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_VictoryDanceEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_VictoryDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSynchronoise:
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
BattleScript_SynchronoiseLoop:
	movevaluescleanup
	jumpifcantusesynchronoise BattleScript_SynchronoiseNoEffect
	accuracycheck BattleScript_SynchronoiseMissed, ACC_CURR_MOVE
	critcalc
	damagecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	printstring STRINGID_EMPTYSTRING3
	waitmessage 0x1
	tryfaintmon BS_TARGET, FALSE, NULL
BattleScript_SynchronoiseMoveTargetEnd:
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_SynchronoiseLoop
	end
BattleScript_SynchronoiseMissed:
	pause 0x20
	resultmessage
	waitmessage 0x40
	goto BattleScript_SynchronoiseMoveTargetEnd
BattleScript_SynchronoiseNoEffect:
	pause 0x20
	printstring STRINGID_NOEFFECTONTARGET
	waitmessage 0x40
	goto BattleScript_SynchronoiseMoveTargetEnd

BattleScript_EffectSmackDown:
	setmoveeffect MOVE_EFFECT_SMACK_DOWN
	goto BattleScript_EffectHit

BattleScript_MoveEffectSmackDown::
	printstring STRINGID_FELLSTRAIGHTDOWN
	waitmessage 0x40
	return

BattleScript_EffectHitEnemyHealAlly:
	jumpiftargetally BattleScript_EffectHealPulse
	goto BattleScript_EffectHit

BattleScript_EffectDefog:
	setstatchanger STAT_EVASION, 1, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_DefogIfCanClearHazards
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_EVASION, 0x0, BattleScript_DefogWorks
BattleScript_DefogIfCanClearHazards:
	defogclear BS_ATTACKER, FALSE, BattleScript_ButItFailedAtkStringPpReduce
BattleScript_DefogWorks:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_DefogTryHazardsWithAnim
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 0x2, BattleScript_DefogDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_DefogTryHazardsWithAnim
	pause 0x20
	goto BattleScript_DefogPrintString
BattleScript_DefogDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_DefogPrintString::
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_DefogTryHazards::
	copybyte gEffectBattler, gBattlerAttacker
	defogclear BS_ATTACKER, TRUE, NULL
	copybyte gBattlerAttacker, gEffectBattler
	goto BattleScript_MoveEnd
BattleScript_DefogTryHazardsWithAnim:
	attackanimation
	waitanimation
	goto BattleScript_DefogTryHazards

BattleScript_EffectCopycat:
	attackcanceler
	attackstring
	pause 0x5
	trycopycat BattleScript_CopycatFail
	attackanimation
	waitanimation
	jumptocalledmove TRUE
BattleScript_CopycatFail:
	ppreduce
	goto BattleScript_ButItFailed

BattleScript_EffectInstruct:
	attackcanceler
	attackstring
	ppreduce
	pause 0x5
	tryinstruct BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_USEDINSTRUCTEDMOVE
	waitmessage 0x40
	setbyte sB_ANIM_TURN, 0x0
	setbyte sB_ANIM_TARGETS_HIT, 0x0
	jumptocalledmove TRUE

BattleScript_EffectAutotomize:
	setstatchanger STAT_SPEED, 2, FALSE
	attackcanceler
	attackstring
	ppreduce
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_AutotomizeWeightLoss
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AutotomizeAttackAnim
	pause 0x20
	goto BattleScript_AutotomizePrintString
BattleScript_AutotomizeAttackAnim::
	attackanimation
	waitanimation
BattleScript_AutotomizeDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_AutotomizePrintString::
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AutotomizeWeightLoss::
	jumpifmovehadnoeffect BattleScript_MoveEnd		@doesnt have type calc wondering what this means? how work?
	tryautotomize BS_ATTACKER, BattleScript_MoveEnd
	printstring STRINGID_BECAMENIMBLE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFinalGambit:		@CHANGED effect to do dmg based on missing health, instead of currenthalth
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	missinghealthtoDmg
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	resultmessage
	waitmessage 0x40
	setatkhptozero
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	setmoveeffectwithchance
	tryfaintmon BS_ATTACKER, FALSE, NULL
	tryfaintmon BS_TARGET, FALSE, NULL
	jumpifmovehadnoeffect BattleScript_MoveEnd
	goto BattleScript_MoveEnd

BattleScript_EffectHitSwitchTarget:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, FALSE, NULL
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	tryhitswitchtarget BattleScript_EffectHitSwitchTargetMoveEnd @check hitswitch make sure all moves are not based on level to work
BattleScript_EffectHitSwitchTargetMoveEnd:
	moveendall
	end

BattleScript_EffectClearSmog:
	setmoveeffect MOVE_EFFECT_CLEAR_SMOG
	goto BattleScript_EffectHit

BattleScript_EffectToxicThread:
	setstatchanger STAT_SPEED, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailedAtkStringPpReduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, 0x0, BattleScript_ToxicThreadWorks
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_ButItFailedAtkStringPpReduce
BattleScript_ToxicThreadWorks:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_ToxicThreadTryPsn
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 0x2, BattleScript_ToxicThreadDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_ToxicThreadTryPsn
	pause 0x20
	goto BattleScript_ToxicThreadPrintString
BattleScript_ToxicThreadDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_ToxicThreadPrintString::
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_ToxicThreadTryPsn::
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectVenomDrench:
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus BS_TARGET, STATUS1_PSN_ANY, BattleScript_EffectVenomDrenchCanBeUsed
	goto BattleScript_ButItFailed
BattleScript_EffectVenomDrenchCanBeUsed:
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, 0x0, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPATK, 0x0, BattleScript_VenomDrenchDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, 0x0, BattleScript_CantLowerMultipleStats
BattleScript_VenomDrenchDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK | BIT_SPEED, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_VenomDrenchTryLowerSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VenomDrenchTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_VenomDrenchTryLowerSpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_VenomDrenchTryLowerSpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VenomDrenchTryLowerSpeed
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_VenomDrenchTryLowerSpeed::
	playstatchangeanimation BS_TARGET, BIT_SPEED, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_VenomDrenchEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_VenomDrenchEnd
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_VenomDrenchEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectNobleRoar:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, 0x0, BattleScript_NobleRoarDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, 0x0, BattleScript_CantLowerMultipleStats
BattleScript_NobleRoarDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_NobleRoarTryLowerSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_NobleRoarTryLowerSpAtk
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_NobleRoarTryLowerSpAtk::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_SPATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_NobleRoarEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_NobleRoarEnd
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_NobleRoarEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectShellSmash:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, 0xC, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, 0xC, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, 0, BattleScript_ShellSmashTryDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 0, BattleScript_ButItFailed
BattleScript_ShellSmashTryDef::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShellSmashTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShellSmashTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShellSmashTrySpDef:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShellSmashTryAttack
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShellSmashTryAttack
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShellSmashTryAttack:
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_ATK | BIT_SPEED, STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShellSmashTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShellSmashTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShellSmashTrySpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShellSmashTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShellSmashTrySpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShellSmashTrySpeed:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShellSmashEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShellSmashEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShellSmashEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectLastResort:
	attackcanceler
	attackstring
	ppreduce
	jumpifcantuselastresort BS_ATTACKER, BattleScript_ButItFailed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

BattleScript_EffectGrowth:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_GrowthDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_GrowthDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0x0
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_ANY, BattleScript_GrowthAtk2
	setstatchanger STAT_ATK, 1, FALSE
	goto BattleScript_GrowthAtk
BattleScript_GrowthAtk2:
	setstatchanger STAT_ATK, 2, FALSE
BattleScript_GrowthAtk:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_GrowthTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_GrowthTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_GrowthTrySpAtk::
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_ANY, BattleScript_GrowthSpAtk2
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_GrowthSpAtk
BattleScript_GrowthSpAtk2:
	setstatchanger STAT_SPATK, 2, FALSE
BattleScript_GrowthSpAtk:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_GrowthEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_GrowthEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_GrowthEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectSoak:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_MULTITYPE, BattleScript_ButItFailed
	jumpifability BS_TARGET, ABILITY_RKS_SYSTEM, BattleScript_ButItFailed
	jumpifsubstituteblocks BattleScript_ButItFailed
	attackanimation
	waitanimation
	trysoak BattleScript_ButItFailed
	printstring STRINGID_TRANSFORMEDINTOWATERTYPE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectReflectType:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryreflecttype BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_REFLECTTARGETSTYPE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectElectrify:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryelectrify BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TARGETELECTRIFIED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectShiftGear:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, 0xC, BattleScript_ShiftGearDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ATK, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_ShiftGearDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 0xA, BattleScript_ShiftGearSpeedBy1
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_ShiftGearDoSpeed
BattleScript_ShiftGearSpeedBy1:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED | BIT_ATK, 0x0
	setstatchanger STAT_SPEED, 1, FALSE
BattleScript_ShiftGearDoSpeed:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShiftGearTryAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShiftGearTryAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShiftGearTryAtk:
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_ShiftGearEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_ShiftGearEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_ShiftGearEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectCoil:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, 0xC, BattleScript_CoilDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_CoilDoMoveAnim:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_ACC, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_CoilTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoilTryDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CoilTryDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_CoilTryAcc
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoilTryAcc
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CoilTryAcc:
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_CoilEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoilEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CoilEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectQuiverDance:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, 0xC, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, 0xC, BattleScript_QuiverDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_QuiverDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF | BIT_SPEED, 0x0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_QuiverDanceTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_QuiverDanceTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_QuiverDanceTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_QuiverDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_QuiverDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_QuiverDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_QuiverDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_QuiverDanceEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_QuiverDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedUpHit:
	setmoveeffect MOVE_EFFECT_SPD_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectMeFirst:
	attackcanceler
	attackstring
	trymefirst BattleScript_ButItFailedPpReduce
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0x0
	setbyte sB_ANIM_TARGETS_HIT, 0x0
	jumptocalledmove TRUE

BattleScript_EffectAttackSpAttackUp:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_AttackSpAttackUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPATK, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_AttackSpAttackUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPATK, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_AttackSpAttackUpTrySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackSpAttackUpTrySpAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AttackSpAttackUpTrySpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_AttackSpAttackUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackSpAttackUpEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AttackSpAttackUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectAttackAccUp:
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 0xC, BattleScript_AttackAccUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_ACC, 0xC, BattleScript_CantRaiseMultipleStats
BattleScript_AttackAccUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_AttackAccUpTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackAccUpTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AttackAccUpTrySpDef::
	setstatchanger STAT_ACC, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_AttackAccUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackAccUpEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AttackAccUpEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectMistyTerrain:
BattleScript_EffectGrassyTerrain:
BattleScript_EffectElectricTerrain:
BattleScript_EffectPsychicTerrain:
	attackcanceler
	attackstring
	ppreduce
	setterrain BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gTerrainStringIds
	waitmessage 0x40
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	call BattleScript_TerrainSeedLoop
	jumpifabilitypresent ABILITY_MIMICRY, BattleScript_ApplyMimicry
	goto BattleScript_MoveEnd

BattleScript_ApplyMimicry::
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_MimicryLoopIter:
	copybyte sBATTLER, gBattlerTarget
	trytoapplymimicry BS_TARGET, BattleScript_MimicryLoop_NextBattler
	copybyte gBattlerAbility, sBATTLER
	@ call BattleScript_AbilityPopUp
	printstring STRINGID_BATTLERTYPECHANGEDTO
	waitmessage B_WAIT_TIME_LONG
BattleScript_MimicryLoop_NextBattler:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_MimicryLoopIter
	restoretarget
	goto BattleScript_MoveEnd

BattleScript_MimicryActivatesEnd3::
	printstring STRINGID_BATTLERTYPECHANGEDTO
	waitmessage 0x40
	end3

BattleScript_EffectTopsyTurvy:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPDEF, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPEED, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ACC, 6, BattleScript_EffectTopsyTurvyWorks
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_EVASION, 6, BattleScript_ButItFailed
BattleScript_EffectTopsyTurvyWorks:
	attackanimation
	waitanimation
	invertstatstages BS_TARGET
	printstring STRINGID_TOPSYTURVYSWITCHEDSTATS
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectIonDeluge:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	orword gFieldStatuses, STATUS_FIELD_ION_DELUGE
	setiondeluge
	attackanimation
	waitanimation
	printstring STRINGID_IONDELUGEON
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectQuash:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryquash BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_QUASHSUCCESS
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectHealPulse:
	attackcanceler
	attackstring
	ppreduce
	jumpifhealblock BS_ATTACKER, BattleScript_MoveUsedHealBlockPrevents @ stops pollen puff
    jumpifhealblock BS_TARGET, BattleScript_MoveUsedHealBlockPrevents
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifsubstituteblocks BattleScript_ButItFailed
	tryhealpulse BS_TARGET, BattleScript_AlreadyAtFullHp
	attackanimation
	waitanimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectEntrainment:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryentrainment BattleScript_ButItFailed
	attackanimation
	waitanimation
	setlastusedability BS_TARGET
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSimpleBeam:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setabilitysimple BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNACQUIREDSIMPLE
	waitmessage 0x40
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 0x1
	tryendneutralizinggas BS_TARGET
	tryendstench BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectSuckerPunch:
	attackcanceler
	suckerpunchcheck BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_HitFromAtkString

BattleScript_EffectLuckyChant:
	attackcanceler
	attackstring
	ppreduce
	setluckychant BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_SHIELDEDFROMCRITICALHITS
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMetalBurst:
	attackcanceler
	metalburstdamagecalculator BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bichalfword gMoveResultFlags, MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectHealingWish:
	attackcanceler
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_ButItFailedAtkStringPpReduce
	attackstring
	ppreduce
	attackanimation
	waitanimation
	instanthpdrop BS_ATTACKER
	setatkhptozero
	tryfaintmon BS_ATTACKER, FALSE, NULL
	openpartyscreen 0x1, BattleScript_EffectHealingWishEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 0x2
	returnatktoball
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	setbyte cMULTISTRING_CHOOSER 0
	jumpifnotchosenmove MOVE_LUNAR_DANCE BattleScript_EffectHealingWishNewMon
	setbyte cMULTISTRING_CHOOSER 1
	restorepp BS_ATTACKER
BattleScript_EffectHealingWishNewMon:
	printfromtable gHealingWishStringIds
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_WISH_HEAL, NULL
	waitanimation
	dmgtomaxattackerhp
	manipulatedamage NEGATIVE_DMG
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	clearstatus BS_ATTACKER
	waitstate
	updatestatusicon BS_ATTACKER
	waitstate
	printstring STRINGID_HEALINGWISHHEALED
	waitmessage 0x40
	switchineffects BS_ATTACKER
BattleScript_EffectHealingWishEnd:
	moveendall
	end

BattleScript_EffectWorrySeed:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	tryworryseed BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNACQUIREDABILITY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSplit:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	averagestats STAT_ATK
	averagestats STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSPOWER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSplit:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	averagestats STAT_DEF
	averagestats STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_SHAREDITSGUARD
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectHeartSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstatstages STAT_ATK
	swapstatstages STAT_DEF
	swapstatstages STAT_SPEED
	swapstatstages STAT_SPATK
	swapstatstages STAT_SPDEF
	swapstatstages STAT_EVASION
	swapstatstages STAT_ACC
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPowerSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstatstages STAT_ATK
	swapstatstages STAT_SPATK
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectGuardSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstatstages STAT_DEF
	swapstatstages STAT_SPDEF
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSpeedSwap:
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	swapstatstages STAT_SPEED
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDSTATCHANGES
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTelekinesis:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, NO_ACC_CALC_CHECK_LOCK_ON
	attackstring
	ppreduce
	settelekinesis BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNIDENTIFIED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectStealthRock:
	attackcanceler
	attackstring
	ppreduce
	setstealthrock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POINTEDSTONESFLOAT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectStickyWeb:
	attackcanceler
	attackstring
	ppreduce
	setstickyweb BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_STICKYWEBUSED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectGastroAcid:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setgastroacid BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSABILITYSUPPRESSED
	waitmessage 0x40
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 0x1
	tryendneutralizinggas BS_TARGET
	tryendstench BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_EffectToxicSpikes:
	attackcanceler
	attackstring
	ppreduce
	settoxicspikes BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_POISONSPIKESSCATTERED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_ToxicSpikesAbsorbed::
	printstring STRINGID_TOXICSPIKESABSORBED
	waitmessage 0x40
	return

BattleScript_ToxicSpikesPoisoned::
	printstring STRINGID_TOXICSPIKESPOISONED
	waitmessage 0x40
	statusanimation BS_SCRIPTING
	updatestatusicon BS_SCRIPTING
	waitstate
	return

BattleScript_StickyWebOnSwitchIn::
	savetarget
	copybyte gBattlerTarget, sBATTLER
	printstring STRINGID_STICKYWEBSWITCHIN
	waitmessage 0x40
	jumpifability BS_TARGET, ABILITY_MIRROR_ARMOR, BattleScript_MirrorArmorReflectStickyWeb
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_StickyWebOnSwitchInEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_StickyWebOnSwitchInStatAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_FELL_EMPTY, BattleScript_StickyWebOnSwitchInEnd
	pause 0x20
	goto BattleScript_StickyWebOnSwitchInPrintStatMsg
BattleScript_StickyWebOnSwitchInStatAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StickyWebOnSwitchInPrintStatMsg:
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_StickyWebOnSwitchInEnd:
	restoretarget
	return

BattleScript_EffectMagnetRise:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_MAGNET_RISE, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNLEVITATEDONELECTROMAGNETISM
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTrickRoom:
BattleScript_EffectWonderRoom:
BattleScript_EffectMagicRoom:
	attackcanceler
	attackstring
	ppreduce
	setroom
	attackanimation
	waitanimation
	printfromtable gRoomsStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectAquaRing:
	attackcanceler
	attackstring
	ppreduce
	setuserstatus3 STATUS3_AQUA_RING, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSURROUNDEDWITHVEILOFWATER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectEmbargo:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setembargo BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCANTUSEITEMSANYMORE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTailwind:
	attackcanceler
	attackstring
	ppreduce
	settailwind BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_TAILWINDBLEW
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMircleEye:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setmiracleeye BattleScript_ButItFailed
	goto BattleScript_IdentifiedFoe

BattleScript_EffectGravity:
	attackcanceler
	attackstring
	ppreduce
	setgravity BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_GRAVITYINTENSIFIED 
	waitmessage 0x40
	selectfirstvalidtarget
BattleScript_GravityLoop:
	movevaluescleanup
	jumpifstatus3 BS_TARGET, STATUS3_ON_AIR | STATUS3_MAGNET_RISE | STATUS3_TELEKINESIS, BattleScript_GravityLoopDrop
	goto BattleScript_GravityLoopEnd
BattleScript_GravityLoopDrop:
	bringdownairbornebattler BS_TARGET
	printstring STRINGID_GRAVITYGROUNDING 
	waitmessage 0x40
BattleScript_GravityLoopEnd:	
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_GravityLoop
	end   

BattleScript_EffectRoost:
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_TARGET
	setroost
	goto BattleScript_PresentHealTarget

BattleScript_EffectCaptivate:
	setstatchanger STAT_SPATK, 2, TRUE
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailedAtkStringPpReduce
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_ButItFailedAtkStringPpReduce
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_ButItFailedAtkStringPpReduce
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_ButItFailedAtkStringPpReduce
	jumpifoppositegenders BattleScript_CaptivateCheckAcc
	goto BattleScript_ButItFailedAtkStringPpReduce
BattleScript_CaptivateCheckAcc:
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	goto BattleScript_StatDownFromAttackString

BattleScript_EffectHealBlock:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifability BS_TARGET_SIDE, ABILITY_AROMA_VEIL, BattleScript_AromaVeilProtects
	sethealblock BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPREVENTEDFROMHEALING
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectThroatChop:
	jumpifsubstituteblocks BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_THROAT_CHOP | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectHitEscape:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	jumpifmovehadnoeffect BattleScript_MoveEnd
	setmoveeffectwithchance
	tryfaintmon BS_TARGET, FALSE, NULL
	moveendto MOVE_END_ATTACKER_VISIBLE
	moveendfrom MOVE_END_TARGET_VISIBLE
	jumpifbattleend BattleScript_HitEscapeEnd
	jumpifbyte CMP_NOT_EQUAL gBattleOutcome 0, BattleScript_HitEscapeEnd
	@jumpifbattletype BATTLE_TYPE_ARENA, BattleScript_HitEscapeEnd
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_HitEscapeEnd
	jumpifemergencyexited BS_TARGET, BattleScript_HitEscapeEnd
	openpartyscreen BS_ATTACKER, BattleScript_HitEscapeEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 0x2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
BattleScript_HitEscapeEnd:
	end

BattleScript_MoveEndEscape::		@for emergency exit
	jumpifcantswitch SWITCH_IGNORE_ESCAPE_PREVENTION | BS_ATTACKER, BattleScript_HitEscapeEnd
	openpartyscreen BS_ATTACKER, BattleScript_HitEscapeEnd
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 0x2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, TRUE
	waitstate
	switchineffects BS_ATTACKER
	goto BattleScript_HitEscapeEnd

BattleScript_EffectPlaceholder:
	attackcanceler
	attackstring
	ppreduce
	pause 0x5
	printstring STRINGID_NOTDONEYET
	goto BattleScript_MoveEnd

@vsonic tracking down battle bug
@changes I've made have had an effect so it means the game is actually IN this script
@but i'm also confused on what its dooing with the weird wrap affect,I assumed scripts were out of alignment and it was going to dif effect
@but that can't be right?
@seems to be happening on switchin/ battle start?
BattleScript_EffectHit::
	jumpifmove MOVE_SPLISHY_SPLASH, BattleScript_EffectParalyzeHit
	jumpifmove MOVE_FREEZE_SHOCK, BattleScript_EffectParalyzeHit
	jumpifmove MOVE_ICE_BURN, BattleScript_EffectBurnHit
	@jumpifnotmove MOVE_SURF, BattleScript_HitFromAtkCanceler	@hmm double check how logic is handled now, potentially remove this
	@jumpifnostatus3 BS_TARGET, STATUS3_UNDERWATER, BattleScript_HitFromAtkCanceler
	@orword gHitMarker, HITMARKER_IGNORE_UNDERWATER
	@setbyte sDMG_MULTIPLIER, 2
BattleScript_HitFromAtkCanceler::
	jumpifability BS_ATTACKER, ABILITY_MULTI_TASK, BattleScript_EffectMultiHit
	attackcanceler
BattleScript_HitFromAccCheck::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_HitFromAtkString::
	jumpifability BS_ATTACKER, ABILITY_MULTI_TASK, BattleScript_MultiHitFromAtkString
	ppreduce
BattleScript_SkyDropHitFromAtkString::
	attackstring	
BattleScript_HitFromCritCalc::
	critcalc		@ok actually I'm starting to think my type chart is just somehow out of sync? like its reading a different line than what it should be
	damagecalc
	typecalc	@typecalc has issue its only reading first type for some reason, also some other issue with wrap animation? effect? @something weirder absorb always not effective ghost moves always no effect against things it should effect
	call_if EFFECT_ROLLOUT	@somehow not working its being triggered everytime, when it shouldnt? thought that was a thing but then ran clean and no issue? / change to use nativeargs seems fine now?
	adjustnormaldamage	@THIS was the issue, forgot the currinstr increment *facepalm so obviously it couldnt continue passed this to animation
	pause 0x01	@was put after every adjustnormaldamage script, as added playcry pause is to clear values
BattleScript_HitFromAtkAnimation::
	attackanimation
	waitanimation
	effectivenesssound
	@groundonairbattlerwithoutgravity BS_TARGET	@Need to change this and make a jump put here becuz should make target visible, shuold work for evrthing  this is an issue
	hitanimation BS_TARGET	@fixed above issue was various command needed return not break, doesnt break but also just in wrong place
	waitstate
	groundonairbattlerwithoutgravity BS_TARGET
BattleScript_HitFromHpUpdate::
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	setmoveeffectwithchance		@seems to be fine
	argumenttomoveeffect	@seems to be fine
	tryfaintmon BS_TARGET, 0, NULL	@somehow this is an issue now, player mon isn't fainting animation
BattleScript_MoveEnd::
	moveendall
	end

BattleScript_GroundFlyingEnemywithoutGravity::
	printstring STRINGID_CRASHEDTOTHEGROUND
	waitmessage 0x20	
	return

BattleScript_EffectNaturalGift:
	attackcanceler
	attackstring
	ppreduce
	jumpifnotberry BS_ATTACKER, BattleScript_ButItFailed
	jumpifword CMP_COMMON_BITS, gFieldStatuses, STATUS_FIELD_MAGIC_ROOM, BattleScript_ButItFailed
	jumpifability BS_ATTACKER, ABILITY_KLUTZ, BattleScript_ButItFailed
	jumpifembargo BattleScript_ButItFailed
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setmoveeffectwithchance
	jumpifmovehadnoeffect BattleScript_EffectNaturalGiftEnd
	checkparentalbondcounter 2, BattleScript_EffectNaturalGiftEnd
	removeitem BS_ATTACKER
BattleScript_EffectNaturalGiftEnd:
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_MakeMoveMissed::
	orbyte gMoveResultFlags, MOVE_RESULT_MISSED
BattleScript_PrintMoveMissed::
	attackstring
	ppreduce
BattleScript_MoveMissedPause::
	pause 0x20
BattleScript_MoveMissed::
	effectivenesssound
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSleep::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_SLEEP, BattleScript_AlreadyAsleep
	jumpifcantmakeasleep BattleScript_CantMakeAsleep
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifability BS_TARGET_SIDE, ABILITY_SWEET_VEIL, BattleScript_SweetVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	typecalc
BattleScript_EndingSleepChecks:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_SLEEP
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_FlowerVeilProtectsRet::
	pause 0x20	
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage 0x40
	return

BattleScript_FlowerVeilProtects:
	call BattleScript_FlowerVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_SweetVeilProtectsRet::
	pause 0x20	
	printstring STRINGID_FLOWERVEILPROTECTED
	waitmessage 0x40
	return

BattleScript_SweetVeilProtects:
	call BattleScript_SweetVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AromaVeilProtectsRet::
	pause 0x20	
	printstring STRINGID_AROMAVEILPROTECTED
	waitmessage 0x40
	return

BattleScript_AromaVeilProtects:
	call BattleScript_AromaVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_PastelVeilProtectsRet::
	pause B_WAIT_TIME_SHORT
	@call BattleScript_AbilityPopUp
	printstring STRINGID_PASTELVEILPROTECTED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PastelVeilProtects:
	@call BattleScript_PastelVeilProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_LeafGuardProtectsRet::
	pause 0x20	
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage 0x40
	return

BattleScript_LeafGuardProtects:
	call BattleScript_LeafGuardProtectsRet
	orhalfword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_AlreadyAsleep::
	pause 0x20
	printstring STRINGID_PKMNALREADYASLEEP
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_WasntAffected::
	pause 0x20
	printstring STRINGID_PKMNWASNTAFFECTED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_CantMakeAsleep::
	pause 0x20
	printfromtable gUproarAwakeStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPoisonHit::
	jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_DoPoison
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_SkipToDmgPhase	@this jump would make it work as normal,but with function hange shoudnt need jump test without this line
BattleScript_DoPoison:
	setmoveeffect MOVE_EFFECT_POISON
BattleScript_SkipToDmgPhase:
	goto BattleScript_EffectHit

	@for some reason this is ALWAYS defaulting to moveresult not effective
BattleScript_EffectAbsorb::  @need setup multi task also make ghost with liquid ooze for extra troll...CURSOLA!
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
 	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	jumpifhealblock BS_ATTACKER, BattleScript_AbsorbHealBlock
	sethpdrain	@ without this, damgae to attacker is doubleed
	manipulatedamage DMG_BIG_ROOT		@makes negative to heal
 	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
 	jumpifability BS_TARGET, ABILITY_LIQUID_OOZE, BattleScript_AbsorbLiquidOoze	@should always be below DMG_BIG_ROOT
	setbyte cMULTISTRING_CHOOSER, 0
	goto BattleScript_AbsorbUpdateHp @went one by one, the problem was jumpifability from when I expanded abilities 

BattleScript_AbsorbLiquidOoze::
  	manipulatedamage NEGATIVE_DMG
	setbyte cMULTISTRING_CHOOSER, 1
BattleScript_AbsorbUpdateHp::
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_AbsorbTryFainting
	printfromtable gLeechSeedDrainStringIds
	waitmessage 0x40
BattleScript_AbsorbTryFainting::
	tryfaintmon BS_ATTACKER, 0, NULL
BattleScript_AbsorbHealBlock::
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectBurnHit::
BattleScript_EffectScald:
	setmoveeffect MOVE_EFFECT_BURN
	jumpifmove MOVE_ICE_BURN, BattleScript_HitFromAtkCanceler
	goto BattleScript_EffectHit

BattleScript_EffectParalyzeHit::
	setmoveeffect MOVE_EFFECT_PARALYSIS
	jumpifmove MOVE_SPLISHY_SPLASH, BattleScript_HitFromAtkCanceler
	jumpifmove MOVE_FREEZE_SHOCK, BattleScript_HitFromAtkCanceler
	goto BattleScript_EffectHit

BattleScript_EffectExplosion::
	attackcanceler
	attackstring
	ppreduce
	faintifabilitynotdamp
	setatkhptozero
	waitstate
	jumpifbyte CMP_NO_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_MISSED, BattleScript_ExplosionDoAnimStartLoop
	call BattleScript_PreserveMissedBitDoMoveAnim
	goto BattleScript_ExplosionLoop

BattleScript_ExplosionDoAnimStartLoop::
	attackanimation
	waitanimation
BattleScript_ExplosionLoop::
	movevaluescleanup
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	accuracycheck BattleScript_ExplosionMissed, ACC_CURR_MOVE
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, 0, NULL
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_ExplosionLoop
	tryfaintmon BS_ATTACKER, 0, NULL
	end

BattleScript_ExplosionMissed::
	effectivenesssound
	resultmessage
	waitmessage 0x40
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_ExplosionLoop
	tryfaintmon BS_ATTACKER, 0, NULL
	end

BattleScript_PreserveMissedBitDoMoveAnim::
	bicbyte gMoveResultFlags, MOVE_RESULT_MISSED
	attackanimation
	waitanimation
	orbyte gMoveResultFlags, MOVE_RESULT_MISSED
	return

BattleScript_EffectDreamEater::
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_DreamEaterNoEffect
	jumpifstatus BS_TARGET, STATUS1_SLEEP, BattleScript_DreamEaterWorked
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_DreamEaterWorked
BattleScript_DreamEaterNoEffect::
	attackstring
	ppreduce
	waitmessage 0x40
	goto BattleScript_WasntAffected

BattleScript_DreamEaterWorked::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	jumpifhealblock BS_ATTACKER, BattleScript_AbsorbHealBlock
	sethpdrain	@ without this, damgae to attacker is doubleed
	manipulatedamage DMG_BIG_ROOT		@makes negative to heal
 	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	jumpifmovehadnoeffect BattleScript_DreamEaterTryFaintEnd
	printstring STRINGID_PKMNDREAMEATEN
	waitmessage 0x40
BattleScript_DreamEaterTryFaintEnd::
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectMirrorMove::
	attackcanceler
	attackstring
	pause 0x40
	trymirrormove
	ppreduce
	orbyte gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_MIRRORMOVEFAILED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectAttackUp::
	setstatchanger STAT_ATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp::
	setstatchanger STAT_DEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpeedUp:
	setstatchanger STAT_SPEED, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialDefenseUp:
	setstatchanger STAT_SPDEF, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectAccuracyUp:
	setstatchanger STAT_ACC, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp::
	setstatchanger STAT_SPATK, 1, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectEvasionUp::
	setstatchanger STAT_EVASION, 1, FALSE
BattleScript_EffectStatUp::
	attackcanceler
BattleScript_EffectStatUpAfterAtkCanceler::
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_StatUpEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_StatUpAttackAnim
	pause 0x20
	@goto BattleScript_StatUpPrintString
	goto BattleScript_StatUpCantGoHigher

BattleScript_StatUpAttackAnim::
	attackanimation
	waitanimation
BattleScript_StatUpDoAnim::
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatUpPrintString::
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_StatUpEnd::
	goto BattleScript_MoveEnd

BattleScript_StatUpCantGoHigher::
	attackanimation
	waitanimation
	goto BattleScript_StatUpPrintString

BattleScript_StatUp::
	playanimation BS_EFFECT_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatUpMsg::
	printfromtable gStatUpStringIds
	waitmessage 0x40
	return

BattleScript_EffectAttackDown::
	setstatchanger STAT_ATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectDefenseDown::
	setstatchanger STAT_DEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpeedDown::
	setstatchanger STAT_SPEED, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectAccuracyDown::
	call_if EFFECT_ACCURACY_DOWN	@would prefer put after animation but way stat script works has to be here, stops sandattack from affecting earth types
	setstatchanger STAT_ACC, 1, TRUE
	goto BattleScript_EffectStatDown

@HOPE works if eerror would be because setmoveeffectwithchance is not at end of script hope not an issue dont know how else to deal with it
@had a weird thing where move missed but it still caused flinh effect, think its because I had setmoveeffectwithchance before an accuracy check
@that worked last fix is to still do move animation even when stat wont go lower
BattleScript_EffectFlash::
	setmoveeffect MOVE_EFFECT_FLINCH
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffectwithchance
	setstatchanger STAT_ACC, 1, TRUE
	goto BattleScript_StatDownFromAttackString

BattleScript_EffectSpecialAttackDown:
	setstatchanger STAT_SPATK, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialDefenseDown:
	setstatchanger STAT_SPDEF, 1, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectEvasionDown::
	setstatchanger STAT_EVASION, 1, TRUE
BattleScript_EffectStatDown::
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
BattleScript_StatDownFromAttackString::
	attackstring
	ppreduce
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_StatDownEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 2, BattleScript_StatDownDoAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 3, BattleScript_StatDownEnd
	pause 0x20
	@goto BattleScript_StatDownPrintString
	goto BattleScript_StatDownCantGoLower
@believe its referring to gStatDownStringIds less than 2 is stat fell, 2 is cant lower
@ pretty sure I commented out the other line to make it play animation even if stat cant be lowered need test, replace statdownend if need too
@VSONIC check this in case wrong, think issue of misunderstanding what multistring is referrnig too?

BattleScript_StatDownDoAnim::
	attackanimation
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_StatDownPrintString::
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_StatDownEnd::
	goto BattleScript_MoveEnd

BattleScript_StatDownCantGoLower::
	attackanimation
	waitanimation
	goto BattleScript_StatDownPrintString

BattleScript_StatDown::
	playanimation BS_EFFECT_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40
	return

@theres some weird logic here if a bs is defined and referred to in the C code it NEEDS to use the double colon :: single doesnt work  vsonic
BattleScript_EmpathAttackAnimation::
	attackanimation
	waitanimation
BattleScript_EmpathActivates::	
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_AbilityNoSpecificStatLoss
	statbuffchange STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_BS_PTR, BattleScript_EmpathEnd	@end if fail stat change
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_EmpathAnimation	@if able to lower go to animation
	goto BattleScript_MirrorArmorReflectPrintString	@else display stat cant fall message
BattleScript_EmpathAnimation:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_EmpathSecondLower:
	copybyte sBATTLER, gBattlerAttacker
	jumpifstatus2 BS_ATTACKER, STATUS2_SUBSTITUTE, BattleScript_AbilityNoSpecificStatLoss
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_BS_PTR, BattleScript_EmpathEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_SecondEmpathAnimation
	goto BattleScript_MirrorArmorReflectPrintString
BattleScript_SecondEmpathAnimation:
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_EmpathEnd:		@may need to be a return...yup needed to be a return -_-
	return

BattleScript_MirrorArmorAttackAnimation::
	attackanimation
	waitanimation
BattleScript_MirrorArmorReflect::
	pause B_WAIT_TIME_SHORT
	@call BattleScript_AbilityPopUp
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_AbilityNoSpecificStatLoss
BattleScript_MirrorArmorReflectStatLoss:
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_MIRROR_ARMOR | STAT_CHANGE_NOT_PROTECT_AFFECTED | STAT_CHANGE_BS_PTR, BattleScript_MirrorArmorReflectEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_MirrorArmorReflectAnim
	goto BattleScript_MirrorArmorReflectWontFall
BattleScript_MirrorArmorReflectAnim:
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_MirrorArmorReflectPrintString:
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_MirrorArmorReflectEnd:
	return

BattleScript_MirrorArmorReflectWontFall:
	copybyte gBattlerTarget, gBattlerAttacker   @ STRINGID_STATSWONTDECREASE uses target
	goto BattleScript_MirrorArmorReflectPrintString

@ gBattlerTarget is battler with Mirror Armor
BattleScript_MirrorArmorReflectStickyWeb:
	@call BattleScript_AbilityPopUp
	setattackertostickywebuser
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_StickyWebOnSwitchInEnd   @ Sticky web user not on field -> no stat loss
	goto BattleScript_MirrorArmorReflectStatLoss

BattleScript_EffectHaze::
	attackcanceler
	attackstring
	ppreduce
	attackanimation
	waitanimation
	normalisebuffs
	printstring STRINGID_STATCHANGESGONE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectBide::
	attackcanceler
	setbide
	attackstring
	ppreduce
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	goto BattleScript_MoveEnd

BattleScript_EffectRampage::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_EffectRampage2
	ppreduce
BattleScript_EffectRampage2::
	confuseifrepeatingattackends
	goto BattleScript_HitFromCritCalc

BattleScript_EffectRoar::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_SUCTION_CUPS, BattleScript_AbilityPreventsPhasingOut
	jumpifstatus3 BS_TARGET, STATUS3_ROOTED, BattleScript_PrintMonIsRooted
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
BattleScript_ForceRandomSwitch::	
	forcerandomswitch BattleScript_ButItFailed

@something here is causing freeze with furycutter, vsonic
@also just realized this doesn't have setmoveeffectwithchance or argumenttomoveeffect
@meaning this never sets extra effects...
@ok checked and that's more because usually multiihit IS the effect so those moves never got other effects...
@excluding things like twinneedle
@ok nvm twinneedle STILL only poisons on last hit until gen 4
@emerlad expansion revamped multihit and twinneedle just uses poison_hit with a twohit flag
@I'll take the best of both, removes most setmultihit commands just does logic in atk canceler command,
@doing that will let me use setmoveeffectchance & argumenttomoveeffect within loop ... I think
@will also need to slightly adjust multitask setup in effecthit: etc.
@but main issue is effect_multihit would trigger the script to go to effectmultihit therefore jumping OUT of the loop...
@I think what I can do is, use movevaluescleanup direclty after(or before) attackcanceler, and for multihit moves set the moveeffect to use in the argument
@and for multitask moves make sure they always jump to multihitfromatkstring to skip the move effect clear
@so twineedle would have argument MOVE_EFFECT_POISON and the script effect for it would only be a goto BattleScript_EffectMultiHit
@once in atkcanceler it'll read the effect of the move and set the counter to 2  (might as well replace with effect 2 hit honestly)
@no that was wrong, I put setmoveeffect MOVE_EFFECT_POISON in twineedle then a goto multihit from atk cancelere 
@it'll apply the poison when it gets to setmoveeffectwithchance  that way I can still use argument as well
@yeah that works was confused on what setmoveeffectwithchance did, it had nothing to do with effect it was move_effect all along
@ok other issue use of seteffectwithchance zeros out the move effect set in script which would mean it wouldnt be applied in loop
@only solution I can come up with is for multihit also set move effect based on effect in another macro command/function
@same as atkcancler is now used to set counter, it would need to go after movevaluescleanup
@do switch case for multihit moves that should do move effect like twinneedle (actually will need do for every move w effect cuz multitask)

BattleScript_EffectMultiHit::
	attackcanceler
	@ accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE  realized dont need 2 accuracycheck it could just as well miss on the first strike from the one below
BattleScript_MultiHitFromAtkString::
	attackstring
	ppreduce
	@setmultihitcounter2 0	@adjust script  for specific logic for move_present
	initmultihitstring
	@setbyte sMULTIHIT_EFFECT, 0  @now that i understand this, this clears stored move effects of multihit moves... twineedle jumps to below this to avoid the clear, so can remove
BattleScript_MultiHitLoop::
	jumpifhasnohp BS_ATTACKER, BattleScript_MultiHitEnd
	jumpifhasnohp BS_TARGET, BattleScript_MultiHitPrintStrings
	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoMultiHit
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_MultiHitPrintStrings
	accuracycheck BattleScript_MultiHitMiss, ACC_CURR_MOVE	@changed this for custom miss message double check and verify vsonic
BattleScript_DoMultiHit::
	movevaluescleanup		@this directly clears move effect, not sMULTIHIT_EFFECT, its needed to keep every hit from critting etc.
	@copybyte cEFFECT_CHOOSER, sMULTIHIT_EFFECT	@copies multihi_effect to effect choosesr don't know what that does with it after, something to do with gbattlecommunication + 3?
	getmoveeffect
	furycuttercalc
	presentdamagecalculation BattleScript_NewPresentHealMulti @if heal, I would need to skip passed crit calc etc then jump to play attack animation and do heal animation and text, then return in place to loop again
	critcalc			@plan set curr instr to BattleScript_MultiHitEndMessage  then do jump to and return from present heal logic (may need pushcursor call back?)
	damagecalc			@potentially do other way around, do push cursor call back to heal, from present dmg calc, and then set curr instruct to BattleScript_MultiHitEndMessage
	typecalc
	jumpifmovehadnoeffect BattleScript_MultiHitNoMoreHits
	adjustnormaldamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	groundonairbattlerwithoutgravity BS_TARGET
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
BattleScript_MultiHitEndMessages:
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1 @ to clear any buffer issues
	setmoveeffectwithchance
	argumenttomoveeffect
	@addbyte gBattleScripting + 12, 1   @ updated pret uses this "addbyte sMULTIHIT_STRING + 4, 1"
	addbyte sMULTIHIT_STRING + 4, 1
	moveendto MOVE_END_NEXT_TARGET
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_FOE_ENDURED, BattleScript_MultiHitPrintStrings
	decrementmultihit BattleScript_MultiHitLoop
	goto BattleScript_MultiHitPrintStrings

@jump here if presentdamagecalc would return do heal
BattleScript_NewPresentHealMulti::
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	call BattleScript_TargetHealAnimation
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage 0x40
	goto BattleScript_MultiHitEndMessages

BattleScript_MultiHitNoMoreHits:: @@MAKE multihit miss script specifically for fury cutter to print miss & number hits
	pause 0x20						@instead want to make all multi hit work that way
BattleScript_MultiHitPrintStrings::
	resultmessage
	waitmessage 0x40
	jumpifmovehadnoeffect BattleScript_MultiHitEnd		@this includes type not effect need something specifically for missing
	copyarray gBattleTextBuff1, sMULTIHIT_STRING, 6	@seems this determines how many times hit, I could change to use multitask - multihit counter
	printstring STRINGID_HITXTIMES
	waitmessage 0x40
BattleScript_MultiHitEnd::
	@setmoveeffectwithchance
	tryfaintmon BS_TARGET, 0, NULL
	moveendcase MOVE_END_SYNCHRONIZE_TARGET
	moveendfrom MOVE_END_STATUS_IMMUNITY_ABILITIES
	end

BattleScript_MultiHitMiss::
	pause 0x20
	effectivenesssound
	resultmessage
	waitmessage 0x2c
	copyarray gBattleTextBuff1, sMULTIHIT_STRING, 6
	printstring STRINGID_HITXTIMES
	waitmessage 0x32
	goto BattleScript_MultiHitEnd

BattleScript_EffectConversion::
	attackcanceler
	attackstring
	ppreduce
	tryconversiontypechange BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFlinchHit::
	setmoveeffect MOVE_EFFECT_FLINCH
	goto BattleScript_EffectHit

@test if works		cant remember wht this for	pretty sure not using, using argumenttomoveeffect  instead if this was for traps
@ok checked this is from emerald, for things like thunder fang ice fang fire fang etc.
BattleScript_EffectFlinchStatus:
	setmoveeffect MOVE_EFFECT_FLINCH
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	setmoveeffectwithchance
	argumentstatuseffect
	tryfaintmon BS_TARGET, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectRestoreHp::
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_ATTACKER
	attackanimation
	waitanimation
BattleScript_RestoreHp:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectToxic::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_IMMUNITY, BattleScript_ImmunityProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifability BS_TARGET_SIDE, ABILITY_PASTEL_VEIL, BattleScript_PastelVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifability BS_ATTACKER, ABILITY_CORROSION, BattleScript_EndingToxicChecks
	typecalc
BattleScript_EndingToxicChecks:
	@jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_AlreadyPoisoned
	jumpifstatus BS_TARGET, STATUS1_TOXIC_POISON, BattleScript_AlreadyPoisoned
	jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_ToxicAccuracyCheck
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
BattleScript_ToxicAccuracyCheck:
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_TOXIC
	seteffectprimary
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AlreadyPoisoned::
	pause 0x40
	printstring STRINGID_PKMNALREADYPOISONED
	waitmessage 0x40
	goto BattleScript_MoveEnd


BattleScript_ImmunityProtected::
	copybyte gEffectBattler, gBattlerTarget
	setbyte cMULTISTRING_CHOOSER, 0
	call BattleScript_PSNPrevention
	goto BattleScript_MoveEnd

BattleScript_EffectPayDay::
	setmoveeffect MOVE_EFFECT_PAYDAY
	goto BattleScript_EffectHit

BattleScript_EffectAuroraVeil:
	attackcanceler
	attackstring
	ppreduce
	setauroraveil BS_ATTACKER
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectLightScreen::
	attackcanceler
	attackstring
	ppreduce
	setlightscreen
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectTriAttack::
	setmoveeffect MOVE_EFFECT_TRI_ATTACK
	goto BattleScript_EffectHit

BattleScript_EffectRest::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_RestIsAlreadyAsleep
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_RestIsAlreadyAsleep
	jumpifcantmakeasleep BattleScript_RestCantSleep
	trysetrest BattleScript_AlreadyAtFullHp
	pause 0x20
	printfromtable gRestUsedStringIds
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	waitstate
	goto BattleScript_PresentHealTarget

BattleScript_RestCantSleep::
	pause 0x40
	printfromtable gUproarAwakeStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_RestIsAlreadyAsleep::
	pause 0x20
	printstring STRINGID_PKMNALREADYASLEEP2
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectOHKO::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	typecalc
	jumpifmovehadnoeffect BattleScript_HitFromAtkAnimation
	tryKO BattleScript_KOFail
	trysetdestinybondtohappen
	goto BattleScript_HitFromAtkAnimation

BattleScript_KOFail::
	pause 0x40
	printfromtable gKOFailedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

@not used
BattleScript_EffectRazorWind::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, 0
	call BattleScriptFirstChargingTurn
	goto BattleScript_MoveEnd

BattleScript_TwoTurnMovesSecondTurn::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	argumenttomoveeffect
	goto BattleScript_HitFromAccCheck

BattleScriptFirstChargingTurn::
	attackcanceler
	printstring STRINGID_EMPTYSTRING3
	ppreduce
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	copybyte cMULTISTRING_CHOOSER, sTWOTURN_STRINGID
	printfromtable gFirstTurnOfTwoStringIds
	waitmessage 0x40
	return

BattleScript_EffectSuperFang::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	damagetohalftargethp
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectDragonRage::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	setword gBattleMoveDamage, 40
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectTrap::
	setmoveeffect MOVE_EFFECT_WRAP	@goes to BattleScript_MoveEffectWrap sets status & stringID
	goto BattleScript_EffectHit

BattleScript_EffectDoubleHit::
	attackcanceler
	goto BattleScript_MultiHitFromAtkString

BattleScript_EffectRecoilIfMiss::
	attackcanceler
	typecalc	@put higher to aply for both jumps @as before any dmg calc doesnt affect dmg
	accuracycheck BattleScript_MoveMissedDoDamage, ACC_CURR_MOVE	
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveMissedDoDamage
	goto BattleScript_HitFromAtkString

@recoil
BattleScript_MoveMissedDoDamage::
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_PrintMoveMissed
	attackstring
	ppreduce
	pause 0x40
	resultmessage
	waitmessage 0x40
	@typecalc remove cuz worry about double calc, even if not an issue
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_RecoilTargetImmuneDoDamage
	printstring STRINGID_PKMNCRASHED
	waitmessage 0x40
	damagecalc
	adjustnormaldamage
	manipulatedamage RECOIL_MISS_DMG
	bicbyte gMoveResultFlags, MOVE_RESULT_MISSED
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	orbyte gMoveResultFlags, MOVE_RESULT_MISSED
	goto BattleScript_MoveEnd

BattleScript_RecoilTargetImmuneDoDamage::
	printstring STRINGID_PKMNCRASHED
	waitmessage 0x40
	damagecalc
	typecalc
	adjustnormaldamage
	manipulatedamage RECOIL_MISS_DMG
	bicbyte gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	orbyte gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_EffectMist::
	attackcanceler
	attackstring
	ppreduce
	setmist
	attackanimation
	waitanimation
	printfromtable gMistUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFocusEnergy::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY, BattleScript_ButItFailed
	setfocusenergy
	attackanimation
	waitanimation
	printfromtable gFocusEnergyUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTripleArrows::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstatus2 BS_ATTACKER, STATUS2_FOCUS_ENERGY, BattleScript_TripleArrowsMoveAnimation
	setfocusenergy
	printfromtable gFocusEnergyUsedStringIds
	waitmessage 0x40
BattleScript_TripleArrowsMoveAnimation:
	attackanimation
	waitanimation
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	setmoveeffectwithchance
	argumenttomoveeffect
BattleScript_TripleArrowsMoveEnd:
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectRecoil::
	setmoveeffect MOVE_EFFECT_RECOIL_25 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	jumpifnotmove MOVE_STRUGGLE, BattleScript_EffectHit
	incrementgamestat GAME_STAT_USED_STRUGGLE
	goto BattleScript_EffectHit

BattleScript_EffectConfuse::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_AlreadyConfused
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AlreadyConfused::
	pause 0x20
	printstring STRINGID_PKMNALREADYCONFUSED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectAttackUp2::
	setstatchanger STAT_ATK, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp2::
	setstatchanger STAT_DEF, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectDefenseUp3:
	setstatchanger STAT_DEF, 3, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpeedUp2::
	setstatchanger STAT_SPEED, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp2::
	setstatchanger STAT_SPATK, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialDefenseUp2::
	setstatchanger STAT_SPDEF, 2, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectSpecialAttackUp3::
	setstatchanger STAT_SPATK, 3, FALSE
	goto BattleScript_EffectStatUp

BattleScript_EffectTransform::
	attackcanceler
	attackstring
	ppreduce
	transformdataexecution
	attackanimation
	waitanimation
	printfromtable gTransformUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

@ using True on end means stat lowers, False means stat raises, number represents number of stat stages to change

BattleScript_EffectAttackDown2::
	setstatchanger STAT_ATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectDefenseDown2::
	setstatchanger STAT_DEF, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpeedDown2::
	setstatchanger STAT_SPEED, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialDefenseDown2::
	setstatchanger STAT_SPDEF, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectSpecialAttackDown2:
	setstatchanger STAT_SPATK, 2, TRUE
	goto BattleScript_EffectStatDown

BattleScript_EffectReflect::
	attackcanceler
	attackstring
	ppreduce
	setreflect
BattleScript_PrintReflectLightScreenSafeguardString::
	attackanimation
	waitanimation
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPoison::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_IMMUNITY, BattleScript_ImmunityProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifability BS_TARGET_SIDE, ABILITY_PASTEL_VEIL, BattleScript_PastelVeilProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_POISON, BattleScript_SkiptoPoison
	jumpifstatus BS_TARGET, STATUS1_TOXIC_POISON, BattleScript_AlreadyPoisoned
	jumpifability BS_ATTACKER, ABILITY_CORROSION, BattleScript_EndingPoisonChecks
	typecalc
BattleScript_EndingPoisonChecks:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
BattleScript_SkiptoPoison:
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_POISON
	seteffectprimary
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

@status filters already in setmoveeffect, but added typecalc to these
@ for more specificity on which moves can be used to effect which mon
@i.e doesnt make sense for thunderwave to paralyze a groudn type, even though they can be paralyzed
@use ability jump checks if more corosion like abilities are added
@that would get around type immunity, as in above example
BattleScript_EffectParalyze::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_LIMBER, BattleScript_LimberProtected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	typecalc 
BattleScript_EndingParalysisChecks:
	jumpifstatus BS_TARGET, STATUS1_PARALYSIS, BattleScript_AlreadyParalyzed
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AlreadyParalyzed::
	pause 0x20
	printstring STRINGID_PKMNISALREADYPARALYZED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_LimberProtected::
	copybyte gEffectBattler, gBattlerTarget
	setbyte cMULTISTRING_CHOOSER, 0
	call BattleScript_PRLZPrevention
	goto BattleScript_MoveEnd

BattleScript_EffectAttackDownHit::
	setmoveeffect MOVE_EFFECT_ATK_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectDefenseDownHit::
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpeedDownHit::
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectSpecialAttackDownHit::
	setmoveeffect MOVE_EFFECT_SP_ATK_MINUS_1
	goto BattleScript_EffectHit


BattleScript_EffectSpecialDefenseDownHit::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_1
	goto BattleScript_EffectHit
	
BattleScript_EffectSpecialDefenseDownHit2::
	setmoveeffect MOVE_EFFECT_SP_DEF_MINUS_2
	goto BattleScript_EffectHit

BattleScript_EffectAccuracyDownHit::
	setmoveeffect MOVE_EFFECT_ACC_MINUS_1
	goto BattleScript_EffectHit

BattleScript_EffectHurricane:
BattleScript_EffectConfuseHit::
	setmoveeffect MOVE_EFFECT_CONFUSION
	goto BattleScript_EffectHit

BattleScript_EffectTwineedle::
	attackcanceler
	goto BattleScript_MultiHitFromAtkString

BattleScript_EffectSubstitute::
	attackcanceler
	ppreduce
	attackstring
	waitstate
	jumpifstatus2 BS_ATTACKER, STATUS2_SUBSTITUTE, BattleScript_AlreadyHasSubstitute
	setsubstitute
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 1, BattleScript_SubstituteAnim
	pause 0x20
	goto BattleScript_SubstituteString

BattleScript_SubstituteAnim::
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_SubstituteString::
	printfromtable gSubsituteUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AlreadyHasSubstitute::
	pause 0x20
	printstring STRINGID_PKMNHASSUBSTITUTE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRecharge::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RECHARGE | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromAtkString

BattleScript_MoveUsedMustRecharge::
	printstring STRINGID_PKMNMUSTRECHARGE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRage::
	attackcanceler
	accuracycheck BattleScript_RageMiss, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_RAGE
	seteffectprimary
	setmoveeffect 0
	goto BattleScript_HitFromAtkString

BattleScript_RageMiss::
	setmoveeffect MOVE_EFFECT_RAGE
	clearstatusfromeffect BS_ATTACKER
	goto BattleScript_PrintMoveMissed

BattleScript_EffectMimic::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	mimicattackcopy BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNLEARNEDMOVE2
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMetronome::
	attackcanceler
	attackstring
	pause 0x20
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	metronome
BattleScript_EffectLeechSeed::
	attackcanceler
	attackstring
	pause 0x20
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck .+6, ACC_CURR_MOVE
	setseeded
	attackanimation
	waitanimation
	printfromtable gLeechSeedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSplash::
	attackcanceler
	attackstring
	ppreduce
	attackanimation
	waitanimation
	incrementgamestat GAME_STAT_USED_SPLASH
	printstring STRINGID_BUTNOTHINGHAPPENED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectDisable::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	disablelastusedattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNMOVEWASDISABLED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectLevelDamage::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE	@so these lines just remove super & not effective values from moves, so only type immunities affect it
	dmgtolevel
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectPsywave::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE	@dont know what this does, check it vsonic @ok these moves always hit for neutral,
	psywavedamageeffect
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation	@skips dmg calc command

@psywave effect except, it is affected by typing, so can be super
@kept for notes not used just using psywave put flinch in argument
BattleScript_EffectSnowball::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE	@with buff to psywavedmg realized need keep this, cant do stab or super would be too strong
	psywavedamageeffect	@balance by giving flinch chance, psywave doesnt need  extra effect but this is losing offense ability of ice type
	adjustsetdamage				
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectCounter::
	attackcanceler
	typecalc
	counterdamagecalculator BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectEncore::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trysetencore BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNGOTENCORE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPainSplit::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	painsplitdmgcalc BattleScript_ButItFailed
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	copyword gBattleMoveDamage, sPAINSPLIT_HP
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_SHAREDPAIN
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSnore::
	attackcanceler
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_SnoreIsAsleep
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_SnoreIsAsleep
	attackstring
	ppreduce
	goto BattleScript_ButItFailed

BattleScript_SnoreIsAsleep::
	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoSnore
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage 0x40
	statusanimation BS_ATTACKER
BattleScript_DoSnore::
	attackstring
	ppreduce
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_FLINCH
	goto BattleScript_HitFromCritCalc

BattleScript_EffectConversion2::
	attackcanceler
	attackstring
	ppreduce
	settypetorandomresistance BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectLockOn::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	setalwayshitflag
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTOOKAIM
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSketch:: @changes should allow temp copy, just need to add stat increase
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	mimicattackcopy BattleScript_ButItFailed
	call BattleScript_EffectSketchStatUp @if done right checks for move sucess does stat increase then move animation
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSKETCHEDMOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMonotype::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	copymovepermanently BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSKETCHEDMOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSleepTalk::
	attackcanceler
	jumpifability BS_ATTACKER, ABILITY_COMATOSE, BattleScript_SleepTalkIsAsleep
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_SleepTalkIsAsleep
	attackstring
	ppreduce
	goto BattleScript_ButItFailed

BattleScript_SleepTalkIsAsleep::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage 0x40
	statusanimation BS_ATTACKER
	attackstring
	ppreduce
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	trychoosesleeptalkmove BattleScript_SleepTalkUsingMove
	pause 0x40
	goto BattleScript_ButItFailed

BattleScript_SleepTalkUsingMove::
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove 1
BattleScript_EffectDestinyBond::
	attackcanceler
	attackstring
	ppreduce
	setdestinybond
	attackanimation
	waitanimation
	printstring STRINGID_PKMNTRYINGTOTAKEFOE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFlail::
	remaininghptopower
	goto BattleScript_EffectHit

BattleScript_EffectSpite::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryspiteppreduce BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectEerieSpell::	@excluded from multitask
	attackcanceler
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryspiteppreduce BattleScript_HitFromAtkString	@jumps if fails to reduce pp, would activate multitask, but is fine since it wont reduce pp.
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	printstring STRINGID_PKMNREDUCEDPP
	waitmessage 0x40
	setmoveeffectwithchance
	argumenttomoveeffect
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectHealBell::
	attackcanceler
	attackstring
	ppreduce
	healpartystatus
	waitstate
	attackanimation
	waitanimation
	printfromtable gPartyStatusHealStringIds
	waitmessage 0x40
	jumpifnotmove MOVE_HEAL_BELL, BattleScript_PartyHealEnd
	jumpifbyte CMP_NO_COMMON_BITS, cMULTISTRING_CHOOSER, 1, BattleScript_CheckHealBellMon2Unaffected
	printstring STRINGID_PKMNSXBLOCKSY
	waitmessage 0x40
BattleScript_CheckHealBellMon2Unaffected::
	jumpifbyte CMP_NO_COMMON_BITS, cMULTISTRING_CHOOSER, 2, BattleScript_PartyHealEnd
	printstring STRINGID_PKMNSXBLOCKSY2
	waitmessage 0x40
BattleScript_PartyHealEnd::
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	goto BattleScript_MoveEnd

BattleScript_EffectTripleKick::
	attackcanceler
	attackstring
	ppreduce
	@setbyte sTRIPLE_KICK_POWER, 0	@wont need this when done
	@setbyte gBattleScripting + 19, 0	@pretty sure is triple_kick_power in scripting battlestruct, so also remove?
	initmultihitstring
	@setmultihit 3
BattleScript_TripleKickLoop::
	jumpifhasnohp BS_ATTACKER, BattleScript_TripleKickEnd
	jumpifhasnohp BS_TARGET, BattleScript_TripleKickNoMoreHits
	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoTripleKickAttack
	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_TripleKickNoMoreHits
BattleScript_DoTripleKickAttack::
	accuracycheck BattleScript_TripleKickNoMoreHits, ACC_CURR_MOVE
	movevaluescleanup
	@jumpifmove MOVE_SURGING_STRIKES, EffectTripleKick_DoDmgCalcs    @ no power boost each hit
	@jumpifmove MOVE_TRIPLE_AXEL, EffectTripleKick_TripleAxelBoost   @ triple axel gets +20 power
	@addbyte sTRIPLE_KICK_POWER, 10                                  @ triple kick gets +10 power
	addbyte gBattleScripting + 12, 1		@leaving this, think its a multi hit string?
	goto EffectTripleKick_DoDmgCalcs
EffectTripleKick_TripleAxelBoost:
	@addbyte sTRIPLE_KICK_POWER, 20
EffectTripleKick_DoDmgCalcs:
	@copyhword gDynamicBasePower, sTRIPLE_KICK_POWER
	critcalc		@added alwayscrit logic to critcalc, should make surgingstrikes work
	damagecalc
	typecalc
	jumpifmovehadnoeffect BattleScript_TripleKickNoMoreHits  @thinking shouldn't just put this right below typecalc?
	adjustnormaldamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	moveendto MOVE_END_NEXT_TARGET
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_FOE_ENDURED, BattleScript_TripleKickPrintStrings
	decrementmultihit BattleScript_TripleKickLoop
	goto BattleScript_TripleKickPrintStrings

BattleScript_TripleKickNoMoreHits::
	pause 0x20
	jumpifbyte CMP_EQUAL, gBattleScripting + 12, 0, BattleScript_TripleKickPrintStrings
	bicbyte gMoveResultFlags, MOVE_RESULT_MISSED
BattleScript_TripleKickPrintStrings::
	resultmessage
	waitmessage 0x40
	jumpifbyte CMP_EQUAL, gBattleScripting + 12, 0, BattleScript_TripleKickEnd
	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_TripleKickEnd
	copyarray gBattleTextBuff1, sMULTIHIT_STRING, 6
	printstring STRINGID_HITXTIMES
	waitmessage 0x40
BattleScript_TripleKickEnd::
	setmoveeffectwithchance
	tryfaintmon BS_TARGET, 0, NULL
	moveendfrom MOVE_END_UPDATE_LAST_MOVES
	end

BattleScript_EffectThief::
	setmoveeffect MOVE_EFFECT_STEAL_ITEM
	goto BattleScript_EffectHit

BattleScript_EffectHitPreventEscape:
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	goto BattleScript_EffectHit

BattleScript_EffectMeanLook::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_TARGETCANTESCAPENOW
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectNightmare::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus2 BS_TARGET, STATUS2_NIGHTMARE, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_SLEEP, BattleScript_NightmareWorked
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_NightmareWorked
	goto BattleScript_ButItFailed

BattleScript_NightmareWorked::
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_NIGHTMARE
	seteffectprimary
	printstring STRINGID_PKMNFELLINTONIGHTMARE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMinimize::
	attackcanceler
	setminimize
	setstatchanger STAT_EVASION, 1, FALSE
	goto BattleScript_EffectStatUpAfterAtkCanceler

BattleScript_EffectCurse::	@
	jumpiftype BS_ATTACKER, TYPE_GHOST, BattleScript_GhostCurse
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_SPEED, 0, BattleScript_CurseTrySpeed
	jumpifstat BS_ATTACKER, CMP_NOT_EQUAL, STAT_ATK, 12, BattleScript_CurseTrySpeed
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_DEF, 12, BattleScript_ButItFailed
BattleScript_CurseTrySpeed::
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte sB_ANIM_TURN, 1
	attackanimation
	waitanimation
	setstatchanger STAT_SPEED, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CurseTryAttack
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_CurseTryAttack::
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CurseTryDefence
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CurseTryDefence::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CurseEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CurseEnd::
	goto BattleScript_MoveEnd

BattleScript_GhostCurse::
	jumpifbytenotequal gBattlerAttacker, gBattlerTarget, BattleScript_DoGhostCurse
	getmovetarget BS_ATTACKER
BattleScript_DoGhostCurse::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	cursetarget BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectDryadsCurse::
	attackcanceler	@will set correct target like bide, to last attacker to damage user
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_ATK, 0x0, BattleScript_CantLowerMultipleStats @fail without cursing if can""t lower stat
	cursetarget BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	setbyte sB_ANIM_TURN, 0	@ 
	attackanimation
	waitanimation
	printstring STRINGID_PKMNLAIDCURSE
	waitmessage 0x40
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_MoveEnd	@ as already have fail if cant lower stat this will never jump
	printfromtable gStatDownStringIds
	@healthbarupdate BS_ATTACKER  not doing health sacrifice, put stat drops here instead
	@datahpupdate BS_ATTACKER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMatBlock::
	attackcanceler
	jumpifnotfirstturn BattleScript_ButItFailedAtkStringPpReduce
	goto BattleScript_ProtectLikeAtkString

BattleScript_EffectProtect::
	attackcanceler
BattleScript_ProtectLikeAtkString::
	attackstring
	ppreduce
	setprotectlike
	attackanimation
	waitanimation
	printfromtable gProtectLikeUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSpikes::
	attackcanceler
	trysetspikes BattleScript_ButItFailedAtkStringPpReduce
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_SPIKESSCATTERED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectForesight::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setforesight
BattleScript_IdentifiedFoe:
	attackanimation
	waitanimation
	printstring STRINGID_PKMNIDENTIFIED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPerishSong::
	attackcanceler
	attackstring
	ppreduce
	trysetperishsong BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_FAINTINTHREE
	waitmessage 0x40
	setbyte sBATTLER, 0
BattleScript_PerishSongLoop::
	jumpifability BS_SCRIPTING, ABILITY_SOUNDPROOF, BattleScript_PerishSongNotAffected
BattleScript_PerishSongLoopIncrement::
	addbyte sBATTLER, 1
	jumpifbytenotequal sBATTLER, gBattlersCount, BattleScript_PerishSongLoop
	goto BattleScript_MoveEnd

BattleScript_PerishSongNotAffected::
	printstring STRINGID_PKMNSXBLOCKSY2
	waitmessage 0x40
	goto BattleScript_PerishSongLoopIncrement

BattleScript_PerishBodyActivates::
	@call BattleScript_AbilityPopUp
	printstring STRINGID_FAINTINTHREE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	return

BattleScript_GulpMissileGorging::
	@call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_GULP_MISSILE, sB_ANIM_ARG1
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_GulpMissileNoDmgGorging
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, FALSE, NULL
	getbattlerfainted BS_ATTACKER
	jumpifbyte CMP_EQUAL, gBattleCommunication, TRUE, BattleScript_GulpMissileNoSecondEffectGorging
BattleScript_GulpMissileNoDmgGorging:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE, sB_ANIM_ARG1
	waitanimation
	swapattackerwithtarget
	setmoveeffect MOVE_EFFECT_PARALYSIS
	seteffectprimary
	swapattackerwithtarget
	return
BattleScript_GulpMissileNoSecondEffectGorging:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE, sB_ANIM_ARG1
	waitanimation
	return

BattleScript_GulpMissileGulping::
	@call BattleScript_AbilityPopUp
	playanimation BS_ATTACKER, B_ANIM_GULP_MISSILE, sB_ANIM_ARG1
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_GulpMissileNoDmgGulping
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, FALSE, NULL
	getbattlerfainted BS_ATTACKER
	jumpifbyte CMP_EQUAL, gBattleCommunication, TRUE, BattleScript_GulpMissileNoSecondEffectGulping
	jumpifability BS_ATTACKER, ABILITY_CLEAR_BODY, BattleScript_GulpMissileNoSecondEffectGulping
	jumpifability BS_ATTACKER, ABILITY_FULL_METAL_BODY, BattleScript_GulpMissileNoSecondEffectGulping
	jumpifability BS_ATTACKER, ABILITY_WHITE_SMOKE, BattleScript_GulpMissileNoSecondEffectGulping
	jumpifability BS_ATTACKER, ABILITY_LIQUID_METAL, BattleScript_GulpMissileNoSecondEffectGulping
	jumpifflowerveilattacker BattleScript_GulpMissileNoSecondEffectGulping
BattleScript_GulpMissileNoDmgGulping:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE, sB_ANIM_ARG1
	waitanimation
	swapattackerwithtarget @ to make gStatDownStringIds down below print the right battler
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_GulpMissileGorgingTargetDefenseCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget @ restore the battlers, just in case
	return
BattleScript_GulpMissileNoSecondEffectGulping:
	handleformchange BS_TARGET, 0
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE, sB_ANIM_ARG1
	waitanimation
	return
BattleScript_GulpMissileGorgingTargetDefenseCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectSandstorm::
	attackcanceler
	attackstring
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	setsandstorm
	goto BattleScript_MoveWeatherChange

BattleScript_EffectRollout::
	attackcanceler
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_RolloutHit
	ppreduce
BattleScript_RolloutHit::
	accuracycheck .+6, ACC_CURR_MOVE
	@typecalc2 @was just for ending multi turn if move would have no effect -_- replace this with callif  (do switch case check for move effect and just do what I need it to then continue)
	rolloutdamagecalculation	@in this case switch over battlemoves[gCurrentMove].effect  if rollout, run function cancelmultiturn if no effect  not explicitly a bs call but same effect, 
	goto BattleScript_HitFromCritCalc		@since call is just executing some logic, then continuining on in the script	vsonic  using callnative to setup

BattleScript_EffectSwagger::
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_MakeMoveMissed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifconfusedandstatmaxed 1, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_SwaggerTryConfuse
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_SwaggerTryConfuse
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_SwaggerTryConfuse::
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_AbilityPreventsMoodShift
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_AbilityPreventsMoodShift
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	goto BattleScript_MoveEnd

@Need to fix this so it displays miss message
@ and then number of hits
@ accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE  think I need that
BattleScript_EffectFuryCutter::
	attackcanceler
	goto BattleScript_MultiHitFromAtkString

@BattleScript_FuryCutterLoop::
@	jumpifhasnohp BS_ATTACKER, BattleScript_FuryCutterEnd
@	jumpifhasnohp BS_TARGET, BattleScript_FuryCutterNoMoreHits
@	jumpifhalfword CMP_EQUAL, gChosenMove, MOVE_SLEEP_TALK, BattleScript_DoFuryCutterAttack
@	jumpifstatus BS_ATTACKER, STATUS1_SLEEP, BattleScript_FuryCutterNoMoreHits
@BattleScript_DoFuryCutterAttack::
@	accuracycheck BattleScript_FuryCutterNoMoreHits, ACC_CURR_MOVE
@	movevaluescleanup
@  	addbyte gBattleScripting + 12, 1
@	furycuttercalc
@	critcalc
@	damagecalc
@	typecalc
@	jumpifmovehadnoeffect BattleScript_FuryCutterNoMoreHits
@	adjustnormaldamage
@	attackanimation
@	waitanimation
@	effectivenesssound
@	hitanimation BS_TARGET
@	waitstate
@	healthbarupdate BS_TARGET
@	datahpupdate BS_TARGET
@	critmessage
@	waitmessage 0x40
@	printstring STRINGID_EMPTYSTRING3
@	waitmessage 1
@	moveendto MOVE_END_NEXT_TARGET
@	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_FOE_ENDURED, BattleScript_FuryCutterPrintStrings
@	decrementmultihit BattleScript_FuryCutterLoop
@	goto BattleScript_FuryCutterPrintStrings
@BattleScript_FuryCutterNoMoreHits::
@	pause 0x20
@	jumpifbyte CMP_EQUAL, gBattleScripting + 12, 0, BattleScript_FuryCutterPrintStrings
@	bicbyte gMoveResultFlags, MOVE_RESULT_MISSED
@BattleScript_FuryCutterPrintStrings::
@	resultmessage
@	waitmessage 0x40
@	jumpifbyte CMP_EQUAL, gBattleScripting + 12, 0, BattleScript_FuryCutterEnd
@	jumpifbyte CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_FuryCutterEnd
@	copyarray gBattleTextBuff1, sMULTIHIT_STRING, 6
@	printstring STRINGID_HITXTIMES
@	waitmessage 0x40
@BattleScript_FuryCutterEnd::
@	setmoveeffectwithchance
@	tryfaintmon BS_TARGET, 0, NULL
@	moveendfrom 14
@	end

BattleScript_EffectAttract::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryinfatuating BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectAttractHit::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryinfatuating BattleScript_HitFromAtkAnimation
	setmoveeffect MOVE_EFFECT_ATTRACT
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectReturn::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	happinesstodamagecalculation
	goto BattleScript_HitFromAtkString

BattleScript_EffectTargetTypeBasedDmg::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	typebaseddmgboost
	call_if EFFECT_TARGET_TYPE_DAMAGE	@set defensedown effect back for rock smash
	goto BattleScript_HitFromAtkString

BattleScript_EffectPresent::
	attackcanceler
	goto BattleScript_MultiHitFromAtkString
	@ppreduce
	@typecalc
	@accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE	@loop start here
	@attackstring	
	@presentdamagecalculation	@need to setup heal logic, think need change this command to a jump condition, 
	@if heal, I would need to skip passed crit calc etc then jump to play attack animation and do heal animation and text, then return in place to loop again  VSONIC


BattleScript_EffectSafeguard::
	attackcanceler
	attackstring
	ppreduce
	setsafeguard
	goto BattleScript_PrintReflectLightScreenSafeguardString

BattleScript_EffectThawHit::
	setmoveeffect MOVE_EFFECT_BURN
	goto BattleScript_EffectHit

BattleScript_EffectMagnitude::
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
	magnitudedamagecalculation
	pause 0x20
	printstring STRINGID_MAGNITUDESTRENGTH
	waitmessage 0x40
	goto BattleScript_HitsAllWithUndergroundBonusLoop

BattleScript_EffectBatonPass::
	attackcanceler
	attackstring
	ppreduce
	jumpifcantswitch BS_ATTACKER | ATK4F_DONT_CHECK_STATUSES, BattleScript_ButItFailed
	attackanimation
	waitanimation
	openpartyscreen BS_ATTACKER, BattleScript_ButItFailed
	switchoutabilities BS_ATTACKER
	waitstate
	switchhandleorder BS_ATTACKER, 2
	returntoball BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	switchinanim BS_ATTACKER, 1
	waitstate
	switchineffects BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectMindBlown::
	attackcanceler
	attackstring
	ppreduce
	faintifabilitynotdamp
	dmg_1_2_attackerhp
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	waitstate
	jumpifbyte CMP_NO_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_MISSED, BattleScript_ExplosionDoAnimStartLoop
	call BattleScript_PreserveMissedBitDoMoveAnim
	goto BattleScript_ExplosionLoop

@adjust script so effect works with multitask
@jump to BattleScript_HitFromAtkString
@will need use setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
@but without seteffectchange directy after
@and setup like strength change where stat buff is at start of script
BattleScript_EffectRapidSpin::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	jumpifhalfword CMP_COMMON_BITS, gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_RAPIDSPIN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	setmoveeffectwithchance
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_EffectRapidSpinEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_EffectRapidSpinEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_EffectRapidSpinEnd::
	tryfaintmon BS_TARGET, 0, NULL
	moveendall
	end

BattleScript_EffectSonicscreech::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	setword gBattleMoveDamage, 20
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectMorningSun::
BattleScript_EffectShoreUp::
	attackcanceler
	attackstring
	ppreduce
	recoverbasedonsunlight BattleScript_AlreadyAtFullHp
	goto BattleScript_PresentHealTarget

BattleScript_EffectHiddenPower::
	attackcanceler
	hiddenpowercalc
	goto BattleScript_HitFromAccCheck

BattleScript_EffectRainDance::
	attackcanceler
	attackstring
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	setrain
BattleScript_MoveWeatherChange::
	attackanimation
	waitanimation
	printfromtable gMoveWeatherChangeStringIds
	waitmessage 0x40
	call BattleScript_HandleWeatherFormChanges
	goto BattleScript_MoveEnd

BattleScript_EffectSunnyDay::
	attackcanceler
	attackstring
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	setsunny
	goto BattleScript_MoveWeatherChange

BattleScript_ExtremelyHarshSunlightWasNotLessened:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_ExtremelyHarshSunlightWasNotLessenedEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_ExtremelyHarshSunlightWasNotLessenedRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_NoReliefFromHeavyRain:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_NoReliefFromHeavyRainEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_NoReliefFromHeavyRainRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_NORELIEFROMHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MysteriousAirCurrentBlowsOn:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_MysteriousAirCurrentBlowsOnEnd3:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_MysteriousAirCurrentBlowsOnRet:
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_MYSTERIOUSAIRCURRENTBLOWSON
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BlockedByPrimalWeatherEnd3::
	@call BattleScript_AbilityPopUp
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessenedEnd3
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRainEnd3
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOnEnd3
	end3

BattleScript_BlockedByPrimalWeatherRet::
	@call BattleScript_AbilityPopUp
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessenedRet
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRainRet
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOnRet
	return

BattleScript_EffectDefenseUpHit::
	setmoveeffect MOVE_EFFECT_DEF_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectAttackUpHit::
	setmoveeffect MOVE_EFFECT_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectSpecialAttackUpHit::
	setmoveeffect MOVE_EFFECT_SP_ATK_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectAttackerDefenseDownHit:
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectAllStatsUpHit::
	setmoveeffect MOVE_EFFECT_ALL_STATS_UP | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_EffectBellyDrum::
	attackcanceler
	attackstring
	ppreduce
	maxattackhalvehp BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNCUTHPMAXEDATTACK
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectPsychUp::
	attackcanceler
	attackstring
	ppreduce
	copyfoestats BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCOPIEDSTATCHANGES
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMirrorCoat::
	attackcanceler
	typecalc
	mirrorcoatdamagecalculator BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectSkullBash::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKULL_BASH
	call BattleScriptFirstChargingTurn
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_SkullBashEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_SkullBashEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_SkullBashEnd::
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectSkyAttack::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SKY_ATTACK
	call BattleScriptFirstChargingTurn
	setstatchanger STAT_EVASION, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_SkyAttackEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_SkyAttackEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_SkyAttackEnd::
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectTwister::
BattleScript_FlinchEffect::
	setmoveeffect MOVE_EFFECT_FLINCH
	goto BattleScript_EffectHit

BattleScript_EffectBulldoze:
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1
BattleScript_EffectEarthquake::
	attackcanceler
	attackstring
	ppreduce
	selectfirstvalidtarget
BattleScript_HitsAllWithUndergroundBonusLoop::
	movevaluescleanup
	@jumpifnostatus3 BS_TARGET, STATUS3_UNDERGROUND, BattleScript_HitsAllNoUndergroundBonus
	@orword gHitMarker, HITMARKER_IGNORE_UNDERGROUND
	@setbyte sDMG_MULTIPLIER, 2
	@goto BattleScript_DoHitAllWithUndergroundBonus
BattleScript_HitsAllNoUndergroundBonus::
	@bicword gHitMarker, HITMARKER_IGNORE_UNDERGROUND
	@setbyte sDMG_MULTIPLIER, 1
BattleScript_DoHitAllWithUndergroundBonus::
	@accuracycheck BattleScript_HitAllWithUndergroundBonusMissed, ACC_CURR_MOVE		@late gen suer hit
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	tryfaintmon BS_TARGET, 0, NULL
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_HitsAllWithUndergroundBonusLoop
	end

BattleScript_HitAllWithUndergroundBonusMissed::
	pause 0x20
	typecalc
	effectivenesssound
	resultmessage
	waitmessage 0x40
	moveendto MOVE_END_NEXT_TARGET
	jumpifnexttargetvalid BattleScript_HitsAllWithUndergroundBonusLoop
	end

BattleScript_EffectFutureSight::
	attackcanceler
	attackstring
	ppreduce
	trysetfutureattack BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gFutureMoveUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectGust::
	goto BattleScript_EffectHit

BattleScript_EffectFlinchMinimizeHit::
	goto BattleScript_FlinchEffect

BattleScript_EffectSolarbeam::
	attackthisturn BattleScript_SolarbeamOnFirstTurn @replacement for sun check, also setup for fluorescence
	jumpifabilitypresent ABILITY_CLOUD_NINE, BattleScript_SolarbeamDecideTurn
	jumpifabilitypresent ABILITY_AIR_LOCK, BattleScript_SolarbeamDecideTurn
BattleScript_SolarbeamDecideTurn::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_SOLAR_BEAM
	call BattleScriptFirstChargingTurn
	goto BattleScript_MoveEnd

BattleScript_SolarbeamOnFirstTurn::
	orword gHitMarker, HITMARKER_CHARGING
	setmoveeffect MOVE_EFFECT_CHARGING | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	ppreduce
	goto BattleScript_TwoTurnMovesSecondTurn

BattleScript_EffectThunder::
	setmoveeffect MOVE_EFFECT_PARALYSIS
	goto BattleScript_EffectHit

BattleScript_EffectTeleport::
	attackcanceler
	attackstring
	ppreduce
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_ButItFailed
	getifcantrunfrombattle BS_ATTACKER
	jumpifbyte CMP_EQUAL, gBattleCommunication, 1, BattleScript_ButItFailed
	jumpifbyte CMP_EQUAL, gBattleCommunication, 2, BattleScript_PrintAbilityMadeIneffective
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFLEDFROMBATTLE
	waitmessage 0x40
	setbyte gBattleOutcome, B_OUTCOME_PLAYER_TELEPORTED
	goto BattleScript_MoveEnd

BattleScript_EffectBeatUp::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause 0x20
	ppreduce
	setbyte gBattleCommunication, 0
BattleScript_BeatUpLoop::
	movevaluescleanup
	jumpifhasnohp BS_TARGET, BattleScript_BeatUpEnd @ for some reaosn hda to add this, move continued after battler hp was 0
	critcalc
	trydobeatup BattleScript_BeatUpEnd, BattleScript_ButItFailed	@need to do full damagecalc here
	printstring STRINGID_PKMNATTACK
BattleScript_BeatUpAttack::
	adjustnormaldamage
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, 0, NULL
	moveendto MOVE_END_NEXT_TARGET
	goto BattleScript_BeatUpLoop

BattleScript_BeatUpEnd::
	end

BattleScript_EffectTwoTurnsAttack::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_TwoTurnMovesSecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_TwoTurnMovesSecondTurn
	setbyte sTWOTURN_STRINGID, 0x0
BattleScript_EffectTwoTurnsAttackContinue:
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
	goto BattleScript_TwoTurnMovesSecondTurn



BattleScript_EffectGeomancy:
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_GeomancySecondTurn
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_GeomancySecondTurn
	setbyte sTWOTURN_STRINGID, B_MSG_TURN1_GEOMANCY
	call BattleScriptFirstChargingTurn
	jumpifnoholdeffect BS_ATTACKER, HOLD_EFFECT_POWER_HERB, BattleScript_MoveEnd
	call BattleScript_PowerHerbActivation
BattleScript_GeomancySecondTurn:
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	attackstring
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, MAX_STAT_STAGE, BattleScript_GeomancyDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPDEF, MAX_STAT_STAGE, BattleScript_GeomancyDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_CantRaiseMultipleStats
BattleScript_GeomancyDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF | BIT_SPEED, 0
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_GeomancyTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GeomancyTrySpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GeomancyTrySpDef::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_GeomancyTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GeomancyTrySpeed
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GeomancyTrySpeed::
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_GeomancyEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_GeomancyEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_GeomancyEnd::
	goto BattleScript_MoveEnd

BattleScript_PowerHerbActivation:
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_POWERHERB
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_EffectSemiInvulnerable::
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_SecondTurnSemiInvulnerable
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_NO_ATTACKSTRING, BattleScript_SecondTurnSemiInvulnerable
	jumpifmove MOVE_FLY, BattleScript_FlyFirstTurn
	jumpifmove MOVE_DIVE, BattleScript_DiveFirstTurn
	jumpifmove MOVE_BOUNCE, BattleScript_BounceFirstTurn
	@ MOVE_DIG
	setbyte sTWOTURN_STRINGID, 5
	goto BattleScript_FirstTurnSemiInvulnerable

BattleScript_BounceFirstTurn::
	setbyte sTWOTURN_STRINGID, 7
	goto BattleScript_FirstTurnSemiInvulnerable

BattleScript_DiveFirstTurn::
	setbyte sTWOTURN_STRINGID, 6
	goto BattleScript_FirstTurnSemiInvulnerable

BattleScript_FlyFirstTurn::
	setbyte sTWOTURN_STRINGID, 4
BattleScript_FirstTurnSemiInvulnerable::
	call BattleScriptFirstChargingTurn
	setsemiinvulnerablebit
	goto BattleScript_MoveEnd

BattleScript_EffectWithChance::
	setmoveeffectwithchance

BattleScript_SideStatusWoreOff::	@ dont know if that B_wait is gonna work
	printstring STRINGID_PKMNSXWOREOFF
	waitmessage 0x40
	end2

BattleScript_SideStatusWoreOffReturn::   @ replaced as needed with normal time 0x40
	printstring STRINGID_PKMNSXWOREOFF
	waitmessage 0x40
	return	

BattleScript_SecondTurnSemiInvulnerable::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	setbyte sB_ANIM_TURN, 1
	clearstatusfromeffect BS_ATTACKER
	orword gHitMarker, HITMARKER_NO_PPDEDUCT
	jumpifnotmove MOVE_BOUNCE, BattleScript_SemiInvulnerableTryHit
	setmoveeffect MOVE_EFFECT_PARALYSIS
BattleScript_SemiInvulnerableTryHit::
	accuracycheck BattleScript_SemiInvulnerableMiss, ACC_CURR_MOVE
	clearsemiinvulnerablebit
	goto BattleScript_HitFromAtkString

BattleScript_SemiInvulnerableMiss::
	clearsemiinvulnerablebit
	goto BattleScript_PrintMoveMissed

BattleScript_EffectDefenseCurl::
	attackcanceler
	attackstring
	ppreduce
	setdefensecurlbit
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_DefenseCurlDoStatUpAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_StatUpPrintString
	attackanimation
	waitanimation
BattleScript_DefenseCurlDoStatUpAnim::
	goto BattleScript_StatUpDoAnim

BattleScript_EffectSoftboiled::
	attackcanceler
	attackstring
	ppreduce
	tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_TARGET
BattleScript_PresentHealTarget::
	attackanimation
	waitanimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AlreadyAtFullHp::
	pause 0x20
	printstring STRINGID_PKMNHPFULL
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_ReturnAlreadyAtFullHp::
	pause 0x20
	printstring STRINGID_PKMNHPFULL
	waitmessage 0x40
	return

BattleScript_EffectFakeOut::
	attackcanceler
	jumpifnotfirstturn BattleScript_ButItFailedAtkStringPpReduce
	setmoveeffect MOVE_EFFECT_FLINCH | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_ButItFailedAtkStringPpReduce::
	attackstring
BattleScript_ButItFailedPpReduce::
	ppreduce
BattleScript_ButItFailed::
	pause 0x20
	orbyte gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_NotAffected::
	pause 0x20
	orbyte gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectUproar::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setmoveeffect MOVE_EFFECT_UPROAR | MOVE_EFFECT_AFFECTS_USER
	attackstring
	jumpifstatus2 BS_ATTACKER, STATUS2_MULTIPLETURNS, BattleScript_UproarHit
	ppreduce
BattleScript_UproarHit::
	nop
	goto BattleScript_HitFromCritCalc

BattleScript_EffectStockpile::
	attackcanceler
	attackstring
	ppreduce
	stockpile
	attackanimation
	waitanimation
	printfromtable gStockpileUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSpitUp::
	attackcanceler
	jumpifbyte CMP_EQUAL, gBattleCommunication + 6, 1, BattleScript_SpitUpNoDamage
	attackstring
	ppreduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	stockpiletobasedamage BattleScript_SpitUpFail
	typecalc
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_SpitUpFail::
	pause 0x20
	printstring STRINGID_FAILEDTOSPITUP
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SpitUpNoDamage::
	attackstring
	ppreduce
	pause 0x40
	stockpiletobasedamage BattleScript_SpitUpFail
	resultmessage
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSwallow::
	attackcanceler
	attackstring
	ppreduce
	stockpiletohpheal BattleScript_SwallowFail
	goto BattleScript_PresentHealTarget

BattleScript_SwallowFail::
	pause 0x20
	printfromtable gSwallowFailStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectHail::
	attackcanceler
	attackstring
	ppreduce
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_SUN_PRIMAL, BattleScript_ExtremelyHarshSunlightWasNotLessened
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_RAIN_PRIMAL, BattleScript_NoReliefFromHeavyRain
	jumpifhalfword CMP_COMMON_BITS, gBattleWeather, WEATHER_STRONG_WINDS, BattleScript_MysteriousAirCurrentBlowsOn
	sethail
	goto BattleScript_MoveWeatherChange

BattleScript_EffectTorment::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	settorment BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSUBJECTEDTOTORMENT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectFlatter::
	attackcanceler
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_MakeMoveMissed
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifconfusedandstatmaxed 4, BattleScript_ButItFailed
	attackanimation
	waitanimation
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_FlatterTryConfuse
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_FlatterTryConfuse
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_FlatterTryConfuse::
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_OwnTempoPrevents
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_AbilityPreventsMoodShift
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_AbilityPreventsMoodShift
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	setmoveeffect MOVE_EFFECT_CONFUSION
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectWillOWisp::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_BURN, BattleScript_AlreadyBurned
	jumpiftype BS_TARGET, TYPE_FIRE, BattleScript_NotAffected
	jumpifability BS_TARGET, ABILITY_WATER_VEIL, BattleScript_WaterVeilPrevents
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	typecalc
BattleScript_EndingBurnChecks:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation
	waitanimation
	setmoveeffect MOVE_EFFECT_BURN
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_EffectFlashFreeze::	@nearly done  just need to make animation for... for now using sheer cold i think
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifstatus BS_TARGET, STATUS1_FREEZE, BattleScript_AlreadyFrozen	@prevents refreezing given new freeze status but thats fine
	jumpiftype BS_TARGET, TYPE_ICE, BattleScript_NotAffected
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_LeafGuardProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	typecalc
BattleScript_EndingFreezeChecks:
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	attackanimation		@still need make animation
	waitanimation
	setmoveeffect MOVE_EFFECT_FREEZE
	seteffectprimary
	goto BattleScript_MoveEnd

BattleScript_WaterVeilPrevents::
	copybyte gEffectBattler, gBattlerTarget
	setbyte cMULTISTRING_CHOOSER, 0
	call BattleScript_BRNPrevention
	goto BattleScript_MoveEnd

BattleScript_AlreadyBurned::
	pause 0x20
	printstring STRINGID_PKMNALREADYHASBURN
	waitmessage 0x40
	goto BattleScript_MoveEnd
	
BattleScript_AlreadyFrozen::
	pause 0x20
	printstring STRINGID_PKMNALREADYFROZEN
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectMemento::
	attackcanceler
	jumpifbyte CMP_EQUAL, gBattleCommunication + 6, 1, BattleScript_MementoNoReduceStats
	attackstring
	ppreduce
	jumpifattackandspecialattackcannotfall BattleScript_ButItFailed
	setatkhptozero
	attackanimation
	waitanimation
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_MementoSubstituteInvulnerable
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_STAT_BY_TWO | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_ATK, 2, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_MementoSkipStatDown1
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 1, BattleScript_MementoSkipStatDown1
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_MementoSkipStatDown1::
	playstatchangeanimation BS_TARGET, BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_SPATK, 2, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_MementoSkipStatDown2
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 1, BattleScript_MementoSkipStatDown2
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_MementoSkipStatDown2::
	tryfaintmon BS_ATTACKER, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_MementoSubstituteInvulnerable::
	printstring STRINGID_BUTNOEFFECT
	waitmessage 0x40
	goto BattleScript_MementoSkipStatDown2

BattleScript_MementoNoReduceStats::
	attackstring
	ppreduce
	jumpifattackandspecialattackcannotfall .+4
	setatkhptozero
	pause 0x40
	effectivenesssound
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectFacade::
	jumpifstatus BS_ATTACKER, STATUS1_POISON | STATUS1_PARALYSIS | STATUS1_BURN | STATUS1_TOXIC_POISON, BattleScript_FacadeDoubleDmg
	goto BattleScript_EffectHit

BattleScript_FacadeDoubleDmg::
	manipulatedamage DOUBLE_DMG @replaced sDMG_MULTIPLIER
	goto BattleScript_EffectHit

BattleScript_EffectFocusPunch::
	attackcanceler
	jumpifnodamage BattleScript_HitFromAccCheck
	ppreduce
	printstring STRINGID_PKMNLOSTFOCUS
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSmellingsalt::
BattleScript_EffectWakeUpSlap:
BattleScript_EffectSparklingAria:
	jumpifsubstituteblocks BattleScript_EffectHit
	setmoveeffect MOVE_EFFECT_REMOVE_STATUS | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectFollowMe::
	attackcanceler
	attackstring
	ppreduce
	setforcedtarget
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCENTERATTENTION
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectNaturePower::
	attackcanceler
	attackstring
	pause 0x20
	callterrainattack
	printstring STRINGID_NATUREPOWERTURNEDINTO
	waitmessage 0x40
	return

BattleScript_EffectCharge::
	attackcanceler
	attackstring
	ppreduce
	setcharge
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHARGINGPOWER
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTaunt::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	settaunt BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNFELLFORTAUNT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectHelpingHand::
	attackcanceler
	attackstring
	ppreduce
	trysethelpinghand BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNREADYTOHELP
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectTrick::
	attackcanceler
	attackstring
	ppreduce
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	tryswapitems BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWITCHEDITEMS
	waitmessage 0x40
	printfromtable gItemSwapStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRolePlay::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	trycopyability BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCOPIEDFOE
	waitmessage 0x40
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectWish::
	attackcanceler
	attackstring
	ppreduce
	trywish 0, BattleScript_ButItFailed
	attackanimation
	waitanimation
	goto BattleScript_MoveEnd

BattleScript_EffectAssist::
	attackcanceler
	attackstring
	assistattackselect BattleScript_ButItFailedPpReduce
	attackanimation
	waitanimation
	setbyte sB_ANIM_TURN, 0
	setbyte sB_ANIM_TARGETS_HIT, 0
	jumptocalledmove 1
BattleScript_EffectIngrain::
	attackcanceler
	attackstring
	ppreduce
	trysetroots BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNPLANTEDROOTS
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSuperpower::	@needtest
	setmoveeffect MOVE_EFFECT_ATK_DEF_DOWN | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit	@REMOVED REcoil

BattleScript_EffectCloseCombat::	@removed sp def drop, was going to make recoil but decided against it
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectMagicCoat::
	attackcanceler
	setmagiccoat
	attackstring
	ppreduce
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSHROUDEDITSELF
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRecycle::
	attackcanceler
	attackstring
	ppreduce
	tryrecycleitem BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_XFOUNDONEY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRevenge::
	doubledamagedealtifdamaged
	goto BattleScript_EffectHit

BattleScript_EffectBrickBreak::
	call_if	EFFECT_BRICK_BREAK

@still working on this vsonic
BattleScript_BrickBreakWithScreens::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	removelightscreenreflect @check if I added my other effects to this already vsonic
	critcalc
	damagecalc
	adjustnormaldamage
	pause 0x01
	jumpifbyte CMP_EQUAL, sB_ANIM_TURN, 0, BattleScript_BrickBreakAnim
	bicbyte gMoveResultFlags, MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE
BattleScript_BrickBreakAnim::
	attackanimation
	waitanimation
	jumpifbyte CMP_LESS_THAN, sB_ANIM_TURN, 2, BattleScript_BrickBreakDoHit
	printstring STRINGID_THEWALLSHATTERED
	waitmessage 0x40
BattleScript_BrickBreakDoHit::
	typecalc2	@apparently still need as move would still work on type immune mon, but just to break the wall, need look into this script is confusing
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	setmoveeffectwithchance
	argumenttomoveeffect	@added for psychic fangs to add flinch effect, should do nothing for normal brickbreak
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_BrickBreakNoScreens::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	@removelightscreenreflect @check if I added my other effects to this already vsonic	 hadnt added new stuff, but just use scrancleaner stuff instead no longer need this
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	setmoveeffectwithchance
	argumenttomoveeffect	@added for psychic fangs to add flinch effect, should do nothing for normal brickbreak
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectYawn::
	attackcanceler
	attackstring
	ppreduce
	jumpifability BS_TARGET, ABILITY_VITAL_SPIRIT, BattleScript_PrintBankAbilityMadeIneffective
	jumpifability BS_TARGET, ABILITY_INSOMNIA, BattleScript_PrintBankAbilityMadeIneffective
	jumpifability BS_TARGET, ABILITY_COMATOSE, BattleScript_PrintBankAbilityMadeIneffective
	jumpifflowerveil BattleScript_FlowerVeilProtects
	jumpifleafguard BattleScript_LeafGuardProtects
	jumpifshieldsdown BS_TARGET, BattleScript_LeafGuardProtects
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_ButItFailed
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_SafeguardProtected
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	jumpifcantmakeasleep BattleScript_ButItFailed
	setyawn BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNWASMADEDROWSY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_PrintBankAbilityMadeIneffective::
	copybyte sBATTLER, sBATTLER_WITH_ABILITY
BattleScript_PrintAbilityMadeIneffective::
	pause 0x20
	printstring STRINGID_PKMNSXMADEITINEFFECTIVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectKnockOff::
	setmoveeffect MOVE_EFFECT_KNOCK_OFF
	goto BattleScript_EffectHit

BattleScript_EffectEndeavor::
	attackcanceler
	attackstring
	ppreduce
	setdamagetohealthdifference BattleScript_ButItFailed
	copyword gHpDealt, gBattleMoveDamage
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	typecalc
	jumpifmovehadnoeffect BattleScript_HitFromAtkAnimation
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	copyword gBattleMoveDamage, gHpDealt
	adjustsetdamage
	goto BattleScript_HitFromAtkAnimation

BattleScript_EffectEruption::
	scaledamagebyhealthratio
	goto BattleScript_EffectHit

BattleScript_EffectSkillSwap::
	attackcanceler
	attackstring
	ppreduce
	accuracycheck BattleScript_ButItFailed, NO_ACC_CALC_CHECK_LOCK_ON
	tryswapabilities BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSWAPPEDABILITIES
	waitmessage 0x40
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectImprison::
	attackcanceler
	attackstring
	ppreduce
	tryimprison BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSEALEDOPPONENTMOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectRefresh::
	attackcanceler
	attackstring
	ppreduce
	cureifburnedparalysedorpoisoned BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_EffectGrudge::
	attackcanceler
	attackstring
	ppreduce
	trysetgrudge BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNWANTSGRUDGE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectSnatch::
	attackcanceler
	trysetsnatch BattleScript_ButItFailedAtkStringPpReduce
	attackstring
	ppreduce
	attackanimation
	waitanimation
	pause 0x20
	printstring STRINGID_PKMNWAITSFORTARGET
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectLowKick::
	attackcanceler
	weightdamagecalculation
	jumpifability BS_ATTACKER, ABILITY_MULTI_TASK, BattleScript_MultiHitFromAtkString
	attackstring
	ppreduce
	@ weightdamagecalculation
	accuracycheck BattleScript_MoveMissedPause, ACC_CURR_MOVE
	goto BattleScript_HitFromCritCalc

@hope works based around intimidate
@ok got the effect to work but its causing a slight menu glitch for some reason
@tip from ghoulslash had to add empty string to free resources to do stat animation
BattleScript_EffectStrengthUpHit::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_HitFromAtkString
	setgraphicalstatchangevalues
	printstring STRINGID_EMPTYSTRING3
	waitmessage 0x1
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x30
	goto BattleScript_HitFromAtkString

BattleScript_EffectSecretPower::
	getsecretpowereffect
	goto BattleScript_EffectHit

BattleScript_EffectDoubleEdge::
	setmoveeffect MOVE_EFFECT_RECOIL_33 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectRecoil33WithStatus:
	setmoveeffect MOVE_EFFECT_RECOIL_33_STATUS | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectRecoil50:
	setmoveeffect MOVE_EFFECT_RECOIL_50 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectTeeterDance::
	attackcanceler
	attackstring
	ppreduce
	setbyte gBattlerTarget, 0
BattleScript_TeeterDanceLoop::
	movevaluescleanup
	setmoveeffect MOVE_EFFECT_CONFUSION
	jumpifbyteequal gBattlerAttacker, gBattlerTarget, BattleScript_TeeterDanceLoopIncrement
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_TeeterDanceOwnTempoPrevents
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_TeeterDanceSubstitutePrevents
	jumpifstatus2 BS_TARGET, STATUS2_CONFUSION, BattleScript_TeeterDanceAlreadyConfused
	accuracycheck BattleScript_TeeterDanceMissed, ACC_CURR_MOVE
	jumpifsideaffecting BS_TARGET, SIDE_STATUS_SAFEGUARD, BattleScript_TeeterDanceSafeguardProtected
	attackanimation
	waitanimation
	seteffectprimary
	resultmessage
	waitmessage 0x40
BattleScript_TeeterDanceLoopIncrement::
	moveendto MOVE_END_NEXT_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TeeterDanceLoop
	end

BattleScript_TeeterDanceOwnTempoPrevents::
	pause 0x20
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage 0x40
	goto BattleScript_TeeterDanceLoopIncrement

BattleScript_TeeterDanceSafeguardProtected::
	pause 0x20
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage 0x40
	goto BattleScript_TeeterDanceLoopIncrement

BattleScript_TeeterDanceSubstitutePrevents::
	pause 0x20
	printstring STRINGID_BUTITFAILED
	waitmessage 0x40
	goto BattleScript_TeeterDanceLoopIncrement

BattleScript_TeeterDanceAlreadyConfused::
	pause 0x20
	printstring STRINGID_PKMNALREADYCONFUSED
	waitmessage 0x40
	goto BattleScript_TeeterDanceLoopIncrement

BattleScript_TeeterDanceMissed::
	resultmessage
	waitmessage 0x40
	goto BattleScript_TeeterDanceLoopIncrement

BattleScript_EffectMudSport::
	attackcanceler
	attackstring
	ppreduce
	settypebasedhalvers BattleScript_ButItFailed
	attackanimation
	waitanimation
	printfromtable gSportsUsedStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_MudSportEnds::
	printstring STRINGID_MUDSPORTENDS
	waitmessage 0x40
	end2

BattleScript_WaterSportEnds::
	printstring STRINGID_WATERSPORTENDS
	waitmessage 0x40
	end2

BattleScript_EffectPoisonFang::
	setmoveeffect MOVE_EFFECT_TOXIC
	goto BattleScript_EffectHit

BattleScript_EffectWeatherBall::
	setweatherballtype
	goto BattleScript_EffectHit

BattleScript_EffectOverheat::
	setmoveeffect MOVE_EFFECT_RECOIL_33 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_EffectTickle::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_ATK, 0, BattleScript_TickleDoMoveAnim
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_DEF, 0, BattleScript_CantLowerMultipleStats
BattleScript_TickleDoMoveAnim::
	accuracycheck BattleScript_ButItFailed, ACC_CURR_MOVE
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_TARGET, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TickleTryLowerDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_TickleTryLowerDef
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_TickleTryLowerDef::
	playstatchangeanimation BS_TARGET, BIT_DEF, STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TickleEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_TickleEnd
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_TickleEnd::
	goto BattleScript_MoveEnd

BattleScript_CantLowerMultipleStats::
	pause 0x20
	orbyte gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_STATSWONTDECREASE2
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectCosmicPower::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, 12, BattleScript_CosmicPowerDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 12, BattleScript_CantRaiseMultipleStats
BattleScript_CosmicPowerDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CosmicPowerTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CosmicPowerTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CosmicPowerTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CosmicPowerEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CosmicPowerEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CosmicPowerEnd::
	goto BattleScript_MoveEnd	@ change cocoon to lower speed so its not so easy to just keep and use for beedrill/butterfree lower speed 2 stages

@ ended up making new effect to do what I want mostly copied from cosmic power, dont know if need a speed stat check
BattleScript_EffectCocoon::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, 12, BattleScript_CocoonDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 12, BattleScript_CantRaiseMultipleStats
BattleScript_CocoonDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, 0
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CocoonTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CocoonTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CocoonTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CocoonTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CocoonTrySpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CocoonTrySpeed::
	setstatchanger STAT_SPEED, 1, TRUE		@used on bug mid evos really slow ealready so doesnt effect them, unsure if change to lower 1, yeah changed to 1.
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CocoonEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CocoonEnd
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_CocoonEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectSkyUppercut::
	goto BattleScript_EffectHit

BattleScript_EffectBulkUp::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 12, BattleScript_BulkUpDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_DEF, 12, BattleScript_CantRaiseMultipleStats
BattleScript_BulkUpDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_BulkUpTryDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_BulkUpTryDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_BulkUpTryDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_BulkUpEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_BulkUpEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_BulkUpEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectCalmMind::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, 12, BattleScript_CalmMindDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 12, BattleScript_CantRaiseMultipleStats
BattleScript_CalmMindDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CalmMindTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CalmMindTrySpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CalmMindTrySpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_CalmMindEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_CalmMindEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_CalmMindEnd::
	goto BattleScript_MoveEnd

BattleScript_CantRaiseMultipleStats::
	pause 0x20
	orbyte gMoveResultFlags, MOVE_RESULT_FAILED
	printstring STRINGID_STATSWONTINCREASE2
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_EffectDragonDance::
	attackcanceler
	attackstring
	ppreduce
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 12, BattleScript_DragonDanceDoMoveAnim
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, 12, BattleScript_CantRaiseMultipleStats
BattleScript_DragonDanceDoMoveAnim::
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_SPEED, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_DragonDanceTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_DragonDanceTrySpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_DragonDanceTrySpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_DragonDanceEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_DragonDanceEnd
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_DragonDanceEnd::
	goto BattleScript_MoveEnd

BattleScript_EffectCamouflage::
	attackcanceler
	attackstring
	ppreduce
	settypetoterrain BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_FaintAttacker::
	tryillusionoff BS_ATTACKER
	playfaintcry BS_ATTACKER
	pause 0x40
	dofaintanimation BS_ATTACKER
	cleareffectsonfaint BS_ATTACKER
	printstring STRINGID_ATTACKERFAINTED
	printstring STRINGID_EMPTYSTRING3
	tryactivatesoulheart
	tryactivatereceiver BS_ATTACKER
	return

BattleScript_FaintTarget::
	tryillusionoff BS_TARGET		@same as issue as before this script naviagting wrong broke rest of script
	playfaintcry BS_TARGET
	pause 0x40
	dofaintanimation BS_TARGET
	cleareffectsonfaint BS_TARGET
	printstring STRINGID_TARGETFAINTED
	printstring STRINGID_EMPTYSTRING3
	tryactivatefellstinger BS_ATTACKER
	tryactivatesoulheart
	tryactivatereceiver BS_TARGET
	tryactivatemoxie BS_ATTACKER
	tryactivatebeastboost BS_ATTACKER
	return

BattleScript_GiveExp::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
	end2

BattleScript_BallFetch::
	printstring STRINGID_FETCHEDPOKEBALL
	waitmessage 0x40
	end3

BattleScript_MagicCoatBouncePrankster::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	printfromtable gMagicCoatBounceStringIds
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	goto BattleScript_MoveEnd

BattleScript_HandleFaintedMon::
	confirmlosingteam BattleScript_LinkBattleHandleFaint
	jumpifbyte CMP_NOT_EQUAL, gBattleOutcome, 0, BattleScript_FaintedMonEnd
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_FaintedMonTryChooseAnother
	jumpifword CMP_NO_COMMON_BITS, gHitMarker, HITMARKER_PLAYER_FAINTED, BattleScript_FaintedMonTryChooseAnother
	printstring STRINGID_USENEXTPKMN
	setbyte gBattleCommunication, 0
	yesnobox
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, 0, BattleScript_FaintedMonTryChooseAnother
	@ 0 in above statement means jump if player selects yes
	jumpifplayerran BattleScript_FaintedMonEnd
	printstring STRINGID_CANTESCAPE2
BattleScript_FaintedMonTryChooseAnother::
	openpartyscreen BS_FAINTED, BattleScript_FaintedMonEnd
	switchhandleorder BS_FAINTED, 2
	jumpifnotbattletype BATTLE_TYPE_TRAINER, BattleScript_FaintedMonChooseAnother
	jumpifbattletype BATTLE_TYPE_LINK, BattleScript_FaintedMonChooseAnother
	jumpifbattletype BATTLE_TYPE_BATTLE_TOWER, BattleScript_FaintedMonChooseAnother
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_FaintedMonChooseAnother
	@ check double battle in case this doesnt let you pick your pokemon and instead
	@ sends out your next ordered mon
	jumpifword CMP_COMMON_BITS, gHitMarker, HITMARKER_PLAYER_FAINTED, BattleScript_FaintedMonChooseAnother
	jumpifbyte CMP_EQUAL, sBATTLE_STYLE, 1, BattleScript_FaintedMonChooseAnother @believe checking if set mode not switch
	jumpifcantswitch BS_PLAYER1, BattleScript_FaintedMonChooseAnother
	printstring STRINGID_ENEMYABOUTTOSWITCHPKMN
	setbyte gBattleCommunication, 0
	yesnobox
	jumpifbyte CMP_EQUAL, gBattleCommunication + 1, 1, BattleScript_FaintedMonChooseAnother
	@ 1 above means jump if player selects no on switching if they switch pokemon
	setatktoplayer0
	openpartyscreen BS_ATTACKER | OPEN_PARTY_ALLOW_CANCEL, BattleScript_FaintedMonChooseAnother
	switchhandleorder BS_ATTACKER, 2
	jumpifbyte CMP_EQUAL, gBattleCommunication, 6, BattleScript_FaintedMonChooseAnother
	atknameinbuff1
	resetintimidatetracebits BS_ATTACKER  @check what this means think it allows intimidate to cast again if sent out
	hpthresholds2 BS_ATTACKER
	printstring STRINGID_RETURNMON
	switchoutabilities BS_ATTACKER
	waitstate
	returnatktoball
	waitstate
	drawpartystatussummary BS_ATTACKER
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_ATTACKER
	switchinanim BS_ATTACKER, 0
	waitstate
	switchineffects BS_ATTACKER
	resetsentmonsvalue
BattleScript_FaintedMonChooseAnother::
	drawpartystatussummary BS_FAINTED
	getswitchedmondata BS_FAINTED
	switchindataupdate BS_FAINTED
	hpthresholds BS_FAINTED
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_FAINTED
	switchinanim BS_FAINTED, 0
	waitstate
	resetplayerfainted BS_ATTACKER
	switchineffects BS_FAINTED
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_FaintedMonEnd
	cancelallactions
BattleScript_FaintedMonEnd::
	end2

BattleScript_LinkBattleHandleFaint::
	openpartyscreen BS_FAINTED_LINK_MULTIPLE_1, .+4
	switchhandleorder BS_FAINTED, 0
	openpartyscreen BS_FAINTED_LINK_MULTIPLE_2, BattleScript_LinkBattleFaintedMonEnd
	switchhandleorder BS_FAINTED, 0
BattleScript_LinkBattleFaintedMonLoop::
	switchhandleorder BS_FAINTED, 2
	drawpartystatussummary BS_FAINTED
	getswitchedmondata BS_FAINTED
	switchindataupdate BS_FAINTED
	hpthresholds BS_FAINTED
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_FAINTED
	switchinanim BS_FAINTED, 0
	waitstate
	switchineffects 5
	jumpifbytenotequal gBattlerFainted, gBattlersCount, BattleScript_LinkBattleFaintedMonLoop
BattleScript_LinkBattleFaintedMonEnd::
	end2

BattleScript_LocalTrainerBattleWon::
	printstring STRINGID_PLAYERDEFEATEDTRAINER1
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1LOSETEXT
	getmoneyreward .+4
	printstring STRINGID_PLAYERGOTMONEY
	waitmessage 0x40
BattleScript_PayDayMoneyAndPickUpItems::
	givepaydaymoney
	@pickup
	end2

BattleScript_LocalBattleLost::
	jumpifbattletype BATTLE_TYPE_TRAINER_TOWER, BattleScript_BattleTowerLost
	jumpifbattletype BATTLE_TYPE_EREADER_TRAINER, BattleScript_EReaderOrSecretBaseTrainerEnd
	jumpifhalfword CMP_EQUAL, gTrainerBattleOpponent_A, TRAINER_SECRET_BASE, BattleScript_EReaderOrSecretBaseTrainerEnd
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_RivalBattleLost
BattleScript_LocalBattleLostPrintWhiteOut::
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_LocalBattleLostEnd
	printstring STRINGID_PLAYERWHITEOUT
	waitmessage 0x40
	getmoneyreward BattleScript_LocalBattleLostPrintTrainersWinText
	printstring STRINGID_PLAYERWHITEOUT2
	waitmessage 0x40
	goto BattleScript_EReaderOrSecretBaseTrainerEnd

BattleScript_LocalBattleLostEnd::
	printstring STRINGID_PLAYERLOSTAGAINSTENEMYTRAINER
	waitmessage 0x40
	getmoneyreward BattleScript_LocalBattleLostPrintTrainersWinText
	printstring STRINGID_PLAYERPAIDPRIZEMONEY
	waitmessage 0x40
BattleScript_EReaderOrSecretBaseTrainerEnd::
	end2

BattleScript_LocalBattleLostPrintTrainersWinText::
	printstring STRINGID_PLAYERWHITEDOUT
	waitmessage 0x40
	end2

BattleScript_RivalBattleLost::
	jumpifhasnohp BS_ATTACKER, BattleScript_RivalBattleLostSkipMonRecall
	printstring STRINGID_TRAINER1MON1COMEBACK
	waitmessage 0x40
	returnatktoball
	waitstate
BattleScript_RivalBattleLostSkipMonRecall::
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1WINTEXT
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_LocalBattleLostPrintWhiteOut
	end2

BattleScript_BattleTowerLost::
	various8 BS_ATTACKER
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_BattleTowerLostLostSkipMonRecall
	printfromtable gDoubleBattleRecallStrings
	waitmessage 0x40
	returnopponentmon1toball BS_ATTACKER
	waitstate
	returnopponentmon2toball BS_ATTACKER
	waitstate
BattleScript_BattleTowerLostLostSkipMonRecall::
	trainerslidein BS_ATTACKER
	waitstate
	printstring STRINGID_TRAINER1WINTEXT
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_BattleTowerLostLostSkipDouble
	printstring STRINGID_TRAINER2NAME
BattleScript_BattleTowerLostLostSkipDouble::
	end2

BattleScript_LinkBattleWonOrLost::
	printstring STRINGID_BATTLEEND
	waitmessage 0x40
	atk57
	waitmessage 0x40
	end2

BattleScript_BattleTowerTrainerBattleWon::
	printstring STRINGID_PLAYERDEFEATEDTRAINER1
	trainerslidein BS_ATTACKER
	waitstate
	jumpifnotbattletype BATTLE_TYPE_TRAINER_TOWER, BattleScript_BattleTowerEtcTrainerBattleWonSkipText
	printstring STRINGID_TRAINER1LOSETEXT
	jumpifnotbattletype BATTLE_TYPE_DOUBLE, BattleScript_BattleTowerEtcTrainerBattleWonSkipText
	printstring STRINGID_TRAINER2CLASS
BattleScript_BattleTowerEtcTrainerBattleWonSkipText::
	@pickup
	end2

BattleScript_SmokeBallEscape::
	playanimation BS_ATTACKER, B_ANIM_SMOKEBALL_ESCAPE, NULL
	printstring STRINGID_PKMNFLEDUSINGITS
	waitmessage 0x40
	end2

BattleScript_RanAwayUsingMonAbility::
	printstring STRINGID_PKMNFLEDUSING
	waitmessage 0x40
	end2

BattleScript_GotAwaySafely::
	printstring STRINGID_GOTAWAYSAFELY
	waitmessage 0x40
	end2

BattleScript_WildMonFled::
	printstring STRINGID_WILDPKMNFLED
	waitmessage 0x40
	end2

BattleScript_PrintCantRunFromTrainer::
	jumpifbattletype BATTLE_TYPE_FIRST_BATTLE, BattleScript_LeftoverBirchString
	printstring STRINGID_NORUNNINGFROMTRAINERS
	end2

BattleScript_LeftoverBirchString::
	printstring STRINGID_DONTLEAVEBIRCH
	end2

BattleScript_PrintFailedToRunString::
	printfromtable gNoEscapeStringIds
	waitmessage 0x40
	end2

BattleScript_PrintCantEscapeFromBattle::
	printselectionstringfromtable gNoEscapeStringIds
	endselectionscript

BattleScript_PrintFullBox::
	printselectionstring STRINGID_BOXISFULL
	endselectionscript

BattleScript_ActionSwitch::
	hpthresholds2 BS_ATTACKER
	printstring STRINGID_RETURNMON
	@can put runaway avoiding pursuit here just jump to BattleScript_SkipPursuit vsonic
	jumpifability BS_ATTACKER, ABILITY_RUN_AWAY, BattleScript_SkipPursuit
	jumpifability BS_ATTACKER, ABILITY_AVIATOR, BattleScript_SkipPursuit
	manipulatedamage DOUBLE_DMG @for pursuit hopefully works? 
	@setbyte sDMG_MULTIPLIER, 2
	jumpifbattletype BATTLE_TYPE_DOUBLE, BattleScript_PursuitSwitchCheckTwice
	setmultihit 1
	goto BattleScript_PursuitSwitchLoop

BattleScript_PursuitSwitchCheckTwice::
	setmultihit 2
BattleScript_PursuitSwitchLoop::
	jumpifnopursuitswitchdmg BattleScript_DoSwitchOut
	swapattackerwithtarget
	trysetdestinybondtohappen
	call BattleScript_PursuitDmgOnSwitchOut
	swapattackerwithtarget
BattleScript_DoSwitchOut::
	decrementmultihit BattleScript_PursuitSwitchLoop
BattleScript_SkipPursuit::
	switchoutabilities BS_ATTACKER  @abilities that activate when switching out
	waitstate
	returnatktoball
	waitstate
	drawpartystatussummary BS_ATTACKER
	switchhandleorder BS_ATTACKER, 1
	getswitchedmondata BS_ATTACKER
	switchindataupdate BS_ATTACKER
	hpthresholds BS_ATTACKER
	printstring STRINGID_SWITCHINMON
	hidepartystatussummary BS_ATTACKER
	switchinanim BS_ATTACKER, 0
	waitstate
	jumpifcantreverttoprimal BattleScript_DoSwitchOut2
	call BattleScript_PrimalReversionRet
BattleScript_DoSwitchOut2:
	switchineffects BS_ATTACKER @this should be where switch in works,
	moveendcase MOVE_END_STATUS_IMMUNITY_ABILITIES
	moveendcase MOVE_END_MIRROR_MOVE
	end2

BattleScript_PursuitDmgOnSwitchOut::
	pause 0x20
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage 0x40
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, 0, NULL
	moveendfromto MOVE_END_MOVE_END_ABILITIES, MOVE_END_CHOICE_MOVE
	getbattlerfainted BS_TARGET
	jumpifbyte CMP_EQUAL, gBattleCommunication, 0, BattleScript_PursuitSwitchRivalSkip
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
BattleScript_PursuitSwitchRivalSkip::
	return

BattleScript_Pausex20::
	pause 0x20
	return

BattleScript_LevelUp::
	fanfare MUS_LEVEL_UP
	printstring STRINGID_PKMNGREWTOLV
	setbyte sLVLBOX_STATE, 0
	drawlvlupbox
	handlelearnnewmove BattleScript_LearnedNewMove, BattleScript_LearnMoveReturn, 1 @believe 2 pointers and a bool
	goto BattleScript_AskToLearnMove

BattleScript_LearnMoveLoop::
	handlelearnnewmove BattleScript_LearnedNewMove, BattleScript_LearnMoveReturn, 0
BattleScript_AskToLearnMove::
	buffermovetolearn
	printstring STRINGID_TRYTOLEARNMOVE1
	printstring STRINGID_TRYTOLEARNMOVE2
BattleScript_AskToLearnMoveFast::
	buffermovetolearn
	printstring STRINGID_TRYTOLEARNMOVE3
	waitstate
	setbyte sLEARNMOVE_STATE, 0 @needed to setup for yesnobox commands for learnn/stoplearn move
	yesnoboxlearnmove BattleScript_ForgotAndLearnedNewMove @case 0-1 yes no logic jump is case 3,
	buffermovetolearn
	printstring STRINGID_STOPLEARNINGMOVE
	waitstate
	setbyte sLEARNMOVE_STATE, 0
	@yesnoboxstoplearningmove BattleScript_AskToLearnMove
	yesnoboxstoplearningmove BattleScript_AskToLearnMoveFast
	printstring STRINGID_DIDNOTLEARNMOVE
	goto BattleScript_LearnMoveLoop	@check if can learn another move

BattleScript_ForgotAndLearnedNewMove::
	@printstring STRINGID_CONFIRMFORGETMOVE
	@waitstate
	@setbyte sLEARNMOVE_STATE, 0
	@yesnoboxstoplearningmove BattleScript_AskToLearnMoveFast
	printstring STRINGID_123POOF
	printstring STRINGID_PKMNFORGOTMOVE
	printstring STRINGID_ANDELLIPSIS
BattleScript_LearnedNewMove::
	buffermovetolearn
	fanfare MUS_LEVEL_UP
	printstring STRINGID_PKMNLEARNEDMOVE
	waitmessage 0x40
	updatechoicemoveonlvlup BS_ATTACKER
	goto BattleScript_LearnMoveLoop

BattleScript_LearnMoveReturn::
	return

BattleScript_RainContinuesOrEnds::
	printfromtable gRainContinuesStringIds
	waitmessage 0x40
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_RainContinuesOrEndsEnd
	playanimation BS_ATTACKER, B_ANIM_RAIN_CONTINUES, NULL
BattleScript_RainContinuesOrEndsEnd::
	end2

BattleScript_DamagingWeatherContinues::
	printfromtable gSandstormHailContinuesStringIds
	waitmessage 0x40
	playanimation2 BS_ATTACKER, sB_ANIM_ARG1, NULL
	setbyte gBattleCommunication, 0
BattleScript_DamagingWeatherLoop::
	copyarraywithindex gBattlerAttacker, gBattlerByTurnOrder, gBattleCommunication, 1
	weatherdamage
	jumpifword CMP_EQUAL, gBattleMoveDamage, NULL, BattleScript_DamagingWeatherContinuesEnd
	printfromtable gSandstormHailDmgStringIds
	waitmessage 0x40
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_GRUDGE
	effectivenesssound
	hitanimation BS_ATTACKER
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	confirmlosingteam .+4
BattleScript_DamagingWeatherContinuesEnd::
	jumpifbyte CMP_NOT_EQUAL, gBattleOutcome, 0, BattleScript_WeatherDamageEndedBattle
	addbyte gBattleCommunication, 1
	jumpifbytenotequal gBattleCommunication, gBattlersCount, BattleScript_DamagingWeatherLoop
BattleScript_WeatherDamageEndedBattle::
	bicword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_GRUDGE
	end2

BattleScript_SandStormHailEnds::
	printfromtable gSandstormHailEndStringIds
	waitmessage 0x40
	end2

BattleScript_SunlightContinues::
	printstring STRINGID_SUNLIGHTSTRONG
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_SUN_CONTINUES, NULL
	end2

BattleScript_SunlightFaded::
	printstring STRINGID_SUNLIGHTFADED
	waitmessage 0x40
	end2

BattleScript_OverworldWeatherStarts::
	printfromtable gWeatherContinuesStringIds
	waitmessage 0x40
	playanimation2 BS_ATTACKER, sB_ANIM_ARG1, NULL
	end3

BattleScript_OverworldTerrain::
	printfromtable gTerrainStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	end3


BattleScript_SafeguardProtected::
	pause 0x20
	printstring STRINGID_PKMNUSEDSAFEGUARD
	waitmessage 0x40
	end2

BattleScript_SafeguardEnds::
	pause 0x20
	printstring STRINGID_PKMNSAFEGUARDEXPIRED
	waitmessage 0x40
	end2

BattleScript_LeechSeedTurnDrain::
	playanimation BS_ATTACKER, B_ANIM_LEECH_SEED_DRAIN, sB_ANIM_ARG1
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	copyword gBattleMoveDamage, gHpDealt
	setbyte cMULTISTRING_CHOOSER, 3
	jumpifhealblock BS_TARGET, BattleScript_LeechSeedHealBlock
	manipulatedamage DMG_BIG_ROOT
	jumpifability BS_ATTACKER, ABILITY_LIQUID_OOZE, BattleScript_LeechSeedTurnPrintLiquidOoze
	goto BattleScript_LeechSeedTurnPrintAndUpdateHp
BattleScript_LeechSeedTurnPrintLiquidOoze::
	manipulatedamage NEGATIVE_DMG
	copybyte gBattlerAbility, gBattlerAttacker
	setbyte cMULTISTRING_CHOOSER, 4	@don'tknow what this does so hope nota problem
BattleScript_LeechSeedTurnPrintAndUpdateHp::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printfromtable gLeechSeedStringIds
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, FALSE, NULL
	tryfaintmon BS_TARGET, FALSE, NULL
	end2

BattleScript_LeechSeedHealBlock::
	setword gBattleMoveDamage, 0
	goto BattleScript_LeechSeedTurnPrintAndUpdateHp

BattleScript_BideStoringEnergy::
	printstring STRINGID_PKMNSTORINGENERGY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_BideAttack::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	clearstatusfromeffect BS_ATTACKER
	printstring STRINGID_PKMNUNLEASHEDENERGY
	waitmessage 0x40
	accuracycheck BattleScript_MoveMissed, ACC_CURR_MOVE
	typecalc
	bicbyte gMoveResultFlags, MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_NOT_VERY_EFFECTIVE
	copyword gBattleMoveDamage, sBIDE_DMG
	adjustsetdamage
	setbyte sB_ANIM_TURN, 1
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_BideNoEnergyToAttack::
	attackcanceler
	setmoveeffect MOVE_EFFECT_CHARGING
	clearstatusfromeffect BS_ATTACKER
	printstring STRINGID_PKMNUNLEASHEDENERGY
	waitmessage 0x40
	goto BattleScript_ButItFailed

BattleScript_SuccessForceOut::
	attackanimation
	waitanimation
	switchoutabilities BS_TARGET
	returntoball BS_TARGET
	waitstate
	jumpifbattletype BATTLE_TYPE_TRAINER, BattleScript_TrainerBattleForceOut
	setbyte gBattleOutcome, B_OUTCOME_PLAYER_TELEPORTED
	finishaction
BattleScript_TrainerBattleForceOut::
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	switchinanim BS_TARGET, 0
	waitstate
	printstring STRINGID_PKMNWASDRAGGEDOUT
	switchineffects BS_TARGET
	goto BattleScript_MoveEnd

BattleScript_WeaknessPolicy::
	copybyte sBATTLER, gBattlerTarget
	jumpifstat BS_TARGET, CMP_LESS_THAN, STAT_ATK, MAX_STAT_STAGE, BattleScript_WeaknessPolicyAtk
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPATK, MAX_STAT_STAGE, BattleScript_WeaknessPolicyEnd
BattleScript_WeaknessPolicyAtk:
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, STAT_CHANGE_STAT_BY_TWO
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_WeaknessPolicySpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WeaknessPolicySpAtk
	printstring STRINGID_USINGXTHEYOFZN
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeaknessPolicySpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_WeaknessPolicyRemoveItem
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_WeaknessPolicyRemoveItem
	printstring STRINGID_USINGXTHEYOFZN
	waitmessage B_WAIT_TIME_LONG
BattleScript_WeaknessPolicyRemoveItem:
	removeitem BS_TARGET
BattleScript_WeaknessPolicyEnd:
	return

BattleScript_TargetItemStatRaise::
	copybyte sBATTLER, gBattlerTarget
	statbuffchange 0, BattleScript_TargetItemStatRaiseRemoveItemRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_TargetItemStatRaiseRemoveItemRet
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_USINGXTHEYOFZN
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
BattleScript_TargetItemStatRaiseRemoveItemRet:
	return

BattleScript_AttackerItemStatRaise::
	copybyte sBATTLER, gBattlerAttacker
	statbuffchange MOVE_EFFECT_AFFECTS_USER, BattleScript_AttackerItemStatRaiseRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_AttackerItemStatRaiseRet
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_USINGXTHEYOFZN
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
BattleScript_AttackerItemStatRaiseRet:
	return

BattleScript_MistProtected::
	pause 0x20
	printstring STRINGID_PKMNPROTECTEDBYMIST
	waitmessage 0x40
	return

BattleScript_RageIsBuilding::
	printstring STRINGID_PKMNRAGEBUILDING
	waitmessage 0x40
	return

BattleScript_MoveUsedIsDisabled::
	printstring STRINGID_PKMNMOVEISDISABLED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SelectingDisabledMove::
	printselectionstring STRINGID_PKMNMOVEISDISABLED
	endselectionscript

BattleScript_DisabledNoMore::
	printstring STRINGID_PKMNMOVEDISABLEDNOMORE
	waitmessage 0x40
	end2

BattleScript_EncoredNoMore::
	printstring STRINGID_PKMNENCOREENDED
	waitmessage 0x40
	end2

BattleScript_DestinyBondTakesLife::
	printstring STRINGID_PKMNTOOKFOE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	return

BattleScript_SpikesOnAttacker::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	call BattleScript_PrintHurtBySpikes
	tryfaintmon BS_ATTACKER, 0, NULL
	tryfaintmon BS_ATTACKER, 1, BattleScript_SpikesOnAttackerFainted
	return

BattleScript_SpikesOnAttackerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_ATTACKER
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_SpikesOnTarget::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	call BattleScript_PrintHurtBySpikes
	tryfaintmon BS_TARGET, 0, NULL
	tryfaintmon BS_TARGET, 1, BattleScript_SpikesOnTargetFainted
	return

BattleScript_SpikesOnTargetFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_SpikesOnFaintedBattler::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_FAINTED
	datahpupdate BS_FAINTED
	call BattleScript_PrintHurtBySpikes
	tryfaintmon BS_FAINTED, 0, NULL
	tryfaintmon BS_FAINTED, 1, BattleScript_SpikesOnFaintedBattlerFainted
	return

BattleScript_SpikesOnFaintedBattlerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_FAINTED
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_PrintHurtBySpikes::
	printstring STRINGID_PKMNHURTBYSPIKES
	waitmessage 0x40
	return

BattleScript_DmgHazardsOnAttacker::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_ATTACKER 0, NULL
	tryfaintmon_spikes BS_ATTACKER, BattleScript_DmgHazardsOnAttackerFainted
	return

BattleScript_DmgHazardsOnAttackerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_ATTACKER
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_DmgHazardsOnTarget::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_TARGET 0, NULL
	tryfaintmon_spikes BS_TARGET, BattleScript_DmgHazardsOnTargetFainted
	return

BattleScript_DmgHazardsOnTargetFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_TARGET
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_DmgHazardsOnFaintedBattler::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_FAINTED
	datahpupdate BS_FAINTED
	call BattleScript_PrintHurtByDmgHazards
	tryfaintmon BS_FAINTED 0, NULL
	tryfaintmon_spikes BS_FAINTED, BattleScript_DmgHazardsOnFaintedBattlerFainted
	return

BattleScript_DmgHazardsOnFaintedBattlerFainted::
	setbyte sGIVEEXP_STATE, 0
	getexp BS_FAINTED
	moveendall
	goto BattleScript_HandleFaintedMon

BattleScript_PrintHurtByDmgHazards::
	printfromtable gDmgHazardsStringIds
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_PerishSongTakesLife::
	printstring STRINGID_PKMNPERISHCOUNTFELL
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	end2

BattleScript_PerishSongCountGoesDown::
	printstring STRINGID_PKMNPERISHCOUNTFELL
	waitmessage 0x40
	end2

BattleScript_AllStatsUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 12, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, 12, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPEED, 12, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, 12, BattleScript_AllStatsUpAtk
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 12, BattleScript_AllStatsUpRet
BattleScript_AllStatsUpAtk::
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPEED | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpDef::
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpSpeed
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpSpeed::
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpSpAtk
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpSpAtk::
	setstatchanger STAT_SPATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpSpDef
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpSpDef::
	setstatchanger STAT_SPDEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpRet
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpRet::
	return

	@believe cpm equal tell it to not raise stats if spdef is maxed since its raising everything
BattleScript_EffectSketchStatUp::
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_ATK, 12, BattleScript_AllStatsUpAtk2
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_DEF, 12, BattleScript_AllStatsUpAtk2
	jumpifstat BS_ATTACKER, CMP_LESS_THAN, STAT_SPATK, 12, BattleScript_AllStatsUpAtk2
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPDEF, 12, BattleScript_AllStatsUpRet2
BattleScript_AllStatsUpAtk2::
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF | BIT_SPATK | BIT_SPDEF, 0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpDef2
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpDef2::
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpSpAtk2
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpSpAtk2::
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpSpDef2
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpSpDef2::
	setstatchanger STAT_SPDEF, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, BattleScript_AllStatsUpRet2
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_AllStatsUpRet2::
	return

BattleScript_RapidSpinAway::
	rapidspinfree
	return

BattleScript_WrapFree::
	printstring STRINGID_PKMNGOTFREE
	waitmessage 0x40
	copybyte gBattlerTarget, sBATTLER
	return

BattleScript_LeechSeedFree::
	printstring STRINGID_PKMNSHEDLEECHSEED
	waitmessage 0x40
	return

BattleScript_SpikesFree::
	printstring STRINGID_PKMNBLEWAWAYSPIKES
	waitmessage 0x40
	return

BattleScript_ToxicSpikesFree::
	printstring STRINGID_PKMNBLEWAWAYTOXICSPIKES
	waitmessage 0x40
	return

BattleScript_StickyWebFree::
	printstring STRINGID_PKMNBLEWAWAYSTICKYWEB
	waitmessage 0x40
	return

BattleScript_StealthRockFree::
	printstring STRINGID_PKMNBLEWAWAYSTEALTHROCK
	waitmessage 0x40
	return

BattleScript_StealthRockAbsorb::
	printstring STRINGID_STEALTHROCKABROSBED
	waitmessage 0x40
	return

BattleScript_SwitchInAbilityMsg::
	@@ call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage 0x40
	end3

BattleScript_SwitchInAbilityMsgRet::
	@@ call BattleScript_AbilityPopUp
	printfromtable gSwitchInAbilityStringIds
	waitmessage 0x40
	return

@just relized set byte is wrong
@what I need is to check if byte is that value
@since crit are handled differently here
BattleScript_MegaEvolution::
	printstring STRINGID_MEGAEVOREACTING
	waitmessage 0x40
	@setbyte gIsCriticalHit, 0
	@setbyte gCritMultiplier, 1
	handlemegaevo BS_ATTACKER, 0
	handlemegaevo BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_MEGA_EVOLUTION, NULL
	waitanimation
	handlemegaevo BS_ATTACKER, 2
	printstring STRINGID_MEGAEVOEVOLVED
	waitmessage 0x40
	switchinabilities BS_ATTACKER
	end2

@changed to 2 hopefully means when crits,
@sometimes value is greater than 2 so hopefully no problem
BattleScript_WishMegaEvolution::
	printstring STRINGID_FERVENTWISHREACHED
	waitmessage 0x40
	@setbyte gIsCriticalHit, 1
	@setbyte gCritMultiplier, 2
	handlemegaevo BS_ATTACKER, 0
	handlemegaevo BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_MEGA_EVOLUTION, NULL
	waitanimation
	handlemegaevo BS_ATTACKER, 2
	printstring STRINGID_MEGAEVOEVOLVED
	waitmessage 0x40
	switchinabilities BS_ATTACKER
	end2

BattleScript_PrimalReversion::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	@setbyte gIsCriticalHit, 0
	handleprimalreversion BS_ATTACKER, 0
	handleprimalreversion BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_PRIMAL_REVERSION, NULL
	waitanimation
	handleprimalreversion BS_ATTACKER, 2
	printstring STRINGID_PKMNREVERTEDTOPRIMAL
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	end2

BattleScript_PrimalReversionRet::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	@setbyte gIsCriticalHit, 0	dont remember what thsi is for?
	handleprimalreversion BS_ATTACKER, 0
	handleprimalreversion BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_PRIMAL_REVERSION, NULL
	waitanimation
	handleprimalreversion BS_ATTACKER, 2
	printstring STRINGID_PKMNREVERTEDTOPRIMAL
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AttackerFormChange::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	@ call BattleScript_AbilityPopUp
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
BattleScript_AttackerFormChangeNoPopup::
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE, NULL
	waitanimation
	handleformchange BS_ATTACKER, 2
	return

BattleScript_AttackerFormChangeEnd3::
	call BattleScript_AttackerFormChange
	end3

BattleScript_AttackerFormChangeEnd3NoPopup::
	call BattleScript_AttackerFormChangeNoPopup

@need test
BattleScript_AttackerFormChangeMoveEffect::
	waitmessage 1
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE, NULL @not sure what last argument should be
	waitanimation
	copybyte sBATTLER, gBattlerAttacker
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	handleformchange BS_ATTACKER, 2
	end3
	
BattleScript_RaiseStatOnFaintingTarget::
	copybyte gBattlerAbility, gBattlerAttacker
	@ @ call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_LASTABILITYRAISEDSTAT
	waitmessage 0x40
	return

BattleScript_MonTookFutureAttack::
	printstring STRINGID_PKMNTOOKATTACK
	waitmessage 0x40
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_CheckDoomDesireMiss
	accuracycheck BattleScript_FutureAttackMiss, MOVE_FUTURE_SIGHT
	goto BattleScript_FutureAttackAnimate

BattleScript_CheckDoomDesireMiss::
	accuracycheck BattleScript_FutureAttackMiss, MOVE_DOOM_DESIRE
BattleScript_FutureAttackAnimate::
	adjustnormaldamage2
	jumpifbyte CMP_NOT_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_FutureHitAnimDoomDesire
	playanimation BS_ATTACKER, B_ANIM_FUTURE_SIGHT_HIT, NULL
	goto BattleScript_DoFutureAttackHit

BattleScript_FutureHitAnimDoomDesire::
	playanimation BS_ATTACKER, B_ANIM_DOOM_DESIRE_HIT, NULL
BattleScript_DoFutureAttackHit::
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_TARGET, 0, NULL
	confirmlosingteam .+4 @check this make sure updates didnt break 
	@moveendcase 0  was original setup but changed order of case constants so need use actual constant 
	moveendcase MOVE_END_RAGE
	moveendfromto MOVE_END_ITEM_EFFECTS_ALL, MOVE_END_UPDATE_LAST_MOVES
	setbyte gMoveResultFlags, 0
	end2

BattleScript_FutureAttackMiss::
	pause 0x20
	setbyte gMoveResultFlags, 0
	orbyte gMoveResultFlags, MOVE_RESULT_FAILED
	resultmessage
	waitmessage 0x40
	setbyte gMoveResultFlags, 0
	end2

BattleScript_NoMovesLeft::
	printselectionstring STRINGID_PKMNHASNOMOVESLEFT
	endselectionscript

BattleScript_SelectingMoveWithNoPP::
	printselectionstring STRINGID_NOPPLEFT
	endselectionscript

BattleScript_NoPPForMove::
	attackstring
	pause 0x20
	printstring STRINGID_BUTNOPPLEFT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SelectingTormentedMove::
	printselectionstring STRINGID_PKMNCANTUSEMOVETORMENT
	endselectionscript

	printstring STRINGID_PKMNCANTUSEMOVETORMENT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SelectingNotAllowedMoveTaunt::
	printselectionstring STRINGID_PKMNCANTUSEMOVETAUNT
	endselectionscript

BattleScript_SelectingNotAllowedMoveThroatChop::
	printselectionstring STRINGID_PKMNCANTUSEMOVETHROATCHOP
	endselectionscript

BattleScript_SelectingNotAllowedMoveGravity::
	printselectionstring STRINGID_GRAVITYPREVENTSUSAGE
	endselectionscript

BattleScript_SelectingNotAllowedStuffCheeks::
	printselectionstring STRINGID_STUFFCHEEKSCANTSELECT
	endselectionscript

BattleScript_SelectingNotAllowedBelch::
	printselectionstring STRINGID_BELCHCANTSELECT
	endselectionscript

BattleScript_SelectingNotAllowedMoveHealBlock::
	printselectionstring STRINGID_HEALBLOCKPREVENTSUSAGE
	endselectionscript

BattleScript_MoveUsedIsTaunted::
	printstring STRINGID_PKMNCANTUSEMOVETAUNT
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_WishComesTrue::
	trywish 1, BattleScript_WishButFullHp
	playanimation BS_TARGET, B_ANIM_WISH_HEAL, NULL
	printstring STRINGID_PKMNWISHCAMETRUE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage 0x40
	end2

BattleScript_WishButFullHp::
	printstring STRINGID_PKMNWISHCAMETRUE
	waitmessage 0x40
	pause 0x20
	printstring STRINGID_PKMNHPFULL
	waitmessage 0x40
	end2

BattleScript_IngrainTurnHeal::
	playanimation BS_ATTACKER, B_ANIM_INGRAIN_HEAL, NULL
	printstring STRINGID_PKMNABSORBEDNUTRIENTS
BattleScript_TurnHeal:
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_AquaRingHeal::
	playanimation BS_ATTACKER, B_ANIM_INGRAIN_HEAL, NULL
	printstring STRINGID_AQUARINGHEAL
	goto BattleScript_TurnHeal

BattleScript_PrintMonIsRooted::
	pause 0x20
	printstring STRINGID_PKMNANCHOREDITSELF
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AtkDefDown::
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_ATK | BIT_DEF, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE | STAT_CHANGE_DONT_CHECK_LOWER
	playstatchangeanimation BS_ATTACKER, BIT_ATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_ATK, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_AtkDefDownAtkFail
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_AtkDefDownAtkFail
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_AtkDefDownAtkFail::
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_AtkDefDownDefFail
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_AtkDefDownDefFail
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_AtkDefDownDefFail::
	return

BattleScript_DefSpDefDown::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_DONT_CHECK_LOWER | STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_ONLY_MULTIPLE
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_DONT_CHECK_LOWER | STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_BS_PTR, BattleScript_DefSpDefDownTrySpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DefSpDefDownTrySpDef
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_DefSpDefDownTrySpDef::
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_DONT_CHECK_LOWER | STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_BS_PTR, BattleScript_DefSpDefDownRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DefSpDefDownRet
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_DefSpDefDownRet::
	return

BattleScript_DefDownSpeedUp::
	jumpifstat BS_ATTACKER, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_DefDownSpeedUpTryDef
	jumpifstat BS_ATTACKER, CMP_EQUAL, STAT_SPEED, MAX_STAT_STAGE, BattleScript_DefDownSpeedUpRet
BattleScript_DefDownSpeedUpTryDef::
	playstatchangeanimation BS_ATTACKER, BIT_DEF, STAT_CHANGE_DONT_CHECK_LOWER | STAT_CHANGE_STAT_NEGATIVE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR | MOVE_EFFECT_CERTAIN, BattleScript_DefDownSpeedUpTrySpeed
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefDownSpeedUpTrySpeed
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefDownSpeedUpTrySpeed:
	playstatchangeanimation BS_ATTACKER, BIT_SPEED, 0
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR | MOVE_EFFECT_CERTAIN, BattleScript_DefDownSpeedUpRet
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_DefDownSpeedUpRet
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DefDownSpeedUpRet::
	return

BattleScript_KnockedOff::
	playanimation BS_TARGET, B_ANIM_ITEM_KNOCKOFF, NULL
	printstring STRINGID_PKMNKNOCKEDOFF
	waitmessage 0x40
	return

BattleScript_MoveUsedIsImprisoned::
	printstring STRINGID_PKMNCANTUSEMOVESEALED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SelectingImprisonedMove::
	printselectionstring STRINGID_PKMNCANTUSEMOVESEALED
	endselectionscript

BattleScript_GrudgeTakesPp::
	printstring STRINGID_PKMNLOSTPPGRUDGE
	waitmessage 0x40
	return

BattleScript_MagicCoatBounce::
	attackstring
	ppreduce
	pause 0x20
	printstring STRINGID_PKMNMOVEBOUNCED
	waitmessage 0x40
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_ALLOW_NO_PP
	setmagiccoattarget BS_ATTACKER
	return

BattleScript_SnatchedMove::
	attackstring
	ppreduce
	snatchsetbattlers
	playanimation BS_TARGET, B_ANIM_SNATCH_MOVE, NULL
	printstring STRINGID_PKMNSNATCHEDMOVE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED | HITMARKER_NO_PPDEDUCT | HITMARKER_ALLOW_NO_PP
	swapattackerwithtarget
	return

BattleScript_EnduredMsg::
	printstring STRINGID_PKMNENDUREDHIT
	waitmessage 0x40
	return

BattleScript_OneHitKOMsg::
	printstring STRINGID_ONEHITKO
	waitmessage 0x40
	return

BattleScript_SturdiedMsg::
	pause B_WAIT_TIME_SHORTEST
	@ call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ENDUREDSTURDY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AttackerSturdiedMsg::
	pause B_WAIT_TIME_SHORTEST
	@ call BattleScript_AbilityPopUpTarget
	printstring STRINGID_ATTACKER_STURDY
	waitmessage B_WAIT_TIME_LONG
	return	


BattleScript_SAtkDown2::
	setbyte sSTAT_ANIM_PLAYED, 0
	playstatchangeanimation BS_ATTACKER, BIT_SPATK, STAT_CHANGE_STAT_NEGATIVE | STAT_CHANGE_STAT_BY_TWO | STAT_CHANGE_DONT_CHECK_LOWER
	setstatchanger STAT_SPATK, 2, TRUE
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_SAtkDown2End
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 2, BattleScript_SAtkDown2End
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_SAtkDown2End::
	return

BattleScript_MoveEffectClearSmog::
	printstring STRINGID_RESETSTARGETSSTATLEVELS
	waitmessage 0x40
	return

BattleScript_FocusPunchSetUp::
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	playanimation BS_ATTACKER, B_ANIM_FOCUS_PUNCH_SETUP, NULL
	printstring STRINGID_PKMNTIGHTENINGFOCUS
	waitmessage 0x40
	end2

BattleScript_MoveUsedIsAsleep::
	printstring STRINGID_PKMNFASTASLEEP
	waitmessage 0x40
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MoveUsedWokeUp::
	bicword gHitMarker, HITMARKER_WAKE_UP_CLEAR
	printfromtable gWokeUpStringIds
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	return

BattleScript_MonWokeUpInUproar::
	printstring STRINGID_PKMNWOKEUPINUPROAR
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	end2

BattleScript_PoisonTurnDmg::
	printstring STRINGID_PKMNHURTBYPOISON
	waitmessage 0x40
BattleScript_DoStatusTurnDmg::
	statusanimation BS_ATTACKER
BattleScript_DoTurnDmg::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	tryfaintmon BS_ATTACKER, 0, NULL
	confirmlosingteam BattleScript_DoTurnDmgEnd
BattleScript_DoTurnDmgEnd:
	end2

BattleScript_PoisonHealActivates::
	printstring STRINGID_POISONHEALHPUP
	waitmessage B_WAIT_TIME_LONG
	statusanimation BS_ATTACKER
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_BurnTurnDmg::
	printstring STRINGID_PKMNHURTBYBURN
	waitmessage 0x40
	goto BattleScript_DoStatusTurnDmg

BattleScript_FreezeTurnDmg::
	printstring STRINGID_PKMNHURTBYFREEZE
	waitmessage 0x40
	goto BattleScript_DoStatusTurnDmg

BattleScript_FrostbiteTurnDmg::
	printstring STRINGID_PKMNHURTBYFROSTBITE
	waitmessage 0x40
	goto BattleScript_DoStatusTurnDmg

BattleScript_MoveUsedIsFrozen::
	printstring STRINGID_PKMNISFROZEN
	waitmessage 0x40
	statusanimation BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MoveUsedUnfroze::
	printfromtable gGotDefrostedStringIds
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	return

BattleScript_DefrostedViaFireMove::
	printstring STRINGID_PKMNWASDEFROSTED
	waitmessage 0x40
	updatestatusicon BS_TARGET
	return

BattleScript_DefrostBattler_KeepStatus::
	printstring STRINGID_DEFROST_POKEMON
	waitmessage 0x40
	return

BattleScript_MoveUsedIsParalyzed::
	printstring STRINGID_PKMNISPARALYZED
	waitmessage 0x40
	statusanimation BS_ATTACKER
	cancelmultiturnmoves BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_MovePressureCanceler::
	printstring STRINGID_PRESSUREATKCANCEL
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_MON_SCARED, NULL
	cancelmultiturnmoves BS_ATTACKER
	goto BattleScript_MoveEnd

BattleScript_PowderMoveNoEffect::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	jumpiftype BS_TARGET, TYPE_GRASS, BattleScript_PowderMoveNoEffectPrint
	jumpifability BS_TARGET, ABILITY_OVERCOAT, BattleScript_PowderMoveNoEffectOvercoat
	printstring STRINGID_SAFETYGOGGLESPROTECTED
	goto BattleScript_PowderMoveNoEffectWaitMsg
BattleScript_PowderMoveNoEffectOvercoat:
	@call BattleScript_AbilityPopUp
BattleScript_PowderMoveNoEffectPrint:
	printstring STRINGID_ITDOESNTAFFECT
BattleScript_PowderMoveNoEffectWaitMsg:
	waitmessage B_WAIT_TIME_LONG
	cancelmultiturnmoves BS_ATTACKER
	sethword gMoveResultFlags, MOVE_RESULT_FAILED
	goto BattleScript_MoveEnd

BattleScript_MoveUsedFlinched::
	printstring STRINGID_PKMNFLINCHED
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_PrintUproarOverTurns::
	printfromtable gUproarOverTurnStringIds
	waitmessage 0x40
	end2

BattleScript_ThrashConfuses::
	chosenstatusanimation BS_ATTACKER, 1, STATUS2_CONFUSION
	printstring STRINGID_PKMNFATIGUECONFUSION
	waitmessage 0x40
	end2

BattleScript_MoveUsedIsConfused::
	printstring STRINGID_PKMNISCONFUSED
	waitmessage 0x40
	status2animation BS_ATTACKER, STATUS2_CONFUSION
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0, BattleScript_MoveUsedIsConfusedRet
BattleScript_DoSelfConfusionDmg::
	cancelmultiturnmoves BS_ATTACKER
	adjustnormaldamage2
	printstring STRINGID_ITHURTCONFUSION
	waitmessage 0x40
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	resultmessage
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_MoveUsedIsConfusedRet::
	return

BattleScript_MoveUsedPowder::
	bicword gHitMarker, HITMARKER_NO_ATTACKSTRING | HITMARKER_ATTACKSTRING_PRINTED
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	cancelmultiturnmoves BS_ATTACKER
	status2animation BS_ATTACKER, STATUS2_POWDER
	waitanimation
	effectivenesssound
	hitanimation BS_ATTACKER
	waitstate
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_POWDEREXPLODES
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER, 0, NULL
	goto BattleScript_MoveEnd

BattleScript_MoveUsedIsConfusedNoMore::
	printstring STRINGID_PKMNHEALEDCONFUSION
	waitmessage 0x40
	return

BattleScript_PrintPayDayMoneyString::
	printstring STRINGID_PKMNPICKEDUPITEM
	waitmessage 0x40
	return

BattleScript_WrapTurnDmg::
	jumpifability BS_ATTACKER, ABILITY_MAGIC_GUARD, BattleScript_DoTurnDmgEnd
	playanimation BS_ATTACKER, B_ANIM_TURN_TRAP, sB_ANIM_ARG1
	printstring STRINGID_PKMNHURTBY
	waitmessage 0x40
	goto BattleScript_DoTurnDmg

BattleScript_WrapEnds::
	printstring STRINGID_PKMNFREEDFROM
	waitmessage 0x40
	end2

BattleScript_MoveUsedIsInLove::
	printstring STRINGID_PKMNINLOVE
	waitmessage 0x40
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	return

BattleScript_MoveUsedIsInLoveCantAttack::
	printstring STRINGID_PKMNIMMOBILIZEDBYLOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_NightmareTurnDmg::
	printstring STRINGID_PKMNLOCKEDINNIGHTMARE
	waitmessage 0x40
	status2animation BS_ATTACKER, STATUS2_NIGHTMARE
	goto BattleScript_DoTurnDmg

BattleScript_CurseTurnDmg::
	printstring STRINGID_PKMNAFFLICTEDBYCURSE
	waitmessage 0x40
	status2animation BS_ATTACKER, STATUS2_CURSED
	goto BattleScript_DoTurnDmg

BattleScript_TargetPRLZHeal::
	printstring STRINGID_PKMNHEALEDPARALYSIS
	waitmessage 0x40
	updatestatusicon BS_TARGET
	return

BattleScript_TargetWokeUp::
	printstring STRINGID_TARGETWOKEUP
	waitmessage 0x40
	updatestatusicon BS_TARGET
	return

BattleScript_TargetBurnHeal::
	printstring STRINGID_PKMNBURNHEALED
	waitmessage 0x40
	updatestatusicon BS_TARGET
	return

BattleScript_TooScaredToMove::
	printstring STRINGID_MONTOOSCAREDTOMOVE
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_MON_SCARED, NULL
	goto BattleScript_MoveEnd

BattleScript_GhostGetOutGetOut::
	printstring STRINGID_GHOSTGETOUTGETOUT
	playanimation BS_ATTACKER, B_ANIM_GHOST_GET_OUT, NULL
	goto BattleScript_MoveEnd

BattleScript_SilphScopeUnveiled::
	pause 0x20
	printstring STRINGID_SILPHSCOPEUNVEILED
	waitstate
	playanimation BS_OPPONENT1, B_ANIM_SILPH_SCOPED, NULL
	pause 0x20
	printstring STRINGID_GHOSTWASMAROWAK
	waitmessage 0x40
	end2

BattleScript_MoveEffectSleep::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gFellAsleepStringIds
	waitmessage 0x40
BattleScript_UpdateEffectStatusIconRet::
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	return

BattleScript_YawnMakesAsleep::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNFELLASLEEP
	waitmessage 0x40
	updatestatusicon BS_EFFECT_BATTLER
	waitstate
	makevisible BS_EFFECT_BATTLER
	end2

BattlesScript_RoostEnds::
	printstring STRINGID_PKMNSTOPPEDROOSTING
	waitmessage 0x40
	end2

BattleScript_EmbargoEndTurn::
	printstring STRINGID_EMBARGOENDS
	waitmessage 0x40
	end2

BattleScript_TelekinesisEndTurn::
	printstring STRINGID_TELEKINESISENDS
	waitmessage 0x40
	end2

BattleScript_LuckyChantEnds::
	printstring STRINGID_LUCKYCHANTENDS
	waitmessage 0x40
	end2

BattleScript_TailwindEnds::
	printstring STRINGID_TAILWINDENDS
	waitmessage 0x40
	end2

BattleScript_TrickRoomEnds::
	printstring STRINGID_TRICKROOMENDS
	waitmessage 0x40
	end2

BattleScript_WonderRoomEnds::
	printstring STRINGID_WONDERROOMENDS
	waitmessage 0x40
	end2

BattleScript_MagicRoomEnds::
	printstring STRINGID_MAGICROOMENDS
	waitmessage 0x40
	end2

BattleScript_ElectricTerrainEnds::
	printstring STRINGID_ELECTRICTERRAINENDS
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG, NULL
	end2

BattleScript_MistyTerrainEnds::
	printstring STRINGID_MISTYTERRAINENDS
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG, NULL
	end2

BattleScript_GrassyTerrainEnds::
	printstring STRINGID_GRASSYTERRAINENDS
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG, NULL
	end2

BattleScript_PsychicTerrainEnds::
	printstring STRINGID_PSYCHICTERRAINENDS
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG, NULL
	end2

BattleScript_GravityEnds::
	printstring STRINGID_GRAVITYENDS
	waitmessage 0x40
	end2

BattleScript_MoveEffectAttract::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNFELLINLOVE
	waitmessage 0x40
	return

BattleScript_MoveEffectPoison::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotPoisonedStringIds
	waitmessage 0x40
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectBurn::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotBurnedStringIds
	waitmessage 0x40
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectFreeze::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotFrozenStringIds
	waitmessage 0x40
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_MoveEffectParalysis::
	statusanimation BS_EFFECT_BATTLER
	printfromtable gGotParalyzedStringIds
	waitmessage 0x40
	goto BattleScript_UpdateEffectStatusIconRet

@change to match above when get status icon setup, plan kamen raider esque neon green icon with bug mask
BattleScript_MoveEffectInfestation::
	@setmoveeffect MOVE_EFFECT_INFESTATION
	printstring STRINGID_INFESTATION
	waitmessage 0x40
	return

BattleScript_StatusInfested::
	playanimation BS_ATTACKER, B_ANIM_STATUS_INFESTED, NULL
	printstring STRINGID_PKMNINFESTED
	waitmessage 0x40
	return

BattleScript_MoveEffectSpiritLock::
	goto BattleScript_UpdateEffectStatusIconRet

BattleScript_AftermathOnSwitch::
	pause 0x01
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_ATTACKER_ABILITYHURTS_TARGET
	waitmessage B_WAIT_TIME_SHORT
	tryfaintmon BS_TARGET, FALSE, NULL
	setmoveeffect MOVE_EFFECT_SPD_MINUS_1 | MOVE_EFFECT_CERTAIN
	setmoveeffectwithchance
BattleScript_AftermathEndRet:
	return

@uses diff arguemnts because it takes place on mon attacking aftermon target
BattleScript_AftermathDmg::
	pause 0x01
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_AFTERMATHDMG
	waitmessage B_WAIT_TIME_SHORT
	tryfaintmon BS_ATTACKER, FALSE, NULL
	setmoveeffect MOVE_EFFECT_SPD_MINUS_2 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	setmoveeffectwithchance
	@seteffectsecondary  @should lower speed, if enemy doesnt faint
	return

BattleScript_DampPreventsAftermath::
	pause B_WAIT_TIME_SHORT
	@call BattleScript_AbilityPopUp
	pause 40
	copybyte gBattlerAbility, sBATTLER
	@call BattleScript_AbilityPopUp
	printstring STRINGID_PKMNSABILITYPREVENTSABILITY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_AnticipationActivates::
	pause 0x5
	printstring STRINGID_ANTICIPATIONACTIVATES
	waitmessage 0x40
	return

BattleScript_CottonDownActivates::
	copybyte gEffectBattler, gBattlerTarget
	savetarget
	setbyte gBattlerTarget, 0x0
BattleScript_CottonDownLoop:
	setstatchanger STAT_SPEED, 1, TRUE
	jumpifbyteequal gBattlerTarget, gEffectBattler, BattleScript_CottonDownLoopIncrement
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CottonDownTargetSpeedCantGoLower
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40
	goto BattleScript_CottonDownLoopIncrement
BattleScript_CottonDownTargetSpeedCantGoLower:
	printstring STRINGID_STATSWONTDECREASE
	waitmessage 0x40
BattleScript_CottonDownLoopIncrement:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_CottonDownLoop
BattleScript_CottonDownReturn:
	restoretarget
	return

BattleScript_IllusionOff::
	spriteignore0hp TRUE
	playanimation BS_TARGET, B_ANIM_ILLUSION_OFF, NULL
	waitanimation
	updatenick BS_TARGET
	waitstate
	spriteignore0hp FALSE
	printstring STRINGID_ILLUSIONWOREOFF
	waitmessage 0x40
	return

BattleScript_MoveEffectUproar::
	printstring STRINGID_PKMNCAUSEDUPROAR
	waitmessage 0x40
	return

BattleScript_MoveEffectToxic::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNBADLYPOISONED
	waitmessage 0x40
	goto BattleScript_UpdateEffectStatusIconRet

@setmoveeffect function is the basis for all move effects, the setmoveeffectwithchance command & augments as well.
@so for this poinsoning mechanc I need to properly set it up through setmoveeffect, and then have proper checks in bs command, like above 
@to skip STATUS1_ANY check.
@@edited, did work in main setmoveeffect dont think ill be usin this script at all. string will only be used on toxic.
BattleScript_PoisonWorsened::
	statusanimation BS_EFFECT_BATTLER
	printstring STRINGID_PKMNSPOISONWORSENED
	waitmessage 0x40
	return

BattleScript_MoveEffectPayDay::
	printstring STRINGID_COINSSCATTERED
	waitmessage 0x40
	return

BattleScript_MoveEffectWrap::
	printfromtable gWrappedStringIds
	waitmessage 0x40
	return

BattleScript_MoveEffectConfusion::
	chosenstatusanimation BS_EFFECT_BATTLER, 1, STATUS2_CONFUSION
	printstring STRINGID_PKMNWASCONFUSED
	waitmessage 0x40
	return

BattleScript_ToxicOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectToxic
	end2

BattleScript_FlameOrb::
	setbyte cMULTISTRING_CHOOSER, 0
	copybyte gEffectBattler, gBattlerAttacker
	call BattleScript_MoveEffectBurn
	end2


BattleScript_MoveEffectRecoilWithStatus::
	argumentstatuseffect
	@copyword gBattleMoveDamage, sSAVED_DMG  dont need this actualy becauase my version doesnt use sSAVED_DMG
BattleScript_MoveEffectRecoil::
	jumpifmove MOVE_STRUGGLE, BattleScript_DoRecoil
	jumpifability BS_ATTACKER, ABILITY_ROCK_HEAD, BattleScript_RecoilEnd
	jumpifability BS_ATTACKER, ABILITY_KLUTZ, BattleScript_RecoilEnd
BattleScript_DoRecoil::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHITWITHRECOIL
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
BattleScript_RecoilEnd::
	return	

BattleScript_ItemSteal::
	playanimation BS_TARGET, B_ANIM_ITEM_STEAL, NULL
	printstring STRINGID_PKMNSTOLEITEM
	waitmessage 0x40
	return

BattleScript_HailActivates::
	pause 0x20
	printstring STRINGID_PKMNSXCALLEDDOWNHAIL
	waitstate
	sethail
	playanimation BS_BATTLER_0, B_ANIM_HAIL_CONTINUES, NULL
	waitanimation
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_AbilityRaisesDefenderStat::
	pause 0x20	
	statbuffchange 0, NULL
	setgraphicalstatchangevalues
	playanimation BS_ABILITY_BATTLER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_DEFENDERSSTATROSE
	waitmessage 0x40
	return

@BattleScript_AbilityPopUp:
@	showabilitypopup BS_ABILITY_BATTLER
@	recordlastability BS_ABILITY_BATTLER
@	pause 40
@	return

BattleScript_SpeedBoostActivates::
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_PKMNRAISEDSPEED
	waitmessage 0x40
	end3

BattleScript_DefeatistActivates::	@CHECK may need to customizee buff anim that plays
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_DEFEATISTACTIVATED
	waitmessage 0x40
	end3

@ Cant compare directly to a value, have to compare to value at pointer
sZero:
.byte 0

BattleScript_MoodyActivates::	
	jumpifbyteequal sSTATCHANGER, sZero, BattleScript_MoodyLower
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyLower
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 0x1, BattleScript_MoodyLower
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_MoodyLower:
	jumpifbyteequal sSAVED_STAT_CHANGER, sZero, BattleScript_MoodyEnd
	copybyte sSTATCHANGER, sSAVED_STAT_CHANGER
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoodyEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 0x1, BattleScript_MoodyEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage 0x40
BattleScript_MoodyEnd:
	end3
	
BattleScript_EmergencyExit::
	pause 0x5	
	pause 0x40
BattleScript_EmergencyExitNoPopUp::
	playanimation BS_TARGET, B_ANIM_SLIDE_OFFSCREEN, NULL
	waitanimation
	openpartyscreen BS_TARGET, BattleScript_EmergencyExitRet
	switchoutabilities BS_TARGET
	waitstate
	switchhandleorder BS_TARGET, 2
	returntoball BS_TARGET
	getswitchedmondata BS_TARGET
	switchindataupdate BS_TARGET
	hpthresholds BS_TARGET
	printstring STRINGID_SWITCHINMON
	switchinanim BS_TARGET, TRUE
	waitstate
	switchineffects BS_TARGET
BattleScript_EmergencyExitRet:
	return
	
BattleScript_EmergencyExitWild::
	pause 0x5	
	pause 0x40
BattleScript_EmergencyExitWildNoPopUp::
	playanimation BS_TARGET, B_ANIM_SLIDE_OFFSCREEN, NULL
	waitanimation
	setoutcomeonteleport BS_TARGET
	finishaction
	return

BattleScript_TraceActivates::
	pause 0x20
	printstring STRINGID_PKMNTRACED
	waitmessage 0x40
	healthbarupdate BS_ATTACKER  @? why??
	datahpupdate BS_ATTACKER
	end3

BattleScript_ReceiverActivates::	
	printstring STRINGID_RECEIVERABILITYTAKEOVER
	waitmessage 0x40
	settracedability BS_ABILITY_BATTLER
	return
	
BattleScript_AbilityHpHeal::	
	printstring STRINGID_PKMNSXRESTOREDHPALITTLE2
	waitmessage 0x40
	call BattleScript_HealAnimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_RainDishActivates::
	printstring STRINGID_PKMNSXRESTOREDHPALITTLE2
	waitmessage 0x40
BattleScript_HealWithoutMessage::
	call BattleScript_HealAnimation
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end3

BattleScript_CheekPouchActivates::
	copybyte sBATTLER, gBattlerAttacker
	copybyte gBattlerAttacker, gBattlerAbility
	call BattleScript_AbilityHpHeal
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_HarvestActivates::
	pause 0x5	
	printstring STRINGID_HARVESTBERRY
	waitmessage 0x40
	end3

BattleScript_SolarPowerActivates::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE	
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_SOLARPOWERHPDROP
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, FALSE, NULL
	end3
	
BattleScript_EffectFreezeDry:
BattleScript_EffectFreezeHit::
	setmoveeffect MOVE_EFFECT_FREEZE
	goto BattleScript_EffectHit

BattleScript_HealerActivates::	
	curestatus BS_SCRIPTING
	updatestatusicon BS_SCRIPTING
	printstring STRINGID_HEALERCURE
	waitmessage 0x40
	end3

BattleScript_SandstreamActivates::
	pause 0x20
	printstring STRINGID_PKMNSXWHIPPEDUPSANDSTORM
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SANDSTORM_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

@NEED test
BattleScript_SandSpitActivates::
	pause B_WAIT_TIME_SHORT
	@call BattleScript_AbilityPopUp
	printstring STRINGID_TARGETSXWHIPPEDUPSANDSTORM
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SANDSTORM_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	return

BattleScript_ShedSkinActivates::
	printstring STRINGID_PKMNSXCUREDYPROBLEM
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	end3

BattleScript_PurifyingAuraActivates::
	printstring STRINGID_HEALERCURE
	waitmessage 0x40
	updatestatusicon BS_ATTACKER
	end3

BattleScript_PurifyingAuraActivatesForPartner::
	printstring STRINGID_HEALERCURE
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	end3

BattleScript_HandleWeatherFormChanges::
	setbyte sBATTLER, 0
BattleScript_WeatherFormChangesLoop::
	trycastformdatachange @PROB why cherrim change didnt work, update for cherrim species
	addbyte sBATTLER, 1
	jumpifbytenotequal sBATTLER, gBattlersCount, BattleScript_WeatherFormChangesLoop
	return

BattleScript_CastformChange::
	call BattleScript_DoCastformChangeAnim
	end3

BattleScript_DoCastformChangeAnim::
	docastformchangeanimation
	waitstate
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage 0x40
	return

sByteFour:
.byte MAX_BATTLERS_COUNT

@these two work
BattleScript_NeutralizingGasExits::
	savetarget
	pause 0x20
	printstring STRINGID_NEUTRALIZINGGASOVER
	waitmessage 0x40
	setbyte gBattlerTarget, 0
BattleScript_NeutralizingGasExitsLoop:
	switchinabilities BS_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, sByteFour, BattleScript_NeutralizingGasExitsLoop	@ SOMEHOW, comparing to gBattlersCount is problematic.
	restoretarget
	return

BattleScript_StenchExits::
	savetarget
	pause 0x20
	printstring STRINGID_STENCHENDS
	waitmessage 0x40
	setbyte gBattlerTarget, 0
BattleScript_StenchExitsLoop:
	switchinabilities BS_TARGET
	addbyte gBattlerTarget, 1
	jumpifbytenotequal gBattlerTarget, sByteFour, BattleScript_NeutralizingGasExitsLoop	@ SOMEHOW, comparing to gBattlersCount is problematic.
	restoretarget
	return

BattleScript_MagicianActivates::
	@call BattleScript_AbilityPopUp
	call BattleScript_ItemSteal
	return

BattleScript_SymbiosisActivates::
	@call BattleScript_AbilityPopUp
	printstring STRINGID_SYMBIOSISITEMPASS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_TargetAbilityStatRaiseRet::
	copybyte gBattlerAbility, gEffectBattler
	copybyte gBattlerAttacker, gBattlerTarget
	@call BattleScript_AbilityPopUp
	statbuffchange MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN, BattleScript_TargetAbilityStatRaiseRet_End
	setgraphicalstatchangevalues
	call BattleScript_StatUp
BattleScript_TargetAbilityStatRaiseRet_End:
	return

BattleScript_TryAdrenalineOrb:
	jumpifnoholdeffect BS_TARGET, HOLD_EFFECT_ADRENALINE_ORB, BattleScript_TryAdrenalineOrbRet
	jumpifstat BS_TARGET, CMP_EQUAL, STAT_SPEED, 12, BattleScript_TryAdrenalineOrbRet
	setstatchanger STAT_SPEED, 1, FALSE
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN | STAT_CHANGE_BS_PTR, BattleScript_TryAdrenalineOrbRet
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	copybyte sBATTLER, gBattlerTarget
	setlastuseditem BS_TARGET
	printstring STRINGID_USINGXTHEYOFZN
	waitmessage 0x40
	removeitem BS_TARGET
BattleScript_TryAdrenalineOrbRet:
	return

BattleScript_IntimidateActivatesEnd3::
	call BattleScript_DoIntimidateActivationAnim
	end3

@does nothing now, but put here to compile from use in battle_script_commands
BattleScript_ReactivateIntimidate::
	end3

BattleScript_DoIntimidateActivationAnim::
	pause 0x20
BattleScript_IntimidateActivates::
	jumpifability BS_ATTACKER, ABILITY_TIGER_MOM, BattleScript_TigerMomActivates	@JUMPS attack drop and does def drop instead then goes to loop
	setbyte gBattlerTarget, 0
	setstatchanger STAT_ATK, 1, TRUE
		@Think Ill cut this down by making a new command to do ability check, and fail jump that way can do all checks in 1 line.
		@specific stat abilities like hypercutter would need to be kept out, to still do tiger mom, so make it general stat drop/intimidate exclusions not stat specific stuff.
BattleScript_IntimidateActivationAnimLoop::
	trygetintimidatetarget BattleScript_IntimidateEnd @updated intimidate to current gen standard
	jumpiftype BS_ATTACKER, TYPE_DARK, BattleScript_IntimidateFailChecks	@if attkaer dark avoids intimidate failing on dark mon	@DARK Buff after changes, immune to intimidation
BattleScript_IntimidateDarkCheck:
	jumpiftype BS_TARGET, TYPE_DARK, BattleScript_IntimidateFail	
BattleScript_IntimidateFailChecks:
	jumpifstatus2 BS_TARGET, STATUS2_SUBSTITUTE, BattleScript_IntimidateFail		@forgot tiger mom had to different ability exclusion need rearrange abilities here
	jumpifability BS_TARGET, ABILITY_CLEAR_BODY, BattleScript_IntimidateAbilityFail		@and then jump out, before atk stat specific exclusions
	jumpifability BS_TARGET, ABILITY_LEAF_GUARD, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_FULL_METAL_BODY, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_LIQUID_METAL, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_WHITE_SMOKE, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_INNER_FOCUS, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_SCRAPPY, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_OWN_TEMPO, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_OBLIVIOUS, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_UNAWARE, BattleScript_IntimidateAbilityFail
	jumpifability BS_ATTACKER, ABILITY_INTIMIDATE, BattleScipt_Intimidate_AttackDropExclusions
	jumpifability BS_ATTACKER, ABILITY_TIGER_MOM, BattleScipt_TigerMom_DefenseDropExclusions	@jump for tigermom to skip atk specific stat drop exclusions
BattleScript_IntimidateStatDrop::	
	copybyte sBATTLER, gBattlerAttacker
	statbuffchange STAT_CHANGE_BS_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_IntimidateFail
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 1, BattleScript_IntimidateFail
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	jumpifability BS_ATTACKER, ABILITY_TIGER_MOM, BattleScript_TigerMomBattleMessage
	printstring STRINGID_PKMNCUTSATTACKWITH
	waitmessage 0x40
BattleScript_IntimidateFail::
	addbyte gBattlerTarget, 1 @ this value keeps the command from looping on single target
	goto BattleScript_IntimidateActivationAnimLoop

BattleScript_IntimidateEnd::
	return

BattleScript_IntimidateAbilityFail::
	pause 0x20
	printstring STRINGID_PREVENTEDFROMWORKING
	waitmessage 0x40
	goto BattleScript_IntimidateFail

BattleScript_TigerMomActivates::
	setbyte gBattlerTarget, 0
	setstatchanger STAT_DEF, 1, TRUE
	goto BattleScript_IntimidateActivationAnimLoop

BattleScript_TigerMomBattleMessage::
	printstring STRINGID_TIGER_MOM_ACTIVATES
	waitmessage 0x40
	goto BattleScript_IntimidateFail

BattleScipt_TigerMom_DefenseDropExclusions::
	jumpifability BS_TARGET, ABILITY_BIG_PECKS, BattleScript_IntimidateAbilityFail
	goto BattleScript_IntimidateStatDrop

BattleScipt_Intimidate_AttackDropExclusions::
	jumpifability BS_TARGET, ABILITY_BIG_PECKS, BattleScript_IntimidateAbilityFail
	jumpifability BS_TARGET, ABILITY_HYPER_CUTTER, BattleScript_IntimidateAbilityFail
	goto BattleScript_IntimidateStatDrop

BattleScript_DrizzleActivates::
	pause 0x20
	printstring STRINGID_PKMNMADEITRAIN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_RAIN_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_DroughtActivates::
	pause 0x20
	printstring STRINGID_PKMNSXINTENSIFIEDSUN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SUN_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_DesolateLandActivates::
	pause B_WAIT_TIME_SHORT
	@ call BattleScript_AbilityPopUp
	printstring STRINGID_EXTREMELYHARSHSUNLIGHT
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_SUN_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_DesolateLandEvaporatesWaterTypeMoves::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause B_WAIT_TIME_SHORT
	ppreduce
	printstring STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_PrimordialSeaActivates::
	pause B_WAIT_TIME_SHORT
	@@ call BattleScript_AbilityPopUp
	printstring STRINGID_HEAVYRAIN
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_RAIN_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_PrimordialSeaFizzlesOutFireTypeMoves::
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause B_WAIT_TIME_SHORT
	ppreduce
	printstring STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_DeltaStreamActivates::
	pause B_WAIT_TIME_SHORT
	@ call BattleScript_AbilityPopUp
	printstring STRINGID_MYSTERIOUSAIRCURRENT
	waitstate
	playanimation BS_ATTACKER, B_ANIM_STRONG_WINDS, NULL
	end3

BattleScript_AttackWeakenedByStrongWinds::
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ATTACKWEAKENEDBYSTRONGWINDS
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_SnowWarningActivates::
	pause 0x20	
	printstring STRINGID_SNOWWARNINGHAIL
	waitstate
	playanimation BS_BATTLER_0, B_ANIM_HAIL_CONTINUES, NULL
	call BattleScript_HandleWeatherFormChanges
	end3

BattleScript_ActivateTerrainAbilities:		@pretty sure dont need this as handled with switchin stuff
	copybyte sBATTLER, gBattlerAttacker
	setbyte gBattlerAttacker, 0
BattleScript_ActivateTerrainAbilities_Loop:
	@activateterrainchangeabilities BS_ATTACKER
BattleScript_ActivateTerrainAbilities_Increment:
	addbyte gBattlerAttacker, 1
	jumpifbytenotequal gBattlerAttacker, gBattlersCount, BattleScript_ActivateTerrainAbilities_Loop
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_TerrainSeedLoop:
	savetarget
	setbyte gBattlerTarget, 0
BattleScript_TerrainSeedLoopIter:
	copybyte sBATTLER, gBattlerTarget
	doterrainseed BS_TARGET, BattleScript_TerrainSeedLoop_NextBattler
	removeitem BS_TARGET
BattleScript_TerrainSeedLoop_NextBattler:
	addbyte gBattlerTarget, 0x1
	jumpifbytenotequal gBattlerTarget, gBattlersCount, BattleScript_TerrainSeedLoopIter
	restoretarget
	return

BattleScript_ElectricSurgeActivates::
	pause 0x20	
	printstring STRINGID_TERRAINBECOMESELECTRIC
	waitstate
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	@call BattleScript_ActivateTerrainAbilities
	call BattleScript_TerrainSeedLoop
	end3

BattleScript_MistySurgeActivates::
	pause 0x20	
	printstring STRINGID_TERRAINBECOMESMISTY
	waitstate
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	@call BattleScript_ActivateTerrainAbilities
	call BattleScript_TerrainSeedLoop
	end3

BattleScript_GrassySurgeActivates::
	pause 0x20	
	printstring STRINGID_TERRAINBECOMESGRASSY
	waitstate
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	@call BattleScript_ActivateTerrainAbilities
	call BattleScript_TerrainSeedLoop
	end3

BattleScript_PsychicSurgeActivates::
	pause 0x20	
	printstring STRINGID_TERRAINBECOMESPSYCHIC
	waitstate
	playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	@call BattleScript_ActivateTerrainAbilities
	call BattleScript_TerrainSeedLoop
	end3

BattleScript_LavaDistortionActivates::
	pause 0x20	
	printstring STRINGID_TERRAINBECOMESFIRE
	waitstate
	@playanimation BS_SCRIPTING, B_ANIM_RESTORE_BG, NULL
	@@call BattleScript_ActivateTerrainAbilities
	@call BattleScript_TerrainSeedLoop	@no seed for fire/water terrains as they also get weather would need to make
	end3

BattleScript_BadDreamsActivates::
	setbyte gBattlerTarget, 0	
BattleScript_BadDreamsLoop:
	trygetbaddreamstarget BattleScript_BadDreamsEnd
	jumpifability BS_TARGET, ABILITY_MAGIC_GUARD, BattleScript_BadDreamsIncrement
BattleScript_BadDreams_Dmg:
	dmg_1_8_targethp
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	printstring STRINGID_BADDREAMSDMG
	waitmessage 0x40
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	tryfaintmon BS_TARGET, FALSE, NULL
	confirmlosingteam BattleScript_BadDreamsIncrement
BattleScript_BadDreamsIncrement:
	addbyte gBattlerTarget, 1
	goto BattleScript_BadDreamsLoop
BattleScript_BadDreamsEnd:
	end3

BattleScript_TookAttack::
	attackstring
	pause 0x20
BattleScript_TookAttackFromString:
	printstring STRINGID_PKMNSXTOOKATTACK
	waitmessage 0x40
	orword gHitMarker, HITMARKER_ATTACKSTRING_PRINTED
	return

BattleScript_SturdyPreventsOHKO::
	pause 0x20
	printstring STRINGID_PKMNPROTECTEDBY
	pause 0x40
	goto BattleScript_MoveEnd

BattleScript_DampStopsExplosion::
	pause 0x20
	printstring STRINGID_PKMNPREVENTSUSAGE
	pause 0x40
	goto BattleScript_MoveEnd

BattleScript_MoveHPDrain_PPLoss::
	ppreduce
BattleScript_MoveHPDrain::
	attackstring
	pause 0x20
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNRESTOREDHPUSING
	waitmessage 0x40
	orbyte gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_MoveStatDrain_PPLoss::
	ppreduce
BattleScript_MoveStatDrain::
	attackstring
	pause B_WAIT_TIME_SHORT
	@call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage B_WAIT_TIME_LONG
	clearsemiinvulnerablebit
	tryfaintmon BS_ATTACKER, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_MonMadeMoveUseless_PPLoss::
	ppreduce
BattleScript_MonMadeMoveUseless::
	attackstring
	pause 0x20
	printstring STRINGID_PKMNSXMADEYUSELESS
	waitmessage 0x40
	orbyte gMoveResultFlags, MOVE_RESULT_DOESNT_AFFECT_FOE
	goto BattleScript_MoveEnd

BattleScript_FlashFireBoost_PPLoss::
	ppreduce
BattleScript_FlashFireBoost::
	attackstring
	pause 0x20
	printfromtable gFlashFireStringIds
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AbilityPreventsPhasingOut::
	pause 0x20
	printstring STRINGID_PKMNANCHORSITSELFWITH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_AbilityNoStatLoss::
	pause 0x20
	printstring STRINGID_PKMNPREVENTSSTATLOSSWITH
	waitmessage 0x40
	return

BattleScript_BRNPrevention::
	pause 0x20
	printfromtable gBRNPreventionStringIds
	waitmessage 0x40
	return

BattleScript_PRLZPrevention::
	pause 0x20
	printfromtable gPRLZPreventionStringIds
	waitmessage 0x40
	return

BattleScript_PSNPrevention::
	pause 0x20
	printfromtable gPSNPreventionStringIds
	waitmessage 0x40
	return

@use for oblivious & unaware extra effect prevention  was oblivious attraction prevention
BattleScript_AbilityPreventsMoodShift::
	pause 0x20
	printstring STRINGID_PKMNIGNOREDADVANCESWITH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_FlinchPrevention::
	pause 0x20
	printstring STRINGID_PKMNSXPREVENTSFLINCHING
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_OwnTempoPrevents::
	pause 0x20
	printstring STRINGID_PKMNPREVENTSCONFUSIONWITH
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_SoundproofProtected::
	attackstring
	ppreduce
	pause 0x20
	printstring STRINGID_PKMNSXBLOCKSY
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_DazzlingProtected::
	attackstring
	ppreduce
	pause 0x20	
	printstring STRINGID_POKEMONCANNOTUSEMOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_IceFaceNullsDamage::
	attackstring
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	call BattleScript_TargetFormChangeWithString
	goto BattleScript_MoveEnd

BattleScript_DarkTypePreventsPrankster::
	attackstring
	ppreduce
	pause B_WAIT_TIME_SHORT
	printstring STRINGID_ITDOESNTAFFECT
	waitmessage B_WAIT_TIME_LONG
	orhalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	goto BattleScript_MoveEnd

BattleScript_TargetFormChangeWithString::
	@pause 5
	@ call BattleScript_AbilityPopUpTarget
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	handleformchange BS_TARGET, 0
	handleformchange BS_TARGET, 1
	playanimation BS_TARGET, B_ANIM_FORM_CHANGE, NULL
	waitanimation
	handleformchange BS_TARGET, 2
	printstring STRINGID_PKMNTRANSFORMED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_MoveUsedPsychicTerrainPrevents::
	printstring STRINGID_POKEMONCANNOTUSEMOVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_GrassyTerrainHeals::
	setbyte gBattleCommunication, 0
BattleScript_GrassyTerrainLoop:
	copyarraywithindex gBattlerAttacker, gBattlerByTurnOrder, gBattleCommunication, 0x1
	checkgrassyterrainheal BS_ATTACKER, BattleScript_GrassyTerrainLoopIncrement
	printstring STRINGID_GRASSYTERRAINHEALS
	waitmessage 0x40
BattleScript_GrassyTerrainHpChange:
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
BattleScript_GrassyTerrainLoopIncrement::
	addbyte gBattleCommunication, 0x1
	jumpifbytenotequal gBattleCommunication, gBattlersCount, BattleScript_GrassyTerrainLoop
BattleScript_GrassyTerrainLoopEnd::
	bicword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	jumpifbyte CMP_EQUAL, gFieldTimers + 5, 0x0, BattleScript_GrassyTerrainEnds
	end2

BattleScript_AbilityNoSpecificStatLoss::
	pause 0x20
	printstring STRINGID_PKMNSXPREVENTSYLOSS
	waitmessage 0x40
	setbyte cMULTISTRING_CHOOSER, 3
	return

BattleScript_StickyHoldActivates::
	pause 0x20
	printstring STRINGID_PKMNSXMADEYINEFFECTIVE
	waitmessage 0x40
	goto BattleScript_MoveEnd

BattleScript_ColorChangeActivates::
	printstring STRINGID_PKMNCHANGEDTYPEWITH
	waitmessage 0x40
	return

BattleScript_ProteanActivates::	
	printstring STRINGID_PKMNCHANGEDTYPE
	waitmessage 0x40
	return

BattleScript_CursedBodyActivates::	
	printstring STRINGID_CUSEDBODYDISABLED
	waitmessage 0x40
	return

BattleScript_MummyActivates::	
	printstring STRINGID_ATTACKERACQUIREDABILITY
	waitmessage 0x40
	return

@check later make sure timing & effect works
@actually everythiing in if may be irrelevent and only there for popups
BattleScript_WanderingSpiritActivates::
	.if B_ABILITY_POP_UP == TRUE
	@setbyte sFIXED_ABILITY_POPUP, TRUE
	sethword sABILITY_OVERWRITE, ABILITY_WANDERING_SPIRIT
	@showabilitypopup BS_TARGET
	@pause 60
	sethword sABILITY_OVERWRITE, 0
	@updateabilitypopup BS_TARGET
	@pause 20
	@destroyabilitypopup
	@pause 40

	@setbyte sFIXED_ABILITY_POPUP, TRUE
	copyhword sABILITY_OVERWRITE, gLastUsedAbility
	@showabilitypopup BS_ATTACKER
	@pause 60
	sethword sABILITY_OVERWRITE, 0
	@updateabilitypopup BS_ATTACKER
	@pause 20
	@destroyabilitypopup
	@pause 40
.endif
	printstring STRINGID_SWAPPEDABILITIES
	waitmessage B_WAIT_TIME_LONG
	switchinabilities BS_ATTACKER
	switchinabilities BS_TARGET
	return

BattleScript_TargetsStatWasMaxedOut::
	@call BattleScript_AbilityPopUp
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETSSTATWASMAXEDOUT
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BattlerAbilityStatRaiseOnSwitchIn::
	copybyte gBattlerAbility, gBattlerAttacker
	@call BattleScript_AbilityPopUp
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_BATTLERABILITYRAISEDSTAT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_TargetAbilityStatRaiseOnMoveEnd::
	@call BattleScript_AbilityPopUp
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_ABILITYRAISEDSTATDRASTICALLY
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_ScriptingAbilityStatRaise::
	copybyte gBattlerAbility, sBATTLER
	@ @ call BattleScript_AbilityPopUp
	copybyte sSAVED_DMG, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	statbuffchange STAT_CHANGE_NOT_PROTECT_AFFECTED | MOVE_EFFECT_CERTAIN, NULL
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage 0x40
	copybyte gBattlerAttacker, sSAVED_DMG
	return

BattleScript_WeakArmorActivates::	
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_WeakArmorActivatesSpeed
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 0x2, BattleScript_WeakArmorDefAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_WeakArmorActivatesSpeed
	pause 0x10
	printfromtable gStatDownStringIds
	waitmessage 0x40
	goto BattleScript_WeakArmorActivatesSpeed
BattleScript_WeakArmorDefAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATLOWER
	waitmessage 0x40
BattleScript_WeakArmorActivatesSpeed:
	setstatchanger STAT_SPEED, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_WeakArmorActivatesEnd
	jumpifbyte CMP_LESS_THAN, cMULTISTRING_CHOOSER, 0x2, BattleScript_WeakArmorSpeedAnim
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x3, BattleScript_WeakArmorActivatesEnd
	pause 0x10
	printstring STRINGID_TARGETSTATWONTGOHIGHER
	waitmessage 0x40
	goto BattleScript_WeakArmorActivatesEnd
BattleScript_WeakArmorSpeedAnim:
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printstring STRINGID_TARGETABILITYSTATRAISE
	waitmessage 0x40
BattleScript_WeakArmorActivatesEnd:
	return

BattleScript_FellStingerRaisesStat::
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_FellStingerRaisesAtkEnd
	jumpifbyte CMP_GREATER_THAN, cMULTISTRING_CHOOSER, 0x1, BattleScript_FellStingerRaisesAtkEnd
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage 0x40
BattleScript_FellStingerRaisesAtkEnd:
	return

BattleScript_AttackerAbilityStatRaise::
	copybyte gBattlerAbility, gBattlerAttacker
	@ @ call BattleScript_AbilityPopUp
	setgraphicalstatchangevalues
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	waitanimation
	printstring STRINGID_ATTACKERABILITYSTATRAISE
	waitmessage 0x40
	return

BattleScript_AttackerAbilityStatRaiseEnd3::
	call BattleScript_AttackerAbilityStatRaise
	end3

BattleScript_TotemFlaredToLife::
	playanimation BS_ATTACKER, B_ANIM_TOTEM_FLARE, NULL
	printstring STRINGID_AURAFLAREDTOLIFE
	waitmessage 0x40
	goto BattleScript_ApplyTotemVarBoost

BattleScript_TotemVar::
	gettotemboost BattleScript_ApplyTotemVarBoost
BattleScript_TotemVarEnd:
	end2
BattleScript_ApplyTotemVarBoost:
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TotemVarEnd
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
BattleScript_TotemVarPrintStatMsg:
	printfromtable gStatUpStringIds
	waitmessage 0x40
	goto BattleScript_TotemVar  @loop until stats bitfield is empty

@BattleScript_FriskMsgWithPopup::
@	copybyte gBattlerAbility, gBattlerAttacker	
BattleScript_FriskMsg::
	printstring STRINGID_FRISKACTIVATES
	waitmessage 0x40
	return
	
BattleScript_FriskActivates::
	tryfriskmsg BS_ATTACKER
	end3

BattleScript_ImposterActivates::
	transformdataexecution	
	playmoveanimation BS_ATTACKER, MOVE_TRANSFORM
	waitanimation
	printstring STRINGID_IMPOSTERTRANSFORM
	waitmessage 0x40
	end3

BattleScript_RoughSkinActivates::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITHABILITY
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
	return
	
BattleScript_EmpathicCurseActivates::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_EMPATHIC_CURSE_ACTIVATES
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, 0, NULL
	return

BattleScript_RockyHelmetActivates::
	@ don''t play the animation for a fainted mon
	jumpifabsent BS_TARGET, BattleScript_RockyHelmetActivatesDmg
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
BattleScript_RockyHelmetActivatesDmg:
	call BattleScript_HurtAttacker
	return

BattleScript_HurtAttacker:
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH2
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, FALSE, NULL
	return

BattleScript_SetSpikesfromSpikyShield::
	trysetspikes BattleScript_LearnMoveReturn	@using this as an attempt to end script without text/effects should just return from call if failed
	@attackanimation	@may swap to just playanimation 
	playanimation BS_ATTACKER, B_ANIM_SPIKE_TOSS, NULL
	waitanimation
	printstring STRINGID_SPIKESSCATTERED
	waitmessage 0x40 @yeah need to use playanimation using attackanimation just replays the enemies last useed move, but it does appear to work.
	return

BattleScript_SpikyShieldEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH2
	waitmessage 0x40
	call BattleScript_SetSpikesfromSpikyShield @attempts to set spikes unsure if should put before or after tryfaintmon
	tryfaintmon BS_ATTACKER, FALSE, NULL	@will keep above faintmon, since spike script needs target, it works without causing issue that way
	return

BattleScript_ShieldBash::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	typecalc
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_PKMNHURTSWITH2 @make new string  "mon countered the blow!"
	waitmessage 0x40
	tryfaintmon BS_ATTACKER, FALSE, NULL
	return

BattleScript_KingsShieldEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect 0
	copybyte sBATTLER, gBattlerTarget
	copybyte gBattlerTarget, gBattlerAttacker
	copybyte gBattlerAttacker, sBATTLER
	return

BattleScript_BanefulBunkerEffect::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	bichalfword gMoveResultFlags, MOVE_RESULT_NO_EFFECT
	seteffectsecondary
	setmoveeffect 0
	return

BattleScript_EffectShellSideArm:
	shellsidearmcheck
	setmoveeffect MOVE_EFFECT_POISON
	goto BattleScript_EffectHit

BattleScript_EffectPhotonGeyser:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	photongeysercheck
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setmoveeffectwithchance
	tryfaintmon BS_TARGET, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectAuraWheel: @ Aura Wheel can only be used by Morpeko
	jumpifspecies BS_ATTACKER, SPECIES_MORPEKO, BattleScript_EffectSpeedUpHit
	jumpifspecies BS_ATTACKER, SPECIES_MORPEKO_HANGRY, BattleScript_EffectSpeedUpHit
	printstring STRINGID_BUTPOKEMONCANTUSETHEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectClangorousSoul:
	attackcanceler
	attackstring
	ppreduce
	cutonethirdhpraisestats BattleScript_ButItFailed
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_SKIP_DMG_TRACK | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	attackanimation
	waitanimation
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	call BattleScript_AllStatsUp
	goto BattleScript_MoveEnd

BattleScript_EffectOctolock:
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	setoctolock BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	printstring STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_OctolockEndTurn::
	setbyte sSTAT_ANIM_PLAYED, FALSE
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_DEF, MIN_STAT_STAGE, BattleScript_OctolockLowerDef
	jumpifstat BS_TARGET, CMP_GREATER_THAN, STAT_SPDEF, MIN_STAT_STAGE, BattleScript_OctolockTryLowerSpDef
	goto BattleScript_OctolockEnd2
BattleScript_OctolockLowerDef:
	jumpifability BS_TARGET, ABILITY_BIG_PECKS, BattleScript_OctolockTryLowerSpDef
	playstatchangeanimation BS_ATTACKER, BIT_DEF | BIT_SPDEF, STAT_CHANGE_STAT_NEGATIVE
	setbyte sSTAT_ANIM_PLAYED, TRUE
	setstatchanger STAT_DEF, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_OctolockTryLowerSpDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_OctolockTryLowerSpDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctolockTryLowerSpDef:
	jumpifbyte CMP_EQUAL, sSTAT_ANIM_PLAYED, TRUE, BattleScript_OctolockSkipSpDefAnim
	playstatchangeanimation BS_ATTACKER, BIT_SPDEF, STAT_CHANGE_STAT_NEGATIVE
BattleScript_OctolockSkipSpDefAnim:
	setstatchanger STAT_SPDEF, 1, TRUE
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_OctolockEnd2
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_DECREASE, BattleScript_OctolockEnd2
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_OctolockEnd2::
	end2

BattleScript_EffectPoltergeist:
	attackcanceler
	attackstring
	ppreduce
	checkpoltergeist BS_TARGET, BattleScript_ButItFailed
	printstring STRINGID_ABOUTTOUSEPOLTERGEIST
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_HitFromCritCalc

BattleScript_EffectTarShot:
	attackcanceler
	jumpifsubstituteblocks BattleScript_ButItFailedAtkStringPpReduce
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	cantarshotwork BS_TARGET, BattleScript_ButItFailedAtkStringPpReduce
	attackstring
	ppreduce
	setstatchanger STAT_SPEED, 1, TRUE
	attackanimation
	waitanimation
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_TryTarShot
	setgraphicalstatchangevalues
	playanimation BS_TARGET, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatDownStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_TryTarShot:
	trytarshot BS_TARGET, BattleScript_MoveEnd
	printstring STRINGID_PKMNBECAMEWEAKERTOFIRE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectNoRetreat:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	trynoretreat BS_TARGET, BattleScript_ButItFailed
	attackanimation
	waitanimation
	call BattleScript_AllStatsUp
	jumpifstatus2 BS_TARGET, STATUS2_ESCAPE_PREVENTION, BattleScript_MoveEnd
	setmoveeffect MOVE_EFFECT_PREVENT_ESCAPE
	seteffectprimary
	printstring STRINGID_CANTESCAPEDUETOUSEDMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectJawLock:
	setmoveeffect MOVE_EFFECT_TRAP_BOTH | MOVE_EFFECT_CERTAIN
	goto BattleScript_EffectHit

BattleScript_BothCanNoLongerEscape::
	printstring STRINGID_BOTHCANNOLONGERESCAPE
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectHyperspaceFury:
	jumpifspecies BS_ATTACKER, SPECIES_HOOPA_UNBOUND, BattleScript_EffectHyperspaceFuryUnbound
	jumpifspecies BS_ATTACKER, SPECIES_HOOPA, BattleScript_ButHoopaCantUseIt
	printstring STRINGID_BUTPOKEMONCANTUSETHEMOVE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectHyperspaceFuryUnbound::
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	pause B_WAIT_TIME_LONG
	ppreduce
	setmoveeffect MOVE_EFFECT_FEINT
	setmoveeffectwithchance
	setmoveeffect MOVE_EFFECT_DEF_MINUS_1 | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	goto BattleScript_HitFromCritCalc

BattleScript_ButHoopaCantUseIt:
	printstring STRINGID_BUTHOOPACANTUSEIT
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_HyperspaceFuryRemoveProtect::
	printstring STRINGID_BROKETHROUGHPROTECTION
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_EffectPlasmaFists:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setmoveeffectwithchance
	tryfaintmon BS_TARGET, FALSE, NULL
	applyplasmafists
	printstring STRINGID_IONDELUGEON
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSparklySwirl:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET, FALSE, NULL
	healpartystatus
	waitstate
	updatestatusicon BS_ATTACKER_WITH_PARTNER
	waitstate
	goto BattleScript_MoveEnd

BattleScript_EffectFreezyFrost:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET, FALSE, NULL
	normalisebuffs
	printstring STRINGID_STATCHANGESGONE
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectSappySeed:
	jumpifstatus3 BS_TARGET, STATUS3_LEECHSEED, BattleScript_EffectHit
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET, FALSE, NULL
	jumpifhasnohp BS_TARGET, BattleScript_MoveEnd
	setseeded
	printfromtable gLeechSeedStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectBaddyBad:
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_REFLECT, BattleScript_EffectHit
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET, FALSE, NULL
	setreflect
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectGlitzyGlow:
	jumpifsideaffecting BS_ATTACKER, SIDE_STATUS_LIGHTSCREEN, BattleScript_EffectHit
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_TARGET, FALSE, NULL
	setlightscreen
	printfromtable gReflectLightScreenSafeguardStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectDoubleIronBash:
	attackcanceler
	goto BattleScript_MultiHitFromAtkString

BattleScript_EffectEvasionUpHit:
	setmoveeffect MOVE_EFFECT_EVS_PLUS_1 | MOVE_EFFECT_AFFECTS_USER
	goto BattleScript_EffectHit

BattleScript_MicleBerryActivateEnd2::
	@jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_MicleBerryActivateEnd2_Ripen
	goto BattleScript_MicleBerryActivateEnd2_Anim
BattleScript_MicleBerryActivateEnd2_Ripen:
	@ call BattleScript_AbilityPopUp
BattleScript_MicleBerryActivateEnd2_Anim:
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_MICLEBERRYACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	end2

BattleScript_MicleBerryActivateRet::
	@jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_MicleBerryActivateRet_Ripen
	goto BattleScript_MicleBerryActivateRet_Anim
BattleScript_MicleBerryActivateRet_Ripen:
	@ call BattleScript_AbilityPopUp
BattleScript_MicleBerryActivateRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_MICLEBERRYACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	return

BattleScript_JabocaRowapBerryActivates::
	@jumpifability BS_TARGET, ABILITY_RIPEN, BattleScript_JabocaRowapBerryActivate_Ripen
	goto BattleScript_JabocaRowapBerryActivate_Anim
BattleScript_JabocaRowapBerryActivate_Ripen:
	@ call BattleScript_AbilityPopUp
BattleScript_JabocaRowapBerryActivate_Anim:
	jumpifabsent BS_TARGET, BattleScript_JabocaRowapBerryActivate_Dmg   @ dont play the animation for a fainted target
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
BattleScript_JabocaRowapBerryActivate_Dmg:
	call BattleScript_HurtAttacker
	removeitem BS_TARGET
	return

@more berry effects need port from emeraldexpansion

BattleScript_EffectStuffCheeks::
	attackcanceler
	attackstring
	ppreduce
	jumpifnotberry BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
BattleScript_StuffCheeksEatBerry:
	setbyte sBERRY_OVERRIDE, TRUE
	orword gHitMarker, HITMARKER_NO_ANIMATIONS
	consumeberry BS_ATTACKER
	bicword gHitMarker, HITMARKER_NO_ANIMATIONS
	setbyte sBERRY_OVERRIDE, FALSE
	setstatchanger STAT_DEF, 2, FALSE
	statbuffchange MOVE_EFFECT_AFFECTS_USER | STAT_CHANGE_BS_PTR, BattleScript_StuffCheeksEnd
	setgraphicalstatchangevalues
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, B_MSG_STAT_WONT_INCREASE, BattleScript_StuffCheeksEnd @ cant raise def
	playanimation BS_ATTACKER, B_ANIM_STATS_CHANGE, sB_ANIM_ARG1
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_StuffCheeksEnd:
	goto BattleScript_MoveEnd

BattleScript_EffectDecorate:
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, 12, BattleScript_DecorateBoost
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_SPATK, 12, BattleScript_DecorateBoost
	goto BattleScript_ButItFailed
BattleScript_DecorateBoost:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_SPATK, 0x0
	setstatchanger STAT_ATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_DecorateBoostSpAtk
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_DecorateBoostSpAtk
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_DecorateBoostSpAtk:
	setstatchanger STAT_SPATK, 2, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectRemoveTerrain:
	attackcanceler
	attackstring
	ppreduce
	jumpifword CMP_NO_COMMON_BITS, gFieldStatuses, STATUS_FIELD_TERRAIN_ANY, BattleScript_ButItFailed
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	removeterrain
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 4, BattleScript_MoveEnd
	printfromtable gTerrainEndingStringIds
	waitmessage B_WAIT_TIME_LONG
	playanimation BS_ATTACKER, B_ANIM_RESTORE_BG, NULL	@guessing don''t know what last value should be
	tryfaintmon BS_TARGET, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_EffectCoaching:
	attackcanceler
	attackstring
	ppreduce
	jumpifnoally BS_ATTACKER, BattleScript_ButItFailed
	copybyte gBattlerTarget, gBattlerAttacker
	setallytonexttarget EffectCoaching_CheckAllyStats
	goto BattleScript_ButItFailed
EffectCoaching_CheckAllyStats:
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_ATK, MAX_STAT_STAGE, BattleScript_CoachingWorks
	jumpifstat BS_TARGET, CMP_NOT_EQUAL, STAT_DEF, MAX_STAT_STAGE, BattleScript_CoachingWorks
	goto BattleScript_ButItFailed   @ ally at max atk, def
BattleScript_CoachingWorks:
	attackanimation
	waitanimation
	setbyte sSTAT_ANIM_PLAYED, FALSE
	playstatchangeanimation BS_TARGET, BIT_ATK | BIT_DEF, 0x0
	setstatchanger STAT_ATK, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_CoachingBoostDef
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_CoachingBoostDef
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
BattleScript_CoachingBoostDef:
	setstatchanger STAT_DEF, 1, FALSE
	statbuffchange STAT_CHANGE_BS_PTR | STAT_CHANGE_NOT_PROTECT_AFFECTED, BattleScript_MoveEnd
	jumpifbyte CMP_EQUAL, cMULTISTRING_CHOOSER, 0x2, BattleScript_MoveEnd
	printfromtable gStatUpStringIds
	waitmessage B_WAIT_TIME_LONG
	goto BattleScript_MoveEnd

BattleScript_EffectJungleHealing:
	attackcanceler
	attackstring
	ppreduce
	jumpifteamhealthy BS_ATTACKER, BattleScript_ButItFailed
	attackanimation
	waitanimation
	copybyte gBattlerTarget, gBattlerAttacker
	setbyte gBattleCommunication, 0
JungleHealing_RestoreTargetHealth:
	copybyte gBattlerAttacker, gBattlerTarget
	tryhealquarterhealth BS_TARGET, BattleScript_JungleHealing_TryCureStatus
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	printstring STRINGID_PKMNREGAINEDHEALTH
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealing_TryCureStatus:
	jumpifmove MOVE_LIFE_DEW, BattleScript_JungleHealingTryRestoreAlly  @ life dew only heals
	jumpifstatus BS_TARGET, STATUS1_ANY, BattleScript_JungleHealingCureStatus
	goto BattleScript_JungleHealingTryRestoreAlly
BattleScript_JungleHealingCureStatus:
	curestatus BS_TARGET
	updatestatusicon BS_TARGET
	printstring STRINGID_PKMNSTATUSNORMAL
	waitmessage B_WAIT_TIME_LONG
BattleScript_JungleHealingTryRestoreAlly:
	jumpifbyte CMP_NOT_EQUAL, gBattleCommunication, 0x0, BattleScript_MoveEnd
	addbyte gBattleCommunication, 1
	jumpifnoally BS_TARGET, BattleScript_MoveEnd
	setallytonexttarget JungleHealing_RestoreTargetHealth
	goto BattleScript_MoveEnd

BattleScript_CuteCharmActivates::
	status2animation BS_ATTACKER, STATUS2_INFATUATION
	printstring STRINGID_PKMNSXINFATUATEDY
	waitmessage 0x40
	return
	
BattleScript_CupidsArrowActivates::
	status2animation BS_TARGET, STATUS2_INFATUATION
	printstring STRINGID_CUPIDSARROWSTRUCK
	waitmessage 0x40
	return

BattleScript_GooeyActivates::
	waitstate
	@call BattleScript_AbilityPopUp
	swapattackerwithtarget  @ for defiant, mirror armor
	seteffectsecondary
	return

BattleScript_BattleBondActivatesOnMoveEndAttacker::
	pause 5
	copybyte gBattlerAbility, gBattlerAttacker
	@@ call BattleScript_AbilityPopUp
	printstring STRINGID_ATTACKERBECAMEFULLYCHARGED
	handleformchange BS_ATTACKER, 0
	handleformchange BS_ATTACKER, 1
	playanimation BS_ATTACKER, B_ANIM_FORM_CHANGE, NULL @guessing don''t know what value should be
	waitanimation
	handleformchange BS_ATTACKER, 2
	printstring STRINGID_ATTACKERBECAMEASHSPECIES
	return

BattleScript_EffectRelicSong:
	setmoveeffect MOVE_EFFECT_RELIC_SONG | MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN
	attackcanceler
	accuracycheck BattleScript_PrintMoveMissed, ACC_CURR_MOVE
	attackstring
	ppreduce
	critcalc
	damagecalc
	typecalc
	adjustnormaldamage
	pause 0x01
	attackanimation
	waitanimation
	effectivenesssound
	hitanimation BS_TARGET
	waitstate
	healthbarupdate BS_TARGET
	datahpupdate BS_TARGET
	critmessage
	waitmessage B_WAIT_TIME_LONG
	resultmessage
	waitmessage B_WAIT_TIME_LONG
	setmoveeffectwithchance
	argumentstatuseffect
	tryfaintmon BS_TARGET, FALSE, NULL
	goto BattleScript_MoveEnd

BattleScript_DancerActivates::	
	waitmessage 0x20
	setbyte sB_ANIM_TURN, 0x0
	setbyte sB_ANIM_TARGETS_HIT, 0x0
	orword gHitMarker, HITMARKER_ALLOW_NO_PP
	jumptocalledmove TRUE

BattleScript_Pickpocket::
	@@ call BattleScript_AbilityPopUp
	jumpifability BS_ATTACKER, ABILITY_STICKY_HOLD, BattleScript_PickpocketPrevented
	swapattackerwithtarget
	call BattleScript_ItemSteal
	swapattackerwithtarget
	activateitemeffects BS_TARGET
	return

BattleScript_PickpocketPrevented:
	pause B_WAIT_TIME_SHORT
	copybyte gBattlerAbility, gBattlerAttacker
	@@ call BattleScript_AbilityPopUp
	printstring STRINGID_ITEMCANNOTBEREMOVED
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_StickyBarbTransfer::
	playanimation BS_TARGET, B_ANIM_ITEM_STEAL, NULL
	printstring STRINGID_STICKYBARBTRANSFER
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_RedCardActivates::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_REDCARDACTIVATE
	waitmessage B_WAIT_TIME_LONG
	swapattackerwithtarget
	jumpifstatus3 BS_EFFECT_BATTLER, STATUS3_ROOTED, BattleScript_RedCardIngrain
	jumpifability BS_EFFECT_BATTLER, ABILITY_SUCTION_CUPS, BattleScript_RedCardSuctionCups
	setbyte sSWITCH_CASE, B_SWITCH_RED_CARD
	forcerandomswitch BattleScript_RedCardEnd
	@ changes the current battle script. the rest happens in BattleScript_RoarSuccessSwitch_Ret, if switch is successful
BattleScript_RedCardEnd:
	return
BattleScript_RedCardIngrain:
	printstring STRINGID_PKMNANCHOREDITSELF
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	swapattackerwithtarget
	return
BattleScript_RedCardSuctionCups:
	printstring STRINGID_PKMNANCHORSITSELFWITH
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	swapattackerwithtarget
	return

BattleScript_ApplySecondaryEffect::
	waitstate
	seteffectsecondary
	return

BattleScript_BufferEndTurn::
	printstring STRINGID_BUFFERENDS
	waitmessage 0x40
	end2

BattleScript_SynchronizeActivates::
	waitstate
	seteffectprimary
	return

BattleScript_AbilityCuredStatus::
	printstring STRINGID_PKMNSXCUREDITSYPROBLEM
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	return

BattleScript_IgnoresWhileAsleep::
	printstring STRINGID_PKMNIGNORESASLEEP
	waitmessage 0x40
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_IgnoresAndUsesRandomMove::
	printstring STRINGID_PKMNIGNOREDORDERS
	waitmessage B_WAIT_TIME_LONG
	jumptocalledmove FALSE
	printfromtable gInobedientStringIds
	waitmessage B_WAIT_TIME_LONG
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_PanickedAndUsesRandomMove::
	printstring STRINGID_PKMNPANICKED
	waitmessage B_WAIT_TIME_LONG
	jumptocalledmove FALSE
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_BindDoCalledMove::
	jumptocalledmove FALSE
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_MoveUsedLoafingAround::
	printfromtable gInobedientStringIds
	waitmessage B_WAIT_TIME_LONG
	jumpifnotfullhp	BS_ATTACKER, BattleScript_Healing
BattleScript_TruantHealing::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE	@putting this here would otherwise do nothing, but since trunt has health change it would heal
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_HealAnimation::
	playanimation BS_ATTACKER, B_ANIM_BASIC_HEAL, NULL
	return

BattleScript_TargetHealAnimation::
	playanimation BS_TARGET, B_ANIM_BASIC_HEAL, NULL
	return

BattleScript_Healing::
	playanimation BS_ATTACKER, B_ANIM_BASIC_HEAL, NULL
	goto BattleScript_TruantHealing

BattleScript_SleepHealing::
	printstring STRINGID_WELLRESTED
	waitmessage 0x40
	playanimation BS_ATTACKER, B_ANIM_BASIC_HEAL, NULL
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	end2

BattleScript_IgnoresAndFallsAsleep::
	printstring STRINGID_PKMNBEGANTONAP
	waitmessage 0x40
	setmoveeffect MOVE_EFFECT_SLEEP | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	moveendto MOVE_END_NEXT_TARGET
	end

BattleScript_IgnoresAndHitsItself::
	printstring STRINGID_PKMNWONTOBEY
	waitmessage 0x40
	goto BattleScript_DoSelfConfusionDmg

BattleScript_SubstituteFade::
	playanimation BS_TARGET, B_ANIM_SUBSTITUTE_FADE, NULL
	printstring STRINGID_PKMNSUBSTITUTEFADED
	return

BattleScript_BerryCurePrlzEnd2::
	call BattleScript_BerryCureParRet
	end2

BattleScript_BerryCureParRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMCUREDPARALYSIS
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCurePsnEnd2::
	call BattleScript_BerryCurePsnRet
	end2

BattleScript_BerryCurePsnRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMCUREDPOISON
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureBrnEnd2::
	call BattleScript_BerryCureBrnRet
	end2

BattleScript_BerryCureBrnRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMHEALEDBURN
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureFrzEnd2::
	call BattleScript_BerryCureFrzRet
	end2

BattleScript_BerryCureFrzRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMDEFROSTEDIT
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureSlpEnd2::
	call BattleScript_BerryCureSlpRet
	end2

BattleScript_BerryCureSlpRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMWOKEIT
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_GemActivates::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
	printstring STRINGID_GEMACTIVATES
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_ATTACKER
	return

BattleScript_BerryReduceDmg::
	playanimation BS_TARGET, B_ANIM_ITEM_EFFECT, NULL
	waitanimation
	printstring STRINGID_TARGETATEITEM
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_PrintBerryReduceString::
	waitmessage B_WAIT_TIME_LONG
	printstring STRINGID_BERRYDMGREDUCES
	waitmessage B_WAIT_TIME_LONG
	return

BattleScript_BerryCureConfusionEnd2::
	call BattleScript_BerryCureConfusionRet
	end2

BattleScript_BerryCureConfusionRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMSNAPPEDOUT
	waitmessage 0x40
	removeitem BS_SCRIPTING
	return

BattleScript_BerryCureChosenStatusEnd2::
	call BattleScript_BerryCureChosenStatusRet
	end2

BattleScript_BerryCureChosenStatusRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printfromtable gBerryEffectStringIds
	waitmessage 0x40
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_MentalHerbCureRet::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printfromtable gMentalHerbCureStringIds
	waitmessage B_WAIT_TIME_LONG
	updatestatusicon BS_SCRIPTING
	removeitem BS_SCRIPTING
	copybyte gBattlerAttacker, sSAVED_BATTLER   @ restore the original attacker just to be safe
	return

BattleScript_MentalHerbCureEnd2::
	call BattleScript_MentalHerbCureRet
	end2

BattleScript_WhiteHerbEnd2::
	call BattleScript_WhiteHerbRet
	end2

BattleScript_WhiteHerbRet::
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDSTATUS
	waitmessage 0x40
	removeitem BS_SCRIPTING
	return

BattleScript_BerryConfuseHealRet::
	@jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryConfuseHealRet_AbilityPopup
	goto BattleScript_BerryConfuseHealRet_Anim
BattleScript_BerryConfuseHealRet_AbilityPopup:
	@ call BattleScript_AbilityPopUp
BattleScript_BerryConfuseHealRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	printstring STRINGID_FORXCOMMAYZ
	waitmessage B_WAIT_TIME_LONG
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_CERTAIN
	seteffectprimary
	removeitem BS_TARGET
	return

BattleScript_ItemHealHP_RemoveItemRet::
	@jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp
	goto BattleScript_ItemHealHP_RemoveItemRet_Anim
BattleScript_ItemHealHP_RemoveItemRet_AbilityPopUp:
	@ call BattleScript_AbilityPopUp
BattleScript_ItemHealHP_RemoveItemRet_Anim:
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage B_WAIT_TIME_LONG
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_SCRIPTING
	datahpupdate BS_SCRIPTING
	removeitem BS_SCRIPTING
	return

BattleScript_ItemHealHP_RemoveItem::
	@jumpifability BS_ATTACKER, ABILITY_RIPEN, BattleScript_ItemHealHP_RemoveItemEnd2_AbilityPopUp
	goto BattleScript_ItemHealHP_RemoveItemEnd2_Anim
BattleScript_ItemHealHP_RemoveItemEnd2_AbilityPopUp:
	@ call BattleScript_AbilityPopUp
BattleScript_ItemHealHP_RemoveItemEnd2_Anim:
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage 0x40
	orword gHitMarker, HITMARKER_SKIP_DMG_TRACK | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	removeitem BS_ATTACKER
	end2

BattleScript_BerryPPHealEnd2::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDPP
	waitmessage 0x40
	removeitem BS_ATTACKER
	end2

BattleScript_ItemHealHP_End2::
	call BattleScript_ItemHealHP_Ret
	end2

BattleScript_InBattlePickup::
	printstring STRINGID_PICKUP_ITEM
	waitmessage 0x40
	end

BattleScript_ItemHealHP_Ret::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDHPALITTLE
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	return

BattleScript_ItemHurtRet::
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_PASSIVE_DAMAGE | HITMARKER_IGNORE_DISGUISE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_HURTBYITEM
	waitmessage B_WAIT_TIME_LONG
	tryfaintmon BS_ATTACKER, FALSE, NULL
	return

BattleScript_ItemHurtEnd2::
	playanimation BS_ATTACKER, B_ANIM_MON_HIT, NULL
	waitanimation
	call BattleScript_ItemHurtRet
	end2

BattleScript_AirBaloonMsgIn::
	printstring STRINGID_AIRBALLOONFLOAT
	waitmessage B_WAIT_TIME_LONG
	end3

BattleScript_AirBaloonMsgPop::
	printstring STRINGID_AIRBALLOONPOP
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_TARGET
	return

BattleScript_SelectingNotAllowedMoveChoiceItem::
	printselectionstring STRINGID_ITEMALLOWSONLYYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveGorillaTactics::
	printselectionstring STRINGID_ABILITYALLOWSONLYMOVE
	endselectionscript

BattleScript_SelectingNotAllowedMoveAssaultVest::
	printselectionstring STRINGID_ASSAULTVESTDOESNTALLOW
	endselectionscript

BattleScript_HangedOnMsg::
	playanimation BS_TARGET, B_ANIM_HANGED_ON, NULL
	printstring STRINGID_PKMNHUNGONWITHX
	waitmessage 0x40
	return

BattleScript_BerryConfuseHealEnd2::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNSITEMRESTOREDHEALTH
	waitmessage 0x40
	orword gHitMarker, HITMARKER_IGNORE_SUBSTITUTE
	healthbarupdate BS_ATTACKER
	datahpupdate BS_ATTACKER
	printstring STRINGID_FORXCOMMAYZ
	waitmessage 0x40
	setmoveeffect MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER
	seteffectprimary
	removeitem BS_ATTACKER
	end2

BattleScript_BerryStatRaiseEnd2::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	statbuffchange STAT_CHANGE_BS_PTR | MOVE_EFFECT_AFFECTS_USER, .+4
	setbyte cMULTISTRING_CHOOSER, 4
	call BattleScript_StatUp
	removeitem BS_ATTACKER
	end2

BattleScript_BerryStatRaiseRet::
	@jumpifability BS_SCRIPTING, ABILITY_RIPEN, BattleScript_BerryStatRaiseRet_AbilityPopup
	@goto BattleScript_BerryStatRaiseRet_Anim
BattleScript_BerryStatRaiseRet_Anim:
	statbuffchange STAT_CHANGE_BS_PTR, BattleScript_BerryStatRaiseRet_End
	setgraphicalstatchangevalues
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, sB_ANIM_ARG1
	setbyte cMULTISTRING_CHOOSER, B_MSG_STAT_ROSE_ITEM
	call BattleScript_StatUp
	removeitem BS_SCRIPTING
BattleScript_BerryStatRaiseRet_End:
	return

BattleScript_BerryFocusEnergyEnd2::
	playanimation BS_ATTACKER, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_PKMNUSEDXTOGETPUMPED
	waitmessage 0x40
	removeitem BS_ATTACKER
	end2

BattleScript_ActionSelectionItemsCantBeUsed::
	printselectionstring STRINGID_ITEMSCANTBEUSEDNOW
	endselectionscript

BattleScript_FlushMessageBox::
	printstring STRINGID_EMPTYSTRING3
	return

BattleScript_EjectButtonActivates::
	makevisible BS_ATTACKER
	playanimation BS_SCRIPTING, B_ANIM_ITEM_EFFECT, NULL
	printstring STRINGID_EJECTBUTTONACTIVATE
	waitmessage B_WAIT_TIME_LONG
	removeitem BS_SCRIPTING
	makeinvisible BS_SCRIPTING
	openpartyscreen BS_SCRIPTING, BattleScript_EjectButtonEnd
	switchoutabilities BS_SCRIPTING
	waitstate
	switchhandleorder BS_SCRIPTING 0x2
	returntoball BS_SCRIPTING
	getswitchedmondata BS_SCRIPTING
	switchindataupdate BS_SCRIPTING
	hpthresholds BS_SCRIPTING
	trytoclearprimalweather
	printstring STRINGID_EMPTYSTRING3
	waitmessage 1
	printstring 0x3
	switchinanim BS_SCRIPTING 0x1
	waitstate
	switchineffects BS_SCRIPTING
BattleScript_EjectButtonEnd:
	return

BattleScript_EjectPackActivate_Ret::
	goto BattleScript_EjectButtonActivates

BattleScript_EjectPackActivate_End2::
	call BattleScript_EjectPackActivate_Ret
	end2

BattleScript_EjectPackActivates::
	jumpifcantswitch BS_SCRIPTING, BattleScript_EjectButtonEnd
	goto BattleScript_EjectPackActivate_Ret
