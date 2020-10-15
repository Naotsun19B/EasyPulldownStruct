// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "EPS_EditorGlobals.h"
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
}

void FEasyPulldownStructModuleEd::ShutdownModule()
{
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
