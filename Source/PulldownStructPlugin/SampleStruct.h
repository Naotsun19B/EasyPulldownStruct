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
	virtual EEPS_PulldownSource GetPulldownSourceType() const { return EEPS_PulldownSource::Array; }

	virtual TArray<FString> GetSourceArray() const override 
	{
		return TArray<FString>
		{
			TEXT("ItemA"),
			TEXT("ItemB"),
			TEXT("ItemC")
		};
	}
#endif
};
