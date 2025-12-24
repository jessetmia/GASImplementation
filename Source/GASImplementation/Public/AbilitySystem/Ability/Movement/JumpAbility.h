// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BaseAbility.h"
#include "JumpAbility.generated.h"

class ABasePlayerCharacter;
/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UJumpAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	UJumpAbility();

protected:
	UPROPERTY()
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter = nullptr;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
