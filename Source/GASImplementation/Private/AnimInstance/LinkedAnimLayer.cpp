// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/LinkedAnimLayer.h"

UBaseAnimInstance* ULinkedAnimLayer::GetBaseAnimInstance() const
{
	return Cast<UBaseAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
