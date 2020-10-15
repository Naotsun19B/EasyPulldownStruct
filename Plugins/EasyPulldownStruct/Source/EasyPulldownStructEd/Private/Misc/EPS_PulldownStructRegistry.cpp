// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/EPS_PulldownStructRegistry.h"
#include "EPS_EditorGlobals.h"
#include "PulldownSlate/EPS_PulldownDetail.h"
#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "PropertyEditorModule.h"
#include "AssetRegistryHelpers.h"
#include "AssetRegistryModule.h"

UEPS_PulldownStructRegistry* UEPS_PulldownStructRegistry::Get()
{
	if (GEditor)
	{

	}

	return nullptr;
}

void UEPS_PulldownStructRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Register a factory class that generates pins for pull-down menus.
	FEPS_PulldownGraphPinFactory::RegisterPulldownGraphPinFactory();

	// Register a natively defined pull-down menu structure in details panel customization.	
	TArray<UStruct*> NativePulldownStructs;
	GetNativePulldownStructs(NativePulldownStructs);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& NativePulldownStruct : NativePulldownStructs)
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(NativePulldownStruct->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IEPS_PulldownDetail::MakeInstance));
		RegisteredPulldownStructs.AddUnique(NativePulldownStruct);
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been registered in details panel customization."), *NativePulldownStruct->GetName());
	}

	// Register pull-down menu structure assets in details panel customization when registered in AssetRegistry.
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	AssetRegistry.OnAssetAdded().AddLambda([this, &PropertyModule](const FAssetData& AddedAsset)
	{
		if (AddedAsset.AssetClass != UEPS_PulldownStructAsset::StaticClass()->GetFName())
		{
			return;
		}

		if (auto PulldownStructAsset = Cast<UEPS_PulldownStructAsset>(AddedAsset.GetAsset()))
		{
			PropertyModule.RegisterCustomPropertyTypeLayout(PulldownStructAsset->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IEPS_PulldownDetail::MakeInstance));
			RegisteredPulldownStructs.AddUnique(PulldownStructAsset);
			UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been registered in details panel customization."), *PulldownStructAsset->GetName());
		}
	});
}

void UEPS_PulldownStructRegistry::Deinitialize()
{
	// Unregister if it inherits FEPS_PulldownStructBase or UEPS_PulldownStructAsset.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& PulldownStruct : RegisteredPulldownStructs)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(PulldownStruct->GetFName());
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been unregistered from the details panel customization."), *PulldownStruct->GetName());
	}

	Super::Deinitialize();
}

void UEPS_PulldownStructRegistry::GetNativePulldownStructs(TArray<UStruct*>& PulldownStructs)
{
	for (TObjectIterator<UStruct> Itr; Itr; ++Itr)
	{
		UStruct* Struct = *Itr;
		if (FEPS_PulldownStructEditorUtils::IsInheritPulldownStructBase(Struct))
		{
			PulldownStructs.Add(Struct);
		}
	}
}

void UEPS_PulldownStructRegistry::GetPulldownStructAssets(TArray<UStruct*>& PulldownStructs)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(TEXT("/Game/")));
	Filter.ClassNames.Add(UEPS_PulldownStructAsset::StaticClass()->GetFName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;
	Filter.bIncludeOnlyOnDiskAssets = false;

	AssetRegistry.EnumerateAllAssets([&PulldownStructs](const FAssetData& AssetData) -> bool
	{
		if (auto Asset = Cast<UStruct>(AssetData.GetAsset()))
		{
			PulldownStructs.Add(Asset);
		}

		return true;
	});
}

void UEPS_PulldownStructRegistry::GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs)
{
	GetNativePulldownStructs(PulldownStructs);
	GetPulldownStructAssets(PulldownStructs);
}
