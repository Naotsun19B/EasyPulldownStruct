// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

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
            }
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Slate",
                "SlateCore",
                "AssetTools",
                "Kismet",
                "UnrealEd",
                "LevelEditor",
                "GraphEditor",
                "AssetRegistry",
                "PropertyEditor",
                "BlueprintGraph",

                "EasyPulldownStruct",
            }
			);
    }
}
