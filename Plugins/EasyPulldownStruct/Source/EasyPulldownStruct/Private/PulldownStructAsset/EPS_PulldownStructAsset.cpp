// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "EPS_EditorGlobals.h"
#include "Engine/DataTable.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

#if WITH_EDITOR
void UEPS_PulldownStructAsset::PostLoad()
{
	Super::PostLoad();

	RegisterPulldownStruct();
}

void UEPS_PulldownStructAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Property may become nullptr when duplicated, so check here.
	if (PropertyChangedEvent.Property == nullptr)
	{
		return;
	}

	// Check the string for whitespace and remove it if it does.
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, SourceArray))
	{
		for (auto& Element : SourceArray)
		{
			Element.Replace(TEXT(" "), TEXT(""));
		}
	}

	// Update the registration information when the type of the source data changes or when the source data changes.
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, PulldownSource) ||
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, SourceDataTable) ||
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, SourceStringTable) ||
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, SourceArray))
	{
		RegisterPulldownStruct(true);
	}
}

void UEPS_PulldownStructAsset::RegisterPulldownStruct(bool bIsUpdate)
{
	auto Container = UEPS_DisplayStringsContainer::Get();
	check(Container);

	// Unregister to update data.
	if (bIsUpdate)
	{
		Container->UnregisterDisplayStrings(GetName());
	}

	Container->RegisterDisplayStrings(GetName(), GetDisplayStrings());
}

TArray<TSharedPtr<FString>> UEPS_PulldownStructAsset::GetDisplayStrings() const
{
	TArray<TSharedPtr<FString>> DisplayStrings;

	switch (PulldownSource)
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
