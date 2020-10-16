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

	// Bind pull-down menu structure event when an asset is deleted.
	FEditorDelegates::OnAssetsPreDelete.AddLambda([this](const TArray<UObject*>& AssetsToDelete)
	{
		for (const auto& AssetToDelete : AssetsToDelete)
		{
			if (auto PulldownStuctAsset = Cast<UPulldownStructAsset>(AssetToDelete))
			{
				RegisteredPulldownStructs.Remove(PulldownStuctAsset);
				OnPulldownStructUnregistered.ExecuteIfBound();
			}
		}
	});

	// Register a factory class that generates pins for pull-down menus.
	FPulldownGraphPinFactory::RegisterPulldownGraphPinFactory();

	// Register a natively defined pull-down menu structure in details panel customization.	
	TArray<UStruct*> NativePulldownStructs;
	for (TObjectIterator<UStruct> Itr; Itr; ++Itr)
	{
		UStruct* Struct = *Itr;
		if (FPulldownStructEditorUtils::IsInheritPulldownStructBase(Struct))
		{
			NativePulldownStructs.Add(Struct);
		}
	}

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
		
			OnPulldownStructRegistered.ExecuteIfBound(PulldownStructAsset);
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

void UPulldownStructRegistry::GetNativePulldownStructs(TArray<UStruct*>& NativePulldownStructs)
{
	for (const auto& RegisteredPulldownStruct : RegisteredPulldownStructs)
	{
		if (FPulldownStructEditorUtils::IsInheritPulldownStructBase(RegisteredPulldownStruct))
		{
			NativePulldownStructs.Add(RegisteredPulldownStruct);
		}
	}
}

void UPulldownStructRegistry::GetPulldownStructAssets(TArray<UPulldownStructAsset*>& PulldownStructAssets)
{
	for (const auto& RegisteredPulldownStruct : RegisteredPulldownStructs)
	{
		if (auto PulldownStructAsset = Cast<UPulldownStructAsset>(RegisteredPulldownStruct))
		{
			PulldownStructAssets.Add(PulldownStructAsset);
		}
	}
}
