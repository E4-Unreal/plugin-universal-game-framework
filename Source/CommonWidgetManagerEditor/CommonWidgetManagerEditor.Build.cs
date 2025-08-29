using UnrealBuildTool;

public class CommonWidgetManagerEditor : ModuleRules
{
    public CommonWidgetManagerEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
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
                "CommonUI",
                "UnrealEd",
                "EditorScriptingUtilities"
            }
        );
    }
}
