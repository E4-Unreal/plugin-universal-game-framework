using UnrealBuildTool;

public class UniversalGameFramework : ModuleRules
{
    public UniversalGameFramework(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "GameplayTags",
                "UniversalUtilities",
                "EnhancedInputBinder",
                "InteractionSystem",
                "InventorySystem",
                "DynamicData"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}
