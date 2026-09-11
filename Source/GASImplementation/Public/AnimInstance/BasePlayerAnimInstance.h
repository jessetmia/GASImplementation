// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAnimInstance.h"
#include "Character/BasePlayerCharacter.h"
#include "BasePlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GASIMPLEMENTATION_API UBasePlayerAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual FORCEINLINE ABasePlayerCharacter* GetCharacter() const override { return PlayerCharacter; }
	
	virtual void NativeInitializeAnimation() override;
	
protected:
	UPROPERTY()
	TObjectPtr<ABasePlayerCharacter> PlayerCharacter;
};
