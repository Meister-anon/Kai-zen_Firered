#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

#include <limits.h>
#include "global.h"
#include "constants/battle.h"
#include "constants/form_change_types.h"
#include "constants/battle_move_effects.h"
#include "battle_util.h"
#include "battle_script_commands.h"
#include "battle_main.h"
#include "battle_ai_switch_items.h"
#include "battle_gfx_sfx_util.h"
#include "battle_util2.h"
#include "battle_bg.h"
#include "window.h" //need this for build modern to work for battle window ui

/*
    Banks are a name given to what could be called a 'battlerId' or 'monControllerId'.
    Each bank has a value consisting of two bits.
    0x1 bit is responsible for the side, 0 = player's side, 1 = opponent's side.
    0x2 bit is responsible for the id of sent out pokemon. 0 means it's the first sent out pokemon, 1 it's the second one. (Triple battle didn't exist at the time yet.)
*/

#define GET_BATTLER_POSITION(battler)((gBattlerPositions[battler]))
#define GET_BATTLER_SIDE(battler)((GetBattlerPosition(battler) & BIT_SIDE))
#define GET_BATTLER_SIDE2(battler)((GET_BATTLER_POSITION(battler) & BIT_SIDE))

#define TRAINER_OPPONENT_3FE        0x3FE
#define TRAINER_OPPONENT_C00        0xC00
#define TRAINER_LINK_OPPONENT       0x800
#define SECRET_BASE_OPPONENT        0x400 //need remove secret base stuff and help meun again, remove this after

// Used to exclude moves learned temporarily by Transform or Mimic
#define MOVE_IS_PERMANENT(battler, moveSlot)                        \
   (!(gBattleMons[battler].status2 & STATUS2_TRANSFORMED)           \
 && !(gDisableStructs[battler].mimickedMoves & gBitTable[moveSlot]))

#define B_ACTION_USE_MOVE                  0
#define B_ACTION_USE_ITEM                  1
#define B_ACTION_SWITCH                    2
#define B_ACTION_RUN                       3
#define B_ACTION_SAFARI_WATCH_CAREFULLY    4
#define B_ACTION_SAFARI_BALL               5
#define B_ACTION_SAFARI_BAIT               6
#define B_ACTION_SAFARI_GO_NEAR            7
#define B_ACTION_SAFARI_RUN                8
#define B_ACTION_OLDMAN_THROW              9
#define B_ACTION_EXEC_SCRIPT               10
#define B_ACTION_TRY_FINISH                11
#define B_ACTION_FINISHED                  12
#define B_ACTION_CANCEL_PARTNER            12 // when choosing an action
#define B_ACTION_NOTHING_FAINTED           13 // when choosing an action
#define B_ACTION_NONE                      0xFF

#define MAX_TRAINER_ITEMS 4

// array entries for battle communication
#define MULTIUSE_STATE          0x0
#define CURSOR_POSITION         0x1
#define TASK_ID                 0x1 // task Id and cursor position share the same field
#define SPRITES_INIT_STATE1     0x1 // shares the Id as well
#define SPRITES_INIT_STATE2     0x2
#define MOVE_EFFECT_BYTE        0x3
#define ACTIONS_CONFIRMED_COUNT 0x4
#define MULTISTRING_CHOOSER     0x5
#define MSG_DISPLAY             0x7
#define BATTLE_COMMUNICATION_ENTRIES_COUNT  0x8

#define MOVE_TARGET_SELECTED            0
#define MOVE_TARGET_DEPENDS             (1 << 0)
#define MOVE_TARGET_USER_OR_SELECTED    (1 << 1)
#define MOVE_TARGET_RANDOM              (1 << 2)
#define MOVE_TARGET_BOTH                (1 << 3)
#define MOVE_TARGET_USER                (1 << 4)
#define MOVE_TARGET_FOES_AND_ALLY       (1 << 5)
#define MOVE_TARGET_OPPONENTS_FIELD     (1 << 6)
#define MOVE_TARGET_ALLY                (1 << 7)
#define MOVE_TARGET_ALL_BATTLERS        (MOVE_TARGET_FOES_AND_ALLY | MOVE_TARGET_USER)  //use untl setup like emerald, taken from MOVE_ROTOTILLER
//#define MOVE_TARGET_ALL_BATTLERS        ((1 << 8) | MOVE_TARGET_USER)  can use when setup correctly

// For the second argument of GetMoveTarget, when no target override is needed
#define NO_TARGET_OVERRIDE 0

// Flag settings
// To use the following features in scripting, replace the 0s with the flag ID you're assigning it to.
// Eg: Replace with FLAG_UNUSED_0x264 so you can use that flag to toggle the feature.
#define B_FLAG_INVERSE_BATTLE       0     // If this flag is set, the battle's type effectiveness are inversed. For example, fire is super effective against water.
#define B_FLAG_FORCE_DOUBLE_WILD    0     // If this flag is set, all land and surfing wild battles will be double battles.
#define B_SMART_WILD_AI_FLAG        1     // If not 0, you can set this flag in a script to enable smart wild pokemon
#define B_FLAG_NO_BAG_USE           0     // If this flag is set, the ability to use the bag in battle is disabled.
#define B_FLAG_NO_CATCHING          0     // If this flag is set, the ability to catch wild Pok�mon is disabled.


struct TrainerMonNoItemDefaultMoves //pull from 4-12 later
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
};

struct TrainerMonItemDefaultMoves
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
    u16 heldItem;
};

struct TrainerMonNoItemCustomMoves
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
    u16 moves[4];
};

/*there isn't really much reason to have more structs than just TrainerMonItemCustomMoves, since I've fixed the move error
only values needed in selction are lvl and species, everything else can be left empty and can safely default to zero.
Check definition of struct to find base/default values.

Still need to add u8 abilityNum field so ability can track w repeated trainers,
but setup like iv field, so if left blank can just set a random value
Using multiple structs was to save memory, it wouldn't cost me too too much to consolidate
but to attempt to compensate change iv, to u8 field. its only u16 for the weird masking they do.
would require combing all trainer fields and translating from mask back to max 31
change in code would just be fixedIV = partyData[i].iv  removing the mask and 255 divisor
would only save me 1 byte for every trainer party, which would balance by adding the abilityNum field
but still a net positive

put abilityNum field below lvl, make constant defines so don't have to just use 0-3

since I want leaving blank to be set random ability, I can't use value 0 as set mon ability num
so i will need to make a function to do it, "i" value of 0 will default to setting randomly
then if not 0,  use setmondata ability num i-1    so  i value of 1, will be abilitynum 0 etc.

Replacing iv values will be easier than thought, as most entries are blank,
the only used values: 20 30 40 50 60 80 90
    100 110 120 130 150 160 170 180 or 200 220 250 & 255
so simple as running a ctrl h for  .iv = existing value,
then just multiply by 31 and divide by 255, to find the replace value
*/
struct TrainerMonItemCustomMoves
{
    u8 iv;
    u16 evs[6];
    u8 lvl;
    u8 abilityNum;
    u16 species;
    u16 heldItem;
    u16 moves[4];
};

union TrainerMonPtr
{
    const struct TrainerMonNoItemDefaultMoves *NoItemDefaultMoves;
    const struct TrainerMonNoItemCustomMoves *NoItemCustomMoves;
    const struct TrainerMonItemDefaultMoves *ItemDefaultMoves;
    const struct TrainerMonItemCustomMoves *ItemCustomMoves;
};

struct Trainer
{
    /*0x00*/ u8 partyFlags;
    /*0x01*/ u8 trainerClass;
    /*0x02*/ u8 encounterMusic_gender; // last bit is gender
    /*0x03*/ u8 trainerPic;
    /*0x04*/ u8 trainerName[12];
    /*0x10*/ u16 items[4];
    /*0x18*/ u8 battleType; //with addition fo triple & rotation change this from bool, to just a constant value to represent each battle type
    /*0x1C*/ u32 aiFlags;
    /*0x20*/ u8 partySize;
    /*0x24*/ const union TrainerMonPtr party;
};

extern const struct Trainer gTrainers[];

#define SINGLES      0  //needed rename include was causing issues


struct ResourceFlags
{
    u32 flags[MAX_BATTLERS_COUNT];
};

#define RESOURCE_FLAG_FLASH_FIRE     1
#define RESOURCE_FLAG_ROOST          2
#define RESOURCE_FLAG_UNBURDEN       4
#define RESOURCE_FLAG_EMERGENCY_EXIT 8  //check how this used will prob do it differently for my implementation
#define RESOURCE_FLAG_NEUTRALIZING_GAS 16 //works by doubling previous

struct DisableStruct
{
    /*0x00*/ u32 transformedMonPersonality;
    /*0x04*/ u16 disabledMove;
    /*0x06*/ u16 encoredMove;
    /*0x08*/ u8 protectUses;
    /*0x09*/ u8 stockpileCounter;
    s8 stockpileDef;
    s8 stockpileSpDef;
    s8 stockpileBeforeDef;
    s8 stockpileBeforeSpDef;
    /*0x0A*/ u8 substituteHP;
    /*0x0B*/ u8 disableTimer : 4;
    /*0x0B*/ u8 disableTimerStartValue : 4;
    /*0x0C*/ u8 encoredMovePos;
    /*0x0D*/ u8 unkD;
    /*0x0E*/ u8 encoreTimer : 4;
    /*0x0E*/ u8 encoreTimerStartValue : 4;
    /*0x0F*/ u8 perishSongTimer : 4;
    /*0x0F*/ u8 perishSongTimerStartValue : 4;
    /*0x10*/ u8 furyCutterCounter;  //apparently still need for anim task in anim_effects_2
             u16 furyCutterAccDrop; //need for acc drop to keep value 
    /*0x11*/ u8 rolloutTimer : 4;
    /*0x11*/ u8 rolloutTimerStartValue : 4;
    /*0x12*/ u8 chargeTimer : 4;
    /*0x12*/ u8 chargeTimerStartValue : 4;
    /*0x13*/ u8 tauntTimer : 4;
    /*0x13*/ u8 tauntTimer2 : 4;
    /*0x14*/ u8 battlerPreventingEscape;
    /*0x15*/ u8 battlerWithSureHit;
    /*0x16*/ u8 isFirstTurn;
    /*0x17*/ u8 unk17;
    /*0x18*/ u8 truantCounter : 1;
    /*0x18*/ u8 sleepCounter : 1;
    /*0x18*/ u8 truantSwitchInHack : 1; // unused? 
    /*0x18*/ u8 unk18_a_2 : 2;
    /*0x18*/ u8 mimickedMoves : 4;
    /*0x19*/ u8 rechargeTimer;
    u8 toxicTurn; //wit change to statusnig will need move aqua ring ingrain and toxic turn counters to differnet way
    u8 ingrainTurn;
    u8 aquaringTurn;
    u8 rageCounter;
    u8 autotomizeCount;
    u8 noRetreat : 1;
    u8 tarShot : 1;
    u8 octolock : 1;
    u8 slowStartTimer;
    //u8 embargoTimer; moved to gsidetimers
    u8 magnetRiseTimer;
    u8 telekinesisTimer;
    u8 laserFocusTimer;
    u8 throatChopTimer;
    u8 RoostTimer; // to set random % 4 effect after use roost setup iondelluge the same remove random make constant
    u8 usedMoves : 4; //have iondelug in field timers already
    u8 wrapTurns;  //turn counter for wrap 
    u8 bindTurns;  // turn counter for bind
    u8 clampTurns;
    u8 swarmTurns;
    u8 snaptrapTurns;
    u8 thundercageTurns;
    u8 environmentTrapTurns;   //turn counter for environment traps fire spin whirlpool sandtomb magma storm
    u8 FrozenTurns;
    u8 bideTimer;
    u8 bindMovepos; //stored pos of bind move   //double check I'm actually using
    u16 bindedMove; //move bind locks you to
    u8 inthralled;
    u8 inthrallTimer;
    u16 inthralledMove;
    //u8 RoostTimerStartValue;  //remove for now until I get 
    /*0x1A*/ u8 unk1A[2];
}; //think I may not actually need roost start value, long as I have timer
//need look up padding and bitwise to understand how these work so i'm doing it correctly
//if I don't have proper padding it won't be faster/save space, and could actually slow it down instead
//vsonic

extern struct DisableStruct gDisableStructs[MAX_BATTLERS_COUNT];

struct ProtectStruct
{
    /* field_0 */
             u32 protected:1;
             u32 endured : 1;
             u32 noValidMoves : 1;
             u32 helpingHand : 1;
             u32 bounceMove : 1;
             u32 stealMove : 1;
             u32 flag0Unknown : 1;
             u32 prlzImmobility : 1;
             /* field_1 */
             u32 confusionSelfDmg : 1;  //will instead change ot make random target, and within that if move is non-damaging do normal confusion hit, or use move against self
             u32 targetNotAffected : 1; //opposite equivalent of targetAffected
             u32 chargingTurn : 1;
             u32 fleeFlag : 2; // for RunAway Defeatist and Smoke Ball
             u32 usedImprisonedMove : 1;
             u32 loveImmobility : 1;
             u32 usedDisabledMove : 1;
             /* field_2 */
             u32 usedTauntedMove : 1;      // 0x1
             u32 flag2Unknown : 1;         // 0x2
             u32 flinchImmobility : 1;     // 0x4
             u32 notFirstStrike : 1;       // 0x8
             u32 flag_x10 : 1;           // 0x10
             u32 flag_x20 : 1;           // 0x20
             u32 flag_x40 : 1;           // 0x40
             u32 flag_x80 : 1;           // 0x80
             u32 field3 : 8;

             u32 physicalDmg;
             u32 specialDmg;
             u8 physicalBattlerId;
             u8 specialBattlerId;
             u32 spikyShielded : 1;  //consider renaming spike shield
             u32 kingsShielded : 1;
             u32 banefulBunkered : 1;
             u16 silkTrapped : 1;
             u32 shieldBashed : 1;
             u32 usesBouncedMove : 1;
             u32 usedHealBlockedMove : 1;
             u32 usedGravityPreventedMove : 1;
             u32 powderSelfDmg : 1;  //not sure why  I added this I'm not gonna use it? well for someone else I guess. 
             u32 usedThroatChopPreventedMove : 1;
             u32 pranksterElevated : 1;
             u32 quickDraw : 1;
             u16 quash : 1;
             u16 beakBlastCharge : 1;
             u32 usedMicleBerry : 1;
             u32 usedCustapBerry : 1;    // also quick claw
             u32 touchedProtectLike : 1;
             u32 obstructed : 1;
             u32 disableEjectPack : 1;
             u16 forewarnedMove; //for storing move from forewarn ability
             u8 forewarnDone : 1;  //to be set TRUE if predicted move was used by opponent, if not and enemy faints or switches, reactivate forewarn for next opponent 
             u16 anticipatedMove;    //for storing move from anticipation ability
             u8 anticipationDone : 1;// same as forwarn clause //also considering moveend & moveendtarget can prob do swithin repeat, by swapping battler and side w new abilityeffet clause?
             u16 fieldE;
};

extern struct ProtectStruct gProtectStructs[MAX_BATTLERS_COUNT];

struct SpecialStatus    //pretty sure all values
{
    u8 statLowered : 1;             // 0x1
    //u8 lightningRodRedirected : 1;  // 0x2    //removed to save ew ram  just do in the code
    //u8 stormDrainRedirected : 1;  // 0x2
    u8 tigerMomAttacked : 1;  // 0x2 //need to add redirects here for lightning rod/storm drain esque abilities unless I code it different
    u8 restoredBattlerSprite : 1;    // 0x4
    u8 intimidatedMon : 1;          // 0x8
    u8 tigeredMon : 1;          // 0x8  extra set incase using intimidatedmon prevents using both at once
    u8 traced : 1;                  // 0x10
    u8 defeatistActivated : 1;      // 
    u8 ppNotAffectedByPressure : 1;
    u8 flag40 : 1;
    u8 focusBanded : 1;
    u8 focusSashed : 1;
    u8 sturdied : 1;
    u8 sturdyhungon:1; //new one time use  for sturdy avoiding exploion moves death
    u8 field1[3];
    u8 berryReduced : 1;
    u8 rototillerAffected : 1;  // to be affected by rototiller
    u8 instructedChosenTarget : 3;
    u8 switchInItemDone : 1;
    u8 gemBoost : 1;
    u8 gemParam;
    u8 damagedMons : 4; // Mons that have been damaged directly by using a move, includes substitute. //NOW THAT have added can prob use to update catchexp function/macro?
    u8 dancerUsedMove : 1;
    u8 dancerOriginalTarget : 3;
    u8 announceNeutralizingGas : 1;   // See Cmd_switchineffects
    u8 neutralizingGasRemoved : 1;    // See VARIOUS_TRY_END_NEUTRALIZING_GAS
    u8 stenchRemoved : 1;    // Set as VARIOUS_TRY_END_STENCH  both exclusive to gastro acid?
    u8 switchInAbilityDone : 1;
    s32 dmg;
    s32 physicalDmg;
    s32 specialDmg;
    u8 EmergencyExit : 1; //logic mix truant pursuit/escape hit, setup like truant trigger on end turn that hp met theshold,raise attack then make attack first & set moveeffect escape hit so it leaves after attacking. WILL USE for both wimpout and Emergency exit just use ability check for logic change
    u8 physicalBattlerId;
    u8 specialBattlerId;
    u8 changedStatsBattlerId; // Battler that was responsible for the latest stat change. Can be self.
    u8 parentalBondState : 2; // 0/1/2
    u8 multiHitOn : 1; //think is a state chech, seems most used with parental bond
    u8 firstFuturesightHits;
    u8 secondFuturesightHits;
    u8 field12;
    u8 field13;//check moody case for switchin line something something = 2
};

extern struct SpecialStatus gSpecialStatuses[MAX_BATTLERS_COUNT];

struct SideTimer
{
    /*0x00*/ u8 reflectTimer;
    /*0x01*/ u8 reflectBattlerId;
    /*0x02*/ u8 lightscreenTimer;
    /*0x03*/ u8 lightscreenBattlerId;
    /*0x04*/ u8 mistTimer;
    /*0x05*/ u8 mistBattlerId;
    /*0x06*/ u8 safeguardTimer;
    /*0x07*/ u8 safeguardBattlerId;
    /*0x08*/ u8 followmeTimer;
    /*0x09*/ u8 followmeTarget;
    /*0x0A*/ u8 followmePowder;
    u8 spikesAmount;
    u8 toxicSpikesAmount;
    u8 stealthRockAmount;
    u8 stickyWebAmount;
    u8 stickyWebBattlerSide; // Used for Court Change
    u8 auroraVeilTimer;
    u8 auroraVeilBattlerId;
    u8 tailwindTimer;
    u8 tailwindBattlerId;
    u8 luckyChantTimer;
    u8 luckyChantBattlerId;
    u8 healBlockTimer; //added for side status effect
    u8 healBlockBattlerId; //hopefully will be able to individual target clear status, but keep side status in effect for new switches
    u8 embargoBattlerId;
    u8 embargoTimer;
    u8 mudSportBattlerId;
    u8 mudSportTimer;     //put these back, gen 3 effect didn' work how I thought. effect only lasts long as user stays in, and only for user who set it.
    u8 waterSportTimer;  //forgot to remove these earlier, since I'm using gen 3 effects for them
    u8 waterSportBattlerId;
    u8 retaliateTimer;  //vsonic need to implement
    u8 MagicTimer;
    u8 MagicBattlerId; //magic coat defines changed from one turn to screen like side status
    /*0x0B*/ u8 fieldB;
};

extern struct SideTimer gSideTimers[];

struct FieldTimer
{

    u8 wonderRoomTimer;
    u8 magicRoomTimer;
    u8 trickRoomTimer;
    u8 terrainTimer;
    u8 echoVoiceCounter;
    u8 gravityTimer;
    u8 fairyLockTimer;
    u8 IonDelugeTimer; // this & roost will be only ones that don't fail if used when timer isn't 0
    u8 HazeTimer;

};//check how I setup roost may not need iondelugetimer here

struct WishFutureKnock
{
    u8 futureSightCounter[MAX_BATTLERS_COUNT];
    u8 futureSightCounter2[MAX_BATTLERS_COUNT];
    u8 futureSightAttacker[MAX_BATTLERS_COUNT];
    s32 futureSightDmg[MAX_BATTLERS_COUNT];
    u16 futureSightMove[MAX_BATTLERS_COUNT];
    u8 wishCounter[MAX_BATTLERS_COUNT];
    u8 wishMonId[MAX_BATTLERS_COUNT];
    u8 weatherDuration;
    u8 forecastedWeather; //will be second weather effect predicted on switchin by forecast
    u8 knockedOffMons[2];
};

extern struct WishFutureKnock gWishFutureKnock;

struct AI_ThinkingStruct
{
    u8 aiState;
    u8 movesetIndex;
    u16 moveConsidered;
    s8 score[4];
    u32 funcResult;
    u32 aiFlags;
    u8 aiAction;
    u8 aiLogicId;
    u8 filler12[6];
    u8 simulatedRNG[4];
};

extern u8 gActiveBattler;
extern u8 gBattlerAbility;
extern u8 gBattlerTarget;
extern u8 gAbsentBattlerFlags;

extern struct BattlePokemon gBattleMons[MAX_BATTLERS_COUNT];

struct UsedMoves
{
    u16 moves[MAX_BATTLERS_COUNT];
    u16 unknown[MAX_BATTLERS_COUNT];
};

struct BattleHistory
{
    /*0x00*/ u16 usedMoves[2][8]; // 0xFFFF means move not used (confuse self hit, etc)
    /*0x20*/ u16 abilities[MAX_BATTLERS_COUNT / 2];
    /*0x24*/ u8 itemEffects[MAX_BATTLERS_COUNT / 2];
    /*0x26*/ u16 trainerItems[MAX_BATTLERS_COUNT];
    /*0x2E*/ u8 itemsNo;
             u16 heldItems[MAX_BATTLERS_COUNT]; //not default added
};

struct BattleScriptsStack
{
    const u8 *ptr[8];
    u8 size;
};

struct BattleCallbacksStack
{
    void (*function[8])(void);
    u8 size;
};

struct StatsArray
{
    u16 stats[NUM_STATS];
};

struct BattleResources
{
    struct SecretBaseRecord *secretBase;
    struct ResourceFlags *flags;
    struct BattleScriptsStack *battleScriptsStack;
    struct BattleCallbacksStack *battleCallbackStack;
    struct StatsArray *beforeLvlUp;
    struct AI_ThinkingStruct *ai;
    struct BattleHistory *battleHistory;
    struct BattleScriptsStack *AI_ScriptsStack;
    u8 bufferA[MAX_BATTLERS_COUNT][0x200]; //ported seems for megas
    u8 bufferB[MAX_BATTLERS_COUNT][0x200];
};

extern struct BattleResources *gBattleResources;

struct BattleResults
{
    u8 playerFaintCounter;    // 0x0
    u8 opponentFaintCounter;  // 0x1
    u8 playerSwitchesCounter; // 0x2
    u8 numHealingItemsUsed;   // 0x3
    u8 numRevivesUsed;        // 0x4
    u8 playerMonWasDamaged : 1; // 0x5
    u8 usedMasterBall : 1;      // 0x5
    u8 caughtMonBall : 4;       // 0x5
    u8 shinyWildMon : 1;        // 0x5
    u8 unk5_7 : 1;              // 0x5
    u16 playerMon1Species;    // 0x6
    u8 playerMon1Name[POKEMON_NAME_LENGTH + 1];    // 0x8
    u8 battleTurnCounter;     // 0x13
    u8 playerMon2Name[POKEMON_NAME_LENGTH + 1];    // 0x14
    u8 pokeblockThrows;       // 0x1F   //leave in in case I can implement contest/ emerlad style safari zone planters
    u16 lastOpponentSpecies;  // 0x20
    u16 lastUsedMovePlayer;   // 0x22
    u16 lastUsedMoveOpponent; // 0x24
    u16 playerMon2Species;    // 0x26
    u16 caughtMonSpecies;     // 0x28
    u8 caughtMonNick[POKEMON_NAME_LENGTH];     // 0x2A
    u8 filler34[2];
    //u8 catchAttempts[11];     // 0x36
    u8 catchAttempts[POKEMON_NAME_LENGTH + 1];     // 0x36
};//some of these seem just for statistics so may remove


extern struct BattleResults gBattleResults;

struct LinkPartnerHeader
{
    u8 versionSignatureLo;
    u8 versionSignatureHi;
    u8 vsScreenHealthFlagsLo;
    u8 vsScreenHealthFlagsHi;
    struct BattleEnigmaBerry battleEnigmaBerry;
};

struct MegaEvolutionData
{
    u8 toEvolve; // As flags using gBitTable.
    u8 evolvedPartyIds[2]; // As flags using gBitTable;
    bool8 alreadyEvolved[4]; // Array id is used for mon position.
    u16 evolvedSpecies[MAX_BATTLERS_COUNT];
    u16 playerEvolvedSpecies;
    u8 primalRevertedPartyIds[2]; // As flags using gBitTable;
    u16 primalRevertedSpecies[MAX_BATTLERS_COUNT];
    u16 playerPrimalRevertedSpecies;
    u8 battlerId;
    bool8 playerSelect;
    u8 triggerSpriteId;
    bool8 isWishMegaEvo;
    bool8 isPrimalReversion;
};

struct Illusion
{
    u8 on;
    u8 set;
    u8 broken;
    u8 partyId;
    struct Pokemon *mon;
};

struct StolenItem
{
    u16 originalItem : 15;
    u16 stolen : 1;
};

struct StatFractions
{
    u8 dividend;
    u8 divisor;
};

extern const struct StatFractions gAccuracyStageRatios[];

//think effects meant to last all battle should go here rather than special status as that is cleared on switch
struct BattleStruct //fill in unused fields when porting
{
    u8 turnEffectsTracker;
    u8 turnEffectsBattlerId;
    u8 turnCountersTracker;
    u16 wrappedMove[MAX_BATTLERS_COUNT]; // Leftover from Ruby's ewram access. /u16 because epanded move ids  //no longer need the * 2 forgot I redid these
    u16 moveTarget[MAX_BATTLERS_COUNT]; //checked is u16 in emerald, and fixed missed replacement of wrappedMove logic
    u8 expGetterMonId;
    u8 targetsDone[MAX_BATTLERS_COUNT]; // Each battler as a bit.
    u8 wildVictorySong;
    u8 dynamicMoveType;
    u8 wrappedBy[MAX_BATTLERS_COUNT];
    u8 weathersetBy[MAX_BATTLERS_COUNT];    //new member for tracking who set new weather conditions
    u16 assistPossibleMoves[PARTY_SIZE * MAX_MON_MOVES]; // 6 mons, each of them knowing 4 moves
    //u8 focusPunchBattlerId; //don't need as changed focus punch effct
    u8 battlerPreventingSwitchout;
    u8 moneyMultiplier;
    u8 moneyMultiplierMove : 1;
    u8 savedTurnActionNumber;
    u8 switchInAbilitiesCounter;
    u8 faintedActionsState;
    u8 faintedActionsBattlerId;
    // balign 2
    u16 expValue;
    u8 scriptPartyIdx; // for printing the nickname
    u8 sentInPokes;
    bool8 selectionScriptFinished[MAX_BATTLERS_COUNT];
    u8 battlerPartyIndexes[MAX_BATTLERS_COUNT];
    u8 monToSwitchIntoId[MAX_BATTLERS_COUNT];
    u8 battlerPartyOrders[MAX_BATTLERS_COUNT][3];
    u8 runTries;
    u8 caughtMonNick[POKEMON_NAME_LENGTH + 1];
    struct MegaEvolutionData mega;
    //u8 field_78; // unused
    u8 safariGoNearCounter;
    u8 safariPkblThrowCounter;
    u8 safariEscapeFactor;
    u8 safariCatchFactor;
    u8 linkBattleVsSpriteId_V;
    u8 linkBattleVsSpriteId_S;
    u8 formToChangeInto;
    u8 chosenMovePositions[MAX_BATTLERS_COUNT];
    u8 stateIdAfterSelScript[MAX_BATTLERS_COUNT];
    struct Illusion illusion[MAX_BATTLERS_COUNT];
    //u8 field_88; // unused
    //u8 field_89; // unused
    //u8 field_8A; // unused
    u8 playerPartyIdx;
    //u8 field_8C; // unused
    //u8 field_8D; // unused
    //s8 aiFinalScore[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT][MAX_MON_MOVES]; // AI, target, moves to make debugging easier
    //u8 aiMoveOrAction[MAX_BATTLERS_COUNT];
    //u8 aiChosenTarget[MAX_BATTLERS_COUNT]; //ported these 3 hope ot a problem
    u8 soulheartBattlerId;  //Magearna ability
    u8 friskedBattler; // Frisk needs to identify 2 battlers in double battles.
    bool8 friskedAbility; // If identifies two mons, show the ability pop-up only once.
    u16 changedSpecies[NUM_BATTLE_SIDES][PARTY_SIZE]; // For Zygarde or future forms when multiple mons can change into the same pokemon.
    u8 stringMoveType;
    u8 expGetterBattlerId;
    bool8 ateBoost[MAX_BATTLERS_COUNT];//says that but ateberry seems to only be used by dodriogame
    u8 ateBerry[2]; // array id determined by side, each party pokemon as bit
    u8 stolenStats[NUM_BATTLE_STATS]; // hp byte is used for which stats to raise, other inform about by how many stages
    //u8 field_90; // unused   //ok thank god these really are unused, I'll replace when I need to bing stuff from emerald
    u8 absentBattlerFlags;
    u8 AI_monToSwitchIntoId[MAX_BATTLERS_COUNT]; //changed from 2, based on emerald
    u8 simulatedInputState[4];  // used by Oak/Old Man/Pokedude controllers
    //u8 lastTakenMove[MAX_BATTLERS_COUNT * 2 * 2]; // ask gamefreak why they declared it that way /original here, emerald version below
    u16 lastTakenMove[MAX_BATTLERS_COUNT]; // Last move that a battler was hit with.
    u8 lastMoveFailed; // as bits for each battler, for the sake of Stomping Tantrum
    u8 lastMoveTarget[MAX_BATTLERS_COUNT]; // The last target on which each mon used a move, for the sake of Instruct
    u16 hpOnSwitchout[2];
    u16 abilityPreventingSwitchout; //could probably use lastTakenMove with ai, to keep a count of a party mons moveset.
    u8 hpScale;
    u16 savedBattleTypeFlags;
    void (*savedCallback)(void);
    u8 synchronizeMoveEffect;
    u8 multiplayerId;
    bool8 overworldWeatherDone;
    bool8 terrainDone;
    u8 atkCancellerTracker;
    //u16 usedHeldItems[MAX_BATTLERS_COUNT]; //original value below is emerald expansion changed version,  
    u16 usedHeldItems[PARTY_SIZE][NUM_BATTLE_SIDES]; // For each party member and side. For harvest, recycle  //think I"m setup to use this? adjusted all values now
    u8 chosenItem[4]; // why is this an u8?
    u8 AI_itemType[2];
    u8 AI_itemFlags[2];
    u16 choicedMove[MAX_BATTLERS_COUNT];
    u16 changedItems[MAX_BATTLERS_COUNT];
    u8 intimidateBattler;
    u8 switchInItemsCounter;
    u8 field_DA; // battle tower related
    u8 turnSideTracker;
    u8 fillerDC[0xDF - 0xDC];
    u8 givenExpMons;
    u16 lastTakenMoveFrom[MAX_BATTLERS_COUNT][MAX_BATTLERS_COUNT];// a 2-D array [target][attacker]
    u16 castformPalette[MAX_BATTLERS_COUNT][16]; //important, may be how they fixed alcremie?
    u8 wishPerishSongState;
    u8 wishPerishSongBattlerId;
    u8 savedBattlerTarget;
    bool8 anyMonHasTransformed;
    u16 tracedAbility[MAX_BATTLERS_COUNT]; //didn't really need to port, but prob can use it to show current ability in menu summary screen //important
    u16 hpBefore[MAX_BATTLERS_COUNT]; // Hp of battlers before using a move. For Berserk
    bool8 spriteIgnore0Hp;
    u8 field_182; //look into this
    struct StolenItem itemStolen[PARTY_SIZE];  // Player's team that had items stolen (two bytes per party member)
    u8 blunderPolicy : 1; // should blunder policy activate
    u8 swapDamageCategory:1; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
    u8 sameMoveTurns[MAX_BATTLERS_COUNT]; // For Metronome, number of times the same moves has been SUCCESFULLY used.
    u16 moveEffect2; // For Knock Off smack down and removestatus moves i.e smelling salts wakeupslap & sparklin aria   -PORTED
    u8 ballSpriteIds[2];    // item gfx, window gfx
    u8 stickyWebUser;
    u8 appearedInBattle; // Bitfield to track which Pokemon appeared in battle. Used for Burmy's form change
    u8 skyDropTargets[MAX_BATTLERS_COUNT]; // For Sky Drop, to account for if multiple Pokemon use Sky Drop in a double battle.
    // When using a move which hits multiple opponents which is then bounced by a target, we need to make sure, the move hits both opponents, the one with bounce, and the one without.
    u8 attackerBeforeBounce : 2;
    u16 overwrittenAbilities[MAX_BATTLERS_COUNT];    // abilities overwritten during battle (keep separate from battle history in case of switching)
    u8 battleBondTransformed[NUM_BATTLE_SIDES]; // Bitfield for each party.
    //u8 presentBasePower; //used for   multihit move effect check, but with my version don't need this
    bool8 slowstartDone[MAX_BATTLERS_COUNT];
    // align 4
    union {
        struct LinkPartnerHeader linkPartnerHeader;
        struct MultiBattlePokemonTx multiBattleMons[3];
    } multiBuffer;
    u8 padding_1E4[0x1C];
}; // size == 0x200 bytes

extern struct BattleStruct *gBattleStruct;

#define F_DYNAMIC_TYPE_1 (1 << 6)
#define F_DYNAMIC_TYPE_2 (1 << 7)
#define DYNAMIC_TYPE_MASK (F_DYNAMIC_TYPE_1 - 1) //how does this work?

//changing this as it is, doesn't work right with things that set 
//type normal but aren't normal, since normal is type 0
//think this may be only change I need to make actually
#define GET_MOVE_TYPE(move, typeArg)                                    \
{                                                                       \
    if (gBattleStruct->dynamicMoveType != 0xFF)                         \
        typeArg = gBattleStruct->dynamicMoveType & DYNAMIC_TYPE_MASK;   \
    else                                                                \
        typeArg = gBattleMoves[move].type;                              \
}

//leave else set to 0, as first argument should always be true, 
//so essentially just means if not two typed move,
//in which case I don't want to read the argument as a type at all
#define GET_MOVE_ARGUMENT(move, typeArg)                                   \
{                                                                          \
    if ((gBattleMoves[move].effect == EFFECT_TWO_TYPED_MOVE)               \
    && gBattleStruct->dynamicMoveType != 0xFF)                             \
        typeArg = gBattleStruct->dynamicMoveType & DYNAMIC_TYPE_MASK;      \
    else                                                                   \
        typeArg = 0;                                                       \
}

//#define IS_TYPE_PHYSICAL(moveType)(moveType < TYPE_MYSTERY)
//#define IS_TYPE_SPECIAL(moveType)(moveType > TYPE_MYSTERY)

#define IS_MOVE_PHYSICAL(move)(GetBattleMoveSplit(move) == SPLIT_PHYSICAL)
#define IS_MOVE_SPECIAL(move)(GetBattleMoveSplit(move) == SPLIT_SPECIAL)
#define IS_MOVE_STATUS(move)(gBattleMoves[move].split == SPLIT_STATUS)
#define BATTLER_MAX_HP(battlerId)(gBattleMons[battlerId].hp == gBattleMons[battlerId].maxHP)
#define TARGET_TURN_DAMAGED ((gSpecialStatuses[gBattlerTarget].physicalDmg != 0 || gSpecialStatuses[gBattlerTarget].specialDmg != 0))
#define IS_BATTLER_OF_TYPE(battlerId, type)((gBattleMons[battlerId].type1 == type || gBattleMons[battlerId].type2 == type || gBattleMons[battlerId].type3 == type))
#define SET_BATTLER_TYPE(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type1 = type;            \
    gBattleMons[battlerId].type2 = type;            \
    gBattleMons[battlerId].type3 = TYPE_MYSTERY;    \
}
//made this myself
#define SET_BATTLER_TYPE2(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type2 = type;            \
    gBattleMons[battlerId].type3 = TYPE_MYSTERY;    \
}

//made this myself
//plan use this for planned idea of terra
#define SET_BATTLER_TYPE3(battlerId, type)           \
{                                                   \
    gBattleMons[battlerId].type3 = type;            \
}

#define SET_BATTLER_TYPE_PROTEAN(battlerId, type)   \
{                                                   \
    gBattleMons[battlerId].type1 = type;            \
    gBattleMons[battlerId].type2 = type;            \
}//change so type 3 is unaffected

#define GET_STAT_BUFF_ID(n)((n & 7))              // first three bits 0x1, 0x2, 0x4
#define GET_STAT_BUFF_VALUE_WITH_SIGN(n)((n & 0xF8))
#define GET_STAT_BUFF_VALUE(n)(((n >> 3) & 0xF))      // 0x8, 0x10, 0x20, 0x40
#define STAT_BUFF_NEGATIVE 0x80                     // 0x80, the sign bit

#define SET_STAT_BUFF_VALUE(n)((((n) << 3) & 0xF8))

#define SET_STATCHANGER(statId, stage, goesDown)(gBattleScripting.statChanger = (statId) + ((stage) << 3) + (goesDown << 7))
#define SET_STATCHANGER2(dst, statId, stage, goesDown)(dst = (statId) + ((stage) << 3) + (goesDown << 7)) //for changing 2 different stats in a turn



static inline struct Pokemon *GetSideParty(u32 side)
{
    return side == B_SIDE_PLAYER ? gPlayerParty : gEnemyParty;
}

static inline struct Pokemon *GetBattlerParty(u32 battlerId)
{
    extern u8 GetBattlerSide(u8 battler);
    return GetSideParty(GetBattlerSide(battlerId));
}

// NOTE: The members of this struct have hard-coded offsets 
//       in include/constants/battle_script_commands.h
struct BattleScripting  //remember expanding this costs ewram
{
    s32 painSplitHp;
    s32 bideDmg;
    u8 multihitString[6];
    u8 dmgMultiplier;
    u8 twoTurnsMoveStringId;
    u8 animArg1;
    u8 animArg2;    //gBattleScripting +12 & +19 only used in multihit scripts in battle_scripts_1.s so somewhat confident of conclusions
    u16 tripleKickPower; //important gBattleScripting +19   //since changed move effect, can now remove this,   would need to update following values again
    u8 atk49_state; //move end
    u8 battlerWithAbility;
    //u8 multihitMoveEffect; //important, why do these need to go here   [they make up the table, if not properly orded bs effets won't work correctly
    u16 multihitMoveEffect; //why did I make u16?   -because it is in emerald
    u16 savedMoveEffect; // For moves hitting multiple targets.
    u16 moveEffect; //don't change capitalization won't be able to just copy from emerald easily
    u8 battler;
    u8 animTurn;
    u8 animTargetsHit;
    u8 statChanger;
    bool8 statAnimPlayed;
    u8 atk23_getexpState;
    u8 battleStyle;
    u8 atk6C_drawlvlupboxState;
    u8 learnMoveState;
    u8 field_25_pursuitDoublesAttacker; //pursuit damage  //not sure what htis does don't see it used and double damage is handled in script not with this value?
    u8 reshowMainState;
    u8 reshowHelperState;
    u8 savedStatChanger; // For if attempting to change stat two times(ex. Moody)
    u8 savedBattler;  //for now saveBattler not used just using normal sBattler - ported just in case there's issue

    /* u8 illusionNickHack; // To properly display nick in STRINGID_ENEMYABOUTTOSWITCHPKMN.
     bool8 fixedPopup;   // Force ability popup to stick until manually called back
     u16 abilityPopupOverwrite;  //UNCOMMENT if you want these features
     u16 savedMoveEffect; // For moves hitting multiple targets.
     u16 moveEffect;*/
    u8 switchCase;  // Special switching conditions, eg. red card
    u8 overrideBerryRequirements;
    u8 stickyWebStatDrop; // To prevent Defiant activating on a Court Change'd Sticky Web
    s32 savedDmg;   //port feature leaving out for now - added as needed for bs somehow
    //bool8 monCaught;  //believe most of these aren't needed, can be handled with battlescript , they are just different ways of doing things, btu I prefer saving ram.
    u8 field_23;    //used for hp change on level up & shedinja hp stuff in pokemon.c
};

enum
{
    BACK_PIC_RED,
    BACK_PIC_LEAF,
    BACK_PIC_RS_BRENDAN,
    BACK_PIC_RS_MAY,
    BACK_PIC_POKEDUDE,
    BACK_PIC_OLDMAN
};

struct BattleSpriteInfo
{
    /*0x0*/ u16 invisible : 1; // 0x1
            u16 lowHpSong : 1; // 0x2
            u16 behindSubstitute : 1; // 0x4
            u16 flag_x8 : 1; // 0x8
            u16 hpNumbersNoBars : 1; // 0x10
    /*0x2*/ u16 transformSpecies;
};

struct BattleAnimationInfo
{
    u16 animArg; // to fill up later
    u8 field_2;
    u8 field_3;
    u8 field_4;
    u8 field_5;
    u8 field_6;
    u8 field_7;
    u8 ballThrowCaseId;
    u8 healthboxSlideInStarted : 1;
    u8 field_9_x2 : 1;
    u8 field_9_x1C : 3;
    u8 field_9_x20 : 1;
    u8 field_9_x40 : 1;
    u8 field_9_x80 : 1;
    u8 field_A;
    u8 field_B;
    s16 field_C;
    u8 field_E;
    u8 field_F;
};

struct BattleHealthboxInfo
{
    u8 partyStatusSummaryShown : 1; // x1
    u8 healthboxIsBouncing : 1; // x2
    u8 battlerIsBouncing : 1; // x4
    u8 ballAnimActive : 1; // 0x8
    u8 statusAnimActive : 1; // x10
    u8 animFromTableActive : 1; // x20
    u8 specialAnimActive : 1; // x40
    u8 triedShinyMonAnim : 1; // x80
    u8 finishedShinyMonAnim : 1; // x1
    u8 opponentDrawPartyStatusSummaryDelay : 5; // x2
    u8 healthboxBounceSpriteId;
    u8 battlerBounceSpriteId;
    u8 animationState;
    u8 partyStatusDelayTimer;
    u8 matrixNum;
    u8 shadowSpriteId;
    u8 soundTimer;
    u8 introEndDelay;
};

struct BattleBarInfo
{
    u8 healthboxSpriteId;
    s32 maxValue;
    s32 oldValue;
    s32 receivedValue;
    s32 currValue;
};

struct BattleSpriteData
{
    struct BattleSpriteInfo *battlerData;
    struct BattleHealthboxInfo *healthBoxesData;
    struct BattleAnimationInfo *animationData;
    struct BattleBarInfo *battleBars;
};

extern struct BattleSpriteData *gBattleSpritesDataPtr;



// Move this somewhere else

#include "sprite.h"

struct MonSpritesGfx
{
    void* firstDecompressed; // ptr to the decompressed sprite of the first pokemon
    void* sprites[MAX_BATTLERS_COUNT];
    struct SpriteTemplate templates[MAX_BATTLERS_COUNT];
    struct SpriteFrameImage images[MAX_BATTLERS_COUNT][4];
    u8 field_F4[0x80]; // unused
    u8 *barFontGfx;
    void *field_178; // freed but never allocated
    u16 *multiUseBuffer;
};

struct PokedudeBattlerState
{
    u8 action_idx;
    u8 move_idx;
    u8 timer;
    u8 msg_idx;
    u8 saved_bg0y;
};

struct TotemBoost
{
    u8 stats;   // bitfield for each battle stat that is set if the stat changes
    s8 statChanges[NUM_BATTLE_STATS - 1];    // highest bit being set decreases the stat
}; /* size = 8 */

//put here to make non-static so can refer to in other files
//this is window used for battle move selection ui
extern const struct WindowTemplate sStandardBattleWindowTemplates[];

// All battle variables are declared in battle_main.c
extern u16 gBattle_BG0_X;
extern u16 gBattle_BG0_Y;
extern u16 gBattle_BG1_X;
extern u16 gBattle_BG1_Y;
extern u16 gBattle_BG2_X;
extern u16 gBattle_BG2_Y;
extern u16 gBattle_BG3_X;
extern u16 gBattle_BG3_Y;
extern u16 gBattle_WIN0H;
extern u16 gBattle_WIN0V;
extern u16 gBattle_WIN1H;
extern u16 gBattle_WIN1V;
extern struct BattleSpritesGfx *gMonSpritesGfx;
extern u8 gBattleOutcome;
extern u16 gLastUsedItem;
extern u32 gBattleTypeFlags;
extern struct MonSpritesGfx *gMonSpritesGfxPtr;
extern u16 gTrainerBattleOpponent_A;
extern u16 gTrainerBattleOpponent_B;
extern u16 gMoveToLearn;
extern u16 gBattleMovePower;
extern struct BattleEnigmaBerry gEnigmaBerries[MAX_BATTLERS_COUNT];
extern u16 gCurrentMove;
extern u16 gChosenMove;
extern u16 gCalledMove;
extern u8 gCritMultiplier;
extern u16 gBattleWeather;
extern u16 gLastUsedAbility;
extern u8 gBattlerInMenuId;
extern u8 gPotentialItemEffectBattler;
extern u8 gBattlersCount;
extern u16 gBattlerPartyIndexes[MAX_BATTLERS_COUNT];
extern s32 gBattleMoveDamage;
extern u16 gIntroSlideFlags;
extern u32 gTransformedPersonalities[MAX_BATTLERS_COUNT];
extern u8 gBattlerPositions[MAX_BATTLERS_COUNT];
extern u8 gHealthboxSpriteIds[MAX_BATTLERS_COUNT];
extern u8 gBattleOutcome;  //no idea why I had removed this
extern u8 gBattleMonForms[MAX_BATTLERS_COUNT];
extern void (*gBattlerControllerFuncs[MAX_BATTLERS_COUNT])(void);
extern u32 gBattleControllerExecFlags;
extern u8 gBattleBufferA[MAX_BATTLERS_COUNT][0x200];
extern u8 gBattleBufferB[MAX_BATTLERS_COUNT][0x200];
extern u8 gActionSelectionCursor[MAX_BATTLERS_COUNT];
extern void (*gPreBattleCallback1)(void);
extern bool8 gDoingBattleAnim;
extern struct PokedudeBattlerState *gPokedudeBattlerStates[MAX_BATTLERS_COUNT];
extern u8 *gBattleAnimMons_BgTilesBuffer;
extern u8 *gBattleAnimMons_BgTilemapBuffer;
extern void (*gBattleMainFunc)(void);
extern u8 gMoveSelectionCursor[MAX_BATTLERS_COUNT];
extern u32 gUnknown_2022B54;
extern u8 gUnknown_2023DDC;
extern u8 gAnticipatedBattler;  //for storing battlerId of anticipation target   unsure if need max battler array thing [MAX_BATTLERS_COUNT];
extern u8 gForewarnedBattler;   //for storing battlerId of forewarn target
extern u8 gBattlerAttacker;
extern u8 gEffectBattler;
extern u8 gMultiHitCounter;
extern u8 gMultiTask;
extern struct BattleScripting gBattleScripting;
extern u8 gBattlerFainted;
extern u32 gStatuses3[MAX_BATTLERS_COUNT];
extern u32 gStatuses4[MAX_BATTLERS_COUNT];
extern u8 gSentPokesToOpponent[2];
extern const u8 *gBattlescriptCurrInstr;
extern const u8 *gSelectionBattleScripts[MAX_BATTLERS_COUNT];
extern u16 gLastMoves[MAX_BATTLERS_COUNT];
extern u8 gBattlerByTurnOrder[MAX_BATTLERS_COUNT];
extern u8 gBattleCommunication[BATTLE_COMMUNICATION_ENTRIES_COUNT];
extern u32 gSideStatuses[2];    //upgraded from u16, because of increase in side status flags
extern u32 gHitMarker;
extern u16 gChosenMoveByBattler[MAX_BATTLERS_COUNT];
extern u8 gMoveResultFlags;
extern s32 gTakenDmg[MAX_BATTLERS_COUNT];
extern u8 gTakenDmgByBattler[MAX_BATTLERS_COUNT];
extern u8 gCurrentActionFuncId;
extern u8 gCurrMovePos;
extern u8 gChosenMovePos;
extern u8 gBattleControllerData[MAX_BATTLERS_COUNT];
extern u8 gBattlerStatusSummaryTaskId[MAX_BATTLERS_COUNT];
extern u16 gDynamicBasePower;
extern u32 gFieldStatuses;
extern struct FieldTimer gFieldTimers; //both needed for things like gravity etc.  //can apparently hold more than one effect at once?
extern bool8 gHasFetchedBall;
extern u8 gLastUsedBall;
extern u16 gLastThrownBall;
extern bool8 gSwapDamageCategory; // Photon Geyser, Shell Side Arm, Light That Burns the Sky
extern u16 gLastLandedMoves[MAX_BATTLERS_COUNT];
extern u8 gLastHitBy[MAX_BATTLERS_COUNT];
extern u8 gMultiUsePlayerCursor;
extern u8 gNumberOfMovesToChoose;
extern u16 gLastHitByType[MAX_BATTLERS_COUNT];
extern struct TotemBoost gTotemBoosts[MAX_BATTLERS_COUNT];
extern s32 gHpDealt;
extern u16 gPauseCounterBattle;
extern u16 gPaydayMoney;
extern u16 gLockedMoves[MAX_BATTLERS_COUNT];
extern u16 gLastUsedMove;
extern u8 gCurrentTurnActionNumber;
extern struct BattleResources *gBattleResources;
extern u16 gExpShareExp;
extern u8 gLeveledUpInBattle;
extern u16 gLastResultingMoves[MAX_BATTLERS_COUNT];
extern u16 gLastPrintedMoves[MAX_BATTLERS_COUNT];
extern u8 gActionsByTurnOrder[MAX_BATTLERS_COUNT];
extern u8 gChosenActionByBattler[MAX_BATTLERS_COUNT];
extern u8 gBattleTerrain;
extern struct MultiBattlePokemonTx gMultiPartnerParty[3];
extern u16 gRandomTurnNumber;

#endif // GUARD_BATTLE_H
