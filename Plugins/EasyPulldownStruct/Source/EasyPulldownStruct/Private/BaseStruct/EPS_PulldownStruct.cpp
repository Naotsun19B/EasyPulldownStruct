// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseStruct/EPS_PulldownStruct.h"

#if WITH_EDITOR
#include "EPS_EditorGlobals.h"
#endif

void FEPS_PulldownStructBase::RegisterPulldownStruct(const FString& StructName, const TArray<TSharedPtr<FString>>& DisplayStrings)
{
	auto Container = UEPS_DisplayStringsContainer::Get();
	check(Container);
	Container->RegisterDisplayStrings(StructName, DisplayStrings);
}
