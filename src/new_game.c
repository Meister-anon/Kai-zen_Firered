#include "global.h"
#include "gflib.h"
#include "random.h"
#include "overworld.h"
#include "constants/maps.h"
#include "load_save.h"
#include "item_menu.h"
#include "tm_case.h"
#include "berry_pouch.h"
#include "quest_log.h"
#include "wild_encounter.h"
#include "event_data.h"
#include "mail_data.h"
#include "play_time.h"
#include "money.h"
#include "battle_records.h"
#include "pokemon_size_record.h"
#include "pokemon_storage_system.h"
#include "roamer.h"
#include "item.h"
#include "player_pc.h"
#include "berry.h"
#include "easy_chat.h"
#include "union_room_chat.h"
#include "mevent.h"
#include "renewable_hidden_items.h"
#include "trainer_tower.h"
#include "script.h"
#include "berry_powder.h"
#include "pokemon_jump.h"
#include "event_scripts.h"
#include "rtc.h"
//may be able to ues some of these functions to make a new file, for "new game+" just need be selective in which things get reset.
//my idea for new game place, was to keep all pokemon, change level (probably do by changing amount of exp) of party pokemon, 
//keep all items, so don't affect pc,  and keep track of when the new game +/ number of playthroughs.  Since i removed link battle, maybe I can have playthrough numbers shown 
//on card instead.

// this file's functions
//static void ResetMiniGamesResults(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < 4; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 0x10) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void) //
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_LR;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

static void sub_80549D4(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
}

static void WarpToPlayersRoom(void)
{
    SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagCursorPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop();
    ResetQuestLog();
    SeedWildEncounterRng(Random());
    ResetSpecialVars();
}

void NewGameInitData(void)
{
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
	RtcReset();
    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    sub_80549D4();
    ClearSav1();
    //ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    //gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->field_AC = 1;
    gSaveBlock2Ptr->field_AD = 0; //pretty sure these are pokedex stuff
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    //ResetFameChecker();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    ResetGameStats();
    //ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    sub_806E190();
    gPlayerPartyCount = 0; // change this & zeroplayerpartymons for new game+
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData();
    gSaveBlock1Ptr->registeredItem = 0;
    ClearBag();
    NewGameInitPCItems();
    sub_809C794();
    InitEasyChatPhrases();
    ResetTrainerFanClub();
    //UnionRoomChat_InitializeRegisteredTexts();
    //ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags();
    WarpToPlayersRoom();
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
    ResetTrainerTowerResults();
}
/*
static void ResetMiniGamesResults(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
   // SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokeJumpResults();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}*/
