// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BasePlayerAnimInstance.h"

void UBasePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<ABasePlayerCharacter>(GetOwningActor());
}
