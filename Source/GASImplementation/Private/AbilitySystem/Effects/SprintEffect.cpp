// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/SprintEffect.h"
#include "AbilitySystem/AttributeSets/MovementAttributeSet.h"
#include "AbilitySystem/AttributeSets/StaminaAttributeSet.h"
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
}

USprintSpeedEffect::USprintSpeedEffect()
{
	FGameplayModifierInfo MovementSpeedModifier;
	MovementSpeedModifier.Attribute = UMovementAttributeSet::GetMovementSpeedAttribute();
	MovementSpeedModifier.ModifierOp = EGameplayModOp::Multiplicitive;
	MovementSpeedModifier.ModifierMagnitude = FScalableFloat(1.5f);
	Modifiers.Add(MovementSpeedModifier);
}

USprintStaminaDrainEffect::USprintStaminaDrainEffect()
{
	Period = 1.f;
	bExecutePeriodicEffectOnApplication = true;
	
	FGameplayModifierInfo StaminaReductionModifier;
	StaminaReductionModifier.Attribute = UStaminaAttributeSet::GetStaminaAttribute();
	StaminaReductionModifier.ModifierOp = EGameplayModOp::Additive;
	StaminaReductionModifier.ModifierMagnitude = FScalableFloat(-1.f);
	Modifiers.Add(StaminaReductionModifier);
}
