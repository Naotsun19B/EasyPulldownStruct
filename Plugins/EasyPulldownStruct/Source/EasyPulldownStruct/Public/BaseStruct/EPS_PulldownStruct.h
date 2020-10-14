// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/EPS_PulldownStructUtils.h"
#include "EPS_PulldownStruct.generated.h"

class UDataTable;
class UStringTable;

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

public:
	// Constructor.
	FEPS_PulldownStructBase(const FName& InKey) : Key(InKey) {}
	FEPS_PulldownStructBase() : Key(NAME_None) {}

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

#if WITH_EDITOR
protected:
	// Get type of data that is the basis of the pull-down menu.
	virtual EEPS_PulldownSource GetPulldownSourceType() const { return EEPS_PulldownSource::InValid; }
	
	// Get data table asset from which the pull-down menu is based.
	virtual UDataTable* GetSourceDataTable() const { return nullptr; }
	
	// Get string table asset from which the pull-down menu is based.
	virtual UStringTable* GetSourceStringTable() const { return nullptr; }
	
	// Get array of strings that is the basis of the pull-down menu.
	virtual TArray<FString> GetSourceArray() const { return TArray<FString>(); }

	// It is used inside the macro registered in the pull-down menu.
	void RegisterPulldownStructInternal(UScriptStruct* StaticStruct);
#endif
};

#if WITH_EDITOR
/**
 * A container class that summarizes the necessary data in the pull-down menu.
 */
UCLASS()
class EASYPULLDOWNSTRUCT_API UEPS_PulldownData : public UObject
{
	GENERATED_BODY()

private:
	friend FEPS_PulldownStructBase;

	// Type of data that is the basis of the pull-down menu.
	UPROPERTY()
	EEPS_PulldownSource SourceType;

	// Data table asset from which the pull-down menu is based.
	UPROPERTY()
	UDataTable* SourceDataTable;

	// String table asset from which the pull-down menu is based.
	UPROPERTY()
	UStringTable* SourceStringTable;

	// An array of strings that is the basis of the pull-down menu.
	UPROPERTY()
	TArray<FString> SourceArray;

public:
	// Get the items to be displayed in the pull-down menu.
	TArray<TSharedPtr<FString>> GetDisplayStrings() const;
};
#endif

#if WITH_EDITOR
/**
 * Macro for registration required to display pull-down menu on editor.
 * Place it in the constructor of a structure that inherits FEPS_PulldownStructBase.
 */
#define REGISTER_PULLDOWN_STRUCT() \
	RegisterPulldownStructInternal(StaticStruct()); \
	static_cast<FEPS_PulldownStructBase*>(this); // Prevents use in structures that do not inherit from FEPS_PulldownStructBase.
#else
#define REGISTER_PULLDOWN_STRUCT()
#endif
