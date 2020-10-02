// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyPulldownStructEd : ModuleRules
{
	public EasyPulldownStructEd(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
            }
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Slate",
                "SlateCore",
                "UnrealEd",
                "GraphEditor",
                "PropertyEditor",
                "BlueprintGraph",

                //"EasyPulldownStruct",
            }
			);
	}
}
