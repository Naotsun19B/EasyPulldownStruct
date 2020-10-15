// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UPulldownData;

/**
 * Functions used in the editor module.
 */
class EASYPULLDOWNSTRUCTED_API FPulldownStructEditorUtils
{
public:
	// Recursive function that determines if a struct inherits from FPulldownStructBase.
	static bool IsInheritPulldownStructBase(UStruct* InStruct);

	// Recursive function that determines if a struct inherits from FPulldownStructAsset.
	static bool IsInheritPulldownStructAsset(UStruct* InStruct);

	// Get the data need for the pull-down menu.
	static UPulldownData* GetPulldownData(UStruct* InStruct);
};
