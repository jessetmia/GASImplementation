// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Delegates/BaseDelegates.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, const FGameplayAttribute& /*Attribute*/, float /*NewValue*/);

UCLASS()
class GASIMPLEMENTATION_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAttrbutesInitialized OnAttrbutesInitialized;
	
	UPROPERTY()
	FOnAttributeChanged OnAttributeChanged;

	UPROPERTY(ReplicatedUsing=OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;
	
	UFUNCTION()
	void OnRep_AttributesInitialized();
};
