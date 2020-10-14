// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownStructUtils.h"
#include "Engine/DataTable.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

#if WITH_EDITOR
TArray<TSharedPtr<FString>> FEPS_PulldownStructUtils::GetDisplayStringsInternal(EEPS_PulldownSource SourceType, UDataTable* SourceDataTable, UStringTable* SourceStringTable, const TArray<FString>& SourceArray)
{
	TArray<TSharedPtr<FString>> DisplayStrings;

	switch (SourceType)
	{
	case EEPS_PulldownSource::DataTable:
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
	case EEPS_PulldownSource::StringTable:
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
	case EEPS_PulldownSource::Array:
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
