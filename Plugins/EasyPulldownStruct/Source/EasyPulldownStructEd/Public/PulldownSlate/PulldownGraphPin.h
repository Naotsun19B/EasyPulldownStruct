// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

/**
 * Slate in the graph pin pull-down menu on the Blueprint Editor.
 */
class EASYPULLDOWNSTRUCTED_API SPulldownGraphPin : public SGraphPin
{
protected:
	// List of character strings displayed in the pull-down menu.
	TArray<TSharedPtr<FString>> DisplayStrings;

	// Currently selected string.
	FName Key;

public:
	SLATE_BEGIN_ARGS(SPulldownGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

	// SGraphPin interface.
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
	// End of SGraphPin interface.

protected:
	// Called when the value is changed in the pull-down menu.
	virtual void OnValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
};
