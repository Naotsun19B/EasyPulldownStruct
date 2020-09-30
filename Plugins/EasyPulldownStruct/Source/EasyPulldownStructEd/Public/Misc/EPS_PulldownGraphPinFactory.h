// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class SGraphPin;
class UEdGraphPin;

/**
 * A factory class that registers a custom graph pin that displays a pull-down menu.
 */
class EASYPULLDOWNSTRUCTED_API FEPS_PulldownGraphPinFactory : public FGraphPanelPinFactory
{
	// FGraphPanelPinFactory interface.
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;
	// End of FGraphPanelPinFactory interface.
};
