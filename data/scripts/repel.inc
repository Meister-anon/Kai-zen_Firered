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

EventScript_BwTrainerRepelWoreOff::
	lockall
	checkitem ITEM_BAD_ONION, 1
	compare VAR_RESULT, TRUE
	goto_if_ge EventScript_AnotherTrainerRepel
	goto EventScript_TrainerRepelWoreOff

EventScript_AnotherTrainerRepel::
	msgbox Text_BadOnionWoreOff, MSGBOX_SIGN
	msgbox Text_AskUseAnotherRepel MSGBOX_YESNO
	compare VAR_RESULT, TRUE
	goto_if_ne EventScript_EndScript
	checkitem ITEM_BAD_ONION, 1
	compare VAR_RESULT, TRUE
	goto_if_eq EventScript_UseAnotherBadOnion
	goto EventScript_EndScript

EventScript_AnotherRepel::
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
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
	setvar VAR_REPEL_STEP_COUNT 150
	setvar VAR_LAST_USED_REPEL	ITEM_REPEL
	goto EventScript_FinishNewRepel
	
EventScript_UseAnotherBadOnion::
	removeitem ITEM_BAD_ONION, 1
	setvar VAR_TRAINER_REPEL_STEP_COUNT 150	@if change this  need change item value as well in items.json
	goto EventScript_FinishNewRepel
	
EventScript_UseAnotherSuperRepel::
	removeitem ITEM_SUPER_REPEL, 1
	setvar VAR_REPEL_STEP_COUNT 150
	setvar VAR_LAST_USED_REPEL	ITEM_SUPER_REPEL
	goto EventScript_FinishNewRepel
	
EventScript_UseAnotherMaxRepel::
	removeitem ITEM_MAX_REPEL, 1
	setvar VAR_REPEL_STEP_COUNT 150
	setvar VAR_LAST_USED_REPEL	ITEM_MAX_REPEL
	goto EventScript_FinishNewRepel
	
EventScript_FinishNewRepel::
	playse SE_REPEL
	msgbox Text_UsedAnotherRepel MSGBOX_SIGN
	goto EventScript_EndScript
	
EventScript_RepelWoreOff:: @ 81BFB65
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end
	
EventScript_TrainerRepelWoreOff:: 
	msgbox Text_BadOnionWoreOff, MSGBOX_SIGN
	end

EventScript_EndScript::
	releaseall
	end

Text_RepelWoreOff:: @ 81BFB6E
	.string "REPEL's effect wore off…$"
	
Text_BadOnionWoreOff:: 
	.string "The strong smell has faded…$"


Text_UsedAnotherRepel::
	.string "{PLAYER} used a Repellent.$"

Text_AskUseAnotherRepel::
	.string "Would you like to use another REPEL?$"
