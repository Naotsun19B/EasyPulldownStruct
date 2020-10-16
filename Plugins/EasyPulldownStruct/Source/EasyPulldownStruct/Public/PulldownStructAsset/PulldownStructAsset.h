// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Misc/PulldownStructUtils.h"
#include "PulldownStructAsset.generated.h"

class UDataTable;
class UStringTable;
struct FPropertyChangedEvent;

/**
 * Structure asset class for pull-down menus.
 * Created by extending standard structure assets.
 */
UCLASS()
class EASYPULLDOWNSTRUCT_API UPulldownStructAsset : public UUserDefinedStruct
{
	GENERATED_BODY()

#if WITH_EDITOR
public:
	// UObject interface.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface.

	// Get type of data that is the basis of the pull-down menu.
	EPulldownSource GetSourceType() const { return SourceType; }

	// Get the items to be displayed in the pull-down menu.
	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const;
#endif

#if WITH_EDITORONLY_DATA
public:
	// An event called when the original data that builds the pull-down menu changes.
	DECLARE_DELEGATE_OneParam(FOnSourceTypeChanged, UPulldownStructAsset* /* ChangedAsset */);
	FOnSourceTypeChanged OnSourceTypeChanged;

protected:
	// The content is copied to the Tooltip of a regular struct asset.
	UPROPERTY(EditAnywhere, Category = "Tooltip", meta = (MultiLine = true))
	FString Tooltip;

	// Type of data that is the basis of the pull-down menu.
	UPROPERTY(EditAnywhere, Category = "Pulldown Source")
	EPulldownSource SourceType = EPulldownSource::PS_DataTable;

	// Data table asset from which the pull-down menu is based.
	UPROPERTY(EditAnywhere, Category = "Pulldown Source", meta = (EditCondition = "SourceType == EPulldownSource::PS_DataTable"))
	UDataTable* SourceDataTable = nullptr;

	// String table asset from which the pull-down menu is based.
	UPROPERTY(EditAnywhere, Category = "Pulldown Source", meta = (EditCondition = "SourceType == EPulldownSource::PS_StringTable"))
	UStringTable* SourceStringTable = nullptr;

	// An array of strings that is the basis of the pull-down menu.
	UPROPERTY(EditAnywhere, Category = "Pulldown Source", meta = (EditCondition = "SourceType == EPulldownSource::PS_Array"))
	TArray<FString> SourceArray;
#endif
};
