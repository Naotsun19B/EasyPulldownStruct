// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStruct/EPS_PulldownStruct.h"
#include "SampleStruct.generated.h"

USTRUCT(BlueprintType)
struct PULLDOWNSTRUCTPLUGIN_API FSampleStruct : public FEPS_PulldownStructBase
{
	GENERATED_BODY()

public:
	FSampleStruct()
	{
		REGISTER_PULLDOWN_STRUCT();
	}

#if WITH_EDITOR
	virtual TArray<TSharedPtr<FString>> GetDisplayStrings() const override 
	{
		return TArray<TSharedPtr<FString>> 
		{
			MakeShareable(new FString(TEXT("ItemA"))),
			MakeShareable(new FString(TEXT("ItemB"))),
			MakeShareable(new FString(TEXT("ItemC")))
		};
	}
#endif
};
