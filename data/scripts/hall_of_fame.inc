EventScript_SetDefeatedEliteFourFlagsVars:: @ 81A651A
	clearflag FLAG_HIDE_POSTGAME_GOSSIPERS
	call EventScript_ResetEliteFour
	special Script_UpdateTrainerFanClubGameClear
	call_if_unset FLAG_BECAME_LEAGUE_CHAMPION, EventScript_SetReadyTryGiveNationalDexScene
	@specialvar VAR_RESULT, IsNationalPokedexEnabled
	@compare VAR_RESULT, FALSE
	@call_if_eq EventScript_SetReadyTryGiveNationalDexScene	@if get nat dex in elite four, think replace all special progression checks to eite four clear flag checks intead then can give nat dex at start
	call EventScript_ResetLegendaries		@vsonic plan change this to time based rather than needing to fight elite four, well could do both,
	return					@if you want them back faster you have to beat the elite four challenge.

EventScript_SetReadyTryGiveNationalDexScene:: @ 81A653B
	@setvar VAR_MAP_SCENE_PALLET_TOWN_OAK, 2	@if I give nat dex from start guess I just block this var
	setflag FLAG_BECAME_LEAGUE_CHAMPION	@progression replacement
	return

EventScript_ResetLegendaries:: @ 81A6541
	clearflag FLAG_LUGIA_FLEW_AWAY
	clearflag FLAG_HO_OH_FLEW_AWAY
	clearflag FLAG_DEOXYS_FLEW_AWAY	@what does this mean for legendary birds?
	return

EventScript_ResetEliteFourEnd:: @ 81A654B
	call EventScript_ResetEliteFour
	end

EventScript_ResetEliteFour:: @ 81A6551
	clearflag FLAG_DEFEATED_LORELEI
	clearflag FLAG_DEFEATED_BRUNO
	clearflag FLAG_DEFEATED_AGATHA
	clearflag FLAG_DEFEATED_LANCE
	clearflag FLAG_DEFEATED_CHAMP
	cleartrainerflag TRAINER_CHAMPION_FIRST_SQUIRTLE
	cleartrainerflag TRAINER_CHAMPION_FIRST_BULBASAUR
	cleartrainerflag TRAINER_CHAMPION_FIRST_CHARMANDER
	cleartrainerflag TRAINER_CHAMPION_REMATCH_SQUIRTLE
	cleartrainerflag TRAINER_CHAMPION_REMATCH_BULBASAUR
	cleartrainerflag TRAINER_CHAMPION_REMATCH_CHARMANDER
	setvar VAR_MAP_SCENE_POKEMON_LEAGUE, 0
	return
