// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GASImplementation : ModuleRules
{
	public GASImplementation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
				
		
		PrivateIncludePaths.AddRange( new string[] {});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"InputCore",
				"EnhancedInput",
				"GameplayAbilities",
				"GameplayTags",
				"GameplayTasks",
				"AIModule",
				"StateTreeModule",
				"GameplayStateTreeModule",
				"UMG",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",	
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
