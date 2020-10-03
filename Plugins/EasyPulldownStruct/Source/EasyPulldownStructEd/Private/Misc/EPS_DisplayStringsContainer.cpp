// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_DisplayStringsContainer.h"
#include "EPS_EditorGlobals.h"
#include "PropertyEditorModule.h"
#include "PulldownSlate/EPS_PulldownDetail.h"

UEPS_DisplayStringsContainer* UEPS_DisplayStringsContainer::This = nullptr;

UEPS_DisplayStringsContainer* UEPS_DisplayStringsContainer::Get()
{
	if (!IsValid(This))
	{
		This = NewObject<UEPS_DisplayStringsContainer>();
		check(This);
		This->AddToRoot();
	}

	return This;
}

void UEPS_DisplayStringsContainer::BeginDestroy()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	TArray<FString> Keys;
	DisplayStringsList.GetKeys(Keys);
	for (const auto& Key : Keys)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(FName(Key));
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("Unregistered - %s"), *Key);
	}

	Super::BeginDestroy();
}

bool UEPS_DisplayStringsContainer::RegisterDisplayStrings(const FString& StructName, const TArray<TSharedPtr<FString>>& DisplayStrings)
{
	// Check for duplicates.
	bool bCanRegister = !DisplayStringsList.Contains(StructName);
	if (bCanRegister)
	{
		DisplayStringsList.Add(StructName, DisplayStrings);

		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"); 
		PropertyModule.RegisterCustomPropertyTypeLayout(FName(StructName), FOnGetPropertyTypeCustomizationInstance::CreateLambda([StructName]() -> TSharedRef<IPropertyTypeCustomization> 
		{ 
				TArray<TSharedPtr<FString>> DisplayStrings; 
				UEPS_DisplayStringsContainer::Get()->GetDisplayStrings(StructName, DisplayStrings); 
				return IEPS_PulldownDetail::MakeInstance(DisplayStrings); 
		})); 

		UE_LOG(LogEasyPulldownStruct, Log, TEXT("Registered - %s"), *StructName);
	}
	return bCanRegister;
}

bool UEPS_DisplayStringsContainer::GetDisplayStrings(const FString& StructName, TArray<TSharedPtr<FString>>& DisplayStrings)
{
	if (DisplayStringsList.Contains(StructName))
	{
		DisplayStrings.Empty();
		DisplayStrings = DisplayStringsList[StructName];

		// Be sure to put "None" so that the list is not empty.
		const TSharedPtr<FString>& DefaultValue = MakeShareable(new FString(FName(NAME_None).ToString()));
		if (!DisplayStrings.Contains(DefaultValue))
		{
			DisplayStrings.Insert(DefaultValue, 0);
		}

		return true;
	}

	return false;
}
