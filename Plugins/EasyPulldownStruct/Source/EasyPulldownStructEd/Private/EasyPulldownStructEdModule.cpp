// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "EPS_EditorGlobals.h"
#include "Misc/EPS_PulldownStructEditorUtils.h"
#include "Misc/EPS_PulldownGraphPinFactory.h"
#include "PulldownStructAsset/EPS_AssetTypeActions_PulldownStructAsset.h"

DEFINE_LOG_CATEGORY(LogEasyPulldownStruct);

class FEasyPulldownStructModuleEd : public IModuleInterface
{
private:
	// An instance of a class that defines information and operations for structure assets for pull-down menus.
	TSharedPtr<FEPS_AssetTypeActions_PulldownStructAsset> AssetTypeActions;

public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.
};

void FEasyPulldownStructModuleEd::StartupModule()
{
	// Register a class that defines information and operations of structure assets for pull-down menu.
	AssetTypeActions = MakeShareable(new FEPS_AssetTypeActions_PulldownStructAsset());
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());

	// Register a factory class that generates pins for pull-down menus.
	FEPS_PulldownGraphPinFactory::RegisterPulldownGraphPinFactory();

	// Register all pull-down menu structures existing in the project with details panel customization.
	FEPS_PulldownStructEditorUtils::RegisterPulldownStructToDetailsCustomization();
}

void FEasyPulldownStructModuleEd::ShutdownModule()
{
	// Unregister all pull-down menu structures existing in the project with details panel customization.
	FEPS_PulldownStructEditorUtils::UnregisterPulldownStructToDetailsCustomization();

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

IMPLEMENT_MODULE(FEasyPulldownStructModuleEd, EasyPulldownStructEd)
