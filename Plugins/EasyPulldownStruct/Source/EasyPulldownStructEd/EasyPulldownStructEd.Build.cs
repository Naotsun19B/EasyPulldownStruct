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
                "InputCore",
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
                "GraphEditor",
                "LevelEditor",
                "AssetRegistry",
                "PropertyEditor",
                "BlueprintGraph",
                "EditorSubsystem",

                "EasyPulldownStruct",
            }
			);
    }
}
