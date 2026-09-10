// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/MovementAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UMovementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MovementSpeed, COND_None, REPNOTIFY_Always);
}

void UMovementAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	
	if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		SetMovementSpeed(FMath::Clamp(GetMovementSpeed(), 0.0f, 1500.0f));
		OnAttributeChanged.Broadcast(Data.EvaluatedData.Attribute, GetMovementSpeed());
	}
}

void UMovementAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MovementSpeed, OldValue);
	OnAttributeChanged.Broadcast(GetMovementSpeedAttribute(), GetMovementSpeed());
}
