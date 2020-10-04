// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructAsset/EPS_AssetTypeActions_PulldownStructAsset.h"
#include "EPS_EditorGlobals.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"
#include "Toolkits/SimpleAssetEditor.h"

UClass* FEPS_AssetTypeActions_PulldownStructAsset::GetSupportedClass() const
{
	return UEPS_PulldownStructAsset::StaticClass();
}

FText FEPS_AssetTypeActions_PulldownStructAsset::GetAssetDescription(const FAssetData & AssetData) const
{
	FString Description = AssetData.GetTagValueRef<FString>("Tooltip");
	if (!Description.IsEmpty())
	{
		Description.ReplaceInline(TEXT("\\n"), TEXT("\n"));
		return FText::FromString(MoveTemp(Description));
	}

	return FText::GetEmpty();
}
