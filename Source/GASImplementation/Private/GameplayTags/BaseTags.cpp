#include "GameplayTags/BaseTags.h"

namespace BaseTags
{
	namespace Abilities
	{
		namespace Categories
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "BaseTags.Abilities.Categories.Primary", "Primary Ability Tag");
		}
		namespace Movement
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Jump, "BaseTags.Abilities.Movement.Jump", "Jump Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprint, "BaseTags.Abilities.Movement.Sprint", "Sprint Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Crouch, "BaseTags.Abilities.Movement.Crouch", "Crouch Ability Tag");
		}
	}
	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Exhausted, "BaseTags.State.Exhausted", "Exhausted State Tag");
	}
}
