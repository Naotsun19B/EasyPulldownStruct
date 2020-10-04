// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "EPS_EditorGlobals.h"
#include "PulldownSlate/EPS_PulldownGraphPin.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "SGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"

void FEPS_PulldownGraphPinFactory::RegisterPulldownGraphPinFactory()
{
	TSharedPtr<FEPS_PulldownGraphPinFactory> This = MakeShareable(new FEPS_PulldownGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(This);
}

TSharedPtr<SGraphPin> FEPS_PulldownGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		if (auto Struct = Cast<UStruct>(InPin->PinType.PinSubCategoryObject))
		{
			if (IsInheritPulldownStructBase(Struct))
			{
				return SNew(SEPS_PulldownGraphPin, InPin);
			}
		}
	}
	
	return nullptr;
}

bool FEPS_PulldownGraphPinFactory::IsInheritPulldownStructBase(UStruct* InStruct) const
{
	UScriptStruct* BaseStruct = FEPS_PulldownStructBase::StaticStruct();
	if (IsValid(InStruct) && IsValid(BaseStruct))
	{
		if (InStruct->GetName() == BaseStruct->GetName())
		{
			return true;
		}
		else if (auto SuperStruct = InStruct->GetSuperStruct())
		{
			if (SuperStruct->GetName() == BaseStruct->GetName())
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
