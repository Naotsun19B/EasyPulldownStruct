// Fill out your copyright notice in the Description page of Project Settings.

#include "Misc/PulldownStructRegistry.h"
#include "EditorGlobals.h"
#include "PulldownSlate/PulldownDetails.h"
#include "Misc/PulldownStructEditorUtils.h"
#include "Misc/PulldownGraphPinFactory.h"
#include "BaseStruct/PulldownStructBase.h"
#include "PulldownStructAsset/PulldownStructAsset.h"
#include "PropertyEditorModule.h"
#include "AssetRegistryHelpers.h"
#include "AssetRegistryModule.h"

UPulldownStructRegistry* UPulldownStructRegistry::Get()
{
	if (GEditor)
	{
		return GEditor->GetEditorSubsystem<UPulldownStructRegistry>();
	}

	return nullptr;
}

void UPulldownStructRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Register a factory class that generates pins for pull-down menus.
	FPulldownGraphPinFactory::RegisterPulldownGraphPinFactory();

	// Register a natively defined pull-down menu structure in details panel customization.	
	TArray<UStruct*> NativePulldownStructs;
	GetNativePulldownStructs(NativePulldownStructs);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& NativePulldownStruct : NativePulldownStructs)
	{
		PropertyModule.RegisterCustomPropertyTypeLayout(NativePulldownStruct->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IPulldownDetail::MakeInstance));
		RegisteredPulldownStructs.AddUnique(NativePulldownStruct);
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been registered in details panel customization."), *NativePulldownStruct->GetName());
	}

	// Register pull-down menu structure assets in details panel customization when registered in AssetRegistry.
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	AssetRegistry.OnAssetAdded().AddLambda([this, &PropertyModule](const FAssetData& AddedAsset)
	{
		if (AddedAsset.AssetClass != UPulldownStructAsset::StaticClass()->GetFName())
		{
			return;
		}

		if (auto PulldownStructAsset = Cast<UPulldownStructAsset>(AddedAsset.GetAsset()))
		{
			PropertyModule.RegisterCustomPropertyTypeLayout(PulldownStructAsset->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IPulldownDetail::MakeInstance));
			RegisteredPulldownStructs.AddUnique(PulldownStructAsset);
			UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been registered in details panel customization."), *PulldownStructAsset->GetName());
		}
	});
}

void UPulldownStructRegistry::Deinitialize()
{
	// Unregister if it inherits FPulldownStructBase or UPulldownStructAsset.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& PulldownStruct : RegisteredPulldownStructs)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(PulldownStruct->GetFName());
		UE_LOG(LogEasyPulldownStruct, Log, TEXT("%s has been unregistered from the details panel customization."), *PulldownStruct->GetName());
	}

	Super::Deinitialize();
}

void UPulldownStructRegistry::GetNativePulldownStructs(TArray<UStruct*>& PulldownStructs)
{
	for (TObjectIterator<UStruct> Itr; Itr; ++Itr)
	{
		UStruct* Struct = *Itr;
		if (FPulldownStructEditorUtils::IsInheritPulldownStructBase(Struct))
		{
			PulldownStructs.Add(Struct);
		}
	}
}

void UPulldownStructRegistry::GetPulldownStructAssets(TArray<UStruct*>& PulldownStructs)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(TEXT("/Game/")));
	Filter.ClassNames.Add(UPulldownStructAsset::StaticClass()->GetFName());
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

void UPulldownStructRegistry::GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs)
{
	GetNativePulldownStructs(PulldownStructs);
	GetPulldownStructAssets(PulldownStructs);
}
