// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class UBaseAttributeSet;
class UBaseCharacterMovementComponent;
class UBaseAbilitySystemComponent;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Debug")
	bool bDrawDebugMessages = false;

	UFUNCTION(BlueprintCallable, Category = "GAS|Character")
	virtual FORCEINLINE ABaseCharacter* GetCharacter() const { return Character; }
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Character")
	virtual FORCEINLINE UBaseAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "GAS|Character")
	 virtual FORCEINLINE UBaseCharacterMovementComponent* GetCharacterMovementComponent() const { return CharacterMovementComponent; }

	UFUNCTION(BlueprintCallable, Category = "GAS|Character")
	virtual FORCEINLINE UBaseAttributeSet* GetAttributeSet() const { return BaseAttributeSet; }
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> Character;

	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBaseCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	FGameplayTag CurrentlyEquippedWeapon = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	float Direction = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	bool ShouldMove = false;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	bool IsFalling = false;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	bool IsCrouching = false;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	bool IsSprinting = false;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Character")
	bool IsCombatReady = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
	float DirectionClampAngle = 45.f;
    
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
	float MinSpeedToMove = 0.f;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UBaseAttributeSet* AttributeSet);
};
