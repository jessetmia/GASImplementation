// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SetupCameraComponents();
}

void ABasePlayerCharacter::InitializeCharacterMovement()
{
	Super::InitializeCharacterMovement();
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ABasePlayerCharacter::SetupCameraComponents()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = ArmLength;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = CameraSocketOffset;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Follow Camera");
	FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("First Person Camera");
	FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

