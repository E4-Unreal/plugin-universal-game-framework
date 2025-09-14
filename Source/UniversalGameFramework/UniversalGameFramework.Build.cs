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
                "UMG",
                "CommonUI",

                "UniversalUtilities",
                "EnhancedInputBinder",
                "InteractionSystem",
                "InventorySystem",
                "EquipmentManager",
                "DynamicData",
                "ShopSystem",
                "SocketManager",
                "QuickSlotManager",
                "CurrencyManager",
                "DataManager",
                "CommonWidgetManager",
                "WeaponManager",
                "DataManager",
                "SlotManager",
                "AnimationSystem"
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
