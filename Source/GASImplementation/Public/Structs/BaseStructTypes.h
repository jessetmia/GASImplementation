#pragma once
#include "GameplayTagContainer.h"

#include "BaseStructTypes.generated.h"

class ULinkedAnimLayer;

USTRUCT(BlueprintType)
struct FAnimLayerEntry
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	FGameplayTag ActivationTag;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TSubclassOf<ULinkedAnimLayer> AnimLayerClass;
};
