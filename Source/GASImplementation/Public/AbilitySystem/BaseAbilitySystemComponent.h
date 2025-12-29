// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="GAS|Helper")
	bool IsCombatReady() const;
	
	UFUNCTION(BlueprintCallable, Category="GAS|Helper")
	bool IsSprinting() const;
	
};
