// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "EPS_PulldownStructRegistry.generated.h"

/**
 * 
 */
UCLASS()
class EASYPULLDOWNSTRUCTED_API UEPS_PulldownStructRegistry : public UEditorSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TArray<UStruct*> RegisteredPulldownStructs;

public:
	// Gets an instance of this subsystem.
	static UEPS_PulldownStructRegistry* Get();

	// USubsystem interface.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End of USubsystem interface.

	// Get the all structure inheriting FEPS_PulldownStructBase in the project.
	void GetNativePulldownStructs(TArray<UStruct*>& PulldownStructs);

	// Get all UEPS_PulldownStructAsset under the content folder.
	void GetPulldownStructAssets(TArray<UStruct*>& PulldownStructs);

	// Get the all structure inheriting FEPS_PulldownStructBase and UEPS_PulldownStructAsset in the project.
	void GetAllPulldownStructs(TArray<UStruct*>& PulldownStructs);
};
