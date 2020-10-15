// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownSlate/EPS_PulldownGraphPin.h"
#include "EPS_EditorGlobals.h"
#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Widgets/Input/STextComboBox.h"

void SEPS_PulldownGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

#pragma optimize("", off)
TSharedRef<SWidget>	SEPS_PulldownGraphPin::GetDefaultValueWidget()
{
	// Get a list of strings to display in the pull-down menu from the name of the structure of your own pin.
	DisplayStrings.Empty();
	if (UEdGraphPin* Pin = GetPinObj())
	{
		// Get a list of strings to cast and display for structure assets for pull-down menus.
		if (auto PulldownStructAsset = Cast<UEPS_PulldownStructAsset>(Pin->PinType.PinSubCategoryObject))
		{
			DisplayStrings = PulldownStructAsset->GetDisplayStrings();
		}
		// Get an instance of the structure from the DefaultStructInstance associated with StaticStruct, 
		// and get the list of strings to display from that instance.
		else if (auto Struct = Cast<UStruct>(Pin->PinType.PinSubCategoryObject))
		{
			if (auto PulldownData = FEPS_PulldownStructEditorUtils::GetPulldownData(Struct))
			{
				DisplayStrings = PulldownData->GetDisplayStrings();
			}
		}
	}

	// Be sure to put "None" so that the list is not empty.
	const TSharedPtr<FString>& DefaultValue = MakeShareable(new FString(FName(NAME_None).ToString()));
	if (!DisplayStrings.Contains(DefaultValue))
	{
		DisplayStrings.Insert(DefaultValue, 0);
	}

	int Index = 0;
	FString CurrentDefault = GraphPinObj->GetDefaultAsString();
	if (CurrentDefault.Len() > 2)
	{
		// Extract only the value part of the structure string.
		FString Left;
		FString Right;
		CurrentDefault.Split(TEXT("="), &Left, &Right);
		CurrentDefault = Right;

		CurrentDefault = CurrentDefault.Replace(TEXT(")"), TEXT(""));
		CurrentDefault = CurrentDefault.Replace(TEXT("\""), TEXT(""));

		// Find the index on the list from the set character string.
		bool bIsFound = false;
		for (int32 Itr = 0; Itr < DisplayStrings.Num(); ++Itr)
		{
			if (DisplayStrings[Itr]->Equals(CurrentDefault))
			{
				Index = Itr;
				Key = FName(*CurrentDefault);
				bIsFound = true;
				break;
			}
		}
		if (!bIsFound)
		{
			FString TempString = *(DisplayStrings[0]);
			Key = FName(*TempString);
			UE_LOG(LogEasyPulldownStruct, Error, TEXT("The string \"%s\" was not found in the list."), *TempString);
		}
	}
	else
	{
		FString TempString = *(DisplayStrings[0]);
		Key = FName(*TempString);
	}

	// Create a Slate that composes the pull-down menu.
	return SNew(SHorizontalBox)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		[
			SNew(STextComboBox)
			.OptionsSource(&DisplayStrings)
			.OnSelectionChanged(this, &SEPS_PulldownGraphPin::OnValueChanged)
			.InitiallySelectedItem(DisplayStrings[Index])
		];
}
#pragma optimize("", on)

void SEPS_PulldownGraphPin::OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (DisplayStrings.Contains(ItemSelected))
		{
			// Apply the selected string to the graph pin string.
			FString KeyString = FString::Printf(TEXT("(Key=%s)"), *(*ItemSelected));
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, KeyString);
		}
		else
		{
			UE_LOG(LogEasyPulldownStruct, Error, TEXT("The string \"%s\" was not found in the list."), *(*ItemSelected));
		}
	}
}
