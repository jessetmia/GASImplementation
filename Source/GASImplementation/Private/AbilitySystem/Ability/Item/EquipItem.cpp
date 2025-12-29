// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Item/EquipItem.h"

#include "Component/BaseCombatComponent.h"
#include "GameplayTags/BaseTags.h"
#include "Items/BaseItem.h"

UEquipItem::UEquipItem()
{
	SetTagData(BaseTags::Abilities::Categories::EquipItem);

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = BaseTags::Items::Equip;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);
}

void UEquipItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!TriggerEventData)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const ABaseItem* EquippableItem = Cast<ABaseItem>(TriggerEventData->OptionalObject);

	if (!EquippableItem)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	const FGameplayTag EquippableItemTag = TriggerEventData->EventTag;
	
	// @TODO: Validate that item can be equipped. 
	GetCombatComponent()->EquipItem(EquippableItemTag, EquippableItem);
	
	// @TODO: Apply effects on equip. Should this be handled here or in combat component? 
}
