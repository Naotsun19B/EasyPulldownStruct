// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "PulldownStructRegistry.generated.h"

/**
 * 
 */
UCLASS()
class EASYPULLDOWNSTRUCTED_API UPulldownStructRegistry : public UEditorSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TArray<UStruct*> RegisteredPulldownStructs;

public:
	// Gets an instance of this subsystem.
	static UPulldownStructRegistry* Get();

	// USubsystem interface.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End of USubsystem interface.

	// Get the all structure inheriting FPulldownStructBase in the project.
	void GetNativePulldownStructs(TArray<UStruct*>& PulldownStructs);

	// Get all UPulldownStructAsset under the content folder.
	void GetPulldownStructAssets(TArray<UStruct*>& PulldownStructs);

	// Get the all structure inheriting FPulldownStructBase and UPulldownStructAsset in the project.
	void GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs);
};
