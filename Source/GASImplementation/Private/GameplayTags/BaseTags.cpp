#include "GameplayTags/BaseTags.h"

namespace BaseTags
{
	namespace Abilities
	{
		namespace Categories
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "BaseTags.Abilities.Categories.Primary", "Primary Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(CombatStance, "BaseTags.Abilities.Categories.CombatStance", "CombatStance Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EquipItem, "BaseTags.Abilities.Categories.EquipItem", "EquipItem Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(UnequipItem, "BaseTags.Abilities.Categories.UnequipItem", "UnequipItem Ability Tag");
		}
		namespace Movement
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Jump, "BaseTags.Abilities.Movement.Jump", "Jump Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Sprint, "BaseTags.Abilities.Movement.Sprint", "Sprint Ability Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Crouch, "BaseTags.Abilities.Movement.Crouch", "Crouch Ability Tag");
		}

		namespace CrowdControl
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Stunned, "BaseTags.Abilities.CrowdControl.Stunned", "Stunned Ability Tag");
		}
	}
	namespace Items
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(DefaultSlot, "BaseTags.Items.DefaultSlot", "Default Slot Tag");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Equip, "BaseTags.Items.Equip", "Equip Item Tag");
	}
	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Exhausted, "BaseTags.State.Exhausted", "Exhausted State Tag");
		namespace Combat
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ready, "BaseTags.State.Combat.Ready", "Ready State Tag");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(InCombat, "BaseTags.State.Combat.InCombat", "InCombat State Tag");
		}
	}
}
