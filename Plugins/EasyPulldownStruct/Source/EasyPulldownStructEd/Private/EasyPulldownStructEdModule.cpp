// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "EPS_EditorGlobals.h"
#include "Misc/EPS_PulldownGraphPinFactory.h"

DEFINE_LOG_CATEGORY(LogEasyPulldownStruct);

class FEasyPulldownStructModuleEd : public IModuleInterface
{
public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.
};

void FEasyPulldownStructModuleEd::StartupModule()
{
	FEPS_PulldownGraphPinFactory::RegisterPulldownGraphPinFactory();
}

void FEasyPulldownStructModuleEd::ShutdownModule()
{
	
}

IMPLEMENT_MODULE(FEasyPulldownStructModuleEd, EasyPulldownStructEd)