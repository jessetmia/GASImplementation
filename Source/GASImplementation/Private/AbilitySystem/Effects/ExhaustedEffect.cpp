// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/ExhaustedEffect.h"
#include "GameplayEffect.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameplayTags/BaseTags.h"

UExhaustedEffect::UExhaustedEffect()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(5.0f);

	FInheritedTagContainer AddedTags;
	AddedTags.AddTag(BaseTags::State::Exhausted);
	UTargetTagsGameplayEffectComponent* TargetTagsComponent =  CreateDefaultSubobject<UTargetTagsGameplayEffectComponent>(TEXT("TargetTagsGameplayEffectComponent"));
	TargetTagsComponent->SetAndApplyTargetTagChanges(AddedTags);

	GEComponents.Add(TargetTagsComponent);
}
