// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Movement/CrouchAbility.h"

#include "Character/BasePlayerCharacter.h"
#include "GameplayTags/BaseTags.h"
#include "Utils/DebugHelper.h"

UCrouchAbility::UCrouchAbility()
{
	SetTagData(BaseTags::Abilities::Movement::Crouch);

	ActivationBlockedTags.AddTag(BaseTags::Abilities::CrowdControl::Stunned);
}

void UCrouchAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	PlayerCharacter = Cast<ABasePlayerCharacter>(GetAvatarActorFromActorInfo());

	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("ActivateAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		return;
	}
	
	PlayerCharacter->Crouch();
}

void UCrouchAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("EndAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		return;
	}
	
	PlayerCharacter->UnCrouch();
	PlayerCharacter = nullptr;
}
