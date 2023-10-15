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
#include "constants/battle_move_effects.h"
#include "constants/moves.h"
#include "constants/items.h"
#include "constants/weather.h"
#include "constants/abilities.h"
#include "constants/pokemon.h"
#include "constants/hold_effects.h"
#include "pokedex.h"
#include "constants/battle_effects.h"
#include "constants/battle_script_commands.h"
#include "battle_script_commands.h"       
#include "party_menu.h"

//static declarations
static bool32 IsUnnerveAbilityOnOpposingSide(u8 battlerId);
static bool32 IsGravityPreventingMove(u32 move);
static bool32 IsBelchPreventingMove(u32 battler, u32 move);
static bool32 GetMentalHerbEffect(u8 battlerId);
static u16 GetInverseTypeMultiplier(u16 multiplier);
static void MulByTypeEffectiveness(u16 *modifier, u16 move, u8 moveType, u8 battlerDef, u8 defType, u8 battlerAtk, bool32 recordAbilities);
static u16 CalcTypeEffectivenessMultiplierInternal(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities, u16 modifier);
static void UpdateMoveResultFlags(u16 modifier); //only used for accuracycheck command
static void infatuationchecks(void);//cusotm effect used for cupidarrow

static const u16 sSoundMovesTable[] =
{
    MOVE_GROWL, MOVE_ROAR, MOVE_SING, MOVE_SUPERSONIC, MOVE_SCREECH, MOVE_SNORE,
    MOVE_UPROAR, MOVE_METAL_SOUND, MOVE_GRASS_WHISTLE, MOVE_HYPER_VOICE, 0xFFFF
};

const u16 gPercentToModifier[101] =
{
    UQ_4_12(0.00), // 0
    UQ_4_12(0.01), // 1
    UQ_4_12(0.02), // 2
    UQ_4_12(0.03), // 3
    UQ_4_12(0.04), // 4
    UQ_4_12(0.05), // 5
    UQ_4_12(0.06), // 6
    UQ_4_12(0.07), // 7
    UQ_4_12(0.08), // 8
    UQ_4_12(0.09), // 9
    UQ_4_12(0.10), // 10
    UQ_4_12(0.11), // 11
    UQ_4_12(0.12), // 12
    UQ_4_12(0.13), // 13
    UQ_4_12(0.14), // 14
    UQ_4_12(0.15), // 15
    UQ_4_12(0.16), // 16
    UQ_4_12(0.17), // 17
    UQ_4_12(0.18), // 18
    UQ_4_12(0.19), // 19
    UQ_4_12(0.20), // 20
    UQ_4_12(0.21), // 21
    UQ_4_12(0.22), // 22
    UQ_4_12(0.23), // 23
    UQ_4_12(0.24), // 24
    UQ_4_12(0.25), // 25
    UQ_4_12(0.26), // 26
    UQ_4_12(0.27), // 27
    UQ_4_12(0.28), // 28
    UQ_4_12(0.29), // 29
    UQ_4_12(0.30), // 30
    UQ_4_12(0.31), // 31
    UQ_4_12(0.32), // 32
    UQ_4_12(0.33), // 33
    UQ_4_12(0.34), // 34
    UQ_4_12(0.35), // 35
    UQ_4_12(0.36), // 36
    UQ_4_12(0.37), // 37
    UQ_4_12(0.38), // 38
    UQ_4_12(0.39), // 39
    UQ_4_12(0.40), // 40
    UQ_4_12(0.41), // 41
    UQ_4_12(0.42), // 42
    UQ_4_12(0.43), // 43
    UQ_4_12(0.44), // 44
    UQ_4_12(0.45), // 45
    UQ_4_12(0.46), // 46
    UQ_4_12(0.47), // 47
    UQ_4_12(0.48), // 48
    UQ_4_12(0.49), // 49
    UQ_4_12(0.50), // 50
    UQ_4_12(0.51), // 51
    UQ_4_12(0.52), // 52
    UQ_4_12(0.53), // 53
    UQ_4_12(0.54), // 54
    UQ_4_12(0.55), // 55
    UQ_4_12(0.56), // 56
    UQ_4_12(0.57), // 57
    UQ_4_12(0.58), // 58
    UQ_4_12(0.59), // 59
    UQ_4_12(0.60), // 60
    UQ_4_12(0.61), // 61
    UQ_4_12(0.62), // 62
    UQ_4_12(0.63), // 63
    UQ_4_12(0.64), // 64
    UQ_4_12(0.65), // 65
    UQ_4_12(0.66), // 66
    UQ_4_12(0.67), // 67
    UQ_4_12(0.68), // 68
    UQ_4_12(0.69), // 69
    UQ_4_12(0.70), // 70
    UQ_4_12(0.71), // 71
    UQ_4_12(0.72), // 72
    UQ_4_12(0.73), // 73
    UQ_4_12(0.74), // 74
    UQ_4_12(0.75), // 75
    UQ_4_12(0.76), // 76
    UQ_4_12(0.77), // 77
    UQ_4_12(0.78), // 78
    UQ_4_12(0.79), // 79
    UQ_4_12(0.80), // 80
    UQ_4_12(0.81), // 81
    UQ_4_12(0.82), // 82
    UQ_4_12(0.83), // 83
    UQ_4_12(0.84), // 84
    UQ_4_12(0.85), // 85
    UQ_4_12(0.86), // 86
    UQ_4_12(0.87), // 87
    UQ_4_12(0.88), // 88
    UQ_4_12(0.89), // 89
    UQ_4_12(0.90), // 90
    UQ_4_12(0.91), // 91
    UQ_4_12(0.92), // 92
    UQ_4_12(0.93), // 93
    UQ_4_12(0.94), // 94
    UQ_4_12(0.95), // 95
    UQ_4_12(0.96), // 96
    UQ_4_12(0.97), // 97
    UQ_4_12(0.98), // 98
    UQ_4_12(0.99), // 99
    UQ_4_12(1.00), // 100
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
    case BS_ATTACKER_PARTNER:
        ret = BATTLE_PARTNER(gBattlerAttacker);
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
    case BS_FAINTED_LINK_MULTIPLE_1:
        ret = gBattlerFainted;
        break;
    case BS_PLAYER1:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        break;
    case BS_OPPONENT1:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        break;
    case BS_PLAYER2:
        ret = GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT);
        break;
    case BS_OPPONENT2:
        ret = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
        break;
    case BS_ABILITY_BATTLER:
        ret = gBattlerAbility;
        break;
    case 4:
    case 6:
    case 8:
    case 9:
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
                --gBattleMons[attacker].pp[i];
            if (!(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED)
                && !(gDisableStructs[attacker].mimickedMoves & gBitTable[i]))
            {
                gActiveBattler = attacker;
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + i, 0, 1, &gBattleMons[gActiveBattler].pp[i]);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
    }
    else if (gBattleMons[target].ability == ABILITY_HI_PRESSURE)
    {
        for (i = 0; i < MAX_MON_MOVES && gBattleMons[attacker].moves[i] != move; ++i);
        if (i != MAX_MON_MOVES)
        {
            if (gBattleMons[attacker].pp[i]) //current pp not 0
            {
                --gBattleMons[attacker].pp[i];
                --gBattleMons[attacker].pp[i];
            }
                
            if (!(gBattleMons[attacker].status2 & STATUS2_TRANSFORMED)
                && !(gDisableStructs[attacker].mimickedMoves & gBitTable[i]))
            {
                gActiveBattler = attacker;
                BtlController_EmitSetMonData(0, REQUEST_PPMOVE1_BATTLE + i, 0, 1, &gBattleMons[gActiveBattler].pp[i]);
                MarkBattlerForControllerExec(gActiveBattler);
            }
        }
    }//so now that I understand this pretty sure all I have to do is repeat the decrement action -_-
}//since I belive i isn't the value of the pp, but the position of the move who's pp we're lowering

void PressurePPLoseOnUsingImprison(u8 attacker)//it was so simple *facepalm*
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

        else if (atkSide != GetBattlerSide(i) && gBattleMons[i].ability == ABILITY_HI_PRESSURE)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_IMPRISON; ++j);
            if (j != MAX_MON_MOVES)
            {
                imprisonPos = j;
                if (gBattleMons[attacker].pp[j])
                    --gBattleMons[attacker].pp[j];
                --gBattleMons[attacker].pp[j];
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
        else if (gBattleMons[i].ability == ABILITY_HI_PRESSURE && i != attacker)
        {
            for (j = 0; j < MAX_MON_MOVES && gBattleMons[attacker].moves[j] != MOVE_PERISH_SONG; ++j);
            if (j != MAX_MON_MOVES)
            {
                perishSongPos = j;
                if (gBattleMons[attacker].pp[j])
                    --gBattleMons[attacker].pp[j];
                --gBattleMons[attacker].pp[j];
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

// use for cupid's arrow think can just call this function after my conditions are set
//switch in if effect works string is "targtet name fell in love w attcaker name at first sight"
//not sure it'll target correctly  so will make custom effect

static void infatuationchecks(void)//cusotm effect used for cupidarrow
{
    if (GetBattlerAbility(gBattlerTarget) == ABILITY_OBLIVIOUS)
    {
        gBattlescriptCurrInstr = BattleScript_AbilityPreventsMoodShift;
        gLastUsedAbility = ABILITY_OBLIVIOUS;
        RecordAbilityBattle(gBattlerTarget, ABILITY_OBLIVIOUS);
    }
    if (gBattleMons[gBattlerTarget].status2 & STATUS2_INFATUATION)

    {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    }
    else
    {

        gBattleMons[gBattlerTarget].status2 |= STATUS2_INFATUATED_WITH(gBattlerAttacker);
        gBattlescriptCurrInstr += 5;

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

//if wonder guard is in one of these lists (and I want it to be) make sure to add dispirit guard too
//also need to remember to add all custom abilities to these lists as I see fit  !important

static const u8 sAbilitiesAffectedByMoldBreaker[] =
{
    [ABILITY_BATTLE_ARMOR] = 1,
    [ABILITY_CLEAR_BODY] = 1,
    [ABILITY_LIQUID_METAL] = 1,
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
    [ABILITY_MIRROR_ARMOR] = 1,
    [ABILITY_PUNK_ROCK] = 1,
    [ABILITY_ICE_SCALES] = 1,
    [ABILITY_ICE_FACE] = 1,
    [ABILITY_PASTEL_VEIL] = 1,
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

//come back to this when doing move expansion
//changing stench so no longer applicable.
/*static const u8 sMovesNotAffectedByStench[] =
{
    [MOVE_AIR_SLASH] = 1,
    [MOVE_ASTONISH] = 1,
    [MOVE_BITE] = 1,
    [MOVE_BONE_CLUB] = 1,
    [MOVE_DARK_PULSE] = 1,
    [MOVE_DOUBLE_IRON_BASH] = 1,
    [MOVE_DRAGON_RUSH] = 1,
    [MOVE_EXTRASENSORY] = 1,
    [MOVE_FAKE_OUT] = 1,
    [MOVE_FIERY_WRATH] = 1,
    [MOVE_FIRE_FANG] = 1,
    [MOVE_FLING] = 1,
    [MOVE_FLOATY_FALL] = 1,
    [MOVE_HEADBUTT] = 1,
    [MOVE_HEART_STAMP] = 1,
    [MOVE_HYPER_FANG] = 1,
    [MOVE_ICE_FANG] = 1,
    [MOVE_ICICLE_CRASH] = 1,
    [MOVE_IRON_HEAD] = 1,
    [MOVE_NEEDLE_ARM] = 1,
    [MOVE_NONE] = 1,
    [MOVE_ROCK_SLIDE] = 1,
    [MOVE_ROLLING_KICK] = 1,
    [MOVE_SECRET_POWER] = 1,
    [MOVE_SKY_ATTACK] = 1,
    [MOVE_SNORE] = 1,
    [MOVE_STEAMROLLER] = 1,
    [MOVE_STOMP] = 1,
    [MOVE_THUNDER_FANG] = 1,
    [MOVE_TWISTER] = 1,
    [MOVE_WATERFALL] = 1,
    [MOVE_ZEN_HEADBUTT] = 1,
    [MOVE_ZING_ZAP] = 1,
};*/

static const u16 sSkillSwapBannedAbilities[] =
{
    //ABILITY_WONDER_GUARD,
    //ABILITY_DISPIRIT_GUARD,
    ABILITY_MULTITYPE,
    ABILITY_ILLUSION,
    ABILITY_STANCE_CHANGE,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_DISGUISE,
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_NEUTRALIZING_GAS,
    ABILITY_ICE_FACE,
    ABILITY_HUNGER_SWITCH,
    ABILITY_GULP_MISSILE,
};

static const u16 sRolePlayBannedAbilities[] =
{
    ABILITY_TRACE,
    //ABILITY_WONDER_GUARD,
    //ABILITY_DISPIRIT_GUARD,
    ABILITY_FORECAST,
    ABILITY_FLOWER_GIFT,
    ABILITY_MULTITYPE,
    ABILITY_ILLUSION,
    ABILITY_ZEN_MODE,
    ABILITY_IMPOSTER,
    ABILITY_STANCE_CHANGE,
    ABILITY_POWER_OF_ALCHEMY,
    ABILITY_RECEIVER,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_DISGUISE,
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_ICE_FACE,
    ABILITY_HUNGER_SWITCH,
    ABILITY_GULP_MISSILE,
};

//don't understand what this does yet
static const u16 sRolePlayBannedAttackerAbilities[] =
{
    ABILITY_MULTITYPE,
    ABILITY_ZEN_MODE,
    ABILITY_STANCE_CHANGE,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_DISGUISE,
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_ICE_FACE,
    ABILITY_GULP_MISSILE,
};

static const u16 sWorrySeedBannedAbilities[] =
{
    ABILITY_MULTITYPE,
    ABILITY_STANCE_CHANGE,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_DISGUISE,
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_TRUANT,
    ABILITY_ICE_FACE,
    ABILITY_GULP_MISSILE,
};

//or this...
static const u16 sGastroAcidBannedAbilities[] =
{
    ABILITY_AS_ONE_ICE_RIDER,
    ABILITY_AS_ONE_SHADOW_RIDER,
    ABILITY_BATTLE_BOND,
    ABILITY_COMATOSE,
    ABILITY_DISGUISE,
    ABILITY_GULP_MISSILE,
    ABILITY_ICE_FACE,
    ABILITY_MULTITYPE,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_RKS_SYSTEM,
    ABILITY_SCHOOLING,
    ABILITY_SHIELDS_DOWN,
    ABILITY_STANCE_CHANGE,
    ABILITY_ZEN_MODE,
};

static const u16 sEntrainmentBannedAttackerAbilities[] =
{
    ABILITY_TRACE,
    ABILITY_FORECAST,
    ABILITY_FLOWER_GIFT,
    ABILITY_ZEN_MODE,
    ABILITY_ILLUSION,
    ABILITY_IMPOSTER,
    ABILITY_POWER_OF_ALCHEMY,
    ABILITY_RECEIVER,
    ABILITY_DISGUISE,
    ABILITY_POWER_CONSTRUCT,
    ABILITY_NEUTRALIZING_GAS,
    ABILITY_ICE_FACE,
    ABILITY_HUNGER_SWITCH,
    ABILITY_GULP_MISSILE,
};
//LOGIC seems to be doesn't work on biology based abilities
static const u16 sEntrainmentTargetSimpleBeamBannedAbilities[] =
{
    ABILITY_TRUANT,
    ABILITY_MULTITYPE,
    ABILITY_STANCE_CHANGE,
    ABILITY_SCHOOLING,
    ABILITY_COMATOSE,
    ABILITY_SHIELDS_DOWN,
    ABILITY_ZEN_MODE,
    ABILITY_DISGUISE,
    ABILITY_MAGMA_ARMOR,    //POTENTIAL do
    ABILITY_RKS_SYSTEM,
    ABILITY_BATTLE_BOND,
    ABILITY_ICE_FACE,
    ABILITY_GULP_MISSILE,
    ABILITY_LAVA_FISSURE,
};

u16 GetUsedHeldItem(u8 battler) //vsonic
{
    return gBattleStruct->usedHeldItems[gBattlerPartyIndexes[battler]][GetBattlerSide(battler)];
}

bool32 IsBattlerWeatherAffected(u8 battlerId, u32 weatherFlags) //need to add utility umbrella clause to weather effects
{
    if (!WEATHER_HAS_EFFECT)
        return FALSE;

    if (!IsBlackFogNotOnField())
        return FALSE;

    if (gBattleWeather & weatherFlags)
    {
        // given weather is active -> check if its sun, rain against utility umbrella ( since only 1 weather can be active at once)
        if (gBattleWeather & (WEATHER_SUN_ANY | WEATHER_RAIN_ANY) && GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_UTILITY_UMBRELLA)
            return FALSE; // utility umbrella blocks sun, rain effects

        return TRUE;
    }
    return FALSE;
}

// This function is the body of "jumpifstat", but can be used dynamically in a function
bool32 CompareStat(u8 battlerId, u8 statId, u8 cmpTo, u8 cmpKind)
{
    bool8 ret = FALSE;
    u8 statValue = gBattleMons[battlerId].statStages[statId];

    // Because this command is used as a way of checking if a stat can be lowered/raised,
    // we need to do some modification at run-time.
    if (GetBattlerAbility(battlerId) == ABILITY_CONTRARY)
    {
        if (cmpKind == CMP_GREATER_THAN)
            cmpKind = CMP_LESS_THAN;
        else if (cmpKind == CMP_LESS_THAN)
            cmpKind = CMP_GREATER_THAN;

        if (cmpTo == MIN_STAT_STAGE)
            cmpTo = MAX_STAT_STAGE;
        else if (cmpTo == MAX_STAT_STAGE)
            cmpTo = MIN_STAT_STAGE;
    }

    switch (cmpKind)
    {
    case CMP_EQUAL:
        if (statValue == cmpTo)
            ret = TRUE;
        break;
    case CMP_NOT_EQUAL:
        if (statValue != cmpTo)
            ret = TRUE;
        break;
    case CMP_GREATER_THAN:
        if (statValue > cmpTo)
            ret = TRUE;
        break;
    case CMP_LESS_THAN:
        if (statValue < cmpTo)
            ret = TRUE;
        break;
    case CMP_COMMON_BITS:
        if (statValue & cmpTo)
            ret = TRUE;
        break;
    case CMP_NO_COMMON_BITS:
        if (!(statValue & cmpTo))
            ret = TRUE;
        break;
    }

    return ret;
}

void BufferStatChange(u8 battlerId, u8 statId, u8 stringId)
{
    bool8 hasContrary = (GetBattlerAbility(battlerId) == ABILITY_CONTRARY);

    PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
    if (stringId == STRINGID_STATFELL)
    {
        if (hasContrary)
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATROSE)
        else
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATFELL)
    }
    else if (stringId == STRINGID_STATROSE)
    {
        if (hasContrary)
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATFELL)
        else
            PREPARE_STRING_BUFFER(gBattleTextBuff2, STRINGID_STATROSE)
    }
    else
    {
        PREPARE_STRING_BUFFER(gBattleTextBuff2, stringId)
    }
}

bool32 DoesPranksterBlockMove(u16 move, u8 battlerwithPrankster, u8 battlerDef, bool32 checkTarget)
{
    if (!gProtectStructs[battlerwithPrankster].pranksterElevated)   //if  not boosted by prankster?
        return FALSE;
    if (GetBattlerSide(battlerwithPrankster) == GetBattlerSide(battlerDef)) //if prankster mon & target are on same side, doesn't block move
        return FALSE;
    if (checkTarget && (gBattleMoves[move].target & (MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_DEPENDS)))
        return FALSE;
    if (!IS_BATTLER_OF_TYPE(battlerDef, TYPE_DARK))
        return FALSE;
    if (gStatuses3[battlerDef] & STATUS3_SEMI_INVULNERABLE)
        return FALSE;

    return TRUE;
}

void CancelMultiTurnMoves(u8 battler)
{
    gBattleMons[battler].status2 &= ~(STATUS2_MULTIPLETURNS);
    gBattleMons[battler].status2 &= ~(STATUS2_LOCK_CONFUSE);
    gBattleMons[battler].status2 &= ~(STATUS2_UPROAR);
    gBattleMons[battler].status2 &= ~(STATUS2_BIDE);
    gStatuses3[battler] &= ~(STATUS3_SEMI_INVULNERABLE); //this will reemove on air status & fly

    // Clear battler's semi-invulnerable bits if they are not held by Sky Drop.
    if (!(gStatuses3[battler] & STATUS3_SKY_DROPPED))
        gStatuses3[battler] &= ~(STATUS3_SEMI_INVULNERABLE);

    // Check to see if this Pokemon was in the middle of using Sky Drop. If so, release the target.
    if (gBattleStruct->skyDropTargets[battler] != 0xFF && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
    {
        // Get the target's battler id
        u8 otherSkyDropper = gBattleStruct->skyDropTargets[battler];

        // Clears sky_dropped and on_air statuses
        gStatuses3[otherSkyDropper] &= ~(STATUS3_SKY_DROPPED | STATUS3_ON_AIR);
        //if status on air and last hit by move with flag 2x damage on air cancel on air status 
        //to cancel fly and set grounded

        // Makes both attacker and target's sprites visible
        gSprites[gBattlerSpriteIds[battler]].invisible = FALSE; //addeed to grounded command in case its needed to cnacel fly
        gSprites[gBattlerSpriteIds[otherSkyDropper]].invisible = FALSE;

        // If target was sky dropped in the middle of Outrage/Thrash/Petal Dance,
        // confuse them upon release and display "confused by fatigue" message & animation.
        // Don't do this if this CancelMultiTurnMoves is caused by falling asleep via Yawn.
        if (gBattleMons[otherSkyDropper].status2 & STATUS2_LOCK_CONFUSE && gBattleStruct->turnEffectsTracker != 24)
        {
            gBattleMons[otherSkyDropper].status2 &= ~(STATUS2_LOCK_CONFUSE);

            // If the target can be confused, confuse them.
            // Don't use CanBeConfused, can cause issues in edge cases.
            if (!(GetBattlerAbility(otherSkyDropper) == ABILITY_OWN_TEMPO
                || gBattleMons[otherSkyDropper].status2 & STATUS2_CONFUSION
                || IsBattlerTerrainAffected(otherSkyDropper, STATUS_FIELD_MISTY_TERRAIN)))
            {
                // Set confused status
                gBattleMons[otherSkyDropper].status2 |= STATUS2_CONFUSION_TURN(((Random()) % 4) + 2);   //2-5 turn value for confusion

                // If this CancelMultiTurnMoves is occuring due to attackcanceller
                if (gBattlescriptCurrInstr[0] == 0x0)
                {
                    gBattleStruct->skyDropTargets[battler] = 0xFE; //vsonic IMPORTANT
                }
                // If this CancelMultiTurnMoves is occuring due to VARIOUS_GRAVITY_ON_AIRBORNE_MONS
                // Reapplying STATUS3_SKY_DROPPED allows for avoiding unecessary messages when Gravity is applied to the target.
                else if (gBattlescriptCurrInstr[0] == 0x76 && gBattlescriptCurrInstr[2] == 76)
                {
                    gBattleStruct->skyDropTargets[battler] = 0xFE;
                    gStatuses3[otherSkyDropper] |= STATUS3_SKY_DROPPED;
                }
                // If this CancelMultiTurnMoves is occuring due to cancelmultiturnmoves script
                else if (gBattlescriptCurrInstr[0] == 0x76 && gBattlescriptCurrInstr[2] == 0)
                {
                    gBattlerAttacker = otherSkyDropper;
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses - 3;
                }
                // If this CancelMultiTurnMoves is occuring due to receiving Sleep/Freeze status
                else if ((gBattleMons[otherSkyDropper].status1 & STATUS1_SLEEP)// | STATUS1_FREEZE))
                    || (gDisableStructs[otherSkyDropper].FrozenTurns != 0))//(gBattleScripting.moveEffect <= PRIMARY_STATUS_MOVE_EFFECT)
                {
                    gBattlerAttacker = otherSkyDropper;
                    BattleScriptPush(gBattlescriptCurrInstr + 1);
                    gBattlescriptCurrInstr = BattleScript_ThrashConfuses - 1;//HOPE this still works right  vsonic
                }
            }
        }

        // Clear skyDropTargets data, unless this CancelMultiTurnMoves is caused by Yawn, attackcanceler, or VARIOUS_GRAVITY_ON_AIRBORNE_MONS
        if (!(gBattleMons[otherSkyDropper].status2 & STATUS2_LOCK_CONFUSE) && gBattleStruct->skyDropTargets[battler] < 4)
        {
            gBattleStruct->skyDropTargets[battler] = 0xFF;
            gBattleStruct->skyDropTargets[otherSkyDropper] = 0xFF;
        }
    }

    gDisableStructs[battler].rolloutTimer = 0;
    gDisableStructs[battler].furyCutterCounter = 0;
}

bool8 WasUnableToUseMove(u8 battler)
{
    if (gProtectStructs[battler].prlzImmobility
        || gProtectStructs[battler].targetNotAffected
        || gProtectStructs[battler].usedImprisonedMove
        || gProtectStructs[battler].loveImmobility
        || gProtectStructs[battler].usedDisabledMove
        || gProtectStructs[battler].usedTauntedMove
        || gProtectStructs[battler].flag2Unknown
        || gProtectStructs[battler].usedGravityPreventedMove
        || gProtectStructs[battler].usedHealBlockedMove
        || gProtectStructs[battler].powderSelfDmg
        || gProtectStructs[battler].usedThroatChopPreventedMove
        || gProtectStructs[battler].flinchImmobility
        || gProtectStructs[battler].confusionSelfDmg) //prob need adjust this when done
        return TRUE; //actually no I'll keep that as is, but only have it trigger when using non-status move on self at bad oods
    else
        return FALSE;
}

void PrepareStringBattle(u16 stringId, u8 battler)
{
    u32 targetSide = GetBattlerSide(gBattlerTarget);
    u16 battlerAbility = GetBattlerAbility(battler);
    u16 targetAbility = GetBattlerAbility(gBattlerTarget);
    // Support for Contrary ability.
    // If a move attempted to raise stat - print "won't increase".
    // If a move attempted to lower stat - print "won't decrease".
    if (stringId == STRINGID_STATSWONTDECREASE && !(gBattleScripting.statChanger & STAT_BUFF_NEGATIVE))
        stringId = STRINGID_STATSWONTINCREASE;
    else if (stringId == STRINGID_STATSWONTINCREASE && gBattleScripting.statChanger & STAT_BUFF_NEGATIVE)
        stringId = STRINGID_STATSWONTDECREASE;

    else if (stringId == STRINGID_STATSWONTDECREASE2 && battlerAbility == ABILITY_CONTRARY) //Shouldn't this be target ability?
        stringId = STRINGID_STATSWONTINCREASE2;
    else if (stringId == STRINGID_STATSWONTINCREASE2 && battlerAbility == ABILITY_CONTRARY)
        stringId = STRINGID_STATSWONTDECREASE2;


    // Check Defiant and Competitive stat raise whenever a stat is lowered.
    if (stringId == STRINGID_DEFENDERSSTATFELL
        && ((targetAbility == ABILITY_DEFIANT && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            || (targetAbility == ABILITY_COMPETITIVE && CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            || (targetAbility == ABILITY_URSURPER && CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
                && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)))
        && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != BATTLE_PARTNER(gBattlerTarget)
        && ((gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget) || gBattleScripting.stickyWebStatDrop == 1)
        && !(gBattleScripting.stickyWebStatDrop == 1 && gSideTimers[targetSide].stickyWebBattlerSide == targetSide)) // Sticky Web must have been set by the foe
    {
        gBattleScripting.stickyWebStatDrop = 0;
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat;
        if (targetAbility == ABILITY_DEFIANT)
            SET_STATCHANGER(STAT_ATK, 1, FALSE);    //since have extra to effect, lowered these 2 to a single stat stage for each stat drop.
        else if (targetAbility == ABILITY_COMPETITIVE)
            SET_STATCHANGER(STAT_SPATK, 1, FALSE);
        else if (targetAbility == ABILITY_URSURPER)
        {
            SET_STATCHANGER(STAT_ATK, 1, FALSE);
            SET_STATCHANGER2(gBattleScripting.savedStatChanger, STAT_SPATK, 1, FALSE);
        }
    }

    //specific case just for intimidate, uses normal effect
    else if ((stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_TIGER_MOM_ACTIVATES)
        && ((targetAbility == ABILITY_DEFIANT && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            || (targetAbility == ABILITY_COMPETITIVE && CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
            || (targetAbility == ABILITY_URSURPER && CompareStat(gBattlerTarget, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
                && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)))
        && gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != BATTLE_PARTNER(gBattlerTarget)
        && ((gSpecialStatuses[gBattlerTarget].changedStatsBattlerId != gBattlerTarget) || gBattleScripting.stickyWebStatDrop == 1) //stats weren't dropped byitslf or teammate
        && !(gBattleScripting.stickyWebStatDrop == 1 && gSideTimers[targetSide].stickyWebBattlerSide == targetSide))
    {
        gBattleScripting.stickyWebStatDrop = 0;
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat; //ok intimidate is actually just 1 stat stage 
        if (targetAbility == ABILITY_DEFIANT)
            SET_STATCHANGER(STAT_ATK, 2, FALSE);    //since intimidate is explicitly an 2 stage atk drop, boosting defiant, so you don't just negate
        else if (targetAbility == ABILITY_COMPETITIVE)
            SET_STATCHANGER(STAT_SPATK, 2, FALSE);
        else if (targetAbility == ABILITY_URSURPER)
        {
            SET_STATCHANGER(STAT_ATK, 3, FALSE);    //to counteract intimidate and keep pace with sp atk, and for even daring attempting to intimidate it
            SET_STATCHANGER2(gBattleScripting.savedStatChanger, STAT_SPATK, 2, FALSE); //check if I need to update stat changer for 4 stage stat boost.
        }
    }

    else if ((stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_TIGER_MOM_ACTIVATES)
        && targetAbility == ABILITY_RATTLED
        && CompareStat(gBattlerTarget, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat;
        SET_STATCHANGER(STAT_SPEED, 2, FALSE);  //buffed to 2 stage stat boost
    }
    else if ((stringId == STRINGID_PKMNCUTSATTACKWITH || stringId == STRINGID_TIGER_MOM_ACTIVATES)
        && targetAbility == ABILITY_ANGER_POINT 
        && CompareStat(gBattlerTarget, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN)) //For the trolls  :)
    {
        gBattlerAbility = gBattlerTarget;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AbilityRaisesDefenderStat;
        SET_STATCHANGER(STAT_ATK, 3, FALSE); //talk with lucky decide section effect, make plus 2 from intimidate, as some mon that get anger point are hella fast

    }
    else if ((stringId == STRINGID_PKMNFLINCHED)
        && battlerAbility == ABILITY_STEADFAST
        && CompareStat(gBattlerAttacker, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        gBattlerAbility = gBattlerAttacker;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_AttackerAbilityStatRaise;  //need test
        SET_STATCHANGER(STAT_SPEED, 1, FALSE);
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
    if (gDisableStructs[gActiveBattler].throatChopTimer != 0 && gBattleMoves[move].flags & FLAG_SOUND)
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveThroatChop;
        limitations++;
    }
    if (GetImprisonedMovesCount(gActiveBattler, move))
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingImprisonedMove;
        ++limitations;
    }
    if (IsGravityPreventingMove(move))
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveGravity;
        limitations++;
    }

    if (IsHealBlockPreventingMove(gActiveBattler, move))
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveHealBlock;
        limitations++;
    }

    if (IsBelchPreventingMove(gActiveBattler, move))
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedBelch;
        limitations++;
    }

    if (move == MOVE_STUFF_CHEEKS && ItemId_GetPocket(gBattleMons[gActiveBattler].item) != POCKET_BERRY_POUCH)
    {
        gCurrentMove = move;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedStuffCheeks;
        limitations++;
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
    else if (holdEffect == HOLD_EFFECT_ASSAULT_VEST && gBattleMoves[move].power == 0 && move != MOVE_ME_FIRST)
    {
        gCurrentMove = move;
        gLastUsedItem = gBattleMons[gActiveBattler].item;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveAssaultVest;
        limitations++;
    }
    if ((GetBattlerAbility(gActiveBattler) == ABILITY_GORILLA_TACTICS) && *choicedMove != MOVE_NONE
        && *choicedMove != 0xFFFF && *choicedMove != move)
    {
        gCurrentMove = *choicedMove;
        gLastUsedItem = gBattleMons[gActiveBattler].item;
        gSelectionBattleScripts[gActiveBattler] = BattleScript_SelectingNotAllowedMoveGorillaTactics;
        limitations++;
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
        // Assault Vest
        if (holdEffect == HOLD_EFFECT_ASSAULT_VEST && gBattleMoves[gBattleMons[battlerId].moves[i]].power == 0 && gBattleMons[battlerId].moves[i] != MOVE_ME_FIRST)
            unusableMoves |= gBitTable[i];
        // Gravity
        if (IsGravityPreventingMove(gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        // Heal Block
        if (IsHealBlockPreventingMove(battlerId, gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        // Belch
        if (IsBelchPreventingMove(battlerId, gBattleMons[battlerId].moves[i]))
            unusableMoves |= gBitTable[i];
        // Throat Chop
        if (gDisableStructs[battlerId].throatChopTimer && gBattleMoves[gBattleMons[battlerId].moves[i]].flags & FLAG_SOUND)
            unusableMoves |= gBitTable[i];
        // Stuff Cheeks
        if (gBattleMons[battlerId].moves[i] == MOVE_STUFF_CHEEKS && ItemId_GetPocket(gBattleMons[gActiveBattler].item) != POCKET_BERRY_POUCH)
            unusableMoves |= gBitTable[i];
        // Gorilla Tactics
        if (GetBattlerAbility(battlerId) == ABILITY_GORILLA_TACTICS && *choicedMove != MOVE_NONE && *choicedMove != 0xFFFF && *choicedMove != gBattleMons[battlerId].moves[i])
            unusableMoves |= gBitTable[i];
    }
    return unusableMoves;
}

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


void RestoreBattlerOriginalTypes(u8 battlerId)
{
    gBattleMons[battlerId].type1 = gBaseStats[gBattleMons[battlerId].species].type1;
    gBattleMons[battlerId].type2 = gBaseStats[gBattleMons[battlerId].species].type2;
}

void TryToApplyMimicry(u8 battlerId, bool8 various)
{
    u32 moveType, move;

    GET_MOVE_TYPE(move, moveType);
    switch (gFieldStatuses)
    {
    case STATUS_FIELD_ELECTRIC_TERRAIN:
        moveType = TYPE_ELECTRIC;
        break;
    case STATUS_FIELD_MISTY_TERRAIN:
        moveType = TYPE_FAIRY;
        break;
    case STATUS_FIELD_GRASSY_TERRAIN:
        moveType = TYPE_GRASS;
        break;
    case STATUS_FIELD_PSYCHIC_TERRAIN:
        moveType = TYPE_PSYCHIC;
        break;
    default:
        moveType = 0;
        break;
    }

    if (moveType != 0 && !IS_BATTLER_OF_TYPE(battlerId, moveType))
    {
        SET_BATTLER_TYPE(battlerId, moveType);
        PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, battlerId, gBattlerPartyIndexes[battlerId])
            PREPARE_TYPE_BUFFER(gBattleTextBuff2, moveType);
        if (!various)
            BattleScriptPushCursorAndCallback(BattleScript_MimicryActivatesEnd3);
    }
}

void TryToRevertMimicry(void)
{
    s32 i;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (GetBattlerAbility(i) == ABILITY_MIMICRY)
            RestoreBattlerOriginalTypes(i);
    }
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

bool32 IsHealBlockPreventingMove(u32 battler, u32 move)
{
    if (!(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
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

bool32 CanPoisonType(u8 battlerAttacker, u8 battlerTarget)  //somehow works...
{
    return (((GetBattlerAbility(battlerAttacker) == ABILITY_CORROSION) && (gBattleMoves[gCurrentMove].split == SPLIT_STATUS))
        || !(IS_BATTLER_OF_TYPE(battlerTarget, TYPE_POISON) || IS_BATTLER_OF_TYPE(battlerTarget, TYPE_STEEL)));
}

// Ingrain, Leech Seed, Strength Sap and Aqua Ring
//leech seed has weird targetting so I'm worried it'llc ause issues for ghost drain & leech seed logic
//but if works for big root which uses battler and is pulled from gbattlerattacker I think it should work
s32 GetDrainedBigRootHp(u32 battler, s32 hp)
{
    s32 ghostdmg;
    if (GetBattlerHoldEffect(battler, TRUE) == HOLD_EFFECT_BIG_ROOT) //prob need to balance this for ingrain,
    {
        hp = (hp * 1300) / 1000;
        if (gStatuses3[gActiveBattler] & STATUS3_ROOTED) //hopefully that works. //should be a weakened effect
            hp = (hp * 1100) / 1000;
    }

     //set ghost drain damg
     //hp argument is gbattlemovedamage 
     //needed change from explicitly only work with x effects because leech seed
    if (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GHOST)
        && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST)
        && gBattleMoves[gCurrentMove].effect != EFFECT_DREAM_EATER) //work on physical drain moves, dream eater is mental/dreams not lifeforce
        //should prevent damage for ghost types
    {
        if ((hp / 2) < gBattleMons[battler].maxHP / 8)
            ghostdmg = gBattleMons[battler].maxHP / 8;

        else if ((hp / 2) > gBattleMons[battler].maxHP / 8)
            ghostdmg = hp / 2;
        //take the greater of the two, changed from else, so I don't have to worry about it
        if (GetBattlerAbility(gBattlerTarget) == ABILITY_LIQUID_OOZE) //rest fo liquid ooze logic handled in script
        {
            hp += ghostdmg;

            /*if (gBattleMoves[gCurrentMove].effect == EFFECT_STRENGTH_SAP)
                hp = (hp + ghostdmg) / 2; //to try keep this from just being an insta kill
                */ //...nevermnid then -_- liquid ooze was meant to work with strength sap from the start
                //so I should let it work as is, not try to scale it back for balance I guess
        }
        else
        {
            hp = -ghostdmg; //since below flips sign need set this negative to properly do damage
                //would love a script for this but cant do anything as set in a command? idk I might be able to put
                //something below that pushes and returns?
        }      
        //if can setup text to say aborb ghostly energy!  it'd go here vsonic  
    }

    if (hp == 0)
        hp = 1;

    return hp * -1; //sets value negative as pass command
}

#define MAGIC_GUARD_CHECK \
if (ability == ABILITY_MAGIC_GUARD) \
{\
    RecordAbilityBattle(gActiveBattler, ability);\
    ++gBattleStruct->turnEffectsTracker;\
            break;\
}

//field/side based end turn
enum
{
    ENDTURN_ORDER,
    ENDTURN_REFLECT,
    ENDTURN_LIGHT_SCREEN,
    ENDTURN_MAGIC_COAT,
    ENDTURN_AURORA_VEIL,
    ENDTURN_MIST,
    ENDTURN_HAZE,
    ENDTURN_LUCKY_CHANT,
    ENDTURN_SAFEGUARD,
    ENDTURN_HEALBLOCK,
    ENDTURN_EMBARGO,
    ENDTURN_TAILWIND,
    ENDTURN_WISH,
    ENDTURN_RAIN,
    ENDTURN_SANDSTORM,
    ENDTURN_SUN,
    ENDTURN_HAIL,
    ENDTURN_GRAVITY,
    ENDTURN_TRICK_ROOM,
    ENDTURN_WONDER_ROOM,
    ENDTURN_MAGIC_ROOM,
    ENDTURN_ELECTRIC_TERRAIN,
    ENDTURN_MISTY_TERRAIN,
    ENDTURN_GRASSY_TERRAIN,
    ENDTURN_PSYCHIC_TERRAIN,
    ENDTURN_WATER_SPORT,
    ENDTURN_MUD_SPORT,
    ENDTURN_ION_DELUGE,
    ENDTURN_FAIRY_LOCK,
    ENDTURN_RETALIATE,
    ENDTURN_FIELD_COUNT,
};

#define FIELD_ENDTURN
u8 DoFieldEndTurnEffects(void)// still to do  //vsonic IMPORTANT  done updated
{
    u8 effect = 0;

    for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerAttacker]; gBattlerAttacker++)
    {
    }
    for (gBattlerTarget = 0; gBattlerTarget < gBattlersCount && gAbsentBattlerFlags & gBitTable[gBattlerTarget]; gBattlerTarget++)
    {
    }
    do
    {
        s32 i;
        u8 side;

        switch (gBattleStruct->turnCountersTracker)
        {
        case ENDTURN_ORDER:
            for (i = 0; i < gBattlersCount; ++i)
                gBattlerByTurnOrder[i] = i;
            for (i = 0; i < gBattlersCount - 1; ++i)
            {
                s32 j;

                for (j = i + 1; j < gBattlersCount; ++j)
                {
                    if (GetWhoStrikesFirst(gBattlerByTurnOrder[i], gBattlerByTurnOrder[j], 0))
                        SwapTurnOrder(i, j);
                }
            }
            ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_MAGIC_COAT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].MagicBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_MAGIC_COAT)
                {
                    if (--gSideTimers[side].MagicTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_MAGIC_COAT;
                        gProtectStructs[gBattlerAttacker].bounceMove = FALSE; //think this is proper way to do this
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_MAGIC_COAT);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_MIST:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].mistBattlerId;
                
                if (gSideStatuses[side] & SIDE_STATUS_MIST)
                {
                    if (--gSideTimers[side].mistTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_MIST;
                        BattleScriptExecute(BattleScript_SideStatusWoreOff);
                        gBattleCommunication[MULTISTRING_CHOOSER] = side;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_MIST);
                        ++effect;
                    }
                }                
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_HAZE: //compiles but check if right
            if (gFieldStatuses & STATUS_FIELD_BLACK_FOG && --gFieldTimers.HazeTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_BLACK_FOG;
                BattleScriptExecute(BattleScript_TrickRoomEnds);//MAKE new script for later vsonic
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_HEALBLOCK:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerTarget = gSideTimers[side].healBlockBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_HEAL_BLOCK)//checking if finished heal block effect item & move heal cancel..E
                {
                    //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; //set status for mid turn switch ins..actually could just put in switchin function

                    if (--gSideTimers[side].healBlockTimer == 0) //believe this is the decrement
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_HEAL_BLOCK; //clears side status
                        //gStatuses3[gActiveBattler] &= ~STATUS3_HEAL_BLOCK;  //clears battler status   //think dont need this?
                        BattleScriptExecute(BattleScript_BufferEndTurn); //unsure if this message will print for both parties to see
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_HEAL_BLOCK); //need to make sure player is aware heal block ends if its used by or against them
                        ++effect;
                    }//belive I have healing moves, & healing items blocked by need to make logic for held berries/items  /just check hold effect for healing done, 
                    //added !(gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_HEAL_BLOCK)  to itembattleeffects function, should cover everything now??
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_EMBARGO:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerTarget = gSideTimers[side].embargoBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_EMBARGO)//checking if finished heal block effect item & move heal cancel..E
                {
                    //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; //set status for mid turn switch ins..actually could just put in switchin function

                    if (--gSideTimers[side].embargoTimer == 0)//setup different message for if ability is on field or not, when timer is 0, potentially
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_EMBARGO; //clears side status
                        //gStatuses3[gActiveBattler] &= ~STATUS3_HEAL_BLOCK;  //clears battler status   //think dont need this?
                        BattleScriptExecute(BattleScript_BufferEndTurn); //unsure if this message will print for both parties to see
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_EMBARGO); //need to make sure player is aware heal block ends if its used by or against them
                        ++effect;
                    }//belive I have healing moves, & healing items blocked by need to make logic for held berries/items  /just check hold effect for healing done, 
                    //added !(gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_HEAL_BLOCK)  to itembattleeffects function, should cover everything now??
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
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
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
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
                    ++effect;
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            break;
        case ENDTURN_RAIN:
            if (gBattleWeather & WEATHER_RAIN_ANY)
            {
                if (!(gBattleWeather & WEATHER_RAIN_PERMANENT)
                    && !(gBattleWeather & WEATHER_RAIN_PRIMAL)
                    && !IsAbilityOnField(ABILITY_DRIZZLE)
                    && !IsAbilityOnField(ABILITY_SQUALL))
                {

                    if (--gWishFutureKnock.weatherDuration == 0) //decremennts weather, and does removes weather if equals 0 after decrement
                    {
                        gBattleWeather &= ~WEATHER_RAIN_TEMPORARY;
                        gBattleWeather &= ~WEATHER_RAIN_DOWNPOUR;
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_STOPPED;//why is rain the only one with all this extra logic?
                    }
                    else if (gBattleWeather & WEATHER_RAIN_DOWNPOUR)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOWNPOUR_CONTINUES;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_CONTINUES;
                }
                else if (gBattleWeather & WEATHER_RAIN_DOWNPOUR)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_DOWNPOUR_CONTINUES;
                }
                else
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_RAIN_CONTINUES;
                }
                BattleScriptExecute(BattleScript_RainContinuesOrEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_SANDSTORM:
            if (gBattleWeather & WEATHER_SANDSTORM_ANY)
            {
                if (!(gBattleWeather & WEATHER_SANDSTORM_PERMANENT)
                    && !IsAbilityOnField(ABILITY_SAND_STREAM))  //only the abilities that actually call weather directly
                {
                        if (--gWishFutureKnock.weatherDuration == 0)  //weather decrement
                        {
                            gBattleWeather &= ~WEATHER_SANDSTORM_TEMPORARY;
                            gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
                        }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }
                gBattleScripting.animArg1 = B_ANIM_SANDSTORM_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                BattleScriptExecute(gBattlescriptCurrInstr);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_SUN:
            if (gBattleWeather & WEATHER_SUN_ANY)
            {
                if (!(gBattleWeather & WEATHER_SUN_PERMANENT)
                    && !(gBattleWeather & WEATHER_SUN_PRIMAL)
                    && !IsAbilityOnField(ABILITY_DROUGHT)
                    && !IsAbilityOnField(ABILITY_SUN_DISK))
                {

                        if (--gWishFutureKnock.weatherDuration == 0) //weathr decrement
                        {
                            gBattleWeather &= ~WEATHER_SUN_TEMPORARY;
                            gBattlescriptCurrInstr = BattleScript_SunlightFaded;
                        }

                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_SunlightContinues;
                }
                BattleScriptExecute(gBattlescriptCurrInstr);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_HAIL:
            if (gBattleWeather & WEATHER_HAIL_ANY)
            {
                if (!(gBattleWeather & WEATHER_HAIL_PERMANENT)
                    && !IsAbilityOnField(ABILITY_SNOW_WARNING))
                {
                    //decided to keep this setup  are below drought/drizzle but still gives reason to use weather crystals its a good middle ground
                    //had to fix, logic hierarchy wasn't right, think wouldn't have properly gone to weather continue
                        if (--gWishFutureKnock.weatherDuration == 0)    //weather decrement
                        {
                            gBattleWeather &= ~WEATHER_HAIL;
                            gBattlescriptCurrInstr = BattleScript_SandStormHailEnds;
                        }
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_DamagingWeatherContinues;
                }
                gBattleScripting.animArg1 = B_ANIM_HAIL_CONTINUES;
                gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                BattleScriptExecute(gBattlescriptCurrInstr);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_GRAVITY:
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && --gFieldTimers.gravityTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_GRAVITY;
                BattleScriptExecute(BattleScript_GravityEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_TRICK_ROOM:
            if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && --gFieldTimers.trickRoomTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_TRICK_ROOM;
                BattleScriptExecute(BattleScript_TrickRoomEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_WONDER_ROOM:
            if (gFieldStatuses & STATUS_FIELD_WONDER_ROOM && --gFieldTimers.wonderRoomTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_WONDER_ROOM;
                BattleScriptExecute(BattleScript_WonderRoomEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_MAGIC_ROOM:
            if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM && --gFieldTimers.magicRoomTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_MAGIC_ROOM;
                BattleScriptExecute(BattleScript_MagicRoomEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_ELECTRIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN
                && (!(gFieldStatuses & STATUS_FIELD_TERRAIN_PERMANENT) && --gFieldTimers.terrainTimer == 0))
            {
                gFieldStatuses &= ~(STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_TERRAIN_PERMANENT);
                TryToRevertMimicry();
                BattleScriptExecute(BattleScript_ElectricTerrainEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_MISTY_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN
                && (!(gFieldStatuses & STATUS_FIELD_TERRAIN_PERMANENT) && --gFieldTimers.terrainTimer == 0))
            {
                gFieldStatuses &= ~STATUS_FIELD_MISTY_TERRAIN;
                TryToRevertMimicry();
                BattleScriptExecute(BattleScript_MistyTerrainEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_GRASSY_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_GRASSY_TERRAIN)
            {
                if (!(gFieldStatuses & STATUS_FIELD_TERRAIN_PERMANENT)
                    && (gFieldTimers.terrainTimer == 0 || --gFieldTimers.terrainTimer == 0))
                {
                    gFieldStatuses &= ~STATUS_FIELD_GRASSY_TERRAIN;
                    TryToRevertMimicry();
                }
                BattleScriptExecute(BattleScript_GrassyTerrainHeals);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_PSYCHIC_TERRAIN:
            if (gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN
                && (!(gFieldStatuses & STATUS_FIELD_TERRAIN_PERMANENT) && --gFieldTimers.terrainTimer == 0))
            {
                gFieldStatuses &= ~STATUS_FIELD_PSYCHIC_TERRAIN;
                TryToRevertMimicry();
                BattleScriptExecute(BattleScript_PsychicTerrainEnds);
                ++effect;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_WATER_SPORT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].waterSportBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_WATERSPORT)
                {
                    if (--gSideTimers[side].waterSportTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_WATERSPORT;
                        BattleScriptExecute(BattleScript_WaterSportEnds);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_MUD_SPORT:
            while (gBattleStruct->turnSideTracker < 2)
            {
                side = gBattleStruct->turnSideTracker;
                gActiveBattler = gBattlerAttacker = gSideTimers[side].mudSportBattlerId;
                if (gSideStatuses[side] & SIDE_STATUS_MUDSPORT)
                {
                    if (--gSideTimers[side].mudSportTimer == 0)
                    {
                        gSideStatuses[side] &= ~SIDE_STATUS_MUDSPORT;
                        BattleScriptExecute(BattleScript_MudSportEnds);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnSideTracker;
                if (effect)
                    break;
            }
            if (!effect)
            {
                ++gBattleStruct->turnCountersTracker;
                gBattleStruct->turnSideTracker = 0;
            }
            break;
        case ENDTURN_ION_DELUGE:
            if (gFieldStatuses & STATUS_FIELD_ION_DELUGE && --gFieldTimers.IonDelugeTimer == 0)
                gFieldStatuses &= ~STATUS_FIELD_ION_DELUGE;
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_FAIRY_LOCK:
            if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK && --gFieldTimers.fairyLockTimer == 0)
            {
                gFieldStatuses &= ~STATUS_FIELD_FAIRY_LOCK;
            }
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_RETALIATE: //still to do
            if (gSideTimers[B_SIDE_PLAYER].retaliateTimer > 0)
                gSideTimers[B_SIDE_PLAYER].retaliateTimer--;
            if (gSideTimers[B_SIDE_OPPONENT].retaliateTimer > 0)
                gSideTimers[B_SIDE_OPPONENT].retaliateTimer--;
            ++gBattleStruct->turnCountersTracker;
            break;
        case ENDTURN_FIELD_COUNT:
            ++effect;
            break;
        }
    } while (!effect);

    return (gBattleMainFunc != BattleTurnPassed);
}

/*enum
{
    ENDTURN_INGRAIN,
    ENDTURN_ABILITIES,
    ENDTURN_ITEMS1,
    ENDTURN_LEECH_SEED,
    ENDTURN_POISON,
    ENDTURN_BAD_POISON,
    ENDTURN_BURN,
    ENDTURN_FREEZE,
    ENDTURN_NIGHTMARES,
    ENDTURN_CURSE,
    ENDTURN_WRAP,
    ENDTURN_UPROAR,
    ENDTURN_THRASH,
    ENDTURN_DISABLE,
    ENDTURN_ENCORE,
    ENDTURN_LOCK_ON,
    ENDTURN_CHARGE,
    ENDTURN_TAUNT,
    ENDTURN_YAWN,
    ENDTURN_ROOST,
    ENDTURN_ITEMS2,
    ENDTURN_BATTLER_COUNT
};*/

enum   //battler end turn
{
    ENDTURN_INGRAIN,
    ENDTURN_AQUA_RING,
    ENDTURN_ABILITIES,
    ENDTURN_ITEMS1,
    ENDTURN_LEECH_SEED,
    ENDTURN_POISON,
    ENDTURN_BAD_POISON,
    ENDTURN_BURN,
    ENDTURN_FREEZE,
    ENDTURN_NIGHTMARES,
    ENDTURN_CURSE,
    ENDTURN_BIND,
    ENDTURN_WRAP,
    ENDTURN_CLAMP,
    ENDTURN_SWARM, 
    ENDTURN_SNAPTRAP,
    ENDTURN_ENVIRONMENT_TRAP,
    ENDTURN_OCTOLOCK,
    ENDTURN_UPROAR,
    ENDTURN_THRASH,
    ENDTURN_FLINCH,
    ENDTURN_DISABLE,
    ENDTURN_ENCORE,
    ENDTURN_MAGNET_RISE,
    ENDTURN_TELEKINESIS,
    ENDTURN_LOCK_ON,
    ENDTURN_CHARGE,
    ENDTURN_LASER_FOCUS,
    ENDTURN_TAUNT,
    ENDTURN_YAWN,
    ENDTURN_SLEEP,
    ENDTURN_ITEMS2,
    ENDTURN_ORBS,
    ENDTURN_ROOST,
    ENDTURN_ELECTRIFY,
    ENDTURN_POWDER,
    //ENDTURN_INFESTATION,  //changed to non-damaging debuff status
    ENDTURN_THROAT_CHOP,
    ENDTURN_SLOW_START,
    ENDTURN_PLASMA_FISTS,
    ENDTURN_BIDE,
    ENDTURN_BATTLER_COUNT
};




//important not having all cases completed with increments, causes endless loop, from unreachable code.
//need finish this & dofieldendturneffects
//was able to confirm field end turn is the problem,
#define ENDTURN_EFFECTS
u8 DoBattlerEndTurnEffects(void) 
{
    //u32 ability;    //ok added back realize its literally just for the magic gaurd check
    u32 ability, i, effect = 0;

    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    while (gBattleStruct->turnEffectsBattlerId < gBattlersCount && gBattleStruct->turnEffectsTracker <= ENDTURN_BATTLER_COUNT)
    {
        gActiveBattler = gBattlerAttacker = gBattlerByTurnOrder[gBattleStruct->turnEffectsBattlerId];
        if (gAbsentBattlerFlags & gBitTable[gActiveBattler])
        {
            ++gBattleStruct->turnEffectsBattlerId;
        }
        else
        {
            ability = GetBattlerAbility(gActiveBattler);
            switch (gBattleStruct->turnEffectsTracker) //adjusting to 8 instead of 15 to limit amount of healing
            {
            case ENDTURN_INGRAIN:  // ingrain
                if ((gStatuses3[gActiveBattler] & STATUS3_ROOTED) //IT FUCKING WORKS!!!   prob need lower limit from 15 to llike 7
                    && !BATTLER_MAX_HP(gActiveBattler)
                    && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK)
                    && gBattleMons[gActiveBattler].hp != 0 //function changes & new rooted defines courtesy of phoenix_bound
                    && IsBlackFogNotOnField())
                {
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                    if (gBattleMoveDamage == 0)//this caps at 16 turns because the orginal & bit calculation == 0, then it adds 0x100 if it doesn't equal 0xF00 which is 1500
                        gBattleMoveDamage = 1; // so it caps the turns by essentially counting from 0 to 15. so controlling/balancing the effect is as simple as lowering 0xF00!!!
                    if ((gStatuses3[gActiveBattler] & STATUS3_ROOTED_COUNTER) != STATUS3_ROOTED_TURN(8)) { // not 16 turns/ facepalm just realized how this works!1!
                        gStatuses3[gActiveBattler] += STATUS3_ROOTED_TURN(1); //seriously spitballin' here, nothing's broken atleast all the colors below are still right
                    }
                    gBattleMoveDamage *= gStatuses3[gActiveBattler] >> STATUS3_ROOTED_SHIFT;       // need understand
                    gBattleMoveDamage *= -1; //moved this to the bottom previously, because it doesn't need to be up top, and so its read last, 
                    BattleScriptExecute(BattleScript_IngrainTurnHeal);
                    ++effect; //next step augment battlescript to be similar to poisonturndamage../no changes needed everything handled by gbattlemovedamage in these funtions
                    //and the  updatehp commands in the battle script.  purpose of these changes was to ingrain work like but opposite to toxic, increase heal by same amount each turn
                } //I'm completely guessing but if done right, should heal an additional 1/16th per turn
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_AQUA_RING:  // aqua ring
                if ((gStatuses3[gActiveBattler] & STATUS3_AQUA_RING) //hopefully allows to just reuse counter here for aqua ring to duplicate effect
                    && !BATTLER_MAX_HP(gActiveBattler)
                    && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK)
                    && gBattleMons[gActiveBattler].hp != 0 //function changes & new rooted defines courtesy of phoenix_bound
                    && IsBlackFogNotOnField())
                {
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if ((gStatuses3[gActiveBattler] & STATUS3_ROOTED_COUNTER) != STATUS3_ROOTED_TURN(6)) //forgot how this works but lowered value since not rooted
                    {
                        gStatuses3[gActiveBattler] += STATUS3_ROOTED_TURN(1); //to balance
                    }
                    gBattleMoveDamage *= gStatuses3[gActiveBattler] >> STATUS3_ROOTED_SHIFT;
                    gBattleMoveDamage *= -1;
                    BattleScriptExecute(BattleScript_AquaRingHeal);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
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
                if (IsBattlerAlive(gActiveBattler) && ItemBattleEffects(ITEMEFFECT_ORBS, gActiveBattler, FALSE))
                    ++effect;
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_LEECH_SEED:  // leech seed
                if ((gStatuses3[gActiveBattler] & STATUS3_LEECHSEED) //idea increased healing if in rain or hit with water gBattleMoveDamage *= 2 
                    && gBattleMons[gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER].hp != 0
                    && gBattleMons[gActiveBattler].hp != 0
                    && IsBlackFogNotOnField())
                {
                    MAGIC_GUARD_CHECK;

                    gBattlerTarget = gStatuses3[gActiveBattler] & STATUS3_LEECHSEED_BATTLER; // Notice gBattlerTarget is actually the HP receiver.
                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;//heal leech target max hp
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GHOST)) //need test
                    {
                        //gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 16; //check if correct, but should heal, and then take 1/16 max health of pokemon healed
                         //take damage based on leech user max hp
                        gBattleMoveDamage *= -1; //wouldnt work how I planned changed, just lose hp, making negatibve shold couter negative swap in bs
                    }
                    gBattleScripting.animArg1 = gBattlerTarget;
                    gBattleScripting.animArg2 = gBattlerAttacker;
                    BattleScriptExecute(BattleScript_LeechSeedTurnDrain); //I'll figure this out, and I think what I want to do is for all these ghost effects
                    ++effect; //if absorbign from a ghost just change the color of the effect animation to a purple one
                }//TODO
                ++gBattleStruct->turnEffectsTracker;//ghost drain works need to find proper graphic though/plus do same for if draining poison top
                break;//pretty sure it uses the water bubble graphic
            case ENDTURN_POISON:  // poison
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_POISON) && gBattleMons[gActiveBattler].hp != 0
                    && GetBattlerAbility(gActiveBattler) != ABILITY_TOXIC_BOOST
                    && IsBlackFogNotOnField())
                {
                    MAGIC_GUARD_CHECK;

                    if (TryActivateBattlePoisonHeal())
                    {
                        if (!BATTLER_MAX_HP(gActiveBattler) && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK))
                        {
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                            gBattleMoveDamage *= -1;
                            RecordAbilityBattle(gBattlerAttacker, ABILITY_POISON_HEAL);
                            BattleScriptExecute(BattleScript_PoisonHealActivates);
                            ++effect;
                        }
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        BattleScriptExecute(BattleScript_PoisonTurnDmg);
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BAD_POISON:  // toxic poison
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_POISON) && gBattleMons[gActiveBattler].hp != 0
                    && GetBattlerAbility(gActiveBattler) != ABILITY_TOXIC_BOOST
                    && IsBlackFogNotOnField()) //works as I want, black fog here should also prevent toxic increment so it effectively pauses the dmg boost as well
                {
                    MAGIC_GUARD_CHECK;

                    if (TryActivateBattlePoisonHeal())
                    {
                        if (!BATTLER_MAX_HP(gActiveBattler) && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK))
                        {
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                            gBattleMoveDamage *= -1;
                            RecordAbilityBattle(gBattlerAttacker, ABILITY_POISON_HEAL);
                            BattleScriptExecute(BattleScript_PoisonHealActivates);
                            ++effect;
                        }
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        if ((gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_COUNTER) != STATUS1_TOXIC_TURN(15)) // not 16 turns
                            gBattleMons[gActiveBattler].status1 += STATUS1_TOXIC_TURN(1);   //increments by 100 up to F00 , assume starting from 000, which is why 16 turns
                        gBattleMoveDamage *= (gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_COUNTER) >> 8;    //part adding dmg increase, want to change from 1/16 turn 1, but prob cause an issue
                        BattleScriptExecute(BattleScript_PoisonTurnDmg); //dmg is based on counter value, each turn turn number value is added to counter
                        ++effect;   //was 0x100 previously it gets shifted using right shift 8 which turns it back into turn nummber
                    }//and it multiplies gbattledmg with that, so each turn you do 1 more portion of 1/16 dmg . turn 1, 1/16 turn 2 2/16 turn 3 3/16
                }   //if I want toxic to start at base poison damage, (which is 1/8) then I need to set toxic, and set to equal toxic turn 2
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BURN:  // burn
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_BURN) && gBattleMons[gActiveBattler].hp != 0
                    && GetBattlerAbility(gActiveBattler) != ABILITY_FLARE_BOOST
                    && IsBlackFogNotOnField())
                {
                    MAGIC_GUARD_CHECK;

                    if (GetBattlerAbility(gActiveBattler) == ABILITY_HEATPROOF) {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16;
                    }
                    else
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptExecute(BattleScript_BurnTurnDmg);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_FREEZE:  //FROZEN
                if ((gBattleMons[gActiveBattler].status1 & STATUS1_FREEZE) && gBattleMons[gActiveBattler].hp != 0)
                {
                    /*if (gDisableStructs[gActiveBattler].FrozenTurns) //extra protection to prevent retrigger
                    {
                        if (--gDisableStructs[gActiveBattler].FrozenTurns == 0) //actual decrement with conditional  
                        {
                            BattleScriptPushCursorAndCallback(BattleScript_DefrostBattler_KeepStatus);   //used for value ending with return
                            //gBattlescriptCurrInstr = BattleScript_DefrostBattler_KeepStatus;      //need this block above statusdmg as that doenst return, it ends
                        }//since need to execute and run continue to run script below, think need this
                    }*/
                    if (IsBlackFogNotOnField())//actually need add magic guard check to all of theese...
                    {
                        MAGIC_GUARD_CHECK;
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; //changed to same as others, combined with hail will do  .186 kills in about 5 turns by itself
                        if (gBattleMoveDamage == 0) //balanced by being a temporary status and needing the hail setup to have a good chance of being applied.
                            gBattleMoveDamage = 1;
                        //separate to ensure doesn't block decrement

                        if (gDisableStructs[gActiveBattler].FrozenTurns) //timer starts at 3, will decrement giving 2 full turns of freeze
                            BattleScriptExecute(BattleScript_FreezeTurnDmg); //changed back to 1/16, when hail is active it'll be 1/8 so equal to all others. 
                        else
                            BattleScriptExecute(BattleScript_FrostbiteTurnDmg);
                    }
                    
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_NIGHTMARES:  // spooky nightmares      //dont need black fog check as it being on field removes nightmare status
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_NIGHTMARE) && gBattleMons[gActiveBattler].hp != 0)
                {
                    MAGIC_GUARD_CHECK;
                    // R/S does not perform this sleep check, which causes the nightmare effect to
                    // persist even after the affected Pokemon has been awakened by Shed Skin.
                    if (gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        BattleScriptExecute(BattleScript_NightmareTurnDmg);
                        ++effect;
                    }
                    else
                    {
                        gBattleMons[gActiveBattler].status2 &= ~STATUS2_NIGHTMARE;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_CURSE:  // curse //I prob need add magic guard check here and in nightmare
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_CURSED) && gBattleMons[gActiveBattler].hp != 0
                    && IsBlackFogNotOnField())
                {
                    MAGIC_GUARD_CHECK;

                    gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 4;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptExecute(BattleScript_CurseTurnDmg);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BIND:  // bind
                if ((gBattleMons[gActiveBattler].status4 & STATUS4_BIND)
                    && gBattleMons[gActiveBattler].hp != 0)
                {
                    if (--gDisableStructs[gActiveBattler].bindTurns != 0
                        && IsBlackFogNotOnField())  // damaged by wrap
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/
                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6; //may raise this to /8 since status effects are strong
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_BIND;
                        gDisableStructs[gActiveBattler].bindedMove = 0;
                        //gDisableStructs[gActiveBattler].bindMovepos = 0;  //not using now replace with gcurrmovepos
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_WRAP:  // wrap     //make environemnt trap end turn & then separate ones for each physical trap
                if ((gBattleMons[gActiveBattler].status2 & STATUS2_WRAPPED)
                    && gBattleMons[gActiveBattler].hp != 0)
                {
                    if (--gDisableStructs[gActiveBattler].wrapTurns != 0
                        && IsBlackFogNotOnField())  // damaged by wrap
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/
                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {
                        gBattleMons[gActiveBattler].status2 &= ~STATUS2_WRAPPED;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_CLAMP:  // may need add fallthrough?     //make environemnt trap end turn & then separate ones for each physical trap
                if ((gBattleMons[gActiveBattler].status4 & STATUS4_CLAMP)
                    && gBattleMons[gActiveBattler].hp != 0)
                {
                    if (--gDisableStructs[gActiveBattler].clampTurns != 0
                        && IsBlackFogNotOnField())  // damaged by wrap
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/
                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_CLAMP;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_SWARM:  // may need add fallthrough?     //make environemnt trap end turn & then separate ones for each physical trap
                if (((gDisableStructs[gActiveBattler].swarmTurns
                    && IsBlackFogNotOnField()))
                    && gBattleMons[gActiveBattler].hp != 0)
                {   //THIS was the problem, why didn't i put a status check on this like I did the others?
                    if (--gDisableStructs[gActiveBattler].swarmTurns != 0)  // damaged by wrap
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/

                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler]; //need figure this out since wrappedmove, is setting more than one, isntead do based on status?
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        //BattleScriptExecute(BattleScript_StatusInfested);
                        
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;

                        if (!(gBattleMons[gActiveBattler].status1 & STATUS1_ANY)
                            && Random() % 4)
                            {
                                gBattleMons[gActiveBattler].status1 |= STATUS1_INFESTATION; //IF RIGHT should be 1 in 4 chance to set infestation at end turn after damage
                                BattleScriptPushCursorAndCallback(BattleScript_StatusInfested);
                            }//see if this works

                    }   //make sure new trap effects all have switch prevention still
                    else  // broke free
                    {   //how did I not notice I didn't have the removal status here?
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_SWARM;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_SNAPTRAP:  // may need add fallthrough?     //make environemnt trap end turn & then separate ones for each physical trap
                if ((gBattleMons[gActiveBattler].status4 & STATUS4_SNAP_TRAP) && gBattleMons[gActiveBattler].hp != 0)
                {
                    if (--gDisableStructs[gActiveBattler].snaptrapTurns != 0
                        && IsBlackFogNotOnField())  // damaged by wrap
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/
                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_SNAP_TRAP;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;  //added all extra effects hope it works well
            case ENDTURN_ENVIRONMENT_TRAP:  // may need add fallthrough?     //make environemnt trap end turn & then separate ones for each physical trap
                if ((gBattleMons[gActiveBattler].status4 & STATUS4_ENVIRONMENT_TRAP) //keeping environment traps, put physical traps before this
                    && gBattleMons[gActiveBattler].hp != 0)
                { //made separate because environment traps should be mutually exclusive as they would counter each other
                    //can't have a whirlpool in the same place you'd have a sand tomb or fire hazard etc.
                    if (--gDisableStructs[gActiveBattler].environmentTrapTurns != 0  // damaged by wrap
                        && IsBlackFogNotOnField()) //shouold decrement than prevent dmg if haze on field vsonic test
                    {
                        MAGIC_GUARD_CHECK;

                        /*gBattleScripting.animArg1 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleScripting.animArg2 = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
                        gBattleTextBuff1[1] = B_BUFF_MOVE;
                        gBattleTextBuff1[2] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 0);
                        gBattleTextBuff1[3] = *(gBattleStruct->wrappedMove + gActiveBattler * 2 + 1);
                        gBattleTextBuff1[4] = EOS;*/
                        gBattleScripting.animArg1 = gBattleStruct->wrappedMove[gActiveBattler];
                        gBattleScripting.animArg2 = gBattleStruct->wrappedMove[gActiveBattler] >> 8;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]);
                        gBattlescriptCurrInstr = BattleScript_WrapTurnDmg;
                        if (GetBattlerHoldEffect(gBattleStruct->wrappedBy[gActiveBattler], TRUE) == HOLD_EFFECT_BINDING_BAND)
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 6;
                        else
                            gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 16; ///8  keep 16 for now since buffing effects
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                    }
                    else  // broke free
                    {   //since first filter was a check for anything, I changed clear to a filter on everything
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_FIRE_SPIN;
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_WHIRLPOOL;
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_SAND_TOMB;
                        gBattleMons[gActiveBattler].status4 &= ~STATUS4_MAGMA_STORM;
                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, gBattleStruct->wrappedMove[gActiveBattler]); //vsonic need change this for multi status, so figure move from status
                        gBattlescriptCurrInstr = BattleScript_WrapEnds;
                    }
                    BattleScriptExecute(gBattlescriptCurrInstr);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_OCTOLOCK:
            {
                u16 battlerAbility = GetBattlerAbility(gActiveBattler);
                if (gDisableStructs[gActiveBattler].octolock
                    && (battlerAbility == ABILITY_CLEAR_BODY
                        || battlerAbility == ABILITY_LEAF_GUARD
                        || battlerAbility == ABILITY_FULL_METAL_BODY
                        || battlerAbility == ABILITY_WHITE_SMOKE
                        || battlerAbility == ABILITY_LIQUID_METAL))
                {
                    gBattlerTarget = gActiveBattler;
                    BattleScriptExecute(BattleScript_OctolockEndTurn);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
            }
            break;
            case ENDTURN_UPROAR:  // uproar
                if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR)
                {
                    for (gBattlerAttacker = 0; gBattlerAttacker < gBattlersCount; ++gBattlerAttacker)
                    {
                        if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP)
                            && GetBattlerAbility(gBattlerAttacker) != ABILITY_SOUNDPROOF)
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
                    gBattleMons[gActiveBattler].status2 -= STATUS2_UPROAR_TURN(1);  // uproar timer goes down
                    if (WasUnableToUseMove(gActiveBattler))
                    {
                        CancelMultiTurnMoves(gActiveBattler);
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_ENDS;
                    }
                    else if (gBattleMons[gActiveBattler].status2 & STATUS2_UPROAR)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_CONTINUES;
                        gBattleMons[gActiveBattler].status2 |= STATUS2_MULTIPLETURNS;
                    }
                    else
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_UPROAR_ENDS;
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
            // Don't decrement STATUS2_LOCK_CONFUSE if the target is held by Sky Drop
            if (gBattleMons[gActiveBattler].status2 & STATUS2_LOCK_CONFUSE && !(gStatuses3[gActiveBattler] & STATUS3_SKY_DROPPED))
            {
                gBattleMons[gActiveBattler].status2 -= STATUS2_LOCK_CONFUSE_TURN(1);
                if (WasUnableToUseMove(gActiveBattler))
                    CancelMultiTurnMoves(gActiveBattler);
                else if (!(gBattleMons[gActiveBattler].status2 & STATUS2_LOCK_CONFUSE)
                 && (gBattleMons[gActiveBattler].status2 & STATUS2_MULTIPLETURNS))
                {
                    gBattleMons[gActiveBattler].status2 &= ~STATUS2_MULTIPLETURNS;
                    if (!(gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION))
                    {
                        gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION | MOVE_EFFECT_AFFECTS_USER;
                        SetMoveEffect(TRUE, 0);
                        if (gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION)
                            BattleScriptExecute(BattleScript_ThrashConfuses);
                        ++effect;
                    }
                }
            }
            ++gBattleStruct->turnEffectsTracker;
            break;
            case ENDTURN_FLINCH:  // reset flinch   - remove flinch in end turn easy cleanse
            gBattleMons[gActiveBattler].status2 &= ~STATUS2_FLINCHED;
            ++gBattleStruct->turnEffectsTracker;
            break;
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
                    else if (--gDisableStructs[gActiveBattler].disableTimer == 0)  // disable ends //think this is a decrement?
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
            case ENDTURN_MAGNET_RISE:
            if (gStatuses3[gActiveBattler] & STATUS3_MAGNET_RISE)
            {
                if (gDisableStructs[gActiveBattler].magnetRiseTimer == 0 || --gDisableStructs[gActiveBattler].magnetRiseTimer == 0)
                {
                    gStatuses3[gActiveBattler] &= ~STATUS3_MAGNET_RISE;
                    BattleScriptExecute(BattleScript_BufferEndTurn);
                    PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ELECTROMAGNETISM);
                    ++effect;
                }
            }
            ++gBattleStruct->turnEffectsTracker;
            break;
        case ENDTURN_TELEKINESIS:
            if (gStatuses3[gActiveBattler] & STATUS3_TELEKINESIS)
            {
                if (gDisableStructs[gActiveBattler].telekinesisTimer == 0 || --gDisableStructs[gActiveBattler].telekinesisTimer == 0)
                {
                    gStatuses3[gActiveBattler] &= ~STATUS3_TELEKINESIS;
                    BattleScriptExecute(BattleScript_TelekinesisEndTurn);
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
            case ENDTURN_LASER_FOCUS:
            if (gStatuses3[gActiveBattler] & STATUS3_LASER_FOCUS)
            {
                if (gDisableStructs[gActiveBattler].laserFocusTimer == 0 || --gDisableStructs[gActiveBattler].laserFocusTimer == 0)
                    gStatuses3[gActiveBattler] &= ~STATUS3_LASER_FOCUS;
            }
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
                    gStatuses3[gActiveBattler] &= ~STATUS3_YAWN;    //should remove yawn
                    if (!(gStatuses3[gActiveBattler] & STATUS3_YAWN) && !(gBattleMons[gActiveBattler].status1 & STATUS1_ANY) //vsonic change later
                        && gBattleMons[gActiveBattler].ability != ABILITY_VITAL_SPIRIT
                        && gBattleMons[gActiveBattler].ability != ABILITY_COMATOSE
                        && gBattleMons[gActiveBattler].ability != ABILITY_INSOMNIA && !UproarWakeUpCheck(gActiveBattler))
                    {
                        CancelMultiTurnMoves(gActiveBattler);
                        gBattleMons[gActiveBattler].status1 |= STATUS1_SLEEP; //hopefully works and puts to sleep and sets sleep turns
                        gBattleMons[gActiveBattler].status1 |= ((Random() % 3) + 3); //since sleep is decremented at turn start not end turn, this is effectively 2-4 turns
                        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                        MarkBattlerForControllerExec(gActiveBattler);
                        gEffectBattler = gActiveBattler;
                        BattleScriptExecute(BattleScript_YawnMakesAsleep); //need test
                        ++effect;
                    }
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_SLEEP:
                if (gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP && gDisableStructs[gActiveBattler].sleepCounter)    //if works right should heal every 2 turns
                {
                    if (gBattleMons[gBattlerAttacker].maxHP > gBattleMons[gBattlerAttacker].hp
                        && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        gBattleMoveDamage = gBattleMons[gActiveBattler].maxHP / 5;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                    }
                    BattleScriptExecute(BattleScript_SleepHealing);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ROOST: // Return flying type.
                //may change sounds like its only lost for duration of move i.e 1 turn
                //which is dumb -_- that could only be taken advantage of in double battle
                //think I'll add a timer use Random() % 4 to find start value
                //pokemon will be grounded for the duration. and succeptible to all ground moves
                //setup like healblock timer above.
                //I'd like to have a little battlestring display when timer is at 0
                //something like "pokemonname" returned to the air or something..
                if (gDisableStructs[gActiveBattler].RoostTimer) //realized I never actually built the decrement lol
                    --gDisableStructs[gActiveBattler].RoostTimer;

                if (gBattleResources->flags->flags[gActiveBattler] & RESOURCE_FLAG_ROOST
                    && --gDisableStructs[gActiveBattler].RoostTimer == 0)
                {
                    gBattleResources->flags->flags[gActiveBattler] &= ~(RESOURCE_FLAG_ROOST);
                    MarkBattlerForControllerExec(gActiveBattler);
                    gEffectBattler = gActiveBattler;
                    BattleScriptExecute(BattlesScript_RoostEnds);
                    ++effect; //think logic is if execute/uses battle script use should increment effect?
                    //gBattleMons[gActiveBattler].type1 = gBattleStruct->roostTypes[gActiveBattler][0];
                    //gBattleMons[gActiveBattler].type2 = gBattleStruct->roostTypes[gActiveBattler][1];
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_ELECTRIFY:
                gStatuses4[gActiveBattler] &= ~STATUS4_ELECTRIFIED;
                ++gBattleStruct->turnEffectsTracker;
            case ENDTURN_POWDER:
                gBattleMons[gActiveBattler].status2 &= ~STATUS2_POWDER;
                ++gBattleStruct->turnEffectsTracker;
            case ENDTURN_THROAT_CHOP:
                if (gDisableStructs[gActiveBattler].throatChopTimer && --gDisableStructs[gActiveBattler].throatChopTimer == 0)
                {
                    BattleScriptExecute(BattleScript_ThroatChopEndTurn);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_SLOW_START:
                if (gDisableStructs[gActiveBattler].slowStartTimer
                    && --gDisableStructs[gActiveBattler].slowStartTimer == 0
                    && ability == ABILITY_SLOW_START)
                {
                    gBattleStruct->slowstartDone[gActiveBattler] = TRUE;
                    BattleScriptExecute(BattleScript_SlowStartEnds);
                    ++effect;
                }
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_PLASMA_FISTS:
                for (i = 0; i < gBattlersCount; i++)
                    gStatuses4[i] &= ~STATUS4_PLASMA_FISTS;
                //gStatuses4[gActiveBattler] &= ~STATUS4_PLASMA_FISTS; this line is emerald version...did I change how this works? can't think of why I would
                ++gBattleStruct->turnEffectsTracker;
                break;
            case ENDTURN_BIDE:
                //logic for if I want bide to have no drawback, with this it shouldn't consume a turn on unleaesh if you received no damage
                /*if (--gDisableStructs[gActiveBattler].bideTimer == 1 && gTakenDmg[gActiveBattler] == 0) //should display no energy string, then let select move
                { //should be decrement timer, if timer == 1 and taken no damage
                    MarkBattlerForControllerExec(gActiveBattler);
                    gEffectBattler = gActiveBattler;
                    BattleScriptExecute(BattleScript_BideNoEnergyToAttack); //hopefully works right

                }*/
                if (gBattleMons[gActiveBattler].status2 & STATUS2_BIDE && gDisableStructs[gActiveBattler].bideTimer != 0)
                {
                    //--gDisableStructs[gEffectBattler].bideTimer;
                    MarkBattlerForControllerExec(gActiveBattler);
                    gEffectBattler = gActiveBattler;
                    BattleScriptExecute(BattleScript_BideStoringEnergy);//hopefully don't need to change battlescript
                    ++effect;
                }//ends turn  //may need to swap this to target, depending on who's turn this plays at?
                ////from GriffinR, --timer meaens decreminet timer if timer != 0
                ++gBattleStruct->turnEffectsTracker;
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
    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    return 0;
}

bool8 HandleWishPerishSongOnTurnEnd(void)
{
    gHitMarker |= (HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
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
                && IsBlackFogNotOnField()   //should prevent decrement
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
    gHitMarker &= ~(HITMARKER_GRUDGE | HITMARKER_SKIP_DMG_TRACK);
    return FALSE;
}

#define FAINTED_ACTIONS_MAX_CASE 7

bool8 HandleFaintedMonActions(void)
{
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
            ++gBattleStruct->faintedActionsState; //should I add neutralizing gas here? // no neutralizing gas is already working
            break;
        case FAINTED_ACTIONS_MAX_CASE:
            break;
        }
    } while (gBattleStruct->faintedActionsState != FAINTED_ACTIONS_MAX_CASE);
    return FALSE;
}

void TryClearRageStatuses(void) //remove rage if  move used other than rage, changed so just don't call this
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
    CANCELLER_BLACK_FOG,
    CANCELLER_FLINCH,
    CANCELLER_DISABLED,
    CANCELLER_GRAVITY,
    CANCELLER_HEAL_BLOCKED,
    CANCELLER_TAUNTED,
    CANCELLER_IMPRISONED,
    CANCELLER_CONFUSED,
    CANCELLER_PARALYZED,
    CANCELLER_PRESSURE,
    CANCELLER_SPIRIT_LOCKED,
    CANCELLER_GHOST,
    CANCELLER_IN_LOVE,
    CANCELLER_BIDE,
    CANCELLER_THAW,
    CANCELLER_POWDER_MOVE,
    CANCELLER_POWDER_STATUS,
    CANCELLER_THROAT_CHOP,
    CANCELLER_MULTI_HIT_MOVES,
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
                else if (!IsBlackFogNotOnField()) //black fog on field wake up mon
                {
                    gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP);
                    gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_NIGHTMARE);
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedWokeUp; //how I want to work is wake up, attack next turn
                    effect = 2;
                }
                else // ok need to figure how this works, but seems to be sleep chance
                {

                    u8 toSub;

                    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_EARLY_BIRD)  //ok I think what happens is with ability early bird, you get 2 turns off your sleep timr
                        toSub = 2;  //each turn rather than 1, so still useful
                    else
                        toSub = 1;

                    if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP) < toSub)
                        gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP);
                    else if (GetBattlerAbility(gBattlerAttacker) == ABILITY_EARLY_BIRD
                        && Random() % 4 == 0)
                    {
                        gBattleMons[gBattlerAttacker].status1 &= ~(STATUS1_SLEEP); //ok this was my buff I gabe earlybird a chance to immediately wake up
                    }
                    else
                    {
                        gBattleMons[gBattlerAttacker].status1 -= toSub;
                        gDisableStructs[gBattlerAttacker].sleepCounter ^= 1;    //equivalent of truant, sleeper heals every other turn at end of turn
                    }


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
        case CANCELLER_FROZEN: // check being frozen //think I want change back and put decrement here in atk canceler like sleep does, more punishing for fast mon,  but also simpler endturn logic/messaging
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE && gDisableStructs[gActiveBattler].FrozenTurns != 0) //frozen solid
            {
                if (--gDisableStructs[gActiveBattler].FrozenTurns != 0)
                {
                    //if (Random() % 5)//ok found freeze chance, so 1 in 5 chance of thawing out, on freeze.  pretty much  random % 5 if not 0 stays frozen.
                    if (!THAW_CONDITION(gCurrentMove)) //attempt at frozn timr   actuallg best to put timer decrement at endturn, that way can have consistent freze duration
                    {
                        //--gDisableStructs[gActiveBattler].FrozenTurns != 0
                        gBattlescriptCurrInstr = BattleScript_MoveUsedIsFrozen;
                        gHitMarker |= HITMARKER_NO_ATTACKSTRING;
                    }
                    else //continue to thaw out  
                    {
                        ++gBattleStruct->atkCancellerTracker;
                        break;
                    } //check more make sure correct with thaw
                }
                else // unfreeze
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_DefrostBattler_KeepStatus;
                    //gBattlescriptCurrInstr = BattleScript_MoveUsedUnfroze;
                    gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                }
                effect = 2; //changed thaw condition to fire move min 60 base power not fire fang
            }   //done should no longer need thaw effects already replaced
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_TRUANT: // truant
            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_TRUANT && gDisableStructs[gBattlerAttacker].truantCounter)
            {
                CancelMultiTurnMoves(gBattlerAttacker);
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_LOAFING;
                if (gBattleMons[gBattlerAttacker].maxHP > gBattleMons[gBattlerAttacker].hp
                    && !(gSideStatuses[GET_BATTLER_SIDE(gActiveBattler)] & SIDE_STATUS_HEAL_BLOCK))
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 5;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                }
                gBattlescriptCurrInstr = BattleScript_MoveUsedLoafingAround;
                //BattleScriptPushCursorAndCallback(BattleScript_HealWithoutMessage);
                //gMoveResultFlags |= MOVE_RESULT_MISSED; //this could be a problem to prevent healing? idk leave for now test later
                effect = 1; //apears to be a stopgap? will make moves miss if the truant somehow fails to stop attack
                //also yup that move result missed line was the last issue, making move miss got rid of damage
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_RECHARGE: // recharge
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RECHARGE) //add clause for new dialga ability
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
        case CANCELLER_BLACK_FOG: // fly sky drop block
            if (!IsBlackFogNotOnField()) // black fog on field
            {
                if ((gCurrentMove == MOVE_FLY) || (gCurrentMove == MOVE_SKY_DROP))
                {
                    CancelMultiTurnMoves(gBattlerAttacker);
                    gBattlescriptCurrInstr = BattleScript_ButItFailed; //could make custom script leave as is for now, need test vsonic
                    gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                    effect = 1;
                }

            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_FLINCH: // flinch
            if ((IsAbilityOnField(ABILITY_STENCH))
                && (GetBattlerAbility(gBattlerAttacker) != ABILITY_STENCH
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_INNER_FOCUS
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_OBLIVIOUS
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_LEAF_GUARD
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_SWEET_VEIL
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_AROMA_VEIL
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_FLOWER_VEIL
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_AFTERMATH //immune for opposite reason also putride
                    ) //or could just make grass & poison immune? thinking of removing aftermath exclusion..
                && Random() % 5 == 0)   //should be 20% chance to set status to battler
            {
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_FLINCHED;  //set status
            }

            if ((gBattleMons[gBattlerAttacker].status4 & STATUS4_CLAMP) && ((Random() % 3) == 1))
            {
                gBattleMons[gBattlerAttacker].status2 |= STATUS2_FLINCHED;
                //gProtectStructs[gBattlerAttacker].prlzImmobility = 1;
                //gBattlescriptCurrInstr = BattleScript_MoveUsedIsParalyzed;
                //gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                //effect = 1;  don'et need set effect it'll be done in flinch case
            }

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
        case CANCELLER_GRAVITY: //ok this is what I want for fly chaneg I think?
            if (gFieldStatuses & STATUS_FIELD_GRAVITY && IsGravityPreventingMove(gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedGravityPreventedMove = TRUE;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedGravityPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_HEAL_BLOCKED:
            if (gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_HEAL_BLOCK && IsHealBlockPreventingMove(gBattlerAttacker, gCurrentMove))
            {
                gProtectStructs[gBattlerAttacker].usedHealBlockedMove = TRUE;
                gBattleScripting.battler = gBattlerAttacker;
                CancelMultiTurnMoves(gBattlerAttacker); //vsonic need look into this, may cause issues
                gBattlescriptCurrInstr = BattleScript_MoveUsedHealBlockPrevents;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
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
        case CANCELLER_CONFUSED: // confusion need test but done, until double battles are in
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION)//can add bug type exclusion here, they will have confusion affect but never fail atk check
            { //users most likely won't notice the difference unless they attack themselves
                u16 rando = Random() % 4;
                u8 target = gBattleMoves[gCurrentMove].target;
                --gBattleMons[gBattlerAttacker].status2;    //nvm couldn't put bug clause above this line, or confusion wouldn't decrement & be permanent

                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_CONFUSION && IsBlackFogNotOnField()) //&& !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_BUG))
                {// idea cammymealtee trying setup so tangled feet like bug gets confused but never hits themselves
                    if (!IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_BUG) || GetBattlerAbility(gBattlerAttacker) != ABILITY_TANGLED_FEET) //moved bug exclusion to here, so status decrements //NEED TEST //vsonic
                    {
                        if ((Random() % 2) == 0) //chance confused but used move anyway   think 50% may equal random % 2 not 0
                        {
                            if ((Random() % 3) != 0) {   //2/3 chance succesful attack     (doesn't mean not 0,its just returning any value between 0-2)
                                // The MULTISTRING_CHOOSER is used here as a bool to signal
                                // to BattleScript_MoveUsedIsConfused whether or not damage was taken
                                gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;  //need to say != 0 or something, to make it a 2/3rd conditional
                                BattleScriptPushCursor();
                            }
                            else { // 1/3 odds target gets randomly changed
                                if (rando == 0) {
                                    target = MOVE_TARGET_RANDOM;
                                    gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;
                                    BattleScriptPushCursor();
                                }
                                if (rando == 1) {
                                    target = MOVE_TARGET_BOTH;
                                    gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;
                                    BattleScriptPushCursor();
                                }
                                if (rando == 2) {
                                    target = MOVE_TARGET_FOES_AND_ALLY;
                                    gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;
                                    BattleScriptPushCursor();
                                }
                                if (rando == 3) //hits everyone
                                {
                                    target = MOVE_TARGET_USER | MOVE_TARGET_FOES_AND_ALLY;
                                    gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                                    gProtectStructs[gBattlerAttacker].confusionSelfDmg = TRUE;
                                    BattleScriptPushCursor(); //not sure what this is doing
                                } //if it works  may still add just target ally


                            }
                            //gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                            //BattleScriptPushCursor();
                        }
                        else // confusion dmg  //yup oddds are 50%  this is the other side where they attack themselves
                        { //ok I want to keep the sucess condition the same, but split the failure condition.
                            //into different effects,
                            //1 attack a random target
                            //ok understand what I did, I have to separte activation conditions for if its a status move
                            //or not and make sure the move does at least 1/16 health damage, 
                            //if its a status it'll do normal confusion self damage I didn't remove that.
                            gBattlerTarget = gBattlerAttacker;  //Handles target swap
                            gBattleMoveDamage /= 2; //should use move against self at half normal power
                            if (gBattleMoveDamage < gBattleMons[gBattlerTarget].maxHP / 16
                                && gBattleMovePower > 0)
                                gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 16; //minimum dmg clause
                            gProtectStructs[gBattlerAttacker].confusionSelfDmg = 1;

                            if (gBattleMovePower == 0) //if status move does default confusion hit 
                            {
                                gBattleCommunication[MULTISTRING_CHOOSER] = TRUE;
                                //gBattlerTarget = gBattlerAttacker;    this line not needed already handled above
                                gBattleMoveDamage = CalculateBaseDamage(&gBattleMons[gBattlerAttacker], &gBattleMons[gBattlerAttacker], MOVE_POUND, 0, 40, 0, gBattlerAttacker, gBattlerAttacker);
                                gProtectStructs[gBattlerAttacker].confusionSelfDmg = 1;
                                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                            }//consider make this status moves (i.e 0 power) & moves without flag makes contact use normal confusion dmg formula 
                            //for self damage   so only contact moves would go off and damage the attacker
                        }
                    }
                    else //should be if bug type, should make bug always use move regardless of being confused
                    {
                        // The MULTISTRING_CHOOSER is used here as a bool to signal
                        // to BattleScript_MoveUsedIsConfused whether or not damage was taken
                        gBattleCommunication[MULTISTRING_CHOOSER] = FALSE;
                        BattleScriptPushCursor();
                    }
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfused; //want to make sure still takes confusion damage 
                } //even for status move or 0 power move, it makes sense they attempt ot attack but fail and hurt themselves.
                else // snapped out of confusion
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MoveUsedIsConfusedNoMore;
                }
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_PARALYZED: // paralysis
            if (((gBattleMons[gBattlerAttacker].status1 & STATUS1_PARALYSIS) && (Random() % 4) == 0)
                && IsBlackFogNotOnField())
            {
                gProtectStructs[gBattlerAttacker].prlzImmobility = 1;
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsParalyzed;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_PRESSURE: // new pressure effect
            if (((GetBattlerAbility(gBattlerTarget) == ABILITY_PRESSURE
                || GetBattlerAbility(gBattlerTarget) == ABILITY_HI_PRESSURE)
                && (Random() % 4) == 1)
                && IsBlackFogNotOnField())
            {
                gProtectStructs[gBattlerAttacker].prlzImmobility = 1;
                gBattlescriptCurrInstr = BattleScript_MovePressureCanceler;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_SPIRIT_LOCKED: //spirit lock
            if ((gBattleMons[gBattlerAttacker].status1 & STATUS1_SPIRIT_LOCK) && (Random() % 4) == 2) //just an extra precaution in case this and paralysis would use the same counter
            {
                //gProtectStructs[gBattlerAttacker].prlzImmobility = 1;
                //gBattlescriptCurrInstr = BattleScript_MoveUsedIsParalyzed;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            } //vsonic add on to/finish effedct
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
                //&& gBattleMons[gBattlerAttacker].status2 |= STATUS2_INFATUATED_WITH(gBattlerTarget)) //important change ot add check that the target is the one pokemon is infatuated with
            {
                if (IsBlackFogNotOnField()) {


                    gBattleScripting.battler = CountTrailingZeroBits((gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION) >> 0x10);
                    if (Random() & 1) //test if that worked, next step change so infatuation animation only plays if battler their infatuated with is on the field.
                        //well maybe not, if it reminds you each turn, even if not there, its a good reminder the status is still in effect.
                    {
                        BattleScriptPushCursor(); //unfortunately didn't work, will look into it later
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
                else if (!IsBlackFogNotOnField() //black fog on field
                    && (GetBattlerAbility(gBattlerTarget) == ABILITY_CUPIDS_ARROW))
                {
                    gBattleScripting.battler = CountTrailingZeroBits((gBattleMons[gBattlerAttacker].status2 & STATUS2_INFATUATION) >> 0x10);

                    if (Random() & 1) //test if that worked, next step change so infatuation animation only plays if battler their infatuated with is on the field.
                        //well maybe not, if it reminds you each turn, even if not there, its a good reminder the status is still in effect.
                    {
                        BattleScriptPushCursor(); //unfortunately didn't work, will look into it later
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
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_BIDE: // bide
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)//still need logic so can't use bide with status bide
            {
                //gBattleMons[gBattlerAttacker].status2 -= STATUS2_BIDE_TURN(1);
                --gDisableStructs[gBattlerAttacker].bideTimer;

                /*if (((gBattleMoves[gCurrentMove].power == 0) || (gCurrentMove == MOVE_COUNTER || MOVE_MIRROR_COAT))
                    && gDisableStructs[gBattlerAttacker].bideTimer) {
                    effect = 1;

                    //gBattleStruct->atkCancellerTracker++;
                    //break;
                }*/ //should move to checking other cancelr casese hopefully
                //trying to skip move cancel, long as not bide attack turn or damaging moeve

                if (gCurrentMove == MOVE_BIDE
                    && gDisableStructs[gBattlerAttacker].bideTimer) //status is set after this, so firt use should never trigger fail.
                {
                    gBattlescriptCurrInstr = BattleScript_ButItFailedAtkStringPpReduce;
                    effect = 1;
                    break;
                }

                if (gDisableStructs[gBattlerAttacker].bideTimer && gBattleMoves[gCurrentMove].power != 0
                    && (gCurrentMove != MOVE_COUNTER || gCurrentMove != MOVE_MIRROR_COAT))
                {
                    gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_BIDE;
                    //gDisableStructs[gBattlerAttacker].bideTimer = 0;
                    //realized without setting timer to 0, using bide again, would proc this & remove status immediately
                    //effect = 1;
                   //gBattleStruct->atkCancellerTracker++;
                    //break;

                    //gBattlescriptCurrInstr = BattleScript_BideStoringEnergy;//move to end turn w status bide end turn effect function
                }//instead let you use a damaging attack but remove bide status and reset timer
                if (gDisableStructs[gBattlerAttacker].bideTimer == 0)
                    //&& gBattleMons[gBattlerAttacker].status2 & STATUS2_BIDE)
                {
                    // This is removed in FRLG and Emerald for some reason
                    //gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_MULTIPLETURNS;
                   //gBattleMons[gBattlerAttacker].status2 &= ~STATUS2_BIDE; //to remove bide status  //removed had alrady setup in turnvaluecleanup in battle_main.c
                    //and since atkcanceler is before setbide command better to remove status at endturn anyway
                    if (gTakenDmg[gBattlerAttacker])  //if taken dmg not 0?
                    {
                        gCurrentMove = MOVE_BIDE;
                        //gBattleMoves[gCurrentMove].priority = 3; //if works, second attack will go before most priority moves
                        *bideDmg = gTakenDmg[gBattlerAttacker] * 23 / 10; //not sure how it loops rn, but I believe it copies to a separate variable
                      //  *bideDmg = gTakenDmg[gBattlerAttacker] * 2;   //may go back to 2x if 2.3 is too much
                        gBattlerTarget = gTakenDmgByBattler[gBattlerAttacker];
                        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                            gBattlerTarget = GetMoveTarget(MOVE_BIDE, MOVE_TARGET_SELECTED + 1);
                        gBattlescriptCurrInstr = BattleScript_BideAttack;
                    }
                    else
                    {
                        gCurrentMove = MOVE_BIDE;
                        gBattlescriptCurrInstr = BattleScript_BideNoEnergyToAttack;
                    }
                    effect = 1;
                }

            }//since similar just adding dryads curse logic here
            if (gCurrentMove == MOVE_DRYADS_CURSE)  //changed from elses if, so both can run together
            {
                if (gTakenDmg[gBattlerAttacker])    //if took damage from enemy  (believe that turn)
                {

                    gBattlerTarget = gTakenDmgByBattler[gBattlerAttacker];
                    if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
                        gBattlerTarget = GetMoveTarget(MOVE_DRYADS_CURSE, 1);
                }
                else
                {
                    gBattlescriptCurrInstr = BattleScript_ButItFailedAtkStringPpReduce;
                }//prob don't need to put here consider later  vsonic
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_THAW: // move thawing
            if (gBattleMons[gBattlerAttacker].status1 & STATUS1_FREEZE
                && gDisableStructs[gBattlerAttacker].FrozenTurns != 0) //should be thaw if scald, or a fire type move above base 60
            {
                if (THAW_CONDITION(gCurrentMove))
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
            if ((gBattleMoves[gCurrentMove].flags & FLAG_POWDER_MOVE) && (gBattlerAttacker != gBattlerTarget))
            {
                if ((IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_GRASS))
                    || GetBattlerAbility(gBattlerTarget) == ABILITY_OVERCOAT)
                {
                    gBattlerAbility = gBattlerTarget;
                    effect = 1;
                }
                else if (GetBattlerHoldEffect(gBattlerTarget, TRUE) == HOLD_EFFECT_SAFETY_GOGGLES)
                {
                    RecordItemEffectBattle(gBattlerTarget, HOLD_EFFECT_SAFETY_GOGGLES);
                    gLastUsedItem = gBattleMons[gBattlerTarget].item;
                    effect = 1;
                }

                if (effect)
                    gBattlescriptCurrInstr = BattleScript_PowderMoveNoEffect;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_POWDER_STATUS:   //doesn't make sense for grass type to be immune to this but will keep anyway
            if (gBattleMons[gBattlerAttacker].status2 & STATUS2_POWDER)
            {
                u32 moveType;
                GET_MOVE_TYPE(gCurrentMove, moveType);
                if (moveType == TYPE_FIRE)
                {
                    gProtectStructs[gBattlerAttacker].powderSelfDmg = TRUE;
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                    gBattlescriptCurrInstr = BattleScript_MoveUsedPowder;
                    effect = 1;
                }
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_THROAT_CHOP:
            if (gDisableStructs[gBattlerAttacker].throatChopTimer && gBattleMoves[gCurrentMove].flags & FLAG_SOUND)
            {
                gProtectStructs[gBattlerAttacker].usedThroatChopPreventedMove = TRUE;
                CancelMultiTurnMoves(gBattlerAttacker);
                gBattlescriptCurrInstr = BattleScript_MoveUsedIsThroatChopPrevented;
                gHitMarker |= HITMARKER_UNABLE_TO_USE_MOVE;
                effect = 1;
            }
            ++gBattleStruct->atkCancellerTracker;
            break;
        case CANCELLER_MULTI_HIT_MOVES: //set multihit counter
            {
                switch(gBattleMoves[gCurrentMove].effect)
                {   
                    case EFFECT_FURY_CUTTER:
                    {
                        gMultiTask = 5; //unique effect given acc drop, lowered acc drop rate
                        break;
                    }
                    case EFFECT_PRESENT:
                    {
                        gMultiTask = Random() % 4; //return a number between 0 & 3
                        if (gMultiTask > 1)
                            gMultiTask = (Random() % 3) + 3; // if non 0, present lands between 3-5 htis
                        else
                            gMultiTask += 3; //else present lands 3 hits /odds of dmg vs heal is in presentdamagecalc
                        break;
                    }
                    case EFFECT_MULTI_HIT:
                    {
                        gMultiTask = Random() % 4; //return a number between 0 & 3
                        if (gMultiTask > 1)
                            gMultiTask = (Random() % 4) + 2; // if non 0, multihit is between 2-5 htis
                        else
                            gMultiTask += 2; //else add 2 to multi counter, returning a multihit of 2.
                        break;
                    }
                    case EFFECT_TWINEEDLE:
                    case EFFECT_DOUBLE_HIT:
                    case EFFECT_DOUBLE_IRON_BASH:
                        gMultiTask = 2;
                        break;
                    case EFFECT_TRIPLE_KICK: //triple kick, triple axel, & surging strikes
                        gMultiTask = 3;
                        break;         
                    default:
                    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_MULTI_TASK
                        && (CanMultiTask(gCurrentMove) == TRUE))
                        {
                            gMultiTask = Random() % 4; //return a number between 0 & 3
                            if (gMultiTask > 1)
                                gMultiTask = (Random() % 4) + 2; // if non 0, multihit is between 2-5 htis
                            else
                                gMultiTask += 2; //else add 2 to multi counter, returning a multihit of 2.
                        }
                        break;
                }

                if ((GetBattlerAbility(gBattlerAttacker) == ABILITY_SKILL_LINK)
                    || (GetBattlerAbility(gBattlerAttacker) == ABILITY_MULTI_TASK)) //will only affect multi hit & fury cutter /was just meant to be for things that were already multihit
                {
                    if (gBattleMoves[gCurrentMove].effect == EFFECT_MULTI_HIT
                        //|| (gBattleMoves[gCurrentMove].effect == EFFECT_FURY_CUTTER)
                        || (gBattleMoves[gCurrentMove].effect == EFFECT_PRESENT) //to exclude from damagecalc multitask split need add these effects back to miultitask exclusion
                        ) //this will still work, it'll just stop the dmg from getting affected/cut
                        gMultiTask = 5;                
                } //put this part at bottom of multihit

                gMultiHitCounter = gMultiTask;
                
            }    
            ++gBattleStruct->atkCancellerTracker;
                break; 
        case CANCELLER_END:
            break;
        } //end of main switch

    } while (gBattleStruct->atkCancellerTracker != CANCELLER_END && gBattleStruct->atkCancellerTracker != CANCELLER_END2 && effect == 0);
                    //while atkunable touse move hasnt ended, or atkunable to use move 2 hasnt ended and effect is 0 keep looping
                    //so stops soon as effect is set
    if (effect == 2)
    {
        gActiveBattler = gBattlerAttacker;
        BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
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

//logic for this is non-flying type pokemon that are typically
//floating or attack while in the air/ can fly
//already checked to add all pokemon that have levitate as their ability
//2nd pass add ghosts to grounded clause  with specific exclusions spirit tomb cursola galarian corsola etc object linked ghost, just like doduo
//looked over and realized still mising some pokemon that float, but aren't flying types, and also just don't get levitate
//i.e porygon and magnemite line, may be others
//delete value in bracket to see actual list total w intellisense to make sure total is correct before final save
//update define in battle_util.h if diff
const u16 gFloatingSpecies[157] = {
    SPECIES_BUTTERFREE,
    SPECIES_BEAUTIFLY,
    SPECIES_VIVILLON,
    SPECIES_MOTHIM,
    SPECIES_COMBEE,
    SPECIES_DUSTOX,
    SPECIES_BEEDRILL,
    SPECIES_MASQUERAIN,
    SPECIES_NINJASK,
    SPECIES_SHEDINJA,
    SPECIES_VOLBEAT,
    SPECIES_ILLUMISE,
    SPECIES_VIKAVOLT,
    SPECIES_DUSCLOPS,
    SPECIES_DUSKNOIR,
    SPECIES_DUSKULL,
    SPECIES_CHARIZARD_MEGA_X,
    SPECIES_VENOMOTH,
    SPECIES_GASTLY,
    SPECIES_HAUNTER,
    SPECIES_GENGAR,
    SPECIES_DUNSPARCE,
    SPECIES_AERODACTYL,
    SPECIES_AERODACTYL_MEGA,
    SPECIES_MEW,
    SPECIES_MEWTWO,
    SPECIES_LUGIA,
    SPECIES_MEWTWO_MEGA_X,
    SPECIES_MEWTWO_MEGA_Y,
    SPECIES_SCIZOR,
    SPECIES_LEDYBA,
    SPECIES_LEDIAN,
    SPECIES_CELEBI,
    SPECIES_TOGETIC,
    SPECIES_ALTARIA,
    SPECIES_ALTARIA_MEGA,
    SPECIES_LUNATONE,
    SPECIES_SOLROCK,
    SPECIES_MISDREAVUS,
    SPECIES_MISMAGIUS,
    SPECIES_BALTOY,
    SPECIES_CLAYDOL,
    SPECIES_PORYGON,
    SPECIES_PORYGON2,
    SPECIES_PORYGON_Z,
    SPECIES_BELDUM,
    SPECIES_METANG,
    SPECIES_METAGROSS,
    SPECIES_LATIAS,
    SPECIES_LATIOS,
    SPECIES_BRONZOR,
    SPECIES_BRONZONG,
    SPECIES_YANMEGA,
    SPECIES_MAGNEMITE,
    SPECIES_MAGNETON,
    SPECIES_MAGNEZONE,
    SPECIES_CHATOT,
    SPECIES_CARNIVINE,
    SPECIES_ROTOM,
    SPECIES_UXIE,
    SPECIES_AZELF,
    SPECIES_MESPRIT,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS,
    SPECIES_DEOXYS_ATTACK,
    SPECIES_DEOXYS_DEFENSE,
    SPECIES_DEOXYS_SPEED,
    SPECIES_GIRATINA_ORIGIN,
    SPECIES_GENGAR_MEGA,
    SPECIES_LATIAS_MEGA,
    SPECIES_LATIOS_MEGA,
    SPECIES_CRESSELIA,
    SPECIES_MUNNA,
    SPECIES_MUSHARNA,
    SPECIES_DARKRAI,
    SPECIES_VIBRAVA,
    SPECIES_FLYGON,
    SPECIES_HYDREIGON,
    SPECIES_VOLCARONA,
    SPECIES_TYNAMO,
    SPECIES_EELEKTRIK,
    SPECIES_EELEKTROSS,
    SPECIES_KOFFING,
    SPECIES_WEEZING,
    SPECIES_WEEZING_GALARIAN,
    SPECIES_RAICHU_ALOLAN,
    SPECIES_BUZZWOLE,
    SPECIES_UNOWN,
    SPECIES_UNOWN_B,
    SPECIES_UNOWN_C,
    SPECIES_UNOWN_D,
    SPECIES_UNOWN_E,
    SPECIES_UNOWN_EMARK,
    SPECIES_UNOWN_F,
    SPECIES_UNOWN_QMARK,
    SPECIES_UNOWN_G,
    SPECIES_UNOWN_H,
    SPECIES_UNOWN_I,
    SPECIES_UNOWN_J,
    SPECIES_UNOWN_K,
    SPECIES_UNOWN_L,
    SPECIES_UNOWN_M,
    SPECIES_UNOWN_N,
    SPECIES_UNOWN_O,
    SPECIES_UNOWN_P,
    SPECIES_UNOWN_Q,
    SPECIES_UNOWN_R,
    SPECIES_UNOWN_S,
    SPECIES_UNOWN_T,
    SPECIES_UNOWN_U,
    SPECIES_UNOWN_V,
    SPECIES_UNOWN_W,
    SPECIES_UNOWN_X,
    SPECIES_UNOWN_Y,
    SPECIES_UNOWN_Z,
    SPECIES_CASTFORM,
    SPECIES_CASTFORM_RAINY,
    SPECIES_CASTFORM_SNOWY,
    SPECIES_CASTFORM_SUNNY,
    SPECIES_ROTOM_FAN,
    SPECIES_ROTOM_WASH,
    SPECIES_ROTOM_FROST,
    SPECIES_ROTOM_MOW,
    SPECIES_ROTOM_HEAT,
    SPECIES_CUTIEFLY,
    SPECIES_RIBOMBEE,
    SPECIES_SOLOSIS,
    SPECIES_DUOSION,
    SPECIES_REUNICLUS,
    SPECIES_COMFEY,
    SPECIES_BEEDRILL_MEGA,
    SPECIES_RESHIRAM,
    SPECIES_ZEKROM,
    SPECIES_KYUREM,
    SPECIES_KYUREM_WHITE,
    SPECIES_KYUREM_BLACK,
    SPECIES_COSMOG,
    SPECIES_COSMOEM,
    SPECIES_LUNALA,
    SPECIES_NECROZMA,
    SPECIES_NECROZMA_DUSK_MANE,
    SPECIES_NECROZMA_DAWN_WINGS,
    SPECIES_NECROZMA_ULTRA,
    SPECIES_NIHILEGO,
    SPECIES_KARTANA,
    SPECIES_ORBEETLE,
    SPECIES_POIPOLE,
    SPECIES_NAGANADEL,
    SPECIES_FLAPPLE,
    SPECIES_FROSMOTH,
    SPECIES_DREEPY,
    SPECIES_DRAKLOAK,
    SPECIES_DRAGAPULT,
    SPECIES_REGIDRAGO,
    SPECIES_ARCEUS,
    SPECIES_ETERNATUS,
    SPECIES_ETERNATUS_ETERNAMAX
};

bool8 IsFloatingSpecies(u8 battlerId) {
    s32 i;


    for (i = 0; i < NELEMS(gFloatingSpecies); i++)
    {
        if (gBattleMons[battlerId].species == gFloatingSpecies[i])
            return TRUE;
    }
    return FALSE;

}


#define GROUNDED_FUNCTION
//remember else if, makes it exclusive, it only goes to that if the if before it is false,
//and it itself gets skipped over if its false, to the go to the next else if
//need to comb over else if logic to make sure parses
bool8 IsBattlerGrounded(u8 battlerId)
//important done for now, need test later
//finihsed adding to type calc, so should be battle ready
//set as type 8, instead of 32 for test build
{
    u32 species = gBattleMons[battlerId].species;
    bool8 grounded = TRUE; //changed so goes through all checks  //not using else, so need to make it default TRUE



    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_FLYING) && (gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_ROOST))
        grounded = TRUE; //hope this set up right/works
    //according to Mcgriffin needed make flying & roost flag true statement
    //as else at bottom just means not flyign or has roost flag, TRUE
    if (gStatuses4[battlerId] & STATUS4_GROUNDED)
        grounded = TRUE;
    if (gFieldStatuses & STATUS_FIELD_GRAVITY)
        grounded = TRUE;
    if (gFieldStatuses & STATUS_FIELD_BLACK_FOG) //on review this does make sense, its not that they are face down on the ground its that flying higher isn't an option
        grounded = TRUE;
    if (gStatuses3[battlerId] & STATUS3_ROOTED)
        grounded = TRUE;
    if (gStatuses3[battlerId] & STATUS3_SMACKED_DOWN)
        grounded = TRUE;
    if (species == (SPECIES_DODUO || SPECIES_DODRIO || SPECIES_ARCHEN || SPECIES_ARCHEOPS))
        grounded = TRUE;//edit because flightless bird
    if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_IRON_BALL)
        grounded = TRUE;
    if ((IS_BATTLER_OF_TYPE(battlerId, TYPE_GHOST)) && (species == (GROUNDED_GHOSTMON)))   //test GHOST exclusions
        grounded = TRUE;

    else if (IS_BATTLER_OF_TYPE(battlerId, TYPE_GHOST))
        grounded = FALSE;

    if (IsFloatingSpecies(battlerId))//used if as breakline, as else if only reads if everything above it is false
        grounded = FALSE;
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_FLYING) 
    && (species != SPECIES_DODUO && species != SPECIES_DODRIO
        && species != SPECIES_ARCHEN && species != SPECIES_ARCHEOPS)
        && !(gBattleResources->flags->flags[battlerId] & RESOURCE_FLAG_ROOST))
        grounded = FALSE;  

    if (gBattleMons[battlerId].ability == ABILITY_LEVITATE) //remove after removing all instances of levitate on mon  vsonic
        grounded = FALSE;    
    if (gStatuses3[battlerId] & STATUS3_TELEKINESIS)
        grounded = FALSE;
    if (gStatuses3[battlerId] & STATUS3_MAGNET_RISE)
        grounded = FALSE;
    if (gStatuses3[battlerId] & STATUS3_ON_AIR)
        grounded = FALSE;
    if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_AIR_BALLOON)
        grounded = FALSE;

    if (gStatuses3[battlerId] & STATUS3_UNDERGROUND)
        grounded = TRUE;
    
        return grounded;
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

static const u16 sWeatherFlagsInfo[][3] =
{
    [ENUM_WEATHER_RAIN_PRIMAL] =  {WEATHER_RAIN_PRIMAL,         WEATHER_RAIN_PRIMAL,         HOLD_EFFECT_DAMP_ROCK},
    [ENUM_WEATHER_RAIN] =         {WEATHER_RAIN_TEMPORARY,      WEATHER_RAIN_PERMANENT,      HOLD_EFFECT_DAMP_ROCK},
    [ENUM_WEATHER_SUN_PRIMAL] =   {WEATHER_SUN_PRIMAL,          WEATHER_SUN_PRIMAL,          HOLD_EFFECT_HEAT_ROCK},
    [ENUM_WEATHER_SUN] =          {WEATHER_SUN_TEMPORARY,       WEATHER_SUN_PERMANENT,       HOLD_EFFECT_HEAT_ROCK},
    [ENUM_WEATHER_SANDSTORM] =    {WEATHER_SANDSTORM_TEMPORARY, WEATHER_SANDSTORM_PERMANENT, HOLD_EFFECT_SMOOTH_ROCK},
    [ENUM_WEATHER_HAIL] =         {WEATHER_HAIL,                WEATHER_HAIL_PERMANENT,      HOLD_EFFECT_ICY_ROCK},
    [ENUM_WEATHER_STRONG_WINDS] = {WEATHER_STRONG_WINDS,        WEATHER_STRONG_WINDS,        HOLD_EFFECT_NONE},
};

//abilities that don't use timer
static const u16 sPermanentWeatherAbilities[] = {
    ABILITY_DESOLATE_LAND,
    ABILITY_PRIMORDIAL_SEA,
    ABILITY_DELTA_STREAM,
};


static const u16 sSwitchAbilities[][10] = {
[REPEAT_SWITCH_IN] = {ABILITY_MOLD_BREAKER, ABILITY_TERAVOLT, ABILITY_TURBOBLAZE, ABILITY_UNNERVE, ABILITY_ANTICIPATION, ABILITY_FRISK, ABILITY_FOREWARN, ABILITY_INTIMIDATE, ABILITY_TRACE, ABILITY_NEUTRALIZING_GAS}
};
//first bracket number of rows in array, (auto defined)
//second bracket number of members in array, each line willl have that many arguments
//ok set it up correctly so now it doesn't break connections

#define WEATHER_AND_TERRAIN_EFFECTS                                           //pretty sure this is doing nothing, like I'm just not applying it? nvm it is used, its in weather abilities but not move abilities function i.e not in setsunny
bool32 TryChangeBattleWeather(u8 battler, u32 weatherEnumId, bool32 viaAbility) //need check where this is used, in emerald its used in sunny day stuff etc.
{
    u16 battlerAbility = GetBattlerAbility(battler);

    //for (i = 0; i < NELEMS(sPermanentWeatherAbilities); i++)//changign only primals  and overworld weathr are permanent weather, 
                                                       //drought drizzle is temp but doesn't decrement long as their on field, so effectively permanent

        if (gBattleWeather & WEATHER_PRIMAL_ANY
            && battlerAbility != ABILITY_DESOLATE_LAND
            && battlerAbility != ABILITY_PRIMORDIAL_SEA
            && battlerAbility != ABILITY_DELTA_STREAM)
        {
            return FALSE;
        }//if primal weather set, can't change it, except by other primal effect


                                                                        //without for loop don't need this line as its already saying not primal just by being else if
        /*else if (viaAbility && !(gBattleWeather & WEATHER_PRIMAL_ANY))   ////can change if not primal means it can change permanant set weather I think
        {
            gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1]);   //1 is permanent weather,0 is temp
            return TRUE; //I think this sets permanent weather?
        }*/
            //checks if that type of weather has been set in permanent, sets temp weather if noto already set
        else if ((viaAbility && !(gBattleWeather & (sWeatherFlagsInfo[weatherEnumId][1]))) //remove temp filter so it continues to script announcing ability, as it is still psuedo permanent
            && (battlerAbility == ABILITY_DROUGHT || battlerAbility == ABILITY_DRIZZLE))
        {
            gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0]);
            if (GetBattlerHoldEffect(battler, TRUE) == sWeatherFlagsInfo[weatherEnumId][2]) //2 is weather extending hold effect
                gWishFutureKnock.weatherDuration = 8;
            else
                gWishFutureKnock.weatherDuration = 5;

            return TRUE;
        }//want drought and drizzle to be special with this they can't be overwritten by other temp weather abilities
        //believe this is for squall and sun disk,  if not primal and not permanent weather, set temp weather with ability

        //move based weather change & other normal weather abilities
        else if ((!(gBattleWeather & (sWeatherFlagsInfo[weatherEnumId][0] | sWeatherFlagsInfo[weatherEnumId][1])))  //CHECK specific weather isn't alraedy set
            && (!IsAbilityOnField(ABILITY_DROUGHT) && !IsAbilityOnField(ABILITY_DRIZZLE))) //need test if prevents weather change while kyogre/groudon on field
        {
            gBattleWeather = (sWeatherFlagsInfo[weatherEnumId][0]); //set temp weather if meet conditions
            if (GetBattlerHoldEffect(battler, TRUE) == sWeatherFlagsInfo[weatherEnumId][2]) //2 is weather extending hold effect
                gWishFutureKnock.weatherDuration = 8;
            else
                gWishFutureKnock.weatherDuration = 5;

            return TRUE;
        }


        return FALSE;
    

}

//since this just sets timer and terrain,  
     //to make permanent need to set conditions on timer decrement
    //or I could set a timer that would effectively never end
    //when terrain changed by ability
//may set permanent terrain or make permanent terrain if only set form overworld, and ability)
static bool32 TryChangeBattleTerrain(u32 battler, u32 statusFlag, u8 *timer)
{
    if (!(gFieldStatuses & statusFlag))
    {//think means clear any existing field terrain and set terrain / oh this also clears mud/water sport
        gFieldStatuses &= ~(STATUS_FIELD_MISTY_TERRAIN | STATUS_FIELD_GRASSY_TERRAIN | STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_PSYCHIC_TERRAIN);
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
        {ABILITY_ZEN_MODE, SPECIES_DARMANITAN_ZEN_MODE_GALARIAN, SPECIES_DARMANITAN_GALARIAN, 4},   //realized with this function, I can set different logic for same ability
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


static u8 ForewarnChooseMove(u32 battler) //important add to list of switch in moves to work on reset
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
        if (IsBattlerAlive(i) && GetBattlerSide(i) != GetBattlerSide(battler))  //battler is me, i is opponent
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (gBattleMons[i].moves[j] == MOVE_NONE)
                    continue;
                data[count].moveId = gBattleMons[i].moves[j];
                data[count].battlerId = i;
                switch (gBattleMoves[data[count].moveId].effect)    //add more conditions for move effect for smarter move choice
                {//i.e for archetypes mon with highest stat being speed, or defense etc. high speed mon worrying about paralysis etc.
                    //high phys atk worrying about burn etc.
                case EFFECT_OHKO:
                    if (gBattleMons[i].level >= (gBattleMons[battler].level - 7))
                        data[count].power = 150;
                    else
                        data[count].power = 0;
                    break;
                case EFFECT_EXPLOSION:
                    if ((data[count].moveId == MOVE_SELF_DESTRUCT
                        || data[count].moveId == MOVE_EXPLOSION)
                        && (!(IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))))
                        data[count].power = 200;
                    else if (data[count].moveId == MOVE_MISTY_EXPLOSION
                        && (!(IS_BATTLER_OF_TYPE(battler, TYPE_GRASS))))
                        data[count].power = 200;
                    else
                        data[count].power = 0;
                case EFFECT_COUNTER:
                case EFFECT_MIRROR_COAT:
                case EFFECT_METAL_BURST:
                    data[count].power = 120;
                    break;//add EFFECT_ENDEAVOR logic  for based on enemy hp  115 if below or equal 25% max hp, 100 if 50%
                case EFFECT_ENDEAVOR:
                    if (gBattleMons[count].hp <= (gBattleMons[count].maxHP / 4))
                        data[count].power = 110;
                    else if (gBattleMons[count].hp <= (gBattleMons[count].maxHP / 2))
                        data[count].power = 100;
                default:
                    if (gBattleMoves[data[count].moveId].power == 1)
                        data[count].power = 80;
                    else
                        data[count].power = gBattleMoves[data[count].moveId].power; //default to actual move power, final thing need setup type check, to alter power
                    break;
                }
                count++;    //check next battler 
            }
        }
    }

    for (bestId = 0, i = 1; i < count; i++)
    {
        if (data[i].power > data[bestId].power) //think bestId is just taking firstmove slot, into account, while i, reads the power of every move
            bestId = i;
        else if (data[i].power == data[bestId].power && Random() & 1)// flip 50% to decide on the move
            bestId = i;
    }

    gBattlerTarget = data[bestId].battlerId;    //sets target based on which battler has most dangerous move.
    gForewarnedBattler = data[bestId].battlerId;    //
    PREPARE_MOVE_BUFFER(gBattleTextBuff1, data[bestId].moveId)
        //RecordKnownMove(gBattlerTarget, data[bestId].moveId);   //I think this may just be for ai?

    gSpecialStatuses[battler].forewarnedMove = data[bestId].moveId; //this way can transfer the move perfectly without worrying about random shift from recalling function

    free(data);
}



enum
{
    CASTFORM_NO_CHANGE,
    CASTFORM_TO_NORMAL,
    CASTFORM_TO_FIRE,
    CASTFORM_TO_WATER,
    CASTFORM_TO_ICE,
};

enum
{
    CHERRIM_NO_CHANGE,
    CHERRIM_OVERCAST,
    CHEERRIM_SUNSHINE,
};

u8 CastformDataTypeChange(u8 battler)
{
    u8 formChange = 0;
    if (gBattleMons[battler].species == SPECIES_CASTFORM)
    {
        if (gBattleMons[battler].ability != ABILITY_FORECAST || gBattleMons[battler].hp == 0)
            return CASTFORM_NO_CHANGE;
        if (!WEATHER_HAS_EFFECT && gBattleMons[battler].type2 != TYPE_GHOST)
        {
            SET_BATTLER_TYPE2(battler, TYPE_GHOST);
            return CASTFORM_TO_NORMAL;
        }
        if (!WEATHER_HAS_EFFECT)
            return CASTFORM_NO_CHANGE;
        if (!(gBattleWeather & (WEATHER_RAIN_ANY | WEATHER_SUN_ANY | WEATHER_HAIL_ANY)) && gBattleMons[battler].type2 != TYPE_GHOST)
        {
            SET_BATTLER_TYPE2(battler, TYPE_GHOST);
            formChange = CASTFORM_TO_NORMAL; //if Im' able to setup can put ground version for sandstorm here
        }
        if (gBattleWeather & WEATHER_SUN_ANY && gBattleMons[battler].type2 != TYPE_FIRE)
        {
            SET_BATTLER_TYPE2(battler, TYPE_FIRE);
            formChange = CASTFORM_TO_FIRE;
        }
        if (gBattleWeather & WEATHER_RAIN_ANY && gBattleMons[battler].type2 != TYPE_WATER)
        {
            SET_BATTLER_TYPE2(battler, TYPE_WATER);
            formChange = CASTFORM_TO_WATER;
        }
        if (gBattleWeather & WEATHER_HAIL_ANY && gBattleMons[battler].type2 != TYPE_ICE)
        {
            SET_BATTLER_TYPE2(battler, TYPE_ICE);
            formChange = CASTFORM_TO_ICE;
        }
    } //just realied how weird it is that castform is using type setting functions rather than actually transforming to other species, when each form is defined...

    else if (gBattleMons[battler].species == SPECIES_CHERRIM)
    {
        if (gBattleMons[battler].ability != ABILITY_FLOWER_GIFT || gBattleMons[battler].hp == 0)
            formChange = CHERRIM_NO_CHANGE;
        else if (gBattleMonForms[battler] == 0 && WEATHER_HAS_EFFECT && gBattleWeather & WEATHER_SUN_ANY)
            formChange = CHEERRIM_SUNSHINE;
        else if (gBattleMonForms[battler] != 0 && (!WEATHER_HAS_EFFECT || !(gBattleWeather & WEATHER_SUN_ANY)))
            formChange = CHERRIM_OVERCAST;
    }
    return formChange;

} //check to make sure cherrim form change works

#define PICKUP_FORBIDDEN_END            0xFFFF

static const u16 sForbiddenHoldEffects[] =
{
    HOLD_EFFECT_EXP_SHARE,
    HOLD_EFFECT_PREVENT_EVOLVE,
    HOLD_EFFECT_UP_GRADE,
    HOLD_EFFECT_ADAMANT_ORB,
    HOLD_EFFECT_LUSTROUS_ORB,
    HOLD_EFFECT_GRISEOUS_ORB,
    HOLD_EFFECT_GRACIDEA,
    HOLD_EFFECT_DRIVE,
    HOLD_EFFECT_MEGA_STONE,
    HOLD_EFFECT_PRIMAL_ORB,
    HOLD_EFFECT_MEMORY,
    HOLD_EFFECT_Z_CRYSTAL,
    HOLD_EFFECT_ULTIMA_BRACE, //remove this effect I think
    PICKUP_FORBIDDEN_END
}; //think add on to this from hold_effects.h to further tailor what I want effect to be

#define ABILITYBATTLE_FUNCTION

//order only matters as which activates first.
//based on battle_main, function  loops through every battler
//from fastest to slowest, checking for abilities in the order they appear here.
//so for example  even if drought is after drizzle, if the drought mon was faster, drizzle would come after
u8 AbilityBattleEffects(u8 caseID, u8 battler, u16 ability, u8 special, u16 moveArg) //still to update
{
    u8 effect = 0;
    struct Pokemon *pokeAtk;
    struct Pokemon *pokeDef;
    u16 speciesAtk;
    u16 speciesDef;
    u32 pidAtk;
    u32 pidDef;
    u16 value;

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
        u8 moveType, move;
        s32 i, j;
        u8 side;
        u8 target1;

        //Pickup variables needed put above switch start
        u16 PickUpItem, heldItem;

        u16 *changedItem = &gBattleStruct->changedItems[battler];
        if (special)
            gLastUsedAbility = special;
        else
            gLastUsedAbility = GetBattlerAbility(battler); //this is what was needed for neutralizing gas to work
        if (!moveArg)
            moveArg = gCurrentMove;
        GET_MOVE_TYPE(moveArg, moveType);
        if (IS_BATTLE_TYPE_GHOST_WITHOUT_SCOPE(gBattleTypeFlags)
            && (gLastUsedAbility == ABILITY_INTIMIDATE || gLastUsedAbility == ABILITY_TRACE || gLastUsedAbility == ABILITY_TIGER_MOM))
            return effect;//added copy abiliety just incase
        switch (caseID)
        {
        case ABILITYEFFECT_ON_SWITCHIN: // 0
            if (gBattlerAttacker >= gBattlersCount)// this line makes it switch in I think?
                gBattlerAttacker = battler;
            switch (gLastUsedAbility) //guessing but I think...that each abiltiy switch case is based off the ability getting logged in glastusedability 
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
                break;//found logic that says order does matter it starst w FF to wrap around to 0 and thene count up. so put teerrain here
            case ABILITYEFFECT_SWITCH_IN_TERRAIN:   //set battle terrain from map conditions/before battle
                if (VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY)
                {
                    u16 terrainFlags = VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY;    // only works for status flag (1 << 15)
                    gFieldStatuses = terrainFlags | STATUS_FIELD_TERRAIN_PERMANENT; // terrain is permanent
                    switch (VarGet(VAR_TERRAIN) & STATUS_FIELD_TERRAIN_ANY)
                    {
                    case STATUS_FIELD_ELECTRIC_TERRAIN: //set terrain for power plants
                        gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                        break;
                    case STATUS_FIELD_MISTY_TERRAIN:    //could set with fog, need to add fog weather, plan set certain time of day, near water
                        gBattleCommunication[MULTISTRING_CHOOSER] = 0;
                        break;
                    case STATUS_FIELD_GRASSY_TERRAIN:
                        gBattleCommunication[MULTISTRING_CHOOSER] = 1;
                        break;
                    case STATUS_FIELD_PSYCHIC_TERRAIN:
                        gBattleCommunication[MULTISTRING_CHOOSER] = 3;
                        break;
                    }//for terrain auto set from world I think I don't want to have a text string letting ppl know
                    //instead it'll be something for the player to keep in mind, I'll have it explained at a
                    //trainer school or something

                    BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                    ++effect;
                }
#if B_THUNDERSTORM_TERRAIN == TRUE
                else if (GetCurrentWeather() == WEATHER_RAIN_THUNDERSTORM && !(gFieldStatuses & STATUS_FIELD_ELECTRIC_TERRAIN))
                {//my note- plan to add in unused weather and emerald weather for realism
                    //integrate emeraald tv effect to track weather
                    // overworld weather started rain, so just do electric terrain anim
                    gFieldStatuses = (STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_TERRAIN_PERMANENT);
                    gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                    BattleScriptPushCursorAndCallback(BattleScript_OverworldTerrain);
                    ++effect;
                }
#endif
                break;//hopefully can put terrain here without problems, start of weather abilities
            case ABILITY_DRIZZLE:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN, TRUE))
                {
                    //gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_SQUALL:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN, TRUE))
                {
                    //gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                    gBattleScripting.battler = battler;
                    gBattleStruct->weathersetBy[battler] = battler;
                    ++effect;
                }
                break;
            case ABILITY_SAND_STREAM:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
                {
                    //gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);
                    gBattleScripting.battler = battler;
                    gBattleStruct->weathersetBy[battler] = battler;
                    ++effect;
                }
                break;
            case ABILITY_DROUGHT:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN, TRUE))
                {
                    //gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_SUN_DISK:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN, TRUE))
                {
                    //gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                    gBattleScripting.battler = battler;
                    gBattleStruct->weathersetBy[battler] = battler;
                    ++effect;
                }
                break;
            case ABILITY_SNOW_WARNING:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_HAIL, TRUE))
                {
                    //gBattleWeather = WEATHER_HAIL_ANY;
                    BattleScriptPushCursorAndCallback(BattleScript_SnowWarningActivates);
                    gBattleScripting.battler = battler;
                    gBattleStruct->weathersetBy[battler] = battler;
                    ++effect;
                }
                break;
            case ABILITY_DESOLATE_LAND:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_SUN_PRIMAL, TRUE))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_DesolateLandActivates);
                    ++effect;
                }
                break;//makes sense for groudon/kyogre abilities to set terrain will have terrain use 1.3 boost
                //will also need to make one for fire since water has one...
                //actually water doesn't havee terrain. huh
                //think will also make fire terrain move for heatran, immunity to fire like flash fire
                //vsonic
            case ABILITY_PRIMORDIAL_SEA:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_RAIN_PRIMAL, TRUE))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_PrimordialSeaActivates);
                    ++effect;
                }
                break;
            case ABILITY_DELTA_STREAM:
                if (TryChangeBattleWeather(battler, ENUM_WEATHER_STRONG_WINDS, TRUE))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_DeltaStreamActivates);
                    ++effect;
                }
                break;
            case ABILITY_FORECAST: //think I figured out the switch problem, this case works on switch in,
                //while the other is after all turns are done, by switching castform in mid battle.
                //I think I create a situation where both cases are true and both try to activate.

                //plan setup weather to check if first turn, else if all battlers have completed actions. ok is working on start now.
                effect = CastformDataTypeChange(battler);// I think if I copy the function values to an else if using random chance to activate & turn ended it should work how I want
                if (effect)//i,e if (gCurrentTurnActionNumber >= gBattlersCount) && (gBattleMons[battler].hp != 0)  do value and random as before but a higher number and include
                {// value for setting weather timers to 0, prob should use if for each weather type, and link it with its respective timer.
                    BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                    gBattleScripting.battler = battler;
                    *(&gBattleStruct->formToChangeInto) = effect - 1;// sandstorm effect is continuing oddly, before I change "while" I'm trying line up
                    // the dotted linebetween brackets,  I'm assuming for some reason misalignemnt broke it 
                }// before I had 4 separate random functions, so If I used while it could have been because they were returning multiple values at once.

                //maybe problem was the condition was always true?

                if (!(gBattleTypeFlags & (BATTLE_TYPE_OLD_MAN_TUTORIAL))) // don't want to change weather every turn but I do want it to change, mid battle, and trigger after all battlers have had their turns. think that's turn action count > battlers count.
                { //I want it to trigger once at start of battle I think, but maybe not. Some people could make use of "normal" form castform. i guess
                   // u16 value;// trying to store the value returned by random function in one field as per phoenixbound's suggestion. since it seemed I was calling 5 separate random functions
                    value = Random() % 4; //and having random() in the if function was causing the effect to only work if true, which means a non 0 value, so a 3/4 chance.
                    if (value == 0
                        && (!(gBattleWeather & WEATHER_ANY))) {
                        gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                        BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates);
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    if (value == 1
                        && (!(gBattleWeather & WEATHER_ANY))) {
                        gBattleWeather = (WEATHER_SANDSTORM_PERMANENT | WEATHER_SANDSTORM_TEMPORARY);
                        BattleScriptPushCursorAndCallback(BattleScript_SandstreamActivates);
                        gBattleScripting.battler = battler;
                        ++effect;

                    }
                    if (value == 2
                        && (!(gBattleWeather & WEATHER_ANY))) {
                        gBattleWeather = (WEATHER_SUN_PERMANENT | WEATHER_SUN_TEMPORARY);
                        BattleScriptPushCursorAndCallback(BattleScript_DroughtActivates);
                        gBattleScripting.battler = battler;
                        ++effect;
                    }
                    if (value == 3
                        && (!(gBattleWeather & WEATHER_ANY))) {
                        gBattleWeather = WEATHER_HAIL;
                        BattleScriptPushCursorAndCallback(BattleScript_HailActivates);
                        gBattleScripting.battler = battler;// made battlescript change, got it working now.
                        ++effect;

                    } //since this one is only meant to trigger on switch in,
                    //I've set it to fail if any weather condition is already present.
                    //that will at least prevent the looping...I hope
                }
                break;
            case ABILITY_FLOWER_GIFT:
                effect = CastformDataTypeChange(battler);// I think if I copy the function values to an else if using random chance to activate & turn ended it should work how I want
                if (effect)//i,e if (gCurrentTurnActionNumber >= gBattlersCount) && (gBattleMons[battler].hp != 0)  do value and random as before but a higher number and include
                {// value for setting weather timers to 0, prob should use if for each weather type, and link it with its respective timer.
                    BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                    gBattleScripting.battler = battler;
                    *(&gBattleStruct->formToChangeInto) = effect - 1;// sandstorm effect is continuing oddly, before I change "while" I'm trying line up
                    // the dotted linebetween brackets,  I'm assuming for some reason misalignemnt broke it 
                }
                break;
            case ABILITY_CLOUD_NINE:
            case ABILITY_AIR_LOCK:
            {
                for (target1 = 0; target1 < gBattlersCount; ++target1)
                {
                    effect = CastformDataTypeChange(target1);
                    if (effect)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                        gBattleScripting.battler = target1;
                        *(&gBattleStruct->formToChangeInto) = effect - 1;
                        break;
                    }
                }
            }
            break; //end of weather related abilities / start of terrain abilities
            case ABILITY_ELECTRIC_SURGE: //put here to occur after weather abilities
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_ELECTRIC_TERRAIN, &gFieldTimers.terrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_ElectricSurgeActivates);
                    ++effect;
                }
                break;
            case ABILITY_GRASSY_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_GRASSY_TERRAIN, &gFieldTimers.terrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_GrassySurgeActivates);
                    ++effect;
                }
                break;
            case ABILITY_MISTY_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_MISTY_TERRAIN, &gFieldTimers.terrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_MistySurgeActivates);
                    ++effect;
                }
                break;
            case ABILITY_PSYCHIC_SURGE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_PSYCHIC_TERRAIN, &gFieldTimers.terrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_PsychicSurgeActivates);
                    ++effect;
                }
                break;
            case ABILITY_LAVA_FISSURE:
                if (TryChangeBattleTerrain(battler, STATUS_FIELD_SCORCHED_TERRAIN, &gFieldTimers.terrainTimer))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_LavaDistortionActivates);
                    ++effect;
                }
                break;
                //C |= 2 is same as C = C | 2
                // from GriffinR  But yes it's setting a specific status for that battler.
                // But pokemon can have many of these statuses at once, so you want to set those bits in addition to what's already there
                //writing gStatuses3[battler] = STATUS3_INTIMIDATE_POKES; would clear all status which isn't what I want

            case ABILITY_INTIMIDATE:    // moved down here, so weather effects acitvate before these
                if (!(gSpecialStatuses[battler].intimidatedMon)) //if intimidated mon is 0 set intimidate pokes i.e if noto already intimidated
                { //further having this on a switch case ensures it only works for mon with the ability
                    gBattlerAttacker = battler; //for mirror armor & empath battler that sets intimidate
                    gStatuses3[battler] |= STATUS3_INTIMIDATE_POKES;
                    gSpecialStatuses[battler].intimidatedMon = TRUE;           //not changing intimidateMon to 1 causes intimidate case to /the switchin case to loop
                }//special status intimidated mon is set on mon with intimidate, it then applies status3 intimidate pokes to activate intimidate
                //and changes intimdiatedmon to 1 so it can't reactivate/loop
                // but intimidatedMon is reset by faintmon battlescript as well as the SpecialStatusClear function from battle_main.c
                //that is called seemingly each turn and at battle start?  need to figure how this doesn't cause a loop issue.
                //if intimidated mon is reset to 0 each turn  //doesn't loop because intimidate battle script is only called at battle start and switch in
                break; //to reactivate just needs to call battlescript again based on condition
            case ABILITY_TRACE:
                if (!(gSpecialStatuses[battler].traced)) //this is needed to prevent infini loop because its not a "status"
                {
                    gStatuses3[battler] |= STATUS3_TRACE;
                    gSpecialStatuses[battler].traced = TRUE;
                }
                break;
            case ABILITY_TIGER_MOM: //TEST
                if (!(gSpecialStatuses[battler].tigerMomAttacked)) //ok I see what emerald did now, this is same as gSpecialStatuses[battler].switchInAbilityDone, just unique name
                {
                    gStatuses3[battler] |= STATUS3_TIGER_MOM_ATTACKS;
                    gSpecialStatuses[battler].tigerMomAttacked = TRUE;
                }
                break;
            case ABILITY_CUPIDS_ARROW: // 
                for (i = 0; i < gBattlersCount; ++i) //handles ability targetting  /think should also stop reactivate? need test
                {
                    u16 speciesAttacker, speciesTarget1, speciesTarget2;
                    u32 personalityAttacker, personalityTarget1, personalityTarget2;

                    if (gBattleMons[i].ability == ABILITY_CUPIDS_ARROW)// && (Random() % 1) == 0) //hopefully 50% odds,
                        //using high odds since it can only activate on switch in, and if opposite gender is on other side
                    {//changed to 100% oddds since its weak mon, intend to turn luvdisc into setup/stall mon
                        u8 target2;

                        side = (GetBattlerPosition(i) ^ BIT_SIDE) & BIT_SIDE; // side of the opposing pokemon
                        target1 = GetBattlerAtPosition(side);
                        target2 = GetBattlerAtPosition(side + BIT_FLANK);

                        speciesAttacker = GetMonData(i, MON_DATA_SPECIES);
                        personalityAttacker = GetMonData(i, MON_DATA_PERSONALITY);
                        speciesTarget1 = GetMonData(target1, MON_DATA_SPECIES);
                        speciesTarget2 = GetMonData(target2, MON_DATA_SPECIES);
                        personalityTarget1 = GetMonData(target1, MON_DATA_PERSONALITY);
                        personalityTarget2 = GetMonData(target2, MON_DATA_PERSONALITY);

                        if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                        {
                            //end function if all genders are the same  //removed gender check
                            /*if (GetGenderFromSpeciesAndPersonality(speciesAttacker, personalityAttacker) == (GetGenderFromSpeciesAndPersonality(speciesTarget1, personalityTarget1) && GetGenderFromSpeciesAndPersonality(speciesTarget2, personalityTarget2)))
                            {
                                break;
                            }*/
                            if (gBattleMons[target1].ability != 0 && gBattleMons[target1].hp != 0
                                && (GetGenderFromSpeciesAndPersonality(speciesTarget1, personalityTarget1) != MON_GENDERLESS)
                                && gBattleMons[target2].ability != 0 && gBattleMons[target2].hp != 0
                                && (GetGenderFromSpeciesAndPersonality(speciesTarget2, personalityTarget2) != MON_GENDERLESS))
                            {
                                gBattlerTarget = GetBattlerAtPosition(((Random() & 1) * 2) | side); //select on target from enemy 
                                gBattleScripting.battler = i;
                                gLastUsedAbility = gBattleMons[i].ability;
                                infatuationchecks();
                                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                                    BattleScriptPushCursorAndCallback(BattleScript_CupidsArrowActivates);
                                ++effect;
                            }
                            else if (gBattleMons[target1].ability != 0 && gBattleMons[target1].hp != 0
                                && (GetGenderFromSpeciesAndPersonality(speciesTarget1, personalityTarget1) != MON_GENDERLESS))
                            {
                                gBattlerTarget = target1;
                                gBattleScripting.battler = i;
                                gLastUsedAbility = gBattleMons[i].ability;
                                infatuationchecks();
                                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                                    BattleScriptPushCursorAndCallback(BattleScript_CupidsArrowActivates);
                                ++effect;
                            }
                            else if (gBattleMons[target2].ability != 0 && gBattleMons[target2].hp != 0
                                && (GetGenderFromSpeciesAndPersonality(speciesTarget2, personalityTarget2) != MON_GENDERLESS))
                            {
                                gBattlerTarget = target2;
                                gBattleScripting.battler = i;
                                gLastUsedAbility = gBattleMons[i].ability;
                                infatuationchecks();
                                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                                    BattleScriptPushCursorAndCallback(BattleScript_CupidsArrowActivates);
                                ++effect;
                            }
                        }
                        else //single target
                        {

                            if (gBattleMons[target1].ability && gBattleMons[target1].hp
                                && (GetGenderFromSpeciesAndPersonality(speciesTarget1, personalityTarget1) != MON_GENDERLESS))
                            {
                                gBattlerTarget = target1;
                                gBattleScripting.battler = i;
                                gLastUsedAbility = gBattleMons[i].ability;
                                infatuationchecks();
                                PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff1, gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                                    BattleScriptPushCursorAndCallback(BattleScript_CupidsArrowActivates);
                                ++effect;
                            }
                        }

                    }
                }//now in the right place to actually activate on switch in
                break;
            case ABILITY_IMPOSTER:
                if (IsBattlerAlive(BATTLE_OPPOSITE(battler))
                    && !(gBattleMons[BATTLE_OPPOSITE(battler)].status2 & (STATUS2_TRANSFORMED | STATUS2_SUBSTITUTE))
                    && !(gBattleMons[battler].status2 & STATUS2_TRANSFORMED)
                    && !(gBattleStruct->illusion[BATTLE_OPPOSITE(battler)].on)
                    && !(gStatuses3[BATTLE_OPPOSITE(battler)] & STATUS3_SEMI_INVULNERABLE))
                {
                    gBattlerAttacker = battler;
                    gBattlerTarget = BATTLE_OPPOSITE(battler);
                    BattleScriptPushCursorAndCallback(BattleScript_ImposterActivates); //uses transform bs command
                    ++effect;
                }
                break;
            case ABILITY_MOLD_BREAKER:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_MOLDBREAKER;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_TERAVOLT:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TERAVOLT;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_TURBOBLAZE:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_TURBOBLAZE;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_SLOW_START:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    if (!(gBattleStruct->slowstartDone[battler])) //set in end turn when timer ends, not reset on faint
                    {
                        gDisableStructs[battler].slowStartTimer = 3;    //keeping at 2, so won't be able to just freely setup on this mon
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SLOWSTART;   // nvm boosted dmg reduction, keep timer
                        gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                        BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                        ++effect;
                    }
                }
                break;
                /*case ABILITY_UNNERVE: //this isn't fully setup, but effect shuold be enemy side can't eat berries if my ability is intake
                    if (!gSpecialStatuses[battler].switchInAbilityDone)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_UNNERVE;
                        gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                        BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                        ++effect;
                    }
                    break;
                case ABILITY_AS_ONE_ICE_RIDER:
                case ABILITY_AS_ONE_SHADOW_RIDER:
                    if (!gSpecialStatuses[battler].switchInAbilityDone)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_ASONE;
                        gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                        BattleScriptPushCursorAndCallback(BattleScript_ActivateAsOne);
                        ++effect;
                    }
                    break;*/
            case ABILITY_CURIOUS_MEDICINE:
                if (!gSpecialStatuses[battler].switchInAbilityDone && IsDoubleBattle()
                    && IsBattlerAlive(BATTLE_PARTNER(battler)) && TryResetBattlerStatChanges(BATTLE_PARTNER(battler)))
                {
                    //u32 i;  unneeded?
                    gEffectBattler = BATTLE_PARTNER(battler);
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_CURIOUS_MEDICINE;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_CORRUPTION:
                if (!gSpecialStatuses[battler].switchInAbilityDone && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                {
                    //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK; // apply status to target and set side status   //don't think i need this
                    gSideStatuses[GET_BATTLER_SIDE(battler)] |= SIDE_STATUS_HEAL_BLOCK;
                    gSideTimers[GET_BATTLER_SIDE(battler)].healBlockTimer = 5;  //would want to make permanent but 5 turns is enough to last for the mon's life
                    gSideTimers[GET_BATTLER_SIDE(battler)].healBlockBattlerId = battler;

                    //gStatuses3[gBattlerTarget] |= STATUS3_HEAL_BLOCK;
                    //gDisableStructs[gBattlerTarget].healBlockTimer = 5;
                    gBattlerTarget = battler;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_CORRUPTION;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    ++effect;
                }
                else if (!gSpecialStatuses[battler].switchInAbilityDone && gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK)
                {
                    gSideTimers[GET_BATTLER_SIDE(battler)].healBlockTimer += 5; //adds on to existing timer on switchin
                    gBattlerTarget = battler;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_CORRUPTION;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    ++effect;
                }
                break;
            case ABILITY_BANDIT_KING:
                if (!gSpecialStatuses[battler].switchInAbilityDone && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_EMBARGO))
                {

                    gSideStatuses[GET_BATTLER_SIDE(battler)] |= SIDE_STATUS_EMBARGO;
                    gSideTimers[GET_BATTLER_SIDE(battler)].embargoTimer = 5;  //hope works, need test
                    gSideTimers[GET_BATTLER_SIDE(battler)].embargoBattlerId = battler;


                    gBattlerTarget = battler;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_BANDIT;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    ++effect;
                }
                else if (!gSpecialStatuses[battler].switchInAbilityDone && gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_EMBARGO)
                {
                    gSideTimers[GET_BATTLER_SIDE(battler)].embargoTimer += 5; //adds on to existing timer on switchin
                    gBattlerTarget = battler;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_BANDIT;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    ++effect;
                }
                break;
            case ABILITY_FLUORESCENCE:
                if (!gSpecialStatuses[battler].switchInAbilityDone && IsBlackFogNotOnField())
                {


                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FLUORESCENT;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    ++effect;
                    
                }
                
                break;
            case ABILITY_PASTEL_VEIL:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattlerTarget = battler;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_PASTEL_VEIL;
                    //BattleScriptPushCursorAndCallback(BattleScript_PastelVeilActivates);
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                }
                break;
                /*case ABILITY_COMATOSE:  //may remove, check how works and see if sleep status gets applied w icon vsonic
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_COMATOSE;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }it'll list ability name at endd turn when it heals
                break;*/
            case ABILITY_STENCH:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_STENCH;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
            case ABILITY_SCREEN_CLEANER:
                if (!gSpecialStatuses[battler].switchInAbilityDone && TryRemoveScreens(battler))
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_SCREENCLEANER;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_FRISK:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_FriskActivates); // Try activate
                    ++effect;
                }
                return effect; // Note: It returns effect as to not record the ability if Frisk does not activate.
            case ABILITY_FOREWARN:
                if (!gSpecialStatuses[battler].switchInAbilityDone)//will have to make cases for these 2, in same place as effect spore, decids a move on switchin,
                {                                                   //nulls the move if hit by it, or can put in atk canceller, check target switchInAbilityDone, and if currentmove matches ability prediction
                    ForewarnChooseMove(battler);    //for switchin battler is gBattlerAttacker
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FOREWARN;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_ANTICIPATION:  //working on change
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    u32 side = GetBattlerSide(battler);

                    for (i = 0; i < MAX_BATTLERS_COUNT; i++)    //side is me, i is oppononent/target
                    {
                        if (IsBattlerAlive(i) && side != GetBattlerSide(i))//effect is not accurate, anticipation checked for ohko effects and explosion/selfdestruct in gen4
                        {
                            for (j = 0; j < MAX_MON_MOVES; j++)
                            {
                                move = gBattleMons[i].moves[j];
                                GET_MOVE_TYPE(move, moveType);
                                if (gBattleMoves[move].effect == EFFECT_EXPLOSION //setup multiplier calc think can just use multipier check here.
                                    && CalcTypeEffectivenessMultiplier(move, moveType, i, battler, FALSE) != UQ_4_12(0.0))
                                {
                                    
                                    PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ANTICIPATE_EXPLOSION);
                                    ++effect;                                    
                                    break;
                                    //    want setup different message for each, nickname w prefix sensed an X move and shuddered
                                      //depending on value  or have different value copied to gBattleTextBuff1 for each
                                }
                                else if (gBattleMoves[move].effect == EFFECT_OHKO && (gBattleMons[i].level >= (gBattleMons[battler].level - 7))
                                && CalcTypeEffectivenessMultiplier(move, moveType, i, battler, FALSE) != UQ_4_12(0.0))
                                {
                                    PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ANTICIPATE_OHKO);
                                    ++effect;//
                                    break;
                                }
                                else if (CalcTypeEffectivenessMultiplier(move, moveType, i, battler, FALSE) >= UQ_4_12(1.55))//vsonic  //THINK CAN use typecalc fort this?
                                {
                                    PREPARE_STRING_BUFFER(gBattleTextBuff1, STRINGID_ANTICIPATE_DEFAULT);
                                    ++effect;//
                                    break;
                                }//if find super effectivemove, increment effect and break for loop, to lock in move/
                            }//can only return one value, so will need to do an if else based on priority
                        }
                    }

                    if (effect)//if ability activates  i.e effect not 0
                    {
                        gSpecialStatuses[battler].anticipatedMove = move;
                        gAnticipatedBattler = i; //hopeworks.
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_ANTICIPATION;
                        gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                        BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    }
                }
                break;
            case ABILITY_DOWNLOAD:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    u32 statId, opposingBattler;
                    u32 opposingDef = 0, opposingSpDef = 0;

                    opposingBattler = BATTLE_OPPOSITE(battler);
                    for (i = 0; i < 2; opposingBattler ^= BIT_FLANK, i++)
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

                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;

                    if (CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
                    {
                        gBattleMons[battler].statStages[statId]++;
                        SET_STATCHANGER(statId, 1, FALSE);
                        gBattlerAttacker = battler;
                        PREPARE_STAT_BUFFER(gBattleTextBuff1, statId);
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerAbilityStatRaiseEnd3);
                        ++effect;
                    }
                }
                break;
            case ABILITY_DARK_AURA:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_DARKAURA;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;
            case ABILITY_FAIRY_AURA:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_FAIRYAURA;
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }
                break;//change logic so only actiavte if other aura skill is on other side
            case ABILITY_AURA_BREAK:
                if (IsAbilityOnField(ABILITY_DARK_AURA) || IsAbilityOnField(ABILITY_FAIRY_AURA))
                {
                    if (!gSpecialStatuses[battler].switchInAbilityDone)
                    {
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_AURABREAK;
                        gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                        BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                        ++effect; 
                    }
                }
                break;
            case ABILITY_SCHOOLING:
                if (gBattleMons[battler].level < 20)//fall through if above lvl, so would do form change.
                    break;
            case ABILITY_ZEN_MODE:  //putting here would let zenmode trigger at battle start
            case ABILITY_SHIELDS_DOWN:
                if (ShouldChangeFormHpBased(battler))
                {
                    BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                    ++effect;
                }
                break;
            case ABILITY_INTREPID_SWORD:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    SET_STATCHANGER(STAT_ATK, 1, FALSE);
                    BattleScriptPushCursorAndCallback(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                    ++effect;
                }
                break;
            case ABILITY_DAUNTLESS_SHIELD:
                if (!gSpecialStatuses[battler].switchInAbilityDone)
                {
                    gSpecialStatuses[battler].switchInAbilityDone = TRUE;
                    SET_STATCHANGER(STAT_DEF, 1, FALSE);
                    BattleScriptPushCursorAndCallback(BattleScript_BattlerAbilityStatRaiseOnSwitchIn);
                    ++effect;
                }
                break;
            case ABILITY_MIMICRY:
                if (gBattleMons[battler].hp != 0 && gFieldStatuses & STATUS_FIELD_TERRAIN_ANY)
                {
                    TryToApplyMimicry(battler, FALSE);
                    ++effect;
                }
                break;
            case ABILITY_PURIFYING_AURA:
                if (gBattleMons[battler].status2 != STATUS2_CONFUSION)  //switch in ver.
                {
                    if (gBattleMons[battler].status1 & STATUS1_ANY)
                    {

                        gBattleMons[battler].status1 = 0;
                        gBattleMons[battler].status2 &= ~(STATUS2_NIGHTMARE);  // fix nightmare glitch
                        gBattleScripting.battler = gActiveBattler = battler;
                        BattleScriptPushCursorAndCallback(BattleScript_PurifyingAuraActivates);
                        BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                        MarkBattlerForControllerExec(gActiveBattler);
                        ++effect;
                    }
                    if (IsBattlerAlive(BATTLE_PARTNER(battler))) {
                        if (gBattleMons[BATTLE_PARTNER(battler)].status1 & STATUS1_ANY)    //PARTNER status clear
                        {

                            gBattleMons[BATTLE_PARTNER(battler)].status1 = 0;
                            gBattleMons[BATTLE_PARTNER(battler)].status2 &= ~(STATUS2_NIGHTMARE);  // fix nightmare glitch
                            gBattleScripting.battler = gActiveBattler = BATTLE_PARTNER(battler);
                            BattleScriptPushCursorAndCallback(BattleScript_PurifyingAuraActivatesForPartner);
                            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                            MarkBattlerForControllerExec(gActiveBattler);
                            ++effect;
                        }
                    }
                }
                break;
            case ABILITY_DEFEATIST:
                if (gBattleMons[battler].hp < (gBattleMons[battler].maxHP / 2))
                {
                    u16 speed = gBattleMons[battler].speed;
                    if (gSpecialStatuses[battler].defeatistActivated != 1) //done so doesn't  reactivate while on field if heal and hp falls again
                    {

                        if (gBattleMons[battler].statStages[STAT_ATK] > 0)
                        {
                            gBattleMons[battler].statStages[STAT_ATK] -= 2;    //should lower stat by 2 i.e 50% 
                            if (gBattleMons[battler].statStages[STAT_ATK] < 0)
                                gBattleMons[battler].statStages[STAT_ATK] = 0;
                            gBattleScripting.animArg1 = 0x11;
                            gBattleScripting.animArg2 = 0;
                            gBattleScripting.battler = battler;
                        }
                        if (gBattleMons[battler].statStages[STAT_SPATK] > 0)
                        {
                            gBattleMons[battler].statStages[STAT_SPATK] -= 2;    //should lower stat by 2 i.e 50% 
                            if (gBattleMons[battler].statStages[STAT_SPATK] < 0)
                                gBattleMons[battler].statStages[STAT_SPATK] = 0;
                            gBattleScripting.animArg1 = 0x11;
                            gBattleScripting.animArg2 = 0;
                            gBattleScripting.battler = battler;
                        }
                        speed *= 2; //should double effective speed without changing stat

                        BattleScriptPushCursorAndCallback(BattleScript_DefeatistActivates);
                        gBattleScripting.battler = battler; //something new for defeatist activation
                        //buff lost the will to fight, and is ready to run!


                        gSpecialStatuses[battler].defeatistActivated = 1;
                        ++effect;
                    }
                }
                break;
            case ABILITY_EROSION:
                if (gSideStatuses[battler] & SIDE_STATUS_STEALTH_ROCK)
                {
                    gSideStatuses[battler] &= ~(SIDE_STATUS_STEALTH_ROCK);  //absorb stealth rock
                    gSideTimers[battler].stealthRockAmount = 0;
                    if (!(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))    //health block check
                    {
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;

                        if (gBattleMons[battler].hp > gBattleMons[battler].maxHP)
                            gBattleMons[battler].hp = gBattleMons[battler].maxHP;
                    }

                    BattleScriptPushCursorAndCallback(BattleScript_StealthRockAbsorb);
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_ECOSYSTEM:
                SET_BATTLER_TYPE3(battler, TYPE_WATER); //essentially makes it a 3 type mon,
                ++effect;
                break;

            }
            break;  //end of switch-in abilities   switch in
        case ABILITYEFFECT_ENDTURN: // 1
            if (gBattleMons[battler].hp != 0)
            {
                gBattlerAttacker = battler;
                switch (gLastUsedAbility)
                {
                case ABILITY_RAIN_DISH:
                    if (IsBattlerWeatherAffected(battler, WEATHER_RAIN_ANY)
                        && gBattleMons[battler].maxHP > gBattleMons[battler].hp
                        && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        //gLastUsedAbility = ABILITY_RAIN_DISH; // why -_-  ?chcked emerald, and was correct this is unnecessary
                        BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 12;    //could buff?  did buff wass 16
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    break;
                case ABILITY_PHOTOSYNTHESIZE:
                    if (IsBattlerWeatherAffected(battler, WEATHER_SUN_ANY)
                        && gBattleMons[battler].maxHP > gBattleMons[battler].hp
                        && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        //gLastUsedAbility = ABILITY_PHOTOSYNTHESIZE; 
                        BattleScriptPushCursorAndCallback(BattleScript_AbilityHpHeal);  //can use same script //but have another from updates
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 12; //buffed all weather abilities now heal 1/12
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    break;
                case ABILITY_GLACIAL_ICE:
                case ABILITY_ICE_BODY:
                    if (IsBattlerWeatherAffected(battler, WEATHER_HAIL_ANY) //this function only matters for rain & sun otherwise can use
                        && gBattleMons[battler].maxHP > gBattleMons[battler].hp //weather_has_effect
                        && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        //gLastUsedAbility = ABILITY_ICE_BODY; //without this line can use same block for multiple abilities
                        BattleScriptPushCursorAndCallback(BattleScript_AbilityHpHeal);  //can use same script //but have another from updates
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 12;  //buffed all weather abilities now heal 1/12
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    break;
                case ABILITY_DRY_SKIN:
                    if (IsBattlerWeatherAffected(battler, WEATHER_RAIN_ANY)
                        && gBattleMons[battler].maxHP > gBattleMons[battler].hp
                        && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_RainDishActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    /*else if (IsBattlerWeatherAffected(battler, WEATHER_SUN_ANY))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        ++effect;
                    } */ //removed in sun hp drop unnecessary, they already take extra fire dmg
                    break;
                case ABILITY_COMATOSE:
                    if (gBattleMons[battler].maxHP > gBattleMons[battler].hp
                        && !(gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_AbilityHpHeal);  //can use same script //but have another from updates
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 6; //substitute for not being able to use rest, but that in mind woudl be broken with substitute hmm
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                        ++effect;
                    }
                    break;

                case ABILITY_SHED_SKIN: //don't need to make switch in effect, it activates before status dmg
                    if ((gBattleMons[battler].status1 & STATUS1_ANY) && (Random() % 3) == 0)
                    {
                        if (gBattleMons[battler].status1 & (STATUS1_POISON | STATUS1_TOXIC_POISON))
                            StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn); //no idea why this is here? but its in emerald too
                        if (gBattleMons[battler].status1 & STATUS1_SLEEP) //here because shedskin string uses buff1 to read status on mon
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
                case ABILITY_PURIFYING_AURA:
                    if (gBattleMons[battler].status2 != STATUS2_CONFUSION)  //end turn ver.
                    {
                        if (gBattleMons[battler].status1 & STATUS1_ANY)
                        {

                            gBattleMons[battler].status1 = 0;
                            gBattleMons[battler].status2 &= ~(STATUS2_NIGHTMARE);  // fix nightmare glitch
                            gBattleScripting.battler = gActiveBattler = battler;
                            BattleScriptPushCursorAndCallback(BattleScript_PurifyingAuraActivates);
                            BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battler].status1);
                            MarkBattlerForControllerExec(gActiveBattler);
                            ++effect;
                        }
                        if (IsBattlerAlive(BATTLE_PARTNER(battler))) {
                            if (gBattleMons[BATTLE_PARTNER(battler)].status1 & STATUS1_ANY)    //PARTNER status clear
                            {

                                gBattleMons[BATTLE_PARTNER(battler)].status1 = 0;
                                gBattleMons[BATTLE_PARTNER(battler)].status2 &= ~(STATUS2_NIGHTMARE);  // fix nightmare glitch
                                gBattleScripting.battler = gActiveBattler = BATTLE_PARTNER(battler);
                                BattleScriptPushCursorAndCallback(BattleScript_PurifyingAuraActivatesForPartner);
                                BtlController_EmitSetMonData(0, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                                MarkBattlerForControllerExec(gActiveBattler);
                                ++effect;
                            }
                        }
                    }
                    break;
                case ABILITY_PICKUP:

                    if (gBattleMons[battler].item == ITEM_NONE && (Random() % 3 == 0))
                    {   //item search
                        for (PickUpItem = 0; ItemId_GetHoldEffect(PickUpItem) == HOLD_EFFECT_NONE; heldItem = (Random() % LAST_ITEM_INDEX) + 1)   
                        {   //exclusion checks
                            for (i = 0; sForbiddenHoldEffects[i] != PICKUP_FORBIDDEN_END; ++i)//variable needs to come after increment as its being set to the same variable, otherwise it can't increment
                            {   
                                if (ItemId_GetHoldEffect(heldItem) == sForbiddenHoldEffects[i])
                                    break; //breaks out to above loop to search a new item, as pickupitem is still 0

                            }
                            //item assignment 
                            if (sForbiddenHoldEffects[i] == PICKUP_FORBIDDEN_END)
                                PickUpItem = heldItem;

                        }

                        //gLastUsedItem = *changedItem = PickUpItem; consuimable pickup items not working right possible putting oin glastused too soon is issue
                        *changedItem = PickUpItem; //think that was it, item battle effects function passes item to glastuseditem
                        PREPARE_ITEM_BUFFER(gBattleTextBuff1, PickUpItem)
                            gBattleMons[battler].item = PickUpItem;
                        BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, battler, sizeof(PickUpItem), &PickUpItem);
                        MarkBattlerForControllerExec(battler);
                        BattleScriptExecute(BattleScript_InBattlePickup);
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
                    if (gDisableStructs[battler].isFirstTurn != 2) //doesn't activate on switch in
                    {
                        u32 validToRaise = 0, validToLower = 0;
                        u32 statsNum = NUM_BATTLE_STATS;

                        for (i = STAT_ATK; i < statsNum; i++)
                        {
                            if (CompareStat(battler, i, MIN_STAT_STAGE, CMP_GREATER_THAN))  //if battler's chosen stat to change, is greater than min stage, can lower
                                validToLower |= gBitTable[i];
                            if (CompareStat(battler, i, MAX_STAT_STAGE, CMP_LESS_THAN))
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
                            ++effect;
                        }
                    }
                    break;
                case ABILITY_BAD_DREAMS:
                    if (gBattleMons[battler].status1 & STATUS1_SLEEP
                        || gBattleMons[BATTLE_OPPOSITE(battler)].status1 & STATUS1_SLEEP
                        || GetBattlerAbility(battler) == ABILITY_COMATOSE
                        || GetBattlerAbility(BATTLE_OPPOSITE(battler)) == ABILITY_COMATOSE)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_BadDreamsActivates);
                        ++effect;
                    }
                    break;
                SOLAR_POWER_HP_DROP:
                case ABILITY_SOLAR_POWER:
                    if (IsBattlerWeatherAffected(battler, WEATHER_SUN_ANY))
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_SolarPowerActivates);
                        gBattleMoveDamage = gBattleMons[battler].maxHP / 8;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        ++effect;
                    }
                    break;
                case ABILITY_HEALER:
                    gBattleScripting.battler = BATTLE_PARTNER(battler);
                    if (IsBattlerAlive(gBattleScripting.battler)
                        && gBattleMons[gBattleScripting.battler].status1 & STATUS1_ANY
                        && (Random() % 100) < 30)
                    {
                        BattleScriptPushCursorAndCallback(BattleScript_HealerActivates);
                        ++effect;
                    }
                    break;
                case ABILITY_SCHOOLING:
                    if (gBattleMons[battler].level < 20)
                        break;
                case ABILITY_ZEN_MODE:
                case ABILITY_SHIELDS_DOWN:
                    if ((effect = ShouldChangeFormHpBased(battler)))    //if true do formchange, and set effect to value. 
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3); //so has same effect as incrementing effect
                    break;
                case ABILITY_POWER_CONSTRUCT:
                    if ((gBattleMons[battler].species == SPECIES_ZYGARDE || gBattleMons[battler].species == SPECIES_ZYGARDE_10)
                        && gBattleMons[battler].hp <= gBattleMons[battler].maxHP / 2)
                    {
                        gBattleStruct->changedSpecies[gBattlerPartyIndexes[battler]] = gBattleMons[battler].species;
                        gBattleMons[battler].species = SPECIES_ZYGARDE_COMPLETE;
                        BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3);
                        ++effect;
                    }
                    break;
                case ABILITY_BALL_FETCH:
                    if (gBattleMons[battler].item == ITEM_NONE
                        && gBattleResults.catchAttempts[gLastUsedBall - ITEM_ULTRA_BALL] >= 1
                        && !gHasFetchedBall)
                    {
                        gBattleScripting.battler = battler;
                        BtlController_EmitSetMonData(BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, 2, &gLastUsedBall);
                        MarkBattlerForControllerExec(battler);
                        gHasFetchedBall = TRUE;
                        gLastUsedItem = gLastUsedBall;
                        BattleScriptPushCursorAndCallback(BattleScript_BallFetch);
                        ++effect;
                    }
                    break;
                case ABILITY_HUNGER_SWITCH:
                    if (!(gBattleMons[battler].status2 & STATUS2_TRANSFORMED))
                    {
                        if (gBattleMons[battler].species == SPECIES_MORPEKO)
                        {
                            gBattleMons[battler].species = SPECIES_MORPEKO_HANGRY;
                            BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3NoPopup);
                        }
                        else if (gBattleMons[battler].species == SPECIES_MORPEKO_HANGRY)
                        {
                            gBattleMons[battler].species = SPECIES_MORPEKO;
                            BattleScriptPushCursorAndCallback(BattleScript_AttackerFormChangeEnd3NoPopup);
                        }
                        ++effect;
                    }
                    break;
                case ABILITY_TRUANT:
                    gDisableStructs[gBattlerAttacker].truantCounter ^= 1;
                    break;

                    //can conifirm error was entirely because of switch in, not end turn
                case ABILITY_FORECAST: //plan setup weather to check if first turn, else if all battlers have completed actions. ok is working on start now.
                   /* effect = CastformDataTypeChange(battler);// I think if I copy the function values to an else if using random chance to activate & turn ended it should work how I want
                    if (effect)//i,e if (gCurrentTurnActionNumber >= gBattlersCount) && (gBattleMons[battler].hp != 0)  do value and random as before but a higher number and include
                    {// value for setting weather timers to 0, prob should use if for each weather type, and link it with its respective timer.
                        BattleScriptPushCursorAndCallback(BattleScript_CastformChange);
                        gBattleScripting.battler = battler;
                        *(&gBattleStruct->formToChangeInto) = effect - 1;// sandstorm effect is continuing oddly, before I change "while" I'm trying line up
                    }*/// the dotted linebetween brackets,  I'm assuming for some reason misalignemnt broke it 
                    if (gCurrentTurnActionNumber >= gBattlersCount
                        && Random() % 2 == 0) //actually since the bug happens everytime, its most likely do to the first case and not this one.
                        //since this effect only happens on a chance.

                    { // trying to make it not switch every turn, and find a good balance.
                        u16 value2;// trying to store the value returned by random function in one field as per phoenixbound's suggestion. since it seemed I was calling 5 separate random functions
                        value2 = Random() % 5;
                        if (value2 == 0
                            && gBattleWeather != (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY)) {
                            gBattleWeather = (WEATHER_RAIN_PERMANENT | WEATHER_RAIN_TEMPORARY);
                            BattleScriptPushCursorAndCallback(BattleScript_DrizzleActivates); //potentiall cange to other ones, so not permanent? need double check how weather setup again
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


                            if (gBattleWeather == WEATHER_RAIN_ANY)
                            {
                                gWishFutureKnock.weatherDuration = 0;
                                gBattleCommunication[MULTISTRING_CHOOSER] = 2;
                                BattleScriptPushCursorAndCallback(BattleScript_RainContinuesOrEnds);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_SANDSTORM_ANY) {
                                gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SandStormHailEnds);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_SUN_ANY) {
                                gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SunlightFaded);
                                gBattleScripting.battler = battler;
                                ++effect;
                            }
                            if (gBattleWeather == WEATHER_HAIL_ANY) {
                                gWishFutureKnock.weatherDuration = 0;
                                BattleScriptPushCursorAndCallback(BattleScript_SandStormHailEnds);
                                gBattleScripting.battler = battler;
                                ++effect;

                            }
                            // ++effect;
                        }



                    }
                    break;
                }//end of end turn abilities

            }
            break;
        case ABILITYEFFECT_MOVES_BLOCK: // 2
        {
            u16 moveTarget = GetBattlerMoveTargetType(battler, move);
            u16 battlerAbility = GetBattlerAbility(battler);
            u16 targetAbility = GetBattlerAbility(gBattlerTarget);

            if ((gLastUsedAbility == ABILITY_SOUNDPROOF && gBattleMoves[move].flags & FLAG_SOUND && !(moveTarget & MOVE_TARGET_USER))
                || (gLastUsedAbility == ABILITY_BULLETPROOF && gBattleMoves[move].flags & FLAG_BALLISTIC))
            {
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                    gHitMarker |= HITMARKER_NO_PPDEDUCT;
                gBattlescriptCurrInstr = BattleScript_SoundproofProtected;
                effect = 1;
            }
            else if ((gLastUsedAbility == ABILITY_DAZZLING || gLastUsedAbility == ABILITY_QUEENLY_MAJESTY || IsBattlerAlive(battler ^= BIT_FLANK))
                && (battlerAbility == ABILITY_DAZZLING || battlerAbility == ABILITY_QUEENLY_MAJESTY)
                && GetChosenMovePriority(gBattlerAttacker) > 0
                && GetBattlerSide(gBattlerAttacker) != GetBattlerSide(battler))
            {
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                    gHitMarker |= HITMARKER_NO_PPDEDUCT;
                gBattlescriptCurrInstr = BattleScript_DazzlingProtected;
                effect = 1;
            }
            else if (DoesPranksterBlockMove(move, gBattlerAttacker, gBattlerTarget, TRUE) && !(IS_MOVE_STATUS(move) && targetAbility == ABILITY_MAGIC_BOUNCE))
            {
                if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE) || !(moveTarget & (MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY)))
                    CancelMultiTurnMoves(gBattlerAttacker); // Don't cancel moves that can hit two targets bc one target might not be protected
                gBattleScripting.battler = gBattlerAbility = gBattlerTarget;
                gBattlescriptCurrInstr = BattleScript_DarkTypePreventsPrankster;
                effect = 1;
            }
            else if (gLastUsedAbility == ABILITY_ICE_FACE && IS_MOVE_PHYSICAL(move) && gBattleMons[gBattlerTarget].species == SPECIES_EISCUE)
            {
                gBattleMons[gBattlerTarget].species = SPECIES_EISCUE_NOICE_FACE;
                if (gBattleMons[gBattlerAttacker].status2 & STATUS2_MULTIPLETURNS)
                    gHitMarker |= HITMARKER_NO_PPDEDUCT;
                gBattleScripting.battler = gBattlerTarget; // For STRINGID_PKMNTRANSFORMED
                gBattlescriptCurrInstr = BattleScript_IceFaceNullsDamage;
                effect = 1;
            }
            break;
        }
        case ABILITYEFFECT_ABSORBING: // 3  //make absorb moves, change target  to mon with absorbing ability
            if (moveArg)    //if said mon isn't statused  if just use status1 can check for all status1 but status1 & staus1_any is stil used in most cases..
            {
                u8 statId;
                switch (gLastUsedAbility)
                {
                case ABILITY_VOLT_ABSORB:
                    if (moveType == TYPE_ELECTRIC && gBattleMoves[moveArg].power != 0)
                        effect = 1;
                    break;
                case ABILITY_WATER_ABSORB:
                case ABILITY_DRY_SKIN:
                    if (moveType == TYPE_WATER && gBattleMoves[moveArg].power != 0)
                        effect = 1;
                    break;
                case ABILITY_GLACIAL_ICE:
                    if (moveType == TYPE_ICE && gBattleMoves[moveArg].power != 0)
                        effect = 1;
                case ABILITY_EROSION:
                    if (moveType == TYPE_ROCK && gBattleMoves[moveArg].power != 0)
                        effect = 1;
                case ABILITY_JEWEL_METABOLISM:
                    if (moveType == TYPE_ROCK && gBattleMoves[moveArg].power != 0)
                        effect = 2, statId = STAT_DEF;
                case ABILITY_MOTOR_DRIVE:
                    if (moveType == TYPE_ELECTRIC && gBattleMoves[moveArg].power != 0)
                        effect = 2, statId = STAT_SPEED;
                    break;
                case ABILITY_LIGHTNING_ROD:
                    if (moveType == TYPE_ELECTRIC && gBattleMoves[moveArg].power != 0)
                        effect = 2, statId = STAT_SPATK;
                    break;
                case ABILITY_STORM_DRAIN:
                    if (moveType == TYPE_WATER && gBattleMoves[moveArg].power != 0)
                        effect = 2, statId = STAT_SPATK;
                    break;
                case ABILITY_SAP_SIPPER:
                    if (moveType == TYPE_GRASS && gBattleMoves[moveArg].power != 0)
                        effect = 2, statId = STAT_ATK;
                    break;
                case ABILITY_GALEFORCE:
                    if (gBattleMoves[move].flags & FLAG_WIND_MOVE)
                        effect = 2, statId = STAT_ATK;
                case ABILITY_LAVA_FISSURE:
                case ABILITY_FLASH_FIRE:
                    if ((moveType == TYPE_FIRE  && gBattleMoves[moveArg].power != 0) && !((gBattleMons[battler].status1 & STATUS1_FREEZE)))// && B_FLASH_FIRE_FROZEN <= GEN_4))
                    {
                        if (!(gBattleResources->flags->flags[battler] & RESOURCE_FLAG_FLASH_FIRE))
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_BOOST;
                            if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost;   // think cna put atk canceler text here, or below in effect1 effect2 stuff
                            else
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost_PPLoss;

                            gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_FLASH_FIRE;
                            effect = 3; //damage unlification handled inpokemon.c
                        }
                        else
                        {
                            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_FLASH_FIRE_NO_BOOST;
                            if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost;
                            else
                                gBattlescriptCurrInstr = BattleScript_FlashFireBoost_PPLoss;

                            effect = 3;
                        }
                    }
                    break;

                } //end of abilities,  start of effect logic

                if (effect == 1) // Drain Hp ability.
                {
                    if (BATTLER_MAX_HP(battler) || gSideStatuses[GET_BATTLER_SIDE(battler)] & SIDE_STATUS_HEAL_BLOCK)
                    {
                        if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                        else
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                    }
                    else
                    {
                        if (gProtectStructs[gBattlerAttacker].notFirstStrike)
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain;
                        else
                            gBattlescriptCurrInstr = BattleScript_MoveHPDrain_PPLoss;

                        gBattleMoveDamage = gBattleMons[battler].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        gBattleMoveDamage *= -1;
                    }
                }
                else if (effect == 2) // Boost Stat ability; //huh forgot to remove damage lol
                {

                    if (!CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
                    {
                        if ((gProtectStructs[gBattlerAttacker].notFirstStrike))
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless;
                        else
                            gBattlescriptCurrInstr = BattleScript_MonMadeMoveUseless_PPLoss;
                    }
                    else //ok these are actually new, in gen 3 even though lightning-rod existed it didn't stat boost
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
            break;// updated ability battle effects for drain abilities 
        case ABILITYEFFECT_MOVE_END: // Think contact abilities. //logic is if target has ablity
            switch (gLastUsedAbility)//double check if forget other abilities
            {
            case ABILITY_COLOR_CHANGE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && moveArg != MOVE_STRUGGLE
                    && gBattleMoves[moveArg].power != 0
                    && TARGET_TURN_DAMAGED
                    && !IS_BATTLER_OF_TYPE(battler, moveType)
                    && gBattleMons[battler].hp != 0)
                {
                    SET_BATTLER_TYPE2(battler, moveType);   //changed only shifts second type when hit, can take advantage of joat that way.
                    PREPARE_TYPE_BUFFER(gBattleTextBuff1, moveType);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ColorChangeActivates;
                    ++effect;
                }
                break;
            case ABILITY_IRON_BARBS:
            case ABILITY_TOUGH_SPINES:
            case ABILITY_ROUGH_SKIN:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && (IsMoveMakingContact(move, gBattlerAttacker)))
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RoughSkinActivates;
                    ++effect;
                }
                break;
            case ABILITY_EMPATHIC_CURSE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED)
                {
                    gBattleMoveDamage = (gHpDealt) / 5;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_EmpathicCurseActivates; //vsonic test
                    ++effect;
                }
                break;
            case ABILITY_SIROCCO:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && (IsMoveMakingContact(move, gBattlerAttacker)))
                {
                    gBattleWeather = (WEATHER_SANDSTORM_TEMPORARY);
                    BattleScriptPushCursorAndCallback(BattleScript_SandSpitActivates); //made custom as sandstream used attack while this is target specific 
                    gBattleScripting.battler = battler;
                    ++effect;
                }
                break;
            case ABILITY_EFFECT_SPORE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GRASS)
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_OVERCOAT
                    && GetBattlerHoldEffect(gBattlerAttacker, TRUE) != HOLD_EFFECT_SAFETY_GOGGLES
                    && TARGET_TURN_DAMAGED
                    && (IsMoveMakingContact(move, gBattlerAttacker))
                    && (Random() % 2) == 0)
                {
                    do
                        gBattleScripting.moveEffect = Random() % 5; //0-4
                    while (gBattleScripting.moveEffect == 0);

                    if (gBattleScripting.moveEffect == MOVE_EFFECT_BURN)
                        gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;


                    if (gBattleScripting.moveEffect == MOVE_EFFECT_FREEZE)
                        gBattleScripting.moveEffect = MOVE_EFFECT_CONFUSION;
                    gBattleScripting.moveEffect += MOVE_EFFECT_AFFECTS_USER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect; //was gonna do infatuation, but there's no way to make it work that would make sense
                    ++effect;
                }
                break;
                //process if hp reaches below half, check if defeatist has already activated,
                       //if not, if speed is not at max stages double speed
                       //also remove any escape prevention including traps for a cost of 1/20 max hp
                       //make sure to not include normal statuses that don't effect switching
                       //so will need a case by case clear but can't use switch statement
                       //at end set special status that defeatist has been activated
            case ABILITY_DEFEATIST:     //end turn pasting in switch in above to complete ability
                if (TARGET_TURN_DAMAGED
                    && gBattleMons[battler].hp < (gBattleMons[battler].maxHP / 2)
                    && gBattleMons[battler].hp != 0)
                {
                    u16 speed = gBattleMons[battler].speed;
                    if (gSpecialStatuses[battler].defeatistActivated != 1)
                    {

                        if (gBattleMons[battler].statStages[STAT_ATK] > 0)
                        {
                            gBattleMons[battler].statStages[STAT_ATK] -= 2;    //should lower stat by 2 i.e 50% 
                            if (gBattleMons[battler].statStages[STAT_ATK] < 0)
                                gBattleMons[battler].statStages[STAT_ATK] = 0;
                            gBattleScripting.animArg1 = 0x11;
                            gBattleScripting.animArg2 = 0;
                            gBattleScripting.battler = battler;
                        }
                        if (gBattleMons[battler].statStages[STAT_SPATK] > 0)
                        {
                            gBattleMons[battler].statStages[STAT_SPATK] -= 2;    //should lower stat by 2 i.e 50% 
                            if (gBattleMons[battler].statStages[STAT_SPATK] < 0)
                                gBattleMons[battler].statStages[STAT_SPATK] = 0;
                            gBattleScripting.animArg1 = 0x11;
                            gBattleScripting.animArg2 = 0;
                            gBattleScripting.battler = battler;
                        }
                        speed *= 2; //should double effective speed without changing stat

                        BattleScriptPushCursorAndCallback(BattleScript_DefeatistActivates);
                        gBattleScripting.battler = battler; //something new for defeatist activation
                        //buff lost the will to fight, and is ready to run!


                        gSpecialStatuses[battler].defeatistActivated = 1;
                        ++effect;
                    }
                }
                break;
            case ABILITY_POISON_POINT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && (IsMoveMakingContact(move, gBattlerAttacker))
                    && CanBePoisoned(gBattlerTarget, gBattlerAttacker) //need remember battlerTarget is spot for one to be poisoned
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_POISON;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_STATIC:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && CanBeParalyzed(gBattlerAttacker)
                    && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ELECTRIC)
                    && (IsMoveMakingContact(move, gBattlerAttacker))
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_PARALYSIS;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_FLAME_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && CanBeBurned(gBattlerAttacker)
                    && (IsMoveMakingContact(move, gBattlerAttacker))
                    && TARGET_TURN_DAMAGED
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_BURN;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_STICKY_HOLD:
            case ABILITY_MAGMA_ARMOR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    //&& IsBattlerAlive(battler) remove this part, so affect activates even if I faint
                    && IsMoveMakingContact(move, gBattlerAttacker))
                {
                    if (GetBattlerAbility(gBattlerAttacker) == ABILITY_STICKY_HOLD)
                    {
                        if (gBattleMons[gBattlerAttacker].item != ITEM_NONE)
                        {
                            gLastUsedAbility = ABILITY_STICKY_HOLD;
                            BattleScriptPushCursor();
                            gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
                            RecordAbilityBattle(gBattlerAttacker, ABILITY_STICKY_HOLD);
                            ++effect;
                        }
                        break;
                    }
                    else if (gBattleMons[gBattlerAttacker].item)
                    {
                        side = GetBattlerSide(gBattlerAttacker);
                        gLastUsedItem = gBattleMons[gBattlerAttacker].item; //need to make sure these work so player can recover item after check theif/knock off function in bs commands vsonic
                        gBattleMons[gBattlerAttacker].item = ITEM_NONE;
                        gWishFutureKnock.knockedOffMons[side] |= gBitTable[gBattlerPartyIndexes[gBattlerAttacker]];
                        BattleScriptPushCursor();
                        if (GetBattlerAbility(battler) == ABILITY_MAGMA_ARMOR)
                            gBattlescriptCurrInstr = BattleScript_MoveEffectIncinerate;   //changed to new magma armor script
                        else if (GetBattlerAbility(battler) == ABILITY_STICKY_HOLD)
                            gBattlescriptCurrInstr = BattleScript_StickyHoldKnockoff;   //if sticky hold
                        gBattleStruct->choicedMove[gBattlerAttacker] = MOVE_NONE; //think can replace with this
                        //*(u8*)((u8*)(&gBattleStruct->choicedMove[gBattlerTarget]) + 0) = 0; //necessary line
                       // *(u8*)((u8*)(&gBattleStruct->choicedMove[gBattlerTarget]) + 1) = 0;
                        ++effect;
                    }
                }
                break;
            case ABILITY_CUTE_CHARM:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && (IsMoveMakingContact(move, gBattlerAttacker))
                    && TARGET_TURN_DAMAGED
                    && gBattleMons[gBattlerTarget].hp != 0
                    && (Random() % 3) == 0
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_OBLIVIOUS
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
            case ABILITY_PERISH_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && IsMoveMakingContact(move, gBattlerAttacker)
                    && !(gStatuses3[gBattlerAttacker] & STATUS3_PERISH_SONG))
                {
                    /*if (!(gStatuses3[battler] & STATUS3_PERISH_SONG))
                    {
                        gStatuses3[battler] |= STATUS3_PERISH_SONG;
                        gDisableStructs[battler].perishSongTimer = 3;
                        gDisableStructs[battler].perishSongTimerStartValue = 3;
                    }*/
                    gStatuses3[gBattlerAttacker] |= STATUS3_PERISH_SONG;
                    gDisableStructs[gBattlerAttacker].perishSongTimer = 3;
                    gDisableStructs[gBattlerAttacker].perishSongTimerStartValue = 3;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_PerishBodyActivates;
                    ++effect;
                }
                break;
            case ABILITY_JUSTIFIED:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST)
                    && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_ATK, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_RATTLED:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && (moveType == TYPE_DARK || moveType == TYPE_BUG || moveType == TYPE_GHOST)
                    && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_WATER_COMPACTION:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && moveType == TYPE_WATER
                    && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_DEF, 2, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_STAMINA:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && CompareStat(battler, STAT_DEF, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_DEF, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_BERSERK:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    // Had more than half of hp before, now has less
                    && gBattleStruct->hpBefore[battler] >= gBattleMons[battler].maxHP / 2
                    && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                    && (gMultiHitCounter == 0 || gMultiHitCounter == 1)
                    //&& !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
                    && CompareStat(battler, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_WIMP_OUT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    // Had more than half of hp before, now has less
                    && gBattleStruct->hpBefore[battler] > gBattleMons[battler].maxHP / 2
                    && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                    && (gMultiHitCounter == 0 || gMultiHitCounter == 1)
                    //&& !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))
                    && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
                    //&& CountUsablePartyMons(battler) > 0  ai change add abck somehow
                    // Not currently held by Sky Drop
                    && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
                {
                    gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_EMERGENCY_EXIT;
                    ++effect;
                }
                break;
            case ABILITY_EMERGENCY_EXIT:    //separate since plan to treat emergency exit differently
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)//will attempt setup after can build/compile
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    // Had more than half of hp before, now has less
                    //&& gBattleStruct->hpBefore[battler] > gBattleMons[battler].maxHP / 2
                    && gBattleMons[battler].hp < gBattleMons[battler].maxHP / 2
                    && (gMultiHitCounter == 0 || gMultiHitCounter == 1)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && (CanBattlerSwitch(battler) || !(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
                    //&& CountUsablePartyMons(battler) > 0
                    // Not currently held by Sky Drop
                    && !(gStatuses3[battler] & STATUS3_SKY_DROPPED))
                {
                    gBattleResources->flags->flags[battler] |= RESOURCE_FLAG_EMERGENCY_EXIT;
                    gSpecialStatuses[battler].EmergencyExit ^= 1;
                    ++effect;
                }
                break;
            case ABILITY_WEAK_ARMOR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && IS_MOVE_PHYSICAL(gCurrentMove)
                    && (CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN) // Don't activate if speed cannot be raised
                        || CompareStat(battler, STAT_DEF, MIN_STAT_STAGE, CMP_GREATER_THAN))) // Don't activate if defense cannot be lowered
                {
                    if (gBattleMoves[gCurrentMove].effect == EFFECT_HIT_ESCAPE && CanBattlerSwitch(gBattlerAttacker))
                        gProtectStructs[battler].disableEjectPack = TRUE;  // Set flag for target

                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WeakArmorActivates;
                    ++effect;
                }
                break;
            case ABILITY_PICKPOCKET:  //looks clunky, think they had troble setting up will attempt to do it better
                if (IsBattlerAlive(gBattlerAttacker)
                    && gBattleMons[gBattlerAttacker].item != ITEM_NONE
                    && !(gWishFutureKnock.knockedOffMons[GetBattlerSide(gBattlerAttacker)] & gBitTable[gBattlerPartyIndexes[gBattlerAttacker]])   //POSSIBLY remove this
                    //&& !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))  // Pickpocket doesn't activate for sheer force  removing this, as its probably a coding error by GF
                    && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)    // Pickpocket requires contact
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED)
                {
                    u8 battlers[4] = { 0, 1, 2, 3 };
                    SortBattlersBySpeed(battlers, FALSE); //If multiple Pok�mon with this Ability are hit by the same move that made contact,
                    for (i = 0; i < gBattlersCount; i++)//Pickpocket will activate for the fastest one that does not already have an item.
                    {
                        u8 battler = battlers[i];
                        // Attacker is mon who made contact, battler is mon with pickpocket
                        if (battler != gBattlerAttacker                                                     // Cannot pickpocket yourself
                            && GetBattlerAbility(battler) == ABILITY_PICKPOCKET                               // Target must have pickpocket ability
                                                                                   // Target needs to have been damaged
                            && !DoesSubstituteBlockMove(gBattlerAttacker, battler, gCurrentMove)              // Subsitute unaffected
                            && IsBattlerAlive(battler)                                                        // Battler must be alive to pickpocket
                            //&& gBattleMons[battler].item == ITEM_NONE)                                      // Pickpocketer can't have an item already  - removed
                            && CanStealItem(battler, gBattlerAttacker, gBattleMons[gBattlerAttacker].item))   // Cannot steal plates, mega stones, etc
                        {
                                gBattlerTarget = gBattlerAbility = battler;
                                // Battle scripting is super brittle so we shall do the item exchange now (if possible)
                                if (GetBattlerAbility(gBattlerAttacker) != ABILITY_STICKY_HOLD)
                                    StealTargetItem(gBattlerTarget, gBattlerAttacker);  // Target takes attacker's item

                                gEffectBattler = gBattlerAttacker;
                                BattleScriptPushCursor();
                                gBattlescriptCurrInstr = BattleScript_Pickpocket;   // Includes sticky hold check to print separate string
                                effect = TRUE;
                                break; // Pickpocket activates on fastest mon, so exit loop.
                        }
                    }
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
                    ++effect;
                }
                break;
            case ABILITY_MUMMY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && IsBattlerAlive(gBattlerAttacker)
                    && TARGET_TURN_DAMAGED
                    && IsMoveMakingContact(move, gBattlerAttacker)
                    && gBattleStruct->overwrittenAbilities[gBattlerAttacker] != GetBattlerAbility(gBattlerTarget))
                {
                    switch (gBattleMons[gBattlerAttacker].ability)
                    {
                    case ABILITY_MUMMY:
                    case ABILITY_BATTLE_BOND:
                    case ABILITY_COMATOSE:
                    case ABILITY_DISGUISE:
                    case ABILITY_ZEN_MODE:
                    case ABILITY_MULTITYPE:
                    case ABILITY_POWER_CONSTRUCT:
                    case ABILITY_RKS_SYSTEM:
                    case ABILITY_SCHOOLING:
                    case ABILITY_SHIELDS_DOWN:
                    case ABILITY_STANCE_CHANGE:
                    case ABILITY_LAVA_FISSURE:
                        break;
                    default:

                        gLastUsedAbility = gBattleMons[gBattlerAttacker].ability = gBattleStruct->overwrittenAbilities[gBattlerAttacker] = gBattleMons[gBattlerTarget].ability;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_MummyActivates;
                        ++effect;
                        break;
                    }
                }
                break;
            case ABILITY_WANDERING_SPIRIT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) //WHY DO these 2 use different restriction? mummy seems to follow simplebeam/entertainment
                    && IsBattlerAlive(gBattlerAttacker)
                    && TARGET_TURN_DAMAGED
                    && (gBattleMoves[move].flags & FLAG_MAKES_CONTACT))
                {
                    switch (gBattleMons[gBattlerAttacker].ability)
                    {
                    case ABILITY_DISGUISE:
                    case ABILITY_FLOWER_GIFT:
                    case ABILITY_GULP_MISSILE:
                    case ABILITY_HUNGER_SWITCH:
                    case ABILITY_ICE_FACE:
                    case ABILITY_ILLUSION:
                    case ABILITY_IMPOSTER:
                    case ABILITY_RECEIVER:
                    case ABILITY_RKS_SYSTEM:
                    case ABILITY_SCHOOLING:
                    case ABILITY_STANCE_CHANGE:
                    case ABILITY_WONDER_GUARD:
                    case ABILITY_DISPIRIT_GUARD:
                    case ABILITY_ZEN_MODE:
                        break;
                    default:

                        gLastUsedAbility = gBattleMons[gBattlerAttacker].ability;
                        gBattleMons[gBattlerAttacker].ability = gBattleStruct->overwrittenAbilities[gBattlerAttacker] = gBattleMons[gBattlerTarget].ability;
                        gBattleMons[gBattlerTarget].ability = gBattleStruct->overwrittenAbilities[gBattlerTarget] = gLastUsedAbility;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_WanderingSpiritActivates;
                        ++effect;
                        break;
                    }
                }
                break;
            case ABILITY_ANGER_POINT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT) //if take a crit hit
                    && IS_CRIT
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    SET_STATCHANGER(STAT_ATK, MAX_STAT_STAGE - gBattleMons[battler].statStages[STAT_ATK], FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetsStatWasMaxedOut;
                    ++effect;
                }
                else if ((gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)   //if take a super effective hit
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && CompareStat(battler, STAT_ATK, MAX_STAT_STAGE, CMP_LESS_THAN))
                {
                    SET_STATCHANGER(STAT_ATK, MAX_STAT_STAGE - gBattleMons[battler].statStages[STAT_ATK], FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetsStatWasMaxedOut;
                    ++effect;
                }
                break;
            case ABILITY_STEADFAST:
                if ((gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)   //if take a super effective hit
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
                { //think will add immunity to crit to thjis, check balance may be too much
                    SET_STATCHANGER(STAT_SPEED, 1, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseOnMoveEnd;  //need test
                    ++effect;
                }
                break;
            case ABILITY_GOOEY:
            case ABILITY_TANGLING_HAIR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerAttacker].hp != 0
                    && (CompareStat(gBattlerAttacker, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN) 
                        || GetBattlerAbility(gBattlerAttacker) == ABILITY_MIRROR_ARMOR
                        || GetBattlerAbility(gBattlerAttacker) == ABILITY_EMPATH)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && IsMoveMakingContact(move, gBattlerAttacker))
                {
                    SET_STATCHANGER(STAT_SPEED, 1, TRUE);
                    gBattleScripting.moveEffect = MOVE_EFFECT_SPD_MINUS_1;
                    PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_GooeyActivates;
                    ++effect;
                }
                break;
            case ABILITY_AFTERMATH:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp == 0
                    && IsBattlerAlive(gBattlerAttacker)
                    && IsMoveMakingContact(move, gBattlerAttacker))
                {
                    u8 battler;
                    if ((battler = IsAbilityOnField(ABILITY_DAMP)))
                    {
                        gBattleScripting.battler = battler - 1;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_DampPreventsAftermath;
                    }
                    else
                    {
                        gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                        if (gBattleMoveDamage == 0)
                            gBattleMoveDamage = 1;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_AftermathDmg;
                    }
                    ++effect;
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
                    ++effect;
                }
                break;
            case ABILITY_ILLUSION:
                if (gBattleStruct->illusion[gBattlerTarget].on && !gBattleStruct->illusion[gBattlerTarget].broken && TARGET_TURN_DAMAGED)
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_IllusionOff;
                    ++effect;
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
                    ++effect;
                }
                break;
            case ABILITY_STEAM_ENGINE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && CompareStat(battler, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN)
                    && (moveType == TYPE_FIRE || moveType == TYPE_WATER))
                {
                    gEffectBattler = battler;
                    SET_STATCHANGER(STAT_SPEED, 6, FALSE);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetAbilityStatRaiseRet;
                    ++effect;
                }
                break;
            case ABILITY_SAND_SPIT:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && !(gBattleWeather & WEATHER_SANDSTORM_TEMPORARY && WEATHER_HAS_EFFECT))
                {
                    if (gBattleWeather & WEATHER_PRIMAL_ANY && WEATHER_HAS_EFFECT)
                    {
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_BlockedByPrimalWeatherRet;
                        ++effect;
                    }
                    else if (TryChangeBattleWeather(battler, ENUM_WEATHER_SANDSTORM, TRUE))
                    {
                        gBattleScripting.battler = gActiveBattler = battler;
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_SandSpitActivates;
                        ++effect;
                    }
                }
                break;
            case ABILITY_GULP_MISSILE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler))
                {
                    if (gBattleMons[gBattlerTarget].species == SPECIES_CRAMORANT_GORGING)
                    {
                        gBattleStruct->changedSpecies[gBattlerPartyIndexes[gBattlerTarget]] = gBattleMons[gBattlerTarget].species;
                        gBattleMons[gBattlerTarget].species = SPECIES_CRAMORANT;
                        if (GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                        {
                            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                        }
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_GulpMissileGorging;
                        ++effect;
                    }
                    else if (gBattleMons[gBattlerTarget].species == SPECIES_CRAMORANT_GULPING)
                    {
                        gBattleStruct->changedSpecies[gBattlerPartyIndexes[gBattlerTarget]] = gBattleMons[gBattlerTarget].species;
                        gBattleMons[gBattlerTarget].species = SPECIES_CRAMORANT;
                        if (GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                        {
                            gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 4;
                            if (gBattleMoveDamage == 0)
                                gBattleMoveDamage = 1;
                        }
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_GulpMissileGulping;
                        ++effect;
                    }
                }
                break;
            }
            break;
        case ABILITYEFFECT_MOVE_END_ATTACKER: // Same as above, but for attacker with ability hits enemy
            switch (gLastUsedAbility)
            {
            case ABILITY_POISON_TOUCH:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && CanBePoisoned(gBattlerAttacker, gBattlerTarget)  //2nd value is battler meant to be poisoned
                    && IsMoveMakingContact(move, gBattlerAttacker)
                    && TARGET_TURN_DAMAGED // Need to actually hit the target
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_POISON; //tesst later
                    //gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                    //PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_TOXUNGUE:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && CanBeParalyzed(gBattlerTarget)
                    && IsMoveMakingContact(move, gBattlerAttacker)
                    && TARGET_TURN_DAMAGED // Need to actually hit the target
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS; //tesst later
                    //gBattleScripting.moveEffect = MOVE_EFFECT_POISON;
                    //PREPARE_ABILITY_BUFFER(gBattleTextBuff1, gLastUsedAbility);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_STATIC:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && CanBeParalyzed(gBattlerTarget)
                    && !IS_BATTLER_OF_TYPE(gBattlerTarget, TYPE_ELECTRIC) //only addition want make, static shouldn't work on electric types
                    && IsMoveMakingContact(move, gBattlerAttacker) //not using other paralyze statemetn cuz think I already have my own logic,\ thats for moves not abilities                    
                    && TARGET_TURN_DAMAGED
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
                    //gBattleScripting.moveEffect = MOVE_EFFECT_PARALYSIS;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_FLAME_BODY:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && CanBeBurned(gBattlerTarget)
                    && IsMoveMakingContact(move, gBattlerAttacker)
                    && TARGET_TURN_DAMAGED
                    && (Random() % 3) == 0)
                {
                    gBattleScripting.moveEffect = MOVE_EFFECT_BURN;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_ApplySecondaryEffect;
                    ++effect;
                }
                break;
            case ABILITY_MAGMA_ARMOR:
                if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && gBattleMons[gBattlerTarget].hp != 0
                    && !gProtectStructs[gBattlerAttacker].confusionSelfDmg
                    && TARGET_TURN_DAMAGED
                    && IsBattlerAlive(battler)
                    && IsMoveMakingContact(move, gBattlerAttacker))
                {
                    if (GetBattlerAbility(gBattlerTarget) == ABILITY_STICKY_HOLD)
                    {
                        if (gBattleMons[gBattlerTarget].item != ITEM_NONE)
                        {
                            gLastUsedAbility = ABILITY_STICKY_HOLD;
                            BattleScriptPushCursor();
                            gBattlescriptCurrInstr = BattleScript_StickyHoldActivates;
                            RecordAbilityBattle(gBattlerTarget, ABILITY_STICKY_HOLD);
                            ++effect;
                        }
                        break;
                    }
                    else if (gBattleMons[gBattlerTarget].item)
                    {
                        side = GetBattlerSide(gBattlerTarget);
                        gLastUsedItem = gBattleMons[gBattlerTarget].item;
                        gBattleMons[gBattlerTarget].item = ITEM_NONE;
                        gWishFutureKnock.knockedOffMons[side] |= gBitTable[gBattlerPartyIndexes[gBattlerTarget]];
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_MoveEffectIncinerate;
                        gBattleStruct->choicedMove[gBattlerTarget] = MOVE_NONE; //think can replace with this
                        //*(u8*)((u8*)(&gBattleStruct->choicedMove[gBattlerTarget]) + 0) = 0; //necessary line
                       // *(u8*)((u8*)(&gBattleStruct->choicedMove[gBattlerTarget]) + 1) = 0;
                        ++effect;
                    }
                }
                break;
            case ABILITY_GULP_MISSILE:
                if (((gCurrentMove == MOVE_SURF && TARGET_TURN_DAMAGED) || gStatuses3[gBattlerAttacker] & STATUS3_UNDERWATER)
                    && (effect = ShouldChangeFormHpBased(gBattlerAttacker)))
                {
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AttackerFormChange;
                    ++effect;
                }
                break;
            case ABILITY_MAGICIAN:    //this and pickpocket should go in abilityeffects function instead, this should only be for   actual move effect only, think wil move the item stuff recently ported from emerald out too
                if (gCurrentMove != MOVE_FLING && gCurrentMove != MOVE_NATURAL_GIFT
                    && gBattleMons[gBattlerAttacker].item == ITEM_NONE
                    && gBattleMons[gBattlerTarget].item != ITEM_NONE
                    && IsBattlerAlive(gBattlerAttacker)
                    && TARGET_TURN_DAMAGED
                    //&& CanStealItem(gBattlerAttacker, gBattlerTarget, gBattleMons[gBattlerTarget].item)
                    && !gSpecialStatuses[gBattlerAttacker].gemBoost   // In base game, gems are consumed after magician would activate.
                    && !(gWishFutureKnock.knockedOffMons[GetBattlerSide(gBattlerTarget)] & gBitTable[gBattlerPartyIndexes[gBattlerTarget]])
                    && !DoesSubstituteBlockMove(gBattlerAttacker, gBattlerTarget, gCurrentMove)
                    && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                    && (GetBattlerAbility(gBattlerTarget) != ABILITY_STICKY_HOLD || !IsBattlerAlive(gBattlerTarget)))
                {
                    StealTargetItem(gBattlerAttacker, gBattlerTarget);
                    gBattleScripting.battler = gBattlerAbility = gBattlerAttacker;
                    gEffectBattler = gBattlerTarget;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MagicianActivates;
                    ++effect;
                }
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
                    gSpecialStatuses[battler].dancerUsedMove = TRUE;
                    gSpecialStatuses[battler].dancerOriginalTarget = *(gBattleStruct->moveTarget + battler) | 0x4;
                    gBattleStruct->atkCancellerTracker = 0;
                    gBattlerAttacker = gBattlerAbility = battler;
                    gCalledMove = gCurrentMove;

                    // Set the target to the original target of the mon that first used a Dance move
                    gBattlerTarget = gBattleScripting.savedBattler & 0x3;

                    // Make sure that the target isn't an ally - if it is, target the original user
                    if (GetBattlerSide(gBattlerTarget) == GetBattlerSide(gBattlerAttacker))
                        gBattlerTarget = (gBattleScripting.savedBattler & 0xF0) >> 4;
                    gHitMarker &= ~HITMARKER_ATTACKSTRING_PRINTED;
                    BattleScriptExecute(BattleScript_DancerActivates);
                    ++effect;
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
                case ABILITY_WATER_BUBBLE:
                    if (gBattleMons[battler].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        effect = 1;
                    }
                    break;
                case ABILITY_LAVA_FISSURE:
                case ABILITY_FLAME_BODY:
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
                    switch (effect) //this switch case tells the effect values what to do
                        //co dependent status - cure cancel out brn cant be with freeze  sleep cant be w spirit lock  psn cant be w toxic
                    {   //was planning change water veil not remove burn if burned but keep from taking burn dmg, would be for things like flame orb toxic orb, 
                        //would allow for more strat and somewhat make sense, if ability was removed and got status then ability came back it wouldn't change causaility
                        //but things like insomnia make sense to remove status mostly because the status is fully debilatating so sleep & freeze
                    case 1: // status cleared
                        gBattleMons[battler].status1 = 0; //if I'm able to apply multiple status may have to change this to like the others and clear specific status
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
            for (battler = 0; battler < gBattlersCount; ++battler) //change to hopefully trigger cherrim form change
            {
                if (gBattleMons[battler].ability == ABILITY_FORECAST || gBattleMons[battler].ability == ABILITY_FLOWER_GIFT)
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
            if ((gLastUsedAbility == ABILITY_SYNCHRONIZE 
                || gLastUsedAbility == ABILITY_EMPATH
                || gLastUsedAbility == ABILITY_EMPATHIC_CURSE) 
                && (gHitMarker & HITMARKER_SYNCHRONIZE_EFFECT))
            {
                gHitMarker &= ~(HITMARKER_SYNCHRONIZE_EFFECT);
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_TOXIC; //changed so it transfers bad poison
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect + MOVE_EFFECT_AFFECTS_USER; //need to understand this
                gBattleScripting.battler = gBattlerTarget;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                ++effect; //This part is just for poison part of logic
            }
            break;
        case ABILITYEFFECT_ATK_SYNCHRONIZE: // 8
            if ((gLastUsedAbility == ABILITY_SYNCHRONIZE || gLastUsedAbility == ABILITY_EMPATH) && (gHitMarker & HITMARKER_SYNCHRONIZE_EFFECT))
            {
                gHitMarker &= ~(HITMARKER_SYNCHRONIZE_EFFECT);
                gBattleStruct->synchronizeMoveEffect &= ~(MOVE_EFFECT_AFFECTS_USER | MOVE_EFFECT_CERTAIN);
                if (gBattleStruct->synchronizeMoveEffect == MOVE_EFFECT_TOXIC)
                    gBattleStruct->synchronizeMoveEffect = MOVE_EFFECT_TOXIC;
                gBattleScripting.moveEffect = gBattleStruct->synchronizeMoveEffect;
                gBattleScripting.battler = gBattlerAttacker; //shows that changing battler for gBattlecripting is enough to shift who script affects
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_SynchronizeActivates;
                ++effect;
            }
            break;
        case ABILITYEFFECT_INTIMIDATE1: // 9
            for (i = 0; i < gBattlersCount; ++i) //activates this intimidate script is ability intimidate and has status3 intimidate, then removes status 3
            {
                if (gBattleMons[i].ability == ABILITY_INTIMIDATE && gStatuses3[i] & STATUS3_INTIMIDATE_POKES)
                {
                    gLastUsedAbility = ABILITY_INTIMIDATE;
                    gStatuses3[i] &= ~(STATUS3_INTIMIDATE_POKES); //need test this may prevent ativation loop
                    BattleScriptPushCursorAndCallback(BattleScript_IntimidateActivatesEnd3); //intimidate script with extra pause beforehand
                    gBattleStruct->intimidateBattler = i;
                    ++effect;
                    break; //this version is for battle start, because its is called in TryDoEventsBeforeFirstTurn function
                }
                else if (gBattleMons[i].ability == ABILITY_TIGER_MOM && gStatuses3[i] & STATUS3_TIGER_MOM_ATTACKS)
                {
                    gLastUsedAbility = ABILITY_TIGER_MOM;
                    gStatuses3[i] &= ~(STATUS3_TIGER_MOM_ATTACKS); //need test this may prevent ativation loop
                    BattleScriptPushCursorAndCallback(BattleScript_IntimidateActivatesEnd3); //intimidate script with extra pause beforehand
                    gBattleStruct->intimidateBattler = i;   //tentatively think I can use this, as think its just setting target?
                    ++effect;
                    break; //this version is for battle start, because its is called in TryDoEventsBeforeFirstTurn function
                }
            }
            break;
        case ABILITYEFFECT_TRACE: // 11
            for (i = 0; i < gBattlersCount; ++i) //handles ability targetting
            {
                if (gBattleMons[i].ability == ABILITY_TRACE && (gStatuses3[i] & STATUS3_TRACE))
                {
                    u8 target2;

                    side = (GetBattlerPosition(i) ^ BIT_SIDE) & BIT_SIDE; // side of the opposing pokemon
                    target1 = GetBattlerAtPosition(side);
                    target2 = GetBattlerAtPosition(side + BIT_FLANK);
                    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
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
                        {
                            gActiveBattler = target1;
                            gBattleMons[i].ability = gBattleMons[gActiveBattler].ability;
                            gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                            ++effect;
                        }
                        else if (gBattleMons[target2].ability != 0 && gBattleMons[target2].hp != 0)
                        {
                            gActiveBattler = target2;
                            gBattleMons[i].ability = gBattleMons[gActiveBattler].ability;
                            gLastUsedAbility = gBattleMons[gActiveBattler].ability;
                            ++effect;
                        }
                    }
                    else
                    {
                        gActiveBattler = target1;
                        if (gBattleMons[target1].ability && gBattleMons[target1].hp) //can use for skill swap wonder gaurd effect
                        {
                            gBattleMons[i].ability = gBattleMons[target1].ability;
                            gLastUsedAbility = gBattleMons[target1].ability;
                            ++effect;
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
            break; //think may be able to use transform targetting logic to swap target to reactivate?
        case ABILITYEFFECT_INTIMIDATE2: // 10
            for (i = 0; i < gBattlersCount; ++i) //any battler
            {//with intimidate and status 3 intimidate pokes
                if (gBattleMons[i].ability == ABILITY_INTIMIDATE && (gStatuses3[i] & STATUS3_INTIMIDATE_POKES))
                    //&& (IsBattlerAlive(BATTLE_OPPOSITE(i)) || IsBattlerAlive(BATTLE_PARTNER(BATTLE_OPPOSITE(i))))) // At least one opposing mon has to be alive.)
                { //change above keeps switch in intimidate from activating on KO'd pokemon - that was because of a previous change i made, default doesn't need that line
                    gLastUsedAbility = ABILITY_INTIMIDATE;
                    gStatuses3[i] &= ~(STATUS3_INTIMIDATE_POKES);// I "think" this removes the status
                    BattleScriptPushCursor(); //so it does'nt reactivate
                    gBattlescriptCurrInstr = BattleScript_IntimidateActivates;
                    gBattleStruct->intimidateBattler = i;
                    ++effect;//so this intimidate has the same activation conditon as other one,  but without the pause
                    break; //I'm assumig one is for battle start and one is for switch in... confirmed
                }//this version is for switch in, so I only need to change this one to make my switch in ability change

                else if (gBattleMons[i].ability == ABILITY_TIGER_MOM && (gStatuses3[i] & STATUS3_TIGER_MOM_ATTACKS))
                {
                    gLastUsedAbility = ABILITY_TIGER_MOM;
                    gStatuses3[i] &= ~(STATUS3_TIGER_MOM_ATTACKS);
                    BattleScriptPushCursor(); //so it does'nt reactivate
                    gBattlescriptCurrInstr = BattleScript_IntimidateActivates;
                    gBattleStruct->intimidateBattler = i;
                    ++effect;//so this intimidate has the same activation conditon as other one,  but without the pause
                    break; //I'm assumig one is for battle start and one is for switch in... confirmed
                }
            }
            break;
        case ABILITYEFFECT_NEUTRALIZINGGAS:
            // Prints message only. separate from ABILITYEFFECT_ON_SWITCHIN bc activates before entry hazards
            for (i = 0; i < gBattlersCount; i++)
            {
                if (gBattleMons[i].ability == ABILITY_NEUTRALIZING_GAS && !(gBattleResources->flags->flags[i] & RESOURCE_FLAG_NEUTRALIZING_GAS))
                {
                    gBattleResources->flags->flags[i] |= RESOURCE_FLAG_NEUTRALIZING_GAS;
                    gBattlerAbility = i;
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SWITCHIN_NEUTRALIZING_GAS;
                    BattleScriptPushCursorAndCallback(BattleScript_SwitchInAbilityMsg);
                    ++effect;
                }

                if (effect)
                    break;
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
            /* ABILITYEFFECT_FIELD_SPORT: // 14   can remove when timer setup done
                switch (gLastUsedAbility)
                {
                case 0xFC:
                    for (i = 0; i < gBattlersCount; ++i)    //checks entire field
                        if (gSideStatuses[i] & SIDE_STATUS_MUDSPORT)
                            effect = i + 1;
                    break;
                case 0xFD:
                    for (i = 0; i < gBattlersCount; ++i)
                        if (gSideStatuses[i] & SIDE_STATUS_WATERSPORT)
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
                break;*/
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
        case ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER: // 15  ?
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

// Possible return values are defined in battle.h following MOVE_TARGET_SELECTED
u32 GetBattlerMoveTargetType(u8 battlerId, u16 move)
{
    u32 target;

    if (gBattleMoves[move].effect == EFFECT_EXPANDING_FORCE
        && IsBattlerTerrainAffected(battlerId, STATUS_FIELD_PSYCHIC_TERRAIN))
        return MOVE_TARGET_BOTH;
    else
        return gBattleMoves[move].target;
}

bool32 CanTargetBattler(u8 battlerAtk, u8 battlerDef, u16 move)
{
    if (gBattleMoves[move].effect == EFFECT_HIT_ENEMY_HEAL_ALLY
        && GetBattlerSide(battlerAtk) == GetBattlerSide(battlerDef)
        && gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_HEAL_BLOCK)
        return FALSE;   // Pok�mon affected by Heal Block cannot target allies with Pollen Puff
    return TRUE;
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

// second argument is 1/X of current hp compared to max hp
bool32 HasEnoughHpToEatBerry(u8 battlerId, u32 hpFraction, u16 itemId)
{
    bool32 isBerry = (ItemId_GetPocket(itemId) == POCKET_BERRY_POUCH);

    if (gBattleMons[battlerId].hp == 0)
        return FALSE;
    if (gBattleScripting.overrideBerryRequirements)
        return TRUE;
    // Unnerve prevents consumption of opponents' berries.
    if (isBerry && IsUnnerveAbilityOnOpposingSide(battlerId))
        return FALSE;
    if (gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / hpFraction)
        return TRUE;

    if (hpFraction <= 4 && GetBattlerAbility(battlerId) == ABILITY_GLUTTONY && isBerry
        && gBattleMons[battlerId].hp <= gBattleMons[battlerId].maxHP / 2)
    {
        RecordAbilityBattle(battlerId, ABILITY_GLUTTONY);
        return TRUE;
    }

    return FALSE;
}

static u8 ItemHealHp(u32 battlerId, u32 itemId, bool32 end2, bool32 percentHeal)
{
    if (HasEnoughHpToEatBerry(battlerId, 2, itemId)
        && !(gBattleScripting.overrideBerryRequirements && gBattleMons[battlerId].hp == gBattleMons[battlerId].maxHP))
    {
        if (percentHeal)
            gBattleMoveDamage = (gBattleMons[battlerId].maxHP * GetBattlerHoldEffectParam(battlerId) / 100) * -1;
        else
            gBattleMoveDamage = GetBattlerHoldEffectParam(battlerId) * -1;

        // check ripen
        if (ItemId_GetPocket(itemId) == POCKET_BERRY_POUCH && GetBattlerAbility(battlerId) == ABILITY_RIPEN)
            gBattleMoveDamage *= 2;

        gBattlerAbility = battlerId;    // in SWSH, berry juice shows ability pop up but has no effect. This is mimicked here
        if (end2)
        {
            BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet;
        }
        return ITEM_HP_CHANGE;
    }
    return 0;
}

static u8 HealConfuseBerry(u8 battlerId, u16 itemId, u8 flavorId, bool32 end2)  //consider putting back to u32 it does something for efficiency?
{
    if (HasEnoughHpToEatBerry(battlerId, 2, itemId))
    {
        PREPARE_FLAVOR_BUFFER(gBattleTextBuff1, flavorId);

        gBattleMoveDamage = gBattleMons[battlerId].maxHP / GetBattlerHoldEffectParam(battlerId);
        if (gBattleMoveDamage == 0)
            gBattleMoveDamage = 1;
        gBattleMoveDamage *= -1;

        if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
        {
            gBattleMoveDamage *= 2;
            gBattlerAbility = battlerId;
        }
        gBattleScripting.battler = battlerId;
        if (end2)
        {
            if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, flavorId) < 0)
                BattleScriptExecute(BattleScript_BerryConfuseHealEnd2);
            else
                BattleScriptExecute(BattleScript_ItemHealHP_RemoveItem);
        }
        else
        {
            BattleScriptPushCursor();
            if (GetFlavorRelationByPersonality(gBattleMons[battlerId].personality, flavorId) < 0)
                gBattlescriptCurrInstr = BattleScript_BerryConfuseHealRet;  //added
            else
                gBattlescriptCurrInstr = BattleScript_ItemHealHP_RemoveItemRet; //added
        }

        return ITEM_HP_CHANGE;
    }
    return 0;
}

static u8 StatRaiseBerry(u8 battlerId, u16 itemId, u8 statId, bool32 end2)
{
    if (CompareStat(battlerId, statId, MAX_STAT_STAGE, CMP_LESS_THAN) && HasEnoughHpToEatBerry(battlerId, GetBattlerHoldEffectParam(battlerId), itemId))
    {
        BufferStatChange(battlerId, statId, STRINGID_STATROSE);
        gEffectBattler = battlerId;
        if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
            SET_STATCHANGER(statId, 2, FALSE);
        else
            SET_STATCHANGER(statId, 1, FALSE);

        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;

        if (end2)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 RandomStatRaiseBerry(u8 battlerId, u16 itemId, bool32 end2)
{
    s32 i;
    u16 stringId;

    for (i = 0; i < NUM_STATS - 1; i++)
    {
        if (CompareStat(battlerId, STAT_ATK + i, MAX_STAT_STAGE, CMP_LESS_THAN))
            break;
    }
    if (i != NUM_STATS - 1 && HasEnoughHpToEatBerry(battlerId, GetBattlerHoldEffectParam(battlerId), itemId))
    {
        u16 battlerAbility = GetBattlerAbility(battlerId);
        do
        {
            i = Random() % (NUM_STATS - 1);
        } while (!CompareStat(battlerId, STAT_ATK + i, MAX_STAT_STAGE, CMP_LESS_THAN));

        PREPARE_STAT_BUFFER(gBattleTextBuff1, i + 1);
        stringId = (battlerAbility == ABILITY_CONTRARY) ? STRINGID_STATFELL : STRINGID_STATROSE;
        gBattleTextBuff2[0] = B_BUFF_PLACEHOLDER_BEGIN;
        gBattleTextBuff2[1] = B_BUFF_STRING;
        gBattleTextBuff2[2] = STRINGID_STATSHARPLY;
        gBattleTextBuff2[3] = STRINGID_STATSHARPLY >> 8;
        gBattleTextBuff2[4] = B_BUFF_STRING;
        gBattleTextBuff2[5] = stringId;
        gBattleTextBuff2[6] = stringId >> 8;
        gBattleTextBuff2[7] = EOS;
        gEffectBattler = battlerId;
        if (battlerAbility == ABILITY_RIPEN)
            SET_STATCHANGER(i + 1, 4, FALSE);
        else
            SET_STATCHANGER(i + 1, 2, FALSE);

        gBattleScripting.animArg1 = 0x21 + i + 6;
        gBattleScripting.animArg2 = 0;
        if (end2)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }

        return ITEM_STATS_CHANGE;
    }
    return 0;
}

static u8 TrySetMicleBerry(u8 battlerId, u16 itemId, bool32 end2)
{
    if (HasEnoughHpToEatBerry(battlerId, 4, itemId))
    {
        gProtectStructs[battlerId].usedMicleBerry = TRUE;  // battler's next attack has increased accuracy

        if (end2)
        {
            BattleScriptExecute(BattleScript_MicleBerryActivateEnd2);   //need make battlescript for this  //added
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_MicleBerryActivateRet;    //and for this   //added
        }
        return ITEM_EFFECT_OTHER;
    }
    return 0;
}

static u8 DamagedStatBoostBerryEffect(u8 battlerId, u8 statId, u8 split)
{
    if (IsBattlerAlive(battlerId)
        && TARGET_TURN_DAMAGED
        && CompareStat(battlerId, statId, MAX_STAT_STAGE, CMP_LESS_THAN)
        && !DoesSubstituteBlockMove(gBattlerAttacker, battlerId, gCurrentMove)
        && GetBattleMoveSplit(gCurrentMove) == split)
    {
        BufferStatChange(battlerId, statId, STRINGID_STATROSE);

        gEffectBattler = battlerId;
        if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
            SET_STATCHANGER(statId, 2, FALSE);
        else
            SET_STATCHANGER(statId, 1, FALSE);

        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;
        BattleScriptPushCursor();
        gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

u8 TryHandleSeed(u8 battler, u32 terrainFlag, u8 statId, u16 itemId, bool32 execute)
{
    if (gFieldStatuses & terrainFlag && CompareStat(battler, statId, MAX_STAT_STAGE, CMP_LESS_THAN))
    {
        BufferStatChange(battler, statId, STRINGID_STATROSE);
        gLastUsedItem = itemId; // For surge abilities
        gEffectBattler = gBattleScripting.battler = battler;
        SET_STATCHANGER(statId, 1, FALSE);
        gBattleScripting.animArg1 = 14 + statId;
        gBattleScripting.animArg2 = 0;
        if (execute)
        {
            BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
        }
        else
        {
            BattleScriptPushCursor();
            gBattlescriptCurrInstr = BattleScript_BerryStatRaiseRet;
        }
        return ITEM_STATS_CHANGE;
    }
    return 0;
}

bool32 TryRoomService(u8 battlerId)
{
    if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM && CompareStat(battlerId, STAT_SPEED, MIN_STAT_STAGE, CMP_GREATER_THAN))
    {
        BufferStatChange(battlerId, STAT_SPEED, STRINGID_STATFELL);
        gEffectBattler = gBattleScripting.battler = battlerId;
        SET_STATCHANGER(STAT_SPEED, 1, TRUE);
        gBattleScripting.animArg1 = 14 + STAT_SPEED;
        gBattleScripting.animArg2 = 0;
        gLastUsedItem = gBattleMons[battlerId].item;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//commened out original itemBattleEffects function  after is one ported direct from emerald
/*
u8 ItemBattleEffects(u8 caseID, u8 battlerId, bool8 moveTurn)
{
    int i = 0, moveType;
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
            case HOLD_EFFECT_RESTORE_HP:    //eating berry handled here and throughout function. seems no specific case made for them
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
            case HOLD_EFFECT_MENTAL_HERB:
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
            case HOLD_EFFECT_MENTAL_HERB:
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
                    gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
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
*/

static bool32 GetMentalHerbEffect(u8 battlerId)
{
    bool32 ret = FALSE;

    // Check infatuation
    if (gBattleMons[battlerId].status2 & STATUS2_INFATUATION)
    {
        gBattleMons[battlerId].status2 &= ~STATUS2_INFATUATION;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_INFATUATION;  // STRINGID_TARGETGOTOVERINFATUATION
        StringCopy(gBattleTextBuff1, gStatusConditionString_LoveJpn);
        ret = TRUE;
    }
    // Check taunt
    if (gDisableStructs[battlerId].tauntTimer != 0)
    {
        gDisableStructs[battlerId].tauntTimer = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_TAUNT;
        PREPARE_MOVE_BUFFER(gBattleTextBuff1, MOVE_TAUNT);
        ret = TRUE;
    }
    // Check encore
    if (gDisableStructs[battlerId].encoreTimer != 0)
    {
        gDisableStructs[battlerId].encoredMove = 0;
        gDisableStructs[battlerId].encoreTimer = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_ENCORE;   // STRINGID_PKMNENCOREENDED
        ret = TRUE;
    }
    // Check torment
    if (gBattleMons[battlerId].status2 & STATUS2_TORMENT)
    {
        gBattleMons[battlerId].status2 &= ~STATUS2_TORMENT;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_TORMENT;
        ret = TRUE;
    }
    // Check heal block
    if (gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK)
    {
        gSideStatuses[GET_BATTLER_SIDE(battlerId)] &= ~SIDE_STATUS_HEAL_BLOCK;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_HEALBLOCK;
        ret = TRUE;
    }
    // Check disable
    if (gDisableStructs[battlerId].disableTimer != 0)
    {
        gDisableStructs[battlerId].disableTimer = 0;
        gDisableStructs[battlerId].disabledMove = 0;
        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_MENTALHERBCURE_DISABLE;
        ret = TRUE;
    }

    return ret;
}


u8 ItemBattleEffects(u8 caseID, u8 battlerId, bool8 moveTurn)   //updated
{
    int i = 0, moveType;
    u8 effect = ITEM_NO_EFFECT;
    u8 changedPP = 0;
    u8 battlerHoldEffect, atkHoldEffect;
    u8 atkHoldEffectParam;
    u16 atkItem;

    gLastUsedItem = gBattleMons[battlerId].item;
    battlerHoldEffect = GetBattlerHoldEffect(battlerId, TRUE);

    atkItem = gBattleMons[gBattlerAttacker].item;
    atkHoldEffect = GetBattlerHoldEffect(gBattlerAttacker, TRUE);
    atkHoldEffectParam = GetBattlerHoldEffectParam(gBattlerAttacker);

    switch (caseID)
    {
    case ITEMEFFECT_ON_SWITCH_IN:
        if (!gSpecialStatuses[battlerId].switchInItemDone)
        {
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_DOUBLE_PRIZE:
                if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)// && !gBattleStruct->moneyMultiplierItem)
                {
                    gBattleStruct->moneyMultiplier = 2;
                    /*gBattleStruct->moneyMultiplier *= 2;
                    gBattleStruct->moneyMultiplierItem = 1;*/

                    //don't know what moneymultiplier item is, don't see where its used.. returned to default
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerId].statStages[i] < DEFAULT_STAT_STAGE)
                    {
                        gBattleMons[battlerId].statStages[i] = DEFAULT_STAT_STAGE;
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
            case HOLD_EFFECT_CONFUSE_SPICY:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SPICY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_DRY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SWEET, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_BITTER, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SOUR, TRUE);
                break;
            case HOLD_EFFECT_ATTACK_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_ATK, TRUE);
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_DEF, TRUE);
                break;
            case HOLD_EFFECT_SPEED_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPEED, TRUE);
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPATK, TRUE);
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPDEF, TRUE);
                break;
            case HOLD_EFFECT_CRITICAL_UP:
                if (!(gBattleMons[battlerId].status2 & STATUS2_FOCUS_ENERGY) && HasEnoughHpToEatBerry(battlerId, GetBattlerHoldEffectParam(battlerId), gLastUsedItem))
                {
                    gBattleMons[battlerId].status2 |= STATUS2_FOCUS_ENERGY;
                    BattleScriptExecute(BattleScript_BerryFocusEnergyEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)   //adds gen 4 berry activation i.e b
                effect = RandomStatRaiseBerry(battlerId, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_PARALYSIS;
                    BattleScriptExecute(BattleScript_BerryCurePrlzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptExecute(BattleScript_BerryCurePsnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battlerId].status1 & STATUS1_BURN && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_BURN;
                    BattleScriptExecute(BattleScript_BerryCureBrnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battlerId].status1 & STATUS1_FREEZE && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_FREEZE;
                    BattleScriptExecute(BattleScript_BerryCureFrzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battlerId].status1 & STATUS1_SLEEP && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_SLEEP;
                    gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptExecute(BattleScript_BerryCureSlpEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if ((gBattleMons[battlerId].status1 & STATUS1_ANY || gBattleMons[battlerId].status2 & STATUS2_CONFUSION) && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    i = 0;
                    if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
                        i++;
                    }
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    gBattleMons[battlerId].status1 = 0;
                    gBattleMons[battlerId].status2 &= ~STATUS2_CONFUSION;
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_RESTORE_HP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, TRUE, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                //if (B_BERRIES_INSTANT >= GEN_4
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, TRUE, TRUE);
                break;
            case HOLD_EFFECT_AIR_BALLOON:
                effect = ITEM_EFFECT_OTHER;
                gBattleScripting.battler = battlerId;
                BattleScriptPushCursorAndCallback(BattleScript_AirBaloonMsgIn);
                RecordItemEffectBattle(battlerId, HOLD_EFFECT_AIR_BALLOON);
                break;
            case HOLD_EFFECT_ROOM_SERVICE:
                if (TryRoomService(battlerId))
                {
                    BattleScriptExecute(BattleScript_BerryStatRaiseEnd2);
                    effect = ITEM_STATS_CHANGE;
                }
                break;
            case HOLD_EFFECT_SEEDS:
                switch (GetBattlerHoldEffectParam(battlerId))
                {
                case HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN:
                    effect = TryHandleSeed(battlerId, STATUS_FIELD_ELECTRIC_TERRAIN, STAT_DEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_GRASSY_TERRAIN:
                    effect = TryHandleSeed(battlerId, STATUS_FIELD_GRASSY_TERRAIN, STAT_DEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_MISTY_TERRAIN:
                    effect = TryHandleSeed(battlerId, STATUS_FIELD_MISTY_TERRAIN, STAT_SPDEF, gLastUsedItem, TRUE);
                    break;
                case HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN:
                    effect = TryHandleSeed(battlerId, STATUS_FIELD_PSYCHIC_TERRAIN, STAT_SPDEF, gLastUsedItem, TRUE);
                    break;
                }
                break;
            case HOLD_EFFECT_EJECT_PACK:
                if (gProtectStructs[battlerId].disableEjectPack == 0
                //if (gProtectStructs[battlerId].statFell
                 //   && gProtectStructs[battlerId].disableEjectPack == 0
                    && !(gCurrentMove == MOVE_PARTING_SHOT && CanBattlerSwitch(gBattlerAttacker))) // Does not activate if attacker used Parting Shot and can switch out
                {
                    //gProtectStructs[battlerId].statFell = FALSE;  //vsonic, need check this if can replace with statLowered
                    gActiveBattler = gBattleScripting.battler = battlerId;
                    effect = ITEM_STATS_CHANGE;
                    if (moveTurn)
                    {
                        BattleScriptPushCursor();
                        gBattlescriptCurrInstr = BattleScript_EjectPackActivate_Ret;
                    }
                    else
                    {
                        BattleScriptExecute(BattleScript_EjectPackActivate_End2);
                    }
                }
                break;
            }

            if (effect)
            {
                gSpecialStatuses[battlerId].switchInItemDone = TRUE;
                gActiveBattler = gBattlerAttacker = gPotentialItemEffectBattler = gBattleScripting.battler = battlerId;
                switch (effect)
                {
                case ITEM_STATUS_CHANGE:
                    BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battlerId].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case ITEM_PP_CHANGE:
                    if (MOVE_IS_PERMANENT(battlerId, i))
                        gBattleMons[battlerId].pp[i] = changedPP;
                    break;
                }
            }
        }
        break;
    case ITEMEFFECT_NORMAL:
        if (gBattleMons[battlerId].hp)
        {
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_RESTORE_HP:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, TRUE, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, TRUE, TRUE);
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

                    for (i = 0; i < MAX_MON_MOVES; i++)
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
                        u8 ppRestored = GetBattlerHoldEffectParam(battlerId);

                        if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
                        {
                            ppRestored *= 2;
                            gBattlerAbility = battlerId;
                        }
                        if (changedPP + ppRestored > maxPP)
                            changedPP = maxPP;
                        else
                            changedPP = changedPP + ppRestored;

                        PREPARE_MOVE_BUFFER(gBattleTextBuff1, move);

                        BattleScriptExecute(BattleScript_BerryPPHealEnd2);
                        BtlController_EmitSetMonData(BUFFER_A, i + REQUEST_PPMOVE1_BATTLE, 0, 1, &changedPP);
                        MarkBattlerForControllerExec(gActiveBattler);
                        effect = ITEM_PP_CHANGE;
                    }
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerId].statStages[i] < DEFAULT_STAT_STAGE)
                    {
                        gBattleMons[battlerId].statStages[i] = DEFAULT_STAT_STAGE;
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
            case HOLD_EFFECT_BLACK_SLUDGE:
                if (IS_BATTLER_OF_TYPE(battlerId, TYPE_POISON))
                {
                    goto LEFTOVERS;
                }
                else if (GetBattlerAbility(battlerId) != ABILITY_MAGIC_GUARD && !moveTurn)
                {
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    BattleScriptExecute(BattleScript_ItemHurtEnd2);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battlerId, battlerHoldEffect);
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                }
                break;
            case HOLD_EFFECT_LEFTOVERS:
            LEFTOVERS:
                if (gBattleMons[battlerId].hp < gBattleMons[battlerId].maxHP && !moveTurn
                    && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                {
                    gBattleMoveDamage = gBattleMons[battlerId].maxHP / 16;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    gBattleMoveDamage *= -1;
                    BattleScriptExecute(BattleScript_ItemHealHP_End2);
                    effect = ITEM_HP_CHANGE;
                    RecordItemEffectBattle(battlerId, battlerHoldEffect);
                }
                break;
            case HOLD_EFFECT_CONFUSE_SPICY:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SPICY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_DRY, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SWEET, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_BITTER, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                if (!moveTurn && !(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SOUR, TRUE);
                break;
            case HOLD_EFFECT_ATTACK_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_ATK, TRUE);
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_DEF, TRUE);
                break;
            case HOLD_EFFECT_SPEED_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPEED, TRUE);
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPATK, TRUE);
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                if (!moveTurn)
                    effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPDEF, TRUE);
                break;
            case HOLD_EFFECT_CRITICAL_UP:
                if (!moveTurn && !(gBattleMons[battlerId].status2 & STATUS2_FOCUS_ENERGY)
                    && HasEnoughHpToEatBerry(battlerId, GetBattlerHoldEffectParam(battlerId), gLastUsedItem))
                {
                    gBattleMons[battlerId].status2 |= STATUS2_FOCUS_ENERGY;
                    BattleScriptExecute(BattleScript_BerryFocusEnergyEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                if (!moveTurn)
                    effect = RandomStatRaiseBerry(battlerId, gLastUsedItem, TRUE);
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_PARALYSIS;
                    BattleScriptExecute(BattleScript_BerryCurePrlzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptExecute(BattleScript_BerryCurePsnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battlerId].status1 & STATUS1_BURN && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_BURN;
                    BattleScriptExecute(BattleScript_BerryCureBrnEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battlerId].status1 & STATUS1_FREEZE && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_FREEZE;
                    BattleScriptExecute(BattleScript_BerryCureFrzEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battlerId].status1 & STATUS1_SLEEP && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_SLEEP;
                    gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptExecute(BattleScript_BerryCureSlpEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_CONFUSION:
                if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status2 &= ~STATUS2_CONFUSION;
                    BattleScriptExecute(BattleScript_BerryCureConfusionEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if ((gBattleMons[battlerId].status1 & STATUS1_ANY || gBattleMons[battlerId].status2 & STATUS2_CONFUSION) && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    i = 0;
                    if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);
                        i++;
                    }
                    if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                    {
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);
                        i++;
                    }
                    if (i <= 1)
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    else
                        gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_NORMALIZED_STATUS;
                    gBattleMons[battlerId].status1 = 0;
                    gBattleMons[battlerId].status2 &= ~STATUS2_CONFUSION;
                    BattleScriptExecute(BattleScript_BerryCureChosenStatusEnd2);
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_MENTAL_HERB:
                if (GetMentalHerbEffect(battlerId))
                {
                    gBattleScripting.savedBattler = gBattlerAttacker;
                    gBattlerAttacker = battlerId;
                    BattleScriptExecute(BattleScript_MentalHerbCureEnd2);
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_MICLE_BERRY:
                if (!moveTurn)
                    effect = TrySetMicleBerry(battlerId, gLastUsedItem, TRUE);
                break;
            }

            if (effect)
            {
                gActiveBattler = gBattlerAttacker = gPotentialItemEffectBattler = gBattleScripting.battler = battlerId;
                switch (effect)
                {
                case ITEM_STATUS_CHANGE:
                    BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battlerId].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                    break;
                case ITEM_PP_CHANGE:
                    if (MOVE_IS_PERMANENT(battlerId, i))
                        gBattleMons[battlerId].pp[i] = changedPP;
                    break;
                }
            }
        }
        break;
    case ITEMEFFECT_BATTLER_MOVE_END:
        goto DO_ITEMEFFECT_MOVE_END;    // this hurts a bit to do, but is an easy solution
    case ITEMEFFECT_MOVE_END:
        for (battlerId = 0; battlerId < gBattlersCount; battlerId++)//^ not my note
        {
            gLastUsedItem = gBattleMons[battlerId].item;
            battlerHoldEffect = GetBattlerHoldEffect(battlerId, TRUE);
        DO_ITEMEFFECT_MOVE_END:
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_MICLE_BERRY:
                //if (B_HP_BERRIES >= GEN_4)
                effect = TrySetMicleBerry(battlerId, gLastUsedItem, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_HP:
                //if (B_HP_BERRIES >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, FALSE, FALSE);
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = ItemHealHp(battlerId, gLastUsedItem, FALSE, TRUE);
                break;
            case HOLD_EFFECT_CONFUSE_SPICY:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SPICY, FALSE);
                break;
            case HOLD_EFFECT_CONFUSE_DRY:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_DRY, FALSE);
                break;
            case HOLD_EFFECT_CONFUSE_SWEET:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SWEET, FALSE);
                break;
            case HOLD_EFFECT_CONFUSE_BITTER:
                //if (B_BERRIES_INSTANT >= GEN_4)
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_BITTER, FALSE);
                break;
            case HOLD_EFFECT_CONFUSE_SOUR:
                //if (B_BERRIES_INSTANT >= GEN_4)   //check how these work, I don't want it stopping multi hit moves etc.
                if (!(gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_HEAL_BLOCK))
                    effect = HealConfuseBerry(battlerId, gLastUsedItem, FLAVOR_SOUR, FALSE);
                break;
            case HOLD_EFFECT_ATTACK_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)   //vsonic important
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_ATK, FALSE);
                break;
            case HOLD_EFFECT_DEFENSE_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_DEF, FALSE);
                break;
            case HOLD_EFFECT_SPEED_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPEED, FALSE);
                break;
            case HOLD_EFFECT_SP_ATTACK_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPATK, FALSE);
                break;
            case HOLD_EFFECT_SP_DEFENSE_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = StatRaiseBerry(battlerId, gLastUsedItem, STAT_SPDEF, FALSE);
                break;
            case HOLD_EFFECT_RANDOM_STAT_UP:
                //if (B_BERRIES_INSTANT >= GEN_4)
                effect = RandomStatRaiseBerry(battlerId, gLastUsedItem, FALSE);
                break;
            case HOLD_EFFECT_CURE_PAR:
                if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_PARALYSIS;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureParRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_PSN:
                if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~(STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER);
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCurePsnRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_BRN:
                if (gBattleMons[battlerId].status1 & STATUS1_BURN && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_BURN;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureBrnRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_FRZ:
                if (gBattleMons[battlerId].status1 & STATUS1_FREEZE && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_FREEZE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureFrzRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_SLP:
                if (gBattleMons[battlerId].status1 & STATUS1_SLEEP && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status1 &= ~STATUS1_SLEEP;
                    gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureSlpRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_CURE_CONFUSION:
                if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    gBattleMons[battlerId].status2 &= ~STATUS2_CONFUSION;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_BerryCureConfusionRet;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_MENTAL_HERB:
                if (GetMentalHerbEffect(battlerId))
                {
                    gBattleScripting.savedBattler = gBattlerAttacker;
                    gBattlerAttacker = battlerId;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_MentalHerbCureRet;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            case HOLD_EFFECT_CURE_STATUS:
                if ((gBattleMons[battlerId].status1 & STATUS1_ANY || gBattleMons[battlerId].status2 & STATUS2_CONFUSION) && !UnnerveOn(battlerId, gLastUsedItem))
                {
                    if (gBattleMons[battlerId].status1 & STATUS1_PSN_ANY)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_PoisonJpn);

                    if (gBattleMons[battlerId].status1 & STATUS1_SLEEP)
                    {
                        gBattleMons[battlerId].status2 &= ~STATUS2_NIGHTMARE;
                        StringCopy(gBattleTextBuff1, gStatusConditionString_SleepJpn);
                    }

                    if (gBattleMons[battlerId].status1 & STATUS1_PARALYSIS)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ParalysisJpn);

                    if (gBattleMons[battlerId].status1 & STATUS1_BURN)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_BurnJpn);

                    if (gBattleMons[battlerId].status1 & STATUS1_FREEZE)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_IceJpn);

                    if (gBattleMons[battlerId].status2 & STATUS2_CONFUSION)
                        StringCopy(gBattleTextBuff1, gStatusConditionString_ConfusionJpn);

                    gBattleMons[battlerId].status1 = 0;
                    gBattleMons[battlerId].status2 &= ~STATUS2_CONFUSION;
                    BattleScriptPushCursor();
                    gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CURED_PROBLEM;
                    gBattlescriptCurrInstr = BattleScript_BerryCureChosenStatusRet;
                    effect = ITEM_STATUS_CHANGE;
                }
                break;
            case HOLD_EFFECT_RESTORE_STATS:
                for (i = 0; i < NUM_BATTLE_STATS; i++)
                {
                    if (gBattleMons[battlerId].statStages[i] < DEFAULT_STAT_STAGE)
                    {
                        gBattleMons[battlerId].statStages[i] = DEFAULT_STAT_STAGE;
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
                gActiveBattler = gPotentialItemEffectBattler = gBattleScripting.battler = battlerId;
                if (effect == ITEM_STATUS_CHANGE)
                {
                    BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[gActiveBattler].status1);
                    MarkBattlerForControllerExec(gActiveBattler);
                }
                break;
            }
        }
        break;
    case ITEMEFFECT_KINGSROCK:
        // Occur on each hit of a multi-strike move
        switch (atkHoldEffect)
        {
        case HOLD_EFFECT_FLINCH:

            if (GetBattlerAbility(gBattlerAttacker) == ABILITY_SERENE_GRACE)
                atkHoldEffectParam *= 2;

            if (gBattleMoveDamage != 0  // Need to have done damage
                && !(gMoveResultFlags & MOVE_RESULT_NO_EFFECT)
                && TARGET_TURN_DAMAGED
                && (Random() % 100) < atkHoldEffectParam
                && gBattleMoves[gCurrentMove].flags & FLAG_KINGS_ROCK_AFFECTED
                && gBattleMons[gBattlerTarget].hp)
            {
                gBattleScripting.moveEffect = MOVE_EFFECT_FLINCH;
                BattleScriptPushCursor();
                SetMoveEffect(FALSE, 0);
                BattleScriptPop();
            }
            break;
        case HOLD_EFFECT_BLUNDER_POLICY:
            if (gBattleStruct->blunderPolicy
                && gBattleMons[gBattlerAttacker].hp != 0
                && CompareStat(gBattlerAttacker, STAT_SPEED, MAX_STAT_STAGE, CMP_LESS_THAN))
            {
                gBattleStruct->blunderPolicy = FALSE;
                gLastUsedItem = atkItem;
                gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPEED, 2, FALSE);
                effect = ITEM_STATS_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackerItemStatRaise;
            }
            break;
        }
        break;
    case ITEMEFFECT_LIFEORB_SHELLBELL:
        // Occur after the final hit of a multi-strike move
        switch (atkHoldEffect)
        {
        case HOLD_EFFECT_SHELL_BELL:
            if (gSpecialStatuses[gBattlerAttacker].damagedMons  // Need to have done damage
                && gBattlerAttacker != gBattlerTarget
                && gBattleMons[gBattlerAttacker].hp != gBattleMons[gBattlerAttacker].maxHP
                && gBattleMons[gBattlerAttacker].hp != 0
                && !(gSideStatuses[GET_BATTLER_SIDE(gBattlerAttacker)] & SIDE_STATUS_HEAL_BLOCK))
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
                effect = ITEM_HP_CHANGE;
            }
            break;
        case HOLD_EFFECT_LIFE_ORB:
            if (IsBattlerAlive(gBattlerAttacker)
                && !(TestSheerForceFlag(gBattlerAttacker, gCurrentMove))    //keeping this
                && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD
                && gSpecialStatuses[gBattlerAttacker].damagedMons)
            {
                gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 10;
                if (gBattleMoveDamage == 0)
                    gBattleMoveDamage = 1;
                effect = ITEM_HP_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_ItemHurtRet;
                gLastUsedItem = gBattleMons[gBattlerAttacker].item;
            }
            break;
        case HOLD_EFFECT_THROAT_SPRAY:  // Does NOT need to be a damaging move
            if (gBattleMons[gBattlerAttacker].hp != 0
                && gBattleMoves[gCurrentMove].flags & FLAG_SOUND
                && CompareStat(gBattlerAttacker, STAT_SPATK, MAX_STAT_STAGE, CMP_LESS_THAN)
                && !NoAliveMonsForEitherParty()   // Don't activate if battle will end
                && !gProtectStructs[gBattlerAttacker].targetNotAffected)    //should be result not no effect
            {
                gLastUsedItem = atkItem;
                gBattleScripting.battler = gBattlerAttacker;
                gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                effect = ITEM_STATS_CHANGE;
                BattleScriptPushCursor();
                gBattlescriptCurrInstr = BattleScript_AttackerItemStatRaise;
            }
            break;
        }
        break;
    case ITEMEFFECT_TARGET:
        if (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
        {
            GET_MOVE_TYPE(gCurrentMove, moveType);
            switch (battlerHoldEffect)
            {
            case HOLD_EFFECT_AIR_BALLOON:
                if (TARGET_TURN_DAMAGED)
                {
                    effect = ITEM_EFFECT_OTHER;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_AirBaloonMsgPop;
                }
                break;
            case HOLD_EFFECT_ROCKY_HELMET:
                if (TARGET_TURN_DAMAGED
                    && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)
                    && IsBattlerAlive(gBattlerAttacker)
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 6;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_RockyHelmetActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battlerId, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_WEAKNESS_POLICY:
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && gMoveResultFlags & MOVE_RESULT_SUPER_EFFECTIVE)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_WeaknessPolicy;
                }
                break;
            case HOLD_EFFECT_SNOWBALL:
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && moveType == TYPE_ICE)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetItemStatRaise;
                    gBattleScripting.statChanger = SET_STATCHANGER(STAT_ATK, 1, FALSE);
                }
                break;
            case HOLD_EFFECT_LUMINOUS_MOSS:
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && moveType == TYPE_WATER)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetItemStatRaise;
                    gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPDEF, 1, FALSE);
                }
                break;
            case HOLD_EFFECT_CELL_BATTERY:
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && moveType == TYPE_ELECTRIC)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetItemStatRaise;
                    gBattleScripting.statChanger = SET_STATCHANGER(STAT_ATK, 1, FALSE);
                }
                break;
            case HOLD_EFFECT_ABSORB_BULB:
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && moveType == TYPE_WATER)
                {
                    effect = ITEM_STATS_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_TargetItemStatRaise;
                    gBattleScripting.statChanger = SET_STATCHANGER(STAT_SPATK, 1, FALSE);
                }
                break;
            case HOLD_EFFECT_JABOCA_BERRY:  // consume and damage attacker if used physical move
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && !DoesSubstituteBlockMove(gBattlerAttacker, battlerId, gCurrentMove)
                    && (IS_MOVE_PHYSICAL(gCurrentMove) || (IS_MOVE_SPECIAL(gCurrentMove) && GetBattlerAbility(gBattlerAttacker) == ABILITY_MUSCLE_MAGIC))
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;

                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_JabocaRowapBerryActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battlerId, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_ROWAP_BERRY:  // consume and damage attacker if used special move
                if (IsBattlerAlive(battlerId)
                    && TARGET_TURN_DAMAGED
                    && !DoesSubstituteBlockMove(gBattlerAttacker, battlerId, gCurrentMove)
                    && IS_MOVE_SPECIAL(gCurrentMove)
                    && GetBattlerAbility(gBattlerAttacker) != ABILITY_MAGIC_GUARD)
                {
                    gBattleMoveDamage = gBattleMons[gBattlerAttacker].maxHP / 8;
                    if (gBattleMoveDamage == 0)
                        gBattleMoveDamage = 1;
                    if (GetBattlerAbility(battlerId) == ABILITY_RIPEN)
                        gBattleMoveDamage *= 2;

                    effect = ITEM_HP_CHANGE;
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_JabocaRowapBerryActivates;
                    PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);
                    RecordItemEffectBattle(battlerId, HOLD_EFFECT_ROCKY_HELMET);
                }
                break;
            case HOLD_EFFECT_KEE_BERRY:  // consume and boost defense if used physical move
                effect = DamagedStatBoostBerryEffect(battlerId, STAT_DEF, SPLIT_PHYSICAL);
                break;
            case HOLD_EFFECT_MARANGA_BERRY:  // consume and boost sp. defense if used special move
                effect = DamagedStatBoostBerryEffect(battlerId, STAT_SPDEF, SPLIT_SPECIAL);
                break;
            case HOLD_EFFECT_STICKY_BARB:
                if (TARGET_TURN_DAMAGED
                    && (!(gMoveResultFlags & MOVE_RESULT_NO_EFFECT))
                    && IsMoveMakingContact(gCurrentMove, gBattlerAttacker)
                    && !DoesSubstituteBlockMove(gBattlerAttacker, battlerId, gCurrentMove)
                    && IsBattlerAlive(gBattlerAttacker)
                    //&& CanStealItem(gBattlerAttacker, gBattlerTarget, gBattleMons[gBattlerTarget].item) make it work on any item
                    && gBattleMons[gBattlerAttacker].item == ITEM_NONE)
                {
                    // No sticky hold checks.
                    gEffectBattler = battlerId; // gEffectBattler = target
                    StealTargetItem(gBattlerAttacker, gBattlerTarget);  // Attacker takes target's barb
                    BattleScriptPushCursor();
                    gBattlescriptCurrInstr = BattleScript_StickyBarbTransfer;
                    effect = ITEM_EFFECT_OTHER;
                }
                break;
            }
        }
        break;
    case ITEMEFFECT_ORBS:
    {
        u16 battlerAbility = GetBattlerAbility(battlerId);
        switch (battlerHoldEffect)
        {
        case HOLD_EFFECT_TOXIC_ORB:
            if (IsBattlerAlive(battlerId) && CanBePoisoned(battlerId, battlerId))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battlerId].status1 = STATUS1_TOXIC_POISON;
                BattleScriptExecute(BattleScript_ToxicOrb);
                RecordItemEffectBattle(battlerId, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_FLAME_ORB:
            if (IsBattlerAlive(battlerId) && CanBeBurned(battlerId))
            {
                effect = ITEM_STATUS_CHANGE;
                gBattleMons[battlerId].status1 = STATUS1_BURN;
                BattleScriptExecute(BattleScript_FlameOrb);
                RecordItemEffectBattle(battlerId, battlerHoldEffect);
            }
            break;
        case HOLD_EFFECT_STICKY_BARB:   // Not an orb per se, but similar effect, and needs to NOT activate with pickpocket
            if (battlerAbility != ABILITY_MAGIC_GUARD)
            {
                gBattleMoveDamage = gBattleMons[battlerId].maxHP / 8;   //according to bulbapedia stickybarb is not excluded from pickpocket, <it just activates after the barb exchagne
                if (gBattleMoveDamage == 0) //essentially taking it back.
                    gBattleMoveDamage = 1;
                BattleScriptExecute(BattleScript_ItemHurtEnd2);
                effect = ITEM_HP_CHANGE;
                RecordItemEffectBattle(battlerId, battlerHoldEffect);
                PREPARE_ITEM_BUFFER(gBattleTextBuff1, gLastUsedItem);//need test to ensure it triggers before abilty effect pickpocket
            }
            break;
        }

        if (effect == ITEM_STATUS_CHANGE)
        {
            gActiveBattler = battlerId;
            BtlController_EmitSetMonData(BUFFER_A, REQUEST_STATUS_BATTLE, 0, 4, &gBattleMons[battlerId].status1);
            MarkBattlerForControllerExec(gActiveBattler);
        }
    }
    break;
    }

    // Berry was successfully used on a Pokemon.
    if (effect && (gLastUsedItem >= FIRST_BERRY_INDEX && gLastUsedItem <= LAST_BERRY_INDEX))
        gBattleStruct->ateBerry[battlerId & BIT_SIDE] |= gBitTable[gBattlerPartyIndexes[battlerId]];

    return effect;
}

void ClearFuryCutterDestinyBondGrudge(u8 battlerId)
{
    gDisableStructs[battlerId].furyCutterCounter = 0;
    gBattleMons[battlerId].status2 &= ~(STATUS2_DESTINY_BOND);
    gStatuses3[battlerId] &= ~(STATUS3_GRUDGE);
}

void ResetFuryCutterCounter(u8 battlerId)
{
    gDisableStructs[battlerId].furyCutterCounter = 0;
}

void HandleAction_RunBattleScript(void) // identical to RunBattleScriptCommands
{
    if (!gBattleControllerExecFlags)
        gBattleScriptingCommandsTable[*gBattlescriptCurrInstr]();
}

bool32 IsAffectedByFollowMe(u32 battlerAtk, u32 defSide, u32 move)
{
    u32 ability = GetBattlerAbility(battlerAtk);

    if (gSideTimers[defSide].followmeTimer == 0
        || gBattleMons[gSideTimers[defSide].followmeTarget].hp == 0
        || gBattleMoves[move].effect == EFFECT_SNIPE_SHOT
        || gBattleMoves[move].effect == EFFECT_SKY_DROP
        || ability == ABILITY_PROPELLER_TAIL || ability == ABILITY_STALWART)
        return FALSE;

    if (gSideTimers[defSide].followmePowder)// && !IsAffectedByPowder(battlerAtk, ability, GetBattlerHoldEffect(battlerAtk, TRUE)))
        return FALSE; //function in ai update add back later

    return TRUE;
}

u32 SetRandomTarget(u32 battlerId)
{
    u32 target;
    static const u8 targets[2][2] =
    {
        [B_SIDE_PLAYER] = {B_POSITION_OPPONENT_LEFT, B_POSITION_OPPONENT_RIGHT},
        [B_SIDE_OPPONENT] = {B_POSITION_PLAYER_LEFT, B_POSITION_PLAYER_RIGHT},
    };

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerId)][Random() % 2]);
        if (!IsBattlerAlive(target))
            target ^= BIT_FLANK;
    }
    else
    {
        target = GetBattlerAtPosition(targets[GetBattlerSide(battlerId)][0]);
    }

    return target;
}

#define ABSORB_ABILITY_TARGETTING
u8 GetMoveTarget(u16 move, u8 setTarget) //maybe this is actually setting who gets attacked?
{
    u8 targetBattler = 0;
    u8 moveTarget;
    u8 side;

    if (setTarget != NO_TARGET_OVERRIDE)
        moveTarget = setTarget - 1;
    else
        moveTarget = GetBattlerMoveTargetType(gBattlerAttacker, move);

    // Special cases
    if (move == MOVE_CURSE && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_GHOST))
        moveTarget = MOVE_TARGET_USER;
    switch (moveTarget)
    {
    case MOVE_TARGET_SELECTED:
        side = BATTLE_OPPOSITE(GetBattlerSide(gBattlerAttacker));
        if (IsAffectedByFollowMe(gBattlerAttacker, side, move))
        {
            targetBattler = gSideTimers[side].followmeTarget;
        }
        else
        {
            /*side = GetBattlerSide(gBattlerAttacker);//since this makes it use target, guess I can just use atk cancler for that but with these conitions?
            do
            {
                targetBattler = Random() % gBattlersCount;  //think that would just make the battle string work, I still need to set status check her to prevent target swap
            } while (targetBattler == gBattlerAttacker || side == GetBattlerSide(targetBattler) || gAbsentBattlerFlags & gBitTable[targetBattler]);*/

            targetBattler = SetRandomTarget(gBattlerAttacker); //CHANGEd match emerald need test

            if (gBattleMoves[move].type == TYPE_ELECTRIC || gBattleMoves[move].argument == TYPE_ELECTRIC)   //if multiple absorb abilities think would trigger in order of top to bottom
            {

                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_LIGHTNING_ROD) //checks for ability, returns battlerId, think can use as battlreid to check if mon is statused?
                    && GetBattlerAbility(targetBattler) != ABILITY_LIGHTNING_ROD //means chosen target not lightning rod, since side has 2 mon, end goal is swap target to other mon with ability
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION)) //by that logic I believe using target battler for this is wrong vsonic
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_VOLT_ABSORB) //checks for ability, returns battlerId, think can use as battlreid to check if mon is statused?
                    && GetBattlerAbility(targetBattler) != ABILITY_VOLT_ABSORB
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_MOTOR_DRIVE) //checks for ability, returns battlerId, think can use as battlreid to check if mon is statused?
                    && GetBattlerAbility(targetBattler) != ABILITY_MOTOR_DRIVE
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION)) //should be not status 1 and not confused
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }

            }
            if (gBattleMoves[move].type == TYPE_WATER || gBattleMoves[move].argument == TYPE_WATER)
            {

                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_STORM_DRAIN) //checks for ability, returns battlerId, think can use as battlreid to check if mon is statused?
                    && GetBattlerAbility(targetBattler) != ABILITY_STORM_DRAIN    //if the selected target not an absorb ability, shift target to partner with said ability
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_WATER_ABSORB)//I THINK way this works, if I target absorb battler it'll trigger on them rather than swapping target
                    && GetBattlerAbility(targetBattler) != ABILITY_WATER_ABSORB
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_DRY_SKIN)
                    && GetBattlerAbility(targetBattler) != ABILITY_DRY_SKIN
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
            }
            if (gBattleMoves[move].type == TYPE_FIRE || gBattleMoves[move].argument == TYPE_FIRE)
            {

                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_FLASH_FIRE)
                    && GetBattlerAbility(targetBattler) != ABILITY_FLASH_FIRE
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_LAVA_FISSURE)
                    && GetBattlerAbility(targetBattler) != ABILITY_LAVA_FISSURE
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }

            }
            if (gBattleMoves[move].type == TYPE_ROCK || gBattleMoves[move].argument == TYPE_ROCK)
            {
                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_EROSION)
                    && GetBattlerAbility(targetBattler) != ABILITY_EROSION
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }
                else if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_JEWEL_METABOLISM)
                    && GetBattlerAbility(targetBattler) != ABILITY_JEWEL_METABOLISM
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }

            }
            if (gBattleMoves[move].type == TYPE_GRASS || gBattleMoves[move].argument == TYPE_GRASS)
            {
                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_SAP_SIPPER)
                    && GetBattlerAbility(targetBattler) != ABILITY_SAP_SIPPER
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }

            }
            if (gBattleMoves[move].type == TYPE_ICE || gBattleMoves[move].argument == TYPE_ICE)
            {
                if (IsAbilityOnOpposingSide(gBattlerAttacker, ABILITY_GLACIAL_ICE)
                    && GetBattlerAbility(targetBattler) != ABILITY_GLACIAL_ICE
                    && !(gBattleMons[targetBattler].status1 & STATUS1_ANY)
                    && !(gBattleMons[targetBattler].status2 & STATUS2_CONFUSION))
                {
                    targetBattler ^= BIT_FLANK; //sets target
                    RecordAbilityBattle(targetBattler, GetBattlerAbility(targetBattler));
                }

            }

        }
        break;
    case MOVE_TARGET_DEPENDS: //since realized I can set mullti targets using | 
    case MOVE_TARGET_BOTH: //I just need to add ally to this list
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

u32 GetBattlerHoldEffect(u8 battlerId, bool32 checkNegating)
{
    if (checkNegating)  //if equals 0, I think?
    {

        if (gSideStatuses[GET_BATTLER_SIDE(battlerId)] & SIDE_STATUS_EMBARGO)
            return HOLD_EFFECT_NONE;
        if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
            return HOLD_EFFECT_NONE;
        if (gBattleMons[battlerId].ability == ABILITY_KLUTZ && !(gStatuses3[battlerId] & STATUS3_GASTRO_ACID))
            return HOLD_EFFECT_NONE;
    }

    gPotentialItemEffectBattler = battlerId;

    /*if (B_ENABLE_DEBUG && gBattleStruct->debugHoldEffects[battlerId] != 0 && gBattleMons[battlerId].item)
        return gBattleStruct->debugHoldEffects[battlerId];
    else */if (gBattleMons[battlerId].item == ITEM_ENIGMA_BERRY)
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

bool8 IsMoveMakingContact(u16 move, u8 battlerAtk)
{
    if (!(gBattleMoves[move].flags & FLAG_MAKES_CONTACT))
        return FALSE;
    else if (GetBattlerAbility(battlerAtk) == ABILITY_LONG_REACH)
        return FALSE;
    else if (GetBattlerAbility(battlerAtk) == ABILITY_MUSCLE_MAGIC)
        return TRUE;
    else if (GetBattlerHoldEffect(battlerAtk, TRUE) == HOLD_EFFECT_PROTECTIVE_PADS)
        return FALSE;
    else
        return TRUE;
}

//understand why thsi is here now, later gen knock off fully remove the item held
//for effects that take advantage of the user not having an item.
//oh...nvm the item is restored at battle end...
//pretty sure I haven't set that up yet...
//if it does restore Item then I'd prob 
bool8 CanBattlerGetOrLoseItem(u8 battlerId, u16 itemId)//changed logic will only block knock off for items that patently change mons stats/form. logic being somethin that is consumed not something just on them
{
    u16 species = gBattleMons[battlerId].species;

    if (itemId == ITEM_ENIGMA_BERRY)
        return FALSE;
    else if (species == SPECIES_KYOGRE && itemId == ITEM_BLUE_ORB)
        return FALSE;
    else if (species == SPECIES_GROUDON && itemId == ITEM_RED_ORB)
        return FALSE;
    // Mega stone cannot be lost if pokemon can mega evolve with it or is already mega evolved.
    else if (ItemId_GetHoldEffect(itemId) == HOLD_EFFECT_MEGA_STONE)
        //&& ((GetMegaEvolutionSpecies(species, itemId) != SPECIES_NONE) || gBattleStruct->mega.evolvedPartyIds[GetBattlerSide(battlerId)] & gBitTable[gBattlerPartyIndexes[battlerId]]))
        return FALSE;
    /*else if (species == SPECIES_GIRATINA && itemId == ITEM_GRISEOUS_ORB)
        return FALSE;*/
    else if (species == SPECIES_GENESECT && GetBattlerHoldEffect(battlerId, FALSE) == HOLD_EFFECT_DRIVE)
        return TRUE;
    else if (species == SPECIES_SILVALLY && GetBattlerHoldEffect(battlerId, FALSE) == HOLD_EFFECT_MEMORY)
        return TRUE;
    else
        return TRUE;
}

struct Pokemon *GetIllusionMonPtr(u32 battlerId)
{
    if (gBattleStruct->illusion[battlerId].broken) //if illusion broken return null
        return NULL;
    if (!gBattleStruct->illusion[battlerId].set) //if illusion not set, set it
    {
        if (GetBattlerSide(battlerId) == B_SIDE_PLAYER)
            SetIllusionMon(&gPlayerParty[gBattlerPartyIndexes[battlerId]], battlerId);
        else
            SetIllusionMon(&gEnemyParty[gBattlerPartyIndexes[battlerId]], battlerId);
    }
    if (!gBattleStruct->illusion[battlerId].on) //if illusion not on return null?
        return NULL;

    return gBattleStruct->illusion[battlerId].mon;
}

void ClearIllusionMon(u32 battlerId)
{
    memset(&gBattleStruct->illusion[battlerId], 0, sizeof(gBattleStruct->illusion[battlerId]));
}

bool32 SetIllusionMon(struct Pokemon *mon, u32 battlerId)
{
    struct Pokemon *party, * partnerMon;
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

static bool32 IsNotEventLegalMewOrDeoxys(u8 battlerId) //fix to remove GF mew deoxys lock check
{
    if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT
        || (GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES, NULL) != SPECIES_DEOXYS
            && GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_SPECIES, NULL) != SPECIES_MEW))
        return TRUE;
    //return GetMonData(&gPlayerParty[gBattlerPartyIndexes[battlerId]], MON_DATA_EVENT_LEGAL, NULL);
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
    //if (gCurrentMove == MOVE_RAGE)//hmm didn't know about this effectively removes benefits of things
    //   gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RAGE);
    if (gBattleMons[gBattlerAttacker].status2 & STATUS2_RAGE)
        gBattleMons[gBattlerAttacker].status2 &= ~(STATUS2_RAGE);
    if (gBattleMons[gBattlerAttacker].status1 & STATUS1_SLEEP && (gCurrentMove == MOVE_SNORE || gCurrentMove == MOVE_SLEEP_TALK))
    {
        gBattlescriptCurrInstr = BattleScript_IgnoresWhileAsleep;
        return 1;
    }
    rnd = (Random() & 255);
    calc = (gBattleMons[gBattlerAttacker].level + obedienceLevel) * rnd >> 8;
    if (calc < obedienceLevel) // Additional check for focus punch in FR    //removed focus punch check
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
            gHitMarker |= HITMARKER_DISOBEDIENT_MOVE;
            return 2;
        }
    }
    else
    {
        obedienceLevel = gBattleMons[gBattlerAttacker].level - obedienceLevel;
        calc = (Random() & 255);
        if (calc < obedienceLevel && !(gBattleMons[gBattlerAttacker].status1 & STATUS1_ANY) && GetBattlerAbility(gBattlerAttacker) != ABILITY_VITAL_SPIRIT && GetBattlerAbility(gBattlerAttacker) != ABILITY_INSOMNIA)
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

bool32 IsNeutralizingGasBannedAbility(u32 ability)
{
    switch (ability)
    {
    case ABILITY_MULTITYPE:
    case ABILITY_ZEN_MODE:
    case ABILITY_STANCE_CHANGE:
    case ABILITY_POWER_CONSTRUCT:
    case ABILITY_SCHOOLING:
    case ABILITY_RKS_SYSTEM:
    case ABILITY_SHIELDS_DOWN:
    case ABILITY_COMATOSE:
    case ABILITY_DISGUISE:
    case ABILITY_GULP_MISSILE:
    case ABILITY_ICE_FACE:
    case ABILITY_AS_ONE_ICE_RIDER:
    case ABILITY_AS_ONE_SHADOW_RIDER:
        return TRUE;
    default:
        return FALSE;
    }
} //abilities excluded  from neutralizing gas, as they are intrinsic to the pokemon biology/unique to themselves/involves changing their body.


bool32 IsNeutralizingGasOnField(void)   //not used anymore, but still here if want to use default implementation //is not global as only used here.
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        //if (IsBattlerAlive(i) && GetBattlerSide(i) != side && gBattleMons[i].ability == ABILITY_NEUTRALIZING_GAS && !(gStatuses3[i] & STATUS3_GASTRO_ACID))
        if (IsBattlerAlive(i) && gBattleMons[i].ability == ABILITY_NEUTRALIZING_GAS && !(gStatuses3[i] & STATUS3_GASTRO_ACID))  //original code 
        //if (IsAbilityOnOpposingSide(i, ABILITY_NEUTRALIZING_GAS) && !(gStatuses3[i] & STATUS3_GASTRO_ACID))
            return TRUE;
    } //added side statement, should make it only remove ability if neutralzing gas is on other side,
    //change how the ability is used a bit ,but I'm fixing bad abilities anyway so it shouldn't be used to remove bad abiliites.
    return FALSE;
}

bool8 IsBlackFogNotOnField(void)
{
    if (!(gFieldStatuses & STATUS_FIELD_BLACK_FOG))
        return TRUE;
    else if (gFieldStatuses & STATUS_FIELD_BLACK_FOG)
        return FALSE;
}

u32 GetBattlerAbility(u8 battlerId)  //Deokishishu in pret mentioned there is a practice of making things that could
 // be type u8 either s32 or u32, because it has an positive effect on speed, ussually done for things 
 //constantly refernced or looped.
{
    if (gStatuses3[battlerId] & STATUS3_GASTRO_ACID) //only added this, because focusing abilities should work
        return ABILITY_NONE;
    //if (IsNeutralizingGasOnField() && !IsNeutralizingGasBannedAbility(gBattleMons[battlerId].ability))
    if (DoesSideHaveAbility(BATTLE_OPPOSITE(battlerId), ABILITY_NEUTRALIZING_GAS) && !IsNeutralizingGasBannedAbility(gBattleMons[battlerId].ability))
        return ABILITY_NONE;//I don't need to subtract 1 from Id because my function isn't doing anything with the id returned by the function
    if ((((gBattleMons[gBattlerAttacker].ability == ABILITY_MOLD_BREAKER
        || gBattleMons[gBattlerAttacker].ability == ABILITY_TERAVOLT
        || gBattleMons[gBattlerAttacker].ability == ABILITY_TURBOBLAZE)
        && !(gStatuses3[gBattlerAttacker] & STATUS3_GASTRO_ACID))
        || gBattleMoves[gCurrentMove].flags & FLAG_TARGET_ABILITY_IGNORED)
        && sAbilitiesAffectedByMoldBreaker[gBattleMons[battlerId].ability]
        && gBattlerByTurnOrder[gCurrentTurnActionNumber] == gBattlerAttacker
        && gActionsByTurnOrder[gBattlerByTurnOrder[gBattlerAttacker]] == B_ACTION_USE_MOVE
        && gCurrentTurnActionNumber < gBattlersCount)
        return ABILITY_NONE;

    return gBattleMons[battlerId].ability;
}

bool8 IsBattlerAlive(u8 battlerId)
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

u32 IsAbilityOnSide(u32 battlerId, u32 ability)
{
    if (IsBattlerAlive(battlerId) && GetBattlerAbility(battlerId) == ability)
        return battlerId + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && GetBattlerAbility(BATTLE_PARTNER(battlerId)) == ability)
        return BATTLE_PARTNER(battlerId) + 1;
    else
        return 0;
}

u32 DoesSideHaveAbility(u32 battlerId, u32 ability) //adapted ability search function that doesn't use getbattlerability
{
    if (IsBattlerAlive(battlerId) && gBattleMons[battlerId].ability == ability && !(gStatuses3[battlerId] & STATUS3_GASTRO_ACID))
        return battlerId + 1;
    else if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && gBattleMons[BATTLE_PARTNER(battlerId)].ability == ability && !(gStatuses3[BATTLE_PARTNER(battlerId)] & STATUS3_GASTRO_ACID))
        return BATTLE_PARTNER(battlerId) + 1;
    else
        return 0;
}//realized needed to add back in gastro acid check

u32 IsAbilityOnOpposingSide(u32 battlerId, u32 ability) // use for intimidate on enemy team
{
    return IsAbilityOnSide(BATTLE_OPPOSITE(battlerId), ability);
}

//can be used as true false, but also can be used to return battler with ability in question
//todo that use battler = function - 1;  as seen with damp in abilitybattleeffects
u32 IsAbilityOnField(u32 ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityOnFieldExcept(u32 battlerId, u32 ability)
{
    u32 i;

    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != battlerId && IsBattlerAlive(i) && GetBattlerAbility(i) == ability)
            return i + 1;
    }

    return 0;
}

u32 IsAbilityPreventingEscape(u32 battlerId) //ported for ai, equivalent logic in battle main.c is runnign from battle impossible, /-had to retool function logic it gave me compiler issues
{
    u32 id = 0; //note for ghost escape make ghosts escape traps, and arena trap but not most other abilities, the whole heirarchy thing they beat moves, but not abilities
    //they only beat arena trap because levitate beats that, and most ghosts would have levitate

    if ((GetBattlerAbility(battlerId) == ABILITY_DEFEATIST
        && gSpecialStatuses[battlerId].defeatistActivated) //overwrite usual switch preveention from status & traps
        || (GetBattlerAbility(battlerId) == ABILITY_RUN_AWAY)
        || (GetBattlerAbility(battlerId) == ABILITY_AVIATOR))
        return FALSE;

    if (IsBattlerGrounded(battlerId))
        id = IsAbilityOnOpposingSide(battlerId, ABILITY_ARENA_TRAP);

    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_STEEL))
        id = IsAbilityOnOpposingSide(battlerId, ABILITY_MAGNET_PULL);

    if (IsBattlerAlive(BATTLE_OPPOSITE(battlerId)))
        id = IsAbilityOnOpposingSide(battlerId, ABILITY_SHADOW_TAG);

    /*if (id = IsAbilityOnOpposingSide(battlerId, ABILITY_SHADOW_TAG))
        return id;
    if ((id = IsAbilityOnOpposingSide(battlerId, ABILITY_ARENA_TRAP)) && IsBattlerGrounded(battlerId))
        return id;
    if ((id = IsAbilityOnOpposingSide(battlerId, ABILITY_MAGNET_PULL)) && IS_BATTLER_OF_TYPE(battlerId, TYPE_STEEL))
        return id;*/

    return id;
}

u32 GetBattlerWeight(u8 battlerId) //use ethis for calculating  seismic toss damage change
{ //since way I plan to make damage formula may make it too strong at early levels
    //I may need to do an extra level scale component, just to mitigate damage at game start
    //where hp is low.  like say if lvl is less than or equal to 10, gbattlemovedamage *= 2/3
    //so the move will do a third less than the damage calculated from the forumla
    //can also think of it like they have to grow before they can utilize the full power ofthe move
    // 
    //change plan have the weight component be added to normal move damage, 
    //and level scalar can just be there to ensure it scales into late game,
    //pretty much formula will be (normal seismic dmg aka gbattlemovedmg) + (lvl multiplier [0 at lower levels]  * formula for weight-based dmg)
    u32 i;
    u32 weight = GetPokedexHeightWeight(SpeciesToNationalPokedexNum(gBattleMons[battlerId].species), 1);    //weight measured in kilo grams 69 = 6.9 kg -bulbasaur
    u32 ability = GetBattlerAbility(battlerId);
    u32 holdEffect = GetBattlerHoldEffect(battlerId, TRUE);

    //weight goes up to around 999 kg  average weight is 50kg so 500 weight

    if (ability == ABILITY_HEAVY_METAL)
        weight *= 2;
    else if (ability == ABILITY_LIGHT_METAL
        || ability == ABILITY_LIQUID_METAL)
        weight /= 2;

    if (holdEffect == HOLD_EFFECT_FLOAT_STONE)
        weight /= 2;

    for (i = 0; i < gDisableStructs[battlerId].autotomizeCount; i++)
    {
        if (weight > 1000)
        {
            weight -= 1000;
        }
        else if (weight <= 1000)
        {
            weight = 1;
            break;
        }
    }

    if (weight == 0)
        weight = 1;

    return weight;
}

static bool32 IsPartnerMonFromSameTrainer(u8 battlerId)
{
    if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT && gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS) // replaced flag after ingamepartner
        return FALSE;
    else if (GetBattlerSide(battlerId) == B_SIDE_PLAYER && gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        return FALSE;
    else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
        return FALSE;
    else
        return TRUE;
}

u16 GetPrimalReversionSpecies(u16 preEvoSpecies, u16 heldItemId)
{
    u32 i;

    for (i = 0; i < EVOS_PER_MON; i++)
    {
        if (gEvolutionTable[preEvoSpecies][i].method == EVO_PRIMAL_REVERSION
            && gEvolutionTable[preEvoSpecies][i].param == heldItemId)
            return gEvolutionTable[preEvoSpecies][i].targetSpecies;
    }
    return SPECIES_NONE;
}

u16 GetMegaEvolutionSpecies(u16 preEvoSpecies, u16 heldItemId)
{
    u32 i;

    for (i = 0; i < EVOS_PER_MON; i++)
    {
        if (gEvolutionTable[preEvoSpecies][i].method == EVO_MEGA_EVOLUTION
            && gEvolutionTable[preEvoSpecies][i].param == heldItemId)
            return gEvolutionTable[preEvoSpecies][i].targetSpecies;
    }
    return SPECIES_NONE;
}

u16 GetWishMegaEvolutionSpecies(u16 preEvoSpecies, u16 moveId1, u16 moveId2, u16 moveId3, u16 moveId4)
{
    u32 i, par;

    for (i = 0; i < EVOS_PER_MON; i++)
    {
        if (gEvolutionTable[preEvoSpecies][i].method == EVO_MOVE_MEGA_EVOLUTION)
        {
            par = gEvolutionTable[preEvoSpecies][i].param;
            if (par == moveId1 || par == moveId2 || par == moveId3 || par == moveId4)
                return gEvolutionTable[preEvoSpecies][i].targetSpecies;
        }
    }
    return SPECIES_NONE;
}

bool32 CanMegaEvolve(u8 battlerId)
{
    u32 itemId, holdEffect, species;
    struct Pokemon *mon;
    u8 battlerPosition = GetBattlerPosition(battlerId);
    u8 partnerPosition = GetBattlerPosition(BATTLE_PARTNER(battlerId));
    struct MegaEvolutionData *mega = &(((struct ChooseMoveStruct*)(&gBattleResources->bufferA[gActiveBattler][4]))->mega);
    /*
    #ifdef ITEM_EXPANSION
        // Check if Player has a Mega Bracelet
        if ((GetBattlerPosition(battlerId) == B_POSITION_PLAYER_LEFT || (!(gBattleTypeFlags & BATTLE_TYPE_MULTI) && GetBattlerPosition(battlerId) == B_POSITION_PLAYER_RIGHT))
         && !CheckBagHasItem(ITEM_MEGA_BRACELET, 1))
            return FALSE;
    #endif*/

    // Check if trainer already mega evolved a pokemon.
    if (mega->alreadyEvolved[battlerPosition])
        return FALSE;
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        if (IsPartnerMonFromSameTrainer(battlerId)
            && (mega->alreadyEvolved[partnerPosition] || (mega->toEvolve & gBitTable[BATTLE_PARTNER(battlerId)])))
            return FALSE;
    }

    // Gets mon data.
    if (GetBattlerSide(battlerId) == B_SIDE_OPPONENT)
        mon = &gEnemyParty[gBattlerPartyIndexes[battlerId]];
    else
        mon = &gPlayerParty[gBattlerPartyIndexes[battlerId]];

    species = GetMonData(mon, MON_DATA_SPECIES);
    itemId = GetMonData(mon, MON_DATA_HELD_ITEM);

    // Check if there is an entry in the evolution table for regular Mega Evolution.
    if (GetMegaEvolutionSpecies(species, itemId) != SPECIES_NONE)
    {
        if (itemId == ITEM_ENIGMA_BERRY)
            holdEffect = gEnigmaBerries[battlerId].holdEffect;
        else
            holdEffect = ItemId_GetHoldEffect(itemId);

        // Can Mega Evolve via Item.
        if (holdEffect == HOLD_EFFECT_MEGA_STONE)
        {
            gBattleStruct->mega.isWishMegaEvo = FALSE;
            return TRUE;
        }
    }

    // Check if there is an entry in the evolution table for Wish Mega Evolution.
    if (GetWishMegaEvolutionSpecies(species, GetMonData(mon, MON_DATA_MOVE1), GetMonData(mon, MON_DATA_MOVE2), GetMonData(mon, MON_DATA_MOVE3), GetMonData(mon, MON_DATA_MOVE4)))
    {
        gBattleStruct->mega.isWishMegaEvo = TRUE;
        return TRUE;
    }

    // No checks passed, the mon CAN'T mega evolve.
    return FALSE;
}

/*void UndoMegaEvolution(u32 monId)
{
    if (gBattleStruct->mega.evolvedPartyIds[B_SIDE_PLAYER] & gBitTable[monId])
    {
        gBattleStruct->mega.evolvedPartyIds[B_SIDE_PLAYER] &= ~(gBitTable[monId]);
        SetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, &gBattleStruct->mega.playerEvolvedSpecies);
        CalculateMonStats(&gPlayerParty[monId]);
    }
    // While not exactly a mega evolution, Zygarde follows the same rules.
    else if (GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, NULL) == SPECIES_ZYGARDE_COMPLETE)
    {
        SetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, &gBattleStruct->changedSpecies[monId]);
        gBattleStruct->changedSpecies[monId] = 0;
        CalculateMonStats(&gPlayerParty[monId]);
    }
}*/  //I guess this was an older port?

void UndoMegaEvolution(u32 monId)
{
    u16 baseSpecies = GET_BASE_SPECIES_ID(GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES));

    if (gBattleStruct->mega.evolvedPartyIds[B_SIDE_PLAYER] & gBitTable[monId])
    {
        gBattleStruct->mega.evolvedPartyIds[B_SIDE_PLAYER] &= ~(gBitTable[monId]);
        SetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, &gBattleStruct->mega.playerEvolvedSpecies);
        CalculateMonStats(&gPlayerParty[monId]);
    }
    else if (gBattleStruct->mega.primalRevertedPartyIds[B_SIDE_PLAYER] & gBitTable[monId])
    {
        gBattleStruct->mega.primalRevertedPartyIds[B_SIDE_PLAYER] &= ~(gBitTable[monId]);
        SetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, &baseSpecies);
        CalculateMonStats(&gPlayerParty[monId]);
    }
    // While not exactly a mega evolution, Zygarde follows the same rules.
    else if (GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, NULL) == SPECIES_ZYGARDE_COMPLETE)
    {
        SetMonData(&gPlayerParty[monId], MON_DATA_SPECIES, &gBattleStruct->changedSpecies[monId]);
        gBattleStruct->changedSpecies[monId] = 0;
        CalculateMonStats(&gPlayerParty[monId]);
    }

}

bool32 IsBattlerAffectedByHazards(u8 battlerId, bool32 toxicSpikes)
{
    bool32 ret = TRUE;
    u32 holdEffect = GetBattlerHoldEffect(gActiveBattler, TRUE);
    if (toxicSpikes && holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS && !IS_BATTLER_OF_TYPE(battlerId, TYPE_POISON))
    {
        ret = FALSE;
        RecordItemEffectBattle(battlerId, holdEffect);
    }
    else if (holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS)
    {
        ret = FALSE;
        RecordItemEffectBattle(battlerId, holdEffect);
    }
    return ret;
}

bool32 TestSheerForceFlag(u8 battler, u16 move)
{
    if (GetBattlerAbility(battler) == ABILITY_SHEER_FORCE && gBattleMoves[move].flags & FLAG_SHEER_FORCE_BOOST)
        return TRUE;
    else
        return FALSE;
}

void UndoFormChange(u32 monId, u32 side, bool32 isSwitchingOut)
{
    u32 i, currSpecies, targetSpecies;
    struct Pokemon *party = (side == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;
    static const u16 species[][3] =
    {
        // Changed Form ID                      Default Form ID               Should change on switch
        {SPECIES_EISCUE_NOICE_FACE,             SPECIES_EISCUE,               TRUE},
        {SPECIES_MIMIKYU_BUSTED,                SPECIES_MIMIKYU,              FALSE},
        {SPECIES_GRENINJA_ASH,                  SPECIES_GRENINJA_BATTLE_BOND, FALSE},
        {SPECIES_MELOETTA_PIROUETTE,            SPECIES_MELOETTA,             FALSE},
        {SPECIES_AEGISLASH_BLADE,               SPECIES_AEGISLASH,            TRUE},
        {SPECIES_DARMANITAN_ZEN_MODE,           SPECIES_DARMANITAN,           TRUE},
        {SPECIES_MINIOR,                        SPECIES_MINIOR_CORE_RED,      TRUE},
        {SPECIES_MINIOR_METEOR_BLUE,            SPECIES_MINIOR_CORE_BLUE,     TRUE},
        {SPECIES_MINIOR_METEOR_GREEN,           SPECIES_MINIOR_CORE_GREEN,    TRUE},
        {SPECIES_MINIOR_METEOR_INDIGO,          SPECIES_MINIOR_CORE_INDIGO,   TRUE},
        {SPECIES_MINIOR_METEOR_ORANGE,          SPECIES_MINIOR_CORE_ORANGE,   TRUE},
        {SPECIES_MINIOR_METEOR_VIOLET,          SPECIES_MINIOR_CORE_VIOLET,   TRUE},
        {SPECIES_MINIOR_METEOR_YELLOW,          SPECIES_MINIOR_CORE_YELLOW,   TRUE},
        {SPECIES_WISHIWASHI_SCHOOL,             SPECIES_WISHIWASHI,           TRUE},
        {SPECIES_CRAMORANT_GORGING,             SPECIES_CRAMORANT,            TRUE},
        {SPECIES_CRAMORANT_GULPING,             SPECIES_CRAMORANT,            TRUE},
        {SPECIES_MORPEKO_HANGRY,                SPECIES_MORPEKO,              TRUE},
        {SPECIES_DARMANITAN_ZEN_MODE_GALARIAN,  SPECIES_DARMANITAN_GALARIAN,  TRUE},
    };

    currSpecies = GetMonData(&party[monId], MON_DATA_SPECIES, NULL);
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        if (currSpecies == species[i][0] && (!isSwitchingOut || species[i][2] == TRUE))
        {
            SetMonData(&party[monId], MON_DATA_SPECIES, &species[i][1]);
            CalculateMonStats(&party[monId]);
            break;
        }
    }
    /*if (!isSwitchingOut)
    {
        targetSpecies = GetFormChangeTargetSpecies(&party[monId], FORM_BATTLE_END, 0);
        if (targetSpecies != SPECIES_NONE)
        {
            SetMonData(&party[monId], MON_DATA_SPECIES, &targetSpecies);
            CalculateMonStats(&party[monId]);
            TryToSetBattleFormChangeMoves(&party[monId]);
        }
    }*/
}

/*void UndoFormChange(u32 monId, u32 side, bool32 isSwitchingOut)
{
    u32 i, currSpecies, targetSpecies;
    struct Pokemon* party = (side == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;
    static const u16 species[][3] =
    {
        // Changed Form ID                      Default Form ID               Should change on switch
        {SPECIES_EISCUE_NOICE_FACE,             SPECIES_EISCUE,               TRUE},
        {SPECIES_MIMIKYU_BUSTED,                SPECIES_MIMIKYU,              FALSE},
        {SPECIES_GRENINJA_ASH,                  SPECIES_GRENINJA_BATTLE_BOND, FALSE},
        {SPECIES_MELOETTA_PIROUETTE,            SPECIES_MELOETTA,             FALSE},
        {SPECIES_AEGISLASH_BLADE,               SPECIES_AEGISLASH,            TRUE},
        {SPECIES_DARMANITAN_ZEN_MODE,           SPECIES_DARMANITAN,           TRUE},
        {SPECIES_MINIOR,                        SPECIES_MINIOR_CORE_RED,      TRUE},
        {SPECIES_MINIOR_METEOR_BLUE,            SPECIES_MINIOR_CORE_BLUE,     TRUE},
        {SPECIES_MINIOR_METEOR_GREEN,           SPECIES_MINIOR_CORE_GREEN,    TRUE},
        {SPECIES_MINIOR_METEOR_INDIGO,          SPECIES_MINIOR_CORE_INDIGO,   TRUE},
        {SPECIES_MINIOR_METEOR_ORANGE,          SPECIES_MINIOR_CORE_ORANGE,   TRUE},
        {SPECIES_MINIOR_METEOR_VIOLET,          SPECIES_MINIOR_CORE_VIOLET,   TRUE},
        {SPECIES_MINIOR_METEOR_YELLOW,          SPECIES_MINIOR_CORE_YELLOW,   TRUE},
        {SPECIES_WISHIWASHI_SCHOOL,             SPECIES_WISHIWASHI,           TRUE},
        {SPECIES_CRAMORANT_GORGING,             SPECIES_CRAMORANT,            TRUE},
        {SPECIES_CRAMORANT_GULPING,             SPECIES_CRAMORANT,            TRUE},
        {SPECIES_MORPEKO_HANGRY,                SPECIES_MORPEKO,              TRUE},
        {SPECIES_DARMANITAN_ZEN_MODE_GALARIAN,  SPECIES_DARMANITAN_GALARIAN,  TRUE},
    };

    currSpecies = GetMonData(&party[monId], MON_DATA_SPECIES, NULL);
    for (i = 0; i < ARRAY_COUNT(species); i++)
    {
        if (currSpecies == species[i][0] && (!isSwitchingOut || species[i][2] == TRUE))
        {
            SetMonData(&party[monId], MON_DATA_SPECIES, &species[i][1]);
            CalculateMonStats(&party[monId]);
            break;
        }
    }
    if (!isSwitchingOut)
    {
        targetSpecies = GetFormChangeTargetSpecies(&party[monId], FORM_BATTLE_END, 0);
        if (targetSpecies != SPECIES_NONE)
        {
            SetMonData(&party[monId], MON_DATA_SPECIES, &targetSpecies);
            CalculateMonStats(&party[monId]);
            TryToSetBattleFormChangeMoves(&party[monId]);
        }
    }
}*/

//format for use is MulModifier(&modifier, UQ_4_12(1.55));   & is used to denote pointer here
//all functions that use modifier start with u16 modifier = UQ_4_12(1.0); so it defaults to 1, and is modulated from there
void MulModifier(u16 *modifier, u16 val) //portd tried to set globably hope works   //can use decimal values
{
    *modifier = UQ_4_12_TO_INT((*modifier * val) + UQ_4_12_ROUND);
}

u32 ApplyModifier(u16 modifier, u32 val)
{
    return UQ_4_12_TO_INT((modifier * val) + UQ_4_12_ROUND);
}

//attempt porting type multipliers from emerald to more easily add type check to forewarn & anticipate also 
static u16 GetInverseTypeMultiplier(u16 multiplier) //could use total damgae calc function from emerald ported below, but type multiplier check * power should be enough
{
    switch (multiplier)
    {
    case UQ_4_12(0.0):
        return UQ_4_12(1.0);
    case UQ_4_12(0.5):
        return UQ_4_12(1.55);
    case UQ_4_12(1.55):
        return UQ_4_12(0.5);
    case UQ_4_12(1.0):
    default:
        return UQ_4_12(0.0);
    }
}

static void MulByTypeEffectiveness(u16 *modifier, u16 move, u8 moveType, u8 battlerDef, u8 defType, u8 battlerAtk, bool32 recordAbilities)
{
    u16 mod = GetTypeModifier(moveType, defType);

    if (mod == UQ_4_12(0.0) && GetBattlerHoldEffect(battlerDef, TRUE) == HOLD_EFFECT_RING_TARGET)//why would anyone want this?
    {
        mod = UQ_4_12(1.0);
        /*if (recordAbilities)
            RecordItemEffectBattle(battlerDef, HOLD_EFFECT_RING_TARGET);*/
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
    }
    else if ((moveType == TYPE_FIGHTING || moveType == TYPE_NORMAL) && defType == TYPE_GHOST && GetBattlerAbility(battlerAtk) == ABILITY_SCRAPPY && mod == UQ_4_12(0.0))
    {
        mod = UQ_4_12(1.0);
        /*if (recordAbilities)
            RecordAbilityBattle(battlerAtk, ABILITY_SCRAPPY);*/
    }
    else if (GetBattlerAbility(battlerAtk) == ABILITY_NORMALIZE)
    {
        mod = UQ_4_12(1.0);
    }
    else if (GetBattlerAbility(battlerAtk) == ABILITY_INVERSE_WORLD)
    {
        if (mod == UQ_4_12(0.0))
            mod = UQ_4_12(1.0);

        else if (mod == UQ_4_12(0.5))
            mod = UQ_4_12(1.55);

        else if (mod == UQ_4_12(1.55))
            mod = UQ_4_12(0.5);
    }
    else if ((moveType == TYPE_ICE) && GetBattlerAbility(battlerDef) == ABILITY_ECOSYSTEM && defType == TYPE_GRASS && mod == UQ_4_12(1.55))
    {
        mod = UQ_4_12(1.0); //for purose of this being only on mega torterra deftype would be grass
    }
    else if ((moveType == TYPE_ICE) && GetBattlerAbility(battlerDef) == ABILITY_ABSOLUTE_ZERO && defType == TYPE_DRAGON && mod == UQ_4_12(1.55))
    {
        mod = UQ_4_12(0.5); //Because only on kyurem deftype would be dragon
    }

    if (moveType == TYPE_PSYCHIC && defType == TYPE_DARK && gStatuses3[battlerDef] & STATUS3_MIRACLE_EYED && mod == UQ_4_12(0.0))
        mod = UQ_4_12(1.0);
    if (gBattleMoves[move].effect == EFFECT_FREEZE_DRY && defType == TYPE_WATER)
        mod = UQ_4_12(1.55);
    //if (moveType == TYPE_GROUND && defType == TYPE_FLYING && IsBattlerGrounded(battlerDef) && mod == UQ_4_12(0.0))
    //    mod = UQ_4_12(1.0);//think I can completely remove this, as I already changed tyep thing and this is after accuracy check?
    if (moveType == TYPE_FIRE && gDisableStructs[battlerDef].tarShot)
        mod = UQ_4_12(1.55);

    // B_WEATHER_STRONG_WINDS weakens Super Effective moves against Flying-type Pok�mon
    if (gBattleWeather & WEATHER_STRONG_WINDS && WEATHER_HAS_EFFECT)
    {
        if (defType == TYPE_FLYING && mod >= UQ_4_12(1.55))
            mod = UQ_4_12(1.0);
    }

    MulModifier(modifier, mod);
}

u16 GetTypeModifier(u8 atkType, u8 defType)
{

    if (FlagGet(FLAG_INVERSE_BATTLE) || GetBattlerAbility(gBattlerTarget) == ABILITY_INVERSE_WORLD) //or target mon has invers world ability i.e giratina origin
        return GetInverseTypeMultiplier(gTypeEffectivenessTable[atkType][defType]);

    return gTypeEffectivenessTable[atkType][defType];

}

u16 CalcTypeEffectivenessMultiplier(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities)
{
    u16 modifier = UQ_4_12(1.0);

    if (move != MOVE_STRUGGLE && moveType != TYPE_MYSTERY) //skips type calculation as both are meant to do typeless dmg i.e neutral to all
    {
        modifier = CalcTypeEffectivenessMultiplierInternal(move, moveType, battlerAtk, battlerDef, recordAbilities, modifier);
        if (gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE)
            modifier = CalcTypeEffectivenessMultiplierInternal(move, gBattleMoves[move].argument, battlerAtk, battlerDef, recordAbilities, modifier);
    }

    if (recordAbilities)
        UpdateMoveResultFlags(modifier);
    return modifier;
}

//used to repalce CheckWonderGuardAndLevitate, to remove reliance on gamefreak's stupid janky type loop foresight logic
//no longer need type foresight, or to ensure type relations go above it
static u16 CalcTypeEffectivenessMultiplierInternal(u16 move, u8 moveType, u8 battlerAtk, u8 battlerDef, bool32 recordAbilities, u16 modifier)
{
    u16 defAbility = GetBattlerAbility(battlerDef);

    MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type1, battlerAtk, recordAbilities);
    if (gBattleMons[battlerDef].type2 != gBattleMons[battlerDef].type1)
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type2, battlerAtk, recordAbilities);
    if (gBattleMons[battlerDef].type3 != TYPE_MYSTERY && gBattleMons[battlerDef].type3 != gBattleMons[battlerDef].type2
        && gBattleMons[battlerDef].type3 != gBattleMons[battlerDef].type1)
        MulByTypeEffectiveness(&modifier, move, moveType, battlerDef, gBattleMons[battlerDef].type3, battlerAtk, recordAbilities);

    /*if (gBattleMoves[move].split == SPLIT_STATUS)// ??  with change to status stuff think need rmeove this
    {
        modifier = UQ_4_12(1.0);

        if (move == MOVE_GLARE && IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST)) //can keep this line
        {
            modifier = UQ_4_12(0.0);
        }

    }*/
    if (move == MOVE_GLARE && IS_BATTLER_OF_TYPE(battlerDef, TYPE_GHOST)) //can keep this line
    {
        modifier = UQ_4_12(0.0);
    }
    else if ((moveType == TYPE_GROUND) && !IsBattlerGrounded(battlerDef) && !(gBattleMoves[move].flags & FLAG_DMG_IN_AIR))
    {
        modifier = UQ_4_12(0.0);
        /*if (recordAbilities && defAbility == ABILITY_LEVITATE)
        {
            gLastUsedAbility = ABILITY_LEVITATE;
            gMoveResultFlags |= (MOVE_RESULT_MISSED | MOVE_RESULT_DOESNT_AFFECT_FOE);
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_GROUND_MISS;
            RecordAbilityBattle(battlerDef, ABILITY_LEVITATE);
        } */  //potentially add back later.
    }

    else if ((move == MOVE_SHEER_COLD) && IS_BATTLER_OF_TYPE(battlerDef, TYPE_ICE))
    {
        modifier = UQ_4_12(0.0);
    }


    // Thousand Arrows ignores type modifiers for flying mons
   /* if (!IsBattlerGrounded(battlerDef) && (gBattleMoves[move].flags & FLAG_DMG_UNGROUNDED_IGNORE_TYPE_IF_FLYING)
        && (gBattleMons[battlerDef].type1 == TYPE_FLYING || gBattleMons[battlerDef].type2 == TYPE_FLYING || gBattleMons[battlerDef].type3 == TYPE_FLYING))
    {
        modifier = UQ_4_12(1.0);
    }*///since normal multiplie is now 1, I can actually just remove this entirely and have it read the chart normally

    if (((defAbility == ABILITY_WONDER_GUARD && modifier <= UQ_4_12(1.0))
        || (defAbility == ABILITY_TELEPATHY && battlerDef == BATTLE_PARTNER(battlerAtk))
        || (defAbility == ABILITY_DISPIRIT_GUARD && modifier >= UQ_4_12(1.0))
        || (defAbility == ABILITY_LIQUID_SOUL && moveType == TYPE_WATER)
        )
        && gBattleMoves[move].power)
    {
        modifier = UQ_4_12(0.0);
        if (recordAbilities)
        {
            gLastUsedAbility = gBattleMons[battlerDef].ability;
            gMoveResultFlags |= MOVE_RESULT_MISSED;
            gLastLandedMoves[battlerDef] = 0;
            gBattleCommunication[MISS_TYPE] = B_MSG_AVOIDED_DMG;
            RecordAbilityBattle(battlerDef, gBattleMons[battlerDef].ability);
        }
    }

    return modifier;
}

static void UpdateMoveResultFlags(u16 modifier)
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

// for AI - get move damage and effectiveness with one function call
s32 CalculateMoveDamageAndEffectiveness(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, u16 *typeEffectivenessModifier)
{
    *typeEffectivenessModifier = CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, FALSE);
    return DoMoveDamageCalc(move, battlerAtk, battlerDef, moveType, 0, FALSE, FALSE, FALSE, *typeEffectivenessModifier);
}

s32 DoMoveDamageCalc(u16 move, u8 battlerAtk, u8 battlerDef, u8 moveType, s32 fixedBasePower,
    bool32 isCrit, bool32 randomFactor, bool32 updateFlags, u16 typeEffectivenessModifier)
{
    s32 dmg;

    // Don't calculate damage if the move has no effect on target.
    if (typeEffectivenessModifier == UQ_4_12(0))
        return 0;

    if (fixedBasePower)
        gBattleMovePower = fixedBasePower;// don't want to but will need to fill this out, effectively copy all the dmg modifier stuff from CalculateBaseDamage but just for use here
    /*else
        gBattleMovePower = CalcMoveBasePowerAfterModifiers(move, battlerAtk, battlerDef, moveType, updateFlags);

    // long dmg basic formula
    dmg = ((gBattleMons[battlerAtk].level * 2) / 5) + 2;
    dmg *= gBattleMovePower;
    dmg *= CalcAttackStat(move, battlerAtk, battlerDef, moveType, isCrit, updateFlags);
    dmg /= CalcDefenseStat(move, battlerAtk, battlerDef, moveType, isCrit, updateFlags);
    dmg = (dmg / 50) + 2;

    // Calculate final modifiers.
    dmg = CalcFinalDmg(dmg, move, battlerAtk, battlerDef, moveType, typeEffectivenessModifier, isCrit, updateFlags);*/

    // Add a random factor.
    if (randomFactor)
    {
        dmg *= 100 - (Random() % 16);
        dmg /= 100;
    }

    if (dmg == 0)
        dmg = 1;

    return dmg;
}


bool32 DoBattlersShareType(u32 battler1, u32 battler2)
{
    s32 i;
    u8 types1[3] = { gBattleMons[battler1].type1, gBattleMons[battler1].type2, gBattleMons[battler1].type3 };
    u8 types2[3] = { gBattleMons[battler2].type1, gBattleMons[battler2].type2, gBattleMons[battler2].type3 };

    if (types1[2] == TYPE_MYSTERY)
        types1[2] = types1[0];
    if (types2[2] == TYPE_MYSTERY)
        types2[2] = types2[0];

    for (i = 0; i < 3; i++)
    {
        if (types1[i] == types2[0] || types1[i] == types2[1] || types1[i] == types2[2])
            return TRUE;
    }

    return FALSE;
}

u32 GetBattleMoveSplit(u32 moveId)
{
    return gBattleMoves[moveId].split;
}

bool32 CanBattlerEscape(u32 battlerId) // no ability check
{
    if (GetBattlerHoldEffect(battlerId, TRUE) == HOLD_EFFECT_SHED_SHELL)
        return TRUE;
    else if ((!IS_BATTLER_OF_TYPE(battlerId, TYPE_GHOST)) && gBattleMons[battlerId].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_WRAPPED))
        return FALSE;
    else if (gStatuses3[battlerId] & STATUS3_ROOTED)
        return FALSE;
    else if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        return FALSE;
    else
        return TRUE;
}//dont need defeatist here, that dealt with in battle_main

//Make sure the input bank is any bank on the specific mon's side
bool32 CanFling(u8 battlerId)
{
    u16 item = gBattleMons[battlerId].item;
    u16 itemEffect = ItemId_GetHoldEffect(item);

    if (item == ITEM_NONE
        || GetBattlerAbility(battlerId) == ABILITY_KLUTZ
        || gFieldStatuses & STATUS_FIELD_MAGIC_ROOM
        || gSideTimers[GET_BATTLER_SIDE(battlerId)].embargoTimer != 0
        || !CanBattlerGetOrLoseItem(battlerId, item)
        //|| itemEffect == HOLD_EFFECT_PRIMAL_ORB       //this isnt wrong, its commented out even in emerald
        || itemEffect == HOLD_EFFECT_GEMS   //want to change this, let fling gem change move type 
        || item == ITEM_ABILITY_CAPSULE
        || ((ItemId_GetPocket(item) == POCKET_BERRY_POUCH) && IsAbilityOnSide(battlerId, ABILITY_UNNERVE))
        || GetPocketByItemId(item) == POCKET_POKE_BALLS)
        return FALSE;

    return TRUE;
}

bool32 UnnerveOn(u32 battlerId, u32 itemId)
{
    if (ItemId_GetPocket(itemId) == POCKET_BERRY_POUCH && IsUnnerveAbilityOnOpposingSide(battlerId))
        return TRUE;
    return FALSE;
}

// ability checks
bool32 IsRolePlayBannedAbilityAtk(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sRolePlayBannedAttackerAbilities); i++)
    {
        if (ability == sRolePlayBannedAttackerAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsRolePlayBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sRolePlayBannedAbilities); i++)
    {
        if (ability == sRolePlayBannedAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsSkillSwapBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sSkillSwapBannedAbilities); i++)
    {
        if (ability == sSkillSwapBannedAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsWorrySeedBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sWorrySeedBannedAbilities); i++)
    {
        if (ability == sWorrySeedBannedAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsGastroAcidBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sGastroAcidBannedAbilities); i++)
    {
        if (ability == sGastroAcidBannedAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsEntrainmentBannedAbilityAttacker(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sEntrainmentBannedAttackerAbilities); i++)
    {
        if (ability == sEntrainmentBannedAttackerAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 IsEntrainmentTargetOrSimpleBeamBannedAbility(u16 ability)
{
    u32 i;
    for (i = 0; i < NELEMS(sEntrainmentTargetSimpleBeamBannedAbilities); i++)
    {
        if (ability == sEntrainmentTargetSimpleBeamBannedAbilities[i])
            return TRUE;
    }
    return FALSE;
}

bool32 TryRemoveScreens(u8 battler)
{
    bool32 removed = FALSE;
    u8 battlerSide = GetBattlerSide(battler);
    u8 enemySide = GetBattlerSide(BATTLE_OPPOSITE(battler));

    if (GetBattlerAbility(battler) == ABILITY_SCREEN_CLEANER){
        // try to remove from battler's side
        if (gSideStatuses[battlerSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT))
        {
            gSideStatuses[battlerSide] &= ~(SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT);
            gSideTimers[battlerSide].reflectTimer = 0;
            gSideTimers[battlerSide].lightscreenTimer = 0;
            gSideTimers[battlerSide].auroraVeilTimer = 0;
            gSideTimers[battlerSide].safeguardTimer = 0;
            gSideTimers[battlerSide].MagicTimer = 0;
            removed = TRUE;
        }

        // try to remove from battler opponent's side
        if (gSideStatuses[enemySide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT))
        {
            gSideStatuses[enemySide] &= ~(SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT);
            gSideTimers[enemySide].reflectTimer = 0;
            gSideTimers[enemySide].lightscreenTimer = 0;
            gSideTimers[enemySide].auroraVeilTimer = 0;
            gSideTimers[enemySide].safeguardTimer = 0;
            gSideTimers[enemySide].MagicTimer = 0;
            removed = TRUE;
        }
    }
    else //attempt using for brick break
    {
         // try to remove from battler opponent's side
        if (gSideStatuses[enemySide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT))
        {
            gSideStatuses[enemySide] &= ~(SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_SAFEGUARD | SIDE_STATUS_AURORA_VEIL | SIDE_STATUS_MAGIC_COAT);
            gSideTimers[enemySide].reflectTimer = 0;
            gSideTimers[enemySide].lightscreenTimer = 0;
            gSideTimers[enemySide].auroraVeilTimer = 0;
            gSideTimers[enemySide].safeguardTimer = 0;
            gSideTimers[enemySide].MagicTimer = 0;
            removed = TRUE;
        }
    }

    return removed;
}


static bool32 IsUnnerveAbilityOnOpposingSide(u8 battlerId)
{
    if (IsAbilityOnOpposingSide(battlerId, ABILITY_UNNERVE)
        || IsAbilityOnOpposingSide(battlerId, ABILITY_AS_ONE_ICE_RIDER)
        || IsAbilityOnOpposingSide(battlerId, ABILITY_AS_ONE_SHADOW_RIDER))
        return TRUE;
    return FALSE;
}

bool32 IsBattlerTerrainAffected(u8 battlerId, u32 terrainFlag)
{
    if (!(gFieldStatuses & terrainFlag))
        return FALSE;
    else if (gStatuses3[battlerId] & STATUS3_SEMI_INVULNERABLE)
        return FALSE;

    return IsBattlerGrounded(battlerId);
}

bool32 TestMoveFlags(u16 move, u32 flag)
{
    if (gBattleMoves[move].flags & flag)
        return TRUE;
    return FALSE;
}

bool32 CanSleep(u8 battlerId)
{
    u16 ability = GetBattlerAbility(battlerId);
    if (ability == ABILITY_INSOMNIA
        || ability == ABILITY_VITAL_SPIRIT
        || ability == ABILITY_COMATOSE
        || gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_SAFEGUARD
        || gBattleMons[battlerId].status1 & STATUS1_ANY
        || IsAbilityOnSide(battlerId, ABILITY_SWEET_VEIL)
        || IsAbilityStatusProtected(battlerId)
        || IsBattlerTerrainAffected(battlerId, STATUS_FIELD_ELECTRIC_TERRAIN | STATUS_FIELD_MISTY_TERRAIN))
        return FALSE;
    return TRUE;
}

bool32 CanBePoisoned(u8 PoisonUser, u8 PoisonTarget)
{
    u16 ability = GetBattlerAbility(PoisonTarget);

    if (!(CanPoisonType(PoisonUser, PoisonTarget))
        || gSideStatuses[GetBattlerSide(PoisonTarget)] & SIDE_STATUS_SAFEGUARD
        || ability == ABILITY_IMMUNITY
        || ability == ABILITY_COMATOSE
        || IsAbilityOnSide(PoisonTarget, ABILITY_PASTEL_VEIL)
        || IsAbilityStatusProtected(PoisonTarget)
        || IsBattlerTerrainAffected(PoisonTarget, STATUS_FIELD_MISTY_TERRAIN)
        || ((gBattleMons[PoisonTarget].status1) && gBattleMons[PoisonTarget].status1 != STATUS1_POISON)) //if works should exclude status none, and poison
        return FALSE;   
    return TRUE;
}

bool32 CanBeBurned(u8 battlerId)
{
    u16 ability = GetBattlerAbility(battlerId);
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_FIRE)
        || gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_SAFEGUARD
        || gBattleMons[battlerId].status1 & STATUS1_ANY
        || ability == ABILITY_WATER_VEIL
        || ability == ABILITY_WATER_BUBBLE
        || ability == ABILITY_COMATOSE
        || IsAbilityStatusProtected(battlerId)
        || IsBattlerTerrainAffected(battlerId, STATUS_FIELD_MISTY_TERRAIN))
        return FALSE;
    return TRUE;
}

bool32 CanBeParalyzed(u8 battlerId) //update these functions with my custom status logic so can use for cleaner setup   vsonic
{
    u16 ability = GetBattlerAbility(battlerId);
    if ((gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_SAFEGUARD)
        || ability == ABILITY_LIMBER
        || ability == ABILITY_COMATOSE
        || gBattleMons[battlerId].status1 & STATUS1_ANY
        || IsAbilityStatusProtected(battlerId)
        || IsBattlerTerrainAffected(battlerId, STATUS_FIELD_MISTY_TERRAIN))
        return FALSE;
    return TRUE;
}

bool32 CanBeFrozen(u8 battlerId)
{
    u16 ability = GetBattlerAbility(battlerId);
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_ICE)
        || IsBattlerWeatherAffected(battlerId, WEATHER_SUN_ANY)
        || gSideStatuses[GetBattlerSide(battlerId)] & SIDE_STATUS_SAFEGUARD
        || ability == ABILITY_LAVA_FISSURE
        || ability == ABILITY_MAGMA_ARMOR
        || ability == ABILITY_FLAME_BODY
        || ability == ABILITY_COMATOSE
        || gBattleMons[battlerId].status1 & STATUS1_ANY
        || IsAbilityStatusProtected(battlerId)
        || IsBattlerTerrainAffected(battlerId, STATUS_FIELD_MISTY_TERRAIN))
        return FALSE;
    return TRUE;
}

bool32 CanBeConfused(u8 battlerId)
{
    if (GetBattlerAbility(gEffectBattler) == ABILITY_OWN_TEMPO
        || gBattleMons[gEffectBattler].status2 & STATUS2_CONFUSION
        || IsBattlerTerrainAffected(battlerId, STATUS_FIELD_MISTY_TERRAIN))
        return FALSE;
    return TRUE;
}

bool32 TryActivateBattlePoisonHeal(void)  //change mind better to do 2 functions, rather than do 2 different effects with one.
{


    if ((GetBattlerAbility(gActiveBattler) == ABILITY_POISON_HEAL) && gBattleMons[gActiveBattler].hp != 0
        && (gBattleMons[gActiveBattler].status1 & STATUS1_POISON || gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_POISON))
    {
        return TRUE;
    }
    else if ((GetBattlerAbility(gActiveBattler) == ABILITY_POISON_HEAL) && gBattleMons[gActiveBattler].hp != 0
        && IS_BATTLER_OF_TYPE(gActiveBattler, TYPE_POISON) && (GetBattlerHoldEffect(gActiveBattler, TRUE) == HOLD_EFFECT_BLACK_SLUDGE))
    {
        return TRUE;
    }
    else
        return FALSE;

    
}

