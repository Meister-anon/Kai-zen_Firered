#ifndef GUARD_BATTLE_ANIM_H
#define GUARD_BATTLE_ANIM_H

#include "battle.h"
#include "data.h"
#include "task.h"
#include "constants/battle_anim.h"

u8 GetBattlerYDelta(u8 battlerId, u16 species);

enum
{
    BG_ANIM_SCREEN_SIZE,
    BG_ANIM_AREA_OVERFLOW_MODE,
    BG_ANIM_MOSAIC,
    BG_ANIM_CHAR_BASE_BLOCK,
    BG_ANIM_PRIORITY,
    BG_ANIM_PALETTES_MODE,
    BG_ANIM_SCREEN_BASE_BLOCK
};

struct BattleAnimBgData
{
    u8 *bgTiles;
    u16 *bgTilemap;
    u8 paletteId;
    u8 bgId;
    u16 tilesOffset;
    u16 unused;
};

struct BattleAnimBackground
{
    const u32 *image;
    const u32 *palette;
    const u32 *tilemap;
};

#define ANIM_ARGS_COUNT 8

// Linear Translation
#define sTransl_Speed    data[0]
#define sTransl_Duration data[0] // for Fast
#define sTransl_InitX    data[1]
#define sTransl_DestX    data[2]
#define sTransl_InitY    data[3]
#define sTransl_DestY    data[4]
#define sTransl_ArcAmpl  data[5]

extern void (*gAnimScriptCallback)(void);
extern bool8 gAnimScriptActive;
extern u8 gAnimVisualTaskCount;
extern u8 gAnimSoundTaskCount;
extern struct DisableStruct *gAnimDisableStructPtr;
extern u16 gAnimMovePower;
extern u8 gAnimFriendship;
extern u16 gWeatherMoveAnim;
extern s16 gBattleAnimArgs[ANIM_ARGS_COUNT];
extern u8 gAnimMoveTurn;
extern u8 gBattleAnimAttacker;
extern u8 gBattleAnimTarget;
extern u8 gBattlerSpriteIds[MAX_BATTLERS_COUNT];
extern s32 gAnimMoveDmg;
extern u16 gAnimBattlerSpecies[MAX_BATTLERS_COUNT];
extern u8 gAnimCustomPanning;
extern u16 gAnimMoveIndex;  //new addition since previously was static...ok I need to look into this, it may not be necessry?

// battle_anim.c
extern const struct OamData gOamData_AffineOff_ObjNormal_8x8;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_64x64;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x8;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x8;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_64x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_8x16;
extern const struct OamData gOamData_AffineOff_ObjNormal_8x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_16x32;
extern const struct OamData gOamData_AffineOff_ObjNormal_32x64;
extern const struct OamData gOamData_AffineNormal_ObjNormal_8x8;
extern const struct OamData gOamData_AffineNormal_ObjNormal_16x16;
extern const struct OamData gOamData_AffineNormal_ObjNormal_32x32;
extern const struct OamData gOamData_AffineNormal_ObjNormal_64x64;
extern const struct OamData gOamData_AffineNormal_ObjNormal_16x8;
extern const struct OamData gOamData_AffineNormal_ObjNormal_32x8;
extern const struct OamData gOamData_AffineNormal_ObjNormal_32x16;
extern const struct OamData gOamData_AffineNormal_ObjNormal_64x32;
extern const struct OamData gOamData_AffineNormal_ObjNormal_8x16;
extern const struct OamData gOamData_AffineNormal_ObjNormal_8x32;
extern const struct OamData gOamData_AffineNormal_ObjNormal_16x32;
extern const struct OamData gOamData_AffineNormal_ObjNormal_32x64;
extern const struct OamData gOamData_AffineDouble_ObjNormal_8x8;
extern const struct OamData gOamData_AffineDouble_ObjNormal_16x16;
extern const struct OamData gOamData_AffineDouble_ObjNormal_32x32;
extern const struct OamData gOamData_AffineDouble_ObjNormal_64x64;
extern const struct OamData gOamData_AffineDouble_ObjNormal_16x8;
extern const struct OamData gOamData_AffineDouble_ObjNormal_32x8;
extern const struct OamData gOamData_AffineDouble_ObjNormal_32x16;
extern const struct OamData gOamData_AffineDouble_ObjNormal_64x32;
extern const struct OamData gOamData_AffineDouble_ObjNormal_8x16;
extern const struct OamData gOamData_AffineDouble_ObjNormal_8x32;
extern const struct OamData gOamData_AffineDouble_ObjNormal_16x32;
extern const struct OamData gOamData_AffineDouble_ObjNormal_32x64;
extern const struct OamData gOamData_AffineOff_ObjBlend_8x8;
extern const struct OamData gOamData_AffineOff_ObjBlend_16x16;
extern const struct OamData gOamData_AffineOff_ObjBlend_32x32;
extern const struct OamData gOamData_AffineOff_ObjBlend_64x64;
extern const struct OamData gOamData_AffineOff_ObjBlend_16x8;
extern const struct OamData gOamData_AffineOff_ObjBlend_32x8;
extern const struct OamData gOamData_AffineOff_ObjBlend_32x16;
extern const struct OamData gOamData_AffineOff_ObjBlend_64x32;
extern const struct OamData gOamData_AffineOff_ObjBlend_8x16;
extern const struct OamData gOamData_AffineOff_ObjBlend_8x32;
extern const struct OamData gOamData_AffineOff_ObjBlend_16x32;
extern const struct OamData gOamData_AffineOff_ObjBlend_32x64;
extern const struct OamData gOamData_AffineNormal_ObjBlend_8x8;
extern const struct OamData gOamData_AffineNormal_ObjBlend_16x16;
extern const struct OamData gOamData_AffineNormal_ObjBlend_32x32;
extern const struct OamData gOamData_AffineNormal_ObjBlend_64x64;
extern const struct OamData gOamData_AffineNormal_ObjBlend_16x8;
extern const struct OamData gOamData_AffineNormal_ObjBlend_32x8;
extern const struct OamData gOamData_AffineNormal_ObjBlend_32x16;
extern const struct OamData gOamData_AffineNormal_ObjBlend_64x32;
extern const struct OamData gOamData_AffineNormal_ObjBlend_8x16;
extern const struct OamData gOamData_AffineNormal_ObjBlend_8x32;
extern const struct OamData gOamData_AffineNormal_ObjBlend_16x32;
extern const struct OamData gOamData_AffineNormal_ObjBlend_32x64;
extern const struct OamData gOamData_AffineDouble_ObjBlend_8x8;
extern const struct OamData gOamData_AffineDouble_ObjBlend_16x16;
extern const struct OamData gOamData_AffineDouble_ObjBlend_32x32;
extern const struct OamData gOamData_AffineDouble_ObjBlend_64x64;
extern const struct OamData gOamData_AffineDouble_ObjBlend_16x8;
extern const struct OamData gOamData_AffineDouble_ObjBlend_32x8;
extern const struct OamData gOamData_AffineDouble_ObjBlend_32x16;
extern const struct OamData gOamData_AffineDouble_ObjBlend_64x32;
extern const struct OamData gOamData_AffineDouble_ObjBlend_8x16;
extern const struct OamData gOamData_AffineDouble_ObjBlend_8x32;
extern const struct OamData gOamData_AffineDouble_ObjBlend_16x32;
extern const struct OamData gOamData_AffineDouble_ObjBlend_32x64;
extern const struct CompressedSpriteSheet gBattleAnimPicTable[];
extern const struct CompressedSpritePalette gBattleAnimPaletteTable[];
void MoveBattlerSpriteToBG(u8 battlerId, u8);
void ResetBattleAnimBg(u8);
void ClearBattleAnimationVars(void);
void DoMoveAnim(u16 move);
void LaunchBattleAnimation(const u8 *const animsTable[], u16 tableId, bool8 isMoveAnim);
void DestroyAnimSprite(struct Sprite *sprite);
void DestroyAnimVisualTask(u8 taskId);
void DestroyAnimSoundTask(u8 taskId);
bool8 IsContest(void);
s8 BattleAnimAdjustPanning(s8 pan);
s8 BattleAnimAdjustPanning2(s8 pan);
s16 CalculatePanIncrement(s16 sourcePan, s16 targetPan, s16 incrementPan);
u8 GetAnimBattlerId(u8 wantedBattler);
bool8 IsBattlerSpriteVisible(u8 battlerId);
s16 KeepPanInRange(s16 a, s32 oldPan);
void RelocateBattleBgPal(u16 paletteNum, u16 *dest, s32 offset, bool8 largeScreen);

// battle_intro.c
void SetAnimBgAttribute(u8 bgId, u8 attributeId, u8 value);
s32 GetAnimBgAttribute(u8 bgId, u8 attributeId);
void HandleIntroSlide(u8 terrain);
void sub_80BC41C(u8 taskId);
void CopyBattlerSpriteToBg(s32 bgId, u8 x, u8 y, u8 battlerPosition, u8 palno, u8 *tilesDest, u16 *tilemapDest, u16 tilesOffset);

// battle_anim_effects_1.c
extern const union AnimCmd *const gMusicNotesAnimTable[];
extern const struct SpriteTemplate gThoughtBubbleSpriteTemplate;
extern const union AnimCmd *const gConversionAnimTable[];
extern const union AffineAnimCmd *const gConversionAffineAnimTable[];
extern const union AnimCmd *const gSporeParticleAnimTable[];
extern const union AnimCmd *const gCuttingSliceAnimTable[];
extern const union AnimCmd *const gRazorLeafParticleAnimTable[];
extern const union AnimCmd *const gSolarbeamBigOrbAnimTable[];
extern const union AnimCmd *const gPowerAbsorptionOrbAnimTable[];
extern const union AffineAnimCmd *const gPowerAbsorptionOrbAffineAnimTable[];
extern const union AnimCmd *const gOctazookaAnimTable[];
extern const union AnimCmd *const gIngrainRootAnimTable[];
extern const union AnimCmd *const gMoonlightSparkleAnimTable[];
extern const union AnimCmd *const gHealingBlueStarAnimTable[];
extern const union AnimCmd *const gPetalDanceBigFlowerAnimTable[];
extern const union AnimCmd *const gPetalDanceSmallFlowerAnimTable[];
extern const union AnimCmd *const gGrantingStarsAnimTable[];
extern const union AffineAnimCmd *const gSwiftStarAffineAnimTable[];
extern const union AnimCmd *const gMetronomeThroughtBubbleAnimTable[];
extern const union AnimCmd *const gEndureEnergyAnimTable[];
extern const union AffineAnimCmd *const gMimicOrbAffineAnimTable[];
extern const union AffineAnimCmd *const gStockpileAbsorptionOrbAffineAnimTable[];
extern const union AnimCmd *const gPowderParticlesAnimTable[];
void AnimNeedleArmSpikeStep(struct Sprite*);
void AnimMovePowderParticle(struct Sprite *);
void AnimPowerAbsorptionOrb(struct Sprite *);
void AnimSolarbeamBigOrb(struct Sprite *);
void AnimSolarbeamSmallOrb(struct Sprite *);
void AnimAbsorptionOrb(struct Sprite *);
void AnimHyperBeamOrb(struct Sprite *);
void AnimSporeParticle(struct Sprite *);
void AnimPetalDanceBigFlower(struct Sprite *);
void AnimPetalDanceSmallFlower(struct Sprite *);
void AnimRazorLeafParticle(struct Sprite *);
void AnimLeechSeed(struct Sprite *);
void AnimTranslateLinearSingleSineWave(struct Sprite *);
void AnimMoveTwisterParticle(struct Sprite *);
void AnimConstrictBinding(struct Sprite *);
void AnimMimicOrb(struct Sprite *);
void AnimIngrainRoot(struct Sprite *);
void AnimFrenzyPlantRoot(struct Sprite *);
void AnimIngrainOrb(struct Sprite *);
void AnimPresent(struct Sprite *);
void AnimKnockOffItem(struct Sprite *);
void AnimPresentHealParticle(struct Sprite *);
void AnimItemSteal(struct Sprite *);
void AnimTrickBag(struct Sprite *);
void AnimFlyingParticle(struct Sprite *);
void AnimNeedleArmSpike(struct Sprite *);
void sub_80A43F8(struct Sprite *);
void AnimWhipHit(struct Sprite *);
void AnimFlickeringPunch(struct Sprite *);
void AnimCuttingSlice(struct Sprite *);
void AnimAirCutterSlice(struct Sprite *);
void AnimCirclingMusicNote(struct Sprite *);
void AnimProtect(struct Sprite *);
void AnimMilkBottle(struct Sprite *);
void AnimGrantingStars(struct Sprite *);
void AnimSparkingStars(struct Sprite *);
void AnimBubbleBurst(struct Sprite *);
void AnimSleepLetterZ(struct Sprite *);
void AnimLockOnTarget(struct Sprite *);
void AnimLockOnMoveTarget(struct Sprite *);
void AnimBowMon(struct Sprite *);
void AnimTipMon(struct Sprite *);
void AnimSlashSlice(struct Sprite *);
void AnimFalseSwipeSlice(struct Sprite *);
void AnimFalseSwipePositionedSlice(struct Sprite *);
void AnimEndureEnergy(struct Sprite *);
void AnimSharpenSphere(struct Sprite *);
void AnimConversion(struct Sprite *);
void AnimConversion2(struct Sprite *);
void AnimMoon(struct Sprite *);
void AnimMoonlightSparkle(struct Sprite *);
void AnimHornHit(struct Sprite *);
void AnimSuperFang(struct Sprite *);
void AnimWavyMusicNotes(struct Sprite *);
void AnimFlyingMusicNotes(struct Sprite *);
void AnimBellyDrumHand(struct Sprite *);
void AnimSlowFlyingMusicNotes(struct Sprite *);
void AnimThoughtBubble(struct Sprite *);
void AnimMetronomeFinger(struct Sprite *);
void AnimFollowMeFinger(struct Sprite *);
void AnimTauntFinger(struct Sprite *);
void SetSpriteNextToMonHead(u8 battler, struct Sprite* sprite);
void AnimTask_ShrinkTargetCopy(u8 taskId);

// battle_anim_effects_2.c
extern const union AffineAnimCmd *const gGrowingRingAffineAnimTable[];
extern const union AnimCmd *const gExplosionAnimTable[];
extern const union AffineAnimCmd *const gThinRingShrinkingAffineAnimTable[];
extern const union AffineAnimCmd *const gThinRingExpandingAffineAnimTable[];
extern const union AffineAnimCmd *const gHyperVoiceRingAffineAnimTable[];
extern const union AffineAnimCmd *const gGuardRingAffineAnimTable[];
extern const union AffineAnimCmd *const gAngerMarkAffineAnimTable[];
extern const union AffineAnimCmd *const gHiddenPowerOrbAffineAnimTable[];
extern const union AffineAnimCmd *const gWaterPulseRingAffineAnimTable[];
extern const union AnimCmd *const gCoinAnimTable[];
extern const union AffineAnimCmd *const gMetronomeFingerAffineAnimTable[];
extern const union AffineAnimCmd *const gAbsorptionOrbAffineAnimTable[];
void AnimCirclingFinger(struct Sprite *);
void AnimBouncingMusicNote(struct Sprite *);
void AnimVibrateBattlerBack(struct Sprite *);
void AnimMovingClamp(struct Sprite *);
void Anim_KinesisZapEnergy(struct Sprite *);
void Anim_SwordsDanceBlade(struct Sprite *);
void AnimSonicBoomProjectile(struct Sprite *);
void AnimAirWaveProjectile(struct Sprite *);
void AnimVoidLines(struct Sprite *);
void AnimCoinThrow(struct Sprite *);
void AnimFallingCoin(struct Sprite *);
void AnimBulletSeed(struct Sprite *);
void AnimRazorWindTornado(struct Sprite *);
void AnimViceGripPincer(struct Sprite *);
void AnimGuillotinePincer(struct Sprite *);
void AnimBreathPuff(struct Sprite *);
void AnimAngerMark(struct Sprite *);
void AnimPencil(struct Sprite *);
void AnimBlendThinRing(struct Sprite *);
void AnimHyperVoiceRing(struct Sprite *);
void AnimUproarRing(struct Sprite *);
void AnimSoftBoiledEgg(struct Sprite *);
void AnimSpeedDust(struct Sprite *);
void AnimHealBellMusicNote(struct Sprite *);
void AnimMagentaHeart(struct Sprite *);
void AnimRedHeartProjectile(struct Sprite *);
void AnimParticuleBurst(struct Sprite *);
void AnimRedHeartRising(struct Sprite *);
void AnimOrbitFast(struct Sprite *);
void AnimOrbitScatter(struct Sprite *);
void AnimSpitUpOrb(struct Sprite *);
void AnimEyeSparkle(struct Sprite *);
void AnimAngel(struct Sprite *);
void AnimPinkHeart(struct Sprite *);
void AnimDevil(struct Sprite *);
void AnimFurySwipes(struct Sprite *);
void AnimMovementWaves(struct Sprite *);
void AnimJaggedMusicNote(struct Sprite *);
void AnimPerishSongMusicNote2(struct Sprite *);
void AnimPerishSongMusicNote(struct Sprite *);
void AnimGuardRing(struct Sprite *);

// battle_anim_effects_3.c
extern const struct SpriteTemplate gWishStarSpriteTemplate;
extern const struct SpriteTemplate gMiniTwinklingStarSpriteTemplate;
extern const union AnimCmd *const gScratchAnimTable[];
extern const union AnimCmd *const gEclipsingOrbAnimTable[];
extern const union AnimCmd *const gOpeningEyeAnimTable[];
extern const union AffineAnimCmd *const gSpotlightAffineAnimTable[]; //table is array, needs brackets
void AnimBlackSmoke(struct Sprite *);
void AnimWhiteHalo(struct Sprite *);
void AnimTealAlert(struct Sprite *);
void AnimMeanLookEye(struct Sprite *);
void AnimSpikes(struct Sprite *);
void AnimLeer(struct Sprite *);
void AnimLetterZ(struct Sprite *);
void AnimFang(struct Sprite *);
void AnimSpotlight(struct Sprite *);
void AnimClappingHand(struct Sprite *);
void AnimClappingHand2(struct Sprite *);
void AnimRapidSpin(struct Sprite *);
void AnimTriAttackTriangle(struct Sprite *);
void AnimBatonPassPokeball(struct Sprite *);
void AnimWishStar(struct Sprite *);
void AnimMiniTwinklingStar(struct Sprite *);
void AnimSwallowBlueOrb(struct Sprite *);
void AnimGreenStar(struct Sprite *);
void AnimWeakFrustrationAngerMark(struct Sprite *);
void AnimSweetScentPetal(struct Sprite *);
void AnimPainSplitProjectile(struct Sprite *);
void AnimFlatterConfetti(struct Sprite *);
void AnimFlatterSpotlight(struct Sprite *);
void AnimFlatterSpotlight_Step(struct Sprite *sprite);
void AnimReversalOrb(struct Sprite *);
void AnimYawnCloud(struct Sprite *);
void AnimSmokeBallEscapeCloud(struct Sprite *);
void AnimFacadeSweatDrop(struct Sprite *);
void AnimRoarNoiseLine(struct Sprite *);
void AnimGlareEyeDot(struct Sprite *);
void AnimAssistPawprint(struct Sprite *);
void AnimSmellingSaltsHand(struct Sprite *);
void AnimSmellingSaltExclamation(struct Sprite *);
void AnimHelpingHandClap(struct Sprite *);
void AnimForesightMagnifyingGlass(struct Sprite *);
void AnimMeteorMashStar(struct Sprite *);
void AnimBlockX(struct Sprite *);
void sub_80E3E84(struct Sprite *);
//void AnimParticuleBurst(struct Sprite *);
void AnimKnockOffStrike(struct Sprite *);
void AnimRecycle(struct Sprite *);

// battle_anim_special.c
void TryShinyAnimation(u8 battler, struct Pokemon *mon);
u8 ItemIdToBallId(u16 itemId);
u8 LaunchBallStarsTask(u8 x, u8 y, u8 priority, u8 subpriority, u8 ballId);
u8 LaunchBallFadeMonTask(bool8 unFadeLater, u8 battlerId, u32 arg2, u8 ballId);
void DoLoadHealthboxPalsForLevelUp(u8 *, u8 *, u8 battlerId);
void DoFreeHealthboxPalsForLevelUp(u8 batterId);

enum
{
    BATTLER_COORD_X,
    BATTLER_COORD_Y,
    BATTLER_COORD_X_2,
    BATTLER_COORD_Y_PIC_OFFSET,
    BATTLER_COORD_Y_PIC_OFFSET_DEFAULT,
};

enum
{
    BATTLER_COORD_ATTR_HEIGHT,
    BATTLER_COORD_ATTR_WIDTH,
    BATTLER_COORD_ATTR_TOP,
    BATTLER_COORD_ATTR_BOTTOM,
    BATTLER_COORD_ATTR_LEFT,
    BATTLER_COORD_ATTR_RIGHT,
    BATTLER_COORD_ATTR_RAW_BOTTOM,
};

// battle_anim_status_effects.s
#define STAT_ANIM_PLUS1  15
#define STAT_ANIM_PLUS2  39
#define STAT_ANIM_MINUS1 22
#define STAT_ANIM_MINUS2 46
#define STAT_ANIM_MULTIPLE_PLUS1 55
#define STAT_ANIM_MULTIPLE_PLUS2 56
#define STAT_ANIM_MULTIPLE_MINUS1 57
#define STAT_ANIM_MULTIPLE_MINUS2 58
void LaunchStatusAnimation(u8 battlerId, u8 statusAnimId);
extern const union AnimCmd *const sAnims_SpinningSparkle[];

// battle_anim_mons.c
extern const struct MonCoords gCastformFrontSpriteCoords[];
u8 GetBattlerSpriteCoord(u8 battlerId, u8 coordType);
u8 GetBattlerSpriteCoord2(u8 battlerId, u8 coordType);
u8 GetBattlerSpriteDefault_Y(u8 battlerId);
u8 GetSubstituteSpriteDefault_Y(u8 battlerId);
u8 GetGhostSpriteDefault_Y(u8 battlerId);
u8 GetBattlerYCoordWithElevation(u8 battlerId);
u8 GetAnimBattlerSpriteId(u8 animBattler);
void StoreSpriteCallbackInData6(struct Sprite *sprite, SpriteCallback callback);
void TranslateSpriteInCircleOverDuration(struct Sprite *sprite);
void TranslateSpriteInGrowingCircleOverDuration(struct Sprite *sprite);
void TranslateSpriteInEllipseOverDuration(struct Sprite *sprite);
void WaitAnimForDuration(struct Sprite *sprite);
void sub_8074C80(struct Sprite *sprite);
void TranslateSpriteLinear(struct Sprite *sprite);
void TranslateSpriteLinearFixedPoint(struct Sprite *sprite);
void TranslateMonSpriteLinear(struct Sprite *sprite);
void TranslateMonSpriteLinearFixedPoint(struct Sprite *sprite);
void TranslateSpriteLinearAndFlicker(struct Sprite *sprite);
void DestroySpriteAndMatrix(struct Sprite *sprite);
void RunStoredCallbackWhenAffineAnimEnds(struct Sprite *sprite);
void RunStoredCallbackWhenAnimEnds(struct Sprite *sprite);
void DestroyAnimSpriteAndDisableBlend(struct Sprite *sprite);
void DestroyAnimVisualTaskAndDisableBlend(u8 taskId);
void SetSpriteCoordsToAnimAttackerCoords(struct Sprite *sprite);
void SetAnimSpriteInitialXOffset(struct Sprite *sprite, s16 xOffset);
void InitAnimArcTranslation(struct Sprite *sprite);
bool8 TranslateAnimHorizontalArc(struct Sprite *sprite);
bool8 TranslateAnimVerticalArc(struct Sprite *sprite);
void SetSpritePrimaryCoordsFromSecondaryCoords(struct Sprite *sprite);
void InitSpritePosToAnimTarget(struct Sprite *sprite, bool8 respectMonPicOffsets);
void InitSpritePosToAnimAttacker(struct Sprite *sprite, bool8 respectMonPicOffsets);
u8 GetBattlerSide(u8 battlerId);
u8 GetBattlerPosition(u8 battlerId);
u8 GetBattlerAtPosition(u8 position);
bool8 IsBattlerSpritePresent(u8 battlerId);
bool8 IsDoubleBattle(void);
void GetBattleAnimBg1Data(struct BattleAnimBgData *animBgData);
void GetBattleAnimBgData(struct BattleAnimBgData *animBgData, u32 bgId);
void ClearBattleAnimBg(u32 bgId);
void GetBattleAnimBgDataByPriorityRank(struct BattleAnimBgData *animBgData, u8 unused);
void AnimLoadCompressedBgTilemapHandleContest(struct BattleAnimBgData *, const void *, bool32);
void InitBattleAnimBg(u32 bgId);
void AnimLoadCompressedBgGfx(u32 bgId, const u32 *src, u32 tilesOffset);
void InitAnimBgTilemapBuffer(u32 bgId, const void *src);
void AnimLoadCompressedBgTilemap(u32 bgId, const u32 *src);
u8 GetBattleBgPaletteNum(void);
void ToggleBg3Mode(bool8 arg0);
void StartSpriteLinearTranslationFromCurrentPos(struct Sprite *sprite);
void InitSpriteDataForLinearTranslation(struct Sprite *sprite);
void InitAnimLinearTranslation(struct Sprite *sprite);
void StartAnimLinearTranslation(struct Sprite *sprite);
void PlayerThrowBall_StartAnimLinearTranslation(struct Sprite *sprite);
bool8 AnimTranslateLinear(struct Sprite *sprite);
void AnimTranslateLinear_WaitEnd(struct Sprite *sprite);
void BattleAnim_InitLinearTranslationWithDuration(struct Sprite *sprite);
void BattleAnim_InitAndRunLinearTranslationWithDuration(struct Sprite *sprite);
void InitAndRunAnimFastLinearTranslation(struct Sprite *sprite);
bool8 AnimFastTranslateLinear(struct Sprite *sprite);
void InitAnimFastLinearTranslationWithSpeed(struct Sprite *sprite);
void InitAnimFastLinearTranslationWithSpeedAndPos(struct Sprite *sprite);
void SetSpriteRotScale(u8 spriteId, s16 xScale, s16 yScale, u16 rotation);
void PrepareBattlerSpriteForRotScale(u8 spriteId, u8 objMode);
void ResetSpriteRotScale(u8 spriteId);
void SetBattlerSpriteYOffsetFromRotation(u8 spriteId);
void TrySetSpriteRotScale(struct Sprite *sprite, bool8 recalcCenterVector, s16 xScale, s16 yScale, u16 rotation);
void ResetSpriteRotScale_PreserveAffine(struct Sprite *sprite);
u16 ArcTan2Neg(s16 a, s16 b);
void SetGreyscaleOrOriginalPalette(u16 paletteNum, bool8 restoreOriginalColor);
u32 SelectBattleAnimSpriteAndBgPalettes(bool8 battleBackground, bool8 attacker, bool8 target, bool8 attackerPartner, bool8 targetPartner, bool8 a6, bool8 a7);
u32 SelectBattlerSpritePalettes(bool8 playerLeft, bool8 playerRight, bool8 foeLeft, bool8 foeRight);
u8 GetSpritePalIdxByBattler(u8 a1);
void AnimSpriteOnMonPos(struct Sprite *sprite);
void TranslateAnimSpriteToTargetMonLocation(struct Sprite *sprite);
void AnimThrowProjectile(struct Sprite *sprite);
void AnimSnoreZ(struct Sprite *sprite);
s16 CloneBattlerSpriteWithBlend(u8 animBattler);
void obj_delete_but_dont_free_vram(struct Sprite *sprite);
void AnimTask_AlphaFadeIn(u8 taskId);
void AnimTask_BlendMonInAndOut(u8 task);
void AnimTask_BlendPalInAndOutByTag(u8 taskId);
void PrepareAffineAnimInTaskData(struct Task *task, u8 spriteId, const union AffineAnimCmd *affineAnimCmds);
bool8 RunAffineAnimFromTaskData(struct Task *task);
void SetBattlerSpriteYOffsetFromYScale(u8 spriteId);
void SetBattlerSpriteYOffsetFromOtherYScale(u8 spriteId, u8 otherSpriteId);
void StorePointerInVars(s16 *lo, s16 *hi, const void *ptr);
void *LoadPointerFromVars(s16 lo, s16 hi);
void PrepareEruptAnimTaskData(struct Task *task, u8 spriteId, s16 a3, s16 a4, s16 a5, s16 a6, u16 a7);
u8 UpdateEruptAnimTask(struct Task *task);
void AnimTask_GetFrustrationPowerLevel(u8 taskId);
void sub_80767F0(void);
u8 GetBattlerSpriteSubpriority(u8 battlerId);
u8 GetBattlerSpriteBGPriority(u8 battlerId);

// Returns 2 if player left or opp right
// Returns 1 if player right or opp left
u8 GetBattlerSpriteBGPriorityRank(u8 battlerId);
u8 CreateAdditionalMonSpriteForMoveAnim(u16 species, bool8 isBackpic, u8 a3, s16 x, s16 y, u8 subpriority, u32 personality, u32 trainerId, u32 battlerId, u32 a10);
void DestroySpriteAndFreeResources_(struct Sprite *sprite);
s16 GetBattlerSpriteCoordAttr(u8 battlerId, u8 attr);
void SetAverageBattlerPositions(u8 battlerId, bool8 respectMonPicOffsets, s16 *x, s16 *y);
u8 CreateInvisibleSpriteCopy(s32 battlerId, u8 spriteId, s32 species);
void AnimTranslateLinearAndFlicker_Flipped(struct Sprite *sprite);
void AnimTranslateLinearAndFlicker(struct Sprite *sprite);
void AnimSpinningSparkle(struct Sprite *sprite);
void AnimTask_AttackerPunchWithTrace(u8 taskId);
void AnimWeatherBallUp(struct Sprite *sprite);
void AnimWeatherBallDown(struct Sprite *sprite);

// battle_anim_mon_movement.c
void AnimTask_ShakeMon(u8 taskId);
void AnimTask_ShakeMon2(u8 taskId);
void AnimTask_ShakeMonInPlace(u8 taskId);
void AnimTask_ShakeAndSinkMon(u8 taskId);
void AnimTask_TranslateMonElliptical(u8 taskId);
void AnimTask_TranslateMonEllipticalRespectSide(u8 taskId);
void AnimTask_WindUpLunge(u8 taskId);
void AnimTask_SlideOffScreen(u8 taskId);
void AnimTask_SwayMon(u8 taskId);
void AnimTask_ScaleMonAndRestore(u8 taskId);
void AnimTask_RotateMonSpriteToSide(u8 taskId);
void AnimTask_RotateMonToSideAndRestore(u8 taskId);
void AnimTask_ShakeTargetBasedOnMovePowerOrDmg(u8 taskId);

//bug.c
void AnimStringWrap_Step(struct Sprite *sprite);
void AnimMissileArc(struct Sprite *sprite);
void AnimSpiderWeb(struct Sprite *sprite);
void AnimMissileArc_Step(struct Sprite *sprite);

// normal.c
extern const struct SpriteTemplate gFlashingHitSplatSpriteTemplate;
extern const struct SpriteTemplate gBasicHitSplatSpriteTemplate;
extern const struct SpriteTemplate gWaterHitSplatSpriteTemplate;
extern const union AffineAnimCmd *const gAffineAnims_HitSplat[];
u32 UnpackSelectedBattleAnimPalettes(s16 selector);
void AnimTask_BlendColorCycle(u8 taskId);
void AnimTask_BlendColorCycleExclude(u8 taskId);
void AnimTask_BlendColorCycleByTag(u8 taskId);
void AnimTask_FlashAnimTagWithColor(u8 taskId);
void AnimTask_InvertScreenColor(u8 taskId);
void AnimTask_ShakeBattleTerrain(u8 taskId);
void AnimHitSplatBasic(struct Sprite *sprite);
void AnimFlashingHitSplat(struct Sprite *sprite);
void AnimFlashingHitSplat_Step(struct Sprite *sprite);
void AnimHitSplatRandom(struct Sprite *sprite);
void AnimCrossImpact(struct Sprite *sprite);
void AnimHitSplatOnMonEdge(struct Sprite *sprite);

// ground.c
void AnimTask_DigDownMovement(u8 taskId);
void AnimTask_DigUpMovement(u8 taskId);
void AnimTask_HorizontalShake(u8 taskId);
void AnimTask_IsPowerOver99(u8 taskId);
void AnimTask_PositionFissureBgOnBattler(u8 taskId);
void AnimMudSportDirt(struct Sprite *sprite);
void AnimDirtScatter(struct Sprite *sprite);
void AnimMudSportDirtRising(struct Sprite *sprite);
void AnimFissureDirtPlumeParticle(struct Sprite *sprite);
extern const union AffineAnimCmd *const gAffineAnims_SpinningBone[];

// dragon.c
void AnimTask_DragonDanceWaver(u8 taskId);
void AnimDragonRageFirePlume(struct Sprite *sprite);
void AnimDragonFireToTarget(struct Sprite *sprite);
void AnimDragonDanceOrb(struct Sprite *sprite);
void AnimOverheatFlame(struct Sprite *sprite);
extern const union AnimCmd *const gAnims_DragonBreathFire[];
extern const union AffineAnimCmd *const gAffineAnims_DragonBreathFire[];
extern const union AnimCmd *const gAnims_DragonRageFirePlume[];
extern const union AffineAnimCmd *const gAffineAnims_DragonRageFire[];
extern const union AnimCmd *const gAnims_DragonRageFire[];

// ghost.c
void AnimTask_NightShadeClone(u8 taskId);
void AnimTask_NightmareClone(u8 taskId);
void AnimTask_SpiteTargetShadow(u8 taskId);
void AnimTask_DestinyBondWhiteShadow(u8 taskId);
void AnimTask_CurseStretchingBlackBg(u8 taskId);
void AnimTask_GrudgeFlames(u8 taskId);
void AnimTask_GrudgeFlames_Step(u8 taskId);
void AnimShadowBall(struct Sprite *sprite);
void AnimGhostStatusSprite(struct Sprite *sprite);
void sub_80B6BBC(u8 taskId);
extern const union AffineAnimCmd *const gAffineAnims_ShadowBall[];

// rock.c
void AnimTask_LoadSandstormBackground(u8 taskId);
void AnimTask_Rollout(u8 taskId);
void AnimTask_GetSeismicTossDamageLevel(u8 taskId);
void AnimTask_MoveSeismicTossBg(u8 taskId);
void AnimTask_SeismicTossBgAccelerateDownAtEnd(u8 taskId);
extern const union AffineAnimCmd *const gAffineAnims_Whirlpool[];
extern const union AffineAnimCmd *const gAffineAnims_BasicRock[];
extern const union AnimCmd *const gAnims_FlyingRock[];
void AnimParticleInVortex(struct Sprite *sprite);
void AnimFallingRock(struct Sprite *sprite);
void AnimRaiseSprite(struct Sprite *sprite);
void AnimFallingRock_Step(struct Sprite *sprite);
void AnimFlyingSandCrescent(struct Sprite *sprite);

// psychic.c
extern const union AffineAnimCmd *const gAffineAnims_PsychoBoostOrb[];
extern const union AffineAnimCmd *const gAffineAnims_LusterPurgeCircle[];
void AnimPsychoBoost(struct Sprite *sprite);
void AnimTask_MeditateStretchAttacker(u8 taskId);
void AnimTask_Teleport(u8 taskId);
void AnimTask_ImprisonOrbs(u8 taskId);
void AnimTask_SkillSwap(u8 taskId);
void AnimTask_ExtrasensoryDistortion(u8 taskId);
void AnimTask_TransparentCloneGrowAndShrink(u8 taskId);

// dark.c
extern const union AffineAnimCmd *const gAffineAnims_Bite[];
extern const union AffineAnimCmd *const gAffineAnims_TearDrop[];
extern const union AnimCmd *const gAnims_ClawSlash[];
void AnimTask_AttackerFadeToInvisible(u8 taskId);
void AnimTask_AttackerFadeFromInvisible(u8 taskId);
void AnimTask_InitAttackerFadeFromInvisible(u8 taskId);
void AnimTask_MoveAttackerMementoShadow(u8 taskId);
void AnimTask_MoveTargetMementoShadow(u8 taskId);
void AnimTask_InitMementoShadow(u8 taskId);
void sub_80B8664(u8 taskId);  //sub_8114470 in emerald
void AnimTask_MetallicShine(u8 taskId);
void AnimTask_SetGreyscaleOrOriginalPal(u8 taskId);
void GetIsDoomDesireHitTurn(u8 taskId);
void AnimClawSlash(struct Sprite *sprite);
void AnimTearDrop(struct Sprite *sprite);
void AnimBite(struct Sprite *sprite);

// flying.c
void AnimTask_AnimateGustTornadoPalette(u8 taskId);
void AnimTask_DrillPeckHitSplats(u8 taskId);
void DestroyAnimSpriteAfterTimer(struct Sprite *sprite);
void AnimAirWaveCrescent(struct Sprite *sprite);
void AnimFlyBallUp(struct Sprite *sprite);
void AnimFlyBallUp_Step(struct Sprite *sprite);
void AnimFlyBallAttack(struct Sprite *sprite);
void AnimFlyBallAttack_Step(struct Sprite *sprite);
void AnimBounceBallLand(struct Sprite *sprite);
void AnimEllipticalGust(struct Sprite *);
extern const union AnimCmd *const gAffineAnims_AirWaveCrescent[]; //looks wrong but is right
extern const union AffineAnimCmd *const gAffineAnims_FlyBallUp[];
extern const union AffineAnimCmd *const gAffineAnims_FlyBallAttack[];
extern const union AffineAnimCmd *const gAffineAnims_BounceBallLand[];


// poison.c
extern const union AffineAnimCmd *const gAffineAnims_Droplet[];
extern const union AnimCmd *const gAnims_PoisonProjectile[];
extern const union AnimCmd *const gAnims_AcidPoisonDroplet[];
extern const union AffineAnimCmd *const gAffineAnims_PoisonProjectile[];
extern const union AffineAnimCmd *const gAffineAnims_Bubble[];
void AnimSludgeBombHitParticle(struct Sprite *sprite);  //only strut Sprite * in emerald, this should be fine
void AnimAcidPoisonBubble_Step(struct Sprite *sprite);
void AnimBubbleEffect(struct Sprite *sprite);

// fighting.c
void AnimTask_MoveSkyUppercutBg(u8 taskId); //defined here in firered not emerald
void AnimStompFoot(struct Sprite *sprite);
void AnimBrickBreakWall_Step(struct Sprite *sprite);
void AnimSpinningKickOrPunch(struct Sprite *sprite);
void AnimSpinningKickOrPunchFinish(struct Sprite *sprite);
void AnimJumpKick(struct Sprite *sprite);
void AnimBasicFistOrFoot(struct Sprite *sprite);
void AnimRevengeScratch(struct Sprite *sprite);
void AnimDizzyPunchDuck(struct Sprite *sprite);
void AnimSuperpowerFireball(struct Sprite *);
extern const union AnimCmd *const gAnims_HandsAndFeet[];
extern const union AffineAnimCmd *const gAffineAnims_MegaPunchKick[];
extern const union AffineAnimCmd *const gAffineAnims_SpinningHandOrFoot[];
extern const union AnimCmd *const gAnims_RevengeBigScratch[];
extern const union AnimCmd *const gAnims_RevengeSmallScratch[];

// ice.c
extern const union AnimCmd *const gAnims_SmallBubblePair[];
extern const union AnimCmd *const gAnims_Snowball[];
extern const union AffineAnimCmd *const gAffineAnims_IceCrystalHit[];
extern const union AnimCmd *const gAnims_IceCrystalLarge[];
extern const union AnimCmd *const gAnims_IceBallChunk[];
extern const union AnimCmd *const gAnims_BlizzardIceCrystal[];
void AnimThrowMistBall(struct Sprite *sprite);
void AnimSwirlingSnowball_Step1(struct Sprite *sprite);
void AnimMoveParticleBeyondTarget(struct Sprite *sprite);
void AnimIceEffectParticle(struct Sprite *sprite);
void AnimTask_Haze1(u8 taskId);
void AnimTask_LoadMistTiles(u8 taskId);
void AnimTask_Hail1(u8 taskId);
void AnimTask_GetRolloutCounter(u8 taskId);

// electric.c
void AnimTask_ElectricBolt(u8 taskId);
void AnimTask_ElectricChargingParticles(u8 taskId);
void AnimTask_VoltTackleAttackerReappear(u8 taskId);
void AnimTask_VoltTackleBolt(u8 taskId);
void AnimTask_ShockWaveProgressingBolt(u8 taskId);
void AnimTask_ShockWaveLightning(u8 taskId);
void AnimThunderWave(struct Sprite *sprite);
void AnimGrowingChargeOrb(struct Sprite *sprite);
void AnimZapCannonSpark(struct Sprite *sprite);
void AnimSparkElectricity(struct Sprite *sprite);
void AnimElectricPuff(struct Sprite *sprite);
void AnimSparkElectricityFlashing(struct Sprite *sprite);
void AnimGrowingShockWaveOrb(struct Sprite *sprite);
void AnimElectricity(struct Sprite *sprite);
extern const union AffineAnimCmd *const gAffineAnims_GrowingElectricOrb[];
extern const union AffineAnimCmd *const gAffineAnims_FlashingSpark[];
extern const union AnimCmd *const gAnims_ThunderboltOrb[];
extern const union AnimCmd *const gAnims_ElectricPuff[];
extern const union AnimCmd *const gAnims_ElectricChargingParticles[];

// fire.c
void AnimTask_EruptionLaunchRocks(u8 taskId);
void AnimTask_ShakeTargetInPattern(u8 taskId);
void AnimTask_BlendBackground(u8 taskId);
void AnimTask_MoveHeatWaveTargets(u8 taskId);
void AnimFireSpread(struct Sprite *sprite);
void AnimFireSpiralOutward(struct Sprite *sprite);
void AnimWillOWispOrb(struct Sprite *);
void AnimEruptionFallingRock(struct Sprite *);
void AnimFireCross(struct Sprite *);
void AnimFirePlume(struct Sprite *sprite);
extern const union AnimCmd *const gAnims_BasicFire[];
extern const union AnimCmd *const gAnims_FireBlastCross[];
extern const union AnimCmd *const gAnims_FirePlume[];
extern const union AnimCmd *const gAnims_WillOWispOrb[];

// water.c
extern const union AnimCmd *const gAnims_WaterMudOrb[];
extern const union AnimCmd *const gAnims_WaterBubble[];
void AnimWaterPulseRing(struct Sprite *sprite);
void AnimSmallBubblePair(struct Sprite *sprite);
void AnimWaterPulseBubble(struct Sprite *sprite);
extern const union AnimCmd *const gAnims_WaterBubbleProjectile[];
extern const union AnimCmd *const gAnims_FlamethrowerFlame[];
extern const union AnimCmd *const gAnims_WaterPulseBubble[];

// smokescreen.c
u8 SmokescreenImpact(s16 x, s16 y, u8 a3);

// battle_anim_utility_funcs.c
void AnimTask_BlendSelected(u8 taskId);
void AnimTask_BlendExcept(u8 taskId);
void AnimTask_SetCamouflageBlend(u8 taskId);
void AnimTask_BlendParticle(u8 taskId);
void AnimTask_HardwarePaletteFade(u8 taskId);
void AnimTask_CloneBattlerSpriteWithBlend(u8 taskId);
void AnimTask_SetUpCurseBackground(u8 taskId);
void sub_80BB088(u8 taskId);
void sub_80BB660(u8 taskId);
void AnimTask_BlendNonAttackerPalettes(u8 taskId);
void AnimTask_StartSlidingBg(u8 taskId);
void AnimTask_GetAttackerSide(u8 taskId);
void AnimTask_GetTargetSide(u8 taskId);
void AnimTask_GetTargetIsAttackerPartner(u8 taskId);
void AnimTask_SetAllNonAttackersInvisiblity(u8 taskId);
void sub_80BBA20(u8 taskId, s32 unused, u16 arg2, u8 battler1, u8 arg4, u8 arg5, u8 arg6, u8 arg7, const u32 *gfx, const u32 *tilemap, const u32 *palette);
void AnimTask_GetBattleTerrain(u8 taskId);
void AnimTask_AllocBackupPalBuffer(u8 taskId);
void AnimTask_FreeBackupPalBuffer(u8 taskId);
void AnimTask_CopyPalUnfadedToBackup(u8 taskId);
void AnimTask_CopyPalUnfadedFromBackup(u8 taskId);
void AnimTask_CopyPalFadedToUnfaded(u8 taskId);
void AnimTask_IsContest(u8 taskId);
void AnimTask_SetAnimAttackerAndTargetForEffectTgt(u8 taskId);
void AnimTask_IsTargetSameSide(u8 taskId);
void AnimTask_SetAnimTargetToBattlerTarget(u8 taskId);
void AnimTask_SetAnimAttackerAndTargetForEffectAtk(u8 taskId);
void AnimTask_SetAttackerInvisibleWaitForSignal(u8 taskId);

// battle_anim_scripts.s
extern const u8 *const gBattleAnims_StatusConditions[];
extern const u16 gMovesWithQuietBGM[];
extern const u8 *const gBattleAnims_Moves[];

// battle_anim_new.c
void AnimTask_SquishTarget(u8 taskId);
void CoreEnforcerLoadBeamTarget(struct Sprite *sprite);
void AnimTask_CreateBestowItem(u8 taskId);
void AnimTask_PurpleFlamesOnTarget(u8 taskId);
void AnimTask_TechnoBlast(u8 taskId);

#endif // GUARD_BATTLE_ANIM_H
