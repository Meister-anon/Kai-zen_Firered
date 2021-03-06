EventScript_BwRepelWoreOff::
	lockall
	checkitem ITEM_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_ge EventScript_AnotherRepel
	checkitem ITEM_SUPER_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_ge EventScript_AnotherRepel
	checkitem ITEM_MAX_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_ge EventScript_AnotherRepel
	goto EventScript_RepelWoreOff
	
EventScript_AnotherRepel::
	msgbox Text_AskUseAnotherRepel MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_EndScript
	checkitem ITEM_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_UseAnotherRepel
	checkitem ITEM_SUPER_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_UseAnotherSuperRepel
	checkitem ITEM_MAX_REPEL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_UseAnotherMaxRepel
	goto EventScript_EndScript
	
EventScript_UseAnotherRepel::
	removeitem ITEM_REPEL, 1
	setvar VAR_REPEL_STEP_COUNT 100
	goto EventScript_FinishNewRepel
	
EventScript_UseAnotherSuperRepel::
	removeitem ITEM_SUPER_REPEL, 1
	setvar VAR_REPEL_STEP_COUNT 200
	goto EventScript_FinishNewRepel
	
EventScript_UseAnotherMaxRepel::
	removeitem ITEM_MAX_REPEL, 1
	setvar VAR_REPEL_STEP_COUNT 250
	goto EventScript_FinishNewRepel
	
EventScript_FinishNewRepel::
	playse SE_REPEL
	msgbox Text_UsedAnotherRepel MSGBOX_SIGN
	goto EventScript_EndScript
	
EventScript_RepelWoreOff:: @ 81BFB65
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

EventScript_EndScript::
	releaseall
	end

Text_RepelWoreOff:: @ 81BFB6E
	.string "REPEL's effect wore off.$"


Text_UsedAnotherRepel::
	.string "{PLAYER} used a Repellent.$"

Text_AskUseAnotherRepel::
	.string "Would you like to use another REPEL?$"
