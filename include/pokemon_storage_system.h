#ifndef GUARD_POKEMON_STORAGE_SYSTEM_H
#define GUARD_POKEMON_STORAGE_SYSTEM_H

#include "global.h"

#define TOTAL_BOXES_COUNT       14 // so if I'm making all pokemon/forms availale I'll need way more than 14 slots, I'm prob need to double or triple that.
#define IN_BOX_COUNT            30 //that requires save block expansion, but even after that, managing so many boxes would still be too tedious.

// I think if I can get that cfru thing, where you carry a secondary storage on you that may solve it, you can keep the important pokemon on you, and just swap from the pc.
// allowing me to cut down on the needed number of boxes.

//but I'd need to set the thing able to carry about 200 or 300 pokemon and able to register it, to change the after/catch action,
//so when it's registered caught pokemon go directly to this closer storage instead of the pc. 

//that way pressing the register button would swap the default location new pokemon go, so if you have a pokemon you want to use, right away, just hit register before you catch.
//this still requiers save expansion, but its just a more efficient interface.
enum
{
    WALLPAPER_FOREST,
    WALLPAPER_CITY,
    WALLPAPER_DESERT,
    WALLPAPER_SAVANNA,
    WALLPAPER_CRAG,
    WALLPAPER_VOLCANO,
    WALLPAPER_SNOW,
    WALLPAPER_CAVE,
    WALLPAPER_BEACH,
    WALLPAPER_SEAFLOOR,
    WALLPAPER_RIVER,
    WALLPAPER_SKY,
    WALLPAPER_POLKADOT,
    WALLPAPER_POKECENTER,
    WALLPAPER_MACHINE,
    WALLPAPER_PLAIN,
    WALLPAPER_COUNT
};

u8 *GetBoxNamePtr(u8 boxNumber);
struct BoxPokemon *GetBoxedMonPtr(u8 boxId, u8 monPosition);
void SetBoxMonNickAt(u8 boxId, u8 monPosition, const u8 *newNick);
s16 CompactPartySlots(void);
u32 GetBoxMonDataAt(u8 boxId, u8 monPosition, s32 request);
void ZeroBoxMonAt(u8 boxId, u8 monPosition);
void Cb2_ReturnToPSS(void);
void ResetPokemonStorageSystem(void);
u8 StorageGetCurrentBox(void);
void DrawTextWindowAndBufferTiles(const u8 *string, void *dst, u8 zero1, u8 zero2, u8 *buffer, s32 bytesToBuffer);

void UpdatePokemonStorageSystemMonExp(void); //boxx exp gain setup - main function call
void BoxMonAtGainExp(u8 boxId, u8 boxPosition); //box exp gaain setup  //exp setting logic

u8 CheckIfPcEmpty(void); //check if there is a mon in pc, for resetting pc exp gain counter

#endif // GUARD_POKEMON_STORAGE_SYSTEM_H
