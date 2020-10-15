// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/AssetTypeActions_PulldownStructAsset.h"
#include "EditorGlobals.h"
#include "PulldownStructAsset/PulldownStructAsset.h"
#include "Toolkits/SimpleAssetEditor.h"

UClass* FAssetTypeActions_PulldownStructAsset::GetSupportedClass() const
{
	return UPulldownStructAsset::StaticClass();
}

FText FAssetTypeActions_PulldownStructAsset::GetAssetDescription(const FAssetData & AssetData) const
{
	FString Description = AssetData.GetTagValueRef<FString>("Tooltip");
	if (!Description.IsEmpty())
	{
		Description.ReplaceInline(TEXT("\\n"), TEXT("\n"));
		return FText::FromString(MoveTemp(Description));
	}

	return FText::GetEmpty();
}
