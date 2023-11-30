#include "global.h"
#include "gflib.h"
#include "quest_log.h"
#include "list_menu.h"
#include "diploma.h"
#include "script.h"
#include "field_player_avatar.h"
#include "overworld.h"
#include "field_message_box.h"
#include "event_data.h"
#include "strings.h"
#include "battle.h"
#include "fieldmap.h"
#include "field_specials.h"
#include "region_map.h"
#include "task.h"
#include "battle_tower.h"
#include "field_camera.h"
#include "field_effect.h"
#include "event_object_movement.h"
#include "menu_indicators.h"
#include "random.h"
#include "mail_data.h"
#include "help_system.h"
#include "pokemon_storage_system.h"
#include "script_menu.h"
#include "data.h"
#include "pokedex.h"
#include "text_window.h"
#include "menu.h"
#include "mevent.h"
#include "naming_screen.h"
#include "party_menu.h"
#include "dynamic_placeholder_text_util.h"
#include "new_menu_helpers.h"
#include "constants/songs.h"
#include "constants/pokemon.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "constants/moves.h"
#include "constants/menu.h"
#include "constants/event_objects.h"
#include "constants/metatile_labels.h"

static EWRAM_DATA u8 sElevatorCurrentFloorWindowId = 0;
static EWRAM_DATA u16 sElevatorScroll = 0;
static EWRAM_DATA u16 sElevatorCursorPos = 0;
static EWRAM_DATA struct ListMenuItem * sListMenuItems = NULL;
static EWRAM_DATA u16 sListMenuLastScrollPosition = 0;
static EWRAM_DATA u8 sPCBoxToSendMon = 0;
static EWRAM_DATA u8 sBrailleTextCursorSpriteID = 0;

struct ListMenuTemplate sFieldSpecialsListMenuTemplate;
u16 sFieldSpecialsListMenuScrollBuffer;

static void Task_AnimatePcTurnOn(u8 taskId);
static void PcTurnOnUpdateMetatileId(bool16 flag);
static void Task_ShakeScreen(u8 taskId);
static void Task_EndScreenShake(u8 taskId);
static u16 SampleResortGorgeousMon(void);
static u16 SampleResortGorgeousReward(void);
static void Task_ElevatorShake(u8 taskId);
static void AnimateElevatorWindowView(u16 nfloors, bool8 direction);
static void Task_AnimateElevatorWindowView(u8 taskId);
static void Task_CreateScriptListMenu(u8 taskId);
static void CreateScriptListMenu(void);
static void ScriptListMenuMoveCursorFunction(s32 nothing, bool8 is, struct ListMenu * used);
static void Task_ListMenuHandleInput(u8 taskId);
static void Task_DestroyListMenu(u8 taskId);
static void Task_SuspendListMenu(u8 taskId);
static void Task_RedrawScrollArrowsAndWaitInput(u8 taskId);
static void Task_CreateMenuRemoveScrollIndicatorArrowPair(u8 taskId);
static void Task_ListMenuRemoveScrollIndicatorArrowPair(u8 taskId);
static u16 GetStarterSpeciesById(u16 starterIdx);
static void ChangeBoxPokemonNickname_CB(void);
static void ChangePokemonNickname_CB(void);
static void Task_RunPokemonLeagueLightingEffect(u8 taskId);
static void Task_CancelPokemonLeagueLightingEffect(u8 taskId);
static void Task_DoDeoxysTriangleInteraction(u8 taskId);
static void MoveDeoxysObject(u8 num);
static void Task_WaitDeoxysFieldEffect(u8 taskId);
static void Task_WingFlapSound(u8 taskId);

static u8 *const sStringVarPtrs[] = {
    gStringVar1,
    gStringVar2,
    gStringVar3
};

void ShowDiploma(void)
{
    QuestLog_CutRecording();
    SetMainCallback2(CB2_ShowDiploma);
    LockPlayerFieldControls();
}

void ForcePlayerOntoBike(void)
{
    if (gPlayerAvatar.flags & PLAYER_AVATAR_FLAG_ON_FOOT)
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_MACH_BIKE);
    Overworld_SetSavedMusic(MUS_CYCLING);
    Overworld_ChangeMusicTo(MUS_CYCLING);
}

void ResetCyclingRoadChallengeData(void)
{

}

u8 GetPlayerAvatarBike(void)
{
    if (TestPlayerAvatarFlags(4))
        return 1;
    else if (TestPlayerAvatarFlags(2))
        return 2;
    else
        return 0;
}

void ShowFieldMessageStringVar4(void)
{
    ShowFieldMessage(gStringVar4);
}

void GetPlayerXY(void)
{
    gSpecialVar_0x8004 = gSaveBlock1Ptr->pos.x;
    gSpecialVar_0x8005 = gSaveBlock1Ptr->pos.y;
}

u8 GetPlayerTrainerIdOnesDigit(void)
{
    u16 playerId = (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];
    return playerId % 10;
}

void BufferBigGuyOrBigGirlString(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        StringCopy(gStringVar1, gText_BigGuy);
    else
        StringCopy(gStringVar1, gText_BigGirl);
}

void BufferSonOrDaughterString(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        StringCopy(gStringVar1, gText_Daughter);
    else
        StringCopy(gStringVar1, gText_Son);
}

u8 GetBattleOutcome(void)
{
    return gBattleOutcome;
}

void SetHiddenItemFlag(void)
{
    FlagSet(gSpecialVar_0x8004);
}

u8 GetLeadMonFriendship(void)
{
    struct Pokemon * pokemon = &gPlayerParty[GetLeadMonIndex()];
    if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) == 255)
        return 6;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 200)
        return 5;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 150)
        return 4;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 100)
        return 3;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) >= 50)
        return 2;
    else if (GetMonData(pokemon, MON_DATA_FRIENDSHIP) > 0)
        return 1;
    else
        return 0;
}

void ShowTownMap(void)
{
    QuestLog_CutRecording();
    InitRegionMapWithExitCB(REGIONMAP_TYPE_WALL, CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

bool8 PlayerHasGrassPokemonInParty(void)
{
    u8 i;
    struct Pokemon * pokemon;
    u16 species;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        pokemon = &gPlayerParty[i];
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES)
         && !GetMonData(pokemon, MON_DATA_IS_EGG)
        )
        {
            species = GetMonData(pokemon, MON_DATA_SPECIES);
            if (gBaseStats[species].type1 == TYPE_GRASS || gBaseStats[species].type2 == TYPE_GRASS)
                return TRUE;
        }
    }
    return FALSE;
}

#define tState data[0]
#define tTimer data[1]

void AnimatePcTurnOn(void)
{
    u8 taskId;

    if (FuncIsActiveTask(Task_AnimatePcTurnOn) != TRUE)
    {
        taskId = CreateTask(Task_AnimatePcTurnOn, 8);
        gTasks[taskId].tState = 0;
        gTasks[taskId].tTimer = 0;
    }
}

// PC flickers on and off while turning on
static void Task_AnimatePcTurnOn(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (tTimer == 6)
    {
        PcTurnOnUpdateMetatileId(tState & 1);
        DrawWholeMapView();
        tTimer = 0;
        tState++;
        if (tState == 5)
            DestroyTask(taskId);
    }
    tTimer++;
}

#undef tState
#undef tTimer

static void PcTurnOnUpdateMetatileId(bool16 flickerOff)
{
    u16 metatileId = 0;
    s8 deltaX = 0;
    s8 deltaY = 0;
    u8 direction = GetPlayerFacingDirection();

    switch (direction)
    {
    case DIR_NORTH:
        deltaX = 0;
        deltaY = -1;
        break;
    case DIR_WEST:
        deltaX = -1;
        deltaY = -1;
        break;
    case DIR_EAST:
        deltaX = 1;
        deltaY = -1;
        break;
    }
    if (flickerOff)
    {
        if (gSpecialVar_0x8004 == 0)
            metatileId = METATILE_Building_PCOff;
        else if (gSpecialVar_0x8004 == 1)
            metatileId = METATILE_GenericBuilding1_PlayersPCOff;
        else if (gSpecialVar_0x8004 == 2)
            metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    }
    else
    {
        if (gSpecialVar_0x8004 == 0)
            metatileId = METATILE_Building_PCOn;
        else if (gSpecialVar_0x8004 == 1)
            metatileId = METATILE_GenericBuilding1_PlayersPCOn;
        else if (gSpecialVar_0x8004 == 2)
            metatileId = METATILE_GenericBuilding1_PlayersPCOn;
    }
    MapGridSetMetatileIdAt(gSaveBlock1Ptr->pos.x + deltaX + 7, gSaveBlock1Ptr->pos.y + deltaY + 7, metatileId | METATILE_COLLISION_MASK);
}

void AnimatePcTurnOff()
{
    u16 metatileId = 0;
    s8 deltaX = 0;
    s8 deltaY = 0;
    u8 direction = GetPlayerFacingDirection();

    switch (direction)
    {
    case DIR_NORTH:
        deltaX = 0;
        deltaY = -1;
        break;
    case DIR_WEST:
        deltaX = -1;
        deltaY = -1;
        break;
    case DIR_EAST:
        deltaX = 1;
        deltaY = -1;
        break;
    }
    if (gSpecialVar_0x8004 == 0)
        metatileId = METATILE_Building_PCOff;
    else if (gSpecialVar_0x8004 == 1)
        metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    else if (gSpecialVar_0x8004 == 2)
        metatileId = METATILE_GenericBuilding1_PlayersPCOff;
    MapGridSetMetatileIdAt(gSaveBlock1Ptr->pos.x + deltaX + 7, gSaveBlock1Ptr->pos.y + deltaY + 7, metatileId | METATILE_COLLISION_MASK);
    DrawWholeMapView();
}

void SpawnCameraObject(void)
{
    u8 objectEventId = SpawnSpecialObjectEventParameterized(OBJ_EVENT_GFX_YOUNGSTER, 8, OBJ_EVENT_ID_CAMERA, gSaveBlock1Ptr->pos.x + 7, gSaveBlock1Ptr->pos.y + 7, 3);
    gObjectEvents[objectEventId].invisible = TRUE;
    CameraObjectSetFollowedObjectId(gObjectEvents[objectEventId].spriteId);
}

void RemoveCameraObject(void)
{
    CameraObjectSetFollowedObjectId(GetPlayerAvatarObjectId());
    RemoveObjectEventByLocalIdAndMap(127, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
}

void BufferEReaderTrainerName(void)
{
    CopyEReaderTrainerName5(gStringVar1);
}

static const u8 sUnused_83F5B04[] = {
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    12,
    2,
    4,
    5,
    1,
    8,
    7,
    11,
    3,
    10,
    9,
    6
};

static const u8 sSlotMachineIndices[] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    2,
    2,
    2,
    3,
    3,
    3,
    4,
    4,
    5
};

u8 GetRandomSlotMachineId(void)
{
    u16 rval = Random() % NELEMS(sSlotMachineIndices);
    return sSlotMachineIndices[rval];
}

bool8 LeadMonHasEffortRibbon(void)
{
    u8 leadMonIdx = GetLeadMonIndex();
    return GetMonData(&gPlayerParty[leadMonIdx], MON_DATA_EFFORT_RIBBON, NULL);
}

void GiveLeadMonEffortRibbon(void)
{
    u8 leadMonIdx;
    bool8 param;
    IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
    FlagSet(FLAG_SYS_RIBBON_GET);
    param = TRUE;
    leadMonIdx = GetLeadMonIndex();
    SetMonData(&gPlayerParty[leadMonIdx], MON_DATA_EFFORT_RIBBON, &param);
}

bool8 AreLeadMonEVsMaxedOut(void)
{
    u8 leadMonIndex = GetLeadMonIndex();
    if (GetMonEVCount(&gPlayerParty[leadMonIndex]) >= MAX_TOTAL_EVS)
        return TRUE;
    else
        return FALSE;
}

bool8 IsStarterFirstStageInParty(void)
{
    u16 species = GetStarterSpeciesById(VarGet(VAR_STARTER_MON));
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < partyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL) == species)
            return TRUE;
    }
    return FALSE;
}

bool8 IsThereRoomInAnyBoxForMorePokemon(void)
{
    u16 i;
    u16 j;
    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            if (GetBoxMonDataAt(i, j, MON_DATA_SPECIES) == SPECIES_NONE)
                return TRUE;
        }
    }
    return FALSE;
}

bool8 IsPokerusInParty(void)
{
    if (!CheckPartyPokerus(gPlayerParty, 0x3F))
        return FALSE;
    else
        return TRUE;
}

#define tXtrans   data[0]
#define tTimer    data[1]
#define tNremain  data[2]
#define tDuration data[3]
#define tYtrans   data[4]

void ShakeScreen(void)
{
    /*
     * 0x8004 = x translation
     * 0x8005 = y translation
     * 0x8006 = num interations
     * 0x8007 = duration of an iteration
     */
    u8 taskId = CreateTask(Task_ShakeScreen, 9);
    gTasks[taskId].tXtrans = gSpecialVar_0x8005;
    gTasks[taskId].tTimer = 0;
    gTasks[taskId].tNremain = gSpecialVar_0x8006;
    gTasks[taskId].tDuration = gSpecialVar_0x8007;
    gTasks[taskId].tYtrans = gSpecialVar_0x8004;
    SetCameraPanningCallback(NULL);
    PlaySE(SE_M_STRENGTH);
}

static void Task_ShakeScreen(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    tTimer++;
    if (tTimer % tDuration == 0)
    {
        tTimer = 0;
        tNremain--;
        tXtrans = -tXtrans;
        tYtrans = -tYtrans;
        SetCameraPanning(tXtrans, tYtrans);
        if (tNremain == 0)
        {
            Task_EndScreenShake(taskId);
            InstallCameraPanAheadCallback();
        }
    }
}

static void Task_EndScreenShake(u8 taskId)
{
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

#undef tYtrans
#undef tDuration
#undef tNremain
#undef tTimer
#undef tXtrans

u8 GetLeadMonIndex(void)
{
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    struct Pokemon * pokemon;
    for (i = 0; i < partyCount; i++)
    {
        pokemon = &gPlayerParty[i];
        if (GetMonData(pokemon, MON_DATA_SPECIES2, NULL) != SPECIES_EGG && GetMonData(pokemon, MON_DATA_SPECIES2, NULL) != SPECIES_NONE)
            return i;
    }
    return 0;
}

u16 GetPartyMonSpecies(void)
{
    return GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES2, NULL);
}

bool8 IsMonOTNameNotPlayers(void)
{
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_OT_NAME, gStringVar1);
    
    if (!StringCompare(gSaveBlock2Ptr->playerName, gStringVar1))
        return FALSE;
    else
        return TRUE;
}

// Used to nop all the unused specials from RS
void NullFieldSpecial(void)
{

}

void DoPicboxCancel(void)
{
    u8 t = EOS;
    AddTextPrinterParameterized(0, 2, &t, 0, 1, 0, NULL);
    PicboxCancel();
}

void SetVermilionTrashCans(void)
{
    u16 idx = (Random() % 15) + 1;
    gSpecialVar_0x8004 = idx;
    gSpecialVar_0x8005 = idx;
    switch (gSpecialVar_0x8004)
    {
    case 1:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 += 5;
        break;
    case 2:
    case 3:
    case 4:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 += 1;
        else if (idx == 1)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 5:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 6:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 += 5;
        break;
    case 7:
    case 8:
    case 9:
        idx = Random() % 4;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else if (idx == 2)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 10:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 11:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else
            gSpecialVar_0x8005 += 1;
        break;
    case 12:
    case 13:
    case 14:
        idx = Random() % 3;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else if (idx == 1)
            gSpecialVar_0x8005 += 1;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    case 15:
        idx = Random() % 2;
        if (idx == 0)
            gSpecialVar_0x8005 -= 5;
        else
            gSpecialVar_0x8005 -= 1;
        break;
    }
    if (gSpecialVar_0x8005 > 15)
    {
        if (gSpecialVar_0x8004 % 5 == 1)
            gSpecialVar_0x8005 = gSpecialVar_0x8004 + 1;
        else if (gSpecialVar_0x8004 % 5 == 0)
            gSpecialVar_0x8005 = gSpecialVar_0x8004 - 1;
        else
            gSpecialVar_0x8005 = gSpecialVar_0x8004 + 1;
    }
}

static const u16 sResortGorgeousDeluxeRewards[] = {
    ITEM_BIG_PEARL,
    ITEM_PEARL,
    ITEM_STARDUST,
    ITEM_STAR_PIECE,
    ITEM_NUGGET,
    ITEM_RARE_CANDY
};

void IncrementResortGorgeousStepCounter(void)
{
    u16 var4035 = VarGet(VAR_RESORT_GOREGEOUS_STEP_COUNTER);
    if (VarGet(VAR_RESORT_GORGEOUS_REQUESTED_MON) != SPECIES_NONE)
    {
        var4035++;
        if (var4035 >= 250)
        {
            VarSet(VAR_RESORT_GORGEOUS_REQUESTED_MON, 0xFFFF);
            VarSet(VAR_RESORT_GOREGEOUS_STEP_COUNTER, 0);
        }
        else
        {
            VarSet(VAR_RESORT_GOREGEOUS_STEP_COUNTER, var4035);
        }
    }
}

void SampleResortGorgeousMonAndReward(void)
{
    u16 requestedSpecies = VarGet(VAR_RESORT_GORGEOUS_REQUESTED_MON);
    if (requestedSpecies == SPECIES_NONE || requestedSpecies == 0xFFFF)
    {
        VarSet(VAR_RESORT_GORGEOUS_REQUESTED_MON, SampleResortGorgeousMon());
        VarSet(VAR_RESORT_GORGEOUS_REWARD, SampleResortGorgeousReward());
        VarSet(VAR_RESORT_GOREGEOUS_STEP_COUNTER, 0);
    }
    StringCopy(gStringVar1, gSpeciesNames[VarGet(VAR_RESORT_GORGEOUS_REQUESTED_MON)]);
}

static u16 SampleResortGorgeousMon(void)
{
    u16 i;
    u16 species;
    for (i = 0; i < 100; i++)
    {
        species = (Random() % (NUM_SPECIES - 1)) + 1;
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) == TRUE)
            return species;
    }
    while (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) != TRUE)
    {
        if (species == SPECIES_BULBASAUR)
            species = NUM_SPECIES - 1;
        else
            species--;
    }
    return species;
}

static u16 SampleResortGorgeousReward(void)
{
    if ((Random() % 100) >= 30)
        return ITEM_LUXURY_BALL;
    else
        return sResortGorgeousDeluxeRewards[Random() % NELEMS(sResortGorgeousDeluxeRewards)];
}

bool8 CheckAddCoins(void)
{
    if (gSpecialVar_Result + gSpecialVar_0x8006 > 9999)
        return FALSE;
    else
        return TRUE;
}

static const struct WindowTemplate sElevatorCurrentFloorWindowTemplate = {
    .bg = 0,
    .tilemapLeft = 22,
    .tilemapTop = 1,
    .width = 7,
    .height = 4,
    .paletteNum = 0xF,
    .baseBlock = 0x008
};

static const u8 *const sFloorNamePointers[] = {
    gText_B4F,
    gText_B3F,
    gText_B2F,
    gText_B1F,
    gText_1F,
    gText_2F,
    gText_3F,
    gText_4F,
    gText_5F,
    gText_6F,
    gText_7F,
    gText_8F,
    gText_9F,
    gText_10F,
    gText_11F,
    gText_Rooftop
};

static const u8 sUnused_83F5B84[] = {
    26,
    26,
    26,
    26,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    30,
    26,
    26,
    18
};

static const u16 sElevatorWindowMetatilesGoingUp[][3] = {
    {
        METATILE_SilphCo_ElevatorWindow_Top0, 
        METATILE_SilphCo_ElevatorWindow_Top1, 
        METATILE_SilphCo_ElevatorWindow_Top2
    },
    {
        METATILE_SilphCo_ElevatorWindow_Mid0, 
        METATILE_SilphCo_ElevatorWindow_Mid1, 
        METATILE_SilphCo_ElevatorWindow_Mid2
    },
    {
        METATILE_SilphCo_ElevatorWindow_Bottom0, 
        METATILE_SilphCo_ElevatorWindow_Bottom1, 
        METATILE_SilphCo_ElevatorWindow_Bottom2
    }
};

static const u16 sElevatorWindowMetatilesGoingDown[][3] = {
    {
        METATILE_SilphCo_ElevatorWindow_Top0, 
        METATILE_SilphCo_ElevatorWindow_Top2, 
        METATILE_SilphCo_ElevatorWindow_Top1
    },
    {
        METATILE_SilphCo_ElevatorWindow_Mid0, 
        METATILE_SilphCo_ElevatorWindow_Mid2, 
        METATILE_SilphCo_ElevatorWindow_Mid1
    },
    {
        METATILE_SilphCo_ElevatorWindow_Bottom0, 
        METATILE_SilphCo_ElevatorWindow_Bottom2, 
        METATILE_SilphCo_ElevatorWindow_Bottom1
    }
};

static const u8 sElevatorAnimationDuration[] = {
    8,
    16,
    24,
    32,
    38,
    46,
    53,
    56,
    57
};

static const u8 sElevatorWindowAnimDuration[] = {
    3,
    6,
    9,
    12,
    15,
    18,
    21,
    24,
    27
};

void GetElevatorFloor(void)
{
    u16 floor = 4;
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(ROCKET_HIDEOUT_B1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(SILPH_CO_1F):
            floor = 4;
            break;
        case MAP_NUM(SILPH_CO_2F):
            floor = 5;
            break;
        case MAP_NUM(SILPH_CO_3F):
            floor = 6;
            break;
        case MAP_NUM(SILPH_CO_4F):
            floor = 7;
            break;
        case MAP_NUM(SILPH_CO_5F):
            floor = 8;
            break;
        case MAP_NUM(SILPH_CO_6F):
            floor = 9;
            break;
        case MAP_NUM(SILPH_CO_7F):
            floor = 10;
            break;
        case MAP_NUM(SILPH_CO_8F):
            floor = 11;
            break;
        case MAP_NUM(SILPH_CO_9F):
            floor = 12;
            break;
        case MAP_NUM(SILPH_CO_10F):
            floor = 13;
            break;
        case MAP_NUM(SILPH_CO_11F):
            floor = 14;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B1F):
            floor = 3;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B2F):
            floor = 2;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B4F):
            floor = 0;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(CELADON_CITY_DEPARTMENT_STORE_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_1F):
            floor = 4;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_2F):
            floor = 5;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_3F):
            floor = 6;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_4F):
            floor = 7;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_5F):
            floor = 8;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(TRAINER_TOWER_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(TRAINER_TOWER_1F):
        case MAP_NUM(TRAINER_TOWER_2F):
        case MAP_NUM(TRAINER_TOWER_3F):
        case MAP_NUM(TRAINER_TOWER_4F):
        case MAP_NUM(TRAINER_TOWER_5F):
        case MAP_NUM(TRAINER_TOWER_6F):
        case MAP_NUM(TRAINER_TOWER_7F):
        case MAP_NUM(TRAINER_TOWER_8F):
        case MAP_NUM(TRAINER_TOWER_ROOF):
            floor = 15;
            break;
        case MAP_NUM(TRAINER_TOWER_LOBBY):
            floor = 3;
            break;
        }
    }
    VarSet(VAR_ELEVATOR_FLOOR, floor);
}

u16 InitElevatorFloorSelectMenuPos(void)
{
    sElevatorScroll = 0;
    sElevatorCursorPos = 0;

    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(ROCKET_HIDEOUT_B1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(SILPH_CO_11F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(SILPH_CO_10F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(SILPH_CO_9F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        case MAP_NUM(SILPH_CO_8F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 3;
            break;
        case MAP_NUM(SILPH_CO_7F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_6F):
            sElevatorScroll = 1;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_5F):
            sElevatorScroll = 2;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_4F):
            sElevatorScroll = 3;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_3F):
            sElevatorScroll = 4;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_2F):
            sElevatorScroll = 5;
            sElevatorCursorPos = 4;
            break;
        case MAP_NUM(SILPH_CO_1F):
            sElevatorScroll = 5;
            sElevatorCursorPos = 5;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B1F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B2F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(ROCKET_HIDEOUT_B4F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(CELADON_CITY_DEPARTMENT_STORE_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_5F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_4F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_3F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 2;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_2F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 3;
            break;
        case MAP_NUM(CELADON_CITY_DEPARTMENT_STORE_1F):
            sElevatorScroll = 0;
            sElevatorCursorPos = 4;
            break;
        }
    }
    if (gSaveBlock1Ptr->dynamicWarp.mapGroup == MAP_GROUP(TRAINER_TOWER_1F))
    {
        switch (gSaveBlock1Ptr->dynamicWarp.mapNum)
        {
        case MAP_NUM(TRAINER_TOWER_1F):
        case MAP_NUM(TRAINER_TOWER_2F):
        case MAP_NUM(TRAINER_TOWER_3F):
        case MAP_NUM(TRAINER_TOWER_4F):
        case MAP_NUM(TRAINER_TOWER_5F):
        case MAP_NUM(TRAINER_TOWER_6F):
        case MAP_NUM(TRAINER_TOWER_7F):
        case MAP_NUM(TRAINER_TOWER_8F):
        case MAP_NUM(TRAINER_TOWER_ROOF):
            sElevatorScroll = 0;
            sElevatorCursorPos = 0;
            break;
        case MAP_NUM(TRAINER_TOWER_LOBBY):
            sElevatorScroll = 0;
            sElevatorCursorPos = 1;
            break;
        }
    }
    return sElevatorCursorPos;
}

void AnimateElevator(void)
{
    u16 nfloors;
    s16 *data = gTasks[CreateTask(Task_ElevatorShake, 9)].data;
    data[1] = 0;
    data[2] = 0;
    data[4] = 1;
    if (gSpecialVar_0x8005 > gSpecialVar_0x8006)
    {
        nfloors = gSpecialVar_0x8005 - gSpecialVar_0x8006;
        data[6] = 1;
    }
    else
    {
        nfloors = gSpecialVar_0x8006 - gSpecialVar_0x8005;
        data[6] = 0;
    }
    if (nfloors > 8)
        nfloors = 8;
    data[5] = sElevatorAnimationDuration[nfloors];
    SetCameraPanningCallback(NULL);
    AnimateElevatorWindowView(nfloors, data[6]);
    PlaySE(SE_ELEVATOR);
}

static void Task_ElevatorShake(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    data[1]++;
    if ((data[1] % 3) == 0)
    {
        data[1] = 0;
        data[2]++;
        data[4] = -data[4];
        SetCameraPanning(0, data[4]);
        if (data[2] == data[5])
        {
            PlaySE(SE_DING_DONG);
            DestroyTask(taskId);
            EnableBothScriptContexts();
            InstallCameraPanAheadCallback();
        }
    }
}

void DrawElevatorCurrentFloorWindow(void)
{
    const u8 *floorname;
    u32 strwidth;
    if (QuestLog_SchedulePlaybackCB(QLPlaybackCB_DestroyScriptMenuMonPicSprites) != TRUE)
    {
        sElevatorCurrentFloorWindowId = AddWindow(&sElevatorCurrentFloorWindowTemplate);
        TextWindow_SetStdFrame0_WithPal(sElevatorCurrentFloorWindowId, 0x21D, 0xD0);
        DrawStdFrameWithCustomTileAndPalette(sElevatorCurrentFloorWindowId, FALSE, 0x21D, 0xD);
        AddTextPrinterParameterized(sElevatorCurrentFloorWindowId, 2, gText_NowOn, 0, 2, 0xFF, NULL);
        floorname = sFloorNamePointers[gSpecialVar_0x8005];
        strwidth = GetStringWidth(2, floorname, 0);
        AddTextPrinterParameterized(sElevatorCurrentFloorWindowId, 2, floorname, 56 - strwidth, 16, 0xFF, NULL);
        PutWindowTilemap(sElevatorCurrentFloorWindowId);
        CopyWindowToVram(sElevatorCurrentFloorWindowId, COPYWIN_BOTH);
    }
}

void CloseElevatorCurrentFloorWindow(void)
{
    ClearStdWindowAndFrameToTransparent(sElevatorCurrentFloorWindowId, TRUE);
    RemoveWindow(sElevatorCurrentFloorWindowId);
}

static void AnimateElevatorWindowView(u16 nfloors, u8 direction)
{
    u8 taskId;
    if (FuncIsActiveTask(Task_AnimateElevatorWindowView) != TRUE)
    {
        taskId = CreateTask(Task_AnimateElevatorWindowView, 8);
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].data[1] = 0;
        gTasks[taskId].data[2] = direction;
        gTasks[taskId].data[3] = sElevatorWindowAnimDuration[nfloors];
    }
}

static void Task_AnimateElevatorWindowView(u8 taskId)
{
    u8 i;
    u8 j;
    s16 *data = gTasks[taskId].data;
    if (data[1] == 6)
    {
        data[0]++;
        if (data[2] == 0)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    MapGridSetMetatileIdAt(j + 8, i + 7, sElevatorWindowMetatilesGoingUp[i][data[0] % 3] | METATILE_COLLISION_MASK);
                }
            }
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    MapGridSetMetatileIdAt(j + 8, i + 7, sElevatorWindowMetatilesGoingDown[i][data[0] % 3] | METATILE_COLLISION_MASK);
                }
            }
        }
        DrawWholeMapView();
        data[1] = 0;
        if (data[0] == data[3])
            DestroyTask(taskId);
    }
    data[1]++;
}

void ListMenu(void)
{
    u8 taskId;
    struct Task * task;
    if (QuestLog_SchedulePlaybackCB(QLPlaybackCB_DestroyScriptMenuMonPicSprites) != TRUE)
    {
        taskId = CreateTask(Task_CreateScriptListMenu, 8);
        task = &gTasks[taskId];
        switch (gSpecialVar_0x8004)
        {
        case LISTMENU_BADGES:
            task->data[0] = 4;
            task->data[1] = 9;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 12;
            task->data[5] = 7;
            task->data[6] = 1;
            task->data[15] = taskId;
            break;
        case LISTMENU_SILPHCO_FLOORS:
            task->data[0] = 7;
            task->data[1] = 12;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 8;
            task->data[5] = 12;
            task->data[6] = 0;
            task->data[15] = taskId;
            task->data[7] = sElevatorScroll;
            task->data[8] = sElevatorCursorPos;
            break;
        case LISTMENU_ROCKET_HIDEOUT_FLOORS: // Multichoice used instead
            task->data[0] = 4;
            task->data[1] = 4;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 8;
            task->data[5] = 8;
            task->data[6] = 0;
            task->data[15] = taskId;
            break;
        case LISTMENU_DEPT_STORE_FLOORS: // Multichoice used instead
            task->data[0] = 4;
            task->data[1] = 6;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 8;
            task->data[5] = 8;
            task->data[6] = 0;
            task->data[15] = taskId;
            break;
        case LISTMENU_WIRELESS_LECTURE_HEADERS: // Multichoice used instead
            task->data[0] = 4;
            task->data[1] = 4;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 17;
            task->data[5] = 8;
            task->data[6] = 1;
            task->data[15] = taskId;
            break;
        case LISTMENU_BERRY_POWDER:
            task->data[0] = 7;
            task->data[1] = 12;
            task->data[2] = 16;
            task->data[3] = 1;
            task->data[4] = 17;
            task->data[5] = 12;
            task->data[6] = 0;
            task->data[15] = taskId;
            break;
        case LISTMENU_TRAINER_TOWER_FLOORS: // Mulitchoice used instead
            task->data[0] = 3;
            task->data[1] = 3;
            task->data[2] = 1;
            task->data[3] = 1;
            task->data[4] = 8;
            task->data[5] = 6;
            task->data[6] = 0;
            task->data[15] = taskId;
            break;
        case 99:
            break;
        default:
            gSpecialVar_Result = 0x7F;
            DestroyTask(taskId);
            break;
        }
    }
}

static const u8 *const sListMenuLabels[][12] = {
    [LISTMENU_BADGES] = 
    {
        gText_BoulderBadge,
        gText_CascadeBadge,
        gText_ThunderBadge,
        gText_RainbowBadge,
        gText_SoulBadge,
        gText_MarshBadge,
        gText_VolcanoBadge,
        gText_EarthBadge,
        gOtherText_Exit,
    }, 
    [LISTMENU_SILPHCO_FLOORS] = 
    {
        gText_11F,
        gText_10F,
        gText_9F,
        gText_8F,
        gText_7F,
        gText_6F,
        gText_5F,
        gText_4F,
        gText_3F,
        gText_2F,
        gText_1F,
        gOtherText_Exit,
    }, 
    [LISTMENU_ROCKET_HIDEOUT_FLOORS] = // Unncessary, MULTICHOICE_ROCKET_HIDEOUT_ELEVATOR is used instead
    {
        gText_B1F,
        gText_B2F,
        gText_B4F,
        gOtherText_Exit,
    }, 
    [LISTMENU_DEPT_STORE_FLOORS] = // Unncessary, MULTICHOICE_DEPT_STORE_ELEVATOR is used instead
    {
        gText_5F,
        gText_4F,
        gText_3F,
        gText_2F,
        gText_1F,
        gOtherText_Exit,
    }, 
    [LISTMENU_WIRELESS_LECTURE_HEADERS] = // Unnecessary, MULTICHOICE_LINKED_DIRECT_UNION is used instead
    {
        gText_LinkedGamePlay,
        gText_DirectCorner,
        gText_UnionRoom,
        gOtherText_Quit,
    }, 
    [LISTMENU_BERRY_POWDER] = 
    {
        gText_Energypowder_50,
        gText_EnergyRoot_80,
        gText_HealPowder_50,
        gText_RevivalHerb_300,
        gText_Protein_1000,
        gText_Iron_1000,
        gText_Carbos_1000,
        gText_Calcium_1000,
        gText_Zinc_1000,
        gText_HpUp_1000,
        gText_PpUp_3000,
        gOtherText_Exit,
    }, 
    [LISTMENU_TRAINER_TOWER_FLOORS] = // Unnecessary, MULTICHOICE_ROOFTOP_B1F is used instead
    {
        gText_Rooftop,
        gText_B1F,
        gOtherText_Exit,
    }
};

static void Task_CreateScriptListMenu(u8 taskId)
{
    struct WindowTemplate template;
    u8 i;
    s32 width;
    s32 mwidth;
    struct Task * task = &gTasks[taskId];
    u8 windowId;
    LockPlayerFieldControls();
    if (gSpecialVar_0x8004 == LISTMENU_SILPHCO_FLOORS)
        sListMenuLastScrollPosition = sElevatorScroll;
    else
        sListMenuLastScrollPosition = 0;
    sListMenuItems = AllocZeroed(task->data[1] * sizeof(struct ListMenuItem));
    CreateScriptListMenu();
    mwidth = 0;
    for (i = 0; i < task->data[1]; i++)
    {
        sListMenuItems[i].label = sListMenuLabels[gSpecialVar_0x8004][i];
        sListMenuItems[i].index = i;
        width = GetStringWidth(2, sListMenuItems[i].label, 0);
        if (width > mwidth)
            mwidth = width;
    }
    task->data[4] = (mwidth + 9) / 8 + 1;
    if (task->data[2] + task->data[4] > 29)
        task->data[2] = 29 - task->data[4];
    template = SetWindowTemplateFields(0, task->data[2], task->data[3], task->data[4], task->data[5], 15, 0x038);
    task->data[13] = windowId = AddWindow(&template);
    SetStdWindowBorderStyle(task->data[13], 0);
    sFieldSpecialsListMenuTemplate.totalItems = task->data[1];
    sFieldSpecialsListMenuTemplate.maxShowed = task->data[0];
    sFieldSpecialsListMenuTemplate.windowId = task->data[13];
    Task_CreateMenuRemoveScrollIndicatorArrowPair(taskId);
    task->data[14] = ListMenuInit(&sFieldSpecialsListMenuTemplate, task->data[7], task->data[8]);
    PutWindowTilemap(task->data[13]);
    CopyWindowToVram(task->data[13], COPYWIN_BOTH);
    gTasks[taskId].func = Task_ListMenuHandleInput;
}

static void CreateScriptListMenu(void)
{
    sFieldSpecialsListMenuTemplate.items = sListMenuItems;
    sFieldSpecialsListMenuTemplate.moveCursorFunc = ScriptListMenuMoveCursorFunction;
    sFieldSpecialsListMenuTemplate.itemPrintFunc = NULL;
    sFieldSpecialsListMenuTemplate.totalItems = 1;
    sFieldSpecialsListMenuTemplate.maxShowed = 1;
    sFieldSpecialsListMenuTemplate.windowId = 0;
    sFieldSpecialsListMenuTemplate.header_X = 0;
    sFieldSpecialsListMenuTemplate.item_X = 8;
    sFieldSpecialsListMenuTemplate.cursor_X = 0;
    sFieldSpecialsListMenuTemplate.upText_Y = 0;
    sFieldSpecialsListMenuTemplate.cursorPal = 2;
    sFieldSpecialsListMenuTemplate.fillValue = 1;
    sFieldSpecialsListMenuTemplate.cursorShadowPal = 3;
    sFieldSpecialsListMenuTemplate.lettersSpacing = 1;
    sFieldSpecialsListMenuTemplate.itemVerticalPadding = 0;
    sFieldSpecialsListMenuTemplate.scrollMultiple = 0;
    sFieldSpecialsListMenuTemplate.fontId = 2;
    sFieldSpecialsListMenuTemplate.cursorKind = 0;
}

static void ScriptListMenuMoveCursorFunction(s32 nothing, bool8 is, struct ListMenu * used)
{
    u8 taskId;
    struct Task * task;
    PlaySE(SE_SELECT);
    taskId = FindTaskIdByFunc(Task_ListMenuHandleInput);
    if (taskId != 0xFF)
    {
        task = &gTasks[taskId];
        ListMenuGetScrollAndRow(task->data[14], &sFieldSpecialsListMenuScrollBuffer, NULL);
        sListMenuLastScrollPosition = sFieldSpecialsListMenuScrollBuffer;
    }
}

static void Task_ListMenuHandleInput(u8 taskId)
{
    s32 input;
    struct Task * task;

    task = &gTasks[taskId];
    task++;task--;
    input = ListMenu_ProcessInput(task->data[14]);
    switch (input)
    {
    case -1:
        break;
    case -2:
        gSpecialVar_Result = 0x7F;
        PlaySE(SE_SELECT);
        Task_DestroyListMenu(taskId);
        break;
    default:
        gSpecialVar_Result = input;
        PlaySE(SE_SELECT);
        if (task->data[6] == 0 || input == task->data[1] - 1)
        {
            Task_DestroyListMenu(taskId);
        }
        else
        {
            Task_ListMenuRemoveScrollIndicatorArrowPair(taskId);
            task->func = Task_SuspendListMenu;
            EnableBothScriptContexts();
        }
        break;
    }
}

static void Task_DestroyListMenu(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    Task_ListMenuRemoveScrollIndicatorArrowPair(taskId);
    DestroyListMenuTask(task->data[14], NULL, NULL);
    Free(sListMenuItems);
    ClearStdWindowAndFrameToTransparent(task->data[13], TRUE);
    FillWindowPixelBuffer(task->data[13], PIXEL_FILL(0));
    ClearWindowTilemap(task->data[13]);
    CopyWindowToVram(task->data[13], COPYWIN_GFX);
    RemoveWindow(task->data[13]);
    DestroyTask(taskId);
    EnableBothScriptContexts();
}

static void Task_SuspendListMenu(u8 taskId)
{
    switch (gTasks[taskId].data[6])
    {
    case 1:
        break;
    case 2:
        gTasks[taskId].data[6] = 1;
        gTasks[taskId].func = Task_RedrawScrollArrowsAndWaitInput;
        break;
    }
}

void ReturnToListMenu(void)
{
    u8 taskId = FindTaskIdByFunc(Task_SuspendListMenu);
    if (taskId == 0xFF)
        EnableBothScriptContexts();
    else
        gTasks[taskId].data[6]++;
}

static void Task_RedrawScrollArrowsAndWaitInput(u8 taskId)
{
    LockPlayerFieldControls();
    Task_CreateMenuRemoveScrollIndicatorArrowPair(taskId);
    gTasks[taskId].func = Task_ListMenuHandleInput;
}

static void Task_CreateMenuRemoveScrollIndicatorArrowPair(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    struct ScrollArrowsTemplate template = {
        .firstArrowType = 2,
        .secondArrowType = 3,
        .tileTag = 2000,
        .palTag = 100
    };
    if (task->data[0] != task->data[1])
    {
        template.firstX = 4 * task->data[4] + 8 * task->data[2];
        template.firstY = 8;
        template.secondX = 4 * task->data[4] + 8 * task->data[2];
        template.secondY = 8 * task->data[5] + 10;
        template.fullyUpThreshold = 0;
        template.fullyDownThreshold = task->data[1] - task->data[0];
        task->data[12] = AddScrollIndicatorArrowPair(&template, &sListMenuLastScrollPosition);
    }
}

static void Task_ListMenuRemoveScrollIndicatorArrowPair(u8 taskId)
{
    struct Task * task = &gTasks[taskId];
    if (task->data[0] != task->data[1])
        RemoveScrollIndicatorArrowPair(task->data[12]);
}

void ForcePlayerToStartSurfing(void)
{
    SetHelpContext(HELPCONTEXT_SURFING);
    SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_SURFING);
}

//change this to show return value from arrays.
//use regional pokemon only
//will be list of alternative starters, for the most part try keep type relation between each the same.
//player    rival
//bulbasaur -> charmander
//squirtle ->  bulbasaur
//charmander -> squirtle

//#define LIST_END 0xFFFF   //since I'm not doing a loop, I don't really need List_End, just need to match my random function to number of values 
//couting first list value as 0. Need to use random percent equal to value shown when hovering over array. Just used nelms so I don't have to manually change
//just need each array to be equal on hover  and check for type exceptions

//should beat/resist water type or be weak to/against fire
const u16 sBulbasaurBall[] = {
    SPECIES_BULBASAUR,
    SPECIES_CHIKORITA,
    SPECIES_TREECKO,
    SPECIES_TURTWIG,
    SPECIES_SNIVY,
    SPECIES_CHESPIN,
    SPECIES_ROWLET,
    SPECIES_GROOKEY,
    SPECIES_AIPOM, //doesnt make sense I just want to show off, would replace w voltorb but you can get those easily, so keep - also not normally available
    SPECIES_PARAS, //i love it, but its too common? no keeping it, instead I'll take it out of mt moon and reserve for safari zone, replace w something else female nido
    SPECIES_VULPIX_ALOLAN, //will put ditto in squirtle instead, or just replace it, but keep for now as its best tester for loop as only 3 mon should break out of loop
    SPECIES_SEEDOT,  //replaced tyrogue w ditto, show off changed transform mechanics, /ditto doesn't make sense here, breaks type check as it resists fire
    SPECIES_EEVEE, //free eevee  lets go style
    SPECIES_RALTS, //resists fire - no it doesn't its resisted by fire, I keep confusin the fairy fire relation, but fairy is bad against fire
    SPECIES_TYROGUE,
    SPECIES_MAGNEMITE,
    SPECIES_BUNEARY,
    SPECIES_SUNKERN,
    SPECIES_SCYTHER,
    SPECIES_MINCCINO,
    SPECIES_HOPPIP, //too common, replacing oddish, replaced with hoppip, also a mon that saw significant changes
    SPECIES_STUFFUL,
    SPECIES_FOMANTIS,
    SPECIES_SPRITZEE, //replace
    SPECIES_FOONGUS, //doesnt work well, breaks relation of lists, hmm replace w voltorb, pokeball in a pokeball - replaced w foongus instead as voltorbn common
    SPECIES_PANSAGE,
    SPECIES_TOGEDEMARU
    //LIST_END
}; //this list matches the best the others need more work -think will move swinub and ditto to squirtle list, and just add 2 to other lists

//should beat/resist fire, or be weak to/against grass
const u16 sSquirtleBall[] = {
    SPECIES_SQUIRTLE,
    SPECIES_TOTODILE,
    SPECIES_MUDKIP,
    SPECIES_PIPLUP,
    SPECIES_OSHAWOTT,
    SPECIES_FROAKIE,
    SPECIES_POPPLIO,
    SPECIES_BINACLE,
    SPECIES_TRAPINCH, //doesn't work cant use a dragon it resists everything, can put in squirtle bal
    SPECIES_CORSOLA,
    SPECIES_BONSLY, //replaced bonsly put it in a forest, BROUGHT bonsley back  fits cute starters
    SPECIES_EEVEE,
    SPECIES_TEDDIURSA, //replaced lotad
    SPECIES_HELIOPTILE,
    SPECIES_PHANPY,
    SPECIES_AZURILL, //I like azurill but others maybe not, so replace w just marill, as it works for type checklist, while marill doesn't as its not watter, 'w fix for selection function can put back?
    SPECIES_ROCKRUFF,
    SPECIES_SKITTY, //with ghost change skitty would be better in squirtle group, I just want it there, starter doesn't work well as not ghost until evoles,
    SPECIES_PANPOUR,
    SPECIES_SANDSHREW, //resist fire weak to grass, but electric in grass ball breaks list
    SPECIES_SWINUB,
    SPECIES_WOOPER,
    SPECIES_BUNNELBY, //works but I like SPECIES_GOLETT better? is more interesting/popular , replaced rogenrolla //oh right didn't use cuz ghost was free early game wins
    SPECIES_LOTAD,  //REPLACED wailmer
    SPECIES_CASTFORM,   //easter egg mon, not really good for starter otherwise/ rebalancing ability effect would be better in squirtle set can swap w ditto
    SPECIES_SANDILE,
    //SPECIES_SOBBLE,  //make new area sevii island to get all gen starters, rare safari zone, mon will be higher level but all starter form
    SPECIES_SPHEAL
    //LIST_END
};

//should beat/resist grass type and or be weak to/against water
const u16 sCharmanderBall[] = {
    SPECIES_CHARMANDER,
    SPECIES_CYNDAQUIL,
    SPECIES_TORCHIC,
    SPECIES_CHIMCHAR,
    SPECIES_TEPIG,
    SPECIES_FENNEKIN,
    SPECIES_LITTEN,
    SPECIES_SCORBUNNY,
    SPECIES_GLIGAR, //weak to water, poison beats grass
    SPECIES_DITTO,
    SPECIES_EEVEE,
    SPECIES_MURKROW,    //beats grass no relation to water
    SPECIES_NICKIT,
    SPECIES_LICKITUNG,
    SPECIES_RIOLU,
    SPECIES_PANSEAR,
    SPECIES_PONYTA,
    SPECIES_NUMEL, //removed litwick put them in laverge tower
    SPECIES_NOIBAT, //replaced tediursa, looks like a starter but doesn't quite match type since it resists water, but keeping
    SPECIES_STUNKY, //can show off new ability?
    SPECIES_FLETCHLING,
    SPECIES_CUFANT,
    SPECIES_TOGEPI,
    SPECIES_MILTANK,
    SPECIES_GROWLITHE_HISUIAN,    //didn't have graphics just added
    SPECIES_DODUO,  //flyign so beats grass no affiliation to water
    SPECIES_HOUNDOUR
    //LIST_END
};

//setup define for nuber of starters, to plug in for in place of % n
//right now value matches hover over value for array, so count of values in array should be able to make things more efficient.


//started with entire list step 1, remove mono type, step 2 remove all I want to list as type 1.  keep all I want listed as type 2 in teh script here.
//this array below is to substitute type 2 in the oak script where he reads the starter choice. "you picked the *blank* type, species name"
//update the definitnion this value when adding to the array
//should be number of values in array count from 1 not 0.
const u16 sTypeExceptions[] = {
    SPECIES_BINACLE,
    SPECIES_RALTS,
    SPECIES_SPHEAL,
    SPECIES_MURKROW,
    SPECIES_LICKITUNG,
    SPECIES_HOUNDOUR,
    SPECIES_AZURILL,
    SPECIES_TOGEPI,
    SPECIES_DODUO,
    SPECIES_FLETCHLING,
    SPECIES_SANDSHREW,
    SPECIES_PHANPY,
    SPECIES_CASTFORM,
    SPECIES_BUNNELBY,
    SPECIES_ROCKRUFF,
    SPECIES_GLIGAR,
    SPECIES_PONYTA,
    SPECIES_TEPIG
};

static const u16 sStarterSpecies[] = { //ok didn't realize changing starter species was this simple and I didn't need a script but wtvr.
    // but looking at this gives me idea for setting up the other thing I wanted, if I use switch cases to include multiple pokemon on same idea, with random chance.
    SPECIES_BULBASAUR,// then I can have multiple options so each playthrough the mon in the pokeball is different, 
    SPECIES_SQUIRTLE, //not sure if that change needs to be HERE or with the VAR_STARTER_MON from getstarterspecies down below..
    SPECIES_CHARMANDER
};//maybe could do something like form_species_table_pointers file where spcies = another table, which can be an array of different species?
//if I can get to that point, I just need to make it chose a value within that array, with random % n (where n will be size of array)

static u16 GetStarterSpeciesById(u16 idx)
{
    if (idx >= NELEMS(sStarterSpecies))
        idx = 0;
    return sStarterSpecies[idx];
}

//plan to use for eevee evolution check in CreateNPCTrainerParty (battle_main.c)  if rival starter species was eevee check this  function result 
//if return squirtle - evolve into jolteon or leafeon
//if bulbasaur - evolve into flareon or glaceon -(or cefiereon as its flying)
//if charmander - evolve into vaporeon or sylveon
//potentailly make arrays for starter based eeveelutions so I can just use random % nelems for filter can do species = sEeveelutionarray[Random() % NELEMS(sEeveelutionarray)]
//will just make a function that does the checks and selection when run and just put that in CreateNPCTrainerParty can make arrays static that way as well
u16 GetStarterSpecies(void) //this is just used for the roamer,  
{
    return GetStarterSpeciesById(VarGet(VAR_STARTER_MON));
}

const u16 sEeveelutionGrassStarter[] =
{
    SPECIES_FLAREON,
    SPECIES_GLACEON,
    SPECIES_CEFIREON
};

const u16 sEeveelutionWaterStarter[] =
{
    SPECIES_JOLTEON,
    SPECIES_LEAFEON
};

const u16 sEeveelutionFireStarter[] =
{
    SPECIES_VAPOREON,
    SPECIES_SYLVEON
};

const u16 sEeveelutionListing[] =
{
    SPECIES_FLAREON,
    SPECIES_GLACEON,
    SPECIES_CEFIREON,
    SPECIES_JOLTEON,
    SPECIES_LEAFEON,
    SPECIES_VAPOREON,
    SPECIES_ESPEON,
    SPECIES_UMBREON,
    SPECIES_SYLVEON
};


#define STARTER_BULBASAUR   0
#define STARTER_SQUIRTLE    1
#define STARTER_CHARMANDER  2

//NELEMS average doesn't work, whatever happened, it caused the game to reset...on some value.
//trying it again, may have been parenthesis.
//it was the parenthesis, cause of how nelems works, needed each one
//to be separated before adding, group them all in a parenthesis, and then set the divider on the outside
//but also in parenthesis.

//ok so none of that was actually the issue, the problem seems to be that a pokemon's name
//is too long for the  buffer and is causing overflow just like brock's text

//#define STARTERCOUNT 13 //(((NELEMS(sBulbasaurBall)) + (NELEMS(sSquirtleBall)) + (NELEMS(sCharmanderBall))) / 3)

//with advice from ExpoSeed, instead of using a define averaging the array, just use NELEMS array in place of n

//eventually make dynamic so it works off of counting and averaging the arrays essentially  (n + n + n) / 3 = n
void SetPlayerRandomStarterSpecies(void)
{
    /*VarSet(VAR_TEMP_5, SPECIES_BONSLY);    //for testing
    VarSet(VAR_TEMP_6, SPECIES_BONSLY);
    VarSet(VAR_TEMP_7, SPECIES_BONSLY);*/
    

    VarSet(VAR_TEMP_5, sBulbasaurBall[Random() % NELEMS(sBulbasaurBall)]);
    VarSet(VAR_TEMP_6, sSquirtleBall[Random() % NELEMS(sSquirtleBall)]);
    VarSet(VAR_TEMP_7, sCharmanderBall[Random() % NELEMS(sCharmanderBall)]);
}

//vsonic add further logic to this, long as player starter randomized first, can reroll this based on that to ensure type alignment matches advantage/disadvantage
//inspired metronome/pickup logic, just need compare with respective player var i.e  bulb var == sbulbasaurball[value]  
// && rival chrmanderball var  is scharmanderball[value]  reroll  this way I can preserve the relationship or at the least don't end up with an advantage to rival starter
//for exmample if I as player roll value that gives me a tyrogue, rival is unable to save value for miltank, which would give me advantage.
//instead if they landed on that they would reroll.  ...damn I miss vs studio. 
void SetRivalRandomStarterSpecies(void) 
{
    VarSet(VAR_TEMP_8, sCharmanderBall[Random() % NELEMS(sCharmanderBall)]);
    VarSet(VAR_TEMP_9, sBulbasaurBall[Random() % NELEMS(sBulbasaurBall)]);
    VarSet(VAR_TEMP_A, sSquirtleBall[Random() % NELEMS(sSquirtleBall)]);
}

//condition for this function to run if rival starter species eevee, and var species is currently still eevee.
//as it runs random it can't be run each time rival encountered as evolution species would change each battle
//so need this to just be run a single time when rival starter should first evolve
//with changes done gonna need to redo eeveelution setup with logic just added to chose evolution based on type rather than random selection
u16 RivalEeveelutionForPlayerStarter(void) //rather than this can just do like,   other set random from evelution list check fi its super if not loop and redo
{

    u16 ChosenEvolution;
    u16 viable_Eeveelution = 0;  //assign later make sure use plus 1 when using w random, as it'll be used, nvm w way I used dont need + 1
    u16 PlayeStarterSpecies = VarGet(VAR_PLAYER_STARTER); //need get final evo  //this is the problem

    
    //assign random eeveelution compare against player final evo,
    //if it fails super checks chose another random form and run again
    for ((ChosenEvolution = Random() % NELEMS(sEeveelutionListing)); ; (ChosenEvolution = Random() % NELEMS(sEeveelutionListing)))
    {
        if (CheckSuperEffective(sEeveelutionListing[ChosenEvolution], GetFinalEvo(PlayeStarterSpecies)))
        {
            break;
        }
            
    }
    viable_Eeveelution = sEeveelutionListing[ChosenEvolution];

    return viable_Eeveelution;

    /*if (starter == STARTER_BULBASAUR)
        return sEeveelutionGrassStarter[Random() % NELEMS(sEeveelutionGrassStarter)];
    else if (starter == STARTER_SQUIRTLE)
        return sEeveelutionWaterStarter[Random() % NELEMS(sEeveelutionWaterStarter)];
    else if (starter == STARTER_CHARMANDER)
        return sEeveelutionFireStarter[Random() % NELEMS(sEeveelutionFireStarter)];*/
}

//mostly for eevee rival check, simple would only work for non branching evo
//can possibly usefor move relearn nvm for that I need to read evo chart in reverse
//put learnset of current species at top then loop species for target species that equals my species
//set that species learnset to list then loop again to check for a mon that has that as the target species, if hit last value stop loop.
//I know understand why this didn't work if you try to evolve a mon withuot an evo
//it doesnt return species none, it'll just return the same species, i.e trying to evolve a charizard will just return a charizard
//so to fix it I need to make my break condition species != targetspecies
//ok nvm I had that wrong, I was returning species not target species, 
//when you try to evolve a mon that can't evolve it seems to return garbage data?
//...ok it seems to return species none...
u16 GetFinalEvo(u16 species) //well least it works now
{

    u16 targetSpecies = gEvolutionTable[species][0].targetSpecies;

    for (; targetSpecies != SPECIES_NONE; targetSpecies = gEvolutionTable[species][0].targetSpecies)
    {
        species = targetSpecies;        
    }

    return species; //think should loop first evo method encountered for a species, and go until it can't find an evolution, then stop and return species
}

//make into field command,
//if this function does not return/equal species_none make setmonspecies with this functions value as species
u16 De_Evolve(u16 targetSpecies)
{
    u32 j;
    u16 species;

    for (species = 0; species != FORMS_START; species++)
    {
        for (j = 0; j != EVOS_PER_MON; j++)
        {
           if (gEvolutionTable[species][j].targetSpecies == targetSpecies)
            {
                //targetSpecies = species;
                //species = 0;
                return species;
                break;
            }
        }
    }
    if (species == FORMS_START)
        return SPECIES_NONE;
}

u16 Init_movelearn_options(u16 targetSpecies)
{
    u16 preEvos;
    for (; De_Evolve(targetSpecies) != SPECIES_NONE; targetSpecies = De_Evolve(targetSpecies))
    {
        preEvos = De_Evolve(targetSpecies);
        //add preEvos to move learn species list

    }

}
//plan for these two to be used to setup move learn that checks entire species line

u8 CheckSuperEffective(u16 Atk_Species, u16 Target_Species) //is super effective
{
    u8 passedChecks = 0;
    u8 Atktype1 = gBaseStats[Atk_Species].type1;
    u8 Atktype2 = gBaseStats[Atk_Species].type2;
    u8 targetType1 = gBaseStats[Target_Species].type1;
    u8 targetType2 = gBaseStats[Target_Species].type2;
    u16 AtkMultiplierType1 = UQ_4_12(1.0);
    u16 AtkMultiplierType2 = UQ_4_12(1.0);
    u16 DefenseMultiplierType1 = UQ_4_12(1.0);
    u16 DefenseMultiplierType2 = UQ_4_12(1.0);


            //check for if rival starter super against player starter
            MulModifier(&AtkMultiplierType1, (GetTypeModifier(Atktype1, targetType1)));
              if (targetType1 != targetType2)
                MulModifier(&AtkMultiplierType1, (GetTypeModifier(Atktype1, targetType2)));

            if (Atktype2 != Atktype1)
            {
                MulModifier(&AtkMultiplierType2, (GetTypeModifier(Atktype2, targetType1)));
                if (targetType1 != targetType2)
                    MulModifier(&AtkMultiplierType2, (GetTypeModifier(Atktype2, targetType2)));
            }

            //check for if rival starter resists player starter
            MulModifier(&DefenseMultiplierType1, (GetTypeModifier(targetType1, Atktype1)));
              if (Atktype1 != Atktype2)
                MulModifier(&DefenseMultiplierType1, (GetTypeModifier(targetType1, Atktype2)));

            if (targetType2 != targetType1)
            {
                MulModifier(&DefenseMultiplierType2, (GetTypeModifier(targetType2, Atktype1)));
                if (Atktype1 != Atktype2)
                    MulModifier(&DefenseMultiplierType2, (GetTypeModifier(targetType2, Atktype2)));
            }

            
            //check for if rival starter super against player starter
            if (AtkMultiplierType1 > UQ_4_12(1.0)
            || AtkMultiplierType2 > UQ_4_12(1.0))
                ++passedChecks;

            if (targetType1 == TYPE_FAIRY)
            {
                if (DefenseMultiplierType1 < UQ_4_12(1.0)
                || DefenseMultiplierType2 < UQ_4_12(1.0))
                ++passedChecks;
            } //since umbreon is only option for super against fairy, and umbreon is also weak against fairy, this adds lefeon and flareon to the list

            //check for if rival starter resists player starter
            /*else if (DefenseMultiplierType1 <= UQ_4_12(1.0)
            || DefenseMultiplierType2 <= UQ_4_12(1.0))
                ++passedChecks;*/
            if (passedChecks)
                return TRUE;
            else
                return FALSE;
}



u8 ShouldResetRivalStarter(void)
{
    u8 Playerstarter = VarGet(VAR_STARTER_MON);
    u16 PlayeStarterSpecies = VarGet(VAR_PLAYER_STARTER);  //only need to prevent double eevee
    u16 species,playermon;
    u8 type1;
    u8 type2;
    u8 passedChecks = 0;
    u16 AtkMultiplierType1 = UQ_4_12(1.0);
    u16 AtkMultiplierType2 = UQ_4_12(1.0);
    u16 DefenseMultiplierType1 = UQ_4_12(1.0);
    u16 DefenseMultiplierType2 = UQ_4_12(1.0);

    //u16 GetTypeModifier(moveType, defType); checked and all I actually need is this  replace movetype with attacking types type

    if (Playerstarter == STARTER_BULBASAUR)
    {
        species = GetFinalEvo(VarGet(VAR_TEMP_8));
        playermon = GetFinalEvo(VarGet(VAR_TEMP_5)); //need change this to get final evo, check createnpctrainer for how to do, or not prob fine without it
        type1 = gBaseStats[species].type1;
        type2 = gBaseStats[species].type2;

        if (species == SPECIES_EEVEE && PlayeStarterSpecies == SPECIES_EEVEE)
            passedChecks = FALSE;
        else if (species == SPECIES_EEVEE || species == SPECIES_DITTO)
            passedChecks = TRUE;
        else
        {
            //check for if rival starter super against player starter
            MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type1)));
              if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type2)));

            if (type2 != type1)
            {
                MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type1)));
                if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                    MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type2)));
            }

            //check for if rival starter resists player starter
            MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type1)));
              if (type1 != type2)
                MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type2)));

            if (gBaseStats[playermon].type2 != gBaseStats[playermon].type1)
            {
                MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type1)));
                if (type1 != type2)
                    MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type2)));
            }

            
            //check for if rival starter super against player starter
            if (AtkMultiplierType1 >= UQ_4_12(1.0)
            || AtkMultiplierType2 >= UQ_4_12(1.0))
                ++passedChecks;

            //check for if rival starter resists player starter
            else if (DefenseMultiplierType1 <= UQ_4_12(1.0)
            || DefenseMultiplierType2 <= UQ_4_12(1.0))
                ++passedChecks;

            //final catches to ensure rival is not resisted by player
            if (AtkMultiplierType1 < UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            else if (AtkMultiplierType2 < UQ_4_12(1.0)
            && AtkMultiplierType1 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            //final final catch to ensure player not super to rival withuot counter
            //if right should make it so player only allowed to be super to rival if rival is also super to player
            if ((DefenseMultiplierType1 > UQ_4_12(1.0)
            || DefenseMultiplierType2 > UQ_4_12(1.0))
            && AtkMultiplierType1 <= UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;
            
        }
    }

    else if (Playerstarter == STARTER_SQUIRTLE)
    {
        species = GetFinalEvo(VarGet(VAR_TEMP_9));
        playermon = GetFinalEvo(VarGet(VAR_TEMP_6));
        type1 = gBaseStats[species].type1;
        type2 = gBaseStats[species].type2;

        if (species == SPECIES_EEVEE && PlayeStarterSpecies == SPECIES_EEVEE)
            passedChecks = FALSE;
        else if (species == SPECIES_EEVEE || species == SPECIES_DITTO)
            passedChecks = TRUE;
        else
        {
            //check for if rival starter super against player starter
            MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type1)));
              if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type2)));

            if (type2 != type1)
            {
                MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type1)));
                if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                    MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type2)));
            }

            //check for if rival starter resists player starter
            MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type1)));
              if (type1 != type2)
                MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type2)));

            if (gBaseStats[playermon].type2 != gBaseStats[playermon].type1)
            {
                MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type1)));
                if (type1 != type2)
                    MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type2)));
            }

            //check for if rival starter super against player starter
            if (AtkMultiplierType1 >= UQ_4_12(1.0)
            || AtkMultiplierType2 >= UQ_4_12(1.0))
                ++passedChecks;

            //check for if rival starter resists player starter
            else if (DefenseMultiplierType1 <= UQ_4_12(1.0)
            || DefenseMultiplierType2 <= UQ_4_12(1.0))
                ++passedChecks;

            //final catches to ensure rival is not resisted by player
            if (AtkMultiplierType1 < UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            else if (AtkMultiplierType2 < UQ_4_12(1.0)
            && AtkMultiplierType1 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            //final final catch to ensure player not super to rival withuot counter
            //if right should make it so player only allowed to be super to rival if rival is also super to player
            if ((DefenseMultiplierType1 > UQ_4_12(1.0)
            || DefenseMultiplierType2 > UQ_4_12(1.0))
            && AtkMultiplierType1 <= UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            //specific exception case
            if (species == SPECIES_SCIZOR && playermon == SPECIES_SUDOWOODO)
                passedChecks = FALSE;
            
        }
    }

    else if (Playerstarter == STARTER_CHARMANDER)
    {
        species = GetFinalEvo(VarGet(VAR_TEMP_A));
        playermon = GetFinalEvo(VarGet(VAR_TEMP_7));
        type1 = gBaseStats[species].type1;
        type2 = gBaseStats[species].type2;

        if (species == SPECIES_EEVEE && PlayeStarterSpecies == SPECIES_EEVEE)
            passedChecks = FALSE;
        else if (species == SPECIES_EEVEE || species == SPECIES_DITTO)
            passedChecks = TRUE;
        else
        {
            //check for if rival starter super against player starter
            MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type1)));
              if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                MulModifier(&AtkMultiplierType1, (GetTypeModifier(type1, gBaseStats[playermon].type2)));

            if (type2 != type1)
            {
                MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type1)));
                if (gBaseStats[playermon].type1 != gBaseStats[playermon].type2)
                    MulModifier(&AtkMultiplierType2, (GetTypeModifier(type2, gBaseStats[playermon].type2)));
            }

            //check for if rival starter resists player starter
            MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type1)));
              if (type1 != type2)
                MulModifier(&DefenseMultiplierType1, (GetTypeModifier(gBaseStats[playermon].type1, type2)));

            if (gBaseStats[playermon].type2 != gBaseStats[playermon].type1)
            {
                MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type1)));
                if (type1 != type2)
                    MulModifier(&DefenseMultiplierType2, (GetTypeModifier(gBaseStats[playermon].type2, type2)));
            }

            
            //check for if rival starter super against player starter
            if (AtkMultiplierType1 >= UQ_4_12(1.0)
            || AtkMultiplierType2 >= UQ_4_12(1.0))
                ++passedChecks;

            //check for if rival starter resists player starter
            else if (DefenseMultiplierType1 <= UQ_4_12(1.0)
            || DefenseMultiplierType2 <= UQ_4_12(1.0))
                ++passedChecks;

            //final catches to ensure rival is not resisted by player
            if (AtkMultiplierType1 < UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            else if (AtkMultiplierType2 < UQ_4_12(1.0)
            && AtkMultiplierType1 <= UQ_4_12(1.0))
                passedChecks = FALSE;

            //final final catch to ensure player not super to rival withuot counter
            //if right should make it so player only allowed to be super to rival if rival is also super to player
            if ((DefenseMultiplierType1 > UQ_4_12(1.0)
            || DefenseMultiplierType2 > UQ_4_12(1.0))
            && AtkMultiplierType1 <= UQ_4_12(1.0)
            && AtkMultiplierType2 <= UQ_4_12(1.0))
                passedChecks = FALSE;
            
        }
    }

    if (passedChecks) //if meets my conditions don't need to reset
    {
        return FALSE;
    }        
    else
    {
        return TRUE;
    }
}

//works issue was just it was in the wrong place within the script
void RivalStarterConditionCheck(void) 
{

    while(ShouldResetRivalStarter() == TRUE)
    {
        SetRivalRandomStarterSpecies();
    }
    
}

void SetSeenMon(void)
{
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(gSpecialVar_0x8004), 2);
}

void ResetContextNpcTextColor(void)
{
    gSelectedObjectEvent = 0;
    gSpecialVar_TextColor = 0xFF;
}

u8 ContextNpcGetTextColor(void)
{
    u8 gfxId;
    if (gSpecialVar_TextColor != 0xFF)
        return gSpecialVar_TextColor;
    else if (gSelectedObjectEvent == 0)
        return 3;
    else
    {
        gfxId = gObjectEvents[gSelectedObjectEvent].graphicsId;
        if (gfxId >= OBJ_EVENT_GFX_VAR_0)
            gfxId = VarGetObjectEventGraphicsId(gfxId - OBJ_EVENT_GFX_VAR_0);
        return GetColorFromTextColorTable(gfxId);
    }
}

static bool8 HasMonBeenRenamed(u8 idx)
{
    struct Pokemon * pokemon = &gPlayerParty[idx];
    u8 language;
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    language = GetMonData(pokemon, MON_DATA_LANGUAGE, &language);
    if (language != LANGUAGE_ENGLISH)
        return TRUE;
    else if (StringCompare(gSpeciesNames[GetMonData(pokemon, MON_DATA_SPECIES, NULL)], gStringVar1) != 0)
        return TRUE;
    else
        return FALSE;
}

bool8 HasLeadMonBeenRenamed(void)
{
    return HasMonBeenRenamed(GetLeadMonIndex());
}

void TV_PrintIntToStringVar(u8 varidx, s32 number)
{
    s32 n = CountDigits(number);
    ConvertIntToDecimalStringN(sStringVarPtrs[varidx], number, STR_CONV_MODE_LEFT_ALIGN, n);
}

s32 CountDigits(s32 number)
{
    if (number / 10 == 0)
        return 1;
    else if (number / 100 == 0)
        return 2;
    else if (number / 1000 == 0)
        return 3;
    else if (number / 10000 == 0)
        return 4;
    else if (number / 100000 == 0)
        return 5;
    else if (number / 1000000 == 0)
        return 6;
    else if (number / 10000000 == 0)
        return 7;
    else if (number / 100000000 == 0)
        return 8;
    else
        return 1;
}

bool8 NameRaterWasNicknameChanged(void)
{
    struct Pokemon * pokemon = &gPlayerParty[gSpecialVar_0x8004];
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    if (StringCompare(gStringVar3, gStringVar1) == 0)
        return FALSE;
    else
        return TRUE;
}

void ChangeBoxPokemonNickname(void)
{
    struct BoxPokemon * pokemon = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    u16 species;
    u8 gender;
    u32 personality;


    GetBoxMonData(pokemon, MON_DATA_NICKNAME, gStringVar3);
    GetBoxMonData(pokemon, MON_DATA_NICKNAME, gStringVar2);
    species = GetBoxMonData(pokemon, MON_DATA_SPECIES, NULL);
    gender = GetBoxMonGender(pokemon);
    personality = GetBoxMonData(pokemon, MON_DATA_PERSONALITY, NULL);
    DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar2, species, gender, personality, ChangeBoxPokemonNickname_CB);
}

static void ChangeBoxPokemonNickname_CB(void)
{
    SetBoxMonNickAt(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos, gStringVar2);
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
}

void ChangePokemonNickname(void)
{
    u16 species;
    u8 gender;
    u32 personality;

    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar3);
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar2);
    species = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES, NULL);
    gender = GetMonGender(&gPlayerParty[gSpecialVar_0x8004]);
    personality = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_PERSONALITY, NULL);
    DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar2, species, gender, personality, ChangePokemonNickname_CB);
}

static void ChangePokemonNickname_CB(void)
{
    SetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar2);
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
}

void BufferMonNickname(void)
{
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar1);
    StringGet_Nickname(gStringVar1);
}

void IsMonOTIDNotPlayers(void)
{
    if (GetPlayerTrainerId() == GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_OT_ID, NULL))
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
}

u32 GetPlayerTrainerId(void)
{
    return (gSaveBlock2Ptr->playerTrainerId[3] << 24) | (gSaveBlock2Ptr->playerTrainerId[2] << 16) | (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];
}

u8 GetUnlockedSeviiAreas(void)
{
    u8 result = 0;
    if (FlagGet(FLAG_WORLD_MAP_ONE_ISLAND) == TRUE)
        result |= 1 << 0;
    if (FlagGet(FLAG_WORLD_MAP_TWO_ISLAND) == TRUE)
        result |= 1 << 1;
    if (FlagGet(FLAG_WORLD_MAP_THREE_ISLAND) == TRUE)
        result |= 1 << 2;
    if (FlagGet(FLAG_WORLD_MAP_FOUR_ISLAND) == TRUE)
        result |= 1 << 3;
    if (FlagGet(FLAG_WORLD_MAP_FIVE_ISLAND) == TRUE)
        result |= 1 << 4;
    if (FlagGet(FLAG_WORLD_MAP_SIX_ISLAND) == TRUE)
        result |= 1 << 5;
    if (FlagGet(FLAG_WORLD_MAP_SEVEN_ISLAND) == TRUE)
        result |= 1 << 6;
    return result;
}

void UpdateTrainerCardPhotoIcons(void)
{
    u16 species[PARTY_SIZE];
    u32 personality[PARTY_SIZE];
    u8 i;
    u8 partyCount;
    for (i = 0; i < PARTY_SIZE; i++)
        species[i] = SPECIES_NONE;
    partyCount = CalculatePlayerPartyCount();
    for (i = 0; i < partyCount; i++)
    {
        species[i] = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL);
        personality[i] = GetMonData(&gPlayerParty[i], MON_DATA_PERSONALITY, NULL);
    }
    VarSet(VAR_TRAINER_CARD_MON_ICON_1, SpeciesToMailSpecies(species[0], personality[0]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_2, SpeciesToMailSpecies(species[1], personality[1]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_3, SpeciesToMailSpecies(species[2], personality[2]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_4, SpeciesToMailSpecies(species[3], personality[3]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_5, SpeciesToMailSpecies(species[4], personality[4]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_6, SpeciesToMailSpecies(species[5], personality[5]));
    VarSet(VAR_TRAINER_CARD_MON_ICON_TINT_IDX, gSpecialVar_0x8004);
}

u16 StickerManGetBragFlags(void)
{
    u16 result = 0;
    u32 numEggs;
    gSpecialVar_0x8004 = GetGameStat(GAME_STAT_ENTERED_HOF);
    numEggs = GetGameStat(GAME_STAT_HATCHED_EGGS);
    gSpecialVar_0x8006 = GetGameStat(GAME_STAT_LINK_BATTLE_WINS);
    if (numEggs > 0xFFFF)
        gSpecialVar_0x8005 = 0xFFFF;
    else
        gSpecialVar_0x8005 = numEggs;
    if (gSpecialVar_0x8004 != 0)
        result |= 1 << 0;
    if (gSpecialVar_0x8005 != 0)
        result |= 1 << 1;
    if (gSpecialVar_0x8006 != 0)
        result |= 1 << 2;
    return result;
}

u16 GetHiddenItemAttr(u32 hiddenItem, u8 attr)
{
    if (attr == 0)
        return hiddenItem & 0xFFFF;
    else if (attr == 1)
        return ((hiddenItem >> 16) & 0xFF) + 1000;
    else if (attr == 2)
        return (hiddenItem >> 24) & 0x7F;
    else if (attr == 3)
        return (hiddenItem >> 31) & 0x01;
    else
        return 1;
}

bool8 DoesPlayerPartyContainSpecies(void)
{
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < partyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL) == gSpecialVar_0x8004)
            return TRUE;
    }
    return FALSE;
}

static const u8 sMartMaps[][3] = {
    {MAP(VIRIDIAN_CITY_MART),   1},
    {MAP(PEWTER_CITY_MART),     3},
    {MAP(CERULEAN_CITY_MART),   1},
    {MAP(LAVENDER_TOWN_MART),   1},
    {MAP(VERMILION_CITY_MART),  1},
    {MAP(FUCHSIA_CITY_MART),    1},
    {MAP(CINNABAR_ISLAND_MART), 1},
    {MAP(SAFFRON_CITY_MART),    1},
    {MAP(THREE_ISLAND_MART),    1},
    {MAP(FOUR_ISLAND_MART),     1},
    {MAP(SEVEN_ISLAND_MART),    1},
    {MAP(SIX_ISLAND_MART),      1}
};

u8 GetMartClerkObjectId(void)
{
    u8 i;
    for (i = 0; i < NELEMS(sMartMaps); i++)
    {
        if (gSaveBlock1Ptr->location.mapGroup == sMartMaps[i][0] && gSaveBlock1Ptr->location.mapNum == sMartMaps[i][1])
            return sMartMaps[i][2];
    }
    return 1;
}

void SetUsedPkmnCenterQuestLogEvent(void)
{
    SetQuestLogEvent(QL_EVENT_USED_PKMN_CENTER, NULL);
}

static const struct {
    u16 grp;
    u16 num;
    u16 grp2;
    u16 num2;
} sInsideOutsidePairs[51] = {
    [QL_LOCATION_HOME]               = {MAP(PALLET_TOWN_PLAYERS_HOUSE_1F),          MAP(PALLET_TOWN)},
    [QL_LOCATION_OAKS_LAB]           = {MAP(PALLET_TOWN_PROFESSOR_OAKS_LAB),        MAP(PALLET_TOWN)},
    [QL_LOCATION_VIRIDIAN_GYM]       = {MAP(VIRIDIAN_CITY_GYM),                     MAP(VIRIDIAN_CITY)},
    [QL_LOCATION_LEAGUE_GATE_1]      = {MAP(ROUTE22_NORTH_ENTRANCE),                MAP(ROUTE22)},
    [QL_LOCATION_LEAGUE_GATE_2]      = {MAP(ROUTE22_NORTH_ENTRANCE),                MAP(ROUTE23)},
    [QL_LOCATION_VIRIDIAN_FOREST_1]  = {MAP(VIRIDIAN_FOREST),                       MAP(ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE)},
    [QL_LOCATION_VIRIDIAN_FOREST_2]  = {MAP(VIRIDIAN_FOREST),                       MAP(ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE)},
    [QL_LOCATION_PEWTER_MUSEUM]      = {MAP(PEWTER_CITY_MUSEUM_1F),                 MAP(PEWTER_CITY)},
    [QL_LOCATION_PEWTER_GYM]         = {MAP(PEWTER_CITY_GYM),                       MAP(PEWTER_CITY)},
    [QL_LOCATION_MT_MOON_1]          = {MAP(MT_MOON_1F),                            MAP(ROUTE4)},
    [QL_LOCATION_MT_MOON_2]          = {MAP(MT_MOON_B1F),                           MAP(ROUTE4)},
    [QL_LOCATION_CERULEAN_GYM]       = {MAP(CERULEAN_CITY_GYM),                     MAP(CERULEAN_CITY)},
    [QL_LOCATION_BIKE_SHOP]          = {MAP(CERULEAN_CITY_BIKE_SHOP),               MAP(CERULEAN_CITY)},
    [QL_LOCATION_BILLS_HOUSE]        = {MAP(ROUTE25_SEA_COTTAGE),                   MAP(ROUTE25)},
    [QL_LOCATION_DAY_CARE]           = {MAP(ROUTE5_POKEMON_DAY_CARE),               MAP(ROUTE5)},
    [QL_LOCATION_UNDERGROUND_PATH_1] = {MAP(UNDERGROUND_PATH_NORTH_ENTRANCE),       MAP(ROUTE5)},
    [QL_LOCATION_UNDERGROUND_PATH_2] = {MAP(UNDERGROUND_PATH_SOUTH_ENTRANCE),       MAP(ROUTE6)},
    [QL_LOCATION_PKMN_FAN_CLUB]      = {MAP(VERMILION_CITY_POKEMON_FAN_CLUB),       MAP(VERMILION_CITY)},
    [QL_LOCATION_VERMILION_GYM]      = {MAP(VERMILION_CITY_GYM),                    MAP(VERMILION_CITY)},
    [QL_LOCATION_SS_ANNE]            = {MAP(SSANNE_1F_CORRIDOR),                    MAP(VERMILION_CITY)},
    [QL_LOCATION_DIGLETTS_CAVE_1]    = {MAP(DIGLETTS_CAVE_NORTH_ENTRANCE),          MAP(ROUTE2)},
    [QL_LOCATION_DIGLETTS_CAVE_2]    = {MAP(DIGLETTS_CAVE_SOUTH_ENTRANCE),          MAP(ROUTE11)},
    [QL_LOCATION_ROCK_TUNNEL_1]      = {MAP(ROCK_TUNNEL_1F),                        MAP(ROUTE10)},
    [QL_LOCATION_ROCK_TUNNEL_2]      = {MAP(ROCK_TUNNEL_1F),                        MAP(ROUTE10)},
    [QL_LOCATION_POWER_PLANT]        = {MAP(POWER_PLANT),                           MAP(ROUTE10)},
    [QL_LOCATION_PKMN_TOWER]         = {MAP(POKEMON_TOWER_1F),                      MAP(LAVENDER_TOWN)},
    [QL_LOCATION_VOLUNTEER_HOUSE]    = {MAP(LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE), MAP(LAVENDER_TOWN)},
    [QL_LOCATION_NAME_RATERS_HOUSE]  = {MAP(LAVENDER_TOWN_HOUSE2),                  MAP(LAVENDER_TOWN)},
    [QL_LOCATION_UNDERGROUND_PATH_3] = {MAP(UNDERGROUND_PATH_EAST_ENTRANCE),        MAP(ROUTE8)},
    [QL_LOCATION_UNDERGROUND_PATH_4] = {MAP(UNDERGROUND_PATH_WEST_ENTRANCE),        MAP(ROUTE7)},
    [QL_LOCATION_CELADON_DEPT_STORE] = {MAP(CELADON_CITY_DEPARTMENT_STORE_1F),      MAP(CELADON_CITY)},
    [QL_LOCATION_CELADON_MANSION]    = {MAP(CELADON_CITY_CONDOMINIUMS_1F),          MAP(CELADON_CITY)},
    [QL_LOCATION_GAME_CORNER]        = {MAP(CELADON_CITY_GAME_CORNER),              MAP(CELADON_CITY)},
    [QL_LOCATION_CELADON_GYM]        = {MAP(CELADON_CITY_GYM),                      MAP(CELADON_CITY)},
    [QL_LOCATION_CELADON_RESTAURANT] = {MAP(CELADON_CITY_RESTAURANT),               MAP(CELADON_CITY)},
    [QL_LOCATION_ROCKET_HIDEOUT]     = {MAP(ROCKET_HIDEOUT_B1F),                    MAP(CELADON_CITY_GAME_CORNER)},
    [QL_LOCATION_SAFARI_ZONE]        = {MAP(SAFARI_ZONE_CENTER),                    MAP(FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE)},
    [QL_LOCATION_FUCHSIA_GYM]        = {MAP(FUCHSIA_CITY_GYM),                      MAP(FUCHSIA_CITY)},
    [QL_LOCATION_WARDENS_HOME]       = {MAP(FUCHSIA_CITY_WARDENS_HOUSE),            MAP(FUCHSIA_CITY)},
    [QL_LOCATION_FIGHTING_DOJO]      = {MAP(SAFFRON_CITY_DOJO),                     MAP(SAFFRON_CITY)},
    [QL_LOCATION_SAFFRON_GYM]        = {MAP(SAFFRON_CITY_GYM),                      MAP(SAFFRON_CITY)},
    [QL_LOCATION_SILPH_CO]           = {MAP(SILPH_CO_1F),                           MAP(SAFFRON_CITY)},
    [QL_LOCATION_SEAFOAM_ISLANDS_1]  = {MAP(SEAFOAM_ISLANDS_1F),                    MAP(ROUTE20)},
    [QL_LOCATION_SEAFOAM_ISLANDS_2]  = {MAP(SEAFOAM_ISLANDS_1F),                    MAP(ROUTE20)},
    [QL_LOCATION_PKMN_MANSION]       = {MAP(POKEMON_MANSION_1F),                    MAP(CINNABAR_ISLAND)},
    [QL_LOCATION_CINNABAR_GYM]       = {MAP(CINNABAR_ISLAND_GYM),                   MAP(CINNABAR_ISLAND)},
    [QL_LOCATION_CINNABAR_LAB]       = {MAP(CINNABAR_ISLAND_POKEMON_LAB_ENTRANCE),  MAP(CINNABAR_ISLAND)},
    [QL_LOCATION_VICTORY_ROAD_1]     = {MAP(VICTORY_ROAD_1F),                       MAP(ROUTE23)},
    [QL_LOCATION_VICTORY_ROAD_2]     = {MAP(VICTORY_ROAD_2F),                       MAP(ROUTE23)},
    [QL_LOCATION_PKMN_LEAGUE]        = {MAP(INDIGO_PLATEAU_POKEMON_CENTER_1F),      MAP(INDIGO_PLATEAU_EXTERIOR)},
    [QL_LOCATION_CERULEAN_CAVE]      = {MAP(CERULEAN_CAVE_1F),                      MAP(CERULEAN_CITY)}
};

void sub_80CC534(void)
{
    u8 i;
    for (i = 0; i < NELEMS(sInsideOutsidePairs); i++)
    {
        if (gSaveBlock1Ptr->location.mapGroup == sInsideOutsidePairs[i].grp && gSaveBlock1Ptr->location.mapNum == sInsideOutsidePairs[i].num)
        {
            if (VarGet(VAR_0x404D) != QL_LOCATION_ROCKET_HIDEOUT || i != QL_LOCATION_GAME_CORNER)
            {
                VarSet(VAR_0x404D, i);
                FlagSet(FLAG_0x808);
            }
            break;
        }
    }
}

void sub_80CC59C(void)
{
    s16 x, y;
    struct {
        u8 unk0;
        u8 unk1;
    } sp0;
    u16 r5 = VarGet(VAR_0x404D);
    sp0.unk0 = 0;
    sp0.unk1 = 0;
    if (FlagGet(FLAG_0x808))
    {
        if (r5 == QL_LOCATION_VIRIDIAN_FOREST_1)
        {
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE) && (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE) || gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE2_VIRIDIAN_FOREST_NORTH_ENTRANCE)))
            {
                sp0.unk0 = MAPSEC_ROUTE_2;
                if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE2_VIRIDIAN_FOREST_SOUTH_ENTRANCE))
                    sp0.unk1 = r5;
                else
                    sp0.unk1 = r5 + 1;
                SetQuestLogEvent(QL_EVENT_DEPARTED, (void *)&sp0);
                FlagClear(FLAG_0x808);
                return;
            }
        }
        else if (r5 == QL_LOCATION_LEAGUE_GATE_1)
        {
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ROUTE22) && (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE22) || gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE23)))
            {
                sp0.unk0 = Overworld_GetMapHeaderByGroupAndId(sInsideOutsidePairs[r5].grp, sInsideOutsidePairs[r5].num)->regionMapSectionId;
                if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(ROUTE22))
                    sp0.unk1 = r5;
                else
                    sp0.unk1 = r5 + 1;
                SetQuestLogEvent(QL_EVENT_DEPARTED, (void *)&sp0);
                FlagClear(FLAG_0x808);
                return;
            }
        }
        if (gSaveBlock1Ptr->location.mapGroup == sInsideOutsidePairs[r5].grp2 && gSaveBlock1Ptr->location.mapNum == sInsideOutsidePairs[r5].num2)
        {
            sp0.unk0 = Overworld_GetMapHeaderByGroupAndId(sInsideOutsidePairs[r5].grp, sInsideOutsidePairs[r5].num)->regionMapSectionId;
            sp0.unk1 = r5;
            if (r5 == QL_LOCATION_ROCK_TUNNEL_1)
            {
                PlayerGetDestCoords(&x, &y);
                if (x != 15 || y != 26)
                    sp0.unk1++;
            }
            else if (r5 == QL_LOCATION_SEAFOAM_ISLANDS_1)
            {
                PlayerGetDestCoords(&x, &y);
                if (x != 67 || y != 15)
                    sp0.unk1++;
            }
            SetQuestLogEvent(QL_EVENT_DEPARTED, (void *)&sp0);
            FlagClear(FLAG_0x808);
            if (r5 == QL_LOCATION_ROCKET_HIDEOUT)
            {
                VarSet(VAR_0x404D, QL_LOCATION_GAME_CORNER);
                FlagSet(FLAG_0x808);
            }
        }
    }
}

u16 BattleCardAction(void)
{
    switch (gSpecialVar_Result)
    {
    case 0:
        return MEvent_GetBattleCardCount(3);
    case 1:
        return MEvent_GetBattleCardCount(4);
    case 2:
        return MEvent_GetBattleCardCount(0);
    case 3:
        return MEvent_GetBattleCardCount(1);
    case 4:
        return MEvent_GetBattleCardCount(2);
    default:
        AGB_ASSERT_EX(0, ABSPATH("scr_tool.c"), 3873);
        return 0;
    }
}

void SetPCBoxToSendMon(u8 boxId)
{
    sPCBoxToSendMon = boxId;
}

u16 GetPCBoxToSendMon(void)
{
    return sPCBoxToSendMon;
}

bool8 ShouldShowBoxWasFullMessage(void)
{
    if (FlagGet(FLAG_SHOWN_BOX_WAS_FULL_MESSAGE))
        return FALSE;
    if (StorageGetCurrentBox() == VarGet(VAR_PC_BOX_TO_SEND_MON))
        return FALSE;
    FlagSet(FLAG_SHOWN_BOX_WAS_FULL_MESSAGE);
    return TRUE;
}

bool8 IsDestinationBoxFull(void)
{
    s32 i;
    s32 j;
    SetPCBoxToSendMon(VarGet(VAR_PC_BOX_TO_SEND_MON));
    i = StorageGetCurrentBox();
    do
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            if (GetBoxMonData(GetBoxedMonPtr(i, j), MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            {
                if (GetPCBoxToSendMon() != i)
                    FlagClear(FLAG_SHOWN_BOX_WAS_FULL_MESSAGE);
                VarSet(VAR_PC_BOX_TO_SEND_MON, i);
                return ShouldShowBoxWasFullMessage();
            }
        }
        i++;
        if (i == TOTAL_BOXES_COUNT)
            i = 0;
    } while (i != StorageGetCurrentBox());
    return FALSE;
}

const u16 sPokeCenter1FMaps[] = {
    MAP_VIRIDIAN_CITY_POKEMON_CENTER_1F,
    MAP_PEWTER_CITY_POKEMON_CENTER_1F,
    MAP_CERULEAN_CITY_POKEMON_CENTER_1F,
    MAP_LAVENDER_TOWN_POKEMON_CENTER_1F,
    MAP_VERMILION_CITY_POKEMON_CENTER_1F,
    MAP_CELADON_CITY_POKEMON_CENTER_1F,
    MAP_FUCHSIA_CITY_POKEMON_CENTER_1F,
    MAP_CINNABAR_ISLAND_POKEMON_CENTER_1F,
    MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F,
    MAP_SAFFRON_CITY_POKEMON_CENTER_1F,
    MAP_ROUTE4_POKEMON_CENTER_1F,
    MAP_ROUTE10_POKEMON_CENTER_1F,
    MAP_ONE_ISLAND_POKEMON_CENTER_1F,
    MAP_TWO_ISLAND_POKEMON_CENTER_1F,
    MAP_THREE_ISLAND_POKEMON_CENTER_1F,
    MAP_FOUR_ISLAND_POKEMON_CENTER_1F,
    MAP_FIVE_ISLAND_POKEMON_CENTER_1F,
    MAP_SEVEN_ISLAND_POKEMON_CENTER_1F,
    MAP_SIX_ISLAND_POKEMON_CENTER_1F,
    MAP_UNION_ROOM,
    MAP_UNDEFINED
};

bool8 UsedPokemonCenterWarp(void)
{
    s32 i;
    u16 mapno = (gLastUsedWarp.mapGroup << 8) + gLastUsedWarp.mapNum;
    for (i = 0; sPokeCenter1FMaps[i] != MAP_UNDEFINED; i++)
    {
        if (sPokeCenter1FMaps[i] == mapno)
            return TRUE;
    }
    return FALSE;
}

bool8 BufferTMHMMoveName(void)
{
    // 8004 = item ID
    if (gSpecialVar_0x8004 >= ITEM_TM01 && gSpecialVar_0x8004 <= ITEM_HM08)
    {
        StringCopy(gStringVar1, gMoveNames[ItemIdToBattleMoveId(gSpecialVar_0x8004)]);
        return TRUE;
    }
    else
        return FALSE;
}

void RunMassageCooldownStepCounter(void)
{
    u16 count = VarGet(VAR_MASSAGE_COOLDOWN_STEP_COUNTER);
    if (count < 500)
        VarSet(VAR_MASSAGE_COOLDOWN_STEP_COUNTER, count + 1);
}

void DaisyMassageServices(void)
{
    AdjustFriendship(&gPlayerParty[gSpecialVar_0x8004], FRIENDSHIP_EVENT_MASSAGE);
    VarSet(VAR_MASSAGE_COOLDOWN_STEP_COUNTER, 0);
}

static const u16 sEliteFourLightingPalettes[][16] = {
    INCBIN_U16("graphics/field_specials/unk_83F5F50.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F5F70.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F5F90.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F5FB0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F5FD0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F5FF0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6010.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6030.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6050.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6070.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6090.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F60B0.gbapal")
};

static const u16 sChampionRoomLightingPalettes[][16] = {
    INCBIN_U16("graphics/field_specials/unk_83F60D0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F60F0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6110.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6130.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6150.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6170.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6190.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F61B0.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F61D0.gbapal")
};

static const u8 sEliteFourLightingTimers[] = {
    40,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12,
    12
};

static const u8 sChampionRoomLightingTimers[] = {
    20,
     8,
     8,
     8,
     8,
     8,
     8,
     8
};

void DoPokemonLeagueLightingEffect(void)
{
    u8 taskId = CreateTask(Task_RunPokemonLeagueLightingEffect, 8);
    s16 *data = gTasks[taskId].data;
    if (FlagGet(FLAG_TEMP_3) == TRUE)
    {
        gTasks[taskId].func = Task_CancelPokemonLeagueLightingEffect;
    }
    else
    {
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(POKEMON_LEAGUE_CHAMPIONS_ROOM))
        {
            data[0] = sChampionRoomLightingTimers[0];
            data[2] = 8;
            LoadPalette(sChampionRoomLightingPalettes[0], 0x70, 0x20);
        }
        else
        {
            data[0] = sEliteFourLightingTimers[0];
            data[2] = 11;
            LoadPalette(sEliteFourLightingPalettes[0], 0x70, 0x20);
        }
        data[1] = 0;
        sub_8059948(7, 1);
    }
}

static void Task_RunPokemonLeagueLightingEffect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active
     && FlagGet(FLAG_TEMP_2) != FALSE
     && FlagGet(FLAG_TEMP_5) != TRUE
     && gUnknown_2036E28 != 3
     && --data[0] == 0
    )
    {
        if (++data[1] == data[2])
            data[1] = 0;

        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(POKEMON_LEAGUE_CHAMPIONS_ROOM))
        {
            data[0] = sChampionRoomLightingTimers[data[1]];
            LoadPalette(sChampionRoomLightingPalettes[data[1]], 0x70, 0x20);
        }
        else
        {
            data[0] = sEliteFourLightingTimers[data[1]];
            LoadPalette(sEliteFourLightingPalettes[data[1]], 0x70, 0x20);
        }
        sub_8059948(7, 1);
    }
}

static void Task_CancelPokemonLeagueLightingEffect(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (FlagGet(FLAG_TEMP_4) != FALSE)
    {
        if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(POKEMON_LEAGUE_CHAMPIONS_ROOM) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(POKEMON_LEAGUE_CHAMPIONS_ROOM))
        {
            LoadPalette(sChampionRoomLightingPalettes[8], 0x70, 0x20);
        }
        else
        {
            LoadPalette(sEliteFourLightingPalettes[11], 0x70, 0x20);
        }
        sub_8059948(7, 1);
        if (gPaletteFade.active)
        {
            BlendPalettes(0x00000080, 16, RGB_BLACK);
        }
        DestroyTask(taskId);
    }
}

void StopPokemonLeagueLightingEffectTask(void)
{
    if (FuncIsActiveTask(Task_RunPokemonLeagueLightingEffect) == TRUE)
    {
        DestroyTask(FindTaskIdByFunc(Task_RunPokemonLeagueLightingEffect));
    }
}

//add other gen starers on to this list //vsonic
static const u8 sCapeBrinkCompatibleSpecies[] = {
    SPECIES_VENUSAUR,
    SPECIES_CHARIZARD,
    SPECIES_BLASTOISE
};

//actually just remove list and make 3 arrays like starter selection 
//fire starter water starer grass starter
#define STARTER_ULTIMATE_MOVE_SELECTION
bool8 CapeBrinkGetMoveToTeachLeadPokemon(void)
{
    // Returns:
    //   8005 = Move tutor index
    //   8006 = Num moves known by lead mon
    //   8007 = Index of lead mon
    //   to specialvar = whether a move can be taught in the first place
    u8 tutorMonId = 0;
    u8 numMovesKnown = 0;
    u8 leadMonSlot = GetLeadMonIndex();
    u8 i;
    gSpecialVar_0x8007 = leadMonSlot;
    for (i = 0; i < NELEMS(sCapeBrinkCompatibleSpecies); i++)
    {
        if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_SPECIES2, NULL) == sCapeBrinkCompatibleSpecies[i])
        {
            tutorMonId = i;
            break;
        }
    }
    if (i == NELEMS(sCapeBrinkCompatibleSpecies) || GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_FRIENDSHIP) != 255)
        return FALSE;
    if (tutorMonId == 0)
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_FRENZY_PLANT]);
        gSpecialVar_0x8005 = MOVETUTOR_FRENZY_PLANT;
        if (FlagGet(FLAG_TUTOR_FRENZY_PLANT) == TRUE)
            return FALSE;
    }
    else if (tutorMonId == 1)
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_BLAST_BURN]);
        gSpecialVar_0x8005 = MOVETUTOR_BLAST_BURN;
        if (FlagGet(FLAG_TUTOR_BLAST_BURN) == TRUE)
            return FALSE;
    }
    else
    {
        StringCopy(gStringVar2, gMoveNames[MOVE_HYDRO_CANNON]);
        gSpecialVar_0x8005 = MOVETUTOR_HYDRO_CANNON;
        if (FlagGet(FLAG_TUTOR_HYDRO_CANNON) == TRUE)
            return FALSE;
    }
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE1) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE2) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE3) != MOVE_NONE)
        numMovesKnown++;
    if (GetMonData(&gPlayerParty[leadMonSlot], MON_DATA_MOVE4) != MOVE_NONE)
        numMovesKnown++;
    gSpecialVar_0x8006 = numMovesKnown;
    return TRUE;
}

bool8 HasLearnedAllMovesFromCapeBrinkTutor(void)
{
    // 8005 is set by CapeBrinkGetMoveToTeachLeadPokemon
    u8 r4 = 0;
    if (gSpecialVar_0x8005 == MOVETUTOR_FRENZY_PLANT)
        FlagSet(FLAG_TUTOR_FRENZY_PLANT);
    else if (gSpecialVar_0x8005 == MOVETUTOR_BLAST_BURN)
        FlagSet(FLAG_TUTOR_BLAST_BURN);
    else
        FlagSet(FLAG_TUTOR_HYDRO_CANNON);
    if (FlagGet(FLAG_TUTOR_FRENZY_PLANT) == TRUE)
        r4++;
    if (FlagGet(FLAG_TUTOR_BLAST_BURN) == TRUE)
        r4++;
    if (FlagGet(FLAG_TUTOR_HYDRO_CANNON) == TRUE)
        r4++;
    if (r4 == 3)
        return TRUE;
    else
        return FALSE;
}

bool8 CutMoveRuinValleyCheck(void)
{
    if (FlagGet(FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE) != TRUE
     && gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(SIX_ISLAND_RUIN_VALLEY)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(SIX_ISLAND_RUIN_VALLEY)
     && gSaveBlock1Ptr->pos.x == 24
     && gSaveBlock1Ptr->pos.y == 25
     && GetPlayerFacingDirection() == DIR_NORTH
    )
        return TRUE;
    else
        return FALSE;
}

void CutMoveOpenDottedHoleDoor(void)
{
    MapGridSetMetatileIdAt(31, 31, METATILE_SeviiIslands67_DottedHoleDoor_Open);
    DrawWholeMapView();
    PlaySE(SE_BANG);
    FlagSet(FLAG_USED_CUT_ON_RUIN_VALLEY_BRAILLE);
    UnlockPlayerFieldControls();
}

static const u16 sDeoxysObjectPals[][16] = {
    INCBIN_U16("graphics/field_specials/unk_83F6206.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6226.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6246.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6266.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6286.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F62A6.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F62C6.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F62E6.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6306.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6326.gbapal"),
    INCBIN_U16("graphics/field_specials/unk_83F6346.gbapal")
};

static const u8 sDeoxysCoords[][2] = {
    {15, 12},
    {11, 14},
    {15,  8},
    {19, 14},
    {12, 11},
    {18, 11},
    {15, 14},
    {11, 14},
    {19, 14},
    {15, 15},
    {15, 10}
};

static const u8 sDeoxysStepCaps[] = {
    4,
    8,
    8,
    8,
    4,
    4,
    4,
    6,
    3,
    3
};

void DoDeoxysTriangleInteraction(void)
{
    CreateTask(Task_DoDeoxysTriangleInteraction, 8);
}

static void Task_DoDeoxysTriangleInteraction(u8 taskId)
{
    u16 r5;
    u16 r6;
    if (FlagGet(FLAG_SYS_DEOXYS_AWAKENED) == TRUE)
    {
        gSpecialVar_Result = 3;
        EnableBothScriptContexts();
        DestroyTask(taskId);
    }
    else
    {
        r5 = VarGet(VAR_DEOXYS_INTERACTION_NUM);
        r6 = VarGet(VAR_DEOXYS_INTERACTION_STEP_COUNTER);
        VarSet(VAR_DEOXYS_INTERACTION_STEP_COUNTER, 0);
        if (r5 != 0 && sDeoxysStepCaps[r5 - 1] < r6)
        {
            MoveDeoxysObject(0);
            VarSet(VAR_DEOXYS_INTERACTION_NUM, 0);
            gSpecialVar_Result = 0;
            DestroyTask(taskId);
        }
        else if (r5 == 10)
        {
            FlagSet(FLAG_SYS_DEOXYS_AWAKENED);
            gSpecialVar_Result = 2;
            EnableBothScriptContexts();
            DestroyTask(taskId);
        }
        else
        {
            r5++;
            MoveDeoxysObject(r5);
            VarSet(VAR_DEOXYS_INTERACTION_NUM, r5);
            gSpecialVar_Result = 1;
            DestroyTask(taskId);
        }
    }
}

static void MoveDeoxysObject(u8 num)
{
    u8 mapObjId;
    LoadPalette(sDeoxysObjectPals[num], 0x1A0, 0x08);
    sub_8083598(10);
    TryGetObjectEventIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &mapObjId);
    if (num == 0)
        PlaySE(SE_M_CONFUSE_RAY);
    else
        PlaySE(SE_DEOXYS_MOVE);
    CreateTask(Task_WaitDeoxysFieldEffect, 8);
    gFieldEffectArguments[0] = 1;
    gFieldEffectArguments[1] = 56;
    gFieldEffectArguments[2] = 2;
    gFieldEffectArguments[3] = sDeoxysCoords[num][0];
    gFieldEffectArguments[4] = sDeoxysCoords[num][1];
    if (num == 0)
        gFieldEffectArguments[5] = 60;
    else
        gFieldEffectArguments[5] = 5;
    FieldEffectStart(FLDEFF_MOVE_DEOXYS_ROCK);
    Overworld_SetMapObjTemplateCoords(1, sDeoxysCoords[num][0], sDeoxysCoords[num][1]);
}

static void Task_WaitDeoxysFieldEffect(u8 taskId)
{
    if (!FieldEffectActiveListContains(FLDEFF_MOVE_DEOXYS_ROCK))
    {
        EnableBothScriptContexts();
        DestroyTask(taskId);
    }
}

void IncrementBirthIslandRockStepCount(void)
{
    u16 count = VarGet(VAR_DEOXYS_INTERACTION_STEP_COUNTER);
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(BIRTH_ISLAND_EXTERIOR) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(BIRTH_ISLAND_EXTERIOR))
    {
        count++;
        if (count > 99)
            VarSet(VAR_DEOXYS_INTERACTION_STEP_COUNTER, 0);
        else
            VarSet(VAR_DEOXYS_INTERACTION_STEP_COUNTER, count);
    }
}

void SetDeoxysTrianglePalette(void)
{
    u8 num = VarGet(VAR_DEOXYS_INTERACTION_NUM);
    LoadPalette(sDeoxysObjectPals[num], 0x1A0, 0x08);
    sub_8083598(10);
}

bool8 IsBadEggInParty(void)
{
    u8 partyCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < partyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SANITY_IS_BAD_EGG) == TRUE)
            return TRUE;
    }
    return FALSE;
}

bool8 IsPlayerNotInTrainerTowerLobby(void)
{
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRAINER_TOWER_LOBBY) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(TRAINER_TOWER_LOBBY))
        return FALSE;
    else
        return TRUE;
}

void BrailleCursorToggle(void)
{
    // 8004 = x - 27
    // 8005 = y
    // 8006 = action (0 = create, 1 = delete)
    u16 x;
    if (gQuestLogState != QL_STATE_PLAYBACK)
    {
        x = gSpecialVar_0x8004 + 27;
        if (gSpecialVar_0x8006 == 0)
            sBrailleTextCursorSpriteID = CreateTextCursorSpriteForOakSpeech(0, x, gSpecialVar_0x8005, 0, 0);
        else
            sub_8006398(sBrailleTextCursorSpriteID);
    }
}

bool8 PlayerPartyContainsSpeciesWithPlayerID(void)
{
    // 8004 = species
    u8 playerCount = CalculatePlayerPartyCount();
    u8 i;
    for (i = 0; i < playerCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2, NULL) == gSpecialVar_0x8004 
            && GetPlayerTrainerId() == GetMonData(&gPlayerParty[i], MON_DATA_OT_ID, NULL))
            return TRUE;
    }
    return FALSE;
}

/*
 * Determines which of Lorelei's doll collection to show
 * based on how many times you've entered the Hall of Fame.
 */
void UpdateLoreleiDollCollection(void)
{
    u32 numHofClears = GetGameStat(GAME_STAT_ENTERED_HOF);
    if (numHofClears >= 25)
    {
        FlagClear(FLAG_HIDE_LORELEI_HOUSE_MEOWTH_DOLL);
        if (numHofClears >= 50)
            FlagClear(FLAG_HIDE_LORELEI_HOUSE_CHANSEY_DOLL);
        if (numHofClears >= 75)
            FlagClear(FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_F_DOLL);
        if (numHofClears >= 100)
            FlagClear(FLAG_HIDE_LORELEI_HOUSE_JIGGLYPUFF_DOLL);
        if (numHofClears >= 125)
            FlagClear(FLAG_HIDE_LORELEIS_HOUSE_NIDORAN_M_DOLL);
        if (numHofClears >= 150)
            FlagClear(FLAG_HIDE_LORELEIS_HOUSE_FEAROW_DOLL);
        if (numHofClears >= 175)
            FlagClear(FLAG_HIDE_LORELEIS_HOUSE_PIDGEOT_DOLL);
        if (numHofClears >= 200)
            FlagClear(FLAG_HIDE_LORELEIS_HOUSE_LAPRAS_DOLL);
    }
}

void LoopWingFlapSound(void)
{
    // 8004 = Num flaps
    // 8005 = Frame delay between flaps
    CreateTask(Task_WingFlapSound, 8);
    PlaySE(SE_M_WING_ATTACK);
}

static void Task_WingFlapSound(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    data[1]++;
    if (data[1] == gSpecialVar_0x8005)
    {
        data[0]++;
        data[1] = 0;
        PlaySE(SE_M_WING_ATTACK);
    }
    if (data[0] == gSpecialVar_0x8004 - 1)
        DestroyTask(taskId);
}
