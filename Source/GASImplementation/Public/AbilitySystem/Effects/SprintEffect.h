// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "SprintEffect.generated.h"

/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API USprintEffect : public UGameplayEffect
{
	GENERATED_BODY()

public:
	USprintEffect();
};

/**
 * Sprint Speed Buff - Infinite, non-periodic effect that increases movement speed
 */
UCLASS()
class GASIMPLEMENTATION_API USprintSpeedEffect : public USprintEffect
{
	GENERATED_BODY()

public:
	USprintSpeedEffect();
};

/**
 * Sprint Stamina Drain - Infinite, periodic effect that drains stamina over time
 */
UCLASS()
class GASIMPLEMENTATION_API USprintStaminaDrainEffect : public USprintEffect
{
	GENERATED_BODY()

public:
	USprintStaminaDrainEffect();
};
