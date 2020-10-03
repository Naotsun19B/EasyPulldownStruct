// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStruct/EPS_PulldownStruct.h"

#if WITH_EDITOR
#include "EasyPulldownStructEd.h"
#endif

void FEPS_PulldownStructBase::RegisterPulldownStruct(UScriptStruct* StaticStruct, const TArray<TSharedPtr<FString>>& DisplayStrings)
{
	check(StaticStruct);
	auto Container = UEPS_DisplayStringsContainer::Get();
	check(Container);
	Container->RegisterDisplayStrings(StaticStruct->GetName(), DisplayStrings);
}
