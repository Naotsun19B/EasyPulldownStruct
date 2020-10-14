// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UEPS_PulldownData;

/**
 * Functions used in the editor module.
 */
class EASYPULLDOWNSTRUCTED_API FEPS_PulldownStructEditorUtils
{
private:
	UPROPERTY()
	static TArray<UStruct*> RegisteredPulldownStructs;

public:
	// Recursive function that determines if a struct inherits from FEPS_PulldownStructBase.
	static bool IsInheritPulldownStructBase(UStruct* InStruct);

	// Recursive function that determines if a struct inherits from FEPS_PulldownStructAsset.
	static bool IsInheritPulldownStructAsset(UStruct* InStruct);

	// Get the data need for the pull-down menu.
	static UEPS_PulldownData* GetPulldownData(UStruct* InStruct);

	// Get the all structure inheriting FEPS_PulldownStructBase and UEPS_PulldownStructAsset in the project.
	static void GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs);

	// Register all pull-down menu structures existing in the project with details panel customization.
	static void RegisterPulldownStructToDetailsCustomization();

	// Unregister all pull-down menu structures existing in the project with details panel customization.
	static void UnregisterPulldownStructToDetailsCustomization();
};
