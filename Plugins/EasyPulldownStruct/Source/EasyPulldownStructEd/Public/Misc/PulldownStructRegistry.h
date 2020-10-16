// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "PulldownStructRegistry.generated.h"

class UPulldownStructAsset;

/**
 * Manager class that collects pull-down menu structures and registers for various functions.
 */
UCLASS()
class EASYPULLDOWNSTRUCTED_API UPulldownStructRegistry : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	// Gets an instance of this subsystem.
	static UPulldownStructRegistry* Get();

	// USubsystem interface.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End of USubsystem interface.

	// Get the all structure inheriting FPulldownStructBase and UPulldownStructAsset in the project.
	const TArray<UStruct*>& GetAllPulldownStructs() const { return RegisteredPulldownStructs; }

	// Get the all structure inheriting FPulldownStructBase in the project.
	void GetNativePulldownStructs(TArray<UStruct*>& NativePulldownStructs);

	// Get all UPulldownStructAsset under the content folder.
	void GetPulldownStructAssets(TArray<UPulldownStructAsset*>& PulldownStructAssets);

public:
	// Event called when a new pull-down menu structure is added.
	DECLARE_DELEGATE_OneParam(FOnPulldownStructRegistered, UStruct* /* RegisteredPulldownStruct */);
	FOnPulldownStructRegistered OnPulldownStructRegistered;

	// Event called when a new pull-down menu structure is removed.
	DECLARE_DELEGATE(FOnPulldownStructUnregistered);
	FOnPulldownStructUnregistered OnPulldownStructUnregistered;

protected:
	// List of registered pull-down menu structures.
	UPROPERTY()
	TArray<UStruct*> RegisteredPulldownStructs;
};
