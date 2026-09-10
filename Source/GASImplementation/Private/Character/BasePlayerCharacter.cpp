// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/Movement/BaseCharacterMovementComponent.h"
#include "GameplayTags/BaseTags.h"
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

UBaseAttributeSet* ABasePlayerCharacter::GetAttributeSet() const
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

	auto* AbilitySystemComponent = GetAbilitySystemComponent();
	
	if (!IsValid(AbilitySystemComponent) || !HasAuthority()) return;

	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(AbilitySystemComponent, GetAttributeSet());

	AbilitySystemComponent->RegisterGameplayTagEvent(
			FGameplayTag::RequestGameplayTag(TEXT("BaseTags.Abilities.Categories")),
			EGameplayTagEventType::NewOrRemoved
		).AddUObject(this, &ThisClass::OnAnimStateTagChanged);
	
	GiveStartupAbilities();
	InitializeAttributes();
	ApplyStartupEffects();
	InitializeCharacterMovement();
}

void ABasePlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	auto* AbilitySystemComponent = GetAbilitySystemComponent();
	
	if (!IsValid(AbilitySystemComponent)) return;

	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(AbilitySystemComponent, GetAttributeSet());
	InitializeCharacterMovement();

	if (!bAnimTagListenerBound)
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(
				FGameplayTag::RequestGameplayTag(TEXT("BaseTags.Abilities.Categories")),
				EGameplayTagEventType::NewOrRemoved
			).AddUObject(this, &ThisClass::OnAnimStateTagChanged);
		bAnimTagListenerBound = true;
	}
}

