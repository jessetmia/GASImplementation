// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BaseAbility.h"
#include "SprintAbility.generated.h"

class ABasePlayerCharacter;
/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API USprintAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	USprintAbility();

protected:
	UPROPERTY()
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sprint")
	TSubclassOf<UGameplayEffect> SprintEffect;
	
	FActiveGameplayEffectHandle ActiveSprintEffectHandle;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
