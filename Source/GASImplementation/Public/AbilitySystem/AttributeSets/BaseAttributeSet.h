// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Delegates/BaseDelegates.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASIMPLEMENTATION_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAttrbutesInitialized OnAttrbutesInitialized;

	UPROPERTY(ReplicatedUsing=OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;

	/** Replication **/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_AttributesInitialized(bool bWasInitialized);
};
