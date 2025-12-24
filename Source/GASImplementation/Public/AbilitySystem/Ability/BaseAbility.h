// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseAbility.generated.h"

class UBaseAbilitySystemComponent;
UCLASS()
class GASIMPLEMENTATION_API UBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseAbility();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Debug")
	bool bDrawDebugMessages = false;
	
	UFUNCTION(BlueprintCallable, Category="GAS|Abilities|Damage")
	virtual void ApplyEffect(const FGameplayEventData& EventData);
	
	virtual float GetEffectValue() const { return BaseEffectValue; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Abilities")
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Abilities")
	float EffectLevel = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities|Damage")
	FGameplayTag EventReceiveTag;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities|Damage")
	FGameplayTag EffectTypeTag;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Abilities|Damage")
	TArray<FGameplayTag> AbilityDynamicTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Abilities|Damage")
	float BaseEffectValue = 10.0f;

	virtual FGameplayEffectSpecHandle CreateSpecHandle(UBaseAbilitySystemComponent* AbilitySystemComponent) const;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void SetTagData(const FGameplayTag& Tag);
	virtual void SetTagData(const FGameplayTagContainer& Tags);
};
