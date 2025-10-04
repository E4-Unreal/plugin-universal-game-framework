using UnrealBuildTool;

public class CraftingSystem : ModuleRules
{
    public CraftingSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "GameplayTags",
                "UMG",

                // UniversalGameFramework
                "ItemSystem",
                "DataManager",
                "WidgetManager",
                "UniversalUtilities",
                "InteractionSystem",
                "InventorySystem",
                "AttributeSystem"
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
