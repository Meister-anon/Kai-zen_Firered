#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "field_message_box.h"

extern const u8 PokedexRating_Text_LessThan10[];
extern const u8 PokedexRating_Text_LessThan20[];
extern const u8 PokedexRating_Text_LessThan30[];
extern const u8 PokedexRating_Text_LessThan40[];
extern const u8 PokedexRating_Text_LessThan50[];
extern const u8 PokedexRating_Text_LessThan60[];
extern const u8 PokedexRating_Text_LessThan70[];
extern const u8 PokedexRating_Text_LessThan80[];
extern const u8 PokedexRating_Text_LessThan90[];
extern const u8 PokedexRating_Text_LessThan100[];
extern const u8 PokedexRating_Text_LessThan110[];
extern const u8 PokedexRating_Text_LessThan120[];
extern const u8 PokedexRating_Text_LessThan130[];
extern const u8 PokedexRating_Text_LessThan140[];
extern const u8 PokedexRating_Text_LessThan150[];
extern const u8 PokedexRating_Text_Complete[];

u16 GetPokedexCount(void)
{
    if (gSpecialVar_0x8004 == 0) //8004 is somehow apparently supposed to hold result of IsNationalPokedexEnabled func
    {
        gSpecialVar_0x8005 = GetKantoPokedexCount(0); //0 = seen
        gSpecialVar_0x8006 = GetKantoPokedexCount(1); //1 = caugh
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(0); //what could do is change else to if, and make these use var 8007 and 8008
        gSpecialVar_0x8006 = GetNationalPokedexCount(1); //ok think 8004 is VAR_RESULT, and this special populates var result w effect of function when called

        //gSpecialVar_0x8007 = GetKantoPokedexCount(0); //0 = seen    //changed since would affect aides scripts, not presently used 
        //gSpecialVar_0x8008 = GetKantoPokedexCount(1); //1 = caugh      //but want to use for dex rating,change to read both nat and local dex
                                //since supposed to get some reward for completing each, looked further into seems script may already work how I want for rating?
    }   //oh that's great it already works that way so I don't need to change anything, and the aides will pick up my nat dex count so everything is perfect
    return IsNationalPokedexEnabled();
}

static const u8 *GetProfOaksRatingMessageByCount(u16 count) //for this want to change to, say how many native mon you've caught and how many total mon you've caught
{
    gSpecialVar_Result = FALSE;

    if (count < 10)
        return PokedexRating_Text_LessThan10;

    if (count < 20)
        return PokedexRating_Text_LessThan20;

    if (count < 30)
        return PokedexRating_Text_LessThan30;

    if (count < 40)
        return PokedexRating_Text_LessThan40;

    if (count < 50)
        return PokedexRating_Text_LessThan50;

    if (count < 60)
        return PokedexRating_Text_LessThan60;

    if (count < 70)
        return PokedexRating_Text_LessThan70;

    if (count < 80)
        return PokedexRating_Text_LessThan80;

    if (count < 90)
        return PokedexRating_Text_LessThan90;

    if (count < 100)
        return PokedexRating_Text_LessThan100;

    if (count < 110)
        return PokedexRating_Text_LessThan110;

    if (count < 120)
        return PokedexRating_Text_LessThan120;

    if (count < 130)
        return PokedexRating_Text_LessThan130;

    if (count < 140)
        return PokedexRating_Text_LessThan140;

    if (count < 150)
        return PokedexRating_Text_LessThan150;

    if (count == 150)
    {
        // Mew doesn't count for completing the pokedex
        if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_MEW), 1))
            return PokedexRating_Text_LessThan150;

        gSpecialVar_Result = TRUE;
        return PokedexRating_Text_Complete;
    }

    if (count == 151)
    {
        gSpecialVar_Result = TRUE;
        return PokedexRating_Text_Complete;
    }

    return PokedexRating_Text_LessThan10;
}

void GetProfOaksRatingMessage(void)
{
    ShowFieldMessage(GetProfOaksRatingMessageByCount(gSpecialVar_0x8004));
}
