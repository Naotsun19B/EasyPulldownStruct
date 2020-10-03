// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownSlate/EPS_PulldownGraphPin.h"
#include "EPS_EditorGlobals.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Widgets/Input/STextComboBox.h"

void SEPS_PulldownGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	DisplayStrings.Empty();
	DisplayStrings = InArgs._InDisplayStrings;

	const TSharedPtr<FString>& DefaultValue = MakeShareable(new FString(FName(NAME_None).ToString()));
	if (!DisplayStrings.Contains(DefaultValue))
	{
		DisplayStrings.Insert(DefaultValue, 0);
	}
}

TSharedRef<SWidget>	SEPS_PulldownGraphPin::GetDefaultValueWidget()
{
	// Create a list of strings to display in the pull-down menu, including the default value None.
	DisplayStrings.Add(MakeShareable<FString>(new FString(FName(NAME_None).ToString())));

	int Index = 0;
	FString CurrentDefault = GraphPinObj->GetDefaultAsString();
	if (CurrentDefault.Len() > 0)
	{
		// Remove "Key =" and parentheses.
		int32 StartIndex = 5;
		int32 EndIndex;
		CurrentDefault.FindLastChar(')', EndIndex);
		FString DefaultValString = CurrentDefault.Mid(StartIndex, EndIndex - StartIndex);

		// Remove double quotes before and after if necessary.
		if (DefaultValString[0] == '\"')
		{
			DefaultValString = DefaultValString.Mid(1);
		}
		if (DefaultValString[DefaultValString.Len() - 1] == '\"')
		{
			DefaultValString = DefaultValString.Mid(0, DefaultValString.Len() - 1);
		}

		// Find the index on the list from the set character string.
		bool bIsFound = false;
		for (int32 Itr = 0; Itr < DisplayStrings.Num(); ++Itr)
		{
			if (DisplayStrings[Itr]->Equals(DefaultValString))
			{
				Index = Itr;
				Key = FName(*DefaultValString);
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

void SEPS_PulldownGraphPin::OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (DisplayStrings.Find(ItemSelected))
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
