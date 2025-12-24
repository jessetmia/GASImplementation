// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
struct FGameplayTag;
UCLASS()
class GASIMPLEMENTATION_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Contexts")
	TArray<TObjectPtr<UInputMappingContext>> InputContexts;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Contexts")
	TObjectPtr<UInputMappingContext> ControllerContext;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Contexts")
	TObjectPtr<UInputMappingContext> AbilitiesContext;

	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Movement Mappings")
	TObjectPtr<UInputAction> AdjustCameraAction;

	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Ability Mappings")
	TObjectPtr<UInputAction> ConfirmTargetAction;

	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Ability Mappings")
	TObjectPtr<UInputAction> CancelTargetAction;
	
	UPROPERTY(EditDefaultsOnly, Category="BUDS|Input|Ability Mappings")
	TObjectPtr<UInputAction> PrimaryAction;

	void Jump();
	void StopJump();
	void SprintPressed();
	void SprintReleased();
	void CrouchPressed();
	void CrouchReleased();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ConfirmTarget();
	void CancelTarget();
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
	void CancelAbility(const FGameplayTag& AbilityTag) const;
	void ActivatePrimaryAbility();
	void AdjustCamera(const FInputActionValue& Value);
	
	virtual void SetupInputComponent() override;

	virtual void SetUIInputMode();

	virtual void SetGameInputMode();
};
