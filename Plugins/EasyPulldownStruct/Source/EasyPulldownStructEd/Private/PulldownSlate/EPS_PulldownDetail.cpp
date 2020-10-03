// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownSlate/EPS_PulldownDetail.h"
#include "EPS_EditorGlobals.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"

namespace PulldownDetailInternal
{
	// The variable name of the variable that holds the selected string in the pull-down menu structure.
	static const FString& KeyPropertyName = TEXT("Key");
}

TSharedRef<IPropertyTypeCustomization> IEPS_PulldownDetail::MakeInstance(const TArray<TSharedPtr<FString>>& InDisplayStrings)
{
	TSharedRef<IEPS_PulldownDetail> Instance = MakeShareable(new IEPS_PulldownDetail());

	Instance.Get().DisplayStrings.Empty();
	Instance.Get().DisplayStrings = InDisplayStrings;

	return Instance;
}

void IEPS_PulldownDetail::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;

	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	FName Key;
	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ChildIndex++)
	{
		const TSharedPtr< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex);
		if (ChildHandle->GetProperty()->GetName() == PulldownDetailInternal::KeyPropertyName)
		{
			KeyHandle = ChildHandle;
			ChildHandle->GetValue(Key);
		}
	}
	check(KeyHandle.IsValid());

	// Check if the obtained Key is in the list.
	int Index = 0;
	bool bIsFound = false;
	for (int32 Itr = 0; Itr < DisplayStrings.Num(); ++Itr)
	{
		if (DisplayStrings[Itr]->Equals(Key.ToString()))
		{
			Index = Itr;
			bIsFound = true;
			break;
		}
	}
	if (!bIsFound)
	{
		Key = NAME_None;
		KeyHandle->SetValue(Key);
		UE_LOG(LogEasyPulldownStruct, Error, TEXT("The string \"%s\" was not found in the list."), *Key.ToString());
	}

	// Create a Slate that composes the pull-down menu.
	HeaderRow
		.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		.MinDesiredWidth(500)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			[
				SAssignNew(KeyComboBox, STextComboBox)
				.OptionsSource(&DisplayStrings)
				.OnSelectionChanged(this, &IEPS_PulldownDetail::OnStateValueChanged)
				.InitiallySelectedItem(DisplayStrings[Index])
			]
		];
}

void IEPS_PulldownDetail::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

void IEPS_PulldownDetail::OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo)
{
	if (ItemSelected.IsValid())
	{
		if (DisplayStrings.Contains(ItemSelected))
		{
			// Apply the string of the selected item to the value of the variable.
			KeyHandle->SetValue(FName(**ItemSelected));
		}
	}
}
