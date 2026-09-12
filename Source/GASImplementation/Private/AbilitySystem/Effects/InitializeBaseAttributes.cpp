// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/InitializeBaseAttributes.h"
#include "AbilitySystem/AttributeSets/MovementAttributeSet.h"
#include "AbilitySystem/AttributeSets/StaminaAttributeSet.h"

UInitializeBaseAttributes::UInitializeBaseAttributes()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Add modifier for MaxStamina
	FGameplayModifierInfo MaxStaminaModifier;
	MaxStaminaModifier.Attribute = UStaminaAttributeSet::GetMaxStaminaAttribute();
	MaxStaminaModifier.ModifierOp = EGameplayModOp::Override;
	MaxStaminaModifier.ModifierMagnitude = FScalableFloat(100.0f);
	Modifiers.Add(MaxStaminaModifier);
	
	// Add modifier for Stamina
	FGameplayModifierInfo StaminaModifier;
	StaminaModifier.Attribute = UStaminaAttributeSet::GetStaminaAttribute();
	StaminaModifier.ModifierOp = EGameplayModOp::Override;
	StaminaModifier.ModifierMagnitude = FScalableFloat(100.0f);
	Modifiers.Add(StaminaModifier);

	// Add modifier for MovementSpeed
	FGameplayModifierInfo MovementSpeedModifier;
	MovementSpeedModifier.Attribute = UMovementAttributeSet::GetMovementSpeedAttribute();
	MovementSpeedModifier.ModifierOp = EGameplayModOp::Override;
	MovementSpeedModifier.ModifierMagnitude = FScalableFloat(500.0f);
	Modifiers.Add(MovementSpeedModifier);
}
