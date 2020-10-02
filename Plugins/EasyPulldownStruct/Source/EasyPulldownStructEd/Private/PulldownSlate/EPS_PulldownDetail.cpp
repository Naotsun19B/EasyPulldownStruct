// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownSlate/EPS_PulldownDetail.h"
#include "EPS_EditorGlobals.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "PropertyHandle.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"

TSharedRef<IPropertyTypeCustomization> IEPS_PulldownDetail::MakeInstance(const TArray<TSharedPtr<FString>>& InDisplayStrings)
{
	TSharedRef<IEPS_PulldownDetail> Instance = MakeShareable(new IEPS_PulldownDetail());
	//Instance.Get().DisplayStrings.Add(MakeShareable(new FString(FName(NAME_None).ToString())));
	Instance.Get().DisplayStrings.Append(InDisplayStrings);
	return Instance;
}

void IEPS_PulldownDetail::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle = InStructPropertyHandle;

	uint32 NumChildren;
	StructPropertyHandle->GetNumChildren(NumChildren);

	FName Key;
	for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
	{
		const TSharedPtr< IPropertyHandle > ChildHandle = StructPropertyHandle->GetChildHandle(ChildIndex);
		if (ChildHandle->GetProperty()->GetName() == TEXT("Key"))
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
		Key = TEXT("None");
		KeyHandle->SetValue(Key);
		UE_LOG(LogEasyPulldownStruct, Error, TEXT("The string \"%s\" was not found in the list."), *Key.ToString());
	}

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
		if (DisplayStrings.Find(ItemSelected))
		{
			KeyHandle->SetValue(FName(**ItemSelected));
		}
	}
}
