// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/BaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bAttributesInitialized);
}

void UBaseAttributeSet::OnRep_AttributesInitialized(bool bWasInitialized)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, bAttributesInitialized, bWasInitialized);
}
