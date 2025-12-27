// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Delegates/BaseDelegates.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeSet;
class UBaseCharacterMovementComponent;
class UGameplayEffect;
class UGameplayAbility;

UCLASS(Abstract)
class GASIMPLEMENTATION_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	explicit ABaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual UBaseCharacterMovementComponent* GetCharacterMovement() const;

	FORCEINLINE virtual UCharacterMovementComponent* GetBaseMovementComponent() const
	{
		return Super::GetCharacterMovement();
	}

	// Used to pass ASC and Attribute Set to UI and other elements easily
	UPROPERTY(BluePrintAssignable)
	FASCInitialize OnASCInitialized;
	
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }
	FORCEINLINE virtual UBaseAttributeSet* GetAttributeSet() const { return nullptr;}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Debug")
	bool bDrawDebugMessages = false;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Effects")
	TSubclassOf<UGameplayEffect> InitializeBaseAttributesEffect;

	virtual void InitializeCharacterMovement();
	virtual void GiveStartupAbilities();
	virtual void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& Effect, const float Level = 1.f) const;
	virtual void InitializeAttributes() const;
	virtual void ApplyStartupEffects() const;
	virtual void OnMovementSpeedChanged(const FOnAttributeChangeData& OnAttributeChangeData);
};
