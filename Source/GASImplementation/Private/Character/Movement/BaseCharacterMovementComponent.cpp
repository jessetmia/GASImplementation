// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Movement/BaseCharacterMovementComponent.h"
#include "Character/BaseCharacter.h"

float UBaseCharacterMovementComponent::GetMaxSpeed() const
{
	switch(MovementMode)
	{
	case MOVE_Walking:
	case MOVE_NavWalking: return CalculateMaxRunSpeed();
	default: return Super::GetMaxSpeed();
	}
}

float UBaseCharacterMovementComponent::CalculateMaxRunSpeed() const
{
	
	const float BaseSpeed = MaxWalkSpeed;
	const ABaseCharacter* Char = Cast<ABaseCharacter>(GetCharacterOwner());

	if (!IsValid(Char)) return MaxWalkSpeed;

	if (MovementMode != MOVE_Walking  && MovementMode != MOVE_NavWalking) return MaxWalkSpeed;
	
	const FVector CurrentAcceleration = Acceleration;
	if (CurrentAcceleration.IsNearlyZero()) return BaseSpeed;
	
	const FVector ActorForward = Char->GetActorForwardVector();
	
	const FVector MovementDirection = CurrentAcceleration.GetSafeNormal();
	const float DotProduct = FVector::DotProduct(MovementDirection, ActorForward);
	
	if (DotProduct < -0.2f) return BaseSpeed * BackwardSpeedMultiplier;
	
	const float AbsDot = FMath::Abs(DotProduct);
	if (AbsDot < DiagonalThreshold) // Mostly sideways
	{
		return BaseSpeed * StrafeSpeedMultiplier; // Slower than forward, faster than backward
	}
	
	return BaseSpeed;
}
