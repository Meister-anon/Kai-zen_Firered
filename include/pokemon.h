#ifndef GUARD_POKEMON_H
#define GUARD_POKEMON_H

#include "global.h"
#include "sprite.h"
#include "constants/pokemon.h"
#include "pokemon_storage_system.h"

#define GET_BASE_SPECIES_ID(speciesId) (GetFormSpeciesId(speciesId, 0))

struct PokemonSubstruct0
{
    u16 species;
    u16 heldItem;
    u32 experience;
    u8 ppBonuses;
    u8 friendship;
};

struct PokemonSubstruct1
{
    u16 moves[4];
    u8 pp[4];
};

struct PokemonSubstruct2
{
    u8 hpEV;
    u8 attackEV;
    u8 defenseEV;
    u8 speedEV;
    u8 spAttackEV;
    u8 spDefenseEV;
    u8 cool;
    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;
    u8 sheen;
};

struct PokemonSubstruct3
{
 /* 0x00 */ u8 pokerus;
 /* 0x01 */ u8 metLocation;

 /* 0x02 */ u16 metLevel:7;
 /* 0x02 */ u16 metGame:4;
 /* 0x03 */ u16 pokeball:4;
 /* 0x03 */ u16 otGender:1;

 /* 0x04 */ u32 hpIV:5;
 /* 0x04 */ u32 attackIV:5;
 /* 0x05 */ u32 defenseIV:5;
 /* 0x05 */ u32 speedIV:5;
 /* 0x05 */ u32 spAttackIV:5;
 /* 0x06 */ u32 spDefenseIV:5; //changed abilityNum to 3, so I can get the second hidden ability slot.
 /* 0x07 */ u32 isEgg:1;
 /* 0x07 */ u32 abilityNum:2; // allability num are 2 in emerald. so that is the right call //  yeah didn't understand bit fields 2 is correct

 /* 0x08 */ u32 coolRibbon:3;
 /* 0x08 */ u32 beautyRibbon:3; //having this be 3 seems to correspond to 4 options, which matches the above's 3 ability options of 2 slots and 1 hidden.
 /* 0x08 */ u32 cuteRibbon:3;
 /* 0x09 */ u32 smartRibbon:3;
 /* 0x09 */ u32 toughRibbon:3;
 /* 0x09 */ u32 championRibbon:1;
 /* 0x0A */ u32 winningRibbon:1;
 /* 0x0A */ u32 victoryRibbon:1;
 /* 0x0A */ u32 artistRibbon:1;
 /* 0x0A */ u32 effortRibbon:1;
 /* 0x0B */ u32 nationalRibbon:1;
 /* 0x0B */ u32 earthRibbon:1;
 /* 0x0B */ u32 filler:4;
 /* 0x0B */ u32 eventLegal:1; // controls Mew & Deoxys obedience; if set, Pokémon is a fateful encounter in FRLG & Gen 4+ summary screens; set for in-game event island legendaries, some distributed events, and Pokémon from XD: Gale of Darkness.
};

union PokemonSubstruct
{
    struct PokemonSubstruct0 type0;
    struct PokemonSubstruct1 type1;
    struct PokemonSubstruct2 type2;
    struct PokemonSubstruct3 type3;
    u16 raw[6];
};

struct BoxPokemon
{
    u32 personality;
    u32 otId;
    u8 nickname[POKEMON_NAME_LENGTH];
    u8 language;
    u8 isBadEgg:1;
    u8 hasSpecies:1;
    u8 isEgg:1;
    u8 unused:5;
    u8 otName[OT_NAME_LENGTH];
    //u8 markings;
    u16 checksum;
    u16 unknown;

    union
    {
        u32 raw[12];
        union PokemonSubstruct substructs[4];
    } secure;
};

struct Pokemon
{
    struct BoxPokemon box;
    u32 status;
    u8 level;
    //u8 mail;
    u16 hp;
    u16 maxHP;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
};

struct PokemonStorage
{
    /*0x0000*/ u8 currentBox;
    /*0x0001*/ struct BoxPokemon boxes[TOTAL_BOXES_COUNT][IN_BOX_COUNT];
    /*0x8344*/ u8 boxNames[TOTAL_BOXES_COUNT][BOX_NAME_LENGTH + 1];
    /*0x83C2*/ u8 boxWallpapers[TOTAL_BOXES_COUNT]; //when I'm able to expand box counts give this its own separate constant won't need 
};  //a unique wall paper for each box, could even remove some of the wall papers I don't like/no one likes

struct BattleTowerPokemon //apparently used for both battle tower leftover from emerald, AND trainer tower, on sevii island
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 heldItem;
    /*0x04*/ u16 moves[4];
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 ppBonuses;
    /*0x0E*/ u8 hpEV;
    /*0x0F*/ u8 attackEV;
    /*0x10*/ u8 defenseEV;
    /*0x11*/ u8 speedEV;
    /*0x12*/ u8 spAttackEV;
    /*0x13*/ u8 spDefenseEV;
    /*0x14*/ u32 otId;  //if I need to could remove this? I think this is only for the enemy party data, so idk if this is necessary? oh wait that's combined with personality to determine nature?
    /*0x18*/ u32 hpIV:5; //I think this also goes into createmon function used in battle_main.c createtrainerparty if able to set fixed nature can remove otId & personality then
             u32 attackIV:5; //nmv also sets gender
             u32 defenseIV:5;
             u32 speedIV:5;
             u32 spAttackIV:5; //since its restricting to bits, it doesn't much matter the type
             u32 spDefenseIV:5;
             u32 gap:1;
             u16 abilityNum:2;  //didn't properly understand bit fields, each bit stores 2 values so rather than 3 I only need 2 for 4 abilities ? i.e 0-3
    /*0x1C*/ u32 personality:8;  //personality values only go up to 0x96 so think can use bitfield o
    /*0x20*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x2B*/ u8 friendship; //used for frustration and return, exists in either 0 or 255
}; //don't need to change anything foud more space by removing ereader stuff

#define BATTLE_STATS_NO 8

struct BattlePokemon
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 attack;
    /*0x04*/ u16 defense;
    /*0x06*/ u16 speed;
    /*0x08*/ u16 spAttack;
    /*0x0A*/ u16 spDefense;
    /*0x0C*/ u16 moves[4];
    /*0x14*/ u32 hpIV:5;
    /*0x14*/ u32 attackIV:5;
    /*0x15*/ u32 defenseIV:5;
    /*0x15*/ u32 speedIV:5;
    /*0x16*/ u32 spAttackIV:5;
    /*0x17*/ u32 spDefenseIV:5;
    /*0x17*/ u32 isEgg:1;
    /*0x17*/ u32 abilityNum:2;
    /*0x18*/ s8 statStages[BATTLE_STATS_NO];
    /*0x20*/ u16 ability;
    /*0x21*/ u8 type1;
    /*0x22*/ u8 type2;
    /*0x23*/ u8 type3; //no space change replaced unknown
    /*0x24*/ u8 pp[4];
    /*0x28*/ u16 hp;
    /*0x2A*/ u8 level;
    /*0x2B*/ u8 friendship;
    /*0x2C*/ u16 maxHP;
    /*0x2E*/ u16 item;
    /*0x30*/ u8 nickname[POKEMON_NAME_LENGTH + 1];
    /*0x3B*/ u8 ppBonuses;
    /*0x3C*/ u8 otName[8];
    /*0x44*/ u32 experience;
    /*0x48*/ u32 personality;
    /*0x4C*/ u32 status1;   //stays on switch
    /*0x50*/ u32 status2;   //temp status lost on switch
    /*0x54*/ u32 status4;   //new addition  for new statuses mostly for new wrap effects, plan to make equivalent of status2
    /*0x58*/ u32 otId; //may not need status4 in struct status3 & 4 seem to work through gstatuses3 & gstatus4 the same as status 2 already?
};

struct BaseStats  // had to adjust struct order to match paste value from base_stats.h
{
 /* 0x00 */ u8 baseHP;
 /* 0x01 */ u8 baseAttack;
 /* 0x02 */ u8 baseDefense;
 /* 0x03 */ u8 baseSpeed;
 /* 0x04 */ u8 baseSpAttack;
 /* 0x05 */ u8 baseSpDefense;
 /* 0x06 */ u8 type1;
 /* 0x07 */ u8 type2;
 /* 0x08 */ u8 catchRate;
 /* 0x09 */ u16 expYield;
 /* 0x0A */ //u16 evYield_HP:2; //not using these so might as well remove from struct to save room
 /* 0x0A */ //u16 evYield_Attack:2;
 /* 0x0A */ //u16 evYield_Defense:2;
 /* 0x0A */ //u16 evYield_Speed:2;
 /* 0x0B */ //u16 evYield_SpAttack:2;
 /* 0x0B */ //u16 evYield_SpDefense:2;
 /* 0x0C */ u16 item1;
 /* 0x0E */ u16 item2;
 /* 0x10 */ u8 genderRatio;
 /* 0x11 */ u8 eggCycles;
 /* 0x12 */ u8 friendship;
 /* 0x13 */ u8 growthRate;
 /* 0x14 */ u8 eggGroup1;
 /* 0x15 */ u8 eggGroup2;
 /* 0x16 */ u16 abilities[2]; //[partysize] is 6 values, so this is ability 1 and ability 2, doesn't include hidden //this means 2 states, 0 & 1
 /* 0x1A */ u8 safariZoneFleeRate;
 /* 0x1B */ u16 abilityHidden[2]; //need to make sure ability num can be 2, then set that as hidden ability
 /* 0x1D */ u8 bodyColor : 7;
            u8 noFlip : 1;
 /* 0x1E */ u8 flags;
};

struct BattleMove
{
    u16 effect;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 secondaryEffectChance;
    u16 target;
    s8 priority;
    u32 flags; // is u32 in emerald, might not need to do that, will ask //they use a lot of move flags will update
    u8 split;
    u16 argument;// for transferring move effects
    u8 argumentEffectChance; // setup status commands and seteffectwithchance function to read this as a value explicitly for argument
    //would possibly need to redo setup for effects that become certain without reading effectchance nvm it works 
    //Argument works by passive value of argument to battlescript.moveeffect
    //so just do a check in seteffectwithchance that checks if  battlescripting.moveeffect equals gbattlemons[move].effect or the argument
    //if it equals the argument use argument chance, that means it has already done the effect
    //and has passed the arugment over so it can use the argument chance
};//without u32 flags, type overflowed with added moves
//argument is for extra effects other than secondary effect

extern const struct BattleMove gBattleMoves[];

#define IS_CRIT (gCritMultiplier > 1)

/*
#define FLAG_MAKES_CONTACT          0x1
#define FLAG_PROTECT_AFFECTED       0x2
#define FLAG_MAGIC_COAT_AFFECTED     0x4
#define FLAG_SNATCH_AFFECTED        0x8
#define FLAG_MIRROR_MOVE_AFFECTED   0x10
#define FLAG_KINGS_ROCK_AFFECTED     0x20*/

// Battle move flags
#define FLAG_MAKES_CONTACT          (1 << 0)
#define FLAG_PROTECT_AFFECTED       (1 << 1)
#define FLAG_MAGIC_COAT_AFFECTED    (1 << 2)
#define FLAG_SNATCH_AFFECTED        (1 << 3)
#define FLAG_MIRROR_MOVE_AFFECTED   (1 << 4)
#define FLAG_KINGS_ROCK_AFFECTED    (1 << 5)
#define FLAG_HIGH_CRIT              (1 << 6)
#define FLAG_RECKLESS_BOOST         (1 << 7)
#define FLAG_IRON_FIST_BOOST        (1 << 8)
#define FLAG_SHEER_FORCE_BOOST      (1 << 9)
#define FLAG_STRONG_JAW_BOOST       (1 << 10)
#define FLAG_MEGA_LAUNCHER_BOOST    (1 << 11)
#define FLAG_STAT_STAGES_IGNORED    (1 << 12)
#define FLAG_DMG_MINIMIZE           (1 << 13)
#define FLAG_DMG_UNDERGROUND        (1 << 14)
#define FLAG_DMG_UNDERWATER         (1 << 15)
#define FLAG_SOUND                  (1 << 16)
#define FLAG_BALLISTIC              (1 << 17)
#define FLAG_PROTECTION_MOVE        (1 << 18)
#define FLAG_POWDER                 (1 << 19)
#define FLAG_TARGET_ABILITY_IGNORED (1 << 20)
#define FLAG_DANCE                  (1 << 21)
#define FLAG_DMG_2X_IN_AIR          (1 << 22) // If target is in the air, can hit and deal double damage.
#define FLAG_DMG_IN_AIR             (1 << 23) // If target is in the air, can hit.
#define FLAG_DMG_UNGROUNDED_IGNORE_TYPE_IF_FLYING (1 << 24) // Makes a Ground type move do 1x damage to flying and levitating targets
#define FLAG_THAW_USER                            (1 << 25)
#define FLAG_HIT_IN_SUBSTITUTE                    (1 << 26) // Hyperspace Fury
#define FLAG_TWO_STRIKES                          (1 << 27) // A move with this flag will strike twice, and may apply its effect on each hit
#define FLAG_ROCK_HEAD_BOOST    (1 << 28)   //EQUIvalent iron fist will boost moves that used head

#define SPINDA_SPOT_HEIGHT 16

struct SpindaSpot
{
    u8 x, y;
    u16 image[SPINDA_SPOT_HEIGHT];
};

struct LevelUpMove
{
    u16 move;
    u16 level;
};

enum
{
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW
};

enum
{
    BODY_COLOR_RED,
    BODY_COLOR_BLUE,
    BODY_COLOR_YELLOW,
    BODY_COLOR_GREEN,
    BODY_COLOR_BLACK,
    BODY_COLOR_BROWN,
    BODY_COLOR_PURPLE,
    BODY_COLOR_GRAY,
    BODY_COLOR_WHITE,
    BODY_COLOR_PINK
};

#define EVO_FRIENDSHIP       				0x0001 // Pokémon levels up with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_FRIENDSHIP_DAY   				0x0002 // Pokémon levels up during the day with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_FRIENDSHIP_NIGHT 				0x0003 // Pokémon levels up at night with friendship ≥ FRIENDSHIP_EVO_LIMITER
#define EVO_LEVEL            				0x0004 // Pokémon reaches the specified level
#define EVO_TRADE            				0x0005 // Pokémon is traded
#define EVO_TRADE_ITEM       				0x0006 // Pokémon is traded while it's holding the specified item
#define EVO_ITEM             				0x0007 // specified item is used on Pokémon
#define EVO_LEVEL_ATK_GT_DEF 				0x0008 // Pokémon reaches the specified level with attack > defense
#define EVO_LEVEL_ATK_EQ_DEF 				0x0009 // Pokémon reaches the specified level with attack = defense
#define EVO_LEVEL_ATK_LT_DEF 				0x000a // Pokémon reaches the specified level with attack < defense
#define EVO_LEVEL_SILCOON    				0x000b // Pokémon reaches the specified level with a Silcoon personality value
#define EVO_LEVEL_CASCOON    				0x000c // Pokémon reaches the specified level with a Cascoon personality value
#define EVO_LEVEL_NINJASK    				0x000d // Pokémon reaches the specified level (special value for Ninjask)
#define EVO_LEVEL_SHEDINJA   				0x000e // Pokémon reaches the specified level (special value for Shedinja)
#define EVO_BEAUTY   		   				0x000f // Pokémon levels up with beauty ≥ specified value
#define EVO_LEVEL_FEMALE     				0x0010 // Pokémon reaches the specified level, is female
#define EVO_LEVEL_MALE      				0x0011 // Pokémon reaches the specified level, is male
#define EVO_LEVEL_NIGHT     				0x0012 // Pokémon reaches the specified level, is night
#define EVO_LEVEL_DAY       				0x0013 // Pokémon reaches the specified level, is day
#define EVO_LEVEL_DUSK      				0x0014 // Pokémon reaches the specified level, is dusk (5-6 P.M)
#define EVO_ITEM_HOLD  		    		    0x0027 // Pokémon levels up, holds specified item
#define EVO_ITEM_HOLD_DAY  		    		0x0015 // Pokémon levels up, holds specified item at day
#define EVO_ITEM_HOLD_NIGHT 				0x0016 // Pokémon levels up, holds specified item at night
#define EVO_MOVE           			    	0x0017 // Pokémon levels up, knows specified move
#define EVO_MOVE_TYPE       				0x0018 // Pokémon levels up, knows move with specified type
#define EVO_MAPSEC          				0x0019 // Pokémon levels up on specified mapsec
#define EVO_ITEM_MALE      				    0x001a // specified item is used on a male Pokémon
#define EVO_ITEM_FEMALE    				    0x001b // specified item is used on a female Pokémon
#define EVO_LEVEL_RAIN     				    0x001c // Pokémon reaches the specified level while it's raining
#define EVO_SPECIFIC_MON_IN_PARTY         	0x001d // Pokémon levels up with a specified Pokémon in party
#define EVO_SPECIFIC_TYPE_IN_PARTY         	0x001e // Pokémon levels up with a specified Pokémon Type in party (made to bypass nosepass evo location requirement)
#define EVO_LEVEL_DARK_TYPE_MON_IN_PARTY    0x001f // Pokémon reaches the specified level with a Dark Type Pokémon in party
#define EVO_LEVEL_KARRABLAST                0x0020 // Pokémon reaches the specified level (special value for Karrablast)
#define EVO_LEVEL_SHELMET                   0x0021 // Pokémon reaches the specified level (special value for Shelmet)
#define EVO_TRADE_SPECIFIC_MON   			0x0022 // Pokémon is traded for a specified Pokémon
#define EVO_SPECIFIC_MAP   				    0x0023 // Pokémon levels up in a specific room of a specified map.
#define EVO_MEGA_EVOLUTION					0x0024 // (change later)Not an actual evolution, used to temporarily mega evolve in battle.
#define EVO_MOVE_MEGA_EVOLUTION		        0x0025 // Mega Evolution that checks for a move instead of held item
#define EVO_PRIMAL_REVERSION                0x0026// Not an actual evolution, used to undergo primal reversion in battle.
#define EVO_LEVEL_NATURE_AMPED              0x0028     // Pokémon reaches the specified level, it has a Hardy, Brave, Adamant, Naughty, Docile, Impish, Lax, Hasty, Jolly, Naive, Rash, Sassy, or Quirky nature.
#define EVO_LEVEL_NATURE_LOW_KEY            0x0029     // Pokémon reaches the specified level, it has a Lonely, Bold, Relaxed, Timid, Serious, Modest, Mild, Quiet, Bashful, Calm, Gentle, or Careful nature.
#define EVO_CRITICAL_HITS                   0x002a     // Pokémon performs specified number of critical hits in one battle
#define EVO_SCRIPT_TRIGGER_DMG              0x002b     // Pokémon has specified HP below max, then player interacts trigger
#define EVO_DARK_SCROLL                     0x002c     // interacts with Scroll of Darkness
#define EVO_WATER_SCROLL                    0x002d     // interacts with Scroll of Waters

struct Evolution
{
    u16 method;
    u16 param;
    u16 targetSpecies;
};

struct FormChange {
    u16 method;
    u16 targetSpecies;
    u16 param1;
    u16 param2;
}; //may change based on how I use forms

#define EVOS_PER_MON 16 // set to 16 in case I need the shedinja byte change fix
#define FORMS_PER_MON 5 //for breeding


#define RATTATA_EVO_LINE SPECIES_RATTATA || SPECIES_RATICATE

#define PIKACHU_EVO_LINE SPECIES_PIKACHU || SPECIES_RAICHU

#define SANDSHREW_EVO_LINE SPECIES_SANDSHREW || SPECIES_SANDSLASH

#define VULPIX_EVO_LINE SPECIES_VULPIX || SPECIES_NINETALES

#define DIGLETT_EVO_LINE SPECIES_DIGLETT || SPECIES_DUGTRIO

#define MEOWTH_EVO_LINE SPECIES_MEOWTH || SPECIES_PERSIAN //(meowth has 2 form, persian 1 just alolan)

#define GEODUDE_EVO_LINE SPECIES_GEODUDE || SPECIES_GRAVELER || SPECIES_GOLEM

#define PONYTA_EVO_LINE SPECIES_PONYTA || SPECIES_RAPIDASH

#define SLOWPOKE_EVO_LINE SPECIES_SLOWPOKE || SPECIES_SLOWBRO || SPECIES_SLOWKING

#define FARFETCHD_EVO_LINE SPECIES_FARFETCHD

#define GRIMER_EVO_LINE SPECIES_GRIMER || SPECIES_MUK

#define EXEGGCUTE_EVO_LINE SPECIES_EXEGGCUTE || SPECIES_EXEGGUTOR

#define CUBONE_EVO_LINE SPECIES_CUBONE || SPECIES_MAROWAK

#define KOFFING_EVO_LINE SPECIES_KOFFING || SPECIES_WEEZING

#define MR_MIME_EVO_LINE SPECIES_MR_MIME

#define CORSOLA_EVO_LINE SPECIES_CORSOLA

#define ZIGZAGOON_EVO_LINE SPECIES_ZIGZAGOON || SPECIES_LINOONE

#define DARUMAKA_EVO_LINE SPECIES_DARUMAKA || SPECIES_DARMANITAN || SPECIES_DARMANITAN_ZEN_MODE

#define YAMASK_EVO_LINE SPECIES_YAMASK || SPECIES_COFAGRIGUS

#define STUNFISK_EVO_LINE SPECIES_STUNFISK

struct Breeding
{
    u16 evo_line; //template name, looked at daycare function and will have to related it to my start species
    u16 method; // based either on father type (may call pedigree) or held item, (may call affinity)  //both are based on the type of the target form i.e dark for alola rattata
    u16 param;  //specific value for the method
    u16 targetSpecies; //egg species
};



extern u8 gPlayerPartyCount;
extern struct Pokemon gPlayerParty[PARTY_SIZE];
extern u8 gEnemyPartyCount;
extern struct Pokemon gEnemyParty[PARTY_SIZE];
extern const struct BaseStats gBaseStats[];
extern const u8 *const gItemEffectTable[];
extern const struct Evolution gEvolutionTable[][EVOS_PER_MON];
extern const struct Breeding gBreedingTable[][FORMS_PER_MON]; //important second bracket is num rows/forms, 
extern const u8 gStatStageRatios[][2]; //start with 5 expand as needed
extern struct SpriteTemplate gMultiuseSpriteTemplate;
extern struct PokemonStorage* gPokemonStoragePtr;
extern const u32 gExperienceTables[][MAX_LEVEL + 1];
extern const struct LevelUpMove *const gLevelUpLearnsets[];
extern const u8 gFacilityClassToPicIndex[];
extern const u8 gFacilityClassToTrainerClass[];
extern const struct SpriteTemplate gSpriteTemplates_Battlers[];
extern const u8 gPPUpGetMask[];
extern const u16 *const gFormSpeciesIdTables[NUM_SPECIES];

void ZeroBoxMonData(struct BoxPokemon *boxMon);
void ZeroMonData(struct Pokemon *mon);
void ZeroPlayerPartyMons(void);
void ZeroEnemyPartyMons(void);
void CreateMon(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId);
void CreateBoxMon(struct BoxPokemon *boxMon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId);
void CreateMonWithNature(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 nature);
void CreateMonWithGenderNatureLetter(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 gender, u8 nature, u8 unownLetter);
void CreateMaleMon(struct Pokemon *mon, u16 species, u8 level);
void CreateMonWithIVsPersonality(struct Pokemon *mon, u16 species, u8 level, u32 ivs, u32 personality);
void CreateMonWithEVSpread(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 evSpread);
void CreateBattleTowerMon(struct Pokemon *mon, struct BattleTowerPokemon *src);
void ConvertPokemonToBattleTowerPokemon(struct Pokemon *mon, struct BattleTowerPokemon *dest);
void CalculateMonStats(struct Pokemon *mon);
void TransformedMonStats(struct Pokemon *mon);
void BoxMonToMon(struct BoxPokemon *src, struct Pokemon *dest);
u8 GetLevelFromBoxMonExp(struct BoxPokemon *boxMon);
u16 GiveMoveToMon(struct Pokemon *mon, u16 move);
u16 GiveMoveToBattleMon(struct BattlePokemon *mon, u16 move);
void SetMonMoveSlot(struct Pokemon *mon, u16 move, u8 slot);
void SetBattleMonMoveSlot(struct BattlePokemon *mon, u16 move, u8 slot);
u16 MonTryLearningNewMove(struct Pokemon *mon, bool8 firstMove);
void DeleteFirstMoveAndGiveMoveToMon(struct Pokemon *mon, u16 move);
s32 CalculateBaseDamage(struct BattlePokemon *attacker, struct BattlePokemon *defender, u32 move, u16 sideStatus, u16 powerOverride, u8 typeOverride, u8 battlerIdAtk, u8 battlerIdDef);

#define BATTLE_ALIVE_EXCEPT_ACTIVE  0
#define BATTLE_ALIVE_ATK_SIDE       1
#define BATTLE_ALIVE_DEF_SIDE       2

u8 CountAliveMonsInBattle(u8 caseId);

u8 GetDefaultMoveTarget(u8 battlerId);
u8 GetMonGender(struct Pokemon *mon);
u8 GetBoxMonGender(struct BoxPokemon *boxMon);
u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality);
void SetMultiuseSpriteTemplateToPokemon(u16 speciesTag, u8 battlerPosition);
void SetMultiuseSpriteTemplateToTrainerBack(u16 trainerSpriteId, u8 battlerPosition);

// These are full type signatures for GetMonData() and GetBoxMonData(),
// but they are not used since some code erroneously omits the third arg.
// u32 GetMonData(struct Pokemon *mon, s32 field, u8 *data);
// u32 GetBoxMonData(struct BoxPokemon *boxMon, s32 field, u8 *data);
/**/
#ifdef IS_POKEMON_C
u32 GetMonData(struct Pokemon *, s32, u8 *);
u32 GetBoxMonData(struct BoxPokemon *, s32, u8 *);
#else
u32 GetMonData();
u32 GetBoxMonData();
#endif // IS_POKEMON_C  seems like removing this was what made it work?
//*/ 
void SetMonData(struct Pokemon *mon, s32 field, const void *dataArg);
void SetBoxMonData(struct BoxPokemon *boxMon, s32 field, const void *dataArg);
void CopyMon(void *dest, void *src, size_t size);
u8 GiveMonToPlayer(struct Pokemon *mon);
void GiveMonInitialMoveset(struct Pokemon *mon);
void GiveBoxMonInitialMoveset(struct BoxPokemon *boxMon);   //moved these defins here so could use in battle_main
u8 CalculatePlayerPartyCount(void);
u8 CalculateEnemyPartyCount(void);
u8 GetMonsStateToDoubles(void);
u16 GetAbilityBySpecies(u16 species, u8 abilityNum);    //since abilityNum can go to 4, removed bool for u
u16 GetMonAbility(struct Pokemon *mon);
bool32 IsMonType(struct Pokemon *mon, u8 type); //uses get mondata species to check mon type from base stats, not battle type,  used for field poison
//u8 GetSecretBaseTrainerPicIndex(void); 
//u8 GetSecretBaseTrainerNameIndex(void);
bool8 IsPlayerPartyAndPokemonStorageFull(void);
void GetSpeciesName(u8 *name, u16 species);
u8 CalculatePPWithBonus(u16 move, u8 ppBonuses, u8 moveIndex);
void RemoveMonPPBonus(struct Pokemon *mon, u8 moveIndex);
void RemoveBattleMonPPBonus(struct BattlePokemon *mon, u8 moveIndex);
bool8 ExecuteTableBasedItemEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex);
bool8 PokemonUseItemEffects(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex, u8 e);
bool8 PokemonItemUseNoEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex);
u8 GetItemEffectParamOffset(u16 itemId, u8 effectByte, u8 effectBit);
const u8 *Battle_PrintStatBoosterEffectMessage(u16 itemId);
u8 GetNature(struct Pokemon *mon);
u16 GetEvolutionTargetSpecies(struct Pokemon *mon, u8 type, u16 evolutionItem);
u16 NationalPokedexNumToSpecies(u16 nationalNum);
u16 SpeciesToNationalPokedexNum(u16 species);
u16 HoennToNationalOrder(u16 hoennNum);
u16 SpeciesToCryId(u16 species);
void DrawSpindaSpots(u16 species, u32 personality, u8 *dest, bool8 isFrontPic);
void EvolutionRenameMon(struct Pokemon *mon, u16 oldSpecies, u16 newSpecies);
bool8 GetPlayerFlankId(void);
bool16 GetLinkTrainerFlankId(u8 linkPlayerId);
s32 GetBattlerMultiplayerId(u16 a1);
u8 GetTrainerEncounterMusicId(u16 trainer);
void AdjustFriendship(struct Pokemon *mon, u8 event);
void MonGainEVs(struct Pokemon *mon, u16 defeatedSpecies);
u16 GetMonEVCount(struct Pokemon *mon);
void RandomlyGivePartyPokerus(struct Pokemon *party);
u8 CheckPartyPokerus(struct Pokemon *party, u8 selection);
u8 CheckPartyHasHadPokerus(struct Pokemon *party, u8 selection);
void PartySpreadPokerus(struct Pokemon *party);
bool8 TryIncrementMonLevel(struct Pokemon *mon);
u32 CanMonLearnTMHM(struct Pokemon *mon, u8 tm);
u8 GetMoveRelearnerMoves(struct Pokemon *mon, u16 *moves);
u8 GetLevelUpMovesBySpecies(u16 species, u16 *moves);
u8 GetNumberOfRelearnableMoves(struct Pokemon *mon);
u16 SpeciesToPokedexNum(u16 species);
void ClearBattleMonForms(void);
void PlayBattleBGM(void);
void PlayMapChosenOrBattleBGM(u16 songId);
const u32 *GetMonFrontSpritePal(struct Pokemon *mon);
const u32 *GetMonSpritePalFromSpeciesAndPersonality(u16 species, u32 otId, u32 personality);
const struct CompressedSpritePalette *GetMonSpritePalStruct(struct Pokemon *mon);
const struct CompressedSpritePalette *GetMonSpritePalStructFromOtIdPersonality(u16 species, u32 otId , u32 personality);
bool32 IsHMMove2(u16 move);
bool8 IsPokeSpriteNotFlipped(u16 species);
s8 GetFlavorRelationByPersonality(u32 personality, u8 flavor);
bool8 IsTradedMon(struct Pokemon *mon);
bool8 IsOtherTrainer(u32 otId, u8 *otName);
void MonRestorePP(struct Pokemon *mon);
void BoxMonRestorePP(struct BoxPokemon *boxMon);
void SetMonPreventsSwitchingString(void);
void SetWildMonHeldItem(void);
bool8 IsMonShiny(struct Pokemon *mon);
u8 *GetTrainerPartnerName(void);
u8 GetPlayerPartyHighestLevel(void);
u16 FacilityClassToPicIndex(u16 facilityClass);
bool8 ShouldIgnoreDeoxysForm(u8 caseId, u8 battlerId);
void SetDeoxysStats(void);
u16 GetUnionRoomTrainerPic(void);
u16 GetUnionRoomTrainerClass(void);
void CreateEventLegalEnemyMon(void);
void HandleSetPokedexFlag(u16 nationalNum, u8 caseId, u32 personality);
bool8 CheckBattleTypeGhost(struct Pokemon *mon, u8 bank);
struct OakSpeechNidoranFStruct *OakSpeechNidoranFSetup(u8 battlePosition, bool8 enable);
void OakSpeechNidoranFFreeResources(void);
void *OakSpeechNidoranFGetBuffer(u8 bufferId);

u16 GetFormSpeciesId(u16 speciesId, u8 formId);
u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId);

void PokemonToBattleMon(struct Pokemon *src, struct BattlePokemon *dst);

#define HOLD_EFFECT_POWERITEM    (HOLD_EFFECT_POWER_WEIGHT || HOLD_EFFECT_POWER_BRACER || HOLD_EFFECT_POWER_BELT || HOLD_EFFECT_POWER_ANKLET || HOLD_EFFECT_POWER_LENS || HOLD_EFFECT_POWER_BAND)

#endif // GUARD_POKEMON_H
