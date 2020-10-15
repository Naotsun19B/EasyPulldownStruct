// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/PulldownStructAsset.h"

#if WITH_EDITOR
#include "Kismet2/StructureEditorUtils.h"
#endif

#if WITH_EDITOR
void UPulldownStructAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Property may become nullptr when duplicated, so check here.
	if (PropertyChangedEvent.Property == nullptr)
	{
		return;
	}

	// Check the string for whitespace and remove it if it does.
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UPulldownStructAsset, SourceArray))
	{
		for (auto& Element : SourceArray)
		{
			Element = Element.Replace(TEXT(" "), TEXT(""));
		}
	}

	// Copy the content into a regular struct asset tooltip.
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UPulldownStructAsset, Tooltip))
	{
		FStructureEditorUtils::ChangeTooltip(this, Tooltip);
	}
}

TArray<TSharedPtr<FString>> UPulldownStructAsset::GetDisplayStrings() const
{
	return FPulldownStructUtils::GetDisplayStringsInternal(PulldownSource, SourceDataTable, SourceStringTable, SourceArray);
}
#endif
