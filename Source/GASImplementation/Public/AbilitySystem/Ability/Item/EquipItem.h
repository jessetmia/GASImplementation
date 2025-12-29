// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BaseAbility.h"
#include "EquipItem.generated.h"

class ABaseItem;
/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UEquipItem : public UBaseAbility
{
	GENERATED_BODY()

public:
	UEquipItem();	

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
