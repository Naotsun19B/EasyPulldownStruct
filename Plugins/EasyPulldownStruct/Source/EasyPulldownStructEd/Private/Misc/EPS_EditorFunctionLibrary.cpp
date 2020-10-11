// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_EditorFunctionLibrary.h"
#include "EPS_EditorGlobals.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"

bool FEPS_EditorFunctionLibrary::IsInheritPulldownStructBase(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		if (InStruct == FEPS_PulldownStructBase::StaticStruct())
		{
			return true;
		}
		else if (auto SuperStruct = InStruct->GetSuperStruct())
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

bool FEPS_EditorFunctionLibrary::IsInheritPulldownStructAsset(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		return UEPS_PulldownStructAsset::StaticClass()->IsChildOf(InStruct->GetClass());
	}
	
	return false;
}

UEPS_PulldownData* FEPS_EditorFunctionLibrary::GetPulldownData(UStruct* InStruct)
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
