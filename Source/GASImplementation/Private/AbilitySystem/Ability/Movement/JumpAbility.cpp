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

bool UJumpAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;
	
	const ABaseCharacter* Character = Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get());
	if (!IsValid(Character)) return false;
	
	return Character && Character->CanJump();
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	PlayerCharacter = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());

	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("ActivateAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	PlayerCharacter->Jump();
}

void UJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsValid(PlayerCharacter))
	{
		DebugHelper::Print(*GetName(), TEXT("EndAbility: PlayerCharacter is invalid"), FColor::Green, -1, true);
		return;
	}
	
	PlayerCharacter->StopJumping();
	PlayerCharacter = nullptr;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
