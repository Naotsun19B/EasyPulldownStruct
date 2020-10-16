// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/PulldownStructEditorUtils.h"
#include "EditorGlobals.h"
#include "BaseStruct/PulldownStructBase.h"
#include "PulldownStructAsset/PulldownStructAsset.h"

bool FPulldownStructEditorUtils::IsInheritPulldownStructBase(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		if (auto SuperStruct = InStruct->GetSuperStruct())
		{
			if (SuperStruct == FPulldownStructBase::StaticStruct())
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

bool FPulldownStructEditorUtils::IsPulldownStructAsset(UStruct* InStruct)
{
	return IsValid(Cast<UPulldownStructAsset>(InStruct));
}

UPulldownData* FPulldownStructEditorUtils::GetPulldownData(UStruct* InStruct)
{
	auto&& References = InStruct->ScriptAndPropertyObjectReferences;
	for (const auto& Reference : References)
	{
		if (auto PulldownData = Cast<UPulldownData>(Reference))
		{
			return PulldownData;
		}
	}

	return nullptr;
}
