// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/BaseAbility.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/BasePlayerCharacter.h"
#include "Utils/DebugHelper.h"

UBaseAbility::UBaseAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBaseAbility::ApplyEffect(const FGameplayEventData& EventData)
{
	if (!EventData.Instigator || !EventData.Target)
	{
		DebugHelper::Print(*GetName(), TEXT("EventData is invalid"), FColor::Green, -1, true);
		return;
	}
	
	if (!IsValid(EffectClass))
	{
		DebugHelper::Print(*GetName(), TEXT("EffectClass is invalid"), FColor::Green, -1, true);
		return;
	}

	const AActor* AttackingActor = EventData.Instigator;
	if (!IsValid(AttackingActor))
	{
		DebugHelper::Print(*GetName(), TEXT("AttackingActor is invalid"), FColor::Green, -1, true);
		return;
	}

	const ABaseCharacter* Attacker = Cast<ABaseCharacter>(AttackingActor);

	if (!IsValid(Attacker))
	{
		DebugHelper::Print(*GetName(), TEXT("Attacker is invalid"), FColor::Green, -1, true);
		return;
	}
	
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(Attacker->GetAbilitySystemComponent());
	if (!IsValid(AbilitySystemComponent))
	{
		DebugHelper::Print(*GetName(), TEXT("AbilitySystemComponent is invalid"), FColor::Green, -1, true);
		return;
	}

	UBaseAbilitySystemComponent* TargetAbilitySystemComponent = EventData.Target->FindComponentByClass<UBaseAbilitySystemComponent>();
	if (!TargetAbilitySystemComponent)
	{
		const ABasePlayerCharacter* Char = Cast<ABasePlayerCharacter>(EventData.Target);
		if (IsValid(Char))
		{
			TargetAbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(Char->GetAbilitySystemComponent());
			if (!TargetAbilitySystemComponent)
			{
				DebugHelper::Print(*GetName(), TEXT("Target ASC is invalid"), FColor::Green, -1, true);
				return;
			}
		} else
		{
			DebugHelper::Print(*GetName(), TEXT("Target is not a player character"), FColor::Green, -1, true);
			return;
		}
	}

	const FGameplayEffectSpecHandle SpecHandle = CreateSpecHandle(AbilitySystemComponent);
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAbilitySystemComponent);
}

FGameplayEffectSpecHandle UBaseAbility::CreateSpecHandle(
	UBaseAbilitySystemComponent* AbilitySystemComponent) const
{
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, EffectLevel, ContextHandle);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *SpecHandle.Data->GetEffectContext().GetSourceObject()->GetName());
	
	if (!SpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create spec for effect: %s"), *EffectClass->GetName());
		return nullptr;      
	}

	if (EffectTypeTag.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(EffectTypeTag, GetEffectValue());
	}
	return SpecHandle;
}

void UBaseAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (bDrawDebugMessages)
	{
		DebugHelper::Print(*GetName(), TEXT("Activated Ability"), FColor::Green, -1, true);
	}
}

void UBaseAbility::SetTagData(const FGameplayTag& Tag)
{
	SetAssetTags(Tag.GetSingleTagContainer());
	ActivationOwnedTags.AddTag(Tag);
}

void UBaseAbility::SetTagData(const FGameplayTagContainer& Tags)
{
	SetAssetTags(Tags);
	ActivationOwnedTags.AppendTags(Tags);
}
