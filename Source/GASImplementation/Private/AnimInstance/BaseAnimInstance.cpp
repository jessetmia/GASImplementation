// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BaseAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Character/BaseCharacter.h"
#include "Character/Movement/BaseCharacterMovementComponent.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ABaseCharacter>(GetOwningActor());
	if (Character)
	{
		CharacterMovementComponent = Cast<UBaseCharacterMovementComponent>(Character->GetCharacterMovement());

		// Add ASC and AS when available.
		Character->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
	} 
}

void UBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (!GetCharacter() || !GetCharacterMovementComponent())
	{
		return;
	}

	Velocity = CharacterMovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
	
	const FRotator Rot = GetCharacter()->GetActorRotation();
	const float CalcDir = UKismetAnimationLibrary::CalculateDirection(Velocity, Rot);
	Direction = !GetCharacterMovementComponent()->bOrientRotationToMovement ? CalcDir : FMath::Clamp(CalcDir, -DirectionClampAngle, DirectionClampAngle); // Clamp to avoid weird animation glitches ( e.g. when walking backwards
	
	ShouldMove = GetCharacterMovementComponent()->GetCurrentAcceleration() != FVector::ZeroVector && GroundSpeed > MinSpeedToMove;
	IsFalling = GetCharacterMovementComponent()->IsFalling();
	IsCrouching = GetCharacterMovementComponent()->IsCrouching();

	if (UBaseAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		IsSprinting = ASC->IsSprinting();
		IsCombatReady = ASC->IsCombatReady();
	}
}

void UBaseAnimInstance::OnASCInitialized(UAbilitySystemComponent* ASC, UBaseAttributeSet* AttributeSet)
{
	AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(ASC);
	BaseAttributeSet = AttributeSet; // We store values such as movement speed as a gameplay attribute. Having access to this may drive future anims.
}
