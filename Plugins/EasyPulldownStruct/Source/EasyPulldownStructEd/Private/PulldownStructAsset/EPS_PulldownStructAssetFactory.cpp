// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/EPS_PulldownStructAssetFactory.h"
#include "EPS_EditorGlobals.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "Kismet2/StructureEditorUtils.h"
#include "UserDefinedStructure/UserDefinedStructEditorData.h"

UEPS_PulldownStructAssetFactory::UEPS_PulldownStructAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UEPS_PulldownStructAsset::StaticClass();
	bCreateNew = true;
}

bool UEPS_PulldownStructAssetFactory::DoesSupportClass(UClass* Class)
{
	return (Class == UEPS_PulldownStructAsset::StaticClass());
}

UClass* UEPS_PulldownStructAssetFactory::ResolveSupportedClass()
{
	return UEPS_PulldownStructAsset::StaticClass();
}

UObject* UEPS_PulldownStructAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	ensure(UEPS_PulldownStructAsset::StaticClass() == Class);

	// Create a structure asset for pull-down menu through the processing required for a normal structure asset.
	UEPS_PulldownStructAsset* PulldownStructAsset = NewObject<UEPS_PulldownStructAsset>(InParent, Name, Flags);
	check(PulldownStructAsset);

	PulldownStructAsset->EditorData = NewObject<UUserDefinedStructEditorData>(PulldownStructAsset, NAME_None, RF_Transactional);
	check(PulldownStructAsset->EditorData);

	PulldownStructAsset->Guid = FGuid::NewGuid();
	PulldownStructAsset->SetMetaData(TEXT("BlueprintType"), TEXT("true"));
	PulldownStructAsset->Bind();
	PulldownStructAsset->StaticLink(true);
	PulldownStructAsset->Status = UDSS_Error;

	// Add a variable of type FName.
	FStructureEditorUtils::AddVariable(PulldownStructAsset, FEdGraphPinType(UEdGraphSchema_K2::PC_Name, NAME_None, nullptr, EPinContainerType::None, false, FEdGraphTerminalType()));

	// Find the pointer to the added variable.
	FProperty* AddedVariable = nullptr;
	for (TFieldIterator<FProperty> PropertyItr(PulldownStructAsset); PropertyItr; ++PropertyItr)
	{
		FProperty* Property = *PropertyItr;
#if BEFORE_UE425
		if (auto NameProperty = Cast<UNameProperty>(Property))
#else
		if (auto NameProperty = CastField<FNameProperty>(Property))
#endif
		{
			AddedVariable = Property;
			break;
		}
	}

	// Change the variable name of the additional variable to "Key".
	check(AddedVariable);
	const FGuid& VariableGuid = FStructureEditorUtils::GetGuidForProperty(AddedVariable);
	FStructureEditorUtils::RenameVariable(PulldownStructAsset, VariableGuid, TEXT("Key"));

	return PulldownStructAsset;
}
