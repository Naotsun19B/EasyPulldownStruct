// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FTreeViewRow;

using FRowType = TSharedPtr<FTreeViewRow>;
using STreeViewType = STreeView<FRowType>;

// The data that makes up each element of the tree-structured list.
class FTreeViewRow : public TSharedFromThis<FTreeViewRow>
{
public:
	FTreeViewRow(const FText& InDisplayText, int32 InFontSize) 
		: Children(), DisplayText(InDisplayText), FontSize(InFontSize)
	{
	}

	virtual ~FTreeViewRow() {}

	// Get list of elements in the lower hierarchy.
	const TArray<TSharedPtr<FTreeViewRow>>& GetChildren() const { return Children; }

	// Get text displayed.
	const FText& GetDisplayText() const { return DisplayText; }

	// Get font size.
	int32 GetFontSize() const { return FontSize; }

	// Add elements to the lower hierarchy.
	void AddChild(TSharedPtr<FTreeViewRow> Child) { Children.Add(Child); }

protected:
	// List of elements in the lower hierarchy.
	TArray<TSharedPtr<FTreeViewRow>> Children;

	// Text displayed.
	FText DisplayText;

	// Font size.
	int32 FontSize;
};

// Slate in the viewer of the pull-down menu structure.
class SPulldownStructViewer : public SCompoundWidget
{
public:
	// ID to be registered in Tab Manager.
	static const FName TabName;

	// The title of the window to display.
	static const FText WindowTitle;

public:
	SLATE_BEGIN_ARGS(SPulldownStructViewer) {}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	virtual ~SPulldownStructViewer() {}

	// Functions related to tree display.
	virtual TSharedRef<ITableRow> OnGenerateRow(FRowType InItem, const TSharedRef<STableViewBase>& OwnerTable);
	virtual void OnGetChildren(FRowType InItem, TArray<FRowType>& OutChildren);

protected:
	// Update the contents of the list.
	virtual void UpdateTreeView();

private:
	// An instance of Slate that displays a tree.
	TSharedPtr<STreeViewType> TreeView;

	// List of items to display.
	TArray<FRowType> ItemList;
};
