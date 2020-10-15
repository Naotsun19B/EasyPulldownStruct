// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/PulldownStructUtils.h"
#include "Engine/DataTable.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

#if WITH_EDITOR
TArray<TSharedPtr<FString>> FPulldownStructUtils::GetDisplayStringsInternal(EPulldownSource SourceType, UDataTable* SourceDataTable, UStringTable* SourceStringTable, const TArray<FString>& SourceArray)
{
	TArray<TSharedPtr<FString>> DisplayStrings;

	switch (SourceType)
	{
	case EPulldownSource::PS_DataTable:
	{
		if (IsValid(SourceDataTable))
		{
			// Get all row names of data table and make a list of character strings to be displayed in pull-down menu.
			const TArray<FName>& RowNames = SourceDataTable->GetRowNames();
			for (const auto& RowName : RowNames)
			{
				DisplayStrings.Add(MakeShareable(new FString(RowName.ToString())));
			}
		}

		break;
	}
	case EPulldownSource::PS_StringTable:
	{
		if (IsValid(SourceStringTable))
		{
			// Get all keys of string table and make a list of character strings to be displayed in pull-down menu.
			FStringTableConstPtr StringTable = SourceStringTable->GetStringTable();
			if (StringTable.IsValid())
			{
				StringTable->EnumerateSourceStrings([&](const FString& InKey, const FString& InSourceString) -> bool
				{
					DisplayStrings.Add(MakeShareable(new FString(InKey)));
					return true;
				});
			}
		}

		break;
	}
	case EPulldownSource::PS_Array:
	{
		for (const auto& Element : SourceArray)
		{
			DisplayStrings.Add(MakeShareable(new FString(Element)));
		}

		break;
	}
	default: break;
	}

	return DisplayStrings;
}
#endif
