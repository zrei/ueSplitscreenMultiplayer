// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logger.generated.h"

UCLASS()
class SPLITSCREEN_API ULogger : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static enum LogType : char {
		NOTICE = 0,
		WARNING = 1,
		ERROR = 2
	};

public:
	UFUNCTION(BlueprintCallable)
	static void LogErrorToScreen(const FString& DisplayString, float TimeToDisplay = 5, int Key = -1);

	UFUNCTION(BlueprintCallable)
	static void LogNoticeToScreen(const FString& DisplayString, float TimeToDisplay = 5, int Key = -1);

	UFUNCTION(BlueprintCallable)
	static void LogWarningToScreen(const FString& DisplayString, float TimeToDisplay = 5, int Key = -1);

private:
	static const FColor ErrorColor;
	static const FColor WarningColor;
	static const FColor NoticeColor;

	static void LogToScreen(LogType LoggingType, float TimeToDisplay, const FString& DisplayString, int Key = -1);
	static FColor GetLogColor(LogType LoggingType);
};
