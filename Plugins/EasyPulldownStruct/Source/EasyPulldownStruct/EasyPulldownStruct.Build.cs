// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyPulldownStruct : ModuleRules
{
	public EasyPulldownStruct(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
            );

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "PropertyEditor",
                "EasyPulldownStructEd",
				// ... add private dependencies that you statically link with here ...	
			}
            );
        }
    }
}
