// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AttributeSets/MovementAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABasePlayerState();
	
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual TObjectPtr<UMovementAttributeSet> GetMovementAttributeSet() const { return MovementAttributeSet; }

protected:
	UPROPERTY(VisibleInstanceOnly, Category="GAS|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleInstanceOnly, Category="GAS|Abilities")
	TObjectPtr<UMovementAttributeSet> MovementAttributeSet;
};
