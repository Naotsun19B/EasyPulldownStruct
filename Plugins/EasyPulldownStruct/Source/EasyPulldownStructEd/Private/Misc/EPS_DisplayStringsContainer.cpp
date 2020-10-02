// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_DisplayStringsContainer.h"
#include "PropertyEditorModule.h"

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
	}

	Super::BeginDestroy();
}

void UEPS_DisplayStringsContainer::RegisterDisplayStrings(const FString& StructName, const TArray<TSharedPtr<FString>>& DisplayStrings)
{
	// Check for duplicates.
	if (!DisplayStringsList.Contains(StructName))
	{
		DisplayStringsList.Add(StructName, DisplayStrings);
	}
}

bool UEPS_DisplayStringsContainer::GetDisplayStrings(const FString& StructName, TArray<TSharedPtr<FString>>& DisplayStrings)
{
	if (DisplayStringsList.Contains(StructName))
	{
		DisplayStrings = DisplayStringsList[StructName];
		return true;
	}

	return false;
}
