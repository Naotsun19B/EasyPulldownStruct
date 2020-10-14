// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "EPS_EditorGlobals.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "PulldownSlate/EPS_PulldownDetail.h"
#include "PropertyEditorModule.h"
#include "AssetRegistryHelpers.h"
#include "AssetRegistryModule.h"

TArray<UStruct*> FEPS_PulldownStructEditorUtils::RegisteredPulldownStructs;

bool FEPS_PulldownStructEditorUtils::IsInheritPulldownStructBase(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		if (auto SuperStruct = InStruct->GetSuperStruct())
		{
			if (SuperStruct == FEPS_PulldownStructBase::StaticStruct())
			{
				return true;
			}

			if (!IsInheritPulldownStructBase(SuperStruct))
			{
				return false;
			}
		}
	}

	return false;
}

bool FEPS_PulldownStructEditorUtils::IsInheritPulldownStructAsset(UStruct* InStruct)
{
	if (IsValid(InStruct))
	{
		return UEPS_PulldownStructAsset::StaticClass()->IsChildOf(InStruct->GetClass());
	}
	
	return false;
}

UEPS_PulldownData* FEPS_PulldownStructEditorUtils::GetPulldownData(UStruct* InStruct)
{
	auto&& References = InStruct->ScriptAndPropertyObjectReferences;
	for (const auto& Reference : References)
	{
		if (auto PulldownData = Cast<UEPS_PulldownData>(Reference))
		{
			return PulldownData;
		}
	}

	return nullptr;
}

void FEPS_PulldownStructEditorUtils::GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs)
{
	// Get all the structures it inherits FEPS_PulldownStructBase in the project.
	for (TObjectIterator<UStruct> Itr; Itr; ++Itr)
	{
		UStruct* Struct = *Itr;
		if (IsInheritPulldownStructBase(Struct))
		{
			PulldownStructs.Add(Struct);
		}
	}

	// Get all UEPS_PulldownStructAsset under the content folder.
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(TEXT("/Game/")));
	Filter.ClassNames.Add(UEPS_PulldownStructAsset::StaticClass()->GetFName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;
	Filter.bIncludeOnlyOnDiskAssets = false;

	AssetRegistry.EnumerateAssets(Filter, [&PulldownStructs](const FAssetData& AssetData) -> bool
	{
		UE_LOG(LogEasyPulldownStruct, Warning, TEXT("%s"), *AssetData.AssetClass.ToString());

		return true;
	});
}

void FEPS_PulldownStructEditorUtils::RegisterPulldownStructToDetailsCustomization()
{
	TArray<UStruct*> PulldownStructs;
	GetAllPulldownStructs(PulldownStructs);
	
	// Register if it inherits FEPS_PulldownStructBase or UEPS_PulldownStructAsset.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& PulldownStruct : PulldownStructs)
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(PulldownStruct->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IEPS_PulldownDetail::MakeInstance));
		RegisteredPulldownStructs.AddUnique(PulldownStruct);
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been registered in details panel customization."), *PulldownStruct->GetName());
	}
}

void FEPS_PulldownStructEditorUtils::UnregisterPulldownStructToDetailsCustomization()
{
	// Unregister if it inherits FEPS_PulldownStructBase or UEPS_PulldownStructAsset.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& PulldownStruct : RegisteredPulldownStructs)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(PulldownStruct->GetFName());
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been unregistered from the details panel customization."), *PulldownStruct->GetName());
	}
}
