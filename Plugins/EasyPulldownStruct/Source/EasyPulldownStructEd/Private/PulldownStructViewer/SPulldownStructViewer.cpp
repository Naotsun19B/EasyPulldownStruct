// Fill out your copyright notice in the Description page of Project Settings.

#include "PulldownStructViewer/SPulldownStructViewer.h"
#include "Misc/PulldownStructRegistry.h"
#include "Misc/PulldownStructEditorUtils.h"
#include "BaseStruct/PulldownStructBase.h"
#include "PulldownStructAsset/PulldownStructAsset.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Views/STreeView.h"

namespace RowFontSize
{
	static const int32 Root = 16;
	static const int32 StructName = 13;
	static const int32 PulldownItem = 10;
}

const FName SPulldownStructViewer::TabName = TEXT("PulldownStructViewerTab");
const FText SPulldownStructViewer::WindowTitle = FText::FromString(TEXT("Pulldown Struct Viewer"));

#define LOCTEXT_NAMESPACE "PulldownStructViewer"

void SPulldownStructViewer::Construct(const FArguments& InArgs)
{
	if (auto PulldownStructRegistry = UPulldownStructRegistry::Get())
	{
		PulldownStructRegistry->OnPulldownStructRegistered.BindLambda([this](UStruct* RegisteredPulldownStruct)
		{
			UpdateTreeView();
		});

		PulldownStructRegistry->OnPulldownStructUnregistered.BindLambda([this]()
		{
			UpdateTreeView();
		});
	}

	UpdateTreeView();

	// Build Slate based on the created data.
	ChildSlot
	[
		SAssignNew(TreeView, STreeView<TSharedPtr<FTreeViewRow>>)
		.ItemHeight(24)
		.TreeItemsSource(&ItemList)
		.OnGenerateRow(this, &SPulldownStructViewer::OnGenerateRow)
		.OnGetChildren(this, &SPulldownStructViewer::OnGetChildren)
		.SelectionMode(ESelectionMode::None)
	];
}

TSharedRef<ITableRow> SPulldownStructViewer::OnGenerateRow(FRowType InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<TSharedPtr<FTreeViewRow>>>, OwnerTable)
		[
			SNew(STextBlock)
			.Text(InItem->GetDisplayText())
			.Font(FSlateFontInfo(FCoreStyle::GetDefaultFont(), InItem->GetFontSize()))
		];
}

void SPulldownStructViewer::OnGetChildren(FRowType InItem, TArray<FRowType>& OutChildren)
{
	OutChildren += InItem->GetChildren();
}

void SPulldownStructViewer::UpdateTreeView()
{
	ItemList.Reset();

	// Create data from a list of registered pull-down menu structures.
	TArray<UStruct*> NativePulldownStructs;
	TArray<UPulldownStructAsset*> PulldownStructAssets;
	if (auto PulldownStructRegistry = UPulldownStructRegistry::Get())
	{
		PulldownStructRegistry->GetNativePulldownStructs(NativePulldownStructs);
		PulldownStructRegistry->GetPulldownStructAssets(PulldownStructAssets);
	}

	for (const auto& PulldownStructAsset : PulldownStructAssets)
	{
		if (!PulldownStructAsset->OnSourceTypeChanged.IsBound())
		{
			PulldownStructAsset->OnSourceTypeChanged.BindLambda([this](UPulldownStructAsset* ChangedAsset)
			{
				UpdateTreeView();
			});
		}
	}

	FRowType NativeRoot(MakeShareable(new FTreeViewRow(FText::FromString(TEXT("Native Pulldown Struct")), RowFontSize::Root)));
	ItemList.Add(NativeRoot);
	for (const auto& NativePulldownStruct : NativePulldownStructs)
	{
		FString StructName;
		TArray<TSharedPtr<FString>> PulldownList;
		if (UPulldownData* PulldownData = FPulldownStructEditorUtils::GetPulldownData(NativePulldownStruct))
		{
			StructName = FString::Printf(TEXT("%s (Pulldown Source = %s)"), *NativePulldownStruct->GetName(), *UEnum::GetDisplayValueAsText(PulldownData->GetSourceType()).ToString());
			PulldownList = PulldownData->GetDisplayStrings();
		}
		else
		{
			continue;
		}

		FRowType StructNameRow(MakeShareable(new FTreeViewRow(FText::FromString(StructName), RowFontSize::StructName)));
		NativeRoot->AddChild(StructNameRow);
		for (const auto& PulldownItem : PulldownList)
		{
			StructNameRow->AddChild(MakeShareable(new FTreeViewRow(FText::FromString(*PulldownItem), RowFontSize::PulldownItem)));
		}
	}

	FRowType AssetRoot(MakeShareable(new FTreeViewRow(FText::FromString(TEXT("Pulldown Struct Asset")), RowFontSize::Root)));
	ItemList.Add(AssetRoot);
	for (const auto& PulldownStructAsset : PulldownStructAssets)
	{
		if (!IsValid(PulldownStructAsset))
		{
			continue;
		}

		const FString& StructName = FString::Printf(TEXT("%s (Pulldown Source = %s)"), *PulldownStructAsset->GetName(), *UEnum::GetDisplayValueAsText(PulldownStructAsset->GetSourceType()).ToString());
		FRowType StructNameRow(MakeShareable(new FTreeViewRow(FText::FromString(StructName), RowFontSize::StructName)));
		AssetRoot->AddChild(StructNameRow);
		const auto& PulldownList = PulldownStructAsset->GetDisplayStrings();
		for (const auto& PulldownItem : PulldownList)
		{
			StructNameRow->AddChild(MakeShareable(new FTreeViewRow(FText::FromString(*PulldownItem), RowFontSize::PulldownItem)));
		}
	}

	if (TreeView.IsValid())
	{
		TreeView->RequestTreeRefresh();
	}
}

#undef LOCTEXT_NAMESPACE
