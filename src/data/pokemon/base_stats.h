// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define STATS(hp, atk, def, speed, spAtk, spDef) \
.baseHP        = (hp), \
.baseAttack    = (atk), \
.baseDefense   = (def), \
.baseSpeed     = (speed), \
.baseSpAttack  = (spAtk), \
.baseSpDefense = (spDef), \
.statTotal = (hp) + (atk) + (def) + (speed) + (spAtk) + (spDef)

//added from emerald expansion so everyone has flags and abilities.
//but I forgot that removes safariZoneFleeRate so need to add that back for first 151 or so.

/*... ok the paste upest more than just catch rate, its devoid the item fields and evYields
*my stats values should look like this, based on my struct
* 
* actually... it isn't missing anything, but safari flee rate.
it just leaves the spot for the values blank
if it would otherwise be 0/NONE except in the case of ability.
* 
* 
[SPECIES_BULBASAUR] =
    {
        .baseHP = 45,
        .baseAttack = 49,
        .baseDefense = 49,
        .baseSpeed = 45,
        .baseSpAttack = 65,
        .baseSpDefense = 65,
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_HP = 0,
        //.evYield_Attack = 0,
        //.evYield_Defense = 0,
        //.evYield_Speed = 0,
        //.evYield_SpAttack = 0,
        //.evYield_SpDefense = 0,
        //.item1 = ITEM_NONE,
        //.item2 = ITEM_NONE,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE },
        .safariZoneFleeRate = 0,
        .abilityHidden = {ABILITY_CHLOROPHYLL,
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flag = NONE  // or I could leave the flag off
    },
*/
//finished adding safari stuff, just remember to add the flee rate 
//if I plan to add more pokemon to safari zone.

//may need add flag to every pokemon, so can set it as evo case, i.e pokemon with this flag, can evolve to this variant.
//added flag field, think will also use the flag for exp share and ev item boost, so don't need to waste held item slot
//part of setting it up like opal, so have key item, trainer suite, which adds menu fields EXP_SHARE & EV_TRAIN
//taking through task/menu options that would set the specific flag for that mon.
//setting exp share flag should add little "E" symbol  to partymenu window so easy to tell its active
//think can do similar thing for ev items, just set item icon in a spot on party menu to show you're ev training and what stat you're boosting.
//this would be separate from held item position as that's directly on the mon icon itself.
//ev shackle item would still be of use, what it would do is actually be a held item, 
//either it doesn't lower speed or its the only training tool that actually DOES lower speed when in use.
//it'd multiply the individual stat ev gain you normally get by a multiplier
//also of note you should be able to set multiple ev train items at once with this.
//since its a u8 flag I have space for 8 flags at once, and only 6 stat flags plus the exp flag, leaving one space still for the form flag!!

//put more thought into this and I'm wondering if it matters where I put the flag, 
//if I use it here itd be in basestats struct
//but evs are stored in PokemonSubstruct2, idk if it needs to be in teh same struct or not, I assume it shoudn't matter
//its just a matter of checking and setting the relevant fields as I need them.
//I believe its easier to adjust values when they are in the same struct?
//should I need to I could easily replace sheen with the flag as they would both be u8
//meaning savestruct wouldn't be affected  but for form change/breeding it makes more sense
//to use base stat struct for form change/flag check,  I could do both
//leave form change in base stats but move the exp share & ev item flag checks to PokemonSubstruct2
//in place of sheen

//adjusted geodude, added drayano stat changes

//* note I may need to lower some drayano stats 
//to account for my higher ev range, to balance
//read most -_-

//check rotom etc. to ensure I''ve replaced every instance of levitate

//note researching abilities on bulb/db I've come to conclusion ability slots follow a pattern
//slot 1 is a natural capability/ability of the mon i.e intimidatation strong jaws a cute charm etc.
//slot 2 offers some form of boost or synergy  but is also direvative of natural ability/biology i.e lighting rod for cubone with its bone or flash fire
//while the hidden ability slot is meant to be something special/unique that allows it to fit into a different niche or a niche.

//consider comb over ability allocation to make sure correctly follows this logic

//type idea changes
//type 1 is main type,  type 2 is secondary type
//but also concepts...flying tpye is thought of as the "bird" type which is accurate should be an adept flyer to be flying, not just have wings
//to that end I think of normal type as the "animal/beast" type. for consistency want to try keeping to that for my type changes
//for joat I want to add more normal types and I added it to hitmons, but that doesn't feel right now?
//It would make sense for them to stay pure fighting as they have human shape, but that leaves hitmontop available I guess 
//ok went through and adjusted pure fighting mon I felt matched normal archetype

//more notes for flying, mon like doduo I kept flying type but since it cant fly in the type calcs
//I made it take neutral from electricity.   I plan to do same for archen/archeops 
//idea is while it can fly, it needs a runnnings start to do so, so 
//when its battling somone, its gonna be running on the ground, not fighting from the air, like other flying types
//...I didnt' actually do type effect yet. *facepalm such an idiot,
//if flying type grounded and movetype is electric and multiplier is super effective, multiplier is normal
//if flying type grounded and movetype is fighting and multiplier is not very effective, multiplier is normal

//logic for flying types will be, if bird, or if majorly attacks from the air
//w lugia as example for rare cases dragon type can stand in for flying part of identity,  as dragons are rulers of land and sky (and sea for water dragons)

//put thematic logic for all types, helps with type changes as well as keeping consistent
/*
    Normal: Animal type thing that are just normal land mamals/animals
    Flying: Bird type flying for birds or specifically for things that are expert flyers. some qualities can also overlap w dragons
    Water:  Aquatic type  for fish, or aquatic animals/mamals or things made up of the element, some qualities can also overlap w dragons
    Dragon: rulers of land/air/sea apex predators typically with lizard/reptile like qualities
    Dark: supernatural type typically tricksters or evil or related to things seen as bad/evil
    Fairy: Magic type  fairy qualities, like dark can also be tricksters, may also have strong relation to nature - looked further GF seems to have paterned them more after pixie-like fae, nature spirits explains why not effective on fire, as its their weakness/destroys their homes
    Poison: Is poisonous in some manner, or otherwise involves trash/waste or contamination/corruption
    Ground: Lives in deserts/underground or has some link to earth element, is distinct from rock.
    Rock:  Hardened ground sturdy and solid
    Steel:  Refined rock forged into steel, made of metal or has some relation to it/metal weapon or control of metal
    Fire: Made of fire, lives near volcano, or able to breathe fire, not exclusive to fire types some qualities also overlap w dragons
    Ice: Lives in tundra/arctic bioms, made up of or able to control ice/cold.
    Grass:  Plants/Nature type,  involves creatures made of plants or a close relation to plants. I consider it plant/nature/life energy
    ???: Eldritch/Ancient type, creatures beyond normal comprehension, or that the conventional type scheme can't fully grasp.
    Fight: Trained Human type,  extensively physically trained but like normal lacks extra traits, typically human-like egg group, 
    Psychic: counterpart-to fighting, extensively mentally trained, has extra normal powers similar to fairy except source is the mind.
*/

//redoing early fossil mon as well, rock type doesn't really make sense for most of them
//they don't getg many rock moves, they dont have rocky characteristics
//only thing is they are from fossils, and from the "stone age"
//watched cammeemealtea video and they brought up them being dragonsin stead,
//also as that gives ice weakness it makes sense, as ice age killed off dinosaurs.
//or it folllowed end of dinosaurs
//most early fossils could be normal dragon or pure dragon,  but reconciling the loss of resistance is difficult
//especially when its a dual type already

const struct BaseStats gBaseStats[] =
{
    [SPECIES_NONE] = {0},

    [SPECIES_BULBASAUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 49, 49, 45, 65, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 64,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,

    },

    [SPECIES_IVYSAUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(72, 62, 63, 60, 80, 80),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VENUSAUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(93, 82, 83, 80, 100, 100),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 236,
        //.evYield_SpAttack = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CHARMANDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(39, 52, 43, 65, 60, 50),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CHARMELEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(58, 64, 58, 80, 80, 65),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CHARIZARD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(78, 84, 78, 100, 109, 85),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 240,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SQUIRTLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(44, 48, 65, 43, 50, 64),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 63,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WARTORTLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(59, 63, 80, 58, 65, 80),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BLASTOISE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(79, 83, 100, 78, 85, 105),
        .type1 = TYPE_WATER,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_SpDefense = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_HEAVY_METAL},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CATERPIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 30, 35, 45, 20, 20),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 39,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_METAPOD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 20, 65, 30, 25, 25),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG, //potentially make normal bug? would be stronger but then who would be normal but, keep aneye on this prob use type
        .catchRate = 120,
        .expYield = 72,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_MARVEL_SCALE, ABILITY_NONE},
        .abilityHidden = {ABILITY_STAMINA, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//Lunos explained hidden ability is saved even if mid evo doesn't have  a hidden ability final evo will go back to hidden ability slot
  //ok augment hp for late game effectiveness hopefully balanced by you encountering them at such low level bc the hp formula isn't fully effective

    [SPECIES_BUTTERFREE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 45, 50, 90, 95, 80),     
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 178,
        //.evYield_SpAttack = 2,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_COMPOUND_EYES, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TINTED_LENS, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_WEEDLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 35, 30, 50, 20, 40),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 39,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KAKUNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 25, 50, 35, 25, 65),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 120,
        .expYield = 72,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_POISON_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_BEEDRILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 95, 40, 95, 45, 98),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 178,
        //.evYield_Attack = 2,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_POISONED_LEGACY},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIDGEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 45, 40, 67, 45, 35),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 50,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_TANGLED_FEET},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_EARLY_BIRD},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PIDGEOTTO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(63, 70, 55, 91, 70, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 122,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_AVIATOR},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PIDGEOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 95, 85, 121, 85, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 216,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_AVIATOR},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_RATTATA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 56, 35, 72, 25, 35),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 51,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_PICKUP},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_RATICATE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 87, 60, 109, 50, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 127,
        .expYield = 145,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_GUTS},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SPEAROW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 60, 30, 70, 31, 31),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 52,
        //.evYield_Speed = 1,
        //.item2 = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_BIG_PECKS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_FEAROW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 100, 65, 100, 61, 61),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 90,
        .expYield = 155,
        //.evYield_Speed = 2,
        //.item2 = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_BIG_PECKS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_EKANS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 60, 44, 70, 40, 64),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_SHED_SKIN},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_MERCILESS},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_ARBOK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 96, 69, 87, 80, 89),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 157,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_SHED_SKIN},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_MERCILESS},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 75, 40, 95, 85, 50),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_STATIC, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_RAICHU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 100, 75, 70, 95, 90),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 218,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_STATIC, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SANDSHREW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 75, 85, 65, 20, 30),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            ////.item2 = ITEM_GRIP_CLAW, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SANDSLASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 100, 110, 75, 45, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 90,
        .expYield = 158,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_GRIP_CLAW, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_NIDORAN_F] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 47, 52, 41, 40, 50),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 235,
        .expYield = 55,
        //.evYield_HP = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_RIVALRY},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_BIG_PECKS},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NIDORINA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 62, 67, 56, 55, 75),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 128,
        //.evYield_HP = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_GLUTTONY},
        .safariZoneFleeRate = 75,
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_FRIEND_GUARD},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NIDOQUEEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(97, 92, 87, 76, 90, 105),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 227,
        //.evYield_HP = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_THICK_FAT},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_BATTLE_MATRON},//new idea ability Battle Matron, damage increase if paired w unevolved mon
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NIDORAN_M] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(46, 57, 40, 50, 40, 50),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 235,
        .expYield = 55,
        //.evYield_Attack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_RIVALRY},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_GUTS},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_NIDORINO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(61, 77, 57, 65, 55, 65),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 128,
        //.evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_RIVALRY},
        .safariZoneFleeRate = 75,
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_GUTS},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_NIDOKING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(81, 102, 77, 85, 91, 95),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK, //initially forgot logic, but traded electric immunity for psychic immunity, while poison covers the bug and fighting weakness, 
        .catchRate = 45,    //as well as the other dark benefits I get.   //same thing for nidoqueen except she gets normal benefits
        .expYield = 227,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_RIVALRY},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_COMPETITIVE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },  //because dark type intimidate exclusion, should I add workaround so competitive still activates?
    //they attempted to, it just didn't work, yeah find work around, similar idea to anger point

    [SPECIES_CLEFAIRY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 50, 48, 35, 60, 75),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 150,
        .expYield = 113,
        //.evYield_HP = 2,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_UNAWARE, ABILITY_FRIEND_GUARD},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_CLEFABLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 70, 73, 60, 100, 95),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 25,
        .expYield = 217,
        //.evYield_HP = 3,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_UNAWARE, ABILITY_FRIEND_GUARD},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    }, //need test this and consider if normal type is worth give my changes

    [SPECIES_VULPIX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(38, 41, 40, 65, 50, 65),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 190,
        .expYield = 60,
        //.evYield_Speed = 1,
        //.item2 = ITEM_CHARCOAL,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_MULTI_TASK},
        .abilityHidden = {ABILITY_SUN_DISK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_NINETALES] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(73, 76, 75, 100, 81, 100),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GHOST,
        .catchRate = 75,
        .expYield = 177,
        //.evYield_Speed = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_CHARCOAL,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_MULTI_TASK},
        .abilityHidden = {ABILITY_SUN_DISK, ABILITY_SHADOW_TAG},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //give shadow ball , forgot I did this, this is horrifying

    [SPECIES_JIGGLYPUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(115, 45, 37, 20, 45, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 170,
        .expYield = 95,
        //.evYield_HP = 2,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_COMPETITIVE},
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_WIGGLYTUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(140, 70, 55, 45, 85, 68),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 50,
        .expYield = 196,
        //.evYield_HP = 3,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_COMPETITIVE},
            .abilityHidden = {ABILITY_FRISK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_ZUBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 45, 35, 55, 30, 53),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 49,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_NUISANCE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_SONAR},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GOLBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 80, 110, 80, 65, 85),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FLYING,
        .catchRate = 90,
        .expYield = 159,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_NUISANCE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_SONAR},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_ODDISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 50, 55, 30, 75, 75),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 64,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_ABSORB_BULB, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_PRANKSTER},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GLOOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 65, 70, 40, 85, 85),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 120,
        .expYield = 138,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_STENCH},
        .abilityHidden = {ABILITY_AFTERMATH, ABILITY_PRANKSTER},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //potentially lower sp atk for addition of stench/additional bulk given?

    [SPECIES_VILEPLUME] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 80, 85, 50, 110, 101),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 221,
        //.evYield_SpAttack = 3,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_STENCH},
        .abilityHidden = {ABILITY_EFFECT_SPORE, ABILITY_PRANKSTER},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_PARAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 78, 67, 63, 45, 75),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 57,
        //.evYield_Attack = 1,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EFFECT_SPORE, ABILITY_DRY_SKIN},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_DAMP, ABILITY_IMMUNITY},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_PARASECT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(88, 95, 115, 30, 60, 88),
        .type1 = TYPE_BUG,  //think prefer grass for mushroom, as bug is dead the mushroom is the only thing left to be affected
        .type2 = TYPE_GHOST,    //changed back,its the body of a bug its abilities can represent the mushroom effect, plus type strength is about same
        .catchRate = 75,    //still waffling on this, bug grass have similar weaknesses, bug gets confusion immunity, but the bug is dead
        .expYield = 142,    //grass gets the fairy immunity, and powder move immunity, which the mushroom would have
        //.evYield_Attack = 2,      //think keeping bug grass it has more defense strength
        //.evYield_Defense = 1,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EFFECT_SPORE, ABILITY_DRY_SKIN},
        .safariZoneFleeRate = 75,
        .abilityHidden = {ABILITY_DAMP, ABILITY_IMMUNITY},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },
    /*Most mushrooms prefer shade or dark places,
    which is why you'll often find them on forest floors. 
    However, some mushrooms can grow in part to full sun, 
    such as those you may find growing on manure in a field. 
    Mushrooms are more likely to adapt to less ideal conditions
    if they have a quality substrate to grow on.*/  
    //such as anothre creature's corpse, adaptability? something more? new stall?  dark deal?  /think not dark deal wasn't exactly a choice for paras
    //perhaps aftermath?

    [SPECIES_VENONAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(67, 55, 50, 60, 45, 75),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COMPOUND_EYES, ABILITY_TINTED_LENS},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    }, //since it has tinted lens I kinda want this to be normal type..but its literlaly venom nat so poison bug

    [SPECIES_VENOMOTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(77, 65, 60, 100, 100, 90),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 158,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELD_DUST, ABILITY_TINTED_LENS},
            .abilityHidden = {ABILITY_WONDER_SKIN, ABILITY_NONE},//wonder skin is buffed so could keep
        .safariZoneFleeRate = 75,
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },  //tis thing is strong AF

    [SPECIES_DIGLETT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(10, 55, 25, 95, 35, 45),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_Speed = 1,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_ARENA_TRAP},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//making normal ground for more dmg, think this was before I changed joat, most moves are groud so w revert back

    [SPECIES_DUGTRIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 105, 50, 120, 50, 70),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 50,
        .expYield = 149,
        //.evYield_Speed = 2,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_ARENA_TRAP},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MEOWTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 45, 35, 90, 40, 40),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Speed = 1,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_SUPER_LUCK},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PERSIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 77, 60, 115, 77, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 154,
        //.evYield_Speed = 2,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIMBER, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_SUPER_LUCK}, //harken back to  gen 1 crit days
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PSYDUCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 56, 58, 55, 85, 65),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 64,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_DAMP, ABILITY_CLOUD_NINE},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_GOLDUCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 95, 78, 85, 95, 87),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 175,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_DAMP, ABILITY_CLOUD_NINE},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MANKEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(48, 80, 50, 72, 35, 45),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_VITAL_SPIRIT, ABILITY_ANGER_POINT},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_IRON_FIST},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PRIMEAPE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(69, 105, 65, 95, 60, 70),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 159,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_VITAL_SPIRIT, ABILITY_ANGER_POINT},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_IRON_FIST}, //muscle magic vs iron fist giving iron fist mucscle magic was supposed to be special/unique
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GROWLITHE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 70, 45, 70, 70, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIRE,
        .catchRate = 190,
        .expYield = 70,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ARCANINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 110, 80, 105, 100, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIRE,
        .catchRate = 75,
        .expYield = 194,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_POLIWAG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 50, 40, 90, 40, 40),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_DAMP},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_POLIWHIRL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 65, 75, 90, 50, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 120,
        .expYield = 135,
        //.evYield_Speed = 2,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_DAMP},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_POLIWRATH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 105, 105, 70, 70, 90),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 230,
        //.evYield_Defense = 3,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_DAMP},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ABRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 20, 25, 90, 105, 55),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 200,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_COMATOSE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_GUARD, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//buffed hp as perma sleep,  buffing comatose w healing as mon can't rest think will attempt to set to have sleep status icon, no reason not to
    //thought hp was too high, but it doesn't change that much when it evolves, so I guess its fine?

    [SPECIES_KADABRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 35, 30, 105, 120, 70),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 100,
        .expYield = 140,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_EMPATH, ABILITY_ANTICIPATION},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ALAKAZAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 50, 45, 120, 135, 95),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 50,
        .expYield = 225,
        //.evYield_SpAttack = 3,
        //.item2 = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_EMPATH, ABILITY_ANTICIPATION},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MACHOP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 80, 50, 35, 35, 35),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 180,
        .expYield = 61,
        //.evYield_Attack = 1,
        //.item2 = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_NO_GUARD},
            .abilityHidden = {ABILITY_MUSCLE_MAGIC, ABILITY_LIMBER},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MACHOKE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 100, 70, 45, 50, 60),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 90,
        .expYield = 142,
        //.evYield_Attack = 2,
        //.item2 = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_NO_GUARD},
            .abilityHidden = {ABILITY_MUSCLE_MAGIC, ABILITY_LIMBER},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MACHAMP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 130, 80, 60, 65, 85),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 227,
        //.evYield_Attack = 3,
        //.item2 = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_NO_GUARD},
            .abilityHidden = {ABILITY_MUSCLE_MAGIC, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_BELLSPROUT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 75, 36, 89, 70, 56),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE}, //replace gluttony with something else
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//pokemon like this w big evo change have signinficant stat dif so previous evo may be better in some ways do 4 others i find like this
    //remember make 2nd pass at stats to leave room for high ev cap, but still be buffed, leave legends & psuedo where they are 
    //can lower others as needed.

    [SPECIES_WEEPINBELL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 90, 50, 55, 85, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 120,
        .expYield = 137,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VICTREEBEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(111, 105, 75, 57, 100, 87),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 221,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_TENTACOOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 40, 75, 70, 50, 100),
        .type1 = TYPE_WATER,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_LIQUID_OOZE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_POISON_POINT},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_TENTACRUEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 70, 95, 100, 80, 130),
        .type1 = TYPE_WATER,
        .type2 = TYPE_POISON,
        .catchRate = 60,
        .expYield = 180,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_LIQUID_OOZE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },
   
    [SPECIES_GEODUDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 80, 100, 20, 30, 45),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Defense = 1,
        //.item2 = ITEM_EVERSTONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_STURDY},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_DRY_SKIN},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GRAVELER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 95, 115, 35, 45, 65),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 120,
        .expYield = 137,
        //.evYield_Defense = 2,
        //.item2 = ITEM_EVERSTONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_STURDY},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOLEM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 120, 130, 45, 55, 75),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 223,
        //.evYield_Defense = 3,
        //.item2 = ITEM_EVERSTONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_STURDY},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_DRY_SKIN},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PONYTA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 85, 55, 90, 65, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIRE,
        .catchRate = 190,
        .expYield = 82,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_FLASH_FIRE},
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_RAPIDASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 100, 70, 105, 80, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIRE,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_FLASH_FIRE},
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SLOWPOKE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 65, 65, 15, 40, 40),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 63,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LAGGING_TAIL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_OBLIVIOUS, ABILITY_OWN_TEMPO},
        .safariZoneFleeRate = 50,
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    }, //buff tm learnset and mvoe pool needs it badly  learning payvback,gyro ball slow moves, and more water moves early would be good

    [SPECIES_SLOWBRO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 75, 110, 30, 100, 80),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 172,
        //.evYield_Defense = 2,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_OBLIVIOUS, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_MAGNEMITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(25, 35, 70, 45, 95, 55),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_VOLT_ABSORB},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MAGNETON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 60, 95, 70, 120, 70),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 163,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MULTI_TASK, ABILITY_VOLT_ABSORB},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_FARFETCHD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 105, 60, 60, 50, 62),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 192,
        //.evYield_Attack = 1,
        //.item2 = ITEM_LEEK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_INNER_FOCUS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DODUO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 85, 45, 75, 35, 35),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 62,
        //.evYield_Attack = 1,
        //.item2 = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_EARLY_BIRD},
        .safariZoneFleeRate = 50,
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_AERILATE, ABILITY_MULTI_TASK},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DODRIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 110, 70, 110, 60, 60),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 165,
        //.evYield_Attack = 2,
        //.item2 = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_EARLY_BIRD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_AERILATE, ABILITY_MULTI_TASK},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SEEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 45, 55, 45, 45, 70),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ICE,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_ICE_BODY, ABILITY_SWIFT_SWIM},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DEWGONG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 70, 80, 76, 75, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ICE,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_ICE_BODY, ABILITY_SWIFT_SWIM},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GRIMER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 80, 50, 25, 40, 65),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BLACK_SLUDGE,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_STENCH, ABILITY_STICKY_HOLD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_POISON_HEAL},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MUK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 105, 75, 50, 65, 100),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 175,
        //.evYield_HP = 1,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
           // .item1 = ITEM_BLACK_SLUDGE,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_STENCH, ABILITY_STICKY_HOLD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_POISON_HEAL},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SHELLDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 65, 100, 54, 45, 25),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Defense = 1,
        //.item1 = ITEM_PEARL,
        //.item2 = ITEM_BIG_PEARL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHELL_ARMOR, ABILITY_SKILL_LINK},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CLOYSTER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 95, 180, 65, 85, 50),
        .type1 = TYPE_WATER,  //most moves were ice rather than water related plus its a clam which makes pearls so kinda fitting
        .type2 = TYPE_ICE, //ice rock was cool idea but doesn't make any sense for this to be a sandstorm mon
        .catchRate = 60,
        .expYield = 184,
        //.evYield_Defense = 2,
        //.item1 = ITEM_PEARL,
        //.item2 = ITEM_BIG_PEARL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHELL_ARMOR, ABILITY_SKILL_LINK},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//need add rock moves

    [SPECIES_GASTLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 55, 30, 80, 100, 45),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_CURSED_BODY, ABILITY_UNNERVE}, //think want to add ghost ability that sets curse,
        .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_HAUNTER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 70, 45, 95, 115, 75),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_POISON,
        .catchRate = 90,
        .expYield = 142,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
         .abilities = {ABILITY_CURSED_BODY, ABILITY_UNNERVE},
        .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GENGAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 85, 60, 110, 130, 80),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 225,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#if P_UPDATED_ABILITIES >= GEN_7
            //#ifdef BATTLE_ENGINE
                .abilities = {ABILITY_CURSED_BODY, ABILITY_UNNERVE},
                 .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_PERISH_BODY},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_ONIX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 62, 160, 77, 30, 55),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 77,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SAND_RUSH},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_DROWZEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 58, 60, 42, 53, 90),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BAD_DREAMS, ABILITY_FOREWARN},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_GLUTTONY}, //ABILITY_GLUTTONY
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, 

    [SPECIES_HYPNO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 73, 70, 67, 73, 115),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 169,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BAD_DREAMS, ABILITY_FOREWARN},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_MAGICIAN}, //ABILITY_MAGICIAN  for new new version of magician, swaps held item  if holding steals if not holding
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_KRABBY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 105, 90, 55, 39, 25),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 225,
        .expYield = 65,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_IRON_FIST},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_KINGLER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 130, 115, 75, 50, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_IRON_FIST},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_VOLTORB] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 30, 55, 105, 65, 75),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SOUNDPROOF, ABILITY_STATIC}, //with low attack stat and defense potentially remove static for aftermath, but it also has steel typing now
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STURDY, ABILITY_OVERCHARGE}, //: )
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ELECTRODE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 50, 75, 150, 95, 100),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 172,
        //.evYield_Speed = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SOUNDPROOF, ABILITY_STATIC},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STURDY, ABILITY_OVERCHARGE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_EXEGGCUTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 55, 101, 40, 60, 45),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 65,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_PSYCHIC_SEED,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .safariZoneFleeRate = 75,
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_EXEGGUTOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(115, 95, 85, 55, 125, 75),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 186,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CUBONE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 50, 95, 45, 40, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 190,
        .expYield = 64,
        //.evYield_Defense = 1,
        //.item2 = ITEM_THICK_CLUB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_BATTLE_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MAROWAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 88, 118, 65, 50, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 75,
        .expYield = 149,
        //.evYield_Defense = 2,
        //.item2 = ITEM_THICK_CLUB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_BATTLE_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //cant give muslce magic as that was meant to be main of mega marowak

    [SPECIES_HITMONLEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 121, 60, 87, 35, 110),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIMBER, ABILITY_LETHAL_LEGS}, //replaced reckless 
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_MUSCLE_MAGIC},
        .bodyColor = BODY_COLOR_BROWN, //give ability lethal legs strenghts kicking moves?
        .noFlip = FALSE,
    },

    [SPECIES_HITMONCHAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 105, 79, 76, 35, 123),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_IRON_FIST},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_MUSCLE_MAGIC},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //giving back normal type as flexibility as actual martial artists
    //nvm want to keep but flies in face of established normal logic, where normal is for animals, not human likes
    //best I can do is make it for hitmonlee and hitmontop as they have claws and a tail in case of hitmontop,

    [SPECIES_LICKITUNG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(112, 55, 75, 30, 60, 96),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 77,
        //.evYield_HP = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LAGGING_TAIL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_TOXUNGUE, ABILITY_OBLIVIOUS},//replace own tempo with new versino of poison touch that paralyzes instead make signature
        .abilityHidden = {ABILITY_CLOUD_NINE, ABILITY_STALL},//relacing adaptability with stall
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,//ability name ToxuTongue  based on toxungen which this technically is, or maybe ToxunTongue? to lean more into the name?
    },

    [SPECIES_KOFFING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 65, 75, 35, 60, 95),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 68,
        //.evYield_Defense = 1,
        //.item2 = ITEM_SMOKE_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_NEUTRALIZING_GAS},
        .abilityHidden = {ABILITY_STENCH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_WEEZING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 90, 88, 60, 85, 120),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 60,
        .expYield = 172,
        //.evYield_Defense = 2,
        //.item2 = ITEM_SMOKE_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_NEUTRALIZING_GAS},
        .abilityHidden = {ABILITY_STENCH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_RHYHORN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 85, 95, 25, 30, 45),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_ROCK,
        .catchRate = 120,
        .expYield = 69,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_ROCK_HEAD},
        .safariZoneFleeRate = 75,
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_SHEER_FORCE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_RHYDON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 130, 120, 40, 45, 65),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_ROCK,
        .catchRate = 60,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_ROCK_HEAD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_MUSCLE_MAGIC}, //muscle magic makes this thing getting surf actuallyt not a troll
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //give head charge & headlong rush

    [SPECIES_CHANSEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(250, 15, 10, 50, 45, 105),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 30,
        .expYield = 395,
        //.evYield_HP = 2,
        //.item1 = ITEM_LUCKY_PUNCH,
        .genderRatio = MON_FEMALE,
        .eggCycles = 40,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_SERENE_GRACE},
        .safariZoneFleeRate = 125,
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEALER, ABILITY_TRUANT},//replace slow start with immunity, a little TOO unkillable.. //nvm did truant as gave blissey stall, better themati matchup
        // #endif
        .bodyColor = BODY_COLOR_PINK,//giving fairy type as well, mostly just  a few other weaknesses to counter its increased strength witih super changes
        .noFlip = FALSE,
    },

    [SPECIES_TANGELA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 54, 115, 60, 100, 51),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 87,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_LEAF_GUARD},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_KANGASKHAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 95, 80, 90, 40, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_HP = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EARLY_BIRD, ABILITY_SCRAPPY},
        .safariZoneFleeRate = 125,
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_PARENTAL_BOND},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_HORSEA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 40, 70, 60, 70, 25),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 225,
        .expYield = 59,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWIFT_SWIM, ABILITY_SNIPER},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SEADRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 65, 95, 85, 95, 55),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_SNIPER},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GOLDEEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 67, 60, 63, 55, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 225,
        .expYield = 64,
        //.evYield_Attack = 1,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_WATER_BUBBLE, ABILITY_HYDRATION},
        .safariZoneFleeRate = 50,
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_STALL},//idk why I gaev this stall, its slow but not at all bulky
        .bodyColor = BODY_COLOR_RED, //welp nvm its kinda tankin pretty good??
        .noFlip = FALSE,
    },//thinking give unaware, keeping stall on pre evo for eviolite strats taht's about it

    [SPECIES_SEAKING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 92, 65, 88, 65, 80),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 60,
        .expYield = 158,
        //.evYield_Attack = 2,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_WATER_BUBBLE, ABILITY_HYDRATION},
        .safariZoneFleeRate = 75,
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_UNAWARE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//replaced abilities since they suck, and goldeen usually doesns't learn physical water moves, VSONIC

    [SPECIES_STARYU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 45, 55, 85, 70, 55),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 225,
        .expYield = 68,
        //.evYield_Speed = 1,
        //.item1 = ITEM_STARDUST,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_ILLUMINATE, ABILITY_NATURAL_CURE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_REGENERATOR}, //analytic doesn't make sense starfish can regen what makes more sense is
        // #endif                       //adaptability and regenerator  as they can live in many different environments warm hot cold etc
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_STARMIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 75, 85, 115, 100, 85),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 60,
        .expYield = 182,
        //.evYield_Speed = 2,
        //.item1 = ITEM_STARDUST,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_ILLUMINATE, ABILITY_NATURAL_CURE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_REGENERATOR}, //JUST an idea since it has recover potential bulk starkmie with quick claw
        // #endif
        .bodyColor = BODY_COLOR_PURPLE, //quick claw wouldn't work with stall I think?
        .noFlip = FALSE,
    },

    [SPECIES_MR_MIME] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(56, 45, 75, 90, 100, 120),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 161,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOUNDPROOF, ABILITY_FILTER},
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_STALL}, //give more physical moves for troll stall powerswap strats
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    }, //doesn't make sense tobe fairy, just makes weaker, doesn't even get any fairy moves usually

    [SPECIES_SCYTHER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 110, 80, 105, 55, 80),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 100,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWARM, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_STEADFAST, ABILITY_MOXIE},
        .safariZoneFleeRate = 125,
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//give dual wingbeat

    [SPECIES_JYNX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 50, 45, 95, 115, 95),
        .type1 = TYPE_ICE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FEMME_FATALE, ABILITY_FOREWARN}, //replace oblivious w ABILITY_FEMME_FATALE
            .abilityHidden = {ABILITY_DRY_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //need rebalance stats since ice is so much better defensively, oh nvm it was fine

    [SPECIES_ELECTABUZZ] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 83, 57, 105, 95, 85),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Speed = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ELECTIRIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MAGMAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 95, 57, 93, 100, 85),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_MAGMARIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_PINSIR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 125, 100, 85, 55, 70),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYPER_CUTTER, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_MOXIE, ABILITY_MUSCLE_MAGIC},
        .safariZoneFleeRate = 125,
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TAUROS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 110, 95, 110, 40, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_ANGER_POINT},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_SAP_SIPPER},
        .safariZoneFleeRate = 50,
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MAGIKARP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(20, 160, 125, 45, 155, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 20,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_BULLETPROOF},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        // #endif
        .safariZoneFleeRate = 25,
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },// [done]kek make troll dex entry[ and increase max lvl for old rod spawn

    [SPECIES_GYARADOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 125, 79, 81, 60, 100),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 189,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_ANGER_POINT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },  //give new version of rage, if doesn't already get rage

    [SPECIES_LAPRAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(130, 85, 80, 60, 85, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 187,
        //.evYield_HP = 2,
        //.item1 = ITEM_MYSTIC_WATER,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HYDRATION, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DITTO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(48, 99, 99, 130, 99, 99),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GHOST, //the ghost type was a joke but eh guess I'll give it night shade
        .catchRate = 35,
        .expYield = 101,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
           // //.item1 = ITEM_QUICK_POWDER,  vsoonic  , is actually useless, with imposter, even more useless with my joke speed boost
        // #endif
        //.item2 = ITEM_METAL_POWDER,   //so way I setup transform quick powder & metal powder actually really good lol, since transoformign doesn't change spcies in my version
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_DITTO,
        .eggGroup2 = EGG_GROUP_DITTO,
        .abilities = {ABILITY_IMMUNITY, ABILITY_IMPOSTER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INVERSION, ABILITY_NONE}, //inversion still to do //think will add bst to logic to avoid transforming into legendaries
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//levle up is broken...pretty sure its not able to read the species properly if you level up while transformed, or someother part of data
    //-fixed

    [SPECIES_EEVEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 75, 55, 85, 85, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,   //change up eevee stats as its evo is more of a form change than a growth imo so stats are average but actually mid game viable
        .catchRate = 45,
        .expYield = 65,
        //.evYield_SpDefense = 1,
        //.item1 = ITEM_EVIOLITE
        ////.item2 = ITEM_EVERSTONE, put eviolite here make farmable spawn /will be this and everstone
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_ADAPTABILITY},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_PICKUP},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VAPOREON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(130, 65, 60, 65, 110, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_WATER_ABSORB},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIQUID_VOICE, ABILITY_STURDY},   //YES this is a joke
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_JOLTEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 85, 60, 120, 110, 90),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_VOLT_ABSORB},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_OVERCHARGE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_FLAREON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 130, 60, 65, 95, 110),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_FLASH_FIRE},
        .abilityHidden = {ABILITY_GUTS, ABILITY_ILLUMINATE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_PORYGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 60, 70, 40, 85, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 79,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TRACE, ABILITY_DOWNLOAD},
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_VOLT_ABSORB},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_OMANYTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 40, 100, 35, 90, 55),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SWIFT_SWIM},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_OMASTAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 60, 125, 55, 115, 70),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SWIFT_SWIM},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_KABUTO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 80, 90, 55, 55, 45),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_BATTLE_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SWIFT_SWIM},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KABUTOPS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 115, 105, 80, 65, 70),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_BATTLE_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SWIFT_SWIM},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_AERODACTYL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 105, 65, 130, 60, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 180,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_PRESSURE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_STRONG_JAW},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SNORLAX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(160, 110, 65, 30, 65, 110),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 25,
        .expYield = 189,
        //.evYield_HP = 2,
        //.item1 = ITEM_LEFTOVERS,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_IMMUNITY, ABILITY_SAP_SIPPER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_RIPEN},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//IMPORTANT make change to gluttony that it raises attack and speed by 1 stage when opponent uses berry
    //make function that checks lastuseditem from opposite side, and one that looks through berries just like neutralizing gas does abilities

    [SPECIES_ARTICUNO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 75, 100, 85, 115, 115),
        .type1 = TYPE_ICE,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SNOW_WARNING, ABILITY_SNOW_WARNING},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_EARLY_BIRD, ABILITY_REFRIGERATE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZAPDOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 90, 85, 100, 125, 90),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_VOLT_ABSORB},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//based on JPRPokeTrainer98 youtube vid replace pressure for most legendaries, keep for mewtwo 

    [SPECIES_MOLTRES] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 100, 90, 90, 125, 85),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_RISING_PHOENIX, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//new abilities based on JPRPokeTrainer98 youtube vid,  volcanic healing or pheonix or primal fire, fire type volt absorb but combine w flame body effect
    //but with a higher chance to burn,  maybe call it primordial flame/fire  also works as a status cleanse/field cleanse, make status cleanse not field cleanse
    //hit by fire heals status effects  phoenixification ?  phoenix riser  riser phoenix? lol rising phoenix

    [SPECIES_DRATINI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(41, 64, 45, 50, 50, 50),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Attack = 1,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .safariZoneFleeRate = 100,
        .abilityHidden = {ABILITY_MARVEL_SCALE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DRAGONAIR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(61, 84, 65, 70, 70, 70),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Attack = 2,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_MARVEL_SCALE, ABILITY_NONE},
        .safariZoneFleeRate = 125,
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DRAGONITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(91, 134, 95, 80, 100, 100),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_Attack = 3,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_AVIATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MULTISCALE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MEWTWO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(106, 110, 90, 130, 154, 90),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MEW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 100, 127, 100, 160),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_HP = 3,
        //.item1 = ITEM_LUM_BERRY,
        //.item2 = ITEM_LUM_BERRY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_FOREWARN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },//buff to give realm of excellence as mewtwo is more offenseive whille mew was always about avoiding fights/damage

    [SPECIES_CHIKORITA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(61, 49, 65, 45, 49, 75),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_BAYLEEF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(87, 57, 80, 60, 63, 95),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MEGANIUM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 82, 100, 80, 83, 153),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 236,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CYNDAQUIL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(39, 52, 43, 72, 60, 50),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_QUILAVA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(68, 64, 58, 87, 80, 70),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL, //could make fire ground but w my normal change still think fire normal is better?it has a somewhat varied move pool already
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TYPHLOSION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(78, 84, 78, 100, 109, 95),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 240,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TOTODILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 65, 64, 47, 44, 48),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 63,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_STRONG_JAW},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CROCONAW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 80, 80, 66, 59, 63),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_STRONG_JAW},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_FERALIGATOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 115, 100, 82, 79, 83),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Attack = 2,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_STRONG_JAW},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SENTRET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 56, 34, 25, 35, 45),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 43,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_ANALYTIC, ABILITY_KEEN_EYE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_RATTLED},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_FURRET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 86, 64, 100, 45, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 90,
        .expYield = 145,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_KEEN_EYE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_RATTLED},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_HOOTHOOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 40, 30, 50, 66, 56),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 52,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INSOMNIA, ABILITY_TINTED_LENS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_COMPOUND_EYES, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_NOCTOWL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 50, 50, 70, 120, 96),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 158,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INSOMNIA, ABILITY_TINTED_LENS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_COMPOUND_EYES, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//change the type to match grand colloseum [done]

    [SPECIES_LEDYBA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 65, 50, 55, 20, 100),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL, //ok was thinking fighting but will keep this, use normal type joat  to make it super versatile
        .catchRate = 255, //give all the elemental punches
        .expYield = 53,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_TECHNICIAN, ABILITY_SCRAPPY}, //technician or adaptability as idea is make mon uber flexible in move choice
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MULTI_TASK, ABILITY_IRON_FIST}, //want skill link can't fit think will instead add to multi task, think of it like
        // #endif           //using multiple appendages to hit multi strike moves all at once therefore guaranteeing full strikes  //give mind reader fury cutter based on zen mode yt
        .bodyColor = BODY_COLOR_RED,    //also give beat up  give special version fo power trick since that apparently doesn't exist call it power switch swaps sp def & sp atk
        .noFlip = FALSE,    //also give brick break, so only it can setup screens
    },

    [SPECIES_LEDIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 95, 65, 85, 35, 135),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 137,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_TECHNICIAN, ABILITY_SCRAPPY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MULTI_TASK, ABILITY_IRON_FIST},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SPINARAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 60, 40, 65, 40, 60),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 50,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_INSOMNIA},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARIADOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 90, 70, 88, 60, 88),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 90,
        .expYield = 140,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_INSOMNIA},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CROBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 90, 80, 130, 70, 90),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FLYING,
        .catchRate = 90,
        .expYield = 241,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_NUISANCE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_AVIATOR},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CHINCHOU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 38, 48, 67, 66, 66),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_HP = 1,
        //.item2 = ITEM_DEEP_SEA_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_ILLUMINATE},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LANTURN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(125, 58, 68, 67, 86, 86),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 161,
        //.evYield_HP = 2,
        //.item2 = ITEM_DEEP_SEA_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_ILLUMINATE},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PICHU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(20, 40, 30, 60, 55, 25),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 41,
        //.evYield_Speed = 1,
        //.item2 = ITEM_LIGHT_BALL, //change logic think give volt tackle if pichu  is created while holding ths item
        .genderRatio = PERCENT_FEMALE(50),//vsonic
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_MINUS},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CLEFFA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 25, 28, 15, 45, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 150,
        .expYield = 44,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_IGGLYBUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 30, 25, 15, 40, 25),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 170,
        .expYield = 42,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_COMPETITIVE},
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_TOGEPI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 20, 65, 20, 40, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 49,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HUSTLE, ABILITY_SERENE_GRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SUPER_LUCK, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_TOGETIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 40, 85, 40, 80, 115),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FLYING,
        //// #endif
        .catchRate = 75,
        .expYield = 142,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_HUSTLE, ABILITY_SERENE_GRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SUPER_LUCK, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_NATU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 50, 45, 70, 70, 50),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_NORMAL,   //Can't fly
        .catchRate = 190,
        .expYield = 64,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_EMPATH, ABILITY_EARLY_BIRD}, //buffing synchronize think will put back in place of trace
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_TELEPATHY},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_XATU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 75, 70, 100, 100, 75),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_EMPATH, ABILITY_EARLY_BIRD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_TELEPATHY},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MAREEP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 40, 95, 35, 65, 86),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 235,
        .expYield = 56,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_FLUFFY},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLAAFFY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 55, 55, 65, 85, 60),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 120,
        .expYield = 128,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_AMPHAROS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 75, 85, 55, 115, 90),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 230,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_BELLOSSOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 80, 95, 75, 100, 110),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 221,
        //.evYield_SpDefense = 3,
       // #ifdef ITEM_EXPANSION
          // //.item2 = ITEM_ABSORB_BULB,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FLOWER_VEIL, ABILITY_HEALER},
        // #endif 
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MARILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 35, 50, 40, 50, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 88,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_THICK_FAT, ABILITY_HUGE_POWER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_AZUMARILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 55, 80, 50, 90, 80),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 189,
        //.evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_THICK_FAT, ABILITY_HUGE_POWER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SUDOWOODO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 110, 115, 30, 30, 75),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GRASS,
        .catchRate = 65,
        .expYield = 144,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SOLID_ROCK, ABILITY_SAP_SIPPER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_ROCK_HEAD},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//make revisions to add grass moves to lvl up and tm learnsets   thinkin ingrain & bullet seed

    [SPECIES_POLITOED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 75, 75, 70, 90, 110),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 225,
        //.evYield_SpDefense = 3,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_DAMP},
        .abilityHidden = {ABILITY_SQUALL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_HOPPIP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 45, 40, 50, 45, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING, //keep flying for this, may not be a distance flyer but still good at maneovering itself throug the air
        .catchRate = 255,
        .expYield = 50,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_PRANKSTER},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_PHOTOSYNTHESIZE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    }, //think give roost

    [SPECIES_SKIPLOOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 45, 85, 84, 45, 70),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 119,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_PRANKSTER},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_FLUFFY},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_JUMPLUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 55, 70, 128, 105, 95),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 207,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PHOTOSYNTHESIZE, ABILITY_PRANKSTER},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_FLUFFY},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_AIPOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 70, 55, 85, 40, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 72,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_PICKUP},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SKILL_LINK, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SUNKERN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 30, 30, 30, 55, 30),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_NORMAL,
        .catchRate = 235,
        .expYield = 36,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SOLAR_POWER},
        .abilityHidden = {ABILITY_OVERGROW, ABILITY_BLAZE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SUNFLORA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 75, 85, 53, 135, 95),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FIRE,
        .catchRate = 120,
        .expYield = 149,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SOLAR_POWER},
        .abilityHidden = {ABILITY_PHOTOSYNTHESIZE, ABILITY_SUN_DISK},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//made fire match grand colloseum changes

    [SPECIES_YANMA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 65, 45, 95, 75, 45),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 75,
        .expYield = 78,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_WIDE_LENS, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SPEED_BOOST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRISK, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_WOOPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 45, 45, 15, 35, 32),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 42,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_DAMP, ABILITY_WATER_ABSORB},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_QUAGSIRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 95, 95, 35, 65, 65),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 90,
        .expYield = 151,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_DAMP, ABILITY_WATER_ABSORB},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ESPEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 65, 60, 110, 130, 95),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_EMPATH, ABILITY_EMPATH},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_UMBREON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 79, 110, 65, 66, 130),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SYNCHRONIZE, ABILITY_SYNCHRONIZE},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_DARK_DEAL},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_MURKROW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 85, 42, 91, 85, 42),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 81,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_INSOMNIA, ABILITY_DARK_DEAL},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SLOWKING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 75, 80, 30, 100, 110),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 70,
        .expYield = 172,
        //.evYield_SpDefense = 3,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_OBLIVIOUS, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_MISDREAVUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 60, 60, 85, 85, 85),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 87,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_PRESSURE, ABILITY_PRANKSTER}, 
        .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_UNNERVE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(64, 64, 48, 76, 64, 48),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//perhaps give unown special move based on letter?
    //similar to metronome but can pull up a move starting with their  letter
    //would greatly vary baed on letter maybe just new ability?
    //nah just giving it another move in the anime specific psychic
    //will give ability mystic power *name pending pretty much
    //same as plus minus but if another unown is on field with it/meaning same side

    [SPECIES_WOBBUFFET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(190, 33, 58, 33, 33, 58),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_SHADOW_TAG, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TELEPATHY, ABILITY_BATTLE_ARMOR},//usesful to prevent target switch for counter moves etc.
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GIRAFARIG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(69, 77, 63, 95, 97, 64),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 60,
        .expYield = 205,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_EARLY_BIRD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//stats lowered to allow use of eviolite

    [SPECIES_PINECO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 65, 90, 15, 35, 35),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,   //bcuz
        .catchRate = 190,
        .expYield = 58,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_STURDY, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_FORRETRESS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 90, 140, 40, 60, 60),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 75,
        .expYield = 163,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_STURDY, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DUNSPARCE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 70, 70, 45, 65, 87),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 145,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_RUN_AWAY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_DARK_DEAL},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //debuffed hp as plannin to actually add evo, just remodel sprite
    //waffling between leaving pure normal but making float, or normal poison and floating, giving it just a psychic weakness,
    //think I will do that actually, that removes its fighting weakness too. 

    [SPECIES_GLIGAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 75, 105, 85, 35, 65),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FLYING,
        .catchRate = 60,
        .expYield = 86,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SAND_VEIL},
        .abilityHidden = {ABILITY_IMMUNITY, ABILITY_TOXIC_BOOST},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//from zenmodeyt give fly - done

    [SPECIES_STEELIX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 85, 200, 30, 55, 65),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GROUND,
        .catchRate = 25,
        .expYield = 179,
        //.evYield_Defense = 2,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SHEER_FORCE, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_SAND_RUSH},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SNUBBULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 80, 50, 30, 40, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_RUN_AWAY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_GRANBULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 120, 75, 45, 60, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 158,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_QUICK_FEET},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_QWILFISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 95, 85, 85, 95, 65),
        .type1 = TYPE_WATER,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 88,
        //.evYield_Attack = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_POISON_POINT, ABILITY_SWIFT_SWIM},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_POISON_TOUCH},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SCIZOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 130, 100, 80, 55, 80),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 25,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWARM, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_DEFEATIST},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //give dual wingbeat and bug bite

    [SPECIES_SHUCKLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(20, 10, 230, 5, 10, 230),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ROCK,
        .catchRate = 190,
        .expYield = 177,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item1 = ITEM_BERRY_JUICE,
        //.item2 = ITEM_BERRY_JUICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STURDY, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_CONTRARY, ABILITY_SUCTION_CUPS}, //double check sturdy setup, should give perish song immunity, well let you sruvive it 
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_HERACROSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 125, 75, 85, 40, 95),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_GUTS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOXIE, ABILITY_MUSCLE_MAGIC},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SNEASEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 105, 55, 115, 35, 80),
        .type1 = TYPE_DARK,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 86,
        //.evYield_Speed = 1,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_KEEN_EYE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GUTS, ABILITY_PRESSURE},//pickpocket on this mon is compltely worthless   //swapping for guts or moxie
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_TEDDIURSA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 80, 50, 40, 50, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 66,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HONEY_GATHER, ABILITY_QUICK_FEET},
            .abilityHidden = {ABILITY_PICKUP, ABILITY_CUTE_CHARM},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_URSARING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 130, 75, 55, 75, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_QUICK_FEET},
            .abilityHidden = {ABILITY_GORILLA_TACTICS, ABILITY_UNNERVE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SLUGMA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 40, 40, 20, 88, 56),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 190,
        .expYield = 50,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_MAGMA_ARMOR, ABILITY_FLAME_BODY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIQUID_OOZE, ABILITY_GOOEY}, //make sure liquid ooze works on leech seed
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MAGCARGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 50, 120, 30, 115, 90),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_ROCK,
        .catchRate = 75,
        .expYield = 151,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_MAGMA_ARMOR, ABILITY_FLAME_BODY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_STEAM_ENGINE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//move give acid armor shell smash

    [SPECIES_SWINUB] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 50, 40, 50, 30, 30),
        .type1 = TYPE_ICE,
        .type2 = TYPE_GROUND,
        .catchRate = 225,
        .expYield = 50,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_SNOW_CLOAK},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PILOSWINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 80, 50, 60, 60),
        .type1 = TYPE_ICE,
        .type2 = TYPE_GROUND,
        .catchRate = 75,
        .expYield = 158,
        //.evYield_HP = 1,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_SNOW_CLOAK},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_CORSOLA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 65, 115, 35, 85, 110),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ROCK,
        .catchRate = 60,
        .expYield = 144,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_LUMINOUS_MOSS, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_HUSTLE, ABILITY_NATURAL_CURE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_REMORAID] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 65, 35, 65, 65, 35),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 60,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HUSTLE, ABILITY_SNIPER},
            .abilityHidden = {ABILITY_MOODY, ABILITY_INNER_FOCUS},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_OCTILLERY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 105, 75, 45, 105, 75),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SUCTION_CUPS, ABILITY_SNIPER},
            .abilityHidden = {ABILITY_MOODY, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DELIBIRD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(101, 95, 55, 95, 75, 55),
        .type1 = TYPE_ICE,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 116,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_UNNERVE, ABILITY_HUSTLE}, //ABILITY_ICE_BODY, ABILITY_UNNERVE
        .abilityHidden = {ABILITY_MULTI_TASK, ABILITY_MAGIC_GUARD},  //ABILITY_HUSTLE, ABILITY_MAGIC_GUARD
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //idk if I like these abilities

    [SPECIES_MANTINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 40, 70, 70, 80, 140),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 25,
        .expYield = 170,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_WATER_ABSORB},
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SKARMORY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 80, 140, 70, 40, 70),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FLYING,
        .catchRate = 25,
        .expYield = 163,
        //.evYield_Defense = 2,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //give better steel moves smart strike etc.

    [SPECIES_HOUNDOUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 85, 30, 65, 70, 50),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FIRE,
        .catchRate = 120,
        .expYield = 66,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_EARLY_BIRD, ABILITY_FLASH_FIRE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_HOUNDOOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 110, 50, 95, 95, 80),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_EARLY_BIRD, ABILITY_FLASH_FIRE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_KINGDRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 95, 95, 85, 95, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 243,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_DRAGON_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWIFT_SWIM, ABILITY_SNIPER},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PHANPY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 60, 60, 46, 40, 40),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 120,
        .expYield = 66,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_PICKUP, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_SAND_RUSH},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DONPHAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 120, 120, 65, 60, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STURDY, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_SAND_RUSH},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//I guess keep low speed for use in trick room?

    [SPECIES_PORYGON2] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 80, 90, 60, 105, 95),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 180,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TRACE, ABILITY_DOWNLOAD},
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_VOLT_ABSORB},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_STANTLER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(73, 100, 62, 85, 85, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 163,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_FRISK},
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },
      

    [SPECIES_SMEARGLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 40, 35, 85, 40, 45),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 111,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PROTEAN, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_MOODY, ABILITY_SIMPLE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    }, //also slight increase in speed to help chose the right move
    
    [SPECIES_TYROGUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(78, 35, 35, 35, 35, 35),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 65,
        .expYield = 42,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(35),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_STEADFAST},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_PRESSURE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_HITMONTOP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(57, 95, 95, 70, 35, 115),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(35),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_STEADFAST, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SMOOCHUM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 30, 25, 65, 85, 65),
        .type1 = TYPE_ICE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 61,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_FOREWARN},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},//changed ability hydration sucks for this, one time pass on this ability as it makes sense here
        .bodyColor = BODY_COLOR_PINK, //dont know if cupids arrow works for this, ok check bulbapedia and its literally a baby lol, cute charm would work
        .noFlip = FALSE,    //thematically but  its defense is too low, gave it a little more def, and jynx line more hp overall,...may not need I kinda made ice defenses op...
    },//need rewrite dex for this, use bulbapedia info,  dex entries for this thing are kinda cursed... vsonic

    [SPECIES_ELEKID] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 63, 37, 95, 65, 55),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 72,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ELECTIRIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MAGBY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 75, 37, 83, 70, 55),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 73,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_MAGMARIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MILTANK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 80, 105, 100, 40, 80),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Defense = 2,
        //.item1 = ITEM_MOOMOO_MILK,
        //.item2 = ITEM_MOOMOO_MILK,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_STALL},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_BLISSEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(255, 30, 20, 55, 75, 135),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 30,
        .expYield = 608,
        //.evYield_HP = 3,
        //.item2 = ITEM_LUCKY_EGG,
        .genderRatio = MON_FEMALE,
        .eggCycles = 40,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_SERENE_GRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEALER, ABILITY_STALL},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_RAIKOU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 85, 75, 115, 115, 100),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Speed = 2,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_OVERCHARGE, ABILITY_GALVANIZE},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_ELECTRIC_SURGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //think I'll change volt and water absorb
    //to work like lightning rod where the element is auto drawn in

    //or in doubles assume its like the pokemon is jumping in
    //to protect its ally because it can't be hurt.

    //do same for flash fire motor drive & sap sipper
    //counter balance by making it only work for partner if mon with ability isn't statused
    //vsonic
   

    [SPECIES_ENTEI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(115, 115, 85, 100, 90, 75),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_HP = 1,
        //.evYield_Attack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_BLAZE, ABILITY_GUTS},
        .abilityHidden = {ABILITY_STEAM_ENGINE, ABILITY_FLASH_FIRE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SUICUNE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 75, 115, 85, 90, 115),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_TORRENT, ABILITY_REFRIGERATE},
        .abilityHidden = {ABILITY_PURIFYING_AURA, ABILITY_ICE_SCALES},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LARVITAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 64, 50, 41, 45, 50),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_GUTS, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_PUPITAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 84, 70, 51, 65, 65),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 144,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_TYRANITAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 134, 110, 61, 95, 100),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_SAND_STREAM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_MUSCLE_MAGIC},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_LUGIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(106, 90, 130, 110, 90, 154),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_PSYCHIC,  //dragon to resist 3 birds, and dragons have dominion over air and sea, psychic because it has bariers and is able to "talk"
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_THICK_FAT, ABILITY_NONE}, //thick fat to cover ice weakness
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MULTISCALE, ABILITY_NONE}, //pressure was just he default legendary ability,may just remove pressure for this
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_HO_OH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(106, 130, 90, 90, 110, 154),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpDefense = 3,
        //.item1 = ITEM_SACRED_ASH,
        //.item2 = ITEM_SACRED_ASH,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_REGENERATOR, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RISING_PHOENIX, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CELEBI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(120, 35, 110, 110, 130, 120),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_HP = 3,
        //.item1 = ITEM_LUM_BERRY,
        //.item2 = ITEM_LUM_BERRY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //Can make fairy type now that dual weakness is not so punishing

    [SPECIES_TREECKO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 45, 35, 70, 65, 55),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_GROVYLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(81, 65, 45, 95, 85, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_OVERGROW, ABILITY_ADAPTABILITY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_TECHNICIAN},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //I think I'll actually make this dragon here since other mon are getting their secondary at mid evo

    [SPECIES_SCEPTILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(97, 85, 65, 120, 105, 85),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON, //vintage white change, works for me as I made grass imune to fairy
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_OVERGROW, ABILITY_ADAPTABILITY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_TECHNICIAN},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//since is dragon may give flamethrower  //also acrobatics if doesn't already incinerate & fire blast & outrage

    [SPECIES_TORCHIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 60, 40, 45, 70, 50),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_COMBUSKEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 85, 60, 55, 85, 60),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BLAZIKEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 120, 70, 80, 110, 70),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MUDKIP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 70, 50, 40, 50, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MARSHTOMP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 85, 70, 50, 60, 70),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SWAMPERT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 110, 90, 60, 85, 90),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 241,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_POOCHYENA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 55, 35, 35, 30, 30),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_QUICK_FEET},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MIGHTYENA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 105, 70, 77, 60, 60),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 127,
        .expYield = 147,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_QUICK_FEET},
            .abilityHidden = {ABILITY_MOXIE, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_ZIGZAGOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(38, 40, 41, 70, 30, 41),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Speed = 1,
        //.item1 = ITEM_POTION,
        //.item2 = ITEM_REVIVE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_SPEED_BOOST}, //Whim
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_LINOONE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(78, 85, 61, 100, 50, 61),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 147,
        //.evYield_Speed = 2,
        //.item1 = ITEM_POTION,
        //.item2 = ITEM_MAX_REVIVE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_SPEED_BOOST},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_WURMPLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 45, 35, 20, 20, 30),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_HP = 1,
        //.item1 = ITEM_PECHA_BERRY,
        //.item2 = ITEM_BRIGHT_POWDER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SILCOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 35, 55, 15, 25, 25),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 72,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_BEAUTIFLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 70, 60, 90, 105, 60),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 178,
        //.evYield_SpAttack = 3,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_SHED_SHELL,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RIVALRY, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//changed to just pure bug, since it doesn't learn fly
    //or have many flying moves,
    //will need to add to non-grounded list, so it still avoides ground moves.
    
    //will do the same for dustox and other winged-non flying types

    [SPECIES_CASCOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 35, 55, 15, 25, 25),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 72,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DUSTOX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 60, 70, 85, 60, 105),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_SpDefense = 3,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_SHED_SHELL, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        .abilityHidden = {ABILITY_COMPOUND_EYES, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//potentially give switchin ability that sets powder to enemy side? would allow free switch into fire

    [SPECIES_LOTAD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(56, 30, 30, 30, 40, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 44,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_RAIN_DISH},
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_LOMBRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(77, 50, 50, 60, 60, 70),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 119,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_RAIN_DISH},
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_LUDICOLO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(92, 70, 70, 70, 90, 100),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 216,
        //.evYield_SpDefense = 3,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_RAIN_DISH},
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_RAIN_DISH},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SEEDOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(59, 40, 50, 30, 30, 50),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 44,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_POWER_HERB, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_EARLY_BIRD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_NUZLEAF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 82, 40, 80, 60, 40),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DARK,
        .catchRate = 120,
        .expYield = 119,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_POWER_HERB, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_INFILTRATOR},//why does it need earlybird? its grass dark, its immune to all forms of sleep?
        //#ifdef BATTLE_ENGINE          //ok so thats not actually how status moves worked, but I tweaked so status moves that set status 1, have to pass type immunity check
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE}, //with chlorophyll water sport, should outspeed pretty much everything
        // #endif
        .bodyColor = BODY_COLOR_BROWN, //give moves feint and watersport think also give mudsport. hmm good idea since I removed grass electirc resistance, so give them both mudsport/watersport 
        .noFlip = FALSE,    //as both water and mud/ground are important for plants  vsonic
    },

    [SPECIES_SHIFTRY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(92, 100, 88, 70, 90, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 216,
        //.evYield_Attack = 3,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_POWER_HERB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_INFILTRATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //give knock off grassy glide

    [SPECIES_TAILLOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 55, 30, 85, 30, 30),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 200,
        .expYield = 54,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_GUTS, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SWELLOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 100, 60, 125, 75, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_GUTS, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WINGULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 30, 30, 85, 65, 30),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 54,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item1 = ITEM_PRETTY_WING,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_HYDRATION},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_PELIPPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 50, 120, 65, 100, 70),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 154,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
            //.item1 = ITEM_PRETTY_WING,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_SQUALL},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_RALTS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(32, 25, 25, 40, 45, 35),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 235,
        .expYield = 40,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_EMPATH, ABILITY_TRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FOREWARN, ABILITY_TELEPATHY},//on purpose can replace with forewarn
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_KIRLIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(56, 35, 55, 50, 70, 55),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 97,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_EMPATH, ABILITY_TRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FOREWARN, ABILITY_TELEPATHY},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GARDEVOIR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(78, 65, 65, 85, 125, 115),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 233,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_EMPATH, ABILITY_TRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FOREWARN, ABILITY_TELEPATHY},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SURSKIT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 42, 32, 65, 50, 52),
        .type1 = TYPE_BUG,
        .type2 = TYPE_WATER,
        .catchRate = 200,
        .expYield = 54,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item1 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MASQUERAIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 60, 62, 90, 100, 102),
        .type1 = TYPE_BUG,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 200,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_SWIFT_SWIM}, //keep this cuz water strider can still stand on water w wings
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SHROOMISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 40, 60, 35, 40, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 59,
        //.evYield_HP = 1,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EFFECT_SPORE, ABILITY_POISON_HEAL},
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BRELOOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(77, 130, 80, 70, 60, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FIGHTING,
        .catchRate = 90,
        .expYield = 161,
        //.evYield_Attack = 2,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EFFECT_SPORE, ABILITY_POISON_HEAL},
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SLAKOTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 60, 60, 30, 35, 35),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TRUANT, ABILITY_NONE},
        .abilityHidden = {ABILITY_MOODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VIGOROTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 100, 80, 90, 55, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 154,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_VITAL_SPIRIT, ABILITY_NONE},
        .abilityHidden = {ABILITY_MULTI_TASK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SLAKING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(150, 160, 100, 100, 95, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 252,
        //.evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TRUANT, ABILITY_NONE},
        .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_SLOW_START},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_NINCADA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(31, 45, 90, 40, 30, 30),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_Defense = 1,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_COMPOUND_EYES, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_NINJASK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(61, 110, 45, 160, 50, 50),
        .type1 = TYPE_BUG,
        .type2 = TYPE_DARK,
        .catchRate = 120,
        .expYield = 160,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SPEED_BOOST, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //give fell stinger

    [SPECIES_SHEDINJA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(27, 90, 45, 40, 30, 30),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 83,
        //.evYield_HP = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_WONDER_GUARD, ABILITY_DISPIRIT_GUARD},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_WHISMUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(64, 56, 36, 28, 51, 36),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 48,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SOUNDPROOF, ABILITY_RATTLED},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OBLIVIOUS, ABILITY_UNAWARE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    }, //add disarming voice to learn set

    [SPECIES_LOUDRED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(84, 80, 43, 48, 80, 43),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 126,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SOUNDPROOF, ABILITY_SCRAPPY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NO_GUARD, ABILITY_SONAR},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_EXPLOUD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(104, 91, 63, 68, 91, 73),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 221,
        //.evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SOUNDPROOF, ABILITY_SCRAPPY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NO_GUARD, ABILITY_SONAR},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MAKUHITA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(72, 60, 30, 25, 20, 30),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 180,
        .expYield = 47,
        //.evYield_HP = 1,
        ////.item1 = ITEM_FLAME_ORB
        //.item2 = ITEM_BLACK_BELT,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_THICK_FAT, ABILITY_GUTS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_HARIYAMA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(144, 120, 60, 50, 40, 60),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 200,
        .expYield = 166,
        //.evYield_HP = 2,
        ////.item1 = ITEM_FLAME_ORB
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_THICK_FAT, ABILITY_GUTS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_AZURILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 20, 40, 20, 36, 40),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 150,
        .expYield = 38,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_THICK_FAT, ABILITY_HUGE_POWER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NOSEPASS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 45, 135, 30, 45, 90),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 255,
        .expYield = 75,
        //.evYield_Defense = 1,
        //.item2 = ITEM_MAGNET,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_MAGNET_PULL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//change evo to work with certain type in party, either electric type or electric & steel stype [DONE]

    [SPECIES_SKITTY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 45, 45, 50, 35, 35),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 52,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 15,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_NORMALIZE},
            .abilityHidden = {ABILITY_WONDER_SKIN, ABILITY_RATTLED},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },//higher hp isn't meant to denote bulk, but a high vitality/zest for life/energy

    [SPECIES_DELCATTY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 75, 65, 81, 75, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GHOST,
        .catchRate = 60,
        .expYield = 140,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_NORMALIZE},
            .abilityHidden = {ABILITY_WONDER_SKIN, ABILITY_RATTLED},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    }, //stopped making major stat buffs
    //started focusing on smaller tweaks and abilities
    //new update made ghost type to cover its weaker stats, leans on the cats 9 lives thing
    //its a live but techinically could have been dead.  prob need tweak its pokedex entry to fit
    [SPECIES_SABLEYE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(68, 85, 75, 47, 65, 65),
        .type1 = TYPE_DARK,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 133,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_WIDE_LENS,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_JEWEL_METABOLISM, ABILITY_ANALYTIC},
            .abilityHidden = {ABILITY_NUISANCE, ABILITY_INFILTRATOR},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//plan boosting attack, potentially boost hp, but keep in line with small sneaky mon
    //atk isn't too bad in itself thought to raise to close to gabite, since its mentioned as a competiter in its dex gabite is atk 90
    //only reason its attack is mentioned is more because of its bad moves (lost payback in late gen) and relative frailty with low speed
    //gabite has similar similar def/spdef but 20 more hp, 20 more atk and double speed...
    //think will boost hp, keep atk where it is, there's no reason for to be so low hp, its not a pre evo
    [SPECIES_MAWILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 87, 90, 55, 65, 75),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 133,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_IRON_BALL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_INTIMIDATE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_STRONG_JAW},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//adjust learnset to give all bite moves

    [SPECIES_ARON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 70, 100, 30, 40, 55),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_ROCK,
        .catchRate = 180,
        .expYield = 66,
        //.evYield_Defense = 1,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_STURDY, ABILITY_ROCK_HEAD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_LAIRON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 90, 140, 40, 50, 65),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_ROCK,
        .catchRate = 90,
        .expYield = 151,
        //.evYield_Defense = 2,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_STURDY, ABILITY_ROCK_HEAD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_AGGRON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 110, 180, 50, 60, 80),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Defense = 3,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_STURDY, ABILITY_ROCK_HEAD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MEDITITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 40, 55, 60, 40, 55),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 180,
        .expYield = 56,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_PURE_POWER, ABILITY_FOREWARN},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },//note add explosion and self destruct to list of immune moves

    [SPECIES_MEDICHAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 60, 75, 80, 60, 75),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 144,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_PURE_POWER, ABILITY_FOREWARN},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ELECTRIKE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 45, 40, 65, 65, 40),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 120,
        .expYield = 59,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_MINUS, ABILITY_PLUS},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MANECTRIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 75, 60, 105, 105, 60),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_MINUS, ABILITY_PLUS},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PLUSLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 50, 40, 95, 85, 75),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 200,
        .expYield = 142,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_CELL_BATTERY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_PLUS, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MINUN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 40, 50, 95, 75, 85),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 200,
        .expYield = 142,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_CELL_BATTERY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_MINUS, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_VOLBEAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 53, 75, 85, 77, 85),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ELECTRIC, 
        .catchRate = 150,
        .expYield = 151,
        //.evYield_Speed = 1,
        //.item2 = ITEM_BRIGHT_POWDER,
        .genderRatio = MON_MALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_ILLUMINATE, ABILITY_SWARM},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_VOLT_ABSORB},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_ILLUMISE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 47, 75, 95, 73, 85),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,    //grass for sweet smelling  fragance/aroma
        .catchRate = 150,
        .expYield = 151,
        //.evYield_Speed = 1,
        //.item2 = ITEM_BRIGHT_POWDER,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_TINTED_LENS},
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    }, //give grass and fairy moves and acrobatics  strength sap

    [SPECIES_ROSELIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 60, 45, 65, 100, 90),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 150,
        .expYield = 140,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_POISON_POINT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LEAF_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_GULPIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 43, 53, 40, 43, 63),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 225,
        .expYield = 60,
        //.evYield_HP = 1,
        //.item1 = ITEM_ORAN_BERRY,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_LIQUID_OOZE, ABILITY_STICKY_HOLD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SWALOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 73, 83, 55, 83, 87),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 163,
        //.evYield_HP = 2,
        //.item1 = ITEM_ORAN_BERRY,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_LIQUID_OOZE, ABILITY_STICKY_HOLD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CARVANHA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 90, 20, 65, 65, 20),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_Attack = 1,
        //.item2 = ITEM_DEEP_SEA_TOOTH,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SHARPEDO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 120, 40, 95, 95, 40),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 60,
        .expYield = 161,
        //.evYield_Attack = 2,
        //.item2 = ITEM_DEEP_SEA_TOOTH,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_MOXIE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WAILMER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(130, 70, 35, 60, 70, 35),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 125,
        .expYield = 80,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_THICK_FAT, ABILITY_OBLIVIOUS},
        .abilityHidden = {ABILITY_SONAR, ABILITY_UNBURDEN},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WAILORD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(170, 90, 45, 60, 90, 45),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_THICK_FAT, ABILITY_OBLIVIOUS},
        .abilityHidden = {ABILITY_SONAR, ABILITY_UNBURDEN},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NUMEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 60, 40, 35, 65, 45),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 61,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_SIMPLE},
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CAMERUPT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 100, 70, 40, 105, 75),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GROUND,
        .catchRate = 150,
        .expYield = 161,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGMA_ARMOR, ABILITY_SOLID_ROCK},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //keep an eye on this, vsonic, see if with super change it survives well enough or needs more bulk

    [SPECIES_TORKOAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 95, 140, 20, 95, 70),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 90,
        .expYield = 165,
        //.evYield_Defense = 2,
        //.item2 = ITEM_CHARCOAL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_WHITE_SMOKE, ABILITY_SUN_DISK},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_MAGMA_ARMOR},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SPOINK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 25, 35, 60, 70, 80),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 255,
        .expYield = 66,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_THICK_FAT, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_INNER_FOCUS},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_GRUMPIG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 45, 65, 80, 90, 110),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_DARK,
        .catchRate = 60,
        .expYield = 165,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_THICK_FAT, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_DANCER},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//vsonic plan to adjust front sprite / prob need do back as well to match

    [SPECIES_SPINDA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(88, 88, 88, 88, 88, 88),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 126,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OWN_TEMPO, ABILITY_CONTRARY},
            .abilityHidden = {ABILITY_NORMALIZE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TRAPINCH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 110, 55, 10, 45, 65),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Attack = 1,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_ARENA_TRAP},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STRONG_JAW, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //give trick room via tm //potentially give sturdy? slow but w sturdy could be a revenge killer?
    //well could just do focus band for that, and eviolite is also an option now

    [SPECIES_VIBRAVA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 70, 50, 70, 50, 50),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_DRAGON,
        .catchRate = 120,
        .expYield = 119,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SAND_FORCE, ABILITY_SAND_RUSH},
        .abilityHidden = {ABILITY_SIROCCO, ABILITY_DRY_SKIN},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //because of bioligy give vibrava gastro acid  vsonic

    [SPECIES_FLYGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 100, 80, 100, 80, 80),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 234,
        //.evYield_Attack = 1,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SAND_RUSH},
        .abilityHidden = {ABILITY_SIROCCO, ABILITY_DRY_SKIN},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CACNEA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 85, 40, 55, 85, 40),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_STICKY_BARB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_TOUGH_SPINES},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_HEATPROOF},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //give crass equivalent of rough skin  tough spines 

    [SPECIES_CACTURNE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 115, 60, 75, 115, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DARK,
        .catchRate = 60,
        .expYield = 166,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_STICKY_BARB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_SAND_VEIL, ABILITY_TOUGH_SPINES},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_HEATPROOF},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SWABLU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 40, 60, 50, 40, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 62,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_CLOUD_NINE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ALTARIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 70, 90, 80, 77, 105),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_CLOUD_NINE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZANGOOSE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(73, 115, 60, 100, 60, 60),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DARK, //WOULD now be 4x  to fighting and fairy, but its fast enough to overcome that idea from Lockstin & Gnoggin
        .catchRate = 90,
        .expYield = 160,
        //.evYield_Attack = 2,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_IMMUNITY, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TOXIC_BOOST, ABILITY_DEFIANT},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SEVIPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(73, 80, 70, 70, 95, 85),
        .type1 = TYPE_POISON,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 160,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_INFILTRATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MERCILESS, ABILITY_COMPETITIVE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_LUNATONE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 65, 65, 70, 105, 85),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 161,
        //.evYield_SpAttack = 2,
        //.item1 = ITEM_STARDUST,
        //.item2 = ITEM_MOON_STONE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_SOLID_ROCK, ABILITY_PHOTOSYNTHESIZE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //idea lunar power boost in rain? flooding rising tides type deal, maybe double sp def?
    //potentially use moonlight, animation and day/night shift for battle to make lunar weather condition
    //that boosts fairy sp def or fairy move dmg, then setup field move w sunny day to  auto shift 
    //day night schedule will be an ow triggering move, like using strength or fly
    //so think rather than an instant flip ship should greatly speed of time progression
    //so dns would shift each minute from current blend/ until it reaches the target time frame and then return to 
    //normal progression  i.e use moon dance, during afternoon, so each minute shift to  evening twilight to night
    //for opposite using sunny day from their would shift, from night, to twilight, to day.

    [SPECIES_SOLROCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 95, 85, 70, 85, 65),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 161,
        //.evYield_Attack = 2,
        //.item1 = ITEM_STARDUST,
        //.item2 = ITEM_SUN_STONE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_SOLAR_POWER, ABILITY_FLASH_FIRE},
        .abilityHidden = {ABILITY_SOLID_ROCK, ABILITY_PHOTOSYNTHESIZE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BARBOACH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 48, 73, 60, 46, 71),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 190,
        .expYield = 58,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_ANTICIPATION},
            .abilityHidden = {ABILITY_HYDRATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //gave evolved defenses since its mostly hp that grows, speed was alraedy same

    [SPECIES_WHISCASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 98, 73, 60, 76, 71),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 75,
        .expYield = 164,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_ANTICIPATION},
            .abilityHidden = {ABILITY_HYDRATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CORPHISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(43, 80, 65, 35, 50, 35),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 205,
        .expYield = 62,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CRAWDAUNT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(63, 120, 85, 55, 90, 55),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 155,
        .expYield = 164,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BALTOY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 40, 55, 55, 40, 70),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_SpDefense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LIGHT_CLAY,
        // #endif
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_DRY_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_CLAYDOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 70, 105, 75, 70, 120),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 175,
        //.evYield_SpDefense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LIGHT_CLAY,
        // #endif
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_DRY_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_LILEEP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 41, 77, 23, 61, 87),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_SpDefense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BIG_ROOT,
        // #endif
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_SUCTION_CUPS, ABILITY_OCEAN_MEMORY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_SOLID_ROCK},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CRADILY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(96, 81, 97, 43, 81, 107),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_SpDefense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BIG_ROOT,
        // #endif
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_SUCTION_CUPS, ABILITY_OCEAN_MEMORY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_SOLID_ROCK},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ANORITH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 95, 70, 75, 40, 50),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_BUG,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_OCEAN_MEMORY},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_LIQUID_SOUL},//GAVE this based on ultra sun dex entry, use that dex for mon
        .bodyColor = BODY_COLOR_GRAY,   //don't know why I wnted ultra sun dex for this, and liquid soul doesn't make sense here or at all.
        .noFlip = FALSE,    //it'd be for mon that aren't water type, so don't get stab, but just get rain boosted ghost moves  but ghost is a defensive not offensive type in my game, so not worth
    },  //also let it learn rain dance tm

    [SPECIES_ARMALDO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 125, 100, 45, 70, 80),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_BUG,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_OCEAN_MEMORY},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_LIQUID_SOUL},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //think keep rock bug, give move forge to make it bug steel?

    [SPECIES_FEEBAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(37, 35, 40, 80, 30, 125),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 40,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_OBLIVIOUS},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_CONTRARY}, //think shrugging off mental attacks, hm actually contrary would be better for this?
        // #endif       //yeah contary works psychs itself up against negatives, but can't take positives for what they are
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE, //wanna give move mud bomb
    },//change give high sp def think thick skin from everyone calling it ugly

    [SPECIES_MILOTIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 60, 79, 81, 100, 125),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 189,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MARVEL_SCALE, ABILITY_COMPETITIVE},
        .abilityHidden = {ABILITY_CUTE_CHARM, ABILITY_DEFIANT},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_CASTFORM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 70, 70, 70, 70, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GHOST,    //with planned changes makes it a better switch mon, also kinda works think of like casper a friendly ghost
        .catchRate = 45,
        .expYield = 147,
        //.evYield_HP = 1,
        //.item1 = ITEM_MYSTIC_WATER,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_FORECAST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KECLEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 90, 70, 40, 75, 120),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 200,
        .expYield = 154,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_COLOR_CHANGE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SHUPPET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(44, 75, 35, 45, 63, 33),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DARK,
        .catchRate = 225,
        .expYield = 59,
        //.evYield_Attack = 1,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EMPATHIC_CURSE, ABILITY_FRISK},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_ILLUSION},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    }, //found at night typically arodn urban areas as it feeds off negativity
    //pressure is good but think  I need, make value check to make sure it can't trigger twice in doubles in a turn
    //lowered odds to balance //I think I prefer illusion for this over pressure? but still need adjust pressure/hi-pressure
    // - or not its not a field status its target based

    [SPECIES_BANETTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(64, 115, 65, 65, 83, 63),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_Attack = 2,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EMPATHIC_CURSE, ABILITY_FRISK}, //buffed frisk
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_ILLUSION}, //change illusinon effect for wilds, make select random mon from encounter table
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//it doesnt get many contact moves with effects so it still cant do much with frisk
    //zenmode yt had idea to give synchronize since its like voodoo doll, which I like, but realized illusion is also interesting
    //pressure was given to help its slow nature but idk

    [SPECIES_DUSKULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(20, 40, 90, 25, 30, 90),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST, //think want to keep full ghost so banette is more unique
        .catchRate = 190,
        .expYield = 59,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_UNNERVE, ABILITY_INFILTRATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRISK, ABILITY_BAD_DREAMS},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_DUSCLOPS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 70, 130, 25, 60, 130),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 90,
        .expYield = 159,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_PRESSURE, ABILITY_INFILTRATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRISK, ABILITY_BAD_DREAMS},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_TROPIUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 80, 83, 51, 72, 95),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 200,
        .expYield = 238,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SOLAR_POWER},
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CHIMECHO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 80, 49, 65, 95, 90),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 159,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_CLEANSE_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_TELEPATHY, ABILITY_NONE},
        .abilityHidden = {ABILITY_FILTER, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ABSOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 130, 60, 75, 75, 60),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 30,
        .expYield = 163,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DARK_DEAL, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_JUSTIFIED},  //WITH dark type change, had remove justified
        .bodyColor = BODY_COLOR_WHITE, //actually dark deal makes more sense, call it devils luck
        .noFlip = FALSE,
    },//actually maybe keep justified over ABILITY_DARK_DEAL, absol isn't bad/evil plus w super mul drop it may survive to get the dbenefit?

    [SPECIES_WYNAUT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 23, 48, 23, 23, 48),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 125,
        .expYield = 52,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SHADOW_TAG, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TELEPATHY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SNORUNT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 50, 50, 50, 50, 50),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 190,
        .expYield = 60,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
            ////.item2 = ITEM_SNOWBALL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INNER_FOCUS, ABILITY_ICE_BODY},
            .abilityHidden = {ABILITY_MOODY, ABILITY_INNER_FOCUS},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_GLALIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 95, 100, 60, 60, 75),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ROCK,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOLID_ROCK, ABILITY_ICE_BODY},
            .abilityHidden = {ABILITY_MOODY, ABILITY_INNER_FOCUS},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SPHEAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 40, 50, 25, 55, 50),
        .type1 = TYPE_ICE,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_ICE_BODY},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_SLUSH_RUSH},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SEALEO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 60, 70, 45, 75, 70),
        .type1 = TYPE_ICE,
        .type2 = TYPE_WATER,
        .catchRate = 120,
        .expYield = 144,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_ICE_BODY},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_SLUSH_RUSH},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WALREIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 80, 90, 65, 95, 90),
        .type1 = TYPE_ICE,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_THICK_FAT, ABILITY_ICE_BODY},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_SLUSH_RUSH},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CLAMPERL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(35, 64, 125, 32, 74, 55),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 69,
        //.evYield_Defense = 1,
        //.item1 = ITEM_PEARL,
        //.item2 = ITEM_BIG_PEARL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },  //nother update for mon with very different evo form, so they serve a different purpose/ i.e are self-sufficient in base form 
    //but then can evolve to suit a different purpose/niche  keep an eye on this balance wise

    [SPECIES_HUNTAIL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 104, 95, 72, 94, 75),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 170,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        //.item2 = ITEM_DEEP_SEA_TOOTH,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GOREBYSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 84, 75, 72, 114, 95),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 170,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_DEEP_SEA_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HYDRATION, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_RELICANTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 90, 130, 55, 45, 65),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ROCK,
        .catchRate = 25,
        .expYield = 170,
        //.evYield_HP = 1,
        //.evYield_Defense = 1,
        //.item2 = ITEM_DEEP_SEA_SCALE,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_STURDY, ABILITY_ROCK_HEAD},
        .abilityHidden = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_LUVDISC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(43, 55, 71, 77, 55, 88),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 225,
        .expYield = 116,
        //.evYield_Speed = 1,
        //.item1 = ITEM_HEART_SCALE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_CUPIDS_ARROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,//changed to 100% make luv disc a stall/setup mon add moves as needed. give early game endure
    }, //NEW ability will be 33% or 50% chance to infatuate on switch in loop check for target that can infatuate if double use trace targetting
    //stat ajustments made using numbers for love
    [SPECIES_BAGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 75, 60, 50, 40, 30),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Attack = 1,
        //.item2 = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_DEFIANT},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SHELGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 95, 100, 50, 60, 50),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Defense = 2,
        //.item2 = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_ROCK_HEAD, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_SHELL_ARMOR},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SALAMENCE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 135, 80, 100, 110, 80),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_Attack = 3,
        //.item2 = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOXIE, ABILITY_DEFIANT},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BELDUM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 55, 80, 30, 35, 60),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 60,
        //.evYield_Defense = 1,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_ANALYTIC}, //ABILITY_BATTLE_ARMOR  if keep own tempo could give outrage/thrash, but battle armor makes more sense
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_LIGHT_METAL},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_METANG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 75, 100, 50, 55, 80),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 147,
        //.evYield_Defense = 2,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_ANALYTIC},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_LIGHT_METAL},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_METAGROSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 135, 130, 70, 95, 90),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Defense = 3,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_MULTI_TASK},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_LIGHT_METAL},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_REGIROCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 100, 200, 50, 50, 100),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_EROSION, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_REGICE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 50, 100, 50, 100, 200),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_GLACIAL_ICE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, 

    [SPECIES_REGISTEEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 75, 150, 50, 75, 150),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Defense = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIQUID_METAL, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_LATIAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 80, 90, 110, 110, 130),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SPECTRE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//delve into their ability to turn invisible
    //start battle with +1 evasion so they are just harder to hit without needing a setup
    //red spector blue spector?Spectre  or spectrum blend?  that works, just make it a switch in ability that would increase evasiveness, so they can effectively start boosted +1 potentially +2

    [SPECIES_LATIOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 90, 80, 110, 130, 110),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SPECTRE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_KYOGRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 90, 90, 150, 140),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 3,
        .expYield = 302,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_DRIZZLE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GROUDON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 150, 140, 90, 100, 90),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 302,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_DROUGHT, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//now that it exists give solar blade instead

    [SPECIES_RAYQUAZA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 150, 90, 95, 150, 90),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_Attack = 2,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_AIR_LOCK, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_JIRACHI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 100, 100, 100, 100),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_HP = 3,
        //.item1 = ITEM_STAR_PIECE,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_MAGIC_BOUNCE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_DEOXYS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 150, 50, 150, 150, 50),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TURTWIG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 68, 64, 31, 45, 55),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_GROTLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 89, 85, 36, 55, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_TORTERRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(112, 109, 105, 56, 75, 85),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 236,
        //.evYield_Attack = 2,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //give shell smash

    [SPECIES_CHIMCHAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(44, 58, 44, 61, 58, 44),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MONFERNO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(64, 78, 52, 81, 78, 52),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_INFERNAPE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 104, 71, 108, 104, 71),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 240,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PIPLUP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(53, 51, 53, 40, 61, 56),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 63,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_COMPETITIVE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PRINPLUP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 66, 68, 50, 81, 76),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_COMPETITIVE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_EMPOLEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(104, 86, 88, 60, 111, 101),
        .type1 = TYPE_WATER,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_COMPETITIVE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_STARLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 55, 30, 60, 30, 30),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 49,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_EARLY_BIRD},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_STARAVIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 75, 50, 80, 40, 40),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 119,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_AVIATOR},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_STARAPTOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(95, 120, 70, 100, 50, 60),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 218,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_AVIATOR},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BIDOOF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(69, 45, 40, 31, 35, 40),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 50,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SIMPLE, ABILITY_UNAWARE},
            .abilityHidden = {ABILITY_MOODY, ABILITY_NORMALIZE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BIBAREL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(89, 95, 80, 71, 55, 77),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_WATER,
        .catchRate = 127,
        .expYield = 144,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SIMPLE, ABILITY_UNAWARE},
            .abilityHidden = {ABILITY_MOODY, ABILITY_MOLD_BREAKER},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KRICKETOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(37, 35, 51, 25, 25, 41),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 39,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_METRONOME,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_KRICKETUNE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(77, 104, 51, 87, 55, 51),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 45,
        .expYield = 158,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_METRONOME,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SHINX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 77, 34, 45, 50, 34),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 235,
        .expYield = 53,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_GUTS},
        .abilityHidden = {ABILITY_STRONG_JAW, ABILITY_RIVALRY},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LUXIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 95, 49, 60, 70, 49),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 120,
        .expYield = 127,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_GUTS},
        .abilityHidden = {ABILITY_STRONG_JAW, ABILITY_RIVALRY},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LUXRAY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 130, 79, 72, 95, 79),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 235,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_GUTS},
        .abilityHidden = {ABILITY_STRONG_JAW, ABILITY_SHADOW_TAG},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //increase attack because so few physical electric moves

    [SPECIES_BUDEW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 30, 35, 55, 50, 77),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_POISON_POINT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LEAF_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ROSERADE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 70, 65, 90, 125, 105),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 232,
        //.evYield_SpAttack = 3,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_POISON_POINT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CRANIDOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(67, 125, 40, 58, 30, 30),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 70,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_BULLETPROOF},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //THERE'S nothing rock like about most fossil mon, just them being from fossils, and from the stone age... most of this ones moves are normal too

    [SPECIES_RAMPARDOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(97, 165, 60, 58, 65, 50),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_BULLETPROOF},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SHIELDON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 42, 118, 30, 42, 88),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 70,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_STURDY, ABILITY_LIGHT_METAL},
        .abilityHidden = {ABILITY_SOUNDPROOF, ABILITY_BULLETPROOF},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //gave light metal here heavy metal on evo, so this form can suit different niche

    [SPECIES_BASTIODON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 52, 168, 30, 47, 138),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_STURDY, ABILITY_HEAVY_METAL},
        .abilityHidden = {ABILITY_SOUNDPROOF, ABILITY_BULLETPROOF},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_BURMY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 29, 45, 36, 29, 45),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 45,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_ANTICIPATION, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //boost with move variety rather than stats for early bugs like this vsonic

    [SPECIES_WORMADAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 79, 75, 66, 89, 85),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 148,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ANTICIPATION, ABILITY_LEAF_GUARD},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_GRASS_PELT},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MOTHIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(77, 94, 50, 86, 94, 76),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 148,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = MON_MALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TINTED_LENS, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_COMBEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(30, 30, 42, 70, 30, 42),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 49,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HONEY_GATHER, ABILITY_NONE},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_SWARM},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_VESPIQUEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 80, 102, 45, 80, 102),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_PRESSURE, ABILITY_UNNERVE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_QUEENLY_MAJESTY, ABILITY_COMPETITIVE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PACHIRISU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 45, 70, 95, 95, 90),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 200,
        .expYield = 142,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_RUN_AWAY, ABILITY_PICKUP},
        .abilityHidden = {ABILITY_VOLT_ABSORB, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_BUIZEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 65, 35, 85, 60, 30),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//semi aquatic made part normal,  also gets wide variety of moves, hgih speed so should still be able to handle fighting types

    [SPECIES_FLOATZEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 105, 55, 115, 85, 50),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 173,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_CHERUBI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 35, 45, 35, 62, 53),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 55,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_HEALER},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_CHERRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 60, 90, 85, 77, 117),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 158,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_GIFT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = TRUE,
    },

    [SPECIES_SHELLOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 48, 48, 34, 57, 62),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STICKY_HOLD, ABILITY_STORM_DRAIN},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GASTRODON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(111, 83, 68, 39, 92, 82),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STICKY_HOLD, ABILITY_STORM_DRAIN},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_AMBIPOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 100, 66, 115, 60, 66),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 169,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 20,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TECHNICIAN, ABILITY_MULTI_TASK},
            .abilityHidden = {ABILITY_SKILL_LINK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DRIFLOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 50, 34, 70, 60, 44),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FLYING,
        .catchRate = 125,
        .expYield = 70,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AFTERMATH, ABILITY_UNBURDEN},
            .abilityHidden = {ABILITY_FLARE_BOOST, ABILITY_NONE}, //still fixing aftermath, replace others with none
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DRIFBLIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(150, 80, 44, 80, 90, 54),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FLYING,
        .catchRate = 60,
        .expYield = 174,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AFTERMATH, ABILITY_UNBURDEN},
            .abilityHidden = {ABILITY_FLARE_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_BUNEARY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 66, 44, 85, 44, 56),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 70,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_KLUTZ},// 2 ideas for klutz, either they're klutz behavior makes the enemy not take them seriously
        .abilityHidden = {ABILITY_LIMBER, ABILITY_MULTI_TASK}, //ABILITY_KLUTZ  no instead I'll fix the ability
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,//so either klutz will be unable to hold items, but instead either take 75% damage or do 25% more damage I like the former, 
    },//like you're used to stumbling and falling so are able to shrug off blows...OK forgot i even made that note, came up with different idea will combine
    //klutz take 75% dmg and no damage from recoil effects i.e rockhead with dmg reduction DONE

    [SPECIES_LOPUNNY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 86, 84, 105, 74, 96),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 30,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_KLUTZ},
        .abilityHidden = {ABILITY_LIMBER, ABILITY_MULTI_TASK}, //ABILITY_KLUTZ
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MISMAGIUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(66, 66, 66, 105, 105, 105),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_PRANKSTER},
        .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_UNNERVE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_HONCHKROW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 125, 52, 71, 105, 52),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 205,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOXIE, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_INSOMNIA, ABILITY_DARK_DEAL},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_GLAMEOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(49, 55, 42, 85, 42, 37),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_LIMBER, ABILITY_OWN_TEMPO},
        .abilityHidden = {ABILITY_KEEN_EYE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_PURUGLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(89, 82, 74, 112, 64, 69),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 158,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_THICK_FAT, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_CHINGLING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 30, 50, 45, 65, 60),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 57,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_CLEANSE_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_TELEPATHY, ABILITY_NONE},
        .abilityHidden = {ABILITY_FILTER, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_STUNKY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(63, 63, 47, 74, 41, 57),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK,
        .catchRate = 225,
        .expYield = 66,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STENCH, ABILITY_AFTERMATH},
        .abilityHidden = {ABILITY_KEEN_EYE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    }, //see about giving its own uturn like, maybe dark one?  for aftermath well may not need. idk

    [SPECIES_SKUNTANK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(103, 93, 67, 84, 71, 84),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STENCH, ABILITY_AFTERMATH},
        .abilityHidden = {ABILITY_KEEN_EYE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_BRONZOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(57, 24, 86, 23, 24, 86),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Defense = 1,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEAVY_METAL, ABILITY_HEATPROOF},
            .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_BRONZONG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(67, 89, 116, 33, 79, 116),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 175,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEAVY_METAL, ABILITY_HEATPROOF},   //added as rain setter since apparently it does that in pokedex lore
            .abilityHidden = {ABILITY_SQUALL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_BONSLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(57, 80, 95, 10, 10, 45),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STURDY, ABILITY_SAP_SIPPER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RATTLED, ABILITY_ROCK_HEAD},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MIME_JR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(20, 25, 45, 60, 70, 90),
        //#if P_UPDATED_TYPES >= GEN_6
            .type1 = TYPE_PSYCHIC,
            .type2 = TYPE_NORMAL,
        .catchRate = 145,
        .expYield = 62,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOUNDPROOF, ABILITY_FILTER},
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_STALL},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_HAPPINY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 5, 5, 30, 35, 65),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 130,
        .expYield = 110,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
            //.item1 = ITEM_OVAL_STONE,
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 40,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_SERENE_GRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_CHATOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 65, 56, 91, 92, 55),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 144,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_METRONOME,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_TANGLED_FEET},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SPIRITOMB] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 92, 108, 35, 92, 108),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DARK,
        .catchRate = 100,
        .expYield = 170,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_PRESSURE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_DARK_DEAL},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GIBLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(58, 70, 45, 42, 40, 45),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GABITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(68, 90, 65, 82, 50, 55),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 144,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GARCHOMP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(108, 130, 95, 102, 80, 85),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_ROUGH_SKIN, ABILITY_NONE},
        .abilityHidden = {ABILITY_SIROCCO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },//MAKE new garchomp ability to replace sand spit, that works only on contact

    [SPECIES_MUNCHLAX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(135, 85, 40, 5, 40, 85),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 50,
        .expYield = 78,
        //.evYield_HP = 1,
        //.item1 = ITEM_LEFTOVERS,
        //.item2 = ITEM_LEFTOVERS,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_PICKUP, ABILITY_THICK_FAT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_RIOLU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 70, 40, 60, 35, 40),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 57,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_INNER_FOCUS},
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LUCARIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 110, 70, 90, 115, 70),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_INNER_FOCUS},
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_HIPPOPOTAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(68, 72, 78, 32, 38, 42),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 140,
        .expYield = 66,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_STREAM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_HIPPOWDON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(108, 112, 118, 47, 68, 72),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 60,
        .expYield = 184,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SAND_STREAM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SKORUPI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 50, 90, 65, 30, 62),
        .type1 = TYPE_POISON,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 66,
        //.evYield_Defense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_SNIPER},
        .abilityHidden = {ABILITY_KEEN_EYE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DRAPION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 90, 110, 95, 60, 83),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_Defense = 2,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_SNIPER},
        .abilityHidden = {ABILITY_KEEN_EYE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CROAGUNK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(52, 61, 40, 50, 61, 55),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FIGHTING,
        .catchRate = 140,
        .expYield = 60,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BLACK_SLUDGE,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ANTICIPATION, ABILITY_DRY_SKIN},
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_POISON_HEAL}, //poison touch does stack w  poison odds
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //needs more fighting moves barely learns any

    [SPECIES_TOXICROAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(83, 106, 65, 85, 86, 80),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FIGHTING,
        .catchRate = 75,
        .expYield = 172,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BLACK_SLUDGE,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ANTICIPATION, ABILITY_DRY_SKIN},
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_POISON_HEAL},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CARNIVINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(84, 113, 72, 46, 96, 72),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 200,
        .expYield = 159,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_LONG_REACH, ABILITY_STRONG_JAW},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_FINNEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(49, 49, 56, 66, 49, 61),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUORESCENCE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //vsonic,  I'm unsure how to make this good/interesting, doesn't have much identity
    //ok seems they are tyep of fish that absorb and store sunlight, could give ability so sun absorbing charge moves can fire without charge turn give solar beam/blade
    //Fluorescence, guess also raise speed and sp atk in sun? 1.5x  done should allow be only water mon able to run on sun  team
    //ya know I think this may be one of the few cases I need to just replcae other abilities entirely unless I massively buff its stats
    //it doens't really work and having just that ability makes it better thematically, its the water mon you run on sun teams

    [SPECIES_LUMINEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(69, 69, 76, 112, 69, 96),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 161,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUORESCENCE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MANTYKE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(45, 20, 50, 50, 65, 120),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 25,
        .expYield = 69,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_WATER_ABSORB},
        .abilityHidden = {ABILITY_WATER_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SNOVER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 62, 50, 40, 62, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_ICE,
        .catchRate = 120,
        .expYield = 67,
        //.evYield_Attack = 1,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_WARNING, ABILITY_NONE},
        .abilityHidden = {ABILITY_SOUNDPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ABOMASNOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(107, 92, 75, 60, 92, 85),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 173,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_WARNING, ABILITY_NONE},
        .abilityHidden = {ABILITY_SOUNDPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_WEAVILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 120, 65, 125, 45, 85),
        .type1 = TYPE_DARK,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 179,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_PRESSURE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GUTS, ABILITY_HI_PRESSURE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_MAGNEZONE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 70, 115, 60, 130, 90),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 30,
        .expYield = 241,
        //.evYield_SpAttack = 3,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_STURDY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_VOLT_ABSORB},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_LICKILICKY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 85, 95, 50, 80, 105),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_POISON,
        .catchRate = 30,
        .expYield = 180,
        //.evYield_HP = 3,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LAGGING_TAIL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_TOXUNGUE, ABILITY_OBLIVIOUS},//replace own tempo w new licki signature ability
        .abilityHidden = {ABILITY_CLOUD_NINE, ABILITY_ADAPTABILITY}, //think keep adaptability here, so serves a different niche, if want keep stall can use for eviolite strats
        .bodyColor = BODY_COLOR_PINK,   //was worried it'd be too strong?
        .noFlip = FALSE,
    },

    [SPECIES_RHYPERIOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(115, 140, 130, 40, 55, 85),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_ROCK,
        .catchRate = 30,
        .expYield = 241,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_SOLID_ROCK},
            .abilityHidden = {ABILITY_RECKLESS, ABILITY_ROCK_HEAD},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_TANGROWTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(120, 100, 125, 50, 110, 50),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 30,
        .expYield = 187,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_LEAF_GUARD},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ELECTIVIRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 123, 67, 95, 95, 85),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 30,
        .expYield = 243,
        //.evYield_Attack = 3,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ELECTIRIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOTOR_DRIVE, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MAGMORTAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 95, 67, 83, 125, 95),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 30,
        .expYield = 243,
        //.evYield_SpAttack = 3,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_MAGMARIZER,
        // #endif
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TOGEKISS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 50, 95, 80, 120, 115),
        //#if P_UPDATED_TYPES >= GEN_6
            .type1 = TYPE_FAIRY,
            .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 245,
        //.evYield_SpAttack = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_HUSTLE, ABILITY_SERENE_GRACE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SUPER_LUCK, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_YANMEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 76, 86, 105, 116, 56),
        .type1 = TYPE_BUG,
        .type2 = TYPE_DRAGON,
        .catchRate = 30,
        .expYield = 180,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_WIDE_LENS,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SPEED_BOOST, ABILITY_TINTED_LENS},
            .abilityHidden = {ABILITY_FRISK, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//give dragon rage, dragon breath outrage  dragon pulse draco meteor  //potentially rage

    [SPECIES_LEAFEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(86, 110, 130, 95, 60, 65),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_LEAF_GUARD},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_PHOTOSYNTHESIZE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_GLACEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(65, 60, 110, 69, 130, 95),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_SNOW_CLOAK},
            .abilityHidden = {ABILITY_CUTE_CHARM, ABILITY_ICE_BODY},    //just a lil troll :)
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GLISCOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 95, 125, 95, 45, 75),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 179,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_HYPER_CUTTER, ABILITY_SAND_VEIL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_POISON_HEAL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MAMOSWINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 130, 80, 80, 70, 60),
        .type1 = TYPE_ICE,
        .type2 = TYPE_GROUND,
        .catchRate = 50,
        .expYield = 239,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OBLIVIOUS, ABILITY_SNOW_CLOAK},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PORYGON_Z] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(85, 80, 70, 90, 135, 75),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 30,
        .expYield = 241,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ADAPTABILITY, ABILITY_DOWNLOAD},
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_VOLT_ABSORB},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_GALLADE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(68, 125, 65, 80, 65, 115),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 233,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_NONE},
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_PROBOPASS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 55, 145, 40, 75, 150),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 184,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_MAGNET,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_MAGNET_PULL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_DUSKNOIR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(55, 100, 135, 45, 65, 135),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DARK, //this keeps ghost dark,
        .catchRate = 45,
        .expYield = 236,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_PRESSURE, ABILITY_INFILTRATOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRISK, ABILITY_BAD_DREAMS},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_FROSLASS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 80, 70, 110, 90, 70),
        .type1 = TYPE_ICE,
        .type2 = TYPE_GHOST,
        .catchRate = 75,
        .expYield = 189,
        //.evYield_Speed = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_NONE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_ICE_SCALES},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ROTOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(66, 65, 77, 105, 103, 107), //shoudl be near fastest form as not weighed down by an object
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 154,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_INFILTRATOR, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_LIVEWIRE}, //here another ghost or dark ability
        .bodyColor = BODY_COLOR_RED, //replace ABILITY NONE with new ability LIVE_WIRE weaker version fo transistor 20% movedamage boost for electric types
        .noFlip = FALSE,
    },

    [SPECIES_UXIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 75, 130, 95, 75, 130),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Defense = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 30,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_INTHRALL, ABILITY_NONE}, //effect not yet set, should work like disable but with forewarn logic to choose move
        .bodyColor = BODY_COLOR_YELLOW, //beleive should work now? setup, put in ai decision and added all custom messages, still need test
        .noFlip = FALSE,
    },//knowledge/ memoery mon  can seal a move when they attack. the enemy
    //temporarily lose effect to use a move  think I'll make it only work on one move
    //and have it read the enemy move pool and create logic to attempt to pick the most
   //advantageous move of the enemies to seal. weight it to try doing that, (think there is ai logic that reads the most damaging move use that)
   //but have an option to fail, and instead just pick a random move slot i.e random % 4 0-3
   //can't reactivate ability on target is already under affect/thrall, (so use intimidate logic to save status to a variable i guess_
   //if enemy mon has  move sealed by another effect and that move is the most dangerous, either loop again excluding that or just default to random
   //ok anticipation logic, use that function to find move but then lock the move for long as I'm on field
   //works as switch in I guess //think of using psychic powers to read their most effective tactic and seal it away
   //will need exit message
   //vsonic IMPORTANT
    [SPECIES_MESPRIT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 95, 100, 80, 95, 100),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 30,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_EMPATHIC_CURSE, ABILITY_NONE}, //also given to banette line, but only mesprit best takes advantage of it with stats
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },//empath, emotion pokemon, give efffect of synchronize but also make attaker feel a portion of my pain
    //so attacker takes a percent of damage dealt 20% 25% something like that or maybe 15% //change call this empathic curse
    //as plan to make new synchronize buff its own ability & call that empath as realized its a mirror armor/corvinight copy/hybrid and I DON'T want that going on umbreon ...
    //eempathic curse is already set to pass status like the others
    [SPECIES_AZELF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 125, 70, 115, 125, 70),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 2,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 30,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_IRON_WILL, ABILITY_NONE}, //setup done //need test to make sure works
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },//iron will, will pokemon, paralysis effect, a chance to make opponent lose will to attack facing this mon.
    //in double battles use trace targeetting logic, so it randomly affects one target rather than both as that would be broken
    //well idk I could just link it to targeetting this mon with an attack, so even in doubles it'll just 
    //have a chance to activate on both enemy mon but only should they be targetting me. 
    //so its not just me being on the field would keep them from attacking
    //but I gave that effect to pressure so idk how it'd work? //perhaps make attack self or ally? 
    //or could put a  stat drop with it as they don't have the will to fully commit to the attack?
    //instead something like if break through paralysis has chance to drop gbattlemovedmg by 20% or so
    //yeah low chance (10%) to paralyze if breaks through paralyze chance has chance (25%)
    // to reduce dmg by a percentage, I think 20% dmg reduction
    //actually to make more noticeable think need raise dmg reduction chance maybe 40%

    [SPECIES_DIALGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 120, 120, 90, 150, 100),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },//time control two turn attacks skip the charge turn, but reduce power by 20% - change give that to recharge moves
    //2 turn moves go off in 1 turn with no downside
    //my change single turn moves hit twice, once normaly 2nd with reversed animation and a 50% damage cut ...maybe 70% cut that's still 130% dmg
    // can do like multi task, set multihit to 2, divide battlemovedamage by 2/multihit counter,  if multihitcounter == 1 (last hit) battlemovedamage x 120/100
    //simple to do, and would amount to 110% dmg, so a bit more balanced.
    //.8 x .5 ? 120% total,   gbattlemovedmg = 80%  and then if counter == 1  dmg = /2 hmm

    //idea is move goes off, then animation reverses hit effect goes off again and its counted as one move
    //like you attack reverse time and make them get hit again
    //ok intead of making entire new animation what I can do is create a point within the normal animation I can jump back
    //that'll appear like I'm reversing the attack?  check for ability time conrol at end of script, if not present just go to end
    //if present call time control animation to do some special animation and return
    //then jump back to set point in move animation and make sure it can't loop again, with some other variable decremented in time control anim
   //play move animation as normal from there, don't loop and go to end.
   //think will have it count as one attack, but just add a 30% damage buff idk which I'll do
   //simplest would just be to make it attack again like with multi-task...yeah I'll just do that.
   //but it'll be stronger since its not splitting the move damage so make all single turn moves
   //hit twice full damage on first hit, but 30% damage on 2nd hit, most of the logic for this is already in multi-task command 
   //so just use that.
   //...ikd I could still do the animation thing, wouldn't be too too hard
   //think time effect should use extreme speed/quick attack warp horizontal effects but make it grey or something
   //maybe do speed warp, grey out the field and characters, return colors to normal and then do 2nd hit?

   //god that really is going to be annnoying..  oh and add solar beam & future sight to its learnset skull bash too if it isn't already

    [SPECIES_PALKIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 120, 100, 100, 150, 120),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },//based on JPRPokeTrainer98 youtube vid ability space control, tweaked. 
    //in doubles make all non contact attacks multi target target both in doubles, target all in triple/rotation
    //target select if gcurrentmove has flag contact move change targetting to either n=both or enemy fiekd

    //in singles moves can't miss  -put  in acc check, cj=heck ability set accuracy to 0

    //since lives in void of space think make new palkia ability make it immune to ice, dmg
    

    [SPECIES_HEATRAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(91, 90, 106, 77, 130, 106),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_LAVA_FISSURE}, //not setup yet, set fire terrain weaken water
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_REGIGIGAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(110, 160, 110, 100, 80, 110),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_MYSTERY,  //just because its cool, its not in type chart so will just make everythinig neutral so has no effect
        .catchRate = 3,
        .expYield = 302,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SLOW_START, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GIRATINA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(150, 100, 120, 90, 100, 120),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_URSURPER, ABILITY_NONE},//replace with combination of competitive and defiant, known as ursurper 
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_CRESSELIA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(120, 70, 120, 85, 75, 130),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_AURA_OF_LIGHT, ABILITY_NONE}, //effeect should be done, need test switchin wake up
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//lunar spirit/aura/veil  prevents allies/self from falling asleep,  counter to darkai also reduces dark type damage by 50%
    //removes that 4x dark weakness I gave it, sheesh
    //like suicine ability heal should also work on switch in for anyone already asleep

    [SPECIES_PHIONE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(88, 88, 88, 88, 88, 88),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 30,
        .expYield = 216,
        //.evYield_HP = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYDRATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MANAPHY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 100, 100, 100, 100),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYDRATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DARKRAI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 90, 90, 125, 135, 90),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BAD_DREAMS, ABILITY_DESPAIR}, //anti heal for opposing side, make work for items too
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SHAYMIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(130, 100, 100, 100, 100, 100),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_HP = 3,
        //.item1 = ITEM_LUM_BERRY,
        //.item2 = ITEM_LUM_BERRY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_NATURAL_CURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(120, 120, 120, 120, 120, 120),
        .type1 = TYPE_MYSTERY,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },//nothing should ne higher normally

    [SPECIES_VICTINI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(100, 100, 100, 100, 100, 100),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FIRE,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_VICTORY_STAR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = TRUE,
    },

    [SPECIES_SNIVY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        45,
        55,
        63,
        45,
        55),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_CONTRARY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_PRANKSTER},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SERVINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        73,
        60,
        75,
        83,
        60,
        75
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 145,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_CONTRARY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_PRANKSTER},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SERPERIOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        75,
        95,
        113,
        75,
        95
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 238,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_CONTRARY},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_PRANKSTER},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_TEPIG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        63,
        45,
        45,
        45,
        45
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_FLAME_BODY},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_GUTS},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//add ground moves to learnset  check add back adaptability? drayano style

    [SPECIES_PIGNITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        93,
        55,
        55,
        70,
        55
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 146,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_RATTLED}, //hard to decide think I like rattled better as a consistent effect?
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_SAND_RUSH}, //hes kind of a slow glass canon? so guess these are fine?
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//could consider adding blaze back, flash fire lets ti sweep fire types, and is good in double batte
    //but blaze would effectively give it 3 type stab  at low hp. which would be really unique, I could buff the hp threshold for 
    //blaze stuff as well. make it less than 50%, plus it works since below 50 is when hp bar turns yellow
    //note could make fire type u turn for doubles to self proc flash fire...hmm
    //still want to give flash fire
    [SPECIES_EMBOAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        121,
        123,
        65,
        65,
        100,
        65
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 238,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_RATTLED},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_THICK_FAT, ABILITY_SAND_RUSH},// want to get triple stab so blaze may get rid of adaptability?
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //need to add ground moves to learn list for this and mid evo
    //also sandstorm for stat buff

    [SPECIES_OSHAWOTT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        55,
        45,
        45,
        63,
        45
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_INNER_FOCUS},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DEWOTT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        75,
        60,
        60,
        83,
        60
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 145,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_BATTLE_ARMOR},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SAMUROTT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        100,
        85,
        70,
        108,
        70
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 238,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_BATTLE_ARMOR},
        .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //give fighting moves

    [SPECIES_PATRAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        55,
        39,
        42,
        35,
        39
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 51,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_ANTICIPATION, ABILITY_KEEN_EYE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_CHEEK_POUCH},//cheek pouch, anticipation, inner focus is perfect, block crit and intimidate so counter part to lilipup
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_WATCHOG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        85,
        69,
        77,
        70,
        69
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 147,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_ANTICIPATION, ABILITY_ILLUMINATE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_CHEEK_POUCH}, //illuminate makes sense, hard to get rid of run away as its so good now
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_LILLIPUP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        60,
        45,
        55,
        25,
        45
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 55,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_VITAL_SPIRIT, ABILITY_PICKUP},
        .abilityHidden = {ABILITY_RUN_AWAY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_HERDIER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        80,
        65,
        60,
        35,
        65
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_HUSTLE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_STOUTLAND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        110,
        90,
        80,
        45,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 225,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_HUSTLE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_PURRLOIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        41,
        50,
        37,
        66,
        50,
        37
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIMBER, ABILITY_UNBURDEN},
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_MAGICIAN},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_LIEPARD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        64,
        98,
        50,
        116,
        98,
        50
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 90,
        .expYield = 156,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIMBER, ABILITY_BANDIT_KING},
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_MAGICIAN},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_PANSAGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        66,
        62,
        48,
        74,
        62,
        48
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 63,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_OVERGROW, ABILITY_VITAL_SPIRIT},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SIMISAGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        86,
        105,
        63,
        111,
        105,
        63
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 174,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_OVERGROW, ABILITY_SAP_SIPPER},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_PANSEAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        67,
        48,
        74,
        60,
        48
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 63,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_BLAZE, ABILITY_VITAL_SPIRIT},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SIMISEAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        116,
        63,
        111,
        101,
        63
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 174,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_BLAZE, ABILITY_FLASH_FIRE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_PANPOUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        53,
        56,
        74,
        67,
        48
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 63,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_TORRENT, ABILITY_VITAL_SPIRIT},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SIMIPOUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        98,
        79,
        111,
        117,
        63
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 174,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_NONE},
        .abilityHidden = {ABILITY_TORRENT, ABILITY_WATER_COMPACTION},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MUNNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        76,
        25,
        45,
        24,
        67,
        55
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 58,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FOREWARN, ABILITY_ANALYTIC},
            .abilityHidden = {ABILITY_TELEPATHY, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_MUSHARNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        116,
        55,
        85,
        29,
        107,
        95
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 170,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FOREWARN, ABILITY_ANALYTIC},
            .abilityHidden = {ABILITY_TELEPATHY, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_PIDOVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        36,
        40,
        43,
        56,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_HUGE_POWER, ABILITY_STALWART},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_TRANQUILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        50,
        52,
        65,
        77,
        62
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 125,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_HUGE_POWER, ABILITY_STALWART},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//seaprate final evo into gender forms
    //will need to reupdate species file again...

    [SPECIES_UNFEZANT_M] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        65,
        65,
        113,
        115,
        100
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 220,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SERENE_GRACE, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_BLITZLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        60,
        32,
        76,
        50,
        32
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 59,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_MOTOR_DRIVE},
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_ZEBSTRIKA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        100,
        63,
        116,
        80,
        63
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 174,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_MOTOR_DRIVE},
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_ROGGENROLA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        75,
        85,
        15,
        25,
        40
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Defense = 1,
        //.item1 = ITEM_EVERSTONE,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STURDY, ABILITY_WEAK_ARMOR},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BOLDORE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        105,
        105,
        20,
        50,
        55
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 120,
        .expYield = 137,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        //.item1 = ITEM_EVERSTONE,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STURDY, ABILITY_WEAK_ARMOR},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GIGALITH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        135,
        130,
        25,
        60,
        80        
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 232,
        //.evYield_Attack = 3,
        //.item1 = ITEM_EVERSTONE,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_SAND_STREAM},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_WOOBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        45,
        43,
        72,
        55,
        43
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_UNAWARE, ABILITY_SIMPLE},
            .abilityHidden = {ABILITY_SIMPLE, ABILITY_SONAR},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SWOOBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        67,
        55,
        114,
        97,
        65
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 149,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_UNAWARE, ABILITY_SIMPLE},
            .abilityHidden = {ABILITY_SIMPLE, ABILITY_SONAR},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DRILBUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        85,
        40,
        68,
        30,
        45
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 120,
        .expYield = 66,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_RUSH, ABILITY_SAND_FORCE},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_EXCADRILL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        135,
        60,
        88,
        50,
        65
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 178,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_RUSH, ABILITY_SAND_FORCE},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_AUDINO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        103,
        60,
        86,
        50,
        60,
        86
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 390,
        //.evYield_HP = 2,
        //.item1 = ITEM_ORAN_BERRY,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SERENE_GRACE, ABILITY_REGENERATOR},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_TIMBURR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        70,
        35,
        25,
        45
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_ROCK,
        .catchRate = 180,
        .expYield = 61,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_GURDURR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        105,
        95,
        40,
        40,
        60
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_ROCK,
        .catchRate = 90,
        .expYield = 142,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_CONKELDURR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        140,
        100,
        45,
        55,
        75
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 227,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GUTS, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_IRON_FIST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TYMPOLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        50,
        40,
        64,
        50,
        40
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 59,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWIFT_SWIM, ABILITY_HYDRATION},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PALPITOAD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        65,
        55,
        69,
        65,
        55
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 120,
        .expYield = 134,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWIFT_SWIM, ABILITY_HYDRATION},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SEISMITOAD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        95,
        75,
        74,
        85,
        75
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 229,
        //.evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWIFT_SWIM, ABILITY_POISON_TOUCH},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_THROH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        100,
        85,
        45,
        30,
        85
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 163,
        //.evYield_HP = 2,
        //.item2 = ITEM_BLACK_BELT,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_GUTS, ABILITY_MOLD_BREAKER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SAWK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        125,
        75,
        85,
        30,
        75
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 163,
        //.evYield_Attack = 2,
        //.item2 = ITEM_BLACK_BELT,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_STURDY, ABILITY_MOLD_BREAKER},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SEWADDLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        53,
        70,
        42,
        40,
        60
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 62,
        //.evYield_Defense = 1,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_CHLOROPHYLL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SWADLOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        74,
        63,
        90,
        42,
        50,
        80
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 133,
        //.evYield_Defense = 2,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_CHLOROPHYLL},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_GLUTTONY},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_LEAVANNY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        103,
        80,
        92,
        70,
        80
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 225,
        //.evYield_Attack = 3,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_CHLOROPHYLL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_OBLIVIOUS},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_VENIPEDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        30,
        45,
        59,
        57,
        30,
        69
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 255,
        .expYield = 52,
        //.evYield_Defense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_POISON_POINT, ABILITY_SWARM},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_QUICK_FEET},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_WHIRLIPEDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        55,
        99,
        97,
        40,
        89
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 120,
        .expYield = 126,
        //.evYield_Defense = 2,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_POISON_POINT, ABILITY_SWARM},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_QUICK_FEET},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SCOLIPEDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        100,
        89,
        117,
        55,
        69
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 218,
        //.evYield_Speed = 3,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_POISON_POINT, ABILITY_SWARM},
        .abilityHidden = {ABILITY_SPEED_BOOST, ABILITY_QUICK_FEET},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_COTTONEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        56,
        27,
        60,
        66,
        37,
        50
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 56,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_INFILTRATOR},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_WHIMSICOTT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        67,
        85,
        116,
        77,
        75
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_Speed = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_INFILTRATOR},
        .abilityHidden = {ABILITY_CHLOROPHYLL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_PETILIL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        35,
        50,
        30,
        70,
        50
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 56,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LEAF_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_LILLIGANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        89,
        60,
        75,
        90,
        110,
        75
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_ABSORB_BULB,
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_CHLOROPHYLL, ABILITY_OWN_TEMPO},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LEAF_GUARD, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_BASCULIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        92,
        65,
        108,
        80,
        55
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 25,
        .expYield = 161,
        //.evYield_Speed = 2,
        //.item2 = ITEM_DEEP_SEA_TOOTH,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RECKLESS, ABILITY_ADAPTABILITY},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_ROCK_HEAD},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SANDILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        72,
        35,
        65,
        35,
        35
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_DARK,
        .catchRate = 180,
        .expYield = 58,
        //.evYield_Attack = 1,
        //.item2 = ITEM_BLACK_GLASSES,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_MOXIE},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KROKOROK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        82,
        45,
        74,
        45,
        45
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_DARK,
        .catchRate = 90,
        .expYield = 123,
        //.evYield_Attack = 2,
        //.item2 = ITEM_BLACK_GLASSES,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_MOXIE},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KROOKODILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        117,
        80,
        92,
        65,
        70
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 234,
        //.evYield_Attack = 3,
        //.item1 = ITEM_BLACK_GLASSES,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTIMIDATE, ABILITY_MOXIE},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DARUMAKA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        90,
        45,
        60,
        15,
        45
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 120,
        .expYield = 63,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_HUSTLE, ABILITY_RATTLED},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DARMANITAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        155,
        140,
        55,
        75,
        30,
        55
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHEER_FORCE, ABILITY_IRON_FIST},
            .abilityHidden = {ABILITY_ZEN_MODE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MARACTUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        86,
        77,
        60,
        106,
        77
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 255,
        .expYield = 161,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_CHLOROPHYLL},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STORM_DRAIN, ABILITY_SOLAR_POWER},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//LEARNS ingraine can counter solar power hp drop, could also just leech seed, either works

    [SPECIES_DWEBBLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        65,
        85,
        55,
        35,
        55
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ROCK,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_Defense = 1,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CRUSTLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        84,
        105,
        125,
        45,
        65,
        75
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ROCK,
        .catchRate = 75,
        .expYield = 170,
        //.evYield_Defense = 2,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SCRAGGY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        75,
        70,
        48,
        35,
        70
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FIGHTING,
        .catchRate = 180,
        .expYield = 70,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHED_SKIN, ABILITY_MOXIE},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SCRAFTY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        90,
        115,
        58,
        45,
        115
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FIGHTING,
        .catchRate = 90,
        .expYield = 171,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHED_SKIN, ABILITY_MOXIE},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SIGILYPH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        58,
        80,
        97,
        103,
        80
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WONDER_SKIN, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_TINTED_LENS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_YAMASK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        30,
        85,
        30,
        55,
        65
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Defense = 1,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MUMMY, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_COFAGRIGUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        50,
        145,
        30,
        95,
        105
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 169,
        //.evYield_Defense = 2,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MUMMY, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TIRTOUGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        78,
        103,
        22,
        53,
        45
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOLID_ROCK, ABILITY_STURDY},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CARRACOSTA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        74,
        108,
        133,
        32,
        83,
        65
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOLID_ROCK, ABILITY_STURDY},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCHEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        112,
        45,
        70,
        74,
        45
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 71,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DEFEATIST, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ARCHEOPS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        140,
        65,
        110,
        112,
        65
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DEFEATIST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TRUBBISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        50,
        62,
        65,
        40,
        76
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_Speed = 1,
        //.item2 = ITEM_SILK_SCARF,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STENCH, ABILITY_AFTERMATH},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STICKY_HOLD, ABILITY_POISON_TOUCH},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //ADD steel moves to garbodor

    [SPECIES_GARBODOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        95,
        82,
        75,
        75,
        102
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 166,
        //.evYield_Attack = 2,
        //.item1 = ITEM_SILK_SCARF,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_BLACK_SLUDGE,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STENCH, ABILITY_AFTERMATH},
            .abilityHidden = {ABILITY_STICKY_HOLD, ABILITY_CORROSION},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ZORUA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        65,
        40,
        65,
        80,
        40
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 75,
        .expYield = 66,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ILLUSION, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_ZOROARK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        105,
        60,
        105,
        120,
        60
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 179,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ILLUSION, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MINCCINO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        50,
        40,
        75,
        40,
        40
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_SKILL_LINK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_CINCCINO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        95,
        60,
        115,
        65,
        60
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 60,
        .expYield = 165,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CUTE_CHARM, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_SKILL_LINK, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_GOTHITA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        30,
        50,
        45,
        55,
        65
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 200,
        .expYield = 58,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FOREWARN, ABILITY_SHADOW_TAG},
        .abilityHidden = {ABILITY_DARK_DEAL, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GOTHORITA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        45,
        70,
        55,
        75,
        85
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 100,
        .expYield = 137,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FOREWARN, ABILITY_SHADOW_TAG},
        .abilityHidden = {ABILITY_DARK_DEAL, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GOTHITELLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        55,
        95,
        65,
        95,
        110
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 50,
        .expYield = 221,
        //.evYield_SpDefense = 3,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FOREWARN, ABILITY_SHADOW_TAG},
        .abilityHidden = {ABILITY_DARK_DEAL, ABILITY_MAGIC_BOUNCE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SOLOSIS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        30,
        40,
        20,
        105,
        50
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 200,
        .expYield = 58,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OVERCOAT, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DUOSION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        40,
        50,
        30,
        125,
        60
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 100,
        .expYield = 130,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OVERCOAT, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_REUNICLUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        65,
        85,
        30,
        125,
        85
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 50,
        .expYield = 221,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OVERCOAT, ABILITY_MAGIC_GUARD},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DUCKLETT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        44,
        50,
        55,
        44,
        50
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_BIG_PECKS},
            .abilityHidden = {ABILITY_HYDRATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SWANNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        97,
        63,
        98,
        97,
        63
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYDRATION, ABILITY_BIG_PECKS},
            .abilityHidden = {ABILITY_GALE_WINGS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_VANILLITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        36,
        50,
        50,
        44,
        65,
        60
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 255,
        .expYield = 61,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ICE_BODY, ABILITY_SNOW_CLOAK},
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_VANILLISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        51,
        65,
        65,
        59,
        80,
        75
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 120,
        .expYield = 138,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ICE_BODY, ABILITY_SNOW_CLOAK},
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_VANILLUXE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        95,
        85,
        79,
        110,
        95
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 241,
        //.evYield_SpAttack = 3,
        //.item1 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ICE_BODY, ABILITY_SNOW_WARNING},
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DEERLING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        60,
        50,
        75,
        40,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_SAWSBUCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        99,
        100,
        70,
        95,
        60,
        70
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_EMOLGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        85,
        60,
        103,
        85,
        60
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 200,
        .expYield = 150,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_OVERCHARGE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_KARRABLAST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        75,
        45,
        60,
        40,
        45
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 200,
        .expYield = 63,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_SHED_SKIN},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NO_GUARD, ABILITY_OVERCOAT},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ESCAVALIER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        135,
        105,
        60,
        60,
        105
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 75,
        .expYield = 173,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NO_GUARD, ABILITY_NO_GUARD},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_FOONGUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        69,
        55,
        45,
        35,
        55,
        70
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 190,
        .expYield = 59,
        //.evYield_HP = 1,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_EFFECT_SPORE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_AMOONGUSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        114,
        85,
        70,
        50,
        85,
        95
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 162,
        //.evYield_HP = 2,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_EFFECT_SPORE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FRILLISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        40,
        50,
        40,
        65,
        85
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GHOST,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_ABSORB, ABILITY_CURSED_BODY},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    }, //water with tentacruel

    [SPECIES_JELLICENT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        60,
        70,
        60,
        85,
        105
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GHOST,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_ABSORB, ABILITY_CURSED_BODY},
        .abilityHidden = {ABILITY_DAMP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ALOMOMOLA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        165,
        75,
        80,
        65,
        40,
        45
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_JOLTIK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        47,
        50,
        85,
        57,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 64,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COMPOUND_EYES, ABILITY_ANTICIPATION},
        .abilityHidden = {ABILITY_SWARM, ABILITY_UNNERVE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_GALVANTULA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        87,
        60,
        112,
        97,
        60
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COMPOUND_EYES, ABILITY_ANTICIPATION},
        .abilityHidden = {ABILITY_SWARM, ABILITY_UNNERVE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_FERROSEED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        50,
        91,
        10,
        24,
        86
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 61,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_STICKY_BARB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_BARBS, ABILITY_TOUGH_SPINES},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_FERROTHORN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        94,
        131,
        20,
        54,
        116
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 171,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_STICKY_BARB,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_BARBS, ABILITY_TOUGH_SPINES},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KLINK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        55,
        70,
        30,
        45,
        60
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 130,
        .expYield = 60,
        //.evYield_Defense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MOTOR_DRIVE, ABILITY_MINUS},
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_MOLD_BREAKER},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KLANG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        80,
        95,
        50,
        70,
        85
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 60,
        .expYield = 154,
        //.evYield_Defense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MOTOR_DRIVE, ABILITY_MINUS},
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_MOLD_BREAKER},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KLINKLANG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        115,
        90,
        70,
        85
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 30,
        .expYield = 234,
        //.evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_MOTOR_DRIVE, ABILITY_MINUS},
        .abilityHidden = {ABILITY_CLEAR_BODY, ABILITY_MOLD_BREAKER},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_TYNAMO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        55,
        40,
        60,
        45,
        40
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 55,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_LIGHT_METAL},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    }, //why is it not water?

    [SPECIES_EELEKTRIK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        85,
        70,
        50,
        75,
        70
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 60,
        .expYield = 142,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_STRONG_JAW, ABILITY_GALVANIZE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //LOWER EVolution and learnsets

    [SPECIES_EELEKTROSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        115,
        80,
        56,
        105,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 30,
        .expYield = 232,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_STRONG_JAW, ABILITY_GALVANIZE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },//copy learnset of pre evo

    [SPECIES_ELGYEM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        55,
        55,
        30,
        85,
        55
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 67,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TELEPATHY, ABILITY_EMPATH},
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_LIQUID_VOICE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //add round to learnset early on

    [SPECIES_BEHEEYEM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        75,
        75,
        40,
        125,
        95
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 170,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TELEPATHY, ABILITY_EMPATH},
            .abilityHidden = {ABILITY_ANALYTIC, ABILITY_LIQUID_VOICE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_LITWICK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        30,
        55,
        20,
        65,
        55
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FIRE,
        .catchRate = 190,
        .expYield = 55,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_INFILTRATOR, ABILITY_FLASH_FIRE},
            //#ifdef BATTLE_ENGINE
                .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_CURSED_BODY},
            // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_LAMPENT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        40,
        60,
        55,
        95,
        60
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FIRE,
        .catchRate = 90,
        .expYield = 130,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_INFILTRATOR, ABILITY_FLASH_FIRE},
            //#ifdef BATTLE_ENGINE
                .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_CURSED_BODY},
            // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_CHANDELURE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        55,
        90,
        80,
        145,
        90
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 234,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_INFILTRATOR, ABILITY_FLASH_FIRE},
            //#ifdef BATTLE_ENGINE
                .abilityHidden = {ABILITY_SHADOW_TAG, ABILITY_CURSED_BODY},
            // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_AXEW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        46,
        87,
        60,
        57,
        30,
        40
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 75,
        .expYield = 64,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_ARENA_TRAP},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_FRAXURE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        66,
        117,
        70,
        67,
        40,
        50
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 60,
        .expYield = 144,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_ARENA_TRAP},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_HAXORUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        76,
        147,
        90,
        97,
        60,
        70
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 243,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_BATTLE_ARMOR},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CUBCHOO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        70,
        40,
        40,
        60,
        60
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ICE,
        .catchRate = 120,
        .expYield = 61,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_SLUSH_RUSH},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_GOOEY},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_BEARTIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        130,
        85,
        50,
        70,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 177,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_SLUSH_RUSH},
        .abilityHidden = {ABILITY_RATTLED, ABILITY_STAMINA},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_CRYOGONAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80, 
        50,
        50,
        105,
        95,
        135
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 25,
        .expYield = 180,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_ICE_BODY, ABILITY_SNOW_WARNING},
        .abilityHidden = {ABILITY_ICE_SCALES, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SHELMET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        40,
        85,
        25,
        40,
        65
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 200,
        .expYield = 61,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYDRATION, ABILITY_SHELL_ARMOR},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ACCELGOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        70,
        40,
        145,
        120,
        60
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 75,
        .expYield = 173,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYDRATION, ABILITY_STICKY_HOLD},
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_STUNFISK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        109,
        66,
        84,
        32,
        81,
        99
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_HP = 2,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_STATIC, ABILITY_SAND_RUSH},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MIENFOO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        85,
        50,
        65,
        55,
        50
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 180,
        .expYield = 70,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RECKLESS, ABILITY_REGENERATOR},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_JUSTIFIED},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MIENSHAO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        125,
        60,
        105,
        95,
        60
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 179,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RECKLESS, ABILITY_REGENERATOR},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_JUSTIFIED},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_DRUDDIGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        120,
        90,
        48,
        60,
        90
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 170,
        //.evYield_Attack = 2,
        //.item2 = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ROUGH_SKIN, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_ROCK_HEAD},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_GOLETT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        59,
        74,
        50,
        35,
        35,
        50
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GHOST,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LIGHT_CLAY,
        // #endif
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_FIST, ABILITY_NO_GUARD},
            .abilityHidden = {ABILITY_STURDY, ABILITY_JUSTIFIED},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //victory road

    [SPECIES_GOLURK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        99,
        124,
        80,
        55,
        55,
        80
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GHOST,
        .catchRate = 90,
        .expYield = 169,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_LIGHT_CLAY,
        // #endif
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_FIST, ABILITY_NO_GUARD},
            .abilityHidden = {ABILITY_STURDY, ABILITY_JUSTIFIED},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_PAWNIARD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        85,
        70,
        60,
        40,
        40
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_STEEL,
        .catchRate = 120,
        .expYield = 68,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_DEFIANT, ABILITY_INNER_FOCUS},
        .abilityHidden = {ABILITY_PRESSURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BISHARP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        125,
        100,
        70,
        60,
        70
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_DEFIANT, ABILITY_INNER_FOCUS},
        .abilityHidden = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//GIVE Hi pressure ability

    [SPECIES_BOUFFALANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        110,
        95,
        55,
        40,
        95
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_RECKLESS, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SOUNDPROOF, ABILITY_STAMINA},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_RUFFLET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        83,
        50,
        60,
        37,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 70,
        //.evYield_Attack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_SHEER_FORCE},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_BRAVIARY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        123,
        75,
        80,
        57,
        75
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 60,
        .expYield = 179,
        //.evYield_Attack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_SHEER_FORCE},
        .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_VULLABY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        55,
        75,
        60,
        45,
        65
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 190,
        .expYield = 74,
        //.evYield_Defense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BIG_PECKS, ABILITY_OVERCOAT},
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_RATTLED},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MANDIBUZZ] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        65,
        105,
        80,
        55,
        95
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 60,
        .expYield = 179,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BIG_PECKS, ABILITY_OVERCOAT},
            .abilityHidden = {ABILITY_WEAK_ARMOR, ABILITY_RATTLED},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = TRUE,
    },

    [SPECIES_HEATMOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        97,
        66,
        65,
        105,
        66
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 90,
        .expYield = 169,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_FLASH_FIRE},
        .abilityHidden = {ABILITY_WHITE_SMOKE, ABILITY_MOODY},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DURANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        109,
        112,
        109,
        48,
        48
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 169,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_HEATPROOF, ABILITY_NONE},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//GAVE HEATPROOF cuz apparently steel armor was to protect against main predator a fire type, buffing heatproof to be /4 damage since this is 4x weak
    //and just being neutral for mon with normal weakness isn't exactly "heat proof"

    [SPECIES_DEINO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        52,
        65,
        50,
        38,
        45,
        50
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_HUSTLE, ABILITY_RIVALRY},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZWEILOUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        85,
        70,
        58,
        65,
        70
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_HUSTLE, ABILITY_RIVALRY},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_HYDREIGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        105,
        90,
        98,
        125,
        90
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_HUSTLE, ABILITY_RIVALRY},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LARVESTA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        85,
        55,
        80,
        50,
        55
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 72,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_ANTICIPATION},
        .abilityHidden = {ABILITY_SWARM, ABILITY_FLASH_FIRE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_VOLCARONA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        99,
        65,
        110,
        135,
        105
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIRE,
        .catchRate = 15,
        .expYield = 248,
        //.evYield_SpAttack = 3,
        //.item1 = ITEM_SILVER_POWDER,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SUN_DISK, ABILITY_BLAZE},
        .abilityHidden = {ABILITY_SWARM, ABILITY_FLASH_FIRE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_COBALION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        91,
        90,
        129,
        108,
        90,
        72
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_JUSTIFIED, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_TERRAKION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        91,
        129,
        90,
        108,
        72,
        90
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_JUSTIFIED, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_VIRIZION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        91,
        90,
        72,
        108,
        90,
        129
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_JUSTIFIED, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_TORNADUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        115,
        70,
        111,
        125,
        80
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_NONE},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_THUNDURUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        115,
        70,
        111,
        125,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_NONE},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_RESHIRAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        120,
        100,
        90,
        150,
        120
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FIRE,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TURBOBLAZE, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ZEKROM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        150,
        120,
        90,
        120,
        100
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TERAVOLT, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_LANDORUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        89,
        125,
        90,
        101,
        115,
        80
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KYUREM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        125,
        130,
        90,
        95,
        130,
        90
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 297,
        //.evYield_HP = 1,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_ABSOLUTE_ZERO, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//absolute zero, turns all water type attacks into ice type attacks field wide, think also change type effect like ecosystem eto resist ice - DONE

    [SPECIES_KELDEO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        91,
        72,
        90,
        108,
        129,
        90
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_JUSTIFIED, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MELOETTA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        77,
        77,
        90,
        128,
        128
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        //.evYield_SpDefense = 1,
        //.item1 = ITEM_STAR_PIECE,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_MAGIC_GUARD},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GENESECT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        120,
        95,
        99,
        120,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_DOWNLOAD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CHESPIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        66,
        61,
        65,
        38,
        48,
        45
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 63,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_OVERGROW, ABILITY_OVERGROW},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_TOUGH_SPINES},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //making grass normal since has varied move pool, lil chespin love

    [SPECIES_QUILLADIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        78,
        95,
        57,
        56,
        58
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STURDY, ABILITY_ROCK_HEAD},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_TOUGH_SPINES},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//has takedown wood hammer so rock head could be useful plus has enough stats for eviolite to be worthwhile

    [SPECIES_CHESNAUGHT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        98,
        107,
        127,
        64,
        74,
        75
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_STURDY, ABILITY_SHELL_ARMOR},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_TOUGH_SPINES},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//change signature move spike shield to apply field spikes as well as normal effect
    //also re arrange move learn order pain split belly drum possibly ingrain
    //think what I'll do is split it into 2 effects, it'll scatter spikes when it gets hit

    [SPECIES_FENNEKIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        45,
        40,
        60,
        62,
        60
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 61,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BRAIXEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        59,
        59,
        58,
        73,
        90,
        70
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 143,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DELPHOX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        69,
        72,
        104,
        114,
        100
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 240,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_MAGICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_FROAKIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        41,
        56,
        40,
        71,
        62,
        44
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 63,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_FROGADIER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        63,
        52,
        97,
        83,
        56
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 142,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GRENINJA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        95,
        67,
        122,
        103,
        71
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROTEAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BUNNELBY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        36,
        38,
        57,
        32,
        36
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 47,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_CHEEK_POUCH},
        .abilityHidden = {ABILITY_HUGE_POWER, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DIGGERSBY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        56,
        77,
        78,
        50,
        77
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 127,
        .expYield = 148,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_CHEEK_POUCH},
        .abilityHidden = {ABILITY_HUGE_POWER, ABILITY_MULTI_TASK},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_FLETCHLING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        50,
        43,
        62,
        40,
        38
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BIG_PECKS, ABILITY_NONE},
            .abilityHidden = {ABILITY_GALE_WINGS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_FLETCHINDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        73,
        55,
        84,
        56,
        52
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 134,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GALE_WINGS, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TALONFLAME] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        81,
        71,
        126,
        74,
        69
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_FLAME_BODY, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GALE_WINGS, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SCATTERBUG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        35,
        40,
        35,
        27,
        25
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 40,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SPEWPA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        22,
        60,
        29,
        27,
        30
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 75,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHED_SKIN, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        54,
        66,
        99,
        95,
        66
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_LITLEO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        50,
        58,
        72,
        73,
        54
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 220,
        .expYield = 74,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_TIGER_CUB},//ABILITY_TIGER_CUB
            .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PYROAR_M] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        106,
        78,
        87,
        106,
        109,
        66
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 65,
        .expYield = 177,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_FLAME_BODY},
            .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//add sunny day crunch extremespeed to learnet and have thunderbolt as tm move    vsonic
    
    [SPECIES_FLABEBE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        39,
        42,
        61,
        79
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        45,
        47,
        52,
        75,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLORGES] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        65,
        68,
        75,
        112,
        154
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SKIDDO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        66,
        65,
        48,
        52,
        62,
        57
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 200,
        .expYield = 70,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_NONE},
            .abilityHidden = {ABILITY_GRASS_PELT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOGOAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        123,
        100,
        62,
        68,
        97,
        81
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 186,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_NONE},
            .abilityHidden = {ABILITY_GRASS_PELT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PANCHAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        67,
        82,
        62,
        43,
        46,
        48
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 220,
        .expYield = 70,
        //.evYield_Attack = 1,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_FIST, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_PANGORO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        124,
        78,
        58,
        69,
        71
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_DARK,
        .catchRate = 65,
        .expYield = 173,
        //.evYield_Attack = 2,
        //.item2 = ITEM_MENTAL_HERB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_FIST, ABILITY_MOLD_BREAKER},
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ESPURR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        48,
        54,
        68,
        63,
        60
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 71,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_INFILTRATOR},
        .abilityHidden = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MEOWSTIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        74,
        48,
        76,
        104,
        83,
        81
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 163,
        //.evYield_Speed = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_PRANKSTER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_HONEDGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        80,
        100,
        28,
        35,
        37
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GHOST,
        .catchRate = 180,
        .expYield = 65,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
            .abilities = {ABILITY_NO_GUARD, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DOUBLADE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        59,
        110,
        150,
        35,
        45,
        49
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GHOST,
        .catchRate = 90,
        .expYield = 157,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_NO_GUARD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_AEGISLASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        50,
        150,
        60,
        50,
        150
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 234,
        //.evYield_Defense = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STANCE_CHANGE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SPRITZEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        52,
        60,
        23,
        63,
        65
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 200,
        .expYield = 68,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_HEALER, ABILITY_NONE},
        .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_AROMATISSE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        101,
        72,
        72,
        29,
        99,
        89
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 140,
        .expYield = 162,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_SWIRLIX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        48,
        66,
        49,
        59,
        57
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 200,
        .expYield = 68,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SLURPUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        82,
        80,
        86,
        72,
        85,
        75
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 140,
        .expYield = 168,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_UNBURDEN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_INKAY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        53,
        54,
        53,
        45,
        37,
        46
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 58,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CONTRARY, ABILITY_SUCTION_CUPS},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MALAMAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        86,
        92,
        88,
        73,
        68,
        75
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 80,
        .expYield = 169,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CONTRARY, ABILITY_SUCTION_CUPS},
            .abilityHidden = {ABILITY_INFILTRATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BINACLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        42,
        52,
        67,
        50,
        39,
        56
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 120,
        .expYield = 61,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_SNIPER},
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BARBARACLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        105,
        115,
        68,
        54,
        86
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_SNIPER},
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SKRELP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        60,
        60,
        30,
        60,
        60
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_WATER,
        .catchRate = 225,
        .expYield = 64,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_POISON_TOUCH},
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DRAGALGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        75,
        90,
        44,
        97,
        123
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 55,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_POISON_TOUCH},
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_CLAUNCHER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        53,
        62,
        44,
        58,
        63
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 225,
        .expYield = 66,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
            .abilities = {ABILITY_MEGA_LAUNCHER, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //normal because highly varied learnset,  and I just need more normal types, lol nvm I'm good on normal types

    [SPECIES_CLAWITZER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        73,
        88,
        59,
        120,
        89
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_NORMAL,
        .catchRate = 55,
        .expYield = 100,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MEGA_LAUNCHER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_HELIOPTILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        33,
        70,
        61,
        43
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 58,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DRY_SKIN, ABILITY_SAND_VEIL},
            .abilityHidden = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_HELIOLISK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        55,
        52,
        109,
        109,
        94
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_NORMAL,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DRY_SKIN, ABILITY_SAND_VEIL},
            .abilityHidden = {ABILITY_SOLAR_POWER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TYRUNT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        89,
        77,
        48,
        45,
        45
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 72,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_ROCK_HEAD},
        .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TYRANTRUM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        82,
        121,
        119,
        71,
        69,
        59
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_ROCK_HEAD},
        .abilityHidden = {ABILITY_STURDY, ABILITY_SHEER_FORCE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_AMAURA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        59,
        50,
        46,
        67,
        63
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 72,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_REFRIGERATE, ABILITY_NONE},
            .abilityHidden = {ABILITY_SNOW_WARNING, ABILITY_SOLID_ROCK},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_AURORUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        123,
        77,
        72,
        58,
        99,
        92
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 104,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_REFRIGERATE, ABILITY_NONE},
            .abilityHidden = {ABILITY_SNOW_WARNING, ABILITY_SOLID_ROCK},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SYLVEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        65,
        65,
        60,
        110,
        130
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 184,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_CUTE_CHARM, ABILITY_CUTE_CHARM},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PIXILATE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_HAWLUCHA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        92,
        75,
        118,
        74,
        63
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FLYING,
        .catchRate = 100,
        .expYield = 175,
        //.evYield_Attack = 2,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        //#if P_UPDATED_EGG_GROUPS >= GEN_8
            .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIMBER, ABILITY_UNBURDEN},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DEDENNE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        67,
        58,
        57,
        101,
        81,
        67
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 180,
        .expYield = 151,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHEEK_POUCH, ABILITY_PICKUP},
        .abilityHidden = {ABILITY_PLUS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CARBINK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        50,
        150,
        50,
        50,
        150
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FAIRY,
        .catchRate = 60,
        .expYield = 100,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_NONE},
        .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_GOOMY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        50,
        35,
        40,
        55,
        75
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_SpDefense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_GOOEY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SLIGGOO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        75,
        53,
        60,
        83,
        113
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 158,
        //.evYield_SpDefense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_SHED_SHELL,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_GOOEY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GOODRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        100,
        70,
        80,
        110,
        150
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_SpDefense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_HYDRATION},
            .abilityHidden = {ABILITY_GOOEY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_KLEFKI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        57,
        80,
        91,
        75,
        80,
        87
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_NONE},
            .abilityHidden = {ABILITY_MAGICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_PHANTUMP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        70,
        48,
        38,
        50,
        60
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 62,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_NATURAL_CURE, ABILITY_FRISK},
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TREVENANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        110,
        76,
        56,
        65,
        82
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 60,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_NATURAL_CURE, ABILITY_FRISK},
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PUMPKABOO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        64,
        66,
        70,
        51,
        44,
        55
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 67,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOURGEIST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        90,
        122,
        84,
        58,
        75
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 60,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BERGMITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        69,
        85,
        28,
        32,
        35
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
       // #ifdef BATTLE_ENGINE
            .eggGroup2 = EGG_GROUP_MINERAL,
        // #endif
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OWN_TEMPO, ABILITY_ICE_BODY},
        .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_AVALUGG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        117,
        184,
        28,
        44,
        46
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 55,
        .expYield = 180,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_OWN_TEMPO, ABILITY_ICE_BODY},
        .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NOIBAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        30,
        35,
        55,
        45,
        40
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_DRAGON,
        .catchRate = 190,
        .expYield = 49,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
            .eggGroup2 = EGG_GROUP_DRAGON,
            .abilities = {ABILITY_FRISK, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_SONAR}, //not psychic makes no sense to have telepathy, its a sound based mon
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_NOIVERN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        70,
        80,
        123,
        97,
        80
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 187,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
            .eggGroup2 = EGG_GROUP_DRAGON,
            .abilities = {ABILITY_FRISK, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_SONAR},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_XERNEAS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        126,
        131,
        95,
        99,
        131,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FAIRY_AURA, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_YVELTAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        126,
        131,
        95,
        99,
        131,
        98
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DARK_AURA, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ZYGARDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        108,
        100,
        121,
        95,
        81,
        95
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AURA_BREAK, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DIANCIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        100,
        150,
        50,
        100,
        150
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_CLEAR_BODY, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_HOOPA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        110,
        60,
        70,
        150,
        130
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_GHOST,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGICIAN, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_VOLCANION] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        110,
        120,
        70,
        130,
        90
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_WATER,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_WATER_ABSORB, ABILITY_NONE},
        .abilityHidden = {ABILITY_STEAM_ENGINE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ROWLET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        55,
        55,
        42,
        50,
        50
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_OVERGROW, ABILITY_OVERGROW},
        .abilityHidden = {ABILITY_LONG_REACH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DARTRIX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        75,
        75,
        52,
        70,
        70
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_OVERGROW, ABILITY_OVERGROW},
        .abilityHidden = {ABILITY_LONG_REACH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DECIDUEYE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        107,
        75,
        70,
        100,
        100
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        .abilities = {ABILITY_OVERGROW, ABILITY_OVERGROW},
        .abilityHidden = {ABILITY_LONG_REACH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_LITTEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        65,
        40,
        70,
        60,
        40
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TORRACAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        85,
        50,
        90,
        80,
        50
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_INCINEROAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        115,
        90,
        60,
        80,
        90
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_POPPLIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        54,
        54,
        40,
        66,
        56
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 64,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIQUID_VOICE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BRIONNE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        69,
        69,
        50,
        91,
        81
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIQUID_VOICE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PRIMARINA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        74,
        74,
        60,
        126,
        116
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIQUID_VOICE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_PIKIPEK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        30,
        65,
        30,
        30
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_Attack = 1,
        //.item2 = ITEM_ORAN_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SKILL_LINK},
        .abilityHidden = {ABILITY_PICKUP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_TRUMBEAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        85,
        50,
        75,
        40,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 124,
        //.evYield_Attack = 2,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SKILL_LINK},
        .abilityHidden = {ABILITY_PICKUP, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_TOUCANNON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        120,
        75,
        60,
        75,
        75
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 218,
        //.evYield_Attack = 3,
        //.item2 = ITEM_RAWST_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SKILL_LINK},
            .abilityHidden = {ABILITY_SHEER_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_YUNGOOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        70,
        30,
        45,
        30,
        30
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 51,
        //.evYield_Attack = 1,
        //.item2 = ITEM_PECHA_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STAKEOUT, ABILITY_STRONG_JAW},
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_STALL},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GUMSHOOS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        110,
        60,
        45,
        55,
        60
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 127,
        .expYield = 146,
        //.evYield_Attack = 2,
        //.item2 = ITEM_PECHA_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STAKEOUT, ABILITY_STRONG_JAW},
            .abilityHidden = {ABILITY_ADAPTABILITY, ABILITY_STALL},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },//give first impressions as evo move & facade

    [SPECIES_GRUBBIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        47,
        62,
        55,
        46,
        55,
        55
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_ANTICIPATION},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_CHARJABUG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        67,
        82,
        95,
        36,
        55,
        83
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 120,
        .expYield = 140,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_CELL_BATTERY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTERY, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VIKAVOLT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        70,
        90,
        100,
        145,
        75
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 225,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_GALVANIZE, ABILITY_MOTOR_DRIVE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CRABRAWLER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        47,
        82,
        57,
        63,
        42,
        47
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 225,
        .expYield = 68,
        //.evYield_Attack = 1,
        //.item2 = ITEM_ASPEAR_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYPER_CUTTER, ABILITY_IRON_FIST},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_REGENERATOR}, //regernnerator here is like a prize fighter taking a rest between rounds
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_CRABOMINABLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        132,
        117,
        43,
        62,
        67
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 167,
        //.evYield_Attack = 2,
        //.item2 = ITEM_CHERI_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_3,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HYPER_CUTTER, ABILITY_IRON_FIST},
            .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_WETIKO},    //thought to remove something to keep regeneraor & refrigerate but type still not good to switch with
        .bodyColor = BODY_COLOR_WHITE, //want regenrator for healing monster lore, but refrigerate gets ice stab return, dizzy punch & giga impact, too good to give up
        .noFlip = FALSE,
    },//make new fighting move to take advantage of regenerator "cheap shot" idea is a hit after bell, will be low priority u-turn like
    //The user throws delayed punch when the foe doesn't expect it then retreats
    //THINK USE astonish "!" on user  then do something like mega punch
    //...just gonna make new ability for it that is combination of regrigerate and regenerator aka "Wetiko"
    //which is algonuin for wendigo i.e original word

    [SPECIES_ORICORIO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        70,
        70,
        93,
        98,
        70
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DANCER, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CUTIEFLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        45,
        40,
        84,
        55,
        40
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HONEY_GATHER, ABILITY_SHIELD_DUST},
            .abilityHidden = {ABILITY_SWEET_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_RIBOMBEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        55,
        60,
        124,
        95,
        70
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 162,
        //.evYield_Speed = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HONEY_GATHER, ABILITY_SHIELD_DUST},
            .abilityHidden = {ABILITY_SWEET_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ROCKRUFF] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        65,
        40,
        60,
        30,
        40
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ROCK,
        .catchRate = 190,
        .expYield = 56,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_KEEN_EYE, ABILITY_VITAL_SPIRIT},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STEADFAST, ABILITY_OWN_TEMPO}, //base game needs own tempo to evolve into dusk form, gave owntempo to work, so could just use ability patch
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //give these normal secondary

    [SPECIES_LYCANROC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        115,
        65,
        112,
        55,
        65
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ROCK,
        .catchRate = 90,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SAND_RUSH},
            .abilityHidden = {ABILITY_STEADFAST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    }, //give crush claw

    [SPECIES_WISHIWASHI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        20,
        20,
        40,
        25,
        25
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 61,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SCHOOLING, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MAREANIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        53,
        62,
        45,
        43,
        62
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Defense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MERCILESS, ABILITY_LIMBER},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_TOXAPEX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        63,
        152,
        35,
        53,
        142
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_WATER,
        .catchRate = 75,
        .expYield = 173,
        //.evYield_Defense = 2,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MERCILESS, ABILITY_LIMBER},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MUDBRAY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        100,
        70,
        45,
        45,
        55
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 190,
        .expYield = 77,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_LIGHT_CLAY, Vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OWN_TEMPO, ABILITY_STAMINA},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_LETHAL_LEGS},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MUDSDALE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        125,
        100,
        35,
        55,
        85
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
            ////.item2 = ITEM_LIGHT_CLAY,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OWN_TEMPO, ABILITY_STAMINA},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_LETHAL_LEGS},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_DEWPIDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        50,
        52,
        27,
        55,
        72
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_BUG,
        .catchRate = 200,
        .expYield = 54,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_BUBBLE, ABILITY_NONE},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARAQUANID] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        69,
        86,
        92,
        72,
        80,
        132
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_BUG,
        .catchRate = 100,
        .expYield = 159,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_BUBBLE, ABILITY_NONE},
        .abilityHidden = {ABILITY_WATER_ABSORB, ABILITY_DAMP},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_FOMANTIS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        76,
        55,
        35,
        35,
        50,
        35
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 50,
        //.evYield_Attack = 1,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_NONE},
            .abilityHidden = {ABILITY_CONTRARY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_LURANTIS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        105,
        90,
        45,
        80,
        90
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 168,
        //.evYield_Attack = 2,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_NONE},
            .abilityHidden = {ABILITY_CONTRARY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_MORELULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        35,
        55,
        15,
        65,
        75
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 57,
        //.evYield_SpDefense = 1,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_ILLUMINATE, ABILITY_EFFECT_SPORE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SHIINOTIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        45,
        100,
        30,
        90,
        100
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GHOST,
        .catchRate = 75,
        .expYield = 142,
        //.evYield_SpDefense = 2,
        //.item1 = ITEM_TINY_MUSHROOM,
        //.item2 = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_TOADSTOOL_NYMPH, ABILITY_EFFECT_SPORE},
        .abilityHidden = {ABILITY_RAIN_DISH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SALANDIT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        44,
        40,
        77,
        71,
        57
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FIRE,
        .catchRate = 120,
        .expYield = 64,
        //.evYield_Speed = 1,
        //.item2 = ITEM_SMOKE_BALL,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CORROSION, ABILITY_NONE},
        .abilityHidden = {ABILITY_OBLIVIOUS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SALAZZLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        64,
        60,
        117,
        111,
        77
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 168,
        //.evYield_Speed = 2,
        //.item2 = ITEM_SMOKE_BALL,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CORROSION, ABILITY_MERCILESS},
        .abilityHidden = {ABILITY_OBLIVIOUS, ABILITY_QUEENLY_MAJESTY}, //oblivious is hidden ability as it can't be infatuated as its a seductress itself, new idea make femme fatale to replace
        .bodyColor = BODY_COLOR_BLACK, //give base oblivious affect and roll in gen 9 buff immunity to taunt and maybe flinch?  replace levitate
        .noFlip = FALSE, //Femme fatale ABILITY_FEMME_FATALE    //so cant be flinched or taunted
    },//vsonic

    [SPECIES_STUFFUL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        75,
        50,
        50,
        45,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 140,
        .expYield = 68,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUFFY, ABILITY_KLUTZ},
        .abilityHidden = {ABILITY_CUTE_CHARM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_BEWEAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        125,
        80,
        60,
        55,
        60
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 70,
        .expYield = 175,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUFFY, ABILITY_KLUTZ},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_BOUNSWEET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        52,
        30,
        38,
        32,
        30,
        38
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 235,
        .expYield = 42,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_GRASSY_SEED,  VSONIC
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_OBLIVIOUS},
            .abilityHidden = {ABILITY_SWEET_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_STEENEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        40,
        48,
        62,
        40,
        48
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 102,
        //.evYield_Speed = 2,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_GRASSY_SEED,  VSONIC
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_OBLIVIOUS},
            .abilityHidden = {ABILITY_SWEET_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_TSAREENA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        87,
        120,
        98,
        72,
        50,
        98
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 230,
        //.evYield_Attack = 3,
       // #ifdef ITEM_EXPANSION
            ////.item1 = ITEM_GRASSY_SEED,  VSONIC
        // #endif
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_QUEENLY_MAJESTY},
            .abilityHidden = {ABILITY_SWEET_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_COMFEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        51,
        52,
        90,
        100,
        82,
        110
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 60,
        .expYield = 170,
        //.evYield_SpDefense = 2,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_MISTY_SEED, VSONIC
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_TRIAGE},
        .abilityHidden = {ABILITY_NATURAL_CURE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ORANGURU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        75,
        80,
        60,
        90,
        110
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TELEPATHY, ABILITY_FOREWARN},  //removd inner focus, prevents intimidate but its a special attacker
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_INNER_FOCUS}, //ok I like gorilla tactics but it just doesn't mesh with the theme of the mon. its too violent
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_PASSIMIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        120,
        90,
        80,
        40,
        60
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RECEIVER, ABILITY_NONE},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_WIMPOD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        25,
        35,
        40,
        99,
        20,
        30
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_WATER,
        .catchRate = 90,
        .expYield = 46,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WIMP_OUT, ABILITY_WIMP_OUT},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    }, //give uturn, the turn one flinch move, and good deal of status moves to keep enemy away something hazards or something

    [SPECIES_GOLISOPOD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        115,
        125,
        140,
        55,
        60,
        90
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 186,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_EMERGENCY_EXIT, ABILITY_HI_PRESSURE},
            .abilityHidden = {ABILITY_TOUGH_CLAWS, ABILITY_ANTICIPATION},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SANDYGAST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        55,
        80,
        15,
        70,
        45
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GROUND,
        .catchRate = 140,
        .expYield = 64,
        //.evYield_Defense = 1,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_COMPACTION, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PALOSSAND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        75,
        110,
        35,
        100,
        75
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GROUND,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_Defense = 2,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_COMPACTION, ABILITY_NONE},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PYUKUMUKU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        60,
        130,
        5,
        30,
        130
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 144,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INNARDS_OUT, ABILITY_NONE},
            .abilityHidden = {ABILITY_UNAWARE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,  //give trick room   VSONIC
        .noFlip = FALSE,
    },

    [SPECIES_TYPE_NULL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        59,
        95,
        95
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 107,
        //.evYield_HP = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KOMALA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        115,
        65,
        65,
        75,
        95
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 168,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COMATOSE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_TURTONATOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        78,
        165,
        47,
        91,
        85
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_DRAGON,
        .catchRate = 70,
        .expYield = 170,
        //.evYield_Defense = 2,
        //.item2 = ITEM_CHARCOAL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SHELL_ARMOR, ABILITY_ROCK_HEAD},
        .abilityHidden = {ABILITY_ANGER_POINT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TOGEDEMARU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        98,
        63,
        96,
        40,
        73
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 180,
        .expYield = 152,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_ELECTRIC_SEED,  VSONINC
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_BARBS, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MIMIKYU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        90,
        80,
        96,
        50,
        105
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpDefense = 2,
        //.item2 = ITEM_CHESTO_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DISGUISE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_BRUXISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        105,
        70,
        92,
        70,
        70
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 80,
        .expYield = 166,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_RAZOR_FANG,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DAZZLING, ABILITY_STRONG_JAW},
            .abilityHidden = {ABILITY_WONDER_SKIN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_DRAMPA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        60,
        85,
        36,
        135,
        91
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DRAGON,
        .catchRate = 70,
        .expYield = 170,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_PERSIM_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BERSERK, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_CLOUD_NINE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DHELMISE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        131,
        100,
        40,
        86,
        90
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 25,
        .expYield = 181,
        //.evYield_Attack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEELWORKER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_JANGMO_O] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        55,
        65,
        45,
        45,
        45
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 60,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_RAZOR_CLAW,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BULLETPROOF, ABILITY_SOUNDPROOF},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_HAKAMO_O] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        75,
        90,
        65,
        65,
        70
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_RAZOR_CLAW,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BULLETPROOF, ABILITY_SOUNDPROOF},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KOMMO_O] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        110,
        125,
        85,
        100,
        105
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_Defense = 3,
       // #ifdef ITEM_EXPANSION
            //.item1 = ITEM_RAZOR_CLAW,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BULLETPROOF, ABILITY_SOUNDPROOF},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },//give vacuum wave

    [SPECIES_TAPU_KOKO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        115,
        85,
        130,
        95,
        75
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ELECTRIC_SURGE, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_TAPU_LELE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        85,
        75,
        95,
        130,
        115
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PSYCHIC_SURGE, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_TAPU_BULU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        83,
        130,
        115,
        75,
        85,
        95
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GRASSY_SURGE, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_TAPU_FINI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        75,
        115,
        85,
        95,
        130
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MISTY_SURGE, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_COSMOG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        43,
        29,
        31,
        37,
        29,
        31
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 40,
        //.evYield_HP = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_UNAWARE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_COSMOEM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        43,
        29,
        131,
        37,
        29,
        131
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 140,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STURDY, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SOLGALEO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        137,
        137,
        107,
        97,
        113,
        89
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FULL_METAL_BODY, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_LUNALA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        137,
        113,
        89,
        97,
        137,
        107
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHADOW_SHIELD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_NIHILEGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        109,
        53,
        47,
        103,
        127,
        131
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_BUZZWOLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        107,
        139,
        139,
        79,
        53,
        53
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_Attack = 1,
        //.evYield_Defense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_PHEROMOSA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        137,
        37,
        151,
        137,
        37
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_XURKITREE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        83,
        89,
        71,
        83,
        173,
        71
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_CELESTEELA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        101,
        103,
        61,
        107,
        101
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_KARTANA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        69,
        181,
        131,
        109,
        59,
        31
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_GUZZLORD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        223,
        101,
        53,
        43,
        97,
        53
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CORRUPTION, ABILITY_NONE },
            .abilityHidden = {ABILITY_BEAST_BOOST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_NECROZMA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        107,
        101,
        79,
        127,
        89
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 255,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRISM_ARMOR, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//light devour(er) add on to prism armor, any light based move used by enemy is canceled and heals necrozma instead,also gets healing in harsh sunlight
    //moves solar beam, synthesis, moonlight, morning sun, etc. sunny day too.  Do like sound just setup a flag for it, or just do am effect search for enemy move
    //put im attack cancelor

    [SPECIES_MAGEARNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        95,
        115,
        65,
        130,
        115
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOUL_HEART, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MARSHADOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        125,
        80,
        125,
        90,
        90
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_GHOST,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 2,
        //.evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TECHNICIAN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_POIPOLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        67,
        73,
        67,
        73,
        73,
        67
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 189,
        //.evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISONED_LEGACY, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BEAST_BOOST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_NAGANADEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        73,
        73,
        73,
        121,
        127,
        73
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 243,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISONED_LEGACY, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_BEAST_BOOST, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_STAKATAKA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        61,
        131,
        211,
        13,
        53,
        101
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_STEEL,
        .catchRate = 30,
        .expYield = 257,
        //.evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_BLACEPHALON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        53,
        127,
        53,
        107,
        151,
        79
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GHOST,
        .catchRate = 30,
        .expYield = 257,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BEAST_BOOST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_ULTRA_BEAST,
    },

    [SPECIES_ZERAORA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        112,
        75,
        143,
        102,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MELTAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        46,
        65,
        65,
        34,
        55,
        35
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 135,
        //.evYield_Attack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_MAGNET_PULL, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MELMETAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        135,
        143,
        143,
        34,
        80,
        65
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_IRON_FIST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_GROOKEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        65,
        50,
        65,
        40,
        40
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GRASSY_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_THWACKEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        86,
        85,
        70,
        80,
        55,
        60
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GRASSY_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_RILLABOOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        130,
        125,
        90,
        85,
        60,
        70
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 265,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_OVERGROW, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GRASSY_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SCORBUNNY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        71,
        40,
        69,
        40,
        40
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIBERO, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_RABOOT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        86,
        60,
        94,
        55,
        60
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIBERO, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_CINDERACE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        116,
        75,
        119,
        65,
        75
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 265,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_BLAZE, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_LIBERO, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SOBBLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        40,
        40,
        70,
        70,
        40
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 62,
        //.evYield_Speed = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DRIZZILE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        55,
        90,
        95,
        55
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_INTELEON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        85,
        65,
        120,
        125,
        65
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 265,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_TORRENT, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SNIPER, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SKWOVET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        55,
        55,
        25,
        35,
        35
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 55,
        //.evYield_HP = 1,
        //.item2 = ITEM_ORAN_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHEEK_POUCH, ABILITY_NONE},
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GREEDENT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        95,
        95,
        20,
        55,
        75
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 161,
        //.evYield_HP = 2,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHEEK_POUCH, ABILITY_NONE},
            .abilityHidden = {ABILITY_GLUTTONY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ROOKIDEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        47,
        35,
        57,
        33,
        35
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_FLYING,
        .catchRate = 255,
        .expYield = 49,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_UNNERVE},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CORVISQUIRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        67,
        55,
        77,
        43,
        55
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_FLYING,
        .catchRate = 120,
        .expYield = 128,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_UNNERVE},
            .abilityHidden = {ABILITY_BIG_PECKS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CORVIKNIGHT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        98,
        87,
        105,
        67,
        53,
        85
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRESSURE, ABILITY_UNNERVE},
            .abilityHidden = {ABILITY_MIRROR_ARMOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_BLIPBUG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        20,
        20,
        75,
        25,
        45
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 255,
        .expYield = 36,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DOTTLER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        35,
        80,
        30,
        50,
        90
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 120,
        .expYield = 117,
        //.evYield_SpDefense = 2,
       // #ifdef ITEM_EXPANSION
            ////.item2 = ITEM_PSYCHIC_SEED,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SWARM, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FOREWARN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ORBEETLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        63,
        45,
        110,
        117,
        90,
        120
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 253,
        //.evYield_SpDefense = 3,
       // #ifdef ITEM_EXPANSION
            ////.item2 = ITEM_PSYCHIC_SEED,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWARM, ABILITY_FRISK},
            .abilityHidden = {ABILITY_FOREWARN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_NICKIT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        28,
        28,
        50,
        47,
        52
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 49,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_UNBURDEN},
            .abilityHidden = {ABILITY_STAKEOUT, ABILITY_PICKUP},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_THIEVUL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        78,
        58,
        112,
        87,
        92
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 127,
        .expYield = 159,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_BANDIT_KING},
            .abilityHidden = {ABILITY_STAKEOUT, ABILITY_MAGICIAN},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOSSIFLEUR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        56,
        40,
        60,
        10,
        40,
        60
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 50,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COTTON_DOWN, ABILITY_REGENERATOR},
        .abilityHidden = {ABILITY_EFFECT_SPORE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ELDEGOSS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        50,
        90,
        60,
        80,
        120
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 161,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COTTON_DOWN, ABILITY_REGENERATOR},
        .abilityHidden = {ABILITY_EFFECT_SPORE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_WOOLOO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        42,
        40,
        55,
        48,
        40,
        45
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 122,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUFFY, ABILITY_RUN_AWAY},
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_SAP_SIPPER},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DUBWOOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        80,
        100,
        88,
        60,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 127,
        .expYield = 172,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLUFFY, ABILITY_STEADFAST},
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_SAP_SIPPER},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_CHEWTLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        64,
        50,
        44,
        38,
        38
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 57,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_SHELL_ARMOR},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DREDNAW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        115,
        90,
        74,
        48,
        68
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ROCK,
        .catchRate = 75,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_SHELL_ARMOR},
        .abilityHidden = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_YAMPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        59,
        45,
        50,
        26,
        40,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 255,
        .expYield = 54,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BALL_FETCH, ABILITY_NONE},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_BOLTUND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        69,
        90,
        60,
        121,
        90,
        60
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 172,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_NONE},
            .abilityHidden = {ABILITY_COMPETITIVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ROLYCOLY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        30,
        40,
        50,
        30,
        40,
        50
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 255,
        .expYield = 48,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEAM_ENGINE, ABILITY_HEATPROOF},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_CARKOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        60,
        90,
        50,
        60,
        70
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FIRE,
        .catchRate = 120,
        .expYield = 144,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEAM_ENGINE, ABILITY_FLAME_BODY},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_COALOSSAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        80,
        120,
        30,
        80,
        90
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 255,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEAM_ENGINE, ABILITY_FLAME_BODY},
        .abilityHidden = {ABILITY_FLASH_FIRE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_APPLIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        51,
        40,
        80,
        20,
        40,
        40
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 255,
        .expYield = 52,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIPEN, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_BULLETPROOF, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_FLAPPLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        87,
        110,
        80,
        70,
        95,
        60
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIPEN, ABILITY_GLUTTONY},
        .abilityHidden = {ABILITY_HUSTLE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_APPLETUN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        110,
        85,
        80,
        30,
        100,
        80
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 170,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIPEN, ABILITY_GLUTTONY},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SILICOBRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        52,
        57,
        75,
        46,
        35,
        50
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 255,
        .expYield = 63,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_SPIT, ABILITY_SHED_SKIN},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SANDACONDA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        107,
        125,
        71,
        65,
        70
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 120,
        .expYield = 179,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_SPIT, ABILITY_SHED_SKIN},
        .abilityHidden = {ABILITY_SAND_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CRAMORANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        85,
        55,
        85,
        85,
        95
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GULP_MISSILE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ARROKUDA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        41,
        63,
        40,
        66,
        40,
        30
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROPELLER_TAIL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BARRASKEWDA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        61,
        123,
        60,
        136,
        60,
        50
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 172,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PROPELLER_TAIL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TOXEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        38,
        35,
        40,
        54,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_POISON,
        .catchRate = 75,
        .expYield = 48,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RATTLED, ABILITY_STATIC},
            .abilityHidden = {ABILITY_KLUTZ, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_TOXTRICITY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        98,
        70,
        75,
        114,
        87
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 176,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PUNK_ROCK, ABILITY_PLUS},
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SIZZLIPEDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        65,
        45,
        65,
        50,
        50
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_BUG,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_WHITE_SMOKE},
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CENTISKORCH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        115,
        65,
        81,
        90,
        90
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_BUG,
        .catchRate = 75,
        .expYield = 184,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_FLASH_FIRE, ABILITY_WHITE_SMOKE},
        .abilityHidden = {ABILITY_FLAME_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CLOBBOPUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        68,
        60,
        32,
        50,
        50
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 180,
        .expYield = 62,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_DRY_SKIN, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GRAPPLOCT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        118,
        90,
        42,
        70,
        80
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 168,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_DRY_SKIN, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SINISTEA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        45,
        45,
        50,
        74,
        54
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 120,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_POLTEAGEIST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        65,
        65,
        70,
        134,
        114
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 60,
        .expYield = 178,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_HATENNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        42,
        30,
        45,
        39,
        56,
        53
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 235,
        .expYield = 53,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_ANTICIPATION},
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_HATTREM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        57,
        40,
        65,
        49,
        86,
        73
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_ANTICIPATION},
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_HATTERENE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        57,
        90,
        95,
        29,
        136,
        103
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 255,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_ANTICIPATION},
            .abilityHidden = {ABILITY_MAGIC_BOUNCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_IMPIDIMP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        45,
        30,
        50,
        55,
        40
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FAIRY,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_FRISK},
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_MORGREM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        45,
        70,
        75,
        55
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_FRISK},
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_GRIMMSNARL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        120,
        65,
        60,
        95,
        75
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 255,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_FRISK},
            .abilityHidden = {ABILITY_PICKPOCKET, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_OBSTAGOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        93,
        90,
        101,
        95,
        60,
        81
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 260,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RECKLESS, ABILITY_GUTS},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_DARK_DEAL}, 
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_PERRSERKER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        110,
        100,
        50,
        50,
        60
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 154,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_TOUGH_CLAWS},
            .abilityHidden = {ABILITY_STEELY_SPIRIT, ABILITY_MAGNET_PULL},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_CURSOLA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        105,
        50,
        30,
        145,
        145
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_ROCK,
        .catchRate = 30,
        .expYield = 179,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_LIQUID_OOZE},
            .abilityHidden = {ABILITY_PERISH_BODY, ABILITY_LIQUID_SOUL},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SIRFETCHD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        62,
        135,
        95,
        65,
        68,
        82
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Attack = 2,
        //.item2 = ITEM_LEEK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_NONE},
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_MR_RIME] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        85,
        75,
        70,
        110,
        100
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TANGLED_FEET, ABILITY_SCREEN_CLEANER},
            .abilityHidden = {ABILITY_ICE_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_RUNERIGUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        95,
        145,
        30,
        50,
        105
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GHOST,
        .catchRate = 90,
        .expYield = 169,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WANDERING_SPIRIT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MILCERY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        40,
        40,
        34,
        50,
        61
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 200,
        .expYield = 54,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FALINKS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        100,
        100,
        75,
        70,
        60
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 165,
        //.evYield_Attack = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_BATTLE_ARMOR, ABILITY_NONE},
        .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PINCURCHIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        101,
        95,
        15,
        91,
        85
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 75,
        .expYield = 152,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ELECTRIC_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SNOM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        25,
        35,
        20,
        45,
        30
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_BUG,
        .catchRate = 190,
        .expYield = 37,
        //.evYield_SpAttack = 1,
       // #ifdef ITEM_EXPANSION
           // //.item2 = ITEM_SNOWBALL,  VSONIC
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ICE_SCALES, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FROSMOTH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        77,
        65,
        60,
        85,
        125,
        90
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_BUG,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_ICE_SCALES, ABILITY_ANTICIPATION},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_STONJOURNER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        125,
        135,
        70,
        20,
        30
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 60,
        .expYield = 165,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POWER_SPOT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_EISCUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        110,
        50,
        65,
        90
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 165,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ICE_FACE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_INDEEDEE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        65,
        55,
        95,
        105,
        95
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_NORMAL,
        .catchRate = 30,
        .expYield = 166,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 40,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_EMPATH},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PSYCHIC_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MORPEKO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        95,
        58,
        97,
        70,
        58
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_DARK,
        .catchRate = 180,
        .expYield = 153,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HUNGER_SWITCH, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_CUFANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        80,
        49,
        40,
        40,
        49
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_NORMAL,
        .catchRate = 190,
        .expYield = 66,
        //.evYield_Attack = 1,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_LAGGING_TAIL, vsonic  hold effect is done, but item not defined to make sure hold effects are in right place
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHEER_FORCE, ABILITY_NONE},
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_STALL},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_COPPERAJAH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        122,
        130,
        69,
        30,
        80,
        69
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 175,
        //.evYield_Attack = 2,
       // #ifdef ITEM_EXPANSION
         //   //.item2 = ITEM_LAGGING_TAIL,   vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHEER_FORCE, ABILITY_NONE},
            .abilityHidden = {ABILITY_HEAVY_METAL, ABILITY_STALL},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DRACOZOLT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        100,
        90,
        75,
        80,
        70
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Attack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_HUSTLE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARCTOZOLT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        100,
        90,
        55,
        90,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Attack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_STATIC},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_SLUSH_RUSH, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DRACOVISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        90,
        100,
        75,
        70,
        80
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Defense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_ABSORB, ABILITY_STRONG_JAW},
            .abilityHidden = {ABILITY_SAND_RUSH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARCTOVISH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        90,
        100,
        55,
        80,
        90
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 177,
        //.evYield_Defense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WATER_ABSORB, ABILITY_ICE_BODY},
            .abilityHidden = {ABILITY_SLUSH_RUSH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DURALUDON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        95,
        115,
        85,
        120,
        50
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 187,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LIGHT_METAL, ABILITY_HEAVY_METAL},
            .abilityHidden = {ABILITY_STALWART, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DREEPY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        28,
        60,
        30,
        82,
        40,
        30
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 54,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CLEAR_BODY, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DRAKLOAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        80,
        50,
        102,
        60,
        50
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 144,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CLEAR_BODY, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DRAGAPULT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        120,
        75,
        142,
        100,
        75
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 300,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CLEAR_BODY, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ZACIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        130,
        115,
        138,
        80,
        115
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 10,
        .expYield = 335,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTREPID_SWORD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZAMAZENTA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        130,
        115,
        138,
        80,
        115
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_NORMAL,
        .catchRate = 10,
        .expYield = 335,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DAUNTLESS_SHIELD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ETERNATUS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        140,
        85,
        95,
        130,
        145,
        95
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 255,
        .expYield = 345,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},  //vsonic would like make own unique ability no idea what shold be, but it does steal light? 
        .bodyColor = BODY_COLOR_PURPLE,         //but don't want to just copy necrozma, it absorbs energy, can possibly affect space time
        .noFlip = FALSE,
    }, //since it absorbs things to grow get stronger maybe boosts def spdef?

    [SPECIES_KUBFU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        90,
        60,
        72,
        53,
        50
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 77,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 120,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_URSHIFU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        130,
        100,
        97,
        63,
        60
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_DARK,
        .catchRate = 3,
        .expYield = 275,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 120,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_UNSEEN_FIST, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_ZARUDE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        120,
        105,
        105,
        70,
        95
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_GRASS,
        .catchRate = 3,
        .expYield = 300,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_REGIELEKI] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        100,
        50,
        200,
        100,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_TRANSISTOR, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_REGIDRAGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        200,
        100,
        50,
        80,
        100,
        50
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
            .abilities = {ABILITY_DRAGONS_MAW, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_GLASTRIER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        145,
        130,
        30,
        65,
        110
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHILLING_NEIGH, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    }, //note setup ability so it plays the cry before the stat boost

    [SPECIES_SPECTRIER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        65,
        60,
        130,
        145,
        80
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GRIM_NEIGH, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//note setup ability so it plays the cry before the stat boost  /DONE

    [SPECIES_CALYREX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        80,
        80,
        80,
        80,
        80
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_GRASS,
        .catchRate = 3,
        .expYield = 250,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 50,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_UNNERVE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },//need to add below mon to species_to_national dex in pokemon.c

    [SPECIES_WYRDEER] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            103,
            105,
            72,
            65,
            105,
            75
            ),
            .type1 = TYPE_NORMAL,
            .type2 = TYPE_PSYCHIC,
            .catchRate = 45,
            .expYield = 184,
            //.evYield_Attack = 1,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_INTIMIDATE, ABILITY_FRISK},
            .abilityHidden = {ABILITY_SAP_SIPPER, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GRAY,
            .noFlip = FALSE,
        },

        [SPECIES_KLEAVOR] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            70,
            135,
            95,
            85,
            45,
            70
            ),
            .type1 = TYPE_BUG,
            .type2 = TYPE_ROCK,
            .catchRate = 25,
            .expYield = 175,
            //.evYield_Attack = 2,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 25,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_BUG,
            .eggGroup2 = EGG_GROUP_BUG,
            .abilities = {ABILITY_SWARM, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_STEADFAST, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BROWN,
            .noFlip = FALSE,
        },

        [SPECIES_URSALUNA] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            130,
            140,
            105,
            50,
            45,
            80
            ),
            .type1 = TYPE_GROUND,
            .type2 = TYPE_NORMAL,
            .catchRate = 75,
            .expYield = 194,
            //.evYield_Attack = 3,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_GUTS, ABILITY_BULLETPROOF},
            .abilityHidden = {ABILITY_GORILLA_TACTICS, ABILITY_UNNERVE},
            .bodyColor = BODY_COLOR_BROWN,
            .noFlip = FALSE,
        },

        [SPECIES_BASCULEGION] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            120,
            112,
            65,
            78,
            80,
            75
            ),
            .type1 = TYPE_WATER,
            .type2 = TYPE_GHOST,
            .catchRate = 25,
            .expYield = 186,
            //.evYield_HP = 2,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 40,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_WATER_2,
            .eggGroup2 = EGG_GROUP_WATER_2,
            .abilities = {ABILITY_RATTLED, ABILITY_ADAPTABILITY},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GREEN,
            .noFlip = FALSE,
            .flags = SPECIES_FLAG_GENDER_DIFFERENCE,
        },

        [SPECIES_SNEASLER] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            80,
            130,
            60,
            120,
            40,
            80
            ),
            .type1 = TYPE_FIGHTING,
            .type2 = TYPE_POISON,
            .catchRate = 135,
            .expYield = 179,
            //.evYield_Attack = 1,
            //.evYield_Speed = 1,
            .genderRatio = PERCENT_FEMALE(MON_FEMALE),
            .eggCycles = 20,
            .friendship = 10,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_FEMME_FATALE, ABILITY_FEMME_FATALE},
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BLUE,
            .noFlip = FALSE,
        },//think will make female only evo, counterpart to salazzle
        //give ABILITY_FEMME_FATALE when finish setup

        [SPECIES_OVERQWIL] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            85,
            115,
            95,
            85,
            65,
            65
            ),
            .type1 = TYPE_DARK,
            .type2 = TYPE_POISON,
            .catchRate = 135,
            .expYield = 180,
            //.evYield_Attack = 1,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_WATER_2,
            .eggGroup2 = EGG_GROUP_WATER_2,
            .abilities = {ABILITY_POISON_POINT, ABILITY_SWIFT_SWIM},
            .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BLACK,
            .noFlip = FALSE,
        },

        [SPECIES_ENAMORUS] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            74,
            115,
            70,
            106,
            135,
            80
            ),
            .type1 = TYPE_FAIRY,
            .type2 = TYPE_FLYING,
            .catchRate = 3,
            .expYield = 261,
            //.evYield_SpAttack = 3,
            .genderRatio = MON_FEMALE,
            .eggCycles = 120,
            .friendship = 25,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_UNDISCOVERED,
            .eggGroup2 = EGG_GROUP_UNDISCOVERED,
            .abilities = {ABILITY_HEALER, ABILITY_NONE},
            .abilityHidden = {ABILITY_CONTRARY, ABILITY_NONE},
            .bodyColor = BODY_COLOR_PINK,
            .noFlip = FALSE,
            //.flags = SPECIES_FLAG_LEGENDARY, don't need
        },

        [SPECIES_CEFIREON] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            65,
            65,
            60,
            130,
            110,
            95
            ),
            .type1 = TYPE_FLYING,
            .type2 = TYPE_GHOST,
            .catchRate = 45,
            .expYield = 184,
            //.evYield_SpDefense = 2,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 35,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_LIGHTNING_ROD},
            //#ifdef BATTLE_ENGINE
                .abilityHidden = {ABILITY_COMPOUND_EYES, ABILITY_WHITE_SMOKE},
            // #endif
            .bodyColor = BODY_COLOR_YELLOW,
            .noFlip = FALSE,
            
        },

        [SPECIES_FRAEYJTA] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            170,  //hp betweeen snorlax and chansey
            15,
            25,
            60,
            50,
            210
            ),
            .type1 = TYPE_FAIRY,
            .type2 = TYPE_GHOST,
            .catchRate = 13,
            .expYield = 384,
            //.evYield_SpDefense = 2,
            .genderRatio = MON_FEMALE,
            .eggCycles = 35,
             .friendship = 15,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_UNDISCOVERED,
            .eggGroup2 = EGG_GROUP_UNDISCOVERED,
            .abilities = {ABILITY_OMNIPOTENT_AIDE, ABILITY_NONE}, //make ability that passes on any healing received to battle partner, potentially also makes healing effect priority?
            //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_DISPIRIT_GUARD, ABILITY_NONE}, //not able to heal this mon, ok just make it so recovery moves don't work on it, otherwise would be horribly annoying
            // #endif
            .bodyColor = BODY_COLOR_GRAY,
            .noFlip = FALSE,
        }, //give move powersplit,   //name is a mix of word for fairy,  freya norse goddess of protection/that watches over the dead, body based on priscilla from dark souls
        //ok ability plan is heal moves don't work on self, if partner alive (and passes normal recurring ability conditions) increase priority by 3, same as triage
        //heal them instead

    [SPECIES_VENUSAUR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        100,
        123,
        80,
        122,
        120
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 281,
        //.evYield_SpAttack = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_THICK_FAT, ABILITY_THICK_FAT},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CHARIZARD_MEGA_X] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        130,
        111,
        100,
        130,
        85
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 285,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_TOUGH_CLAWS},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_CHARIZARD_MEGA_Y] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        104,
        78,
        100,
        159,
        115
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 285,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_SUN_DISK, ABILITY_SUN_DISK},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BLASTOISE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        103,
        120,
        78,
        135,
        115
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 284,
        //.evYield_SpDefense = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MEGA_LAUNCHER, ABILITY_MEGA_LAUNCHER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BEEDRILL_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        150,
        40,
        145,
        15,
        80
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 223,
        //.evYield_Attack = 2,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ADAPTABILITY, ABILITY_ADAPTABILITY},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIDGEOT_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        83,
        80,
        80,
        121,
        135,
        80
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 261,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_NO_GUARD, ABILITY_NO_GUARD},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ALAKAZAM_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        50,
        65,
        150,
        175,
        105
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 50,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        //.item2 = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_TRACE, ABILITY_TRACE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SLOWBRO_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        75,
        180,
        30,
        130,
        80
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 207,
        //.evYield_Defense = 2,
        //.item2 = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SHELL_ARMOR, ABILITY_SHELL_ARMOR},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_GENGAR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        65,
        80,
        130,
        170,
        95
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_SHADOW_TAG, ABILITY_SHADOW_TAG},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_KANGASKHAN_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        125,
        100,
        100,
        60,
        100
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 45,
        .expYield = 207,
        //.evYield_HP = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PARENTAL_BOND, ABILITY_PARENTAL_BOND},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PINSIR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        155,
        120,
        105,
        65,
        90
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 210,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AERILATE, ABILITY_AERILATE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GYARADOS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        155,
        109,
        81,
        70,
        130
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 224,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOLD_BREAKER, ABILITY_MOLD_BREAKER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_AERODACTYL_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        135,
        85,
        150,
        70,
        95
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 215,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 35,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_TOUGH_CLAWS},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MEWTWO_MEGA_X] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        106,
        190,
        100,
        130,
        154,
        100
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 351,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_STEADFAST},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MEWTWO_MEGA_Y] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        106,
        150,
        70,
        140,
        194,
        120
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 351,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_INSOMNIA, ABILITY_INSOMNIA},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_AMPHAROS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        95,
        105,
        45,
        165,
        110
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 275,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MOLD_BREAKER, ABILITY_MOLD_BREAKER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_STEELIX_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        125,
        230,
        30,
        55,
        95
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GROUND,
        .catchRate = 25,
        .expYield = 214,
        //.evYield_Defense = 2,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_FORCE, ABILITY_SAND_FORCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SCIZOR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        150,
        140,
        75,
        65,
        100
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 25,
        .expYield = 210,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TECHNICIAN, ABILITY_TECHNICIAN},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_HERACROSS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        185,
        115,
        75,
        40,
        105
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 210,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SKILL_LINK, ABILITY_SKILL_LINK},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_HOUNDOOM_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        90,
        90,
        115,
        140,
        90
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 210,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOLAR_POWER, ABILITY_SOLAR_POWER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_TYRANITAR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        164,
        150,
        71,
        95,
        120
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 315,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_SAND_STREAM, ABILITY_SAND_STREAM},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_SCEPTILE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        110,
        75,
        165,
        145,
        85
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 284,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        .abilities = {ABILITY_REGENERATOR, ABILITY_REGENERATOR}, //...why did this get lightning rod.
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN, //it regenerates its tail its getting that instead
        .noFlip = FALSE, //there's little reason to pair this with water or flying type
    }, //give sceptile flamethrower incinerate & fire blast (incinerate is for technician)

    [SPECIES_BLAZIKEN_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        160,
        80,
        100,
        130,
        80
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 284,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_SPEED_BOOST, ABILITY_SPEED_BOOST},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_SWAMPERT_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        150,
        110,
        70,
        95,
        110
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 286,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_SWIFT_SWIM},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GARDEVOIR_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        85,
        65,
        100,
        165,
        135
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 278,
        //.evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PIXILATE, ABILITY_PIXILATE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_SABLEYE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        95,
        125,
        20,
        85,
        115
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 168,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_MAGIC_BOUNCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_STALL, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MAWILE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        105,
        125,
        50,
        55,
        95
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 168,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_HUGE_POWER, ABILITY_HUGE_POWER},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_AGGRON_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        140,
        230,
        50,
        60,
        80
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 284,
        //.evYield_Defense = 3,
        //.item2 = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FILTER, ABILITY_FILTER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MEDICHAM_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        85,
        100,
        80,
        85
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 90,
        .expYield = 179,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        .abilities = {ABILITY_PURE_POWER, ABILITY_PURE_POWER},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MANECTRIC_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        75,
        80,
        135,
        135,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 201,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_INTIMIDATE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_SHARPEDO_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        140,
        70,
        105,
        110,
        65
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 60,
        .expYield = 196,
        //.evYield_Attack = 2,
        //.item2 = ITEM_DEEP_SEA_TOOTH,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STRONG_JAW, ABILITY_STRONG_JAW},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CAMERUPT_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        120,
        100,
        20,
        145,
        105
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GROUND,
        .catchRate = 150,
        .expYield = 196,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHEER_FORCE, ABILITY_SHEER_FORCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ALTARIA_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        110,
        110,
        80,
        110,
        105
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 207,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_ERRATIC,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PIXILATE, ABILITY_PIXILATE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_BANETTE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        84,
        145,
        75,
        86,
        123,
        83
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 194,
        //.evYield_Attack = 2,
        //.item2 = ITEM_SPELL_TAG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRANKSTER, ABILITY_PRANKSTER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_ABSOL_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        150,
        60,
        115,
        115,
        60
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 30,
        .expYield = 198,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 10,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_MAGIC_BOUNCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GLALIE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        120,
        130,
        100,
        120,
        80
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ROCK,
        .catchRate = 75,
        .expYield = 203,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_REFRIGERATE, ABILITY_REFRIGERATE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SALAMENCE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        145,
        130,
        120,
        120,
        90
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 315,
        //.evYield_Attack = 3,
        //.item2 = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_DRAGON,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AERILATE, ABILITY_AERILATE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_METAGROSS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        145,
        150,
        110,
        105,
        110
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_Defense = 3,
        //.item2 = ITEM_METAL_COAT,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_TOUGH_CLAWS},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LATIAS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        100,
        120,
        110,
        140,
        150
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SPECTRE, ABILITY_SPECTRE},  //vsonic NEED replace for this
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_LATIOS_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        130,
        100,
        110,
        160,
        120
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SPECTRE, ABILITY_SPECTRE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_LOPUNNY_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        136,
        94,
        135,
        54,
        96
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 60,
        .expYield = 203,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 30,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SCRAPPY, ABILITY_SCRAPPY},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GARCHOMP_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        108,
        170,
        115,
        92,
        120,
        95
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 315,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_DRAGON,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_FORCE, ABILITY_SAND_FORCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    }, //ugly don't want to use

    [SPECIES_LUCARIO_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        145,
        88,
        112,
        140,
        70
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 219,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ADAPTABILITY, ABILITY_ADAPTABILITY},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ABOMASNOW_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        132,
        105,
        30,
        132,
        105
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 208,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        //.item2 = ITEM_NEVER_MELT_ICE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_WARNING, ABILITY_SNOW_WARNING},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GALLADE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        68,
        165,
        95,
        110,
        65,
        115
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FIGHTING,
        .catchRate = 45,
        .expYield = 278,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_INNER_FOCUS, ABILITY_INNER_FOCUS},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_AUDINO_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        103,
        60,
        126,
        50,
        80,
        126
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FAIRY,
        .catchRate = 255,
        .expYield = 425,
        //.evYield_HP = 2,
        //.item1 = ITEM_ORAN_BERRY,
        //.item2 = ITEM_SITRUS_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HEALER, ABILITY_HEALER},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DIANCIE_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        160,
        110,
        110,
        160,
        110
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGIC_BOUNCE, ABILITY_MAGIC_BOUNCE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_RAYQUAZA_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        180,
        75,
        115,
        180,
        100
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_Attack = 2,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DELTA_STREAM, ABILITY_DELTA_STREAM},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    }, //need bring this down in mega/primal readjust

    [SPECIES_KYOGRE_PRIMAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        120,
        90,
        90,
        180,
        160
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 3,
        .expYield = 302,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRIMORDIAL_SEA, ABILITY_PRIMORDIAL_SEA},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GROUDON_PRIMAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        180,
        160,
        100,
        130,
        90
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FIRE,
        .catchRate = 3,
        .expYield = 302,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DESOLATE_LAND, ABILITY_DESOLATE_LAND},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_RATTATA_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        30,
        56,
        35,
        72,
        25,
        35
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 51,
        //.evYield_Speed = 1,
        //.item2 = ITEM_PECHA_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_HUSTLE},
        .abilityHidden = {ABILITY_SCRAPPY, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_RATICATE_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        71,
        70,
        77,
        40,
        80
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 127,
        .expYield = 145,
        //.evYield_Speed = 2,
        //.item2 = ITEM_PECHA_BERRY,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_HUSTLE},
        .abilityHidden = {ABILITY_THICK_FAT, ABILITY_STRONG_JAW},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_RAICHU_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        85,
        50,
        110,
        105,
        85
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 218,
        //.evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SURGE_SURFER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_SANDSHREW_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        75,
        90,
        40,
        10,
        35
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_GRIP_CLAW,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_NONE},
            .abilityHidden = {ABILITY_SLUSH_RUSH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_SANDSLASH_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        100,
        120,
        65,
        25,
        65
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_STEEL,
        .catchRate = 90,
        .expYield = 158,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_NONE},
            .abilityHidden = {ABILITY_SLUSH_RUSH, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_VULPIX_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        41,
        40,
        65,
        50,
        65
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 190,
        .expYield = 60,
        //.evYield_Speed = 1,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_SNOWBALL,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_MULTI_TASK},
            .abilityHidden = {ABILITY_SNOW_WARNING, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_NINETALES_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        73,
        67,
        75,
        109,
        81,
        100
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_FAIRY,
        .catchRate = 75,
        .expYield = 177,
        //.evYield_Speed = 1,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SNOW_CLOAK, ABILITY_MULTI_TASK},
            .abilityHidden = {ABILITY_SNOW_WARNING, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_DIGLETT_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        10,
        55,
        30,
        90,
        35,
        45
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 53,
        //.evYield_Speed = 1,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_VEIL, ABILITY_TANGLING_HAIR},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_DUGTRIO_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        100,
        60,
        110,
        50,
        70
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_STEEL,
        .catchRate = 50,
        .expYield = 149,
        //.evYield_Speed = 2,
        //.item2 = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SAND_VEIL, ABILITY_TANGLING_HAIR},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_MEOWTH_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        60,
        35,
        97,
        50,
        40
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DARK,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Speed = 1,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_STALL},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_PERSIAN_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        88,
        60,
        135,
        75,
        65
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_DARK,
        .catchRate = 90,
        .expYield = 154,
        //.evYield_Speed = 2,
        //.item2 = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_TECHNICIAN},
            .abilityHidden = {ABILITY_RATTLED, ABILITY_STALL},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    }, //changed up sprite face

    [SPECIES_GEODUDE_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        80,
        100,
        20,
        30,
        45
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 255,
        .expYield = 60,
        //.evYield_Defense = 1,
       // #ifdef ITEM_EXPANSION
          //  //.item2 = ITEM_CELL_BATTERY, vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_MUSCLE_MAGIC}, //replace magnet pull w ABILITY_MUSCLE_MAGIC put sturdy i slot 1
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GALVANIZE, ABILITY_DRY_SKIN}, //planned to replace magnet pull w muscle magic, but with magnet pull buff and effectiveness change
        // #endif
        .bodyColor = BODY_COLOR_BROWN,                      //magnet pull would actually be good on them...they could slow down steel types and then super hit them with electricity
        .noFlip = FALSE,                            //but on the other hand most steel are electric too, so it'd be neutral, while rock is weak to steel.. 
        .flags = F_ALOLAN_FORM,                 //oh but made electric resist, so it'd just be a neutral hit, hmm check how many steel are also electric to see value
    },//checked steel and they are rare, many are psuedos so its not a type you'd ecounter much, many resist electric, good against metagross, but still a very specific thing

    [SPECIES_GRAVELER_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        95,
        115,
        35,
        45,
        65
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 120,
        .expYield = 137,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
         //   //.item2 = ITEM_CELL_BATTERY,  vsonic
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_MUSCLE_MAGIC},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GALVANIZE, ABILITY_MULTI_TASK},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_GOLEM_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        120,
        130,
        45,
        55,
        75
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 45,
        .expYield = 223,
        //.evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        .abilities = {ABILITY_STURDY, ABILITY_MUSCLE_MAGIC},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_GALVANIZE, ABILITY_DRY_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_GRIMER_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(80, 80, 50, 25, 40, 65),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_HP = 1,
       // #ifdef ITEM_EXPANSION
         //.item2 = ITEM_BLACK_SLUDGE, 
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_TOUCH, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_POWER_OF_ALCHEMY, ABILITY_POISON_HEAL},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_MUK_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 105, 75, 50, 65, 100),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DARK,
        .catchRate = 75,
        .expYield = 175,
        //.evYield_HP = 1,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_TOUCH, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_POWER_OF_ALCHEMY, ABILITY_POISON_HEAL},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_EXEGGUTOR_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(115, 105, 85, 37, 125, 75),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_DRAGON,
        .catchRate = 45,
        .expYield = 186,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_GRASS,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FRISK, ABILITY_LONG_REACH},
            .abilityHidden = {ABILITY_HARVEST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_MAROWAK_ALOLAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(60, 88, 80, 65, 66, 118),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_GHOST,
        .catchRate = 75,
        .expYield = 149,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CURSED_BODY, ABILITY_LIGHTNING_ROD},
        .abilityHidden = {ABILITY_ROCK_HEAD, ABILITY_MUSCLE_MAGIC}, //gets so many good special moves
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
        .flags = F_ALOLAN_FORM,
    },

    [SPECIES_MEOWTH_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        65,
        55,
        40,
        40,
        40
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 58,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_TOUGH_CLAWS},
            .abilityHidden = {ABILITY_UNNERVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_PONYTA_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        85,
        55,
        90,
        65,
        65
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 82,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_PASTEL_VEIL},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_RAPIDASH_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        100,
        70,
        105,
        80,
        80
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 60,
        .expYield = 175,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RUN_AWAY, ABILITY_PASTEL_VEIL},
            .abilityHidden = {ABILITY_ANTICIPATION, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_SLOWPOKE_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        65,
        65,
        15,
        40,
        40
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 63,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GLUTTONY, ABILITY_OWN_TEMPO},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },


    [SPECIES_SLOWBRO_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        100,
        95,
        30,
        100,
        70
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 172,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_QUICK_DRAW, ABILITY_OWN_TEMPO},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    //uses much bigger stalk/leek cant fly so will be grouded
    [SPECIES_FARFETCHD_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        57,
        115,
        65,
        50,
        58,
        62
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 132,
        //.evYield_Attack = 1,
        //.item1 = ITEM_LEEK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STEADFAST, ABILITY_NONE},
            .abilityHidden = {ABILITY_SCRAPPY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_WEEZING_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        90,
        120,
        60,
        85,
        90
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_FAIRY,
        .catchRate = 60,
        .expYield = 172,
        //.evYield_Defense = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_MISTY_SEED,
        // #endif
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POISON_POINT, ABILITY_NEUTRALIZING_GAS},
            .abilityHidden = {ABILITY_MISTY_SURGE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_MR_MIME_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        50,
        65,
        65,
        100,
        90,
        90
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 45,
        .expYield = 161,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_VITAL_SPIRIT, ABILITY_SCREEN_CLEANER},
            .abilityHidden = {ABILITY_ICE_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_ARTICUNO_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        85,
        85,
        95,
        125,
        100
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_COMPETITIVE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_ZAPDOS_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        125,
        90,
        100,
        85,
        90
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DEFIANT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_MOLTRES_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        90,
        85,
        75,
        90,
        100,
        125
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 290,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DREAD_WING, ABILITY_NONE}, //more in line with theme, weakens opponents, with aura letting it do more physical/special dmg and take less physical dmg
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    }, //lacks special dark moves, as they pretty much don't exist outside of its unique move

    [SPECIES_SLOWKING_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        65,
        80,
        30,
        110,
        110
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 70,
        .expYield = 172,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_WATER_1,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CURIOUS_MEDICINE, ABILITY_OWN_TEMPO},
            .abilityHidden = {ABILITY_REGENERATOR, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_CORSOLA_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        75,
        100,
        30,
        75,
        120
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_ROCK,
        .catchRate = 60,
        .expYield = 144,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_WATER_3,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_OCEAN_MEMORY, ABILITY_LIQUID_OOZE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_LIQUID_SOUL},
       // #ifdef BATTLE_ENGINE//courtesy of haven new ability Liquid Soul turns water moves into ghost moves
        .bodyColor = BODY_COLOR_WHITE,//other idea Ocean Memory, reduced damage from water moves
        .noFlip = FALSE,    // for ancient pokemon or fosill mon that previoiusly dwelled in water
        .flags = F_GALARIAN_FORM,
    }, //gave this line liquid ooze to double up on absorb damage from ghost tweak :)

    [SPECIES_ZIGZAGOON_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        30,
        41,
        60,
        30,
        41
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 255,
        .expYield = 56,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_DARK_DEAL},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_LINOONE_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        70,
        61,
        100,
        50,
        61
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_NORMAL,
        .catchRate = 90,
        .expYield = 147,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_GLUTTONY},
            .abilityHidden = {ABILITY_QUICK_FEET, ABILITY_DARK_DEAL},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_DARUMAKA_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        90,
        45,
        50,
        15,
        45
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 120,
        .expYield = 63,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_HUSTLE, ABILITY_NONE},
        .abilityHidden = {ABILITY_INNER_FOCUS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_DARMANITAN_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        140,
        55,
        95,
        30,
        55
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 168,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GORILLA_TACTICS, ABILITY_NONE},
            .abilityHidden = {ABILITY_ZEN_MODE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_YAMASK_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        38,
        55,
        85,
        30,
        30,
        65
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GHOST,
        .catchRate = 190,
        .expYield = 61,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WANDERING_SPIRIT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_STUNFISK_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        109,
        81,
        99,
        32,
        66,
        84
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_STEEL,
        .catchRate = 75,
        .expYield = 165,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MIMICRY, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_GROWLITHE_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            60,
            75,
            45,
            55,
            65,
            50
            ),
            .type1 = TYPE_FIRE,
            .type2 = TYPE_ROCK,
            .catchRate = 190,
            .expYield = 70,
            //.evYield_Attack = 1,
            .genderRatio = PERCENT_FEMALE(25),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE},
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BROWN,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_ARCANINE_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            95,
            115,
            80,
            90,
            95,
            80
            ),
            .type1 = TYPE_FIRE,
            .type2 = TYPE_ROCK,
            .catchRate = 75,
            .expYield = 194,
            //.evYield_Attack = 2,
            .genderRatio = PERCENT_FEMALE(25),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE},
            .abilityHidden = {ABILITY_JUSTIFIED, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BROWN,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_VOLTORB_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            56,
            55,
            50,
            100,
            65,
            70
            ),
            .type1 = TYPE_ELECTRIC,
            .type2 = TYPE_GRASS,
            .catchRate = 190,
            .expYield = 66,
            //.evYield_Speed = 1,
            .genderRatio = MON_GENDERLESS,
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_MINERAL,
            .eggGroup2 = EGG_GROUP_MINERAL,
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_STATIC},
            .abilityHidden = {ABILITY_GRASSY_SURGE, ABILITY_SKILL_LINK}, //ok remember wy I did this now, their grass so get bullet seed, this would guarantee 5 hit
            .bodyColor = BODY_COLOR_RED,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_ELECTRODE_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            76,
            75,
            70,
            130,
            90,
            90
            ),
            .type1 = TYPE_ELECTRIC,
            .type2 = TYPE_GRASS,
            .catchRate = 60,
            .expYield = 172,
            //.evYield_Speed = 2,
            .genderRatio = MON_GENDERLESS,
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_MINERAL,
            .eggGroup2 = EGG_GROUP_MINERAL,
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_STATIC},
            .abilityHidden = {ABILITY_GRASSY_SURGE, ABILITY_SKILL_LINK},
            .bodyColor = BODY_COLOR_RED,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_TYPHLOSION_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            73,
            84,
            78,
            95,
            119,
            85
            ),
            .type1 = TYPE_FIRE,
            .type2 = TYPE_GHOST,
            .catchRate = 45,
            .expYield = 240,
            //.evYield_SpAttack = 3,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_BLAZE, ABILITY_NONE},
            .abilityHidden = {ABILITY_FRISK, ABILITY_FILTER},
            .bodyColor = BODY_COLOR_YELLOW,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_QWILFISH_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            65,
            95,
            85,
            85,
            55,
            55
            ),
            .type1 = TYPE_DARK,
            .type2 = TYPE_POISON,
            .catchRate = 45,
            .expYield = 88,
            //.evYield_Attack = 1,
            //.item2 = ITEM_POISON_BARB,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_WATER_2,
            .eggGroup2 = EGG_GROUP_WATER_2,
            .abilities = {ABILITY_POISON_POINT, ABILITY_SWIFT_SWIM},
            .abilityHidden = {ABILITY_INTIMIDATE, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GRAY,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_SNEASEL_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            55,
            95,
            55,
            115,
            35,
            75
            ),
            .type1 = TYPE_POISON,
            .type2 = TYPE_FIGHTING,
            .catchRate = 60,
            .expYield = 86,
            //.evYield_Speed = 1,
            //.item2 = ITEM_QUICK_CLAW,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
            .friendship = 10,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_PRESSURE, ABILITY_INNER_FOCUS},
            .abilityHidden = {ABILITY_POISON_TOUCH, ABILITY_KEEN_EYE}, 
            .bodyColor = BODY_COLOR_BLACK,
            .noFlip = TRUE,
            .flags = F_HISUIAN_FORM,
        },

//////#if P_GEN_5_POKEMON == TRUE
        [SPECIES_SAMUROTT_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            90,
            108,
            80,
            85,
            100,
            65
            ),
            .type1 = TYPE_WATER,
            .type2 = TYPE_DARK,
            .catchRate = 45,
            .expYield = 238,
            //.evYield_SpAttack = 3,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_TORRENT, ABILITY_NONE},
            .abilityHidden = {ABILITY_SHELL_ARMOR, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BLUE,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_LILLIGANT_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            70,
            105,
            75,
            105,
            50,
            75
            ),
            .type1 = TYPE_GRASS,
            .type2 = TYPE_FIGHTING,
            .catchRate = 75,
            .expYield = 168,
            //.evYield_Attack = 2,
            ////.item2 = ITEM_ABSORB_BULB,  new item?
            .genderRatio = MON_FEMALE,
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_GRASS,
            .eggGroup2 = EGG_GROUP_GRASS,
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_HUSTLE},
            .abilityHidden = {ABILITY_LEAF_GUARD, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GREEN,
            .noFlip = TRUE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_ZORUA_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            35,
            60,
            40,
            70,
            85,
            40
            ),
            .type1 = TYPE_NORMAL,
            .type2 = TYPE_GHOST,
            .catchRate = 75,
            .expYield = 66,
            //.evYield_SpAttack = 1,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 25,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_ILLUSION, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GRAY,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_ZOROARK_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            55,
            100,
            60,
            110,
            125,
            60
            ),
            .type1 = TYPE_NORMAL,
            .type2 = TYPE_GHOST,
            .catchRate = 45,
            .expYield = 179,
            //.evYield_SpAttack = 2,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FIELD,
            .eggGroup2 = EGG_GROUP_FIELD,
            .abilities = {ABILITY_ILLUSION, ABILITY_NONE},
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
            .bodyColor = BODY_COLOR_GRAY,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_BRAVIARY_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            110,
            83,
            70,
            65,
            112,
            70
            ),
            .type1 = TYPE_PSYCHIC,
            .type2 = TYPE_FLYING,
            .catchRate = 60,
            .expYield = 179,
            //.evYield_SpAttack = 2,
            .genderRatio = MON_MALE,
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_FLYING,
            .eggGroup2 = EGG_GROUP_FLYING,
            .abilities = {ABILITY_KEEN_EYE, ABILITY_SHEER_FORCE},
            .abilityHidden = {ABILITY_DEFIANT, ABILITY_NONE},
            .bodyColor = BODY_COLOR_RED,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },
//// #endif

////#if P_GEN_6_POKEMON == TRUE
        [SPECIES_SLIGGOO_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            58,
            75,
            83,
            40,
            83,
            113
            ),
            .type1 = TYPE_DRAGON,
            .type2 = TYPE_STEEL,
            .catchRate = 45,
            .expYield = 158,
            //.evYield_SpDefense = 2,
            ////.item2 = ITEM_SHED_SHELL, new item?
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 40,
            .friendship = 10,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_DRAGON,
            .eggGroup2 = EGG_GROUP_DRAGON,
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_OVERCOAT},
            .abilityHidden = {ABILITY_GOOEY, ABILITY_NONE},
            .bodyColor = BODY_COLOR_PURPLE,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_GOODRA_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            80,
            100,
            100,
            60,
            110,
            150
            ),
            .type1 = TYPE_DRAGON,
            .type2 = TYPE_STEEL,
            .catchRate = 45,
            .expYield = 270,
            //.evYield_SpDefense = 3,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 40,
            .friendship = 10,
            .growthRate = GROWTH_SLOW,
            .eggGroup1 = EGG_GROUP_DRAGON,
            .eggGroup2 = EGG_GROUP_DRAGON,
            .abilities = {ABILITY_SAP_SIPPER, ABILITY_OVERCOAT},
            .abilityHidden = {ABILITY_GOOEY, ABILITY_NONE},
            .bodyColor = BODY_COLOR_PURPLE,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

        [SPECIES_AVALUGG_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            95,
            127,
            184,
            38,
            34,
            36
            ),
            .type1 = TYPE_ICE,
            .type2 = TYPE_ROCK,
            .catchRate = 55,
            .expYield = 180,
            //.evYield_Defense = 2,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_FAST,
            .eggGroup1 = EGG_GROUP_MONSTER,
            .eggGroup2 = EGG_GROUP_MINERAL,
            .abilities = {ABILITY_STRONG_JAW, ABILITY_ICE_BODY},
            .abilityHidden = {ABILITY_STURDY, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BLUE,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },
//// #endif

////#if P_GEN_7_POKEMON == TRUE
        [SPECIES_DECIDUEYE_HISUIAN] =
        { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
            98,
            112,
            80,
            60,
            95,
            95
            ),
            .type1 = TYPE_GRASS,
            .type2 = TYPE_FIGHTING,
            .catchRate = 45,
            .expYield = 239,
            //.evYield_Attack = 3,
            .genderRatio = PERCENT_FEMALE(12.5),
            .eggCycles = 15,
             .friendship = 15,
            .growthRate = GROWTH_MEDIUM_SLOW,
            .eggGroup1 = EGG_GROUP_FLYING,
            .eggGroup2 = EGG_GROUP_FLYING,
            .abilities = {ABILITY_OVERGROW, ABILITY_SCRAPPY},
            .abilityHidden = {ABILITY_FEATHER_JACKET, ABILITY_NONE},
            .bodyColor = BODY_COLOR_BROWN,
            .noFlip = FALSE,
            .flags = F_HISUIAN_FORM,
        },

    [SPECIES_PIKACHU_COSPLAY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//ok cosplay pikachu, is just the special base form, that  changes with the costome so not necessary as I'm doing the radical red version
    //doing plus 40 bst for each form to make unique/

    [SPECIES_PIKACHU_ROCK_STAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        95,
        60,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_STEEL,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//don't take rest of pika abilitie instead for forms that change type fill with abilities that fit secondary type
    //nvm just keeping lightning rod,  as that's what it had in game change typing and stats and instead of doing like rotom forms give each its own learnset
    
    [SPECIES_PIKACHU_BELLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        70,
        95,
        95,
        66
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ICE,    //lol cottage core
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //ok can't make this grass, but would really really want a grass/electric one so I could do a cottage core pikachu idea.  but idk maybe still fits

    [SPECIES_PIKACHU_POP_STAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        75,
        40,
        95,
        105,
        70
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FAIRY,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_PH_D] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        105,
        100,
        60
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_LIBRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        110,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FIGHTING,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
       .abilities = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    }, //not taking cap forms

    [SPECIES_PIKACHU_ORIGINAL_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_HOENN_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_SINNOH_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_UNOVA_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_KALOS_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_ALOLA_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_PARTNER_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PIKACHU_WORLD_CAP] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        35,
        75,
        40,
        95,
        85,
        50
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 112,
        //.evYield_Speed = 2,
        //.item2 = ITEM_LIGHT_BALL,
        .genderRatio = MON_MALE,
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_NONE},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_PICHU_SPIKY_EARED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        20,
        40,
        30,
        60,
        55,
        35
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 190,
        .expYield = 41,
        //.evYield_Speed = 1,
        //.item2 = ITEM_LIGHT_BALL, //change logic think give volt tackle if pichu  is created while holding ths item
        .genderRatio = PERCENT_FEMALE(50), //think want set it so if spiky eared pichuy is generated they always have this
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_STATIC, ABILITY_PLUS},
        .abilityHidden = {ABILITY_LIGHTNING_ROD, ABILITY_OVERCHARGE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },//make rare form, that should spawn

    [SPECIES_UNOWN_B] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_C] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_D] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_E] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_F] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_G] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_H] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_I] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_J] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_K] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_L] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_M] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_N] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_O] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_P] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_Q] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_R] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_S] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_T] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_U] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_V] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_W] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_X] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_Y] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_Z] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_EMARK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_UNOWN_QMARK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        48,
        72,
        48,
        48,
        72,
        48
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 225,
        .expYield = 118,
        //.evYield_Attack = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILTY_UNKNOWN_POWER, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_CASTFORM_SUNNY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 70, 70, 70, 70, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_HP = 1,
        //.item1 = ITEM_MYSTIC_WATER,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_FORECAST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CASTFORM_RAINY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 70, 70, 70, 70, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_HP = 1,
        //.item1 = ITEM_MYSTIC_WATER,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_FORECAST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CASTFORM_SNOWY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(75, 70, 70, 70, 70, 70),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 147,
        //.evYield_HP = 1,
        //.item1 = ITEM_MYSTIC_WATER,
        //.item2 = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_FORECAST, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_DEOXYS_ATTACK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 180, 20, 150, 180, 20),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 2,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DEOXYS_DEFENSE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 70, 160, 90, 70, 160),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Defense = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DEOXYS_SPEED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(50, 95, 90, 180, 95, 90),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_BURMY_SANDY_CLOAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 29, 45, 36, 29, 45),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 45,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_ANTICIPATION, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_BURMY_TRASH_CLOAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(40, 29, 45, 36, 29, 45),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 120,
        .expYield = 45,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_ANTICIPATION, ABILITY_NONE},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_WORMADAM_SANDY_CLOAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 89, 125, 36, 59, 85),
        .type1 = TYPE_BUG,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 148,
        //.evYield_Defense = 2,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ANTICIPATION, ABILITY_ROUGH_SKIN},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_IMMUNITY},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_WORMADAM_TRASH_CLOAK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 69, 115, 36, 69, 115),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 45,
        .expYield = 148,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_SILVER_POWDER,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ANTICIPATION, ABILITY_IRON_BARBS},
            .abilityHidden = {ABILITY_OVERCOAT, ABILITY_STURDY},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CHERRIM_SUNSHINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(90, 70, 70, 100, 97, 60),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FIRE, //makes no sense not to do this for grass mon that needs sun
        .catchRate = 75,
        .expYield = 158,
        //.evYield_SpAttack = 2,
        //.item2 = ITEM_MIRACLE_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_GRASS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_GIFT, ABILITY_NONE},//can't have different ability/hidden ability,  as this form is linked to ability
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = TRUE,
    }, //dropped attack back to 70 as ability is meant to boost atk & sp def in sun

    [SPECIES_SHELLOS_EAST_SEA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 48, 48, 34, 57, 62),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 190,
        .expYield = 65,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STICKY_HOLD, ABILITY_STORM_DRAIN},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GASTRODON_EAST_SEA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(111, 83, 68, 39, 92, 82),
        .type1 = TYPE_WATER,
        .type2 = TYPE_GROUND,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STICKY_HOLD, ABILITY_STORM_DRAIN},
            .abilityHidden = {ABILITY_SAND_FORCE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ROTOM_HEAT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(66, 76, 110, 76, 107, 85),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FIRE,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_SOLAR_POWER, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_FLAME_BODY},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //higher defense than base lower than bulk forms as its a microwave / plan to give second secondary type hidden ability for slot 4 so here anotehr fire ability
    //need to change weight for these forms as well

    [SPECIES_ROTOM_WASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 65, 97, 81, 75, 97),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_SWIFT_SWIM, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_STORM_DRAIN}, //here another water ability
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },//bulk

    [SPECIES_ROTOM_FROST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 74, 107, 74, 81, 97),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ICE,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_SNOW_CLOAK, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_FILTER},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //all in floating list so immune to ground by base, so while not ghost still retains ghost elements / bulk

    [SPECIES_ROTOM_FAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(66, 67, 67, 112, 105, 87),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_GALE_WINGS, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_GALEFORCE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //Maybe Fan could be given a spatk version of wind rider So it has a wind immunity and gets spatk boosts
    //wind moves i.e gust whirlwind huricane etc. setup with flag like iron  fist
    //ability name wind tunnel or turbine (still worksshopping name)  /Galeforce!!

    [SPECIES_ROTOM_MOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(76, 102, 80, 90, 103, 77),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_GRASS,
        .catchRate = 45,
        .expYield = 182,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        .abilities = {ABILITY_LEAF_GUARD, ABILITY_OVERCHARGE},
        .abilityHidden = {ABILITY_MOTOR_DRIVE, ABILITY_GRASSY_SURGE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    }, //speed attacker

    [SPECIES_GIRATINA_ORIGIN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(150, 120, 100, 90, 120, 100),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 306,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_INVERSE_WORLD, ABILITY_NONE}, //LOGIC not done yet
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_SHAYMIN_SKY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(130, 103, 75, 127, 120, 75),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 270,
        //.evYield_HP = 3,
        //.item1 = ITEM_LUM_BERRY,
        //.item2 = ITEM_LUM_BERRY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_FIGHTING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_FLYING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_POISON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_POISON,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_GROUND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_ROCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_ROCK,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_BUG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_BUG,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_GHOST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_STEEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_FIRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_FIRE,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_WATER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_GRASS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_GRASS,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_ELECTRIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_ELECTRIC,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_PSYCHIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_ICE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_DRAGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_DRAGON,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_DARK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_DARK,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ARCEUS_FAIRY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        120,
        120,
        120,
        120,
        120,
        120
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 324,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MULTITYPE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_BASCULIN_BLUE_STRIPED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(70, 92, 65, 98, 80, 55),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 25,
        .expYield = 161,
        //.evYield_Speed = 2,
        //.item2 = ITEM_DEEP_SEA_SCALE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ROCK_HEAD, ABILITY_ADAPTABILITY},
            .abilityHidden = {ABILITY_MOLD_BREAKER, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DARMANITAN_ZEN_MODE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(155, 30, 105, 55, 140, 105),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 60,
        .expYield = 189,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHEER_FORCE, ABILITY_IRON_FIST},
            .abilityHidden = {ABILITY_ZEN_MODE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(105, 160, 55, 135, 30, 55),
        .type1 = TYPE_ICE,
        .type2 = TYPE_FIRE,
        .catchRate = 60,
        .expYield = 189,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GORILLA_TACTICS, ABILITY_NONE},
            .abilityHidden = {ABILITY_ZEN_MODE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
        .flags = F_GALARIAN_FORM,
    },

    [SPECIES_DEERLING_SUMMER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        60,
        50,
        75,
        40,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_DEERLING_AUTUMN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        60,
        50,
        75,
        40,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_DEERLING_WINTER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        60,
        50,
        75,
        40,
        50
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 190,
        .expYield = 67,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SAWSBUCK_SUMMER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        99,
        100,
        70,
        95,
        60,
        70
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SAWSBUCK_AUTUMN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        99,
        100,
        70,
        95,
        60,
        70
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_SAWSBUCK_WINTER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        99,
        100,
        70,
        95,
        60,
        70
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GRASS,
        .catchRate = 75,
        .expYield = 166,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_CHLOROPHYLL, ABILITY_SAP_SIPPER},
        .abilityHidden = {ABILITY_SERENE_GRACE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_TORNADUS_THERIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        100,
        80,
        121,
        110,
        90
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_REGENERATOR, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_THUNDURUS_THERIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        105,
        70,
        101,
        145,
        80
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_VOLT_ABSORB, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_LANDORUS_THERIAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        89,
        145,
        90,
        91,
        105,
        80
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_FLYING,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 25,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_INTIMIDATE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_KYUREM_WHITE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        125,
        120,
        90,
        95,
        170,
        100
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TURBOBLAZE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KYUREM_BLACK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        125,
        170,
        100,
        95,
        120,
        90
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 315,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TERAVOLT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_KELDEO_RESOLUTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        91,
        72,
        90,
        108,
        129,
        90
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 261,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 80,
        .friendship = 10,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_JUSTIFIED, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MELOETTA_PIROUETTE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        128,
        90,
        128,
        77,
        77
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FIGHTING,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Defense = 1,
        //.evYield_Speed = 1,
        //.item1 = ITEM_STAR_PIECE,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_SERENE_GRACE, ABILITY_MAGIC_GUARD},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_GENESECT_DOUSE_DRIVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        120,
        95,
        99,
        120,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DOWNLOAD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GENESECT_SHOCK_DRIVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        120,
        95,
        99,
        120,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DOWNLOAD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GENESECT_BURN_DRIVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        120,
        95,
        99,
        120,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DOWNLOAD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GENESECT_CHILL_DRIVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        71,
        120,
        95,
        99,
        120,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_STEEL,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DOWNLOAD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_GRENINJA_BATTLE_BOND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        95,
        67,
        122,
        103,
        71
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 239,
        //.evYield_Speed = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTLE_BOND, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_GRENINJA_ASH] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        72,
        145,
        67,
        132,
        153,
        71
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_DARK,
        .catchRate = 45,
        .expYield = 288,
        //.evYield_Speed = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_BATTLE_BOND, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},  //JUST like cherrim can't have another ability as its trigger for this form
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_POLAR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_TUNDRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_CONTINENTAL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_GARDEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_ELEGANT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_MEADOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_MODERN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_MARINE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_ARCHIPELAGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_HIGH_PLAINS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_SANDSTORM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_RIVER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_MONSOON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_SAVANNA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_SUN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_OCEAN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_JUNGLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_FANCY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_VIVILLON_POKE_BALL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        52,
        50,
        89,
        90,
        50
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 185,
        //.evYield_HP = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_BUG,
        .eggGroup2 = EGG_GROUP_BUG,
        .abilities = {ABILITY_SHIELD_DUST, ABILITY_COMPOUND_EYES},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_FRIEND_GUARD, ABILITY_WONDER_SKIN},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_UNFEZANT_F] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        65,
        65,
        93,
        115,
        100
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 220,
        //.evYield_Attack = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SERENE_GRACE, ABILITY_SUPER_LUCK},
            .abilityHidden = {ABILITY_QUEENLY_MAJESTY, ABILITY_STAMINA},
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_PYROAR_F] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        89,
        98,
        72,
        116,
        109,
        66
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_NORMAL,
        .catchRate = 65,
        .expYield = 177,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(87.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RIVALRY, ABILITY_TIGER_MOM},//CHANGE give own ability TIGER_MOM/Apex Predator
            .abilityHidden = {ABILITY_MOXIE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_FLABEBE_YELLOW_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        39,
        42,
        61,
        79
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLABEBE_ORANGE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        39,
        42,
        61,
        79
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLABEBE_BLUE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        39,
        42,
        61,
        79
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLABEBE_WHITE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        44,
        38,
        39,
        42,
        61,
        79
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 225,
        .expYield = 61,
        //.evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE_YELLOW_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        45,
        47,
        52,
        75,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE_ORANGE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        45,
        47,
        52,
        75,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE_BLUE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        45,
        47,
        52,
        75,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE_WHITE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        45,
        47,
        52,
        75,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 130,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLOETTE_ETERNAL_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        74,
        65,
        67,
        92,
        125,
        128
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 120,
        .expYield = 243,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },//special az version

    [SPECIES_FLORGES_YELLOW_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        65,
        68,
        75,
        112,
        154
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLORGES_ORANGE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        65,
        68,
        75,
        112,
        154
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLORGES_BLUE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        65,
        68,
        75,
        112,
        154
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FLORGES_WHITE_FLOWER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        78,
        65,
        68,
        75,
        112,
        154
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 248,
        //.evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FLOWER_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_SYMBIOSIS, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_HEART_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_STAR_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_DIAMOND_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_DEBUTANTE_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_MATRON_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_DANDY_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_LA_REINE_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_KABUKI_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_FURFROU_PHARAOH_TRIM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        60,
        102,
        65,
        90
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_NORMAL,
        .catchRate = 160,
        .expYield = 165,
        //.evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FUR_COAT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_MEOWSTIC_FEMALE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        74,
        48,
        76,
        104,
        83,
        81
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_PSYCHIC,
        .catchRate = 75,
        .expYield = 163,
        //.evYield_Speed = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_KEEN_EYE, ABILITY_INFILTRATOR},
            .abilityHidden = {ABILITY_COMPETITIVE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_AEGISLASH_BLADE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        150,
        50,
        60,
        150,
        50
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_GHOST,
        .catchRate = 45,
        .expYield = 234,
        //.evYield_Defense = 2,
        //.evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_STANCE_CHANGE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PUMPKABOO_SMALL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        59,
        66,
        70,
        56,
        44,
        55
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 67,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PUMPKABOO_LARGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        69,
        66,
        70,
        46,
        44,
        55
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 67,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_PUMPKABOO_SUPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        79,
        66,
        70,
        41,
        44,
        55
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 120,
        .expYield = 67,
        //.evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOURGEIST_SMALL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        85,
        122,
        99,
        58,
        75
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 60,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOURGEIST_LARGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        122,
        69,
        58,
        75
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 60,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_GOURGEIST_SUPER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        100,
        122,
        54,
        58,
        75
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GRASS,
        .catchRate = 60,
        .expYield = 173,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PICKUP, ABILITY_FRISK},
        .abilityHidden = {ABILITY_INSOMNIA, ABILITY_PICKPOCKET},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_XERNEAS_ACTIVE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        126,
        131,
        95,
        99,
        131,
        98
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 306,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_FAIRY_AURA, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZYGARDE_10] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        100,
        71,
        115,
        61,
        85
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 219,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AURA_BREAK, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_ZYGARDE_10_POWER_CONSTRUCT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        54,
        100,
        71,
        115,
        61,
        85
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 219,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POWER_CONSTRUCT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_ZYGARDE_50_POWER_CONSTRUCT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        108,
        100,
        121,
        95,
        81,
        95
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POWER_CONSTRUCT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ZYGARDE_COMPLETE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        216,
        100,
        121,
        85,
        91,
        95
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_GROUND,
        .catchRate = 3,
        .expYield = 319,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_POWER_CONSTRUCT, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },

    [SPECIES_HOOPA_UNBOUND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        160,
        60,
        80,
        170,
        130
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_DARK,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 100,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_MAGICIAN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_ORICORIO_POM_POM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        70,
        70,
        93,
        98,
        70
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DANCER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ORICORIO_PAU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        70,
        70,
        93,
        98,
        70
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DANCER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_ORICORIO_SENSU] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        70,
        70,
        93,
        98,
        70
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FLYING,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpAttack = 2,
       // #ifdef ITEM_EXPANSION
            //.item2 = ITEM_HONEY,
        // #endif
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FLYING,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DANCER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ROCKRUFF_OWN_TEMPO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        65,
        40,
        60,
        30,
        40
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_ROCK,
        .catchRate = 190,
        .expYield = 56,
        //.evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_OWN_TEMPO, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_LYCANROC_MIDNIGHT] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        85,
        115,
        75,
        82,
        55,
        75
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_ROCK,
        .catchRate = 90,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        .abilities = {ABILITY_NO_GUARD, ABILITY_ROCK_HEAD},//known for headbuts, doesn't learn headbut...
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_VITAL_SPIRIT, ABILITY_NONE}, //change evo move to headbutt   eventually learn move head smash
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },  //give sucker punch /setup to also evolve with moon stone, make no guard first abiility, think buff keen eye

    [SPECIES_LYCANROC_DUSK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        117,
        65,
        110,
        55,
        65
        ),
        .type1 = TYPE_FIGHTING, //each form has different evo move, shift moves around to fit new typing, give counter
        .type2 = TYPE_ROCK, //setup to evolve with dusk stone as well
        .catchRate = 90,
        .expYield = 170,
        //.evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_TOUGH_CLAWS, ABILITY_ROCK_HEAD},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_WISHIWASHI_SCHOOL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        45,
        140,
        130,
        30,
        140,
        135
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_WATER,
        .catchRate = 60,
        .expYield = 61,
        //.evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
         .friendship = 15,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_WATER_2,
        .eggGroup2 = EGG_GROUP_WATER_2,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SCHOOLING, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_FIGHTING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_FLYING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_POISON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_GROUND] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_GROUND,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_ROCK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_BUG] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_BUG,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_GHOST] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_STEEL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_FIRE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_FIRE,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_WATER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_WATER,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_GRASS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_ELECTRIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_PSYCHIC] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_ICE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_DRAGON] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_DRAGON,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_DARK] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_SILVALLY_FAIRY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        95,
        95,
        95,
        95,
        95,
        95
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_MYSTERY,
        .catchRate = 3,
        .expYield = 257,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_RKS_SYSTEM, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_ORANGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_YELLOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_GREEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_BLUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_INDIGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_METEOR_VIOLET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        60,
        100,
        60,
        60,
        100
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_RED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_ORANGE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_YELLOW] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_GREEN] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_BLUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_INDIGO] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_MINIOR_CORE_VIOLET] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        100,
        60,
        120,
        100,
        60
        ),
        .type1 = TYPE_ROCK,
        .type2 = TYPE_FLYING,
        .catchRate = 30,
        .expYield = 154,
        //.evYield_Defense = 1,
        //.evYield_SpDefense = 1,
        //.item2 = ITEM_STAR_PIECE,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_MINERAL,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SHIELDS_DOWN, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MIMIKYU_BUSTED] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        55,
        90,
        80,
        96,
        50,
        105
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_FAIRY,
        .catchRate = 45,
        .expYield = 167,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_AMORPHOUS,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DISGUISE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_NECROZMA_DUSK_MANE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        157,
        127,
        77,
        113,
        109
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_STEEL,
        .catchRate = 255,
        .expYield = 306,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRISM_ARMOR, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_NECROZMA_DAWN_WINGS] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        113,
        109,
        77,
        157,
        127
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_GHOST,
        .catchRate = 255,
        .expYield = 306,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PRISM_ARMOR, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_NECROZMA_ULTRA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        97,
        167,
        97,
        129,
        167,
        97
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_DRAGON,
        .catchRate = 255,
        .expYield = 339,
        //.evYield_Attack = 1,
        //.evYield_Speed = 1,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_NEUROFORCE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_MAGEARNA_ORIGINAL_COLOR] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        80,
        95,
        115,
        65,
        130,
        115
        ),
        .type1 = TYPE_STEEL,
        .type2 = TYPE_FAIRY,
        .catchRate = 3,
        .expYield = 270,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SOUL_HEART, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_CRAMORANT_GULPING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        85,
        55,
        85,
        85,
        95
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GULP_MISSILE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_CRAMORANT_GORGING] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        85,
        55,
        85,
        85,
        95
        ),
        .type1 = TYPE_FLYING,
        .type2 = TYPE_WATER,
        .catchRate = 45,
        .expYield = 166,
        //.evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FLYING,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_GULP_MISSILE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_TOXTRICITY_LOW_KEY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        98,
        70,
        75,
        114,
        87
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_POISON,
        .catchRate = 45,
        .expYield = 176,
        //.evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_HUMAN_LIKE,
        .eggGroup2 = EGG_GROUP_HUMAN_LIKE,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_PUNK_ROCK, ABILITY_MINUS},
            .abilityHidden = {ABILITY_TECHNICIAN, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_SINISTEA_ANTIQUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        40,
        45,
        45,
        50,
        74,
        54
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 120,
        .expYield = 62,
        //.evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_POLTEAGEIST_ANTIQUE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        60,
        65,
        65,
        70,
        134,
        114
        ),
        .type1 = TYPE_GHOST,
        .type2 = TYPE_GHOST,
        .catchRate = 60,
        .expYield = 178,
        //.evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_MINERAL,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_WEAK_ARMOR, ABILITY_NONE},
            .abilityHidden = {ABILITY_CURSED_BODY, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_RUBY_CREAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_MATCHA_CREAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_MINT_CREAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_LEMON_CREAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_SALTED_CREAM] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_RUBY_SWIRL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_CARAMEL_SWIRL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
    },

    [SPECIES_ALCREMIE_RAINBOW_SWIRL] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        65,
        60,
        75,
        64,
        110,
        121
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_FAIRY,
        .catchRate = 100,
        .expYield = 173,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_AMORPHOUS,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_SWEET_VEIL, ABILITY_NONE},
            .abilityHidden = {ABILITY_AROMA_VEIL, ABILITY_NONE},
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_EISCUE_NOICE_FACE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        75,
        80,
        70,
        130,
        65,
        50
        ),
        .type1 = TYPE_ICE,
        .type2 = TYPE_ICE,
        .catchRate = 60,
        .expYield = 165,
        //.evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_WATER_1,
        .eggGroup2 = EGG_GROUP_FIELD,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_ICE_FACE, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_INDEEDEE_FEMALE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        70,
        55,
        65,
        85,
        95,
        105
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_NORMAL,
        .catchRate = 30,
        .expYield = 166,
        //.evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 40,
         .friendship = 30,
        .growthRate = GROWTH_FAST,
        .eggGroup1 = EGG_GROUP_FAIRY,
        .eggGroup2 = EGG_GROUP_FAIRY,
        .abilities = {ABILITY_OWN_TEMPO, ABILITY_EMPATH},
        //#ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_PSYCHIC_SURGE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_MORPEKO_HANGRY] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        58,
        95,
        58,
        97,
        70,
        58
        ),
        .type1 = TYPE_ELECTRIC,
        .type2 = TYPE_DARK,
        .catchRate = 180,
        .expYield = 153,
        //.evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroup1 = EGG_GROUP_FIELD,
        .eggGroup2 = EGG_GROUP_FAIRY,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_HUNGER_SWITCH, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = FALSE,
    },

    [SPECIES_ZACIAN_CROWNED_SWORD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        170,
        115,
        148,
        80,
        115
        ),
        .type1 = TYPE_FAIRY,
        .type2 = TYPE_STEEL,
        .catchRate = 10,
        .expYield = 360,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_INTREPID_SWORD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLUE,
        .noFlip = FALSE,
    },

    [SPECIES_ZAMAZENTA_CROWNED_SHIELD] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        92,
        130,
        145,
        128,
        80,
        145
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_STEEL,
        .catchRate = 10,
        .expYield = 360,
        //.evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_DAUNTLESS_SHIELD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_RED,
        .noFlip = FALSE,
    },

    [SPECIES_ETERNATUS_ETERNAMAX] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        255,
        115,
        250,
        130,
        125,
        250
        ),
        .type1 = TYPE_POISON,
        .type2 = TYPE_DRAGON,
        .catchRate = 255,
        .expYield = 563,
        //.evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        .abilities = {ABILITY_HI_PRESSURE, ABILITY_NONE},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_PURPLE,
        .noFlip = FALSE,
    },

    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        130,
        100,
        97,
        63,
        60
        ),
        .type1 = TYPE_FIGHTING,
        .type2 = TYPE_WATER,
        .catchRate = 3,
        .expYield = 275,
        //.evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 120,
         .friendship = 15,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_UNSEEN_FIST, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = FALSE,
    },

    [SPECIES_ZARUDE_DADA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        105,
        120,
        105,
        105,
        70,
        95
        ),
        .type1 = TYPE_DARK,
        .type2 = TYPE_GRASS,
        .catchRate = 3,
        .expYield = 300,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_LEAF_GUARD, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
    },

    [SPECIES_CALYREX_ICE_RIDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        165,
        150,
        50,
        85,
        130
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_ICE,
        .catchRate = 3,
        .expYield = 340,
        //.evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 50,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AS_ONE_ICE_RIDER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_WHITE,
        .noFlip = FALSE,
    },//note setup ability so it plays the cry of glastrier before the stat boost
    
    [SPECIES_CALYREX_SHADOW_RIDER] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        100,
        85,
        80,
        150,
        165,
        100
        ),
        .type1 = TYPE_PSYCHIC,
        .type2 = TYPE_GHOST,
        .catchRate = 3,
        .expYield = 340,
        //.evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 120,
        .friendship = 50,
        .growthRate = GROWTH_SLOW,
        .eggGroup1 = EGG_GROUP_UNDISCOVERED,
        .eggGroup2 = EGG_GROUP_UNDISCOVERED,
        //#ifdef BATTLE_ENGINE
            .abilities = {ABILITY_AS_ONE_SHADOW_RIDER, ABILITY_NONE},
       // #ifdef BATTLE_ENGINE
            .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        // #endif
        .bodyColor = BODY_COLOR_BLACK,
        .noFlip = FALSE,
    },//note setup ability so it plays the cry of spectrier before the stat boost IMPORTANT - DONE

    [SPECIES_TORTERRA_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        175,
        92,
        126,
        21,
        92,
        106
        ),
        .type1 = TYPE_GRASS,
        .type2 = TYPE_ROCK,
        .catchRate = 45,
        .expYield = 281,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_GRASS,
        .abilities = {ABILITY_ECOSYSTEM, ABILITY_ECOSYSTEM},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = FALSE,
        .flags = F_MEGA_FORM,
    },

    [SPECIES_MAROWAK_MEGA] =
    { 
           //hp, atk, def, spd, spatk, spdef
         STATS(
        88,
        126,
        164,
        56,
        31,
        106
        ),
        .type1 = TYPE_NORMAL,
        .type2 = TYPE_GROUND,
        .catchRate = 45,
        .expYield = 281,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
         .friendship = 15,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroup1 = EGG_GROUP_MONSTER,
        .eggGroup2 = EGG_GROUP_MONSTER,
        .abilities = {ABILITY_MUSCLE_MAGIC, ABILITY_MUSCLE_MAGIC},
        .abilityHidden = {ABILITY_NONE, ABILITY_NONE},
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = FALSE,
        .flags = F_MEGA_FORM,
    },
};
