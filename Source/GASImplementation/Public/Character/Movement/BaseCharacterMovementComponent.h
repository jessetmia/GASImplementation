// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacterMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASIMPLEMENTATION_API UBaseCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement|Speed Modifiers")
	float BackwardSpeedMultiplier = 0.5f;
    
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement|Speed Modifiers")
	float StrafeSpeedMultiplier = 0.75f;
    
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement|Speed Modifiers")
	float DiagonalThreshold = 0.3f;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Movement")
	virtual float CalculateMaxRunSpeed() const;
};
