// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Misc/Paths.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "EditorGlobals.h"
#include "PulldownStructAsset/AssetTypeActions_PulldownStructAsset.h"
#include "PulldownStructViewer/SPulldownStructViewer.h"

DEFINE_LOG_CATEGORY(LogEasyPulldownStruct);

#define LOCTEXT_NAMESPACE "EasyPulldownStructModuleEd"

class FEasyPulldownStructModuleEd : public IModuleInterface
{
public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.

private:
	// Called when a pull-down menu structure viewer tab is created.
	TSharedRef<SDockTab> HandleRegisterTabSpawner(const FSpawnTabArgs& TabSpawnArgs);

	// Called when the level editor window tab is generated.
	void OnWindowMenuExtension(FMenuBuilder& MenuBuilder);

private:
	// An instance of a class that defines information and operations for structure assets for pull-down menus.
	TSharedPtr<FAssetTypeActions_PulldownStructAsset> AssetTypeActions;

	// Level editor extension point.
	TSharedPtr<FExtender> Extender;

	// Pull-down menu structure asset icon.
	TSharedPtr<FSlateStyleSet> StyleSet;
};

void FEasyPulldownStructModuleEd::StartupModule()
{
	// Register a class that defines information and operations of structure assets for pull-down menu.
	AssetTypeActions = MakeShareable(new FAssetTypeActions_PulldownStructAsset());
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AssetTypeActions.ToSharedRef());

	// Register the icon of the pull-down menu structure asset.
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("PulldownStructAssetStyle")));
	if (StyleSet.IsValid())
	{
		StyleSet->SetContentRoot(FPaths::Combine(
			FPaths::ConvertRelativePathToFull(FPaths::EngineContentDir()),
			TEXT("Editor"),
			TEXT("Slate"),
			TEXT("Icons"),
			TEXT("AssetIcons")
		));

		auto Path = StyleSet->RootToContentDir(TEXT("/UserDefinedEnum_64x"));

		// Divert standard Enum asset icons.
		FSlateImageBrush* Icon = new FSlateImageBrush(
			StyleSet->RootToContentDir(TEXT("/UserDefinedEnum_64x"), TEXT(".png")), FVector2D(64.f, 64.f)
		);
		if (StyleSet.IsValid())
		{
			StyleSet->Set("ClassThumbnail.PulldownStructAsset", Icon);
			FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
		}
	}

	// Add items to the window tab of the level editor.
	if (!IsRunningCommandlet())
	{
		Extender = MakeShareable(new FExtender);
		Extender->AddMenuExtension(
			"LevelEditor",
			EExtensionHook::After,
			NULL,
			FMenuExtensionDelegate::CreateRaw(this, &FEasyPulldownStructModuleEd::OnWindowMenuExtension)
		);

		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extender);
	}

	// Register a viewer that displays a list of pull-down menu structures in the global tab manager.
	TSharedRef<FGlobalTabmanager> GlobalTabmanager = FGlobalTabmanager::Get();
	GlobalTabmanager->RegisterTabSpawner(
		SPulldownStructViewer::TabName, FOnSpawnTab::CreateRaw(this, &FEasyPulldownStructModuleEd::HandleRegisterTabSpawner))
		.SetDisplayName(SPulldownStructViewer::WindowTitle);
}

void FEasyPulldownStructModuleEd::ShutdownModule()
{
	// Unregister a viewer that displays a list of pull-down menu structures in the global tab manager
	TSharedRef<FGlobalTabmanager> GlobalTabmanager = FGlobalTabmanager::Get();
	GlobalTabmanager->UnregisterTabSpawner(SPulldownStructViewer::TabName);

	// Remove items to the window tab of the level editor.
	if (Extender.IsValid() && FModuleManager::Get().IsModuleLoaded("LevelEditor"))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		LevelEditorModule.GetToolBarExtensibilityManager()->RemoveExtender(Extender);
	}

	// Unregister the icon of the pull-down menu structure asset.
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());

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

TSharedRef<SDockTab> FEasyPulldownStructModuleEd::HandleRegisterTabSpawner(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SPulldownStructViewer)
		];

	return SpawnedTab;
}

void FEasyPulldownStructModuleEd::OnWindowMenuExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("PulldownStructViewer_MenuTitle", "Pulldown Struct Viewer"),
		LOCTEXT("PulldownStructViewer_ToolTip", "Display a list of currently registered pull-down menu structures and the items displayed in that pull-down."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Outliner"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			TSharedRef<FGlobalTabmanager> GlobalTabmanager = FGlobalTabmanager::Get();
			GlobalTabmanager->InvokeTab(SPulldownStructViewer::TabName);
		}))
	);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEasyPulldownStructModuleEd, EasyPulldownStructEd)
