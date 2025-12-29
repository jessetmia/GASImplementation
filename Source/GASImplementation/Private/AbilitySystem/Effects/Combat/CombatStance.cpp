// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/Combat/CombatStance.h"

#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameplayTags/BaseTags.h"

UCombatStance::UCombatStance()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	
	FGameplayTagRequirements AppRequirements;
	AppRequirements.RequireTags.AddTag(BaseTags::Abilities::Categories::CombatStance);

	UTargetTagRequirementsGameplayEffectComponent* TargetReqsComponent =  CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirementsGameplayEffectComponent"));
	TargetReqsComponent->ApplicationTagRequirements = AppRequirements;
	TargetReqsComponent->OngoingTagRequirements = AppRequirements;
	GEComponents.Add(TargetReqsComponent);

	FInheritedTagContainer AddedTags;
	AddedTags.AddTag(BaseTags::State::Combat::Ready);
	UTargetTagsGameplayEffectComponent* TargetTagsComponent =  CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(TEXT("TargetTagsGameplayEffectComponent"));
	TargetTagsComponent->SetAndApplyTargetTagChanges(AddedTags);
	GEComponents.Add(TargetTagsComponent);
}
