using UnrealBuildTool;

public class InventorySystem : ModuleRules
{
    public InventorySystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "GameplayTags",
                "UMG",
                "CommonUI",
                "InputCore",
                "DeveloperSettings",

                // UniversalGameFramework
                "UniversalUtilities",
                "InteractionSystem",
                "DataManager",
                "SlotManager",
                "WidgetManager",
                "MeshManager",
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
