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
    u16 field_12;
    u8 field_14;
    u8 field_15;
    u8 field_16;
    u8 field_17;
    u16 field_18[4];
    u8 categoryMonWindowIds[4];
    u8 categoryMonInfoWindowIds[4];
    u8 field_28;
    u8 field_29;
    u8 field_2A;
    u8 field_2B;
    u8 numMonsOnPage;
    u8 field_2D;
    u8 field_2E;
    u8 field_2F;
    u32 field_30;
    u16 field_34;
    u16 field_36;
    u16 field_38;
    u16 field_3A;
    u16 field_3C;
    u16 field_3E;
    u8 numericalOrderWindowId;
    u8 field_41;
    u8 field_42;
    struct ListMenuItem * field_44;
    u16 field_48;
    u8 windowIds[0x10];
    u16 dexSpecies;
    u16 * field_5C;
    u8 field_60;
    u8 field_61;
    u16 field_62;
    u8 field_64;
    u16 field_66;
    u16 field_68;
    u16 field_6A;
    u16 field_6C;
};

struct PokedexScreenWindowGfx
{
    const u16 * map;
    const u16 * pal;
};

struct PokedexCategoryPage
{
    const u16 * species;
    u8 count;
};

EWRAM_DATA struct PokedexScreenData * sPokedexScreenData = NULL;

static void sub_810287C(u8 taskId);
static void sub_8102C28(void);
static void sub_8102F80(u8 taskId);
static void sub_810317C(void);
static void sub_8103238(u8 taskId);
static void sub_810345C(void);
static u16 sub_8103518(u8 a0);
static void sub_8103924(const struct ListMenuTemplate * a0, u8 a1);
static u8 sub_81039F0(void);
static void sub_8103988(u8 a0);
static void sub_8103AC8(u8 taskId);
static u8 sub_8104234(void);
static int sub_8104284(void);
static void sub_81042EC(u8 taskId);
static bool32 sub_8104664(u8 a0);
void DexScreen_RemoveWindow(u8 *windowId_p);
void DexScreen_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 colorIdx);
static void sub_810491C(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx);
void DexScreen_PrintMonDexNo(u8 windowId, u8 fontId, u16 species, u8 x, u8 y);
static u16 sub_8104BBC(u8 caseId, bool8 whichDex);
void sub_8104C2C(const u8 *src);
void sub_8104E90(void);
bool8 sub_8104F0C(bool8 a0);
void sub_8105058(u8 a0);
void sub_8105178(u8 a0, u8 a1, u8 a2);
static bool8 sub_81052D0(u8 a0);
void DexScreen_DexPageZoomEffectFrame(u8 a0, u8 a1);
u8 DexScreen_DrawMonDexPage(u8 a0);
u8 RemoveDexPageWindows(void);
u8 DexScreen_DrawMonAreaPage(void);
bool8 sub_8106838(u8 category, u8 a1);
u8 sub_81068A0(u8 a0);
u8 sub_810699C(u8 category);
bool8 sub_8106A20(u16 a0);
u8 sub_81067C0(void);
void sub_81068DC(u8 category, u8 a1);
u8 sub_8106AF8(u16 a0);
void sub_8106B34(void);
void sub_8106E78(const u8 *a0, s32 a1);
static void sub_8102EC0(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void sub_8102F48(u8 windowId, s32 itemId, u8 y);
static void ItemPrintFunc_OrderedListMenu(u8 windowId, s32 itemId, u8 y);
static void sub_8106BD8(u8 taskId);
static void sub_8106BE8(u8 taskId);

#include "data/pokemon_graphics/footprint_table.h"

#ifdef SPECIES_NAME_EXPANSION
const u32 sCategoryMonLargeInfoBgTiles[] = INCBIN_U32("graphics/pokedex/large_mini_page.4bpp.lz");
const u32 sCategoryMonMediumInfoBgTiles[] = INCBIN_U32("graphics/pokedex/medium_mini_page.4bpp.lz");
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#else
const u32 sCategoryMonInfoBgTiles[] = INCBIN_U32("graphics/pokedex/mini_page.4bpp.lz");
#endif // SPECIES_NAME_EXPANSION

//const u8 sCategoryMonInfoBgTiles[] = INCBIN_U8("graphics/pokedex/mini_page.bin.lz");
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
const u16 gUnknown_8443460[] = INCBIN_U16("graphics/pokedex/unk_8443460.gbapal");
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
const u32 gUnknown_8443620[] = INCBIN_U32("graphics/pokedex/unk_8443620.bin.lz");
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
    .field_14 = -1,
    .field_15 = -1,
    .field_16 = -1,
    .field_18 = {-1, -1, -1, -1},
    .categoryMonWindowIds = {-1, -1, -1, -1},
    .categoryMonInfoWindowIds = {-1, -1, -1, -1},
    .numericalOrderWindowId = -1, 
    .windowIds = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    .field_60 = -1, 
    .field_61 = -1,
};


static const struct WindowTemplate sUnknown_8451F54 = {
   .bg = 1,
   .tilemapLeft = 1,
   .tilemapTop = 2,
   .width = 20,
   .height = 16,
   .paletteNum = 0,
   .baseBlock = 0x0008
 };

static const struct WindowTemplate sUnknown_8451F5C = {
   .bg = 1,
   .tilemapLeft = 21,
   .tilemapTop = 11,
   .width = 8,
   .height = 6,
   .paletteNum = 1,
   .baseBlock = 0x0148
 };

static const struct WindowTemplate sUnknown_8451F64 = {
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

static const struct ListMenuTemplate sUnknown_8452004 = {
    .items = sListMenuItems_KantoDexModeSelect,
    .moveCursorFunc = sub_8102EC0,
    .itemPrintFunc = sub_8102F48,
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

static const struct ListMenuTemplate sUnknown_84520BC = {
    .items = sUnknown_845201C,
    .moveCursorFunc = sub_8102EC0,
    .itemPrintFunc = sub_8102F48,
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
    .width = 26,
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
        .width = 8,
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
    .height = 3,
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
    .tilemapTop = 5,
    .width = 8,
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
} const gUnknown_8452254[] = {
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

static const struct ScrollArrowsTemplate sUnknown_84524B4 = {
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

//category window cursor, was 8 x 5 now 9 x 5  so need change cursor to width 72 from 64 for expansion
const struct CursorStruct sCursorStruct_CategoryPage = {
    .left = 0, 
    .top = 160,
    .rowWidth = 72, 
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

void sub_810250C(void)
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
    taskId = CreateTask(sub_810287C, 0);
    sPokedexScreenData = Alloc(sizeof(struct PokedexScreenData));
    *sPokedexScreenData = sUnknown_8451EE4;
    sPokedexScreenData->taskId = taskId;
    sPokedexScreenData->field_44 = Alloc(NATIONAL_DEX_COUNT * sizeof(struct ListMenuItem));
    sPokedexScreenData->field_6A = sub_8104BBC(0, 1);
    sPokedexScreenData->field_6C = sub_8104BBC(1, 1);
    sPokedexScreenData->field_66 = sub_8104BBC(0, 0);
    sPokedexScreenData->field_68 = sub_8104BBC(1, 0);
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
    sub_810250C();
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
        FREE_IF_NOT_NULL(sPokedexScreenData->field_44);
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

static void sub_810287C(u8 taskId)
{
    int i;
    switch (sPokedexScreenData->state)
    {
    case 0:
        sPokedexScreenData->unlockedCategories = 0;
        for (i = 0; i < 9; i++)
            sPokedexScreenData->unlockedCategories |= (sub_81068A0(i) << i);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_14);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_15);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_16);
        SetMainCallback2(sub_8102858);
        DestroyTask(taskId);
        break;
    case 2:
        sub_8102C28();
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
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
        if (IsNationalPokedexEnabled())
            sPokedexScreenData->field_60 = AddScrollIndicatorArrowPair(&sUnknown_84520E4, &sPokedexScreenData->field_62);
        else
            sPokedexScreenData->field_60 = AddScrollIndicatorArrowPair(&sUnknown_84520D4, &sPokedexScreenData->field_62);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->modeSelectInput = ListMenu_ProcessInput(sPokedexScreenData->field_17);
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
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
                if (sub_81068A0(sPokedexScreenData->modeSelectInput))
                {
                    RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
                    sPokedexScreenData->field_28 = sPokedexScreenData->modeSelectInput;
                    BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                    sPokedexScreenData->state = 7;
                }
                break;
            case 9:
            case 14:
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
                sPokedexScreenData->field_42 = sPokedexScreenData->modeSelectInput - 9;
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 9;
                break;
            case 10:
            case 11:
            case 12:
            case 13:
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
                sPokedexScreenData->field_42 = sPokedexScreenData->modeSelectInput - 9;
                sPokedexScreenData->field_38 = sPokedexScreenData->field_3A = 0;
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
        DestroyListMenuTask(sPokedexScreenData->field_17, &sPokedexScreenData->field_12, &sPokedexScreenData->field_10);
        FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_14);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_15);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_16);
        sPokedexScreenData->field_2B = 0;
        sPokedexScreenData->field_2D = 0;
        sPokedexScreenData->field_2F = 0;
        gTasks[taskId].func = sub_8103AC8;
        sPokedexScreenData->state = 0;
        break;
    case 8:
        DestroyListMenuTask(sPokedexScreenData->field_17, &sPokedexScreenData->field_12, &sPokedexScreenData->field_10);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_14);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_15);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_16);
        gTasks[taskId].func = sub_8103238;
        sPokedexScreenData->state = 0;
        break;
    case 9:
        DestroyListMenuTask(sPokedexScreenData->field_17, &sPokedexScreenData->field_12, &sPokedexScreenData->field_10);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_14);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_15);
        DexScreen_RemoveWindow(&sPokedexScreenData->field_16);
        gTasks[taskId].func = sub_8102F80;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void sub_8102C28(void)
{
    struct ListMenuTemplate listMenuTemplate;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(2, 0x000, 0, 0, 30, 20, 0x11);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 30, 20, 0x11);
    sPokedexScreenData->field_14 = AddWindow(&sUnknown_8451F54);
    sPokedexScreenData->field_15 = AddWindow(&sUnknown_8451F5C);
    sPokedexScreenData->field_16 = AddWindow(&sUnknown_8451F64);
    if (IsNationalPokedexEnabled())
    {
        listMenuTemplate = sUnknown_84520BC;
        listMenuTemplate.windowId = sPokedexScreenData->field_14;
        sPokedexScreenData->field_17 = ListMenuInit(&listMenuTemplate, sPokedexScreenData->field_12, sPokedexScreenData->field_10);
        FillWindowPixelBuffer(sPokedexScreenData->field_16, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_Seen, 0, 2, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_Kanto, 8, 13, 0);
        sub_810491C(sPokedexScreenData->field_16, 0, sPokedexScreenData->field_66, 52, 13, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_National, 8, 24, 0);
        sub_810491C(sPokedexScreenData->field_16, 0, sPokedexScreenData->field_6A, 52, 24, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_Owned, 0, 37, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_Kanto, 8, 48, 0);
        sub_810491C(sPokedexScreenData->field_16, 0, sPokedexScreenData->field_68, 52, 48, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 0, gText_National, 8, 59, 0);
        sub_810491C(sPokedexScreenData->field_16, 0, sPokedexScreenData->field_6C, 52, 59, 2);
    }
    else
    {
        listMenuTemplate = sUnknown_8452004;
        listMenuTemplate.windowId = sPokedexScreenData->field_14;
        sPokedexScreenData->field_17 = ListMenuInit(&listMenuTemplate, sPokedexScreenData->field_12, sPokedexScreenData->field_10);
        FillWindowPixelBuffer(sPokedexScreenData->field_16, PIXEL_FILL(0));
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 1, gText_Seen, 0, 9, 0);
        sub_810491C(sPokedexScreenData->field_16, 1, sPokedexScreenData->field_66, 32, 21, 2);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->field_16, 1, gText_Owned, 0, 37, 0);
        sub_810491C(sPokedexScreenData->field_16, 1, sPokedexScreenData->field_68, 32, 49, 2);
    }
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    sub_8106E78(gText_PokedexTableOfContents, 1);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    sub_8104C2C(gText_PickOK);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_GFX);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_GFX);
    PutWindowTilemap(sPokedexScreenData->field_16);
    CopyWindowToVram(sPokedexScreenData->field_16, COPYWIN_GFX);
}

static void sub_8102EC0(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (!onInit)
        PlaySE(SE_SELECT);
    if (itemIndex == LIST_CANCEL)
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->field_15, sTopMenuSelectionIconTiles_Cancel, 0x000, 0x000);
        LoadPalette(gUnknown_8443460, 0x10, 0x20);
    }
    else
    {
        CopyToWindowPixelBuffer(sPokedexScreenData->field_15, sTopMenuSelectionIconGfxPtrs[itemIndex].map, 0x000, 0x000);
        LoadPalette(sTopMenuSelectionIconGfxPtrs[itemIndex].pal, 0x10, 0x20);
    }
    PutWindowTilemap(sPokedexScreenData->field_15);
    CopyWindowToVram(sPokedexScreenData->field_15, COPYWIN_GFX);
}

static void sub_8102F48(u8 windowId, s32 itemId, u8 y)
{
    u32 itemId_ = itemId;
    if (itemId_ > 8 || sPokedexScreenData->unlockedCategories & (1 << itemId_))
        ListMenuOverrideSetColors(1, 0, 3);
    else
        ListMenuOverrideSetColors(10, 0, 11);
}

static void sub_8102F80(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(0x10, 0);
        ListMenuLoadStdPalAt(0x20, 1);
        sPokedexScreenData->field_48 = sub_8103518(sPokedexScreenData->field_42);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        sub_8103988(sPokedexScreenData->field_42);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = sub_810287C;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sub_810317C();
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
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
        sPokedexScreenData->field_60 = sub_81039F0();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->field_30 = ListMenu_ProcessInput(sPokedexScreenData->field_41);
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if ((sPokedexScreenData->field_30 >> 16) & 1)
            {
                sPokedexScreenData->dexSpecies = sPokedexScreenData->field_30;
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        sub_8103988(sPokedexScreenData->field_42);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = sub_81042EC;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void sub_810317C(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->field_44;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->field_48;
    sub_8103924(&template, sPokedexScreenData->field_42);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    sub_8106E78(gText_PokemonListNoColor, 1);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    sub_8104C2C(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static void sub_8103238(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        ListMenuLoadStdPalAt(0x10, 0);
        ListMenuLoadStdPalAt(0x20, 1);
        sPokedexScreenData->field_48 = sub_8103518(sPokedexScreenData->field_42);
        sPokedexScreenData->state = 2;
        break;
    case 1:
        sub_8103988(sPokedexScreenData->field_42);
        HideBg(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        gTasks[taskId].func = sub_810287C;
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sub_810345C();
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
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
        sPokedexScreenData->field_60 = sub_81039F0();
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sPokedexScreenData->field_30 = ListMenu_ProcessInput(sPokedexScreenData->field_41);
        ListMenuGetScrollAndRow(sPokedexScreenData->field_17, &sPokedexScreenData->field_62, NULL);
        if (JOY_NEW(A_BUTTON))
        {
            if (((sPokedexScreenData->field_30 >> 16) & 1) && !sub_8106A20(sPokedexScreenData->field_30))
            {
                RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
                BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
                sPokedexScreenData->state = 7;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
            BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
            sPokedexScreenData->state = 1;
        }
        break;
    case 7:
        sub_8103988(sPokedexScreenData->field_42);
        FillBgTilemapBufferRect_Palette0(1, 0x000, 0, 0, 32, 20);
        CopyBgTilemapBufferToVram(1);
        DexScreen_RemoveWindow(&sPokedexScreenData->numericalOrderWindowId);
        sPokedexScreenData->field_2F = 1;
        gTasks[taskId].func = sub_8103AC8;
        sPokedexScreenData->state = 0;
        break;
    }
}

static void sub_810345C(void)
{
    struct ListMenuTemplate template;
    FillBgTilemapBufferRect(3, 0x00E, 0, 0, 30, 20, 0x00);
    FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
    sPokedexScreenData->numericalOrderWindowId = AddWindow(&sWindowTemplate_OrderedListMenu);
    template = sListMenuTemplate_OrderedListMenu;
    template.items = sPokedexScreenData->field_44;
    template.windowId = sPokedexScreenData->numericalOrderWindowId;
    template.totalItems = sPokedexScreenData->field_48;
    sub_8103924(&template, sPokedexScreenData->field_42);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    sub_8106E78(gText_SearchNoColor, 1);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    sub_8104C2C(gText_PickOKExit);
    CopyWindowToVram(0, COPYWIN_GFX);
    CopyWindowToVram(1, COPYWIN_GFX);
}

static u16 sub_8103518(u8 a0)
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
    case 0:
        for (i = 0; i < KANTO_DEX_COUNT; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
            if (seen)
            {
                sPokedexScreenData->field_44[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->field_44[i].label = gText_5Dashes;
            }
            sPokedexScreenData->field_44[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    case 1:
        for (i = 0; i < SPECIES_CHIMECHO; i++)
        {
            ndex_num = gPokedexOrder_Alphabetical[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (seen)
                {
                    sPokedexScreenData->field_44[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->field_44[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case 2:
        for (i = 0; i < NUM_SPECIES - 1; i++)
        {
            ndex_num = SpeciesToNationalPokedexNum(gPokedexOrder_Type[i]);
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->field_44[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->field_44[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case 3:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = gPokedexOrder_Weight[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->field_44[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->field_44[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case 4:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = gPokedexOrder_Height[i];
            if (ndex_num <= max_n)
            {
                seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
                caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
                if (caught)
                {
                    sPokedexScreenData->field_44[ret].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                    sPokedexScreenData->field_44[ret].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
                    ret++;
                }
            }
        }
        break;
    case 5:
        for (i = 0; i < NATIONAL_DEX_COUNT; i++)
        {
            ndex_num = i + 1;
            seen = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_SEEN, 0);
            caught = DexScreen_GetSetPokedexFlag(ndex_num, FLAG_GET_CAUGHT, 0);
            if (seen)
            {
                sPokedexScreenData->field_44[i].label = gSpeciesNames[NationalPokedexNumToSpecies(ndex_num)];
                ret = ndex_num;
            }
            else
            {
                sPokedexScreenData->field_44[i].label = gText_5Dashes;
            }
            sPokedexScreenData->field_44[i].index = (caught << 17) + (seen << 16) + NationalPokedexNumToSpecies(ndex_num);
        }
        break;
    }
    return ret;
}

static void sub_8103924(const struct ListMenuTemplate * template, u8 a1)
{
    switch (a1)
    {
    default:
    case 0:
        sPokedexScreenData->field_41 = ListMenuInitInRect(template, &sListMenuRects_OrderedList, sPokedexScreenData->field_36, sPokedexScreenData->field_34);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        sPokedexScreenData->field_41 = ListMenuInitInRect(template, &sListMenuRects_OrderedList, sPokedexScreenData->field_3A, sPokedexScreenData->field_38);
        break;
    case 5:
        sPokedexScreenData->field_41 = ListMenuInitInRect(template, &sListMenuRects_OrderedList, sPokedexScreenData->field_3E, sPokedexScreenData->field_3C);
        break;
    }
}

static void sub_8103988(u8 a0)
{
    switch (a0)
    {
    default:
    case 0:
        DestroyListMenuTask(sPokedexScreenData->field_41, &sPokedexScreenData->field_36, &sPokedexScreenData->field_34);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        DestroyListMenuTask(sPokedexScreenData->field_41, &sPokedexScreenData->field_3A, &sPokedexScreenData->field_38);
        break;
    case 5:
        DestroyListMenuTask(sPokedexScreenData->field_41, &sPokedexScreenData->field_3E, &sPokedexScreenData->field_3C);
        break;
    }
}

static u8 sub_81039F0(void)
{
    struct ScrollArrowsTemplate template = sDexOrderScrollArrowsTemplate;
    if (sPokedexScreenData->field_48 > sListMenuTemplate_OrderedListMenu.maxShowed)
        template.fullyDownThreshold = sPokedexScreenData->field_48 - sListMenuTemplate_OrderedListMenu.maxShowed;
    else
        template.fullyDownThreshold = 0;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->field_62);
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
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, 0, 0x28, y); //pokeball icon
        type1 = gBaseStats[species].type1;
        BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, type1 + 1, 0x80, y); //4bpp 32 width between these 2 type icons
        if (type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->numericalOrderWindowId, gBaseStats[species].type2 + 1, 0xA0, y);
    }
}

static void sub_8103AC8(u8 taskId)
{
    int r4;
    u8 *ptr;
    switch (sPokedexScreenData->state)
    {
    case 0:
        HideBg(3);
        HideBg(2);
        HideBg(1);
        sub_810699C(sPokedexScreenData->field_28);
        if (sPokedexScreenData->field_2B < sPokedexScreenData->field_29)
            sPokedexScreenData->field_2B = sPokedexScreenData->field_29;
        sPokedexScreenData->state = 2;
        break;
    case 1:
        sub_8104E90();
        HideBg(2);
        HideBg(1);
        switch (sPokedexScreenData->field_2F)
        {
        case 0:
        default:
            gTasks[taskId].func = sub_810287C;
            break;
        case 1:
            gTasks[taskId].func = sub_8103238;
            break;
        }
        sPokedexScreenData->state = 0;
        break;
    case 2:
        sub_8104F0C(0);
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        sub_8105058(0xFF);
        sPokedexScreenData->state = 3;
        break;
    case 3:
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 16, 0, RGB_WHITEALPHA);
        ShowBg(3);
        ShowBg(2);
        ShowBg(1);
        sPokedexScreenData->state = 4;
        break;
    case 4:
        sPokedexScreenData->field_60 = sub_8104234();
        sPokedexScreenData->field_61 = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 5;
        break;
    case 5:
        sub_8105058(sPokedexScreenData->field_2D);
        sub_8105178(sPokedexScreenData->field_61, sPokedexScreenData->field_2D, sPokedexScreenData->numMonsOnPage);
        sPokedexScreenData->field_62 = sPokedexScreenData->field_2B;
        r4 = 0;
        if (JOY_NEW(A_BUTTON) && DexScreen_GetSetPokedexFlag(sPokedexScreenData->field_18[sPokedexScreenData->field_2D], FLAG_GET_SEEN, 1))
        {
            RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
            ListMenuRemoveCursorObject(sPokedexScreenData->field_61, 0);
            sPokedexScreenData->state = 12;
            break;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_LEFT))
        {
            if (sPokedexScreenData->field_2D != 0)
            {
                sPokedexScreenData->field_2D--;
                PlaySE(SE_SELECT);
                break;
            }
            else
                r4 = 1;
        }
        if (!JOY_HELD(R_BUTTON) && JOY_REPT(DPAD_RIGHT))
        {
            if (sPokedexScreenData->field_2D < sPokedexScreenData->numMonsOnPage - 1)
            {
                sPokedexScreenData->field_2D++;
                PlaySE(SE_SELECT);
                break;
            }
            else
                r4 = 2;
        }
        if (r4 == 0)
            r4 = sub_8104284();
        switch (r4)
        {
        case 0:
            break;
        case 1:
            while (sPokedexScreenData->field_2B > sPokedexScreenData->field_29)
            {
                sPokedexScreenData->field_2B--;
                if (sub_8106838(sPokedexScreenData->field_28, sPokedexScreenData->field_2B))
                {
                    sPokedexScreenData->state = 8;
                    break;
                }
            }
            if (sPokedexScreenData->state != 8)
                sPokedexScreenData->state = 6;
            break;
        case 2:
            while (sPokedexScreenData->field_2B < sPokedexScreenData->field_2A - 1)
            {
                sPokedexScreenData->field_2B++;
                if (sub_8106838(sPokedexScreenData->field_28, sPokedexScreenData->field_2B))
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
        RemoveScrollIndicatorArrowPair(sPokedexScreenData->field_60);
        ListMenuRemoveCursorObject(sPokedexScreenData->field_61, 0);
        BeginNormalPaletteFade(0xFFFF7FFF, 0, 0, 16, RGB_WHITEALPHA);
        sPokedexScreenData->state = 1;
        break;
    case 8:
    case 10:
        sub_8104E90();
        sub_8105058(0xFF);
        ListMenuUpdateCursorObject(sPokedexScreenData->field_61, 0, 0xA0, 0);
        sPokedexScreenData->field_2E = 0;
        sPokedexScreenData->data[0] = 0;
        sPokedexScreenData->state++;
        break;
    case 9:
        if (sub_81052D0(0))
        {
            sPokedexScreenData->field_2D = sPokedexScreenData->numMonsOnPage - 1;
            sPokedexScreenData->state = 5;
        }
        break;
    case 11:
        if (sub_81052D0(1))
        {
            sPokedexScreenData->field_2D = 0;
            sPokedexScreenData->state = 5;
        }
        break;
    case 12:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->field_18[sPokedexScreenData->field_2D];
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
        sub_8104F0C(0);
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

static u8 sub_8104234(void)
{
    struct ScrollArrowsTemplate template = sUnknown_84524B4;
    template.fullyUpThreshold = sPokedexScreenData->field_29;
    template.fullyDownThreshold = sPokedexScreenData->field_2A - 1;
    sPokedexScreenData->field_62 = sPokedexScreenData->field_2B;
    return AddScrollIndicatorArrowPair(&template, &sPokedexScreenData->field_62);
}

static int sub_8104284(void)
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

static void sub_81042EC(u8 taskId)
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
        gTasks[taskId].func = sub_8102F80;
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
        sPokedexScreenData->dexSpecies = sPokedexScreenData->field_30;
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

    switch (sPokedexScreenData->field_42)
    {
    default:
    case 0:
        r12 = &sPokedexScreenData->field_36;
        r6 = &sPokedexScreenData->field_34;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        r12 = &sPokedexScreenData->field_3A;
        r6 = &sPokedexScreenData->field_38;
        break;
    case 5:
        r12 = &sPokedexScreenData->field_3E;
        r6 = &sPokedexScreenData->field_3C;
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
            if ((sPokedexScreenData->field_44[r3].index >> 16) & 1)
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
        if (r3 == sPokedexScreenData->field_48 - 1)
        {
            return FALSE;
        }

        r3++;
        while (r3 < sPokedexScreenData->field_48) //Should be while (++r3 < sPokedexScreenData->field_48) without the r3++ in the body or before the while at all, but this is needed to match.
        {
            if ((sPokedexScreenData->field_44[r3].index >> 16) & 1)
                break;
            r3++;
        }
        if (r3 >= sPokedexScreenData->field_48)
        {
            return FALSE;
        }
    }
    sPokedexScreenData->field_30 = sPokedexScreenData->field_44[r3].index;

    if (sPokedexScreenData->field_48 > 9)
    {
        if (r3 < 4)
        {
            *r12 = 0;
            *r6 = r3;
        }
        else if (r3 >= (sPokedexScreenData->field_48 - 4))
        {
            *r12 = (sPokedexScreenData->field_48 - 9);
            *r6 = r3 + 9 - (sPokedexScreenData->field_48);
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

static void sub_810491C(u8 windowId, u8 fontId, u16 num, u8 x, u8 y, u8 colorIdx)
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

u32 sub_81049CC(int species)
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
    LoadMonPicInWindow(species, 8, sub_81049CC(species), TRUE, paletteOffset >> 4, windowId);
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
    return retVal;
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
            if (DexScreen_GetSetPokedexFlag(i + 1, caseId, FALSE))
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

void sub_8104C2C(const u8 *src)
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

void sub_8104E90(void)
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
    sub_8106E78(buffer, 2);
}

bool8 sub_8104F0C(bool8 a0)
{
    FillBgTilemapBufferRect_Palette0(3, 2, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 32, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 32, 20);
    sub_81068DC(sPokedexScreenData->field_28, sPokedexScreenData->field_2B);
    FillWindowPixelBuffer(0, PIXEL_FILL(15));
    if (a0)
    {
        sub_8106E78(sDexCategoryNamePtrs[sPokedexScreenData->field_28], 1);
    }
    else
    {
        sub_8106E78(sDexCategoryNamePtrs[sPokedexScreenData->field_28], 0);
        sub_8104EC0(0, sub_8106AF8(sPokedexScreenData->field_2B), sub_8106AF8(sPokedexScreenData->field_2A - 1), 160, 2);
    }
    CopyWindowToVram(0, COPYWIN_GFX);
    FillWindowPixelBuffer(1, PIXEL_FILL(15));
    if (!a0)
        sub_8104C2C(gText_PickFlipPageCheckCancel);
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

void sub_8105058(u8 a0)
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

void sub_8105178(u8 a0, u8 a1, u8 a2)
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
        sub_8104F0C(FALSE);
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
        sub_8104F0C(FALSE);
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
        tileLeft = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->field_2D][2];
        tileTop = sCategoryPageIconCoords[sPokedexScreenData->numMonsOnPage - 1][sPokedexScreenData->field_2D][3];
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
    divY = (top + 1) + ((height / 2) - 1);// The horizontal divider    //this determines space for dex entries 
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
    footprint = (u8 *)(gMonFootprintTable[species]);
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

#define CREATE_POKEDEX_PAGE
u8 DexScreen_DrawMonDexPage(bool8 a0)
{
    DexScreen_DexPageZoomEffectFrame(3, 6);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_DexEntry_MonPic);
    sPokedexScreenData->windowIds[1] = AddWindow(&sWindowTemplate_DexEntry_SpeciesStats);
    sPokedexScreenData->windowIds[2] = AddWindow(&sWindowTemplate_DexEntry_FlavorText);

    // Mon pic
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[0], 0);
    DexScreen_LoadMonPicInWindow(sPokedexScreenData->windowIds[0], sPokedexScreenData->dexSpecies, 144);
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
        sub_8104C2C(gText_NextDataCancel);
    }
    else
        sub_8104C2C(gText_Next);
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
    u8 v1, v2;
    bool8 v3;
    s16 v4, v5;
    u16 speciesId, species;
    u16 v8;

    species = sPokedexScreenData->dexSpecies;
    speciesId = SpeciesToNationalPokedexNum(species);
    v3 = DexScreen_GetSetPokedexFlag(species, 1, 1);
    v1 = 28;
    v2 = 14;
    v4 = 0;
    v5 = 2;

    FillBgTilemapBufferRect_Palette0(3, 4, v4, v5, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 1028, v4 + 1 + v1, v5, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 2052, v4, v5 + 1 + v2, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 3076, v4 + 1 + v1, v5 + 1 + v2, 1, 1);
    FillBgTilemapBufferRect_Palette0(3, 5, v4 + 1, v5, v1, 1);
    FillBgTilemapBufferRect_Palette0(3, 2053, v4 + 1, v5 + 1 + v2, v1, 1);
    FillBgTilemapBufferRect_Palette0(3, 6, v4, v5 + 1, 1, v2);
    FillBgTilemapBufferRect_Palette0(3, 1030, v4 + 1 + v1, v5 + 1, 1, v2);
    FillBgTilemapBufferRect_Palette0(3, 1, v4 + 1, v5 + 1, v1, v2);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 2, 30, 16);

    v1 = 10;
    v2 = 6;
    v4 = 1;
    v5 = 9;

    FillBgTilemapBufferRect_Palette0(0, 29, v4, v5, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 1053, v4 + 1 + v1, v5, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 2077, v4, v5 + 1 + v2, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 3101, v4 + 1 + v1, v5 + 1 + v2, 1, 1);
    FillBgTilemapBufferRect_Palette0(0, 30, v4 + 1, v5, v1, 1);
    FillBgTilemapBufferRect_Palette0(0, 2078, v4 + 1, v5 + 1 + v2, v1, 1);
    FillBgTilemapBufferRect_Palette0(0, 31, v4, v5 + 1, 1, v2);
    FillBgTilemapBufferRect_Palette0(0, 1055, v4 + 1 + v1, v5 + 1, 1, v2);
    FillBgTilemapBufferRect_Palette0(2, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);

    sPokedexScreenData->field_64 = GetUnlockedSeviiAreas();
    v8 = 4;
    for (i = 3; i < 7; i++)
        if ((sPokedexScreenData->field_64 >> i) & 1)
            v8 = 0;

    sPokedexScreenData->windowIds[0] = AddWindow(&sWindowTemplate_AreaMap_Kanto);
    CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[0], (void *)gUnknown_8443620, 0, 0);
    SetWindowAttribute(sPokedexScreenData->windowIds[0], 2,
                       GetWindowAttribute(sPokedexScreenData->windowIds[0], 2) + v8);
    PutWindowTilemap(sPokedexScreenData->windowIds[0]);
    for (i = 0; i < 7; i++)
        if ((sPokedexScreenData->field_64 >> i) & 1)
        {
            sPokedexScreenData->windowIds[i + 1] = AddWindow(gUnknown_8452254[i].window);
            CopyToWindowPixelBuffer(sPokedexScreenData->windowIds[i + 1], gUnknown_8452254[i].tilemap, 0, 0);
            SetWindowAttribute(sPokedexScreenData->windowIds[i + 1], 2, GetWindowAttribute(sPokedexScreenData->windowIds[i + 1], 2) + v8);
            PutWindowTilemap(sPokedexScreenData->windowIds[i + 1]);
            CopyWindowToVram(sPokedexScreenData->windowIds[i + 1], 2);
        }
    sPokedexScreenData->windowIds[8] = AddWindow(&sWindowTemplate_AreaMap_SpeciesName);
    sPokedexScreenData->windowIds[9] = AddWindow(&sWindowTemplate_AreaMap_Size);
    sPokedexScreenData->windowIds[10] = AddWindow(&sWindowTemplate_AreaMap_Area);
    sPokedexScreenData->windowIds[11] = AddWindow(&sWindowTemplate_AreaMap_MonIcon);
    sPokedexScreenData->windowIds[12] = AddWindow(&sWindowTemplate_AreaMap_MonTypes);
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[11], 0);
    sub_8107CD8(160, species);
    sub_8107CF8(sPokedexScreenData->windowIds[11], species, sub_81049CC(species), 0, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[11]);
    CopyWindowToVram(sPokedexScreenData->windowIds[11], 2);
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[9], 0);
    {
        s32 width = GetStringWidth(0, gText_Size, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[9], 0, gText_Size, (sWindowTemplate_AreaMap_Size.width * 8 - width) / 2, 4, 0);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[9]);
    CopyWindowToVram(sPokedexScreenData->windowIds[9], 2);

    FillWindowPixelBuffer(sPokedexScreenData->windowIds[10], 0);
    {
        s32 width = GetStringWidth(0, gText_Area, 0);
        DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[10], 0, gText_Area, (sWindowTemplate_AreaMap_Area.width * 8 - width) / 2, 4, 0);
    }
    SetWindowAttribute(sPokedexScreenData->windowIds[10], 2, GetWindowAttribute(sPokedexScreenData->windowIds[10], 2) + v8);
    PutWindowTilemap(sPokedexScreenData->windowIds[10]);
    CopyWindowToVram(sPokedexScreenData->windowIds[10], 2);
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[8], 0);
    DexScreen_PrintMonDexNo(sPokedexScreenData->windowIds[8], 0, species, 0, 0);
    DexScreen_AddTextPrinterParameterized(sPokedexScreenData->windowIds[8], 2, gSpeciesNames[species], 3, 12, 0);
    PutWindowTilemap(sPokedexScreenData->windowIds[8]);
    CopyWindowToVram(sPokedexScreenData->windowIds[8], 2);
    FillWindowPixelBuffer(sPokedexScreenData->windowIds[12], 0);
    ListMenuLoadStdPalAt(176, 1);

    if (v3)
    {
        BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type1, 0, 1);
        if (gBaseStats[species].type1 != gBaseStats[species].type2)
            BlitMoveInfoIcon(sPokedexScreenData->windowIds[12], 1 + gBaseStats[species].type2, 32, 1);
    }
    PutWindowTilemap(sPokedexScreenData->windowIds[12]);
    CopyWindowToVram(sPokedexScreenData->windowIds[12], 2);
    ResetAllPicSprites();
    LoadPalette(sPalette_Silhouette, 288, 32);

    if (v3)
    {
        sPokedexScreenData->windowIds[14] = CreateMonPicSprite_HandleDeoxys(species, 8, sub_81049CC(species), 1, 40, 104, 0, 65535);
        gSprites[sPokedexScreenData->windowIds[14]].oam.paletteNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.affineMode = 1;
        gSprites[sPokedexScreenData->windowIds[14]].oam.matrixNum = 2;
        gSprites[sPokedexScreenData->windowIds[14]].oam.priority = 1;
        gSprites[sPokedexScreenData->windowIds[14]].pos2.y = gPokedexEntries[speciesId].pokemonOffset;
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
    sPokedexScreenData->areaMarkersTaskId = sub_8134230(species, TAG_AREA_MARKERS, 3, v8 * 8);
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
    sub_8104C2C(gText_CancelPreviousData);
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

int sub_8106810(u16 species)
{
    if (IsNationalPokedexEnabled() == TRUE)
        return TRUE;
    if (SpeciesToNationalPokedexNum(species) <= KANTO_DEX_COUNT)
        return TRUE;
    return FALSE;
}

u8 sub_8106838(u8 categoryNum, u8 pageNum)
{
    int i, count;
    u16 species;

    count = gDexCategories[categoryNum].page[pageNum].count;

    for (i = 0; i < 4; i++)
    {
        if (i < count)
        {
            species = gDexCategories[categoryNum].page[pageNum].species[i];
            if (sub_8106810(species) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
                return 1;
        }
    }
    return 0;
}

u8 sub_81068A0(u8 categoryNum)
{
    int i;
    u8 count;

    count = gDexCategories[categoryNum].count;

    for (i = 0; i < count; i++)
        if (sub_8106838(categoryNum, i))
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
        if (sub_8106810(species) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
        {
            sPokedexScreenData->field_18[sPokedexScreenData->numMonsOnPage] = gDexCategories[categoryNum].page[pageNum].species[i];
            sPokedexScreenData->numMonsOnPage++;
        }
    }
}

u8 sub_810699C(u8 category)
{
    int i;
    u8 count, v2, v3;

    count = gDexCategories[category].count;
    v2 = 0xff;
    v3 = 0xff;

    for (i = 0; i < count; i++)
        if (sub_8106838(category, i))
        {
            if (v2 == 0xff)
                v2 = i;
            v3 = i;
        }
    if (v3 != 0xff)
    {
        sPokedexScreenData->field_29 = v2;
        sPokedexScreenData->field_2A = v3 + 1;
        return 0;
    }
    else
    {
        sPokedexScreenData->field_29 = 0;
        sPokedexScreenData->field_2A = 0;
        return 1;
    }
}

u8 sub_8106A20(u16 a0)
{
    int i, j, k, categoryCount, categoryPageCount, v5;
    u16 species;

    for (i = 0; i < NELEMS(gDexCategories); i++)
    {
        categoryCount = gDexCategories[i].count;
        for (j = 0; j < categoryCount; j++)
        {
            categoryPageCount = gDexCategories[i].page[j].count;
            for (k = 0, v5 = 0; k < categoryPageCount; k++)
            {
                species = gDexCategories[i].page[j].species[k];
                if (a0 == species)
                {
                    sPokedexScreenData->field_28 = i;
                    sPokedexScreenData->field_2B = j;
                    sPokedexScreenData->field_2D = v5;
                    return 0;
                }
                if (sub_8106810(species) == TRUE && DexScreen_GetSetPokedexFlag(species, 0, 1))
                    v5++;
            }
        }
    }
    return 1;
}

u8 sub_8106AF8(u16 a0)
{
    int i, v1;

    for (i = 0, v1 = 0; i < a0; i++)
        if (sub_8106838(sPokedexScreenData->field_28, i))
            v1++;

    return v1 + 1;
}

void sub_8106B34(void)
{
    if (JOY_NEW(START_BUTTON))
        PlayCry_NormalNoDucking(sPokedexScreenData->dexSpecies, 0, 125, 10);
}

u8 sub_8106B60(u16 species)
{
    DexScreen_GetSetPokedexFlag(species, 2, 1);
    DexScreen_GetSetPokedexFlag(species, 3, 1);

    if (!IsNationalPokedexEnabled() && SpeciesToNationalPokedexNum(species) > KANTO_DEX_COUNT)
        return CreateTask(sub_8106BD8, 0);

    sub_810250C();
    gTasks[sPokedexScreenData->taskId].func = sub_8106BE8;
    sub_8106A20(species);

    return sPokedexScreenData->taskId;
}

static void sub_8106BD8(u8 taskId)
{
    DestroyTask(taskId);
}

static void sub_8106BE8(u8 taskId)
{
    switch (sPokedexScreenData->state)
    {
    case 0:
        sub_810699C(sPokedexScreenData->field_28);
        if (sPokedexScreenData->field_2B < sPokedexScreenData->field_29)
            sPokedexScreenData->field_2B = sPokedexScreenData->field_29;
        sPokedexScreenData->state = 3;
        break;
    case 1:
        RemoveDexPageWindows();
        sub_8104E90();

        gMain.state = 0;
        sPokedexScreenData->state = 2;
        break;
    case 2:
        if (sub_8102798())
            DestroyTask(taskId);
        break;
    case 3:
        sub_8104F0C(1);
        PutWindowTilemap(0);
        PutWindowTilemap(1);

        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);

        sub_8105058(0xff);

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
    case 5:
        gTasks[taskId].data[0] = 30;
        sPokedexScreenData->field_61 = ListMenuAddCursorObjectInternal(&sCursorStruct_CategoryPage, 0);
        sPokedexScreenData->state = 6;
        break;
    case 6:
        sub_8105058(sPokedexScreenData->field_2D);
        sub_8105178(sPokedexScreenData->field_61, sPokedexScreenData->field_2D, sPokedexScreenData->numMonsOnPage);

        if (gTasks[taskId].data[0])
            gTasks[taskId].data[0]--;
        else
        {
            ListMenuRemoveCursorObject(sPokedexScreenData->field_61, 0);
            sPokedexScreenData->state = 7;
        }
        break;
    case 7:
        sPokedexScreenData->dexSpecies = sPokedexScreenData->field_18[sPokedexScreenData->field_2D];
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

void sub_8106E78(const u8 * str, s32 mode)
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
