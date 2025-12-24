// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BaseAbility.h"
#include "CrouchAbility.generated.h"

class ABasePlayerCharacter;
/**
 * This requires you to set Can Crouch as true in a BasePlayerCharacter blueprint.
 * I was unable to find an easy way to set the FMovementProperties.bCanCrouch to true in the C++ class.
 */
UCLASS()
class GASIMPLEMENTATION_API UCrouchAbility : public UBaseAbility
{
	GENERATED_BODY()
public:
	UCrouchAbility();

protected:
	UPROPERTY()
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter = nullptr;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
