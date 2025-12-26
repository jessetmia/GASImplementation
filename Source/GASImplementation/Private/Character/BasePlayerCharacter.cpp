// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/Movement/BaseCharacterMovementComponent.h"
#include "Player/BasePlayerState.h"


// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	SetupCameraComponents();
}

UAbilitySystemComponent* ABasePlayerCharacter::GetAbilitySystemComponent() const
{
	const TObjectPtr<ABasePlayerState> PState = Cast<ABasePlayerState>(GetPlayerState());
	if (!IsValid(PState)) return nullptr;
	
	return PState->GetAbilitySystemComponent();
}

TObjectPtr<UBaseAttributeSet> ABasePlayerCharacter::GetAttributeSet() const
{
	const TObjectPtr<ABasePlayerState> PState = Cast<ABasePlayerState>(GetPlayerState());
	if (!IsValid(PState)) return nullptr;
	
	return PState->GetAttributeSet();
}

void ABasePlayerCharacter::AdjustCamera(float CameraLength)
{
	ArmLength = CameraLength;
	SpringArmComponent->TargetArmLength = ArmLength;
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

void ABasePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	GiveStartupAbilities();
	InitializeAttributes();
	ApplyStartupEffects();
	InitializeCharacterMovement();
}

void ABasePlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (!IsValid(GetAbilitySystemComponent())) return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	InitializeCharacterMovement();
}

