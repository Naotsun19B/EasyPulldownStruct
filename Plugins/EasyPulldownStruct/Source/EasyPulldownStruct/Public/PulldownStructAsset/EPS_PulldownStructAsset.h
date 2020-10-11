﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "EPS_PulldownStructAsset.generated.h"

class UDataTable;
class UStringTable;
struct FPropertyChangedEvent;

/**
 * Structure asset class for pull-down menus.
 * Created by extending standard structure assets.
 */
UCLASS()
class EASYPULLDOWNSTRUCT_API UEPS_PulldownStructAsset : public UUserDefinedStruct
{
	GENERATED_BODY()

#if WITH_EDITORONLY_DATA
protected:
	// The content is copied to the Tooltip of a regular struct asset.
	UPROPERTY(EditAnywhere, Category = "Tooltip", meta = (MultiLine = true))
	FString Tooltip;

	// Type of data that is the basis of the pull-down menu.
	UPROPERTY(EditAnywhere, Category = "PulldownSource")
	EEPS_PulldownSource PulldownSource;

	// Data table asset from which the pull-down menu is based.
	UPROPERTY(EditAnywhere, Category = "PulldownSource", meta = (EditCondition = "PulldownSource == EEPS_PulldownSource::DataTable"))
	UDataTable* SourceDataTable;

	// String table asset from which the pull-down menu is based.
	UPROPERTY(EditAnywhere, Category = "PulldownSource", meta = (EditCondition = "PulldownSource == EEPS_PulldownSource::StringTable"))
	UStringTable* SourceStringTable;

	// An array of strings that is the basis of the pull-down menu.
	UPROPERTY(EditAnywhere, Category = "PulldownSource", meta = (EditCondition = "PulldownSource == EEPS_PulldownSource::Array"))
	TArray<FString> SourceArray;
#endif

#if WITH_EDITOR
public:
	// UObject interface.
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface.

	// Get the items to be displayed in the pull-down menu.
	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const;
#endif
};
