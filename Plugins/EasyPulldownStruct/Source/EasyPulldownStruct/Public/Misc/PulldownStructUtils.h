// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UDataTable;
class UStringTable;

#if WITH_EDITOR
/**
 * Type of data that is the basis of the pull-down menu.
 */
UENUM()
enum class EPulldownSource : uint8
{
	PS_DataTable	UMETA(DisplayName = "Data Table"),
	PS_StringTable	UMETA(DisplayName = "String Table"),
	PS_Array		UMETA(DisplayName = "Array"),
	PS_InValid			UMETA(Hidden)
};
#endif

#if WITH_EDITOR
/**
 * Class that defines general-purpose functions used in the runtime module.
 */
class FPulldownStructUtils 
{
public:
	// Internal function to get the list of required strings in the pull-down menu.
	static TArray<TSharedPtr<FString>> GetDisplayStringsInternal(EPulldownSource SourceType, UDataTable* SourceDataTable, UStringTable* SourceStringTable, const TArray<FString>& SourceArray);
};
#endif
