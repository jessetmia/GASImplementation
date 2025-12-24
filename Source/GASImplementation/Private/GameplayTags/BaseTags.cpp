#include "GameplayTags/BaseTags.h"

namespace BaseTags
{
	namespace Abilities
	{
		namespace Categories
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "BUDSTags.Abilities.Categories.Primary", "Primary Ability Tag");
		}
	}
	namespace Movement
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Jump, "BUDSTags.Abilities.Movement.Jump", "Jump Ability Tag");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprint, "BUDSTags.Abilities.Movement.Sprint", "Sprint Ability Tag");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Crouch, "BUDSTags.Abilities.Movement.Crouch", "Crouch Ability Tag");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Slide, "BUDSTags.Abilities.Movement.Slide", "Slide Ability Tag");
	}
}
