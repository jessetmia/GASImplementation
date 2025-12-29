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
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Contexts")
	TArray<TObjectPtr<UInputMappingContext>> InputContexts;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Contexts")
	TObjectPtr<UInputMappingContext> ControllerContext;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Contexts")
	TObjectPtr<UInputMappingContext> AbilitiesContext;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> CrouchAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Movement Mappings")
	TObjectPtr<UInputAction> AdjustCameraAction;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Ability Mappings")
	TObjectPtr<UInputAction> ConfirmTargetAction;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Ability Mappings")
	TObjectPtr<UInputAction> CancelTargetAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Ability Mappings")
	TObjectPtr<UInputAction> PrimaryAction;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Input|Ability Mappings")
	TObjectPtr<UInputAction> CombatStanceAction;

	virtual void Jump();
	virtual void StopJump();
	virtual void SprintPressed();
	virtual void SprintReleased();
	virtual void CrouchPressed();
	virtual void CrouchReleased();
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void ConfirmTarget();
	virtual void CancelTarget();
	virtual void ActivateAbility(const FGameplayTag& AbilityTag) const;
	virtual void CancelAbility(const FGameplayTag& AbilityTag) const;
	virtual void ActivatePrimaryAbility();
	virtual void AdjustCamera(const FInputActionValue& Value);
	virtual void ToggleCombatStance();
	
	virtual void SetupInputComponent() override;

	virtual void SetUIInputMode();

	virtual void SetGameInputMode();
};
