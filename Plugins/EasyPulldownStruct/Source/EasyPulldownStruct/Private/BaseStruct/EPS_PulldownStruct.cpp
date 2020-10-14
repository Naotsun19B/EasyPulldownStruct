// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStruct/EPS_PulldownStruct.h"

#if WITH_EDITOR
void FEPS_PulldownStructBase::RegisterPulldownStructInternal(UScriptStruct* StaticStruct)
{
	auto&& References = StaticStruct->ScriptAndPropertyObjectReferences;
	bool bIsRegisterd = false;
	for (const auto& Reference : References)
	{
		if (Reference->IsA<UEPS_PulldownData>())
		{
			bIsRegisterd = true;
			break;
		}
	}
	if (!bIsRegisterd)
	{
		auto PulldownData = NewObject<UEPS_PulldownData>();
		PulldownData->SourceType = GetPulldownSourceType();
		PulldownData->SourceDataTable = GetSourceDataTable();
		PulldownData->SourceStringTable = GetSourceStringTable();
		PulldownData->SourceArray = GetSourceArray();
		References.Add(PulldownData);
	}
}

TArray<TSharedPtr<FString>> UEPS_PulldownData::GetDisplayStrings() const
{
	return FEPS_PulldownStructUtils::GetDisplayStringsInternal(SourceType, SourceDataTable, SourceStringTable, SourceArray);
}
#endif
