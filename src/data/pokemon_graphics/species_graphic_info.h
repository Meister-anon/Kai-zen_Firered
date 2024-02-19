
#define FRONT_PIC(sprite)                    \
        .frontPic = gMonFrontPic_## sprite,                 \
        .frontPicSize = 0x800

#define FRONT_PIC_FEMALE(sprite, width, height)             \
        .frontPicFemale = gMonFrontPic_## sprite##F,        \
        .frontPicSizeFemale = MON_COORDS_SIZE(width, height)

#define BACK_PIC(sprite)                     \
        .backPic = gMonBackPic_## sprite,                   \
        .backPicSize = 0x800

#define FRONT_COORD(size, y_offset)                    \
        .frontCoordSize = size,                 \
        .frontPicYOffset = y_offset

#define BACK_COORD(size, y_offset)                    \
        .backCoordSize = size,                 \
        .backPicYOffset = y_offset


#define PALETTES(pal)                                       \
        .palette = gMonPalette_## pal,                      \
        .shinyPalette = gMonShinyPalette_## pal


#define ICON(sprite, palId)                                 \
        .iconSprite = gMonIcon_## sprite,                   \
        .iconPalIndex = palId

const struct SpeciesGraphicInfo gSpeciesGraphics[] =
{
[SPECIES_NONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //QuestionMark,
[SPECIES_BULBASAUR] = 
    {  
      FRONT_PIC(Bulbasaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Bulbasaur),
      BACK_COORD(0x88,0),
      PALETTES(Bulbasaur),
      ICON(Bulbasaur,0),
    }, //Bulbasaur,
[SPECIES_IVYSAUR] = 
    {  
      FRONT_PIC(Ivysaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Ivysaur),
      BACK_COORD(0x88,0),
      PALETTES(Ivysaur),
      ICON(Ivysaur,0),
    }, //Ivysaur,
[SPECIES_VENUSAUR] = 
    {  
      FRONT_PIC(Venusaur),
      FRONT_COORD(0x88,0),
      BACK_PIC(Venusaur),
      BACK_COORD(0x88,0),
      PALETTES(Venusaur),
      ICON(Venusaur,0),
    }, //Venusaur,
[SPECIES_CHARMANDER] = 
    {  
      FRONT_PIC(Charmander),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charmander),
      BACK_COORD(0x88,0),
      PALETTES(Charmander),
      ICON(Charmander,0),
    }, //Charmander,
[SPECIES_CHARMELEON] = 
    {  
      FRONT_PIC(Charmeleon),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charmeleon),
      BACK_COORD(0x88,0),
      PALETTES(Charmeleon),
      ICON(Charmeleon,0),
    }, //Charmeleon,
[SPECIES_CHARIZARD] = 
    {  
      FRONT_PIC(Charizard),
      FRONT_COORD(0x88,0),
      BACK_PIC(Charizard),
      BACK_COORD(0x88,0),
      PALETTES(Charizard),
      ICON(Charizard,0),
    }, //Charizard,
[SPECIES_SQUIRTLE] = 
    {  
      FRONT_PIC(Squirtle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Squirtle),
      BACK_COORD(0x88,0),
      PALETTES(Squirtle),
      ICON(Squirtle,0),
    }, //Squirtle,
[SPECIES_WARTORTLE] = 
    {  
      FRONT_PIC(Wartortle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Wartortle),
      BACK_COORD(0x88,0),
      PALETTES(Wartortle),
      ICON(Wartortle,0),
    }, //Wartortle,
[SPECIES_BLASTOISE] = 
    {  
      FRONT_PIC(Blastoise),
      FRONT_COORD(0x88,0),
      BACK_PIC(Blastoise),
      BACK_COORD(0x88,0),
      PALETTES(Blastoise),
      ICON(Blastoise,0),
    }, //Blastoise,
[SPECIES_CATERPIE] = 
    {  
      FRONT_PIC(Caterpie),
      FRONT_COORD(0x88,0),
      BACK_PIC(Caterpie),
      BACK_COORD(0x88,0),
      PALETTES(Caterpie),
      ICON(Caterpie,0),
    }, //Caterpie,
[SPECIES_METAPOD] = 
    {  
      FRONT_PIC(Metapod),
      FRONT_COORD(0x88,0),
      BACK_PIC(Metapod),
      BACK_COORD(0x88,0),
      PALETTES(Metapod),
      ICON(Metapod,0),
    }, //Metapod,
[SPECIES_BUTTERFREE] = 
    {  
      FRONT_PIC(Butterfree),
      FRONT_COORD(0x88,0),
      BACK_PIC(Butterfree),
      BACK_COORD(0x88,0),
      PALETTES(Butterfree),
      ICON(Butterfree,0),
    }, //Butterfree,
[SPECIES_WEEDLE] = 
    {  
      FRONT_PIC(Weedle),
      FRONT_COORD(0x88,0),
      BACK_PIC(Weedle),
      BACK_COORD(0x88,0),
      PALETTES(Weedle),
      ICON(Weedle,0),
    }, //Weedle,
[SPECIES_KAKUNA] = 
    {  
      FRONT_PIC(Kakuna),
      FRONT_COORD(0x88,0),
      BACK_PIC(Kakuna),
      BACK_COORD(0x88,0),
      PALETTES(Kakuna),
      ICON(Kakuna,0),
    }, //Kakuna,
[SPECIES_BEEDRILL] = 
    {  
      FRONT_PIC(Beedrill),
      FRONT_COORD(0x88,0),
      BACK_PIC(Beedrill),
      BACK_COORD(0x88,0),
      PALETTES(Beedrill),
      ICON(Beedrill,0),
    }, //Beedrill,
[SPECIES_PIDGEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pidgey,
[SPECIES_PIDGEOTTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pidgeotto,
[SPECIES_PIDGEOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pidgeot,
[SPECIES_RATTATA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rattata,
[SPECIES_RATICATE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Raticate,
[SPECIES_SPEAROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spearow,
[SPECIES_FEAROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fearow,
[SPECIES_EKANS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ekans,
[SPECIES_ARBOK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arbok,
[SPECIES_PIKACHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pikachu,
[SPECIES_RAICHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Raichu,
[SPECIES_SANDSHREW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sandshrew,
[SPECIES_SANDSLASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sandslash,
[SPECIES_NIDORAN_F] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NidoranF,
[SPECIES_NIDORINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nidorina,
[SPECIES_NIDOQUEEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nidoqueen,
[SPECIES_NIDORAN_M] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NidoranM,
[SPECIES_NIDORINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nidorino,
[SPECIES_NIDOKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nidoking,
[SPECIES_CLEFAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clefairy,
[SPECIES_CLEFABLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clefable,
[SPECIES_VULPIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vulpix,
[SPECIES_NINETALES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ninetales,
[SPECIES_JIGGLYPUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jigglypuff,
[SPECIES_WIGGLYTUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wigglytuff,
[SPECIES_ZUBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zubat,
[SPECIES_GOLBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golbat,
[SPECIES_ODDISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Oddish,
[SPECIES_GLOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gloom,
[SPECIES_VILEPLUME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vileplume,
[SPECIES_PARAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Paras,
[SPECIES_PARASECT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Parasect,
[SPECIES_VENONAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Venonat,
[SPECIES_VENOMOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Venomoth,
[SPECIES_DIGLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Diglett,
[SPECIES_DUGTRIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dugtrio,
[SPECIES_MEOWTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meowth,
[SPECIES_PERSIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Persian,
[SPECIES_PSYDUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Psyduck,
[SPECIES_GOLDUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golduck,
[SPECIES_MANKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mankey,
[SPECIES_PRIMEAPE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Primeape,
[SPECIES_GROWLITHE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Growlithe,
[SPECIES_ARCANINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arcanine,
[SPECIES_POLIWAG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Poliwag,
[SPECIES_POLIWHIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Poliwhirl,
[SPECIES_POLIWRATH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Poliwrath,
[SPECIES_ABRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Abra,
[SPECIES_KADABRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kadabra,
[SPECIES_ALAKAZAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alakazam,
[SPECIES_MACHOP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Machop,
[SPECIES_MACHOKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Machoke,
[SPECIES_MACHAMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Machamp,
[SPECIES_BELLSPROUT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bellsprout,
[SPECIES_WEEPINBELL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Weepinbell,
[SPECIES_VICTREEBEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Victreebel,
[SPECIES_TENTACOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tentacool,
[SPECIES_TENTACRUEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tentacruel,
[SPECIES_GEODUDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Geodude,
[SPECIES_GRAVELER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Graveler,
[SPECIES_GOLEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golem,
[SPECIES_PONYTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ponyta,
[SPECIES_RAPIDASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rapidash,
[SPECIES_SLOWPOKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slowpoke,
[SPECIES_SLOWBRO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slowbro,
[SPECIES_MAGNEMITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magnemite,
[SPECIES_MAGNETON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magneton,
[SPECIES_FARFETCHD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Farfetchd,
[SPECIES_DODUO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Doduo,
[SPECIES_DODRIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dodrio,
[SPECIES_SEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seel,
[SPECIES_DEWGONG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dewgong,
[SPECIES_GRIMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grimer,
[SPECIES_MUK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Muk,
[SPECIES_SHELLDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shellder,
[SPECIES_CLOYSTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cloyster,
[SPECIES_GASTLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gastly,
[SPECIES_HAUNTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Haunter,
[SPECIES_GENGAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gengar,
[SPECIES_ONIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Onix,
[SPECIES_DROWZEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drowzee,
[SPECIES_HYPNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hypno,
[SPECIES_KRABBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Krabby,
[SPECIES_KINGLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kingler,
[SPECIES_VOLTORB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Voltorb,
[SPECIES_ELECTRODE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Electrode,
[SPECIES_EXEGGCUTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Exeggcute,
[SPECIES_EXEGGUTOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Exeggutor,
[SPECIES_CUBONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cubone,
[SPECIES_MAROWAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Marowak,
[SPECIES_HITMONLEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hitmonlee,
[SPECIES_HITMONCHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hitmonchan,
[SPECIES_LICKITUNG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lickitung,
[SPECIES_KOFFING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Koffing,
[SPECIES_WEEZING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Weezing,
[SPECIES_RHYHORN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rhyhorn,
[SPECIES_RHYDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rhydon,
[SPECIES_CHANSEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chansey,
[SPECIES_TANGELA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tangela,
[SPECIES_KANGASKHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kangaskhan,
[SPECIES_HORSEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Horsea,
[SPECIES_SEADRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seadra,
[SPECIES_GOLDEEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Goldeen,
[SPECIES_SEAKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seaking,
[SPECIES_STARYU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Staryu,
[SPECIES_STARMIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Starmie,
[SPECIES_MR_MIME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MrMime,
[SPECIES_SCYTHER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scyther,
[SPECIES_JYNX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jynx,
[SPECIES_ELECTABUZZ] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Electabuzz,
[SPECIES_MAGMAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magmar,
[SPECIES_PINSIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pinsir,
[SPECIES_TAUROS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tauros,
[SPECIES_MAGIKARP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magikarp,
[SPECIES_GYARADOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gyarados,
[SPECIES_LAPRAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lapras,
[SPECIES_DITTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ditto,
[SPECIES_EEVEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eevee,
[SPECIES_VAPOREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vaporeon,
[SPECIES_JOLTEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jolteon,
[SPECIES_FLAREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Flareon,
[SPECIES_PORYGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Porygon,
[SPECIES_OMANYTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Omanyte,
[SPECIES_OMASTAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Omastar,
[SPECIES_KABUTO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kabuto,
[SPECIES_KABUTOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kabutops,
[SPECIES_AERODACTYL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aerodactyl,
[SPECIES_SNORLAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snorlax,
[SPECIES_ARTICUNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Articuno,
[SPECIES_ZAPDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zapdos,
[SPECIES_MOLTRES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Moltres,
[SPECIES_DRATINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dratini,
[SPECIES_DRAGONAIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dragonair,
[SPECIES_DRAGONITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dragonite,
[SPECIES_MEWTWO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mewtwo,
[SPECIES_MEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mew,
[SPECIES_CHIKORITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chikorita,
[SPECIES_BAYLEEF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bayleef,
[SPECIES_MEGANIUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meganium,
[SPECIES_CYNDAQUIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cyndaquil,
[SPECIES_QUILAVA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Quilava,
[SPECIES_TYPHLOSION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Typhlosion,
[SPECIES_TOTODILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Totodile,
[SPECIES_CROCONAW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Croconaw,
[SPECIES_FERALIGATOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Feraligatr,
[SPECIES_SENTRET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sentret,
[SPECIES_FURRET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Furret,
[SPECIES_HOOTHOOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hoothoot,
[SPECIES_NOCTOWL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Noctowl,
[SPECIES_LEDYBA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ledyba,
[SPECIES_LEDIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ledian,
[SPECIES_SPINARAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spinarak,
[SPECIES_ARIADOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ariados,
[SPECIES_CROBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Crobat,
[SPECIES_CHINCHOU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chinchou,
[SPECIES_LANTURN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lanturn,
[SPECIES_PICHU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pichu,
[SPECIES_CLEFFA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cleffa,
[SPECIES_IGGLYBUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Igglybuff,
[SPECIES_TOGEPI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Togepi,
[SPECIES_TOGETIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Togetic,
[SPECIES_NATU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Natu,
[SPECIES_XATU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Xatu,
[SPECIES_MAREEP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mareep,
[SPECIES_FLAAFFY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Flaaffy,
[SPECIES_AMPHAROS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ampharos,
[SPECIES_BELLOSSOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bellossom,
[SPECIES_MARILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Marill,
[SPECIES_AZUMARILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Azumarill,
[SPECIES_SUDOWOODO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sudowoodo,
[SPECIES_POLITOED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Politoed,
[SPECIES_HOPPIP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hoppip,
[SPECIES_SKIPLOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skiploom,
[SPECIES_JUMPLUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jumpluff,
[SPECIES_AIPOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aipom,
[SPECIES_SUNKERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sunkern,
[SPECIES_SUNFLORA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sunflora,
[SPECIES_YANMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yanma,
[SPECIES_WOOPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wooper,
[SPECIES_QUAGSIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Quagsire,
[SPECIES_ESPEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Espeon,
[SPECIES_UMBREON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Umbreon,
[SPECIES_MURKROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Murkrow,
[SPECIES_SLOWKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slowking,
[SPECIES_MISDREAVUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Misdreavus,
[SPECIES_UNOWN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Unown,
[SPECIES_WOBBUFFET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wobbuffet,
[SPECIES_GIRAFARIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Girafarig,
[SPECIES_PINECO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pineco,
[SPECIES_FORRETRESS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Forretress,
[SPECIES_DUNSPARCE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dunsparce,
[SPECIES_GLIGAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gligar,
[SPECIES_STEELIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Steelix,
[SPECIES_SNUBBULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snubbull,
[SPECIES_GRANBULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Granbull,
[SPECIES_QWILFISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Qwilfish,
[SPECIES_SCIZOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scizor,
[SPECIES_SHUCKLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shuckle,
[SPECIES_HERACROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Heracross,
[SPECIES_SNEASEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sneasel,
[SPECIES_TEDDIURSA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Teddiursa,
[SPECIES_URSARING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ursaring,
[SPECIES_SLUGMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slugma,
[SPECIES_MAGCARGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magcargo,
[SPECIES_SWINUB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swinub,
[SPECIES_PILOSWINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Piloswine,
[SPECIES_CORSOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Corsola,
[SPECIES_REMORAID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Remoraid,
[SPECIES_OCTILLERY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Octillery,
[SPECIES_DELIBIRD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Delibird,
[SPECIES_MANTINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mantine,
[SPECIES_SKARMORY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skarmory,
[SPECIES_HOUNDOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Houndour,
[SPECIES_HOUNDOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Houndoom,
[SPECIES_KINGDRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kingdra,
[SPECIES_PHANPY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Phanpy,
[SPECIES_DONPHAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Donphan,
[SPECIES_PORYGON2] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Porygon2,
[SPECIES_STANTLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stantler,
[SPECIES_SMEARGLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Smeargle,
[SPECIES_TYROGUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tyrogue,
[SPECIES_HITMONTOP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hitmontop,
[SPECIES_SMOOCHUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Smoochum,
[SPECIES_ELEKID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Elekid,
[SPECIES_MAGBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magby,
[SPECIES_MILTANK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Miltank,
[SPECIES_BLISSEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Blissey,
[SPECIES_RAIKOU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Raikou,
[SPECIES_ENTEI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Entei,
[SPECIES_SUICUNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Suicune,
[SPECIES_LARVITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Larvitar,
[SPECIES_PUPITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pupitar,
[SPECIES_TYRANITAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tyranitar,
[SPECIES_LUGIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lugia,
[SPECIES_HO_OH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //HoOh,
[SPECIES_CELEBI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Celebi,
    
[SPECIES_TREECKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Treecko,
[SPECIES_GROVYLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grovyle,
[SPECIES_SCEPTILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sceptile,
[SPECIES_TORCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Torchic,
[SPECIES_COMBUSKEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Combusken,
[SPECIES_BLAZIKEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Blaziken,
[SPECIES_MUDKIP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mudkip,
[SPECIES_MARSHTOMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Marshtomp,
[SPECIES_SWAMPERT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swampert,
[SPECIES_POOCHYENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Poochyena,
[SPECIES_MIGHTYENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mightyena,
[SPECIES_ZIGZAGOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zigzagoon,
[SPECIES_LINOONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Linoone,
[SPECIES_WURMPLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wurmple,
[SPECIES_SILCOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silcoon,
[SPECIES_BEAUTIFLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Beautifly,
[SPECIES_CASCOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cascoon,
[SPECIES_DUSTOX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dustox,
[SPECIES_LOTAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lotad,
[SPECIES_LOMBRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lombre,
[SPECIES_LUDICOLO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ludicolo,
[SPECIES_SEEDOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seedot,
[SPECIES_NUZLEAF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nuzleaf,
[SPECIES_SHIFTRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shiftry,
[SPECIES_NINCADA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nincada,
[SPECIES_NINJASK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ninjask,
[SPECIES_SHEDINJA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shedinja,
[SPECIES_TAILLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Taillow,
[SPECIES_SWELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swellow,
[SPECIES_SHROOMISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shroomish,
[SPECIES_BRELOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Breloom,
[SPECIES_SPINDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spinda,
[SPECIES_WINGULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wingull,
[SPECIES_PELIPPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pelipper,
[SPECIES_SURSKIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Surskit,
[SPECIES_MASQUERAIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Masquerain,
[SPECIES_WAILMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wailmer,
[SPECIES_WAILORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wailord,
[SPECIES_SKITTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skitty,
[SPECIES_DELCATTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Delcatty,
[SPECIES_KECLEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kecleon,
[SPECIES_BALTOY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Baltoy,
[SPECIES_CLAYDOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Claydol,
[SPECIES_NOSEPASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nosepass,
[SPECIES_TORKOAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Torkoal,
[SPECIES_SABLEYE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sableye,
[SPECIES_BARBOACH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Barboach,
[SPECIES_WHISCASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Whiscash,
[SPECIES_LUVDISC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Luvdisc,
[SPECIES_CORPHISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Corphish,
[SPECIES_CRAWDAUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Crawdaunt,
[SPECIES_FEEBAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Feebas,
[SPECIES_MILOTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Milotic,
[SPECIES_CARVANHA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Carvanha,
[SPECIES_SHARPEDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sharpedo,
[SPECIES_TRAPINCH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Trapinch,
[SPECIES_VIBRAVA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vibrava,
[SPECIES_FLYGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Flygon,
[SPECIES_MAKUHITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Makuhita,
[SPECIES_HARIYAMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hariyama,
[SPECIES_ELECTRIKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Electrike,
[SPECIES_MANECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Manectric,
[SPECIES_NUMEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Numel,
[SPECIES_CAMERUPT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Camerupt,
[SPECIES_SPHEAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spheal,
[SPECIES_SEALEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sealeo,
[SPECIES_WALREIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Walrein,
[SPECIES_CACNEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cacnea,
[SPECIES_CACTURNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cacturne,
[SPECIES_SNORUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snorunt,
[SPECIES_GLALIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Glalie,
[SPECIES_LUNATONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lunatone,
[SPECIES_SOLROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Solrock,
[SPECIES_AZURILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Azurill,
[SPECIES_SPOINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spoink,
[SPECIES_GRUMPIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grumpig,
[SPECIES_PLUSLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Plusle,
[SPECIES_MINUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minun,
[SPECIES_MAWILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mawile,
[SPECIES_MEDITITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meditite,
[SPECIES_MEDICHAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Medicham,
[SPECIES_SWABLU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swablu,
[SPECIES_ALTARIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Altaria,
[SPECIES_WYNAUT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wynaut,
[SPECIES_DUSKULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Duskull,
[SPECIES_DUSCLOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dusclops,
[SPECIES_ROSELIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Roselia,
[SPECIES_SLAKOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slakoth,
[SPECIES_VIGOROTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vigoroth,
[SPECIES_SLAKING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slaking,
[SPECIES_GULPIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gulpin,
[SPECIES_SWALOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swalot,
[SPECIES_TROPIUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tropius,
[SPECIES_WHISMUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Whismur,
[SPECIES_LOUDRED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Loudred,
[SPECIES_EXPLOUD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Exploud,
[SPECIES_CLAMPERL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clamperl,
[SPECIES_HUNTAIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Huntail,
[SPECIES_GOREBYSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gorebyss,
[SPECIES_ABSOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Absol,
[SPECIES_SHUPPET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shuppet,
[SPECIES_BANETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Banette,
[SPECIES_SEVIPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seviper,
[SPECIES_ZANGOOSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zangoose,
[SPECIES_RELICANTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Relicanth,
[SPECIES_ARON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aron,
[SPECIES_LAIRON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lairon,
[SPECIES_AGGRON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aggron,
[SPECIES_CASTFORM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Castform,
[SPECIES_VOLBEAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Volbeat,
[SPECIES_ILLUMISE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Illumise,
[SPECIES_LILEEP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lileep,
[SPECIES_CRADILY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cradily,
[SPECIES_ANORITH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Anorith,
[SPECIES_ARMALDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Armaldo,
[SPECIES_RALTS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ralts,
[SPECIES_KIRLIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kirlia,
[SPECIES_GARDEVOIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gardevoir,
[SPECIES_BAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bagon,
[SPECIES_SHELGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shelgon,
[SPECIES_SALAMENCE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Salamence,
[SPECIES_BELDUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Beldum,
[SPECIES_METANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Metang,
[SPECIES_METAGROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Metagross,
[SPECIES_REGIROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Regirock,
[SPECIES_REGICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Regice,
[SPECIES_REGISTEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Registeel,
[SPECIES_KYOGRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kyogre,
[SPECIES_GROUDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Groudon,
[SPECIES_RAYQUAZA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rayquaza,
[SPECIES_LATIAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Latias,
[SPECIES_LATIOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Latios,
[SPECIES_JIRACHI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jirachi,
[SPECIES_DEOXYS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Deoxys,
[SPECIES_CHIMECHO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chimecho,
[SPECIES_EGG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Egg,
[SPECIES_UNOWN_B] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownB,
[SPECIES_UNOWN_C] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownC,
[SPECIES_UNOWN_D] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownD,
[SPECIES_UNOWN_E] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownE,
[SPECIES_UNOWN_F] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownF,
[SPECIES_UNOWN_G] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownG,
[SPECIES_UNOWN_H] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownH,
[SPECIES_UNOWN_I] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownI,
[SPECIES_UNOWN_J] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownJ,
[SPECIES_UNOWN_K] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownK,
[SPECIES_UNOWN_L] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownL,
[SPECIES_UNOWN_M] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownM,
[SPECIES_UNOWN_N] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownN,
[SPECIES_UNOWN_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownO,
[SPECIES_UNOWN_P] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownP,
[SPECIES_UNOWN_Q] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownQ,
[SPECIES_UNOWN_R] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownR,
[SPECIES_UNOWN_S] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownS,
[SPECIES_UNOWN_T] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownT,
[SPECIES_UNOWN_U] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownU,
[SPECIES_UNOWN_V] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownV,
[SPECIES_UNOWN_W] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownW,
[SPECIES_UNOWN_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownX,
[SPECIES_UNOWN_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownY,
[SPECIES_UNOWN_Z] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownZ,
[SPECIES_UNOWN_EMARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownExclamationMark,
[SPECIES_UNOWN_QMARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //UnownQuestionMark, //ok I see now part of problem, this doeesn't have a comma and others are misaligned.
[SPECIES_TURTWIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Turtwig,
[SPECIES_GROTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grotle,
[SPECIES_TORTERRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Torterra,
[SPECIES_CHIMCHAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chimchar,
[SPECIES_MONFERNO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Monferno,
[SPECIES_INFERNAPE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Infernape,
[SPECIES_PIPLUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Piplup,
[SPECIES_PRINPLUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Prinplup,
[SPECIES_EMPOLEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Empoleon,
[SPECIES_STARLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Starly,
[SPECIES_STARAVIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Staravia,
[SPECIES_STARAPTOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Staraptor,
[SPECIES_BIDOOF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bidoof,
[SPECIES_BIBAREL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bibarel,
[SPECIES_KRICKETOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kricketot,
[SPECIES_KRICKETUNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kricketune,
[SPECIES_SHINX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shinx,
[SPECIES_LUXIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Luxio,
[SPECIES_LUXRAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Luxray,
[SPECIES_BUDEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Budew,
[SPECIES_ROSERADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Roserade,
[SPECIES_CRANIDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cranidos,
[SPECIES_RAMPARDOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rampardos,
[SPECIES_SHIELDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shieldon,
[SPECIES_BASTIODON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bastiodon,
[SPECIES_BURMY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Burmy,
[SPECIES_WORMADAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wormadam,
[SPECIES_MOTHIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mothim,
[SPECIES_COMBEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Combee,
[SPECIES_VESPIQUEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vespiquen,
[SPECIES_PACHIRISU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pachirisu,
[SPECIES_BUIZEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Buizel,
[SPECIES_FLOATZEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Floatzel,
[SPECIES_CHERUBI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cherubi,
[SPECIES_CHERRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cherrim,
[SPECIES_SHELLOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shellos,
[SPECIES_GASTRODON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gastrodon,
[SPECIES_AMBIPOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ambipom,
[SPECIES_DRIFLOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drifloon,
[SPECIES_DRIFBLIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drifblim,
[SPECIES_BUNEARY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Buneary,
[SPECIES_LOPUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lopunny,
[SPECIES_MISMAGIUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mismagius,
[SPECIES_HONCHKROW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Honchkrow,
[SPECIES_GLAMEOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Glameow,
[SPECIES_PURUGLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Purugly,
[SPECIES_CHINGLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chingling,
[SPECIES_STUNKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stunky,
[SPECIES_SKUNTANK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skuntank,
[SPECIES_BRONZOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bronzor,
[SPECIES_BRONZONG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bronzong,
[SPECIES_BONSLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bonsly,
[SPECIES_MIME_JR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MimeJr,
[SPECIES_HAPPINY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Happiny,
[SPECIES_CHATOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chatot,
[SPECIES_SPIRITOMB] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spiritomb,
[SPECIES_GIBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gible,
[SPECIES_GABITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gabite,
[SPECIES_GARCHOMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Garchomp,
[SPECIES_MUNCHLAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Munchlax,
[SPECIES_RIOLU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Riolu,
[SPECIES_LUCARIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lucario,
[SPECIES_HIPPOPOTAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hippopotas,
[SPECIES_HIPPOWDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hippowdon,
[SPECIES_SKORUPI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skorupi,
[SPECIES_DRAPION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drapion,
[SPECIES_CROAGUNK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Croagunk,
[SPECIES_TOXICROAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toxicroak,
[SPECIES_CARNIVINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Carnivine,
[SPECIES_FINNEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Finneon,
[SPECIES_LUMINEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lumineon,
[SPECIES_MANTYKE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mantyke,
[SPECIES_SNOVER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snover,
[SPECIES_ABOMASNOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Abomasnow,
[SPECIES_WEAVILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Weavile,
[SPECIES_MAGNEZONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magnezone,
[SPECIES_LICKILICKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lickilicky,
[SPECIES_RHYPERIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rhyperior,
[SPECIES_TANGROWTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tangrowth,
[SPECIES_ELECTIVIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Electivire,
[SPECIES_MAGMORTAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magmortar,
[SPECIES_TOGEKISS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Togekiss,
[SPECIES_YANMEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yanmega,
[SPECIES_LEAFEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Leafeon,
[SPECIES_GLACEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Glaceon,
[SPECIES_GLISCOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gliscor,
[SPECIES_MAMOSWINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mamoswine,
[SPECIES_PORYGON_Z] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Porygon_Z,
[SPECIES_GALLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gallade,
[SPECIES_PROBOPASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Probopass,
[SPECIES_DUSKNOIR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dusknoir,
[SPECIES_FROSLASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Froslass,
[SPECIES_ROTOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rotom,
[SPECIES_UXIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Uxie,
[SPECIES_MESPRIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mesprit,
[SPECIES_AZELF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Azelf,
[SPECIES_DIALGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dialga,
[SPECIES_PALKIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Palkia,
[SPECIES_HEATRAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Heatran,
[SPECIES_REGIGIGAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Regigigas,
[SPECIES_GIRATINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Giratina,
[SPECIES_CRESSELIA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cresselia,
[SPECIES_PHIONE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Phione,
[SPECIES_MANAPHY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Manaphy,
[SPECIES_DARKRAI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Darkrai,
[SPECIES_SHAYMIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shaymin,
[SPECIES_ARCEUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
[SPECIES_VICTINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Victini,
[SPECIES_SNIVY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snivy,
[SPECIES_SERVINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Servine,
[SPECIES_SERPERIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Serperior,
[SPECIES_TEPIG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tepig,
[SPECIES_PIGNITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pignite,
[SPECIES_EMBOAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Emboar,
[SPECIES_OSHAWOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Oshawott,
[SPECIES_DEWOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dewott,
[SPECIES_SAMUROTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Samurott,
[SPECIES_PATRAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Patrat,
[SPECIES_WATCHOG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Watchog,
[SPECIES_LILLIPUP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lillipup,
[SPECIES_HERDIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Herdier,
[SPECIES_STOUTLAND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stoutland,
[SPECIES_PURRLOIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Purrloin,
[SPECIES_LIEPARD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Liepard,
[SPECIES_PANSAGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pansage,
[SPECIES_SIMISAGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Simisage,
[SPECIES_PANSEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pansear,
[SPECIES_SIMISEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Simisear,
[SPECIES_PANPOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Panpour,
[SPECIES_SIMIPOUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Simipour,
[SPECIES_MUNNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Munna,
[SPECIES_MUSHARNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Musharna,
[SPECIES_PIDOVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pidove,
[SPECIES_TRANQUILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tranquill,
[SPECIES_UNFEZANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Unfezant,
[SPECIES_BLITZLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Blitzle,
[SPECIES_ZEBSTRIKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zebstrika,
[SPECIES_ROGGENROLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Roggenrola,
[SPECIES_BOLDORE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Boldore,
[SPECIES_GIGALITH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gigalith,
[SPECIES_WOOBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Woobat,
[SPECIES_SWOOBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swoobat,
[SPECIES_DRILBUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drilbur,
[SPECIES_EXCADRILL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Excadrill,
[SPECIES_AUDINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Audino,
[SPECIES_TIMBURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Timburr,
[SPECIES_GURDURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gurdurr,
[SPECIES_CONKELDURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Conkeldurr,
[SPECIES_TYMPOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tympole,
[SPECIES_PALPITOAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Palpitoad,
[SPECIES_SEISMITOAD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Seismitoad,
[SPECIES_THROH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Throh,
[SPECIES_SAWK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sawk,
[SPECIES_SEWADDLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sewaddle,
[SPECIES_SWADLOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swadloon,
[SPECIES_LEAVANNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Leavanny,
[SPECIES_VENIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Venipede,
[SPECIES_WHIRLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Whirlipede,
[SPECIES_SCOLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scolipede,
[SPECIES_COTTONEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cottonee,
[SPECIES_WHIMSICOTT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Whimsicott,
[SPECIES_PETILIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Petilil,
[SPECIES_LILLIGANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lilligant,
[SPECIES_BASCULIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Basculin,
[SPECIES_SANDILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sandile,
[SPECIES_KROKOROK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Krokorok,
[SPECIES_KROOKODILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Krookodile,
[SPECIES_DARUMAKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Darumaka,
[SPECIES_DARMANITAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Darmanitan,
[SPECIES_MARACTUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Maractus,
[SPECIES_DWEBBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dwebble,
[SPECIES_CRUSTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Crustle,
[SPECIES_SCRAGGY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scraggy,
[SPECIES_SCRAFTY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scrafty,
[SPECIES_SIGILYPH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sigilyph,
[SPECIES_YAMASK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yamask,
[SPECIES_COFAGRIGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cofagrigus,
[SPECIES_TIRTOUGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tirtouga,
[SPECIES_CARRACOSTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Carracosta,
[SPECIES_ARCHEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Archen,
[SPECIES_ARCHEOPS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Archeops,
[SPECIES_TRUBBISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Trubbish,
[SPECIES_GARBODOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Garbodor,
[SPECIES_ZORUA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zorua,
[SPECIES_ZOROARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zoroark,
[SPECIES_MINCCINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minccino,
[SPECIES_CINCCINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cinccino,
[SPECIES_GOTHITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gothita,
[SPECIES_GOTHORITA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gothorita,
[SPECIES_GOTHITELLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gothitelle,
[SPECIES_SOLOSIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Solosis,
[SPECIES_DUOSION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Duosion,
[SPECIES_REUNICLUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Reuniclus,
[SPECIES_DUCKLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ducklett,
[SPECIES_SWANNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swanna,
[SPECIES_VANILLITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vanillite,
[SPECIES_VANILLISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vanillish,
[SPECIES_VANILLUXE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vanilluxe,
[SPECIES_DEERLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Deerling,
[SPECIES_SAWSBUCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sawsbuck,
[SPECIES_EMOLGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Emolga,
[SPECIES_KARRABLAST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Karrablast,
[SPECIES_ESCAVALIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Escavalier,
[SPECIES_FOONGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Foongus,
[SPECIES_AMOONGUSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Amoonguss,
[SPECIES_FRILLISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Frillish,
[SPECIES_JELLICENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jellicent,
[SPECIES_ALOMOMOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alomomola,
[SPECIES_JOLTIK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Joltik,
[SPECIES_GALVANTULA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Galvantula,
[SPECIES_FERROSEED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ferroseed,
[SPECIES_FERROTHORN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ferrothorn,
[SPECIES_KLINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Klink,
[SPECIES_KLANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Klang,
[SPECIES_KLINKLANG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Klinklang,
[SPECIES_TYNAMO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tynamo,
[SPECIES_EELEKTRIK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eelektrik,
[SPECIES_EELEKTROSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eelektross,
[SPECIES_ELGYEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Elgyem,
[SPECIES_BEHEEYEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Beheeyem,
[SPECIES_LITWICK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Litwick,
[SPECIES_LAMPENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lampent,
[SPECIES_CHANDELURE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chandelure,
[SPECIES_AXEW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Axew,
[SPECIES_FRAXURE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fraxure,
[SPECIES_HAXORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Haxorus,
[SPECIES_CUBCHOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cubchoo,
[SPECIES_BEARTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Beartic,
[SPECIES_CRYOGONAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cryogonal,
[SPECIES_SHELMET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shelmet,
[SPECIES_ACCELGOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Accelgor,
[SPECIES_STUNFISK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stunfisk,
[SPECIES_MIENFOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mienfoo,
[SPECIES_MIENSHAO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mienshao,
[SPECIES_DRUDDIGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Druddigon,
[SPECIES_GOLETT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golett,
[SPECIES_GOLURK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golurk,
[SPECIES_PAWNIARD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pawniard,
[SPECIES_BISHARP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bisharp,
[SPECIES_BOUFFALANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bouffalant,
[SPECIES_RUFFLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rufflet,
[SPECIES_BRAVIARY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Braviary,
[SPECIES_VULLABY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vullaby,
[SPECIES_MANDIBUZZ] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mandibuzz,
[SPECIES_HEATMOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Heatmor,
[SPECIES_DURANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Durant,
[SPECIES_DEINO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Deino,
[SPECIES_ZWEILOUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zweilous,
[SPECIES_HYDREIGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hydreigon,
[SPECIES_LARVESTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Larvesta,
[SPECIES_VOLCARONA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Volcarona,
[SPECIES_COBALION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cobalion,
[SPECIES_TERRAKION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Terrakion,
[SPECIES_VIRIZION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Virizion,
[SPECIES_TORNADUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tornadus,
[SPECIES_THUNDURUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Thundurus,
[SPECIES_RESHIRAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Reshiram,
[SPECIES_ZEKROM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zekrom,
[SPECIES_LANDORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Landorus,
[SPECIES_KYUREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kyurem,
[SPECIES_KELDEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Keldeo,
[SPECIES_MELOETTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meloetta,
[SPECIES_GENESECT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Genesect,
[SPECIES_CHESPIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chespin,
[SPECIES_QUILLADIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Quilladin,
[SPECIES_CHESNAUGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chesnaught,
[SPECIES_FENNEKIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fennekin,
[SPECIES_BRAIXEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Braixen,
[SPECIES_DELPHOX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Delphox,
[SPECIES_FROAKIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Froakie,
[SPECIES_FROGADIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Frogadier,
[SPECIES_GRENINJA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Greninja,
[SPECIES_BUNNELBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bunnelby,
[SPECIES_DIGGERSBY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Diggersby,
[SPECIES_FLETCHLING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fletchling,
[SPECIES_FLETCHINDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fletchinder,
[SPECIES_TALONFLAME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Talonflame,
[SPECIES_SCATTERBUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scatterbug,
[SPECIES_SPEWPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spewpa,
[SPECIES_VIVILLON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vivillon,
[SPECIES_LITLEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Litleo,
[SPECIES_PYROAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pyroar,
[SPECIES_FLABEBE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Flabebe,
[SPECIES_FLOETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Floette,
[SPECIES_FLORGES] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Florges,
[SPECIES_SKIDDO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skiddo,
[SPECIES_GOGOAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gogoat,
[SPECIES_PANCHAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pancham,
[SPECIES_PANGORO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pangoro,
[SPECIES_FURFROU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Furfrou,
[SPECIES_ESPURR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Espurr,
[SPECIES_MEOWSTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meowstic,
[SPECIES_HONEDGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Honedge,
[SPECIES_DOUBLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Doublade,
[SPECIES_AEGISLASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aegislash,
[SPECIES_SPRITZEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spritzee,
[SPECIES_AROMATISSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aromatisse,
[SPECIES_SWIRLIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Swirlix,
[SPECIES_SLURPUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Slurpuff,
[SPECIES_INKAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Inkay,
[SPECIES_MALAMAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Malamar,
[SPECIES_BINACLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Binacle,
[SPECIES_BARBARACLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Barbaracle,
[SPECIES_SKRELP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skrelp,
[SPECIES_DRAGALGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dragalge,
[SPECIES_CLAUNCHER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clauncher,
[SPECIES_CLAWITZER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clawitzer,
[SPECIES_HELIOPTILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Helioptile,
[SPECIES_HELIOLISK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Heliolisk,
[SPECIES_TYRUNT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tyrunt,
[SPECIES_TYRANTRUM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tyrantrum,
[SPECIES_AMAURA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Amaura,
[SPECIES_AURORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Aurorus,
[SPECIES_SYLVEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sylveon,
[SPECIES_HAWLUCHA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hawlucha,
[SPECIES_DEDENNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dedenne,
[SPECIES_CARBINK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Carbink,
[SPECIES_GOOMY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Goomy,
[SPECIES_SLIGGOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sliggoo,
[SPECIES_GOODRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Goodra,
[SPECIES_KLEFKI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Klefki,
[SPECIES_PHANTUMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Phantump,
[SPECIES_TREVENANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Trevenant,
[SPECIES_PUMPKABOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pumpkaboo,
[SPECIES_GOURGEIST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gourgeist,
[SPECIES_BERGMITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bergmite,
[SPECIES_AVALUGG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Avalugg,
[SPECIES_NOIBAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Noibat,
[SPECIES_NOIVERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Noivern,
[SPECIES_XERNEAS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Xerneas,
[SPECIES_YVELTAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yveltal,
[SPECIES_ZYGARDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zygarde,
[SPECIES_DIANCIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Diancie,
[SPECIES_HOOPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hoopa,
[SPECIES_VOLCANION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Volcanion,
[SPECIES_ROWLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rowlet,
[SPECIES_DARTRIX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dartrix,
[SPECIES_DECIDUEYE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Decidueye,
[SPECIES_LITTEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Litten,
[SPECIES_TORRACAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Torracat,
[SPECIES_INCINEROAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Incineroar,
[SPECIES_POPPLIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Popplio,
[SPECIES_BRIONNE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Brionne,
[SPECIES_PRIMARINA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Primarina,
[SPECIES_PIKIPEK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pikipek,
[SPECIES_TRUMBEAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Trumbeak,
[SPECIES_TOUCANNON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toucannon,
[SPECIES_YUNGOOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yungoos,
[SPECIES_GUMSHOOS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gumshoos,
[SPECIES_GRUBBIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grubbin,
[SPECIES_CHARJABUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Charjabug,
[SPECIES_VIKAVOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Vikavolt,
[SPECIES_CRABRAWLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Crabrawler,
[SPECIES_CRABOMINABLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Crabominable,
[SPECIES_ORICORIO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Oricorio,
[SPECIES_CUTIEFLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cutiefly,
[SPECIES_RIBOMBEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ribombee,
[SPECIES_ROCKRUFF] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rockruff,
[SPECIES_LYCANROC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lycanroc,
[SPECIES_WISHIWASHI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wishiwashi,
[SPECIES_MAREANIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mareanie,
[SPECIES_TOXAPEX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toxapex,
[SPECIES_MUDBRAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mudbray,
[SPECIES_MUDSDALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mudsdale,
[SPECIES_DEWPIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dewpider,
[SPECIES_ARAQUANID] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Araquanid,
[SPECIES_FOMANTIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Fomantis,
[SPECIES_LURANTIS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lurantis,
[SPECIES_MORELULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Morelull,
[SPECIES_SHIINOTIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Shiinotic,
[SPECIES_SALANDIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Salandit,
[SPECIES_SALAZZLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Salazzle,
[SPECIES_STUFFUL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stufful,
[SPECIES_BEWEAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bewear,
[SPECIES_BOUNSWEET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bounsweet,
[SPECIES_STEENEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Steenee,
[SPECIES_TSAREENA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Tsareena,
[SPECIES_COMFEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Comfey,
[SPECIES_ORANGURU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Oranguru,
[SPECIES_PASSIMIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Passimian,
[SPECIES_WIMPOD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wimpod,
[SPECIES_GOLISOPOD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Golisopod,
[SPECIES_SANDYGAST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sandygast,
[SPECIES_PALOSSAND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Palossand,
[SPECIES_PYUKUMUKU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pyukumuku,
[SPECIES_TYPE_NULL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TypeNull,
[SPECIES_SILVALLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
[SPECIES_MINIOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
[SPECIES_KOMALA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Komala,
[SPECIES_TURTONATOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Turtonator,
[SPECIES_TOGEDEMARU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Togedemaru,
[SPECIES_MIMIKYU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Mimikyu,
[SPECIES_BRUXISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Bruxish,
[SPECIES_DRAMPA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drampa,
[SPECIES_DHELMISE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dhelmise,
[SPECIES_JANGMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Jangmoo,
[SPECIES_HAKAMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hakamoo,
[SPECIES_KOMMO_O] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kommoo,
[SPECIES_TAPU_KOKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TapuKoko,
[SPECIES_TAPU_LELE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TapuLele,
[SPECIES_TAPU_BULU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TapuBulu,
[SPECIES_TAPU_FINI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TapuFini,
[SPECIES_COSMOG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cosmog,
[SPECIES_COSMOEM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cosmoem,
[SPECIES_SOLGALEO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Solgaleo,
[SPECIES_LUNALA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Lunala,
[SPECIES_NIHILEGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nihilego,
[SPECIES_BUZZWOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Buzzwole,
[SPECIES_PHEROMOSA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pheromosa,
[SPECIES_XURKITREE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Xurkitree,
[SPECIES_CELESTEELA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Celesteela,
[SPECIES_KARTANA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kartana,
[SPECIES_GUZZLORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Guzzlord,
[SPECIES_NECROZMA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Necrozma,
[SPECIES_MAGEARNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Magearna,
[SPECIES_MARSHADOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Marshadow,
[SPECIES_POIPOLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Poipole,
[SPECIES_NAGANADEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Naganadel,
[SPECIES_STAKATAKA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stakataka,
[SPECIES_BLACEPHALON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Blacephalon,
[SPECIES_ZERAORA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zeraora,
[SPECIES_MELTAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Meltan,
[SPECIES_MELMETAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Melmetal,
[SPECIES_GROOKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grookey,
[SPECIES_THWACKEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Thwackey,
[SPECIES_RILLABOOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rillaboom,
[SPECIES_SCORBUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Scorbunny,
[SPECIES_RABOOT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Raboot,
[SPECIES_CINDERACE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cinderace,
[SPECIES_SOBBLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sobble,
[SPECIES_DRIZZILE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drizzile,
[SPECIES_INTELEON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Inteleon,
[SPECIES_SKWOVET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Skwovet,
[SPECIES_GREEDENT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Greedent,
[SPECIES_ROOKIDEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rookidee,
[SPECIES_CORVISQUIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Corvisquire,
[SPECIES_CORVIKNIGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Corviknight,
[SPECIES_BLIPBUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Blipbug,
[SPECIES_DOTTLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dottler,
[SPECIES_ORBEETLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Orbeetle,
[SPECIES_NICKIT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Nickit,
[SPECIES_THIEVUL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Thievul,
[SPECIES_GOSSIFLEUR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gossifleur,
[SPECIES_ELDEGOSS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eldegoss,
[SPECIES_WOOLOO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wooloo,
[SPECIES_DUBWOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dubwool,
[SPECIES_CHEWTLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Chewtle,
[SPECIES_DREDNAW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drednaw,
[SPECIES_YAMPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Yamper,
[SPECIES_BOLTUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Boltund,
[SPECIES_ROLYCOLY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Rolycoly,
[SPECIES_CARKOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Carkol,
[SPECIES_COALOSSAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Coalossal,
[SPECIES_APPLIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Applin,
[SPECIES_FLAPPLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Flapple,
[SPECIES_APPLETUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Appletun,
[SPECIES_SILICOBRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silicobra,
[SPECIES_SANDACONDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sandaconda,
[SPECIES_CRAMORANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cramorant,
[SPECIES_ARROKUDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arrokuda,
[SPECIES_BARRASKEWDA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Barraskewda,
[SPECIES_TOXEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toxel,
[SPECIES_TOXTRICITY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toxtricity,
[SPECIES_SIZZLIPEDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sizzlipede,
[SPECIES_CENTISKORCH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Centiskorch,
[SPECIES_CLOBBOPUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Clobbopus,
[SPECIES_GRAPPLOCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grapploct,
[SPECIES_SINISTEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sinistea,
[SPECIES_POLTEAGEIST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Polteageist,
[SPECIES_HATENNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hatenna,
[SPECIES_HATTREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hattrem,
[SPECIES_HATTERENE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Hatterene,
[SPECIES_IMPIDIMP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Impidimp,
[SPECIES_MORGREM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Morgrem,
[SPECIES_GRIMMSNARL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Grimmsnarl,
[SPECIES_OBSTAGOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Obstagoon,
[SPECIES_PERRSERKER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Perrserker,
[SPECIES_CURSOLA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cursola,
[SPECIES_SIRFETCHD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sirfetchd,
[SPECIES_MR_RIME] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MrRime,
[SPECIES_RUNERIGUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Runerigus,
[SPECIES_MILCERY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Milcery,
[SPECIES_ALCREMIE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie,
[SPECIES_FALINKS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Falinks,
[SPECIES_PINCURCHIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pincurchin,
[SPECIES_SNOM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Snom,
[SPECIES_FROSMOTH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Frosmoth,
[SPECIES_STONJOURNER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Stonjourner,
[SPECIES_EISCUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eiscue,
[SPECIES_INDEEDEE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Indeedee,
[SPECIES_MORPEKO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Morpeko,
[SPECIES_CUFANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cufant,
[SPECIES_COPPERAJAH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Copperajah,
[SPECIES_DRACOZOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dracozolt,
[SPECIES_ARCTOZOLT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arctozolt,
[SPECIES_DRACOVISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dracovish,
[SPECIES_ARCTOVISH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arctovish,
[SPECIES_DURALUDON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Duraludon,
[SPECIES_DREEPY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dreepy,
[SPECIES_DRAKLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Drakloak,
[SPECIES_DRAGAPULT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Dragapult,
[SPECIES_ZACIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zacian,
[SPECIES_ZAMAZENTA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zamazenta,
[SPECIES_ETERNATUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eternatus,
[SPECIES_KUBFU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kubfu,
[SPECIES_URSHIFU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Urshifu,
[SPECIES_ZARUDE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zarude,
[SPECIES_REGIELEKI] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Regieleki,
[SPECIES_REGIDRAGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Regidrago,
[SPECIES_GLASTRIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Glastrier,
[SPECIES_SPECTRIER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Spectrier,
[SPECIES_CALYREX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Calyrex,
[SPECIES_WYRDEER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Wyrdeer,
[SPECIES_KLEAVOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Kleavor,
[SPECIES_URSALUNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Ursaluna,
[SPECIES_BASCULEGION] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Basculegion,
[SPECIES_SNEASLER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Sneasler,
[SPECIES_OVERQWIL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Overqwil,
[SPECIES_ENAMORUS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Enamorus,
  [SPECIES_VENUSAUR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VenusaurMega,
  [SPECIES_CHARIZARD_MEGA_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CharizardMegaX,
  [SPECIES_CHARIZARD_MEGA_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CharizardMegaY,
  [SPECIES_BLASTOISE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BlastoiseMega,
  [SPECIES_BEEDRILL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BeedrillMega,
  [SPECIES_PIDGEOT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PidgeotMega,
  [SPECIES_ALAKAZAM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AlakazamMega,
  [SPECIES_SLOWBRO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SlowbroMega,
  [SPECIES_GENGAR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GengarMega,
  [SPECIES_KANGASKHAN_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //KangaskhanMega,
  [SPECIES_PINSIR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PinsirMega,
  [SPECIES_GYARADOS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GyaradosMega,
  [SPECIES_AERODACTYL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AerodactylMega,
  [SPECIES_MEWTWO_MEGA_X] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MewtwoMegaX,
  [SPECIES_MEWTWO_MEGA_Y] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MewtwoMegaY,
  [SPECIES_AMPHAROS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AmpharosMega,
  [SPECIES_STEELIX_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SteelixMega,
  [SPECIES_SCIZOR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ScizorMega,
  [SPECIES_HERACROSS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //HeracrossMega,
  [SPECIES_HOUNDOOM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //HoundoomMega,
  [SPECIES_TYRANITAR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TyranitarMega,
  [SPECIES_SCEPTILE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SceptileMega,
  [SPECIES_BLAZIKEN_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BlazikenMega,
  [SPECIES_SWAMPERT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SwampertMega,
  [SPECIES_GARDEVOIR_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GardevoirMega,
  [SPECIES_SABLEYE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SableyeMega,
  [SPECIES_MAWILE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MawileMega,
  [SPECIES_AGGRON_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AggronMega,
  [SPECIES_MEDICHAM_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MedichamMega,
  [SPECIES_MANECTRIC_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ManectricMega,
  [SPECIES_SHARPEDO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SharpedoMega,
  [SPECIES_CAMERUPT_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CameruptMega,
  [SPECIES_ALTARIA_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AltariaMega,
  [SPECIES_BANETTE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BanetteMega,
  [SPECIES_ABSOL_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AbsolMega,
  [SPECIES_GLALIE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GlalieMega,
  [SPECIES_SALAMENCE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SalamenceMega,
  [SPECIES_METAGROSS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MetagrossMega,
  [SPECIES_LATIAS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LatiasMega,
  [SPECIES_LATIOS_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LatiosMega,
  [SPECIES_LOPUNNY_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LopunnyMega,
  [SPECIES_GARCHOMP_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GarchompMega,
  [SPECIES_LUCARIO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LucarioMega,
  [SPECIES_ABOMASNOW_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AbomasnowMega,
  [SPECIES_GALLADE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GalladeMega,
  [SPECIES_AUDINO_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AudinoMega,
  [SPECIES_DIANCIE_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DiancieMega,
  [SPECIES_RAYQUAZA_MEGA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RayquazaMega,
  [SPECIES_KYOGRE_PRIMAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //KyogrePrimal,
  [SPECIES_GROUDON_PRIMAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GroudonPrimal,
  [SPECIES_RATTATA_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RattataAlolan,
  [SPECIES_RATICATE_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RaticateAlolan,
  [SPECIES_RAICHU_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RaichuAlolan,
  [SPECIES_SANDSHREW_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SandshrewAlolan,
  [SPECIES_SANDSLASH_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SandslashAlolan,
  [SPECIES_VULPIX_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VulpixAlolan,
  [SPECIES_NINETALES_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NinetalesAlolan,
  [SPECIES_DIGLETT_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DiglettAlolan,
  [SPECIES_DUGTRIO_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DugtrioAlolan,
  [SPECIES_MEOWTH_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MeowthAlolan,
  [SPECIES_PERSIAN_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PersianAlolan,
  [SPECIES_GEODUDE_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GeodudeAlolan,
  [SPECIES_GRAVELER_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GravelerAlolan,
  [SPECIES_GOLEM_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GolemAlolan,
  [SPECIES_GRIMER_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GrimerAlolan,
  [SPECIES_MUK_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MukAlolan,
  [SPECIES_EXEGGUTOR_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ExeggutorAlolan,
  [SPECIES_MAROWAK_ALOLAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MarowakAlolan,
  [SPECIES_MEOWTH_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MeowthGalarian,
  [SPECIES_PONYTA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PonytaGalarian,
  [SPECIES_RAPIDASH_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RapidashGalarian,
  [SPECIES_SLOWPOKE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SlowpokeGalarian,
  [SPECIES_SLOWBRO_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SlowbroGalarian,
  [SPECIES_FARFETCHD_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FarfetchdGalarian,
  [SPECIES_WEEZING_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //WeezingGalarian,
  [SPECIES_MR_MIME_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MrMimeGalarian,
  [SPECIES_ARTICUNO_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ArticunoGalarian,
  [SPECIES_ZAPDOS_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ZapdosGalarian,
  [SPECIES_MOLTRES_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MoltresGalarian,
  [SPECIES_SLOWKING_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SlowkingGalarian,
  [SPECIES_CORSOLA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CorsolaGalarian,
  [SPECIES_ZIGZAGOON_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ZigzagoonGalarian,
  [SPECIES_LINOONE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LinooneGalarian,
  [SPECIES_DARUMAKA_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DarumakaGalarian,
  [SPECIES_DARMANITAN_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DarmanitanGalarian,
  [SPECIES_YAMASK_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //YamaskGalarian,
  [SPECIES_STUNFISK_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //StunfiskGalarian,
  [SPECIES_GROWLITHE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GrowlitheHisuian,
  [SPECIES_ARCANINE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ArcanineHisuian,
  [SPECIES_VOLTORB_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VoltorbHisuian,
  [SPECIES_ELECTRODE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ElectrodeHisuian,
  [SPECIES_TYPHLOSION_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TyphlosionHisuian,
  [SPECIES_QWILFISH_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //QwilfishHisuian,
  [SPECIES_SNEASEL_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SneaselHisuian,
  [SPECIES_SAMUROTT_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SamurottHisuian,
  [SPECIES_LILLIGANT_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LilligantHisuian,
  [SPECIES_ZORUA_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ZoruaHisuian,
  [SPECIES_ZOROARK_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ZoroarkHisuian,
  [SPECIES_BRAVIARY_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BraviaryHisuian,
  [SPECIES_SLIGGOO_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SliggooHisuian,
  [SPECIES_GOODRA_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GoodraHisuian,
  [SPECIES_AVALUGG_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AvaluggHisuian,
  [SPECIES_DECIDUEYE_HISUIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DecidueyeHisuian,
  [SPECIES_PIKACHU_COSPLAY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuCosplay,
  [SPECIES_PIKACHU_ROCK_STAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuRockStar,
  [SPECIES_PIKACHU_BELLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuBelle,
  [SPECIES_PIKACHU_POP_STAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuPopStar,
  [SPECIES_PIKACHU_PH_D] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuPhD,
  [SPECIES_PIKACHU_LIBRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuLibre,
  [SPECIES_PIKACHU_ORIGINAL_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuOriginalCap,
  [SPECIES_PIKACHU_HOENN_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuHoennCap,
  [SPECIES_PIKACHU_SINNOH_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuSinnohCap,
  [SPECIES_PIKACHU_UNOVA_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuUnovaCap,
  [SPECIES_PIKACHU_KALOS_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuKalosCap,
  [SPECIES_PIKACHU_ALOLA_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuAlolaCap,
  [SPECIES_PIKACHU_PARTNER_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuPartnerCap,
  [SPECIES_PIKACHU_WORLD_CAP] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PikachuWorldCap,
  [SPECIES_PICHU_SPIKY_EARED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //PichuSpikyEared,
  [SPECIES_CASTFORM_SUNNY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CastformSunny,
  [SPECIES_CASTFORM_RAINY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CastformRainy,
  [SPECIES_CASTFORM_SNOWY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CastformSnowy,
  [SPECIES_DEOXYS_ATTACK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeoxysAttack,
  [SPECIES_DEOXYS_DEFENSE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeoxysDefense,
  [SPECIES_DEOXYS_SPEED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeoxysSpeed,
  [SPECIES_BURMY_SANDY_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BurmySandyCloak,
  [SPECIES_BURMY_TRASH_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BurmyTrashCloak,
  [SPECIES_WORMADAM_SANDY_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //WormadamSandyCloak,
  [SPECIES_WORMADAM_TRASH_CLOAK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //WormadamTrashCloak,
  [SPECIES_CHERRIM_SUNSHINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //CherrimSunshine,
  [SPECIES_SHELLOS_EAST_SEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ShellosEastSea,
  [SPECIES_GASTRODON_EAST_SEA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GastrodonEastSea,
  [SPECIES_ROTOM_HEAT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RotomHeat,
  [SPECIES_ROTOM_WASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RotomWash,
  [SPECIES_ROTOM_FROST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RotomFrost,
  [SPECIES_ROTOM_FAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RotomFan,
  [SPECIES_ROTOM_MOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //RotomMow,
  [SPECIES_GIRATINA_ORIGIN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GiratinaOrigin,
  [SPECIES_SHAYMIN_SKY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ShayminSky,
  [SPECIES_ARCEUS_FIGHTING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_FLYING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_POISON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_GROUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_ROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_BUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_GHOST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_STEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_FIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_WATER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_GRASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_ELECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_PSYCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_ICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_DRAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_DARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_ARCEUS_FAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Arceus,
  [SPECIES_BASCULIN_BLUE_STRIPED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BasculinBlueStriped,
  [SPECIES_BASCULIN_WHITE_STRIPED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //BasculinHisuian,
  [SPECIES_DARMANITAN_ZEN_MODE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DarmanitanZenMode,
  [SPECIES_DARMANITAN_ZEN_MODE_GALARIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DarmanitanZenModeGalarian,
  [SPECIES_DEERLING_SUMMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeerlingSummer,
  [SPECIES_DEERLING_AUTUMN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeerlingAutumn,
  [SPECIES_DEERLING_WINTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //DeerlingWinter,
  [SPECIES_SAWSBUCK_SUMMER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SawsbuckSummer,
  [SPECIES_SAWSBUCK_AUTUMN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SawsbuckAutumn,
  [SPECIES_SAWSBUCK_WINTER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //SawsbuckWinter,
  [SPECIES_TORNADUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //TornadusTherian,
  [SPECIES_THUNDURUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ThundurusTherian,
  [SPECIES_LANDORUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LandorusTherian,
  [SPECIES_ENAMORUS_THERIAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //EnamorusTherian,
  [SPECIES_KYUREM_WHITE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //KyuremWhite,
  [SPECIES_KYUREM_BLACK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //KyuremBlack,
  [SPECIES_KELDEO_RESOLUTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //KeldeoResolute,
  [SPECIES_MELOETTA_PIROUETTE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MeloettaPirouette,
  [SPECIES_GENESECT_DOUSE_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Genesect,
  [SPECIES_GENESECT_SHOCK_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Genesect,
  [SPECIES_GENESECT_BURN_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Genesect,
  [SPECIES_GENESECT_CHILL_DRIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Genesect,
  [SPECIES_GRENINJA_ASH] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //GreninjaAsh,
  [SPECIES_VIVILLON_POLAR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonPolar,
  [SPECIES_VIVILLON_TUNDRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonTundra,
  [SPECIES_VIVILLON_CONTINENTAL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonContinental,
  [SPECIES_VIVILLON_GARDEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonGarden,
  [SPECIES_VIVILLON_ELEGANT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonElegant,
  [SPECIES_VIVILLON_MEADOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonMeadow,
  [SPECIES_VIVILLON_MODERN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonModern,
  [SPECIES_VIVILLON_MARINE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonMarine,
  [SPECIES_VIVILLON_ARCHIPELAGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonArchipelago,
  [SPECIES_VIVILLON_HIGH_PLAINS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonHighPlains,
  [SPECIES_VIVILLON_SANDSTORM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonSandstorm,
  [SPECIES_VIVILLON_RIVER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonRiver,
  [SPECIES_VIVILLON_MONSOON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonMonsoon,
  [SPECIES_VIVILLON_SAVANNA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonSavanna,
  [SPECIES_VIVILLON_SUN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonSun,
  [SPECIES_VIVILLON_OCEAN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonOcean,
  [SPECIES_VIVILLON_JUNGLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonJungle,
  [SPECIES_VIVILLON_FANCY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonFancy,
  [SPECIES_VIVILLON_POKE_BALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //VivillonPokeBall,
  [SPECIES_UNFEZANT_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Unfezant_Female
  [SPECIES_PYROAR_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pyroar_Female,
  [SPECIES_FLABEBE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlabebeYellowFlower,
  [SPECIES_FLABEBE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlabebeOrangeFlower,
  [SPECIES_FLABEBE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlabebeBlueFlower,
  [SPECIES_FLABEBE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlabebeWhiteFlower,
  [SPECIES_FLOETTE_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FloetteYellowFlower,
  [SPECIES_FLOETTE_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FloetteOrangeFlower,
  [SPECIES_FLOETTE_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FloetteBlueFlower,
  [SPECIES_FLOETTE_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FloetteWhiteFlower,
  [SPECIES_FLOETTE_ETERNAL_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FloetteEternalFlower,
  [SPECIES_FLORGES_YELLOW_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlorgesYellowFlower,
  [SPECIES_FLORGES_ORANGE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlorgesOrangeFlower,
  [SPECIES_FLORGES_BLUE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlorgesBlueFlower,
  [SPECIES_FLORGES_WHITE_FLOWER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FlorgesWhiteFlower,
  [SPECIES_FURFROU_HEART_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouHeartTrim,
  [SPECIES_FURFROU_STAR_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouStarTrim,
  [SPECIES_FURFROU_DIAMOND_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouDiamondTrim,
  [SPECIES_FURFROU_DEBUTANTE_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouDebutanteTrim,
  [SPECIES_FURFROU_MATRON_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouMatronTrim,
  [SPECIES_FURFROU_DANDY_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouDandyTrim,
  [SPECIES_FURFROU_LA_REINE_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouLaReineTrim,
  [SPECIES_FURFROU_KABUKI_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouKabukiTrim,
  [SPECIES_FURFROU_PHARAOH_TRIM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //FurfrouPharaohTrim,
  [SPECIES_MEOWSTIC_FEMALE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MeowsticFemale,
  [SPECIES_AEGISLASH_BLADE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //AegislashBlade,
  [SPECIES_PUMPKABOO_SMALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_LARGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pumpkaboo,
  [SPECIES_PUMPKABOO_SUPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Pumpkaboo,
  [SPECIES_GOURGEIST_SMALL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gourgeist,
  [SPECIES_GOURGEIST_LARGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gourgeist,
  [SPECIES_GOURGEIST_SUPER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Gourgeist,
  [SPECIES_XERNEAS_ACTIVE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //XerneasActive,
  [SPECIES_ZYGARDE_10] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zygarde10,
  [SPECIES_ZYGARDE_10_POWER_CONSTRUCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zygarde10,
  [SPECIES_ZYGARDE_50_POWER_CONSTRUCT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zygarde,
  [SPECIES_ZYGARDE_COMPLETE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //ZygardeComplete,
  [SPECIES_HOOPA_UNBOUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //HoopaUnbound,
  [SPECIES_ORICORIO_POM_POM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //OricorioPomPom,
  [SPECIES_ORICORIO_PAU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //OricorioPau,
  [SPECIES_ORICORIO_SENSU] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //OricorioSensu,
  [SPECIES_LYCANROC_MIDNIGHT] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LycanrocMidnight,
  [SPECIES_LYCANROC_DUSK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //LycanrocDusk,
  [SPECIES_WISHIWASHI_SCHOOL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //WishiwashiSchool,
  [SPECIES_SILVALLY_FIGHTING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_FLYING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_POISON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_GROUND] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_ROCK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_BUG] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_GHOST] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_STEEL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_FIRE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_WATER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_GRASS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_ELECTRIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_PSYCHIC] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_ICE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_DRAGON] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_DARK] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_SILVALLY_FAIRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Silvally,
  [SPECIES_MINIOR_METEOR_ORANGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_YELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_GREEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_BLUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_INDIGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_METEOR_VIOLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Minior,
  [SPECIES_MINIOR_CORE_RED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreRed,
  [SPECIES_MINIOR_CORE_ORANGE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreOrange,
  [SPECIES_MINIOR_CORE_YELLOW] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreYellow,
  [SPECIES_MINIOR_CORE_GREEN] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreGreen,
  [SPECIES_MINIOR_CORE_BLUE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreBlue,
  [SPECIES_MINIOR_CORE_INDIGO] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreIndigo,
  [SPECIES_MINIOR_CORE_VIOLET] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MiniorCoreViolet,
  [SPECIES_MIMIKYU_BUSTED] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MimikyuBusted,
  [SPECIES_NECROZMA_DUSK_MANE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NecrozmaDuskMane,
  [SPECIES_NECROZMA_DAWN_WINGS] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NecrozmaDawnWings,
  [SPECIES_NECROZMA_ULTRA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //NecrozmaUltra,
  [SPECIES_MAGEARNA_ORIGINAL_COLOR] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //MagearnaOriginalColor,
  [SPECIES_CRAMORANT_GULPING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cramorant_Gulping,
  [SPECIES_CRAMORANT_GORGING] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Cramorant_Gorging,
  [SPECIES_TOXTRICITY_LOW_KEY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Toxtricity_Low_key,
      //[SPECIES_SINISTEA_ANTIQUE]                = gMonIcon_Sinistea_Antique,
      //[SPECIES_POLTEAGEIST_ANTIQUE]             = gMonIcon_PolteaGeist_Antique,
    [SPECIES_ALCREMIE_RUBY_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_ruby,
    [SPECIES_ALCREMIE_MATCHA_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_matcha,
    [SPECIES_ALCREMIE_MINT_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_mint,
    [SPECIES_ALCREMIE_LEMON_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_lemon,
    [SPECIES_ALCREMIE_SALTED_CREAM] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_salt,
    [SPECIES_ALCREMIE_RUBY_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_ruby_swirl,
    [SPECIES_ALCREMIE_CARAMEL_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_caramel_swirl,
    [SPECIES_ALCREMIE_RAINBOW_SWIRL] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Alcremie_rainbow_swirl,
    [SPECIES_EISCUE_NOICE_FACE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eiscue_noice_face,
    [SPECIES_INDEEDEE_FEMALE] = 
    {  
      FRONT_PIC(Indeedee_Female),
      FRONT_COORD(0x88,0),
      BACK_PIC(Indeedee_Female),
      BACK_COORD(0x88,0),
      PALETTES(Indeedee_Female),
      ICON(Indeedee_Female,0),
    }, //Indeedee_Female,
    [SPECIES_MORPEKO_HANGRY] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Morpeko_Hangry,
    [SPECIES_ZACIAN_CROWNED_SWORD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zacian_Crowned_Sword,
    [SPECIES_ZAMAZENTA_CROWNED_SHIELD] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zamazenta_Crowned_Shield,
    [SPECIES_ETERNATUS_ETERNAMAX] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Eternatus_Eternamax,
    [SPECIES_URSHIFU_RAPID_STRIKE_STYLE] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Urshifu_Rapid, //think last value needs no comma, nope doesn't matter but using comma is better in case you plan to add more
    [SPECIES_ZARUDE_DADA] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(QuestionMark,0),
    }, //Zarude_Dada,
    [SPECIES_CALYREX_ICE_RIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CircledQuestionMark),
      ICON(Calyrex_Ice_Rider,0),
    }, //Calyrex_Ice_Rider,
    [SPECIES_CALYREX_SHADOW_RIDER] = 
    {  
      FRONT_PIC(CircledQuestionMark),
      FRONT_COORD(0x88,0),
      BACK_PIC(CircledQuestionMark),
      BACK_COORD(0x88,0),
      PALETTES(CalyrexShadowRider),
      ICON(Calyrex_Shadow_Rider,0), //names w dashes are in icons only, can be pushsed to pallete and front/back pics
    }, //Calyrex_Shadow_Rider,
    [SPECIES_BASCULEGION_FEMALE] = 
    {  
      FRONT_PIC(BasculegionFemale),
      FRONT_COORD(0x88,0),
      BACK_PIC(BasculegionFemale),
      BACK_COORD(0x88,0),
      PALETTES(BasculegionFemale),
      ICON(BasculegionFemale,0),
    }, //BasculegionFemale,
};
