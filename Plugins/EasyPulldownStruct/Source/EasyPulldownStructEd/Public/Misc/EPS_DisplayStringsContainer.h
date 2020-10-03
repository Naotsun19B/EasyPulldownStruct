// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EPS_DisplayStringsContainer.generated.h"

/**
 * A singleton class that holds a list of structure type names and strings to display in the pull-down menu.
 */
UCLASS()
class EASYPULLDOWNSTRUCTED_API UEPS_DisplayStringsContainer : public UObject
{
	GENERATED_BODY()
	
private:
	// Instance of this class.
	static UEPS_DisplayStringsContainer* This;

	// Map of the string list of the pull-down menu corresponding to the type name of the structure.
	TMap<FString, TArray<TSharedPtr<FString>>> DisplayStringsList;

public:
	// Get an instance of this class.
	static UEPS_DisplayStringsContainer* Get();

	// UObject interface.
	virtual void BeginDestroy() override;
	// End of UObject interface.

	// Register information on the map.
	// Returns false if already registered.
	bool RegisterDisplayStrings(const FString& StructName, const TArray<TSharedPtr<FString>>& DisplayStrings);
	
	// Unregister information on the map.
	// Returns false if not registered.
	bool UnregisterDisplayStrings(const FString& StructName);

	// Get the registered information.
	// Returns false if not registered.
	bool GetDisplayStrings(const FString& StructName, TArray<TSharedPtr<FString>>& DisplayStrings) const;

private:
	// Since it is a singleton class, the constructor is sealed.
	UEPS_DisplayStringsContainer() {}
};
