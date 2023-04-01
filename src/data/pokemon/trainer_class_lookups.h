// TODO: document trainer pic indices with macro
const u8 gFacilityClassToPicIndex[] =
{
    [FACILITY_CLASS_AQUA_LEADER] = 0,
    [FACILITY_CLASS_TEAM_AQUA] = 1,
    [FACILITY_CLASS_TEAM_AQUA_2] = 2,
    [FACILITY_CLASS_AROMA_LADY] = 3,
    [FACILITY_CLASS_RUIN_MANIAC] = 4,
    [FACILITY_CLASS_INTERVIEWER] = 5,
    [FACILITY_CLASS_TUBER] = 6,
    [FACILITY_CLASS_TUBER_2] = 7,
    [FACILITY_CLASS_COOLTRAINER] = 8,
    [FACILITY_CLASS_COOLTRAINER_2] = 9,
    [FACILITY_CLASS_HEX_MANIAC] = 10,
    [FACILITY_CLASS_LADY] = 11,
    [FACILITY_CLASS_BEAUTY] = 12,
    [FACILITY_CLASS_RICH_BOY] = 13,
    [FACILITY_CLASS_POKEMANIAC] = 14,
    [FACILITY_CLASS_SWIMMER_MALE] = 15,
    [FACILITY_CLASS_BLACK_BELT] = 16,
    [FACILITY_CLASS_GUITARIST] = 17,
    [FACILITY_CLASS_KINDLER] = 18,
    [FACILITY_CLASS_CAMPER] = 19,
    [FACILITY_CLASS_BUG_MANIAC] = 20,
    [FACILITY_CLASS_PSYCHIC] = 21,
    [FACILITY_CLASS_PSYCHIC_2] = 22,
    [FACILITY_CLASS_GENTLEMAN] = 23,
    [FACILITY_CLASS_ELITE_FOUR] = 24,
    [FACILITY_CLASS_ELITE_FOUR_2] = 25,
    [FACILITY_CLASS_LEADER] = 26,
    [FACILITY_CLASS_LEADER_2] = 27,
    [FACILITY_CLASS_LEADER_3] = 28,
    [FACILITY_CLASS_SCHOOL_KID] = 29,
    [FACILITY_CLASS_SCHOOL_KID_2] = 30,
    [FACILITY_CLASS_SR_AND_JR] = 31,
    [FACILITY_CLASS_POKEFAN] = 32,
    [FACILITY_CLASS_POKEFAN_2] = 33,
    [FACILITY_CLASS_EXPERT] = 34,
    [FACILITY_CLASS_EXPERT_2] = 35,
    [FACILITY_CLASS_YOUNGSTER] = 36,
    [FACILITY_CLASS_CHAMPION] = 37,
    [FACILITY_CLASS_FISHERMAN] = 38,
    [FACILITY_CLASS_TRIATHLETE] = 39,
    [FACILITY_CLASS_TRIATHLETE_2] = 40,
    [FACILITY_CLASS_TRIATHLETE_3] = 41,
    [FACILITY_CLASS_TRIATHLETE_4] = 42,
    [FACILITY_CLASS_TRIATHLETE_5] = 43,
    [FACILITY_CLASS_TRIATHLETE_6] = 44,
    [FACILITY_CLASS_DRAGON_TAMER] = 45,
    [FACILITY_CLASS_BIRD_KEEPER] = 46,
    [FACILITY_CLASS_NINJA_BOY] = 47,
    [FACILITY_CLASS_BATTLE_GIRL] = 48,
    [FACILITY_CLASS_PARASOL_LADY] = 49,
    [FACILITY_CLASS_SWIMMER_FEMALE] = 50,
    [FACILITY_CLASS_PICNICKER] = 51,
    [FACILITY_CLASS_TWINS] = 52,
    [FACILITY_CLASS_SAILOR] = 53,
    [FACILITY_CLASS_BOARDER] = 36,
    [FACILITY_CLASS_BOARDER_2] = 36,
    [FACILITY_CLASS_COLLECTOR] = 54,
    [FACILITY_CLASS_PKMN_TRAINER] = 55,
    [FACILITY_CLASS_PKMN_TRAINER_2] = 56,
    [FACILITY_CLASS_PKMN_TRAINER_3] = 56,
    [FACILITY_CLASS_PKMN_TRAINER_4] = 56,
    [FACILITY_CLASS_PKMN_TRAINER_5] = 57,
    [FACILITY_CLASS_PKMN_TRAINER_6] = 57,
    [FACILITY_CLASS_PKMN_TRAINER_7] = 57,
    [FACILITY_CLASS_PKMN_BREEDER] = 58,
    [FACILITY_CLASS_PKMN_BREEDER_2] = 59,
    [FACILITY_CLASS_PKMN_RANGER] = 60,
    [FACILITY_CLASS_PKMN_RANGER_2] = 61,
    [FACILITY_CLASS_MAGMA_LEADER] = 62,
    [FACILITY_CLASS_TEAM_MAGMA] = 63,
    [FACILITY_CLASS_TEAM_MAGMA_2] = 64,
    [FACILITY_CLASS_LASS] = 65,
    [FACILITY_CLASS_BUG_CATCHER] = 66,
    [FACILITY_CLASS_HIKER] = 67,
    [FACILITY_CLASS_YOUNG_COUPLE] = 68,
    [FACILITY_CLASS_OLD_COUPLE] = 69,
    [FACILITY_CLASS_SIS_AND_BRO] = 70,
    [FACILITY_CLASS_AQUA_ADMIN] = 71,
    [FACILITY_CLASS_AQUA_ADMIN_2] = 72,
    [FACILITY_CLASS_MAGMA_ADMIN] = 73,
    [FACILITY_CLASS_MAGMA_ADMIN_2] = 74,
    [FACILITY_CLASS_LEADER_4] = 75,
    [FACILITY_CLASS_LEADER_5] = 76,
    [FACILITY_CLASS_LEADER_6] = 77,
    [FACILITY_CLASS_LEADER_7] = 78,
    [FACILITY_CLASS_LEADER_8] = 79,
    [FACILITY_CLASS_ELITE_FOUR_3] = 80,
    [FACILITY_CLASS_ELITE_FOUR_4] = 81,
    [FACILITY_CLASS_YOUNGSTER_2] = 82,
    [FACILITY_CLASS_BUG_CATCHER_2] = 83,
    [FACILITY_CLASS_LASS_2] = 84,
    [FACILITY_CLASS_SAILOR_2] = 85,
    [FACILITY_CLASS_CAMPER_2] = 86,
    [FACILITY_CLASS_PICNICKER_2] = 87,
    [FACILITY_CLASS_POKEMANIAC_2] = 88,
    [FACILITY_CLASS_SUPER_NERD] = 89,
    [FACILITY_CLASS_HIKER_2] = 90,
    [FACILITY_CLASS_BIKER] = 91,
    [FACILITY_CLASS_BURGLAR] = 92,
    [FACILITY_CLASS_ENGINEER] = 93,
    [FACILITY_CLASS_FISHERMAN_2] = 94,
    [FACILITY_CLASS_SWIMMER_MALE_2] = 95,
    [FACILITY_CLASS_CUE_BALL] = 96,
    [FACILITY_CLASS_GAMER] = 97,
    [FACILITY_CLASS_BEAUTY_2] = 98,
    [FACILITY_CLASS_SWIMMER_FEMALE_2] = 99,
    [FACILITY_CLASS_PSYCHIC_3] = 100,
    [FACILITY_CLASS_ROCKER] = 101,
    [FACILITY_CLASS_JUGGLER] = 102,
    [FACILITY_CLASS_TAMER] = 103,
    [FACILITY_CLASS_BIRD_KEEPER_2] = 104,
    [FACILITY_CLASS_BLACK_BELT_2] = 105,
    [FACILITY_CLASS_RIVAL] = 106,
    [FACILITY_CLASS_SCIENTIST] = 107,
    [FACILITY_CLASS_BOSS] = 108,
    [FACILITY_CLASS_TEAM_ROCKET] = 109,
    [FACILITY_CLASS_COOLTRAINER_3] = 110,
    [FACILITY_CLASS_COOLTRAINER_4] = 111,
    [FACILITY_CLASS_ELITE_FOUR_5] = 112,
    [FACILITY_CLASS_ELITE_FOUR_6] = 113,
    [FACILITY_CLASS_LEADER_9] = 116,
    [FACILITY_CLASS_LEADER_10] = 117,
    [FACILITY_CLASS_GENTLEMAN_2] = 123,
    [FACILITY_CLASS_RIVAL_2] = 124,
    [FACILITY_CLASS_CHAMPION_2] = 125,
    [FACILITY_CLASS_CHANNELER] = 126,
    [FACILITY_CLASS_TWINS_2] = 127,
    [FACILITY_CLASS_COOL_COUPLE] = 128,
    [FACILITY_CLASS_YOUNG_COUPLE_2] = 129,
    [FACILITY_CLASS_CRUSH_KIN] = 130,
    [FACILITY_CLASS_SIS_AND_BRO_2] = 131,
    [FACILITY_CLASS_PKMN_PROF] = 132,
    [FACILITY_CLASS_BRENDAN] = TRAINER_PIC_RS_BRENDAN_2,
    [FACILITY_CLASS_MAY] = TRAINER_PIC_RS_MAY_2,
    [FACILITY_CLASS_RED] = TRAINER_PIC_RED,
    [FACILITY_CLASS_LEAF] = TRAINER_PIC_LEAF,
    [FACILITY_CLASS_TEAM_ROCKET_2] = 137,
    [FACILITY_CLASS_PSYCHIC_4] = 138,
    [FACILITY_CLASS_CRUSH_GIRL] = 139,
    [FACILITY_CLASS_TUBER_3] = 140,
    [FACILITY_CLASS_PKMN_BREEDER_3] = 141,
    [FACILITY_CLASS_PKMN_RANGER_3] = 142,
    [FACILITY_CLASS_PKMN_RANGER_4] = 143,
    [FACILITY_CLASS_AROMA_LADY_2] = 144,
    [FACILITY_CLASS_RUIN_MANIAC_2] = 145,
    [FACILITY_CLASS_LADY_2] = 146,
    [FACILITY_CLASS_PAINTER] = 147,
    [FACILITY_CLASS_ELITE_FOUR_7] = 114,
    [FACILITY_CLASS_ELITE_FOUR_8] = 115,
    [FACILITY_CLASS_CHAMPION_3] = 125,
};//bug fix done

const u8 gFacilityClassToTrainerClass[] =
{
    [FACILITY_CLASS_AQUA_LEADER] = CLASS_AQUA_LEADER,
    [FACILITY_CLASS_TEAM_AQUA] = CLASS_TEAM_AQUA,
    [FACILITY_CLASS_TEAM_AQUA_2] = CLASS_TEAM_AQUA,
    [FACILITY_CLASS_AROMA_LADY] = CLASS_AROMA_LADY,
    [FACILITY_CLASS_RUIN_MANIAC] = CLASS_RUIN_MANIAC,
    [FACILITY_CLASS_INTERVIEWER] = CLASS_INTERVIEWER,
    [FACILITY_CLASS_TUBER] = CLASS_TUBER,
    [FACILITY_CLASS_TUBER_2] = CLASS_TUBER_2,
    [FACILITY_CLASS_COOLTRAINER] = CLASS_COOLTRAINER,
    [FACILITY_CLASS_COOLTRAINER_2] = CLASS_COOLTRAINER,
    [FACILITY_CLASS_HEX_MANIAC] = CLASS_HEX_MANIAC,
    [FACILITY_CLASS_LADY] = CLASS_LADY,
    [FACILITY_CLASS_BEAUTY] = CLASS_BEAUTY,
    [FACILITY_CLASS_RICH_BOY] = CLASS_RICH_BOY,
    [FACILITY_CLASS_POKEMANIAC] = CLASS_POKEMANIAC,
    [FACILITY_CLASS_SWIMMER_MALE] = CLASS_SWIMMER_MALE,
    [FACILITY_CLASS_BLACK_BELT] = CLASS_BLACK_BELT,
    [FACILITY_CLASS_GUITARIST] = CLASS_GUITARIST,
    [FACILITY_CLASS_KINDLER] = CLASS_KINDLER,
    [FACILITY_CLASS_CAMPER] = CLASS_CAMPER,
    [FACILITY_CLASS_BUG_MANIAC] = CLASS_BUG_MANIAC,
    [FACILITY_CLASS_PSYCHIC] = CLASS_PSYCHIC,
    [FACILITY_CLASS_PSYCHIC_2] = CLASS_PSYCHIC,
    [FACILITY_CLASS_GENTLEMAN] = CLASS_GENTLEMAN,
    [FACILITY_CLASS_ELITE_FOUR] = CLASS_ELITE_FOUR,
    [FACILITY_CLASS_ELITE_FOUR_2] = CLASS_ELITE_FOUR,
    [FACILITY_CLASS_LEADER] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_2] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_3] = CLASS_LEADER,
    [FACILITY_CLASS_SCHOOL_KID] = CLASS_SCHOOL_KID,
    [FACILITY_CLASS_SCHOOL_KID_2] = CLASS_SCHOOL_KID,
    [FACILITY_CLASS_SR_AND_JR] = CLASS_SR_AND_JR,
    [FACILITY_CLASS_POKEFAN] = CLASS_POKEFAN,
    [FACILITY_CLASS_POKEFAN_2] = CLASS_POKEFAN,
    [FACILITY_CLASS_EXPERT] = CLASS_EXPERT,
    [FACILITY_CLASS_EXPERT_2] = CLASS_EXPERT,
    [FACILITY_CLASS_YOUNGSTER] = CLASS_YOUNGSTER,
    [FACILITY_CLASS_CHAMPION] = CLASS_CHAMPION,
    [FACILITY_CLASS_FISHERMAN] = CLASS_FISHERMAN,
    [FACILITY_CLASS_TRIATHLETE] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_TRIATHLETE_2] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_TRIATHLETE_3] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_TRIATHLETE_4] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_TRIATHLETE_5] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_TRIATHLETE_6] = CLASS_TRIATHLETE,
    [FACILITY_CLASS_DRAGON_TAMER] = CLASS_DRAGON_TAMER,
    [FACILITY_CLASS_BIRD_KEEPER] = CLASS_BIRD_KEEPER,
    [FACILITY_CLASS_NINJA_BOY] = CLASS_NINJA_BOY,
    [FACILITY_CLASS_BATTLE_GIRL] = CLASS_BATTLE_GIRL,
    [FACILITY_CLASS_PARASOL_LADY] = CLASS_PARASOL_LADY,
    [FACILITY_CLASS_SWIMMER_FEMALE] = CLASS_SWIMMER_FEMALE,
    [FACILITY_CLASS_PICNICKER] = CLASS_PICNICKER,
    [FACILITY_CLASS_TWINS] = CLASS_TWINS,
    [FACILITY_CLASS_SAILOR] = CLASS_SAILOR,
    [FACILITY_CLASS_BOARDER] = CLASS_BOARDER,
    [FACILITY_CLASS_BOARDER_2] = CLASS_BOARDER,
    [FACILITY_CLASS_COLLECTOR] = CLASS_COLLECTOR,
    [FACILITY_CLASS_PKMN_TRAINER] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_2] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_3] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_4] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_5] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_6] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_TRAINER_7] = CLASS_PKMN_TRAINER_3,
    [FACILITY_CLASS_PKMN_BREEDER] = CLASS_PKMN_BREEDER,
    [FACILITY_CLASS_PKMN_BREEDER_2] = CLASS_PKMN_BREEDER,
    [FACILITY_CLASS_PKMN_RANGER] = CLASS_PKMN_RANGER,
    [FACILITY_CLASS_PKMN_RANGER_2] = CLASS_PKMN_RANGER,
    [FACILITY_CLASS_MAGMA_LEADER] = CLASS_MAGMA_LEADER,
    [FACILITY_CLASS_TEAM_MAGMA] = CLASS_TEAM_MAGMA,
    [FACILITY_CLASS_TEAM_MAGMA_2] = CLASS_TEAM_MAGMA,
    [FACILITY_CLASS_LASS] = CLASS_LASS,
    [FACILITY_CLASS_BUG_CATCHER] = CLASS_BUG_CATCHER,
    [FACILITY_CLASS_HIKER] = CLASS_HIKER,
    [FACILITY_CLASS_YOUNG_COUPLE] = CLASS_YOUNG_COUPLE,
    [FACILITY_CLASS_OLD_COUPLE] = CLASS_OLD_COUPLE,
    [FACILITY_CLASS_SIS_AND_BRO] = CLASS_SIS_AND_BRO,
    [FACILITY_CLASS_AQUA_ADMIN] = CLASS_AQUA_ADMIN,
    [FACILITY_CLASS_AQUA_ADMIN_2] = CLASS_AQUA_ADMIN,
    [FACILITY_CLASS_MAGMA_ADMIN] = CLASS_MAGMA_ADMIN,
    [FACILITY_CLASS_MAGMA_ADMIN_2] = CLASS_MAGMA_ADMIN,
    [FACILITY_CLASS_LEADER_4] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_5] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_6] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_7] = CLASS_LEADER,
    [FACILITY_CLASS_LEADER_8] = CLASS_LEADER,
    [FACILITY_CLASS_ELITE_FOUR_3] = CLASS_ELITE_FOUR,
    [FACILITY_CLASS_ELITE_FOUR_4] = CLASS_ELITE_FOUR,
    [FACILITY_CLASS_YOUNGSTER_2] = CLASS_YOUNGSTER_2,
    [FACILITY_CLASS_BUG_CATCHER_2] = CLASS_BUG_CATCHER_2,
    [FACILITY_CLASS_LASS_2] = CLASS_LASS_2,
    [FACILITY_CLASS_SAILOR_2] = CLASS_SAILOR_2,
    [FACILITY_CLASS_CAMPER_2] = CLASS_CAMPER_2,
    [FACILITY_CLASS_PICNICKER_2] = CLASS_PICNICKER_2,
    [FACILITY_CLASS_POKEMANIAC_2] = CLASS_POKEMANIAC_2,
    [FACILITY_CLASS_SUPER_NERD] = CLASS_SUPER_NERD,
    [FACILITY_CLASS_HIKER_2] = CLASS_HIKER_2,
    [FACILITY_CLASS_BIKER] = CLASS_BIKER,
    [FACILITY_CLASS_BURGLAR] = CLASS_BURGLAR,
    [FACILITY_CLASS_ENGINEER] = CLASS_ENGINEER,
    [FACILITY_CLASS_FISHERMAN_2] = CLASS_FISHERMAN_2,
    [FACILITY_CLASS_SWIMMER_MALE_2] = CLASS_SWIMMER_MALE_2,
    [FACILITY_CLASS_CUE_BALL] = CLASS_CUE_BALL,
    [FACILITY_CLASS_GAMER] = CLASS_GAMER,
    [FACILITY_CLASS_BEAUTY_2] = CLASS_BEAUTY_2,
    [FACILITY_CLASS_SWIMMER_FEMALE_2] = CLASS_SWIMMER_FEMALE_2,
    [FACILITY_CLASS_PSYCHIC_3] = CLASS_PSYCHIC_2,
    [FACILITY_CLASS_ROCKER] = CLASS_ROCKER,
    [FACILITY_CLASS_JUGGLER] = CLASS_JUGGLER,
    [FACILITY_CLASS_TAMER] = CLASS_TAMER,
    [FACILITY_CLASS_BIRD_KEEPER_2] = CLASS_BIRD_KEEPER_2,
    [FACILITY_CLASS_BLACK_BELT_2] = CLASS_BLACK_BELT_2,
    [FACILITY_CLASS_RIVAL] = CLASS_RIVAL,
    [FACILITY_CLASS_SCIENTIST] = CLASS_SCIENTIST,
    [FACILITY_CLASS_BOSS] = CLASS_BOSS,
    [FACILITY_CLASS_TEAM_ROCKET] = CLASS_TEAM_ROCKET,
    [FACILITY_CLASS_COOLTRAINER_3] = CLASS_COOLTRAINER_2,
    [FACILITY_CLASS_COOLTRAINER_4] = CLASS_COOLTRAINER_2,
    [FACILITY_CLASS_ELITE_FOUR_5] = CLASS_ELITE_FOUR_2,
    [FACILITY_CLASS_ELITE_FOUR_6] = CLASS_ELITE_FOUR_2,
    [FACILITY_CLASS_LEADER_9] = CLASS_LEADER_2,
    [FACILITY_CLASS_LEADER_10] = CLASS_LEADER_2,
    [FACILITY_CLASS_GENTLEMAN_2] = CLASS_GENTLEMAN_2,
    [FACILITY_CLASS_RIVAL_2] = CLASS_RIVAL_2,
    [FACILITY_CLASS_CHAMPION_2] = CLASS_CHAMPION_2,
    [FACILITY_CLASS_CHANNELER] = CLASS_CHANNELER,
    [FACILITY_CLASS_TWINS_2] = CLASS_TWINS_2,
    [FACILITY_CLASS_COOL_COUPLE] = CLASS_COOL_COUPLE,
    [FACILITY_CLASS_YOUNG_COUPLE_2] = CLASS_YOUNG_COUPLE_2,
    [FACILITY_CLASS_CRUSH_KIN] = CLASS_CRUSH_KIN,
    [FACILITY_CLASS_SIS_AND_BRO_2] = CLASS_SIS_AND_BRO_2,
    [FACILITY_CLASS_PKMN_PROF] = CLASS_PKMN_PROF,
    [FACILITY_CLASS_BRENDAN] = CLASS_PLAYER,
    [FACILITY_CLASS_MAY] = CLASS_PLAYER,
    [FACILITY_CLASS_RED] = CLASS_PLAYER,
    [FACILITY_CLASS_LEAF] = CLASS_PLAYER,
    [FACILITY_CLASS_TEAM_ROCKET_2] = CLASS_TEAM_ROCKET,
    [FACILITY_CLASS_PSYCHIC_4] = CLASS_PSYCHIC_2,
    [FACILITY_CLASS_CRUSH_GIRL] = CLASS_CRUSH_GIRL,
    [FACILITY_CLASS_TUBER_3] = CLASS_TUBER_3,
    [FACILITY_CLASS_PKMN_BREEDER_3] = CLASS_PKMN_BREEDER_2,
    [FACILITY_CLASS_PKMN_RANGER_3] = CLASS_PKMN_RANGER_2,
    [FACILITY_CLASS_PKMN_RANGER_4] = CLASS_PKMN_RANGER_2,
    [FACILITY_CLASS_AROMA_LADY_2] = CLASS_AROMA_LADY_2,
    [FACILITY_CLASS_RUIN_MANIAC_2] = CLASS_RUIN_MANIAC_2,
    [FACILITY_CLASS_LADY_2] = CLASS_LADY_2,
    [FACILITY_CLASS_PAINTER] = CLASS_PAINTER,
    [FACILITY_CLASS_ELITE_FOUR_7] = CLASS_ELITE_FOUR_2,
    [FACILITY_CLASS_ELITE_FOUR_8] = CLASS_ELITE_FOUR_2,
    [FACILITY_CLASS_CHAMPION_3] = CLASS_CHAMPION_2,
};
