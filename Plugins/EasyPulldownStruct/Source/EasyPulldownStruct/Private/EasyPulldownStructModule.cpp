// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FEasyPulldownStructModule : public IModuleInterface
{
public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.
};

void FEasyPulldownStructModule::StartupModule()
{

}

void FEasyPulldownStructModule::ShutdownModule()
{

}

IMPLEMENT_MODULE(FEasyPulldownStructModule, EasyPulldownStruct)