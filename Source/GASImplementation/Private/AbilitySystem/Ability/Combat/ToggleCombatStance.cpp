// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Combat/ToggleCombatStance.h"

#include "GameplayTags/BaseTags.h"

UToggleCombatStance::UToggleCombatStance()
{
	SetTagData(BaseTags::Abilities::Categories::CombatStance);
	ActivationBlockedTags.AddTag(BaseTags::Abilities::CrowdControl::Stunned);
}
