using UnrealBuildTool;

public class ShopSystem : ModuleRules
{
    public ShopSystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UniversalUtilities",
                "GameplayTags",
                "UMG",

                // UniversalGameFramework
                "DataManager",
                "CurrencyManager",
                "SlotManager",
                "InventorySystem"
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
