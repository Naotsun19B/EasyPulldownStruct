// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownSlate/EPS_PulldownDetail.h"
#include "EPS_EditorGlobals.h"
#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
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

TSharedRef<IPropertyTypeCustomization> IEPS_PulldownDetail::MakeInstance()
{
	return MakeShareable(new IEPS_PulldownDetail());
}

void IEPS_PulldownDetail::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;

	// Get a list of strings to display in the pull-down menu from the name of the structure of your own pin.
	if (auto StructProperty = CastField<FStructProperty>(StructPropertyHandle->GetProperty()))
	{
		// Get a list of strings to cast and display for structure assets for pull-down menus.
		if (auto PulldownStructAsset = Cast<UEPS_PulldownStructAsset>(StructProperty->Struct))
		{
			DisplayStrings = PulldownStructAsset->GetDisplayStrings();
		}
		// Get an instance of the structure from the DefaultStructInstance associated with StaticStruct, 
		// and get the list of strings to display from that instance.
		else if (auto PulldownData = FEPS_PulldownStructEditorUtils::GetPulldownData(StructProperty->Struct))
		{
			DisplayStrings = PulldownData->GetDisplayStrings();
		}
	}

	// Be sure to put "None" so that the list is not empty.
	const TSharedPtr<FString>& DefaultValue = MakeShareable(new FString(FName(NAME_None).ToString()));
	if (!DisplayStrings.Contains(DefaultValue))
	{
		DisplayStrings.Insert(DefaultValue, 0);
	}

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

	if (!KeyHandle.IsValid())
	{
		return;
	}

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
