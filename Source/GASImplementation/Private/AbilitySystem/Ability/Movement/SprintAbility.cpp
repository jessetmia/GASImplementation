// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Movement/SprintAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Effects/SprintEffect.h"
#include "GameplayTags/BaseTags.h"

USprintAbility::USprintAbility()
{
	SetTagData(BaseTags::Abilities::Movement::Sprint);
	ActivationBlockedTags.AddTag(BaseTags::State::Exhausted);
}
