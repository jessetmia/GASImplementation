// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, bAttributesInitialized, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized) OnAttrbutesInitialized.Broadcast();
}
