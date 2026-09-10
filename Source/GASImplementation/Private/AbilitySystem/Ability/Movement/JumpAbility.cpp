// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/Movement/JumpAbility.h"

#include "Character/BasePlayerCharacter.h"
#include "GameplayTags/BaseTags.h"
#include "Utils/DebugHelper.h"

UJumpAbility::UJumpAbility()
{
	SetTagData(BaseTags::Abilities::Movement::Jump);

	ActivationBlockedTags.AddTag(BaseTags::Abilities::CrowdControl::Stunned);
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	PlayerCharacter = Cast<ABasePlayerCharacter>(GetAvatarActorFromActorInfo());

	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("ActivateAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		return;
	}

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		PlayerCharacter->Jump();
	}
}

void UJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("EndAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		return;
	}
	
	PlayerCharacter->StopJumping();
	PlayerCharacter = nullptr;
}
