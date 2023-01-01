const u8 gMoveNames[][13] = {
    _("-$$$$$$"),
    _("POUND"),
    _("KARATE CHOP"),
    _("DOUBLESLAP"),
    _("COMET PUNCH"),
    _("MEGA PUNCH"),
    _("PAY DAY"),
    _("FIRE PUNCH"),
    _("ICE PUNCH"),
    _("THUNDERPUNCH"),
    _("SCRATCH"),
    _("VICEGRIP"),
    _("GUILLOTINE"),
    _("RAZOR WIND"),
    _("SWORDS DANCE"),
    _("CUT"),
    _("GUST"),
    _("WING ATTACK"),
    _("WHIRLWIND"),
    _("FLY"),
    _("BIND"),
    _("SLAM"),
    _("VINE WHIP"),
    _("STOMP"),
    _("DOUBLE KICK"),
    _("MEGA KICK"),
    _("JUMP KICK"),
    _("ROLLING KICK"),
    _("SAND-ATTACK"),
    _("HEADBUTT"),
    _("HORN ATTACK"),
    _("FURY ATTACK"),
    _("HORN DRILL"),
    _("TACKLE"),
    _("BODY SLAM"),
    _("WRAP"),
    _("TAKE DOWN"),
    _("THRASH"),
    _("DOUBLE-EDGE"),
    _("TAIL WHIP"),
    _("POISON STING"),
    _("TWINEEDLE"),
    _("PIN MISSILE"),
    _("LEER"),
    _("BITE"),
    _("GROWL"),
    _("ROAR"),
    _("SING"),
    _("SUPERSONIC"),
    _("SONICBOOM"),
    _("DISABLE"),
    _("ACID"),
    _("EMBER"),
    _("FLAMETHROWER"),
    _("MIST"),
    _("WATER GUN"),
    _("HYDRO PUMP"),
    _("SURF"),
    _("ICE BEAM"),
    _("BLIZZARD"),
    _("PSYBEAM"),
    _("BUBBLEBEAM"),
    _("AURORA BEAM"),
    _("HYPER BEAM"),
    _("PECK"),
    _("DRILL PECK"),
    _("SUBMISSION"),
    _("LOW KICK"),
    _("COUNTER"),
    _("SEISMIC TOSS"),
    _("STRENGTH"),
    _("ABSORB"),
    _("MEGA DRAIN"),
    _("LEECH SEED"),
    _("GROWTH"),
    _("RAZOR LEAF"),
    _("SOLARBEAM"),
    _("POISONPOWDER"),
    _("STUN SPORE"),
    _("SLEEP POWDER"),
    _("PETAL DANCE"),
    _("STRING SHOT"),
    _("DRAGON RAGE"),
    _("FIRE SPIN"),
    _("THUNDERSHOCK"),
    _("THUNDERBOLT"),
    _("THUNDER WAVE"),
    _("THUNDER"),
    _("ROCK THROW"),
    _("EARTHQUAKE"),
    _("FISSURE"),
    _("DIG"),
    _("TOXIC"),
    _("CONFUSION"),
    _("PSYCHIC"),
    _("HYPNOSIS"),
    _("MEDITATE"),
    _("AGILITY"),
    _("QUICK ATTACK"),
    _("RAGE"),
    _("TELEPORT"),
    _("NIGHT SHADE"),
    _("MIMIC"),
    _("SCREECH"),
    _("DOUBLE TEAM"),
    _("RECOVER"),
    _("HARDEN"),
    _("MINIMIZE"),
    _("SMOKESCREEN"),
    _("CONFUSE RAY"),
    _("WITHDRAW"),
    _("DEFENSE CURL"),
    _("BARRIER"),
    _("LIGHT SCREEN"),
    _("HAZE"),
    _("REFLECT"),
    _("FOCUS ENERGY"),
    _("BIDE"),
    _("METRONOME"),
    _("MIRROR MOVE"),
    _("SELFDESTRUCT"),
    _("EGG BOMB"),
    _("LICK"),
    _("SMOG"),
    _("SLUDGE"),
    _("BONE CLUB"),
    _("FIRE BLAST"),
    _("WATERFALL"),
    _("CLAMP"),
    _("SWIFT"),
    _("SKULL BASH"),
    _("SPIKE CANNON"),
    _("CONSTRICT"),
    _("AMNESIA"),
    _("KINESIS"),
    _("SOFTBOILED"),
    _("HI JUMP KICK"),
    _("GLARE"),
    _("DREAM EATER"),
    _("POISON GAS"),
    _("BARRAGE"),
    _("LEECH LIFE"),
    _("LOVELY KISS"),
    _("SKY ATTACK"),
    _("TRANSFORM"),
    _("BUBBLE"),
    _("DIZZY PUNCH"),
    _("SPORE"),
    _("FLASH"),
    _("PSYWAVE"),
    _("SPLASH"),
    _("ACID ARMOR"),
    _("CRABHAMMER"),
    _("EXPLOSION"),
    _("FURY SWIPES"),
    _("BONEMERANG"),
    _("REST"),
    _("ROCK SLIDE"),
    _("HYPER FANG"),
    _("SHARPEN"),
    _("CONVERSION"),
    _("TRI ATTACK"),
    _("SUPER FANG"),
    _("SLASH"),
    _("SUBSTITUTE"),
    _("STRUGGLE"),
    _("SKETCH"),
    _("TRIPLE KICK"),
    _("THIEF"),
    _("SPIDER WEB"),
    _("MIND READER"),
    _("NIGHTMARE"),
    _("FLAME WHEEL"),
    _("SNORE"),
    _("CURSE"),
    _("FLAIL"),
    _("CONVERSION 2"),
    _("AEROBLAST"),
    _("COTTON SPORE"),
    _("REVERSAL"),
    _("SPITE"),
    _("POWDER SNOW"),
    _("PROTECT"),
    _("MACH PUNCH"),
    _("SCARY FACE"),
    _("FAINT ATTACK"),
    _("SWEET KISS"),
    _("BELLY DRUM"),
    _("SLUDGE BOMB"),
    _("MUD-SLAP"),
    _("OCTAZOOKA"),
    _("SPIKES"),
    _("ZAP CANNON"),
    _("FORESIGHT"),
    _("DESTINY BOND"),
    _("PERISH SONG"),
    _("ICY WIND"),
    _("DETECT"),
    _("BONE RUSH"),
    _("LOCK-ON"),
    _("OUTRAGE"),
    _("SANDSTORM"),
    _("GIGA DRAIN"),
    _("ENDURE"),
    _("CHARM"),
    _("ROLLOUT"),
    _("FALSE SWIPE"),
    _("SWAGGER"),
    _("MILK DRINK"),
    _("SPARK"),
    _("FURY CUTTER"),
    _("STEEL WING"),
    _("MEAN LOOK"),
    _("ATTRACT"),
    _("SLEEP TALK"),
    _("HEAL BELL"),
    _("RETURN"),
    _("PRESENT"),
    _("FRUSTRATION"),
    _("SAFEGUARD"),
    _("PAIN SPLIT"),
    _("SACRED FIRE"),
    _("MAGNITUDE"),
    _("DYNAMICPUNCH"),
    _("MEGAHORN"),
    _("DRAGONBREATH"),
    _("BATON PASS"),
    _("ENCORE"),
    _("PURSUIT"),
    _("RAPID SPIN"),
    _("SWEET SCENT"),
    _("IRON TAIL"),
    _("METAL CLAW"),
    _("VITAL THROW"),
    _("MORNING SUN"),
    _("SYNTHESIS"),
    _("MOONLIGHT"),
    _("HIDDEN POWER"),
    _("CROSS CHOP"),
    _("TWISTER"),
    _("RAIN DANCE"),
    _("SUNNY DAY"),
    _("CRUNCH"),
    _("MIRROR COAT"),
    _("PSYCH UP"),
    _("EXTREMESPEED"),
    _("ANCIENTPOWER"),
    _("SHADOW BALL"),
    _("FUTURE SIGHT"),
    _("ROCK SMASH"),
    _("WHIRLPOOL"),
    _("BEAT UP"),
    _("FAKE OUT"),
    _("UPROAR"),
    _("STOCKPILE"),
    _("SPIT UP"),
    _("SWALLOW"),
    _("HEAT WAVE"),
    _("HAIL"),
    _("TORMENT"),
    _("FLATTER"),
    _("WILL-O-WISP"),
    _("MEMENTO"),
    _("FACADE"),
    _("FOCUS PUNCH"),
    _("SMELLINGSALT"),
    _("FOLLOW ME"),
    _("NATURE POWER"),
    _("CHARGE"),
    _("TAUNT"),
    _("HELPING HAND"),
    _("TRICK"),
    _("ROLE PLAY"),
    _("WISH"),
    _("ASSIST"),
    _("INGRAIN"),
    _("SUPERPOWER"),
    _("MAGIC COAT"),
    _("RECYCLE"),
    _("REVENGE"),
    _("BRICK BREAK"),
    _("YAWN"),
    _("KNOCK OFF"),
    _("ENDEAVOR"),
    _("ERUPTION"),
    _("SKILL SWAP"),
    _("IMPRISON"),
    _("REFRESH"),
    _("GRUDGE"),
    _("SNATCH"),
    _("SECRET POWER"),
    _("DIVE"),
    _("ARM THRUST"),
    _("CAMOUFLAGE"),
    _("TAIL GLOW"),
    _("LUSTER PURGE"),
    _("MIST BALL"),
    _("FEATHERDANCE"),
    _("TEETER DANCE"),
    _("BLAZE KICK"),
    _("MUD SPORT"),
    _("ICE BALL"),
    _("NEEDLE ARM"),
    _("SLACK OFF"),
    _("HYPER VOICE"),
    _("POISON FANG"),
    _("CRUSH CLAW"),
    _("BLAST BURN"),
    _("HYDRO CANNON"),
    _("METEOR MASH"),
    _("ASTONISH"),
    _("WEATHER BALL"),
    _("AROMATHERAPY"),
    _("FAKE TEARS"),
    _("AIR CUTTER"),
    _("OVERHEAT"),
    _("ODOR SLEUTH"),
    _("ROCK TOMB"),
    _("SILVER WIND"),
    _("METAL SOUND"),
    _("GRASSWHISTLE"),
    _("TICKLE"),
    _("COSMIC POWER"),
    _("WATER SPOUT"),
    _("SIGNAL BEAM"),
    _("SHADOW PUNCH"),
    _("EXTRASENSORY"),
    _("SKY UPPERCUT"),
    _("SAND TOMB"),
    _("SHEER COLD"),
    _("MUDDY WATER"),
    _("BULLET SEED"),
    _("AERIAL ACE"),
    _("ICICLE SPEAR"),
    _("IRON DEFENSE"),
    _("BLOCK"),
    _("HOWL"),
    _("DRAGON CLAW"),
    _("FRENZY PLANT"),
    _("BULK UP"),
    _("BOUNCE"),
    _("MUD SHOT"),
    _("POISON TAIL"),
    _("COVET"),
    _("VOLT TACKLE"),
    _("MAGICAL LEAF"),
    _("WATER SPORT"),
    _("CALM MIND"),
    _("LEAF BLADE"),
    _("DRAGON DANCE"),
    _("ROCK BLAST"),
    _("SHOCK WAVE"),
    _("WATER PULSE"),
    _("DOOM DESIRE"),
    _("PSYCHO BOOST"),
    _("ROOST"),
    _("GRAVITY"),
    _("MIRACLE EYE"),
    _("WAKE-UP SLAP"),
    _("HAMMER ARM"),
    _("GYRO BALL"),
    _("HEALING WISH"),
    _("BRINE"),
    _("NATURAL GIFT"),
    _("FEINT"),
    _("PLUCK"),
    _("TAILWIND"),
    _("ACUPRESSURE"),
    _("METAL BURST"),
    _("U-TURN"),
    _("CLOSE COMBAT"),
    _("PAYBACK"),
    _("ASSURANCE"),
    _("EMBARGO"),
    _("FLING"),
    _("PSYCHO SHIFT"),
    _("TRUMP CARD"),
    _("HEAL BLOCK"),
    _("WRING OUT"),
    _("POWER TRICK"),
    _("GASTRO ACID"),
    _("LUCKY CHANT"),
    _("ME FIRST"),
    _("COPYCAT"),
    _("POWER SWAP"),
    _("GUARD SWAP"),
    _("PUNISHMENT"),
    _("LAST RESORT"),
    _("WORRY SEED"),
    _("SUCKER PUNCH"),
    _("TOXIC SPIKES"),
    _("HEART SWAP"),
    _("AQUA RING"),
    _("MAGNET RISE"),
    _("FLARE BLITZ"),
    _("FORCE PALM"),
    _("AURA SPHERE"),
    _("ROCK POLISH"),
    _("POISON JAB"),
    _("DARK PULSE"),
    _("NIGHT SLASH"),
    _("AQUA TAIL"),
    _("SEED BOMB"),
    _("AIR SLASH"),
    _("X-SCISSOR"),
    _("BUG BUZZ"),
    _("DRAGON PULSE"),
    _("DRAGON RUSH"),
    _("POWER GEM"),
    _("DRAIN PUNCH"),
    _("VACUUM WAVE"),
    _("FOCUS BLAST"),
    _("ENERGY BALL"),
    _("BRAVE BIRD"),
    _("EARTH POWER"),
    _("SWITCHEROO"),
    _("GIGA IMPACT"),
    _("NASTY PLOT"),
    _("BULLET PUNCH"),
    _("AVALANCHE"),
    _("ICE SHARD"),
    _("SHADOW CLAW"),
    _("THUNDER FANG"),
    _("ICE FANG"),
    _("FIRE FANG"),
    _("SHADOW SNEAK"),
    _("MUD BOMB"),
    _("PSYCHO CUT"),
    _("ZEN HEADBUTT"),
    _("MIRROR SHOT"),
    _("FLASH CANNON"),
    _("ROCK CLIMB"),
    _("DEFOG"),
    _("TRICK ROOM"),
    _("DRACO METEOR"),
    _("DISCHARGE"),
    _("LAVA PLUME"),
    _("LEAF STORM"),
    _("POWER WHIP"),
    _("ROCK WRECKER"),
    _("CROSS POISON"),
    _("GUNK SHOT"),
    _("IRON HEAD"),
    _("MAGNET BOMB"),
    _("STONE EDGE"),
    _("CAPTIVATE"),
    _("STEALTH ROCK"),
    _("GRASS KNOT"),
    _("CHATTER"),
    _("JUDGMENT"),
    _("BUG BITE"),
    _("CHARGE BEAM"),
    _("WOOD HAMMER"),
    _("AQUA JET"),
    _("ATTACK ORDER"),
    _("DEFEND ORDER"),
    _("HEAL ORDER"),
    _("HEAD SMASH"),
    _("DOUBLE HIT"),
    _("ROAR OF TIME"),
    _("SPACIAL REND"),
    _("LUNAR DANCE"),
    _("CRUSH GRIP"),
    _("MAGMA STORM"),
    _("DARK VOID"),
    _("SEED FLARE"),
    _("OMINOUS WIND"),
    _("SHADOW FORCE"),
    _("HONE CLAWS"),
    _("WIDE GUARD"),
    _("GUARD SPLIT"),
    _("POWER SPLIT"),
    _("WONDER ROOM"),
    _("PSYSHOCK"),
    _("VENOSHOCK"),
    _("AUTOTOMIZE"),
    _("RAGE POWDER"),
    _("TELEKINESIS"),
    _("MAGIC ROOM"),
    _("SMACK DOWN"),
    _("STORM THROW"),
    _("FLAME BURST"),
    _("SLUDGE WAVE"),
    _("QUIVER DANCE"),
    _("HEAVY SLAM"),
    _("SYNCHRONOISE"),
    _("ELECTRO BALL"),
    _("SOAK"),
    _("FLAME CHARGE"),
    _("COIL"),
    _("LOW SWEEP"),
    _("ACID SPRAY"),
    _("FOUL PLAY"),
    _("SIMPLE BEAM"),
    _("ENTRAINMENT"),
    _("AFTER YOU"),
    _("ROUND"),
    _("ECHOED VOICE"),
    _("CHIP AWAY"),
    _("CLEAR SMOG"),
    _("STORED POWER"),
    _("QUICK GUARD"),
    _("ALLY SWITCH"),
    _("SCALD"),
    _("SHELL SMASH"),
    _("HEAL PULSE"),
    _("HEX"),
    _("SKY DROP"),
    _("SHIFT GEAR"),
    _("CIRCLE THROW"),
    _("INCINERATE"),
    _("QUASH"),
    _("ACROBATICS"),
    _("REFLECT TYPE"),
    _("RETALIATE"),
    _("FINAL GAMBIT"),
    _("BESTOW"),
    _("INFERNO"),
    _("WATER PLEDGE"),
    _("FIRE PLEDGE"),
    _("GRASS PLEDGE"),
    _("VOLT SWITCH"),
    _("STRUGGLE BUG"),
    _("BULLDOZE"),
    _("FROST BREATH"),
    _("DRAGON TAIL"),
    _("WORK UP"),
    _("ELECTROWEB"),
    _("WILD CHARGE"),
    _("DRILL RUN"),
    _("DUAL CHOP"),
    _("HEART STAMP"),
    _("HORN LEECH"),
    _("SACRED SWORD"),
    _("RAZOR SHELL"),
    _("HEAT CRASH"),
    _("LEAF TORNADO"),
    _("STEAMROLLER"),
    _("COTTON GUARD"),
    _("NIGHT DAZE"),
    _("PSYSTRIKE"),
    _("TAIL SLAP"),
    _("HURRICANE"),
    _("HEAD CHARGE"),
    _("GEAR GRIND"),
    _("SEARING SHOT"),
    _("TECHNO BLAST"),
    _("RELIC SONG"),
    _("SECRET SWORD"),
    _("GLACIATE"),
    _("BOLT STRIKE"),
    _("BLUE FLARE"),
    _("FIERY DANCE"),
    _("FREEZE SHOCK"),
    _("ICE BURN"),
    _("SNARL"),
    _("ICICLE CRASH"),
    _("V CREATE"),
    _("FUSION FLARE"),
    _("FUSION BOLT"),
    _("FLYING PRESS"),
    _("MAT BLOCK"),
    _("BELCH"),
    _("ROTOTILLER"),
    _("STICKY WEB"),
    _("FELL STINGER"),
    _("PHANTOM FORCE"),
    _("TRICK OR TREAT"),
    _("NOBLE ROAR"),
    _("ION DELUGE"),
    _("PARABOLIC CHARGE"),
    _("FORESTS CURSE"),
    _("PETAL BLIZZARD"),
    _("FREEZE DRY"),
    _("DISARMING VOICE"),
    _("PARTING SHOT"),
    _("TOPSY TURVY"),
    _("DRAINING KISS"),
    _("CRAFTY SHIELD"),
    _("FLOWER SHIELD"),
    _("GRASSY TERRAIN"),
    _("MISTY TERRAIN"),
    _("ELECTRIFY"),
    _("PLAY ROUGH"),
    _("FAIRY WIND"),
    _("MOONBLAST"),
    _("BOOMBURST"),
    _("FAIRY LOCK"),
    _("KINGS SHIELD"),
    _("PLAY NICE"),
    _("CONFIDE"),
    _("DIAMOND STORM"),
    _("STEAM ERUPTION"),
    _("HYPERSPACE HOLE"),
    _("WATER SHURIKEN"),
    _("MYSTICAL FIRE"),
    _("SPIKY SHIELD"),
    _("AROMATIC MIST"),
    _("EERIE IMPULSE"),
    _("VENOM DRENCH"),
    _("POWDER"),
    _("GEOMANCY"),
    _("MAGNETIC FLUX"),
    _("HAPPY HOUR"),
    _("ELECTRIC TERRAIN"),
    _("DAZZLING GLEAM"),
    _("CELEBRATE"),
    _("HOLD HANDS"),
    _("BABY DOLL EYES"),
    _("NUZZLE"),
    _("HOLD BACK"),
    _("INFESTATION"),
    _("POWER UP PUNCH"),
    _("OBLIVION WING"),
    _("THOUSAND ARROWS"),
    _("THOUSAND WAVES"),
    _("LANDS WRATH"),
    _("LIGHT OF RUIN"),
    _("ORIGIN PULSE"),
    _("PRECIPICE BLADES"),
    _("DRAGON ASCENT"),
    _("HYPERSPACE FURY"),
    _("SHORE UP"),
    _("FIRST IMPRESSION"),
    _("BANEFUL BUNKER"),
    _("SPIRIT SHACKLE"),
    _("DARKEST LARIAT"),
    _("SPARKLING ARIA"),
    _("ICE HAMMER"),
    _("FLORAL HEALING"),
    _("HIGH HORSEPOWER"),
    _("STRENGTH SAP"),
    _("SOLAR BLADE"),
    _("LEAFAGE"),
    _("SPOTLIGHT"),
    _("TOXIC THREAD"),
    _("LASER FOCUS"),
    _("GEAR UP"),
    _("THROAT CHOP"),
    _("POLLEN PUFF"),
    _("ANCHOR SHOT"),
    _("PSYCHIC TERRAIN"),
    _("LUNGE"),
    _("FIRE LASH"),
    _("POWER TRIP"),
    _("BURN UP"),
    _("SPEED SWAP"),
    _("SMART STRIKE"),
    _("PURIFY"),
    _("REVELATION DANCE"),
    _("CORE ENFORCER"),
    _("TROP KICK"),
    _("INSTRUCT"),
    _("BEAK BLAST"),
    _("CLANGING SCALES"),
    _("DRAGON HAMMER"),
    _("BRUTAL SWING"),
    _("AURORA VEIL"),
    _("SHELL TRAP"),
    _("FLEUR CANNON"),
    _("PSYCHIC FANGS"),
    _("STOMPING TANTRUM"),
    _("SHADOW BONE"),
    _("ACCELEROCK"),
    _("LIQUIDATION"),
    _("PRISMATIC LASER"),
    _("SPECTRAL THIEF"),
    _("SUNSTEEL STRIKE"),
    _("MOONGEIST BEAM"),
    _("TEARFUL LOOK"),
    _("ZING ZAP"),
    _("NATURES MADNESS"),
    _("MULTI ATTACK"),
    _("MIND BLOWN"),
    _("PLASMA FISTS"),
    _("PHOTON GEYSER"),
    _("ZIPPY ZAP"),
    _("SPLISHY SPLASH"),
    _("FLOATY FALL"),
    _("PIKA PAPOW"),
    _("BOUNCY BUBBLE"),
    _("BUZZY BUZZ"),
    _("SIZZLY SLIDE"),
    _("GLITZY GLOW"),
    _("BADDY BAD"),
    _("SAPPY SEED"),
    _("FREEZY FROST"),
    _("SPARKLY SWIRL"),
    _("VEEVEE VOLLEY"),
    _("DOUBLE IRON BASH"),
    _("DYNAMAX CANNON"),
    _("SNIPE SHOT"),
    _("JAW LOCK"),
    _("STUFF CHEEKS"),
    _("NO RETREAT"),
    _("TAR SHOT"),
    _("MAGIC POWDER"),
    _("DRAGON DARTS"),
    _("TEATIME"),
    _("OCTOLOCK"),
    _("BOLT BEAK"),
    _("FISHIOUS REND"),
    _("COURT CHANGE"),
    _("CLANGOROUS SOUL"),
    _("BODY PRESS"),
    _("DECORATE"),
    _("DRUM BEATING"),
    _("SNAP TRAP"),
    _("PYRO BALL"),
    _("BEHEMOTH BLADE"),
    _("BEHEMOTH BASH"),
    _("AURA WHEEL"),
    _("BREAKING SWIPE"),
    _("BRANCH POKE"),
    _("OVERDRIVE"),
    _("APPLE ACID"),
    _("GRAV APPLE"),
    _("SPIRIT BREAK"),
    _("STRANGE STEAM"),
    _("LIFE DEW"),
    _("OBSTRUCT"),
    _("FALSE SURRENDER"),
    _("METEOR ASSAULT"),
    _("ETERNABEAM"),
    _("STEEL BEAM"),
    _("EXPANDING FORCE"),
    _("STEEL ROLLER"),
    _("SCALE SHOT"),
    _("METEOR BEAM"),
    _("SHELL SIDE ARM"),
    _("MISTY EXPLOSION"),
    _("GRASSY GLIDE"),
    _("RISING VOLTAGE"),
    _("TERRAIN PULSE"),
    _("SKITTER SMACK"),
    _("BURNING JEALOUSY"),
    _("LASH OUT"),
    _("POLTERGEIST"),
    _("CORROSIVE GAS"),
    _("COACHING"),
    _("FLIP TURN"),
    _("TRIPLE AXEL"),
    _("DUAL WINGBEAT"),
    _("SCORCHING SANDS"),
    _("JUNGLE HEALING"),
    _("WICKED BLOW"),
    _("SURGING STRIKES"),
    _("THUNDER CAGE"),
    _("DRAGON ENERGY"),
    _("FREEZING GLARE"),
    _("FIERY WRATH"),
    _("THUNDEROUS KICK"),
    _("GLACIAL LANCE"),
    _("ASTRAL BARRAGE"),
    _("EERIE SPELL"),
    _("COCOON"),
    _("MONOTYPE")
};//remember to remove comma from last entry //longest name is 17 chars
