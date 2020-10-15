// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UEPS_PulldownData;

/**
 * Functions used in the editor module.
 */
class EASYPULLDOWNSTRUCTED_API FEPS_PulldownStructEditorUtils
{
public:
	// Recursive function that determines if a struct inherits from FEPS_PulldownStructBase.
	static bool IsInheritPulldownStructBase(UStruct* InStruct);

	// Recursive function that determines if a struct inherits from FEPS_PulldownStructAsset.
	static bool IsInheritPulldownStructAsset(UStruct* InStruct);

	// Get the data need for the pull-down menu.
	static UEPS_PulldownData* GetPulldownData(UStruct* InStruct);
};
