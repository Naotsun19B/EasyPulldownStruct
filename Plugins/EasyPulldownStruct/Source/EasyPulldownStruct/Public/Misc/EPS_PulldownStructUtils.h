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
enum class EEPS_PulldownSource : uint8
{
	DataTable,
	StringTable,
	Array,
	InValid		UMETA(meta = (Hidden))
};
#endif

#if WITH_EDITOR
/**
 * Class that defines general-purpose functions used in the runtime module.
 */
class FEPS_PulldownStructUtils 
{
public:
	// Internal function to get the list of required strings in the pull-down menu.
	static TArray<TSharedPtr<FString>> GetDisplayStringsInternal(EEPS_PulldownSource SourceType, UDataTable* SourceDataTable, UStringTable* SourceStringTable, const TArray<FString>& SourceArray);
};
#endif
