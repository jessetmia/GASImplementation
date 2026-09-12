// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/StaminaAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/Effects/ExhaustedEffect.h"
#include "GameplayTags/BaseTags.h"
#include "Net/UnrealNetwork.h"

UStaminaAttributeSet::UStaminaAttributeSet()
{
	ExhaustedEffect = UExhaustedEffect::StaticClass();
}

void UStaminaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UStaminaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
	
	if (Attribute == GetMaxStaminaAttribute())
	{
		NewValue =  FMath::Max(NewValue, 0.0f);
	}
}

void UStaminaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetMaxStaminaAttribute())
	{
		if (GetMaxStamina() >= GetStamina()) return;
	}
	
	SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina())); 
	// @TODO: This can eventually be moved into a BP Gameplay Effect that is always assigned to the player 
	// We would only activate it if Stamina is equal to 0, though this is a topic for greater discussion. 
	// Do we modify the GE so that the user is exhausted until their stamina is 50~100% and then remove it? If so
	// We will have to add some extra calcs to the modifier for removal.
	if (GetStamina() <= 0.f && ExhaustedEffect)
	{
		if (UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
		{
			if (!ASC->HasMatchingGameplayTag(BaseTags::State::Exhausted))
			{
				FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
				Context.AddSourceObject(GetOwningActor());
                
				const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ExhaustedEffect, 1.f, Context);
				if (SpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
				}
			}
		}
	}
}

void UStaminaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Stamina, OldValue);
}

void UStaminaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxStamina, OldValue);
}
