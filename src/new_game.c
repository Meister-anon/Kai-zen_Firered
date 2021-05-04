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
//may be able to ues some of these functions to make a new file, for "new game+" just need be selective in which things get reset.
//my idea for new game place, was to keep all pokemon, change level (probably do by changing amount of exp) of party pokemon, 
//keep all items, so don't affect pc,  and keep track of when the new game +/ number of playthroughs.  Since i removed link battle, maybe I can have playthrough numbers shown 
//on card instead.

// will comment things I need to change or not change for newgame+

// this file's functions
//static void ResetMiniGamesResults(void);

// EWRAM vars
EWRAM_DATA bool8 gDifferentSaveFile = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst) // don't change
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

static void SetDefaultOptions(void) // don't change
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_MONO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_LR;
}

static void ClearPokedexFlags(void) // don't use
{
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));
}

static void sub_80549D4(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->battleTower, sizeof(gSaveBlock2Ptr->battleTower));
}

static void WarpToPlayersRoom(void) // use
{
    SetWarpDestination(MAP_GROUP(PALLET_TOWN_PLAYERS_HOUSE_2F), MAP_NUM(PALLET_TOWN_PLAYERS_HOUSE_2F), -1, 6, 6);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void) // don't use
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ZeroPlayerPartyMons(); // change use to make set party level function
    ZeroEnemyPartyMons(); // is this rival? don't know if will use
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

    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    sub_80549D4();
    ClearSav1();
    ClearMailData();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    gSaveBlock2Ptr->field_AC = 1;
    gSaveBlock2Ptr->field_AD = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData(); // need to take a closer look, but may keep if it resets flag stuff but I can still keep track of number of playthroughs oh ok this seems to reset flags keep for now.
    ResetFameChecker(); //keep
    SetMoney(&gSaveBlock1Ptr->money, 3000); // keep
    ResetGameStats();
    //ClearPlayerLinkBattleRecords();
    InitHeracrossSizeRecord();
    InitMagikarpSizeRecord();
    sub_806E190();
    gPlayerPartyCount = 0; // change this & zeroplayerpartymons for new game+
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    ClearRoamerData(); // keep
    gSaveBlock1Ptr->registeredItem = 0; // keep maybe not
    ClearBag();
    NewGameInitPCItems(); // may need to do this may not
    sub_809C794();
    InitEasyChatPhrases();
    ResetTrainerFanClub(); // think I'll leave this, may add some in on the joke text scripts
    UnionRoomChat_InitializeRegisteredTexts();
    //ResetMiniGamesResults();
    InitMEventData();
    SetAllRenewableItemFlags(); //keep
    WarpToPlayersRoom(); //keep
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags); // keep
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

void NewGame_Plus(void){
    gDifferentSaveFile = FALSE;
    ResetPlayerPartyMons();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    ClearRoamerData();
    ResetSpecialVars(); // not 100% on this one
    SetAllRenewableItemFlags(); //keep
    InitEventData(); //seems to reset all flags, I'll need to eventually make a custom one, that excludes the flags I want to stay. should be simple just use a not equal and a range i.e less than y greater than x
    ScriptContext2_RunNewScript(EventScript_ResetAllMapFlags);
    ResetBagCursorPositions();
    ResetTMCaseCursorPos();
    BerryPouch_CursorResetToTop(); // kind of want to remove certain items for this actually, like remove all healing items, key items would also pose a problem for progression...
    ResetQuestLog(); // ok here's the strat remove all items except capture items and fishing rods, (remember to edit those npc to check for rod first) 
    SeedWildEncounterRng(Random());// but also set hm checks to use a separate flag from badge, that just is also set when you beat the gym the first time.  As long as those aren't reset, newgame+ can have a cool open world experience.
    //ClearBag(); do custom, but this seems to check all bag pockets and then set the amount to remove to the full capacity,thus zeroing it out.
    WarpToPlayersRoom(); //otherwise the clear item functions works by selecting id / item slot and how much to remove. think I'll do if not item id rods clear pocket capacity for key items
}