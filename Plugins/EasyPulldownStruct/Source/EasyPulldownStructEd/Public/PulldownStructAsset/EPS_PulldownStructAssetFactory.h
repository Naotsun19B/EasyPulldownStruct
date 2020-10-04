// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "EPS_PulldownStructAssetFactory.generated.h"

class UEPS_PulldownStructAsset;

/**
 * Factory class to create struct assets for pull-down menus.
 */
UCLASS(HideCategories = "Object")
class EASYPULLDOWNSTRUCTED_API UEPS_PulldownStructAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
public:
	// UFactory interface.
	virtual bool DoesSupportClass(UClass* Class) override;
	virtual UClass* ResolveSupportedClass() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface.
};
