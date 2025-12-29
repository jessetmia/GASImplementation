// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "GameplayTags/BaseTags.h"

bool UBaseAbilitySystemComponent::IsCombatReady() const
{
	return HasMatchingGameplayTag(BaseTags::State::Combat::Ready);
}

bool UBaseAbilitySystemComponent::IsSprinting() const
{
	return HasMatchingGameplayTag(BaseTags::Abilities::Movement::Sprint);
}
