// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/SprintEffect.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h"
#include "GameplayTags/BaseTags.h"

USprintEffect::USprintEffect()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	
	FGameplayTagRequirements AppRequirements;
	AppRequirements.RequireTags.AddTag(BaseTags::Abilities::Movement::Sprint);

	UTargetTagRequirementsGameplayEffectComponent* TargetReqsComponent =  CreateDefaultSubobject<UTargetTagRequirementsGameplayEffectComponent>(TEXT("TargetTagRequirementsGameplayEffectComponent"));
	TargetReqsComponent->ApplicationTagRequirements = AppRequirements;
	TargetReqsComponent->OngoingTagRequirements = AppRequirements;
	
	GEComponents.Add(TargetReqsComponent);
	
	FGameplayModifierInfo MovementSpeedModifier;
	MovementSpeedModifier.Attribute = UBaseAttributeSet::GetMovementSpeedAttribute();
	MovementSpeedModifier.ModifierOp = EGameplayModOp::Multiplicitive;
	MovementSpeedModifier.ModifierMagnitude = FScalableFloat(1.5f);
	Modifiers.Add(MovementSpeedModifier);

	FGameplayModifierInfo StaminaReductionModifier;
	StaminaReductionModifier.Attribute = UBaseAttributeSet::GetStaminaAttribute();
	StaminaReductionModifier.ModifierOp = EGameplayModOp::Additive;
	StaminaReductionModifier.ModifierMagnitude = FScalableFloat(-1.f);
	Modifiers.Add(StaminaReductionModifier);
}
