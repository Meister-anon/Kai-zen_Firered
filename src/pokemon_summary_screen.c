#include "global.h"
#include "gflib.h"
#include "pokemon.h"
#include "pokemon_summary_screen.h"
#include "help_system.h"
#include "task.h"
#include "menu_helpers.h"
#include "link.h"
#include "overworld.h"
#include "constants/songs.h"
#include "strings.h"
#include "new_menu_helpers.h"
#include "menu.h"
#include "constants/items.h"
#include "data.h"
#include "item.h"
#include "constants/party_menu.h"
#include "trade.h"
#include "battle_main.h"
#include "scanline_effect.h"
#include "constants/moves.h"
#include "dynamic_placeholder_text_util.h"
#include "constants/region_map_sections.h"
#include "region_map.h"
#include "field_specials.h"
#include "party_menu.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "event_data.h"
#include "trainer_pokemon_sprites.h"
#include "battle_anim.h"
#include "pokeball.h"
#include "pokemon_icon.h"
#include "battle_interface.h"
#include "mon_markings.h"
#include "pokemon_storage_system.h"

// needs conflicting header to match (curIndex is s8 in the function, but has to be defined as u8 here)
extern s16 SeekToNextMonInBox(struct BoxPokemon * boxMons, u8 curIndex, u8 maxIndex, u8 flags);

static void BufferSelectedMonData(struct Pokemon * mon);
static void CB2_SetUpPSS(void);
static void PokeSum_TryPlayMonCry(void);
static void PokeSum_RemoveWindows(u8 curPageIndex);
static void Task_PokeSum_FlipPages(u8 taskId);
static void Task_FlipPages_FromInfo(u8 taskId);
static void Task_PokeSum_SwitchDisplayedPokemon(u8 taskId);
static void PokeSum_SeekToNextMon(u8, s8);
static void Task_DestroyResourcesOnExit(u8 taskId);
static void PokeSum_HideSpritesBeforePageFlip(void);
static void PokeSum_ShowSpritesBeforePageFlip(void);
static void PokeSum_UpdateWin1ActiveFlag(u8 curPageIndex);
static void PokeSum_AddWindows(u8 curPageIndex);
static void PokeSum_PrintPageHeaderText(u8 curPageIndex);
static void PokeSum_InitBgCoordsBeforePageFlips(void);
static u8 PokeSum_IsPageFlipFinished(u8);
static void PokeSum_SetHelpContext(void);
static void Task_HandleInput_SelectMove(u8 taskId);
static void PokeSum_CopyNewBgTilemapBeforePageFlip_2(void);
static void PokeSum_CopyNewBgTilemapBeforePageFlip(void);
static void PokeSum_DrawBg3Tilemap(void);
static void PokeSum_PrintPageHeaderText(u8 curPageIndex);
static void PokeSum_PrintRightPaneText(void);
static void PokeSum_PrintBottomPaneText(void);
static void PokeSum_PrintAbilityDataOrMoveTypes(void);
static void PokeSum_PrintMonTypeIcons(void);
static void PokeSum_PrintPageName(const u8 * str);
static void PokeSum_PrintControlsString(const u8 * str);
static void PrintMonLevelNickOnWindow2(const u8 * str);
static void PokeSum_UpdateBgPriorityForPageFlip(u8 setBg0Priority, u8 keepBg1Bg2PriorityOrder);
static void ShowOrHideHpBarObjs(u8 invisible);
static void ShowOrHideExpBarObjs(u8 invisible);
static void PokeSum_ShowOrHideMonPicSprite(u8 invisible);
static void PokeSum_ShowOrHideMonMarkingsSprite(u8 invisible);
static void ShowOrHideBallIconObj(u8 invisible);
static void ShowOrHideStatusIcon(u8 invisible);
static void HideShowPokerusIcon(u8 invisible);
static void HideShowShinyStar(u8 invisible);
static void ShoworHideMoveSelectionCursor(u8 invisible);
static void PokeSum_ShowOrHideMonIconSprite(u8 invisible);
static void PokeSum_Setup_ResetCallbacks(void);
static void PokeSum_Setup_InitGpu(void);
static void PokeSum_Setup_SpritesReset(void);
static u8 PokeSum_HandleLoadBgGfx(void);
static u8 PokeSum_HandleCreateSprites(void);
static void PokeSum_CreateWindows(void);
static u8 PokeSum_Setup_BufferStrings(void);
static void CommitStaticWindowTilemaps(void);
static void PokeSum_Setup_SetVBlankCallback(void);
static void PokeSum_FinishSetup(void);
static void BufferMonInfo(void);
static void BufferMonSkills(void);
static void BufferMonMoves(void);
static u8 StatusToAilment(u32 status);
static void BufferMonMoveI(u8);
static u16 GetMonMoveBySlotId(struct Pokemon * mon, u8 moveSlot);
static u16 GetMonPpByMoveSlot(struct Pokemon * mon, u8 moveSlot);
static void CreateShinyStarObj(u16, u16);
static void CreatePokerusIconObj(u16, u16);
static void PokeSum_CreateMonMarkingsSprite(void);
static void CreateMoveSelectionCursorObjs(u16, u16);
static void CreateMonStatusIconObj(u16, u16);
static void CreateHpBarObjs(u16, u16);
static void CreateExpBarObjs(u16, u16);
static void CreateBallIconObj(void);
static void PokeSum_CreateMonIconSprite(void);
static void PokeSum_CreateMonPicSprite(void);
static void Task_InputHandler_SelectOrForgetMove(u8 taskId);
static void CB2_RunPokemonSummaryScreen(void);
static void PrintInfoPage(void);
static void PrintSkillsPage(void);
static void PrintMovesPage(void);
static void PokeSum_PrintMoveName(u8 i);
static void PokeSum_PrintTrainerMemo(void);
static void PokeSum_PrintExpPoints_NextLv(void);
static void PokeSum_PrintSelectedMoveStats(void);
static void PokeSum_PrintTrainerMemo_Mon(void);
static void PokeSum_PrintTrainerMemo_Egg(void);
static bool32 MapSecIsInKantoOrSevii(u8 metLocation);
static bool32 IsMultiBattlePartner(void);
static bool32 PokeSum_IsMonBoldOrGentle(u8 nature);
static void PokeSum_PrintTrainerMemo_Mon_NotHeldByOT(void);
static bool32 CurrentMonIsFromGBA(void);
static u8 PokeSum_BufferOtName_IsEqualToCurrentOwner(struct Pokemon * mon);
static void PokeSum_PrintAbilityNameAndDesc(void);
static void PokeSum_DrawMoveTypeIcons(void);
static void PokeSum_DestroySprites(void);
static void PokeSum_FlipPages_HandleBgHofs(void);
static void SwapMonMoveSlots(void);
static void SwapBoxMonMoveSlots(void);
static void UpdateCurrentMonBufferFromPartyOrBox(struct Pokemon * mon);
static void PokeSum_SetMonPicSpriteCallback(u16 spriteId);
static void SpriteCB_MoveSelectionCursor(struct Sprite * sprite);
static void UpdateMonStatusIconObj(void);
static void UpdateHpBarObjs(void);
static void UpdateExpBarObjs(void);
static void ShowPokerusIconObjIfHasOrHadPokerus(void);
static void ShowShinyStarObjIfMonShiny(void);
static void PokeSum_DestroyMonMarkingsSprite(void);
static void PokeSum_UpdateMonMarkingsAnim(void);
static s8 SeekToNextMonInSingleParty(s8);
static s8 SeekToNextMonInMultiParty(s8);

struct PokemonSummaryScreenData
{
    u16 bg1TilemapBuffer[0x800];
    u16 bg2TilemapBuffer[0x800];
    u16 bg3TilemapBuffer[0x800];
    u8 ALIGNED(4) windowIds[7];

    u8 ALIGNED(4) unk3008;
    u8 ALIGNED(4) ballIconSpriteId;
    u8 ALIGNED(4) monPicSpriteId;
    u8 ALIGNED(4) monIconSpriteId;

    u8 ALIGNED(4) inputHandlerTaskId;
    u8 ALIGNED(4) inhibitPageFlipInput;

    u8 ALIGNED(4) numMonPicBounces;

    bool32 isEnemyParty; /* 0x3024 */

    struct PokeSummary
    {
        u8 ALIGNED(4) speciesNameStrBuf[POKEMON_NAME_LENGTH + 1]; //neeed add +1 to give enough buff
        u8 ALIGNED(4) nicknameStrBuf[POKEMON_NAME_LENGTH + 1];
        u8 ALIGNED(4) otNameStrBuf[12];
        u8 ALIGNED(4) otNameStrBufs[2][12];

        u8 ALIGNED(4) dexNumStrBuf[5];
        u8 ALIGNED(4) unk306C[7];
        u8 ALIGNED(4) itemNameStrBuf[ITEM_NAME_LENGTH + 1];

        u8 ALIGNED(4) genderSymbolStrBuf[3];
        u8 ALIGNED(4) levelStrBuf[7];
        u8 ALIGNED(4) curHpStrBuf[9];
        u8 ALIGNED(4) statValueStrBufs[5][5];

        u8 ALIGNED(4) moveCurPpStrBufs[5][11]; //these already have enough space to display transform mon moves, just use 0-3 seutp like abilityname
        u8 ALIGNED(4) moveMaxPpStrBufs[5][11]; //will set moves but not think will keep type as is, in summary screen since its still your ditto.
        u8 ALIGNED(4) moveNameStrBufs[5][MOVE_NAME_LENGTH + 1]; //if you've caught the mon before you should already know, if you haven't
        u8 ALIGNED(4) movePowerStrBufs[5][5]; //then ditto transforming wouldn't help tell you.
        u8 ALIGNED(4) moveAccuracyStrBufs[5][5];

        //u8 ALIGNED(4) expPointsStrBuf[9];   //planning to remove this, to make room for expanded ability descriptions
        u8 ALIGNED(4) expToNextLevelStrBuf[9];

        u8 ALIGNED(4) abilityNameStrBuf[4][ABILITY_NAME_LENGTH + 1]; //made 4 string values eventually make constants for each, slot 1 slot 2 slot 3(rotatoin) and party
        u8 ALIGNED(4) abilityDescStrBuf[4][ABILITY_DESCRIPTION_LENGTH + 1]; //tested & works
    } summary; //move descriptinos are off, clearly a result of chang to the ability buffs here? don't know why didn't see taht in my pret red version unless I did and forgot?

    u8 ALIGNED(4) isEgg; /* 0x3200 */
    u8 ALIGNED(4) isBadEgg; /* 0x3204 */

    u8 ALIGNED(4) mode; /* 0x3208 */
    u8 ALIGNED(4) unk320C; /* 0x320C */
    u8 ALIGNED(4) lastIndex; /* 0x3210 */
    u8 ALIGNED(4) curPageIndex; /* 0x3214 */
    u8 ALIGNED(4) unk3218; /* 0x3218 */
    u8 ALIGNED(4) isBoxMon; /* 0x321C */
    u8 ALIGNED(4) monTypes[2]; /* 0x3220 */

    u8 ALIGNED(4) pageFlipDirection; /* 0x3224 */
    u8 ALIGNED(4) unk3228; /* 0x3228 */
    u8 ALIGNED(4) unk322C; /* 0x322C */
    u8 ALIGNED(4) unk3230; /* 0x3230 */

    u8 ALIGNED(4) lockMovesFlag; /* 0x3234 */

    u8 ALIGNED(4) whichBgLayerToTranslate; /* 0x3238 */
    u8 ALIGNED(4) skillsPageBgNum; /* 0x323C */
    u8 ALIGNED(4) infoAndMovesPageBgNum; /* 0x3240 */
    u8 ALIGNED(4) flippingPages; /* 0x3244 */
    u8 ALIGNED(4) unk3248; /* 0x3248 */
    s16 ALIGNED(4) flipPagesBgHofs; /* 0x324C */

    u16 moveTypes[5]; /* 0x3250 */
    u16 moveIds[5]; /* 0x325A */
    u8 ALIGNED(4) numMoves; /* 0x3264 */
    u8 ALIGNED(4) isSwappingMoves; /* 0x3268 */

    u8 ALIGNED(4) curMonStatusAilment; /* 0x326C */  //important seems to be for displaying status

    u8 ALIGNED(4) state3270; /* 0x3270 */
    u8 ALIGNED(4) summarySetupStep; /* 0x3274 */
    u8 ALIGNED(4) loadBgGfxStep; /* 0x3278 */
    u8 ALIGNED(4) spriteCreationStep; /* 0x327C */
    u8 ALIGNED(4) bufferStringsStep; /* 0x3280 */
    u8 ALIGNED(4) state3284; /* 0x3284 */
    u8 ALIGNED(4) selectMoveInputHandlerState; /* 0x3288 */
    u8 ALIGNED(4) switchMonTaskState; /* 0x328C */

    struct Pokemon currentMon; /* 0x3290 */

    union
    {
        struct Pokemon * mons;
        struct BoxPokemon * boxMons;
    } monList;

    MainCallback savedCallback;
    //struct Sprite * markingSprite;

    u8 ALIGNED(4) lastPageFlipDirection[2]; /* 0x3300 */
    u8 ALIGNED(4) unk3304[3]; /* 0x3304 */
};

struct Struct203B144
{
    u16 unk00;
    u16 curHpStr;
    u16 atkStr;
    u16 defStr;
    u16 spAStr;
    u16 spDStr;
    u16 speStr;
    u16 expStr;
    u16 toNextLevel;

    u16 curPp[5];
    u16 maxPp[5];

    u16 unk26;
};

struct ExpBarObjs
{
    struct Sprite * sprites[11]; /* 0x00 */
    u16 xpos[11]; /* 0x2c */
    u16 tileTag; /* 0x42 */
    u16 palTag; /* 0x44 */
};

struct HpBarObjs
{
    struct Sprite * sprites[10]; /* 0x00 */
    u16 xpos[10]; /* 0x28 */
    u16 tileTag; /* 0x3c */
    u16 palTag; /* 0x3e */
};

struct MonPicBounceState    //want mon pic on known moves page when selecting move to bounce just much slower
{
    u8 ALIGNED(4) animFrame; /* 0x00 */
    u8 ALIGNED(4) initDelay; /* 0x04 */
    u8 ALIGNED(4) vigor; /* 0x08 */
};

struct MoveSelectionCursor
{
    struct Sprite * sprite; /* 0x00 */
    u16 whichSprite; /* 0x04 */
    u16 tileTag; /* 0x06 */
    u16 palTag; /* 0x08 */
};

struct MonStatusIconObj
{
    struct Sprite * sprite; /* 0x00 */
    u16 tileTag; /* 0x04 */
    u16 palTag; /* 0x06 */
};

struct PokerusIconObj
{
    struct Sprite * sprite; /* 0x00 */
    u16 tileTag; /* 0x04 */
    u16 palTag; /* 0x06 */
};

struct ShinyStarObjData
{
    struct Sprite * sprite; /* 0x00 */
    u16 tileTag; /* 0x04 */
    u16 palTag; /* 0x06 */
};

static EWRAM_DATA struct PokemonSummaryScreenData * sMonSummaryScreen = NULL;
static EWRAM_DATA struct Struct203B144 * sMonSkillsPrinterXpos = NULL;
static EWRAM_DATA struct MoveSelectionCursor * sMoveSelectionCursorObjs[4] = {};
static EWRAM_DATA struct MonStatusIconObj * sStatusIcon = NULL; //important believe this is for displaying status icon in summary screens
static EWRAM_DATA struct HpBarObjs * sHpBarObjs = NULL;
static EWRAM_DATA struct ExpBarObjs * sExpBarObjs = NULL;
static EWRAM_DATA struct PokerusIconObj * sPokerusIconObj = NULL;
static EWRAM_DATA struct ShinyStarObjData * sShinyStarObjData = NULL;
static EWRAM_DATA u8 sLastViewedMonIndex = 0;
static EWRAM_DATA u8 sMoveSelectionCursorPos = 0;
static EWRAM_DATA u8 sMoveSwapCursorPos = 0;
static EWRAM_DATA struct MonPicBounceState * sMonPicBounceState = NULL;

extern const u32 gBgTilemap_TrainerMemo_Stats[];
extern const u32 gBgTilemap_PokeSum_MovesListForDelete[];
extern const u32 gBgTilemap_TrainerMemo_Details[];
extern const u32 gBgTilemap_PokeSum_MoveDetailsForDelete[];
extern const u32 gBgTilemap_TrainerMemo_Egg[];
extern const u16 gTrainerMemoPal1[];
extern const u32 gPokeSumBgTiles[];
extern const u16 gPokeSummary_ExpBarPals[];
extern const u32 gPokeSummary_StatusAilmentIconTiles[];
extern const u16 gPokeSummary_StatusAilmentIconPals[];
extern const u32 gPokeSummary_HpBarTiles[];
extern const u32 gPokeSummary_ExpBarTiles[];
extern const u16 gPokeSummary_ExpBarPals[];

static const u32 sBgPal7[] = INCBIN_U32("graphics/interface/pokesummary_unk_84636C0.gbapal");
static const u16 sMonMarkingSpritePalette[] = INCBIN_U16("graphics/interface/pokesummary_unk_84636E0.gbapal");
static const u32 sBgPal8[] = INCBIN_U32("graphics/interface/pokesummary_unk_8463700.gbapal");
static const u16 sMoveSelectionCursorPals[] = INCBIN_U16("graphics/interface/pokesummary_unk_8463720.gbapal");
static const u32 sMoveSelectionCursorTiles_Left[] = INCBIN_U32("graphics/interface/pokesummary_unk_8463740.4bpp.lz");
static const u32 sMoveSelectionCursorTiles_Right[] = INCBIN_U32("graphics/interface/pokesummary_unk_846386C.4bpp.lz");

static const struct OamData sMoveSelectionCursorOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sMoveSelectionCursorOamAnim_Red[] = 
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sMoveSelectionCursorOamAnim_Blue[] = 
{
    ANIMCMD_FRAME(0x20, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd * const sMoveSelectionCursorOamAnimTable[] =
{
    sMoveSelectionCursorOamAnim_Red,
    sMoveSelectionCursorOamAnim_Blue
};

static const struct OamData sStatusAilmentIconOamData = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sStatusAilmentIconAnim_PSN[] = 
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_PRZ[] = 
{
    ANIMCMD_FRAME(4, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_SLP[] = 
{
    ANIMCMD_FRAME(8, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_FRZ[] = 
{
    ANIMCMD_FRAME(12, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_BRN[] = 
{
    ANIMCMD_FRAME(16, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_PKRS[] = 
{
    ANIMCMD_FRAME(20, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_FNT[] = 
{
    ANIMCMD_FRAME(24, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sStatusAilmentIconAnim_Blank[] = 
{
    ANIMCMD_FRAME(28, 20),
    ANIMCMD_JUMP(0),
};//not unused this is used when not statused

//believe to make icons bounce with menu bounce
static const union AnimCmd * const sStatusAilmentIconAnimTable[] =
{
    sStatusAilmentIconAnim_PSN,
    sStatusAilmentIconAnim_PRZ,
    sStatusAilmentIconAnim_SLP,
    sStatusAilmentIconAnim_FRZ,
    sStatusAilmentIconAnim_BRN,
    sStatusAilmentIconAnim_PKRS,
    sStatusAilmentIconAnim_FNT,
    sStatusAilmentIconAnim_Blank
};//vsonic

static const struct OamData sHpOrExpBarOamData = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sHpOrExpAnim_0[] = 
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_1[] = 
{
    ANIMCMD_FRAME(1, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_2[] = 
{
    ANIMCMD_FRAME(2, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_3[] = 
{
    ANIMCMD_FRAME(3, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_4[] = 
{
    ANIMCMD_FRAME(4, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_5[] = 
{
    ANIMCMD_FRAME(5, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_6[] = 
{
    ANIMCMD_FRAME(6, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_7[] = 
{
    ANIMCMD_FRAME(7, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_8[] = 
{
    ANIMCMD_FRAME(8, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_9[] = 
{
    ANIMCMD_FRAME(9, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_10[] = 
{
    ANIMCMD_FRAME(10, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sHpOrExpAnim_11[] = 
{
    ANIMCMD_FRAME(11, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd * const sHpOrExpBarAnimTable[] =
{
    sHpOrExpAnim_0,
    sHpOrExpAnim_1,
    sHpOrExpAnim_2,
    sHpOrExpAnim_3,
    sHpOrExpAnim_4,
    sHpOrExpAnim_5,
    sHpOrExpAnim_6,
    sHpOrExpAnim_7,
    sHpOrExpAnim_8,
    sHpOrExpAnim_9,
    sHpOrExpAnim_10,
    sHpOrExpAnim_11
};

static const u16 sPokeSummary_HpBarPalYellow[] = INCBIN_U16("graphics/interface/pokesummary_unk_8463AAC.gbapal");
static const u16 sPokeSummary_HpBarPalRed[] = INCBIN_U16("graphics/interface/pokesummary_unk_8463ACC.gbapal");

static const struct OamData sPokerusIconObjOamData = {
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sPokerusIconObjAnim0[] = 
{
    ANIMCMD_FRAME(0, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd * const sPokerusIconObjAnimTable[] =
{
    sPokerusIconObjAnim0
};

static const u16 sPokerusIconObjPal[] = INCBIN_U16("graphics/interface/pokesummary_unk_8463B00.gbapal");
static const u32 sPokerusIconObjTiles[] = INCBIN_U32("graphics/interface/pokesummary_unk_8463B20.4bpp.lz");

static const struct OamData sStarObjOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0
};

static const union AnimCmd sStarObjAnim0[] = 
{
    ANIMCMD_FRAME(1, 20),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd * const sStarObjAnimTable[] =
{
    sStarObjAnim0
};

static const u16 sStarObjPal[] = INCBIN_U16( "graphics/interface/pokesummary_unk_8463B44.gbapal");
static const u32 sStarObjTiles[] = INCBIN_U32( "graphics/interface/pokesummary_unk_8463B64.4bpp.lz");
static const u32 sBgTilemap_MovesInfoPage[] = INCBIN_U32( "graphics/interface/pokesummary_unk_8463B88.bin.lz");
//static const u32 sBgTilemap_MovesPage[] = INCBIN_U32( "graphics/interface/pokesummary_unk_8463C80.bin.lz"); //page name maybe wrong
                        //pretty sure this file is the move info page i.e move selection.  /was able to confirm this is file that affects moveinfo page
static const u32 sBgTilemap_MovesPage[] = INCBIN_U32("graphics/interface/pokesummary_unk_8463C80_replace.bin.lz");//test to see what color gets blinded

// const rom data
#include "data/text/nature_names.h"

static const u8 * const sEggHatchTimeTexts[] = {
    gText_PokeSum_EggHatch_LongTime,
    gText_PokeSum_EggHatch_SomeTime,
    gText_PokeSum_EggHatch_Soon,
    gText_PokeSum_EggHatch_AlmostReady
};

static const u8 * const sEggOriginTexts[] = {
    gText_PokeSum_EggOrigin_DayCare,
    gText_PokeSum_EggOrigin_Trade,
    gText_PokeSum_EggOrigin_TravelingMan,
    gText_PokeSum_EggOrigin_Trade,
    gText_PokeSum_EggOrigin_NicePlace,
    gText_PokeSum_EggOrigin_Spa,
    gText_PokeSum_EggOrigin_Trade
};

static const u8 sPrintMoveTextColors[][3] = {
    {0, 7, 8},
    {0, 1, 2},
    {0, 3, 4},
    {0, 5, 6}
};

static const struct BgTemplate sBgTempaltes[] = 
{
	 {
	 	.bg = 0,
	 	.charBaseIndex = 0,
	 	.mapBaseIndex = 14,
	 	.screenSize = 1,
	 	.paletteMode = 0,
	 	.priority = 0,
	 	.baseTile = 0x0000
	 },
	 {
	 	.bg = 2,
	 	.charBaseIndex = 2,
	 	.mapBaseIndex = 10,
	 	.screenSize = 1,
	 	.paletteMode = 0,
	 	.priority = 1,
	 	.baseTile = 0x0000
	 },
	 {
	 	.bg = 3,
	 	.charBaseIndex = 2,
	 	.mapBaseIndex = 9,
	 	.screenSize = 0,
	 	.paletteMode = 0,
	 	.priority = 3,
	 	.baseTile = 0x0000
	 },
	 {
	 	.bg = 1,
	 	.charBaseIndex = 2,
	 	.mapBaseIndex = 12,
	 	.screenSize = 1,
	 	.paletteMode = 0,
	 	.priority = 2,
	 	.baseTile = 0x0000
	 }
};

#define POKESUM_WIN_PAGE_NAME        0
#define POKESUM_WIN_CONTROLS         1
#define POKESUM_WIN_LVL_NICK         2
#define POKESUM_WIN_RIGHT_PANE       3
#define POKESUM_WIN_TRAINER_MEMO     4

//PokeSum_CreateWindows function  loops 4 times 0-3
//to create 4 windows/templates for each page of the 3 summary screens
//loop is 0-3 but then functions adds 3 to the loop value
//which is why these constants are 3-6
//this is important because I could potentially use those functionns
//to create new window templates to more easily split up the existing ui.

//PokeSum_AddWindows is used via PokeSum_CreateWindows so look into that as well

#define POKESUM_WIN_INFO_3           3
#define POKESUM_WIN_INFO_4           4
#define POKESUM_WIN_INFO_5           5
#define POKESUM_WIN_INFO_6           6

#define POKESUM_WIN_SKILLS_3         3
#define POKESUM_WIN_SKILLS_4         4
#define POKESUM_WIN_SKILLS_5         5
#define POKESUM_WIN_SKILLS_6         6

#define POKESUM_WIN_MOVES_3          3  //mon move names & pp window
#define POKESUM_WIN_MOVES_4          4  //move selct descriptions & info
#define POKESUM_WIN_MOVES_5          5  //Type Icons
#define POKESUM_WIN_MOVES_6          6  //Mon Type Icons
#define POKESUM_WIN_MOVES_5_1        7  //Type Icon Move 2
#define POKESUM_WIN_MOVES_5_2        8  //Type Icon Move 3
#define POKESUM_WIN_MOVES_5_3        9  //Type Icon Move 4
#define POKESUM_WIN_MOVES_5_4        10  //Type Icon Move 5 potentially for new move learning?

static const struct WindowTemplate sWindowTemplates_Permanent_Bg1[] =
{
    [POKESUM_WIN_PAGE_NAME] = {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 13,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0258
    },
    [POKESUM_WIN_CONTROLS] = {
        .bg = 1,
        .tilemapLeft = 19,
        .tilemapTop = 0,
        .width = 11,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0272
    },
    [POKESUM_WIN_LVL_NICK] = {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = 15,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0288
    }
};

//if above is other windows wonder if here can be right pane
static const struct WindowTemplate sWindowTemplates_Permanent_Bg2[] = 
{
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 13,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0258
    },
    {
        .bg = 2,
        .tilemapLeft = 19,
        .tilemapTop = 0,
        .width = 11,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0272
    },
    {
        .bg = 2,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = 15,
        .height = 2,
        .paletteNum = 7,
        .baseBlock = 0x0288
    },
};

static const struct WindowTemplate sWindowTemplates_Info[] = 
{
    [POKESUM_WIN_INFO_3 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 2,
        .width = 15,
        .height = 12,
        .paletteNum = 6,
        .baseBlock = 0x0001
    },
    [POKESUM_WIN_INFO_4 - 3] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 14,
        .width = 28,
        .height = 6,
        .paletteNum = 6,
        .baseBlock = 0x00b5
    },
    [POKESUM_WIN_INFO_5 - 3] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },
    [POKESUM_WIN_INFO_6 - 3] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },
};

static const struct WindowTemplate sWindowTemplates_Skills[] = 
{
    [POKESUM_WIN_SKILLS_3 - 3] = {
        .bg = 0,
        .tilemapLeft = 20,
        .tilemapTop = 2,
        .width = 10,
        .height = 13,
        .paletteNum = 6,
        .baseBlock = 0x0001
    },//think this is stats down to nxt level data. attempt decrease height for removal of total exp field
    [POKESUM_WIN_SKILLS_4 - 3] = {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 12,
        .width = 14,
        .height = 4,
        .paletteNum = 6,
        .baseBlock = 0x008d
    },//assuming is mon pic
    [POKESUM_WIN_SKILLS_5 - 3] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 29,
        .height = 6,
        .paletteNum = 6,
        .baseBlock = 0x00c5
    },//believe is ability data. //attempt increasing height and moving tilemapTop higher up, from removal of total exp field, and expansion of ability desc
    [POKESUM_WIN_SKILLS_6 - 3] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },//not used equivalent of a dummy or buffer of some sort, since nothing here shouldn't need to shift baseblock for expansion of window 5
};//shifted bg, windows & text data, still need to adjust exp bar y position

//experiement see how this affects windows maybe is what i need
static const struct WindowTemplate sWindowTemplates_Moves[] = 
{
    //appears to be window for all move data? move names, pp, even the cancel button was shifted for selection
    //since all these things moves together the fix is either separting them into individual windows
    //or to move this left enough for what I want and then compensate by making the width much wider (since it just extends it right)
    //and then adjusting the x position for the pp and cancel button until it looks like it wasn't moved...
    [POKESUM_WIN_MOVES_3 - 3] = {
        .bg = 0,
        .tilemapLeft = 16,
        .tilemapTop = 2,
        .width = 13,
        .height = 19,
        .paletteNum = 8,
        .baseBlock = 0x0001 //needs to be 19 to fit values
    },//is the baseblock telling it what tile to use or is that the actual window so if I swap the base block can I get it to move the text values 
    //associated with the window to the position of the other stuff?   like make it make the window in a different place?

    //appears to be left window move data, only noticeable when selecting a move,
    //shifts here affect move power, accuracy, and effect/description windows/values
    [POKESUM_WIN_MOVES_4 - 3] = {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 7,
        .width = 15,
        .height = 13,
        .paletteNum = 6,
        .baseBlock = 0x00f5
    },
    //shifts the type icons for the moves on the right panel
    //apparently mon pic is on a different layer than the text
    //moved the type icon and it appeared above the mon name
    //but behind the mon pic hmm
    [POKESUM_WIN_MOVES_5 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 2,
        .width = 5,
        .height = 18,
        .paletteNum = 6,
        .baseBlock = 0x01b8
    },
    //moves the mon type icons that appear when moves are selected
    [POKESUM_WIN_MOVES_6 - 3] = {
        .bg = 0,
        .tilemapLeft = 11,
        .tilemapTop = 2,
        .width = 3,
        .height = 5,
        .paletteNum = 6,
        .baseBlock = 0x0212
    },//based on what jaizu said I'm guessing baseblock is actually memory/vram allocation/address? so need to increase all these below expanded window
    //I tweaked it and it appears to be working?
    /*[POKESUM_WIN_MOVES_5_1 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 6,
        .width = 5,
        .height = 2,
        .paletteNum = 6,
        .baseBlock = 0x0242
    },
    [POKESUM_WIN_MOVES_5_2 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 9,
        .width = 5,
        .height = 3,
        .paletteNum = 6,
        .baseBlock = 0x0252
    },//changed tilemaptop to same as 5, proves the window isn't getting written/added at all
    //compared in tilemap studio and values for tilemap seem to match, and surprsingly my y position matches perfectly
    //the 3rd move window, isn't really even, its a bit high, so I set the height higher so I can have more room to lower it later
    //just need to find how to get these to display
    [POKESUM_WIN_MOVES_5_3 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 13,
        .width = 5,
        .height = 2,
        .paletteNum = 6,
        .baseBlock = 0x0262
    },
    [POKESUM_WIN_MOVES_5_4 - 3] = {
        .bg = 0,
        .tilemapLeft = 15,
        .tilemapTop = 18,
        .width = 5,
        .height = 2,
        .paletteNum = 6,
        .baseBlock = 0x0272
    },*/
};

static const struct WindowTemplate sWindowTemplates_Dummy[] = 
{
    {
        .bg = 255,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 0,
        .height = 0,
        .paletteNum = 0,
        .baseBlock = 0x0000
    },
};


enum Text_Colors
{
    BLACK_COLOR,
    RED_COLOR,
    BLUE_PURPLE_COLOR,
    LIGHT_GREEN_COLOR,
    ORANGE_COLOR,
    LIGHT_BROWN_COLOR,
    PURPLE_COLOR,
    LIGHT_GREY_COLOR
};


//3 values were in ARRAY represent
/*  printer.bgColor = color[0];
    printer.fgColor = color[1];
    printer.shadowColor = color[2];*/
    //first value should always be 0
    //colors are different on different windows I think,
    //so for reference these colors are on bg of skill page
    //make new colors instead of editing existing for /nature
static const u8 sLevelNickTextColors[][3] =
{                      //bgColor   //fgColor         //shadowColor
   [BLACK_COLOR] =          {0,     BLACK,               GREY_LAVENDER  },
   [RED_COLOR] =            {0,      RED,                 ORANGE        },
   [BLUE_PURPLE_COLOR] =    {0,    NAVY_BLUE,             PURPLE        },
   [LIGHT_GREEN_COLOR] =    {0,   LIGHT_GREEN,            TAN           },
   [ORANGE_COLOR] =         {0,     ORANGE,               PEACH         },
   [LIGHT_BROWN_COLOR] =    {0,    LIGHT_BROWN,          GREY_LAVENDER  },
   [PURPLE_COLOR] =         {0,      PURPLE,              PURPLE        },
   [LIGHT_GREY_COLOR] =     {0,   GREY_LAVENDER,         WHITE          }, //colors cap at 14 it seems, changed grey shadow to white to make more readable was grey
};

static const u8 ALIGNED(4) sMultiBattlePartyOrder[] =
{
    0, 2, 3, 1, 4, 5
};

static const s8 sMonPicBounceYDelta_Under60[] =
{
    -1, 0, 1
};

static const s8 sMonPicBounceYDelta_60to80[] =
{
    -2, -1, 0, 1, 2
};

static const s8 sMonPicBounceYDelta_80to99[] =
{
    -3, -2, -1, 0, 1, 2, 3
};

static const s8 sMonPicBounceYDelta_Full[] =
{
    -5, -3, -1, 0, 1, 3, 5
};

static const s8 sEggPicShakeXDelta_ItWillTakeSomeTime[] =
{
    1, 1, 0, -1, -1, 0, -1, -1, 0, 1, 1
};

static const s8 sEggPicShakeXDelta_OccasionallyMoves[] =
{
    2, 1, 0, -1, -2, 0, -2, -1, 0, 1, 2
};

static const s8 sEggPicShakeXDelta_AlmostReadyToHatch[] =
{
    2, 1, 1, 0, -1, -1, -2, 0, -2, -1, -1, 0, 1, 1, 2
};

static const u16 * const sHpBarPals[] =
{
    gPokeSummary_ExpBarPals,
    sPokeSummary_HpBarPalYellow,
    sPokeSummary_HpBarPalRed,
};


#define FREE_AND_SET_NULL_IF_SET(ptr) \
{                                     \
    if (ptr != NULL)                  \
    {                                 \
        free(ptr);                    \
        (ptr) = NULL;                 \
    }                                 \
}

#define FLIP_RIGHT 1
#define FLIP_LEFT 0

void ShowPokemonSummaryScreen(struct Pokemon * party, u8 cursorPos, u8 lastIdx, MainCallback savedCallback, u8 mode)
{
    sMonSummaryScreen = AllocZeroed(sizeof(struct PokemonSummaryScreenData));
    sMonSkillsPrinterXpos = AllocZeroed(sizeof(struct Struct203B144));

    if (sMonSummaryScreen == NULL)
    {
        SetMainCallback2(savedCallback);
        return;
    }

    sLastViewedMonIndex = cursorPos;

    sMoveSelectionCursorPos = 0;
    sMoveSwapCursorPos = 0;
    sMonSummaryScreen->savedCallback = savedCallback;
    sMonSummaryScreen->monList.mons = party;

    if (party == gEnemyParty)
        sMonSummaryScreen->isEnemyParty = TRUE;
    else
        sMonSummaryScreen->isEnemyParty = FALSE;

    sMonSummaryScreen->lastIndex = lastIdx;
    sMonSummaryScreen->mode = mode;

    switch (sMonSummaryScreen->mode)
    {
    case PSS_MODE_NORMAL:
    default:
       // SetHelpContext(HELPCONTEXT_POKEMON_INFO);
        sMonSummaryScreen->curPageIndex = PSS_PAGE_INFO;
        sMonSummaryScreen->isBoxMon = FALSE;
        sMonSummaryScreen->lockMovesFlag = FALSE;
        break;
    case PSS_MODE_BOX:
       // SetHelpContext(HELPCONTEXT_POKEMON_INFO);
        sMonSummaryScreen->curPageIndex = PSS_PAGE_INFO;
        sMonSummaryScreen->isBoxMon = TRUE;
        sMonSummaryScreen->lockMovesFlag = FALSE;
        break;
    case PSS_MODE_SELECT_MOVE:
    case PSS_MODE_FORGET_MOVE:
       // SetHelpContext(HELPCONTEXT_POKEMON_MOVES);
        sMonSummaryScreen->curPageIndex = PSS_PAGE_MOVES_INFO;
        sMonSummaryScreen->isBoxMon = FALSE;
        sMonSummaryScreen->lockMovesFlag = TRUE;
        break;
    }

    sMonSummaryScreen->state3270 = 0;
    sMonSummaryScreen->summarySetupStep = 0;
    sMonSummaryScreen->loadBgGfxStep = 0;
    sMonSummaryScreen->spriteCreationStep = 0;

    sMonSummaryScreen->whichBgLayerToTranslate = 0;
    sMonSummaryScreen->skillsPageBgNum = 2;
    sMonSummaryScreen->infoAndMovesPageBgNum = 1;
    sMonSummaryScreen->flippingPages = FALSE;

    sMonSummaryScreen->unk3228 = 0;
    sMonSummaryScreen->unk322C = 1;

    BufferSelectedMonData(&sMonSummaryScreen->currentMon); //should set currentmon to value of lastviewedindex
    sMonSummaryScreen->isEgg = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_IS_EGG);
    sMonSummaryScreen->isBadEgg = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SANITY_IS_BAD_EGG);

    if (sMonSummaryScreen->isBadEgg == TRUE)
        sMonSummaryScreen->isEgg = TRUE;

    sMonSummaryScreen->lastPageFlipDirection[0] = 0xff;
    SetMainCallback2(CB2_SetUpPSS);
}

//can prob use this for in battle show move info, to see split power etc.
#define SHOW_SUMMARY_SCREEN
void ShowSelectMovePokemonSummaryScreen(struct Pokemon *party, u8 cursorPos, u8 lastIdx, MainCallback savedCallback, u16 newMove)
{
    ShowPokemonSummaryScreen(party, cursorPos, lastIdx, savedCallback, PSS_MODE_SELECT_MOVE);
    sMonSummaryScreen->moveIds[4] = newMove;
} //cursor position is which mon to show

static u8 sub_813476C(u8 a0)
{
    if (sMonSummaryScreen->inhibitPageFlipInput == TRUE && sMonSummaryScreen->pageFlipDirection != a0)
        return TRUE;

    return FALSE;
}

u32 sub_81347A4(u8 a0)
{
    if (sMonSummaryScreen->isEgg)
        return FALSE;

    if (sMonSummaryScreen->lastPageFlipDirection[0] != 0xff && sMonSummaryScreen->lastPageFlipDirection[0] == a0)
    {
        sMonSummaryScreen->lastPageFlipDirection[0] = 0xff;
        return TRUE;
    }

    if (sub_813476C(a0))
        return FALSE;

    switch (a0)
    {
    case 1:
        if (JOY_NEW(DPAD_RIGHT))
            return TRUE;

        if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR && JOY_NEW(R_BUTTON))
            return TRUE;

        break;
    case 0:
        if (JOY_NEW(DPAD_LEFT))
            return TRUE;

        if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_LR && JOY_NEW(L_BUTTON))
            return TRUE;

        break;
    }

    return FALSE;
}

static void Task_InputHandler_Info(u8 taskId)
{
    switch (sMonSummaryScreen->state3270) {
    case PSS_STATE3270_0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0);
        sMonSummaryScreen->state3270 = PSS_STATE3270_1;
        break;
    case PSS_STATE3270_1:
        if (!gPaletteFade.active)
        {
            PokeSum_TryPlayMonCry();
            sMonSummaryScreen->state3270 = PSS_STATE3270_2;
            return;
        }

        sMonSummaryScreen->state3270 = PSS_STATE3270_1;
        break;
    case PSS_STATE3270_2:
        if (MenuHelpers_CallLinkSomething() == TRUE) //this too
            return;
        else if (sub_800B270() == TRUE) //functions in link.c
            return;
        else if (FuncIsActiveTask(Task_PokeSum_SwitchDisplayedPokemon))
            return;

        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
        {
            if (sub_81347A4(1) == TRUE)
            {
                if (FuncIsActiveTask(Task_PokeSum_FlipPages))
                {
                    sMonSummaryScreen->lastPageFlipDirection[0] = 1;
                    return;
                }
                else if (sMonSummaryScreen->curPageIndex < PSS_PAGE_MOVES)
                {
                    PlaySE(SE_SELECT);
                    HideBg(0);
                    sMonSummaryScreen->pageFlipDirection = 1;
                    PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
                    sMonSummaryScreen->curPageIndex++;
                    sMonSummaryScreen->state3270 = PSS_STATE3270_3;
                }
                return;
            }
            else if (sub_81347A4(0) == TRUE)
            {
                if (FuncIsActiveTask(Task_PokeSum_FlipPages))
                {
                    sMonSummaryScreen->lastPageFlipDirection[0] = 0;
                    return;
                }
                else if (sMonSummaryScreen->curPageIndex > PSS_PAGE_INFO)
                {
                    PlaySE(SE_SELECT);
                    HideBg(0);
                    sMonSummaryScreen->pageFlipDirection = 0;
                    PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
                    sMonSummaryScreen->curPageIndex--;
                    sMonSummaryScreen->state3270 = PSS_STATE3270_3;
                }
                return;
            }
        }

        if ((!FuncIsActiveTask(Task_PokeSum_FlipPages)) || FuncIsActiveTask(Task_PokeSum_SwitchDisplayedPokemon))
        { // put summary screen actions else if
            if (JOY_NEW(DPAD_UP))
            {
                PokeSum_SeekToNextMon(taskId, -1);
                return;
            }
            else if (JOY_NEW(DPAD_DOWN))
            {
                PokeSum_SeekToNextMon(taskId, 1);
                return;
            }
            else if (JOY_NEW(A_BUTTON))
            {
                if (sMonSummaryScreen->curPageIndex == PSS_PAGE_INFO)
                {
                    PlaySE(SE_SELECT);
                    sMonSummaryScreen->state3270 = PSS_STATE3270_4; // close menu
                }
                else if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES)
                {
                    PlaySE(SE_SELECT);
                    sMonSummaryScreen->pageFlipDirection = 1;
                    PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
                    sMonSummaryScreen->curPageIndex++;
                    sMonSummaryScreen->state3270 = PSS_STATE3270_3;
                }
                return;
            }
            else if (JOY_NEW(B_BUTTON))
            {
                sMonSummaryScreen->state3270 = PSS_STATE3270_4; // close menu
            }
        }
        break;
    case PSS_STATE3270_3:
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
        {
            CreateTask(Task_PokeSum_FlipPages, 0);
            sMonSummaryScreen->state3270 = PSS_STATE3270_2;
        }
        else
        {
            gTasks[sMonSummaryScreen->inputHandlerTaskId].func = Task_FlipPages_FromInfo;
            sMonSummaryScreen->state3270 = PSS_STATE3270_2;
        }
        break;
    case PSS_STATE3270_4:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, 0);
        sMonSummaryScreen->state3270 = PSS_STATE3270_5;
        break;
    case PSS_STATE3270_5:
        if (Overworld_LinkRecvQueueLengthMoreThan2() == TRUE)
            return;
        else if (sub_800B270() == TRUE) //function in link.c
            return;

        sMonSummaryScreen->state3270 = PSS_STATE3270_6;
        break;
    default:
        if (!gPaletteFade.active)
            Task_DestroyResourcesOnExit(taskId);

        break;
    }
}

static void Task_PokeSum_FlipPages(u8 taskId)
{
    s16 * data = gTasks[taskId].data;

    switch (data[0])
    {
    case 0:
        PokeSum_HideSpritesBeforePageFlip();
        PokeSum_ShowSpritesBeforePageFlip();
        sMonSummaryScreen->lockMovesFlag = TRUE;
        sMonSummaryScreen->inhibitPageFlipInput = TRUE;
        PokeSum_UpdateWin1ActiveFlag(sMonSummaryScreen->curPageIndex);
        PokeSum_AddWindows(sMonSummaryScreen->curPageIndex);
        break;
    case 1:
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
        {
            if (!(sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES && sMonSummaryScreen->pageFlipDirection == 0))
            {
                FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
                CopyBgTilemapBufferToVram(0);
            }
        }
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 2, 15, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 2, 15, 2);
        break;
    case 2:
        PokeSum_CopyNewBgTilemapBeforePageFlip_2();
        PokeSum_CopyNewBgTilemapBeforePageFlip();
        PokeSum_DrawBg3Tilemap();
        PokeSum_PrintPageHeaderText(sMonSummaryScreen->curPageIndex);
        break;
    case 3:
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2);
        break;
    case 4:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
        }
        else
            return;

        break;
    case 5:
        PokeSum_InitBgCoordsBeforePageFlips();
        sMonSummaryScreen->flippingPages = TRUE;
        break;
    case 6:
        if (!PokeSum_IsPageFlipFinished(sMonSummaryScreen->pageFlipDirection))
            return;

        break;
    case 7:
        PokeSum_PrintRightPaneText();
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
            PokeSum_PrintBottomPaneText();

        PokeSum_PrintAbilityDataOrMoveTypes();
        PokeSum_PrintMonTypeIcons();
        break;
    case 8:
        CopyWindowToVram(sMonSummaryScreen->windowIds[3], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[4], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        break;
    case 9:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CopyBgTilemapBufferToVram(0);
            ShowBg(0);
        }
        else
            return;

        break;
    default:
        PokeSum_SetHelpContext();

        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
            gTasks[sMonSummaryScreen->inputHandlerTaskId].func = Task_HandleInput_SelectMove;

        DestroyTask(taskId);
        data[0] = 0;
        sMonSummaryScreen->lockMovesFlag = FALSE;
        sMonSummaryScreen->inhibitPageFlipInput = FALSE;
        return;
    }

    data[0]++;
}

static void Task_FlipPages_FromInfo(u8 taskId)
{
    switch (sMonSummaryScreen->state3284)
    {
    case 0:
        sMonSummaryScreen->lockMovesFlag = TRUE;
        sMonSummaryScreen->inhibitPageFlipInput = TRUE;
        PokeSum_AddWindows(sMonSummaryScreen->curPageIndex);
        break;
    case 1:
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
        {
            if (!(sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES && sMonSummaryScreen->pageFlipDirection == 0))
            {
                FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
                CopyBgTilemapBufferToVram(0);
            }
        }

        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 2, 15, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 2, 15, 2);
        break;
    case 2:
        PokeSum_HideSpritesBeforePageFlip();
        PokeSum_UpdateWin1ActiveFlag(sMonSummaryScreen->curPageIndex);
        PokeSum_CopyNewBgTilemapBeforePageFlip();
        PokeSum_DrawBg3Tilemap();
        PokeSum_CopyNewBgTilemapBeforePageFlip_2();
        break;
    case 3:
        PokeSum_PrintPageName(gText_PokeSum_PageName_KnownMoves);
        if (!(gMain.inBattle || gReceivedRemoteLinkPlayers))
            PokeSum_PrintControlsString(gText_PokeSum_Controls_PickSwitch);
        else
            PokeSum_PrintControlsString(gText_PokeSum_Controls_Pick);

        break;
    case 4:
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 2);
        break;
    case 5:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(3);
        }
        else
            return;

        break;
    case 6:
        PokeSum_PrintRightPaneText();
        PokeSum_PrintAbilityDataOrMoveTypes();
        CopyWindowToVram(sMonSummaryScreen->windowIds[3], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        break;
    case 7:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CopyBgTilemapBufferToVram(0);
            PokeSum_InitBgCoordsBeforePageFlips();
            sMonSummaryScreen->flippingPages = TRUE;
        }
        else
            return;

        break;
    case 8:
        if (!PokeSum_IsPageFlipFinished(sMonSummaryScreen->pageFlipDirection))
            return;

        PokeSum_PrintBottomPaneText();
        CopyWindowToVram(sMonSummaryScreen->windowIds[4], 2);
        break;
    case 9:
        PokeSum_PrintMonTypeIcons();
        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case 10:
        PokeSum_ShowSpritesBeforePageFlip();
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2);
        break;
    case 11:
        if (!IsDma3ManagerBusyWithBgCopy())
        {
            CopyBgTilemapBufferToVram(0);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
        }
        else
            return;

        break;
    default:
        PokeSum_SetHelpContext();
        gTasks[sMonSummaryScreen->inputHandlerTaskId].func = Task_HandleInput_SelectMove;
        sMonSummaryScreen->state3284 = 0;
        sMonSummaryScreen->lockMovesFlag = FALSE;
        sMonSummaryScreen->inhibitPageFlipInput = FALSE;
        return;
    }

    sMonSummaryScreen->state3284++;
    return;
}

static void Task_BackOutOfSelectMove(u8 taskId)
{
    switch (sMonSummaryScreen->state3284)
    {
    case 0:
        sMonSummaryScreen->lockMovesFlag = TRUE;
        sMonSummaryScreen->inhibitPageFlipInput = TRUE;
        PokeSum_AddWindows(sMonSummaryScreen->curPageIndex);
        break;
    case 1:
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO) {
            if (!(sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES && sMonSummaryScreen->pageFlipDirection == 0))
            {
                FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
                CopyBgTilemapBufferToVram(0);
            }
        }

        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 2, 15, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 2);
        FillBgTilemapBufferRect_Palette0(2, 0, 0, 2, 15, 2);
        break;
    case 2:
        PokeSum_CopyNewBgTilemapBeforePageFlip_2();
        break;
    case 3:
        PokeSum_PrintRightPaneText();
        PokeSum_PrintBottomPaneText();
        PokeSum_PrintAbilityDataOrMoveTypes();
        CopyWindowToVram(sMonSummaryScreen->windowIds[3], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[4], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        CopyBgTilemapBufferToVram(0);
        break;
    case 4:
        PokeSum_PrintPageName(gText_PokeSum_PageName_KnownMoves);
        PokeSum_PrintControlsString(gText_PokeSum_Controls_PageDetail);
        break;
    case 5:
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 2);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        break;
    case 6:
        PokeSum_InitBgCoordsBeforePageFlips();
        sMonSummaryScreen->flippingPages = TRUE;
        PokeSum_HideSpritesBeforePageFlip();
        PokeSum_UpdateWin1ActiveFlag(sMonSummaryScreen->curPageIndex);
        PokeSum_PrintMonTypeIcons();
        break;
    case 7:
        break;
    case 8:
        if (PokeSum_IsPageFlipFinished(sMonSummaryScreen->pageFlipDirection) == 0)
            return;

        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case 9:
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        break;
    case 10:
        PokeSum_CopyNewBgTilemapBeforePageFlip();
        PokeSum_DrawBg3Tilemap();
        CopyBgTilemapBufferToVram(3);
        PokeSum_ShowSpritesBeforePageFlip();
        break;
    default:
        PokeSum_SetHelpContext();
        gTasks[sMonSummaryScreen->inputHandlerTaskId].func = Task_InputHandler_Info;
        sMonSummaryScreen->state3284 = 0;
        sMonSummaryScreen->lockMovesFlag = FALSE;
        sMonSummaryScreen->inhibitPageFlipInput = FALSE;
        return;
    }

    sMonSummaryScreen->state3284++;
    return;
}

static void sub_813546C(void)
{
    u8 i;
    for (i = 0; i < 11; i++)
    {
        sExpBarObjs->xpos[i] = (8 * i) + 396;
        sExpBarObjs->sprites[i]->pos1.x = sExpBarObjs->xpos[i];
        if (i >= 9)
            continue;

        sHpBarObjs->xpos[i] = (8 * i) + 412;
        sHpBarObjs->sprites[i]->pos1.x = sHpBarObjs->xpos[i];
    }
}

static void sub_81354C4(void)
{
    u8 i;
    for (i = 0; i < 11; i++)
    {
        sExpBarObjs->xpos[i] = (8 * i) + 156;
        sExpBarObjs->sprites[i]->pos1.x = sExpBarObjs->xpos[i];
        if (i >= 9)
            continue;
        sHpBarObjs->xpos[i] = (8 * i) + 172;
        sHpBarObjs->sprites[i]->pos1.x = sHpBarObjs->xpos[i];
    }
}

static void PokeSum_InitBgCoordsBeforePageFlips(void)
{
    s8 pageDelta = 1;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        pageDelta = -1;

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
    {
        sMonSummaryScreen->flipPagesBgHofs = 240;
        return;
    }

    if ((sMonSummaryScreen->curPageIndex + pageDelta) == PSS_PAGE_MOVES_INFO)
    {
        PokeSum_UpdateBgPriorityForPageFlip(0, 0);
        sMonSummaryScreen->flipPagesBgHofs = 0;
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        return;
    }

    if (sMonSummaryScreen->pageFlipDirection == 1)
    {
        sMonSummaryScreen->flipPagesBgHofs = 0;
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        PokeSum_UpdateBgPriorityForPageFlip(1, 1);
    }
    else
    {
        u32 bg1Priority = GetGpuReg(REG_OFFSET_BG1CNT) & 3;
        u32 bg2Priority = GetGpuReg(REG_OFFSET_BG2CNT) & 3;
        sMonSummaryScreen->flipPagesBgHofs = 240;

        if (bg1Priority > bg2Priority)
            SetGpuReg(REG_OFFSET_BG1HOFS, 240);
        else
            SetGpuReg(REG_OFFSET_BG2HOFS, 240);

        SetGpuReg(REG_OFFSET_BG0HOFS, 240);
        PokeSum_UpdateBgPriorityForPageFlip(1, 0);
    }

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_SKILLS)
    {
        if (sMonSummaryScreen->pageFlipDirection == 1)
            sub_81354C4();
        else
            sub_813546C();
    }
    else if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES)
        sub_81354C4();

}

static void PokeSum_HideSpritesBeforePageFlip(void)
{
    u8 newPage;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        newPage = sMonSummaryScreen->curPageIndex - 1;
    else
        newPage = sMonSummaryScreen->curPageIndex + 1;

    switch (newPage)
    {
    case PSS_PAGE_INFO:
        break;
    case PSS_PAGE_SKILLS:
        ShowOrHideHpBarObjs(1);
        ShowOrHideExpBarObjs(1);
        break;
    case PSS_PAGE_MOVES:
        if (sMonSummaryScreen->pageFlipDirection == 1)
        {
            PokeSum_ShowOrHideMonPicSprite(1);
            //PokeSum_ShowOrHideMonMarkingsSprite(1);
            ShowOrHideBallIconObj(1);
            ShowOrHideStatusIcon(1);
            HideShowPokerusIcon(1);
            HideShowShinyStar(1);
        }

        break;
    case PSS_PAGE_MOVES_INFO:
        ShoworHideMoveSelectionCursor(1);
        PokeSum_ShowOrHideMonIconSprite(1);
        ShowOrHideStatusIcon(1);
        HideShowPokerusIcon(1);
        HideShowShinyStar(1);
        break;
    }
}

static void PokeSum_ShowSpritesBeforePageFlip(void)
{
    u8 newPage;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        newPage = sMonSummaryScreen->curPageIndex - 1;
    else
        newPage = sMonSummaryScreen->curPageIndex + 1;

    switch (newPage)
    {
    case PSS_PAGE_INFO:
        ShowOrHideHpBarObjs(0);
        ShowOrHideExpBarObjs(0);
        break;
    case PSS_PAGE_SKILLS:
        break;
    case PSS_PAGE_MOVES:
        if (sMonSummaryScreen->pageFlipDirection == 0)
        {
            ShowOrHideHpBarObjs(0);
            ShowOrHideExpBarObjs(0);
        }
        else
        {
            ShoworHideMoveSelectionCursor(0);
            HideShowPokerusIcon(0);
            PokeSum_ShowOrHideMonIconSprite(0);
            HideShowShinyStar(0);
        }

        break;
    case PSS_PAGE_MOVES_INFO:
        PokeSum_ShowOrHideMonPicSprite(0);
        //PokeSum_ShowOrHideMonMarkingsSprite(0);
        ShowOrHideStatusIcon(0);
        ShowOrHideBallIconObj(0);
        HideShowPokerusIcon(0);
        HideShowShinyStar(0);
        break;
    }
}

static u8 PokeSum_IsPageFlipFinished(u8 a0)
{
    s8 pageDelta = 1;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        pageDelta = -1;

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
        if (sMonSummaryScreen->flipPagesBgHofs <= 0)
        {
            sMonSummaryScreen->flipPagesBgHofs = 0;
            sMonSummaryScreen->whichBgLayerToTranslate ^= 1;
            PokeSum_UpdateBgPriorityForPageFlip(0, 0);
            sMonSummaryScreen->flippingPages = FALSE;
            return TRUE;
        }

    if ((sMonSummaryScreen->curPageIndex + pageDelta) == PSS_PAGE_MOVES_INFO)
        if (sMonSummaryScreen->flipPagesBgHofs >= 240)
        {
            sMonSummaryScreen->flipPagesBgHofs = 240;
            sMonSummaryScreen->whichBgLayerToTranslate ^= 1;
            sMonSummaryScreen->flippingPages = FALSE;
            return TRUE;
        }

    if (sMonSummaryScreen->pageFlipDirection == 1)
    {
        if (sMonSummaryScreen->flipPagesBgHofs >= 240)
        {
            sMonSummaryScreen->flipPagesBgHofs = 240;
            sMonSummaryScreen->whichBgLayerToTranslate ^= 1;
            PokeSum_UpdateBgPriorityForPageFlip(0, 0);
            sMonSummaryScreen->flippingPages = FALSE;
            return TRUE;
        }
    }
    else if (sMonSummaryScreen->flipPagesBgHofs <= 0)
    {
        sMonSummaryScreen->whichBgLayerToTranslate ^= 1;
        sMonSummaryScreen->flipPagesBgHofs = 0;
        sMonSummaryScreen->flippingPages = FALSE;
        return TRUE;
    }

    return FALSE;
}

static void PokeSum_UpdateBgPriorityForPageFlip(u8 setBg0Priority, u8 keepBg1Bg2PriorityOrder)
{
    u8 i;
    u32 bg0Priority;
    u32 bg1Priority;
    u32 bg2Priority;

    bg0Priority = GetGpuReg(REG_OFFSET_BG0CNT) & 3;
    bg1Priority = GetGpuReg(REG_OFFSET_BG1CNT) & 3;
    bg2Priority = GetGpuReg(REG_OFFSET_BG2CNT) & 3;

    if (sMonSummaryScreen->pageFlipDirection == 1)
    {
        if (setBg0Priority == 0)
        {
            bg0Priority = 0;

            if (keepBg1Bg2PriorityOrder == 0)
            {
                if (bg1Priority > bg2Priority)
                    bg1Priority = 1, bg2Priority = 2;
                else
                    bg1Priority = 2, bg2Priority = 1;
            }
            else
            {
                if (bg1Priority > bg2Priority)
                    bg1Priority = 2, bg2Priority = 1;
                else
                    bg1Priority = 1, bg2Priority = 2;
            }
        }
        if (setBg0Priority == 1)
        {
            bg0Priority = 1;

            if (keepBg1Bg2PriorityOrder == 0)
            {
                if (bg1Priority > bg2Priority)
                    bg1Priority = 0, bg2Priority = 2;
                else
                    bg1Priority = 2, bg2Priority = 0;
            }
            else
            {
                if (bg1Priority > bg2Priority)
                    bg1Priority = 2, bg2Priority = 0;
                else
                    bg1Priority = 0, bg2Priority = 2;
            }
        }
    }

    if (sMonSummaryScreen->pageFlipDirection == 0)
    {
        bg0Priority = 0;
        if (bg1Priority > bg2Priority)
            bg1Priority = 1, bg2Priority = 2;
        else
            bg1Priority = 2, bg2Priority = 1;
    }

    for (i = 0; i < 11; i++)
    {
        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_SKILLS && sMonSummaryScreen->pageFlipDirection == 1)
            sExpBarObjs->sprites[i]->oam.priority = bg0Priority;
        else
            sExpBarObjs->sprites[i]->oam.priority = bg1Priority;

        if (i >= 9)
            continue;

        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_SKILLS && sMonSummaryScreen->pageFlipDirection == 1)
            sHpBarObjs->sprites[i]->oam.priority = bg0Priority;
        else
            sHpBarObjs->sprites[i]->oam.priority = bg1Priority;
    }

    SetGpuReg(REG_OFFSET_BG0CNT, (GetGpuReg(REG_OFFSET_BG0CNT) & 0xfffc) | bg0Priority);
    SetGpuReg(REG_OFFSET_BG1CNT, (GetGpuReg(REG_OFFSET_BG1CNT) & 0xfffc) | bg1Priority);
    SetGpuReg(REG_OFFSET_BG2CNT, (GetGpuReg(REG_OFFSET_BG2CNT) & 0xfffc) | bg2Priority);
}

static void PokeSum_CopyNewBgTilemapBeforePageFlip_2(void)
{
    u8 newPage;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        newPage = sMonSummaryScreen->curPageIndex - 1;
    else
        newPage = sMonSummaryScreen->curPageIndex + 1;

    switch (newPage)
    {
    case PSS_PAGE_INFO:
        CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);
        break;
    case PSS_PAGE_SKILLS:
        if (sMonSummaryScreen->pageFlipDirection == 1)
            CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_PokeSum_MovesListForDelete, 0, 0);
        else
            CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_TrainerMemo_Details, 0, 0);

        break;
    case PSS_PAGE_MOVES:
        if (sMonSummaryScreen->pageFlipDirection == 1)
            CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_PokeSum_MoveDetailsForDelete, 0, 0);
        else
            CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);

        break;
    case PSS_PAGE_MOVES_INFO:
        CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_PokeSum_MovesListForDelete, 0, 0);
        break;
    }
}

static void PokeSum_CopyNewBgTilemapBeforePageFlip(void)
{
    u8 newPage;

    if (sMonSummaryScreen->pageFlipDirection == 1)
        newPage = sMonSummaryScreen->curPageIndex - 1;
    else
        newPage = sMonSummaryScreen->curPageIndex + 1;

    switch (newPage)
    {
    case PSS_PAGE_INFO:
        CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);
        break;
    case PSS_PAGE_SKILLS:
        break;
    case PSS_PAGE_MOVES:
        if (sMonSummaryScreen->pageFlipDirection == 1)
            CopyToBgTilemapBuffer(3, sBgTilemap_MovesPage, 0, 0);
        else
            CopyToBgTilemapBuffer(3, sBgTilemap_MovesInfoPage, 0, 0);

        break;
    case PSS_PAGE_MOVES_INFO:
        CopyToBgTilemapBuffer(3, sBgTilemap_MovesInfoPage, 0, 0);
        break;
    }
}

static void CB2_SetUpPSS(void)
{
    switch (sMonSummaryScreen->summarySetupStep)
    {
    case 0:
        PokeSum_Setup_ResetCallbacks();
        break;
    case 1:
        PokeSum_Setup_InitGpu();
        break;
    case 2:
        PokeSum_Setup_SpritesReset();
        break;
    case 3:
        if (!PokeSum_HandleLoadBgGfx())
            return;
        break;
    case 4:
        if (!PokeSum_HandleCreateSprites())
            return;
        break;
    case 5:
        PokeSum_CreateWindows();
        break;
    case 6:
        if (!PokeSum_Setup_BufferStrings())
            return;
        break;
    case 7:
        PokeSum_PrintRightPaneText();
        break;
    case 8:
        PokeSum_PrintBottomPaneText();
        break;
    case 9:
        PokeSum_PrintAbilityDataOrMoveTypes();
        PokeSum_PrintMonTypeIcons();
        break;
    case 10:
        if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE || sMonSummaryScreen->mode == PSS_MODE_FORGET_MOVE)
            CopyToBgTilemapBuffer(3, sBgTilemap_MovesPage, 0, 0);
        else
            CopyToBgTilemapBuffer(3, sBgTilemap_MovesInfoPage, 0, 0);

        PokeSum_DrawBg3Tilemap();
        break;
    case 11:
        if (sMonSummaryScreen->isEgg)
            CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_TrainerMemo_Egg, 0, 0);
        else
        {
            if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE || sMonSummaryScreen->mode == PSS_MODE_FORGET_MOVE)
            {
                CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_PokeSum_MovesListForDelete, 0, 0);
                CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_PokeSum_MoveDetailsForDelete, 0, 0);
            }
            else
            {
                CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_TrainerMemo_Details, 0, 0);
                CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);
            }
        }

        break;
    case 12:
        BlendPalettes(PALETTES_ALL, 16, 0);
        PokeSum_PrintPageHeaderText(sMonSummaryScreen->curPageIndex);
        CommitStaticWindowTilemaps();
        break;
    case 13:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[3], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[4], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        break;
    case 14:
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(3);
        break;
    case 15:
        if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE || sMonSummaryScreen->mode == PSS_MODE_FORGET_MOVE)
        {
            PokeSum_ShowOrHideMonIconSprite(0);
            ShoworHideMoveSelectionCursor(0);
        }
        else
        {
            PokeSum_ShowOrHideMonPicSprite(0);
            //PokeSum_ShowOrHideMonMarkingsSprite(0);
            ShowOrHideBallIconObj(0);
            ShowOrHideHpBarObjs(0);
            ShowOrHideExpBarObjs(0);
        }

        ShowOrHideStatusIcon(0);
        HideShowPokerusIcon(0);
        HideShowShinyStar(0);
        break;
    default:
        PokeSum_Setup_SetVBlankCallback();
        PokeSum_FinishSetup();
        return;
    }

    sMonSummaryScreen->summarySetupStep++;
}

static u8 PokeSum_HandleLoadBgGfx(void)
{
    switch (sMonSummaryScreen->loadBgGfxStep)
    {
    case 0:
        LoadPalette(gTrainerMemoPal1, 0, 0x20 * 5);
        if (IsMonShiny(&sMonSummaryScreen->currentMon) == TRUE && !sMonSummaryScreen->isEgg)
        {
            LoadPalette(&gTrainerMemoPal1[16 * 6], 0, 0x20);
            LoadPalette(&gTrainerMemoPal1[16 * 5], 0x10, 0x20);
        }
        else
        {
            LoadPalette(&gTrainerMemoPal1[16 * 0], 0, 0x20);
            LoadPalette(&gTrainerMemoPal1[16 * 1], 0x10, 0x20);
        }

        break;
    case 1:
        ListMenuLoadStdPalAt(0x60, 1);
        LoadPalette(sBgPal7, 0x70, 0x20);
        break;
    case 2:
        ResetTempTileDataBuffers();
        break;
    case 3:
        DecompressAndCopyTileDataToVram(2, gPokeSumBgTiles, 0, 0, 0);
        break;
    case 4:
        if (FreeTempTileDataBuffersIfPossible() == TRUE)
            return FALSE;
        break;

    case 5:
    case 6:
        break;

    default:
        LoadPalette(sBgPal8, 0x80, 0x20);
        return TRUE;
    }

    sMonSummaryScreen->loadBgGfxStep++;
    return FALSE;
}

static u8 PokeSum_Setup_BufferStrings(void)
{
    switch (sMonSummaryScreen->bufferStringsStep)
    {
    case 0:
        BufferMonInfo();
        if (sMonSummaryScreen->isEgg)
        {
            sMonSummaryScreen->bufferStringsStep = 0;
            return TRUE;
        }

        break;
    case 1:
        if (sMonSummaryScreen->isEgg == 0) //if false
            BufferMonSkills();
        break;
    case 2:
        if (sMonSummaryScreen->isEgg == 0) //if false
            BufferMonMoves();
        break;
    default:
        sMonSummaryScreen->bufferStringsStep = 0;
        return TRUE;
    }

    sMonSummaryScreen->bufferStringsStep++;
    return FALSE;
}

static void BufferMonInfo(void) // seems to be PSS_PAGE_INFO or data for it
{
    u8 tempStr[20];
    u16 dexNum;
    u16 gender;
    u16 heldItem;
    u32 otId;

    dexNum = SpeciesToPokedexNum(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES));
    if (dexNum == 0xffff)
        StringCopy(sMonSummaryScreen->summary.dexNumStrBuf, gUnknown_8416202);
    else
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.dexNumStrBuf, dexNum, STR_CONV_MODE_LEADING_ZEROS, 3);

    sMonSkillsPrinterXpos->unk00 = 0;

    if (!sMonSummaryScreen->isEgg)
    {
        dexNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES);
        GetSpeciesName(sMonSummaryScreen->summary.speciesNameStrBuf, dexNum);
    }
    else
    {
        GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_NICKNAME, sMonSummaryScreen->summary.speciesNameStrBuf);
        return;
    }

    sMonSummaryScreen->monTypes[0] = gBaseStats[dexNum].type1;
    sMonSummaryScreen->monTypes[1] = gBaseStats[dexNum].type2;

    GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_NICKNAME, tempStr);
    StringCopyN_Multibyte(sMonSummaryScreen->summary.nicknameStrBuf, tempStr, POKEMON_NAME_LENGTH);
    StringGet_Nickname(sMonSummaryScreen->summary.nicknameStrBuf);

    gender = GetMonGender(&sMonSummaryScreen->currentMon);
    dexNum = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2);

    if (gender == MON_FEMALE)
        StringCopy(sMonSummaryScreen->summary.genderSymbolStrBuf, gText_FemaleSymbol);
    else if (gender == MON_MALE)
        StringCopy(sMonSummaryScreen->summary.genderSymbolStrBuf, gText_MaleSymbol);
    else
        StringCopy(sMonSummaryScreen->summary.genderSymbolStrBuf, gString_Dummy);

    if (dexNum == SPECIES_NIDORAN_M || dexNum == SPECIES_NIDORAN_F)
        if (StringCompare(sMonSummaryScreen->summary.nicknameStrBuf, gSpeciesNames[dexNum]) == 0)
            StringCopy(sMonSummaryScreen->summary.genderSymbolStrBuf, gString_Dummy); //important may use for other gender difference mon

    GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_OT_NAME, tempStr);
    StringCopyN_Multibyte(sMonSummaryScreen->summary.otNameStrBuf, tempStr, OT_NAME_LENGTH);

    ConvertInternationalString(sMonSummaryScreen->summary.otNameStrBuf, GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_LANGUAGE));

    otId = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_OT_ID) & 0xffff;
    ConvertIntToDecimalStringN(sMonSummaryScreen->summary.unk306C, otId, STR_CONV_MODE_LEADING_ZEROS, 5);

    ConvertIntToDecimalStringN(tempStr, GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_LEVEL), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringCopy(sMonSummaryScreen->summary.levelStrBuf, gText_Lv);
    StringAppendN(sMonSummaryScreen->summary.levelStrBuf, tempStr, 4);

    heldItem = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HELD_ITEM);

    if (heldItem == ITEM_NONE)
        StringCopy(sMonSummaryScreen->summary.itemNameStrBuf, gUnknown_84161EF);
    else
        CopyItemName(heldItem, sMonSummaryScreen->summary.itemNameStrBuf);
}

#define MACRO_8136350_0(x) (63 - StringLength((x)) * 6)
#define MACRO_8136350_1(x) (27 - StringLength((x)) * 6)

static void BufferMonSkills(void) // seems to be PSS_PAGE_SKILLS or data for it.
{
    u8 tempStr[20];
    u8 level,i;
    u16 abilitydatabattler, abilitydatabattler2, abilitydatabattler3, abilitydataparty;
    u16 species;
    u16 hp;
    u16 statValue;
    u32 exp;
    u32 expToNextLevel;

    hp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP);
    ConvertIntToDecimalStringN(sMonSummaryScreen->summary.curHpStrBuf, hp, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(sMonSummaryScreen->summary.curHpStrBuf, gText_Slash);

    hp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MAX_HP);
    ConvertIntToDecimalStringN(tempStr, hp, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringAppend(sMonSummaryScreen->summary.curHpStrBuf, tempStr);

    sMonSkillsPrinterXpos->curHpStr = MACRO_8136350_0(sMonSummaryScreen->summary.curHpStrBuf);

    if (sMonSummaryScreen->savedCallback == CB2_ReturnToTradeMenuFromSummary && sMonSummaryScreen->isEnemyParty == TRUE)
    {
        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ATK2);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->atkStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_DEF2);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->defStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPATK2);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->spAStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPDEF2);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->spDStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPEED2);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->speStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE]);
    }
    else
    {
        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ATK);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->atkStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_DEF);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->defStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPATK);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->spAStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPDEF);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->spDStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD]);

        statValue = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPEED);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE], statValue, STR_CONV_MODE_LEFT_ALIGN, 3);
        sMonSkillsPrinterXpos->speStr = MACRO_8136350_1(sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE]);
    }

    exp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EXP); //this is needed for level function so keep calc but dont write
    //ConvertIntToDecimalStringN(sMonSummaryScreen->summary.expPointsStrBuf, exp, STR_CONV_MODE_LEFT_ALIGN, 7);
    //sMonSkillsPrinterXpos->expStr = GetNumberRightAlign63(sMonSummaryScreen->summary.expPointsStrBuf);

    level = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_LEVEL);
    expToNextLevel = 0;
    if (level < 100)
    {
        species = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES);
        expToNextLevel = gExperienceTables[gBaseStats[species].growthRate][level + 1] - exp;
    }

    ConvertIntToDecimalStringN(sMonSummaryScreen->summary.expToNextLevelStrBuf, expToNextLevel, STR_CONV_MODE_LEFT_ALIGN, 7);
    sMonSkillsPrinterXpos->toNextLevel = MACRO_8136350_0(sMonSummaryScreen->summary.expToNextLevelStrBuf);

    //need set abilitydata values for transformation and for ability swap effects like trace  skillswap
    //if (gBattleTypeFlags != 0) //should mean if in a battle? - works
    if (gMain.inBattle) // use this for battles, using gbattletypeflags not 0, excludes wilds as those use value 0 accordign to GriffinR
    {
        u32 curr_personality, slot1_personality, slot2_personality, slot3_personality;
        curr_personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);
        slot1_personality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        slot2_personality = GetMonData(&gPlayerParty[1], MON_DATA_PERSONALITY);
        slot3_personality = GetMonData(&gPlayerParty[2], MON_DATA_PERSONALITY);

        if (!(gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_ROTATION | BATTLE_TYPE_TWO_OPPONENTS))) //found fix, setup before had wrong operation now it works
        {
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
            {
                abilitydatabattler = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].ability;
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[0], gAbilityNames[abilitydatabattler]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[0], gAbilityDescriptionPointers[abilitydatabattler]);
            }
            else //party
            {
                abilitydataparty = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[3], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[3], gAbilityDescriptionPointers[abilitydataparty]);
            }
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        {
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))//slot 1
            {
                abilitydatabattler = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].ability;
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[0], gAbilityNames[abilitydatabattler]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[0], gAbilityDescriptionPointers[abilitydatabattler]);
            }
            else if ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP)) //slot 2
            {
                abilitydatabattler2 = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].ability;
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[1], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[1], gAbilityDescriptionPointers[abilitydataparty]);
            }
            else //party
            {
                abilitydataparty = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[3], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[3], gAbilityDescriptionPointers[abilitydataparty]);
            }
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_ROTATION) //potentially setup triple batttle as well
        {
            //still to do, only one mon on field at atime technically so same layout as singles, but would need to store data for all mon for ai and battle logic
            //idea show icons in triangle, show relative health by speed of bounce, make icon flash red for mon in red health,
            //play low hp music if a mon "on field" has low hp, not just mon out as that would just constantly change
            //abilitydata = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
            {
                abilitydatabattler = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].ability;
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[0], gAbilityNames[abilitydatabattler]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[0], gAbilityDescriptionPointers[abilitydatabattler]);
            }
            else if ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP)) //slot 2
            {
                abilitydatabattler2 = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].ability;
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[1], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[1], gAbilityDescriptionPointers[abilitydataparty]);
            }
            else if ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP)) //...slot 3
            {
                //will need change this and when I setup triple battler/rotation battle extra battler positions
                //could make display of all mon in battle with their icons, then based on turn order could load/deload sprites
                //i.e 3 on battlers for triple/rotation, rather than having 3 on field load/deload leftmost and right most battler
                //and have middle battler swap betwen position left and position right, based on if its left mons turn or right mons turn. hmm   vsonic
                abilitydatabattler3 = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[2], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[2], gAbilityDescriptionPointers[abilitydataparty]);
            }
            else //party
            {
                abilitydataparty = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));
                StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[3], gAbilityNames[abilitydataparty]);
                StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[3], gAbilityDescriptionPointers[abilitydataparty]);
            }
        }
    }//would be potentially complex for rotation battles but just need to make sure party slot doesn't change when rotating battle position
    else
    {

        abilitydataparty = GetAbilityBySpecies(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES), GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ABILITY_NUM));

        for (i = 0; i < 4; i++)
        {
            StringCopy(sMonSummaryScreen->summary.abilityNameStrBuf[i], gAbilityNames[abilitydataparty]);
            StringCopy(sMonSummaryScreen->summary.abilityDescStrBuf[i], gAbilityDescriptionPointers[abilitydataparty]);
        }
    }

    sMonSummaryScreen->curMonStatusAilment = StatusToAilment(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_STATUS)); //important status screen, unk326c & this sub seem to be important for displaying status.
    if (sMonSummaryScreen->curMonStatusAilment == AILMENT_NONE)
        if (CheckPartyPokerus(&sMonSummaryScreen->currentMon, 0))
            sMonSummaryScreen->curMonStatusAilment = AILMENT_PKRS;
}

static void BufferMonMoves(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
        BufferMonMoveI(i);

    if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE)
        BufferMonMoveI(4);
}

#define GetRightAlignXpos_NDigits(a, b) ((6 * (a)) - StringLength((b)) * 6)

static void BufferMonMoveI(u8 i)//think this is the menu/function I need has move index and pp ony one in file that uses gMoveNames //transform need change
{
    u32 powerBits;
    u32 hiddenpower,power;
    power = gBattleMoves[sMonSummaryScreen->moveIds[i]].power;
    if (i < 4)
        sMonSummaryScreen->moveIds[i] = GetMonMoveBySlotId(&sMonSummaryScreen->currentMon, i);

    if (sMonSummaryScreen->moveIds[i] == MOVE_NONE)//tells function what to do if data doesn't exist in the slot/window i.e no move
    {
        StringCopy(sMonSummaryScreen->summary.moveNameStrBufs[i], gText_PokeSum_OneHyphen);
        StringCopy(sMonSummaryScreen->summary.moveCurPpStrBufs[i], gText_PokeSum_TwoHyphens);
        StringCopy(sMonSummaryScreen->summary.movePowerStrBufs[i], gText_ThreeHyphens);
        StringCopy(sMonSummaryScreen->summary.moveAccuracyStrBufs[i], gText_ThreeHyphens);
        sMonSkillsPrinterXpos->curPp[i] = 0xff;
        sMonSkillsPrinterXpos->maxPp[i] = 0xff;
        return;
    }

    if (sMonSummaryScreen->moveIds[i] == MOVE_HIDDEN_POWER)
    {
        s32 typeBits = ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP_IV) & 1) << 0)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ATK_IV) & 1) << 1)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_DEF_IV) & 1) << 2)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPEED_IV) & 1) << 3)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPATK_IV) & 1) << 4)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPDEF_IV) & 1) << 5);


        u32 type = (((NUMBER_OF_MON_TYPES - 4) * typeBits) / 63 + 1); //think changing from 15 to 16 adds one more type to options so now have fairy
        if (type == TYPE_MYSTERY || type == TYPE_SOUND)
            type = TYPE_FAIRY; // or may need to increase it by 6 to get over other types to 21 since the +1 and ++ adds 2 tellign the last type added
        //type |= F_DYNAMIC_TYPE_1 | F_DYNAMIC_TYPE_2; //no idea why removing this fixed it but guess makes sense?
        sMonSummaryScreen->moveTypes[i] = type;
    }
    else 
        sMonSummaryScreen->moveTypes[i] = gBattleMoves[sMonSummaryScreen->moveIds[i]].type;// if works right should set hidden power to display its type in summary screen
        //was playing on keeping this unknown to test but realistic people won't want to use it 
        //if they don't know what its doing

    sMonSummaryScreen->numMoves++;
    StringCopy(sMonSummaryScreen->summary.moveNameStrBufs[i], gMoveNames[sMonSummaryScreen->moveIds[i]]);

    if (i >= 4 && sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE)//assume it would only be greater than 4 if its a new move that is being learned when you already have 4
    {
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.moveCurPpStrBufs[i],
                                   gBattleMoves[sMonSummaryScreen->moveIds[i]].pp, STR_CONV_MODE_LEFT_ALIGN, 3);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.moveMaxPpStrBufs[i],
                                   gBattleMoves[sMonSummaryScreen->moveIds[i]].pp, STR_CONV_MODE_LEFT_ALIGN, 3);
    }
    else
    {
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.moveCurPpStrBufs[i],
                                   GetMonPpByMoveSlot(&sMonSummaryScreen->currentMon, i), STR_CONV_MODE_LEFT_ALIGN, 3);
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.moveMaxPpStrBufs[i],
                                   CalculatePPWithBonus(sMonSummaryScreen->moveIds[i], GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PP_BONUSES), i),
                                   STR_CONV_MODE_LEFT_ALIGN, 3);
    }

    sMonSkillsPrinterXpos->curPp[i] = GetRightAlignXpos_NDigits(2, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
    sMonSkillsPrinterXpos->maxPp[i] = GetRightAlignXpos_NDigits(2, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);    

    powerBits = ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP_IV) & 2) >> 1)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_ATK_IV) & 2) << 0)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_DEF_IV) & 2) << 1)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPEED_IV) & 2) << 2)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPATK_IV) & 2) << 3)
        | ((GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPDEF_IV) & 2) << 4);
    
    hiddenpower = (35 * powerBits) / 63 + 45;

    if (gMoveNames[sMonSummaryScreen->moveIds[i]] == gMoveNames[MOVE_HIDDEN_POWER])
        power = hiddenpower;
    else
        power = gBattleMoves[sMonSummaryScreen->moveIds[i]].power;

    if (power <= 1 && (!(gMoveNames[sMonSummaryScreen->moveIds[i]] == gMoveNames[MOVE_HIDDEN_POWER])))
        StringCopy(sMonSummaryScreen->summary.movePowerStrBufs[i], gText_ThreeHyphens);//the part that makes status/non-damage moves show as hyphens instead of a power
    else
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.movePowerStrBufs[i], power, STR_CONV_MODE_RIGHT_ALIGN, 3);

    if (gBattleMoves[sMonSummaryScreen->moveIds[i]].accuracy == 0)
        StringCopy(sMonSummaryScreen->summary.moveAccuracyStrBufs[i], gText_ThreeHyphens);//same as above but for accuracy
    else
        ConvertIntToDecimalStringN(sMonSummaryScreen->summary.moveAccuracyStrBufs[i], gBattleMoves[sMonSummaryScreen->moveIds[i]].accuracy, STR_CONV_MODE_RIGHT_ALIGN, 3);
}//will update rest of file but for now all names have been updated for this function

static u8 PokeSum_HandleCreateSprites(void)
{
    switch (sMonSummaryScreen->spriteCreationStep)
    {
    case 0:
        CreateShinyStarObj(TAG_PSS_UNK_A0, TAG_PSS_UNK_A0);
        break;
    case 1:
        CreatePokerusIconObj(TAG_PSS_UNK_96, TAG_PSS_UNK_96);
        break;
    case 2:
        //PokeSum_CreateMonMarkingsSprite();
        break;
    case 3:
        CreateMoveSelectionCursorObjs(TAG_PSS_UNK_64, TAG_PSS_UNK_64);
        break;
    case 4:
        CreateMonStatusIconObj(TAG_PSS_UNK_6E, TAG_PSS_UNK_6E);
        break;
    case 5:
        CreateHpBarObjs(TAG_PSS_UNK_78, TAG_PSS_UNK_78);
        break;
    case 6:
        CreateExpBarObjs(TAG_PSS_UNK_82, TAG_PSS_UNK_82);
        break;
    case 7:
        CreateBallIconObj();
        break;
    case 8:
        PokeSum_CreateMonIconSprite();
        break;
    default:
        PokeSum_CreateMonPicSprite();
        return TRUE;
    }

    sMonSummaryScreen->spriteCreationStep++;
    return FALSE;
}

static void PokeSum_Setup_SpritesReset(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ScanlineEffect_Stop();
}

static void PokeSum_Setup_InitGpu(void)
{
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);

    SetGpuReg(REG_OFFSET_DISPCNT, 0);

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTempaltes, NELEMS(sBgTempaltes));

    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);

    DeactivateAllTextPrinters();

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_WIN1_ON);

    PokeSum_UpdateWin1ActiveFlag(sMonSummaryScreen->curPageIndex);

    SetGpuReg(REG_OFFSET_WININ, (WININ_WIN0_OBJ | WININ_WIN0_BG0 | WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_BG3) << 8);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3);
    SetGpuReg(REG_OFFSET_WIN1V, 32 << 8 | 135);
    SetGpuReg(REG_OFFSET_WIN1H, 2 << 8 | 240);

    SetBgTilemapBuffer(1, sMonSummaryScreen->bg1TilemapBuffer);
    SetBgTilemapBuffer(2, sMonSummaryScreen->bg2TilemapBuffer);
    SetBgTilemapBuffer(3, sMonSummaryScreen->bg3TilemapBuffer);

    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void PokeSum_FinishSetup(void)
{
    if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE || sMonSummaryScreen->mode == PSS_MODE_FORGET_MOVE)
        sMonSummaryScreen->inputHandlerTaskId = CreateTask(Task_InputHandler_SelectOrForgetMove, 0);
    else
        sMonSummaryScreen->inputHandlerTaskId = CreateTask(Task_InputHandler_Info, 0);

    SetMainCallback2(CB2_RunPokemonSummaryScreen);
}

static void PokeSum_PrintPageName(const u8 * str)
{
    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 0);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], FONT_NORMAL, 4, 1, sLevelNickTextColors[1], 0, str);
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME]);
}

static void PokeSum_PrintControlsString(const u8 * str)
{
    u8 v0;
    s32 width;
    u8 r1;

    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 0);
    width = GetStringWidth(0, str, 0);
    r1 = sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS];
    AddTextPrinterParameterized3(r1, 0, 0x54 - width, 0, sLevelNickTextColors[1], 0, str);
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS]);
}

static void PrintMonLevelNickOnWindow2(const u8 * str)
{
    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 0);

    if (!sMonSummaryScreen->isEgg)  //is not an egg
    {
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO) //should remove gender symbol from move info page
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2, 4, 2, sLevelNickTextColors[1], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.levelStrBuf);

            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], FONT_NORMAL, 32, 2, sLevelNickTextColors[1], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.nicknameStrBuf);
            //main window of summary
        
            if (GetMonGender(&sMonSummaryScreen->currentMon) == MON_FEMALE)
                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], FONT_NORMAL, 108, 2, sLevelNickTextColors[3], 0, sMonSummaryScreen->summary.genderSymbolStrBuf);
            else
                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], FONT_NORMAL, 108, 2, sLevelNickTextColors[2], 0, sMonSummaryScreen->summary.genderSymbolStrBuf);
        }
        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO) //change to move name over move info
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], FONT_NORMAL, 4, 0, sLevelNickTextColors[1], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.nicknameStrBuf);
    }   //can use sLevelNickTextColors  3 & 2 for the types that get buffed/debuffed by nature

    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK]);
}

static void PokeSum_PrintRightPaneText(void)
{
    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], 0);

    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        PrintInfoPage();
        break;
    case PSS_PAGE_SKILLS:
        PrintSkillsPage();
        break;
    case PSS_PAGE_MOVES:
    case PSS_PAGE_MOVES_INFO:
        PrintMovesPage();
        break;
    }

    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE]);
}//could be relevant

static void PrintInfoPage(void)
{
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 46, 19, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.speciesNameStrBuf);

    if (!sMonSummaryScreen->isEgg)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 47 + sMonSkillsPrinterXpos->unk00, 5, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.dexNumStrBuf);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 47, 49, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.otNameStrBuf);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 47, 64, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.unk306C);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 47, 79, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.itemNameStrBuf);
    }
    else
    {
        u8 eggCycles;
        u8 hatchMsgIndex;

        eggCycles = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_FRIENDSHIP);

        if (eggCycles <= 5)
            hatchMsgIndex = 3;
        else if (eggCycles <= 10)
            hatchMsgIndex = 2;
        else if (eggCycles <= 40)
            hatchMsgIndex = 1;
        else
            hatchMsgIndex = 0;

        if (sMonSummaryScreen->isBadEgg)
            hatchMsgIndex = 0;

        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[3], FONT_NORMAL, 7, 45, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sEggHatchTimeTexts[hatchMsgIndex]);
    }
}

static const u8* GetNatureStatColor(u16 *string) 
{                     
    //changed struct to read the string for hte x position i.e which stat its on.
    // if (string == &sMonSkillsPrinterXpos->curHpStr) /always 0  actually don't need to worry about this, can just leave it off my function 
    // if (string == &sMonSkillsPrinterXpos->atkStr)
    // if (string == &sMonSkillsPrinterXpos->defStr)
    // if (string == &sMonSkillsPrinterXpos->spAStr)
    // if (string == &sMonSkillsPrinterXpos->spDStr)
    // if (string == &sMonSkillsPrinterXpos->speStr)
    u16  *atkString = &sMonSkillsPrinterXpos->atkStr;
    u16  *defString = &sMonSkillsPrinterXpos->defStr;
    u16  *speedString = &sMonSkillsPrinterXpos->speStr;
    u16  *spAtkString = &sMonSkillsPrinterXpos->spAStr;
    u16  *spDefString = &sMonSkillsPrinterXpos->spDStr;
    
    //in comparison say if string == atkString as an example (I think?)
    u8 nature;

    nature = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY, NULL) % 25;



    //actually this is all I need, this will be first check, filters for natures that default to black text 
    //order of case if string == statraised return 6 else if string == statlowered return 7  else return 0
    //temp separate for ease of reading
    switch (nature) 
    {
    case NATURE_LONELY:
        if (string == atkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == defString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_BRAVE:
        if (string == atkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == speedString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_ADAMANT:
        if (string == atkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spAtkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_NAUGHTY:
        if (string == atkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spDefString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break; //end of attack boosts
    case NATURE_BOLD:
        if (string == defString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == atkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_RELAXED:
        if (string == defString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == speedString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_IMPISH:
        if (string == defString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spAtkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_LAX:
        if (string == defString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spDefString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break; //end of defense boosts
    case NATURE_TIMID:
        if (string == speedString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == atkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_HASTY:
        if (string == speedString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == defString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_JOLLY:
        if (string == speedString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spAtkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_NAIVE:
        if (string == speedString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spDefString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;//end of speed boosts
    case NATURE_MODEST:
        if (string == spAtkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == atkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_MILD:
        if (string == spAtkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == defString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_QUIET:
        if (string == spAtkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == speedString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_RASH:
        if (string == spAtkString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spDefString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break; //end of sp atk boosts
    case NATURE_CALM:
        if (string == spDefString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == atkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_GENTLE:
        if (string == spDefString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == defString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_SASSY:
        if (string == spDefString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == speedString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break;
    case NATURE_CAREFUL:
        if (string == spDefString)
            return sLevelNickTextColors[PURPLE_COLOR];
        else if (string == spAtkString)
            return sLevelNickTextColors[LIGHT_GREY_COLOR];
        else
            return sLevelNickTextColors[BLACK_COLOR];
        break; //end of sp def boosts
    case NATURE_QUIRKY:
    case NATURE_BASHFUL:
    case NATURE_SERIOUS:
    case NATURE_DOCILE:
    case NATURE_HARDY:
    default: //neutral natures
        return sLevelNickTextColors[BLACK_COLOR]; //for natures that don't boost any stat i.e neutral natures
        break;
    }
}

//put logic here for nature color 6 for boost   7 for negative
//think can replace sLevelNickTextColors with  function that checks nature 
//and returns color 0 6 or 7 based on how stat should be affected by nature
static void PrintSkillsPage(void)//vsonic 
{
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[3], FONT_NORMAL, 14 + sMonSkillsPrinterXpos->curHpStr, 4, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.curHpStrBuf);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + sMonSkillsPrinterXpos->atkStr, 22, GetNatureStatColor(&sMonSkillsPrinterXpos->atkStr), TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_ATK]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + sMonSkillsPrinterXpos->defStr, 35, GetNatureStatColor(&sMonSkillsPrinterXpos->defStr), TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_DEF]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + sMonSkillsPrinterXpos->spAStr, 48, GetNatureStatColor(&sMonSkillsPrinterXpos->spAStr), TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPA]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + sMonSkillsPrinterXpos->spDStr, 61, GetNatureStatColor(&sMonSkillsPrinterXpos->spDStr), TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPD]);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 50 + sMonSkillsPrinterXpos->speStr, 74, GetNatureStatColor(&sMonSkillsPrinterXpos->speStr), TEXT_SKIP_DRAW, sMonSummaryScreen->summary.statValueStrBufs[PSS_STAT_SPE]);
    //AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 15 + sMonSkillsPrinterXpos->expStr, 87, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.expPointsStrBuf);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 15 + sMonSkillsPrinterXpos->toNextLevel, 87, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.expToNextLevelStrBuf);
}   //ok since this is going on window 3, and I need to move up abilities which are on window 5 think need decrease height of 3 for skills menu

#define GetOtherMoveNamePrinterYpos(x) ((x) * 28 + 2)    //used for pp of move box 0 & 2, subtracted 3 to match hopefuly
#define SpecialMove1NamePrinterYpos(x) ((x) * 28 + 3)   //specic for id 1 move slot 2
#define GetMoveNamePrinterYpos(x) ((x) * 28 + 5)    //used for pp
#define GetOtherMovePpPinterYpos(x) ((x) * 28 + 13) //used for moveename

////this is the function I need for changing move name position
//need to shift y position formula then move x after, as it uses x to determine why
//since they all go to same spot it just made a formula to fix the position
static void PrintMovesPage(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
        PokeSum_PrintMoveName(i);

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
    {
        if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE)
            PokeSum_PrintMoveName(4);
        else
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[3], FONT_NORMAL,
                                         32, GetMoveNamePrinterYpos(4),
                                         sPrintMoveTextColors[0], TEXT_SKIP_DRAW, gFameCheckerText_Cancel);
    }
}//ok this function doenst' matter its just for displaying the cancel button when you select a move, and for telling the main funtion below how to loop

#define GetMovePpPrinterYpos(x) ((x) * 28 + 16)
//function for printing pp values & changing position
static void PokeSum_PrintMoveName(u8 i)
{
    u8 colorIdx = 0;
    u8 curPP = GetMonPpByMoveSlot(&sMonSummaryScreen->currentMon, i);
    u16 move = sMonSummaryScreen->moveIds[i];
    u8 ppBonuses = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PP_BONUSES);
    u8 maxPP = CalculatePPWithBonus(move, ppBonuses, i);

    if (i == 4)//used for move slot loop, believe i==4 is moves being learned
        curPP = maxPP;

    //this line prints the move names in the windows I got it to move how I want by swapping all GetMoveNamePrinterYpos & GetMovePpPrinterYpos in this funtion
    //I have the y value I just need to move this further to the left now
    
    
   // AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], FONT_NORMAL, 1, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);
    //making x value after font 0 did move it over without shifting the y value but not nearly enough, it was like the text instead of moving the window..
    //actually I think that is what it does, its like battle_message.c its only moving text within the window not the window itself hmm
    //tried a negative number onfirmed can go below zero to move text left, also confirm the x y values are only for text need to move window itslef some how
    //I think it may be a matter of changing windowIds,  think window ID has a fixed coordinate?

    if (i == 0)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 1, GetOtherMovePpPinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);
    }
    if (i == 1)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 1, GetOtherMovePpPinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);
    }
    if (i == 2)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 1, GetOtherMovePpPinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);
    }
    if (i == 3)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 1, GetMovePpPrinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);
    }
    if (i == 4)
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 1, GetMovePpPrinterYpos(i), sPrintMoveTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveNameStrBufs[i]);


    if (sMonSummaryScreen->moveIds[i] == 0 || (curPP == maxPP))//
        colorIdx = 0;
    else if (curPP == 0)
        colorIdx = 3;
    else if (maxPP == 3)
    {
        if (curPP == 2)
            colorIdx = 2;
        else if (curPP == 1)
            colorIdx = 1;
    }
    else if (maxPP == 2)
    {
        if (curPP == 1)
            colorIdx = 1;
    }
    else
    {
        if (curPP <= (maxPP / 4))
            colorIdx = 2;
        else if (curPP <= (maxPP / 2))
            colorIdx = 1;
    }                                           //gap valus 10,12, 6


    if (i == 0) //gap valus 10,12, 6
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
            gText_PokeSum_PP);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
        if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
        }
    }
    if (i == 1)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, SpecialMove1NamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
            gText_PokeSum_PP);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], SpecialMove1NamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
        if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, SpecialMove1NamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], SpecialMove1NamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
        }
    }
    if (i == 2)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
            gText_PokeSum_PP);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
        if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], GetOtherMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
        }
    }
    if (i == 3)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
            gText_PokeSum_PP);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
        if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
        }
    }
    if (i == 4)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
            gText_PokeSum_PP);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);
        if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
        {
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
            AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
        }
    }

    /*AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 64, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW,
        gText_PokeSum_PP);
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 74 + sMonSkillsPrinterXpos->curPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveCurPpStrBufs[i]);

    if (sMonSummaryScreen->moveIds[i] != MOVE_NONE)
    {
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 86, GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, gText_Slash);
        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_3], FONT_NORMAL, 92 + sMonSkillsPrinterXpos->maxPp[i], GetMoveNamePrinterYpos(i), sPrintMoveTextColors[colorIdx], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.moveMaxPpStrBufs[i]);
    }*/
}//AddTextPrinter functions above put the pp symbol back slash and current & max pp values in menu

static void PokeSum_PrintBottomPaneText(void)
{
    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 0);
    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], 0);

    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        PokeSum_PrintTrainerMemo();
        break;
    case PSS_PAGE_SKILLS:
        PokeSum_PrintExpPoints_NextLv();
        break;
    case PSS_PAGE_MOVES_INFO:
        PokeSum_PrintSelectedMoveStats();
        break;
    case PSS_PAGE_MOVES:
        break;//doing something here may fix garbage data
    }

    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO]);
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6]);
}

static void PokeSum_PrintTrainerMemo(void)
{
    if (!sMonSummaryScreen->isEgg)
        PokeSum_PrintTrainerMemo_Mon();
    else
        PokeSum_PrintTrainerMemo_Egg();
}

#define TRAINER_MEMO_SUMMARY
static void PokeSum_PrintTrainerMemo_Mon_HeldByOT(void) // seems to relate to or be PSS_PAGE_INFO
{                   //pretty sure this is trainer memo screen used for your caught mon
    u8 nature;
    u8 level;
    u8 metLocation;
    u8 levelStr[5];
    u8 mapNameStr[32];
    u8 natureMetOrHatchedAtLevelStr[152];

    DynamicPlaceholderTextUtil_Reset();
    nature = GetNature(&sMonSummaryScreen->currentMon);
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, gNatureNamePointers[nature]);
    level = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LEVEL);

    if (level == 0)
        level = 5;

    ConvertIntToDecimalStringN(levelStr, level, STR_CONV_MODE_LEFT_ALIGN, 3);
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(1, levelStr);

    metLocation = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LOCATION);

    if (MapSecIsInKantoOrSevii(metLocation) == TRUE)
        GetMapNameGeneric_(mapNameStr, metLocation);
    else
    {
        if (sMonSummaryScreen->isEnemyParty == TRUE || IsMultiBattlePartner() == TRUE)
            StringCopy(mapNameStr, gText_Somewhere);
        else
            StringCopy(mapNameStr, gText_PokeSum_ATrade);
    }

    DynamicPlaceholderTextUtil_SetPlaceholderPtr(2, mapNameStr);

    // These pairs of strings are bytewise identical to each other in English,
    // but Japanese uses different grammar for Bold and Gentle natures.
    if (GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LEVEL) == 0) // Hatched
    {
        if (GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EVENT_LEGAL) == 1) // Fateful encounter
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterHatched_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterHatched);
        }
        else
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_Hatched_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_Hatched);
        }
    }
    else
    {
        if (metLocation == METLOC_FATEFUL_ENCOUNTER)
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet);
        }
        else
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_Met_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_Met);
        }
    }

    AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL, 0, 3, 0, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, natureMetOrHatchedAtLevelStr);
}

static void PokeSum_PrintTrainerMemo_Mon_NotHeldByOT(void)  //believe this is traded/ not originally yours
{
    u8 nature;
    u8 level;
    u8 metLocation;
    u8 levelStr[5];
    u8 mapNameStr[32];
    u8 natureMetOrHatchedAtLevelStr[152];

    DynamicPlaceholderTextUtil_Reset();
    nature = GetNature(&sMonSummaryScreen->currentMon);
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(0, gNatureNamePointers[nature]);

    level = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LEVEL);

    if (level == 0)
        level = 5;  //assume mostly for setting egg hatch level

    ConvertIntToDecimalStringN(levelStr, level, STR_CONV_MODE_LEFT_ALIGN, 3);
    DynamicPlaceholderTextUtil_SetPlaceholderPtr(1, levelStr);

    metLocation = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LOCATION);

    if (!MapSecIsInKantoOrSevii(metLocation) || !CurrentMonIsFromGBA())
    {
        if (IsMultiBattlePartner() == TRUE)
        {
            PokeSum_PrintTrainerMemo_Mon_HeldByOT();
            return;
        }

        if (metLocation == METLOC_FATEFUL_ENCOUNTER)
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet);
        }
        else
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gUnknown_841979D);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gUnknown_8419782);
        }

        AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL, 0, 3, 0, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, natureMetOrHatchedAtLevelStr);
        return;
    }

    if (MapSecIsInKantoOrSevii(metLocation) == TRUE)
        GetMapNameGeneric_(mapNameStr, metLocation);
    else
        StringCopy(mapNameStr, gText_PokeSum_ATrade);

    DynamicPlaceholderTextUtil_SetPlaceholderPtr(2, mapNameStr);

    // These pairs of strings are bytewise identical to each other in English,
    // but Japanese uses different grammar for Bold and Gentle natures.
    if (GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LEVEL) == 0) // hatched from an EGG
    {
        if (GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EVENT_LEGAL) == 1) // Fateful encounter
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyFatefulEncounterHatched_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyFatefulEncounterHatched);
        }
        else
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyMet_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyMet);
        }
    }
    else
    {
        if (metLocation == METLOC_FATEFUL_ENCOUNTER)
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_FatefulEncounterMet);
        }
        else
        {
            if (PokeSum_IsMonBoldOrGentle(nature))
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyMet_BoldGentleGrammar);
            else
                DynamicPlaceholderTextUtil_ExpandPlaceholders(natureMetOrHatchedAtLevelStr, gText_PokeSum_ApparentlyMet);
        }
    }

    AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[4], FONT_NORMAL, 0, 3, 0, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, natureMetOrHatchedAtLevelStr);
}

static void PokeSum_PrintTrainerMemo_Mon(void)
{
    if (PokeSum_BufferOtName_IsEqualToCurrentOwner(&sMonSummaryScreen->currentMon) == TRUE)
        PokeSum_PrintTrainerMemo_Mon_HeldByOT();
    else
        PokeSum_PrintTrainerMemo_Mon_NotHeldByOT();
}

static void PokeSum_PrintTrainerMemo_Egg(void)
{
    u8 metLocation;
    u8 version;
    u8 chosenStrIndex = 0;

    metLocation = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_LOCATION);

    if (sMonSummaryScreen->monList.mons != gEnemyParty)
    {
        if (metLocation == METLOC_FATEFUL_ENCOUNTER || GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EVENT_LEGAL) == 1)
            chosenStrIndex = 4;
        else
        {
            version = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_GAME);

            if (version != VERSION_LEAF_GREEN && version != VERSION_FIRE_RED)
                chosenStrIndex = 1;
            else if (metLocation == METLOC_SPECIAL_EGG)
                chosenStrIndex = 2;

            if (chosenStrIndex == 0 || chosenStrIndex == 2)
                if (PokeSum_BufferOtName_IsEqualToCurrentOwner(&sMonSummaryScreen->currentMon) == FALSE)
                    chosenStrIndex++;
        }
    }
    else
    {
        if (metLocation == METLOC_FATEFUL_ENCOUNTER || GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EVENT_LEGAL) == 1)
            chosenStrIndex = 4;
        else
        {
            version = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_GAME);

            if (version != VERSION_LEAF_GREEN && version != VERSION_FIRE_RED)
            {
                if (metLocation == METLOC_SPECIAL_EGG)
                    chosenStrIndex = 5;
            }
            else if (metLocation == METLOC_SPECIAL_EGG)
                chosenStrIndex = 2;

            if (PokeSum_BufferOtName_IsEqualToCurrentOwner(&sMonSummaryScreen->currentMon) == FALSE)
                chosenStrIndex++;
        }
    }

    if (sMonSummaryScreen->isBadEgg)
        chosenStrIndex = 0;

    AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL, 0, 3, 0, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sEggOriginTexts[chosenStrIndex]);
}

static void PokeSum_PrintExpPoints_NextLv(void)
{
    AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL,
                                 26, 7,
                                 sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                 gText_PokeSum_NextLv);  //remove this, actally put nextlevl in this place & decrease height to match
                  

    /*AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL,
                                 26, 20,
                                 sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                 gText_PokeSum_NextLv);*///this just window text need the actual stats too
}

static void PokeSum_PrintSelectedMoveStats(void)
{
    if (sMoveSelectionCursorPos < 5)
    {
        if (sMonSummaryScreen->mode != PSS_MODE_SELECT_MOVE && sMoveSelectionCursorPos == 4)
            return;

        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], FONT_NORMAL,
                                     4, 8,
                                     sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                     sMonSummaryScreen->summary.movePowerStrBufs[sMoveSelectionCursorPos]);

        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], FONT_NORMAL,
                                     4, 20,
                                     sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                     sMonSummaryScreen->summary.moveAccuracyStrBufs[sMoveSelectionCursorPos]);

        AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[4], FONT_NORMAL,
                                     7, 12,
                                     0, 0,
                                     sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                     gMoveDescriptionPointers[sMonSummaryScreen->moveIds[sMoveSelectionCursorPos]]);
    }
}

#define MOVEICON_ABILITYDESC
static void PokeSum_PrintAbilityDataOrMoveTypes(void)
{
    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        break;
    case PSS_PAGE_SKILLS:
        PokeSum_PrintAbilityNameAndDesc();
        PutWindowTilemap(sMonSummaryScreen->windowIds[5]);
        break;
    case PSS_PAGE_MOVES:
    case PSS_PAGE_MOVES_INFO:
        PokeSum_DrawMoveTypeIcons();
        PutWindowRectTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_5],0,0,5,2);  //...welp that worked o.0  just need to adjust y
        PutWindowRectTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_5], 0, 3, 5, 2); //move 2   
        PutWindowRectTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_5], 0, 7, 5, 2);  //move 3
        PutWindowRectTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_5], 0, 10, 5, 2); //move 4
        PutWindowRectTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_5], 0, 14, 5, 2); //move learn
        
        //moves 2 & 4 window position doesn't work, 2 is too high, 4 is too low
        //think need to shift how it handles movement so I can make smaller incremental movement, 

        break;
    }

    //PutWindowTilemap(sMonSummaryScreen->windowIds[5]);//other option is use PutWindowRectTilemap function which I believe would
    //only place a specific section of the tile map atspecific area rather than fill the entire window, could do that with original logic for window 5
    //and original window 5 height
}//best option use original window 5 height, the type icons are positioned perfectly I just need to split up the window


//think I was planning to run move values & ability values into a single function?
//could work/make sense
static void PokeSum_PrintAbilityNameAndDesc(void)
{

    u32 curr_personality, slot1_personality, slot2_personality, slot3_personality;
    curr_personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);
    slot1_personality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
    slot2_personality = GetMonData(&gPlayerParty[1], MON_DATA_PERSONALITY);
    slot3_personality = GetMonData(&gPlayerParty[2], MON_DATA_PERSONALITY); //eventually for triple/ rotation battles

    if (!gMain.inBattle)
    {
        FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);//checked window fills entire graphic

        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
            66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[3]);

        AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
            2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[3]);
    }

    //for in battle
    if (gMain.inBattle) //trainer in bnattle, not if mon is in battle
    {
        if (!(IsDoubleBattle())) //problem appears to be function always returns 0, I think I need to loop
        {
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))//....changedd if current mon matches party slot and hp not 0, use battle value
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0); //I think this is clearing window ? so extra safety

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[0]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[0]);
            }
            else //party
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[3]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[3]);
            }
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        {
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[0]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[0]);
            }
            else if ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[1]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[1]);
            }
            else //party
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[3]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[3]);
            }
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_ROTATION)
        {
            if ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[0]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[0]);
            }
            else if ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[1]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[1]);
            }
            else if ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[2]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[2]);
            }
            else //party
            {
                FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    66, 0, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityNameStrBuf[3]);

                AddTextPrinterParameterized3(sMonSummaryScreen->windowIds[5], FONT_NORMAL,
                    2, 10, sLevelNickTextColors[0], TEXT_SKIP_DRAW, sMonSummaryScreen->summary.abilityDescStrBuf[3]);
            }
        }
    }
     //ok I can't loop? or have empty data as it prints garbage if the field is empty, so I need it to keep it from printing if the field is empty and just increment instead
}

//new define so I can shift type icon y position without messing with the window
//since its not full screen height I may need to just make this x + 4
//actually since screen length is 28? I think this is just saying move down 4 each time at the same x position?
//since I'm already moving my windows down by 4 each time I think my y needs to be 0?

//ok so before the type icons were all in one long window and was using the loop number to determine the y value i.e move "down" a row
//but I'm creating my own individual window at the height I want so I need a constant value separate from the loop
#define NewMoveTypeIconYpos(x) ((x) * 28 + 0)
#define GetMoveTypeIconPrinterYpos(x) ((x) * 0 + 1)  //type icon just for first move

#define MOVE_1 0
#define MOVE_2 1
#define MOVE_3 2
#define MOVE_4 3

static void PokeSum_DrawMoveTypeIcons(void) //idea get icons to print on window 3 see if that works since its the same size as old window 5
{
    u8 i;

    FillWindowPixelBuffer(sMonSummaryScreen->windowIds[5], 0x0);

    //FillWindowPixelRect(sMonSummaryScreen->windowIds[5], 0x0, 0, 0, 5, 2);   //ok can't use this, it puts white space over graphics

    //fills without the putwindowtilemap function appears to do nothing? yeah it does. which is good.
    //PutWindowRectTilemap can use this instead so tilemap has selective position instead of covering the entire window and everything below it

    //but putting tileamap without fill buffer for full  window still puts the icon, it just doesn't cover/remove whitespace?

    for (i = 0; i < 4; i++)
    {
        if (sMonSummaryScreen->moveIds[i] == MOVE_NONE)
            continue;

        

        if (i == 0)

        BlitMoveInfoIcon(sMonSummaryScreen->windowIds[5], sMonSummaryScreen->moveTypes[i] + 1, 3, GetMoveTypeIconPrinterYpos(i));

        else {
            BlitMoveInfoIcon(sMonSummaryScreen->windowIds[5], sMonSummaryScreen->moveTypes[i] + 1, 3, NewMoveTypeIconYpos(i));
        }//so my understanding is blitmove, copies the icons onto specific area of the assigned window
        //I believe PutWindowRectTilemap also puts a specific area of teh window on the bg,/screen so I should be able to
        //I think I should be able to use those together to only display the window at the y position icons are printed
        //to get the icons without the space between.  if so that would solve everything
        //potential issue is if this and or PutWindowRectTilemap dont work how I expect and I have to make my own PutWindowRectTilemap 
        //that works how I expect

    }//note printerypos is again using value 28 in its function, seems to be deriving y from x?

    if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE)
        BlitMoveInfoIcon(sMonSummaryScreen->windowIds[5], sMonSummaryScreen->moveTypes[4] + 1, 3, NewMoveTypeIconYpos(4));
}// movetype 4 is the type icon for the 4th move, which is when you are learning a new move, and already have 4, its where the cancel button appears
//attempted change, put window id to 3, instead of 5, and icon showed up, but pallete wwas wrong, think I can shift the type icons to window 3 though
//need to go through the work flow and see how it prepares window 5 to display the icon, may just be a matter of shifting those to window 3
//didn't work, going back to attempt to use the multiple windows
//vsonic IMPORTANT

//note need to update fire red move learn to emerald standard where it asks you to confirm you want to replace a move,
//with a yes no box and takes you back to move learn so you don't accidentally replace/forget moves. IMPORTANT vsonic

static void PokeSum_PrintPageHeaderText(u8 curPageIndex) //
{
    switch (curPageIndex)
    {
    case PSS_PAGE_INFO:
        PokeSum_PrintPageName(gText_PokeSum_PageName_PokemonInfo);
        if (!sMonSummaryScreen->isEgg)
            PokeSum_PrintControlsString(gText_PokeSum_Controls_PageCancel);
        else
            PokeSum_PrintControlsString(gText_PokeSum_Controls_Cancel);

        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case PSS_PAGE_SKILLS:
        PokeSum_PrintPageName(gText_PokeSum_PageName_PokemonSkills);
        PokeSum_PrintControlsString(gText_PokeSum_Controls_Page);
        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case PSS_PAGE_MOVES:
        PokeSum_PrintPageName(gText_PokeSum_PageName_KnownMoves);
        PokeSum_PrintControlsString(gText_PokeSum_Controls_PageDetail);
        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case PSS_PAGE_MOVES_INFO:
        PokeSum_PrintPageName(gText_PokeSum_PageName_KnownMoves);
        if (!gMain.inBattle)
            PokeSum_PrintControlsString(gText_PokeSum_Controls_PickSwitch);
        else
            PokeSum_PrintControlsString(gText_PokeSum_Controls_Pick);
        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    case PSS_PAGE_MOVE_DELETER:
        PokeSum_PrintPageName(gText_PokeSum_PageName_KnownMoves);
        PokeSum_PrintControlsString(gText_PokeSum_Controls_PickDelete);
        PrintMonLevelNickOnWindow2(gText_PokeSum_NoData);
        break;
    default:
        break;
    }
}

static void CommitStaticWindowTilemaps(void)
{
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME]);
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS]);
    PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK]);
}

static void Task_DestroyResourcesOnExit(u8 taskId)
{
    PokeSum_DestroySprites();
    FreeAllSpritePalettes();

    if (IsCryPlayingOrClearCrySongs() == TRUE)
        StopCryAndClearCrySongs();

    PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
    FreeAllWindowBuffers();
    DestroyTask(taskId);
    SetMainCallback2(sMonSummaryScreen->savedCallback);

    sLastViewedMonIndex = GetLastViewedMonIndex();

    FREE_AND_SET_NULL_IF_SET(sMonSummaryScreen);
    FREE_AND_SET_NULL_IF_SET(sMonSkillsPrinterXpos);
}

static void CB2_RunPokemonSummaryScreen(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void PokeSum_FlipPages_SlideHpExpBarsOut(void)
{
    u8 i;

    for (i = 0; i < 11; i++)
    {
        if (sExpBarObjs->xpos[i] < 240)
        {
            sExpBarObjs->xpos[i] += 60;
            sExpBarObjs->sprites[i]->pos1.x = sExpBarObjs->xpos[i] + 60;
        }

        if (i >= 9)
            continue;

        if (sHpBarObjs->xpos[i] < 240)
        {
            sHpBarObjs->xpos[i] += 60;
            sHpBarObjs->sprites[i]->pos1.x = sHpBarObjs->xpos[i] + 60;
        }
    }
}

static void PokeSum_FlipPages_SlideHpExpBarsIn(void)
{
    u8 i;

    for (i = 0; i < 11; i++)
    {
        if (sExpBarObjs->xpos[i] > 156 + (8 * i))
        {
            sExpBarObjs->xpos[i] -= 60;

            if (sExpBarObjs->xpos[i] < 156 + (8 * i))
                sExpBarObjs->xpos[i] = 156 + (8 * i);

            sExpBarObjs->sprites[i]->pos1.x = sExpBarObjs->xpos[i];
        }

        if (i >= 9)
            continue;

        if (sHpBarObjs->xpos[i] > 172 + (8 * i))
        {
            sHpBarObjs->xpos[i] -= 60;

            if (sHpBarObjs->xpos[i] < 172 + (8 * i))
                sHpBarObjs->xpos[i] = 172 + (8 * i);

            sHpBarObjs->sprites[i]->pos1.x = sHpBarObjs->xpos[i];
        }
    }
}

static void PokeSum_FlipPages_SlideLayerLeft(void)
{
    if (sMonSummaryScreen->flipPagesBgHofs < 240)
    {
        sMonSummaryScreen->flipPagesBgHofs += 60;
        if (sMonSummaryScreen->flipPagesBgHofs > 240)
            sMonSummaryScreen->flipPagesBgHofs = 240;

        if (sMonSummaryScreen->whichBgLayerToTranslate == 0)
            SetGpuReg(REG_OFFSET_BG2HOFS, -sMonSummaryScreen->flipPagesBgHofs);
        else
            SetGpuReg(REG_OFFSET_BG1HOFS, -sMonSummaryScreen->flipPagesBgHofs);
    }
}

static void PokeSum_FlipPages_SlideLayeRight(void)
{
    if (sMonSummaryScreen->flipPagesBgHofs >= 60)
    {
        sMonSummaryScreen->flipPagesBgHofs -= 60;
        if (sMonSummaryScreen->flipPagesBgHofs < 0)
            sMonSummaryScreen->flipPagesBgHofs = 0;

        if (sMonSummaryScreen->whichBgLayerToTranslate == 0)
            SetGpuReg(REG_OFFSET_BG1HOFS, -sMonSummaryScreen->flipPagesBgHofs);
        else
            SetGpuReg(REG_OFFSET_BG2HOFS, -sMonSummaryScreen->flipPagesBgHofs);

        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
            SetGpuReg(REG_OFFSET_BG0HOFS, -sMonSummaryScreen->flipPagesBgHofs);
    }
}

static void PokeSum_FlipPages_HandleBgHofs(void)
{
    if (sMonSummaryScreen->pageFlipDirection == 1) //Right
    {
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
            PokeSum_FlipPages_SlideLayerLeft();
        else
            PokeSum_FlipPages_SlideLayeRight();
    }
    else
    {
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES)
            PokeSum_FlipPages_SlideLayeRight();
        else
            PokeSum_FlipPages_SlideLayerLeft();
    }
}

static void PokeSum_FlipPages_HandleHpExpBarSprites(void)
{
    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_SKILLS
        && sMonSummaryScreen->pageFlipDirection == 0)
        PokeSum_FlipPages_SlideHpExpBarsIn();

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES
        && sMonSummaryScreen->pageFlipDirection == 1)
        PokeSum_FlipPages_SlideHpExpBarsOut();
}

static void VBlankCB_PokemonSummaryScreen(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();

    if (sMonSummaryScreen->flippingPages == FALSE)
        return;

    PokeSum_FlipPages_HandleBgHofs();
    PokeSum_FlipPages_HandleHpExpBarSprites();
}

static void PokeSum_Setup_ResetCallbacks(void)
{
    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
}

static void PokeSum_Setup_SetVBlankCallback(void)
{
    SetVBlankCallback(VBlankCB_PokemonSummaryScreen);
}

static void PokeSum_CreateWindows(void)
{
    u8 i;

    InitWindows(sWindowTemplates_Dummy);

    for (i = 0; i < 3; i++)
        sMonSummaryScreen->windowIds[i] = AddWindow(&sWindowTemplates_Permanent_Bg1[i]);

    for (i = 0; i < 4; i++)
        switch (sMonSummaryScreen->curPageIndex)//loops 4 times
        {
        case PSS_PAGE_INFO:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Info[i]);
            break;
        case PSS_PAGE_SKILLS:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Skills[i]);
            break;
        case PSS_PAGE_MOVES:
        case PSS_PAGE_MOVES_INFO:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Moves[i]);
            break;//possibly make 2 more loops for move info page to split the template up, would need loop to 6 instead of 4
        default:
            break;
        }
}//pretty much to separate pp, and cancel button from window for move names

static void PokeSum_AddWindows(u8 curPageIndex)
{
    u8 i;
    u32 bgPriority1 = GetGpuReg(REG_OFFSET_BG1CNT) & 3;
    u32 bgPriority2 = GetGpuReg(REG_OFFSET_BG2CNT) & 3;

    for (i = 0; i < 7; i++)
        sMonSummaryScreen->windowIds[i] = 0xff;

    if ((sMonSummaryScreen->pageFlipDirection == 1 && sMonSummaryScreen->curPageIndex != PSS_PAGE_MOVES_INFO)
        || (sMonSummaryScreen->pageFlipDirection == 0 && sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES))
    {
        if (bgPriority2 > bgPriority1)
            for (i = 0; i < 3; i++)
                sMonSummaryScreen->windowIds[i] = AddWindow(&sWindowTemplates_Permanent_Bg2[i]);
        else
            for (i = 0; i < 3; i++)
                sMonSummaryScreen->windowIds[i] = AddWindow(&sWindowTemplates_Permanent_Bg1[i]);
    }
    else
    {
        if (bgPriority2 > bgPriority1)
            for (i = 0; i < 3; i++)
                sMonSummaryScreen->windowIds[i] = AddWindow(&sWindowTemplates_Permanent_Bg1[i]);
        else
            for (i = 0; i < 3; i++)
                sMonSummaryScreen->windowIds[i] = AddWindow(&sWindowTemplates_Permanent_Bg2[i]);
    }

    for (i = 0; i < 4; i++)
        switch (curPageIndex)
        {
        case PSS_PAGE_INFO:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Info[i]);
            break;
        case PSS_PAGE_SKILLS:
        default:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Skills[i]);
            break;
        case PSS_PAGE_MOVES:
        case PSS_PAGE_MOVES_INFO:
            sMonSummaryScreen->windowIds[i + 3] = AddWindow(&sWindowTemplates_Moves[i]);
            break;
        }
}

static void PokeSum_RemoveWindows(u8 curPageIndex)//loops to 6 because windowId are 3 more than windowtemplate 6 is actually value 6 in remove window
{
    u8 i;

    for (i = 0; i < 7; i++)
        RemoveWindow(sMonSummaryScreen->windowIds[i]);

}

static void PokeSum_SetHelpContext(void)
{
    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        //SetHelpContext(HELPCONTEXT_POKEMON_INFO);
        break;
    case PSS_PAGE_SKILLS:
       //SetHelpContext(HELPCONTEXT_POKEMON_SKILLS);
        break;
    case PSS_PAGE_MOVES:
    case PSS_PAGE_MOVES_INFO:
       // SetHelpContext(HELPCONTEXT_POKEMON_MOVES);
        break;
    }
}

static u8 PokeSum_BufferOtName_IsEqualToCurrentOwner(struct Pokemon * mon)
{
    u8 i;
    u8 multiplayerId;
    u32 trainerId = 0;

    if (sMonSummaryScreen->monList.mons == gEnemyParty)
    {
        multiplayerId = GetMultiplayerId() ^ 1;
        trainerId = gLinkPlayers[multiplayerId].trainerId & 0xffff;
        StringCopy(sMonSummaryScreen->summary.otNameStrBufs[0], gLinkPlayers[multiplayerId].name);
    }
    else
    {
        trainerId = GetPlayerTrainerId() & 0xffff;
        StringCopy(sMonSummaryScreen->summary.otNameStrBufs[0], gSaveBlock2Ptr->playerName);
    }

    if (trainerId != (GetMonData(mon, MON_DATA_OT_ID) & 0xffff))
        return FALSE;

    GetMonData(mon, MON_DATA_OT_NAME, sMonSummaryScreen->summary.otNameStrBufs[1]);

    if (!StringCompareWithoutExtCtrlCodes(sMonSummaryScreen->summary.otNameStrBufs[0], sMonSummaryScreen->summary.otNameStrBufs[1]))
        return TRUE;
    else
        return FALSE;

    return TRUE;
}

#define SUB_8138538_BASE_TILE_NUM (345)

static void PokeSum_DrawBg3Tilemap(void)//relates to bg may be useful for understanding battle menu bg
{
    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        if (!sMonSummaryScreen->isEgg)
        {
            FillBgTilemapBufferRect(3, 17 + SUB_8138538_BASE_TILE_NUM, 13, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 33 + SUB_8138538_BASE_TILE_NUM, 13, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 16 + SUB_8138538_BASE_TILE_NUM, 14, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 32 + SUB_8138538_BASE_TILE_NUM, 14, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 18 + SUB_8138538_BASE_TILE_NUM, 15, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 34 + SUB_8138538_BASE_TILE_NUM, 15, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 20 + SUB_8138538_BASE_TILE_NUM, 16, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 36 + SUB_8138538_BASE_TILE_NUM, 16, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 18 + SUB_8138538_BASE_TILE_NUM, 17, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 34 + SUB_8138538_BASE_TILE_NUM, 17, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 21 + SUB_8138538_BASE_TILE_NUM, 18, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 37 + SUB_8138538_BASE_TILE_NUM, 18, 1, 1, 1, 0);
        }
        else
        {
            FillBgTilemapBufferRect(3, 17 + SUB_8138538_BASE_TILE_NUM, 13, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 33 + SUB_8138538_BASE_TILE_NUM, 13, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 48 + SUB_8138538_BASE_TILE_NUM, 14, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 64 + SUB_8138538_BASE_TILE_NUM, 14, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 2 + SUB_8138538_BASE_TILE_NUM, 15, 0, 4, 2, 0);
        }
        break;
    case PSS_PAGE_SKILLS:
        FillBgTilemapBufferRect(3, 49 + SUB_8138538_BASE_TILE_NUM, 13, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 65 + SUB_8138538_BASE_TILE_NUM, 13, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 14, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 14, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 17 + SUB_8138538_BASE_TILE_NUM, 15, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 33 + SUB_8138538_BASE_TILE_NUM, 15, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 16 + SUB_8138538_BASE_TILE_NUM, 16, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 32 + SUB_8138538_BASE_TILE_NUM, 16, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 18 + SUB_8138538_BASE_TILE_NUM, 17, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 34 + SUB_8138538_BASE_TILE_NUM, 17, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 21 + SUB_8138538_BASE_TILE_NUM, 18, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 37 + SUB_8138538_BASE_TILE_NUM, 18, 1, 1, 1, 0);
        break;
    case PSS_PAGE_MOVES:
        FillBgTilemapBufferRect(3, 49 + SUB_8138538_BASE_TILE_NUM, 13, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 65 + SUB_8138538_BASE_TILE_NUM, 13, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 14, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 14, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 49 + SUB_8138538_BASE_TILE_NUM, 15, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 65 + SUB_8138538_BASE_TILE_NUM, 15, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 16, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 16, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 17 + SUB_8138538_BASE_TILE_NUM, 17, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 33 + SUB_8138538_BASE_TILE_NUM, 17, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 48 + SUB_8138538_BASE_TILE_NUM, 18, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 64 + SUB_8138538_BASE_TILE_NUM, 18, 1, 1, 1, 0);
        break;
    case PSS_PAGE_MOVES_INFO:
        if (sMonSummaryScreen->mode == PSS_MODE_SELECT_MOVE)
        {
            FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 13, 0, 4, 1, 0);
            FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 13, 1, 4, 1, 0);
        }
        else
        {
            FillBgTilemapBufferRect(3, 49 + SUB_8138538_BASE_TILE_NUM, 13, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 65 + SUB_8138538_BASE_TILE_NUM, 13, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 14, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 14, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 49 + SUB_8138538_BASE_TILE_NUM, 15, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 65 + SUB_8138538_BASE_TILE_NUM, 15, 1, 1, 1, 0);
            FillBgTilemapBufferRect(3, 1 + SUB_8138538_BASE_TILE_NUM, 16, 0, 1, 1, 0);
            FillBgTilemapBufferRect(3, 19 + SUB_8138538_BASE_TILE_NUM, 16, 1, 1, 1, 0);
        }
        FillBgTilemapBufferRect(3, 50 + SUB_8138538_BASE_TILE_NUM, 17, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 66 + SUB_8138538_BASE_TILE_NUM, 17, 1, 1, 1, 0);
        FillBgTilemapBufferRect(3, 48 + SUB_8138538_BASE_TILE_NUM, 18, 0, 1, 1, 0);
        FillBgTilemapBufferRect(3, 64 + SUB_8138538_BASE_TILE_NUM, 18, 1, 1, 1, 0);
        break;
    }//think 49 65 1 19 are tiles for the 4 moves? x value changes each pair and y is based on x
    //and I know tiles are broken up so it could be top and bottom?
}//check move & move info patterns.

static void PokeSum_PrintMonTypeIcons(void)
{
    switch (sMonSummaryScreen->curPageIndex)
    {
    case PSS_PAGE_INFO:
        if (!sMonSummaryScreen->isEgg)
        {
            BlitMoveInfoIcon(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], sMonSummaryScreen->monTypes[0] + 1, 47, 35);

            if (sMonSummaryScreen->monTypes[0] != sMonSummaryScreen->monTypes[1])
                BlitMoveInfoIcon(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], sMonSummaryScreen->monTypes[1] + 1, 83, 35);
        }//think this is type 1 & 2
        break;
    case PSS_PAGE_SKILLS:
        break;
    case PSS_PAGE_MOVES:
        break;
    case PSS_PAGE_MOVES_INFO:   //removed these it was blocking text from displaying
        //FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], 0);
        /*BlitMoveInfoIcon(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], sMonSummaryScreen->monTypes[0] + 1, 0, 3);

        if (sMonSummaryScreen->monTypes[0] != sMonSummaryScreen->monTypes[1])   //if type 1 isn't type 2
            BlitMoveInfoIcon(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6], sMonSummaryScreen->monTypes[1] + 1, 36, 3);*/

        //PutWindowTilemap(sMonSummaryScreen->windowIds[POKESUM_WIN_MOVES_6]);
        break;
    }
}

u8 GetLastViewedMonIndex(void)
{
    return sLastViewedMonIndex;
}

u8 GetMoveSlotToReplace(void)
{
    return sMoveSwapCursorPos;
}

void SetPokemonSummaryScreenMode(u8 mode)
{
    sMonSummaryScreen->mode = mode;
}

static bool32 IsMultiBattlePartner(void)
{
    if (!IsUpdateLinkStateCBActive()
        && IsMultiBattle() == TRUE
        && gReceivedRemoteLinkPlayers == 1
        && (sLastViewedMonIndex >= 4 || sLastViewedMonIndex == 1))
        return TRUE;

    return FALSE;
}

static void BufferSelectedMonData(struct Pokemon * mon)
{
    if (!sMonSummaryScreen->isBoxMon)
    {
        struct Pokemon * partyMons = sMonSummaryScreen->monList.mons;
        *mon = partyMons[GetLastViewedMonIndex()];
    }
    else
    {
        struct BoxPokemon * boxMons = sMonSummaryScreen->monList.boxMons;
        BoxMonToMon(&boxMons[GetLastViewedMonIndex()], mon);
    }
}

#define SINGLE_BATTLE   (gMain.inBattle && singles)
#define DOUBLE_BATTLE   (gMain.inBattle && doubles)
#define TRIPLE_ROTATION (gMain.inBattle && rotation) //update for triple battle add for ability desc list too, need defines from below

//problem identified its these 2 functions that are the issue
//issue is this GetBattlerAtPosition(B_POSITION_PLAYER_LEFT) want to get this set in place of player party, want to use battle position that was plan
//issue was with switching, playerparty isn't changed how I thought, so current setup isn't as fool proof as I thought
//looking into potentiallt gBattlerPartyIndexes[] can be used
//mon = &gPlayerParty[gBattlerPartyIndexes[gActiveBattler]];  taht did it, seems to be working now, but need to check doubles as unsure if it is right,
//but it shold be
static u16 GetMonMoveBySlotId(struct Pokemon * mon, u8 moveSlot) 
{
    u16 move;
    u32 curr_personality, slot1_personality, slot2_personality, slot3_personality;
    u32 singles, doubles, rotation;
    curr_personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);
    slot1_personality = GetMonData(&gPlayerParty[gBattlerPartyIndexes[B_POSITION_PLAYER_LEFT]], MON_DATA_PERSONALITY);
    slot2_personality = GetMonData(&gPlayerParty[gBattlerPartyIndexes[B_POSITION_PLAYER_RIGHT]], MON_DATA_PERSONALITY);
    slot3_personality = GetMonData(&gPlayerParty[2], MON_DATA_PERSONALITY); //placehold value setup later
    
    singles = (!(gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_ROTATION | BATTLE_TYPE_TRIPLE | BATTLE_TYPE_TWO_OPPONENTS)));
    doubles = (gBattleTypeFlags & BATTLE_TYPE_DOUBLE);
    rotation = (gBattleTypeFlags & BATTLE_TYPE_ROTATION);

    switch (moveSlot)
    {
    case 0://move 1
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[0];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[0];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[0];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[0];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[0];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[0]; //fill in value, will need make new on efor triple/rotation instead of positionm right
        }
        else
            move = GetMonData(mon, MON_DATA_MOVE1);
        break;
    case 1://move 2
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[1];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[1];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[1];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[1];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[1];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[1];
        }
        else
            move = GetMonData(mon, MON_DATA_MOVE2);
        break;
    case 2://move 3
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[2];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[2];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[2];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[2];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[2];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[2];
        }
        else
            move = GetMonData(mon, MON_DATA_MOVE3);
        break;
    default://move 4
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[3];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[3];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[3];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].moves[3];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[3];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                move = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].moves[3];
        }
        else
            move = GetMonData(mon, MON_DATA_MOVE4);
    }

    return move;
}

static u16 GetMonPpByMoveSlot(struct Pokemon * mon, u8 moveSlot)
{
    u16 pp;
    u32 curr_personality, slot1_personality, slot2_personality, slot3_personality;
    u32 singles, doubles, rotation;
    curr_personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);
    slot1_personality = GetMonData(&gPlayerParty[gBattlerPartyIndexes[B_POSITION_PLAYER_LEFT]], MON_DATA_PERSONALITY); //works need test doubles value unsure of if right
    slot2_personality = GetMonData(&gPlayerParty[gBattlerPartyIndexes[B_POSITION_PLAYER_RIGHT]], MON_DATA_PERSONALITY);
    slot3_personality = GetMonData(&gPlayerParty[2], MON_DATA_PERSONALITY); //placehold value setup later
    
    singles = (!(gBattleTypeFlags & (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_ROTATION | BATTLE_TYPE_TWO_OPPONENTS)));
    doubles = (gBattleTypeFlags & BATTLE_TYPE_DOUBLE);
    rotation = (gBattleTypeFlags & BATTLE_TYPE_ROTATION);

    switch (moveSlot)
    {
    case 0://move 1
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[0];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[0];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[0];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[0];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[0];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[0];
        }
        else
            pp = GetMonData(mon, MON_DATA_PP1);
        break;
    case 1://move 2
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[1];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[1];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[1];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[1];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[1];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[1];
        }
        else
            pp = GetMonData(mon, MON_DATA_PP2);
        break;
    case 2://move 3
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[2];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[2];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[2];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[2];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[2];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[2];
        }
        else
            pp = GetMonData(mon, MON_DATA_PP3);
        break;
    default://move 4
        if (SINGLE_BATTLE && (curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
        {
            pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[3];
        }
        else if (DOUBLE_BATTLE)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[3];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[3];
        }
        else if (TRIPLE_ROTATION)
        {
            if  ((curr_personality == slot1_personality)
            && GetMonData(&gPlayerParty[0], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)].pp[3];

            if  ((curr_personality == slot2_personality)
            && GetMonData(&gPlayerParty[1], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[3];

            if  ((curr_personality == slot3_personality)
            && GetMonData(&gPlayerParty[2], MON_DATA_HP))
                pp = gBattleMons[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)].pp[3];
        }
        else
            pp = GetMonData(mon, MON_DATA_PP4);
    }
    return pp;
}

static u8 StatusToAilment(u32 status)
{
    if (GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP) == 0)
        return AILMENT_FNT;

    if ((status & STATUS1_PSN_ANY) != 0)
        return AILMENT_PSN;

    if ((status & STATUS1_PARALYSIS) != 0)
        return AILMENT_PRZ;

    if ((status & STATUS1_SLEEP) != 0)
        return AILMENT_SLP;

    if ((status & STATUS1_FREEZE) != 0)
        return AILMENT_FRZ;

    if ((status & STATUS1_BURN) != 0)
        return AILMENT_BRN;
    
    if ((status & STATUS1_SPIRIT_LOCK) != 0)
        return AILMENT_SPRT;

    if (CheckPartyPokerus(&sMonSummaryScreen->currentMon, 0)) //important very !!
        return AILMENT_PKRS; // !! if this function can check and return/display both status1 ailment and pokerus ailment
    //then multi status should be pheasible!!!
    return AILMENT_NONE;
}//well pokerus and status 1 are stored differently but I still believe its possible

static void Task_HandleInput_SelectMove(u8 id)
{
    u8 i;

    switch (sMonSummaryScreen->selectMoveInputHandlerState)
    {
    case 0:
        if (MenuHelpers_CallLinkSomething() == TRUE || sub_800B270() == TRUE)  //sub function in link.c
            return;

        if (JOY_NEW(DPAD_UP))
        {
            if (sMoveSelectionCursorPos > 0)
            {
                sMonSummaryScreen->selectMoveInputHandlerState = 2;
                PlaySE(SE_SELECT);

                for (i = sMoveSelectionCursorPos; i > 0; i--)
                    if (sMonSummaryScreen->moveIds[i - 1] != 0)
                    {
                        PlaySE(SE_SELECT);
                        sMoveSelectionCursorPos = i - 1;
                        return;
                    }
            }
            else
            {
                sMoveSelectionCursorPos = 4;
                sMonSummaryScreen->selectMoveInputHandlerState = 2;
                PlaySE(SE_SELECT);

                if (sMonSummaryScreen->isSwappingMoves == TRUE)
                    for (i = sMoveSelectionCursorPos; i > 0; i--)
                        if (sMonSummaryScreen->moveIds[i - 1] != 0)
                        {
                            PlaySE(SE_SELECT);
                            sMoveSelectionCursorPos = i - 1;
                            return;
                        }
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (sMoveSelectionCursorPos < 4)
            {
                u8 v0 = 4;

                sMonSummaryScreen->selectMoveInputHandlerState = 2;

                if (sMonSummaryScreen->isSwappingMoves == TRUE)
                {
                    if (sMoveSelectionCursorPos == 5 - 2)
                    {
                        sMoveSelectionCursorPos = 0;
                        sMonSummaryScreen->selectMoveInputHandlerState = 2;
                        PlaySE(SE_SELECT);
                        return;
                    }
                    v0--;
                }

                for (i = sMoveSelectionCursorPos; i < v0; i++)
                    if (sMonSummaryScreen->moveIds[i + 1] != 0)
                    {
                        PlaySE(SE_SELECT);
                        sMoveSelectionCursorPos = i + 1;
                        return;
                    }

                if (!sMonSummaryScreen->isSwappingMoves)
                {
                    PlaySE(SE_SELECT);
                    sMoveSelectionCursorPos = i;
                }
                else
                {
                    PlaySE(SE_SELECT);
                    sMoveSelectionCursorPos = 0;
                }

                return;
            }
            else if (sMoveSelectionCursorPos == 4)
            {
                sMoveSelectionCursorPos = 0;
                sMonSummaryScreen->selectMoveInputHandlerState = 2;
                PlaySE(SE_SELECT);
                return;
            }
        }
        else if (JOY_NEW(A_BUTTON))
        {
            PlaySE(SE_SELECT);
            if (sMoveSelectionCursorPos == 4)
            {
                sMoveSelectionCursorPos = 0;
                sMoveSwapCursorPos = 0;
                sMonSummaryScreen->isSwappingMoves = FALSE;
                ShoworHideMoveSelectionCursor(1);
                sMonSummaryScreen->pageFlipDirection = 0;
                PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
                sMonSummaryScreen->curPageIndex--;
                sMonSummaryScreen->selectMoveInputHandlerState = 1;
                return;
            }

            if (sMonSummaryScreen->isSwappingMoves != TRUE)
            {
                if (sMonSummaryScreen->isEnemyParty == FALSE
                    && gMain.inBattle == 0
                    && gReceivedRemoteLinkPlayers == 0)
                {
                    sMoveSwapCursorPos = sMoveSelectionCursorPos;
                    sMonSummaryScreen->isSwappingMoves = TRUE;
                }
                return;
            }
            else
            {
                sMonSummaryScreen->isSwappingMoves = FALSE;

                if (sMoveSelectionCursorPos == sMoveSwapCursorPos)
                    return;

                if (sMonSummaryScreen->isBoxMon == FALSE)
                    SwapMonMoveSlots();
                else
                    SwapBoxMonMoveSlots();

                UpdateCurrentMonBufferFromPartyOrBox(&sMonSummaryScreen->currentMon);
                BufferMonMoves();
                sMonSummaryScreen->selectMoveInputHandlerState = 2;
                return;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            if (sMonSummaryScreen->isSwappingMoves == TRUE)
            {
                sMoveSwapCursorPos = sMoveSelectionCursorPos;
                sMonSummaryScreen->isSwappingMoves = FALSE;
                return;
            }

            if (sMoveSelectionCursorPos == 4)
            {
                sMoveSelectionCursorPos = 0;
                sMoveSwapCursorPos = 0;
            }

            ShoworHideMoveSelectionCursor(TRUE);
            sMonSummaryScreen->pageFlipDirection = 0;
            PokeSum_RemoveWindows(sMonSummaryScreen->curPageIndex);
            sMonSummaryScreen->curPageIndex--;
            sMonSummaryScreen->selectMoveInputHandlerState = 1;
        }
        break;
    case 1:
        gTasks[sMonSummaryScreen->inputHandlerTaskId].func = Task_BackOutOfSelectMove;
        sMonSummaryScreen->selectMoveInputHandlerState = 0;
        break;
    case 2:
        PokeSum_PrintRightPaneText();
        PokeSum_PrintBottomPaneText();
        PokeSum_PrintAbilityDataOrMoveTypes();
        sMonSummaryScreen->selectMoveInputHandlerState = 3;
        break;
    case 3:
        if (MenuHelpers_CallLinkSomething() == TRUE || sub_800B270() == TRUE)
            return;

        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(3);
        sMonSummaryScreen->selectMoveInputHandlerState = 0;
        break;
    default:
        break;
    }
}

//vsonic here would be setup for move swap based on move length
#define MOVE_SWAP_FUNCTION
static void SwapMonMoveSlots(void)
{
    struct Pokemon * partyMons;
    struct Pokemon * mon;

    u16 move1, move2;
    u8 pp1, pp2;
    u8 allMovesPPBonuses;
    u8 move1ppBonus, move2ppBonus;

    partyMons = sMonSummaryScreen->monList.mons;
    mon = &partyMons[GetLastViewedMonIndex()];

    move1 = GetMonData(mon, MON_DATA_MOVE1 + sMoveSelectionCursorPos);
    move2 = GetMonData(mon, MON_DATA_MOVE1 + sMoveSwapCursorPos);

    pp1 = GetMonData(mon, MON_DATA_PP1 + sMoveSelectionCursorPos);
    pp2 = GetMonData(mon, MON_DATA_PP1 + sMoveSwapCursorPos);

    allMovesPPBonuses = GetMonData(mon, MON_DATA_PP_BONUSES);

    move1ppBonus = (allMovesPPBonuses & gPPUpGetMask[sMoveSelectionCursorPos]) >> (sMoveSelectionCursorPos * 2);
    move2ppBonus = (allMovesPPBonuses & gPPUpGetMask[sMoveSwapCursorPos]) >> (sMoveSwapCursorPos * 2);

    allMovesPPBonuses &= ~gPPUpGetMask[sMoveSelectionCursorPos];
    allMovesPPBonuses &= ~gPPUpGetMask[sMoveSwapCursorPos];
    allMovesPPBonuses |= (move1ppBonus << (sMoveSwapCursorPos * 2)) + (move2ppBonus << (sMoveSelectionCursorPos * 2));

    SetMonData(mon, MON_DATA_MOVE1 + sMoveSelectionCursorPos, (u8 *)&move2);
    SetMonData(mon, MON_DATA_MOVE1 + sMoveSwapCursorPos, (u8 *)&move1);
    SetMonData(mon, MON_DATA_PP1 + sMoveSelectionCursorPos, &pp2);
    SetMonData(mon, MON_DATA_PP1 + sMoveSwapCursorPos, &pp1);
    SetMonData(mon, MON_DATA_PP_BONUSES, &allMovesPPBonuses);
}

static void SwapBoxMonMoveSlots(void)
{
    struct BoxPokemon * boxMons;
    struct BoxPokemon * boxMon;

    u16 move1, move2;
    u8 pp1, pp2;
    u8 allMovesPPBonuses;
    u8 move1ppBonus, move2ppBonus;

    boxMons = sMonSummaryScreen->monList.boxMons;
    boxMon = &boxMons[GetLastViewedMonIndex()];

    move1 = GetBoxMonData(boxMon, MON_DATA_MOVE1 + sMoveSelectionCursorPos);
    move2 = GetBoxMonData(boxMon, MON_DATA_MOVE1 + sMoveSwapCursorPos);

    pp1 = GetBoxMonData(boxMon, MON_DATA_PP1 + sMoveSelectionCursorPos);
    pp2 = GetBoxMonData(boxMon, MON_DATA_PP1 + sMoveSwapCursorPos);

    allMovesPPBonuses = GetBoxMonData(boxMon, MON_DATA_PP_BONUSES);

    move1ppBonus = (allMovesPPBonuses & gPPUpGetMask[sMoveSelectionCursorPos]) >> (sMoveSelectionCursorPos * 2);
    move2ppBonus = (allMovesPPBonuses & gPPUpGetMask[sMoveSwapCursorPos]) >> (sMoveSwapCursorPos * 2);

    allMovesPPBonuses &= ~gPPUpGetMask[sMoveSelectionCursorPos];
    allMovesPPBonuses &= ~gPPUpGetMask[sMoveSwapCursorPos];
    allMovesPPBonuses |= (move1ppBonus << (sMoveSwapCursorPos * 2)) + (move2ppBonus << (sMoveSelectionCursorPos * 2));

    SetBoxMonData(boxMon, MON_DATA_MOVE1 + sMoveSelectionCursorPos, (u8 *)&move2);
    SetBoxMonData(boxMon, MON_DATA_MOVE1 + sMoveSwapCursorPos, (u8 *)&move1);
    SetBoxMonData(boxMon, MON_DATA_PP1 + sMoveSelectionCursorPos, &pp2);
    SetBoxMonData(boxMon, MON_DATA_PP1 + sMoveSwapCursorPos, &pp1);
    SetBoxMonData(boxMon, MON_DATA_PP_BONUSES, &allMovesPPBonuses);
}

static void UpdateCurrentMonBufferFromPartyOrBox(struct Pokemon * mon)
{
    if (!sMonSummaryScreen->isBoxMon)
    {
        struct Pokemon * partyMons;
        partyMons = sMonSummaryScreen->monList.mons;
        *mon = partyMons[GetLastViewedMonIndex()];
    }
    else
    {
        struct BoxPokemon * boxMons;
        boxMons = sMonSummaryScreen->monList.boxMons;
        BoxMonToMon(&boxMons[GetLastViewedMonIndex()], mon);
    }
}

static u8 PokeSum_CanForgetSelectedMove(void)
{
    u16 move;

    move = GetMonMoveBySlotId(&sMonSummaryScreen->currentMon, sMoveSelectionCursorPos);

    if (IsMoveHm(move) == TRUE && sMonSummaryScreen->mode != PSS_MODE_FORGET_MOVE)
        return TRUE; //thought I caught all these but extra flip to make hms forgettable

    return TRUE;
}

static void Task_InputHandler_SelectOrForgetMove(u8 taskId)
{
    u8 i;

    switch (sMonSummaryScreen->selectMoveInputHandlerState)
    {
    case 0://replaced with upgraded pallete fade constant hope works
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0);
        sMonSummaryScreen->selectMoveInputHandlerState++;
        break;
    case 1:
        if (!gPaletteFade.active)
        {
            PokeSum_TryPlayMonCry();
            sMonSummaryScreen->selectMoveInputHandlerState++;
        }
        break;
    case 2:
        if (JOY_NEW(DPAD_UP))
        {
            if (sMoveSelectionCursorPos > 0)
            {
                sMonSummaryScreen->selectMoveInputHandlerState = 3;
                PlaySE(SE_SELECT);
                for (i = sMoveSelectionCursorPos; i > 0; i--)
                    if (sMonSummaryScreen->moveIds[i - 1] != 0)
                    {
                        PlaySE(SE_SELECT);
                        sMoveSelectionCursorPos = i - 1;
                        return;
                    }
            }
            else
            {
                sMoveSelectionCursorPos = 4;
                sMonSummaryScreen->selectMoveInputHandlerState = 3;
                PlaySE(SE_SELECT);
                return;
            }
        }
        else if (JOY_NEW(DPAD_DOWN))
        {
            if (sMoveSelectionCursorPos < 4)
            {
                u8 v0 = 4;

                sMonSummaryScreen->selectMoveInputHandlerState = 3;

                if (sMonSummaryScreen->isSwappingMoves == TRUE)
                    v0--;

                for (i = sMoveSelectionCursorPos; i < v0; i++)
                    if (sMonSummaryScreen->moveIds[i + 1] != 0)
                    {
                        PlaySE(SE_SELECT);
                        sMoveSelectionCursorPos = i + 1;
                        return;
                    }

                if (!sMonSummaryScreen->isSwappingMoves)
                {
                    PlaySE(SE_SELECT);
                    sMoveSelectionCursorPos = i;
                }

                return;
            }
            else if (sMoveSelectionCursorPos == 4)
            {
                sMoveSelectionCursorPos = 0;
                sMonSummaryScreen->selectMoveInputHandlerState = 3;
                PlaySE(SE_SELECT);
                return;
            }
        }
        else if (JOY_NEW(A_BUTTON))
        {
            if (PokeSum_CanForgetSelectedMove() == TRUE || sMoveSelectionCursorPos == 4)
            {
                PlaySE(SE_SELECT);
                sMoveSwapCursorPos = sMoveSelectionCursorPos;
                gSpecialVar_0x8005 = sMoveSwapCursorPos;
                sMonSummaryScreen->selectMoveInputHandlerState = 6;
            }
            else
            {
                PlaySE(SE_FAILURE);
                sMonSummaryScreen->selectMoveInputHandlerState = 5;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sMoveSwapCursorPos = 4;
            gSpecialVar_0x8005 = (u16)sMoveSwapCursorPos;
            sMonSummaryScreen->selectMoveInputHandlerState = 6;
        }
        break;
    case 3:
        PokeSum_PrintRightPaneText();
        PokeSum_PrintBottomPaneText();
        PokeSum_PrintAbilityDataOrMoveTypes();
        sMonSummaryScreen->selectMoveInputHandlerState = 4;
        break;
    case 4:
        if (MenuHelpers_CallLinkSomething() == TRUE || sub_800B270() == TRUE)
            return;

        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(3);
        sMonSummaryScreen->selectMoveInputHandlerState = 2;
        break;
    case 5:
        FillWindowPixelBuffer(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 0);
        AddTextPrinterParameterized4(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], FONT_NORMAL,
                                     7, 42,
                                     0, 0,
                                     sLevelNickTextColors[0], TEXT_SKIP_DRAW,
                                     gUnknown_8419CB9);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 2);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(3);
        sMonSummaryScreen->selectMoveInputHandlerState = 2;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, 0);
        sMonSummaryScreen->selectMoveInputHandlerState++;
        break;
    default:
        if (!gPaletteFade.active)
            Task_DestroyResourcesOnExit(taskId);
        break;
    }
}

static void SpriteCB_PokeSum_MonPicSprite(struct Sprite * sprite)
{
    if (sMonSummaryScreen->numMonPicBounces >= 2)
        return;

    if (sMonPicBounceState->initDelay++ >= 2)
    {
        u8 v0;

        switch (sMonPicBounceState->vigor)
        {
        case 0:
            sprite->pos1.y += sMonPicBounceYDelta_Under60[sMonPicBounceState->animFrame++];
            v0 = NELEMS(sMonPicBounceYDelta_Under60);
            break;
        case 1:
            sprite->pos1.y += sMonPicBounceYDelta_60to80[sMonPicBounceState->animFrame++];
            v0 = NELEMS(sMonPicBounceYDelta_60to80);
            break;
        case 2:
            sprite->pos1.y += sMonPicBounceYDelta_80to99[sMonPicBounceState->animFrame++];
            v0 = NELEMS(sMonPicBounceYDelta_80to99);
            break;
        case 3:
        default:
            sprite->pos1.y += sMonPicBounceYDelta_Full[sMonPicBounceState->animFrame++];
            v0 = NELEMS(sMonPicBounceYDelta_Full);
            break;
        }

        if (sMonPicBounceState->animFrame >= v0)
        {
            sMonPicBounceState->animFrame = 0;
            sMonSummaryScreen->numMonPicBounces++;
        }

        sMonPicBounceState->initDelay = 0;
    }
}

static void SpriteCB_PokeSum_EggPicShake(struct Sprite * sprite)//sprite pos1 was changed more than I feel comfortable dealing w right now
{
    if (sMonSummaryScreen->numMonPicBounces >= 2)
        return;

    switch (sMonPicBounceState->vigor)
    {
    case 0:
    default:
        if (sMonPicBounceState->initDelay++ >= 120)
        {
            sprite->pos1.x += sEggPicShakeXDelta_ItWillTakeSomeTime[sMonPicBounceState->animFrame];
            if (++sMonPicBounceState->animFrame >= NELEMS(sEggPicShakeXDelta_ItWillTakeSomeTime))
            {
                sMonPicBounceState->animFrame = 0;
                sMonPicBounceState->initDelay = 0;
                sMonSummaryScreen->numMonPicBounces++;
            }
        }
        break;
    case 1:
        if (sMonPicBounceState->initDelay++ >= 90)
        {
            sprite->pos1.x += sEggPicShakeXDelta_OccasionallyMoves[sMonPicBounceState->animFrame];
            if (++sMonPicBounceState->animFrame >= NELEMS(sEggPicShakeXDelta_OccasionallyMoves))
            {
                sMonPicBounceState->animFrame = 0;
                sMonPicBounceState->initDelay = 0;
                sMonSummaryScreen->numMonPicBounces++;
            }
        }
        break;
    case 2:
        if (sMonPicBounceState->initDelay++ >= 60)
        {
            sprite->pos1.x += sEggPicShakeXDelta_AlmostReadyToHatch[sMonPicBounceState->animFrame];
            if (++sMonPicBounceState->animFrame >= NELEMS(sEggPicShakeXDelta_AlmostReadyToHatch))
            {
                sMonPicBounceState->animFrame = 0;
                sMonPicBounceState->initDelay = 0;
                sMonSummaryScreen->numMonPicBounces++;
            }
        }
        break;
    }
}

static void SpriteCB_MonPicDummy(struct Sprite * sprite)
{
}

static void PokeSum_CreateMonPicSprite(void)
{
    u16 spriteId;
    u16 species;
    u32 personality;
    u32 trainerId;

    sMonPicBounceState = AllocZeroed(sizeof(struct MonPicBounceState));

    species = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2);
    personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);
    trainerId = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_OT_ID);

    if (sMonSummaryScreen->savedCallback == CB2_ReturnToTradeMenuFromSummary)
    {
        if (sMonSummaryScreen->isEnemyParty == TRUE)
            spriteId = CreateMonPicSprite(species, trainerId, personality, TRUE, 60, 65, 12, 0xffff, TRUE);
        else
            spriteId = CreateMonPicSprite_HandleDeoxys(species, trainerId, personality, TRUE, 60, 65, 12, 0xffff);
    }
    else
    {
        if (ShouldIgnoreDeoxysForm(DEOXYS_CHECK_TRADE_MAIN, sLastViewedMonIndex))
            spriteId = CreateMonPicSprite(species, trainerId, personality, TRUE, 60, 65, 12, 0xffff, TRUE);
        else
            spriteId = CreateMonPicSprite_HandleDeoxys(species, trainerId, personality, TRUE, 60, 65, 12, 0xffff);
    }//do something with this later to make sure I can change forms in game

    FreeSpriteOamMatrix(&gSprites[spriteId]);

    if (!IsPokeSpriteNotFlipped(species))
        gSprites[spriteId].hFlip = TRUE;
    else
        gSprites[spriteId].hFlip = FALSE;

    sMonSummaryScreen->monPicSpriteId = spriteId;

    PokeSum_ShowOrHideMonPicSprite(TRUE);
    PokeSum_SetMonPicSpriteCallback(spriteId);
}

static void PokeSum_SetMonPicSpriteCallback(u16 spriteId)
{
    u16 curHp;
    u16 maxHp;

    sMonSummaryScreen->numMonPicBounces = 0;

    if (sMonSummaryScreen->isEgg == TRUE)
    {
        u8 friendship = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_FRIENDSHIP);

        if (friendship <= 5)
            sMonPicBounceState->vigor = 2;
        else
        {
            if (friendship <= 10)
                sMonPicBounceState->vigor = 1;
            else if (friendship <= 40)
                sMonPicBounceState->vigor = 0;
        }

        gSprites[spriteId].callback = SpriteCB_PokeSum_EggPicShake;
        return;
    }

    if (sMonSummaryScreen->curMonStatusAilment != AILMENT_NONE && sMonSummaryScreen->curMonStatusAilment != AILMENT_PKRS)
    {
        if (sMonSummaryScreen->curMonStatusAilment == AILMENT_FNT)
            return;

        gSprites[spriteId].callback = SpriteCB_MonPicDummy;
        return;
    }

    curHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP);
    maxHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MAX_HP);

    if (curHp == maxHp)
        sMonPicBounceState->vigor = 3;
    else if (maxHp * 0.8 <= curHp)
        sMonPicBounceState->vigor = 2;
    else if (maxHp * 0.6 <= curHp)
        sMonPicBounceState->vigor = 1;
    else
        sMonPicBounceState->vigor = 0;

    gSprites[spriteId].callback = SpriteCB_PokeSum_MonPicSprite;
}//changes how mon appears in party screen (I think) based on hp
//can prob use this for nuzlocke feature for when mon dies

static void PokeSum_ShowOrHideMonPicSprite(u8 invisible)
{
    gSprites[sMonSummaryScreen->monPicSpriteId].invisible = invisible;
}

static void PokeSum_DestroyMonPicSprite(void)
{
    FreeAndDestroyMonPicSprite(sMonSummaryScreen->monPicSpriteId);
    FREE_AND_SET_NULL(sMonPicBounceState);
}

void PokeballIcon_CaughtIn(u8 y) //figure out how to use this, need put in pokemonsummary screen but make non static
{
    u16 ballItemId; //forgot sum screen took pokeball you caught them in, plan use this  for pokedex
    u8 ballId; //what I plan to do make function that defaults it to pokeball(id 0) but make it invisible until caught
    //and so I don't need to make a new storage value make function call in caught functio, that checks pokeball of caught mon
//if the mon hasn't been caught before, then replaces the pokeball with the ball you caught it in and makes it visible)

    ballItemId = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_POKEBALL); //change current mon to identifier 


    ballId = ItemIdToBallId(ballItemId);
    LoadBallGfx(ballId);
    //need put logic here to explicitlyu put it on the correct pokedex window
    //sPokedexScreenData->numericalOrderWindowId

    /*sMonSummaryScreen->ballIconSpriteId =*/ CreateSprite(&gBallSpriteTemplates[ballId], 0x28, y, 0);
    //gSprites[gBallSpriteTemplates[ballId]].callback = SpriteCallbackDummy;  //sMonSummaryScreen->ballIconSpriteId
    //gSprites[gBallSpriteTemplates[ballId]].oam.priority = 0;//value here is meant as stand in for index/id but can use gBallSpriteTemplates[ballId] for that
    //inside isn't right need pass to other value or variable to work, dereferrence?

    ShowOrHideBallIconObj(TRUE);
}

static void CreateBallIconObj(void)
{
    u16 ballItemId;
    u8 ballId;

    if (!sMonSummaryScreen->isEgg)
        ballItemId = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_POKEBALL);
    else
        ballItemId = 0;

    ballId = ItemIdToBallId(ballItemId);
    LoadBallGfx(ballId);

    sMonSummaryScreen->ballIconSpriteId = CreateSprite(&gBallSpriteTemplates[ballId], 106, 88, 0);
    gSprites[sMonSummaryScreen->ballIconSpriteId].callback = SpriteCallbackDummy;
    gSprites[sMonSummaryScreen->ballIconSpriteId].oam.priority = 0;

    ShowOrHideBallIconObj(TRUE);
}

static void ShowOrHideBallIconObj(u8 invisible)
{
    gSprites[sMonSummaryScreen->ballIconSpriteId].invisible = invisible;
}

static void DestroyBallIconObj(void)
{
    // Redundant, as DestroySpriteAndFreeResources could've been used.
    DestroySpriteAndFreeResources2(&gSprites[sMonSummaryScreen->ballIconSpriteId]);
}

static void PokeSum_CreateMonIconSprite(void)
{
    u16 species;
    u32 personality;

    species = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2);
    personality = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_PERSONALITY);

    SafeLoadMonIconPalette(species);

    if (sMonSummaryScreen->savedCallback == CB2_ReturnToTradeMenuFromSummary) //trade/link stuff
    {
        if (sMonSummaryScreen->isEnemyParty == TRUE)
            sMonSummaryScreen->monIconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, 24, 32, 0, personality, 0);
        else
            sMonSummaryScreen->monIconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, 24, 32, 0, personality, 1);
    }
    else
    {
        if (ShouldIgnoreDeoxysForm(DEOXYS_CHECK_TRADE_MAIN, sLastViewedMonIndex))
            sMonSummaryScreen->monIconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, 24, 32, 0, personality, 0);
        else
            sMonSummaryScreen->monIconSpriteId = CreateMonIcon(species, SpriteCallbackDummy, 18, 36, 0, personality, 1);
    }//last line is exactly what I need to move sprite coordinate
    //vsonic IMPORTANT
    if (!IsPokeSpriteNotFlipped(species))
        gSprites[sMonSummaryScreen->monIconSpriteId].hFlip = TRUE;
    else
        gSprites[sMonSummaryScreen->monIconSpriteId].hFlip = FALSE;

    PokeSum_ShowOrHideMonIconSprite(TRUE);
}

static void PokeSum_ShowOrHideMonIconSprite(u8 invisible)
{
    gSprites[sMonSummaryScreen->monIconSpriteId].invisible = invisible;
}

static void PokeSum_DestroyMonIconSprite(void)
{
    u16 species;
    species = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2);
    SafeFreeMonIconPalette(species);
    DestroyMonIcon(&gSprites[sMonSummaryScreen->monIconSpriteId]);
}

static void CreateMoveSelectionCursorObjs(u16 tileTag, u16 palTag)
{
    u8 i;
    u8 spriteId;
    void * gfxBufferPtrs[2];
    gfxBufferPtrs[0] = AllocZeroed(0x20 * 64);
    gfxBufferPtrs[1] = AllocZeroed(0x20 * 64);

    sMoveSelectionCursorObjs[0] = AllocZeroed(sizeof(struct MoveSelectionCursor));
    sMoveSelectionCursorObjs[1] = AllocZeroed(sizeof(struct MoveSelectionCursor));
    sMoveSelectionCursorObjs[2] = AllocZeroed(sizeof(struct MoveSelectionCursor));
    sMoveSelectionCursorObjs[3] = AllocZeroed(sizeof(struct MoveSelectionCursor));

    LZ77UnCompWram(sMoveSelectionCursorTiles_Left, gfxBufferPtrs[0]);
    LZ77UnCompWram(sMoveSelectionCursorTiles_Right, gfxBufferPtrs[1]);

    for (i = 0; i < 4; i++)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtrs[i % 2],
            .size = 0x20 * 64,
            .tag = tileTag + i
        };

        struct SpritePalette palette = {.data = sMoveSelectionCursorPals, .tag = palTag};
        struct SpriteTemplate template = {
            .tileTag = tileTag + i,
            .paletteTag = palTag,
            .oam = &sMoveSelectionCursorOamData,
            .anims = sMoveSelectionCursorOamAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCB_MoveSelectionCursor,
        };

        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette);

        spriteId = CreateSprite(&template, 64 * (i % 2) + 152, sMoveSelectionCursorPos * 28 + 34, i % 2);
        sMoveSelectionCursorObjs[i]->sprite = &gSprites[spriteId];
        sMoveSelectionCursorObjs[i]->whichSprite = i;
        sMoveSelectionCursorObjs[i]->tileTag = tileTag + i;
        sMoveSelectionCursorObjs[i]->palTag = palTag;
        sMoveSelectionCursorObjs[i]->sprite->subpriority = i;

        if (i > 1)
            StartSpriteAnim(sMoveSelectionCursorObjs[i]->sprite, 1);
    }

    ShoworHideMoveSelectionCursor(TRUE);

    FREE_AND_SET_NULL_IF_SET(gfxBufferPtrs[0]);
    FREE_AND_SET_NULL_IF_SET(gfxBufferPtrs[1]);
}

static void ShoworHideMoveSelectionCursor(u8 invisible)
{
    u8 i;
    for (i = 0; i < 4; i++)
        sMoveSelectionCursorObjs[i]->sprite->invisible = invisible;
}

static void SpriteCB_MoveSelectionCursor(struct Sprite * sprite)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (sMonSummaryScreen->isSwappingMoves == TRUE && i > 1)
            continue;

        sMoveSelectionCursorObjs[i]->sprite->pos1.y = sMoveSelectionCursorPos * 28 + 34;
    }

    if (sMonSummaryScreen->isSwappingMoves != TRUE)
    {
        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
        {
            sMoveSelectionCursorObjs[0]->sprite->invisible = FALSE;
            sMoveSelectionCursorObjs[1]->sprite->invisible = FALSE;
        }
        return;
    }

    for (i = 0; i < 2; i++)
    {
        sprite = sMoveSelectionCursorObjs[i]->sprite;
        sprite->data[0]++;

        if (sprite->invisible)
        {
            if (sprite->data[0] > 60)
            {
                sprite->invisible = FALSE;
                sprite->data[0] = 0;
            }
        }
        else if (sprite->data[0] > 60)
        {
            sprite->invisible = TRUE;
            sprite->data[0] = 0;
        }
    }
}

static void DestroyMoveSelectionCursorObjs(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (sMoveSelectionCursorObjs[i]->sprite != NULL)
            DestroySpriteAndFreeResources(sMoveSelectionCursorObjs[i]->sprite);

        FREE_AND_SET_NULL_IF_SET(sMoveSelectionCursorObjs[i]);
    }
}

static void CreateMonStatusIconObj(u16 tileTag, u16 palTag) //important very for new status
{
    u16 spriteId;
    void * gfxBufferPtr;

    sStatusIcon = AllocZeroed(sizeof(struct MonStatusIconObj));
    gfxBufferPtr = AllocZeroed(0x20 * 32);

    LZ77UnCompWram(gPokeSummary_StatusAilmentIconTiles, gfxBufferPtr);

    if (sStatusIcon != NULL)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtr,
            .size = 0x20 * 32,
            .tag = tileTag
        };

        struct SpritePalette palette = {.data = gPokeSummary_StatusAilmentIconPals, .tag = palTag};
        struct SpriteTemplate template = {
            .tileTag = tileTag,
            .paletteTag = palTag,
            .oam = &sStatusAilmentIconOamData,
            .anims = sStatusAilmentIconAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCallbackDummy,
        };

        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette);

        spriteId = CreateSprite(&template, 0, 0, 0);
        sStatusIcon->sprite = &gSprites[spriteId];
        sStatusIcon->tileTag = tileTag;
        sStatusIcon->palTag = palTag;
    }

    ShowOrHideStatusIcon(TRUE);
    UpdateMonStatusIconObj();
    FREE_AND_SET_NULL_IF_SET(gfxBufferPtr);
}

static void DestroyMonStatusIconObj(void)
{
    if (sStatusIcon->sprite != NULL)
        DestroySpriteAndFreeResources(sStatusIcon->sprite);

    FREE_AND_SET_NULL_IF_SET(sStatusIcon);
}

static void UpdateMonStatusIconObj(void)//important
{
    sMonSummaryScreen->curMonStatusAilment = StatusToAilment(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_STATUS));

    if (sMonSummaryScreen->curMonStatusAilment == AILMENT_NONE)
    {
        ShowOrHideStatusIcon(1); //will need to havea defautl arrangement of invisible status icons
        return; // check the order of list and swap order and then make visible as statuses are applied

    } //I'm thinking work backwards like evo table, order based on turn order status applied in, FIFO style,
      // next check that the status is still in affect, if it isn't, swap it to the bottom of the stack and make invisible

    StartSpriteAnim(sStatusIcon->sprite, sMonSummaryScreen->curMonStatusAilment - 1);
    ShowOrHideStatusIcon(0);
}

static void ShowOrHideStatusIcon(u8 invisible) //important status icon visibility and position
{
    if (sMonSummaryScreen->curMonStatusAilment == AILMENT_NONE || sMonSummaryScreen->isEgg)
        sStatusIcon->sprite->invisible = TRUE; //believe this just means make ailment none sprite invisible,
    else
        sStatusIcon->sprite->invisible = invisible;

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
    {
        if (sStatusIcon->sprite->pos1.y != 45)
        {
            sStatusIcon->sprite->pos1.x = 16; //important this unknown and data may be for position of status icon when on move page.
            sStatusIcon->sprite->pos1.y = 45;
            return;
        }
    }
    else if (sStatusIcon->sprite->pos1.y != 38) //and this may be for every other windows.
    {
        sStatusIcon->sprite->pos1.x = 16;
        sStatusIcon->sprite->pos1.y = 38;
        return;
    }
}

static void CreateHpBarObjs(u16 tileTag, u16 palTag)
{
    u8 i;
    u8 spriteId;
    void * gfxBufferPtr;
    u32 curHp;
    u32 maxHp;
    u8 hpBarPalTagOffset = 0;

    sHpBarObjs = AllocZeroed(sizeof(struct HpBarObjs));
    gfxBufferPtr = AllocZeroed(0x20 * 12);
    LZ77UnCompWram(gPokeSummary_HpBarTiles, gfxBufferPtr);

    curHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP);
    maxHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MAX_HP);

    if (maxHp / 4 > curHp)
        hpBarPalTagOffset = 2;
    else if (maxHp / 2 > curHp)
        hpBarPalTagOffset = 1;

    if (gfxBufferPtr != NULL)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtr,
            .size = 0x20 * 12,
            .tag = tileTag
        };

        struct SpritePalette palette1 = {.data = sHpBarPals[0], .tag = palTag};
        struct SpritePalette palette2 = {.data = sHpBarPals[1], .tag = palTag + 1};
        struct SpritePalette palette3 = {.data = sHpBarPals[2], .tag = palTag + 2};

        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette1);
        LoadSpritePalette(&palette2);
        LoadSpritePalette(&palette3);
    }

    for (i = 0; i < 9; i++)
    {
        struct SpriteTemplate template = {
            .tileTag = tileTag,
            .paletteTag = palTag + hpBarPalTagOffset,
            .oam = &sHpOrExpBarOamData,
            .anims = sHpOrExpBarAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCallbackDummy,
        };

        sHpBarObjs->xpos[i] = i * 8 + 172;
        spriteId = CreateSprite(&template, sHpBarObjs->xpos[i], 36, 0);
        sHpBarObjs->sprites[i] = &gSprites[spriteId];
        sHpBarObjs->sprites[i]->invisible = FALSE;
        sHpBarObjs->sprites[i]->oam.priority = 2;
        sHpBarObjs->tileTag = tileTag;
        sHpBarObjs->palTag = palTag;
        StartSpriteAnim(sHpBarObjs->sprites[i], 8);
    }

    UpdateHpBarObjs();
    ShowOrHideHpBarObjs(TRUE);

    FREE_AND_SET_NULL_IF_SET(gfxBufferPtr);
}

static void UpdateHpBarObjs(void)
{
    u8 numWholeHpBarTiles = 0;
    u8 i;
    u8 animNum;
    u8 two = 2;
    u8 hpBarPalOffset = 0;
    u32 curHp;
    u32 maxHp;
    s64 pointsPerTile;
    s64 totalPoints;

    if (sMonSummaryScreen->isEgg)
        return;

    curHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_HP);
    maxHp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MAX_HP);

    if (maxHp / 5 >= curHp)
        hpBarPalOffset = 2;
    else if (maxHp / 2 >= curHp)
        hpBarPalOffset = 1; //changes color of bar based on health ratio red below 20, yellow below 50

    switch (GetHPBarLevel(curHp, maxHp))
    {
    case 3:
    default:
        hpBarPalOffset = 0;
        break;
    case 2:
        hpBarPalOffset = 1;
        break;
    case 1:
        hpBarPalOffset = 2;
        break;
    }

    for (i = 0; i < 9; i++)
        sHpBarObjs->sprites[i]->oam.paletteNum = IndexOfSpritePaletteTag(TAG_PSS_UNK_78) + hpBarPalOffset;

    if (curHp == maxHp)
        for (i = two; i < 8; i++)
            StartSpriteAnim(sHpBarObjs->sprites[i], 8);

    else
    {
        pointsPerTile = (maxHp << 2) / 6;
        totalPoints = (curHp << 2);

        while (TRUE)
        {
            if (totalPoints <= pointsPerTile)
                break;
            totalPoints -= pointsPerTile;
            numWholeHpBarTiles++;
        }

        numWholeHpBarTiles += two;

        for (i = two; i < numWholeHpBarTiles; i++)
            StartSpriteAnim(sHpBarObjs->sprites[i], 8);

        animNum = (totalPoints * 6) / pointsPerTile;
        StartSpriteAnim(sHpBarObjs->sprites[numWholeHpBarTiles], animNum);

        for (i = numWholeHpBarTiles + 1; i < 8; i++)
            StartSpriteAnim(sHpBarObjs->sprites[i], 0);
    }

    StartSpriteAnim(sHpBarObjs->sprites[0], 9);
    StartSpriteAnim(sHpBarObjs->sprites[1], 10);
    StartSpriteAnim(sHpBarObjs->sprites[8], 11);
}

static void DestroyHpBarObjs(void)
{
    u8 i;

    for (i = 0; i < 9; i++)
        if (sHpBarObjs->sprites[i] != NULL)
            DestroySpriteAndFreeResources(sHpBarObjs->sprites[i]);

    FREE_AND_SET_NULL_IF_SET(sHpBarObjs);
}

static void ShowOrHideHpBarObjs(u8 invisible)
{
    u8 i;

    for (i = 0; i < 9; i++)
        sHpBarObjs->sprites[i]->invisible = invisible;
}

static void CreateExpBarObjs(u16 tileTag, u16 palTag)
{
    u8 i;
    u8 spriteId;
    void * gfxBufferPtr;

    sExpBarObjs = AllocZeroed(sizeof(struct ExpBarObjs));
    gfxBufferPtr = AllocZeroed(0x20 * 12);

    LZ77UnCompWram(gPokeSummary_ExpBarTiles, gfxBufferPtr);
    if (gfxBufferPtr != NULL)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtr,
            .size = 0x20 * 12,
            .tag = tileTag
        };

        struct SpritePalette palette = {.data = gPokeSummary_ExpBarPals, .tag = palTag};
        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette);
    }

    for (i = 0; i < 11; i++)
    {
        struct SpriteTemplate template = {
            .tileTag = tileTag,
            .paletteTag = palTag,
            .oam = &sHpOrExpBarOamData,
            .anims = sHpOrExpBarAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCallbackDummy,
        };

        sExpBarObjs->xpos[i] = i * 8 + 156; //could be the important for changes to trainer memo
        spriteId = CreateSprite(&template, sExpBarObjs->xpos[i], 128, 0); //says is y coordinate see if all i need
        sExpBarObjs->sprites[i] = &gSprites[spriteId];//yeah that's all I need to change
        sExpBarObjs->sprites[i]->oam.priority = 2;
        sExpBarObjs->tileTag = tileTag;
        sExpBarObjs->palTag = palTag;
    }

    UpdateExpBarObjs();
    ShowOrHideExpBarObjs(TRUE);

    FREE_AND_SET_NULL_IF_SET(gfxBufferPtr);
}

static void UpdateExpBarObjs(void)
{
    u8 numWholeExpBarTiles = 0;
    u8 i;
    u8 level;
    u32 exp;
    u32 totalExpToNextLevel;
    u32 curExpToNextLevel;
    u16 species;
    s64 pointsPerTile;
    s64 totalPoints;
    u8 animNum;
    u8 two = 2;

    if (sMonSummaryScreen->isEgg)
        return;

    exp = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_EXP);
    level = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_LEVEL);
    species = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES);

    if (level < 100)
    {
        totalExpToNextLevel = gExperienceTables[gBaseStats[species].growthRate][level + 1] - gExperienceTables[gBaseStats[species].growthRate][level];
        curExpToNextLevel = exp - gExperienceTables[gBaseStats[species].growthRate][level];
        pointsPerTile = ((totalExpToNextLevel << 2) / 8);
        totalPoints = (curExpToNextLevel << 2);

        while (TRUE)
        {
            if (totalPoints <= pointsPerTile)
                break;
            totalPoints -= pointsPerTile;
            numWholeExpBarTiles++;
        }

        numWholeExpBarTiles += two;

        for (i = two; i < numWholeExpBarTiles; i++)
            StartSpriteAnim(sExpBarObjs->sprites[i], 8);

        if (numWholeExpBarTiles >= 10)
        {
            if (totalExpToNextLevel == curExpToNextLevel)
                return;
            else
                StartSpriteAnim(sExpBarObjs->sprites[9], 7);
        }

        animNum = (totalPoints * 8) / pointsPerTile;
        StartSpriteAnim(sExpBarObjs->sprites[numWholeExpBarTiles], animNum);

        for (i = numWholeExpBarTiles + 1; i < 10; i++)
            StartSpriteAnim(sExpBarObjs->sprites[i], 0);
    }
    else
        for (i = two; i < 10; i++)
            StartSpriteAnim(sExpBarObjs->sprites[i], 0);

    StartSpriteAnim(sExpBarObjs->sprites[0], 9);
    StartSpriteAnim(sExpBarObjs->sprites[1], 10);
    StartSpriteAnim(sExpBarObjs->sprites[10], 11);
}

static void DestroyExpBarObjs(void)
{
    u8 i;

    for (i = 0; i < 11; i++)
        if (sExpBarObjs->sprites[i] != NULL)
            DestroySpriteAndFreeResources(sExpBarObjs->sprites[i]);

    FREE_AND_SET_NULL_IF_SET(sExpBarObjs);
}

static void ShowOrHideExpBarObjs(u8 invisible)
{
    u8 i;

    for (i = 0; i < 11; i++)
        sExpBarObjs->sprites[i]->invisible = invisible;
}

static void CreatePokerusIconObj(u16 tileTag, u16 palTag)
{
    u16 spriteId;
    void * gfxBufferPtr;

    sPokerusIconObj = AllocZeroed(sizeof(struct PokerusIconObj));
    gfxBufferPtr = AllocZeroed(0x20 * 1);

    LZ77UnCompWram(sPokerusIconObjTiles, gfxBufferPtr);

    if (sPokerusIconObj != NULL)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtr,
            .size = 0x20 * 1,
            .tag = tileTag
        };

        struct SpritePalette palette = {.data = sPokerusIconObjPal, .tag = palTag};
        struct SpriteTemplate template = {
            .tileTag = tileTag,
            .paletteTag = palTag,
            .oam = &sPokerusIconObjOamData,
            .anims = sPokerusIconObjAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCallbackDummy,
        };

        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette);

        spriteId = CreateSprite(&template, 114, 92, 0);
        sPokerusIconObj->sprite = &gSprites[spriteId];
        sPokerusIconObj->tileTag = tileTag;
        sPokerusIconObj->palTag = palTag;
    }

    HideShowPokerusIcon(TRUE);
    ShowPokerusIconObjIfHasOrHadPokerus();

    FREE_AND_SET_NULL_IF_SET(gfxBufferPtr);
}

static void DestroyPokerusIconObj(void)
{
    if (sPokerusIconObj->sprite != NULL)
        DestroySpriteAndFreeResources(sPokerusIconObj->sprite);

    FREE_AND_SET_NULL_IF_SET(sPokerusIconObj);
}

static void ShowPokerusIconObjIfHasOrHadPokerus(void)
{
    if (!CheckPartyPokerus(&sMonSummaryScreen->currentMon, 0)
        && CheckPartyHasHadPokerus(&sMonSummaryScreen->currentMon, 0))
        HideShowPokerusIcon(0);
    else
        HideShowPokerusIcon(1);
}

static void HideShowPokerusIcon(u8 invisible)
{
    if (!CheckPartyPokerus(&sMonSummaryScreen->currentMon, 0)
        && CheckPartyHasHadPokerus(&sMonSummaryScreen->currentMon, 0))
    {
        sPokerusIconObj->sprite->invisible = invisible;
        return;
    }
    else
        sPokerusIconObj->sprite->invisible = TRUE;

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
    {
        sPokerusIconObj->sprite->invisible = TRUE;
        sPokerusIconObj->sprite->pos1.x = 16;
        sPokerusIconObj->sprite->pos1.y = 44;
    }
    else
    {
        sPokerusIconObj->sprite->pos1.x = 114;
        sPokerusIconObj->sprite->pos1.y = 92;
    }
}

static void CreateShinyStarObj(u16 tileTag, u16 palTag)
{
    u16 spriteId;
    void * gfxBufferPtr;

    sShinyStarObjData = AllocZeroed(sizeof(struct ShinyStarObjData));
    gfxBufferPtr = AllocZeroed(0x20 * 2);

    LZ77UnCompWram(sStarObjTiles, gfxBufferPtr);

    if (sShinyStarObjData != NULL)
    {
        struct SpriteSheet sheet = {
            .data = gfxBufferPtr,
            .size = 0x20 * 2,
            .tag = tileTag
        };

        struct SpritePalette palette = {.data = sStarObjPal, .tag = palTag};
        struct SpriteTemplate template = {
            .tileTag = tileTag,
            .paletteTag = palTag,
            .oam = &sStarObjOamData,
            .anims = sStarObjAnimTable,
            .images = NULL,
            .affineAnims = gDummySpriteAffineAnimTable,
            .callback = SpriteCallbackDummy,
        };

        LoadSpriteSheet(&sheet);
        LoadSpritePalette(&palette);
        spriteId = CreateSprite(&template, 106, 40, 0);
        sShinyStarObjData->sprite = &gSprites[spriteId];
        sShinyStarObjData->tileTag = tileTag;
        sShinyStarObjData->palTag = palTag;
    }

    HideShowShinyStar(TRUE);
    ShowShinyStarObjIfMonShiny();

    FREE_AND_SET_NULL_IF_SET(gfxBufferPtr);
}

static void DestroyShinyStarObj(void)
{
    if (sShinyStarObjData->sprite != NULL)
        DestroySpriteAndFreeResources(sShinyStarObjData->sprite);

    FREE_AND_SET_NULL_IF_SET(sShinyStarObjData);
}

static void HideShowShinyStar(u8 invisible)
{
    if (IsMonShiny(&sMonSummaryScreen->currentMon) == TRUE
        && !sMonSummaryScreen->isEgg)
        sShinyStarObjData->sprite->invisible = invisible;
    else
        sShinyStarObjData->sprite->invisible = TRUE;

    if (sMonSummaryScreen->curPageIndex == PSS_PAGE_MOVES_INFO)
    {
        sShinyStarObjData->sprite->pos1.x = 8;
        sShinyStarObjData->sprite->pos1.y = 24;
    }
    else
    {
        sShinyStarObjData->sprite->pos1.x = 106;
        sShinyStarObjData->sprite->pos1.y = 40;
    }
}

static void ShowShinyStarObjIfMonShiny(void)
{
    if (IsMonShiny(&sMonSummaryScreen->currentMon) == TRUE && !sMonSummaryScreen->isEgg)
        HideShowShinyStar(0);
    else
        HideShowShinyStar(1);
}

static void PokeSum_DestroySprites(void)
{
    DestroyMoveSelectionCursorObjs();
    DestroyHpBarObjs();
    DestroyExpBarObjs();
    PokeSum_DestroyMonPicSprite();
    PokeSum_DestroyMonIconSprite();
    DestroyBallIconObj();
    //PokeSum_DestroyMonMarkingsSprite();
    DestroyMonStatusIconObj();
    DestroyPokerusIconObj();
    DestroyShinyStarObj();
    ResetSpriteData();
}

static void PokeSum_CreateSprites(void)
{
    CreateBallIconObj();
    ShowOrHideBallIconObj(0);
    PokeSum_CreateMonIconSprite();
    PokeSum_CreateMonPicSprite();
    PokeSum_ShowOrHideMonPicSprite(0);
    UpdateHpBarObjs();
    UpdateExpBarObjs();
    //PokeSum_UpdateMonMarkingsAnim();
    UpdateMonStatusIconObj();
    ShowPokerusIconObjIfHasOrHadPokerus();
    ShowShinyStarObjIfMonShiny();
}

static void PokeSum_CreateMonMarkingsSprite(void)
{
    /*u32 markings = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MARKINGS);

    DestroySpriteAndFreeResources(sMonSummaryScreen->markingSprite);
   // sMonSummaryScreen->markingSprite = CreateMonMarkingSprite_SelectCombo(TAG_PSS_UNK_8C, TAG_PSS_UNK_8C, sUnknown_84636E0);

    if (sMonSummaryScreen->markingSprite != NULL)
    {
        StartSpriteAnim(sMonSummaryScreen->markingSprite, markings);
        sMonSummaryScreen->markingSprite->pos1.x = 20;
        sMonSummaryScreen->markingSprite->pos1.y = 91;
    }

    PokeSum_ShowOrHideMonMarkingsSprite(TRUE); */
    return;  //ok cuz this is void
}

static void PokeSum_DestroyMonMarkingsSprite(void)
{
    return; //DestroySpriteAndFreeResources(sMonSummaryScreen->markingSprite);
}

static void PokeSum_ShowOrHideMonMarkingsSprite(u8 invisible)
{
    return;
    /*u32 markings = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MARKINGS);

    if (markings == 0)
        sMonSummaryScreen->markingSprite->invisible = TRUE;
    else
        sMonSummaryScreen->markingSprite->invisible = invisible;*/
}

static void PokeSum_UpdateMonMarkingsAnim(void)
{
    return;
    /*u32 markings = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MARKINGS);

    StartSpriteAnim(sMonSummaryScreen->markingSprite, markings);
    PokeSum_ShowOrHideMonMarkingsSprite(0); */
}

static void PokeSum_SeekToNextMon(u8 taskId, s8 direction)
{
    s8 scrollResult = -1;

    if (sMonSummaryScreen->isBoxMon == TRUE)
    {
        if (sMonSummaryScreen->curPageIndex != PSS_PAGE_INFO)
        {
            if (direction == 1)
                direction = 0;
            else
                direction = 2;
        }
        else
        {
            // Allow Eggs
            if (direction == 1)
                direction = 1;
            else
                direction = 3;
        }

        scrollResult = SeekToNextMonInBox(sMonSummaryScreen->monList.boxMons, GetLastViewedMonIndex(), sMonSummaryScreen->lastIndex, (u8)direction);
    }
    else
    {
        if (IsUpdateLinkStateCBActive() == FALSE
            && gReceivedRemoteLinkPlayers == 1
            && IsMultiBattle() == TRUE)
            scrollResult = SeekToNextMonInMultiParty(direction);
        else
            scrollResult = SeekToNextMonInSingleParty(direction);
    }

    if (scrollResult == -1)
        return;

    sLastViewedMonIndex = scrollResult;
    CreateTask(Task_PokeSum_SwitchDisplayedPokemon, 0);
    sMonSummaryScreen->switchMonTaskState = 0;
}

static s8 SeekToNextMonInSingleParty(s8 a0)
{
    struct Pokemon * partyMons = sMonSummaryScreen->monList.mons;
    s8 v1 = 0;

    if (sMonSummaryScreen->curPageIndex == 0)
    {
        if (a0 == -1 && sLastViewedMonIndex == 0)
            return -1;
        else if (a0 == 1 && sLastViewedMonIndex >= sMonSummaryScreen->lastIndex)
            return -1;
        else
            return sLastViewedMonIndex + a0;
    }

    while (TRUE)
    {
        v1 += a0;
        if (0 > sLastViewedMonIndex + v1 || sLastViewedMonIndex + v1 > sMonSummaryScreen->lastIndex)
            return -1;

        if (GetMonData(&partyMons[sLastViewedMonIndex + v1], MON_DATA_IS_EGG) == 0)
            return sLastViewedMonIndex + v1;
    }

    return -1;
}

static u8 PokeSum_CanSeekToMon(struct Pokemon * partyMons)
{
    if (GetMonData(partyMons, MON_DATA_SPECIES) != 0 && (sMonSummaryScreen->curPageIndex != 0 || GetMonData(partyMons, MON_DATA_IS_EGG) == 0))
        return TRUE;

    return FALSE;
}

static s8 SeekToMonInMultiParty_SeekForward(u8 startingIdx)
{
    while (TRUE)
    {
        startingIdx++;

        if (startingIdx == 6)
            return -1;
        if (PokeSum_CanSeekToMon(&gPlayerParty[sMultiBattlePartyOrder[startingIdx]]) == TRUE)
            break;
    }

    return (s8)sMultiBattlePartyOrder[startingIdx];
}

static s8 sub_813B348(u8 startingIdx)
{
    while (1)
    {
        if (startingIdx == 0)
            return -1;

        startingIdx--;

        if (PokeSum_CanSeekToMon(&gPlayerParty[sMultiBattlePartyOrder[startingIdx]]) == TRUE)
            break;
    }

    return (s8)(sMultiBattlePartyOrder[startingIdx]);
}

static s8 SeekToNextMonInMultiParty(s8 direction)
{
    u8 foundPartyIdx = 0;
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
        if (sMultiBattlePartyOrder[i] == GetLastViewedMonIndex())
        {
            foundPartyIdx = i;
            break;
        }

    if ((direction == -1 && foundPartyIdx == 0)
        || (direction == 1 && foundPartyIdx == 5))
        return -1;

    if (direction == 1)
        return SeekToMonInMultiParty_SeekForward(foundPartyIdx);
    else
        return sub_813B348(foundPartyIdx);
}

static void Task_PokeSum_SwitchDisplayedPokemon(u8 id)
{
    switch (sMonSummaryScreen->switchMonTaskState)
    {
    case 0:
        StopCryAndClearCrySongs();
        sMoveSelectionCursorPos = 0;
        sMoveSwapCursorPos = 0;
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 1:
        PokeSum_DestroyMonPicSprite();
        PokeSum_DestroyMonIconSprite();
        DestroyBallIconObj();
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 2:
        BufferSelectedMonData(&sMonSummaryScreen->currentMon);

        sMonSummaryScreen->isEgg = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_IS_EGG);
        sMonSummaryScreen->isBadEgg = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SANITY_IS_BAD_EGG);

        if (sMonSummaryScreen->isBadEgg == TRUE)
            sMonSummaryScreen->isEgg = TRUE;

        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 3:
        FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);

        if (IsMonShiny(&sMonSummaryScreen->currentMon) == TRUE && !sMonSummaryScreen->isEgg)
        {
            LoadPalette(&gTrainerMemoPal1[16 * 6], 0, 0x20);
            LoadPalette(&gTrainerMemoPal1[16 * 5], 0x10, 0x20);
        }
        else
        {
            LoadPalette(&gTrainerMemoPal1[16 * 0], 0, 0x20);
            LoadPalette(&gTrainerMemoPal1[16 * 1], 0x10, 0x20);
        }

        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 4:
        if (sMonSummaryScreen->curPageIndex == PSS_PAGE_INFO)
        {
            if (sMonSummaryScreen->isEgg)
            {
                CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_TrainerMemo_Egg, 0, 0);
                CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);
            }
            else
            {
                CopyToBgTilemapBuffer(sMonSummaryScreen->skillsPageBgNum, gBgTilemap_TrainerMemo_Details, 0, 0);
                CopyToBgTilemapBuffer(sMonSummaryScreen->infoAndMovesPageBgNum, gBgTilemap_TrainerMemo_Stats, 0, 0);
            }
        }
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 5:
        BufferMonInfo();
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 6:
        if (!sMonSummaryScreen->isEgg)
            BufferMonSkills();

        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 7:
        if (!sMonSummaryScreen->isEgg)
            BufferMonMoves();

        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 8:
        PokeSum_PrintRightPaneText();
        PokeSum_PrintBottomPaneText();
        PokeSum_PrintAbilityDataOrMoveTypes();
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 9:
        PokeSum_PrintMonTypeIcons();
        PokeSum_DrawBg3Tilemap();
        PokeSum_PrintPageHeaderText(sMonSummaryScreen->curPageIndex);
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 10:
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_PAGE_NAME], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_CONTROLS], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_LVL_NICK], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[6], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_RIGHT_PANE], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[POKESUM_WIN_TRAINER_MEMO], 2);
        CopyWindowToVram(sMonSummaryScreen->windowIds[5], 2);
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sMonSummaryScreen->switchMonTaskState++;
        break;
    case 11:
        if (!Overworld_LinkRecvQueueLengthMoreThan2() && !sub_800B270())
        {
            PokeSum_CreateSprites();
            PokeSum_TryPlayMonCry();
            sMonSummaryScreen->switchMonTaskState++;
        }
        break;
    default:
        sMonSummaryScreen->switchMonTaskState = 0;
        DestroyTask(id);
        break;
    }
}

static void PokeSum_UpdateWin1ActiveFlag(u8 curPageIndex)
{
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN1_ON);

    switch (curPageIndex)
    {
    case PSS_PAGE_INFO:
    case PSS_PAGE_SKILLS:
    case PSS_PAGE_MOVES:
        SetGpuReg(REG_OFFSET_DISPCNT, GetGpuReg(REG_OFFSET_DISPCNT) | DISPCNT_WIN1_ON);
        break;
    default:
        break;
    }
}

static void PokeSum_TryPlayMonCry(void)
{
    if (!GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_IS_EGG))
    {
        if (ShouldPlayNormalPokeCry(&sMonSummaryScreen->currentMon) == TRUE)
            PlayCry_ByMode(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2), 0, 0);
        else
            PlayCry_ByMode(GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_SPECIES2), 0, 11);
    }
}

static bool32 PokeSum_IsMonBoldOrGentle(u8 nature)
{
    if (nature == NATURE_BOLD || nature == NATURE_GENTLE)
        return TRUE;

    return FALSE;
}

static bool32 CurrentMonIsFromGBA(void)
{
    u8 version = GetMonData(&sMonSummaryScreen->currentMon, MON_DATA_MET_GAME);

    if (version == VERSION_LEAF_GREEN
        || version == VERSION_FIRE_RED
        || version == VERSION_RUBY
        || version == VERSION_SAPPHIRE
        || version == VERSION_EMERALD)
        return TRUE;

    return FALSE;
}

static bool32 MapSecIsInKantoOrSevii(u8 place)
{
    if (place >= MAPSECS_KANTO && place < MAPSEC_NONE)
        return TRUE;
    return FALSE;
}

// Unused
static void ShowPokemonSummaryScreen_NullParty(void)
{
    ShowPokemonSummaryScreen(0, 0, 0, CB2_ReturnToField, PSS_MODE_NORMAL);
}
