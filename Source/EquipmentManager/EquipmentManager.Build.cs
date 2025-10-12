using UnrealBuildTool;

public class EquipmentManager : ModuleRules
{
    public EquipmentManager(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UniversalUtilities",
                "GameplayTags",

                // UniversalGameFramework
                "SocketManager",
                "DataManager"
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
