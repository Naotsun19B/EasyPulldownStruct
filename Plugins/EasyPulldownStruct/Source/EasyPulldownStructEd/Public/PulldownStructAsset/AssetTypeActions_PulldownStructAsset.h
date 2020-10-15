// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

struct FAssetData;
class IToolkitHost;

/**
 * Structure for pull-down menu in editor class that defines asset information and 
 * operations that can be performed on the asset.
 */
class FAssetTypeActions_PulldownStructAsset : public FAssetTypeActions_Base
{
public:
	// FAssetTypeActions_Base interface.
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PulldownStructAsset", "Pulldown Structure"); }
	virtual FColor GetTypeColor() const override { return FColor(103, 206, 218); }
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Blueprint; }
	virtual bool CanLocalize() const override { return false; }
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;
	// End of FAssetTypeActions_Base interface.
};