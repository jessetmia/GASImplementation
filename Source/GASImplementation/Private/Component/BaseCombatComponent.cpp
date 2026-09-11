// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseCombatComponent.h"

const ABaseItem* UBaseCombatComponent::GetCharacterCurrentEquippedBySlot(const FGameplayTag EquipmentSlot) const
{
	// wtf is even const ABaseItem const*. Why is this a thing?
	return EquippedItems.FindRef(EquipmentSlot); 
}

bool UBaseCombatComponent::EquipItem(const FGameplayTag EquipmentSlot, const ABaseItem* ItemToEquip)
{
	if (!ItemToEquip)
	{
		return false;
	}
	
	// @TODO: Validate that Item is equippable.
	EquippedItems.Emplace(EquipmentSlot, ItemToEquip);

	return true;
}
