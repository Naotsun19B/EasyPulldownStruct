// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION < 25
#define BEFORE_UE425 1
#else
#define BEFORE_UE425 0
#endif

#if BEFORE_UE425
using FProperty = UProperty;
#endif

EASYPULLDOWNSTRUCTED_API DECLARE_LOG_CATEGORY_EXTERN(LogEasyPulldownStruct, Log, All);
