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
            "PCG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
