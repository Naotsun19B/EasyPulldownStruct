// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

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

}

void FEasyPulldownStructModuleEd::ShutdownModule()
{

}

IMPLEMENT_MODULE(FEasyPulldownStructModuleEd, EasyPulldownStructEd)