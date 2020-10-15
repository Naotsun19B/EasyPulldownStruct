// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/EPS_PulldownStructAsset.h"

#if WITH_EDITOR
#include "Kismet2/StructureEditorUtils.h"
#endif

#if WITH_EDITOR
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
			Element = Element.Replace(TEXT(" "), TEXT(""));
		}
	}

	// Copy the content into a regular struct asset tooltip.
	if (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEPS_PulldownStructAsset, Tooltip))
	{
		FStructureEditorUtils::ChangeTooltip(this, Tooltip);
	}
}

TArray<TSharedPtr<FString>> UEPS_PulldownStructAsset::GetDisplayStrings() const
{
	return FEPS_PulldownStructUtils::GetDisplayStringsInternal(PulldownSource, SourceDataTable, SourceStringTable, SourceArray);
}
#endif
