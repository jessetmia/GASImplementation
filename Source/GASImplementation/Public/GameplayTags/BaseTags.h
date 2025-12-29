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
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatStance);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EquipItem);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(UnequipItem);
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
	namespace Items
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DefaultSlot);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equip);
	}
	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Exhausted);
		namespace Combat
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ready);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(InCombat);
		}
	}
}
