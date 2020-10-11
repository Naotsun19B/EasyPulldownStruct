// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "EPS_EditorGlobals.h"
#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "PulldownSlate/EPS_PulldownDetail.h"
#include "PulldownStructAsset/EPS_AssetTypeActions_PulldownStructAsset.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "PulldownStructAsset/EPS_PulldownStructAsset.h"

DEFINE_LOG_CATEGORY(LogEasyPulldownStruct);

class FEasyPulldownStructModuleEd : public IModuleInterface
{
private:
	// An instance of a class that defines information and operations for structure assets for pull-down menus.
	TSharedPtr<FEPS_AssetTypeActions_PulldownStructAsset> AssetTypeActions;

	// List of structure type names registered as pull-down menu.
	TArray<FName> RegisteredPulldownTypes;

public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.

private:
	// Called when a structure is registered as a pull-down menu.
	void HandleOnRegisterPulldownStruct(const FName& StructName);
};

void FEasyPulldownStructModuleEd::StartupModule()
{
	// Register a class that defines information and operations of structure assets for pull-down menu.
	AssetTypeActions = MakeShareable(new FEPS_AssetTypeActions_PulldownStructAsset());
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());

	// Register a factory class that generates pins for pull-down menus.
	FEPS_PulldownGraphPinFactory::RegisterPulldownGraphPinFactory();
}

void FEasyPulldownStructModuleEd::ShutdownModule()
{
	// Unregister to display the pull-down menu in the details panel.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	for (const auto& TypeName : RegisteredPulldownTypes)
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout(TypeName);
	}

	// Unregister a class that defines information and operations of structure assets for pull-down menu.
	if (AssetTypeActions.IsValid())
	{
		if (FAssetToolsModule::IsModuleLoaded())
		{
			FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AssetTypeActions.ToSharedRef());
			AssetTypeActions.Reset();
		}
	}
}

void FEasyPulldownStructModuleEd::HandleOnRegisterPulldownStruct(const FName& StructName)
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&IEPS_PulldownDetail::MakeInstance));
	RegisteredPulldownTypes.Add(StructName);
}

IMPLEMENT_MODULE(FEasyPulldownStructModuleEd, EasyPulldownStructEd)
