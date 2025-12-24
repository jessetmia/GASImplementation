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

protected:
	UPROPERTY(VisibleAnywhere, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	float ArmLength = 300.f;

	UPROPERTY(EditDefaultsOnly, Category="Camera")
	FVector CameraSocketOffset = FVector(0.f, 35.f, 35.f);
	
	virtual void InitializeCharacterMovement() override;
	void SetupCameraComponents();
};
