// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/InitializeBaseAttributes.h"

#include "AbilitySystem/BaseAttributeSet.h"

UInitializeBaseAttributes::UInitializeBaseAttributes()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Add modifier for MaxStamina
	FGameplayModifierInfo MaxStaminaModifier;
	MaxStaminaModifier.Attribute = UBaseAttributeSet::GetMaxStaminaAttribute();
	MaxStaminaModifier.ModifierOp = EGameplayModOp::Override;
	MaxStaminaModifier.ModifierMagnitude = FScalableFloat(100.0f);
	Modifiers.Add(MaxStaminaModifier);

	// Add modifier for Stamina
	FGameplayModifierInfo StaminaModifier;
	StaminaModifier.Attribute = UBaseAttributeSet::GetStaminaAttribute();
	StaminaModifier.ModifierOp = EGameplayModOp::Override;
	StaminaModifier.ModifierMagnitude = FScalableFloat(100.0f);
	Modifiers.Add(StaminaModifier);

	// Add modifier for MovementSpeed
	FGameplayModifierInfo MovementSpeedModifier;
	MovementSpeedModifier.Attribute = UBaseAttributeSet::GetMovementSpeedAttribute();
	MovementSpeedModifier.ModifierOp = EGameplayModOp::Override;
	MovementSpeedModifier.ModifierMagnitude = FScalableFloat(600.0f);
	Modifiers.Add(MovementSpeedModifier);
}
