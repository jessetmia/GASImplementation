// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class GASIMPLEMENTATION_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameMode();
};



