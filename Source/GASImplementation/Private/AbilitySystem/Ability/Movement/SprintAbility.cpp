// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Movement/SprintAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Effects/SprintEffect.h"
#include "GameplayTags/BaseTags.h"

USprintAbility::USprintAbility()
{
	SetTagData(BaseTags::Abilities::Movement::Sprint);
	SprintEffect = USprintEffect::StaticClass();
}

void USprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!SprintEffect)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(SprintEffect, GetAbilityLevel(), EffectContext);
    
	if (SpecHandle.IsValid())
	{
		ActiveSprintEffectHandle = GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void USprintAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ActiveSprintEffectHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveSprintEffectHandle);
		ActiveSprintEffectHandle.Invalidate();
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
