// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/ExhaustedEffect.h"
#include "GameplayEffect.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameplayEffectComponents/CancelAbilityTagsGameplayEffectComponent.h"
#include "GameplayTags/BaseTags.h"

UExhaustedEffect::UExhaustedEffect()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(5.0f);

	// Add Exhaustion State to ASC
	FInheritedTagContainer AddedTags;
	AddedTags.AddTag(BaseTags::State::Exhausted);
	UTargetTagsGameplayEffectComponent* TargetTagsComponent =  CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(TEXT("TargetTagsGameplayEffectComponent"));
	TargetTagsComponent->SetAndApplyTargetTagChanges(AddedTags);
	GEComponents.Add(TargetTagsComponent);

	// Cancel Sprint Ability if Active
	FInheritedTagContainer CancelWithTags;
	CancelWithTags.AddTag(BaseTags::Abilities::Movement::Sprint);
	FInheritedTagContainer EmptyTags; 
	UCancelAbilityTagsGameplayEffectComponent* CancelTagsComponent = CreateDefaultSubobject<UCancelAbilityTagsGameplayEffectComponent>(TEXT("CancelTagsGameplayEffectComponent"));
	CancelTagsComponent->SetAndApplyCanceledAbilityTagChanges(CancelWithTags, EmptyTags);
	GEComponents.Add(CancelTagsComponent);
}
