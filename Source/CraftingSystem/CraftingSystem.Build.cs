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
                "CommonUI",

                // UniversalGameFramework
                "ItemSystem",
                "DataManager",
                "WidgetManager",
                "CommonWidgetManager",
                "UniversalUtilities",
                "InteractionSystem",
                "InventorySystem",
                "AttributeSystem",
                "SlotManager"
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
