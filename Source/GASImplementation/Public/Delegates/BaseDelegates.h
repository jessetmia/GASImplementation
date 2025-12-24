// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/Object.h"
#include "BaseDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttrbutesInitialized);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityGiven, FGameplayAbilitySpec&, AbilitySpec);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialize, UAbilitySystemComponent*, ASC, UBaseAttributeSet*, AS);
/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UBaseDelegates : public UObject
{
	GENERATED_BODY()
};
