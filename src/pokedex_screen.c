#include "global.h"
#include "gflib.h"
#include "graphics.h"
#include "m4a.h"
#include "scanline_effect.h"
#include "task.h"
#include "new_menu_helpers.h"
#include "event_data.h"
#include "help_system.h"
#include "menu_indicators.h"
#include "overworld.h"
#include "strings.h"
#include "menu.h"
#include "pokedex_screen.h"
#include "data.h"
#include "pokedex.h"
#include "trainer_pokemon_sprites.h"
#include "decompress.h"
#include "constants/songs.h"
#include "constants/sound.h"
#include "pokedex_area_markers.h"
#include "field_specials.h"

#define TAG_AREA_MARKERS 2001

#define DEX_MAX_SHOWN sListMenuTemplate_OrderedListMenu.maxShowed//9  //plan use for amount of mon to initially load, for speed sake, then expand on as scroll

#define DEX_LOWER_FILL 30
#define DEX_UPPER_FILL 30 //same value but need diff constant

#define SCROLL_UP 1
#define SCROLL_DOWN 0
#define EXIT_DEX_ENTRY 2

enum TextMode {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

struct PokedexScreenData
{
    u8 taskId;
    u8 state;
    u8 data[2]; //doesn't go above 1, so only 2 fileds, so using 4 is unnecessary
    u8 areaMarkersTaskId;
    u32 unlockedCategories;
    u32 modeSelectInput;
    u16 modeSelectItemsAbove;
    u16 modeSelectCursorPos;
    u8 modeSelectWindowId;
    u8 selectionIconWindowId;
    u8 dexCountsWindowId;
    u8 modeSelectListMenuId;
    u16 pageSpecies[4];
    u8 categoryMonWindowIds[4];
    u8 categoryMonInfoWindowIds[4];
    u8 category;
    u8 firstPageInCategory;
    u8 lastPageInCategory;
    u8 pageNum;
    u8 numMonsOnPage;
    u8 categoryCursorPosInPage;
    u8 categoryPageSelectionCursorTimer;
    u8 parentOfCategoryMenu;
    u32 characteristicMenuInput;
    u16 kantoOrderMenuItemsAbove;
    u16 kantoOrderMenuCursorPos;
    u16 characteristicOrderMenuItemsAbove;
    u16 characteristicOrderMenuCursorPos;
    u16 nationalOrderMenuItemsAbove;
    u16 nationalOrderMenuCursorPos;
    u8 numericalOrderWindowId;
    u8 orderedListMenuTaskId;
    u8 dexOrderId;
    struct ListMenuItem * listItems; //reverted below for space saving, think otherwise its same affect, didn't affect load time, saves bout 10Kb of rom space
   // struct ListMenuItem listItems[NATIONAL_DEX_COUNT + 1]; //making this lets me skip alloc in load resources, costs good deal of space, but hopefully will svae me elsewher
    u16 orderedDexCount;
    u16 CurrentIndexValue; //added for categorica lists, to store array value that alligns w current index, takes i + 1 for this, so next trigger will be in allignment
    u8 windowIds[0x10];
    u16 dexSpecies;
    u16 * bgBufsMem;
    u8 scrollArrowsTaskId;
    u8 categoryPageCursorTaskId;
    u16 modeSelectCursorPosBak;
    u8 unlockedSeviiAreas;
    u16 numSeenKanto;
    u16 numOwnedKanto;
    u16 numSeenNational;
    u16 numOwnedNational;
};

struct PokedexScreenWindowGfx
{
    const u16 * tiles;
    const u16 * pal;
};

struct PokedexCategoryPage
{
    const u16 * species;
    u8 count;
};

//equivalent of sPokedexScreenData in emerald meaning dexscreendata is = PokedexView
EWRAM_DATA static struct PokedexScreenData * sPokedexScreenData = NULL;

static void Task_PokedexScreen(u8 taskId);
static void DexScreen_InitGfxForTopMenu(void);
static void Task_DexScreen_NumericalOrder(u8 taskId);
static void DexScreen_InitGfxForNumericalOrderList(void);
static void Task_DexScreen_CharacteristicOrder(u8 taskId);
static void DexScreen_CreateCharacteristicListMenu(void);
static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx);
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order);
static u8 DexScreen_CreateDexOrderScrollArrows(void);
static void DexScreen_DestroyDexOrderListMenu(u8 order);
static void Task_DexScreen_CategorySubmenu(u8 taskId);
static u8 DexScreen_CreateCategoryMenuScrollArrows(void);
static int DexScreen_InputHandler_GetShoulderInput(void);
static void Task_DexScreen_ShowMonPage(u8 taskId);
static bool32 DexScreen_TryScrollMonsVertical(u8 direction);
static void DexScreen_RemoveWindow(u8 *windowId_p); //pret made static, which makes sense these aren't used elsewhere
static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y);
static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex);
static void DexScreen_PrintControlInfo(const u8 *src);
static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void);
static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered);
static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos);
static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage);
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction);
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale);
static u8 DexScreen_DrawMonDexPage(bool8 justRegistered);
u8 RemoveDexPageWindows(void);
u8 DexScreen_DrawMonAreaPage(void);
static bool8 DexScreen_CanShowMonInCategory(u8 category, u8 pageNum); //same as is page unlocked just prefer name
static bool8 DexScreen_IsCategoryUnlocked(u8 category);
static u8 DexScreen_GetPageLimitsForCategory(u8 category);
static bool8 DexScreen_LookUpCategoryBySpecies(u16 species);
u8 DexScreen_DestroyAreaScreenResources(void);
void DexScreen_CreateCategoryPageSpeciesList(u8 category, u8 pageNum);
static u8 DexScreen_PageNumberToRenderablePages(u16 page);
void DexScreen_InputHandler_StartToCry(void);
void DexScreen_PrintStringWithAlignment(const u8 *str, s32 mode);
static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y);
static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y);
static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId);
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId);

//new stuff
static s32 DexScreen_ProcessInput(u8 listTaskId); //replace list menu input so can adjust separately
static void DexScreen_LoadIndex(u32 count, u8 direction, int selectedIndex, s8 scroll_increment);//load list indexs on scroll after first open
//added scroll increment to attempt help keep placement - works done
static u16 DexScreen_CreateList_ReturnCount(u8 orderIdx, int selectedIndex); //moved new list creation logic here, still to be called from DexScreen_CountMonsInOrderedList

#include "data/pokemon_graphics/footprint_table.h"

//const u8 sCategoryMonInfoBgTiles[] = INCBIN_U8("graphics/pokedex/unk_8440124.bin.lz"); //think was previous category image

/*#ifdef SPECIES_NAME_EXPANSION
const u32 sCategoryMonLargeInfoBgTiles[] = INCBIN_U32("graphics/pokedex/large_mini_page.4bpp.lz");
const u32 sCategoryMonMediumInfoBgTiles[] = INCBIN_U32("graphics/pokedex/medium_mini_page.4bpp.lz");
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#else
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#endif // SPECIES_NAME_EXPANSION */

const u8 sCategoryMonInfoBgTiles[] = INCBIN_U8("graphics/pokedex/mini_page.bin.lz");
const u8 sKantoDexTiles[] = INCBIN_U8("graphics/pokedex/unk_8440274.4bpp.lz");
const u8 sNatDexTiles[] = INCBIN_U8("graphics/pokedex/unk_84403AC.4bpp.lz");
const u16 sKantoDexPalette[] = INCBIN_U16("graphics/pokedex/unk_84404C8.gbapal");

const u16 sDexScreen_CategoryCursorPals[] = {
    RGB(24, 22, 17), RGB(26, 24, 20),
    RGB(26, 20, 15), RGB(27, 23, 19),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(30, 16, 13), RGB(29, 21, 18),
    RGB(28, 18, 15), RGB(28, 22, 19),
    RGB(26, 20, 15), RGB(27, 23, 19)
};

const u16 sNationalDexPalette[] = INCBIN_U16("graphics/pokedex/unk_84406E0.gbapal");
const u16 sTopMenuIconTiles_Cave[] = INCBIN_U16("graphics/pokedex/unk_84408E0.bin.lz");
const u16 sTopMenuIconTiles_Urban[] = INCBIN_U16("graphics/pokedex/unk_8440BD8.bin.lz");
const u32 sTopMenuSelectionIconTiles_Cancel[] = INCBIN_U32("graphics/pokedex/unk_8440EF0.bin.lz");
const u16 sTopMenuIconTiles_Forest[] = INCBIN_U16("graphics/pokedex/unk_844112C.bin.lz");
const u16 sTopMenuIconTiles_Grassland[] = INCBIN_U16("graphics/pokedex/unk_84414BC.bin.lz");
const u32 sTopMenuIconTiles_QuestionMark[] = INCBIN_U32("graphics/pokedex/unk_8441808.bin.lz");
const u16 sTopMenuIconTiles_Mountain[] = INCBIN_U16("graphics/pokedex/unk_8441A40.bin.lz");
const u16 sTopMenuIconTiles_Rare[] = INCBIN_U16("graphics/pokedex/unk_8441D54.bin.lz");
const u16 sTopMenuIconTiles_Sea[] = INCBIN_U16("graphics/pokedex/unk_8442004.bin.lz");
const u16 sTopMenuIconTiles_Numerical[] = INCBIN_U16("graphics/pokedex/unk_844223C.bin.lz");
const u16 sTopMenuIconTiles_RoughTerrain[] = INCBIN_U16("graphics/pokedex/unk_84424E4.bin.lz");
const u16 sTopMenuIconTiles_WatersEdge[] = INCBIN_U16("graphics/pokedex/unk_8442838.bin.lz");
const u16 sTopMenuIconTiles_Type[] = INCBIN_U16("graphics/pokedex/unk_8442BC0.bin.lz");
const u16 sTopMenuIconTiles_Lightest[] = INCBIN_U16("graphics/pokedex/unk_8442EF8.bin.lz");
const u16 sTopMenuIconTiles_Smallest[] = INCBIN_U16("graphics/pokedex/unk_844318C.bin.lz");
const u16 sTopMenuIconPals_Cave[] = INCBIN_U16("graphics/pokedex/unk_8443420.gbapal");
const u16 sTopMenuIconPals_Urban[] = INCBIN_U16("graphics/pokedex/unk_8443440.gbapal");
const u16 sTopMenuSelectionIconPals_Cancel[] = INCBIN_U16("graphics/pokedex/unk_8443460.gbapal");
const u16 sTopMenuIconPals_Forest[] = INCBIN_U16("graphics/pokedex/unk_8443480.gbapal");
const u16 sTopMenuIconPals_Grassland[] = INCBIN_U16("graphics/pokedex/unk_84434A0.gbapal");
const u16 sTopMenuIconPals_QuestionMark[] = INCBIN_U16("graphics/pokedex/unk_84434C0.gbapal");
const u16 sTopMenuIconPals_Mountain[] = INCBIN_U16("graphics/pokedex/unk_84434E0.gbapal");
const u16 sTopMenuIconPals_Rare[] = INCBIN_U16("graphics/pokedex/unk_8443500.gbapal");
const u16 sTopMenuIconPals_Sea[] = INCBIN_U16("graphics/pokedex/unk_8443520.gbapal");
const u16 sTopMenuIconPals_Numerical[] = INCBIN_U16("graphics/pokedex/unk_8443540.gbapal");
const u16 sTopMenuIconPals_RoughTerrain[] = INCBIN_U16("graphics/pokedex/unk_8443560.gbapal");
const u16 sTopMenuIconPals_WatersEdge[] = INCBIN_U16("graphics/pokedex/unk_8443580.gbapal");
const u16 sTopMenuIconPals_Type[] = INCBIN_U16("graphics/pokedex/unk_84435A0.gbapal");
const u16 sTopMenuIconPals_Lightest[] = INCBIN_U16("graphics/pokedex/unk_84435C0.gbapal");
const u16 sTopMenuIconPals_Smallest[] = INCBIN_U16("graphics/pokedex/unk_84435E0.gbapal");
const u8 sDexScreen_CaughtIcon[] = INCBIN_U8("graphics/pokedex/unk_8443600.4bpp");
const u32 sTilemap_AreaMap_Kanto[] = INCBIN_U32("graphics/pokedex/unk_8443620.bin.lz");
const u32 sTilemap_AreaMap_OneIsland[] = INCBIN_U32("graphics/pokedex/unk_8443910.bin.lz");
const u32 sTilemap_AreaMap_TwoIsland[] = INCBIN_U32("graphics/pokedex/unk_8443988.bin.lz");
const u32 sTilemap_AreaMap_ThreeIsland[] = INCBIN_U32("graphics/pokedex/unk_84439FC.bin.lz");
const u32 sTilemap_AreaMap_FourIsland[] = INCBIN_U32("graphics/pokedex/unk_8443A78.bin.lz");
const u32 sTilemap_AreaMap_FiveIsland[] = INCBIN_U32("graphics/pokedex/unk_8443AF8.bin.lz");
const u32 sTilemap_AreaMap_SixIsland[] = INCBIN_U32("graphics/pokedex/unk_8443BB0.bin.lz");
const u32 sTilemap_AreaMap_SevenIsland[] = INCBIN_U32("graphics/pokedex/unk_8443C54.bin.lz");
const u16 sBlitTiles_WideEllipse[] = INCBIN_U16("graphics/pokedex/unk_8443D00.4bpp");

#include "data/pokemon/pokedex_orders.h"

static const u8 gExpandedPlaceholder_PokedexDescription[] = _("");

#include "data/pokemon/pokedex_text.h"
#include "data/pokemon/pokedex_entries.h"

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 5,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x0000
    },
    {
        .bg = 1,
        .charBaseIndex = 2,
        .mapBaseIndex = 4,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x0000
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x0000
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x0000
    },
};

static const struct WindowTemplate sWindowTemplates[] = {
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x03c4
    },
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 18,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x0388
    },
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

static const struct PokedexScreenData sDexScreenDataInitialState = {
    .modeSelectItemsAbove = 1,  //this works like n-1 so value 1 always just means 0/top of list
    .modeSelectWindowId = -1,
    .selectionIconWindowId = -1,
    .dexCountsWindowId = -1,
    .pageSpecies = {-1, -1, -1, -1},
    .categoryMonWindowIds = {-1, -1, -1, -1},
    .categoryMonInfoWindowIds = {-1, -1, -1, -1},
    .numericalOrderWindowId = -1,
    .windowIds = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    .scrollArrowsTaskId = -1,
    .categoryPageCursorTaskId = -1,
};


static const struct WindowTemplate sWindowTemplate_ModeSelect = {
    .bg = 1,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 20,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct WindowTemplate sWindowTemplate_SelectionIcon = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 11,
    .width = 8,
    .height = 6,
    .paletteNum = 1,
    .baseBlock = 0x0148
};

static const struct WindowTemplate sWindowTemplate_DexCounts = {
    .bg = 1,
    .tilemapLeft = 21,
    .tilemapTop = 2,
    .width = 9,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x0178
};

static const struct ListMenuItem sListMenuItems_KantoDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalMode,                DEX_MODE(NUMERICAL_KANTO)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_KantoDexModeSelect = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_KantoDexModeSelect),
    .maxShowed = 9, //same as below but just withuot national dex stuff
    .windowId = 0,
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ListMenuItem sListMenuItems_NatDexModeSelect[] = {
    {gText_PokemonList,                  LIST_HEADER},
    {gText_NumericalModeKanto,           DEX_MODE(NUMERICAL_KANTO)},
    {gText_NumericalModeNational,        DEX_MODE(NUMERICAL_NATIONAL)},
    {gText_PokemonHabitats,              LIST_HEADER},
    {gText_DexCategory_GrasslandPkmn,    DEX_CATEGORY_GRASSLAND},
    {gText_DexCategory_ForestPkmn,       DEX_CATEGORY_FOREST},
    {gText_DexCategory_WatersEdgePkmn,   DEX_CATEGORY_WATERS_EDGE},
    {gText_DexCategory_SeaPkmn,          DEX_CATEGORY_SEA},
    {gText_DexCategory_CavePkmn,         DEX_CATEGORY_CAVE},
    {gText_DexCategory_MountainPkmn,     DEX_CATEGORY_MOUNTAIN},
    {gText_DexCategory_RoughTerrainPkmn, DEX_CATEGORY_ROUGH_TERRAIN},
    {gText_DexCategory_UrbanPkmn,        DEX_CATEGORY_URBAN},
    {gText_DexCategory_RarePkmn,         DEX_CATEGORY_RARE},
    {gText_Search,                       LIST_HEADER},
    {gText_AToZMode,                     DEX_MODE(ATOZ)},
    {gText_TypeMode,                     DEX_MODE(TYPE)},
    {gText_LightestMode,                 DEX_MODE(LIGHTEST)},
    {gText_SmallestMode,                 DEX_MODE(SMALLEST)},
    {gText_PokedexOther,                 LIST_HEADER},
    {gText_ClosePokedex,                 LIST_CANCEL},
};

static const struct ListMenuTemplate sListMenuTemplate_NatDexModeSelect = {
    .items = sListMenuItems_NatDexModeSelect,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sListMenuItems_NatDexModeSelect),
    .maxShowed = 9, //max seen on page, and amount moved by when moving left and right
    .windowId = 0, //oh wait thats in geneeral not for the mon dex page, it only shows 9 lines in general
    .header_X = 0,
    .item_X = 12,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_KantoDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 10,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_NatDex = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 11,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1
};


static const struct PokedexScreenWindowGfx sTopMenuSelectionIconGfxPtrs[] = {
    [DEX_CATEGORY_GRASSLAND] = {
        .tiles = sTopMenuIconTiles_Grassland,
        .pal   = sTopMenuIconPals_Grassland
    },
    [DEX_CATEGORY_FOREST] = {
        .tiles = sTopMenuIconTiles_Forest,
        .pal   = sTopMenuIconPals_Forest
    },
    [DEX_CATEGORY_WATERS_EDGE] = {
        .tiles = sTopMenuIconTiles_WatersEdge,
        .pal   = sTopMenuIconPals_WatersEdge
    },
    [DEX_CATEGORY_SEA] = {
        .tiles = sTopMenuIconTiles_Sea,
        .pal   = sTopMenuIconPals_Sea
    },
    [DEX_CATEGORY_CAVE] = {
        .tiles = sTopMenuIconTiles_Cave,
        .pal   = sTopMenuIconPals_Cave
    },
    [DEX_CATEGORY_MOUNTAIN] = {
        .tiles = sTopMenuIconTiles_Mountain,
        .pal   = sTopMenuIconPals_Mountain
    },
    [DEX_CATEGORY_ROUGH_TERRAIN] = {
        .tiles = sTopMenuIconTiles_RoughTerrain,
        .pal   = sTopMenuIconPals_RoughTerrain
    },
    [DEX_CATEGORY_URBAN] = {
        .tiles = sTopMenuIconTiles_Urban,
        .pal   = sTopMenuIconPals_Urban
    },
    [DEX_CATEGORY_RARE] = {
        .tiles = sTopMenuIconTiles_Rare,
        .pal   = sTopMenuIconPals_Rare
    },
    [DEX_MODE(NUMERICAL_KANTO)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
    [DEX_MODE(ATOZ)] = {
        .tiles = gDexScreen_TopMenuIconTiles_AtoZ,
        .pal   = gDexScreen_TopMenuIconPals_AtoZ
    },
    [DEX_MODE(TYPE)] = {
        .tiles = sTopMenuIconTiles_Type,
        .pal   = sTopMenuIconPals_Type
    },
    [DEX_MODE(LIGHTEST)] = {
        .tiles = sTopMenuIconTiles_Lightest,
        .pal   = sTopMenuIconPals_Lightest
    },
    [DEX_MODE(SMALLEST)] = {
        .tiles = sTopMenuIconTiles_Smallest,
        .pal   = sTopMenuIconPals_Smallest
    },
    [DEX_MODE(NUMERICAL_NATIONAL)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal   = sTopMenuIconPals_Numerical
    },
};

//main window for list effects numerical & search modes
static const struct WindowTemplate sWindowTemplate_OrderedListMenu = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 27,
    .height = 16,
    .paletteNum = 0,
    .baseBlock = 0x0008
};

static const struct ListMenuTemplate sListMenuTemplate_OrderedListMenu = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = ItemPrintFunc_OrderedListMenu,
    .totalItems = 0,
    .maxShowed = 9, //ok THIS is actually for the dex list page
    .windowId = 0,
    .header_X = 0,
    .item_X = 56,
    .cursor_X = 4,
    .upText_Y = 2,
    .cursorPal = 1,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = 1,
    .fontId = FONT_NORMAL,
    .cursorKind = 0,
};

enum {
    LIST_MENU_CURSOR_DEXNUM,
    LIST_MENU_MONCAUGHT_ICON,
    LIST_MENU_SPECIES_NAME,
    LIST_MENU_TYPE_ICONS,
    LIST_MENU_0,
};

//used for all the list views in the menus, numerical order & all the search filters. eaech is a separate window  
//believe its the window the values sit in, not the main window as changnig x value doesn't seem to move values,
//just move the space they sit on?
static const struct ListMenuWindowRect sListMenuRects_OrderedList[] = {
    [LIST_MENU_CURSOR_DEXNUM] = {
        .x = 0,
        .y = 0,
        .width = 5,
        .height = 16,
        .palNum = 0
    },
    [LIST_MENU_MONCAUGHT_ICON] = {
        .x = 5,
        .y = 0,
        .width = 2,
        .height = 16,
        .palNum = 1
    },
    [LIST_MENU_SPECIES_NAME] = {
        .x = 7,
        .y = 0,
        .width = 9,
        .height = 16,
        .palNum = 0
    },
    [LIST_MENU_TYPE_ICONS] = {
        .x = 16,
        .y = 0,
        .width = 10,
        .height = 16,
        .palNum = 2,
    },
    [LIST_MENU_0] = {
        .x = 0xFF,
        .y = 0xFF,
        .width = 0xFF,
        .height = 0xFF,
        .palNum = 0xFF
    }
};

static const struct ScrollArrowsTemplate sDexOrderScrollArrowsTemplate = {
    .firstArrowType = 2,
    .firstX = 200,
    .firstY = 19,
    .secondArrowType = 3,
    .secondX = 200,
    .secondY = 141,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

static const struct WindowTemplate sWindowTemplate_CategoryMonIcon = {
    .bg = 2,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

static const struct WindowTemplate sWindowTemplate_CategoryMonInfo = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 0,
    .width = 8,
    .height = 5,
    .paletteNum = 0,
    .baseBlock = 0x0000
};

const struct WindowTemplate sWindowTemplate_DexEntry_MonPic = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 3,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x01a8
};

//separate window need load for larger species that sit too low otherwise, as 
//I don't currently have an elevation value I can use to put them at different space 
//within window, I can only raise window
const struct WindowTemplate sWindowTemplate_DexEntry_MonPic2_Large = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 2,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x02d8
}; //need make 3rd window for mon still too long, think just 3 elves
//uxie mespirit and azelf
//thinkm can just put a conditional where using first list to continue if species matches any of those 3
//or just put otehr window there..

const struct WindowTemplate sWindowTemplate_DexEntry_MonPic3_Highest = {
    .bg = 1,
    .tilemapLeft = 19,
    .tilemapTop = 1,
    .width = 8,
    .height = 8,
    .paletteNum = 9,
    .baseBlock = 0x0348
};

const struct WindowTemplate sWindowTemplate_DexEntry_SpeciesStats = {
    .bg = 1,
    .tilemapLeft = 2,
    .tilemapTop = 2,
    .width = 13,
    .height = 8,
    .paletteNum = 0,
    .baseBlock = 0x0208
};

const struct WindowTemplate sWindowTemplate_DexEntry_FlavorText = {
    .bg = 1,
    .tilemapLeft = 0,
    .tilemapTop = 10,
    .width = 30,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x0250
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonIcon = {
    .bg = 2,
    .tilemapLeft = 1,
    .tilemapTop = 2,
    .width = 4,
    .height = 4,
    .paletteNum = 10,
    .baseBlock = 0x01a8
};

const struct WindowTemplate sWindowTemplate_AreaMap_SpeciesName = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 2,
    .width = 10,
    .height = 5,
    .paletteNum = 0,
    .baseBlock = 0x01b8
};

const struct WindowTemplate sWindowTemplate_AreaMap_Size = {
    .bg = 2,
    .tilemapLeft = 2,
    .tilemapTop = 7,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01d5
};

const struct WindowTemplate sWindowTemplate_AreaMap_Area = {
    .bg = 2,
    .tilemapLeft = 18,
    .tilemapTop = 2,
    .width = 10,
    .height = 2,
    .paletteNum = 0,
    .baseBlock = 0x01e9
};

const struct WindowTemplate sWindowTemplate_AreaMap_MonTypes = {
    .bg = 2,
    .tilemapLeft = 5,
    .tilemapTop = 6,
    .width = 9,
    .height = 2,
    .paletteNum = 11,
    .baseBlock = 0x01fd
};

const struct WindowTemplate sWindowTemplate_AreaMap_Kanto = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 4,
    .width = 12,
    .height = 9,
    .paletteNum = 0,
    .baseBlock = 0x020d
};

static const struct WindowTemplate sWindowTemplate_AreaMap_OneIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 4,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0279
};

static const struct WindowTemplate sWindowTemplate_AreaMap_TwoIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 7,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0285
};

static const struct WindowTemplate sWindowTemplate_AreaMap_ThreeIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 10,
    .width = 4,
    .height = 3,
    .paletteNum = 0,
    .baseBlock = 0x0292
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FourIsland = {
    .bg = 2,
    .tilemapLeft = 13,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x029d
};

static const struct WindowTemplate sWindowTemplate_AreaMap_FiveIsland = {
    .bg = 2,
    .tilemapLeft = 17,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02ad
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SixIsland = {
    .bg = 2,
    .tilemapLeft = 21,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02bd
};

static const struct WindowTemplate sWindowTemplate_AreaMap_SevenIsland = {
    .bg = 2,
    .tilemapLeft = 25,
    .tilemapTop = 13,
    .width = 4,
    .height = 4,
    .paletteNum = 0,
    .baseBlock = 0x02cd
};

struct {
    const struct WindowTemplate * window;
    const u32 * tiles;          //changed from tilemap idk of difference if any
} const sAreaMapStructs_SeviiIslands[] = {
    {&sWindowTemplate_AreaMap_OneIsland,   sTilemap_AreaMap_OneIsland},
    {&sWindowTemplate_AreaMap_TwoIsland,   sTilemap_AreaMap_TwoIsland},
    {&sWindowTemplate_AreaMap_ThreeIsland, sTilemap_AreaMap_ThreeIsland},
    {&sWindowTemplate_AreaMap_FourIsland,  sTilemap_AreaMap_FourIsland},
    {&sWindowTemplate_AreaMap_FiveIsland,  sTilemap_AreaMap_FiveIsland},
    {&sWindowTemplate_AreaMap_SixIsland,   sTilemap_AreaMap_SixIsland},
    {&sWindowTemplate_AreaMap_SevenIsland, sTilemap_AreaMap_SevenIsland},
};

static const u16 sCategoryPageIconWindowBg[] = INCBIN_U16("graphics/pokedex/unk_845228C.bin");

//Category page Circular window mon icon x/y;
//Rectangular window x/y mon info caught num name & image
static const u8 sPageIconCoords_1Mon[1][4] = {
    {0x0b, 0x03, 0x0b, 0x0b},
};

static const u8 sPageIconCoords_2Mons[2][4] = {
    {0x03, 0x03, 0x0b, 0x03},
    {0x12, 0x09, 0x0a, 0x0b},
};

static const u8 sPageIconCoords_3Mons[3][4] = {
    {0x01, 0x02, 0x09, 0x02},
    {0x0b, 0x09, 0x03, 0x0b},
    {0x15, 0x03, 0x15, 0x0b}
};

static const u8 sPageIconCoords_4Mons[4][4] = {
    {0x00, 0x02, 0x06, 0x03},
    {0x07, 0x0a, 0x00, 0x0c},
    {0x0f, 0x0a, 0x16, 0x0b},
    {0x16, 0x02, 0x0f, 0x04}
};//left in hex

const u8 (*const sCategoryPageIconCoords[])[4] = {
    sPageIconCoords_1Mon,
    sPageIconCoords_2Mons,
    sPageIconCoords_3Mons,
    sPageIconCoords_4Mons,
};

static const u8 *const sDexCategoryNamePtrs[] = {
    gText_DexCategory_GrasslandPkmn,
    gText_DexCategory_ForestPkmn,
    gText_DexCategory_WatersEdgePkmn,
    gText_DexCategory_SeaPkmn,
    gText_DexCategory_CavePkmn,
    gText_DexCategory_MountainPkmn,
    gText_DexCategory_RoughTerrainPkmn,
    gText_DexCategory_UrbanPkmn,
    gText_DexCategory_RarePkmn,
};

const u16 sPalette_Silhouette[] = INCBIN_U16("graphics/pokedex/unk_8452368.gbapal");

static const u8 sDexScreenPageTurnColumns[][30] = {
    {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 5, 11, 17, 23, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 2,  4,  5,  7,  8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26, 28, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  7,  8,  9, 10, 11, 12, 13, 15, 16, 17, 19, 20, 21, 23, 24, 25, 27, 28, 29, 30, 30, 30, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 30, 30},
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
};

static const struct ScrollArrowsTemplate sScrollArrowsTemplate_CategoryMenu = {
    .firstArrowType = 0,
    .firstX = 16,
    .firstY = 80,
    .secondArrowType = 1,
    .secondX = 224,
    .secondY = 80,
    .fullyUpThreshold = 0,
    .fullyDownThreshold = 0,
    .tileTag = 2000,
    .palTag = 0xFFFF,
    .palNum = 1,
};

const struct CursorStruct sCursorStruct_CategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 64,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

#include "data/pokemon/pokedex_categories.h"

void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_PokedexScreen(void)
{
    if (!gPaletteFade.active || IsDma3ManagerBusyWithBgCopy())
    {
        RunTasks(); //believe tasks are from DexScreen_loadResources
        RunTextPrinters();
        AnimateSprites();
        BuildOamBuffer();
    }
    else
    {
        UpdatePaletteFade();
    }
}

//looks to be a good plae to put, last view index
void DexScreen_LoadResources(void) //look into equiv emerald function, may be what I need
{
    bool8 natDex;
    u8 taskId;

    natDex = IsNationalPokedexEnabled();
    m4aSoundVSyncOff();
    SetVBlankCallback(NULL);
    ResetPaletteFade();
    ResetSpriteData();
    ResetTasks();
    ScanlineEffect_Stop();
    ResetBgsAndClearDma3BusyFlags(TRUE);
    InitBgsFromTemplates(0, sBgTemplates, NELEMS(sBgTemplates));
    SetBgTilemapBuffer(3, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(2, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(1, (u16 *)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(0, (u16 *)Alloc(BG_SCREEN_SIZE));
    if (natDex)
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sNatDexTiles, BG_SCREEN_SIZE, 0, 0);
    else
        DecompressAndLoadBgGfxUsingHeap(3, (void *)sKantoDexTiles, BG_SCREEN_SIZE, 0, 0);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    m4aSoundVSyncOn();
    SetVBlankCallback(VBlankCB);
    EnableInterrupts(INTR_FLAG_VBLANK);
    taskId = CreateTask(Task_PokedexScreen, 0);//actually think its equiv to pokedexListf
    sPokedexScreenData = Alloc(sizeof(struct PokedexScreenData)); //think  listItems equivalent to pokemonListCount  in EE, which is 0 at start and built w dex IMPORTANT
    *sPokedexScreenData = sDexScreenDataInitialState;
    sPokedexScreenData->taskId = taskId; //without below value graphic gets broken
    sPokedexScreenData->listItems = Alloc(NATIONAL_DEX_COUNT * sizeof(struct ListMenuItem)); //AsparagusEduardo from rhh mentnioed this could be problamatic
    sPokedexScreenData->numSeenNational = DexScreen_GetDexCount(FLAG_GET_SEEN, 1);  //need look into how ee (actualy basic emerald logic) does the dex it loads in pieces
    sPokedexScreenData->numOwnedNational = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 1);//rather than all at once, which is what I had in mind
    sPokedexScreenData->numSeenKanto = DexScreen_GetDexCount(FLAG_GET_SEEN, 0);
    sPokedexScreenData->numOwnedKanto = DexScreen_GetDexCount(FLAG_GET_CAUGHT, 0);
    SetBGMVolume_SuppressHelpSystemReduction(0x80);//think I'm better understanding the listitem thing, it uses nationaldexcount to  make a list item and index for every mon
    ChangeBgX(0, 0, 0);     //but think those values don't get populated until the later function getorderedlist count sometjhing
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    gPaletteFade.bufferTransferDisabled = TRUE;
    if (natDex)
        LoadPalette(sNationalDexPalette, BG_PLTT_ID(0), sizeof(sNationalDexPalette)); //instead of sizeof was 0x200
    else
        LoadPalette(sKantoDexPalette, BG_PLTT_ID(0), sizeof(sKantoDexPalette));
    FillBgTilemapBufferRect(3, 0x001, 0,  0, 32, 32, 0);
    FillBgTilemapBufferRect(2, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(1, 0x000, 0,  0, 32, 32, 17);
    FillBgTilemapBufferRect(0, 0x003, 0,  0, 32,  2, 15);
    FillBgTilemapBufferRect(0, 0x000, 0,  2, 32, 16, 17);
    FillBgTilemapBufferRect(0, 0x003, 0, 18, 32,  2, 15);
}

void CB2_OpenPokedexFromStartMenu(void)
{
    DexScreen_LoadResources();
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetMainCallback2(CB2_PokedexScreen);
    //SetHelpContext(HELPCONTEXT_POKEDEX);
}

#define FREE_IF_NOT_NULL(ptr0) ({ void *ptr = (ptr0); if (ptr) Free(ptr); })

bool8 DoClosePokedex(void)
{
    switch (gMain.state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gMain.state++;
        return FALSE;
    case 1:
        if (!gPaletteFade.active)
            gMain.state = 2;
        else
            UpdatePaletteFade();
        return FALSE;
    case 2:
        FREE_IF_NOT_NULL(sPokedexScreenData->listItems);
        FREE_IF_NOT_NULL(sPokedexScreenData);
        FreeAllWindowBuffers();
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(0));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(1));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(2));
        FREE_IF_NOT_NULL(GetBgTilemapBuffer(3));
        BGMVolumeMax_EnableHelpSystemReduction();
        break;
    }
    return TRUE;
}

void CB2_ClosePokedex(void)
{
    if (DoClosePokedex())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    }
}

//could also put it here, so isnt triged excesively
//looked further and its perfect, this called in creation and in case for closing dex list, so only need to add it here to both set and clear
static void Task_PokedexScreen(u8 taskId) //appears be top menu
{
    int i;
    switch (sPokedexScreenData->state)
    {
    case 0:
        sPokedexScreenData->CurrentIndexValue = 0; //works, also added on clear
        sPokedexScreenData->unlockedCategories = 0;
        for (i = 0; i < 9; i++)
            sPokedexScreenData->unlockedCategories |= (DexScreen_IsCategoryUnlocked(i) << i);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        SetMainCallback2(CB2_ClosePokedex);
        DestroyTask(taskId);
        break;
    case 2:
        DexScreen_InitGfxForTopMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);
        if (gPaletteFade.bufferTransferDisabled)
        {
            gPaletteFade.bufferTransferDisabled = FALSE;
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0, RGB_WHITEALPHA);
        }
        else
            BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);  //was 0xFFFF7FFF
        sPokedexScreenData->state = 5;
        break;
    case 5: //can't tell where modeSelectCursorPosBak is getting a value from where it seems to only be set in places I'm not navigating too (now) or yet
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL); //ah this funtion is  assignign it
        if (IsNationalPokedexEnabled())
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_NatDex, &sPokedexScreenData->modeSelectCursorPosBak);
        else
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sScrollArrowsTemplate_KantoDex, &sPokedexScreenData->modeSelectCursorPosBak);
        sPokedexScreenData->state = 6;//think this is end of just displaying the main dex page, after this it takes inpputs for navigation
        break;
    case 6:
        sPokedexScreenData->modeSelectInput = ListMenu_ProcessInput(sPokedexScreenData->modeSelectListMenuId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            switch (sPokedexScreenData->modeSelectInput)
            {
            case LIST_CANCEL:
                sPokedexScreenData->state = 1;
                break;
            case DEX_CATEGORY_GRASSLAND:
            case DEX_CATEGORY_FOREST:
            case DEX_CATEGORY_WATERS_EDGE:
            case DEX_CATEGORY_SEA:
            case DEX_CATEGORY_CAVE:
            case DEX_CATEGORY_MOUNTAIN:
            case DEX_CATEGORY_ROUGH_TERRAIN:
            case DEX_CATEGORY_URBAN:
            case DEX_CATEGORY_RARE:
                if (DexScreen_IsCategoryUnlocked(sPokedexScreenData->modeSelectInput))
                {
                    RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                    sPokedexScreenData->category = sPokedexScreenData->modeSelectInput;
                    BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                    sPokedexScreenData->state = 7;
                }
                break;
            case DEX_MODE(NUMERICAL_KANTO):
            case DEX_MODE(NUMERICAL_NATIONAL):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9;
                break;
            case DEX_MODE(ATOZ):
            case DEX_MODE(TYPE):
            case DEX_MODE(LIGHTEST):
            case DEX_MODE(SMALLEST):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId); //remove scroll arrow for previous menu, in prep loading next one
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - DEX_CATEGORY_COUNT; //selects mode i.e which list generate based on selection
                sPokedexScreenData->characteristicOrderMenuItemsAbove = sPokedexScreenData->characteristicOrderMenuCursorPos = 0;
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9; //...welp it was as simple as changing this  to 9 and now goes to dex list page not cat page
                break;
            }
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        sPokedexScreenData->pageNum = 0;
        sPokedexScreenData->categoryCursorPosInPage = 0;
        sPokedexScreenData->parentOfCategoryMenu = 0;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu;
        sPokedexScreenData->state = 0;
        break;
    case 8:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
        sPokedexScreenData->state = 0;
        break;
    case 9:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->modeSelectItemsAbove);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder; //this list function for setting up dex list
        sPokedexScreenData->state = 0;
        break;
    }//removes all stuff for main page, then ends this function as you are moving away from front page of dex
}

static void DexScreen_InitGfxForTopMenu(void)
{
    struct ListMenuTemplate listMenuTemplate;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 30, 20, 17);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 30, 20, 17);
    sPokedexScreenData->modeSelectWindowId = AddWindow(&sWindowTemplate_ModeSelect);
    sPokedexScreenData->selectionIconWindowId = AddWindow(&sWindowTemplate_SelectionIcon);
    sPokedexScreenData->dexCountsWindowId = AddWindow(&sWindowTemplate_DexCounts);
    if (IsNationalPokedexEnabled())
    {
        listMenuTemplate = sListMenuTemplate_NatDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId; //assigns cursor pos and items above from this below in ListMenuInitInternal via ListMenuInit
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0)); //ok this sets cursor pos, which is passed in the other function,
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Seen, 0, 2, 0); //is where menu starts i.e what value it opens on
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 13, 0); //i.e the row, I think itemsabove, shows 
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenKanto, 52, 13, 2);//how many items in lilst to put above teh selection
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 24, 0);//if zero you are at top of list?
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenNational, 52, 24, 2);//seems no? cant tell what items above does here
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Owned, 0, 37, 0);//items above seems work same but at value of n-1
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 48, 0); //if select 2 it will sart you 1 value lower?
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedKanto, 52, 48, 2);//ok I understand the effect now but not the purpose
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 59, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedNational, 52, 59, 2);
    }
    else
    {
        listMenuTemplate = sListMenuTemplate_KantoDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->modeSelectItemsAbove);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Seen, 0, 9, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numSeenKanto, 32, 21, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Owned, 0, 37, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numOwnedKanto, 32, 49, 2);
    }
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokedexTableOfContents, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOK);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_GFX);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);
    PutWindowTilemap(sPokedexScreenData->dexCountsWindowId);
    CopyWindowToVram(sPokedexScreenData->dexCountsWindowId, COPYWIN_GFX);
}

static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (!onInit)
        PlaySE(SE_SELECT);
    if (itemIndex == LIST_CANCEL)
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconTiles_Cancel, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconPals_Cancel, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    else
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconGfxPtrs[itemIndex].tiles, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconGfxPtrs[itemIndex].pal, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    }
    PutWindowTilemap(sPokedexScreenData->selectionIconWindowId);
    CopyWindowToVram(sPokedexScreenData->selectionIconWindowId, COPYWIN_GFX);
}

static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y) //pret eventually made u32 not s, so will have to go through and adjust,
{
    if (itemId >= DEX_CATEGORY_COUNT || sPokedexScreenData->unlockedCategories & (1 << itemId))
        ListMenuOverrideSetColors(TEXT_COLOR_WHITE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_GREY);
    else
        ListMenuOverrideSetColors(TEXT_DYNAMIC_COLOR_1, TEXT_COLOR_TRANSPARENT, TEXT_DYNAMIC_COLOR_2);
}

//vsonic IMPORTANT this is the function I need, it sets everyting for display of firered dex list
static void Task_DexScreen_NumericalOrder(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId); //needed to return list size, butalso to run funciton logic
        sPokedexScreenData->state = 2;//countmons ^ used to tell size of list , changing thing itself didn't affet load times
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_InitGfxForNumericalOrderList();//orderedDexCount used here to make list count, actually building the list
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA); //same as before was 0xFFFF7FFF
        sPokedexScreenData->state = 5;
        break;
    case 5://modeSelectListMenuId set by ListMenuInit in DexScreen_InitGfxForTopMenu function paasses values cursor pos to the backup here
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL); //but this uses cursorposbak, assuming a backup value?
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();//idk why this ^ is in case 5 & 6 doesn't appear to do anything in 5?
        sPokedexScreenData->state = 6;//could possibly be a good fit to, put initial load basedon index/cursor here?  in case 5
        break;//yeah think that may be it
    case 6://thinking need replace ListMenu_ProcessInput, to control how it would go from here? , without process input list doesn't scroll, Only B press works
        //sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId); //think this is end of dispaly then goes into navigation away from this page
        sPokedexScreenData->characteristicMenuInput = DexScreen_ProcessInput(sPokedexScreenData->orderedListMenuTaskId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);//creates top arrow?
        if (JOY_NEW(A_BUTTON))
        {
            if ((sPokedexScreenData->characteristicMenuInput >> 16) & 1) //pretty much if actually selected someting, so only if pressed A
            {
                sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7; //go to mons dex entry
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1; //close dex list
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_DexScreen_ShowMonPage;
        sPokedexScreenData->state = 0;
        break;
    }
}

/*
// u16 ignored is passed but never used - /for port remove ignored, put this in place of ListMenu_ProcessInput think shold work,
//functions used here ported to bottom of file
static u16 TryDoPokedexScroll(u16 selectedMon) //vsonic IMPORTANT  //think equiv ListMenu_ProcessInput
{
    u8 scrollTimer;
    u8 scrollMonIncrement;
    u8 i;
    u16 startingPos;
    u8 scrollDir = 0;

    if (JOY_HELD(DPAD_UP) && (selectedMon > 0)) //selected mon here is more position in the list, i.e not 0 and not end of list
    {
        scrollDir = 1;
        selectedMon = GetNextPosition(1, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        CreateScrollingPokemonSprite(1, selectedMon);
        CreateMonListEntry(1, selectedMon); //put so list updates w scroll. ok makes sense
        PlaySE(SE_DEX_SCROLL);//tested and this does indeed only preclude scrolling up and down with dpad not left and right
        //createmonlistentry was the entry for updating based on scroll, so removing that stopped the list updating by not via moving left 
    }
    else if (JOY_HELD(DPAD_DOWN) && (selectedMon < sPokedexScreenData->pokemonListCount - 1))
    {
        scrollDir = 2;
        selectedMon = GetNextPosition(0, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        CreateScrollingPokemonSprite(2, selectedMon);
        CreateMonListEntry(2, selectedMon);
        PlaySE(SE_DEX_SCROLL);
    }
    else if (JOY_NEW(DPAD_LEFT) && (selectedMon > 0))
    {
        startingPos = selectedMon;

        for (i = 0; i < 9; i++) //think this is somehow the update, 8 list per page on EE so think this it?
            selectedMon = GetNextPosition(1, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);
        sPokedexScreenData->pokeBallRotation += 16 * (selectedMon - startingPos);
        ClearMonSprites();
        CreateMonSpritesAtPos(selectedMon, 0xE); //this is the left right for createmonlistentry, function is called through this
        PlaySE(SE_DEX_PAGE);
    }
    else if (JOY_NEW(DPAD_RIGHT) && (selectedMon < sPokedexScreenData->pokemonListCount - 1))
    {
        startingPos = selectedMon;
        for (i = 0; i < 9; i++) //has left and right move by 7, in firered moves by 9
            selectedMon = GetNextPosition(0, selectedMon, 0, sPokedexScreenData->pokemonListCount - 1);//for porting need top 3 lines and createmonlistentry for left right
        sPokedexScreenData->pokeBallRotation += 16 * (selectedMon - startingPos);
        ClearMonSprites();
        CreateMonSpritesAtPos(selectedMon, 0xE); - replace these

        CreateMonListEntry(0, selectedMon); //believe not needed? for emerald because it displays mon pick as scroll, so think skip this use of the function
    SetGpuReg(REG_OFFSET_BG2VOFS, sPokedexScreenData->initialVOffset); //ok think was wrong PRETTY SURE THIS, is left right scroll and that first arg is scroll direction
        //1 and 2 are up and down respectively, and zero is left right
    sPokedexScreenData->listVOffset = 0;
    sPokedexScreenData->listMovingVOffset = 0;    don't konw if need all, or just createmonlistentry 0

        PlaySE(SE_DEX_PAGE);
    }

    if (scrollDir == 0)
    {
        // Left/right input just snaps up/down, no scrolling
        sPokedexScreenData->scrollSpeed = 0;
        return selectedMon;
    }
    //think most this below is irrelevant for port, along w scroll speed/increment stuff
    //emerald speeds up to max, while firered has one constant max speed when held.
    //so think can ignore everthing below other than the return?

    scrollMonIncrement = sScrollMonIncrements[sPokedexScreenData->scrollSpeed / 4];
    scrollTimer = sScrollTimers[sPokedexScreenData->scrollSpeed / 4];
    sPokedexScreenData->scrollTimer = scrollTimer;
    sPokedexScreenData->maxScrollTimer = scrollTimer;
    sPokedexScreenData->scrollMonIncrement = scrollMonIncrement;
    sPokedexScreenData->scrollDirection = scrollDir;
    sPokedexScreenData->pokeBallRotationStep = scrollMonIncrement / 2;
    UpdateDexListScroll(sPokedexScreenData->scrollDirection, sPokedexScreenData->scrollMonIncrement, sPokedexScreenData->maxScrollTimer);
    if (sPokedexScreenData->scrollSpeed < 12) //^says dexList but seems has nothing to do w list and is just mon icons and the the pokeball when scrolling?
        sPokedexScreenData->scrollSpeed++;
    return selectedMon;
}
*/

//vsonic IMPORTANT, what builds the dex list
static void DexScreen_InitGfxForNumericalOrderList(void) //important
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu; //template info for displaying dex list mon
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount; //changign this doesnt chagne load time
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);//think this the important value //passes template to use to make page
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokemonListNoColor, TEXT_CENTER);//above line and this paired, fill buffer, than print onto space, same as two below
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX); //then copies two windows to ram, meaning actual building part is DexScreen_InitListMenuForOrderedList
}

//changing list here does nothing, think becuase changed case for category to no longer go to list?
static void Task_DexScreen_CharacteristicOrder(u8 taskId) //changes here also seemed to have no effect?
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(BG_PLTT_ID(1), 0);
        ListMenuLoadStdPalAt(BG_PLTT_ID(2), 1);
        sPokedexScreenData->orderedDexCount = DexScreen_CountMonsInOrderedList(sPokedexScreenData->dexOrderId);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = Task_PokedexScreen;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCharacteristicListMenu();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateDexOrderScrollArrows();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->characteristicMenuInput = ListMenu_ProcessInput(sPokedexScreenData->orderedListMenuTaskId);
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if (((sPokedexScreenData->characteristicMenuInput >> 16) & 1) && !DexScreen_LookUpCategoryBySpecies(sPokedexScreenData->characteristicMenuInput))
            {
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        sPokedexScreenData->parentOfCategoryMenu = 1;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu; 
        sPokedexScreenData->state = 0;
        break;
    }
}

//doesn't do anything, was potentially for other pages that used to go from category pages but I changed?
//either way this isn't what I need to change I believe
static void DexScreen_CreateCharacteristicListMenu(void) //vsonic like numericla dex lit but for teh non numerical lists i.e weight a-z type etc.
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 17);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId); //think this the important value,// removing this doesn't affect load times
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_SearchNoColor, TEXT_CENTER);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

//vsonic IMPORTANT also relevant for dex change plans,
//need make read like emerald load dex in pieces nto all mon
//think equivalent to CreatePokedexList in EE
static u16 DexScreen_CountMonsInOrderedList(u8 orderIdx) //this function returns size of list, but ALSO sets cursor position callback, when opening for first time
{
    
    int selectedIndex;
    u16 *itemsAbove_p, *cursorPos_p;


    switch (orderIdx)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        cursorPos_p = &sPokedexScreenData->kantoOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case DEX_ORDER_ATOZ:    
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        cursorPos_p = &sPokedexScreenData->characteristicOrderMenuCursorPos; //think see now why it always defaults to 0, they share same value 
        itemsAbove_p = &sPokedexScreenData->characteristicOrderMenuItemsAbove; //while national and kanto have their own,
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        cursorPos_p = &sPokedexScreenData->nationalOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }
    
    selectedIndex = *cursorPos_p + *itemsAbove_p;

    return DexScreen_CreateList_ReturnCount(orderIdx,selectedIndex); //should hopefully work the same, just look better - works

    //can put everythin gbelow this in a funtion, use like process input, to assign ret, have it do funtion logic and do return value u16 ret
    //need take argument orderIdx, and selectedIndex, put most arguments inside function, leave only ret selectedIndex & itemsabove and cursorPos in this function

    
}

//vsonic IMPORTANT
//need put those cursor changes here as well for them to track, nvm, since got working no need for new cursors
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order) //belive this is actual dex list build, i.e what builds it at once
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->kantoOrderMenuCursorPos, sPokedexScreenData->kantoOrderMenuItemsAbove);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->characteristicOrderMenuCursorPos, sPokedexScreenData->characteristicOrderMenuItemsAbove);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        sPokedexScreenData->orderedListMenuTaskId = ListMenuInitInRect(template, sListMenuRects_OrderedList, sPokedexScreenData->nationalOrderMenuCursorPos, sPokedexScreenData->nationalOrderMenuItemsAbove);
        break;
    }
}


//and here
static void DexScreen_DestroyDexOrderListMenu(u8 order)
{
    switch (order)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->kantoOrderMenuCursorPos, &sPokedexScreenData->kantoOrderMenuItemsAbove);
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->characteristicOrderMenuCursorPos, &sPokedexScreenData->characteristicOrderMenuItemsAbove);
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        DestroyListMenuTask(sPokedexScreenData->orderedListMenuTaskId, &sPokedexScreenData->nationalOrderMenuCursorPos, &sPokedexScreenData->nationalOrderMenuItemsAbove);
        break;
    }
}

static u8 DexScreen_CreateDexOrderScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sDexOrderScrollArrowsTemplate;
    if (sPokedexScreenData->orderedDexCount > sListMenuTemplate_OrderedListMenu.maxShowed)
        template.fullyDownThreshold = sPokedexScreenData->orderedDexCount - sListMenuTemplate_OrderedListMenu.maxShowed;
    else
        template.fullyDownThreshold = 0;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

struct PokedexListItem
{
    u16 species;
    bool8 seen:1;
    bool8 caught:1;
};

static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y)
{
    u32 itemId_ = itemId; //potentially revise later when change itemId stuff to u32
    u16 species = itemId_;
    bool8 seen = (itemId_ >> 16) & 1;  // not used but required to match
    bool8 caught = (itemId_ >> 17) & 1;
    u8 type1;
    DexScreen_PrintMonDexNo(sPokedexScreenData->numericalOrderWindowId, FONT_SMALL, species, 12, y);
    if (caught)
    {
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, MENU_INFO_ICON_CAUGHT, 0x28, y); //pokeball icon
        type1 = gBaseStats[species].type1;
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, type1 + 1, 0x84, y); //4bpp 32 width between these 2 type icons
        if (type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, gBaseStats[species].type2 + 1, 0xA8, y);
    }
}


#define POKEDEX_CATEGORY_CURSOR_DATA
static void Task_DexScreen_CategorySubmenu(u8 taskId)
{
    int pageFlipCmd;
    u8 *ptr;
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 2;
        break;
    case 1:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        HideBg(2);
        HideBg(1);
        switch (sPokedexScreenData->parentOfCategoryMenu)
        {
        case 0:
        default:
            gTasks[taskId].func = Task_PokedexScreen;
            break;
        case 1:
            gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
            break;
        }
        sPokedexScreenData->state = 0;
        break;
    case 2:
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 4;
        break;
    case 4: //believe for accessing category from within pokedex
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateCategoryMenuScrollArrows();
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);
        sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
        pageFlipCmd = 0;
        if (JOY_NEW(A_BUTTON) && DexScreen_GetSetPokedexFlag(sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage], FLAG_GET_SEEN, TRUE))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 12;
            break;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_LEFT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage != 0)
            {
                sPokedexScreenData->categoryCursorPosInPage--;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 1;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_RIGHT))
        {
            if (sPokedexScreenData->categoryCursorPosInPage < sPokedexScreenData->numMonsOnPage - 1)
            {
                sPokedexScreenData->categoryCursorPosInPage++;
                PlaySE(SE_SELECT);
                break;
            }
            else
                pageFlipCmd = 2;
        }
        if (pageFlipCmd == 0)
            pageFlipCmd = DexScreen_InputHandler_GetShoulderInput();
        switch (pageFlipCmd)
        {
        case 0: // No action
            break;
        case 1: // Left
            while (sPokedexScreenData->pageNum > sPokedexScreenData->firstPageInCategory)
            {
                sPokedexScreenData->pageNum--;
                if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 8;
                    break;
                }
            }
            if (sPokedexScreenData->state != 8)
                sPokedexScreenData->state = 6;
            break;
        case 2: // Right
            while (sPokedexScreenData->pageNum < sPokedexScreenData->lastPageInCategory - 1)
            {
                sPokedexScreenData->pageNum++;
                if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, sPokedexScreenData->pageNum))
                {
                    sPokedexScreenData->state = 10;
                    break;
                }
            }
            if (sPokedexScreenData->state != 10)
                sPokedexScreenData->state = 6;
            break;
        }
        if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 6;
        }
        break;
    case 6:
    case 7:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
        ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
        BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
        sPokedexScreenData->state = 1;
        break;
    case 8:
    case 10:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        ListMenuUpdateCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0, 0xA0, 0);
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->state++;
        break;
    case 9:
        if (DexScreen_FlipCategoryPageInDirection(0))
        {
            sPokedexScreenData->categoryCursorPosInPage = sPokedexScreenData->numMonsOnPage - 1;
            sPokedexScreenData->state = 5;
        }
        break;
    case 11:
        if (DexScreen_FlipCategoryPageInDirection(1))
        {
            sPokedexScreenData->categoryCursorPosInPage = 0;
            sPokedexScreenData->state = 5;
        }
        break;
    case 12:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->pageSpecies[sPokedexScreenData->categoryCursorPosInPage];
        PlaySE(SE_SELECT);
        sPokedexScreenData->state = 14;
        break;
    case 13:
        RemoveDexPageWindows();
        sPokedexScreenData->state = 4;
        break;
    case 14:
        DexScreen_DrawMonDexPage(FALSE); //from category page go to dex entry page
        sPokedexScreenData->state = 15;
        break;
    case 15:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
        // fallthrough
    case 16:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
            {
                sPokedexScreenData->data[0]--;
            }
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 17;
        }
        break;
    case 17: //navigation, think attempt put scrollmon vertical here, vsonic, hopefully simple as but need it to update cat page num as well
        if (JOY_NEW(A_BUTTON)) //believe can'tuse tryscrollmon vertical, as that explicitly uses dex list stuff and not category org stuff
        {
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);//but need compare w default to see how changed, if need make scroll logic
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 21;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 18;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 18:
        DexScreen_CreateCategoryListGfx(FALSE);
        DexScreen_DexPageZoomEffectFrame(0, 6);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 19;
        break;
    case 19:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 6;
        sPokedexScreenData->state++;
        // fallthrough
    case 20:
        if (sPokedexScreenData->data[1])
        {
            if (sPokedexScreenData->data[0])
            {
                sPokedexScreenData->data[1]--;
                FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 1;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 13;
        }
        break;
    case 21:
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state = 22;
        break;
    case 22:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 23;
        break;
    case 23:
        if (JOY_NEW(A_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 26;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 24;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 24:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 25;
        break;
    case 25:
        DexScreen_DrawMonDexPage(FALSE); //pressing B return from Area page, in category menu/task
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 17;
        break;
    case 26:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 18;
        break;
    }
}

static u8 DexScreen_CreateCategoryMenuScrollArrows(void)
{
    struct ScrollArrowsTemplate template = sScrollArrowsTemplate_CategoryMenu;
    template.fullyUpThreshold = sPokedexScreenData->firstPageInCategory;
    template.fullyDownThreshold = sPokedexScreenData->lastPageInCategory - 1;
    sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->modeSelectCursorPosBak);
}

/*
 * Returns 1 to flip pages left, 2 to flip pages right, 0 for no action
 */
static int DexScreen_InputHandler_GetShoulderInput(void)
{
    switch (gSaveBlock2Ptr->optionsButtonMode)
    {
    case OPTIONS_BUTTON_MODE_L_EQUALS_A:
        // Using the JOY_HELD and JOY_NEW macros here does not match!
        if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_LEFT))
            return 1;
        else if ((gMain.heldKeys & R_BUTTON) && (gMain.newKeys & DPAD_RIGHT))
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_LR:
        if (gMain.newKeys & L_BUTTON)
            return 1;
        else if (gMain.newKeys & R_BUTTON)
            return 2;
        else
            return 0;
    case OPTIONS_BUTTON_MODE_HELP:
    default:
        return 0;
    }
}

static void Task_DexScreen_ShowMonPage(u8 taskId)//think task show dex entry from the scrolled list page, so possibly what I need  //vsonic
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        HideBg(2);
        HideBg(1);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sPokedexScreenData->numMonsOnPage = 1;
        DexScreen_DrawMonDexPage(FALSE); //believe selecting a mon from the numerical list, navigate to ex entry page?
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        BeginNormalPaletteFade(~0x8000, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 7;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        else if (JOY_NEW(DPAD_UP) && DexScreen_TryScrollMonsVertical(1)) //use of this function means if able to scroll in that direction
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else if (JOY_NEW(DPAD_DOWN) && DexScreen_TryScrollMonsVertical(0)) //vsonic attempt use add scrolling between category dex entires
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 6:
        HideBg(2);
        HideBg(1);
        sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
        sPokedexScreenData->state = 2;
        break;
    case 7:
        DexScreen_DrawMonAreaPage();
        sPokedexScreenData->state = 8;
        break;
    case 8:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 9;
        break;
    case 9:
        if (JOY_NEW(A_BUTTON))
        {
            BeginNormalPaletteFade(~0x8000, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 12;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);
            sPokedexScreenData->state = 10;
        }
        else
        {
            DexScreen_InputHandler_StartToCry();
        }
        break;
    case 10:
        DexScreen_DestroyAreaScreenResources();
        sPokedexScreenData->state = 11;
        break;
    case 11:
        DexScreen_DrawMonDexPage(FALSE); //same as other, Press B return from area page
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 5;
        break;
    case 12:
        DexScreen_DestroyAreaScreenResources();
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 1;
        break;
    }
}

//vsonic
static bool32 DexScreen_TryScrollMonsVertical(u8 direction) //vsonic important think    seems equivalent of GetNextPosition but writes arguments instead of taking them
{
    int selectedIndex;
    u16 *itemsAbove_p, *cursorPos_p;

    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        cursorPos_p = &sPokedexScreenData->kantoOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case DEX_ORDER_ATOZ:
    case DEX_ORDER_TYPE:
    case DEX_ORDER_LIGHTEST:
    case DEX_ORDER_SMALLEST:
        cursorPos_p = &sPokedexScreenData->characteristicOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->characteristicOrderMenuItemsAbove;
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        cursorPos_p = &sPokedexScreenData->nationalOrderMenuCursorPos;
        itemsAbove_p = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }
    
    selectedIndex = *cursorPos_p + *itemsAbove_p;
    if (direction) // Seek up   //but think this applies to both up and left, since they both go in that direction based on emerald
    {
        if (selectedIndex == 0) //ok has going up vs going down, but where is logic for the scroll from left right inputs?
            return FALSE; //ok that's all handled in list menu file, done in ListMenu_ProcessInput function


        //if (selectedIndex >= 10) //oh realized I can do more, since it scrolls fast now
            DexScreen_LoadIndex(255, SCROLL_UP, selectedIndex, 1); //works
        //selectedIndex--;
        while (--selectedIndex >= 0) //Should be while (--selectedIndex >= 0) without the selectedIndex-- in the body or before the while at all, but this is needed to match.
        {
            
            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1)
            {
                break;
            }
            //selectedIndex--;
        }

        if (selectedIndex < 0)
        {
            return FALSE;
        }
    }
    else // Seek down
    {
        if (selectedIndex == sPokedexScreenData->orderedDexCount - 1)
        {
            return FALSE;
        }
        // depending on where you are compared to the limit of the dex
        //meaning if you're scrolling the full range without hittnig a limit
        //it gets kind of slow, and since I want game to be fast unless
        //I can somehow shorten the actual fade in fade out time, (which I THINK is possible)
        //then i would need to lower the number to cut the processing load
        //nvm I need to lower the range, the process goes before the fade 
        //so the fade would be delayed regardless of shortening it,
        DexScreen_LoadIndex(255, SCROLL_DOWN, selectedIndex, 1);//discovered issue when scroll on entry need value large enough to cover blank entries or wont' scroll
        //ok bounds hold, seems works without issue, huh even with the far larger value, it doesn't add to load time, nice :D
        //ok this is good enough, nvm tested w full dex and its much slower
        //when having to navigate filled values and can't just write blank entries

        //selectedIndex++;
        while (++selectedIndex < sPokedexScreenData->orderedDexCount) //Should be while (++selectedIndex < sPokedexScreenData->orderedDexCount) without the selectedIndex++ in the body or before the while at all, but this is needed to match.
        {            

            if ((sPokedexScreenData->listItems[selectedIndex].index >> 16) & 1) //I think should put the dpad loads within these loops?
                break;
            //selectedIndex++;
        }
        if (selectedIndex >= sPokedexScreenData->orderedDexCount)
        {
            return FALSE;
        }
    }
    sPokedexScreenData->characteristicMenuInput = sPokedexScreenData->listItems[selectedIndex].index; //the mon you're on

    // as this part is CLEARLY only for being read on a list, hmm but removing it ONLY removed ability to scroll dex entries..
    //this is translating cursor position on list with where you are since you've moving "above" it in the info pages
    if (sPokedexScreenData->orderedDexCount > sListMenuTemplate_OrderedListMenu.maxShowed)//if can scroll, and total list longer than max shown
    {
        if (selectedIndex < 4) //both instances of 4, mean to scroll vertically when would be within 4 spaces/rows of max shown from either top or bottom
        {
            *cursorPos_p = 0;
            *itemsAbove_p = selectedIndex;
        }
        else if (selectedIndex >= (sPokedexScreenData->orderedDexCount - 4)) //if can scroll i.e is not 4 away from end of list
        {
            *cursorPos_p = (sPokedexScreenData->orderedDexCount - sListMenuTemplate_OrderedListMenu.maxShowed); //changed from flat 9s
            *itemsAbove_p = selectedIndex + sListMenuTemplate_OrderedListMenu.maxShowed - (sPokedexScreenData->orderedDexCount);
        }
        else
        {
            *cursorPos_p = selectedIndex - 4;
            *itemsAbove_p = 4;
        } //ok so this isn't the right place for change I want, ok removing this just prevents changing dex entry shown as move up down, so not what I need.
    } //uses orderedDexCount as max value, and that's set with funcntion, but with my change, dex count is dif from actual total size should be
    //so think best to make other struct value to replace curent use of orderedDexCount in getcount function,
    //so it'd show end of list,  or keep orderedDexCount as just amount loaded in list curr, but make new value to be what the max list should be
    //rather than my preload value. DexListMax
    else
    {
        *cursorPos_p = 0;
        *itemsAbove_p = selectedIndex;
    }
    return TRUE;
}

//duplicate effect functions for port effect
//vsonic Important, add on to this stuff to expand orderedDexCount
//think need return
static s32 DexScreen_ProcessInput(u8 listTaskId)//replace listmenu process input
{
    
    struct ListMenu *list = (struct ListMenu *)gTasks[listTaskId].data;
    struct ListMenuTemplate template;

    u32 selectedIndex = list->cursorPos + list->itemsAbove;
    //u16 ndex_num = selectedIndex + DEX_MAX_SHOWN;

    if (JOY_NEW(A_BUTTON))
    {
        return list->template.items[list->cursorPos + list->itemsAbove].index;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        return LIST_CANCEL;
    }
    else if (gMain.newAndRepeatedKeys & DPAD_UP)
    {
        //if (selectedIndex >= list->template.maxShowed)//fix works betternow
        //changed load function can do without this now
        DexScreen_LoadIndex(list->template.maxShowed, SCROLL_UP, selectedIndex, 1);//building w scroll, not building based on index pos when press b, from info page
        ListMenuChangeSelection(list, TRUE, 1, FALSE); //count here seems to be how much to move by   
        return LIST_NOTHING_CHOSEN;
    }
    else if (gMain.newAndRepeatedKeys & DPAD_DOWN)
    {

        
        DexScreen_LoadIndex(list->template.maxShowed, SCROLL_DOWN, selectedIndex, 1);
        ListMenuChangeSelection(list, TRUE, 1, TRUE); //think issue could be htis, its increasing place by 1, simple fix is putting it after the scroll increment
        return LIST_NOTHING_CHOSEN;//tested works, need add to tryscrollmon vertical as well
    }
    else // try to move by one window scroll
    {
        bool16 rightButton, leftButton;
        switch (list->template.scrollMultiple)
        {
        case LIST_NO_MULTIPLE_SCROLL:
        default:
            leftButton = FALSE;
            rightButton = FALSE;
            break;
        case LIST_MULTIPLE_SCROLL_DPAD:
            leftButton = gMain.newAndRepeatedKeys & DPAD_LEFT;
            rightButton = gMain.newAndRepeatedKeys & DPAD_RIGHT;
            break;
        case LIST_MULTIPLE_SCROLL_L_R:
            leftButton = gMain.newAndRepeatedKeys & L_BUTTON;
            rightButton = gMain.newAndRepeatedKeys & R_BUTTON;
            break;
        }
        if (leftButton) //think take page from this setup  else if (JOY_NEW(DPAD_UP) && DexScreen_TryScrollMonsVertical(1))
        {
            
            //if (selectedIndex >= 13)
                DexScreen_LoadIndex(13, SCROLL_UP, selectedIndex, list->template.maxShowed);
            ListMenuChangeSelection(list, TRUE, list->template.maxShowed, FALSE); //think count ishow much to move by, since this is 9 other is 1
            return LIST_NOTHING_CHOSEN;
        }
        else if (rightButton)
        {
            DexScreen_LoadIndex(13, SCROLL_DOWN, selectedIndex, list->template.maxShowed); //14 / or 13 to cover where scroll, so always full window //works
            ListMenuChangeSelection(list, TRUE, list->template.maxShowed, TRUE);
            return LIST_NOTHING_CHOSEN;
        }
        else
        {
            return LIST_NOTHING_CHOSEN;
        }
    }
}//there is issue only with scrolling up, (just left as ofnow) in case of things that could exceed the list limit, but that doesn't happen when doing down.

static void DexScreen_RemoveWindow(u8 *windowId_p)
{
    if (*windowId_p != 0xFF)
    {
        RemoveWindow(*windowId_p);
        *windowId_p = 0xFF;
    }
}

static void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx)
{
    u8 textColor[3];
    switch (colorIdx)
    {
    case 0:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 3;
        break;
    case 1:
        textColor[0] = 0;
        textColor[1] = 5;
        textColor[2] = 1;
        break;
    case 2:
        textColor[0] = 0;
        textColor[1] = 15;
        textColor[2] = 14;
        break;
    case 3:
        textColor[0] = 0;
        textColor[1] = 11;
        textColor[2] = 1;
        break;
    case 4:
        textColor[0] = 0;
        textColor[1] = 1;
        textColor[2] = 2;
        break;
    }
    AddTextPrinterParameterized4(windowId, fontId, x, y, fontId == FONT_SMALL ? 0 : 1, 0, textColor, -1, str);
}

static void DexScreen_PrintNum3LeadingZeroes(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{
    u8 buff[4];
    buff[0] = (num / 100) + CHAR_0;
    buff[1] = ((num %= 100) / 10) + CHAR_0;
    buff[2] = (num % 10) + CHAR_0;
    buff[3] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}

static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
{
    u8 buff[4];
    int i;
    buff[0] = (num / 100) + CHAR_0;
    buff[1] = ((num %= 100) / 10) + CHAR_0;
    buff[2] = (num % 10) + CHAR_0;
    buff[3] = EOS;
    for (i = 0; i < 3; i++)
    {
        if (buff[i] != CHAR_0)
            break;
        buff[i] = CHAR_SPACE;
    }
    DexScreen_AddTextPrinterParameterized(windowId, fontId, buff, x, y, colorIdx);
}

static u32 DexScreen_GetDefaultPersonality(int species)
{
    switch (species)
    {
    case SPECIES_SPINDA:
        return gSaveBlock2Ptr->pokedex.spindaPersonality;
    case SPECIES_UNOWN:
        return gSaveBlock2Ptr->pokedex.unownPersonality;
    default:
        return 0;
    }
}

static void DexScreen_LoadMonPicInWindow(u8 windowId, u16 species, u16 paletteOffset)
{
    LoadMonPicInWindow(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, paletteOffset >> 4, windowId);
}

static void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y)
{
    u16 dexNum = SpeciesToNationalPokedexNum(species);
    DexScreen_AddTextPrinterParameterized(windowId, fontId, gText_PokedexNo, x, y, 0);
    DexScreen_PrintNum3LeadingZeroes(windowId, fontId, dexNum, x + 9, y, 0);
}

s8 DexScreen_GetSetPokedexFlag(u16 nationalDexNo, u8 caseId, bool8 indexIsSpecies)
{
    u8 index;
    u8 bit;
    u8 mask;
    s8 retVal;

    if (indexIsSpecies)
        nationalDexNo = SpeciesToNationalPokedexNum(nationalDexNo);

    nationalDexNo--;
    index = nationalDexNo / 8;
    bit = nationalDexNo % 8;
    mask = 1 << bit;
    retVal = 0;
    switch (caseId)
    {
    case FLAG_GET_SEEN:
        if (gSaveBlock2Ptr->pokedex.seen[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_GET_CAUGHT:
        if (gSaveBlock2Ptr->pokedex.owned[index] & mask)
        {
            // Anticheat
            if ((gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock2Ptr->pokedex.seen[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_SET_SEEN:
        gSaveBlock2Ptr->pokedex.seen[index] |= mask;
        // Anticheat
        gSaveBlock1Ptr->seen1[index] |= mask;
        gSaveBlock1Ptr->seen2[index] |= mask;
        break;
    case FLAG_SET_CAUGHT:
        gSaveBlock2Ptr->pokedex.owned[index] |= mask;
        break;
    }
    return retVal;
    //return 1;   //dex test value  //other in event_data.c IsNationalPokedexEnabled function
} //for some reason navigation only works with my dex test breaks, without them everything gets fucked so EVEN MORE FUCKING WORK

static u16 DexScreen_GetDexCount(u8 caseId, bool8 whichDex) //vsonic IMPORTANT, right now have more nat dex species values than I actually have array spots or dex entries
{
    u16 count = 0;
    u16 i;

    switch (whichDex)
    {
    case 0: // Kanto
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))  //for seen amount but doesnt make appear in dex
                count++;
        }
        break;
    case 1: // National
        for (i = 0; i < NATIONAL_SPECIES_COUNT; i++) //so same as other places can't use NATIONAL_DEX_COUNT for this rn, to use nat count, need update search arrays, and add entry data
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))//changed back only reason this was issue was I was using numseen as size, which used this
                count++;

        }
        break; //changed from NATIONAL_DEX_COUNT
    }
    return count;
}

static void DexScreen_PrintControlInfo(const u8 *src)
{
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, src, 236 - GetStringWidth(FONT_SMALL, src, 0), 2, 4);
}

bool8 DexScreen_DrawMonPicInCategoryPage(u16 species, u8 slot, u8 numSlots)
{
    struct WindowTemplate template;
    numSlots--;
    CopyToBgTilemapBufferRect_ChangePalette(3, sCategoryPageIconWindowBg, sCategoryPageIconCoords[numSlots][slot][0], sCategoryPageIconCoords[numSlots][slot][1], 8, 8, slot + 5);
    if (sPokedexScreenData->categoryMonWindowIds[slot] == 0xFF)
    {
        template = sWindowTemplate_CategoryMonIcon;
        template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][0];
        template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][1];
        template.paletteNum = slot + 1;
        template.baseBlock = slot * 64 + 8;
        sPokedexScreenData->categoryMonWindowIds[slot] = AddWindow(&template);
        FillWindowPixelBuffer(sPokedexScreenData->categoryMonWindowIds[slot], PIXEL_FILL(0));
        DexScreen_LoadMonPicInWindow(sPokedexScreenData->categoryMonWindowIds[slot], species, slot * 16 + 16);
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);
        CopyWindowToVram(sPokedexScreenData->categoryMonWindowIds[slot], COPYWIN_GFX);
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonWindowIds[slot]);

    if (sPokedexScreenData->categoryMonInfoWindowIds[slot] == 0xFF)
    {
        if (species != SPECIES_NONE)
        {
            template = sWindowTemplate_CategoryMonInfo;
            template.tilemapLeft = sCategoryPageIconCoords[numSlots][slot][2];
            template.tilemapTop = sCategoryPageIconCoords[numSlots][slot][3];
            template.baseBlock = slot * 40 + 0x108;
            sPokedexScreenData->categoryMonInfoWindowIds[slot] = AddWindow(&template);
            CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonInfoBgTiles, 0, 0);
            DexScreen_PrintMonDexNo(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_SMALL, species, 12, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->categoryMonInfoWindowIds[slot], FONT_NORMAL, gSpeciesNames[species], 2, 13, 0);
            if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE))
                BlitBitmapRectToWindow(sPokedexScreenData->categoryMonInfoWindowIds[slot], sDexScreen_CaughtIcon, 0, 0, 8, 8, 2, 3, 8, 8);
            PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);
            CopyWindowToVram(sPokedexScreenData->categoryMonInfoWindowIds[slot], COPYWIN_GFX);
        }
    }
    else
        PutWindowTilemap(sPokedexScreenData->categoryMonInfoWindowIds[slot]);

    return TRUE;
}

static void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonWindowIds[i]);
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonInfoWindowIds[i]);
    }
}

static void DexScreen_PrintCategoryPageNumbers(u8 windowId, u16 currentPage, u16 totalPages, u16 x, u16 y)
{
    u8 buffer[30];
    u8 *ptr = StringCopy(buffer, gText_Page);
    ptr = ConvertIntToDecimalStringN(ptr, currentPage, STR_CONV_MODE_RIGHT_ALIGN, 2);
    *ptr++ = CHAR_SLASH;
    ptr = ConvertIntToDecimalStringN(ptr, totalPages, STR_CONV_MODE_RIGHT_ALIGN, 2);
    DexScreen_PrintStringWithAlignment(buffer, TEXT_RIGHT);
}

static bool8 DexScreen_CreateCategoryListGfx(bool8 justRegistered)
{
    FillBgTilemapBufferRect_Palette0(3, 2, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
    DexScreen_CreateCategoryPageSpeciesList(sPokedexScreenData->category, sPokedexScreenData->pageNum);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    if (justRegistered)
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_CENTER);
    }
    else
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], TEXT_LEFT);
        DexScreen_PrintCategoryPageNumbers(0, DexScreen_PageNumberToRenderablePages(sPokedexScreenData->pageNum), DexScreen_PageNumberToRenderablePages(sPokedexScreenData->lastPageInCategory - 1), 160, 2);
    }
    CopyWindowToVram(0, COPYWIN_GFX);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (!justRegistered)
        DexScreen_PrintControlInfo(gText_PickFlipPageCheckCancel);
    CopyWindowToVram(1, COPYWIN_GFX);

    if (justRegistered) //to override pulling species from an existing cat page
    {
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->dexSpecies, 0, 1);   //WORKS!!!

    }//slot needs to be 0
        
    if (!justRegistered)
    {
    if (sPokedexScreenData->pageSpecies[0] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[0], 0, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[1] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[1], 1, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[2] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[2], 2, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->pageSpecies[3] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->pageSpecies[3], 3, sPokedexScreenData->numMonsOnPage);
    }
    return FALSE;
}

static void DexScreen_CreateCategoryPageSelectionCursor(u8 cursorPos)
{
    int i;
    u32 palIdx;

    if (cursorPos == 0xFF)
    {
        for (i = 0; i < 4; i++)
        {
            LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));   //LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x52 + 0x10 * i, 2);
            LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));   //LoadPalette(&sDexScreen_CategoryCursorPals[1], 0x58 + 0x10 * i, 2);
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x141, PLTT_SIZEOF(1));
        sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
    }
    else
    {
        sPokedexScreenData->categoryPageSelectionCursorTimer++;
        if (sPokedexScreenData->categoryPageSelectionCursorTimer == 16)
            sPokedexScreenData->categoryPageSelectionCursorTimer = 0;
        palIdx = sPokedexScreenData->categoryPageSelectionCursorTimer >> 2;
        for (i = 0; i < 4; i++)
        {
            if (i == cursorPos)
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 3], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
            else
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[0], PLTT_ID(i) + PLTT_ID(5) + 2 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
                LoadPalette(&sDexScreen_CategoryCursorPals[1], PLTT_ID(i) + PLTT_ID(5) + 8 + BG_PLTT_OFFSET, PLTT_SIZEOF(1));
            }
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[2 * palIdx + 2], OBJ_PLTT_ID(4) + 1, PLTT_SIZEOF(1));
    }
}

static void DexScreen_UpdateCategoryPageCursorObject(u8 taskId, u8 cursorPos, u8 numMonsInPage)
{
    numMonsInPage--;
    ListMenuUpdateCursorObject(taskId, sCategoryPageIconCoords[numMonsInPage][cursorPos][2] * 8, sCategoryPageIconCoords[numMonsInPage][cursorPos][3] * 8, 0);
}

bool8 DexPage_TileBuffer_CopyCol(const u16 *srcBuf, u8 srcCol, u16 *dstBuf, u8 dstCol)
{
    int i;
    const u16 *src = &srcBuf[srcCol];
    u16 *dst = &dstBuf[dstCol];
    for (i = 0; i < 20; i++)
    {
        *dst = *src;
        dst += 32;
        src += 32;
    }
    return FALSE;
}

bool8 DexPage_TileBuffer_FillCol(u16 tileNo, u16 *tileBuf, u8 x)
{
    int i;
    u16 *dst = &tileBuf[x];
    for (i = 0; i < 20; i++)
    {
        *dst = tileNo;
        dst += 32;
    }
    return FALSE;
}

bool8 DexScreen_TurnCategoryPage_BgEffect(u8 page)
{
    int dstCol;
    int srcCol;
    u16 *bg1buff = GetBgTilemapBuffer(1);
    u16 *bg2buff = GetBgTilemapBuffer(2);
    u16 *bg3buff = GetBgTilemapBuffer(3);
    u16 *bg1mem = sPokedexScreenData->bgBufsMem + 0x800;
    u16 *bg2mem = sPokedexScreenData->bgBufsMem + 0x400;
    u16 *bg3mem = sPokedexScreenData->bgBufsMem + 0x000;
    for (dstCol = 0; dstCol < 30; dstCol++)
    {
        srcCol = sDexScreenPageTurnColumns[page][dstCol];
        if (srcCol == 30)
        {
            DexPage_TileBuffer_FillCol(0x000, bg1buff, dstCol);
            DexPage_TileBuffer_FillCol(0x000, bg2buff, dstCol);
            DexPage_TileBuffer_FillCol(0x00C, bg3buff, dstCol);
        }
        else
        {
            DexPage_TileBuffer_CopyCol(bg1mem, srcCol, bg1buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg2mem, srcCol, bg2buff, dstCol);
            DexPage_TileBuffer_CopyCol(bg3mem, srcCol, bg3buff, dstCol);
        }
    }
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(3);
    return FALSE;
}

/*
 * Direction = 0: Left; 1: Right
 */
static bool8 DexScreen_FlipCategoryPageInDirection(u8 direction)
{
    u16 color;
    if (IsNationalPokedexEnabled())
        color = sNationalDexPalette[7];
    else
        color = sKantoDexPalette[7];
    switch (sPokedexScreenData->data[0])
    {
    case 0:
        sPokedexScreenData->bgBufsMem = Alloc(3 * BG_SCREEN_SIZE);
        if (direction)
            sPokedexScreenData->data[0] = 6;
        else
            sPokedexScreenData->data[0] = 2;
        break;
    case 1:
        Free(sPokedexScreenData->bgBufsMem);
        return TRUE;
        // Go left
    case 2:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 16, color);
        sPokedexScreenData->data[0]++;
        break;
    case 3:
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 4:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 0, color);
        DexScreen_CreateCategoryListGfx(FALSE);
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        FillBgTilemapBufferRect_Palette0(3, 0x00C, 0, 0, 30, 20);
        FillBgTilemapBufferRect_Palette0(2, 0x000, 0, 0, 32, 20);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);

        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 5:
        if (sPokedexScreenData->data[1] < 10)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]++;
        }
        else
        {
            sPokedexScreenData->data[0] = 1;
        }
        break;
        // Go right
    case 6:
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->bgBufsMem[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->bgBufsMem[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->bgBufsMem[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);

        sPokedexScreenData->data[1] = 9;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 7:
        if (sPokedexScreenData->data[1] != 0)
        {
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]--;
        }
        else
        {
#ifdef BUGFIX
            DexScreen_TurnCategoryPage_BgEffect(0);
#else
            DexScreen_TurnCategoryPage_BgEffect(sPokedexScreenData->data[0]);
#endif
            BeginNormalPaletteFade(0x00007FFF, 0, 16, 16, color);
            sPokedexScreenData->data[0]++;
        }
        break;
    case 8:
        gPaletteFade.bufferTransferDisabled = TRUE;
        DexScreen_CreateCategoryListGfx(FALSE);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(3);
        sPokedexScreenData->data[0]++;
        break;
    case 9:
        gPaletteFade.bufferTransferDisabled = FALSE;
        BeginNormalPaletteFade(0x00007FFF, 0, 16, 0, color);
        sPokedexScreenData->data[0] = 1;
        break;
    }
    return FALSE;
}

#define POKEDEX_PAGE_FUNCTIONS
// Scale from 0 to 6
void DexScreen_DexPageZoomEffectFrame(u8 bg, u8 scale)
{
    u8 tileLeft, tileTop, width, height;
    s16 left, top, divY;

    if (!sPokedexScreenData->numMonsOnPage)
    {
        tileLeft = sCategoryPageIconCoords[0][0][2];
        tileTop = sCategoryPageIconCoords[0][0][3];
    }
    else
    {
        tileLeft = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][2];
        tileTop = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->categoryCursorPosInPage][3];
    }

    width = 6 + (scale * 4);
    height = 3 + (scale * 2);
    if (width >= 28) // Make sure it's not wider than the screen
        width = 28;
    if (height >= 14) // Make sure it's not taller than the screen
        height = 14;

    left = tileLeft - ((scale * 4) / 2);
    top = tileTop - ((scale * 2) / 2);
    if ((left + width + 2) >= 30) // Don't wrap right...
        left -= ((left + width + 2) - 30);
    else if (left < 0) // ... left ...
        left = 0;
    if ((top + height + 2) >= 18) // ... down ...
        top -= ((top + height + 2) - 18);
    else if (top < 2) // or up.
        top = 2;

    //either adjust this or height value
    divY = (top + 1) + ((height / 2) - 1);// The horizontal divider    //this determines space for dex entries/ this was my change to give more room for text space
            //to keep dividing line where it is,  changes to tilemap top, must be contrasted by double the change by height, in the opposite
            //i.e if I decrease top by 1 I must increase height by 2
    // Top edge
    FillBgTilemapBufferRect_Palette0(bg, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);

    // Bottom edge
    FillBgTilemapBufferRect_Palette0(bg, 10, left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 11, left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(10), left + 1 + width, top + 1 + height, 1, 1);

    // Left edge
    FillBgTilemapBufferRect_Palette0(bg, 6, left, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 7, left, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, 9, left, divY + 1, 1, top + height - divY);

    // Right edge
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(7), left + 1 + width, divY, 1, 1);
    FillBgTilemapBufferRect_Palette0(bg, BG_TILE_H_FLIP(9), left + 1 + width, divY + 1, 1, top + height - divY);

    // Interior
    FillBgTilemapBufferRect_Palette0(bg, 1, left + 1, top + 1, width, divY - top - 1);
    FillBgTilemapBufferRect_Palette0(bg, 8, left + 1, divY, width, 1);
    FillBgTilemapBufferRect_Palette0(bg, 2, left + 1, divY + 1, width, top + height - divY);
}

void DexScreen_PrintMonCategory(u8 windowId, u16 species, u8 x, u8 y)
{
    u8 * categoryName;
    u8 index, categoryStr[12];

    species = SpeciesToNationalPokedexNum(species);

    categoryName = (u8 *)gPokedexEntries[species].categoryName;
    index = 0;
    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
#if REVISION == 0
        while ((categoryName[index] != CHAR_SPACE) && (index < 11))
#else
        while ((categoryName[index] != EOS) && (index < 11))
#endif
        {
            categoryStr[index] = categoryName[index];
            index++;
        }
    }
    else
    {
        while (index < 11)
        {
            categoryStr[index] = CHAR_QUESTION_MARK;
            index++;
        }
    }

    categoryStr[index] = EOS;

    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, categoryStr, x, y, 0);
    x += GetStringWidth(FONT_SMALL, categoryStr, 0);
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, gText_PokedexPokemon, x, y, 0);
}

void DexScreen_PrintMonHeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 height;
    u32 inches, feet;
    const u8 *labelText;
    u8 buffer[32];
    u8 i;

    species = SpeciesToNationalPokedexNum(species);
    height = gPokedexEntries[species].height;
    labelText = gText_HT;

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 5;
    buffer[i++] = CHAR_SPACE;

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        inches = 10000 * height / 254; // actually tenths of inches here
        if (inches % 10 >= 5)
            inches += 10;
        feet = inches / 120;
        inches = (inches - (feet * 120)) / 10;
        if (feet / 10 == 0)
        {
            buffer[i++] = 0;
            buffer[i++] = feet + CHAR_0;
        }
        else
        {
            buffer[i++] = feet / 10 + CHAR_0;
            buffer[i++] = feet % 10 + CHAR_0;
        }
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = inches / 10 + CHAR_0;
        buffer[i++] = inches % 10 + CHAR_0;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
        buffer[i++] = EOS;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_SGL_QUOTE_RIGHT;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_DBL_QUOTE_RIGHT;
    }

    buffer[i++] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

void DexScreen_PrintMonWeight(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 weight;
    u32 lbs;
    bool8 output;
    const u8 * labelText;
    const u8 * lbsText;
    u8 buffer[32];
    u8 i;
    u32 j;

    species = SpeciesToNationalPokedexNum(species);
    weight = gPokedexEntries[species].weight;
    labelText = gText_WT;
    lbsText = gText_Lbs;

    i = 0;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 5;

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        lbs = (weight * 100000) / 4536; // Convert to hundredths of lb

        // Round up to the nearest 0.1 lb
        if (lbs % 10 >= 5)
            lbs += 10;

        output = FALSE;

        if ((buffer[i] = (lbs / 100000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 100000;
        if ((buffer[i] = (lbs / 10000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 10000;
        if ((buffer[i] = (lbs / 1000) + CHAR_0) == CHAR_0 && !output)
        {
            buffer[i++] = CHAR_SPACE;
        }
        else
        {
            output = TRUE;
            i++;
        }

        lbs %= 1000;
        buffer[i++] = (lbs / 100) + CHAR_0;
        lbs %= 100;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = (lbs / 10) + CHAR_0;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_PERIOD;
        buffer[i++] = CHAR_QUESTION_MARK;
    }
    buffer[i++] = CHAR_SPACE;
    buffer[i++] = EXT_CTRL_CODE_BEGIN;
    buffer[i++] = EXT_CTRL_CODE_MIN_LETTER_SPACING;
    buffer[i++] = 0;

    for (j = 0; j < 33 - i && lbsText[j] != EOS; j++)
        buffer[i + j] = lbsText[j];

    buffer[i + j] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, FONT_SMALL, buffer, x, y, 0);
}

void DexScreen_PrintMonFlavorText(u8 windowId, u16 species, u8 x, u8 y)
{
    struct TextPrinterTemplate printerTemplate;
    u16 length;
    s32 xCenter;

    species = SpeciesToNationalPokedexNum(species);

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, FALSE))
    {
        printerTemplate.currentChar = gPokedexEntries[species].description;
        printerTemplate.windowId = windowId;
        printerTemplate.fontId = FONT_NORMAL;
        printerTemplate.letterSpacing = 1;
        printerTemplate.lineSpacing = 0;
        printerTemplate.unk = 0;
        printerTemplate.fgColor = 1;
        printerTemplate.bgColor = 0;
        printerTemplate.shadowColor = 2;

        length = GetStringWidth(FONT_NORMAL, gPokedexEntries[species].description, 0);
        xCenter = x + (240 - length) / 2;

        if (xCenter > 0)
            x = xCenter;
        else
            x = 0;

        printerTemplate.x = x;
        printerTemplate.y = y;
        printerTemplate.currentX = x;
        printerTemplate.currentY = y;

        AddTextPrinter(&printerTemplate, TEXT_SKIP_DRAW, NULL);
    }
}

void DexScreen_DrawMonFootprint(u8 windowId, u16 species, u8 x, u8 y)
{
    u16 i, j, unused, tileIdx;
    u8 footprintPixel, footprintTile;
    u8 * buffer;
    u8 * footprint;

    if (!(DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE)))
        return;
    footprint = (u8 *)(gMonFootprint_None); //this is what where replaced  gfootprint stuff
    buffer = gDecompressionBuffer;
    unused = 0;
    tileIdx = 0;

    // Expand 1bpp to 4bpp
    for (i = 0; i < 32; i++)
    {
        footprintPixel = footprint[i];
        for (j = 0; j < 4; j++)
        {
            footprintTile = 0;
            if (footprintPixel & (1 << (j * 2)))
                footprintTile |= 0x01;
            if (footprintPixel & (2 << (j * 2)))
                footprintTile |= 0x10;
            buffer[tileIdx] = footprintTile;
            tileIdx++;
        }
    }
    BlitBitmapRectToWindow(windowId, buffer, 0, 0, 16, 16, x, y, 16, 16);
}

#define CREATE_POKEDEX_PAGE
static u8 DexScreen_DrawMonDexPage(bool8 justRegistered) //should be able to usse this to breakdown dex navigation this will only exist from a place that lists the mon
{
    u32 i;
    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    for (i = 0; gDexAdjusting[i] != END_LIST; i++)
    {
        if (sPokedexScreenData->dexSpecies == gDexAdjusting[i]) //this works now just need a list of all mon I Need the bigger window for a make it do a loop
            break;
    }
    if (sPokedexScreenData->dexSpecies == SPECIES_AZELF 
    || sPokedexScreenData->dexSpecies == SPECIES_MESPRIT 
    || sPokedexScreenData->dexSpecies == SPECIES_UXIE)
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic3_Highest); //works

    else if (sPokedexScreenData->dexSpecies != gDexAdjusting[i]) //if mon not in list, uses biger window
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic2_Large);
        
    else
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);

    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    // Mon pic
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], PIXEL_FILL(0));
    DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144);     //interestingly using 104 makes it siloutted could use for dexnav vsonic
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    // Species stats
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[1], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[1], FONT_SMALL, sPokedexScreenData->dexSpecies, 0, 1);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[1], FONT_NORMAL, gSpeciesNames[sPokedexScreenData->dexSpecies], 28, 1, 0);
    DexScreen_PrintMonCategory(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 16);
    DexScreen_PrintMonHeight(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 28);
    DexScreen_PrintMonWeight(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 0, 40);
    DexScreen_DrawMonFootprint(sPokedexScreenData->windowIds[1], sPokedexScreenData->dexSpecies, 88, 32);
    PutWindowTilemap(sPokedexScreenData->windowIds[1]);
    CopyWindowToVram(sPokedexScreenData->windowIds[1], COPYWIN_GFX);

    // Dex entry
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[2], PIXEL_FILL(0));
    DexScreen_PrintMonFlavorText(sPokedexScreenData->windowIds[2], sPokedexScreenData->dexSpecies, 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[2]);
    CopyWindowToVram(sPokedexScreenData->windowIds[2], COPYWIN_GFX);

    // Control info - cancel/next buttons
    FillWindowPixelBuffer(1, PIXEL_FILL(15)); //was 255
    if (justRegistered == FALSE)
    {
        DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
        DexScreen_PrintControlInfo(gText_NextDataCancel);
    }
    else
        // Just registered
        DexScreen_PrintControlInfo(gText_Next);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}

u8 RemoveDexPageWindows(void)
{
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[0]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[1]);
    DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[2]);

    return 0;
}

u8 DexScreen_DrawMonAreaPage(void)
{
    int i;
    u8 width, height;
    bool8 monIsCaught;
    s16 left, top;
    u16 speciesId, species;
    u16 kantoMapVoff;

    species = sPokedexScreenData->dexSpecies;
    speciesId = SpeciesToNationalPokedexNum(species);
    monIsCaught = DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, TRUE);
    width = 28;
    height = 14;
    left = 0;
    top = 2;

    FillBgTilemapBufferRect_Palette0(3, 4, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(4), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(4), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_V_FLIP(4), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 5, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_V_FLIP(5), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(3, 6, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, BG_TILE_H_FLIP(6), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(3, 1, left + 1, top + 1, width, height);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    width = 10;
    height = 6;
    left = 1;
    top = 9;

    FillBgTilemapBufferRect_Palette0(0, 29, left, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(29), left + 1 + width, top, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(29), left, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_V_FLIP(29), left + 1 + width, top + 1 + height, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 30, left + 1, top, width, 1);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_V_FLIP(30), left + 1, top + 1 + height, width, 1);
    FillBgTilemapBufferRect_Palette0(0, 31, left, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(0, BG_TILE_H_FLIP(31), left + 1 + width, top + 1, 1, height);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);

    sPokedexScreenData->unlockedSeviiAreas = GetUnlockedSeviiAreas();
    kantoMapVoff = 4;
    // If any of the postgame islands are unlocked, Kanto map needs to be flush with the
    // top of the screen.
    for (i = 3; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
            kantoMapVoff = 0;

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_AreaMap_Kanto);
    CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[0], (void *)sTilemap_AreaMap_Kanto, 0, 0);
    SetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP,
                       GetWindowAttribute(sPokedexScreenData->windowIds[0], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    for (i = 0; i < 7; i++)
        if ((sPokedexScreenData->unlockedSeviiAreas >> i) & 1)
        {
            sPokedexScreenData->windowIds[i + 1] = AddWindow(sAreaMapStructs_SeviiIslands[i].window);
            CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[i + 1], sAreaMapStructs_SeviiIslands[i].tiles, 0, 0);
            SetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP) + kantoMapVoff);
            PutWindowTilemap(sPokedexScreenData->windowIds[i + 1]);
            CopyWindowToVram(sPokedexScreenData->windowIds[i + 1], COPYWIN_GFX);
        }
    sPokedexScreenData->windowIds[8] = AddWindow(&sWindowTemplate_AreaMap_SpeciesName); //also dex number?
    sPokedexScreenData->windowIds[9] = AddWindow(&sWindowTemplate_AreaMap_Size);
    sPokedexScreenData->windowIds[10] = AddWindow(&sWindowTemplate_AreaMap_Area);
    sPokedexScreenData->windowIds[11] = AddWindow(&sWindowTemplate_AreaMap_MonIcon);
    sPokedexScreenData->windowIds[12] = AddWindow(&sWindowTemplate_AreaMap_MonTypes);

    // Draw the mon icon
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[11], PIXEL_FILL(0));
    ListMenu_LoadMonIconPalette(BG_PLTT_ID(10), species);
    ListMenu_DrawMonIconGraphics(sPokedexScreenData->windowIds[11], species, DexScreen_GetDefaultPersonality(species), 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[11]);
    CopyWindowToVram(sPokedexScreenData->windowIds[11], COPYWIN_GFX);

    // Print "Size"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[9], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Size, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[9], FONT_SMALL, gText_Size, (sWindowTemplate_AreaMap_Size.width * 8 - strWidth) / 2, 4, 0);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[9]);
    CopyWindowToVram(sPokedexScreenData->windowIds[9], COPYWIN_GFX);

    // Print "Area"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[10], PIXEL_FILL(0));
    {
        s32 strWidth = GetStringWidth(FONT_SMALL, gText_Area, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[10], FONT_SMALL, gText_Area, (sWindowTemplate_AreaMap_Area.width * 8 - strWidth) / 2, 4, 0);
    }
    SetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[10], WINDOW_TILEMAP_TOP) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[10]);
    CopyWindowToVram(sPokedexScreenData->windowIds[10], COPYWIN_GFX);

    // Print species name
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[8], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[8], FONT_SMALL, species, 0, 4);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[8], FONT_NORMAL, gSpeciesNames[species], 3, 16, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[8]);
    CopyWindowToVram(sPokedexScreenData->windowIds[8], COPYWIN_GFX);

    // Type icons
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[12], PIXEL_FILL(0));
    ListMenuLoadStdPalAt(BG_PLTT_ID(11), 1);

    if (monIsCaught)
    {
        BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type1, 0, 1);
        if (gBaseStats[species].type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type2, 34, 1);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[12]);
    CopyWindowToVram(sPokedexScreenData->windowIds[12], COPYWIN_GFX);

    // Show size comparison
    ResetAllPicSprites();
    LoadPalette(sPalette_Silhouette, OBJ_PLTT_ID(2), PLTT_SIZE_4BPP);

    if (monIsCaught)
    {
        sPokedexScreenData->windowIds[14] = CreateMonPicSprite_HandleDeoxys(species, SHINY_ODDS, DexScreen_GetDefaultPersonality(species), TRUE, 40, 104, 0, 0xFFFF); //was 65535
        gSprites[sPokedexScreenData->windowIds[14]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[14]].oam.matrixNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[14]].pos2.y = gPokedexEntries[speciesId].pokemonOffset; //this is elevation of mon pic
        SetOamMatrix(2, gPokedexEntries[speciesId].pokemonScale, 0, 0, gPokedexEntries[speciesId].pokemonScale);
        sPokedexScreenData->windowIds[15] = CreateTrainerPicSprite(PlayerGenderToFrontTrainerPicId_Debug(gSaveBlock2Ptr->playerGender, TRUE), 1, 80, 104, 0, 0xFFFF); //same as above
        gSprites[sPokedexScreenData->windowIds[15]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[15]].oam.affineMode = ST_OAM_AFFINE_NORMAL;
        gSprites[sPokedexScreenData->windowIds[15]].oam.matrixNum = 1;
        gSprites[sPokedexScreenData->windowIds[15]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[15]].pos2.y = gPokedexEntries[speciesId].trainerOffset;
        SetOamMatrix(1, gPokedexEntries[speciesId].trainerScale, 0, 0, gPokedexEntries[speciesId].trainerScale);
    }
    else
    {
        sPokedexScreenData->windowIds[14] = 0xff;
        sPokedexScreenData->windowIds[15] = 0xff;
    }

    // Create the area markers
    sPokedexScreenData->areaMarkersTaskId = CreatePokedexAreaMarkers(species, TAG_AREA_MARKERS, 3, kantoMapVoff * 8);
    if (GetNumPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId) == 0)
    {
        // No markers, display "Area Unknown"
        BlitBitmapRectToWindow(sPokedexScreenData->windowIds[0], (void *)sBlitTiles_WideEllipse, 0, 0, 88, 16, 4, 28, 88, 16);
        {
            s32 strWidth = GetStringWidth(FONT_SMALL, gText_AreaUnknown, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[0], FONT_SMALL, gText_AreaUnknown, (96 - strWidth) / 2, 29, 0);
        }
    }
    CopyWindowToVram(sPokedexScreenData->windowIds[0], COPYWIN_GFX);

    // Draw the control info
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_AddTextPrinterParameterized(1, FONT_SMALL, gText_Cry, 8, 2, 4);
    DexScreen_PrintControlInfo(gText_CancelPreviousData);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);

    return 1;
}


u8 DexScreen_DestroyAreaScreenResources(void)
{
    int i;

    DestroyPokedexAreaMarkers(sPokedexScreenData->areaMarkersTaskId);

    for (i = 0; i < 13; i++)
        DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[i]);
    if (sPokedexScreenData->windowIds[15] != 0xff)
        FreeAndDestroyTrainerPicSprite(sPokedexScreenData->windowIds[15]);
    if (sPokedexScreenData->windowIds[14] != 0xff)
        FreeAndDestroyMonPicSprite(sPokedexScreenData->windowIds[14]);
    return 0;
}

static int DexScreen_CanShowMonInDex(u16 species)
{
    if (IsNationalPokedexEnabled() == TRUE)
        return TRUE;
    if (SpeciesToNationalPokedexNum(species) <= KANTO_DEX_COUNT)
        return TRUE;
    return FALSE;
}

static u8 DexScreen_CanShowMonInCategory(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;

    for (i = 0; i < 4; i++)
    {
        if (i < count)
        {
            species = gDexCategories[categoryNum].page[pageNum].species[i];
            if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
                return TRUE;
        }
    }
    return FALSE;
}

static bool8 DexScreen_IsCategoryUnlocked(u8 categoryNum)
{
    int i;
    u8 count;

    count = gDexCategories[categoryNum].count;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(categoryNum, i))
            return 1;

    return 0;
}

void DexScreen_CreateCategoryPageSpeciesList(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;
    sPokedexScreenData->numMonsOnPage = 0;

    for (i = 0; i < 4; i++) //max number mon on category page
        sPokedexScreenData->pageSpecies[i] = 0xffff;
    for (i = 0; i < count; i++) //dex page, also limited to 4 to fit
    {
        species = gDexCategories[categoryNum].page[pageNum].species[i];
        if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, FLAG_GET_SEEN, TRUE))
        {
            sPokedexScreenData->pageSpecies[sPokedexScreenData->numMonsOnPage] = gDexCategories[categoryNum].page[pageNum].species[i];
            sPokedexScreenData->numMonsOnPage++;
        }
    }
}

static u8 DexScreen_GetPageLimitsForCategory(u8 category)
{
    int i;
    u8 count, firstPage, lastPage;

    count = gDexCategories[category].count;
    firstPage = 0xff;
    lastPage = 0xff;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(category, i))
        {
            if (firstPage == 0xff)
                firstPage = i;
            lastPage = i;
        }
    if (lastPage != 0xff)
    {
        sPokedexScreenData->firstPageInCategory = firstPage;
        sPokedexScreenData->lastPageInCategory = lastPage + 1;
        return FALSE;
    }
    else
    {
        sPokedexScreenData->firstPageInCategory = 0;
        sPokedexScreenData->lastPageInCategory = 0;
        return TRUE;
    }
}

enum DexCategories {
    Grassland_Pokemon,
    Forest_Pokemon,
    WatersEdge_Pokemon,
    Sea_Pokemon,
    Cave_Pokemon,
    Mountain_Pokemon,
    RoughTerrain_Pokemon,
    Urban_Pokemon,
    Rare_Pokemon,    
};

//still searching but need find a way to replace 
//mon for loading dex stuff on catch
//without neeeding to create a category page for them
static u8 DexScreen_LookUpCategoryBySpecies(u16 species)
{
    int i, j;
    u16 dexSpecies;
    u16 foundSpecies = 0; //check to break out of main loop after find species

    for (i = 0; i < NELEMS(gDexCategories); i++) //change to an i value check make enum to match array
    {   
        
        if (Grassland_Pokemon == i) //written this just cuz felt was more readable
        {
            for (j = 0; j < NELEMS(gDexCategory_GrasslandPkmnlist); j++)
            {
                if (species == gDexCategory_GrasslandPkmnlist[j])
                {
                    foundSpecies = gDexCategory_GrasslandPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }


        if (Forest_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_ForestPkmnlist); j++)
            {
                if (species == gDexCategory_ForestPkmnlist[j])
                {
                    foundSpecies = gDexCategory_ForestPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

            
        if (WatersEdge_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_WatersEdgePkmnlist); j++)
            {
                if (species == gDexCategory_WatersEdgePkmnlist[j])
                {
                    foundSpecies = gDexCategory_WatersEdgePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Sea_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_SeaPkmnlist); j++)
            {
                if (species == gDexCategory_SeaPkmnlist[j])
                {
                    foundSpecies = gDexCategory_SeaPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Cave_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_CavePkmnlist); j++)
            {
                if (species == gDexCategory_CavePkmnlist[j])
                {
                    foundSpecies = gDexCategory_CavePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Mountain_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_MountainPkmnlist); j++)
            {
                if (species == gDexCategory_MountainPkmnlist[j])
                {
                    foundSpecies = gDexCategory_MountainPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (RoughTerrain_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_RoughTerrainPkmnlist); j++)
            {
                if (species == gDexCategory_RoughTerrainPkmnlist[j])
                {
                    foundSpecies = gDexCategory_RoughTerrainPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Urban_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_UrbanPkmnlist); j++)
            {
                if (species == gDexCategory_UrbanPkmnlist[j])
                {
                    foundSpecies = gDexCategory_UrbanPkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }

        if (Rare_Pokemon == i)
        {
            for (j = 0; j < NELEMS(gDexCategory_RarePkmnlist); j++)
            {
                if (species == gDexCategory_RarePkmnlist[j])
                {
                    foundSpecies = gDexCategory_RarePkmnlist[j];
                    break; //break out of inner loop
                }
                    
            }
            
        }
        
        if (foundSpecies)   //realized only need one
            break;  //break out of main loop
        
    }

        //this needed to pass to screendeta->dexspecies to
        //populate dex as well as play correct cry on dex load - need check cry play w volume but from looks should work correctly
        sPokedexScreenData->dexSpecies = dexSpecies = foundSpecies;

        //got it all working, all need is store category, removed need for other values
        //instead of reading dex category struct, it'll fill in the template page with its image species name and dex number, 
        //same as if it actually had a cat page.
        //this saves me a good deal of physical space, and also I just don't want to add a BUNCH of category pages that already move slowly
        //that no one really looks through, it'd just be unnecesary bloat
        if (species == dexSpecies)
        {
            sPokedexScreenData->category = i; //this sets category text, only part I needed from original function      
            
            return FALSE; 
           
        }
        
    return TRUE;
}

static u8 DexScreen_PageNumberToRenderablePages(u16 page)
{
    int i, count;

    for (i = 0, count = 0; i < page; i++)
        if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, i))
            count++;

    return count + 1;
}

void DexScreen_InputHandler_StartToCry(void)
{
    if (JOY_NEW(START_BUTTON))
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
}

u8 DexScreen_RegisterMonToPokedex(u16 species) //now has nat dex, need workaround register mon setup, for cat page, half working dex loads correct not cat page
{
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_SEEN, TRUE);
    DexScreen_GetSetPokedexFlag(species, FLAG_SET_CAUGHT, TRUE);

    //if (!IsNationalPokedexEnabled() && SpeciesToNationalPokedexNum(species) > KANTO_DEX_COUNT)
    //    return CreateTask(Task_DexScreen_RegisterNonKantoMonBeforeNationalDex, 0);

    DexScreen_LoadResources();
    
    DexScreen_LookUpCategoryBySpecies(species);//with nat dex enabled at start am able to trigger full mon caught script, but issue is expansion mon
                                        //dont have a species category page, and without that they can't show up properly, it instead defaults to rattata.
                                        //but I don't want to bloat the category dex with a bunch of extra pages so hopefully I can just display the mon in the category
                                        //and won't need an actual page for them.       vsonic IMPORTANT
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_RegisterMonToPokedex; //again putting here below lookup just in case order matered
    return sPokedexScreenData->taskId;
}

static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId)
{
    DestroyTask(taskId);
}

//for when catching mon, vsonic edit later for double wilds
//think add some kind of loop/check if battle type double wild and caught both mon
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId) //called from above dexScreen register function, which is called only from bs_commands so change need go there
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        DexScreen_GetPageLimitsForCategory(sPokedexScreenData->category);
        if (sPokedexScreenData->pageNum < sPokedexScreenData->firstPageInCategory)
            sPokedexScreenData->pageNum = sPokedexScreenData->firstPageInCategory;
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        if (DoClosePokedex())
            DestroyTask(taskId);
        break;
    case 3:
        DexScreen_CreateCategoryListGfx(TRUE);
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);

        DexScreen_CreateCategoryPageSelectionCursor(0xff);

        sPokedexScreenData->state = 4;
        break;
    case 4:
        gPaletteFade.bufferTransferDisabled = 0;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, 0xffff);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);

        sPokedexScreenData->state = 5;
        break;
    case 5: //think for when mon first caught
        gTasks[taskId].data[0] = 30;
        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, 1); //this seems to have fixed cursor

        if (gTasks[taskId].data[0])
            gTasks[taskId].data[0]--;
        else
        {
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 7;
        }
        break;
    case 7: 
        sPokedexScreenData->state = 8; 
        break;
    case 8:
        DexScreen_DrawMonDexPage(TRUE); 
        sPokedexScreenData->state = 9;
        break;
    case 9:
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->data[1] = 0;
        sPokedexScreenData->state++;
    case 10:
        if (sPokedexScreenData->data[1] < 6)
        {
            if (sPokedexScreenData->data[0])
            {
                DexScreen_DexPageZoomEffectFrame(0, sPokedexScreenData->data[1]);
                CopyBgTilemapBufferToVram(0);
                sPokedexScreenData->data[0] = 4;
                sPokedexScreenData->data[1]++;
            }
            else
                sPokedexScreenData->data[0]--;
        }
        else
        {
            FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(3);
            CopyBgTilemapBufferToVram(2);
            CopyBgTilemapBufferToVram(1);
            CopyBgTilemapBufferToVram(0);

            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, CRY_VOLUME_RS, CRY_PRIORITY_NORMAL);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 11;
        }
        break;
    case 11:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
            sPokedexScreenData->state = 2;
        break;
    }
}

void DexScreen_PrintStringWithAlignment(const u8 * str, s32 mode)
{
    u32 x;

    switch (mode)
    {
    case TEXT_LEFT:
        x = 8;
        break;
    case TEXT_CENTER:
        x = (u32)(240 - GetStringWidth(FONT_NORMAL, str, 0)) / 2;
        break;
    case TEXT_RIGHT:
    default:
        x = 232 - GetStringWidth(FONT_NORMAL, str, 0);
        break;
    }

    DexScreen_AddTextPrinterParameterized(0, FONT_NORMAL, str, x, 2, 4);
}


//building w scroll, not building based on index pos when press b, from info page
//idk what the fuck is wrong but its broken AGAIN somehow, duplicate values on scrolll, not displaying entire list,
//kanto dex is showing 150 values not 151, but if I close and reopen when at end of index it displays correctly so somehting happens
//but ONLY when I effing scroll effing wonderful
//...got it working instantly after gonna pass out now
//issue was just it not properly lining up with other function that created list. smh
//needed + 1 because the natdex stuff subtracts 1, from value
static void DexScreen_LoadIndex(u32 count, u8 direction, int selectedIndex, s8 scroll_increment)//most complete, last thing to do is get search dexes to load in, on last seen entry like numerial ones do
{
    s32 i,j,d;
    bool8 caught;
    bool8 seen;
    struct ListMenu *list = (struct ListMenu *)gTasks[sPokedexScreenData->orderedListMenuTaskId].data; //hopefully works , it does
    s16 ndex_num = selectedIndex;
    u16 Id_limit = IsNationalPokedexEnabled() ? NATIONAL_DEX_COUNT : KANTO_DEX_COUNT;  //for category dex, to limit displayed to kanto dex
    //simple to do but idealy I'd just start with nat dex enabled, so think will leave for now  vsonic


    //want to setup scroll overlap thought would be as simple as when at 0 scroll up sets to ordered dex count
    //and when at ordered dex count and scroll down, set to 0, but issue is index changing function comes AFTER this one,
    //so think wouldn't be able to load because of set boundaries, so would need to put this function after the index changing one?
    //idk that might not work either, point is I would need new boundaries to solve for that,
    //or something to change index itself, like say if ndex_num == 0 and direction scroll up, can change to ordered dex count? adn then it'd just count
    //and then change the functino that adjusts index directly so my ACTUAL cursor position,would be at ordered dex count?

    //yeah think that should work well enough, hard part wouldbe  adjusting the listmenu index changing function,
    //remember its direclty below loadindex in most cases and would NOT want it to change from showmonpage/dex entry
    //for that would want to justbreak as normal, hopefully won't need separate function to preserve that
    //that said its alraedy pretty different in use...vsonic IMPORTANT

    //note would also not want it to flip from using left right, only up and down
    //, looking like I will need a separate function than hmm.

    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        if (direction == SCROLL_DOWN)
        {
            for (i = 0; i <= count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function
                
                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num + i + 1)]; //in lower range print first 10
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gText_5Dashes; //ok the + 1 WAS right, issue was the other part was wrong first, facepalm
                }
                sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num + i + 1);

                if (ndex_num + i == sPokedexScreenData->orderedDexCount) //to stop the function effect so I don't increment passed what I need to
                    break; //needed to prevent graphic glitch from going too high
            }
        }
        else if (direction == SCROLL_UP)
        {
            

            for (i = 0; i < count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                if (ndex_num - i < 0) //to stop the function effect so I don't increment passed what I need to
                    break; //changed worked for preventing breaks, can now remove limiter on function, should hopefullyu fix az
                    //with signed changed, changed from <= to just < think is more correct

                seen = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function
                
                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num - i + 1)]; //in lower range print first 10
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num - i + 1);
            }
        }
        break;
    case DEX_ORDER_ATOZ:
       
        if (direction == SCROLL_DOWN)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Alphabetical); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_CAUGHT, FALSE);
                if (seen)
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j])];
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
        }
        else if (direction == SCROLL_UP)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[j], FLAG_GET_CAUGHT, FALSE); 
                if (seen)
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j])];
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
        }
        break;
    case DEX_ORDER_TYPE: //can't build automatically would need to loop entire species list MANY times, so would take forever
        //now that I'm saving time I MAY be able to build with a function
        
        if (direction == SCROLL_DOWN)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Type); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[j])];
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
        }
        else if (direction == SCROLL_UP)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[j])];
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
        }
        break; //order by type and weight, just wouldn't work with my changes/species expansion would require, going through and creating list by hand
    case DEX_ORDER_LIGHTEST: //this is built by weight, but for identical weight it goes in order of lowest to highest height

        if (direction == SCROLL_DOWN)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Weight); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[j])];
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
        }
        else if (direction == SCROLL_UP)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[j])];
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
        }
        break;
    case DEX_ORDER_SMALLEST:

        if (direction == SCROLL_DOWN)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j <= NELEMS(gPokedexOrder_Height); j++)
            {

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_CAUGHT, FALSE);
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[j])];
                    sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + scroll_increment >= sPokedexScreenData->orderedDexCount && ndex_num + i == sPokedexScreenData->orderedDexCount - 1)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num + i == sPokedexScreenData->orderedDexCount - 1) //to stop the function effect so I don't increment passed what I need to
                        break;  //seems to have no effect?, ok had change to == - 1 to make work, don't know why but it all seems to work now?
                    
                    
                    i++;
                }
            }
        }
        else if (direction == SCROLL_UP)
        {
            for (i = 0, j = sPokedexScreenData->CurrentIndexValue; i <= count && j >= 0; j--)
            { 

                seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[j], FLAG_GET_CAUGHT, FALSE); 
                if (caught)
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[j])];
                    sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[j]);

                    
                    if (i == scroll_increment)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - scroll_increment <= 0 && ndex_num - i == 0)
                        sPokedexScreenData->CurrentIndexValue = j;

                    if (ndex_num - i == 0) //to stop the function effect so I don't increment passed what I need to
                        break; //think putting here should be equivalent
                        
                    i++;
                    
                    
                }
            }
        }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        if (direction == SCROLL_DOWN)
        {
            for (i = 0; i <= count; i++) //can have this be taken by count argument, so its same code for increasing once
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num + i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function

                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num + i + 1)]; //in lower range print first 10
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num + i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num + i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num + i + 1);

                if (ndex_num + i == sPokedexScreenData->orderedDexCount) //to stop the function effect so I don't increment passed what I need to
                    break; //needed to prevent graphic glitch from going too high
            }
        }
        else if (direction == SCROLL_UP)
        {
            for (i = 0; i < count; i++) //can have this be taken by count argument, so its same code for increasing once
            {

                if (ndex_num - i < 0) //to stop the function effect so I don't increment passed what I need to
                    break;

                seen = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_SEEN, FALSE);
                caught = DexScreen_GetSetPokedexFlag(ndex_num - i + 1, FLAG_GET_CAUGHT, FALSE); //since nav function increments value, can't use that in function

                if (seen) //ok using this fixed it, thiknk issue is keeping same structure between, this function and DexScreen_CreateList_ReturnCount
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num - i + 1)]; //in lower range print first 10
                    
                }   
                else
                {
                    sPokedexScreenData->listItems[ndex_num - i].label = gText_5Dashes;
                }
                sPokedexScreenData->listItems[ndex_num - i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num - i + 1);
            }
        }
        break;
    }
}

//this works loadindex doesn't? this builds full list, and rebuilds based on spot when presss B from info page/showmon page
//sigh I can't give up on this, emerald has it working perfectly if I DON'T get it, its just inferior,
//haven't truly been trying, I have emerald built, to solve the non numeric issue I need to look into how
//emeralds search menu works, 
static u16 DexScreen_CreateList_ReturnCount(u8 orderIdx, int selectedIndex) //replacement to simplify new DexScreen_CountMonsInOrderedList logic
{
    u32 entryPos;
    u16 ndex_num;
    u16 ret = NATIONAL_DEX_NONE;
    s32 i,j, d;
    bool8 caught;  //true false
    bool8 seen;
    u16 NumSeen = IsNationalPokedexEnabled() ? sPokedexScreenData->numSeenNational : sPokedexScreenData->numSeenKanto;
    u16 NumCaught = IsNationalPokedexEnabled() ? sPokedexScreenData->numOwnedNational : sPokedexScreenData->numOwnedKanto;
    u16 Id_limit = IsNationalPokedexEnabled() ? NATIONAL_DEX_COUNT : KANTO_DEX_COUNT;  //for category dex, to limit displayed to kanto dex
    //leaving unset for now`, for plans to setup nat dex from start

    entryPos = selectedIndex;
    j = 0; //remove later

    //for non numericals, use num seen and num caught, if 0, loop max shown and just make full blank page
    //if greater than 0, less than or equal to max shown, display that number no blanks
    switch (orderIdx)//for some reason when open another list, and come back, it breaks this list...fucking hell just fucking work, think I had fixed this
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        
        for (i = 0; i <= KANTO_DEX_COUNT; i++)
        {
          

            if (entryPos <= DEX_MAX_SHOWN && i == entryPos) //there's a split between here and the else if, causes some issue
            {
                for (j = 0; j <= DEX_MAX_SHOWN; j++,i++) //was matter of using else if, instea of continuous if, would cause it to skip a cycle, so changed all to if and fixed that bit
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);//still reads value 1 higher than it should be when scrolling
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);//happens when scrolling through info pages too, so something wrong with loadindex function

                            if (seen)
                            {
                                sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)]; //in lower range print first 10
                                
                            }   
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                }
            }

            if (entryPos > DEX_MAX_SHOWN && i == entryPos && entryPos < sPokedexScreenData->orderedDexCount - 4) //loop 10, over i -5 label & index
            {
                /*if (i - DEX_LOWER_FILL < 0) //remember had change variable to s rather than unsigned, to properly compare negative value
                    j = 0; //better way to do this would be with a macro but...
                else
                    j = i - DEX_LOWER_FILL;

                if (entryPos + DEX_UPPER_FILL > sPokedexScreenData->orderedDexCount) //ok think has to be macro, can't reassign define, check stat index check
                    d = sPokedexScreenData->orderedDexCount;
                else
                    d = entryPos + DEX_UPPER_FILL;*/
                //removing for now as could increase load times, and realized it was an issue of scrolling not initial load
                //and increasing scrolling range can be done easier, and is less intensive as wouldn't require loading both directions at once,
                //and it already has built in bounds

                for (j = i - DEX_MAX_SHOWN; j <= entryPos + DEX_MAX_SHOWN; j++) //changed to better fill, because issue w az etc. changess
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE); //attempt expand above, can't scroll if empty space between entries is bigger than first load
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                            if (seen)
                            {
                                sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)];//other print 10 from i minus 5                                    
                            }
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                        if (j > entryPos)
                            i++;

                }
                
            } 
            if (i == entryPos && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                for (j = i - DEX_MAX_SHOWN; j <= sPokedexScreenData->orderedDexCount; j++) //works
                {
                    seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                            if (seen)
                            {
                                sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)];//other print 10 from i minus 5                                    
                            }
                            else
                            {
                                sPokedexScreenData->listItems[j].label = gText_5Dashes;
                            }
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                            ret++;

                        if (j > entryPos)
                            i++;

                }

            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
                sPokedexScreenData->listItems[i].index = 0;
                //sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(i + 1); //fixed
                //ok didn't need that line, was just an issue with my scroll function now fixed
            }
            
            ret = KANTO_DEX_COUNT;
                    
        }
        break;
    case DEX_ORDER_ATOZ: //look into making this load in sections?, think issue is would need to continuously retrigger this function?, not az but all national lists

        for (i = 0; i <= NELEMS(gPokedexOrder_Alphabetical); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[i], FLAG_GET_CAUGHT, FALSE);

            if (seen && ret < NELEMS(gPokedexOrder_Alphabetical) && ret < NumSeen) //had to add extra change so its still limited to numseen/caught
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumSeen <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumSeen == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumSeen > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Alphabetical))
                    {
                        
                        if (seen)
                        {
                            sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[i])];
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumSeen > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (seen) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Alphabetical); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Alphabetical[d], FLAG_GET_CAUGHT, FALSE);

                    if (seen)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Alphabetical[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }  

        }
       //only kanto and national dex list should fill empty space with dashes, rest are supposed to ONLY show number you've seen or caught based on their condition
        break;
    case DEX_ORDER_TYPE: //can't build automatically would need to loop entire species list MANY times, so would take forever
     //now that I'm saving time I MAY be able to build with a function
        for (i = 0; i <= NELEMS(gPokedexOrder_Type); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Type) && ret < NumCaught)
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Type))
                    {
                        
                        if (caught)
                        {
                            sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[i])];
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Type); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Type[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Type[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Type[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        break; //order by type and weight, just wouldn't work with my changes/species expansion would require, going through and creating list by hand
    case DEX_ORDER_LIGHTEST:
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Weight); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Weight) && ret < NumCaught)
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Weight))
                    {
                        
                        if (caught)
                        {
                            sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[i])];
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Weight); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Weight[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Weight[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Weight[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        break;
    case DEX_ORDER_SMALLEST:
        
        for (i = 0; i <= NELEMS(gPokedexOrder_Height); i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        { //old setup - couldn't give up SUCCESS

            seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[i], FLAG_GET_SEEN, FALSE);
            caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[i], FLAG_GET_CAUGHT, FALSE);

            if (caught && ret < NELEMS(gPokedexOrder_Height) && ret < NumCaught) //issue its not currently matching numcaught, works
                ret++; //build list size here, to avoid using num seen/num caught for nat dex limit issue

            if (NumCaught <= DEX_MAX_SHOWN) //works for now at lower levels, but for some reason has issue at lower limit scroll, if press down when at end, it keeps going
            {
                if (NumCaught == 0  && i <= DEX_MAX_SHOWN)
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;

                    
                }

                else if (NumCaught > 0)
                {
                    if (j < NELEMS(gPokedexOrder_Height))
                    {
                        
                        if (caught)
                        {
                            sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[i])];
                            sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[i]);

                            if (j == entryPos) //extra safety buffer, for when returning to list from dex entry, should assign curr index value 
                                sPokedexScreenData->CurrentIndexValue = i;
                            j++;
                        }
                    }
                }

            } 
        }

        if (NumCaught > DEX_MAX_SHOWN) //REALIZE don't really need i loop for this, 
        {


            for (d = 0; d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    sPokedexScreenData->listItems[d].label = gText_5Dashes;
                    sPokedexScreenData->listItems[d].index = 0;
                    //to quick fill with empty values, then fill only what I need to see
                } 


  
            if (entryPos < 5) //couldn't use i, as would trigger on different indexs and can't use i as that's looping around this, values wouldn't be consistent
            {
                for (j = 0, d = 0; j <= DEX_MAX_SHOWN && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    
                    if (caught) //would be an issue but above condition will arleady cut it off, if numseenis lessthan this condition
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }                      
                            

                }
            }

            if (entryPos >= 5 && entryPos < sPokedexScreenData->orderedDexCount - 4) 
            {

                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= entryPos + 5 && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            } 

            if (entryPos >= 5 && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
            {
                if (entryPos - DEX_MAX_SHOWN < 0)
                    i = 0;
                else
                    i = entryPos - DEX_MAX_SHOWN;

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j > i && d >= 0; d--)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j--;

                    }

                }

                for (j = entryPos, d = sPokedexScreenData->CurrentIndexValue; j <= sPokedexScreenData->orderedDexCount && d <= NELEMS(gPokedexOrder_Height); d++)
                {
                    seen = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_SEEN, FALSE);
                    caught = DexScreen_GetSetPokedexFlag(gPokedexOrder_Height[d], FLAG_GET_CAUGHT, FALSE);

                    if (caught)
                    {
                        sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(gPokedexOrder_Height[d])];
                        sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(gPokedexOrder_Height[d]);
                        if (j == entryPos)
                            sPokedexScreenData->CurrentIndexValue = d;
                        j++;

                    }

                }

                
            }
        }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        
        for (i = 0; i <= NATIONAL_SPECIES_COUNT; i++) //ok this changes load times, and num entries on list,
        {
            
            if (entryPos <= DEX_MAX_SHOWN && i == entryPos)
                {
                    for (j = 0; j <= DEX_MAX_SHOWN; j++,i++)
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);
                                if (seen)
                                {
                                    sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)]; //in lower range print first 10
                                    
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                ret++;

                    }
                }

                if (entryPos > DEX_MAX_SHOWN && i == entryPos && entryPos < sPokedexScreenData->orderedDexCount - 4) //loop 10, over i -5 label & index
                {
                    for (j = i - DEX_MAX_SHOWN; j <= entryPos + DEX_MAX_SHOWN; j++) //changed to better fill, because issue w az etc. changess
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE); //attempt expand above, can't scroll if empty space between entries is bigger than first load
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);

                                if (seen)
                                {
                                    sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)];//other print 10 from i minus 5                                    
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                ret++;

                            if (j > entryPos)
                                i++;

                    }
                    
                } 
                if (i == entryPos && entryPos >= sPokedexScreenData->orderedDexCount - 4)//for highest portion of list
                {
                    for (j = i - DEX_MAX_SHOWN; j <= sPokedexScreenData->orderedDexCount; j++) //works
                    {
                        seen = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_SEEN, FALSE);
                        caught = DexScreen_GetSetPokedexFlag(j + 1, FLAG_GET_CAUGHT, FALSE);
                                if (seen)
                                {
                                    sPokedexScreenData->listItems[j].label = gSpeciesNames[NationalPokedexNumToSpecies(j + 1)];//other print 10 from i minus 5                                    
                                }
                                else
                                {
                                    sPokedexScreenData->listItems[j].label = gText_5Dashes;
                                }
                                sPokedexScreenData->listItems[j].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(j + 1);
                                ret++;

                            if (j > entryPos)
                                i++;

                    }
                }
                else
                {
                    sPokedexScreenData->listItems[i].label = gText_5Dashes;
                    sPokedexScreenData->listItems[i].index = 0;
                    //sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(i + 1); //fixed
                    //ok didn't need that line, was just an issue with my scroll function now fixed
                
                }
                
                ret = i;

        }
        break; //changing  index affects, species number displayed and mon type displayed, not the nmae
    }


    return ret; //this would be end of new function

}