// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "EPS_EditorGlobals.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"

bool FEPS_PulldownStructEditorUtils::IsInheritPulldownStructBase(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		if (auto SuperStruct = InStruct->GetSuperStruct())
		{
			if (SuperStruct == FEPS_PulldownStructBase::StaticStruct())
			{
				return true;
			}

			if (!IsInheritPulldownStructBase(SuperStruct))
			{
				return false;
			}
		}
	}

	return false;
}

bool FEPS_PulldownStructEditorUtils::IsInheritPulldownStructAsset(UStruct* InStruct)
{
	return IsValid(Cast<UEPS_PulldownStructAsset>(InStruct));
}

UEPS_PulldownData* FEPS_PulldownStructEditorUtils::GetPulldownData(UStruct* InStruct)
{
	auto&& References = InStruct->ScriptAndPropertyObjectReferences;
	for (const auto& Reference : References)
	{
		if (auto PulldownData = Cast<UEPS_PulldownData>(Reference))
		{
			return PulldownData;
		}
	}

	return nullptr;
}
