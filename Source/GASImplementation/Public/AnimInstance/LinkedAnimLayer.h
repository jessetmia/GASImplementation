// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "LinkedAnimLayer.generated.h"

/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API ULinkedAnimLayer : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UBaseAnimInstance* GetBaseAnimInstance() const;
};
