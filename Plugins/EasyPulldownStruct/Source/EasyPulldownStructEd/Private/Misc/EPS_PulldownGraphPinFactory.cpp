// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "SGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"

TSharedPtr<SGraphPin> FEPS_PulldownGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Struct)
	{
		//if (InPin->PinType.PinSubCategoryObject == FEPS_PulldownStructBase::StaticStruct())
		//{
		//	return SNew(SGraphPin, InPin);
		//}
	}

	return nullptr;
}
