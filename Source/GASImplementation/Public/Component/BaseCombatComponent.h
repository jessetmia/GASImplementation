// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "BaseCombatComponent.generated.h"


class ABaseItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASIMPLEMENTATION_API UBaseCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Base|Combat")
	virtual const ABaseItem* GetCharacterCurrentEquippedBySlot(const FGameplayTag EquipmentSlot) const;

	UFUNCTION(BlueprintCallable, Category = "Base|Combat")
	virtual bool EquipItem(const FGameplayTag EquipmentSlot, const ABaseItem* ItemToEquip);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Base|Combat")
	TMap<FGameplayTag, const ABaseItem*> EquippedItems;

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}
	
	template <class T>
	T* GetOwningPawn() const
	{	
		static_assert(TPointerIsConvertibleFromTo<T,APawn>::Value,"'T' Template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}
	
	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,AController>::Value,"'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
