// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStruct/PulldownStructBase.h"
#include "SampleStruct.generated.h"

USTRUCT(BlueprintType)
struct PULLDOWNSTRUCTPLUGIN_API FSampleStruct : public FPulldownStructBase
{
	GENERATED_BODY()

public:
	FSampleStruct()
	{
		REGISTER_PULLDOWN_STRUCT();
	}

#if WITH_EDITOR
	virtual EPulldownSource GetPulldownSourceType() const { return EPulldownSource::PS_Array; }

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
