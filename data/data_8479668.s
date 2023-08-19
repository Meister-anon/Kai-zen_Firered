#include "constants/species.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/easy_chat.h"
#include "constants/facility_trainer_classes.h"

#define MALE 0
#define FEMALE 1
#define NULL 0

	.include "asm/macros.inc"

	.section .rodata

	@ 847ABAC
.align 2
	.include "data/trainer_tower/trainers.inc"

	.align 2, 0
