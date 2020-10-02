// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#include "PulldownSlate/EPS_PulldownDetail.h"
#include "Misc/EPS_DisplayStringsContainer.h"
#endif

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

	// Get the items to be displayed in the pull-down menu.
	// Build a list from data tables, arrays, etc. at the inheritance destination.
	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const { return TArray<TSharedPtr<FString>>(); }
};

/**
 * Macro for registration required to display pull-down menu on editor.
 * Place it in the constructor of a structure that inherits FEPS_PulldownStructBase.
 */
#if WITH_EDITOR
#define REGISTER_PULLDOWN_STRUCT() \
	const FString& StructName = StaticStruct()->GetName(); \
	UEPS_DisplayStringsContainer::Get()->RegisterDisplayStrings(StructName, GetDisplayStrings()); \
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"); \
	PropertyModule.RegisterCustomPropertyTypeLayout(FName(StructName), FOnGetPropertyTypeCustomizationInstance::CreateLambda([this]() -> TSharedRef<IPropertyTypeCustomization> \
	{ \
		return IEPS_PulldownDetail::MakeInstance(GetDisplayStrings()); \
	}));

	// static_assert(TIsDerivedFrom<TResult, FEPS_PulldownStructBase>::IsDerived, "This class or struct does not inherit from FEPS_PulldownStructBase."); 
#else
#define REGISTER_PULLDOWN_STRUCT()
#endif

USTRUCT(BlueprintType)
struct EASYPULLDOWNSTRUCT_API FTestStruct : public FEPS_PulldownStructBase
{
	GENERATED_BODY()

public:
	FTestStruct()
	{
		REGISTER_PULLDOWN_STRUCT();
	}

	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const override 
	{
		return TArray<TSharedPtr<FString>> 
		{
			MakeShareable(new FString(TEXT("Item A"))),
			MakeShareable(new FString(TEXT("Item B"))),
			MakeShareable(new FString(TEXT("Item C")))
		};
	}
};

USTRUCT(BlueprintType)
struct EASYPULLDOWNSTRUCT_API FTestStruct2 : public FEPS_PulldownStructBase
{
	GENERATED_BODY()

public:
	FTestStruct2()
	{
		REGISTER_PULLDOWN_STRUCT();
	}

	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const override
	{
		return TArray<TSharedPtr<FString>>
		{
			MakeShareable(new FString(TEXT("Hoge"))),
				MakeShareable(new FString(TEXT("Fuga"))),
				MakeShareable(new FString(TEXT("Piyo")))
		};
	}
};
