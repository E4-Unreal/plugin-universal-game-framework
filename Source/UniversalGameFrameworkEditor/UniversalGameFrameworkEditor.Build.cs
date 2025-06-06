﻿using UnrealBuildTool;

public class UniversalGameFrameworkEditor : ModuleRules
{
    public UniversalGameFrameworkEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "UniversalUtilities",
                "DynamicDataEditor",
                "Blutility"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DynamicData",
                "StructUtils",
                "UniversalGameFramework",
                "InventorySystem",
                "GameplayTags",
            }
        );
    }
}
