// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SGraphPin.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphUtilities.h"

/**
 * Slate in the graph pin pull-down menu on the Blueprint Editor.
 */
class EASYPULLDOWNSTRUCTED_API SEPS_PulldownGraphPin : public SGraphPin
{
protected:
	// List of character strings displayed in the pull-down menu.
	TArray<TSharedPtr<FString>> DisplayStrings;

	// Currently selected string.
	FName Key;

public:
	SLATE_BEGIN_ARGS(SEPS_PulldownGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	// SGraphPin interface.
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	// End of SGraphPin interface.

protected:
	// Called when the value is changed in the pull-down menu.
	virtual void OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
};

/**
 * A factory class that registers a custom graph pin that displays a pull-down menu.
 */
class EASYPULLDOWNSTRUCTED_API FEPS_PulldownGraphPinFactory : public FGraphPanelPinFactory
{
	// FGraphPanelPinFactory interface.
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;
	// End of FGraphPanelPinFactory interface.
};
