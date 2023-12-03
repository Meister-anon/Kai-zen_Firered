#include "global.h"
#include "gflib.h"
#include "strings.h"
#include "constants/abilities.h"
#include "task.h"
#include "field_message_box.h"
#include "script.h"
#include "event_data.h"
#include "fldeff.h"
#include "party_menu.h"
#include "field_poison.h"
#include "constants/form_change_types.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "constants/items.h"

static bool32 IsMonValidSpecies(struct Pokemon *pokemon)
{
    u16 species = GetMonData(pokemon, MON_DATA_SPECIES2);
    if (species == SPECIES_NONE || species == SPECIES_EGG)
        return FALSE;
    return TRUE;
}

static bool32 AllMonsFainted(void)
{
    int i;

    struct Pokemon *pokemon = gPlayerParty;
    for (i = 0; i < PARTY_SIZE; i++, pokemon++)
        if (IsMonValidSpecies(pokemon) && GetMonData(pokemon, MON_DATA_HP))
            return FALSE;
    return TRUE;
}

static void FaintFromFieldPoison(u8 partyIdx)
{
    struct Pokemon *pokemon = gPlayerParty + partyIdx;
    u32 status = STATUS1_NONE;
    AdjustFriendship(pokemon, FRIENDSHIP_EVENT_FAINT_OUTSIDE_BATTLE);
    SetMonData(pokemon, MON_DATA_STATUS, &status);
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    StringGet_Nickname(gStringVar1);
}

static bool32 MonFaintedFromPoison(u8 partyIdx)
{
    struct Pokemon *pokemon = gPlayerParty + partyIdx;
    if (IsMonValidSpecies(pokemon) && !GetMonData(pokemon, MON_DATA_HP) && GetAilmentFromStatus(GetMonData(pokemon, MON_DATA_STATUS)) == AILMENT_PSN)
        return TRUE; //if species, hp == 0, and status is poisoned
    return FALSE;
}

#define tState   data[0]
#define tPartyId data[1]

static void Task_TryFieldPoisonWhiteOut(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (tState)
    {
    case 0:
        for (; tPartyId < PARTY_SIZE; tPartyId++)
        {
            if (MonFaintedFromPoison(tPartyId))
            {
                FaintFromFieldPoison(tPartyId);
                ShowFieldMessage(gText_PkmnFainted3);
                data[0]++;
                return;
            }
        }
        tState = 2;
        break;
    case 1:
        if (IsFieldMessageBoxHidden())
            tState--;
        break;
    case 2:
        if (AllMonsFainted())
            gSpecialVar_Result = TRUE;
        else
            gSpecialVar_Result = FALSE;
        EnableBothScriptContexts();
        DestroyTask(taskId);
        break;
    }
}

void TryFieldPoisonWhiteOut(void)
{
    CreateTask(Task_TryFieldPoisonWhiteOut, 80);
    ScriptContext1_Stop();
}

static bool32 TryActivateFieldPoisonHeal(struct Pokemon *mon) //putting inside the loop so doesn't need a loop...I think
{
    
    if (GetMonData(mon, MON_DATA_SANITY_HAS_SPECIES) && GetMonAbility(mon) == ABILITY_POISON_HEAL) //think can just use pokemon constant, as its already a pointer, so shouldn't need ampersand
    {
        if (GetAilmentFromStatus(GetMonData(mon, MON_DATA_STATUS)) == AILMENT_PSN)
            return TRUE;
        else if (IsMonType(mon, TYPE_POISON) && (GetMonData(mon, MON_DATA_HELD_ITEM) == ITEM_BLACK_SLUDGE)) //also work for poison_orb when setup
            return TRUE;
        else
            return FALSE;
    }
    else
        return FALSE;
    

}

s32 DoPoisonFieldEffect(void) //now heals poison heal pokemon outside of battle
{
    int i;
    u32 hp;
    //u32 max;
    
    struct Pokemon *pokemon = gPlayerParty;
    u32 numPoisoned = 0;
    u32 numFainted = 0;
    for (i = 0; i < PARTY_SIZE; i++)  //fix found by shinny from pret his code solution
    {
        hp = GetMonData(pokemon, MON_DATA_HP);
        //if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES) && GetAilmentFromStatus(GetMonData(pokemon, MON_DATA_STATUS)) == AILMENT_PSN)//replace this
        if (TryActivateFieldPoisonHeal(pokemon))
        {

            if (hp < GetMonData(pokemon, MON_DATA_MAX_HP))
                hp++;
            //if (GetMonAbility(&gPlayerParty[i]) == ABILITY_POISON_HEAL)//replace this
        }
        else if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES) && GetAilmentFromStatus(GetMonData(pokemon, MON_DATA_STATUS)) == AILMENT_PSN) //normal poison checks
        {
            if (hp == 0 || --hp == 0)
                numFainted++;
            numPoisoned++;
        }
        SetMonData(pokemon, MON_DATA_HP, &hp);        
        pokemon++;
    }
    if (numFainted || numPoisoned) //if not 0
        FldEffPoison_Start();
    if (numFainted)
        return FLDPSN_FNT;
    if (numPoisoned)
        return FLDPSN_PSN;
    return FLDPSN_NONE;
}
