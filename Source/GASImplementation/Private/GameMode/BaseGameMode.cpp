// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameMode/BaseGameMode.h"

#include "Character/BasePlayerCharacter.h"
#include "Player/BasePlayerController.h"
#include "Player/BasePlayerState.h"

ABaseGameMode::ABaseGameMode()
{
	PlayerStateClass = ABasePlayerState::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();
	DefaultPawnClass = ABasePlayerCharacter::StaticClass();
}
