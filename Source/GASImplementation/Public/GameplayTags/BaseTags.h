#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace BaseTags
{
	namespace Abilities
	{
		namespace Categories
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
		}
		
		namespace Movement
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Jump);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Sprint);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Crouch);
		}

		namespace CrowdControl
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stunned);
		}
	}
	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exhausted);
	}
}
