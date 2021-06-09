#include "global.h"
#include "item.h"
#include "text.h"
#include "util.h"
#include "link.h"
#include "malloc.h"
#include "berry.h"
#include "random.h"
#include "pokemon.h"
#include "string_util.h"
#include "field_weather.h"
#include "event_data.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_scripts.h"
#include "battle_message.h"
#include "constants/battle_anim.h"
#include "battle_controllers.h"
#include "battle_string_ids.h"
#include "battle_ai_script_commands.h"
#include "constants/battle.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/weather.h"
#include "constants/abilities.h"
#include "constants/pokemon.h"
#include "constants/hold_effects.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"

static const u16 sSoundMovesTable[] =
{
    MOVE_GROWL, MOVE_ROAR, MOVE_SING, MOVE_SUPERSONIC, MOVE_SCREECH, MOVE_SNORE,
    MOVE_UPROAR, MOVE_METAL_SOUND, MOVE_GRASS_WHISTLE, MOVE_HYPER_VOICE, 0xFFFF
};

u8 GetBattlerForBattleScript(u8 caseId)
{
    u32 ret = 0;

    switch (caseId)
    {
    case BS_TARGET:
        ret = gBattlerTarget;
        break;
    case BS_ATTACKER:
        ret = gBattlerAttacker;
        break;
    case BS_EFFECT_BATTLER:
        ret = gEffectBattler;
        break;
    case BS_BATTLER_0:
        ret = 0;
        break;
    case BS_SCRIPTING:
        ret = gBattleScripting.battler;
        break;
    case BS_FAINTED:
        ret = gBattlerFainted;
        break;
    case 5:
        ret = gBattlerFainted;
        break;
    case BS_PLAYER1:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        break;
    case BS_OPPONENT1:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        break;
    case 4:
    case 6:
    case 8:
    case 9:
	case BS_PLAYER2:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        break;
    case BS_OPPONENT2:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        break;
    case BS_ABILITY_BATTLER:
        ret = gBattlerAbility;
        break;
    }
    return ret;
}

void PressurePPLose(u8 target, u8 attacker, u16 move)
{
    s32 i;

    if (gBattleMons[target].ability == ABILITY_PRESSURE)
    {
        for (i = 0; i < MAX_MON_MOVES && gBattleMons[attacker].moves[i] != move; ++i);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[attacker].pp[i])
                --gBattleMons[attacker].pp[i]; //ok since the minus arent directly on the i, I don't think its what they are augmenting here
            if (!(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED) // the i is just being used to cover move position (i.e 0-3) while the minus is on the pp here telling it remove 1.
             && !(gDisableStructs[attacker].mimickedMoves & gBitTable[i]))
            {
                gActiveBattler = attacker;
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + i, 0, 1, &gBattleMons[gActiveBattler].pp[i]);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
    }

    else if (gBattleMons[target].ability == ABILITY_HI_PRESSURE) //need to understand what "i" is doing before I can correct this
    {
        for (i = 0; i < MAX_MON_MOVES && gBattleMons[attacker].moves[i] != move; ++i); // this is apparently a C loop, incrementing until reach limit, i.e max mon moves (4)
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[attacker].pp[i])
                gBattleMons[attacker].pp[i] = (gBattleMons[attacker].pp[i] - 2); // hope that'll do it
            if (!(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED)
                && !(gDisableStructs[attacker].mimickedMoves & gBitTable[i]))
            {
                gActiveBattler = attacker;
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + i, 0, 1, &gBattleMons[gActiveBattler].pp[i]);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
    } //did the same as below, made a separate instance for Hi_Pressure with extra plus & minus
} // ok from buffel saft I learned the ++ trick can't go higher than 1.

void PressurePPLoseOnUsingImprison(u8 attacker)
{
    s32 i, j;
    s32 imprisonPos = 4;
    u8 atkSide = GetBattlerSide(attacker);

    for (i = 0; i < gBattlersCount; ++i)
    {
        if (atkSide != GetBattlerSide(i) && gBattleMons[i].ability == ABILITY_PRESSURE)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_IMPRISON; ++j);
            if (j != MAX_MON_MOVES)
            {
                imprisonPos = j;
                if (gBattleMons[attacker].pp[j])
                    --gBattleMons[attacker].pp[j];
            }
        }
        if (atkSide != GetBattlerSide(i) && gBattleMons[i].ability == ABILITY_HI_PRESSURE)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_IMPRISON; ++j);
            if (j != MAX_MON_MOVES)
            {
                imprisonPos = j;
                if (gBattleMons[attacker].pp[j])
                    gBattleMons[attacker].pp[j] = (gBattleMons[attacker].pp[j] - 2); //unsure same problemas aboev; 
            } 
        }
    }
    if (imprisonPos != 4
     && !(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED)
     && !(gDisableStructs[attacker].mimickedMoves & gBitTable[imprisonPos]))
    {
        gActiveBattler = attacker;
        BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + imprisonPos, 0, 1, &gBattleMons[gActiveBattler].pp[imprisonPos]);
        MarkBattlerForControllerExec(gActiveBattler);
    }
}

void PressurePPLoseOnUsingPerishSong(u8 attacker)
{
    s32 i, j;
    s32 perishSongPos = 4;

    for (i = 0; i < gBattlersCount; ++i)
    {
        if (gBattleMons[i].ability == ABILITY_PRESSURE && i != attacker)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_PERISH_SONG; ++j);
            if (j != MAX_MON_MOVES)
            {
                perishSongPos = j;
                if (gBattleMons[attacker].pp[j])
                    --gBattleMons[attacker].pp[j];
            }
        }
        if (gBattleMons[i].ability == ABILITY_HI_PRESSURE && i != attacker)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_PERISH_SONG; ++j);
            if (j != MAX_MON_MOVES)
            {
                perishSongPos = j;
                if (gBattleMons[attacker].pp[j])
                    gBattleMons[attacker].pp[j] = (gBattleMons[attacker].pp[j] - 2); //need to test same as above
            }
        }
    }
    if (perishSongPos != MAX_MON_MOVES
     && !(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED)
     && !(gDisableStructs[attacker].mimickedMoves & gBitTable[perishSongPos]))
    {
        gActiveBattler = attacker;
        BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + perishSongPos, 0, 1, &gBattleMons[gActiveBattler].pp[perishSongPos]);
        MarkBattlerForControllerExec(gActiveBattler);
    }
}

void MarkAllBattlersForControllerExec(void)
{
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        for (i = 0; i < gBattlersCount; ++i)
            gBattleControllerExecFlags |= gBitTable[i] << 0x1C;
    else
        for (i = 0; i < gBattlersCount; ++i)
            gBattleControllerExecFlags |= gBitTable[i];
}

void MarkBattlerForControllerExec(u8 battlerId)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        gBattleControllerExecFlags |= gBitTable[battlerId] << 0x1C;
    else
        gBattleControllerExecFlags |= gBitTable[battlerId];
}

void sub_8017298(u8 arg0)
{
    s32 i;

    for (i = 0; i < GetLinkPlayerCount(); ++i)
        gBattleControllerExecFlags |= gBitTable[arg0] << (i << 2);
    gBattleControllerExecFlags &= ~(0x10000000 << arg0);
}

static const u8 sAbilitiesAffectedByMoldBreaker[] =
{
    [ABILITY_BATTLE_ARMOR] = 1,
    [ABILITY_CLEAR_BODY] = 1,
    [ABILITY_DAMP] = 1,
    [ABILITY_DRY_SKIN] = 1,
    [ABILITY_FILTER] = 1,
    [ABILITY_FLASH_FIRE] = 1,
    [ABILITY_FLOWER_GIFT] = 1,
    [ABILITY_HEATPROOF] = 1,
    [ABILITY_HYPER_CUTTER] = 1,
    [ABILITY_IMMUNITY] = 1,
    [ABILITY_INNER_FOCUS] = 1,
    [ABILITY_INSOMNIA] = 1,
    [ABILITY_KEEN_EYE] = 1,
    [ABILITY_LEAF_GUARD] = 1,
    [ABILITY_LEVITATE] = 1,
    [ABILITY_LIGHTNING_ROD] = 1,
    [ABILITY_LIMBER] = 1,
    [ABILITY_MAGMA_ARMOR] = 1,
    [ABILITY_MARVEL_SCALE] = 1,
    [ABILITY_MOTOR_DRIVE] = 1,
    [ABILITY_OBLIVIOUS] = 1,
    [ABILITY_OWN_TEMPO] = 1,
    [ABILITY_SAND_VEIL] = 1,
    [ABILITY_SHELL_ARMOR] = 1,
    [ABILITY_SHIELD_DUST] = 1,
    [ABILITY_SIMPLE] = 1,
    [ABILITY_SNOW_CLOAK] = 1,
    [ABILITY_SOLID_ROCK] = 1,
    [ABILITY_SOUNDPROOF] = 1,
    [ABILITY_STICKY_HOLD] = 1,
    [ABILITY_STORM_DRAIN] = 1,
    [ABILITY_STURDY] = 1,
    [ABILITY_SUCTION_CUPS] = 1,
    [ABILITY_TANGLED_FEET] = 1,
    [ABILITY_THICK_FAT] = 1,
    [ABILITY_UNAWARE] = 1,
    [ABILITY_VITAL_SPIRIT] = 1,
    [ABILITY_VOLT_ABSORB] = 1,
    [ABILITY_WATER_ABSORB] = 1,
    [ABILITY_WATER_VEIL] = 1,
    [ABILITY_WHITE_SMOKE] = 1,
    [ABILITY_WONDER_GUARD] = 1,
    [ABILITY_DISPIRIT_GUARD] = 1,
    [ABILITY_BIG_PECKS] = 1,
    [ABILITY_CONTRARY] = 1,
    [ABILITY_FRIEND_GUARD] = 1,
    [ABILITY_HEAVY_METAL] = 1,
    [ABILITY_LIGHT_METAL] = 1,
    [ABILITY_MAGIC_BOUNCE] = 1,
    [ABILITY_MULTISCALE] = 1,
    [ABILITY_SAP_SIPPER] = 1,
    [ABILITY_TELEPATHY] = 1,
    [ABILITY_WONDER_SKIN] = 1,
    [ABILITY_AROMA_VEIL] = 1,
    [ABILITY_BULLETPROOF] = 1,
    [ABILITY_FLOWER_VEIL] = 1,
    [ABILITY_FUR_COAT] = 1,
    [ABILITY_OVERCOAT] = 1,
    [ABILITY_SWEET_VEIL] = 1,
    [ABILITY_DAZZLING] = 1,
    [ABILITY_DISGUISE] = 1,
    [ABILITY_FLUFFY] = 1,
    [ABILITY_QUEENLY_MAJESTY] = 1,
    [ABILITY_WATER_BUBBLE] = 1,
};

static const u8 sAbilitiesNotTraced[ABILITIES_COUNT] =
{
    [ABILITY_AS_ONE_ICE_RIDER] = 1,
    [ABILITY_AS_ONE_SHADOW_RIDER] = 1,
    [ABILITY_BATTLE_BOND] = 1,
    [ABILITY_COMATOSE] = 1,
    [ABILITY_DISGUISE] = 1,
    [ABILITY_FLOWER_GIFT] = 1,
    [ABILITY_FORECAST] = 1,
    [ABILITY_GULP_MISSILE] = 1,
    [ABILITY_HUNGER_SWITCH] = 1,
    [ABILITY_ICE_FACE] = 1,
    [ABILITY_ILLUSION] = 1,
    [ABILITY_IMPOSTER] = 1,
    [ABILITY_MULTITYPE] = 1,
    [ABILITY_NEUTRALIZING_GAS] = 1,
    [ABILITY_NONE] = 1,
    [ABILITY_POWER_CONSTRUCT] = 1,
    [ABILITY_POWER_OF_ALCHEMY] = 1,
    [ABILITY_RECEIVER] = 1,
    [ABILITY_RKS_SYSTEM] = 1,
    [ABILITY_SCHOOLING] = 1,
    [ABILITY_SHIELDS_DOWN] = 1,
    [ABILITY_STANCE_CHANGE] = 1,
    [ABILITY_TRACE] = 1,
    [ABILITY_ZEN_MODE] = 1,
};


void CancelMultiTurnMoves(u8 battler)
{
    gBattleMons[battler].status2 &= ~(STATUS2_MULTIPLETURNS);
    gBattleMons[battler].status2 &= ~(STATUS2_LOCK_CONFUSE);
    gBattleMons[battler].status2 &= ~(STATUS2_UPROAR);
    gBattleMons[battler].status2 &= ~(STATUS2_BIDE);
    gStatuses3[battler] &= ~(STATUS3_SEMI_INVULNERABLE);
    gDisableStructs[battler].rolloutTimer = 0;
    gDisableStructs[battler].furyCutterCounter = 0; //need test but if worked
    //this is no longer a multi-turn effect so guess
    //I may not need furycounter.. 
}

bool8 WasUnableToUseMove(u8 battler) //put in spirit lock here
{
    if (gProtectStructs[battler].prlzImmobility
     || gProtectStructs[battler].targetNotAffected
     || gProtectStructs[battler].usedImprisonedMove
     || gProtectStructs[battler].loveImmobility
     || gProtectStructs[battler].usedDisabledMove
     || gProtectStructs[battler].usedTauntedMove
     || gProtectStructs[battler].usedGravityPreventedMove
     || gProtectStructs[battler].usedHealBlockedMove		
     || gProtectStructs[battler].flag2Unknown
     || gProtectStructs[battler].flinchImmobility
     || gProtectStructs[battler].confusionSelfDmg
	 || gProtectStructs[battler].powderSelfDmg
     || gProtectStructs[battler].usedThroatChopPreventedMove)
        return TRUE;
    else
        return FALSE;
}

void PrepareStringBattle(u16 stringId, u8 battler)
{
    // Support for Contrary ability.
    // If a move attempted to raise stat - print "won't increase".
    // If a move attempted to lower stat - print "won't decrease".
    if (stringId == STRINGID_STATSWONTDECREASE && !(gBattleScripting.statChanger & STAT_BUFF_NEGATIVE))
        stringId = STRINGID_STATSWONTINCREASE;
    else if (stringId == STRINGID_STATSWONTINCREASE && gBattleScripting.statChanger & STAT_BUFF_NEGATIVE)
        stringId = STRINGID_STATSWONTDECREASE;

    else if (stringId == STRINGID_STATSWONTDECREASE2 && GetBattlerAbility(battler) == ABILITY_CONTRARY)
        stringId = STRINGID_STATSWONTINCREASE2;
    else if (stringId == STRINGID_STATSWONTINCREASE2 && GetBattlerAbility(battler) == ABILITY_CONTRARY)
        stringId = STRINGID_STATSWONTDECREASE2;

    // Check Defiant and Competitive stat raise whenever a stat is lowered.
    else if ((stringId == STRINGID_PKMNSSTATCHANGED4 || stringId == STRINGID_PKMNCUTSATTACKWITH)
              && ((GetBattlerAbility(gBattlerTarget) == ABILITY_DEFIANT && gBattleMons[gBattlerTarget].statStages[STAT_ATK] != 12)
                 || (GetBattlerAbility(gBattlerTarget) == ABILITY_COMPETITIVE && gBattleMons[gBattlerTarget].statStages[STAT_SPATK] != 12))
              && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != BATTLE_PARTNER(gBattlerTarget)
              && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget)
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_DefiantActivates;
        if (GetBattlerAbility(gBattlerTarget) == ABILITY_DEFIANT)
            SET_STATCHANGER(STAT_ATK, 2, FALSE);
        else
            SET_STATCHANGER(STAT_SPATK, 2, FALSE);
    }

    gActiveBattler = battler;
    BtlController_EmitPrintString(0, stringId);
    MarkBattlerForControllerExec(gActiveBattler);
}

void ResetSentPokesToOpponentValue(void)
{
    s32 i;
    u32 bits = 0;

    gSentPokesToOpponent[0] = 0;
    gSentPokesToOpponent[1] = 0;
    for (i = 0; i < gBattlersCount; i += 2)
        bits |= gBitTable[gBattlerPartyIndexes[i]];
    for (i = 1; i < gBattlersCount; i += 2)
        gSentPokesToOpponent[(i & BIT_FLANK) >> 1] = bits;
}

void sub_8017434(u8 battler)
{
    s32 i = 0;
    u32 bits = 0;

    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
    {
        u8 flank = ((battler & BIT_FLANK) >> 1);

        gSentPokesToOpponent[flank] = 0;
        for (i = 0; i < gBattlersCount; i += 2)
            if (!(gAbsentBattlerFlags & gBitTable[i]))
                bits |= gBitTable[gBattlerPartyIndexes[i]];
        gSentPokesToOpponent[flank] = bits;
    }
}

void UpdateSentPokesToOpponentValue(u8 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
    {
        sub_8017434(battler);
    }
    else
    {
        s32 i;
        
        for (i = 1; i < gBattlersCount; ++i)
            gSentPokesToOpponent[(i & BIT_FLANK) >> 1] |= gBitTable[gBattlerPartyIndexes[battler]];
    }
}

void BattleScriptPush(const u8 *bsPtr)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = bsPtr;
}

void BattleScriptPushCursor(void)
{
    gBattleResources->battleScriptsStack->ptr[gBattleResources->battleScriptsStack->size++] = gBattlescriptCurrInstr;
}

void BattleScriptPop(void)
{
    gBattlescriptCurrInstr = gBattleResources->battleScriptsStack->ptr[--gBattleResources->battleScriptsStack->size];
}

static bool32 IsGravityPreventingMove(u32 move)
{
    if (!(gFieldStatuses & STATUS_FIELD_GRAVITY))
        return FALSE;

    switch (move)
    {
    case MOVE_BOUNCE:
    case MOVE_FLY:
    case MOVE_FLYING_PRESS:
    case MOVE_HI_JUMP_KICK:
    case MOVE_JUMP_KICK:
    case MOVE_MAGNET_RISE:
    case MOVE_SKY_DROP:
    case MOVE_SPLASH:
    case MOVE_TELEKINESIS:
    case MOVE_FLOATY_FALL:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsHealBlockPreventingMove(u32 battler, u32 move)
{
    if (!(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
        return FALSE;

    switch (gBattleMoves[move].effect)
    {
    case EFFECT_ABSORB:
    case EFFECT_MORNING_SUN:
    case EFFECT_MOONLIGHT:
    case EFFECT_RESTORE_HP:
    case EFFECT_REST:
    case EFFECT_ROOST:
    case EFFECT_HEALING_WISH:
    case EFFECT_WISH:
    case EFFECT_DREAM_EATER:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsBelchPreventingMove(u32 battler, u32 move)
{
    if (gBattleMoves[move].effect != EFFECT_BELCH)
        return FALSE;

    return !(gBattleStruct->ateBerry[battler & BIT_SIDE] & gBitTable[gBattlerPartyIndexes[battler]]);
}											   
u8 TrySetCantSelectMoveBattleScript(void)
{
    u8 holdEffect;
    u8 limitations = 0;
    u16 move = gBattleMons[gActiveBattler].moves[gBattleBufferB[gActiveBattler][2]];
    u16 *choicedMove = &gBattleStruct->choicedMove[gActiveBattler];

    if (gDisableStructs[gActiveBattler].disabledMove == move && move != MOVE_NONE)
    {
        gBattleScripting.battler = gActiveBattler;
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingDisabledMove;
        limitations = 1;
    }
    if (move == gLastMoves[gActiveBattler] && move != MOVE_STRUGGLE && (gBattleMons[gActiveBattler].status2 & STATUS2_TORMENT))
    {
        CancelMultiTurnMoves(gActiveBattler);
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingTormentedMove;
        ++limitations;
    }
    if (gDisableStructs[gActiveBattler].tauntTimer && !gBattleMoves[move].power)
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveTaunt;
        ++limitations;
    }
    if (GetImprisonedMovesCount(gActiveBattler, move))
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingImprisonedMove;
        ++limitations;
    }
    if (gBattleMons[gActiveBattler].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[gActiveBattler].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(gBattleMons[gActiveBattler].item);
    gPotentialItemEffectBattler = gActiveBattler;
    if (holdEffect == HOLD_EFFECT_CHOICE_BAND && *choicedMove && *choicedMove != 0xFFFF && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[gActiveBattler].item;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveChoiceItem;
        ++limitations;
    }
    if (!gBattleMons[gActiveBattler].pp[gBattleBufferB[gActiveBattler][2]])
    {
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingMoveWithNoPP;
        ++limitations;
    }
    return limitations;
}

u8 CheckMoveLimitations(u8 battlerId, u8 unusableMoves, u8 check)
{
    u8 holdEffect;
    u16 *choicedMove = &gBattleStruct->choicedMove[battlerId];
    s32 i;

    if (gBattleMons[battlerId].item == ITEM_ENIGMA_BERRY)
        holdEffect = gEnigmaBerries[battlerId].holdEffect;
    else
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battlerId].item);
    gPotentialItemEffectBattler = battlerId;

    for (i = 0; i < MAX_MON_MOVES; ++i)
    {
        if (gBattleMons[battlerId].moves[i] == 0 && check & MOVE_LIMITATION_ZEROMOVE)
            unusableMoves |= gBitTable[i];
        if (gBattleMons[battlerId].pp[i] == 0 && check & MOVE_LIMITATION_PP)
            unusableMoves |= gBitTable[i];
        if (gBattleMons[battlerId].moves[i] == gDisableStructs[battlerId].disabledMove && check & MOVE_LIMITATION_DISABLED)
            unusableMoves |= gBitTable[i];
        if (gBattleMons[battlerId].moves[i] == gLastMoves[battlerId] && check & MOVE_LIMITATION_TORMENTED && gBattleMons[battlerId].status2 & STATUS2_TORMENT)
            unusableMoves |= gBitTable[i];
        if (gDisableStructs[battlerId].tauntTimer && check & MOVE_LIMITATION_TAUNT && gBattleMoves[gBattleMons[battlerId].moves[i]].power == 0)
            unusableMoves |= gBitTable[i];
        if (GetImprisonedMovesCount(battlerId, gBattleMons[battlerId].moves[i]) && check & MOVE_LIMITATION_IMPRISON)
            unusableMoves |= gBitTable[i];
        if (gDisableStructs[battlerId].encoreTimer && gDisableStructs[battlerId].encoredMove != gBattleMons[battlerId].moves[i])
            unusableMoves |= gBitTable[i];
        if (holdEffect == HOLD_EFFECT_CHOICE_BAND && *choicedMove != 0 && *choicedMove != 0xFFFF && *choicedMove != gBattleMons[battlerId].moves[i])
            unusableMoves |= gBitTable[i];
        if (holdEffect == HOLD_EFFECT_ASSAULT_VEST && gBattleMoves[gBattleMons[battlerId].moves[i]].power == 0)
            unusableMoves |= gBitTable[i];
        if (IsGravityPreventingMove(gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        if (IsHealBlockPreventingMove(battlerId, gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        if (IsBelchPreventingMove(battlerId, gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        if (gDisableStructs[battlerId].throatChopTimer && gBattleMoves[gBattleMons[battlerId].moves[i]].flags & FLAG_SOUND)
            unusableMoves |= gBitTable[i];
    }
    return unusableMoves;
}

static void MulModifier(u16* modifier, u16 val)
{
    *modifier = UQ_4_12_TO_INT((*modifier * val) + UQ_4_12_ROUND);
}

static u32 ApplyModifier(u16 modifier, u32 val)
{
    return UQ_4_12_TO_INT((modifier * val) + UQ_4_12_ROUND);
}

/*static void UpdateMoveResultFlags(u16 modifier) //  start of ported effect flags  
//may instead just use move result flags instead of these functions...yeah I'll just use that.
{
    if (modifier == UQ_4_12(0.0))
    {
        gMoveResultFlags |= MOVE_RESULT_DOESNT_AFFECT_FOE;
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE);
    }
    else if (modifier == UQ_4_12(1.0))
    {
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else if (modifier > UQ_4_12(1.0))
    {
        gMoveResultFlags |= MOVE_RESULT_SUPER_EFFECTIVE;
        gMoveResultFlags &= ~(MOVE_RESULT_NOT_VERY_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
    else //if (modifier < UQ_4_12(1.0))
    {
        gMoveResultFlags |= MOVE_RESULT_NOT_VERY_EFFECTIVE;
        gMoveResultFlags &= ~(MOVE_RESULT_SUPER_EFFECTIVE | MOVE_RESULT_DOESNT_AFFECT_FOE);
    }
}

static void MulByTypeEffectiveness(u16 *modifier, u16 move, u8 moveType, u8 battlerDef, u8 defType, u8 battlerAtk, bool32 recordAbilities)
{
    u16 mod = GetTypeModifier(moveType, defType);

    if (mod == UQ_4_12(0.0) && GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_RING_TARGET)
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordItemEffectBattle(battlerDef, HOLD_EFFECT_RING_TARGET);
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && GetBattlerAbility(battlerAtk) == ABILITY_SCRAPPY && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
        if (recordAbilities)
            RecordAbilityBattle(battlerAtk, ABILITY_SCRAPPY);
    }

    if (moveType == TYPE_PSYCHIC && defType == TYPE_DARK && gStatuses3[battlerDef] & STATUS3_MIRACLE_EYED && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_FREEZE_DRY && defType == TYPE_WATER)
        mod = UQ_4_12(2.0);
    if (moveType == TYPE_GROUND && defType == TYPE_FLYING && IsBattlerGrounded(battlerDef) && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);

    if (gProtectStructs[battlerDef].kingsShielded && gBattleMoves[move].effect != EFFECT_FEINT)
        mod = UQ_4_12(1.0);

    MulModifier(modifier, mod);
}

static u16 CalcTypeEffectivenessMultiplierInternal(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities, u16 modifier)
{
    MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type1, battlerAtk, recordAbilities);
    if (gBattleMons[battlerDef].type2 != gBattleMons[battlerDef].type1)
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type2, battlerAtk, recordAbilities);
    if (gBattleMons[battlerDef].type3 != TYPE_MYSTERY && gBattleMons[battlerDef].type3 != gBattleMons[battlerDef].type2
        && gBattleMons[battlerDef].type3 != gBattleMons[battlerDef].type1)
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type3, battlerAtk, recordAbilities);

    if (moveType == TYPE_GROUND && !IsBattlerGrounded(battlerDef))
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities && GetBattlerAbility(battlerDef) == ABILITY_LEVITATE)
        {
            gLastUsedAbility = ABILITY_LEVITATE;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[6] = 4;
            RecordAbilityBattle(battlerDef, ABILITY_LEVITATE);
        }
    }
    if (GetBattlerAbility(battlerDef) == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0) && gBattleMoves[move].power)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities)
        {
            gLastUsedAbility = ABILITY_WONDER_GUARD;
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[6] = 3;
            RecordAbilityBattle(battlerDef, ABILITY_WONDER_GUARD);
        }
    }

    return modifier;
}

u16 CalcTypeEffectivenessMultiplier(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities)
{
    u16 modifier = UQ_4_12(1.0);

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY)
    {
        modifier = CalcTypeEffectivenessMultiplierInternal(move, moveType, battlerAtk, battlerDef, recordAbilities, modifier);
        if (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, gBattleMoves[move].argument, battlerAtk, battlerDef, recordAbilities, modifier);
    }

    if (recordAbilities)
        UpdateMoveResultFlags(modifier);
    return modifier;
}*/   //  end of ported effect flags functions

bool8 AreAllMovesUnusable(void)
{
    u8 unusable = CheckMoveLimitations(gActiveBattler, 0, 0xFF);

    if (unusable == 0xF) // All moves are unusable.
    {
        gProtectStructs[gActiveBattler].noValidMoves = 1;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_NoMovesLeft;
        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            gBattleBufferB[gActiveBattler][3] = GetBattlerAtPosition((BATTLE_OPPOSITE(GetBattlerPosition(gActiveBattler))) | (Random() & 2));
        else 
            gBattleBufferB[gActiveBattler][3] = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerPosition(gActiveBattler)));
    }
    else
    {
        gProtectStructs[gActiveBattler].noValidMoves = 0;
    }
    return (unusable == 0xF);
}

u8 GetImprisonedMovesCount(u8 battlerId, u16 move)
{
    s32 i;
    u8 imprisonedMoves = 0;
    u8 battlerSide = GetBattlerSide(battlerId);

    for (i = 0; i < gBattlersCount; ++i)
    {
        if (battlerSide != GetBattlerSide(i) && gStatuses3[i] & STATUS3_IMPRISONED_OTHERS)
        {
            s32 j;

            for (j = 0; j < MAX_MON_MOVES && move != gBattleMons[i].moves[j]; ++j);
            if (j < MAX_MON_MOVES)
                ++imprisonedMoves;
        }
    }
    return imprisonedMoves;
}

enum
{
    ENDTURN_ORDER,
    ENDTURN_REFLECT,
    ENDTURN_LIGHT_SCREEN,
    ENDTURN_AURORA_VEIL,
    ENDTURN_MIST,
    ENDTURN_LUCKY_CHANT,
    ENDTURN_SAFEGUARD,
    ENDTURN_TAILWIND,
    ENDTURN_WISH,
    ENDTURN_RAIN,
    ENDTURN_SANDSTORM,
    ENDTURN_SUN,
    ENDTURN_HAIL,
    ENDTURN_GRAVITY,
    ENDTURN_WATER_SPORT,
    ENDTURN_MUD_SPORT,
    ENDTURN_TRICK_ROOM,
    ENDTURN_WONDER_ROOM,
    ENDTURN_MAGIC_ROOM,
    ENDTURN_ELECTRIC_TERRAIN,
    ENDTURN_MISTY_TERRAIN,
    ENDTURN_GRASSY_TERRAIN,
    ENDTURN_PSYCHIC_TERRAIN,
    ENDTURN_ION_DELUGE,
    ENDTURN_FAIRY_LOCK,
    ENDTURN_FIELD_COUNT,
};

u8 DoFieldEndTurnEffects(void)
{
    u8 effect = 0;
    s32 i;

    for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerAttacker]; ++gBattlerAttacker);
    for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerTarget]; ++gBattlerTarget);
    do
    {
        u8 side;

        switch (gBattleStruct->turnCountersTracker)
        {
        case ENDTURN_ORDER:
            for (i = 0; i < gBattlersCount; i++)
            {
                gBattlerByTurnOrder[i] = i;
            }
            for (i = 0; i < gBattlersCount - 1; i++)
            {
                s32 j;
				
                for (j = i + 1; j < gBattlersCount; j++)
                {
                    if (GetWhoStrikesFirst(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], 0))
                        SwapTurnOrder(i, j);
                }
			 
															  
				
					   
												   
            }

            gBattleStruct->turnCountersTracker++;
            gBattleStruct->turnSideTracker = 0;
            // fall through
        case ENDTURN_REFLECT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].reflectBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_REFLECT)
                {
                    if (--gSideTimers[side].reflectTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_REFLECT;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_REFLECT);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_LIGHT_SCREEN:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].lightscreenBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_LIGHTSCREEN)
                {
                    if (--gSideTimers[side].lightscreenTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_LIGHTSCREEN;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_LIGHT_SCREEN);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_AURORA_VEIL:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].auroraVeilBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_AURORA_VEIL)
                {
                    if (--gSideTimers[side].auroraVeilTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_AURORA_VEIL;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_AURORA_VEIL);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_MIST:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].mistBattlerId;
                if (gSideTimers[side].mistTimer != 0
                 && --gSideTimers[side].mistTimer == 0)
                {
                    gSideStatuses[side] &= ~SIDE_STATUS_MIST;
                    BattleScriptExecute(BattleScript_SideStatusWoreOff);
                    gBattleCommunication[MULTISTRING_CHOOSER] = side;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_MIST);
                    effect++;
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_SAFEGUARD:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].safeguardBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_SAFEGUARD)
                {
                    if (--gSideTimers[side].safeguardTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_SAFEGUARD;
                        BattleScriptExecute(BattleScript_SafeguardEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_LUCKY_CHANT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].luckyChantBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_LUCKY_CHANT)
                {
                    if (--gSideTimers[side].luckyChantTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_LUCKY_CHANT;
                        BattleScriptExecute(BattleScript_LuckyChantEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_TAILWIND:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].tailwindBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_TAILWIND)
                {
                    if (--gSideTimers[side].tailwindTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_TAILWIND;
                        BattleScriptExecute(BattleScript_TailwindEnds);
                        effect++;
                    }
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_WISH:
            while (gBattleStruct->turnSideTracker < gBattlersCount)
            {
                gActiveBattler = gBattlerByTurnOrder[gBattleStruct->turnSideTracker];
                if (gWishFutureKnock.wishCounter[gActiveBattler] != 0
                 && --gWishFutureKnock.wishCounter[gActiveBattler] == 0
                 && gBattleMons[gActiveBattler].hp != 0)
                {
                    gBattlerTarget = gActiveBattler;
                    BattleScriptExecute(BattleScript_WishComesTrue);
                    effect++;
                }
                gBattleStruct->turnSideTracker++;
                if (effect)
                    break;
            }
            if (!effect)
            {
                gBattleStruct->turnCountersTracker++;
            }
            break;
        case ENDTURN_RAIN:
            if (gBattleWeather & WEATHER_RAIN_ANY)
            {
                if (!(gBattleWeather & WEATHER_RAIN_PERMANENT))
                {
                    if (--gWishFutureKnock.weatherDuration == 0)
                    {
                        gBattleWeather &= ~WEATHER_RAIN_TEMPORARY;
                        gBattleWeather &= ~WEATHER_RAIN_DOWNPOUR;
                        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                    }
                    else if (gBattleWeather & WEATHER_RAIN_DOWNPOUR)
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                }
                else if (gBattleWeather & WEATHER_RAIN_DOWNPOUR)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                }
                else
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                }

                BattleScriptExecute(BattleScript_RainContinuesOrEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_SANDSTORM:
            if (gBattleWeather & WEATHER_SANDSTORM_ANY)
            {
                if (!(gBattleWeather & WEATHER_SANDSTORM_PERMANENT) && --gWishFutureKnock.weatherDuration == 0)
                {
                    gBattleWeather &= ~WEATHER_SANDSTORM_TEMPORARY;
                    gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }

                gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_SUN:
            if (gBattleWeather & WEATHER_SUN_ANY)
            {
                if (!(gBattleWeather & WEATHER_SUN_PERMANENT) && --gWishFutureKnock.weatherDuration == 0)
                {
                    gBattleWeather &= ~WEATHER_SUN_TEMPORARY;
                    gBattlescriptCurrInstr = BattleScript_SunlightFaded;
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_SunlightContinues;
                }

                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_HAIL:
            if (gBattleWeather & WEATHER_HAIL_ANY)
            {
                if (!(gBattleWeather & WEATHER_HAIL) && --gWishFutureKnock.weatherDuration == 0)
                {
                    gBattleWeather &= ~WEATHER_HAIL;
                    gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }

                gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                BattleScriptExecute(gBattlescriptCurrInstr);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_TRICK_ROOM:
            if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && --gFieldTimers.trickRoomTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_TRICK_ROOM);
                BattleScriptExecute(BattleScript_TrickRoomEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_WONDER_ROOM:
            if (gFieldStatuses & STATUS_FIELD_WONDER_ROOM && --gFieldTimers.wonderRoomTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_WONDER_ROOM);
                BattleScriptExecute(BattleScript_WonderRoomEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MAGIC_ROOM:
            if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM && --gFieldTimers.magicRoomTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_MAGIC_ROOM);
                BattleScriptExecute(BattleScript_MagicRoomEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_ELECTRIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN && --gFieldTimers.electricTerrainTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_ELECTRIC_TERRAIN);
                BattleScriptExecute(BattleScript_ElectricTerrainEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MISTY_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN && --gFieldTimers.mistyTerrainTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_MISTY_TERRAIN);
                BattleScriptExecute(BattleScript_MistyTerrainEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_GRASSY_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
            {
                if (gFieldTimers.grassyTerrainTimer == 0 || --gFieldTimers.grassyTerrainTimer == 0)
                    gFieldStatuses &= ~(STATUS_FIELD_GRASSY_TERRAIN);
                BattleScriptExecute(BattleScript_GrassyTerrainHeals);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_PSYCHIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN && --gFieldTimers.psychicTerrainTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_PSYCHIC_TERRAIN);
                BattleScriptExecute(BattleScript_PsychicTerrainEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        /*case ENDTURN_WATER_SPORT: // remove these because I'm keeping old sport function that doesn't end mid battle
            if (gFieldStatuses & STATUS_FIELD_WATERSPORT && --gFieldTimers.waterSportTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_WATERSPORT);
                BattleScriptExecute(BattleScript_WaterSportEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_MUD_SPORT:
            if (gFieldStatuses & STATUS_FIELD_MUDSPORT && --gFieldTimers.mudSportTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_MUDSPORT);
                BattleScriptExecute(BattleScript_MudSportEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;*/
        case ENDTURN_GRAVITY:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && --gFieldTimers.gravityTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_GRAVITY);
                BattleScriptExecute(BattleScript_GravityEnds);
                effect++;
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_ION_DELUGE:
            if (gFieldStatuses & STATUS_FIELD_ION_DELUGE && --gFieldTimers.IonDelugeTimer == 0) //
            {
                gFieldStatuses &= ~(STATUS_FIELD_ION_DELUGE); //timers seems to be set in bs commands (fairylock is different)
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_FAIRY_LOCK:
            if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK && --gFieldTimers.fairyLockTimer == 0)
            {
                gFieldStatuses &= ~(STATUS_FIELD_FAIRY_LOCK);
            }
            gBattleStruct->turnCountersTracker++;
            break;
        case ENDTURN_FIELD_COUNT:
            effect++;
            break;
        }
    } while (effect == 0);

    return (gBattleMainFunc != BattleTurnPassed);
}

enum
{
    ENDTURN_INGRAIN,
    ENDTURN_AQUA_RING,
    ENDTURN_ABILITIES,
    ENDTURN_ITEMS1,
    ENDTURN_LEECH_SEED,
    ENDTURN_POISON,
    ENDTURN_BAD_POISON,
    ENDTURN_BURN,
    ENDTURN_NIGHTMARES,
    ENDTURN_CURSE,
    ENDTURN_WRAP,
    ENDTURN_UPROAR,
    ENDTURN_THRASH,
    ENDTURN_FLINCH,
    ENDTURN_DISABLE,
    ENDTURN_ENCORE,
    ENDTURN_MAGNET_RISE,
    ENDTURN_TELEKINESIS,
    ENDTURN_HEALBLOCK,
    ENDTURN_EMBARGO,
    ENDTURN_LOCK_ON,
    ENDTURN_CHARGE,
    ENDTURN_LASER_FOCUS,
    ENDTURN_TAUNT,
    ENDTURN_YAWN,
    ENDTURN_ITEMS2,
    ENDTURN_ORBS,
    ENDTURN_ROOST,
    ENDTURN_ELECTRIFY,
    ENDTURN_POWDER,
    ENDTURN_THROAT_CHOP,
    ENDTURN_SLOW_START,
    ENDTURN_BATTLER_COUNT
};
// Ingrain, Leech Seed, Strength Sap and Aqua Ring
s32 GetDrainedBigRootHp(u32 battler, s32 hp)
{
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_BIG_ROOT) //prob need to balance this for ingrain,
    {
        hp = (hp * 1300) / 1000;
        if (gStatuses3[gActiveBattler] & STATUS3_ROOTED) //hopefully that works.
            hp = (hp * 1100) / 1000;
    }
       
    if (hp == 0)
        hp = 1;

    return hp * -1;
}

#define MAGIC_GAURD_CHECK \
if (ability == ABILITY_MAGIC_GUARD) \
{\
    RecordAbilityBattle(gActiveBattler, ability);\
    gBattleStruct->turnEffectsTracker++;\
            break;\
}											   
u8 DoBattlerEndTurnEffects(void)
{
    u8 effect = 0;
    u16 ability;

    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_x20);
    while (gBattleStruct->turnEffectsBattlerId < gBattlersCount && gBattleStruct->turnEffectsTracker <= ENDTURN_BATTLER_COUNT)
    {
        gActiveBattler = gBattlerAttacker = gBattlerByTurnOrder[gBattleStruct->turnEffectsBattlerId];
        if (gAbsentBattlerFlags & gBitTable[gActiveBattler])
        {
            ++gBattleStruct->turnEffectsBattlerId;
        }
        else
        {
            switch (gBattleStruct->turnEffectsTracker)
            {
            case ENDTURN_INGRAIN:  // ingrain
                if ((gStatuses3[gActiveBattler] & STATUS3_ROOTED)
                 && !BATTLER_MAX_HP(gActiveBattler)
                 && !(gStatuses3[gActiveBattler] & STATUS3_HEAL_BLOCK)
                 && gBattleMons[gActiveBattler].hp != 0) //function changes & new rooted defines courtesy of phoenix_bound
                {
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                    if (gBattleMoveDamage == 0)//this caps at 16 turns because the orginal & bit calculation == 0, then it adds 0x100 if it doesn't equal 0xF00 which is 1500
                        gBattleMoveDamage = 1; // so it caps the turns by essentially counting from 0 to 15. so controlling/balancing the effect is as simple as lowering 0xF00!!!
                    if ((gStatuses3[gActiveBattler] & STATUS3_ROOTED_COUNTER) != STATUS3_ROOTED_TURN(15)) { // not 16 turns/ facepalm just realized how this works!1!
                        gStatuses3[gActiveBattler] += STATUS3_ROOTED_TURN(1); //seriously spitballin' here, nothing's broken atleast all the colors below are still right
                    }
                    gBattleMoveDamage *= gStatuses3 >> STATUS3_ROOTED_SHIFT;       // need understand
                    gBattleMoveDamage *= -1; //moved this to the bottom previously, because it doesn't need to be up top, and so its read last, 
                    BattleScriptExecute(BattleScript_IngrainTurnHeal);
                    ++effect; //next step augment battlescript to be similar to poisonturndamage../no changes needed everything handled by gbattlemovedamage in these funtions
                    //and the  updatehp commands in the battle script.  purpose of these changes was to ingrain work like but opposite to toxic, increase heal by same amount each turn
                } //I'm completely guessing but if done right, should heal an additional 1/16th per turn
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_AQUA_RING:  // aqua ring
                if ((gStatuses3[gActiveBattler] & STATUS3_AQUA_RING)
                    && !BATTLER_MAX_HP(gActiveBattler)
                    && !(gStatuses3[gActiveBattler] & STATUS3_HEAL_BLOCK)
                    && gBattleMons[gActiveBattler].hp != 0)
                {
                    gBattleMoveDamage = GetDrainedBigRootHp(gActiveBattler, gBattleMons[gActiveBattler].maxHP / 16);
                    BattleScriptExecute(BattleScript_AquaRingHeal);
                    effect++;
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_ABILITIES:  // end turn abilities
                if (AbilityBattleEffects(ABILITYEFFECT_ENDTURN, gActiveBattler, 0, 0, 0))
                    ++effect;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ITEMS1:  // item effects
                if (ItemBattleEffects(1, gActiveBattler, FALSE))
                    ++effect;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ITEMS2:  // item effects again
                if (ItemBattleEffects(1, gActiveBattler, TRUE))
                    ++effect;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ORBS:
                if (ItemBattleEffects(ITEMEFFECT_ORBS, gActiveBattler, FALSE))
                    effect++;
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_LEECH_SEED:  // leech seed
                if ((gStatuses3[gActiveBattler] & STATUS3_LEECHSEED)
                 && gBattleMons[gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER].hp != 0
                 && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;

                    gBattlerTarget = gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER; // Notice gBattlerTarget is actually the HP receiver.
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleScripting.animArg1 = gBattlerTarget;
                    gBattleScripting.animArg2 = gBattlerAttacker;
                    BattleScriptExecute(BattleScript_LeechSeedTurnDrain);
                    effect++;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_POISON:  // poison
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_POISON) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;

                    if (ability == ABILITY_POISON_HEAL)
                    {
                        if (!BATTLER_MAX_HP(gActiveBattler) && !(gStatuses3[gActiveBattler] & STATUS3_HEAL_BLOCK))
                        {
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                            gBattleMoveDamage *= -1;
                            BattleScriptExecute(BattleScript_PoisonHealActivates);
                            effect++;
                        }
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        BattleScriptExecute(BattleScript_PoisonTurnDmg);
                        effect++;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BAD_POISON:  // toxic poison
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_POISON) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;

                    if (ability == ABILITY_POISON_HEAL)
                    {
                        if (!BATTLER_MAX_HP(gActiveBattler) && !(gStatuses3[gActiveBattler] & STATUS3_HEAL_BLOCK))
                        {
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                            gBattleMoveDamage *= -1; //this is what I need to make it heal.
                            BattleScriptExecute(BattleScript_PoisonHealActivates);
                            effect++;
                        }
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1; //guess part below handles toxic counter allong with battlescript
                        if ((gBattleMons[gActiveBattler].status1 & 0xF00) != 0xF00) // not 16 turns
                            gBattleMons[gActiveBattler].status1 += 0x100;
                        gBattleMoveDamage *= (gBattleMons[gActiveBattler].status1 & 0xF00) >> 8;// think 0xF00 is also value for poison counter so will have to change first part for ingrain
                        BattleScriptExecute(BattleScript_PoisonTurnDmg);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BURN:  // burn
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_BURN) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;

                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                    if (ability == ABILITY_HEATPROOF)
                    {
                        if (gBattleMoveDamage > (gBattleMoveDamage / 2) + 1) // Record ability if the burn takes less damage than it normally would.
                            RecordAbilityBattle(gActiveBattler, ABILITY_HEATPROOF);
                        gBattleMoveDamage /= 2;
                    }
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptExecute(BattleScript_BurnTurnDmg);
                    effect++;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_NIGHTMARES:  // spooky nightmares
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_NIGHTMARE) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;
                    // R/S does not perform this sleep check, which causes the nightmare effect to
                    // persist even after the affected Pokemon has been awakened by Shed Skin.
                    if (gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        BattleScriptExecute(BattleScript_NightmareTurnDmg);
                        effect++;
                    }
                    else
                    {
                        gBattleMons[gActiveBattler].status2 &= ~STATUS2_NIGHTMARE;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_CURSE:  // curse
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_CURSED) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GAURD_CHECK;
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptExecute(BattleScript_CurseTurnDmg);
                    effect++;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_WRAP:  // wrap
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_WRAPPED) && gBattleMons[gActiveBattler].hp != 0)
                {
                    gBattleMons[gActiveBattler].status2 -= 0x2000;
                    if (gBattleMons[gActiveBattler].status2 & STATUS2_WRAPPED)  // damaged by wrap
                    {
                        gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8; // 6 for gen 6+
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; // 8 for gen 6+
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_UPROAR:  // uproar
                if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR)
                {
                    for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount; ++gBattlerAttacker)
                    {
                        if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP)
                         && gBattleMons[gBattlerAttacker].ability != ABILITY_SOUNDPROOF)
                        {
                            gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP);
                            gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
                            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                            BattleScriptExecute(BattleScript_MonWokeUpInUproar);
                            gActiveBattler = gBattlerAttacker;
                            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                            MarkBattlerForControllerExec(gActiveBattler);
                            break;
                        }
                    }
                    if (gBattlerAttacker != gBattlersCount)
                    {
                        effect = 2;  // a pokemon was awaken
                        break;
                    }
                    else
                    {
                        gBattlerAttacker = gActiveBattler;
                        gBattleMons[gActiveBattler].status2 -= 0x10;  // uproar timer goes down
                        if (WasUnableToUseMove(gActiveBattler))
                        {
                            CancelMultiTurnMoves(gActiveBattler);
                            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                        }
                        else if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR)
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                            gBattleMons[gActiveBattler].status2 |= STATUS2_MULTIPLETURNS;
                        }
                        else
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                            CancelMultiTurnMoves(gActiveBattler);
                        }
                        BattleScriptExecute(BattleScript_PrintUproarOverTurns);
                        effect = 1;
                    }
                }
                if (effect != 2)
                    ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_THRASH:  // thrash
                if (gBattleMons[gActiveBattler].status2 & STATUS2_LOCK_CONFUSE)
                {
                    gBattleMons[gActiveBattler].status2 -= 0x400;
                    if (WasUnableToUseMove(gActiveBattler))
                        CancelMultiTurnMoves(gActiveBattler);
                    else if (!(gBattleMons[gActiveBattler].status2 & STATUS2_LOCK_CONFUSE)
                          && (gBattleMons[gActiveBattler].status2 & STATUS2_MULTIPLETURNS))
                    {
                        gBattleMons[gActiveBattler].status2 &= ~(STATUS2_MULTIPLETURNS);
                        if (!(gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION))
                        {
                            gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER;
                            SetMoveEffect(1, 0);
                            if (gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION)
                                BattleScriptExecute(BattleScript_ThrashConfuses);
                            ++effect;
                        }
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_FLINCH:  // reset flinch
                gBattleMons[gActiveBattler].status2 &= ~(STATUS2_FLINCHED);
                gBattleStruct->turnEffectsTracker++;
            case ENDTURN_DISABLE:  // disable
                if (gDisableStructs[gActiveBattler].disableTimer != 0)
                {
                    s32 i;

                    for (i = 0; i < MAX_MON_MOVES; ++i)
                    {
                        if (gDisableStructs[gActiveBattler].disabledMove == gBattleMons[gActiveBattler].moves[i])
                            break;
                    }
                    if (i == MAX_MON_MOVES)  // pokemon does not have the disabled move anymore
                    {
                        gDisableStructs[gActiveBattler].disabledMove = MOVE_NONE;
                        gDisableStructs[gActiveBattler].disableTimer = 0;
                    }
                    else if (--gDisableStructs[gActiveBattler].disableTimer == 0)  // disable ends
                    {
                        gDisableStructs[gActiveBattler].disabledMove = MOVE_NONE;
                        BattleScriptExecute(BattleScript_DisabledNoMore);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ENCORE:  // encore
                if (gDisableStructs[gActiveBattler].encoreTimer != 0)
                {
                    if (gBattleMons[gActiveBattler].moves[gDisableStructs[gActiveBattler].encoredMovePos] != gDisableStructs[gActiveBattler].encoredMove)  // pokemon does not have the encored move anymore
                    {
                        gDisableStructs[gActiveBattler].encoredMove = MOVE_NONE;
                        gDisableStructs[gActiveBattler].encoreTimer = 0;
                    }
                    else if (--gDisableStructs[gActiveBattler].encoreTimer == 0
                          || gBattleMons[gActiveBattler].pp[gDisableStructs[gActiveBattler].encoredMovePos] == 0)
                    {
                        gDisableStructs[gActiveBattler].encoredMove = MOVE_NONE;
                        gDisableStructs[gActiveBattler].encoreTimer = 0;
                        BattleScriptExecute(BattleScript_EncoredNoMore);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_LOCK_ON:  // lock-on decrement
                if (gStatuses3[gActiveBattler] & STATUS3_ALWAYS_HITS)
                    gStatuses3[gActiveBattler] -= 0x8;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_CHARGE:  // charge
                if (gDisableStructs[gActiveBattler].chargeTimer && --gDisableStructs[gActiveBattler].chargeTimer == 0)
                    gStatuses3[gActiveBattler] &= ~STATUS3_CHARGED_UP;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_TAUNT:  // taunt
                if (gDisableStructs[gActiveBattler].tauntTimer)
                    --gDisableStructs[gActiveBattler].tauntTimer;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_YAWN:  // yawn
                if (gStatuses3[gActiveBattler] & STATUS3_YAWN)
                {
                    gStatuses3[gActiveBattler] -= 0x800;
                    if (!(gStatuses3[gActiveBattler] & STATUS3_YAWN) && !(gBattleMons[gActiveBattler].status1 & STATUS1_ANY)
                     && gBattleMons[gActiveBattler].ability != ABILITY_VITAL_SPIRIT
                     && gBattleMons[gActiveBattler].ability != ABILITY_INSOMNIA && !UproarWakeUpCheck(gActiveBattler))
                    {
                        CancelMultiTurnMoves(gActiveBattler);
                        gBattleMons[gActiveBattler].status1 |= (Random() & 3) + 2;
                        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                        MarkBattlerForControllerExec(gActiveBattler);
                        gEffectBattler = gActiveBattler;
                        BattleScriptExecute(BattleScript_YawnMakesAsleep);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_LASER_FOCUS:
                if (gStatuses3[gActiveBattler] & STATUS3_LASER_FOCUS)
                {
                    if (gDisableStructs[gActiveBattler].laserFocusTimer == 0 || --gDisableStructs[gActiveBattler].laserFocusTimer == 0)
                        gStatuses3[gActiveBattler] &= ~(STATUS3_LASER_FOCUS);
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_EMBARGO:
                if (gStatuses3[gActiveBattler] & STATUS3_EMBARGO)
                {
                    if (gDisableStructs[gActiveBattler].embargoTimer == 0 || --gDisableStructs[gActiveBattler].embargoTimer == 0)
                    {
                        gStatuses3[gActiveBattler] &= ~(STATUS3_EMBARGO);
                        BattleScriptExecute(BattleScript_EmbargoEndTurn);
                        effect++;
                    }
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_MAGNET_RISE:
                if (gStatuses3[gActiveBattler] & STATUS3_MAGNET_RISE)
                {
                    if (gDisableStructs[gActiveBattler].magnetRiseTimer == 0 || --gDisableStructs[gActiveBattler].magnetRiseTimer == 0)
                    {
                        gStatuses3[gActiveBattler] &= ~(STATUS3_MAGNET_RISE);
                        BattleScriptExecute(BattleScript_BufferEndTurn);
                        PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ELECTROMAGNETISM);
                        effect++;
                    }
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_TELEKINESIS:
                if (gStatuses3[gActiveBattler] & STATUS3_TELEKINESIS)
                {
                    if (gDisableStructs[gActiveBattler].telekinesisTimer == 0 || --gDisableStructs[gActiveBattler].telekinesisTimer == 0)
                    {
                        gStatuses3[gActiveBattler] &= ~(STATUS3_TELEKINESIS);
                        BattleScriptExecute(BattleScript_TelekinesisEndTurn);
                        effect++;
                    }
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_HEALBLOCK:
                if (gStatuses3[gActiveBattler] & STATUS3_HEAL_BLOCK)
                {
                    if (gDisableStructs[gActiveBattler].healBlockTimer == 0 || --gDisableStructs[gActiveBattler].healBlockTimer == 0)
                    {
                        gStatuses3[gActiveBattler] &= ~(STATUS3_HEAL_BLOCK);
                        BattleScriptExecute(BattleScript_BufferEndTurn);
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_HEAL_BLOCK);
                        effect++;
                    }
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_ROOST: // Return flying type.
                //may change sounds like its only lost for duration of move i.e 1 turn
                //which is dumb -_- that could only be taken advantage of in double battle
                //think I'll add a timer use Random() % 4 to find start value
                //pokemon will be grounded for the duration. and succeptible to all ground moves
                //setup like healblock timer above.
                //I'd like to have a little battlestring display when timer is at 0
                //something like "pokemonname" returned to the air or something..
                if (gBattleResources->flags->flags[gActiveBattler] & RESOURCE_FLAG_ROOST
                    && --gDisableStructs[gActiveBattler].RoostTimer == 0)
                {
                    gBattleResources->flags->flags[gActiveBattler] &= ~(RESOURCE_FLAG_ROOST);
                    //gBattleMons[gActiveBattler].type1 = gBattleStruct->roostTypes[gActiveBattler][0];
                    //gBattleMons[gActiveBattler].type2 = gBattleStruct->roostTypes[gActiveBattler][1];
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_ELECTRIFY:
                gStatuses3[gActiveBattler] &= ~(STATUS3_ELECTRIFIED);
                gBattleStruct->turnEffectsTracker++;
            case ENDTURN_POWDER:
                gBattleMons[gActiveBattler].status2 &= ~(STATUS2_POWDER);
                gBattleStruct->turnEffectsTracker++;
            case ENDTURN_THROAT_CHOP:
                if (gDisableStructs[gActiveBattler].throatChopTimer && --gDisableStructs[gActiveBattler].throatChopTimer == 0)
                {
                    BattleScriptExecute(BattleScript_ThroatChopEndTurn);
                    effect++;
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_SLOW_START:
                if (gDisableStructs[gActiveBattler].slowStartTimer
                    && --gDisableStructs[gActiveBattler].slowStartTimer == 0
                    && ability == ABILITY_SLOW_START)
                {
                    BattleScriptExecute(BattleScript_SlowStartEnds);
                    effect++;
                }
                gBattleStruct->turnEffectsTracker++;
                break;
            case ENDTURN_BATTLER_COUNT:  // done
                gBattleStruct->turnEffectsTracker = 0;
                ++gBattleStruct->turnEffectsBattlerId;
                break;
            }
            if (effect)
                return effect;
        }
    }
    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_x20);
    return 0;
}

bool8 HandleWishPerishSongOnTurnEnd(void)
{
    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_x20);
    switch (gBattleStruct->wishPerishSongState)
    {
    case 0:
        while (gBattleStruct->wishPerishSongBattlerId < gBattlersCount)
        {
            gActiveBattler = gBattleStruct->wishPerishSongBattlerId;
            if (gAbsentBattlerFlags & gBitTable[gActiveBattler])
            {
                ++gBattleStruct->wishPerishSongBattlerId;
                continue;
            }
            ++gBattleStruct->wishPerishSongBattlerId;
            if (gWishFutureKnock.futureSightCounter[gActiveBattler] != 0
             && --gWishFutureKnock.futureSightCounter[gActiveBattler] == 0
             && gBattleMons[gActiveBattler].hp != 0)
            {
                if (gWishFutureKnock.futureSightMove[gActiveBattler] == MOVE_FUTURE_SIGHT)
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                else
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                PREPARE_MOVE_BUFFER(gBattleTextBuff1, gWishFutureKnock.futureSightMove[gActiveBattler]);
                gBattlerTarget = gActiveBattler;
                gBattlerAttacker = gWishFutureKnock.futureSightAttacker[gActiveBattler];
                gBattleMoveDamage = gWishFutureKnock.futureSightDmg[gActiveBattler];
                gSpecialStatuses[gBattlerTarget].dmg = 0xFFFF;
                BattleScriptExecute(BattleScript_MonTookFutureAttack);
                return TRUE;
            }
        }
        {
            u8 *state = &gBattleStruct->wishPerishSongState;

            *state = 1;
            gBattleStruct->wishPerishSongBattlerId = 0;
        }
        // fall through
    case 1:
        while (gBattleStruct->wishPerishSongBattlerId < gBattlersCount)
        {
            gActiveBattler = gBattlerAttacker = gBattlerByTurnOrder[gBattleStruct->wishPerishSongBattlerId];
            if (gAbsentBattlerFlags & gBitTable[gActiveBattler])
            {
                ++gBattleStruct->wishPerishSongBattlerId;
                continue;
            }
            ++gBattleStruct->wishPerishSongBattlerId;
            if (gStatuses3[gActiveBattler] & STATUS3_PERISH_SONG)
            {
                PREPARE_BYTE_NUMBER_BUFFER(gBattleTextBuff1, 1, gDisableStructs[gActiveBattler].perishSongTimer);
                if (gDisableStructs[gActiveBattler].perishSongTimer == 0)
                {
                    gStatuses3[gActiveBattler] &= ~STATUS3_PERISH_SONG;
                    gBattleMoveDamage = gBattleMons[gActiveBattler].hp;
                    gBattlescriptCurrInstr = BattleScript_PerishSongTakesLife;
                }
                else
                {
                    --gDisableStructs[gActiveBattler].perishSongTimer;
                    gBattlescriptCurrInstr = BattleScript_PerishSongCountGoesDown;
                }
                BattleScriptExecute(gBattlescriptCurrInstr);
                return TRUE;
            }
        }
        break;
    }
    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_x20);
    return FALSE;
}

#define FAINTED_ACTIONS_MAX_CASE 7

bool8 HandleFaintedMonActions(void) //important looking here can prob find what need 
{ // for setup switch in ability reset when opponent pokemon is fainted
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
        return FALSE;
    do
    {
        s32 i;
        switch (gBattleStruct->faintedActionsState)
        {
        case 0:
            gBattleStruct->faintedActionsBattlerId = 0;
            ++gBattleStruct->faintedActionsState;
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gAbsentBattlerFlags & gBitTable[i] && !HasNoMonsToSwitch(i, 6, 6))
                    gAbsentBattlerFlags &= ~(gBitTable[i]);
            }
            // fall through
        case 1:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->faintedActionsBattlerId;
                if (gBattleMons[gBattleStruct->faintedActionsBattlerId].hp == 0
                 && !(gBattleStruct->givenExpMons & gBitTable[gBattlerPartyIndexes[gBattleStruct->faintedActionsBattlerId]])
                 && !(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBattlerId]))
                {
                    BattleScriptExecute(BattleScript_GiveExp);
                    gBattleStruct->faintedActionsState = 2;
                    return TRUE;
                }
            } while (++gBattleStruct->faintedActionsBattlerId != gBattlersCount);
            gBattleStruct->faintedActionsState = 3;
            break;
        case 2:
            sub_8017434(gBattlerFainted);
            if (++gBattleStruct->faintedActionsBattlerId == gBattlersCount)
                gBattleStruct->faintedActionsState = 3;
            else
                gBattleStruct->faintedActionsState = 1;
            break;
        case 3:
            gBattleStruct->faintedActionsBattlerId = 0;
            ++gBattleStruct->faintedActionsState;
            // fall through
        case 4:
            do
            {
                gBattlerFainted = gBattlerTarget = gBattleStruct->faintedActionsBattlerId;
                if (gBattleMons[gBattleStruct->faintedActionsBattlerId].hp == 0
                 && !(gAbsentBattlerFlags & gBitTable[gBattleStruct->faintedActionsBattlerId]))
                {
                    BattleScriptExecute(BattleScript_HandleFaintedMon);
                    gBattleStruct->faintedActionsState = 5;
                    return TRUE;
                }
            } while (++gBattleStruct->faintedActionsBattlerId != gBattlersCount);
            gBattleStruct->faintedActionsState = 6;
            break;
        case 5:
            if (++gBattleStruct->faintedActionsBattlerId == gBattlersCount)
                gBattleStruct->faintedActionsState = 6;
            else
                gBattleStruct->faintedActionsState = 4;
            break;
        case 6:
            if (AbilityBattleEffects(ABILITYEFFECT_INTIMIDATE1, 0, 0, 0, 0) || AbilityBattleEffects(ABILITYEFFECT_TRACE, 0, 0, 0, 0) || ItemBattleEffects(1, 0, TRUE) || AbilityBattleEffects(ABILITYEFFECT_FORECAST, 0, 0, 0, 0))
                return TRUE;
            ++gBattleStruct->faintedActionsState;
            break;
        case FAINTED_ACTIONS_MAX_CASE:
            break;
        }
    } while (gBattleStruct->faintedActionsState != FAINTED_ACTIONS_MAX_CASE);
    return FALSE;
}

void TryClearRageStatuses(void)
{
    s32 i;

    for (i = 0; i < gBattlersCount; ++i)
        if ((gBattleMons[i].status2 & STATUS2_RAGE) && gChosenMoveByBattler[i] != MOVE_RAGE)
            gBattleMons[i].status2 &= ~(STATUS2_RAGE);
}

enum
{
    CANCELLER_FLAGS,
    CANCELLER_ASLEEP,
    CANCELLER_FROZEN,
    CANCELLER_TRUANT,
    CANCELLER_RECHARGE,
    CANCELLER_FLINCH,
    CANCELLER_DISABLED,
    CANCELLER_GRAVITY,
    CANCELLER_HEAL_BLOCKED,
    CANCELLER_TAUNTED,
    CANCELLER_IMPRISONED,
    CANCELLER_CONFUSED,
    CANCELLER_PARALYSED,
    CANCELLER_GHOST,
    CANCELLER_IN_LOVE,
    CANCELLER_BIDE,
    CANCELLER_THAW,
    CANCELLER_POWDER_MOVE,
    CANCELLER_POWDER_STATUS,
    CANCELLER_THROAT_CHOP,
    CANCELLER_END,
    CANCELLER_PSYCHIC_TERRAIN,
    CANCELLER_END2,
};

u8 AtkCanceller_UnableToUseMove(void)
{
    u8 effect = 0;
    s32 *bideDmg = &gBattleScripting.bideDmg;

    do
    {
        switch (gBattleStruct->atkCancellerTracker)
        {
        case CANCELLER_FLAGS: // flags clear
            gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_DESTINY_BOND);
            gStatuses3[gBattlerAttacker] &= ~(STATUS3_GRUDGE);
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_ASLEEP: // check being asleep
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP)
            {
                if (UproarWakeUpCheck(gBattlerAttacker))
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP);
                    gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedWokeUp;
                    effect = 2;
                }
                else
                {
                    u8 toSub;

                    if (gBattleMons[gBattlerAttacker].ability == ABILITY_EARLY_BIRD)
                        toSub = 2;
                    else
                        toSub = 1;
                    if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP) < toSub)
                        gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP);
                    else
                        gBattleMons[gBattlerAttacker].status1 -= toSub;
                    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP)
                    {
                        if (gCurrentMove != MOVE_SNORE && gCurrentMove != MOVE_SLEEP_TALK)
                        {
                            gBattlescriptCurrInstr = BattleScript_MoveUsedIsAsleep;
                            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                            effect = 2;
                        }
                    }
                    else
                    {
                        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
                        BattleScriptPushCursor();
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                        gBattlescriptCurrInstr = BattleScript_MoveUsedWokeUp;
                        effect = 2;
                    }
                }
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_FROZEN: // check being frozen
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
            {
                if (Random() % 5)
                {
                    if (gBattleMoves[gCurrentMove].effect != EFFECT_THAW_HIT) // unfreezing via a move effect happens in case 13
                    {
                        gBattlescriptCurrInstr = BattleScript_MoveUsedIsFrozen;
                        gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                    }
                    else
                    {
                        ++gBattleStruct->atkCancellerTracker;
                        break;
                    }
                }
                else // unfreeze
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_FREEZE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedUnfroze;
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                }
                effect = 2;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_TRUANT: // truant
            if (gBattleMons[gBattlerAttacker].ability == ABILITY_TRUANT && gDisableStructs[gBattlerAttacker].truantCounter)
            {
                CancelMultiTurnMoves(gBattlerAttacker);
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
                gMoveResultFlags |= MOVE_RESULT_MISSED;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_RECHARGE: // recharge
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RECHARGE)
            {
                gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RECHARGE);
                gDisableStructs[gBattlerAttacker].rechargeTimer = 0;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedMustRecharge;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_FLINCH: // flinch
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_FLINCHED)
            {
                gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_FLINCHED);
                gProtectStructs[gBattlerAttacker].flinchImmobility = 1;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedFlinched;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_DISABLED: // disabled move
            if (gDisableStructs[gBattlerAttacker].disabledMove == gCurrentMove && gDisableStructs[gBattlerAttacker].disabledMove != MOVE_NONE)
            {
                gProtectStructs[gBattlerAttacker].usedDisabledMove = 1;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsDisabled;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_HEAL_BLOCKED:
            if (gStatuses3[gBattlerAttacker] & STATUS3_HEAL_BLOCK && IsHealBlockPreventingMove(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedHealBlockedMove = 1;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedHealBlockPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_GRAVITY:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && IsGravityPreventingMove(gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedGravityPreventedMove = 1;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedGravityPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_TAUNTED: // taunt
            if (gDisableStructs[gBattlerAttacker].tauntTimer && gBattleMoves[gCurrentMove].power == 0)
            {
                gProtectStructs[gBattlerAttacker].usedTauntedMove = 1;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsTaunted;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_IMPRISONED: // imprisoned
            if (GetImprisonedMovesCount(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedImprisonedMove = 1;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsImprisoned;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_CONFUSED: // confusion  ODDS confusion and change effect here
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION)
            {
                --gBattleMons[gBattlerAttacker].status2;
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION)
                {
                    if (Random() & 1)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                        BattleScriptPushCursor();
                    }
                    else // confusion dmg
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                        gBattlerTarget = gBattlerAttacker;
                        gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerAttacker], MOVE_POUND, 0, 40, 0, gBattlerAttacker, gBattlerAttacker);
                        gProtectStructs[gBattlerAttacker].confusionSelfDmg = 1;
                        gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    }
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfused;
                }
                else // snapped out of confusion
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfusedNoMore;
                }
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_PARALYSED: // paralysis
            if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_PARALYSIS) && (Random() % 4) == 0)
            {
                gProtectStructs[gBattlerAttacker].prlzImmobility = 1;
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsParalyzed;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_GHOST: // GHOST in pokemon tower
            if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags))
            {
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    gBattlescriptCurrInstr = BattleScript_TooScaredToMove;
                else
                    gBattlescriptCurrInstr = BattleScript_GhostGetOutGetOut;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_IN_LOVE: // infatuation
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION)
            {
                gBattleScripting.battler = CountTrailingZeroBits((gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION) >> 0x10);
                if (Random() & 1)
                {
                    BattleScriptPushCursor();
                }
                else
                {
                    BattleScriptPush(BattleScript_MoveUsedIsInLoveCantAttack);
                    gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    gProtectStructs[gBattlerAttacker].loveImmobility = 1;
                    CancelMultiTurnMoves(gBattlerAttacker);
                }
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsInLove;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_BIDE: // bide
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)
            {
                gBattleMons[gBattlerAttacker].status2 -= 0x100;
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)
                {
                    gBattlescriptCurrInstr = BattleScript_BideStoringEnergy;
                }
                else
                {
                    if (gTakenDmg[gBattlerAttacker])
                    {
                        gCurrentMove = MOVE_BIDE;
                        *bideDmg = gTakenDmg[gBattlerAttacker] * 2;
                        gBattlerTarget = gTakenDmgByBattler[gBattlerAttacker];
                        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                            gBattlerTarget = GetMoveTarget(MOVE_BIDE, 1);
                        gBattlescriptCurrInstr = BattleScript_BideAttack;
                    }
                    else
                    {
                        gBattlescriptCurrInstr = BattleScript_BideNoEnergyToAttack;
                    }
                }
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_THAW: // move thawing
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE)
            {
                if (gBattleMoves[gCurrentMove].effect == EFFECT_THAW_HIT)
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_FREEZE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedUnfroze;
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                }
                effect = 2;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_POWDER_MOVE:
            if (gBattleMoves[gCurrentMove].flags & FLAG_POWDER)
            {
                if ((IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GRASS))
                    || GetBattlerAbility(gBattlerTarget) == ABILITY_OVERCOAT)
                {
                    gBattlerAbility = gBattlerTarget;
                    effect = 1;
                }
                else if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_SAFETY_GOOGLES)
                {
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_SAFETY_GOOGLES);
                    effect = 1;
                }

                if (effect)
                    gBattlescriptCurrInstr = BattleScript_PowderMoveNoEffect;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_POWDER_STATUS:
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_POWDER)
            { // gonna need to look into this, but looks like some sort of explosive damage from igniting powder?
                u32 moveType;
                GET_MOVE_TYPE(gCurrentMove, moveType);
                if (moveType == TYPE_FIRE)
                {
                    gProtectStructs[gBattlerAttacker].powderSelfDmg = 1;
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedPowder;
                    effect = 1;
                }
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_THROAT_CHOP:
            if (gDisableStructs[gBattlerAttacker].throatChopTimer && gBattleMoves[gCurrentMove].flags & FLAG_SOUND)
            {
                gProtectStructs[gBattlerAttacker].usedThroatChopPreventedMove = 1;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsThroatChopPrevented;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_END: // put spirit lock in , before this same chance as paralysis
            break;
        }

    } while (gBattleStruct->atkCancellerTracker != CANCELLER_END && !effect);
    if (effect == 2)
    {
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
        MarkBattlerForControllerExec(gActiveBattler);
    }
    return effect;
}


// After Protean Activation.

u8 AtkCanceller_UnableToUseMove2(void)
{
    u8 effect = 0;

    do
    {
        switch (gBattleStruct->atkCancellerTracker)
        {
        case CANCELLER_END:
            gBattleStruct->atkCancellerTracker++;
        case CANCELLER_PSYCHIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN
                && IsBattlerGrounded(gBattlerTarget)
                && GetChosenMovePriority(gBattlerAttacker) > 0
                && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(gBattlerTarget))
            {
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedPsychicTerrainPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            gBattleStruct->atkCancellerTracker++;
            break;
        case CANCELLER_END2:
            break;
        }

    } while (gBattleStruct->atkCancellerTracker != CANCELLER_END2 && effect == 0);

    return effect;
}

bool32 IsBattlerGrounded(u8 battlerId)
{
    if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_IRON_BALL)
        return TRUE;
    else if (gFieldStatuses & STATUS_FIELD_GRAVITY)
        return TRUE;
    else if (gStatuses3[battlerId] & STATUS3_ROOTED)
        return TRUE;
    else if (gStatuses3[battlerId] & STATUS3_SMACKED_DOWN)
        return TRUE; //important roost change
    else if (IS_BATTLER_OF_TYPE(battlerId, TYPE_FLYING) && (gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_ROOST))
        return TRUE; //hope this set up right/works
    //according to Mcgriffin need make flying & roost flag true statement
    //as else at bottom just means not flyign or has roost flag
    else if (gStatuses3[battlerId] & STATUS3_TELEKINESIS)
        return FALSE;
    else if (gStatuses3[battlerId] & STATUS3_MAGNET_RISE)
        return FALSE;
    else if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_AIR_BALLOON)
        return FALSE;
    else if (GetBattlerAbility(battlerId) == ABILITY_LEVITATE)
        return FALSE;
    else if (IS_BATTLER_OF_TYPE(battlerId, TYPE_FLYING) && !(gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_ROOST))
        return FALSE;

    else
        return TRUE;
}

bool8 HasNoMonsToSwitch(u8 battler, u8 partyIdBattlerOn1, u8 partyIdBattlerOn2)
{
    u8 playerId, flankId;
    struct Pokemon *party;
    s32 i;

    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
    {
        return FALSE;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        {
            playerId = GetBattlerMultiplayerId(battler);
            if (GetBattlerSide(battler) == B_SIDE_PLAYER)
                party = gPlayerParty;
            else
                party = gEnemyParty;
            flankId = GetLinkTrainerFlankId(playerId);
            for (i = flankId * 3; i < flankId * 3 + 3; ++i)
            {
                if (GetMonData(&party[i], MON_DATA_HP) != 0
                 && GetMonData(&party[i], MON_DATA_SPECIES2) != SPECIES_NONE
                 && GetMonData(&party[i], MON_DATA_SPECIES2) != SPECIES_EGG)
                    break;
            }
            return (i == flankId * 3 + 3);
        }
        else
        {
            if (GetBattlerSide(battler) == B_SIDE_OPPONENT)
            {
                playerId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                flankId = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
                party = gEnemyParty;
            }
            else
            {
                playerId = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
                flankId = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
                party = gPlayerParty;
            }
            if (partyIdBattlerOn1 == PARTY_SIZE)
                partyIdBattlerOn1 = gBattlerPartyIndexes[playerId];
            if (partyIdBattlerOn2 == PARTY_SIZE)
                partyIdBattlerOn2 = gBattlerPartyIndexes[flankId];
            for (i = 0; i < PARTY_SIZE; ++i)
            {
                if (GetMonData(&party[i], MON_DATA_HP) != 0
                 && GetMonData(&party[i], MON_DATA_SPECIES2) != SPECIES_NONE
                 && GetMonData(&party[i], MON_DATA_SPECIES2) != SPECIES_EGG
                 && i != partyIdBattlerOn1
                 && i != partyIdBattlerOn2
                 && i != *(gBattleStruct->monToSwitchIntoId + playerId)
                 && i != flankId[gBattleStruct->monToSwitchIntoId])
                    break;
            }
            return (i == PARTY_SIZE);
        }
    }
}

enum
{
    CASTFORM_NO_CHANGE,
    CASTFORM_TO_NORMAL,
    CASTFORM_TO_FIRE,
    CASTFORM_TO_WATER,
    CASTFORM_TO_ICE,
};

u8 CastformDataTypeChange(u8 battler)
{
    u8 formChange = 0;
    if (gBattleMons[battler].species == SPECIES_CASTFORM)
    {
        if (gBattleMons[battler].ability != ABILITY_FORECAST || gBattleMons[battler].hp == 0)
            return CASTFORM_NO_CHANGE;
        if (!WEATHER_HAS_EFFECT && !IS_BATTLER_OF_TYPE(battler, TYPE_NORMAL))
        {
            SET_BATTLER_TYPE(battler, TYPE_NORMAL);
            return CASTFORM_TO_NORMAL;
        }
        if (!WEATHER_HAS_EFFECT)
            return CASTFORM_NO_CHANGE;
        if (!(gBattleWeather & (WEATHER_RAIN_ANY | WEATHER_SUN_ANY | WEATHER_HAIL_ANY)) && !IS_BATTLER_OF_TYPE(battler, TYPE_NORMAL))
        {
            SET_BATTLER_TYPE(battler, TYPE_NORMAL);
            formChange = CASTFORM_TO_NORMAL;
        }
        if (gBattleWeather & WEATHER_SUN_ANY && !IS_BATTLER_OF_TYPE(battler, TYPE_FIRE))
        {
            SET_BATTLER_TYPE(battler, TYPE_FIRE);
            formChange = CASTFORM_TO_FIRE;
        }
        if (gBattleWeather & WEATHER_RAIN_ANY && !IS_BATTLER_OF_TYPE(battler, TYPE_WATER))
        {
            SET_BATTLER_TYPE(battler, TYPE_WATER);
            formChange = CASTFORM_TO_WATER;
        }
        if (gBattleWeather & WEATHER_HAIL_ANY && !IS_BATTLER_OF_TYPE(battler, TYPE_ICE))
        {
            SET_BATTLER_TYPE(battler, TYPE_ICE);
            formChange = CASTFORM_TO_ICE;
        }
    }
    else if (gBattleMons[battler].species == SPECIES_CHERRIM)
    {
        if (gBattleMons[battler].ability != ABILITY_FLOWER_GIFT || gBattleMons[battler].hp == 0)
            formChange = 0;
        else if (gBattleMonForms[battler] == 0 && WEATHER_HAS_EFFECT && gBattleWeather & WEATHER_SUN_ANY)
            formChange = 2;
        else if (gBattleMonForms[battler] != 0 && (!WEATHER_HAS_EFFECT || !(gBattleWeather & WEATHER_SUN_ANY)))
            formChange = 1;
    }
        return formChange;
    
} //check to make sure cherrim form change works

static const u16 sWeatherFlagsInfo[][3] =
{
    [ENUM_WEATHER_RAIN] = {WEATHER_RAIN_TEMPORARY, WEATHER_RAIN_PERMANENT, HOLD_EFFECT_DAMP_ROCK},
    [ENUM_WEATHER_SUN] = {WEATHER_SUN_TEMPORARY, WEATHER_SUN_PERMANENT, HOLD_EFFECT_HEAT_ROCK},
    [ENUM_WEATHER_SANDSTORM] = {WEATHER_SANDSTORM_TEMPORARY, WEATHER_SANDSTORM_PERMANENT, HOLD_EFFECT_SMOOTH_ROCK},
    [ENUM_WEATHER_HAIL] = {WEATHER_HAIL, HOLD_EFFECT_ICY_ROCK},
};

/*static const u16 sSwitchAbilities[][9] =
{
[REPEAT_SWITCH_IN] = {ABILITY_MOLD_BREAKER, ABILITY_TERAVOLT, ABILITY_TURBOBLAZE, ABILITY_UNNERVE, ABILITY_ANTICIPATION, ABILITY_FRISK, ABILITY_FOREWARN, ABILITY_INTIMIDATE, ABILITY_TRACE}
};*/
//ok set it up correctly so now it doesn't break connections

bool32 TryChangeBattleWeather(u8 battler, u32 weatherEnumId, bool32 viaAbility)
{
    if (viaAbility
        && !(gBattleWeather & sWeatherFlagsInfo[weatherEnumId][1]))
    {
        gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1]);
        return TRUE;
    }
    else if (!(gBattleWeather & (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1])))
    {
        gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0]);
        if (GetBattlerHoldEffect(battler, TRUE) == sWeatherFlagsInfo[weatherEnumId][2])
            gWishFutureKnock.weatherDuration = 8;
        else
            gWishFutureKnock.weatherDuration = 5;

        return TRUE;
    }

    return FALSE;
}

static bool32 TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer)
{
    if (!(gFieldStatuses & statusFlag))
    {
        gFieldStatuses &= ~(STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | EFFECT_ELECTRIC_TERRAIN | EFFECT_PSYCHIC_TERRAIN);
        gFieldStatuses |= statusFlag;

        if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_TERRAIN_EXTENDER)
            *timer = 8;
        else
            *timer = 5;

        gBattlerAttacker = gBattleScripting.battler = battler;
        return TRUE;
    }

    return FALSE;
}

static bool32 ShouldChangeFormHpBased(u32 battler)
{
    // Ability,     form >, form <=, hp divided
    static const u16 forms[][4] =
    {
        {ABILITY_ZEN_MODE, SPECIES_DARMANITAN, SPECIES_DARMANITAN_ZEN_MODE, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR, SPECIES_MINIOR_CORE_RED, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_BLUE, SPECIES_MINIOR_CORE_BLUE, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_GREEN, SPECIES_MINIOR_CORE_GREEN, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_INDIGO, SPECIES_MINIOR_CORE_INDIGO, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_ORANGE, SPECIES_MINIOR_CORE_ORANGE, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_VIOLET, SPECIES_MINIOR_CORE_VIOLET, 2},
        {ABILITY_SHIELDS_DOWN, SPECIES_MINIOR_METEOR_YELLOW, SPECIES_MINIOR_CORE_YELLOW, 2},
        {ABILITY_SCHOOLING, SPECIES_WISHIWASHI_SCHOOL, SPECIES_WISHIWASHI, 4},
    };
    u32 i;

    for (i = 0; i < NELEMS(forms); i++) //try see if nelems will work here, or I need to use emerald array count
    {
        if (gBattleMons[battler].ability == forms[i][0])
        {
            if (gBattleMons[battler].species == forms[i][2]
                && gBattleMons[battler].hp > gBattleMons[battler].maxHP / forms[i][3])
            {
                gBattleMons[battler].species = forms[i][1];
                return TRUE;
            }
            if (gBattleMons[battler].species == forms[i][1]
                && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / forms[i][3])
            {
                gBattleMons[battler].species = forms[i][2];
                return TRUE;
            }
        }
    }
    return FALSE;
}


static u8 ForewarnChooseMove(u32 battler)
{
    struct Forewarn {
        u8 battlerId;
        u8 power;
        u16 moveId;
    };
    u32 i, j, bestId, count;
    struct Forewarn *data = malloc(sizeof(struct Forewarn) * MAX_BATTLERS_COUNT * MAX_MON_MOVES);

    // Put all moves
    for (count = 0, i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerSide(i) != GetBattlerSide(battler))
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[i].moves[j] == MOVE_NONE)
                    continue;
                data[count].moveId = gBattleMons[i].moves[j];
                data[count].battlerId = i;
                switch (gBattleMoves[data[count].moveId].effect)
                {
                case EFFECT_OHKO:
                    data[count].power = 150;
                    break;
                case EFFECT_COUNTER:
                case EFFECT_MIRROR_COAT:
                case EFFECT_METAL_BURST:
                    data[count].power = 120;
                    break;
                default:
                    if (gBattleMoves[data[count].moveId].power == 1)
                        data[count].power = 80;
                    else
                        data[count].power = gBattleMoves[data[count].moveId].power;
                    break;
                }
                count++;
            }
        }
    }

    for (bestId = 0, i = 1; i < count; i++)
    {
        if (data[i].power > data[bestId].power)
            bestId = i;
        else if (data[i].power == data[bestId].power && Random() & 1)
            bestId = i;
    }

    gBattlerTarget = data[bestId].battlerId;
    PREPARE_MOVE_BUFFER(gBattleTextBuff1, data[bestId].moveId)
        RecordKnownMove(gBattlerTarget, data[bestId].moveId);

    free(data);
}

#include "battle_script_commands.c"

// alright includes here look wrong, but they're actually fine.
u8 AbilityBattleEffects(u8 caseID, u8 battler, u16 ability, u8 special, u16 moveArg) // for this function pick through all the battle scripts if it isn't there add it.
{
    u8 effect = 0;
    struct Pokemon *pokeAtk;
    struct Pokemon *pokeDef;
    u16 speciesAtk;
    u16 speciesDef;
    u32 pidAtk;
    u32 pidDef;

    if (gBattlerAttacker >= gBattlersCount)
        gBattlerAttacker = battler;
    if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
        pokeAtk = &gPlayerParty[gBattlerPartyIndexes[gBattlerAttacker]];
    else
        pokeAtk = &gEnemyParty[gBattlerPartyIndexes[gBattlerAttacker]];
    if (gBattlerTarget >= gBattlersCount)
        gBattlerTarget = battler;
    if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
        pokeDef = &gPlayerParty[gBattlerPartyIndexes[gBattlerTarget]];
    else
        pokeDef = &gEnemyParty[gBattlerPartyIndexes[gBattlerTarget]];
    speciesAtk = GetMonData(pokeAtk, MON_DATA_SPECIES);
    pidAtk = GetMonData(pokeAtk, MON_DATA_PERSONALITY);
    speciesDef = GetMonData(pokeDef, MON_DATA_SPECIES);
    pidDef = GetMonData(pokeDef, MON_DATA_PERSONALITY);
    if (!(gBattleTypeFlags & BATTLE_TYPE_SAFARI)) // Why isn't that check done at the beginning?
    {
        u8 moveType;
        s32 i, j;
        u8 side;
        u8 target1;

        if (special)
            gLastUsedAbility = special;
        else
            gLastUsedAbility = gBattleMons[battler].ability;
        if (!moveArg)
            moveArg = gCurrentMove;
        GET_MOVE_TYPE(moveArg, moveType);
        if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags)
         && (gLastUsedAbility == ABILITY_INTIMIDATE || gLastUsedAbility == ABILITY_TRACE))
            return effect;
        switch (caseID)
        {
        case ABILITYEFFECT_ON_SWITCHIN: // 0
            if (gBattlerAttacker >= gBattlersCount)
                gBattlerAttacker = battler;
            switch (gLastUsedAbility)
            {
            case ABILITYEFFECT_SWITCH_IN_WEATHER:
                switch (GetCurrentWeather())
                {
                case WEATHER_RAIN:
                case WEATHER_RAIN_THUNDERSTORM:
                case WEATHER_DOWNPOUR:
                    if (!(gBattleWeather & WEATHER_RAIN_ANY))
                    {
                        gBattleWeather = (WEATHER_RAIN_TEMPORARY | WEATHER_RAIN_PERMANENT);
                        gBattleScripting.animArg1 = B_ANIM_RAIN_CONTINUES;
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    break;
                case WEATHER_SANDSTORM:
                    if (!(gBattleWeather & WEATHER_SANDSTORM_ANY))
                    {
                        gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                        gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    break;
                case WEATHER_DROUGHT:
                    if (!(gBattleWeather & WEATHER_SUN_ANY))
                    {
                        gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                        gBattleScripting.animArg1 = B_ANIM_SUN_CONTINUES;
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    break;
                }
                if (effect)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = GetCurrentWeather();
                    BattleScriptPushCursorAndCallback(BattleScript_OverworldWeatherStarts);
                }
                break;
            case ABILITY_IMPOSTER:
                if (IsBattlerAlive(BATTLE_OPPOSITE(battler))
                    && !(gBattleMons[BATTLE_OPPOSITE(battler)].status2 & (STATUS2_TRANSFORMED | STATUS2_SUBSTITUTE))
                    && !(gBattleMons[battler].status2 & STATUS2_TRANSFORMED)
                    && !(gBattleStruct->illusion[BATTLE_OPPOSITE(battler)].on)
                    && !(gStatuses3[BATTLE_OPPOSITE(battler)] & STATUS3_SEMI_INVULNERABLE))
                {
                    gBattlerTarget = BATTLE_OPPOSITE(battler);
                    BattleScriptPushCursorAndCallback(BattleScript_ImposterActivates);
                    effect++; // code ahs error attempt to fix by using trace targetting
                }//set target 1  target 2 position then assign either based on battler positoin on player player party & enemy party side
                break;
            case ABILITY_MOLD_BREAKER:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_MOLDBREAKER;
                    gSpecialStatuses[battler].switchInAbilityDone = 1; //  switchindone is when it equals 1, so I guess I'll neeed to set this field ot 0
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_TERAVOLT:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_TERAVOLT;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_TURBOBLAZE:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_TURBOBLAZE;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_SLOW_START:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gDisableStructs[battler].slowStartTimer = 5;
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_SLOWSTART;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_UNNERVE:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_UNNERVE;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_ANTICIPATION:
                if (!gSpecialStatuses[battler].switchInAbilityDone) // make sure to change switch in ability ot reset on each opponent switch
                {
                    u32 side = GetBattlerSide(battler);

                    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
                    {
                        if (IsBattlerAlive(i) && side != GetBattlerSide(i))
                        {
                            for (j = 0; j < MAX_MON_MOVES; j++)
                            {
                                moveArg = gBattleMons[i].moves[j]; //replaced move w moveArg should be fine
                                GET_MOVE_TYPE(moveArg, moveType);
                                if (gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE || gMoveResultFlags & MOVE_RESULT_ONE_HIT_KO || gBattleMoves[move].effect == EFFECT_OHKO)
                                { // this value may not work, since oh-ko is not an effectiveness but an effect in firered (i think that's different)
                                    //so I may change it to move result super effect or move.effect == EFFECT_OHKO
                                    effect++;
                                    break;
                                }
                            }
                        }
                    }

                    if (effect)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_ANTICIPATION;
                        gSpecialStatuses[battler].switchInAbilityDone = 1;
                        BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    }
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_FRISK:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_FriskActivates); // Try activate
                    effect++;
                }
                return effect; // Note: It returns effect as to not record the ability if Frisk does not activate.

                if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
            case ABILITY_FOREWARN:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    ForewarnChooseMove(battler);
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_FOREWARN;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_DOWNLOAD:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    u32 statId, opposingBattler;
                    u32 opposingDef = 0, opposingSpDef = 0;

                    opposingBattler = BATTLE_OPPOSITE(battler);
                    for (i = 0; i < 2; opposingBattler ^= BIT_SIDE, i++)
                    {
                        if (IsBattlerAlive(opposingBattler))
                        {
                            opposingDef += gBattleMons[opposingBattler].defense
                                * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][0]
                                / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_DEF]][1];
                            opposingSpDef += gBattleMons[opposingBattler].spDefense
                                * gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][0]
                                / gStatStageRatios[gBattleMons[opposingBattler].statStages[STAT_SPDEF]][1];
                        }
                    }

                    if (opposingDef < opposingSpDef)
                        statId = STAT_ATK;
                    else
                        statId = STAT_SPATK;

                    gSpecialStatuses[battler].switchInAbilityDone = 1;

                    if (gBattleMons[battler].statStages[statId] != 12)
                    {
                        gBattleMons[battler].statStages[statId]++;
                        SET_STATCHANGER(statId, 1, FALSE);
                        PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerAbilityStatRaiseEnd3);
                        effect++;
                    }
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].switchInAbilityDone
                    && Random() % 3 == 0)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].switchInAbilityDone = 0;
                }
                break;
            case ABILITY_DARK_AURA:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_DARKAURA;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_FAIRY_AURA:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_FAIRYAURA;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_AURA_BREAK:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_AURABREAK;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_COMATOSE:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_COMATOSE;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_SCREEN_CLEANER:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = MULTI_SWITCHIN_SCREENCLEANER;
                    gSpecialStatuses[battler].switchInAbilityDone = 1;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    effect++;
                }
                break;
            case ABILITY_DRIZZLE:
                if (!(gBattleWeather & WEATHER_RAIN_PERMANENT))
                {
                    gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_SAND_STREAM:
                if (!(gBattleWeather & WEATHER_SANDSTORM_PERMANENT))
                {
                    gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_DROUGHT:
                if (!(gBattleWeather & WEATHER_SUN_PERMANENT))
                {
                    gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_SNOW_WARNING:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_HAIL, TRUE))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_SnowWarningActivates);
                    effect++;
                }
                break;
            case ABILITY_ELECTRIC_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN, &gFieldTimers.electricTerrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_ElectricSurgeActivates);
                    effect++;
                }
                break;
            case ABILITY_GRASSY_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_GRASSY_TERRAIN, &gFieldTimers.grassyTerrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_GrassySurgeActivates);
                    effect++;
                }
                break;
            case ABILITY_MISTY_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_MISTY_TERRAIN, &gFieldTimers.mistyTerrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_MistySurgeActivates);
                    effect++;
                }
                break;
            case ABILITY_PSYCHIC_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN, &gFieldTimers.psychicTerrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_PsychicSurgeActivates);
                    effect++;
                }
                break;
            case ABILITY_INTIMIDATE:
                if (!(gSpecialStatuses[battler].intimidatedMon))
                {
                    gStatuses3[battler] |= STATUS3_INTIMIDATE_POKES;
                    gSpecialStatuses[battler].intimidatedMon = 1;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].intimidatedMon)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].intimidatedMon = 0;
                }
                break;
            case ABILITY_FLOWER_GIFT:
            case ABILITY_FORECAST: //plan setup weather to check if first turn, else if all battlers have completed actions. ok is working on start now.
                effect = CastformDataTypeChange(battler);// I think if I copy the function values to an else if using random chance to activate & turn ended it should work how I want
                if (effect != 0)//i,e if (gCurrentTurnActionNumber >= gBattlersCount) && (gBattleMons[battler].hp != 0)  do value and random as before but a higher number and include
                {// value for setting weather timers to 0, prob should use if for each weather type, and link it with its respective timer.
                    BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                    gBattleScripting.battler = battler;
                    *(&gBattleStruct->formToChangeInto) = effect - 1;// sandstorm effect is continuing oddly, before I change "while" I'm trying line up
                    // the dotted linebetween brackets,  I'm assuming for some reason misalignemnt broke it 
                }// before I had 4 separate random functions, so If I used while it could have been because they were returning multiple values at once.

                if (gBattleMons[battler].hp != 0 && ability == ABILITY_FORECAST) // don't want to change weather every turn but I do want it to change, mid battle, and trigger after all battlers have had their turns. think that's turn action count > battlers count.
                { //I want it to trigger once at start of battle I think, but maybe not. Some people could make use of "normal" form castform. i guess
                    u16 value;// trying to store the value returned by random function in one field as per phoenixbound's suggestion. since it seemed I was calling 5 separate random functions
                    value = Random() % 4; //and having random() in the if function was causing the effect to only work if true, which means a non 0 value, so a 3/4 chance.
                    if (value == 0) {
                        // confusing but will test next, if  doesn't work may try usign turn order or turn count tracker
                        gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY); // so there's a chance every turn  for the weather to be changed. 
                        BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates); // that should fit my plans for the effect.
                        gBattleScripting.battler = battler;
                        ++effect; //seems to be working, but I think I need to change my hail value to use the battlescript "sethail" right now its starting on battle end, and not doing it began to hail
                    }// instead its using hail continues, other than that it works now.
                    if (value == 1) {
                        gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                        BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);//still not triggering every battle, also for some reason rain script is retriggering
                        gBattleScripting.battler = battler;// on opponent ability too. I guess it has to do with gbattlescripting.battler  since battler is attacker?
                        ++effect;

                    }
                    if (value == 2) {
                        gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                        BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    if (value == 3) {
                        gBattleWeather = WEATHER_HAIL; //ok weather is still a little trippy, effect isn't triggering all the time, battle script isn't right yet,
                        BattleScriptPushCursorAndCallback(BattleScript_HailActivates); // for some reason hail animation isnt playing, but the form change works.
                        gBattleScripting.battler = battler;// made battlescript change, got it working now.
                        ++effect;

                    }
                }
                break;
            case ABILITY_TRACE:
                if (!(gSpecialStatuses[battler].traced))
                {
                    gStatuses3[battler] |= STATUS3_TRACE;
                    gSpecialStatuses[battler].traced = 1;
                }
                else if (atk4E_switchinanim && gSpecialStatuses[battler].traced)
                {
                    gSpecialStatuses[BATTLE_OPPOSITE(battler)].traced = 0; // don't forget need to add more complex decision tree for who to trace
                }
                break;
            case ABILITY_CLOUD_NINE:
            case ABILITY_AIR_LOCK:
                {
                    for (target1 = 0; target1 < gBattlersCount; ++target1)
                    {
                        effect = CastformDataTypeChange(target1);
                        if (effect != 0)
                        {
                            BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                            gBattleScripting.battler = target1;
                            *(&gBattleStruct->formToChangeInto) = effect - 1;
                            break;
                        }
                    }
                }
                break;
            /*case ABILITY_NUISANCE: 
                { //since abilituy effect macro has proven to have an affect on weather/how the function activates, I may need to move this to an existing category.
                     
                    u16 moveBattler = 0;
                    u16 move; //not sure why this shouldn't just be u16 but pokemon.c line 3166    ah because its "move" not "moves"  gbattlemoves[move] is u16 in script commands though
                    s8 priority; //this threw up a syntax error before I rearranged type listing, into order it appears in function
                    moveBattler = gBattleMons[gBattlerAttacker].moves[*(gBattleStruct->chosenMovePositions + gBattlerAttacker)];
                    priority = gBattleMoves[moveBattler].priority;
                //also power is better than using gbattlemovedamage as movedamage takes all other factors into account to boost damage.
                     //apparently gchosenmoves refers to move used previously, not a buffer for the move you will use in your turn, so gcurrentmove is best here.
                //movearg works for other abiities so I'll try it, combined with gcurrentmove
                   
                    if (gBattleMoves[move].power <= 60)
                      priority = priority + 3; //tried putting in parenthesis that may ado it
                 // taken from battle_main.c function GetWhoStrikesFirst
                
                }
                break;*/
            }
            break;
        case ABILITYEFFECT_ENDTURN: // 1
            if (gBattleMons[battler].hp != 0)
            {
                gBattlerAttacker = battler;
                switch (gLastUsedAbility)
                {
                case ABILITY_HARVEST:
                    if (((WEATHER_HAS_EFFECT && gBattleWeather & WEATHER_SUN_ANY) || Random() % 2 == 0)
                        && gBattleMons[battler].item == ITEM_NONE
                        && gBattleStruct->changedItems[battler] == ITEM_NONE
                        && ItemId_GetPocket(gBattleStruct->usedHeldItems[battler]) == POCKET_BERRY_POUCH)
                    {
                        gLastUsedItem = gBattleStruct->changedItems[battler] = gBattleStruct->usedHeldItems[battler];
                        gBattleStruct->usedHeldItems[battler] = ITEM_NONE;
                        BattleScriptPushCursorAndCallback(BattleScript_HarvestActivates);
                        effect++;
                    }
                    break;
                case ABILITY_DRY_SKIN:
                    if (gBattleWeather & WEATHER_SUN_ANY)
                        goto SOLAR_POWER_HP_DROP;
                    // Dry Skin works similarly to Rain Dish in Rain
                case ABILITY_RAIN_DISH:
                    if (WEATHER_HAS_EFFECT && (gBattleWeather & WEATHER_RAIN_ANY)
                     && gBattleMons[battler].maxHP > gBattleMons[battler].hp
                     && !(gStatuses3[battler] & STATUS3_HEAL_BLOCK))
                    {
                        gLastUsedAbility = ABILITY_RAIN_DISH; // why
                        BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 16;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    break;
                case ABILITY_HYDRATION:
                    if (WEATHER_HAS_EFFECT
                        && (gBattleWeather & WEATHER_RAIN_ANY)
                        && gBattleMons[battler].status1 & STATUS1_ANY)
                    {
                        goto ABILITY_HEAL_MON_STATUS;
                    }
                    break;
                case ABILITY_SHED_SKIN:
                    if ((gBattleMons[battler].status1 & STATUS1_ANY) && (Random() % 3) == 0)
                    {
                    ABILITY_HEAL_MON_STATUS:
                        if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
                            StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                        if (gBattleMons[battler].status1 & STATUS1_SLEEP)
                            StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
                            StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                        if (gBattleMons[battler].status1 & STATUS1_BURN)
                            StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        if (gBattleMons[battler].status1 & STATUS1_FREEZE)
                            StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                        gBattleMons[battler].status1 = 0;
                        gBattleMons[battler].status2 &= ~(STATUS2_NIGHTMARE);  // fix nightmare glitch
                        gBattleScripting.battler = gActiveBattler = battler;
                        BattleScriptPushCursorAndCallback(BattleScript_ShedSkinActivates);
                        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                        MarkBattlerForControllerExec(gActiveBattler);
                        ++effect;
                    }
                    break;
                case ABILITY_SPEED_BOOST:
                    if (gBattleMons[battler].statStages[STAT_SPEED] < 0xC && gDisableStructs[battler].isFirstTurn != 2)
                    {
                        ++gBattleMons[battler].statStages[STAT_SPEED];
                        gBattleScripting.animArg1 = 0x11;
                        gBattleScripting.animArg2 = 0;
                        BattleScriptPushCursorAndCallback(BattleScript_SpeedBoostActivates);
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    break;
                case ABILITY_MOODY:
                    if (gDisableStructs[battler].isFirstTurn != 2)
                    {
                        u32 validToRaise = 0, validToLower = 0;
                        u32 statsNum = NUM_BATTLE_STATS;

                        for (i = STAT_ATK; i < statsNum; i++)
                        {
                            if (gBattleMons[battler].statStages[i] != 0)
                                validToLower |= gBitTable[i];
                            if (gBattleMons[battler].statStages[i] != 12)
                                validToRaise |= gBitTable[i];
                        }

                        if (validToLower != 0 || validToRaise != 0) // Can lower one stat, or can raise one stat
                        {
                            gBattleScripting.statChanger = gBattleScripting.savedStatChanger = 0; // for raising and lowering stat respectively
                            if (validToRaise != 0) // Find stat to raise
                            {
                                do
                                {
                                    i = (Random() % statsNum) + STAT_ATK;
                                } while (!(validToRaise & gBitTable[i]));
                                SET_STATCHANGER(i, 2, FALSE);
                                validToLower &= ~(gBitTable[i]); // Can't lower the same stat as raising.
                            }
                            if (validToLower != 0) // Find stat to lower
                            {
                                do
                                {
                                    i = (Random() % statsNum) + STAT_ATK;
                                } while (!(validToLower & gBitTable[i]));
                                SET_STATCHANGER2(gBattleScripting.savedStatChanger, i, 1, TRUE);
                            }
                            BattleScriptPushCursorAndCallback(BattleScript_MoodyActivates);
                            effect++;
                        }
                    }
                    break;
                case ABILITY_TRUANT:
                    gDisableStructs[gBattlerAttacker].truantCounter ^= 1;
                    break;
                case ABILITY_BAD_DREAMS:
                    if (gBattleMons[battler].status1 & STATUS1_SLEEP
                        || gBattleMons[BATTLE_OPPOSITE(battler)].status1 & STATUS1_SLEEP
                        || GetBattlerAbility(battler) == ABILITY_COMATOSE
                        || GetBattlerAbility(BATTLE_OPPOSITE(battler)) == ABILITY_COMATOSE)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_BadDreamsActivates);
                        effect++;
                    }
                    break;
                SOLAR_POWER_HP_DROP:
                case ABILITY_SOLAR_POWER:
                    if (WEATHER_HAS_EFFECT && gBattleWeather & WEATHER_SUN_ANY)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        effect++;
                    }
                    break;
                case ABILITY_HEALER:
                    gBattleScripting.battler = BATTLE_PARTNER(battler);
                    if (IsBattlerAlive(gBattleScripting.battler)
                        && gBattleMons[gBattleScripting.battler].status1 & STATUS1_ANY
                        && (Random() % 100) < 30)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_HealerActivates);
                        effect++;
                    }
                    break;
                case ABILITY_SCHOOLING:
                    if (gBattleMons[battler].level < 20)
                        break;
                case ABILITY_ZEN_MODE:
                case ABILITY_SHIELDS_DOWN:
                    if ((effect = ShouldChangeFormHpBased(battler)))
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                    break;
                case ABILITY_POWER_CONSTRUCT:
                    if ((gBattleMons[battler].species == SPECIES_ZYGARDE || gBattleMons[battler].species == SPECIES_ZYGARDE_10)
                        && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2)
                    {
                        gBattleStruct->changedSpecies[gBattlerPartyIndexes[battler]] = gBattleMons[battler].species;
                        gBattleMons[battler].species = SPECIES_ZYGARDE_COMPLETE;
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                        effect++;
                    }
                    break;
                case ABILITY_BALL_FETCH:
                    if (gBattleMons[battler].item == ITEM_NONE
                        && gBattleResults.catchAttempts[gLastUsedBall - ITEM_ULTRA_BALL] >= 1
                        && !gHasFetchedBall)
                    {
                        gBattleScripting.battler = battler;
                        BtlController_EmitSetMonData(0, REQUEST_HELDITEM_BATTLE, 0, 2, &gLastUsedBall);
                        MarkBattlerForControllerExec(battler);
                        gHasFetchedBall = TRUE;
                        gLastUsedItem = gLastUsedBall;
                        BattleScriptPushCursorAndCallback(BattleScript_BallFetch);
                        effect++;
                    }
                    break;
                case ABILITY_FORECAST: //plan setup weather to check if first turn, else if all battlers have completed actions. ok is working on start now.
                    effect = CastformDataTypeChange(battler);// I think if I copy the function values to an else if using random chance to activate & turn ended it should work how I want
                    if (effect != 0)//i,e if (gCurrentTurnActionNumber >= gBattlersCount) && (gBattleMons[battler].hp != 0)  do value and random as before but a higher number and include
                    {// value for setting weather timers to 0, prob should use if for each weather type, and link it with its respective timer.
                        BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                        gBattleScripting.battler = battler;
                        *(&gBattleStruct->formToChangeInto) = effect - 1;// sandstorm effect is continuing oddly, before I change "while" I'm trying line up
                    }// the dotted linebetween brackets,  I'm assuming for some reason misalignemnt broke it 
                    if (gCurrentTurnActionNumber >= gBattlersCount
                        && Random() % 2 == 0)
                    { // trying to make it not switch every turn, and find a good balance.
                        u16 value2;// trying to store the value returned by random function in one field as per phoenixbound's suggestion. since it seemed I was calling 5 separate random functions
                        value2 = Random() % 5;
                        if (value2 == 0
                            && gBattleWeather != (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY)) {
                            gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                            BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                            gBattleScripting.battler = battler;
                            ++effect;
                        }
                        if (value2 == 1
                            && gBattleWeather != (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY)) {
                            gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                            BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);
                            gBattleScripting.battler = battler;
                            ++effect;

                        }
                        if (value2 == 2
                            && gBattleWeather != (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY)) {
                            gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                            BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                            gBattleScripting.battler = battler;
                            ++effect;
                        }
                        if (value2 == 3
                            && gBattleWeather != WEATHER_HAIL) {
                            gBattleWeather = WEATHER_HAIL;
                            BattleScriptPushCursorAndCallback(BattleScript_HailActivates);
                            gBattleScripting.battler = battler;// made battlescript change, got it working now.
                            ++effect;

                        }
                        if (value2 == 4
                            && gBattleWeather == WEATHER_ANY)
                        {
                            gWishFutureKnock.weatherDuration = 0;

                           /* if (gBattleWeather == WEATHER_RAIN_ANY)
                            {
                                
                                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                                BattleScriptPushCursorAndCallback(BattleScript_RainContinuesOrEnds);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_SANDSTORM_ANY) {
                                --gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SandStormHailEnds);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_SUN_ANY) {
                                --gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SunlightFaded);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_HAIL_ANY) {
                                --gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SandStormHailEnds);
                                gBattleScripting.battler = battler;
                                ++effect;

                            }*/

                        }



                    }
                    break;
                }
                
            }
            break;
        case ABILITYEFFECT_MOVES_BLOCK: // 2
            if ((gLastUsedAbility == ABILITY_SOUNDPROOF && gBattleMoves[moveArg].flags & FLAG_SOUND)
                || (gLastUsedAbility == ABILITY_BULLETPROOF && gBattleMoves[moveArg].flags & FLAG_BALLISTIC))
            {
                for (i = 0; sSoundMovesTable[i] != 0xFFFF; ++i)
                    if (sSoundMovesTable[i] == moveArg)
                        break;
                if (sSoundMovesTable[i] != 0xFFFF)
                {
                    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                        gHitMarker |= HITMARKER_NO_PPDEDUCT;
                    gBattlescriptCurrInstr = BattleScript_SoundproofProtected;
                    effect = 1;
                }
                else if ((((gLastUsedAbility == ABILITY_DAZZLING || gLastUsedAbility == ABILITY_QUEENLY_MAJESTY
                    || (IsBattlerAlive(battler ^= BIT_FLANK)
                        && ((GetBattlerAbility(battler) == ABILITY_DAZZLING) || GetBattlerAbility(battler) == ABILITY_QUEENLY_MAJESTY)))
                    ))
                    && GetChosenMovePriority(gBattlerAttacker) > 0
                    && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(battler))
                {
                    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                        gHitMarker |= HITMARKER_NO_PPDEDUCT;
                    gBattlescriptCurrInstr = BattleScript_DazzlingProtected;
                    effect = 1;
                }
            }
            break;
        case ABILITYEFFECT_ABSORBING: // 3
            if (moveArg)
            {
                u8 statId;
                switch (gLastUsedAbility)
                {
                case ABILITY_VOLT_ABSORB:
                    if (moveType == TYPE_ELECTRIC && gBattleMoves[moveArg].power != 0)
                    {
                        if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain;
                        else
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain_PPLoss;
                        effect = 1;
                    }
                    break;
                case ABILITY_DRY_SKIN:
                case ABILITY_WATER_ABSORB:
                    if (moveType == TYPE_WATER && gBattleMoves[moveArg].power != 0)
                    {
                        if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain;
                        else
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain_PPLoss;
                        effect = 1;
                    }
                    break;
                case ABILITY_MOTOR_DRIVE:
                    if (moveType == TYPE_ELECTRIC)
                        effect = 2, statId = STAT_SPEED;
                    break;
                case ABILITY_LIGHTNING_ROD:
                    if (moveType == TYPE_ELECTRIC)
                        effect = 2, statId = STAT_SPATK;
                    break;
                case ABILITY_STORM_DRAIN:
                    if (moveType == TYPE_WATER)
                        effect = 2, statId = STAT_SPATK;
                    break;
                case ABILITY_SAP_SIPPER:
                    if (moveType == TYPE_GRASS)
                        effect = 2, statId = STAT_ATK;
                    break;
                case ABILITY_FLASH_FIRE:
                    if (moveType == TYPE_FIRE && !(gBattleMons[battler].status1 & STATUS1_FREEZE))
                    {
                        if (!(gBattleResources->flags->flags[battler] & RESOURCE_FLAG_FLASH_FIRE))
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                            if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost;
                            else
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost_PPLoss;
                            gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_FLASH_FIRE;
                            effect = 2;
                        }
                        else
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                            if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost;
                            else
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost_PPLoss;
                            effect = 2;
                        }
                    }
                    break;
                }
                if (effect == 1)
                {
                    if (gBattleMons[battler].maxHP == gBattleMons[battler].hp && STATUS3_HEAL_BLOCK)
                    {
                        if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                        else
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                    }
                }
                else if (effect == 2) // Boost Stat ability;
                {
                    if (gBattleMons[battler].statStages[statId] == 0xC)
                    {
                        if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                        else
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                    }
                    else
                    {
                        if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                            gBattlescriptCurrInstr = BattleScript_MoveStatDrain;
                        else
                            gBattlescriptCurrInstr = BattleScript_MoveStatDrain_PPLoss;

                        SET_STATCHANGER(statId, 1, FALSE);
                        gBattleMons[battler].statStages[statId]++;
                        PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                    }
                }
            }
            break;
        case ABILITYEFFECT_MOVE_END: // Think contact abilities.
            switch (gLastUsedAbility)
            {
            case ABILITY_JUSTIFIED:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && moveType == TYPE_DARK
                    && gBattleMons[battler].statStages[STAT_ATK] != 12)
                {
                    SET_STATCHANGER(STAT_ATK, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_RATTLED:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST)
                    && gBattleMons[battler].statStages[STAT_SPEED] != 12)
                {
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_WATER_COMPACTION:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && moveType == TYPE_WATER
                    && gBattleMons[battler].statStages[STAT_DEF] != 12)
                {
                    SET_STATCHANGER(STAT_DEF, 2, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_STAMINA:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && gBattleMons[battler].statStages[STAT_DEF] != 12)
                {
                    SET_STATCHANGER(STAT_DEF, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_BERSERK:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    // Had more than half of hp before, now has less
                    && gBattleStruct->hpBefore[battler] > gBattleMons[battler].maxHP / 2
                    && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                    && (gMultiHitCounter == 0 || gMultiHitCounter == 1) //guess this is to ensure the effect triggers when move ends
                    && !(GetBattlerAbility(gBattlerAttacker) == ABILITY_SHEER_FORCE && gBattleMoves[gCurrentMove].flags & FLAG_SHEER_FORCE_BOOST)
                    && gBattleMons[battler].statStages[STAT_SPATK] != 12)
                {
                    SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_EMERGENCY_EXIT:
            case ABILITY_WIMP_OUT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    // Had more than half of hp before, now has less
                    && gBattleStruct->hpBefore[battler] > gBattleMons[battler].maxHP / 2
                    && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                    && (gMultiHitCounter == 0 || gMultiHitCounter == 1)
                    && !(GetBattlerAbility(gBattlerAttacker) == ABILITY_SHEER_FORCE && gBattleMoves[gCurrentMove].flags & FLAG_SHEER_FORCE_BOOST)
                    && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
                    && !IsLastAliveMon(battler)) //prevents soft lock, could also be useful for double battle fix?
                    //&& !(gBattleTypeFlags & BATTLE_TYPE_ARENA))
                {
                    gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_EMERGENCY_EXIT;
                    effect++;
                }
                break;
            case ABILITY_WEAK_ARMOR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && IS_MOVE_PHYSICAL(gCurrentMove)
                    && (gBattleMons[battler].statStages[STAT_SPEED] != 12 || gBattleMons[battler].statStages[STAT_DEF] != 0))
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WeakArmorActivates;
                    effect++;
                }
                break;
            case ABILITY_CURSED_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && gDisableStructs[gBattlerAttacker].disabledMove == MOVE_NONE
                    && IsBattlerAlive(gBattlerAttacker)
                    && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
                    && gBattleMons[gBattlerAttacker].pp[gChosenMovePos] != 0
                    && (Random() % 3) == 0)
                {
                    gDisableStructs[gBattlerAttacker].disabledMove = gChosenMove;
                    gDisableStructs[gBattlerAttacker].disableTimer = 4;
                    PREPARE_MOVE_BUFFER(gBattleTextBuff1, gChosenMove);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CursedBodyActivates;
                    effect++;
                }
                break;
            case ABILITY_MUMMY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && IsBattlerAlive(gBattlerAttacker)
                    && TARGET_TURN_DAMAGED
                    && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT))
                {
                    switch (gBattleMons[gBattlerAttacker].ability)
                    {
                    case ABILITY_MUMMY:
                    case ABILITY_BATTLE_BOND:
                    case ABILITY_COMATOSE:
                    case ABILITY_DISGUISE:
                    case ABILITY_MULTITYPE:
                    case ABILITY_POWER_CONSTRUCT:
                    case ABILITY_RKS_SYSTEM:
                    case ABILITY_SCHOOLING:
                    case ABILITY_SHIELDS_DOWN:
                    case ABILITY_STANCE_CHANGE:
                        break;
                    default:
                        gLastUsedAbility = gBattleMons[gBattlerAttacker].ability = ABILITY_MUMMY;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_MummyActivates;
                        effect++;
                        break;
                    }
                }
                break;
            case ABILITY_ANGER_POINT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gCritMultiplier == 2; // looked this should be case where hit is critical
                    && TARGET_TURN_DAMAGED //setting to 2 makes crit, because it defaults to 1
                    && IsBattlerAlive(battler)
                    && gBattleMons[battler].statStages[STAT_ATK] != 12)
                {
                    SET_STATCHANGER(STAT_ATK, 12 - gBattleMons[battler].statStages[STAT_ATK], FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetsStatWasMaxedOut;
                    effect++;
                }
                break;
            case ABILITY_COLOR_CHANGE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && moveArg != MOVE_STRUGGLE
                 && gBattleMoves[moveArg].power != 0
                 && TARGET_TURN_DAMAGED
                 && !IS_BATTLER_OF_TYPE(battler, moveType)
                 && gBattleMons[battler].hp != 0)
                {
                    SET_BATTLER_TYPE(battler, moveType);
                    PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ColorChangeActivates;
                    ++effect;
                }
                break;
            case ABILITY_GOOEY:
            case ABILITY_TANGLING_HAIR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && gBattleMons[gBattlerAttacker].statStages[STAT_SPEED] != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT))
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_SPD_MINUS_1;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    effect++;
                }
                break;
            case ABILITY_ROUGH_SKIN:
            case ABILITY_IRON_BARBS:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && TARGET_TURN_DAMAGED
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT))
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 16; // 8 for later gen
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RoughSkinActivates;
                    ++effect;
                }
                break;
            case ABILITY_AFTERMATH:
                if (!IsAbilityOnField(ABILITY_DAMP)
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp == 0
                    && IsBattlerAlive(gBattlerAttacker)
                    && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT))
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AftermathDmg;
                    effect++;
                }
                break;
            case ABILITY_INNARDS_OUT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp == 0
                    && IsBattlerAlive(gBattlerAttacker))
                {
                    gBattleMoveDamage = gSpecialStatuses[gBattlerTarget].dmg;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AftermathDmg;
                    effect++;
                }
                break;
            case ABILITY_EFFECT_SPORE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && TARGET_TURN_DAMAGED
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                 && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GRASS)
                 && GetBattlerAbility(gBattlerAttacker) != ABILITY_OVERCOAT
                 && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_SAFETY_GOOGLES
                 && (Random() % 2) == 0) // thought % 2 would be too high, but its been good, because of how random number works, it stil feels random and doesn't always trigger in battle
                {
                    do
                        gBattleCommunication[MOVE_EFFECT_BYTE] = Random() % 5;
                    while (gBattleCommunication[MOVE_EFFECT_BYTE] == 0);

                    if (gBattleCommunication[MOVE_EFFECT_BYTE] == MOVE_EFFECT_BURN)
                        gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_PARALYSIS;


                    if (gBattleCommunication[MOVE_EFFECT_BYTE] == MOVE_EFFECT_FREEZE)
                        gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_CONFUSION;
                    gBattleCommunication[MOVE_EFFECT_BYTE] += MOVE_EFFECT_AFFECTS_USER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    ++effect;
                }
                break;
            case ABILITY_POISON_POINT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && TARGET_TURN_DAMAGED
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                 && (Random() % 3) == 0)
                {
                    gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_POISON;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    ++effect;
                }
                break;
            case ABILITY_STATIC:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && TARGET_TURN_DAMAGED
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                 && (Random() % 3) == 0)
                {
                    gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PARALYSIS;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    ++effect;
                }
                break;
            case ABILITY_FLAME_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                 && TARGET_TURN_DAMAGED
                 && (Random() % 3) == 0)
                {
                    gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_BURN;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                    ++effect;
                }
                break;
            case ABILITY_CUTE_CHARM:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gBattleMons[gBattlerAttacker].hp != 0
                 && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                 && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                 && TARGET_TURN_DAMAGED
                 && gBattleMons[gBattlerTarget].hp != 0
                 && (Random() % 3) == 0
                 && gBattleMons[gBattlerAttacker].ability != ABILITY_OBLIVIOUS
                 && !IsAbilityOnSide(gBattlerAttacker, ABILITY_AROMA_VEIL)
                 && GetGenderFromSpeciesAndPersonality(speciesAtk, pidAtk) != GetGenderFromSpeciesAndPersonality(speciesDef, pidDef)
                 && !(gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION)
                 && GetGenderFromSpeciesAndPersonality(speciesAtk, pidAtk) != MON_GENDERLESS
                 && GetGenderFromSpeciesAndPersonality(speciesDef, pidDef) != MON_GENDERLESS)
                {
                    gBattleMons[gBattlerAttacker].status2 |= STATUS2_INFATUATED_WITH(gBattlerTarget);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CuteCharmActivates;
                    ++effect;
                }
                break;
            case ABILITY_ILLUSION:
                if (gBattleStruct->illusion[gBattlerTarget].on && !gBattleStruct->illusion[gBattlerTarget].broken && TARGET_TURN_DAMAGED)
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_IllusionOff;
                    effect++;
                }
                break;
            case ABILITY_COTTON_DOWN:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED)
                {
                    gEffectBattler = gBattlerTarget;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_CottonDownActivates;
                    effect++;
                }
                break;
            case ABILITY_STEAM_ENGINE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && gBattleMons[battler].statStages[STAT_SPEED] != 12
                    && (moveType == TYPE_FIRE || moveType == TYPE_WATER))
                {
                    SET_STATCHANGER(STAT_SPEED, 6, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;
                    effect++;
                }
                break;
            case ABILITY_SAND_SPIT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && !(WEATHER_HAS_EFFECT && gBattleWeather & WEATHER_SANDSTORM_ANY)
                    && TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
                {
                    gBattleScripting.battler = gActiveBattler = battler;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_SandSpitActivates;
                    effect++;
                }
                break;
            case ABILITY_PERISH_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                    && !(gStatuses3[gBattlerAttacker] & STATUS3_PERISH_SONG))
                {
                    if (!(gStatuses3[battler] & STATUS3_PERISH_SONG))
                    {
                        gStatuses3[battler] |= STATUS3_PERISH_SONG;
                        gDisableStructs[battler].perishSongTimer = 3;
                        gDisableStructs[battler].perishSongTimerStartValue = 3;
                    }
                    gStatuses3[gBattlerAttacker] |= STATUS3_PERISH_SONG;
                    gDisableStructs[gBattlerAttacker].perishSongTimer = 3;
                    gDisableStructs[gBattlerAttacker].perishSongTimerStartValue = 3;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_PerishBodyActivates;
                    effect++;
                }
                break;
            }
            break;
            case ABILITYEFFECT_MOVE_END_ATTACKER: // Same as above, but for attacker
                switch (gLastUsedAbility)
                {
                case ABILITY_POISON_TOUCH:
                    if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                        && gBattleMons[gBattlerTarget].hp != 0
                        && !gProtectStructs[gBattlerTarget].confusionSelfDmg
                        && !IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_POISON)
                        && !IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_STEEL)
                        && GetBattlerAbility(gBattlerTarget) != ABILITY_IMMUNITY
                        && !(gBattleMons[gBattlerTarget].status1 & STATUS1_ANY // may remoove these checks, check effect spore & poison point make identical to that
                        && !IsAbilityStatusProtected(gBattlerTarget)
                        && (gBattleMoves[moveArg].flags & FLAG_MAKES_CONTACT)
                        && (Random() % 3) == 0))
                    {
                        gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                        PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                        gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                        effect++;
                    }
                    break;
                }
                break;
            case ABILITYEFFECT_MOVE_END_OTHER: // Abilities that activate on *another* battler's moveend: Dancer, Soul-Heart, Receiver, Symbiosis
                switch (GetBattlerAbility(battler))
                {
                case ABILITY_DANCER:
                    if (IsBattlerAlive(battler)
                        && (gBattleMoves[gCurrentMove].flags & FLAG_DANCE)
                        && !gSpecialStatuses[battler].dancerUsedMove
                        && gBattlerAttacker != battler)
                    {
                        // Set bit and save Dancer mon's original target
                        gSpecialStatuses[battler].dancerUsedMove = 1;
                        gSpecialStatuses[battler].dancerOriginalTarget = *(gBattleStruct->moveTarget + battler) | 0x4;
                        gBattleStruct->atkCancellerTracker = 0;
                        gBattlerAttacker = gBattlerAbility = battler;
                        gCalledMove = gCurrentMove;

                        // Set the target to the original target of the mon that first used a Dance move
                        gBattlerTarget = gBattleScripting.savedBattler & 0x3;

                        // Make sure that the target isn't an ally - if it is, target the original user
                        if (GetBattlerSide(gBattlerTarget) == GetBattlerSide(gBattlerAttacker))
                            gBattlerTarget = (gBattleScripting.savedBattler & 0xF0) >> 4;
                        gHitMarker &= ~(HITMARKER_ATTACKSTRING_PRINTED);
                        BattleScriptExecute(BattleScript_DancerActivates);
                        effect++;
                    }
                    break;
                }
                break;
        case ABILITYEFFECT_IMMUNITY: // 5
            for (battler = 0; battler < gBattlersCount; ++battler)
            {
                switch (gBattleMons[battler].ability)
                {
                case ABILITY_IMMUNITY:
                    if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON | STATUS1_TOXIC_COUNTER))
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_OWN_TEMPO:
                    if (gBattleMons[battler].status2 & STATUS2_CONFUSION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
                        effect = 2;
                    }
                    break;
                case ABILITY_LIMBER:
                    if (gBattleMons[battler].status1 & STATUS1_PARALYSIS)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_INSOMNIA:
                case ABILITY_VITAL_SPIRIT:
                    if (gBattleMons[battler].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battler].status2 &= ~(STATUS2_NIGHTMARE);
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_WATER_VEIL:
                    if (gBattleMons[battler].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_MAGMA_ARMOR:
                    if (gBattleMons[battler].status1 & STATUS1_FREEZE)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_OBLIVIOUS:
                    if (gBattleMons[battler].status2 & STATUS2_INFATUATION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_LoveJpn);
                        effect = 3;
                    }
                    break;
                }
                if (effect)
                {
                    switch (effect)
                    {
                    case 1: // status cleared
                        gBattleMons[battler].status1 = 0;
                        break;
                    case 2: // get rid of confusion
                        gBattleMons[battler].status2 &= ~(STATUS2_CONFUSION);
                        break;
                    case 3: // get rid of infatuation
                        gBattleMons[battler].status2 &= ~(STATUS2_INFATUATION);
                        break;
                    }

                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AbilityCuredStatus;
                    gBattleScripting.battler = battler;
                    gActiveBattler = battler;
                    BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    return effect;
                }
            }
            break;
        case ABILITYEFFECT_FORECAST: // 6
            for (battler = 0; battler < gBattlersCount; ++battler)
            {
                if (gBattleMons[battler].ability == ABILITY_FORECAST)
                {
                    effect = CastformDataTypeChange(battler);
                    if (effect)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                        gBattleScripting.battler = battler;
                        *(&gBattleStruct->formToChangeInto) = effect - 1;
                        return effect;
                    }
                }
            }
            break;
        case ABILITYEFFECT_SYNCHRONIZE: // 7
            if (gLastUsedAbility == ABILITY_SYNCHRONIZE && (gHitMarker & HITMARKER_SYNCHRONISE_EFFECT))
            {
                gHitMarker &= ~(HITMARKER_SYNCHRONISE_EFFECT);
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_TOXIC;
                gBattleCommunication[MOVE_EFFECT_BYTE] = gBattleStruct->synchronizeMoveEffect + MOVE_EFFECT_AFFECTS_USER;
                gBattleScripting.battler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                ++effect;
            }
            break;
        case ABILITYEFFECT_ATK_SYNCHRONIZE: // 8
            if (gLastUsedAbility == ABILITY_SYNCHRONIZE && (gHitMarker & HITMARKER_SYNCHRONISE_EFFECT))
            {
                gHitMarker &= ~(HITMARKER_SYNCHRONISE_EFFECT);
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_TOXIC;
                gBattleCommunication[MOVE_EFFECT_BYTE] = gBattleStruct->synchronizeMoveEffect;
                gBattleScripting.battler = gBattlerAttacker;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                gHitMarker |= HITMARKER_IGNORE_SAFEGUARD;
                ++effect;
            }
            break;
        case ABILITYEFFECT_INTIMIDATE1: // 9
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattleMons[i].ability == ABILITY_INTIMIDATE && gStatuses3[i] & STATUS3_INTIMIDATE_POKES)
                {
                    gLastUsedAbility = ABILITY_INTIMIDATE;
                    gStatuses3[i] &= ~(STATUS3_INTIMIDATE_POKES);
                    BattleScriptPushCursorAndCallback(BattleScript_IntimidateActivatesEnd3);
                    gBattleStruct->intimidateBattler = i;
                    ++effect;
                    break;
                }
            }
            break;
        case ABILITYEFFECT_TRACE: // 11
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattleMons[i].ability == ABILITY_TRACE && (gStatuses3[i] & STATUS3_TRACE))
                {
                    u8 target2;
                    
                    side = (GetBattlerPosition(i) ^ BIT_SIDE) & BIT_SIDE; // side of the opposing pokemon
                    target1 = GetBattlerAtPosition(side);
                    target2 = GetBattlerAtPosition(side + BIT_FLANK); //can possibly use this with getbattler position
                    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) //to make fix for Imposter ability
                    {
                        if (gBattleMons[target1].ability != 0 && gBattleMons[target1].hp != 0
                         && gBattleMons[target2].ability != 0 && gBattleMons[target2].hp != 0)
                        {
                            gActiveBattler = GetBattlerAtPosition(((Random() & 1) * 2) | side);
                            gBattleMons[i].ability = gBattleMons[gActiveBattler].ability;
                            gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                            ++effect;
                        }
                        else if (gBattleMons[target1].ability != 0 && gBattleMons[target1].hp != 0)
                        { // double battle targets 1
                            gActiveBattler = target1;
                            gBattleMons[i].ability = gBattleMons[gActiveBattler].ability;
                            gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                            if (gBattleMons[gActiveBattler].ability == ABILITY_WONDER_GUARD) {
                                gBattleMoveDamage = 1 - gBattleMons[i].hp; // should do damage and leave 1 hp
                            }
                            ++effect;
                            
                        }
                        else if (gBattleMons[target2].ability != 0 && gBattleMons[target2].hp != 0)
                        { // double battle targets 2
                            gActiveBattler = target2;
                            gBattleMons[i].ability = gBattleMons[gActiveBattler].ability;
                            gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                            if (gBattleMons[gActiveBattler].ability == ABILITY_WONDER_GUARD) {
                                gBattleMoveDamage = 1 - gBattleMons[i].hp; // should do damage and leave 1 hp
                                // maybe these if statements should go ABOVE effect?
                            }
                            ++effect;
                            
                        }
                    }
                    else // single battle
                    {
                        gActiveBattler = target1;
                        if (gBattleMons[target1].ability && gBattleMons[target1].hp)
                        {
                            gBattleMons[i].ability = gBattleMons[target1].ability;
                            gLastUsedAbility = gBattleMons[target1].ability;
                            if (gBattleMons[target1].ability == ABILITY_WONDER_GUARD) {
                                gBattleMoveDamage = 1 - gBattleMons[i].hp; // should do damage and leave 1 hp
                            ++effect;
                            
                            }
                        }
                    }
                    if (effect)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_TraceActivates);
                        gStatuses3[i] &= ~(STATUS3_TRACE);
                        gBattleScripting.battler = i;
                        PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gActiveBattler, gBattlerPartyIndexes[gActiveBattler])
                        PREPARE_ABILITY_BUFFER(gBattleTextBuff2, gLastUsedAbility)
                        break;
                    }
                }
            }
            break;
        case ABILITYEFFECT_INTIMIDATE2: // 10
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattleMons[i].ability == ABILITY_INTIMIDATE && (gStatuses3[i] & STATUS3_INTIMIDATE_POKES))
                {
                    gLastUsedAbility = ABILITY_INTIMIDATE;
                    gStatuses3[i] &= ~(STATUS3_INTIMIDATE_POKES);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_IntimidateActivates;
                    gBattleStruct->intimidateBattler = i;
                    ++effect;
                    break;
                }
            }
            break;
        case ABILITYEFFECT_CHECK_OTHER_SIDE: // 12
            side = GetBattlerSide(battler);
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (GetBattlerSide(i) != side && gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    effect = i + 1;
                }
            }
            break;
        case ABILITYEFFECT_CHECK_BATTLER_SIDE: // 13
            side = GetBattlerSide(battler);
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (GetBattlerSide(i) == side && gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    effect = i + 1;
                }
            }
            break;
        case ABILITYEFFECT_FIELD_SPORT: // 14
            switch (gLastUsedAbility)
            {
            case 0xFD: // check this value
                for (i = 0; i < gBattlersCount; ++i)
                    if (gStatuses3[i] & STATUS3_MUDSPORT)
                        effect = i + 1;
                break;
            case 0xFE:
                for (i = 0; i < gBattlersCount; ++i)
                    if (gStatuses3[i] & STATUS3_WATERSPORT)
                        effect = i + 1;
                break;
            default:
                for (i = 0; i < gBattlersCount; ++i)
                {
                    if (gBattleMons[i].ability == ability)
                    {
                        gLastUsedAbility = ability;
                        effect = i + 1;
                    }
                }
                break;
            }
            break;
        case ABILITYEFFECT_CHECK_ON_FIELD: // 19
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattleMons[i].ability == ability && gBattleMons[i].hp != 0)
                {
                    gLastUsedAbility = ability;
                    effect = i + 1;
                }
            }
            break;
        case ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER: // 15
            side = GetBattlerSide(battler);
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (GetBattlerSide(i) != side && gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    effect = i + 1;
                    break;
                }
            }
            if (!effect)
            {
                for (i = 0; i < gBattlersCount; ++i)
                {
                    if (gBattleMons[i].ability == ability && GetBattlerSide(i) == side && i != battler)
                    {
                        gLastUsedAbility = ability;
                        effect = i + 1;
                    }
                }
            }
            break;
        case ABILITYEFFECT_COUNT_OTHER_SIDE: // 16
            side = GetBattlerSide(battler);
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (GetBattlerSide(i) != side && gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    ++effect;
                }
            }
            break;
        case ABILITYEFFECT_COUNT_BATTLER_SIDE: // 17
            side = GetBattlerSide(battler);
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (GetBattlerSide(i) == side && gBattleMons[i].ability == ability)
                {
                    gLastUsedAbility = ability;
                    ++effect;
                }
            }
            break;
        case ABILITYEFFECT_COUNT_ON_FIELD: // 18
            for (i = 0; i < gBattlersCount; ++i)
            {
                if (gBattleMons[i].ability == ability && i != battler)
                {
                    gLastUsedAbility = ability;
                    ++effect;
                }
            }
            break;
        }
        if (effect && caseID < ABILITYEFFECT_CHECK_OTHER_SIDE && gLastUsedAbility != 0xFF)
            RecordAbilityBattle(battler, gLastUsedAbility);
    }
    return effect;
}

void BattleScriptExecute(const u8 *BS_ptr)
{
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands_PopCallbacksStack;
    gCurrentActionFuncId = 0;
}

void BattleScriptPushCursorAndCallback(const u8 *BS_ptr)
{
    BattleScriptPushCursor();
    gBattlescriptCurrInstr = BS_ptr;
    gBattleResources->battleCallbackStack->function[gBattleResources->battleCallbackStack->size++] = gBattleMainFunc;
    gBattleMainFunc = RunBattleScriptCommands;
}

enum
{
    ITEM_NO_EFFECT,
    ITEM_STATUS_CHANGE,
    ITEM_EFFECT_OTHER,
    ITEM_PP_CHANGE,
    ITEM_HP_CHANGE,
    ITEM_STATS_CHANGE,
};

u8 ItemBattleEffects(u8 caseID, u8 battlerId, bool8 moveTurn) // function is from emerald
{
    int i = 0;
    u8 effect = ITEM_NO_EFFECT;
    u8 changedPP = 0;
    u8 battlerHoldEffect, atkHoldEffect, defHoldEffect;
    u8 battlerHoldEffectParam, atkHoldEffectParam, defHoldEffectParam;
    u16 atkItem, defItem;

    gLastUsedItem = gBattleMons[battlerId].item;
    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
    {
        battlerHoldEffect = gEnigmaBerries[battlerId].holdEffect;
        battlerHoldEffectParam = gEnigmaBerries[battlerId].holdEffectParam;
    }
    else
    {
        battlerHoldEffect = ItemId_GetHoldEffect(gLastUsedItem);
        battlerHoldEffectParam = ItemId_GetHoldEffectParam(gLastUsedItem);
    }

    atkItem = gBattleMons[gBattlerAttacker].item;
    if (atkItem == ITEM_ENIGMA_BERRY)
    {
        atkHoldEffect = gEnigmaBerries[gBattlerAttacker].holdEffect;
        atkHoldEffectParam = gEnigmaBerries[gBattlerAttacker].holdEffectParam;
    }
    else
    {
        atkHoldEffect = ItemId_GetHoldEffect(atkItem);
        atkHoldEffectParam = ItemId_GetHoldEffectParam(atkItem);
    }

    // def variables are unused
    defItem = gBattleMons[gBattlerTarget].item;
    if (defItem == ITEM_ENIGMA_BERRY)
    {
        defHoldEffect = gEnigmaBerries[gBattlerTarget].holdEffect;
        defHoldEffectParam = gEnigmaBerries[gBattlerTarget].holdEffectParam;
    }
    else
    {
        defHoldEffect = ItemId_GetHoldEffect(defItem);
        defHoldEffectParam = ItemId_GetHoldEffectParam(defItem);
    }
    switch (caseID)
    {
    case ITEMEFFECT_ON_SWITCH_IN:
        switch (battlerHoldEffect)
        {
        case HOLD_EFFECT_DOUBLE_PRIZE:
            gBattleStruct->moneyMultiplier = 2;
            break;
        case HOLD_EFFECT_RESTORE_STATS:
            for (i = 0; i < NUM_BATTLE_STATS; ++i)
            {
                if (gBattleMons[battlerId].statStages[i] < 6)
                {
                    gBattleMons[battlerId].statStages[i] = 6;
                    effect = ITEM_STATS_CHANGE;
                }
            }
            if (effect)
            {
                gBattleScripting.battler = battlerId;
                gPotentialItemEffectBattler = battlerId;
                gActiveBattler = gBattlerAttacker = battlerId;
                BattleScriptExecute(BattleScript_WhiteHerbEnd2);
            }
            break;
        }
        break;
    case 1:
        if (gBattleMons[battlerId].hp)
        {
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_RESTORE_HP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    gBattleMoveDamage = battlerHoldEffectParam;
                    if (gBattleMons[battlerId].hp + battlerHoldEffectParam > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = 4;
                }
                break;
            case HOLD_EFFECT_RESTORE_PP:
                if (!moveTurn)
                {
                    struct Pokemon *mon;
                    u8 ppBonuses;
                    u16 move;

                    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
                        mon = &gPlayerParty[gBattlerPartyIndexes[battlerId]];
                    else
                        mon = &gEnemyParty[gBattlerPartyIndexes[battlerId]];
                    for (i = 0; i < MAX_MON_MOVES; ++i)
                    {
                        move = GetMonData(mon, MON_DATA_MOVE1 + i);
                        changedPP = GetMonData(mon, MON_DATA_PP1 + i);
                        ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES);
                        if (move && changedPP == 0)
                            break;
                    }
                    if (i != MAX_MON_MOVES)
                    {
                        u8 maxPP = CalculatePPWithBonus(move, ppBonuses, i);
                        if (changedPP + battlerHoldEffectParam > maxPP)
                            changedPP = maxPP;
                        else
                            changedPP = changedPP + battlerHoldEffectParam;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, move);
                        BattleScriptExecute(BattleScript_BerryPPHealEnd2);
                        BtlController_EmitSetMonData(0, i + REQUEST_PPMOVE1_BATTLE, 0, 1, &changedPP);
                        MarkBattlerForControllerExec(gActiveBattler);
                        effect = ITEM_PP_CHANGE;
                    }
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                for (i = 0; i < NUM_BATTLE_STATS; ++i)
                {
                    if (gBattleMons[battlerId].statStages[i] < 6)
                    {
                        gBattleMons[battlerId].statStages[i] = 6;
                        effect = ITEM_STATS_CHANGE;
                    }
                }
                if (effect)
                {
                    gBattleScripting.battler = battlerId;
                    gPotentialItemEffectBattler = battlerId;
                    gActiveBattler = gBattlerAttacker = battlerId;
                    BattleScriptExecute(BattleScript_WhiteHerbEnd2);
                }
                break;
            case HOLD_EFFECT_LEFTOVERS:
                if (gBattleMons[battlerId].hp < gBattleMons[battlerId].maxHP && !moveTurn)
                {
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    BattleScriptExecute(BattleScript_ItemHealHP_End2);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battlerId, battlerHoldEffect);
                }
                break;
            case HOLD_EFFECT_CONFUSE_SPICY:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, FLAVOR_SPICY);
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / battlerHoldEffectParam;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, FLAVOR_SPICY) < 0)
                        BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
                    else
                        BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = ITEM_HP_CHANGE;
                }
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, FLAVOR_DRY);
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / battlerHoldEffectParam;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, FLAVOR_DRY) < 0)
                        BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
                    else
                        BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = ITEM_HP_CHANGE;
                }
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, FLAVOR_SWEET);
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / battlerHoldEffectParam;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, FLAVOR_SWEET) < 0)
                        BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
                    else
                        BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = ITEM_HP_CHANGE;
                }
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, FLAVOR_BITTER);
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / battlerHoldEffectParam;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, FLAVOR_BITTER) < 0)
                        BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
                    else
                        BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = ITEM_HP_CHANGE;
                }
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2 && !moveTurn)
                {
                    PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, FLAVOR_SOUR);
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / battlerHoldEffectParam;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (gBattleMons[battlerId].hp + gBattleMoveDamage > gBattleMons[battlerId].maxHP)
                        gBattleMoveDamage = gBattleMons[battlerId].maxHP - gBattleMons[battlerId].hp;
                    gBattleMoveDamage *= -1;
                    if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, FLAVOR_SOUR) < 0)
                        BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
                    else
                        BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
                    effect = ITEM_HP_CHANGE;
                }
                break;
            case HOLD_EFFECT_ATTACK_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && gBattleMons[battlerId].statStages[STAT_ATK] < 0xC)
                {
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_ATK);
                    PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATROSE);
                    gEffectBattler = battlerId;
                    SET_STATCHANGER(STAT_ATK, 1, FALSE);
                    gBattleScripting.animArg1 = 0xE + STAT_ATK;
                    gBattleScripting.animArg2 = 0;
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && gBattleMons[battlerId].statStages[STAT_DEF] < 0xC)
                {
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_DEF);
                    gEffectBattler = battlerId;
                    SET_STATCHANGER(STAT_DEF, 1, FALSE);
                    gBattleScripting.animArg1 = 0xE + STAT_DEF;
                    gBattleScripting.animArg2 = 0;
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_SPEED_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && gBattleMons[battlerId].statStages[STAT_SPEED] < 0xC)
                {
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPEED);
                    gEffectBattler = battlerId;
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    gBattleScripting.animArg1 = 0xE + STAT_SPEED;
                    gBattleScripting.animArg2 = 0;
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && gBattleMons[battlerId].statStages[STAT_SPATK] < 0xC)
                {
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPATK);
                    gEffectBattler = battlerId;
                    SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                    gBattleScripting.animArg1 = 0xE + STAT_SPATK;
                    gBattleScripting.animArg2 = 0;
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && gBattleMons[battlerId].statStages[STAT_SPDEF] < 0xC)
                {
                    PREPARE_STAT_BUFFER(gBattleTextBuff1, STAT_SPDEF);
                    gEffectBattler = battlerId;
                    SET_STATCHANGER(STAT_SPDEF, 1, FALSE);
                    gBattleScripting.animArg1 = 0xE + STAT_SPDEF;
                    gBattleScripting.animArg2 = 0;
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CRITICAL_UP:
                if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam && !moveTurn && !(gBattleMons[battlerId].status2 & STATUS2_FOCUS_ENERGY))
                {
                    gBattleMons[battlerId].status2 |= STATUS2_FOCUS_ENERGY;
                    BattleScriptExecute(BattleScript_BerryFocusEnergyEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                if (!moveTurn && gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / battlerHoldEffectParam)
                {
                    for (i = 0; i < 5 && gBattleMons[battlerId].statStages[STAT_ATK + i] >= 0xC; ++i);
                    if (i != 5)
                    {
                        do
                            i = Random() % 5;
                        while (gBattleMons[battlerId].statStages[STAT_ATK + i] == 0xC);
                        PREPARE_STAT_BUFFER(gBattleTextBuff1, i + 1);
                        gBattleTextBuff2[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff2[1] = B_BUFF_STRING;
                        gBattleTextBuff2[2] = STRINGID_STATSHARPLY;
                        gBattleTextBuff2[3] = STRINGID_STATSHARPLY >> 8;
                        gBattleTextBuff2[4] = B_BUFF_STRING;
                        gBattleTextBuff2[5] = STRINGID_STATROSE;
                        gBattleTextBuff2[6] = STRINGID_STATROSE >> 8;
                        gBattleTextBuff2[7] = EOS;
                        gEffectBattler = battlerId;
                        SET_STATCHANGER(i + 1, 2, FALSE);
                        gBattleScripting.animArg1 = 0x21 + i + 6;
                        gBattleScripting.animArg2 = 0;
                        BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                        effect = ITEM_STATS_CHANGE;
                    }
                }
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PARALYSIS);
                    BattleScriptExecute(BattleScript_BerryCurePrlzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptExecute(BattleScript_BerryCurePsnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_BURN);
                    BattleScriptExecute(BattleScript_BerryCureBrnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_FREEZE);
                    BattleScriptExecute(BattleScript_BerryCureFrzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_SLEEP);
                    gBattleMons[battlerId].status2 &= ~(STATUS2_NIGHTMARE);
                    BattleScriptExecute(BattleScript_BerryCureSlpEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_CONFUSION:
                if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                {
                    gBattleMons[battlerId].status2 &= ~(STATUS2_CONFUSION);
                    BattleScriptExecute(BattleScript_BerryCureConfusionEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if (gBattleMons[battlerId].status1 & STATUS1_ANY || gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                {
                    i = 0;
                    if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                        ++i;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battlerId].status2 &= ~(STATUS2_NIGHTMARE);
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        ++i;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                        ++i;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        ++i;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                        ++i;
                    }
                    if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
                        ++i;
                    }
                    if (!(i > 1))
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                    gBattleMons[battlerId].status1 = 0;
                    gBattleMons[battlerId].status2 &= ~(STATUS2_CONFUSION);
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_ATTRACT:
                if (gBattleMons[battlerId].status2 & STATUS2_INFATUATION)
                {
                    gBattleMons[battlerId].status2 &= ~(STATUS2_INFATUATION);
                    StringCopy(gBattleTextBuff1, gStatusConditionString_LoveJpn);
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            }
            if (effect)
            {
                gBattleScripting.battler = battlerId;
                gPotentialItemEffectBattler = battlerId;
                gActiveBattler = gBattlerAttacker = battlerId;
                switch (effect)
                {
                case ITEM_STATUS_CHANGE:
                    BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battlerId].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case ITEM_PP_CHANGE:
                    if (!(gBattleMons[battlerId].status2 & STATUS2_TRANSFORMED) && !(gDisableStructs[battlerId].mimickedMoves & gBitTable[i]))
                        gBattleMons[battlerId].pp[i] = changedPP;
                    break;
                }
            }
        }
        break;
    case 2:
        break;
    case ITEMEFFECT_MOVE_END:
        for (battlerId = 0; battlerId < gBattlersCount; ++battlerId)
        {
            gLastUsedItem = gBattleMons[battlerId].item;
            if (gBattleMons[battlerId].item == ITEM_ENIGMA_BERRY)
            {
                battlerHoldEffect = gEnigmaBerries[battlerId].holdEffect;
                battlerHoldEffectParam = gEnigmaBerries[battlerId].holdEffectParam;
            }
            else
            {
                battlerHoldEffect = ItemId_GetHoldEffect(gLastUsedItem);
                battlerHoldEffectParam = ItemId_GetHoldEffectParam(gLastUsedItem);
            }
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PARALYSIS);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureParRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCurePsnRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_BURN);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureBrnRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_FREEZE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureFrzRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_SLEEP);
                    gBattleMons[battlerId].status2 &= ~(STATUS2_NIGHTMARE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureSlpRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_CONFUSION:
                if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                {
                    gBattleMons[battlerId].status2 &= ~(STATUS2_CONFUSION);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureConfusionRet;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_ATTRACT:
                if (gBattleMons[battlerId].status2 & STATUS2_INFATUATION)
                {
                    gBattleMons[battlerId].status2 &= ~(STATUS2_INFATUATION);
                    StringCopy(gBattleTextBuff1, gStatusConditionString_LoveJpn);
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    gBattlescriptCurrInstr = BattleScript_BerryCureChosenStatusRet;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if (gBattleMons[battlerId].status1 & STATUS1_ANY || gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                {
                    if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battlerId].status2 &= ~(STATUS2_NIGHTMARE);
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                    }
                    if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
                    }
                    gBattleMons[battlerId].status1 = 0;
                    gBattleMons[battlerId].status2 &= ~(STATUS2_CONFUSION);
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                    gBattlescriptCurrInstr = BattleScript_BerryCureChosenStatusRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                for (i = 0; i < NUM_BATTLE_STATS; ++i)
                {
                    if (gBattleMons[battlerId].statStages[i] < 6)
                    {
                        gBattleMons[battlerId].statStages[i] = 6;
                        effect = ITEM_STATS_CHANGE;
                    }
                }
                if (effect)
                {
                    gBattleScripting.battler = battlerId;
                    gPotentialItemEffectBattler = battlerId;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WhiteHerbRet;
                    return effect;
                }
                break;
            }
            if (effect)
            {
                gBattleScripting.battler = battlerId;
                gPotentialItemEffectBattler = battlerId;
                gActiveBattler = battlerId;
                BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                MarkBattlerForControllerExec(gActiveBattler);
                break;
            }
        }
        break;
    case ITEMEFFECT_KINGSROCK_SHELLBELL:
        if (gBattleMoveDamage)
        {
            switch (atkHoldEffect)
            {
            case HOLD_EFFECT_FLINCH:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && TARGET_TURN_DAMAGED
                 && (Random() % 100) < battlerHoldEffectParam
                 && gBattleMoves[gCurrentMove].flags & FLAG_KINGS_ROCK_AFFECTED
                 && gBattleMons[gBattlerTarget].hp)
                {
                    gBattleCommunication[MOVE_EFFECT_BYTE] = MOVE_EFFECT_FLINCH;
                    BattleScriptPushCursor();
                    SetMoveEffect(0, 0);
                    BattleScriptPop();
                }
                break;
            case HOLD_EFFECT_SHELL_BELL:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                 && gSpecialStatuses[gBattlerTarget].dmg != 0
                 && gSpecialStatuses[gBattlerTarget].dmg != 0xFFFF
                 && gBattlerAttacker != gBattlerTarget
                 && gBattleMons[gBattlerAttacker].hp != gBattleMons[gBattlerAttacker].maxHP
                 && gBattleMons[gBattlerAttacker].hp != 0)
                {
                    gLastUsedItem = atkItem;
                    gPotentialItemEffectBattler = gBattlerAttacker;
                    gBattleScripting.battler = gBattlerAttacker;
                    gBattleMoveDamage = (gSpecialStatuses[gBattlerTarget].dmg / atkHoldEffectParam) * -1;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = -1;
                    gSpecialStatuses[gBattlerTarget].dmg = 0;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ItemHealHP_Ret;
                    ++effect;
                }
                break;
            }
        }
        break;
    }
    return effect;
}

void ClearFuryCutterDestinyBondGrudge(u8 battlerId)
{
    gDisableStructs[battlerId].furyCutterCounter = 0;
    gBattleMons[battlerId].status2 &= ~(STATUS2_DESTINY_BOND);
    gStatuses3[battlerId] &= ~(STATUS3_GRUDGE);
}

void HandleAction_RunBattleScript(void) // identical to RunBattleScriptCommands
{
    if (!gBattleControllerExecFlags)
        gBattleScriptingCommandsTable[*gBattlescriptCurrInstr]();
}

u8 GetMoveTarget(u16 move, u8 setTarget)
{
    u8 targetBattler = 0;
    u8 moveTarget;
    u8 side;

    if (setTarget)
        moveTarget = setTarget - 1;
    else
        moveTarget = gBattleMoves[move].target;
    switch (moveTarget)
    {
    case MOVE_TARGET_SELECTED:
        side = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE;
        if (gSideTimers[side].followmeTimer && gBattleMons[gSideTimers[side].followmeTarget].hp)
            targetBattler = gSideTimers[side].followmeTarget;
        else
        {
            side = GetBattlerSide(gBattlerAttacker);
            do
            {
                targetBattler = Random() % gBattlersCount;
            } while (targetBattler == gBattlerAttacker || side == GetBattlerSide(targetBattler) || gAbsentBattlerFlags & gBitTable[targetBattler]);
            if (gBattleMoves[move].type == TYPE_ELECTRIC
             && AbilityBattleEffects(ABILITYEFFECT_COUNT_OTHER_SIDE, gBattlerAttacker, ABILITY_LIGHTNING_ROD, 0, 0)
             && gBattleMons[targetBattler].ability != ABILITY_LIGHTNING_ROD)
            {
                targetBattler ^= BIT_FLANK;
                RecordAbilityBattle(targetBattler, gBattleMons[targetBattler].ability);
                gSpecialStatuses[targetBattler].lightningRodRedirected = 1;
            }
        }
        break;
    case MOVE_TARGET_DEPENDS:
    case MOVE_TARGET_BOTH:
    case MOVE_TARGET_FOES_AND_ALLY:
    case MOVE_TARGET_OPPONENTS_FIELD:
        targetBattler = GetBattlerAtPosition((GetBattlerPosition(gBattlerAttacker) & BIT_SIDE) ^ BIT_SIDE);
        if (gAbsentBattlerFlags & gBitTable[targetBattler])
            targetBattler ^= BIT_FLANK;
        break;
    case MOVE_TARGET_RANDOM:
        side = GetBattlerSide(gBattlerAttacker) ^ BIT_SIDE;
        if (gSideTimers[side].followmeTimer && gBattleMons[gSideTimers[side].followmeTarget].hp)
            targetBattler = gSideTimers[side].followmeTarget;
        else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE && moveTarget & MOVE_TARGET_RANDOM)
        {
            if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
            {
                if (Random() & 1)
                    targetBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
                else
                    targetBattler = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            }
            else
            {
                if (Random() & 1)
                    targetBattler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
                else
                    targetBattler = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
            }
            if (gAbsentBattlerFlags & gBitTable[targetBattler])
                targetBattler ^= BIT_FLANK;
        }
        else
            targetBattler = GetBattlerAtPosition((GetBattlerPosition(gBattlerAttacker) & BIT_SIDE) ^ BIT_SIDE);
        break;
    case MOVE_TARGET_USER_OR_SELECTED:
    case MOVE_TARGET_USER:
        targetBattler = gBattlerAttacker;
        break;
    }
    *(gBattleStruct->moveTarget + gBattlerAttacker) = targetBattler;
    return targetBattler;
}

struct Pokemon *GetIllusionMonPtr(u32 battlerId)
{
    if (gBattleStruct->illusion[battlerId].broken)
        return NULL;
    if (!gBattleStruct->illusion[battlerId].set)
    {
        if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
            SetIllusionMon(&gPlayerParty[gBattlerPartyIndexes[battlerId]], battlerId);
        else
            SetIllusionMon(&gEnemyParty[gBattlerPartyIndexes[battlerId]], battlerId);
    }
    if (!gBattleStruct->illusion[battlerId].on)
        return NULL;

    return gBattleStruct->illusion[battlerId].mon;
}

void ClearIllusionMon(u32 battlerId)
{
    memset(&gBattleStruct->illusion[battlerId], 0, sizeof(gBattleStruct->illusion[battlerId]));
}

bool32 SetIllusionMon(struct Pokemon* mon, u32 battlerId)
{
    struct Pokemon* party, * partnerMon;
    s32 i, id;

    gBattleStruct->illusion[battlerId].set = 1;
    if (GetMonAbility(mon) != ABILITY_ILLUSION)
        return FALSE;

    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    if (IsBattlerAlive(BATTLE_PARTNER(battlerId)))
        partnerMon = &party[gBattlerPartyIndexes[BATTLE_PARTNER(battlerId)]];
    else
        partnerMon = mon;

    // Find last alive non-egg pokemon.
    for (i = PARTY_SIZE - 1; i >= 0; i--)
    {
        id = i;
        if (GetMonData(&party[id], MON_DATA_SANITY_HAS_SPECIES)
            && GetMonData(&party[id], MON_DATA_HP)
            && &party[id] != mon
            && &party[id] != partnerMon)
        {
            gBattleStruct->illusion[battlerId].on = 1;
            gBattleStruct->illusion[battlerId].broken = 0;
            gBattleStruct->illusion[battlerId].partyId = id;
            gBattleStruct->illusion[battlerId].mon = &party[id];
            return TRUE;
        }
    }

    return FALSE;
}

static bool32 IsNotEventLegalMewOrDeoxys(u8 battlerId)
{
    if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT
     || (GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES, NULL) != SPECIES_DEOXYS
     && GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES, NULL) != SPECIES_MEW))
        return TRUE;
    return GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_EVENT_LEGAL, NULL);
}

u8 IsMonDisobedient(void)
{
    s32 rnd;
    s32 calc;
    u8 obedienceLevel = 0;

    if ((gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_POKEDUDE)) || GetBattlerSide(gBattlerAttacker) == B_SIDE_OPPONENT)
        return 0;
    if (IsNotEventLegalMewOrDeoxys(gBattlerAttacker)) // only if species is Mew or Deoxys
    {
        if (!IsOtherTrainer(gBattleMons[gBattlerAttacker].otId, gBattleMons[gBattlerAttacker].otName) || FlagGet(FLAG_BADGE08_GET))
            return 0;
        obedienceLevel = 10;
        if (FlagGet(FLAG_BADGE02_GET))
            obedienceLevel = 30;
        if (FlagGet(FLAG_BADGE04_GET))
            obedienceLevel = 50;
        if (FlagGet(FLAG_BADGE06_GET))
            obedienceLevel = 70;
    }
    if (gBattleMons[gBattlerAttacker].level <= obedienceLevel)
        return 0;
    rnd = (Random() & 255);
    calc = (gBattleMons[gBattlerAttacker].level + obedienceLevel) * rnd >> 8;
    if (calc < obedienceLevel)
        return 0;
    // is not obedient
    if (gCurrentMove == MOVE_RAGE)
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RAGE);
    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP && (gCurrentMove == MOVE_SNORE || gCurrentMove == MOVE_SLEEP_TALK))
    {
        gBattlescriptCurrInstr = BattleScript_IgnoresWhileAsleep;
        return 1;
    }
    rnd = (Random() & 255);
    calc = (gBattleMons[gBattlerAttacker].level + obedienceLevel) * rnd >> 8;
    if (calc < obedienceLevel && gCurrentMove != MOVE_FOCUS_PUNCH) // Additional check for focus punch in FR
    {
        calc = CheckMoveLimitations(gBattlerAttacker, gBitTable[gCurrMovePos], 0xFF);
        if (calc == 0xF) // all moves cannot be used
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = Random() & 3;
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
            return 1;
        }
        else // use a random move
        {
            do
                gCurrMovePos = gChosenMovePos = Random() & 3;
            while (gBitTable[gCurrMovePos] & calc);
            gCalledMove = gBattleMons[gBattlerAttacker].moves[gCurrMovePos];
            gBattlescriptCurrInstr = BattleScript_IgnoresAndUsesRandomMove;
            gBattlerTarget = GetMoveTarget(gCalledMove, 0);
            gHitMarker |= HITMARKER_x200000;
            return 2;
        }
    }
    else
    {
        obedienceLevel = gBattleMons[gBattlerAttacker].level - obedienceLevel;
        calc = (Random() & 255);
        if (calc < obedienceLevel && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_ANY) && gBattleMons[gBattlerAttacker].ability != ABILITY_VITAL_SPIRIT && gBattleMons[gBattlerAttacker].ability != ABILITY_INSOMNIA)
        {
            // try putting asleep
            int i;

            for (i = 0; i < gBattlersCount; ++i)
                if (gBattleMons[i].status2 & STATUS2_UPROAR)
                    break;
            if (i == gBattlersCount)
            {
                gBattlescriptCurrInstr = BattleScript_IgnoresAndFallsAsleep;
                return 1;
            }
        }
        calc -= obedienceLevel;
        if (calc < obedienceLevel)
        {
            gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerAttacker], MOVE_POUND, 0, 40, 0, gBattlerAttacker, gBattlerAttacker);
            gBattlerTarget = gBattlerAttacker;
            gBattlescriptCurrInstr = BattleScript_IgnoresAndHitsItself;
            gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
            return 2;
        }
        else
        {
            gBattleCommunication[MULTISTRING_CHOOSER] = Random() & 3;
            gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
            return 1;
        }
    }
}

bool32 IsLastAliveMon(u8 battlerId)
{
    struct Pokemon* party;
    u8 i;
    u8 count = 0;

    if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_HP) != 0)
            count++;
    }

    if (count > 1)
        return FALSE;
    else
        return TRUE;
}

u32 GetBattlerAbility(u8 battlerId)
{
    if (gStatuses3[battlerId] & STATUS3_GASTRO_ACID)
        return ABILITY_NONE;
    else if ((((gBattleMons[gBattlerAttacker].ability == ABILITY_MOLD_BREAKER
        || gBattleMons[gBattlerAttacker].ability == ABILITY_TERAVOLT
        || gBattleMons[gBattlerAttacker].ability == ABILITY_TURBOBLAZE)
        && !(gStatuses3[gBattlerAttacker] & STATUS3_GASTRO_ACID))
        || gBattleMoves[gCurrentMove].flags & FLAG_TARGET_ABILITY_IGNORED)
        && sAbilitiesAffectedByMoldBreaker[gBattleMons[battlerId].ability]
        && gBattlerByTurnOrder[gCurrentTurnActionNumber] == gBattlerAttacker
        && gActionsByTurnOrder[gBattlerByTurnOrder[gBattlerAttacker]] == B_ACTION_USE_MOVE
        && gCurrentTurnActionNumber < gBattlersCount)
        return ABILITY_NONE;
    else
        return gBattleMons[battlerId].ability;
}

u32 GetBattlerHoldEffect(u8 battlerId, bool32 checkNegating)
{
    if (checkNegating)
    {
        if (gStatuses3[battlerId] & STATUS3_EMBARGO)
            return HOLD_EFFECT_NONE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return HOLD_EFFECT_NONE;
        if (gBattleMons[battlerId].ability == ABILITY_KLUTZ && !(gStatuses3[battlerId] & STATUS3_GASTRO_ACID))
            return HOLD_EFFECT_NONE;
    }

    gPotentialItemEffectBattler = battlerId;

    //if (gBattleStruct->debugHoldEffects[battlerId] != 0 && gBattleMons[battlerId].item)
      //  return gBattleStruct->debugHoldEffects[battlerId];
    if (gBattleMons[battlerId].item == ITEM_ENIGMA_BERRY)
        return gEnigmaBerries[battlerId].holdEffect;
    else
        return ItemId_GetHoldEffect(gBattleMons[battlerId].item);
}

u32 GetBattlerHoldEffectParam(u8 battlerId)
{
    if (gBattleMons[battlerId].item == ITEM_ENIGMA_BERRY)
        return gEnigmaBerries[battlerId].holdEffectParam;
    else
        return ItemId_GetHoldEffectParam(gBattleMons[battlerId].item);
}

u8 GetBattleMoveSplit(u32 moveId)
{
    return gBattleMoves[moveId].split;
}


bool32 IsBattlerAlive(u8 battlerId)
{
    if (gBattleMons[battlerId].hp == 0)
        return FALSE;
    else if (battlerId >= gBattlersCount)
        return FALSE;
    else if (gAbsentBattlerFlags & gBitTable[battlerId])
        return FALSE;
    else
        return TRUE;
}
