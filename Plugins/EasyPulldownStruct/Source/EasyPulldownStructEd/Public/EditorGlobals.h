// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

/**
 * Since there is a big difference between UE4.25 and earlier, 
 * such as the absence of FProperty, a macro for branching processing.
 */
#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION < 25)
#define BEFORE_UE425 1
#else
#define BEFORE_UE425 0
#endif

/**
 * FProperty does not exist before UE4.25, so replace it with UProperty.
 */
#if BEFORE_UE425
using FProperty = UProperty;
#endif

/**
 * Categories used for log output with this plugin.
 */
EASYPULLDOWNSTRUCTED_API DECLARE_LOG_CATEGORY_EXTERN(LogEasyPulldownStruct, Log, All);
