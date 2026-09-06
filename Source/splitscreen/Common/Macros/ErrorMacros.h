// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/Logger.h"

#if !UE_BUILD_SHIPPING
#define LOG_ERROR_AND_RETURN_VOID(identifier, error) ULogger::LogErrorToScreen(FString::Printf(TEXT("[%s]. Error: %s"), identifier, error), 5); return;
#define LOG_ERROR_AND_RETURN_NULL(identifier, error) ULogger::LogErrorToScreen(FString::Printf(TEXT("[%s]. Error: %s"), identifier, error), 5); return NULL;
#else 
#define LOG_ERROR_AND_RETURN_VOID(identifier, error) return;
#define LOG_ERROR_AND_RETURN_NULL(identifier, error) return NULL;
#endif

#define CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(pointer, identifier, error) if (!(pointer)) { LOG_ERROR_AND_RETURN_VOID(identifier, error) }
#define CHECK_POINTER_IF_NULL_LOG_ERROR_AND_RETURN_NULL(pointer, identifier, error) if (!(pointer)) { LOG_ERROR_AND_RETURN_NULL(identifier, error) }