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


class UExhaustedEffect;

UCLASS()
class GASIMPLEMENTATION_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();
	
	UPROPERTY(BlueprintAssignable)
	FAttrbutesInitialized OnAttrbutesInitialized;

	UPROPERTY(ReplicatedUsing=OnRep_AttributesInitialized)
	bool bAttributesInitialized = false;
	
	/** Resources **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MaxStamina);

	/** Secondary Attributes **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass, MovementSpeed);

	/** Replication **/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_AttributesInitialized(bool bWasInitialized);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Effects")
	TSubclassOf<UGameplayEffect> ExhaustedEffect;
};
