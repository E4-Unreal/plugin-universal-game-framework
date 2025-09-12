using UnrealBuildTool;

public class InteractionSystem : ModuleRules
{
    public InteractionSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UniversalUtilities",
                "EnhancedInputBinder",
                "GameplayTags",
                "UMG",
                "InputCore"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EnhancedInput"
            }
        );
    }
}
