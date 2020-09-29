// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPS_PulldownStruct.generated.h"

/**
 * Base structure of the structure displayed as a pull-down menu.
 * To create a pull-down menu structure in C++, define a structure that inherits this structure.
 */
USTRUCT(BlueprintType)
struct EASYPULLDOWNSTRUCT_API FEPS_PulldownStructBase
{
	GENERATED_BODY()

public:
	// Variable to store the item selected in the pull-down menu.
	// Stores the value used at runtime.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Key;

	// Constructor.
	FEPS_PulldownStructBase(const FName& InKey) : Key(InKey) {}
	FEPS_PulldownStructBase() : Key(NAME_None) {};

	// Overload operators.
	FORCEINLINE bool operator ==(const FEPS_PulldownStructBase& Other) const
	{
		return (Key == Other.Key);
	}

	FORCEINLINE bool operator !=(const FEPS_PulldownStructBase& Other) const
	{
		return !(*this == Other);
	}

	FORCEINLINE bool operator ==(const FName& Other) const
	{
		return (Key == Other);
	}

	FORCEINLINE bool operator !=(const FName& Other) const
	{
		return !(*this == Other);
	}

	FORCEINLINE const FName& operator *() const
	{
		return Key;
	}

	// Get the items to be displayed in the pull-down menu.
	// Build a list from data tables, arrays, etc. at the inheritance destination.
	virtual void GetDisplayStrings(TArray<TSharedPtr<FString>>& DisplayStrings) const {}
};
