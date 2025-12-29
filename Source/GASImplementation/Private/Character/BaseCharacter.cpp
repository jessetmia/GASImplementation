// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "AbilitySystem/BaseAttributeSet.h"
#include "Character/Movement/BaseCharacterMovementComponent.h"
#include "Component/BaseCombatComponent.h"
#include "GameFramework/PlayerState.h"
#include "Utils/DebugHelper.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CombatComponent = CreateDefaultSubobject<UBaseCombatComponent>(TEXT("CombatComponent"));

	// Tick and refresh bone anims on dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

#pragma region Initialization
UBaseCharacterMovementComponent* ABaseCharacter::GetCharacterMovement() const
{
	return Cast<UBaseCharacterMovementComponent>(Super::GetCharacterMovement());
}

void ABaseCharacter::InitializeCharacterMovement()
{
	float MaxWalkSpeed = 500.f;
	
	if (const TObjectPtr<UBaseAttributeSet> AttributeSet = Cast<UBaseAttributeSet>(GetAttributeSet()))
	{
		if (IsValid(AttributeSet))
		{
			if (AttributeSet->MovementSpeed.GetCurrentValue() <= 0.f) return;
			MaxWalkSpeed = AttributeSet->MovementSpeed.GetCurrentValue();
		}
		
		GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetMovementSpeedAttribute()
		).AddUObject(this, &ThisClass::OnMovementSpeedChanged);
	}
	
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ABaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent()) || StartupAbilities.IsEmpty()) return;
	
	for (const TSubclassOf<UGameplayAbility>& Ability: StartupAbilities)
	{
		if (bDrawDebugMessages)
		{
			DebugHelper::Print(*GetName(), FString::Printf(TEXT("Giving ability: %s"), *Ability->GetName()), FColor::Green, -1, true);
		}
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		AbilitySpec.SourceObject = this;
		// @TODO: Dynamically set ability level. Will require StartupAbilities refactor. Possibly DataTable? 
		AbilitySpec.Level = 1;
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ABaseCharacter::InitializeAttributes() const
{
	if (IsValid(InitializeBaseAttributesEffect))
	{
		ApplyEffectToSelf(InitializeBaseAttributesEffect);
	}
}

void ABaseCharacter::ApplyStartupEffects() const
{
	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!AbilitySystemComponent)
	{
		DebugHelper::Print(*GetName(), TEXT("Failed to get Ability System Component"), FColor::Green, -1, true);
		return;
	}

	if (PassiveGameplayEffects.IsEmpty())
	{
		DebugHelper::Print(*GetName(), TEXT("No passive gameplay effects configured"), FColor::Green, -1, true);
		return;
	}

	for (const TSubclassOf<UGameplayEffect>& EffectClass : PassiveGameplayEffects)
	{
		if (!EffectClass)
		{
			DebugHelper::Print(*GetName(), TEXT("Empty gameplay effect in PassiveGameplayEffects array"), FColor::Green, -1, true);
			continue;
		}

		const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();

		if (const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, 1.f, ContextHandle); SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		else
		{
			DebugHelper::Print(*GetName(), TEXT("Failed to create spec for effect: ") + EffectClass->GetName(), FColor::Green, -1, true);
		}
	}
}

#pragma endregion

void ABaseCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	if (!IsValid(GetCharacterMovement())) return;
	GetCharacterMovement()->MaxWalkSpeed = OnAttributeChangeData.NewValue;
}

void ABaseCharacter::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& Effect, const float Level) const
{
	if (!IsValid(Effect) || !GetAbilitySystemComponent())
	{
		DebugHelper::Print(*GetName(), TEXT("Effect is invalid or AbilitySystemComponent is invalid"), FColor::Green, -1, true);
		return;
	}

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	
	if (const TObjectPtr<APlayerState> PS = GetPlayerState())
	{
		ContextHandle.AddSourceObject(PS);
	}
	else
	{
		ContextHandle.AddSourceObject(this);
	}
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, Level, ContextHandle);
    
	if (!SpecHandle.IsValid())
	{
		DebugHelper::Print(*GetName(), TEXT("Failed to create spec for effect: ") + Effect->GetName(), FColor::Green, -1, true);
		return;   
	}
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
