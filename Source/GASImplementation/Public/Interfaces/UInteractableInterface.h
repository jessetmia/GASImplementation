// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UInteractableInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None		UMETA(DisplayName = "None"),
	Open		UMETA(DisplayName = "Open"),
	Close		UMETA(DisplayName = "Close"),
	Pickup		UMETA(DisplayName = "Pickup"),
	Climb		UMETA(DisplayName = "Climb"),
	Mount		UMETA(DisplayName = "Mount"),
	Use			UMETA(DisplayName = "Use"),
	Talk		UMETA(DisplayName = "Talk"),
	Trade		UMETA(DisplayName = "Trade"),
	Inspect		UMETA(DisplayName = "Inspect")
};

USTRUCT(BlueprintType)
struct FInteractionDataOld
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	EInteractionType InteractionType = EInteractionType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	FText InteractableName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	FText ActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	float InteractionDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	float InteractionDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	bool bCanInteract = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HnS | Interaction")
	FText DisabledReason;

	FInteractionDataOld()
		:InteractableName(FText::FromString("Interactable"))
		, ActionText(FText::GetEmpty())
		, DisabledReason(FText::GetEmpty())
	{}
};

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class GASIMPLEMENTATION_API IInteractableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	FInteractionDataOld GetInteractionData(AActor* InteractingActor) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	void Interact(AActor* InteractingActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	bool BeginInteract(AActor* InteractingActor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	void CancelInteract(AActor* InteractingActor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	bool CanInteract(AActor* InteractingActor) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HnS | Interaction")
	FVector GetInteractionFocusPoint() const;
};
