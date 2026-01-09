// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AiGenRpg : ModuleRules
{
	public AiGenRpg(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"PCG" // ⬅️ КРИТИЧНО
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
		});
	}
}
