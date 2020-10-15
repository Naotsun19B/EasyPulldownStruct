// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStruct/PulldownStructBase.h"

#if WITH_EDITOR
void FPulldownStructBase::RegisterPulldownStructInternal(UScriptStruct* StaticStruct)
{
	auto&& References = StaticStruct->ScriptAndPropertyObjectReferences;
	bool bIsRegisterd = false;
	for (const auto& Reference : References)
	{
		if (Reference->IsA<UPulldownData>())
		{
			bIsRegisterd = true;
			break;
		}
	}
	if (!bIsRegisterd)
	{
		auto PulldownData = NewObject<UPulldownData>();
		PulldownData->SourceType = GetPulldownSourceType();
		PulldownData->SourceDataTable = GetSourceDataTable();
		PulldownData->SourceStringTable = GetSourceStringTable();
		PulldownData->SourceArray = GetSourceArray();
		References.Add(PulldownData);
	}
}

TArray<TSharedPtr<FString>> UPulldownData::GetDisplayStrings() const
{
	return FPulldownStructUtils::GetDisplayStringsInternal(SourceType, SourceDataTable, SourceStringTable, SourceArray);
}
#endif
