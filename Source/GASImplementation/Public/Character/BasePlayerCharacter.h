// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GASIMPLEMENTATION_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	explicit ABasePlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual TObjectPtr<UBaseAttributeSet> GetAttributeSet() const override;

	
	FORCEINLINE float GetArmLength() const { return ArmLength; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	void AdjustCamera(float CameraLength);

protected:
	UPROPERTY(VisibleAnywhere, Category="GAS|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, Category="GAS|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, Category="GAS|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Camera")
	float ArmLength = 300.f;

	UPROPERTY(EditDefaultsOnly, Category="GAS|Camera")
	FVector CameraSocketOffset = FVector(0.f, 35.f, 35.f);
	
	virtual void InitializeCharacterMovement() override;
	virtual void SetupCameraComponents();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
};
