// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logger.h"

void ULogger::LogErrorToScreen(const FString& DisplayString, float TimeToDisplay, int Key) {
	LogToScreen(LogType::ERROR, TimeToDisplay, DisplayString, Key);
}

void ULogger::LogNoticeToScreen(const FString& DisplayString, float TimeToDisplay, int Key) {
	LogToScreen(LogType::NOTICE, TimeToDisplay, DisplayString, Key);
}

void ULogger::LogWarningToScreen(const FString& DisplayString, float TimeToDisplay, int Key) {
	LogToScreen(LogType::WARNING, TimeToDisplay, DisplayString, Key);
}

void ULogger::LogToScreen(LogType LoggingType, float TimeToDisplay, const FString& DisplayString, int Key) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(Key, TimeToDisplay, GetLogColor(LoggingType), DisplayString);
}

FColor ULogger::GetLogColor(LogType LoggingType) {
	switch (LoggingType)
	{
	case LogType::NOTICE:
		return NoticeColor;
	case LogType::WARNING:
		return WarningColor;
	case LogType::ERROR:
		return ErrorColor;
	default:
		return FColor::White;
	}
}

// specifiying colors
const FColor ULogger::ErrorColor = FColor::Red;
const FColor ULogger::WarningColor = FColor::Yellow;
const FColor ULogger::NoticeColor = FColor::White;