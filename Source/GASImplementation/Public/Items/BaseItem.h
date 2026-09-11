// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Structs/BaseStructTypes.h"
#include "BaseItem.generated.h"

class UBoxComponent;

UCLASS()
class GASIMPLEMENTATION_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();
	
	FORCEINLINE virtual UBoxComponent* GetCollisionBox() const { return CollisionBox; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "GAS|Components")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Components")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Item")
	FGameplayTag EquipmentSlot;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Item")
	FGameplayTag ItemType;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Item")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "GAS|Item")
	float ItemWeight = 1.0f;
	
};
