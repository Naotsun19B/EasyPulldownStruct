// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "EPS_EditorGlobals.h"
#include "PulldownSlate/EPS_PulldownGraphPin.h"
#include "SGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"

namespace PulldownGraphPinFactoryInternal
{
	// The structure name is defined here, 
	// although it is not a very desirable way to eliminate module interdependence.
	static const FString PulldownStructBaseName = TEXT("EPS_PulldownStructBase");
}

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
	if (IsValid(InStruct))
	{
		if (auto SuperStruct = InStruct->GetSuperStruct())
		{
			if (SuperStruct->GetName() == PulldownGraphPinFactoryInternal::PulldownStructBaseName)
			{
				return true;
			}

			if (!IsInheritPulldownStructBase(SuperStruct))
			{
				return false;
			}
		}
		else
		{
			if (InStruct->GetName() == PulldownGraphPinFactoryInternal::PulldownStructBaseName)
			{
				return true;
			}
		}
	}

	return false;
}
