#include "global.h"
#include "gflib.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_script_commands.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_main.h"
#include "battle_message.h"
#include "battle_scripts.h"
#include "battle_setup.h"
#include "battle_string_ids.h"
#include "berry.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "graphics.h"
#include "help_system.h"
#include "item.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "m4a.h"
#include "party_menu.h"
#include "pokeball.h"
#include "pokedex.h"
#include "quest_log.h"
#include "random.h"
#include "roamer.h"
#include "safari_zone.h"
#include "scanline_effect.h"
#include "task.h"
#include "trig.h"
#include "vs_seeker.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_setup.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/songs.h"
#include "constants/trainer_classes.h"
#include "constants/opponents.h" //believe trainerNum, should be same as values for opponents in opponents.h since trainer.h is in same order

static void SpriteCB_UnusedDebugSprite(struct Sprite *sprite);
static void HandleAction_UseMove(void);
static void HandleAction_Switch(void);
static void HandleAction_UseItem(void);
static void HandleAction_Run(void);
static void HandleAction_WatchesCarefully(void);
static void HandleAction_SafariZoneBallThrow(void);
static void HandleAction_ThrowBait(void);
static void HandleAction_ThrowRock(void);
static void HandleAction_SafariZoneRun(void);
static void HandleAction_OldManBallThrow(void);
static void HandleAction_TryFinish(void);
static void HandleAction_NothingIsFainted(void);
static void HandleAction_WaitTurnEnd(void);
static void HandleAction_ActionFinished(void);
static void HandleEndTurn_ContinueBattle(void);
static void HandleEndTurn_BattleWon(void);
static void HandleEndTurn_BattleLost(void);
static void HandleEndTurn_RanFromBattle(void);
static void HandleEndTurn_MonFled(void);
static void HandleEndTurn_FinishBattle(void);
static void CB2_InitBattleInternal(void);
static void CB2_PreInitMultiBattle(void);
static void CB2_HandleStartMultiBattle(void);
static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum);
static void CB2_HandleStartBattle(void);
static void TryCorrectShedinjaLanguage(struct Pokemon *mon);
static void BattleMainCB1(void);
static void CB2_QuitPokedudeBattle(void);
static void SpriteCB_UnusedDebugSprite_Step(struct Sprite *sprite);
static void CB2_EndLinkBattle(void);
static void EndLinkBattleInSteps(void);
static void SpriteCB_MoveWildMonToRight(struct Sprite *sprite);
static void SpriteCB_WildMonShowHealthbox(struct Sprite *sprite);
//static void SpriteCB_Unused_8011E28_Step(struct Sprite *sprite);
static void SpriteCB_AnimFaintOpponent(struct Sprite *sprite);
static void SpriteCb_BlinkVisible(struct Sprite *sprite);
static void oac_poke_ally_(struct Sprite *sprite);
static void SpriteCallbackDummy3(struct Sprite *sprite);
static void SpriteCB_BounceEffect(struct Sprite *sprite);
static void SpriteCB_PlayerThrowUpdate(struct Sprite *sprite);
static void BattleStartClearSetData(void);
static void BattleIntroGetMonsData(void);
static void TurnValuesCleanUp(bool8 var0);
static void SpecialStatusesClear(void);
static void BattleIntroPrepareBackgroundSlide(void);
static void BattleIntroDrawTrainersOrMonsSprites(void);
static void BattleIntroDrawPartySummaryScreens(void);
static void BattleIntroPrintTrainerWantsToBattle(void);
static void BattleIntroPrintWildMonAttacked(void);
static void BattleIntroPrintOpponentSendsOut(void);
static void BattleIntroPrintPlayerSendsOut(void);
static void BattleIntroRecordMonsToDex(void);
static void BattleIntroOpponentSendsOutMonAnimation(void);
static void BattleIntroPlayerSendsOutMonAnimation(void);
static void TryDoEventsBeforeFirstTurn(void);
static void HandleTurnActionSelectionState(void);
static void RunTurnActionsFunctions(void);
static void SetActionsAndBattlersTurnOrder(void);
static void CheckFocusPunch_ClearVarsBeforeTurnStarts(void);
static void HandleEndTurn_FinishBattle(void);
static void FreeResetData_ReturnToOvOrDoEvolutions(void);
static void ReturnFromBattleToOverworld(void);
static void TryEvolvePokemon(void);
static void WaitForEvoSceneToFinish(void);

EWRAM_DATA u16 gBattle_BG0_X = 0;
EWRAM_DATA u16 gBattle_BG0_Y = 0;
EWRAM_DATA u16 gBattle_BG1_X = 0;
EWRAM_DATA u16 gBattle_BG1_Y = 0;
EWRAM_DATA u16 gBattle_BG2_X = 0;
EWRAM_DATA u16 gBattle_BG2_Y = 0;
EWRAM_DATA u16 gBattle_BG3_X = 0;
EWRAM_DATA u16 gBattle_BG3_Y = 0;
EWRAM_DATA u16 gBattle_WIN0H = 0;
EWRAM_DATA u16 gBattle_WIN0V = 0;
EWRAM_DATA u16 gBattle_WIN1H = 0;
EWRAM_DATA u16 gBattle_WIN1V = 0; //gonna try 380, estimated by counting hover over values for 3 buffs and gunown below whih was about 73
EWRAM_DATA u8 gDisplayedStringBattle[380] = {0}; //need increase from 300 to fix brocks
EWRAM_DATA u8 gBattleTextBuff1[TEXT_BUFF_ARRAY_COUNT] = {0};
EWRAM_DATA u8 gBattleTextBuff2[TEXT_BUFF_ARRAY_COUNT] = {0};
EWRAM_DATA u8 gBattleTextBuff3[TEXT_BUFF_ARRAY_COUNT] = {0};
//static EWRAM_DATA u32 gUnknown_2022AE8[25] = {0}; //zsonic  //GriffinR came through again,  thought this was unused but removing is what broke brocks battle.
EWRAM_DATA u32 gBattleTypeFlags = 0;
EWRAM_DATA u8 gBattleTerrain = 0;
EWRAM_DATA u32 gUnknown_2022B54 = 0;
EWRAM_DATA struct MultiBattlePokemonTx gMultiPartnerParty[3] = {0};
EWRAM_DATA u8 *gBattleAnimMons_BgTilesBuffer = NULL;
EWRAM_DATA u8 *gBattleAnimMons_BgTilemapBuffer = NULL;
static EWRAM_DATA u16 *sUnknownDebugSpriteDataBuffer = NULL;
EWRAM_DATA u8 gBattleBufferA[MAX_BATTLERS_COUNT][0x200] = {0};
EWRAM_DATA u8 gBattleBufferB[MAX_BATTLERS_COUNT][0x200] = {0};
EWRAM_DATA u8 gActiveBattler = 0;
EWRAM_DATA u8 gBattlerAbility = 0;  //didn't want to port but its required since its the main thing used with ability popups
EWRAM_DATA u32 gBattleControllerExecFlags = 0;
EWRAM_DATA u8 gBattlersCount = 0;
EWRAM_DATA u16 gBattlerPartyIndexes[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerPositions[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gActionsByTurnOrder[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerByTurnOrder[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gCurrentTurnActionNumber = 0;
EWRAM_DATA u8 gCurrentActionFuncId = 0;
EWRAM_DATA struct BattlePokemon gBattleMons[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerSpriteIds[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gCurrMovePos = 0;
EWRAM_DATA u8 gChosenMovePos = 0;
EWRAM_DATA u16 gCurrentMove = 0;
EWRAM_DATA u16 gChosenMove = 0;
EWRAM_DATA u16 gCalledMove = 0;
EWRAM_DATA s32 gBattleMoveDamage = 0;
EWRAM_DATA s32 gHpDealt = 0;
EWRAM_DATA s32 gTakenDmg[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastUsedItem = 0;
EWRAM_DATA u16 gLastUsedAbility = 0;
EWRAM_DATA u8 gAnticipatedBattler = 0;  
EWRAM_DATA u8 gForewarnedBattler = 0;   
EWRAM_DATA u8 gBattlerAttacker = 0;
EWRAM_DATA u8 gBattlerTarget = 0;
EWRAM_DATA u8 gBattlerFainted = 0;
EWRAM_DATA u8 gEffectBattler = 0;
EWRAM_DATA u8 gPotentialItemEffectBattler = 0;
EWRAM_DATA u8 gAbsentBattlerFlags = 0;
EWRAM_DATA u8 gCritMultiplier = 0;
EWRAM_DATA u8 gMultiHitCounter = 0;
EWRAM_DATA u8 gMultiTask = 0;
EWRAM_DATA const u8 *gBattlescriptCurrInstr = NULL;
EWRAM_DATA u32 gUnusedBattleMainVar = 0;
EWRAM_DATA u8 gChosenActionByBattler[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA const u8 *gSelectionBattleScripts[MAX_BATTLERS_COUNT] = {NULL};
EWRAM_DATA u16 gLastPrintedMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastLandedMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLastHitByType[MAX_BATTLERS_COUNT] = {0};    //may need to add last hit by move for fly cancel?
EWRAM_DATA u16 gLastResultingMoves[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gLockedMoves[MAX_BATTLERS_COUNT] = {0};
//EWRAM_DATA u16 gLastUsedMove = 0; //still unsure if I need to add this or can just use gLastResultingMoves which seems to be equivalent
EWRAM_DATA u8 gLastHitBy[MAX_BATTLERS_COUNT] = {0};//ran make with and without above line came to same conclusion so either works
EWRAM_DATA u16 gChosenMoveByBattler[MAX_BATTLERS_COUNT] = {0};//rn I'll use existing value to save on ram
EWRAM_DATA u8 gMoveResultFlags = 0;
EWRAM_DATA u32 gHitMarker = 0;
static EWRAM_DATA u8 gUnknown_2023DD4[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gTakenDmgByBattler[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gUnknown_2023DDC = 0;
EWRAM_DATA u16 gSideStatuses[2] = {0};
EWRAM_DATA struct SideTimer gSideTimers[2] = {0};
EWRAM_DATA u32 gStatuses3[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u32 gStatuses4[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct DisableStruct gDisableStructs[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gPauseCounterBattle = 0;
EWRAM_DATA u16 gPaydayMoney = 0;
EWRAM_DATA u16 gRandomTurnNumber = 0;
EWRAM_DATA u8 gBattleCommunication[BATTLE_COMMUNICATION_ENTRIES_COUNT] = {0};
EWRAM_DATA u8 gBattleOutcome = 0;
EWRAM_DATA struct ProtectStruct gProtectStructs[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct SpecialStatus gSpecialStatuses[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u16 gBattleWeather = 0;
EWRAM_DATA struct WishFutureKnock gWishFutureKnock = {0};
EWRAM_DATA u16 gIntroSlideFlags = 0;
EWRAM_DATA u8 gSentPokesToOpponent[2] = {0};
EWRAM_DATA u16 gDynamicBasePower = 0;
EWRAM_DATA u16 gExpShareExp = 0;
EWRAM_DATA struct BattleEnigmaBerry gEnigmaBerries[MAX_BATTLERS_COUNT] = {0}; //onlyused for ereader stuff can remove
EWRAM_DATA struct BattleScripting gBattleScripting = {0};
EWRAM_DATA struct BattleStruct *gBattleStruct = NULL;
EWRAM_DATA u8 *gLinkBattleSendBuffer = NULL;
EWRAM_DATA u8 *gLinkBattleRecvBuffer = NULL;
EWRAM_DATA struct BattleResources *gBattleResources = NULL;  //edited includes flags I added i.e flashfire etc.
EWRAM_DATA u8 gActionSelectionCursor[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gMoveSelectionCursor[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerStatusSummaryTaskId[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u8 gBattlerInMenuId = 0;
EWRAM_DATA bool8 gDoingBattleAnim = FALSE;
EWRAM_DATA u32 gTransformedPersonalities[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct BattleSpriteData *gBattleSpritesDataPtr = NULL;
EWRAM_DATA struct MonSpritesGfx *gMonSpritesGfxPtr = NULL;
EWRAM_DATA u16 gBattleMovePower = 0;
EWRAM_DATA u16 gMoveToLearn = 0;
EWRAM_DATA u8 gBattleMonForms[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA u32 gFieldStatuses = 0;
EWRAM_DATA struct FieldTimer gFieldTimers = { 0 };
EWRAM_DATA struct TotemBoost gTotemBoosts[MAX_BATTLERS_COUNT] = { 0 };  //not gonna use for my stuff so can comment out
EWRAM_DATA bool8 gHasFetchedBall = FALSE;
EWRAM_DATA u8 gLastUsedBall = 0;    //need to implement add in these 2 somewhere
EWRAM_DATA u16 gLastThrownBall = 0;
EWRAM_DATA bool8 gSwapDamageCategory = FALSE; // Photon Geyser, Shell Side Arm, Light That Burns the Sky

void (*gPreBattleCallback1)(void);
void (*gBattleMainFunc)(void);
struct BattleResults gBattleResults;
u8 gLeveledUpInBattle;
void (*gBattlerControllerFuncs[MAX_BATTLERS_COUNT])(void);
u8 gHealthboxSpriteIds[MAX_BATTLERS_COUNT];
u8 gMultiUsePlayerCursor;
u8 gNumberOfMovesToChoose;
u8 gBattleControllerData[MAX_BATTLERS_COUNT];

static const struct ScanlineEffectParams sIntroScanlineParams16Bit =
{
    &REG_BG3HOFS, SCANLINE_EFFECT_DMACNT_16BIT, 1
};

const struct SpriteTemplate gUnknownDebugSprite =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_UnusedDebugSprite,
};

static const u8 sText_ShedinjaJpnName[] = _("ヌケニン"); // Nukenin

const struct OamData gOamData_BattlerOpponent =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

const struct OamData gOamData_BattlerPlayer =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_NORMAL,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 2,
    .affineParam = 0,
};

// not used
static const union AnimCmd gUnknown_824F020[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_JUMP(0),
};

// not used
static const union AnimCmd *const gUnknown_824F028[] =
{
    gUnknown_824F020,
};

// not used
static const union AffineAnimCmd gUnknown_824F02C[] =
{
    AFFINEANIMCMD_FRAME(-0x10, 0x0, 0, 4),
    AFFINEANIMCMD_FRAME(0x0, 0x0, 0, 0x3C),
    AFFINEANIMCMD_JUMP(1),
};

// not used
static const union AffineAnimCmd *const gUnknown_824F044[] =
{
    gUnknown_824F02C,
};

static const s8 sPlayerThrowXTranslation[] = { -32, -16, -16, -32, -32, 0, 0, 0 };

#define X UQ_4_12
//rows are attacking type
//columns are defending type 
static const u16 sTypeEffectivenessTable[NUMBER_OF_MON_TYPES][NUMBER_OF_MON_TYPES] =
{
 //               normal  fight   flying  poison  ground   rock    bug    ghost   steel   mystery  fire   water   grass  electric  psychic  ice   dragon   dark   fairy    sound
      /*normal*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // normal

       /*fight*/ {X(2.0), X(1.0), X(0.5), X(0.5), X(1.0), X(2.0), X(0.5), X(0.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(2.0), X(0.5), X(1.0)}, // fight

      /*flying*/ {X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(2.0), X(0.5), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0)}, // flying

      /*poison*/ {X(1.0), X(2.0), X(1.0), X(0.0), X(0.5), X(0.0), X(1.0), X(0.5), X(0.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(2.0), X(1.0)}, // poison

      /*ground*/ {X(1.0), X(1.0), X(0.0), X(2.0), X(1.0), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(0.5), X(2.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0)}, // ground

        /*rock*/ {X(1.0), X(0.5), X(2.0), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // rock

         /*bug*/ {X(1.0), X(0.5), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(2.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0)}, // bug

       /*ghost*/ {X(0.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(1.0)}, // ghost

       /*steel*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(1.0), X(0.5), X(0.5), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(2.0), X(1.0)}, // steel

     /*mystery*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // mystery

        /*fire*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(2.0), X(0.5), X(2.0), X(1.0), X(0.5), X(0.5), X(2.0), X(1.0), X(1.0), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0)}, // fire

       /*water*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(0.5), X(0.5), X(1.0), X(1.0), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0)}, // water

       /*grass*/ {X(1.0), X(1.0), X(0.5), X(0.5), X(2.0), X(2.0), X(0.5), X(1.0), X(0.5), X(1.0), X(0.5), X(2.0), X(0.5), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0)}, // grass

    /*electric*/ {X(1.0), X(1.0), X(2.0), X(1.0), X(0.0), X(0.5), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(2.0), X(1.0), X(0.5), X(1.0), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0)}, // electric

     /*psychic*/ {X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(0.0), X(0.5), X(1.0)}, // psychic

         /*ice*/ {X(1.0), X(1.0), X(2.0), X(1.0), X(2.0), X(1.0), X(2.0), X(0.5), X(0.5), X(1.0), X(0.5), X(1.0), X(2.0), X(1.0), X(1.0), X(0.5), X(2.0), X(1.0), X(1.0), X(1.0)}, // ice

      /*dragon*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(0.5), X(1.0)}, // dragon

        /*dark*/ {X(1.0), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(0.5), X(0.5), X(0.5), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(2.0), X(1.0), X(1.0), X(2.0), X(2.0), X(1.0)}, // dark

       /*fairy*/ {X(2.0), X(1.0), X(1.0), X(0.5), X(1.0), X(1.0), X(0.5), X(1.0), X(0.5), X(1.0), X(0.5), X(1.0), X(0.0), X(1.0), X(1.0), X(1.0), X(2.0), X(2.0), X(1.0), X(1.0)}, // fairy

       /*sound*/ {X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0), X(1.0)}, // sound
};//              normal  fight   flying  poison  ground   rock    bug    ghost   steel   mystery  fire   water   grass  electric  psychic  ice   dragon    dark   fairy   sound

#undef X



// format: attacking type, defending type, damage multiplier
// the multiplier is a (decimal) fixed-point number:
// 20 is ×2.0 TYPE_MUL_SUPER_EFFECTIVE
// 10 is ×1.0 TYPE_MUL_NORMAL
// 05 is ×0.5 TYPE_MUL_NOT_EFFECTIVE
// 00 is ×0.0 TYPE_MUL_NO_EFFECT

//each line adds 3 because there are 3 arguments in each line, atk type, def type, & effectiveness  /so SUBTRACT 3 for any lines kept but commented out
//DON'T FORGET every time I change below, need to update in the .h / also need to update table above, so ai, and other pre-damage type calcs are accurate
#define TYPE_CHART

const u8 gTypeEffectiveness[417] = // 336 is number of entries x 3 i.e number of efffectiveness since only super not effective and no effect are included. 
{ // counted from ompen bracket to end of table. so subtract line end table is on from where open bracket starts (313)  then multipy by 3.
    TYPE_NORMAL, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_NORMAL, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIRE, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE, //ghost adjustment same logic as ice
    TYPE_FIRE, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE, //NEW effectiveness for snivy, may remove
    TYPE_FIRE, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIRE, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_WATER, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_WATER, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_WATER, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,   //new change mostly for cloyster but makes sense.
    TYPE_ELECTRIC, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,    //tentative change to make ice better defensively //there are several water ice & flying ice, makes science sense as well
    TYPE_ELECTRIC, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE, //made bug resist electric always made sense to me, they can chew threw electric cables
    TYPE_ELECTRIC, TYPE_GROUND, TYPE_MUL_NO_EFFECT,  //plus bug is related to nature like grass, which already resist electric
    TYPE_ELECTRIC, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ELECTRIC, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_WATER, TYPE_MUL_SUPER_EFFECTIVE,//removed grass resistance to electric,  lighting splits trees and can spark fire, didn't make sense, leaving neutral
    TYPE_GRASS, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GRASS, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GRASS, TYPE_DRAGON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GRASS, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,   //ghost adjustment, the dead aren't bothered by cold
    TYPE_ICE, TYPE_GROUND, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ICE, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ICE, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_NORMAL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE, //when grounded fighting should do normal damage to flying
    TYPE_FIGHTING, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FIGHTING, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_STEEL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_POISON, TYPE_POISON, TYPE_MUL_NO_EFFECT,
    TYPE_POISON, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_POISON, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,  //cold slows spread of poison
    TYPE_POISON, TYPE_ROCK, TYPE_MUL_NO_EFFECT,
    TYPE_POISON, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_POISON, TYPE_STEEL, TYPE_MUL_NO_EFFECT,
    TYPE_GROUND, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GROUND, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GROUND, TYPE_ELECTRIC, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GROUND, TYPE_GRASS, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GROUND, TYPE_POISON, TYPE_MUL_SUPER_EFFECTIVE,// delete ground to flying so its set to normal effective
    TYPE_GROUND, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE, //then create condition where its set to no effect if not grounded
    TYPE_GROUND, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE, //made ground steel neutral, as its better rock, and materiel comes from the earth
    TYPE_FLYING, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE,  //makes sense flying resists grass, birds make their home in trees,
    TYPE_FLYING, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,   //also hurricanes/tornadoes uproot & destroy trees
    TYPE_FLYING, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FLYING, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FLYING, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,  //screw it!! it makes sense so I'm doing it
    TYPE_FLYING, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,      //Removed psychic super to flying, too strong, psychic strong offensively can already beat flying at neutral
    TYPE_PSYCHIC, TYPE_FIGHTING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_PSYCHIC, TYPE_POISON, TYPE_MUL_SUPER_EFFECTIVE,    //psychic power can stop a target cold, can keep them from flying,    
    TYPE_PSYCHIC, TYPE_PSYCHIC, TYPE_MUL_NOT_EFFECTIVE,     //or confuse them which would make it impossible to fly, so makes sense,
    TYPE_PSYCHIC, TYPE_DARK, TYPE_MUL_NO_EFFECT,        //mostly done to counter fairy resistance
    TYPE_PSYCHIC, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,   //effect prob too strong, flying is weak defensively and psychic is strong offenseively
    TYPE_BUG, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,    //plus fairy nerfed, will replace with resistancee instad of super effectiveness
    TYPE_BUG, TYPE_GRASS, TYPE_MUL_SUPER_EFFECTIVE, //changed mind, flying still weak defensively regardless but they exell at attack so worse to weaken their atk power
    TYPE_BUG, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_ICE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_FLYING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_BUG, TYPE_PSYCHIC, TYPE_MUL_SUPER_EFFECTIVE,//removed ghost resistance to bug by accident in my chart, but was so good will add to my chart
    TYPE_BUG, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE, //removed still resist to bug, apparently many insect types are known to destroy/consume light metals, would be great for the type
    TYPE_ROCK, TYPE_FIRE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_GROUND, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_FLYING, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_BUG, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_ROCK, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_ROCK, TYPE_ROCK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GHOST, TYPE_NORMAL, TYPE_MUL_NO_EFFECT,
    TYPE_GHOST, TYPE_PSYCHIC, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_GHOST, TYPE_DARK, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GHOST, TYPE_GHOST, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_DRAGON, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_DRAGON, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_DARK, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_DARK, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,    //type change from wolveyvgc to buff bugs, its weak to bugs, so resists it, and dark is evil & bugs are //also associated with evil  so makes sense
    TYPE_DARK, TYPE_PSYCHIC, TYPE_MUL_SUPER_EFFECTIVE,  //-keeping psychic weakness to dark post ghost change as dark is living and able to do physical attacks while psychic is usually phsycially weak
    TYPE_DARK, TYPE_GHOST, TYPE_MUL_NOT_EFFECTIVE,  //changed there's nothing significant bout dark, its more or less same as ghost but alive, and ghosts thrive in darkness
    TYPE_DARK, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,   //change essentially makes ghost inverse of normal type effect wise, where most things are neutral and it has 1 weakness
    TYPE_DARK, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,//NEW type relation for dark types, showed positively for offense capability and makes sense sneaky backstabbers bad guys take each other out often.
    TYPE_STEEL, TYPE_WATER, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_ELECTRIC, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_FIGHTING, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_STEEL, TYPE_ICE, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_ROCK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FORESIGHT, TYPE_FORESIGHT, TYPE_MUL_NO_EFFECT,
    TYPE_NORMAL, TYPE_GHOST, TYPE_MUL_NO_EFFECT,
    TYPE_FIGHTING, TYPE_GHOST, TYPE_MUL_NO_EFFECT,
    TYPE_FAIRY, TYPE_NORMAL, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FAIRY, TYPE_DRAGON, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FAIRY, TYPE_DARK, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FAIRY, TYPE_STEEL, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_FIRE, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_POISON, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_BUG, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_FAIRY, TYPE_GRASS, TYPE_MUL_NO_EFFECT,     //grass buff, and based on idea fairy are nature spirits i.e can't hurt nature as they can't exist without it
    TYPE_POISON, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_STEEL, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_DARK, TYPE_FAIRY, TYPE_MUL_SUPER_EFFECTIVE,
    TYPE_FIGHTING, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_GHOST, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_PSYCHIC, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_DRAGON, TYPE_FAIRY, TYPE_MUL_NOT_EFFECTIVE,
    TYPE_SOUND, TYPE_SOUND, TYPE_MUL_NO_EFFECT,
    TYPE_ENDTABLE, TYPE_ENDTABLE, TYPE_MUL_NO_EFFECT
};

//questioned bug and ice resistance to electricity, but after research it made even more sense, than I initially thought.
//initial basis was grass resists, bug is like nature so is similar, also bugs chew threw electrical cables,
//and ice slowls electron flow, which can prevent electrical flow.
//but later found, not only  does ice stop electrical flow, bugs and ice are capable of producing lightning/electricity mostly via friction
//and as electric resists electric, that is another reason ice/bug resistance to electricity makes sense.

    //consider makign bugs immune to confusion status, like wolfeyvgc said, he didn't explain but I gather logic is most bugs work by hivemind,
//on top of having some type of extra sensory options with its feelers etc. will have to add dark type exception to prankster back i guess
//think this is done?

#define TYPE_NAMES
const u8 gTypeNames[][TYPE_NAME_LENGTH + 1] =
{
    _("NORMAL"),
    _("FIGHT"),
    _("FLYING"),
    _("POISON"),
    _("GROUND"),
    _("ROCK"),
    _("BUG"),
    _("GHOST"),
    _("STEEL"),
    _("???"),
    _("FIRE"),
    _("WATER"),
    _("GRASS"),
    _("ELECTR"),
    _("PSYCHC"),
    _("ICE"),
    _("DRAGON"),
    _("DARK"),
    _("FAIRY"), //fairy addition
    _("SOUND"),
}; //uses same type order as list_menu.c so this fairy is 12, but my actuall fairy type
//was at 17. fixed now they are both 12.
//had to retruncate type names to fit move name

//also needed change value in & pokemon.h

// This is a factor in how much money you get for beating a trainer.
const struct TrainerMoney gTrainerMoneyTable[] =
{
    { CLASS_LEADER_2, 25 },
    { CLASS_ELITE_FOUR_2, 25 },
    { CLASS_PKMN_PROF, 25 },
    { CLASS_RIVAL, 4 },
    { CLASS_RIVAL_2, 9 },
    { CLASS_CHAMPION_2, 25 },
    { CLASS_YOUNGSTER_2, 4 },
    { CLASS_BUG_CATCHER_2, 3 },
    { CLASS_HIKER_2, 9 },
    { CLASS_BIRD_KEEPER_2, 6 },
    { CLASS_PICNICKER_2, 5 },
    { CLASS_SUPER_NERD, 6 },
    { CLASS_FISHERMAN_2, 9 },
    { CLASS_TEAM_ROCKET, 8 },
    { CLASS_LASS_2, 4 },
    { CLASS_BEAUTY_2, 18 },
    { CLASS_BLACK_BELT_2, 6 },
    { CLASS_CUE_BALL, 6 },
    { CLASS_CHANNELER, 8 },
    { CLASS_ROCKER, 6 },
    { CLASS_GENTLEMAN_2, 18 },
    { CLASS_BURGLAR, 22 },
    { CLASS_SWIMMER_MALE_2, 1 },
    { CLASS_ENGINEER, 12 },
    { CLASS_JUGGLER, 10 },
    { CLASS_SAILOR_2, 8 },
    { CLASS_COOLTRAINER_2, 9 },
    { CLASS_POKEMANIAC_2, 12 },
    { CLASS_TAMER, 10 },
    { CLASS_CAMPER_2, 5 },
    { CLASS_PSYCHIC_2, 5 },
    { CLASS_BIKER, 5 },
    { CLASS_GAMER, 18 },
    { CLASS_SCIENTIST, 12 },
    { CLASS_CRUSH_GIRL, 6 },
    { CLASS_TUBER_3, 1 },
    { CLASS_PKMN_BREEDER_2, 7 },
    { CLASS_PKMN_RANGER_2, 9 },
    { CLASS_AROMA_LADY_2, 7 },
    { CLASS_RUIN_MANIAC_2, 12 },
    { CLASS_LADY_2, 50 },
    { CLASS_PAINTER, 4 },
    { CLASS_TWINS_2, 3 },
    { CLASS_YOUNG_COUPLE_2, 7 },
    { CLASS_SIS_AND_BRO_2, 1 },
    { CLASS_COOL_COUPLE, 6 },
    { CLASS_CRUSH_KIN, 6 },
    { CLASS_SWIMMER_FEMALE_2, 1 },
    { CLASS_PLAYER, 1 },
    { CLASS_LEADER, 25 },
    { CLASS_ELITE_FOUR, 25 },
    { CLASS_LASS, 4 },
    { CLASS_YOUNGSTER, 4 },
    { CLASS_PKMN_TRAINER_3, 15 },
    { CLASS_HIKER, 10 },
    { CLASS_BEAUTY, 20 },
    { CLASS_FISHERMAN, 10 },
    { CLASS_LADY, 50 },
    { CLASS_TRIATHLETE, 10 },
    { CLASS_TEAM_AQUA, 5 },
    { CLASS_TWINS, 3 },
    { CLASS_SWIMMER_FEMALE, 2 },
    { CLASS_BUG_CATCHER, 4 },
    { CLASS_SCHOOL_KID, 5 },
    { CLASS_RICH_BOY, 50 },
    { CLASS_SR_AND_JR, 4 },
    { CLASS_BLACK_BELT, 8 },
    { CLASS_TUBER, 1 },
    { CLASS_HEX_MANIAC, 6 },
    { CLASS_PKMN_BREEDER, 10 },
    { CLASS_TEAM_MAGMA, 5 },
    { CLASS_INTERVIEWER, 12 },
    { CLASS_TUBER_2, 1 },
    { CLASS_YOUNG_COUPLE, 8 },
    { CLASS_GUITARIST, 8 },
    { CLASS_GENTLEMAN, 20 },
    { CLASS_CHAMPION, 50 },
    { CLASS_MAGMA_LEADER, 20 },
    { CLASS_BATTLE_GIRL, 6 },
    { CLASS_SWIMMER_MALE, 2 },
    { CLASS_POKEFAN, 20 },
    { CLASS_EXPERT, 10 },
    { CLASS_DRAGON_TAMER, 12 },
    { CLASS_BIRD_KEEPER, 8 },
    { CLASS_NINJA_BOY, 3 },
    { CLASS_PARASOL_LADY, 10 },
    { CLASS_BUG_MANIAC, 15 },
    { CLASS_SAILOR, 8 },
    { CLASS_COLLECTOR, 15 },
    { CLASS_PKMN_RANGER, 12 },
    { CLASS_MAGMA_ADMIN, 10 },
    { CLASS_AROMA_LADY, 10 },
    { CLASS_RUIN_MANIAC, 15 },
    { CLASS_COOLTRAINER, 12 },
    { CLASS_POKEMANIAC, 15 },
    { CLASS_KINDLER, 8 },
    { CLASS_CAMPER, 4 },
    { CLASS_PICNICKER, 4 },
    { CLASS_PSYCHIC, 6 },
    { CLASS_SIS_AND_BRO, 3 },
    { CLASS_OLD_COUPLE, 10 },
    { CLASS_AQUA_ADMIN, 10 },
    { CLASS_AQUA_LEADER, 20 },
    { CLASS_BOSS, 25 },
    { 0xFF, 5 },
};


static void (*const sTurnActionsFuncsTable[])(void) =
{
    [B_ACTION_USE_MOVE] = HandleAction_UseMove,
    [B_ACTION_USE_ITEM] = HandleAction_UseItem,
    [B_ACTION_SWITCH] = HandleAction_Switch,
    [B_ACTION_RUN] = HandleAction_Run,
    [B_ACTION_SAFARI_WATCH_CAREFULLY] = HandleAction_WatchesCarefully,
    [B_ACTION_SAFARI_BALL] = HandleAction_SafariZoneBallThrow,
    [B_ACTION_SAFARI_BAIT] = HandleAction_ThrowBait,
    [B_ACTION_SAFARI_GO_NEAR] = HandleAction_ThrowRock,
    [B_ACTION_SAFARI_RUN] = HandleAction_SafariZoneRun,
    [B_ACTION_OLDMAN_THROW] = HandleAction_OldManBallThrow,
    [B_ACTION_EXEC_SCRIPT] = HandleAction_RunBattleScript,
    [B_ACTION_TRY_FINISH] = HandleAction_TryFinish,
    [B_ACTION_FINISHED] = HandleAction_ActionFinished,
    [B_ACTION_NOTHING_FAINTED] = HandleAction_NothingIsFainted,
    [B_ACTION_SKIP_TURN] = HandleAction_WaitTurnEnd,
};

static void (*const sEndTurnFuncsTable[])(void) =
{
    [0] = HandleEndTurn_ContinueBattle, //B_OUTCOME_NONE?
    [B_OUTCOME_WON] = HandleEndTurn_BattleWon,
    [B_OUTCOME_LOST] = HandleEndTurn_BattleLost,
    [B_OUTCOME_DREW] = HandleEndTurn_BattleLost,
    [B_OUTCOME_RAN] = HandleEndTurn_RanFromBattle,
    [B_OUTCOME_PLAYER_TELEPORTED] = HandleEndTurn_FinishBattle,
    [B_OUTCOME_MON_FLED] = HandleEndTurn_MonFled,
    [B_OUTCOME_CAUGHT] = HandleEndTurn_FinishBattle,
    [B_OUTCOME_NO_SAFARI_BALLS] = HandleEndTurn_FinishBattle,
};

const u8 gStatusConditionString_PoisonJpn[8] = _("どく$$$$$");
const u8 gStatusConditionString_SleepJpn[8] = _("ねむり$$$$");
const u8 gStatusConditionString_ParalysisJpn[8] = _("まひ$$$$$");
const u8 gStatusConditionString_BurnJpn[8] = _("やけど$$$$");
const u8 gStatusConditionString_IceJpn[8] = _("こおり$$$$");
const u8 gStatusConditionString_ConfusionJpn[8] = _("こんらん$$$");
const u8 gStatusConditionString_LoveJpn[8] = _("メロメロ$$$");

const u8 *const gStatusConditionStringsTable[7][2] =
{
    {gStatusConditionString_PoisonJpn, gText_Poison},
    {gStatusConditionString_SleepJpn, gText_Sleep},
    {gStatusConditionString_ParalysisJpn, gText_Paralysis},
    {gStatusConditionString_BurnJpn, gText_Burn},
    {gStatusConditionString_IceJpn, gText_Ice},
    {gStatusConditionString_ConfusionJpn, gText_Confusion},
    {gStatusConditionString_LoveJpn, gText_Love}
};

void CB2_InitBattle(void)
{
    MoveSaveBlocks_ResetHeap();
    AllocateBattleResources();
    AllocateBattleSpritesData();
    AllocateMonSpritesGfx();
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI) //not link, but multiplayer
    {
        return;
        SetMainCallback2(CB2_PreInitMultiBattle);
        gBattleCommunication[MULTIUSE_STATE] = 0;
    } 
    else
    {
        CB2_InitBattleInternal();
      /*  if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
        {
            if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                    SetHelpContext(HELPCONTEXT_TRAINER_BATTLE_DOUBLE);
                else
                    SetHelpContext(HELPCONTEXT_TRAINER_BATTLE_SINGLE);
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
            {
                SetHelpContext(HELPCONTEXT_SAFARI_BATTLE);
            }
            else
            {
                SetHelpContext(HELPCONTEXT_WILD_BATTLE);
            }
        }*/
    }
}

static void CB2_InitBattleInternal(void)
{
    s32 i;

    SetHBlankCallback(NULL);
    SetVBlankCallback(NULL);
    CpuFill32(0, (void *)VRAM, VRAM_SIZE);
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0, 0xF0));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(0x50, 0x51));
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    gBattle_WIN0H = WIN_RANGE(0, 0xF0);
    gBattle_WIN0V = WIN_RANGE(0x50, 0x51);
    ScanlineEffect_Clear();
    for (i = 0; i < 80; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xF0;
        gScanlineEffectRegBuffers[1][i] = 0xF0;
    }
    for (; i < 160; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xFF10;
        gScanlineEffectRegBuffers[1][i] = 0xFF10;
    }
    ScanlineEffect_SetParams(sIntroScanlineParams16Bit);
    ResetPaletteFade();
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gBattle_BG2_X = 0;
    gBattle_BG2_Y = 0;
    gBattle_BG3_X = 0;
    gBattle_BG3_Y = 0;
    gBattleTerrain = BattleSetup_GetTerrainId();
    InitBattleBgsVideo();
    LoadBattleTextboxAndBackground();
    ResetSpriteData();
    ResetTasks();
    DrawBattleEntryBackground();
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 4;
    SetVBlankCallback(VBlankCB_Battle);
    SetUpBattleVars();
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        SetMainCallback2(CB2_HandleStartMultiBattle);
    else
        SetMainCallback2(CB2_HandleStartBattle);
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        CreateNPCTrainerParty(&gEnemyParty[0], gTrainerBattleOpponent_A);
        SetWildMonHeldItem();
    }
    gMain.inBattle = TRUE;
    for (i = 0; i < PARTY_SIZE; ++i)
        AdjustFriendship(&gPlayerParty[i], 3);
    gBattleCommunication[MULTIUSE_STATE] = 0;
}
//believe this is summary screen during battle 
#define BUFFER_PARTY_VS_SCREEN_STATUS(party, flags, i)              \
    for ((i) = 0; (i) < PARTY_SIZE; (i)++)                          \
    {                                                               \
        u16 species = GetMonData(&(party)[(i)], MON_DATA_SPECIES2); \
        u16 hp = GetMonData(&(party)[(i)], MON_DATA_HP);            \
        u32 status = GetMonData(&(party)[(i)], MON_DATA_STATUS);    \
                                                                    \
        if (species == SPECIES_NONE)                                \
            continue;                                               \
                                                                    \
        /* Is healthy mon? */                                       \
        if (species != SPECIES_EGG && hp != 0 && status == 0)       \
            (flags) |= 1 << (i) * 2;                                \
                                                                    \
        if (species == SPECIES_NONE) /* Redundant */                \
            continue;                                               \
                                                                    \
        /* Is Egg or statused? */                                   \
        if (hp != 0 && (species == SPECIES_EGG || status != 0))     \
            (flags) |= 2 << (i) * 2;                                \
                                                                    \
        if (species == SPECIES_NONE) /* Redundant */                \
            continue;                                               \
                                                                    \
        /* Is fainted? */                                           \
        if (species != SPECIES_EGG && hp == 0)                      \
            (flags) |= 3 << (i) * 2;                                \
    }

static void BufferPartyVsScreenHealth_AtStart(void)
{
    u16 flags = 0;
    s32 i;

    BUFFER_PARTY_VS_SCREEN_STATUS(gPlayerParty, flags, i);
    gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsLo = flags;
    *(&gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsHi) = flags >> 8;
}

/*static const u8 sFlailHpScaleToPowerTable[] =
{
    1, 200,
    4, 150,
    9, 100,
    16, 80,
    32, 40,
    48, 20
};*/

// format: min. weight (hectograms), base power
static const u16 sWeightToDamageTable[] =
{
    100, 20,
    250, 40,
    500, 60,
    1000, 80,
    2000, 100,
    0xFFFF, 0xFFFF
};

static const u8 sSpeedDiffPowerTable[] = {40, 60, 80, 120, 150};
static const u8 sHeatCrashPowerTable[] = {40, 40, 60, 80, 100, 120};
static const u8 sTrumpCardPowerTable[] = {200, 80, 60, 50, 40};

const struct TypePower gNaturalGiftTable[] =
{
    [ITEM_TO_BERRY(ITEM_CHERI_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_CHESTO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_PECHA_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RAWST_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_ASPEAR_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_LEPPA_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_ORAN_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_PERSIM_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_LUM_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_SITRUS_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_FIGY_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_WIKI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_MAGO_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_AGUAV_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_IAPAPA_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_RAZZ_BERRY)] = {TYPE_STEEL, 80},
    /*[ITEM_TO_BERRY(ITEM_OCCA_BERRY)] = {TYPE_FIRE, 80},
    [ITEM_TO_BERRY(ITEM_PASSHO_BERRY)] = {TYPE_WATER, 80},
    [ITEM_TO_BERRY(ITEM_WACAN_BERRY)] = {TYPE_ELECTRIC, 80},
    [ITEM_TO_BERRY(ITEM_RINDO_BERRY)] = {TYPE_GRASS, 80},
    [ITEM_TO_BERRY(ITEM_YACHE_BERRY)] = {TYPE_ICE, 80},
    [ITEM_TO_BERRY(ITEM_CHOPLE_BERRY)] = {TYPE_FIGHTING, 80},
    [ITEM_TO_BERRY(ITEM_KEBIA_BERRY)] = {TYPE_POISON, 80},
    [ITEM_TO_BERRY(ITEM_SHUCA_BERRY)] = {TYPE_GROUND, 80},
    [ITEM_TO_BERRY(ITEM_COBA_BERRY)] = {TYPE_FLYING, 80},
    [ITEM_TO_BERRY(ITEM_PAYAPA_BERRY)] = {TYPE_PSYCHIC, 80},
    [ITEM_TO_BERRY(ITEM_TANGA_BERRY)] = {TYPE_BUG, 80},
    [ITEM_TO_BERRY(ITEM_CHARTI_BERRY)] = {TYPE_ROCK, 80},
    [ITEM_TO_BERRY(ITEM_KASIB_BERRY)] = {TYPE_GHOST, 80},
    [ITEM_TO_BERRY(ITEM_HABAN_BERRY)] = {TYPE_DRAGON, 80},
    [ITEM_TO_BERRY(ITEM_COLBUR_BERRY)] = {TYPE_DARK, 80},
    [ITEM_TO_BERRY(ITEM_BABIRI_BERRY)] = {TYPE_STEEL, 80},
    [ITEM_TO_BERRY(ITEM_CHILAN_BERRY)] = {TYPE_NORMAL, 80},
    [ITEM_TO_BERRY(ITEM_ROSELI_BERRY)] = {TYPE_FAIRY, 80},*/
    [ITEM_TO_BERRY(ITEM_BLUK_BERRY)] = {TYPE_FIRE, 90},
    [ITEM_TO_BERRY(ITEM_NANAB_BERRY)] = {TYPE_WATER, 90},
    [ITEM_TO_BERRY(ITEM_WEPEAR_BERRY)] = {TYPE_ELECTRIC, 90},
    [ITEM_TO_BERRY(ITEM_PINAP_BERRY)] = {TYPE_GRASS, 90},
    [ITEM_TO_BERRY(ITEM_POMEG_BERRY)] = {TYPE_ICE, 90},
    [ITEM_TO_BERRY(ITEM_KELPSY_BERRY)] = {TYPE_FIGHTING, 90},
    [ITEM_TO_BERRY(ITEM_QUALOT_BERRY)] = {TYPE_POISON, 90},
    [ITEM_TO_BERRY(ITEM_HONDEW_BERRY)] = {TYPE_GROUND, 90},
    [ITEM_TO_BERRY(ITEM_GREPA_BERRY)] = {TYPE_FLYING, 90},
    [ITEM_TO_BERRY(ITEM_TAMATO_BERRY)] = {TYPE_PSYCHIC, 90},
    [ITEM_TO_BERRY(ITEM_CORNN_BERRY)] = {TYPE_BUG, 90},
    [ITEM_TO_BERRY(ITEM_MAGOST_BERRY)] = {TYPE_ROCK, 90},
    [ITEM_TO_BERRY(ITEM_RABUTA_BERRY)] = {TYPE_GHOST, 90},
    [ITEM_TO_BERRY(ITEM_NOMEL_BERRY)] = {TYPE_DRAGON, 90},
    [ITEM_TO_BERRY(ITEM_SPELON_BERRY)] = {TYPE_DARK, 90},
    [ITEM_TO_BERRY(ITEM_PAMTRE_BERRY)] = {TYPE_STEEL, 90},
    [ITEM_TO_BERRY(ITEM_WATMEL_BERRY)] = {TYPE_FIRE, 100},
    [ITEM_TO_BERRY(ITEM_DURIN_BERRY)] = {TYPE_WATER, 100},
    [ITEM_TO_BERRY(ITEM_BELUE_BERRY)] = {TYPE_ELECTRIC, 100},
    [ITEM_TO_BERRY(ITEM_LIECHI_BERRY)] = {TYPE_GRASS, 100},
    [ITEM_TO_BERRY(ITEM_GANLON_BERRY)] = {TYPE_ICE, 100},
    [ITEM_TO_BERRY(ITEM_SALAC_BERRY)] = {TYPE_FIGHTING, 100},
    [ITEM_TO_BERRY(ITEM_PETAYA_BERRY)] = {TYPE_POISON, 100},
    [ITEM_TO_BERRY(ITEM_APICOT_BERRY)] = {TYPE_GROUND, 100},
    [ITEM_TO_BERRY(ITEM_LANSAT_BERRY)] = {TYPE_FLYING, 100},
    [ITEM_TO_BERRY(ITEM_STARF_BERRY)] = {TYPE_PSYCHIC, 100},
    [ITEM_TO_BERRY(ITEM_ENIGMA_BERRY)] = {TYPE_BUG, 100},
    /*[ITEM_TO_BERRY(ITEM_MICLE_BERRY)] = {TYPE_ROCK, 100},
    [ITEM_TO_BERRY(ITEM_CUSTAP_BERRY)] = {TYPE_GHOST, 100},
    [ITEM_TO_BERRY(ITEM_JABOCA_BERRY)] = {TYPE_DRAGON, 100},
    [ITEM_TO_BERRY(ITEM_ROWAP_BERRY)] = {TYPE_DARK, 100},
    [ITEM_TO_BERRY(ITEM_KEE_BERRY)] = {TYPE_FAIRY, 100},
    [ITEM_TO_BERRY(ITEM_MARANGA_BERRY)] = {TYPE_DARK, 100},*/
};

static void SetPlayerBerryDataInBattleStruct(void)
{
    s32 i;
    struct BattleStruct *battleStruct = gBattleStruct;
    struct BattleEnigmaBerry *battleBerry = &battleStruct->multiBuffer.linkPartnerHeader.battleEnigmaBerry;

    if (IsEnigmaBerryValid() == TRUE)
    {
        for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            battleBerry->name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
        battleBerry->name[i] = EOS;
        for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            battleBerry->itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
        battleBerry->holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
        battleBerry->holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
    }
    else
    {
        const struct Berry *berryData = GetBerryInfo(ItemIdToBerryType(ITEM_ENIGMA_BERRY));

        for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            battleBerry->name[i] = berryData->name[i];
        battleBerry->name[i] = EOS;
        for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            battleBerry->itemEffect[i] = 0;
        battleBerry->holdEffect = HOLD_EFFECT_NONE;
        battleBerry->holdEffectParam = 0;
    }
}

static void SetAllPlayersBerryData(void)
{
    s32 i, j;

    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        if (IsEnigmaBerryValid() == TRUE)
        {
            for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            {
                gEnigmaBerries[0].name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
                gEnigmaBerries[2].name[i] = gSaveBlock1Ptr->enigmaBerry.berry.name[i];
            }
            gEnigmaBerries[0].name[i] = EOS;
            gEnigmaBerries[2].name[i] = EOS;
            for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            {
                gEnigmaBerries[0].itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
                gEnigmaBerries[2].itemEffect[i] = gSaveBlock1Ptr->enigmaBerry.itemEffect[i];
            }
            gEnigmaBerries[0].holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
            gEnigmaBerries[2].holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
            gEnigmaBerries[0].holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
            gEnigmaBerries[2].holdEffectParam = gSaveBlock1Ptr->enigmaBerry.holdEffectParam;
        }
        else
        {
            const struct Berry *berryData = GetBerryInfo(ItemIdToBerryType(ITEM_ENIGMA_BERRY));

            for (i = 0; i < BERRY_NAME_LENGTH; ++i)
            {
                gEnigmaBerries[0].name[i] = berryData->name[i];
                gEnigmaBerries[2].name[i] = berryData->name[i];
            }
            gEnigmaBerries[0].name[i] = EOS;
            gEnigmaBerries[2].name[i] = EOS;
            for (i = 0; i < BERRY_ITEM_EFFECT_COUNT; ++i)
            {
                gEnigmaBerries[0].itemEffect[i] = 0;
                gEnigmaBerries[2].itemEffect[i] = 0;
            }
            gEnigmaBerries[0].holdEffect = HOLD_EFFECT_NONE;
            gEnigmaBerries[2].holdEffect = HOLD_EFFECT_NONE;
            gEnigmaBerries[0].holdEffectParam = 0;
            gEnigmaBerries[2].holdEffectParam = 0;
        }
    }
    else
    {
        s32 numPlayers;
        struct BattleEnigmaBerry *src;
        u8 battlerId;

        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            for (i = 0; i < 4; ++i)
            {
                src = (struct BattleEnigmaBerry *)(gBlockRecvBuffer[i] + 2);
                battlerId = gLinkPlayers[i].id;
                for (j = 0; j < BERRY_NAME_LENGTH; ++j)
                    gEnigmaBerries[battlerId].name[j] = src->name[j];
                gEnigmaBerries[battlerId].name[j] = EOS;
                for (j = 0; j < BERRY_ITEM_EFFECT_COUNT; ++j)
                    gEnigmaBerries[battlerId].itemEffect[j] = src->itemEffect[j];
                gEnigmaBerries[battlerId].holdEffect = src->holdEffect;
                gEnigmaBerries[battlerId].holdEffectParam = src->holdEffectParam;
            }
        }
        else
        {
            for (i = 0; i < 2; ++i)
            {
                src = (struct BattleEnigmaBerry *)(gBlockRecvBuffer[i] + 2);
                for (j = 0; j < BERRY_NAME_LENGTH; ++j)
                {
                    gEnigmaBerries[i].name[j] = src->name[j];
                    gEnigmaBerries[i + 2].name[j] = src->name[j];
                }
                gEnigmaBerries[i].name[j] = EOS;
                gEnigmaBerries[i + 2].name[j] = EOS;
                for (j = 0; j < BERRY_ITEM_EFFECT_COUNT; ++j)
                {
                    gEnigmaBerries[i].itemEffect[j] = src->itemEffect[j];
                    gEnigmaBerries[i + 2].itemEffect[j] = src->itemEffect[j];
                }
                gEnigmaBerries[i].holdEffect = src->holdEffect;
                gEnigmaBerries[i + 2].holdEffect = src->holdEffect;
                gEnigmaBerries[i].holdEffectParam = src->holdEffectParam;
                gEnigmaBerries[i + 2].holdEffectParam = src->holdEffectParam;
            }
        }
    }
}

static void HandleAction_WaitTurnEnd(void) {
    if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
    {
        gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
        PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, *(gBattleStruct->battlerPartyIndexes + gBattlerAttacker));
        gBattleScripting.battler = gBattlerAttacker;
        gBattlescriptCurrInstr = BattleScript_SkipTurn;
        gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
        //gCurrentActionFuncId = B_ACTION_FINISHED;
        //++gCurrentTurnActionNumber;
    }
}

#define LOGIC_FOR_MOVETYPE_CHANGE
void SetTypeBeforeUsingMove(u16 move, u8 battlerAtk)
{
    u32 moveType, ateType, attackerAbility;
    u16 holdEffect = GetBattlerHoldEffect(battlerAtk, TRUE);

    if (move == (MOVE_STRUGGLE || MOVE_BIDE)) 
        return;

    gBattleStruct->dynamicMoveType = 0;
    gBattleStruct->ateBoost[battlerAtk] = 0;
    gSpecialStatuses[battlerAtk].gemBoost = FALSE;

    
    if (gBattleMoves[move].effect == EFFECT_CHANGE_TYPE_ON_ITEM)
    {
        if (holdEffect == gBattleMoves[move].argument)
            gBattleStruct->dynamicMoveType = ItemId_GetSecondaryId(gBattleMons[battlerAtk].item);// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_REVELATION_DANCE)
    {
        if (gBattleMons[battlerAtk].type1 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type1;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type2 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type2;// | F_DYNAMIC_TYPE_2;
        else if (gBattleMons[battlerAtk].type3 != TYPE_MYSTERY)
            gBattleStruct->dynamicMoveType = gBattleMons[battlerAtk].type3;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].effect == EFFECT_NATURAL_GIFT)
    {
        if (ItemId_GetPocket(gBattleMons[battlerAtk].item) == POCKET_BERRY_POUCH)
            gBattleStruct->dynamicMoveType = gNaturalGiftTable[ITEM_TO_BERRY(gBattleMons[battlerAtk].item)].type;
    }
    else if (gBattleMoves[move].effect == EFFECT_TERRAIN_PULSE)
    {
        if (IsBattlerTerrainAffected(battlerAtk, STATUS_FIELD_TERRAIN_ANY))
        {
            if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_GRASS;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_FAIRY;// | F_DYNAMIC_TYPE_2;
            else if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN)
                gBattleStruct->dynamicMoveType = TYPE_PSYCHIC;// | F_DYNAMIC_TYPE_2;
            else //failsafe
                gBattleStruct->dynamicMoveType = TYPE_NORMAL;// | F_DYNAMIC_TYPE_2;
        }
    }

    attackerAbility = GetBattlerAbility(battlerAtk);
    GET_MOVE_TYPE(move, moveType);
    if ((gFieldStatuses & STATUS_FIELD_ION_DELUGE && moveType == TYPE_NORMAL)
        || gStatuses4[battlerAtk] & STATUS4_ELECTRIFIED)
    {
        gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;   //need test if these work without this extra value
    }
    else if (gBattleMoves[move].type == TYPE_NORMAL
             && gBattleMoves[move].effect != EFFECT_HIDDEN_POWER
             && gBattleMoves[move].effect != EFFECT_WEATHER_BALL
             && gBattleMoves[move].effect != EFFECT_CHANGE_TYPE_ON_ITEM
             && gBattleMoves[move].effect != EFFECT_NATURAL_GIFT
             && ((attackerAbility == ABILITY_PIXILATE && (ateType = TYPE_FAIRY))
                 || (attackerAbility == ABILITY_REFRIGERATE && (ateType = TYPE_ICE))
                 || (attackerAbility == ABILITY_AERILATE && (ateType = TYPE_FLYING))
                 || ((attackerAbility == ABILITY_GALVANIZE) && (ateType = TYPE_ELECTRIC))))
    {
        gBattleStruct->dynamicMoveType = ateType;// | F_DYNAMIC_TYPE_2; //above should do type change already, dmg boosts are already in pokemon.c
        gBattleStruct->ateBoost[battlerAtk] = 1;
    }
    else if (gBattleMoves[move].type != TYPE_NORMAL
             && gBattleMoves[move].effect != EFFECT_HIDDEN_POWER
             && gBattleMoves[move].effect != EFFECT_WEATHER_BALL
             && attackerAbility == ABILITY_NORMALIZE)   //thought to remove normal exclusion, but would just result in them getting much weaker
    {                                                   //without stab, so not worth
        gBattleStruct->dynamicMoveType = TYPE_MYSTERY;// | F_DYNAMIC_TYPE_2;    //WILL MAke moves do neutral damage to everything, need exclude from joat.
        gBattleStruct->ateBoost[battlerAtk] = 1;
    }
    else if (gBattleMoves[move].flags & FLAG_SOUND
             && attackerAbility == ABILITY_LIQUID_VOICE)
    {
        gBattleStruct->dynamicMoveType = TYPE_WATER;// | F_DYNAMIC_TYPE_2;
    }
    else if (gBattleMoves[move].type == TYPE_WATER
        && attackerAbility == ABILITY_LIQUID_SOUL)
    {
        gBattleStruct->dynamicMoveType = TYPE_GHOST;// | F_DYNAMIC_TYPE_2;
    }
    else if (gStatuses4[battlerAtk] & STATUS4_PLASMA_FISTS && moveType == TYPE_NORMAL)
    {
        gBattleStruct->dynamicMoveType = TYPE_ELECTRIC;// | F_DYNAMIC_TYPE_2;
    }
    else if (move == MOVE_AURA_WHEEL && gBattleMons[battlerAtk].species == SPECIES_MORPEKO_HANGRY)
    {
        gBattleStruct->dynamicMoveType = TYPE_DARK;// | F_DYNAMIC_TYPE_2;
    }

    // Check if a gem should activate.
    GET_MOVE_TYPE(move, moveType);
    if (holdEffect == HOLD_EFFECT_GEMS
        && moveType == ItemId_GetSecondaryId(gBattleMons[battlerAtk].item))
    {
        gSpecialStatuses[battlerAtk].gemParam = GetBattlerHoldEffectParam(battlerAtk);
        gSpecialStatuses[battlerAtk].gemBoost = TRUE;
    }
}

static void LinkBattleComputeBattleTypeFlags(u8 numPlayers, u8 multiPlayerId)
{
    u8 found = 0;

    // If player 1 is playing the minimum version, player 1 is master.
    if (gBlockRecvBuffer[0][0] == 0x100)
    {
        if (multiPlayerId == 0)
            gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
        else
            gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
        ++found;
    }
    if (found == 0)
    {
        // If multiple different versions are being used, player 1 is master.
        s32 i;

        for (i = 0; i < numPlayers; ++i)
            if (gBlockRecvBuffer[0][0] != gBlockRecvBuffer[i][0])
                break;
        if (i == numPlayers)
        {
            if (multiPlayerId == 0)
                gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
            else
                gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
            ++found;
        }
        if (found == 0)
        {
            // Lowest index player with the highest game version is master.
            for (i = 0; i < numPlayers; ++i)
            {
                if (gBlockRecvBuffer[i][0] == 0x201 && i != multiPlayerId)
                    if (i < multiPlayerId)
                        break;
                if (gBlockRecvBuffer[i][0] > 0x201 && i != multiPlayerId)
                    break;
            }
            if (i == numPlayers)
                gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER | BATTLE_TYPE_TRAINER;
            else
                gBattleTypeFlags |= BATTLE_TYPE_TRAINER;
        }
    }
}

static void CB2_HandleStartBattle(void)
{
    u8 playerMultiplayerId;
    u8 enemyMultiplayerId;

    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    playerMultiplayerId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplayerId;
    enemyMultiplayerId = playerMultiplayerId ^ BIT_SIDE;
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            BattleInterfaceSetWindowPals();
            gBattleCommunication[MULTIUSE_STATE] = 1;
        }
        if (gWirelessCommType)
            LoadWirelessStatusIndicatorSpriteGfx();
        break;
    case 1:
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        {
            if (gReceivedRemoteLinkPlayers)
            {
                if (IsLinkTaskFinished())
                {
                    // 0x201
                    *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureLo) = 1;
                    *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureHi) = 2;
                    BufferPartyVsScreenHealth_AtStart();
                    SetPlayerBerryDataInBattleStruct();
                    SendBlock(bitmask_all_link_players_but_self(), &gBattleStruct->multiBuffer.linkPartnerHeader, sizeof(gBattleStruct->multiBuffer.linkPartnerHeader));
                    gBattleCommunication[MULTIUSE_STATE] = 2;
                }
                if (gWirelessCommType != 0)
                    CreateWirelessStatusIndicatorSprite(0, 0);
            }
        }
        else
        {
            gBattleTypeFlags |= BATTLE_TYPE_IS_MASTER;
            gBattleCommunication[MULTIUSE_STATE] = 15;
            SetAllPlayersBerryData();
        }
        break; 
    case 2:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            u8 taskId;

            ResetBlockReceivedFlags();
            LinkBattleComputeBattleTypeFlags(2, playerMultiplayerId);
            SetAllPlayersBerryData();
            taskId = CreateTask(InitLinkBattleVsScreen, 0);
            gTasks[taskId].data[1] = 270;
            gTasks[taskId].data[2] = 90;
            gTasks[taskId].data[5] = 0;
            gTasks[taskId].data[3] = gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsLo | (gBattleStruct->multiBuffer.linkPartnerHeader.vsScreenHealthFlagsHi << 8);
            gTasks[taskId].data[4] = gBlockRecvBuffer[enemyMultiplayerId][1];
            SetDeoxysStats();
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 3:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 4:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 7:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty + 2, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 8:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty + 2, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 11:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gPlayerParty + 4, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 12:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            ResetBlockReceivedFlags();
            memcpy(gEnemyParty + 4, gBlockRecvBuffer[enemyMultiplayerId], sizeof(struct Pokemon) * 2);
            TryCorrectShedinjaLanguage(&gEnemyParty[0]);
            TryCorrectShedinjaLanguage(&gEnemyParty[1]);
            TryCorrectShedinjaLanguage(&gEnemyParty[2]);
            TryCorrectShedinjaLanguage(&gEnemyParty[3]);
            TryCorrectShedinjaLanguage(&gEnemyParty[4]);
            TryCorrectShedinjaLanguage(&gEnemyParty[5]);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 15:
        InitBtlControllers();
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
        gBattleCommunication[SPRITES_INIT_STATE2] = 0;
        break;
    case 16:
        if (BattleInitAllSprites(&gBattleCommunication[SPRITES_INIT_STATE1], &gBattleCommunication[SPRITES_INIT_STATE2]))
        {
            gPreBattleCallback1 = gMain.callback1;
            gMain.callback1 = BattleMainCB1;
            SetMainCallback2(BattleMainCB2);
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
            {
                gBattleTypeFlags |= BATTLE_TYPE_20;
            }
        }
        break;
    case 5:
    case 9:
    case 13:
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[1] = 1;
    case 6:
    case 10:
    case 14:
        if (--gBattleCommunication[1] == 0)
            ++gBattleCommunication[MULTIUSE_STATE];
        break;
    }
}

static void PrepareOwnMultiPartnerBuffer(void)
{
    s32 i, j;
    u8 *nick, *cur;

    for (i = 0; i < 3; ++i)
    {
        gMultiPartnerParty[i].species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        gMultiPartnerParty[i].heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
        nick = gMultiPartnerParty[i].nickname;
        GetMonData(&gPlayerParty[i], MON_DATA_NICKNAME, nick);
        gMultiPartnerParty[i].level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
        gMultiPartnerParty[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
        gMultiPartnerParty[i].maxhp = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);
        gMultiPartnerParty[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
        gMultiPartnerParty[i].personality = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY);
        gMultiPartnerParty[i].gender = GetMonGender(&gPlayerParty[i]);
        StripExtCtrlCodes(nick);
        if (GetMonData(&gPlayerParty[i], MON_DATA_LANGUAGE) != LANGUAGE_JAPANESE)
        {
            for (cur = nick, j = 0; cur[j] != EOS; ++j)
                ;
            while (j < 6)
                cur[j++] = 0;
            cur[j] = EOS;
        }
    }
    memcpy(gBattleStruct->multiBuffer.multiBattleMons, gMultiPartnerParty, sizeof(gMultiPartnerParty));
}

static void CB2_PreInitMultiBattle(void)
{
    s32 i;
    u8 playerMultiplierId;
    u8 r4 = 0xF;
    u16 *savedBattleTypeFlags;
    void (**savedCallback)(void);

    playerMultiplierId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplierId;
    savedCallback = &gBattleStruct->savedCallback;
    savedBattleTypeFlags = &gBattleStruct->savedBattleTypeFlags;

    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (gReceivedRemoteLinkPlayers && IsLinkTaskFinished())
        {
            PrepareOwnMultiPartnerBuffer();
            SendBlock(bitmask_all_link_players_but_self(), gBattleStruct->multiBuffer.multiBattleMons, sizeof(gBattleStruct->multiBuffer.multiBattleMons));
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 1:
        if ((GetBlockReceivedStatus() & r4) == r4)
        {
            ResetBlockReceivedFlags();
            for (i = 0; i < 4; ++i)
            {
                if (i == playerMultiplierId)
                    continue;
                if ((!(gLinkPlayers[i].id & 1) && !(gLinkPlayers[playerMultiplierId].id & 1))
                 || (gLinkPlayers[i].id & 1 && gLinkPlayers[playerMultiplierId].id & 1))
                    memcpy(gMultiPartnerParty, gBlockRecvBuffer[i], sizeof(gMultiPartnerParty));
            }
            ++gBattleCommunication[MULTIUSE_STATE];
            *savedCallback = gMain.savedCallback;
            *savedBattleTypeFlags = gBattleTypeFlags;
            gMain.savedCallback = CB2_PreInitMultiBattle;
            ShowPartyMenuToShowcaseMultiBattleParty();
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            ++gBattleCommunication[MULTIUSE_STATE];
            if (gWirelessCommType)
                SetLinkStandbyCallback();
            else
                SetCloseLinkCallback();
        }
        break;
    case 3:
        if (gWirelessCommType)
        {
            if (IsLinkRfuTaskFinished())
            {
                gBattleTypeFlags = *savedBattleTypeFlags;
                gMain.savedCallback = *savedCallback;
                SetMainCallback2(CB2_InitBattleInternal);
            }
        }
        else if (!gReceivedRemoteLinkPlayers)
        {
            gBattleTypeFlags = *savedBattleTypeFlags;
            gMain.savedCallback = *savedCallback;
            SetMainCallback2(CB2_InitBattleInternal);
        }
        break;
    }
}

static void CB2_HandleStartMultiBattle(void)
{
    u8 playerMultiplayerId;
    s32 id;
    u8 taskId;

    playerMultiplayerId = GetMultiplayerId();
    gBattleStruct->multiplayerId = playerMultiplayerId;
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            BattleInterfaceSetWindowPals();
            gBattleCommunication[MULTIUSE_STATE] = 1;
        }
        if (gWirelessCommType)
            LoadWirelessStatusIndicatorSpriteGfx();
        break;
    case 1:
        if (gReceivedRemoteLinkPlayers)
        {
            if (IsLinkTaskFinished())
            {
                // 0x201
                *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureLo) = 1;
                *(&gBattleStruct->multiBuffer.linkPartnerHeader.versionSignatureHi) = 2;
                BufferPartyVsScreenHealth_AtStart();
                SetPlayerBerryDataInBattleStruct();
                SendBlock(bitmask_all_link_players_but_self(), &gBattleStruct->multiBuffer.linkPartnerHeader, sizeof(gBattleStruct->multiBuffer.linkPartnerHeader));
                ++gBattleCommunication[MULTIUSE_STATE];
            }
            if (gWirelessCommType)
                CreateWirelessStatusIndicatorSprite(0, 0);
        }
        break; 
    case 2:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            LinkBattleComputeBattleTypeFlags(4, playerMultiplayerId);
            SetAllPlayersBerryData();
            SetDeoxysStats();
            memcpy(gDecompressionBuffer, gPlayerParty, sizeof(struct Pokemon) * 3);
            taskId = CreateTask(InitLinkBattleVsScreen, 0);
            gTasks[taskId].data[1] = 270;
            gTasks[taskId].data[2] = 90;
            gTasks[taskId].data[5] = 0;
            gTasks[taskId].data[3] = 0;
            gTasks[taskId].data[4] = 0;
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                switch (gLinkPlayers[id].id)
                {
                case 0:
                    gTasks[taskId].data[3] |= gBlockRecvBuffer[id][1] & 0x3F;
                    break;
                case 1:
                    gTasks[taskId].data[4] |= gBlockRecvBuffer[id][1] & 0x3F;
                    break;
                case 2:
                    gTasks[taskId].data[3] |= (gBlockRecvBuffer[id][1] & 0x3F) << 6;
                    break;
                case 3:
                    gTasks[taskId].data[4] |= (gBlockRecvBuffer[id][1] & 0x3F) << 6;
                    break;
                }
            }
            ZeroPlayerPartyMons();
            ZeroEnemyPartyMons();
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        else
        {
            break;
        }
        // fall through
    case 3:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gDecompressionBuffer, sizeof(struct Pokemon) * 2);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 4:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                if (id == playerMultiplayerId)
                {
                    switch (gLinkPlayers[id].id)
                    {
                    case 0:
                    case 3:
                        memcpy(gPlayerParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                        break;
                    case 1:
                    case 2:
                        memcpy(gPlayerParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                        break;
                    }
                }
                else
                {
                    if ((!(gLinkPlayers[id].id & 1) && !(gLinkPlayers[playerMultiplayerId].id & 1))
                     || ((gLinkPlayers[id].id & 1) && (gLinkPlayers[playerMultiplayerId].id & 1)))
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gPlayerParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        case 1:
                        case 2:
                            memcpy(gPlayerParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        }
                    }
                    else
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gEnemyParty, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        case 1:
                        case 2:
                            memcpy(gEnemyParty + 3, gBlockRecvBuffer[id], sizeof(struct Pokemon) * 2);
                            break;
                        }
                    }
                }
            }
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 7:
        if (IsLinkTaskFinished())
        {
            SendBlock(bitmask_all_link_players_but_self(), gDecompressionBuffer + sizeof(struct Pokemon) * 2, sizeof(struct Pokemon));
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break; 
    case 8:
        if ((GetBlockReceivedStatus() & 0xF) == 0xF)
        {
            ResetBlockReceivedFlags();
            for (id = 0; id < MAX_LINK_PLAYERS; ++id)
            {
                if (id == playerMultiplayerId)
                {
                    switch (gLinkPlayers[id].id)
                    {
                    case 0:
                    case 3:
                        memcpy(gPlayerParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                        break;
                    case 1:
                    case 2:
                        memcpy(gPlayerParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                        break;
                    }
                }
                else
                {
                    if ((!(gLinkPlayers[id].id & 1) && !(gLinkPlayers[playerMultiplayerId].id & 1))
                     || ((gLinkPlayers[id].id & 1) && (gLinkPlayers[playerMultiplayerId].id & 1)))
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gPlayerParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        case 1:
                        case 2:
                            memcpy(gPlayerParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        }
                    }
                    else
                    {
                        switch (gLinkPlayers[id].id)
                        {
                        case 0:
                        case 3:
                            memcpy(gEnemyParty + 2, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        case 1:
                        case 2:
                            memcpy(gEnemyParty + 5, gBlockRecvBuffer[id], sizeof(struct Pokemon));
                            break;
                        }
                    }
                }
            } 
            TryCorrectShedinjaLanguage(&gPlayerParty[0]);
            TryCorrectShedinjaLanguage(&gPlayerParty[1]);
            TryCorrectShedinjaLanguage(&gPlayerParty[2]);
            TryCorrectShedinjaLanguage(&gPlayerParty[3]);
            TryCorrectShedinjaLanguage(&gPlayerParty[4]);
            TryCorrectShedinjaLanguage(&gPlayerParty[5]);
            TryCorrectShedinjaLanguage(&gEnemyParty[0]);
            TryCorrectShedinjaLanguage(&gEnemyParty[1]);
            TryCorrectShedinjaLanguage(&gEnemyParty[2]);
            TryCorrectShedinjaLanguage(&gEnemyParty[3]);
            TryCorrectShedinjaLanguage(&gEnemyParty[4]);
            TryCorrectShedinjaLanguage(&gEnemyParty[5]);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 11:
        InitBtlControllers();
        ++gBattleCommunication[MULTIUSE_STATE];
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
        gBattleCommunication[SPRITES_INIT_STATE2] = 0;
        break;
    case 12:
        if (BattleInitAllSprites(&gBattleCommunication[SPRITES_INIT_STATE1], &gBattleCommunication[SPRITES_INIT_STATE2]))
        {
            gPreBattleCallback1 = gMain.callback1;
            gMain.callback1 = BattleMainCB1;
            SetMainCallback2(BattleMainCB2);
            if (gBattleTypeFlags & BATTLE_TYPE_LINK)
                gBattleTypeFlags |= BATTLE_TYPE_20;
        }
        break;
    case 5:
    case 9:
        ++gBattleCommunication[0];
        gBattleCommunication[SPRITES_INIT_STATE1] = 1;
        // fall through
    case 6:
    case 10:
        if (--gBattleCommunication[SPRITES_INIT_STATE1] == 0)
            ++gBattleCommunication[0];
        break;
    }
}

void BattleMainCB2(void)
{
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
    RunTasks();
    if (JOY_HELD(B_BUTTON) && gBattleTypeFlags & BATTLE_TYPE_POKEDUDE)
    {
        gSpecialVar_Result = gBattleOutcome = B_OUTCOME_DREW;
        ResetPaletteFadeControl();
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        SetMainCallback2(CB2_QuitPokedudeBattle);
    }
}

void FreeRestoreBattleData(void)
{
    gMain.callback1 = gPreBattleCallback1;
    gScanlineEffect.state = 3;
    gMain.inBattle = FALSE;
    ZeroEnemyPartyMons();
    m4aSongNumStop(SE_LOW_HEALTH);
    FreeMonSpritesGfx();
    FreeBattleSpritesData();
    FreeBattleResources();
}

static void CB2_QuitPokedudeBattle(void)
{
    UpdatePaletteFade();
    if (!gPaletteFade.active)
    {
        FreeRestoreBattleData();
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void SpriteCB_UnusedDebugSprite(struct Sprite *sprite)
{
    sprite->data[0] = 0;
    sprite->callback = SpriteCB_UnusedDebugSprite_Step;
}

static void SpriteCB_UnusedDebugSprite_Step(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        sUnknownDebugSpriteDataBuffer = AllocZeroed(0x1000);
        ++sprite->data[0];
        sprite->data[1] = 0;
        sprite->data[2] = 0x281;
        sprite->data[3] = 0;
        sprite->data[4] = 1;
        // fall through
    case 1:
        if (--sprite->data[4] == 0)
        {
            s32 i, r2, r0;

            sprite->data[4] = 2;
            r2 = sprite->data[1] + sprite->data[3] * 32;
            r0 = sprite->data[2] - sprite->data[3] * 32;
            for (i = 0; i <= 29; i += 2)
            {
                *(&sUnknownDebugSpriteDataBuffer[r2] + i) = 0x3D;
                *(&sUnknownDebugSpriteDataBuffer[r0] + i) = 0x3D;
            }
            if (++sprite->data[3] == 21)
            {
                ++sprite->data[0];
                sprite->data[1] = 32;
            }
        }
        break;
    case 2:
        if (--sprite->data[1] == 20)
        {
            if (sUnknownDebugSpriteDataBuffer != NULL)
            {
                memset(sUnknownDebugSpriteDataBuffer, 0, 0x1000);
                FREE_AND_SET_NULL(sUnknownDebugSpriteDataBuffer);
            }
            SetMainCallback2(CB2_InitBattle);
        }
        break;
    }
}

bool8 IsRivalBattle(u16 trainerNum)
{
    u8 trainerClass = gTrainers[trainerNum].trainerClass;
    if (trainerClass == CLASS_RIVAL || trainerClass == CLASS_RIVAL_2 || trainerClass == CLASS_CHAMPION_2)
        return TRUE;
    else
        return FALSE;
}

#define TRAINER_PARTY_DATA
static u8 CreateNPCTrainerParty(struct Pokemon *party, u16 trainerNum)
{
    u32 nameHash = 0;
    u8 RandomAbility = Random() % 4;    //to put in setmondata dataarg to hopefully set random ability slot 0-3
    u32 personalityValue; //personality now uses name hash, which is trainer name
    u8 fixedIV; //figure how to set personality for individual pokemon, or at least set their ability
    u8 abilityNum;  //should let set ability slot for mon
    u16 totalEVs = 0;
    u16 evs[NUM_EV_STATS];
    u16 species;
    s32 i, j;
    int l = 0;
    u16 targetSpecies = 0;

    if (trainerNum == TRAINER_SECRET_BASE)
        return 0;
    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
     && !(gBattleTypeFlags & (BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_TRAINER_TOWER)))
    {
        ZeroEnemyPartyMons();
        for (i = 0; i < gTrainers[trainerNum].partySize; ++i)   //uses i, to loop through trainers entir party 
        {

            if (gTrainers[trainerNum].doubleBattle == TRUE)
                personalityValue = 0x80;
            else if (gTrainers[trainerNum].encounterMusic_gender & 0x80)
                personalityValue = 0x78;
            else
                personalityValue = 0x88;
            for (j = 0; gTrainers[trainerNum].trainerName[j] != EOS; ++j)
                nameHash += gTrainers[trainerNum].trainerName[j];
            switch (gTrainers[trainerNum].partyFlags)
            {
            case 0: //evolution works, only issue is if you give the rival multiple instances of the same starter line, with the evolved form first
                //because their both using the same var, it just eliminated the unevolved version of the pokemon if it comes after the evolved form.
            {
                const struct TrainerMonNoItemDefaultMoves *partyData = gTrainers[trainerNum].party.NoItemDefaultMoves;
                if (IsRivalBattle(trainerNum)) // && i == gTrainers[trainerNum].partySize - 1) //probably go back & make a nested function based on the species
                    //of the starter in trainer_parties, it may need to be constant so instead of a variable I'll use a define like weather_hail but for starter 
                    //to set teh species checks it'll be partyData[i].species == StarterEvo_0  up to StarterEvo_2 for last evolution
                    //if species can't evolve target species will be species
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter
                        VarSet(VAR_RIVAL_EVO, 0);   //gaurantees values are different, as species will never be none
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO)) 
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        //if evolution branches preferrably pick the one with type advantage to player starter,
                        //to do this realize I need another var to hold player starter, and use basestates type (playervar) to check its type
                        //to help ai pick evolution     actually only eevee has branch evo

                        //in that case make it based on partydatea.species if its charizard be flareon, if venusaur lefeon or jolteon
                        //and vaporeon if blastoise check what mon I put in lists again I may make the eeveelutions have 2 options per starter group
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, 0);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else
                        species = partyData[i].species;
                }
                else
                    species = partyData[i].species;

                for (j = 0; gSpeciesNames[species][j] != EOS; ++j) //starting from 0, loops through all the species names until it matches for each slot in party
                    nameHash += gSpeciesNames[species][j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;   //I think actually is Ivs, uses weird logic to make fixed iv, think will set to random
                //but if I set it to random, but refight trainers, does it keep the iv distribution or generate a new one..?
                //I'm gonna guess it regenerates, based on how the roamers are handled, where it specifically saves all their data
                //ok setting random but attempt to treat rival starter like roamer so it keeps iv distribution
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS;
                
                //as ability and ev are not part of CreateMon arguments may need to put these two below createmon function to have them take effect. hm,
                //checked against custom move set  and move assignment logic is BELOW createmon so that confirms I need to move createmon up to here.
                //double checked again, and Ivs and Evs need to go BEFORE cretemon as function uses those to do calcstats
                //so for now will leave these where they are I "think" it will work. or just move ability data to below function...
                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs               
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);

                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);//did basic test I THINK this shouldn't break first condition logic, should always be less
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility); //for some reason only worked with u8??
                else                                                              
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);
                break; //&party[i] checks mon slot.   next one checks species for that slot
            }
            case F_TRAINER_PARTY_CUSTOM_MOVESET: //could probably get custom moves working with same trick as above but going to a different array
            { //but that can probably better be solved by getting my smart learnsets up and running
                const struct TrainerMonNoItemCustomMoves *partyData = gTrainers[trainerNum].party.NoItemCustomMoves;
                if (IsRivalBattle(trainerNum)) 
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter
                        VarSet(VAR_RIVAL_EVO, 0);
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO)) 
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, 0);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else
                        species = partyData[i].species;
                }
                else
                    species = partyData[i].species;

                for (j = 0; gSpeciesNames[species][j] != EOS; ++j)
                    nameHash += gSpeciesNames[species][j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS;
                
               /* //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);

                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);//did basic test I THINK this shouldn't break first condition logic, should always be less
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);

                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                for (j = 0; j < MAX_MON_MOVES; ++j) //max moves is 4, .moves field is size 4, so loop is to loop through all possible moves
                {
                    SetMonData(&party[i], MON_DATA_MOVE1 + j, &partyData[i].moves[j]); //actually I need custom moves, otherwise its not a good base
                    SetMonData(&party[i], MON_DATA_PP1 + j, &gBattleMoves[partyData[i].moves[j]].pp); //so I need a way to change how this works

                    if (partyData[i].moves[0] == MOVE_NONE) //hopefully this'll do what I want. set to default moves, if mon has none set
                        GiveMonInitialMoveset(&party[i]);
                }
                break; //like custom moves for some, but if its blank just give them default moves.  I think it defaults to 0, if nothing is there.
                //so making it break if move is move_none should let it default to normal learnset.?

                //note, to change battle type, i.e custom moves no item, etc. need to change trainer.h & trainer_parties.h files
            }
            case F_TRAINER_PARTY_HELD_ITEM: //make choose ai flags for individual pokemon, instead of party/trainer
            { //also add pp bonus setting to custom moves,for more strategy/control //important
                const struct TrainerMonItemDefaultMoves *partyData = gTrainers[trainerNum].party.ItemDefaultMoves;
                if (IsRivalBattle(trainerNum)) 
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter
                        VarSet(VAR_RIVAL_EVO, 0);
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO)) 
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, 0);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else
                        species = partyData[i].species;
                }
                else
                    species = partyData[i].species;

                for (j = 0; gSpeciesNames[species][j] != EOS; ++j)
                    nameHash += gSpeciesNames[species][j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)
                    fixedIV = USE_RANDOM_IVS;
                
                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);

                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);//did basic test I THINK this shouldn't break first condition logic, should always be less
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);

                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);
                break;
            }
            case F_TRAINER_PARTY_CUSTOM_MOVESET | F_TRAINER_PARTY_HELD_ITEM:
            {
                const struct TrainerMonItemCustomMoves *partyData = gTrainers[trainerNum].party.ItemCustomMoves;
                if (IsRivalBattle(trainerNum)) 
                {
                    if (partyData[i].species == SPECIES_BULBASAUR
                        || partyData[i].species == SPECIES_SQUIRTLE
                        || partyData[i].species == SPECIES_CHARMANDER)
                    {
                        species = VarGet(VAR_RIVAL_STARTER);  //Set dynamic starter
                        VarSet(VAR_RIVAL_EVO, 0);
                    }
                   else if (partyData[i].species == SPECIES_IVYSAUR
                        || partyData[i].species == SPECIES_WARTORTLE
                        || partyData[i].species == SPECIES_CHARMELEON)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) != VarGet(VAR_RIVAL_EVO)) 
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, targetSpecies);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do first evolution, otherwise stay the same
                            
                        }
                        //check first evo 
                        
                    }
                   else if (partyData[i].species == SPECIES_VENUSAUR
                        || partyData[i].species == SPECIES_BLASTOISE
                        || partyData[i].species == SPECIES_CHARIZARD)
                    {
                        if (VarGet(VAR_RIVAL_STARTER) == VarGet(VAR_RIVAL_EVO))
                        {
                            targetSpecies = gEvolutionTable[VarGet(VAR_RIVAL_STARTER)][l].targetSpecies;
                            if (targetSpecies != SPECIES_NONE) {
                                VarSet(VAR_RIVAL_STARTER, targetSpecies);
                                VarSet(VAR_RIVAL_EVO, 0);
                            }
                            else
                                species = VarGet(VAR_RIVAL_STARTER); //if can evolve do second evolution otherwise stay the same
                        }  //check 2nd evo   //think evo can be set up using the evo loop in the daycare file
                    }
                   else
                        species = partyData[i].species;
                }//need correct logic with this, I think its excluding rivals from the rest of this logic.
                else
                    species = partyData[i].species;

                for (j = 0; gSpeciesNames[species][j] != EOS; ++j)
                    nameHash += gSpeciesNames[species][j];
                personalityValue += nameHash << 8;
                fixedIV = partyData[i].iv;
                if (fixedIV > MAX_PER_STAT_IVS)
                    fixedIV = MAX_PER_STAT_IVS;
                if (fixedIV < MIN_FIXED_IVS)    //for new game plus do flag check and set fixed ivs to max per stat, would require you ev train 
                    fixedIV = USE_RANDOM_IVS;   //mon instead of needing perfect ivs, and ideally you should alraedy have trained mon, and easy access to fast training items.

                /*//Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(Random() % 4));
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &(abilityNum - 1));*/

                //Set Evs
                for (j = 0; j < NUM_EV_STATS; ++j)
                {
                    evs[j] = GetMonData(&party[i], partyData[i].evs[j], NULL);
                    
                    //make identical conditional for each possible value for evs 0-5,

                    switch (j)  //limit conditional
                    {
                    case 0: //hpEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;
                            
                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 1: //attackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 2: //defenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 3: //speedEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 4: //spAttackEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    case 5: //spDefenseEV
                        if (totalEVs >= MAX_TOTAL_EVS)  //prevent addition of more evs
                            break;

                        if (evs[j] > MAX_PER_STAT_EVS) //reduce applied evs to per stat cap
                        {
                            evs[j] = MAX_PER_STAT_EVS;

                        }
                        else if ((totalEVs + evs[j]) > MAX_TOTAL_EVS)//reduce applied evs to dif of applied & total cap, if exceeds max & if below per stat cap 
                        {
                            evs[j] = (MAX_TOTAL_EVS - totalEVs);//did basic test I THINK this shouldn't break first condition logic, should always be less
                        }
                        SetMonData(&party[i], MON_DATA_HP_EV + j, &evs[j]);
                        totalEVs += evs[j]; //increment totalEvs
                        break;
                    }

                }//had to readjust order, as ev set had to go before CreateMon, for Evs to be applied, now matches order of struct as well
                //iv ev lvl species Helditem moves
                CreateMon(&party[i], species, partyData[i].lvl, fixedIV, TRUE, personalityValue, OT_ID_RANDOM_NO_SHINY, 0);
                SetMonData(&party[i], MON_DATA_HELD_ITEM, &partyData[i].heldItem);

                //Set ability slot
                abilityNum = partyData[i].abilityNum;
                if (abilityNum == 0)
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &RandomAbility);
                else
                    SetMonData(&party[i], MON_DATA_ABILITY_NUM, &abilityNum - 1);

                for (j = 0; j < MAX_MON_MOVES; ++j)
                {
                    SetMonData(&party[i], MON_DATA_MOVE1 + j, &partyData[i].moves[j]);
                    SetMonData(&party[i], MON_DATA_PP1 + j, &gBattleMoves[partyData[i].moves[j]].pp);

                    if (partyData[i].moves[0] == MOVE_NONE) //hopefully this'll do what I want. set to default moves, if mon has none set
                        GiveMonInitialMoveset(&party[i]);   //it works!!
                }//works but had to change, to only if moveslot 1 is no move, otherwise it replaced custom setting that has slots set to move_none
            }
            break;
            }   //end of switch case
        }//end of i
       gBattleTypeFlags |= gTrainers[trainerNum].doubleBattle;
    }
    return gTrainers[trainerNum].partySize;
}

// not used
UNUSED static void unused_80116CC(void)
{
    if (REG_VCOUNT < 0xA0 && REG_VCOUNT >= 0x6F)
        REG_BG0CNT = BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(24) | BGCNT_16COLOR | BGCNT_TXT256x512;
}

void VBlankCB_Battle(void)
{
    // Change gRngSeed every vblank.
    Random();
    SetGpuReg(REG_OFFSET_BG0HOFS, gBattle_BG0_X);
    SetGpuReg(REG_OFFSET_BG0VOFS, gBattle_BG0_Y);
    SetGpuReg(REG_OFFSET_BG1HOFS, gBattle_BG1_X);
    SetGpuReg(REG_OFFSET_BG1VOFS, gBattle_BG1_Y);
    SetGpuReg(REG_OFFSET_BG2HOFS, gBattle_BG2_X);
    SetGpuReg(REG_OFFSET_BG2VOFS, gBattle_BG2_Y);
    SetGpuReg(REG_OFFSET_BG3HOFS, gBattle_BG3_X);
    SetGpuReg(REG_OFFSET_BG3VOFS, gBattle_BG3_Y);
    SetGpuReg(REG_OFFSET_WIN0H, gBattle_WIN0H);
    SetGpuReg(REG_OFFSET_WIN0V, gBattle_WIN0V);
    SetGpuReg(REG_OFFSET_WIN1H, gBattle_WIN1H);
    SetGpuReg(REG_OFFSET_WIN1V, gBattle_WIN1V);
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ScanlineEffect_InitHBlankDmaTransfer();
}

void SpriteCB_VsLetterDummy(struct Sprite *sprite)
{
}

static void SpriteCB_VsLetter(struct Sprite *sprite)
{
    if (sprite->data[0] != 0)
        sprite->pos1.x = sprite->data[1] + ((sprite->data[2] & 0xFF00) >> 8);
    else
        sprite->pos1.x = sprite->data[1] - ((sprite->data[2] & 0xFF00) >> 8);
    sprite->data[2] += 0x180;
    if (sprite->affineAnimEnded)
    {
        FreeSpriteTilesByTag(ANIM_SPRITES_START);
        FreeSpritePaletteByTag(ANIM_SPRITES_START);
        FreeSpriteOamMatrix(sprite);
        DestroySprite(sprite);
    }
}

void SpriteCB_VsLetterInit(struct Sprite *sprite)
{
    StartSpriteAffineAnim(sprite, 1);
    sprite->callback = SpriteCB_VsLetter;
    PlaySE(SE_MUGSHOT);
}

static void BufferPartyVsScreenHealth_AtEnd(u8 taskId)
{
    struct Pokemon *party1 = NULL;
    struct Pokemon *party2 = NULL;
    u8 multiplayerId = gBattleStruct->multiplayerId;
    u32 r7;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        switch (gLinkPlayers[multiplayerId].id)
        {
        case 0:
        case 2:
            party1 = gPlayerParty;
            party2 = gEnemyParty;
            break;
        case 1:
        case 3:
            party1 = gEnemyParty;
            party2 = gPlayerParty;
            break;
        }
    }
    else
    {
        party1 = gPlayerParty;
        party2 = gEnemyParty;
    }
    r7 = 0;
    BUFFER_PARTY_VS_SCREEN_STATUS(party1, r7, i);
    gTasks[taskId].data[3] = r7;
    r7 = 0;
    BUFFER_PARTY_VS_SCREEN_STATUS(party2, r7, i);
    gTasks[taskId].data[4] = r7;
}

void CB2_InitEndLinkBattle(void)
{
    s32 i;
    u8 taskId;

    SetHBlankCallback(NULL);
    SetVBlankCallback(NULL);
    CpuFill32(0, (void *)VRAM, VRAM_SIZE);
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(0, 0xF0));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(0x50, 0x51));
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    gBattle_WIN0H = WIN_RANGE(0, 0xF0);
    gBattle_WIN0V = WIN_RANGE(0x50, 0x51);
    ScanlineEffect_Clear();
    for (i = 0; i < 80; ++i)
    //    return; //why did I add this again?
    {
        gScanlineEffectRegBuffers[0][i] = 0xF0;
        gScanlineEffectRegBuffers[1][i] = 0xF0;
    }

    for (; i < 160; ++i)
    {
        gScanlineEffectRegBuffers[0][i] = 0xFF10;
        gScanlineEffectRegBuffers[1][i] = 0xFF10;
    }
    ResetPaletteFade();
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gBattle_BG2_X = 0;
    gBattle_BG2_Y = 0;
    gBattle_BG3_X = 0;
    gBattle_BG3_Y = 0;
    InitBattleBgsVideo();
    LoadCompressedPalette(gBattleInterface_Textbox_Pal, 0, 64);
    LoadBattleMenuWindowGfx();
    ResetSpriteData();
    ResetTasks();
    DrawBattleEntryBackground();
    SetGpuReg(REG_OFFSET_WINOUT, WININ_WIN0_BG0 | WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
    FreeAllSpritePalettes();
    gReservedSpritePaletteCount = 4;
    SetVBlankCallback(VBlankCB_Battle);
    taskId = CreateTask(InitLinkBattleVsScreen, 0);
    gTasks[taskId].data[1] = 270;
    gTasks[taskId].data[2] = 90;
    gTasks[taskId].data[5] = 1;
    BufferPartyVsScreenHealth_AtEnd(taskId);
    SetMainCallback2(CB2_EndLinkBattle);
    gBattleCommunication[MULTIUSE_STATE] = 0;
}

static void CB2_EndLinkBattle(void) 
{
  //  return; //possible brock issue?
    EndLinkBattleInSteps();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    RunTasks();
}

static void EndLinkBattleInSteps(void)
{
    s32 i;

    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gBattleCommunication[1] = 0xFF;
        ++gBattleCommunication[MULTIUSE_STATE];
        break;
    case 1:
        if (--gBattleCommunication[1] == 0)
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
            ++gBattleCommunication[MULTIUSE_STATE];
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            SetMainCallback2(gMain.savedCallback);
          //  TrySetQuestLogLinkBattleEvent();
            FreeMonSpritesGfx();
            FreeBattleSpritesData();
            FreeBattleResources();
        }
        break;
    }
}

u32 GetBattleBgAttribute(u8 arrayId, u8 caseId)
{
    u32 ret = 0;

    switch (caseId)
    {
    case 0:
        ret = gBattleBgTemplates[arrayId].bg;
        break;
    case 1:
        ret = gBattleBgTemplates[arrayId].charBaseIndex;
        break;
    case 2:
        ret = gBattleBgTemplates[arrayId].mapBaseIndex;
        break;
    case 3:
        ret = gBattleBgTemplates[arrayId].screenSize;
        break;
    case 4:
        ret = gBattleBgTemplates[arrayId].paletteMode;
        break;
    case 5:
        ret = gBattleBgTemplates[arrayId].priority;
        break;
    case 6:
        ret = gBattleBgTemplates[arrayId].baseTile;
        break;
    }
    return ret;
}

static void TryCorrectShedinjaLanguage(struct Pokemon *mon)
{
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 language = LANGUAGE_JAPANESE;

    if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_SHEDINJA
     && GetMonData(mon, MON_DATA_LANGUAGE) != language)
    {
        GetMonData(mon, MON_DATA_NICKNAME, nickname);
        if (StringCompareWithoutExtCtrlCodes(nickname, sText_ShedinjaJpnName) == 0)
            SetMonData(mon, MON_DATA_LANGUAGE, &language);
    }
}

#define sBattler            data[0]
#define sSpeciesId          data[2]

void SpriteCB_EnemyMon(struct Sprite *sprite)
{
    sprite->callback = SpriteCB_MoveWildMonToRight;
    StartSpriteAnimIfDifferent(sprite, 0);
    BeginNormalPaletteFade(0x20000, 0, 10, 10, RGB(8, 8, 8));
}

static void SpriteCB_MoveWildMonToRight(struct Sprite *sprite)
{
    if ((gIntroSlideFlags & 1) == 0)
    {
        sprite->pos2.x += 2;
        if (sprite->pos2.x == 0)
        {
            sprite->callback = SpriteCB_WildMonShowHealthbox;
            PlayCry_Normal(sprite->data[2], 25);
        }
    }
}

static void SpriteCB_WildMonShowHealthbox(struct Sprite *sprite)
{
    if (sprite->animEnded)
    {
        StartHealthboxSlideIn(sprite->sBattler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[sprite->sBattler]);
        sprite->callback = SpriteCallbackDummy2;
        StartSpriteAnimIfDifferent(sprite, 0);
        BeginNormalPaletteFade(0x20000, 0, 10, 0, RGB(8, 8, 8));
    }
}

void SpriteCallbackDummy2(struct Sprite *sprite)
{
}

// not used
/*UNUSED static void SpriteCB_Unused_8011E28(struct Sprite *sprite)
{
    sprite->data[3] = 6;
    sprite->data[4] = 1;
    sprite->callback = SpriteCB_Unused_8011E28_Step;
}

// not used
static void SpriteCB_Unused_8011E28_Step(struct Sprite *sprite)
{
    --sprite->data[4];
    if (sprite->data[4] == 0)
    {
        sprite->data[4] = 8;
        sprite->invisible ^= 1;
        --sprite->data[3];
        if (sprite->data[3] == 0)
        {
            sprite->invisible = FALSE;
            sprite->callback = SpriteCallbackDummy2;
            gUnknown_2022AE8[0] = 0;
        }
    }
}*/

void SpriteCB_FaintOpponentMon(struct Sprite *sprite)
{
    u8 battler = sprite->sBattler;
    u16 species;
    u8 yOffset;

    if (gBattleSpritesDataPtr->battlerData[battler].transformSpecies != 0)
        species = gBattleSpritesDataPtr->battlerData[battler].transformSpecies;
    else
        species = sprite->sSpeciesId;
    GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_PERSONALITY);  // Unused return value.

    /*if (species == SPECIES_UNOWN)
    {
        u32 personalityValue = GetMonData(&gEnemyParty[gBattlerPartyIndexes[battler]], MON_DATA_PERSONALITY);
        u16 unownForm = ((((personalityValue & 0x3000000) >> 18) | ((personalityValue & 0x30000) >> 12) | ((personalityValue & 0x300) >> 6) | (personalityValue & 3)) % 0x1C);
        u16 unownSpecies;

        if (unownForm == 0)
            unownSpecies = SPECIES_UNOWN;  // Use the A Unown form.
        else
            unownSpecies = NUM_SPECIES + unownForm;  // Use one of the other Unown letters.
        yOffset = gMonFrontPicCoords[unownSpecies].y_offset;
    }
    else if (species == SPECIES_CASTFORM)
    {
        yOffset = gCastformFrontSpriteCoords[gBattleMonForms[battler]].y_offset;
    }
    else if (species > NUM_SPECIES)
    {
        yOffset = gMonFrontPicCoords[SPECIES_NONE].y_offset; //again capitalization matters. mime broke because it wasn't Mime
    } //                                           
    else
    {
        yOffset = gMonFrontPicCoords[species].y_offset;
    }*/
    yOffset = GetBattlerYDelta(battler, species);

    sprite->data[3] = 8 - yOffset / 8;
    sprite->data[4] = 1;
    sprite->callback = SpriteCB_AnimFaintOpponent;
}

static void SpriteCB_AnimFaintOpponent(struct Sprite *sprite)
{
    s32 i;

    if (--sprite->data[4] == 0)
    {
        sprite->data[4] = 2;
        sprite->pos2.y += 8; // Move the sprite down.
        if (--sprite->data[3] < 0)
        {
            FreeSpriteOamMatrix(sprite);
            DestroySprite(sprite);
        }
        else // Erase bottom part of the sprite to create a smooth illusion of mon falling down.
        {
            u8 *dst = (u8 *)gMonSpritesGfxPtr->sprites[GetBattlerPosition(sprite->sBattler)] + (gBattleMonForms[sprite->sBattler] << 11) + (sprite->data[3] << 8);

            for (i = 0; i < 0x100; ++i)
                *(dst++) = 0;
            StartSpriteAnim(sprite, gBattleMonForms[sprite->sBattler]);
        }
    }
}

void SpriteCb_ShowAsMoveTarget(struct Sprite *sprite)
{
    sprite->data[3] = 8;
    sprite->data[4] = sprite->invisible;
    sprite->callback = SpriteCb_BlinkVisible;
}

static void SpriteCb_BlinkVisible(struct Sprite *sprite)
{
    --sprite->data[3];
    if (sprite->data[3] == 0)
    {
        sprite->invisible ^= 1;
        sprite->data[3] = 8;
    }
}

void SpriteCb_HideAsMoveTarget(struct Sprite *sprite)
{
    sprite->invisible = sprite->data[4];
    sprite->data[4] = FALSE;
    sprite->callback = SpriteCallbackDummy2;
}

void SpriteCB_AllyMon(struct Sprite *sprite)
{
    sprite->callback = oac_poke_ally_;
}

static void oac_poke_ally_(struct Sprite *sprite)
{
    if (!(gIntroSlideFlags & 1))
    {
        sprite->pos2.x -= 2;
        if (sprite->pos2.x == 0)
        {
            sprite->callback = SpriteCallbackDummy3;
            sprite->data[1] = 0;
        }
    }
}

void SpriteCB_SetToDummy3(struct Sprite *sprite)
{
    sprite->callback = SpriteCallbackDummy3;
}

static void SpriteCallbackDummy3(struct Sprite *sprite)
{
}

void SpriteCB_FaintSlideAnim(struct Sprite *sprite)
{
    if (!(gIntroSlideFlags & 1))
    {
        sprite->pos2.x += sprite->data[1];
        sprite->pos2.y += sprite->data[2];
    }
}

#define sSinIndex           data[0]
#define sDelta              data[1]
#define sAmplitude          data[2]
#define sBouncerSpriteId    data[3]
#define sWhich              data[4]

void DoBounceEffect(u8 battler, u8 which, s8 delta, s8 amplitude)
{
    u8 invisibleSpriteId;
    u8 bouncerSpriteId;

    switch (which)
    {
    case BOUNCE_HEALTHBOX:
    default:
        if (gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing)
            return;
        break;
    case BOUNCE_MON:
        if (gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing)
            return;
        break;
    }
    invisibleSpriteId = CreateInvisibleSpriteWithCallback(SpriteCB_BounceEffect);
    if (which == BOUNCE_HEALTHBOX)
    {
        bouncerSpriteId = gHealthboxSpriteIds[battler];
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId = invisibleSpriteId;
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing = 1;
        gSprites[invisibleSpriteId].sSinIndex = 128; // 0
    }
    else
    {
        bouncerSpriteId = gBattlerSpriteIds[battler];
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId = invisibleSpriteId;
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing = 1;
        gSprites[invisibleSpriteId].sSinIndex = 192; // -1
    }
    gSprites[invisibleSpriteId].sDelta = delta;
    gSprites[invisibleSpriteId].sAmplitude = amplitude;
    gSprites[invisibleSpriteId].sBouncerSpriteId = bouncerSpriteId;
    gSprites[invisibleSpriteId].sWhich = which;
    gSprites[bouncerSpriteId].pos2.x = 0;
    gSprites[bouncerSpriteId].pos2.y = 0;
}

void EndBounceEffect(u8 battler, u8 which)
{
    u8 bouncerSpriteId;

    if (which == BOUNCE_HEALTHBOX)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing)
            return;

        bouncerSpriteId = gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId].sBouncerSpriteId;
        DestroySprite(&gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].healthboxBounceSpriteId]);
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxIsBouncing = 0;
    }
    else
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing)
            return;

        bouncerSpriteId = gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId].sBouncerSpriteId;
        DestroySprite(&gSprites[gBattleSpritesDataPtr->healthBoxesData[battler].battlerBounceSpriteId]);
        gBattleSpritesDataPtr->healthBoxesData[battler].battlerIsBouncing = 0;
    }
    gSprites[bouncerSpriteId].pos2.x = 0;
    gSprites[bouncerSpriteId].pos2.y = 0;
}

static void SpriteCB_BounceEffect(struct Sprite *sprite)
{
    u8 bouncerSpriteId = sprite->sBouncerSpriteId;
    s32 index;

    if (sprite->sWhich == BOUNCE_HEALTHBOX)
        index = sprite->sSinIndex;
    else
        index = sprite->sSinIndex;
    gSprites[bouncerSpriteId].pos2.y = Sin(index, sprite->sAmplitude) + sprite->sAmplitude;
    sprite->sSinIndex = (sprite->sSinIndex + sprite->sDelta) & 0xFF;
}

void SpriteCB_PlayerThrowInit(struct Sprite *sprite)
{
    StartSpriteAnim(sprite, 1);
    sprite->callback = SpriteCB_PlayerThrowUpdate;
}

void UpdatePlayerPosInThrowAnim(struct Sprite *sprite)
{
    if (sprite->animDelayCounter == 0)
        sprite->centerToCornerVecX = sPlayerThrowXTranslation[sprite->animCmdIndex];
}

static void SpriteCB_PlayerThrowUpdate(struct Sprite *sprite)
{
    UpdatePlayerPosInThrowAnim(sprite);
    if (sprite->animEnded)
        sprite->callback = SpriteCallbackDummy3;
}

void BattleDummy(void)
{
}

void BeginBattleIntro(void)
{
    BattleStartClearSetData();
    gBattleCommunication[1] = 0;
    gBattleMainFunc = BattleIntroGetMonsData;
}

static void BattleMainCB1(void)
{
    gBattleMainFunc();
    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        gBattlerControllerFuncs[gActiveBattler]();
}

static void BattleStartClearSetData(void)
{
    s32 i;
    u32 j;
    u8 *dataPtr;

    TurnValuesCleanUp(FALSE);
    SpecialStatusesClear();
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
    {
        gStatuses3[i] = 0;
        dataPtr = (u8 *)&gDisableStructs[i];
        for (j = 0; j < sizeof(struct DisableStruct); ++j)
            dataPtr[j] = 0;
        gDisableStructs[i].isFirstTurn = 2; //beelieve is switching in? based on emerald comment    //vsonic
        gUnknown_2023DD4[i] = 0;
        gLastMoves[i] = MOVE_NONE;
        gLastLandedMoves[i] = MOVE_NONE;
        gLastHitByType[i] = 0;
        gLastResultingMoves[i] = MOVE_NONE;
        gLastHitBy[i] = 0xFF;
        gLockedMoves[i] = MOVE_NONE;
        gLastPrintedMoves[i] = MOVE_NONE;
        gBattleResources->flags->flags[i] = 0;
    }
    for (i = 0; i < 2; ++i)
    {
        gSideStatuses[i] = 0;
        dataPtr = (u8 *)&gSideTimers[i];
        for (j = 0; j < sizeof(struct SideTimer); ++j)
            dataPtr[j] = 0;
    }
    gBattlerAttacker = 0;
    gBattlerTarget = 0;
    gBattleWeather = 0;
    dataPtr = (u8 *)&gWishFutureKnock;
    for (i = 0; i < sizeof(struct WishFutureKnock); ++i)
        dataPtr[i] = 0;
    gHitMarker = 0;
    if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_POKEDUDE)) && gSaveBlock2Ptr->optionsBattleSceneOff)
        gHitMarker |= HITMARKER_NO_ANIMATIONS;
    gBattleScripting.battleStyle = gSaveBlock2Ptr->optionsBattleStyle;
    gMultiHitCounter = 0;
    gMultiTask = 0;
    gBattleOutcome = 0;
    gBattleControllerExecFlags = 0;
    gPaydayMoney = 0;
    gBattleResources->battleScriptsStack->size = 0;
    gBattleResources->battleCallbackStack->size = 0;
    for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
        gBattleCommunication[i] = 0;
    gPauseCounterBattle = 0;
    gBattleMoveDamage = 0;
    gIntroSlideFlags = 0;
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gLeveledUpInBattle = 0;
    gAbsentBattlerFlags = 0;
    gBattleStruct->runTries = 0;
    gBattleStruct->safariGoNearCounter = 0;
    gBattleStruct->safariPkblThrowCounter = 0;
    *(&gBattleStruct->safariCatchFactor) = gBaseStats[GetMonData(&gEnemyParty[0], MON_DATA_SPECIES)].catchRate * 100 / 1275;
    *(&gBattleStruct->safariEscapeFactor) = gBaseStats[GetMonData(&gEnemyParty[0], MON_DATA_SPECIES)].safariZoneFleeRate * 100 / 1275;
    if (gBattleStruct->safariEscapeFactor <= 1)
        gBattleStruct->safariEscapeFactor = 2;
    gBattleStruct->wildVictorySong = 0;
    gBattleStruct->moneyMultiplier = 1;
    for (i = 0; i < 8; ++i)
    {
        *((u8 *)gBattleStruct->lastTakenMove + i) = MOVE_NONE;
        *((u8 *)gBattleStruct->usedHeldItems + i) = ITEM_NONE;
        *((u8 *)gBattleStruct->choicedMove + i) = MOVE_NONE;
        *((u8 *)gBattleStruct->changedItems + i) = ITEM_NONE;
        *(i + 0 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 1 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 2 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i + 3 * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    }
    *(gBattleStruct->AI_monToSwitchIntoId + 0) = PARTY_SIZE;
    *(gBattleStruct->AI_monToSwitchIntoId + 1) = PARTY_SIZE;
    *(&gBattleStruct->givenExpMons) = 0;
    for (i = 0; i < 11; ++i)
        gBattleResults.catchAttempts[i] = 0;
    gBattleResults.battleTurnCounter = 0;
    gBattleResults.playerFaintCounter = 0;
    gBattleResults.opponentFaintCounter = 0;
    gBattleResults.playerSwitchesCounter = 0;
    gBattleResults.numHealingItemsUsed = 0;
    gBattleResults.numRevivesUsed = 0;
    gBattleResults.playerMonWasDamaged = FALSE;
    gBattleResults.usedMasterBall = FALSE;
    gBattleResults.lastOpponentSpecies = SPECIES_NONE;
    gBattleResults.lastUsedMovePlayer = MOVE_NONE;
    gBattleResults.lastUsedMoveOpponent = MOVE_NONE;
    gBattleResults.playerMon1Species = SPECIES_NONE;
    gBattleResults.playerMon2Species = SPECIES_NONE;
    gBattleResults.caughtMonSpecies = SPECIES_NONE;
    for (i = 0; i < POKEMON_NAME_LENGTH; ++i)
    {
        gBattleResults.playerMon1Name[i] = 0;
        gBattleResults.playerMon2Name[i] = 0;
        gBattleResults.caughtMonNick[i] = 0;
    }
}

#define CLEARDATA_ON_SWITCH
void SwitchInClearSetData(void) //handles what gets reset on switchout
{
    struct DisableStruct disableStructCopy = gDisableStructs[gActiveBattler];
    s32 i;
    u8 *ptr;

    if (gBattleMoves[gCurrentMove].effect != EFFECT_BATON_PASS)
    {
        for (i = 0; i < NUM_BATTLE_STATS; ++i)
            gBattleMons[gActiveBattler].statStages[i] = 6; //6 is 0 so this resets to normal levels
        for (i = 0; i < gBattlersCount; ++i)
        {
            if ((gBattleMons[i].status2 & STATUS2_ESCAPE_PREVENTION) && gDisableStructs[i].battlerPreventingEscape == gActiveBattler)
                gBattleMons[i].status2 &= ~STATUS2_ESCAPE_PREVENTION; //if mon blocking escape switches, removes escape prevention status
            if ((gStatuses3[i] & STATUS3_ALWAYS_HITS) && gDisableStructs[i].battlerWithSureHit == gActiveBattler)
            {
                gStatuses3[i] &= ~STATUS3_ALWAYS_HITS;
                gDisableStructs[i].battlerWithSureHit = 0;
            }
        }
    }
    if (gBattleMoves[gCurrentMove].effect == EFFECT_BATON_PASS)
    {
        gBattleMons[gActiveBattler].status2 &= (STATUS2_CONFUSION | STATUS2_FOCUS_ENERGY | STATUS2_SUBSTITUTE | STATUS2_ESCAPE_PREVENTION | STATUS2_CURSED);
        gStatuses3[gActiveBattler] &= (STATUS3_LEECHSEED_BATTLER | STATUS3_LEECHSEED | STATUS3_ALWAYS_HITS | STATUS3_PERISH_SONG | STATUS3_ROOTED); //| STATUS3_MUDSPORT | STATUS3_WATERSPORT);
        for (i = 0; i < gBattlersCount; ++i)
        {
            if (GetBattlerSide(gActiveBattler) != GetBattlerSide(i)
             && (gStatuses3[i] & STATUS3_ALWAYS_HITS) != 0
             && (gDisableStructs[i].battlerWithSureHit == gActiveBattler))
            {
                gStatuses3[i] &= ~(STATUS3_ALWAYS_HITS);
                gStatuses3[i] |= 0x10;
            }
        }
    }
    else //if not using baton pass clear status 2 & 3 on switch?
    {
        gBattleMons[gActiveBattler].status2 = 0;
        gStatuses3[gActiveBattler] = 0; //guess so but seems I misunderstood switch clear it clears data when they switch into battle not switching out
    }
    for (i = 0; i < gBattlersCount; ++i)// is this something that removes wrap, and infatuation if the mon that caused the effect is switched out?
    {
        if (gBattleMons[i].status2 & STATUS2_INFATUATED_WITH(gActiveBattler))
            gBattleMons[i].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));
        if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status2 &= ~(STATUS2_WRAPPED);
    }
    gActionSelectionCursor[gActiveBattler] = 0;
    gMoveSelectionCursor[gActiveBattler] = 0;
    ptr = (u8 *)&gDisableStructs[gActiveBattler];
    for (i = 0; i < sizeof(struct DisableStruct); ++i)
        ptr[i] = 0;
    if (gBattleMoves[gCurrentMove].effect == EFFECT_BATON_PASS)
    {
        gDisableStructs[gActiveBattler].substituteHP = disableStructCopy.substituteHP;
        gDisableStructs[gActiveBattler].battlerWithSureHit = disableStructCopy.battlerWithSureHit;
        gDisableStructs[gActiveBattler].perishSongTimer = disableStructCopy.perishSongTimer;
        gDisableStructs[gActiveBattler].perishSongTimerStartValue = disableStructCopy.perishSongTimerStartValue;
        gDisableStructs[gActiveBattler].battlerPreventingEscape = disableStructCopy.battlerPreventingEscape;
    }
    gMoveResultFlags = 0;
    gDisableStructs[gActiveBattler].isFirstTurn = 2; //??
    gLastMoves[gActiveBattler] = MOVE_NONE;
    gLastLandedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitByType[gActiveBattler] = 0;
    gLastResultingMoves[gActiveBattler] = MOVE_NONE;
    gLastPrintedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitBy[gActiveBattler] = 0xFF;
    gBattleStruct->sameMoveTurns[gActiveBattler] = 0;
    *(gBattleStruct->lastTakenMove + gActiveBattler * 2 + 0) = MOVE_NONE;
    *(gBattleStruct->lastTakenMove + gActiveBattler * 2 + 1) = MOVE_NONE;
    *(0 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(0 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(1 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(1 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(2 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(2 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(3 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(3 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    for (i = 0; i < gBattlersCount; ++i)
    {
        if (i != gActiveBattler)
        {
            *(gBattleStruct->lastTakenMove + i * 2 + 0) = MOVE_NONE;
            *(gBattleStruct->lastTakenMove + i * 2 + 1) = MOVE_NONE;
        }
        *(i * 8 + gActiveBattler * 2 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i * 8 + gActiveBattler * 2 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    }
    *((u8 *)(&gBattleStruct->choicedMove[gActiveBattler]) + 0) = MOVE_NONE;
    *((u8 *)(&gBattleStruct->choicedMove[gActiveBattler]) + 1) = MOVE_NONE;
    gBattleResources->flags->flags[gActiveBattler] = 0;
    gCurrentMove = MOVE_NONE;
}

#define CLEARDATA_ON_FAINT
void FaintClearSetData(void)
{
    s32 i;
    u8 *ptr;

    for (i = 0; i < NUM_BATTLE_STATS; ++i)
        gBattleMons[gActiveBattler].statStages[i] = 6;
    gBattleMons[gActiveBattler].status2 = 0;
    gStatuses3[gActiveBattler] = 0;
    for (i = 0; i < gBattlersCount; ++i)
    {
        if ((gBattleMons[i].status2 & STATUS2_ESCAPE_PREVENTION) && gDisableStructs[i].battlerPreventingEscape == gActiveBattler)
            gBattleMons[i].status2 &= ~STATUS2_ESCAPE_PREVENTION;
        if (gBattleMons[i].status2 & STATUS2_INFATUATED_WITH(gActiveBattler))
            gBattleMons[i].status2 &= ~(STATUS2_INFATUATED_WITH(gActiveBattler));
        if ((gBattleMons[i].status2 & STATUS2_WRAPPED) && *(gBattleStruct->wrappedBy + i) == gActiveBattler)
            gBattleMons[i].status2 &= ~(STATUS2_WRAPPED);
    }
    gActionSelectionCursor[gActiveBattler] = 0;
    gMoveSelectionCursor[gActiveBattler] = 0;
    ptr = (u8 *)&gDisableStructs[gActiveBattler];
    for (i = 0; i < sizeof(struct DisableStruct); ++i)
        ptr[i] = 0;
    gProtectStructs[gActiveBattler].protected = FALSE;
    gProtectStructs[gActiveBattler].endured = FALSE;
    gProtectStructs[gActiveBattler].noValidMoves = FALSE;
    gProtectStructs[gActiveBattler].helpingHand = FALSE;
    gProtectStructs[gActiveBattler].spikyShielded = FALSE;
    gProtectStructs[gActiveBattler].kingsShielded = FALSE;
    gProtectStructs[gActiveBattler].banefulBunkered = FALSE;
    gProtectStructs[gActiveBattler].bounceMove = FALSE;
    gProtectStructs[gActiveBattler].stealMove = FALSE;
    gProtectStructs[gActiveBattler].flag0Unknown = FALSE;
    gProtectStructs[gActiveBattler].prlzImmobility = FALSE;
    gProtectStructs[gActiveBattler].confusionSelfDmg = FALSE;
    gProtectStructs[gActiveBattler].targetNotAffected = FALSE;
    gProtectStructs[gActiveBattler].chargingTurn = FALSE;
    gProtectStructs[gActiveBattler].fleeFlag = 0;
    gProtectStructs[gActiveBattler].usedImprisonedMove = FALSE;
    gProtectStructs[gActiveBattler].loveImmobility = FALSE;
    gProtectStructs[gActiveBattler].obstructed = FALSE;
    gProtectStructs[gActiveBattler].usedDisabledMove = FALSE;
    gProtectStructs[gActiveBattler].usedTauntedMove = FALSE;
    gProtectStructs[gActiveBattler].flag2Unknown = FALSE;
    gProtectStructs[gActiveBattler].flinchImmobility = FALSE;
    gProtectStructs[gActiveBattler].notFirstStrike = FALSE;
    gProtectStructs[gActiveBattler].pranksterElevated = FALSE;
    gProtectStructs[gActiveBattler].usedHealBlockedMove = FALSE;
    gProtectStructs[gActiveBattler].usesBouncedMove = FALSE;
    gProtectStructs[gActiveBattler].usedGravityPreventedMove = FALSE;
    gProtectStructs[gActiveBattler].usedThroatChopPreventedMove = FALSE;
    gDisableStructs[gActiveBattler].isFirstTurn = 2;
    gLastMoves[gActiveBattler] = MOVE_NONE;
    gLastLandedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitByType[gActiveBattler] = MOVE_NONE;
    gLastResultingMoves[gActiveBattler] = MOVE_NONE;
    gLastPrintedMoves[gActiveBattler] = MOVE_NONE;
    gLastHitBy[gActiveBattler] = 0xFF;
    gBattleStruct->sameMoveTurns[gActiveBattler] = 0; //hope works since others writ diff in fire red/emerald
    *((u8 *)(&gBattleStruct->choicedMove[gActiveBattler]) + 0) = MOVE_NONE;
    *((u8 *)(&gBattleStruct->choicedMove[gActiveBattler]) + 1) = MOVE_NONE;
    *(gBattleStruct->lastTakenMove + gActiveBattler * 2 + 0) = MOVE_NONE;
    *(gBattleStruct->lastTakenMove + gActiveBattler * 2 + 1) = MOVE_NONE;
    *(0 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(0 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(1 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(1 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(2 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(2 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    *(3 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
    *(3 * 2 + gActiveBattler * 8 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    for (i = 0; i < gBattlersCount; ++i)
    {
        if (i != gActiveBattler)
        {
            *(gBattleStruct->lastTakenMove + i * 2 + 0) = MOVE_NONE;
            *(gBattleStruct->lastTakenMove + i * 2 + 1) = MOVE_NONE;
        }
        *(i * 8 + gActiveBattler * 2 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 0) = 0;
        *(i * 8 + gActiveBattler * 2 + (u8 *)(gBattleStruct->lastTakenMoveFrom) + 1) = 0;
    }
    gBattleResources->flags->flags[gActiveBattler] = 0;
    gBattleMons[gActiveBattler].type1 = gBaseStats[gBattleMons[gActiveBattler].species].type1;
    gBattleMons[gActiveBattler].type2 = gBaseStats[gBattleMons[gActiveBattler].species].type2;
}

static void BattleIntroGetMonsData(void)
{
    switch (gBattleCommunication[MULTIUSE_STATE])
    {
    case 0:
        gActiveBattler = gBattleCommunication[1];
        BtlController_EmitGetMonData(0, REQUEST_ALL_BATTLE, 0);
        MarkBattlerForControllerExec(gActiveBattler);
        ++gBattleCommunication[MULTIUSE_STATE];
        break;
    case 1:
        if (gBattleControllerExecFlags == 0)
        {
            ++gBattleCommunication[1];
            if (gBattleCommunication[1] == gBattlersCount)
                gBattleMainFunc = BattleIntroPrepareBackgroundSlide;
            else
                gBattleCommunication[MULTIUSE_STATE] = 0;
        }
        break;
    }
}

static void BattleIntroPrepareBackgroundSlide(void)
{
    if (gBattleControllerExecFlags == 0)
    {
        gActiveBattler = GetBattlerAtPosition(0);
        BtlController_EmitIntroSlide(0, gBattleTerrain);
        MarkBattlerForControllerExec(gActiveBattler);
        gBattleMainFunc = BattleIntroDrawTrainersOrMonsSprites;
        gBattleCommunication[MULTIUSE_STATE] = 0;
        gBattleCommunication[SPRITES_INIT_STATE1] = 0;
    }
}

static void BattleIntroDrawTrainersOrMonsSprites(void)
{
    u8 *ptr;
    s32 i;

    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if ((gBattleTypeFlags & BATTLE_TYPE_SAFARI)
             && GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                ptr = (u8 *)&gBattleMons[gActiveBattler];
                for (i = 0; i < sizeof(struct BattlePokemon); ++i)
                    ptr[i] = 0;
            }
            else // all non-safari battles
            {
                u16 *hpOnSwitchout;

                ptr = (u8 *)&gBattleMons[gActiveBattler];
                for (i = 0; i < sizeof(struct BattlePokemon); ++i)
                    ptr[i] = gBattleBufferB[gActiveBattler][4 + i];
                gBattleMons[gActiveBattler].type1 = gBaseStats[gBattleMons[gActiveBattler].species].type1;
                gBattleMons[gActiveBattler].type2 = gBaseStats[gBattleMons[gActiveBattler].species].type2;
                gBattleMons[gActiveBattler].ability = GetAbilityBySpecies(gBattleMons[gActiveBattler].species, gBattleMons[gActiveBattler].abilityNum);
                hpOnSwitchout = &gBattleStruct->hpOnSwitchout[GetBattlerSide(gActiveBattler)];
                *hpOnSwitchout = gBattleMons[gActiveBattler].hp;
                for (i = 0; i < NUM_BATTLE_STATS; ++i)
                    gBattleMons[gActiveBattler].statStages[i] = 6; //important, these two reset stat buffs, and clear status2 effects on switch
                gBattleMons[gActiveBattler].status2 = 0;
            }
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_LEFT)
            {
                BtlController_EmitDrawTrainerPic(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
            {
                if (GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_LEFT)
                {
                    BtlController_EmitDrawTrainerPic(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT
                 && !(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                       | BATTLE_TYPE_POKEDUDE
                                       | BATTLE_TYPE_LINK
                                       | BATTLE_TYPE_GHOST
                                       | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                       | BATTLE_TYPE_LEGENDARY)))
                    HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
            }
            else
            {
                if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT)
                {
                    if (gBattleTypeFlags & (BATTLE_TYPE_GHOST | BATTLE_TYPE_GHOST_UNVEILED))
                    {
                        if (!IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
                            HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
                    }
                    else if (!(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                                | BATTLE_TYPE_POKEDUDE
                                                | BATTLE_TYPE_LINK
                                                | BATTLE_TYPE_GHOST
                                                | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                                | BATTLE_TYPE_LEGENDARY)))
                    {
                        HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
                    }
                    BtlController_EmitLoadMonSprite(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI
             && (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_RIGHT || GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_RIGHT))
            {
                BtlController_EmitDrawTrainerPic(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleMainFunc = BattleIntroDrawPartySummaryScreens;
    }
}

static void BattleIntroDrawPartySummaryScreens(void)
{
    s32 i;
    struct HpAndStatus hpStatus[PARTY_SIZE];

    if (!gBattleControllerExecFlags)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gEnemyParty[i], MON_DATA_SPECIES2) == SPECIES_NONE
                 || GetMonData(&gEnemyParty[i], MON_DATA_SPECIES2) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gEnemyParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gEnemyParty[i], MON_DATA_STATUS);
                }
            }
            gActiveBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            BtlController_EmitDrawPartyStatusSummary(0, hpStatus, 0x80);
            MarkBattlerForControllerExec(gActiveBattler);
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2) == SPECIES_NONE
                 || GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
                }
            }
            gActiveBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            BtlController_EmitDrawPartyStatusSummary(0, hpStatus, 0x80);
            MarkBattlerForControllerExec(gActiveBattler);

            gBattleMainFunc = BattleIntroPrintTrainerWantsToBattle;
        }
        else
        {
            // The struct gets set here, but nothing is ever done with it since
            // wild battles don't show the party summary.
            // Still, there's no point in having dead code.
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2) == SPECIES_NONE
                 || GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2) == SPECIES_EGG)
                {
                    hpStatus[i].hp = 0xFFFF;
                    hpStatus[i].status = 0;
                }
                else
                {
                    hpStatus[i].hp = GetMonData(&gPlayerParty[i], MON_DATA_HP);
                    hpStatus[i].status = GetMonData(&gPlayerParty[i], MON_DATA_STATUS);
                }
            }
            gBattleMainFunc = BattleIntroPrintWildMonAttacked;
        }
    }
}

static void BattleIntroPrintTrainerWantsToBattle(void)
{
    if (!gBattleControllerExecFlags)
    {
        gActiveBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        PrepareStringBattle(STRINGID_INTROMSG, gActiveBattler);
        gBattleMainFunc = BattleIntroPrintOpponentSendsOut;
    }
}

static void BattleIntroPrintWildMonAttacked(void)
{
    if (!gBattleControllerExecFlags)
    {
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
        PrepareStringBattle(STRINGID_INTROMSG, 0);
        if (IS_BATTLE_TYPE_GHOST_WITH_SCOPE(gBattleTypeFlags))
        {
            gBattleScripting.battler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            BattleScriptExecute(BattleScript_SilphScopeUnveiled);
        }
    }
}

static void BattleIntroPrintOpponentSendsOut(void)
{
    if (!gBattleControllerExecFlags)
    {
        PrepareStringBattle(STRINGID_INTROSENDOUT, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
        gBattleMainFunc = BattleIntroOpponentSendsOutMonAnimation;
    }
}

static void BattleIntroOpponentSendsOutMonAnimation(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_LEFT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && GetBattlerPosition(gActiveBattler) == B_POSITION_OPPONENT_RIGHT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleMainFunc = BattleIntroRecordMonsToDex;
    }
}

static void BattleIntroRecordMonsToDex(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT
             && !(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
                                   | BATTLE_TYPE_POKEDUDE
                                   | BATTLE_TYPE_LINK
                                   | BATTLE_TYPE_GHOST
                                   | BATTLE_TYPE_OLD_MAN_TUTORIAL
                                   | BATTLE_TYPE_LEGENDARY)))
                HandleSetPokedexFlag(SpeciesToNationalPokedexNum(gBattleMons[gActiveBattler].species), FLAG_SET_SEEN, gBattleMons[gActiveBattler].personality);
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
    }
}

// not used
static void Unused_AutoProgressToIntro(void)
{
    if (!gBattleControllerExecFlags)
        gBattleMainFunc = BattleIntroPrintPlayerSendsOut;
}

void BattleIntroPrintPlayerSendsOut(void)
{
    if (!gBattleControllerExecFlags)
    {
        if (!(gBattleTypeFlags & BATTLE_TYPE_SAFARI))
            PrepareStringBattle(STRINGID_INTROSENDOUT, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT));
        gBattleMainFunc = BattleIntroPlayerSendsOutMonAnimation;
    }
}

static void BattleIntroPlayerSendsOutMonAnimation(void)
{
    u32 position;

    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_LEFT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && GetBattlerPosition(gActiveBattler) == B_POSITION_PLAYER_RIGHT)
            {
                BtlController_EmitIntroTrainerBallThrow(0);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleStruct->switchInAbilitiesCounter = 0;
        gBattleStruct->switchInItemsCounter = 0;
        gBattleStruct->overworldWeatherDone = FALSE;
        gBattleMainFunc = TryDoEventsBeforeFirstTurn;
    }
}

// not used
static void Unused_AutoProgressToSwitchInAnims(void)
{
    if (!gBattleControllerExecFlags)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                BtlController_EmitSwitchInAnim(0, gBattlerPartyIndexes[gActiveBattler], FALSE);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
        gBattleStruct->switchInAbilitiesCounter = 0;
        gBattleStruct->switchInItemsCounter = 0;
        gBattleStruct->overworldWeatherDone = FALSE;
        gBattleMainFunc = TryDoEventsBeforeFirstTurn;
    }
}

static void TryDoEventsBeforeFirstTurn(void)
{
    s32 i, j;
    u8 effect = 0;

    if (!gBattleControllerExecFlags)
    {
        
        if (gBattleStruct->switchInAbilitiesCounter == 0)
        {
            for (i = 0; i < gBattlersCount; ++i)
                gBattlerByTurnOrder[i] = i;
            for (i = 0; i < gBattlersCount - 1; ++i)
                for (j = i + 1; j < gBattlersCount; ++j)
                    if (GetWhoStrikesFirst(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], TRUE) != 0)
                        SwapTurnOrder(i, j);
        }
        
        if (!gBattleStruct->terrainDone && AbilityBattleEffects(0, 0, 0, ABILITYEFFECT_SWITCH_IN_TERRAIN, 0) != 0)
        {
            gBattleStruct->terrainDone = TRUE;
            return;
        }
        if (!gBattleStruct->overworldWeatherDone && AbilityBattleEffects(0, 0, 0, ABILITYEFFECT_SWITCH_IN_WEATHER, 0) != 0)
        {
            gBattleStruct->overworldWeatherDone = TRUE; //move here cuz I want terrain to trigger first
            return;
        }
        // Totem boosts
        for (i = 0; i < gBattlersCount; i++)
        {
            if (gTotemBoosts[i].stats != 0)
            {
                gBattlerAttacker = i;
                BattleScriptExecute(BattleScript_TotemVar);
                return;
            }
        }
        memset(gTotemBoosts, 0, sizeof(gTotemBoosts));  // erase all totem boosts just to be safe

        // Primal Reversion
        for (i = 0; i < gBattlersCount; i++)
        {
            if (CanMegaEvolve(i)
                && GetBattlerHoldEffect(i, TRUE) == HOLD_EFFECT_PRIMAL_ORB)
            {
                gBattlerAttacker = i;
                BattleScriptExecute(BattleScript_PrimalReversion);
                return;
            }
        }

        // Check neutralizing gas
        if (AbilityBattleEffects(ABILITYEFFECT_NEUTRALIZINGGAS, 0, 0, 0, 0) != 0)
            return;//note removal of levitate will make flying types safer
        //from poison/weezing, but countred by increasd smackdown learnset and roost change

        // Check all switch in abilities happening from the fastest mon to slowest.
        while (gBattleStruct->switchInAbilitiesCounter < gBattlersCount) //want to change to work on switchin and when opponent switches pokemon.
        {
            if (AbilityBattleEffects(ABILITYEFFECT_ON_SWITCHIN, gBattlerByTurnOrder[gBattleStruct->switchInAbilitiesCounter], 0, 0, 0) != 0)
                ++effect; //believe this is looping through only switch in abilities, I think long as ability isn't none?
            ++gBattleStruct->switchInAbilitiesCounter; //intimidate2 isn't referenced anywhere, so I assume its just baked into normal switchin
            //if I want another category of switchin abilities, pretty sure all I need to do is add it in here above the counter? unless this is all really battle 1st turn
            //and not firstturn for mon in which case it wouldn't work for my needs..
            if (effect)//think if effect increments counts as activated so returns and checks next battler?
                return; //yeah checking mon in battle for if they have switchin abilities, and activates them if they do.
        } //check pursuit it may be the best way to do this, since it tells when a battler is switching and activates an effect
        //plan to pattern after spikes instead as that effects side, and only on mon switching in
        if (AbilityBattleEffects(ABILITYEFFECT_INTIMIDATE1, 0, 0, 0, 0) != 0) //this is battle start intimidate.
            return;
        if (AbilityBattleEffects(ABILITYEFFECT_TRACE, 0, 0, 0, 0) != 0)
            return;
        // Check all switch in items having effect from the fastest mon to slowest.
        while (gBattleStruct->switchInItemsCounter < gBattlersCount)
        {
            if (ItemBattleEffects(ITEMEFFECT_ON_SWITCH_IN, gBattlerByTurnOrder[gBattleStruct->switchInItemsCounter], FALSE))
                ++effect;
            ++gBattleStruct->switchInItemsCounter;
            if (effect)
                return;
        }
        for (i = 0; i < gBattlersCount; ++i) // pointless, ruby leftover
            ;
        for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        {
            *(gBattleStruct->monToSwitchIntoId + i) = PARTY_SIZE;
            gChosenActionByBattler[i] = B_ACTION_NONE;
            gChosenMoveByBattler[i] = MOVE_NONE;
        }
        TurnValuesCleanUp(FALSE);
        SpecialStatusesClear();
        *(&gBattleStruct->absentBattlerFlags) = gAbsentBattlerFlags;
        gBattleMainFunc = HandleTurnActionSelectionState;
        ResetSentPokesToOpponentValue();
        for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
            gBattleCommunication[i] = 0;
        for (i = 0; i < gBattlersCount; ++i)
            gBattleMons[i].status2 &= ~(STATUS2_FLINCHED);
        *(&gBattleStruct->turnEffectsTracker) = 0;
        *(&gBattleStruct->turnEffectsBattlerId) = 0;
        *(&gBattleStruct->wishPerishSongState) = 0;
        *(&gBattleStruct->wishPerishSongBattlerId) = 0;
        gBattleScripting.atk49_state = 0;
        gBattleStruct->faintedActionsState = 0;
        gBattleStruct->turnCountersTracker = 0;
        gMoveResultFlags = 0;
        gRandomTurnNumber = Random();
    }
}

static void HandleEndTurn_ContinueBattle(void)
{
    s32 i;

    if (!gBattleControllerExecFlags)
    {
        gBattleMainFunc = BattleTurnPassed;
        for (i = 0; i < BATTLE_COMMUNICATION_ENTRIES_COUNT; ++i)
            gBattleCommunication[i] = 0;
        for (i = 0; i < gBattlersCount; ++i)
        {
            gBattleMons[i].status2 &= ~(STATUS2_FLINCHED);
            if ((gBattleMons[i].status1 & STATUS1_SLEEP) && (gBattleMons[i].status2 & STATUS2_MULTIPLETURNS))
                CancelMultiTurnMoves(i);
        }
        gBattleStruct->turnEffectsTracker = 0;
        gBattleStruct->turnEffectsBattlerId = 0;
        gBattleStruct->wishPerishSongState = 0;
        gBattleStruct->wishPerishSongBattlerId = 0;
        gBattleStruct->turnCountersTracker = 0;
        gMoveResultFlags = 0;
    }
}

void BattleTurnPassed(void)
{
    s32 i;

    TurnValuesCleanUp(TRUE);
    if (gBattleOutcome == 0)
    {
        if (DoFieldEndTurnEffects())
            return;
        if (DoBattlerEndTurnEffects())
            return;
    }
    if (HandleFaintedMonActions())
        return;
    gBattleStruct->faintedActionsState = 0;
    if (HandleWishPerishSongOnTurnEnd())
        return;
    TurnValuesCleanUp(FALSE);
    gHitMarker &= ~(HITMARKER_NO_ATTACKSTRING);
    gHitMarker &= ~(HITMARKER_UNABLE_TO_USE_MOVE);
    gHitMarker &= ~(HITMARKER_PLAYER_FAINTED);
    gHitMarker &= ~(HITMARKER_PASSIVE_DAMAGE);
    gBattleScripting.animTurn = 0;
    gBattleScripting.animTargetsHit = 0;
    gBattleScripting.atk49_state = 0;
    gBattleMoveDamage = 0;
    gMoveResultFlags = 0;
    for (i = 0; i < 5; ++i)
        gBattleCommunication[i] = 0;
    if (gBattleOutcome != 0)
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        gBattleMainFunc = RunTurnActionsFunctions;
        return;
    }
    if (gBattleResults.battleTurnCounter < 0xFF)
        ++gBattleResults.battleTurnCounter;
    for (i = 0; i < gBattlersCount; ++i)
    {
        gChosenActionByBattler[i] = B_ACTION_NONE;
        gChosenMoveByBattler[i] = MOVE_NONE;
    }
    for (i = 0; i < MAX_BATTLERS_COUNT; ++i)
        *(gBattleStruct->monToSwitchIntoId + i) = PARTY_SIZE;
    *(&gBattleStruct->absentBattlerFlags) = gAbsentBattlerFlags;
    gBattleMainFunc = HandleTurnActionSelectionState;
    gRandomTurnNumber = Random();
}

#define RUN_LOGIC_PT1
u8 IsRunningFromBattleImpossible(void) // equal to emerald is ability preventing escape  put logic in here.
{
    u8 holdEffect;
    u8 side;
    s32 i;

    if (gBattleMons[gActiveBattler].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[gActiveBattler].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(gBattleMons[gActiveBattler].item);
    gPotentialItemEffectBattler = gActiveBattler;
    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN
     || (gBattleTypeFlags & BATTLE_TYPE_LINK)
     || gBattleMons[gActiveBattler].ability == ABILITY_RUN_AWAY
     || gBattleMons[gActiveBattler].ability == ABILITY_AVIATOR
     || (gBattleMons[gActiveBattler].ability == ABILITY_DEFEATIST
         && gSpecialStatuses[gActiveBattler].defeatistActivated)
     || holdEffect == HOLD_EFFECT_SHED_SHELL)
        return BATTLE_RUN_SUCCESS;
    
    side = GetBattlerSide(gActiveBattler);
    for (i = 0; i < gBattlersCount; ++i)
    {
        if (side != GetBattlerSide(i)
         && gBattleMons[i].ability == ABILITY_SHADOW_TAG) //since shadow tag is like an exorcism talismon 
            //meant to keep spirits from escaping it makes sense for shadow tag
            // to still lock in ghost types
        {
            gBattleScripting.battler = i;
            gLastUsedAbility = gBattleMons[i].ability;
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            return BATTLE_RUN_FAILURE;
        }
        if (side != GetBattlerSide(i)
         /*&& gBattleMons[gActiveBattler].ability != ABILITY_LEVITATE
         && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING)
         && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST)*/
         && IsBattlerGrounded(gActiveBattler)
         && gBattleMons[i].ability == ABILITY_ARENA_TRAP) //need add grounded check for flying  vsonic
        {
            gBattleScripting.battler = i;
            gLastUsedAbility = gBattleMons[i].ability;
            gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            return BATTLE_RUN_FAILURE;
        }
    }
    i = AbilityBattleEffects(ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER, gActiveBattler, ABILITY_MAGNET_PULL, 0, 0);
    if (i != 0 && IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_STEEL))
    {
        gBattleScripting.battler = i - 1;
        gLastUsedAbility = gBattleMons[i - 1].ability;
        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
        return BATTLE_RUN_FAILURE;
    }//vsonic IMPORTANT do search, for status2_wrapped & wrappedby  implement new trap checks where it makes sense
    //similar to as below
    if ((gBattleMons[gActiveBattler].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_WRAPPED))//vsonic need add new trap status here
     || (gBattleMons[gActiveBattler].status4 == ITS_A_TRAP_STATUS4)
     || (gBattleMons[gActiveBattler].status1 == ITS_A_TRAP_STATUS1)
     || (gStatuses3[gActiveBattler] & STATUS3_ROOTED)
     || (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
     /*|| (!IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_GHOST)
        && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING))*/
     || (IsBattlerGrounded(gActiveBattler))) //use paras ingraint to check I didn't break affect with this
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        return BATTLE_RUN_FORBIDDEN;
    }
    if (gBattleTypeFlags & BATTLE_TYPE_FIRST_BATTLE)
    {
        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        return BATTLE_RUN_FORBIDDEN;
    }
    return BATTLE_RUN_SUCCESS;
}

void UpdatePartyOwnerOnSwitch_NonMulti(u8 battler)
{
    s32 i;
    u8 r4, r1;

    for (i = 0; i < 3; ++i)
        gBattlePartyCurrentOrder[i] = *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders));
    r4 = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[battler]);
    r1 = GetPartyIdFromBattlePartyId(*(gBattleStruct->monToSwitchIntoId + battler));
    SwitchPartyMonSlots(r4, r1);
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        for (i = 0; i < 3; ++i)
        {
            *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
            *(BATTLE_PARTNER(battler) * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
        }
    }
    else
    {
        for (i = 0; i < 3; ++i)
            *(battler * 3 + i + (u8 *)(gBattleStruct->battlerPartyOrders)) = gBattlePartyCurrentOrder[i];
    }
}

enum
{
    STATE_BEFORE_ACTION_CHOSEN,
    STATE_WAIT_ACTION_CHOSEN,
    STATE_WAIT_ACTION_CASE_CHOSEN,
    STATE_WAIT_ACTION_CONFIRMED_STANDBY,
    STATE_WAIT_ACTION_CONFIRMED,
    STATE_SELECTION_SCRIPT,
    STATE_WAIT_SET_BEFORE_ACTION,
};

#define TURN_ACTIONS_SWITCH_ETC

static void HandleTurnActionSelectionState(void) //think need add case for my swith action
{
    s32 i;

    gBattleCommunication[ACTIONS_CONFIRMED_COUNT] = 0;
    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        u8 position = GetBattlerPosition(gActiveBattler);

        switch (gBattleCommunication[gActiveBattler])
        {
        case STATE_BEFORE_ACTION_CHOSEN: // Choose an action.
            *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = PARTY_SIZE;
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI
             || (position & BIT_FLANK) == B_FLANK_LEFT
             || gBattleStruct->absentBattlerFlags & gBitTable[GetBattlerAtPosition(BATTLE_PARTNER(position))]
             || gBattleCommunication[GetBattlerAtPosition(BATTLE_PARTNER(position))] == STATE_WAIT_ACTION_CONFIRMED)
            {
                if (gBattleStruct->absentBattlerFlags & gBitTable[gActiveBattler])
                {
                    gChosenActionByBattler[gActiveBattler] = B_ACTION_NOTHING_FAINTED;
                    if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED;
                    else
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                }
                else
                {
                    if (gBattleMons[gActiveBattler].status2 & STATUS2_MULTIPLETURNS
                     || gBattleMons[gActiveBattler].status2 & STATUS2_RECHARGE)
                    {
                        gChosenActionByBattler[gActiveBattler] = B_ACTION_USE_MOVE;
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                    }
                    else
                    {
                        BtlController_EmitChooseAction(0, gChosenActionByBattler[0], gBattleBufferB[0][1] | (gBattleBufferB[0][2] << 8));
                        MarkBattlerForControllerExec(gActiveBattler);
                        ++gBattleCommunication[gActiveBattler];
                    }
                }
            }
            break;
        case STATE_WAIT_ACTION_CHOSEN: // Try to perform an action.
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                gChosenActionByBattler[gActiveBattler] = gBattleBufferB[gActiveBattler][1];
                switch (gBattleBufferB[gActiveBattler][1])
                {
                case B_ACTION_USE_MOVE:
                    if (AreAllMovesUnusable())
                    {
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                        *(gBattleStruct->moveTarget + gActiveBattler) = gBattleBufferB[gActiveBattler][3];
                        return;
                    }
                    else if (gDisableStructs[gActiveBattler].encoredMove != MOVE_NONE)
                    {
                        gChosenMoveByBattler[gActiveBattler] = gDisableStructs[gActiveBattler].encoredMove;
                        *(gBattleStruct->chosenMovePositions + gActiveBattler) = gDisableStructs[gActiveBattler].encoredMovePos;
                        gBattleCommunication[gActiveBattler] = STATE_WAIT_ACTION_CONFIRMED_STANDBY;
                        return;
                    }
                    else
                    {
                        struct ChooseMoveStruct moveInfo;

                        moveInfo.species = gBattleMons[gActiveBattler].species;
                        moveInfo.monType1 = gBattleMons[gActiveBattler].type1;
                        moveInfo.monType2 = gBattleMons[gActiveBattler].type2;
                        for (i = 0; i < MAX_MON_MOVES; ++i)
                        {
                            moveInfo.moves[i] = gBattleMons[gActiveBattler].moves[i];
                            moveInfo.currentPp[i] = gBattleMons[gActiveBattler].pp[i];
                            moveInfo.maxPp[i] = CalculatePPWithBonus(gBattleMons[gActiveBattler].moves[i],
                                                                     gBattleMons[gActiveBattler].ppBonuses,
                                                                     i);
                        }
                        BtlController_EmitChooseMove(0, (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) != 0, FALSE, &moveInfo);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    break;
                case B_ACTION_USE_ITEM:
                    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_EREADER_TRAINER))
                    {
                        gSelectionBattleScripts[gActiveBattler] = BattleScript_ActionSelectionItemsCantBeUsed;
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                        return;
                    }
                    else
                    {
                        BtlController_EmitChooseItem(0, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        MarkBattlerForControllerExec(gActiveBattler);
                    }
                    break;
                case B_ACTION_SWITCH:
                    *(gBattleStruct->battlerPartyIndexes + gActiveBattler) = gBattlerPartyIndexes[gActiveBattler];
                    if (gBattleMons[gActiveBattler].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION) 
                        || (gStatuses3[gActiveBattler] & STATUS3_ROOTED)
                        || (gBattleMons[gActiveBattler].status1 & (ITS_A_TRAP_STATUS1)) 
                        || (gStatuses4[gActiveBattler] & (ITS_A_TRAP_STATUS4))) //hope this works...
                    {
                        if (gBattleMons[gActiveBattler].ability == ABILITY_DEFEATIST
                            && gSpecialStatuses[gActiveBattler].defeatistActivated) //overwrite usual switch preveention from status & traps
                        {
                            if (gActiveBattler == 2 && gChosenActionByBattler[0] == B_ACTION_SWITCH)
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 0), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                            else if (gActiveBattler == 3 && gChosenActionByBattler[1] == B_ACTION_SWITCH)
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 1), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                            else
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        }
                        else
                        BtlController_EmitChoosePokemon(0, PARTY_ACTION_CANT_SWITCH, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                    }
                    else if ((i = ABILITY_ON_OPPOSING_FIELD(gActiveBattler, ABILITY_SHADOW_TAG))
                          || ((i = ABILITY_ON_OPPOSING_FIELD(gActiveBattler, ABILITY_ARENA_TRAP))
                              && !IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_FLYING)
                              //&& gBattleMons[gActiveBattler].ability != ABILITY_LEVITATE
                              && !IsBattlerGrounded(gActiveBattler))
                          || ((i = AbilityBattleEffects(ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER, gActiveBattler, ABILITY_MAGNET_PULL, 0, 0))
                              && IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_STEEL)))
                    {
                         if (gBattleMons[gActiveBattler].ability == ABILITY_DEFEATIST
                            && gSpecialStatuses[gActiveBattler].defeatistActivated) //overwrite usual switch preveention from ability
                         {
                            if (gActiveBattler == 2 && gChosenActionByBattler[0] == B_ACTION_SWITCH)
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 0), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                            else if (gActiveBattler == 3 && gChosenActionByBattler[1] == B_ACTION_SWITCH)
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 1), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                            else
                                BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                         }
                        else
                        BtlController_EmitChoosePokemon(0, ((i - 1) << 4) | PARTY_ACTION_ABILITY_PREVENTS, 6, gLastUsedAbility, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                    }
                    else //can switch
                    {
                        if (gActiveBattler == 2 && gChosenActionByBattler[0] == B_ACTION_SWITCH)
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 0), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        else if (gActiveBattler == 3 && gChosenActionByBattler[1] == B_ACTION_SWITCH)
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, *(gBattleStruct->monToSwitchIntoId + 1), ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                        else
                            BtlController_EmitChoosePokemon(0, PARTY_ACTION_CHOOSE_MON, 6, ABILITY_NONE, gBattleStruct->battlerPartyOrders[gActiveBattler]);
                    }
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case B_ACTION_SAFARI_BALL:
                    if (IsPlayerPartyAndPokemonStorageFull())
                    {
                        gSelectionBattleScripts[gActiveBattler] = BattleScript_PrintFullBox;
                        gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                        *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                        *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                        return;
                    }
                    break;
                case B_ACTION_SKIP_TURN:
                    gBattleCommunication[gActiveBattler] = STATE_WAIT_SET_BEFORE_ACTION; //still unsure which state to use
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case B_ACTION_CANCEL_PARTNER:
                    gBattleCommunication[gActiveBattler] = STATE_WAIT_SET_BEFORE_ACTION;
                    gBattleCommunication[GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerPosition(gActiveBattler)))] = STATE_BEFORE_ACTION_CHOSEN;
                    BtlController_EmitEndBounceEffect(0);
                    MarkBattlerForControllerExec(gActiveBattler);
                    return;
                }
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER
                 && !(gBattleTypeFlags & BATTLE_TYPE_LINK)
                 && gBattleBufferB[gActiveBattler][1] == B_ACTION_RUN)
                {
                    BattleScriptExecute(BattleScript_PrintCantRunFromTrainer);
                    gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                }
                else if (IsRunningFromBattleImpossible() != BATTLE_RUN_SUCCESS
                      && gBattleBufferB[gActiveBattler][1] == B_ACTION_RUN)
                {
                    gSelectionBattleScripts[gActiveBattler] = BattleScript_PrintCantEscapeFromBattle;
                    gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                    *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                    *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_BEFORE_ACTION_CHOSEN;
                    return;
                }
                else
                {
                    ++gBattleCommunication[gActiveBattler];
                }
            }
            break;
        case STATE_WAIT_ACTION_CASE_CHOSEN:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                switch (gChosenActionByBattler[gActiveBattler])
                {
                case B_ACTION_USE_MOVE:
                    switch (gBattleBufferB[gActiveBattler][1])
                    {
                    case 3 ... 9:
                        gChosenActionByBattler[gActiveBattler] = gBattleBufferB[gActiveBattler][1];
                        return;
                    default:
                        if ((gBattleBufferB[gActiveBattler][2] | (gBattleBufferB[gActiveBattler][3] << 8)) == 0xFFFF)
                        {
                            gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                        }
                        else if (TrySetCantSelectMoveBattleScript())
                        {
                            gBattleCommunication[gActiveBattler] = STATE_SELECTION_SCRIPT;
                            *(gBattleStruct->selectionScriptFinished + gActiveBattler) = FALSE;
                            gBattleBufferB[gActiveBattler][1] = 0;
                            *(gBattleStruct->stateIdAfterSelScript + gActiveBattler) = STATE_WAIT_ACTION_CHOSEN;
                            return;
                        }
                        else
                        {
                            *(gBattleStruct->chosenMovePositions + gActiveBattler) = gBattleBufferB[gActiveBattler][2];
                            gChosenMoveByBattler[gActiveBattler] = gBattleMons[gActiveBattler].moves[*(gBattleStruct->chosenMovePositions + gActiveBattler)];
                            *(gBattleStruct->moveTarget + gActiveBattler) = gBattleBufferB[gActiveBattler][3];
                            ++gBattleCommunication[gActiveBattler];
                        }
                        break;
                    }
                    break;
                case B_ACTION_USE_ITEM:
                    if ((gBattleBufferB[gActiveBattler][1] | (gBattleBufferB[gActiveBattler][2] << 8)) == 0)
                    {
                        gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    }
                    else
                    {
                        gLastUsedItem = (gBattleBufferB[gActiveBattler][1] | (gBattleBufferB[gActiveBattler][2] << 8));
                        ++gBattleCommunication[gActiveBattler];
                    }
                    break;
                case B_ACTION_SWITCH:
                    if (gBattleBufferB[gActiveBattler][1] == PARTY_SIZE)
                    {
                        gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
                    }
                    else
                    {
                        *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = gBattleBufferB[gActiveBattler][1];
                        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        {
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= 0xF;
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0);
                            *(gActiveBattler * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 1) = gBattleBufferB[gActiveBattler][3];
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) &= (0xF0);
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 0) |= (gBattleBufferB[gActiveBattler][2] & 0xF0) >> 4;
                            *((gActiveBattler ^ BIT_FLANK) * 3 + (u8 *)(gBattleStruct->battlerPartyOrders) + 2) = gBattleBufferB[gActiveBattler][3];
                        }
                        ++gBattleCommunication[gActiveBattler];
                    }
                    break;
                case B_ACTION_RUN:
                    gHitMarker |= HITMARKER_RUN;
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_WATCH_CAREFULLY:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_BALL:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_BAIT:
                case B_ACTION_SAFARI_GO_NEAR:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_SAFARI_RUN:
                    gHitMarker |= HITMARKER_RUN;
                    ++gBattleCommunication[gActiveBattler];
                    break;
                case B_ACTION_OLDMAN_THROW:
                    ++gBattleCommunication[gActiveBattler];
                    break;
                }
            }
            break;
        case STATE_WAIT_ACTION_CONFIRMED_STANDBY:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
            {
                if (((gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_DOUBLE)) != BATTLE_TYPE_DOUBLE)
                 || (position & BIT_FLANK) != B_FLANK_LEFT
                 || (*(&gBattleStruct->absentBattlerFlags) & gBitTable[GetBattlerAtPosition(position ^ BIT_FLANK)]))
                    BtlController_EmitLinkStandbyMsg(0, 0);
                else
                    BtlController_EmitLinkStandbyMsg(0, 1);
                MarkBattlerForControllerExec(gActiveBattler);
                ++gBattleCommunication[gActiveBattler];
            }
            break;
        case STATE_WAIT_ACTION_CONFIRMED:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                ++gBattleCommunication[ACTIONS_CONFIRMED_COUNT];
            break;
        case STATE_SELECTION_SCRIPT:
            if (*(gBattleStruct->selectionScriptFinished + gActiveBattler))
            {
                gBattleCommunication[gActiveBattler] = *(gBattleStruct->stateIdAfterSelScript + gActiveBattler);
            }
            else
            {
                gBattlerAttacker = gActiveBattler;
                gBattlescriptCurrInstr = gSelectionBattleScripts[gActiveBattler];
                if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                    gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
                gSelectionBattleScripts[gActiveBattler] = gBattlescriptCurrInstr;
            }
            break;
        case STATE_WAIT_SET_BEFORE_ACTION:
            if (!(gBattleControllerExecFlags & ((gBitTable[gActiveBattler]) | (0xF0000000) | (gBitTable[gActiveBattler] << 4) | (gBitTable[gActiveBattler] << 8) | (gBitTable[gActiveBattler] << 0xC))))
                gBattleCommunication[gActiveBattler] = STATE_BEFORE_ACTION_CHOSEN;
            break;
        }
    }
    // Check if everyone chose actions.
    if (gBattleCommunication[ACTIONS_CONFIRMED_COUNT] == gBattlersCount)
        gBattleMainFunc = SetActionsAndBattlersTurnOrder;
}

void SwapTurnOrder(u8 id1, u8 id2)
{
    u32 temp;

    SWAP(gActionsByTurnOrder[id1], gActionsByTurnOrder[id2], temp);
    SWAP(gBattlerByTurnOrder[id1], gBattlerByTurnOrder[id2], temp);
}

u8 GetWhoStrikesFirst(u8 battler1, u8 battler2, bool8 ignoreChosenMoves)
{
    u8 strikesFirst = 0;
    u8 speedMultiplierBattler1 = 0, speedMultiplierBattler2 = 0;
    u32 speedBattler1 = 0, speedBattler2 = 0;
    u8 holdEffect = 0;
    u8 holdEffectParam = 0;
    //u16 moveBattler1 = 0, moveBattler2 = 0;
    s8 priority1 = 0, priority2 = 0;

    if (WEATHER_HAS_EFFECT)
    {
        if ((gBattleMons[battler1].ability == ABILITY_SWIFT_SWIM && gBattleWeather & WEATHER_RAIN_ANY)
         || (gBattleMons[battler1].ability == ABILITY_CHLOROPHYLL && gBattleWeather & WEATHER_SUN_ANY))
            speedMultiplierBattler1 = 2;
        else
            speedMultiplierBattler1 = 1;
        if ((gBattleMons[battler2].ability == ABILITY_SWIFT_SWIM && gBattleWeather & WEATHER_RAIN_ANY)
         || (gBattleMons[battler2].ability == ABILITY_CHLOROPHYLL && gBattleWeather & WEATHER_SUN_ANY))
            speedMultiplierBattler2 = 2;
        else
            speedMultiplierBattler2 = 1;
    }
    else
    {
        speedMultiplierBattler1 = 1;
        speedMultiplierBattler2 = 1;
    }
    speedBattler1 = (gBattleMons[battler1].speed * speedMultiplierBattler1)
                    * (gStatStageRatios[gBattleMons[battler1].statStages[STAT_SPEED]][0])
                    / (gStatStageRatios[gBattleMons[battler1].statStages[STAT_SPEED]][1]);
    if (gBattleMons[battler1].item == ITEM_ENIGMA_BERRY)
    {
        holdEffect = gEnigmaBerries[battler1].holdEffect;
        holdEffectParam = gEnigmaBerries[battler1].holdEffectParam;
    }
    else
    {
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battler1].item);
        holdEffectParam = ItemId_GetHoldEffectParam(gBattleMons[battler1].item);
    }
    // badge boost
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK)
     && FlagGet(FLAG_BADGE03_GET)
     && GetBattlerSide(battler1) == B_SIDE_PLAYER)
        speedBattler1 = (speedBattler1 * 110) / 100;
    if (holdEffect == (HOLD_EFFECT_MACHO_BRACE || HOLD_EFFECT_ULTIMA_BRACE || HOLD_EFFECT_POWERITEM) 
        && (GetBattlerAbility(battler2) != ABILITY_TANGLED_FEET
            || GetBattlerAbility(battler2) != ABILITY_AVIATOR
            || GetBattlerAbility(battler2) != ABILITY_RUN_AWAY
            ))
        speedBattler1 /= 2;
    if ((gBattleMons[battler1].status1 & STATUS1_PARALYSIS)
        && (GetBattlerAbility(battler1) != ABILITY_TANGLED_FEET
            || GetBattlerAbility(battler1) != ABILITY_AVIATOR
            || GetBattlerAbility(battler1) != ABILITY_RUN_AWAY
            ))
        speedBattler1 /= 4;
    //trap effects
    if ((gBattleMons[battler1].status4 & STATUS4_WHIRLPOOL) || (gBattleMons[battler1].status1 & STATUS1_WHIRLPOOL))  //should be good
        speedBattler1 /= 2; //cut speed by half, which is the same as 2 stat stage drops & guess it makes more sense to cut 

    if ((gBattleMons[battler1].status2 & STATUS2_WRAPPED) || (gBattleMons[battler1].status1 & STATUS1_WRAPPED))
        speedBattler1 /= 2; //cut speed by half, which is the same as 2 stat stage drops & guess it makes more sense to cut 
    if (holdEffect == HOLD_EFFECT_QUICK_CLAW && gRandomTurnNumber < (0xFFFF * holdEffectParam) / 100)   //buffed param to 40% rathre than 20
        speedBattler1 = UINT_MAX;
    // check second battlerId's speed
    speedBattler2 = (gBattleMons[battler2].speed * speedMultiplierBattler2)
                    * (gStatStageRatios[gBattleMons[battler2].statStages[STAT_SPEED]][0])
                    / (gStatStageRatios[gBattleMons[battler2].statStages[STAT_SPEED]][1]);
    if (gBattleMons[battler2].item == ITEM_ENIGMA_BERRY)
    {
        holdEffect = gEnigmaBerries[battler2].holdEffect;
        holdEffectParam = gEnigmaBerries[battler2].holdEffectParam;
    }
    else
    {
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battler2].item);
        holdEffectParam = ItemId_GetHoldEffectParam(gBattleMons[battler2].item);
    }
    // badge boost
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK)
     && FlagGet(FLAG_BADGE03_GET)
     && GetBattlerSide(battler2) == B_SIDE_PLAYER)
        speedBattler2 = (speedBattler2 * 110) / 100;
    if (holdEffect == (HOLD_EFFECT_MACHO_BRACE || HOLD_EFFECT_ULTIMA_BRACE || HOLD_EFFECT_POWERITEM) 
        && (GetBattlerAbility(battler2) != ABILITY_TANGLED_FEET
            || GetBattlerAbility(battler2) != ABILITY_AVIATOR
            || GetBattlerAbility(battler2) != ABILITY_RUN_AWAY
            ))
        speedBattler2 /= 2;
    if ((gBattleMons[battler2].status1 & STATUS1_PARALYSIS)
        && (GetBattlerAbility(battler2) != ABILITY_TANGLED_FEET
            || GetBattlerAbility(battler2) != ABILITY_AVIATOR
            || GetBattlerAbility(battler2) != ABILITY_RUN_AWAY
            ))
        speedBattler2 /= 4;
    //trap effects
    if ((gBattleMons[battler2].status4 & STATUS4_WHIRLPOOL) || (gBattleMons[battler2].status1 & STATUS1_WHIRLPOOL))  //should be good
        speedBattler2 /= 2;

    if ((gBattleMons[battler2].status2 & STATUS2_WRAPPED) || (gBattleMons[battler2].status1 & STATUS1_WRAPPED))
        speedBattler2 /= 2;

    if (holdEffect == HOLD_EFFECT_QUICK_CLAW && gRandomTurnNumber < (0xFFFF * holdEffectParam) / 100)   //buffed to 40 % odds rather than 20
        speedBattler2 = UINT_MAX;
    if (!ignoreChosenMoves)
    {
        if (gChosenActionByBattler[battler1] == B_ACTION_USE_MOVE)
            priority1 = GetChosenMovePriority(battler1);
        if (gChosenActionByBattler[battler2] == B_ACTION_USE_MOVE)
            priority2 = GetChosenMovePriority(battler2);
    }
    /*else
    {
        if (gChosenActionByBattler[battler1] == B_ACTION_USE_MOVE)
        {
            if (gProtectStructs[battler1].noValidMoves)
                moveBattler1 = MOVE_STRUGGLE;
            else
                gBattleMoves[moveBattler1].priority = GetChosenMovePriority;
        }
        else
            moveBattler1 = MOVE_NONE;
        if (gChosenActionByBattler[battler2] == B_ACTION_USE_MOVE)
        {
            if (gProtectStructs[battler2].noValidMoves)
                moveBattler2 = MOVE_STRUGGLE;
            else
                moveBattler2 = GetChosenMovePriority;
        }
        else
            moveBattler2 = MOVE_NONE;
    }*/  //think this was old firered stuff I replaced with more optimal emerald stuff
    
    // both move priorities are different than 0
    if (priority1 != 0 || priority2 != 0)
    {
        // both priorities are the same
        if (priority1 == priority2)
        {
            if (speedBattler1 == speedBattler2 && Random() & 1)
                strikesFirst = 2; // same speeds, same priorities
            else if (speedBattler1 < speedBattler2)
                strikesFirst = 1; // battler2 has more speed
            // else battler1 has more speed
        }
        else if (priority1 < priority2)
            strikesFirst = 1; // battler2's move has greater priority
        // else battler1's move has greater priority
    }
    // both priorities are equal to 0
    else
    {
        if (speedBattler1 == speedBattler2 && Random() & 1)
            strikesFirst = 2; // same speeds, same priorities
        else if (speedBattler1 < speedBattler2)
            strikesFirst = 1; // battler2 has more speed
        // else battler1 has more speed
    }
    return strikesFirst;
}

static void SetActionsAndBattlersTurnOrder(void)
{
    s32 turnOrderId = 0;
    s32 i, j;

    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
    {
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
            gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
            ++turnOrderId;
        }
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                {
                    turnOrderId = 5;
                    break;
                }
            }
        }
        else if (gChosenActionByBattler[0] == B_ACTION_RUN)
        {
            gActiveBattler = 0;
            turnOrderId = 5;
        }
        if (turnOrderId == 5) // One of battlers wants to run.
        {
            gActionsByTurnOrder[0] = gChosenActionByBattler[gActiveBattler];
            gBattlerByTurnOrder[0] = gActiveBattler;
            turnOrderId = 1;
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (i != gActiveBattler)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[i];
                    gBattlerByTurnOrder[turnOrderId] = i;
                    ++turnOrderId;
                }
            }
            gBattleMainFunc = CheckFocusPunch_ClearVarsBeforeTurnStarts;
            gBattleStruct->focusPunchBattlerId = 0;
            return;
        }
        else
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_USE_ITEM || gChosenActionByBattler[gActiveBattler] == B_ACTION_SWITCH)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
                    gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
                    ++turnOrderId;
                }
            }
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (gChosenActionByBattler[gActiveBattler] != B_ACTION_USE_ITEM && gChosenActionByBattler[gActiveBattler] != B_ACTION_SWITCH)
                {
                    gActionsByTurnOrder[turnOrderId] = gChosenActionByBattler[gActiveBattler];
                    gBattlerByTurnOrder[turnOrderId] = gActiveBattler;
                    ++turnOrderId;
                }
            }
            for (i = 0; i < gBattlersCount - 1; ++i)
            {
                for (j = i + 1; j < gBattlersCount; ++j)
                {
                    u8 battler1 = gBattlerByTurnOrder[i];
                    u8 battler2 = gBattlerByTurnOrder[j];

                    if (gActionsByTurnOrder[i] != B_ACTION_USE_ITEM
                     && gActionsByTurnOrder[j] != B_ACTION_USE_ITEM
                     && gActionsByTurnOrder[i] != B_ACTION_SWITCH
                     && gActionsByTurnOrder[j] != B_ACTION_SWITCH)
                        if (GetWhoStrikesFirst(battler1, battler2, FALSE))
                            SwapTurnOrder(i, j);
                }
            }
        }
    }
    gBattleMainFunc = CheckFocusPunch_ClearVarsBeforeTurnStarts;
    gBattleStruct->focusPunchBattlerId = 0;
}

static void TurnValuesCleanUp(bool8 var0)
{
    s32 i;
    u8 *dataPtr;

    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        if (var0)
        {
            gProtectStructs[gActiveBattler].protected = FALSE;
            gProtectStructs[gActiveBattler].endured = FALSE;
        }
        else
        {
            dataPtr = (u8 *)(&gProtectStructs[gActiveBattler]);
            for (i = 0; i < sizeof(struct ProtectStruct); ++i)
                dataPtr[i] = 0;
            if (gDisableStructs[gActiveBattler].isFirstTurn)
                --gDisableStructs[gActiveBattler].isFirstTurn;
            if (gDisableStructs[gActiveBattler].rechargeTimer)
            {
                --gDisableStructs[gActiveBattler].rechargeTimer;
                if (gDisableStructs[gActiveBattler].rechargeTimer == 0)
                    gBattleMons[gActiveBattler].status2 &= ~(STATUS2_RECHARGE);
            }
            if (gDisableStructs[gActiveBattler].bideTimer == 0)
                gBattleMons[gActiveBattler].status2 &= ~(STATUS2_BIDE); //status remover
            //makes sure status isn't removed until end turn
        }

        if (gDisableStructs[gActiveBattler].substituteHP == 0)
            gBattleMons[gActiveBattler].status2 &= ~(STATUS2_SUBSTITUTE);
    }
    gSideTimers[0].followmeTimer = 0;
    gSideTimers[1].followmeTimer = 0;
}

static void SpecialStatusesClear(void) //intimidatedmon is a special status so this function is what's resetting it outside of the faint condition
{
    for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
    {
        s32 i;
        u8 *dataPtr = (u8 *)(&gSpecialStatuses[gActiveBattler]);

        for (i = 0; i < sizeof(struct SpecialStatus); ++i)
            dataPtr[i] = 0;
    }
}

static void CheckFocusPunch_ClearVarsBeforeTurnStarts(void)
{
    if (!(gHitMarker & HITMARKER_RUN))
    {
        while (gBattleStruct->focusPunchBattlerId < gBattlersCount)
        {
            gActiveBattler = gBattlerAttacker = gBattleStruct->focusPunchBattlerId;
            ++gBattleStruct->focusPunchBattlerId;
            if (gChosenMoveByBattler[gActiveBattler] == MOVE_FOCUS_PUNCH
             && !(gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
             && !(gDisableStructs[gBattlerAttacker].truantCounter)
             && !(gProtectStructs[gActiveBattler].noValidMoves))
            {
                BattleScriptExecute(BattleScript_FocusPunchSetUp);
                return;
            }
        }
    }
    TryClearRageStatuses();
    gCurrentTurnActionNumber = 0;
    {
        // something stupid needed to match
        u8 zero;

        gCurrentActionFuncId = gActionsByTurnOrder[(zero = 0)];
    }
    gDynamicBasePower = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleMainFunc = RunTurnActionsFunctions;
    gBattleCommunication[3] = 0;
    gBattleCommunication[4] = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattleResources->battleScriptsStack->size = 0;
}

static void RunTurnActionsFunctions(void) //important
{
    if (gBattleOutcome != 0)
        gCurrentActionFuncId = B_ACTION_FINISHED;
    *(&gBattleStruct->savedTurnActionNumber) = gCurrentTurnActionNumber;
    sTurnActionsFuncsTable[gCurrentActionFuncId]();

    if (gCurrentTurnActionNumber >= gBattlersCount) // everyone did their actions, turn finished
    {
        gHitMarker &= ~(HITMARKER_PASSIVE_DAMAGE);
        gBattleMainFunc = sEndTurnFuncsTable[gBattleOutcome & 0x7F];
    }
    else
    {
        if (gBattleStruct->savedTurnActionNumber != gCurrentTurnActionNumber) // action turn has been done, clear hitmarker bits for another battlerId
        {
            gHitMarker &= ~(HITMARKER_NO_ATTACKSTRING);
            gHitMarker &= ~(HITMARKER_UNABLE_TO_USE_MOVE);
        }
    }
}

static void HandleEndTurn_BattleWon(void)
{
    gCurrentActionFuncId = 0;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gBattleTextBuff1[0] = gBattleOutcome;
        gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    //    gBattlescriptCurrInstr = BattleScript_LinkBattleWonOrLost;
        gBattleOutcome &= ~(B_OUTCOME_LINK_BATTLE_RAN);
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_BATTLE_TOWER))
    {
        BattleStopLowHpSound();
        PlayBGM(MUS_VICTORY_TRAINER);
        gBattlescriptCurrInstr = BattleScript_BattleTowerTrainerBattleWon;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && !(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        BattleStopLowHpSound();
        gBattlescriptCurrInstr = BattleScript_LocalTrainerBattleWon;
        switch (gTrainers[gTrainerBattleOpponent_A].trainerClass)
        {
        case CLASS_LEADER_2:
        case CLASS_CHAMPION_2:
            PlayBGM(MUS_VICTORY_GYM_LEADER);
            break;
        case CLASS_BOSS:
        case CLASS_TEAM_ROCKET:
        case CLASS_COOLTRAINER_2:
        case CLASS_ELITE_FOUR_2:
        case CLASS_GENTLEMAN_2:
        default:
            PlayBGM(MUS_VICTORY_TRAINER);
            break;
        }
    }
    else
    {
        gBattlescriptCurrInstr = BattleScript_PayDayMoneyAndPickUpItems;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_BattleLost(void)
{
    gCurrentActionFuncId = 0;
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gBattleTextBuff1[0] = gBattleOutcome;
        gBattlerAttacker = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
    //    gBattlescriptCurrInstr = BattleScript_LinkBattleWonOrLost;
        gBattleOutcome &= ~(B_OUTCOME_LINK_BATTLE_RAN);
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && GetTrainerBattleMode() == TRAINER_BATTLE_EARLY_RIVAL)
        {
            if (GetRivalBattleFlags() & RIVAL_BATTLE_HEAL_AFTER)
                gBattleCommunication[MULTISTRING_CHOOSER] = 1; // Dont do white out text
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 2; // Do white out text
            gBattlerAttacker = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
        gBattlescriptCurrInstr = BattleScript_LocalBattleLost;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_RanFromBattle(void)
{
    gCurrentActionFuncId = 0;
    switch (gProtectStructs[gBattlerAttacker].fleeFlag)
    {
    default:
        gBattlescriptCurrInstr = BattleScript_GotAwaySafely;
        break;
    case 1:
        gBattlescriptCurrInstr = BattleScript_SmokeBallEscape;
        break;
    case 2:
        gBattlescriptCurrInstr = BattleScript_RanAwayUsingMonAbility;
        break;
    }
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_MonFled(void)
{
    gCurrentActionFuncId = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker]);
    gBattlescriptCurrInstr = BattleScript_WildMonFled;
    gBattleMainFunc = HandleEndTurn_FinishBattle;
}

static void HandleEndTurn_FinishBattle(void)
{
    if (gCurrentActionFuncId == B_ACTION_TRY_FINISH || gCurrentActionFuncId == B_ACTION_FINISHED)
    {
        if (!(gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_OLD_MAN_TUTORIAL | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_SAFARI | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_LINK)))
        {
            for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
            {
                if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
                {
                    if (gBattleResults.playerMon1Species == SPECIES_NONE)
                    {
                        gBattleResults.playerMon1Species = gBattleMons[gActiveBattler].species;
                        StringCopy(gBattleResults.playerMon1Name, gBattleMons[gActiveBattler].nickname);
                    }
                    else
                    {
                        gBattleResults.playerMon2Species = gBattleMons[gActiveBattler].species;
                        StringCopy(gBattleResults.playerMon2Name, gBattleMons[gActiveBattler].nickname);
                    }
                }
            }
        }
        TrySetQuestLogBattleEvent();
        TryRestoreStolenItems();    //missing part of knock off, that restorees item.
        //if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)  //GriffinR helped apparently leaving if statement made battle fade exclusive to trainer only fights
            //ClearRematchStateByTrainerId();   //vsonic what does this do again?
        BeginFastPaletteFade(3);
        FadeOutMapMusic(5);
        gBattleMainFunc = FreeResetData_ReturnToOvOrDoEvolutions;
        gCB2_AfterEvolution = BattleMainCB2;
    }
    else if (!gBattleControllerExecFlags)
    {
        gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
    }
}

static void FreeResetData_ReturnToOvOrDoEvolutions(void) //  this causes end battle, and starts evolutions, need to make one for in battle, 
{ // the way this is setup to work on palettefade causes it to happen one after another, return to overworld causes palette fade the else make evo happen during palette fade.
    if (!gPaletteFade.active)
    { // Ok it wasn't that simple for some reason, so this leads to one function, which leads to another that actually does the palette fade that triggers the evo...
        ResetSpriteData();
        if (gLeveledUpInBattle == 0 || gBattleOutcome != B_OUTCOME_WON) //0 is false anything but 0.
            gBattleMainFunc = ReturnFromBattleToOverworld;
        else
            gBattleMainFunc = TryEvolvePokemon;
        FreeAllWindowBuffers();
        if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
        {
            FreeMonSpritesGfx();
            FreeBattleSpritesData();
            FreeBattleResources();
        }
    }
}

#define EVOLUTION_LOGIC

static void TryEvolvePokemon(void) //want battle evolution for player and opponenet for enemy need to work out how to give them exp.
{ //     after they have exp need set function to make it feel real that they would level up i.e they aren't starting from 0.
    s32 i; //  for that make random function that would get their needed exp to level and then random divide that by either 2, 3, or 4 to increase their chance of lvl in battle.
    // player can use this and the above function to evolve, but enemy needs a specific one, that won't take out of battle, make it so if they can evolve they will. 
    while (gLeveledUpInBattle != 0) // use CFRU mega evolve for opponent.
    {
        for (i = 0; i < PARTY_SIZE; ++i)
        {
            if (gLeveledUpInBattle & gBitTable[i])
            {
                u16 species;
                u8 levelUpBits = gLeveledUpInBattle;

                levelUpBits &= ~(gBitTable[i]);
                gLeveledUpInBattle = levelUpBits;
                species = GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_NORMAL, levelUpBits);
                if (species != SPECIES_NONE)
                {
                    gBattleMainFunc = WaitForEvoSceneToFinish;
                    EvolutionScene(&gPlayerParty[i], species, 0x81, i);
                    return;
                }// for evo in battle, use  if (gCurrentTurnActionNumber >= gBattlersCount) && (gLeveledUpInBattle != 0 || gBattleOutcome != B_OUTCOME_WON)
            }// need to import mega evo graphic,  also make it check for or come after learn move on level up then, go into gBattleMainFunc = TryEvolvePokemon;
        }
    }
    gBattleMainFunc = ReturnFromBattleToOverworld;
}

static void WaitForEvoSceneToFinish(void)
{
    if (gMain.callback2 == BattleMainCB2)
        gBattleMainFunc = TryEvolvePokemon;
}

static void ReturnFromBattleToOverworld(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK))
    {
        RandomlyGivePartyPokerus(gPlayerParty);
        PartySpreadPokerus(gPlayerParty);
    }
    if (!(gBattleTypeFlags & BATTLE_TYPE_LINK) || !gReceivedRemoteLinkPlayers)
    {
        gSpecialVar_Result = gBattleOutcome;
        gMain.inBattle = FALSE;
        gMain.callback1 = gPreBattleCallback1;
        if (gBattleTypeFlags & BATTLE_TYPE_ROAMER)
        {
            UpdateRoamerHPStatus(&gEnemyParty[0]);
#ifdef BUGFIX
            if ((gBattleOutcome == B_OUTCOME_WON) || gBattleOutcome == B_OUTCOME_CAUGHT)
#else
            if ((gBattleOutcome & B_OUTCOME_WON) || gBattleOutcome == B_OUTCOME_CAUGHT) // Bug: When Roar is used by roamer, gBattleOutcome is B_OUTCOME_PLAYER_TELEPORTED (5).
#endif                                                                                  // & with B_OUTCOME_WON (1) will return TRUE and deactivates the roamer.
                SetRoamerInactive();
        }
        m4aSongNumStop(SE_LOW_HEALTH);
        SetMainCallback2(gMain.savedCallback);
    }
}

void RunBattleScriptCommands_PopCallbacksStack(void)
{
    if (gCurrentActionFuncId == B_ACTION_TRY_FINISH || gCurrentActionFuncId == B_ACTION_FINISHED)
    {
        if (gBattleResources->battleCallbackStack->size != 0)
            --gBattleResources->battleCallbackStack->size;
        gBattleMainFunc = gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size];
    }
    else
    {
        if (!gBattleControllerExecFlags)
            gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
    }
}

void RunBattleScriptCommands(void)
{
    if (!gBattleControllerExecFlags)
        gBattleScriptingCommandsTable[gBattlescriptCurrInstr[0]]();
}

#define CAN_ABILITY_ABSORB (gBattleMons[gActiveBattler].status1 == 0 && !(gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION))

static void HandleAction_UseMove(void)
{
    u32 i, side, moveType, var = 4;
    u16 moveTarget;

    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    if (*(&gBattleStruct->absentBattlerFlags) & gBitTable[gBattlerAttacker])
    {
        gCurrentActionFuncId = B_ACTION_FINISHED;
        return;
    }
    gCritMultiplier = 1;
    gBattleScripting.dmgMultiplier = 1;
    gBattleStruct->atkCancellerTracker = 0;
    gMoveResultFlags = 0;
    gMultiHitCounter = 0;
    gMultiTask = 0;
    gBattleCommunication[6] = 0;
    gCurrMovePos = gChosenMovePos = *(gBattleStruct->chosenMovePositions + gBattlerAttacker);
    // choose move
    if (gProtectStructs[gBattlerAttacker].noValidMoves)
    {
        gProtectStructs[gBattlerAttacker].noValidMoves = 0;
        gCurrentMove = gChosenMove = MOVE_STRUGGLE;
        gHitMarker |= HITMARKER_NO_PPDEDUCT;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(MOVE_STRUGGLE, 0);
    }
    else if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS || gBattleMons[gBattlerAttacker].status2 & STATUS2_RECHARGE)
    {
        gCurrentMove = gChosenMove = gLockedMoves[gBattlerAttacker];
    }
    // encore forces you to use the same move
    else if (gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE
          && gDisableStructs[gBattlerAttacker].encoredMove == gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrentMove = gChosenMove = gDisableStructs[gBattlerAttacker].encoredMove;
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    // check if the encored move wasn't overwritten
    else if (gDisableStructs[gBattlerAttacker].encoredMove != MOVE_NONE
          && gDisableStructs[gBattlerAttacker].encoredMove != gBattleMons[gBattlerAttacker].moves[gDisableStructs[gBattlerAttacker].encoredMovePos])
    {
        gCurrMovePos = gChosenMovePos = gDisableStructs[gBattlerAttacker].encoredMovePos;
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        gDisableStructs[gBattlerAttacker].encoredMove = MOVE_NONE;
        gDisableStructs[gBattlerAttacker].encoredMovePos = 0;
        gDisableStructs[gBattlerAttacker].encoreTimer = 0;
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    else if (gBattleMons[gBattlerAttacker].moves[gCurrMovePos] != gChosenMoveByBattler[gBattlerAttacker])
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
        *(gBattleStruct->moveTarget + gBattlerAttacker) = GetMoveTarget(gCurrentMove, 0);
    }
    else
    {
        gCurrentMove = gChosenMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
    }
    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        gBattleResults.lastUsedMovePlayer = gCurrentMove;
    else
        gBattleResults.lastUsedMoveOpponent = gCurrentMove;

    // Set dynamic move type.
    SetTypeBeforeUsingMove(gChosenMove, gBattlerAttacker);
    GET_MOVE_TYPE(gChosenMove, moveType);

    moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, gCurrentMove);

    // choose target
    side = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE;
    if (gSideTimers[side].followmeTimer != 0
     && gBattleMoves[gCurrentMove].target == MOVE_TARGET_SELECTED
     && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gSideTimers[side].followmeTarget)
     && gBattleMons[gSideTimers[side].followmeTarget].hp != 0)
    {
        gBattlerTarget = gSideTimers[side].followmeTarget;
    }
    else if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
          && gSideTimers[side].followmeTimer == 0
          && (gBattleMoves[gCurrentMove].power != 0
              || (moveTarget != MOVE_TARGET_USER && moveTarget != MOVE_TARGET_ALL_BATTLERS))
          && ((GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_LIGHTNING_ROD && moveType == TYPE_ELECTRIC)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_VOLT_ABSORB && moveType == TYPE_ELECTRIC)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_MOTOR_DRIVE && moveType == TYPE_ELECTRIC)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_STORM_DRAIN && moveType == TYPE_WATER)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_WATER_ABSORB && moveType == TYPE_WATER)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_DRY_SKIN && moveType == TYPE_WATER)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_EROSION && moveType == TYPE_ROCK)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_SAP_SIPPER && moveType == TYPE_GRASS)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_GLACIAL_ICE && moveType == TYPE_ICE)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_LAVA_FISSURE && moveType == TYPE_FIRE)
            || (GetBattlerAbility(*(gBattleStruct->moveTarget + gBattlerAttacker)) != ABILITY_FLASH_FIRE && moveType == TYPE_FIRE)))
    {
        side = GetBattlerSide(gBattlerAttacker);
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; gActiveBattler++)
             if (side != GetBattlerSide(gActiveBattler) //I think I need to add status clause to below linses?
                && *(gBattleStruct->moveTarget + gBattlerAttacker) != gActiveBattler
                && ((GetBattlerAbility(gActiveBattler) == ABILITY_LIGHTNING_ROD && moveType == TYPE_ELECTRIC && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_VOLT_ABSORB && moveType == TYPE_ELECTRIC && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_MOTOR_DRIVE && moveType == TYPE_ELECTRIC && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_STORM_DRAIN && moveType == TYPE_WATER && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_WATER_ABSORB && moveType == TYPE_WATER && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_DRY_SKIN && moveType == TYPE_WATER && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_EROSION && moveType == TYPE_ROCK && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_SAP_SIPPER && moveType == TYPE_GRASS && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_GLACIAL_ICE && moveType == TYPE_ICE && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_LAVA_FISSURE && moveType == TYPE_FIRE && CAN_ABILITY_ABSORB)
                 || (GetBattlerAbility(gActiveBattler) == ABILITY_FLASH_FIRE && moveType == TYPE_FIRE && CAN_ABILITY_ABSORB))
                && GetBattlerTurnOrderNum(gActiveBattler) < var
                && gBattleMoves[gCurrentMove].effect != EFFECT_SNIPE_SHOT
                && (GetBattlerAbility(gBattlerAttacker) != ABILITY_PROPELLER_TAIL
                 || GetBattlerAbility(gBattlerAttacker) != ABILITY_STALWART))
                var = GetBattlerTurnOrderNum(gActiveBattler);
        if (var == 4)
        {
            if (gBattleMoves[gChosenMove].target & MOVE_TARGET_RANDOM)
            {
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                {
                    if (Random() & 1)
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                    else
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
                }
                else
                {
                    if (Random() & 1)
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
                    else
                        gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
                }
            }
            else
            {
                gBattlerTarget = *(gBattleStruct->moveTarget + gBattlerAttacker);
            }
            if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
            {
                if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
                {
                    gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
                }
                else
                {
                    gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_SIDE);
                    if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                        gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
                }
            }
        }
        else
        {
            gActiveBattler = gBattlerByTurnOrder[var];
            RecordAbilityBattle(gActiveBattler, gBattleMons[gActiveBattler].ability);
            //gSpecialStatuses[gActiveBattler].lightningRodRedirected = 1;  //idk why this sets this here, if its also set by getmovetarget in battle_util.c?
            gBattlerTarget = gActiveBattler;
        }
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE
          && gBattleMoves[gChosenMove].target & MOVE_TARGET_RANDOM)
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        }
        else
        {
            if (Random() & 1)
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
            else
                gBattlerTarget = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        }
        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget]
         && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
    }
    else
    {
        gBattlerTarget = *(gBattleStruct->moveTarget + gBattlerAttacker);
        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
        {
            if (GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            {
                gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
            }
            else
            {
                gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerAttacker) ^ BIT_SIDE);
                if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                    gBattlerTarget = GetBattlerAtPosition(GetBattlerPosition(gBattlerTarget) ^ BIT_FLANK);
            }
        }
    }

    // Record HP of each battler
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        gBattleStruct->hpBefore[i] = gBattleMons[i].hp;

    gBattlescriptCurrInstr = gBattleScriptsForMoveEffects[gBattleMoves[gCurrentMove].effect];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_Switch(void) //actual switch code
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gActionSelectionCursor[gBattlerAttacker] = 0;
    gMoveSelectionCursor[gBattlerAttacker] = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, *(gBattleStruct->battlerPartyIndexes + gBattlerAttacker));
    gBattleScripting.battler = gBattlerAttacker;
    gBattlescriptCurrInstr = BattleScript_ActionSwitch;
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    if (gBattleResults.playerSwitchesCounter < 255)
        ++gBattleResults.playerSwitchesCounter;
}

static void HandleAction_UseItem(void)
{
    gBattlerAttacker = gBattlerTarget = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);
    gLastUsedItem = gBattleBufferB[gBattlerAttacker][1] | (gBattleBufferB[gBattlerAttacker][2] << 8);
    if (gLastUsedItem <= ITEM_PREMIER_BALL) // is ball
    {
        gBattlescriptCurrInstr = gBattlescriptsForBallThrow[gLastUsedItem];
    }
    else if (gLastUsedItem == ITEM_POKE_DOLL || gLastUsedItem == ITEM_FLUFFY_TAIL)
    {
        gBattlescriptCurrInstr = gBattlescriptsForRunningByItem[0];
    }
    else if (gLastUsedItem == ITEM_POKE_FLUTE)
    {
        gBattlescriptCurrInstr = gBattlescriptsForRunningByItem[1];
    }
    else if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
    {
        gBattlescriptCurrInstr = gBattlescriptsForUsingItem[0];
    }
    else
    {
        gBattleScripting.battler = gBattlerAttacker;
        switch (*(gBattleStruct->AI_itemType + (gBattlerAttacker >> 1)))
        {
        case AI_ITEM_FULL_RESTORE:
        case AI_ITEM_HEAL_HP:
            break;
        case AI_ITEM_CURE_CONDITION:
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            if (*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 1)
            {
                if (*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 0x3E)
                    gBattleCommunication[MULTISTRING_CHOOSER] = 5;
            }
            else
            {
                while (!(*(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) & 1))
                {
                    *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) >>= 1;
                    ++gBattleCommunication[MULTISTRING_CHOOSER];
                }
            }
            break;
        case AI_ITEM_X_STAT:
            gBattleCommunication[MULTISTRING_CHOOSER] = 4;
            if (*(gBattleStruct->AI_itemFlags + (gBattlerAttacker >> 1)) & 0x80)
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = 5;
            }
            else
            {
                PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
                PREPARE_STRING_BUFFER(gBattleTextBuff2, CHAR_X);
                while (!((*(gBattleStruct->AI_itemFlags + (gBattlerAttacker >> 1))) & 1))
                {
                    *(gBattleStruct->AI_itemFlags + gBattlerAttacker / 2) >>= 1;
                    ++gBattleTextBuff1[2];
                }
                gBattleScripting.animArg1 = gBattleTextBuff1[2] + 14;
                gBattleScripting.animArg2 = 0;
            }
            break;
        case AI_ITEM_GUARD_SPECS:
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
            else
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            break;
        }

        gBattlescriptCurrInstr = gBattlescriptsForUsingItem[*(gBattleStruct->AI_itemType + gBattlerAttacker / 2)];
    }
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

#define RUN_LOGIC_PT2
bool8 TryRunFromBattle(u8 battler)
{
    bool8 effect = FALSE;
    u8 holdEffect;
    u8 speedVar;

    if (gBattleMons[battler].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[battler].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battler].item);
    gPotentialItemEffectBattler = battler;
    if (holdEffect == HOLD_EFFECT_CAN_ALWAYS_RUN)
    {
        gLastUsedItem = gBattleMons[battler].item;
        gProtectStructs[battler].fleeFlag = 1;
        ++effect;
    }
    else if (gBattleMons[battler].ability == ABILITY_RUN_AWAY)
    {
        gLastUsedAbility = ABILITY_RUN_AWAY;
        gProtectStructs[battler].fleeFlag = 2;
        ++effect;
    }
    else if (gBattleMons[gActiveBattler].ability == ABILITY_DEFEATIST
        && gSpecialStatuses[gActiveBattler].defeatistActivated)
    {
        gLastUsedAbility = ABILITY_DEFEATIST;
        gProtectStructs[battler].fleeFlag = 2;
        ++effect;
    }
    else if (gBattleMons[gActiveBattler].ability == ABILITY_AVIATOR)
    {
        gLastUsedAbility = ABILITY_AVIATOR;
        gProtectStructs[battler].fleeFlag = 2;
        ++effect;
    }
    else if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
    {
        if (GetBattlerSide(battler) == B_SIDE_PLAYER)
            ++effect;
    }
    else
    {
        if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        {
            if (gBattleMons[battler].speed < gBattleMons[BATTLE_OPPOSITE(battler)].speed)
            {
                speedVar = (gBattleMons[battler].speed * 128) / (gBattleMons[BATTLE_OPPOSITE(battler)].speed) + (gBattleStruct->runTries * 30);
                if (speedVar > (Random() & 0xFF))
                    ++effect;
            }
            else // same speed or faster
            {
                ++effect;
            }
        }

        ++gBattleStruct->runTries;
    }
    if (effect)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        gBattleOutcome = B_OUTCOME_RAN;
    }
    return effect;
}

static void HandleAction_Run(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gCurrentTurnActionNumber = gBattlersCount;
        for (gActiveBattler = 0; gActiveBattler < gBattlersCount; ++gActiveBattler)
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_LOST;
            }
            else
            {
                if (gChosenActionByBattler[gActiveBattler] == B_ACTION_RUN)
                    gBattleOutcome |= B_OUTCOME_WON;
            }
        }
        gBattleOutcome |= B_OUTCOME_LINK_BATTLE_RAN;
    }
    else
    {
        if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        {
            if (!TryRunFromBattle(gBattlerAttacker)) // failed to run away
            {
                ClearFuryCutterDestinyBondGrudge(gBattlerAttacker);
                gBattleCommunication[MULTISTRING_CHOOSER] = 3;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
        }
        else
        {
            if (gBattleMons[gBattlerAttacker].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
            {
                gBattleCommunication[MULTISTRING_CHOOSER] = 4;
                gBattlescriptCurrInstr = BattleScript_PrintFailedToRunString;
                gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
            }
            else
            {
                gCurrentTurnActionNumber = gBattlersCount;
                gBattleOutcome = B_OUTCOME_MON_FLED;
            }
        }
    }
}

static void HandleAction_WatchesCarefully(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    if (gBattleStruct->safariGoNearCounter != 0)
    {
        --gBattleStruct->safariGoNearCounter;
        if (gBattleStruct->safariGoNearCounter == 0)
        {
            *(&gBattleStruct->safariCatchFactor) = gBaseStats[GetMonData(gEnemyParty, MON_DATA_SPECIES)].catchRate * 100 / 1275;
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
        }
    }
    else
    {
        if (gBattleStruct->safariPkblThrowCounter != 0)
        {
            --gBattleStruct->safariPkblThrowCounter;
            if (gBattleStruct->safariPkblThrowCounter == 0)
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
            else
                gBattleCommunication[5] = 2;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
        }
    }
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[0];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    --gNumSafariBalls;
    gLastUsedItem = ITEM_SAFARI_BALL;
    gBattlescriptCurrInstr = gBattlescriptsForBallThrow[ITEM_SAFARI_BALL];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_ThrowBait(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleStruct->safariPkblThrowCounter += Random() % 5 + 2;
    if (gBattleStruct->safariPkblThrowCounter > 6)
        gBattleStruct->safariPkblThrowCounter = 6;
    gBattleStruct->safariGoNearCounter = 0;
    gBattleStruct->safariCatchFactor >>= 1;
    if (gBattleStruct->safariCatchFactor <= 2)
        gBattleStruct->safariCatchFactor = 3;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[2];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_ThrowRock(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattleStruct->safariGoNearCounter += Random() % 5 + 2;
    if (gBattleStruct->safariGoNearCounter > 6)
        gBattleStruct->safariGoNearCounter = 6;
    gBattleStruct->safariPkblThrowCounter = 0;
    gBattleStruct->safariCatchFactor <<= 1;
    if (gBattleStruct->safariCatchFactor > 20)
        gBattleStruct->safariCatchFactor = 20;
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[1];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
}

static void HandleAction_SafariZoneRun(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    PlaySE(SE_FLEE);
    gCurrentTurnActionNumber = gBattlersCount;
    gBattleOutcome = B_OUTCOME_RAN;
}

static void HandleAction_OldManBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
    gBattlescriptCurrInstr = gBattlescriptsForSafariActions[3];
    gCurrentActionFuncId = B_ACTION_EXEC_SCRIPT;
    gActionsByTurnOrder[1] = B_ACTION_FINISHED;
}

static void HandleAction_TryFinish(void)
{
    if (!HandleFaintedMonActions())
    {
        gBattleStruct->faintedActionsState = 0;
        gCurrentActionFuncId = B_ACTION_FINISHED;
    }
}


static void HandleAction_NothingIsFainted(void)
{
    ++gCurrentTurnActionNumber;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED
                    | HITMARKER_NO_PPDEDUCT | HITMARKER_IGNORE_SAFEGUARD | HITMARKER_PASSIVE_DAMAGE
                    | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONISE_EFFECT
                    | HITMARKER_CHARGING | HITMARKER_NEVER_SET);
}

static void HandleAction_ActionFinished(void) //may be important for intimidate synchronize adn trace changes
{
    ++gCurrentTurnActionNumber;
    gCurrentActionFuncId = gActionsByTurnOrder[gCurrentTurnActionNumber];
    SpecialStatusesClear(); //yeah the function call here is what resets intimidated mon status,
    gHitMarker &= ~(HITMARKER_DESTINYBOND | HITMARKER_IGNORE_SUBSTITUTE | HITMARKER_ATTACKSTRING_PRINTED 
                    | HITMARKER_NO_PPDEDUCT | HITMARKER_IGNORE_SAFEGUARD | HITMARKER_PASSIVE_DAMAGE
                    | HITMARKER_OBEYS | HITMARKER_WAKE_UP_CLEAR | HITMARKER_SYNCHRONISE_EFFECT
                    | HITMARKER_CHARGING | HITMARKER_NEVER_SET | HITMARKER_IGNORE_DISGUISE);
    gCurrentMove = MOVE_NONE; // but it doesn't loop because the function doesn't get called except at battle start and switch i.e switch in abilities
    gBattleMoveDamage = 0;
    gMoveResultFlags = 0; //so what I need is to change activation condition or add a new activation condtions
    gBattleScripting.animTurn = 0; //that will be on switch in but check opposite field for a mon with intimidate
    gBattleScripting.animTargetsHit = 0;//and reactivate intimidate if mon doesn't have STATUS3_INTIMIDATE_POKES
    gLastLandedMoves[gBattlerAttacker] = 0;
    gLastHitByType[gBattlerAttacker] = 0;//actually all I need to do is add that extra function call, for switch in
    gBattleStruct->dynamicMoveType = 0;//and then add STATUS3_INTIMIDATE_POKES filter to existing break condition and it should work perfect
    gDynamicBasePower = 0;//if target is on opposite side and visible and not already intimidated it will activate otherwise it'll skip/do nothing!! need test
    gBattleScripting.atk49_state = 0;
    gBattleCommunication[MOVE_EFFECT_BYTE] = 0;
    gBattleCommunication[ACTIONS_CONFIRMED_COUNT] = 0;
    gBattleScripting.multihitMoveEffect = 0;
    gBattleResources->battleScriptsStack->size = 0;
}

s8 GetChosenMovePriority(u8 battlerId) //made u8 (in test build)
{
    u16 move;
    gProtectStructs[battlerId].pranksterElevated = 0;
    if (gProtectStructs[battlerId].noValidMoves)
        move = MOVE_STRUGGLE;
    else
        move = gBattleMons[battlerId].moves[*(gBattleStruct->chosenMovePositions + battlerId)];

    return GetMovePriority(battlerId, move);
}

#define PRIORITY_EFFECTS

s8 GetMovePriority(u8 battlerId, u16 move) //ported from emerald the EXACT thing I needed to make nuisance work (facepalm)
{ //adjusted battlerId made u8,
    s8 priority;


    priority = gBattleMoves[move].priority;
    //if gBattleMoves[move].flags == FLAG_DMG_2X_IN_AIR & target is STATUS3_ON_AIR increment priority (gStatuses3[battler] & STATUS3_SKY_DROPPED)
    if (gBattleMoves[move].flags == FLAG_DMG_2X_IN_AIR
        && gStatuses3[gBattlerTarget] & STATUS3_ON_AIR) //done because flying mon are fast, and most mon with this move are slow, so would never land otherwise
    {
        priority++;
    }//that's good, just need to figure how to set grounded if by 2x flag move while in air - done in bs command

    if (GetBattlerAbility(battlerId) == ABILITY_GALE_WINGS
        && gBattleMoves[move].type == TYPE_FLYING)
    {
        priority++;
    }
    else if (GetBattlerAbility(battlerId) == ABILITY_PRANKSTER && IS_MOVE_STATUS(move))
    {
        priority++;
    }
    else if (gBattleMoves[move].effect == EFFECT_GRASSY_GLIDE && gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN && IsBattlerGrounded(battlerId))
    {
        priority++;
    }
    else if (GetBattlerAbility(battlerId) == ABILITY_TRIAGE)
    {
        switch (gBattleMoves[move].effect)
        {
        case EFFECT_RESTORE_HP:
        case EFFECT_REST:
        case EFFECT_MORNING_SUN:
        case EFFECT_MOONLIGHT:
        case EFFECT_SYNTHESIS:
        case EFFECT_HEAL_PULSE:
        case EFFECT_HEALING_WISH:
        case EFFECT_ROOST:
        case EFFECT_SWALLOW:
        case EFFECT_WISH:
        case EFFECT_SOFTBOILED:
        case EFFECT_ABSORB:
            priority += 3;
            break;
        }
    }
    else if (gBattleMons[battlerId].ability == ABILITY_NUISANCE
        && (gBattleMoves[move].power <= 60 || gDynamicBasePower <= 60)) //added dynamic for moves like hidden power
    {
        priority += 3;
    }

    else if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE
        && gDisableStructs[gBattlerAttacker].bideTimer == 0
        && gCurrentMove == MOVE_BIDE)
    {
        priority = 3; //if works, second attack will go before most priority moves
    }
    return priority;
}
