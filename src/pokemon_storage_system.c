#include "global.h"
#include "gflib.h"
#include "pokemon_storage_system_internal.h"

static void ApplyOakRanchExperience(struct Pokemon *mon); //ohop make work



void BackupPokemonStorage(struct PokemonStorage * dest)
{
    *dest = *gPokemonStoragePtr;
}

void RestorePokemonStorage(struct PokemonStorage * src)
{
    *gPokemonStoragePtr = *src;
}

// Functions here are general utility functions.
u8 StorageGetCurrentBox(void)
{
    return gPokemonStoragePtr->currentBox;
}

void SetCurrentBox(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        gPokemonStoragePtr->currentBox = boxId;
}

u32 GetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request);
    else
        return 0;
}

void SetBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, const void *value)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        SetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request, value);
}

u32 GetCurrentBoxMonData(u8 boxPosition, s32 request)
{
    return GetBoxMonDataAt(gPokemonStoragePtr->currentBox, boxPosition, request);
}

void SetCurrentBoxMonData(u8 boxPosition, s32 request, const void *value)
{
    SetBoxMonDataAt(gPokemonStoragePtr->currentBox, boxPosition, request, value);
}

void GetBoxMonNickAt(u8 boxId, u8 boxPosition, u8 *dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_NICKNAME, dst);
    else
        *dst = EOS;
}

void SetBoxMonNickAt(u8 boxId, u8 boxPosition, const u8 *nick)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        SetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_NICKNAME, nick);
}

u32 GetAndCopyBoxMonDataAt(u8 boxId, u8 boxPosition, s32 request, void *dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], request, dst);
    else
        return 0;
}

void SetBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon * src)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        gPokemonStoragePtr->boxes[boxId][boxPosition] = *src;
}

void CopyBoxMonAt(u8 boxId, u8 boxPosition, struct BoxPokemon * dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        *dst = gPokemonStoragePtr->boxes[boxId][boxPosition];
}

void CreateBoxMonAt(u8 boxId, u8 boxPosition, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 personality, u8 otIDType, u32 otID)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
    {
        CreateBoxMon(&gPokemonStoragePtr->boxes[boxId][boxPosition],
                     species,
                     level,
                     fixedIV,
                     hasFixedPersonality, personality,
                     otIDType, otID);
    }
}

void ZeroBoxMonAt(u8 boxId, u8 boxPosition)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        ZeroBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition]);
}

#define BOX_EXP_GAIN
void BoxMonAtGainExp(struct BoxPokemon * mon)
{
    u32 experience;
    //struct BoxPokemon *mon = &gPokemonStoragePtr->boxes[boxId][boxPosition];
    struct Pokemon dst;
    BoxMonToMon(mon, &dst);

    //if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT) //think replace this with speecies check and not egg
    //{
        if (GetMonData(&dst, MON_DATA_LEVEL) != MAX_LEVEL) //realize getmondata & getboxmondata have different fields...
        {
            if (GetMonData(&dst, MON_DATA_LEVEL) < 10) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                experience = GetBoxMonData(mon, MON_DATA_EXP) + (gSaveBlock1Ptr->oakRanchStepCounter); //nvm didn't work for some reason because didn't use constant
                SetBoxMonData(mon, MON_DATA_EXP, &experience);  //replaced setup, now use 17 value wrap around var before counter increments, will need rebalance here
                ApplyOakRanchExperience(&dst);
            }
            else if (GetMonData(&dst, MON_DATA_LEVEL) <= 25) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                experience = GetMonData(mon, MON_DATA_EXP) + (gSaveBlock1Ptr->oakRanchStepCounter * 5);
                SetBoxMonData(mon, MON_DATA_EXP, &experience);
                ApplyOakRanchExperience(&dst);
            }
            else if (GetMonData(&dst, MON_DATA_LEVEL) <= 40) //test see if change works in sub of a wrap around, should make increase 1 for every 30 steps
            {
                experience = GetBoxMonData(mon, MON_DATA_EXP) + (gSaveBlock1Ptr->oakRanchStepCounter * gSaveBlock1Ptr->oakRanchStepCounter);
                SetBoxMonData(mon, MON_DATA_EXP, &experience);
                ApplyOakRanchExperience(&dst);
            }
            else
            {
                experience = GetBoxMonData(mon, MON_DATA_EXP) + ( 2 * (gSaveBlock1Ptr->oakRanchStepCounter * gSaveBlock1Ptr->oakRanchStepCounter));
                SetBoxMonData(mon, MON_DATA_EXP, &experience);
                ApplyOakRanchExperience(&dst); //using this is irrelvant for some reason not setting exp evenly to each slot
            } //but it does or seemingly does if I  use struc Pokemon *mon; ?  but it ignores rule and sets to lvl 100 with FAR more lag for unkown reasons
        }        


    //}
        
}

static void ApplyOakRanchExperience(struct Pokemon *mon)
{

    TryIncrementMonLevel(mon); //increment level if less than max level, commented out move learn
    
    // Re-calculate the mons stats at its new level.
    CalculateMonStats(mon);
}

void BoxMonAtToMon(u8 boxId, u8 boxPosition, struct Pokemon * dst)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        BoxMonToMon(&gPokemonStoragePtr->boxes[boxId][boxPosition], dst);
}

struct BoxPokemon * GetBoxedMonPtr(u8 boxId, u8 boxPosition)
{
    if (boxId < TOTAL_BOXES_COUNT && boxPosition < IN_BOX_COUNT)
        return &gPokemonStoragePtr->boxes[boxId][boxPosition];
    else
        return NULL;
}

u8 *GetBoxNamePtr(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        return gPokemonStoragePtr->boxNames[boxId];
    else
        return NULL;
}

u8 GetBoxWallpaper(u8 boxId)
{
    if (boxId < TOTAL_BOXES_COUNT)
        return gPokemonStoragePtr->boxWallpapers[boxId];
    else
        return 0;
}

void SetBoxWallpaper(u8 boxId, u8 wallpaperId)
{
    if (boxId < TOTAL_BOXES_COUNT && wallpaperId < WALLPAPER_COUNT)
        gPokemonStoragePtr->boxWallpapers[boxId] = wallpaperId;
}

s16 SeekToNextMonInBox(struct BoxPokemon * boxMons, s8 curIndex, u8 maxIndex, u8 flags)
{
    // flags:
    // bit 0: Allow eggs
    // bit 1: Search backwards
    s16 i;
    s16 adder;
    if (flags == 0 || flags == 1)
        adder = 1;
    else
        adder = -1;

    if (flags == 1 || flags == 3)
    {
        for (i = curIndex + adder; i >= 0 && i <= maxIndex; i += adder)
        {
            if (GetBoxMonData(&boxMons[i], MON_DATA_SPECIES) != SPECIES_NONE)
                return i;
        }
    }
    else
    {
        for (i = curIndex + adder; i >= 0 && i <= maxIndex; i += adder)
        {
            if (GetBoxMonData(&boxMons[i], MON_DATA_SPECIES) != SPECIES_NONE
                && !GetBoxMonData(&boxMons[i], MON_DATA_IS_EGG))
                return i;
        }
    }

    return -1;
}
