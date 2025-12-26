// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Movement/BaseCharacterMovementComponent.h"
#include "Character/BaseCharacter.h"

float UBaseCharacterMovementComponent::GetMaxSpeed() const
{
	switch(MovementMode)
	{
	case MOVE_Walking: return CalculateMaxRunSpeed();
	default: return Super::GetMaxSpeed();
	}
}

float UBaseCharacterMovementComponent::CalculateMaxRunSpeed() const
{
	
	const ABaseCharacter* Char = Cast<ABaseCharacter>(GetCharacterOwner());

	if (!IsValid(Char)) return MaxWalkSpeed;

	if (MovementMode != MOVE_Walking  && MovementMode != MOVE_NavWalking) return Super::GetMaxSpeed();

	const FVector CurrentAcceleration = Acceleration;
    
	if (CurrentAcceleration.IsNearlyZero()) return MaxWalkSpeed;

	const FVector ActorForward = Char->GetActorForwardVector();

	const FVector MovementDirection = CurrentAcceleration.GetSafeNormal();
	const float DotProduct = FVector::DotProduct(MovementDirection, ActorForward);

	if (DotProduct < 0.0f) return MaxWalkSpeed * BackwardSpeedMultiplier;

	const float AbsDot = FMath::Abs(DotProduct);
	if (AbsDot < DiagonalThreshold) // Mostly sideways
	{
		return MaxWalkSpeed * StrafeSpeedMultiplier; // Slower than forward, faster than backward
	}
	
	return MaxWalkSpeed;
}
