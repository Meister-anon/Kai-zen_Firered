#ifndef GUARD_CONSTANTS_ITEMS_H
#define GUARD_CONSTANTS_ITEMS_H
// because of my change to the item table I need to change all values that are ITEM_(some hex value) into ITEM_NONE I think..yeah I do, because they were previously
//auto aligned with a question mark icon & palette.   actually imma leave it for now, since I plan to fill those placeholders in.

// Note: If moving ball IDs around, updating FIRST_BALL/LAST_BALL is not sufficient
//       Several places expect the ball IDs to be first and contiguous (e.g. MON_DATA_POKEBALL)
//       If adding new balls, it's easiest to insert them after the last ball and increment the below IDs (and removing ITEM_034 for example)
//    this is needed because ball effects rely on secondaryId set in item slot, each on is unique to the ball
#define FIRST_BALL ITEM_MASTER_BALL
#define LAST_BALL  ITEM_PREMIER_BALL

//actually I think this file just needs to match the items.json //yup confirmed
#define ITEM_NONE 0
#define ITEM_MASTER_BALL 1
#define ITEM_ULTRA_BALL 2
#define ITEM_GREAT_BALL 3
#define ITEM_POKE_BALL 4
#define ITEM_SAFARI_BALL 5
#define ITEM_NET_BALL 6
#define ITEM_DIVE_BALL 7
#define ITEM_NEST_BALL 8
#define ITEM_REPEAT_BALL 9
#define ITEM_TIMER_BALL 10
#define ITEM_LUXURY_BALL 11
#define ITEM_PREMIER_BALL 12

//end of ball ids
#define ITEM_POTION 13
#define ITEM_ANTIDOTE 14
#define ITEM_BURN_HEAL 15
#define ITEM_ICE_HEAL 16
#define ITEM_AWAKENING 17
#define ITEM_PARALYZE_HEAL 18
#define ITEM_FULL_RESTORE 19
#define ITEM_MAX_POTION 20
#define ITEM_HYPER_POTION 21
#define ITEM_SUPER_POTION 22
#define ITEM_FULL_HEAL 23
#define ITEM_REVIVE 24
#define ITEM_MAX_REVIVE 25
#define ITEM_FRESH_WATER 26
#define ITEM_SODA_POP 27
#define ITEM_LEMONADE 28
#define ITEM_MOOMOO_MILK 29
#define ITEM_ENERGY_POWDER 30
#define ITEM_ENERGY_ROOT 31
#define ITEM_HEAL_POWDER 32
#define ITEM_REVIVAL_HERB 33
#define ITEM_ETHER 34
#define ITEM_MAX_ETHER 35
#define ITEM_ELIXIR 36
#define ITEM_MAX_ELIXIR 37
#define ITEM_LAVA_COOKIE 38
#define ITEM_BLUE_FLUTE 39
#define ITEM_YELLOW_FLUTE 40
#define ITEM_RED_FLUTE 41
#define ITEM_BLACK_FLUTE 42
#define ITEM_WHITE_FLUTE 43
#define ITEM_BERRY_JUICE 44
#define ITEM_SACRED_ASH 45
#define ITEM_SHOAL_SALT 46
#define ITEM_SHOAL_SHELL 47
#define ITEM_RED_SHARD 48
#define ITEM_BLUE_SHARD 49
#define ITEM_YELLOW_SHARD 50
#define ITEM_GREEN_SHARD 51
#define ITEM_034 52
#define ITEM_035 53
#define ITEM_036 54
#define ITEM_037 55
#define ITEM_038 56
#define ITEM_039 57
#define ITEM_03A 58
#define ITEM_03B 59
#define ITEM_03C 60
#define ITEM_03D 61
#define ITEM_03E 62
#define ITEM_HP_UP 63
#define ITEM_PROTEIN 64
#define ITEM_IRON 65
#define ITEM_CARBOS 66
#define ITEM_CALCIUM 67
#define ITEM_RARE_CANDY 68
#define ITEM_PP_UP 69
#define ITEM_ZINC 70
#define ITEM_PP_MAX 71
#define ITEM_048 72
#define ITEM_GUARD_SPEC 73
#define ITEM_DIRE_HIT 74
#define ITEM_X_ATTACK 75
#define ITEM_X_DEFENSE 76
#define ITEM_X_SPEED 77
#define ITEM_X_ACCURACY 78
#define ITEM_X_SP_ATK 79
#define ITEM_POKE_DOLL 80
#define ITEM_FLUFFY_TAIL 81
#define ITEM_X_SP_DEF 82
#define ITEM_SUPER_REPEL 83
#define ITEM_MAX_REPEL 84
#define ITEM_ESCAPE_ROPE 85
#define ITEM_REPEL 86
#define ITEM_ABILITY_CAPSULE 87	//remmbeber need change logic of this, so lets me select the slot to change to
#define ITEM_058 88
#define ITEM_059 89
#define ITEM_05A 90
#define ITEM_05B 91
#define ITEM_05C 92
#define ITEM_SUN_STONE 93
#define ITEM_MOON_STONE 94
#define ITEM_FIRE_STONE 95
#define ITEM_THUNDER_STONE 96
#define ITEM_WATER_STONE 97
#define ITEM_LEAF_STONE 98
#define ITEM_DAWN_STONE 99
#define ITEM_DUSK_STONE 100
#define ITEM_SHINY_STONE 101
#define ITEM_ICE_STONE 102
#define ITEM_TINY_MUSHROOM 103
#define ITEM_BIG_MUSHROOM 104
#define ITEM_069 105
#define ITEM_PEARL 106
#define ITEM_BIG_PEARL 107
#define ITEM_STARDUST 108
#define ITEM_STAR_PIECE 109
#define ITEM_NUGGET 110
#define ITEM_HEART_SCALE 111
#define ITEM_070 112
#define ITEM_071 113
#define ITEM_072 114
#define ITEM_073 115
#define ITEM_074 116
#define ITEM_075 117
#define ITEM_WHIPPED_DREAM 118
#define ITEM_SACHET 119
#define ITEM_OVAL_STONE 120
#define ITEM_ORANGE_MAIL 121
#define ITEM_HARBOR_MAIL 122
#define ITEM_GLITTER_MAIL 123
#define ITEM_MECH_MAIL 124
#define ITEM_WOOD_MAIL 125
#define ITEM_WAVE_MAIL 126
#define ITEM_BEAD_MAIL 127
#define ITEM_SHADOW_MAIL 128
#define ITEM_TROPIC_MAIL 129
#define ITEM_DREAM_MAIL 130
#define ITEM_FAB_MAIL 131
#define ITEM_RETRO_MAIL 132
#define ITEM_CHERI_BERRY 133
#define ITEM_CHESTO_BERRY 134
#define ITEM_PECHA_BERRY 135
#define ITEM_RAWST_BERRY 136
#define ITEM_ASPEAR_BERRY 137
#define ITEM_LEPPA_BERRY 138
#define ITEM_ORAN_BERRY 139
#define ITEM_PERSIM_BERRY 140
#define ITEM_LUM_BERRY 141
#define ITEM_SITRUS_BERRY 142
#define ITEM_FIGY_BERRY 143
#define ITEM_WIKI_BERRY 144
#define ITEM_MAGO_BERRY 145
#define ITEM_AGUAV_BERRY 146
#define ITEM_IAPAPA_BERRY 147
#define ITEM_RAZZ_BERRY 148
#define ITEM_BLUK_BERRY 149
#define ITEM_NANAB_BERRY 150
#define ITEM_WEPEAR_BERRY 151
#define ITEM_PINAP_BERRY 152
#define ITEM_POMEG_BERRY 153
#define ITEM_KELPSY_BERRY 154
#define ITEM_QUALOT_BERRY 155
#define ITEM_HONDEW_BERRY 156
#define ITEM_GREPA_BERRY 157
#define ITEM_TAMATO_BERRY 158
#define ITEM_CORNN_BERRY 159
#define ITEM_MAGOST_BERRY 160
#define ITEM_RABUTA_BERRY 161
#define ITEM_NOMEL_BERRY 162
#define ITEM_SPELON_BERRY 163
#define ITEM_PAMTRE_BERRY 164
#define ITEM_WATMEL_BERRY 165
#define ITEM_DURIN_BERRY 166
#define ITEM_BELUE_BERRY 167
#define ITEM_LIECHI_BERRY 168
#define ITEM_GANLON_BERRY 169
#define ITEM_SALAC_BERRY 170
#define ITEM_PETAYA_BERRY 171
#define ITEM_APICOT_BERRY 172
#define ITEM_LANSAT_BERRY 173
#define ITEM_STARF_BERRY 174
#define ITEM_ENIGMA_BERRY 175
#define ITEM_PROTECTOR 176 // add more evo "use" items below 0B2
#define ITEM_DRAGON_SCALE 177
#define ITEM_0B2 178 //last value for can be used on pokemon
#define ITEM_BRIGHT_POWDER 179
#define ITEM_WHITE_HERB 180
#define ITEM_MACHO_BRACE 181
#define ITEM_EXP_SHARE 182
#define ITEM_QUICK_CLAW 183
#define ITEM_SOOTHE_BELL 184
#define ITEM_MENTAL_HERB 185
#define ITEM_CHOICE_BAND 186
#define ITEM_KINGS_ROCK 187
#define ITEM_SILVER_POWDER 188
#define ITEM_AMULET_COIN 189
#define ITEM_CLEANSE_TAG 190
#define ITEM_SOUL_DEW 191
#define ITEM_DEEP_SEA_TOOTH 192
#define ITEM_DEEP_SEA_SCALE 193
#define ITEM_SMOKE_BALL 194
#define ITEM_EVERSTONE 195
#define ITEM_FOCUS_BAND 196
#define ITEM_LUCKY_EGG 197
#define ITEM_SCOPE_LENS 198
#define ITEM_C7 199
#define ITEM_LEFTOVERS 200
#define ITEM_0C9 201
#define ITEM_LIGHT_BALL 202
#define ITEM_SOFT_SAND 203
#define ITEM_HARD_STONE 204
#define ITEM_MIRACLE_SEED 205
#define ITEM_BLACK_GLASSES 206
#define ITEM_BLACK_BELT 207
#define ITEM_MAGNET 208
#define ITEM_MYSTIC_WATER 209
#define ITEM_SHARP_BEAK 210
#define ITEM_POISON_BARB 211
#define ITEM_NEVER_MELT_ICE 212
#define ITEM_SPELL_TAG 213
#define ITEM_TWISTED_SPOON 214
#define ITEM_CHARCOAL 215
#define ITEM_DRAGON_FANG 216
#define ITEM_SILK_SCARF 217
#define ITEM_0DA 218
#define ITEM_SHELL_BELL 219
#define ITEM_0DC 220
#define ITEM_0DD 221
#define ITEM_LUCKY_PUNCH 222
#define ITEM_METAL_POWDER 223
#define ITEM_THICK_CLUB 224
#define ITEM_LEEK 225
#define ITEM_PRISM_SCALE 226 // will make this an evo hold item level up, but because its milotic and difficult, make it random %4 only evolve while 0, so a 1 in 5 each level up.
#define ITEM_RAZOR_CLAW 227
#define ITEM_EVIOLITE 228
#define ITEM_EVIOLITE_FAIL 229
#define ITEM_0E6 230
#define ITEM_0E7 231
#define ITEM_0E8 232
#define ITEM_0E9 233
//Power Items
#define ITEM_POWER_WEIGHT 234	
#define ITEM_POWER_BRACER 235		
#define ITEM_POWER_BELT 236		
#define ITEM_POWER_LENS 237		
#define ITEM_POWER_BAND 238	
#define ITEM_POWER_ANKLET 239
//Fossils
#define ITEM_SAIL_FOSSIL 240		//amaura
#define ITEM_JAW_FOSSIL 241			//tyrunt
#define ITEM_PLUME_FOSSIL 242		//archen
#define ITEM_COVER_FOSSIL 243		//tirtouga
#define ITEM_FOSSILIZED_BIRD 244	//dracozolt = bird + drake
#define ITEM_FOSSILIZED_FISH 245	//dracovish = fish + drake
#define ITEM_SKULL_FOSSIL 246		//craniados
#define ITEM_ARMOR_FOSSIL 247		//shieldon
#define ITEM_FOSSILIZED_DINO 248	//arctozolt = bird + dino
#define ITEM_FOSSILIZED_DRAKE 249	//arctovish = fish + dino
#define ITEM_0FA 250
#define ITEM_0FB 251
#define ITEM_0FC 252
#define ITEM_0FD 253
#define ITEM_RED_SCARF 254
#define ITEM_BLUE_SCARF 255
#define ITEM_PINK_SCARF 256
#define ITEM_GREEN_SCARF 257
#define ITEM_YELLOW_SCARF 258
#define ITEM_MACH_BIKE 259
#define ITEM_COIN_CASE 260
#define ITEM_ITEMFINDER 261
#define ITEM_OLD_ROD 262
#define ITEM_GOOD_ROD 263
#define ITEM_SUPER_ROD 264
#define ITEM_SS_TICKET 265
#define ITEM_CONTEST_PASS 266
#define ITEM_10B 267
#define ITEM_WAILMER_PAIL 268
#define ITEM_DEVON_GOODS 269
#define ITEM_SOOT_SACK 270
#define ITEM_BASEMENT_KEY 271
#define ITEM_ACRO_BIKE 272
#define ITEM_POKEBLOCK_CASE 273
#define ITEM_LETTER 274
#define ITEM_EON_TICKET 275
#define ITEM_RED_ORB 276
#define ITEM_BLUE_ORB 277
#define ITEM_SCANNER 278
#define ITEM_GO_GOGGLES 279
#define ITEM_METEORITE 280
#define ITEM_ROOM_1_KEY 281
#define ITEM_ROOM_2_KEY 282
#define ITEM_ROOM_4_KEY 283
#define ITEM_ROOM_6_KEY 284
#define ITEM_STORAGE_KEY 285
#define ITEM_ROOT_FOSSIL 286	//lileep
#define ITEM_CLAW_FOSSIL 287	//anorith
#define ITEM_DEVON_SCOPE 288
#define ITEM_TM01 289
#define ITEM_TM02 290
#define ITEM_TM03 291
#define ITEM_TM04 292
#define ITEM_TM05 293
#define ITEM_TM06 294
#define ITEM_TM07 295
#define ITEM_TM08 296
#define ITEM_TM09 297
#define ITEM_TM10 298
#define ITEM_TM11 299
#define ITEM_TM12 300
#define ITEM_TM13 301
#define ITEM_TM14 302
#define ITEM_TM15 303
#define ITEM_TM16 304
#define ITEM_TM17 305
#define ITEM_TM18 306
#define ITEM_TM19 307
#define ITEM_TM20 308
#define ITEM_TM21 309
#define ITEM_TM22 310
#define ITEM_TM23 311
#define ITEM_TM24 312
#define ITEM_TM25 313
#define ITEM_TM26 314
#define ITEM_TM27 315
#define ITEM_TM28 316
#define ITEM_TM29 317
#define ITEM_TM30 318
#define ITEM_TM31 319
#define ITEM_TM32 320
#define ITEM_TM33 321
#define ITEM_TM34 322
#define ITEM_TM35 323
#define ITEM_TM36 324
#define ITEM_TM37 325
#define ITEM_TM38 326
#define ITEM_TM39 327
#define ITEM_TM40 328
#define ITEM_TM41 329
#define ITEM_TM42 330
#define ITEM_TM43 331
#define ITEM_TM44 332
#define ITEM_TM45 333
#define ITEM_TM46 334
#define ITEM_TM47 335
#define ITEM_TM48 336
#define ITEM_TM49 337
#define ITEM_TM50 338
#define ITEM_HM01 339
#define ITEM_HM02 340
#define ITEM_HM03 341
#define ITEM_HM04 342
#define ITEM_HM05 343
#define ITEM_HM06 344
#define ITEM_HM07 345
#define ITEM_HM08 346
#define ITEM_15B 347
#define ITEM_15C 348

#define ITEM_TM01_FOCUS_PUNCH ITEM_TM01
#define ITEM_TM02_DRAGON_CLAW ITEM_TM02
#define ITEM_TM03_WATER_PULSE ITEM_TM03
#define ITEM_TM04_CALM_MIND ITEM_TM04
#define ITEM_TM05_ROAR ITEM_TM05
#define ITEM_TM06_TOXIC ITEM_TM06
#define ITEM_TM07_HAIL ITEM_TM07
#define ITEM_TM08_BULK_UP ITEM_TM08
#define ITEM_TM09_BULLET_SEED ITEM_TM09
#define ITEM_TM10_HIDDEN_POWER ITEM_TM10
#define ITEM_TM11_SUNNY_DAY ITEM_TM11
#define ITEM_TM12_TAUNT ITEM_TM12
#define ITEM_TM13_ICE_BEAM ITEM_TM13
#define ITEM_TM14_BLIZZARD ITEM_TM14
#define ITEM_TM15_HYPER_BEAM ITEM_TM15
#define ITEM_TM16_LIGHT_SCREEN ITEM_TM16
#define ITEM_TM17_PROTECT ITEM_TM17
#define ITEM_TM18_RAIN_DANCE ITEM_TM18
#define ITEM_TM19_GIGA_DRAIN ITEM_TM19
#define ITEM_TM20_SAFEGUARD ITEM_TM20
#define ITEM_TM21_FRUSTRATION ITEM_TM21
#define ITEM_TM22_SOLARBEAM ITEM_TM22
#define ITEM_TM23_IRON_TAIL ITEM_TM23
#define ITEM_TM24_THUNDERBOLT ITEM_TM24
#define ITEM_TM25_THUNDER ITEM_TM25
#define ITEM_TM26_EARTHQUAKE ITEM_TM26
#define ITEM_TM27_RETURN ITEM_TM27
#define ITEM_TM28_DIG ITEM_TM28
#define ITEM_TM29_PSYCHIC ITEM_TM29
#define ITEM_TM30_SHADOW_BALL ITEM_TM30
#define ITEM_TM31_BRICK_BREAK ITEM_TM31
#define ITEM_TM32_DOUBLE_TEAM ITEM_TM32
#define ITEM_TM33_REFLECT ITEM_TM33
#define ITEM_TM34_SHOCK_WAVE ITEM_TM34
#define ITEM_TM35_FLAMETHROWER ITEM_TM35
#define ITEM_TM36_SLUDGE_BOMB ITEM_TM36
#define ITEM_TM37_SANDSTORM ITEM_TM37
#define ITEM_TM38_FIRE_BLAST ITEM_TM38
#define ITEM_TM39_ROCK_TOMB ITEM_TM39
#define ITEM_TM40_AERIAL_ACE ITEM_TM40
#define ITEM_TM41_TORMENT ITEM_TM41
#define ITEM_TM42_FACADE ITEM_TM42
#define ITEM_TM43_SECRET_POWER ITEM_TM43
#define ITEM_TM44_REST ITEM_TM44
#define ITEM_TM45_ATTRACT ITEM_TM45
#define ITEM_TM46_THIEF ITEM_TM46
#define ITEM_TM47_STEEL_WING ITEM_TM47
#define ITEM_TM48_SKILL_SWAP ITEM_TM48
#define ITEM_TM49_SNATCH ITEM_TM49
#define ITEM_TM50_OVERHEAT ITEM_TM50
#define ITEM_HM01_CUT ITEM_HM01
#define ITEM_HM02_FLY ITEM_HM02
#define ITEM_HM03_SURF ITEM_HM03
#define ITEM_HM04_STRENGTH ITEM_HM04
#define ITEM_HM05_FLASH ITEM_HM05
#define ITEM_HM06_ROCK_SMASH ITEM_HM06
#define ITEM_HM07_WATERFALL ITEM_HM07
#define ITEM_HM08_DIVE ITEM_HM08

// FireRed/LeafGreen  believe this is key items actually maybe..?
#define ITEM_OAKS_PARCEL 349
#define ITEM_POKE_FLUTE 350
#define ITEM_SECRET_KEY 351
#define ITEM_BIKE_VOUCHER 352
#define ITEM_GOLD_TEETH 353
#define ITEM_OLD_AMBER 354		//aerodactyl
#define ITEM_CARD_KEY 355
#define ITEM_LIFT_KEY 356
#define ITEM_HELIX_FOSSIL 357	//omanyte
#define ITEM_DOME_FOSSIL 358	//kabuto
#define ITEM_SILPH_SCOPE 359
#define ITEM_BICYCLE 360
#define ITEM_TOWN_MAP 361
#define ITEM_VS_SEEKER 362
#define ITEM_FAME_CHECKER 363
#define ITEM_TM_CASE 364
#define ITEM_BERRY_POUCH 365
#define ITEM_TEACHY_TV 366
#define ITEM_LINK_KEY 367 //NEW IDEA make key item call link key, trade evos can level up evolve long as yuo have this item //remove later don' tneed
#define ITEM_TRI_PASS 368 //  AND they meet whatever other condition they have
#define ITEM_RAINBOW_PASS 369
#define ITEM_TEA 370
#define ITEM_MYSTIC_TICKET 371
#define ITEM_AURORA_TICKET 372 /*
#define ITEM_POWDER_JAR 372 */
#define ITEM_MAGMA_EMBLEM 373
#define ITEM_OLD_SEA_MAP 374
#define ITEM_RUBY 375
#define ITEM_SAPPHIRE 376
#define ITEM_ULTIMA_BRACE 377
#define ITEM_EV_SHACKLES  378
// Secondary Set of Use items  (mostly for evo) 
#define ITEM_UP_GRADE 379  //need to change these items in items.json so they are evo items.
#define ITEM_ELECTIRIZER 380 //don't forget to list in evolutions table as well
#define ITEM_MAGMARIZER 381
#define ITEM_DUBIOUS_DISC 382
#define ITEM_REAPER_CLOTH 383
#define ITEM_METAL_COAT 384
//#define ITEM_LINK_CABLE 383 	// not gonna need this, if can just make use whatever item I want

#define ITEM_ABOMASITE 385
#define ITEM_ABSOLITE 386
#define ITEM_AERODACTYLITE 399
#define ITEM_AGGRONITE 400
#define ITEM_ALAKAZITE 401
#define ITEM_ALTARIANITE 402
#define ITEM_AMPHAROSITE 403
#define ITEM_AUDINITE 404
#define ITEM_BANETTITE 405
#define ITEM_BEEDRILLITE 406
#define ITEM_BLASTOISINITE 407
#define ITEM_BLAZIKENITE 408
#define ITEM_CAMERUPTITE 409
#define ITEM_CHARIZARDITE_X 410
#define ITEM_CHARIZARDITE_Y 411
#define ITEM_DIANCITE 412
#define ITEM_GALLADITE 413
#define ITEM_GARCHOMPITE 414
#define ITEM_GARDEVOIRITE 415
#define ITEM_GENGARITE 416
#define ITEM_GLALITITE 417
#define ITEM_GYARADOSITE 418
#define ITEM_HERACRONITE 419
#define ITEM_HOUNDOOMINITE 420
#define ITEM_KANGASKHANITE 421
#define ITEM_LATIASITE 422
#define ITEM_LATIOSITE 423
#define ITEM_LOPUNNITE 424
#define ITEM_LUCARIONITE 425
#define ITEM_MANECTITE 426
#define ITEM_MAWILITE 427
#define ITEM_MEDICHAMITE 428
#define ITEM_METAGROSSITE 429
#define ITEM_MEWTWONITE_X 430
#define ITEM_MEWTWONITE_Y 431
#define ITEM_PIDGEOTITE 432
#define ITEM_PINSIRITE 433
#define ITEM_SABLENITE 434
#define ITEM_SALAMENCITE 435
#define ITEM_SCEPTILITE 436
#define ITEM_SCIZORITE 437
#define ITEM_SHARPEDONITE 438
#define ITEM_SLOWBRONITE 439
#define ITEM_STEELIXITE 440
#define ITEM_SWAMPERTITE 441
#define ITEM_TYRANITARITE 442
#define ITEM_VENUSAURITE 443 //end of mega
//K looks like it doesn't matter where I put it except the use items,
// because effects and bag placement are set in the items.h file.
#define ITEM_MEGA_BRACELET 444 // should move set as key item.
/*
//More hold items
// Z Crystals
#define ITEM_Z_RING                   568
#define ITEM_NORMALIUM_Z              569
#define ITEM_FIGHTINIUM_Z             570
#define ITEM_FLYINIUM_Z               571
#define ITEM_POISONIUM_Z              572
#define ITEM_GROUNDIUM_Z              573
#define ITEM_ROCKIUM_Z                574
#define ITEM_BUGINIUM_Z               575
#define ITEM_GHOSTIUM_Z               576
#define ITEM_STEELIUM_Z               577
#define ITEM_FIRIUM_Z                 578
#define ITEM_WATERIUM_Z               579
#define ITEM_GRASSIUM_Z               580
#define ITEM_ELECTRIUM_Z              581
#define ITEM_PSYCHIUM_Z               582
#define ITEM_ICIUM_Z                  583
#define ITEM_DRAGONIUM_Z              584
#define ITEM_DARKINIUM_Z              585
#define ITEM_FAIRIUM_Z                586
#define ITEM_ALORAICHIUM_Z            587
#define ITEM_DECIDIUM_Z               588
#define ITEM_EEVIUM_Z                 589
#define ITEM_INCINIUM_Z               590
#define ITEM_KOMMONIUM_Z              591
#define ITEM_LUNALIUM_Z               592
#define ITEM_LYCANIUM_Z               593
#define ITEM_MARSHADIUM_Z             594
#define ITEM_MEWNIUM_Z                595
#define ITEM_MIMIKIUM_Z               596
#define ITEM_PIKANIUM_Z               597
#define ITEM_PIKASHUNIUM_Z            598
#define ITEM_PRIMARIUM_Z              599
#define ITEM_SNORLIUM_Z               600
#define ITEM_SOLGANIUM_Z              601
#define ITEM_TAPUNIUM_Z               602
#define ITEM_ULTRANECROZIUM_Z         603
//2nd set non-use held items
#define ITEM_CHOICE_SCARF 266
#define ITEM_CHOICE_SPECS 267
#define ITEM_FOCUS_SASH 268
#define ITEM_WIDE_LENS 269
#define ITEM_ZOOM_LENS 270
#define ITEM_METRONOME 271
#define ITEM_MUSCLE_BAND 272
#define ITEM_WISE_GLASSES 273
#define ITEM_EXPERT_BELT 274
#define ITEM_LIGHT_CLAY 275
#define ITEM_ICY_ROCK 276
#define ITEM_SMOOTH_ROCK 277
#define ITEM_HEAT_ROCK 278
#define ITEM_DAMP_ROCK 279
#define ITEM_DESTINY_KNOT 280
#define ITEM_GRIP_CLAW 281      //when do item port, change to description to say reinforce trap effects (to match suction cups and give that better context) last 7 turns and last if user switches
#define ITEM_LIFE_ORB 282
#define ITEM_TOXIC_ORB 283
#define ITEM_FLAME_ORB 284
#define ITEM_STICKY_BARB 285
#define ITEM_BLACK_SLUDGE 286
#define ITEM_IRON_BALL 287
#define ITEM_LAGGING_TAIL 288
#define ITEM_SHED_SHELL 289
#define ITEM_BIG_ROOT 290
#define 
#define ITEM_FLOAT_STONE 292
#define ITEM_ROCKY_HELMET 293
#define ITEM_AIR_BALLOON 294
#define ITEM_RED_CARD 295
#define ITEM_RING_TARGET 296
#define ITEM_BINDING_BAND 297
#define ITEM_EJECT_BUTTON 298
#define ITEM_ABSORB_BULB 299
#define ITEM_CELL_BATTERY 300
#define ITEM_LUMINOUS_MOSS 301
#define ITEM_SNOWBALL 302
#define ITEM_WEAKNESS_POLICY 303
#define ITEM_ASSAULT_VEST 304
#define ITEM_SAFETY_GOGGLES 305
#define ITEM_ADRENALINE_ORB 306
#define ITEM_TERRAIN_EXTENDER 307
#define ITEM_PROTECTIVE_PADS 308
#define ITEM_ELECTRIC_SEED 309
#define ITEM_PSYCHIC_SEED 310
#define ITEM_MISTY_SEED 311
#define ITEM_GRASSY_SEED 312*/
//END of 2nd set of Use items
// Incenses
#define ITEM_SEA_INCENSE 445//385 
#define ITEM_LAX_INCENSE 446
#define ITEM_BLACK_SLUDGE 447
#define ITEM_BAD_ONION 448 //  ok these new values for incense are actually better, since they aren't supposed to be for use, just hold.
/*#define ITEM_ODD_INCENSE 386
#define ITEM_ROCK_INCENSE 387
#define ITEM_FULL_INCENSE 388
#define ITEM_WAVE_INCENSE 389
#define ITEM_ROSE_INCENSE 390
#define ITEM_LUCK_INCENSE 391
#define ITEM_PURE_INCENSE 392
// Plates
#define ITEM_INSECT_PLATE 322
#define ITEM_DREAD_PLATE 323
#define ITEM_DRACO_PLATE 324
#define ITEM_ZAP_PLATE 325
#define ITEM_PIXIE_PLATE 326
#define ITEM_FIST_PLATE 327
#define ITEM_FLAME_PLATE 328
#define ITEM_SKY_PLATE 329
#define ITEM_SPOOKY_PLATE 330
#define ITEM_MEADOW_PLATE 331
#define ITEM_EARTH_PLATE 332
#define ITEM_ICICLE_PLATE 333
#define ITEM_TOXIC_PLATE 334
#define ITEM_MIND_PLATE 335
#define ITEM_STONE_PLATE 336
#define ITEM_IRON_PLATE 337
#define ITEM_SPLASH_PLATE 338
// Gems
#define ITEM_BUG_GEM 339
#define ITEM_DARK_GEM 340
#define ITEM_DRAGON_GEM 341
#define ITEM_ELECTRIC_GEM 342
#define ITEM_FAIRY_GEM 343
#define ITEM_FIGHTING_GEM 344
#define ITEM_FIRE_GEM 345
#define ITEM_FLYING_GEM 346
#define ITEM_GHOST_GEM 347
#define ITEM_GRASS_GEM 348
#define ITEM_GROUND_GEM 349
#define ITEM_ICE_GEM 350
#define ITEM_NORMAL_GEM 351
#define ITEM_POISON_GEM 352
#define ITEM_PSYCHIC_GEM 353
#define ITEM_ROCK_GEM 354
#define ITEM_STEEL_GEM 355
#define ITEM_WATER_GEM 356
// Memories
#define ITEM_BUG_MEMORY 371
#define ITEM_DARK_MEMORY 372
#define ITEM_DRAGON_MEMORY 373
#define ITEM_ELECTRIC_MEMORY 374
#define ITEM_FAIRY_MEMORY 375
#define ITEM_FIGHTING_MEMORY 376
#define ITEM_FIRE_MEMORY 377
#define ITEM_FLYING_MEMORY 378
#define ITEM_GHOST_MEMORY 379
#define ITEM_GRASS_MEMORY 380
#define ITEM_GROUND_MEMORY 381
#define ITEM_ICE_MEMORY 382
#define ITEM_POISON_MEMORY 383
#define ITEM_PSYCHIC_MEMORY 384
#define ITEM_ROCK_MEMORY 385
#define ITEM_STEEL_MEMORY 386
#define ITEM_WATER_MEMORY 387
// Drives
#define ITEM_DOUSE_DRIVE 388
#define ITEM_SHOCK_DRIVE 389
#define ITEM_BURN_DRIVE 390
#define ITEM_CHILL_DRIVE 391

//extra key items
#define ITEM_BEATER
#define ITEM_BEATER
#define ITEM_BEATER
#define ITEM_GRACIDEA
#define ITEM_ODD_KEYSTONE
#define ITEM_ADAMANT_ORB
#define ITEM_LUSTROUS_ORB
#define ITEM_GRISEOUS_ORB */
#define ITEM_N_A 449 // keep this as last item value, needs be +1 last defined item value   emerald stuff needs to be a separate value, otherwise seems to make duplicate error
#define ITEMS_COUNT ITEM_N_A +1
#define ITEM_FIELD_ARROW ITEM_N_A//field arrow isn't defined as an item, it just end of item_menu_icons.c list
// Emerald   BUT based on list from vanilla its actually ID was equal to items N_A, circumventing that equation.

#define LAST_ITEM_INDEX ITEM_BAD_ONION

#define FIRST_BERRY_INDEX ITEM_CHERI_BERRY
#define LAST_BERRY_INDEX ITEM_ENIGMA_BERRY
#define ITEM_TO_BERRY(itemId)(((itemId - FIRST_BERRY_INDEX) + 1))

#define NUM_TECHNICAL_MACHINES 50 //change to 120 later  / or more plan to add on to tms I think for ease spreading certain moves
#define NUM_HIDDEN_MACHINES     8

// Check if the item is one that can be used on a Pokemon.
#define IS_POKEMON_ITEM(item) ((item) > ITEM_PREMIER_BALL && (item) < ITEM_0B2)
#define IS_POKEMON_ITEM2(item) ((item) > ITEM_EV_SHACKLES && (item) < ITEM_SEA_INCENSE)
//BECAUSE of this need to add mega stones in somewhere before to cutoff.
// or copy function for define and create a new range, for IS_POKEMON_ITEM2
//that way I can just add on to end. but before N_A
#endif  // GUARD_CONSTANTS_ITEMS_H