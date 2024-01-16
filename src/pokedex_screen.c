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
#include "pokedex_area_markers.h"
#include "field_specials.h"

#define TAG_AREA_MARKERS 2001

enum TextMode {
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};

struct PokedexScreenData
{
    u8 taskId;
    u8 state;
    u8 data[4]; //not used?
    u8 areaMarkersTaskId;  //added wasn't here before taks place of data[2]
    u32 unlockedCategories;
    u32 modeSelectInput;
    u16 field_10;
    u16 modeSelectCursorPos;
    u8 modeSelectWindowId;
    u8 selectionIconWindowId;
    u8 dexCountsWindowId;
    u8 modeSelectListMenuId;
    u16 field_18[4];
    u8 categoryMonWindowIds[4];
    u8 categoryMonInfoWindowIds[4];
    u8 category;
    u8 firstPageInCategory;
    u8 lastPageInCategory;
    u8 pageNum;
    u8 numMonsOnPage;
    u8 categoryCursorPosInPage;
    u8 field_2E;
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
    struct ListMenuItem * listItems;
    u16 orderedDexCount;
    u8 windowIds[0x10];
    u16 dexSpecies;
    u16 * field_5C;
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

EWRAM_DATA struct PokedexScreenData * sPokedexScreenData = NULL;

static void Task_PokedexScreen(u8 taskId);
static void DexScreen_InitGfxForTopMenu(void);
static void Task_DexScreen_NumericalOrder(u8 taskId);
static void DexScreen_InitGfxForNumericalOrderList(void);
static void Task_DexScreen_CharacteristicOrder(u8 taskId);
static void DexScreen_CreateCharacteristicListMenu(void);
static u16 DexScreen_CountMonsInOrderedList(u8 a0);
static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * a0, u8 a1);
static u8 DexScreen_CreateDexOrderScrollArrows(void);
static void DexScreen_DestroyDexOrderListMenu(u8 a0);
static void Task_DexScreen_CategorySubmenu(u8 taskId);
static u8 DexScreen_CreateCategoryMenuScrollArrows(void);
static int DexScreen_InputHandler_GetShoulderInput(void);
static void Task_DexScreen_ShowMonPage(u8 taskId);
static bool32 sub_8104664(u8 a0);
void DexScreen_RemoveWindow(u8 *windowId_p);
void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx);
static void DexScreen_PrintNum3RightAlign(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx);
void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y);
static u16 sub_8104BBC(u8 caseId, bool8 whichDex);
void DexScreen_PrintControlInfo(const u8 *src);
void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void);
bool8 DexScreen_CreateCategoryListGfx(bool8 a0);
void DexScreen_CreateCategoryPageSelectionCursor(u8 a0);
void DexScreen_UpdateCategoryPageCursorObject(u8 a0, u8 a1, u8 a2);
static bool8 sub_81052D0(u8 a0);
void DexScreen_DexPageZoomEffectFrame(u8 a0, u8 a1);
u8 DexScreen_DrawMonDexPage(u8 a0);
u8 RemoveDexPageWindows(void);
u8 DexScreen_DrawMonAreaPage(void);
bool8 DexScreen_CanShowMonInCategory(u8 category, u8 a1);
u8 DexScreen_IsCategoryUnlocked(u8 a0);
u8 DexScreen_GetPageLimitsForCategory(u8 category);
bool8 DexScreen_LookUpCategoryBySpecies(u16 a0);
u8 sub_81067C0(void);
void sub_81068DC(u8 category, u8 a1);
u8 sub_8106AF8(u16 a0);
void sub_8106B34(void);
void DexScreen_PrintStringWithAlignment(const u8 *a0, s32 a1);
static void MoveCursorFunc_DexModeSelect(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y);
static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y);
static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId);
static void Task_DexScreen_RegisterMonToPokedex(u8 taskId);

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
const u16 gUnknown_84434C0[] = INCBIN_U16("graphics/pokedex/unk_84434C0.gbapal");
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
const u16 gUnknown_8443D00[] = INCBIN_U16("graphics/pokedex/unk_8443D00.4bpp");

#include "data/pokemon/pokedex_orders.h"

static const u8 gExpandedPlaceholder_PokedexDescription[] = _("");

#include "data/pokemon/pokedex_text.h"
#include "data/pokemon/pokedex_entries.h"

static const struct BgTemplate sUnknown_8451EBC[] = {
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

static const struct WindowTemplate sUnknown_8451ECC[] = {
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

static const struct PokedexScreenData sUnknown_8451EE4 = {
    .field_10 = 1,
    .modeSelectWindowId = -1,
    .selectionIconWindowId = -1,
    .dexCountsWindowId = -1,
    .field_18 = {-1, -1, -1, -1},
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
    {gText_PokemonList,              LIST_HEADER},
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
    .maxShowed = 9,
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
    .fontId = 2,
    .cursorKind = 0,
};

static const struct ListMenuItem sUnknown_845201C[] = {
    {gText_PokemonList, -3},
    {gText_NumericalModeKanto, 9},
    {gText_NumericalModeNational, 14},
    {gText_PokemonHabitats, -3},
    {gText_DexCategory_GrasslandPkmn, 0},
    {gText_DexCategory_ForestPkmn, 1},
    {gText_DexCategory_WatersEdgePkmn, 2},
    {gText_DexCategory_SeaPkmn, 3},
    {gText_DexCategory_CavePkmn, 4},
    {gText_DexCategory_MountainPkmn, 5},
    {gText_DexCategory_RoughTerrainPkmn, 6},
    {gText_DexCategory_UrbanPkmn, 7},
    {gText_DexCategory_RarePkmn, 8},
    {gText_Search, -3},
    {gText_AToZMode, 10},
    {gText_TypeMode, 11},
    {gText_LightestMode, 12},
    {gText_SmallestMode, 13},
    {gText_PokedexOther, -3},
    {gText_ClosePokedex, -2},
};

static const struct ListMenuTemplate sListMenuTemplate_NatDexModeSelect = {
    .items = sUnknown_845201C,
    .moveCursorFunc = MoveCursorFunc_DexModeSelect,
    .itemPrintFunc = ItemPrintFunc_DexModeSelect,
    .totalItems = NELEMS(sUnknown_845201C),
    .maxShowed = 9,
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
    .fontId = 2,
    .cursorKind = 0,
};

static const struct ScrollArrowsTemplate sUnknown_84520D4 = {
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

static const struct ScrollArrowsTemplate sUnknown_84520E4 = {
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
        .pal = sTopMenuIconPals_Grassland
    },
    [DEX_CATEGORY_FOREST] = {
        .tiles = sTopMenuIconTiles_Forest,
        .pal = sTopMenuIconPals_Forest
    },
    [DEX_CATEGORY_WATERS_EDGE] = {
        .tiles = sTopMenuIconTiles_WatersEdge,
        .pal = sTopMenuIconPals_WatersEdge
    },
    [DEX_CATEGORY_SEA] = {
        .tiles = sTopMenuIconTiles_Sea,
        .pal = sTopMenuIconPals_Sea
    },
    [DEX_CATEGORY_CAVE] = {
        .tiles = sTopMenuIconTiles_Cave,
        .pal = sTopMenuIconPals_Cave
    },
    [DEX_CATEGORY_MOUNTAIN] = {
        .tiles = sTopMenuIconTiles_Mountain,
        .pal = sTopMenuIconPals_Mountain
    },
    [DEX_CATEGORY_ROUGH_TERRAIN] = {
        .tiles = sTopMenuIconTiles_RoughTerrain,
        .pal = sTopMenuIconPals_RoughTerrain
    },
    [DEX_CATEGORY_URBAN] = {
        .tiles = sTopMenuIconTiles_Urban,
        .pal = sTopMenuIconPals_Urban
    },
    [DEX_CATEGORY_RARE] = {
        .tiles = sTopMenuIconTiles_Rare,
        .pal = sTopMenuIconPals_Rare
    },
    [DEX_MODE(NUMERICAL_KANTO)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal = sTopMenuIconPals_Numerical
    },
    [DEX_MODE(ATOZ)] = {
        .tiles = gDexScreen_TopMenuIconTiles_AtoZ,
        .pal = gDexScreen_TopMenuIconPals_AtoZ
    },
    [DEX_MODE(TYPE)] = {
        .tiles = sTopMenuIconTiles_Type,
        .pal = sTopMenuIconPals_Type
    },
    [DEX_MODE(LIGHTEST)] = {
        .tiles = sTopMenuIconTiles_Lightest,
        .pal = sTopMenuIconPals_Lightest
    },
    [DEX_MODE(SMALLEST)] = {
        .tiles = sTopMenuIconTiles_Smallest,
        .pal = sTopMenuIconPals_Smallest
    },
    [DEX_MODE(NUMERICAL_NATIONAL)] = {
        .tiles = sTopMenuIconTiles_Numerical,
        .pal = sTopMenuIconPals_Numerical
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
    .maxShowed = 9,
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

// Unused   //values for listmenurect in other repo
/*static const u8 gUnknown_8452194[] = {
    0x05, 0x00, 0x02, 0x10, 0x01, 0x00, 0x00, 0x00, 
    0x07, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x0f, 0x00, 0x08, 0x10, 0x02, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00
};*/

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
    .width = 9,
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
    const u32 * tilemap;
} const sAreaMapStructs_SeviiIslands[] = {
    {&sWindowTemplate_AreaMap_OneIsland,    sTilemap_AreaMap_OneIsland},
    {&sWindowTemplate_AreaMap_TwoIsland,    sTilemap_AreaMap_TwoIsland},
    {&sWindowTemplate_AreaMap_ThreeIsland,  sTilemap_AreaMap_ThreeIsland},
    {&sWindowTemplate_AreaMap_FourIsland,   sTilemap_AreaMap_FourIsland},
    {&sWindowTemplate_AreaMap_FiveIsland,   sTilemap_AreaMap_FiveIsland},
    {&sWindowTemplate_AreaMap_SixIsland,    sTilemap_AreaMap_SixIsland},
    {&sWindowTemplate_AreaMap_SevenIsland,  sTilemap_AreaMap_SevenIsland},
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
};

const u8 (*const sCategoryPageIconCoords[])[4] = {
    sPageIconCoords_1Mon,
    sPageIconCoords_2Mons,
    sPageIconCoords_3Mons,
    sPageIconCoords_4Mons,
};

static const u8 * const sDexCategoryNamePtrs[] = {
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
    {
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x05, 0x0b, 0x11, 0x17, 0x1d, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x02, 0x05, 0x08, 0x0b, 0x0e, 0x11, 0x14, 0x17, 0x1a, 0x1d, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x02, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x11, 0x13, 
        0x15, 0x17, 0x19, 0x1b, 0x1d, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x02, 0x04, 0x05, 0x07, 0x08, 0x0a, 0x0b, 0x0d, 0x0e, 0x10, 
        0x11, 0x13, 0x14, 0x16, 0x17, 0x19, 0x1a, 0x1c, 0x1d, 0x1e, 
        0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x01, 0x02, 0x03, 0x04, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 
        0x0d, 0x0f, 0x10, 0x11, 0x13, 0x14, 0x15, 0x17, 0x18, 0x19, 
        0x1b, 0x1c, 0x1d, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0a, 0x0b, 
        0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x14, 0x15, 0x16, 
        0x17, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1e, 0x1e, 0x1e
    }, {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0b, 
        0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x15, 0x16, 
        0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1e, 0x1e
    }, {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 
        0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e
    }, {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
        0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 
        0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d
    },
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


//need be constant so think will need 3 of this as well to match each mini_page
//category window cursor, was 8 x 5 now 9 x 5  so need change cursor to width 72 from 64 for expansion
//cursor red outline for category minipage
const struct CursorStruct sCursorStruct_SmallCategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 64,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

const struct CursorStruct sCursorStruct_MediumCategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 72,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

const struct CursorStruct sCursorStruct_LargeCategoryPage = {
    .left = 0,
    .top = 160,
    .rowWidth = 80,
    .rowHeight = 40,
    .tileTag = 2002,
    .palTag = 0xFFFF,
    .palNum = 4,
};

#include "data/pokemon/pokedex_categories.h"

void sub_81024C0(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void sub_81024D4(void)
{
    if (!gPaletteFade.active || IsDma3ManagerBusyWithBgCopy())
    {
        RunTasks();
        RunTextPrinters();
        AnimateSprites();
        BuildOamBuffer();
    }
    else
    {
        UpdatePaletteFade();
    }
}

void DexScreen_LoadResources(void)
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
    InitBgsFromTemplates(0, sUnknown_8451EBC, NELEMS(sUnknown_8451EBC));
    SetBgTilemapBuffer(3, (u16*)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(2, (u16*)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(1, (u16*)Alloc(BG_SCREEN_SIZE));
    SetBgTilemapBuffer(0, (u16*)Alloc(BG_SCREEN_SIZE));
    if (natDex)
        DecompressAndLoadBgGfxUsingHeap(3, (void*)sNatDexTiles, BG_SCREEN_SIZE, 0, 0);
    else
        DecompressAndLoadBgGfxUsingHeap(3, (void*)sKantoDexTiles, BG_SCREEN_SIZE, 0, 0);
    InitWindows(sUnknown_8451ECC);
    DeactivateAllTextPrinters();
    m4aSoundVSyncOn();
    SetVBlankCallback(sub_81024C0);
    EnableInterrupts(INTR_FLAG_VBLANK);
    taskId = CreateTask(Task_PokedexScreen, 0);
    sPokedexScreenData = Alloc(sizeof(struct PokedexScreenData));
    *sPokedexScreenData = sUnknown_8451EE4;
    sPokedexScreenData->taskId = taskId;
    sPokedexScreenData->listItems = Alloc(NATIONAL_DEX_COUNT * sizeof(struct ListMenuItem));
    sPokedexScreenData->numSeenNational = sub_8104BBC(0, 1);
    sPokedexScreenData->numOwnedNational = sub_8104BBC(1, 1);
    sPokedexScreenData->numSeenKanto = sub_8104BBC(0, 0);
    sPokedexScreenData->numOwnedKanto = sub_8104BBC(1, 0);
    sub_8072474(0x80);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    gPaletteFade.bufferTransferDisabled = TRUE;
    if (natDex)
        LoadPalette(sNationalDexPalette, 0, 0x200);
    else
        LoadPalette(sKantoDexPalette, 0, 0x200);
    FillBgTilemapBufferRect(3, 0x001, 0, 0, 32, 32, 0);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 32, 32, 0x11);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
    FillBgTilemapBufferRect(0, 0x0003, 0, 0, 32, 2, 0xF);
    FillBgTilemapBufferRect(0, 0x0000, 0, 2, 32, 16, 0x11);
    FillBgTilemapBufferRect(0, 0x003, 0, 18, 32, 2, 0xF);
}

void CB2_OpenPokedexFromStartMenu(void)
{
    DexScreen_LoadResources();
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetMainCallback2(sub_81024D4);
   // SetHelpContext(HELPCONTEXT_POKEDEX);
}

#define FREE_IF_NOT_NULL(ptr0) ({ void * ptr = (ptr0); if (ptr) Free(ptr); })

bool8 sub_8102798(void)
{
    switch (gMain.state)
    {
    case 0:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
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
        sub_807249C();
        break;
    }
    return TRUE;
}

void sub_8102858(void)
{
    if (sub_8102798())
    {
        SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
    }
}

static void Task_PokedexScreen(u8 taskId)
{
    int i;
    switch (sPokedexScreenData->state)
    {
    case 0:
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
        SetMainCallback2(sub_8102858);
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
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0, RGB_WHITEALPHA);
        }
        else
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        ListMenuGetScrollAndRow(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPosBak, NULL);
        if (IsNationalPokedexEnabled())
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sUnknown_84520E4, &sPokedexScreenData->modeSelectCursorPosBak);
        else
            sPokedexScreenData->scrollArrowsTaskId = AddScrollIndicatorArrowPair(&sUnknown_84520D4, &sPokedexScreenData->modeSelectCursorPosBak);
        sPokedexScreenData->state = 6;
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
                    BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                    sPokedexScreenData->state = 7;
                }
                break;
            case DEX_MODE(NUMERICAL_KANTO):
            case DEX_MODE(NUMERICAL_NATIONAL):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - 9;
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9;
                break;
            case DEX_MODE(ATOZ):
            case DEX_MODE(TYPE):
            case DEX_MODE(LIGHTEST):
            case DEX_MODE(SMALLEST):
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                sPokedexScreenData->dexOrderId = sPokedexScreenData->modeSelectInput - 9;
                sPokedexScreenData->characteristicOrderMenuItemsAbove = sPokedexScreenData->characteristicOrderMenuCursorPos = 0;
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 8;
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
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->field_10);
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
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->field_10);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_CharacteristicOrder;
        sPokedexScreenData->state = 0;
        break;
    case 9:
        DestroyListMenuTask(sPokedexScreenData->modeSelectListMenuId, &sPokedexScreenData->modeSelectCursorPos, &sPokedexScreenData->field_10);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->modeSelectWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->selectionIconWindowId);
        DexScreen_RemoveWindow(&sPokedexScreenData->dexCountsWindowId);
        gTasks[taskId].func = Task_DexScreen_NumericalOrder;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void DexScreen_InitGfxForTopMenu(void)
{
    struct ListMenuTemplate listMenuTemplate;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 30, 20, 0x11);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 30, 20, 0x11);
    sPokedexScreenData->modeSelectWindowId = AddWindow(&sWindowTemplate_ModeSelect);
    sPokedexScreenData->selectionIconWindowId = AddWindow(&sWindowTemplate_SelectionIcon);
    sPokedexScreenData->dexCountsWindowId = AddWindow(&sWindowTemplate_DexCounts);
    if (IsNationalPokedexEnabled())
    {
        listMenuTemplate = sListMenuTemplate_NatDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->field_10);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Seen, 0, 2, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 13, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenKanto, 52, 13, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 24, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numSeenNational, 52, 24, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Owned, 0, 37, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_Kanto, 8, 48, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedKanto, 52, 48, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_SMALL, gText_National, 8, 59, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 0, sPokedexScreenData->numOwnedNational, 52, 59, 2);
    }
    else
    {
        listMenuTemplate = sListMenuTemplate_KantoDexModeSelect;
        listMenuTemplate.windowId = sPokedexScreenData->modeSelectWindowId;
        sPokedexScreenData->modeSelectListMenuId = ListMenuInit(&listMenuTemplate, sPokedexScreenData->modeSelectCursorPos, sPokedexScreenData->field_10);
        FillWindowPixelBuffer(sPokedexScreenData->dexCountsWindowId, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Seen, 0, 9, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numSeenKanto, 32, 21, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->dexCountsWindowId, FONT_NORMAL_COPY_1, gText_Owned, 0, 37, 0);
        DexScreen_PrintNum3RightAlign(sPokedexScreenData->dexCountsWindowId, 1, sPokedexScreenData->numOwnedKanto, 32, 49, 2);
    }
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokedexTableOfContents, 1);
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
        LoadPalette(sTopMenuSelectionIconPals_Cancel, 0x10, 0x20);
    }
    else
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->selectionIconWindowId, sTopMenuSelectionIconGfxPtrs[itemIndex].tiles, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconGfxPtrs[itemIndex].pal, 0x10, 0x20);
    }
    PutWindowTilemap(sPokedexScreenData->selectionIconWindowId);
    CopyWindowToVram(sPokedexScreenData->selectionIconWindowId, COPYWIN_GFX);
}

static void ItemPrintFunc_DexModeSelect(u8 windowId, s32 itemId, u8 y) //don't konw why but for some resason itemId uses s, and some things use negative itemId values?
{
    
    if (itemId >= DEX_CATEGORY_COUNT || sPokedexScreenData->unlockedCategories & (1 << itemId))
        ListMenuOverrideSetColors(TEXT_COLOR_WHITE, TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_GREY);
    else
        ListMenuOverrideSetColors(TEXT_DYNAMIC_COLOR_1, TEXT_COLOR_TRANSPARENT, TEXT_DYNAMIC_COLOR_2);
}

static void Task_DexScreen_NumericalOrder(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(0x10, 0);
        ListMenuLoadStdPalAt(0x20, 1);
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
        DexScreen_InitGfxForNumericalOrderList();
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        ShowBg(1);
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
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
            if ((sPokedexScreenData->characteristicMenuInput >> 16) & 1)
            {
                sPokedexScreenData->dexSpecies = sPokedexScreenData->characteristicMenuInput;
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
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

static void DexScreen_InitGfxForNumericalOrderList(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_PokemonListNoColor, 1);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static void Task_DexScreen_CharacteristicOrder(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(0x10, 0);
        ListMenuLoadStdPalAt(0x20, 1);
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
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
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
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId); //potentailly along with remove category search above
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->scrollArrowsTaskId);
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        DexScreen_DestroyDexOrderListMenu(sPokedexScreenData->dexOrderId);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        sPokedexScreenData->parentOfCategoryMenu = 1;
        gTasks[taskId].func = Task_DexScreen_CategorySubmenu; //think this is what need to change,
        sPokedexScreenData->state = 0;
        break;
    }
}

static void DexScreen_CreateCharacteristicListMenu(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->listItems;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->orderedDexCount;
    DexScreen_InitListMenuForOrderedList(&template, sPokedexScreenData->dexOrderId);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    DexScreen_PrintStringWithAlignment(gText_SearchNoColor, 1);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    DexScreen_PrintControlInfo(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static u16 DexScreen_CountMonsInOrderedList(u8 a0)
{
    s32 max_n = IsNationalPokedexEnabled() ? NATIONAL_DEX_COUNT : KANTO_DEX_COUNT;
    u16 ndex_num;
    u16 ret = NATIONAL_DEX_NONE;
    s32 i;
    bool8 caught;
    bool8 seen;

    switch (a0)
    {
    default:
    case DEX_ORDER_NUMERICAL_KANTO:
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
            if (seen)
            {
                sPokedexScreenData->listItems[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
            }
            sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    case DEX_ORDER_ATOZ:
        for (i = 0; i < SPECIES_CALYREX; i++) //this was issue with limit, it used chimecho for some dumb reason, rather than species or something smh
        {
            ndex_num = gPokedexOrder_Alphabetical[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (seen)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++; //need 
                }
            }
        }
        break;
    case DEX_ORDER_TYPE:
        for (i = 0; i < SPECIES_CALYREX; i++)  //for (i = 0; i < NUM_SPECIES - 1; i++)  replaced because gens error, with undefined values
        {
            ndex_num = SpeciesToNationalPokedexNum(gPokedexOrder_Type[i]);
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_LIGHTEST:
        for (i = 0; i < SPECIES_CALYREX; i++) //for (i = 0; i < NATIONAL_DEX_COUNT; i++) same reason as above //all below share same original value
        {
            ndex_num = gPokedexOrder_Weight[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_SMALLEST:
        for (i = 0; i < SPECIES_CALYREX; i++)
        {
            ndex_num = gPokedexOrder_Height[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->listItems[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->listItems[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case DEX_ORDER_NUMERICAL_NATIONAL:
        for (i = 0; i < SPECIES_CALYREX; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
            if (seen)
            {
                sPokedexScreenData->listItems[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->listItems[i].label = gText_5Dashes;
            }
            sPokedexScreenData->listItems[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    }
    return ret;
}

static void DexScreen_InitListMenuForOrderedList(const struct ListMenuTemplate * template, u8 order)
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
    u32 itemId_ = itemId;
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
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 4;
        break;
    case 4: //believe for accessing category from within pokedex
        sPokedexScreenData->scrollArrowsTaskId = DexScreen_CreateCategoryMenuScrollArrows();

        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_SmallCategoryPage, 0);

        sPokedexScreenData->state = 5;
        break;//cursor is not changing with each mon, even though bg window does even though that doesn't have loop either
        //I'm guessing without loop its only checking the species on the first page of the category, testing next
        //its nto doig that but I think will need to make look specifically through each category and each page
        //to pull the right species info for the cursor to use
    case 5:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);
        sPokedexScreenData->modeSelectCursorPosBak = sPokedexScreenData->pageNum;
        pageFlipCmd = 0;
        if (JOY_NEW(A_BUTTON) && DexScreen_GetSetPokedexFlag(sPokedexScreenData->field_18[sPokedexScreenData->categoryCursorPosInPage], FLAG_GET_SEEN, 1))
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
        case 0:
            break;
        case 1:
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
        case 2:
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
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
        sPokedexScreenData->state = 1;
        break;
    case 8:
    case 10:
        DexScreen_DestroyCategoryPageMonIconAndInfoWindows();
        DexScreen_CreateCategoryPageSelectionCursor(0xFF);
        ListMenuUpdateCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0, 0xA0, 0);
        sPokedexScreenData->field_2E = 0;
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->state++;
        break;
    case 9:
        if (sub_81052D0(0))
        {
            sPokedexScreenData->categoryCursorPosInPage = sPokedexScreenData->numMonsOnPage - 1;
            sPokedexScreenData->state = 5;
        }
        break;
    case 11:
        if (sub_81052D0(1))
        {
            sPokedexScreenData->categoryCursorPosInPage = 0;
            sPokedexScreenData->state = 5;
        }
        break;
    case 12:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->field_18[sPokedexScreenData->categoryCursorPosInPage];
        PlaySE(SE_SELECT);
        sPokedexScreenData->state = 14;
        break;
    case 13:
        RemoveDexPageWindows();
        sPokedexScreenData->state = 4;
        break;
    case 14:
        DexScreen_DrawMonDexPage(0);
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
            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, 125, 10);
            sPokedexScreenData->data[0] = 0;
            sPokedexScreenData->state = 17;
        }
        break;
    case 17:
        if (JOY_NEW(A_BUTTON))
        {
            RemoveDexPageWindows();
            FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 2, 30, 16);
            CopyBgTilemapBufferToVram(1);
            sPokedexScreenData->state = 21;
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPokedexScreenData->state = 18;
        }
        else
        {
            sub_8106B34();
        }
        break;
    case 18:
        DexScreen_CreateCategoryListGfx(0);
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
            sub_8106B34();
        }
        break;
    case 24:
        sub_81067C0();
        sPokedexScreenData->state = 25;
        break;
    case 25:
        DexScreen_DrawMonDexPage(0);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 17;
        break;
    case 26:
        sub_81067C0();
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

static void Task_DexScreen_ShowMonPage(u8 taskId)
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
        DexScreen_DrawMonDexPage(0);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, 125, 10);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
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
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        else if (JOY_NEW(DPAD_UP) && sub_8104664(1))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else if (JOY_NEW(DPAD_DOWN) && sub_8104664(0))
        {
            RemoveDexPageWindows();
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 6;
        }
        else
        {
            sub_8106B34();
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
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
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
            sub_8106B34();
        }
        break;
    case 10:
        sub_81067C0();
        sPokedexScreenData->state = 11;
        break;
    case 11:
        DexScreen_DrawMonDexPage(0);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 5;
        break;
    case 12:
        sub_81067C0();
        FillBgTilemapBufferRect_Palette0(0, 0x000, 0, 2, 30, 16);
        CopyBgTilemapBufferToVram(0);
        sPokedexScreenData->state = 1;
        break;
    }
}

static bool32 sub_8104664(u8 a0)
{
    int r3;
    u16 *r6, *r12;

    switch (sPokedexScreenData->dexOrderId)
    {
    default:
    case 0:
        r12 = &sPokedexScreenData->kantoOrderMenuCursorPos;
        r6 = &sPokedexScreenData->kantoOrderMenuItemsAbove;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        r12 = &sPokedexScreenData->characteristicOrderMenuCursorPos;
        r6 = &sPokedexScreenData->characteristicOrderMenuItemsAbove;
        break;
    case 5:
        r12 = &sPokedexScreenData->nationalOrderMenuCursorPos;
        r6 = &sPokedexScreenData->nationalOrderMenuItemsAbove;
        break;
    }

    r3 = *r12 + *r6;
    if (a0)
    {
        if (r3 == 0)
            return FALSE;

        r3--;
        while (r3 >= 0) //Should be while (--r3 >= 0) without the r3-- in the body or before the while at all, but this is needed to match.
        {
            if ((sPokedexScreenData->listItems[r3].index >> 16) & 1)
            {
                break;
            }
            r3--;
        }

        if (r3 < 0)
        {
            return FALSE;
        }
    }
    else
    {
        if (r3 == sPokedexScreenData->orderedDexCount - 1)
        {
            return FALSE;
        }

        r3++;
        while (r3 < sPokedexScreenData->orderedDexCount) //Should be while (++r3 < sPokedexScreenData->orderedDexCount) without the r3++ in the body or before the while at all, but this is needed to match.
        {
            if ((sPokedexScreenData->listItems[r3].index >> 16) & 1)
                break;
            r3++;
        }
        if (r3 >= sPokedexScreenData->orderedDexCount)
        {
            return FALSE;
        }
    }
    sPokedexScreenData->characteristicMenuInput = sPokedexScreenData->listItems[r3].index;

    if (sPokedexScreenData->orderedDexCount > 9)
    {
        if (r3 < 4)
        {
            *r12 = 0;
            *r6 = r3;
        }
        else if (r3 >= (sPokedexScreenData->orderedDexCount - 4))
        {
            *r12 = (sPokedexScreenData->orderedDexCount - 9);
            *r6 = r3 + 9 - (sPokedexScreenData->orderedDexCount);
        }
        else
        {
            *r12 = r3 - 4;
            *r6 = 4;
        }
    }
    else
    {
        *r12 = 0;
        *r6 = r3;
    }
    return TRUE;
}

void DexScreen_RemoveWindow(u8 *windowId_p)
{
    if (*windowId_p != 0xFF)
    {
        RemoveWindow(*windowId_p);
        *windowId_p = 0xFF;
    }
}

void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx)
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
    AddTextPrinterParameterized4(windowId, fontId, x, y, fontId == 0 ? 0 : 1, 0, textColor, -1, str);
}

void sub_8104880(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
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

u32 DexScreen_GetDefaultPersonality(int species)
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

void DexScreen_LoadMonPicInWindow(u8 windowId, u16 species, u16 paletteOffset)
{
    LoadMonPicInWindow(species, 8, DexScreen_GetDefaultPersonality(species), TRUE, paletteOffset >> 4, windowId);
}

void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y)
{
    u16 dexNum = SpeciesToNationalPokedexNum(species);
    DexScreen_AddTextPrinterParameterized(windowId, fontId, gText_PokedexNo, x, y, 0);
    sub_8104880(windowId, fontId, dexNum, x + 9, y, 0);
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
            if ((gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.seen[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_GET_CAUGHT:
        if (gSaveBlock2Ptr->pokedex.owned[index] & mask)
        {
            if ((gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock2Ptr->pokedex.seen[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen1[index] & mask)
                && (gSaveBlock2Ptr->pokedex.owned[index] & mask) == (gSaveBlock1Ptr->seen2[index] & mask))
                retVal = 1;
        }
        break;
    case FLAG_SET_SEEN:
        gSaveBlock2Ptr->pokedex.seen[index] |= mask;
        gSaveBlock1Ptr->seen1[index] |= mask;
        gSaveBlock1Ptr->seen2[index] |= mask;
        break;
    case FLAG_SET_CAUGHT:
        gSaveBlock2Ptr->pokedex.owned[index] |= mask;
        break;
    }
    //return retVal;
    return 1;
}

static u16 sub_8104BBC(u8 caseId, bool8 whichDex)
{
    u16 count = 0;
    u16 i;

    switch (whichDex)
    {
    case 0: // Kanto
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))  //for seen amount but not appearing in dex 
                count++;
        }
        break;
    case 1: // National
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))
                count++;

        }
        break;
    }
    return count;
}

void DexScreen_PrintControlInfo(const u8 *src)
{
    DexScreen_AddTextPrinterParameterized(1, 0, src, 236 - GetStringWidth(0, src, 0), 2, 4);
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
            /*if (StringLength(gSpeciesNames[species]) <= 11)
            {
                //sPokedexScreenData->categoryMonInfoWindowIds[slot] = AddWindow(&template); //still unsure if this need be here or not?
                CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonInfoBgTiles, 0, 0);
            }
            else if (StringLength(gSpeciesNames[species]) == 12) 
            {
                CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonMediumInfoBgTiles, 0, 0);
            }

            else if (StringLength(gSpeciesNames[species]) == 13) 
            {
                CopyToWindowPixelBuffer(sPokedexScreenData->categoryMonInfoWindowIds[slot], sCategoryMonLargeInfoBgTiles, 0, 0);
            }*/

            DexScreen_PrintMonDexNo(sPokedexScreenData->categoryMonInfoWindowIds[slot], 0, species, 12, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->categoryMonInfoWindowIds[slot], 2, gSpeciesNames[species], 2, 13, 0);
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

void DexScreen_DestroyCategoryPageMonIconAndInfoWindows(void)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonWindowIds[i]);
        DexScreen_RemoveWindow(&sPokedexScreenData->categoryMonInfoWindowIds[i]);
    }
}

void sub_8104EC0(u8 unused, u16 a1, u16 a2, u8 unused2, u8 unused3)
{
    u8 buffer[30];
    u8 *ptr = StringCopy(buffer, gText_Page);
    ptr = ConvertIntToDecimalStringN(ptr, a1, STR_CONV_MODE_RIGHT_ALIGN, 2);
    *ptr++ = CHAR_SLASH;
    ptr = ConvertIntToDecimalStringN(ptr, a2, STR_CONV_MODE_RIGHT_ALIGN, 2);
    DexScreen_PrintStringWithAlignment(buffer, 2);
}

bool8 DexScreen_CreateCategoryListGfx(bool8 a0)
{
    FillBgTilemapBufferRect_Palette0(3, 2, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
    sub_81068DC(sPokedexScreenData->category, sPokedexScreenData->pageNum);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    if (a0)
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], 1);
    }
    else
    {
        DexScreen_PrintStringWithAlignment(sDexCategoryNamePtrs[sPokedexScreenData->category], 0);
        sub_8104EC0(0, sub_8106AF8(sPokedexScreenData->pageNum), sub_8106AF8(sPokedexScreenData->lastPageInCategory - 1), 160, 2);
    }
    CopyWindowToVram(0, COPYWIN_GFX);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (!a0)
        DexScreen_PrintControlInfo(gText_PickFlipPageCheckCancel);
    CopyWindowToVram(1, COPYWIN_GFX);
    if (sPokedexScreenData->field_18[0] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->field_18[0], 0, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->field_18[1] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->field_18[1], 1, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->field_18[2] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->field_18[2], 2, sPokedexScreenData->numMonsOnPage);
    if (sPokedexScreenData->field_18[3] != 0xFFFF)
        DexScreen_DrawMonPicInCategoryPage(sPokedexScreenData->field_18[3], 3, sPokedexScreenData->numMonsOnPage);
    return FALSE;
}

void DexScreen_CreateCategoryPageSelectionCursor(u8 a0)
{
    int i;
    u32 r7;

    if (a0 == 0xFF)
    {
        for (i = 0; i < 4; i++)
        {
            LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x52 + 0x10 * i, 2);
            LoadPalette(&sDexScreen_CategoryCursorPals[1], 0x58 + 0x10 * i, 2);
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x141, 2);
        sPokedexScreenData->field_2E = 0;
    }
    else
    {
        sPokedexScreenData->field_2E++;
        if (sPokedexScreenData->field_2E == 16)
            sPokedexScreenData->field_2E = 0;
        r7 = sPokedexScreenData->field_2E >> 2;
        for (i = 0; i < 4; i++)
        {
            if (i == a0)
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * r7 + 2], 0x52 + 0x10 * i, 2);
                LoadPalette(&sDexScreen_CategoryCursorPals[2 * r7 + 3], 0x58 + 0x10 * i, 2);
            }
            else
            {
                LoadPalette(&sDexScreen_CategoryCursorPals[0], 0x52 + 0x10 * i, 2);
                LoadPalette(&sDexScreen_CategoryCursorPals[1], 0x58 + 0x10 * i, 2);
            }
        }
        LoadPalette(&sDexScreen_CategoryCursorPals[2 * r7 + 2], 0x141, 2);
    }
}

void DexScreen_UpdateCategoryPageCursorObject(u8 a0, u8 a1, u8 a2)
{
    a2--;
    ListMenuUpdateCursorObject(a0, sCategoryPageIconCoords[a2][a1][2] * 8, sCategoryPageIconCoords[a2][a1][3] * 8, 0);
}

bool8 sub_81051AC(const u16 *a0, u8 a1, u16 *a2, u8 a3)
{
    int i;
    const u16 *src = &a0[a1];
    u16 *dst = &a2[a3];
    for (i = 0; i < 20; i++)
    {
        *dst = *src;
        dst += 32;
        src += 32;
    }
    return FALSE;
}

bool8 sub_81051D0(u16 a0, u16 *a1, u8 a2)
{
    int i;
    u16 *dst = &a1[a2];
    for (i = 0; i < 20; i++)
    {
        *dst = a0;
        dst += 32;
    }
    return FALSE;
}

bool8 sub_81051F0(u8 a0)
{
    int i;
    int r4;
    u16 *bg1buff = GetBgTilemapBuffer(1);
    u16 *bg2buff = GetBgTilemapBuffer(2);
    u16 *bg3buff = GetBgTilemapBuffer(3);
    u16 *sp04 = sPokedexScreenData->field_5C + 0x800;
    u16 *sp08 = sPokedexScreenData->field_5C + 0x400;
    u16 *sp0C = sPokedexScreenData->field_5C + 0x000;
    for (i = 0; i < 30; i++)
    {
        r4 = sDexScreenPageTurnColumns[a0][i];
        if (r4 == 30)
        {
            sub_81051D0(0x000, bg1buff, i);
            sub_81051D0(0x000, bg2buff, i);
            sub_81051D0(0x00C, bg3buff, i);
        }
        else
        {
            sub_81051AC(sp04, r4, bg1buff, i);
            sub_81051AC(sp08, r4, bg2buff, i);
            sub_81051AC(sp0C, r4, bg3buff, i);
        }
    }
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(3);
    return FALSE;
}

static bool8 sub_81052D0(u8 a0)
{
    u16 r4;
    if (IsNationalPokedexEnabled())
        r4 = sNationalDexPalette[7];
    else
        r4 = sKantoDexPalette[7];
    switch (sPokedexScreenData->data[0])
    {
    case 0:
        sPokedexScreenData->field_5C = Alloc(3 * BG_SCREEN_SIZE);
        if (a0)
            sPokedexScreenData->data[0] = 6;
        else
            sPokedexScreenData->data[0] = 2;
        break;
    case 1:
        Free(sPokedexScreenData->field_5C);
        return TRUE;
    case 2:
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 16, r4);
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
        BeginNormalPaletteFade(0x00007FFF, 0, 0, 0, r4);
        DexScreen_CreateCategoryListGfx(FALSE);
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->field_5C[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->field_5C[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->field_5C[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
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
            sub_81051F0(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]++;
        }
        else
        {
            sPokedexScreenData->data[0] = 1;
        }
        break;
    case 6:
        CpuFastCopy(GetBgTilemapBuffer(3), &sPokedexScreenData->field_5C[0 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(2), &sPokedexScreenData->field_5C[1 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);
        CpuFastCopy(GetBgTilemapBuffer(1), &sPokedexScreenData->field_5C[2 * BG_SCREEN_SIZE / 2], BG_SCREEN_SIZE);

        sPokedexScreenData->data[1] = 9;
        sPokedexScreenData->data[0]++;
        PlaySE(SE_BALL_TRAY_ENTER);
        break;
    case 7:
        if (sPokedexScreenData->data[1] != 0)
        {
            sub_81051F0(sPokedexScreenData->data[1]);
            sPokedexScreenData->data[1]--;
        }
        else
        {
#ifdef BUGFIX
            sub_81051F0(0);
#else
            sub_81051F0(sPokedexScreenData->data[0]);
#endif
            BeginNormalPaletteFade(0x00007FFF, 0, 16, 16, r4);
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
        BeginNormalPaletteFade(0x00007FFF, 0, 16, 0, r4);
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
    if (height >= 14)// Make sure it's not taller than the screen
        height = 14;
    left = tileLeft - ((scale * 4) / 2);
    top = tileTop - ((scale * 2) / 2);
    if ((left + width + 2) >= 30)// Don't wrap right...
        left -= ((left + width + 2) - 30);
    else if (left < 0)// ... left ...
        left = 0;
    if ((top + height + 2) >= 18)// ... down ...
        top -= ((top + height + 2) - 18);
    else if (top < 2)// or up.
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

void DexScreen_PrintMonCategory(u8 a0, u16 species, u8 a2, u8 a3)
{
    u8 * categoryName;
    u8 index, categoryStr[12];

    species = SpeciesToNationalPokedexNum(species);

    categoryName = (u8 *)gPokedexEntries[species].categoryName;
    index = 0;
    if (DexScreen_GetSetPokedexFlag(species, 1, 0))
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

    DexScreen_AddTextPrinterParameterized(a0, 0, categoryStr, a2, a3, 0);
    a2 += GetStringWidth(0, categoryStr, 0);
    DexScreen_AddTextPrinterParameterized(a0, 0, gText_PokedexPokemon, a2, a3, 0);
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

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, 0))
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
        buffer[i++] = CHAR_SGL_QUOT_RIGHT;
        buffer[i++] = inches / 10 + CHAR_0;
        buffer[i++] = inches % 10 + CHAR_0;
        buffer[i++] = CHAR_DBL_QUOT_RIGHT;
        buffer[i++] = EOS;
    }
    else
    {
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_SGL_QUOT_RIGHT;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_QUESTION_MARK;
        buffer[i++] = CHAR_DBL_QUOT_RIGHT;
    }

    buffer[i++] = EOS;
    DexScreen_AddTextPrinterParameterized(windowId, 0, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, 0, buffer, x, y, 0);
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

    if (DexScreen_GetSetPokedexFlag(species, FLAG_GET_CAUGHT, 0))
    {
        lbs = (weight * 100000) / 4536;

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
    DexScreen_AddTextPrinterParameterized(windowId, 0, labelText, x, y, 0);
    x += 30;
    DexScreen_AddTextPrinterParameterized(windowId, 0, buffer, x, y, 0);
}

void DexScreen_PrintMonFlavorText(u8 windowId, u16 species, u8 x, u8 y)
{
    struct TextPrinterTemplate printerTemplate;
    u16 length;
    s32 v1;

    species = SpeciesToNationalPokedexNum(species);

    if (DexScreen_GetSetPokedexFlag(species, 1, 0))
    {
        printerTemplate.currentChar = gPokedexEntries[species].description;
        printerTemplate.windowId = windowId;
        printerTemplate.fontId = 2;
        printerTemplate.letterSpacing = 1;
        printerTemplate.lineSpacing = 0;
        printerTemplate.unk = 0;
        printerTemplate.fgColor = 1;
        printerTemplate.bgColor = 0;
        printerTemplate.shadowColor = 2;

        length = GetStringWidth(2, gPokedexEntries[species].description, 0);
        v1 = x + (240 - length) / 2;

        if (v1 > 0)
            x = v1;
        else
            x = 0;

        printerTemplate.x = x;
        printerTemplate.y = y;
        printerTemplate.currentX = x;
        printerTemplate.currentY = y;

        AddTextPrinter(&printerTemplate, TEXT_SKIP_DRAW, NULL);
    }
}

void DexScreen_DrawMonFootprint(u8 a0, u16 species, u8 a2, u8 a3)
{
    u16 i, j, unused, v3;
    u8 v4, v5;
    u8 * buffer;
    u8 * footprint;

    if (!(DexScreen_GetSetPokedexFlag(species, 1, 1)))
        return;
    footprint = (u8 *)(gMonFootprint_None); //this is what where replaced  gfootprint stuff
    buffer = gDecompressionBuffer;
    unused = 0;
    v3 = 0;

    for (i = 0; i < 32; i++)
    {
        v4 = footprint[i];
        for (j = 0; j < 4; j++)
        {
            v5 = 0;
            if (v4 & (1 << (j * 2)))
                v5 |= 1;
            if (v4 & (2 << (j * 2)))
                v5 |= 16;
            buffer[v3] = v5;
            v3++;
        }
    }
    BlitBitmapRectToWindow(a0, buffer, 0, 0, 16, 16, a2, a3, 16, 16);
}

#define END_LIST 0XFFFF
//when have error defined in text discarded in data
//for in array thats an issue of not using const, when I should
//when done make global and move to .h file
const u32 sDexAdjusting[] =
{
    SPECIES_BULBASAUR,
    SPECIES_IVYSAUR,
    SPECIES_CHARMANDER,
    SPECIES_SQUIRTLE,
    SPECIES_WARTORTLE,
    SPECIES_CATERPIE,
    SPECIES_METAPOD,
    SPECIES_WEEDLE,
    SPECIES_KAKUNA,
    SPECIES_PIDGEY,
    SPECIES_RATTATA,
    SPECIES_SPEAROW,
    SPECIES_EKANS,
    SPECIES_SANDSHREW,
    SPECIES_NIDORAN_F,
    SPECIES_NIDORAN_M,
    SPECIES_CLEFAIRY,
    SPECIES_VULPIX,
    SPECIES_JIGGLYPUFF,
    SPECIES_ODDISH,
    SPECIES_VILEPLUME,
    SPECIES_PARAS,
    SPECIES_PARASECT,
    SPECIES_VENONAT,
    SPECIES_DIGLETT,
    SPECIES_DUGTRIO,
    SPECIES_MEOWTH,
    SPECIES_PERSIAN,
    SPECIES_MANKEY,
    SPECIES_GROWLITHE,
    SPECIES_POLIWAG,
    SPECIES_POLIWHIRL,
    SPECIES_ABRA,
    SPECIES_MACHOP,
    SPECIES_BELLSPROUT,
    SPECIES_WEEPINBELL,
    SPECIES_GEODUDE,
    SPECIES_GRAVELER,
    SPECIES_SLOWPOKE,
    SPECIES_MAGNEMITE,
    SPECIES_FARFETCHD,
    SPECIES_SEEL,
    SPECIES_GRIMER,
    SPECIES_MUK,
    SPECIES_SHELLDER,
    SPECIES_KRABBY,
    SPECIES_VOLTORB,
    SPECIES_ELECTRODE,
    SPECIES_EXEGGCUTE,
    SPECIES_CUBONE,
    SPECIES_MAROWAK,
    SPECIES_RHYHORN,
    SPECIES_TANGELA,
    SPECIES_STARYU,
    SPECIES_JYNX,
    SPECIES_DITTO,
    SPECIES_EEVEE,
    SPECIES_JOLTEON,
    SPECIES_FLAREON,
    SPECIES_PORYGON,
    SPECIES_OMANYTE,
    SPECIES_OMASTAR,
    SPECIES_KABUTO,
    SPECIES_DRATINI,
    SPECIES_MEW,

    
    //gen 2
    SPECIES_CHIKORITA,
    SPECIES_CYNDAQUIL,
    SPECIES_TOTODILE,
    SPECIES_HOOTHOOT,
    SPECIES_SPINARAK,
    SPECIES_CHINCHOU,
    SPECIES_LANTURN,
    SPECIES_PICHU,
    SPECIES_CLEFFA,
    SPECIES_IGGLYBUFF,
    SPECIES_TOGEPI,
    SPECIES_TOGETIC,
    SPECIES_NATU,
    SPECIES_MAREEP,
    SPECIES_BELLOSSOM,
    SPECIES_MARILL,
    SPECIES_YANMA,
    SPECIES_WOOPER,
    SPECIES_MURKROW,
    SPECIES_UNOWN,
    SPECIES_DUNSPARCE,
    SPECIES_SNUBBULL,
    SPECIES_SHUCKLE,
    SPECIES_TEDDIURSA,
    SPECIES_SLUGMA,
    SPECIES_MAGCARGO,
    SPECIES_SWINUB,
    SPECIES_PILOSWINE,
    SPECIES_CORSOLA,
    SPECIES_REMORAID,
    SPECIES_OCTILLERY,
    SPECIES_HOUNDOUR,
    SPECIES_PHANPY,
    SPECIES_PORYGON2,
    SPECIES_SMOOCHUM,
    SPECIES_ELEKID,
    SPECIES_MAGBY,
    //GEN 3
    SPECIES_MUDKIP,
    SPECIES_POOCHYENA,
    SPECIES_ZIGZAGOON,
    SPECIES_WURMPLE,
    SPECIES_SILCOON,
    SPECIES_CASCOON,
    SPECIES_LOTAD,
    SPECIES_LOMBRE,
    SPECIES_SEEDOT,
    SPECIES_TAILLOW,
    SPECIES_WINGULL,
    SPECIES_RALTS,
    SPECIES_SURSKIT,
    SPECIES_SHROOMISH,
    SPECIES_SLAKOTH,
    SPECIES_NINCADA,
    SPECIES_WHISMUR,
    SPECIES_MAKUHITA,
    SPECIES_AZURILL,
    SPECIES_NOSEPASS,
    SPECIES_SKITTY,
    SPECIES_SABLEYE,
    SPECIES_MAWILE,
    SPECIES_ARON,
    SPECIES_LAIRON,
    SPECIES_ELECTRIKE,
    SPECIES_GULPIN,
    SPECIES_NUMEL,
    SPECIES_CAMERUPT,
    SPECIES_TRAPINCH,
    SPECIES_VIBRAVA,
    SPECIES_CACNEA,
    SPECIES_SWABLU,
    SPECIES_SEVIPER,
    SPECIES_BARBOACH,
    SPECIES_CORPHISH,
    SPECIES_BALTOY,
    SPECIES_ANORITH,
    SPECIES_FEEBAS,
    SPECIES_SHUPPET,
    SPECIES_WYNAUT,
    SPECIES_SPHEAL,
    SPECIES_SEALEO,
    SPECIES_CLAMPERL,
    SPECIES_LUVDISC,
    SPECIES_BAGON,
    SPECIES_SHELGON,
    SPECIES_METAGROSS,
    SPECIES_JIRACHI,
    //GEN 4,
    SPECIES_TURTWIG,
    SPECIES_CHIMCHAR,
    SPECIES_PIPLUP,
    SPECIES_STARLY,
    SPECIES_STARAVIA,
    SPECIES_BIDOOF,
    SPECIES_SHINX,
    SPECIES_LUXIO,
    SPECIES_BUDEW,
    SPECIES_CRANIDOS,
    SPECIES_SHIELDON,
    SPECIES_BURMY,
    SPECIES_PACHIRISU,
    SPECIES_BUIZEL,
    SPECIES_CHERUBI,
    SPECIES_SHELLOS,
    SPECIES_AMBIPOM,
    SPECIES_CHINGLING,
    SPECIES_STUNKY,
    SPECIES_BONSLY,
    SPECIES_HAPPINY,
    SPECIES_CHATOT,
    SPECIES_MUNCHLAX,
    SPECIES_RIOLU,
    SPECIES_HIPPOPOTAS,
    SPECIES_HIPPOWDON,
    SPECIES_SNOVER,
    SPECIES_GLACEON,
    SPECIES_FROSLASS,
    SPECIES_SHAYMIN,
    //GEN 5
    SPECIES_SNIVY,
    SPECIES_TEPIG,
    SPECIES_OSHAWOTT,
    SPECIES_PATRAT,
    SPECIES_LILLIPUP,
    SPECIES_PURRLOIN,
    SPECIES_PANSAGE,
    SPECIES_PANPOUR,
    SPECIES_PANSEAR,
    SPECIES_MUNNA,
    SPECIES_PIDOVE,
    SPECIES_ROGGENROLA,
    SPECIES_BOLDORE,
    SPECIES_TIMBURR,
    SPECIES_CONKELDURR,
    SPECIES_TYMPOLE,
    SPECIES_PALPITOAD,
    SPECIES_SEWADDLE,
    SPECIES_SWADLOON,
    SPECIES_VENIPEDE,
    SPECIES_COTTONEE,
    SPECIES_BASCULIN,
    SPECIES_SANDILE,
    SPECIES_DARUMAKA,
    SPECIES_DWEBBLE,
    SPECIES_SCRAGGY,
    SPECIES_ARCHEN,
    SPECIES_TRUBBISH,
    SPECIES_ZORUA,
    SPECIES_DUCKLETT,
    SPECIES_VANILLITE,
    SPECIES_DEERLING,
    SPECIES_EMOLGA,
    SPECIES_KARRABLAST,
    SPECIES_FOONGUS,
    SPECIES_JOLTIK,
    SPECIES_GALVANTULA,
    SPECIES_KLINK,
    SPECIES_TYNAMO,
    SPECIES_ELGYEM,
    SPECIES_AXEW,
    SPECIES_CUBCHOO,
    SPECIES_SHELMET,
    SPECIES_STUNFISK,
    SPECIES_MIENFOO,
    SPECIES_PAWNIARD,
    SPECIES_RUFFLET,
    SPECIES_DURANT,
    SPECIES_DEINO,
    SPECIES_LARVESTA,
    SPECIES_MELOETTA,
    //GEN 6
    SPECIES_CHESPIN,
    SPECIES_QUILLADIN,
    SPECIES_FENNEKIN,
    SPECIES_FROAKIE,
    SPECIES_FLETCHLING,
    SPECIES_FLETCHINDER,
    SPECIES_SCATTERBUG,
    SPECIES_SPEWPA,
    SPECIES_LITLEO,
    SPECIES_FLABEBE,
    SPECIES_PANCHAM,
    SPECIES_ESPURR,
    SPECIES_SPRITZEE,
    SPECIES_BINACLE,
    SPECIES_SKRELP,
    SPECIES_CLAUNCHER,
    SPECIES_CLAWITZER,
    SPECIES_HELIOPTILE,
    SPECIES_TYRUNT,
    SPECIES_HAWLUCHA,
    SPECIES_DEDENNE,
    SPECIES_CARBINK,
    SPECIES_GOOMY,
    SPECIES_PHANTUMP,
    SPECIES_PUMPKABOO,
    SPECIES_BERGMITE,
    //GEN 7
    SPECIES_ROWLET,
    SPECIES_LITTEN,
    SPECIES_POPPLIO,
    SPECIES_PIKIPEK,
    SPECIES_YUNGOOS,
    SPECIES_GRUBBIN,
    SPECIES_CHARJABUG,
    SPECIES_ROCKRUFF,
    SPECIES_WISHIWASHI,
    SPECIES_MAREANIE,
    SPECIES_DEWPIDER,
    SPECIES_FOMANTIS,
    SPECIES_SALANDIT,
    SPECIES_STUFFUL,
    SPECIES_BOUNSWEET,
    SPECIES_WIMPOD,
    SPECIES_SANDYGAST,
    SPECIES_KOMALA,
    SPECIES_TOGEDEMARU,
    SPECIES_MIMIKYU,
    SPECIES_MELTAN,
    //GEN 8
    SPECIES_GROOKEY,
    SPECIES_SOBBLE,
    SPECIES_ROOKIDEE,
    SPECIES_BLIPBUG,
    SPECIES_DOTTLER,
    SPECIES_NICKIT,
    SPECIES_GOSSIFLEUR,
    SPECIES_WOOLOO,
    SPECIES_CHEWTLE,
    SPECIES_YAMPER,
    SPECIES_ROLYCOLY,
    SPECIES_APPLIN,
    SPECIES_SILICOBRA,
    SPECIES_SANDACONDA,
    SPECIES_ARROKUDA,
    SPECIES_BARRASKEWDA,
    SPECIES_TOXEL,
    SPECIES_SIZZLIPEDE,
    SPECIES_CLOBBOPUS,
    SPECIES_SINISTEA,
    SPECIES_HATENNA,
    SPECIES_IMPIDIMP,
    SPECIES_MILCERY,
    SPECIES_FALINKS,
    SPECIES_PINCURCHIN,
    SPECIES_SNOM,
    SPECIES_INDEEDEE,
    SPECIES_MORPEKO,
    SPECIES_CUFANT,
    SPECIES_DREEPY, //cephireon and fraejta need be added before truly done but otherwise done



    END_LIST,
}; //way list is turning out, it'd be a better idea, to instead use exceptions rather than additions,
//would greatly save time

#define CREATE_POKEDEX_PAGE
u8 DexScreen_DrawMonDexPage(bool8 a0)
{
    u32 i;
    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    for (i = 0; sDexAdjusting[i] != END_LIST; i++)
    {
        if (sPokedexScreenData->dexSpecies == sDexAdjusting[i]) //this works now just need a list of all mon I Need the bigger window for a make it do a loop
            break;
    }
    if (sPokedexScreenData->dexSpecies != sDexAdjusting[i]) //this works now just need a list of all mon I Need the bigger window for a make it do a loop
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic2_Large);
    else
        sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);   //sWindowTemplate_DexEntry_MonPic2_Large

    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    // Mon pic
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], 0);
    DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144); //interestingly using 104 makes it siloutted could use for dexnav vsonic
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    CopyWindowToVram(sPokedexScreenData->windowIds[0], 2);

    // Species stats
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[1], 0);
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
    FillWindowPixelBuffer(1, 255);
    if (a0 == FALSE)
    {
        DexScreen_AddTextPrinterParameterized(1, 0, gText_Cry, 8, 2, 4);
        DexScreen_PrintControlInfo(gText_NextDataCancel);
    }
    else
        DexScreen_PrintControlInfo(gText_Next);
    PutWindowTilemap(1);
    CopyWindowToVram(1, 2);

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
    monIsCaught = DexScreen_GetSetPokedexFlag(species, 1, 1);
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
            CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[i + 1], sAreaMapStructs_SeviiIslands[i].tilemap, 0, 0);
            SetWindowAttribute(sPokedexScreenData->windowIds[i + 1], WINDOW_TILEMAP_TOP, GetWindowAttribute(sPokedexScreenData->windowIds[i + 1], 2) + kantoMapVoff);
            PutWindowTilemap(sPokedexScreenData->windowIds[i + 1]);
            CopyWindowToVram(sPokedexScreenData->windowIds[i + 1], COPYWIN_GFX);
        }
    sPokedexScreenData->windowIds[8] = AddWindow(&sWindowTemplate_AreaMap_SpeciesName); //also dex number
    sPokedexScreenData->windowIds[9] = AddWindow(&sWindowTemplate_AreaMap_Size);
    sPokedexScreenData->windowIds[10] = AddWindow(&sWindowTemplate_AreaMap_Area);
    sPokedexScreenData->windowIds[11] = AddWindow(&sWindowTemplate_AreaMap_MonIcon);
    sPokedexScreenData->windowIds[12] = AddWindow(&sWindowTemplate_AreaMap_MonTypes);
    
    // Draw the mon icon
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[11], PIXEL_FILL(0));
    ListMenu_LoadMonIconPalette(160, species);
    ListMenu_DrawMonIconGraphics(sPokedexScreenData->windowIds[11], species, DexScreen_GetDefaultPersonality(species), 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[11]);
    CopyWindowToVram(sPokedexScreenData->windowIds[11], COPYWIN_GFX);
    
    // Print "Size"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[9], PIXEL_FILL(0));
    {
        s32 width = GetStringWidth(FONT_SMALL, gText_Size, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[9], 0, gText_Size, (sWindowTemplate_AreaMap_Size.width * 8 - width) / 2, 4, 0);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[9]);
    CopyWindowToVram(sPokedexScreenData->windowIds[9], COPYWIN_GFX);

    // Print "Area"
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[10], PIXEL_FILL(0));
    {
        s32 width = GetStringWidth(FONT_SMALL, gText_Area, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[10], 0, gText_Area, (sWindowTemplate_AreaMap_Area.width * 8 - width) / 2, 4, 0);
    }
    SetWindowAttribute(sPokedexScreenData->windowIds[10], 2, GetWindowAttribute(sPokedexScreenData->windowIds[10], 2) + kantoMapVoff);
    PutWindowTilemap(sPokedexScreenData->windowIds[10]);
    CopyWindowToVram(sPokedexScreenData->windowIds[10], 2);
    
    // Print species name
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[8], PIXEL_FILL(0));
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[8], FONT_SMALL, species, 0, 4);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[8], 2, gSpeciesNames[species], 3, 16, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[8]);
    CopyWindowToVram(sPokedexScreenData->windowIds[8], COPYWIN_GFX);
    
    // Type icons
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[12], PIXEL_FILL(0));
    ListMenuLoadStdPalAt(176, 1);

    if (monIsCaught)
    {
        BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type1, 0, 1);
        if (gBaseStats[species].type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type2, 32, 1);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[12]);
    CopyWindowToVram(sPokedexScreenData->windowIds[12], 2);
    ResetAllPicSprites();
    LoadPalette(sPalette_Silhouette, 288, 32);

    if (monIsCaught)
    {
        sPokedexScreenData->windowIds[14] = CreateMonPicSprite_HandleDeoxys(species, 8, DexScreen_GetDefaultPersonality(species), 1, 40, 104, 0, 65535);
        gSprites[sPokedexScreenData->windowIds[14]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.affineMode = 1;
        gSprites[sPokedexScreenData->windowIds[14]].oam.matrixNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[14]].pos2.y = gPokedexEntries[speciesId].pokemonOffset; //this is elevation of mon pic
        SetOamMatrix(2, gPokedexEntries[speciesId].pokemonScale, 0, 0, gPokedexEntries[speciesId].pokemonScale);
        sPokedexScreenData->windowIds[15] = CreateTrainerPicSprite(PlayerGenderToFrontTrainerPicId_Debug(gSaveBlock2Ptr->playerGender, 1), 1, 80, 104, 0, 65535);
        gSprites[sPokedexScreenData->windowIds[15]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[15]].oam.affineMode = 1;
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
    sPokedexScreenData->areaMarkersTaskId = sub_8134230(species, TAG_AREA_MARKERS, 3, kantoMapVoff * 8);
    if (!(sub_81344E0(sPokedexScreenData->areaMarkersTaskId)))
    {
        // No markers, display "Area Unknown"
        BlitBitmapRectToWindow(sPokedexScreenData->windowIds[0], (void *)gUnknown_8443D00, 0, 0, 88, 16, 4, 28, 88, 16);
        {
            s32 width = GetStringWidth(0, gText_AreaUnknown, 0);
            DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[0], 0, gText_AreaUnknown, (96 - width) / 2, 29, 0);
        }
    }
    CopyWindowToVram(sPokedexScreenData->windowIds[0], 2);
   
    // Draw the control info
    FillWindowPixelBuffer(1, 255);
    DexScreen_AddTextPrinterParameterized(1, 0, gText_Cry, 8, 2, 4);
    DexScreen_PrintControlInfo(gText_CancelPreviousData);
    PutWindowTilemap(1);
    CopyWindowToVram(1, 2);

    return 1;
}


u8 sub_81067C0(void)
{
    int i;

    sub_81343F4(sPokedexScreenData->areaMarkersTaskId);

    for (i = 0; i < 13; i++)
        DexScreen_RemoveWindow(&sPokedexScreenData->windowIds[i]);
    if (sPokedexScreenData->windowIds[15] != 0xff)
        FreeAndDestroyTrainerPicSprite(sPokedexScreenData->windowIds[15]);
    if (sPokedexScreenData->windowIds[14] != 0xff)
        FreeAndDestroyMonPicSprite(sPokedexScreenData->windowIds[14]);
    return 0;
}

int DexScreen_CanShowMonInDex(u16 species)
{
    if (IsNationalPokedexEnabled() == TRUE)
        return TRUE;
    if (SpeciesToNationalPokedexNum(species) <= KANTO_DEX_COUNT)
        return TRUE;
    return TRUE; //change so all mon can show in dex
}

u8 DexScreen_CanShowMonInCategory(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;

    for (i = 0; i < 4; i++)
    {
        if (i < count)
        {
            species = gDexCategories[categoryNum].page[pageNum].species[i];
            if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
                return 1;
        }
    }
    return 0;
}

u8 DexScreen_IsCategoryUnlocked(u8 categoryNum)
{
    int i;
    u8 count;

    count = gDexCategories[categoryNum].count;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(categoryNum, i))
            return 1;

    return 0;
}

void sub_81068DC(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;
    sPokedexScreenData->numMonsOnPage = 0;

    for (i = 0; i < 4; i++)
        sPokedexScreenData->field_18[i] = 0xffff;
    for (i = 0; i < count; i++)
    {
        species = gDexCategories[categoryNum].page[pageNum].species[i];
        if (DexScreen_CanShowMonInDex(species) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
        {
            sPokedexScreenData->field_18[sPokedexScreenData->numMonsOnPage] = gDexCategories[categoryNum].page[pageNum].species[i];
            sPokedexScreenData->numMonsOnPage++;
        }
    }
}

u8 DexScreen_GetPageLimitsForCategory(u8 category)
{
    int i;
    u8 count, v2, v3;

    count = gDexCategories[category].count;
    v2 = 0xff;
    v3 = 0xff;

    for (i = 0; i < count; i++)
        if (DexScreen_CanShowMonInCategory(category, i))
        {
            if (v2 == 0xff)
                v2 = i;
            v3 = i;
        }
    if (v3 != 0xff)
    {
        sPokedexScreenData->firstPageInCategory = v2;
        sPokedexScreenData->lastPageInCategory = v3 + 1;
        return 0;
    }
    else
    {
        sPokedexScreenData->firstPageInCategory = 0;
        sPokedexScreenData->lastPageInCategory = 0;
        return 1;
    }
}

u8 DexScreen_LookUpCategoryBySpecies(u16 species)
{
    int i, j, k, categoryCount, categoryPageCount, posInPage;
    u16 dexSpecies;

    for (i = 0; i < NELEMS(gDexCategories); i++)
    {
        categoryCount = gDexCategories[i].count;
        for (j = 0; j < categoryCount; j++)
        {
            categoryPageCount = gDexCategories[i].page[j].count;
            for (k = 0, posInPage = 0; k < categoryPageCount; k++)
            {
                dexSpecies = gDexCategories[i].page[j].species[k];
                if (species == dexSpecies)//don't understand this
                {
                    sPokedexScreenData->category = i;
                    sPokedexScreenData->pageNum = j;
                    sPokedexScreenData->categoryCursorPosInPage = posInPage;
                    return FALSE;
                }
                if (DexScreen_CanShowMonInDex(dexSpecies) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
                    posInPage++;
            }
        }
    }
    return TRUE;
}

u8 sub_8106AF8(u16 a0)
{
    int i, v1;

    for (i = 0, v1 = 0; i < a0; i++)
        if (DexScreen_CanShowMonInCategory(sPokedexScreenData->category, i))
            v1++;

    return v1 + 1;
}

void sub_8106B34(void)
{
    if (JOY_NEW(START_BUTTON))
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, 125, 10);
}

#define DEX_REGISTER_DATA
u8 DexScreen_RegisterMonToPokedex(u16 species)
{
    DexScreen_GetSetPokedexFlag(species, 2, 1);
    DexScreen_GetSetPokedexFlag(species, 3, 1);

    if (!IsNationalPokedexEnabled() && SpeciesToNationalPokedexNum(species) > KANTO_DEX_COUNT)
        return CreateTask(Task_DexScreen_RegisterNonKantoMonBeforeNationalDex, 0); //couldn't remove this yet, breaks things cuz can't see all connections

    DexScreen_LoadResources();
    gTasks[sPokedexScreenData->taskId].func = Task_DexScreen_RegisterMonToPokedex;
    DexScreen_LookUpCategoryBySpecies(species);

    return sPokedexScreenData->taskId;
}

static void Task_DexScreen_RegisterNonKantoMonBeforeNationalDex(u8 taskId)
{
    DestroyTask(taskId);
}

static void Task_DexScreen_RegisterMonToPokedex(u8 taskId)
{
    u8 i;
    //trying empty bracket in place of i, since I'm not actually looping anything
    //didn't work without i for no apparent reason
    //pretty sure this works because its just one page, I think I need a variable for page too
    u16 species = gDexCategories[sPokedexScreenData->category].page[sPokedexScreenData->pageNum].species[i]; //no idea if work
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
        if (sub_8102798())
            DestroyTask(taskId);
        break;
    case 3:
        DexScreen_CreateCategoryListGfx(1);
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
        BeginNormalPaletteFade(0xffffffff, 0, 16, 0, 0xffff);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        ShowBg(0);

        sPokedexScreenData->state = 5;
        break;
    case 5: //think for when mon first caught
        gTasks[taskId].data[0] = 30;

        sPokedexScreenData->categoryPageCursorTaskId = ListMenuAddCursorObjectInternal(&sCursorStruct_SmallCategoryPage, 0);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        DexScreen_CreateCategoryPageSelectionCursor(sPokedexScreenData->categoryCursorPosInPage);
        DexScreen_UpdateCategoryPageCursorObject(sPokedexScreenData->categoryPageCursorTaskId, sPokedexScreenData->categoryCursorPosInPage, sPokedexScreenData->numMonsOnPage);

        if (gTasks[taskId].data[0])
            gTasks[taskId].data[0]--;
        else
        {
            ListMenuRemoveCursorObject(sPokedexScreenData->categoryPageCursorTaskId, 0);
            sPokedexScreenData->state = 7;
        }
        break;
    case 7:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->field_18[sPokedexScreenData->categoryCursorPosInPage];
        sPokedexScreenData->state = 8;
        break;
    case 8:
        DexScreen_DrawMonDexPage(1);
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

            PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, 125, 10);
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
    case 0:
        x = 8;
        break;
    case 1:
        x = (u32)(240 - GetStringWidth(2, str, 0)) / 2;
        break;
    case 2:
    default:
        x = 232 - GetStringWidth(2, str, 0);
        break;
    }

    DexScreen_AddTextPrinterParameterized(0, 2, str, x, 2, 4);
}
