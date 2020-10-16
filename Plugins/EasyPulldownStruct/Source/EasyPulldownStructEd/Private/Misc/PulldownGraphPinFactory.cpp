// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/PulldownGraphPinFactory.h"
#include "EditorGlobals.h"
#include "Misc/PulldownStructEditorUtils.h"
#include "PulldownSlate/PulldownGraphPin.h"
#include "BaseStruct/PulldownStructBase.h"
#include "PulldownStructAsset/PulldownStructAsset.h"
#include "SGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"

void FPulldownGraphPinFactory::RegisterPulldownGraphPinFactory()
{
	TSharedPtr<FPulldownGraphPinFactory> This = MakeShareable(new FPulldownGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(This);
}

TSharedPtr<SGraphPin> FPulldownGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		if (auto Struct = Cast<UStruct>(InPin->PinType.PinSubCategoryObject))
		{
			if (FPulldownStructEditorUtils::IsInheritPulldownStructBase(Struct) || 
				FPulldownStructEditorUtils::IsPulldownStructAsset(Struct))
			{
				return SNew(SPulldownGraphPin, InPin);
			}
		}
	}
	
	return nullptr;
}
